#pragma once

#if (defined(BOOM_GUIDER_CFG_LARGEBOOM_RC) || defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)) && !defined(CHISA_WIDE_MODEL)
#error "Large requires the new native core/frontend/oracle build; legacy fallback is forbidden."
#endif

// ==========================================================================
// SystemGuider — the microarchitecture reference model for the complete
// RepCut `TestHarness` (SmallBoomConfig and, later, Large/Mega).
//
// Scope, and what makes this different from guiders/boom
// -----------------------------------------------------
// The archived core-only guider consumed its environment: the harness handed
// it the fetch stream the DUT had actually accepted, memory answered in a
// fixed two cycles with one request in flight, and there was no FPU, no VM,
// no cache, no interconnect.  Under the complete TestHarness every one of
// those is inside the design and must be *predicted*:
//
//   - the fetch stream is produced by frontend + TAGE-L + I-cache;
//   - memory latency is derived from D-cache hit/miss, MSHR occupancy, TLB
//     and PTW state, then TileLink and AXI queueing -- it is not a constant;
//   - the debug module and DTM are part of the DUT, so the boot path through
//     DMI is modeled, not simulated away.
//
// Every selected oracle needs independently maintained source state. Relaxed
// inactive payload precision does not disable sampling or state transitions.
// The consumer owns comparison policy: experiments can record signal
// mismatches and continue to architectural validation while retaining the
// real RTL recomputation and comparison cost.
//
// Boundary discipline (docs/GUIDER_PARADIGM.md section 1)
// ------------------------------------------------------
//  1. Externalized storage is not modeled.  CHISA owns the AXI RAM and the
//     other large arrays as chronological state computed by the RTL kernel, so
//     this model predicts protocol and timing registers, never memory data
//     that the kernel already holds.
//  2. Control state is modeled bit-exactly: queue pointers, arbiter grants,
//     beat counters, coherence trackers, cache and TLB state machines, and the
//     whole out-of-order backend.
//  3. Functional datapaths are computed once in C, not replicated as pipeline
//     structure.  Timing is carried separately by explicit delay lines.
//
// The model never reads the DUT.  Sampling RTL state and feeding it back as a
// prediction is replay, not production, and the manifest audit refuses to
// count it.  The only thing crossing the boundary is the comparison itself.
//
// Two single-sided tools live here and are deliberately distinct from probes:
//   - watchpoints (WP_LOG / WP_ASSERT) print or assert inside a step;
//   - sentinels are invariants over model state that report but never feed
//     back.  Sentinels catch the model contradicting *itself*, which probes
//     structurally cannot see: there is no RTL signal to compare against.
// ==========================================================================

#include "sample_placement.h"
#include "worker_protocol.h"
#include <atomic>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "../boom_model/common/backend_contract.h"

#if defined(CHISA_WIDE_MODEL)
#include "../boom_model/wide/backend.h"
#else
#include "../boom_model/small/backend.h"
#endif

#include "native_fabric.h"
#include "pmp_permissions.h"
#include "components/axi_chain_mirror.h"
#include "components/boom_uncached_path.h"
#include "components/small_pma.h"
#include "components/small_tlb.h"
#include "frontend_state.h"
#include "memory_state.h"
#include "sparse_backing_memory.h"

