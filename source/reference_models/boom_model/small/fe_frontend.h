#pragma once
// ==========================================================================
// model frontend: the Small BOOM fetch unit (F0-F5, predictor bank, I-cache,
// ITLB) as one component whose contract registers are written into the
// model image at the write site.
//
// This replaces guiders/boom-system/frontend_state.h for the Small model.
// The class keeps the name FrontendState and the SystemGuider-facing API.
// ==========================================================================
#include <array>
#include <cstddef>
#include <cstdint>

#include "../common/frontend_contract.h"
#include "../../boom-system/components/small_icache.h"
#include "../../boom-system/components/small_machine_itlb.h"
#include "fe_bpd.h"
#include "fe_pipeline.h"
#include "generated/image.h"

namespace chisa::boom_system {



/** The FetchBuffer's cycle-start offer (read in place). */


/** Per-cycle evaluation consumed by commit(). */
struct FrontendEvaluation {
  bool reset = false;
  bool run = false;
  bool clear = false;
  components::SmallTlbCycleInputs itlb_input{};
  components::SmallFrontendTlbResponse itlb{};   // raw ITLB response
  components::SmallTlbSfence next_itlb_sfence{};
  boom_model::fe::F0F2Eval f0_f2{};
  boom_model::fe::SmallGlobalHistory redirect_ghist{};
  components::SmallICacheInputs icache_input{};
  components::SmallICacheOutputs icache{};
  // queues
  bool f4_reset = false, f4_enq_valid = false, f4_enq_ready = false, f4_deq_ready = false, f4_delay = false;
  bool fb_enq_valid = false, fb_deq_ready = false;
  std::uint8_t fb_ftq_idx = 0;
  bool ftq_upd_valid = false;
  boom_model::fe::FtqIn ftq_input{};
  bool ftq_do_commit = false;
  bool f3_main_enq_valid = false, f3_main_enq_ready = false, f3_bpd_enq_valid = false,
       f3_bpd_enq_ready = false, f3_bpd_deq_valid = false, f3_deq_ready = false;
  bool f3_fire = false;
  std::uint8_t f3_btb_mispredicts = 0;
  bool bpd_update_valid = false;
  const boom_model::fe::SmallFtqBpdUpdate* bpd_update = nullptr;
  std::uint8_t ras_read_idx = 0;
  bool ras_write_valid = false;
  std::uint8_t ras_write_idx = 0;
  std::uint64_t ras_write_addr = 0;
  boom_model::fe::BpdIn bpd_in{};
};

class FrontendState {
 public:
  explicit FrontendState(boom_model::Image& image);

  void evaluate_into(FrontendEvaluation& r, const FrontendInputs& in,
                     const BackendFrontendFeedback& feedback);
  void commit(const FrontendEvaluation& e);

  HeldFetch held_fetch(bool reset) const {
    HeldFetch h;
    h.enq_ready = fetch_buffer_.enq_ready();
    h.deq_valid = fetch_buffer_.deq_valid();
    h.uop_valid = h.deq_valid && !reset;
    h.uop = &fetch_buffer_.head_uop();
    h.group[0]=h.uop;h.group_valid=h.uop_valid ? 1 : 0;
    return h;
  }
  components::SmallICache::AcquireOffer held_icache_acquire() const {
    return icache_.held_acquire_offer(f0_f2_.held_s2_kill());
  }
  void held_itlb_cycle_inputs_into(const FrontendInputs& in, components::SmallTlbCycleInputs& r) const {
    r = components::SmallTlbCycleInputs{};
    r.reset = in.reset;
    r.request_valid = in.run && ((f0_f2_.s1().valid && !f0_f2_.s1().is_replay && !frontend_clear(in)) ||
                                 f0_f2_.s1().is_sfence);
    r.virtual_address = f0_f2_.s1().vpc;
    r.vm_enabled = in.itlb_vm_enabled;
    r.privilege = in.itlb_privilege;
    r.dynamic_execute_permission = in.itlb_dynamic_execute_permission;
    r.ptw_request_ready = in.itlb_ptw_request_ready;
    r.refill = in.itlb_refill;
    r.sfence = itlb_sfence_r_;
  }
  components::SmallTlbCycleInputs held_itlb_cycle_inputs(const FrontendInputs& in) const {
    components::SmallTlbCycleInputs r;
    held_itlb_cycle_inputs_into(in, r);
    return r;
  }

  const components::SmallFtqGetPcResponse& ftq_get_pc(unsigned port) const { return ftq_.registered_get_pc(port); }

  // diagnostic faces
  const boom_model::fe::F0F2& f0_f2_for_diagnostic() const { return f0_f2_; }
  const components::SmallICache& icache_for_diagnostic() const { return icache_; }
  const components::SmallInstructionTlb& itlb_for_diagnostic() const { return itlb_.state_for_diagnostic(); }
  const boom_model::fe::F3Queues& f3_queues_for_diagnostic() const { return f3_queues_; }
  const boom_model::fe::F3Assembler& f3_assembler_for_diagnostic() const { return f3_assembler_; }
  const boom_model::fe::FetchBuffer& fetch_buffer_for_diagnostic() const { return fetch_buffer_; }
  const boom_model::fe::F4Queue& f4_queue_for_diagnostic() const { return f4_queue_; }
  const boom_model::fe::Ftq& ftq_for_diagnostic() const { return ftq_; }
  const boom_model::fe::BpdUpdatePath& bpd_update_path_for_diagnostic() const { return bpd_update_path_; }
  const boom_model::fe::Ras& ras_for_diagnostic() const { return ras_; }
  const boom_model::fe::Bpd& bpd_for_diagnostic() const { return bpd_; }

 private:
  static bool frontend_clear(const FrontendInputs& in) {
    return in.backend_control.sfence_valid || in.backend_control.redirect_flush;
  }
  void commit_reset(bool reset);
  void write_lanes();
  void write_itlb_lanes();
  static std::uint64_t reconstructed_redirect_pc(const BackendFrontendControl& c,
                                                 const components::SmallFtqGetPcResponse& g1);
  static void redirect_history(const BackendFrontendControl& c,
                               const components::SmallFtqGetPcResponse& g0,
                               const components::SmallFtqGetPcResponse& g1,
                               boom_model::fe::SmallGlobalHistory& out);

  boom_model::Image& I_;
  boom_model::fe::Bpd bpd_;
  boom_model::fe::F0F2 f0_f2_{};
  components::SmallICache icache_{};
  boom_model::fe::F3Queues f3_queues_{};
  boom_model::fe::F3Assembler f3_assembler_{};
  boom_model::fe::F4Queue f4_queue_{};
  boom_model::fe::FetchBuffer fetch_buffer_{};
  boom_model::fe::Ftq ftq_{};
  boom_model::fe::BpdUpdatePath bpd_update_path_{};
  boom_model::fe::Ras ras_{};
  components::SmallMachineItlb itlb_{};
  components::SmallTlbSfence itlb_sfence_r_{};
  std::uint8_t ras_read_idx_ = 0;
  std::uint64_t cycle_ = 0;
  // lane gating
  std::uint64_t itlb_epoch_ = ~UINT64_C(0);
  std::uint32_t corr_ver_ = 0;
};

}  // namespace chisa::boom_system
