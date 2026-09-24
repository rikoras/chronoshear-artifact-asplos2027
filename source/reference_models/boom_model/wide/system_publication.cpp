#include <cstdio>
#include <cstdlib>
#include "oracle_bindings.h"
#include "cold_record_fields.h"
#include "record_fields.h"
#include "frontend.h"
#include "../../boom-system/system_guider.h"
#include "../../boom-system/model_bindings.h"
#include "../common/diagnostic_monitor.h"
#include "diagnostics/record_dump.h"
namespace chisa::boom_model::wide {
using chisa::boom_system::SystemGuider;
namespace {
struct PublicationVersions {
  std::uint64_t system_bus = ~UINT64_C(0);
  std::uint64_t periphery_bus = ~UINT64_C(0);
  std::uint64_t coherent = ~UINT64_C(0);
  std::uint64_t mbus_memory = ~UINT64_C(0);
  std::uint64_t mmio_memory = ~UINT64_C(0);
  std::uint64_t ptw = ~UINT64_C(0);
  std::uint64_t fpu = ~UINT64_C(0);
  std::uint64_t fdivsqrt = ~UINT64_C(0);
  std::uint64_t dtlb_entries = ~UINT64_C(0);
  std::uint64_t debug_registers = ~UINT64_C(0);
#if defined(CHISA_MODEL_DIAGNOSTICS)
  std::uint64_t published_debug_data = 0;
#endif
} versions;
}
void reset_publication_versions() { versions = {}; }
void publish_system_early(const SystemGuider& m) {
  auto& I = system_record();
  const auto& mem = m.fabric().mbus_memory_oracles();
  const auto& coherent = m.fabric().coherent_memory_oracles();
  const auto& dcache = m.memory().dcache_for_diagnostic();
  (void)mem; (void)coherent; (void)dcache;
  if (versions.system_bus != m.fabric().system_bus_oracle_version()) {
    versions.system_bus = m.fabric().system_bus_oracle_version();
    write_record_columns<fields::system_bus_columns>(I,m.fabric().system_bus_oracles());
  }
  if (versions.periphery_bus != m.fabric().periphery_bus_oracle_version()) {
    versions.periphery_bus = m.fabric().periphery_bus_oracle_version();
    write_record_columns<fields::periphery_bus_columns>(I,m.fabric().periphery_bus_oracles());
  }
  if (versions.coherent != m.fabric().coherent_memory_oracle_version()) {
    versions.coherent = m.fabric().coherent_memory_oracle_version();
    for (unsigned queue=0;queue<32;++queue) {
      const auto& q=coherent.all_yank[queue];
      write_record(I,fields::yank_deq_ptr_value[queue],q.deq_ptr);
      write_record(I,fields::yank_enq_ptr_value[queue],q.enq_ptr);
      write_record(I,fields::yank_maybe_full[queue],q.maybe_full);
      write_record(I,fields::yank_ram_extra_id_io_deq_bits_MPORT[queue],q.extra_id);
      write_record(I,fields::yank_ram_tl_state_size_io_deq_bits_MPORT[queue],q.size);
      write_record(I,fields::yank_ram_tl_state_source_io_deq_bits_MPORT[queue],q.source);
    }
    I.r.uncoreMisc.plicDomainWrapper_plic_out_back_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().plic_out_back_maybe_full()) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_reg) & UINT64_C(0x1));
    if (m.cut_lanes()) {
      write_record(I, fields::l2_broadcast_reg_1, coherent.broadcast_reg_1);
      write_record(I, fields::l2_broadcast_reg_2, coherent.broadcast_reg_2);
      write_record(I, fields::l2_broadcast_counter, coherent.broadcast_counter);
      write_record(I, fields::l2_broadcast_r, coherent.broadcast_r);
    }
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_address = static_cast<std::uint32_t>(static_cast<std::uint64_t>(coherent.tracker_address) & UINT64_C(0xffffffff));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_count = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[0].count) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_got_e = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_got_e) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_o_data_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_o_maybe_full) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_o_data_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_o_enq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_o_data_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_o_deq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_opcode = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_opcode) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_sent_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_sent_d) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_shared = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[0].shared) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_size) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTrackerinst_source = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tracker_source) & UINT64_C(0x1f));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_address = static_cast<std::uint32_t>(static_cast<std::uint64_t>(coherent.trackers[1].address) & UINT64_C(0xffffffff));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_count = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].count) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_got_e = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].got_e) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_o_data_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].o_maybe_full) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_o_data_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].o_enq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_o_data_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].o_deq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_opcode = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].opcode) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_sent_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].sent_d) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_shared = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].shared) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].size) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_1inst_source = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[1].source) & UINT64_C(0x1f));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_address = static_cast<std::uint32_t>(static_cast<std::uint64_t>(coherent.trackers[2].address) & UINT64_C(0xffffffff));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_count = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].count) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_got_e = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].got_e) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_o_data_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].o_maybe_full) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_o_data_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].o_enq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_o_data_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].o_deq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_opcode = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].opcode) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_sent_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].sent_d) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_shared = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].shared) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].size) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_2inst_source = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[2].source) & UINT64_C(0x1f));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_address = static_cast<std::uint32_t>(static_cast<std::uint64_t>(coherent.trackers[3].address) & UINT64_C(0xffffffff));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_count = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].count) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_got_e = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].got_e) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_o_data_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].o_maybe_full) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_o_data_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].o_enq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_o_data_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].o_deq_ptr) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_opcode = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].opcode) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_sent_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].sent_d) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_shared = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].shared) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].size) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_TLBroadcastTracker_3inst_source = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.trackers[3].source) & UINT64_C(0x1f));
    I.r.uncoreL2.broadcast_1_beatsLeft = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_beats_left) & UINT64_C(0x7));
    I.r.uncoreL2.broadcast_1_beatsLeft_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_beats_left_1) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.uncoreL2.broadcast_1_counter_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_counter_2) & UINT64_C(0x7));
#endif
    I.r.uncoreL2.broadcast_1_state_1[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state_1_0) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state_1[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state_1_1) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state_1[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state_1_2) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state_1[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state_1_3) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state_1[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state_1_4) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state__0) & UINT64_C(0x1));
    I.r.uncoreL2.broadcast_1_state[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.broadcast_state__1) & UINT64_C(0x1));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_b_delay = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_b_delay) & UINT64_C(0x7));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_counter = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_counter) & UINT64_C(0x7));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_deq_maybe_full) & UINT64_C(0x1));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_deq_ram_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(coherent.tl2axi4_deq_data));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_deq_ram_strb = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_deq_strb) & UINT64_C(0xff));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_doneAW = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_done_aw) & UINT64_C(0x1));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_queue_arw_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_arw_maybe_full) & UINT64_C(0x1));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_r_holds_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_r_holds_d) & UINT64_C(0x1));
    I.c.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_GEN_257 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(coherent.tl2axi4_gen_257) & UINT64_C(0x1));
    I.r.uncoreMbus.coupler_to_memory_controller_port_named_axi4_tl2axi4_queue_arw_deq_rambank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(coherent.tl2axi4_arw_bank));
  }
  if (versions.mbus_memory != m.fabric().mbus_memory_oracle_version()) {
    versions.mbus_memory = m.fabric().mbus_memory_oracle_version();
    I.r.memAxi.axi4buf_bundleIn_0_b_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_b_maybe_full) & UINT64_C(0x1));
    if (m.cut_lanes()) {
      write_record(I, fields::mem_axi4buf_b_deq_value, mem.buf_b_enq_ptr);
      write_record(I, fields::mem_axi4buf_r_deq_value, mem.buf_r_enq_ptr);
    }
    I.r.memAxi.axi4buf_bundleIn_0_b_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_b_deq_ptr) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleIn_0_r_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_maybe_full) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleIn_0_r_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_deq_ptr) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.memAxi.axi4buf_bundleOut_0_ar_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_ar_maybe_full) & UINT64_C(0x1));