namespace chisa::boom_system {
#if defined(CHISA_WIDE_MODEL)
using SystemBackend = boom_model::wide::Backend;
#else
using SystemBackend = boom_model::Backend;
#endif

/** Model-side view of the exact fesvr DTM outputs.
  *
  * The implementation used by the lockstep runner owns a second `dtm_t` and
  * never samples the RTL-facing instance.  Keeping this narrow interface in
  * the guider avoids making component tests link fesvr while preserving the
  * important boundary: the transport is supplied once at construction and
  * advanced for the full run only from feedback predicted by the model.
  *
  * The Bootstrap names are retained for source compatibility with the first
  * activation-only producer; the contract is no longer activation-only. */
struct DebugBootstrapOutputs {
  bool req_valid = false;
  uint32_t req_addr = 0;
  uint32_t req_op = 0;
  uint32_t req_data = 0;
  bool resp_ready = false;
  uint32_t exit = 0;
};

struct DebugBootstrapFeedback {
  bool req_ready = false;
  bool resp_valid = false;
  uint32_t resp = 0;
  uint32_t data = 0;
};

class DebugBootstrapTransport {
 public:
  virtual ~DebugBootstrapTransport() = default;
  virtual DebugBootstrapOutputs outputs() const = 0;
  virtual void advance(bool reset,
                       const DebugBootstrapFeedback& feedback) = 0;
};

/** Everything the model needs from outside the design.
  *
  * Deliberately tiny.  A reference model that needs per-cycle input from the
  * DUT is a replay harness; this one is handed the workload once and then runs
  * free, exactly as the live sidecar producer will have to. */
struct BoundaryConfig {
  const char* image_path = nullptr;  // flat workload image, as fesvr loads it
  uint64_t load_address = 0x80000000ull;
  int argc = 0;      // the same plusargs the RTL sees, so both agree on
  char** argv = nullptr;  // +max-cycles, +verbose and friends
  uint64_t reset_cycles = 12;  // externally scheduled initial reset interval
  DebugBootstrapTransport* debug_bootstrap = nullptr;  // non-owning
  // The runtime supplies the worker executors; DTM/backend advancement
  // remains on the calling thread.
  bool cooperative_workers = false;
};

/** Result of advancing the model one chronological cycle. */
struct StepResult {
  bool ok = true;             // false once the model has detected it is lost
  const char* failure = "";   // why, when ok is false
};

// --------------------------------------------------------------------------
// Subsystem state.
//
// Each struct mirrors one RTL subsystem, field by field, and every field
// carries its RTL width and the scala file:line it comes from.  They are
// deliberately plain aggregates: the model's step order is the only thing that
// encodes timing, so state must not hide behaviour behind accessors.
//
// These are declared empty until the corresponding subsystem lands.  An empty
// struct is honest -- the probe registry reports its streams as UNMODELED --
// whereas a struct full of plausible-looking zeroes is not.
// --------------------------------------------------------------------------

/** TestHarness-level reset state that remains after CHISA's oracle selection.
  *
  * The exact SimDTM used by this locked harness never sets DMCONTROL.ndmreset:
  * every DMCONTROL write in fesvr/dtm.cc constructs a value from dmactive,
  * halt/resume and hart selection, and bit 1 is never introduced.  The RTL
  * register below is the one-cycle shell copy of that bit.  It is kept as
  * explicit model state instead of returning a naked constant so probes and
  * sentinels document the inductive reason it is zero. */
struct ResetClockState {
  bool ndmreset_delay_observed = false;
  bool ndmreset_delay_state = false;
};

/** External-interrupt state at the PLIC boundary.
  *
  * This TestHarness ties its two external interrupt inputs to UInt<2>(0).
  * After the synchronizer reset, neither PLIC gateway can create a request.
  * A software claim can only clear a pending bit, so both bits remain zero by
  * induction for every workload, including workloads that access the PLIC. */
struct InterruptState {
  bool plic_pending_0_observed = false;
  bool plic_pending_1_observed = false;
  bool plic_pending_0_state = false;
  bool plic_pending_1_state = false;
  std::uint8_t clint_source_state = 0;
};

/** Debug module plus the DMI crossing.  The exact fesvr `dtm_t` is reused, not
  * reimplemented; what the model owes is the shadow state that lets it predict
  * DMI feedback before the RTL evaluates, since the reference path's captured
  * feedback is not available to a producer. */
struct DebugState {
  // Three counters survive oracle selection even though this elaboration can
  // only issue one-beat DMI TileLink transactions.  Their update equations
  // therefore collapse to zero for every legal request, not merely for the
  // current Dhrystone trace.  Keeping them as named fields documents why the
  // model can predict them without looking at the DUT.
  uint8_t bypass_stall_beats_left = 0;  // Edges.scala 228, TLBusBypassBar
  uint8_t error_arbiter_beats_left = 0; // Arbiter.scala 87, TLError
  uint8_t xbar_beats_left = 0;          // Arbiter.scala 87, DMI TLXbar

  // TLError.idle resets to one, but the generated C++ object is zero before
  // the first reset edge.  `error_idle_observed` is the cycle-start value the
  // PRE tap sees; `error_idle_state` is the value carried to the next cycle.
  // The exact SimDTM only emits mapped debug-register addresses, so the error
  // slave never accepts a request and idle remains one after reset.
  bool error_idle_observed = false;
  bool error_idle_state = false;

  // Activation starts in dmOuter with the first exact fesvr request: a write
  // of DMCONTROL.dmactive.  These observed/state pairs distinguish the PRE
  // register value from the value carried across the edge.
  bool dmactive_observed = false;
  bool dmactive_state = false;
  bool bypass_reg_observed = false;
  bool bypass_reg_state = false;
  bool clock_en_observed = false;
  bool clock_en_state = false;

  // `dmInner._T_1` is not `!DMCONTROLReg_dmactive`; it is the inverse of the
  // inner-domain synchronizer's final stage and therefore changes six cycles
  // later on this reset/clock sequence.
  bool inner_dmactive_inactive = true;

  // AsyncResetSynchronizerShiftReg stages are numbered in the same reverse
  // order as the generated RTL: input enters sync_2 and leaves sync_0.
  bool reset_sync_2 = false;
  bool reset_sync_1 = false;
  bool reset_sync_0 = false;
  bool top_dmactive_ack_sync_2 = false;
  bool top_dmactive_ack_sync_1 = false;
  bool top_dmactive_ack_sync_0 = false;
  bool outer_dmactive_ack_sync_2 = false;
  bool outer_dmactive_ack_sync_1 = false;
  bool outer_dmactive_ack_sync_0 = false;
  bool inner_dmactive_sync_2 = false;
  bool inner_dmactive_sync_1 = false;
  bool inner_dmactive_sync_0 = false;
  bool bootstrap_complete = false;

