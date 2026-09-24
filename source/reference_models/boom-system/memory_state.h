#pragma once
#include "phase_sub.h"
#ifdef CHISA_PHASE_TIMERS
#include <x86intrin.h>
#endif
// ============================================================================
// Complete SmallBoom memory-side producer.
//
// MemoryState owns the stateful boundary between BackendState/FrontendState
// and the complete-chip memory hierarchy.  In particular, it is the only
// place that:
//
//   - routes an accepted LSU request to the coherent D-cache or BoomIOMSHR;
//   - gives coherent MSHRs priority over uncached source 3 on tile A;
//   - combines D-cache, Debug and shared TileLink state into dmem_ordered;
//   - connects I/D requests to the shared queued manager path; and
//   - routes manager reads to Debug ROM, boot ROM or external backing memory.
//
// Backing storage remains caller-owned.  Read/write callbacks are the chip
// boundary; no RTL response, ready, or state is accepted by this class.
// ============================================================================

#include <cstdint>

#include "components/boom_uncached_path.h"
#include "components/small_boot_rom.h"
#include "components/small_dcache.h"
#include "components/small_icache_memory_path.h"
#include "components/small_pma.h"

namespace chisa::boom_system {

struct MemoryStateInputs {
  // Debug and tile logic occupy different reset domains in the complete
  // harness.  Keeping the three reset inputs explicit avoids silently
  // extending the core reset into dmInner or the shared fabric.
  bool debug_reset = false;
  bool dcache_reset = false;
  bool fabric_reset = false;

  components::BoomDmiRequest dmi{};
  components::BoomUncachedRequest raw_attempt{};
  bool dmi_response_ready = false;

  // Request accepted by BackendState on this edge.  MemoryState performs PMA
  // routing; callers must not pre-classify it into parallel component inputs.
  components::BoomUncachedRequest request{};

  // Current I-cache line request.  FrontendState may first be evaluated with
  // this false to obtain the held D response, then reevaluated with the
  // resulting acquire offer before the edge is committed.
  bool icache_a_valid = false;
  std::uint32_t icache_a_address = 0;

  // Ready returned by BackendState after it schedules this cycle's internal
  // DCache -> LSU release search.
  bool lsu_release_ready = false;

  // Same-edge LSU cancellation for the request already occupying D-cache s1.
  bool dcache_s1_kill = false;

  // The D-cache request payload registers apply GetNewBrMask on every edge,
  // independently of their valid bits.
  boomcfg::br_mask_t branch_resolve_mask = 0;
  boomcfg::br_mask_t branch_kill_mask = 0;  // brupdate.b1.mispredict_mask
  bool lsu_exception = false;          // io.lsu.exception

  // Current Debug Module manager-face A handshake, evaluated by the live
  // cold SystemBus/PeripheryBus chain before this edge commits.
  bool debug_manager_a_fire = false;
  std::uint8_t debug_manager_a_source = 0;
};

struct MemoryBackendOutputs {
  components::BoomUncachedCompletion cacheable_response{};
  components::BoomUncachedCompletion cacheable_nack{};
  components::BoomUncachedCompletion hella_response{};
  components::BoomUncachedCompletion hella_nack{};
  bool dmem_req_ready = true;
  bool dmem_ordered = true;
  bool dmem_release_valid = false;
  std::uint64_t dmem_release_address = 0;
};

/** Cycle-start outputs that feed BackendState and diagnostic comparisons. */
struct MemoryStateOutputs {
  components::BoomUncachedOutputs debug{};
  components::SmallDcacheOutputs dcache{};
  MemoryBackendOutputs backend{};
};

class MemoryState {
 public:
  MemoryStateOutputs outputs(const MemoryStateInputs& input) const {

    MemoryStateOutputs result;

    outputs_into(input, result);

    return result;

  }

