#pragma once
#include "memory_bus.h"
namespace chisa::boom_system::protocol {
struct CoherentTlB {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint32_t address = 0;
  std::uint8_t mask = 0;
  std::uint64_t data = 0;
  bool corrupt = false;
};

struct CoherentTlC {
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
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;  // tile-side beat bytes 8..15
  bool corrupt = false;

  bool operator==(const CoherentTlC& other) const {
    return valid == other.valid && opcode == other.opcode &&
           param == other.param && size == other.size &&
           source == other.source && address == other.address &&
           bufferable == other.bufferable &&
           modifiable == other.modifiable && readalloc == other.readalloc &&
           writealloc == other.writealloc &&
           privileged == other.privileged && secure == other.secure &&
           fetch == other.fetch && data == other.data &&
           data_hi == other.data_hi &&
           corrupt == other.corrupt;
  }
};

struct CoherentTlD {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint8_t sink = 0;
  bool denied = false;
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;  // beat bytes 8..15 (zero on Small)
  bool corrupt = false;
};

struct CoherentTlE {
  bool valid = false;
  std::uint8_t sink = 0;

  bool operator==(const CoherentTlE& other) const {
    return valid == other.valid && sink == other.sink;
  }
};

struct CoherenceManagerInputs {
  bool reset = false;
  MbusTlA tile_a{};  // Same payload shape; source is masked to five bits.
  bool tile_b_ready = false;
  CoherentTlC tile_c{};
  bool tile_d_ready = false;
  CoherentTlE tile_e{};

  bool mbus_a_ready = false;
  MbusTlD mbus_d{};

  bool operator==(const CoherenceManagerInputs& other) const {
    return reset == other.reset && tile_a == other.tile_a &&
           tile_b_ready == other.tile_b_ready && tile_c == other.tile_c &&
           tile_d_ready == other.tile_d_ready && tile_e == other.tile_e &&
           mbus_a_ready == other.mbus_a_ready &&
           mbus_d.valid == other.mbus_d.valid &&
           mbus_d.opcode == other.mbus_d.opcode &&
           mbus_d.param == other.mbus_d.param &&
           mbus_d.size == other.mbus_d.size &&
           mbus_d.source == other.mbus_d.source &&
           mbus_d.sink == other.mbus_d.sink &&
           mbus_d.denied == other.mbus_d.denied &&
           mbus_d.data == other.mbus_d.data &&
           mbus_d.corrupt == other.mbus_d.corrupt;
  }
  bool operator!=(const CoherenceManagerInputs& other) const {
    return !(*this == other);
  }
};

struct CoherenceManagerOutputs {
  bool tile_a_ready = false;
  CoherentTlB tile_b{};
  bool tile_c_ready = false;
  CoherentTlD tile_d{};
  bool tile_e_ready = false;

  MbusTlA mbus_a{};
  bool mbus_d_ready = false;
};

} // namespace chisa::boom_system::protocol
