// Native state of the AXI frontend in the locked DefaultConfig TestHarness.
// TestHarness connects AR/AW/W.valid and R/B.ready to false. Therefore no AXI
// request, response or yanker handshake exists, including during reset. This
// is a property of the simulated circuit's boundary, not missing-value policy.
// Keep the real queues/registers and their reset semantics: unreset payloads
// retain their contents, while queue pointers/counters/flight reset on edges.
// A harness with a driven frontend needs an AXI source and bridge evaluation;
// it must not reuse this closed-boundary specialization.
#pragma once
#include "uncore/tl.h"

namespace chisa::rocket_model::uncore {
struct ClosedFrontBus {
  Queue<TlA, 2> buffer_a, coupler_a;
  Queue<TlD, 2> buffer_d, coupler_d;
  FifoFixer fixer;
  Queue<AxiB, 1, true> q_b;
  Queue<uint8_t, 4> write_echo[2];
  uint8_t b_count[2] = {};

  void commit(bool reset, bool response_valid) {
    // No source [0,16) has issued a request. Receiving a response would break
    // the closed-boundary induction; expose the fault instead of swallowing it.
    if (response_valid) throw std::logic_error("response to undriven AXI frontend");
    fixer.step(false, TlA{}, false, 1, false, TlD{}, reset);
    if (reset) {
      buffer_a.reset(); buffer_d.reset(); coupler_a.reset(); coupler_d.reset();
      q_b.reset(); for (auto& q : write_echo) q.reset();
      b_count[0] = b_count[1] = 0;
    }
  }
};
}  // namespace chisa::rocket_model::uncore
