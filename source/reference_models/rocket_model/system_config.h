#pragma once
// Standalone program/environment configuration for the native Rocket model.
// This header has no RTL implementation, oracle writer or sidecar dependency.
#include <cstdint>
#include <string>

namespace chisa::rocket_model {
inline constexpr std::uint64_t kMemoryBase = UINT64_C(0x80000000);
inline constexpr std::uint64_t kMemoryBytes = UINT64_C(0x10000000);

struct SystemConfig {
  int argc = 0;
  char** argv = nullptr;
  std::string image_path;
  std::uint64_t load_address = kMemoryBase;
  std::uint64_t tohost_address = UINT64_C(0x80001000);
  std::uint64_t fromhost_address = UINT64_C(0x80001040);
  std::uint64_t reset_cycles = 64;
  std::uint32_t reset_vector = UINT32_C(0x00010040);
  unsigned fixed_point_limit = 16;
  std::uint64_t console_wait_pc[4] = {
      UINT64_C(0x80001634), UINT64_C(0x80001636),
      UINT64_C(0x80001716), UINT64_C(0x80001718)};
  std::uint64_t exit_park_pc = UINT64_C(0x800016ae);
  std::uint64_t trap_park_pc = UINT64_C(0x800016be);
  std::uint64_t pc_trigger_stable_cycles = 8;
  bool service_htif = true;
};
} // namespace chisa::rocket_model
