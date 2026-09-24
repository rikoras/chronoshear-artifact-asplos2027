// Export offload: the model's thread ships what the export side needs
// through ExportRing -- the changed 8-byte groups of moved unified rows,
// moved values as (lane, value) pairs, and the per-position control marks --
// and does none of the export work itself.  A worker keeps the export state
// (lane cells, record image, change lists, a copy of the unified rows) and
// runs field resolution, the writer's flushing and the block sealing against
// it, through the writer's templated implementation (flush_registers_from /
// finish_position_from).  With a faithful mirror the block bytes are
// identical to the in-thread path (bench digest; live --dump-blocks hash).
//
// The worker is either an own thread (bench) or a thread the owner already
// has (the live sidecar's expander thread drives drain()).  Shipping costs
// the model's thread about one cache-line transfer per 64 bytes shipped,
// so the records are compact: about 1.3 KB per cycle for the Small SoC.
//
// Predicted lanes are still evaluated on the model's thread (they read the
// model); only their (lane, value) results cross.
//
// Include after the generated writer .inc (SystemOracleWriter must be
// complete).

#pragma once

#include <immintrin.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <thread>
#include <vector>

namespace chisa::boom_system {

class ExportThread {
 public:
  /** `model`: attach the bindings to it first when they are not yet (the
    * live sidecar constructs the exporter before the first step; the bench
    * after its initialization phase).  `own_thread`: run the export work on
    * a thread started here; otherwise the owner drives it through drain()
    * from exactly one thread. */
  explicit ExportThread(SystemOracleWriter& writer, const SystemGuider* model = nullptr,
                        bool own_thread = true)
      : writer_(writer), ring_(ring_bytes_from_env()), own_thread_(own_thread) {
    ModelBindings& b = ModelBindings::instance();
#if defined(CHISA_WIDE_MODEL)
    b.set_image_mode(writer_.image_mode());
#endif
    if (model != nullptr && b.attached_ != model) b.attach(*model);
#if defined(CHISA_WIDE_MODEL)
    native_active_ = b.native_image_enabled();
    if (native_active_) native_shadow_ = b.record();
#endif
    // Lane cells: the writer's precomputed destinations plus the values as
    // of now; the record image follows the values.
    for (std::size_t lane = 0; lane < kOracleRecordLanes; ++lane) {
      mirror_.cells[lane] = b.lane_cell(static_cast<std::uint16_t>(lane));
      mirror_.image.store(static_cast<std::uint16_t>(lane), mirror_.cells[lane].value);
    }
    if (writer.image_mode()) {
      // Image transport: the bindings' record is the current image (the
      // lane cells are not maintained in that mode).
      mirror_.image = b.record();
      for (std::size_t lane = 0; lane < kOracleRecordLanes; ++lane)
        mirror_.cells[lane].value = mirror_.image.load(lane);
    }
    // The pending change lists cross as they are (an ROI start typically
    // finds the list overflowed, so the first flush writes the image).
    mirror_.n_changes = b.change_count();
    std::memcpy(mirror_.changed.data(), b.changed_lanes(),
                mirror_.n_changes * sizeof(std::uint16_t));
    mirror_.n_predicted = b.predicted_change_count();
    std::memcpy(mirror_.predicted.data(), b.predicted_changes(),
                mirror_.n_predicted * sizeof(std::uint16_t));
    b.seal_changes();
    b.seal_predicted();
    // Unified rows: start from the diff shadow (the rows as of the last
    // cycle-start diff, which is where the shipped rows continue from) and
    // resolve every field's offset inside the dense row copy.
#if defined(CHISA_WIDE_MODEL)
    if (native_active_) {
      mirror_.native_image = true;
      std::memcpy(lane_bits_, b.lane_bits_, sizeof(lane_bits_));
      ring_.set_rows_capacity(kOracleRecordChunks);
    } else
#endif
    {
    rows_ = b.unified_row_src_.size();
    rows_bytes_.assign(rows_ * 64 + 64, 0);
    if (rows_ != 0) std::memcpy(rows_bytes_.data(), b.unified_shadow_, rows_ * 64);
    row_byte_field_ = b.unified_row_byte_field_;
    claimed_ = b.unified_row_claimed_;
    ring_.set_rows_capacity(rows_);
    std::memcpy(lane_bits_, b.lane_bits_, sizeof(lane_bits_));
    fields_.assign(b.unified_flat_.size(), Field{});
    std::vector<bool> seen(b.unified_flat_.size(), false);
    for (std::size_t i = 0; i < rows_; ++i) {
      std::uint64_t claimed = b.unified_row_claimed_[i];
      while (claimed != 0) {
        const unsigned k = static_cast<unsigned>(__builtin_ctzll(claimed));
        claimed &= claimed - 1;
        const std::uint16_t fid = row_byte_field_[64 * i + k];
        if (fid == 0xffff || seen[fid]) continue;
        seen[fid] = true;
        const ModelBindings::UnifiedField& f = b.unified_flat_[fid];
        Field& m = fields_[fid];
        m.offset = static_cast<std::uint32_t>(64 * i + k);
        m.lane = f.lane;
        m.bits = f.bits;
        m.bytes = f.bytes;
        m.shift = f.shift;
        m.is_signed = f.is_signed;
        m.tail = f.tail;
      }
    }
    }
    b.set_export_ring(&ring_);
    // Experiment switch (blocks come out wrong): 1 = the worker drops the
    // data records and only acts on the control marks; 2 = the worker
    // consumes without reading the ring at all.
    if (const char* s = std::getenv("CHISA_EXPORT_SKIP_APPLY")) skip_mode_ = std::atoi(s);
    if (own_thread_) worker_ = std::thread([this] { run(); });
  }
  ~ExportThread() {
    if (own_thread_) {
      sync();
      stop_.store(true, std::memory_order_release);
      worker_.join();
    } else {
      ring_.publish();
      while (drain(1024) != 0) {
      }
    }
    ModelBindings::instance().set_export_ring(nullptr);
    if (std::getenv("CHISA_EXPORT_STATS") != nullptr && finishes_ != 0) {
      std::fprintf(stderr,
                   "EXPORT_RING cycles=%llu rows_per_cycle=%.2f pairs_per_cycle=%.2f "
                   "bytes_per_cycle=%.1f publishes_per_cycle=%.2f\n",
                   static_cast<unsigned long long>(finishes_),
                   static_cast<double>(ring_.stat_rows()) / static_cast<double>(finishes_),
                   static_cast<double>(ring_.stat_pairs()) / static_cast<double>(finishes_),
                   static_cast<double>(ring_.stat_bytes()) / static_cast<double>(finishes_),
                   static_cast<double>(ring_.stat_publishes()) / static_cast<double>(finishes_));
    }
  }
  ExportThread(const ExportThread&) = delete;
  ExportThread& operator=(const ExportThread&) = delete;

