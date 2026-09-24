#pragma once
#include <cstdint>

namespace chisa::rocket_model {

// RV64 F/D semantics shared by the core and FPU. Rounding-mode legality,
// including dynamic frm, is checked separately when the instruction issues.
enum class FpOperation : uint8_t {
  Illegal, Load, Store, Add, Subtract, Multiply, FusedMultiplyAdd, Divide,
  SquareRoot, SignInject, MinMax, Compare, Classify, MoveToInteger,
  MoveFromInteger, ToInteger, FromInteger, ConvertFormat
};
struct FpInstruction {
  FpOperation operation = FpOperation::Illegal;
  uint8_t input_type = 0, output_type = 0;  // binary32=0, binary64=1
  bool legal() const { return operation != FpOperation::Illegal; }
};
inline uint8_t fp_fma_operation(uint32_t inst) {
  switch (inst & 127) {
    case 0x43: return 0; // a*b+c
    case 0x47: return 1; // a*b-c
    case 0x4b: return 2; // -a*b+c
    case 0x4f: return 3; // -a*b-c
    case 0x53: return ((inst >> 25) & 0x7e) == 4 ? 1 : 0; // SUB vs ADD/MUL
    default: return 0;
  }
}
inline FpInstruction decode_fp_instruction(uint32_t inst) {
  const unsigned opcode = inst & 127, sub = (inst >> 12) & 7;
  const unsigned function = inst >> 25, rs2 = (inst >> 20) & 31;
  const auto op = [](FpOperation operation, unsigned in, unsigned out) {
    return FpInstruction{operation, static_cast<uint8_t>(in), static_cast<uint8_t>(out)};
  };
  if (opcode == 0x07 || opcode == 0x27) {
    if (sub != 2 && sub != 3) return {};
    return op(opcode == 0x07 ? FpOperation::Load : FpOperation::Store, sub-2, sub-2);
  }
  if (opcode == 0x43 || opcode == 0x47 || opcode == 0x4b || opcode == 0x4f) {
    const unsigned format = (inst >> 25) & 3;
    return format <= 1 ? op(FpOperation::FusedMultiplyAdd, format, format) : FpInstruction{};
  }
  if (opcode != 0x53) return {};
  const unsigned format = function & 1;
  switch (function) {
    case 0x00: case 0x01: return op(FpOperation::Add, format, format);
    case 0x04: case 0x05: return op(FpOperation::Subtract, format, format);
    case 0x08: case 0x09: return op(FpOperation::Multiply, format, format);
    case 0x0c: case 0x0d: return op(FpOperation::Divide, format, format);
    case 0x2c: case 0x2d:
      if (rs2 == 0) return op(FpOperation::SquareRoot, format, format);
      break;
    case 0x10: case 0x11:
      if (sub <= 2) return op(FpOperation::SignInject, format, format);
      break;
    case 0x14: case 0x15:
      if (sub <= 1) return op(FpOperation::MinMax, format, format);
      break;
    case 0x50: case 0x51:
      if (sub <= 2) return op(FpOperation::Compare, format, format);
      break;
    case 0x20:  // FCVT.S.D
      if (rs2 == 1) return op(FpOperation::ConvertFormat, 1, 0);
      break;
    case 0x21:  // FCVT.D.S
      if (rs2 == 0) return op(FpOperation::ConvertFormat, 0, 1);
      break;
    case 0x60: case 0x61:
      if (rs2 <= 3) return op(FpOperation::ToInteger, format, format);
      break;
    case 0x68: case 0x69:
      if (rs2 <= 3) return op(FpOperation::FromInteger, format, format);
      break;
    case 0x70: case 0x71:
      if (rs2 == 0 && sub == 0) return op(FpOperation::MoveToInteger, format, format);
      if (rs2 == 0 && sub == 1) return op(FpOperation::Classify, format, format);
      break;
    case 0x78: case 0x79:
      if (rs2 == 0 && sub == 0) return op(FpOperation::MoveFromInteger, format, format);
      break;
  }
  return {};
}
}  // namespace chisa::rocket_model
