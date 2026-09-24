#pragma once
// ============================================================================
// Small BOOM loop predictor (four columns, 16 entries per column).
//
// This is component 0 of the locked TAGE-L composition.  It owns the common
// F0/F1/F2/F3 request pipeline, the registered update path, four independent
// loop-entry columns, the F2/F3 repair forwarding paths, and the F4 iteration
// progression writes.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

#include <cstdio>
#include <cstdlib>
#include "small_tage_predictor.h"

namespace chisa::boom_system::components {

struct SmallLoopEntry {
  std::uint16_t tag = 0;
  std::uint8_t conf = 0;
  std::uint8_t age = 0;
  std::uint16_t p_cnt = 0;
  std::uint16_t s_cnt = 0;
};

struct SmallLoopMetadata {
  std::array<std::uint16_t, 4> s_cnt{};
};

struct SmallLoopColumnInputs {
  bool reset = false;
  std::uint64_t f2_req_idx = 0;
  bool f3_req_fire = false;
  bool f3_pred_in = false;

  bool update_mispredict = false;
  bool update_repair = false;
  std::uint64_t update_idx = 0;
  std::uint16_t update_meta_s_cnt = 0;
};

struct SmallLoopColumnOutputs {
  bool f3_pred = false;
  std::uint16_t f3_meta_s_cnt = 0;
  bool overrides = false;

  bool f4_progress = false;
  bool f4_resets_iteration = false;
  bool mispredict_write = false;
  bool repair_write = false;
};

class SmallLoopPredictorColumn {
 public:
  static constexpr std::size_t kEntries = 16;

  SmallLoopColumnOutputs outputs(const SmallLoopColumnInputs& input) const {
    SmallLoopColumnOutputs result;
    result.f3_meta_s_cnt =
        input.update_repair && masked_index(input.update_idx) == f3_index_
            ? mask_counter(input.update_meta_s_cnt)
            : f3_entry_.s_cnt;
    result.overrides =
        f3_entry_.tag == f3_tag_ && f3_entry_.conf == 7 &&
        result.f3_meta_s_cnt == f3_entry_.p_cnt;
    result.f3_pred = result.overrides ? !input.f3_pred_in
                                      : input.f3_pred_in;

    result.f4_progress =
        f4_fire_ && f4_entry_.tag == f4_tag_;
    result.f4_resets_iteration =
        result.f4_progress && f4_entry_.conf == 7 &&
        f4_scnt_ == f4_entry_.p_cnt;

    const SmallLoopEntry& update_entry =
        entries_[row(input.update_idx)];
    const bool update_tag_match =
        update_entry.tag == tag(input.update_idx);
    result.mispredict_write = input.update_mispredict && !doing_reset_;
    result.repair_write =
        !input.update_mispredict && input.update_repair && !doing_reset_ &&
        update_tag_match &&
        !(f4_fire_ && masked_index(input.update_idx) == f4_idx_);
    return result;
  }

