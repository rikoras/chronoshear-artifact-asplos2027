#pragma once
// Native transaction, memory and floating-point models for the full-chip
// reference. The implementation contains no generated RTL execution code.

#include <array>
#include <cstdint>
#include <memory>
#if defined(CHISA_WIDE_MODEL)
#include "cold_contract.h"
#endif

#include "protocol/coherence.h"
#include "protocol/debug.h"
#include "protocol/floating_point.h"
#include "protocol/memory_bus.h"
#include "protocol/ptw.h"
#include "protocol/axi_memory.h"
#include "protocol/system_bus.h"
#include "sparse_backing_memory.h"

namespace chisa::boom_system {

/** Complete hot-tile boundary followed by SystemBus, L2 and the DRAM chain.
  * Tile source geometry is fixed by the BOOM configuration. The software
  * system bus applies client prefixes and the configured beat-width conversion. */
struct CoherentMemoryInputs {
  bool reset = false;
  protocol::MbusTlA tile_a{};
  bool tile_b_ready = false;
  protocol::CoherentTlC tile_c{};
  bool tile_d_ready = false;
  protocol::CoherentTlE tile_e{};
  bool operator==(const CoherentMemoryInputs& o) const {
    return reset == o.reset && tile_a == o.tile_a &&
           tile_b_ready == o.tile_b_ready && tile_c == o.tile_c &&
           tile_d_ready == o.tile_d_ready && tile_e == o.tile_e;
  }
  bool operator!=(const CoherentMemoryInputs& o) const {
    return !(*this == o);
  }
};

struct CoherentMemoryOutputs {
  bool tile_a_ready = false;
  protocol::CoherentTlB tile_b{};
  bool tile_c_ready = false;
  protocol::CoherentTlD tile_d{};
  bool tile_e_ready = false;
};

/** Selected AXI-memory oracle values owned by one cold memory chain.
  *
  * These describe the native fragmenter/buffer transaction state and
  * the exact sparse AXI RAM control shell.  Queue MPORT values are the word
  * addressed by the queue's current dequeue pointer, exactly as in FIRRTL. */
struct MbusMemoryOracleState {
  std::uint64_t buf_b_maybe_full = 0;
  std::uint64_t buf_b_enq_ptr = 0;
  std::uint64_t buf_b_deq_ptr = 0;
  std::uint64_t buf_b_echo_real_last = 0;
  std::uint64_t buf_b_id = 0;
  std::uint64_t buf_b_resp = 0;

  std::uint64_t buf_r_maybe_full = 0;
  std::uint64_t buf_r_enq_ptr = 0;
  std::uint64_t buf_r_deq_ptr = 0;
  std::uint64_t buf_r_data = 0;
  std::uint64_t buf_r_echo_real_last = 0;
  std::uint64_t buf_r_id = 0;
  std::uint64_t buf_r_last = 0;
  std::uint64_t buf_r_resp = 0;

  std::uint64_t buf_ar_maybe_full = 0;
  std::uint64_t buf_ar_enq_ptr = 0;
  std::uint64_t buf_ar_deq_ptr = 0;
  std::uint64_t buf_ar_addr = 0;
  std::uint64_t buf_ar_echo_real_last = 0;
  std::uint64_t buf_ar_id = 0;

  std::uint64_t buf_aw_maybe_full = 0;
  std::uint64_t buf_aw_deq_ptr = 0;
  std::uint64_t buf_aw_addr = 0;
  std::uint64_t buf_aw_echo_real_last = 0;
  std::uint64_t buf_aw_id = 0;

  std::uint64_t buf_w_maybe_full = 0;
  std::uint64_t buf_w_enq_ptr = 0;
  std::uint64_t buf_w_deq_ptr = 0;
  std::uint64_t buf_w_data = 0;
  std::uint64_t buf_w_last = 0;
  std::uint64_t buf_w_strb = 0;

