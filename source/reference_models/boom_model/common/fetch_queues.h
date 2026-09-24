#pragma once
#include <array>
#include <cstdint>
#include "../../boom-system/components/small_f3_queues.h"
#include "../../boom-system/components/small_fetch_buffer.h"

namespace chisa::boom_model::fe {
using chisa::boom_system::components::SmallFrontendResp;
using chisa::boom_system::components::SmallBpdResponse;
using chisa::boom_system::components::SmallFetchBundle;
class F3Queues {
 public:
  bool main_enq_ready(bool deq_ready) const { return !main_full_ || deq_ready; }
  bool main_deq_valid() const { return main_full_; }
  const SmallFrontendResp& main_deq() const { return main_payload_; }
  bool bpd_enq_valid() const { return main_full_ && prev_main_enq_ready_; }
  bool bpd_enq_ready(bool deq_ready) const { return !bpd_full_ || deq_ready; }
  bool bpd_deq_valid() const { return bpd_full_ || bpd_enq_valid(); }
  bool bpd_full() const { return bpd_full_; }
  const SmallBpdResponse& bpd_payload() const { return bpd_payload_; }
  const SmallFrontendResp& main_payload() const { return main_payload_; }
  bool main_full() const { return main_full_; }
  bool previous_main_enq_ready() const { return prev_main_enq_ready_; }
  std::uint32_t main_version() const { return main_ver_; }
  std::uint32_t bpd_version() const { return bpd_ver_; }

  void commit(bool reset, bool clear, bool main_enq_valid, bool main_enq_ready,
              const SmallFrontendResp& main_enq, bool bpd_enq_valid, bool bpd_enq_ready,
              bool bpd_deq_valid, const SmallBpdResponse& bpd_enq, bool deq_ready) {
    const bool main_do_enq = main_enq_valid && main_enq_ready;
    const bool main_do_deq = main_full_ && deq_ready;
    const bool bpd_do_enq = bpd_enq_valid && bpd_enq_ready;
    const bool bpd_do_deq = bpd_deq_valid && deq_ready;
    if (main_do_enq) { main_payload_ = main_enq; ++main_ver_; }
    if (main_do_enq != main_do_deq) main_full_ = main_do_enq;
    // flow queue: an empty queue with a ready consumer passes the entry
    // through without writing the ram.
    if (bpd_do_enq && !(!bpd_full_ && deq_ready)) { bpd_payload_ = bpd_enq; ++bpd_ver_; }
    if (bpd_do_enq != bpd_do_deq) bpd_full_ = bpd_do_enq;
    if (reset || clear) { main_full_ = false; bpd_full_ = false; }
    prev_main_enq_ready_ = main_enq_ready;
  }

 private:
  SmallFrontendResp main_payload_{};
  SmallBpdResponse bpd_payload_{};
  bool main_full_ = false, bpd_full_ = false, prev_main_enq_ready_ = false;
  std::uint32_t main_ver_ = 1, bpd_ver_ = 1;
};
class F4Queue {
 public:
  bool enq_ready(bool deq_ready) const { return !full_ || deq_ready; }
  bool deq_valid() const { return full_; }
  bool full() const { return full_; }
  const SmallFetchBundle& payload() const { return payload_; }
  void commit(bool reset, bool enq_valid, bool enq_ready_now, const SmallFetchBundle& enq, bool deq_ready) {
    const bool do_enq = enq_ready_now && enq_valid;
    const bool do_deq = full_ && deq_ready;
    if (do_enq) payload_ = enq;
    if (do_enq != do_deq) full_ = do_enq;
    if (reset) full_ = false;
  }

 private:
  SmallFetchBundle payload_{};
  bool full_ = false;
};
class Ras {
 public:
  std::uint64_t read_addr() const { return (bypass_reg_ ? write_addr_reg_ : read_data_reg_) & ((UINT64_C(1)<<40)-1); }
  void step(std::uint8_t read_idx, bool write_valid, std::uint8_t write_idx, std::uint64_t write_addr) {
    read_idx &= 0x1fu; write_idx &= 0x1fu;
    const std::uint64_t old = ras_[read_idx];
    bypass_reg_ = write_valid && read_idx == write_idx;
    write_addr_reg_ = write_addr & ((UINT64_C(1)<<40)-1);
    read_data_reg_ = old & ((UINT64_C(1)<<40)-1);
    if (write_valid) ras_[write_idx] = write_addr & ((UINT64_C(1)<<40)-1);
  }
  bool bypass_reg() const { return bypass_reg_; }
  std::uint64_t write_addr_reg() const { return write_addr_reg_; }
  std::uint64_t read_data_reg() const { return read_data_reg_; }

 private:
  std::array<std::uint64_t, 32> ras_{};
  bool bypass_reg_ = false;
  std::uint64_t write_addr_reg_ = 0x8, read_data_reg_ = 0;
};
}  // namespace chisa::boom_model::fe
