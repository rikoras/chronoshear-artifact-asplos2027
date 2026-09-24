#pragma once
#include "oracle_prefetch_cursor.h"
#include <stdexcept>

#if (defined(BOOM_GUIDER_CFG_LARGEBOOM_RC) || defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)) && !defined(CHISA_WIDE_MODEL)
#error "Large bindings require the native model; no legacy adapter is available."
#endif

// ==========================================================================
// The join between the generated stream registry and the model.
//
// `generated/system_probe_registry.inc` lists all 2,086 selected streams and
// is regenerated whenever CHISA's oracle selection changes.  This file is the
// hand-maintained other half: which of those streams the model can currently
// predict, and with what expression.
//
// Keeping the two apart is deliberate.  The generated list is the obligation
// and must never be edited to make a gate pass; the bindings are the claim,
// and a claim that names a stream the manifest no longer selects, or that
// binds one stream twice, is rejected at registration rather than silently
// ignored.  Streams with no binding register as UNMODELED and are reported as
// such -- an honest zero, not a passing green.
//
// Subsystems are added by writing a `register_<subsystem>_bindings()` and
// calling it from `register_model_bindings()`.  Explicit calls rather than
// static-initializer self-registration: the order in which bindings appear
// must not depend on link order, because a duplicate-binding error that only
// reproduces in some builds is worse than no check at all.
// ==========================================================================

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <atomic>
#include "../boom_model/common/boom_uop_pack.h"
#if defined(__x86_64__) || defined(__i386__)
#include <immintrin.h>  // _mm_prefetch in the unified-row scan
#endif
#include <cmath>
#include <map>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#if defined(__AVX512BW__)
#include <immintrin.h>
#endif

#include "generated/system_oracle_record.h"
#include "oracle_timing.h"
#include "sample_placement.h"

namespace chisa::boom_model { struct Image; }
namespace chisa::boom_system {

// Packed 45-bit ROB uop row, matching the v2 state-array layout
// (MSB..LSB): uopc7 is_rvc1 ftq_idx4 edge_inst1 pc_lob6 pdst6 stale_pdst6
// is_fencei1 uses_ldq1 uses_stq1 is_sys_pc2epc1 flush_on_commit1 ldst6
// ldst_val1 dst_rtype2.
// RPQ occupancy bitmap in bank order (slot 0 at the top bit).
inline uint64_t rpq_valids_bank(std::size_t head, std::size_t count,
                                std::size_t depth = 16) {
  uint64_t v = 0;
  for (std::size_t i = 0; i < count && i < depth; ++i)
    v |= uint64_t(1) << (depth - 1 - ((head + i) % depth));
  return v;
}

// Mirror the BranchKillableQueue `valids` register directly.  An entry
// killed this edge (flush/branch) clears its valid bit the same cycle,
// whereas rpq_count is only decremented on the following edge when the
// dead head auto-pops -- so the count-based bank lags RTL by one cycle
// for a killed-but-not-yet-popped entry.  Reading the live per-slot
// valid flags keeps the occupancy bitmap edge-aligned with the hardware.
template <class MshrT>
inline uint64_t rpq_valids_bank_live(const MshrT& mshr,
                                     std::size_t depth = 16) {
  uint64_t v = 0;
  for (std::size_t i = 0; i < mshr.rpq_count && i < depth; ++i) {
    const std::size_t slot = (mshr.rpq_head + i) % depth;
    if (mshr.rpq[slot].valid)
      v |= uint64_t(1) << (depth - 1 - slot);
  }
  return v;
}

// The int-response wire shows the pending writeback closest to firing
// (the response stream head); falls back to the pipe shadow when the
// pool is empty.
template <class CoreT>
inline uint64_t iresp_wire_rob(const CoreT& c) {
  int best = -1;
  unsigned best_left = 255;
  for (int i = 0; i < 16; ++i)
    if (c.wb_pend[i].v && c.wb_pend[i].left < best_left) {
      best_left = c.wb_pend[i].left;
      best = i;
    }
  return best >= 0 ? c.wb_pend[best].rob_idx
                   : c.omir.oracle_b4_uop.rob_idx;
}

// pack_rob_uop: boom/boom_uop_pack.h (cached per ROB entry by the core).
// The lockstep runtime names it through this namespace.
using ::pack_rob_uop;

class SystemGuider;
class WatchSink;

/** Watch declarations (generated/watch_bindings.inc) decide with these
  * whether an expression is an addressable model field. */
template <class T>
inline constexpr bool watch_lvalue = std::is_lvalue_reference_v<T>;
template <class T>
inline constexpr bool watch_scalar =
    (std::is_integral_v<T> || std::is_enum_v<T>) && sizeof(T) <= 8;
/** A `chain ? 1u : 0u` store may only bind the chain directly when the
  * chain really is a bool (a wider field would need the != 0 fold). */
template <class T>
inline constexpr bool watch_bool =
    std::is_same_v<std::remove_cv_t<std::remove_reference_t<T>>, bool>;

using PredictFn = uint64_t (*)(const SystemGuider&);
using CareFn = bool (*)(const SystemGuider&);

struct ModelBinding {
  PredictFn predict = nullptr;
  CareFn care = nullptr;  // null => always compared
  int sampled_slot = -1;  // >=0: prediction is the pre-step sample buffer
  BindingTiming timing = BindingTiming::PostStepCycle;
};

/** A stream bound through the central cycle-start sample buffer.
  *
  * This is usually a PRE register image, but it may also be a POST
  * combinational value whose operands must be read before the model mutates
  * them in place (an asynchronous SRAM read is the common case).  The latter
  * must use the explicit `*_sampled_combinational` API.  The first cycle
  * reports zero, matching the generated simulator image before any edge. */
using SampleFn = uint64_t (*)(const SystemGuider&);
using IndexedSampleFn = uint64_t (*)(const SystemGuider&, std::size_t);
using IdlePredicate = bool (*)(const SystemGuider&);
using SampleEpochFn = uint64_t (*)(const SystemGuider&);

/** Export offload ring: single producer (the model's thread) and single
  * consumer (the export worker).  The model's thread ships what the export
  * side needs and nothing it computes: moved unified rows (64 bytes plus
  * their byte mask), moved values as (lane, value) pairs, and the two
  * per-position control marks the writer acts on.  Records never wrap
  * around the ring end (a pad record fills the tail instead).  Pairs are
  * appended to an open record that is sealed when a record of another
  * kind follows, so a cycle's changes cross as a few dense records. */
class ExportRing {
 public:
  enum Kind : std::uint8_t {
    kPairs = 1, kRows = 2, kFlush = 3, kPredicted = 4, kFinish = 5, kPad = 6,
    kWindow = 7,  // block field = window number: the window's positions are all in
    kImageRows = 8  // changed groups of the already formed record, not model rows
  };
  struct Header {
    std::uint64_t block;  // kFlush / kFinish: the block being written
    std::uint32_t payload_bytes;  // exact; records are laid out at 16-byte steps
    std::int16_t position;
    std::uint8_t kind;
    std::uint8_t pad;
  };
  /** kRows payload: per moved row a u32 head {u16 dense row index; u8 group
    * bits; u8 zero}, followed by the row's 8-byte groups whose bit is set
    * (group g is present iff (mask >> 8g) & 0xff != 0), in group order.
    * The consumer recovers the moved-byte mask by comparing the groups with
    * its own copy of the row, restricted to the claimed bytes. */
  static constexpr std::size_t kRowHeadBytes = 4;
  static constexpr std::size_t kRowCapacity = kRowHeadBytes + 64;
  /** kPairs / kPredicted payload: repeated {u16 lane; value in
    * (lane bits + 7) / 8 bytes, already masked to the lane width}. */
  static_assert(sizeof(Header) == 16, "ring headers are 16 bytes");
  static constexpr std::size_t kMaxPayload = std::size_t{1} << 12;  // pairs record cap
  static constexpr std::size_t kMaxEntry = 2 + 8;
  /** The two shared counters are the only cache lines both threads touch,
    * so they move rarely: the producer makes records visible at the
    * control marks (twice per cycle) and otherwise every kPublishBytes;
    * the consumer reports freed space when it catches up and otherwise
    * every kPublishBytes.  Everything else each side touches sits on its
    * own cache lines. */
  static constexpr std::size_t kPublishBytes = std::size_t{1} << 15;  // 32 KiB

  explicit ExportRing(std::size_t ring_bytes)
      : ring_(ring_bytes), ring_mask_(ring_bytes - 1) {
    base_ = ring_.data();
  }
  ExportRing(const ExportRing&) = delete;
  ExportRing& operator=(const ExportRing&) = delete;

  static std::size_t round16(std::size_t n) { return (n + 15) & ~std::size_t{15}; }
  /** One bit per 8-byte group of a 64-byte row that has any set mask bit. */
  static unsigned group_bits(std::uint64_t mask) {
    std::uint64_t m = mask;
    m |= m >> 4;
    m |= m >> 2;
    m |= m >> 1;
#if defined(__BMI2__)
    return static_cast<unsigned>(_pext_u64(m, UINT64_C(0x0101010101010101)));
#else
    unsigned g = 0;
    for (unsigned k = 0; k < 8; ++k) g |= static_cast<unsigned>((m >> (8 * k)) & 1u) << k;
    return g;
#endif
  }

  // ---- producer side --------------------------------------------------
  /** Worst-case rows record, from the number of unified rows. */
  void set_rows_capacity(std::size_t rows) { rows_capacity_ = rows * kRowCapacity; }
  void push_pair(std::uint16_t lane, std::uint64_t value, unsigned bits) {
    append_pair(kPairs, lane, value, bits);
  }
  void push_predicted(std::uint16_t lane, std::uint64_t value, unsigned bits) {
    append_pair(kPredicted, lane, value, bits);
  }
  void push_row(std::uint32_t index, std::uint64_t mask, const unsigned char* row) {
    push_row_as(kRows, index, mask, row);
  }
  void push_image_row(std::uint32_t index, std::uint64_t mask, const unsigned char* row) {
    push_row_as(kImageRows, index, mask, row);
  }
  void push_row_as(Kind kind, std::uint32_t index, std::uint64_t mask,
                   const unsigned char* row) {
    if (open_kind_ != kind) {
      close_open();
      open(kind, rows_capacity_);
    }
    unsigned char* p = base_ + (cursor_ & ring_mask_);
    const unsigned g = group_bits(mask);
    const std::uint32_t head = (index & 0xffffu) | (g << 16);
    std::memcpy(p, &head, kRowHeadBytes);
#if defined(__AVX512F__)
    // The set groups, packed; the store covers 64 bytes and the cursor only
    // claims the packed ones (open() reserves the slack).
    _mm512_storeu_si512(p + kRowHeadBytes,
                        _mm512_maskz_compress_epi64(static_cast<__mmask8>(g),
                                                    _mm512_loadu_si512(row)));
    cursor_ += kRowHeadBytes + 8 * static_cast<unsigned>(__builtin_popcount(g));
#else
    p += kRowHeadBytes;
    std::size_t n = kRowHeadBytes;
    unsigned rest = g;
    while (rest != 0) {
      const unsigned k = static_cast<unsigned>(__builtin_ctz(rest));
      rest &= rest - 1;
      std::memcpy(p, row + 8 * k, 8);
      p += 8;
      n += 8;
    }
    cursor_ += n;
#endif
    ++stat_rows_;
  }
  void push_control(Kind kind, std::uint64_t block, int position) {
    close_open();
    begin(kind, 0, block, position);
    cursor_ += sizeof(Header);
    publish();
  }
  /** Seal the open record: its header gets the exact payload size and the
    * cursor moves to the next 16-byte step. */
  void close_open() {
    if (open_kind_ == 0) return;
    Header h;
    unsigned char* at = base_ + (open_start_ & ring_mask_);
    std::memcpy(&h, at, sizeof(Header));
    const std::size_t payload = cursor_ - open_start_ - sizeof(Header);
    h.payload_bytes = static_cast<std::uint32_t>(payload);
    std::memcpy(at, &h, sizeof(Header));
    cursor_ = open_start_ + sizeof(Header) + round16(payload);
    open_kind_ = 0;
  }
  /** Make everything appended so far visible to the consumer. */
  void publish() {
    close_open();
    if (published_ == cursor_) return;
    published_ = cursor_;
    ++stat_publishes_;
    head_.store(cursor_, std::memory_order_release);
  }
  /** Everything published has been consumed. */
  bool drained() const {
    return tail_.load(std::memory_order_acquire) >= head_.load(std::memory_order_acquire);
  }
  // producer-side counters (since construction)
  std::uint64_t stat_rows() const { return stat_rows_; }
  std::uint64_t stat_pairs() const { return stat_pairs_; }
  std::uint64_t stat_publishes() const { return stat_publishes_; }
  std::uint64_t stat_bytes() const { return cursor_; }

  // ---- consumer side --------------------------------------------------
  bool pop(Header& h, const unsigned char*& payload) {
    if (tail_local_ >= head_seen_) {
      report_tail();
      head_seen_ = head_.load(std::memory_order_acquire);
      if (tail_local_ >= head_seen_) return false;
    }
    const unsigned char* at = base_ + (tail_local_ & ring_mask_);
    std::memcpy(&h, at, sizeof(Header));
    payload = at + sizeof(Header);
    return true;
  }
  void advance(const Header& h) {
    tail_local_ += sizeof(Header) + round16(h.payload_bytes);
    if (tail_local_ - tail_reported_ >= kPublishBytes) report_tail();
  }
  /** Experiment: consume everything published without reading it. */
  void skip_all() {
    head_seen_ = head_.load(std::memory_order_acquire);
    tail_local_ = head_seen_;
    report_tail();
  }

 private:
  void append_pair(Kind kind, std::uint16_t lane, std::uint64_t value, unsigned bits) {
    if (open_kind_ != kind || cursor_ - open_start_ - sizeof(Header) + kMaxEntry > kMaxPayload) {
      close_open();
      open(kind, kMaxPayload);
    }
    unsigned char* p = base_ + (cursor_ & ring_mask_);
    std::memcpy(p, &lane, 2);
    std::memcpy(p + 2, &value, 8);  // over-store; the cursor advances by the lane's bytes
    cursor_ += 2 + ((bits + 7u) >> 3);
    ++stat_pairs_;
  }
  void open(Kind kind, std::size_t capacity) {
    if (cursor_ - published_ >= kPublishBytes) publish();
    reserve(sizeof(Header) + capacity + 64);  // +64: entry over-store slack
    Header h{0, 0, 0, kind, 0};
    std::memcpy(base_ + (cursor_ & ring_mask_), &h, sizeof(Header));
    open_start_ = cursor_;
    cursor_ += sizeof(Header);
    open_kind_ = kind;
  }
  /** Write a header at the cursor (after making room) and return the
    * payload position; the caller advances the cursor once the payload is
    * in place. */
  unsigned char* begin(Kind kind, std::size_t payload_bytes, std::uint64_t block,
                       int position) {
    reserve(sizeof(Header) + payload_bytes);
    Header h{block, static_cast<std::uint32_t>(payload_bytes),
             static_cast<std::int16_t>(position), kind, 0};
    unsigned char* at = base_ + (cursor_ & ring_mask_);
    std::memcpy(at, &h, sizeof(Header));
    return at + sizeof(Header);
  }
  /** Make `need` contiguous bytes available at the cursor: pad to the ring
    * end when the record would wrap, then wait for the consumer to free
    * enough space. */
  void reserve(std::size_t need) {
    const std::size_t offset = cursor_ & ring_mask_;
    if (offset + need > ring_mask_ + 1) {
      const std::size_t pad = ring_mask_ + 1 - offset;
      wait_for_space(pad);
      Header h{0, static_cast<std::uint32_t>(pad - sizeof(Header)), 0, kPad, 0};
      std::memcpy(base_ + offset, &h, sizeof(Header));
      cursor_ += pad;
    }
    wait_for_space(need);
  }
  void wait_for_space(std::size_t need) {
    if (cursor_ + need - tail_seen_ <= ring_mask_ + 1) return;
    publish();  // the consumer can only free what it can see
    for (;;) {
      tail_seen_ = tail_.load(std::memory_order_acquire);
      if (cursor_ + need - tail_seen_ <= ring_mask_ + 1) return;
#if defined(__x86_64__)
      __builtin_ia32_pause();
#endif
    }
  }
  void report_tail() {
    if (tail_reported_ == tail_local_) return;
    tail_reported_ = tail_local_;
    tail_.store(tail_local_, std::memory_order_release);
  }

