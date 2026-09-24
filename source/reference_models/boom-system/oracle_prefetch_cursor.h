#pragma once
// Write-ahead prefetch of the next oracle window position (SYSMODEL_IMAGE_PREFETCH=1).
//
// The writer's image copy lands on ring-slot lines that this core does not
// own (the slot was last written a few windows ago and read by the decoder
// core since), so the copy pays one ownership transfer per line.  After a
// copy the writer parks the next position's destination here, and the
// bindings' sampling placements, which run at several points inside the
// model step, prefetch a slice each with write intent.  Issued in slices
// because a core tracks only a few dozen outstanding misses: a single burst
// of 227 prefetches is mostly dropped.
#include <cstddef>

namespace chisa::boom_system {

struct OraclePrefetchCursor {
  const char* next = nullptr;
  std::size_t remaining = 0;
  static constexpr std::size_t kSliceLines = 48;
  void drain_slice() {
    std::size_t lines = kSliceLines;
    while (remaining != 0 && lines-- != 0) {
      __builtin_prefetch(next, 1, 3);
      next += 64;
      remaining = remaining > 64 ? remaining - 64 : 0;
    }
  }
};
inline thread_local OraclePrefetchCursor g_oracle_prefetch_cursor;

}  // namespace chisa::boom_system