  // Debug-to-tile interrupt crossing: IntSyncCrossingSource's AsyncResetRegVec
  // in the (gated) debug clock domain, then the tile's three-stage
  // NonSyncReset synchronizer.  The core samples int_sync_0; total launch
  // latency from DMCONTROL.haltreq is four edges, matching the observed ten
  // cycles from sync_0 rise to the 0x800 redirect once decode attach and the
  // ROB flush are added.
  bool int_source_reg = false;
  bool int_sync_2 = false;
  bool int_sync_1 = false;
  bool int_sync_0 = false;
};

// --------------------------------------------------------------------------

/** Cycle-start snapshots for the core bring-up probe slice.
  *
  * Probes compare against the RTL's PRE register tap, i.e. the value a
  * register holds at the start of the evaluated cycle.  Component state after
  * SystemGuider::step is the post-edge value, so these fields are filled at
  * the end of each step and read by the next cycle's probes -- the same
  * observed/state split the debug shell uses, starting from the generated
  * simulator's zero-initialized image. */
struct CoreBringupSnapshots {
  bool int_sync_0 = false;
  bool s1_valid = false;
  std::uint64_t s1_vpc = 0;
  std::uint64_t s2_ppc = 0;
  std::uint8_t fb_head = 0;
  std::uint8_t fb_tail = 0;
  bool fb_maybe_full = false;
  std::uint8_t ftq_enq_ptr = 0;
  bool icache_s2_valid = false;
  bool icache_s2_hit = false;
  std::uint8_t rob_head = 0;
  std::uint8_t rob_tail = 0;
};

class SystemGuider {
 public:
  explicit SystemGuider(const BoundaryConfig& config);
  ~SystemGuider();
  SystemGuider(const SystemGuider&) = delete;
  SystemGuider& operator=(const SystemGuider&) = delete;

  /** Frontend evaluation placement (SYSMODEL_FRONTEND_THREAD).
    *
    * Off: the frontend evaluates after the backend edge, as written below.
    * Check: the frontend evaluates before the backend edge from a preview of
    * the backend's frontend-facing control, on this thread; the preview is
    * compared with the real control afterwards and a difference re-evaluates
    * serially.  Threaded: the same, with the evaluation and the commit on a
    * worker thread (SYSMODEL_FRONTEND_CPU pins it).  All three commit the
    * same evaluation; the published oracles do not depend on the mode. */
  enum class FrontendThreading { Off, Check, Threaded };
  struct FrontendThreadStats {
    std::uint64_t cycles = 0, previewed = 0, fallbacks = 0;
    std::uint64_t control_mismatches = 0, feedback_mismatches = 0;
    std::uint64_t wait_evaluate_ticks = 0, wait_commit_ticks = 0;
    std::uint64_t evaluate_ticks = 0, commit_ticks = 0;
    std::uint64_t roi_cycles = 0;  // steps since the last reset_phase_counters (the tick divisor)
  };
  FrontendThreading frontend_threading() const { return frontend_threading_; }
  const FrontendThreadStats& frontend_thread_stats() const { return frontend_thread_stats_; }
  // Exactly one runtime executor per role. Each call performs at most one
  // ready phase and never waits for another role.
  bool try_frontend_task();
  bool try_memory_task();
  using WaitTask = bool (*)(void*);
  void set_wait_task(WaitTask task, void* context) { wait_task_ = task; wait_task_context_ = context; }

  /** Advance exactly one chronological cycle.
    *
    * The body's statement order is the clock-edge evaluation order and is the
    * only place timing is expressed; reordering it is a bug, not a
    * refactoring.  Cycle-start snapshots are taken first so that logic reading
    * a registered value sees the pre-edge one, which is the single most
    * common source of divergence in this codebase's history. */
  /** DMI traffic of the most recent step, for live-sidecar cycle records. */
  struct DmiSnapshot {
    bool req_valid = false;
    std::uint32_t req_addr = 0;
    std::uint32_t req_op = 0;
    std::uint32_t req_data = 0;
    bool resp_ready = false;
    bool req_ready = false;
    bool resp_valid = false;
    std::uint32_t resp_response = 0;
    std::uint32_t resp_data = 0;
    std::uint32_t exit = 0;
    bool reset = false;
  };
  const DmiSnapshot& last_dmi() const { return last_dmi_; }

  /** DTLB boundary values consumed by the most recent backend step.
    * Diagnostic only: this records the pre-step AGU view before BoomGuider
    * advances, so a runner can compare it with the RTL PRE packed state
    * without re-evaluating the lookup at a different pipeline phase. */
  struct DtlbSnapshot {
    bool agu_valid = false;
    bool candidate_valid = false;
    std::uint64_t candidate_vaddr = 0;
    std::uint8_t candidate_size = 0;
    std::uint8_t candidate_cmd = 0;
    bool pma_legal = false;
    bool pma_cacheable = false;
    bool response_uncacheable = false;
    bool lcam_packed_pre = false;
    bool lcam_packed_next = false;
  };
  const DtlbSnapshot& last_dtlb() const { return last_dtlb_; }