  std::uint64_t frag_busy = 0;
  std::uint64_t frag_busy_1 = 0;
  std::uint64_t frag_deq_maybe_full = 0;
  std::uint64_t frag_deq_1_maybe_full = 0;
  std::uint64_t frag_deq_id = 0, frag_deq_1_id = 0;
  std::uint64_t frag_deq_addr = 0, frag_deq_1_addr = 0;
  std::uint64_t frag_deq_len = 0, frag_deq_size = 0, frag_deq_burst = 0;
  std::uint64_t frag_deq_1_len = 0, frag_deq_1_size = 0, frag_deq_1_burst = 0;
  std::uint64_t frag_deq_bank = 0;
  std::uint64_t frag_deq_1_bank = 0;
  std::uint64_t frag_in_w_maybe_full = 0;
  std::uint64_t frag_in_w_data = 0;
  std::uint64_t frag_in_w_strb = 0;
  std::uint64_t frag_r_addr = 0;
  std::uint64_t frag_r_addr_1 = 0;
  std::uint64_t frag_r_len = 0;
  std::uint64_t frag_r_len_1 = 0;
  std::uint64_t frag_w_counter = 0;
  std::uint64_t frag_wbeats_latched = 0;

  std::uint64_t ram_r_full = 0;
  std::uint64_t ram_r_id = 0;
  std::uint64_t ram_rdata_addr_pipe = 0;
  std::uint64_t ram_w_echo_real_last = 0;
  std::uint64_t ram_w_full = 0;
  std::uint64_t ram_w_id = 0;
};

/** Selected register/wire values owned by the extracted coherence and
  * MemoryBus modules.  Keeping this plain snapshot outside the generated
  * types prevents their very large headers from leaking into the hot model.
  * Unlike AxiChainMirror these values are read from the sidecar that actually
  * drives the modeled TileLink/AXI traffic. */
struct CoherentMemoryOracleState {
  struct Tracker {
    std::uint64_t address = 0;
    std::uint64_t count = 0;
    std::uint64_t got_e = 0;
    std::uint64_t o_maybe_full = 0;
    std::uint64_t o_enq_ptr = 0;
    std::uint64_t o_deq_ptr = 0;
    std::uint64_t opcode = 0;
    std::uint64_t sent_d = 0;
    std::uint64_t shared = 0;
    std::uint64_t size = 0;
    std::uint64_t source = 0;
  };

  struct YankerQueue {
    std::uint64_t deq_ptr = 0;
    std::uint64_t enq_ptr = 0;
    std::uint64_t maybe_full = 0;
    std::uint64_t extra_id = 0;
    std::uint64_t size = 0;
    std::uint64_t source = 0;
  };

  std::uint64_t tracker_address = 0;
  std::uint64_t tracker_got_e = 0;
  std::uint64_t tracker_o_maybe_full = 0;
  std::uint64_t tracker_o_enq_ptr = 0;
  std::uint64_t tracker_o_deq_ptr = 0;
  std::uint64_t tracker_opcode = 0;
  std::uint64_t tracker_sent_d = 0;
  std::uint64_t tracker_size = 0;
  std::uint64_t tracker_source = 0;
  std::uint64_t broadcast_beats_left = 0;
  std::uint64_t broadcast_beats_left_1 = 0;
  std::uint64_t broadcast_state_1_0 = 0;
  std::uint64_t broadcast_state_1_1 = 0;
  std::uint64_t broadcast_state__1 = 0;
  std::uint64_t broadcast_reg = 0;
  std::uint64_t broadcast_counter_2 = 0;
  std::uint64_t broadcast_state_1_2 = 0;
  std::uint64_t broadcast_state_1_3 = 0;
  std::uint64_t broadcast_state_1_4 = 0;
  std::uint64_t broadcast_state__0 = 0;
  // Partition-cut lanes of the broadcast hub.
  std::uint64_t broadcast_reg_1 = 0, broadcast_reg_2 = 0, broadcast_counter = 0, broadcast_r = 0;

  std::array<Tracker, 4> trackers{};
  std::array<YankerQueue, 32> all_yank{};