#endif
    I.r.memAxi.axi4buf_bundleOut_0_ar_deq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_ar_enq_ptr) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleOut_0_ar_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_ar_deq_ptr) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleOut_0_aw_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_aw_maybe_full) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleOut_0_aw_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_aw_deq_ptr) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleOut_0_w_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_w_maybe_full) & UINT64_C(0x1));
    I.r.memAxi.axi4buf_bundleOut_0_w_deq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_w_enq_ptr) & UINT64_C(0x1));
    I.r.memAxi.axi4frag_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_deq_maybe_full) & UINT64_C(0x1));
    I.r.memAxi.axi4frag_deq_1_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_deq_1_maybe_full) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.memAxi.axi4frag_in_w_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_in_w_maybe_full) & UINT64_C(0x1));
#endif
    I.r.memAxi.axi4frag_in_w_deq_ram_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(mem.frag_in_w_data));
    I.r.memAxi.axi4frag_in_w_deq_ram_strb = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_in_w_strb) & UINT64_C(0xff));
    I.r.memAxi.axi4frag_r_addr = static_cast<std::uint32_t>(static_cast<std::uint64_t>(mem.frag_r_addr) & UINT64_C(0xffffffff));
    I.r.memAxi.axi4frag_r_addr_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(mem.frag_r_addr_1) & UINT64_C(0xffffffff));
    I.r.memAxi.axi4frag_r_len = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_r_len) & UINT64_C(0xff));
    I.r.memAxi.axi4frag_r_len_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_r_len_1) & UINT64_C(0xff));
    I.r.memAxi.axi4frag_w_counter = static_cast<std::uint16_t>(static_cast<std::uint64_t>(mem.frag_w_counter) & UINT64_C(0x1ff));
    I.r.memAxi.axi4frag_wbeats_latched = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.frag_wbeats_latched) & UINT64_C(0x1));
    I.r.memAxi.srams_r_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.ram_r_full) & UINT64_C(0x1));
    I.r.memAxi.srams_r_id = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.ram_r_id) & UINT64_C(0xf));
    I.r.memAxi.srams_w_echo_real_last = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.ram_w_echo_real_last) & UINT64_C(0x1));
    I.r.memAxi.srams_w_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.ram_w_full) & UINT64_C(0x1));
    I.r.memAxi.srams_w_id = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.ram_w_id) & UINT64_C(0xf));
    I.c.memAxi.axi4buf_bundleIn_0_b_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_b_echo_real_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleIn_0_b_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_b_id) & UINT64_C(0xf));
    I.c.memAxi.axi4buf_bundleIn_0_b_deq_ram_resp_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_b_resp) & UINT64_C(0x3));
    I.c.memAxi.axi4buf_bundleIn_0_r_deq_ram_data_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(mem.buf_r_data));
    I.c.memAxi.axi4buf_bundleIn_0_r_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_echo_real_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleIn_0_r_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_id) & UINT64_C(0xf));
    I.c.memAxi.axi4buf_bundleIn_0_r_deq_ram_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleIn_0_r_deq_ram_resp_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_r_resp) & UINT64_C(0x3));
    I.c.memAxi.axi4buf_bundleOut_0_ar_deq_ram_addr_io_deq_bits_MPORT = static_cast<std::uint32_t>(static_cast<std::uint64_t>(mem.buf_ar_addr) & UINT64_C(0xffffffff));
    I.c.memAxi.axi4buf_bundleOut_0_ar_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_ar_echo_real_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleOut_0_ar_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_ar_id) & UINT64_C(0xf));
    I.c.memAxi.axi4buf_bundleOut_0_aw_deq_ram_addr_io_deq_bits_MPORT = static_cast<std::uint32_t>(static_cast<std::uint64_t>(mem.buf_aw_addr) & UINT64_C(0xffffffff));
    I.c.memAxi.axi4buf_bundleOut_0_aw_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_aw_echo_real_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleOut_0_aw_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_aw_id) & UINT64_C(0xf));
    I.c.memAxi.axi4buf_bundleOut_0_w_deq_ram_data_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(mem.buf_w_data));
    I.c.memAxi.axi4buf_bundleOut_0_w_deq_ram_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_w_last) & UINT64_C(0x1));
    I.c.memAxi.axi4buf_bundleOut_0_w_deq_ram_strb_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(mem.buf_w_strb) & UINT64_C(0xff));
    I.r.memAxi.axi4frag_busy = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mbus_memory_oracles().frag_busy) & UINT64_C(0x1));
    I.r.memAxi.axi4frag_busy_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mbus_memory_oracles().frag_busy_1) & UINT64_C(0x1));
    I.r.memAxi.axi4frag_deq_rambank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mbus_memory_oracles().frag_deq_bank) & UINT64_C(0x1ffffffffffff));
    I.r.memAxi.axi4frag_deq_1_rambank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mbus_memory_oracles().frag_deq_1_bank) & UINT64_C(0x1ffffffffffff));
  }
  if (versions.mmio_memory != m.fabric().mmio_memory_oracle_version()) {
    versions.mmio_memory = m.fabric().mmio_memory_oracle_version();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.mmioAxi.axi4buf_bundleIn_0_b_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_maybe_full) & UINT64_C(0x1));
#endif
    I.r.mmioAxi.axi4buf_bundleIn_0_b_deq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_enq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleIn_0_b_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_deq_ptr) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.mmioAxi.axi4buf_bundleIn_0_r_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_maybe_full) & UINT64_C(0x1));
#endif
    I.r.mmioAxi.axi4buf_bundleIn_0_r_deq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_enq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleIn_0_r_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_deq_ptr) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.mmioAxi.axi4buf_bundleOut_0_ar_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_maybe_full) & UINT64_C(0x1));
