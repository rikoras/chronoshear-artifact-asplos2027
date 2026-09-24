#include "core.h"
#include "../common/memory_data.h"

namespace chisa::boom_model::wide {
MemoryTag Core::memory_tag(bool load, unsigned index) const {
  if (index>=kLsq) throw std::out_of_range("Large memory tag index");
  const auto& q=state_.lsu;
  const auto& entry=load ? q.loads[index] : q.stores[index];
  MemoryTag tag;
  tag.rob=entry.rob();tag.pdst=entry.pdst();tag.load=entry.load_index();tag.store=entry.store_index();
  tag.size=entry.size();tag.command=entry.command();tag.branch=entry.branch();
  tag.uses_load=load;tag.uses_store=!load;tag.amo=entry.amo();
  tag.floating=entry.floating;tag.single=entry.single;tag.signed_load=entry.signed_load();
  tag.generation=load ? q.load_generation[index] : q.store_generation[index];
  return tag;
}
bool Core::memory_tag_live(const MemoryTag& tag, BranchMask killed, bool flush) const {
  const auto& q=state_.lsu;
  if (tag.branch&killed) return false;
  if (tag.uses_load)
    return !flush && tag.load<kLsq && test(q.load_valid,tag.load) &&
           q.load_generation[tag.load]==tag.generation && q.loads[tag.load].rob()==tag.rob;
  if (tag.uses_store)
    return tag.store<kLsq && test(q.store_valid,tag.store) &&
           (!flush || test(q.store_committed,tag.store)) &&
           q.store_generation[tag.store]==tag.generation && q.stores[tag.store].rob()==tag.rob;
  return !flush && static_cast<unsigned>(RobGeometry::bank(tag.rob))<kWidth &&
         test(state_.rob.valid[RobGeometry::bank(tag.rob)],RobGeometry::row(tag.rob));
}
MemoryPlan Core::plan_memory(const MemoryControl& control, const BranchUpdate& branch) const {
  const auto& q=state_.lsu;const auto& m=state_.memory;
  MemoryPlan plan;plan.owner=this;plan.cycle=state_.cycle;plan.control=control;
  plan.flush=state_.rob.rolling_back || state_.trap_pending;
  BranchMask killed=branch.mispredicted;
  killed |= pending_b1_mispredict_mask();
  const auto& incoming=m.read[1];
  const auto& u=incoming.uop;
  const bool live=incoming.valid && !plan.flush && !(u.br_mask&killed);
  auto& c=plan.candidates;
  c.load_incoming=live && u.is_load();
  c.stad_incoming=live && u.is_sta() && u.is_std();
  c.sta_incoming=live && u.is_sta() && !u.is_std();
  c.std_incoming=live && u.is_std() && !u.is_sta();
  c.sfence=live && u.mem_cmd==20;
  c.release=control.release_valid;c.hella_incoming=control.hella_incoming;c.hella_wakeup=control.hella_wakeup;
  const unsigned head=q.store_head;
  const bool needs_order=boom_lsu::store_needs_order(test(q.store_valid,head),
      test(q.store_committed,head),q.stores[head].fence(),control.ordered);
  const unsigned retry=m.load_retry, sr=m.store_retry, wake=m.load_wakeup, execute=q.store_execute;
  const auto blocked=m.block1|m.block2;
  c.load_retry=!plan.flush && test(q.load_valid&q.load_address&q.load_virtual,retry) &&
      !test(blocked|q.load_order_fail|q.load_exception,retry) && control.tlb_miss_ready && !needs_order;
  c.sta_retry=test(q.store_valid&q.store_address&q.store_virtual,sr) &&
      !test(q.store_exception,sr) && control.tlb_miss_ready &&
      (!plan.flush || test(q.store_committed,sr));
  c.load_wakeup=!plan.flush && test(q.load_valid&q.load_address,wake) &&
      !test(q.load_virtual|q.load_executed|q.load_succeeded|q.load_order_fail|q.load_exception|blocked,wake) &&
      m.store_blocked!=15 && !m.block_wakeup && !needs_order &&
      (!test(q.load_uncacheable,wake) ||
       (m.commit_load_head && wake==q.load_head && q.dependencies[wake]==0));
  c.store_commit=test(q.store_valid,execute) && !q.stores[execute].fence() &&
      !(q.stores[execute].branch()&killed) && !m.translation_fault.valid &&
      !test(q.store_exception,execute) &&
      (test(q.store_committed,execute) || (!plan.flush && q.stores[execute].amo() &&
       test(q.store_address&q.store_data,execute) && !test(q.store_virtual,execute)));
  plan.schedule=boom_lsu::schedule(c);
  const auto& s=plan.schedule;
  plan.incoming=u;plan.incoming_data=incoming.rs2;
  if (s.load_incoming || s.stad_incoming || s.sta_incoming || s.std_incoming || s.sfence) {
    if (u.uses_ldq()) plan.translated=memory_tag(true,u.ldq_idx);
    else if (u.uses_stq()) plan.translated=memory_tag(false,u.stq_idx);
    else { plan.translated.rob=u.rob;plan.translated.branch=u.br_mask; }
    plan.translated.branch=u.br_mask;
    plan.virtual_address=s.sfence ? incoming.rs1 : incoming.rs1+decode_imm(instruction(u.rob));
    if (!s.std_incoming) {
      plan.translation.valid=true;plan.translation.vaddr=plan.virtual_address;
      plan.translation.size=plan.translated.size;plan.translation.cmd=u.mem_cmd;
    }
  } else if (s.load_retry) {
    plan.translated=memory_tag(true,retry);plan.virtual_address=q.loads[retry].address;
    plan.translation={true,plan.virtual_address,plan.translated.size,plan.translated.command};
  } else if (s.sta_retry) {
    plan.translated=memory_tag(false,sr);plan.virtual_address=q.stores[sr].address;
    plan.translation={true,plan.virtual_address,plan.translated.size,plan.translated.command};
  }
  plan.translation.passthrough=control.passthrough;
  if (s.load_incoming || s.load_retry) plan.cache=plan.translated;
  else if (s.load_wakeup) {
    plan.cache=memory_tag(true,wake);plan.cache_address=q.loads[wake].address;
  } else if (s.store_commit) {
    plan.cache=memory_tag(false,execute);plan.cache_address=q.stores[execute].address;
    plan.store_data=storegen_replicate(plan.cache.size,q.stores[execute].data);
  }
  return plan;
}
MemoryRequest Core::memory_request(const MemoryPlan& plan, const Translation& translation) const {
  MemoryRequest request;
  const auto& s=plan.schedule;
  if (s.load_incoming || s.load_retry) {
    const bool passthrough=plan.control.passthrough || translation.passthrough;
    request.valid=passthrough || (!translation.miss && !translation.uncacheable);
    request.address=passthrough ? plan.virtual_address : translation.physical;
  } else if (s.load_wakeup || s.store_commit) {
    request.valid=true;request.address=plan.cache_address;request.data=plan.store_data;
  } else return request;
  request.tag=plan.cache;request.tag.ticket=state_.memory.next_ticket;
  return request;
}
void Core::launch_memory(const CycleInputs& input, const CycleOutputs& output) {
  auto& m=state_.memory;
  m.issued_load=output.memory.selected && output.memory.uop.uses_ldq();
  m.load_issue_count=m.issued_load ? static_cast<std::uint8_t>((m.load_issue_count+1)&31u) : 0;
  m.read[1]=m.read[0];
  // register-read.scala:110-125: the address leaves at the end of the issue
  // edge and the data arrives at the end of the register-read edge, so the
  // operands of the stage being read belong to this edge, not to the issue
  // edge. register-read.scala:168-175 bypasses a source only when its type is
  // integer; anything else reads the register file, which the model keeps
  // apart from the bypassed values. The memory port reads the integer file, so
  // a floating store's data operand is a register-file read here.
  {
    const auto operand=[&](std::uint8_t preg,std::uint8_t rtype) -> std::uint64_t {
      if (!preg) return 0;
      return rtype==RT_FIX ? state_.integer_values[preg] : state_.integer_registers[preg];
    };
    const auto& held=m.read[1].uop;
    m.read[1].rs1=operand(held.prs1,held.lrs1_rtype);
    m.read[1].rs2=operand(held.prs2,held.lrs2_rtype);
  }
  const auto& raw=output.memory;
  m.read[0].valid=output.memory.valid;
  if (!raw.selected) {
    // issue-unit-age-ordered.scala:93-101 issues a null micro-op with zero
    // source registers, so the stage carries that instead of the last one.
    m.read[0].uop=StageUop{};m.read[0].rs1=0;m.read[0].rs2=0;
    return;
  }
  auto& u=m.read[0].uop;
  u=raw.uop;
  // Apply RegisterReadDecode to compact stage flags directly. Static decode
  // remains in the ROB; a split store does not need a rebuilt MicroOp.
  u.flags &= static_cast<std::uint16_t>(~(StageUop::kIsLoad | StageUop::kIsSta | StageUop::kIsStd));
  if (u.uses_ldq()) u.flags |= StageUop::kIsLoad;
  const bool address=u.uopc==uopSTA || u.uopc==uopAMO_AG;
  if (address && u.lrs1_rtype!=RT_X) u.flags |= StageUop::kIsSta;
  if ((address || u.uopc==uopSTD) && u.lrs2_rtype==RT_FIX) u.flags |= StageUop::kIsStd;
  if (u.uopc==uopAMO_AG || (u.uopc==uopLD && u.mem_cmd==6))
    m.read[0].uop.imm_packed=0;
  m.read[0].uop.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
}
void Core::flush_memory_pipeline() {
  auto& m=state_.memory;
  for (auto& stage : m.read) stage.valid=false;
  for (auto& speculative : m.speculative) speculative.valid=false;
  for (auto& clear : m.clear_store) clear.valid=false;
  m.fp_store.valid=false;m.search.valid=false;m.forward.valid=false;
  m.translation_fault.valid=m.exception.valid=false;
  m.block1=m.block2=m.nacks=0;m.commit_load_head=false;
  if (m.pending.valid && m.pending.tag.uses_load) m.pending_fault=true;
}
}  // namespace chisa::boom_model::wide
