#pragma once
#include <array>
#include <cstdint>

namespace chisa::boom_model {

struct RetirementEvent {
  bool valid = false;
  std::uint64_t sequence = 0, cycle = 0, pc = 0;
  // Original instruction bits (low 16 for RVC), plus the expanded decoder word.
  std::uint32_t instruction = 0, expanded_instruction = 0;
  bool is_rvc = false, debug_mode = false, writes_x = false, writes_f = false;
  std::uint8_t rd = 0, fflags = 0;
  // Integer bits or the IEEE/NaN-boxed 64-bit architectural FP readout.
  std::uint64_t value = 0;
  bool memory_write = false;  // ordinary committed store, excluding AMO/SC
  std::uint8_t memory_size = 0;
  std::uint64_t memory_address = 0, memory_value = 0;
};

struct ArchitecturalState {
  std::array<std::uint64_t, 32> x{}, f{};
  // Reset does not invent architecturally specified values for x1..31/f0..31.
  std::uint32_t x_written_mask = 1, f_written_mask = 0;
  std::uint64_t retired = 0, last_pc = 0;
};

// Separate committed storage: no map-table/PRF alias and no speculative writes.
class ArchitecturalRetirement {
 public:
  const ArchitecturalState& state() const { return state_; }
  const RetirementEvent& event() const { return event_; }
  void reset() { state_ = {}; event_ = {}; }
  void begin_cycle() { event_.valid = false; }
  void retire(RetirementEvent event) {
    event.valid = true;
    event.sequence = ++state_.retired;
    event.rd &= 31u;
    event.writes_x &= event.rd != 0;
    if (event.writes_x) {
      state_.x[event.rd] = event.value;
      state_.x_written_mask |= std::uint32_t{1} << event.rd;
    }
    if (event.writes_f) {
      state_.f[event.rd] = event.value;
      state_.f_written_mask |= std::uint32_t{1} << event.rd;
    }
    state_.last_pc = event.pc;
    event_ = event;
  }
 private:
  ArchitecturalState state_;
  RetirementEvent event_;
};
}  // namespace chisa::boom_model