#endif
    I.r.mmioAxi.axi4buf_bundleOut_0_ar_deq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_enq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleOut_0_ar_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_deq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleOut_0_aw_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_aw_maybe_full) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleOut_0_aw_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_aw_deq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4buf_bundleOut_0_w_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_w_maybe_full) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_deq_maybe_full) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_deq_1_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_deq_1_maybe_full) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_in_w_deq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_in_w_maybe_full) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_in_w_deq_ram_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_in_w_data));
    I.r.mmioAxi.axi4frag_in_w_deq_ram_strb = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_in_w_strb) & UINT64_C(0xff));
    I.r.mmioAxi.axi4frag_r_addr = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_r_addr) & UINT64_C(0x7fffffff));
    I.r.mmioAxi.axi4frag_r_addr_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_r_addr_1) & UINT64_C(0x7fffffff));
    I.r.mmioAxi.axi4frag_r_len = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_r_len) & UINT64_C(0xff));
    I.r.mmioAxi.axi4frag_r_len_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_r_len_1) & UINT64_C(0xff));
    I.r.mmioAxi.axi4frag_w_counter = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_w_counter) & UINT64_C(0x1ff));
    I.r.mmioAxi.axi4frag_wbeats_latched = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_wbeats_latched) & UINT64_C(0x1));
    I.r.mmioAxi.srams_r_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().ram_r_full) & UINT64_C(0x1));
    I.r.mmioAxi.srams_r_id = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().ram_r_id) & UINT64_C(0xf));
    I.r.mmioAxi.srams_w_echo_real_last = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().ram_w_echo_real_last) & UINT64_C(0x1));
    I.r.mmioAxi.srams_w_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().ram_w_full) & UINT64_C(0x1));
    I.r.mmioAxi.srams_w_id = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().ram_w_id) & UINT64_C(0xf));
    I.c.mmioAxi.axi4buf_bundleIn_0_b_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_echo_real_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleIn_0_b_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_id) & UINT64_C(0xf));
    I.c.mmioAxi.axi4buf_bundleIn_0_b_deq_ram_resp_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_b_resp) & UINT64_C(0x3));
    I.c.mmioAxi.axi4buf_bundleIn_0_r_deq_ram_data_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_data));
    I.c.mmioAxi.axi4buf_bundleIn_0_r_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_echo_real_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleIn_0_r_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_id) & UINT64_C(0xf));
    I.c.mmioAxi.axi4buf_bundleIn_0_r_deq_ram_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleIn_0_r_deq_ram_resp_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_r_resp) & UINT64_C(0x3));
    I.c.mmioAxi.axi4buf_bundleOut_0_ar_deq_ram_addr_io_deq_bits_MPORT = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_addr) & UINT64_C(0x7fffffff));
    I.c.mmioAxi.axi4buf_bundleOut_0_ar_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_echo_real_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleOut_0_ar_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_ar_id) & UINT64_C(0xf));
    I.c.mmioAxi.axi4buf_bundleOut_0_aw_deq_ram_addr_io_deq_bits_MPORT = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_aw_addr) & UINT64_C(0x7fffffff));
    I.c.mmioAxi.axi4buf_bundleOut_0_aw_deq_ram_echo_real_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_aw_echo_real_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleOut_0_aw_deq_ram_id_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_aw_id) & UINT64_C(0xf));
    I.c.mmioAxi.axi4buf_bundleOut_0_w_deq_ram_data_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_w_data));
    I.c.mmioAxi.axi4buf_bundleOut_0_w_deq_ram_last_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_w_last) & UINT64_C(0x1));
    I.c.mmioAxi.axi4buf_bundleOut_0_w_deq_ram_strb_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_w_strb) & UINT64_C(0xff));
    I.r.mmioAxi.axi4buf_bundleOut_0_w_deq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().buf_w_deq_ptr) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_busy = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_busy) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_busy_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_busy_1) & UINT64_C(0x1));
    I.r.mmioAxi.axi4frag_deq_rambank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_deq_bank) & UINT64_C(0xffffffffffff));
    I.r.mmioAxi.axi4frag_deq_1_rambank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().mmio_memory_oracles().frag_deq_1_bank) & UINT64_C(0xffffffffffff));
  }
}
// The memory side (memory_side) writes the memory-run lanes: D-cache, MSHRs,
// uncore, PTW, debug registers.  The calling thread (core_side) writes the
// core-run ones: the LSU's registered DTLB miss-ready bits and hella state,
// the DTLB entries, the FPU and FDivSqrt sidecars.  With a memory worker the
// two halves run on different threads (see SystemGuider::MemoryWorker).
static void publish_system_end_impl(const SystemGuider& m, bool memory_side, bool core_side) {
  auto& I = system_record();
  const auto& mem = m.fabric().mbus_memory_oracles();
  const auto& coherent = m.fabric().coherent_memory_oracles();
  const auto& dcache = m.memory().dcache_for_diagnostic();
  (void)mem; (void)coherent; (void)dcache;
  if (memory_side) { // SYSMODEL_TRACE_DCACHE=lo:hi prints the write-back unit, prober and MSHRs per cycle (diagnostic only)
    static const char* trace_spec = std::getenv("SYSMODEL_TRACE_DCACHE");
    static unsigned long long trace_lo = 0, trace_hi = 0;
    static bool trace_parsed = false;
    if (trace_spec && !trace_parsed) { trace_parsed = true; std::sscanf(trace_spec, "%llu:%llu", &trace_lo, &trace_hi); }
    if (trace_spec && m.cycle() >= trace_lo && m.cycle() <= trace_hi) {
      const auto& wb = dcache.writeback_for_diagnostic();
      const auto& pr = dcache.prober_for_diagnostic();
      std::fprintf(stderr, "DCTRACE cyc=%llu wb{st=%d probe=%d addr=%08x owner=%u rc=%u rb=%u acked=%d} prober{st=%d req=%08x hit=%d}",
                   (unsigned long long)m.cycle(), int(wb.state), int(wb.probe), unsigned(wb.address), unsigned(wb.owner),
                   unsigned(wb.read_count), unsigned(wb.release_beat), int(wb.acked), int(pr.state), unsigned(pr.request.address), int(pr.lookup.hit));
      for (unsigned k = 0; k < 4; ++k) {
        const auto& ms = dcache.mshr_for_diagnostic(k);
        std::fprintf(stderr, " m%u{st=%d addr=%08x}", k, int(ms.state), unsigned(ms.request.address));
      }
      std::fprintf(stderr, " arbc=%u arba=%u iom=%d s2type=%u s2way=%02x\n", unsigned(dcache.arbiter_c_state_oracle()),
                   unsigned(dcache.arbiter_a_state_oracle()), int(m.memory().debug_path_for_diagnostic().iomshr_state_now()),
                   unsigned(dcache.oracle_s2_type()), unsigned(dcache.s2_tag_match_way_oracle()));
    }
  }
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  // Only these record-member spellings are specific to Medium. The cut
  // fields below describe hardware shared with Large and must be published
  // for every configuration whose contract retains them.
  if (memory_side) {
  I.r.dcache.REG_10=dcache.s2_replacement_way_oracle();I.r.dcache.REG_15=dcache.s2_send_shadow_oracle();
  I.r.dcache.prober_req_param=dcache.prober_for_diagnostic().request.param;
  I.r.dcacheMshrs.mmios_0_req_data=m.memory().debug_path_for_diagnostic().iomshr_active_oracle().data;
  I.c.dcacheMshrs.lb_MPORT_2=dcache.line_buffer_port_oracle();
  for (unsigned beat=4;beat<8;++beat) I.r.dcache.wb_wb_buffer[beat]=dcache.writeback_buffer_lane_oracle(beat,0);
  for (unsigned mshr=0;mshr<boomcfg::DCACHE_MSHRS;++mshr)
    I.r.dcacheMshrs.mshrs_rpq_uops_15_br_mask[mshr]=dcache.mshr_for_diagnostic(mshr).rpq[15].request.br_mask;
  }
#endif
  if (memory_side && m.cut_lanes()) { // MSHRs, response queue, prober and write-back unit
    for (unsigned i=0;i<boomcfg::DCACHE_MSHRS;++i)
      write_record(I, fields::dcache_mshr_grant_sink[i], dcache.mshr_for_diagnostic(i).grant_sink);
    for (unsigned i=0;i<4;++i) {
      const auto& c=dcache.respq_completion_oracle(i);
      write_record(I, fields::dcache_respq_uop_ldq_idx[i], c.ldq_idx);
      write_record(I, fields::dcache_respq_uop_stq_idx[i], c.stq_idx);
      write_record(I, fields::dcache_respq_uop_is_amo[i], c.is_amo);
      write_record(I, fields::dcache_respq_uop_uses_ldq[i], c.uses_ldq);
      write_record(I, fields::dcache_respq_uop_uses_stq[i], c.uses_stq);
    }
    // dcache.scala 171-173: the probe unit latches the matched way and its
    // coherence state (Nothing/Branch/Trunk/Dirty) at the metadata response.
    const auto& lookup=dcache.prober_for_diagnostic().lookup;
    write_record(I, fields::dcache_prober_old_coh_state, !lookup.hit ? 0u : lookup.dirty ? 3u : lookup.writable ? 2u : 1u);
    write_record(I, fields::dcache_prober_way_en, lookup.hit ? (1u<<lookup.way) : 0u);
    // dcache.scala 85: the write-back unit's request register.
    const auto& wb=dcache.writeback_for_diagnostic();
    write_record(I, fields::dcache_wb_req_idx, (wb.address>>6)&0x3fu);
    write_record(I, fields::dcache_wb_req_param, wb.probe ? wb.probe_param : 1u);
    write_record(I, fields::dcache_wb_req_voluntary, !wb.probe);
    // dcache.scala: the store pipeline's s3/s4/s5 request registers.
    write_record(I, fields::dcache_s3_valid, dcache.s3_valid_oracle());
    write_record(I, fields::dcache_s3_req_addr, dcache.s3_req_addr_oracle());
    write_record(I, fields::dcache_s3_req_data, dcache.s3_req_data_oracle());
    write_record(I, fields::dcache_s4_valid, dcache.s4_valid_oracle());
    write_record(I, fields::dcache_s4_req_addr, dcache.s4_req_addr_oracle());
    write_record(I, fields::dcache_s5_valid, dcache.s5_valid_oracle());
    write_record(I, fields::dcache_s5_req_addr, dcache.s5_req_addr_oracle());
    write_record(I, fields::dcache_s5_req_data, dcache.s5_req_data_oracle());
    for (unsigned i = 0; i < boomcfg::DCACHE_MSHRS+1; ++i) write_record(I, fields::dcache_mshr_arb_a_state[i], (dcache.arbiter_a_state_oracle() >> i) & 1u);
    for (unsigned i = 0; i < boomcfg::DCACHE_MSHRS; ++i) write_record(I, fields::dcache_mshr_arb_e_state[i], (dcache.arbiter_e_state_oracle() >> i) & 1u);
    for (unsigned i = 0; i < 2; ++i) write_record(I, fields::dcache_arb_c_state[i], (dcache.arbiter_c_state_oracle() >> i) & 1u);
    write_record(I, fields::dcache_s1_nack_r, dcache.s2_nack_hit_oracle());
    write_record(I, fields::dcache_s1_req_is_hella, dcache.s1_req_is_hella_oracle());
    write_record(I, fields::dcache_mmio_req_data, m.memory().debug_path_for_diagnostic().iomshr_active_oracle().data);
  }
  if (core_side && m.cut_lanes()) { // the DTLB is the calling thread's
    write_record(I, fields::lsu_dtlb_r_sectored_hit, m.dtlb().sectored_hit());
    write_record(I, fields::lsu_dtlb_r_sectored_hit_addr, m.dtlb().sectored_hit_address());
    write_record(I, fields::lsu_dtlb_r_sectored_repl_addr, m.dtlb().sectored_replacement_address());
    write_record(I, fields::lsu_dtlb_state, static_cast<std::uint8_t>(m.dtlb().state()));
  }
  if (memory_side) { // memory
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.uncoreTile.buffer_1_bundleIn_0_b_q_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().b_queue_for_diagnostic().maybe_full()) & UINT64_C(0x1));
#endif
    I.r.uncoreTile.buffer_1_bundleIn_0_b_q_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().b_queue_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleIn_0_b_q_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().b_queue_for_diagnostic().deq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleIn_0_d_q_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().d_queue_for_diagnostic().maybe_full()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleIn_0_d_q_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().d_queue_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleIn_0_d_q_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().d_queue_for_diagnostic().deq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_a_q_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().a_queue_for_diagnostic().maybe_full()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_a_q_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().a_queue_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_a_q_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().a_queue_for_diagnostic().deq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_c_q_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().c_queue_for_diagnostic().maybe_full()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_c_q_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().c_queue_for_diagnostic().deq_ptr()) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.uncoreTile.buffer_1_bundleOut_0_e_q_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().e_queue_for_diagnostic().maybe_full()) & UINT64_C(0x1));
