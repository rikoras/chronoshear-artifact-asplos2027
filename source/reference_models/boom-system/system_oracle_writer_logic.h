#pragma once
#include <type_traits>
#include "oracle_prefetch_cursor.h"
#include "image_copy.h"
#include <vector>
#include <new>
#include <immintrin.h>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include "../boom_model/common/diagnostic_monitor.h"
#if defined(CHISA_MODEL_DIAGNOSTICS)
#include "diagnostic_image_audit.h"
#endif
#ifdef CHISA_PHASE_TIMERS
#include <x86intrin.h>
#endif
// Hand-written writer logic for the oracle transport.  The generated
// system_oracle_writer*.inc files emit only the per-width constants and
// the kSystemOracleStreams table, then include this header, so the logic
// is normal source code instead of Python string literals inside the
// generator.  Depends on the constants, the spec table, model_bindings.h
// and the generated OracleRecord, all provided by the including file.
//
// Wire format (one block per 2W-cycle window):
//
//   0     u32 magic          kOracleCompactMagic
//   4     u32 positions      positions sealed so far (resealed at every
//                            position, so a partially produced window
//                            decodes correctly for what is already there)
//   8     u32 list_end       bytes of the change area used so far
//   12    ..64               reserved
//   64    u32 end[128]       change-area end offset after each position
//   576   base record        the OracleRecord at position 0
//   5120  change area        per position, in position order: entries of
//                            16 bytes {dst u32, lane u16, pad u16, value
//                            u64} -- the lanes whose record value moved
//                            during that cycle (position 0: moved since
//                            the previous window's last cycle).  dst is
//                            the lane's placement in the consumer's
//                            expansion buffer (byte offset of its 2W
//                            elements in the low 24 bits, element width in
//                            the high 8), so the consumer needs no lane
//                            table.  A position whose list overflowed is
//                            one marker entry (lane 0xffff) followed by
//                            the whole record image.
//
// Change detection happens where values are stored: every sampled or
// predicted lane goes through OracleRecord::store_if_changed, and the
// bindings append the lane to the current position's list when it moved.
// The writer only seals: it copies the list (with the current values) into
// the block.  The consumer fills exactly the listed lanes
// (oracle_delta_codec.h) and never compares records.

