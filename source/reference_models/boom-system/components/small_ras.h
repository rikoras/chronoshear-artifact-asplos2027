#pragma once
// ============================================================================
// Small BOOM 32-entry return-address stack storage.
//
// The RTL has an unreset Reg(Vec) plus a one-cycle registered read and a
// same-index write bypass.  This component preserves that exact edge order.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>

namespace chisa::boom_system::components {

struct SmallRasInputs {
  std::uint8_t read_idx = 0;
  bool write_valid = false;
  std::uint8_t write_idx = 0;
  std::uint64_t write_addr = 0;
};

struct SmallRasOutputs {
  std::uint64_t read_addr = 0;
};

class SmallRas {
 public:
  static constexpr std::size_t kEntries = 32;

  SmallRasOutputs outputs() const {
    SmallRasOutputs result;
    result.read_addr =
        (bypass_reg_ ? write_addr_reg_ : read_data_reg_) & kPcMask;
    return result;
  }

  void step(const SmallRasInputs& input) {
    const std::size_t read_idx = input.read_idx & 0x1fu;
    const std::size_t write_idx = input.write_idx & 0x1fu;
    const std::uint64_t old_read_data = ras_[read_idx];

    bypass_reg_ = input.write_valid && read_idx == write_idx;
    write_addr_reg_ = input.write_addr & kPcMask;
    read_data_reg_ = old_read_data & kPcMask;
    if (input.write_valid) ras_[write_idx] = input.write_addr & kPcMask;
  }

  const std::array<std::uint64_t, kEntries>& entries() const {
    return ras_;
  }
  const bool& bypass_reg() const { return bypass_reg_; }
  const std::uint64_t& write_addr_reg() const { return write_addr_reg_; }
  const std::uint64_t& read_data_reg() const { return read_data_reg_; }

 private:
  static constexpr std::uint64_t kPcMask =
      (UINT64_C(1) << 40) - UINT64_C(1);

  std::array<std::uint64_t, kEntries> ras_{};  // unreset in RTL
  bool bypass_reg_ = false;                   // plain RegNext
  // The RTL register is unreset and latches the boot-era write wire (0x8)
  // through the reset window.
  std::uint64_t write_addr_reg_ = 0x8;          // plain RegNext
  std::uint64_t read_data_reg_ = 0;           // plain RegNext
};

}  // namespace chisa::boom_system::components
