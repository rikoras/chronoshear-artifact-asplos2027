#pragma once
#include "../common/micro_op.h"
#include "../../common/softfloat_fp.h"

namespace chisa::boom_model::wide {
// UOPCodeFPUDecoder typeTagOut: FMV.S.X already produces a boxed 65-bit
// image, so it passes through the D arm just like FMV.D.X. Only FCVT.S.X
// produces a narrow FU result for the wrapper to box.
inline bool ifpu_output_double(std::uint8_t uopc) {
  return uopc == uopFMV_S_X || uopc == uopFMV_D_X || uopc == uopFCVT_D_X;
}

inline sfp::rec_t ifpu_pipe_data(std::uint8_t uopc, sfp::rec_t register_image) {
  if (uopc != uopFCVT_S_X) return register_image;
  // Undo the existing S swizzle; no second numerical conversion is needed.
  // The wrapper reads only the low 33 bits with typeTagOut=S. Its unused
  // upper padding is not claimed equivalent to IntToFP's parallel D result.
  const std::uint64_t single =
      ((static_cast<std::uint64_t>(register_image >> 31) & 1u) << 32) |
      ((static_cast<std::uint64_t>(register_image >> 52) & 1u) << 31) |
      (static_cast<std::uint64_t>(register_image) & UINT64_C(0x7fffffff));
  return (register_image & ~((sfp::rec_t{1} << 33) - 1)) | single;
}
} // namespace chisa::boom_model::wide
