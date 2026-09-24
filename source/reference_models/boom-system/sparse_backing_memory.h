#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

namespace chisa::boom_system {

/** Sparse byte-addressed backing store shared by the handwritten hot model
  * and the exact cold AXI RAM control shell. */
class SparseBackingMemory {
 public:
  std::uint64_t read64(std::uint32_t address) const {
    const auto page = pages_.find(page_of(address));
    if (page == pages_.end()) return 0;
    return page->second[beat_of(address)];
  }
  void write64(std::uint32_t address, std::uint64_t data) {
    pages_[page_of(address)][beat_of(address)] = data;
  }
  void write64_masked(std::uint32_t address, std::uint64_t data,
                      std::uint8_t strobe) {
    std::uint64_t merged = read64(address);
    for (unsigned byte = 0; byte < 8; ++byte) {
      if ((strobe & (std::uint8_t{1} << byte)) == 0) continue;
      const std::uint64_t mask = UINT64_C(0xff) << (byte * 8);
      merged = (merged & ~mask) | (data & mask);
    }
    write64(address, merged);
  }
  std::size_t touched_pages() const { return pages_.size(); }

 private:
  static constexpr std::uint32_t kPageBytes = 4096;
  static std::uint32_t page_of(std::uint32_t address) {
    return address / kPageBytes;
  }
  static std::size_t beat_of(std::uint32_t address) {
    return (address % kPageBytes) / 8;
  }
  std::unordered_map<std::uint32_t,
                     std::array<std::uint64_t, kPageBytes / 8>>
      pages_;
};

}  // namespace chisa::boom_system