  std::vector<unsigned char> ring_;
  // read-only after construction
  alignas(64) unsigned char* base_ = nullptr;
  std::size_t ring_mask_ = 0;
  std::size_t rows_capacity_ = 0;
  // producer-private
  alignas(64) std::uint64_t cursor_ = 0;  // reserved end (>= published head)
  std::uint64_t open_start_ = 0;          // header of the open record
  std::uint64_t published_ = 0;           // last head_ value stored
  std::uint64_t tail_seen_ = 0;           // last tail_ value loaded
  std::uint8_t open_kind_ = 0;
  std::uint64_t stat_rows_ = 0;
  std::uint64_t stat_pairs_ = 0;
  std::uint64_t stat_publishes_ = 0;
  // consumer-private
  alignas(64) std::uint64_t tail_local_ = 0;
  std::uint64_t head_seen_ = 0;
  std::uint64_t tail_reported_ = 0;
  // shared
  alignas(64) std::atomic<std::uint64_t> head_{0};
  alignas(64) std::atomic<std::uint64_t> tail_{0};
};

class ExportThread;

class ModelBindings {
 public:
  friend class ExportThread;
  using DispatchFn = void (*)(const SystemGuider&, ModelBindings&);
  static ModelBindings& instance() {
    static ModelBindings bindings;
    return bindings;
  }

  /** Claim one manifest stream. Binding the same key twice is a programming
    * error: two subsystems each believing they own a stream is exactly how a
    * prediction silently stops being checked. */
  void bind(const char* trace_key, PredictFn predict, CareFn care = nullptr);

  void set_care(const char* trace_key, CareFn care) {
    bindings_.at(trace_key).care=care;
  }
  int sampled_size() const { return static_cast<int>(lane_of_slot_.size()); }

  /** A direct post-step accessor that deliberately returns a register image
    * saved at cycle start.  This is not a one-cycle-late register binding: the
    * component owns the snapshot and the accessor merely reads it after the
    * step.  Keep this spelling explicit so timing audits can distinguish that
    * proof from an accidental register<-post connection. */
  void bind_register_snapshot(const char* trace_key, PredictFn predict,
                              CareFn care = nullptr) {
    bind(trace_key, predict, care);
    bindings_.at(trace_key).timing =
        BindingTiming::PostStepRegisterSnapshot;
  }

  /** Claim one manifest stream through the pre-step sample buffer. */
  void bind_sampled(const char* trace_key, SampleFn sample);

  /** A combinational oracle computed from the cycle-start state before the
    * model mutates that state in place.  Typical examples are asynchronous
    * SRAM MPORTs: POST in the RTL tap, but safest to calculate from the PRE
    * memory image and this cycle's address. */
  void bind_sampled_combinational(const char* trace_key, SampleFn sample) {
    bind_sampled(trace_key, sample);
    bindings_.at(trace_key).timing = BindingTiming::PreStepCombinational;
  }

  /** Indexed variant used when many homogeneous generated-RTL registers are
    * exposed through one compact sidecar array. */
  void bind_indexed_sampled(const char* trace_key, IndexedSampleFn sample,
                            std::size_t index, IdlePredicate idle = nullptr,
                            SampleEpochFn epoch = nullptr) {
    const int slot = reserve_sampled(trace_key);
    const IndexedEntry entry{static_cast<uint32_t>(slot),
                             static_cast<uint32_t>(index)};
    for (IndexedSamplerGroup& group : indexed_sampler_groups_) {
      if (group.fn == sample && group.idle == idle && group.epoch == epoch) {
        group.entries.push_back(entry);
        return;
      }
    }
    indexed_sampler_groups_.push_back(
        IndexedSamplerGroup{sample, idle, epoch, 0, false, {entry}});
  }

  /** Indexed cycle-start reconstruction of a POST combinational stream. */
  void bind_indexed_sampled_combinational(const char* trace_key,
                                           IndexedSampleFn sample,
                                           std::size_t index,
                                           IdlePredicate idle = nullptr,
                                           SampleEpochFn epoch = nullptr) {
    bind_indexed_sampled(trace_key, sample, index, idle, epoch);
    bindings_.at(trace_key).timing = BindingTiming::PreStepCombinational;
  }

  /** Profiled-constant claim: the stream held one value through the entire
    * profiling run (fail-closed: Micro-Lockstep still compares every cycle,
    * so a workload that wakes the stream turns the run red instead of
    * wrong). The value is written into the sample buffer once; the sampler
    * slot stays null, so steady state costs nothing per cycle. */
  int reserve_constant(const char* trace_key, uint64_t value) {
    const int slot = reserve_sampled(trace_key);
    bindings_.at(trace_key).timing = BindingTiming::ProfileConstant;
    // Cycle 0 compares against the generated simulator's pre-edge zero
    // image; the steady (reset) value only appears from cycle 1. Arm the
    // buffer at the first sample call instead of at registration.
    deferred_constants_.emplace_back(slot, value);
    return slot;
  }

  /** Structurally constant claim: configuration or top-level wiring proves
    * that the steady value cannot change for any workload accepted by this
    * fixed TestHarness.  Cycle zero still uses the generated simulator's
    * pre-edge zero image, as reserve_constant() does.  Call sites must carry
    * the proof; a quiet trace is not sufficient.  The separate API keeps
    * topology facts distinguishable from profile assumptions in source
    * review and qualification tooling. */
  int reserve_structural_constant(const char* trace_key, uint64_t value) {
    const int slot = reserve_sampled(trace_key);
    bindings_.at(trace_key).timing = BindingTiming::StructuralConstant;
    deferred_constants_.emplace_back(slot, value);
    return slot;
  }

  /** Batch form: reserve one buffer slot per key, then register a single
    * function that fills the whole contiguous range with direct member
    * access.  One call per subsystem instead of one indirect call per
    * stream keeps the sampling cost flat as coverage grows. */
  int reserve_sampled(const char* trace_key);
  /** A stream the model writes directly into the record (the record is
    * the model image, generated/image.h): no sampler, no shadow.  A
    * register stream is the register itself; a combinational stream is
    * computed from the committed state at the end of the step (the
    * position after this one), like the placed samplers did. */
  void reserve_image_owned(const char* trace_key, bool combinational);
  std::size_t image_owned_lane_count() const { return owned_lanes_.size(); }
  int reserve_sampled_combinational(const char* trace_key) {
    const int slot = reserve_sampled(trace_key);
    bindings_.at(trace_key).timing = BindingTiming::PreStepCombinational;
    return slot;
  }

  /** Keep a contiguous batch's slot layout when one member is exported
    * directly after the model step instead of through the pre-step buffer.
    * The batch may still write this unused slot; it has no manifest binding
    * and maps to the pad lane, which the writer ignores. */
  int reserve_batch_scratch() {
    const int slot = static_cast<int>(lane_of_slot_.size());
    lane_of_slot_.push_back(kOracleRecordPadLane);
    shadow_slots_.push_back(0);
    return slot;
  }
  /** A batch's view of its slots: the raw-value shadow (registration
    * order, the compare target) and the manifest lane of each slot. */
  struct BatchSlots {
    uint64_t* values;
    const std::uint16_t* lanes;
    // Deferred: store plainly, a later diff finds what moved (unused by
    // the batches: rewriting the whole 16 KB slot array every cycle costs
    // more in cache write traffic than the compares it saves).
    bool deferred;
    // Per slot (base-relative): >= 0 when the slot is a gathered field, so
    // a generated group skips the accessor store it also carries.
    const int32_t* gather_index = nullptr;
    // The bindings these slots belong to (batch_store commits through it
    // instead of the guarded singleton accessor).
    ModelBindings* owner = nullptr;

  };
  using BatchSampleFn = void (*)(const SystemGuider&, BatchSlots slots);
  using SamplePlacement = ::chisa::boom_system::SamplePlacement;
  /** A batch's watch declaration: which model fields its slots copy and
    * which model regions its other expressions read (generated by
    * duts/boom-repcut/scripts/generate_watch_bindings.py). */
  using WatchFn = void (*)(const SystemGuider&, BatchSlots, WatchSink&);

  /** SYSMODEL_ALL_PRESTEP=1: every placed batch and evaluator runs at the
    * cycle start instead of right after its component commits (one scan
    * point; the values are the same when a field survives to the step end,
    * which SYSMODEL_SAMPLE_CHECK verifies). */
  static bool all_prestep() {
    static const bool on = std::getenv("SYSMODEL_ALL_PRESTEP") != nullptr;
    return on;
  }
  void add_batch_sampler(BatchSampleFn fn, int base,
                         SamplePlacement placement = SamplePlacement::PreStep,
                         WatchFn watch = nullptr) {
    if (all_prestep()) placement = SamplePlacement::PreStep;
    batches_.push_back(Batch{fn, base, placement, watch, false, -1, 0});
  }

  // ---- Change-detected sampling -------------------------------------
  // A watched field is compared as part of its 64-byte line: one vector
  // compare per line per cycle, and only the fields inside a moved line
  // are loaded and committed.  An evaluator (a batch, or one generated
  // per-slot function) runs only when a line of one of its declared
  // regions moved.  Built once per model instance by attach().
  static constexpr std::size_t kMaxRegionBytes = 8192;
  int add_evaluator(BatchSampleFn fn, int base, SamplePlacement placement,
                    int slot = -1, int batch = -1, int ordinal = -1,
                    uint32_t stores = 1) {
    if (all_prestep()) placement = SamplePlacement::PreStep;
    Evaluator e{fn, base, placement, 0, false, slot};
    e.batch = batch;
    e.ordinal = ordinal;
    e.stores = stores == 0 ? 1 : stores;
    evaluators_.push_back(e);

    return static_cast<int>(evaluators_.size()) - 1;
  }

  /** Generated static dispatchers (one per placement): every evaluator is
    * a direct call guarded by its batch's due bit, so no per-evaluator
    * indirect call has to be predicted each cycle. */
  using PhasePrepareFn = void (*)(const SystemGuider&);
  void set_phase_prepare(SamplePlacement placement,PhasePrepareFn fn) {
    phase_prepare_[static_cast<std::size_t>(placement)]=fn;
  }
  void set_dispatch(SamplePlacement placement, DispatchFn fn) {
    dispatch_[static_cast<std::size_t>(placement)] = fn;
  }
  uint64_t due_bits(int batch, std::size_t word) const {
    return batch < 0 ? 0 : due_bits_[static_cast<std::size_t>(batch) * kDueWords + word];
  }
  bool batch_due(int batch) const {
    if (batch < 0) return false;
    const uint64_t* w = &due_bits_[static_cast<std::size_t>(batch) * kDueWords];
    return (w[0] | w[1] | w[2] | w[3]) != 0;
  }
  void set_exact_dispatch(DispatchFn fn) { exact_dispatch_ = fn; }
  BatchSlots slots_of_index(int batch) {
    return slots_of(batches_[static_cast<std::size_t>(batch)]);
  }
  void add_field(std::size_t slot, const void* addr, std::size_t bytes,
                 bool is_signed, SamplePlacement placement) {
    field_builds_.push_back(FieldBuild{
        static_cast<const unsigned char*>(addr), static_cast<uint32_t>(slot),
        static_cast<uint8_t>(bytes), is_signed, placement});
  }
  void add_region(int evaluator, const void* addr, std::size_t bytes,
                  const char* what = "") {
    if (evaluator < 0) return;
    if (bytes > kMaxRegionBytes) {
      // Too large to watch: the evaluator runs every cycle and must never
      // be gated again on the small regions it may also have declared.
      Evaluator& e = evaluators_[static_cast<std::size_t>(evaluator)];
      if (!e.forced) {
        e.why = what;
        e.why_bytes = bytes;
      }
      e.always = true;
      e.forced = true;
      return;
    }
    region_builds_.push_back(RegionBuild{
        static_cast<const unsigned char*>(addr), bytes,
        static_cast<uint32_t>(evaluator), what});
  }
  void add_masked_region(int evaluator,const void* addr,std::size_t bytes,
                         uint64_t mask,const char* what) {
    if(evaluator<0)return;
    if(bytes>8) { add_region(evaluator,addr,bytes,what);return; }
    region_builds_.push_back(RegionBuild{static_cast<const unsigned char*>(addr),
                                        bytes,static_cast<uint32_t>(evaluator),what,mask});
  }
  /** Declare a unified storage region: watched fields whose storage lies
    * inside it are no longer gathered field-by-field; the region's memory
    * is compared line-by-line against a shadow at the cycle-start diff and
    * only the fields under moved bytes are committed.  Timing note: this
    * commits at the cycle-start diff, exactly when the deferred gather
    * path committed, so the record contract is unchanged (verified per
    * field by SYSMODEL_UNIFY_CHECK=1).  Fields that are an exact
    * evaluator's input, or that alias another claimed field's bytes, stay
    * on the gather path. */
  void unify_region(const void* addr, std::size_t bytes, const char* name) {
    unify_builds_.push_back(UnifyBuild{
        static_cast<const unsigned char*>(addr), bytes, name});
  }
  void mark_always(int evaluator, const char* why = "") {
    if (evaluator < 0) return;
    Evaluator& e = evaluators_[static_cast<std::size_t>(evaluator)];
    if (!e.forced) e.why = why;
    e.always = true;
    e.forced = true;
  }
  void mark_exact(int evaluator) {
    if (evaluator >= 0) evaluators_[static_cast<std::size_t>(evaluator)].exact = true;
  }
  /** A dependency of an exact evaluator: gathered (at End) without a
    * lane; a move of it wakes the evaluator at the next cycle start. */
  void add_input(int evaluator, const void* addr, std::size_t bytes, bool is_signed) {
    if (evaluator < 0) return;
    input_builds_.push_back(InputBuild{static_cast<const unsigned char*>(addr),
                                       static_cast<uint8_t>(bytes), is_signed,
                                       static_cast<uint32_t>(evaluator)});
  }
  /** Bind the watch tables to one model instance (addresses are taken
    * from it; it must not move afterwards). */
  void attach(const SystemGuider& model);
  void set_check_mode(bool on) { check_mode_ = on; }
  bool check_mode() const { return check_mode_; }

  /** Change list for the transport: lanes whose record value moved since
    * the writer last sealed a position, in store order (a lane may appear
    * more than once; the last value wins).  Bounded: past the capacity the
    * list is marked overflowed and the writer ships the whole record for
    * that position instead. */
  static constexpr std::size_t kChangeCapacity = 2304;
  /** Predicted lanes listed per position (>= the registered predicted
    * lanes, checked at registration). */
  static constexpr std::size_t kPredictedCapacity = 1024;
  const std::uint16_t* changed_lanes() const { return changed_lanes_; }
  std::size_t change_count() const { return change_count_; }
  bool change_overflow() const { return change_count_ >= kChangeCapacity; }
  void seal_changes() { change_count_ = 0; }
  /** Export offload: with a ring attached, moved values and moved unified
    * rows leave through it instead of the local lane cells / change list
    * (the worker owns those, see export_thread.h). */
  void set_export_ring(ExportRing* ring) {
    ring_ = ring;
    if (ring != nullptr) snapshot_image_owned();
  }
  /** Image-owned lanes are written by the model straight into the record.
    * Under export offload the worker only sees ring entries, so once per
    * step the owned bytes are compared with a shadow and every changed lane
    * is pushed as a pair (next-position value, like any committed lane). */
  void publish_image_owned();
  /** Compact transport: the lanes the model writes straight into the record
    * (image-owned, see reserve_image_owned) have no commit path.  Find the
    * ones that changed since the last call, refresh their lane cells and
    * list them as changes, so the writer's change list and the base image
    * (materialize_record) carry them.  The first call seeds every owned
    * cell from the record. */
  void sync_owned_changes();
  ExportRing* export_ring() const { return ring_; }
  /** Image transport: the record image is the only destination.  Every
    * moved value is masked into record_ where it is found (no lane cells,
    * no change list); the writer copies the whole image per cycle. */
  /** The record is the model's contract image: every lane is written in
    * place (samplers through commit_lane, the core directly).  The delta
    * transport's lane cells are gone, so image mode is the only mode. */
  void set_image_mode(bool on) {

    (void)on;

    image_mode_ = true;
  }
  bool image_mode() const { return image_mode_; }
  bool native_image_enabled() const {

    return false;

  }