  /** Exact cycle-start TLB -> PTW request contract consumed on the most
    * recent edge.  This is diagnostic state only; keeping the selected seam
    * here avoids re-evaluating a TLB or the generated PTW after both have
    * already committed their registers. */
  struct PtwBoundarySnapshot {
    std::array<protocol::PtwRequest, 3> requestors{};
    std::array<bool, 3> request_ready{};
    std::array<bool, 3> response_valid{};
    protocol::PtwMemoryRequest memory_request{};
    std::uint8_t state = 0;
    components::SmallTlbCycleInputs dtlb_input{};
    components::SmallTlbCycleOutputs dtlb_output{};
    std::uint8_t dtlb_state = 0;
  };
  const PtwBoundarySnapshot& last_ptw_boundary() const {
    return last_ptw_boundary_;
  }

  /** Exact cycle-start ITLB -> F1/F2 contract consumed on the most recent
    * edge.  In particular, the F2 payload is written even when s1_valid is
    * false, so keeping the raw lookup and the replay-selected response makes
    * invalid-bubble timing bugs visible without reading an RTL value. */
  struct ItlbBoundarySnapshot {
    components::SmallTlbCycleInputs input{};
    components::SmallFrontendTlbResponse raw_response{};
    components::SmallFrontendTlbResponse selected_response{};
    bool s1_valid = false;
    bool s1_is_replay = false;
    bool s1_is_sfence = false;
    std::uint64_t s1_vpc = 0;
  };
  const ItlbBoundarySnapshot& last_itlb_boundary() const {
    return last_itlb_boundary_;
  }

  /** AXI-chain register mirror (observer; components/axi_chain_mirror.h). */
  const components::AxiChainMirror& axi_mirror() const { return axi_mirror_; }
  /** Raw cycle-start candidate from the cacheable D-cache producer. */
  const components::SmallDcacheOutputs& last_dcache_candidate() const {
    static const components::SmallDcacheOutputs kNone{};
    return last_dcache_candidate_ != nullptr ? *last_dcache_candidate_ : kNone;
  }
  /** Selected and qualified transaction actually consumed by the LSU. */
  const BackendCompletionBoundary& last_memory_completion_boundary() const {
    static const BackendCompletionBoundary kNone{};
    return last_memory_completion_boundary_ != nullptr ? *last_memory_completion_boundary_ : kNone;
  }
  std::uint64_t last_lsu_resp_data() const { return last_lsu_resp_data_; }

  StepResult step();
#if defined(CHISA_WIDE_MODEL)
  const auto& retirement_events() const { return backend_.core().outputs().retired; }
#endif
  const auto& architectural_state() const {
    return backend_.core().architectural_state();
  }

  const auto& retirement_event() const {
    return backend_.core().retirement_event();
  }

  /** Called inside step() once this cycle's record is complete (after the
    * cycle-start sampling, before any component commits): the writer seals
    * the cycle's change list into its block from here. */
  // Predicted: the predicted lanes of the position (the core-side ones when a
  // memory worker publishes the memory-side ones); PredictedMemory: the
  // memory-side ones, from the memory worker after its commit.
  enum class PublishPhase : std::uint8_t { Registers, Predicted, PredictedMemory };
  using PublishFn = void (*)(void* context, const SystemGuider& model,
                             PublishPhase phase);
  void sample_placed(SamplePlacement placement);
  /** Image pre-copy: asked before a frontend commit is posted for the image
    * position the next step will publish into, or nullptr.  The committing
    * thread then copies the frontend's record runs there itself, and the
    * next step's publish skips them (see frontend_image_runs). */
  using ImagePrecopyFn = char* (*)(void* context);
#if defined(CHISA_MODEL_DIAGNOSTICS)
  using ImageSourceObserver = void (*)(void*, std::uint64_t, const unsigned char*, std::size_t, std::size_t);
  void set_image_source_observer(ImageSourceObserver fn, void* context) {
    image_source_observer_=fn; image_source_context_=context;
  }
  void observe_image_source(std::uint64_t cycle, const unsigned char* source,
                            std::size_t begin, std::size_t bytes) const {
    if (image_source_observer_) image_source_observer_(image_source_context_,cycle,source,begin,bytes);
  }
#endif
  void set_image_precopy_hook(ImagePrecopyFn fn, void* context) {
    image_precopy_fn_ = fn;
    image_precopy_context_ = context;
  }
  struct ImageRun { std::size_t begin, end; };
  /** The record byte ranges the frontend writes (64-byte aligned runs of the
    * generated layout); empty on the Small build. */
  static const ImageRun* frontend_image_runs(std::size_t& count);
  /** The image position the frontend's runs were already copied into for
    * this step's publish, or nullptr. */
  const char* frontend_image_runs_copied_to() const;
  /** The record runs already copied into image position `destination` by
    * the frontend and memory threads, sorted by offset (at most nine). */
  const ImageRun* precopied_image_runs(const char* destination, std::size_t& count) const;
  void set_publish_hook(PublishFn fn, void* context, bool image_owner_copy = false) {
    publish_fn_ = fn;
    publish_context_ = context;
    publish_image_owner_copy_ = image_owner_copy;
  }

