#include "oracle_bindings.h"
#include "../../boom-system/model_bindings.h"
#include "../../boom-system/system_guider.h"
#include "../../boom-system/generated/system_probe_registry.inc"
#include <string_view>
#include "../common/diagnostic_monitor.h"
#include "system_publication.h"
namespace chisa::boom_system {
namespace {
struct Constant { const char* key; std::uint64_t value; };
// Arbitration read ports belong to this cycle. As in Small, the writer
// patches these few already-computed words into the current position.
// Pure registered-address reads remain in the next cycle's record.
template<unsigned Port> std::uint64_t rob_uop_port(const SystemGuider&) {
  return boom_model::wide::system_record().c.coreRob.state_rob_uop_r[Port];
}
template<unsigned Port> std::uint64_t rob_busy_port(const SystemGuider&) {
  return boom_model::wide::system_record().c.coreRob.state_rob_bsy_r[Port];
}
std::uint64_t sdq_port(const SystemGuider& m) {
  return m.memory().dcache_for_diagnostic().sdq_port_cycle_oracle();
}
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
template<unsigned Port> std::uint64_t ftq_ram_port(const SystemGuider& m) {
  const auto value=boom_model::wide::system_record().c.frontendFtq.state_ram_r[Port];
  CHISA_DIAG(
    const auto& ftq=m.frontend().ftq_for_diagnostic();
    chisa::diagnostic::sample("ftq", "ram-current-publication",
      m.cycle() ? m.cycle()-1 : chisa::diagnostic::unknown_cycle,
      chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Combinational,
      {{"index", Port}, {"address", ftq.oracle_ram_idx(Port)}, {"native", ftq.oracle_ram_read(Port)},
       {"typed_record", value}, {"register_cycle", m.cycle()}});
  );
  return value;
}
#endif
struct CurrentPort { const char* key; PredictFn value; };
constexpr CurrentPort current_ports[] = {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  // These Reg(Vec) reads use this edge's addresses and PRE array contents.
  // Their snapshots are captured inside FTQ::commit before any writes, so
  // patch the current slot after the step, as the qualified Small path does.
  // The SyncReadMem ghist ports keep their registered-address PRE placement.
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r0", ftq_ram_port<0>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r1", ftq_ram_port<1>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r2", ftq_ram_port<2>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_ftq___v2_state_ram_r3", ftq_ram_port<3>},
  // This highest-priority LSU candidate is granted unchanged by schedule().
  // Publish the current edge's decision after Core::step, like the other
  // predicted combinational ports. It has no image-owned writer in Wide.
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_lsu_can_fire_load_incoming_0",
   [](const SystemGuider& m)->std::uint64_t {
     return m.backend().core().outputs().memory_ports.schedule.load_incoming;
   }},
  {"ldut_debug_1_dmInner_dmInner__T_1", [](const SystemGuider& m)->std::uint64_t {return m.debug().inner_dmactive_inactive;}},
#endif
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r2", rob_uop_port<2>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r3", rob_uop_port<3>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r4", rob_uop_port<4>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r5", rob_uop_port<5>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r6", rob_uop_port<6>},
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_uop_r7", rob_uop_port<7>},
#endif
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r0", rob_busy_port<0>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r1", rob_busy_port<1>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r3", rob_busy_port<3>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r4", rob_busy_port<4>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r5", rob_busy_port<5>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r6", rob_busy_port<6>},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r7", rob_busy_port<7>},
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_rob___v2_state_rob_bsy_r8", rob_busy_port<8>},
#endif
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_sdq_MPORT_3", sdq_port},
};
// TestHarness ties off the frontend AXI slave. Its queues and counters stay
// reset; the two-input AXI4ToTL arbiter mask resets to 3. Header-only cache
// acquires and one-beat IOMSHR requests cannot start a multi-beat A transfer.
constexpr Constant constants[] = {
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_beatsLeft", 0},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_dcache_mshrs_beatsLeft_1", 0},
  {"ldut_tile_prci_domain_tile_reset_domain_boom_tile_tlMasterXbar_beatsLeft", 0},
  {"ldut_subsystem_fbus_buffer_bundleIn_0_d_q_value_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_deq_ram__v2_bank_0_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_ram__v2_bank_0_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_1_ram__v2_bank_0_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_ram_data", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_addr", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_deq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_enq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_deq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_enq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_ram_extra_id_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_1_ram_real_last_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_ram_extra_id_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_2$$inst_ram_real_last_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_buffer_bundleIn_0_d_q_maybe_full", 0},
  {"ldut_subsystem_fbus_buffer_bundleIn_0_d_q_value", 0},
  {"ldut_subsystem_fbus_buffer_bundleOut_0_a_q_maybe_full", 0},
  {"ldut_subsystem_fbus_buffer_bundleOut_0_a_q_value_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_b_count_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_beatsLeft", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_deq_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_q_b_deq_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_q_b_deq_ram_id", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_r_count_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_r_count_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_readys_mask", 3},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_state_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_state_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_w_count_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi42tl_w_count_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_busy", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_busy_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_deq_1_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_in_w_deq_ram_strb", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_addr_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_len", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_r_len_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_w_counter", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4frag_wbeats_latched", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_deq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_enq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_deq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_enq_ptr_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_value_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_maybe_full", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_value", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_value_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_a_first_counter", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_flight__v2_bank_0_0", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_stalls_id", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_fixer_stalls_id_1", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_ram_extra_id_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility$$inst_ram_real_last_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_ram_extra_id_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_axi4yank_QueueCompatibility_3_ram_real_last_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_corrupt_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_data_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_denied_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_opcode_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_param_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_sink_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_size_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleIn_0_d_q_ram_source_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_address_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_corrupt_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_data_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_mask_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_opcode_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_param_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_size_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_source_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_bufferable_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_fetch_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_modifiable_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_privileged_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_readalloc_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_secure_io_deq_bits_MPORT", 0},
  {"ldut_subsystem_fbus_coupler_from_port_named_slave_port_axi4_buffer_bundleOut_0_a_q_ram_user_amba_prot_writealloc_io_deq_bits_MPORT", 0},
};
}
void register_wide_bindings() {
  static bool registered = false;
  if (registered) return;
  registered = true;
  auto& b = ModelBindings::instance();
  for (const auto& row : kSystemProbeManifest) {
    const CurrentPort* port = nullptr;
    for (const auto& p : current_ports) if (std::string_view(row.key) == p.key) { port = &p; break; }
    if (port) { b.bind(row.key, port->value); continue; }
    const Constant* constant = nullptr;
    for (const auto& c : constants) if (std::string_view(row.key) == c.key) { constant = &c; break; }
    if (constant) b.reserve_structural_constant(row.key, constant->value);
    else b.reserve_image_owned(row.key, row.kind == OracleKind::Combinational);
  }
}
void register_model_bindings() { register_wide_bindings(); }
void install_watch_dispatch(ModelBindings& b) {
  boom_model::wide::reset_publication_versions();
  // The memory-run lanes are published by the memory side itself
  // (SystemGuider::memory_pre_fabric / memory_commit_phase); the placements
  // only publish the core-run lanes of the End point.
  b.set_phase_prepare(SamplePlacement::End, boom_model::wide::publish_system_end_core);
}
}  // namespace chisa::boom_system
