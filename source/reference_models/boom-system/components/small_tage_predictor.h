#pragma once
// ============================================================================
// Small BOOM TAGE predictor (six tagged history tables, bankWidth=4).
//
// This is component 1 of the locked TAGE-L composition.  It owns the exact
// F0/F1/F3 query pipeline, provider/alternate selection, 56-bit local
// metadata, allocation LFSRs, parent update register, and each table's reset,
// usefulness-clear, counter memory, and two-entry counter-write bypass.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "small_btb_predictor.h"
#include "small_ftq.h"

namespace chisa::boom_system::components {

struct SmallTageValidTable {
  bool valid = false;
  std::uint8_t bits = 0;
};

struct SmallTageMetadata {
  std::array<SmallTageValidTable, 4> allocate{};
  std::array<std::uint8_t, 4> provider_ctr{};
  std::array<std::uint8_t, 4> provider_u{};
  std::array<bool, 4> alt_differs{};
  std::array<SmallTageValidTable, 4> provider{};
};

struct SmallTageTableResponse {
  bool valid = false;
  std::uint8_t ctr = 0;
  std::uint8_t u = 0;
};

struct SmallTageTableEntry {
  bool valid = false;
  std::uint16_t tag = 0;
  std::uint8_t ctr = 0;
};

struct SmallTageTableUpdate {
  std::array<bool, 4> mask{};
  std::array<bool, 4> taken{};
  std::array<bool, 4> alloc{};
  std::array<std::uint8_t, 4> old_ctr{};
  std::array<bool, 4> u_mask{};
  std::array<std::uint8_t, 4> u{};
  std::uint64_t pc = 0;
  std::uint64_t history = 0;
};

struct SmallTageTableInputs {
  bool reset = false;
  bool f1_valid = false;
  std::uint64_t f1_pc = 0;
  std::uint64_t f1_history = 0;
  SmallTageTableUpdate update{};
};

// Diagnostic transaction at the table's storage boundary.  This is the
// useful seam for differential debugging: the parent chooses the registered
// update fields, then the table resolves the counter-bypass old value and
// commits one masked memory write.  Keeping this record does not participate
// in prediction; it only makes the first bad write directly observable.
struct SmallTageCounterWriteTransaction {
  bool active = false;
  bool bypass_hit = false;
  std::uint8_t bypass_hit_index = 0;
  std::uint8_t bypass_destination = 0;
  std::uint16_t index = 0;
  std::uint16_t tag = 0;
  SmallTageTableUpdate input{};
  std::array<std::uint8_t, 4> selected_old_ctr{};
  std::array<std::uint8_t, 4> next_ctr{};
};

class SmallTageTable {
 public:
  static constexpr std::size_t kMaxRows = 256;
  static constexpr std::size_t kSlots = 4;
  static constexpr std::uint32_t kUsefulnessPeriod = 2048;

  SmallTageTable(std::uint16_t rows = 128, std::uint8_t tag_bits = 7,
                 std::uint8_t history_length = 2)
      : rows_(rows),
        tag_bits_(tag_bits),
        history_length_(history_length),
        index_bits_(rows == 256 ? 8 : 7),
        row_mask_(static_cast<std::uint16_t>(rows - 1u)),
        clear_counter_mask_((UINT32_C(1)
                             << (11u + index_bits_ + 1u)) -
                            UINT32_C(1)) {}

  const std::array<SmallTageTableResponse, kSlots>& responses() const {
    return f3_response_;
  }

