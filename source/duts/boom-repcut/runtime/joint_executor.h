#pragma once
#include <atomic>
#include <cstdint>
#if defined(CHISA_MODEL_DIAGNOSTICS)
#include "../../../reference_models/boom_model/common/diagnostic_monitor.h"
#endif

namespace chisa::boom_repcut {

// Capture these by reference in the runtime closures. Reserving the whole
// line prevents diagnostic-only stack locals changing which hot flags share
// a cache line in the performance build.
template <class T> struct alignas(64) IsolatedAtomic : std::atomic<T> {
  constexpr IsolatedAtomic(T initial = {}) : std::atomic<T>(initial) {}
};
struct alignas(64) IsolatedClaim {
  std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

// A task is a bounded, nonblocking phase. Its state belongs to the task's
// fixed owner, except for explicitly synchronized shared background work.
struct TryTask {
  bool (*function)(void*) = nullptr;
  void* context = nullptr;
  bool operator()() const { return function && function(context); }
  template <class F> static TryTask bind(F& fn) {
    return {[](void* ctx) {
#if defined(CHISA_MODEL_DIAGNOSTICS)
      struct RestoreCycle {
        std::uint64_t previous=::chisa::diagnostic::cycle();
        ~RestoreCycle() { ::chisa::diagnostic::set_cycle(previous); }
      } restore;
#endif
      return (*static_cast<F*>(ctx))();
    }, &fn};
  }
};

class alignas(64) JointTaskPump {
 public:
  TryTask priority, background;
  unsigned priority_budget = 4;
  bool background_in_kernel = false;
  std::uint64_t polls = 0, priority_tasks = 0, background_tasks = 0;
  bool poll(bool allow_background = true) {
    if (!priority.function && (!allow_background || !background.function)) return false;
    // RTL callbacks and idle polling share this owner. No recursion into
    // the same task is allowed even if a callback indirectly polls again.
    if (active_) return false;
    active_ = true;
    struct Guard { bool& active; ~Guard() { active = false; } } guard{active_};
    ++polls;
    bool progress = false;
    // A memory edge has four dependent phases. Drain already-ready phases
    // together so each handoff does not have to wait for another RTL chunk.
    // The fixed budget also prevents a fast requester starving the RTL.
    for (unsigned n = 0; n < priority_budget && priority(); ++n) {
      ++priority_tasks;
      progress = true;
    }
    if (progress) return true;
    if (allow_background && background()) { ++background_tasks; return true; }
    return false;
  }
  static void kernel_poll(void* ctx, unsigned, bool, unsigned) {
    auto& pump = *static_cast<JointTaskPump*>(ctx);
    pump.poll(pump.background_in_kernel);
  }
 private:
  bool active_ = false;
};

// Older consumers remain usable for the baseline. Joint mode requires the
// emitter's actual chunk callbacks and must fail instead of silently using
// a whole half-window as one uninterruptible phase.
template <class Dut>
auto bind_joint_pump(Dut& dut, JointTaskPump& pump, int)
    -> decltype(dut.partition_task_poll = &JointTaskPump::kernel_poll, bool()) {
  dut.partition_task_poll = pump.priority.function || (pump.background_in_kernel && pump.background.function)
      ? &JointTaskPump::kernel_poll : nullptr;
  dut.partition_task_context = &pump;
  return true;
}
template <class Dut>
bool bind_joint_pump(Dut&, JointTaskPump&, long) { return false; }

}  // namespace chisa::boom_repcut
