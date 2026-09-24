#pragma once
#include "coherence.h"
namespace chisa::boom_system::protocol {
inline bool same_tl_b(const CoherentTlB& left, const CoherentTlB& right) {
  return left.valid == right.valid && left.opcode == right.opcode &&
         left.param == right.param && left.size == right.size &&
         left.source == right.source && left.address == right.address &&
         left.mask == right.mask && left.data == right.data &&
         left.corrupt == right.corrupt;
}

inline bool same_tl_d(const CoherentTlD& left, const CoherentTlD& right) {
  return left.valid == right.valid && left.opcode == right.opcode &&
         left.param == right.param && left.size == right.size &&
         left.source == right.source && left.sink == right.sink &&
         left.denied == right.denied && left.data == right.data &&
         left.data_hi == right.data_hi &&
         left.corrupt == right.corrupt;
}

inline bool same_tl_d(const MbusTlD& left, const MbusTlD& right) {
  return left.valid == right.valid && left.opcode == right.opcode &&
         left.param == right.param && left.size == right.size &&
         left.source == right.source && left.sink == right.sink &&
         left.denied == right.denied && left.data == right.data &&
         left.corrupt == right.corrupt;
}

struct SystemBusInputs {
  bool reset = false;

  // Hot BOOM tile client.
  MbusTlA tile_a{};
  bool tile_b_ready = false;
  CoherentTlC tile_c{};
  bool tile_d_ready = false;
  CoherentTlE tile_e{};

  // Cold L2/coherence manager.
  bool l2_a_ready = false;
  CoherentTlB l2_b{};
  bool l2_c_ready = false;
  CoherentTlD l2_d{};
  bool l2_e_ready = false;

  // Front bus is another uncached client of the system bus.
  MbusTlA fbus_a{};
  bool fbus_d_ready = false;

  // Control bus is an uncached manager reached from the system bus.
  bool cbus_a_ready = false;
  CoherentTlD cbus_d{};

  // Direct MMIO AXI manager port.
  bool mmio_axi_aw_ready = false;
  bool mmio_axi_w_ready = false;
  MbusAxiB mmio_axi_b{};
  bool mmio_axi_ar_ready = false;
  MbusAxiR mmio_axi_r{};

  bool operator==(const SystemBusInputs& other) const {
    return reset == other.reset && tile_a == other.tile_a &&
           tile_b_ready == other.tile_b_ready && tile_c == other.tile_c &&
           tile_d_ready == other.tile_d_ready && tile_e == other.tile_e &&
           l2_a_ready == other.l2_a_ready && same_tl_b(l2_b, other.l2_b) &&
           l2_c_ready == other.l2_c_ready && same_tl_d(l2_d, other.l2_d) &&
           l2_e_ready == other.l2_e_ready && fbus_a == other.fbus_a &&
           fbus_d_ready == other.fbus_d_ready &&
           cbus_a_ready == other.cbus_a_ready &&
           same_tl_d(cbus_d, other.cbus_d) &&
           mmio_axi_aw_ready == other.mmio_axi_aw_ready &&
           mmio_axi_w_ready == other.mmio_axi_w_ready &&
           mmio_axi_b == other.mmio_axi_b &&
           mmio_axi_ar_ready == other.mmio_axi_ar_ready &&
           mmio_axi_r == other.mmio_axi_r;
  }
  bool operator!=(const SystemBusInputs& other) const {
    return !(*this == other);
  }
};

struct SystemBusOutputs {
  bool tile_a_ready = false;
  CoherentTlB tile_b{};
  bool tile_c_ready = false;
  CoherentTlD tile_d{};
  bool tile_e_ready = false;

  MbusTlA l2_a{};
  bool l2_b_ready = false;
  CoherentTlC l2_c{};
  bool l2_d_ready = false;
  CoherentTlE l2_e{};

  bool fbus_a_ready = false;
  CoherentTlD fbus_d{};

  MbusTlA cbus_a{};
  bool cbus_d_ready = false;

  MbusAxiAw mmio_axi_aw{};
  MbusAxiW mmio_axi_w{};
  bool mmio_axi_b_ready = false;
  MbusAxiAr mmio_axi_ar{};
  bool mmio_axi_r_ready = false;
};

}
