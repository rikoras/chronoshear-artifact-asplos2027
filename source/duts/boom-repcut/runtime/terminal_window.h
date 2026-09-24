#pragma once
#include <atomic>
#include <cstdint>

namespace chisa::boom_repcut {
// A source window must publish its known output boundary before the window
// itself becomes visible. RTL still checks that boundary; this only prevents
// faster owners from evaluating an extra window while the checker is behind.
inline void note_terminal_window(std::atomic<std::uint64_t>& terminal,
                                 std::uint64_t window) {
  auto before=terminal.load(std::memory_order_relaxed);
  while(window<before && !terminal.compare_exchange_weak(before,window,
      std::memory_order_release,std::memory_order_relaxed)) {}
}
}  // namespace chisa::boom_repcut
