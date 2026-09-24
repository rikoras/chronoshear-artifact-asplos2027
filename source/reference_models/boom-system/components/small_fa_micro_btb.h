#pragma once
// ============================================================================
// Small BOOM fully-associative MicroBTB (16 ways x 4 fetch slots).
//
// This is component 3 of the locked TAGE-L composition.  It owns the
// resettable tag/type/counter registers, unreset target offsets, F1 lookup,
// F2/F3 response registers, the two-stage 8-bit prediction metadata path,
// and commit training.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

#include "small_f0_f2.h"
#include "small_ftq.h"

namespace chisa::boom_system::components {

struct SmallFaMicroBtbInputs {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;
  bool update_valid = false;
  SmallFtqBpdUpdate update{};
};

struct SmallFaMicroBtbMetaEntry {
  bool is_br = false;
  std::uint64_t tag = 0;
  std::uint8_t counter = 0;
};

struct SmallFaMicroBtbOutputs {
  SmallFrontendPredictionResponse f1{};
  SmallFrontendPredictionResponse f2{};
  SmallFrontendPredictionResponse f3{};
  std::array<std::uint16_t, 4> hit_oh{};
  std::array<bool, 4> hits{};
  std::array<std::uint8_t, 4> hit_way{};
  std::uint8_t allocation_way = 0;
  std::uint8_t write_way = 0;
  std::uint8_t s1_meta = 0;
  std::uint8_t f3_meta = 0;
};

class SmallFaMicroBtb {
 public:
  static constexpr std::size_t kWays = 16;

  SmallFaMicroBtbOutputs outputs(const SmallFaMicroBtbInputs& input) const {

    SmallFaMicroBtbOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallFaMicroBtbInputs& input, SmallFaMicroBtbOutputs& result) const {
    (void)input;
    result = SmallFaMicroBtbOutputs{};
    for (std::size_t slot = 0; slot < 4; ++slot) {
      for (std::size_t way = 0; way < kWays; ++way) {
        if (meta_[way][slot].tag == s1_index_)
          result.hit_oh[slot] |= static_cast<std::uint16_t>(1u << way);
      }
      result.hits[slot] = result.hit_oh[slot] != 0;
      result.hit_way[slot] = priority_encode(result.hit_oh[slot]);
      const std::size_t way = result.hit_way[slot];
      const SmallFaMicroBtbMetaEntry& meta = meta_[way][slot];
      SmallFrontendPrediction& prediction = result.f1.preds[slot];
      prediction.predicted_pc_valid = s1_valid_ && result.hits[slot];
      prediction.predicted_pc =
          add_offset(s1_pc_, slot, offsets_[way][slot]);
      prediction.is_br = prediction.predicted_pc_valid && meta.is_br;
      prediction.is_jal = prediction.predicted_pc_valid && !meta.is_br;
      prediction.taken = !meta.is_br || ((meta.counter >> 1u) & 1u) != 0;
    }

    result.f2 = f2_response_;
    result.f3 = f3_response_;
    result.allocation_way = allocation_way();
    std::uint16_t any_hit_ways = 0;
    for (const std::uint16_t hits : result.hit_oh) any_hit_ways |= hits;
    result.write_way = any_hit_ways != 0
                           ? priority_encode(any_hit_ways)
                           : result.allocation_way;
    std::uint8_t hit_mask = 0;
    for (std::size_t slot = 0; slot < 4; ++slot)
      hit_mask |= static_cast<std::uint8_t>(result.hits[slot] << slot);
    result.s1_meta = static_cast<std::uint8_t>(
        (hit_mask << 4u) | (result.write_way & 0x0fu));
    result.f3_meta = f3_meta_stage2_;
    return;
  }