  /** Loading/warm-up still advances every modeled component, but no oracle
    * buffer is consumed until the target ROI begins. */
  void set_oracle_sampling_enabled(bool enabled);

#ifdef CHISA_PHASE_TIMERS
  /** Per-phase TSC accumulators (producer benchmark flavor only): the
    * pre-step sampling pass, the post-edge fabric lookahead, and the whole
    * step().  Model time is step minus the other two; the bench calibrates
    * ticks to nanoseconds against its own wall clock. */
  struct StepPhaseCounters {
    std::uint64_t sample_tsc = 0;
    std::uint64_t lookahead_tsc = 0;
    std::uint64_t step_tsc = 0;
    // The frontend's share of the step: evaluate + commit + FTQ port capture
    // (frontend_tsc) and the Frontend-placement sampling (also inside
    // sample_tsc).  Together they bound what a frontend thread could take.
    std::uint64_t frontend_tsc = 0;
    std::uint64_t frontend_sample_tsc = 0;
    // The core's step (BackendState::step) and the sampling split by
    // placement (PreStep, Core, Frontend, Memory, End; all inside sample_tsc).
    std::uint64_t backend_tsc = 0;
    std::uint64_t sample_by_placement_tsc[5] = {};
    // The remaining step segments: before the cycle-start sampling (debug
    // shell, memory outputs, offers, cold fixed point, fabric), between the
    // Registers publish and the core step (TLB/PTW previews, backend inputs),
    // after the core step up to the frontend evaluation (PTW/DTLB/FP commits,
    // memory inputs), and the tail after the Frontend sampling up to the End
    // sampling (DTM, halt, hybrid/coherent/debug commits, AXI, reset).
    std::uint64_t pre_tsc = 0;
    std::uint64_t tlbptw_tsc = 0;
    std::uint64_t postbackend_tsc = 0;
    std::uint64_t tail_tsc = 0;
    // Finer splits: 0 backend-input assembly, 1 DTLB/ITLB/PTW previews,
    // 2 frontend preview + request, 3 memory/coherent commit, 4 frontend
    // commit wait + finish.
    std::uint64_t sub_tsc[12] = {};  // 8..11: frontend tail, head publish, memory prepare, DTM
    std::uint64_t steps = 0;
  };
  const StepPhaseCounters& phase_counters() const { return phase_counters_; }
  void reset_phase_counters() {
    phase_counters_ = StepPhaseCounters{};
    memory_wait_ticks_ = memory_fabric_wait_ticks_ = 0;
    memory_fabric_wait_count_ = memory_fabric_wait_max_ = 0;
    fabric_join_arrival_ticks_ = fabric_signal_after_post_ticks_ = fabric_join_count_ = 0;
    memory_stats_reset_pending_ = true;  // the next memory request carries it to the worker
    frontend_thread_stats_.wait_evaluate_ticks = frontend_thread_stats_.wait_commit_ticks = 0;
    frontend_thread_stats_.evaluate_ticks = frontend_thread_stats_.commit_ticks = 0;
    frontend_thread_stats_.roi_cycles = 0;
    frontend_stats_reset_pending_ = true;  // the next frontend evaluate request carries it
  }
#endif

  uint64_t cycle() const { return cycle_; }
  bool reset_asserted() const { return reset_asserted_; }

  /** True after the external DMI transport has deactivated dmactive and all
    * model-visible debug clock crossings have reached their idle fixed point.
    * The transport itself is checked by its owner because BoundaryConfig
    * deliberately stores only the minimal abstract interface. */
  bool debug_roi_quiescent() const;