#endif
    I.r.uncoreTile.buffer_1_bundleOut_0_e_q_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().e_queue_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_e_q_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().e_queue_for_diagnostic().deq_ptr()) & UINT64_C(0x1));
    I.r.dcache.REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s1_valid_oracle() ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcache.REG_3 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_valid_oracle() ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcache.REG_4_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_coh_reg(0)) & UINT64_C(0x3));
    I.r.dcache.REG_5_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_coh_reg(1)) & UINT64_C(0x3));
    I.r.dcache.REG_6_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_coh_reg(2)) & UINT64_C(0x3));
    I.r.dcache.REG_7_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_coh_reg(3)) & UINT64_C(0x3));
    I.r.dcache.lfsr_prng_state_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>((m.memory().dcache_for_diagnostic().lfsr_for_diagnostic() & 1u)) & UINT64_C(0x1));
    I.r.dcacheMshrs.mmios_0_req_addr = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().address) & UINT64_C(0xffffffffff));
    I.r.dcacheMshrs.mmios_0_req_uop_is_amo = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().is_amo) & UINT64_C(0x1));
    I.r.dcacheMshrs.mmios_0_req_uop_mem_cmd = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().command) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mmios_0_req_uop_mem_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().size) & UINT64_C(0x3));
    I.r.dcacheMshrs.mmios_0_req_uop_uses_ldq = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().uses_ldq) & UINT64_C(0x1));
    I.r.dcacheMshrs.mmios_0_req_uop_uses_stq = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().uses_stq) & UINT64_C(0x1));
    I.r.dcacheMshrs.mmios_0_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_state_oracle()) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_grantack_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(0).grant_ack_valid ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_new_coh_state[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_new_coh_oracle(0)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_addr[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).request.address) & UINT64_C(0xffffffffff));
    I.r.dcacheMshrs.mshrs_req_old_meta_coh_state[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_old_meta_coh_oracle(0)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_uop_mem_cmd[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).request.command) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_rpq_maybe_full[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).rpq_maybe_full) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_0_rpq_uopsbank_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_oracle(0, 0)));
    I.r.dcacheMshrs.mshrs_0_rpq_uopsbank_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_oracle(0, 1)));
    I.r.dcacheMshrs.mshrs_rpq_validsbank_0_0[0] = static_cast<std::uint16_t>(static_cast<std::uint64_t>(chisa::boom_system::rpq_valids_bank_live(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0))) & UINT64_C(0xffff));
    I.r.dcacheMshrs.mshrs_rpq_value[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).rpq_tail) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_rpq_value_1[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).rpq_head) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_state[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).state) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_grantack_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(1).grant_ack_valid ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_new_coh_state[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_new_coh_oracle(1)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_addr[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).request.address) & UINT64_C(0xffffffffff));
    I.r.dcacheMshrs.mshrs_req_old_meta_coh_state[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_old_meta_coh_oracle(1)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_uop_mem_cmd[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).request.command) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_rpq_maybe_full[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).rpq_maybe_full) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_1_rpq_uopsbank_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_oracle(1, 0)));
    I.r.dcacheMshrs.mshrs_1_rpq_uopsbank_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_oracle(1, 1)));
    I.r.dcacheMshrs.mshrs_rpq_validsbank_0_0[1] = static_cast<std::uint16_t>(static_cast<std::uint64_t>(chisa::boom_system::rpq_valids_bank_live(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1))) & UINT64_C(0xffff));
    I.r.dcacheMshrs.mshrs_rpq_value[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).rpq_tail) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_rpq_value_1[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).rpq_head) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_state[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).state) & UINT64_C(0x1f));
    I.r.dcacheMshrs.respq_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().respq_maybe_full_oracle()) & UINT64_C(0x1));
    I.r.dcacheMshrs.respq_validsbank_0_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().respq_valids_oracle()) & UINT64_C(0xf));
    I.r.dcacheMshrs.respq_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().respq_enq_oracle()) & UINT64_C(0x3));
    I.r.dcacheMshrs.respq_value_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().respq_deq_oracle()) & UINT64_C(0x3));
    I.r.dcacheMshrs.sdq_val = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().sdq_val_oracle()) & UINT64_C(0x1ffff));
    I.r.dcache.prober_req_address = static_cast<std::uint32_t>(static_cast<std::uint64_t>(dcache.prober_for_diagnostic().request.address) & UINT64_C(0xffffffff));
    I.r.dcache.prober_req_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.prober_for_diagnostic().request.size) & UINT64_C(0xf));
    I.r.dcache.prober_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.prober_for_diagnostic().state) & UINT64_C(0xf));
    I.r.dcache.s2_req_0_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().data));
    I.r.dcache.s2_req_0_is_hella = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().is_hella ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcache.s2_req_0_uop_is_amo = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().is_amo) & UINT64_C(0x1));
    I.r.dcache.s2_req_0_uop_mem_cmd = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().command & 0x1fu) & UINT64_C(0x1f));
    I.r.dcache.s2_req_0_uop_mem_signed = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().is_signed ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcache.s2_req_0_uop_mem_size = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().size & 3u) & UINT64_C(0x3));
    I.r.dcache.s2_req_0_uop_uses_ldq = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().bus_s2_oracle().uses_ldq) & UINT64_C(0x1));
    I.r.dcache.s2_req_0_uop_uses_stq = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().uses_stq ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcache.s2_type = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_s2_type()) & UINT64_C(0x7));
    I.r.dcache.wb_req_tag = static_cast<std::uint32_t>(static_cast<std::uint64_t>((m.memory().dcache_for_diagnostic().writeback_for_diagnostic().address >> 12)) & UINT64_C(0xfffff));
    I.r.dcache.wb_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().writeback_for_diagnostic().state) & UINT64_C(0x7));
    I.r.xbar.readys_mask = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.axi_mirror().tlmx_readys_mask) & UINT64_C(0x3));
    I.r.xbar.state[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.axi_mirror().tlmx_state_0) & UINT64_C(0x1));
    I.r.xbar.state[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.axi_mirror().tlmx_state_1) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.c.dcache.data_array_0_0_0_MPORT_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(0)));