  void outputs_into(const MemoryStateInputs& input, MemoryStateOutputs& result) const {
    // debug and dcache are rebuilt from scratch by their own outputs_into;
    // only the backend view is assigned field by field below.
    result.backend = MemoryBackendOutputs{};
    debug_path_.outputs_into(make_debug_inputs(input), result.debug);

    components::SmallDcacheInputs dcache_input;
    dcache_input.reset = input.dcache_reset;
    result.dcache = dcache_.evaluate(dcache_input);

    if (result.dcache.response.is_hella)
      result.backend.hella_response = result.dcache.response;
    else
      result.backend.cacheable_response = result.dcache.response;
    if (result.dcache.nack.is_hella)
      result.backend.hella_nack = result.dcache.nack;
    else
      result.backend.cacheable_nack = result.dcache.nack;
    result.backend.dmem_req_ready = result.dcache.request_ready;
    result.backend.dmem_ordered =
        result.dcache.ordered && !result.debug.dcache_s1_valid &&
        !result.debug.dcache_s2_valid && result.debug.iomshr_state == 0;
    result.backend.dmem_release_valid = result.dcache.lsu_release_valid;
    result.backend.dmem_release_address =
        result.dcache.lsu_release_address;
    return;
  }

  /** Combinational shared-fabric view for the current I-cache offer. */
  template <typename Read64>
  components::SmallICacheMemoryPathOutputs fabric_outputs(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const Read64& external_read64) const {
    const components::SmallICacheMemoryPathInputs fabric_input =
        make_fabric_inputs(input, state);
    const auto mapped_read64 = [&](std::uint32_t address) {
      return read_mapped(address, external_read64);
    };
    return fabric_.outputs(fabric_input, mapped_read64);
  }

  template <typename Read64>
  components::SmallICacheMemoryPath::HybridEvaluation prepare_hybrid_fabric(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const Read64& external_read64) const {
    const auto fabric_input = make_fabric_inputs(input, state);
    const auto mapped_read64 = [&](std::uint32_t address) {
      return read_mapped(address, external_read64);
    };
    return fabric_.prepare_hybrid(fabric_input, mapped_read64);
  }

  components::SmallICacheMemoryPathOutputs resolve_hybrid_fabric(
      const components::SmallICacheMemoryPath::HybridEvaluation& evaluation,
      const components::SmallExternalManagerInputs& manager) const {
    return fabric_.resolve_hybrid(evaluation, manager);
  }

  const components::SmallICacheMemoryPathOutputs& resolve_hybrid_fabric_in_place(
      components::SmallICacheMemoryPath::HybridEvaluation& evaluation,
      const components::SmallExternalManagerInputs& manager) const {
    return fabric_.resolve_hybrid_in_place(evaluation, manager);
  }

  template <typename Read64>
  components::SmallICacheMemoryPathOutputs hybrid_fabric_outputs(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const components::SmallExternalManagerInputs& manager,
      const Read64& external_read64) const {
    const components::SmallICacheMemoryPathInputs fabric_input =
        make_fabric_inputs(input, state);
    const auto mapped_read64 = [&](std::uint32_t address) {
      return read_mapped(address, external_read64);
    };
    return fabric_.hybrid_outputs(fabric_input, manager, mapped_read64);
  }

  /** Compatibility wrapper for standalone diagnostics. The production
    * SystemGuider passes its already-evaluated cycle-start state instead. */
  template <typename Read64>
  components::SmallICacheMemoryPathOutputs fabric_outputs(
      const MemoryStateInputs& input, const Read64& external_read64) const {
    const MemoryStateOutputs state = outputs(input);
    return fabric_outputs(input, state, external_read64);
  }

