// Software interval checks for eight PMP entries, 32-bit physical addresses
// and four-byte minimum granularity. No circuit match equations are used.
#pragma once
#include <cstdint>

namespace chisa::rocket_model {

struct PmpEntry {
  uint32_t addr;  // 30 bits (paddrBits - lgAlign)
  uint32_t mask;  // 32 bits, PMP.computeMask (from the CSR file)
  bool l, r, w, x;
  uint8_t a;      // 2 bits
};

struct PmpSet {
  PmpEntry e[8];
  bool any_enabled;  // some cfg.a != 0 (fast path when false)
};

struct PmpResult { bool r, w, x; };

namespace pmp_detail {
struct Interval {
  uint64_t first = 0, end = 0;  // half-open, with a 64-bit end for 4 GiB
  bool intersects(uint64_t begin, uint64_t stop) const {
    return first < end && begin < end && first < stop;
  }
  bool contains(uint64_t begin, uint64_t stop) const {
    return first <= begin && stop <= end;
  }
};
inline Interval region(const PmpEntry& entry, uint32_t previous_address) {
  constexpr uint64_t space = UINT64_C(1) << 32;
  const uint64_t address = uint64_t(entry.addr & UINT32_C(0x3fffffff)) * 4;
  switch (entry.a) {
    case 0: return {};
    case 1: return {uint64_t(previous_address & UINT32_C(0x3fffffff)) * 4, address};
    case 2: return {address, address + 4};
    case 3: {
      // NAPOT encodes log2(bytes)-3 trailing ones in pmpaddr.
      const uint32_t first_zero = ~entry.addr & UINT32_C(0x3fffffff);
      const unsigned ones = first_zero ? unsigned(__builtin_ctz(first_zero)) : 30;
      const uint64_t size = UINT64_C(1) << (ones + 3);
      const uint64_t base = address & ~(size - 1);
      const uint64_t end = base + size;
      return {base, end < space ? end : space};
    }
    default: return {};
  }
}
}  // namespace pmp_detail

// The lowest numbered overlapping entry owns the access. Partial coverage
// denies the entire access, including when an unlocked entry permits M-mode.
inline PmpResult pmp_check(const PmpSet& set, uint32_t addr, unsigned lg_size,
                          unsigned lg_max, unsigned prv) {
  const bool machine = prv > 1;
  if (lg_size > lg_max || lg_size > 32) return {false, false, false};
  if (!set.any_enabled) return {machine, machine, machine};
  const uint64_t end = uint64_t(addr) + (UINT64_C(1) << lg_size);
  uint32_t previous = 0;
  for (const auto& entry : set.e) {
    const auto range = pmp_detail::region(entry, previous);
    previous = entry.addr;  // TOR uses its predecessor even if that entry is OFF
    if (!range.intersects(addr, end)) continue;
    if (!range.contains(addr, end)) return {false, false, false};
    if (machine && !entry.l) return {true, true, true};
    return {entry.r, entry.w, entry.x};
  }
  return {machine, machine, machine};
}

// A translation page is homogeneous only when every active PMP interval
// either covers it completely or misses it. This preserves conservative
// page-cache admission across priority and permission boundaries.
inline bool pmp_homogeneous(const PmpSet& set, uint64_t addr, unsigned level) {
  if (!set.any_enabled) return true;
  const unsigned bits = level == 0 ? 30 : level == 1 ? 21 : 12;
  const uint64_t size = UINT64_C(1) << bits;
  const uint64_t begin = addr & ~(size - 1), end = begin + size;
  uint32_t previous = 0;
  for (const auto& entry : set.e) {
    const auto range = pmp_detail::region(entry, previous);
    previous = entry.addr;
    if (range.intersects(begin, end) && !range.contains(begin, end)) return false;
  }
  return true;
}

}  // namespace chisa::rocket_model
