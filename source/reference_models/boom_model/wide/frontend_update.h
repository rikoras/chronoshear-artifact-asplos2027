#pragma once
#include "../common/predictor_bank.h"
#include "../../boom-system/components/small_fetch_buffer.h"
namespace chisa::boom_model::wide {
using chisa::boom_system::components::SmallFtqBpdUpdate;
using chisa::boom_system::components::SmallFetchBundle;
// Same queue and arbitration as Small; payload moves only on enqueue.
class BpdUpdatePath {
 public:
  bool correction_deq_valid() const { return !empty(); }
  std::uint32_t enq_ptr() const { return enq_ptr_; }
  std::uint32_t deq_ptr() const { return deq_ptr_; }
  bool maybe_full() const { return maybe_full_; }
  const SmallFtqBpdUpdate& payload(std::size_t i) const { return payloads_[i]; }
  const SmallFtqBpdUpdate& deq_payload() const { return payloads_[deq_ptr_]; }
  std::uint32_t version() const { return ver_; }

  /** The arbiter output: FTQ update first, else the queued correction. */
  bool update_valid(bool ftq_valid) const { return ftq_valid || !empty(); }
  const SmallFtqBpdUpdate& update(bool ftq_valid, const SmallFtqBpdUpdate& ftq_update) const {
    return ftq_valid ? ftq_update : payloads_[deq_ptr_];
  }

  void commit(bool reset, bool f3_fire, std::uint8_t f3_btb_mispredicts, const SmallFetchBundle& f3_bundle,
              bool ftq_valid) {
    const bool enq_valid = f3_fire && (f3_btb_mispredicts & ((1u<<boomcfg::FETCH_WIDTH)-1)) != 0;
    const bool deq_ready = !ftq_valid;
    const bool enq_ready = !full();
    if (!reset && enq_valid && enq_ready) {
      SmallFtqBpdUpdate& c = payloads_[enq_ptr_];
      c = SmallFtqBpdUpdate{};
      c.btb_mispredicts = static_cast<std::uint8_t>(f3_btb_mispredicts & ((1u<<boomcfg::FETCH_WIDTH)-1));
      c.pc = f3_bundle.pc & fe::kPc40;
      c.ghist = f3_bundle.ghist;
      c.meta = f3_bundle.bpd_meta;
      for (unsigned bank=0;bank<boomcfg::NBANKS;++bank) c.meta[bank*4+3] &= 0x00ffffffu;
      ++ver_;
    }
    if (reset) { enq_ptr_ = 0; deq_ptr_ = 0; maybe_full_ = false; ++ver_; return; }
    const bool do_enq = enq_ready && enq_valid;
    const bool do_deq = deq_ready && !empty();
    if (do_enq) enq_ptr_ ^= 1u;
    if (do_deq) deq_ptr_ ^= 1u;
    if (do_enq != do_deq) maybe_full_ = do_enq;
    if (do_enq || do_deq) ++ver_;
  }

 private:
  bool empty() const { return enq_ptr_ == deq_ptr_ && !maybe_full_; }
  bool full() const { return enq_ptr_ == deq_ptr_ && maybe_full_; }
  std::uint32_t enq_ptr_ = 0, deq_ptr_ = 0;
  bool maybe_full_ = false;
  std::array<SmallFtqBpdUpdate, 2> payloads_{};
  std::uint32_t ver_ = 1;
};
}
