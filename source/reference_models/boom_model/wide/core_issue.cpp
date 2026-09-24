#include "core.h"
#include "issue_movement.h"
#include <initializer_list>

namespace chisa::boom_model::wide {
IssueImage& Core::queue(QueueKind kind) {
  if (kind == QueueKind::Floating) return state_.floating_issue;
  if (kind == QueueKind::Memory) return state_.memory_issue;
  return state_.integer_issue;
}
const MicroOp& Core::instruction(unsigned wire) const {
  return state_.rob.instructions[dense(wire)].decoded;
}
unsigned Core::vacancies(const IssueImage& q) {
  return q.capacity - static_cast<unsigned>(__builtin_popcount(q.occupied_mask()));
}
void Core::wake(IssueImage& q, const Wakeup& wakeup) {
  // issue-slot.scala:183-195 compares the wake-up's destination against each
  // slot's source registers with no exception for register 0, so a wake-up for
  // physical register 0 sets the ready bits of every slot that reads it. Only
  // the register write and the busy clear need a real destination.
  if (!wakeup.valid) return;
  using namespace byte_columns;
  unsigned i=0;
  for(;i+8<=q.capacity;i+=8) {
    const auto m1=eq_bytes(load8(q.prs1.data()+i),wakeup.physical);
    const auto m2=eq_bytes(load8(q.prs2.data()+i),wakeup.physical);
    const auto m3=eq_bytes(load8(q.prs3.data()+i),wakeup.physical);
    const auto p1=load8(q.p1.data()+i),p2=load8(q.p2.data()+i),p3=load8(q.p3.data()+i);
    if(m1&~p1)store8(q.p1.data()+i,p1|m1);
    if(m2&~p2)store8(q.p2.data()+i,p2|m2);
    if(m3&~p3)store8(q.p3.data()+i,p3|m3);
    if(wakeup.speculative) {
      const auto s1=m1&eq_bytes(load8(q.rt1.data()+i),RT_FIX);
      const auto s2=m2&eq_bytes(load8(q.rt2.data()+i),RT_FIX);
      if(s1)store8(q.poison1.data()+i,load8(q.poison1.data()+i)|s1);
      if(s2)store8(q.poison2.data()+i,load8(q.poison2.data()+i)|s2);
    }
  }
  // Medium has 20/12-entry queues. The tail must not read or overwrite the
  // following record column; the full eight-byte path above is unchanged.
  for(;i<q.capacity;++i) {
    const bool m1=q.prs1[i]==wakeup.physical,m2=q.prs2[i]==wakeup.physical,m3=q.prs3[i]==wakeup.physical;
    q.p1[i]|=m1;q.p2[i]|=m2;q.p3[i]|=m3;
    if(wakeup.speculative) {
      q.poison1[i]|=m1 && q.rt1[i]==RT_FIX;
      q.poison2[i]|=m2 && q.rt2[i]==RT_FIX;
    }
  }
}
void Core::resolve_issue(IssueImage& q, const BranchUpdate& update) {
  if (!update.resolved && !update.mispredicted) return;
  for (unsigned i = 0; i < q.capacity; ++i) {
    if (q.branch(i) & update.mispredicted) q.state[i]=0;
    q.clear_branches(i,update.resolved);
  }
}
void Core::select_queue(IssueImage& q, const std::uint16_t* fu, unsigned ports, IssueGrant* grants) {
  using namespace byte_columns;
  QueueMask requests=0;
  unsigned start=0;
  for (;start+8<=q.capacity;start+=8) {
    const auto state=load8(q.state.data()+start),p1=load8(q.p1.data()+start),p2=load8(q.p2.data()+start);
    const auto p3=load8(q.p3.data()+start),pp=load8(q.ppred.data()+start);
    const auto ready=(eq_bytes(state,1)&p1&p2&p3&pp) | (eq_bytes(state,2)&(p1|p2)&pp);
    requests |= QueueMask(compact8(ready))<<start;
  }
  for(;start<q.capacity;++start) {
    const bool ready=q.ppred[start] && ((q.state[start]==1 && q.p1[start] && q.p2[start] && q.p3[start]) ||
                                      (q.state[start]==2 && (q.p1[start] || q.p2[start])));
    if(ready)requests|=QueueMask{1}<<start;
  }
  unsigned available=(1u<<ports)-1;
  while (requests && available) {
    const unsigned slot=static_cast<unsigned>(__builtin_ctz(requests)); requests&=requests-1;
    for (unsigned choices=available;choices;choices&=choices-1) {
      const unsigned port=static_cast<unsigned>(__builtin_ctz(choices));
      if (!(q.fu[slot]&fu[port])) continue;
      available &= ~(1u<<port);
      auto& g=grants[port];g.selected=g.valid=true;g.slot=static_cast<int>(slot);
      g.poisoned=q.poisoned(slot);
      const bool two=q.state[slot]==2;
      g.vacates=!two || (q.p1[slot] && q.p2[slot] && q.ppred[slot]);
      auto& s=g.uop;s=StageUop::from(instruction(q.rob[slot]));
      s.rob=q.rob[slot];s.br_mask=q.branch(slot);s.uopc=q.uopc(slot);s.fu_code=q.fu[slot];
      s.prs1=q.prs1[slot];s.prs2=q.prs2[slot];g.prs3=q.prs3[slot];
      s.lrs1_rtype=q.rt1[slot];s.lrs2_rtype=q.rt2[slot];
      if (two && !g.vacates) {
        if (q.p1[slot]) s.lrs2_rtype=RT_X;
        else { s.uopc=uopSTD;s.lrs1_rtype=RT_X; }
      }
      if ((s.csr_cmd==6 || s.csr_cmd==7) && !s.prs1) s.csr_cmd=2;
      break;
    }
  }
}
void Core::prepare_issue(CycleInputs& input, CycleOutputs& output) {
  // One PRE arbitration, using byte masks and only requesting slots. The
  // same compact winner supplies raw read addresses and the functional grant.
  select_queue(state_.integer_issue,input.issue.integer_fu.data(),kWidth,output.integer.data());
  select_queue(state_.memory_issue,&input.issue.memory_fu,1,&output.memory);
  select_queue(state_.floating_issue,&input.issue.floating_fu,1,&output.floating);
}
void Core::select_issue(const CycleInputs& input, CycleOutputs& output) {
  const auto filter=[&](IssueGrant& g) {
    if (!g.selected) return;
    g.squashed=input.load_miss && g.poisoned;
    g.valid=!(g.uop.br_mask&input.branch.mispredicted) && !g.squashed;
    g.uop.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
  };
  for (auto& g:output.integer) filter(g);
  filter(output.memory);filter(output.floating);
  // A squashed PRE winner has consumed its port: never choose a replacement.
  if (input.load_miss) { state_.integer_issue.squash_poison();state_.memory_issue.squash_poison(); }
}
void Core::install(IssueImage& q, unsigned slot, const MicroOp& u) {
  const bool two = (u.uopc == uopSTA && u.lrs2_rtype == RT_FIX) || u.uopc == uopAMO_AG;
  q.rob[slot] = u.rob_idx; q.prs1[slot] = u.prs1; q.prs2[slot] = u.prs2; q.prs3[slot] = u.prs3;
  q.rt1[slot] = u.lrs1_rtype; q.rt2[slot] = u.lrs2_rtype;
  q.fu[slot] = u.fu_code;
  q.opcode[slot]=u.uopc; q.branch_mask[slot]=u.br_mask;
  q.state[slot]=two?2:1;
  q.p1[slot]=!u.prs1_busy;q.p2[slot]=!u.prs2_busy;
  q.p3[slot]=q.kind==QueueKind::Floating ? !u.prs3_busy : 1;
  q.ppred[slot]=!u.ppred_busy;
  // Queue-specific split-store shape is applied here, without three copies
  // of the dispatch MicroOp for the three queues.
  if (q.kind==QueueKind::Memory && u.uopc==uopSTA && u.lrs2_rtype==RT_FLT) {
    q.rt2[slot]=RT_X; q.p2[slot]=1;
  }
  if (q.kind==QueueKind::Floating && u.uopc==uopSTA) {
    q.rt1[slot]=RT_X; q.p1[slot]=1;
  }
  if (q.kind!=QueueKind::Floating) q.poison1[slot]=q.poison2[slot]=0;
  write_issue_payload(q,slot,u);
}
void Core::copy_slot(IssueImage& q, unsigned to, unsigned from) {
  q.rob[to] = q.rob[from]; q.prs1[to] = q.prs1[from]; q.prs2[to] = q.prs2[from];
  q.prs3[to] = q.prs3[from]; q.rt1[to] = q.rt1[from];
  q.rt2[to] = q.rt2[from]; q.fu[to] = q.fu[from];
  q.opcode[to]=q.opcode[from]; q.branch_mask[to]=q.branch_mask[from];
  for (auto* column : {&q.state,&q.p1,&q.p2,&q.p3,&q.ppred})
    (*column)[to]=(*column)[from];
  q.word0[to]=q.word0[from];q.word2[to]=q.word2[from];q.shape[to]=q.shape[from];
  if (q.kind==QueueKind::Integer) q.integer_word1[to]=q.integer_word1[from];
  else if (q.kind==QueueKind::Memory) q.memory_word1[to]=q.memory_word1[from];
  else q.floating_word1[to]=q.floating_word1[from];
  if (q.kind!=QueueKind::Floating) { q.poison1[to]=q.poison1[from];q.poison2[to]=q.poison2[from]; }
}
void Core::collapse(IssueImage& q, QueueMask pre_occupied,
                    const IssueGrant* grants, unsigned ports,
                    const std::array<MicroOp,kWidth>& dispatch, std::uint8_t dispatch_mask) {
  QueueMask vacated=0;
  for (unsigned port=0;port<ports;++port) {
    const auto& g=grants[port];
    if (!g.selected || g.squashed) continue;
    const unsigned slot=static_cast<unsigned>(g.slot);
    if (g.vacates) vacated |= bit(slot);
    else {
      if (q.p1[slot]) q.rewrite_shape(slot,uopSTD,RT_X,q.rt2[slot]);
      else q.rewrite_shape(slot,q.uopc(slot),q.rt1[slot],RT_X);
      if (q.state[slot]) q.state[slot]=1;
    }
  }
  const auto move=issue_movement(q.capacity,pre_occupied,vacated,dispatch_mask);
  for (auto slots=move.receives;slots;slots&=slots-1) {
    const unsigned to=static_cast<unsigned>(__builtin_ctz(slots));
    unsigned distance=1;
    for(unsigned d=1;d<kWidth;++d) if(move.from_distance[d]&bit(to))distance=d+1;
    const unsigned source=to+distance;
    if (source<q.capacity) copy_slot(q,to,source);
    else install(q,to,dispatch[source-q.capacity]);
  }
  for (auto slots=move.clears;slots;slots&=slots-1) q.state[__builtin_ctz(slots)]=0;
  q.set_available(move.available);
}
}  // namespace chisa::boom_model::wide
