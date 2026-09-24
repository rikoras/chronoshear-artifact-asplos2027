#pragma once

#include <array>
#include <cstdint>

namespace chisa::boom_system::components {

/** Executable 128-byte mask ROM at 0x10000 in the locked Small chip.
  * The larger TLROM also contains a generated device tree; instruction
  * refills only use this reset program image. */
class SmallBootRom {
 public:
  static std::uint64_t read64(std::uint32_t address) {
    if (address < kBase || address >= kBase + kWords.size() * 8u)
      return 0;
    return kWords[(address - kBase) >> 3];
  }

 private:
  static constexpr std::uint32_t kBase = UINT32_C(0x10000);
  inline static constexpr std::array<std::uint64_t, 16> kWords = {
      UINT64_C(0x0010041b7c105073), UINT64_C(0xf140257301f41413),
      UINT64_C(0x0705859300000597), UINT64_C(0x0000000000008402),
      0, 0, 0, 0,
      UINT64_C(0xf14025737c105073), UINT64_C(0x0385859300000597),
      UINT64_C(0x1050007330405073), UINT64_C(0x000000000000bff5),
      0, 0, 0, 0};
};

}  // namespace chisa::boom_system::components