  /** Commit one chronological edge from the exact cycle-start evaluation
    * already consumed by the backend and frontend. */
  template <typename Write64>
  void commit(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const components::SmallICacheMemoryPathOutputs& fabric_output,
      const Write64& external_write64) {
    const components::SmallICacheMemoryPathInputs fabric_input =
        make_fabric_inputs(input, state);

    // A ReleaseData beat updates caller-owned memory on the same edge before
    // the protocol state advances, matching the standalone audit ordering.
    if (fabric_output.memory_write_valid) {
      external_write64(fabric_output.memory_write_address,
                       fabric_output.memory_write_data);
      if constexpr (boomcfg::DCACHE_BEAT_WORDS == 2) {
        external_write64(fabric_output.memory_write_address + 8u,
                         fabric_output.memory_write_data_hi);
      }
    }

    components::SmallDcacheInputs dcache_input;
    dcache_input.reset = input.dcache_reset;
    dcache_input.raw_request =
        input.request.valid ? input.request : input.raw_attempt;
    dcache_input.raw_request_fire = input.request.valid;
    dcache_input.s1_kill = input.dcache_s1_kill;
    dcache_input.branch_resolve_mask = input.branch_resolve_mask;
    dcache_input.branch_kill_mask = input.branch_kill_mask;
    dcache_input.exception = input.lsu_exception;

    if (input.request.valid &&
        physical_attributes(input.request.address).cacheable) {
      dcache_input.request = input.request;
    }
    dcache_input.external_miss_fire =
        state.debug.iomshr_req_valid && state.debug.iomshr_req_ready;
    dcache_input.tile_a_ready =
        state.dcache.tile_a.valid && fabric_output.dcache_a_ready;
    dcache_input.tile_b = fabric_output.dcache_b;
    dcache_input.tile_c_ready = fabric_output.dcache_c_ready;
    dcache_input.tile_d = fabric_output.dcache_d;
    dcache_input.lsu_release_ready = input.lsu_release_ready;
    dcache_input.iomshr_mem_access = debug_path_.iomshr_state_now() == 1;

    components::BoomUncachedPathInputs debug_input =
        make_debug_inputs(input);
    if (input.request.valid &&
        !physical_attributes(input.request.address).cacheable)
      debug_input.request = input.request;
    debug_input.tile_a_ready =
        !state.dcache.tile_a.valid && fabric_output.dcache_a_ready;
    debug_input.tile_d_valid = fabric_output.dcache_d.valid;
    debug_input.tile_d_opcode = fabric_output.dcache_d.opcode;
    debug_input.tile_d_source = fabric_output.dcache_d.source;
    debug_input.tile_d_data =
        boomcfg::TILE_BEAT_BYTES == 16 && (state.debug.fabric_address & 8u)
            ? fabric_output.dcache_d.data_hi : fabric_output.dcache_d.data;


    // All three transitions consume the same cycle-start packets.  Their
    // statement order mirrors the qualified audit and must stay explicit.
    fabric_.commit(fabric_input, fabric_output);
    dcache_.step(dcache_input);
    debug_path_.step(debug_input);
    // Oracle: the io-mshr writes the shared response queue the cycle its
    // response fires toward the LSU.
    if (debug_path_.iomshr_entered_resp_oracle())
      dcache_.oracle_io_push(debug_path_.iomshr_resp_data_oracle());
    dcache_.refresh_oracle_snapshots();
  }

  /** What the tile half of the post-edge commit leaves for the fabric half. */
  struct HybridCommitCarry {
    components::SmallICacheMemoryPathInputs fabric_input{};
  };

