#pragma once
// ============================================================================
// Small BOOM frontend branch-predictor update path.
//
// F3 may discover that a BTB-cached JAL target is wrong.  Those fast repairs
// wait in a plain two-entry Chisel Queue.  A fixed-priority Arbiter then sends
// either the FTQ update (input 0, highest priority) or the queued correction
// (input 1) to the branch predictor; the predictor is always ready.
// ============================================================================

#include <array>
#include <cstdint>

#include "queue.h"
#include "small_ftq.h"

namespace chisa::boom_system::components {

struct SmallBpdUpdatePathInputs {
  bool reset = false;

  bool f3_fire = false;
  std::uint8_t f3_btb_mispredicts = 0;
  SmallFetchBundle f3_bundle{};

  bool ftq_valid = false;
  SmallFtqBpdUpdate ftq_update{};
  // When set, the F3 bundle is read from the caller's evaluation object
  // instead of the copy in `f3_bundle`.
  const SmallFetchBundle* f3_bundle_ref = nullptr;
};

struct SmallBpdUpdatePathOutputs {
  bool correction_enq_valid = false;
  bool correction_enq_ready = false;
  SmallFtqBpdUpdate correction_enq{};

  bool correction_deq_valid = false;
  bool correction_deq_ready = false;
  SmallFtqBpdUpdate correction_deq{};

  bool ftq_ready = true;
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

class SmallBpdUpdatePath {
 public:
  SmallBpdUpdatePathOutputs outputs(
      const SmallBpdUpdatePathInputs& input) const {
    SmallBpdUpdatePathOutputs result;
    result.correction_enq_valid =
        input.f3_fire && (input.f3_btb_mispredicts & kFetchMask) != 0;
    result.correction_enq = make_correction(input);
    result.correction_deq_valid = queue_.deq_valid(false);
    // deq.bits is the ram word at the dequeue pointer whether or not the
    // entry is valid; the update arbiter shows it whenever the FTQ is idle.
    result.correction_deq = payloads_[queue_.deq_ptr()];

    // Chisel Arbiter gives input zero fixed priority.  out.ready is tied high,
    // so input zero is always ready and input one is ready only when zero is
    // not valid.
    result.correction_deq_ready = !input.ftq_valid;
    result.correction_enq_ready =
        queue_.enq_ready(result.correction_deq_ready);
    result.update_valid = input.ftq_valid || result.correction_deq_valid;
    result.update = input.ftq_valid ? input.ftq_update
                                    : result.correction_deq;
    return result;
  }

  void commit(const SmallBpdUpdatePathInputs& input,
              const SmallBpdUpdatePathOutputs& output) {
    if (!input.reset && output.correction_enq_valid &&
        output.correction_enq_ready)
      payloads_[queue_.enq_ptr()] = output.correction_enq;
    queue_.step(input.reset, output.correction_enq_valid,
                output.correction_deq_ready);
  }

  void step(const SmallBpdUpdatePathInputs& input) {
    commit(input, outputs(input));
  }

  // References into the queue (the stream masks the value to its width).
  const std::uint32_t& enq_ptr() const { return queue_.enq_ptr(); }
  const std::uint32_t& deq_ptr() const { return queue_.deq_ptr(); }
  const bool& maybe_full() const { return queue_.maybe_full(); }
  const SmallFtqBpdUpdate& payload(std::size_t index) const {
    return payloads_[index];
  }

 private:
  static constexpr std::uint8_t kFetchMask = static_cast<std::uint8_t>(
      (std::uint16_t{1} << boomcfg::FETCH_WIDTH) - std::uint16_t{1});
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);

  static SmallFtqBpdUpdate make_correction(
      const SmallBpdUpdatePathInputs& input) {
    SmallFtqBpdUpdate result;
    result.btb_mispredicts =
        static_cast<std::uint8_t>(input.f3_btb_mispredicts & kFetchMask);
    const SmallFetchBundle& bundle =
        input.f3_bundle_ref != nullptr ? *input.f3_bundle_ref : input.f3_bundle;
    result.pc = bundle.pc & kPcMask;
    result.ghist = bundle.ghist;
    result.meta = bundle.bpd_meta;
    for (int b = 0; b < boomcfg::NBANKS; ++b) {
      result.meta[4 * b + 3] &= 0x00ffffffu;
    }
    return result;
  }

  Queue queue_{2};
  std::array<SmallFtqBpdUpdate, 2> payloads_{};
};

}  // namespace chisa::boom_system::components
