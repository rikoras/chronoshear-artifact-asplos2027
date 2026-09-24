#pragma once
#include "../../boom_model/common/boom_config.h"
#include "../../boom_model/common/model_mode.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace chisa::boom_system::components {

// The common registered part of Rocket TLB and BOOM NBDTLB.  Lookup, PTW
// request, PTW refill, and sfence are deliberately separate faces: they can
// overlap on one edge and the RTL gives them different priorities.

struct SmallTlbEntryData {
  std::uint32_t ppn = 0;  // SmallBoom paddrBits=32 -> ppnBits=20.
  bool u = false;
  bool g = false;
  bool ae = false;
  bool sw = false;
  bool sx = false;
  bool sr = false;
  bool pw = false;
  bool px = false;
  bool pr = false;
  bool ppp = false;  // Instruction TLB only (PutPartial capability).
  bool pal = false;
  bool paa = false;
  bool eff = false;
  bool c = false;
  bool fragmented_superpage = false;
};

struct SmallTlbSfence {
  bool valid = false;
  bool rs1 = false;
  bool rs2 = false;
  std::uint64_t address = 0;
};

struct SmallTlbRefill {
  bool valid = false;
  std::uint8_t level = 0;
  bool homogeneous = true;
  SmallTlbEntryData data{};
};

struct SmallTlbCycleInputs {
  bool reset = false;

  bool request_valid = false;
  std::uint64_t virtual_address = 0;
  bool vm_enabled = false;
  bool passthrough = false;
  bool kill = false;
  std::uint8_t privilege = 3;

  // Rocket's optional special entry is used when PMP granularity is smaller
  // than a page.  Unlike ordinary entries, its physical execute permission
  // is rechecked from the current PMA/PMP result on every lookup (and from
  // the refill PPN on a refill cycle), rather than read from the entry data.
  bool dynamic_execute_permission = false;

  bool ptw_request_ready = false;
  SmallTlbRefill refill{};
  SmallTlbSfence sfence{};
};

struct SmallTlbCycleOutputs {
  bool request_ready = true;
  // BOOM's NBDTLB keeps req.ready asserted while a miss walk is in flight,
  // but exposes the state-machine availability separately as miss_rdy.
  // Rocket's blocking ITLB has the same value on both signals.
  bool miss_ready = true;
  bool hit = false;
  bool multiple_hits = false;
  bool special_hit = false;
  bool bad_virtual_address = false;
  bool miss = false;
  std::uint32_t ppn = 0;
  std::uint32_t physical_address = 0;
  SmallTlbEntryData data{};

  bool ptw_request_valid = false;
  bool ptw_request_payload_valid = false;
  std::uint32_t ptw_request_vpn = 0;
};

// Dynamic physical permissions selected by NBDTLB's PMA/PMP checker.  Normal
// homogeneous TLB entries retain these bits from refill time; the physical
// bypass arm and the non-homogeneous special entry consume this live view.
struct SmallTlbPhysicalAccess {
  bool read = false;
  bool write = false;
  bool atomic_logical = false;
  bool atomic_arithmetic = false;
  bool effectful = false;
  bool cacheable = false;
};

struct SmallDataTlbAccessInputs {
  bool vm_enabled = false;
  std::uint64_t virtual_address = 0;
  std::uint8_t size = 0;
  std::uint8_t command = 0;
  std::uint8_t privilege = 3;
  bool status_sum = false;
  bool status_mxr = false;
  SmallTlbCycleOutputs translation{};
  SmallTlbPhysicalAccess dynamic_physical{};
};

struct SmallDataTlbAccessOutputs {
  bool pf_ld = false;
  bool pf_st = false;
  bool ae_ld = false;
  bool ae_st = false;
};

/** NBDTLB's page- and physical-permission response for one request lane.
  *
  * This is kept beside the registered TLB rather than in SystemGuider so the
  * subtle distinction is unit-testable: PTE permission failures are page
  * faults, while PMA/PMP failures are access exceptions.  A PTW-reported
  * access exception suppresses the page fault, matching tlb.scala's
  * `r_array | ptw_ae_array` equations. */
