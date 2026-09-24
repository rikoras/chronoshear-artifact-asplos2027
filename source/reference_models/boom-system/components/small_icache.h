#pragma once
#include "../../boom_model/common/boom_config.h"
// ============================================================================
// Small BOOM L1 instruction cache.
//
// This is the locked SmallBoomConfig instance from boom/ifu/icache.scala:
//   64 sets x 4 ways, 64-byte lines, one 8-byte fetch bank, 8 refill beats.
// It owns the tag/data arrays, valid bits, two-cycle lookup pipeline, miss
// request, refill counter, invalidation tracking, and replacement LFSR.
// TileLink A/D are the explicit boundary to the still-separate memory system.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

namespace chisa::boom_system::components {

struct SmallICacheInputs {
  bool reset = false;

  bool req_valid = false;
  std::uint64_t req_addr = 0;
  std::uint32_t s1_paddr = 0;
  bool s1_kill = false;
  bool s2_kill = false;
  bool invalidate = false;

  bool tl_a_ready = false;
  bool tl_d_valid = false;
  std::uint8_t tl_d_opcode = 0;
  std::uint8_t tl_d_size = 0;
  std::uint64_t tl_d_data = 0;
  std::uint64_t tl_d_data_hi = 0;
};

struct SmallICacheMemoryInputs {
  bool tl_a_ready = false;
  bool tl_d_valid = false;
  std::uint8_t tl_d_opcode = 0;
  std::uint8_t tl_d_size = 0;
  std::uint64_t tl_d_data = 0;
  std::uint64_t tl_d_data_hi = 0;
};

struct SmallICacheOutputs {
  bool req_ready = true;
  bool resp_valid = false;
  std::uint64_t resp_data = 0;

  bool acquire_valid = false;
  std::uint32_t acquire_address = 0;
  bool acquire_fire = false;

  bool s0_valid = false;
  std::array<bool, boomcfg::ICACHE_WAYS> s1_tag_hit{};
  bool s1_hit = false;
  bool s2_miss = false;
  bool refill_one_beat = false;
  bool refill_done = false;
  std::uint16_t refill_count = 0;
  std::uint8_t replacement_way = 0;
};

struct SmallICacheResponse {
  bool valid = false;
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;
};

struct SmallICacheWriteEvent {
  std::uint64_t data_hi = 0;
  bool tag_valid = false;
  std::uint8_t tag_way = 0;
  std::uint8_t tag_set = 0;
  std::uint32_t tag = 0;

  bool data_valid = false;
  std::uint8_t data_way = 0;
  std::uint16_t data_row = 0;
  std::uint64_t data = 0;
};

class SmallICache {
 public:
  static constexpr std::size_t kSets = 64;
  static constexpr std::size_t kWays = boomcfg::ICACHE_WAYS;
  static constexpr std::size_t kRowsPerWay = 512;
  static constexpr std::size_t kRefillBeats =
      boomcfg::ICACHE_REFILL_BEATS;
  static_assert(kWays != 0 && (kWays & (kWays - 1)) == 0,
                "I-cache way count must be a power of two");

  SmallICacheOutputs outputs(const SmallICacheInputs& input) const {
    return evaluate(input);
  }

  SmallICacheResponse held_response() const {
    SmallICacheResponse result;
    result.valid = s2_valid_ && s2_hit_;
    for (std::size_t way = 0; way < kWays; ++way)
      if (s2_tag_hit_[way]) {
        result.data |= data_read_[way];
        result.data_hi |= data_read_hi_[way];
      }
    return result;
  }

