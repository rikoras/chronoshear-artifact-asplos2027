#pragma once
// ==========================================================================
// boom_model::Backend -- the complete-chip wrapper around boom_model::Core, with
// the same seam as boom_system::BackendState (frontend feedback/control,
// D-cache completion arbitration, HellaCache shim, PMA routing) so the
// system model can drive either core.
// ==========================================================================
#include <cstdint>

#include "../common/backend_contract.h"   // seam structs, uncached path, hella shim, PMA
#include "core.h"

namespace chisa::boom_model {

using boom_system::BackendCompletionBoundary;
using boom_system::BackendCompletionSource;
using boom_system::BackendFrontendControl;
using boom_system::BackendFrontendFeedback;
using boom_system::BackendInputs;

class Backend {
 public:
  explicit Backend(Image* image);

  void reset(std::uint64_t boot_pc = 0);
  BackendFrontendFeedback step(const BackendInputs& input,
                               const boom_system::components::BoomUncachedOutputs& uncached);
  void latch_hpm_events(const HpmEventInputs& input) { core_.latch_hpm_events(input); }

  BackendCompletionBoundary evaluate_completion_boundary(
      const boom_system::components::BoomUncachedCompletion& response,
      const boom_system::components::BoomUncachedCompletion& nack,
      BackendCompletionSource source = BackendCompletionSource::CacheableDcache) const;
  void evaluate_completion_boundary_into(
      const boom_system::components::BoomUncachedCompletion& response,
      const boom_system::components::BoomUncachedCompletion& nack,
      BackendCompletionSource source, BackendCompletionBoundary& result) const;

  const BackendCompletionBoundary& last_completion_boundary() const { return last_completion_boundary_; }
  const boom_system::components::BoomUncachedRequest& uncached_request() const { return uncached_request_; }
  const boom_system::components::BoomUncachedRequest& raw_attempt() const { return raw_attempt_; }
  const boom_system::components::BoomUncachedRequest& memory_request() const { return memory_request_; }

  DtlbLookupCandidate dtlb_lookup_candidate(const BackendInputs& input) const {
    const LsuScheduleInputs schedule_input = lsu_schedule_inputs(input);
    const boom_lsu::Schedule schedule = core_.compute_lsu_schedule(schedule_input);
    const DtlbLookupCandidate core = core_.dtlb_lookup_candidate(schedule);
    if (core.valid) return core;
    if (!schedule.hella_incoming) return core;
    const auto& request = hella_.held_request();
    DtlbLookupCandidate result;
    result.valid = true;
    result.vaddr = request.address;
    result.size = request.size;
    result.cmd = request.command;
    result.passthrough = request.physical;
    result.is_hella = true;
    return result;
  }

  const boom_system::components::SmallHellaCacheOutputs& last_hella_outputs() const { return last_hella_outputs_; }
  std::uint8_t hella_state_oracle() const { return static_cast<std::uint8_t>(hella_.state()); }
  std::uint64_t hella_paddr_oracle() const { return hella_.paddr(); }

  BackendFrontendControl cycle_start_sfence_control() const {
    BackendFrontendControl result;
    result.sfence_valid = core_.sfence_pending.valid;
    result.sfence_rs1 = core_.sfence_pending.rs1;
    result.sfence_rs2 = core_.sfence_pending.rs2;
    result.sfence_addr = core_.sfence_pending.addr;
    return result;
  }
  bool dmem_release_ready() const { return core_.out_dmem_release_ready != 0; }
  bool dmem_s1_kill() const { return core_.out_dmem_s1_kill != 0; }

  BackendFrontendControl frontend_control() const {
    BackendFrontendControl result;
    result.fetch_ready = core_.out_ifu_fetchpacket_ready != 0;
    result.sfence_valid = core_.out_ifu_sfence_valid != 0;
    result.sfence_rs1 = core_.out_ifu_sfence_rs1 != 0;
    result.sfence_rs2 = core_.out_ifu_sfence_rs2 != 0;
    result.sfence_addr = core_.out_ifu_sfence_addr;
    result.icache_invalidate = core_.out_ifu_flush_icache != 0;
    result.redirect_valid = core_.out_ifu_redirect_val != 0;
    result.redirect_pc = core_.out_ifu_redirect_pc;
    result.redirect_ftq_idx = static_cast<std::uint8_t>(core_.out_ifu_redirect_ftq_idx & 0x0fu);
    result.redirect_flush = result.redirect_valid || core_.br_kill_this_cycle || core_.xcpt_kill_start;
    result.redirect_from_rob_flush = redirect_metadata_.redirect_from_rob_flush;
    result.redirect_from_branch_mispredict = redirect_metadata_.redirect_from_branch_mispredict;
    result.redirect_branch_taken = redirect_metadata_.redirect_branch_taken;
    result.redirect_branch_is_br = redirect_metadata_.redirect_branch_is_br;
    result.redirect_branch_is_rvc = redirect_metadata_.redirect_branch_is_rvc;
    result.redirect_branch_edge_inst = redirect_metadata_.redirect_branch_edge_inst;
    result.redirect_branch_pc_lob = redirect_metadata_.redirect_branch_pc_lob;
    result.redirect_branch_pc_sel = redirect_metadata_.redirect_branch_pc_sel;
    result.redirect_branch_cfi_type = redirect_metadata_.redirect_branch_cfi_type;
    result.redirect_branch_target_offset = redirect_metadata_.redirect_branch_target_offset;
    result.redirect_branch_jalr_target = redirect_metadata_.redirect_branch_jalr_target;
    return result;
  }

  const Core& core() const { return core_; }
  Core& core_for_diagnostic() { return core_; }

 private:
  struct HellaSchedule {
    bool incoming = false;
    bool replay = false;
    bool blocks_lower_dmem = false;
  };
  LsuScheduleInputs lsu_schedule_inputs(const BackendInputs& input) const;
  HellaSchedule hella_schedule(const BackendInputs& input) const;
  bool completion_uop(const boom_system::components::BoomUncachedCompletion& completion, MemUop& uop) const;
  static bool is_uncacheable(std::uint64_t address) {
    return !boom_system::components::SmallPma::lookup(address).cacheable;
  }

  Core core_;
  Image* image_;
  boom_system::components::BoomUncachedRequest memory_request_{};
  boom_system::components::BoomUncachedRequest uncached_request_{};
  boom_system::components::BoomUncachedRequest raw_attempt_{};
  boom_system::components::SmallHellaCacheShim hella_{};
  boom_system::components::SmallHellaCacheOutputs last_hella_outputs_{};
  BackendCompletionBoundary last_completion_boundary_{};
  BackendFrontendControl redirect_metadata_{};
};

}  // namespace chisa::boom_model