  /** Step the model one cycle; the two publish phases inside the step
    * become control marks in the ring.  Mirrors
    * SystemOracleWriter::step_and_write. */
  StepResult step_and_export(SystemGuider& model, char* block, int position) {
    Hook hook{this, block, position};
    model.set_publish_hook(&ExportThread::publish_thunk, &hook);
    const StepResult result = model.step();
    model.set_publish_hook(nullptr, nullptr);
    return result;
  }

  /** Window w's positions have all been stepped: once the worker passes
    * this mark, sealed_windows() reports w + 1 and the window's block may be
    * read.  Reset windows (no block) take the mark too, so the count stays
    * aligned with the producer's window numbering. */
  void mark_window(std::uint64_t w) {
    ring_.push_control(ExportRing::kWindow, w, 0);
  }
  std::uint64_t sealed_windows() const {
    return sealed_windows_.load(std::memory_order_acquire);
  }
  /** Without an own thread: apply up to `max_records` ring records; returns
    * how many were applied (0 = nothing pending).  Single caller thread. */
  std::size_t drain(std::size_t max_records) {
    ExportRing::Header h;
    const unsigned char* payload = nullptr;
    std::size_t n = 0;
    while (n < max_records && ring_.pop(h, payload)) {
      apply(h, payload);
      ring_.advance(h);
      ++n;
    }
    return n;
  }

  /** Own-thread mode: block until the worker has applied everything shipped
    * so far (the caller may then read the sealed block bytes). */
  void sync() {
    ring_.publish();
    while (!ring_.drained()) {
#if defined(__x86_64__)
      __builtin_ia32_pause();
#endif
    }
  }

#ifdef CHISA_PHASE_TIMERS
  /** Model-thread time spent in the publish hooks (the control marks and
    * the predicted-lane evaluation); the shipping of pairs and rows is
    * inside the sampling phase. */
  std::uint64_t producer_ticks() const { return hook_tsc_; }
#endif