  /** Sampled slot store.  The hot path compares the raw value against the
    * slot's u64 shadow (one aligned load, a well-predicted branch: ~95% of
    * the ~2,000 stores per cycle find the value unchanged); only a moved
    * value is masked, written into the record and listed.  Comparing
    * against the record's own bytes instead stalls on store forwarding
    * (measured +750 ns/cycle), and routing the compare through per-lane
    * tables costs two extra dependent loads per stream (+900). */
  void store_slot(std::size_t slot, uint64_t value) {

    uint64_t& held = slot_values_[slot];
    if (held == value) return;
    held = value;
    commit_lane(lane_of_slot_[slot], value);
  }
  // A branch-free variant (unconditional shadow store + pending-slot list,
  // count advanced by the change flag) was measured at +850 ns/cycle: the
  // ~2,000 extra stores per cycle cost more than the ~107 mispredicts
  // they remove.  Keep the branch.
  /** Store for lanes without a slot (test records). */
  void store_lane(std::uint16_t lane, uint64_t value) {
    commit_lane(lane, value);
  }
  /** Predict-bound lanes are evaluated after the step (their cycle-t value
    * is the post-step-t state) while the sampled lanes for cycle t+1 are
    * already accumulating in the main list, so they keep a list of their
    * own that the writer appends to position t. */
  void store_lane_predicted(std::uint16_t lane, uint64_t value) {
    if (lane >= kOracleRecordLanes) return;
    const uint64_t masked = apply_bits(value, lane_bits_[lane]);

    if (ring_ != nullptr) {
      // The worker holds the lane values: it drops the unchanged ones.
      ring_->push_predicted(lane, masked, lane_bits_[lane]);
      return;
    }
    if (image_mode_) {
      // Row/change transports ship a predicted lane only when it moved
      // (list_predicted_); the whole-image transport just stores it.
      if (list_predicted_) {
        if (record_.load(lane) == masked) return;
        record_.store(lane, masked);
        if (predicted_count_ < kPredictedCapacity) predicted_lanes_[predicted_count_++] = lane;
        return;
      }
      record_.store(lane, value);
      return;
    }
    if (lane_cell_[lane].value == masked) return;
    lane_cell_[lane].value = masked;
    record_.store(lane, masked);
    if (predicted_count_ < kPredictedCapacity) predicted_lanes_[predicted_count_++] = lane;
  }
  /** Whether store_lane_predicted lists moved lanes (predicted_changes())
    * in image mode; the writer turns it on for every transport that ships
    * changes rather than whole images. */
  void set_list_predicted(bool on) { list_predicted_ = on; }
  /** kOracleRecordLanes-sized value/mask tables as plain arrays, so the
    * inlined commit addresses them directly. */
  const std::uint16_t* predicted_changes() const { return predicted_lanes_; }
  std::size_t predicted_change_count() const { return predicted_count_; }
  void seal_predicted() { predicted_count_ = 0; }
  /** A moved value: mask it, keep it as the lane's value, list the lane
    * (scratch slots map to the pad lane and are dropped).  The record
    * image itself is only materialized when the writer needs it
    * (materialize_record()), so a change costs two stores here. */
  void commit_lane(std::uint16_t lane, uint64_t value) {
    if (lane >= kOracleRecordLanes) return;
    if (verify_mode_) {

      return;
    }

    if (ring_ != nullptr) {  // export offload: the worker keeps the image
      ring_->push_pair(lane, apply_bits(value, lane_bits_[lane]), lane_bits_[lane]);
      return;
    }
    if (image_mode_) {
      record_.store(lane, value);  // width-masked, branch-free
      return;
    }
    // The record image is rebuilt from the lane cells once per window by the
    // writer (materialize_record): at W16/W32 that is cheaper than a masked
    // store per change here (the W4 bench pays more, which is a bench
    // artifact).
    lane_cell_[lane].value = apply_bits(value, lane_bits_[lane]);
    changed_lanes_[change_count_] = lane;
    change_count_ += change_count_ < kChangeCapacity;
  }
  /** Write every lane's value into the record image (only needed when the
    * record was reset behind the lanes' back; commit_lane keeps it current). */
  void materialize_record() {
    if (image_mode_) return;  // the image is always current
    for (std::size_t lane = 0; lane < kOracleRecordLanes; ++lane)
      record_.store(static_cast<std::uint16_t>(lane), lane_cell_[lane].value);
  }
  /** Masked value of a lane as last stored (for the writer's list). */
  uint64_t lane_value(std::uint16_t lane) const {
    return image_mode_ ? record_.load(lane) : lane_cell_[lane].value;
  }
  /** Per lane: the committed value and, in the same cache line, where the
    * consumer keeps this lane's elements (byte offset of its 2W elements
    * in the expansion buffer, element width) -- set once by the writer, so
    * the change entries carry the destination and the consumer needs no
    * per-lane table. */
  struct LaneCell {
    uint64_t value = 0;
    uint32_t offset = 0;
    uint8_t bytes = 0;
    uint8_t pad[3] = {};
  };
  LaneCell& lane_cell(std::uint16_t lane) { return lane_cell_[lane]; }
  const LaneCell& lane_cell(std::uint16_t lane) const { return lane_cell_[lane]; }

  /** Evaluate every cycle-start accessor into the record before any
    * component advances.  Target phase is recorded independently in each
    * binding. */
  void sample_bound_streams(const SystemGuider& model) {
    if (attached_ != &model) attach(model);
    // Values the placed batches and gathers stored during the previous
    // step (their stores have long retired): find what moved, commit it,
    // and re-evaluate the exact-dependency expressions it woke.
    ++stamp_;
    if (!native_image_enabled()) { diff_slots(); diff_unified(); }
    if (!unify_check_fields_.empty()) verify_unify_assumption(stat_diff_cycles_);
    run_due_streams(model);
    if (!constants_armed_) {
      for (const auto& [slot, value] : deferred_constants_)
        store_slot(static_cast<std::size_t>(slot), value);
      constants_armed_ = true;
    }
    for (const IndividualSampler& sampler : individual_samplers_)
      store_slot(sampler.slot, sampler.fn(model));
    for (IndexedSamplerGroup& group : indexed_sampler_groups_) {
      // An idle source cannot have changed its oracle value this edge, so the
      // last-sampled values already in the record are correct: skip the
      // re-sample.  All entries of a group share one predicate, so it is
      // evaluated once per cycle instead of once per stream.
      if (group.epoch != nullptr) {
        const uint64_t epoch = group.epoch(model);
        if (group.epoch_valid && epoch == group.last_epoch) continue;
        group.last_epoch = epoch;
        group.epoch_valid = true;
      } else if (group.idle && group.idle(model)) {
        continue;
      }

      for (const IndexedEntry& entry : group.entries)
        store_slot(entry.slot, group.fn(model, entry.index));
    }
    run_placement(SamplePlacement::PreStep, model);
  }

  // Native wide bindings reserve their already-written image lanes. When
  // no accessor/scan work exists, PreStep does not read another owner's
  // mutable state. Check the actual registered tables, not a configuration
  // name, so added samplers automatically retain the conservative join.
  bool prestep_is_owner_local(const SystemGuider& model) const {
    const auto& table=tables_[static_cast<std::size_t>(SamplePlacement::PreStep)];
    return attached_==&model && image_mode_ && ring_==nullptr && constants_armed_ &&
        !check_mode_ && !verify_mode_ && gathered_lines_==0 && unified_row_src_.empty() &&
        unify_check_fields_.empty() && individual_samplers_.empty() && indexed_sampler_groups_.empty() &&
        evaluators_.empty() && batches_.empty() && due_streams_.empty() && due_batches_.empty() &&
        phase_prepare_[static_cast<std::size_t>(SamplePlacement::PreStep)]==nullptr &&
        phase_prepare_[static_cast<std::size_t>(SamplePlacement::Frontend)]==nullptr &&
        table.groups.empty() && table.chunks.empty() && table.probe_chunks.empty() &&
        table.always_direct.empty() && table.always_due.empty() && table.legacy.empty();
  }

  /** Run one placement (called by the guider right after the
    * corresponding component commits): scan the watched lines, run the
    * evaluators they woke, then the always-on evaluators and the batches
    * without a watch declaration. */
  void sample_placed(SamplePlacement placement, const SystemGuider& model) {
    g_oracle_prefetch_cursor.drain_slice();  // write-ahead prefetch slice (SYSMODEL_IMAGE_PREFETCH)
    run_placement(placement, model);
  }
  /** Sampling was switched off for a stretch of cycles (an ROI warm-up) and
    * is on again. The placed batches gather only when their component
    * commits and the expression slots only when a watched line moves, so
    * nothing refreshed them during the gap: the record would show the
    * values from the switch-off for one cycle (the strict qualification
    * reads exactly that cycle). Re-run every placement now, un-primed so
    * each evaluator runs once; the next cycle-start diff then commits every
    * lane that moved during the gap. */
  void resample_after_gap(const SystemGuider& model) {
    if (attached_ != &model) attach(model);

    for (PlacementTable& t : tables_) t.primed = false;
    run_placement(SamplePlacement::Core, model);
    run_placement(SamplePlacement::Frontend, model);
    run_placement(SamplePlacement::Memory, model);
    run_placement(SamplePlacement::End, model);
  }
  void run_placement(SamplePlacement placement, const SystemGuider& model) {
    if (attached_ != &model) attach(model);
    if (const auto prepare=phase_prepare_[static_cast<std::size_t>(placement)]) prepare(model);

    PlacementTable& t = tables_[static_cast<std::size_t>(placement)];
    // Nothing placed here (the wide model publishes through its own write
    // points): skip the scan machinery.  This also keeps a placement run on
    // another thread (the frontend worker) away from the shared tables.
    if (t.groups.empty() && t.chunks.empty() && t.probe_chunks.empty() && t.always_direct.empty() &&
        t.always_due.empty() && t.legacy.empty() && due_batches_.empty() && !check_mode_)
      return;
    ++stamp_;
    if (placement == SamplePlacement::PreStep

    )
      gather_immediate(t);
    else
      gather(t);
    if (!t.primed) {
      // First pass: every evaluator of this placement runs once, so slots
      // whose inputs start at zero (or have no region) are still filled.
      t.primed = true;
      for (std::size_t e = 0; e < evaluators_.size(); ++e)
        if (evaluators_[e].placement == placement) t.pending.push_back(static_cast<uint32_t>(e));
      for (uint32_t e : t.pending) evaluators_[e].stamp = stamp_;
    }
    scan(t);
    t.stat_evals += t.pending.size();
    for (uint32_t e : t.pending) {
      ++evaluators_[e].wakes;
      mark_due(e, model);
    }
    t.pending.clear();
    if (++t.window_cycles >= kAdaptWindow) adapt(placement, t);
    // Always-on evaluators: their due bits are a constant per batch.
    for (const PlacementTable::AlwaysDue& a : t.always_due) due_bits_[a.batch * kDueWords] |= a.bits;
    for (uint32_t e : t.always_direct) run_evaluator(e, model);
    if (!t.always_due.empty() || !due_batches_.empty()) {
      dispatch_[static_cast<std::size_t>(placement)](model, *this);
      for (const PlacementTable::AlwaysDue& a : t.always_due) due_bits_[a.batch * kDueWords] = 0;
      clear_due_batches();
    }
    for (const Batch* batch : t.legacy)
      batch->fn(model, slots_of(*batch));
    if (check_mode_) verify_batches(model, placement, verify_cycle_, "same placement");
  }
  void set_verify_cycle(unsigned long long cycle) { verify_cycle_ = cycle; }

  /** Self-check (SYSMODEL_SAMPLE_CHECK): re-evaluate every batch in full
    * against a scratch copy of its shadow and compare with the lane
    * values.  At the cycle start for the placed batches ("early
    * placement": a value that differs means the batch sampled its
    * component too early last step); right after each placement for that
    * placement's batches ("same placement": a watched field or region
    * that was missed).  Reports the lane and aborts. */
  void verify_placed(const SystemGuider& model, unsigned long long cycle) {
    if (attached_ != &model) attach(model);
    // The gathered fields of the previous step are committed by the
    // cycle-start diff; run it first so the slot view is current.
    ++stamp_;
    diff_slots();
    diff_unified();
    run_due_streams(model);
    verify_batches(model, SamplePlacement::PreStep, cycle, "early placement", true);
  }
  void verify_batches(const SystemGuider& model, SamplePlacement placement,
                      unsigned long long cycle, const char* when,
                      bool all_but_placement = false) {
    if (attached_ != &model) attach(model);
    verify_mode_ = true;
    verify_when_ = when;
    for (std::size_t b = 0; b < batches_.size(); ++b) {
      const Batch& batch = batches_[b];
      if (all_but_placement ? batch.placement == placement
                            : batch.placement != placement)
        continue;
      std::size_t end = shadow_slots_.size();
      for (const Batch& other : batches_)
        if (other.base > batch.base && static_cast<std::size_t>(other.base) < end)
          end = static_cast<std::size_t>(other.base);
      (void)end;
      const std::size_t count = slot_count();
      // The current view: gathered fields as staged, everything else as
      // stored.  The batch's full run then only differs where it disagrees.
      verify_scratch_.resize(count - static_cast<std::size_t>(batch.base));
      for (std::size_t k = 0; k + batch.base < count; ++k) {
        const std::size_t slot = k + static_cast<std::size_t>(batch.base);

        const int32_t gi = slot_gather_index_[slot];
        verify_scratch_[k] =
            gi >= kUnifiedGatherBase
                ? unified_staged_value(gi)
                : (gi >= 0 && !immediate_placed_gather()
                       ? gathered_[static_cast<std::size_t>(gi)]
                       : slot_values_[slot]);
      }
      verify_batch_ = b;
      batch.fn(model, BatchSlots{verify_scratch_.data(),
                                 lane_of_slot_.data() + batch.base, true, nullptr, this});
      for (std::size_t k = 0; k + batch.base < count; ++k) {
        const std::size_t slot = k + static_cast<std::size_t>(batch.base);
        const std::uint16_t lane = lane_of_slot_[slot];
        if (lane >= kOracleRecordLanes) continue;

        // Exact-dependency streams are refreshed at the next cycle start
        // (the early-placement check covers them); at their own placement
        // they still hold the previous cycle's value by design.
        if (!all_but_placement && slot < slot_exact_.size() && slot_exact_[slot]) continue;
        const uint64_t mask = bits_mask(lane_bits_[lane]);
        // A gathered field's value sits in the gathered array until the
        // next cycle-start diff commits it; compare against that.
        const int32_t gi = slot_gather_index_[slot];
        const uint64_t sampled =

            gi >= kUnifiedGatherBase
                ? unified_staged_value(gi)
                : (gi >= 0 && !immediate_placed_gather()
                       ? gathered_[static_cast<std::size_t>(gi)]
                       : slot_values_[slot]);
        if ((verify_scratch_[k] & mask) == (sampled & mask)) continue;
        if (verify_failures_++ < 16)
          std::fprintf(stderr,
                       "[SAMPLE-CHECK] lane %u slot %zu (%s batch %zu, %s) sampled=0x%llx full=0x%llx\n",
                       unsigned(lane), slot, placement_name(batch.placement), b, when,
                       (unsigned long long)(sampled & mask),
                       (unsigned long long)(verify_scratch_[k] & mask));
      }
    }
    verify_mode_ = false;
    if (verify_failures_ != 0) {
      std::fprintf(stderr, "[SAMPLE-CHECK c%llu] %zu stale sample(s) (%s)\n",
                   cycle, verify_failures_, when);
      std::abort();
    }
  }
  const char* placement_name(SamplePlacement p) const {
    switch (p) {
      case SamplePlacement::PreStep: return "PreStep";
      case SamplePlacement::Core: return "Core";
      case SamplePlacement::Frontend: return "Frontend";
      case SamplePlacement::Memory: return "Memory";
      default: return "End";
    }
  }

  /** Snapshot of the record as published for this cycle (probes read it:
    * the live record already moves on to the next cycle during the step). */
  void publish_record() {
    materialize_record();
    std::memcpy(published_.bytes, record_.bytes, kOracleRecordPaddedBytes);
  }
  const OracleRecord& published_record() const { return published_; }

  /** Base of the slot shadow array (a batch's `values` pointer is this
    * plus its base slot). */
  const uint64_t* slot_values_base() const { return slot_values_; }
  uint64_t sampled_value(std::size_t slot) const {
    const std::uint16_t lane = lane_of_slot_[slot];
    if (lane >= kOracleRecordLanes) return 0;
    return image_mode_ ? record_.load(lane) : lane_cell_[lane].value;
  }
  std::size_t slot_count() const { return lane_of_slot_.size(); }
  /** A family's duplicate key (two manifest keys for one value): when the
    * primary slot is a gathered field, the duplicate is gathered from the
    * same address; else the batch copies it after computing the primary. */
  void add_slot_alias(int primary_slot, int dup_slot) {
    slot_aliases_.emplace_back(primary_slot, dup_slot);
  }
  bool slot_is_gathered(int slot) const {
    return slot >= 0 && static_cast<std::size_t>(slot) < slot_gather_index_.size() &&
           slot_gather_index_[static_cast<std::size_t>(slot)] >= 0;
  }
  /** The per-cycle oracle image every sampled and predicted lane lands in;
    * the writer exports it and the probes read it. */
  const OracleRecord& record() const { return record_; }
  OracleRecord& record() { return record_; }
  int lane_of_slot(int slot) const {
    return slot < 0 || static_cast<std::size_t>(slot) >= lane_of_slot_.size()
               ? -1 : static_cast<int>(lane_of_slot_[static_cast<std::size_t>(slot)]);
  }
  const std::uint16_t* lane_of_slot_table() const { return lane_of_slot_.data(); }
  /** Manifest lane (== kSystemProbeManifest row) of a trace key, or
    * kOracleRecordPadLane when the manifest does not select it. */
  static std::uint16_t lane_for_key(const char* trace_key);
  /** Predict-bound streams (PostStepCycle / PostStepRegisterSnapshot) with
    * their record lanes, for the writer's post-step publication. */
  struct PredictedLane {
    PredictFn predict;
    std::uint16_t lane;
    bool memory_side;   // read from the memory side's post-edge state (the D-cache)
  };
  const std::vector<PredictedLane>& predicted_lanes() {
    if (!predicted_built_) build_predicted_lanes();
    return predicted_;
  }

