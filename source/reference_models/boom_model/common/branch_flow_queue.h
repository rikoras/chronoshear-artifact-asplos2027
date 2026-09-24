#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
#include "boom_config.h"

namespace chisa::boom_model {
// BranchKillableQueue with flow=true. This is the functional queue itself,
// not a second mirror populated by an export pass. Entry owns a compact uop.
template<class Entry, unsigned N>
struct BranchFlowQueue {
  std::array<Entry,N> entries{};
  std::array<bool,N> valids{};
  std::uint8_t enqueue = 0, dequeue = 0;
  bool maybe_full = false;
  bool empty() const { return enqueue == dequeue && !maybe_full; }
  bool full() const { return enqueue == dequeue && maybe_full; }
  unsigned occupancy() const {
    return maybe_full && enqueue == dequeue ? N : (unsigned(enqueue)+N-dequeue)%N;
  }
  Entry front(const Entry& incoming, boomcfg::br_mask_t resolved,
              boomcfg::br_mask_t killed, bool flush) const {
    Entry result = empty() ? incoming : entries[dequeue];
    result.valid = (empty() ? incoming.valid : valids[dequeue]) &&
                   !(result.uop.br_mask & killed) && !flush;
    result.uop.br_mask &= static_cast<boomcfg::br_mask_t>(~resolved);
    return result;
  }
  void step(const Entry& incoming, bool ready, boomcfg::br_mask_t resolved,
            boomcfg::br_mask_t killed, bool flush) {
    const bool was_empty=empty();
    bool put=incoming.valid && !full();
    bool take=!was_empty && (ready || !valids[dequeue]);
    if (was_empty) { take=false; if (ready) put=false; }
    if (incoming.valid && full())
      throw std::overflow_error("BOOM branch-flow queue input overflow");
    if (resolved || killed || flush) {
      for (unsigned i=0;i<N;++i) {
        if (!valids[i]) continue;
        if ((entries[i].uop.br_mask & killed) || flush) valids[i]=false;
        entries[i].uop.br_mask &= static_cast<boomcfg::br_mask_t>(~resolved);
      }
    }
    if (put) {
      entries[enqueue]=incoming;
      entries[enqueue].uop.br_mask &= static_cast<boomcfg::br_mask_t>(~resolved);
      valids[enqueue]=true;
    }
    if (take) valids[dequeue]=false;
    if (put) enqueue=static_cast<std::uint8_t>((enqueue+1)%N);
    if (take) dequeue=static_cast<std::uint8_t>((dequeue+1)%N);
    if (put!=take) maybe_full=put;
  }
  void flush() {
    // Kill data, not the pointers: invalid entries leave through the ordinary
    // dequeue path on later edges, just as in the RTL.
    valids.fill(false);
  }
};
}  // namespace chisa::boom_model
