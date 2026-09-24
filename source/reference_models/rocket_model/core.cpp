// rocket_model core: two-phase model of the DefaultConfig Rocket core.
// Pipeline timing retains the previous native core's evaluate/commit order;
// instruction semantics and arithmetic use software operations.
#include "core.h"

#include <cstring>

#include "rocket_decode.h"
#include "rvc_expand.h"

namespace chisa::rocket_model {

namespace {

constexpr uint64_t kVaddrMask = UINT64_C(0x7fffffffff);      // vaddrBits = 39
constexpr uint64_t kVaddrExtMask = UINT64_C(0xffffffffff);   // vaddrBitsExtended = 40
constexpr int kWideSmallBits = 6;
constexpr uint64_t kWideSmallMask = (UINT64_C(1) << kWideSmallBits) - 1;
constexpr uint64_t kMedelegMask = UINT64_C(0xb15d);
constexpr uint64_t kMidelegMask = UINT64_C(0x222);
constexpr uint64_t kCounterenMask = UINT64_C(0x7);

// MulDiv: mulUnroll=8, divUnroll=1, mulEarlyOut, divEarlyOut.
constexpr int kMulUnroll = 8;
constexpr int kMulEndCount = 64 / kMulUnroll - 1;   // 7
constexpr int kMulDw32Start = 64 / kMulUnroll / 2;  // 4
constexpr int kDivEndCount = 64;

inline uint64_t sext32(uint64_t v) {
  return static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(v)));
}
inline uint64_t sign_extend(uint64_t value, unsigned width) {
  const uint64_t mask = (UINT64_C(1) << width) - 1;
  const uint64_t sign = UINT64_C(1) << (width - 1);
  value &= mask;
  return (value ^ sign) - sign;
}
inline uint64_t read_medeleg(const Csr& c) { return c.medeleg & kMedelegMask; }
inline uint64_t read_mideleg(const Csr& c) { return c.mideleg & kMidelegMask; }
inline uint64_t read_epc(uint64_t value, uint64_t misa) {
  const uint64_t alignment = (misa & (UINT64_C(1) << 2)) ? 1 : 3;
  return sign_extend(value & ~alignment, 40);
}
inline uint64_t form_tvec(uint64_t value) {
  return value & ~((value & 1) ? UINT64_C(0xfe) : UINT64_C(0x2));
}
inline uint32_t rd_addr(uint32_t inst) { return (inst >> 7) & 0x1f; }
inline uint32_t rs1_addr(uint32_t inst) { return (inst >> 15) & 0x1f; }
inline uint32_t rs2_addr(uint32_t inst) { return (inst >> 20) & 0x1f; }
inline bool is_store(uint8_t cmd) { return cmd == M_XWR || cmd == M_PWR; }
inline bool is_load(uint8_t cmd) { return cmd == M_XRD; }
inline uint64_t alu_dw_trunc(uint64_t v, uint8_t dw) {
  return dw == DW_32 ? sext32(v & 0xffffffffULL) : v;
}

uint64_t alu_result(uint64_t op1, uint64_t op2, uint8_t fn, uint8_t dw) {
  uint64_t r;
  const unsigned shift = op2 & (dw == DW_32 ? 31 : 63);
  switch (fn) {
    case FN_ADD:  r = op1 + op2; break;
    case FN_SUB:  r = op1 - op2; break;
    case FN_SL:   r = op1 << shift; break;
    case FN_SR:   r = (dw == DW_32 ? uint64_t(uint32_t(op1)) : op1) >> shift; break;
    case FN_SRA:  r = uint64_t(int64_t(dw == DW_32 ? sext32(op1) : op1) >> shift); break;
    case FN_AND:  r = op1 & op2; break;
    case FN_OR:   r = op1 | op2; break;
    case FN_XOR:  r = op1 ^ op2; break;
    case FN_SLT:
    case FN_SGE:  r = (static_cast<int64_t>(op1) < static_cast<int64_t>(op2)) ? 1 : 0; break;
    case FN_SLTU:
    case FN_SGEU: r = (op1 < op2) ? 1 : 0; break;
    default:      r = 0; break;
  }
  return alu_dw_trunc(r, dw);
}

bool alu_cmp_out(uint64_t a, uint64_t b, uint8_t fn) {
  switch (fn) {
    case FN_SEQ: return a == b;
    case FN_SNE: return a != b;
    case FN_SLT: return int64_t(a) < int64_t(b);
    case FN_SGE: return int64_t(a) >= int64_t(b);
    case FN_SLTU: return a < b;
    case FN_SGEU: return a >= b;
    default: return false;
  }
}

void ex_alu(const Stage& ex, uint64_t rs0, uint64_t rs1,
            uint64_t& result, bool& branch_taken, uint64_t& adder) {
  uint64_t op1, op2;
  switch (ex.ctrl.sel_alu1) {
    case A1_RS1: op1 = rs0; break;
    case A1_PC: op1 = sign_extend(ex.pc, 40); break;
    default: op1 = 0; break;
  }
  switch (ex.ctrl.sel_alu2) {
    case A2_RS2: op2 = rs1; break;
    case A2_IMM: op2 = decode_imm(ex.inst, ex.ctrl.sel_imm); break;
    case A2_SIZE: op2 = ex.rvc ? 2 : 4; break;
    default: op2 = 0; break;
  }
  result = alu_result(op1, op2, ex.ctrl.alu_fn, ex.ctrl.alu_dw);
  branch_taken = alu_cmp_out(op1, op2, ex.ctrl.alu_fn);
  const bool sub = (ex.ctrl.alu_fn >> 3) & 1;
  adder = op1 + (sub ? ~op2 : op2) + (sub ? 1 : 0);
}

// Register operand through the bypass network recorded in the EX slot.
uint64_t rs_val(int port, const Stage& ex, const Stage& mem, const Stage& wb,
                uint64_t dmem_word_bypass) {
  if (ex.rs_bypass[port]) {
    switch (ex.rs_lsb[port] & 3) {
      case 1: return mem.wdata;
      case 2: return wb.wdata;
      case 3: return dmem_word_bypass;
      default: return 0;
    }
  }
  return (ex.rs_msb[port] << 2) | (ex.rs_lsb[port] & 3);
}

uint64_t mem_branch_target(const Stage& mem) {
  uint64_t offset = mem.rvc ? 2 : 4;
  if (mem.ctrl.branch && mem.br_taken) offset = decode_imm(mem.inst, IMM_SB);
  else if (mem.ctrl.jal) offset = decode_imm(mem.inst, IMM_UJ);
  return (mem.pc + offset) & kVaddrExtMask;
}

uint64_t mem_npc_of(const Stage& mem, uint64_t branch_target) {
  const uint64_t selected = (mem.ctrl.jalr || mem.sfence)
      ? encode_virtual_address(mem.wdata, mem.wdata) : branch_target;
  return selected & ~UINT64_C(1) & kVaddrExtMask;
}

bool breakpoint_address_match(const Csr& csr, uint64_t address) {
  const uint64_t wanted = csr.bp_0_address & kVaddrMask;
  const uint8_t tmatch = csr.bp_0_control_tmatch & 3;
  if (tmatch & 2)
    return ((address & kVaddrMask) >= wanted) ^ ((tmatch & 1) != 0);
  uint64_t mask = 0;
  bool grow = (tmatch & 1) != 0;
  for (unsigned bit = 0; bit < 4; ++bit) {
    if (grow) mask |= UINT64_C(1) << bit;
    if (bit < 3) grow = grow && ((wanted >> bit) & 1);
  }
  return (((address ^ wanted) & kVaddrMask & ~mask) == 0);
}

uint64_t div_response_data(const Div& d) {
  uint64_t result = d.resHi
      ? ((d.rem_hi >> 1) | (static_cast<uint64_t>(d.rem_top & 1) << 63))
      : d.remainder;
  if (d.req_dw == DW_32) {
    if (d.cmdMul) result = sext32((result >> 32) & UINT64_C(0xffffffff));
    else result = sext32(result & UINT64_C(0xffffffff));
  }
  return result;
}

uint32_t pmp_mask(const Csr& csr, unsigned index) {
  const auto& pmp = csr.pmp[index];
  if (!(pmp.cfg_a & 1)) return 3;
  // The retained mask field describes the address's trailing-one run, also
  // while TOR selects the separate interval comparator.
  const uint32_t first_zero = ~uint32_t(pmp.addr) & UINT32_C(0x3fffffff);
  const unsigned bits = 3 + (first_zero ? unsigned(__builtin_ctz(first_zero)) : 30);
  return bits >= 32 ? UINT32_MAX : (UINT32_C(1) << bits)-1;
}

void fill_status(const Csr& csr, RocketSystemStatusOutputs& s) {
  s = RocketSystemStatusOutputs{};
  s.debug = csr.debug;
  s.cease = csr.status_cease_r;
  s.wfi = csr.wfi;
  s.isa = static_cast<uint32_t>(csr.misa);
  s.dprv = csr.status_dprv & 3;
  s.prv = csr.mstatus_prv & 3;
  s.sd = (csr.mstatus_fs & 3) == 3;
  s.sxl = 2;
  s.uxl = 2;
  s.tsr = csr.mstatus_tsr;
  s.tw = csr.mstatus_tw;
  s.tvm = csr.mstatus_tvm;
  s.mxr = csr.mstatus_mxr;
  s.sum = csr.mstatus_sum;
  s.mprv = csr.mstatus_mprv;
  s.fs = csr.mstatus_fs & 3;
  s.mpp = csr.mstatus_mpp & 3;
  s.spp = csr.mstatus_spp;
  s.mpie = csr.mstatus_mpie;
  s.spie = csr.mstatus_spie;
  s.mie = csr.mstatus_mie;
  s.sie = csr.mstatus_sie;
}

void compute_subtractor(uint64_t rem_hi, uint8_t rem_top, uint64_t div_lo,
                        uint8_t div_hi, uint64_t& sub_lo, uint8_t& sub_hi) {
  const __uint128_t a = ((__uint128_t)(rem_top & 1) << 64) | rem_hi;
  const __uint128_t b = ((__uint128_t)(div_hi & 1) << 64) | div_lo;
  const __uint128_t r = a - b;
  sub_lo = (uint64_t)r;
  sub_hi = (uint8_t)((r >> 64) & 1);
}
__int128_t signed65(uint64_t lo, uint8_t hi) {
  return __int128_t(lo) - ((hi & 1) ? (__int128_t(1) << 64) : 0);
}

uint64_t replicate_store_data(uint64_t rs2, uint8_t size) {
  switch (size & 3) {
    case 0: { uint64_t r = rs2 & 0xff; r |= r << 8; r |= r << 16; r |= r << 32; return r; }
    case 1: { uint64_t r = rs2 & 0xffff; r |= r << 16; r |= r << 32; return r; }
    case 2: { const uint64_t w = rs2 & 0xffffffffULL; return (w << 32) | w; }
    default: return rs2;
  }
}

}  // namespace

// ---------------------------------------------------------- pure helpers ----

uint64_t encode_virtual_address(uint64_t a0, uint64_t ea) {
  const int64_t upper = static_cast<int64_t>(a0) >> 39;
  const bool canonical = upper == 0 || upper == -1;
  const bool msb = canonical ? ((ea >> 39) & 1) : (((ea >> 38) & 1) == 0);
  return ((static_cast<uint64_t>(msb) << 39) | (ea & kVaddrMask)) & kVaddrExtMask;
}

uint64_t decode_imm(uint32_t inst, uint8_t sel_imm) {
  int32_t imm32 = 0;
  switch (sel_imm) {
    case IMM_I: imm32 = static_cast<int32_t>(inst) >> 20; break;
    case IMM_S:
      imm32 = (static_cast<int32_t>(inst & 0xFE000000) >> 20) | ((inst >> 7) & 0x1F);
      break;
    case IMM_SB: {
      const uint32_t b12 = (inst >> 31) & 1, b11 = (inst >> 7) & 1;
      const uint32_t b105 = (inst >> 25) & 0x3F, b41 = (inst >> 8) & 0xF;
      imm32 = static_cast<int32_t>((b12 << 12) | (b11 << 11) | (b105 << 5) | (b41 << 1));
      if (b12) imm32 |= static_cast<int32_t>(0xFFFFE000);
      break;
    }
    case IMM_U: imm32 = static_cast<int32_t>(inst & 0xFFFFF000); break;
    case IMM_UJ: {
      const uint32_t b20 = (inst >> 31) & 1, b1912 = (inst >> 12) & 0xFF;
      const uint32_t b11 = (inst >> 20) & 1, b101 = (inst >> 21) & 0x3FF;
      imm32 = static_cast<int32_t>((b20 << 20) | (b1912 << 12) | (b11 << 11) | (b101 << 1));
      if (b20) imm32 |= static_cast<int32_t>(0xFFE00000);
      break;
    }
    case IMM_Z: imm32 = static_cast<int32_t>((inst >> 15) & 0x1F); break;
    default: imm32 = 0; break;
  }
  return static_cast<uint64_t>(static_cast<int64_t>(imm32));
}



FpuCtrl fpu_decode_from_inputs(const RocketSystemFpuInputs& input) {
  FpuCtrl c{};
  c.ldst = input.dec_ldst;
  c.wen = input.dec_wen;
  c.ren1 = input.dec_ren1;
  c.ren2 = input.dec_ren2;
  c.ren3 = input.dec_ren3;
  c.swap12 = input.dec_swap12;
  c.swap23 = input.dec_swap23;
  c.typeTagIn = input.dec_type_tag_in;
  c.typeTagOut = input.dec_type_tag_out;
  c.fromint = input.dec_fromint;
  c.toint = input.dec_toint;
  c.fastpipe = input.dec_fastpipe;
  c.fma = input.dec_fma;
  c.div = input.dec_div;
  c.sqrt = input.dec_sqrt;
  c.wflags = input.dec_wflags;
  return c;
}

// ------------------------------------------------------------------ CSR ----

