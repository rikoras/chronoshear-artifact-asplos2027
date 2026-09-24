#include "core.h"
#include "record_fields.h"
#include "record_fields.h"
#include <initializer_list>
#include "../common/fp_execute.h"
#include "../common/diagnostic_monitor.h"
#include "diagnostics/record_dump.h"

namespace chisa::boom_model::wide {
Core::Core(contract::Image& record) : record_(&record) { reset(); }
void Core::reset() {
  rob_rows_dirty_ = {}; rob_branch_dirty_ = {}; rob_uop_dirty_ = {}; rename_dirty_ = 0; csr_dirty_ = false; step_batch_pending_ = false;
  lsq_flags_ = {};
  state_ = Image{};output_={};fields::reset_core(*record_);
  reset_domain(state_.rename.integer,boomcfg::NUM_PREGS);
  reset_domain(state_.rename.floating,boomcfg::NUM_FPREGS);
  state_.integer_issue.kind = QueueKind::Integer;
  state_.memory_issue.kind = QueueKind::Memory;
  state_.floating_issue.kind = QueueKind::Floating;
  bind_issue_columns();
  auto div=divider_state();
  div.state=div.divisor_hi=div.remainder_hi=0;div.negate=false;
  div.divisor=div.remainder[0]=div.remainder[1]=0;
  for (unsigned port=0;port<kWidth;++port) {
    write_integer_read(port,0,false);write_integer_read(port,1,false);
    write_integer_result(port,false);write_branch_info(port,false);
  }
  reset_csr();
  // This carrier publishes the raw IntToFP pipe register, not the boxed
  // response of an idle wrapper. The generated register starts at zero.
  state_.floating.ifpu_rec_lo=0;
  state_.floating.ifpu_rec_hi=0;
  architectural_.reset();held_debug_ = false;write_fp_record();
}
const CycleOutputs& Core::step(CycleInputs& input) {
  // The frontend consumes the registered ROB redirect on this edge. Its
  // PRE fetch packet is still the wrong path and must not refill rename.
  const bool rob_flush_pre=output_.rob_flush;
  output_={};auto& out=output_;
  // Rename observes the registered flush on the following edge.
  // The retiring serial operation does not close a partially filled ROB row.
  if (rob_flush_pre) {
    state_.rename.branches=0;
    state_.rename.valid.fill(0);
    state_.decode_finished=0;
  }
  ++state_.cycle;architectural_.begin_cycle();
  begin_rob_reads();
  const auto rob_head_pre=state_.rob.head,rob_tail_pre=state_.rob.tail;
  QueueMask rob_unsafe_pre=0, rob_live_pre=0;
  for (unsigned bank=0;bank<kWidth;++bank) {
    rob_unsafe_pre |= state_.rob.valid[bank]&(state_.rob.unsafe[bank]|state_.rob.exception[bank]);
    rob_live_pre |= state_.rob.valid[bank];
  }
  const bool rob_empty_pre=rob_head_pre==rob_tail_pre && !test(rob_live_pre,rob_head_pre);
  // rob.scala:897 clears ROB readiness while the held exception register is
  // set, so no lane dispatches on such an edge. Read the register before this
  // edge's retirement can clear it.
  const bool rob_exception_pending_pre=record_->r.coreRob.r_xcpt_val != 0;
  const auto load_allocation_pre=state_.lsu.load_valid;
  const auto store_allocation_pre=state_.lsu.store_valid;
  const auto rename_valid_pre=state_.rename.pending_mask();
  const bool disable_ooo_pre=(state_.csr.custom_0 & UINT64_C(8))!=0;
  const auto load_head_pre=state_.lsu.load_head, store_head_pre=state_.lsu.store_head;
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    sample("core","rob_control",state_.cycle,Layer::Internal,Phase::Pre,
        {{"fsm",state_.rob.fsm},{"head",rob_head_pre},{"tail",rob_tail_pre},
         {"head_lsb",state_.rob.head_lsb},{"tail_lsb",state_.rob.tail_lsb},
         {"maybe_full",state_.rob.maybe_full},{"row_open",state_.rob.row_open},
         {"empty",rob_empty_pre},{"rolling_back",state_.rob.rolling_back},
         {"trap_pending",state_.trap_pending},{"rob_flush",rob_flush_pre}});
  );
  if (state_.rob.rolling_back || state_.trap_pending) {
    const bool entering=csr_cycle_start();
    // Committed stores and an already-started cold divider keep progressing
    // while speculative backend rows are being rolled back.
    prepare_memory(input,out,true);
    prepare_floating(input,out,true);
    capture_rob_writeback_reads(input);
    launch_memory(input,out);
    launch_floating(input,out);
    out.rollback_done=!entering && rollback_row();
    csr_cycle_end(input,out);
    update_rob_control(rob_unsafe_pre,rob_empty_pre,rob_head_pre,rob_tail_pre);

    CHISA_DIAG(
      using namespace ::chisa::diagnostic;
      require("core","rollback_no_dispatch",state_.cycle,Layer::Internal,Phase::Post,
          out.dispatched==0,{{"dispatched",out.dispatched},{"fsm",state_.rob.fsm},
          {"rolling_back",state_.rob.rolling_back},{"head",state_.rob.head},{"tail",state_.rob.tail}});
      require("core","rob_bank_geometry",state_.cycle,Layer::Internal,Phase::Post,
          state_.rob.head_lsb<kWidth && state_.rob.tail_lsb<kWidth,
          {{"width",kWidth},{"head_lsb",state_.rob.head_lsb},{"tail_lsb",state_.rob.tail_lsb},
           {"fsm",state_.rob.fsm},{"row_open",state_.rob.row_open}});
      sample("core","rob_control",state_.cycle,Layer::Internal,Phase::Post,
          {{"fsm",state_.rob.fsm},{"head",state_.rob.head},{"tail",state_.rob.tail},
           {"head_lsb",state_.rob.head_lsb},{"tail_lsb",state_.rob.tail_lsb},
           {"maybe_full",state_.rob.maybe_full},{"row_open",state_.rob.row_open},
           {"rolling_back",state_.rob.rolling_back},{"rollback_done",out.rollback_done}});
    );

    finish_step_record();
    return out;
  }
  floating_availability(input);
  prepare_execution(input,out);out.branch=input.branch;
  prepare_memory(input,out);
  prepare_floating(input,out);
  capture_rob_writeback_reads(input);
  csr_cycle_start();
  input.commit_allowed=input.commit_allowed && !state_.csr.wfi && !state_.csr.cease;

