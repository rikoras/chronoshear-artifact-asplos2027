#pragma once
// ============================================================================
// Small BOOM F0-F2 fetch-control pipeline.
//
// This owns the frontend's s1/s2 pipeline registers and the exact replay,
// predictor-repair, clear, and F3-enqueue control for the locked Small BOOM
// configuration (fetchWidth=4, fetchBytes=8, nBanks=1).  I-cache, ITLB, BPD,
// backend redirect, and F3 prediction results are explicit neighboring inputs;
// none are sampled from an implementation by this component.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "small_f3_queues.h"

namespace chisa::boom_system::components {

struct SmallFrontendPrediction {
  bool taken = false;
  bool is_br = false;
  bool is_jal = false;
  bool predicted_pc_valid = false;
  std::uint64_t predicted_pc = 0;
};

struct SmallFrontendPredictionResponse {
  // Group-wide lanes; a single predictor bank fills lanes 0..3 and the
  // response merge places the second bank at lanes 4.. (Large).
  std::array<SmallFrontendPrediction, boomcfg::FETCH_WIDTH> preds{};
};

struct SmallFrontendTlbResponse {
  bool miss = false;
  bool xcpt_pf_if = false;
  bool xcpt_ae_if = false;
  std::uint64_t paddr = 0;
};

struct SmallF0F2Inputs {
  bool reset = false;
  std::uint64_t reset_vector = UINT64_C(0x10040);

  bool f3_enq_ready = false;
  bool icache_resp_valid = false;
  std::uint64_t icache_resp_data = 0;
  std::uint64_t icache_resp_data_hi = 0;
  SmallFrontendTlbResponse tlb{};
  SmallFrontendPredictionResponse bpd_f1{};
  SmallFrontendPredictionResponse bpd_f2{};

  // F3 prediction-control result.  This remains a neighboring input until
  // branch target/history/RAS control is brought into the model.
  bool f3_deq_valid = false;
  bool f4_ready = false;
  std::uint64_t f3_predicted_target = 0;
  SmallGlobalHistory f3_predicted_ghist{};
  std::uint8_t f3_fsrc = 0;
  bool f3_xcpt_pf_if = false;
  bool f3_xcpt_ae_if = false;

  // Backend-to-frontend control boundary.
  bool sfence_valid = false;
  std::uint64_t sfence_addr = 0;
  bool redirect_flush = false;
  bool redirect_valid = false;
  std::uint64_t redirect_pc = 0;
  SmallGlobalHistory redirect_ghist{};
};

struct SmallF0F2Outputs {
  bool icache_req_valid = false;
  std::uint64_t icache_req_addr = 0;
  SmallGlobalHistory bpd_f0_ghist{};

  bool f1_clear = false;
  bool f2_clear = false;
  bool f2_correct_f1_ghist = false;
  bool f3_correct_f1_ghist = false;
  bool f3_correct_f2_ghist = false;

  bool f3_enq_valid = false;
  SmallFrontendResp f3_enq{};

  // Final F3 bundle source after the BSRC_3 repair override.  This is the
  // neighboring value consumed by SmallF3Assembler.
  std::uint8_t final_fsrc = 0;

  // Control sent to the future BPD/TLB/I-cache producers.
  bool s0_is_replay = false;
  bool s0_is_sfence = false;
  bool s0_s1_use_f3_bpd_resp = false;
  bool tlb_req_valid = false;
  std::uint64_t tlb_req_vaddr = 0;
  bool icache_s1_kill = false;
  std::uint64_t icache_s1_paddr = 0;
  bool icache_s2_kill = false;
};

struct SmallF1PipelineState {
  std::uint64_t vpc = 0;
  bool valid = false;
  SmallGlobalHistory ghist{};
  bool is_replay = false;
  bool is_sfence = false;
  std::uint8_t tsrc = 0;
};

struct SmallF2PipelineState {
  std::uint64_t vpc = 0;
  bool valid = false;
  SmallGlobalHistory ghist{};
  std::uint64_t ppc = 0;
  SmallFrontendTlbResponse tlb{};
  bool tlb_miss = false;
  bool replay_reg = false;
  std::uint8_t tsrc = 0;

