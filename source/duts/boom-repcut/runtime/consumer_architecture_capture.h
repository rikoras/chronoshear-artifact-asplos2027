#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>
#include "consumer_architecture_fields.h"
#include "boom_config.h"

namespace chisa::boom_repcut::consumer_arch {
#if defined(CHISA_WIDE_MODEL)
inline constexpr unsigned kCommitWidth = boomcfg::CORE_WIDTH, kRetirementFields = 11;
inline constexpr unsigned kIntegerRegisters = boomcfg::NUM_PREGS, kFloatingRegisters = boomcfg::NUM_FPREGS;
inline constexpr unsigned kIntegerWritePorts = boomcfg::IRF_WRITE_PORTS, kFloatingWritePorts = 2;
inline constexpr unsigned kRobRows = boomcfg::NUM_ROB_ROWS, kFtqEntries = boomcfg::NUM_FTQ;
inline constexpr unsigned kStoreEntries = boomcfg::NUM_STQ;
#ifndef CHISA_CONSUMER_ARCHITECTURE_SCHEMA
#error "Large architecture observation requires configuration-specific generated fields"
#endif
#else
inline constexpr unsigned kCommitWidth = 1, kRetirementFields = 10;
inline constexpr unsigned kIntegerRegisters = 52, kFloatingRegisters = 48;
inline constexpr unsigned kIntegerWritePorts = 2, kFloatingWritePorts = 2;
inline constexpr unsigned kRobRows = 32, kFtqEntries = 16, kStoreEntries = 8;
#endif
#ifdef CHISA_CONSUMER_ARCHITECTURE_SCHEMA
static_assert(kCapturedCommitWidth == kCommitWidth &&
              kCapturedRetirementFields == kRetirementFields,
              "consumer architectural field configuration mismatch");
#endif
#ifdef CHISA_CONSUMER_WIDTH
static_assert(kWidth == CHISA_CONSUMER_WIDTH, "consumer architectural lane width mismatch");
#endif
struct Word { std::uint64_t lo = 0, hi = 0; };
struct Write { bool valid = false; unsigned address = 0; Word data{}; };
struct Frame {
  bool enabled = false;
  std::array<std::array<Word, kWidth>, SignalCount> signals{};
  std::array<bool, SignalCount> seen{};
  std::array<std::array<Write, kIntegerWritePorts>, kWidth> integer{};
  std::array<std::array<Write, kFloatingWritePorts>, kWidth> floating{};
  void begin_half() {
    for (auto& ports : integer) for (auto& port : ports) port.valid = false;
    for (auto& ports : floating) for (auto& port : ports) port.valid = false;
  }
  std::uint64_t get(unsigned signal, unsigned lane) const {
    if (!seen[signal]) throw std::runtime_error("consumer architectural field was never evaluated: " +
                                               std::to_string(signal));
    return signals[signal][lane].lo;
  }
};
inline Frame frame;
// Partition observations belong to an instance/window, not to the host thread:
// a cooperative worker may execute several partition tasks in succession.
inline thread_local Frame* capture_frame = nullptr;
class FrameScope {
 public:
  explicit FrameScope(Frame* current) : previous_(capture_frame) { capture_frame = current; }
  ~FrameScope() { capture_frame = previous_; }
  FrameScope(const FrameScope&) = delete;
  FrameScope& operator=(const FrameScope&) = delete;
 private:
  Frame* previous_;
};
inline Frame& active_frame() { return capture_frame ? *capture_frame : frame; }

template <int Bits>
Word word(const UInt<Bits>& value) {
  if constexpr (Bits <= 64) return {static_cast<std::uint64_t>(value.as_single_word()), 0};
  else return {value.template bits<63, 0>().as_single_word(),
               value.template bits<Bits - 1, 64>().as_single_word()};
}
template <int Bits>
Word word(const SInt<Bits>& value) { return word(value.asUInt()); }

template <class T>
void signal(unsigned id, unsigned lane, const T& value) {
  Frame& frame = active_frame();
  if (!frame.enabled) return;
  frame.signals[id][lane] = word(value);
  frame.seen[id] = true;
}
template <class T>
void signal_array(unsigned id, const T* values) {
  Frame& frame = active_frame();
  if (!frame.enabled) return;
  for (unsigned lane = 0; lane < kWidth; ++lane) frame.signals[id][lane] = word(values[lane]);
  frame.seen[id] = true;
}
template <class T>
void register_write(bool floating, unsigned port, unsigned lane, std::uint64_t address, const T& value) {
  Frame& frame = active_frame();
  if (!frame.enabled) return;
  if (lane >= kWidth || port >= (floating ? kFloatingWritePorts : kIntegerWritePorts))
    throw std::runtime_error("consumer register-file write port/lane out of range");
  if (address >= (floating ? kFloatingRegisters : kIntegerRegisters))
    throw std::runtime_error("consumer register-file write address outside selected geometry");
  auto& out = floating ? frame.floating[lane][port] : frame.integer[lane][port];
  out = Write{true, static_cast<unsigned>(address), word(value)};
}
} // namespace chisa::boom_repcut::consumer_arch

#if !defined(CHISA_DISABLE_ARCHITECTURE_CAPTURE)
#define CHISA_ARCH_SIGNAL(id, lane, value) \
  chisa::boom_repcut::consumer_arch::signal(chisa::boom_repcut::consumer_arch::id, lane, value)
#define CHISA_ARCH_ARRAY(id, values) \
  chisa::boom_repcut::consumer_arch::signal_array(chisa::boom_repcut::consumer_arch::id, values)
#define CHISA_ARCH_REGISTER_WRITE(fp, port, lane, address, value) \
  chisa::boom_repcut::consumer_arch::register_write(fp, port, lane, address, value)
#else
#define CHISA_ARCH_SIGNAL(...) ((void)0)
#define CHISA_ARCH_ARRAY(...) ((void)0)
#define CHISA_ARCH_REGISTER_WRITE(...) ((void)0)
#endif