uint64_t Core::csr_read(uint32_t addr, const RocketFullSystemInputs& in) const {
  const Csr& csr = csr_;
  const auto status_value = [&]() -> uint64_t {
    uint64_t v = 0;
    v |= (csr.mstatus_sie & 1) << 1;
    v |= (csr.mstatus_mie & 1) << 3;
    v |= (csr.mstatus_spie & 1) << 5;
    v |= (csr.mstatus_mpie & 1) << 7;
    v |= (csr.mstatus_spp & 1) << 8;
    v |= (csr.mstatus_mpp & 3) << 11;
    v |= (csr.mstatus_fs & 3) << 13;
    v |= (csr.mstatus_mprv & 1) << 17;
    v |= (csr.mstatus_sum & 1) << 18;
    v |= (csr.mstatus_mxr & 1) << 19;
    v |= (csr.mstatus_tvm & 1) << 20;
    v |= (csr.mstatus_tw & 1) << 21;
    v |= (csr.mstatus_tsr & 1) << 22;
    v |= UINT64_C(2) << 32;
    v |= UINT64_C(2) << 34;
    if ((csr.mstatus_fs & 3) == 3) v |= UINT64_C(1) << 63;
    return v;
  };
  const auto mip_value = [&]() -> uint64_t {
    uint64_t value = ((csr.mip_ssip & 1) << 1) | ((csr.mip_stip & 1) << 5) |
                     ((csr.mip_seip & 1) << 9);
    value |= (in.interrupt_msip ? UINT64_C(1) << 3 : 0) |
             (in.interrupt_mtip ? UINT64_C(1) << 7 : 0) |
             (in.interrupt_seip ? UINT64_C(1) << 9 : 0) |
             (in.interrupt_meip ? UINT64_C(1) << 11 : 0);
    return value & UINT64_C(0xaaa);
  };
  const bool have_f = (csr.misa & (UINT64_C(1) << ('F' - 'A'))) != 0;
  switch (addr) {
    case 0x100: return status_value() & UINT64_C(0x80000003000de762);
    case 0x300: return status_value();
    case 0x001: if (have_f) return csr.fflags; break;
    case 0x002: if (have_f) return csr.frm; break;
    case 0x003: if (have_f) return (csr.frm << 5) | csr.fflags; break;
    case 0x301: return csr.misa;
    case 0x302: return read_medeleg(csr);
    case 0x303: return read_mideleg(csr);
    case 0x304: return csr.mie;
    case 0x305: return form_tvec(csr.mtvec & UINT64_C(0xffffffff));
    case 0x306: return csr.mcounteren & kCounterenMask;
    case 0x320: return csr.mcountinhibit & 0x7;
    case 0x340: return csr.mscratch;
    case 0x341: return read_epc(csr.mepc, csr.misa);
    case 0x342: return csr.mcause;
    case 0x343: return sign_extend(csr.mtval, 40);
    case 0x344: return mip_value();
    case 0x104: return csr.mie & read_mideleg(csr);
    case 0x105: return sign_extend(form_tvec(csr.stvec & UINT64_C(0x7fffffffff)), 39);
    case 0x106: return csr.scounteren & kCounterenMask;
    case 0x140: return csr.sscratch;
    case 0x141: return read_epc(csr.sepc, csr.misa);
    case 0x142: return csr.scause;
    case 0x143: return sign_extend(csr.stval, 40);
    case 0x144: return mip_value() & read_mideleg(csr);
    case 0x180: return ((csr.satp_mode & 0xf) << 60) | ((csr.satp_asid & 0xffff) << 44) |
                       (csr.satp_ppn & UINT64_C(0xfffffffffff));
    case 0xB00: case 0xC00:
      return (csr.value_hi_1 << kWideSmallBits) | (csr.mcycle_small & kWideSmallMask);
    case 0xB02: case 0xC02:
      return (csr.value_hi << kWideSmallBits) | (csr.value_lo & kWideSmallMask);
    case 0x7B0: {
      uint64_t v = 4ULL << 28;
      v |= (csr.dcsr_ebreakm & 1) << 15;
      v |= (csr.dcsr_ebreaks & 1) << 13;
      v |= (csr.dcsr_ebreaku & 1) << 12;
      v |= (csr.dcsr_cause & 0x7) << 6;
      v |= (csr.dcsr_step & 1) << 2;
      v |= csr.dcsr_prv & 0x3;
      return v;
    }
    case 0x7B1: return read_epc(csr.dpc, csr.misa);
    case 0x7B2: return csr.dscratch;
    case 0x7A1: {
      uint64_t v = 2ULL << (64 - 4);
      v |= (csr.bp_0_control_dmode & 1) << 59;
      v |= UINT64_C(4) << 53;
      v |= (csr.bp_0_control_action & 1) << 12;
      v |= (csr.bp_0_control_tmatch & 0x3) << 7;
      v |= (csr.bp_0_control_m & 1) << 6;
      v |= (csr.bp_0_control_s & 1) << 4;
      v |= (csr.bp_0_control_u & 1) << 3;
      v |= (csr.bp_0_control_x & 1) << 2;
      v |= (csr.bp_0_control_w & 1) << 1;
      v |= (csr.bp_0_control_r & 1);
      return v;
    }
    case 0x7A2: return sign_extend(csr.bp_0_address, 39);
    case 0x7A3: return 0;
    case 0x7C1: return csr.custom_0;
    case 0xF11: return csr.custom_2;
    case 0xF12: return csr.custom_1;
    case 0xF13: return csr.custom_3;
    case 0xF14: return in.hartid;
    case 0x3A0: case 0x3A2: {
      const int base = (addr == 0x3A0) ? 0 : 8;
      uint64_t val = 0;
      for (int i = 0; i < 8 && base + i < 8; i++) {
        uint8_t cfg = 0;
        cfg |= (csr.pmp[base + i].cfg_l & 1) << 7;
        cfg |= (csr.pmp[base + i].cfg_a & 3) << 3;
        cfg |= (csr.pmp[base + i].cfg_x & 1) << 2;
        cfg |= (csr.pmp[base + i].cfg_w & 1) << 1;
        cfg |= (csr.pmp[base + i].cfg_r & 1);
        val |= static_cast<uint64_t>(cfg) << (i * 8);
      }
      return val;
    }
    case 0x3B0: case 0x3B1: case 0x3B2: case 0x3B3:
    case 0x3B4: case 0x3B5: case 0x3B6: case 0x3B7:
      return csr.pmp[addr - 0x3B0].addr;
    case 0x3B8: case 0x3B9: case 0x3BA: case 0x3BB:
    case 0x3BC: case 0x3BD: case 0x3BE: case 0x3BF:
      return 0;
    default: return 0;
  }
  return 0;
}

bool Core::csr_exists(uint32_t addr) const {
  switch (addr & 0xfff) {
    case 0x001: case 0x002: case 0x003:
    case 0x100: case 0x104: case 0x105: case 0x106:
    case 0x140: case 0x141: case 0x142: case 0x143: case 0x144:
    case 0x180:
    case 0x300: case 0x301: case 0x302: case 0x303: case 0x304:
    case 0x305: case 0x306: case 0x320:
    case 0x340: case 0x341: case 0x342: case 0x343: case 0x344:
    case 0x3a0: case 0x3a2:
    case 0x3b0: case 0x3b1: case 0x3b2: case 0x3b3:
    case 0x3b4: case 0x3b5: case 0x3b6: case 0x3b7:
    case 0x3b8: case 0x3b9: case 0x3ba: case 0x3bb:
    case 0x3bc: case 0x3bd: case 0x3be: case 0x3bf:
    case 0x7a0: case 0x7a1: case 0x7a2: case 0x7a3:
    case 0x7b0: case 0x7b1: case 0x7b2:
    case 0x7c1:
    case 0xb00: case 0xb02: case 0xc00: case 0xc02:
    case 0xf11: case 0xf12: case 0xf13: case 0xf14:
      return true;
    default:
      return (addr >= 0x323 && addr <= 0x33f) || (addr >= 0xb03 && addr <= 0xb1f) ||
             (addr >= 0xc03 && addr <= 0xc1f);
  }
}

bool Core::csr_read_illegal(uint32_t addr) const {
  const Csr& csr = csr_;
  addr &= 0xfff;
  if ((csr.mstatus_prv & 3) < ((addr >> 8) & 3)) return true;
  if (!csr_exists(addr)) return true;
  if (addr >= 0x7b0 && addr <= 0x7bf && !csr.debug) return true;
  if (addr == 0x180 && (csr.mstatus_prv & 3) <= 1 && csr.mstatus_tvm) return true;
  if (addr >= 0x001 && addr <= 0x003 &&
      ((csr.mstatus_fs & 3) == 0 || !(csr.misa & (UINT64_C(1) << 5))))
    return true;
  if (addr >= 0xc00 && addr <= 0xc1f) {
    const unsigned counter = addr & 0x1f;
    if ((csr.mstatus_prv & 3) <= 1 &&
        (((csr.mcounteren & kCounterenMask) >> counter) & 1) == 0)
      return true;
    if ((csr.mstatus_prv & 3) == 0 &&
        (((csr.scounteren & kCounterenMask) >> counter) & 1) == 0)
      return true;
  }
  return false;
}

bool Core::csr_write_illegal(uint32_t addr) const {
  return csr_read_illegal(addr) || (((addr >> 10) & 3) == 3);
}

bool Core::csr_system_illegal(uint32_t encoded_system) const {
  const Csr& csr = csr_;
  const uint32_t addr = encoded_system & 0xfff;
  if ((csr.mstatus_prv & 3) < ((addr >> 8) & 3)) return true;
  const bool sret = addr == 0x102, mret = addr == 0x302, dret = addr == 0x7b2;
  const bool wfi_insn = addr == 0x105;
  const bool sfence = (addr & 0xfe0) == 0x120;
  const bool known = addr == 0x000 || addr == 0x001 || sret || mret || dret ||
                     wfi_insn || sfence || addr == 0x305;
  if (!known) return true;
  if (wfi_insn && (csr.mstatus_prv & 3) <= 1 && csr.mstatus_tw) return true;
  if (sret && (csr.mstatus_prv & 3) <= 1 && csr.mstatus_tsr) return true;
  if (dret && !csr.debug) return true;
  if (sfence && (csr.mstatus_prv & 3) <= 1 && csr.mstatus_tvm) return true;
  return false;
}

uint64_t Core::trap_vector(uint64_t cause) const {
  const Csr& csr = csr_;
  const bool interrupt = (cause >> 63) != 0;
  const uint64_t code = cause & UINT64_C(0x3f);
  const bool delegate = (csr.mstatus_prv & 3) <= 1 &&
      (((interrupt ? read_mideleg(csr) : read_medeleg(csr)) >> code) & 1);
  const uint64_t raw = delegate
      ? sign_extend(csr.stvec & UINT64_C(0x7fffffffff), 39)
      : (csr.mtvec & UINT64_C(0xffffffff));
  const uint64_t formed = form_tvec(raw);
  const uint64_t vector = (interrupt && (formed & 1) && code < 64)
      ? ((formed & ~UINT64_C(0xff)) | (code << 2))
      : (formed & ~UINT64_C(3));
  return vector & kVaddrExtMask;
}

uint64_t Core::rmw_wdata(uint32_t address, uint8_t command, uint64_t wdata,
                         const RocketFullSystemInputs& in) const {
  // Write/no-op commands do not consume the old CSR value. In particular,
  // custom CSR payload outputs call this even on non-CSR/invalid WB cycles.
  if (command != CSR_S && command != CSR_C) return wdata;
  uint64_t old_value = csr_read(address, in);
  if (address == 0x344)
    old_value = ((csr_.mip_ssip & 1) << 1) | ((csr_.mip_stip & 1) << 5) |
                ((csr_.mip_seip & 1) << 9);
  if (command == CSR_S) return old_value | wdata;
  if (command == CSR_C) return old_value & ~wdata;
  return wdata;
}

void Core::update_csr(const Stage& s, uint64_t wdata) {
  Csr& csr = csr_;
  if (s.ctrl.csr == CSR_N || s.ctrl.csr == CSR_I) return;
  if (!s.valid) return;
  const uint32_t csr_addr = (s.inst >> 20) & 0xFFF;
  const bool have_f = (csr.misa & (UINT64_C(1) << ('F' - 'A'))) != 0;
  switch (csr_addr) {
    case 0x100:
      csr.mstatus_sie = (wdata >> 1) & 1;
      csr.mstatus_spie = (wdata >> 5) & 1;
      csr.mstatus_spp = (wdata >> 8) & 1;
      if (have_f) csr.mstatus_fs = ((wdata >> 13) & 0x3) ? 3 : 0;
      csr.mstatus_sum = (wdata >> 18) & 1;
      csr.mstatus_mxr = (wdata >> 19) & 1;
      break;
    case 0x300:
      csr.mstatus_sie = (wdata >> 1) & 1;
      csr.mstatus_spp = (wdata >> 8) & 1;
      csr.mstatus_spie = (wdata >> 5) & 1;
      csr.mstatus_mpie = (wdata >> 7) & 1;
      csr.mstatus_mie = (wdata >> 3) & 1;
      csr.mstatus_mpp = ((wdata >> 11) & 0x3) == 2 ? 0 : ((wdata >> 11) & 0x3);
      csr.mstatus_mprv = (wdata >> 17) & 1;
      csr.mstatus_sum = (wdata >> 18) & 1;
      csr.mstatus_mxr = (wdata >> 19) & 1;
      csr.mstatus_tvm = (wdata >> 20) & 1;
      csr.mstatus_tw = (wdata >> 21) & 1;
      csr.mstatus_tsr = (wdata >> 22) & 1;
      if (have_f) csr.mstatus_fs = ((wdata >> 13) & 0x3) ? 3 : 0;
      break;
    case 0x001: csr.fflags = wdata & 0x1F; csr.mstatus_fs = 3; break;
    case 0x002: csr.frm = wdata & 0x7; csr.mstatus_fs = 3; break;
    case 0x003:
      csr.fflags = wdata & 0x1F; csr.frm = (wdata >> 5) & 0x7; csr.mstatus_fs = 3;
      break;
    case 0x301: {
      constexpr uint64_t variable = UINT64_C(0x102d);
      if (((s.pc >> 1) & 1) == 0 || ((wdata >> 2) & 1)) {
        uint64_t next = (csr.misa & ~variable) | (wdata & variable);
        if (((next >> 5) & 1) == 0) next &= ~(UINT64_C(1) << 3);
        csr.misa = next;
      }
      break;
    }
    case 0x302: csr.medeleg = wdata; break;
    case 0x303: csr.mideleg = wdata; break;
    case 0x304: csr.mie = wdata & UINT64_C(0xaaa); break;
    case 0x305: csr.mtvec = wdata & UINT64_C(0xffffffff); break;
    case 0x306: csr.mcounteren = wdata & UINT64_C(0xffffffff); break;
    case 0x320: csr.mcountinhibit = wdata & 0x5; break;
    case 0x340: csr.mscratch = wdata; break;
    case 0x341: csr.mepc = wdata & UINT64_C(0xfffffffffe); break;
    case 0x342: csr.mcause = wdata & UINT64_C(0x800000000000000f); break;
    case 0x343: csr.mtval = wdata & UINT64_C(0xffffffffff); break;
    case 0x344:
      csr.mip_ssip = (wdata >> 1) & 1;
      csr.mip_stip = (wdata >> 5) & 1;
      csr.mip_seip = (wdata >> 9) & 1;
      break;
    case 0x104:
      csr.mie = (csr.mie & ~read_mideleg(csr)) | (wdata & read_mideleg(csr) & UINT64_C(0xaaa));
      break;
    case 0x105: csr.stvec = wdata & UINT64_C(0x7fffffffff); break;
    case 0x106: csr.scounteren = wdata & UINT64_C(0xffffffff); break;
    case 0x140: csr.sscratch = wdata; break;
    case 0x141: csr.sepc = wdata & UINT64_C(0xfffffffffe); break;
    case 0x142: csr.scause = wdata & UINT64_C(0x800000000000001f); break;
    case 0x143: csr.stval = wdata & UINT64_C(0xffffffffff); break;
    case 0x144:
      if (read_mideleg(csr) & (UINT64_C(1) << 1)) csr.mip_ssip = (wdata >> 1) & 1;
      break;
    case 0x180: {
      const uint64_t mode = (wdata >> 60) & 0xf;
      if (mode == 0 || mode == 8) {
        csr.satp_mode = mode;
        csr.satp_asid = 0;
        csr.satp_ppn = wdata & UINT64_C(0xfffff);
      }
      break;
    }
    case 0xB00:
      csr.mcycle_small = wdata & kWideSmallMask;
      csr.value_hi_1 = wdata >> kWideSmallBits;
      break;
    case 0xB02:
      csr.value_lo = wdata & kWideSmallMask;
      csr.value_hi = wdata >> kWideSmallBits;
      break;
    case 0x7B0:
      csr.dcsr_ebreakm = (wdata >> 15) & 1;
      csr.dcsr_ebreaks = (wdata >> 13) & 1;
      csr.dcsr_ebreaku = (wdata >> 12) & 1;
      csr.dcsr_step = (wdata >> 2) & 1;
      csr.dcsr_prv = ((wdata & 0x3) == 2) ? 0 : (wdata & 0x3);
      break;
    case 0x7B1: csr.dpc = wdata & UINT64_C(0xfffffffffe); break;
    case 0x7B2: csr.dscratch = wdata; break;
    case 0x7A1: {
      if (csr.bp_0_control_dmode && !csr.debug) break;
      const bool dmode = ((wdata >> 59) & 1) && csr.debug;
      csr.bp_0_control_dmode = dmode;
      csr.bp_0_control_action = dmode ? ((wdata >> 12) & 1) : 0;
      csr.bp_0_control_tmatch = (wdata >> 7) & 0x3;
      csr.bp_0_control_m = (wdata >> 6) & 1;
      csr.bp_0_control_s = (wdata >> 4) & 1;
      csr.bp_0_control_u = (wdata >> 3) & 1;
      csr.bp_0_control_x = (wdata >> 2) & 1;
      csr.bp_0_control_w = (wdata >> 1) & 1;
      csr.bp_0_control_r = wdata & 1;
      break;
    }
    case 0x7A2:
      if (!csr.bp_0_control_dmode || csr.debug) csr.bp_0_address = wdata & UINT64_C(0x7fffffffff);
      break;
    case 0x7C1:
      csr.custom_0 = (csr.custom_0 & ~UINT64_C(0x208)) | (wdata & UINT64_C(0x208));
      break;
    default:
      if (csr_addr == 0x3A0 || csr_addr == 0x3A2) {
        const int base = (csr_addr == 0x3A0) ? 0 : 8;
        for (int i = 0; i < 8 && base + i < 8; i++) {
          const uint8_t cfg = (wdata >> (i * 8)) & 0xFF;
          auto& entry = csr.pmp[base + i];
          if (entry.cfg_l) continue;
          const bool read = (cfg & 1) != 0;
          if (entry.cfg_l != ((cfg >> 7) & 1) || entry.cfg_a != ((cfg >> 3) & 3) ||
              entry.cfg_x != ((cfg >> 2) & 1) || entry.cfg_w != (((cfg >> 1) & 1) && read) ||
              entry.cfg_r != read) invalidate_pmp_views();
          entry.cfg_l = (cfg >> 7) & 1;
          entry.cfg_a = (cfg >> 3) & 3;
          entry.cfg_x = (cfg >> 2) & 1;
          entry.cfg_w = ((cfg >> 1) & 1) && read;
          entry.cfg_r = read;
        }
      } else if (csr_addr >= 0x3B0 && csr_addr <= 0x3B7) {
        const unsigned index = csr_addr - 0x3B0;
        const bool self_locked = csr.pmp[index].cfg_l;
        const bool tor_locked_by_next = index + 1 < 8 && csr.pmp[index + 1].cfg_l &&
                                        csr.pmp[index + 1].cfg_a == 1;
        if (!self_locked && !tor_locked_by_next) {
          if (csr.pmp[index].addr != (wdata & UINT64_C(0x3fffffff))) invalidate_pmp_views();
          csr.pmp[index].addr = wdata & UINT64_C(0x3fffffff);
        }
      }
      break;
  }
}