  bool is_replay() const { return replay_reg && valid; }
};

struct SmallF0F2Evaluation {
  SmallF0F2Outputs output{};
  bool s0_valid = false;
  std::uint64_t s0_vpc = 0;
  SmallGlobalHistory s0_ghist{};
  std::uint8_t s0_tsrc = 0;
  bool s0_is_replay = false;
  bool s0_is_sfence = false;
  bool s0_s1_use_f3_bpd_resp = false;
  SmallFrontendTlbResponse s1_tlb{};
  std::uint64_t s1_ppc = 0;
  bool s1_tlb_miss = false;
  SmallGlobalHistory next_s2_ghist{};
};

class SmallF0F2 {
 public:
  SmallF0F2Evaluation evaluate(const SmallF0F2Inputs& input) const {
    return evaluate_impl(input);
  }
  void evaluate_into(const SmallF0F2Inputs& input, SmallF0F2Evaluation& result) const {
    evaluate_impl_into(input, result);
  }

  SmallF0F2Outputs outputs(const SmallF0F2Inputs& input) const {
    return evaluate(input).output;
  }

  void commit(const SmallF0F2Inputs& input,
              const SmallF0F2Evaluation& evaluation) {
    SmallF1PipelineState next_s1;
    next_s1.vpc = evaluation.s0_vpc;
    next_s1.valid = evaluation.s0_valid;
    next_s1.ghist = evaluation.s0_ghist;
    next_s1.is_replay = evaluation.s0_is_replay;
    next_s1.is_sfence = evaluation.s0_is_sfence;
    next_s1.tsrc = evaluation.s0_tsrc;

    SmallF2PipelineState next_s2;
    next_s2.vpc = s1_.vpc;
    next_s2.valid = s1_.valid && !evaluation.output.f1_clear;
    next_s2.ghist = evaluation.next_s2_ghist;
    next_s2.ppc = evaluation.s1_ppc;
    next_s2.tlb = evaluation.s1_tlb;
    next_s2.tlb_miss = evaluation.s1_tlb_miss;
    next_s2.replay_reg = s1_.is_replay;
    next_s2.tsrc = s1_.tsrc;

    // RegNext(..., false.B) reset applies only to the two valid registers.
    if (input.reset) {
      next_s1.valid = false;
      next_s2.valid = false;
    }

    replay_tlb_ = s2_.tlb;
    replay_ppc_ = s2_.ppc;
    s1_ = next_s1;
    s2_ = next_s2;
    previous_reset_ = input.reset;
  }

  void step(const SmallF0F2Inputs& input) {
    commit(input, evaluate(input));
  }

  const SmallF1PipelineState& s1() const { return s1_; }
  const SmallF2PipelineState& s2() const { return s2_; }

  /** The registered S2 exception, i.e. this cycle's icache_s2_kill.  Shared
    * with evaluate() so the light acquire-offer path cannot drift from the
    * full evaluation. */
  static bool s2_exception(const SmallF2PipelineState& s2) {
    return s2.valid && (s2.tlb.xcpt_ae_if || s2.tlb.xcpt_pf_if) &&
           !s2.is_replay();
  }
  bool held_s2_kill() const { return s2_exception(s2_); }
  bool previous_reset() const { return previous_reset_; }
  const SmallFrontendTlbResponse& replay_tlb() const {
    return replay_tlb_;
  }
  std::uint64_t replay_ppc() const { return replay_ppc_; }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);
  static constexpr std::uint64_t kPaddrMask = UINT64_C(0xffffffff);
  static constexpr std::uint8_t kBsrc1 = 0;
  static constexpr std::uint8_t kBsrc2 = 1;
  static constexpr std::uint8_t kBsrc3 = 2;
  static constexpr std::uint8_t kBsrcCore = 3;

