#pragma once
// ============================================================================
// Small BOOM set-associative BTB (128 sets x 2 ways x 4 fetch slots).
//
// This is component 2 of the locked TAGE-L composition.  It owns the tag and
// relative-target memories, the shared extended-target memory, reset sweep,
// F2/F3 conditional override pipeline, one-bit prediction metadata, and BTB
// training/invalidation path.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

#include "small_bim_predictor.h"
#include "small_f0_f2.h"
#include "small_fa_micro_btb.h"
#include "small_ftq.h"

namespace chisa::boom_system::components {

struct SmallBtbInputs {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;
  SmallFrontendPredictionResponse resp_in_f1{};
  SmallFrontendPredictionResponse resp_in_f2{};
  SmallFrontendPredictionResponse resp_in_f3{};
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

struct SmallBtbMetaEntry {
  bool is_br = false;
  std::uint32_t tag = 0;
};

struct SmallBtbTargetEntry {
  std::int16_t offset = 0;
  bool extended = false;
};

struct SmallBtbOutputs {
  SmallFrontendPredictionResponse f1{};
  SmallFrontendPredictionResponse f2{};
  SmallFrontendPredictionResponse f3{};
  SmallFrontendPredictionResponse s1_response{};
  std::array<std::uint8_t, 4> hit_oh{};
  std::array<bool, 4> hits{};
  std::array<std::uint8_t, 4> hit_way{};
  std::uint8_t allocation_way = 0;
  std::uint8_t write_way = 0;
  std::uint8_t f3_meta = 0;
  std::uint8_t update_wbtb_mask = 0;
  std::uint8_t update_wmeta_mask = 0;
  bool update_offset_extended = false;
  std::int16_t update_offset = 0;
};

class SmallBtbPredictor {
 public:
  static constexpr std::size_t kSets = 128;
  static constexpr std::size_t kWays = 2;
  static constexpr std::size_t kSlots = 4;

  SmallBtbOutputs outputs(const SmallBtbInputs& input) const {

    SmallBtbOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallBtbInputs& input, SmallBtbOutputs& result) const {
    result = SmallBtbOutputs{};
    result.f1 = input.resp_in_f1;
    result.f2 = input.resp_in_f2;
    result.f3 = input.resp_in_f3;

    const std::uint32_t request_tag = s1_tag();
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      for (std::size_t way = 0; way < kWays; ++way) {
        if (rows_[read_row_].meta[way][slot].tag == request_tag)
          result.hit_oh[slot] |= static_cast<std::uint8_t>(1u << way);
      }
      result.hits[slot] = result.hit_oh[slot] != 0;
      result.hit_way[slot] = priority_encode(result.hit_oh[slot]);
      const std::size_t way = result.hit_way[slot];
      const SmallBtbMetaEntry& meta = rows_[read_row_].meta[way][slot];
      const SmallBtbTargetEntry& target = rows_[read_row_].targets[way][slot];
      SmallFrontendPrediction& prediction = result.s1_response.preds[slot];
      prediction.predicted_pc_valid =
          !doing_reset_ && s1_valid_ && result.hits[slot];
      prediction.predicted_pc =
          target.extended
              ? rows_[read_row_].extended
              : add_offset(s1_pc_, slot, target.offset);
      prediction.is_br =
          !doing_reset_ && prediction.predicted_pc_valid && meta.is_br;
      prediction.is_jal =
          !doing_reset_ && prediction.predicted_pc_valid && !meta.is_br;

      if (f2_override_[slot]) {
        SmallFrontendPrediction& f2 = result.f2.preds[slot];
        f2.predicted_pc_valid = f2_prediction_.preds[slot].predicted_pc_valid;
        f2.predicted_pc = f2_prediction_.preds[slot].predicted_pc;
        f2.is_br = f2_prediction_.preds[slot].is_br;
        f2.is_jal = f2_prediction_.preds[slot].is_jal;
        f2.taken = f2.taken || f2_force_taken_[slot];
      }
      if (f3_override_[slot]) {
        SmallFrontendPrediction& f3 = result.f3.preds[slot];
        f3.predicted_pc_valid = f3_prediction_.preds[slot].predicted_pc_valid;
        f3.predicted_pc = f3_prediction_.preds[slot].predicted_pc;
        f3.is_br = f3_prediction_.preds[slot].is_br;
        f3.is_jal = f3_prediction_.preds[slot].is_jal;
        f3.taken = f3.taken || f3_force_taken_[slot];
      }
    }

