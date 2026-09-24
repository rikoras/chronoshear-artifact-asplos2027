#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include "boom_config.h"

namespace chisa::boom_model {

// The four wrapper registers expose only these fields. Keep their payload
// advancing even when valid is false: fu_code is an unconditional oracle.
struct FpWrapperUop {
  boomcfg::br_mask_t br_mask = 0;
  std::uint8_t rob_idx = 0;
  std::uint16_t fu_code = 0;
  // Partition-cut lanes of the FPU's stage registers.
  std::uint8_t pdst = 0, stq_idx = 0, uopc = 0, dst_rtype = 0, flags = 0;  // flags: 1 is_amo, 2 uses_stq
  void clear() { *this = FpWrapperUop{}; }
};

template <bool PreserveInvalid = true>
inline void advance_fp_wrapper(FpWrapperUop (&uops)[4], bool (&valids)[4],
                               FpWrapperUop input, bool input_valid,
                               boomcfg::br_mask_t resolve,
                               boomcfg::br_mask_t mispredict, bool flush) {
  for (int stage = 3; stage >= 0; --stage) {
    const bool valid = stage == 0 ? input_valid : valids[stage - 1];
    if (!PreserveInvalid && !valid) { valids[stage] = false; continue; }
    const FpWrapperUop source = stage == 0 ? input : uops[stage - 1];
    valids[stage] = valid && !(source.br_mask & mispredict) && !flush;
    if (PreserveInvalid || valids[stage]) {
      uops[stage] = source;
      uops[stage].br_mask &= static_cast<boomcfg::br_mask_t>(~resolve);
    }
  }
}

inline void require_external_fp_result(bool connected, bool response_valid,
                                       bool wrapper_valid, FpWrapperUop wrapper,
                                       FpWrapperUop expected, bool already_consumed,
                                       std::uint64_t core_cycle = 0) {
  const auto fail = [&](const char* reason) {
    throw std::runtime_error(std::string(reason) + " core_cycle=" + std::to_string(core_cycle) +
        " expected_rob=" + std::to_string(expected.rob_idx) +
        " wrapper_rob=" + std::to_string(wrapper.rob_idx) +
        " expected_fu=" + std::to_string(expected.fu_code) +
        " wrapper_fu=" + std::to_string(wrapper.fu_code) +
        " expected_br=" + std::to_string(expected.br_mask) +
        " wrapper_br=" + std::to_string(wrapper.br_mask) +
        " wrapper_valid=" + std::to_string(wrapper_valid) +
        " already_consumed=" + std::to_string(already_consumed));
  };
  if (!connected || !response_valid)
    fail("BOOM external FPU result missing at fixed-pipeline writeback");
  if (!wrapper_valid || already_consumed || wrapper.rob_idx != expected.rob_idx ||
      wrapper.fu_code != expected.fu_code || wrapper.br_mask != expected.br_mask)
    fail("BOOM external FPU result does not match the writeback operation");
}

}  // namespace chisa::boom_model