  bool step(const SmallLoopColumnInputs& input) {
    const SmallLoopColumnOutputs output = outputs(input);
    const std::uint64_t query_idx = masked_index(input.f2_req_idx);
    const std::uint64_t update_idx = masked_index(input.update_idx);
    const std::array<std::size_t, 3> touched_rows{
        row(f4_idx_), row(update_idx), reset_idx_};
    const std::array<bool, 3> touched{
        output.f4_progress,
        output.mispredict_write || output.repair_write,
        doing_reset_};
    std::array<SmallLoopEntry, 3> previous_entries{};
    for (std::size_t index = 0; index < touched.size(); ++index)
      if (touched[index]) previous_entries[index] = entries_[touched_rows[index]];

    // f2_entry is a read of the cycle-start Vec.  Repair has forwarding
    // priority over mispredict, exactly matching the WireInit/when chain.
    SmallLoopEntry next_f3_entry = entries_[row(query_idx)];
    if (input.update_repair && update_idx == query_idx) {
      next_f3_entry.s_cnt = mask_counter(input.update_meta_s_cnt);
    } else if (input.update_mispredict && update_idx == query_idx) {
      next_f3_entry.s_cnt = 0;
    }

    // The update decision reads the cycle-start entry.  A later full-entry
    // training write therefore replaces, rather than incorporates, a same-
    // edge F4 age/counter update.
    const SmallLoopEntry old_update_entry = entries_[row(update_idx)];

    if (output.f4_progress) {
      SmallLoopEntry& entry = entries_[row(f4_idx_)];
      if (output.f4_resets_iteration) {
        entry.age = 7;
        entry.s_cnt = 0;
      } else {
        entry.s_cnt = mask_counter(f4_scnt_ + 1u);
        entry.age = saturating_increment_age(f4_entry_.age);
      }
    }

    if (output.mispredict_write) {
      entries_[row(update_idx)] = trained_entry(
          old_update_entry, tag(update_idx), input.update_meta_s_cnt);
    } else if (output.repair_write) {
      SmallLoopEntry repaired = old_update_entry;
      repaired.s_cnt = mask_counter(input.update_meta_s_cnt);
      entries_[row(update_idx)] = repaired;
    }

    // The sequential reset sweep is the final assignment in loop.scala and
    // consequently overrides either kind of normal write to this row.
    if (doing_reset_) entries_[reset_idx_] = SmallLoopEntry{};

    const bool next_doing_reset =
        doing_reset_ && reset_idx_ != kEntries - 1u;
    const std::uint8_t next_reset_idx = static_cast<std::uint8_t>(
        (reset_idx_ + (doing_reset_ ? 1u : 0u)) & 0x0fu);

    const SmallLoopEntry next_f4_entry = f3_entry_;
    const std::uint16_t next_f4_tag = f3_tag_;
    const std::uint16_t next_f4_scnt = output.f3_meta_s_cnt;
    const std::uint64_t next_f4_idx = f4_index_stage1_;

    f3_entry_ = normalized(next_f3_entry);
    f3_index_ = query_idx;
    f3_tag_ = tag(query_idx);
    f4_fire_ = input.f3_req_fire;
    f4_entry_ = normalized(next_f4_entry);
    f4_tag_ = next_f4_tag;
    f4_scnt_ = next_f4_scnt;
    f4_idx_ = next_f4_idx;
    f4_index_stage1_ = query_idx;

    if (input.reset) {
      doing_reset_ = true;
      reset_idx_ = 0;
    } else {
      doing_reset_ = next_doing_reset;
      reset_idx_ = next_reset_idx;
    }

    bool storage_changed = false;
    for (std::size_t index = 0; index < touched.size(); ++index) {
      if (!touched[index]) continue;
      bool duplicate = false;
      for (std::size_t prior = 0; prior < index; ++prior)
        duplicate |= touched[prior] &&
                     touched_rows[prior] == touched_rows[index];
      if (duplicate ||
          equal_entry(previous_entries[index], entries_[touched_rows[index]]))
        continue;
      ++entry_epochs_[touched_rows[index]];
      storage_changed = true;
    }
    return storage_changed;
  }

  const bool& doing_reset() const { return doing_reset_; }
  const std::uint8_t& reset_index() const { return reset_idx_; }
  const SmallLoopEntry& entry(std::size_t index) const {
    return entries_[index];
  }
  const std::uint64_t& entry_epoch_for_diagnostic(std::size_t index) const {
    return entry_epochs_[index];
  }

  const SmallLoopEntry& f3_entry() const { return f3_entry_; }
  std::uint64_t f3_index() const { return f3_index_; }
  const std::uint16_t& f3_tag() const { return f3_tag_; }

  bool f4_fire() const { return f4_fire_; }
  const SmallLoopEntry& f4_entry() const { return f4_entry_; }
  std::uint16_t f4_tag() const { return f4_tag_; }
  std::uint16_t f4_scnt() const { return f4_scnt_; }
  const std::uint64_t& f4_index_stage1() const { return f4_index_stage1_; }
  std::uint64_t f4_index() const { return f4_idx_; }

  static std::uint8_t row(std::uint64_t index) {
    return static_cast<std::uint8_t>(index & 0x0fu);
  }

