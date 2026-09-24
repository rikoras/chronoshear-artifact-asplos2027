#include "core.h"
#include "record_fields.h"

namespace chisa::boom_model::wide {
void Core::export_oracles() {
  // SystemGuider calls this after its HPM latch. All selected core fields
  // already belong to their module's reset/transition/read-port operation;
  // the HPM selectors/counters are not selected by this contract.
}

void Core::finish_step_record() {
  if (record_deferred_) { step_batch_pending_ = true; return; }
  write_rename_valids(); write_lsq_control(); write_fp_record(); write_rob_ports(); write_core_control();
  write_cut_step_lanes();
}

std::uint64_t Core::oldest_exception_cause(bool& any) const {
  // rob.scala r_xcpt_uop.exc_cause: the oldest valid exception's cause.
  const auto& r=state_.rob;unsigned oldest=kRobEntries;std::uint64_t cause=0;
  for (unsigned b=0;b<kWidth;++b) {
    const auto mask=r.valid[b]&r.exception[b];
    if (!mask) continue;
    const auto rotated=(mask>>r.head)|(r.head ? mask<<(kRows-r.head) : 0);
    const unsigned age=__builtin_ctz(rotated)*kWidth+b;
    if (age<oldest) { oldest=age;cause=r.exception_cause[((r.head+age/kWidth)%kRows)*kWidth+b]; }
  }
  any=oldest!=kRobEntries;return cause;
}

void Core::write_cut_step_lanes() {
  if (!cut_lanes_) return;
  const auto& c=state_.csr;
  // CSR.scala: io.status.dprv is RegNext(Mux(mprv && !debug, mpp, prv)).
  write_record(*record_,fields::csr_dprv_r,dprv_prev_);
  dprv_prev_=static_cast<std::uint8_t>(((c.mstatus>>17)&1u) && !c.debug ? (c.mstatus>>11)&3u : c.prv);
  write_record(*record_,fields::csr_mip_seip,c.mip_seip);
  write_record(*record_,fields::csr_single_stepped,c.single_stepped);
  write_record(*record_,fields::iq_poison[0][0],state_.integer_issue.poison1[0]);
  write_record(*record_,fields::iq_poison[0][1],state_.integer_issue.poison2[0]);
  write_record(*record_,fields::iq_poison[1][0],state_.memory_issue.poison1[0]);
  write_record(*record_,fields::iq_poison[1][1],state_.memory_issue.poison2[0]);
  write_record(*record_,fields::lsu_p2_block_load_mask_0,state_.memory.block2&1u);   // lsu.scala p2_block_load_mask(0)
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  // core.scala:1012 csr.io.cause = RegNext(rob.io.com_xcpt.bits.cause): the
  // ROB's exception-cause register one cycle late.
  write_record(*record_,fields::core_com_xcpt_cause_r,exc_cause_hold_);
  {
    // CSR.scala:684-721 and 808-832: io.evec is the trap vector for the
    // cycle's cause (an ecall/ebreak in the CSR unit overrides it), the
    // debug entry in debug mode, or the return address of an xRET being
    // executed. core.scala:406 keeps RegNext(RegNext(io.evec)).
    const std::uint64_t cause_in=exc_cause_hold_;
    const bool insn_call=sys_insn_now_ && sys_insn_addr_==0, insn_break=sys_insn_now_ && sys_insn_addr_==1;
    const bool insn_ret=sys_insn_now_ && (sys_insn_addr_==0x102 || sys_insn_addr_==0x302 || sys_insn_addr_==0x7b2 || sys_insn_addr_==0x702);
    const std::uint64_t cause=insn_call ? std::uint64_t(c.prv)+8u : insn_break ? 3u : cause_in;
    const unsigned lsbs=static_cast<unsigned>(cause&0xffu);const bool interrupt=((cause>>63)&1u)!=0;
    const bool debug_break=!interrupt && insn_break && (((c.dcsr>>(c.prv==3 ? 15 : c.prv==1 ? 13 : 12))&1u)!=0);
    const bool trap_debug=c.single_stepped || lsbs==14 || debug_break || c.debug;
    std::uint64_t evec;
    if (insn_ret) {
      const bool sret=!((sys_insn_addr_>>9)&1u), dret=((sys_insn_addr_>>10)&1u) && ((sys_insn_addr_>>7)&1u);
      const std::uint64_t epc=sret ? c.sepc : dret ? c.dpc : c.mepc;
      evec=epc & ~(((c.misa>>2)&1u) ? UINT64_C(1) : UINT64_C(3));
    } else if (trap_debug) {
      evec=c.debug ? (insn_break ? 0x800u : 0x808u) : 0x800u;
    } else {
      const bool delegate=c.prv<=1 && ((((interrupt ? c.mideleg : c.medeleg)>>lsbs)&1u)!=0);
      const auto form=[](std::uint64_t x) { return x & ~((x&1u) ? UINT64_C(0xfe) : UINT64_C(2)); };
      std::uint64_t base=delegate ? form(c.stvec) : form(c.mtvec);
      if (delegate && ((base>>39)&1u)) base |= ~((UINT64_C(1)<<40)-1);
      const bool do_vector=(base&1u) && interrupt && (lsbs>>6)==0;
      evec=do_vector ? (((base>>8)<<8) | ((cause&0x3fu)<<2)) : ((base>>2)<<2);
    }
    write_record(*record_,fields::core_evec_rr,evec_r1_);
    evec_r1_=evec;
  }
  bool any=false;const auto cause=oldest_exception_cause(any);
  if (any) exc_cause_hold_=cause;
  // core.scala:383: RegNext(dec_valids && is_jalr && status.debug) per lane.
  for (unsigned i=1;i<kWidth && i<4;++i)
    write_record(*record_,fields::core_dec_jalr_debug[i],c.debug && state_.rename.valid[i] && state_.rename.held[i].is_jalr);
  // lsu.scala:979/1004: RegNext(exception) and RegNext(RegNext(exception)).
  const bool ex=state_.execution.exception_r;
  write_record(*record_,fields::lsu_exception_r[0],ex);write_record(*record_,fields::lsu_exception_r[1],ex);
  write_record(*record_,fields::lsu_exception_rr[0],exception_rr_);write_record(*record_,fields::lsu_exception_rr[1],exception_rr_);
  exception_rr_=ex;
  // core.scala:1004 csr.io.retire = RegNext(PopCount(commit.arch_valids)); 1295 kill = RegNext(rob.io.flush.valid).
  write_record(*record_,fields::core_retire_count_r,retired_count_);
  write_record(*record_,fields::core_rob_flush_r,rob_flush_now());
#endif
}

void Core::publish_record() {
  for (unsigned bank = 0; bank < kWidth; ++bank) {
    for (auto rows = rob_rows_dirty_[bank]; rows; rows &= rows - 1)
      write_rob_row(bank, static_cast<unsigned>(__builtin_ctzll(rows)));
    for (auto rows = rob_branch_dirty_[bank]; rows; rows &= rows - 1)
      write_rob_branch(bank, static_cast<unsigned>(__builtin_ctzll(rows)));
    for (auto rows = rob_uop_dirty_[bank]; rows; rows &= rows - 1)
      write_rob_uop_fields(bank, static_cast<unsigned>(__builtin_ctzll(rows)));
    rob_rows_dirty_[bank] = rob_branch_dirty_[bank] = rob_uop_dirty_[bank] = 0;
  }
  for (unsigned lanes = rename_dirty_; lanes; lanes &= lanes - 1)
    write_rename_uop(static_cast<unsigned>(__builtin_ctz(lanes)));
  rename_dirty_ = 0;
  if (csr_dirty_) { csr_dirty_ = false; write_csr_record(); }
  if (step_batch_pending_) {
    step_batch_pending_ = false;
    write_rename_valids(); write_lsq_control(); write_fp_record(); write_rob_ports(); write_core_control();
    write_cut_step_lanes();
  }
}
}  // namespace chisa::boom_model::wide
