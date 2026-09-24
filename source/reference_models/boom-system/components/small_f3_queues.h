#pragma once
#include "../../boom_model/common/boom_config.h"
// ============================================================================
// Small BOOM F3 response queues.
//
// F3 holds the I-cache/TLB response in a depth-one pipe queue.  The matching
// branch-predictor response arrives one stage later and uses a depth-one
// pipe+flow queue.  Its enqueue valid is gated by RegNext(f3.enq.ready), which
// is deliberately represented as separate unreset state here.
// ============================================================================

#include <array>
#include <cstdint>

namespace chisa::boom_system::components {

struct SmallGlobalHistory {
  std::uint64_t old_history = 0;
  bool current_saw_branch_not_taken = false;
  bool new_saw_branch_not_taken = false;
  bool new_saw_branch_taken = false;
  std::uint8_t ras_idx = 0;
  // GlobalHistory.histories(bank): bank 1 derives from bank 0's outcome
  // flags of the same fetch group (only bank 0 exists on Small).
  std::uint64_t history_word(int b) const {
    if (b == 0) return old_history;
    if (new_saw_branch_taken) return (old_history << 1) | UINT64_C(1);
    if (new_saw_branch_not_taken) return old_history << 1;
    return old_history;
  }
};

/** GlobalHistory.update without the RAS side: fills the three history
  * fields of `result` from this group's branch outcomes.  `not_taken` is
  * already masked to the lanes before the taken CFI; `pc` feeds the
  * single-bank test and is unused with one bank. */
inline void advance_global_history(const SmallGlobalHistory& history,
                                   std::uint8_t not_taken, bool cfi_is_br,
                                   bool cfi_taken, bool cfi_valid,
                                   unsigned cfi_fixed, std::uint64_t pc,
                                   SmallGlobalHistory& result) {
  result.current_saw_branch_not_taken = false;
  if constexpr (boomcfg::NBANKS == 1) {
    (void)cfi_fixed;
    (void)pc;
    const bool saw_not_taken =
        not_taken != 0 || history.current_saw_branch_not_taken;
    if (cfi_is_br && cfi_taken && cfi_valid)
      result.old_history = (history.old_history << 1) | UINT64_C(1);
    else if (saw_not_taken)
      result.old_history = history.old_history << 1;
    else
      result.old_history = history.old_history;
    result.new_saw_branch_not_taken = false;
    result.new_saw_branch_taken = false;
  } else {
    // frontend.scala nBanks==2: base on histories(1); the second bank's
    // outcome rides the new_saw flags into the next derivation.
    constexpr unsigned kBankWidth = boomcfg::FETCH_WIDTH / boomcfg::NBANKS;
    constexpr std::uint8_t kBank0Mask =
        static_cast<std::uint8_t>((1u << kBankWidth) - 1u);
    const std::uint64_t base = history.history_word(1);
    const bool cfi_in_bank_0 =
        cfi_valid && cfi_taken && cfi_fixed < kBankWidth;
    const bool may_not_be_dual =
        boomcfg::fetch_may_not_be_dual_banked(pc);
    const bool ignore_second_bank = cfi_in_bank_0 || may_not_be_dual;
    const bool first_bank_saw_not_taken =
        (not_taken & kBank0Mask) != 0 ||
        history.current_saw_branch_not_taken;
    if (ignore_second_bank) {
      result.old_history = base;
      result.new_saw_branch_not_taken = first_bank_saw_not_taken;
      result.new_saw_branch_taken = cfi_is_br && cfi_in_bank_0;
    } else {
      if (cfi_is_br && cfi_in_bank_0)
        result.old_history = (base << 1) | UINT64_C(1);
      else if (first_bank_saw_not_taken)
        result.old_history = base << 1;
      else
        result.old_history = base;
      result.new_saw_branch_not_taken =
          static_cast<std::uint8_t>(not_taken >> kBankWidth) != 0;
      result.new_saw_branch_taken =
          cfi_valid && cfi_taken && cfi_is_br && !cfi_in_bank_0;
    }
  }
}

struct SmallFrontendResp {
  std::uint64_t pc = 0;
  std::uint64_t data = 0;
  // Fetch words for banks 1.. (empty on Small).  data_word(0) == data.
  std::array<std::uint64_t, boomcfg::NBANKS - 1> data_hi{};
  std::uint64_t data_word(int i) const { return i == 0 ? data : data_hi[i - 1]; }
  std::uint8_t mask = 0;
  bool xcpt_pf_if = false;
  bool xcpt_ae_if = false;
  SmallGlobalHistory ghist{};
  std::uint8_t fsrc = 0;
};

struct SmallBpdPrediction {
  bool taken = false;
  bool predicted_pc_valid = false;
  std::uint64_t predicted_pc = 0;
};

struct SmallBpdResponse {
  std::uint64_t pc = 0;
  std::array<SmallBpdPrediction, boomcfg::FETCH_WIDTH> preds{};
  std::array<std::uint32_t, boomcfg::BPD_META_WORDS> meta{};  // 120 bits/bank
};

struct SmallF3QueueInputs {
  bool reset = false;
  bool clear = false;
  bool main_enq_valid = false;
  SmallFrontendResp main_enq{};
  SmallBpdResponse bpd_enq{};
  bool deq_ready = false;
};

struct SmallF3QueueOutputs {
  bool main_enq_ready = false;
  bool main_deq_valid = false;
  SmallFrontendResp main_deq{};
  bool bpd_enq_valid = false;
  bool bpd_enq_ready = false;
  bool bpd_deq_valid = false;
  SmallBpdResponse bpd_deq{};
};

class SmallF3Queues {
 public:
  SmallF3QueueOutputs outputs(const SmallF3QueueInputs& input) const {

    SmallF3QueueOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallF3QueueInputs& input, SmallF3QueueOutputs& result) const {
    result = SmallF3QueueOutputs{};

    // f3: Queue(entries=1, pipe=true, flow=false).
    result.main_enq_ready = !main_full_ || input.deq_ready;
    result.main_deq_valid = main_full_;
    result.main_deq = main_payload_;

    // f3_bpd_resp: Queue(entries=1, pipe=true, flow=true).  When empty,
    // deq.bits bypasses the RAM and carries this cycle's BPD response.
    result.bpd_enq_valid = main_full_ && prev_main_enq_ready_;
    result.bpd_enq_ready = !bpd_full_ || input.deq_ready;
    result.bpd_deq_valid = bpd_full_ || result.bpd_enq_valid;
    result.bpd_deq = bpd_full_ ? bpd_payload_ : input.bpd_enq;
    return;
  }

