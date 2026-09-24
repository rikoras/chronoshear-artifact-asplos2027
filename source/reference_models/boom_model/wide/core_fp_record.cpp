#include "core.h"
#include "ifpu_publication.h"
#include "record_fields.h"
namespace chisa::boom_model::wide {
namespace {
template<class Q> std::uint64_t masks(const Q& q,unsigned start,unsigned count) {
  std::uint64_t result=0;
  for(unsigned i=start;i<start+count;++i) result=(result<<kBranches)|q.entries[i].uop.br_mask;
  return result;
}
template<class Q> unsigned valids(const Q& q) {
  unsigned result=0;for(bool valid:q.valids) result=(result<<1)|unsigned(valid);return result;
}
}
void Core::write_fp_record() {
  auto& f=state_.floating;auto& r=record_->r.coreFp;auto& c=record_->r.coreCsrExe;
  if(f.queue_words_changed) {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    r.fpiu_unit_BranchKillableQueueinst_uopsbank_1_0=masks(f.to_integer,0,5);
    r.fpiu_unit_BranchKillableQueueinst_uopsbank_1_1=masks(f.to_integer,5,2);
#else
    r.fpiu_unit_BranchKillableQueueinst_uopsbank_1[0]=masks(f.to_integer,0,4);
    r.fpiu_unit_BranchKillableQueueinst_uopsbank_1[1]=masks(f.to_integer,4,3);
#endif
    r.fpiu_unit_BranchKillableQueueinst_validsbank_0_0=valids(f.to_integer);
    r.fpiu_unit_BranchKillableQueueinst_maybe_full=f.to_integer.maybe_full;
    r.fpiu_unit_BranchKillableQueueinst_value=f.to_integer.enqueue;r.fpiu_unit_BranchKillableQueueinst_value_1=f.to_integer.dequeue;
    r.fpiu_unit_BranchKillableQueue_1_uopsbank_1_0=masks(f.to_store,0,3);
    r.fpiu_unit_BranchKillableQueue_1_validsbank_0_0=valids(f.to_store);
    r.fpiu_unit_BranchKillableQueue_1_maybe_full=f.to_store.maybe_full;
    r.fpiu_unit_BranchKillableQueue_1_value=f.to_store.enqueue;r.fpiu_unit_BranchKillableQueue_1_value_1=f.to_store.dequeue;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    auto& j=record_->r.coreMisc;
    j.jmp_unit_BranchKillableQueueinst_uopsbank_0_0=masks(f.from_integer,0,5);
    j.jmp_unit_BranchKillableQueueinst_validsbank_0_0=valids(f.from_integer);
    j.jmp_unit_BranchKillableQueueinst_maybe_full=f.from_integer.maybe_full;
    j.jmp_unit_BranchKillableQueueinst_value=f.from_integer.enqueue;
    j.jmp_unit_BranchKillableQueueinst_value_1=f.from_integer.dequeue;
#else
    c.BranchKillableQueueinst_uopsbank_0_0=masks(f.from_integer,0,4);
    c.BranchKillableQueueinst_uops_4_br_mask=f.from_integer.entries[4].uop.br_mask;
    c.BranchKillableQueueinst_validsbank_0_0=valids(f.from_integer);
    c.BranchKillableQueueinst_maybe_full=f.from_integer.maybe_full;
    c.BranchKillableQueueinst_value=f.from_integer.enqueue;c.BranchKillableQueueinst_value_1=f.from_integer.dequeue;
#endif
    record_->c.coreFp.fpiu_unit_BranchKillableQueueinst_ram_fflags_bits_uop_rob_idx_MPORT_1=f.to_integer.entries[f.to_integer.dequeue].uop.rob;
    record_->c.coreFp.fpiu_unit_BranchKillableQueue_1_ram_fflags_bits_uop_rob_idx_MPORT_1=f.to_store.entries[f.to_store.dequeue].uop.rob;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    record_->c.coreMisc.jmp_unit_BranchKillableQueueinst_ram_fflags_bits_uop_rob_idx_MPORT_1=f.from_integer.entries[f.from_integer.dequeue].uop.rob;
#else
    record_->c.coreCsrExe.BranchKillableQueueinst_ram_fflags_bits_uop_rob_idx_MPORT_1=f.from_integer.entries[f.from_integer.dequeue].uop.rob;
#endif
    if (cut_lanes_) {
      // The per-entry uop fields of the three BranchKillableQueues.
      const auto queue_uop=[&](unsigned q,unsigned i,const FpTag& u) {
        write_record(*record_,fields::fp_queue_uop_uopc[q][i],u.uopc);write_record(*record_,fields::fp_queue_uop_rob_idx[q][i],u.rob);
        write_record(*record_,fields::fp_queue_uop_stq_idx[q][i],u.stq_idx);write_record(*record_,fields::fp_queue_uop_pdst[q][i],u.pdst);
        write_record(*record_,fields::fp_queue_uop_is_amo[q][i],u.is_amo());write_record(*record_,fields::fp_queue_uop_uses_stq[q][i],u.uses_stq());
        write_record(*record_,fields::fp_queue_uop_dst_rtype[q][i],u.dst_rtype);
      };
      for (unsigned i=0;i<f.to_integer.entries.size();++i) queue_uop(0,i,f.to_integer.entries[i].uop);
      for (unsigned i=0;i<f.to_store.entries.size();++i) queue_uop(1,i,f.to_store.entries[i].uop);
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
      constexpr unsigned from_unit=1;
#else
      constexpr unsigned from_unit=0;
#endif
      for (unsigned i=0;i<f.from_integer.entries.size();++i) {
        const auto& u=f.from_integer.entries[i].uop;
        write_record(*record_,fields::from_integer_uop_rob_idx[from_unit][i],u.rob);
        write_record(*record_,fields::from_integer_uop_pdst[from_unit][i],u.pdst);
        write_record(*record_,fields::from_integer_uop_dst_rtype[from_unit][i],u.dst_rtype);
      }
    }
    f.queue_words_changed=false;
  }
  r.REG=f.divide_issue_mask ? 0x37fu : 0x3ffu;
  if(f.long_writeback.valid) {r.REG_1_bits_data_1=f.long_writeback.rec_lo;r.REG_1_bits_data_2=f.long_writeback.rec_hi&1u;}
  r.fpiu_unit_fdivsqrt_r_buffer_val=f.divide_buffer.value.valid;
  r.fpiu_unit_fdivsqrt_r_divsqrt_val=f.divide_active.value.valid;
  r.fpiu_unit_fdivsqrt_r_out_val=f.divide_output.valid;
  if(f.divide_buffer_changed && f.divide_buffer.value.valid) {
    r.fpiu_unit_fdivsqrt_r_buffer_fin_in1_1=f.divide_buffer.a;r.fpiu_unit_fdivsqrt_r_buffer_fin_in1_2=f.divide_buffer.hi&1u;
    r.fpiu_unit_fdivsqrt_r_buffer_fin_in2_1=f.divide_buffer.b;r.fpiu_unit_fdivsqrt_r_buffer_fin_in2_2=(f.divide_buffer.hi>>1)&1u;
  }
  if(f.divide_output_changed && f.divide_output.valid) {
    const auto& u=f.divide_output.uop;
    r.fpiu_unit_fdivsqrt_r_out_uop_br_mask=u.br_mask;r.fpiu_unit_fdivsqrt_r_out_uop_rob_idx=u.rob;
    r.fpiu_unit_fdivsqrt_r_out_uop_dst_rtype=u.dst_rtype;
    if (cut_lanes_) {
      write_record(*record_,fields::fdivsqrt_r_out_uop_pdst,u.pdst);
      write_record(*record_,fields::fdivsqrt_r_out_flags_double,f.divide_output.flags);
      write_record(*record_,fields::fdivsqrt_r_out_wdata_double,
                   (static_cast<unsigned __int128>(f.divide_output.rec_hi&1u)<<64)|f.divide_output.rec_lo);
    }
  }
  if (cut_lanes_ && f.divide_active_changed) {
    // fdivsqrt.scala r_divsqrt_fin: latched with the request that enters the divider.
    const auto& d=f.divide_active;
    write_record(*record_,fields::fdivsqrt_r_divsqrt_fin_rm,d.rounding);
    write_record(*record_,fields::fdivsqrt_r_divsqrt_fin_typeTagIn,
                 d.value.uop.uopc==uopFDIV_D || d.value.uop.uopc==uopFSQRT_D ? 1u : 0u);
  }
  f.divide_buffer_changed=f.divide_output_changed=f.divide_active_changed=false;
  r.fpiu_unit_fpu_REG_3=f.wrapper_valids[3];
  if(f.wrapper_valids[3]) {r.fpiu_unit_fpu_REG_1_3_fu_code=f.wrapper_uops[3].fu_code;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    r.fpiu_unit_fpu_REG_1_3_br_mask=f.wrapper_uops[3].br_mask;
#endif
    if (cut_lanes_) {
      const auto& u=f.wrapper_uops[3];
      write_record(*record_,fields::fpu_stage3_uop_is_amo,(u.flags&1u)!=0);
      write_record(*record_,fields::fpu_stage3_uop_rob_idx,u.rob_idx);
      write_record(*record_,fields::fpu_stage3_uop_stq_idx,u.stq_idx);
    }
  }
  if (cut_lanes_) {
    // functional-unit.scala:239 shifts the uop every edge; an idle stage
    // carries NullMicroOp (dst_rtype RT_X, pdst/uopc/uses_stq zero).
    const bool live3=f.wrapper_valids[3];const auto& u3=f.wrapper_uops[3];
    write_record(*record_,fields::fpu_stage3_uop_dst_rtype,live3 ? u3.dst_rtype : 2u);
    write_record(*record_,fields::fpu_stage3_uop_pdst,live3 ? u3.pdst : 0u);
    write_record(*record_,fields::fpu_stage3_uop_uopc,live3 ? u3.uopc : 0u);
    write_record(*record_,fields::fpu_stage3_uop_uses_stq,live3 && (u3.flags&2u)!=0);
  }
  r.fregister_read_exe_reg_valids_0=f.read[1].valid;
  if (cut_lanes_ && f.read[0].valid) write_record(*record_,fields::fp_rrd_stage0_br_mask,f.read[0].uop.br_mask);
  {
    // register-read.scala:134: exe_reg_uops := Mux(kill, NullMicroOp, rrd_uops),
    // and rrd_uops is the issue unit's NullMicroOp when nothing issues, so an
    // idle stage shows dst_rtype RT_X and zero pdst/uopc/uses_stq; the fields
    // NullMicroOp leaves DontCare keep their last payload.
    const bool live=f.read[1].valid;const auto& u=f.read[1].uop;
    if (live) {
      r.fregister_read_exe_reg_rs2_data_0_1=f.read[1].rec_lo[1];r.fregister_read_exe_reg_rs2_data_0_2=(f.read[1].rec_hi>>1)&1u;
      r.fregister_read_exe_reg_uops_0_br_mask=u.br_mask;
      r.fregister_read_exe_reg_uops_0_fu_code=u.fu_code;r.fregister_read_exe_reg_uops_0_is_amo=u.is_amo();
      r.fregister_read_exe_reg_uops_0_rob_idx=u.rob;r.fregister_read_exe_reg_uops_0_stq_idx=u.stq_idx;
    }
    r.fregister_read_exe_reg_uops_0_dst_rtype=live ? u.dst_rtype : 2u;
    r.fregister_read_exe_reg_uops_0_pdst=live ? u.pdst : 0u;
    r.fregister_read_exe_reg_uops_0_uopc=live ? u.uopc : 0u;
    r.fregister_read_exe_reg_uops_0_uses_stq=live && u.uses_stq();
  }
  if (cut_lanes_) {
    // The IntToFP unit's output pipe: data latched with the result, the
    // double-type flag (functional-unit.scala 621) one cycle after the request.
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    constexpr unsigned ifpu_unit=1;
#else
    constexpr unsigned ifpu_unit=0;
#endif
    if (f.ifpu_changed) {
      f.ifpu_changed=false;
      write_record(*record_,fields::ifpu_out_data[ifpu_unit],
                   (static_cast<unsigned __int128>(f.ifpu_rec_hi&1u)<<64)|f.ifpu_rec_lo);
    }
    if (f.integer_valids&2u) {
      const auto uopc=f.integer_uops[1].uopc;
      write_record(*record_,fields::ifpu_out_double[ifpu_unit],ifpu_output_double(uopc) ? 1u : 0u);
    }
  }
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  auto& j=record_->r.coreMisc;
  j.jmp_unit_ifpu_REG_1=(f.integer_valids&2u)!=0;
  {
    // The IntToFP unit's stage register shifts every edge (NullMicroOp when idle).
    const bool live=(f.integer_valids&2u)!=0;const auto& u=f.integer_uops[1];
    j.jmp_unit_ifpu_REG_1_1_dst_rtype=live ? u.dst_rtype : 2u;
    j.jmp_unit_ifpu_REG_1_1_pdst=live ? u.pdst : 0u;
    if (live) j.jmp_unit_ifpu_REG_1_1_rob_idx=u.rob;
  }
#else
  c.ifpu_REG_1=(f.integer_valids&2u)!=0;
  {
    // The IntToFP unit's stage register shifts every edge (NullMicroOp when idle).
    const bool live=(f.integer_valids&2u)!=0;const auto& u=f.integer_uops[1];
    if (live) { c.ifpu_REG_1_1_br_mask=u.br_mask;c.ifpu_REG_1_1_rob_idx=u.rob; }
    c.ifpu_REG_1_1_dst_rtype=live ? u.dst_rtype : 2u;c.ifpu_REG_1_1_pdst=live ? u.pdst : 0u;
  }
#endif
}
void Core::write_ifpu_input() {
  const auto& f=state_.floating;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  auto& r=record_->r.coreMisc;
  r.jmp_unit_ifpu_ifpu_inPipe_bits_in1=f.integer_operand;
  r.jmp_unit_ifpu_ifpu_inPipe_bits_rm=f.integer_rounding;
  r.jmp_unit_ifpu_ifpu_inPipe_bits_typ=f.integer_type;
  r.jmp_unit_ifpu_ifpu_inPipe_bits_typeTagIn=f.integer_tag;
  r.jmp_unit_ifpu_ifpu_inPipe_bits_wflags=f.integer_wflags;
#else
  auto& r=record_->r.coreCsrExe;
  r.ifpu_ifpu_inPipe_bits_in1=f.integer_operand;r.ifpu_ifpu_inPipe_bits_rm=f.integer_rounding;
  r.ifpu_ifpu_inPipe_bits_typ=f.integer_type;r.ifpu_ifpu_inPipe_bits_typeTagIn=f.integer_tag;
  r.ifpu_ifpu_inPipe_bits_wflags=f.integer_wflags;
#endif
}
}  // namespace chisa::boom_model::wide
