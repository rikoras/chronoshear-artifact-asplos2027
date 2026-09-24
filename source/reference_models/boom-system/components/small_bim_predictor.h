#pragma once
// ============================================================================
// Small BOOM BIM predictor bank (nSets=2048, bankWidth=4).
//
// This is component 4 of the locked TAGE-L composition.  It owns four 2-bit
// counters per fetch row, the sequential reset sweep, the F0->F2 synchronous
// read path, F3 metadata/taken registers, and the two-entry write-bypass table.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

#include "small_ftq.h"

namespace chisa::boom_system::components {

struct SmallBimInputs {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

struct SmallBimOutputs {
  std::array<bool, 4> f2_taken{};
  std::array<bool, 4> f3_taken{};
  std::uint8_t f3_meta = 0;
  std::array<bool, 4> update_wmask{};
  std::array<std::uint8_t, 4> update_wdata{};
  bool bypass_hit = false;
  std::uint8_t bypass_hit_idx = 0;
};

class SmallBimPredictor {
 public:
  static constexpr std::size_t kSets = 2048;

  SmallBimOutputs outputs(const SmallBimInputs& input) const {

    SmallBimOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallBimInputs& input, SmallBimOutputs& result) const {
    (void)input;
    result = SmallBimOutputs{};
    for (std::size_t slot = 0; slot < 4; ++slot) {
      result.f2_taken[slot] =
          s2_valid_ && ((s2_read_data_[slot] >> 1u) & 1u) != 0 &&
          !doing_reset_;
      result.f3_taken[slot] = f3_taken_[slot];
    }
    result.f3_meta = f3_meta_;

    result.bypass_hit =
        !doing_reset_ &&
        (bypass_indices_[0] == update_index() ||
         bypass_indices_[1] == update_index());
    result.bypass_hit_idx =
        !doing_reset_ && bypass_indices_[0] == update_index() ? 0 : 1;
    for (std::size_t slot = 0; slot < 4; ++slot) {
      const bool selected =
          ((s1_update_.br_mask >> slot) & 1u) != 0 ||
          (s1_update_.cfi_valid &&
           (s1_update_.cfi_idx & 0x03u) == slot);
      result.update_wmask[slot] = selected;
      const bool was_taken =
          s1_update_.cfi_valid &&
          (s1_update_.cfi_idx & 0x03u) == slot &&
          ((s1_update_.cfi_is_br &&
            ((s1_update_.br_mask >> slot) & 1u) != 0 &&
            s1_update_.cfi_taken) ||
           s1_update_.cfi_is_jal);
      const std::uint8_t old_value =
          result.bypass_hit
              ? bypass_values_[result.bypass_hit_idx][slot]
              : static_cast<std::uint8_t>(
                    (s1_update_.meta[0] >> (slot * 2u)) & 0x03u);
      result.update_wdata[slot] = update_counter(old_value, was_taken);
    }
    return;
  }