  /** Slots claimed by either constant-reservation API: their value never
    * changes after the first sample call, so writers may prefill trace lanes
    * once instead of storing them every element. */
  bool slot_is_constant(int slot) const {
    for (const auto& [s, v] : deferred_constants_)
      if (s == slot) return true;
    return false;
  }
  uint64_t constant_slot_value(int slot) const {
    for (const auto& [s, v] : deferred_constants_)
      if (s == slot) return v;
    return 0;
  }

  const ModelBinding* find(const std::string& trace_key) const {
    auto found = bindings_.find(trace_key);
    return found == bindings_.end() ? nullptr : &found->second;
  }

  std::size_t size() const { return bindings_.size(); }

  /** Keys that were bound but never registered, i.e. the model claims to
    * predict something this manifest does not select. Non-empty means the
    * bindings and the manifest have drifted and the model is being checked
    * against a stale contract. */
  const std::vector<std::string>& unclaimed() const { return unclaimed_; }
  void note_registered(const std::string& trace_key) {
    registered_.insert(trace_key);
  }
  void finalize();

 private:
  ModelBindings() {
    for (std::size_t lane = 0; lane < kOracleRecordLanes; ++lane)
      lane_bits_[lane] = static_cast<uint8_t>(
          mask_bits(kOracleRecordWidthMask[kOracleRecordLane[lane].width]));
  }
  /** Lane widths as bit counts (2 KB, L1-resident) instead of 64-bit
    * masks (16 KB): the commit path masks with one bzhi. */
  static unsigned mask_bits(uint64_t mask) {
    return mask == 0 ? 0u : 64u - static_cast<unsigned>(__builtin_clzll(mask));
  }
  static uint64_t bits_mask(unsigned bits) {
    return bits >= 64 ? ~UINT64_C(0) : (UINT64_C(1) << bits) - 1;
  }
  static uint64_t apply_bits(uint64_t value, unsigned bits) {
#if defined(__BMI2__)
    return _bzhi_u64(value, bits);  // bits >= 64 leaves value unchanged
#else
    return value & bits_mask(bits);
#endif
  }
  void build_predicted_lanes();
  std::unordered_map<std::string, ModelBinding> bindings_;
  std::unordered_set<std::string> registered_;
  std::vector<std::string> unclaimed_;
  // Slots are registration indices (contiguous per batch); lane_of_slot_
  // maps every slot to its manifest lane, and every sampled value is stored
  // masked at that lane of record_.
  OracleRecord record_{};
  std::vector<std::uint16_t> lane_of_slot_;
  std::vector<uint64_t> shadow_slots_;  // raw sampled value per slot
  // Per-lane masked value as last stored (writer's list) and width mask.
  LaneCell lane_cell_[kOracleRecordLanes] = {};
  uint8_t lane_bits_[kOracleRecordLanes] = {};
  std::uint16_t changed_lanes_[kChangeCapacity + 1] = {};
  std::size_t change_count_ = 0;
  std::uint16_t predicted_lanes_[kPredictedCapacity] = {};
  std::size_t predicted_count_ = 0;
  std::vector<std::pair<int, uint64_t>> deferred_constants_;
  bool constants_armed_ = false;
  std::vector<PredictedLane> predicted_;
  bool predicted_built_ = false;
  struct IndividualSampler {
    SampleFn fn;
    std::size_t slot;
  };
  std::vector<IndividualSampler> individual_samplers_;
  struct IndexedEntry {
    uint32_t slot;
    uint32_t index;
  };
  struct IndexedSamplerGroup {
    IndexedSampleFn fn;
    IdlePredicate idle = nullptr;  // when true, group is idle: reuse last values
    SampleEpochFn epoch = nullptr;  // unchanged token => reuse last values
    uint64_t last_epoch = 0;
    bool epoch_valid = false;
    std::vector<IndexedEntry> entries;

  };
  std::vector<IndexedSamplerGroup> indexed_sampler_groups_;
  struct Batch {
    BatchSampleFn fn;
    int base;
    SamplePlacement placement;
    WatchFn watch;
    bool check_only;  // every slot is covered by fields / per-slot evaluators
    int evaluator;    // the batch's own evaluator, once a watch names it
    int next_ordinal = 0;  // due-bit allocator for the static dispatcher
    const char* name = "";  // set by the watch declaration (diagnostics)
  };
  std::vector<Batch> batches_;
  OracleRecord published_{};
  bool verify_mode_ = false;
  std::size_t verify_batch_ = 0;
  std::size_t verify_failures_ = 0;
  std::vector<uint64_t> verify_scratch_;
  const char* verify_when_ = "";
  unsigned long long verify_cycle_ = 0;
  bool check_mode_ = false;

  friend class WatchSink;
  BatchSlots slots_of(const Batch& batch) {
    return slots_at(batch.base);
  }
  BatchSlots slots_at(int base) {
    return BatchSlots{slot_values_ ? slot_values_ + base : nullptr,
                      lane_of_slot_.data() + base, false,
                      slot_gather_index_.data() + base, this

    };
  }

  std::vector<std::pair<int, int>> slot_aliases_;
  struct Evaluator {
    BatchSampleFn fn;
    int base;
    SamplePlacement placement;
    uint32_t stamp;
    bool always;
    int slot;  // >= 0: a per-slot fallback evaluator for that batch slot
    uint32_t wakes = 0;       // times woken in the current adaptation window
    uint32_t probe_hits = 0;  // unused (probing removed)
    uint32_t lines = 0;       // distinct region lines this evaluator watches
    bool probe = false;       // unused (probing removed)
    bool forced = false;      // a dependency cannot be watched: always-on for good
    int batch = -1;           // owning batch (index into batches_)
    int ordinal = -1;         // bit in the batch's due word; -1: runtime-dispatched
    bool exact = false;       // woken by moves of its gathered inputs
    uint32_t stores = 1;      // stores per run (generator estimate): gating policy
    uint64_t cost = 0;        // SYSMODEL_EVAL_COST: TSC ticks spent in fn
    uint64_t runs = 0;        // SYSMODEL_EVAL_COST: times fn ran
    const char* why = "";     // first reason it was forced always-on
    std::size_t why_bytes = 0;  // size of the oversize region, when that is the reason
  };
  /** Promotion threshold of an evaluator: gating pays while
    *   ratio * (run + wake) + lines * scan  <  run,
    * so it is promoted once its wake ratio exceeds
    *   1 - lines * scan / (run + wake),  run = stores * kStoreTicks. */
  static constexpr double kScanTicks = 4.0;
  static constexpr double kStoreTicks = 5.0;
  static constexpr double kWakeTicks = 30.0;
  static double promote_threshold(const Evaluator& e) {
    const double run = double(e.stores) * kStoreTicks;
    const double thr = 1.0 - double(e.lines) * kScanTicks / (run + kWakeTicks);
    // <= 0: scanning its lines costs more than running it, whatever the
    // wake ratio (promoted at the first window even if it never woke).
    return thr < 0.0 ? 0.0 : (thr > 0.95 ? 0.95 : thr);
  }
  /** SYSMODEL_EVAL_COST=1: every evaluator runs through run_evaluator()
    * (no static dispatch) and is timed, for report_watch_activity(). */
  bool cost_mode_ = false;
  ExportRing* ring_ = nullptr;  // export offload (set by ExportThread)
  // image-owned lanes: registration order, merged byte ranges of the record,
  // byte -> lane map and the shadow the per-step diff runs against
  std::vector<std::uint16_t> owned_lanes_;
  std::vector<std::pair<std::uint32_t, std::uint32_t>> owned_ranges_;
  std::vector<std::uint16_t> owned_lane_at_byte_;
  std::vector<unsigned char> owned_shadow_;
  std::uint32_t owned_span_lo_ = 0, owned_span_hi_ = 0;  // sync_owned_changes scan span
  void snapshot_image_owned();
  bool image_mode_ = true;      // the record is the model image (see set_image_mode)
  bool list_predicted_ = false;  // see set_list_predicted
  struct InputBuild {
    const unsigned char* addr;
    uint8_t bytes;
    bool is_signed;
    uint32_t evaluator;
  };
  std::vector<InputBuild> input_builds_;
  // Inverted index: gathered entry -> exact evaluators depending on it.
  std::vector<uint32_t> dep_first_, dep_list_;
  std::vector<uint32_t> due_streams_;
  PhasePrepareFn phase_prepare_[5] = {};
  DispatchFn dispatch_[5] = {};
  DispatchFn exact_dispatch_ = nullptr;
  static constexpr std::size_t kDueWords = 4;  // 256 ordinals per batch
  std::vector<uint64_t> due_bits_;  // per batch, kDueWords words
  std::vector<int> due_batches_;
  /** Adaptation: after this many cycles at a placement, evaluators woken
    * in more than kAdaptWakeRatio of them stop being watched (their
    * regions move nearly every cycle; scanning them only adds cost). */
  static constexpr uint32_t kAdaptWindow = 65536;
  /** Per-cycle wake ratio above which a gated evaluator runs every cycle
    * (promote-only: deterministic, no flip-flopping between windows). */
  static constexpr double kAdaptWakeRatio = 0.5;
  /** Evaluators watching at most this many lines are never promoted: the
    * scan of one or two hot lines costs less than any evaluation, and this
    * keeps the cold groups (one version word each) gated through a busy
    * boot phase. */
  static constexpr std::size_t kNeverPromoteLines = 2;
  // Probing / demotion of always-on evaluators was tried and removed: the
  // sampled wake ratio and the exact one disagree for evaluators near the
  // threshold, and the two flip each other every window.
  static constexpr std::size_t kAdaptProbeLines = 0;
  static constexpr uint32_t kProbeEvery = 16;
  struct FieldBuild {
    const unsigned char* addr;
    uint32_t slot;
    uint8_t bytes;
    bool is_signed;
    SamplePlacement placement;
  };
  struct RegionBuild {
    const unsigned char* addr;
    std::size_t bytes;
    uint32_t evaluator;
    const char* what;  // "prefix <- chain" from the watch declaration
    uint64_t value_mask = UINT64_MAX;
  };
  /** SYSMODEL_WATCH_PROFILE=1: nothing is promoted, every region line is
    * scanned all run long, and the exit report lists how often each
    * declared chain's lines moved (input of the generator's hot-chain
    * grouping). */
  bool profile_mode_ = false;
  /** Fields of one (width, signedness) class: gathered with one plain
    * loop each -- a load and a store per field, no compare, no branch. */
  struct GatherGroup {
    uint8_t bytes;
    bool is_signed;
    std::vector<const unsigned char*> addrs;
    std::vector<uint32_t> slots;
    std::size_t first = 0;  // index of this group's first entry in gathered_
  };
  struct Chunk {
    const unsigned char* src;
    uint32_t first_eval, eval_count;
  };
#if defined(CHISA_WIDE_MODEL)
  static constexpr bool kPreciseDependencyBytes = true;
#else
  static constexpr bool kPreciseDependencyBytes = false;
#endif
  struct PlacementTable {
    std::vector<Chunk> chunks;        // lines gating at least one evaluator
    std::vector<Chunk> probe_chunks;  // lines only probing always-on ones
    std::vector<uint32_t> probe_evals;
    std::vector<unsigned char> probe_shadow_storage;
    unsigned char* probe_shadow = nullptr;
    std::vector<GatherGroup> groups;
    std::size_t field_count = 0;
    std::vector<uint32_t> evals;
    std::vector<uint64_t> eval_byte_masks, claimed_bytes, changed_bytes;
    std::vector<uint64_t> eval_word_masks;
    std::vector<uint8_t> eval_words;
    std::vector<unsigned char> shadow_storage;
    unsigned char* shadow = nullptr;
    std::vector<uint32_t> always_evals;
    struct AlwaysDue { std::size_t batch; uint64_t bits; };
    std::vector<AlwaysDue> always_due;      // static-dispatched always-on ones
    std::vector<uint32_t> always_direct;    // always-on without a static call site
    std::vector<uint32_t> pending;
    std::vector<const Batch*> legacy;
    uint32_t window_cycles = 0;
    std::vector<uint64_t> chunk_moves;     // stats mode only: moves per line
    std::vector<uint8_t> line_moved;       // per line, this scan
    std::vector<uint32_t> moved;           // lines that moved, this scan
    bool primed = false;
    uint64_t stat_cycles = 0, stat_moved = 0, stat_evals = 0;
  };
  template <class T>
  static T* align64(T* p) {
    const std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(p);
    return reinterpret_cast<T*>((raw + 63) & ~std::uintptr_t{63});
  }
  // The slot array proper (values as the batches / gathers store them),
  // its committed image, and the diff's scratch lists.  shadow_slots_ is
  // only the registration-time size record; attach() sizes these.
  std::vector<uint64_t> slot_storage_;
  uint64_t* slot_values_ = nullptr;
  // Compact array of the placed gathered fields and its committed image.
  std::vector<uint64_t> gathered_storage_, gathered_prev_storage_;
  uint64_t* gathered_ = nullptr;
  uint64_t* gathered_prev_ = nullptr;
  std::size_t gathered_lines_ = 0;
  std::vector<uint32_t> gathered_slot_;
  std::vector<int32_t> slot_gather_index_;  // slot -> gathered index, or -1
  std::vector<bool> slot_exact_;            // slot -> computed by an exact-dependency stream
  std::vector<uint8_t> slot_masks_;
  std::vector<uint32_t> slot_moved_, slot_changed_;
  uint64_t stat_diff_cycles_ = 0, stat_diff_moved_ = 0, stat_diff_changed_ = 0, stat_diff_streams_ = 0;
  const SystemGuider* attached_ = nullptr;
  std::vector<Evaluator> evaluators_;
  std::vector<FieldBuild> field_builds_;
  std::vector<RegionBuild> region_builds_;
  PlacementTable tables_[5];
  uint32_t stamp_ = 0;

  // ---- Unified storage regions ------------------------------------
  struct UnifyBuild {
    const unsigned char* base;
    std::size_t bytes;
    const char* name;
  };
  struct UnifiedField {
    const unsigned char* addr;
    uint32_t slot;
    uint16_t lane;    // lane_of_slot_ resolved at build time
    uint8_t bits;     // lane_bits_ resolved at build time
    uint8_t bytes;
    uint8_t shift;    // 64 - 8*bytes
    bool is_signed;
    bool tail;        // an 8-byte load at addr would cross the region end
    uint8_t rec_mask; // image mode: the lane's byte mask in the record
    uint16_t rec_off; // image mode: the lane's byte offset in the record
  };
  /** Build-time view of one region; the runtime tables are the dense
    * per-claimed-row arrays below (one streaming loop over every claimed
    * row of every region, shadow and masks stored compactly so the diff
    * touches only claimed lines). */
  struct UnifiedRegion {
    const unsigned char* rows_base = nullptr;  // 64-byte aligned start
    std::size_t rows = 0;
    const char* name = "";
    std::vector<uint64_t> claimed;        // per-row claimed-byte mask
    std::vector<uint16_t> byte_field;     // rows*64 -> flat field index
    std::size_t field_count = 0;
  };
  std::vector<UnifyBuild> unify_builds_;
  std::vector<UnifiedRegion> unified_;
  std::vector<UnifiedField> unified_flat_;    // by slot_gather_index_ sentinel
  std::vector<const unsigned char*> unified_row_src_;  // dense claimed rows
  std::vector<uint64_t> unified_row_claimed_;          // dense masks
  std::vector<uint16_t> unified_row_byte_field_;       // dense rows*64
  std::vector<unsigned char> unified_shadow_storage_;
  unsigned char* unified_shadow_ = nullptr;            // dense rows*64
  std::vector<uint64_t> unified_masks_;                // pass-1 scratch
  std::vector<uint32_t> unified_moved_;                // pass-1 scratch
  /** Image mode: a row's fields as a contiguous descriptor run, so a
    * moved row reads one or two metadata lines instead of one scattered
    * 24-byte entry per field.  `fmask` selects the field's bytes inside
    * this row (a crossing field is listed under both rows). */
  struct RowField {
    uint64_t fmask;
    int8_t off;        // field start relative to the row start (may be < 0)
    uint8_t bytes;
    uint8_t shift;
    uint8_t is_signed;
    uint8_t tail;      // an 8-byte load at the field would cross the region end
    uint8_t bits;
    uint16_t rec_off;
    uint8_t rec_mask;
    uint8_t pad[3] = {};
    uint32_t slot;
  };
  static_assert(sizeof(RowField) == 24, "RowField is three per line");
  std::vector<uint32_t> unified_row_field_first_;      // image mode: rows+1
  std::vector<RowField> unified_row_fields_;           // image mode: per row
  std::vector<FieldBuild> unify_check_fields_;  // SYSMODEL_UNIFY_CHECK=1
  uint64_t stat_unified_rows_moved_ = 0, stat_unified_commits_ = 0;
  uint64_t stat_unified_pass1_tsc_ = 0, stat_unified_pass2_tsc_ = 0;  // CHISA_PHASE_TIMERS
  static constexpr int32_t kUnifiedGatherBase = 1 << 28;

