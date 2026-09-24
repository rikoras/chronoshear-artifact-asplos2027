#include "core.h"
#include "record_fields.h"
namespace chisa::boom_model::wide {
void Core::write_rob_row(unsigned bank,unsigned row) {
  const auto& r=state_.rob;
  write_record(*record_,fields::rob_val[bank][row],test(r.valid[bank],row));
  write_record(*record_,fields::rob_bsy[bank][row],test(r.busy[bank],row));
  write_record(*record_,fields::rob_exception[bank][row],test(r.exception[bank],row));
  write_record(*record_,fields::rob_unsafe[bank][row],test(r.unsafe[bank],row));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  constexpr bool publish_exc_cause=true;
#else
  const bool publish_exc_cause=cut_lanes_;   // a partition-cut lane on Large
#endif
  if (publish_exc_cause && test(r.valid[bank]&r.exception[bank],row)) {
    unsigned oldest=kRobEntries;
    for (unsigned b=0;b<kWidth;++b) {
      const auto mask=r.valid[b]&r.exception[b];
      if (!mask) continue;
      const auto rotated=(mask>>r.head)|(r.head ? mask<<(kRows-r.head) : 0);
      const unsigned age=__builtin_ctz(rotated)*kWidth+b;
      if (age<oldest) {
        oldest=age;
        const auto cause=r.exception_cause[((r.head+age/kWidth)%kRows)*kWidth+b];
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
        record_->r.coreRob.r_xcpt_uop_exc_cause=cause;
#else
        write_record(*record_,fields::rob_r_xcpt_uop_exc_cause,cause);
#endif
      }
    }
  }
  // The locked BOOM configurations have no SFB predication.
  write_record(*record_,fields::rob_predicated[bank][row],0u);
  if(bank==0) {
    record_->c.coreRob.state_rob_exception_r[row+1]=test(r.exception[0],row);
    record_->c.coreRob.state_rob_unsafe_r[row+1]=test(r.unsafe[0],row);
  }
}
void Core::write_rob_branch(unsigned bank,unsigned row) {
  write_record(*record_,fields::rob_branch[bank][row],state_.rob.branch_mask[row*kWidth+bank]);
}
void Core::write_rob_ports() {
  const auto& r=state_.rob;auto& c=record_->c.coreRob;
  c.state_rob_uop_r[0]=r.packed_uop[(r.fsm==2 ? r.tail : r.head)*kWidth];
  c.state_rob_uop_r[1]=r.packed_uop[r.head*kWidth];
  for(unsigned p=2;p<kWritebackPorts+2;++p) if(r.reads.uop_care&(1u<<p)) c.state_rob_uop_r[p]=r.reads.uop[p];
  for(unsigned p=0;p<kWritebackPorts+3;++p) if(r.reads.busy_care&(1u<<p)) c.state_rob_bsy_r[p]=(r.reads.busy>>p)&1u;
  c.state_rob_bsy_r[2]=test(r.busy[0],r.head);
  c.state_rob_exception_r[0]=test(r.exception[0],r.head);
  c.state_rob_exception_r[33]=test(r.exception[0],r.pnr);
  c.state_rob_unsafe_r[33]=test(r.unsafe[0],r.pnr);
  if(state_.memory.exception.valid) c.state_rob_unsafe_r[0]=test(r.unsafe[0],RobGeometry::row(state_.memory.exception.tag.rob));
  c.state_rob_predicated_r0=0;
  c.rob_fflags_MPORT_4=r.fflags[r.head*kWidth]&31u;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  c.rob_fflags_1_MPORT_15=r.fflags[r.head*kWidth+1]&31u;
  c.rob_fflags_2_MPORT_26=r.fflags[r.head*kWidth+2]&31u;
#else
  c.rob_fflags_1_MPORT_14=r.fflags[r.head*kWidth+1]&31u;
#endif
  auto& q=record_->r.coreRob;
  q.REG=r.exception_delay1;q.REG_2=r.exception_delay2;q.REG_6=state_.memory.commit_load_head;
  q.maybe_full=r.maybe_full;
  q.rob_head=r.head;q.rob_tail=r.tail;q.rob_pnr=r.pnr;q.rob_state=r.fsm;
  q.rob_head_lsb=r.head_lsb;q.rob_tail_lsb=r.tail_lsb;
}
void Core::write_flush_record(const MicroOp& u) {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  record_->r.coreMisc.REG_16=u.ftq_idx;
#else
  auto& r=record_->r.coreMisc;
  r.REG_8=u.pc_lob;r.REG_9=u.edge_inst;r.REG_10=u.is_rvc;r.REG_11=u.ftq_idx;
#endif
}

void Core::write_rob_uop_fields(unsigned bank,unsigned row) {
  // The RTL's per-entry rob_uop registers are written at dispatch only; the
  // partitioned kernels read these fields across the ROB/LSU/frontend cuts.
  const MicroOp& u=state_.rob.instructions[row*kWidth+bank].decoded;
#define UOP(name) write_record(*record_,fields::rob_uop_##name[bank][row],u.name)
  UOP(dst_rtype);UOP(edge_inst);UOP(flush_on_commit);UOP(ftq_idx);UOP(is_fencei);UOP(is_rvc);UOP(is_sys_pc2epc);
  UOP(ldst);UOP(ldst_val);UOP(pc_lob);UOP(pdst);UOP(stale_pdst);UOP(uopc);UOP(uses_ldq);UOP(uses_stq);
#undef UOP
}
}  // namespace chisa::boom_model::wide
