#pragma once
// Software channel values for a 64-bit AXI transaction interface. These
// contain payloads and handshakes only, with no RTL evaluator or DUT state.
#include <cstdint>
namespace chisa::boom_system::protocol {
struct AxiAddress {
  bool valid = false;
  std::uint8_t id = 0;
  std::uint32_t address = 0;
  std::uint8_t length = 0;
  std::uint8_t size = 0;
  std::uint8_t burst = 0;
  bool lock = false;
  std::uint8_t cache = 0;
  std::uint8_t protection = 0;
  std::uint8_t qos = 0;
  bool echo_real_last = false;

  bool operator==(const AxiAddress& other) const {
    return valid == other.valid && id == other.id &&
           address == other.address && length == other.length &&
           size == other.size && burst == other.burst &&
           lock == other.lock && cache == other.cache &&
           protection == other.protection && qos == other.qos &&
           echo_real_last == other.echo_real_last;
  }
};

struct AxiWriteData {
  bool valid = false;
  std::uint64_t data = 0;
  std::uint8_t strobe = 0;
  bool last = false;

  bool operator==(const AxiWriteData& other) const {
    return valid == other.valid && data == other.data &&
           strobe == other.strobe && last == other.last;
  }
};

struct AxiWriteResponse {
  bool valid = false;
  std::uint8_t id = 0;
  std::uint8_t response = 0;
  bool echo_real_last = false;

  bool operator==(const AxiWriteResponse& other) const {
    return valid == other.valid && id == other.id &&
           response == other.response &&
           echo_real_last == other.echo_real_last;
  }
};

struct AxiReadResponse {
  bool valid = false;
  std::uint8_t id = 0;
  std::uint64_t data = 0;
  std::uint8_t response = 0;
  bool echo_real_last = false;
  bool last = false;

  bool operator==(const AxiReadResponse& other) const {
    return valid == other.valid && id == other.id && data == other.data &&
           response == other.response &&
           echo_real_last == other.echo_real_last && last == other.last;
  }
};

struct AxiStageInputs {
  bool reset = false;

  AxiAddress in_aw{};
  AxiWriteData in_w{};
  bool in_b_ready = false;
  AxiAddress in_ar{};
  bool in_r_ready = false;

  bool out_aw_ready = false;
  bool out_w_ready = false;
  AxiWriteResponse out_b{};
  bool out_ar_ready = false;
  AxiReadResponse out_r{};

  bool operator==(const AxiStageInputs& other) const {
    return reset == other.reset && in_aw == other.in_aw &&
           in_w == other.in_w && in_b_ready == other.in_b_ready &&
           in_ar == other.in_ar && in_r_ready == other.in_r_ready &&
           out_aw_ready == other.out_aw_ready &&
           out_w_ready == other.out_w_ready && out_b == other.out_b &&
           out_ar_ready == other.out_ar_ready && out_r == other.out_r;
  }
  bool operator!=(const AxiStageInputs& other) const {
    return !(*this == other);
  }
};

struct AxiStageOutputs {
  bool in_aw_ready = false;
  bool in_w_ready = false;
  AxiWriteResponse in_b{};
  bool in_ar_ready = false;
  AxiReadResponse in_r{};

  AxiAddress out_aw{};
  AxiWriteData out_w{};
  bool out_b_ready = false;
  AxiAddress out_ar{};
  bool out_r_ready = false;
};

}  // namespace chisa::boom_system::protocol