  void commit(const SmallF3QueueInputs& input,
              const SmallF3QueueOutputs& output) {
    const bool main_do_enq = input.main_enq_valid && output.main_enq_ready;
    const bool main_do_deq = output.main_deq_valid && input.deq_ready;
    const bool bpd_do_enq = output.bpd_enq_valid && output.bpd_enq_ready;
    const bool bpd_do_deq = output.bpd_deq_valid && input.deq_ready;

    if (main_do_enq) main_payload_ = input.main_enq;
    if (main_do_enq != main_do_deq) main_full_ = main_do_enq;
    // Queue(flow=true): an empty queue with a ready consumer passes the entry
    // through without writing the ram (chisel3 Queue: do_enq := false).
    if (bpd_do_enq && !(!bpd_full_ && input.deq_ready)) bpd_payload_ = input.bpd_enq;
    if (bpd_do_enq != bpd_do_deq) bpd_full_ = bpd_do_enq;

    // Queue resets clear occupancy but leave their payload RAMs untouched.
    if (input.reset || input.clear) {
      main_full_ = false;
      bpd_full_ = false;
    }

    // Plain RegNext: f3_clear does not reset it, and the operand is the
    // cycle-start ready value even on a reset edge.
    prev_main_enq_ready_ = output.main_enq_ready;
  }

  void step(const SmallF3QueueInputs& input) {
    commit(input, outputs(input));
  }

  const bool& main_full() const { return main_full_; }
  const bool& bpd_full() const { return bpd_full_; }
  const bool& previous_main_enq_ready() const { return prev_main_enq_ready_; }
  const SmallFrontendResp& main_payload() const { return main_payload_; }
  const SmallBpdResponse& bpd_payload() const { return bpd_payload_; }

 private:
  SmallFrontendResp main_payload_{};
  SmallBpdResponse bpd_payload_{};
  bool main_full_ = false;
  bool bpd_full_ = false;
  bool prev_main_enq_ready_ = false;
};

}  // namespace chisa::boom_system::components
