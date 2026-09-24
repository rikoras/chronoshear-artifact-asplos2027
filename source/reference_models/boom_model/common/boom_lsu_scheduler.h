#pragma once

#include <cstdint>

#include "boom_config.h"

namespace boom_lsu {

// BOOM util.scala AgePriorityEncoder over an N-entry LDQ/STQ.  The
// PriorityEncoder mux cascade falls through to the last index, so the
// all-zero (empty) value is N-1 on every configuration (7 on Small, 23 on
// Large).  Eligibility remains a separate question -- the fall-through
// value is also a perfectly valid winner.
template <int N = 8, class Mask>
inline std::uint8_t age_priority_pick(Mask mask, std::uint8_t head) {
  if (head >= N) head = 0;
  for (std::uint8_t index = head; index < N; ++index)
    if ((mask >> index) & 1u) return index;
  for (std::uint8_t index = 0; index < head; ++index)
    if ((mask >> index) & 1u) return index;
  return N - 1;
}

inline bool store_needs_order(bool valid, bool committed, bool is_fence,
                              bool dmem_ordered) {
  return valid && committed && is_fence && !dmem_ordered;
}

inline bool clear_store(bool valid, bool committed, bool is_fence,
                        bool succeeded, bool dmem_ordered) {
  return valid && committed && (is_fence ? dmem_ordered : succeeded);
}

// lsu.scala:901-904.  Retry/wakeup requests participate in the raw scheduler
// even when this cycle's branch update kills their queue entry.  The kill is
// applied only while registering the corresponding fired_* signal.
inline bool registered_fire(bool will_fire, boomcfg::br_mask_t uop_br_mask,
                            boomcfg::br_mask_t b1_mispred_mask) {
  return will_fire && (uop_br_mask & b1_mispred_mask) == 0;
}

struct Candidates {
  bool load_incoming = false;
  bool stad_incoming = false;
  bool sta_incoming = false;
  bool std_incoming = false;
  bool sfence = false;
  bool release = false;
  bool hella_incoming = false;
  bool hella_wakeup = false;
  bool load_retry = false;
  bool sta_retry = false;
  bool load_wakeup = false;
  bool store_commit = false;
};

struct Schedule {
  bool load_incoming = false;
  bool stad_incoming = false;
  bool sta_incoming = false;
  bool std_incoming = false;
  bool sfence = false;
  bool release = false;
  bool hella_incoming = false;
  bool hella_wakeup = false;
  bool load_retry = false;
  bool sta_retry = false;
  bool load_wakeup = false;
  bool store_commit = false;
};

enum Resource : unsigned {
  kTlb = 1u << 0,
  kDcache = 1u << 1,
  kLcam = 1u << 2,
  kRob = 1u << 3,
};

// lsu.scala:553-564.  Statement order is architectural priority.  Every
// granted row consumes only the resources listed beside it, so independent
// rows (for example STD + load retry) may proceed in the same cycle.
inline Schedule schedule(const Candidates& candidate) {
  Schedule result;
  unsigned available = kTlb | kDcache | kLcam | kRob;
  const auto grant = [&](bool can_fire, unsigned resources) {
    const bool fires = can_fire && (available & resources) == resources;
    if (fires) available &= ~resources;
    return fires;
  };

  result.load_incoming =
      grant(candidate.load_incoming, kTlb | kDcache | kLcam);
  result.stad_incoming =
      grant(candidate.stad_incoming, kTlb | kLcam | kRob);
  result.sta_incoming =
      grant(candidate.sta_incoming, kTlb | kLcam | kRob);
  result.std_incoming = grant(candidate.std_incoming, kRob);
  result.sfence = grant(candidate.sfence, kTlb | kRob);
  result.release = grant(candidate.release, kLcam);
  result.hella_incoming =
      grant(candidate.hella_incoming, kTlb | kDcache);
  result.hella_wakeup = grant(candidate.hella_wakeup, kDcache);
  result.load_retry =
      grant(candidate.load_retry, kTlb | kDcache | kLcam);
  result.sta_retry =
      grant(candidate.sta_retry, kTlb | kLcam | kRob);
  result.load_wakeup =
      grant(candidate.load_wakeup, kDcache | kLcam);
  result.store_commit = grant(candidate.store_commit, kDcache);
  return result;
}

}  // namespace boom_lsu
