#pragma once
// Software traversal of a replacement tree. Its packed postorder layout is
// the observation format: lower-numbered ways occupy the low subtree.
#include <cstdint>

namespace chisa::rocket_model {
inline unsigned log2_ceil(unsigned n) { unsigned r=0; while ((1u<<r)<n) ++r; return r; }

inline uint32_t plru_next_state(uint32_t state, uint32_t touch_way, unsigned n) {
  if (n <= 1) return 0;
  state &= (UINT32_C(1) << (n-1))-1;
  unsigned offset=0;
  while (n > 1) {
    const unsigned lower=1u << (log2_ceil(n)-1);
    const bool upper=(touch_way & lower)!=0;
    const uint32_t node=UINT32_C(1) << (offset+n-2);
    if (upper) state &= ~node; else state |= node;
    touch_way &= lower-1;
    if (upper) { offset += lower-1; n -= lower; }
    else n=lower;
  }
  return state;
}

inline uint32_t plru_replace_way(uint32_t state, unsigned n) {
  unsigned way=0, offset=0;
  while (n > 1) {
    const unsigned lower=1u << (log2_ceil(n)-1);
    if ((state >> (offset+n-2)) & 1) {
      way += lower; offset += lower-1; n -= lower;
    } else n=lower;
  }
  return way;
}

// OR the indices of all selected entries. Normal callers supply a one-hot
// hit; multiple hits retain the established observation convention.
inline uint32_t oh_to_uint(uint32_t bits, unsigned width) {
  if (width < 32) bits &= (UINT32_C(1)<<width)-1;
  uint32_t result=0;
  while (bits) { result |= unsigned(__builtin_ctz(bits)); bits &= bits-1; }
  return result;
}
inline uint32_t priority_encoder(uint32_t x) { return x ? unsigned(__builtin_ctz(x)) : 0; }
}  // namespace chisa::rocket_model
