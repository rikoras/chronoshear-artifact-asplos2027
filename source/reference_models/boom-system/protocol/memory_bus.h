#pragma once
#include <cstdint>
namespace chisa::boom_system::protocol {
struct MbusTlA {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint32_t address = 0;
  bool bufferable = false;
  bool modifiable = false;
  bool readalloc = false;
  bool writealloc = false;
  bool privileged = false;
  bool secure = false;
  bool fetch = false;
  // Also used at the tile boundary, before Large's 128-to-64-bit widget.
  std::uint16_t mask = 0;
  std::uint64_t data = 0;
  bool corrupt = false;
  std::uint64_t data_hi = 0;

  bool operator==(const MbusTlA& other) const {
    return valid == other.valid && opcode == other.opcode &&
           param == other.param && size == other.size &&
           source == other.source && address == other.address &&
           bufferable == other.bufferable &&
           modifiable == other.modifiable && readalloc == other.readalloc &&
           writealloc == other.writealloc &&
           privileged == other.privileged && secure == other.secure &&
           fetch == other.fetch && mask == other.mask && data == other.data &&
           corrupt == other.corrupt && data_hi == other.data_hi;
  }
};

struct MbusAxiB {
  bool valid = false;
  std::uint8_t id = 0;
  std::uint8_t response = 0;

  bool operator==(const MbusAxiB& other) const {
    return valid == other.valid && id == other.id &&
           response == other.response;
  }
};

struct MbusAxiR {
  bool valid = false;
  std::uint8_t id = 0;
  std::uint64_t data = 0;
  std::uint8_t response = 0;
  bool last = false;

  bool operator==(const MbusAxiR& other) const {
    return valid == other.valid && id == other.id && data == other.data &&
           response == other.response && last == other.last;
  }
};

struct MbusCouplerInputs {
  bool reset = false;
  MbusTlA tl_a{};
  bool tl_d_ready = false;
  bool axi_aw_ready = false;
  bool axi_w_ready = false;
  MbusAxiB axi_b{};
  bool axi_ar_ready = false;
  MbusAxiR axi_r{};

  bool operator==(const MbusCouplerInputs& other) const {
    return reset == other.reset && tl_a == other.tl_a &&
           tl_d_ready == other.tl_d_ready &&
           axi_aw_ready == other.axi_aw_ready &&
           axi_w_ready == other.axi_w_ready && axi_b == other.axi_b &&
           axi_ar_ready == other.axi_ar_ready && axi_r == other.axi_r;
  }
  bool operator!=(const MbusCouplerInputs& other) const {
    return !(*this == other);
  }
};

struct MbusTlD {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  bool sink = false;
  bool denied = false;
  std::uint64_t data = 0;
  bool corrupt = false;
};

struct MbusAxiAw {
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
};

struct MbusAxiW {
  bool valid = false;
  std::uint64_t data = 0;
  std::uint8_t strobe = 0;
  bool last = false;
};

using MbusAxiAr = MbusAxiAw;

struct MbusCouplerOutputs {
  bool tl_a_ready = false;
  MbusTlD tl_d{};
  MbusAxiAw axi_aw{};
  MbusAxiW axi_w{};
  bool axi_b_ready = false;
  MbusAxiAr axi_ar{};
  bool axi_r_ready = false;
};

} // namespace chisa::boom_system::protocol