 private:
  struct Hook {
    ExportThread* self;
    char* block;
    int position;
  };
  struct Field {
    std::uint32_t offset = 0;  // byte offset inside rows_bytes_
    std::uint16_t lane = 0;
    std::uint8_t bits = 0;
    std::uint8_t bytes = 0;
    std::uint8_t shift = 0;
    bool is_signed = false;
    bool tail = false;
    std::uint8_t pad = 0;
  };

#if defined(CHISA_WIDE_MODEL)
  void publish_native_image(const OracleRecord& image) {
    // This is a transport checkpoint, not a second model/slot image. The
    // worker receives already resolved bytes and performs no field sampling.
    for (std::size_t index = 0; index < kOracleRecordChunks; ++index) {
      const unsigned char* current = image.bytes + 64 * index;
      unsigned char* held = native_shadow_.bytes + 64 * index;
      std::uint64_t changed = 0;
#if defined(__AVX512BW__)
      const auto value = _mm512_loadu_si512(current);
      changed = _mm512_cmpneq_epi8_mask(value, _mm512_loadu_si512(held));
      if (changed != 0) _mm512_storeu_si512(held, value);
#else
      for (unsigned group = 0; group < 8; ++group) {
        std::uint64_t value, previous;
        std::memcpy(&value, current + 8 * group, 8);
        std::memcpy(&previous, held + 8 * group, 8);
        if (value != previous) changed |= UINT64_C(0xff) << (8 * group);
      }
      if (changed != 0) std::memcpy(held, current, 64);
#endif
      if (changed != 0)
        ring_.push_image_row(static_cast<std::uint32_t>(index), changed, current);
    }
  }
#endif

  static void publish_thunk(void* context, const SystemGuider& model,
                            SystemGuider::PublishPhase phase) {
    Hook* hook = static_cast<Hook*>(context);
    ExportThread* self = hook->self;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
    if (phase == SystemGuider::PublishPhase::Registers) {
#if defined(CHISA_WIDE_MODEL)
      if (self->native_active_)
        self->publish_native_image(ModelBindings::instance().record());
#endif
      self->ring_.push_control(ExportRing::kFlush,
                               reinterpret_cast<std::uint64_t>(hook->block), hook->position);
    } else {
      ModelBindings& bindings = ModelBindings::instance();
      for (const ModelBindings::PredictedLane& p : bindings.predicted_lanes()) {
        const auto value = p.predict(model);
        bindings.store_lane_predicted(p.lane, value);  // -> ring
#if defined(CHISA_WIDE_MODEL)
        // The worker applies this POST patch too. Updating only these lanes
        // keeps the checkpoint exact without capturing next-cycle register
        // values that component commits have already put in the live image.
        if (self->native_active_) self->native_shadow_.store(p.lane, value);
#endif
      }
      self->ring_.push_control(ExportRing::kFinish,
                               reinterpret_cast<std::uint64_t>(hook->block), hook->position);
    }
#ifdef CHISA_PHASE_TIMERS
    self->hook_tsc_ += __rdtsc() - t0;
#endif
  }

  static std::size_t ring_bytes_from_env() {
    int log2 = 23;  // 8 MiB
    if (const char* s = std::getenv("CHISA_EXPORT_RING_LOG2")) log2 = std::atoi(s);
    if (log2 < 16) log2 = 16;
    if (log2 > 28) log2 = 28;
    return std::size_t{1} << log2;
  }

  void run() {
    if (skip_mode_ == 2) {
      while (!stop_.load(std::memory_order_acquire)) {
        ring_.skip_all();
#if defined(__x86_64__)
        __builtin_ia32_pause();
#endif
      }
      ring_.skip_all();
      return;
    }
    while (true) {
      if (drain(1024) != 0) continue;
      if (stop_.load(std::memory_order_acquire) && drain(1024) == 0) return;
#if defined(__x86_64__)
      __builtin_ia32_pause();
#endif
    }
  }