namespace chisa::boom_system {

inline constexpr std::uint32_t kOracleCompactMagic = 0x39574f52u;  // "ROW9"
inline constexpr std::size_t kOracleCompactHeaderBytes = 64;
inline constexpr std::size_t kOracleCompactIndexEntries = 128;  // 2W <= 128
inline constexpr std::size_t kOracleCompactBaseOffset =
    kOracleCompactHeaderBytes + kOracleCompactIndexEntries * 4;  // 576
inline constexpr std::size_t kOracleCompactListOffset =
    kOracleCompactBaseOffset + kOracleRecordPaddedBytes;  // 5120
inline constexpr std::size_t kOracleChangeEntryBytes = 16;
inline constexpr std::uint16_t kOracleChangeOverflowLane = 0xffffu;
// Row transport (SystemOracleWriter::set_row_mode(true)): the record is
// compared with a shadow copy 64-byte row by 64-byte row at the Registers
// point of every cycle, and each row that differs is appended to the
// position's list as one entry: the change-entry header with the row's
// record offset in the dst field and kOracleRowLane in the lane field,
// followed by the 64 row bytes.  Predicted lanes still travel as ordinary
// change entries.  No lane bookkeeping happens on the producer; the
// consumer resolves the rows into lanes (oracle_delta_codec.h) against its
// own shadow, so a row that moved only in bytes outside a lane costs it
// nothing but the compare.
inline constexpr std::uint16_t kOracleRowLane = 0xfffeu;
inline constexpr std::size_t kOracleRowEntryBytes = kOracleChangeEntryBytes + kOracleRecordChunkBytes;
static_assert(kOracleRecordPaddedBytes % kOracleRecordChunkBytes == 0,
              "row transport needs a whole number of 64-byte rows");
static_assert(kSystemOracleCyclesPerWindow <= kOracleCompactIndexEntries,
              "window index table too small for this width");

// Image form (SystemOracleWriter::set_image_mode(true)): one block per
// window holds
//
//   0     u32 magic          kOracleImageMagic
//   4     u32 positions      positions sealed so far
//   8     u32 image_bytes    kOracleRecordPaddedBytes
//   12    ..64               reserved
//   64    2W record images   position p at 64 + p * kOracleRecordPaddedBytes:
//                            the whole OracleRecord as it stood at the
//                            Registers point of that cycle, with the
//                            predict-bound lanes patched in at the cycle end.
//
// No change detection between the bindings and the block: the bindings
// mask every moved value straight into their record (ModelBindings image
// mode) and the writer copies that image.  Decoded by oracle_image_codec.h.
/** 64-byte aligned storage for window blocks (std::vector<char,
  * OracleBlockAllocator<char>>): the record images start on cache lines,
  * which the streaming-store copy requires and the write-ahead prefetch
  * assumes. */
template <class T>
struct OracleBlockAllocator {
  using value_type = T;
  OracleBlockAllocator() = default;
  template <class U>
  OracleBlockAllocator(const OracleBlockAllocator<U>&) {}
  T* allocate(std::size_t n) {
    void* p = nullptr;
    if (posix_memalign(&p, 64, n * sizeof(T) + 64) != 0) throw std::bad_alloc();
    return static_cast<T*>(p);
  }
  void deallocate(T* p, std::size_t) { std::free(p); }
  template <class U>
  bool operator==(const OracleBlockAllocator<U>&) const { return true; }
  template <class U>
  bool operator!=(const OracleBlockAllocator<U>&) const { return false; }
};
using OracleBlockBytes = std::vector<char, OracleBlockAllocator<char>>;

inline constexpr std::uint32_t kOracleImageMagic = 0x39474d49u;  // "IMG9"
inline constexpr std::size_t kOracleImageHeaderBytes = 64;
inline constexpr std::size_t oracle_image_block_bytes() {
  return kOracleImageHeaderBytes +
         static_cast<std::size_t>(kSystemOracleCyclesPerWindow) * kOracleRecordPaddedBytes;
}

/** Worst case per position: a full change list, the overflow marker with a
  * record image, or every row plus every predicted lane, whichever is
  * largest. */
inline constexpr std::size_t oracle_compact_position_capacity() {
  const std::size_t list = ModelBindings::kChangeCapacity * kOracleChangeEntryBytes;
  const std::size_t image = kOracleChangeEntryBytes + kOracleRecordPaddedBytes;
  const std::size_t rows = (kOracleRecordPaddedBytes / kOracleRecordChunkBytes) * kOracleRowEntryBytes +
                           ModelBindings::kPredictedCapacity * kOracleChangeEntryBytes;
  const std::size_t most = list > image ? list : image;
  return most > rows ? most : rows;
}
inline constexpr std::size_t oracle_compact_capacity() {
  return kOracleCompactListOffset +
         static_cast<std::size_t>(kSystemOracleCyclesPerWindow) *
             oracle_compact_position_capacity();
}
static_assert(oracle_image_block_bytes() <= oracle_compact_capacity(),
              "an image block must fit the compact block buffers");

class SystemOracleWriter {
 public:
  SystemOracleWriter() {
    register_model_bindings();
    ModelBindings& bindings = ModelBindings::instance();
    bindings.set_list_predicted(!image_mode_);
    static_assert(kSystemOracleModeledStreams == kOracleRecordLanes,
                  "writer stream table and oracle record disagree");
    for (std::size_t index = 0; index < kSystemOracleModeledStreams; ++index) {
      const SystemOracleStreamSpec& spec = kSystemOracleStreams[index];
      if (kOracleRecordLane[index].bytes != spec.elem_bytes ||
          kOracleRecordLane[index].width != spec.width)
        throw std::runtime_error(std::string("system-oracle record shape drift: ") +
                                 spec.trace_key);
      // Transport placement is required even for a migration-only unbound
      // lane: write_record() deliberately mutates every lane in codec tests,
      // and its change entry must never inherit LaneCell's sentinel offset.
      ModelBindings::LaneCell& cell =
          bindings.lane_cell(static_cast<std::uint16_t>(index));
      if (spec.block_offset >= (1u << 24))
        throw std::runtime_error("system-oracle expansion buffer exceeds 16 MB");
      cell.offset = spec.block_offset;
      cell.bytes = spec.elem_bytes;

      const ModelBinding* binding = bindings.find(spec.trace_key);
      if (binding == nullptr ||
          (binding->predict == nullptr && binding->sampled_slot < 0)) {
#if defined(CHISA_LARGE_MIGRATION_OVERRIDE)
        // Unbound during the Large migration: the lane is transported but
        // never written by the model; the record keeps it zero.
        continue;
#else
        throw std::runtime_error(std::string("missing system-oracle binding: ") +
                                 spec.trace_key);
#endif
      }
      if (!binding_matches(spec.kind, binding->timing))
        throw std::runtime_error(std::string("unproved system-oracle timing: ") +
                                 spec.trace_key + " manifest=" +
                                 oracle_kind_name(spec.kind) + " binding=" +
                                 binding_timing_name(binding->timing));
      // Lane == manifest index: the record was generated from the same
      // qualification, and every sampled slot must resolve to its lane.
      if (binding->sampled_slot >= 0 &&
          bindings.lane_of_slot(binding->sampled_slot) !=
              static_cast<int>(index))
        throw std::runtime_error(std::string("system-oracle lane mismatch: ") +
                                 spec.trace_key);
    }
  }

  static int element_index(int position) {
    if (position < 0 || position >= kSystemOracleCyclesPerWindow)
      throw std::out_of_range("system-oracle window position");
    return position < kSystemOracleWidth
        ? position : 3 * kSystemOracleWidth - 1 - position;
  }