void Core::handle_trap(uint64_t pc, uint32_t inst, uint8_t csr_cmd, uint64_t cause,
                       uint64_t tval_source) {
  Csr& csr = csr_;
  const bool interrupt = (cause >> 63) != 0;
  const uint64_t code = cause & UINT64_C(0x3f);
  const uint32_t system_addr = (inst >> 20) & 0xfff;
  const bool ebreak = csr_cmd == CSR_I && system_addr == 0x001;
  const bool debug_break = ebreak &&
      (((csr.mstatus_prv == 3) && csr.dcsr_ebreakm) ||
       ((csr.mstatus_prv == 1) && csr.dcsr_ebreaks) ||
       ((csr.mstatus_prv == 0) && csr.dcsr_ebreaku));
  const bool trap_to_debug = csr.debug || csr.singleStepped || code == 14 || debug_break;
  const uint64_t epc = pc & UINT64_C(0xfffffffffe);
  if (trap_to_debug) {
    if (!csr.debug) {
      csr.debug = 1;
      csr.dpc = epc;
      csr.dcsr_cause = csr.singleStepped ? 4 : (interrupt && code == 14) ? 3
                       : (!interrupt && code == 14) ? 2 : 1;
      csr.dcsr_prv = csr.mstatus_prv & 3;
      csr.mstatus_prv = 3;
    }
    return;
  }
  const bool delegate = (csr.mstatus_prv & 3) <= 1 &&
      ((((interrupt ? read_mideleg(csr) : read_medeleg(csr)) >> code) & 1) != 0);
  const bool tval_valid = !interrupt &&
      (code == 2 || code == 3 || code == 4 || code == 6 || code == 1 || code == 5 ||
       code == 7 || code == 12 || code == 13 || code == 15);
  const uint64_t tval = tval_valid ? encode_virtual_address(tval_source, tval_source) : 0;
  if (delegate) {
    csr.sepc = epc;
    csr.scause = cause;
    csr.stval = tval;
    csr.mstatus_spie = csr.mstatus_sie;
    csr.mstatus_spp = csr.mstatus_prv & 1;
    csr.mstatus_sie = 0;
    csr.mstatus_prv = 1;
  } else {
    csr.mepc = epc;
    csr.mcause = cause;
    csr.mtval = tval;
    csr.mstatus_mpie = csr.mstatus_mie;
    csr.mstatus_mpp = csr.mstatus_prv & 3;
    csr.mstatus_mie = 0;
    csr.mstatus_prv = 3;
  }
}

BreakpointView Core::breakpoint_view(uint64_t pc, uint64_t ea) const {
  const Csr& csr = csr_;
  BreakpointView v{};
  const unsigned prv = csr.mstatus_prv & 3;
  const bool privilege_enabled =
      (prv == 3 && csr.bp_0_control_m) || (prv == 1 && csr.bp_0_control_s) ||
      (prv == 0 && csr.bp_0_control_u);
  const bool enabled = !csr.debug && privilege_enabled;
  if (!enabled) return v;
  const bool pc_match = breakpoint_address_match(csr, pc);
  const bool ea_match = breakpoint_address_match(csr, ea);
  const bool action_debug = (csr.bp_0_control_action & 1) != 0;
  const bool x = pc_match && csr.bp_0_control_x;
  const bool r = ea_match && csr.bp_0_control_r;
  const bool w = ea_match && csr.bp_0_control_w;
  v.instruction = x && !action_debug;
  v.load = r && !action_debug;
  v.store = w && !action_debug;
  v.debug_instruction = x && action_debug;
  v.debug_load = r && action_debug;
  v.debug_store = w && action_debug;
  return v;
}

const DecodedCtrl& Core::decode_cached(uint32_t inst) const {
  const unsigned index = (inst * 0x9E3779B1u) >> (32 - 8);
  DecodeEntry& e = decode_cache_[index];
  if (!e.valid || e.inst != inst) {
    e.inst = inst;
    e.ctrl = decode(inst);
    e.valid = true;
  }
  return e.ctrl;
}

uint32_t Core::expand_cached(uint16_t half) const {
  if (!rvc_cache_valid_ || rvc_cache_half_ != half) {
    bool compressed = false;
    rvc_cache_inst_ = rvc_expand(half, &compressed);
    rvc_cache_half_ = half;
    rvc_cache_valid_ = true;
  }
  return rvc_cache_inst_;
}

// ------------------------------------------------------------- stalls ----

bool Core::stall_check(const CoreWires& w, const DecodedCtrl& id_ctrl,
                       const RocketFullSystemInputs& in) const {
  const uint32_t id_inst = w.id_inst;
  const uint32_t id_raddr1 = rs1_addr(id_inst);
  const uint32_t id_raddr2 = rs2_addr(id_inst);
  const uint32_t id_waddr = rd_addr(id_inst);
  const uint32_t id_raddr3 = (id_inst >> 27) & 0x1F;
  const bool rs1_nz = id_ctrl.rxs1 && id_raddr1 != 0;
  const bool rs2_nz = id_ctrl.rxs2 && id_raddr2 != 0;
  const bool wd_nz = id_ctrl.wxd && id_waddr != 0;
  const FpuCtrl& fpu_dec = w.id_fpu_dec;
  const auto fp_hazard_match = [&](uint32_t waddr) -> bool {
    return (fpu_dec.ren1 && id_raddr1 == waddr) || (fpu_dec.ren2 && id_raddr2 == waddr) ||
           (fpu_dec.ren3 && id_raddr3 == waddr) || (fpu_dec.wen && id_waddr == waddr);
  };
  const Stage& ex = ex_;
  const Stage& mem = mem_;
  const Stage& wb = wb_;

  if (ex.valid) {
    const uint32_t ex_wa = rd_addr(ex.inst);
    const bool ex_cannot_bypass = (ex.ctrl.csr != CSR_N) || ex.ctrl.jalr || ex.ctrl.mem ||
                                  ex.ctrl.mul || ex.ctrl.div || ex.ctrl.fp || ex.ctrl.rocc ||
                                  ex.ctrl.scie;
    const bool data_hazard_ex = ex.ctrl.wxd &&
        ((rs1_nz && id_raddr1 == ex_wa) || (rs2_nz && id_raddr2 == ex_wa) ||
         (wd_nz && id_waddr == ex_wa));
    const bool fp_data_hazard_ex = ex.ctrl.wfd && fp_hazard_match(ex_wa);
    if ((data_hazard_ex && ex_cannot_bypass) || fp_data_hazard_ex) return true;
  }
  if (mem.valid) {
    const uint32_t mem_wa = rd_addr(mem.inst);
    const bool mem_cannot_bypass = (mem.ctrl.csr != CSR_N) || (mem.ctrl.mem && mem.slow_bypass) ||
                                   mem.ctrl.mul || mem.ctrl.div || mem.ctrl.fp || mem.ctrl.rocc;
    const bool data_hazard_mem = mem.ctrl.wxd &&
        ((rs1_nz && id_raddr1 == mem_wa) || (rs2_nz && id_raddr2 == mem_wa) ||
         (wd_nz && id_waddr == mem_wa));
    const bool fp_data_hazard_mem = mem.ctrl.wfd && fp_hazard_match(mem_wa);
    if ((data_hazard_mem && mem_cannot_bypass) || fp_data_hazard_mem) return true;
  }
  if (wb.valid) {
    const uint32_t wb_wa = rd_addr(wb.inst);
    const bool wb_dcache_miss = wb.ctrl.mem && !in.dmem.resp.valid;
    const bool wb_set_sboard_now = wb.ctrl.div || wb_dcache_miss || wb.ctrl.rocc;
    const bool data_hazard_wb = wb.ctrl.wxd &&
        ((rs1_nz && id_raddr1 == wb_wa) || (rs2_nz && id_raddr2 == wb_wa) ||
         (wd_nz && id_waddr == wb_wa));
    const bool fp_data_hazard_wb = wb.ctrl.wfd && fp_hazard_match(wb_wa);
    if ((data_hazard_wb && wb_set_sboard_now) || fp_data_hazard_wb) return true;
  }
  {
    const auto sboard_hit = [&](uint32_t addr) -> bool {
      const bool set = (sboard_ >> addr) & 1;
      const bool bypass_div = w.ll_wen_div_bypass && (w.ll_waddr_div_bypass == addr);
      const bool bypass_dmem = w.ll_wen_dmem_bypass && (w.ll_waddr_dmem_bypass == addr);
      return set && !bypass_div && !bypass_dmem;
    };
    if ((rs1_nz && sboard_hit(id_raddr1)) || (rs2_nz && sboard_hit(id_raddr2)) ||
        (wd_nz && sboard_hit(id_waddr)))
      return true;
  }
  {
    const bool id_csr_en = (id_ctrl.csr == CSR_W || id_ctrl.csr == CSR_S || id_ctrl.csr == CSR_C);
    const uint32_t csr_addr = (id_inst >> 20) & 0xFFF;
    const bool is_fp_csr = (csr_addr >= 0x001 && csr_addr <= 0x003);
    if (id_csr_en && is_fp_csr && !in.fpu.fcsr_ready) return true;
  }
  if (id_ctrl.fp) {
    const auto fp_sboard_hit = [&](uint32_t addr) -> bool { return (fp_sboard_ >> (addr & 31u)) & 1; };
    const bool fp_sb = (fpu_dec.ren1 && fp_sboard_hit(id_raddr1)) ||
                       (fpu_dec.ren2 && fp_sboard_hit(id_raddr2)) ||
                       (fpu_dec.ren3 && fp_sboard_hit(id_raddr3)) ||
                       (fpu_dec.wen && fp_sboard_hit(id_waddr));
    if (fp_sb) return true;
  }
  if (id_ctrl.div) {
    const bool req_ready = (div_.state == DIV_S_READY);
    const bool resp_valid = (div_.state == DIV_S_DONE_MUL || div_.state == DIV_S_DONE_DIV);
    const bool wbwxd = wb.valid && wb.ctrl.wxd;
    const bool can_accept = req_ready || (resp_valid && !wbwxd);
    const bool req_valid = ex.valid && ex.ctrl.div;
    if (!can_accept || req_valid) return true;
  }
  if (id_ctrl.mem && blocked_ && !in.dmem.perf_grant) return true;
  {
    const bool dmem_req_valid = ex.valid && (ex.ctrl.mem != 0);
    const bool id_mem_busy = !in.dmem.ordered || dmem_req_valid;
    const bool id_amo_rl = id_ctrl.amo && ((id_inst >> 25) & 1u);
    const bool id_do_fence = id_mem_busy &&
        (id_amo_rl || id_ctrl.fence_i || (id_reg_fence_ && (id_ctrl.mem || id_ctrl.rocc)));
    if (id_do_fence) return true;
  }
  if (id_reg_pause_) return true;
  {
    const bool pipeline_live = ex.valid || mem.valid || wb.valid;
    if (csr_.dcsr_step && !csr_.debug && pipeline_live) return true;
    if (csr_.wfi || csr_.status_cease_r) return true;
    if (in.trace_stall) return true;
  }
  return false;
}

// ------------------------------------------------------------ evaluate ----

const Core::PreDerived& Core::pre_derived() const {
  if (!pre_derived_valid_) {
    PreDerived& p = pre_derived_;
    // A WB flush resumes at the MEM next PC even when MEM itself is a
    // bubble. Keep that live redirect dependency while dropping dead data.
    const bool mem_live = mem_.valid || mem_.replay || mem_.xcpt_interrupt || wb_.flush_pipe;
    p.mem_target = (!architectural_mode_ || mem_live) ? mem_branch_target(mem_) : 0;
    p.mem_npc = (!architectural_mode_ || mem_live) ? mem_npc_of(mem_, p.mem_target) : 0;
    p.mem_npc_misaligned = ((csr_.misa & (UINT64_C(1) << 2)) == 0) &&
                           ((p.mem_npc >> 1) & 1) && !mem_.sfence;
    const bool ex_live = ex_.valid || ex_.replay || ex_.xcpt_interrupt;
    if (architectural_mode_ && !ex_live) {
      p.ex_cold_rs[0] = p.ex_cold_rs[1] = p.ex_cold_alu = p.ex_br_taken = false;
      p.ex_rs[0] = p.ex_rs[1] = p.ex_wdata = p.ex_adder = p.ex_store_data = 0;
    } else {
      for (unsigned port = 0; port < 2; ++port) {
        p.ex_cold_rs[port] = ex_.rs_bypass[port] && (ex_.rs_lsb[port] & 3) == 3;
        p.ex_rs[port] = rs_val(port, ex_, mem_, wb_, 0);
      }
      p.ex_cold_alu = (ex_.ctrl.sel_alu1 == A1_RS1 && p.ex_cold_rs[0]) ||
                      (ex_.ctrl.sel_alu2 == A2_RS2 && p.ex_cold_rs[1]);
      // Only state-derived operands are memoized; live cold bypasses remain
      // part of every fixed-point evaluation.
      if (!p.ex_cold_alu)
        ex_alu(ex_, p.ex_rs[0], p.ex_rs[1], p.ex_wdata, p.ex_br_taken, p.ex_adder);
      if (!p.ex_cold_rs[1]) p.ex_store_data = replicate_store_data(p.ex_rs[1], ex_.mem_size);
    }
    pre_derived_valid_ = true;
  }
  return pre_derived_;
}