inline SmallDataTlbAccessOutputs small_data_tlb_access(
    const SmallDataTlbAccessInputs& input) {
  const auto is_amo_logical = [](std::uint8_t command) {
    return command == 4 || (command >= 9 && command <= 11);
  };
  const auto is_amo_arithmetic = [](std::uint8_t command) {
    return command == 8 || (command >= 12 && command <= 15);
  };
  const bool amo_logical = is_amo_logical(input.command);
  const bool amo_arithmetic = is_amo_arithmetic(input.command);
  const bool amo = amo_logical || amo_arithmetic;
  const bool command_read = input.command == 0 || input.command == 6 ||
                            input.command == 7 || amo;
  const bool command_write = input.command == 1 || input.command == 17 ||
                             input.command == 7 || amo;
  // SmallBoom has D-cache flush support, so M_FLUSH_ALL also checks write
  // permission even though it is not itself classified as a write.
  const bool command_write_permission =
      command_write || input.command == 5;
  const bool command_lrsc = input.command == 6 || input.command == 7;

  SmallDataTlbAccessOutputs result;
  const auto& translation = input.translation;
  if (input.vm_enabled && translation.bad_virtual_address) {
    result.pf_ld = command_read;
    result.pf_st = command_write_permission;
    return result;
  }

  // With VM enabled, an actual TLB entry must select the permission arrays.
  // A miss/refill cycle has no selected hit and therefore reports only miss,
  // not a speculative permission exception.  The physical bypass arm is the
  // selected hit when VM is disabled.
  const bool selected =
      !input.vm_enabled ||
      (translation.hit && !translation.multiple_hits);
  if (!selected) return result;

  const SmallTlbEntryData& entry = translation.data;
  const bool entry_access_exception =
      input.vm_enabled && entry.ae;
  if (input.vm_enabled) {
    const bool supervisor = (input.privilege & 1u) != 0;
    const bool privilege_rw_ok = supervisor
                                     ? (!entry.u || input.status_sum)
                                     : entry.u;
    const bool readable =
        privilege_rw_ok && (entry.sr || (input.status_mxr && entry.sx));
    const bool writable = privilege_rw_ok && entry.sw;
    result.pf_ld = command_read && !entry_access_exception && !readable;
    result.pf_st = command_write_permission && !entry_access_exception &&
                   !writable;
  }

  SmallTlbPhysicalAccess physical = input.dynamic_physical;
  if (input.vm_enabled && !translation.special_hit) {
    physical.read = entry.pr;
    physical.write = entry.pw;
    physical.atomic_logical = entry.pal;
    physical.atomic_arithmetic = entry.paa;
    physical.effectful = entry.eff;
    physical.cacheable = entry.c;
  }
  // ptw_ae_array masks the physical R/W permission arrays.
  physical.read &= !entry_access_exception;
  physical.write &= !entry_access_exception;

  const std::uint64_t bytes = UINT64_C(1) << (input.size & 3u);
  const bool misaligned =
      (input.virtual_address & (bytes - UINT64_C(1))) != 0;
  const bool common_access_exception =
      (misaligned && physical.effectful) ||
      (command_lrsc && !physical.cacheable);
  result.ae_ld = command_read &&
                 (common_access_exception || !physical.read);
  result.ae_st =
      (command_write_permission &&
       (common_access_exception || !physical.write)) ||
      (amo_logical &&
       !(physical.atomic_logical || physical.cacheable)) ||
      (amo_arithmetic &&
       !(physical.atomic_arithmetic || physical.cacheable));
  return result;
}

enum class SmallTlbState : std::uint8_t {
  Ready = 0,
  Request = 1,
  Wait = 2,
  WaitInvalidate = 3,
};

struct SmallTlbEntry {
  std::uint8_t level = 0;
  std::uint32_t tag = 0;
  std::array<SmallTlbEntryData, 4> data{};
  std::array<bool, 4> valid{};

  bool any_valid(std::size_t sectors) const {
    for (std::size_t i = 0; i < sectors; ++i)
      if (valid[i]) return true;
    return false;
  }
};

template <std::size_t SectoredEntries, bool Instruction>
class SmallTlb {
 public:
  static_assert(SectoredEntries == 2 || SectoredEntries == 4 ||
                    SectoredEntries == 8,
                "sectored-entry wrap masks with SectoredEntries - 1");

