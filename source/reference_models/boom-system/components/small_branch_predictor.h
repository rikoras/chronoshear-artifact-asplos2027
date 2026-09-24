#pragma once
// ============================================================================
// Small BOOM top-level branch predictor (one bank, TAGE-L composition).
//
// The five predictor banks own their internal state independently.  This
// wrapper owns the raw-PC F1/F2/F3 pipeline and the exact component metadata
// concatenation used by ComposedBranchPredictorBank/BranchPredictor.
// ============================================================================

#include <array>
#include <cstdint>

#include "../../boom_model/common/boom_config.h"
#include "small_loop_predictor.h"

namespace chisa::boom_system::components {

struct SmallBranchPredictorOutputs {
  std::uint64_t f1_pc = 0;
  std::uint64_t f2_pc = 0;
  std::uint64_t f3_pc = 0;
  SmallFrontendPredictionResponse f1{};
  SmallFrontendPredictionResponse f2{};
  SmallFrontendPredictionResponse f3{};
  std::array<std::uint32_t, boomcfg::BPD_META_WORDS> f3_meta{};
  SmallBpdResponse f3_response{};
};

class SmallBranchPredictor {
 public:
  SmallBranchPredictorOutputs outputs(
      const SmallFaMicroBtbOutputs& fa,
      const SmallBimOutputs& bim,
      const SmallBtbOutputs& btb,
      const SmallTageOutputs& tage,
      const SmallLoopOutputs& loop) const {

    SmallBranchPredictorOutputs result;

    outputs_into(fa, bim, btb, tage, loop, result);

    return result;

  }

  void outputs_into(const SmallFaMicroBtbOutputs& fa, const SmallBimOutputs& bim, const SmallBtbOutputs& btb, const SmallTageOutputs& tage, const SmallLoopOutputs& loop, SmallBranchPredictorOutputs& result) const {
    result = SmallBranchPredictorOutputs{};
    result.f1_pc = f1_pc_;
    result.f2_pc = f2_pc_;
    result.f3_pc = f3_pc_;
    result.f1 = loop.f1;
    result.f2 = loop.f2;
    result.f3 = loop.f3;
    // Bank 0 slice; banks 1.. are composed by the bank-select batch.
    const std::array<std::uint32_t, 4> slice0 = compose_metadata(
        fa.f3_meta, bim.f3_meta, btb.f3_meta, tage.f3_meta,
        loop.f3_meta);
    for (std::size_t w = 0; w < slice0.size(); ++w) {
      result.f3_meta[w] = slice0[w];
    }

    result.f3_response.pc = result.f3_pc;
    result.f3_response.meta = result.f3_meta;
    for (std::size_t lane = 0; lane < result.f3_response.preds.size();
         ++lane) {
      result.f3_response.preds[lane].taken =
          result.f3.preds[lane].taken;
      result.f3_response.preds[lane].predicted_pc_valid =
          result.f3.preds[lane].predicted_pc_valid;
      result.f3_response.preds[lane].predicted_pc =
          result.f3.preds[lane].predicted_pc & kPcMask;
    }
    return;
  }

  void step(std::uint64_t f0_pc) {
    f3_pc_ = f2_pc_;
    f2_pc_ = f1_pc_;
    f1_pc_ = f0_pc & kPcMask;
  }

  std::uint64_t f1_pc() const { return f1_pc_; }
  std::uint64_t f2_pc() const { return f2_pc_; }
  std::uint64_t f3_pc() const { return f3_pc_; }

  static std::array<std::uint32_t, 4> compose_metadata(
      std::uint8_t fa_meta, std::uint8_t bim_meta,
      std::uint8_t btb_meta, std::uint64_t tage_meta,
      std::uint64_t loop_meta) {
    // Composer order is loop, TAGE, BTB, FA-uBTB, BIM.  Repeated left shifts
    // therefore place BIM at bits 0-7 and loop at bits 73-112.
    std::array<std::uint32_t, 4> result{};
    result[0] = static_cast<std::uint32_t>(bim_meta) |
                (static_cast<std::uint32_t>(fa_meta) << 8u) |
                (static_cast<std::uint32_t>(btb_meta & 1u) << 16u);
    SmallTagePredictor::set_local_metadata(result, tage_meta);
    SmallLoopPredictor::set_local_metadata(result, loop_meta);
    result[3] &= 0x00ffffffu;
    return result;
  }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40u) - UINT64_C(1);

  std::uint64_t f1_pc_ = 0;
  std::uint64_t f2_pc_ = 0;
  std::uint64_t f3_pc_ = 0;
};

}  // namespace chisa::boom_system::components