  void commit(const SmallBimInputs& input,
              const SmallBimOutputs& output) {
    const bool is_commit_update =
        !s1_update_.is_mispredict_update &&
        !s1_update_.is_repair_update &&
        (s1_update_.btb_mispredicts & 0x0fu) == 0;
    const bool update_write =
        s1_update_valid_ && is_commit_update;
    const bool any_update = output.update_wmask[0] ||
                            output.update_wmask[1] ||
                            output.update_wmask[2] ||
                            output.update_wmask[3];

    // The memory's registered address holds when its read enable is low, but
    // the outer RegNext still captures the data at that held address.  Read
    // before this edge's write, matching the generated read-old ordering.
    const std::array<std::uint8_t, 4> next_s2_read_data =
        counters_[read_address_pipe_];
    oracle_data_port_ = next_s2_read_data;
    oracle_s2_read_prev_ = s2_read_data_;

    const std::array<bool, 4> next_f3_taken = output.f2_taken;
    const std::uint8_t next_f3_meta = pack(s2_read_data_);

    if (doing_reset_) {
      counters_[reset_index_] = {2, 2, 2, 2};
    } else if (update_write) {
      for (std::size_t slot = 0; slot < 4; ++slot)
        if (output.update_wmask[slot])
          counters_[update_index()][slot] = output.update_wdata[slot];
    }

    if (any_update && update_write) {
      const std::uint8_t destination =
          output.bypass_hit ? output.bypass_hit_idx : bypass_enqueue_index_;
      if (bypass_values_[destination] != output.update_wdata)
        ++bypass_epoch_;
      bypass_values_[destination] = output.update_wdata;
      if (!output.bypass_hit) {
        if (bypass_indices_[destination] != update_index())
          ++bypass_epoch_;
        bypass_indices_[destination] = update_index();
        ++bypass_epoch_;
        bypass_enqueue_index_ ^= 1u;
      }
    }

    const std::uint16_t next_reset_index = static_cast<std::uint16_t>(
        (reset_index_ + (doing_reset_ ? 1u : 0u)) & 0x07ffu);
    const bool next_doing_reset =
        doing_reset_ && reset_index_ != 0x07ffu;

    if (oracle_cold_ != 0) --oracle_cold_;
    else s2_read_data_ = next_s2_read_data;
    f3_taken_ = next_f3_taken;
    f3_meta_ = next_f3_meta;
    s2_valid_ = s1_valid_;
    s1_valid_ = input.f0_valid;
    read_enable_pipe_ = input.f0_valid;
    if (input.f0_valid)
      read_address_pipe_ = fetch_index(input.f0_pc);
    s1_update_valid_ = input.update_valid;
    s1_update_ = input.update;
    s1_update_.pc &= kPcMask;
    reset_index_ = next_reset_index;
    doing_reset_ = next_doing_reset;

    // RegInit reset overrides only these three registers.  The pipeline,
    // memories, bypass payloads and bypass indices are deliberately unreset.
    if (input.reset) {
      reset_index_ = 0;
      doing_reset_ = true;
      if (bypass_enqueue_index_ != 0) ++bypass_epoch_;
      bypass_enqueue_index_ = 0;

    }

    const std::array<std::uint8_t, 4> next_oracle_comb_data_port =
        oracle_cold_ != 0 ? oracle_data_port_
                          : counters_[read_address_pipe_];
    if (oracle_comb_data_port_ != next_oracle_comb_data_port) {
      oracle_comb_data_port_ = next_oracle_comb_data_port;
      ++read_epoch_;
    }
    // The remaining live BIM streams are scalar pipeline/reset/update
    // registers.  They are clocked every frontend edge, so one epoch word is
    // cheaper to watch than either comparing the 8 KiB counter table or
    // reconstructing a large byte region around these fields.
    ++pipeline_epoch_;
  }

  void step(const SmallBimInputs& input) {
    commit(input, outputs(input));
  }

  const bool& doing_reset() const { return doing_reset_; }
  const std::uint16_t& oracle_bypass_index(std::size_t e) const {
    return bypass_indices_[e];
  }
  const std::uint8_t& oracle_bypass_value(std::size_t e, std::size_t s) const {
    return bypass_values_[e][s];
  }
  const std::uint16_t& reset_index() const { return reset_index_; }
  const bool& s1_valid() const { return s1_valid_; }
  const bool& s2_valid() const { return s2_valid_; }
  const bool& s1_update_valid() const { return s1_update_valid_; }
  const SmallFtqBpdUpdate& s1_update() const { return s1_update_; }
  std::uint64_t s1_update_index() const {
    return s1_update_.pc >> boomcfg::FETCH_IDX_SHIFT;
  }
  const std::uint8_t& oracle_s2_read_prev(std::size_t slot) const {
    return oracle_s2_read_prev_[slot];
  }
  const std::uint8_t& oracle_data_port(std::size_t slot) const {
    return oracle_data_port_[slot];
  }