  void commit(const SmallICacheInputs& input,
              const SmallICacheOutputs& output) {
    const bool old_s1_valid = s1_valid_;

    // SyncReadMem outputs and all combinational decisions below observe the
    // cycle-start arrays.  Save them before applying the refill writes.
    std::array<std::uint64_t, kWays> next_data_read{};
    std::array<std::uint64_t, kWays> next_data_read_hi{};
    for (std::size_t way = 0; way < kWays; ++way) {
      const bool odd_row = (data_read_row_[way] & 1u) != 0;
      next_data_read[way] = odd_row ? oracle_bank1_read_[way]
                                     : oracle_bank0_read_[way];
      if constexpr (boomcfg::ICACHE_BEAT_WORDS == 2) {
        next_data_read_hi[way] = odd_row ? oracle_bank0_read_[way]
                                        : oracle_bank1_read_[way];
      }
    }

    const bool capture_refill_paddr =
        s1_valid_ && !(refill_valid_ || output.s2_miss);
    const bool refill_has_data = output.refill_one_beat;
    const std::uint8_t refill_way = output.replacement_way;
    const std::uint8_t refill_set =
        static_cast<std::uint8_t>((refill_paddr_ >> 6) & 0x3fu);
    const std::uint16_t refill_row = static_cast<std::uint16_t>(
        (static_cast<std::uint16_t>(refill_set) << 3) |
        ((output.refill_count &
          (boomcfg::ICACHE_REFILL_BEATS - 1)) *
         boomcfg::ICACHE_BEAT_WORDS));

    last_write_ = SmallICacheWriteEvent{};
    if (output.refill_done) {
      last_write_.tag_valid = true;
      last_write_.tag_way = refill_way;
      last_write_.tag_set = refill_set;
      last_write_.tag = (refill_paddr_ >> 12) & 0xfffffu;
    }
    if (refill_has_data && !invalidated_) {
      last_write_.data_valid = true;
      last_write_.data_way = refill_way;
      last_write_.data_row = refill_row;
      last_write_.data = input.tl_d_data;
      last_write_.data_hi = input.tl_d_data_hi;
    }

    // Pipeline registers.  BOOM's I-cache leaves these unreset; the enclosing
    // reset traffic drains them naturally, just as the zero-init reference
    // Verilator build does.
    s1_valid_ = output.s0_valid;
    s2_valid_ = old_s1_valid && !input.s1_kill;
    s2_hit_ = output.s1_hit;
    s2_tag_hit_ = output.s1_tag_hit;
    data_read_ = next_data_read;
    data_read_hi_ = next_data_read_hi;

    // A successful CPU request starts the synchronous tag/data reads.  A D
    // data beat makes req.ready low, so it cannot also update these addresses.
    if (output.s0_valid && !output.refill_done)
      tag_read_set_ = static_cast<std::uint8_t>((input.req_addr >> 6) & 0x3fu);
    if (output.s0_valid) {
      // The two-bank I-cache rotates its response around the requested bank:
      // a bank-1 request returns that 8-byte bank first and bank 0 of the
      // next chunk second.  In the model's linear 8-byte row image this is
      // exactly [row, row+1]; rounding row down to a 16-byte beat silently
      // returned the preceding bank and corrupted F3 assembly.
      const std::uint16_t row =
          static_cast<std::uint16_t>((input.req_addr >> 3) & 0x1ffu);
      for (std::size_t way = 0; way < kWays; ++way)
        data_read_row_[way] = row;
    }

    if (capture_refill_paddr) refill_paddr_ = input.s1_paddr;

    if (last_write_.tag_valid)
      sets_[last_write_.tag_set].tag[last_write_.tag_way] =
          last_write_.tag;
    if (last_write_.data_valid) {
      data_[last_write_.data_way][last_write_.data_row] =
          last_write_.data;
      if constexpr (boomcfg::ICACHE_BEAT_WORDS == 2) {
        data_[last_write_.data_way][last_write_.data_row + 1] =
            last_write_.data_hi;
      }
    }

    // Valid-bit priority is reset, invalidate, then the current refill beat.
    if (input.reset || input.invalidate) {
      for (auto& set : sets_) set.valid.fill(false);
    } else if (refill_has_data) {
      sets_[refill_set].valid[refill_way] =
          output.refill_done && !invalidated_;
    }

    // `invalidated` records a flush only while a refill is outstanding.
    if (!refill_valid_)
      invalidated_ = false;
    else if (input.invalidate)
      invalidated_ = true;

    const bool old_refill_valid = refill_valid_;
    if (input.reset || output.refill_done)
      refill_valid_ = false;
    else if (output.acquire_fire)
      refill_valid_ = true;
    delayed_refill_valid_ = old_refill_valid;

    if (input.reset) {
      refill_counter_ = 0;
    } else if (input.tl_d_valid) {
      if (refill_counter_ == 0)
        refill_counter_ = has_data(input.tl_d_opcode)
                              ? beats_minus_one(input.tl_d_size)
                              : 0;
      else
        refill_counter_ =
            static_cast<std::uint16_t>((refill_counter_ - 1u) & 0x1ffu);
    }

    if (input.reset) {
      lfsr_ = 1;
    } else if (output.acquire_fire) {
      const std::uint16_t feedback = static_cast<std::uint16_t>(
          ((lfsr_ >> 15) ^ (lfsr_ >> 13) ^ (lfsr_ >> 12) ^
           (lfsr_ >> 10)) &
          1u);
      lfsr_ = static_cast<std::uint16_t>((lfsr_ << 1) | feedback);
    }

    bool oracle_read_changed = false;
    for (std::size_t way = 0; way < kWays; ++way) {
      const std::size_t row = data_read_row_[way];
      const std::size_t bank0_row =
          (row & 1u) ? (row + 1) % kRowsPerWay : row;
      const std::size_t bank1_row =
          (row & 1u) ? row : (row + 1) % kRowsPerWay;
      const std::uint64_t bank0 = data_[way][bank0_row];
      const std::uint64_t bank1 = data_[way][bank1_row];
      const std::uint32_t tag = sets_[tag_read_set_].tag[way];
      oracle_read_changed |= oracle_bank0_read_[way] != bank0 ||
                             oracle_bank1_read_[way] != bank1 ||
                             oracle_tag_read_[way] != tag;
      oracle_bank0_read_[way] = bank0;
      oracle_bank1_read_[way] = bank1;
      oracle_tag_read_[way] = tag;
    }
    if (oracle_read_changed) ++oracle_read_epoch_;
  }

