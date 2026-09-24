#pragma once
// ==========================================================================
// Depth-one rocket-chip AsyncQueue, transcribed from the locked artifact.
//
// This is not the ordinary Chisel Queue in queue.h.  Its source and sink may
// use different clocks, so the one-bit read/write indices cross through
// three-register synchronizers and a safe-start protocol prevents either end
// from accepting traffic until both resets have been observed deasserted.
//
// The model is split into source and sink endpoints for two reasons:
//
//   1. each endpoint can be differentially checked against the corresponding
//      artifact module with arbitrary remote signals;
//   2. a full-system caller can advance the endpoints on different clock
//      edges.  It must snapshot the remote outputs first, then step both --
//      passing one endpoint's post-edge state to the other is a one-cycle bug.
//
// Payloads in the complete Small BOOM debug crossing are 15, 43 or 55 bits,
// so uint64_t covers every concrete instance.  The width mask belongs to the
// caller; the queue stores and transfers bits without interpreting them.
// ==========================================================================

#include <array>
#include <cstddef>
#include <cstdint>

namespace chisa::boom_system::components {

/** The exact three-register synchronizer emitted by SynchronizerReg.scala.
  *
  * The artifact numbers the destination-nearest register `sync_0` and shifts
  * `sync_2 <- input`, `sync_1 <- old sync_2`, `sync_0 <- old sync_1`.
  * `q()` is therefore stage zero. */
class AsyncSync3 {
 public:
  void apply_async_reset(bool reset) {
    if (reset) stages_.fill(false);
  }

  void step(bool reset, bool input) {
    if (reset) {
      stages_.fill(false);
      return;
    }
    const std::array<bool, 3> old = stages_;
    stages_[0] = old[1];
    stages_[1] = old[2];
    stages_[2] = input;
  }

  bool q() const { return stages_[0]; }
  bool stage(std::size_t index) const { return stages_.at(index); }

 private:
  std::array<bool, 3> stages_{};
};

struct AsyncQueueSourceInputs {
  bool reset = false;
  bool enq_valid = false;
  uint64_t enq_bits = 0;
  bool remote_ridx = false;
  bool remote_ridx_valid = false;
  bool remote_sink_reset_n = false;
};

/** Source-clock half of a depth-one AsyncQueue. */
class AsyncQueueSource1 {
 public:
  /** Model the asynchronous reset effect before a clock edge. */
  void settle_async_resets(bool reset, bool remote_sink_reset_n) {
    if (reset) {
      widx_bin_ = false;
      ready_reg_ = false;
      widx_gray_ = false;
    }
    ridx_sync_.apply_async_reset(reset);
    const bool guarded_reset = reset || !remote_sink_reset_n;
    source_valid_0_.apply_async_reset(guarded_reset);
    source_valid_1_.apply_async_reset(guarded_reset);
    sink_extend_.apply_async_reset(guarded_reset);
    sink_valid_.apply_async_reset(reset);
  }

  void step(const AsyncQueueSourceInputs& input) {
    settle_async_resets(input.reset, input.remote_sink_reset_n);

    // All expressions below are pre-edge snapshots.  In particular, the
    // second safe-start synchronizer consumes the first one's old output.
    const bool source_valid_0_q = source_valid_0_.q();
    const bool sink_extend_q = sink_extend_.q();
    const bool sink_ready_now = sink_ready();
    const bool fire = enq_ready() && input.enq_valid;
    const bool widx_incremented =
        sink_ready_now ? static_cast<bool>(widx_bin_ ^ fire) : false;
    const bool ready_next =
        sink_ready_now && (widx_incremented != (ridx_sync_.q() ^ true));

    if (!input.reset && fire) memory_ = input.enq_bits;
    if (input.reset) {
      widx_bin_ = false;
      ready_reg_ = false;
      widx_gray_ = false;
    } else {
      // A one-bit Gray code is identical to its binary value.
      widx_bin_ = widx_incremented;
      ready_reg_ = ready_next;
      widx_gray_ = widx_incremented;
    }

    ridx_sync_.step(input.reset, input.remote_ridx);
    const bool guarded_reset = input.reset || !input.remote_sink_reset_n;
    source_valid_0_.step(guarded_reset, true);
    source_valid_1_.step(guarded_reset, source_valid_0_q);
    sink_extend_.step(guarded_reset, input.remote_ridx_valid);
    sink_valid_.step(input.reset, sink_extend_q);
  }