  static std::uint16_t tag(std::uint64_t index) {
    return static_cast<std::uint16_t>((index >> 4u) & 0x03ffu);
  }

 private:
  static constexpr std::uint64_t kIndexMask =
      (UINT64_C(1) << 37u) - UINT64_C(1);

  static std::uint64_t masked_index(std::uint64_t index) {
    return index & kIndexMask;
  }

  static std::uint16_t mask_counter(std::uint64_t counter) {
    return static_cast<std::uint16_t>(counter & 0x03ffu);
  }

  static std::uint8_t saturating_increment_age(std::uint8_t age) {
    age &= 0x07u;
    return age == 7 ? 7 : static_cast<std::uint8_t>(age + 1u);
  }

  static SmallLoopEntry normalized(SmallLoopEntry entry) {
    entry.tag &= 0x03ffu;
    entry.conf &= 0x07u;
    entry.age &= 0x07u;
    entry.p_cnt &= 0x03ffu;
    entry.s_cnt &= 0x03ffu;
    return entry;
  }

  static bool equal_entry(const SmallLoopEntry& lhs,
                          const SmallLoopEntry& rhs) {
    return lhs.tag == rhs.tag && lhs.conf == rhs.conf &&
           lhs.age == rhs.age && lhs.p_cnt == rhs.p_cnt &&
           lhs.s_cnt == rhs.s_cnt;
  }

  static SmallLoopEntry trained_entry(const SmallLoopEntry& old_entry,
                                      std::uint16_t update_tag,
                                      std::uint16_t update_counter) {
    SmallLoopEntry result = normalized(old_entry);
    update_tag &= 0x03ffu;
    update_counter &= 0x03ffu;
    const bool tag_match = result.tag == update_tag;
    const bool counter_match = result.p_cnt == update_counter;

    if (result.conf == 7 && tag_match) {
      result.s_cnt = 0;
      result.conf = 0;
    } else if (result.conf == 7 && !tag_match) {
      // A fully learned entry is not evicted by an unrelated loop.
    } else if (result.conf != 0 && tag_match && counter_match) {
      result.conf = static_cast<std::uint8_t>(result.conf + 1u);
      result.s_cnt = 0;
    } else if (result.conf != 0 && tag_match && !counter_match) {
      result.conf = 0;
      result.s_cnt = 0;
      result.p_cnt = update_counter;
    } else if (result.conf != 0 && !tag_match && result.age == 0) {
      // The source comment says "set age high", but the executable Chisel
      // leaves age unchanged in this branch.
      result.tag = update_tag;
      result.conf = 1;
      result.s_cnt = 0;
      result.p_cnt = update_counter;
    } else if (result.conf != 0 && !tag_match && result.age != 0) {
      result.age = static_cast<std::uint8_t>(result.age - 1u);
    } else if (result.conf == 0 && tag_match && counter_match) {
      result.conf = 1;
      result.age = 7;
      result.s_cnt = 0;
    } else if (result.conf == 0 && tag_match && !counter_match) {
      result.p_cnt = update_counter;
      result.age = 7;
      result.s_cnt = 0;
    } else {
      result.tag = update_tag;
      result.conf = 1;
      result.age = 7;
      result.s_cnt = 0;
      result.p_cnt = update_counter;
    }
    return normalized(result);
  }

  std::array<SmallLoopEntry, kEntries> entries_{};
  std::array<std::uint64_t, kEntries> entry_epochs_{};

  bool doing_reset_ = true;
  std::uint8_t reset_idx_ = 0;

  SmallLoopEntry f3_entry_{};
  std::uint64_t f3_index_ = 0;
  std::uint16_t f3_tag_ = 0;

