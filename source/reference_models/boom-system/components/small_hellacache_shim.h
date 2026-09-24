#pragma once
// ============================================================================
// BOOM LSU HellaCache timing shim.
//
// The locked SmallBoom has one HellaCache client (the PTW), so the outer
// HellaCacheArbiter is a wire.  This component models the seven registered
// states inside LSU that sit between that wire, the DTLB and the D-cache.
// Arbitration against ordinary LSU traffic stays in the hot core; it reports
// the two `*_granted` decisions here.
// ============================================================================

#include <cstdint>

#include "boom_uncached_path.h"

namespace chisa::boom_system::components {

struct SmallHellaCacheRequest {
  bool valid = false;
  std::uint64_t address = 0;
  std::uint8_t tag = 0;
  std::uint8_t command = 0;
  std::uint8_t size = 0;
  bool is_signed = false;
  std::uint8_t dprv = 0;
  bool physical = false;
  bool no_allocate = false;
  bool no_exception = false;
  std::uint64_t data = 0;
  std::uint8_t mask = 0;
};

struct SmallHellaCacheExceptions {
  bool ma_ld = false;
  bool ma_st = false;
  bool pf_ld = false;
  bool pf_st = false;
  bool ae_ld = false;
  bool ae_st = false;

  bool any() const {
    return ma_ld || ma_st || pf_ld || pf_st || ae_ld || ae_st;
  }
};

struct SmallHellaCacheResponse {
  bool valid = false;
  std::uint64_t address = 0;
  std::uint8_t tag = 0;
  std::uint8_t command = 0;
  std::uint8_t size = 0;
  bool is_signed = false;
  std::uint8_t dprv = 0;
  std::uint64_t data = 0;
  std::uint8_t mask = 0;
  bool replay = false;
  bool has_data = false;
  std::uint64_t data_word_bypass = 0;
  std::uint64_t data_raw = 0;
  std::uint64_t store_data = 0;
};

struct SmallHellaCacheInputs {
  bool reset = false;

  // Current PTW-side HellaCache wires.  request is sampled only in Ready;
  // s1_data/s1_kill and s2_kill are intentionally separate-cycle signals.
  SmallHellaCacheRequest request{};
  std::uint64_t s1_data = 0;
  bool s1_kill = false;
  bool s2_kill = false;

  // Result of the hot LSU's fixed-priority resource scheduler.
  bool incoming_granted = false;  // TLB + D-cache in state S1.
  bool replay_granted = false;    // D-cache only in state Replay.
  bool dcache_ready = false;

  // DTLB response sampled in state S1.  A physical request still traverses
  // the LSU TLB scheduling slot, but ignores miss when issuing D-cache.
  bool tlb_miss = false;
  std::uint64_t tlb_paddr = 0;
  SmallHellaCacheExceptions tlb_exceptions{};

  BoomUncachedCompletion dcache_response{};
  BoomUncachedCompletion dcache_nack{};
};

struct SmallHellaCacheOutputs {
  bool request_ready = false;
  bool wants_incoming = false;
  bool wants_replay = false;
  BoomUncachedRequest dcache_request{};
  bool dcache_request_fire = false;
  bool s2_nack = false;
  SmallHellaCacheExceptions s2_exceptions{};
  SmallHellaCacheResponse response{};
  std::uint8_t state = 0;
  std::uint64_t held_paddr = 0;
};

class SmallHellaCacheShim {
 public:
  // Encoding is the Chisel Enum order in lsu.scala and is itself an oracle.
  enum class State : std::uint8_t {
    kReady = 0,
    kS1 = 1,
    kS2 = 2,
    kS2Nack = 3,
    kWait = 4,
    kReplay = 5,
    kDead = 6,
  };

  void reset() { *this = SmallHellaCacheShim{}; }

