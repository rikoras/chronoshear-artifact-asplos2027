#pragma once
// Env-gated diagnostics cache their knobs in statics.  A process that resumes
// from a checkpoint (run_system_model_lockstep --checkpoint-at) changes the
// environment after those statics were set, so it bumps this generation and
// the traces re-read getenv() when they see it change.
namespace chisa::boom_model {
extern int g_env_generation;
}  // namespace chisa::boom_model
