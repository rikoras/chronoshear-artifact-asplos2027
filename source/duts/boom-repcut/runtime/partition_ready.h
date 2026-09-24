#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <stdexcept>

namespace chisa::boom_repcut {

// One object per ring slot. Setup occurs inside the decode claim lock after
// the slot's previous readers AND all expansion writers have retired.
// Each successful group ticket contributes exactly once to its readers.
template<unsigned Partitions> class PartitionReady {
  static_assert(Partitions>0 && Partitions<64);
  struct alignas(64) Reader {
    std::atomic<unsigned> remaining{0};
    std::atomic<std::uint64_t> epoch_end{0};
  };
  std::array<Reader,Partitions> readers_{};
 public:
  struct NoNotify { void operator()(unsigned,bool) const {} };
  void begin(std::uint64_t epoch, const std::array<unsigned,Partitions>& counts) {
    for (unsigned p=0;p<Partitions;++p) {
      if (!counts[p]) throw std::logic_error("partition has no expansion dependency");
      readers_[p].remaining.store(counts[p],std::memory_order_relaxed);
    }
    (void)epoch;
  }
  template<class Notify=NoNotify>
  void complete(std::uint64_t epoch, std::uint64_t mask, Notify notify={}) {
    if (!mask || (mask>>Partitions)) throw std::logic_error("invalid completion reader mask");
    while (mask) {
      const auto p=static_cast<unsigned>(__builtin_ctzll(mask));mask &= mask-1;
      // The RMW chain acquires every previous group store for this reader.
      // Only its last group releases that partition's complete input set.
      const auto previous=readers_[p].remaining.fetch_sub(1,std::memory_order_acq_rel);
      if (!previous) throw std::logic_error("duplicate partition completion");
      if (previous==1) {
        notify(p,false);
        readers_[p].epoch_end.store(epoch+1,std::memory_order_release);
        notify(p,true);
      }
    }
  }
  bool ready(std::uint64_t epoch, unsigned partition) const {
    return readers_[partition].epoch_end.load(std::memory_order_acquire)>epoch;
  }
};
} // namespace chisa::boom_repcut
