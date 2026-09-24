#pragma once

#include <cstdint>

namespace chisa::boom_system::components {

struct PmaAttributes {
  bool legal = false;
  bool cacheable = false;
};

/** Static physical-memory attributes of the locked SmallBoomConfig.
  *
  * These seven regions are the exact AddressSet comparisons elaborated into
  * `NBDTLB.legal_address_0` in the locked artifact.  Its `cacheable_0` adds
  * the condition that bit 31 equals the DRAM base's bit 31, leaving only the
  * 0x8000_0000--0x8fff_ffff manager cacheable. */
class SmallPma {
 public:
  static constexpr PmaAttributes lookup(std::uint64_t address) {
    const bool dram = contains(address, UINT64_C(0x80000000),
                               UINT64_C(0x10000000));
    const bool legal =
        contains(address, UINT64_C(0x00000000), UINT64_C(0x00001000)) ||
        contains(address, UINT64_C(0x00003000), UINT64_C(0x00001000)) ||
        contains(address, UINT64_C(0x00010000), UINT64_C(0x00010000)) ||
        contains(address, UINT64_C(0x02000000), UINT64_C(0x00010000)) ||
        contains(address, UINT64_C(0x0c000000), UINT64_C(0x04000000)) ||
        contains(address, UINT64_C(0x60000000), UINT64_C(0x20000000)) ||
        dram;
    return PmaAttributes{legal, legal && dram};
  }

 private:
  static constexpr bool contains(std::uint64_t address, std::uint64_t base,
                                 std::uint64_t size) {
    return address >= base && address - base < size;
  }
};

}  // namespace chisa::boom_system::components