  bool f4_fire_ = false;
  SmallLoopEntry f4_entry_{};
  std::uint16_t f4_tag_ = 0;
  std::uint16_t f4_scnt_ = 0;
  std::uint64_t f4_index_stage1_ = 0;
  std::uint64_t f4_idx_ = 0;
};

struct SmallLoopInputs {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;
  std::uint8_t f0_mask = 0;
  SmallFrontendPredictionResponse resp_in_f1{};
  SmallFrontendPredictionResponse resp_in_f2{};
  SmallFrontendPredictionResponse resp_in_f3{};
  bool f3_fire = false;
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

struct SmallLoopOutputs {
  SmallFrontendPredictionResponse f1{};
  SmallFrontendPredictionResponse f2{};
  SmallFrontendPredictionResponse f3{};
  SmallLoopMetadata metadata{};
  std::uint64_t f3_meta = 0;
  std::array<SmallLoopColumnOutputs, 4> columns{};
};

class SmallLoopPredictor {
 public:
  static constexpr std::size_t kColumns = 4;
  static constexpr std::size_t kEntries = 16;
  static constexpr std::uint8_t kMetadataOffset = 73;

  SmallLoopOutputs outputs(const SmallLoopInputs& input) const {

    SmallLoopOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallLoopInputs& input, SmallLoopOutputs& result) const {
    result = SmallLoopOutputs{};
    result.f1 = input.resp_in_f1;
    result.f2 = input.resp_in_f2;
    result.f3 = input.resp_in_f3;

    const SmallLoopMetadata update_metadata =
        unpack_metadata(local_metadata(s1_update_.meta));
    for (std::size_t lane = 0; lane < kColumns; ++lane) {
      const SmallLoopColumnInputs column_input =
          make_column_input(input, update_metadata, lane);
      result.columns[lane] = columns_[lane].outputs(column_input);
      result.f3.preds[lane].taken = result.columns[lane].f3_pred;
      result.metadata.s_cnt[lane] =
          result.columns[lane].f3_meta_s_cnt;
    }
    result.f3_meta = pack_metadata(result.metadata);
    return;
  }

  void step(const SmallLoopInputs& input) {
    const std::array<std::size_t, 2> previous_read_rows{
        static_cast<std::size_t>(s2_idx_ & 0x0fu),
        static_cast<std::size_t>(s1_update_idx_ & 0x0fu)};
    std::array<std::array<std::uint64_t, 2>, kColumns>
        previous_read_epochs{};
    for (std::size_t lane = 0; lane < kColumns; ++lane)
      for (std::size_t port = 0; port < previous_read_rows.size(); ++port)
        previous_read_epochs[lane][port] =
            columns_[lane].entry_epoch_for_diagnostic(
                previous_read_rows[port]);

    const SmallLoopMetadata update_metadata =
        unpack_metadata(local_metadata(s1_update_.meta));
    bool storage_changed = false;
    for (std::size_t lane = 0; lane < kColumns; ++lane)
      storage_changed |=
          columns_[lane].step(make_column_input(input, update_metadata, lane));

    s2_idx_ = s1_idx_;
    s1_idx_ = fetch_index(input.f0_pc);
    s3_valid_ = s2_valid_;
    s2_valid_ = s1_valid_;
    s1_valid_ = input.f0_valid;
    s3_mask_ = s2_mask_;
    s2_mask_ = s1_mask_;
    s1_mask_ = input.reset ? std::uint8_t{0x0f}
                           : static_cast<std::uint8_t>(input.f0_mask & 0x0fu);

    s1_update_valid_ = input.update_valid;
    s1_update_ = input.update;
    s1_update_.pc &= kPcMask;
    s1_update_idx_ = fetch_index(input.update.pc);
    // The RTL update-index register is an enabled latch: it holds the last
    // valid update's index across idle cycles.
    if (input.update_valid)
      s1_update_raw_idx_ =
          (input.update.pc & kPcMask) >> boomcfg::FETCH_IDX_SHIFT;

    for (std::size_t lane = 0; lane < kColumns; ++lane) {
      f2_predicted_branch_[lane] =
          input.resp_in_f2.preds[lane].predicted_pc_valid &&
          input.resp_in_f2.preds[lane].is_br;
    }

    const std::array<std::size_t, 2> next_read_rows{
        static_cast<std::size_t>(s2_idx_ & 0x0fu),
        static_cast<std::size_t>(s1_update_idx_ & 0x0fu)};
    bool read_changed = previous_read_rows != next_read_rows;
    if (!read_changed) {
      for (std::size_t lane = 0; lane < kColumns && !read_changed; ++lane)
        for (std::size_t port = 0;
             port < next_read_rows.size() && !read_changed; ++port)
          read_changed = previous_read_epochs[lane][port] !=
                         columns_[lane].entry_epoch_for_diagnostic(
                             next_read_rows[port]);
    }
    if (storage_changed) ++storage_epoch_;
    if (read_changed) ++read_epoch_;
    // Every exported non-read field is a scalar pipeline/reset register.
    // A one-word watch avoids comparing the complete loop-entry storage on
    // each frontend edge.
    ++pipeline_epoch_;
    // The two RTL read ports of every column (the s2 lookup row and the
    // update row), captured as plain fields: the oracle export compares
    // these bytes instead of re-reading the storage through the index
    // registers every cycle.
    for (std::size_t lane = 0; lane < kColumns; ++lane) {
      s2_port_[lane] = columns_[lane].entry(next_read_rows[0]);
      update_port_[lane] = columns_[lane].entry(next_read_rows[1]);
    }
  }

