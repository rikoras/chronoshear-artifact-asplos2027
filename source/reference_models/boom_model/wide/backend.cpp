#include "backend.h"
#include "../../boom-system/phase_sub.h"
#ifdef CHISA_PHASE_TIMERS
#include <x86intrin.h>
#endif
#include "../common/fp_execute.h"
#include <stdexcept>
#include <initializer_list>

namespace chisa::boom_model::wide {
void Backend::reset(std::uint64_t boot_pc) {
  (void)boot_pc;core_.reset();hella_.reset();plan_valid_=false;
  hella_outputs_={};memory_request_={};uncached_request_={};raw_attempt_={};
  control_={};feedback_={};completion_={};rob_redirect_={};loads_={};stores_={};
  commit_valid_=jump_valid_=false;commit_index_=jump_index_=0;
  fpu_={};fdiv_={};debug_jalr_flush_=false;
}
const MemoryPlan& Backend::memory_plan(const BackendInputs& input) const {
  MemoryControl control;
  control.request_ready=input.dmem_req_ready;control.ordered=input.dmem_ordered;
  control.release_valid=input.dmem_release_valid;control.release_address=input.dmem_release_address;
  control.tlb_miss_ready=input.dtlb_miss_ready_registered;
  control.passthrough=input.dtlb_passthrough;
  control.hella_incoming=hella_.state()==components::SmallHellaCacheShim::State::kS1;
  control.hella_wakeup=hella_.state()==components::SmallHellaCacheShim::State::kReplay;
  const auto& old=plan_.control;
  if (!plan_valid_ || plan_.cycle!=core_.image().cycle ||
      old.ordered!=control.ordered || old.release_valid!=control.release_valid ||
      old.release_address!=control.release_address || old.tlb_miss_ready!=control.tlb_miss_ready ||
      old.hella_incoming!=control.hella_incoming || old.hella_wakeup!=control.hella_wakeup) {
    plan_=core_.plan_memory(control);plan_valid_=true;
  }
  // Cache readiness and translation mode do not change LSU arbitration.
  plan_.control.request_ready=control.request_ready;
  plan_.control.passthrough=control.passthrough;
  plan_.translation.passthrough=control.passthrough;
  return plan_;
}
DtlbLookupCandidate Backend::dtlb_lookup_candidate(const BackendInputs& input) const {
  const auto& plan=memory_plan(input);
  if (plan.translation.valid || !plan.schedule.hella_incoming) return plan.translation;
  const auto& held=hella_.held_request();
  return {true,held.address,held.size,held.command,held.physical,true};
}
MemoryTag Backend::completion_tag(const components::BoomUncachedCompletion& response) const {
  if (!response.valid || response.is_hella) return {};
  if (response.uses_ldq) {
    if (response.ldq_idx>=kLsq) throw std::out_of_range("Large cache LDQ response");
    return loads_[response.ldq_idx];
  }
  if (response.uses_stq) {
    if (response.stq_idx>=kLsq) throw std::out_of_range("Large cache STQ response");
    return stores_[response.stq_idx];
  }
  return {};
}
BackendCompletionBoundary Backend::evaluate_completion_boundary(
    const components::BoomUncachedCompletion& response,const components::BoomUncachedCompletion& nack,
    BackendCompletionSource source) const {
  BackendCompletionBoundary result;
  evaluate_completion_boundary_into(response,nack,source,result);return result;
}
void Backend::evaluate_completion_boundary_into(
    const components::BoomUncachedCompletion& response,const components::BoomUncachedCompletion& nack,
    BackendCompletionSource source,BackendCompletionBoundary& result) const {
  result={};result.source=source;result.candidate_response=response;result.candidate_nack=nack;
  result.response=response;result.nack=nack;
  const auto& image=core_.image();
  const auto mask=core_.pending_b1_mispredict_mask();
  const auto classify=[&](const components::BoomUncachedCompletion& raw,bool& br,bool& flush) {
    if (!raw.valid || raw.is_hella) return;
    const auto tag=completion_tag(raw);
    br=(tag.branch&mask)!=0;
    flush=raw.uses_ldq && (image.trap_pending || image.rob.rolling_back);
  };
  classify(response,result.response_branch_killed,result.response_flush_killed);
  classify(nack,result.nack_branch_killed,result.nack_flush_killed);
  result.response.valid &= !result.response_branch_killed && !result.response_flush_killed;
  result.nack.valid &= !result.nack_branch_killed && !result.nack_flush_killed;
}
components::BoomUncachedRequest Backend::request(const MemoryRequest& raw) {
  components::BoomUncachedRequest result;
  result.valid=raw.valid;result.uses_ldq=raw.tag.uses_load;result.uses_stq=raw.tag.uses_store;
  result.is_amo=raw.tag.amo;result.is_signed=raw.tag.signed_load;result.br_mask=raw.tag.branch;
  result.ldq_idx=raw.tag.load;result.stq_idx=raw.tag.store;result.command=raw.tag.command;
  result.size=raw.tag.size;result.address=raw.address;result.data=raw.data;
  return result;
}
void Backend::preview_frontend_links(const BackendInputs& input, BackendFrontendControl& c,
                                     BackendFrontendFeedback& f) const {
  c={};f={};
#ifdef CHISA_PHASE_TIMERS
  std::uint64_t t = __rdtsc();
  const auto lap = [&](unsigned slot) { const std::uint64_t now = __rdtsc(); boom_system::g_phase_sub[slot] += now - t; t = now; };
#else
  const auto lap = [](unsigned) {};
#endif
  BranchUpdate branch;Redirect branch_redirect;
  core_.preview_branch(branch,branch_redirect);
  lap(boom_system::kSubPreviewBranch);
  const bool rob_exception_pending_pre=system_record().r.coreRob.r_xcpt_val != 0;
  const Redirect redirect=rob_redirect_.valid ? rob_redirect_
      : branch_redirect.branch ? branch_redirect : Redirect{};
  const auto& image=core_.image();
  if (!(image.rob.rolling_back || image.trap_pending)) {
    const auto& plan=memory_plan(input);
    lap(boom_system::kSubPreviewPlan);
    if (plan.schedule.sfence && core_.tag_live(plan.translated,branch.mispredicted,false)) {
      c.sfence_valid=true;
      c.sfence_rs1=plan.incoming.prs1!=0;c.sfence_rs2=plan.incoming.prs2!=0;
      c.sfence_addr=plan.virtual_address;
    }
  }
  c.icache_invalidate=debug_jalr_flush_ || core_.preview_fencei_retire(branch.mispredicted);
  c.redirect_valid=redirect.valid;c.redirect_pc=redirect.pc;
  c.redirect_ftq_idx=redirect.ftq;
  c.redirect_flush=rob_exception_pending_pre || redirect.valid || branch.mispredicted;
  c.redirect_from_rob_flush=redirect.valid && !redirect.branch;
  c.redirect_from_branch_mispredict=redirect.valid && redirect.branch;
  c.redirect_branch_taken=redirect.taken;c.redirect_branch_is_br=redirect.is_br;
  c.redirect_branch_is_rvc=redirect.is_rvc;c.redirect_branch_edge_inst=redirect.edge;
  c.redirect_branch_pc_lob=redirect.pc_lob;c.redirect_branch_pc_sel=redirect.pc_select;
  c.redirect_branch_cfi_type=redirect.is_br ? 1 : 3;
  c.redirect_branch_target_offset=redirect.offset;c.redirect_branch_jalr_target=redirect.pc;
  f.ftq_redirect_valid=redirect.valid;f.ftq_redirect_idx=redirect.ftq;
  f.ftq_brupdate_mispredict=branch.redirect;
  f.ftq_brupdate_idx=redirect.ftq;f.ftq_brupdate_pc_lob=redirect.pc_lob;
  f.ftq_brupdate_taken=redirect.taken;
  const auto* oldest=core_.oldest_b1_mispredict();
  f.ftq_get_pc_1_idx=oldest ? oldest->ftq_idx : image.execution.brinfo[kWidth-1].ftq_idx;
  lap(boom_system::kSubPreviewRest);
}
BackendFrontendFeedback Backend::step(const BackendInputs& input,
                                      const components::BoomUncachedOutputs& uncached) {
  restore_cycle_zero();
  memory_request_={};uncached_request_={};raw_attempt_={};feedback_={};
  fpu_.reset=input.reset;fdiv_.reset=input.reset;fpu_.valid=false;fdiv_.in_valid=false;
  if (input.reset) { reset(input.boot_pc);fpu_.reset=fdiv_.reset=true;return feedback_; }
  if (!input.run) { completion_={};return feedback_; }
  const auto& plan=memory_plan(input);
  CycleInputs cycle;
  const bool debug_jalr_flush=debug_jalr_flush_;
  debug_jalr_flush_=false;
  const auto decoded_pre=core_.image().decode_finished;
  const bool debug_pre=core_.csr().debug;
  for (unsigned lane=0;lane<kWidth;++lane) {
    const bool offered=lane ? input.fetch_offered_g[lane] : input.fetch_offered;
    if (!offered) continue;
    // Unpacked and decoded by the frontend handoff; the edge patches its own copy.
    auto& u=cycle.decoded[lane];u=input.fetch_group[lane];
    // decode.scala:511: the shared DecodeUnit interrupt applies to every
    // offered lane except a short-forward-branch uop.
    if (input.decode_interrupt && !u.is_sfb) { u.exception=1;u.exc_cause=input.decode_interrupt_cause; }
    if (debug_pre && !(decoded_pre&(1u<<lane)) && u.is_jalr)
      debug_jalr_flush_=true;
    cycle.decoded_valid |= 1u<<lane;
  }
  cycle.wfi_wakeup=input.wfi_wakeup;
  cycle.ftq0={input.ftq0_next_val,input.ftq0_cfi_valid,input.ftq0_start_bank,
              input.ftq0_cfi_idx,input.ftq0_next_pc};
  cycle.memory.control=plan.control;cycle.memory.control.request_ready=input.dmem_req_ready;
  auto& translation=cycle.memory.translation;
  translation.passthrough=input.dtlb_passthrough;translation.miss=input.dtlb_resp_miss;
  translation.uncacheable=input.dtlb_resp_uncacheable;
  translation.page_fault_load=input.dtlb_resp_pf_ld;translation.page_fault_store=input.dtlb_resp_pf_st;
  translation.access_fault_load=input.dtlb_resp_ae_ld;translation.access_fault_store=input.dtlb_resp_ae_st;
  translation.physical=input.dtlb_resp_paddr;
  cycle.memory.prepared_plan=&plan;
  const auto prepared_request=core_.memory_request(plan,translation);
  cycle.memory.prepared_request=&prepared_request;
  const bool pending_uncached=core_.image().memory.pending.valid &&
      !components::SmallPma::lookup(core_.image().memory.pending.address).cacheable;
  auto ur=uncached.response,un=uncached.nack;
  ur.valid &= !ur.is_hella;un.valid &= !un.is_hella;
  // pending names the newer S1 request, not the S2 response. A following
  // uncached store must not hide the preceding cache hit's valid response.
  // Keep the pending hint only for inactive response payloads.
  const bool from_uncached=ur.valid || un.valid ||
      (pending_uncached && !input.cacheable_response.valid && !input.cacheable_nack.valid);
  const auto& response=from_uncached ? ur : input.cacheable_response;
  const auto& nack=from_uncached ? un : input.cacheable_nack;
  evaluate_completion_boundary_into(response,nack,
      from_uncached ? BackendCompletionSource::UncachedDebug : BackendCompletionSource::CacheableDcache,completion_);
  cycle.memory.response.valid=completion_.response.valid;
  cycle.memory.response.tag=completion_tag(response);cycle.memory.response.data=response.data;
  cycle.memory.nack.valid=completion_.nack.valid;cycle.memory.nack.tag=completion_tag(nack);

  components::SmallHellaCacheInputs hi;
  hi.request=input.hella_request;hi.s1_data=input.hella_s1_data;
  hi.s1_kill=input.hella_s1_kill;hi.s2_kill=input.hella_s2_kill;
  hi.incoming_granted=plan.schedule.hella_incoming;hi.replay_granted=plan.schedule.hella_wakeup;
  hi.dcache_ready=input.dmem_req_ready;hi.tlb_miss=input.dtlb_resp_miss;hi.tlb_paddr=input.dtlb_resp_paddr;
  hi.tlb_exceptions.pf_ld=input.dtlb_resp_pf_ld;hi.tlb_exceptions.pf_st=input.dtlb_resp_pf_st;
  hi.tlb_exceptions.ae_ld=input.dtlb_resp_ae_ld;hi.tlb_exceptions.ae_st=input.dtlb_resp_ae_st;
  hi.dcache_response=uncached.response.valid && uncached.response.is_hella ? uncached.response : input.hella_response;
  hi.dcache_nack=uncached.nack.valid && uncached.nack.is_hella ? uncached.nack : input.hella_nack;
  hella_.outputs_into(hi,hella_outputs_);
  cycle.fp.fixed={input.fpu_response_connected,input.fpu_response_valid,input.fpu_response_data,
                  static_cast<std::uint8_t>(input.fpu_response_data_bit64),input.fpu_response_flags};
  cycle.fp.divide={input.fdiv_response_connected,input.fdiv_response_valid,input.fdiv_response_data,
                   static_cast<std::uint8_t>(input.fdiv_response_data_bit64),input.fdiv_response_flags};
  // Adapt the cold double-precision arithmetic boundary to the wrapper's
  // destination precision. Small uses these same numerical/flag semantics.
  const auto& active_divide=core_.image().floating.divide_active;
  if (cycle.fp.divide.valid && active_divide.value.valid && !core_.image().floating.divide_killed &&
      (active_divide.value.uop.uopc==uopFDIV_S || active_divide.value.uop.uopc==uopFSQRT_S)) {
    const auto& stage=active_divide.value.uop;
    const auto& u=core_.instruction(stage.rob);
    const auto& registers=core_.image().floating_registers;
    const auto saved_tininess=softfloat_detectTininess;
    softfloat_detectTininess=softfloat_tininess_beforeRounding;
    const auto value=fp_compute(u,active_divide.rounding,registers[u.prs1],registers[u.prs2],0);
    softfloat_detectTininess=saved_tininess;
    const auto rec=fp_result_rec(u,value.ieee);
    cycle.fp.divide.rec_lo=static_cast<std::uint64_t>(rec);
    cycle.fp.divide.rec_hi=static_cast<std::uint8_t>((rec>>64)&1u);
    cycle.fp.divide.flags=value.exc;
  }
  cycle.fp.divide_ready=core_.image().floating.divide_buffer.sqrt
      ? input.fdiv_ready_sqrt : input.fdiv_ready_div;
  const auto* oldest=core_.oldest_b1_mispredict();
  const auto b1_ftq=oldest ? oldest->ftq_idx : core_.image().execution.brinfo[kWidth-1].ftq_idx;
  // ROB exception-pending drives the early clear before the delayed target.
  // Capture its native PRE register before Core::step can retire/clear it.
  const bool rob_exception_pending_pre=system_record().r.coreRob.r_xcpt_val != 0;
  const auto& output=core_.step(cycle);
  plan_valid_=false;
  for (auto* contexts : {&loads_,&stores_})
    for (auto& tag : *contexts) tag.branch &= static_cast<BranchMask>(~output.branch.resolved);
  raw_attempt_=hella_outputs_.dcache_request.valid ? hella_outputs_.dcache_request
                                                 : request(output.memory_ports.request);
  if (hella_outputs_.dcache_request_fire) memory_request_=hella_outputs_.dcache_request;
  else if (output.memory_ports.fired) {
    memory_request_=request(output.memory_ports.request);
    auto tag=output.memory_ports.request.tag;
    tag.branch &= static_cast<BranchMask>(~output.branch.resolved);
    if (tag.uses_load) loads_[tag.load]=tag;
    if (tag.uses_store) stores_[tag.store]=tag;
  }
  if (memory_request_.valid && !components::SmallPma::lookup(memory_request_.address).cacheable)
    uncached_request_=memory_request_;
  hella_.step(hi);
  control_={};control_.fetch_ready=output.decode_accepted;
  control_.sfence_valid=output.memory_ports.sfence;
  control_.sfence_rs1=output.memory_ports.sfence_rs1;control_.sfence_rs2=output.memory_ports.sfence_rs2;
  control_.sfence_addr=output.memory_ports.sfence_address;
  control_.icache_invalidate=output.invalidate_icache || debug_jalr_flush;
  const Redirect redirect=rob_redirect_.valid ? rob_redirect_
      : output.redirect.branch ? output.redirect : Redirect{};
  rob_redirect_=output.redirect.valid && !output.redirect.branch ? output.redirect : Redirect{};
  control_.redirect_valid=redirect.valid;control_.redirect_pc=redirect.pc;
  control_.redirect_ftq_idx=redirect.ftq;control_.redirect_flush=rob_exception_pending_pre || redirect.valid || output.branch.mispredicted;
  control_.redirect_from_rob_flush=redirect.valid && !redirect.branch;
  control_.redirect_from_branch_mispredict=redirect.valid && redirect.branch;
  control_.redirect_branch_taken=redirect.taken;control_.redirect_branch_is_br=redirect.is_br;
  control_.redirect_branch_is_rvc=redirect.is_rvc;control_.redirect_branch_edge_inst=redirect.edge;
  control_.redirect_branch_pc_lob=redirect.pc_lob;control_.redirect_branch_pc_sel=redirect.pc_select;
  control_.redirect_branch_cfi_type=redirect.is_br ? 1 : 3;
  control_.redirect_branch_target_offset=redirect.offset;control_.redirect_branch_jalr_target=redirect.pc;
  feedback_.ftq_deq_valid=output.commit_ftq_valid || commit_valid_;
  feedback_.ftq_deq_idx=commit_valid_ ? commit_index_ : output.commit_ftq;
  commit_valid_=output.sys_pc2epc_valid;commit_index_=output.sys_pc2epc;
  feedback_.ftq_redirect_valid=redirect.valid;feedback_.ftq_redirect_idx=redirect.ftq;
  feedback_.ftq_brupdate_mispredict=output.branch.redirect;
  feedback_.ftq_brupdate_idx=redirect.ftq;feedback_.ftq_brupdate_pc_lob=redirect.pc_lob;
  feedback_.ftq_brupdate_taken=redirect.taken;
  feedback_.ftq_get_pc_0_idx=output.exception || output.serializing ? output.redirect.ftq
      : jump_valid_ ? jump_index_ : input.fetch_group[0].ftq_idx;
  feedback_.ftq_get_pc_1_idx=b1_ftq;
  const auto& selected=output.integer[0];
  jump_valid_=selected.selected && (selected.uop.fu_code&FU_JMP);
  jump_index_=selected.uop.ftq_idx;

  const auto& fp=output.fp.fixed_request;
  fpu_.valid=fp.valid;fpu_.uopc=fp.uop.uopc;fpu_.imm_packed=fp.uop.imm_packed;
  fpu_.operands=fp.rec_lo;fpu_.operand_bit64=fp.rec_hi;fpu_.fcsr_rm=output.fp.rounding;
  const auto& div=output.fp.divide_request;
  fdiv_.in_valid=output.fp.divide_valid;fdiv_.sqrt_op=div.sqrt;
  fdiv_.a=div.a;fdiv_.b=div.b;fdiv_.a_bit64=div.hi&1u;fdiv_.b_bit64=div.hi&2u;
  fdiv_.rounding_mode=div.rounding;fdiv_.detect_tininess=false;
  return feedback_;
}
}  // namespace chisa::boom_model::wide