  /** The nine Debug Module oracle streams, derived from the hand-written
    * uncached path's own registers (validated shadow-exact against the
    * generated dmOuter/dmInner sidecars before those were removed). */
  enum class DebugStream : unsigned {
    OuterXbarReadysMask, OuterASourceWidxBin, OuterDSinkValidReg,
    OuterInnerCtrlReadyReg, InnerCtrlState, InnerCtrlSinkValidReg,
    InnerDSourceReadyReg, InnerASinkCdcReg, InnerASinkValidReg, InnerDSourceWidxBin, Count
  };
  std::uint64_t debug_stream(DebugStream stream) const;
  // Reused every cycle by step(): see FrontendState::evaluate_into.
  alignas(64) FrontendEvaluation frontend_evaluation_{};
  // The calling thread fills frontend_input_main_ / frontend_feedback_preview_main_;
  // with a frontend worker only the 64-byte chunks that changed are copied
  // into the worker-read pair before the evaluate request (an idle input
  // then costs no cache-line transfer), and the late links reach the worker
  // through one line of their own, patched into the evaluation by the worker.
  alignas(64) FrontendInputs frontend_input_main_{};
  BackendFrontendFeedback frontend_feedback_preview_main_{};
  alignas(64) FrontendInputs frontend_input_{};
  alignas(64) BackendFrontendFeedback frontend_feedback_preview_{};
  struct FrontendLateLinks {
    bool fetch_ready = false;
    std::uint8_t handoff_index = 0;    // the FrontendHandoff buffer the commit fills
    char* image_runs_destination = nullptr;  // where to copy the frontend's record runs after the commit
    BackendFrontendFeedback feedback{};
    BackendFrontendControl control{};  // the actual links; the worker checks the preview against them
  };
  alignas(64) FrontendLateLinks frontend_late_links_{};
  // The committed frontend's outputs for the next edge (FrontendHandoff):
  // this thread reads [frontend_handoff_read_] while whoever commits fills
  // the other buffer; the swap happens when the commit is joined.
  alignas(64) std::array<FrontendHandoff, 2> frontend_handoff_{};
  unsigned frontend_handoff_read_ = 0;
  bool frontend_handoff_swap_pending_ = false;
  // A commit posted to the worker and not yet joined.  It is joined at the
  // start of the next step, so the worker's late commit overlaps this
  // thread's memory commit and publication instead of being waited for.
  bool frontend_commit_pending_ = false;
  std::uint64_t frontend_commit_cycle_ = 0;
  void finish_frontend_deferred();
  /** Joins the frontend worker's outstanding commit, if any, and adopts its
    * handoff.  step() calls it first; anything that reads frontend state
    * between steps with SYSMODEL_FRONTEND_THREAD set must call it too. */
  void synchronize_frontend();
  /** Joins the frontend worker's copy of its record runs into the image
    * position after the last committed cycle's (it follows the commit
    * signal): a harness calls it before releasing that position. */
  void synchronize_frontend_runs();
  /** Joins the memory worker's outstanding cycle, if any: its post-edge
    * commits, its Predicted publish of that cycle's image position and the
    * next cycle's pre-edge phase.  step() calls it; a harness calls it before
    * releasing the position.  The writer's publish context is not held past
    * the step that posted it: the worker keeps its own copy of the hook. */
  void synchronize_memory_side() { synchronize_memory_fabric(); }
  bool memory_worker_on() const { return memory_worker_ != nullptr; }
  // 1: the worker runs the Frontend sampling placement after its commit
  // (no export ring); 0: the calling thread does; -1: not decided yet.
  alignas(64) std::int8_t frontend_worker_samples_ = -1;
  FrontendThreading frontend_threading_ = FrontendThreading::Off;
  // SYSMODEL_FRONTEND_THREAD=3: the worker also applies the evaluation-only
  // half of the commit before the backend edge is verified.  A preview
  // mismatch can then no longer be repaired by re-evaluation and aborts.
  bool frontend_early_commit_ = false;
  bool frontend_memory_pipeline_ = true;
  alignas(64) FrontendThreadStats frontend_thread_stats_{};
  struct FrontendWorker;
  alignas(64) std::unique_ptr<FrontendWorker> frontend_worker_;
  // Core record publication (wide model): Inline writes the record inside the
  // step as before; Deferred replays the marks right after the step on this
  // thread (equivalence mode); Threaded replays them on a worker while the
  // memory side of the cycle runs, joined before the End placement.
  enum class RecordPublication { Inline, Deferred, Threaded };
  alignas(64) RecordPublication record_publication_ = RecordPublication::Inline;
  bool cut_lanes_ = true;   // partition-cut lanes published (SYSMODEL_CUT_LANES=0 turns them off)
  bool cut_lanes() const { return cut_lanes_; }
  // CLINT.scala:69-70 with RTC.scala's 100-cycle tick counter: mtime as the
  // partitioned kernels read it across the uncore cut.
  std::uint8_t rtc_counter_ = 0;
  std::uint64_t clint_time_ = 0;
  std::uint64_t clint_time() const { return clint_time_; }
  struct RecordWorker;
  std::unique_ptr<RecordWorker> record_worker_;
  std::uint64_t record_wait_ticks_ = 0, record_cycles_ = 0;
  std::uint64_t record_posted_cycle_ = 0;  // cycle_ at the post; cycle_ has advanced by the join
  BackendInputs backend_input_{};
  alignas(64) mutable components::BoomUncachedPath::DebugHandOracles debug_oracles_{};
  mutable bool debug_oracles_valid_ = false;

  const ResetClockState& reset_clock() const { return reset_clock_; }
  const InterruptState& interrupts() const { return interrupts_; }
  const DebugState& debug() const { return debug_; }
  const NativeFabric& fabric() const { return fabric_; }
  const FrontendState& frontend() const { return frontend_; }
  const MemoryState& memory() const { return memory_; }

  const SystemBackend& backend() const { return backend_; }

