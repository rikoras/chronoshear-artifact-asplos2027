#pragma once
#include "axi.h"
namespace chisa::boom_system::protocol {
/** One cycle at the eight byte-wide SRAM ports, before the committing edge.
  * Addresses are bank indices, not AXI byte addresses.  The read port remains
  * live even when the AXI response is invalid or held.  A consumer without a
  * memory image checks these accesses against its own RTL control logic. */
struct AxiRamAccess {
  std::uint32_t read_address = 0;
  std::uint64_t read_data = 0;
  std::uint32_t write_address = 0;
  std::uint64_t write_data = 0;
  std::uint8_t write_mask = 0;
};


struct SparseAxiRamInputs {
  bool reset = false;
  AxiAddress aw{};
  AxiWriteData w{};
  bool b_ready = false;
  AxiAddress ar{};
  bool r_ready = false;

  bool operator==(const SparseAxiRamInputs& other) const {
    return reset == other.reset && aw == other.aw && w == other.w &&
           b_ready == other.b_ready && ar == other.ar &&
           r_ready == other.r_ready;
  }
  bool operator!=(const SparseAxiRamInputs& other) const {
    return !(*this == other);
  }
};

struct SparseAxiRamOutputs {
  bool aw_ready = false;
  bool w_ready = false;
  AxiWriteResponse b{};
  bool ar_ready = false;
  AxiReadResponse r{};
};

}
