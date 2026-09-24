#pragma once

// Historical flag name: relaxed mode may retain old inactive payloads, but
// must still maintain/export every selected oracle's effective state. Oracle
// supply and comparison/reporting policy are separate runner decisions.
#ifndef CHISA_MODEL_ARCHITECTURAL
#define CHISA_MODEL_ARCHITECTURAL 0
#endif
#if CHISA_MODEL_ARCHITECTURAL != 0 && CHISA_MODEL_ARCHITECTURAL != 1
#error "CHISA_MODEL_ARCHITECTURAL must be 0 or 1"
#endif

namespace chisa::boom_model {
inline constexpr bool kArchitecturalModel = CHISA_MODEL_ARCHITECTURAL != 0;
// Legacy name for preserving the RTL's inactive wire/payload values. Do not
// use this flag to suppress selected state machines or oracle publication.
inline constexpr bool kInternalSignalContract = !kArchitecturalModel;
}  // namespace chisa::boom_model
