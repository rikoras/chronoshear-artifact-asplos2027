#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "backend.h"
#include "env_knob.h"

namespace chisa::boom_model { int g_env_generation = 0; }

namespace chisa::boom_model {

namespace components = boom_system::components;

Backend::Backend(Image* image) : image_(image) {
  core_.bind(image);
  reset();
}

void Backend::reset(std::uint64_t boot_pc) {
  core_.reset(boot_pc);
  memory_request_ = components::BoomUncachedRequest{};
  uncached_request_ = components::BoomUncachedRequest{};
  raw_attempt_ = components::BoomUncachedRequest{};
  hella_.reset();
  last_hella_outputs_ = components::SmallHellaCacheOutputs{};
  last_completion_boundary_ = BackendCompletionBoundary{};
  redirect_metadata_ = BackendFrontendControl{};
  image_->r.lsu.hella_state = hella_state_oracle();
  image_->r.lsu.hella_paddr = static_cast<std::uint32_t>(hella_paddr_oracle());
}

LsuScheduleInputs Backend::lsu_schedule_inputs(const BackendInputs& input) const {
  LsuScheduleInputs result;
  result.dmem_release_valid = input.dmem_release_valid;
  result.hella_incoming = hella_.state() == components::SmallHellaCacheShim::State::kS1;
  result.hella_wakeup = hella_.state() == components::SmallHellaCacheShim::State::kReplay;
  result.dtlb_miss_ready_registered = input.dtlb_miss_ready_registered;
  result.dmem_ordered = input.dmem_ordered;
  return result;
}

Backend::HellaSchedule Backend::hella_schedule(const BackendInputs& input) const {
  HellaSchedule result;
  const boom_lsu::Schedule schedule = core_.compute_lsu_schedule(lsu_schedule_inputs(input));
  result.incoming = schedule.hella_incoming;
  result.replay = schedule.hella_wakeup;
  result.blocks_lower_dmem = result.incoming || result.replay;
  return result;
}

bool Backend::completion_uop(const components::BoomUncachedCompletion& completion, MemUop& uop) const {
  if (completion.uses_ldq) { uop = core_.ldq_uop(completion.ldq_idx); return true; }
  if (completion.uses_stq) { uop = core_.stq_uop(completion.stq_idx); return true; }
  return false;
}

BackendCompletionBoundary Backend::evaluate_completion_boundary(
    const components::BoomUncachedCompletion& response, const components::BoomUncachedCompletion& nack,
    BackendCompletionSource source) const {
  BackendCompletionBoundary result;
  evaluate_completion_boundary_into(response, nack, source, result);
  return result;
}

void Backend::evaluate_completion_boundary_into(
    const components::BoomUncachedCompletion& response, const components::BoomUncachedCompletion& nack,
    BackendCompletionSource source, BackendCompletionBoundary& result) const {
  result = BackendCompletionBoundary{};
  result.source = source;
  result.candidate_response = response;
  result.candidate_nack = nack;
  result.response = response;
  result.nack = nack;
  const auto classify = [&](const components::BoomUncachedCompletion& raw, bool& branch_killed, bool& flush_killed) {
    if (!raw.valid) return;
    MemUop uop;
    if (!completion_uop(raw, uop)) return;
    flush_killed = core_.redirect_pending && uop.uses_ldq;
    br_mask_t mispredict_mask = 0;
    const auto& b1 = core_.br_pipe[2];
    if (b1.v && b1.mispredict) mispredict_mask = static_cast<br_mask_t>(1u << b1.tag);
    branch_killed = (uop.br_mask & mispredict_mask) != 0;
  };
  classify(response, result.response_branch_killed, result.response_flush_killed);
  classify(nack, result.nack_branch_killed, result.nack_flush_killed);
  result.response.valid &= !(result.response_branch_killed || result.response_flush_killed);
  result.nack.valid &= !(result.nack_branch_killed || result.nack_flush_killed);
}

BackendFrontendFeedback Backend::step(const BackendInputs& input,
                                      const components::BoomUncachedOutputs& uncached) {
  memory_request_ = components::BoomUncachedRequest{};
  uncached_request_ = components::BoomUncachedRequest{};
  redirect_metadata_ = BackendFrontendControl{};
  if (input.reset) {
    reset(input.boot_pc);
    return BackendFrontendFeedback{};
  }
  if (!input.run) {
    last_completion_boundary_ = BackendCompletionBoundary{};
    last_hella_outputs_ = hella_.outputs(components::SmallHellaCacheInputs{});
    return BackendFrontendFeedback{};
  }

  const LsuScheduleInputs core_schedule_input = lsu_schedule_inputs(input);
  const HellaSchedule hella_schedule_now = hella_schedule(input);

  // brupdate.b2 is a cycle-start pipeline value.
  const bool brupdate_mispredict = core_.br_pipe[3].v && core_.br_pipe[3].mispredict;
  const bool rob_flush_redirect = core_.redirect_pending;
  const StageUop brupdate_uop = core_.brupdate_b2_uop_r;
  const BrPayload brupdate_payload = core_.brupdate_b2_payload_r;

  if (kInternalSignalContract || input.fetch_offered) {
    core_.fp_uop = input.fetch;
  } else {
    // The FTQ read address still follows the held fetch wire on a bubble;
    // the rest of this large payload has no valid decode consumer.
    core_.fp_uop.ftq_idx = input.fetch.ftq_idx;
  }
  core_.fp_offered = input.fetch_offered;
  core_.fp_offered_inst = input.fetch_offered ? input.fetch.inst : 0;
  core_.fp_uop_valid = false;

  const bool uncached_pending = core_.dmem_pending.valid && is_uncacheable(core_.dmem_pending.addr);
  components::BoomUncachedCompletion uncached_core_response = uncached.response;
  components::BoomUncachedCompletion uncached_core_nack = uncached.nack;
  uncached_core_response.valid &= !uncached_core_response.is_hella;
  uncached_core_nack.valid &= !uncached_core_nack.is_hella;
  const bool use_uncached_completion = uncached_pending || uncached_core_response.valid || uncached_core_nack.valid;
  const components::BoomUncachedCompletion& response = use_uncached_completion ? uncached_core_response : input.cacheable_response;
  const components::BoomUncachedCompletion& nack = use_uncached_completion ? uncached_core_nack : input.cacheable_nack;

  evaluate_completion_boundary_into(response, nack,
                                    use_uncached_completion ? BackendCompletionSource::UncachedDebug
                                                            : BackendCompletionSource::CacheableDcache,
                                    last_completion_boundary_);
  const BackendCompletionBoundary& completion_boundary = last_completion_boundary_;
  MemUop response_uop;
  const bool response_uop_valid = response.valid && completion_uop(response, response_uop);
  const bool response_visible = completion_boundary.response.valid;
  const bool nack_visible = completion_boundary.nack.valid;
  if (nack.valid) {
    static bool dbg = false;
    static int dbg_gen = -1;
    if (dbg_gen != g_env_generation) { dbg_gen = g_env_generation; dbg = std::getenv("CHISA_NACK_DEBUG") != nullptr; }
    if (dbg)
      std::fprintf(stderr, "[NACK] core_cycle=%llu raw uses_ldq=%d uses_stq=%d ldq=%u stq=%u hella=%d uncached=%d visible=%d br_killed=%d flush_killed=%d exe_head=%u head=%u\n",
                   static_cast<unsigned long long>(core_.cycle_count()), int(nack.uses_ldq), int(nack.uses_stq),
                   unsigned(nack.ldq_idx), unsigned(nack.stq_idx), int(nack.is_hella), int(use_uncached_completion),
                   int(nack_visible), int(completion_boundary.nack_branch_killed), int(completion_boundary.nack_flush_killed),
                   unsigned(core_.stq_execute_head_dbg()), unsigned(core_.stq_head_dbg()));
  }

  core_.dmem_resp_valid = response_visible;
  core_.dmem_resp_data = response.data;
  core_.dmem_resp_uop_valid = false;
  core_.dmem_resp_nack = nack_visible;
  core_.dmem_nack_uses_ldq = nack.uses_ldq;
  core_.dmem_nack_ldq_idx = nack.ldq_idx;
  core_.dmem_nack_uses_stq = nack.uses_stq;
  core_.dmem_nack_stq_idx = nack.stq_idx;
  core_.dmem_req_ready = input.dmem_req_ready;
  core_.dmem_ordered = input.dmem_ordered;
  core_.dmem_release_valid = input.dmem_release_valid;
  core_.dmem_release_address = input.dmem_release_address;
  core_.hella_incoming_candidate = core_schedule_input.hella_incoming;
  core_.hella_wakeup_candidate = core_schedule_input.hella_wakeup;
  core_.dtlb_passthrough = input.dtlb_passthrough;
  core_.dtlb_req_ready = input.dtlb_req_ready;
  core_.dtlb_miss_ready_registered = input.dtlb_miss_ready_registered;
  core_.dtlb_resp_miss = input.dtlb_resp_miss;
  core_.dtlb_resp_uncacheable = input.dtlb_resp_uncacheable;
  core_.dtlb_resp_pf_ld = input.dtlb_resp_pf_ld;
  core_.dtlb_resp_pf_st = input.dtlb_resp_pf_st;
  core_.dtlb_resp_ae_ld = input.dtlb_resp_ae_ld;
  core_.dtlb_resp_ae_st = input.dtlb_resp_ae_st;
  core_.dtlb_resp_paddr = input.dtlb_resp_paddr;
  core_.mem_tlb_uncacheable_for_lcam = input.mem_tlb_uncacheable_for_lcam;
  core_.wfi_wakeup = input.wfi_wakeup;

  components::SmallHellaCacheInputs hella_input;
  hella_input.request = input.hella_request;
  hella_input.s1_data = input.hella_s1_data;
  hella_input.s1_kill = input.hella_s1_kill;
  hella_input.s2_kill = input.hella_s2_kill;
  hella_input.incoming_granted = hella_schedule_now.incoming;
  hella_input.replay_granted = hella_schedule_now.replay;
  hella_input.dcache_ready = input.dmem_req_ready;
  hella_input.tlb_miss = input.dtlb_resp_miss;
  hella_input.tlb_paddr = input.dtlb_resp_paddr;
  hella_input.tlb_exceptions.pf_ld = input.dtlb_resp_pf_ld;
  hella_input.tlb_exceptions.pf_st = input.dtlb_resp_pf_st;
  hella_input.tlb_exceptions.ae_ld = input.dtlb_resp_ae_ld;
  hella_input.tlb_exceptions.ae_st = input.dtlb_resp_ae_st;
  hella_input.dcache_response = input.hella_response;
  hella_input.dcache_nack = input.hella_nack;
  if (uncached.response.valid && uncached.response.is_hella) hella_input.dcache_response = uncached.response;
  if (uncached.nack.valid && uncached.nack.is_hella) hella_input.dcache_nack = uncached.nack;
  hella_.outputs_into(hella_input, last_hella_outputs_);
  core_.ext_fpu_response_connected = input.fpu_response_connected;
  core_.ext_fpu_response_valid = input.fpu_response_valid;
  core_.ext_fpu_response_data = input.fpu_response_data;
  core_.ext_fpu_response_data_bit64 = input.fpu_response_data_bit64;
  core_.ext_fpu_response_flags = input.fpu_response_flags;

  if (response_visible && response_uop_valid) {
    core_.dmem_resp_uop = response_uop;
    core_.dmem_resp_uop_valid = true;
  }
  for (int port = 0; port < boomcfg::IRF_READ_PORTS; ++port)
    core_.ext_irf_read_datas[port] = core_.prf_landed.rd(core_.rd_addr_reg[port]);
  core_.ext_ftq_get_pc0 = ExtFtqGetPc{input.ftq0_next_val, input.ftq0_pc, input.ftq0_next_pc,
                                      input.ftq0_cfi_valid, input.ftq0_cfi_idx, input.ftq0_start_bank};
  core_.ext_ftq_get_pc1 = ExtFtqGetPc{input.ftq1_next_val, input.ftq1_pc, input.ftq1_next_pc,
                                      input.ftq1_cfi_valid, input.ftq1_cfi_idx, input.ftq1_start_bank};
  core_.step();

  redirect_metadata_.redirect_from_rob_flush = core_.out_ifu_redirect_val != 0 && rob_flush_redirect;
  redirect_metadata_.redirect_from_branch_mispredict =
      core_.out_ifu_redirect_val != 0 && !rob_flush_redirect && brupdate_mispredict;
  redirect_metadata_.redirect_branch_taken = brupdate_payload.taken;
  redirect_metadata_.redirect_branch_is_br = brupdate_uop.is_br();
  redirect_metadata_.redirect_branch_is_rvc = brupdate_uop.is_rvc();
  redirect_metadata_.redirect_branch_edge_inst = brupdate_uop.edge_inst();
  redirect_metadata_.redirect_branch_pc_lob = static_cast<std::uint8_t>(brupdate_uop.pc_lob & 0x3fu);
  redirect_metadata_.redirect_branch_pc_sel = brupdate_payload.pc_sel;
  redirect_metadata_.redirect_branch_cfi_type = brupdate_payload.cfi_type;
  redirect_metadata_.redirect_branch_target_offset = brupdate_payload.target_offset;
  redirect_metadata_.redirect_branch_jalr_target = brupdate_payload.jalr_target;

  BackendFrontendFeedback fb;
  fb.ftq_deq_valid = core_.out_ifu_commit_valid != 0;
  fb.ftq_deq_idx = static_cast<std::uint8_t>(core_.out_ifu_commit_bits & (boomcfg::NUM_FTQ - 1));
  fb.ftq_redirect_valid = core_.out_ifu_redirect_val != 0;
  fb.ftq_redirect_idx = static_cast<std::uint8_t>(core_.out_ifu_redirect_ftq_idx & (boomcfg::NUM_FTQ - 1));
  fb.ftq_brupdate_mispredict = brupdate_mispredict;
  fb.ftq_brupdate_idx = static_cast<std::uint8_t>(brupdate_uop.ftq_idx & (boomcfg::NUM_FTQ - 1));
  fb.ftq_brupdate_pc_lob = static_cast<std::uint8_t>(brupdate_uop.pc_lob & 0x3fu);
  fb.ftq_brupdate_taken = brupdate_payload.taken;
  fb.ftq_get_pc_0_idx = static_cast<std::uint8_t>(core_.out_ifu_get_pc_0_ftq_idx & (boomcfg::NUM_FTQ - 1));
  fb.ftq_get_pc_1_idx = static_cast<std::uint8_t>(core_.out_ifu_get_pc_1_ftq_idx & (boomcfg::NUM_FTQ - 1));

  components::BoomUncachedRequest core_raw_attempt;
  if (core_.mem_attempt_v) {
    const MemUop& u = core_.mem_attempt_uop;
    core_raw_attempt.valid = true;
    core_raw_attempt.uses_ldq = u.uses_ldq;
    core_raw_attempt.uses_stq = u.uses_stq;
    core_raw_attempt.is_signed = u.mem_signed;
    core_raw_attempt.br_mask = u.br_mask;
    core_raw_attempt.ldq_idx = u.ldq_idx;
    core_raw_attempt.stq_idx = u.stq_idx;
    core_raw_attempt.command = u.mem_cmd;
    core_raw_attempt.size = u.mem_size;
    core_raw_attempt.address = core_.mem_attempt_addr;
    core_raw_attempt.data = core_.mem_attempt_data;
  }
  raw_attempt_ = last_hella_outputs_.dcache_request.valid ? last_hella_outputs_.dcache_request : core_raw_attempt;
  if (last_hella_outputs_.dcache_request_fire) {
    memory_request_ = last_hella_outputs_.dcache_request;
  } else if (core_.dmem_req_fired_now && core_.dmem_pending.valid) {
    const auto& pending = core_.dmem_pending;
    memory_request_.valid = true;
    memory_request_.uses_ldq = pending.uop.uses_ldq;
    memory_request_.uses_stq = pending.uop.uses_stq;
    memory_request_.is_amo = pending.uop.is_amo;
    memory_request_.is_signed = pending.uop.mem_signed;
    memory_request_.br_mask = pending.uop.br_mask;
    memory_request_.ldq_idx = pending.uop.ldq_idx;
    memory_request_.stq_idx = pending.uop.stq_idx;
    memory_request_.command = pending.uop.mem_cmd;
    memory_request_.size = pending.uop.mem_size;
    memory_request_.address = pending.addr;
    memory_request_.data = pending.data;
  }
  if (memory_request_.valid && is_uncacheable(memory_request_.address)) uncached_request_ = memory_request_;
  {
    // CHISA_DMEM_TRACE=lo-hi (core cycles): the core<->dcache interface per step.
    static long long lo = -1, hi = -1;
    static int parsed_gen = -1;
    if (parsed_gen != g_env_generation) {
      parsed_gen = g_env_generation;
      lo = hi = -1;
      if (const char* w = std::getenv("CHISA_DMEM_TRACE")) {
        lo = std::atoll(w);
        if (const char* dash = std::strchr(w, '-')) hi = std::atoll(dash + 1);
      }
    }
    const long long c = static_cast<long long>(core_.cycle_count());
    if (hi >= 0 && c >= lo && c <= hi)
      std::fprintf(stderr,
                   "[DMEM] c=%lld ready=%d ordered=%d rel=%d resp=%d nack=%d | attempt=%d/%llx fired=%d pend=%d/%llx ldq=%d stq=%d idx=%u/%u br=%02x | b1kill=%02x b1res=%02x redirect=%d flush=%d exc_prev=%d\n",
                   c, int(input.dmem_req_ready), int(input.dmem_ordered), int(input.dmem_release_valid),
                   int(input.cacheable_response.valid), int(input.cacheable_nack.valid),
                   int(core_.mem_attempt_v), static_cast<unsigned long long>(core_.mem_attempt_addr),
                   int(core_.dmem_req_fired_now), int(core_.dmem_pending.valid),
                   static_cast<unsigned long long>(core_.dmem_pending.addr),
                   int(core_.dmem_pending.uop.uses_ldq), int(core_.dmem_pending.uop.uses_stq),
                   unsigned(core_.dmem_pending.uop.ldq_idx), unsigned(core_.dmem_pending.uop.stq_idx),
                   unsigned(core_.dmem_pending.uop.br_mask),
                   unsigned(core_.b1_mispred_mask_now()), unsigned(core_.b1_resolve_mask_now()),
                   int(core_.redirect_pending), int(core_.rob_flush_now()), int(core_.rob_exception_now()));
  }
  hella_.step(hella_input);
  // HellaCache shim registers (the lsu.hella_* streams).
  image_->r.lsu.hella_state = hella_state_oracle() & 7;
  image_->r.lsu.hella_paddr = static_cast<std::uint32_t>(hella_paddr_oracle());
  return fb;
}

}  // namespace chisa::boom_model
