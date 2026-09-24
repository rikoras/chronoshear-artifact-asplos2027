#pragma once

// Cycle-exact functional model of the tiny PLIC configuration endpoint in
// the locked SmallBoom system.  The two interrupt sources are tied low by the
// harness, so the hot behavior is the RegisterRouter's one-entry response
// queue.  Keep the writable register file as well: software may access the
// PLIC even though no external interrupt can become pending.

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "../protocol/peripheral.h"

namespace chisa::boom_system::components {

struct SmallPlicInputs {
  bool reset = false;
  protocol::PeripheralTlA a{};
  bool d_ready = false;
};

class SmallPlic {
 public:
  const protocol::PeripheralManagerInputs& evaluate(
      const SmallPlicInputs& inputs) {
    pending_inputs_ = inputs;
    pending_valid_ = true;
    refresh_outputs();
    return outputs_;
  }

  const protocol::PeripheralManagerInputs& outputs() const {
    return outputs_;
  }

  void commit_evaluated() {
    if (!pending_valid_) return;

    // Queue_43 has depth one and neither flow nor pipe enabled.
    const bool do_enq = !maybe_full_ && pending_inputs_.a.valid;
    const bool do_deq = maybe_full_ && pending_inputs_.d_ready;

    // RegisterRouter applies reads/writes only when the queued D response is
    // accepted, not when the A request first enters the queue.
    const std::uint64_t dequeued_data = response_data();
    if (do_deq) apply_dequeued_request();
    if (do_enq) request_ = pending_inputs_.a;

    if (pending_inputs_.reset) {
      maybe_full_ = false;
      pending_0_ = false;
      pending_1_ = false;
    } else if (do_enq != do_deq) {
      maybe_full_ = do_enq;
    }

    // Both LevelGateway inputs are structural zeroes in TestHarness.  Hence
    // no workload can create a pending interrupt; a claim can only clear one.
    pending_0_ = false;
    pending_1_ = false;

    static const bool plic_debug = std::getenv("SYSPLIC_DEBUG") != nullptr;
    if (plic_debug && (do_enq || do_deq)) {
      if (do_enq) {
        std::fprintf(stderr,
                     "[PLIC] c%llu enq op=%u sz=%u src=%u addr=%08x "
                     "mask=%02x data=%016llx\n",
                     static_cast<unsigned long long>(cycle_),
                     static_cast<unsigned>(pending_inputs_.a.opcode),
                     static_cast<unsigned>(pending_inputs_.a.size),
                     static_cast<unsigned>(pending_inputs_.a.source),
                     pending_inputs_.a.address,
                     static_cast<unsigned>(pending_inputs_.a.mask),
                     static_cast<unsigned long long>(pending_inputs_.a.data));
      }
      if (do_deq) {
        std::fprintf(stderr,
                     "[PLIC] c%llu deq op=%u addr=%08x resp=%016llx "
                     "prio=%u/%u en=%u/%u th=%u/%u\n",
                     static_cast<unsigned long long>(cycle_),
                     static_cast<unsigned>(request_.opcode), request_.address,
                     static_cast<unsigned long long>(dequeued_data),
                     static_cast<unsigned>(priority_0_),
                     static_cast<unsigned>(priority_1_),
                     static_cast<unsigned>(enables_0_),
                     static_cast<unsigned>(enables_1_),
                     static_cast<unsigned>(threshold_0_),
                     static_cast<unsigned>(threshold_1_));
      }
    }

    pending_valid_ = false;
    refresh_outputs();
    ++cycle_;
  }

  void commit(const SmallPlicInputs& inputs) {
    evaluate(inputs);
    commit_evaluated();
  }

  const bool& maybe_full() const { return maybe_full_; }
  std::uint64_t out_back_bank_0() const {
    return (std::uint64_t(request_.opcode == 4) << 23) |
           ((request_.address >> 3) & UINT32_C(0x7fffff));
  }
  std::uint64_t out_back_bank_1() const {
    return (std::uint64_t(request_.mask & UINT8_C(0xff)) << 11) |
           (std::uint64_t(request_.source & UINT16_C(0x1ff)) << 2) |
           (request_.size & UINT8_C(0x3));
  }
  std::uint64_t out_back_data() const { return request_.data; }
  bool pending_0() const { return pending_0_; }
  bool pending_1() const { return pending_1_; }
  bool active() const { return maybe_full_; }