  void apply(const ExportRing::Header& h, const unsigned char* payload) {
    char* block = reinterpret_cast<char*>(h.block);
    if (skip_mode_ == 1 && h.kind != ExportRing::kFlush && h.kind != ExportRing::kFinish &&
        h.kind != ExportRing::kWindow)
      return;
    switch (h.kind) {
      case ExportRing::kPad:
        break;
#if defined(CHISA_WIDE_MODEL)
      case ExportRing::kImageRows: {
        if (!native_active_ || !writer_.image_mode()) std::abort();
        const unsigned char* p = payload;
        const unsigned char* const end = payload + h.payload_bytes;
        while (p < end) {
          if (static_cast<std::size_t>(end - p) < ExportRing::kRowHeadBytes) std::abort();
          std::uint32_t head;
          std::memcpy(&head, p, ExportRing::kRowHeadBytes);
          p += ExportRing::kRowHeadBytes;
          const unsigned index = head & 0xffffu;
          const unsigned groups = (head >> 16) & 0xffu;
          const unsigned bytes = 8 * static_cast<unsigned>(__builtin_popcount(groups));
          if (index >= kOracleRecordChunks || static_cast<std::size_t>(end - p) < bytes)
            std::abort();
          unsigned char* row = mirror_.image.bytes + 64 * index;
#if defined(__AVX512F__)
          const auto value = _mm512_mask_expandloadu_epi64(
              _mm512_loadu_si512(row), static_cast<__mmask8>(groups), p);
          _mm512_storeu_si512(row, value);
          p += bytes;
#else
          unsigned remaining = groups;
          while (remaining != 0) {
            const unsigned group = static_cast<unsigned>(__builtin_ctz(remaining));
            remaining &= remaining - 1;
            std::memcpy(row + 8 * group, p, 8);
            p += 8;
          }
#endif
        }
        break;
      }
#endif
      case ExportRing::kPairs:
      case ExportRing::kPredicted: {
        const unsigned char* p = payload;
        const unsigned char* const end = payload + h.payload_bytes;
        while (p < end) {
          std::uint16_t lane;
          std::memcpy(&lane, p, 2);
          const unsigned n = (lane_bits_[lane] + 7u) >> 3;
          std::uint64_t value = 0;
          std::memcpy(&value, p + 2, n);
          p += 2 + n;
          if (h.kind == ExportRing::kPairs)
            mirror_.commit(lane, value);
          else
            mirror_.predict(lane, value);
        }
        break;
      }
      case ExportRing::kRows: {
        const unsigned char* p = payload;
        const unsigned char* const end = payload + h.payload_bytes;
        while (p < end) {
          std::uint32_t head;
          std::memcpy(&head, p, ExportRing::kRowHeadBytes);
          p += ExportRing::kRowHeadBytes;
          const std::uint32_t index = head & 0xffffu;
          const unsigned g = (head >> 16) & 0xffu;
          unsigned char* row = rows_bytes_.data() + 64 * index;
          // Place the shipped groups into the row copy; the moved-byte mask
          // is the difference against the previous copy over claimed bytes
          // (unclaimed bytes may lag, they are never read).
          std::uint64_t neq;
#if defined(__AVX512BW__)
          const __m512i old = _mm512_loadu_si512(row);
          const __m512i cur = _mm512_mask_expandloadu_epi64(old, static_cast<__mmask8>(g), p);
          neq = _mm512_cmpneq_epi8_mask(cur, old) & claimed_[index];
          _mm512_storeu_si512(row, cur);
          p += 8 * static_cast<unsigned>(__builtin_popcount(g));
#else
          unsigned char cur[64];
          std::memcpy(cur, row, 64);
          unsigned rest = g;
          while (rest != 0) {
            const unsigned k = static_cast<unsigned>(__builtin_ctz(rest));
            rest &= rest - 1;
            std::memcpy(cur + 8 * k, p, 8);
            p += 8;
          }
          neq = 0;
          for (unsigned k = 0; k < 64; ++k)
            neq |= static_cast<std::uint64_t>(cur[k] != row[k]) << k;
          neq &= claimed_[index];
          std::memcpy(row, cur, 64);
#endif
          commit_row(index, neq);
        }
        break;
      }
      case ExportRing::kFlush:
        CHISA_DIAG(::chisa::diagnostic::set_cycle(
            sealed_windows_.load(std::memory_order_relaxed) * kSystemOracleCyclesPerWindow + h.position));
        writer_.flush_registers_from(mirror_, block, h.position);
        break;
      case ExportRing::kFinish:
        // The FIFO contains every window marker, including reset windows.
        // Use that worker-owned position, never the producer thread's TLS or
        // a stale cycle left by a decoder sharing this worker.
        CHISA_DIAG(::chisa::diagnostic::set_cycle(
            sealed_windows_.load(std::memory_order_relaxed) * kSystemOracleCyclesPerWindow + h.position));
        writer_.finish_position_from(mirror_, block, h.position);
        ++finishes_;
        break;
      case ExportRing::kWindow:
        sealed_windows_.store(h.block + 1, std::memory_order_release);
        break;
    }
  }

  static std::uint64_t bits_below(unsigned k) {
    return k >= 64 ? ~UINT64_C(0) : (UINT64_C(1) << k) - 1;
  }

