// model core: CSR file (rocket CSRFile subset), traps, Debug Mode entry,
// and the contract image of the CSR registers (written when they change).
#include "core.h"
#include "../common/csr_logic.h"

namespace chisa::boom_model {

namespace {
constexpr uint64_t kVaddr40Mask = (UINT64_C(1) << 40) - 1;
constexpr uint64_t kStvec39Mask = (UINT64_C(1) << 39) - 1;
constexpr uint64_t kPmpAddrMask = (UINT64_C(1) << 30) - 1;
}  // namespace

uint64_t Core::compute_csr_rdata(uint32_t address) const {
  return csr_logic::read(csr_,minstret_count_,address,4);
}

void Core::exec_csr(const MicroOp& u, uint8_t command, uint64_t operand) {
  const auto effect = csr_logic::execute(
      {csr_,minstret_count_,minstret_csr_reg_,csr_flush_target_,wfi_wakeup,4},
      u,command,operand);
  if (effect.changed) csr_export();
}

void Core::latch_hpm_events(const HpmEventInputs& input) {
  csr_logic::latch_hpm_events(csr_,input);
}

bool Core::trap_to_debug(uint64_t cause, uint32_t instruction) const {
  return csr_logic::trap_to_debug(csr_,cause,instruction);
}

uint64_t Core::trap_target(uint64_t cause, uint32_t instruction) const {
  return csr_logic::trap_target(csr_,cause,instruction);
}

uint64_t Core::take_trap(uint64_t pc, uint64_t cause, uint32_t instruction) {
  const auto target = csr_logic::take_trap(csr_,pc,cause,instruction);
  csr_export();
  return target;
}

// Every CSR register field of the contract (called after a CSR write, a
// trap, a WFI/CEASE change or an FP flags accrual).
void Core::csr_export() {
  auto& C = img_->r.coreCsr;
  const GuiderCSR& c = csr_;
  C.reg_custom_0 = c.custom_0;
  C.reg_dpc = c.dpc & kVaddr40Mask;
  C.reg_dscratch = c.dscratch;
  C.reg_hpmevent[0] = c.hpmevent[0];
  C.reg_hpmevent[1] = c.hpmevent[1];
  C.reg_mcause = c.mcause;
  C.reg_medeleg = c.medeleg;
  C.reg_mepc = c.mepc & kVaddr40Mask;
  C.reg_mideleg = c.mideleg;
  C.reg_mie = c.mie;
  C.reg_mscratch = c.mscratch;
  C.reg_mtval = c.mtval & kVaddr40Mask;
  C.reg_satp_ppn = c.satp_ppn & ((UINT64_C(1) << 44) - 1);
  C.reg_scause = c.scause;
  C.reg_sepc = c.sepc & kVaddr40Mask;
  C.reg_sscratch = c.sscratch;
  C.reg_stval = c.stval & kVaddr40Mask;
  C.reg_stvec = c.stvec & kStvec39Mask;
  C.reg_mcounteren = c.mcounteren;
  C.reg_mtvec = static_cast<uint32_t>(c.mtvec & UINT64_C(0xffffffff));
  for (int i = 0; i < 8; ++i) {
    C.reg_pmp_addr[i] = c.pmp[i].addr & kPmpAddrMask;
    C.reg_pmp_cfg_a[i] = c.pmp[i].cfg_a & 3;
    C.reg_pmp_cfg_l[i] = bit(c.pmp[i].cfg_l);
    C.reg_pmp_cfg_r[i] = bit(c.pmp[i].cfg_r);
    C.reg_pmp_cfg_w[i] = bit(c.pmp[i].cfg_w);
    C.reg_pmp_cfg_x[i] = bit(c.pmp[i].cfg_x);
  }
  C.reg_scounteren = c.scounteren;
  C.io_status_cease_r = bit(c.cease);
  C.reg_dcsr_cause = (c.dcsr >> 6) & 7;
  C.reg_dcsr_ebreakm = (c.dcsr >> 15) & 1;
  C.reg_dcsr_ebreaks = (c.dcsr >> 13) & 1;
  C.reg_dcsr_ebreaku = (c.dcsr >> 12) & 1;
  C.reg_dcsr_prv = c.dcsr & 3;
  C.reg_dcsr_step = (c.dcsr >> 2) & 1;
  C.reg_debug = bit(c.debug);
  C.reg_fflags = c.fcsr & 0x1f;
  C.reg_frm = (c.fcsr >> 5) & 7;
  C.reg_mcountinhibit = c.mcountinhibit & 0x1f;
  C.reg_mip_seip = bit(c.mip_seip);
  C.reg_mip_ssip = bit(c.mip_ssip);
  C.reg_mip_stip = bit(c.mip_stip);
  C.reg_mstatus_fs = (c.mstatus >> 13) & 3;
  C.reg_mstatus_mie = (c.mstatus >> 3) & 1;
  C.reg_mstatus_mpie = (c.mstatus >> 7) & 1;
  C.reg_mstatus_mpp = (c.mstatus >> 11) & 3;
  C.reg_mstatus_mprv = (c.mstatus >> 17) & 1;
  C.reg_mstatus_mxr = (c.mstatus >> 19) & 1;
  C.reg_mstatus_prv = c.prv & 3;
  C.reg_mstatus_sie = (c.mstatus >> 1) & 1;
  C.reg_mstatus_spie = (c.mstatus >> 5) & 1;
  C.reg_mstatus_spp = (c.mstatus >> 8) & 1;
  C.reg_mstatus_sum = (c.mstatus >> 18) & 1;
  C.reg_mstatus_tsr = (c.mstatus >> 22) & 1;
  C.reg_mstatus_tvm = (c.mstatus >> 20) & 1;
  C.reg_mstatus_tw = (c.mstatus >> 21) & 1;
  C.reg_satp_mode = c.satp_mode & 0xf;
  C.reg_singleStepped = bit(c.single_stepped);
  C.reg_wfi = bit(c.wfi);
  csr_export_counters();
}

// The free-running counters: value_hi/lo pairs of instret, cycle, hpm0, hpm1.
void Core::csr_export_counters() {
  auto& C = img_->r.coreCsr;
  const GuiderCSR& c = csr_;
  C.value_lo[0] = minstret_csr_reg_ & 0x3f;
  C.value_hi[0] = (minstret_csr_reg_ >> 6) & ((UINT64_C(1) << 58) - 1);
  C.value_lo[1] = c.mcycle & 0x3f;
  C.value_hi[1] = (c.mcycle >> 6) & ((UINT64_C(1) << 58) - 1);
  C.value_lo[2] = c.hpmcounter[0] & 0x3f;
  C.value_hi[2] = (c.hpmcounter[0] >> 6) & ((UINT64_C(1) << 34) - 1);
  C.value_lo[3] = c.hpmcounter[1] & 0x3f;
  C.value_hi[3] = (c.hpmcounter[1] >> 6) & ((UINT64_C(1) << 34) - 1);
}

}  // namespace chisa::boom_model
