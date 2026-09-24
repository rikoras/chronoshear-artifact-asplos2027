#pragma once
// ============================================================================
// Small BOOM F4 queue carrying the complete FetchBundle payload.
//
// The RTL instance is Queue(new FetchBundle, entries=1, pipe=true, flow=false).
// Its full payload is consumed in parallel by the FetchBuffer and FTQ.
// ============================================================================

#include "small_fetch_buffer.h"

namespace chisa::boom_system::components {

struct SmallF4QueueInputs {
  bool reset = false;  // module reset || f4_clear
  bool enq_valid = false;
  SmallFetchBundle enq{};
  bool deq_ready = false;
  // When set, the bundle to enqueue lives in the caller's evaluation
  // object and is read there instead of being copied into `enq`.
  const SmallFetchBundle* enq_ref = nullptr;
};

struct SmallF4QueueOutputs {
  bool enq_ready = false;
  bool deq_valid = false;
  SmallFetchBundle deq{};
};

class SmallF4Queue {
 public:
  SmallF4QueueOutputs outputs(bool deq_ready) const {
    // `pipe=true`: a dequeue from a full depth-one queue permits replacement
    // on the same edge.  `flow=false`: an enqueue into an empty queue is not
    // visible at deq until the next cycle.
    return SmallF4QueueOutputs{!full_ || deq_ready, full_, payload_};
  }
  void outputs_into(bool deq_ready, SmallF4QueueOutputs& result) const {
    result.enq_ready = !full_ || deq_ready;
    result.deq_valid = full_;
    result.deq = payload_;
  }

  void commit(const SmallF4QueueInputs& input,
              const SmallF4QueueOutputs& output) {
    const bool do_enq = output.enq_ready && input.enq_valid;
    const bool do_deq = output.deq_valid && input.deq_ready;

    // Queue RAM is unreset and may be replaced on a simultaneous deq/enq.
    if (do_enq) payload_ = input.enq_ref != nullptr ? *input.enq_ref : input.enq;
    if (do_enq != do_deq) full_ = do_enq;
    if (input.reset) full_ = false;
  }

  void step(const SmallF4QueueInputs& input) {
    commit(input, outputs(input.deq_ready));
  }

  const bool& full() const { return full_; }
  const SmallFetchBundle& payload() const { return payload_; }

 private:
  SmallFetchBundle payload_{};
  bool full_ = false;
};

}  // namespace chisa::boom_system::components