  static constexpr std::size_t kSectoredEntries = SectoredEntries;
  static constexpr std::size_t kSectors = 4;
  static constexpr std::size_t kSuperpageEntries = 4;
  static constexpr std::uint32_t kVpnMask = (UINT32_C(1) << 27) - 1;
  static constexpr std::uint32_t kPpnMask = (UINT32_C(1) << 20) - 1;

  SmallTlbCycleOutputs outputs(const SmallTlbCycleInputs& input) const {
    SmallTlbCycleOutputs result;
    result.miss_ready = state_ == SmallTlbState::Ready;
    result.request_ready = Instruction ? result.miss_ready : true;
    result.ptw_request_valid = state_ == SmallTlbState::Request;
    result.ptw_request_payload_valid = result.ptw_request_valid && !input.kill;
    result.ptw_request_vpn = r_refill_tag_;

    const bool vm = input.vm_enabled && !input.passthrough;
    const std::uint32_t vpn = address_vpn(input.virtual_address);
    if (!vm) {
      result.hit = true;  // The physical bypass arm of Rocket's hits vector.
      result.ppn = vpn & kPpnMask;
      result.physical_address =
          static_cast<std::uint32_t>(input.virtual_address);
      result.miss = input.refill.valid;
      return result;
    }

    const HitSet hits = find_hits(vpn);
    result.bad_virtual_address = bad_virtual_address(input.virtual_address);
    result.multiple_hits = hits.count > 1;
    result.hit = hits.count != 0;
    result.special_hit = hits.first_special;
    if (hits.count != 0) {
      const SmallTlbEntry& entry = hits.first_special ? special_entry_
          : hits.first_superpage ? superpage_entries_[hits.first_index]
                                : sectored_entries_[hits.first_index];
      const std::size_t sector = hits.first_sectors == 1 ? 0 : vpn & 3u;
      result.data = entry.data[sector];
      result.ppn = entry_ppn(entry, result.data, vpn,
                             hits.first_superpage,
                             hits.first_superpage_only);
    }
    result.physical_address = static_cast<std::uint32_t>(
        (static_cast<std::uint64_t>(result.ppn) << 12) |
        (input.virtual_address & UINT64_C(0xfff)));
    result.miss = input.refill.valid ||
                  (!result.bad_virtual_address && !result.hit) ||
                  result.multiple_hits;
    return result;
  }