    result.allocation_way = allocation_way();
    std::uint8_t any_hit_ways = 0;
    for (const std::uint8_t hit_oh : result.hit_oh)
      any_hit_ways |= hit_oh;
    result.write_way = any_hit_ways != 0
                           ? priority_encode(any_hit_ways)
                           : result.allocation_way;
    result.f3_meta = f3_meta_stage2_;

    const bool commit = is_commit_update();
    if (s1_update_valid_ && commit && s1_update_.cfi_valid &&
        s1_update_.cfi_taken) {
      result.update_wbtb_mask = static_cast<std::uint8_t>(
          1u << (s1_update_.cfi_idx & 0x03u));
    }
    const std::uint8_t candidate_mask = static_cast<std::uint8_t>(
        result.update_wbtb_mask | (s1_update_.br_mask & 0x0fu));
    const std::uint8_t enable_mask = static_cast<std::uint8_t>(
        (s1_update_valid_ && commit ? 0x0fu : 0u) |
        (s1_update_valid_ ? s1_update_.btb_mispredicts & 0x0fu : 0u));
    result.update_wmeta_mask =
        static_cast<std::uint8_t>(candidate_mask & enable_mask);
    const std::int64_t offset = update_offset_value();
    result.update_offset_extended = offset > 4095 || offset < -4096;
    result.update_offset = sign_extend_offset(
        static_cast<std::uint16_t>(offset) & 0x1fffu);
    return;
  }

  void commit(const SmallBtbInputs& input,
              const SmallBtbOutputs& output) {
    const std::size_t update_way = local_update_write_way();
    const std::size_t update_row = s1_update_row();
    const std::uint8_t previous_read_row = read_row_;
    bool previous_read_row_written = false;

    if (doing_reset_) {
      previous_read_row_written = reset_index_ == previous_read_row;
      for (std::size_t way = 0; way < kWays; ++way) {
        for (std::size_t slot = 0; slot < kSlots; ++slot) {
          rows_[reset_index_].meta[way][slot] = SmallBtbMetaEntry{};
          rows_[reset_index_].targets[way][slot] = SmallBtbTargetEntry{};
        }
      }
    } else {
      previous_read_row_written =
          update_row == previous_read_row &&
          (output.update_wbtb_mask != 0 || output.update_wmeta_mask != 0);
      for (std::size_t slot = 0; slot < kSlots; ++slot) {
        if (((output.update_wbtb_mask >> slot) & 1u) != 0) {
          rows_[update_row].targets[update_way][slot].offset =
              output.update_offset;
          rows_[update_row].targets[update_way][slot].extended =
              output.update_offset_extended;
        }
        if (((output.update_wmeta_mask >> slot) & 1u) != 0) {
          SmallBtbMetaEntry& meta = rows_[update_row].meta[update_way][slot];
          meta.is_br = ((s1_update_.br_mask >> slot) & 1u) != 0;
          meta.tag = ((s1_update_.btb_mispredicts >> slot) & 1u) != 0
                         ? 0
                         : s1_update_tag();
        }
      }
    }
    if (output.update_wbtb_mask != 0 && output.update_offset_extended) {
      rows_[update_row].extended = s1_update_.target & kPcMask;
      previous_read_row_written |= update_row == previous_read_row;
    }

    f3_prediction_ = output.f2;
    f3_override_ = f3_override_stage1_;
    f3_override_stage1_ = output.hits;
    f3_force_taken_ = f3_force_taken_stage1_;
    for (std::size_t slot = 0; slot < kSlots; ++slot)
      f3_force_taken_stage1_[slot] =
          output.s1_response.preds[slot].is_jal;
    f2_override_ = output.hits;
    f2_prediction_ = output.s1_response;
    for (std::size_t slot = 0; slot < kSlots; ++slot)
      f2_force_taken_[slot] = output.s1_response.preds[slot].is_jal;

    f3_meta_stage2_ = f3_meta_stage1_;
    f3_meta_stage1_ = output.write_way;
    s1_index_ = fetch_index(input.f0_pc);
    s1_valid_ = input.f0_valid;
    s1_pc_ = input.f0_pc & kPcMask;
    if (input.f0_valid)
      read_row_ = static_cast<std::uint8_t>(s1_index_ & 0x7fu);
    s1_update_valid_ = input.update_valid;
    s1_update_ = input.update;
    s1_update_.pc &= kPcMask;
    s1_update_.target &= kPcMask;

    const std::uint8_t next_reset_index = static_cast<std::uint8_t>(
        (reset_index_ + (doing_reset_ ? 1u : 0u)) & 0x7fu);
    const bool next_doing_reset =
        doing_reset_ && reset_index_ != 0x7fu;
    reset_index_ = next_reset_index;
    doing_reset_ = next_doing_reset;
    if (input.reset) {
      reset_index_ = 0;
      doing_reset_ = true;
    }
    // The packed read-row snapshots are a function of rows_[read_row_]
    // alone: refresh them exactly when the read row moved or was written
    // (the same condition that advances read_epoch_).
    if (read_row_ != previous_read_row || previous_read_row_written) {
      ++read_epoch_;
      refresh_packed_snapshots();  // the frontend commits directly (step() only on reset)
    }
    // The remaining live streams are all scalar pipeline/reset fields.
    // Watching this word avoids comparing the 128-row storage array merely
    // to discover that those registers advance on every frontend edge.
    ++pipeline_epoch_;
  }