  void step(const SmallTageTableInputs& input) {
    const bool was_doing_reset = doing_reset_;
    bool bypass_changed = false;
    // The query hash only depends on (pc, history); a stalled fetch
    // presents the same pair for many cycles.
    if (!query_memo_valid_ || input.f1_pc != query_memo_pc_ ||
        input.f1_history != query_memo_history_) {
      query_memo_ = hash(input.f1_pc, input.f1_history);
      query_memo_pc_ = input.f1_pc;
      query_memo_history_ = input.f1_history;
      query_memo_valid_ = true;
    }
    const Hash query_hash = query_memo_;

    // hi_us and lo_us are separate memories.  A periodic clear blocks only
    // the corresponding half; the other half may still accept an update.
    const bool doing_clear =
        (clear_u_counter_ & (kUsefulnessPeriod - 1u)) == 0;
    const bool doing_clear_hi =
        doing_clear &&
        ((clear_u_counter_ >> (11u + index_bits_)) & 1u) != 0;
    const bool doing_clear_lo =
        doing_clear && !doing_clear_hi;
    const std::uint16_t clear_row = static_cast<std::uint16_t>(
        (clear_u_counter_ >> 11u) & row_mask_);

    // The F3 response registers capture the sparse-read result before the
    // matching array write commits. A same-address query/update therefore
    // feeds the old entry and usefulness bits into F3 this cycle. The separate
    // exported MPORT snapshot below follows its existing post-write sampling
    // contract; these are deliberately two observable faces of the edge.
    std::array<SmallTageTableResponse, kSlots> next_response{};
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      const SmallTageTableEntry& entry = table_rows_[read_row_].entries[slot];
      next_response[slot].valid =
          entry.valid && entry.tag == s2_tag_ && !doing_reset_;
      next_response[slot].ctr = entry.ctr & 0x07u;
      next_response[slot].u = usefulness(read_row_, slot);
    }

    // Most cycles carry no table update at all (branch updates arrive only
    // when a fetch bundle with branches commits).  On those cycles the update
    // hash, the write bypass and the counter computation feed nothing
    // observable: no entry or usefulness write happens and the bypass queue
    // does not move.  Only the scheduled periodic usefulness clear still
    // lands.  last_counter_write_ is a test-only observer; no test inspects
    // its payload on an idle cycle.
    const bool update_active =
        input.update.mask[0] || input.update.mask[1] ||
        input.update.mask[2] || input.update.mask[3] ||
        input.update.u_mask[0] || input.update.u_mask[1] ||
        input.update.u_mask[2] || input.update.u_mask[3];
    if (!doing_reset_ && !update_active) {
      // Test observer: only its `active` flag is inspected on an idle
      // cycle, so the payload is not zeroed here.
      last_counter_write_.active = false;
      if (doing_clear_hi) table_rows_[clear_row].hi_use = {};
      if (doing_clear_lo) table_rows_[clear_row].lo_use = {};
    } else {
    const Hash update_hash = hash(input.update.pc, input.update.history);
    const bool bypass_hit_0 =
        !doing_reset_ && bypass_tags_[0] == update_hash.tag &&
        bypass_indices_[0] == update_hash.index;
    const bool bypass_hit_1 =
        !doing_reset_ && bypass_tags_[1] == update_hash.tag &&
        bypass_indices_[1] == update_hash.index;
    const bool bypass_hit = bypass_hit_0 || bypass_hit_1;
    const std::uint8_t bypass_hit_index = bypass_hit_0 ? 0 : 1;

    std::array<std::uint8_t, kSlots> update_counters{};
    std::array<std::uint8_t, kSlots> selected_old_counters{};
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      const std::uint8_t old_counter =
          bypass_hit ? bypass_values_[bypass_hit_index][slot]
                     : input.update.old_ctr[slot];
      selected_old_counters[slot] = old_counter;
      update_counters[slot] =
          input.update.alloc[slot]
              ? static_cast<std::uint8_t>(input.update.taken[slot] ? 4 : 3)
              : update_counter(old_counter, input.update.taken[slot]);
    }

    // The tagged-entry memory has reset priority over a normal update.
    if (doing_reset_) {
      for (std::size_t slot = 0; slot < kSlots; ++slot)
        table_rows_[reset_index_].entries[slot] = SmallTageTableEntry{};
    } else {
      for (std::size_t slot = 0; slot < kSlots; ++slot) {
        if (!input.update.mask[slot]) continue;
        SmallTageTableEntry& entry = table_rows_[update_hash.index].entries[slot];
        entry.valid = true;
        entry.tag = update_hash.tag;
        entry.ctr = update_counters[slot];
      }
    }

    if (doing_reset_) {
      table_rows_[reset_index_].hi_use = {};
      table_rows_[reset_index_].lo_use = {};
    } else {
      if (doing_clear_hi) {
        table_rows_[clear_row].hi_use = {};
      } else {
        for (std::size_t slot = 0; slot < kSlots; ++slot)
          if (input.update.u_mask[slot])
            table_rows_[update_hash.index].hi_use[slot] =
                ((input.update.u[slot] >> 1u) & 1u) != 0;
      }
      if (doing_clear_lo) {
        table_rows_[clear_row].lo_use = {};
      } else {
        for (std::size_t slot = 0; slot < kSlots; ++slot)
          if (input.update.u_mask[slot])
            table_rows_[update_hash.index].lo_use[slot] =
                (input.update.u[slot] & 1u) != 0;
      }
    }