  /** Seal this cycle: the sampled lanes already sit in the bindings' record
    * (stored at the start of the step, with the moved lanes listed); the
    * predict-bound lanes are evaluated here, after the step, through the
    * same path; then the position's list is copied into the block.  The
    * block is the buffer of oracle_compact_capacity() bytes. */
  /** Registers phase (cycle start): position `position` receives the
    * lanes whose sampled value moved since the previous seal; position 0
    * also takes the base record.  The index is not closed yet. */
  void flush_registers(char* block, int position, const SystemGuider* model = nullptr) {
    // The predicted-lane list is built lazily; build it here, on the calling
    // thread, before the memory worker's first PredictedMemory call of this
    // cycle can race a build of its own.
    (void)ModelBindings::instance().predicted_lanes();
    flush_registers_from(ModelBindings::instance(), block, position, model);
  }
  /** Image staging: image positions go to a small ring of `positions`
    * record images at `base` (position p at base + (p % positions) *
    * kOracleRecordPaddedBytes) instead of into the window block, and another
    * thread copies them into the block and writes its header.  The
    * producer's copy then stays inside its own L2 instead of streaming
    * through the shared window ring (4.8 MB live), whose cold lines cost an
    * ownership transfer each and evict the model's code and data. */
  void set_image_staging(char* base, unsigned positions) {
    if (kSystemOracleCyclesPerWindow % positions != 0) std::abort();  // ring index = position % positions across windows
    staging_ = base;
    staging_positions_ = positions;
  }
  /** The image position the next step publishes into, when it is known and
    * free (the staging ring's next slot, or the next position of the window
    * block), else nullptr.  The committing frontend thread copies its record
    * runs there ahead of the publish (SystemGuider::set_image_precopy_hook). */
  char* next_image_destination(char* block, int position, bool next_slot_free) const {
    if (!image_mode_ || !next_slot_free) return nullptr;
    if (staging_ != nullptr) return image_destination(block, position + 1);
    return position + 1 < kSystemOracleCyclesPerWindow ? image_destination(block, position + 1) : nullptr;
  }
  char* image_destination(char* block, int position) const {
    return staging_ != nullptr
        ? staging_ + static_cast<std::size_t>(static_cast<unsigned>(position) % staging_positions_) *
                         kOracleRecordPaddedBytes
        : block + kOracleImageHeaderBytes +
              static_cast<std::size_t>(position) * kOracleRecordPaddedBytes;
  }
  /** Image transport on/off (before the first step; also switches the
    * bindings' store path). */
  void set_image_mode(bool on) {
    image_mode_ = on;
    if (on) row_mode_ = false;
    ModelBindings::instance().set_image_mode(on);
    ModelBindings::instance().set_list_predicted(!on);
  }
  bool image_mode() const { return image_mode_; }
#if defined(CHISA_MODEL_DIAGNOSTICS)
  void enable_owner_diagnostics() { diagnostic_deferred_=true; }
  void diagnostic_seal(const char* block, std::uint64_t first) {
    if (!diagnostic_deferred_ || !image_mode_) return;
    for (unsigned p=0; p<kSystemOracleCyclesPerWindow; ++p)
      diagnostic_audit_.verify(first+p,reinterpret_cast<const unsigned char*>(
          block+kOracleImageHeaderBytes+p*kOracleRecordPaddedBytes),p);
    diagnostic_window(block,first+kSystemOracleCyclesPerWindow-1,kSystemOracleCyclesPerWindow-1);
  }
#endif
  /** Row transport on/off (before the first step; see kOracleRowLane). */
  void set_row_mode(bool on) {
    row_mode_ = on;
    if (on) image_mode_ = false;
    ModelBindings::instance().set_list_predicted(!image_mode_);
  }
  bool row_mode() const { return row_mode_; }
  /** Same sealing against any source exposing the bindings' export
    * surface (record/change list/lane cells); the export thread's mirror
    * is the second source, so both paths share one block-layout
    * implementation. */
  static void copy_image_out(char* dst, const unsigned char* src, std::size_t n) {
    static const bool changed = [] {
      const char* value=std::getenv("SYSMODEL_IMAGE_CHANGED_LINES");
      return value && value[0]=='1';
    }();
    if (changed) { copy_changed_image_lines(dst,src,n);return; }
    static const bool stream = std::getenv("SYSMODEL_IMAGE_STREAM") != nullptr;
#if defined(__AVX512F__)
    if (stream && (reinterpret_cast<std::uintptr_t>(dst) & 63u) == 0 && (n & 63u) == 0) {
      for (std::size_t i = 0; i < n; i += 64)
        _mm512_stream_si512(reinterpret_cast<__m512i*>(dst + i),
                            _mm512_loadu_si512(reinterpret_cast<const void*>(src + i)));
      _mm_sfence();
      return;
    }
#endif
    std::memcpy(dst, src, n);
  }
  template <class Source>
  void flush_registers_from(Source& bindings, char* block, int position,
                            const SystemGuider* model = nullptr) {
    if (image_mode_) {
      CHISA_DIAG(if (!diagnostic_deferred_) std::memcpy(diagnostic_expected_.bytes, bindings.record().bytes,
                             kOracleRecordPaddedBytes));
      // Image form: the source's record is current; copy it whole.  The
      // block is read by another core, so SYSMODEL_IMAGE_STREAM=1 streams the
      // copy past this core's cache instead of taking each line for
      // ownership (the Xeon mesh charges 100-200 ns per such line).
      char* destination = image_destination(block, position);
      std::size_t run_count = 0;
      const SystemGuider::ImageRun* runs = nullptr;
      if (model != nullptr) runs = model->precopied_image_runs(destination, run_count);
      if (run_count == 0) {
        CHISA_DIAG(if (diagnostic_deferred_) diagnostic_audit_.capture(::chisa::diagnostic::cycle(),bindings.record().bytes,0,kOracleRecordPaddedBytes));
        copy_image_out(destination, bindings.record().bytes, kOracleRecordPaddedBytes);
      } else {
        // The frontend's runs were copied by the thread that committed them;
        // copy the stretches between them.
        std::size_t at = 0;
        for (std::size_t i = 0; i < run_count; ++i) {
          if (runs[i].begin > at) {
            CHISA_DIAG(if (diagnostic_deferred_) diagnostic_audit_.capture(::chisa::diagnostic::cycle(),bindings.record().bytes,at,runs[i].begin-at));
            copy_image_out(destination + at, bindings.record().bytes + at, runs[i].begin - at);
          }
          if (runs[i].end > at) at = runs[i].end;
        }
        if (kOracleRecordPaddedBytes > at) {
          CHISA_DIAG(if (diagnostic_deferred_) diagnostic_audit_.capture(::chisa::diagnostic::cycle(),bindings.record().bytes,at,kOracleRecordPaddedBytes-at));
          copy_image_out(destination + at, bindings.record().bytes + at, kOracleRecordPaddedBytes - at);
        }
      }
      // SYSMODEL_IMAGE_PREFETCH=1: ask for the next position's destination
      // lines now, so their ownership transfers overlap the coming step
      // instead of stalling the next copy (the block lines are cold: the
      // ring slot was last written kRing windows ago and read by another
      // core since).  Pointless with staging, whose lines stay hot.
      static const bool prefetch_next = std::getenv("SYSMODEL_IMAGE_PREFETCH") != nullptr;
      if (prefetch_next && staging_ == nullptr && position + 1 < kSystemOracleCyclesPerWindow) {
        g_oracle_prefetch_cursor.next = block + kOracleImageHeaderBytes +
            static_cast<std::size_t>(position + 1) * kOracleRecordPaddedBytes;
        g_oracle_prefetch_cursor.remaining = kOracleRecordPaddedBytes;
        g_oracle_prefetch_cursor.drain_slice();  // the placements drain the rest
      }
      bindings.seal_changes();
      return;
    }
    if (row_mode_) {
      flush_rows(bindings, block, position);
      return;
    }
    // Lanes written straight into the record image (image-owned) join the
    // change list here; materialize_record then stores their cells back
    // unchanged.
    if constexpr (std::is_same_v<Source, ModelBindings>) bindings.sync_owned_changes();
    if (position == 0 || sealed_tracked_ || bindings.change_overflow())
      bindings.materialize_record();
    const OracleRecord& record = bindings.record();
    if (position == 0) {
      std::memcpy(block + kOracleCompactBaseOffset, record.bytes,
                  kOracleRecordPaddedBytes);
      list_end_ = 0;
      delta_count_ = 0;
    }
    if (sealed_tracked_)
      std::memcpy(sealed_.bytes, record.bytes, kOracleRecordPaddedBytes);
    char* area = block + kOracleCompactListOffset;
    if (bindings.change_overflow()) {
      const std::uint16_t marker = kOracleChangeOverflowLane;
      std::memset(area + list_end_, 0, kOracleChangeEntryBytes);
      // Change entries are {dst:u32, lane:u16, pad:u16, value:u64}; the
      // decoder recognizes an image marker in the lane field.
      std::memcpy(area + list_end_ + 4, &marker, 2);
      std::memcpy(area + list_end_ + kOracleChangeEntryBytes, record.bytes,
                  kOracleRecordPaddedBytes);
      list_end_ += kOracleChangeEntryBytes + kOracleRecordPaddedBytes;
      overflowed_position_ = true;
    } else {
      append_entries(bindings, area, bindings.changed_lanes(),
                     bindings.change_count(), position);
      overflowed_position_ = false;
    }
    bindings.seal_changes();
  }