  std::uint8_t priority(std::size_t index) const {
    return index == 0 ? priority_0_ : priority_1_;
  }
  std::uint8_t enables(std::size_t context) const {
    return context == 0 ? enables_0_ : enables_1_;
  }
  std::uint8_t threshold(std::size_t context) const {
    return context == 0 ? threshold_0_ : threshold_1_;
  }

 private:
  struct DecodedAddress {
    bool valid = false;
    std::uint8_t selector = 0;
  };

  static DecodedAddress decode(std::uint32_t address) {
    // Exact RegisterRouter equations from TLPLIC: index=address[25:3], the
    // bindex mask rejects holes, and five sparse bits form the one-hot field
    // selector.  Keeping the equations avoids baking in one address alias.
    const std::uint32_t index = (address >> 3) & UINT32_C(0x7fffff);
    if ((index & UINT32_C(0x7bf9ee)) != 0) return {};
    const std::uint8_t selector =
        static_cast<std::uint8_t>(((index >> 18) & 1u) << 4 |
                                  ((index >> 10) & 1u) << 3 |
                                  ((index >> 9) & 1u) << 2 |
                                  ((index >> 4) & 1u) << 1 |
                                  (index & 1u));
    return {true, selector};
  }

  std::uint64_t response_data() const {
    const DecodedAddress address = decode(request_.address);
    if (!address.valid) return 0;
    switch (address.selector) {
      case 0: return std::uint64_t(priority_0_ & 3u) << 32;
      case 1: return priority_1_ & 3u;
      case 4:
        return (std::uint64_t(pending_1_) << 2) |
               (std::uint64_t(pending_0_) << 1);
      case 8: return std::uint64_t(enables_0_ & 3u) << 1;
      case 10: return std::uint64_t(enables_1_ & 3u) << 1;
      case 16:
        // maxDevs_0 is always zero when both pending bits are zero.
        return threshold_0_ & 3u;
      case 20:
        // maxDevs_1 is always zero when both pending bits are zero.
        return threshold_1_ & 3u;
      default: return 0;
    }
  }

  void apply_dequeued_request() {
    if (request_.opcode == 4) {
      // Claim reads would clear the selected pending source.  Both sources
      // are structurally inactive, so the selected device is always zero.
      return;
    }

    const DecodedAddress address = decode(request_.address);
    if (!address.valid) return;
    switch (address.selector) {
      case 0:
        if (request_.mask & UINT8_C(0x10))
          priority_0_ = static_cast<std::uint8_t>((request_.data >> 32) & 3u);
        break;
      case 1:
        if (request_.mask & UINT8_C(0x01))
          priority_1_ = static_cast<std::uint8_t>(request_.data & 3u);
        break;
      case 8:
        if (request_.mask & UINT8_C(0x01))
          enables_0_ = static_cast<std::uint8_t>((request_.data >> 1) & 3u);
        break;
      case 10:
        if (request_.mask & UINT8_C(0x01))
          enables_1_ = static_cast<std::uint8_t>((request_.data >> 1) & 3u);
        break;
      case 16:
        if (request_.mask & UINT8_C(0x01))
          threshold_0_ = static_cast<std::uint8_t>(request_.data & 3u);
        break;
      case 20:
        if (request_.mask & UINT8_C(0x01))
          threshold_1_ = static_cast<std::uint8_t>(request_.data & 3u);
        break;
      default:
        // Pending is read-only; claim/complete has no effect with no source.
        break;
    }
  }

  void refresh_outputs() {
    outputs_ = {};
    outputs_.a_ready = !maybe_full_;
    outputs_.d.valid = maybe_full_;
    outputs_.d.opcode = request_.opcode == 4 ? 1 : 0;
    outputs_.d.size = request_.size & 3u;
    outputs_.d.source = request_.source & UINT16_C(0x1ff);
    outputs_.d.data = response_data();
  }

  protocol::PeripheralTlA request_{};
  SmallPlicInputs pending_inputs_{};
  protocol::PeripheralManagerInputs outputs_{};
  bool pending_valid_ = false;
  bool maybe_full_ = false;
  bool pending_0_ = false;
  bool pending_1_ = false;
  std::uint8_t priority_0_ = 0;
  std::uint8_t priority_1_ = 0;
  std::uint8_t threshold_0_ = 0;
  std::uint8_t threshold_1_ = 0;
  std::uint8_t enables_0_ = 0;
  std::uint8_t enables_1_ = 0;
  std::uint64_t cycle_ = 0;
};

}  // namespace chisa::boom_system::components
