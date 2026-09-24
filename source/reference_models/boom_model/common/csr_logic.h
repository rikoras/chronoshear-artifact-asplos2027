#pragma once
#include "core_types.h"
namespace chisa::boom_model::csr_logic {
struct Context {
  GuiderCSR& state;
  std::uint64_t& retired;
  std::uint64_t& retired_register;
  std::uint64_t& flush_target;
  bool wakeup = false;
  unsigned lookahead = 0;
  bool read_override = false;
  std::uint64_t read_value = 0;
};
struct Effects {
  bool changed = false, cycle_written = false, retired_written = false;
  std::uint8_t hpm_written = 0;
};
std::uint64_t read(const GuiderCSR&, std::uint64_t retired, std::uint32_t address, unsigned lookahead = 0);
Effects execute(Context, const MicroOp&, std::uint8_t command, std::uint64_t operand);
bool trap_to_debug(const GuiderCSR&, std::uint64_t cause, std::uint32_t instruction);
std::uint64_t trap_target(const GuiderCSR&, std::uint64_t cause, std::uint32_t instruction);
std::uint64_t take_trap(GuiderCSR&, std::uint64_t pc, std::uint64_t cause, std::uint32_t instruction);
void latch_hpm_events(GuiderCSR&, const HpmEventInputs&);
void decode_legality(MicroOp&, const GuiderCSR&);
}  // namespace chisa::boom_model::csr_logic