void Core::evaluate(const RocketFullSystemInputs& in, CoreWires& w,
                    RocketFullSystemOutputs& out) const {
  const Stage& ex = ex_;
  const Stage& mem = mem_;
  const Stage& wb = wb_;
  const Csr& csr = csr_;
  const IBuf& ibuf = ibuf_;
  const RocketSystemImemInputs& imem = in.imem;
  const RocketSystemDmemInputs& dmem = in.dmem;
  const RocketSystemDmemResponse& resp = dmem.resp;
  const PreDerived& pre = pre_derived();

  // Shared IBuf packet geometry. ID visibility, expansion and the queue edge
  // consume this same input projection, including invalid packet payloads.
  const int fetch_pc_word = static_cast<int>((imem.resp_pc >> 1) & 1);
  const int fetch_words = imem.resp_btb.taken ? static_cast<int>(imem.resp_btb.bridx) + 1 : 2;
  const int fetch_nic = fetch_words > fetch_pc_word ? fetch_words - fetch_pc_word : 0;
  const int fetch_nvalid = static_cast<int>(ibuf.nBufValid) + (imem.resp_valid ? fetch_nic : 0);
  const bool fetch_buffered = ibuf.nBufValid != 0;
  const uint16_t fetch_first = fetch_buffered ? static_cast<uint16_t>(ibuf.buf_data)
      : static_cast<uint16_t>(imem.resp_data >> (fetch_pc_word * 16));
  const bool fetch_rvc = (fetch_first & 3u) != 3u;
  const bool fetch_buffered_replay = fetch_buffered && ibuf.buf_replay;

  w = CoreWires{};
  w.id_pc = ibuf.nBufValid ? ibuf.buf_pc : imem.resp_pc;
  w.dmem_resp_valid = resp.valid && resp.has_data;
  const bool dmem_resp_xpu = (resp.tag & 1u) == 0;
  const bool dmem_resp_replay = w.dmem_resp_valid && resp.replay;

  // ---- redirects from the MEM and WB slots (registered values) ----
  const bool mem_cfi = mem.ctrl.branch || mem.ctrl.jalr || mem.ctrl.jal;
  const bool mem_cfi_taken = (mem.ctrl.branch && mem.br_taken) || mem.ctrl.jalr || mem.ctrl.jal;
  w.mem_npc = pre.mem_npc;
  w.ex_pc_valid = ex.valid || ex.replay || ex.xcpt_interrupt;
  w.mem_pc_valid = mem.valid || mem.replay || mem.xcpt_interrupt;
  w.id_visible = fetch_nvalid >= 1 && (fetch_rvc || fetch_nvalid >= 2 || fetch_buffered_replay);
  {
    const uint64_t observed_next_pc = w.ex_pc_valid ? ex.pc : w.id_pc;
    const bool next_pc_present = w.ex_pc_valid || w.id_visible || imem.resp_valid;
    w.mem_wrong_npc = !next_pc_present || w.mem_npc != observed_next_pc;
  }
  w.take_pc_mem = mem.valid && (w.mem_wrong_npc || mem.sfence);

  // ---- WB view ----
  w.wb_xcpt = wb.xcpt;
  w.wb_cause = wb.xcpt ? wb.cause : 5;
  if (!w.wb_xcpt && wb.valid && wb.ctrl.mem) {
    if (dmem.s2_xcpt_ma_st)      { w.wb_xcpt = true; w.wb_cause = 6; }
    else if (dmem.s2_xcpt_ma_ld) { w.wb_xcpt = true; w.wb_cause = 4; }
    else if (dmem.s2_xcpt_pf_st) { w.wb_xcpt = true; w.wb_cause = 15; }
    else if (dmem.s2_xcpt_pf_ld) { w.wb_xcpt = true; w.wb_cause = 13; }
    else if (dmem.s2_xcpt_ae_st) { w.wb_xcpt = true; w.wb_cause = 7; }
    else if (dmem.s2_xcpt_ae_ld) { w.wb_xcpt = true; w.wb_cause = 5; }
  }
  w.wb_system = wb.valid && wb.ctrl.csr == CSR_I;
  const uint32_t wb_system_addr = (wb.inst >> 20) & 0xfff;
  w.wb_ecall = w.wb_system && wb_system_addr == 0x000;
  w.wb_ebreak = w.wb_system && wb_system_addr == 0x001;
  w.wb_sret = w.wb_system && wb_system_addr == 0x102;
  w.wb_mret = w.wb_system && wb_system_addr == 0x302;
  w.wb_dret = w.wb_system && wb_system_addr == 0x7b2;
  w.wb_wfi = w.wb_system && wb_system_addr == 0x105;
  w.wb_cease = w.wb_system && wb_system_addr == 0x305;
  w.wb_return = w.wb_sret || w.wb_mret || w.wb_dret;
  w.wb_csr_eret = w.wb_ecall || w.wb_ebreak || w.wb_return;
  if (w.wb_ecall) w.wb_cause = 8 + (csr.mstatus_prv & 3);
  if (w.wb_ebreak) w.wb_cause = 3;
  w.wb_csr_exception = w.wb_ecall || w.wb_ebreak;
  const bool replay_wb_common = dmem.s2_nack || wb.replay;
  const bool replay_wb_rocc = wb.valid && wb.ctrl.rocc && !in.rocc.cmd_ready;
  w.replay_wb = replay_wb_common || replay_wb_rocc;
  w.take_pc_wb = w.replay_wb || w.wb_xcpt || w.wb_csr_eret || wb.flush_pipe;
  w.take_pc_mem_wb = w.take_pc_mem || w.take_pc_wb;
  w.wb_valid_retire = wb.valid && !w.replay_wb && !w.wb_xcpt;
  if (w.wb_xcpt || w.wb_csr_exception) {
    const uint64_t code = w.wb_cause & UINT64_C(0x3f);
    const bool debug_break = w.wb_ebreak &&
        (((csr.mstatus_prv & 3) == 3 && csr.dcsr_ebreakm) ||
         ((csr.mstatus_prv & 3) == 1 && csr.dcsr_ebreaks) ||
         ((csr.mstatus_prv & 3) == 0 && csr.dcsr_ebreaku));
    const bool to_debug = csr.debug || csr.singleStepped || code == 14 || debug_break;
    w.wb_evec = to_debug ? ((csr.debug && !w.wb_ebreak) ? UINT64_C(0x808) : UINT64_C(0x800))
                         : trap_vector(w.wb_cause);
  } else if (w.wb_return) {
    const uint64_t target = w.wb_dret ? csr.dpc : w.wb_sret ? csr.sepc : csr.mepc;
    w.wb_evec = target & ((csr.misa & (UINT64_C(1) << 2)) ? ~UINT64_C(1) : ~UINT64_C(3));
  }

  // ---- long-latency writeback bypass for the scoreboard check ----
  {
    const bool div_resp_v = (div_.state == DIV_S_DONE_MUL || div_.state == DIV_S_DONE_DIV);
    const bool wb_wxd_v = wb.valid && wb.ctrl.wxd;
    w.ll_wen_div_bypass = div_resp_v && !wb_wxd_v && !(dmem_resp_replay && dmem_resp_xpu);
    w.ll_waddr_div_bypass = static_cast<uint32_t>(div_.req_tag);
    w.ll_wen_dmem_bypass = dmem_resp_replay && dmem_resp_xpu;
    w.ll_waddr_dmem_bypass = (resp.tag >> 1) & 0x1F;
  }

  // ---- EX operands ----
  w.ex_rs0 = pre.ex_cold_rs[0] ? resp.data_word_bypass : pre.ex_rs[0];
  w.ex_rs1 = pre.ex_cold_rs[1] ? resp.data_word_bypass : pre.ex_rs[1];

  // ---- WB <- MEM ----
  w.mem_npc_misaligned = pre.mem_npc_misaligned;
  w.id_bp = breakpoint_view(w.id_pc, mem.wdata);
  w.mem_breakpoint = (mem.load && w.id_bp.load) || (mem.store && w.id_bp.store);
  w.mem_debug_breakpoint = (mem.load && w.id_bp.debug_load) || (mem.store && w.id_bp.debug_store);
  w.mem_xcpt = mem.xcpt_interrupt || mem.xcpt;
  w.mem_cause = mem.cause;
  if (!w.mem_xcpt && mem.valid && w.mem_npc_misaligned) { w.mem_xcpt = true; w.mem_cause = 0; }
  else if (!w.mem_xcpt && mem.valid && w.mem_debug_breakpoint) { w.mem_xcpt = true; w.mem_cause = 14; }
  else if (!w.mem_xcpt && mem.valid && w.mem_breakpoint) { w.mem_xcpt = true; w.mem_cause = 3; }
  else if (!w.mem_xcpt) { w.mem_cause = 3; }
  w.dcache_kill_mem = mem.valid && mem.ctrl.wxd && dmem.replay_next;
  w.killm_common = w.dcache_kill_mem || w.take_pc_wb || mem.xcpt || !mem.valid;
  w.fpu_nack_mem = in.fpu.nack_mem;
  w.fpu_kill_mem = mem.valid && (mem.ctrl.fp != 0) && w.fpu_nack_mem;
  w.ctrl_killm = w.killm_common || w.mem_xcpt || w.fpu_kill_mem;
  {
    uint64_t wdata = mem.wdata;
    if (!mem.xcpt && ((mem.ctrl.jalr != 0) ^ w.mem_npc_misaligned))
      wdata = sign_extend(pre.mem_target, 40);
    if (!mem.xcpt && mem.ctrl.fp && mem.ctrl.wxd) wdata = in.fpu.toint_data;
    w.new_wb_wdata = wdata;
    w.new_wb_wphit = mem.wphit_0 ||
        ((mem.load && (w.mem_breakpoint || w.mem_debug_breakpoint)) ||
         (mem.store && (w.mem_breakpoint || w.mem_debug_breakpoint)));
  }
  w.new_wb_valid = !w.ctrl_killm;
  w.new_wb_xcpt = w.mem_xcpt && !w.take_pc_wb;
  w.new_wb_flush_pipe = !w.ctrl_killm && mem.flush_pipe;
  w.new_wb_replay = (w.dcache_kill_mem || mem.replay || w.fpu_kill_mem) && !w.take_pc_wb;

  // ---- MEM <- EX ----
  w.mem_flush_stall = mem.valid && mem.flush_pipe;
  w.wb_dcache_miss = wb.ctrl.mem && !resp.valid;
  const bool div_req_ready_now = div_.state == DIV_S_READY;
  {
    const bool replay_ex_structural = (ex.ctrl.mem && !dmem.req_ready) ||
                                      (ex.ctrl.div && !div_req_ready_now);
    const bool replay_ex_load_use = w.wb_dcache_miss && ex.load_use;
    w.replay_ex = ex.replay || (ex.valid && (replay_ex_structural || replay_ex_load_use));
  }
  w.ctrl_killx = w.take_pc_mem_wb || w.replay_ex || !ex.valid;
  {
    w.new_mem_debug_fence = ex.ctrl.jalr && csr.debug;
    if (pre.ex_cold_alu) {
      ex_alu(ex, w.ex_rs0, w.ex_rs1, w.new_mem_wdata, w.new_mem_br_taken, w.ex_adder);
    } else {
      w.new_mem_wdata = pre.ex_wdata;
      w.new_mem_br_taken = pre.ex_br_taken;
      w.ex_adder = pre.ex_adder;
    }
    w.new_mem_store = ex.ctrl.mem && is_store(ex.ctrl.mem_cmd);
    w.new_mem_load = ex.ctrl.mem && is_load(ex.ctrl.mem_cmd);
    w.new_mem_slow_bypass = (ex.ctrl.mem_cmd == M_XSC) || (ex.mem_size < 2);
    w.new_mem_rs2_valid = ex.ctrl.rxs2 && ex.ctrl.mem;
    w.new_mem_rs2 = pre.ex_cold_rs[1] ? replicate_store_data(w.ex_rs1, ex.mem_size) : pre.ex_store_data;
  }
  w.new_mem_valid = !w.ctrl_killx;
  w.new_mem_replay = !w.take_pc_mem_wb && w.replay_ex;
  w.new_mem_xcpt = !w.ctrl_killx && ex.xcpt;
  w.new_mem_xcpt_interrupt = !w.take_pc_mem_wb && ex.xcpt_interrupt;

  // ---- interrupt selection (CSR.scala chooseInterrupt) ----
  {
    const uint64_t mip = ((csr.mip_ssip & 1) << 1) |
                         ((in.interrupt_msip ? 1ULL : 0ULL) << 3) |
                         ((csr.mip_stip & 1) << 5) |
                         ((in.interrupt_mtip ? 1ULL : 0ULL) << 7) |
                         ((((csr.mip_seip & 1) || in.interrupt_seip) ? 1ULL : 0ULL) << 9) |
                         ((in.interrupt_meip ? 1ULL : 0ULL) << 11);
    const uint64_t pending = mip & csr.mie;
    const bool machine_enabled = csr.mstatus_prv <= 1 || csr.mstatus_mie;
    const bool supervisor_enabled = csr.mstatus_prv < 1 || (csr.mstatus_prv == 1 && csr.mstatus_sie);
    const uint64_t mideleg = read_mideleg(csr);
    const uint64_t machine_interrupts = machine_enabled ? pending & ~mideleg : 0;
    const uint64_t supervisor_interrupts = supervisor_enabled ? pending & mideleg : 0;
    static constexpr int kPriority[] = {11, 3, 7, 9, 1, 5};
    int selected = -1;
    if (in.interrupt_debug) {
      selected = 14;
    } else {
      for (int cause : kPriority) if ((machine_interrupts >> cause) & 1ULL) { selected = cause; break; }
      if (selected < 0)
        for (int cause : kPriority) if ((supervisor_interrupts >> cause) & 1ULL) { selected = cause; break; }
    }
    const bool single_step = csr.dcsr_step && !csr.debug;
    w.csr_interrupt = ((selected >= 0 && !single_step) || csr.singleStepped) &&
                      !csr.debug && !csr.status_cease_r;
    const int which_interrupt = selected >= 0 ? selected : 4;
    if (w.csr_interrupt)
      w.csr_interrupt_cause = (UINT64_C(1) << 63) | static_cast<uint64_t>(which_interrupt);
  }

  // ---- ID: fetch packet, decode, stall ----
  w.ctrl_killd = w.take_pc_mem_wb;
  {
    const int pc_word = fetch_pc_word;
    const int nvalid = fetch_nvalid;
    const bool buffered = fetch_buffered;
    const uint8_t valid_mask = nvalid <= 0 ? 0 : nvalid == 1 ? 1 : 3;
    const uint8_t buffer_mask = buffered ? 1 : 0;
    const uint32_t pkt = imem.resp_data;
    const uint16_t first = fetch_first;
    const uint16_t second = static_cast<uint16_t>(pkt >> ((buffered ? pc_word : 1) * 16));
    w.id_half = first;
    w.id_rvc = fetch_rvc;
    w.ibuf_inst_valid = w.id_visible;
    w.id_raw_inst = static_cast<uint32_t>(first) | (static_cast<uint32_t>(second) << 16);
    if (architectural_mode_ && !w.ibuf_inst_valid) {
      w.id_inst = 0;
    } else if (w.id_rvc) {
      w.id_inst = expand_cached(first);
    } else {
      w.id_inst = w.id_raw_inst;
    }
    w.id_xcpt0_pf = buffered ? ibuf.buf_xcpt_pf_inst : imem.resp_xcpt_pf_inst;
    w.id_xcpt0_ae = buffered ? ibuf.buf_xcpt_ae_inst : imem.resp_xcpt_ae_inst;
    w.id_xcpt1_pf = !w.id_rvc && imem.resp_xcpt_pf_inst;
    w.id_xcpt1_ae = !w.id_rvc && imem.resp_xcpt_ae_inst;
    const uint8_t buffer_replay = ibuf.buf_replay ? buffer_mask : 0;
    const uint8_t ic_replay = buffer_replay |
        ((imem.resp_valid && imem.resp_replay) ? static_cast<uint8_t>(valid_mask & ~buffer_mask) : 0);
    w.id_replay = (ic_replay & 1) || (!w.id_rvc && (ic_replay & 2));
    const RocketSystemBtbResponse& b = imem.resp_btb;
    w.id_btb.cfiType = b.cfi_type;
    w.id_btb.taken = b.taken;
    w.id_btb.mask = b.mask;
    w.id_btb.bridx = b.bridx;
    w.id_btb.target = b.target;
    w.id_btb.entry = b.entry;
    w.id_btb.bht_history = b.bht_history;
    w.id_btb.bht_value = b.bht_value;
    if (buffered && w.id_rvc) w.id_btb = ibuf.btb;
  }
  if (w.id_replay || w.csr_interrupt) w.ctrl_killd = true;
  if (!architectural_mode_ || w.ibuf_inst_valid) w.id_ctrl = decode_cached(w.id_inst);
  if (!architectural_mode_ || w.id_ctrl.fp) w.id_fpu_dec = fpu_decode_from_inputs(in.fpu);
  if (!w.ctrl_killd && !w.ibuf_inst_valid) w.ctrl_killd = true;
  const bool killed_before_id = w.ctrl_killd;
  if (killed_before_id) w.ctrl_stalld = stall_check(w, w.id_ctrl, in);

  const bool id_fpu_disabled = !(csr.misa & (UINT64_C(1) << ('F' - 'A'))) || (csr.mstatus_fs & 3) == 0;
  const uint32_t id_csr_addr = (w.id_inst >> 20) & 0xfff;
  const bool id_csr_en = w.id_ctrl.csr == CSR_W || w.id_ctrl.csr == CSR_S || w.id_ctrl.csr == CSR_C;
  const uint32_t id_csr_rs1 = (w.id_inst >> 15) & 0x1f;
  const bool id_csr_ren = (w.id_ctrl.csr == CSR_S || w.id_ctrl.csr == CSR_C) && id_csr_rs1 == 0;
  const bool id_system_insn = w.id_ctrl.csr == CSR_I;
  const bool id_sfence = w.id_ctrl.mem && w.id_ctrl.mem_cmd == M_SFENCE;
  const bool id_dp = w.id_ctrl.fp && w.id_ctrl.dp;
  w.id_illegal = !w.id_ctrl.legal ||
      ((w.id_ctrl.mul || w.id_ctrl.div) && !(csr.misa & (UINT64_C(1) << 12))) ||
      (w.id_ctrl.amo && !(csr.misa & (UINT64_C(1) << 0))) ||
      (w.id_ctrl.fp && id_fpu_disabled) ||
      (id_dp && !(csr.misa & (UINT64_C(1) << 3))) ||
      (w.id_rvc && !(csr.misa & (UINT64_C(1) << 2))) ||
      (w.id_ctrl.fp && in.fpu.illegal_rm) ||
      (id_csr_en && (csr_read_illegal(id_csr_addr) ||
                     (!id_csr_ren && csr_write_illegal(id_csr_addr)))) ||
      (!w.id_rvc && (id_sfence || id_system_insn) && csr_system_illegal(id_csr_addr));
  const bool id_debug_trigger = w.id_bp.debug_instruction;
  const bool id_instruction_breakpoint = w.id_bp.instruction;
  const bool id_fetch_fault = w.id_xcpt0_pf || w.id_xcpt0_ae || w.id_xcpt1_pf || w.id_xcpt1_ae;
  w.id_cause = 2;
  if (w.csr_interrupt) w.id_cause = w.csr_interrupt_cause;
  else if (id_debug_trigger) w.id_cause = 14;
  else if (id_instruction_breakpoint) w.id_cause = 3;
  else if (w.id_xcpt0_pf) w.id_cause = 12;
  else if (w.id_xcpt0_ae) w.id_cause = 1;
  else if (w.id_xcpt1_pf) w.id_cause = 12;
  else if (w.id_xcpt1_ae) w.id_cause = 1;
  else if (w.id_illegal) w.id_cause = 2;
  w.id_xcpt = id_debug_trigger || id_instruction_breakpoint || w.id_illegal || id_fetch_fault;

  // register-file write of this cycle (RegFile write-through read ports)
  {
    const bool div_resp_valid = div_.state == DIV_S_DONE_MUL || div_.state == DIV_S_DONE_DIV;
    const bool wb_wxd = wb.valid && wb.ctrl.wxd;
    bool ll_wen = div_resp_valid && !wb_wxd;
    uint32_t ll_waddr = static_cast<uint32_t>(div_.req_tag) & 31u;
    const uint64_t ll_wdata = div_response_data(div_);
    if (dmem_resp_replay && dmem_resp_xpu) {
      ll_wen = true;
      ll_waddr = (resp.tag >> 1) & 31u;
    }
    const bool wb_wen = w.wb_valid_retire && wb.ctrl.wxd;
    w.rf_wen = wb_wen || ll_wen;
    if (w.rf_wen) {
      w.rf_waddr = ll_wen ? ll_waddr : rd_addr(wb.inst);
      if (w.dmem_resp_valid && dmem_resp_xpu) w.rf_wdata = resp.data;
      else if (ll_wen) w.rf_wdata = ll_wdata;
      else if (wb.ctrl.csr != CSR_N) w.rf_wdata = csr_read((wb.inst >> 20) & 0xfff, in);
      else w.rf_wdata = wb.wdata;
    }
  }
  const auto rf_read = [&](uint32_t a) -> uint64_t {
    if (a == 0) return 0;
    if (w.rf_wen && w.rf_waddr == a) return w.rf_wdata;
    return rf_[a & 31];
  };

  if (!w.ctrl_killd) {
    DecodedCtrl ctrl = w.id_ctrl;
    const uint32_t id_inst = w.id_inst;
    w.new_ex_mem_size = (id_inst >> 12) & 0x3;
    if (ctrl.mem_cmd == M_SFENCE || ctrl.mem_cmd == M_FLUSH_ALL) {
      uint8_t sfence_rs1, sfence_rs2;
      sfence_rs1 = rs1_addr(id_inst); sfence_rs2 = rs2_addr(id_inst);
      w.new_ex_mem_size = ((sfence_rs2 != 0 ? 1 : 0) << 1) | (sfence_rs1 != 0 ? 1 : 0);
    }
    if (w.id_xcpt) {
      ctrl.alu_fn = FN_ADD;
      ctrl.alu_dw = DW_XPR;
      ctrl.sel_alu1 = A1_RS1;
      ctrl.sel_alu2 = A2_ZERO;
      if (w.id_xcpt1_pf || w.id_xcpt1_ae) {
        ctrl.sel_alu1 = A1_PC;
        ctrl.sel_alu2 = A2_SIZE;
      }
      if (id_instruction_breakpoint || w.id_xcpt0_pf || w.id_xcpt0_ae) {
        ctrl.sel_alu1 = A1_PC;
        ctrl.sel_alu2 = A2_ZERO;
      }
    }
    {
      if (id_csr_ren) ctrl.csr = CSR_R;
      const bool in_m_scratch = id_csr_addr >= 0x340 && id_csr_addr <= 0x343;
      const bool in_s_scratch = id_csr_addr >= 0x140 && id_csr_addr <= 0x143;
      const bool write_flush = !(in_m_scratch || in_s_scratch);
      const bool id_csr_flush = (id_csr_en && !id_csr_ren && write_flush) || id_sfence || id_system_insn;
      w.new_ex_flush_pipe = ctrl.fence_i || id_csr_flush;
    }
    w.new_ex_sfence = id_sfence;
    w.new_ex_hw_rs1 = rs1_addr(id_inst);
    w.new_ex_hw_rs2 = rs2_addr(id_inst);
    w.new_ex_raddr1 = rs1_addr(id_inst); w.new_ex_raddr2 = rs2_addr(id_inst);
    // 4-source bypass selection (PriorityEncoder order: x0, EX, MEM non-load, MEM)
    for (int port = 0; port < 2; ++port) {
      const uint32_t rs_addr = port == 0 ? w.new_ex_raddr1 : w.new_ex_raddr2;
      const bool ren = port == 0 ? ctrl.rxs1 != 0 : ctrl.rxs2 != 0;
      const bool src0 = rs_addr == 0;
      const bool src1 = ex.valid && ex.ctrl.wxd && (rd_addr(ex.inst) & 0x1F) == rs_addr;
      const bool src2 = mem.valid && mem.ctrl.wxd && !mem.ctrl.mem && (rd_addr(mem.inst) & 0x1F) == rs_addr;
      const bool src3 = mem.valid && mem.ctrl.wxd && (rd_addr(mem.inst) & 0x1F) == rs_addr;
      const bool do_bypass = src0 || src1 || src2 || src3;
      w.new_ex_rs_bypass[port] = do_bypass;
      w.new_ex_rs_lsb[port] = src0 ? 0 : (src1 ? 1 : (src2 ? 2 : 3));
      w.new_ex_rs_msb[port] = ex.rs_msb[port];
      if (ren && !do_bypass) {
        const uint64_t rf_val = rf_read(rs_addr);
        w.new_ex_rs_lsb[port] = rf_val & 0x3;
        w.new_ex_rs_msb[port] = rf_val >> 2;
      }
    }
    {
      const uint32_t mem_wa = rd_addr(mem.inst) & 0x1F;
      const bool id_r1_nz = ctrl.rxs1 && w.new_ex_hw_rs1 != 0;
      const bool id_r2_nz = ctrl.rxs2 && w.new_ex_hw_rs2 != 0;
      const bool id_wd_nz = ctrl.wxd && rd_addr(id_inst) != 0;
      const bool data_haz = mem.ctrl.wxd &&
          ((id_r1_nz && w.new_ex_hw_rs1 == mem_wa) || (id_r2_nz && w.new_ex_hw_rs2 == mem_wa) ||
           (id_wd_nz && rd_addr(id_inst) == mem_wa));
      w.new_ex_load_use = mem.valid && data_haz && mem.ctrl.mem;
    }
    if (w.id_illegal) {
      const uint32_t enc_inst = w.id_rvc ? (w.id_raw_inst & 0xFFFF) : w.id_raw_inst;
      w.new_ex_rs_bypass[0] = false;
      w.new_ex_rs_lsb[0] = enc_inst & 0x3;
      w.new_ex_rs_msb[0] = static_cast<uint64_t>(enc_inst) >> 2;
    }
    w.new_ex_ctrl = ctrl;
    const bool stall = stall_check(w, ctrl, in);
    w.ctrl_stalld = stall;
    if (stall) w.ctrl_killd = true;
  }
  w.new_ex_valid = !w.ctrl_killd;
  w.capture_killed_id = w.csr_interrupt || w.id_replay;
  w.new_ex_replay = !w.take_pc_mem_wb && w.ibuf_inst_valid && w.id_replay;
  w.new_ex_xcpt_interrupt = !w.take_pc_mem_wb && w.ibuf_inst_valid && w.csr_interrupt;

  // ---- CSR bookkeeping wires ----
  w.csr_single_step = csr.dcsr_step && !csr.debug;
  w.csr_stall = csr.wfi || csr.status_cease_r;
  w.next_dprv = (csr.mstatus_mprv && !csr.debug) ? csr.mstatus_mpp : csr.mstatus_prv;
  w.pending_interrupts = (csr_read(0x344, in) & csr.mie) != 0;
  w.pause_unpause = ((csr.mcycle_small & 0x1fu) == 0) || ((csr.mcountinhibit & 1u) != 0) ||
                    dmem.perf_release || w.take_pc_mem_wb;
  w.disable_icache_clock_gate = ((csr.custom_0 >> 1) & 1) != 0;
  w.wb_csr_write = w.wb_valid_retire && wb.ctrl.csr >= CSR_W &&
                   !csr_write_illegal((wb.inst >> 20) & 0xfff);
  w.wb_csr_wdata = w.wb_csr_write
      ? rmw_wdata((wb.inst >> 20) & 0xfff, wb.valid ? wb.ctrl.csr : CSR_N, wb.wdata, in) : 0;
  w.fflags_accumulate = in.fpu.fcsr_flags_valid;

  // ---- divider ----
  w.div_kill = w.killm_common && div_io_kill_reg_;
  {
    const bool div_resp_valid = (div_.state == DIV_S_DONE_MUL || div_.state == DIV_S_DONE_DIV);
    const bool wb_wxd_old = wb.valid && wb.ctrl.wxd;
    w.div_resp_fire = div_resp_valid && !wb_wxd_old;
    if (dmem_resp_replay && dmem_resp_xpu) w.div_resp_fire = false;
    w.div_req_fire = ex.valid && ex.ctrl.div && div_req_ready_now;
    if (w.div_req_fire) {
      const uint8_t fn = ex.ctrl.alu_fn;
      bool cmdHi, lhsSigned, rhsSigned;
      switch (fn) {
        case FN_ADD: cmdHi = false; lhsSigned = false; rhsSigned = false; break;
        case FN_SL:  cmdHi = true;  lhsSigned = true;  rhsSigned = true;  break;
        case FN_SEQ: cmdHi = true;  lhsSigned = true;  rhsSigned = false; break;
        case FN_SNE: cmdHi = true;  lhsSigned = false; rhsSigned = false; break;
        case FN_XOR: cmdHi = false; lhsSigned = true;  rhsSigned = true;  break;
        case FN_SR:  cmdHi = false; lhsSigned = false; rhsSigned = false; break;
        case FN_OR:  cmdHi = true;  lhsSigned = true;  rhsSigned = true;  break;
        case FN_AND: cmdHi = true;  lhsSigned = false; rhsSigned = false; break;
        default:     cmdHi = false; lhsSigned = false; rhsSigned = false; break;
      }
      const bool halfW = ex.ctrl.alu_dw == DW_32;
      const auto sext_op = [&](uint64_t x, bool is_signed, uint64_t& result) -> bool {
        bool sign;
        uint64_t hi;
        if (halfW) {
          sign = is_signed && ((x >> 31) & 1);
          hi = sign ? 0xFFFFFFFFULL : 0ULL;
        } else {
          sign = is_signed && ((x >> 63) & 1);
          hi = (x >> 32) & 0xFFFFFFFFULL;
        }
        result = (hi << 32) | (x & 0xFFFFFFFFULL);
        return sign;
      };
      w.div_lhs_sign = sext_op(w.ex_rs0, lhsSigned, w.div_lhs);
      w.div_rhs_sign = sext_op(w.ex_rs1, rhsSigned, w.div_rhs);
      w.div_cmd_hi = cmdHi;
      w.div_cmd_mul = (fn & 0x4) == 0;
      w.div_req_dw = ex.ctrl.alu_dw;
      w.div_req_fn = fn;
      w.div_req_tag = rd_addr(ex.inst);
    }
  }

  // ---- scoreboards ----
  {
    w.sb_dmem_clear = dmem_resp_replay && dmem_resp_xpu;
    w.sb_dmem_addr = (resp.tag >> 1) & 31u;
    const bool wb_wen = w.wb_valid_retire && wb.ctrl.wxd;
    const bool wb_dcache_miss_now = wb.ctrl.mem && !resp.valid;
    const bool wb_set_sboard = wb.ctrl.div || wb_dcache_miss_now || wb.ctrl.rocc;
    w.sb_set = wb_set_sboard && wb_wen;
    w.sb_set_addr = rd_addr(wb.inst) & 31u;
    w.sb_div_clear = w.div_resp_fire;
    w.fpsb_set = ((wb_dcache_miss_now && (wb.ctrl.wfd != 0)) || in.fpu.sboard_set) && w.wb_valid_retire;
    w.fpsb_set_addr = rd_addr(wb.inst) & 31u;
    w.fpsb_dmem_clear = w.dmem_resp_valid && resp.replay && (resp.tag & 1u);
    w.fpsb_dmem_addr = (resp.tag >> 1) & 31u;
    w.fpsb_clear = in.fpu.sboard_clear;
    w.fpsb_clear_addr = in.fpu.sboard_clear_addr & 31u;
  }

  // ---- IBuf (kill = take_pc_mem_wb, ready = !ctrl_stalld) ----
  {
    const bool kill = w.take_pc_mem_wb;
    const bool ready = !w.ctrl_stalld;
    w.ibuf_kill = kill;
    w.ibuf_ready = ready;
    w.ibuf_next_nbufvalid = ibuf.nBufValid;
    w.imem_ready = false;
    if (ready || kill) {
      const bool imem_valid = imem.resp_valid;
      const uint64_t ic_pc = imem.resp_pc;
      const int pcWordBits = fetch_pc_word;
      const int nIC = fetch_nic;
      const uint32_t pkt = imem.resp_data;
      const bool is_rvc = fetch_rvc;
      const int nValid = fetch_nvalid;
      const bool full_insn = is_rvc || (nValid >= 2) || fetch_buffered_replay;
      const int nReady = full_insn ? (is_rvc ? 1 : 2) : 0;
      const int old_n = static_cast<int>(ibuf.nBufValid);
      int nICReady = nReady - old_n;
      if (nICReady < 0) nICReady = 0;
      if (ready) {
        w.ibuf_consume = true;
        w.ibuf_next_nbufvalid = nReady >= old_n ? 0 : static_cast<uint64_t>(old_n - nReady);
        const bool reload = imem_valid && (nReady >= old_n) && (nICReady < nIC) && (1 >= nIC - nICReady);
        if (reload) {
          const int shamt = pcWordBits + nICReady;
          w.ibuf_reload = true;
          w.ibuf_next_nbufvalid = static_cast<uint64_t>(nIC - nICReady);
          w.ibuf_reload_data = static_cast<uint64_t>((pkt >> (shamt * 16)) & 0xFFFF);
          w.ibuf_reload_pc = (ic_pc & ~UINT64_C(3)) | ((ic_pc + nICReady * 2) & UINT64_C(3));
        }
      }
      w.imem_ready = ready && (nReady >= old_n) && (nICReady >= nIC || 1 >= nIC - nICReady);
      if (kill) w.ibuf_next_nbufvalid = 0;
    }
  }

  // ---- fence / pause / blocked / might_request ----
  {
    const bool dmem_req_valid_fence = ex.valid && (ex.ctrl.mem != 0);
    const bool id_mem_busy_fence = !dmem.ordered || dmem_req_valid_fence;
    bool next_fence = id_reg_fence_;
    if (!id_mem_busy_fence) next_fence = false;
    if (!w.ctrl_killd) {
      const bool id_fence_next = (w.new_ex_ctrl.fence != 0) ||
                                 (w.new_ex_ctrl.amo && ((w.id_inst >> 26) & 1u));
      if (id_fence_next) next_fence = true;
    }
    w.next_id_reg_fence = next_fence;
    bool next_pause = id_reg_pause_;
    if (!w.ctrl_killd && w.new_ex_ctrl.fence && (((w.id_inst >> 20) & 0xfu) == 0)) next_pause = true;
    if (w.pause_unpause) next_pause = false;
    w.next_id_reg_pause = next_pause;
    w.next_blocked = !dmem.req_ready && dmem.clock_enabled && !dmem.perf_grant &&
                     (blocked_ || dmem_req_valid_fence || dmem.s2_nack);
    w.next_might_request = ex.valid || ex.replay || ex.xcpt_interrupt || mem.valid || mem.replay ||
                           mem.xcpt_interrupt || w.disable_icache_clock_gate;
  }

  // ---- module outputs ----
  out = RocketFullSystemOutputs{};
  out.imem.might_request = imem_might_request_reg_;
  out.imem.resp_ready = w.imem_ready;
  out.imem.req_valid = w.take_pc_mem_wb;
  out.imem.req_speculative = !w.take_pc_wb;
  out.imem.req_pc = ((w.wb_xcpt || w.wb_csr_eret) ? w.wb_evec
                     : w.replay_wb ? (wb.pc & kVaddrExtMask) : w.mem_npc) & kVaddrExtMask;
  out.imem.sfence_valid = wb.valid && wb.sfence;
  out.imem.sfence_rs1 = wb.mem_size & 1;
  out.imem.sfence_rs2 = (wb.mem_size >> 1) & 1;
  out.imem.sfence_addr = wb.wdata & kVaddrMask;
  out.imem.sfence_asid = (wb.rs2 & 1) != 0;
  out.imem.btb_update_valid = mem.valid && !w.take_pc_wb && w.mem_wrong_npc && (!mem_cfi || mem_cfi_taken);
  out.imem.btb_prediction.cfi_type = mem.btb.cfiType;
  out.imem.btb_prediction.taken = mem.btb.taken;
  out.imem.btb_prediction.mask = mem.btb.mask;
  out.imem.btb_prediction.bridx = mem.btb.bridx;
  out.imem.btb_prediction.target = mem.btb.target & kVaddrMask;
  out.imem.btb_prediction.entry = mem.btb.entry;
  out.imem.btb_prediction.bht_history = mem.btb.bht_history;
  out.imem.btb_prediction.bht_value = mem.btb.bht_value;
  {
    const uint64_t branch_pc = (mem.pc + (mem.rvc ? 0 : 2)) & kVaddrMask;
    out.imem.btb_pc = branch_pc & ~UINT64_C(3);
    out.imem.btb_target = out.imem.req_pc & kVaddrMask;
    out.imem.btb_is_valid = mem_cfi;
    out.imem.btb_branch_pc = branch_pc;
    if ((mem.ctrl.jal || mem.ctrl.jalr) && ((rd_addr(mem.inst) & 1) != 0)) out.imem.btb_cfi_type = 2;
    else if (mem.ctrl.jalr && (((mem.inst >> 15) & 0x1b) == 1)) out.imem.btb_cfi_type = 3;
    else if (mem.ctrl.jal || mem.ctrl.jalr) out.imem.btb_cfi_type = 1;
    else out.imem.btb_cfi_type = 0;
    out.imem.bht_update_valid = mem.valid && !w.take_pc_wb;
    out.imem.bht_prediction_history = mem.btb.bht_history;
    out.imem.bht_prediction_value = mem.btb.bht_value;
    out.imem.bht_pc = out.imem.btb_pc;
    out.imem.bht_branch = mem.ctrl.branch;
    out.imem.bht_taken = mem.br_taken;
    out.imem.bht_mispredict = w.mem_wrong_npc;
    out.imem.flush_icache = wb.valid && wb.ctrl.fence_i && !dmem.s2_nack;
  }
  out.dmem.req_valid = ex.valid && ex.ctrl.mem;
  out.dmem.req_addr = encode_virtual_address(w.ex_rs0, w.ex_adder);
  out.dmem.req_tag = ((rd_addr(ex.inst) & 31u) << 1) | (ex.ctrl.fp ? 1u : 0u);
  out.dmem.req_cmd = ex.ctrl.mem_cmd;
  out.dmem.req_size = ex.mem_size & 3;
  out.dmem.req_signed = ((ex.inst >> 14) & 1) == 0;
  out.dmem.req_dprv = csr.status_dprv & 3;
  out.dmem.s1_kill = w.killm_common || w.mem_breakpoint || w.mem_debug_breakpoint || w.fpu_kill_mem;
  out.dmem.s1_data = mem.ctrl.fp ? in.fpu.store_data : mem.rs2;
  out.dmem.keep_clock_enabled = w.id_visible && w.id_ctrl.mem && !w.csr_stall;
  out.ptbr_mode = csr.satp_mode & 0xf;
  out.ptbr_asid = 0;
  out.ptbr_ppn = csr.satp_ppn & UINT64_C(0xfffffffffff);
  if (!status_cache_valid_) {
    fill_status(csr, status_cache_);
    status_cache_valid_ = true;
  }
  out.status = status_cache_;
  if (!pmp_cache_valid_) {
    for (unsigned index = 0; index < 8; ++index) {
      pmp_cache_[index].cfg_l = csr.pmp[index].cfg_l;
      pmp_cache_[index].cfg_res = 0;
      pmp_cache_[index].cfg_a = csr.pmp[index].cfg_a & 3;
      pmp_cache_[index].cfg_x = csr.pmp[index].cfg_x;
      pmp_cache_[index].cfg_w = csr.pmp[index].cfg_w;
      pmp_cache_[index].cfg_r = csr.pmp[index].cfg_r;
      pmp_cache_[index].addr = csr.pmp[index].addr & UINT64_C(0x3fffffff);
      pmp_cache_[index].mask = pmp_mask(csr, index);
    }
    pmp_cache_valid_ = true;
  }
  std::memcpy(out.pmp, pmp_cache_, sizeof pmp_cache_);
  {
    const uint64_t custom_wdata = rmw_wdata((wb.inst >> 20) & 0xfff,
                                            wb.valid ? wb.ctrl.csr : CSR_N, wb.wdata, in);
    const uint32_t wb_csr_addr = (wb.inst >> 20) & 0xfff;
    const bool wb_csr_wen = wb.valid &&
        (wb.ctrl.csr == CSR_W || wb.ctrl.csr == CSR_S || wb.ctrl.csr == CSR_C);
    constexpr uint32_t custom_csr_ids[4] = {0x7c1, 0xf12, 0xf11, 0xf13};
    for (unsigned index = 0; index < 4; ++index) {
      out.custom_csr_wen[index] = wb_csr_wen && wb_csr_addr == custom_csr_ids[index];
      out.custom_csr_wdata[index] = custom_wdata;
    }
    out.custom_csr_value[0] = csr.custom_0;
    out.custom_csr_value[1] = csr.custom_1;
    out.custom_csr_value[2] = csr.custom_2;
    out.custom_csr_value[3] = csr.custom_3;
  }
  out.fpu.hartid = in.hartid;
  out.fpu.time = ((csr.value_hi_1 << kWideSmallBits) | (csr.mcycle_small & kWideSmallMask)) &
                 UINT64_C(0xffffffff);
  out.fpu.inst = w.id_inst;
  out.fpu.fromint_data = w.ex_rs0;
  out.fpu.fcsr_rm = csr.frm & 7;
  out.fpu.dmem_resp_valid = w.dmem_resp_valid && ((resp.tag & 1u) != 0);
  out.fpu.dmem_resp_type = resp.size;
  out.fpu.dmem_resp_tag = (resp.tag >> 1) & 31u;
  out.fpu.dmem_resp_data = resp.data_word_bypass;
  out.fpu.valid = !w.ctrl_killd && w.id_ctrl.fp;
  out.fpu.killx = w.ctrl_killx;
  out.fpu.killm = w.killm_common;
  out.fpu.keep_clock_enabled = (csr.custom_0 >> 2) & 1;
  out.rocc.cmd_valid = wb.valid && wb.ctrl.rocc && !replay_wb_common;
  out.rocc.cmd_inst.funct = (wb.inst >> 25) & 0x7f;
  out.rocc.cmd_inst.rs2 = (wb.inst >> 20) & 0x1f;
  out.rocc.cmd_inst.rs1 = (wb.inst >> 15) & 0x1f;
  out.rocc.cmd_inst.xd = (wb.inst >> 14) & 1;
  out.rocc.cmd_inst.xs1 = (wb.inst >> 13) & 1;
  out.rocc.cmd_inst.xs2 = (wb.inst >> 12) & 1;
  out.rocc.cmd_inst.rd = (wb.inst >> 7) & 0x1f;
  out.rocc.cmd_inst.opcode = wb.inst & 0x7f;
  out.rocc.cmd_rs1 = wb.wdata;
  out.rocc.cmd_rs2 = wb.rs2;
  out.rocc.cmd_status = out.status;
  out.rocc.exception = false;
  {
    const uint64_t trace_cause = w.wb_cause;
    const bool trace_exception = w.wb_xcpt || w.wb_csr_exception;
    out.trace.valid = w.wb_valid_retire || trace_exception;
    out.trace.iaddr = wb.pc & kVaddrExtMask;
    const uint32_t trace_upper = ((wb.raw_inst & 3u) == 3u) ? (wb.inst & UINT32_C(0xffff0000)) : 0;
    out.trace.insn = trace_upper | (wb.raw_inst & UINT32_C(0xffff));
    out.trace.priv = ((csr.debug & 1) << 2) | (csr.mstatus_prv & 3);
    out.trace.exception = trace_exception;
    out.trace.interrupt = (trace_cause >> 63) != 0;
    out.trace.cause = trace_cause;
    const uint64_t code = trace_cause & UINT64_C(0x3f);
    const bool tval_valid = w.wb_xcpt && (trace_cause >> 63) == 0 &&
        (code == 2 || code == 3 || code == 4 || code == 6 || code == 1 || code == 5 ||
         code == 7 || code == 12 || code == 13 || code == 15);
    out.trace.tval = tval_valid ? encode_virtual_address(wb.wdata, wb.wdata) : 0;
  }
  out.bpwatch_valid = wb.wphit_0;
  out.bpwatch_action = csr.bp_0_control_action & 1;
  out.cease = csr.status_cease_r && !clock_en_reg_;
  out.wfi = csr.wfi;
}