  const std::uint64_t& s1_index() const { return s1_idx_; }
  const std::uint64_t& s2_index() const { return s2_idx_; }

  const bool& s1_valid() const { return s1_valid_; }
  const bool& s2_valid() const { return s2_valid_; }
  bool s3_valid() const { return s3_valid_; }
  const std::uint8_t& s1_mask() const { return s1_mask_; }
  std::uint8_t s2_mask() const { return s2_mask_; }
  std::uint8_t s3_mask() const { return s3_mask_; }
  bool s1_update_valid() const { return s1_update_valid_; }
  const SmallFtqBpdUpdate& s1_update() const { return s1_update_; }
  const std::uint64_t& s1_update_index() const { return s1_update_idx_; }
  // Full-width RTL update-index register (row masking happens at the read).
  std::uint64_t s1_update_raw_index() const { return s1_update_raw_idx_; }
  bool f2_predicted_branch(std::size_t lane) const {
    return f2_predicted_branch_[lane];
  }
  const SmallLoopPredictorColumn& column(std::size_t lane) const {
    return columns_[lane];
  }
  /** Post-edge read-port contents: entry(s2_index & 0xf) and
    * entry(s1_update_index & 0xf) of the column, as of the end of step(). */
  const SmallLoopEntry& s2_port_entry(std::size_t lane) const {
    return s2_port_[lane];
  }
  const SmallLoopEntry& update_port_entry(std::size_t lane) const {
    return update_port_[lane];
  }
  const std::uint64_t& storage_epoch_for_diagnostic() const {
    return storage_epoch_;
  }
  const std::uint64_t& read_epoch_for_diagnostic() const {
    return read_epoch_;
  }
  const std::uint64_t& pipeline_epoch_for_diagnostic() const {
    return pipeline_epoch_;
  }

  static std::uint8_t fetch_mask(std::uint64_t pc) {
    return boomcfg::fetch_mask(pc);
  }

  static std::uint64_t pack_metadata(const SmallLoopMetadata& metadata) {
    std::uint64_t result = 0;
    for (std::size_t lane = 0; lane < kColumns; ++lane)
      result |= static_cast<std::uint64_t>(metadata.s_cnt[lane] & 0x03ffu)
                << (lane * 10u);
    return result & kLocalMetadataMask;
  }

  static SmallLoopMetadata unpack_metadata(std::uint64_t bits) {
    SmallLoopMetadata result;
    bits &= kLocalMetadataMask;
    for (std::size_t lane = 0; lane < kColumns; ++lane)
      result.s_cnt[lane] = static_cast<std::uint16_t>(
          (bits >> (lane * 10u)) & 0x03ffu);
    return result;
  }