    // Counter bypass enqueues all four computed counters whenever any table
    // lane writes, exactly like VecInit(update_wdata.map(_.ctr)).
    const bool any_update = input.update.mask[0] || input.update.mask[1] ||
                            input.update.mask[2] || input.update.mask[3];
    last_counter_write_ = {};
    last_counter_write_.active = any_update;
    last_counter_write_.bypass_hit = bypass_hit;
    last_counter_write_.bypass_hit_index = bypass_hit_index;
    last_counter_write_.bypass_destination =
        bypass_hit ? bypass_hit_index : bypass_enqueue_index_;
    last_counter_write_.index = update_hash.index;
    last_counter_write_.tag = update_hash.tag;
    last_counter_write_.input = input.update;
    last_counter_write_.selected_old_ctr = selected_old_counters;
    last_counter_write_.next_ctr = update_counters;
    if (any_update) {
      bypass_changed = true;
      const std::uint8_t destination =
          bypass_hit ? bypass_hit_index : bypass_enqueue_index_;
      bypass_values_[destination] = update_counters;
      if (!bypass_hit) {
        bypass_tags_[destination] = update_hash.tag;
        bypass_indices_[destination] = update_hash.index;
        bypass_enqueue_index_ ^= 1u;
      }
    }
    }

    // The externalized array-read streams are sampled from this post-write
    // face in the locked model contract.  The SyncReadMem read enable gates
    // only its address register: while disabled, MPORT remains a combinational
    // view of the held row and therefore still reflects a same-row write.
    // Keep that timing independent of the pre-write value captured by the F3
    // response registers above.
    const std::uint16_t mport_row =
        input.f1_valid ? query_hash.index : read_row_;
    for (std::size_t slot = 0; slot < kSlots; ++slot)
      read_data_snapshot_[slot] = packed_entry(mport_row, slot);

    f3_response_ = next_response;
    s2_tag_ = query_hash.tag;
    read_enable_ = input.f1_valid;
    if (input.f1_valid) read_row_ = query_hash.index;

    const std::uint16_t next_reset_index = static_cast<std::uint16_t>(
        (reset_index_ + (doing_reset_ ? 1u : 0u)) & row_mask_);
    const bool next_doing_reset =
        doing_reset_ && reset_index_ != row_mask_;
    if (input.reset) {
      reset_index_ = 0;
      doing_reset_ = true;
    } else {
      reset_index_ = next_reset_index;
      doing_reset_ = next_doing_reset;
    }