  void commit(const SmallFaMicroBtbInputs& input,
              const SmallFaMicroBtbOutputs& output) {
    bool storage_changed = false;
    const bool commit = !s1_update_.is_mispredict_update &&
                        !s1_update_.is_repair_update &&
                        (s1_update_.btb_mispredicts & 0x0fu) == 0;
    const std::uint8_t update_way = local_update_write_way();
    const std::uint8_t cfi_slot =
        static_cast<std::uint8_t>(s1_update_.cfi_idx & 0x03u);

    if (s1_update_valid_ && commit && s1_update_.cfi_valid &&
        s1_update_.cfi_taken) {
      const std::int16_t next_offset = update_offset();
      if (offsets_[update_way][cfi_slot] != next_offset) {
        offsets_[update_way][cfi_slot] = next_offset;
        ++offset_way_epochs_[update_way];
        storage_changed = true;
      }
    }

    if (s1_update_valid_ && commit) {
      for (std::size_t slot = 0; slot < 4; ++slot) {
        const bool branch = ((s1_update_.br_mask >> slot) & 1u) != 0;
        const bool taken_cfi = s1_update_.cfi_valid &&
                               cfi_slot == slot &&
                               s1_update_.cfi_taken;
        if (!branch && !taken_cfi) continue;

        const bool was_taken = s1_update_.cfi_valid && cfi_slot == slot &&
                               (s1_update_.cfi_taken ||
                                s1_update_.cfi_is_jal);
        SmallFaMicroBtbMetaEntry& meta = meta_[update_way][slot];
        const SmallFaMicroBtbMetaEntry previous = meta;
        meta.is_br = branch;
        const unsigned entry_phase = static_cast<unsigned>(
            ((update_way * std::size_t{4} + slot + 1) * kIndexWidth) & 3u);
        meta_fold_ = static_cast<std::uint8_t>(
            meta_fold_ ^ fold_index(meta.tag, entry_phase) ^
            fold_index(update_index(), entry_phase));
        meta.tag = update_index();
        if (!local_update_hit(slot)) {
          meta.counter = was_taken ? 3 : 0;
        } else {
          meta.counter = update_counter(meta.counter, was_taken);
        }
        if (meta.is_br != previous.is_br || meta.tag != previous.tag ||
            meta.counter != previous.counter) {
          ++meta_epochs_[update_way][slot];
          storage_changed = true;
        }
      }
    }

    f3_response_ = f2_response_;
    f2_response_ = output.f1;
    f3_meta_stage2_ = f3_meta_stage1_;
    f3_meta_stage1_ = output.s1_meta;
    s1_valid_ = input.f0_valid;
    s1_index_ = fetch_index(input.f0_pc);
    s1_pc_ = input.f0_pc & kPcMask;
    s1_update_valid_ = input.update_valid;
    s1_update_ = input.update;
    s1_update_.pc &= kPcMask;
    s1_update_.target &= kPcMask;

    // Only the metadata array is RegInit state.  Target offsets and all
    // pipeline registers are deliberately unreset in the RTL.
    if (input.reset) {
      for (std::size_t way = 0; way < kWays; ++way) {
        for (std::size_t slot = 0; slot < 4; ++slot) {
          SmallFaMicroBtbMetaEntry& entry = meta_[way][slot];
          if (entry.is_br || entry.tag != 0 || entry.counter != 0) {
            ++meta_epochs_[way][slot];
            storage_changed = true;
          }
          entry = SmallFaMicroBtbMetaEntry{};
        }
      }
      meta_fold_ = 0;
    }
    if (storage_changed) ++storage_epoch_;
    // All scalar streams owned by this component are derived from the
    // pipeline fields assigned above.  A one-word watch is substantially
    // cheaper than comparing the complete predictor every cycle.
    ++pipeline_epoch_;
    refresh_packed_snapshots();  // the frontend commits directly (step() only on reset)
  }

  void step(const SmallFaMicroBtbInputs& input) {
    commit(input, outputs(input));
    refresh_packed_snapshots();
  }
  /** Packed views of the offset/meta storage (the lowered bank streams),
    * recomputed only when the storage epoch moved so the sampler can bind
    * them as plain fields. */
  void refresh_packed_snapshots() {
    if (packed_snapshot_epoch_ == storage_epoch_ && packed_snapshot_valid_) return;
    for (std::size_t way = 0; way < kWays; ++way) {
      packed_offsets_snapshot_[way] = packed_offsets_now(way);
      for (std::size_t slot = 0; slot < 4; ++slot)
        packed_meta_snapshot_[way][slot] = packed_meta_now(way, slot);
    }
    packed_snapshot_epoch_ = storage_epoch_;
    packed_snapshot_valid_ = true;
  }
  const std::uint64_t& packed_offsets(std::size_t way) const {
    return packed_offsets_snapshot_[way];
  }
  const std::uint64_t& packed_meta(std::size_t way, std::size_t slot) const {
    return packed_meta_snapshot_[way][slot];
  }

