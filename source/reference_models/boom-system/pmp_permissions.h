#pragma once
#include <array>
#include <cstdint>

namespace chisa::boom_system {

// Decode configuration once. A cached page is accepted only when no active
// PMP boundary crosses it; narrow/overlapping regions retain the ordered scan.
class PmpPermissions {
 public:
  struct Access { bool read = false, write = false, execute = false; };

  template<class Entries> void configure(const Entries& entries) {
    count_ = 0;
    for (auto& page : pages_) page.valid = false;
    std::uint64_t previous = 0;
    for (const auto& entry : entries) {
      const unsigned mode = entry.address_mode & 3u;
      const std::uint64_t top = std::uint64_t(entry.address & UINT32_C(0x3fffffff)) << 2;
      std::uint64_t lower = 0, upper = 0;
      if (mode == 1) { lower = previous; upper = top; }
      else if (mode & 2u) {
        lower = top & ~std::uint64_t(entry.mask);
        upper = lower + std::uint64_t(entry.mask) + 1;
      }
      previous = top;
      if (mode) {
        windows_[count_++] = Window{lower, upper, entry.locked,
            {entry.read, entry.write, entry.execute}};
      }
    }
  }

  Access lookup(std::uint64_t address, std::uint8_t size, std::uint8_t privilege) const {
    const std::uint64_t start = static_cast<std::uint32_t>(address);
    const std::uint64_t end = start + (UINT64_C(1) << (size > 3 ? 3 : size));
    const std::uint64_t page_start = start & ~UINT64_C(4095);
    const std::uint64_t page_end = page_start + 4096;
    auto& page = pages_[(start >> 12) & (pages_.size() - 1)];
    if (page.valid && page.start == page_start && page.privilege == privilege && end <= page_end)
      return page.access;

    const bool machine = privilege == 3;
    Access result{machine, machine, machine};
    bool selected = false, uniform_page = end <= page_end;
    for (unsigned i = 0; i < count_; ++i) {
      const auto& window = windows_[i];
      if ((window.lower > page_start && window.lower < page_end) ||
          (window.upper > page_start && window.upper < page_end)) uniform_page = false;
      if (selected || start >= window.upper || end <= window.lower) continue;
      const bool aligned = start >= window.lower && end <= window.upper;
      const bool unlocked_machine = machine && !window.locked;
      result = {aligned && (unlocked_machine || window.access.read),
                aligned && (unlocked_machine || window.access.write),
                aligned && (unlocked_machine || window.access.execute)};
      selected = true;
    }
    if (uniform_page) page = Page{page_start, privilege, true, result};
    return result;
  }

 private:
  struct Window { std::uint64_t lower = 0, upper = 0; bool locked = false; Access access{}; };
  struct Page { std::uint64_t start = 0; std::uint8_t privilege = 0; bool valid = false; Access access{}; };
  std::array<Window, 8> windows_{};
  unsigned count_ = 0;
  mutable std::array<Page, 4> pages_{};
};
}  // namespace chisa::boom_system
