#pragma once

#include "TestHarness.h"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <utility>

#include "extmodule_bindings.h"

namespace chisa::boom_repcut {

enum class HalfDirection : uint8_t { forward, reverse };
enum class TapPhase : uint8_t { pre_eval_register, post_eval_combinational };

inline const char* direction_name(HalfDirection direction) {
  return direction == HalfDirection::forward ? "forward" : "reverse";
}

inline const char* phase_name(TapPhase phase) {
  return phase == TapPhase::pre_eval_register ? "pre" : "post";
}

// Count the selected W=4 ABI without maintaining a second hand-written
// constant.  These X-macros are the exact byte-identical copies whose source
// is checked by scalar_tap_provenance.json.
inline constexpr std::size_t exact_register_tap_count() {
  std::size_t count = 0;
#define REG_ORACLE(expr, name) ++count
#define REG_ORACLE_WORD(expr, i, name) ++count
#include "exact_reg_oracle_fields.inc"
#undef REG_ORACLE
#undef REG_ORACLE_WORD
  return count;
}
inline constexpr std::size_t kExactRegisterTapCount =
    exact_register_tap_count();

inline constexpr std::size_t exact_combinational_tap_count() {
  std::size_t count = 0;
#define PUSH_AS(expr, name) ++count
#include "exact_probe_fields_v2.inc"
#undef PUSH_AS
  return count;
}
inline constexpr std::size_t kExactCombinationalTapCount =
    exact_combinational_tap_count();

/** Sample the manifest register state before one chronological RTL cycle.
  *
  * `Observer::observe` receives (cycle, direction, phase, trace key, value).
  * The observer is validation infrastructure only: values sampled here must
  * never be used as predictions for the cycle being evaluated. */
template <typename Observer>
inline void sample_exact_register_tap(
    TestHarness& t, Observer& observer, uint64_t cycle,
    HalfDirection direction) {
#define REG_ORACLE(expr, name)                                               \
  do {                                                                       \
    observer.observe(cycle, direction, TapPhase::pre_eval_register, (name),  \
                     essent_to_u64((expr)[0]));                              \
  } while (false)
/* Wide (>64-bit) register: word i of the UInt<N> word array (V2_WIDE_ORACLE). */
#define REG_ORACLE_WORD(expr, i, name)                                       \
  do {                                                                       \
    observer.observe(cycle, direction, TapPhase::pre_eval_register, (name),  \
                     (uint64_t)((expr)[0].val[(i)]));                        \
  } while (false)
#include "exact_reg_oracle_fields.inc"
#undef REG_ORACLE
#undef REG_ORACLE_WORD
}

/** Sample compiler-promoted combinational values after the same RTL cycle. */
template <typename Observer>
inline void sample_exact_combinational_tap(
    Observer& observer, uint64_t cycle, HalfDirection direction) {
#define CHISA_TAP_CAT_INNER(a, b) a##b
#define CHISA_TAP_CAT(a, b) CHISA_TAP_CAT_INNER(a, b)
#define CHISA_TAP_SCRATCH(expr) CHISA_TAP_CAT(_s_, expr)
#define PUSH_AS(expr, name)                                                  \
  do {                                                                       \
    observer.observe(cycle, direction, TapPhase::post_eval_combinational,    \
                     (name), essent_to_u64(CHISA_TAP_SCRATCH(expr)[0]));     \
  } while (false)
#include "exact_probe_fields_v2.inc"
#undef PUSH_AS
#undef CHISA_TAP_SCRATCH
#undef CHISA_TAP_CAT
#undef CHISA_TAP_CAT_INNER
}

struct ReferenceStepResult {
  uint64_t cycle = 0;
  HalfDirection direction = HalfDirection::forward;
  DmiFeedback dmi_feedback{};
  bool io_success = false;
};

/** Clock-faithful, zero-oracle W=1 execution wrapper.
  *
  * One call advances exactly one chronological cycle: forward and reverse
  * calls must alternate.  The ordering is deliberately fixed:
  *
  *   drive exact host boundary -> PRE register tap -> RTL eval -> POST comb
  *   tap -> capture actual DMI feedback -> advance exact dtm_t adapter
  *
  * This is the scalar validation/reference path.  A future W>1 live sidecar
  * has to predict DMI feedback before eval; it cannot reuse the actual value
  * captured by this class as an oracle producer.
  */
template <typename Dtm, typename Observer>
class W1ReferenceStepper {
 public:
  using PostEvalHook =
      std::function<void(TestHarness&, uint64_t, HalfDirection)>;

  W1ReferenceStepper(TestHarness& dut, Dtm& dtm, Observer& observer,
                     int argc, char** argv)
      : dut_(dut), adapter_(dtm), observer_(observer) {
    initialize_plusarg_readers<1>(dut_, argc, argv);
    // Generated reverse-half bookkeeping performs pointer += 0 even though
    // this reference has no oracle block.  Keep the base non-null so that
    // operation is well-defined C++.
    dut_.oracle_win_base = &empty_oracle_byte_;
  }

  uint64_t cycle() const { return cycle_; }
  HalfDirection expected_direction() const { return expected_direction_; }
  FesvrDtmAdapter<Dtm>& dtm_adapter() { return adapter_; }
  const FesvrDtmAdapter<Dtm>& dtm_adapter() const { return adapter_; }
  void set_post_eval_hook(PostEvalHook hook) {
    post_eval_hook_ = std::move(hook);
  }

  ReferenceStepResult step(HalfDirection direction, bool reset, bool verbose) {
    if (direction != expected_direction_) {
      throw std::logic_error(
          "W=1 reference halves must alternate forward then reverse");
    }

    assign_port(dut_.reset, reset);
    auto& ports = simdtm_ports(dut_);
    adapter_.drive_lane(ports, 0);

    if (observer_.capture_cycle(cycle_))
      sample_exact_register_tap(dut_, observer_, cycle_, direction);

    const bool done_reset = !reset;
    if (direction == HalfDirection::forward)
      dut_.eval_forward(true, verbose, done_reset);
    else
      dut_.eval_reverse(true, verbose, done_reset);

    // Diagnostic-only seam audits need the exact POST combinational image,
    // after host inputs and RTL eval but before the next chronological cycle.
    // The hook is never an oracle producer and must not mutate the DUT/model.
    if (post_eval_hook_) post_eval_hook_(dut_, cycle_, direction);

    if (observer_.capture_cycle(cycle_))
      sample_exact_combinational_tap(observer_, cycle_, direction);

    const DmiFeedback feedback =
        FesvrDtmAdapter<Dtm>::feedback_lane(ports, 0);
    adapter_.advance(reset, feedback);

    const ReferenceStepResult result{
        cycle_, direction, feedback, port_value(dut_.io_success[0]) != 0};
    ++cycle_;
    expected_direction_ =
        direction == HalfDirection::forward ? HalfDirection::reverse
                                            : HalfDirection::forward;
    return result;
  }

 private:
  TestHarness& dut_;
  FesvrDtmAdapter<Dtm> adapter_;
  Observer& observer_;
  PostEvalHook post_eval_hook_{};
  uint64_t cycle_ = 0;
  HalfDirection expected_direction_ = HalfDirection::forward;
  char empty_oracle_byte_ = 0;
};

} // namespace chisa::boom_repcut
