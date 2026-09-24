#pragma once
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace chisa::boom_repcut {

// One immutable source window, many independent transpose groups. The lock
// covers only setup and ticket allocation. No model task waits on this lock.
// The caller publishes the expanded window only after complete() returns true.
template<class Context> class alignas(64) ParallelDecode {
 public:
  struct Ticket {
    std::uint64_t epoch;
    std::size_t group, groups;
    Context context;
  };
  template<class Initialize>
  bool claim(std::uint64_t epoch, std::size_t groups, Initialize&& initialize, Ticket& ticket) {
    if (claim_.test_and_set(std::memory_order_acquire)) return false;
    struct Unlock { std::atomic_flag& flag; ~Unlock() { flag.clear(std::memory_order_release); } } unlock{claim_};
    if (epoch != epoch_) {
      // A poll may have sampled the old published epoch before another
      // worker completed it. Reject that stale poll without moving backwards.
      if (epoch_ != UINT64_MAX && epoch < epoch_) return false;
      if (epoch_ != UINT64_MAX && (epoch != epoch_ + 1 || completed_.load(std::memory_order_acquire) != groups_))
        throw std::logic_error("decode epoch advanced before all groups completed");
      if (!groups) throw std::logic_error("empty decode window");
      Context context{};
      initialize(context);
      context_ = context;
      groups_ = groups;
      next_ = 0;
      completed_.store(0, std::memory_order_relaxed);
      epoch_ = epoch;
    }
    if (next_ == groups_) return false;
    ticket = {epoch_, next_++, groups_, context_};
    return true;
  }
  bool complete(const Ticket& ticket) {
    // Each successful claim has exactly one completion. The acq_rel chain
    // makes all output stores visible to the last completing worker.
    const auto previous = completed_.fetch_add(1, std::memory_order_acq_rel);
    if (previous >= ticket.groups) throw std::logic_error("too many decode completions");
    return previous + 1 == ticket.groups;
  }
 private:
  alignas(64) std::atomic_flag claim_ = ATOMIC_FLAG_INIT;
  std::uint64_t epoch_ = UINT64_MAX;
  std::size_t groups_ = 0, next_ = 0;
  Context context_{};
  alignas(64) std::atomic<std::size_t> completed_{0};
};
}  // namespace chisa::boom_repcut