    if (input.reset) {
      clear_u_counter_ = 0;
      bypass_changed |= bypass_enqueue_index_ != 0;
      bypass_enqueue_index_ = 0;
    } else if (was_doing_reset) {
      clear_u_counter_ = 1;
    } else {
      clear_u_counter_ =
          (clear_u_counter_ + 1u) & clear_counter_mask_;
    }
    if (bypass_changed) ++bypass_epoch_;
    // Post-step face of the usefulness read ports at the (updated) read
    // row: the exported lo_us/hi_us MPORT streams are sampled from here as
    // plain fields instead of being recomputed through the component by
    // the sampler batch every cycle (that batch could only declare the
    // whole component as its input and therefore ran every cycle).
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      const std::uint8_t u = usefulness(read_row_, slot);
      usefulness_lo_snapshot_[slot] = static_cast<std::uint8_t>(u & 1u);
      usefulness_hi_snapshot_[slot] = static_cast<std::uint8_t>((u >> 1u) & 1u);
    }
  }

  std::uint16_t rows() const { return rows_; }
  std::uint8_t tag_bits() const { return tag_bits_; }
  std::uint8_t history_length() const { return history_length_; }
  std::uint8_t index_bits() const { return index_bits_; }
  const bool& doing_reset() const { return doing_reset_; }
  const std::uint16_t& reset_index() const { return reset_index_; }
  const std::uint16_t& read_row() const { return read_row_; }
  bool read_enable() const { return read_enable_; }
  /** Post-step usefulness bits (lo_us / hi_us read ports) at the read row. */
  const std::uint8_t& usefulness_lo(std::size_t slot) const {
    return usefulness_lo_snapshot_[slot];
  }
  const std::uint8_t& usefulness_hi(std::size_t slot) const {
    return usefulness_hi_snapshot_[slot];
  }
  /** Post-step combinational value at the SyncReadMem MPORT for one slot. */
  const std::uint16_t& read_data(std::size_t slot) const {
    return read_data_snapshot_[slot];
  }
  const std::uint16_t& s2_tag() const { return s2_tag_; }
  std::uint32_t clear_u_counter() const { return clear_u_counter_; }
  const std::uint8_t& bypass_enqueue_index() const {
    return bypass_enqueue_index_;
  }
  const std::uint16_t& bypass_tag(std::size_t entry) const {
    return bypass_tags_[entry];
  }
  const std::uint16_t& bypass_index(std::size_t entry) const {
    return bypass_indices_[entry];
  }
  const std::uint8_t& bypass_value(std::size_t entry, std::size_t slot) const {
    return bypass_values_[entry][slot];
  }
  const std::uint64_t& bypass_epoch_for_diagnostic() const {
    return bypass_epoch_;
  }
  const SmallTageCounterWriteTransaction& last_counter_write() const {
    return last_counter_write_;
  }
  const SmallTageTableEntry& entry(std::size_t row,
                                   std::size_t slot) const {
    return table_rows_[row].entries[slot];
  }
  std::uint8_t usefulness(std::size_t row, std::size_t slot) const {
    return static_cast<std::uint8_t>(
        (static_cast<std::uint8_t>(table_rows_[row].hi_use[slot]) << 1u) |
        static_cast<std::uint8_t>(table_rows_[row].lo_use[slot]));
  }
  std::uint16_t packed_entry(std::size_t row, std::size_t slot) const {
    const SmallTageTableEntry& value = entry(row, slot);
    return static_cast<std::uint16_t>(
        (static_cast<std::uint16_t>(value.valid) << (tag_bits_ + 3u)) |
        ((value.tag & tag_mask()) << 3u) | (value.ctr & 0x07u));
  }

  std::uint16_t query_index(std::uint64_t pc,
                            std::uint64_t history) const {
    return hash(pc, history).index;
  }
  std::uint16_t query_tag(std::uint64_t pc,
                          std::uint64_t history) const {
    return hash(pc, history).tag;
  }

 private:
  struct Hash {
    std::uint16_t index = 0;
    std::uint16_t tag = 0;
  };

  std::uint16_t tag_mask() const {
    return static_cast<std::uint16_t>((1u << tag_bits_) - 1u);
  }

  std::uint64_t folded_history(std::uint64_t history,
                               std::uint8_t width) const {
    const std::uint64_t width_mask = (UINT64_C(1) << width) - 1u;
    std::uint64_t folded = 0;
    for (std::uint8_t offset = 0; offset < history_length_;
         offset = static_cast<std::uint8_t>(offset + width)) {
      const std::uint8_t remaining =
          static_cast<std::uint8_t>(history_length_ - offset);
      const std::uint8_t chunk_width = remaining < width ? remaining : width;
      const std::uint64_t chunk_mask =
          (UINT64_C(1) << chunk_width) - 1u;
      folded ^= (history >> offset) & chunk_mask;
    }
    return folded & width_mask;
  }

  Hash hash(std::uint64_t pc, std::uint64_t history) const {
    const std::uint64_t unhashed =
        (pc & kPcMask) >> boomcfg::FETCH_IDX_SHIFT;
    Hash result;
    result.index = static_cast<std::uint16_t>(
        (unhashed ^ folded_history(history, index_bits_)) & row_mask_);
    result.tag = static_cast<std::uint16_t>(
        ((unhashed >> index_bits_) ^
         folded_history(history, tag_bits_)) &
        tag_mask());
    return result;
  }

  static std::uint8_t update_counter(std::uint8_t counter, bool taken) {
    counter &= 0x07u;
    if (taken)
      return counter == 7 ? 7 : static_cast<std::uint8_t>(counter + 1u);
    return counter == 0 ? 0 : static_cast<std::uint8_t>(counter - 1u);
  }

  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40u) - UINT64_C(1);

  std::uint16_t rows_ = 128;
  std::uint8_t tag_bits_ = 7;
  std::uint8_t history_length_ = 2;
  std::uint8_t index_bits_ = 7;
  std::uint16_t row_mask_ = 127;
  std::uint32_t clear_counter_mask_ = (UINT32_C(1) << 19u) - 1u;

  // One row per line: the tagged entries and both usefulness halves of a
  // row are read together every cycle (the F3 response), so keeping them
  // in one 24-byte record turns three cache lines per table per cycle
  // into one.
  struct Row {
    std::array<SmallTageTableEntry, kSlots> entries{};
    std::array<bool, kSlots> hi_use{};
    std::array<bool, kSlots> lo_use{};
  };
  std::array<Row, kMaxRows> table_rows_{};

  std::uint16_t read_row_ = 0;
  bool read_enable_ = false;
  Hash query_memo_{};
  std::uint64_t query_memo_pc_ = 0, query_memo_history_ = 0;
  bool query_memo_valid_ = false;
  std::array<std::uint16_t, kSlots> read_data_snapshot_{};
  std::array<std::uint8_t, kSlots> usefulness_lo_snapshot_{};
  std::array<std::uint8_t, kSlots> usefulness_hi_snapshot_{};
  std::uint16_t s2_tag_ = 0;
  std::array<SmallTageTableResponse, kSlots> f3_response_{};

  bool doing_reset_ = true;
  std::uint16_t reset_index_ = 0;
  std::uint32_t clear_u_counter_ = 0;

  std::array<std::uint16_t, 2> bypass_tags_{};
  std::array<std::uint16_t, 2> bypass_indices_{};
  std::array<std::array<std::uint8_t, kSlots>, 2> bypass_values_{};
  std::uint8_t bypass_enqueue_index_ = 0;
  std::uint64_t bypass_epoch_ = 0;
  SmallTageCounterWriteTransaction last_counter_write_{};
};