  void step(const SmallICacheInputs& input) {
    commit(input, evaluate(input));
  }

  const bool& s1_valid() const { return s1_valid_; }
  const bool& s2_valid() const { return s2_valid_; }
  const bool& s2_hit() const { return s2_hit_; }
  const bool& invalidated() const { return invalidated_; }
  const bool& refill_valid() const { return refill_valid_; }
  const bool& delayed_refill_valid() const { return delayed_refill_valid_; }
  const std::uint32_t& refill_paddr() const { return refill_paddr_; }
  const std::uint16_t& refill_counter() const { return refill_counter_; }
  const std::uint16_t& lfsr() const { return lfsr_; }
  const std::uint8_t& tag_read_set() const { return tag_read_set_; }
  const std::uint16_t& data_read_row(std::size_t way) const {
    return data_read_row_[way];
  }

  bool valid(std::size_t way, std::size_t set) const {
    return sets_[set].valid[way];
  }
  std::uint32_t tag(std::size_t way, std::size_t set) const {
    return sets_[set].tag[way];
  }
  std::uint64_t data(std::size_t way, std::size_t row) const {
    return data_[way][row];
  }
  const std::array<bool, kWays>& s2_tag_hit() const {
    return s2_tag_hit_;
  }
  const std::uint64_t& oracle_bank0_read_for_diagnostic(
      std::size_t way) const {
    return oracle_bank0_read_[way];
  }
  const std::uint64_t& oracle_bank1_read_for_diagnostic(
      std::size_t way) const {
    return oracle_bank1_read_[way];
  }
  const std::uint32_t& oracle_tag_read_for_diagnostic(
      std::size_t way) const {
    return oracle_tag_read_[way];
  }
  const std::uint64_t& oracle_read_epoch_for_diagnostic() const {
    return oracle_read_epoch_;
  }
  const SmallICacheWriteEvent& last_write() const { return last_write_; }

 private:
  static bool has_data(std::uint8_t opcode) {
    // TileLink D HasData is opcode(0) for the generated Get-only client.
    return (opcode & 1u) != 0;
  }

  static std::uint16_t beats_minus_one(std::uint8_t size) {
    const unsigned shift = size & 0x0fu;
    const std::uint16_t shifted =
        shift >= 12 ? 0 : static_cast<std::uint16_t>(0x0fffu << shift);
    return static_cast<std::uint16_t>(
        ((~shifted) & 0x0fffu) >> boomcfg::TILE_BEAT_SHIFT);
  }