#else
    I.c.dcache.data_array_0_0_MPORT_1[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(0)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.c.dcache.data_array_1_0_0_MPORT_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(1)));
#else
    I.c.dcache.data_array_1_0_MPORT_3[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.c.dcache.data_array_2_0_0_MPORT_5 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(2)));
#else
    I.c.dcache.data_array_2_0_MPORT_5[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(2)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.c.dcache.data_array_3_0_0_MPORT_7 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(3)));
#else
    I.c.dcache.data_array_3_0_MPORT_7[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_data_port(3)));
#endif
    I.c.dcache.meta_0_tag_array_0_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_tag_port(0)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_1_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_tag_port(1)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_2_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_tag_port(2)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_3_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().oracle_tag_port(3)) & UINT64_C(0x3fffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_addr_MPORT_1[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).rpq[m.memory().dcache_for_diagnostic().mshr_for_diagnostic(0).rpq_head].request.address) & UINT64_C(0xffffffffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_is_hella_MPORT_1[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.rpq_is_hella_port_oracle(0) ? 1u : 0u) & UINT64_C(0x1));
    I.c.dcacheMshrs.mshrs_rpq_ram_sdq_id_MPORT_1[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(0).rpq_sdq_id[dcache.mshr_for_diagnostic(0).rpq_head]) & UINT64_C(0x1f));
    I.c.dcacheMshrs.mshrs_rpq_ram_addr_MPORT_1[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).rpq[m.memory().dcache_for_diagnostic().mshr_for_diagnostic(1).rpq_head].request.address) & UINT64_C(0xffffffffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_is_hella_MPORT_1[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.rpq_is_hella_port_oracle(1) ? 1u : 0u) & UINT64_C(0x1));
    I.c.dcacheMshrs.mshrs_rpq_ram_sdq_id_MPORT_1[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(1).rpq_sdq_id[dcache.mshr_for_diagnostic(1).rpq_head]) & UINT64_C(0x1f));
    I.c.dcacheMshrs.respq_ram_data_MPORT_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().respq_head_data_oracle()));
    I.c.dcacheMshrs.respq_ram_is_hella_MPORT_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.respq_is_hella_port_oracle() ? 1u : 0u) & UINT64_C(0x1));
    I.r.uncoreTile.buffer_1_bundleOut_0_c_q_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().fabric_for_diagnostic().c_queue_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.REG_10_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.oracle_coh_reg(6)) & UINT64_C(0x3));
    I.r.dcache.REG_11_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.oracle_coh_reg(7)) & UINT64_C(0x3));
    I.r.dcache.REG_14 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_replacement_way_oracle()) & UINT64_C(0x7));
    I.r.dcache.REG_23 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_send_shadow_oracle()) & UINT64_C(0x1));
    I.r.dcache.REG_8_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.oracle_coh_reg(4)) & UINT64_C(0x3));
    I.r.dcache.REG_9_state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.oracle_coh_reg(5)) & UINT64_C(0x3));
#endif
    I.r.dcache.beatsLeft = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.writeback_beats_left_oracle()) & UINT64_C(0xff));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.data_REG = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(0,0)));
#else
    I.r.dcache.data_REG_1[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(0,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.data_REG_2[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(0,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.data_REG_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(1,0)));
#else
    I.r.dcache.data_REG_1[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(1,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.data_REG_1[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(1,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.data_REG_2 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(2,0)));
#else
    I.r.dcache.data_REG_2[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(2,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.data_REG_2[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(2,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.data_REG_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(3,0)));
#else
    I.r.dcache.data_REG_3[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(3,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.data_REG_3[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(3,1)));
    I.r.dcache.data_REG_4[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(4,0)));
    I.r.dcache.data_REG_4[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(4,1)));
    I.r.dcache.data_REG_5[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(5,0)));
    I.r.dcache.data_REG_5[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(5,1)));
    I.r.dcache.data_REG_6[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(6,0)));
    I.r.dcache.data_REG_6[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(6,1)));
    I.r.dcache.data_REG_7[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(7,0)));
    I.r.dcache.data_REG_7[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_reg_lane(7,1)));
#endif
    I.r.dcacheMshrs.REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_alloc_index_oracle()) & UINT64_C(0x3));
    I.r.dcacheMshrs.mmios_0_req_uop_ldq_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().ldq_idx) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mmios_0_req_uop_stq_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().debug_path_for_diagnostic().iomshr_active_oracle().stq_idx) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_req_way_en[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(0).way_en) & UINT64_C(0xff));
    I.r.dcacheMshrs.mshrs_req_way_en[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(1).way_en) & UINT64_C(0xff));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcacheMshrs.mshrs_grantack_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(2).grant_ack_valid ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_new_coh_state[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_new_coh_oracle(2)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_addr[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).request.address) & UINT64_C(0xffffffffff));
    I.r.dcacheMshrs.mshrs_req_old_meta_coh_state[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_old_meta_coh_oracle(2)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_uop_mem_cmd[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).request.command) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_req_way_en[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(2).way_en) & UINT64_C(0xff));
    I.r.dcacheMshrs.mshrs_rpq_maybe_full[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).rpq_maybe_full) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_rpq_validsbank_0_0[2] = static_cast<std::uint16_t>(static_cast<std::uint64_t>(chisa::boom_system::rpq_valids_bank_live(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2))) & UINT64_C(0xffff));
    I.r.dcacheMshrs.mshrs_rpq_value[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).rpq_tail) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_rpq_value_1[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).rpq_head) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_state[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).state) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_grantack_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(3).grant_ack_valid ? 1u : 0u) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_new_coh_state[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_new_coh_oracle(3)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_addr[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).request.address) & UINT64_C(0xffffffffff));
    I.r.dcacheMshrs.mshrs_req_old_meta_coh_state[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_old_meta_coh_oracle(3)) & UINT64_C(0x3));
    I.r.dcacheMshrs.mshrs_req_uop_mem_cmd[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).request.command) & UINT64_C(0x1f));
    I.r.dcacheMshrs.mshrs_req_way_en[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(3).way_en) & UINT64_C(0xff));
    I.r.dcacheMshrs.mshrs_rpq_maybe_full[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).rpq_maybe_full) & UINT64_C(0x1));
    I.r.dcacheMshrs.mshrs_rpq_validsbank_0_0[3] = static_cast<std::uint16_t>(static_cast<std::uint64_t>(chisa::boom_system::rpq_valids_bank_live(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3))) & UINT64_C(0xffff));
    I.r.dcacheMshrs.mshrs_rpq_value[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).rpq_tail) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_rpq_value_1[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).rpq_head) & UINT64_C(0xf));
    I.r.dcacheMshrs.mshrs_state[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).state) & UINT64_C(0x1f));