  void step(const SmallTlbCycleInputs& input) {
    const SmallTlbState old_state = state_;
    const bool vm = input.vm_enabled && !input.passthrough;
    const bool idle_can_invalidate = boom_model::kArchitecturalModel && multiple_entries_possible();
    if constexpr (boom_model::kArchitecturalModel) {
      // No translation, walk transition, refill or fence can observe an
      // idle lookup. In particular, a physical request does not touch PLRU.
      if (old_state == SmallTlbState::Ready &&
          (!input.request_valid || !vm) && !input.refill.valid &&
          !input.sfence.valid && !input.reset && !idle_can_invalidate) return;
    }
    const std::uint32_t vpn = address_vpn(input.virtual_address);
    const HitSet hits = boom_model::kInternalSignalContract ||
                                (input.request_valid && vm) || idle_can_invalidate
                            ? find_hits(vpn) : HitSet{};
    const bool multiple_hits = hits.count > 1;
    const bool tlb_miss = vm && !bad_virtual_address(input.virtual_address) &&
                          !hits.count;
    const bool request_fire =
        input.request_valid && old_state == SmallTlbState::Ready;

    // Replacement state is updated by a real VM lookup, independently of
    // whether the requested sector itself is valid.
    if (input.request_valid && vm) {
      const std::size_t sector_hit = first_sector_group_hit(vpn);
      if (sector_hit != SectoredEntries)
        sectored_plru_ = plru_next(sectored_plru_, sector_hit,
                                   SectoredEntries);
      const std::size_t super_hit = first_superpage_hit(vpn);
      if (super_hit != kSuperpageEntries)
        superpage_plru_ = plru_next(superpage_plru_, super_hit,
                                    kSuperpageEntries);
    }

    // PTW response writes use the replacement decision captured at miss
    // time.  invalidate_refill is evaluated from the old state, exactly like
    // the RTL wire in TLB.scala/tlb.scala.
    if (input.refill.valid) {
      const bool invalidate_refill =
          old_state == SmallTlbState::Request ||
          old_state == SmallTlbState::WaitInvalidate || input.sfence.valid;
      insert_refill(input.refill, invalidate_refill);
    }

    SmallTlbState next_state = old_state;
    if (request_fire && tlb_miss) {
      next_state = SmallTlbState::Request;
      r_refill_tag_ = vpn;
      r_superpage_repl_addr_ = static_cast<std::uint8_t>(
          replacement_entry(superpage_entries_,
                            plru_replace(superpage_plru_,
                                         kSuperpageEntries),
                            1));
      r_sectored_repl_addr_ = static_cast<std::uint8_t>(
          replacement_entry(sectored_entries_,
                            plru_replace(sectored_plru_, SectoredEntries),
                            kSectors));
      r_sectored_hit_addr_ =
          static_cast<std::uint8_t>(sector_hit_encoding(vpn));
      r_sectored_hit_ = first_sector_group_hit(vpn) != SectoredEntries;
    }

    // Later whens in the Chisel source have priority over earlier ones.
    if (old_state == SmallTlbState::Request) {
      if (input.sfence.valid) next_state = SmallTlbState::Ready;
      if (input.ptw_request_ready)
        next_state = input.sfence.valid ? SmallTlbState::WaitInvalidate
                                        : SmallTlbState::Wait;
      if (input.kill) next_state = SmallTlbState::Ready;
    }
    if (old_state == SmallTlbState::Wait && input.sfence.valid)
      next_state = SmallTlbState::WaitInvalidate;
    if (input.refill.valid) next_state = SmallTlbState::Ready;

    if (input.sfence.valid) invalidate_sfence(input.sfence);
    if (multiple_hits || input.reset) invalidate_all();

    // Only state and replacement-policy registers have explicit reset.
    // Entry payload/tag and r_* registers retain their old bits while all
    // valid bits are synchronously cleared.
    if (input.reset) {
      state_ = SmallTlbState::Ready;
      sectored_plru_ = 0;
      superpage_plru_ = 0;
    } else {
      state_ = next_state;
    }
  }

  SmallTlbState state() const { return state_; }
  const std::uint32_t& refill_tag() const { return r_refill_tag_; }
  const std::uint8_t& superpage_replacement_address() const {
    return r_superpage_repl_addr_;
  }
  const std::uint8_t& sectored_replacement_address() const {
    return r_sectored_repl_addr_;
  }
  const std::uint8_t& sectored_hit_address() const {
    return r_sectored_hit_addr_;
  }
  const bool& sectored_hit() const { return r_sectored_hit_; }

  const SmallTlbEntry& sectored_entry(std::size_t index) const {
    return sectored_entries_[index];
  }
  const SmallTlbEntry& superpage_entry(std::size_t index) const {
    return superpage_entries_[index];
  }
  const SmallTlbEntry& special_entry() const { return special_entry_; }
  /** Bumped by every entry write (refill, sfence, flush). */
  std::uint64_t entries_epoch() const { return entries_epoch_; }

  static std::uint64_t pack_entry_data(const SmallTlbEntryData& data) {
    std::uint64_t result = data.ppn & kPpnMask;
    result = (result << 1) | static_cast<std::uint64_t>(data.u);
    result = (result << 1) | static_cast<std::uint64_t>(data.g);
    result = (result << 1) | static_cast<std::uint64_t>(data.ae);
    result = (result << 1) | static_cast<std::uint64_t>(data.sw);
    result = (result << 1) | static_cast<std::uint64_t>(data.sx);
    result = (result << 1) | static_cast<std::uint64_t>(data.sr);
    result = (result << 1) | static_cast<std::uint64_t>(data.pw);
    result = (result << 1) | static_cast<std::uint64_t>(data.px);
    result = (result << 1) | static_cast<std::uint64_t>(data.pr);
    if constexpr (Instruction)
      result = (result << 1) | static_cast<std::uint64_t>(data.ppp);
    result = (result << 1) | static_cast<std::uint64_t>(data.pal);
    result = (result << 1) | static_cast<std::uint64_t>(data.paa);
    result = (result << 1) | static_cast<std::uint64_t>(data.eff);
    result = (result << 1) | static_cast<std::uint64_t>(data.c);
    result =
        (result << 1) | static_cast<std::uint64_t>(data.fragmented_superpage);
    return result;
  }