  // Registered state selected by CHISA in one or more concrete instances.
  bool widx_bin() const { return widx_bin_; }
  bool ready_reg() const { return ready_reg_; }
  bool widx_gray() const { return widx_gray_; }
  uint64_t memory() const { return memory_; }

  // Combinational interface values for the current source-clock cycle.
  bool sink_ready() const { return sink_valid_.q(); }
  bool enq_ready() const { return ready_reg_ && sink_ready(); }
  bool async_widx() const { return widx_gray_; }
  bool async_widx_valid() const { return source_valid_1_.q(); }

  const AsyncSync3& ridx_sync() const { return ridx_sync_; }
  const AsyncSync3& source_valid_0_sync() const { return source_valid_0_; }
  const AsyncSync3& source_valid_1_sync() const { return source_valid_1_; }
  const AsyncSync3& sink_extend_sync() const { return sink_extend_; }
  const AsyncSync3& sink_valid_sync() const { return sink_valid_; }

  /** Model-only invariant used by the full-system sentinel. */
  bool gray_matches_binary() const { return widx_gray_ == widx_bin_; }

 private:
  uint64_t memory_ = 0;  // artifact register has no reset
  bool widx_bin_ = false;
  bool ready_reg_ = false;
  bool widx_gray_ = false;
  AsyncSync3 ridx_sync_;
  AsyncSync3 source_valid_0_;
  AsyncSync3 source_valid_1_;
  AsyncSync3 sink_extend_;
  AsyncSync3 sink_valid_;
};

struct AsyncQueueSinkInputs {
  bool reset = false;
  bool deq_ready = false;
  uint64_t remote_memory = 0;
  bool remote_widx = false;
  bool remote_widx_valid = false;
  bool remote_source_reset_n = false;
};

/** Sink-clock half of a depth-one AsyncQueue. */
class AsyncQueueSink1 {
 public:
  void settle_async_resets(bool reset, bool remote_source_reset_n) {
    if (reset) {
      ridx_bin_ = false;
      valid_reg_ = false;
      ridx_gray_ = false;
    }
    widx_sync_.apply_async_reset(reset);
    const bool guarded_reset = reset || !remote_source_reset_n;
    sink_valid_0_.apply_async_reset(guarded_reset);
    sink_valid_1_.apply_async_reset(guarded_reset);
    source_extend_.apply_async_reset(guarded_reset);
    source_valid_.apply_async_reset(reset);
    // crossing_reg_ deliberately has no reset in the artifact.
  }

  void step(const AsyncQueueSinkInputs& input) {
    settle_async_resets(input.reset, input.remote_source_reset_n);

    const bool sink_valid_0_q = sink_valid_0_.q();
    const bool source_extend_q = source_extend_.q();
    const bool source_ready_now = source_ready();
    const bool fire = deq_valid() && input.deq_ready;
    const bool ridx_incremented =
        source_ready_now ? static_cast<bool>(ridx_bin_ ^ fire) : false;
    // FIRRTL computes `valid` from the incremented index, so a dequeue of the
    // sole entry clears valid_reg on that same edge.
    const bool valid_next =
        source_ready_now && (ridx_incremented != widx_sync_.q());

    if (!input.reset && valid_next) crossing_reg_ = input.remote_memory;
    if (input.reset) {
      ridx_bin_ = false;
      valid_reg_ = false;
      ridx_gray_ = false;
    } else {
      ridx_bin_ = ridx_incremented;
      valid_reg_ = valid_next;
      ridx_gray_ = ridx_incremented;
    }

    widx_sync_.step(input.reset, input.remote_widx);
    const bool guarded_reset = input.reset || !input.remote_source_reset_n;
    sink_valid_0_.step(guarded_reset, true);
    sink_valid_1_.step(guarded_reset, sink_valid_0_q);
    source_extend_.step(guarded_reset, input.remote_widx_valid);
    source_valid_.step(input.reset, source_extend_q);
  }

