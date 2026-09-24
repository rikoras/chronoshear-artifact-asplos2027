#pragma once
#include <atomic>
#include <cstdint>

namespace chisa::boom_system {

// A cancelled speculative record copy is not a completed main-thread
// publication. Keep those epochs distinct: window drains and DTM retries
// may cancel a copy before the main thread has sampled the next edge.
class RecordCopyGate {
 public:
  enum class State { Pending, Ready, Cancelled };
  void publish(std::uint64_t epoch) { published_.store(epoch, std::memory_order_release); }
  void cancel(std::uint64_t epoch) { cancelled_.store(epoch, std::memory_order_release); }
  std::uint64_t published() const { return published_.load(std::memory_order_acquire); }
  State state(std::uint64_t epoch) const {
    if (cancelled_.load(std::memory_order_acquire) >= epoch) return State::Cancelled;
    return published() >= epoch ? State::Ready : State::Pending;
  }
 private:
  alignas(64) std::atomic<std::uint64_t> published_{0};
  std::atomic<std::uint64_t> cancelled_{0};
};

} // namespace chisa::boom_system