 private:
  struct HitSet {
    unsigned count = 0;
    // Indices keep a copied TLB's memo attached to its own entries.
    std::uint8_t first_index = 0;
    std::uint8_t first_sectors = 0;
    bool first_superpage = false;
    bool first_superpage_only = false;
    bool first_special = false;
    std::uint8_t sector_group = SectoredEntries;
    std::uint8_t sector_encoding = 0;
    std::uint8_t superpage_index = kSuperpageEntries;
  };

  bool multiple_entries_possible() const {
    if (population_epoch_ == entries_epoch_) return multiple_entries_;
    unsigned population = 0;
    for (const auto& entry : sectored_entries_) population += entry.any_valid(kSectors);
    for (const auto& entry : superpage_entries_) population += entry.valid[0];
    population += special_entry_.valid[0];
    population_epoch_ = entries_epoch_;
    multiple_entries_ = population > 1;
    return multiple_entries_;
  }

  static std::uint32_t address_vpn(std::uint64_t address) {
    return static_cast<std::uint32_t>((address >> 12) & kVpnMask);
  }

  static bool bad_virtual_address(std::uint64_t address) {
    // SmallBoom exposes Sv39's one extended sign bit to the TLB.  The valid
    // encodings therefore have vaddr[39] == vaddr[38].
    return ((address >> 39) & 1u) != ((address >> 38) & 1u);
  }

  static bool sector_tag_match(const SmallTlbEntry& entry,
                               std::uint32_t vpn) {
    return ((entry.tag ^ vpn) >> 2) == 0;
  }

  static bool superpage_hit(const SmallTlbEntry& entry, std::uint32_t vpn,
                            bool superpage_only) {
    if (!entry.valid[0]) return false;
    const unsigned shift = entry.level == 0 ? 18u
        : (entry.level == 1 || superpage_only) ? 9u : 0u;
    return (((entry.tag ^ vpn) & kVpnMask) >> shift) == 0;
  }

  static std::uint32_t entry_ppn(const SmallTlbEntry& entry,
                                 const SmallTlbEntryData& data,
                                 std::uint32_t vpn, bool superpage,
                                 bool superpage_only) {
    if (!superpage) return data.ppn & kPpnMask;
    std::uint32_t ppn = data.ppn & kPpnMask;
    if (entry.level < 1)
      ppn = (ppn & ~UINT32_C(0x3fe00)) | (vpn & UINT32_C(0x3fe00));
    if (entry.level < 2 || superpage_only)
      ppn = (ppn & ~UINT32_C(0x001ff)) | (vpn & UINT32_C(0x001ff));
    return ppn & kPpnMask;
  }

