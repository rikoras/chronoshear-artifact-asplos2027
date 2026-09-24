#pragma once
// Diagnostic bridge to the old scalar producer. This header is not needed by
// the all-native execution path; it can feed the same real cache/DMI traffic
// into Uncore and compare architectural channel behavior before either edge.
#include "uncore/uncore.h"

namespace chisa::rocket_model::uncore {

template <class Cold>
void capture_uncore_cache_inputs(const Cold& cold, UncoreIn& in) {
  const auto& dc = cold.ldut.tile_prci_domain.tile_reset_domain.tile.dcache;
  const auto& ic = cold.ldut.tile_prci_domain.tile_reset_domain.tile.frontend;
#define READ(target, owner, port) target = owner.port.as_single_word()
  READ(in.dc_a_valid, dc, auto_out_a_valid);
  READ(in.dc_c_valid, dc, auto_out_c_valid);
  READ(in.dc_e_valid, dc, auto_out_e_valid);
  READ(in.dc_b_ready, dc, auto_out_b_ready);
  READ(in.dc_d_ready, dc, auto_out_d_ready);
  READ(in.ic_a_valid, ic, auto_icache_master_out_a_valid);
  READ(in.ic_d_ready, ic, auto_icache_master_out_d_ready);
#define A_FIELD(field) READ(in.dc_a.field, dc, auto_out_a_bits_##field); READ(in.ic_a.field, ic, auto_icache_master_out_a_bits_##field)
  A_FIELD(opcode); A_FIELD(param); A_FIELD(size); A_FIELD(source); A_FIELD(address); A_FIELD(mask); A_FIELD(data); A_FIELD(corrupt);
#undef A_FIELD
#define C_FIELD(field) READ(in.dc_c.field, dc, auto_out_c_bits_##field)
  C_FIELD(opcode); C_FIELD(param); C_FIELD(size); C_FIELD(source); C_FIELD(address); C_FIELD(data); C_FIELD(corrupt);
#undef C_FIELD
  READ(in.dc_e.sink, dc, auto_out_e_bits_sink);
#undef READ
}

template <class Cold>
UncoreOut capture_uncore_outputs(const Cold& cold) {
  const auto& dc = cold.ldut.tile_prci_domain.tile_reset_domain.tile.dcache;
  const auto& ic = cold.ldut.tile_prci_domain.tile_reset_domain.tile.frontend;
  const auto& core = cold.ldut.tile_prci_domain.tile_reset_domain.tile.core;
  const auto& dtm = cold.SimDTM;
  UncoreOut out;
#define READ(target, owner, port) target = owner.port.as_single_word()
  READ(out.dc_a_ready, dc, auto_out_a_ready); READ(out.dc_c_ready, dc, auto_out_c_ready); READ(out.dc_e_ready, dc, auto_out_e_ready);
  READ(out.dc_b_valid, dc, auto_out_b_valid); READ(out.dc_d_valid, dc, auto_out_d_valid);
  READ(out.ic_a_ready, ic, auto_icache_master_out_a_ready); READ(out.ic_d_valid, ic, auto_icache_master_out_d_valid);
#define B_FIELD(field) READ(out.dc_b.field, dc, auto_out_b_bits_##field)
  B_FIELD(opcode); B_FIELD(param); B_FIELD(size); B_FIELD(source); B_FIELD(address); B_FIELD(mask); B_FIELD(data); B_FIELD(corrupt);
#undef B_FIELD
#define D_FIELD(field) READ(out.dc_d.field, dc, auto_out_d_bits_##field); READ(out.ic_d.field, ic, auto_icache_master_out_d_bits_##field)
  D_FIELD(opcode); D_FIELD(param); D_FIELD(size); D_FIELD(source); D_FIELD(sink); D_FIELD(denied); D_FIELD(data); D_FIELD(corrupt);
#undef D_FIELD
  READ(out.dmi_req_ready, dtm, debug_req_ready); READ(out.dmi_resp_valid, dtm, debug_resp_valid);
  READ(out.dmi_resp_data, dtm, debug_resp_bits_data); READ(out.dmi_resp_resp, dtm, debug_resp_bits_resp);
  READ(out.int_debug, core, io_interrupts_debug); READ(out.int_msip, core, io_interrupts_msip);
  READ(out.int_mtip, core, io_interrupts_mtip); READ(out.int_meip, core, io_interrupts_meip); READ(out.int_seip, core, io_interrupts_seip);
  READ(out.system_reset, core, reset);
#undef READ
  return out;
}

// This diagnoses the valid channel contract. It is explicitly separate from
// the retained strict 650-stream internal oracle contract.
inline const char* first_uncore_boundary_mismatch(const UncoreOut& a, const UncoreOut& b, bool invalid_payloads = false) {
#define EQ(field) if (a.field != b.field) return #field
  EQ(dc_a_ready); EQ(dc_c_ready); EQ(dc_e_ready); EQ(dc_b_valid); EQ(dc_d_valid);
  EQ(ic_a_ready); EQ(ic_d_valid); EQ(dmi_req_ready); EQ(dmi_resp_valid);
  EQ(int_debug); EQ(int_msip); EQ(int_mtip); EQ(int_meip); EQ(int_seip); EQ(system_reset);
  if (a.dc_b_valid || invalid_payloads) {
    EQ(dc_b.opcode); EQ(dc_b.param); EQ(dc_b.size); EQ(dc_b.source); EQ(dc_b.address); EQ(dc_b.mask); EQ(dc_b.data); EQ(dc_b.corrupt);
  }
  if (a.dc_d_valid || invalid_payloads) {
    EQ(dc_d.opcode); EQ(dc_d.param); EQ(dc_d.size); EQ(dc_d.source); EQ(dc_d.sink); EQ(dc_d.denied); EQ(dc_d.data); EQ(dc_d.corrupt);
  }
  if (a.ic_d_valid || invalid_payloads) {
    EQ(ic_d.opcode); EQ(ic_d.param); EQ(ic_d.size); EQ(ic_d.source); EQ(ic_d.sink); EQ(ic_d.denied); EQ(ic_d.data); EQ(ic_d.corrupt);
  }
  if (a.dmi_resp_valid || invalid_payloads) { EQ(dmi_resp_data); EQ(dmi_resp_resp); }
#undef EQ
  return nullptr;
}

}  // namespace chisa::rocket_model::uncore