  /** ModelBindings::diff_unified pass 2, against the row copy. */
  void commit_row(std::uint32_t i, std::uint64_t neq) {
    const unsigned char* rows = rows_bytes_.data();
    while (neq != 0) {
      const unsigned b0 = static_cast<unsigned>(__builtin_ctzll(neq));
      const std::uint16_t fid = row_byte_field_[64 * i + b0];
      const Field& f = fields_[fid];
      std::uint64_t raw = 0;
      if (f.tail)
        std::memcpy(&raw, rows + f.offset, f.bytes);
      else
        std::memcpy(&raw, rows + f.offset, 8);
      const std::uint64_t shifted = raw << f.shift;
      const std::uint64_t v =
          f.is_signed
              ? static_cast<std::uint64_t>(static_cast<std::int64_t>(shifted) >> f.shift)
              : shifted >> f.shift;
      mirror_.commit(f.lane, ModelBindings::apply_bits(v, f.bits));
      const std::ptrdiff_t fstart =
          static_cast<std::ptrdiff_t>(f.offset) - static_cast<std::ptrdiff_t>(64 * i);
      const std::ptrdiff_t lo = fstart > 0 ? fstart : 0;
      const std::ptrdiff_t hi =
          fstart + static_cast<std::ptrdiff_t>(f.bytes) < 64
              ? fstart + static_cast<std::ptrdiff_t>(f.bytes)
              : 64;
      neq &= ~(bits_below(static_cast<unsigned>(hi)) & ~bits_below(static_cast<unsigned>(lo)));
    }
  }

  /** The writer-facing export state: same surface as ModelBindings' export
    * side, fed purely by the ring. */
  struct Mirror {
    OracleRecord image{};
#if defined(CHISA_WIDE_MODEL)
    bool native_image = false;
#endif
    std::vector<ModelBindings::LaneCell> cells =
        std::vector<ModelBindings::LaneCell>(kOracleRecordLanes);
    std::vector<std::uint16_t> changed =
        std::vector<std::uint16_t>(ModelBindings::kChangeCapacity + 1);
    std::vector<std::uint16_t> predicted =
        std::vector<std::uint16_t>(ModelBindings::kPredictedCapacity);
    std::size_t n_changes = 0;
    std::size_t n_predicted = 0;

    void commit(std::uint16_t lane, std::uint64_t value) {
      cells[lane].value = value;
      image.store(lane, value);
      changed[n_changes] = lane;
      n_changes += n_changes < ModelBindings::kChangeCapacity;
    }
    void predict(std::uint16_t lane, std::uint64_t value) {
#if defined(CHISA_WIDE_MODEL)
      if ((native_image ? image.load(lane) : cells[lane].value) == value) return;
#else
      if (cells[lane].value == value) return;
#endif
      cells[lane].value = value;
      image.store(lane, value);
      if (n_predicted < ModelBindings::kPredictedCapacity) predicted[n_predicted++] = lane;
    }
    void materialize_record() {}  // the image is always current
    /** The writer's change entries take a lane's value from here. */
    std::uint64_t lane_value(std::uint16_t lane) const { return cells[lane].value; }
    const OracleRecord& record() const { return image; }
    bool change_overflow() const { return n_changes >= ModelBindings::kChangeCapacity; }
    const std::uint16_t* changed_lanes() const { return changed.data(); }
    std::size_t change_count() const { return n_changes; }
    const ModelBindings::LaneCell& lane_cell(std::uint16_t lane) const {
      return cells[lane];
    }
    const std::uint16_t* predicted_changes() const { return predicted.data(); }
    std::size_t predicted_change_count() const { return n_predicted; }
    void seal_changes() { n_changes = 0; }
    void seal_predicted() { n_predicted = 0; }
  };

  // The producer's thread touches only the ring's producer side, stop_
  // (once) and hook_tsc_; the worker touches the rest.  Keep the two
  // sides' fields on separate cache lines.
  SystemOracleWriter& writer_;
  ExportRing ring_;
  alignas(64) Mirror mirror_;
  std::size_t rows_ = 0;
  std::vector<unsigned char> rows_bytes_;
  std::vector<std::uint16_t> row_byte_field_;
  std::vector<std::uint64_t> claimed_;
  std::vector<Field> fields_;
  std::uint8_t lane_bits_[kOracleRecordLanes] = {};
  std::uint64_t finishes_ = 0;
  int skip_mode_ = 0;
  bool own_thread_ = true;
  std::thread worker_;
#if defined(CHISA_WIDE_MODEL)
  bool native_active_ = false;
  OracleRecord native_shadow_{};
#endif
  alignas(64) std::atomic<bool> stop_{false};
  alignas(64) std::atomic<std::uint64_t> sealed_windows_{0};
#ifdef CHISA_PHASE_TIMERS
  alignas(64) std::uint64_t hook_tsc_ = 0;
#endif
};

}  // namespace chisa::boom_system