struct SmallTageInputs {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;
  std::uint64_t f1_ghist = 0;
  SmallFrontendPredictionResponse resp_in_f1{};
  SmallFrontendPredictionResponse resp_in_f2{};
  SmallFrontendPredictionResponse resp_in_f3{};
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

struct SmallTageOutputs {
  SmallFrontendPredictionResponse f1{};
  SmallFrontendPredictionResponse f2{};
  SmallFrontendPredictionResponse f3{};
  SmallTageMetadata metadata{};
  std::uint64_t f3_meta = 0;
  std::array<std::array<SmallTageTableResponse, 4>, 6> table_responses{};
  std::array<SmallTageTableUpdate, 6> parent_updates{};
};

class SmallTagePredictor {
 public:
  static constexpr std::size_t kTables = 6;
  static constexpr std::size_t kSlots = 4;
  static constexpr std::uint8_t kMetadataOffset = 17;

  SmallTagePredictor()
      : tables_{{SmallTageTable(128, 7, 2),
                 SmallTageTable(128, 7, 4),
                 SmallTageTable(256, 8, 8),
                 SmallTageTable(256, 8, 16),
                 SmallTageTable(128, 9, 32),
                 SmallTageTable(128, 9, 64)}} {}

  SmallTageOutputs outputs(const SmallTageInputs& input) const {

    SmallTageOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallTageInputs& input, SmallTageOutputs& result) const {
    result = SmallTageOutputs{};
    result.f1 = input.resp_in_f1;
    result.f2 = input.resp_in_f2;
    result.f3 = input.resp_in_f3;
    result.parent_updates = current_parent_updates();

    for (std::size_t table = 0; table < kTables; ++table)
      result.table_responses[table] = tables_[table].responses();

    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      bool alternate_prediction = input.resp_in_f3.preds[slot].taken;
      bool final_alternate = alternate_prediction;
      bool prediction = alternate_prediction;
      bool provider_valid = false;
      std::uint8_t provider = 0;

      for (std::size_t table = 0; table < kTables; ++table) {
        const SmallTageTableResponse& response =
            result.table_responses[table][slot];
        if (response.valid) {
          prediction = response.ctr == 3 || response.ctr == 4
                           ? alternate_prediction
                           : ((response.ctr >> 2u) & 1u) != 0;
          final_alternate = alternate_prediction;
          provider_valid = true;
          provider = static_cast<std::uint8_t>(table);
          alternate_prediction = ((response.ctr >> 2u) & 1u) != 0;
        }
      }
      result.f3.preds[slot].taken = prediction;
      result.metadata.provider[slot] = {provider_valid, provider};
      result.metadata.alt_differs[slot] =
          final_alternate != prediction;
      result.metadata.provider_u[slot] =
          result.table_responses[provider][slot].u;
      result.metadata.provider_ctr[slot] =
          result.table_responses[provider][slot].ctr;

      std::uint8_t allocatable = 0;
      for (std::size_t table = 0; table < kTables; ++table) {
        const SmallTageTableResponse& response =
            result.table_responses[table][slot];
        const bool longer_than_provider =
            !provider_valid || table > provider;
        if (!response.valid && response.u == 0 && longer_than_provider)
          allocatable |= static_cast<std::uint8_t>(1u << table);
      }
      const std::uint8_t masked =
          static_cast<std::uint8_t>(allocatable & lfsr_[slot]);
      const std::uint8_t allocation =
          priority_encode(masked != 0 ? masked : allocatable);
      result.metadata.allocate[slot] =
          {allocatable != 0, allocation};
    }
    result.f3_meta = pack_metadata(result.metadata);
    return;
  }