// -------------------------------------------------------------- commit ----

void Core::div_step() {
  Div& div = div_;
  switch (div.state) {
    case DIV_S_NEG_INPUTS: {
      const uint64_t old_rem_lo = div.remainder;
      const uint64_t neg_rem = UINT64_C(0) - old_rem_lo;
      uint64_t sub_lo; uint8_t sub_hi;
      compute_subtractor(div.rem_hi, div.rem_top, div.divisor_lo, div.divisor_hi, sub_lo, sub_hi);
      if (old_rem_lo & (1ULL << 63)) { div.remainder = neg_rem; div.rem_hi = 0; div.rem_top = 0; }
      if (div.divisor_lo & (1ULL << 63)) { div.divisor_lo = sub_lo; div.divisor_hi = sub_hi; }
      div.state = DIV_S_DIV;
      break;
    }
    case DIV_S_MUL: {
      // Radix-256 multiplication: consume one signed digit and add its
      // partial product to the accumulator. Packing below only describes
      // the existing observation fields; there is no gate-level multiplier.
      const uint64_t remaining = div.remainder;
      const uint64_t accumulator_low = (div.rem_hi >> 1) | (uint64_t(div.rem_top & 1) << 63);
      const auto accumulator = signed65(accumulator_low, div.rem_top >> 1);
      const auto multiplicand = signed65(div.divisor_lo, div.divisor_hi);
      const int digit = int(remaining & 255) - ((div.rem_hi & 1) ? 256 : 0);
      const __uint128_t sum = __uint128_t(accumulator + digit * multiplicand);
      const uint64_t shifted_low = (remaining >> 8) | (uint64_t(sum) << 56);
      const uint64_t shifted_high = uint64_t(sum >> 8);
      const unsigned old_count = div.count;
      const unsigned processed = old_count * kMulUnroll;
      const bool early = old_count > 0 && old_count < unsigned(kMulEndCount) && !div.isHi &&
          (remaining << processed) == 0;
      const __uint128_t packed = (__uint128_t(accumulator_low) << 64) | remaining;
      div.remainder = early ? uint64_t(packed >> (64-processed)) : shifted_low;
      const bool sign_digit = old_count == unsigned(kMulEndCount-1) && div.neg_out;
      div.rem_hi = (shifted_high << 1) | unsigned(sign_digit);
      div.rem_top = uint8_t((sum >> 71) & 3);
      div.count = old_count + 1;
      if (early || old_count == unsigned(kMulEndCount)) {
        div.state = DIV_S_DONE_MUL; div.resHi = div.isHi;
      }
      break;
    }
    case DIV_S_DIV: {
      const uint64_t old_rem_lo = div.remainder;
      const uint64_t old_rem_hi = div.rem_hi;
      const uint64_t old_count = div.count;
      uint64_t sub_lo; uint8_t sub_hi;
      compute_subtractor(old_rem_hi, div.rem_top, div.divisor_lo, div.divisor_hi, sub_lo, sub_hi);
      const bool less = (sub_hi & 1) != 0;
      const uint64_t new_upper = less ? old_rem_hi : sub_lo;
      div.rem_top = (uint8_t)((new_upper >> 63) & 1);
      div.rem_hi = ((new_upper & 0x7FFFFFFFFFFFFFFFULL) << 1) | (old_rem_lo >> 63);
      div.remainder = (old_rem_lo << 1) | (less ? 0ULL : 1ULL);
      if (old_count == (uint64_t)kDivEndCount) {
        div.state = div.neg_out ? DIV_S_NEG_OUTPUT : DIV_S_DONE_DIV;
        div.resHi = div.isHi;
      }
      div.count = old_count + 1;
      const bool divby0 = (old_count == 0) && !(sub_hi & 1);
      if (old_count == 0) {
        const auto log2_val = [](uint64_t x) -> int { return x == 0 ? 0 : 63 - __builtin_clzll(x); };
        const int divisorMSB = log2_val(div.divisor_lo);
        const int dividendMSB = log2_val(old_rem_lo);
        const int eOutPos = (~(dividendMSB - divisorMSB)) & 0x3F;
        const bool eOut = !divby0 && (eOutPos >= 1);
        if (eOut) {
          const __uint128_t shifted = (__uint128_t)old_rem_lo << eOutPos;
          div.remainder = (uint64_t)shifted;
          div.rem_hi = (uint64_t)(shifted >> 64);
          div.rem_top = 0;
          div.count = (uint64_t)eOutPos;
        }
      }
      if (divby0 && !div.isHi) div.neg_out = false;
      break;
    }
    case DIV_S_NEG_OUTPUT: {
      const uint64_t result = div.resHi
          ? ((div.rem_hi >> 1) | ((uint64_t)(div.rem_top & 1) << 63)) : div.remainder;
      div.remainder = UINT64_C(0) - result;
      div.rem_hi = 0;
      div.rem_top = 0;
      div.state = DIV_S_DONE_DIV;
      div.resHi = false;
      break;
    }
    default:
      break;
  }
}