  // The MPORT tap is a combinational read of the registered SRAM address.
  // Unlike s2_req_rdata, it is not the value captured on the preceding edge.
  const std::uint8_t& oracle_comb_data_port(std::size_t slot) const {
    return oracle_comb_data_port_[slot];
  }
  std::uint8_t oracle_comb_data_port_reference_for_diagnostic(
      std::size_t slot) const {
    // Independent slow path used by deferred sample checking.  Keep this as
    // the literal SyncReadMem expression so a missed cache/epoch update is
    // observable instead of validating the cache against itself.
    if (oracle_cold_ != 0) return oracle_data_port_[slot];
    return counters_[read_address_pipe_][slot];
  }

  const std::array<std::uint8_t, 4>& s2_read_data() const {
    return s2_read_data_;
  }
  const std::uint8_t& bypass_enqueue_index() const {
    return bypass_enqueue_index_;
  }
  const std::uint16_t& bypass_index(std::size_t entry) const {
    return bypass_indices_[entry];
  }
  const std::array<std::uint8_t, 4>& bypass_value(
      std::size_t entry) const {
    return bypass_values_[entry];
  }
  std::uint8_t counter(std::size_t row, std::size_t slot) const {
    return counters_[row][slot];
  }
  const std::uint64_t& read_epoch_for_diagnostic() const {
    return read_epoch_;
  }
  const std::uint64_t& pipeline_epoch_for_diagnostic() const {
    return pipeline_epoch_;
  }
  const std::uint64_t& bypass_epoch_for_diagnostic() const {
    return bypass_epoch_;
  }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);

  static std::uint16_t fetch_index(std::uint64_t pc) {
    return static_cast<std::uint16_t>(
        (pc >> boomcfg::FETCH_IDX_SHIFT) & 0x07ffu);
  }

  std::uint16_t update_index() const {
    return fetch_index(s1_update_.pc);
  }

  static std::uint8_t update_counter(std::uint8_t value, bool taken) {
    value &= 0x03u;
    if (taken) return value == 3 ? 3 : static_cast<std::uint8_t>(value + 1u);
    return value == 0 ? 0 : static_cast<std::uint8_t>(value - 1u);
  }

  static std::uint8_t pack(
      const std::array<std::uint8_t, 4>& values) {
    std::uint8_t result = 0;
    for (std::size_t slot = 0; slot < 4; ++slot)
      result |= static_cast<std::uint8_t>(
          (values[slot] & 0x03u) << (slot * 2u));
    return result;
  }

  std::array<std::array<std::uint8_t, 4>, kSets> counters_{};

  bool s1_valid_ = false;
  bool s2_valid_ = false;
  bool read_enable_pipe_ = false;
  std::uint16_t read_address_pipe_ = 0;
  std::array<std::uint8_t, 4> s2_read_data_{};
  std::array<std::uint8_t, 4> oracle_data_port_{};
  std::array<std::uint8_t, 4> oracle_comb_data_port_{};
  std::array<std::uint8_t, 4> oracle_s2_read_prev_{};
  int oracle_cold_ = 2;
  std::array<bool, 4> f3_taken_{};
  std::uint8_t f3_meta_ = 0;

  bool s1_update_valid_ = false;
  SmallFtqBpdUpdate s1_update_{};

  bool doing_reset_ = true;
  std::uint16_t reset_index_ = 0;
  std::array<std::uint16_t, 2> bypass_indices_{};
  std::array<std::array<std::uint8_t, 4>, 2> bypass_values_{};
  std::uint8_t bypass_enqueue_index_ = 0;
  std::uint64_t read_epoch_ = 0;
  std::uint64_t pipeline_epoch_ = 0;
  std::uint64_t bypass_epoch_ = 0;
};

}  // namespace chisa::boom_system::components