  SmallICacheOutputs evaluate(const SmallICacheInputs& input) const {
    SmallICacheOutputs result;
    result.replacement_way =
        static_cast<std::uint8_t>(lfsr_ & (kWays - 1u));

    const bool d_has_data = has_data(input.tl_d_opcode);
    result.refill_one_beat = input.tl_d_valid && d_has_data;
    result.req_ready = !result.refill_one_beat;
    result.s0_valid = input.req_valid && result.req_ready;

    const std::uint16_t beats1 =
        d_has_data ? beats_minus_one(input.tl_d_size) : 0;
    const std::uint16_t counter1 =
        static_cast<std::uint16_t>((refill_counter_ - 1u) & 0x1ffu);
    result.refill_count = static_cast<std::uint16_t>(
        beats1 & static_cast<std::uint16_t>((~counter1) & 0x1ffu));
    const bool last = refill_counter_ == 1 || beats1 == 0;
    result.refill_done = result.refill_one_beat && last;

    const std::uint8_t s1_set =
        static_cast<std::uint8_t>((input.s1_paddr >> 6) & 0x3fu);
    const std::uint32_t s1_tag = (input.s1_paddr >> 12) & 0xfffffu;
    for (std::size_t way = 0; way < kWays; ++way) {
      result.s1_tag_hit[way] =
          sets_[s1_set].valid[way] && sets_[tag_read_set_].tag[way] == s1_tag;
      result.s1_hit = result.s1_hit || result.s1_tag_hit[way];
    }

    const SmallICacheResponse response = held_response();
    result.resp_valid = response.valid;
    result.resp_data = response.data;

    result.s2_miss =
        s2_valid_ && !s2_hit_ && !delayed_refill_valid_;
    const AcquireOffer offer = held_acquire_offer(input.s2_kill);
    result.acquire_valid = offer.valid;
    result.acquire_address = offer.address;
    result.acquire_fire = result.acquire_valid && input.tl_a_ready;
    return result;
  }

 public:
  /** The TileLink A-channel offer, from registered state plus the registered
    * S2 kill.  outputs() uses this same expression; the system guider uses it
    * to place the offer without a full frontend evaluation, since neither
    * valid nor address depends on tl_a_ready. */
  struct AcquireOffer {
    bool valid = false;
    std::uint32_t address = 0;
  };
  AcquireOffer held_acquire_offer(bool s2_kill) const {
    AcquireOffer offer;
    const bool miss = s2_valid_ && !s2_hit_ && !delayed_refill_valid_;
    offer.valid = miss && !refill_valid_ && !s2_kill;
    offer.address = refill_paddr_ & UINT32_C(0xffffffc0);
    return offer;
  }

 private:

  // One record per set: the tag compare reads every way's tag and valid
  // bit of one set each cycle, so keep them in one line per set instead
  // of one line per way per array.
  struct SetMeta {
    std::array<std::uint32_t, kWays> tag{};
    std::array<bool, kWays> valid{};
  };
  std::array<SetMeta, kSets> sets_{};
  std::array<std::array<std::uint64_t, kRowsPerWay>, kWays> data_{};

  std::uint8_t tag_read_set_ = 0;
  std::array<std::uint16_t, kWays> data_read_row_{};
  std::array<std::uint64_t, kWays> data_read_{};
  std::array<std::uint64_t, kWays> data_read_hi_{};
  std::array<bool, kWays> s2_tag_hit_{};
  // The exported MPORT values and the functional SyncReadMem result address
  // the same rows one cycle apart.  Keep the post-commit MPORT image so the
  // following commit can reuse it instead of fetching every data row twice.
  std::array<std::uint64_t, kWays> oracle_bank0_read_{};
  std::array<std::uint64_t, kWays> oracle_bank1_read_{};
  std::array<std::uint32_t, kWays> oracle_tag_read_{};
  std::uint64_t oracle_read_epoch_ = 0;

  bool s1_valid_ = false;
  bool s2_valid_ = false;
  bool s2_hit_ = false;
  bool invalidated_ = false;
  bool refill_valid_ = false;
  bool delayed_refill_valid_ = false;
  std::uint32_t refill_paddr_ = 0;
  std::uint16_t refill_counter_ = 0;
  std::uint16_t lfsr_ = 0;
  SmallICacheWriteEvent last_write_{};
};

}  // namespace chisa::boom_system::components