#endif
    I.r.dcache.prober_req_source = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.prober_for_diagnostic().request.source) & UINT64_C(0x7));
    I.r.dcache.s2_nack_hit_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_nack_hit_oracle()) & UINT64_C(0x1));
    I.r.dcache.s2_req_0_addr = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().address) & UINT64_C(0xffffffffff));
    I.r.dcache.s2_req_0_uop_br_mask = static_cast<std::uint16_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().br_mask) & UINT64_C(0xffff));
    I.r.dcache.s2_req_0_uop_ldq_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().ldq_idx) & UINT64_C(0x1f));
    I.r.dcache.s2_req_0_uop_stq_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.bus_s2_oracle().stq_idx) & UINT64_C(0x1f));
    I.r.dcache.s2_tag_match_way_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_tag_match_way_oracle()) & UINT64_C(0xff));
    I.r.dcache.s2_wb_idx_matches_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.s2_wb_idx_match_oracle()) & UINT64_C(0x1));
    I.r.dcache.s4_req_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.s4_req_data_oracle()));
    // The request counter includes the exhausted sentinel: eight beats need
    // four bits on Medium, while Large's four beats need three bits.
    I.r.dcache.wb_data_req_cnt = static_cast<std::uint8_t>(
        dcache.writeback_for_diagnostic().read_count & (2u * boomcfg::DCACHE_REFILL_BEATS - 1u));
    CHISA_DIAG(
      const auto& wb = dcache.writeback_for_diagnostic();
      chisa::diagnostic::require("dcache", "wb-counter-native-range", m.cycle(),
          chisa::diagnostic::Layer::Internal, chisa::diagnostic::Phase::Post,
          wb.read_count <= boomcfg::DCACHE_REFILL_BEATS,
          {{"count", wb.read_count}, {"beats", boomcfg::DCACHE_REFILL_BEATS},
           {"state", static_cast<std::uint64_t>(wb.state)}});
      chisa::diagnostic::require("dcache", "wb-counter-publication", m.cycle(),
          chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
          I.r.dcache.wb_data_req_cnt == wb.read_count,
          {{"native", wb.read_count}, {"published", I.r.dcache.wb_data_req_cnt},
           {"beats", boomcfg::DCACHE_REFILL_BEATS}, {"state", static_cast<std::uint64_t>(wb.state)},
           {"record_offset", offsetof(contract::Image, r.dcache.wb_data_req_cnt)}});
      for (unsigned index = 0; index < boomcfg::DCACHE_MSHRS; ++index) {
        const auto state = static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(index).state);
        chisa::diagnostic::require("dcache", "mshr-state-publication", m.cycle(),
            chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
            state < 32 && I.r.dcacheMshrs.mshrs_state[index] == state,
            {{"index", index}, {"native", state}, {"published", I.r.dcacheMshrs.mshrs_state[index]},
             {"mshrs", boomcfg::DCACHE_MSHRS}});
      }
    );
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.wb_wb_buffer[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(0,0)));
#else
    I.r.dcache.wb_wb_buffer_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(0,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.wb_wb_buffer_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(0,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.wb_wb_buffer[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(1,0)));
#else
    I.r.dcache.wb_wb_buffer_1[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(1,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.wb_wb_buffer_1[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(1,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.wb_wb_buffer[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(2,0)));
#else
    I.r.dcache.wb_wb_buffer_2[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(2,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.wb_wb_buffer_2[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(2,1)));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    I.r.dcache.wb_wb_buffer[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(3,0)));
#else
    I.r.dcache.wb_wb_buffer_3[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(3,0)));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcache.wb_wb_buffer_3[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.writeback_buffer_lane_oracle(3,1)));
#endif
  }
  if (core_side) {
    I.r.lsu.REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb_miss_ready_registered()) & UINT64_C(0x1));
    I.r.lsu.REG_1 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb_miss_ready_registered()) & UINT64_C(0x1));
    I.r.lsu.hella_state = m.backend().hella_state_oracle() & 7u;
  }
  if (memory_side) {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.c.dcache.data_array_0_0_MPORT_1[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(0,1)));
    I.c.dcache.data_array_1_0_MPORT_3[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(1,1)));
    I.c.dcache.data_array_2_0_MPORT_5[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(2,1)));
    I.c.dcache.data_array_3_0_MPORT_7[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(3,1)));
    I.c.dcache.data_array_4_0_MPORT_9[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(4,0)));
    I.c.dcache.data_array_4_0_MPORT_9[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(4,1)));
    I.c.dcache.data_array_5_0_MPORT_11[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(5,0)));
    I.c.dcache.data_array_5_0_MPORT_11[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(5,1)));
    I.c.dcache.data_array_6_0_MPORT_13[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(6,0)));
    I.c.dcache.data_array_6_0_MPORT_13[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(6,1)));
    I.c.dcache.data_array_7_0_MPORT_15[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(7,0)));
    I.c.dcache.data_array_7_0_MPORT_15[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.oracle_data_port_lane(7,1)));
    I.c.dcache.meta_0_tag_array_4_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(dcache.oracle_tag_port(4)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_5_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(dcache.oracle_tag_port(5)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_6_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(dcache.oracle_tag_port(6)) & UINT64_C(0x3fffff));
    I.c.dcache.meta_0_tag_array_7_MPORT_1 = static_cast<std::uint32_t>(static_cast<std::uint64_t>(dcache.oracle_tag_port(7)) & UINT64_C(0x3fffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_addr_MPORT_1[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).rpq[m.memory().dcache_for_diagnostic().mshr_for_diagnostic(2).rpq_head].request.address) & UINT64_C(0xffffffffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_is_hella_MPORT_1[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.rpq_is_hella_port_oracle(2) ? 1u : 0u) & UINT64_C(0x1));
    I.c.dcacheMshrs.mshrs_rpq_ram_sdq_id_MPORT_1[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(2).rpq_sdq_id[dcache.mshr_for_diagnostic(2).rpq_head]) & UINT64_C(0x1f));
    I.c.dcacheMshrs.mshrs_rpq_ram_addr_MPORT_1[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).rpq[m.memory().dcache_for_diagnostic().mshr_for_diagnostic(3).rpq_head].request.address) & UINT64_C(0xffffffffff));
    I.c.dcacheMshrs.mshrs_rpq_ram_is_hella_MPORT_1[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.rpq_is_hella_port_oracle(3) ? 1u : 0u) & UINT64_C(0x1));
    I.c.dcacheMshrs.mshrs_rpq_ram_sdq_id_MPORT_1[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(dcache.mshr_for_diagnostic(3).rpq_sdq_id[dcache.mshr_for_diagnostic(3).rpq_head]) & UINT64_C(0x1f));
#endif
    I.c.dcacheMshrs.sdq_MPORT_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.sdq_port_cycle_oracle()));
  }
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  if (core_side) // the interrupt sink's sync register is kept by the calling thread (debug_.int_sync_0)
    I.r.uncoreTile.intsink_chain_output_chain_sync_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().int_sync_0 ? 1 : 0) & UINT64_C(0x1));
#endif
  if (memory_side) { // rpq_words
    I.r.dcacheMshrs.mshrs_0_rpq_uopsbank_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(0,2)));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcacheMshrs.mshrs_0_rpq_uopsbank_0[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(0,3)));
#endif
    I.r.dcacheMshrs.mshrs_1_rpq_uopsbank_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(1,2)));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.dcacheMshrs.mshrs_1_rpq_uopsbank_0[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(1,3)));
    I.r.dcacheMshrs.mshrs_2_rpq_uopsbank_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(2,0)));
    I.r.dcacheMshrs.mshrs_2_rpq_uopsbank_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(2,1)));
    I.r.dcacheMshrs.mshrs_2_rpq_uopsbank_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(2,2)));
    I.r.dcacheMshrs.mshrs_2_rpq_uopsbank_0[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(2,3)));
    I.r.dcacheMshrs.mshrs_3_rpq_uopsbank_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(3,0)));
    I.r.dcacheMshrs.mshrs_3_rpq_uopsbank_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(3,1)));
    I.r.dcacheMshrs.mshrs_3_rpq_uopsbank_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(3,2)));
    I.r.dcacheMshrs.mshrs_3_rpq_uopsbank_0[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.rpq_uop_br_mask_bank_now(3,3)));