  // PRE views are captured once. Later same-edge writes do not change the
  // commit eligibility, freelist selection or collapse-vacancy decisions.
  const auto busy_before = state_.rob.busy;
  const PhysicalMask integer_free = state_.rename.integer.free;
  const PhysicalMask floating_free = state_.rename.floating.free;
  const BranchMask allocation_view = state_.rename.branches;
  const std::array<QueueMask,3> occupied{{state_.integer_issue.occupied_mask(),
      state_.memory_issue.occupied_mask(),state_.floating_issue.occupied_mask()}};
  // Large instantiates BasicDispatcher, exactly as Small does. Its ready
  // mask is the AND of all IQ ready masks, indexed by original decode lane.
  // Counting only the queues used by earlier uops would implement the
  // different CompactingDispatcher and let RTL/model ROB enqueues diverge.
  const unsigned dispatch_credit=std::min({state_.integer_issue.available,
      state_.memory_issue.available,state_.floating_issue.available});
  const bool rob_ready = rob_can_dispatch();
  // Match ROB.io.empty from the PRE head/tail and head-bank valids.
  // A same-edge retirement or store drain must not release dispatch early.
  const bool rob_empty_before = rob_empty_pre;

  if (input.branch.redirect) {
    CHISA_DIAG(
      using namespace ::chisa::diagnostic;
      if (RecordDump::instance().selected(state_.cycle))
        checkpoint("rename","redirect-restore",state_.cycle,Layer::Internal,
            {{"branches_pre",state_.rename.branches},{"surviving",input.branch.surviving},
             {"tag",input.branch.tag},{"mispredicted",input.branch.mispredicted},
             {"resolved",input.branch.resolved},{"rename_valid_pre",rename_valid_pre}});
    );
    state_.decode_finished=0;
    restore_rename(input.branch.tag);
    state_.rename.branches = input.branch.surviving;
  }
  for (unsigned lane=0;lane<kWidth;++lane) {
    auto& held=state_.rename.held[lane];
    if (held.br_mask & input.branch.mispredicted)
      state_.rename.valid[lane]=0;
    if(held.br_mask&input.branch.resolved) {
      held.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
      // rename-stage.scala:133 rewrites the entry's mask on every edge, so the
      // published field has to follow the value here as well as at admission.
      // Only this configuration's contract carries the field.
      for(unsigned domain=0;domain<2;++domain)
        write_record(*record_,fields::rename_uop_br_mask[domain][lane],held.br_mask);
#endif
    }
  }
  state_.rename.branches &= static_cast<BranchMask>(~input.branch.resolved);
  for (auto* queue : {&state_.integer_issue,&state_.memory_issue,&state_.floating_issue})
    resolve_issue(*queue,input.branch);
  resolve_rob(input.branch);resolve_memory(input.branch);

  std::array<bool,12> accepted_completion{};
  for (unsigned i = 0; i < input.completions.size(); ++i)
    accepted_completion[i] = complete(input.completions[i]);
  commit(busy_before,input.commit_allowed,out);
  for (const auto& retired : out.retired)
    if (retired.valid) state_.memory.commit_load_head=false;

