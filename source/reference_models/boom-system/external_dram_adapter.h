#pragma once
// Include after the qualified system_oracle_writer and before the image
// decoder.  The generated profile maps its existing record into the new
// consumer layout; only the forty DRAM accesses have a new producer source.
#include <cstdint>
#include <cstring>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "dram_access_profile.inc"
#include "protocol/axi_memory.h"

namespace chisa::boom_system {

class ExternalDramAdapter {
 public:
  ExternalDramAdapter() : offsets_(kSystemOracleModeledStreams) {
    static_assert(dram_profile::kWidth == kSystemOracleWidth,
                  "DRAM profile and model writer widths disagree");
    static_assert(dram_profile::kBaseBlockBytes == kSystemOracleBlockBytes,
                  "DRAM profile was generated from another base layout");
    static_assert(std::size(dram_profile::kBaseStreams) == kSystemOracleModeledStreams,
                  "DRAM profile changed the model's base stream set");
    std::unordered_map<std::string, const dram_profile::BaseStream*> expected;
    for (const auto& entry : dram_profile::kBaseStreams)
      if (!expected.emplace(entry.trace_key, &entry).second)
        throw std::runtime_error("duplicate base stream in DRAM profile");
    for (std::size_t lane = 0; lane < kSystemOracleModeledStreams; ++lane) {
      const auto& actual = kSystemOracleStreams[lane];
      const auto found = expected.find(actual.trace_key);
      if (found == expected.end())
        throw std::runtime_error(std::string("DRAM profile missing base stream: ") + actual.flat);
      const auto& e = *found->second;
      if (std::strcmp(actual.flat, e.flat) != 0 ||
          actual.block_offset != e.source || actual.width != e.width ||
          actual.elem_bytes != e.bytes)
        throw std::runtime_error(std::string("DRAM base layout drift: ") + actual.flat);
      offsets_[lane] = e.destination;
      expected.erase(found);
    }
    if (!expected.empty()) throw std::runtime_error("unused base stream in DRAM profile");
  }

  const std::vector<std::uint32_t>& base_offsets() const { return offsets_; }

  void inject(const protocol::AxiRamAccess* cycles, char* expanded) const {
    for (const auto& stream : dram_profile::kAccessStreams) {
      for (unsigned p = 0; p < 2 * dram_profile::kWidth; ++p) {
        const auto& access = cycles[p];
        const bool enabled = (access.write_mask & (1u << stream.bank)) != 0;
        std::uint64_t value = 0;
        switch (stream.field) {
          case dram_profile::Field::ReadData:
            value = (access.read_data >> (8 * stream.bank)) & 0xffu; break;
          case dram_profile::Field::ReadAddress:
            value = access.read_address; break;
          case dram_profile::Field::WriteEnable:
            value = enabled; break;
          case dram_profile::Field::WriteAddress:
            value = enabled ? access.write_address : 0; break;
          case dram_profile::Field::WriteData:
            value = enabled ? ((access.write_data >> (8 * stream.bank)) & 0xffu) : 0; break;
        }
        const unsigned element = p < dram_profile::kWidth
            ? p : 3 * dram_profile::kWidth - 1 - p;
        std::memcpy(expanded + stream.offset + element * stream.bytes,
                    &value, stream.bytes);
      }
    }
  }

 private:
  std::vector<std::uint32_t> offsets_;
};

}  // namespace chisa::boom_system
