#pragma once
#include <array>
#include <cstdint>
namespace chisa::boom_system::protocol {
struct FpuInputs {
  bool reset = false;
  bool valid = false;
  std::uint8_t uopc = 0;
  std::uint32_t imm_packed = 0;
  std::array<std::uint64_t, 3> operands{};
  std::uint8_t operand_bit64 = 0;
  std::uint8_t fcsr_rm = 0;

  bool operator==(const FpuInputs& other) const {
    return reset == other.reset && valid == other.valid &&
           uopc == other.uopc && imm_packed == other.imm_packed &&
           operands == other.operands &&
           operand_bit64 == other.operand_bit64 &&
           fcsr_rm == other.fcsr_rm;
  }
  bool operator!=(const FpuInputs& other) const { return !(*this == other); }
};

struct FpuOutputs {
  bool valid = false;
  std::uint64_t data = 0;
  bool data_bit64 = false;
  std::uint8_t exception_flags = 0;
};

// Exact order used by fpu_profile_selector().  Every entry is a PRE register
// stream.  Slots 0..27 are the locked SmallBoom contract; slots 28..58 are
// the additional LargeBoom payload/register faces.  Wide FIRRTL registers
// occupy one oracle slot per manifest word rather than silently dropping the
// high word.
// Slots 59/60 add the Small cut experiment's registered FPMU result; all
// existing Small/Large selector indices retain their original meaning.
using FpuOracleState = std::array<std::uint64_t, 70>;   // 61..69: partition-cut output registers

struct FDivSqrtInputs {
  bool reset = false;
  bool in_valid = false;
  bool sqrt_op = false;
  std::uint64_t a = 0;
  std::uint64_t b = 0;
  bool a_bit64 = false;
  bool b_bit64 = false;
  std::uint8_t rounding_mode = 0;
  bool detect_tininess = false;

  bool operator==(const FDivSqrtInputs& other) const {
    return reset == other.reset && in_valid == other.in_valid &&
           sqrt_op == other.sqrt_op && a == other.a && b == other.b &&
           a_bit64 == other.a_bit64 && b_bit64 == other.b_bit64 &&
           rounding_mode == other.rounding_mode &&
           detect_tininess == other.detect_tininess;
  }
  bool operator!=(const FDivSqrtInputs& other) const {
    return !(*this == other);
  }
};

struct FDivSqrtOutputs {
  bool in_ready_div = false;
  bool in_ready_sqrt = false;
  bool out_valid_div = false;
  bool out_valid_sqrt = false;
  std::uint64_t out = 0;
  bool out_bit64 = false;
  std::uint8_t exception_flags = 0;
};

// Exact manifest order: the 35 SmallBoom streams first, followed by the four
// additional LargeBoom internal-register words. All are PRE register
// streams.
using FDivSqrtOracleState = std::array<std::uint64_t, 40>;   // 39: partition-cut cycleNum_E

}