  /** The hit set is a pure function of the entries and the VPN; the same
    * VPN is looked up several times per cycle (outputs() by more than one
    * caller, then step()), so the last result is kept until an entry is
    * written (entries_epoch_) or the VPN changes. */
  const HitSet& find_hits(std::uint32_t vpn) const {
    if (hits_memo_valid_ && hits_memo_vpn_ == vpn &&
        hits_memo_epoch_ == entries_epoch_)
      return hits_memo_;
    hits_memo_ = find_hits_uncached(vpn);
    hits_memo_vpn_ = vpn;
    hits_memo_epoch_ = entries_epoch_;
    hits_memo_valid_ = true;
    return hits_memo_;
  }
  HitSet find_hits_uncached(std::uint32_t vpn) const {
    HitSet result;
    const auto add = [&](std::size_t index, std::size_t sectors,
                         bool superpage, bool superpage_only,
                         bool special, bool hit) {
      if (!hit) return;
      ++result.count;
      if (result.count != 1) return;
      result.first_index = static_cast<std::uint8_t>(index);
      result.first_sectors = static_cast<std::uint8_t>(sectors);
      result.first_superpage = superpage;
      result.first_superpage_only = superpage_only;
      result.first_special = special;
    };
    for (std::size_t index = 0; index < SectoredEntries; ++index) {
      const SmallTlbEntry& entry = sectored_entries_[index];
      const std::size_t sector = vpn & 3u;
      const bool group = sector_tag_match(entry, vpn);
      if (group && entry.any_valid(kSectors)) {
        if (result.sector_group == SectoredEntries)
          result.sector_group = static_cast<std::uint8_t>(index);
        result.sector_encoding |= static_cast<std::uint8_t>(index);
      }
      add(index, kSectors, false, false, false, entry.valid[sector] && group);
    }
    for (std::size_t index = 0; index < kSuperpageEntries; ++index) {
      const bool hit = superpage_hit(superpage_entries_[index], vpn, true);
      if (hit && result.superpage_index == kSuperpageEntries)
        result.superpage_index = static_cast<std::uint8_t>(index);
      add(index, 1, true, true, false, hit);
    }
    add(0, 1, true, false, true,
        superpage_hit(special_entry_, vpn, false));
    return result;
  }

  std::size_t first_sector_group_hit(std::uint32_t vpn) const {
    return find_hits(vpn).sector_group;
  }

  std::size_t sector_hit_encoding(std::uint32_t vpn) const {
    return find_hits(vpn).sector_encoding;
  }

  std::size_t first_superpage_hit(std::uint32_t vpn) const {
    return find_hits(vpn).superpage_index;
  }

  template <std::size_t N>
  static std::size_t replacement_entry(
      const std::array<SmallTlbEntry, N>& entries, std::uint8_t alternative,
      std::size_t sectors) {
    for (std::size_t i = 0; i < N; ++i)
      if (!entries[i].any_valid(sectors)) return i;
    return alternative & (N - 1);
  }

  static std::uint8_t plru_replace(std::uint8_t state, std::size_t ways) {
    if (ways == 2) return state & 1u;
    const std::size_t half = ways / 2;
    const unsigned root_bit = static_cast<unsigned>(ways - 2);
    const bool high_half = ((state >> root_bit) & 1u) != 0;
    const std::uint8_t low_mask = static_cast<std::uint8_t>((1u << (half - 1)) - 1u);
    const std::uint8_t subtree = high_half
                                     ? static_cast<std::uint8_t>(
                                           (state >> (half - 1)) & low_mask)
                                     : static_cast<std::uint8_t>(state & low_mask);
    return static_cast<std::uint8_t>(
        (high_half ? half : 0) + plru_replace(subtree, half));
  }

  static std::uint8_t plru_next(std::uint8_t state, std::size_t touched,
                                std::size_t ways) {
    if (ways == 2) return static_cast<std::uint8_t>((touched & 1u) == 0);
    const std::size_t half = ways / 2;
    const unsigned root_bit = static_cast<unsigned>(ways - 2);
    const std::uint8_t subtree_mask =
        static_cast<std::uint8_t>((1u << (half - 1)) - 1u);
    std::uint8_t low = state & subtree_mask;
    std::uint8_t high = static_cast<std::uint8_t>(
        (state >> (half - 1)) & subtree_mask);
    const bool touched_high = touched >= half;
    if (touched_high)
      high = plru_next(high, touched - half, half);
    else
      low = plru_next(low, touched, half);
    const std::uint8_t root = touched_high ? 0u : 1u;
    return static_cast<std::uint8_t>(
        (root << root_bit) | (high << (half - 1)) | low);
  }

  static void insert(SmallTlbEntry& entry, std::size_t sectors,
                     bool superpage_only, std::uint32_t tag,
                     std::uint8_t level, const SmallTlbEntryData& data) {
    entry.tag = tag & kVpnMask;
    entry.level = static_cast<std::uint8_t>(
        level & (superpage_only ? 1u : 3u));
    const std::size_t sector = sectors == 1 ? 0 : tag & 3u;
    entry.valid[sector] = true;
    entry.data[sector] = data;
  }