  struct PredictionDecision {
    std::uint8_t branches = 0;
    std::uint8_t redirect_idx = boomcfg::FETCH_WIDTH - 1;
    bool do_redirect = false;
    std::uint64_t target = 0;
    SmallGlobalHistory ghist{};
  };

  static std::uint8_t fetch_mask(std::uint64_t pc) {
    return boomcfg::fetch_mask(pc);
  }

  static std::uint64_t next_fetch(std::uint64_t pc) {
    return boomcfg::fetch_next(pc) & kPcMask;
  }

  static bool histories_differ(const SmallGlobalHistory& left,
                               const SmallGlobalHistory& right) {
    // GlobalHistory.=== deliberately excludes current_saw_branch_not_taken
    // and ras_idx in BOOM.
    return left.old_history != right.old_history ||
           left.new_saw_branch_not_taken !=
               right.new_saw_branch_not_taken ||
           left.new_saw_branch_taken != right.new_saw_branch_taken;
  }

  static SmallGlobalHistory update_history(
      const SmallGlobalHistory& history, std::uint8_t branches,
      bool cfi_taken, bool cfi_is_br, std::uint8_t cfi_idx,
      bool cfi_valid, std::uint64_t pc = 0) {
    const unsigned cfi_fixed = cfi_idx & (boomcfg::FETCH_WIDTH - 1);
    const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t mask_lower =
        static_cast<std::uint8_t>((cfi_oh << 1) - 1u);
    const std::uint8_t selected = static_cast<std::uint8_t>(
        cfi_valid ? mask_lower : ((1u << boomcfg::FETCH_WIDTH) - 1u));
    const std::uint8_t taken_cfi =
        cfi_is_br && cfi_taken ? cfi_oh : 0u;
    const std::uint8_t not_taken =
        branches & selected & static_cast<std::uint8_t>(~taken_cfi);

    SmallGlobalHistory result;
    advance_global_history(history, not_taken, cfi_is_br, cfi_taken,
                           cfi_valid, cfi_fixed, pc, result);
    result.ras_idx = history.ras_idx;
    return result;
  }

  static PredictionDecision prediction(
      bool stage_valid, std::uint64_t pc,
      const SmallGlobalHistory& history,
      const SmallFrontendPredictionResponse& response) {
    PredictionDecision result;
    const std::uint8_t mask = fetch_mask(pc);
    for (std::size_t slot = 0; slot < response.preds.size(); ++slot) {
      const SmallFrontendPrediction& pred = response.preds[slot];
      if (pred.is_br && pred.predicted_pc_valid &&
          ((mask >> slot) & 1u) != 0)
        result.branches |= static_cast<std::uint8_t>(1u << slot);
      const bool redirect =
          stage_valid && ((mask >> slot) & 1u) != 0 &&
          pred.predicted_pc_valid &&
          (pred.is_jal || (pred.is_br && pred.taken));
      if (redirect && !result.do_redirect) {
        result.do_redirect = true;
        result.redirect_idx = static_cast<std::uint8_t>(slot);
      }
    }

    const SmallFrontendPrediction& selected =
        response.preds[result.redirect_idx & (boomcfg::FETCH_WIDTH - 1)];
    result.target = result.do_redirect
                        ? (selected.predicted_pc & kPcMask)
                        : next_fetch(pc);
    result.ghist = update_history(
        history, result.branches,
        selected.taken && result.do_redirect, selected.is_br,
        result.redirect_idx, result.do_redirect, pc);
    return result;
  }

  SmallF0F2Evaluation evaluate_impl(const SmallF0F2Inputs& input) const {

    SmallF0F2Evaluation result;

    evaluate_impl_into(input, result);

    return result;

  }

