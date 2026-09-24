#include "csr_logic.h"

// State transitions shared from the current Small implementation.
// Pipeline timing and publication remain with each core.
namespace chisa::boom_model::csr_logic {
namespace {
constexpr uint8_t CSR_W = 5, CSR_S = 6, CSR_C = 7;
constexpr uint64_t kInterruptBit = UINT64_C(1) << 63;
constexpr uint64_t kDebugInterruptCause = kInterruptBit | UINT64_C(14);
constexpr uint64_t kDebugTriggerCause = UINT64_C(14);
constexpr uint64_t kDebugEntry = UINT64_C(0x800);
constexpr uint64_t kDebugException = UINT64_C(0x808);
constexpr uint32_t kEcall = UINT32_C(0x00000073);
constexpr uint32_t kEbreak = UINT32_C(0x00100073);
constexpr uint32_t kSret = UINT32_C(0x10200073);
constexpr uint32_t kMret = UINT32_C(0x30200073);
constexpr uint32_t kDret = UINT32_C(0x7b200073);
constexpr uint32_t kCease = UINT32_C(0x30500073);
constexpr uint64_t kVaddr40Mask = (UINT64_C(1) << 40) - 1;
constexpr uint64_t kStvec39Mask = (UINT64_C(1) << 39) - 1;
constexpr uint64_t kSatpPpnMask = (UINT64_C(1) << 20) - 1;
constexpr uint64_t kPmpAddrMask = (UINT64_C(1) << 30) - 1;
constexpr uint64_t kSupervisorInterruptMask = UINT64_C(0x222);
constexpr uint64_t kSupportedInterruptMask = UINT64_C(0xaaa);
constexpr uint64_t kDelegableExceptionMask = UINT64_C(0xb15d);

uint64_t packed_pmpcfg0(const GuiderCSR& csr) {
  uint64_t value = 0;
  for (unsigned i = 0; i < 8; ++i) {
    const auto& p = csr.pmp[i];
    const uint8_t cfg = static_cast<uint8_t>((uint8_t(p.cfg_l) << 7) | ((p.cfg_a & 3u) << 3) |
                                             (uint8_t(p.cfg_x) << 2) | (uint8_t(p.cfg_w) << 1) | uint8_t(p.cfg_r));
    value |= uint64_t(cfg) << (8 * i);
  }
  return value;
}
uint64_t writable_mip(const GuiderCSR& csr) {
  return (uint64_t(csr.mip_seip) << 9) | (uint64_t(csr.mip_stip) << 5) | (uint64_t(csr.mip_ssip) << 1);
}
bool delegates_to_supervisor(const GuiderCSR& csr, uint64_t cause) {
  if (csr.prv > 1 || (cause & ~kInterruptBit) >= 64) return false;
  const unsigned index = static_cast<unsigned>(cause & ~kInterruptBit);
  const uint64_t mask = (cause & kInterruptBit) ? (csr.mideleg & kSupervisorInterruptMask)
                                                : (csr.medeleg & kDelegableExceptionMask);
  return ((mask >> index) & 1u) != 0;
}
}  // namespace

uint64_t read(const GuiderCSR& csr, uint64_t retired, uint32_t addr, unsigned lookahead) {
  constexpr unsigned counter_mask=(1u<<(boomcfg::NUM_HPM+3))-1;
  if (addr>=0x323 && addr<0x323+boomcfg::NUM_HPM) return csr.hpmevent[addr-0x323];
  if ((addr>>8==0xB || addr>>8==0xC) && (addr&0xff)>=3 && (addr&0xff)<3+boomcfg::NUM_HPM)
    return csr.hpmcounter[(addr&0xff)-3]&((UINT64_C(1)<<40)-1);
  switch (addr) {
    case 0xB00: case 0xC00: {
      const bool counter_runs = !csr.wfi && !csr.cease && (csr.mcountinhibit & 1u) == 0;
      return csr.mcycle + (counter_runs ? lookahead : 0);
    }
    case 0x300: {
      uint64_t value = csr.mstatus | (UINT64_C(2) << 34);
      if (((csr.mstatus >> 13) & 3u) == 3u) value |= UINT64_C(1) << 63;
      return value;
    }
    case 0x301: return csr.misa;
    case 0x302: return csr.medeleg & kDelegableExceptionMask;
    case 0x303: return csr.mideleg & kSupervisorInterruptMask;
    case 0x304: return csr.mie;
    case 0x305: return csr.mtvec;
    case 0x306: return csr.mcounteren & counter_mask;
    case 0x320: return csr.mcountinhibit & (counter_mask&~2u);
    case 0x340: return csr.mscratch;
    case 0x341: return csr.mepc;
    case 0x342: return csr.mcause;
    case 0x343: return csr.mtval;
    case 0x344: return (csr.mip & ~kSupervisorInterruptMask) | writable_mip(csr);
    case 0x100: {
      constexpr uint64_t visible = (UINT64_C(1) << 1) | (UINT64_C(1) << 5) | (UINT64_C(1) << 8) |
                                   (UINT64_C(3) << 13) | (UINT64_C(1) << 18) | (UINT64_C(1) << 19) |
                                   (UINT64_C(3) << 32);
      uint64_t value = csr.mstatus & visible;
      if (((csr.mstatus >> 13) & 3u) == 3u) value |= UINT64_C(1) << 63;
      return value;
    }
    case 0x104: return csr.mie & csr.mideleg & kSupervisorInterruptMask;
    case 0x105: return csr.stvec & ~UINT64_C(2);
    case 0x106: return csr.scounteren & counter_mask;
    case 0x140: return csr.sscratch;
    case 0x141: return csr.sepc & ~UINT64_C(1);
    case 0x142: return csr.scause;
    case 0x143: return csr.stval;
    case 0x144: return read(csr, retired, 0x344, lookahead) & csr.mideleg & kSupervisorInterruptMask;
    case 0x180: return (uint64_t(csr.satp_mode & 0xfu) << 60) | (csr.satp_ppn & ((UINT64_C(1) << 44) - 1));
    case 0x3A0: return packed_pmpcfg0(csr);
    case 0x3B0: case 0x3B1: case 0x3B2: case 0x3B3:
    case 0x3B4: case 0x3B5: case 0x3B6: case 0x3B7:
      return csr.pmp[addr - 0x3B0].addr & kPmpAddrMask;
    case 0x7C1: return csr.custom_0;
    case 0x7B0: return csr.dcsr;
    case 0x7B1: return csr.dpc;
    case 0x7B2: return csr.dscratch;
    case 0x001: return csr.fcsr & 0x1F;
    case 0x002: return (csr.fcsr >> 5) & 0x7;
    case 0x003: return csr.fcsr;
    case 0xB02: case 0xC02: return retired;
    default: return 0;
  }
}

bool trap_to_debug(const GuiderCSR& csr, uint64_t cause, uint32_t inst) {
  if (csr.debug) return true;
  if (csr.single_stepped) return true;
  if (cause == kDebugInterruptCause || cause == kDebugTriggerCause) return true;
  if (inst != kEbreak) return false;
  const unsigned ebreak_bit = csr.prv == 3 ? 15 : csr.prv == 1 ? 13 : 12;
  return ((csr.dcsr >> ebreak_bit) & 1u) != 0;
}

uint64_t trap_target(const GuiderCSR& csr, uint64_t cause, uint32_t inst) {
  if (trap_to_debug(csr, cause, inst)) return (csr.debug && inst != kEbreak) ? kDebugException : kDebugEntry;
  const uint64_t tvec = delegates_to_supervisor(csr, cause) ? csr.stvec : csr.mtvec;
  const uint64_t base = tvec & ~UINT64_C(3);
  const bool vectored_interrupt = (tvec & 3u) == 1u && (cause & kInterruptBit) != 0;
  return vectored_interrupt ? base + UINT64_C(4) * (cause & ~kInterruptBit) : base;
}

uint64_t take_trap(GuiderCSR& csr, uint64_t epc, uint64_t cause, uint32_t inst) {
  const uint64_t target = trap_target(csr, cause, inst);
  if (trap_to_debug(csr, cause, inst)) {
    if (!csr.debug) {
      csr.debug = true;
      csr.dpc = epc & ~UINT64_C(1);
      const uint64_t debug_cause = csr.single_stepped ? 4u : cause == kDebugInterruptCause ? 3u
                                 : cause == kDebugTriggerCause ? 2u : 1u;
      csr.dcsr = (csr.dcsr & ~((UINT64_C(7) << 6) | UINT64_C(3))) | (debug_cause << 6) | (csr.prv & 3u);
      csr.prv = 3;
    }
    csr.wfi = false;
    return target;
  }
  if (delegates_to_supervisor(csr, cause)) {
    csr.sepc = epc & kVaddr40Mask & ~UINT64_C(1);
    csr.scause = cause;
    csr.stval = cause == 2 ? (uint64_t(inst) & kVaddr40Mask) : 0;
    const uint64_t sie = (csr.mstatus >> 1) & 1u;
    csr.mstatus = (csr.mstatus & ~((UINT64_C(1) << 5) | (UINT64_C(1) << 1) | (UINT64_C(1) << 8))) |
                  (sie << 5) | (uint64_t(csr.prv & 1u) << 8);
    csr.prv = 1;
    csr.wfi = false;
    return target;
  }
  csr.mepc = epc & kVaddr40Mask & ~UINT64_C(1);
  csr.mcause = cause;
  csr.mtval = cause == 2 ? (uint64_t(inst) & kVaddr40Mask) : 0;
  const uint64_t mie = (csr.mstatus >> 3) & 1u;
  csr.mstatus = (csr.mstatus & ~((UINT64_C(1) << 7) | (UINT64_C(1) << 3) | (UINT64_C(3) << 11))) |
                (mie << 7) | (uint64_t(csr.prv & 3u) << 11);
  csr.prv = 3;
  csr.wfi = false;
  return target;
}

static bool execute_state(Context context, const MicroOp& u, uint8_t op, uint64_t rs1_val) {
  GuiderCSR& csr = context.state;
  if (u.inst == kCease) { csr.cease = true; return true; }
  if (u.uopc == uopWFI) { csr.wfi = !context.wakeup; return true; }
  if (u.uopc == uopERET) {
    switch (u.inst) {
      case kEcall: {
        const uint64_t cause = UINT64_C(8) + (csr.prv & 3u);
        context.flush_target = trap_target(csr, cause, u.inst);
        take_trap(csr, u.debug_pc, cause, u.inst);
        break;
      }
      case kEbreak: {
        constexpr uint64_t cause = 3;
        context.flush_target = trap_target(csr, cause, u.inst);
        take_trap(csr, u.debug_pc, cause, u.inst);
        break;
      }
      case kMret: {
        const uint8_t return_prv = static_cast<uint8_t>((csr.mstatus >> 11) & 3u);
        const uint64_t mpie = (csr.mstatus >> 7) & 1u;
        csr.mstatus &= ~((UINT64_C(1) << 3) | (UINT64_C(1) << 7) | (UINT64_C(3) << 11));
        csr.mstatus |= (mpie << 3) | (UINT64_C(1) << 7);
        if (return_prv < 3) csr.mstatus &= ~(UINT64_C(1) << 17);
        csr.prv = return_prv;
        context.flush_target = csr.mepc & ~UINT64_C(1);
        break;
      }
      case kDret:
        csr.prv = static_cast<uint8_t>(csr.dcsr & 3u);
        csr.debug = false;
        context.flush_target = csr.dpc & ~UINT64_C(1);
        break;
      case kSret: {
        const uint8_t return_prv = static_cast<uint8_t>((csr.mstatus >> 8) & 1u);
        const uint64_t spie = (csr.mstatus >> 5) & 1u;
        csr.mstatus &= ~((UINT64_C(1) << 1) | (UINT64_C(1) << 5) | (UINT64_C(1) << 8));
        csr.mstatus |= (spie << 1) | (UINT64_C(1) << 5);
        if (return_prv < 3) csr.mstatus &= ~(UINT64_C(1) << 17);
        csr.prv = return_prv;
        context.flush_target = csr.sepc & ~UINT64_C(1);
        break;
      }
      default: break;
    }
    return true;
  }
  if (op != CSR_W && op != CSR_S && op != CSR_C) return false;
  const uint32_t addr = u.csr_addr;
  const bool imm_form = ((u.inst >> 12) & 0x4) != 0;
  const uint64_t src = imm_form ? ((u.inst >> 15) & 0x1F) : rs1_val;
  const uint64_t old = (context.read_override ? context.read_value : read(csr, context.retired, addr, context.lookahead));
  const uint64_t nv = (op == CSR_W) ? src : (op == CSR_S) ? (old | src) : (old & ~src);
  if (addr>=0x323 && addr<0x323+boomcfg::NUM_HPM) csr.hpmevent[addr-0x323]=nv&UINT64_C(0x3f03);
  if (addr>=0xB03 && addr<0xB03+boomcfg::NUM_HPM) csr.hpmcounter[addr-0xB03]=nv&((UINT64_C(1)<<40)-1);
  switch (addr) {
    case 0x300: {
      const uint64_t W = (1ULL << 1) | (1ULL << 3) | (1ULL << 5) | (1ULL << 7) | (1ULL << 8) | (3ULL << 11) |
                         (3ULL << 13) | (1ULL << 17) | (1ULL << 18) | (1ULL << 19) | (1ULL << 20) | (1ULL << 21) |
                         (1ULL << 22);
      csr.mstatus = (csr.mstatus & ~W) | (nv & W);
      break;
    }
    case 0x301: csr.misa = nv; break;
    case 0x302: csr.medeleg = nv; break;
    case 0x303: csr.mideleg = nv; break;
    case 0x304: csr.mie = nv & kSupportedInterruptMask; break;
    case 0x305: csr.mtvec = nv & UINT64_C(0xffffffff); break;
    case 0x306: csr.mcounteren = static_cast<uint32_t>(nv); break;
    case 0x320: csr.mcountinhibit = nv & (((1u<<(boomcfg::NUM_HPM+3))-1)&~2u); break;
    case 0x340: csr.mscratch = nv; break;
    case 0x341: csr.mepc = nv & kVaddr40Mask & ~1ULL; break;
    case 0x342: csr.mcause = nv; break;
    case 0x343: csr.mtval = nv & kVaddr40Mask; break;
    case 0x344:
      csr.mip_ssip = ((nv >> 1) & 1u) != 0;
      csr.mip_stip = ((nv >> 5) & 1u) != 0;
      csr.mip_seip = ((nv >> 9) & 1u) != 0;
      csr.mip = (csr.mip & ~kSupervisorInterruptMask) | writable_mip(csr);
      break;
    case 0x100: {
      constexpr uint64_t W = (UINT64_C(1) << 1) | (UINT64_C(1) << 5) | (UINT64_C(1) << 8) | (UINT64_C(3) << 13) |
                             (UINT64_C(1) << 18) | (UINT64_C(1) << 19);
      csr.mstatus = (csr.mstatus & ~W) | (nv & W);
      break;
    }
    case 0x104:
      csr.mie = (csr.mie & ~(csr.mideleg & kSupervisorInterruptMask)) | (nv & csr.mideleg & kSupervisorInterruptMask);
      break;
    case 0x105: csr.stvec = nv & kStvec39Mask; break;
    case 0x106: csr.scounteren = static_cast<uint32_t>(nv); break;
    case 0x140: csr.sscratch = nv; break;
    case 0x141: csr.sepc = nv & kVaddr40Mask & ~UINT64_C(1); break;
    case 0x142: csr.scause = nv & (kInterruptBit | UINT64_C(31)); break;
    case 0x143: csr.stval = nv & kVaddr40Mask; break;
    case 0x144: {
      const uint64_t delegated = csr.mideleg & kSupervisorInterruptMask;
      const uint64_t new_mip = (read(csr, context.retired, 0x344, context.lookahead) & ~delegated) | (nv & delegated);
      csr.mip_ssip = ((new_mip >> 1) & 1u) != 0;
      break;
    }
    case 0x180: {
      const uint8_t mode = static_cast<uint8_t>((nv >> 60) & 0xfu);
      if (mode == 0 || mode == 8) { csr.satp_mode = mode; csr.satp_ppn = nv & kSatpPpnMask; }
      break;
    }
    case 0xB00: csr.mcycle = nv; break;
    case 0xB02: context.retired = nv; context.retired_register = nv; break;
    case 0x3A0:
      for (unsigned i = 0; i < 8; ++i) {
        auto& p = csr.pmp[i];
        if (p.cfg_l) continue;
        const uint8_t cfg = static_cast<uint8_t>(nv >> (8 * i));
        p.cfg_l = ((cfg >> 7) & 1u) != 0;
        p.cfg_a = (cfg >> 3) & 3u;
        p.cfg_x = ((cfg >> 2) & 1u) != 0;
        p.cfg_r = (cfg & 1u) != 0;
        p.cfg_w = ((cfg >> 1) & 1u) != 0 && p.cfg_r;
      }
      break;
    case 0x3B0: case 0x3B1: case 0x3B2: case 0x3B3:
    case 0x3B4: case 0x3B5: case 0x3B6: case 0x3B7: {
      const unsigned i = addr - 0x3B0;
      const bool next_tor_locked = i + 1 < 8 && csr.pmp[i + 1].cfg_l && csr.pmp[i + 1].cfg_a == 1;
      if (!csr.pmp[i].cfg_l && !next_tor_locked) csr.pmp[i].addr = static_cast<uint32_t>(nv & kPmpAddrMask);
      break;
    }
    case 0x7C1: csr.custom_0 = (csr.custom_0 & ~UINT64_C(8)) | (nv & 8u); break;
    case 0x7B0: {
      constexpr uint64_t W = (UINT64_C(1) << 15) | (UINT64_C(1) << 13) | (UINT64_C(1) << 12) | (UINT64_C(1) << 2) | UINT64_C(3);
      csr.dcsr = (csr.dcsr & ~W) | (nv & W);
      break;
    }
    case 0x7B1: csr.dpc = nv & ~UINT64_C(1); break;
    case 0x7B2: csr.dscratch = nv; break;
    case 0x001: csr.fcsr = (csr.fcsr & ~0x1FULL) | (nv & 0x1F); break;
    case 0x002: csr.fcsr = (csr.fcsr & ~0xE0ULL) | ((nv & 0x7) << 5); break;
    case 0x003: csr.fcsr = nv & 0xFF; break;
    default: break;
  }
  return true;
}

void latch_hpm_events(GuiderCSR& csr, const HpmEventInputs& input) {
  for (unsigned i = 0; i < boomcfg::NUM_HPM; ++i) {
    const uint64_t selector = input.selector[i];
    const uint8_t set = static_cast<uint8_t>(selector & 3u);
    const uint8_t mask = static_cast<uint8_t>((selector >> 8) & 0x3fu);
    bool hit = false;
    switch (set) {
      case 0: hit = (mask & 1u) != 0 && input.exception; break;
      case 1: hit = (mask & 2u) != 0 && input.flush; break;
      default:
        hit = ((mask & UINT8_C(0x01)) && input.ifu_acquire) || ((mask & UINT8_C(0x02)) && input.lsu_acquire) ||
              ((mask & UINT8_C(0x04)) && input.lsu_release) || ((mask & UINT8_C(0x08)) && input.ifu_tlb_miss) ||
              ((mask & UINT8_C(0x10)) && input.lsu_tlb_miss) || ((mask & UINT8_C(0x20)) && input.ptw_l2_miss);
        break;
    }
    csr.hpm_inc_r[i] = hit;
  }
}

void decode_legality(MicroOp& u, const GuiderCSR& csr) {
  const bool fs_off = ((csr.mstatus >> 13) & 3u) == 0;
  const bool fp_csr = u.csr_addr >= 0x001 && u.csr_addr <= 0x003;
  if (!u.exception && fs_off && (u.fp_val || fp_csr)) { u.exception = 1; u.exc_cause = 2; }
  const uint32_t inst = u.inst;
  const bool system_insn = (inst & UINT32_C(0x0000707f)) == UINT32_C(0x00000073);
  const bool sfence = (inst & UINT32_C(0xfe007fff)) == UINT32_C(0x12000073);
  if (!u.exception && (system_insn || sfence)) {
    const uint16_t csr_addr = static_cast<uint16_t>((inst >> 20) & 0x0fffu);
    const uint8_t required_prv = static_cast<uint8_t>((csr_addr >> 8) & 3u);
    const bool is_wfi = inst == UINT32_C(0x10500073);
    const bool is_sret = inst == UINT32_C(0x10200073);
    const bool is_mret = inst == UINT32_C(0x30200073);
    const bool is_dret = inst == UINT32_C(0x7b200073);
    const bool is_ret = is_sret || is_mret || is_dret;
    const bool tw = ((csr.mstatus >> 21) & 1u) != 0;
    const bool tsr = ((csr.mstatus >> 22) & 1u) != 0;
    const bool tvm = ((csr.mstatus >> 20) & 1u) != 0;
    const bool allow_wfi = csr.prv > 1 || !tw;
    const bool allow_sret = csr.prv > 1 || !tsr;
    const bool allow_sfence = csr.prv > 1 || !tvm;
    const bool system_illegal = csr.prv < required_prv || (is_wfi && !allow_wfi) || (is_ret && !allow_sret) ||
                                (is_dret && !csr.debug) || (sfence && !allow_sfence);
    if (system_illegal) { u.exception = 1; u.exc_cause = 2; }
  }
}

Effects execute(Context context, const MicroOp& u, std::uint8_t command, std::uint64_t operand) {
  Effects result;
  result.changed = execute_state(context,u,command,operand);
  if (result.changed && command >= 5 && command <= 7 && u.uopc != uopERET && u.uopc != uopWFI) {
    result.cycle_written = u.csr_addr == 0xb00;
    result.retired_written = u.csr_addr == 0xb02;
    if (u.csr_addr>=0xb03 && u.csr_addr<0xb03+boomcfg::NUM_HPM)
      result.hpm_written=1u<<(u.csr_addr-0xb03);
  }
  return result;
}
}  // namespace chisa::boom_model::csr_logic