  /** Predicted phase (cycle end): evaluate the predict-bound lanes from
    * the post-step state, append the ones that moved to `position`, patch
    * them into the base/sealed images, and close the position. */
  enum class PredictedSet { All, Core, Memory };
  /** Predicted lanes of the position: all of them, the core-side ones (the
    * calling thread, when a memory worker patches the memory-side ones) or
    * the memory-side ones (the memory worker, after its commit; the position
    * is closed by the core-side call). */
  void finish_position(const SystemGuider& model, char* block, int position,
                       PredictedSet set = PredictedSet::All) {
    ModelBindings& bindings = ModelBindings::instance();
    const auto selected = [set](const ModelBindings::PredictedLane& p) {
      return set == PredictedSet::All || (set == PredictedSet::Memory) == p.memory_side;
    };
    for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes())
      if (selected(p)) bindings.store_lane_predicted(p.lane, p.predict(model));
    if (image_mode_) {
      // The predicted lanes were just stored into the record: patch them
      // into this position's image and close the position.
      unsigned char* image = reinterpret_cast<unsigned char*>(image_destination(block, position));
      const OracleRecord& record = bindings.record();
      CHISA_DIAG(
        if (diagnostic_deferred_)
          for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes())
            if (selected(p)) {
              const auto& lane=kOracleRecordLane[p.lane];
              diagnostic_audit_.capture(::chisa::diagnostic::cycle(),record.bytes,lane.offset,lane.bytes);
            }
      );
      for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes())
        if (selected(p)) patch_lane(image, record, p.lane);
      if (set == PredictedSet::Memory) return;
      CHISA_DIAG(
        if (!diagnostic_deferred_) {
        for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes())
          patch_lane(diagnostic_expected_.bytes, record, p.lane);
        diagnostic_image(image, model.cycle() - 1, position);
        }
      );
      if (staging_ == nullptr) write_image_header(block, position);
      CHISA_DIAG(if (!diagnostic_deferred_) diagnostic_window(block, model.cycle() - 1, position));
      return;
    }
    if (row_mode_ && predicted_ids_.empty())
      for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes())
        predicted_ids_.push_back(p.lane);
    finish_position_from(bindings, block, position);
  }
  /** The predicted lanes are already evaluated and stored into `bindings`
    * (the model is only needed for that evaluation, which stays on the
    * model's thread). */
  template <class Source>
  void finish_position_from(Source& bindings, char* block, int position) {
    const OracleRecord& record = bindings.record();
    const std::uint16_t* lanes = bindings.predicted_changes();
    std::size_t count = bindings.predicted_change_count();
    if (row_mode_) {
      // A predicted lane holds its post-step value at this position.  The
      // model may have written that value itself, so the store above sees
      // no move; what counts is whether the record bytes differ from the
      // Registers-point image, which the row shadow still holds.
      predicted_moved_.clear();
      for (const std::uint16_t lane : predicted_ids_) {
        const OracleRecordLane& d = kOracleRecordLane[lane];
        if (std::memcmp(record.bytes + d.offset, row_shadow_.bytes + d.offset, d.bytes) != 0)
          predicted_moved_.push_back(lane);
      }
      lanes = predicted_moved_.data();
      count = predicted_moved_.size();
    }
    if (image_mode_) {
      // Image form: patch the predicted lanes that moved into this
      // position's image and close the position.
      unsigned char* image = reinterpret_cast<unsigned char*>(image_destination(block, position));
      for (std::size_t i = 0; i < count; ++i) patch_lane(image, record, lanes[i]);
      CHISA_DIAG(
        for (std::size_t i = 0; i < count; ++i)
          patch_lane(diagnostic_expected_.bytes, record, lanes[i]);
        diagnostic_image(image, ::chisa::diagnostic::cycle(), position);
      );
      bindings.seal_predicted();
      if (staging_ == nullptr) write_image_header(block, position);
      CHISA_DIAG(diagnostic_window(block, ::chisa::diagnostic::cycle(), position));
      return;
    }
    char* area = block + kOracleCompactListOffset;
    if (overflowed_position_) {
      // The record image shipped for this position must carry the
      // predicted values too.
      unsigned char* image = reinterpret_cast<unsigned char*>(
          area + list_end_ - kOracleRecordPaddedBytes);
      for (std::size_t i = 0; i < count; ++i) patch_lane(image, record, lanes[i]);
    } else {
      append_entries(bindings, area, lanes, count, position);
    }
    if (position == 0) {
      unsigned char* base = reinterpret_cast<unsigned char*>(block + kOracleCompactBaseOffset);
      for (std::size_t i = 0; i < count; ++i) patch_lane(base, record, lanes[i]);
    }
    if (sealed_tracked_)
      for (std::size_t i = 0; i < count; ++i) patch_lane(sealed_.bytes, record, lanes[i]);
    bindings.seal_predicted();
    const std::uint32_t end = static_cast<std::uint32_t>(list_end_);
    std::memcpy(block + kOracleCompactHeaderBytes + 4 * position, &end, 4);
    const std::uint32_t positions = static_cast<std::uint32_t>(position) + 1u;
    std::memcpy(block, &kOracleCompactMagic, 4);
    std::memcpy(block + 4, &positions, 4);
    std::memcpy(block + 8, &end, 4);
  }

  /** Tests only: keep an image of exactly what was sealed for the last
    * position (register lanes as flushed, predicted lanes as finished). */
  void track_sealed_image(bool on) { sealed_tracked_ = on; }

  /** Step the model one cycle and seal that cycle's oracle values into the
    * block at `position`.  The sealing happens inside step(), at the point
    * where the cycle's record is complete and before any component moves
    * on (the placed samplers write the next cycle's values afterwards). */
  /** `next_image_slot_free`: the caller vouches that the image position
    * after `position` may already be written during this step (a staging
    * ring slot the decoder has drained). */
  StepResult step_and_write(SystemGuider& model, char* block, int position,
                           SystemGuider::PublishFn observer = nullptr,
                           void* observer_context = nullptr,
                           bool next_image_slot_free = false) {
    // The memory worker publishes the previous position's memory-side
    // predicted lane through the previous context, until the step after the
    // next joins it: two contexts alternate, the worker holds the one of the
    // step that posted its request.
    PublishContext& context = contexts_[context_slot_ ^= 1u];
    context = PublishContext{this, block, position, observer, observer_context, next_image_slot_free};
    CHISA_DIAG(
      context.cycle=model.cycle();
      if (diagnostic_deferred_ && !diagnostic_hook_installed_) {
        model.set_image_source_observer(&SystemOracleWriter::diagnostic_source_thunk,this);
        diagnostic_hook_installed_=true;
      }
    );
    model.set_publish_hook(&SystemOracleWriter::publish_thunk, &context,
                           image_mode_ && observer==nullptr);
    model.set_image_precopy_hook(&SystemOracleWriter::precopy_thunk, &context);
    const StepResult result = model.step();
    // The hooks stay installed: the memory worker may still be publishing
    // this position.
    return result;
  }