void Core::commit(const RocketFullSystemInputs& in, const CoreWires& w) {
  pre_derived_valid_ = false;
  Csr& csr = csr_;
  retirement_ = CoreRetirement{};
  retirement_.debug_mode = csr.debug != 0;
  late_integer_write_ = CoreIntegerWriteback{};
  if (!in.reset && (w.wb_valid_retire || w.wb_xcpt || w.wb_csr_exception)) {
    retirement_.trapped = w.wb_xcpt || w.wb_csr_exception;
    retirement_.retired = w.wb_valid_retire && !retirement_.trapped;
    retirement_.pc = sign_extend(wb_.pc, 40);
    retirement_.instruction = wb_.rvc ? (wb_.raw_inst & 0xffffu) : wb_.inst;
    retirement_.instruction_bytes = wb_.rvc ? 2 : 4;
    retirement_.privilege = static_cast<uint8_t>(csr.mstatus_prv & 3);
    retirement_.cause = retirement_.trapped ? w.wb_cause : 0;
    retirement_.expanded_instruction = wb_.inst;
    if (retirement_.retired) {
      const uint8_t rd = static_cast<uint8_t>(rd_addr(wb_.inst));
      retirement_.x_write = wb_.ctrl.wxd && rd != 0;
      retirement_.xrd = rd;
      retirement_.x_value_valid = retirement_.x_write && !w.sb_set;
      if (retirement_.x_value_valid) retirement_.xvalue = w.rf_wdata;
      retirement_.fp_write = wb_.ctrl.wfd;
      retirement_.frd = rd;
      const unsigned opcode = wb_.inst & 0x7f;
      retirement_.store = opcode == 0x23 || opcode == 0x27;
      if (retirement_.store) {
        const unsigned size = (wb_.inst >> 12) & 7;
        retirement_.store_bytes = size < 4 ? static_cast<uint8_t>(1u << size) : 0;
        retirement_.store_address = wb_.wdata;
        retirement_.store_value = size == 3 ? wb_store_data_ :
            (size < 3 ? (wb_store_data_ & ((UINT64_C(1) << (8u << size)) - 1)) : 0);
      }
    }
    if (retirement_.retired) committed_pc_ = retirement_.pc;
  }
  // Match Rocket's xrfWriteBundle: omit the ordinary/placeholder write on
  // the current WB instruction; report the actual late completion separately.
  if (!in.reset && w.rf_wen && (w.rf_waddr & 31) != 0 &&
      !(w.wb_valid_retire && wb_.ctrl.wxd && rd_addr(wb_.inst) == (w.rf_waddr & 31))) {
    late_integer_write_.valid = true;
    late_integer_write_.rd = static_cast<uint8_t>(w.rf_waddr & 31);
    late_integer_write_.value = w.rf_wdata;
  }
  // Only these commit paths modify the stable CSR projection. Counter,
  // fflags and WFI/cease values are still exported unconditionally below.
  if (w.wb_csr_write || w.wb_xcpt || w.wb_csr_exception || w.wb_return ||
      (w.fflags_accumulate && csr.mstatus_fs != 3)) invalidate_csr_views();
  const uint64_t old_wfi = csr.wfi, old_cease = csr.status_cease_r, old_dprv = csr.status_dprv;

  // ---- CSR bookkeeping (reads the pre-edge WB slot) ----
  {
    const Stage& old_wb = wb_;
    // counters
    if (!w.csr_stall && !(csr.mcountinhibit & 1)) {
      const uint64_t next = (csr.mcycle_small & kWideSmallMask) + 1;
      if (next & (1ULL << kWideSmallBits)) csr.value_hi_1++;
      csr.mcycle_small = next & kWideSmallMask;
    }
    if (!(csr.mcountinhibit & 4) && w.wb_valid_retire) {
      const uint64_t next = (csr.value_lo & kWideSmallMask) + 1;
      if (next & (1ULL << kWideSmallBits)) csr.value_hi++;
      csr.value_lo = next & kWideSmallMask;
    }
    if (w.fflags_accumulate) {
      csr.fflags = (csr.fflags | in.fpu.fcsr_flags) & 0x1f;
      csr.mstatus_fs = 3;
    }
    if (w.wb_xcpt || w.wb_csr_exception) {
      const uint64_t tval_source = (w.wb_csr_exception && !w.wb_xcpt) ? 0 : old_wb.wdata;
      handle_trap(old_wb.pc, old_wb.inst, old_wb.ctrl.csr, w.wb_cause, tval_source);
    } else if (w.wb_return) {
      uint64_t ret_prv = 3;
      if (w.wb_sret) {
        ret_prv = csr.mstatus_spp & 1;
        csr.mstatus_sie = csr.mstatus_spie;
        csr.mstatus_spie = 1;
        csr.mstatus_spp = 0;
      } else if (w.wb_dret) {
        ret_prv = csr.dcsr_prv & 3;
        csr.debug = 0;
      } else {
        ret_prv = csr.mstatus_mpp & 3;
        csr.mstatus_mie = csr.mstatus_mpie;
        csr.mstatus_mpie = 1;
        csr.mstatus_mpp = 0;
      }
      csr.mstatus_prv = ret_prv == 2 ? 0 : ret_prv;
      if (csr.mstatus_prv < 3) csr.mstatus_mprv = 0;
    }
    if (w.wb_csr_write) update_csr(old_wb, w.wb_csr_wdata);
    if (w.wb_wfi && !w.csr_single_step && !csr.debug) csr.wfi = 1;
    if (w.wb_cease) csr.status_cease_r = 1;
    if (w.pending_interrupts || in.interrupt_debug || w.wb_xcpt || w.wb_csr_exception) csr.wfi = 0;
    if (!w.csr_single_step) csr.singleStepped = 0;
    else if (w.wb_valid_retire || w.wb_xcpt || w.wb_csr_exception) csr.singleStepped = 1;
    csr.status_dprv = w.next_dprv & 3;
    if (old_wfi != csr.wfi || old_cease != csr.status_cease_r || old_dprv != csr.status_dprv)
      status_cache_valid_ = false;
  }

  // ---- register file ----
  if (w.rf_wen && (w.rf_waddr & 31u) != 0) rf_[w.rf_waddr & 31u] = w.rf_wdata;

  // ---- pipeline registers: WB <- MEM, MEM <- EX, EX <- ID ----
  if (w.mem_pc_valid) {
    wb_store_data_ = mem_.ctrl.fp ? in.fpu.store_data : mem_.rs2;
    wb_ = mem_;
    wb_.wdata = w.new_wb_wdata;
    wb_.cause = w.mem_cause;
    wb_.wphit_0 = w.new_wb_wphit;
  }
  wb_.valid = w.new_wb_valid;
  wb_.xcpt = w.new_wb_xcpt;
  wb_.flush_pipe = w.new_wb_flush_pipe;
  wb_.replay = w.new_wb_replay;

  if (w.mem_flush_stall) {
    mem_.sfence = false;
  } else if (w.ex_pc_valid) {
    const uint64_t old_mem_rs2 = mem_.rs2;
    mem_ = ex_;
    if (w.new_mem_debug_fence) {
      mem_.ctrl.fence_i = 1;
      mem_.flush_pipe = true;
    }
    mem_.wdata = w.new_mem_wdata;
    mem_.br_taken = w.new_mem_br_taken;
    mem_.store = w.new_mem_store;
    mem_.load = w.new_mem_load;
    mem_.slow_bypass = w.new_mem_slow_bypass;
    mem_.rs2 = w.new_mem_rs2_valid ? w.new_mem_rs2 : old_mem_rs2;
  }
  mem_.valid = w.new_mem_valid;
  mem_.replay = w.new_mem_replay;
  mem_.xcpt = w.new_mem_xcpt;
  mem_.xcpt_interrupt = w.new_mem_xcpt_interrupt;

  if (!w.ctrl_killd) {
    ex_.pc = w.id_pc;
    ex_.inst = w.id_inst;
    ex_.raw_inst = w.id_raw_inst;
    ex_.rvc = w.id_rvc;
    ex_.ctrl = w.new_ex_ctrl;
    ex_.mem_size = w.new_ex_mem_size;
    ex_.cause = w.id_cause;
    ex_.xcpt = w.id_xcpt;
    ex_.flush_pipe = w.new_ex_flush_pipe;
    ex_.sfence = w.new_ex_sfence;
    ex_.wphit_0 = w.id_bp.instruction || w.id_bp.debug_instruction;
    ex_.btb = w.id_btb;
    ex_.hw_rs1_addr = w.new_ex_hw_rs1;
    ex_.hw_rs2_addr = w.new_ex_hw_rs2;
    ex_.raddr1 = w.new_ex_raddr1;
    ex_.raddr2 = w.new_ex_raddr2;
    for (int port = 0; port < 2; ++port) {
      ex_.rs_bypass[port] = w.new_ex_rs_bypass[port];
      ex_.rs_lsb[port] = w.new_ex_rs_lsb[port];
      ex_.rs_msb[port] = w.new_ex_rs_msb[port];
    }
    ex_.load_use = w.new_ex_load_use;
  }
  ex_.valid = w.new_ex_valid;
  if (w.ctrl_killd) ex_.xcpt = false;
  if (w.capture_killed_id) {
    ex_.cause = w.id_cause;
    ex_.inst = w.id_inst;
    ex_.raw_inst = w.id_raw_inst;
    ex_.pc = w.id_pc;
    ex_.btb = w.id_btb;
    ex_.wphit_0 = w.id_bp.instruction || w.id_bp.debug_instruction;
  }
  ex_.replay = w.new_ex_replay;
  ex_.xcpt_interrupt = w.new_ex_xcpt_interrupt;

  // ---- divider ----
  div_step();
  if (w.div_kill || w.div_resp_fire) div_.state = DIV_S_READY;
  if (w.div_req_fire) {
    Div& d = div_;
    d.cmdMul = w.div_cmd_mul;
    d.req_dw = w.div_req_dw;
    d.req_tag = w.div_req_tag;
    d.req_fn = w.div_req_fn;
    d.resHi = false;
    d.divisor_lo = w.div_rhs;
    d.divisor_hi = w.div_rhs_sign ? 1 : 0;
    d.remainder = w.div_lhs;
    d.rem_hi = 0;
    d.rem_top = 0;
    d.isHi = w.div_cmd_hi;
    d.neg_out = w.div_cmd_hi ? w.div_lhs_sign : (w.div_lhs_sign != w.div_rhs_sign);
    const bool halfW = w.div_req_dw == DW_32;
    d.count = (d.cmdMul && halfW) ? (uint64_t)kMulDw32Start : 0;
    if (d.cmdMul) d.state = DIV_S_MUL;
    else d.state = (w.div_lhs_sign || w.div_rhs_sign) ? DIV_S_NEG_INPUTS : DIV_S_DIV;
  }
  div_io_kill_reg_ = w.div_req_fire;

  // ---- scoreboards ----
  if (w.sb_dmem_clear || w.sb_div_clear || w.sb_set) {
    uint32_t next = sboard_ & ~UINT32_C(1);
    if (w.sb_dmem_clear) next &= ~(UINT32_C(1) << w.sb_dmem_addr);
    if (w.sb_div_clear) next &= ~(UINT32_C(1) << (static_cast<uint32_t>(div_.req_tag) & 31u));
    if (w.sb_set) next |= UINT32_C(1) << w.sb_set_addr;
    sboard_ = next;
  }
  if (w.fpsb_set) fp_sboard_ |= (1u << w.fpsb_set_addr);
  if (w.fpsb_dmem_clear) fp_sboard_ &= ~(1u << w.fpsb_dmem_addr);
  if (w.fpsb_clear) fp_sboard_ &= ~(1u << w.fpsb_clear_addr);

  // ---- IBuf ----
  if (w.ibuf_reload) {
    ibuf_.buf_data = w.ibuf_reload_data;
    ibuf_.buf_pc = w.ibuf_reload_pc;
    ibuf_.buf_xcpt_pf_inst = in.imem.resp_xcpt_pf_inst;
    ibuf_.buf_xcpt_ae_inst = in.imem.resp_xcpt_ae_inst;
    ibuf_.buf_replay = in.imem.resp_replay;
    ibuf_.btb.cfiType = in.imem.resp_btb.cfi_type;
    ibuf_.btb.taken = in.imem.resp_btb.taken;
    ibuf_.btb.mask = in.imem.resp_btb.mask;
    ibuf_.btb.bridx = in.imem.resp_btb.bridx;
    ibuf_.btb.target = in.imem.resp_btb.target;
    ibuf_.btb.entry = in.imem.resp_btb.entry;
    ibuf_.btb.bht_history = in.imem.resp_btb.bht_history;
    ibuf_.btb.bht_value = in.imem.resp_btb.bht_value;
  }
  ibuf_.nBufValid = w.ibuf_next_nbufvalid;

  // ---- fence / pause / blocked / might_request ----
  id_reg_fence_ = w.next_id_reg_fence;
  id_reg_pause_ = w.next_id_reg_pause;
  blocked_ = w.next_blocked;
  imem_might_request_reg_ = w.next_might_request;

  if (in.reset) apply_reset_priority();
  csr.satp_asid = 0;
  export_image();
}