  static uint64_t extend_field(const unsigned char* addr, uint8_t bytes,
                               bool is_signed) {
    uint64_t v = 0;
    std::memcpy(&v, addr, bytes);
    if (!is_signed) return v;
    switch (bytes) {
      case 1: return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int8_t>(v)));
      case 2: return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int16_t>(v)));
      case 4: return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(v)));
      default: return v;
    }
  }
  uint64_t unified_staged_value(int32_t gi) const {
    const UnifiedField& f =
        unified_flat_[static_cast<std::size_t>(gi - kUnifiedGatherBase)];
    return extend_field(f.addr, f.bytes, f.is_signed);
  }

  /** Line-compare every unified region against its shadow and commit the
    * fields under moved bytes.  Runs with diff_slots at the cycle start;
    * a claimed field's commit therefore lands at the same position the
    * deferred gather path gave it. */
  static uint64_t bits_below(unsigned k) {  // k in [0, 64]
#if defined(__BMI2__)
    return _bzhi_u64(~UINT64_C(0), k);
#else
    return k >= 64 ? ~UINT64_C(0) : (UINT64_C(1) << k) - 1;
#endif
  }
  void diff_unified() {
    const std::size_t n = unified_row_src_.size();
    if (n == 0 || verify_mode_) return;
    const unsigned char* const* src = unified_row_src_.data();
    const uint64_t* claimed = unified_row_claimed_.data();
    unsigned char* shadow = unified_shadow_;
    uint64_t* masks = unified_masks_.data();
    uint32_t* moved = unified_moved_.data();
#ifdef CHISA_PHASE_TIMERS
    const uint64_t pass1_t0 = __rdtsc();
#endif
    // Pass 1: streaming scan, fixed-address stores only (same structure as
    // diff_slots): one scattered model-row load per claimed row, everything
    // else dense.
    std::size_t cnt = 0;
    for (std::size_t i = 0; i < n; ++i) {
      // The row pointers are dense, the rows they name are scattered: issue
      // the load 16 rows ahead so the misses overlap instead of serializing
      // behind the pointer chase.
#if defined(__x86_64__) || defined(__i386__)
      if (i + 16 < n) _mm_prefetch(reinterpret_cast<const char*>(src[i + 16]), _MM_HINT_T0);
#endif
#if defined(__AVX512BW__)
      const __m512i a = _mm512_loadu_si512(src[i]);
      const __m512i b = _mm512_load_si512(
          reinterpret_cast<const __m512i*>(shadow + 64 * i));
      const uint64_t m = _mm512_cmpneq_epi8_mask(a, b) & claimed[i];
#else
      uint64_t m = 0;
      for (unsigned k = 0; k < 64; ++k)
        m |= static_cast<uint64_t>(src[i][k] != shadow[64 * i + k]) << k;
      m &= claimed[i];
#endif
      masks[i] = m;
      moved[cnt] = static_cast<uint32_t>(i);
      cnt += m != 0;
    }
#ifdef CHISA_PHASE_TIMERS
    const uint64_t pass2_t0 = __rdtsc();
    stat_unified_pass1_tsc_ += pass2_t0 - pass1_t0;
    struct Pass2Timer {
      uint64_t& acc; uint64_t t0;
      ~Pass2Timer() { acc += __rdtsc() - t0; }
    } pass2_timer{stat_unified_pass2_tsc_, pass2_t0};
#endif
    if (ring_ != nullptr) {
      // Export offload: refresh the shadow and ship the moved rows; the
      // worker commits their fields against its own copy of the rows.
      for (std::size_t j = 0; j < cnt; ++j) {
        const std::size_t i = moved[j];
        std::memcpy(shadow + 64 * i, src[i], 64);
        ring_->push_row(static_cast<std::uint32_t>(i), masks[i], src[i]);
      }
      stat_unified_rows_moved_ += cnt;
      return;
    }
    if (image_mode_) {
      // Image transport: walk the moved row's contiguous descriptors, store
      // the fields under moved bytes straight into the record (no lane
      // cells, no change list, no scattered metadata).
      const uint32_t* first = unified_row_field_first_.data();
      const RowField* fields = unified_row_fields_.data();
      for (std::size_t j = 0; j < cnt; ++j) {
        const std::size_t i = moved[j];
        const unsigned char* row = src[i];
#if defined(__AVX512BW__)
        _mm512_store_si512(reinterpret_cast<__m512i*>(shadow + 64 * i),
                           _mm512_loadu_si512(row));
#else
        std::memcpy(shadow + 64 * i, row, 64);
#endif
        ++stat_unified_rows_moved_;
        const uint64_t neq = masks[i];
        const uint32_t kend = first[i + 1];
        for (uint32_t k = first[i]; k < kend; ++k) {
          const RowField& f = fields[k];
          if ((neq & f.fmask) == 0) continue;
          const unsigned char* addr = row + f.off;
          uint64_t raw;
          if (__builtin_expect(f.tail, 0)) {
            raw = 0;
            std::memcpy(&raw, addr, f.bytes);
          } else {
            std::memcpy(&raw, addr, 8);
          }
          const uint64_t shifted = raw << f.shift;
          const uint64_t v =
              f.is_signed
                  ? static_cast<uint64_t>(static_cast<int64_t>(shifted) >> f.shift)
                  : shifted >> f.shift;
          // No slot shadow for claimed fields: their batch stores are
          // skipped (gather_index), family reads go through the record
          // (family_load), and the check mode stages from model memory.
#ifdef CHISA_ORACLE_RECORD_MASKED_STORE
          _mm_mask_storeu_epi8(record_.bytes + f.rec_off,
                               static_cast<__mmask16>(f.rec_mask),
                               _mm_cvtsi64_si128(static_cast<long long>(
                                   _bzhi_u64(v, f.bits))));
#else
          record_.store(lane_of_slot_[f.slot], v);
#endif
          ++stat_unified_commits_;
        }
      }
      return;
    }
    // Pass 2: refresh the moved rows' shadow and commit their fields with a
    // branch-poor tail (pre-resolved lane/bits, shift-based extension).
    for (std::size_t j = 0; j < cnt; ++j) {
      const std::size_t i = moved[j];
#if defined(__AVX512BW__)
      _mm512_store_si512(reinterpret_cast<__m512i*>(shadow + 64 * i),
                         _mm512_loadu_si512(src[i]));
#else
      std::memcpy(shadow + 64 * i, src[i], 64);
#endif
      ++stat_unified_rows_moved_;
      uint64_t neq = masks[i];
      do {
        const unsigned b0 = static_cast<unsigned>(__builtin_ctzll(neq));
        const uint16_t fid = unified_row_byte_field_[64 * i + b0];
        const UnifiedField& f = unified_flat_[fid];
        uint64_t raw;
        if (__builtin_expect(f.tail, 0)) {
          raw = 0;
          std::memcpy(&raw, f.addr, f.bytes);
        } else {
          std::memcpy(&raw, f.addr, 8);
        }
        const uint64_t shifted = raw << f.shift;
        const uint64_t v =
            f.is_signed
                ? static_cast<uint64_t>(static_cast<int64_t>(shifted) >> f.shift)
                : shifted >> f.shift;
        slot_values_[f.slot] = v;
        lane_cell_[f.lane].value = apply_bits(v, f.bits);
        changed_lanes_[change_count_] = f.lane;
        change_count_ += change_count_ < kChangeCapacity;
        ++stat_unified_commits_;
        // Clear this field's bytes within this row (a field crossing the
        // row boundary is re-committed by the next row: harmless, the
        // change list keeps the last value).
        const std::ptrdiff_t fstart = f.addr - src[i];
        const std::ptrdiff_t lo = fstart > 0 ? fstart : 0;
        const std::ptrdiff_t hi =
            fstart + static_cast<std::ptrdiff_t>(f.bytes) < 64
                ? fstart + static_cast<std::ptrdiff_t>(f.bytes)
                : 64;
        neq &= ~(bits_below(static_cast<unsigned>(hi)) &
                 ~bits_below(static_cast<unsigned>(lo)));
      } while (neq);
    }
  }

  /** SYSMODEL_UNIFY_CHECK=1: nothing is claimed; every would-be-claimed
    * placed field is instead checked each cycle: its value in model memory
    * at the cycle start must equal what the placement gather staged during
    * the previous step.  Proves the placement-point value survives to the
    * step end, i.e. that unified diffing preserves the contract. */
  void verify_unify_assumption(unsigned long long cycle) {
    std::size_t bad = 0;
    for (const FieldBuild& f : unify_check_fields_) {
      const int32_t gi = slot_gather_index_[f.slot];
      if (gi < 0) continue;  // PreStep: immediate, same-point by design
      const uint64_t mem = extend_field(f.addr, f.bytes, f.is_signed);
      if (mem == gathered_[static_cast<std::size_t>(gi)]) continue;
      if (bad++ < 16)
        std::fprintf(stderr,
                     "[UNIFY-CHECK c%llu] slot %u lane %d (%s) staged=0x%llx memory=0x%llx\n",
                     cycle, f.slot, lane_of_slot(static_cast<int>(f.slot)),
                     placement_name(f.placement),
                     static_cast<unsigned long long>(gathered_[static_cast<std::size_t>(gi)]),
                     static_cast<unsigned long long>(mem));
    }
    if (bad != 0) {
      std::fprintf(stderr, "[UNIFY-CHECK] %zu field(s) not stable to step end\n", bad);
      std::abort();
    }
  }

  void clear_due_batches() {
    for (int b : due_batches_) {
      uint64_t* w = &due_bits_[static_cast<std::size_t>(b) * kDueWords];
      w[0] = w[1] = w[2] = w[3] = 0;
    }
    due_batches_.clear();
  }
  /** Queue an evaluator for the static dispatcher (its batch's due bit),
    * or run it directly when it has no static call site. */
  void mark_due(uint32_t id, const SystemGuider& model) {
    const Evaluator& e = evaluators_[id];
    // The generated static dispatchers are per original placement; with
    // every evaluator moved to the cycle start they are bypassed.
    if (e.ordinal < 0 || e.batch < 0 || all_prestep() ||
        dispatch_[static_cast<std::size_t>(e.placement)] == nullptr) {
      run_evaluator(id, model);
      return;
    }
    uint64_t& bits = due_bits_[static_cast<std::size_t>(e.batch) * kDueWords +
                               static_cast<std::size_t>(e.ordinal) / 64];
    if (!batch_due(e.batch)) due_batches_.push_back(e.batch);
    bits |= UINT64_C(1) << (static_cast<std::size_t>(e.ordinal) % 64);
  }
  void run_evaluator(uint32_t id, const SystemGuider& model) {
    Evaluator& e = evaluators_[id];
    // Same shape as slots_of(): batch_store commits through `owner`, so the
    // direct path (runtime-dispatched and cost-mode evaluators) must carry
    // it too.
    const BatchSlots slots{slot_values_ + e.base, lane_of_slot_.data() + e.base, false,
                           slot_gather_index_.data() + e.base, this};
    if (cost_mode_) {
      const uint64_t t0 = __rdtsc();
      e.fn(model, slots);
      e.cost += __rdtsc() - t0;
      e.runs += 1;
      return;
    }
    e.fn(model, slots);
  }
  /** Indices of the nonzero bytes of masks[0..n): eight bytes per step,
    * one iteration per nonzero byte. */
  static std::size_t collect_moved(const uint8_t* masks, std::size_t n, uint32_t* out) {
    std::size_t count = 0;
    for (std::size_t base = 0; base < n; base += 8) {
      uint64_t w;
      std::memcpy(&w, masks + base, 8);  // masks has >= 8 bytes of slack
      while (w != 0) {
        const unsigned bit = static_cast<unsigned>(__builtin_ctzll(w));
        const unsigned byte = bit >> 3;
        out[count++] = static_cast<uint32_t>(base + byte);
        w &= ~(UINT64_C(0xff) << (byte * 8));
      }
    }
    return count;
  }
  template <class T, bool kSigned>
  void gather_group(const GatherGroup& g) {
    // Into the compact gathered array (its entries are dense: index_of
    // registration order), which stays in L1; the cycle-start diff commits
    // what moved.
    const std::size_t n = g.addrs.size();
    const unsigned char* const* addrs = g.addrs.data();
    uint64_t* values = gathered_ + g.first;
    for (std::size_t i = 0; i < n; ++i) {
      T v;
      std::memcpy(&v, addrs[i], sizeof(T));
      if constexpr (kSigned)
        values[i] = static_cast<uint64_t>(static_cast<int64_t>(v));
      else
        values[i] = static_cast<uint64_t>(v);
    }
  }
  template <class T, bool kSigned>
  void gather_group_immediate(const GatherGroup& g) {
    const std::size_t n = g.addrs.size();
    for (std::size_t i = 0; i < n; ++i) {
      T v;
      std::memcpy(&v, g.addrs[i], sizeof(T));
      const uint64_t value = kSigned ? static_cast<uint64_t>(static_cast<int64_t>(v))
                                     : static_cast<uint64_t>(v);
      uint64_t& held = slot_values_[g.slots[i]];
      if (held == value) continue;
      held = value;
      commit_lane(lane_of_slot_[g.slots[i]], value);
    }
  }
  template <bool kImmediate>
  void gather_dispatch(const GatherGroup& g) {
#define CHISA_GATHER_CASE(T, S)                                           \
    if (kImmediate) gather_group_immediate<T, S>(g);                      \
    else gather_group<T, S>(g);
    switch ((g.bytes << 1) | (g.is_signed ? 1 : 0)) {
      case (1 << 1) | 0: CHISA_GATHER_CASE(uint8_t, false) break;
      case (1 << 1) | 1: CHISA_GATHER_CASE(int8_t, true) break;
      case (2 << 1) | 0: CHISA_GATHER_CASE(uint16_t, false) break;
      case (2 << 1) | 1: CHISA_GATHER_CASE(int16_t, true) break;
      case (4 << 1) | 0: CHISA_GATHER_CASE(uint32_t, false) break;
      case (4 << 1) | 1: CHISA_GATHER_CASE(int32_t, true) break;
      case (8 << 1) | 1: CHISA_GATHER_CASE(int64_t, true) break;
      default: CHISA_GATHER_CASE(uint64_t, false) break;
    }
#undef CHISA_GATHER_CASE
  }
  /** Placed fields: copy every watched field into its slot (plain loops);
    * the cycle-start diff commits the ones that moved. */
  void gather(PlacementTable& t) {
    for (const GatherGroup& g : t.groups) gather_dispatch<false>(g);
  }
  /** PreStep fields: the diff already ran this cycle, so compare at the
    * copy and commit at once. */
  void gather_immediate(PlacementTable& t) {
    for (const GatherGroup& g : t.groups) gather_dispatch<true>(g);
  }

  bool immediate_placed_gather() const {

    return false;

  }

  /** Cycle-start diff of the slot array against its committed image:
    * eight slots per 64-byte line, branch-free lists of the moved lines
    * and slots, then one commit per moved slot. */
  void diff_slots() {
    if (immediate_placed_gather()) return;
    const std::size_t lines = gathered_lines_;
    if (lines == 0) return;
    uint64_t* cur = gathered_;
    uint64_t* prev = gathered_prev_;
    uint8_t* masks = slot_masks_.data();
    // Pass 1 stores only to fixed addresses (masks[l]): a store whose
    // address depended on the previous line's compare would make the
    // loads wait for it, one line at a time.
    for (std::size_t l = 0; l < lines; ++l) {
#if defined(__AVX512BW__)
      const __m512i a = _mm512_load_si512(reinterpret_cast<const __m512i*>(cur + 8 * l));
      const __m512i b = _mm512_load_si512(reinterpret_cast<const __m512i*>(prev + 8 * l));
      masks[l] = static_cast<uint8_t>(_mm512_cmpneq_epi64_mask(a, b));
#else
      uint8_t m = 0;
      for (int k = 0; k < 8; ++k) m |= static_cast<uint8_t>((cur[8 * l + k] != prev[8 * l + k]) << k);
      masks[l] = m;
#endif
    }
    uint32_t* moved = slot_moved_.data();
    const std::size_t moved_count = collect_moved(masks, lines, moved);
    uint32_t* changed = slot_changed_.data();
    std::size_t changed_count = 0;
    for (std::size_t i = 0; i < moved_count; ++i) {
      const uint32_t l = moved[i];
      const uint8_t m = masks[l];
#if defined(__AVX512BW__)
      _mm512_store_si512(reinterpret_cast<__m512i*>(prev + 8 * l),
                         _mm512_load_si512(reinterpret_cast<const __m512i*>(cur + 8 * l)));
#else
      std::memcpy(prev + 8 * l, cur + 8 * l, 64);
#endif
      for (uint32_t k = 0; k < 8; ++k) {
        changed[changed_count] = 8 * l + k;
        changed_count += (m >> k) & 1u;
      }
    }
    for (std::size_t i = 0; i < changed_count; ++i) {
      const uint32_t index = changed[i];
      const uint32_t slot = gathered_slot_[index];
      if (slot != 0xffffffffu) {
        const uint64_t value = cur[index];
        slot_values_[slot] = value;  // keep the batch view current (checks, family loads)
        commit_lane(lane_of_slot_[slot], value);
      }
      // Exact evaluators depending on this entry.
      for (uint32_t d = dep_first_[index]; d < dep_first_[index + 1]; ++d) {
        Evaluator& e = evaluators_[dep_list_[d]];
        if (e.stamp == stamp_ || e.always) continue;
        e.stamp = stamp_;
        due_streams_.push_back(dep_list_[d]);
      }
    }
    stat_diff_cycles_ += 1;
    stat_diff_moved_ += moved_count;
    stat_diff_changed_ += changed_count;
    stat_diff_streams_ += due_streams_.size();
  }
  /** Run the exact evaluators woken by the diff (the model is still in the
    * post-commit state of the previous step). */
  void run_due_streams(const SystemGuider& model) {
    if (exact_dispatch_ == nullptr) {
      for (uint32_t id : due_streams_) run_evaluator(id, model);
      due_streams_.clear();
      return;
    }
    for (uint32_t id : due_streams_) mark_due(id, model);
    due_streams_.clear();
    if (!due_batches_.empty()) {
      exact_dispatch_(model, *this);
      clear_due_batches();
    }
  }

  /** Three passes, each a plain loop: (1) every line's byte-difference
    * mask, and a branch-free list of the lines that moved; (2) for the
    * moved lines only: refresh the shadow, list the fields whose bytes
    * moved (branch-free) and wake the evaluators; (3) commit the listed
    * fields.  No data-dependent branch is taken per line or per field,
    * so intermittently moving lines cost no mispredictions. */
  void scan(PlacementTable& t) {
    const std::size_t n = t.chunks.size();
    if (n == 0) return;
    unsigned char* shadow = t.shadow;
    uint8_t* masks = t.line_moved.data();
    const Chunk* chunks = t.chunks.data();
    for (std::size_t c = 0; c < n; ++c) {
#if defined(__AVX512BW__)
      const __m512i live = _mm512_loadu_si512(chunks[c].src);
      const __m512i old = _mm512_load_si512(reinterpret_cast<const __m512i*>(shadow + 64 * c));
      const uint64_t changed=_mm512_cmpneq_epi8_mask(live,old);
      if constexpr(kPreciseDependencyBytes) {
        t.changed_bytes[c]=changed;
        masks[c]=(changed&t.claimed_bytes[c])!=0;
      } else masks[c]=changed!=0;
#else
      if constexpr(kPreciseDependencyBytes) {
        uint64_t changed=0;
        for(unsigned byte=0;byte<64;++byte)
          changed |= uint64_t(chunks[c].src[byte]!=shadow[64*c+byte])<<byte;
        t.changed_bytes[c]=changed;
        masks[c]=(changed&t.claimed_bytes[c])!=0;
      } else masks[c]=std::memcmp(chunks[c].src,shadow+64*c,64)!=0;
#endif
    }
    uint32_t* moved = t.moved.data();
    const std::size_t moved_count = collect_moved(masks, n, moved);
    for (std::size_t i = 0; i < moved_count; ++i) {
      const uint32_t c = moved[i];
      const Chunk& ch = t.chunks[c];
      if (!t.chunk_moves.empty()) ++t.chunk_moves[c];
      alignas(64) uint64_t word_changes[8];
      if constexpr(kPreciseDependencyBytes) {
#if defined(__AVX512BW__)
        const auto changes=_mm512_xor_si512(_mm512_loadu_si512(ch.src),
            _mm512_load_si512(reinterpret_cast<const __m512i*>(shadow+64*c)));
        _mm512_store_si512(reinterpret_cast<__m512i*>(word_changes),changes);
#else
        for(unsigned word=0;word<8;++word) {
          uint64_t live=0,old=0;
          std::memcpy(&live,ch.src+word*8,8);std::memcpy(&old,shadow+64*c+word*8,8);
          word_changes[word]=live^old;
        }
#endif
      }
#if defined(__AVX512BW__)
      _mm512_store_si512(reinterpret_cast<__m512i*>(shadow + 64 * c),
                         _mm512_loadu_si512(ch.src));
#else
      std::memcpy(shadow + 64 * c, ch.src, 64);
#endif
      const uint32_t eend = ch.first_eval + ch.eval_count;
      for (uint32_t e = ch.first_eval; e < eend; ++e) {
        if constexpr(kPreciseDependencyBytes) {
          if(!(t.changed_bytes[c]&t.eval_byte_masks[e]))continue;
          const auto word=t.eval_words[e];
          if(word<8 && !(word_changes[word]&t.eval_word_masks[e]))continue;
        }
        const uint32_t id = t.evals[e];
        Evaluator& ev = evaluators_[id];
        if (ev.stamp == stamp_ || ev.always) continue;
        ev.stamp = stamp_;
        t.pending.push_back(id);
      }
    }
    t.stat_cycles += 1;
    t.stat_moved += moved_count;
    if ((t.stat_cycles % kProbeEvery) == 0) probe(t);
  }
  /** Count wakes of the always-on evaluators whose lines are probed. */
  void probe(PlacementTable& t) {
    const std::size_t n = t.probe_chunks.size();
    for (std::size_t c = 0; c < n; ++c) {
      const Chunk& ch = t.probe_chunks[c];
      unsigned char* sh = t.probe_shadow + 64 * c;
#if defined(__AVX512BW__)
      const __m512i live = _mm512_loadu_si512(ch.src);
      const bool moved = _mm512_cmpneq_epi8_mask(live, _mm512_load_si512(reinterpret_cast<const __m512i*>(sh))) != 0;
      if (!moved) continue;
      _mm512_store_si512(reinterpret_cast<__m512i*>(sh), live);
#else
      if (std::memcmp(ch.src, sh, 64) == 0) continue;
      std::memcpy(sh, ch.src, 64);
#endif
      const uint32_t eend = ch.first_eval + ch.eval_count;
      for (uint32_t e = ch.first_eval; e < eend; ++e) {
        Evaluator& ev = evaluators_[t.probe_evals[e]];
        if (ev.stamp == stamp_) continue;
        ev.stamp = stamp_;
        ++ev.probe_hits;  // moved at least once in the last kProbeEvery cycles
      }
    }
  }
  /** Every kAdaptWindow cycles: evaluators woken in more than
    * kAdaptWakeRatio of them stop being watched (promote-only; the
    * program's phases differ and boot is quiet). */
  void adapt(SamplePlacement placement, PlacementTable& t) {
    std::size_t promoted = 0, demoted = 0;
    const double probes = double(t.window_cycles) / double(kProbeEvery);
    for (Evaluator& e : evaluators_) {
      if (e.placement != placement) continue;
      const double ratio = double(e.wakes) / double(t.window_cycles);
      // A probe sees whether a line moved at least once in kProbeEvery
      // cycles; turn that into a per-cycle estimate before comparing.
      const double probe_ratio = probes > 0 ? double(e.probe_hits) / probes : 1.0;
      const double probe_per_cycle =
          1.0 - std::pow(1.0 - std::min(probe_ratio, 0.999), 1.0 / double(kProbeEvery));
      (void)probe_per_cycle;
      if (!profile_mode_ && !e.always && ratio >= promote_threshold(e)) {
        e.always = true;
        ++promoted;
      }
      e.wakes = 0;
      e.probe_hits = 0;
    }
    if (promoted != 0 || demoted != 0) {
      build_placement_lines(placement, t);
      static const bool stats = std::getenv("SYSMODEL_WATCH_STATS") != nullptr;
      if (stats)
        std::fprintf(stderr, "[WATCH] %s: %zu promoted to always-on, %zu gated again, %zu region lines\n",
                     placement_name(placement), promoted, demoted, t.chunks.size());
    }
    t.window_cycles = 0;
  }
  /** The region lines of one placement (evaluators not always-on), the
    * always-on list, and fresh shadows. */
  void build_placement_lines(SamplePlacement placement, PlacementTable& t) {
    struct LineBuild {
      std::vector<uint32_t> evals;
      std::vector<uint64_t> masks, word_masks;
      std::vector<uint8_t> words;
      uint64_t claimed = 0;
    };
    t.chunks.clear();
    t.evals.clear();
    t.eval_byte_masks.clear();t.claimed_bytes.clear();
    t.eval_word_masks.clear();t.eval_words.clear();
    t.always_evals.clear();
    // Distinct region lines per evaluator (promotion policy) and, when
    // probing is enabled, which always-on ones are cheap enough to probe.
    {
      std::map<uint32_t, std::vector<std::uintptr_t>> lines_of;
      for (const RegionBuild& r : region_builds_) {
        const Evaluator& e = evaluators_[r.evaluator];
        if (e.placement != placement) continue;
        const std::uintptr_t a = reinterpret_cast<std::uintptr_t>(r.addr);
        const std::uintptr_t end = a + r.bytes;
        std::vector<std::uintptr_t>& v = lines_of[r.evaluator];
        for (std::uintptr_t line = a & ~std::uintptr_t{63}; line < end; line += 64)
          if (std::find(v.begin(), v.end(), line) == v.end()) v.push_back(line);
      }
      for (Evaluator& e : evaluators_)
        if (e.placement == placement) e.probe = false;
      for (const auto& [id, v] : lines_of) {
        evaluators_[id].lines = static_cast<uint32_t>(v.size());
        evaluators_[id].probe = evaluators_[id].always && !evaluators_[id].forced &&
                                !v.empty() && v.size() <= kAdaptProbeLines;
      }
    }
    std::map<std::uintptr_t, LineBuild> lines, probe_lines;
    for (const RegionBuild& r : region_builds_) {
      const Evaluator& e = evaluators_[r.evaluator];
      if (e.placement != placement || (e.always && !e.probe)) continue;
      std::map<std::uintptr_t, LineBuild>& target = e.always ? probe_lines : lines;
      const std::uintptr_t a = reinterpret_cast<std::uintptr_t>(r.addr);
      const std::uintptr_t end = a + r.bytes;
      for (std::uintptr_t line = a & ~std::uintptr_t{63}; line < end; line += 64) {
        LineBuild& build=target[line];
        auto& evals=build.evals;
        const auto found=std::find(evals.begin(),evals.end(),r.evaluator);
        const std::size_t index=static_cast<std::size_t>(found-evals.begin());
        if(found==evals.end()) {
          evals.push_back(r.evaluator);
          if constexpr(kPreciseDependencyBytes) {
            build.masks.push_back(0);build.word_masks.push_back(0);build.words.push_back(254);
          }
        }
        if constexpr(kPreciseDependencyBytes) {
          const unsigned lo=static_cast<unsigned>(a>line ? a-line : 0);
          const unsigned hi=static_cast<unsigned>(std::min<std::uintptr_t>(64,end-line));
          const uint64_t mask=bits_below(hi)&~bits_below(lo);
          build.masks[index] |= mask;build.claimed |= mask;
          if(a>=line && end<=line+64 && ((a-line)/8)==((end-line-1)/8)) {
            const auto word=static_cast<uint8_t>((a-line)/8);
            const auto bits=bits_below(static_cast<unsigned>(r.bytes*8))&r.value_mask;
            if(build.words[index]==254 || build.words[index]==word) {
              build.words[index]=word;build.word_masks[index] |= bits<<((a-line)%8*8);
            } else build.words[index]=255;
          } else build.words[index]=255;
        }
      }
    }
    for (auto& [line, build] : lines) {
      Chunk ch{reinterpret_cast<const unsigned char*>(line),
               static_cast<uint32_t>(t.evals.size()),
               static_cast<uint32_t>(build.evals.size())};
      t.evals.insert(t.evals.end(), build.evals.begin(), build.evals.end());
      if constexpr(kPreciseDependencyBytes) {
        t.eval_byte_masks.insert(t.eval_byte_masks.end(),build.masks.begin(),build.masks.end());
        t.claimed_bytes.push_back(build.claimed);
        t.eval_word_masks.insert(t.eval_word_masks.end(),build.word_masks.begin(),build.word_masks.end());
        t.eval_words.insert(t.eval_words.end(),build.words.begin(),build.words.end());
      }
      t.chunks.push_back(ch);
    }
    t.probe_chunks.clear();
    t.probe_evals.clear();
    for (auto& [line, build] : probe_lines) {
      Chunk ch{reinterpret_cast<const unsigned char*>(line),
               static_cast<uint32_t>(t.probe_evals.size()),
               static_cast<uint32_t>(build.evals.size())};
      t.probe_evals.insert(t.probe_evals.end(), build.evals.begin(), build.evals.end());
      t.probe_chunks.push_back(ch);
    }
    t.line_moved.assign(t.chunks.size() + 8, 0);
    if constexpr(kPreciseDependencyBytes)t.changed_bytes.assign(t.chunks.size(),0);
    t.moved.assign(t.chunks.size() + 8, 0);
    t.shadow_storage.assign(t.chunks.size() * 64 + 64, 0);
    t.shadow = align64(t.shadow_storage.data());
    static const bool stats = std::getenv("SYSMODEL_WATCH_STATS") != nullptr;
    if (stats || profile_mode_) t.chunk_moves.assign(t.chunks.size(), 0);
    t.probe_shadow_storage.assign(t.probe_chunks.size() * 64 + 64, 0);
    t.probe_shadow = align64(t.probe_shadow_storage.data());
    t.always_due.clear();
    t.always_direct.clear();
    for (std::size_t i = 0; i < evaluators_.size(); ++i) {
      const Evaluator& e = evaluators_[i];
      if (e.placement != placement || !e.always) continue;
      t.always_evals.push_back(static_cast<uint32_t>(i));
      // all_prestep(): the static dispatchers belong to the original
      // placements, so every always-on evaluator is called directly.
      if (e.ordinal < 0 || e.ordinal >= 64 || e.batch < 0 || all_prestep() ||
          dispatch_[static_cast<std::size_t>(placement)] == nullptr) {
        t.always_direct.push_back(static_cast<uint32_t>(i));
        continue;
      }
      bool merged = false;
      for (PlacementTable::AlwaysDue& a : t.always_due)
        if (a.batch == static_cast<std::size_t>(e.batch)) {
          a.bits |= UINT64_C(1) << e.ordinal;
          merged = true;
        }
      if (!merged)
        t.always_due.push_back(PlacementTable::AlwaysDue{static_cast<std::size_t>(e.batch),
                                                        UINT64_C(1) << e.ordinal});
    }
  }
  void build_tables() {
    for (PlacementTable& t : tables_) t = PlacementTable{};
    // The slot array: 64-byte aligned, padded to whole lines, plus its
    // committed image and the per-diff scratch lists.
    const std::size_t count = lane_of_slot_.size();
    slot_storage_.assign(count + 8, 0);
    slot_values_ = align64(slot_storage_.data());
    // ---- Unified storage claiming: fields living inside a declared
    // region leave the gather path; diff_unified() commits them straight
    // from model memory at the cycle start.
    unified_.clear();
    unified_flat_.clear();
    unified_row_src_.clear();
    unified_row_claimed_.clear();
    unified_row_byte_field_.clear();
    unified_row_field_first_.clear();
    unified_row_fields_.clear();
    unify_check_fields_.clear();

    // Large gathers immediately at the placement (a different commit
    // position in the block); unify only under the deferred contract.
    if (!unify_builds_.empty() && std::getenv("SYSMODEL_NO_UNIFY") == nullptr) {
      const bool check_only_mode = std::getenv("SYSMODEL_UNIFY_CHECK") != nullptr;
      std::map<std::pair<std::uintptr_t, uint8_t>, char> input_keys;
      for (const InputBuild& in : input_builds_)
        input_keys.emplace(std::pair<std::uintptr_t, uint8_t>{
            reinterpret_cast<std::uintptr_t>(in.addr), in.bytes}, 1);
      for (const UnifyBuild& u : unify_builds_) {
        UnifiedRegion r;
        r.name = u.name;
        r.rows_base = reinterpret_cast<const unsigned char*>(
            reinterpret_cast<std::uintptr_t>(u.base) & ~std::uintptr_t{63});
        r.rows = (reinterpret_cast<std::uintptr_t>(u.base) + u.bytes -
                  reinterpret_cast<std::uintptr_t>(r.rows_base) + 63) / 64;
        r.claimed.assign(r.rows, 0);
        r.byte_field.assign(r.rows * 64, 0xffff);
        unified_.push_back(std::move(r));
      }
      std::vector<FieldBuild> kept;
      kept.reserve(field_builds_.size());
      for (const FieldBuild& f : field_builds_) {
        UnifiedRegion* region = nullptr;
        const UnifyBuild* build = nullptr;
        for (std::size_t u = 0; u < unify_builds_.size(); ++u) {
          const UnifyBuild& b = unify_builds_[u];
          if (f.addr >= b.base && f.addr + f.bytes <= b.base + b.bytes) {
            region = &unified_[u];
            build = &b;
            break;
          }
        }
        const std::uint16_t lane = lane_of_slot_[f.slot];
        bool claim = region != nullptr && f.bytes <= 8 &&
                     lane < kOracleRecordLanes &&
                     input_keys.find({reinterpret_cast<std::uintptr_t>(f.addr),
                                      f.bytes}) == input_keys.end();
        if (claim) {  // an aliased/overlapping byte keeps the field gathered
          const std::size_t off = static_cast<std::size_t>(f.addr - region->rows_base);
          for (std::size_t k = 0; k < f.bytes && claim; ++k)
            claim = region->byte_field[off + k] == 0xffff;
        }
        if (!claim) {
          kept.push_back(f);
          continue;
        }
        if (check_only_mode) {
          unify_check_fields_.push_back(f);
          kept.push_back(f);
          continue;
        }
        const std::size_t off = static_cast<std::size_t>(f.addr - region->rows_base);
        const uint16_t fid = static_cast<uint16_t>(unified_flat_.size());
        unified_flat_.push_back(UnifiedField{
            f.addr, f.slot, lane, lane_bits_[lane], f.bytes,
            static_cast<uint8_t>(64 - 8 * f.bytes), f.is_signed,
            f.addr + 8 > build->base + build->bytes,
            kOracleRecordLane[lane].mask, kOracleRecordLane[lane].offset});
        region->field_count += 1;
        for (std::size_t k = 0; k < f.bytes; ++k) {
          region->byte_field[off + k] = fid;
          region->claimed[(off + k) / 64] |= UINT64_C(1) << ((off + k) % 64);
        }
      }
      field_builds_ = std::move(kept);
      // Flatten every claimed row of every region into the dense runtime
      // arrays: the per-cycle loop streams over compact shadow/mask/table
      // storage and touches sparse memory only for the claimed model rows.
      unified_row_field_first_.push_back(0);
      for (UnifiedRegion& r : unified_)
        for (std::size_t l = 0; l < r.rows; ++l) {
          if (r.claimed[l] == 0) continue;
          unified_row_src_.push_back(r.rows_base + 64 * l);
          unified_row_claimed_.push_back(r.claimed[l]);
          unified_row_byte_field_.insert(unified_row_byte_field_.end(),
                                         r.byte_field.begin() + 64 * l,
                                         r.byte_field.begin() + 64 * l + 64);
          // Image mode: the distinct fields under this row's claimed bytes
          // (a field's bytes are contiguous, so a run compare dedupes).
          uint16_t last = 0xffff;
          for (std::size_t k = 0; k < 64; ++k) {
            if (((r.claimed[l] >> k) & 1u) == 0) continue;
            const uint16_t fid = r.byte_field[64 * l + k];
            if (fid == last) continue;
            last = fid;
            const UnifiedField& f = unified_flat_[fid];
            const std::ptrdiff_t fstart = f.addr - (r.rows_base + 64 * l);
            const std::ptrdiff_t lo = fstart > 0 ? fstart : 0;
            const std::ptrdiff_t hi =
                fstart + static_cast<std::ptrdiff_t>(f.bytes) < 64
                    ? fstart + static_cast<std::ptrdiff_t>(f.bytes)
                    : 64;
            RowField rf{};
            rf.fmask = bits_below(static_cast<unsigned>(hi)) &
                       ~bits_below(static_cast<unsigned>(lo));
            rf.off = static_cast<int8_t>(fstart);
            rf.bytes = f.bytes;
            rf.shift = f.shift;
            rf.is_signed = f.is_signed ? 1 : 0;
            rf.tail = f.tail ? 1 : 0;
            rf.bits = f.bits;
            rf.rec_off = f.rec_off;
            rf.rec_mask = f.rec_mask;
            rf.slot = f.slot;
            unified_row_fields_.push_back(rf);
          }
          unified_row_field_first_.push_back(
              static_cast<uint32_t>(unified_row_fields_.size()));
        }
      // SYSMODEL_UNIFIED_ROWS=1: dump every claimed row with the streams it
      // carries (layout work: which model lines the scan touches and why).
      if (std::getenv("SYSMODEL_UNIFIED_ROWS") != nullptr) {
        std::vector<const char*> key_of_slot(lane_of_slot_.size(), "?");
        for (const auto& [key, b] : bindings_)
          if (b.sampled_slot >= 0 && static_cast<std::size_t>(b.sampled_slot) < key_of_slot.size())
            key_of_slot[static_cast<std::size_t>(b.sampled_slot)] = key.c_str();
        for (std::size_t i = 0; i < unified_row_src_.size(); ++i) {
          const unsigned char* row = unified_row_src_[i];
          const char* region = "?";
          std::size_t off = 0;
          for (const UnifiedRegion& r : unified_)
            if (row >= r.rows_base && row < r.rows_base + 64 * r.rows) {
              region = r.name;
              off = static_cast<std::size_t>(row - r.rows_base);
            }
          std::fprintf(stderr, "[ROW] %3zu %-10s off=%7zu bytes=%2d :", i, region, off,
                       __builtin_popcountll(unified_row_claimed_[i]));
          uint16_t last = 0xffff;
          for (std::size_t k = 0; k < 64; ++k) {
            if (((unified_row_claimed_[i] >> k) & 1u) == 0) continue;
            const uint16_t fid = unified_row_byte_field_[64 * i + k];
            if (fid == last) continue;
            last = fid;
            std::fprintf(stderr, " %s", key_of_slot[unified_flat_[fid].slot]);
          }
          std::fprintf(stderr, "\n");
        }
      }
      unified_shadow_storage_.assign(unified_row_src_.size() * 64 + 64, 0);
      unified_shadow_ = align64(unified_shadow_storage_.data());
      unified_masks_.assign(unified_row_src_.size() + 1, 0);
      unified_moved_.assign(unified_row_src_.size() + 1, 0);
    }

    for (int p = 0; p < 5; ++p) {
      const SamplePlacement placement = static_cast<SamplePlacement>(p);
      PlacementTable& t = tables_[p];
      for (const FieldBuild& f : field_builds_) {
        if (f.placement != placement) continue;
        GatherGroup* group = nullptr;
        for (GatherGroup& g : t.groups)
          if (g.bytes == f.bytes && g.is_signed == f.is_signed) group = &g;
        if (group == nullptr) {
          t.groups.push_back(GatherGroup{f.bytes, f.is_signed, {}, {}});
          group = &t.groups.back();
        }
        group->addrs.push_back(f.addr);
        group->slots.push_back(f.slot);
        t.field_count += 1;
      }
      // SYSMODEL_SAMPLE_ALWAYS=1: run every evaluator of this placement each
      // cycle instead of watching its model lines for changes (measurement
      // knob for the image-mode sampler; the record must not change).
      {
        static const bool always_all = std::getenv("SYSMODEL_SAMPLE_ALWAYS") != nullptr;
        if (always_all)
          for (Evaluator& e : evaluators_)
            if (e.placement == placement && !e.always) {
              e.always = true;
              e.forced = true;
              e.why = "SYSMODEL_SAMPLE_ALWAYS";
            }
      }
      build_placement_lines(placement, t);
      for (const Batch& b : batches_)
        if (b.placement == placement && b.watch == nullptr) t.legacy.push_back(&b);
    }
    // The compact gathered array: placed (non-PreStep) groups in order.
    std::size_t total = 0;
    gathered_slot_.clear();
    for (int p = 1; p < 5; ++p)
      for (GatherGroup& g : tables_[p].groups) {
        g.first = total;
        for (uint32_t slot : g.slots) gathered_slot_.push_back(slot);
        total += g.slots.size();
      }
    static constexpr uint32_t kNoSlot = 0xffffffffu;
    // Dependency-only inputs of the exact evaluators: gathered at End, no
    // lane (slot kNoSlot).  An input that is already a gathered stream
    // field (same address and width) reuses that entry.
    {
      std::map<std::pair<std::uintptr_t, uint8_t>, std::size_t> entry_of;
      std::size_t index = 0;
      for (int p = 1; p < 5; ++p)
        for (const GatherGroup& g : tables_[p].groups)
          for (std::size_t i = 0; i < g.addrs.size(); ++i)
            entry_of[{reinterpret_cast<std::uintptr_t>(g.addrs[i]), g.bytes}] = g.first + i;
      PlacementTable& end = tables_[static_cast<int>(SamplePlacement::End)];
      std::vector<std::vector<uint32_t>> dependents(total);
      for (const InputBuild& in : input_builds_) {
        const std::pair<std::uintptr_t, uint8_t> key{reinterpret_cast<std::uintptr_t>(in.addr), in.bytes};
        auto found = entry_of.find(key);
        if (found == entry_of.end()) {
          GatherGroup* group = nullptr;
          for (GatherGroup& g : end.groups)
            if (g.bytes == in.bytes && g.is_signed == in.is_signed) group = &g;
          if (group == nullptr) {
            end.groups.push_back(GatherGroup{in.bytes, in.is_signed, {}, {}});
            group = &end.groups.back();
            group->first = total;  // provisional; fixed below
          }
          // Append to the group; entries of a group must stay contiguous,
          // so groups created here are laid out after all stream groups.
          group->addrs.push_back(in.addr);
          group->slots.push_back(kNoSlot);
          entry_of[key] = index = total++;
          dependents.resize(total);
          found = entry_of.find(key);
        }
        dependents[found->second].push_back(in.evaluator);
      }
      (void)index;
      // Re-lay the End groups' first indices after the stream groups: the
      // stream groups keep [0, stream_total), dependency-only entries follow.
      std::size_t cursor = 0;
      gathered_slot_.clear();
      for (int p = 1; p < 5; ++p)
        for (GatherGroup& g : tables_[p].groups) {
          g.first = cursor;
          for (uint32_t slot : g.slots) gathered_slot_.push_back(slot);
          cursor += g.slots.size();
        }
      total = cursor;
      dep_first_.assign(total + 1, 0);
      dep_list_.clear();
      // dependents was indexed by provisional entry numbers, which equal the
      // final layout only when the End groups were appended last; rebuild it
      // by address instead to be safe.
      std::map<std::pair<std::uintptr_t, uint8_t>, std::size_t> final_entry;
      for (int p = 1; p < 5; ++p)
        for (const GatherGroup& g : tables_[p].groups)
          for (std::size_t i = 0; i < g.addrs.size(); ++i)
            final_entry[{reinterpret_cast<std::uintptr_t>(g.addrs[i]), g.bytes}] = g.first + i;
      std::vector<std::vector<uint32_t>> deps(total);
      for (const InputBuild& in : input_builds_) {
        const std::size_t e = final_entry.at({reinterpret_cast<std::uintptr_t>(in.addr), in.bytes});
        if (std::find(deps[e].begin(), deps[e].end(), in.evaluator) == deps[e].end())
          deps[e].push_back(in.evaluator);
      }
      for (std::size_t e = 0; e < total; ++e) {
        dep_first_[e] = static_cast<uint32_t>(dep_list_.size());
        dep_list_.insert(dep_list_.end(), deps[e].begin(), deps[e].end());
      }
      dep_first_[total] = static_cast<uint32_t>(dep_list_.size());
      due_streams_.clear();
      due_streams_.reserve(evaluators_.size());
      // Every exact evaluator runs once at the first diff.
      for (std::size_t i = 0; i < evaluators_.size(); ++i)
        if (evaluators_[i].exact && !evaluators_[i].always) due_streams_.push_back(static_cast<uint32_t>(i));
    }
    gathered_lines_ = (total + 7) / 8;
    gathered_storage_.assign(gathered_lines_ * 8 + 8, 0);
    gathered_prev_storage_.assign(gathered_lines_ * 8 + 8, 0);
    gathered_ = align64(gathered_storage_.data());
    gathered_prev_ = align64(gathered_prev_storage_.data());
    gathered_slot_.resize(gathered_lines_ * 8 + 8, kNoSlot);
    slot_gather_index_.assign(count, -1);
    for (std::size_t i = 0; i < total; ++i)
      if (gathered_slot_[i] != kNoSlot) slot_gather_index_[gathered_slot_[i]] = static_cast<int32_t>(i);
    // Claimed fields still read as "directly sampled" (>= 0) so a batch's
    // guarded accessor store keeps skipping them; the sentinel range routes
    // the verify path to the field's own memory as the staged view.
    for (std::size_t i = 0; i < unified_flat_.size(); ++i)
      slot_gather_index_[unified_flat_[i].slot] =
          kUnifiedGatherBase + static_cast<int32_t>(i);
    slot_exact_.assign(count, false);
    for (const Evaluator& e : evaluators_)
      if (e.exact && e.slot >= 0 && static_cast<std::size_t>(e.base + e.slot) < count)
        slot_exact_[static_cast<std::size_t>(e.base + e.slot)] = true;
    slot_masks_.assign(gathered_lines_ + 8, 0);
    slot_moved_.assign(gathered_lines_ + 1, 0);
    slot_changed_.assign(gathered_lines_ * 8 + 8, 0);
  }

 public:
  /** Watch-table statistics (for the bench line). */
  struct WatchStats {
    std::size_t chunks = 0, fields = 0, evaluators = 0, always = 0, legacy = 0, check_only = 0;
  };
  void report_watch_activity() const {

    if (cost_mode_) {
      std::vector<std::size_t> order(evaluators_.size());
      for (std::size_t i = 0; i < order.size(); ++i) order[i] = i;
      std::sort(order.begin(), order.end(), [&](std::size_t a, std::size_t b) {
        return evaluators_[a].cost > evaluators_[b].cost;
      });
      const double cycles = stat_diff_cycles_ != 0 ? double(stat_diff_cycles_) : 1.0;
      uint64_t total = 0;
      for (const Evaluator& e : evaluators_) total += e.cost;
      std::fprintf(stderr, "[COST] evaluators total %.0f ticks/cycle over %.0f cycles\n",
                   double(total) / cycles, cycles);
      for (std::size_t n = 0; n < order.size() && n < 60; ++n) {
        const Evaluator& e = evaluators_[order[n]];
        if (e.cost == 0) break;
        std::fprintf(stderr,
                     "[COST] %6.1f ticks/cycle runs/cycle=%.3f ticks/run=%6.0f  %s %s ordinal=%d slot=%d lines=%u stores=%u thr=%.2f%s%s%s\n",
                     double(e.cost) / cycles, double(e.runs) / cycles,
                     double(e.cost) / double(e.runs),
                     e.batch >= 0 ? batches_[static_cast<std::size_t>(e.batch)].name : "(no batch)",
                     placement_name(e.placement), e.ordinal, e.slot, e.lines, e.stores, promote_threshold(e),
                     e.always ? " always" : "", e.forced ? " forced" : "", e.exact ? " exact" : "");
        if (e.forced) std::fprintf(stderr, "[COST]        why: %s (%zu B)\n", e.why, e.why_bytes);
      }
    }
    for (int p = 0; p < 5; ++p) {
      const PlacementTable& t = tables_[p];
      for (std::size_t c = 0; c < t.chunk_moves.size(); ++c) {
        if (t.stat_cycles == 0 || t.chunk_moves[c] * 20 < t.stat_cycles) continue;  // >= 5% of cycles
        std::fprintf(stderr, "[WATCH] %s line %p moves %.2f/cycle, wakes evaluators:",
                     placement_name(static_cast<SamplePlacement>(p)),
                     static_cast<const void*>(t.chunks[c].src),
                     double(t.chunk_moves[c]) / double(t.stat_cycles));
        for (uint32_t e = t.chunks[c].first_eval; e < t.chunks[c].first_eval + t.chunks[c].eval_count; ++e)
          std::fprintf(stderr, " %u(base %d)", t.evals[e], evaluators_[t.evals[e]].base);
        std::fprintf(stderr, "\n");
      }
    }
    if (stat_diff_cycles_ != 0)
      std::fprintf(stderr, "[WATCH] gathered diff: per cycle moved_lines=%.1f/%zu changed_entries=%.1f exact_streams_run=%.1f\n",
                   double(stat_diff_moved_) / double(stat_diff_cycles_), gathered_lines_,
                   double(stat_diff_changed_) / double(stat_diff_cycles_),
                   double(stat_diff_streams_) / double(stat_diff_cycles_));
    if (stat_diff_cycles_ != 0 && !unified_flat_.empty()) {
      for (const UnifiedRegion& r : unified_)
        std::fprintf(stderr, "[WATCH] unified %s: fields=%zu\n", r.name,
                     r.field_count);
      std::fprintf(stderr,
                   "[WATCH] unified total: fields=%zu rows=%zu moved_rows/cycle=%.1f commits/cycle=%.1f\n",
                   unified_flat_.size(), unified_row_src_.size(),
                   double(stat_unified_rows_moved_) / double(stat_diff_cycles_),
                   double(stat_unified_commits_) / double(stat_diff_cycles_));
#ifdef CHISA_PHASE_TIMERS
      std::fprintf(stderr, "[WATCH] unified diff ticks/cycle: pass1(scan)=%.0f pass2(commit)=%.0f\n",
                   double(stat_unified_pass1_tsc_) / double(stat_diff_cycles_),
                   double(stat_unified_pass2_tsc_) / double(stat_diff_cycles_));
#endif
      // Row density: how many of each row's 64 bytes carry a bound field.
      std::size_t claimed_bytes = 0, hist[5] = {};
      for (std::size_t i = 0; i < unified_row_claimed_.size(); ++i) {
        const unsigned n = static_cast<unsigned>(__builtin_popcountll(unified_row_claimed_[i]));
        claimed_bytes += n;
        ++hist[n <= 4 ? 0 : n <= 8 ? 1 : n <= 16 ? 2 : n <= 32 ? 3 : 4];
      }
      std::fprintf(stderr,
                   "[WATCH] unified rows: claimed_bytes=%zu of %zu; rows with <=4 bytes %zu, 5-8 %zu, 9-16 %zu, 17-32 %zu, 33-64 %zu\n",
                   claimed_bytes, unified_row_claimed_.size() * 64, hist[0], hist[1], hist[2], hist[3], hist[4]);
      // SYSMODEL_UNIFIED_ROWS=1: every row with its region, claimed byte
      // count and the lanes it carries (layout planning).
      if (std::getenv("SYSMODEL_UNIFIED_ROWS") != nullptr) {
        for (const UnifiedRegion& r : unified_) {
          for (std::size_t i = 0; i < r.rows; ++i) {
            const uint64_t c = r.claimed[i];
            if (c == 0) continue;
            std::fprintf(stderr, "[UROW] %s row=%zu bytes=%d lanes:", r.name, i,
                         __builtin_popcountll(c));
            uint64_t bits = c;
            uint16_t last = 0xffff;
            while (bits != 0) {
              const unsigned k = static_cast<unsigned>(__builtin_ctzll(bits));
              bits &= bits - 1;
              const uint16_t fid = r.byte_field[64 * i + k];
              if (fid == 0xffff || fid == last) continue;
              last = fid;
              std::fprintf(stderr, " %u", unified_flat_[fid].lane);
            }
            std::fprintf(stderr, "\n");
          }
        }
      }
    }
    for (int p = 0; p < 5; ++p) {
      const PlacementTable& t = tables_[p];
      if (t.stat_cycles == 0) continue;
      std::fprintf(stderr,
                   "[WATCH] %s: fields=%zu region_lines=%zu probe_lines=%zu moved_lines/cycle=%.1f woken_evals/cycle=%.2f always=%zu\n",
                   placement_name(static_cast<SamplePlacement>(p)), t.field_count,
                   t.chunks.size(), t.probe_chunks.size(), double(t.stat_moved) / double(t.stat_cycles),
                   double(t.stat_evals) / double(t.stat_cycles), t.always_evals.size());
    }
  }
  /** Profile-mode exit report: per declared chain, the move rate of its
    * lines (max over lines); forced-always chains as rate 1. */
  void report_hot_chains() const {
    std::map<std::string, double> rate;
    for (int p = 0; p < 5; ++p) {
      const PlacementTable& t = tables_[p];
      if (t.stat_cycles == 0 || t.chunk_moves.empty()) continue;
      for (std::size_t c = 0; c < t.chunks.size(); ++c) {
        const double r = double(t.chunk_moves[c]) / double(t.stat_cycles);
        const std::uintptr_t line = reinterpret_cast<std::uintptr_t>(t.chunks[c].src);
        for (const RegionBuild& b : region_builds_) {
          if (evaluators_[b.evaluator].placement != static_cast<SamplePlacement>(p)) continue;
          const std::uintptr_t a = reinterpret_cast<std::uintptr_t>(b.addr);
          if (line + 64 <= a || line >= a + b.bytes) continue;
          const char* chain = std::strstr(b.what, " <- ");
          std::string key = chain != nullptr ? std::string(chain + 4) : std::string(b.what);
          double& slot = rate[key];
          if (r > slot) slot = r;
        }
      }
    }
    for (const Evaluator& e : evaluators_) {
      if (!e.forced || e.why == nullptr || e.why[0] == '\0') continue;
      const char* chain = std::strstr(e.why, " <- ");
      rate[chain != nullptr ? std::string(chain + 4) : std::string(e.why)] = 1.0;
    }
    for (const auto& [chain, r] : rate)
      if (r >= 0.01) std::fprintf(stderr, "[HOTCHAIN] %.3f %s\n", r, chain.c_str());
  }
  WatchStats watch_stats() const {
    WatchStats st;
    for (const PlacementTable& t : tables_) {
      st.chunks += t.chunks.size();
      st.fields += t.field_count;
      st.always += t.always_evals.size();
      st.legacy += t.legacy.size();
    }
    st.evaluators = evaluators_.size();
    for (const Batch& b : batches_) st.check_only += b.check_only ? 1 : 0;
    return st;
  }
};