#endif
    I.r.dcacheMshrs.respq_uopsbank_0_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(dcache.respq_br_mask_bank_oracle()));
  }
  if (core_side) { // dtlb_control
    I.r.lsuDtlb.r_refill_tag = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.dtlb().refill_tag()) & UINT64_C(0x7ffffff));
    I.r.lsuDtlb.r_superpage_repl_addr = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().superpage_replacement_address()) & UINT64_C(0x3));
  }
  if (core_side && versions.dtlb_entries != m.dtlb().entries_epoch()) {
    versions.dtlb_entries = m.dtlb().entries_epoch();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.lsuDtlb.sectored_entries_2_data[0] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(2).data[0]);
    I.r.lsuDtlb.sectored_entries_2_data[1] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(2).data[1]);
    I.r.lsuDtlb.sectored_entries_2_data[2] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(2).data[2]);
    I.r.lsuDtlb.sectored_entries_2_data[3] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(2).data[3]);
    I.r.lsuDtlb.sectored_entries_tag[2] = m.dtlb().sectored_entry(2).tag;
    I.r.lsuDtlb.sectored_entries_2_valid[0] = m.dtlb().sectored_entry(2).valid[0];
    I.r.lsuDtlb.sectored_entries_2_valid[1] = m.dtlb().sectored_entry(2).valid[1];
    I.r.lsuDtlb.sectored_entries_2_valid[2] = m.dtlb().sectored_entry(2).valid[2];
    I.r.lsuDtlb.sectored_entries_2_valid[3] = m.dtlb().sectored_entry(2).valid[3];
    I.r.lsuDtlb.sectored_entries_3_data[0] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(3).data[0]);
    I.r.lsuDtlb.sectored_entries_3_data[1] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(3).data[1]);
    I.r.lsuDtlb.sectored_entries_3_data[2] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(3).data[2]);
    I.r.lsuDtlb.sectored_entries_3_data[3] = components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(3).data[3]);
    I.r.lsuDtlb.sectored_entries_tag[3] = m.dtlb().sectored_entry(3).tag;
    I.r.lsuDtlb.sectored_entries_3_valid[0] = m.dtlb().sectored_entry(3).valid[0];
    I.r.lsuDtlb.sectored_entries_3_valid[1] = m.dtlb().sectored_entry(3).valid[1];
    I.r.lsuDtlb.sectored_entries_3_valid[2] = m.dtlb().sectored_entry(3).valid[2];
    I.r.lsuDtlb.sectored_entries_3_valid[3] = m.dtlb().sectored_entry(3).valid[3];
#endif
    I.r.lsuDtlb.sectored_entries_0_data[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(0).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_0_data[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(0).data[1])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_0_data[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(0).data[2])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_0_data[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(0).data[3])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_tag[0] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(0).tag) & UINT64_C(0x7ffffff));
    I.r.lsuDtlb.sectored_entries_0_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(0).valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_0_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(0).valid[1]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_0_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(0).valid[2]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_0_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(0).valid[3]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_1_data[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(1).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_1_data[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(1).data[1])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_1_data[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(1).data[2])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_1_data[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().sectored_entry(1).data[3])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.sectored_entries_tag[1] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(1).tag) & UINT64_C(0x7ffffff));
    I.r.lsuDtlb.sectored_entries_1_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(1).valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_1_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(1).valid[1]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_1_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(1).valid[2]) & UINT64_C(0x1));
    I.r.lsuDtlb.sectored_entries_1_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().sectored_entry(1).valid[3]) & UINT64_C(0x1));
    I.r.lsuDtlb.special_entry_data_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().special_entry().data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.special_entry_valid_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().special_entry().valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.superpage_entries_data_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().superpage_entry(0).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.superpage_entries_valid_0[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().superpage_entry(0).valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.superpage_entries_data_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().superpage_entry(1).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.superpage_entries_valid_0[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().superpage_entry(1).valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.superpage_entries_data_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().superpage_entry(2).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.superpage_entries_valid_0[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().superpage_entry(2).valid[0]) & UINT64_C(0x1));
    I.r.lsuDtlb.superpage_entries_data_0[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallDataTlb::pack_entry_data(m.dtlb().superpage_entry(3).data[0])) & UINT64_C(0x3ffffffff));
    I.r.lsuDtlb.superpage_entries_valid_0[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.dtlb().superpage_entry(3).valid[0]) & UINT64_C(0x1));
  }
  if (memory_side && versions.ptw != m.fabric().ptw_eval_count()) {
    versions.ptw = m.fabric().ptw_eval_count();
    I.r.ptw.count = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[0]) & UINT64_C(0x3));
    if (m.cut_lanes()) {
      write_record(I, fields::ptw_l2_refill, m.fabric().ptw_oracles()[26]);
      write_record(I, fields::ptw_s1_valid, m.fabric().ptw_oracles()[27]);
      for (unsigned w = 0; w < 8; ++w) write_record(I, fields::ptw_valid_1_0_word[w], m.fabric().ptw_oracles()[28 + w]);
    }
    I.r.ptw.databank_0[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[1]) & UINT64_C(0xfffffffffffffff));
    I.r.ptw.databank_0[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[2]) & UINT64_C(0xfffffffffffffff));
    I.r.ptw.databank_0[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[3]) & UINT64_C(0xffffffffff));
    I.r.ptw.mem_resp_data = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[4]));
    I.r.ptw.mem_resp_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[5]) & UINT64_C(0x1));
    I.r.ptw.r_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[6]) & UINT64_C(0x1fffffffffff));
    I.r.ptw.r_pte_a = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[7]) & UINT64_C(0x1));
    I.r.ptw.r_pte_d = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[8]) & UINT64_C(0x1));
    I.r.ptw.r_pte_g = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[9]) & UINT64_C(0x1));
    I.r.ptw.r_pte_ppn = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[10]) & UINT64_C(0x3fffffffffffff));
    I.r.ptw.r_pte_r = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[11]) & UINT64_C(0x1));
    I.r.ptw.r_pte_u = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[12]) & UINT64_C(0x1));
    I.r.ptw.r_pte_v = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[13]) & UINT64_C(0x1));
    I.r.ptw.r_pte_w = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[14]) & UINT64_C(0x1));
    I.r.ptw.r_pte_x = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[15]) & UINT64_C(0x1));
    I.r.ptw.r_req_addr = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[16]) & UINT64_C(0x7ffffff));
    I.r.ptw.resp_ae = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[17]) & UINT64_C(0x1));
    I.r.ptw.resp_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[18]) & UINT64_C(0x1));
    I.r.ptw.resp_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[19]) & UINT64_C(0x1));
    I.r.ptw.s2_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[20]) & UINT64_C(0x1));
    I.r.ptw.s2_valid_vec = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[21]) & UINT64_C(0x1));
    I.r.ptw.state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[22]) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.ptw.state_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[23]) & UINT64_C(0x7f));
#endif
    I.r.ptw.valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[24]) & UINT64_C(0xff));
    I.r.ptw.l2_tlb_ram_0_s1_rdata_addr_pipe_0 = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().ptw_oracles()[25]) & UINT64_C(0x1ff));
  }
  if (core_side && versions.fpu != m.fabric().fpu_eval_count()) {
    versions.fpu = m.fabric().fpu_eval_count();
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in1_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[28]));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in1_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[29]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in2_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[30]));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in2_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[31]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in3_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[32]));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_in_in3_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[33]) & UINT64_C(0x1));
    if (m.cut_lanes())
      for (unsigned i = 0; i < 9; ++i) write_record(I, fields::fpu_sidecar_cut[i], m.fabric().fpu_oracles()[61 + i]);
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_io_out_b_data_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[34]));
    I.r.coreFp.fpiu_unit_fpu_fpu_dfma_io_out_b_data_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[35]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpiu_in_in1_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[36]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpiu_in_in1_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[37]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpiu_in_in2_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[38]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpiu_in_in2_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[39]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpiu_outPipe_bits_2_toint = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[40]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_in1_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[41]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_in1_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[42]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_in2_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[43]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_in2_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[44]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_ren2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[45]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_rm = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[46]) & UINT64_C(0x7));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_typeTagOut = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[47]) & UINT64_C(0x3));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_inPipe_bits_wflags = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[48]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_io_out_outPipe_bits_1_data_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[49]));
    I.r.coreFp.fpiu_unit_fpu_fpu_fpmu_io_out_outPipe_bits_1_data_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[50]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in1_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[51]));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in1_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[52]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in2_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[53]));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in2_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[54]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in3_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[55]));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_in_in3_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[56]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_io_out_b_data_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[57]));
    I.r.coreFp.fpiu_unit_fpu_fpu_sfma_io_out_b_data_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fpu_oracles()[58]) & UINT64_C(0x1));
  }
  if (core_side && versions.fdivsqrt != m.fabric().fdivsqrt_eval_count()) {
    versions.fdivsqrt = m.fabric().fdivsqrt_eval_count();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_fractR0_A = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[4]) & UINT64_C(0x1ff));