  void insert_refill(const SmallTlbRefill& refill, bool invalidate_refill) {
    ++entries_epoch_;
    SmallTlbEntry* destination = nullptr;
    std::size_t sectors = 1;
    bool superpage_only = false;
    if (!refill.homogeneous) {
      destination = &special_entry_;
    } else if (refill.level < 2) {
      destination = &superpage_entries_[r_superpage_repl_addr_ & 3u];
      superpage_only = true;
    } else {
      const std::size_t address = r_sectored_hit_
                                      ? r_sectored_hit_addr_
                                      : r_sectored_repl_addr_;
      destination = &sectored_entries_[address & (SectoredEntries - 1)];
      sectors = kSectors;
      if (!r_sectored_hit_) destination->valid.fill(false);
    }
    insert(*destination, sectors, superpage_only, r_refill_tag_, refill.level,
           refill.data);
    if (invalidate_refill) destination->valid.fill(false);
  }

  static void invalidate_vpn(SmallTlbEntry& entry, std::size_t sectors,
                             bool superpage, bool superpage_only,
                             std::uint32_t vpn) {
    if (superpage) {
      if (superpage_hit(entry, vpn, superpage_only)) entry.valid.fill(false);
      return;
    }
    if (sector_tag_match(entry, vpn)) entry.valid[vpn & 3u] = false;
    if (((entry.tag ^ vpn) >> 18) == 0) {
      for (std::size_t i = 0; i < sectors; ++i)
        if (entry.data[i].fragmented_superpage) entry.valid[i] = false;
    }
  }

  static void invalidate_non_global(SmallTlbEntry& entry,
                                    std::size_t sectors) {
    for (std::size_t i = 0; i < sectors; ++i)
      if (!entry.data[i].g) entry.valid[i] = false;
  }

  void invalidate_sfence(const SmallTlbSfence& sfence) {
    ++entries_epoch_;
    const std::uint32_t vpn = address_vpn(sfence.address);
    if (sfence.rs1) {
      for (SmallTlbEntry& entry : sectored_entries_)
        invalidate_vpn(entry, kSectors, false, false, vpn);
      for (SmallTlbEntry& entry : superpage_entries_)
        invalidate_vpn(entry, 1, true, true, vpn);
      invalidate_vpn(special_entry_, 1, true, false, vpn);
    } else if (sfence.rs2) {
      for (SmallTlbEntry& entry : sectored_entries_)
        invalidate_non_global(entry, kSectors);
      for (SmallTlbEntry& entry : superpage_entries_)
        invalidate_non_global(entry, 1);
      invalidate_non_global(special_entry_, 1);
    } else {
      invalidate_all();
    }
  }

  void invalidate_all() {
    ++entries_epoch_;
    for (SmallTlbEntry& entry : sectored_entries_) entry.valid.fill(false);
    for (SmallTlbEntry& entry : superpage_entries_) entry.valid.fill(false);
    special_entry_.valid.fill(false);
  }

  SmallTlbState state_ = SmallTlbState::Ready;
  std::uint32_t r_refill_tag_ = 0;
  std::uint8_t r_superpage_repl_addr_ = 0;
  std::uint8_t r_sectored_repl_addr_ = 0;
  std::uint8_t r_sectored_hit_addr_ = 0;
  bool r_sectored_hit_ = false;

  std::array<SmallTlbEntry, SectoredEntries> sectored_entries_{};
  std::array<SmallTlbEntry, kSuperpageEntries> superpage_entries_{};
  SmallTlbEntry special_entry_{};
  // find_hits memo (see find_hits): bumped by every entry write above.
  std::uint64_t entries_epoch_ = 1;
  mutable std::uint64_t population_epoch_ = 0;
  mutable bool multiple_entries_ = false;
  mutable HitSet hits_memo_{};
  mutable std::uint32_t hits_memo_vpn_ = 0;
  mutable std::uint64_t hits_memo_epoch_ = 0;
  mutable bool hits_memo_valid_ = false;
  std::uint8_t sectored_plru_ = 0;
  std::uint8_t superpage_plru_ = 0;
};

using SmallInstructionTlb = SmallTlb<8, true>;
using SmallDataTlb = SmallTlb<boomcfg::DTLB_SECTORS, false>;

}  // namespace chisa::boom_system::components
