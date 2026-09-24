#include "execute.h"

// Shared verbatim from the current rewritten Small core. No pipeline state.
namespace chisa::boom_model {
namespace {
constexpr uint8_t OP1_RS1 = 0, OP1_ZERO = 1, OP1_PC = 2;
constexpr uint8_t OP2_RS2 = 0, OP2_IMM = 1, OP2_ZERO = 2, OP2_NEXT = 3, OP2_IMMC = 4;
constexpr uint8_t IS_I = 0, IS_S = 1, IS_B = 2, IS_U = 3, IS_J = 4;
constexpr uint8_t FN_ADD = 0, FN_SL = 1, FN_SEQ = 2, FN_SNE = 3, FN_XOR = 4, FN_SR = 5, FN_OR = 6,
                  FN_AND = 7, FN_SUB = 10, FN_SRA = 11, FN_SLT = 12, FN_SGE = 13, FN_SLTU = 14, FN_SGEU = 15;
inline int64_t sext(uint64_t x, int bits) {
  const uint64_t m = 1ULL << (bits - 1);
  return static_cast<int64_t>((x ^ m) - m);
}
}

uint64_t decode_imm(const MicroOp& u) {
  if (u.uopc == uopAMO_AG || (u.uopc == uopLD && u.mem_cmd == 6)) return 0;
  const uint32_t i = u.inst;
  switch (u.ctrl.imm_sel) {
    case IS_I: return static_cast<uint64_t>(sext(i >> 20, 12));
    case IS_S: return static_cast<uint64_t>(sext(((i >> 25) << 5) | ((i >> 7) & 0x1F), 12));
    case IS_B: return static_cast<uint64_t>(sext((((i >> 31) & 1) << 12) | (((i >> 7) & 1) << 11) |
                                                 (((i >> 25) & 0x3F) << 5) | (((i >> 8) & 0xF) << 1), 13));
    case IS_U: return static_cast<uint64_t>(sext(i & 0xFFFFF000u, 32));
    case IS_J: return static_cast<uint64_t>(sext((((i >> 31) & 1) << 20) | (((i >> 12) & 0xFF) << 12) |
                                                 (((i >> 20) & 1) << 11) | (((i >> 21) & 0x3FF) << 1), 21));
  }
  return 0;
}

uint64_t alu_op(uint8_t fn, uint8_t dw, uint64_t in1, uint64_t in2) {
  const uint32_t shamt = dw ? (in2 & 0x3F) : (in2 & 0x1F);
  uint64_t out;
  switch (fn) {
    case FN_ADD: out = in1 + in2; break;
    case FN_SUB: out = in1 - in2; break;
    case FN_AND: out = in1 & in2; break;
    case FN_OR: out = in1 | in2; break;
    case FN_XOR: out = in1 ^ in2; break;
    case FN_SL: out = in1 << shamt; break;
    case FN_SR: out = dw ? (in1 >> shamt) : (static_cast<uint32_t>(in1) >> shamt); break;
    case FN_SRA: out = dw ? static_cast<uint64_t>(static_cast<int64_t>(in1) >> shamt)
                          : static_cast<uint64_t>(static_cast<int32_t>(in1) >> shamt); break;
    case FN_SLT: return (static_cast<int64_t>(in1) < static_cast<int64_t>(in2)) ? 1 : 0;
    case FN_SGE: return (static_cast<int64_t>(in1) >= static_cast<int64_t>(in2)) ? 1 : 0;
    case FN_SLTU: return (in1 < in2) ? 1 : 0;
    case FN_SGEU: return (in1 >= in2) ? 1 : 0;
    case FN_SEQ: return (in1 == in2) ? 1 : 0;
    case FN_SNE: return (in1 != in2) ? 1 : 0;
    default: out = in1 + in2; break;
  }
  if (!dw) out = static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(out)));
  return out;
}

uint64_t mul_op(uint8_t fn, uint64_t a, uint64_t b, bool word) {
  if (word) return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(
      static_cast<uint32_t>(a) * static_cast<uint32_t>(b))));
  switch (fn) {
    case 0: return static_cast<uint64_t>(static_cast<__int128>(static_cast<int64_t>(a)) * static_cast<int64_t>(b));
    case 1: return static_cast<uint64_t>((static_cast<__int128>(static_cast<int64_t>(a)) * static_cast<int64_t>(b)) >> 64);
    case 2: return static_cast<uint64_t>((static_cast<__int128>(static_cast<int64_t>(a)) * static_cast<unsigned __int128>(b)) >> 64);
    default: return static_cast<uint64_t>((static_cast<unsigned __int128>(a) * static_cast<unsigned __int128>(b)) >> 64);
  }
}

