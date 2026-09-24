#pragma once
// ==========================================================================
// Chisel `Queue` — the most-instantiated piece of state in the uncore.
//
// Per-signal scoping of the corrected Small manifest found 100 streams
// declared at `Counter.scala 60:40` (dequeue pointers) plus a matching set of
// `maybe_full` flags at `Decoupled.scala 221:27`, spread across the mbus,
// sbus, fbus, cbus and AXI shims.  They are all the same stock component, so
// it is modeled once here and instantiated against the topology.
//
// Transcribed from the artifact's own elaborated FIRRTL rather than from the
// Chisel source, because the elaboration is what the DUT actually contains:
//
//   ptr_match = enq_ptr == deq_ptr                     Decoupled.scala 223
//   empty     = ptr_match && !maybe_full                             224
//   full      = ptr_match &&  maybe_full                             225
//   do_enq    = enq.ready && enq.valid                                40
//   do_deq    = deq.ready && deq.valid                                40
//   on do_enq: ram[enq_ptr] <= enq.bits;  enq_ptr++                  229
//   on do_deq:                            deq_ptr++                  233
//   if (do_enq != do_deq) maybe_full <= do_enq                   236-237
//   deq.valid = !empty                                               240
//   enq.ready = !full                                                241
//   count     = (maybe_full && ptr_match ? depth : enq_ptr - deq_ptr) 259
//
// The payload `ram` is deliberately absent.  It is a `cmem` that CHISA owns as
// chronological state computed by the RTL kernel, so predicting it here would
// duplicate storage the kernel already holds.  What the model owes is
// occupancy and the handshake it implies.  The depth-1 instances whose `ram`
// was lowered to plain registers are the exception and are handled by the
// caller, which binds those registers separately.
//
// `flow` and `pipe` are carried because rocket-chip instantiates both
// variants; when neither is set this is the plain queue above.
// ==========================================================================

#include <cstdint>

namespace chisa::boom_system::components {

/** One Chisel `Queue` instance: pointers and occupancy, no payload.
  *
  * All accessors read cycle-start state, which is the whole point: the RTL's
  * `deq.valid` and `enq.ready` are combinational functions of the registered
  * pointers, so a caller that samples them after `step()` is reading the wrong
  * cycle.  Sample first, then step. */
class Queue {
 public:
  /** `depth` must match the elaborated instance; `flow` lets an enqueue be
    * dequeued in the same cycle, `pipe` lets a dequeue free a slot for an
    * enqueue in the same cycle. */
  Queue(uint32_t depth, bool flow = false, bool pipe = false)
      : depth_(depth), flow_(flow), pipe_(pipe) {}

  void reset() {
    enq_ptr_ = 0;
    deq_ptr_ = 0;
    maybe_full_ = false;
  }

  const uint32_t& enq_ptr() const { return enq_ptr_; }
  const uint32_t& deq_ptr() const { return deq_ptr_; }
  const bool& maybe_full() const { return maybe_full_; }
  uint32_t depth() const { return depth_; }

  bool ptr_match() const { return enq_ptr_ == deq_ptr_; }
  bool empty() const { return ptr_match() && !maybe_full_; }
  bool full() const { return ptr_match() && maybe_full_; }

  /** `deq.valid` as the RTL drives it, given this cycle's `enq.valid`.
    * The argument is only consulted for a flow queue, where an arriving beat
    * is visible at the output in the same cycle. */
  bool deq_valid(bool enq_valid) const {
    return flow_ ? (!empty() || enq_valid) : !empty();
  }

  /** `enq.ready` as the RTL drives it, given this cycle's `deq.ready`.
    * The argument is only consulted for a pipe queue. */
  bool enq_ready(bool deq_ready) const {
    return pipe_ ? (!full() || deq_ready) : !full();
  }

  uint32_t count() const {
    if (maybe_full_ && ptr_match()) return depth_;
    return (enq_ptr_ - deq_ptr_) & mask();
  }

  /** Advance one clock edge.
    *
    * Takes the *external* handshake signals and derives `do_enq`/`do_deq`
    * internally from its own outputs, exactly as the RTL does. Passing
    * pre-ANDed fire signals instead would let a caller enqueue into a full
    * queue without the model noticing. */
  void step(bool reset_asserted, bool enq_valid, bool deq_ready) {
    if (reset_asserted) {
      reset();
      return;
    }
    const bool do_enq = enq_ready(deq_ready) && enq_valid;
    const bool do_deq = deq_ready && deq_valid(enq_valid);
    // A flow queue that enqueues and dequeues the same beat in one cycle
    // touches neither pointer: the beat never occupied a slot.
    const bool bypassed = flow_ && empty() && do_enq && do_deq;
    if (do_enq && !bypassed) enq_ptr_ = increment(enq_ptr_);
    if (do_deq && !bypassed) deq_ptr_ = increment(deq_ptr_);
    if (!bypassed && do_enq != do_deq) maybe_full_ = do_enq;
  }

 private:
  uint32_t mask() const {
    // Chisel's Counter wraps with `tail(value + 1, 1)` when the depth is a
    // power of two, and with an explicit compare otherwise; increment()
    // covers both, and this mask is only used for the pointer difference.
    return is_power_of_two() ? (depth_ - 1) : 0xffffffffu;
  }

  bool is_power_of_two() const { return (depth_ & (depth_ - 1)) == 0; }

  uint32_t increment(uint32_t value) const {
    if (is_power_of_two()) return (value + 1) & (depth_ - 1);
    return value + 1 == depth_ ? 0 : value + 1;
  }

  uint32_t depth_;
  bool flow_;
  bool pipe_;
  uint32_t enq_ptr_ = 0;
  uint32_t deq_ptr_ = 0;
  bool maybe_full_ = false;
};

}  // namespace chisa::boom_system::components
