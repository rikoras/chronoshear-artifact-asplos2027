#pragma once
// Qualification-only observation storage. Model and RTL values stay separate;
// each frame contains captures made by a particular RTL partition instance.
#include "consumer_architecture_capture.h"
#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace chisa::boom_repcut {

struct PartitionArchitectureOwners {
  unsigned partitions = 0;
  std::array<unsigned, consumer_arch::SignalCount> signals{};
  std::array<unsigned, consumer_arch::kIntegerWritePorts> integer{};
  std::array<unsigned, consumer_arch::kFloatingWritePorts> floating{};
};

template <unsigned RingSize>
class PartitionArchitectureFrames {
 public:
  using Frame = consumer_arch::Frame;
  explicit PartitionArchitectureFrames(const PartitionArchitectureOwners& owners)
      : owners_(owners), active_(owners.partitions), windows_(owners.partitions) {
    if (!owners_.partitions) throw std::invalid_argument("no architecture partition owners");
    for (unsigned owner : owners_.signals) check_owner(owner);
    for (unsigned owner : owners_.integer) check_owner(owner);
    for (unsigned owner : owners_.floating) check_owner(owner);
    for (auto& frame : active_) frame.enabled = true;
  }
  Frame& begin_half(unsigned partition) {
    check_owner(partition);
    // Persistent captures (e.g. unchanged cold source arrays) retain their
    // last actual RTL value. PRF writes are events and reset each half.
    active_[partition].begin_half();
    return active_[partition];
  }
  void finish_half(unsigned partition, std::uint64_t window, unsigned half) {
    check_owner(partition);
    if (half > 1) throw std::out_of_range("architecture half");
    auto& slot = windows_[partition][window % RingSize];
    slot.frame[half] = active_[partition];
    slot.epoch[half] = window;
  }
  // Caller acquires every partition's window-complete publication first.
  // Its ring slot cannot be reused until this merged half was consumed.
  Frame merge(std::uint64_t window, unsigned half) const {
    if (half > 1) throw std::out_of_range("architecture half");
    const auto captured = [&](unsigned partition) -> const Frame& {
      const auto& slot = windows_[partition][window % RingSize];
      if (slot.epoch[half] != window)
        throw std::runtime_error("architecture frame missing or reused before merge");
      return slot.frame[half];
    };
    Frame result;
    result.enabled = true;
    for (unsigned signal = 0; signal < consumer_arch::SignalCount; ++signal) {
      const auto& source = captured(owners_.signals[signal]);
      result.signals[signal] = source.signals[signal];
      result.seen[signal] = source.seen[signal];
    }
    for (unsigned lane = 0; lane < consumer_arch::kWidth; ++lane) {
      for (unsigned port = 0; port < consumer_arch::kIntegerWritePorts; ++port)
        result.integer[lane][port] = captured(owners_.integer[port]).integer[lane][port];
      for (unsigned port = 0; port < consumer_arch::kFloatingWritePorts; ++port)
        result.floating[lane][port] = captured(owners_.floating[port]).floating[lane][port];
    }
    return result;
  }
  const Frame& captured_frame(unsigned partition, std::uint64_t window, unsigned half) const {
    check_owner(partition);
    const auto& slot = windows_[partition][window % RingSize];
    if (half > 1 || slot.epoch[half] != window)
      throw std::runtime_error("architecture probe frame epoch mismatch");
    return slot.frame[half];
  }
 private:
  void check_owner(unsigned owner) const {
    if (owner >= owners_.partitions) throw std::out_of_range("architecture partition owner");
  }
  struct Window {
    std::array<Frame, 2> frame{};
    std::array<std::uint64_t, 2> epoch{{UINT64_MAX, UINT64_MAX}};
  };
  PartitionArchitectureOwners owners_;
  std::vector<Frame> active_;
  std::vector<std::array<Window, RingSize>> windows_;
};

} // namespace chisa::boom_repcut