  // Manifest selects AXI IDs 0, 1 and 18 from the 32-entry UserYanker.
  std::array<YankerQueue, 3> yank{};
  std::uint64_t tl2axi4_gen_257 = 0;
  std::uint64_t tl2axi4_counter = 0;
  std::uint64_t tl2axi4_done_aw = 0;
  std::uint64_t tl2axi4_r_holds_d = 0;
  std::uint64_t tl2axi4_b_delay = 0;
  std::uint64_t tl2axi4_deq_maybe_full = 0;
  std::uint64_t tl2axi4_deq_data = 0;
  std::uint64_t tl2axi4_deq_strb = 0;
  std::uint64_t tl2axi4_arw_maybe_full = 0;
  std::uint64_t tl2axi4_arw_bank = 0;
  std::uint64_t tl2axi4_arw_id = 0, tl2axi4_arw_addr = 0;
  std::uint64_t tl2axi4_arw_len = 0, tl2axi4_arw_size = 0, tl2axi4_arw_burst = 0;
  std::uint64_t tl2axi4_arw_wen = 0, tl2axi4_arw_echo_tl_state_size = 0;
  std::uint64_t tl2axi4_arw_echo_tl_state_source = 0;
};

// Exact manifest order for every selected SystemBus stream.  The generated
// capture contract contains 96 PRE registers followed by 77 POST memory-read
// ports; keeping one fixed array makes batch sampling cheap without erasing
// the timing class recorded by ModelBindings.
#if defined(CHISA_WIDE_MODEL)
using SystemBusOracleState = std::array<std::uint64_t, cold_contract::sbus_count>;
#else
using SystemBusOracleState = std::array<std::uint64_t, 173>;
#endif

// Exact manifest order for every selected control/periphery-bus register.
// All 57 are ordinary PRE register streams in the locked SmallBoom contract.
#if defined(CHISA_WIDE_MODEL)
using PeripheryBusOracleState = std::array<std::uint64_t, cold_contract::pbus_count>;
#else
using PeripheryBusOracleState = std::array<std::uint64_t, 57>;
#endif

/** The A-channel edge most recently clocked into the extracted SystemBus.
  * Kept as provenance for seam diagnosis; it never feeds model behavior. */
struct SystemBusBoundaryTransaction {
  bool a_valid = false;
  bool a_ready = false;
  bool a_fire = false;
  std::uint8_t a_opcode = 0;
  std::uint8_t a_size = 0;
  std::uint8_t a_source = 0;
  std::uint32_t a_address = 0;
  std::uint64_t readys_mask_before = 0;
  std::uint64_t readys_mask_after = 0;
  std::uint64_t state_1_before = 0;
  std::uint64_t state_1_after = 0;
};

/** One committed C-channel edge at the hot-tile / cold-coherence seam.
  *
  * This is validation-only provenance: it records the inputs which were
  * actually clocked into the extracted RTL and the resulting tracker write.
  * Keeping it next to the sidecar prevents downstream oracle mismatches from
  * obscuring whether the first split was at the seam or inside the module. */
struct CoherenceBoundaryTransaction {
  bool c_valid = false;
  bool c_ready = false;
  bool c_fire = false;
  std::uint8_t c_opcode = 0;
  std::uint8_t c_param = 0;
  std::uint8_t c_size = 0;
  std::uint8_t c_source = 0;
  std::uint32_t c_address = 0;
  std::uint64_t c_data = 0;
  std::uint64_t c_data_hi = 0;
  bool c_corrupt = false;

  std::array<bool, 4> line_match{};
  std::array<bool, 4> probe_ack{};
  std::array<std::uint8_t, 4> shared_before{};
  std::array<std::uint8_t, 4> shared_after{};
};

// Cold uncore per-module timing (phase builds; no-ops otherwise).
void cold_module_timing_reset();
void cold_module_timing_report(double ns_per_tick, double cycles);

class NativeFabric {
 public:
  NativeFabric();
  ~NativeFabric();
  NativeFabric(const NativeFabric&) = delete;
  NativeFabric& operator=(const NativeFabric&) = delete;