/** The registration surface a watch declaration writes to. */
class WatchSink {
 public:
  WatchSink(ModelBindings& bindings, ModelBindings::Batch& batch, int batch_index)
      : bindings_(bindings), batch_(batch), batch_index_(batch_index) {}
  void check_only() { batch_.check_only = true; }
  void name(const char* n) { batch_.name = n; }
  /** Publish the runtime batch index to the generated dispatcher. */
  void batch_index_into(int* target) { *target = batch_index_; }
  /** The model through a dependent type, so a generic lambda's
    * `if constexpr` cascade is only checked for the branch it takes. */
  template <class T> const T& model(const T& m) const { return m; }
  template <class F> void slot(std::size_t, F&& f) { f(*this); }
  template <class F> void dep(F&& f) { f(*this); }
  /** A slot that copies one model field.  Non-scalar fields fall back to
    * an evaluator (the per-slot one when given, else the batch) that
    * depends on the field's bytes. */
  template <class T>
  void direct(std::size_t k, const T& ref, ModelBindings::BatchSampleFn fallback) {
    if constexpr (watch_scalar<T>) {
      (void)fallback;
      current_ = -1;  // gathered: the regions that follow are not needed
      bindings_.add_field(static_cast<std::size_t>(batch_.base) + k, &ref,
                          sizeof(T), std::is_signed_v<T>, batch_.placement);
    } else {
      // Not a plain scalar field: the per-slot fallback evaluator when
      // given; with none, a group evaluator already computes this slot.
      if (fallback != nullptr) {
        eval(k, fallback);
        region(&ref, sizeof(T));
      }
    }
  }
  /** One evaluator for a group of a generated batch's expressions that
    * read the same sub-object; gated by the regions declared after it. */
  /** A placed expression re-evaluated exactly when one of its input
    * fields moved (the inputs are gathered too, without a lane). */
  template <class F>
  void stream(std::size_t k, ModelBindings::BatchSampleFn fn, F&& inputs) {
    current_ = bindings_.add_evaluator(fn, batch_.base, batch_.placement,
                                       static_cast<int>(k), batch_index_,
                                       batch_.next_ordinal++);
    bindings_.mark_exact(current_);
    inputs(*this);
  }
  template <class T>
  void input(const T& ref) {
    if constexpr (watch_scalar<T>) {
      bindings_.add_input(current_, &ref, sizeof(T), std::is_signed_v<T>);
    } else {
      always("non-scalar input");  // not a plain scalar: run every cycle
    }
  }
  void group(ModelBindings::BatchSampleFn fn, uint32_t stores = 1) {
    current_ = bindings_.add_evaluator(fn, batch_.base, batch_.placement, -1,
                                       batch_index_, batch_.next_ordinal++, stores);
  }
  // Generated groups retain fixed dispatch bits even when a neighboring
  // direct-field candidate does not need an evaluator.
  void group_at(unsigned ordinal,ModelBindings::BatchSampleFn fn,uint32_t stores=1) {
    if(ordinal>=256)throw std::out_of_range("watch dispatch ordinal");
    batch_.next_ordinal=static_cast<int>(ordinal);
    group(fn,stores);
  }
  void eval(std::size_t k, ModelBindings::BatchSampleFn fn) {
    current_ = bindings_.add_evaluator(fn, batch_.base, batch_.placement,
                                       static_cast<int>(k));
  }
  /** The batch minus its direct-field lines (or the batch itself when it
    * has none): the production evaluator, gated by the regions declared
    * after it. */
  void rest(ModelBindings::BatchSampleFn fn, uint32_t stores = 1) {
    batch_.evaluator = bindings_.add_evaluator(fn != nullptr ? fn : batch_.fn,
                                               batch_.base, batch_.placement, -1,
                                               batch_index_, batch_.next_ordinal++, stores);
    current_ = batch_.evaluator;
  }
  void batch() {
    if (batch_.evaluator < 0)
      batch_.evaluator = bindings_.add_evaluator(batch_.fn, batch_.base, batch_.placement);
    current_ = batch_.evaluator;
  }
  void region(const void* addr, std::size_t bytes, const char* what = "") {
    bindings_.add_region(current_, addr, bytes, what);
  }
  void masked_region(const void* addr,std::size_t bytes,uint64_t mask) {
    bindings_.add_masked_region(current_,addr,bytes,mask,"native bit dependency");
  }
  void always(const char* why = "") { bindings_.mark_always(current_, why); }