#endif
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_hiSqrR0_A_sqrt = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[5]) & UINT64_C(0x3ff));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isInf_PA = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[6]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isInf_PB = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[7]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isInf_PC = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[8]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isNaN_PA = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[9]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isNaN_PB = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[10]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isNaN_PC = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[11]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isZero_PA = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[14]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isZero_PB = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[15]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_isZero_PC = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[16]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_nextMulAdd9A_A = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[18]) & UINT64_C(0x1ff));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_nextMulAdd9B_A = static_cast<std::uint16_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[19]) & UINT64_C(0x1ff));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_partNegSigma0_A = static_cast<std::uint32_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[20]) & UINT64_C(0x1fffff));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_sqrtOp_PA = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[26]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_sqrtOp_PB = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[27]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_valid_PA = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[29]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_valid_PB = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[30]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_valid_PC = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[31]) & UINT64_C(0x1));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_cycleNum_B = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[35]) & UINT64_C(0xf));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_ds_divSqrtRecF64ToRaw_cycleNum_C = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[36]) & UINT64_C(0x7));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_mul_reg_result_s3[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[37]));
    I.r.coreFp.fpiu_unit_fdivsqrt_divsqrt_mul_reg_result_s3[2] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.fabric().fdivsqrt_oracles()[38]) & UINT64_C(0x1ffffffffff));
    if (m.cut_lanes()) {
      write_record(I, fields::fdivsqrt_cyclenum_a, m.fabric().fdivsqrt_oracles()[1]);
      write_record(I, fields::fdivsqrt_cyclenum_e, m.fabric().fdivsqrt_oracles()[39]);
      write_record(I, fields::fdivsqrt_sqrtop_pc, m.fabric().fdivsqrt_oracles()[28]);
    }
  }
  // The CLINT time counter is kept by the calling thread (it advances at the
  // head of its step): published by that thread.
  if (core_side && m.cut_lanes())
    write_record(I, fields::clint_time, m.clint_time());
  if (memory_side && m.cut_lanes())
    write_record(I, fields::debug_inner_d_source_widx_bin, m.debug_stream(SystemGuider::DebugStream::InnerDSourceWidxBin));
  if (memory_side && m.cut_lanes()) { // debug module registers (partition-cut lanes)
    const auto& d = m.memory().debug_path_for_diagnostic();
    if (versions.debug_registers != d.debug_register_version()) {
      versions.debug_registers = d.debug_register_version();
      const auto& words = d.program_buffer_words();
      for (unsigned i = 0; i < 64; ++i)
        write_record(I, fields::debug_program_buffer_byte[i], (words[i / 4] >> (8u * (i % 4))) & 0xffu);
      const std::uint64_t data = d.abstract_data_word();
      CHISA_DIAG(versions.published_debug_data = data);
      for (unsigned i = 0; i < 8; ++i)
        write_record(I, fields::debug_abstract_data_byte[i], (data >> (8u * i)) & 0xffu);
      write_record(I, fields::debug_abstract_generated[0], d.abstract_generated_words()[0]);
      write_record(I, fields::debug_abstract_generated[1], d.abstract_generated_words()[1]);
    }
    CHISA_DIAG(chisa::diagnostic::require("debug", "data-publication-version", m.cycle(),
        chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
        versions.published_debug_data == d.abstract_data_word(),
        {{"version", d.debug_register_version()}, {"published_data", versions.published_debug_data},
         {"native_data", d.abstract_data_word()}}));
    write_record(I, fields::debug_go_reg, d.go_now() ? 1u : 0u);
    write_record(I, fields::debug_resume_req_regs, d.resume_now() ? 1u : 0u);
  }
  // The debug module's outer registers, the reset clock and the interrupt
  // sync registers are kept by the calling thread (debug_, reset_clock_,
  // interrupts_): published by that thread, after its tail updates.  The
  // debug path's faces (debug_stream) are the memory side's.
  if (core_side) { // debug module registers kept by the calling thread
    I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_bar_stall_counter = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().bypass_stall_beats_left) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_error_beatsLeft = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().error_arbiter_beats_left) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_error_idle = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().error_idle_observed) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_dmiXbar_beatsLeft = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().xbar_beats_left) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_dmOuter_DMCONTROLReg_dmactive = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().dmactive_state) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_bar_bypass_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug().bypass_reg_state) & UINT64_C(0x1));
    CHISA_DIAG(chisa::diagnostic::require("debug", "activation-state-publication", m.cycle(),
        chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
        I.r.uncoreMisc.debug_1_dmOuter_dmOuter_DMCONTROLReg_dmactive == m.debug().dmactive_state &&
            I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_bar_bypass_reg == m.debug().bypass_reg_state,
        {{"dmactive_native", m.debug().dmactive_state},
         {"dmactive_published", I.r.uncoreMisc.debug_1_dmOuter_dmOuter_DMCONTROLReg_dmactive},
         {"bypass_native", m.debug().bypass_reg_state},
         {"bypass_published", I.r.uncoreMisc.debug_1_dmOuter_dmiBypass_bar_bypass_reg}}));
  }
  if (memory_side) { // debug path faces
    I.r.uncoreMisc.debug_1_dmOuter_io_innerCtrl_source_ready_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::OuterInnerCtrlReadyReg)) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.uncoreMisc.debug_1_dmOuter_dmiXbar_readys_mask = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::OuterXbarReadysMask)) & UINT64_C(0x3));
#endif
    I.r.uncoreMisc.debug_1_dmOuter_asource_bundleOut_0_a_source_widx_widx_bin = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::OuterASourceWidxBin)) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmOuter_asource_bundleIn_0_d_sink_valid_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::OuterDSinkValidReg)) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmInner_dmInner_ctrlStateReg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::InnerCtrlState)) & UINT64_C(0x3));
    I.r.uncoreMisc.debug_1_dmInner_dmactive_synced_dmInner_io_innerCtrl_sink_valid_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::InnerCtrlSinkValidReg)) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmInner_dmiXing_bundleIn_0_d_source_ready_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::InnerDSourceReadyReg)) & UINT64_C(0x1));
    I.r.uncoreMisc.debug_1_dmInner_dmiXing_bundleOut_0_a_sink_io_deq_bits_deq_bits_reg_cdc_reg = static_cast<std::uint64_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::InnerASinkCdcReg)) & UINT64_C(0x7fffffffffffff));
    I.r.uncoreMisc.debug_1_dmInner_dmiXing_bundleOut_0_a_sink_valid_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.debug_stream(SystemGuider::DebugStream::InnerASinkValidReg)) & UINT64_C(0x1));
  }
  if (core_side) { // reset clock and interrupt sync registers kept by the calling thread
    I.r.top.ldut_reset_reg_reg = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.reset_clock().ndmreset_delay_observed) & UINT64_C(0x1));
    I.r.uncoreMisc.plicDomainWrapper_plic_pending[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.interrupts().plic_pending_0_observed) & UINT64_C(0x1));
    I.r.uncoreMisc.plicDomainWrapper_plic_pending[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.interrupts().plic_pending_1_observed) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    I.r.uncoreMisc.intsource_reg_reg[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.interrupts().clint_source_state) & UINT64_C(0x3));
    I.r.uncoreMisc.intsource_reg_reg[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.interrupts().plic_pending_0_state) & UINT64_C(0x1));
    I.r.uncoreMisc.intsource_reg_reg[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(m.interrupts().plic_pending_1_state) & UINT64_C(0x1));
#endif
  }
  // This cycle's record is complete. Diagnostic builds may capture selected
  // cycles whole so a reported mismatch can be read together with the other
  // fields of the same cycle; performance builds contain neither the call nor
  // its arguments.
  CHISA_DIAG(
    ::chisa::diagnostic::RecordDump::instance().maybe_dump(
        m.cycle(), boom_system::ModelBindings::instance().record().bytes,
        boom_system::kOracleRecordPaddedBytes);
  );
}
void publish_system_end(const SystemGuider& m) { publish_system_end_impl(m, true, true); }
void publish_system_end_memory(const SystemGuider& m) { publish_system_end_impl(m, true, false); }
void publish_system_end_core(const SystemGuider& m) { publish_system_end_impl(m, false, true); }
}  // namespace chisa::boom_model::wide