  void step(const SmallTageInputs& input) {
    const std::array<SmallTageTableUpdate, kTables>& next_parent_updates =
        current_parent_updates();
    bool table_bypass_changed = false;
    for (std::size_t table = 0; table < kTables; ++table) {
      SmallTageTableInputs table_input;
      table_input.reset = input.reset;
      table_input.f1_valid = f1_valid_;
      table_input.f1_pc = f1_pc_;
      table_input.f1_history = input.f1_ghist;
      table_input.update = parent_updates_[table];
      const std::uint64_t bypass_epoch =
          tables_[table].bypass_epoch_for_diagnostic();
      tables_[table].step(table_input);
      table_bypass_changed |=
          bypass_epoch != tables_[table].bypass_epoch_for_diagnostic();
    }

    parent_updates_ = next_parent_updates;
    f1_valid_ = input.f0_valid;
    f1_pc_ = input.f0_pc & kPcMask;
    s1_update_valid_ = input.update_valid;
    s1_update_ = input.update;
    s1_update_.pc &= kPcMask;
    parent_update_cache_valid_ = false;

    for (std::size_t slot = 0; slot < kSlots; ++slot)
      lfsr_[slot] = input.reset ? 1 : next_lfsr(lfsr_[slot]);
    if (table_bypass_changed) ++table_bypass_epoch_;
    ++table_read_epoch_;
    ++pipeline_epoch_;
  }

  bool f1_valid() const { return f1_valid_; }
  std::uint64_t f1_pc() const { return f1_pc_; }
  const bool& s1_update_valid() const { return s1_update_valid_; }
  const SmallFtqBpdUpdate& s1_update() const { return s1_update_; }
  const std::uint8_t& lfsr(std::size_t slot) const { return lfsr_[slot]; }
  const SmallTageTable& table(std::size_t index) const {
    return tables_[index];
  }
  const SmallTageTableUpdate& registered_update(std::size_t index) const {
    return parent_updates_[index];
  }
  const std::uint64_t& table_read_epoch_for_diagnostic() const {
    return table_read_epoch_;
  }
  const std::uint64_t& table_bypass_epoch_for_diagnostic() const {
    return table_bypass_epoch_;
  }
  const std::uint64_t& pipeline_epoch_for_diagnostic() const {
    return pipeline_epoch_;
  }

