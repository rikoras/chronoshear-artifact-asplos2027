#pragma once
// Neighbor-owned backend inputs/outputs; no concrete backend or core dependency.
#include <array>
#include <cstdint>
#include "core_types.h"
#include "../../boom-system/components/boom_uncached_path.h"
#include "../../boom-system/components/small_hellacache_shim.h"
#include "../../boom-system/components/small_pma.h"

namespace chisa::boom_system {

/** Same-edge control feedback consumed by the frontend FTQ.
  *
  * These are outputs of this cycle's backend transition, not sampled DUT
  * wires and not values carried over from the preceding cycle. */
struct BackendFrontendFeedback {
  bool ftq_deq_valid = false;
  std::uint8_t ftq_deq_idx = 0;
  bool ftq_redirect_valid = false;
  std::uint8_t ftq_redirect_idx = 0;
  bool ftq_brupdate_mispredict = false;
  std::uint8_t ftq_brupdate_idx = 0;
  std::uint8_t ftq_brupdate_pc_lob = 0;
  bool ftq_brupdate_taken = false;
  std::uint8_t ftq_get_pc_0_idx = 0;
  std::uint8_t ftq_get_pc_1_idx = 0;
};

/** Current combinational control driven from the core toward the frontend.
  * Populated by BackendState::step after it evaluates the held FetchBuffer
  * offer for this chronological cycle. */
struct BackendFrontendControl {
  bool fetch_ready = false;
  bool sfence_valid = false;
  bool sfence_rs1 = false;
  bool sfence_rs2 = false;
  std::uint64_t sfence_addr = 0;
  bool icache_invalidate = false;
  bool redirect_flush = false;
  bool redirect_valid = false;
  std::uint64_t redirect_pc = 0;
  std::uint8_t redirect_ftq_idx = 0;

  // Redirect history is reconstructed by FrontendState because the snapshots
  // live in its FTQ.  These fields identify the core-side source and carry the
  // branch facts needed to apply GlobalHistory.update without an RTL tap.
  bool redirect_from_rob_flush = false;
  bool redirect_from_branch_mispredict = false;
  bool redirect_branch_taken = false;
  bool redirect_branch_is_br = false;
  bool redirect_branch_is_rvc = false;
  bool redirect_branch_edge_inst = false;
  std::uint8_t redirect_branch_pc_lob = 0;
  std::uint8_t redirect_branch_pc_sel = PC_PLUS4;
  std::uint8_t redirect_branch_cfi_type = 0;
  std::int32_t redirect_branch_target_offset = 0;
  std::uint64_t redirect_branch_jalr_target = 0;
};

/** Inputs owned by the neighboring complete-chip models.
  *
  * This is deliberately a subsystem boundary rather than a collection of
  * Verilator taps.  FrontendState will produce `fetch`; MemoryState will
  * produce the cacheable completion, request readiness, ordering and DTLB
  * result.  The diagnostic reuse audit may fill the same structure from RTL
  * while those producers are being brought up, but SystemGuider never does.
  */
struct BackendInputs {
  bool reset = false;
  // False while the neighboring subsystem producers are not connected.  This
  // keeps an honestly unmodeled backend from consuming producer time or
  // evolving plausible-looking state that might later be mistaken for live
  // coverage.  The diagnostic reuse audit and the future FrontendState set it
  // true on every non-reset edge.
  bool run = false;
  std::uint64_t boot_pc = 0;

  // Fetchpacket payload wires are meaningful even when `fetch_offered` is
  // false: BOOM's rename-stage payload register can sample the held wires.
  bool fetch_offered = false;
#if defined(CHISA_WIDE_MODEL)
  // The dequeue row, unpacked and decoded by the frontend handoff
  // (FrontendHandoff::uops; slot 0 is the historical `fetch`).  The shared
  // DecodeUnit interrupt (decode.scala:511) is applied by the edge to its
  // own copy of every offered uop.
  const MicroOp* fetch_group = nullptr;
  bool decode_interrupt = false;
  std::uint64_t decode_interrupt_cause = 0;
#else
  MicroOp fetch{};
  // Dequeue group (slot 0 duplicates fetch/fetch_offered; slots 1.. exist at
  // CORE_WIDTH>1 and are dead on the Small configuration).
  std::array<MicroOp, boomcfg::MAX_CORE_WIDTH> fetch_g{};
#endif
  std::array<bool, boomcfg::MAX_CORE_WIDTH> fetch_offered_g{};

