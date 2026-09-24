#pragma once
// Fine-grained phase timers for the producer benchmark (CHISA_PHASE_TIMERS
// builds only): components accumulate TSC ticks into named slots that
// benchmark_system_oracle_producer prints per cycle.
#include <cstdint>
namespace chisa::boom_system {
// The slot names exist in every build (the lap calls name them); only the
// counters are timer-build-only.
enum PhaseSub : unsigned {
  kSubFabricCommit = 0, kSubDcacheStep, kSubDebugPathStep, kSubDcacheSnapshots,
  kSubPreviewBranch, kSubPreviewPlan, kSubPreviewRest, kSubMemoryOutputs,
  kSubColdEvaluate, kSubColdCommit, kSubCount
};
#ifdef CHISA_PHASE_TIMERS
inline std::uint64_t g_phase_sub[kSubCount] = {};
// Cold uncore evaluations that ran (not skipped) and their ticks above 2,000
// (an active evaluation), to cost the active cycles on their own.
inline std::uint64_t g_cold_evaluate_active = 0, g_cold_evaluate_active_ticks = 0;
inline std::uint64_t g_cold_commit_active = 0, g_cold_commit_active_ticks = 0;  // commits above 500 ticks
#endif
}  // namespace chisa::boom_system
