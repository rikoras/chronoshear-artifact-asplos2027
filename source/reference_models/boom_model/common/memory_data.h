#pragma once
#include <cstdint>

namespace chisa::boom_model {
// StoreGen replication of sub-dword store data across the 64-bit bus.
inline uint64_t storegen_replicate(uint8_t size, uint64_t d) {
  switch (size & 3) {
    case 0: d &= 0xFF; d |= d << 8; d |= d << 16; d |= d << 32; break;
    case 1: d &= 0xFFFF; d |= d << 16; d |= d << 32; break;
    case 2: d &= 0xFFFFFFFFu; d |= d << 32; break;
    default: break;
  }
  return d;
}
// LoadGen extraction of a forwarded load's data.
inline uint64_t fwd_extract(uint64_t load_addr, uint8_t load_size, bool load_signed,
                            uint8_t store_size, uint64_t store_data) {
  uint64_t d = storegen_replicate(store_size, store_data) >> ((load_addr & 7) * 8);
  const int bits = 8 << (load_size & 3);
  if (bits < 64) {
    d &= (1ULL << bits) - 1;
    if (load_signed && (d >> (bits - 1))) d |= ~((1ULL << bits) - 1);
  }
  return d;
}

}  // namespace chisa::boom_model
