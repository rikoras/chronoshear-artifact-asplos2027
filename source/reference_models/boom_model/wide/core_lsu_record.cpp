#include "core.h"
#include "record_fields.h"
namespace chisa::boom_model::wide {
void Core::write_lsq_load(unsigned i,bool descriptor) {
  const auto& q=state_.lsu;const auto& e=q.loads[i];
#define LD(name,value) write_record(*record_,fields::ldq_##name[i],value)
  LD(bits_addr_bits,e.address);
  LD(bits_forward_stq_idx,q.forwarded_store[i]);LD(bits_st_dep_mask,q.dependencies[i]);
  LD(bits_youngest_stq_idx,q.youngest_store[i]);
  if(descriptor) {
    LD(bits_uop_br_mask,e.branch());LD(bits_uop_pdst,e.pdst());LD(bits_uop_rob_idx,e.rob());
    LD(bits_uop_ldq_idx,e.load_index());LD(bits_uop_stq_idx,e.store_index());
    LD(bits_uop_mem_cmd,e.command());LD(bits_uop_mem_size,e.size());LD(bits_uop_mem_signed,e.signed_load());
    LD(bits_uop_dst_rtype,e.dst_rtype());LD(bits_uop_is_amo,e.amo());
    LD(bits_uop_uses_ldq,MemoryEntry::Word::uses_ldq(e.uop_word));LD(bits_uop_uses_stq,MemoryEntry::Word::uses_stq(e.uop_word));
  }
#undef LD
}
void Core::write_lsq_store(unsigned i,bool) {
  const auto& q=state_.lsu;
#define ST(name,value) write_record(*record_,fields::stq_##name[i],value)
  ST(bits_addr_bits,q.stores[i].address);
  write_record(*record_,fields::stq_descriptor[i],q.stores[i].uop_word);
  if (cut_lanes_) ST(bits_data_bits,q.stores[i].data);   // partition-cut lane: the STQ data register
#undef ST
}
void Core::write_lsq_control() {
  auto& q=state_.lsu;const auto& m=state_.memory;auto& r=record_->r.lsu;
  // Per-row flags of the rows touched this cycle: publish only the bits
  // that differ from what the record holds (lsq_flags_).
  const QueueMask load_rows=q.load_changed|q.load_descriptor_changed,store_rows=q.store_changed;
  const auto flags=[&](QueueMask rows,QueueMask now,QueueMask& held,auto&& lanes) {
    for(auto moved=(now^held)&rows;moved;moved&=moved-1) {
      const unsigned i=__builtin_ctz(moved);write_record(*record_,lanes[i],(now>>i)&1u);
    }
    held=(held&~rows)|(now&rows);
  };
  flags(load_rows,q.load_valid,lsq_flags_.load_valid,fields::ldq_valid);
  flags(load_rows,q.load_address,lsq_flags_.load_address,fields::ldq_bits_addr_valid);
  flags(load_rows,q.load_virtual,lsq_flags_.load_virtual,fields::ldq_bits_addr_is_virtual);
  flags(load_rows,q.load_uncacheable,lsq_flags_.load_uncacheable,fields::ldq_bits_addr_is_uncacheable);
  flags(load_rows,q.load_executed,lsq_flags_.load_executed,fields::ldq_bits_executed);
  flags(load_rows,q.load_succeeded,lsq_flags_.load_succeeded,fields::ldq_bits_succeeded);
  flags(load_rows,q.load_order_fail,lsq_flags_.load_order_fail,fields::ldq_bits_order_fail);
  flags(load_rows,q.load_observed,lsq_flags_.load_observed,fields::ldq_bits_observed);
  flags(load_rows,q.load_forwarded,lsq_flags_.load_forwarded,fields::ldq_bits_forward_std_val);
  flags(store_rows,q.store_valid,lsq_flags_.store_valid,fields::stq_valid);
  flags(store_rows,q.store_address,lsq_flags_.store_address,fields::stq_bits_addr_valid);
  flags(store_rows,q.store_virtual,lsq_flags_.store_virtual,fields::stq_bits_addr_is_virtual);
  flags(store_rows,q.store_data,lsq_flags_.store_data,fields::stq_bits_data_valid);
  flags(store_rows,q.store_committed,lsq_flags_.store_committed,fields::stq_bits_committed);
  flags(store_rows,q.store_succeeded,lsq_flags_.store_succeeded,fields::stq_bits_succeeded);
  for(auto rows=q.load_values_changed|q.load_descriptor_changed;rows;rows&=rows-1) {
    const unsigned i=__builtin_ctz(rows);write_lsq_load(i,(q.load_descriptor_changed&bit(i))!=0);
  }
  for(auto rows=q.store_values_changed;rows;rows&=rows-1) write_lsq_store(__builtin_ctz(rows));
  q.load_changed=q.load_descriptor_changed=q.store_changed=q.load_values_changed=q.store_values_changed=0;
  write_record(*record_,fields::lsu_ldq_head,q.load_head);write_record(*record_,fields::lsu_ldq_tail,q.load_tail);
  write_record(*record_,fields::lsu_ldq_wakeup_idx,m.load_wakeup);write_record(*record_,fields::lsu_ldq_retry_idx,m.load_retry);
  write_record(*record_,fields::lsu_stq_head,q.store_head);write_record(*record_,fields::lsu_stq_tail,q.store_tail);
  write_record(*record_,fields::lsu_stq_commit_head,q.store_commit);write_record(*record_,fields::lsu_stq_execute_head,q.store_execute);
  write_record(*record_,fields::lsu_stq_retry_idx,m.store_retry);
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  r.REG_103=m.store_blocked;r.REG_102=m.block_wakeup;
  r.REG_106=r.REG_107=output_.memory_ports.speculative_wakeup;
#else
  r.live_store_mask=q.store_valid;r.REG_143=m.store_blocked;r.REG_142=m.block_wakeup;
  r.REG_146=output_.memory_ports.speculative_wakeup;r.REG_147=output_.memory_ports.speculative_wakeup;
#endif
  for(unsigned i=0;i<kLsq;++i) r.p1_block_load_mask[i]=(m.block1>>i)&1u;
  r.r_xcpt_valid=m.exception.valid;
  if(m.exception.valid) {r.r_xcpt_uop_rob_idx=m.exception.tag.rob;r.r_xcpt_uop_br_mask=m.exception.tag.branch;}
  r.wb_forward_valid_0=m.forward.valid;
  if(m.forward.valid) {r.wb_forward_ldq_idx_0=m.forward.load.load;r.wb_forward_stq_idx_0=m.forward.store;}
  // lsu.scala:934-937 and the stdf twin: the clear-busy registers reload
  // zero every edge and carry a payload only in the cycle a store clears.
  r.clr_bsy_valid_0=r.stdf_clr_bsy_valid=0;
  r.clr_bsy_rob_idx_0=r.clr_bsy_brmask_0=0;r.stdf_clr_bsy_rob_idx=r.stdf_clr_bsy_brmask=0;
  for(const auto& done:m.clear_store) if(done.valid && done.due==state_.cycle+1) {
    if(done.floating_data) {r.stdf_clr_bsy_valid=1;r.stdf_clr_bsy_rob_idx=done.tag.rob;r.stdf_clr_bsy_brmask=done.tag.branch;}
    else {r.clr_bsy_valid_0=1;r.clr_bsy_rob_idx_0=done.tag.rob;r.clr_bsy_brmask_0=done.tag.branch;}
  }
  auto& rr=record_->r.coreIregRead;const auto& read=m.read[1];
  rr.exe_reg_valids[0]=read.valid;
  // register-read.scala:196-201 writes the stage's payload on every edge, and
  // issue-unit-age-ordered.scala:93-101 supplies a null micro-op with zero
  // source registers when nothing issues, so an idle edge latches zeros here
  // rather than holding the previous operation.
  // register-read.scala:132-134 nulls the valid and the micro-op on a kill but
  // still writes the operand registers with the read, so those follow the
  // stage's operands and not its validity.
  rr.exe_reg_rs1_data[0]=read.rs1;
  rr.exe_reg_rs2_data[0]=read.rs2;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  rr.exe_reg_uops_br_mask[0]=read.valid ? read.uop.br_mask : 0;
#endif
  rr.exe_reg_uops_fu_code[0]=read.valid ? read.uop.fu_code : 0;
  rr.exe_reg_uops_0_imm_packed=read.valid ? read.uop.imm_packed : 0;
  rr.exe_reg_uops_0_uopc=read.valid ? read.uop.uopc : 0;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  rr.exe_reg_uops_0_ctrl_is_load=read.valid ? read.uop.is_load() : 0;
#endif
  rr.exe_reg_uops_0_ctrl_is_sta=read.valid ? read.uop.is_sta() : 0;
  rr.exe_reg_uops_0_ctrl_is_std=read.valid ? read.uop.is_std() : 0;
  if(m.read[0].valid) rr.REG_1_br_mask=m.read[0].uop.br_mask;
}
}  // namespace chisa::boom_model::wide
