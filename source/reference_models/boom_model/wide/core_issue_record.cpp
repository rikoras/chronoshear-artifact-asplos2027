#include "core.h"

namespace chisa::boom_model::wide {
void Core::bind_issue_columns() {
  if (!record_) throw std::logic_error("Core needs its final record storage");
  const auto bind=[&](IssueImage& q, auto& r) {
    q.state.bind(r.slots_state); q.p1.bind(r.slots_p1); q.p2.bind(r.slots_p2);
    q.p3.bind(r.slots_p3); q.ppred.bind(r.slots_ppred);
    q.poison1.bind(r.slots_p1_poisoned); q.poison2.bind(r.slots_p2_poisoned);
    q.word0.bind(r.slots_slot_uopbank_0_0);
    q.word2.bind(r.slots_slot_uopbank_1_0); q.shape.bind(r.slots_slot_uopbank_2_0);
    q.ready[0]=&r.REG;q.ready[1]=&r.REG_1;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    q.ready[2]=&r.REG_2;
#endif
    q.poison1.fill(0); q.poison2.fill(0);
  };
  auto& integer=state_.integer_issue; auto& memory=state_.memory_issue;
  auto& floating=state_.floating_issue;
  bind(integer,record_->r.coreIntIq); integer.capacity=boomcfg::NUM_INT_IQ_SLOTS;
  integer.integer_word1.bind(record_->r.coreIntIq.slots_slot_uopbank_0_1);
  bind(memory,record_->r.coreMemIq); memory.capacity=boomcfg::NUM_MEM_IQ_SLOTS;
  memory.memory_word1.bind(record_->r.coreMemIq.slots_slot_uopbank_0_1);
  auto& f=record_->r.coreFp;
  floating.capacity=boomcfg::NUM_FP_IQ_SLOTS;
  floating.state.bind(f.fp_issue_unit_slots_state); floating.p1.bind(f.fp_issue_unit_slots_p1);
  floating.p2.bind(f.fp_issue_unit_slots_p2); floating.p3.bind(f.fp_issue_unit_slots_p3);
  floating.ppred.bind(f.fp_issue_unit_slots_ppred);
  floating.word0.bind(f.fp_issue_unit_slots_slot_uopbank_0_0);
  floating.floating_word1.bind(f.fp_issue_unit_slots_slot_uopbank_0_1);
  floating.word2.bind(f.fp_issue_unit_slots_slot_uopbank_1_0);
  floating.shape.bind(f.fp_issue_unit_slots_slot_uopbank_2_0);
  floating.ready[0]=&f.fp_issue_unit_REG;floating.ready[1]=&f.fp_issue_unit_REG_1;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  floating.ready[2]=&f.fp_issue_unit_REG_2;
#endif
  for (auto* q:{&integer,&memory,&floating}) {
    q->state.fill(0); q->p1.fill(0); q->p2.fill(0); q->p3.fill(0); q->ppred.fill(0);
    q->set_available(q->capacity);
  }
}

void Core::write_issue_payload(IssueImage& q, unsigned slot, const MicroOp& u) {
  // Actual enqueue writes the final words once. Moves copy these same words;
  // wakeup writes the final ready columns and never rebuilds a payload.
  constexpr unsigned R=boomcfg::geometry::index_width(RobGeometry::wire_count);
  constexpr unsigned L=boomcfg::LDQ_IDX_WIDTH,S=boomcfg::STQ_IDX_WIDTH;
  constexpr unsigned P=boomcfg::geometry::index_width(boomcfg::NUM_PREGS);
  std::uint64_t word=0;
  const auto append=[&](std::uint64_t value,unsigned width) {
    word=(word<<width)|(value&((UINT64_C(1)<<width)-1));
  };
  if (q.kind==QueueKind::Integer) {
    append(u.is_rvc,1);append(u.fu_code,10);append(u.is_br,1);append(u.is_jalr,1);
    append(u.is_jal,1);append(u.is_sfb,1);append(u.br_tag,4);append(u.ftq_idx,5);
    append(u.edge_inst,1);append(u.pc_lob,6);append(u.taken,1);append(u.imm_packed,20);
    append(u.rob_idx,R);append(u.ldq_idx,L);q.word0[slot]=word;word=0;
    append(u.stq_idx,S);append(u.prs1,P);append(u.prs2,P);append(u.prs3,P);
    append(u.mem_cmd,5);append(u.is_amo,1);append(u.ldst_val,1);
    q.integer_word1[slot]=word;word=0;
    append(u.pdst,P);append(u.bypassable,1);append(u.uses_stq,1);append(u.dst_rtype,2);
  } else if (q.kind==QueueKind::Memory) {
    append(u.fu_code,10);append(u.imm_packed,20);append(u.rob_idx,R);
    append(u.ldq_idx,L);append(u.stq_idx,S);append(u.prs1,P);append(u.prs2,P);
    q.word0[slot]=word;word=0;
    append(u.prs3,P);append(u.mem_cmd,5);append(u.mem_size,2);append(u.mem_signed,1);append(u.is_amo,1);
    q.memory_word1[slot]=word;word=0;
    append(u.pdst,P);append(u.uses_ldq,1);append(u.uses_stq,1);append(u.fp_val,1);
  } else {
    append(u.fu_code,10);append(u.imm_packed,20);append(u.rob_idx,R);append(u.stq_idx,S);
    append(u.prs1,P);append(u.prs2,P);append(u.prs3,P);q.word0[slot]=word;word=0;
    append(u.mem_cmd,5);append(u.is_amo,1);q.floating_word1[slot]=word;word=0;
    append(u.pdst,P);append(u.uses_stq,1);append(u.dst_rtype,2);
  }
  q.word2[slot]=word;
  q.write_shape(slot);
}
}  // namespace chisa::boom_model::wide