  void evaluate_impl_into(const SmallF0F2Inputs& input, SmallF0F2Evaluation& result) const {
    result = SmallF0F2Evaluation{};
    SmallF0F2Outputs& output = result.output;

    result.s1_tlb = s1_.is_replay ? replay_tlb_ : input.tlb;
    result.s1_ppc = (s1_.is_replay ? replay_ppc_ : input.tlb.paddr) &
                    kPaddrMask;
    result.s1_tlb_miss = !s1_.is_replay && input.tlb.miss;
    result.next_s2_ghist = s1_.ghist;

    const bool s1_fault =
        result.s1_tlb.xcpt_ae_if || result.s1_tlb.xcpt_pf_if;
    const bool s2_replay = s2_.is_replay();
    const bool s2_fault = s2_.tlb.xcpt_ae_if || s2_.tlb.xcpt_pf_if;
    const bool s2_xcpt = s2_exception(s2_);

    const PredictionDecision f1 =
        prediction(s1_.valid, s1_.vpc, s1_.ghist, input.bpd_f1);
    const PredictionDecision f2 =
        prediction(s2_.valid, s2_.vpc, s2_.ghist, input.bpd_f2);

    // F0 wires begin at WireInit defaults, then receive last-connect priority
    // from boot, F1, F2, F3, and finally backend redirect control.
    if (previous_reset_ && !input.reset) {
      result.s0_valid = true;
      result.s0_vpc = input.reset_vector & kPcMask;
      result.s0_ghist = SmallGlobalHistory{};
      result.s0_tsrc = kBsrcCore;
    }

    if (s1_.valid && !result.s1_tlb_miss) {
      result.s0_valid = !s1_fault;
      result.s0_vpc = f1.target;
      result.s0_ghist = f1.ghist;
      result.s0_is_replay = false;
      result.s0_tsrc = kBsrc1;
    }

    output.f2_correct_f1_ghist =
        histories_differ(s1_.ghist, f2.ghist);
    std::uint8_t s2_fsrc = kBsrc1;
    const bool f2_stall =
        (s2_.valid && !input.icache_resp_valid) ||
        (s2_.valid && input.icache_resp_valid && !input.f3_enq_ready);
    if (f2_stall) {
      result.s0_valid = !s2_fault || s2_replay || s2_.tlb_miss;
      result.s0_vpc = s2_.vpc;
      result.s0_is_replay = s2_.valid && input.icache_resp_valid;
      result.s0_s1_use_f3_bpd_resp = !s2_replay;
      result.s0_ghist = s2_.ghist;
      result.s0_tsrc = s2_.tsrc;
      output.f1_clear = true;
    } else if (s2_.valid && input.f3_enq_ready) {
      if (s1_.valid && s1_.vpc == f2.target &&
          !output.f2_correct_f1_ghist)
        result.next_s2_ghist = f2.ghist;
      if (!s1_.valid || s1_.vpc != f2.target ||
          output.f2_correct_f1_ghist) {
        output.f1_clear = true;
        result.s0_valid = !(s2_fault && !s2_replay);
        result.s0_vpc = f2.target;
        result.s0_is_replay = false;
        result.s0_ghist = f2.ghist;
        result.s0_tsrc = kBsrc2;
        s2_fsrc = kBsrc2;
      }
    }

    output.f3_correct_f1_ghist =
        histories_differ(s1_.ghist, input.f3_predicted_ghist);
    output.f3_correct_f2_ghist =
        histories_differ(s2_.ghist, input.f3_predicted_ghist);
    const bool f3_fire = input.f3_deq_valid && input.f4_ready;
    bool f3_restarted = false;
    bool f3_overrides_enq_ghist = false;
    if (f3_fire) {
      if (s2_.valid && s2_.vpc == input.f3_predicted_target &&
          !output.f3_correct_f2_ghist) {
        f3_overrides_enq_ghist = true;
      } else if (!s2_.valid && s1_.valid &&
                 s1_.vpc == input.f3_predicted_target &&
                 !output.f3_correct_f1_ghist) {
        result.next_s2_ghist = input.f3_predicted_ghist;
      } else {
        output.f2_clear = true;
        output.f1_clear = true;
        result.s0_valid = !(input.f3_xcpt_pf_if || input.f3_xcpt_ae_if);
        result.s0_vpc = input.f3_predicted_target & kPcMask;
        result.s0_is_replay = false;
        result.s0_ghist = input.f3_predicted_ghist;
        result.s0_tsrc = kBsrc3;
        f3_restarted = true;
      }
    }

    if (input.sfence_valid) {
      output.f1_clear = true;
      output.f2_clear = true;
      result.s0_valid = false;
      result.s0_vpc = input.sfence_addr & kPcMask;
      result.s0_is_replay = false;
      result.s0_is_sfence = true;
    } else if (input.redirect_flush) {
      output.f1_clear = true;
      output.f2_clear = true;
      result.s0_valid = input.redirect_valid;
      result.s0_vpc = input.redirect_pc & kPcMask;
      result.s0_ghist = input.redirect_ghist;
      result.s0_tsrc = kBsrcCore;
      result.s0_is_replay = false;
    }

    output.icache_req_valid = result.s0_valid;
    output.icache_req_addr = result.s0_vpc & ((UINT64_C(1) << 39) - 1);
    output.bpd_f0_ghist = result.s0_ghist;
    output.s0_is_replay = result.s0_is_replay;
    output.s0_is_sfence = result.s0_is_sfence;
    output.s0_s1_use_f3_bpd_resp = result.s0_s1_use_f3_bpd_resp;

    output.tlb_req_valid =
        (s1_.valid && !s1_.is_replay && !output.f1_clear) ||
        s1_.is_sfence;
    output.tlb_req_vaddr = s1_.vpc;
    output.icache_s1_paddr = result.s1_ppc;
    output.icache_s1_kill = input.tlb.miss || output.f1_clear;
    output.icache_s2_kill = s2_xcpt;

    output.f3_enq_valid =
        s2_.valid && !output.f2_clear &&
        (input.icache_resp_valid || (s2_fault && !s2_.tlb_miss));
    output.f3_enq.pc = s2_.vpc & kPcMask;
    output.f3_enq.data = s2_xcpt ? 0 : input.icache_resp_data;
    if constexpr (boomcfg::NBANKS > 1) {
      output.f3_enq.data_hi[0] =
          s2_xcpt ? 0 : input.icache_resp_data_hi;
      {
        static const bool ftrace = std::getenv("CHISA_DMI_TRACE") != nullptr;
        static int fshown = 0;
        if (ftrace && fshown < 30 && output.f3_enq_valid &&
            (output.f3_enq.pc >> 6) == 0x20) {
          ++fshown;
          std::fprintf(stderr, "[FSEAM] enq pc=%llx data=%016llx hi=%016llx\n",
                       (unsigned long long)output.f3_enq.pc,
                       (unsigned long long)output.f3_enq.data,
                       (unsigned long long)output.f3_enq.data_hi[0]);
        }
      }
    }
    output.f3_enq.mask = fetch_mask(s2_.vpc);
    output.f3_enq.xcpt_pf_if = s2_.tlb.xcpt_pf_if;
    output.f3_enq.xcpt_ae_if = s2_.tlb.xcpt_ae_if;
    output.f3_enq.ghist = f3_overrides_enq_ghist
                              ? input.f3_predicted_ghist
                              : s2_.ghist;
    output.f3_enq.fsrc = s2_fsrc;
    output.final_fsrc = f3_restarted ? kBsrc3 : (input.f3_fsrc & 0x03u);
    return;
  }

  SmallF1PipelineState s1_{};
  SmallF2PipelineState s2_{};
  SmallFrontendTlbResponse replay_tlb_{};
  std::uint64_t replay_ppc_ = 0;
  bool previous_reset_ = false;  // plain RegNext(reset), unreset in RTL
};

}  // namespace chisa::boom_system::components