  void step(const SmallBtbInputs& input) {
    commit(input, outputs(input));
    refresh_packed_snapshots();
  }

  const bool& doing_reset() const { return doing_reset_; }
  const std::uint8_t& reset_index() const { return reset_index_; }
  const std::uint8_t& read_row() const { return read_row_; }
  const bool& s1_valid() const { return s1_valid_; }
  const std::uint64_t& s1_index() const { return s1_index_; }
  const std::uint64_t& s1_pc() const { return s1_pc_; }
  const bool& s1_update_valid() const { return s1_update_valid_; }
  const SmallFtqBpdUpdate& s1_update() const { return s1_update_; }
  std::uint64_t s1_update_index() const {
    return fetch_index(s1_update_.pc);
  }
  std::uint8_t local_update_write_way() const {
    return static_cast<std::uint8_t>((s1_update_.meta[0] >> 16u) & 1u);
  }
  std::uint8_t f3_meta_stage1() const { return f3_meta_stage1_; }
  const std::uint8_t& f3_meta_stage2() const { return f3_meta_stage2_; }
  /** Registered f2/f3 payloads for the live oracle exports. */
  const SmallFrontendPrediction& f2_prediction(std::size_t slot) const {
    return f2_prediction_.preds[slot];
  }
  const SmallFrontendPrediction& f3_prediction(std::size_t slot) const {
    return f3_prediction_.preds[slot];
  }
  const bool& f2_force_taken(std::size_t slot) const { return f2_force_taken_[slot]; }
  const bool& f3_force_taken(std::size_t slot) const { return f3_force_taken_[slot]; }
  const bool& f3_force_taken_stage1(std::size_t slot) const {
    return f3_force_taken_stage1_[slot];
  }

  const bool& f2_override(std::size_t slot) const {
    return f2_override_[slot];
  }
  const bool& f3_override_stage1(std::size_t slot) const {
    return f3_override_stage1_[slot];
  }
  const bool& f3_override(std::size_t slot) const {
    return f3_override_[slot];
  }