  bool ridx_bin() const { return ridx_bin_; }
  bool valid_reg() const { return valid_reg_; }
  bool ridx_gray() const { return ridx_gray_; }
  uint64_t crossing_reg() const { return crossing_reg_; }

  bool source_ready() const { return source_valid_.q(); }
  bool deq_valid() const { return valid_reg_ && source_ready(); }
  uint64_t deq_bits() const { return crossing_reg_; }
  bool async_ridx() const { return ridx_gray_; }
  bool async_ridx_valid() const { return sink_valid_1_.q(); }

  const AsyncSync3& widx_sync() const { return widx_sync_; }
  const AsyncSync3& sink_valid_0_sync() const { return sink_valid_0_; }
  const AsyncSync3& sink_valid_1_sync() const { return sink_valid_1_; }
  const AsyncSync3& source_extend_sync() const { return source_extend_; }
  const AsyncSync3& source_valid_sync() const { return source_valid_; }

  bool gray_matches_binary() const { return ridx_gray_ == ridx_bin_; }

 private:
  bool ridx_bin_ = false;
  bool valid_reg_ = false;
  bool ridx_gray_ = false;
  uint64_t crossing_reg_ = 0;  // artifact register has no reset
  AsyncSync3 widx_sync_;
  AsyncSync3 sink_valid_0_;
  AsyncSync3 sink_valid_1_;
  AsyncSync3 source_extend_;
  AsyncSync3 source_valid_;
};

/** A same-rate convenience wrapper.  It still snapshots both sides before
  * either step, preserving simultaneous clock-edge semantics. */
class AsyncQueue1 {
 public:
  void step(bool source_reset, bool sink_reset, bool enq_valid,
            uint64_t enq_bits, bool deq_ready) {
    step_gated(source_reset, sink_reset, true, true, enq_valid, enq_bits,
               deq_ready);
  }

  /** Advance endpoints whose clocks have an edge in this host cycle.
    *
    * Async reset still settles on a stopped endpoint.  Remote pointer and
    * safe-start signals are snapshotted before either clocked transition, as
    * in the same-rate wrapper above. */
  void step_gated(bool source_reset, bool sink_reset,
                  bool source_clock_edge, bool sink_clock_edge,
                  bool enq_valid, uint64_t enq_bits, bool deq_ready) {
    source_.settle_async_resets(source_reset, !sink_reset);
    sink_.settle_async_resets(sink_reset, !source_reset);

    const bool source_widx = source_.async_widx();
    const bool source_widx_valid = source_.async_widx_valid();
    const uint64_t source_memory = source_.memory();
    const bool sink_ridx = sink_.async_ridx();
    const bool sink_ridx_valid = sink_.async_ridx_valid();

    if (source_clock_edge) {
      source_.step(AsyncQueueSourceInputs{
          source_reset, enq_valid, enq_bits, sink_ridx, sink_ridx_valid,
          !sink_reset});
    }
    if (sink_clock_edge) {
      sink_.step(AsyncQueueSinkInputs{
          sink_reset, deq_ready, source_memory, source_widx,
          source_widx_valid, !source_reset});
    }
  }

  const AsyncQueueSource1& source() const { return source_; }
  const AsyncQueueSink1& sink() const { return sink_; }
  AsyncQueueSource1& source() { return source_; }
  AsyncQueueSink1& sink() { return sink_; }

 private:
  AsyncQueueSource1 source_;
  AsyncQueueSink1 sink_;
};

}  // namespace chisa::boom_system::components