#ifdef CHISA_PHASE_TIMERS
  // Main-thread publication only. Async memory publication has its own
  // owner and is already included in MemoryWorker's fabric-phase timing.
  std::uint64_t publish_ticks() const { return publish_tsc_; }
  std::uint64_t publish_copy_ticks() const { return publish_copy_tsc_; }
#endif

  /** The transport proper on an externally built record: `next` is applied
    * lane by lane through the same change-detecting store production uses.
    * Model-free, for codec tests. */
  void write_record(const OracleRecord& next, char* block, int position) {
    ModelBindings& bindings = ModelBindings::instance();
    for (std::size_t lane = 0; lane < kOracleRecordLanes; ++lane)
      bindings.store_lane(static_cast<std::uint16_t>(lane), next.load(lane));
    flush_registers(block, position);
    // No predict-bound lanes without a model: close the position directly.
    const std::uint32_t end = static_cast<std::uint32_t>(list_end_);
    std::memcpy(block + kOracleCompactHeaderBytes + 4 * position, &end, 4);
    const std::uint32_t positions = static_cast<std::uint32_t>(position) + 1u;
    std::memcpy(block, &kOracleCompactMagic, 4);
    std::memcpy(block + 4, &positions, 4);
    std::memcpy(block + 8, &end, 4);
  }

  /** The image of the last sealed position (track_sealed_image(true)). */
  const OracleRecord& record() const { return sealed_; }

  std::size_t lane_count() const { return kOracleRecordLanes; }
  /** Change entries written at positions >= 1 of the current window. */
  std::uint32_t last_delta_count() const { return delta_count_; }

  /** Value of one stream at one window position in the EXPANDED
    * (historical window-major) block. */
  static std::uint64_t read_position(const char* block, std::size_t stream,
                                     int position) {
    if (block == nullptr || stream >= kSystemOracleModeledStreams)
      throw std::out_of_range("system-oracle read");
    const SystemOracleStreamSpec& spec = kSystemOracleStreams[stream];
    const char* source = block + spec.block_offset +
                         element_index(position) * spec.elem_bytes;
    std::uint64_t value = 0;
    for (unsigned byte = 0; byte < spec.elem_bytes; ++byte)
      value |= static_cast<std::uint64_t>(
          static_cast<unsigned char>(source[byte])) << (8u * byte);
    return value;
  }

 private:
#if defined(CHISA_MODEL_DIAGNOSTICS)
  void diagnostic_image(const unsigned char* image, std::uint64_t cycle, int position) {
    using namespace ::chisa::diagnostic;
    std::size_t first = kOracleRecordPaddedBytes;
    for (std::size_t byte = 0; byte < kOracleRecordPaddedBytes; ++byte)
      if (image[byte] != diagnostic_expected_.bytes[byte]) { first = byte; break; }
    require("transport", "record-to-image", cycle, Layer::Transport, Phase::Post,
      first == kOracleRecordPaddedBytes,
      {{"position", static_cast<std::uint64_t>(position)}, {"first_byte", first},
       {"expected", first < kOracleRecordPaddedBytes ? diagnostic_expected_.bytes[first] : 0u},
       {"actual", first < kOracleRecordPaddedBytes ? image[first] : 0u}});
  }
  void diagnostic_window(const char* block, std::uint64_t cycle, int position) {
    if (position + 1 != kSystemOracleCyclesPerWindow) return;
    const bool known = cycle != ::chisa::diagnostic::unknown_cycle &&
                       cycle >= static_cast<std::uint64_t>(position);
    ::chisa::diagnostic::require("transport", "window-cycle", cycle,
      ::chisa::diagnostic::Layer::Transport, ::chisa::diagnostic::Phase::Window, known,
      {{"position", static_cast<std::uint64_t>(position)}});
    ::chisa::diagnostic::checkpoint("transport", "sealed-image",
      known ? cycle - position : ::chisa::diagnostic::unknown_cycle,
      ::chisa::diagnostic::Layer::Transport,
      {{"bytes", oracle_image_block_bytes()},
       {"digest", ::chisa::diagnostic::digest(block, oracle_image_block_bytes())}});
  }
  OracleRecord diagnostic_expected_{};
  DiagnosticImageAudit<kOracleRecordPaddedBytes> diagnostic_audit_;
  bool diagnostic_deferred_=false, diagnostic_hook_installed_=false;
  static void diagnostic_source_thunk(void* context, std::uint64_t cycle,
      const unsigned char* source, std::size_t begin, std::size_t bytes) {
    static_cast<SystemOracleWriter*>(context)->diagnostic_audit_.capture(cycle,source,begin,bytes);
  }
