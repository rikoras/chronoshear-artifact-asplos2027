#include "rocket_decode.h"
#include "fp_decode.h"

namespace chisa::rocket_model {
namespace {
DecodedCtrl integer_alu(unsigned fn, bool immediate, bool word = false) {
  DecodedCtrl c{};
  c.legal = c.wxd = c.rxs1 = 1;
  c.rxs2 = !immediate;
  c.sel_alu1 = A1_RS1;
  c.sel_alu2 = immediate ? A2_IMM : A2_RS2;
  c.sel_imm = IMM_I;
  c.alu_dw = word ? DW_32 : DW_XPR;
  c.alu_fn = fn;
  return c;
}
DecodedCtrl floating(uint32_t inst) {
  const auto fp = decode_fp_instruction(inst);
  if (!fp.legal()) return {};
  DecodedCtrl c{};
  c.legal = c.fp = 1;
  c.dp = fp.input_type || fp.output_type;
  c.alu_dw = DW_XPR; c.sel_imm = IMM_I;
  c.rfs1 = c.rfs2 = c.wfd = 1;
  switch (fp.operation) {
    case FpOperation::Load: case FpOperation::Store:
      c.mem = c.rxs1 = 1;
      c.mem_cmd = fp.operation == FpOperation::Load ? M_XRD : M_XWR;
      c.sel_alu1 = A1_RS1; c.sel_alu2 = A2_IMM;
      c.sel_imm = fp.operation == FpOperation::Load ? IMM_I : IMM_S;
      c.rfs1 = 0; c.rfs2 = fp.operation == FpOperation::Store;
      c.wfd = fp.operation == FpOperation::Load;
      break;
    case FpOperation::FromInteger: case FpOperation::MoveFromInteger:
      c.rfs1 = c.rfs2 = 0; c.rxs1 = 1; c.sel_alu1 = A1_RS1;
      break;
    case FpOperation::ToInteger: case FpOperation::MoveToInteger:
    case FpOperation::Classify:
      c.rfs2 = c.wfd = 0; c.wxd = 1;
      break;
    case FpOperation::Compare:
      c.wfd = 0; c.wxd = 1;
      break;
    case FpOperation::SquareRoot: case FpOperation::ConvertFormat:
      c.rfs2 = 0;
      break;
    case FpOperation::FusedMultiplyAdd:
      c.rfs3 = 1;
      break;
    default: break;
  }
  return c;
}
}  // namespace

// ISA operations, with explicit defaults for unused controls. No synthesized
// equations are used to imitate the hardware's choices for don't-care bits.
DecodedCtrl decode(uint32_t inst) {
  const unsigned opcode = inst & 127, f3 = (inst >> 12) & 7, f7 = inst >> 25;
  const unsigned rd = (inst >> 7) & 31, rs1 = (inst >> 15) & 31, rs2 = (inst >> 20) & 31;
  DecodedCtrl c{};
  c.alu_dw = DW_XPR; c.sel_imm = IMM_I;
  switch (opcode) {
    case 0x63: {
      static constexpr uint8_t branch_fn[8] = {FN_SEQ,FN_SNE,0,0,FN_SLT,FN_SGE,FN_SLTU,FN_SGEU};
      if (f3 == 2 || f3 == 3) return {};
      c = integer_alu(branch_fn[f3], false);
      c.branch = 1; c.wxd = 0; c.sel_imm = IMM_SB;
      return c;
    }
    case 0x6f:
      c.legal = c.jal = c.wxd = 1;
      c.sel_alu1 = A1_PC; c.sel_alu2 = A2_SIZE; c.sel_imm = IMM_UJ;
      return c;
    case 0x67:
      if (f3 != 0) return {};
      c = integer_alu(FN_ADD, true); c.jalr = 1;
      return c;
    case 0x37: case 0x17:
      c.legal = c.wxd = 1;
      c.sel_alu1 = opcode == 0x17 ? A1_PC : A1_ZERO;
      c.sel_alu2 = A2_IMM; c.sel_imm = IMM_U;
      return c;
    case 0x03: case 0x23:
      if ((opcode == 0x03 && f3 == 7) || (opcode == 0x23 && f3 > 3)) return {};
      c = integer_alu(FN_ADD, true);
      c.mem = 1; c.mem_cmd = opcode == 0x03 ? M_XRD : M_XWR;
      c.wxd = opcode == 0x03; c.rxs2 = opcode == 0x23;
      c.sel_imm = opcode == 0x03 ? IMM_I : IMM_S;
      return c;
    case 0x13: case 0x1b: case 0x33: case 0x3b: {
      const bool imm = opcode == 0x13 || opcode == 0x1b;
      const bool word = opcode == 0x1b || opcode == 0x3b;
      if (!imm && f7 == 1) {
        if (word && f3 >= 1 && f3 <= 3) return {};
        // The serial unit executes both multiply and divide. Its command
        // encoding coincides with funct3 for this instruction family.
        c = integer_alu(f3, false, word); c.div = 1;
        return c;
      }
      if (word && f3 != 0 && f3 != 1 && f3 != 5) return {};
      if (!imm && f7 != 0 && !(f7 == 0x20 && (f3 == 0 || f3 == 5))) return {};
      static constexpr uint8_t alu_fn[8] = {FN_ADD,FN_SL,FN_SLT,FN_SLTU,FN_XOR,FN_SR,FN_OR,FN_AND};
      unsigned fn = alu_fn[f3];
      if (imm && (f3 == 1 || f3 == 5)) {
        const unsigned upper = word ? f7 : f7 >> 1;
        const unsigned arithmetic = word ? 0x20 : 0x10;
        if (upper != 0 && !(f3 == 5 && upper == arithmetic)) return {};
        if (upper == arithmetic) fn = FN_SRA;
      } else if (!imm && f7 == 0x20) {
        fn = f3 == 0 ? FN_SUB : FN_SRA;
      }
      return integer_alu(fn, imm, word);
    }
    case 0x0f:
      if (f3 > 1) return {};
      c.legal = c.fence = 1; c.fence_i = f3 == 1;
      return c;
    case 0x73:
      if (f3 == 0) {
        if (rd != 0) return {};
        if (f7 == 9) {
          c.legal = c.mem = c.rxs1 = c.rxs2 = 1;
          c.mem_cmd = M_SFENCE; c.sel_alu1 = A1_RS1;
          return c;
        }
        if (rs1 != 0) return {};
        switch (inst >> 20) {
          case 0x000: case 0x001: // ECALL / EBREAK
          case 0x102: case 0x302: // SRET / MRET
          case 0x105: case 0x305: // WFI / implementation CEASE
          case 0x7b2: // DRET; this configuration does not implement NMI/MNRET
            c.legal = 1; c.csr = CSR_I; return c;
          default: return {};
        }
      }
      if (f3 == 4) return {};
      c.legal = c.wxd = 1;
      c.csr = (f3 & 3) == 1 ? CSR_W : (f3 & 3) == 2 ? CSR_S : CSR_C;
      if (f3 < 4) { c.rxs1 = 1; c.sel_alu1 = A1_RS1; }
      else { c.sel_alu2 = A2_IMM; c.sel_imm = IMM_Z; }
      return c;
    case 0x2f: {
      if (f3 != 2 && f3 != 3) return {};
      const unsigned operation = inst >> 27;
      switch (operation) {
        case 0x00: c.mem_cmd = M_XA_ADD; break;
        case 0x01: c.mem_cmd = M_XA_SWAP; break;
        case 0x02: if (rs2 != 0) return {}; c.mem_cmd = M_XLR; break;
        case 0x03: c.mem_cmd = M_XSC; break;
        case 0x04: c.mem_cmd = M_XA_XOR; break;
        case 0x08: c.mem_cmd = M_XA_OR; break;
        case 0x0c: c.mem_cmd = M_XA_AND; break;
        case 0x10: c.mem_cmd = M_XA_MIN; break;
        case 0x14: c.mem_cmd = M_XA_MAX; break;
        case 0x18: c.mem_cmd = M_XA_MINU; break;
        case 0x1c: c.mem_cmd = M_XA_MAXU; break;
        default: return {};
      }
      c.legal = c.mem = c.amo = c.wxd = c.rxs1 = 1;
      c.rxs2 = operation != 2; c.sel_alu1 = A1_RS1;
      return c;
    }
    case 0x07: case 0x27: case 0x43: case 0x47: case 0x4b: case 0x4f: case 0x53:
      return floating(inst);
    default: return {};
  }
}
}  // namespace chisa::rocket_model