void Core::apply_reset_priority() {
  invalidate_csr_views();
  invalidate_pmp_views();
  Csr& csr = csr_;
  clock_en_reg_ = true;
  id_reg_fence_ = false;
  sboard_ = 0;
  fp_sboard_ = 0;
  ibuf_.nBufValid = 0;
  div_.state = DIV_S_READY;
  csr.mstatus_prv = 3;
  csr.mstatus_mpp = 3;
  csr.mstatus_mprv = 0;
  csr.mstatus_sum = 0;
  csr.mstatus_mxr = 0;
  csr.mstatus_tvm = 0;
  csr.mstatus_tw = 0;
  csr.mstatus_tsr = 0;
  csr.mstatus_sie = 0;
  csr.mstatus_spie = 0;
  csr.mstatus_spp = 0;
  csr.mstatus_mpie = 0;
  csr.mstatus_mie = 0;
  csr.mstatus_fs = 0;
  csr.dcsr_ebreakm = 0;
  csr.dcsr_ebreaks = 0;
  csr.dcsr_ebreaku = 0;
  csr.dcsr_prv = 3;
  csr.dcsr_cause = 0;
  csr.dcsr_step = 0;
  csr.debug = 0;
  csr.bp_0_control_dmode = 0;
  csr.bp_0_control_action = 0;
  csr.bp_0_control_r = 0;
  csr.bp_0_control_w = 0;
  csr.bp_0_control_x = 0;
  for (auto& pmp : csr.pmp) { pmp.cfg_a = 0; pmp.cfg_l = 0; }
  csr.mcause = 0;
  csr.mtvec = 0;
  csr.wfi = 0;
  csr.status_cease_r = 0;
  csr.mcountinhibit = 0;
  csr.value_lo = 0;
  csr.value_hi = 0;
  csr.value_hi_1 = 0;
  csr.mcycle_small = 0;
  csr.misa = kMisaFullSystem;
  csr.custom_0 = 0x208;
  csr.custom_1 = 0x1;
  csr.custom_2 = 0x0;
  csr.custom_3 = 0x20181004;
  csr.rnmie = 1;
}

