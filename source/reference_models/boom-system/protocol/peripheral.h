#pragma once
#include <cstdint>
#include "memory_bus.h"
#include "coherence.h"
namespace chisa::boom_system::protocol {
struct PeripheralTlA {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint16_t source = 0;
  std::uint32_t address = 0;
  std::uint8_t mask = 0;
  std::uint64_t data = 0;
  bool corrupt = false;

  bool operator==(const PeripheralTlA& other) const {
    return valid == other.valid && opcode == other.opcode &&
           param == other.param && size == other.size &&
           source == other.source && address == other.address &&
           mask == other.mask && data == other.data &&
           corrupt == other.corrupt;
  }
};

struct PeripheralTlD {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint16_t source = 0;
  bool sink = false;
  bool denied = false;
  std::uint64_t data = 0;
  bool corrupt = false;

  bool operator==(const PeripheralTlD& other) const {
    return valid == other.valid && opcode == other.opcode &&
           param == other.param && size == other.size &&
           source == other.source && sink == other.sink &&
           denied == other.denied && data == other.data &&
           corrupt == other.corrupt;
  }
};

struct PeripheralManagerInputs {
  bool a_ready = false;
  PeripheralTlD d{};

  bool operator==(const PeripheralManagerInputs& other) const {
    return a_ready == other.a_ready && d == other.d;
  }
};

struct PeripheralManagerOutputs {
  PeripheralTlA a{};
  bool d_ready = false;
};

struct PeripheryBusInputs {
  bool reset = false;
  MbusTlA upstream_a{};
  bool upstream_d_ready = false;
  PeripheralManagerInputs bootrom{};
  PeripheralManagerInputs debug{};
  PeripheralManagerInputs clint{};
  PeripheralManagerInputs plic{};

  bool operator==(const PeripheryBusInputs& other) const {
    return reset == other.reset && upstream_a == other.upstream_a &&
           upstream_d_ready == other.upstream_d_ready &&
           bootrom == other.bootrom && debug == other.debug &&
           clint == other.clint && plic == other.plic;
  }
  bool operator!=(const PeripheryBusInputs& other) const {
    return !(*this == other);
  }
};

struct PeripheryBusOutputs {
  bool upstream_a_ready = false;
  CoherentTlD upstream_d{};
  PeripheralManagerOutputs bootrom{};
  PeripheralManagerOutputs debug{};
  PeripheralManagerOutputs clint{};
  PeripheralManagerOutputs plic{};
};

} // namespace chisa::boom_system::protocol