  const components::SmallDataTlb& dtlb() const { return dtlb_; }
  /** LSU's two RegNext(dtlb.io.miss_rdy) copies.  The source is the
    * cycle-start NBDTLB state, so this member is advanced only after that
    * cycle has been evaluated. */
  const bool& dtlb_miss_ready_registered() const {
    return dtlb_miss_ready_registered_;
  }
  const SparseBackingMemory& backing_memory() const { return backing_memory_; }
  void enable_dram_access_capture(bool enabled) {
    capture_dram_access_ = enabled;
  }
  const protocol::AxiRamAccess& last_dram_access() const {
    return last_dram_access_main_;  // this step's, copied when the memory side is joined
  }
  const CoreBringupSnapshots& bringup() const { return bringup_; }

  /** Invariants over model state alone.  Diagnostic only: a sentinel never
    * feeds a value or a decision back into the model, so enabling them cannot
    * change what the model predicts.  Empty vector means all hold. */
  std::vector<std::string> sentinel_failures() const;

 private:
  alignas(64) DmiSnapshot last_dmi_{};
  DtlbSnapshot last_dtlb_{};
  PtwBoundarySnapshot last_ptw_boundary_{};
  ItlbBoundarySnapshot last_itlb_boundary_{};
  // Points into memory_output_ (the outputs of the last step); null before
  // the first step.
  const components::SmallDcacheOutputs* last_dcache_candidate_ = nullptr;
  // Points at the backend's own record of the last completion (it outlives
  // every reader); null before the first step.
  const BackendCompletionBoundary* last_memory_completion_boundary_ = nullptr;
  alignas(64) MemoryStateOutputs memory_output_{};
  components::AxiChainMirror axi_mirror_{};
  alignas(64) components::SmallDataTlb dtlb_{};
  bool dtlb_miss_ready_registered_ = false;
  std::uint64_t last_lsu_resp_data_ = 0;

