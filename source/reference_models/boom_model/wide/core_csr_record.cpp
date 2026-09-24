#include "core.h"
namespace chisa::boom_model::wide {
void Core::write_csr_record() {
  auto& r=record_->r.coreCsr;const auto& c=state_.csr;
  constexpr auto pc=(UINT64_C(1)<<40)-1;
  r.reg_custom_0=c.custom_0;r.reg_dpc=c.dpc&pc;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  r.reg_dscratch=c.dscratch;
#else
  r.reg_dcsr_cause=(c.dcsr>>6)&7u;
  for (unsigned i=0;i<boomcfg::NUM_HPM;++i) r.reg_hpmevent[i]=c.hpmevent[i];
#endif
  r.reg_mcause=c.mcause;r.reg_medeleg=c.medeleg;r.reg_mepc=c.mepc&pc;r.reg_mideleg=c.mideleg;
  r.reg_mie=c.mie;r.reg_mscratch=c.mscratch;r.reg_mtval=c.mtval&pc;
  r.reg_satp_ppn=c.satp_ppn&((UINT64_C(1)<<44)-1);r.reg_satp_mode=c.satp_mode&15;
  r.reg_scause=c.scause;r.reg_sepc=c.sepc&pc;r.reg_sscratch=c.sscratch;r.reg_stval=c.stval&pc;
  r.reg_stvec=c.stvec&((UINT64_C(1)<<39)-1);r.reg_mtvec=c.mtvec&UINT32_MAX;
  r.reg_mcounteren=c.mcounteren;r.reg_scounteren=c.scounteren;
  for(unsigned i=0;i<8;++i) {
    r.reg_pmp_addr[i]=c.pmp[i].addr&0x3fffffffu;r.reg_pmp_cfg_a[i]=c.pmp[i].cfg_a&3;
    r.reg_pmp_cfg_l[i]=c.pmp[i].cfg_l;r.reg_pmp_cfg_r[i]=c.pmp[i].cfg_r;
    r.reg_pmp_cfg_w[i]=c.pmp[i].cfg_w;r.reg_pmp_cfg_x[i]=c.pmp[i].cfg_x;
  }
  r.io_status_cease_r=c.cease;r.reg_wfi=c.wfi;r.reg_debug=c.debug;
  r.reg_dcsr_ebreakm=(c.dcsr>>15)&1;r.reg_dcsr_ebreaks=(c.dcsr>>13)&1;r.reg_dcsr_ebreaku=(c.dcsr>>12)&1;
  r.reg_dcsr_prv=c.dcsr&3;r.reg_dcsr_step=(c.dcsr>>2)&1;
  r.reg_fflags=c.fcsr&31;r.reg_frm=(c.fcsr>>5)&7;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  r.reg_mcountinhibit=c.mcountinhibit&0x1ff;
#else
  r.reg_mcountinhibit=c.mcountinhibit&7;
#endif
  r.reg_mip_ssip=c.mip_ssip;r.reg_mip_stip=c.mip_stip;
  r.reg_mstatus_fs=(c.mstatus>>13)&3;r.reg_mstatus_mie=(c.mstatus>>3)&1;
  r.reg_mstatus_mpie=(c.mstatus>>7)&1;r.reg_mstatus_mpp=(c.mstatus>>11)&3;
  r.reg_mstatus_mprv=(c.mstatus>>17)&1;r.reg_mstatus_mxr=(c.mstatus>>19)&1;r.reg_mstatus_prv=c.prv&3;
  r.reg_mstatus_sie=(c.mstatus>>1)&1;r.reg_mstatus_spie=(c.mstatus>>5)&1;r.reg_mstatus_spp=(c.mstatus>>8)&1;
  r.reg_mstatus_sum=(c.mstatus>>18)&1;r.reg_mstatus_tsr=(c.mstatus>>22)&1;
  r.reg_mstatus_tvm=(c.mstatus>>20)&1;r.reg_mstatus_tw=(c.mstatus>>21)&1;
}
void Core::write_core_control() {
  const auto& out=output_;auto& r=record_->r.coreMisc;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  r.REG_9=r.REG_17=r.REG_29=r.REG_36=r.REG_37=r.REG_39=r.REG_40=out.rob_flush;
  r.int_issue_unit_io_flush_pipeline_REG=r.mem_issue_unit_io_flush_pipeline_REG=out.rob_flush;
  r.REG_25=state_.memory.issued_load;r.saturating_loads_counter=state_.memory.load_issue_count;
  r.REG_26=0x3ffu&~((out.integer[0].selected && (out.integer[0].uop.fu_code&FU_DIV)) ? FU_DIV : 0u);
  r.REG_27=0x3ffu&~((out.integer[1].selected && (out.integer[1].uop.fu_code&FU_DIV)) ? FU_DIV : 0u);
  r.dec_brmask_logic_branch_mask=state_.rename.branches;
#else
  r.REG_4=r.REG_12=r.REG_24=r.REG_31=r.REG_32=r.REG_34=r.REG_35=out.rob_flush;
  r.int_issue_unit_io_flush_pipeline_REG=r.mem_issue_unit_io_flush_pipeline_REG=out.rob_flush;
  r.REG_26=out.exception;r.REG_5=out.flush_type;
  r.REG_20=state_.memory.issued_load;r.saturating_loads_counter=state_.memory.load_issue_count;
  r.REG_21=0x3ffu&~((out.integer[0].selected && (out.integer[0].uop.fu_code&FU_DIV)) ? FU_DIV : 0u);
  r.REG_22=0x3ffu&~((out.integer[2].selected && (out.integer[2].uop.fu_code&FU_DIV)) ? FU_DIV : 0u);
  r.dec_brmask_logic_branch_mask=state_.rename.branches;r.dec_finished_mask=state_.decode_finished;
#endif
  auto& c=record_->r.coreCsr;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  c.value_lo[0]=state_.csr.minstret&63;c.value_hi[0]=state_.csr.minstret>>6;
  c.value_lo[1]=state_.csr.mcycle&63;c.value_hi[1]=state_.csr.mcycle>>6;
  for (unsigned i=0;i<boomcfg::NUM_HPM;++i) {
    c.value_lo[i+2]=state_.csr.hpmcounter[i]&63;c.value_hi[i+2]=state_.csr.hpmcounter[i]>>6;
  }
#else
  c.value_lo=state_.csr.minstret&63;c.value_hi=state_.csr.minstret>>6;
  c.value_lo_1=state_.csr.mcycle&63;c.value_hi_1=state_.csr.mcycle>>6;
#endif
}
}  // namespace chisa::boom_model::wide