  /** Post-edge commit, tile half: the D-cache and the uncached path take the
    * edge on this cycle's inputs.  Everything the next cycle's outputs_into()
    * reads is final after it; the fabric half (commit_hybrid_fabric) may run
    * later, on the same thread, while another thread already reads those
    * outputs.  The fabric input is captured here, before the D-cache moves. */
  void commit_hybrid_tile(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const components::SmallICacheMemoryPathOutputs& fabric_output,
      HybridCommitCarry& carry) {
    carry.fabric_input = make_fabric_inputs(input, state);

    components::SmallDcacheInputs dcache_input;
    dcache_input.reset = input.dcache_reset;
    dcache_input.raw_request =
        input.request.valid ? input.request : input.raw_attempt;
    dcache_input.raw_request_fire = input.request.valid;
    dcache_input.s1_kill = input.dcache_s1_kill;
    dcache_input.branch_resolve_mask = input.branch_resolve_mask;
    dcache_input.branch_kill_mask = input.branch_kill_mask;
    dcache_input.exception = input.lsu_exception;
    if (input.request.valid &&
        physical_attributes(input.request.address).cacheable) {
      dcache_input.request = input.request;
    }
    dcache_input.external_miss_fire =
        state.debug.iomshr_req_valid && state.debug.iomshr_req_ready;
    dcache_input.tile_a_ready =
        state.dcache.tile_a.valid && fabric_output.dcache_a_ready;
    dcache_input.tile_b = fabric_output.dcache_b;
    dcache_input.tile_c_ready = fabric_output.dcache_c_ready;
    dcache_input.tile_d = fabric_output.dcache_d;
    dcache_input.tile_e_ready = fabric_output.dcache_e_ready;
    dcache_input.lsu_release_ready = input.lsu_release_ready;
    dcache_input.iomshr_mem_access = debug_path_.iomshr_state_now() == 1;

    components::BoomUncachedPathInputs debug_input =
        make_debug_inputs(input);
    if (input.request.valid &&
        !physical_attributes(input.request.address).cacheable)
      debug_input.request = input.request;
    debug_input.tile_a_ready =
        !state.dcache.tile_a.valid && fabric_output.dcache_a_ready;
    debug_input.tile_d_valid = fabric_output.dcache_d.valid;
    debug_input.tile_d_opcode = fabric_output.dcache_d.opcode;
    debug_input.tile_d_source = fabric_output.dcache_d.source;
    debug_input.tile_d_data =
        boomcfg::TILE_BEAT_BYTES == 16 && (state.debug.fabric_address & 8u)
            ? fabric_output.dcache_d.data_hi : fabric_output.dcache_d.data;

#ifdef CHISA_PHASE_TIMERS
    std::uint64_t t = __rdtsc();
    const auto lap = [&](unsigned slot) { const std::uint64_t now = __rdtsc(); g_phase_sub[slot] += now - t; t = now; };
#else
    const auto lap = [](unsigned) {};
#endif
    dcache_.step(dcache_input);
    lap(kSubDcacheStep);
    debug_path_.step(debug_input);
    lap(kSubDebugPathStep);
  }

  /** Post-edge commit, fabric half: the memory write behind this cycle's
    * manager beat, the tile fabric's commit, the oracle faces of the D-cache.
    * Neither the D-cache nor the uncached path reads what it writes; the
    * order against the tile half only matters for the oracle faces, which
    * follow both steps as before. */
  template <typename Write64>
  void commit_hybrid_fabric(
      const HybridCommitCarry& carry,
      const components::SmallExternalManagerInputs& manager,
      const components::SmallICacheMemoryPathOutputs& fabric_output,
      const Write64& external_write64,
      const components::SmallICacheMemoryPath::HybridEvaluation* prepared = nullptr) {
    if (fabric_output.memory_write_valid) {
      external_write64(fabric_output.memory_write_address,
                       fabric_output.memory_write_data);
      if constexpr (boomcfg::DCACHE_BEAT_WORDS == 2) {
        external_write64(fabric_output.memory_write_address + 8u,
                         fabric_output.memory_write_data_hi);
      }
    }
#ifdef CHISA_PHASE_TIMERS
    std::uint64_t t = __rdtsc();
    const auto lap = [&](unsigned slot) { const std::uint64_t now = __rdtsc(); g_phase_sub[slot] += now - t; t = now; };
#else
    const auto lap = [](unsigned) {};
#endif
    fabric_.commit_hybrid(carry.fabric_input, manager, fabric_output, prepared);
    lap(kSubFabricCommit);
    // Oracle: the io-mshr writes the shared response queue the cycle its
    // response fires toward the LSU.
    if (debug_path_.iomshr_entered_resp_oracle())
      dcache_.oracle_io_push(debug_path_.iomshr_resp_data_oracle());
    dcache_.refresh_oracle_snapshots();
    lap(kSubDcacheSnapshots);
  }

  /** Both halves back to back (the single-thread path and the tests). */
  template <typename Write64>
  void commit_hybrid(
      const MemoryStateInputs& input, const MemoryStateOutputs& state,
      const components::SmallExternalManagerInputs& manager,
      const components::SmallICacheMemoryPathOutputs& fabric_output,
      const Write64& external_write64,
      const components::SmallICacheMemoryPath::HybridEvaluation* prepared = nullptr) {
    HybridCommitCarry carry;
    commit_hybrid_tile(input, state, fabric_output, carry);
    commit_hybrid_fabric(carry, manager, fabric_output, external_write64, prepared);
  }