  const bool& s1_valid() const { return s1_valid_; }
  const std::uint64_t& s1_index() const { return s1_index_; }
  const std::uint64_t& s1_pc() const { return s1_pc_; }
  const bool& s1_update_valid() const { return s1_update_valid_; }
  const SmallFtqBpdUpdate& s1_update() const { return s1_update_; }
  std::uint64_t s1_update_index() const { return update_index(); }
  std::uint8_t local_update_meta() const {
    return static_cast<std::uint8_t>((s1_update_.meta[0] >> 8u) & 0xffu);
  }
  std::uint8_t local_update_write_way() const {
    return static_cast<std::uint8_t>(local_update_meta() & 0x0fu);
  }
  bool local_update_hit(std::size_t slot) const {
    return ((local_update_meta() >> (4u + slot)) & 1u) != 0;
  }
  const SmallFaMicroBtbMetaEntry& meta(std::size_t way,
                                       std::size_t slot) const {
    return meta_[way][slot];
  }
  const std::int16_t& offset(std::size_t way, std::size_t slot) const {
    return offsets_[way][slot];
  }
  std::uint16_t offset_bits(std::size_t way, std::size_t slot) const {
    return static_cast<std::uint16_t>(offsets_[way][slot]) & 0x1fffu;
  }
  // Packing used by the lowered four-slot `btb__v2_bank_0_<way>` state
  // stream: slot 0 occupies the most-significant 13 bits and slot 3 the
  // least-significant 13 bits.
  std::uint64_t packed_offsets_now(std::size_t way) const {
    std::uint64_t result = 0;
    for (std::size_t slot = 0; slot < 4; ++slot)
      result |= static_cast<std::uint64_t>(offset_bits(way, slot))
                << ((3u - slot) * 13u);
    return result;
  }
  // Lowered `meta__v2_bank_<way>_<slot>` layout: tag, is_br, ctr[1:0].
  // The tag is 37 bits on Small and 36 bits on Large.
  std::uint64_t packed_meta_now(std::size_t way, std::size_t slot) const {
    const SmallFaMicroBtbMetaEntry& entry = meta(way, slot);
    return ((entry.tag & kIndexMask) << 3u) |
           (static_cast<std::uint64_t>(entry.is_br) << 2u) |
           static_cast<std::uint64_t>(entry.counter & 0x03u);
  }
  const std::uint64_t& storage_epoch_for_diagnostic() const {
    return storage_epoch_;
  }
  const std::uint64_t& offset_way_epoch_for_diagnostic(
      std::size_t way) const {
    return offset_way_epochs_[way];
  }
  const std::uint64_t& meta_epoch_for_diagnostic(std::size_t way,
                                                  std::size_t slot) const {
    return meta_epochs_[way][slot];
  }
  const std::uint64_t& pipeline_epoch_for_diagnostic() const {
    return pipeline_epoch_;
  }
  const SmallFrontendPredictionResponse& f2_response() const {
    return f2_response_;
  }
  const SmallFrontendPredictionResponse& f3_response() const {
    return f3_response_;
  }
  std::uint8_t f3_meta_stage1() const { return f3_meta_stage1_; }
  const std::uint8_t& f3_meta_stage2() const { return f3_meta_stage2_; }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);
  static constexpr unsigned kIndexWidth =
      40u - static_cast<unsigned>(boomcfg::FETCH_IDX_SHIFT);
  static constexpr std::uint64_t kIndexMask =
      (UINT64_C(1) << kIndexWidth) - UINT64_C(1);

  static std::uint64_t fetch_index(std::uint64_t pc) {
    return (pc >> boomcfg::FETCH_IDX_SHIFT) & kIndexMask;
  }

  std::uint64_t update_index() const { return fetch_index(s1_update_.pc); }

  static std::uint8_t priority_encode(std::uint16_t bits) {
    for (std::uint8_t index = 0; index < 16; ++index)
      if (((bits >> index) & 1u) != 0) return index;
    // Chisel 3.4's 16-way PriorityEncoder lowers the all-zero input to 15.
    return 15;
  }

