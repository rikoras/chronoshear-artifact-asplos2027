#pragma once
#include "core.h"
#include "../common/backend_contract.h"
#include "../../boom-system/protocol/floating_point.h"
#include "../../boom-system/protocol/floating_point.h"

namespace chisa::boom_model::wide {
namespace components = chisa::boom_system::components;
using chisa::boom_system::BackendInputs;
using chisa::boom_system::BackendFrontendFeedback;
using chisa::boom_system::BackendFrontendControl;
using chisa::boom_system::BackendCompletionBoundary;
using chisa::boom_system::BackendCompletionSource;
contract::Image& system_record();
void prepare_cycle_zero();
void restore_cycle_zero();
class Backend {
 public:
  Backend() : core_(system_record()) { reset(); prepare_cycle_zero(); }
  void reset(std::uint64_t boot_pc = 0);
  BackendFrontendFeedback step(const BackendInputs&, const components::BoomUncachedOutputs&);
  DtlbLookupCandidate dtlb_lookup_candidate(const BackendInputs&) const;
  BackendCompletionBoundary evaluate_completion_boundary(
      const components::BoomUncachedCompletion&, const components::BoomUncachedCompletion&,
      BackendCompletionSource source = BackendCompletionSource::CacheableDcache) const;
  void evaluate_completion_boundary_into(
      const components::BoomUncachedCompletion&, const components::BoomUncachedCompletion&,
      BackendCompletionSource, BackendCompletionBoundary&) const;
  const BackendCompletionBoundary& last_completion_boundary() const { return completion_; }
  const components::BoomUncachedRequest& memory_request() const { return memory_request_; }
  const components::BoomUncachedRequest& uncached_request() const { return uncached_request_; }
  const components::BoomUncachedRequest& raw_attempt() const { return raw_attempt_; }
  const components::SmallHellaCacheOutputs& last_hella_outputs() const { return hella_outputs_; }
  std::uint8_t hella_state_oracle() const { return static_cast<std::uint8_t>(hella_.state()); }
  std::uint64_t hella_paddr_oracle() const { return hella_.paddr(); }
  BackendFrontendControl cycle_start_sfence_control() const { return control_; }
  // The frontend-facing control and FTQ feedback that step() will produce
  // this cycle, computed from registered state before step() runs.  Exact
  // for every field the frontend evaluation reads, except a fence.i
  // retirement (icache_invalidate); fetch_ready, the FTQ dequeue and the
  // get_pc(0) index are left at their defaults because the frontend uses
  // them only when it commits.  The caller compares the result with the
  // real values after step() and falls back when they differ.
  void preview_frontend_links(const BackendInputs&, BackendFrontendControl&,
                              BackendFrontendFeedback&) const;
  const BackendFrontendControl& frontend_control() const { return control_; }
  const BackendFrontendFeedback& frontend_feedback() const { return feedback_; }
  bool dmem_release_ready() const { return core_.outputs().memory_ports.release_ready; }
  bool dmem_s1_kill() const { return core_.outputs().memory_ports.s1_kill; }
  void latch_hpm_events(const HpmEventInputs& input) { core_.latch_hpm_events(input); }
  const Core& core() const { return core_; }
  void publish_record() { core_.publish_record(); }
  void set_record_deferred(bool on) { core_.set_record_deferred(on); }
  void set_cut_lanes(bool on) { core_.set_cut_lanes(on); }
  void export_oracles() { core_.export_oracles(); }
  Core& core_for_diagnostic() { return core_; }
  const boom_system::protocol::FpuInputs& fpu_inputs() const { return fpu_; }
  const boom_system::protocol::FDivSqrtInputs& fdivsqrt_inputs() const { return fdiv_; }
 private:
  bool debug_jalr_flush_ = false;
  const MemoryPlan& memory_plan(const BackendInputs&) const;
  MemoryTag completion_tag(const components::BoomUncachedCompletion&) const;
  static components::BoomUncachedRequest request(const MemoryRequest&);
  Core core_;
  mutable MemoryPlan plan_{};
  mutable bool plan_valid_ = false;
  components::SmallHellaCacheShim hella_;
  components::SmallHellaCacheOutputs hella_outputs_{};
  components::BoomUncachedRequest memory_request_{},uncached_request_{},raw_attempt_{};
  BackendFrontendControl control_{};
  BackendFrontendFeedback feedback_{};
  BackendCompletionBoundary completion_{};
  Redirect rob_redirect_{};
  std::array<MemoryTag,boomcfg::NUM_LDQ> loads_{},stores_{};
  bool commit_valid_ = false,jump_valid_ = false;
  std::uint8_t commit_index_ = 0,jump_index_ = 0;
  boom_system::protocol::FpuInputs fpu_{};
  boom_system::protocol::FDivSqrtInputs fdiv_{};
};
}  // namespace chisa::boom_model::wide