  /** Compatibility wrapper for standalone diagnostics that have not split
    * their evaluate and commit phases. */
  template <typename Read64, typename Write64>
  void step(const MemoryStateInputs& input, const Read64& external_read64,
            const Write64& external_write64) {
    const MemoryStateOutputs state = outputs(input);
    components::SmallICacheMemoryPathOutputs fabric_output;
    if (!input.fabric_reset)
      fabric_output = fabric_outputs(input, state, external_read64);
    commit(input, state, fabric_output, external_write64);
  }

  components::PmaAttributes physical_attributes(
      std::uint64_t address) const {
    return components::SmallPma::lookup(address);
  }

  const components::SmallDcache& dcache_for_diagnostic() const {
    return dcache_;
  }
  const components::SmallICacheMemoryPath& fabric_for_diagnostic() const {
    return fabric_;
  }
  const components::BoomUncachedPath& debug_path_for_diagnostic() const {
    return debug_path_;
  }

 private:
  static components::BoomUncachedPathInputs make_debug_inputs(
      const MemoryStateInputs& input) {
    components::BoomUncachedPathInputs result;
    result.reset = input.debug_reset;
    result.dmi = input.dmi;
    result.dmi_response_ready = input.dmi_response_ready;
    result.debug_manager_a_fire = input.debug_manager_a_fire;
    result.debug_manager_a_source = input.debug_manager_a_source;
    return result;
  }

  static components::SmallTileARequest make_debug_a(
      const components::BoomUncachedOutputs& debug) {
    components::SmallTileARequest result;
    result.valid = debug.dcache_a_valid;
    result.opcode = debug.dcache_a_opcode;
    result.size = debug.dcache_a_size;
    result.source = debug.dcache_a_source;
    result.address = debug.dcache_a_address;
    result.mask = debug.dcache_a_mask;
    result.data = debug.dcache_a_data;
    if constexpr (boomcfg::TILE_BEAT_BYTES == 16) {
      // IOMSHR owns a 64-bit word; place it in the addressed tile beat half.
      // The same active address selects the returning D word above.
      if (result.address & 8u) {
        result.mask <<= 8;
        result.data_hi = result.data;
        result.data = 0;
      }
    }
    return result;
  }

  static components::SmallICacheMemoryPathInputs make_fabric_inputs(
      const MemoryStateInputs& input, const MemoryStateOutputs& state) {
    components::SmallICacheMemoryPathInputs result;
    result.reset = input.fabric_reset;
    result.icache_a_valid = input.icache_a_valid;
    result.icache_a_address = input.icache_a_address;
    // Coherent BoomMSHRs win over the Debug IOMSHR (source nMSHRs+1).  The
    // losing Debug packet remains held until its ready is returned.
    result.dcache_a = state.dcache.tile_a.valid
                          ? state.dcache.tile_a
                          : make_debug_a(state.debug);
    result.dcache_b_ready = state.dcache.tile_b_ready;
    result.dcache_c = state.dcache.tile_c;
    result.dcache_d_ready = state.dcache.tile_d_ready;
    result.dcache_e = state.dcache.tile_e;
    return result;
  }

  template <typename Read64>
  std::uint64_t read_mapped(std::uint32_t address,
                            const Read64& external_read64) const {
    if (address < UINT32_C(0x1000))
      return debug_path_.debug_memory_read64(address);
    if (address >= UINT32_C(0x10000) && address < UINT32_C(0x10080))
      return components::SmallBootRom::read64(address);
    return external_read64(address);
  }

  components::BoomUncachedPath debug_path_{};
  components::SmallDcache dcache_{};
  components::SmallICacheMemoryPath fabric_{};

 public:
  /** Hart-facing debug halt request (DMCONTROL.haltreq).  The guider turns
    * this into the decode-time debug interrupt; no RTL value is involved. */
  bool debug_halt_request() const { return debug_path_.halt_request(); }
};

}  // namespace chisa::boom_system