  static std::uint8_t update_counter(std::uint8_t value, bool taken) {
    value &= 0x03u;
    if (taken) return value == 3 ? 3 : static_cast<std::uint8_t>(value + 1u);
    return value == 0 ? 0 : static_cast<std::uint8_t>(value - 1u);
  }

  static std::int16_t sign_extend_offset(std::uint16_t bits) {
    bits &= 0x1fffu;
    if ((bits & 0x1000u) != 0) bits |= 0xe000u;
    return static_cast<std::int16_t>(bits);
  }

  std::int16_t update_offset() const {
    const std::uint64_t base =
        (s1_update_.pc +
         (static_cast<std::uint64_t>(s1_update_.cfi_idx & 0x03u) << 1u)) &
        kPcMask;
    return sign_extend_offset(static_cast<std::uint16_t>(
        (s1_update_.target - base) & 0x1fffu));
  }

  static std::uint64_t add_offset(std::uint64_t pc, std::size_t slot,
                                  std::int16_t offset) {
    return (pc + static_cast<std::uint64_t>(slot << 1u) +
            static_cast<std::uint64_t>(static_cast<std::int64_t>(offset))) &
           kPcMask;
  }

  /** XOR-fold one predictor-tag field into the four-bit allocation hash.
    *
    * The RTL reduces Cat(meta.asUInt, s1_idx) bitwise into four bits, bit b
    * landing in result bit (offset+b) mod 4.  Bit-parallel form: within one
    * field, the bits of residue class j (b === j mod 4) contribute their
    * parity to result bit (j+phase) mod 4, where phase is the field's start
    * offset mod 4.  Identical arithmetic, ~40x fewer operations; held to the
    * RTL by the component differential. */
  static std::uint8_t fold_index(std::uint64_t value, unsigned phase) {
    value &= kIndexMask;
    std::uint8_t out = 0;
    for (unsigned j = 0; j < 4; ++j) {
      const std::uint64_t mask =
          (UINT64_C(0x1111111111111111) << j) & kIndexMask;
      if (__builtin_parityll(value & mask))
        out ^= static_cast<std::uint8_t>(1u << ((j + phase) & 3u));
    }
    return out;
  }

  std::uint8_t allocation_way() const {
    // Cat(meta.asUInt, s1_idx): s1_idx is the least-significant field with
    // start offset 0; entry k = way*4+slot starts at
    // kIndexWidth*(k+1).  Small's 37-bit tags rotate each entry by one;
    // Large's 36-bit tags keep every entry at phase zero.  The meta
    // contribution is delta-maintained at the single tag write site (XOR is
    // its own inverse), so the per-lookup cost is the s1 fold alone.
    return static_cast<std::uint8_t>(
        (fold_index(s1_index_, 0) ^ meta_fold_) & 0x0fu);
  }

  std::array<std::array<SmallFaMicroBtbMetaEntry, 4>, kWays> meta_{};
  std::uint8_t meta_fold_ = 0;  // XOR-fold of all resident tags
  std::array<std::array<std::int16_t, 4>, kWays> offsets_{};
  std::uint64_t storage_epoch_ = 0;
  std::uint64_t packed_snapshot_epoch_ = 0;
  bool packed_snapshot_valid_ = false;
  std::array<std::uint64_t, kWays> packed_offsets_snapshot_{};
  std::array<std::array<std::uint64_t, 4>, kWays> packed_meta_snapshot_{};
  std::array<std::uint64_t, kWays> offset_way_epochs_{};
  std::array<std::array<std::uint64_t, 4>, kWays> meta_epochs_{};
  std::uint64_t pipeline_epoch_ = 0;

  bool s1_valid_ = false;
  std::uint64_t s1_index_ = 0;
  std::uint64_t s1_pc_ = 0;
  SmallFrontendPredictionResponse f2_response_{};
  SmallFrontendPredictionResponse f3_response_{};
  std::uint8_t f3_meta_stage1_ = 0;
  std::uint8_t f3_meta_stage2_ = 0;

  bool s1_update_valid_ = false;
  SmallFtqBpdUpdate s1_update_{};
};

}  // namespace chisa::boom_system::components