 private:
  ModelBindings& bindings_;
  ModelBindings::Batch& batch_;
  int batch_index_;
  int current_ = -1;
};

void install_watch_dispatch(ModelBindings& b);

/** Declares the unified storage regions (defined in system_guider.cpp,
  * where the model's component types are complete). */
void declare_unified_regions(const SystemGuider& model, ModelBindings& bindings);

inline void ModelBindings::attach(const SystemGuider& model) {
  attached_ = &model;

  for (IndexedSamplerGroup& group : indexed_sampler_groups_)
    group.epoch_valid = false;
  slot_gather_index_.assign(lane_of_slot_.size(), -1);
  evaluators_.clear();
  field_builds_.clear();
  region_builds_.clear();
  input_builds_.clear();
  due_bits_.assign(batches_.size() * kDueWords, 0);
  due_batches_.clear();
  due_batches_.reserve(batches_.size());
  for (std::size_t b = 0; b < batches_.size(); ++b) {
    Batch& batch = batches_[b];

    batch.evaluator = -1;
    batch.check_only = false;
    batch.next_ordinal = 0;
    if (batch.watch == nullptr) continue;
    WatchSink sink(*this, batch, static_cast<int>(b));
    batch.watch(model, slots_of(batch), sink);
  }
  install_watch_dispatch(*this);

  for (const auto& [primary, dup] : slot_aliases_) {
    const std::size_t n = field_builds_.size();
    for (std::size_t i = 0; i < n; ++i)
      if (field_builds_[i].slot == static_cast<uint32_t>(primary)) {
        FieldBuild f = field_builds_[i];
        f.slot = static_cast<uint32_t>(dup);
        field_builds_.push_back(f);
        break;
      }
  }
  if (std::getenv("SYSMODEL_EVAL_COST") != nullptr) {
    cost_mode_ = true;
    for (DispatchFn& d : dispatch_) d = nullptr;
    exact_dispatch_ = nullptr;
  }
  unify_builds_.clear();
  declare_unified_regions(model, *this);
  build_tables();

  if (std::getenv("SYSMODEL_WATCH_PROFILE") != nullptr && !profile_mode_) {
    profile_mode_ = true;
    for (PlacementTable& t : tables_) t.chunk_moves.assign(t.chunks.size(), 0);
    std::atexit([] { ModelBindings::instance().report_hot_chains(); });
  }
  if (std::getenv("SYSMODEL_WATCH_STATS") != nullptr) {
    std::atexit([] { ModelBindings::instance().report_watch_activity(); });
    const WatchStats st = watch_stats();
    std::fprintf(stderr,
                 "[WATCH] lines=%zu fields=%zu evaluators=%zu always=%zu legacy=%zu check_only=%zu\n",
                 st.chunks, st.fields, st.evaluators, st.always, st.legacy, st.check_only);
    for (int p = 0; p < 5; ++p) {
      const PlacementTable& t = tables_[p];
      std::vector<std::uintptr_t> field_lines;
      for (const FieldBuild& f : field_builds_)
        if (static_cast<int>(f.placement) == p)
          field_lines.push_back(reinterpret_cast<std::uintptr_t>(f.addr) >> 6);
      std::sort(field_lines.begin(), field_lines.end());
      field_lines.erase(std::unique(field_lines.begin(), field_lines.end()), field_lines.end());
      std::fprintf(stderr, "[WATCH] %s: region_lines=%zu fields=%zu field_lines=%zu always=%zu legacy=%zu\n",
                   placement_name(static_cast<SamplePlacement>(p)), t.chunks.size(),
                   t.field_count, field_lines.size(), t.always_evals.size(), t.legacy.size());
    }
    for (std::size_t b = 0; b < batches_.size(); ++b)
      std::fprintf(stderr, "[WATCH] batch %zu: base %d %s evaluator %d check_only %d\n", b,
                   batches_[b].base, placement_name(batches_[b].placement),
                   batches_[b].evaluator, batches_[b].check_only ? 1 : 0);
    for (std::size_t i = 0; i < evaluators_.size(); ++i)
      if (evaluators_[i].always)
        std::fprintf(stderr, "[WATCH] always-on evaluator %zu (%s, base %d, slot %d, lane %d)\n", i,
                     placement_name(evaluators_[i].placement), evaluators_[i].base,
                     evaluators_[i].slot,
                     evaluators_[i].slot >= 0 ? lane_of_slot(evaluators_[i].base + evaluators_[i].slot) : -1);
  }
}

/** Store for batch samplers: `slots` is the batch's view of its slots'
  * manifest lanes; the value lands masked in the record (scratch slots map
  * to the pad lane, which the record drops). */
using BatchSlots = ModelBindings::BatchSlots;
inline void batch_store(BatchSlots slots, std::size_t k, uint64_t value) {

  uint64_t& held = slots.values[k];
  if (held == value) return;
  held = value;
  slots.owner->commit_lane(slots.lanes[k], value);
}

/** Install every subsystem's bindings. Call once, before registration. */
void register_model_bindings();
/** Memory-side and uncore contract streams -> the model image (generated). */
void export_memory_image(const SystemGuider& m, chisa::boom_model::Image& I);
/** The cold-sidecar part of the above, written before the position is published. */
void export_memory_image_early(const SystemGuider& m, chisa::boom_model::Image& I);
// Defined in model_bringup_probes.cpp; no-op unless SYSMODEL_CORE_LIVE=1.
void register_core_bringup_probes_if_enabled();

/** Join the generated manifest obligation to the bindings above. */
void register_model_streams();

}  // namespace chisa::boom_system
