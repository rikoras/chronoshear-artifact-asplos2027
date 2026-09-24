#include "fp_execute.h"
#include "fp_semantics.h"

namespace chisa::boom_model {
uint32_t fp_rm(const MicroOp& u, const GuiderCSR& csr) {
  const uint32_t rm = (u.inst >> 12) & 7;
  return (rm == 7) ? ((csr.fcsr >> 5) & 7) : rm;
}

sfp::FpRes fp_compute(const MicroOp& u, uint32_t rm, uint64_t a, uint64_t b, uint64_t c) {
  using namespace sfp;
  const uint32_t inst = u.inst;
  switch (u.uopc) {
    case uopFADD_S: case uopFSUB_S: case uopFMUL_S:
    case uopFMADD_S: case uopFMSUB_S: case uopFNMADD_S: case uopFNMSUB_S: {
      FpRes r = fma_op32(inst, rm, unbox32(a), unbox32(b), unbox32(c));
      r.ieee = box32(static_cast<uint32_t>(r.ieee));
      return r;
    }
    case uopFADD_D: case uopFSUB_D: case uopFMUL_D:
    case uopFMADD_D: case uopFMSUB_D: case uopFNMADD_D: case uopFNMSUB_D:
      return fma_op64(inst, rm, a, b, c);
    case uopFSGNJ_S: case uopFMINMAX_S: {
      FpRes r = fastpipe32(inst, rm, unbox32(a), unbox32(b));
      r.ieee = box32(static_cast<uint32_t>(r.ieee));
      return r;
    }
    case uopFSGNJ_D: case uopFMINMAX_D: return fastpipe64(inst, rm, a, b);
    case uopFCVT_S_D: { FpRes r = cvt_d_to_s(rm, a); r.ieee = box32(static_cast<uint32_t>(r.ieee)); return r; }
    case uopFCVT_D_S: return cvt_s_to_d(rm, unbox32(a));
    case uopFMV_X_S: return FpRes{fp_move_word_to_x(a), 0};
    case uopFCVT_X_S: case uopFCLASS_S: case uopCMPR_S: return fp_to_int32(inst, rm, unbox32(a), unbox32(b));
    case uopFMV_X_D: case uopFCVT_X_D: case uopFCLASS_D: case uopCMPR_D: return fp_to_int64(inst, rm, a, b);
    case uopFDIV_S: {
      // Small's FDivSqrtUnit widens S inputs, runs its D unit, then narrows.
      // The input converters' exception flags have no consumer in this RTL;
      // in particular, they quiet signaling NaNs before the divide sees them.
      const auto wide_a = cvt_s_to_d(0, unbox32(a));
      const auto wide_b = cvt_s_to_d(0, unbox32(b));
      const auto wide = div_op64(rm, wide_a.ieee, wide_b.ieee);
      auto result = cvt_d_to_s(rm, wide.ieee);
      result.exc |= wide.exc;
      result.ieee = box32(static_cast<uint32_t>(result.ieee));
      return result;
    }
    case uopFDIV_D: return div_op64(rm, a, b);
    case uopFSQRT_S: {
      const auto wide_a = cvt_s_to_d(0, unbox32(a));
      const auto wide = sqrt_op64(rm, wide_a.ieee);
      auto result = cvt_d_to_s(rm, wide.ieee);
      result.exc |= wide.exc;
      result.ieee = box32(static_cast<uint32_t>(result.ieee));
      return result;
    }
    case uopFSQRT_D: return sqrt_op64(rm, a);
    default: return sfp::FpRes{0, 0};
  }
}

sfp::FpRes fp_compute_i2f(const MicroOp& u, uint32_t rm, uint64_t rs1) {
  using namespace sfp;
  switch (u.uopc) {
    case uopFMV_S_X: return FpRes{box32(static_cast<uint32_t>(rs1)), 0};
    case uopFMV_D_X: return FpRes{rs1, 0};
    case uopFCVT_S_X: { FpRes r = int_to_fp(u.inst, rm, false, rs1); r.ieee = box32(static_cast<uint32_t>(r.ieee)); return r; }
    case uopFCVT_D_X: return int_to_fp(u.inst, rm, true, rs1);
    default: return FpRes{0, 0};
  }
}

sfp::rec_t fp_result_rec(const MicroOp& u, uint64_t ieee) {
  // Both raw integer-to-FP moves use the register-file recoder. A plain
  // D recoding loses the embedded S encoding for NaN payloads, so a later
  // FMV.X.W would read changed low bits after FMV.D.X.
  if (u.uopc == uopFMV_S_X || u.uopc == uopFMV_D_X)
    return sfp::hf_recode64(ieee, u.uopc == uopFMV_S_X);
  if (u.fp_single) return sfp::hf_pub_box_s(sfp::rec33_from_fn32(static_cast<uint32_t>(sfp::unbox32(ieee))));
  return sfp::rec65_from_fn64(ieee);
}

bool fp_divsqrt_special(const MicroOp& u, uint64_t a, uint64_t b) {
  const bool sqrt = u.uopc == uopFSQRT_S || u.uopc == uopFSQRT_D;
  if (u.uopc == uopFDIV_S || u.uopc == uopFSQRT_S) {
    const uint32_t x = sfp::unbox32(a), y = sfp::unbox32(b);
    const uint32_t ax = x & 0x7fffffffU, ay = y & 0x7fffffffU;
    const bool x_special = ax == 0 || (ax >> 23) == 0xff;
    if (sqrt) return x_special || (x >> 31);
    const bool y_special = ay == 0 || (ay >> 23) == 0xff;
    return x_special || y_special;
  }
  const uint64_t ax = a & 0x7fffffffffffffffULL;
  const uint64_t ay = b & 0x7fffffffffffffffULL;
  const bool x_special = ax == 0 || (ax >> 52) == 0x7ff;
  if (sqrt) return x_special || (a >> 63);
  const bool y_special = ay == 0 || (ay >> 52) == 0x7ff;
  return x_special || y_special;
}

}  // namespace chisa::boom_model
