#pragma once
#include <array>
#include <cstdint>
#include "../common/boom_config.h"

namespace chisa::boom_model::wide {
struct IssueMovement {
  std::array<std::uint32_t,boomcfg::CORE_WIDTH> from_distance{};
  std::uint32_t receives = 0, clears = 0;
  unsigned available = 0;
};

// issue-unit-age-ordered.scala's saturated prefix counter, maxShift=dispatchWidth.
// Source selection happens before will_be_valid gating: the greatest matching
// distance wins even when its selected source is invalid.
inline IssueMovement issue_movement(unsigned capacity, std::uint32_t pre_valid,
                                    std::uint32_t vacated, std::uint8_t dispatch) {
  const std::uint64_t slots=(UINT64_C(1)<<capacity)-1;
  constexpr unsigned width=boomcfg::CORE_WIDTH, incoming_mask=(1u<<width)-1;
  const std::uint64_t span=(UINT64_C(1)<<(capacity+width))-1;
  auto holes=((~std::uint64_t(pre_valid))&slots) | (std::uint64_t((~dispatch)&incoming_mask)<<capacity);
  std::array<std::uint64_t,width> above{};
  for (unsigned n=0;n<width && holes;++n) {
    const unsigned hole=static_cast<unsigned>(__builtin_ctzll(holes));
    holes &= holes-1;
    above[n]=span & ~((UINT64_C(1)<<(hole+1))-1);
  }
  const std::uint64_t will=(std::uint64_t(pre_valid&~vacated)&slots) |
                           (std::uint64_t(dispatch&incoming_mask)<<capacity);
  IssueMovement result;
  std::uint64_t covered=0;
  for (unsigned distance=width;distance>0;--distance) {
    const auto source=above[distance-1] & (distance==width ? span : ~above[distance]);
    const auto destination=(source>>distance)&~covered;
    covered |= destination;
    result.from_distance[distance-1]=static_cast<std::uint32_t>(destination&(will>>distance)&slots);
    result.receives |= result.from_distance[distance-1];
  }
  result.clears=static_cast<std::uint32_t>((above[0]|vacated)&~result.receives&slots);
  result.available=static_cast<unsigned>(__builtin_popcountll((~will|above[0])&~result.receives&slots));
  return result;
}
}  // namespace chisa::boom_model::wide
