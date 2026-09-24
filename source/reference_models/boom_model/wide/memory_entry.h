#pragma once
#include <cstdint>
#include "../common/core_types.h"
#include "../common/lsu_uop_word.h"

namespace chisa::boom_model::wide {
struct MemoryEntry {
  using Word=LsuUopWord<boomcfg::MAX_BR_COUNT,boomcfg::index_width_for_entries(boomcfg::ROB_FLAT),
                        boomcfg::LDQ_IDX_WIDTH,boomcfg::index_width_for_entries(boomcfg::NUM_PREGS)>;
  // Same packed descriptor scheme as Small's StqWord. Address/data have
  // independent lifetimes; no second set of scalar uop fields is retained.
  std::uint64_t uop_word=0;
  bool floating=false,single=false;
  std::uint64_t address=0,data=0,virtual_address=0;
  void assign(const MicroOp& u) {
    uop_word=Word::make(u);floating=u.fp_val;single=u.fp_single;
  }
  bool clear_branches(std::uint16_t resolved) {
    const auto next=Word::set_br_mask(uop_word,static_cast<std::uint16_t>(branch()&~resolved));
    const bool moved=next!=uop_word;uop_word=next;return moved;
  }
  std::uint8_t rob() const { return Word::rob(uop_word); }
  std::uint8_t pdst() const { return Word::pdst(uop_word); }
  std::uint8_t command() const { return Word::mem_cmd(uop_word); }
  std::uint8_t size() const { return Word::mem_size(uop_word); }
  std::uint16_t branch() const { return Word::br_mask(uop_word); }
  bool signed_load() const { return Word::mem_signed(uop_word); }
  bool fence() const { return Word::is_fence(uop_word); }
  bool amo() const { return Word::is_amo(uop_word); }
  std::uint8_t load_index() const { return Word::ldq(uop_word); }
  std::uint8_t store_index() const { return Word::stq(uop_word); }
  std::uint8_t dst_rtype() const { return Word::dst_rtype(uop_word); }
};
}  // namespace chisa::boom_model::wide