uint64_t div_op(uint8_t fn, uint64_t a, uint64_t b, bool word) {
  const bool rem = (fn & 2) != 0, uns = (fn & 1) != 0;
  if (word) {
    if (uns) {
      const uint32_t x = a, y = b;
      const uint32_t q = y ? x / y : 0xFFFFFFFFu, r = y ? x % y : x;
      return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(rem ? r : q)));
    }
    const int32_t x = static_cast<int32_t>(a), y = static_cast<int32_t>(b);
    int32_t q, r;
    if (y == 0) { q = -1; r = x; }
    else if (x == INT32_MIN && y == -1) { q = INT32_MIN; r = 0; }
    else { q = x / y; r = x % y; }
    return static_cast<uint64_t>(static_cast<int64_t>(rem ? r : q));
  }
  if (uns) { const uint64_t q = b ? a / b : ~0ULL, r = b ? a % b : a; return rem ? r : q; }
  const int64_t x = static_cast<int64_t>(a), y = static_cast<int64_t>(b);
  int64_t q, r;
  if (y == 0) { q = -1; r = x; }
  else if (x == INT64_MIN && y == -1) { q = INT64_MIN; r = 0; }
  else { q = x / y; r = x % y; }
  return static_cast<uint64_t>(rem ? r : q);
}

uint8_t branch_pc_sel(uint8_t br_type, uint64_t rs1, uint64_t rs2) {
  const bool eq = rs1 == rs2, ltu = rs1 < rs2;
  const bool lt = static_cast<int64_t>(rs1) < static_cast<int64_t>(rs2);
  switch (br_type) {
    case BR_NE: return !eq ? PC_BRJMP : PC_PLUS4;
    case BR_EQ: return eq ? PC_BRJMP : PC_PLUS4;
    case BR_GE: return !lt ? PC_BRJMP : PC_PLUS4;
    case BR_GEU: return !ltu ? PC_BRJMP : PC_PLUS4;
    case BR_LT: return lt ? PC_BRJMP : PC_PLUS4;
    case BR_LTU: return ltu ? PC_BRJMP : PC_PLUS4;
    case BR_J: return PC_BRJMP;
    case BR_JR: return PC_JALR;
  }
  return PC_PLUS4;
}

// Division latency issue -> ROB busy clear (rocket MulDiv, divEarlyOut).
uint8_t div_latency(uint8_t fn, uint8_t dw, uint64_t in1, uint64_t in2) {
  const bool uns = (fn & 1) != 0, rem = (fn & 2) != 0;
  auto ext = [&](uint64_t x) -> uint64_t {
    if (dw) return x;
    const uint32_t lo = static_cast<uint32_t>(x);
    return uns ? static_cast<uint64_t>(lo)
               : static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(lo)));
  };
  const uint64_t lhs = ext(in1), rhs = ext(in2);
  const bool lhs_sign = !uns && (static_cast<int64_t>(lhs) < 0);
  const bool rhs_sign = !uns && (static_cast<int64_t>(rhs) < 0);
  const int neg_in = (lhs_sign || rhs_sign) ? 1 : 0;
  const uint64_t alhs = lhs_sign ? (0 - lhs) : lhs;
  const uint64_t arhs = rhs_sign ? (0 - rhs) : rhs;
  const bool divby0 = arhs == 0;
  bool neg_out = rem ? lhs_sign : (lhs_sign != rhs_sign);
  if (divby0 && !rem) neg_out = false;
  auto log2f = [](uint64_t x) -> int { return x ? 63 - __builtin_clzll(x) : 0; };
  int c1 = 1;
  if (!divby0) {
    const int pos = 63 - ((log2f(alhs) - log2f(arhs)) & 63);
    if (pos >= 1) c1 = pos;
  }
  return static_cast<uint8_t>(2 + neg_in + (66 - c1) + neg_out + 1);
}

uint64_t compute_int_result(const MicroOp& u, uint64_t rs1, uint64_t rs2) {
  if (u.fu_code & FU_MUL) return mul_op(u.ctrl.op_fcn, rs1, rs2, u.ctrl.fcn_dw == 0);
  if (u.fu_code & FU_DIV) return div_op(u.ctrl.op_fcn, rs1, rs2, u.ctrl.fcn_dw == 0);
  if (u.is_jal || u.is_jalr) return u.debug_pc + (u.is_rvc ? 2 : 4);
  const uint64_t imm = decode_imm(u);
  const uint64_t op1 = (u.ctrl.op1_sel == OP1_PC) ? u.debug_pc
                     : (u.ctrl.op1_sel == OP1_ZERO) ? 0 : rs1;
  const uint64_t op2 = (u.ctrl.op2_sel == OP2_IMM) ? imm
                     : (u.ctrl.op2_sel == OP2_IMMC) ? ((u.inst >> 15) & 0x1F)
                     : (u.ctrl.op2_sel == OP2_NEXT) ? (u.is_rvc ? 2 : 4) : rs2;
  return alu_op(u.ctrl.op_fcn, u.ctrl.fcn_dw, op1, op2);
}

}  // namespace chisa::boom_model