  const SmallBtbMetaEntry& meta(std::size_t way, std::size_t row,
                                std::size_t slot) const {
    return rows_[row].meta[way][slot];
  }
  const SmallBtbTargetEntry& target(std::size_t way, std::size_t row,
                                    std::size_t slot) const {
    return rows_[row].targets[way][slot];
  }
  std::uint64_t extended_target(std::size_t row) const {
    return rows_[row].extended;
  }
  /** Packed views of the meta/target rows at the current read row (the
    * lowered bank streams read them each cycle), kept as fields so the
    * sampler copies them instead of re-packing through the component. */
  void refresh_packed_snapshots() {
    for (std::size_t way = 0; way < kWays; ++way)
      for (std::size_t slot = 0; slot < kSlots; ++slot) {
        packed_meta_snapshot_[way][slot] = packed_meta_now(way, read_row_, slot);
        packed_target_snapshot_[way][slot] = packed_target_now(way, read_row_, slot);
      }
  }
  const std::uint32_t& packed_meta_at_read_row(std::size_t way, std::size_t slot) const {
    return packed_meta_snapshot_[way][slot];
  }
  const std::uint16_t& packed_target_at_read_row(std::size_t way, std::size_t slot) const {
    return packed_target_snapshot_[way][slot];
  }
  std::uint32_t packed_meta_now(std::size_t way, std::size_t row,
                                std::size_t slot) const {
    const SmallBtbMetaEntry& entry = meta(way, row, slot);
    return (static_cast<std::uint32_t>(entry.is_br) << kTagWidth) |
           (entry.tag & kTagMask);
  }
  std::uint16_t packed_target_now(std::size_t way, std::size_t row,
                                  std::size_t slot) const {
    const SmallBtbTargetEntry& entry = target(way, row, slot);
    return static_cast<std::uint16_t>(
        ((static_cast<std::uint16_t>(entry.offset) & 0x1fffu) << 1u) |
        static_cast<std::uint16_t>(entry.extended));
  }
  std::uint32_t packed_meta(std::size_t way, std::size_t row, std::size_t slot) const {
    return packed_meta_now(way, row, slot);
  }
  std::uint16_t packed_target(std::size_t way, std::size_t row, std::size_t slot) const {
    return packed_target_now(way, row, slot);
  }
  const std::uint64_t& read_epoch_for_diagnostic() const {
    return read_epoch_;
  }
  const std::uint64_t& pipeline_epoch_for_diagnostic() const {
    return pipeline_epoch_;
  }

 private:

  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);
  static constexpr unsigned kIndexWidth =
      40u - static_cast<unsigned>(boomcfg::FETCH_IDX_SHIFT);
  static constexpr unsigned kTagWidth = kIndexWidth - 7u;
  static constexpr std::uint64_t kIndexMask =
      (UINT64_C(1) << kIndexWidth) - UINT64_C(1);
  static constexpr std::uint32_t kTagMask =
      (UINT32_C(1) << kTagWidth) - UINT32_C(1);

  static std::uint64_t fetch_index(std::uint64_t pc) {
    return (pc >> boomcfg::FETCH_IDX_SHIFT) & kIndexMask;
  }
  std::uint32_t s1_tag() const {
    return static_cast<std::uint32_t>((s1_index_ >> 7u) & kTagMask);
  }
  std::uint8_t s1_update_row() const {
    return static_cast<std::uint8_t>(s1_update_index() & 0x7fu);
  }
  std::uint32_t s1_update_tag() const {
    return static_cast<std::uint32_t>(
        (s1_update_index() >> 7u) & kTagMask);
  }
  bool is_commit_update() const {
    return !s1_update_.is_mispredict_update &&
           !s1_update_.is_repair_update &&
           (s1_update_.btb_mispredicts & 0x0fu) == 0;
  }
  static std::uint8_t priority_encode(std::uint8_t bits) {
    return (bits & 1u) != 0 ? 0 : 1;
  }
  static bool parity(std::uint64_t value) {
    return __builtin_parityll(value) != 0;
  }
  std::uint8_t allocation_way() const {
    bool result = parity(s1_tag());
    for (std::size_t way = 0; way < kWays; ++way)
      for (std::size_t slot = 0; slot < kSlots; ++slot)
        result ^= parity(rows_[read_row_].meta[way][slot].tag);
    return static_cast<std::uint8_t>(result);
  }
  static std::int64_t sign_extend_40(std::uint64_t value) {
    value &= kPcMask;
    if ((value & (UINT64_C(1) << 39u)) != 0)
      value |= ~kPcMask;
    return static_cast<std::int64_t>(value);
  }
  std::int64_t update_offset_value() const {
    const std::uint64_t base =
        (s1_update_.pc +
         (static_cast<std::uint64_t>(s1_update_.cfi_idx & 0x03u) << 1u)) &
        kPcMask;
    return sign_extend_40((s1_update_.target - base) & kPcMask);
  }
  static std::int16_t sign_extend_offset(std::uint16_t bits) {
    bits &= 0x1fffu;
    if ((bits & 0x1000u) != 0) bits |= 0xe000u;
    return static_cast<std::int16_t>(bits);
  }
  static std::uint64_t add_offset(std::uint64_t pc, std::size_t slot,
                                  std::int16_t offset) {
    return (pc + static_cast<std::uint64_t>(slot << 1u) +
            static_cast<std::uint64_t>(static_cast<std::int64_t>(offset))) &
           kPcMask;
  }