  static std::uint64_t pack_metadata(const SmallTageMetadata& metadata) {
    std::uint64_t result = 0;
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      result |= static_cast<std::uint64_t>(
                    metadata.allocate[slot].bits & 0x07u)
                << (slot * 4u);
      result |= static_cast<std::uint64_t>(
                    metadata.allocate[slot].valid)
                << (slot * 4u + 3u);
      result |= static_cast<std::uint64_t>(
                    metadata.provider_ctr[slot] & 0x07u)
                << (16u + slot * 3u);
      result |= static_cast<std::uint64_t>(
                    metadata.provider_u[slot] & 0x03u)
                << (28u + slot * 2u);
      result |= static_cast<std::uint64_t>(metadata.alt_differs[slot])
                << (36u + slot);
      result |= static_cast<std::uint64_t>(
                    metadata.provider[slot].bits & 0x07u)
                << (40u + slot * 4u);
      result |= static_cast<std::uint64_t>(
                    metadata.provider[slot].valid)
                << (43u + slot * 4u);
    }
    return result & kLocalMetadataMask;
  }

  static SmallTageMetadata unpack_metadata(std::uint64_t bits) {
    SmallTageMetadata result;
    bits &= kLocalMetadataMask;
    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      result.allocate[slot].bits =
          static_cast<std::uint8_t>((bits >> (slot * 4u)) & 0x07u);
      result.allocate[slot].valid =
          ((bits >> (slot * 4u + 3u)) & 1u) != 0;
      result.provider_ctr[slot] = static_cast<std::uint8_t>(
          (bits >> (16u + slot * 3u)) & 0x07u);
      result.provider_u[slot] = static_cast<std::uint8_t>(
          (bits >> (28u + slot * 2u)) & 0x03u);
      result.alt_differs[slot] =
          ((bits >> (36u + slot)) & 1u) != 0;
      result.provider[slot].bits = static_cast<std::uint8_t>(
          (bits >> (40u + slot * 4u)) & 0x07u);
      result.provider[slot].valid =
          ((bits >> (43u + slot * 4u)) & 1u) != 0;
    }
    return result;
  }

  // Words 0..3 always hold this bank's slice: with several banks the
  // update routing pre-slices the composed metadata per bank.
  static std::uint64_t local_metadata(
      const std::array<std::uint32_t, boomcfg::BPD_META_WORDS>&
          full_metadata) {
    const std::uint64_t low =
        static_cast<std::uint64_t>(full_metadata[0]) |
        (static_cast<std::uint64_t>(full_metadata[1]) << 32u);
    return ((low >> kMetadataOffset) |
            (static_cast<std::uint64_t>(full_metadata[2] & 0x01ffu)
             << 47u)) &
           kLocalMetadataMask;
  }

  static void set_local_metadata(std::array<std::uint32_t, 4>& full_metadata,
                                 std::uint64_t local) {
    local &= kLocalMetadataMask;
    full_metadata[0] =
        (full_metadata[0] & 0x0001ffffu) |
        static_cast<std::uint32_t>(local << kMetadataOffset);
    full_metadata[1] = static_cast<std::uint32_t>(local >> 15u);
    full_metadata[2] =
        (full_metadata[2] & ~UINT32_C(0x01ff)) |
        static_cast<std::uint32_t>((local >> 47u) & 0x01ffu);
  }

 private:
  const std::array<SmallTageTableUpdate, kTables>&
  current_parent_updates() const {
    // The parent update is a pure function of the registered S1 update, not
    // of this call's prediction input.  outputs() and step() therefore see
    // the same value until step() advances that registered state.
    if (!parent_update_cache_valid_) {
      parent_update_cache_ = compute_parent_updates();
      parent_update_cache_valid_ = true;
    }
    return parent_update_cache_;
  }

  std::array<SmallTageTableUpdate, kTables> compute_parent_updates() const {
    std::array<SmallTageTableUpdate, kTables> result{};
    for (SmallTageTableUpdate& update : result) {
      update.pc = s1_update_.pc & kPcMask;
      update.history = s1_update_.ghist.old_history;
    }

    const SmallTageMetadata metadata =
        unpack_metadata(local_metadata(s1_update_.meta));
    const bool commit = !s1_update_.is_mispredict_update &&
                        !s1_update_.is_repair_update &&
                        (s1_update_.btb_mispredicts & 0x0fu) == 0;

    // tage.scala initializes these Vecs with DontCare and assigns a lane only
    // inside the provider/allocation cases below.  The lowered locked RTL does
    // not choose zero for the inactive payloads: every table gets the slot's
    // update_was_taken and provider_ctr as its deterministic defaults.  That
    // normally looks dead, but TageTable enqueues all four computed counters
    // into wrbypass whenever *any* lane is masked.  An inactive lane can then
    // become the old counter of a later same-row update, so these values are
    // part of the real storage transition rather than ignorable don't-care.
    for (SmallTageTableUpdate& update : result) {
      for (std::size_t slot = 0; slot < kSlots; ++slot) {
        update.taken[slot] =
            s1_update_.cfi_valid &&
            (s1_update_.cfi_idx & 0x03u) == slot &&
            s1_update_.cfi_taken;
        update.old_ctr[slot] = metadata.provider_ctr[slot] & 0x07u;
      }
    }

    for (std::size_t slot = 0; slot < kSlots; ++slot) {
      if (!s1_update_valid_ || !commit ||
          ((s1_update_.br_mask >> slot) & 1u) == 0 ||
          !metadata.provider[slot].valid)
        continue;
      const std::uint8_t provider = metadata.provider[slot].bits & 0x07u;
      if (provider >= kTables) continue;
      SmallTageTableUpdate& update = result[provider];
      update.mask[slot] = true;
      update.u_mask[slot] = true;
      update.alloc[slot] = false;
      update.u[slot] = update_usefulness(
          metadata.provider_u[slot], metadata.alt_differs[slot],
          s1_update_.cfi_mispredicted &&
              (s1_update_.cfi_idx & 0x03u) == slot);
    }

    if (s1_update_valid_ && commit && s1_update_.cfi_mispredicted &&
        s1_update_.cfi_valid) {
      const std::size_t slot = s1_update_.cfi_idx & 0x03u;
      const SmallTageValidTable allocation = metadata.allocate[slot];
      if (allocation.valid && allocation.bits < kTables) {
        SmallTageTableUpdate& update = result[allocation.bits];
        update.mask[slot] = true;
        update.taken[slot] = s1_update_.cfi_taken;
        update.alloc[slot] = true;
        update.u_mask[slot] = true;
        update.u[slot] = 0;
      } else if (metadata.provider[slot].valid) {
        const std::uint8_t provider = metadata.provider[slot].bits;
        for (std::size_t table = provider + 1u; table < kTables; ++table) {
          result[table].u_mask[slot] = true;
          result[table].u[slot] = 0;
        }
      }
    }
    return result;
  }

  static std::uint8_t update_usefulness(std::uint8_t usefulness,
                                        bool alternate_differs,
                                        bool mispredict) {
    usefulness &= 0x03u;
    if (!alternate_differs) return usefulness;
    if (mispredict)
      return usefulness == 0
                 ? 0
                 : static_cast<std::uint8_t>(usefulness - 1u);
    return usefulness == 3
               ? 3
               : static_cast<std::uint8_t>(usefulness + 1u);
  }

  static std::uint8_t priority_encode(std::uint8_t bits) {
    for (std::uint8_t index = 0; index < 8; ++index)
      if (((bits >> index) & 1u) != 0) return index;
    // Chisel's PriorityEncoder on the widened eight-bit allocation mask
    // resolves an all-zero input to the final index.  The accompanying
    // Valid bit is false, but the payload is still packed into FTQ metadata.
    return 7;
  }

  static std::uint8_t next_lfsr(std::uint8_t state) {
    state &= 0x3fu;
    return static_cast<std::uint8_t>(
        ((state << 1u) & 0x3eu) |
        (((state >> 5u) ^ (state >> 4u)) & 1u));
  }

  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40u) - UINT64_C(1);
  static constexpr std::uint64_t kLocalMetadataMask =
      (UINT64_C(1) << 56u) - UINT64_C(1);

  std::array<SmallTageTable, kTables> tables_;
  bool f1_valid_ = false;
  std::uint64_t f1_pc_ = 0;
  bool s1_update_valid_ = false;
  SmallFtqBpdUpdate s1_update_{};
  std::array<SmallTageTableUpdate, kTables> parent_updates_{};
  mutable std::array<SmallTageTableUpdate, kTables>
      parent_update_cache_{};
  mutable bool parent_update_cache_valid_ = false;
  std::array<std::uint8_t, kSlots> lfsr_{};
  std::uint64_t table_read_epoch_ = 0;
  std::uint64_t table_bypass_epoch_ = 0;
  std::uint64_t pipeline_epoch_ = 0;
};

/** Only the response fields are (re)written; the boundary fields of
  * `result` are the caller's. */
inline void connect_btb_to_tage_into(SmallTageInputs& result,
                                     const SmallBtbOutputs& btb) {
  result.resp_in_f1 = btb.f1;
  result.resp_in_f2 = btb.f2;
  result.resp_in_f3 = btb.f3;
}
inline SmallTageInputs connect_btb_to_tage(
    const SmallTageInputs& boundary, const SmallBtbOutputs& btb) {
  SmallTageInputs result = boundary;
  connect_btb_to_tage_into(result, btb);
  return result;
}

}  // namespace chisa::boom_system::components
