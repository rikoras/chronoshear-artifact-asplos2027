#pragma once

#include <fesvr/elfloader.h>
#include <fesvr/memif.h>

#include <cstddef>
#include <cstdint>
#include <unordered_map>

namespace chisa::boom_repcut {

/** CHISA-owned byte-addressed backing memory initialized from a workload ELF.
  * It is independent of SimAXIMem and can later receive writes from the
  * modeled D-cache/AXI path. */
class ElfBackingMemory final : public chunked_memif_t {
 public:
  ElfBackingMemory() = default;

  explicit ElfBackingMemory(const char* path) {
    memif_t loader(this);
    load_elf(path, &loader, &entry_);
  }

  std::uint64_t read64(std::uint64_t address) const {
    std::uint64_t result = 0;
    for (unsigned byte = 0; byte < 8; ++byte) {
      const auto found = bytes_.find(address + byte);
      if (found != bytes_.end())
        result |= static_cast<std::uint64_t>(found->second) << (byte * 8u);
    }
    return result;
  }

  void write64(std::uint64_t address, std::uint64_t data) {
    for (unsigned byte = 0; byte < 8; ++byte) {
      const std::uint8_t value =
          static_cast<std::uint8_t>(data >> (byte * 8u));
      if (value == 0)
        bytes_.erase(address + byte);
      else
        bytes_[address + byte] = value;
    }
  }

  std::uint64_t entry() const { return entry_; }

  void read_chunk(addr_t address, std::size_t length, void* destination)
      override {
    auto* output = static_cast<std::uint8_t*>(destination);
    for (std::size_t byte = 0; byte < length; ++byte) {
      const auto found = bytes_.find(address + byte);
      output[byte] = found == bytes_.end() ? 0 : found->second;
    }
  }

  void write_chunk(addr_t address, std::size_t length,
                   const void* source) override {
    const auto* input = static_cast<const std::uint8_t*>(source);
    for (std::size_t byte = 0; byte < length; ++byte) {
      if (input[byte] == 0)
        bytes_.erase(address + byte);
      else
        bytes_[address + byte] = input[byte];
    }
  }

  void clear_chunk(addr_t address, std::size_t length) override {
    for (std::size_t byte = 0; byte < length; ++byte)
      bytes_.erase(address + byte);
  }

  std::size_t chunk_align() override { return 1; }
  std::size_t chunk_max_size() override { return 1024; }

  void set_target_endianness(memif_endianness_t endianness) override {
    endianness_ = endianness;
  }
  memif_endianness_t get_target_endianness() const override {
    return endianness_;
  }

 private:
  std::unordered_map<std::uint64_t, std::uint8_t> bytes_{};
  reg_t entry_ = 0;
  memif_endianness_t endianness_ = memif_endianness_undecided;
};

}  // namespace chisa::boom_repcut
