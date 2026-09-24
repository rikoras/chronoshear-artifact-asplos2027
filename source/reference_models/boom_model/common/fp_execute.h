#pragma once
#include "core_types.h"
#include "../../common/softfloat_fp.h"
namespace chisa::boom_model {
std::uint32_t fp_rm(const MicroOp&, const GuiderCSR&);
sfp::FpRes fp_compute(const MicroOp&, std::uint32_t rounding, std::uint64_t a, std::uint64_t b, std::uint64_t c);
sfp::FpRes fp_compute_i2f(const MicroOp&, std::uint32_t rounding, std::uint64_t source);
sfp::rec_t fp_result_rec(const MicroOp&, std::uint64_t ieee);
bool fp_divsqrt_special(const MicroOp&, std::uint64_t a, std::uint64_t b);
}