  select_issue(input,out);

  std::array<MicroOp,kWidth> dispatched{};
  std::array<std::uint8_t,3> dispatch_mask{};
  std::uint8_t integer_consumed = 0, floating_consumed = 0;
  bool unique_dispatched = false;
  if (rob_ready && !rob_exception_pending_pre && !rob_flush_pre && !input.branch.mispredicted && !input.branch.redirect && !out.exception && !out.serializing && !state_.csr.wfi && !state_.csr.cease) {
    for (unsigned lane = 0; lane < kWidth; ++lane) {
      if (!(state_.rename.pending_mask() & (1u << lane))) continue;
      if (lane>=dispatch_credit) break;
      const auto& held = state_.rename.held[lane];
      // Fences finish through ROB/LSU ordering and never need an issue slot.
      const bool needs_execution = !held.exception && !held.is_fence && !held.is_fencei;
      const bool mem = needs_execution && (held.iq_type & IQT_MEM) != 0;
      const bool integer_target = needs_execution && !mem && (held.iq_type & IQT_INT);
      const bool fp = needs_execution && (held.iq_type & IQT_FP) != 0;
      if (!memory_available(held,load_head_pre,store_head_pre) ||
          (held.uses_ldq && test(load_allocation_pre,state_.lsu.load_tail)) ||
          (held.uses_stq && test(store_allocation_pre,state_.lsu.store_tail))) break;
      if ((held.is_unique || disable_ooo_pre) &&
          (!rob_empty_before || store_allocation_pre!=0 || !input.memory.control.ordered ||
           (rename_valid_pre & ((1u<<lane)-1u)))) break;
      // rename-stage.scala:336 stalls the lane on the destination type and the
      // lane's allocation valid alone; it does not look at ldst_val or a zero
      // destination. Those terms belong to the allocation request, so they stay
      // on the consumption below: a uop with an integer destination type but no
      // architectural destination still waits for a free physical register.
      const bool needs_integer_selection = held.dst_rtype == RT_FIX;
      const bool needs_float_selection = held.dst_rtype == RT_FLT;
      const bool writes_integer = held.ldst_val && needs_integer_selection && held.ldst != 0;
      const bool writes_float = held.ldst_val && needs_float_selection;
      if ((needs_integer_selection && !state_.rename.integer.selected_valid[lane]) ||
          (needs_float_selection && !state_.rename.floating.selected_valid[lane])) break;
      auto& u=dispatched[lane];
      rename_dispatch(u,lane);
      u.rob_idx = static_cast<std::uint8_t>(RobGeometry::encode(state_.rob.tail,lane));
      allocate_memory(u);
      rob_enqueue(u,lane,held_debug_);
      if (u.is_sys_pc2epc) { out.sys_pc2epc_valid=true;out.sys_pc2epc=u.ftq_idx; }
      if (writes_integer) integer_consumed |= 1u<<lane;
      if (writes_float) floating_consumed |= 1u<<lane;
      if (integer_target) {
        dispatch_mask[0] |= 1u<<lane;
      }
      if (mem) {
        dispatch_mask[1] |= 1u<<lane;
      }
      if (fp) {
        dispatch_mask[2] |= 1u<<lane;
      }
      out.dispatched |= 1u<<lane;
      state_.rename.valid[lane]=0;
      if (u.is_unique) { unique_dispatched = true;break; }
    }
  }
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  if (cut_lanes_) {
    // core.scala:732-734: the registered "dispatched a sys_pc2epc" flag and,
    // in the cycle it holds, the first valid dispatch lane's FTQ index.
    write_record(*record_,fields::core_sys_pc2epc_ftq_r,
                 state_.rename.held[rename_valid_pre ? __builtin_ctz(rename_valid_pre) : 0].ftq_idx);
    sys_pc2epc_r_=out.dispatched && dispatched[__builtin_ctz(out.dispatched)].is_sys_pc2epc;
    write_record(*record_,fields::core_sys_pc2epc_r,sys_pc2epc_r_);
  }
#endif
  // The ROB advances on a non-stalled dispatch group. Decode's partial
  // fetch row can span several rename/dispatch groups with different holes.
  if (out.dispatched && !state_.rename.pending_mask()) rob_close_row();
  if (unique_dispatched) state_.rob.serializing = true;
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    require("core","dispatch_pre_control",state_.cycle,Layer::Internal,Phase::Post,
        !out.dispatched || (rob_ready && !rob_exception_pending_pre && !rob_flush_pre &&
                            !input.branch.mispredicted &&
                            !input.branch.redirect && !out.exception && !out.serializing),
        {{"dispatched",out.dispatched},{"ready_pre",rob_ready},{"flush_pre",rob_flush_pre},
         {"exception_pending_pre",rob_exception_pending_pre},
         {"kill",input.branch.mispredicted},{"redirect",input.branch.redirect},
         {"exception",out.exception},{"serializing",out.serializing}});
    for(unsigned lane=0;lane<kWidth;++lane) {
      if(!(out.dispatched&(1u<<lane)))continue;
      const auto& u=dispatched[lane];
      if(u.is_unique || disable_ooo_pre)
        require("core","serial_dispatch_drain",state_.cycle,Layer::Internal,Phase::Post,
            rob_empty_before && store_allocation_pre==0 && input.memory.control.ordered &&
            !(rename_valid_pre & ((1u<<lane)-1u)),
            {{"lane",lane},{"rob",u.rob_idx},{"empty_pre",rob_empty_before},
             {"stores_pre",store_allocation_pre},{"ordered",input.memory.control.ordered},
             {"rename_pre",rename_valid_pre},{"unique",u.is_unique},{"disable_ooo_pre",disable_ooo_pre}});
    }
  );
  collapse(state_.integer_issue,occupied[0],out.integer.data(),kWidth,dispatched,dispatch_mask[0]);
  collapse(state_.memory_issue,occupied[1],&out.memory,1,dispatched,dispatch_mask[1]);
  collapse(state_.floating_issue,occupied[2],&out.floating,1,dispatched,dispatch_mask[2]);

  // Poison pulses expire after their PRE value has reached moved slots.
  for (auto* queue : {&state_.integer_issue,&state_.memory_issue,&state_.floating_issue})
    queue->clear_poison();

  // Slow writeback wakeups update next-cycle queue readiness after selection.
  const auto wake_all = [&](const Wakeup& wakeup) {
    if (wakeup.floating) wake(state_.floating_issue,wakeup);
    else { wake(state_.integer_issue,wakeup);wake(state_.memory_issue,wakeup); }
  };
  for (unsigned i = 0; i < input.completions.size(); ++i) {
    if (!accepted_completion[i]) continue;
    const auto& c = input.completions[i];
    if (c.writes_integer) wake_all({true,false,false,c.pdst});
    if (c.writes_float) wake_all({true,true,false,c.pdst});
  }
  for (const auto& wakeup : input.wakeups) wake_all(wakeup);
  preselect(state_.rename.integer,integer_free,integer_consumed);
  preselect(state_.rename.floating,floating_free,floating_consumed);
  rename_bypass_held();
  if (!out.serializing && !rob_flush_pre && !input.branch.mispredicted && !input.branch.redirect && !out.exception && !state_.csr.wfi && !state_.csr.cease) {
    for (unsigned lane=0;lane<kWidth;++lane) {
      if (!(input.decoded_valid & (1u<<lane))) continue;
      csr_logic::decode_legality(input.decoded[lane],state_.csr);
      if (!state_.csr.debug && (input.debug_interrupt || state_.csr.single_stepped)) {
        input.decoded[lane].exception=1;
        input.decoded[lane].exc_cause=(UINT64_C(1)<<63)|14u;
      }
    }
    out.decode_accepted = accept_decode(input.decoded,input.decoded_valid,allocation_view,state_.csr.debug);
  }
  if (out.exception || out.serializing) {
    for (auto& grant : out.integer) grant.valid=false;
    out.memory.valid=out.floating.valid=false;
  }
  launch_execution(input,out);
  launch_memory(input,out);
  launch_floating(input,out);
  csr_cycle_end(input,out);out.rob_flush=out.exception || out.serializing;
  update_rob_control(rob_unsafe_pre,rob_empty_pre,rob_head_pre,rob_tail_pre);

  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    require("core","rob_bank_geometry",state_.cycle,Layer::Internal,Phase::Post,
        state_.rob.head_lsb<kWidth && state_.rob.tail_lsb<kWidth,
        {{"width",kWidth},{"head_lsb",state_.rob.head_lsb},{"tail_lsb",state_.rob.tail_lsb},
         {"fsm",state_.rob.fsm},{"row_open",state_.rob.row_open}});
    sample("core","rob_control",state_.cycle,Layer::Internal,Phase::Post,
        {{"fsm",state_.rob.fsm},{"head",state_.rob.head},{"tail",state_.rob.tail},
         {"head_lsb",state_.rob.head_lsb},{"tail_lsb",state_.rob.tail_lsb},
         {"maybe_full",state_.rob.maybe_full},{"row_open",state_.rob.row_open},
         {"head_pre",rob_head_pre},{"tail_pre",rob_tail_pre},{"empty_pre",rob_empty_pre},
         {"dispatched",out.dispatched},{"serializing",out.serializing}});
  );

  finish_step_record();
  return out;
}
}  // namespace chisa::boom_model::wide
