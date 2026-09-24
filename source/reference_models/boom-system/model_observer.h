#pragma once
// ==========================================================================
// ModelObserver — bridges the generated exact tap to the model's obligations.
//
// `W1ReferenceStepper` (duts/boom-repcut/runtime/scalar_reference_runtime.h)
// drives the complete TestHarness one chronological cycle at a time and calls
// `observe(cycle, direction, phase, trace_key, value)` once per manifest
// stream.  This observer forwards each of those to the probe registry, which
// compares it against the model's own prediction for the same stream.
//
// Direction of information is one way, and it is load bearing.  The RTL value
// arrives only to be *compared*; nothing sampled here is written into the
// model.  A model fed by DUT taps is a replay harness that will pass every
// gate and produce nothing, which is why duts/boom-repcut's coverage audit
// refuses to count a generated accessor as a live producer.
//
// Ordering, which follows the reference stepper's fixed half-cycle contract:
//
//   host drive -> PRE register tap -> RTL eval -> POST comb tap -> DMI capture
//
// The model must have already produced its prediction for cycle N before the
// PRE tap of cycle N is compared, so `begin_cycle()` steps it. That is the
// same constraint the live sidecar runs under: the producer is a full window
// ahead, never level with the consumer.
// ==========================================================================

#include <cstdint>

#include "system_guider.h"
#include "system_probe.h"

namespace chisa::boom_system {

/** Adapts the model to the reference stepper's observer interface.
  *
  * `Direction` and `Phase` are the stepper's own enums, taken as template
  * parameters so this header does not have to include the generated
  * TestHarness just to name them. */
template <typename Direction, typename Phase>
class ModelObserver {
 public:
  explicit ModelObserver(SystemGuider& model) : model_(model) {}

  /** The setup/loading phase still advances the independent model, but it is
    * not part of the target simulation region. */
  void pause_measurement() {
    measurement_enabled_ = false;
    model_.set_oracle_sampling_enabled(false);
    reset_measurements();
  }

  void begin_measurement() {
    reset_measurements();
    model_.set_oracle_sampling_enabled(true);
    measurement_enabled_ = true;
  }

  /** Advance the model to the cycle that is about to be evaluated.
    *
    * Called by the harness before handing the cycle to the stepper. Sentinel
    * failures are recorded rather than thrown: a model that has lost track of
    * itself should keep running so the probe summary can still report where it
    * first diverged, which is more useful than the first assertion. */
  void begin_cycle() {
    const StepResult result = model_.step();
    if (measurement_enabled_ && !result.ok) {
      ++step_failures_;
      last_failure_ = result.failure;
    }
    if (measurement_enabled_) {
      for (const std::string& failure : model_.sentinel_failures()) {
        ++sentinel_failures_;
        if (sentinel_reported_ < kMaxSentinelReports) {
          ++sentinel_reported_;
          fprintf(stderr, "[SENTINEL c%llu] %s\n",
                  (unsigned long long)model_.cycle(), failure.c_str());
        }
      }
    }
  }

  /** Loading is executed but is outside the target region, so avoid both the
    * 2,086-value RTL tap and the matching model-side sample work there. Once
    * measurement begins every ROI cycle is captured without filtering. */
  bool capture_cycle(uint64_t) const { return measurement_enabled_; }

  void observe(uint64_t cycle, Direction, Phase phase, const char* trace_key,
               uint64_t value) {
    const ObservationPhase observation =
        phase == Phase::pre_eval_register
            ? ObservationPhase::PreEvalRegister
            : ObservationPhase::PostEvalCombinational;
    SystemProbes::instance().observe(static_cast<long long>(cycle), trace_key,
                                     observation, value, model_);
  }

  /** Called by the harness once the cycle's taps are done. */
  void end_cycle() { SystemProbes::instance().end_of_cycle(); }

  uint64_t sentinel_failures() const { return sentinel_failures_; }
  uint64_t step_failures() const { return step_failures_; }
  const char* last_failure() const { return last_failure_; }

  /** A run is clean only if the model produced every cycle, no invariant
    * broke, and no modeled stream diverged. */
  bool clean() const {
    return step_failures_ == 0 && sentinel_failures_ == 0 &&
           SystemProbes::instance().real_mismatch_count() == 0 &&
           SystemProbes::instance().phase_mismatch_count() == 0;
  }

 private:
  static constexpr int kMaxSentinelReports = 20;

  void reset_measurements() {
    sentinel_failures_ = 0;
    step_failures_ = 0;
    sentinel_reported_ = 0;
    last_failure_ = "";
  }

  SystemGuider& model_;
  bool measurement_enabled_ = true;
  uint64_t sentinel_failures_ = 0;
  uint64_t step_failures_ = 0;
  int sentinel_reported_ = 0;
  const char* last_failure_ = "";
};

}  // namespace chisa::boom_system