  SmallHellaCacheOutputs outputs(const SmallHellaCacheInputs& input) const {

    SmallHellaCacheOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const SmallHellaCacheInputs& input, SmallHellaCacheOutputs& result) const {
    result = SmallHellaCacheOutputs{};
    result.request_ready = state_ == State::kReady;
    result.wants_incoming = state_ == State::kS1;
    result.wants_replay = state_ == State::kReplay;
    result.state = static_cast<std::uint8_t>(state_);
    result.held_paddr = paddr_;

    if (state_ == State::kS1 && input.incoming_granted) {
      result.dcache_request.valid =
          !input.s1_kill && (!input.tlb_miss || request_.physical);
      result.dcache_request.command = request_.command;
      result.dcache_request.size = request_.size;
      result.dcache_request.is_signed = request_.is_signed;
      result.dcache_request.address = input.tlb_paddr;
      result.dcache_request.data = storegen(request_.size, input.s1_data);
      result.dcache_request.is_hella = true;
    } else if (state_ == State::kReplay && input.replay_granted) {
      result.dcache_request.valid = true;
      result.dcache_request.command = request_.command;
      result.dcache_request.size = request_.size;
      result.dcache_request.is_signed = request_.is_signed;
      result.dcache_request.address = paddr_;
      result.dcache_request.data = storegen(request_.size, data_);
      result.dcache_request.is_hella = true;
    }
    result.dcache_request_fire =
        result.dcache_request.valid && input.dcache_ready;

    if (state_ == State::kS2Nack) result.s2_nack = true;
    if (state_ == State::kS2) result.s2_exceptions = exceptions_;

    if (state_ == State::kWait && input.dcache_response.valid &&
        input.dcache_response.is_hella) {
      result.response.valid = true;
      result.response.address = request_.address;
      result.response.tag = request_.tag;
      result.response.command = request_.command;
      result.response.size = request_.size;
      result.response.is_signed = request_.is_signed;
      result.response.dprv = request_.dprv;
      result.response.data = input.dcache_response.data;
      result.response.mask = request_.mask;
      result.response.has_data = returns_data(request_.command);
      result.response.data_word_bypass = input.dcache_response.data;
      result.response.data_raw = input.dcache_response.data;
      result.response.store_data = data_;
    }
    return;
  }

  void step(const SmallHellaCacheInputs& input) {
    if (input.reset) {
      reset();
      return;
    }

    const SmallHellaCacheOutputs output = outputs(input);
    switch (state_) {
      case State::kReady:
        if (input.request.valid) {
          request_ = input.request;
          state_ = State::kS1;
        }
        break;

      case State::kS1:
        // RTL samples these payloads even when a higher-priority LSU request
        // prevents the Hella request from obtaining the scheduler slot.
        data_ = input.s1_data;
        exceptions_ = input.tlb_exceptions;
        if (input.incoming_granted) paddr_ = input.tlb_paddr;
        if (input.s1_kill) {
          // dmem_req.valid is killed too, so fire is normally impossible;
          // retain the literal RTL condition for completeness.
          state_ = output.dcache_request_fire ? State::kDead
                                              : State::kReady;
        } else {
          state_ = output.dcache_request_fire ? State::kS2
                                              : State::kS2Nack;
        }
        break;

      case State::kS2Nack:
        state_ = State::kReady;
        break;

      case State::kS2:
        state_ = (input.s2_kill || exceptions_.any()) ? State::kDead
                                                      : State::kWait;
        break;

      case State::kWait:
        // The RTL gives a response priority over a simultaneous nack.
        if (input.dcache_response.valid && input.dcache_response.is_hella)
          state_ = State::kReady;
        else if (input.dcache_nack.valid && input.dcache_nack.is_hella)
          state_ = State::kReplay;
        break;

      case State::kReplay:
        if (input.replay_granted && output.dcache_request_fire)
          state_ = State::kWait;
        break;

      case State::kDead:
        // A killed request must still drain its D-cache response.  Nacks are
        // deliberately ignored, matching BOOM's controller.
        if (input.dcache_response.valid && input.dcache_response.is_hella)
          state_ = State::kReady;
        break;
    }
  }

  State state() const { return state_; }
  std::uint64_t paddr() const { return paddr_; }
  const SmallHellaCacheRequest& held_request() const { return request_; }

 private:
  static bool returns_data(std::uint8_t command) {
    // Rocket MemoryOpConstants: reads/LR/AMOs return a data value; ordinary
    // writes do not.  PTW uses M_XRD (0).
    return command == 0 || command == 6 || command >= 8;
  }

  static std::uint64_t storegen(std::uint8_t size, std::uint64_t data) {
    switch (size & 3u) {
      case 0: {
        const std::uint64_t b = data & UINT64_C(0xff);
        return b * UINT64_C(0x0101010101010101);
      }
      case 1: {
        const std::uint64_t h = data & UINT64_C(0xffff);
        return h | (h << 16) | (h << 32) | (h << 48);
      }
      case 2: {
        const std::uint64_t w = data & UINT64_C(0xffffffff);
        return w | (w << 32);
      }
      default:
        return data;
    }
  }

  State state_ = State::kReady;
  SmallHellaCacheRequest request_{};
  std::uint64_t data_ = 0;
  std::uint64_t paddr_ = 0;
  SmallHellaCacheExceptions exceptions_{};
};

}  // namespace chisa::boom_system::components