  void commit_fdivsqrt(const protocol::FDivSqrtInputs& inputs);
  const protocol::FDivSqrtOutputs& fdivsqrt_outputs() const;
  const protocol::FDivSqrtOracleState& fdivsqrt_oracles() const;
  bool fdivsqrt_active() const;
  std::uint64_t fdivsqrt_eval_count() const;
  std::uint64_t fdivsqrt_skipped_count() const;
  void commit_fpu(const protocol::FpuInputs& inputs);
  const protocol::FpuOutputs& fpu_outputs() const;
  const protocol::FpuOracleState& fpu_oracles() const;
  bool fpu_active() const;
  std::uint64_t fpu_eval_count() const;
  std::uint64_t fpu_skipped_count() const;
  const protocol::PtwOutputs& evaluate_ptw(
      const protocol::PtwInputs& inputs);
  void commit_ptw(const protocol::PtwInputs& inputs);
  const protocol::PtwOutputs& ptw_outputs() const;
  const protocol::PtwOracleState& ptw_oracles() const;
  bool ptw_active() const;
  std::uint64_t ptw_eval_count() const;
  std::uint64_t ptw_skipped_count() const;
  // is_lookahead=true marks the post-edge wire-oracle refresh pass.  Both
  // passes idle-skip on one condition: no fabric register changed on the
  // last committed edge and the boundary input equals the last fully
  // evaluated one.  A skipped lookahead is exact because the cached wire
  // oracles were produced from those same registers and that same input.
  const CoherentMemoryOutputs& evaluate_coherent_memory(
      const CoherentMemoryInputs& inputs, bool is_lookahead = false);
  void commit_coherent_memory(SparseBackingMemory& memory);
  protocol::AxiRamAccess dram_access(
      const SparseBackingMemory& memory) const;
  bool coherent_memory_converged() const;
  bool coherent_memory_active() const;
  std::uint64_t coherent_memory_skipped_count() const;
  std::uint64_t coherent_memory_lookahead_skipped_count() const;

  /** The Debug Module is hand-written: the uncached path owns every Debug
    * Module register and its CBus manager face is the same-cycle register
    * router (a.ready = d.ready, d.valid = a.valid, read data from the hand
    * memory map).  The generated dmOuter/dmInner sidecars and the shadow
    * mode that validated the hand model were removed after de86af23. */
  /** 64-bit read of the hand Debug Module memory map, installed by the
    * guider; used by the hand manager face for Get responses. */
  void set_debug_reader(std::uint64_t (*reader)(const void*, std::uint32_t, bool),
                        const void* context);
  /** Current Debug Module CBus manager input after coherent-memory fixed-point
    * convergence.  Its A valid/ready handshake is an architectural side-effect
    * boundary consumed by BoomUncachedPath on the same modeled edge. */
  const protocol::DebugInnerInputs& debug_manager_inputs() const;
  /** Lookahead audit (see native_fabric.cpp): pre-edge evaluations,
    * those whose input equalled the previous lookahead's, and those that
    * still re-ran the fixed point. */
  std::uint64_t coherent_memory_pre_edge_total_count() const;
  std::uint64_t coherent_memory_pre_edge_equal_lookahead_count() const;
  std::uint64_t coherent_memory_pre_edge_recomputed_count() const;
  bool system_bus_active() const;
  std::uint64_t system_bus_eval_count() const;
  std::uint64_t system_bus_skipped_count() const;
  std::uint64_t coherence_manager_eval_count() const;
  std::uint64_t coherence_manager_skipped_count() const;
  std::uint64_t memory_bus_eval_count() const;
  std::uint64_t memory_bus_skipped_count() const;

  std::uint64_t axi_fragmenter_eval_count() const;
  std::uint64_t axi_fragmenter_skipped_count() const;
  std::uint64_t axi_buffer_eval_count() const;
  std::uint64_t axi_buffer_skipped_count() const;
  const MbusMemoryOracleState& mbus_memory_oracles() const;
  const MbusMemoryOracleState& mmio_memory_oracles() const;
  const CoherentMemoryOracleState& coherent_memory_oracles() const;
  const SystemBusOracleState& system_bus_oracles() const;
  const PeripheryBusOracleState& periphery_bus_oracles() const;
  /** Version of each oracle array: incremented by every refresh.  A
    * sampler that reads an array watches this word instead of the array. */
  const std::uint64_t& system_bus_oracle_version() const;
  const std::uint64_t& periphery_bus_oracle_version() const;
  const std::uint64_t& mbus_memory_oracle_version() const;
  const std::uint64_t& mmio_memory_oracle_version() const;
  const std::uint64_t& coherent_memory_oracle_version() const;
  std::uint64_t plic_out_back_maybe_full() const;
  std::uint64_t plic_out_back_bank_0() const;
  std::uint64_t plic_out_back_bank_1() const;
  std::uint64_t plic_out_back_data() const;
  const SystemBusBoundaryTransaction&
  last_system_bus_boundary_transaction() const;
  const CoherenceBoundaryTransaction&
  last_coherence_boundary_transaction() const;

 private:
  struct Impl;
 public:
  static void report_sizes();  // phase builds: the cold module objects' sizes (SYSBENCH_COLD_SIZES)
 private:
  std::unique_ptr<Impl> impl_;
};

}  // namespace chisa::boom_system