  // One record per set: both ways' meta and target entries and the
  // extended target are read together every cycle (the lookup at the
  // registered read row), so one set is two cache lines instead of five.
  struct Row {
    std::array<std::array<SmallBtbMetaEntry, kSlots>, kWays> meta{};
    std::array<std::array<SmallBtbTargetEntry, kSlots>, kWays> targets{};
    std::uint64_t extended = 0;
  };
  std::array<Row, kSets> rows_{};

  std::uint8_t read_row_ = 0;

  std::array<std::array<std::uint32_t, kSlots>, kWays> packed_meta_snapshot_{};

  std::array<std::array<std::uint16_t, kSlots>, kWays> packed_target_snapshot_{};
  bool s1_valid_ = false;
  std::uint64_t s1_index_ = 0;
  std::uint64_t s1_pc_ = 0;
  bool s1_update_valid_ = false;
  SmallFtqBpdUpdate s1_update_{};

  std::array<bool, kSlots> f2_override_{};
  SmallFrontendPredictionResponse f2_prediction_{};
  std::array<bool, kSlots> f2_force_taken_{};
  std::array<bool, kSlots> f3_override_stage1_{};
  std::array<bool, kSlots> f3_override_{};
  SmallFrontendPredictionResponse f3_prediction_{};
  std::array<bool, kSlots> f3_force_taken_stage1_{};
  std::array<bool, kSlots> f3_force_taken_{};
  std::uint8_t f3_meta_stage1_ = 0;
  std::uint8_t f3_meta_stage2_ = 0;

  bool doing_reset_ = true;
  std::uint8_t reset_index_ = 0;
  std::uint64_t read_epoch_ = 0;
  std::uint64_t pipeline_epoch_ = 0;
};

/** Only the response fields are (re)written; the boundary fields of
  * `result` are the caller's. */
inline void connect_fa_bim_to_btb_into(SmallBtbInputs& result,
                                       const SmallFaMicroBtbOutputs& fa,
                                       const SmallBimOutputs& bim) {
  result.resp_in_f1 = fa.f1;
  result.resp_in_f2 = fa.f2;
  result.resp_in_f3 = fa.f3;
  for (std::size_t slot = 0; slot < SmallBtbPredictor::kSlots; ++slot) {
    result.resp_in_f2.preds[slot].taken = bim.f2_taken[slot];
    result.resp_in_f3.preds[slot].taken = bim.f3_taken[slot];
  }
}
inline SmallBtbInputs connect_fa_bim_to_btb(
    const SmallBtbInputs& boundary, const SmallFaMicroBtbOutputs& fa,
    const SmallBimOutputs& bim) {
  SmallBtbInputs result = boundary;
  connect_fa_bim_to_btb_into(result, fa, bim);
  return result;
}

}  // namespace chisa::boom_system::components