  uint64_t cycle_ = 0;
  uint64_t reset_cycles_ = 12;
  bool reset_asserted_ = true;
  bool core_live_ = false;  // SYSMODEL_CORE_LIVE bring-up gate
  // Immutable worker controls must not share lines with the producer's
  // per-cycle counters, request bookkeeping, or changing publish context.
  alignas(64) bool oracle_sampling_enabled_ = true;
  alignas(64) PublishFn publish_fn_ = nullptr;
  void* publish_context_ = nullptr;
  bool publish_image_owner_copy_ = false;
  ImagePrecopyFn image_precopy_fn_ = nullptr;
#if defined(CHISA_MODEL_DIAGNOSTICS)
  ImageSourceObserver image_source_observer_=nullptr;
  void* image_source_context_=nullptr;
#endif
  void* image_precopy_context_ = nullptr;
  // Memory side of the cycle (see memory_pre_phase / memory_commit_phase):
  // the DMI request consumed, the tile inputs (pre-edge fields set by the
  // pre phase, backend-derived fields set after the backend edge), the fabric
  // evaluation and its feedback, and the resolved fabric outputs.
  // memory_pre_outputs: the DMI request and the memory-side outputs arriving
  // in cycle `cycle`; memory_pre_fabric: the tile fabric view, the cold
  // uncore evaluation with its feedback, the pre-edge memory-run lanes and
  // the memory runs' copy into `image_runs_destination` (when given);
  // memory_commit_phase: the post-edge commits and the post-edge memory-run
  // lanes.  A memory worker runs commit(t) then pre(t+1); without one the
  // calling thread runs commit(t) after its backend edge and pre(t) at the
  // start of step t.
  void memory_pre_outputs(bool reset, const DebugBootstrapOutputs& dtm);
  void memory_pre_fabric(bool reset, std::uint64_t cycle, unsigned frontend_handoff_index,
                         char* image_runs_destination);
  bool try_memory_image_copy(std::uint64_t cycle, char* destination);
  void memory_commit_phase(bool reset);  // both halves
  void memory_commit_tile();             // D-cache and uncached path take the edge
  void memory_commit_fabric(bool reset); // fabric commit, cold uncore, AXI mirror
  MemoryState::HybridCommitCarry memory_commit_carry_{};
  struct MemoryRequest {
    std::uint64_t cycle = 0;
    bool reset = false, reset_next = false, frontend_posted = false;
    std::uint8_t frontend_handoff_index = 0;
    char* image_runs_destination = nullptr;
    DebugBootstrapOutputs dtm_next{};
    bool reset_stats = false;  // the worker zeroes its phase statistics (ROI start)
    // The publish hook of the posting step: the memory-side predicted lane of
    // that step's image position goes through it.
    PublishFn publish_fn = nullptr;
    void* publish_context = nullptr;
  };
  void memory_commit_step(const MemoryRequest& request);       // commit_ptw + both halves
  void memory_commit_tile_step(const MemoryRequest& request);  // commit_ptw + tile half
  struct MemoryWorker;
  alignas(64) std::unique_ptr<MemoryWorker> memory_worker_;
  alignas(64) bool memory_pending_ = false;        // a memory request posted, its fabric phase not yet joined
  bool memory_stats_reset_pending_ = false;
  bool frontend_stats_reset_pending_ = false;
  // Where the previous cycle's frontend commit copies (or copied) the
  // frontend's record runs: the worker's destination when posted, nullptr
  // when this thread committed inline.
  char* frontend_runs_destination_ = nullptr;
  bool frontend_runs_from_worker_ = false;
  std::uint64_t frontend_runs_cycle_ = 0;
  // The cycle whose pre-step sampling this thread completed: its record
  // writes for that cycle's image position are done (see memory_pre_fabric).
  RecordCopyGate record_copy_gate_{};
  bool memory_outputs_joined_ = false; // its outputs phase joined
  bool memory_pre_ready_ = false;      // a joined request left this step's pre phase behind
  // The frontend worker takes this cycle's I-cache fabric face itself, once
  // the memory worker's fabric phase of `frontend_icache_memory_cycle_` is
  // done (the calling thread does not wait for it before the backend edge).
  alignas(64) bool frontend_icache_from_memory_ = false;
  std::uint64_t frontend_icache_memory_cycle_ = 0;
  void wait_memory_fabric_for_frontend();
  bool memory_fabric_ready_for_frontend() const;
  void memory_publish_end();
  void synchronize_memory_outputs();
  void synchronize_memory_fabric();
  alignas(64) std::uint64_t memory_cycle_ = 0;
  char* memory_image_runs_destination_ = nullptr;  // where the pending request copies the memory runs
  std::uint64_t memory_image_runs_cycle_ = 0;
  void synchronize_memory();
  static const ImageRun* memory_image_runs(std::size_t& count);
  DebugBootstrapOutputs dtm_outputs_next_{};
  components::SmallTlbCycleInputs dtlb_state_input_{};
  protocol::AxiRamAccess last_dram_access_main_{};
  std::uint64_t memory_wait_ticks_ = 0, memory_fabric_wait_ticks_ = 0;
  bool cooperative_workers_ = false;
  WaitTask wait_task_ = nullptr;
  void* wait_task_context_ = nullptr;
  void wait_task_or_pause() const;
  std::uint64_t memory_fabric_wait_count_ = 0, memory_fabric_wait_max_ = 0;
  std::uint64_t fabric_join_arrival_ticks_ = 0, fabric_signal_after_post_ticks_ = 0, fabric_join_count_ = 0;
  DebugBootstrapOutputs dtm_outputs_{};
  MemoryStateInputs memory_input_{};
  components::SmallICacheMemoryPath::HybridEvaluation fabric_evaluation_{};
  components::SmallExternalManagerInputs manager_feedback_{};
  const components::SmallICacheMemoryPathOutputs* fabric_output_ = nullptr;
#ifdef CHISA_PHASE_TIMERS
  StepPhaseCounters phase_counters_{};
#endif
  bool lsu_exception_prev_ = false;  // RegNext(rob.io.flush.valid) for the D-cache
  // CSR.scala exposes data privilege through an uninitialized Reg(next=...).
  // Keep it separate from mstatus so PTW/DTLB see the preceding edge's value.
  std::uint8_t ptw_dprv_ = 0;
  // make_ptw_inputs() decodes ~30 CSR fields and 8 PMP masks; the result
  // only changes with the CSR/PMP/sfence/dprv/reset inputs, so it is kept
  // and rebuilt on change (the per-cycle requestor fields are set after).
  protocol::PtwInputs ptw_input_base_{};
  PmpPermissions pmp_permissions_;
  GuiderCSR ptw_input_csr_{};
  BackendFrontendControl ptw_input_sfence_{};
  std::uint8_t ptw_input_dprv_ = 0;
  bool ptw_input_reset_ = false;
  bool ptw_input_valid_ = false;
  // TestHarness extern-tap's lowered mem__v2_bank_0_3 bit 0.  In this locked
  // artifact the generated next-state expression stores io_resp.cacheable
  // at the slot whose manifest source is mem_tlb_uncacheable.  Preserve that
  // concrete artifact behavior locally; current EXE semantics remain normal.
  bool lsu_mem_tlb_packed_bit_ = false;
  DebugBootstrapTransport* debug_bootstrap_ = nullptr;

  ResetClockState reset_clock_;
  InterruptState interrupts_;
  DebugState debug_;
  alignas(64) NativeFabric fabric_;
  alignas(64) FrontendState frontend_;
  alignas(64) MemoryState memory_;

  alignas(64) SystemBackend backend_;
#if !defined(CHISA_WIDE_MODEL)
  chisa::boom_model::Image* image_ = nullptr;   // Small's write-through record
#endif

  // Cycle-0 image: the RTL registers are all zero before their first clock
  // edge (simulator initial state) while the model applies reset values at
  // construction. The constructed registers are kept here and handed back
  // right after the first step publishes the cycle-0 record.
#if !defined(CHISA_WIDE_MODEL)
  std::vector<std::uint8_t> boot_regs_snapshot_;
  bool boot_regs_pending_ = false;
#endif
  alignas(64) SparseBackingMemory backing_memory_;
  bool capture_dram_access_ = false;
  protocol::AxiRamAccess last_dram_access_{};
  CoreBringupSnapshots bringup_;
};

}  // namespace chisa::boom_system
