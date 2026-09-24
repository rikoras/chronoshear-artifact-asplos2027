#pragma once
// Shared values/contracts only. Never include a concrete BOOM core here.
#include "micro_op.h"
#include "csr_state.h"
#include "memory_contract.h"
#include "fp_state.h"

namespace chisa::boom_model {
inline constexpr std::uint8_t IS_INVALID = 0;
inline constexpr std::uint8_t IS_VALID_1 = 1;
inline constexpr std::uint8_t IS_VALID_2 = 2;
}  // namespace chisa::boom_model