  // Words 0..3 always hold this bank's slice (see the TAGE note).
  static std::uint64_t local_metadata(
      const std::array<std::uint32_t, boomcfg::BPD_META_WORDS>&
          full_metadata) {
    return ((static_cast<std::uint64_t>(full_metadata[2]) >> 9u) |
            (static_cast<std::uint64_t>(full_metadata[3] & 0x0001ffffu)
             << 23u)) &
           kLocalMetadataMask;
  }

  static void set_local_metadata(std::array<std::uint32_t, 4>& full_metadata,
                                 std::uint64_t local) {
    local &= kLocalMetadataMask;
    full_metadata[2] =
        (full_metadata[2] & 0x000001ffu) |
        static_cast<std::uint32_t>((local & 0x007fffffu) << 9u);
    full_metadata[3] =
        (full_metadata[3] & ~UINT32_C(0x0001ffff)) |
        static_cast<std::uint32_t>((local >> 23u) & 0x0001ffffu);
  }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40u) - UINT64_C(1);
  static constexpr std::uint64_t kIndexMask =
      (UINT64_C(1) << 37u) - UINT64_C(1);
  static constexpr std::uint64_t kLocalMetadataMask =
      (UINT64_C(1) << 40u) - UINT64_C(1);

  static std::uint64_t fetch_index(std::uint64_t pc) {
    return ((pc & kPcMask) >> boomcfg::FETCH_IDX_SHIFT) & kIndexMask;
  }

  SmallLoopColumnInputs make_column_input(
      const SmallLoopInputs& input,
      const SmallLoopMetadata& update_metadata,
      std::size_t lane) const {
    SmallLoopColumnInputs result;
    result.reset = input.reset;
    result.f2_req_idx = s2_idx_;
    result.f3_req_fire =
        s3_valid_ && ((s3_mask_ >> lane) & 1u) != 0 && input.f3_fire &&
        f2_predicted_branch_[lane];
    result.f3_pred_in = input.resp_in_f3.preds[lane].taken;
    result.update_mispredict =
        s1_update_valid_ && ((s1_update_.br_mask >> lane) & 1u) != 0 &&
        s1_update_.is_mispredict_update &&
        s1_update_.cfi_mispredicted;
    result.update_repair =
        s1_update_valid_ && ((s1_update_.br_mask >> lane) & 1u) != 0 &&
        s1_update_.is_repair_update;
    result.update_idx = s1_update_idx_;
    result.update_meta_s_cnt = update_metadata.s_cnt[lane];
    return result;
  }

  std::array<SmallLoopPredictorColumn, kColumns> columns_{};

  std::uint64_t s1_idx_ = 0;
  std::uint64_t s2_idx_ = 0;

  bool s1_valid_ = false;
  bool s2_valid_ = false;
  bool s3_valid_ = false;
  std::uint8_t s1_mask_ = 0x0f;  // matches the RTL latch across reset
  std::uint8_t s2_mask_ = 0;
  std::uint8_t s3_mask_ = 0;

  bool s1_update_valid_ = false;
  SmallFtqBpdUpdate s1_update_{};
  std::uint64_t s1_update_idx_ = 0;
  std::uint64_t s1_update_raw_idx_ = 0;
  std::array<bool, kColumns> f2_predicted_branch_{};
  std::uint64_t storage_epoch_ = 0;
  std::uint64_t read_epoch_ = 0;
  std::uint64_t pipeline_epoch_ = 0;
  std::array<SmallLoopEntry, kColumns> s2_port_{};
  std::array<SmallLoopEntry, kColumns> update_port_{};
};

/** Only the response fields are (re)written; the boundary fields of
  * `result` are the caller's. */
inline void connect_tage_to_loop_into(SmallLoopInputs& result,
                                      const SmallTageOutputs& tage) {
  result.resp_in_f1 = tage.f1;
  result.resp_in_f2 = tage.f2;
  result.resp_in_f3 = tage.f3;
}
inline SmallLoopInputs connect_tage_to_loop(
    const SmallLoopInputs& boundary, const SmallTageOutputs& tage) {
  SmallLoopInputs result = boundary;
  connect_tage_to_loop_into(result, tage);
  return result;
}

}  // namespace chisa::boom_system::components
