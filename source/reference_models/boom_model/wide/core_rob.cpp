#include "core.h"
#include "record_fields.h"
#include "../common/boom_uop_pack.h"
#include "../common/fp_execute.h"

namespace chisa::boom_model::wide {
unsigned Core::dense(unsigned wire) {
  const int index = RobGeometry::dense_from_wire(static_cast<int>(wire));
  if (index < 0) throw std::out_of_range("reserved Large ROB wire code");
  return static_cast<unsigned>(index);
}
bool Core::rob_can_dispatch() const {
  return state_.rob.fsm==1 && !state_.rob.serializing &&
         (state_.rob.row_open || !test(state_.rob.rows,state_.rob.tail));
}
void Core::rob_enqueue(const MicroOp& u, unsigned bank, bool debug) {
  auto& rob = state_.rob;
  if (bank >= kWidth || !rob_can_dispatch()) throw std::logic_error("ROB enqueue without a row");
  const unsigned wire = static_cast<unsigned>(RobGeometry::encode(rob.tail,bank));
  if (u.rob_idx != wire) throw std::logic_error("dispatch/ROB wire identity differs");
  const unsigned index = dense(wire);
  if (test(rob.valid[bank],rob.tail)) throw std::logic_error("ROB bank overwritten while live");
  rob.rows |= bit(rob.tail);rob.row_open = true;
  rob.instructions[index] = {u,debug};
  assign(rob.valid[bank],rob.tail,true);
  assign(rob.busy[bank],rob.tail,!(u.is_fence || u.is_fencei));
  assign(rob.unsafe[bank],rob.tail,u.uses_ldq || (u.uses_stq && !u.is_fence) || u.is_br || u.is_jalr);
  assign(rob.exception[bank],rob.tail,u.exception != 0);
  rob.exception_cause[index] = u.exc_cause;
  if(u.exception) record_->r.coreRob.r_xcpt_val=1;
  rob.exception_tval_valid[index]=false;
  rob.branch_mask[index] = u.br_mask;
  rob.fflags[index] = 0;
  rob.packed_uop[index] = pack_rob_uop(u);
  mark_rob_row(bank,rob.tail);mark_rob_branch(bank,rob.tail);
  if (cut_lanes_) mark_rob_uop(bank,rob.tail);   // written once, at dispatch, like the RTL rob_uop registers
  write_record(*record_,fields::rob_fp[bank][rob.tail],u.fp_val);

}
void Core::rob_close_row() {
  auto& rob = state_.rob;
  if (!rob.row_open) return;
  rob.row_open = false;
  rob.tail = static_cast<std::uint8_t>((rob.tail+1)&31u);
}
void Core::begin_rob_reads() {
  auto& r=state_.rob;auto& p=r.reads;
  p={};p.valid0=r.valid[0];p.unsafe0=r.unsafe[0];p.exception0=r.exception[0];
  p.head=r.head;p.pnr=r.pnr;
  const unsigned row0=r.fsm==2 ? r.tail : r.head;
  p.uop[0]=r.packed_uop[row0*kWidth];p.uop[1]=r.packed_uop[r.head*kWidth];
  p.uop_care=static_cast<std::uint8_t>(unsigned(test(p.valid0,row0)) |
                                    (unsigned(test(p.valid0,r.head))<<1));
  p.busy=static_cast<std::uint16_t>(unsigned(test(r.busy[0],r.head))<<2);
  p.busy_care=static_cast<std::uint16_t>(unsigned(test(p.valid0,r.head))<<2);
  for(unsigned bank=0;bank<kWidth;++bank) {
    p.fflags[bank]=r.fflags[r.head*kWidth+bank];
    p.head_valid |= static_cast<std::uint8_t>(unsigned(test(r.valid[bank],r.head))<<bank);
  }
  const auto& fault=state_.memory.exception;
  const unsigned exception_row=RobGeometry::row(fault.tag.rob);
  p.exception_unsafe=test(r.unsafe[0],exception_row);
  p.exception_unsafe_care=fault.valid && test(p.valid0,exception_row);
}
void Core::capture_rob_writeback_reads(const CycleInputs& input) {
  const auto& r=state_.rob;auto& p=state_.rob.reads;
  for(const auto& c:input.completions) {
    if(!c.valid || c.source_port>=kWritebackPorts+2)continue;
    const unsigned row=RobGeometry::row(c.rob);
    const bool care=test(p.valid0,row);
    const unsigned busy_port=c.source_port<kWritebackPorts ? c.source_port+3 : c.source_port-kWritebackPorts;
    const auto bitmask=static_cast<std::uint16_t>(1u<<busy_port);
    if(test(r.busy[0],row))p.busy |= bitmask;
    if(care)p.busy_care |= bitmask;
    if(c.source_port<kWritebackPorts) {
      const unsigned uop_port=c.source_port+2;
      p.uop[uop_port]=r.packed_uop[row*kWidth];
      if(care)p.uop_care |= static_cast<std::uint8_t>(1u<<uop_port);
    }
  }
}
bool Core::complete(const Completion& completion) {
  if (!completion.valid) return false;
  auto& rob = state_.rob;
  const unsigned index = dense(completion.rob);
  const unsigned bank = RobGeometry::bank(completion.rob), row = RobGeometry::row(completion.rob);
  if (!test(rob.valid[bank],row)) return false; // Completion of a branch-killed operation.
  if (completion.clear_busy) {
    rob.busy[bank] &= ~bit(row);rob.unsafe[bank] &= ~bit(row);
  }
  if (completion.exception) {
    record_->r.coreRob.r_xcpt_val=1;
    rob.exception[bank] |= bit(row);rob.exception_cause[index] = completion.cause;
    rob.exception_tval_valid[index]=completion.tval_valid;
    if (completion.tval_valid) rob.exception_tval[index]=completion.tval;
  }
  rob.fflags[index] |= completion.fflags & 31u;
  if (completion.writes_integer && completion.pdst) {
    if (completion.pdst >= boomcfg::NUM_PREGS) throw std::out_of_range("integer writeback register");
    state_.integer_registers[completion.pdst] = completion.data;
    state_.integer_values[completion.pdst] = completion.data;
    state_.rename.integer.busy &= ~(PhysicalMask{1} << completion.pdst);
  }
  if (completion.writes_float && completion.pdst) {
    if (completion.pdst >= boomcfg::NUM_FPREGS) throw std::out_of_range("floating writeback register");
    state_.floating_registers[completion.pdst] = completion.data;
    const auto rec=completion.floating_rec_valid
        ? (sfp::rec_t(completion.floating_rec_hi&1u)<<64)|completion.floating_rec_lo
        : fp_result_rec(rob.instructions[index].decoded,completion.data);
    state_.floating_rec_lo[completion.pdst]=static_cast<std::uint64_t>(rec);
    state_.floating_rec_hi[completion.pdst]=static_cast<std::uint8_t>((rec>>64)&1u);
    state_.rename.floating.busy &= ~(PhysicalMask{1} << completion.pdst);
  }
  mark_rob_row(bank,row);
  return true;
}
void Core::resolve_rob(const BranchUpdate& update) {
  if (!update.resolved && !update.mispredicted && !update.redirect) return;
  auto& rob = state_.rob;
  for (unsigned row = 0; row < kRows; ++row) {
    for (unsigned bank = 0; bank < kWidth; ++bank) {
      if (!test(rob.valid[bank],row)) continue;
      const unsigned index = row*kWidth+bank;
      if (rob.branch_mask[index] & update.mispredicted) {
        rob.valid[bank] &= ~bit(row);rob.busy[bank] &= ~bit(row);
        rob.unsafe[bank] &= ~bit(row);rob.exception[bank] &= ~bit(row);
        mark_rob_row(bank,row);
      } else {
        if(rob.branch_mask[index]&update.resolved) {
          rob.branch_mask[index] &= static_cast<BranchMask>(~update.resolved);
          mark_rob_branch(bank,row);
        }
      }
    }
  }
  QueueMask exceptions=0;
  for (unsigned bank=0;bank<kWidth;++bank) exceptions |= rob.valid[bank]&rob.exception[bank];
  if (!exceptions) record_->r.coreRob.r_xcpt_val=0;
  if (!update.redirect) return;
  (void)dense(update.rob);
  const unsigned branch_row = RobGeometry::row(update.rob);
  const unsigned distance = (branch_row-rob.head)&31u;
  for (unsigned row = 0; row < kRows; ++row) {
    if (((row-rob.head)&31u) <= distance) continue;
    rob.rows &= ~bit(row);
    for (unsigned bank = 0; bank < kWidth; ++bank) {
      rob.valid[bank] &= ~bit(row);rob.busy[bank] &= ~bit(row);
      rob.unsafe[bank] &= ~bit(row);rob.exception[bank] &= ~bit(row);
      mark_rob_row(bank,row);
    }
  }
  rob.tail = static_cast<std::uint8_t>((branch_row+1)&31u);
  rob.row_open = false;
}
bool Core::preview_fencei_retire(BranchMask killed) const {
  const auto& rob = state_.rob;
  if (state_.rob.rolling_back || state_.trap_pending) return false;
  if (state_.csr.wfi || state_.csr.cease) return false;
  if (!rob.rows) return false;
  const unsigned row = rob.head;
  if (!test(rob.rows,row)) return false;
  for (unsigned bank = 0; bank < kWidth; ++bank) {
    if (!test(rob.valid[bank],row)) continue;
    const unsigned index = row*kWidth+bank;
    if (rob.branch_mask[index] & killed) continue;  // resolve_rob() clears it first
    if (test(rob.exception[bank],row)) return false;
    if (test(rob.busy[bank],row)) return false;
    const auto& u = rob.instructions[index].decoded;
    if (u.flush_on_commit) return u.is_fencei != 0;
  }
  return false;
}
void Core::commit(const std::array<QueueMask,kWidth>& busy_before, bool allowed, CycleOutputs& out) {
  auto& rob = state_.rob;
  if (!rob.rows || !allowed) return;
  const unsigned row = rob.head;
  if (!test(rob.rows,row)) throw std::logic_error("ROB head does not name its oldest row");
  for (unsigned bank = 0; bank < kWidth; ++bank) {
    if (!test(rob.valid[bank],row)) continue;
    const unsigned index = row*kWidth+bank;
    if (test(rob.exception[bank],row)) {
      out.exception = true;out.exception_cause = rob.exception_cause[index];
      record_->r.coreRob.r_xcpt_val=0;
      write_flush_record(rob.instructions[index].decoded);
      out.exception_rob = static_cast<std::uint8_t>(RobGeometry::encode(row,bank));
      out.flush_type=out.exception_cause==16 ? 2 : 1;
      if (out.exception_cause!=16) { out.commit_ftq_valid=true;out.commit_ftq=rob.instructions[index].decoded.ftq_idx; }
      break; // Trap/rollback scheduling belongs to the CSR control integration.
    }
    if (test(busy_before[bank],row)) break;
    const auto& entry = rob.instructions[index];
    const auto& u = entry.decoded;
    RetirementEvent event;
    event.valid = true;event.cycle = state_.cycle;event.pc = u.debug_pc;
    event.debug_mode = entry.debug;event.is_rvc = u.is_rvc != 0;
    event.instruction = u.debug_inst & (event.is_rvc ? UINT32_C(0xffff) : UINT32_MAX);
    event.expanded_instruction = u.inst;event.rd = u.ldst;
    event.writes_x = u.ldst_val && u.dst_rtype == RT_FIX && u.ldst != 0;
    event.writes_f = u.ldst_val && u.dst_rtype == RT_FLT;
    if (event.writes_x) event.value = state_.integer_registers[u.pdst];
    if (event.writes_f) event.value = state_.floating_registers[u.pdst];
    event.fflags = u.fp_val && !u.uses_stq ? rob.fflags[index] : 0;
    commit_memory(u,event);
    architectural_.retire(event);
    out.retired[bank] = architectural_.event();
    out.commit_ftq_valid=true;out.commit_ftq=u.ftq_idx;
    return_register(u,false);
    rob.valid[bank] &= ~bit(row);
    rob.busy[bank] &= ~bit(row);rob.unsafe[bank] &= ~bit(row);rob.exception[bank] &= ~bit(row);
    mark_rob_row(bank,row);
    if (u.is_unique) rob.serializing = false;
    if (u.flush_on_commit) {
      out.serializing = true;
      write_flush_record(u);
      out.flush_type=u.uopc==uopERET ? 3 : u.is_sys_pc2epc ? 2 : 4;
      const auto target=u.uopc==uopERET ? state_.csr_flush_target : u.debug_pc+(u.is_rvc ? 2u : 4u);
      out.redirect={true,false,false,false,false,false,u.ftq_idx,u.pc_lob,0,0,target};
      out.invalidate_icache=u.is_fencei;
    }
    if (u.flush_on_commit) break; // Do not retire younger lanes across a serializing operation.
  }
  bool live = false;
  for (unsigned bank = 0; bank < kWidth; ++bank) live |= test(rob.valid[bank],row);
  if (!live && !(rob.row_open && rob.tail == row)) {
    rob.rows &= ~bit(row);rob.head = static_cast<std::uint8_t>((row+1)&31u);
  }
}
void Core::begin_rollback(unsigned delay) {
  state_.rename.valid.fill(0);state_.decode_finished=0;
  state_.rename.branches = 0;
  state_.rob.rolling_back = true;
  state_.rob.rollback_delay=static_cast<std::uint8_t>(delay);
  state_.rob.rollback_pending=false;
  // Release the actual read/unit reservations on rollback.
  state_.execution.branch_redirect.valid=false;state_.execution.branch_redirect.mispredict=false;
  state_.execution.read_valids.fill(0);state_.execution.unit_valids.fill(0);
  for (unsigned port=0;port<kWidth;++port) {
    state_.execution.brinfo[port].valid=false;
    write_integer_read(port,0,false);write_integer_read(port,1,false);
    write_integer_result(port,false);write_branch_info(port,false);
  }
  state_.execution.csr_port.valid=false;
  divider_state().state=0;
  flush_floating();flush_memory_pipeline();
  auto& memory=state_.lsu;memory.touch_load_values(kLsqMask);memory.touch_store_values(kLsqMask);
  memory.load_valid=memory.load_address=memory.load_executed=memory.load_succeeded=0;
  memory.load_head=memory.load_tail;
  memory.load_virtual=memory.load_uncacheable=memory.load_exception=0;
  memory.load_order_fail=memory.load_observed=memory.load_forwarded=0;
  memory.load_ticket.fill(0);
  const QueueMask keep=memory.store_committed & memory.store_valid;
  memory.store_valid=keep;
  memory.store_address &= keep;memory.store_data &= keep;memory.store_succeeded &= keep;
  memory.set_store_mask(memory.store_virtual,memory.store_virtual&keep);memory.set_store_mask(memory.store_exception,memory.store_exception&keep);
  unsigned retained=0;
  for (unsigned offset=0;offset<kLsq;++offset)
    if (test(keep,static_cast<unsigned>(LsqGeometry::wrap(memory.store_head+offset)))) retained=offset+1;
  memory.store_tail=static_cast<std::uint8_t>(LsqGeometry::wrap(memory.store_head+retained));
  memory.store_commit=memory.store_tail;
  if (!test(keep,memory.store_execute)) memory.store_execute=memory.store_tail;
  state_.integer_issue.state.fill(0);
  state_.memory_issue.state.fill(0);
  state_.floating_issue.state.fill(0);
}
bool Core::rollback_row() {
  auto& rob=state_.rob;
  if (rob.rollback_delay) { --rob.rollback_delay;return false; }
  if (rob.rollback_pending) {
    const unsigned row=rob.rollback_row;
    for (int bank=int(kWidth)-1;bank>=0;--bank) {
      if (test(rob.valid[bank],row)) return_register(rob.instructions[row*kWidth+bank].decoded,true);
      rob.valid[bank] &= ~bit(row);rob.busy[bank] &= ~bit(row);
      rob.unsafe[bank] &= ~bit(row);rob.exception[bank] &= ~bit(row);
      mark_rob_row(bank,row);
    }
    rob.rows &= ~bit(row);rob.rollback_pending=false;
  }
  if (!rob.rows) {
    rob.rolling_back=rob.serializing=rob.row_open=false;
    rob.head=rob.tail;
    return true;
  }
  unsigned row=rob.row_open ? rob.tail : (rob.tail-1u)&31u;
  for (unsigned n=0;n<kRows && !test(rob.rows,row);++n) row=(row-1u)&31u;
  rob.tail=static_cast<std::uint8_t>(row);rob.row_open=false;
  rob.rollback_row=static_cast<std::uint8_t>(row);rob.rollback_pending=true;
  return false;
}

void Core::update_rob_control(QueueMask unsafe_pre, bool empty_pre,
                              std::uint8_t head_pre, std::uint8_t tail_pre) {
  auto& r=state_.rob;
  const auto head_lsb_pre=r.head_lsb;
  const bool enqueued=output_.dispatched!=0;
  const bool row_enqueued=enqueued && !r.row_open;
  // RTL rob_deq also fires when rollback moves the PRE tail, including
  // the first rollback edge before a live row is actually cleared.
  const bool rollback_dequeued=r.fsm==2 && (tail_pre!=head_pre || r.maybe_full);
  const bool row_dequeued=r.fsm==2 ? rollback_dequeued :
      (!empty_pre && (r.head!=head_pre || r.rows==0));
  const bool full=head_pre==tail_pre && r.maybe_full;
  const bool advance=!test(unsafe_pre,r.pnr) &&
      (r.pnr!=tail_pre || (full && !r.pnr_maybe_at_tail));
  if (empty_pre && enqueued) r.pnr=head_pre;
  else if ((r.fsm==1 || r.fsm==3) && advance) r.pnr=static_cast<std::uint8_t>((r.pnr+1)&31u);
  r.pnr_maybe_at_tail=!row_dequeued && (advance || r.pnr_maybe_at_tail);
  r.maybe_full=(!row_dequeued && (row_enqueued || r.maybe_full)) || output_.branch.mispredicted!=0;
  const auto old_fsm=r.fsm;
  if (old_fsm==0) r.fsm=1;
  else if (old_fsm==2) { if (empty_pre) r.fsm=1; }
  // rob.scala:909-931 delays the rollback by two edges out of s_normal so a
  // branch mispredict can drain, but out of s_wait_till_empty it reacts to the
  // exception delayed by one edge.
  else if (old_fsm==3 ? r.exception_delay1 : r.exception_delay2) r.fsm=2;
  else if (enqueued && r.serializing) r.fsm=3;
  else if (old_fsm==3 && empty_pre) r.fsm=1;
  r.exception_delay2=r.exception_delay1;r.exception_delay1=output_.exception;
  if (row_dequeued) r.head_lsb=0;
  else {
    // rob.scala registers the PRE row's first valid bank, not the banks
    // left after this edge's commits. OHToUInt(0) is zero.
    const auto valid=r.reads.head_valid;
    r.head_lsb=valid ? static_cast<std::uint8_t>(__builtin_ctz(valid)) : 0;
  }
  // Use the hardware PRE rollback state, pointers and head-bank index.
  // The native rollback helper can enter or finish on a different edge.
  if (old_fsm==2) r.tail_lsb=head_pre==tail_pre && !full
      ? head_lsb_pre : static_cast<std::uint8_t>(kWidth-1);
  else if (output_.branch.redirect || row_enqueued) r.tail_lsb=0;
  else if (enqueued && r.row_open) {
    // PriorityEncoder(~MaskLower(dis_fire)): earlier retired holes do not
    // move the tail backward within a partially dispatched row.
    r.tail_lsb=static_cast<std::uint8_t>(32u-__builtin_clz(unsigned(output_.dispatched)));
  }
}
}  // namespace chisa::boom_model::wide