  components::BoomUncachedCompletion cacheable_response{};
  components::BoomUncachedCompletion cacheable_nack{};
  components::BoomUncachedCompletion hella_response{};
  components::BoomUncachedCompletion hella_nack{};
  bool dmem_req_ready = true;
  bool dmem_ordered = true;
  bool dmem_release_valid = false;
  std::uint64_t dmem_release_address = 0;

  bool dtlb_passthrough = false;
  bool dtlb_req_ready = true;
  // RegNext(dtlb.io.miss_rdy), distinct from the NBDTLB request port's
  // permanently asserted ready signal.
  bool dtlb_miss_ready_registered = true;
  bool dtlb_resp_miss = false;
  bool dtlb_resp_uncacheable = false;
  bool dtlb_resp_pf_ld = false;
  bool dtlb_resp_pf_st = false;
  bool dtlb_resp_ae_ld = false;
  bool dtlb_resp_ae_st = false;
  std::uint64_t dtlb_resp_paddr = 0;
  // PRE value of the compiled full-chip artifact's mem_tlb packed bit.  It
  // is separate from the current EXE response above because the LCAM search
  // consumes the registered value from the preceding cycle.
  bool mem_tlb_uncacheable_for_lcam = false;

  bool wfi_wakeup = false;

  // PTW-facing HellaCache wires.  The request payload is current-cycle s0;
  // kill/data are the independently timed s1/s2 wires from the sidecar.
  components::SmallHellaCacheRequest hella_request{};
  std::uint64_t hella_s1_data = 0;
  bool hella_s1_kill = false;
  bool hella_s2_kill = false;

#if defined(BOOM_GUIDER_FP)
  // Cycle-start response of the extracted inner FPU.  The hot model owns the
  // wrapper uop/valid pipe and consumes this payload only when that wrapper
  // reaches its writeback stage.  Keeping a connected bit preserves the
  // legacy core-only SoftFloat fallback.
  bool fpu_response_connected = false;
  bool fpu_response_valid = false;
  std::uint64_t fpu_response_data = 0;
  bool fpu_response_data_bit64 = false;
  std::uint8_t fpu_response_flags = 0;
  bool fdiv_response_connected = false, fdiv_response_valid = false;
  bool fdiv_response_data_bit64 = false, fdiv_ready_div = false, fdiv_ready_sqrt = false;
  std::uint64_t fdiv_response_data = 0;
  std::uint8_t fdiv_response_flags = 0;
#endif

  // Registered FTQ get_pc(0) response visible to the jump unit this cycle.
  bool ftq0_next_val = false;
  std::uint64_t ftq0_pc = 0;
  std::uint64_t ftq0_next_pc = 0;
  bool ftq0_cfi_valid = false;
  std::uint8_t ftq0_cfi_idx = 0;
  bool ftq0_start_bank = false;

  // Registered FTQ get_pc(1) response for the later b2 redirect/history path.
  // The jump/CSR ALU itself consumes port 0.
  bool ftq1_next_val = false;
  std::uint64_t ftq1_pc = 0;
  std::uint64_t ftq1_next_pc = 0;
  bool ftq1_cfi_valid = false;
  std::uint8_t ftq1_cfi_idx = 0;
  bool ftq1_start_bank = false;
};

enum class BackendCompletionSource : std::uint8_t {
  None,
  CacheableDcache,
  UncachedDebug,
};

inline constexpr const char* backend_completion_source_name(
    BackendCompletionSource source) {
  switch (source) {
    case BackendCompletionSource::None: return "none";
    case BackendCompletionSource::CacheableDcache: return "dcache";
    case BackendCompletionSource::UncachedDebug: return "uncached";
  }
  return "unknown";
}

/** The three faces of the memory-completion seam consumed by the LSU.
  *
  * `candidate_*` is the output selected by cacheable/uncached arbitration.
  * `*_branch_killed` and `*_flush_killed` are the hot-core qualifiers.
  * `response`/`nack` is the transaction the LSU actually sees.  Diagnostics
  * must compare the RTL consumer interface with this last face, never with a
  * raw producer candidate. */
struct BackendCompletionBoundary {
  BackendCompletionSource source = BackendCompletionSource::None;
  components::BoomUncachedCompletion candidate_response{};
  components::BoomUncachedCompletion candidate_nack{};
  components::BoomUncachedCompletion response{};
  components::BoomUncachedCompletion nack{};
  bool response_branch_killed = false;
  bool response_flush_killed = false;
  bool nack_branch_killed = false;
  bool nack_flush_killed = false;
};


}  // namespace chisa::boom_system
