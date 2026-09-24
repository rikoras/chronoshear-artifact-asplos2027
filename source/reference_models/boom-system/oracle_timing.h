#pragma once

#include <cstdint>

namespace chisa::boom_system {

// Target phase is part of the oracle ABI. Register streams are sampled before
// the RTL evaluation and combinational streams after that same evaluation.
// This is deliberately separate from *when the model computes the value*: a
// model may preserve a PRE register snapshot until the end of step(), or may
// precompute a POST memory-read value before an in-place state update. Those
// cross-phase sources are valid, but must say so explicitly.
enum class OracleKind : std::uint8_t {
  Register,
  Combinational,
};

enum class ObservationPhase : std::uint8_t {
  PreEvalRegister,
  PostEvalCombinational,
};

enum class BindingTiming : std::uint8_t {
  PreStepSample,
  PostStepCycle,
  PreStepCombinational,
  PostStepRegisterSnapshot,
  ProfileConstant,
  StructuralConstant,
};

inline constexpr bool observation_matches(OracleKind kind,
                                          ObservationPhase phase) {
  return (kind == OracleKind::Register &&
          phase == ObservationPhase::PreEvalRegister) ||
         (kind == OracleKind::Combinational &&
          phase == ObservationPhase::PostEvalCombinational);
}

inline constexpr bool binding_matches(OracleKind kind,
                                      BindingTiming timing) {
  if (timing == BindingTiming::ProfileConstant ||
      timing == BindingTiming::StructuralConstant)
    return true;
  return (kind == OracleKind::Register &&
          (timing == BindingTiming::PreStepSample ||
           timing == BindingTiming::PostStepRegisterSnapshot)) ||
         (kind == OracleKind::Combinational &&
          (timing == BindingTiming::PostStepCycle ||
           timing == BindingTiming::PreStepCombinational));
}

inline constexpr bool binding_is_cross_phase(BindingTiming timing) {
  return timing == BindingTiming::PreStepCombinational ||
         timing == BindingTiming::PostStepRegisterSnapshot;
}

inline constexpr const char* oracle_kind_name(OracleKind kind) {
  return kind == OracleKind::Register ? "reg" : "comb";
}

inline constexpr const char* observation_phase_name(ObservationPhase phase) {
  return phase == ObservationPhase::PreEvalRegister ? "pre" : "post";
}

inline constexpr const char* binding_timing_name(BindingTiming timing) {
  switch (timing) {
    case BindingTiming::PreStepSample: return "pre-step";
    case BindingTiming::PostStepCycle: return "post-step-cycle";
    case BindingTiming::PreStepCombinational:
      return "pre-step-combinational";
    case BindingTiming::PostStepRegisterSnapshot:
      return "post-step-register-snapshot";
    case BindingTiming::ProfileConstant: return "profile-constant";
    case BindingTiming::StructuralConstant: return "structural-constant";
  }
  return "unknown";
}

}  // namespace chisa::boom_system