#endif
  struct alignas(64) PublishContext {
    SystemOracleWriter* writer;
    char* block;
    int position;
    SystemGuider::PublishFn observer;
    void* observer_context;
    bool next_image_slot_free;
#if defined(CHISA_MODEL_DIAGNOSTICS)
    std::uint64_t cycle=0;
#endif
  };
  PublishContext contexts_[2]{};
  unsigned context_slot_ = 0;
  static char* precopy_thunk(void* context) {
    PublishContext* ctx = static_cast<PublishContext*>(context);
    return ctx->writer->next_image_destination(ctx->block, ctx->position, ctx->next_image_slot_free);
  }
  static void publish_thunk(void* context, const SystemGuider& model,
                            SystemGuider::PublishPhase phase) {
    PublishContext* ctx = static_cast<PublishContext*>(context);
#if defined(CHISA_MODEL_DIAGNOSTICS)
    struct CycleScope {
      std::uint64_t old=::chisa::diagnostic::cycle();
      explicit CycleScope(std::uint64_t cycle) { ::chisa::diagnostic::set_cycle(cycle); }
      ~CycleScope() { ::chisa::diagnostic::set_cycle(old); }
    } diagnostic_cycle{ctx->cycle};
#endif
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
    if (ctx->observer != nullptr)
      ctx->observer(ctx->observer_context, model, phase);
    if (phase == SystemGuider::PublishPhase::Registers)
      ctx->writer->flush_registers(ctx->block, ctx->position, &model);
    else if (phase == SystemGuider::PublishPhase::PredictedMemory)
      ctx->writer->finish_position(model, ctx->block, ctx->position, PredictedSet::Memory);
    else
      ctx->writer->finish_position(model, ctx->block, ctx->position,
                                   model.memory_worker_on() ? PredictedSet::Core : PredictedSet::All);
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t dt = __rdtsc() - t0;
    // PredictedMemory can run concurrently with Registers/PredictedCore.
    // Sharing this accumulator was a diagnostic data race and bounced the
    // writer's metadata line between the producer and memory worker.
    if (phase != SystemGuider::PublishPhase::PredictedMemory)
      ctx->writer->publish_tsc_ += dt;
    if (phase == SystemGuider::PublishPhase::Registers) ctx->writer->publish_copy_tsc_ += dt;
#endif
  }

  static void patch_lane(unsigned char* image, const OracleRecord& record,
                         std::uint16_t lane) {
    const OracleRecordLane& d = kOracleRecordLane[lane];
    std::memcpy(image + d.offset, record.bytes + d.offset, d.bytes);
  }

  template <class Source>
  void append_entries(Source& bindings, char* area,
                      const std::uint16_t* lanes, std::size_t count,
                      int position) {
    char* entry = area + list_end_;
    for (std::size_t i = 0; i < count; ++i, entry += kOracleChangeEntryBytes) {
      const std::uint16_t lane = lanes[i];
      const ModelBindings::LaneCell& cell = bindings.lane_cell(lane);
      const std::uint32_t dst = cell.offset | (static_cast<std::uint32_t>(cell.bytes) << 24);
      // The value lives in the record when the bindings run in image mode
      // (row transport, predicted lanes) and in the cell otherwise.
      const std::uint64_t value = bindings.lane_value(lane);
      std::memcpy(entry, &dst, 4);
      std::memcpy(entry + 4, &lane, 2);
      entry[6] = 0;
      entry[7] = 0;
      std::memcpy(entry + 8, &value, 8);
    }
    list_end_ += count * kOracleChangeEntryBytes;
    if (position > 0) delta_count_ += static_cast<std::uint32_t>(count);
  }
  /** Row transport, Registers point: append every 64-byte row of the record
    * that differs from the shadow, and refresh the shadow.  Position 0 also
    * carries the whole record as the window's base. */
  template <class Source>
  void flush_rows(Source& bindings, char* block, int position) {
    const OracleRecord& record = bindings.record();
    if (position == 0) {
      std::memcpy(block + kOracleCompactBaseOffset, record.bytes, kOracleRecordPaddedBytes);
      list_end_ = 0;
      delta_count_ = 0;
    }
    if (sealed_tracked_)
      std::memcpy(sealed_.bytes, record.bytes, kOracleRecordPaddedBytes);
    char* area = block + kOracleCompactListOffset;
    const unsigned char* rec = record.bytes;
    unsigned char* shadow = row_shadow_.bytes;
    // Pass 1, branch-free: one bit per row that differs from the shadow (a
    // data-dependent branch per row mispredicts on a third of the rows).
    constexpr std::size_t kRows = kOracleRecordPaddedBytes / kOracleRecordChunkBytes;
    constexpr std::size_t kWords = (kRows + 63) / 64;
    std::uint64_t moved[kWords] = {};
    for (std::size_t row = 0; row < kRows; ++row) {
      const std::size_t at = row * kOracleRecordChunkBytes;
#if defined(__AVX512BW__)
      const __m512i a = _mm512_load_si512(reinterpret_cast<const void*>(rec + at));
      const __m512i b = _mm512_load_si512(reinterpret_cast<const void*>(shadow + at));
      const std::uint64_t differs = _mm512_cmpneq_epi8_mask(a, b) != 0;
#else
      const std::uint64_t differs = std::memcmp(rec + at, shadow + at, kOracleRecordChunkBytes) != 0;
#endif
      moved[row >> 6] |= differs << (row & 63);
    }
    // Pass 2: ship and shadow the rows that moved.
    for (std::size_t w = 0; w < kWords; ++w) {
      std::uint64_t bits = moved[w];
      while (bits != 0) {
        const std::size_t row = (w << 6) | static_cast<std::size_t>(__builtin_ctzll(bits));
        bits &= bits - 1;
        const std::size_t at = row * kOracleRecordChunkBytes;
        char* entry = area + list_end_;
        write_row_header(entry, static_cast<std::uint32_t>(at));
#if defined(__AVX512BW__)
        const __m512i a = _mm512_load_si512(reinterpret_cast<const void*>(rec + at));
        _mm512_storeu_si512(reinterpret_cast<void*>(entry + kOracleChangeEntryBytes), a);
        _mm512_store_si512(reinterpret_cast<void*>(shadow + at), a);
#else
        std::memcpy(entry + kOracleChangeEntryBytes, rec + at, kOracleRecordChunkBytes);
        std::memcpy(shadow + at, rec + at, kOracleRecordChunkBytes);
#endif
        list_end_ += kOracleRowEntryBytes;
        if (position > 0) ++delta_count_;
      }
    }
    overflowed_position_ = false;
    bindings.seal_changes();
  }
  /** Image block header: magic, positions sealed so far, image bytes. */
  static void write_image_header(char* block, int position) {
    const std::uint32_t positions = static_cast<std::uint32_t>(position) + 1u;
    const std::uint32_t image_bytes = static_cast<std::uint32_t>(kOracleRecordPaddedBytes);
    std::memcpy(block, &kOracleImageMagic, 4);
    std::memcpy(block + 4, &positions, 4);
    std::memcpy(block + 8, &image_bytes, 4);
  }
  static void write_row_header(char* entry, std::uint32_t row_offset) {
    const std::uint16_t lane = kOracleRowLane;
    std::memcpy(entry, &row_offset, 4);
    std::memcpy(entry + 4, &lane, 2);
    std::memset(entry + 6, 0, kOracleChangeEntryBytes - 6);
  }
#ifdef CHISA_PHASE_TIMERS
  std::uint64_t publish_tsc_ = 0;
  std::uint64_t publish_copy_tsc_ = 0;
#endif

  std::size_t list_end_ = 0;
  std::uint32_t delta_count_ = 0;
  bool overflowed_position_ = false;
  bool image_mode_ = false;
  bool row_mode_ = false;
  char* staging_ = nullptr;          // image staging ring (set_image_staging)
  unsigned staging_positions_ = 0;
  bool sealed_tracked_ = false;
  OracleRecord sealed_{};
  OracleRecord row_shadow_{};  // row transport: the record as last flushed
  std::vector<std::uint16_t> predicted_ids_;    // row transport: registered predicted lanes
  std::vector<std::uint16_t> predicted_moved_;  // row transport: the ones shipped this position
};

}  // namespace chisa::boom_system