void Core::reset(uint32_t reset_vector) {
  retirement_ = CoreRetirement{};
  late_integer_write_ = CoreIntegerWriteback{};
  committed_pc_ = 0;
  wb_store_data_ = 0;
  pre_derived_valid_ = false;
  invalidate_csr_views();
  invalidate_pmp_views();
  (void)reset_vector;
  ex_ = Stage{};
  mem_ = Stage{};
  wb_ = Stage{};
  std::memset(&csr_, 0, sizeof csr_);
  ibuf_ = IBuf{};
  div_ = Div{};
  std::memset(rf_, 0, sizeof rf_);
  blocked_ = false;
  id_reg_pause_ = false;
  id_reg_fence_ = false;
  clock_en_reg_ = false;
  imem_might_request_reg_ = false;
  sboard_ = 0;
  fp_sboard_ = 0;
  div_io_kill_reg_ = false;
  for (auto& e : decode_cache_) e.valid = false;
  // Values the legacy reset() establishes before the first reset edge.
  csr_.misa = kMisaFullSystem;
  csr_.custom_0 = 0x208;
  csr_.custom_1 = 0x1;
  csr_.custom_2 = 0x0;
  csr_.custom_3 = 0x20181004;
  csr_.mstatus_prv = 3;
  csr_.mstatus_mpp = 3;
  csr_.dcsr_prv = 3;
  csr_.rnmie = 1;
  export_image();
}

void Core::export_image() {
  if (architectural_mode_) return;
  Image::Core& c = *I_;
  const Csr& s = csr_;
  c.r = sboard_;
  c.blocked = blocked_;
  c.csr_io_status_cease_r = s.status_cease_r;
  if (csr_export_dirty_) {
    c.csr_reg_bp_0_address = s.bp_0_address;
    c.csr_reg_bp_0_control_action = s.bp_0_control_action;
    c.csr_reg_bp_0_control_m = s.bp_0_control_m;
    c.csr_reg_bp_0_control_r = s.bp_0_control_r;
    c.csr_reg_bp_0_control_s = s.bp_0_control_s;
    c.csr_reg_bp_0_control_tmatch = s.bp_0_control_tmatch;
    c.csr_reg_bp_0_control_u = s.bp_0_control_u;
    c.csr_reg_bp_0_control_w = s.bp_0_control_w;
    c.csr_reg_bp_0_control_x = s.bp_0_control_x;
    c.csr_reg_custom_0 = s.custom_0;
    c.csr_reg_dcsr_ebreakm = s.dcsr_ebreakm;
    c.csr_reg_dcsr_ebreaks = s.dcsr_ebreaks;
    c.csr_reg_dcsr_ebreaku = s.dcsr_ebreaku;
    c.csr_reg_dcsr_prv = s.dcsr_prv;
    c.csr_reg_dcsr_step = s.dcsr_step;
    c.csr_reg_debug = s.debug;
    c.csr_reg_dpc = s.dpc;
    c.csr_reg_dscratch = s.dscratch;
    c.csr_reg_frm = s.frm;
    c.csr_reg_mcause = s.mcause;
    c.csr_reg_mcounteren = static_cast<uint32_t>(s.mcounteren);
    c.csr_reg_mcountinhibit = s.mcountinhibit;
    c.csr_reg_medeleg = s.medeleg;
    c.csr_reg_mepc = s.mepc;
    c.csr_reg_mideleg = s.mideleg;
    c.csr_reg_mie = s.mie;
    c.csr_reg_mip_ssip = s.mip_ssip;
    c.csr_reg_mip_stip = s.mip_stip;
    c.csr_reg_misa = s.misa;
    c.csr_reg_mscratch = s.mscratch;
    c.csr_reg_mstatus_fs = s.mstatus_fs;
    c.csr_reg_mstatus_mie = s.mstatus_mie;
    c.csr_reg_mstatus_mpie = s.mstatus_mpie;
    c.csr_reg_mstatus_mpp = s.mstatus_mpp;
    c.csr_reg_mstatus_mprv = s.mstatus_mprv;
    c.csr_reg_mstatus_mxr = s.mstatus_mxr;
    c.csr_reg_mstatus_prv = s.mstatus_prv;
    c.csr_reg_mstatus_sie = s.mstatus_sie;
    c.csr_reg_mstatus_spie = s.mstatus_spie;
    c.csr_reg_mstatus_spp = s.mstatus_spp;
    c.csr_reg_mstatus_sum = s.mstatus_sum;
    c.csr_reg_mstatus_tsr = s.mstatus_tsr;
    c.csr_reg_mstatus_tvm = s.mstatus_tvm;
    c.csr_reg_mstatus_tw = s.mstatus_tw;
    c.csr_reg_mtval = s.mtval;
    c.csr_reg_mtvec = static_cast<uint32_t>(s.mtvec);
    c.csr_reg_satp_mode = s.satp_mode;
    c.csr_reg_satp_ppn = s.satp_ppn;
    c.csr_reg_scause = s.scause;
    c.csr_reg_scounteren = static_cast<uint32_t>(s.scounteren);
    c.csr_reg_sepc = s.sepc;
    c.csr_reg_sscratch = s.sscratch;
    c.csr_reg_stval = s.stval;
    c.csr_reg_stvec = s.stvec;
    csr_export_dirty_ = false;
  }
  if (pmp_export_dirty_) {
    c.csr_reg_pmp_0_addr = static_cast<uint32_t>(s.pmp[0].addr); c.csr_reg_pmp_0_cfg_a = s.pmp[0].cfg_a;
    c.csr_reg_pmp_0_cfg_l = s.pmp[0].cfg_l; c.csr_reg_pmp_0_cfg_r = s.pmp[0].cfg_r;
    c.csr_reg_pmp_0_cfg_w = s.pmp[0].cfg_w; c.csr_reg_pmp_0_cfg_x = s.pmp[0].cfg_x;
    c.csr_reg_pmp_1_addr = static_cast<uint32_t>(s.pmp[1].addr); c.csr_reg_pmp_1_cfg_a = s.pmp[1].cfg_a;
    c.csr_reg_pmp_1_cfg_l = s.pmp[1].cfg_l; c.csr_reg_pmp_1_cfg_r = s.pmp[1].cfg_r;
    c.csr_reg_pmp_1_cfg_w = s.pmp[1].cfg_w; c.csr_reg_pmp_1_cfg_x = s.pmp[1].cfg_x;
    c.csr_reg_pmp_2_addr = static_cast<uint32_t>(s.pmp[2].addr); c.csr_reg_pmp_2_cfg_a = s.pmp[2].cfg_a;
    c.csr_reg_pmp_2_cfg_l = s.pmp[2].cfg_l; c.csr_reg_pmp_2_cfg_r = s.pmp[2].cfg_r;
    c.csr_reg_pmp_2_cfg_w = s.pmp[2].cfg_w; c.csr_reg_pmp_2_cfg_x = s.pmp[2].cfg_x;
    c.csr_reg_pmp_3_addr = static_cast<uint32_t>(s.pmp[3].addr); c.csr_reg_pmp_3_cfg_a = s.pmp[3].cfg_a;
    c.csr_reg_pmp_3_cfg_l = s.pmp[3].cfg_l; c.csr_reg_pmp_3_cfg_r = s.pmp[3].cfg_r;
    c.csr_reg_pmp_3_cfg_w = s.pmp[3].cfg_w; c.csr_reg_pmp_3_cfg_x = s.pmp[3].cfg_x;
    c.csr_reg_pmp_4_addr = static_cast<uint32_t>(s.pmp[4].addr); c.csr_reg_pmp_4_cfg_a = s.pmp[4].cfg_a;
    c.csr_reg_pmp_4_cfg_l = s.pmp[4].cfg_l; c.csr_reg_pmp_4_cfg_r = s.pmp[4].cfg_r;
    c.csr_reg_pmp_4_cfg_w = s.pmp[4].cfg_w; c.csr_reg_pmp_4_cfg_x = s.pmp[4].cfg_x;
    c.csr_reg_pmp_5_addr = static_cast<uint32_t>(s.pmp[5].addr); c.csr_reg_pmp_5_cfg_a = s.pmp[5].cfg_a;
    c.csr_reg_pmp_5_cfg_l = s.pmp[5].cfg_l; c.csr_reg_pmp_5_cfg_r = s.pmp[5].cfg_r;
    c.csr_reg_pmp_5_cfg_w = s.pmp[5].cfg_w; c.csr_reg_pmp_5_cfg_x = s.pmp[5].cfg_x;
    c.csr_reg_pmp_6_addr = static_cast<uint32_t>(s.pmp[6].addr); c.csr_reg_pmp_6_cfg_a = s.pmp[6].cfg_a;
    c.csr_reg_pmp_6_cfg_l = s.pmp[6].cfg_l; c.csr_reg_pmp_6_cfg_r = s.pmp[6].cfg_r;
    c.csr_reg_pmp_6_cfg_w = s.pmp[6].cfg_w; c.csr_reg_pmp_6_cfg_x = s.pmp[6].cfg_x;
    c.csr_reg_pmp_7_addr = static_cast<uint32_t>(s.pmp[7].addr); c.csr_reg_pmp_7_cfg_a = s.pmp[7].cfg_a;
    c.csr_reg_pmp_7_cfg_l = s.pmp[7].cfg_l; c.csr_reg_pmp_7_cfg_r = s.pmp[7].cfg_r;
    c.csr_reg_pmp_7_cfg_w = s.pmp[7].cfg_w; c.csr_reg_pmp_7_cfg_x = s.pmp[7].cfg_x;
    pmp_export_dirty_ = false;
  }
  c.csr_reg_fflags = s.fflags;
  c.csr_reg_wfi = s.wfi;
  c.csr_value_hi = s.value_hi;
  c.csr_value_hi_1 = s.value_hi_1;
  c.csr_value_lo = s.value_lo;
  c.csr_value_lo_1 = s.mcycle_small;
  c.div_neg_out = div_.neg_out;
  c.div_resHi = div_.resHi;
  c.div_state = div_.state;
  c.ex_ctrl_alu_dw = ex_.ctrl.alu_dw;
  c.ex_ctrl_alu_fn = ex_.ctrl.alu_fn;
  c.ex_ctrl_csr = ex_.ctrl.csr;
  c.ex_ctrl_div = ex_.ctrl.div;
  c.ex_ctrl_fp = ex_.ctrl.fp;
  c.ex_ctrl_jalr = ex_.ctrl.jalr;
  c.ex_ctrl_mem = ex_.ctrl.mem;
  c.ex_ctrl_mem_cmd = ex_.ctrl.mem_cmd;
  c.ex_ctrl_sel_alu1 = ex_.ctrl.sel_alu1;
  c.ex_ctrl_sel_alu2 = ex_.ctrl.sel_alu2;
  c.ex_ctrl_sel_imm = ex_.ctrl.sel_imm;
  c.ex_ctrl_wfd = ex_.ctrl.wfd;
  c.ex_ctrl_wxd = ex_.ctrl.wxd;
  c.ex_reg_inst = ex_.inst;
  c.ex_reg_pc = ex_.pc;
  c.ex_reg_replay = ex_.replay;
  c.ex_reg_rs_bypass_0 = ex_.rs_bypass[0];
  c.ex_reg_rs_bypass_1 = ex_.rs_bypass[1];
  c.ex_reg_rs_lsb_0 = ex_.rs_lsb[0];
  c.ex_reg_rs_lsb_1 = ex_.rs_lsb[1];
  c.ex_reg_rs_msb_0 = ex_.rs_msb[0];
  c.ex_reg_rs_msb_1 = ex_.rs_msb[1];
  c.ex_reg_rvc = ex_.rvc;
  c.ex_reg_valid = ex_.valid;
  c.ex_reg_xcpt_interrupt = ex_.xcpt_interrupt;
  c.ibuf_buf_data = static_cast<uint32_t>(ibuf_.buf_data);
  c.ibuf_buf_pc = ibuf_.buf_pc;
  c.ibuf_buf_replay = ibuf_.buf_replay;
  c.ibuf_nBufValid = ibuf_.nBufValid;
  c.id_reg_fence = id_reg_fence_;
  c.id_reg_pause = id_reg_pause_;
  c.id_stall_fpu_r = fp_sboard_;
  c.mem_ctrl_branch = mem_.ctrl.branch;
  c.mem_ctrl_csr = mem_.ctrl.csr;
  c.mem_ctrl_div = mem_.ctrl.div;
  c.mem_ctrl_fp = mem_.ctrl.fp;
  c.mem_ctrl_jal = mem_.ctrl.jal;
  c.mem_ctrl_mem = mem_.ctrl.mem;
  c.mem_ctrl_wfd = mem_.ctrl.wfd;
  c.mem_ctrl_wxd = mem_.ctrl.wxd;
  c.mem_reg_flush_pipe = mem_.flush_pipe;
  c.mem_reg_inst = mem_.inst;
  c.mem_reg_replay = mem_.replay;
  c.mem_reg_sfence = mem_.sfence;
  c.mem_reg_slow_bypass = mem_.slow_bypass;
  c.mem_reg_valid = mem_.valid;
  c.mem_reg_wdata = mem_.wdata;
  c.mem_reg_xcpt = mem_.xcpt;
  c.mem_reg_xcpt_interrupt = mem_.xcpt_interrupt;
  c.wb_ctrl_mem = wb_.ctrl.mem;
  c.wb_reg_flush_pipe = wb_.flush_pipe;
  c.wb_reg_inst = wb_.inst;
  c.wb_reg_replay = wb_.replay;
  c.wb_reg_valid = wb_.valid;
  c.wb_reg_wdata = wb_.wdata;
  c.wb_reg_xcpt = wb_.xcpt;
}

}  // namespace chisa::rocket_model
