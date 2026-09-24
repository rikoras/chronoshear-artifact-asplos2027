#include "system_guider.h"
#include "phase_sub.h"
#if defined(CHISA_WIDE_MODEL)
#include "../boom_model/wide/system_publication.h"
#if defined(CHISA_LSU_PUBLICATION_PROBE)
#include "../boom_model/wide/oracle_bindings.h"
#endif
#endif

#include <atomic>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <pthread.h>
#include <sched.h>
#include <stdexcept>
#include <thread>
#include <x86intrin.h>

#include "../boom_model/common/watchpoint.h"
#include "../boom_model/common/diagnostic_monitor.h"

#include "model_bindings.h"
#include "system_probe.h"
#include "core_access.h"

namespace chisa::boom_system {
namespace {

// SmallBoomConfig reset vector: the boot ROM base plus the hang/boot offset.
constexpr std::uint64_t kSmallBootVector = UINT64_C(0x10040);
// rocket CSR.scala debug interrupt: non-maskable, cause bit 63 | 14.
constexpr std::uint64_t kDebugInterruptCause =
    (UINT64_C(1) << 63) | UINT64_C(14);
constexpr std::uint64_t kSingleStepInterruptCause = UINT64_C(1) << 63;

std::uint32_t pmp_mask(const GuiderCSR::PmpEntry& entry) {
  // rocket/PMP.scala:58-60. pmpGranularity is four bytes in SmallBoom.
  const std::uint64_t base =
      (static_cast<std::uint64_t>(entry.addr & UINT32_C(0x3fffffff)) << 1) |
      (entry.cfg_a & 1u);
  return static_cast<std::uint32_t>(
      ((base & ~(base + 1)) << 2) | UINT64_C(3));
}

protocol::PtwRequest make_ptw_request(
    const components::SmallTlbCycleOutputs& tlb) {
  protocol::PtwRequest result;
  result.valid = tlb.ptw_request_valid;
  result.payload_valid = tlb.ptw_request_payload_valid;
  // An idle requestor presents no payload the walker can observe; a fixed
  // vpn keeps the PTW sidecar's inputs equal across idle cycles so its
  // evaluation is skipped instead of re-run for every changing address.
  result.vpn = (result.valid || result.payload_valid) ? tlb.ptw_request_vpn : 0;
  return result;
}

/** The CSR fields make_ptw_inputs() reads (the PTW input cache key). */
bool ptw_csr_inputs_equal(const GuiderCSR& a, const GuiderCSR& b) {
  if (a.satp_mode != b.satp_mode || a.satp_ppn != b.satp_ppn ||
      a.debug != b.debug || a.cease != b.cease || a.wfi != b.wfi ||
      a.misa != b.misa || a.prv != b.prv || a.mstatus != b.mstatus ||
      a.custom_0 != b.custom_0)
    return false;
  for (std::size_t i = 0; i < 8; ++i) {
    const auto& x = a.pmp[i];
    const auto& y = b.pmp[i];
    if (x.cfg_l != y.cfg_l || x.cfg_a != y.cfg_a || x.cfg_x != y.cfg_x ||
        x.cfg_w != y.cfg_w || x.cfg_r != y.cfg_r || x.addr != y.addr)
      return false;
  }
  return true;
}

protocol::PtwInputs make_ptw_inputs(
    bool reset, const GuiderCSR& csr, std::uint8_t registered_dprv,
    const BackendFrontendControl& sfence) {
  protocol::PtwInputs result;
  result.reset = reset;
  result.ptbr_mode = csr.satp_mode;
  result.ptbr_asid = 0;  // SmallBoom has ASIdBits=0.
  result.ptbr_ppn = csr.satp_ppn;
  result.sfence_valid = sfence.sfence_valid;
  result.sfence_rs1 = sfence.sfence_rs1;
  result.sfence_rs2 = sfence.sfence_rs2;
  result.sfence_address = sfence.sfence_addr;
  result.sfence_asid = false;

  const std::uint64_t m = csr.mstatus;
  auto& status = result.status;
  status.debug = csr.debug;
  status.cease = csr.cease;
  status.wfi = csr.wfi;
  status.isa = static_cast<std::uint32_t>(csr.misa);
  status.dprv = registered_dprv & 3u;
  status.prv = csr.prv & 3u;
  status.sd = ((m >> 13) & 3u) == 3u || ((m >> 15) & 3u) == 3u ||
              ((m >> 9) & 3u) == 3u;
  status.zero2 = static_cast<std::uint32_t>((m >> 36) & UINT64_C(0x7ffffff));
  // CSR.scala overrides these two output fields with the architectural XLEN.
  status.sxl = 2;
  status.uxl = 2;
  status.sd_rv32 = false;
  status.zero1 = static_cast<std::uint8_t>((m >> 23) & UINT64_C(0xff));
  status.tsr = ((m >> 22) & 1u) != 0;
  status.tw = ((m >> 21) & 1u) != 0;
  status.tvm = ((m >> 20) & 1u) != 0;
  status.mxr = ((m >> 19) & 1u) != 0;
  status.sum = ((m >> 18) & 1u) != 0;
  status.mprv = ((m >> 17) & 1u) != 0;
  status.xs = static_cast<std::uint8_t>((m >> 15) & 3u);
  status.fs = static_cast<std::uint8_t>((m >> 13) & 3u);
  status.mpp = static_cast<std::uint8_t>((m >> 11) & 3u);
  status.vs = static_cast<std::uint8_t>((m >> 9) & 3u);
  status.spp = ((m >> 8) & 1u) != 0;
  status.mpie = ((m >> 7) & 1u) != 0;
  status.hpie = ((m >> 6) & 1u) != 0;
  status.spie = ((m >> 5) & 1u) != 0;
  status.upie = ((m >> 4) & 1u) != 0;
  status.mie = ((m >> 3) & 1u) != 0;
  status.hie = ((m >> 2) & 1u) != 0;
  status.sie = ((m >> 1) & 1u) != 0;
  status.uie = (m & 1u) != 0;

  for (std::size_t i = 0; i < result.pmp.size(); ++i) {
    const auto& source = csr.pmp[i];
    auto& destination = result.pmp[i];
    destination.locked = source.cfg_l;
    destination.address_mode = source.cfg_a;
    destination.execute = source.cfg_x;
    destination.write = source.cfg_w;
    destination.read = source.cfg_r;
    destination.address = source.addr;
    destination.mask = pmp_mask(source);
  }
  result.custom_csr_value = csr.custom_0;
  result.memory.ordered = true;
  result.memory.clock_enabled = true;
  return result;
}

using PmpAccess = PmpPermissions::Access;

bool tlb_execute_access(const PmpPermissions& permissions, std::uint64_t address,
                        std::uint8_t size, bool instruction) {
  const components::PmaAttributes pma =
      components::SmallPma::lookup(address);
  const PmpAccess pmp = permissions.lookup(address, size, 1);
  const std::uint32_t a = static_cast<std::uint32_t>(address);
  const bool region_01 =
      ((a ^ UINT32_C(0x40000000)) & UINT32_C(0xc0000000)) == 0;
  const bool region_10 =
      ((a ^ UINT32_C(0x80000000)) & UINT32_C(0xc0000000)) == 0;
  const bool supports_execute =
      (a & UINT32_C(0xca000000)) == 0 || region_01 || region_10;
  const bool deny_debug = instruction && a < UINT32_C(0x1000);
  return pma.legal && supports_execute && !deny_debug && pmp.execute;
}

components::SmallTlbPhysicalAccess tlb_data_physical_access(
    const PmpPermissions& permissions, std::uint64_t address, std::uint8_t size,
    std::uint8_t privilege) {
  const components::PmaAttributes pma =
      components::SmallPma::lookup(address);
  const PmpAccess pmp = permissions.lookup(address, size, privilege);
  const std::uint32_t a = static_cast<std::uint32_t>(address);
  const bool atomic =
      (a & UINT32_C(0xc8010000)) == 0 ||
      ((a ^ UINT32_C(0x08000000)) & UINT32_C(0xc8000000)) == 0;
  const bool region_01 =
      ((a ^ UINT32_C(0x40000000)) & UINT32_C(0xc0000000)) == 0;
  const bool region_10 =
      ((a ^ UINT32_C(0x80000000)) & UINT32_C(0xc0000000)) == 0;
  const bool supports_write = atomic || region_01 || region_10;
  const bool effectful =
      (a & UINT32_C(0xca012000)) == 0 ||
      ((a ^ UINT32_C(0x02000000)) & UINT32_C(0xca010000)) == 0 ||
      ((a ^ UINT32_C(0x08000000)) & UINT32_C(0xc8000000)) == 0 ||
      region_01;

  components::SmallTlbPhysicalAccess result;
  result.read = pma.legal && pmp.read;
  result.write = pma.legal && supports_write && pmp.write;
  result.atomic_logical = pma.legal && atomic;
  result.atomic_arithmetic = pma.legal && atomic;
  result.effectful = pma.legal && effectful;
  result.cacheable = pma.cacheable;
  return result;
}

components::SmallTlbRefill make_tlb_refill(
    const protocol::PtwResponse& response, const PmpPermissions& permissions,
    std::uint64_t current_vaddr, std::uint8_t access_size,
    bool instruction) {
  components::SmallTlbRefill result;
#if defined(CHISA_MODEL_ARCHITECTURAL) && CHISA_MODEL_ARCHITECTURAL
  // Both TLBs consume this record only on a valid PTW response. Inactive
  // PTE payloads need neither a port image nor a pair of PMP traversals.
  if (!response.valid) return result;
#endif
  result.valid = response.valid;
  result.level = response.level;
  result.homogeneous = response.homogeneous;

  const auto& pte = response.pte;
  auto& data = result.data;
  data.ppn = static_cast<std::uint32_t>(pte.ppn) & UINT32_C(0xfffff);
  data.u = pte.u;
  // Rocket's ITLB qualifies global with PTE.valid; BOOM's NBDTLB stores g raw.
  data.g = instruction ? pte.g && pte.v : pte.g;
  data.ae = response.access_exception;
  const bool leaf = pte.v && (pte.r || (pte.x && !pte.w)) && pte.a;
  data.sr = leaf && pte.r;
  data.sw = leaf && pte.w && pte.d;
  data.sx = leaf && pte.x;
  data.fragmented_superpage = response.fragmented_superpage;

  // TLB.scala checks the response PPN with the current request's page offset.
  const std::uint64_t physical_address =
      (static_cast<std::uint64_t>(data.ppn) << 12) |
      (current_vaddr & UINT64_C(0xfff));
  const components::PmaAttributes pma =
      components::SmallPma::lookup(physical_address);
  const PmpAccess pmp = permissions.lookup(physical_address, access_size, 1);
  const std::uint32_t a = static_cast<std::uint32_t>(physical_address);
  const bool atomic =
      (a & UINT32_C(0xc8010000)) == 0 ||
      ((a ^ UINT32_C(0x08000000)) & UINT32_C(0xc8000000)) == 0;
  const bool region_01 =
      ((a ^ UINT32_C(0x40000000)) & UINT32_C(0xc0000000)) == 0;
  const bool region_10 =
      ((a ^ UINT32_C(0x80000000)) & UINT32_C(0xc0000000)) == 0;
  const bool supports_write = atomic || region_01 || region_10;
  const bool effectful =
      (a & UINT32_C(0xca012000)) == 0 ||
      ((a ^ UINT32_C(0x02000000)) & UINT32_C(0xca010000)) == 0 ||
      ((a ^ UINT32_C(0x08000000)) & UINT32_C(0xc8000000)) == 0 ||
      region_01;
  const bool deny_debug = instruction && a < UINT32_C(0x1000);
  data.c = pma.cacheable;
  data.pr = pma.legal && !deny_debug && pmp.read;
  data.pw = pma.legal && supports_write && !deny_debug && pmp.write;
  const bool supports_execute =
      (a & UINT32_C(0xca000000)) == 0 || region_01 || region_10;
  data.px = pma.legal && supports_execute && !deny_debug && pmp.execute;
  data.ppp = instruction && pma.legal && supports_write;
  data.pal = pma.legal && atomic;
  data.paa = pma.legal && atomic;
  data.eff = pma.legal && effectful;
  return result;
}

protocol::PtwMemoryInputs make_ptw_memory_inputs(
    const components::SmallHellaCacheOutputs& hella, bool ordered,
    std::uint64_t raw_lsu_response_data) {
  protocol::PtwMemoryInputs result;
  // PTW.scala reads only req.ready, resp, s2_nack and s2_xcpt.ae.ld of its
  // HellaCache port; the other port fields are left at their defaults so the
  // sidecar's input compare sees an idle walker as idle and skips the step.
  (void)ordered;
  result.request_ready = hella.request_ready;
  result.s2_nack = hella.s2_nack;
  result.s2_xcpt_ae_ld = hella.s2_exceptions.ae_ld;
  result.ordered = true;
  result.clock_enabled = true;
  const auto& source = hella.response;
  auto& response = result.response;
  response.valid = source.valid;
  response.address = source.address;
  response.tag = source.tag;
  response.command = source.command;
  response.size = source.size;
  response.is_signed = source.is_signed;
  response.dprv = source.dprv;
  // PTW.scala registers dcache.io.lsu.resp.bits.data without a valid gate,
  // but consumes the register only after a valid response.  The walker gets
  // the raw payload only with a valid response (so its inputs stay equal
  // across idle cycles and it skips); the ungated register stream itself is
  // written by SystemGuider::step from the raw D-cache response port.
  response.data = source.valid ? raw_lsu_response_data : 0;
  response.mask = source.mask;
  response.replay = source.replay;
  response.has_data = source.has_data;
  response.data_word_bypass = source.data_word_bypass;
  response.data_raw = source.data_raw;
  response.store_data = source.store_data;
  return result;
}

CoherentMemoryInputs make_cold_memory_input(
    bool reset,
    const components::SmallICacheMemoryPathOutputs& fabric_offer) {
  CoherentMemoryInputs result;
  result.reset = reset;
#if defined(CHISA_MODEL_ARCHITECTURAL) && CHISA_MODEL_ARCHITECTURAL
  constexpr bool keep_inactive_payload = false;
#else
  constexpr bool keep_inactive_payload = true;
#endif
  // TileLink payloads are consumed only with their channel's valid bit.
  // Canonical empty channels let the fabric reuse its idle evaluation even
  // while the cache's inactive candidates change addresses or decode bits.
  if (keep_inactive_payload || fabric_offer.manager_a.valid) {
    result.tile_a.valid = fabric_offer.manager_a.valid;
    result.tile_a.opcode = fabric_offer.manager_a.opcode;
    result.tile_a.param = fabric_offer.manager_a.param;
    result.tile_a.size = fabric_offer.manager_a.size;
    result.tile_a.source =
        static_cast<std::uint8_t>(fabric_offer.manager_a.source & boomcfg::TILE_SOURCE_MASK);
    result.tile_a.address = fabric_offer.manager_a.address;
    result.tile_a.bufferable = true;
    result.tile_a.modifiable = true;
    result.tile_a.readalloc = fabric_offer.manager_a.opcode == 4 ||
                              fabric_offer.manager_a.opcode == 6;
    result.tile_a.writealloc = fabric_offer.manager_a.opcode <= 3 ||
                               fabric_offer.manager_a.opcode == 7;
    result.tile_a.mask = fabric_offer.manager_a.mask;
    result.tile_a.data = fabric_offer.manager_a.data;
    result.tile_a.data_hi = fabric_offer.manager_a.data_hi;
  }
  result.tile_b_ready = fabric_offer.manager_b_ready;
  if (keep_inactive_payload || fabric_offer.manager_c.valid) {
    result.tile_c.valid = fabric_offer.manager_c.valid;
    result.tile_c.opcode = fabric_offer.manager_c.opcode;
    result.tile_c.param = fabric_offer.manager_c.param;
    result.tile_c.size = fabric_offer.manager_c.size;
    result.tile_c.source =
        static_cast<std::uint8_t>(fabric_offer.manager_c.source & boomcfg::TILE_SOURCE_MASK);
    result.tile_c.address = fabric_offer.manager_c.address;
    result.tile_c.bufferable = true;
    result.tile_c.modifiable = true;
    result.tile_c.writealloc = true;
    result.tile_c.data = fabric_offer.manager_c.data;
    result.tile_c.data_hi = fabric_offer.manager_c.data_hi;
    result.tile_c.corrupt = fabric_offer.manager_c.corrupt;
  }
  result.tile_d_ready = fabric_offer.manager_d_ready;
  if (keep_inactive_payload || fabric_offer.manager_e.valid) {
    result.tile_e.valid = fabric_offer.manager_e.valid;
    result.tile_e.sink = fabric_offer.manager_e.sink;
  }
  return result;
}

}  // namespace

// The bindings' record is the model image: the core writes its streams in
// place (guiders/model), the samplers write theirs through the record API.

#if !defined(CHISA_WIDE_MODEL)
static_assert(sizeof(boom_model::Image) == kOracleRecordPaddedBytes,
              "generated/image.h and the oracle record must share one layout");
#endif

namespace {
// The frontend evaluation reads these backend outputs; fetch_ready and the
// FTQ dequeue/get_pc(0) fields are used only by the commit and are patched
// in afterwards, so they are not compared here.
bool frontend_links_match(const BackendFrontendControl& a, const BackendFrontendControl& b,
                          const BackendFrontendFeedback& fa, const BackendFrontendFeedback& fb,
                          bool& control_ok, bool& feedback_ok) {
  control_ok =
      a.sfence_valid == b.sfence_valid && a.sfence_rs1 == b.sfence_rs1 &&
      a.sfence_rs2 == b.sfence_rs2 && a.sfence_addr == b.sfence_addr &&
      a.icache_invalidate == b.icache_invalidate && a.redirect_flush == b.redirect_flush &&
      a.redirect_valid == b.redirect_valid && a.redirect_pc == b.redirect_pc &&
      a.redirect_ftq_idx == b.redirect_ftq_idx &&
      a.redirect_from_rob_flush == b.redirect_from_rob_flush &&
      a.redirect_from_branch_mispredict == b.redirect_from_branch_mispredict &&
      a.redirect_branch_taken == b.redirect_branch_taken &&
      a.redirect_branch_is_br == b.redirect_branch_is_br &&
      a.redirect_branch_is_rvc == b.redirect_branch_is_rvc &&
      a.redirect_branch_edge_inst == b.redirect_branch_edge_inst &&
      a.redirect_branch_pc_lob == b.redirect_branch_pc_lob &&
      a.redirect_branch_pc_sel == b.redirect_branch_pc_sel &&
      a.redirect_branch_cfi_type == b.redirect_branch_cfi_type &&
      a.redirect_branch_target_offset == b.redirect_branch_target_offset &&
      a.redirect_branch_jalr_target == b.redirect_branch_jalr_target;
  feedback_ok = fa.ftq_redirect_valid == fb.ftq_redirect_valid &&
                fa.ftq_brupdate_mispredict == fb.ftq_brupdate_mispredict;
  return control_ok && feedback_ok;
}
// The first few preview mismatches, for the run's log (pv = the previewed
// links, actual = the links the backend edge produced).
void report_preview_mismatch(std::uint64_t cycle, const BackendFrontendControl& pv,
                             const BackendFrontendControl& actual,
                             const BackendFrontendFeedback& pv_feedback,
                             const BackendFrontendFeedback& feedback) {
  static unsigned reported = 0;
  if (reported >= 4) return;
  ++reported;
  std::fprintf(stderr,
      "SYSMODEL_FRONTEND_PREVIEW_MISMATCH cycle=%llu"
      " sfence=%d/%d inval=%d/%d flush=%d/%d rv=%d/%d rpc=%llx/%llx rftq=%u/%u"
      " rob=%d/%d br=%d/%d taken=%d/%d is_br=%d/%d pc_lob=%u/%u"
      " fb_rv=%d/%d fb_mis=%d/%d\n",
      static_cast<unsigned long long>(cycle),
      pv.sfence_valid, actual.sfence_valid, pv.icache_invalidate, actual.icache_invalidate,
      pv.redirect_flush, actual.redirect_flush, pv.redirect_valid, actual.redirect_valid,
      static_cast<unsigned long long>(pv.redirect_pc), static_cast<unsigned long long>(actual.redirect_pc),
      pv.redirect_ftq_idx, actual.redirect_ftq_idx,
      pv.redirect_from_rob_flush, actual.redirect_from_rob_flush,
      pv.redirect_from_branch_mispredict, actual.redirect_from_branch_mispredict,
      pv.redirect_branch_taken, actual.redirect_branch_taken,
      pv.redirect_branch_is_br, actual.redirect_branch_is_br,
      pv.redirect_branch_pc_lob, actual.redirect_branch_pc_lob,
      pv_feedback.ftq_redirect_valid, feedback.ftq_redirect_valid,
      pv_feedback.ftq_brupdate_mispredict, feedback.ftq_brupdate_mispredict);
}
// The fields the frontend copies from the backend links and reads only when
// it commits (FetchBuffer dequeue, FTQ dequeue/redirect/brupdate/get_pc).
void patch_late_frontend_links(FrontendEvaluation& ev, bool fetch_ready,
                               const BackendFrontendFeedback& f) {
  ev.fb_deq_ready = fetch_ready;
  auto& fq = ev.ftq_input;
  fq.deq_valid = f.ftq_deq_valid; fq.deq_idx = f.ftq_deq_idx;
  fq.redirect_valid = f.ftq_redirect_valid; fq.redirect_idx = f.ftq_redirect_idx;
  fq.brupdate_mispredict = f.ftq_brupdate_mispredict;
  fq.brupdate_ftq_idx = f.ftq_brupdate_idx; fq.brupdate_pc_lob = f.ftq_brupdate_pc_lob;
  fq.brupdate_taken = f.ftq_brupdate_taken;
  fq.get_pc_idx = {{f.ftq_get_pc_0_idx, f.ftq_get_pc_1_idx}};
}
// Copy src over dst one 64-byte chunk at a time, skipping equal chunks, so a
// line another core reads is only invalidated when its content moved.
void copy_changed_lines(void* dst, const void* src, std::size_t bytes) {
  unsigned char* d = static_cast<unsigned char*>(dst);
  const unsigned char* s = static_cast<const unsigned char*>(src);
  for (std::size_t at = 0; at < bytes; at += 64) {
    const std::size_t n = bytes - at < 64 ? bytes - at : 64;
    if (std::memcmp(d + at, s + at, n) != 0) std::memcpy(d + at, s + at, n);
  }
}
}  // namespace

// One worker thread owns the frontend evaluation and commit of the current
// cycle while the calling thread runs the backend.  Requests are (cycle, op)
// pairs on one cache line; completions echo the pair on another.  The
// calling thread never overlaps two frontend operations, so a single slot
// suffices and no operation is ever dropped or reordered.
struct SystemGuider::FrontendWorker {
  enum : std::uint64_t { kEvaluate = 1, kCommit = 2, kStop = 3 };
  explicit FrontendWorker(SystemGuider& owner) : owner_(owner) {
    if (!owner_.cooperative_workers_) thread_ = std::thread([this] { run(); });
  }
  ~FrontendWorker() {
    post(0, kStop);
    if (thread_.joinable()) thread_.join();
  }
  // One slot per request kind: the calling thread posts the commit of a
  // cycle without waiting for its evaluation to be taken, so both may be
  // outstanding at once (a single slot would lose the evaluation).
  void wait_runs(std::uint64_t cycle) const {
    while (runs_done_.load(std::memory_order_acquire) < cycle) owner_.wait_task_or_pause();
  }
  bool records_ready(std::uint64_t cycle) const {
    return runs_done_.load(std::memory_order_acquire) >= cycle;
  }
  void post(std::uint64_t cycle, std::uint64_t op) {
    const std::uint64_t word = (cycle << 2) | op;
    if (op == kEvaluate) {
#ifdef CHISA_PHASE_TIMERS
      evaluate_post_tsc_ = __rdtsc();  // same line as the request: travels with it
#endif
      evaluate_request_.store(word, std::memory_order_release);
    } else {
#ifdef CHISA_PHASE_TIMERS
      post_tsc_ = __rdtsc();
#endif
      request_.store(word, std::memory_order_release);
    }
  }
  /** Spins until the commit (or stop) request of `cycle` has completed;
    * evaluations are never waited for. */
  std::uint64_t wait(std::uint64_t cycle, std::uint64_t op) const {
    const std::uint64_t want = (cycle << 2) | op;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
    while (done_.load(std::memory_order_acquire) != want) owner_.wait_task_or_pause();
#ifdef CHISA_PHASE_TIMERS
    return __rdtsc() - t0;
#else
    return 0;
#endif
  }
  bool ready(std::uint64_t cycle, std::uint64_t op) const {
    return done_.load(std::memory_order_acquire) == ((cycle << 2) | op);
  }
  /** Worker-side timing (CHISA_PHASE_TIMERS): ticks from the post to the
    * worker seeing the request, and the worker's own work, per request. */
  struct Stats {
    std::uint64_t evaluate_requests = 0, commit_requests = 0;
    std::uint64_t observe_ticks = 0, evaluate_ticks = 0, early_ticks = 0;
    std::uint64_t late_observe_ticks = 0, late_ticks = 0, tail_ticks = 0;  // tail: late + sampling + runs copy
    std::uint64_t late_commit_ticks = 0, late_handoff_ticks = 0;  // parts of late
    std::uint64_t fabric_wait_ticks = 0;  // inside evaluate: waiting for the memory worker's fabric phase
    // Preview mismatches found by the worker when the actual links arrived.
    std::uint64_t fallbacks = 0, control_mismatches = 0, feedback_mismatches = 0;
  };
  const Stats& stats() const { return stats_; }
  bool poll() {
    const auto e = evaluate_request_.load(std::memory_order_acquire);
    const auto r = request_.load(std::memory_order_acquire);
    if ((r & 3u) == kStop) return false;
    if (e != last_evaluate_) {
#if defined(CHISA_WIDE_MODEL)
      if (owner_.frontend_early_commit_ && owner_.frontend_memory_pipeline_) {
        if (prepared_evaluate_ != e) {
          reset_stats_if_requested();
#ifdef CHISA_PHASE_TIMERS
          const auto t0 = __rdtsc();
          stats_.observe_ticks += t0 - evaluate_post_tsc_;
#endif
          owner_.frontend_.evaluate_independent(owner_.frontend_evaluation_, owner_.frontend_input_,
                                                 owner_.frontend_feedback_preview_);
#ifdef CHISA_PHASE_TIMERS
          const auto t1 = __rdtsc();
          stats_.evaluate_ticks += t1 - t0;
#endif
          owner_.frontend_.commit_independent(owner_.frontend_evaluation_);
#ifdef CHISA_PHASE_TIMERS
          memory_wait_started_ = __rdtsc();
          stats_.early_ticks += memory_wait_started_ - t1;
          ++stats_.evaluate_requests;
#endif
          prepared_evaluate_ = e;
          return true;
        }
        if (owner_.frontend_icache_from_memory_ && !owner_.memory_fabric_ready_for_frontend()) return false;
#ifdef CHISA_PHASE_TIMERS
        const auto t0 = __rdtsc();
        if (owner_.frontend_icache_from_memory_) stats_.fabric_wait_ticks += t0 - memory_wait_started_;
#endif
        if (owner_.frontend_icache_from_memory_) owner_.wait_memory_fabric_for_frontend();
        owner_.frontend_.evaluate_memory(owner_.frontend_evaluation_, owner_.frontend_input_.icache_memory);
#ifdef CHISA_PHASE_TIMERS
        const auto t1 = __rdtsc();
        stats_.evaluate_ticks += t1 - t0;
#endif
        owner_.frontend_.commit_memory(owner_.frontend_evaluation_);
#ifdef CHISA_PHASE_TIMERS
        stats_.early_ticks += __rdtsc() - t1;
#endif
        last_evaluate_ = e;
        return true;
      }
#endif
      if (owner_.frontend_icache_from_memory_ && !owner_.memory_fabric_ready_for_frontend())
        return false;
      reset_stats_if_requested();
      evaluate(e);
      return true;
    }
    if (r == last_ || last_evaluate_ != (((r >> 2) << 2) | kEvaluate)) return false;
    last_ = r;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
    const std::uint64_t posted = post_tsc_;
#endif
    {
      // The actual backend links arrived with the request.  The calling
      // thread does not wait for the evaluation: the preview is verified
      // here, re-evaluated on a mismatch unless the early commit already
      // happened, then the late links are patched in and the state
      // commits.  The handoff for the next edge is filled last.
      // The tail still needs the destination after handoff-ready is sent.
      // A local request cannot be overwritten by the next posted commit.
      const FrontendLateLinks late = owner_.frontend_late_links_;
      bool control_ok = true, feedback_ok = true;
      if (!frontend_links_match(owner_.frontend_input_.backend_control, late.control,
                                owner_.frontend_feedback_preview_, late.feedback,
                                control_ok, feedback_ok)) {
        ++stats_.fallbacks;
        stats_.control_mismatches += !control_ok;
        stats_.feedback_mismatches += !feedback_ok;
        report_preview_mismatch(r >> 2, owner_.frontend_input_.backend_control, late.control,
                                owner_.frontend_feedback_preview_, late.feedback);
        if (owner_.frontend_early_commit_) {
          std::fprintf(stderr, "SYSMODEL_FRONTEND_THREAD=3: preview mismatch after the early commit "
                               "at cycle %llu; the edge cannot be re-evaluated\n",
                       static_cast<unsigned long long>(r >> 2));
          std::abort();
        }
        owner_.frontend_input_.backend_control = late.control;
        owner_.frontend_.evaluate_into(owner_.frontend_evaluation_, owner_.frontend_input_, late.feedback);
      }
      patch_late_frontend_links(owner_.frontend_evaluation_, late.fetch_ready, late.feedback);
#if defined(CHISA_WIDE_MODEL)
#ifdef CHISA_PHASE_TIMERS
      const std::uint64_t tc0 = __rdtsc();
#endif
      if (owner_.frontend_early_commit_) owner_.frontend_.commit_late(owner_.frontend_evaluation_, false);
      else owner_.frontend_.commit(owner_.frontend_evaluation_);
#ifdef CHISA_PHASE_TIMERS
      const std::uint64_t tc1 = __rdtsc();
      stats_.late_commit_ticks += tc1 - tc0;
#endif
      FrontendHandoff& handoff = owner_.frontend_handoff_[late.handoff_index];
      owner_.frontend_.fill_handoff(handoff);
#ifdef CHISA_PHASE_TIMERS
      stats_.late_handoff_ticks += __rdtsc() - tc1;
#endif
      // The calling thread's next edge needs only the handoff: signal the
      // commit now.  The Frontend sampling placement and the copy of the
      // frontend's record runs into the next image position follow (the
      // calling thread's publish skips those runs; the copy is joined
      // before the position is released, synchronize_frontend_runs).
      handoff.image_runs_copied_to = late.image_runs_destination;
#ifdef CHISA_PHASE_TIMERS
      stats_.late_observe_ticks += t0 - posted;
      stats_.late_ticks += __rdtsc() - t0;
      ++stats_.commit_requests;
#endif
      done_.store(r, std::memory_order_release);
      // The frontend's record lanes of this cycle (deferred by the late
      // commit), then the Frontend sampling placement, then the runs copy.
      if (owner_.frontend_early_commit_) owner_.frontend_.write_late_record_lanes(owner_.frontend_evaluation_);
      sample_frontend_placement();
      if (late.image_runs_destination != nullptr) {
        const unsigned char* record = ModelBindings::instance().record().bytes;
        std::size_t count = 0;
        const ImageRun* runs = frontend_image_runs(count);
        for (std::size_t i = 0; i < count; ++i) {
          CHISA_DIAG(owner_.observe_image_source((r >> 2)+1,record,runs[i].begin,runs[i].end-runs[i].begin));
          std::memcpy(late.image_runs_destination + runs[i].begin, record + runs[i].begin,
                      runs[i].end - runs[i].begin);
        }
      }
#ifdef CHISA_PHASE_TIMERS
      stats_.tail_ticks += __rdtsc() - t0;
#endif
      runs_done_.store(r >> 2, std::memory_order_release);
#else
      owner_.frontend_.commit(owner_.frontend_evaluation_);
      sample_frontend_placement();
#ifdef CHISA_PHASE_TIMERS
      stats_.late_observe_ticks += t0 - posted;
      stats_.late_ticks += __rdtsc() - t0;
      ++stats_.commit_requests;
#endif
      done_.store(r, std::memory_order_release);
#endif
    }
    return true;
  }
 private:
  void reset_stats_if_requested() {
#ifdef CHISA_PHASE_TIMERS
    if (reset_stats_.load(std::memory_order_relaxed) &&
        reset_stats_.exchange(false, std::memory_order_relaxed)) stats_ = Stats{};
#endif
  }
  void evaluate(std::uint64_t e) {
    last_evaluate_ = e;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
    const std::uint64_t posted = evaluate_post_tsc_;
#endif
    // This cycle's I-cache fabric face comes from the memory worker's
    // fabric phase, which the calling thread did not wait for.
    if (owner_.frontend_icache_from_memory_) owner_.wait_memory_fabric_for_frontend();
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0w = __rdtsc();
    stats_.fabric_wait_ticks += t0w - t0;
#endif
    owner_.frontend_.evaluate_into(owner_.frontend_evaluation_, owner_.frontend_input_,
                                   owner_.frontend_feedback_preview_);
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t1 = __rdtsc();
    stats_.observe_ticks += t0 - posted;
    stats_.evaluate_ticks += t1 - t0;
    ++stats_.evaluate_requests;
#endif
#if defined(CHISA_WIDE_MODEL)
    // The early/late commit split exists only on the wide frontend; the
    // Small build never constructs a worker (mode parsing is wide-only).
    if (owner_.frontend_early_commit_) owner_.frontend_.commit_early(owner_.frontend_evaluation_);
#ifdef CHISA_PHASE_TIMERS
    stats_.early_ticks += __rdtsc() - t1;
#endif
#endif
  }
  void run() {
    if (const char* cpu_text = std::getenv("SYSMODEL_FRONTEND_CPU"); cpu_text && *cpu_text) {
      const int cpu = std::atoi(cpu_text);
      cpu_set_t set; CPU_ZERO(&set); CPU_SET(cpu, &set);
      pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
    }
    while ((request_.load(std::memory_order_acquire) & 3u) != kStop)
      if (!poll()) __builtin_ia32_pause();
  }
  // The Frontend sampling placement reads only frontend state: running it
  // here right after the commit keeps those lines on this core (the samplers
  // store into their own record lanes; the calling thread samples other
  // placements into other lanes meanwhile).
  void sample_frontend_placement() {
    if (owner_.frontend_worker_samples_ == 1 && owner_.oracle_sampling_enabled_)
      ModelBindings::instance().sample_placed(ModelBindings::SamplePlacement::Frontend, owner_);
  }
  std::uint64_t last_ = 0, last_evaluate_ = 0, prepared_evaluate_ = 0, memory_wait_started_ = 0;
  SystemGuider& owner_;
  std::thread thread_;
  alignas(64) std::atomic<std::uint64_t> request_{0};           // commit / stop
  std::atomic<std::uint64_t> evaluate_request_{0};              // same line
  std::uint64_t post_tsc_ = 0, evaluate_post_tsc_ = 0;
  alignas(64) std::atomic<std::uint64_t> done_{0};
  std::atomic<std::uint64_t> runs_done_{0};                     // the cycle whose frontend runs are copied
  alignas(64) Stats stats_{};  // the worker's own line
 public:
  void request_stats_reset() { reset_stats_.store(true, std::memory_order_relaxed); }
 private:
  std::atomic<bool> reset_stats_{false};
};

// The memory side of the cycle on its own thread (SYSMODEL_MEMORY_THREAD=1):
// after the backend edge of cycle t the calling thread posts the request; the
// worker commits t (PTW commit, tile and cold uncore commits, post-edge
// memory-run lanes), joins the frontend commit of t, then runs the pre-edge
// phase of t+1 (memory outputs, fabric view, cold uncore evaluation, pre-edge
// memory-run lanes, the memory runs' image copy).  The calling thread joins
// it at the start of step t+1 (synchronize_memory).
struct SystemGuider::MemoryWorker {
  // Request word: (cycle << 2) | kCycle.  Completion word: (cycle << 2) |
  // kOutputs once the next cycle's memory outputs are in (the backend edge
  // can start), kNativeFabric once the PRE(t+1) native feedback is stable,
  // and kFabric only after the record copy is also complete. The frontend
  // needs native feedback; source/context reuse still needs the final tail.
  enum : std::uint64_t { kCycle = 1, kOutputs = 1, kNativeFabric = 2, kFabric = 3, kStop = 3 };
  explicit MemoryWorker(SystemGuider& owner) : owner_(owner) {
    if (!owner_.cooperative_workers_) thread_ = std::thread([this] { run(); });
  }
  ~MemoryWorker() {
    request_.store(kStop, std::memory_order_release);
    if (thread_.joinable()) thread_.join();
  }
  void post(const MemoryRequest& request) {
    request_block_ = request;
#ifdef CHISA_PHASE_TIMERS
    post_tsc_ = __rdtsc();
#endif
    request_.store((request.cycle << 2) | kCycle, std::memory_order_release);
  }
  std::uint64_t wait(std::uint64_t cycle, std::uint64_t phase) const {
    const std::uint64_t want = (cycle << 2) | phase;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
    while (done_.load(std::memory_order_acquire) < want) owner_.wait_task_or_pause();
#ifdef CHISA_PHASE_TIMERS
    return __rdtsc() - t0;
#else
    return 0;
#endif
  }
  std::uint64_t frontend_phase() const { return frontend_mode_.phase; }
  bool ready(std::uint64_t cycle, std::uint64_t phase) const {
    return done_.load(std::memory_order_acquire) >= ((cycle << 2) | phase);
  }
  struct Stats {
    std::uint64_t requests = 0, observe_ticks = 0, commit_ticks = 0, fabric_ticks = 0,
                  frontend_wait_ticks = 0, pre_ticks = 0;
  };
  const Stats& stats() const { return stats_; }
  bool poll() {
    if (phase_ == Phase::Idle) {
      const auto r = request_.load(std::memory_order_acquire);
      if (r == last_ || (r & 3u) == kStop) return false;
      last_ = r;
      active_ = request_block_;
#ifdef CHISA_PHASE_TIMERS
      if (active_.reset_stats) stats_ = Stats{};
      const auto t0 = __rdtsc();
      stats_.observe_ticks += t0 - post_tsc_;
#endif
      owner_.memory_commit_tile_step(active_);
      owner_.memory_pre_outputs(active_.reset_next, active_.dtm_next);
      done_.store((active_.cycle << 2) | kOutputs, std::memory_order_release);
#ifdef CHISA_PHASE_TIMERS
      stats_.commit_ticks += __rdtsc() - t0;
#endif
      phase_ = Phase::Fabric;
      return true;
    }
    if (phase_ == Phase::Fabric) {
#ifdef CHISA_PHASE_TIMERS
      const auto t0 = __rdtsc();
#endif
      owner_.memory_commit_fabric(active_.reset);
      if (active_.publish_fn != nullptr)
        active_.publish_fn(active_.publish_context, owner_, PublishPhase::PredictedMemory);
      owner_.memory_publish_end();
#ifdef CHISA_PHASE_TIMERS
      phase_start_ = __rdtsc();
      stats_.fabric_ticks += phase_start_ - t0;
#endif
      phase_ = Phase::PreFabric;
      return true;
    }
    if (phase_ == Phase::PreFabric) {
      if (active_.frontend_posted && owner_.frontend_worker_ &&
          !owner_.frontend_worker_->ready(active_.cycle, FrontendWorker::kCommit)) return false;
#ifdef CHISA_PHASE_TIMERS
      const auto t0 = __rdtsc();
      stats_.frontend_wait_ticks += t0 - phase_start_;
#endif
      // The source publication and its copy have separate readiness. In
      // cooperative mode neither wait may retain the executor's stack.
      owner_.memory_pre_fabric(active_.reset_next, active_.cycle + 1,
                               active_.frontend_handoff_index, nullptr);
      // The native face and early record lanes are now stable. Do not make
      // frontend computation wait for the separate speculative image copy.
      // The main thread still joins kFabric before reusing this request.
      done_.store((active_.cycle << 2) | kNativeFabric, std::memory_order_release);
#ifdef CHISA_PHASE_TIMERS
      stats_.pre_ticks += __rdtsc() - t0;
#endif
      phase_ = Phase::Copy;
      return true;
    }
#ifdef CHISA_PHASE_TIMERS
    const auto t0 = __rdtsc();
#endif
    if (!owner_.try_memory_image_copy(active_.cycle + 1, active_.image_runs_destination)) return false;
#ifdef CHISA_PHASE_TIMERS
    stats_.pre_ticks += __rdtsc() - t0;
    ++stats_.requests;
    fabric_signal_tsc_ = __rdtsc();
#endif
    phase_ = Phase::Idle;
    done_.store((active_.cycle << 2) | kFabric, std::memory_order_release);
    return true;
  }
 private:
  void run() {
    if (const char* cpu_text = std::getenv("SYSMODEL_MEMORY_CPU"); cpu_text && *cpu_text) {
      const int cpu = std::atoi(cpu_text);
      cpu_set_t set; CPU_ZERO(&set); CPU_SET(cpu, &set);
      pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
    }
    while ((request_.load(std::memory_order_acquire) & 3u) != kStop)
      if (!poll()) __builtin_ia32_pause();
  }

 public:
  std::uint64_t post_tsc() const { return post_tsc_; }
  std::uint64_t fabric_signal_tsc() const { return fabric_signal_tsc_; }
 private:
  std::uint64_t fabric_signal_tsc_ = 0;
  enum class Phase { Idle, Fabric, PreFabric, Copy };
  Phase phase_ = Phase::Idle;
  MemoryRequest active_{};
  std::uint64_t last_ = 0, phase_start_ = 0;
  SystemGuider& owner_;
  std::thread thread_;
  alignas(64) std::atomic<std::uint64_t> request_{0};
  std::uint64_t post_tsc_ = 0;
  MemoryRequest request_block_{};   // same line as the request
  alignas(64) std::atomic<std::uint64_t> done_{0};
  alignas(64) Stats stats_{};
  // The frontend reads this constant on every readiness poll. Keep it off
  // the cache lines containing the memory owner's mutable phase/request.
  struct alignas(64) FrontendMode { std::uint64_t phase; };
  const FrontendMode frontend_mode_{[] {
    const char* native = std::getenv("SYSMODEL_NATIVE_FABRIC_READY");
    return native && native[0] == '0' ? kFabric : kNativeFabric;
  }()};
};

struct SystemGuider::RecordWorker {
  enum : std::uint64_t { kPublish = 1, kStop = 3 };
  explicit RecordWorker(SystemGuider& owner) : owner_(owner) {
    thread_ = std::thread([this] { run(); });
  }
  ~RecordWorker() {
    post(0, kStop);
    if (thread_.joinable()) thread_.join();
  }
  void post(std::uint64_t cycle, std::uint64_t op) {
    request_.store((cycle << 2) | op, std::memory_order_release);
  }
  std::uint64_t wait(std::uint64_t cycle, std::uint64_t op) const {
    const std::uint64_t want = (cycle << 2) | op;
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
    while (done_.load(std::memory_order_acquire) != want) __builtin_ia32_pause();
#ifdef CHISA_PHASE_TIMERS
    return __rdtsc() - t0;
#else
    return 0;
#endif
  }
 private:
  void run() {
    if (const char* cpu_text = std::getenv("SYSMODEL_RECORD_CPU"); cpu_text && *cpu_text) {
      const int cpu = std::atoi(cpu_text);
      cpu_set_t set; CPU_ZERO(&set); CPU_SET(cpu, &set);
      pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
    }
    std::uint64_t last = 0;
    for (;;) {
      std::uint64_t r;
      while ((r = request_.load(std::memory_order_acquire)) == last) __builtin_ia32_pause();
      last = r;
      if ((r & 3u) == kStop) return;
#if defined(CHISA_WIDE_MODEL)
      owner_.backend_.publish_record();
#else
      (void)owner_;  // the Small build never constructs this worker
#endif
      done_.store(r, std::memory_order_release);
    }
  }
  SystemGuider& owner_;
  std::thread thread_;
  alignas(64) std::atomic<std::uint64_t> request_{0};
  alignas(64) std::atomic<std::uint64_t> done_{0};
};

SystemGuider::~SystemGuider() {
  synchronize_frontend();
  synchronize_frontend_runs();
  if (memory_pending_) synchronize_memory_fabric();
  if (memory_worker_) {
    const MemoryWorker::Stats s = memory_worker_->stats();
    memory_worker_.reset();
    const auto per = [&](std::uint64_t ticks) { return s.requests ? double(ticks) / double(s.requests) : 0.0; };
    std::fprintf(stderr, "SYSMODEL_MEMORY_WORKER roi_ticks_per_request: observe=%.1f tile=%.1f fabric=%.1f"
                         " frontend_wait=%.1f pre=%.1f outputs_wait_per_cycle=%.1f fabric_wait_per_cycle=%.1f\n",
                 per(s.observe_ticks), per(s.commit_ticks), per(s.fabric_ticks), per(s.frontend_wait_ticks),
                 per(s.pre_ticks),
                 s.requests ? double(memory_wait_ticks_) / double(s.requests) : 0.0,
                 s.requests ? double(memory_fabric_wait_ticks_) / double(s.requests) : 0.0);
    std::fprintf(stderr, "SYSMODEL_MEMORY_WORKER fabric_waits=%llu (of %llu joins, %llu requests) max_wait_ticks=%llu"
                         " join_arrival_after_post=%.1f signal_after_post=%.1f\n",
                 static_cast<unsigned long long>(memory_fabric_wait_count_), static_cast<unsigned long long>(fabric_join_count_),
                 static_cast<unsigned long long>(s.requests), static_cast<unsigned long long>(memory_fabric_wait_max_),
                 fabric_join_count_ ? double(fabric_join_arrival_ticks_) / double(fabric_join_count_) : 0.0,
                 fabric_join_count_ ? double(fabric_signal_after_post_ticks_) / double(fabric_join_count_) : 0.0);
  }
  record_worker_.reset();
  if (record_publication_ != RecordPublication::Inline)
    std::fprintf(stderr, "SYSMODEL_RECORD_THREAD mode=%s cycles=%llu wait_ticks_per_cycle=%.1f\n",
                 record_publication_ == RecordPublication::Threaded ? "threaded" : "deferred",
                 static_cast<unsigned long long>(record_cycles_),
                 record_cycles_ ? double(record_wait_ticks_) / double(record_cycles_) : 0.0);
  const FrontendWorker::Stats worker_stats = frontend_worker_ ? frontend_worker_->stats()
                                                              : FrontendWorker::Stats{};
  frontend_worker_.reset();
  if (frontend_threading_ != FrontendThreading::Off) {
    const auto& s = frontend_thread_stats_;
    const auto per = [](std::uint64_t ticks, std::uint64_t n) {
      return n ? static_cast<double>(ticks) / static_cast<double>(n) : 0.0;
    };
    if (worker_stats.evaluate_requests != 0)
      std::fprintf(stderr,
          "SYSMODEL_FRONTEND_WORKER roi_ticks_per_request: observe=%.1f evaluate=%.1f (fabric_wait=%.1f) early=%.1f"
          " late_observe=%.1f late=%.1f (commit=%.1f handoff=%.1f) tail=%.1f\n",
          per(worker_stats.observe_ticks, worker_stats.evaluate_requests),
          per(worker_stats.evaluate_ticks, worker_stats.evaluate_requests),
          per(worker_stats.fabric_wait_ticks, worker_stats.evaluate_requests),
          per(worker_stats.early_ticks, worker_stats.evaluate_requests),
          per(worker_stats.late_observe_ticks, worker_stats.commit_requests),
          per(worker_stats.late_ticks, worker_stats.commit_requests),
          per(worker_stats.late_commit_ticks, worker_stats.commit_requests),
          per(worker_stats.late_handoff_ticks, worker_stats.commit_requests),
          per(worker_stats.tail_ticks, worker_stats.commit_requests));
    std::fprintf(stderr,
        "SYSMODEL_FRONTEND_THREAD mode=%s memory_pipeline=%d external_executor=%d cycles=%llu previewed=%llu fallbacks=%llu"
        " control_mismatches=%llu feedback_mismatches=%llu"
        " roi: evaluate_ticks_per_cycle=%.1f commit_ticks_per_cycle=%.1f"
        " wait_evaluate_ticks_per_cycle=%.1f wait_commit_ticks_per_cycle=%.1f\n",
        frontend_threading_ == FrontendThreading::Threaded
            ? (frontend_early_commit_ ? "threaded-early" : "threaded") : "check",
        int(frontend_early_commit_ && frontend_memory_pipeline_), int(cooperative_workers_),
        static_cast<unsigned long long>(s.cycles), static_cast<unsigned long long>(s.previewed),
        static_cast<unsigned long long>(s.fallbacks + worker_stats.fallbacks),
        static_cast<unsigned long long>(s.control_mismatches + worker_stats.control_mismatches),
        static_cast<unsigned long long>(s.feedback_mismatches + worker_stats.feedback_mismatches),
        per(s.evaluate_ticks, s.roi_cycles),
        per(s.commit_ticks, s.roi_cycles),
        per(s.wait_evaluate_ticks, s.roi_cycles),
        per(s.wait_commit_ticks, s.roi_cycles));
  }
}

SystemGuider::SystemGuider(const BoundaryConfig& config)
#if defined(CHISA_WIDE_MODEL)
    : frontend_(), backend_()
#else
    : frontend_(*reinterpret_cast<boom_model::Image*>(ModelBindings::instance().record().bytes)),
      backend_(reinterpret_cast<boom_model::Image*>(ModelBindings::instance().record().bytes)),
      image_(reinterpret_cast<boom_model::Image*>(ModelBindings::instance().record().bytes))
#endif
 {

  // Nothing to initialize until a subsystem lands. The config is accepted now
  // so that the harness contract is fixed before the first subsystem needs it:
  // the model is handed the workload once and then runs free, and adding a
  // per-cycle input later would quietly turn this into a replay harness.
  reset_cycles_ = config.reset_cycles;
  debug_bootstrap_ = config.debug_bootstrap;
  fabric_.set_debug_reader(
      [](const void* ctx, std::uint32_t address, bool get) {
        return static_cast<const SystemGuider*>(ctx)
            ->memory_.debug_path_for_diagnostic()
            .debug_face_data(address, get);
      },
      this);
  // The complete core (frontend + backend + fabric) runs live by default:
  // the bring-up converged with the full 200k-cycle window green.  The
  // environment switch remains as a diagnostic to fall back to the starved
  // ordering (SYSMODEL_CORE_LIVE=0).
  const char* core_live = std::getenv("SYSMODEL_CORE_LIVE");
  core_live_ = core_live == nullptr || core_live[0] != '0';
#if defined(CHISA_WIDE_MODEL)
  if (const char* mode = std::getenv("SYSMODEL_FRONTEND_THREAD"); mode && *mode) {
    if (mode[0] == '1') frontend_threading_ = FrontendThreading::Check;
    else if (mode[0] == '2') frontend_threading_ = FrontendThreading::Threaded;
    else if (mode[0] == '3') { frontend_threading_ = FrontendThreading::Threaded; frontend_early_commit_ = true; }
  }
  if (const char* mode = std::getenv("SYSMODEL_FRONTEND_MEMORY_PIPELINE"); mode && mode[0] == '0')
    frontend_memory_pipeline_ = false;
  cooperative_workers_ = config.cooperative_workers;
  if (cooperative_workers_) {
    if (std::getenv("SYSPROBE") != nullptr)
      throw std::invalid_argument("cooperative workers do not support SYSPROBE");
    if (const char* mode = std::getenv("SYSMODEL_RECORD_THREAD"); mode && mode[0] != '0')
      throw std::invalid_argument("cooperative workers require inline record publication");
    frontend_threading_ = FrontendThreading::Threaded;
    frontend_early_commit_ = true;
  }
  if (frontend_threading_ == FrontendThreading::Threaded && std::getenv("SYSPROBE") != nullptr) {
    // The lockstep boundary snapshots read the evaluation right after the
    // backend edge, which a worker may still be producing.
    std::fprintf(stderr, "SYSMODEL_FRONTEND_THREAD: SYSPROBE set, evaluating the preview on the calling thread\n");
    frontend_threading_ = FrontendThreading::Check;
    frontend_early_commit_ = false;
  }
  if (frontend_threading_ == FrontendThreading::Threaded)
    frontend_worker_ = std::make_unique<FrontendWorker>(*this);
  if (const char* mode = std::getenv("SYSMODEL_RECORD_THREAD"); mode && *mode) {
    if (mode[0] == '1') record_publication_ = RecordPublication::Deferred;
    else if (mode[0] == '2') record_publication_ = RecordPublication::Threaded;
  }
  if (record_publication_ != RecordPublication::Inline) backend_.set_record_deferred(true);
  if (record_publication_ == RecordPublication::Threaded)
    record_worker_ = std::make_unique<RecordWorker>(*this);
  // SYSMODEL_CUT_LANES=0 skips the partition-cut lanes (measurement switch;
  // a consumer emitted with partitions needs them).
  if (const char* cut = std::getenv("SYSMODEL_CUT_LANES"); cut && cut[0] == '0') {
    cut_lanes_ = false; backend_.set_cut_lanes(false); frontend_.set_cut_lanes(false);
  }
  // The first edge reads the constructed frontend through the handoff.
  frontend_.fill_handoff(frontend_handoff_[frontend_handoff_read_]);
  const char* memory_mode = std::getenv("SYSMODEL_MEMORY_THREAD");
  if (cooperative_workers_ || (memory_mode && memory_mode[0] == '1'))
    memory_worker_ = std::make_unique<MemoryWorker>(*this);
#endif
  // Cycle-0 register image: the record compared at cycle 0 is the one
  // published at the start of the first step, and the RTL registers are
  // still the simulator's zero initial state then (their first clock edge
  // has not happened). Keep the model's constructed registers aside and
  // hand them back right after that first publish (see step()).

#if !defined(CHISA_WIDE_MODEL)
  boot_regs_snapshot_.resize(sizeof(image_->r));
  std::memcpy(boot_regs_snapshot_.data(), &image_->r, sizeof(image_->r));
  std::memset(&image_->r, 0, sizeof(image_->r));
  boot_regs_pending_ = true;
#endif

}

StepResult SystemGuider::step() {
  CHISA_DIAG(::chisa::diagnostic::set_cycle(cycle_));
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_step_t0 = __rdtsc();
#endif
  // The previous step's frontend commit may still be running on the worker:
  // it is joined below, after the memory outputs join and the debug
  // transport's advance, which read nothing of it (its late commit overlaps
  // them); everything after that join reads its results.
  // The statement order below is the clock-edge evaluation order. It is the
  // only place timing is expressed in this model, so it is written out even
  // while the bodies are empty -- the order is the design, and filling a body
  // in the wrong slot is the failure mode that costs the most to find.
  //
  //   1. cycle-start snapshots        (registered values, read pre-edge)
  //   2. debug / DMI                  (drives reset release and the boot path)
  //   3. uncore: memory -> tile       (responses arriving this cycle)
  //   4. frontend / I-cache           (produces the fetch stream)
  //   5. backend                      (rename, issue, ROB, LSU, commit, flush)
  //   6. D-cache / TLB / PTW          (consumes this cycle's requests)
  //   7. uncore: tile -> memory       (requests leaving this cycle)
  //   8. delay lines advance          (RegNext chains, last)
  //
  // Steps 3 and 7 are deliberately split around the tile: an uncore queue is
  // read with its pre-edge occupancy and written with this cycle's traffic,
  // and collapsing them into one pass is exactly how a queue ends up one cycle
  // early.

  // Cycle-start snapshot for the bring-up probes.  The observer steps the
  // model one full cycle ahead of the RTL PRE tap it compares, so the value
  // the tap wants is this call's PRE-step component state.  The very first
  // call reports the zero-initialized snapshot, matching the generated
  // simulator image before any edge; component construction state (which is
  // the post-reset value) is never surfaced.
  // The four SYSMODEL_DEV_PROBES remainders read model state directly, so
  // these snapshots have no steady-state consumer; skip the copies (and the
  // FTQ output evaluation they trigger) unless the dev-probe gate is up.
  static const bool bringup_snapshots_enabled =
      std::getenv("SYSMODEL_DEV_PROBES") != nullptr;
  // The last_*_boundary_ snapshots below have exactly one consumer: the
  // scalar-lockstep probe harness, and every lockstep entry point (smoke,
  // qualify, matrix) exports SYSPROBE.  Production runs skip the copies.
  static const bool lockstep_boundary_snapshots =
      std::getenv("SYSPROBE") != nullptr;
  if (bringup_snapshots_enabled && core_live_ && cycle_ > 0) {
    synchronize_frontend();  // diagnostic reads of frontend state
    bringup_.int_sync_0 = debug_.int_sync_0;
    const auto& f0f2 = frontend_.f0_f2_for_diagnostic();
    bringup_.s1_valid = f0f2.s1().valid;
    bringup_.s1_vpc = f0f2.s1().vpc;
    bringup_.s2_ppc = f0f2.s2().ppc;
    const auto& fb = frontend_.fetch_buffer_for_diagnostic();
    bringup_.fb_head = fb.head();
    bringup_.fb_tail = fb.tail();
    bringup_.fb_maybe_full = fb.maybe_full();
    bringup_.ftq_enq_ptr = frontend_.ftq_for_diagnostic().enq_idx();
    const auto& icache = frontend_.icache_for_diagnostic();
    bringup_.icache_s2_valid = icache.s2_valid();
    bringup_.icache_s2_hit = icache.s2_hit();
    bringup_.rob_head = static_cast<std::uint8_t>(core_access::rob_head(backend_.core()) & 0x1f);
    bringup_.rob_tail = static_cast<std::uint8_t>(core_access::rob_tail(backend_.core()) & 0x1f);
  }

  reset_asserted_ = cycle_ < reset_cycles_;
  if (reset_asserted_) lsu_mem_tlb_packed_bit_ = false;
  if (reset_asserted_) { rtc_counter_ = 0; clint_time_ = 0; }
  else if (rtc_counter_ == 99) { rtc_counter_ = 0; ++clint_time_; }
  else ++rtc_counter_;
  {  // env-gated watchpoints (WATCHPOINTS=lsu WP_CYCLES=a-b)
    static bool wp_once = [] {
      WatchpointManager::instance().configure_from_env();
      return true;
    }();
    (void)wp_once;
    WatchpointManager::instance().set_cycle(static_cast<int>(cycle_));
  }

  if (!reset_asserted_ && !debug_bootstrap_ &&
      !debug_.bootstrap_complete) {
    return StepResult{
        false,
        "model-side debug bootstrap transport is required after reset"};
  }

  // A second exact fesvr DTM supplies the request stream and is advanced for
  // the full run only with feedback from the independent debug/uncached path.
  // The activation fields below remain explicit probe-facing snapshots; the
  // component additionally owns the two asynchronous DMI queues, dmOuter and
  // the exercised dmInner registers.
  debug_.dmactive_observed = debug_.dmactive_state;
  debug_.bypass_reg_observed = debug_.bypass_reg_state;
  debug_.clock_en_observed = debug_.clock_en_state;
  debug_.inner_dmactive_inactive = !debug_.inner_dmactive_sync_0;
  // The previous cycle's frontend commit, the cycle-start samples and the
  // Registers publish. These sample the previous edge's completed record;
  // the memory-output face and DMI transport can be prepared before the join
  // because neither writes frontend/core record lanes. Small keeps its
  // existing inline placement after the pre-edge memory phase.
  const auto head_sample_and_publish = [&]() {
  // Cycle-start sample of every bound stream: registered state after the
  // previous edge, pre-image combinational reconstructions, and the cold
  // wire oracles just refreshed above.  Nothing below this point may be
  // read by a sampled binding before the components advance.
  if (oracle_sampling_enabled_ && cycle_ > 0) {
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t phase_t0 = __rdtsc();
#endif
    static const bool sample_check = std::getenv("SYSMODEL_SAMPLE_CHECK") != nullptr;
    if (sample_check) {
      ModelBindings::instance().set_check_mode(true);
      ModelBindings::instance().set_verify_cycle(cycle_);
      ModelBindings::instance().verify_placed(*this, cycle_);
    }
    ModelBindings::instance().sample_bound_streams(*this);
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t phase_dt = __rdtsc() - phase_t0;
    phase_counters_.sample_tsc += phase_dt;
    phase_counters_.sample_by_placement_tsc[0] += phase_dt;  // PreStep
#endif
  }
  // This cycle's record is complete: the placed batches wrote the register
  // streams right after their components committed last step, the cold
  // wire oracles were sampled just above.  Publish before anything commits.
  {
    // Not latched: the strict qualification enables the probes only when its
    // ROI begins (cycle ~803k), and a value latched at step 0 would leave the
    // published record empty for the first measured cycle (every pre-step
    // binding then reads 0). Two loads per cycle; the live flavors have no
    // probes and skip the publish as before.

    if (oracle_sampling_enabled_)
#if !defined(CHISA_WIDE_MODEL)
      export_memory_image_early(*this, *image_);
#endif

    if (oracle_sampling_enabled_) {
      if (SystemProbes::instance().active()) ModelBindings::instance().publish_record();
      // Every record write this thread makes for this cycle's image position
      // (the previous step's End and Predicted publishes, this step's
      // pre-step sampling) is done: the memory worker may copy the memory
      // runs into it.  The core runs are copied here, by the thread that
      // writes them: another thread reading them leaves the lines shared and
      // the backend edge then pays the ownership transfers (240 ns per cycle).
      record_copy_gate_.publish(cycle_);
      if (publish_fn_ != nullptr)
        publish_fn_(publish_context_, *this, PublishPhase::Registers);
    }
  }
  };
#if defined(CHISA_WIDE_MODEL)
  // Runs a worker was given no image destination for (the next image slot
  // was not free: a reset window, a window end without staging) are copied
  // by this thread at the Registers publish below, from the record: the
  // worker's lanes must be complete first.  The frontend worker writes its
  // lanes after its commit signal (synchronize_frontend_runs covers them);
  // the memory worker's post-edge and pre-edge lanes end with its fabric
  // phase.  Both waits are rare.
  if (frontend_worker_ && frontend_runs_from_worker_ && frontend_runs_destination_ == nullptr) {
    synchronize_frontend();
    synchronize_frontend_runs();
  }
  if (memory_worker_ && memory_pending_ && memory_image_runs_destination_ == nullptr)
    synchronize_memory_fabric();
  // The previous cycle's frontend commit first: the pre-step scan below
  // watches frontend fields too (a scan before the join read them mid-commit;
  // the live 1M-cycle totals caught it, the ROI golden dump did not).  The
  // General samplers retain that join. The native owner-only path below
  // copies disjoint record ranges before it, with worker-owned runs skipped.
  bool wide_head_published=false;
  bool defer_frontend_tail=false;
  const auto publish_wide_head = [&] {
    if (wide_head_published) return;
#ifdef CHISA_PHASE_TIMERS
    const auto pre_head_t0 = __rdtsc();
#endif
    head_sample_and_publish();
    wide_head_published=true;
#ifdef CHISA_PHASE_TIMERS
    phase_counters_.sub_tsc[9] += __rdtsc() - pre_head_t0;
#endif
  };
  const auto finish_wide_head = [&] {
  synchronize_frontend();
  // Handoff-ready covers native state. A general PreStep reader also needs
  // the record tail; the proven owner-only path retires it before reuse.
#ifdef CHISA_PHASE_TIMERS
  const auto pre_tail_t0 = __rdtsc();
#endif
  if (!defer_frontend_tail) synchronize_frontend_runs();
#ifdef CHISA_PHASE_TIMERS
  phase_counters_.sub_tsc[8] += __rdtsc() - pre_tail_t0;
#endif
  publish_wide_head();
  };
  static const bool head_after_dtm = [] {
    const char* value = std::getenv("SYSMODEL_HEAD_AFTER_DTM");
    return !(value && value[0] == '0');
  }();
  static const bool owner_local_head = [] {
    const char* value=std::getenv("SYSMODEL_OWNER_LOCAL_HEAD");
    return !(value && value[0]=='0') && std::getenv("SYSMODEL_SAMPLE_CHECK")==nullptr;
  }();
  static const bool late_frontend_tail = [] {
    const char* value=std::getenv("SYSMODEL_LATE_FRONTEND_TAIL");
    return !(value && value[0]=='0');
  }();
  if (head_after_dtm && owner_local_head && oracle_sampling_enabled_ &&
      publish_image_owner_copy_ && !bringup_snapshots_enabled && !lockstep_boundary_snapshots &&
      !SystemProbes::instance().active() && ModelBindings::instance().prestep_is_owner_local(*this)) {
    // Workers publish only their own skipped record ranges. Copy the main
    // owner's ranges while those tails and memory outputs are still running.
    // Native frontend reads and request reuse retain the joins below.
    publish_wide_head();
    // The commit join below makes native handoff/TLB/FTQ state stable. The remaining
    // tail writes only frontend record lanes and its private epoch caches.
    // No registered PreStep reader is present on this path, so retire that
    // tail at request reuse after independent backend-input/PTW preparation.
    defer_frontend_tail=late_frontend_tail && frontend_worker_ && frontend_worker_samples_==1;
  }
  if (!head_after_dtm) finish_wide_head();
#endif
  const bool debug_reset_syncd = !debug_.reset_sync_0;
#ifdef CHISA_PHASE_TIMERS
  const auto pre_memory_t0 = __rdtsc();
#endif
  {
    const DebugBootstrapOutputs dtm_now =
        debug_bootstrap_ ? debug_bootstrap_->outputs() : DebugBootstrapOutputs{};
    bool pre_done = false;
    if (memory_pending_) synchronize_memory_outputs();  // the worker ran commit(t-1) and pre(t)'s outputs
    if (memory_pre_ready_) {
      // (Joined here or by the harness before this step.)  The worker's pre
      // phase used the transport's request as it stood when the memory side
      // was posted.  The harness may have changed it between the steps (the
      // DMI quiesce replaces the pending NOP): then the pre phase is redone
      // here with the actual request, and the memory runs the worker copied
      // into the image position are copied again below.
      memory_pre_ready_ = false;
      const DebugBootstrapOutputs& used = dtm_outputs_;
      pre_done = used.req_valid == dtm_now.req_valid && used.req_addr == dtm_now.req_addr &&
                 used.req_op == dtm_now.req_op && used.req_data == dtm_now.req_data &&
                 used.resp_ready == dtm_now.resp_ready && used.exit == dtm_now.exit;
      if (!pre_done) {
        memory_image_runs_destination_ = nullptr;
        synchronize_memory_fabric();  // the worker's (stale) pre phase, before it is redone
      }
    }
    if (!pre_done) {
      synchronize_frontend();  // the redone pre phase reads this cycle's handoff
      memory_pre_outputs(reset_asserted_, dtm_now);
      memory_pre_fabric(reset_asserted_, cycle_, frontend_handoff_read_, nullptr);
      last_dram_access_main_ = last_dram_access_;
#if defined(CHISA_WIDE_MODEL)
      // An early Registers publish needs a corrected copy after this redo.
      // With the late placement, the single publish below already sees it.
      if (wide_head_published && oracle_sampling_enabled_ && cycle_ > 0 && publish_fn_ != nullptr)
        publish_fn_(publish_context_, *this, PublishPhase::Registers);
#endif
    }
  }
  // The debug transport advances on this cycle's DMI feedback now (it used to
  // at the end of the step; nothing in between reads it), so the request of
  // the next cycle is known before the memory side is posted.
#ifdef CHISA_PHASE_TIMERS
  const auto pre_dtm_t0 = __rdtsc();
  phase_counters_.sub_tsc[10] += pre_dtm_t0 - pre_memory_t0;
#endif
  if (debug_bootstrap_) {
    debug_bootstrap_->advance(
        reset_asserted_,
        DebugBootstrapFeedback{
            memory_output_.debug.dmi_req_ready,
            memory_output_.debug.dmi_resp_valid,
            memory_output_.debug.dmi_resp_response,
            memory_output_.debug.dmi_resp_data});
    dtm_outputs_next_ = debug_bootstrap_->outputs();
  }
#ifdef CHISA_PHASE_TIMERS
  phase_counters_.sub_tsc[11] += __rdtsc() - pre_dtm_t0;
#endif
#if defined(CHISA_WIDE_MODEL)
  // DMI transport and the next memory-output face do not read frontend
  // record lanes. Let the prior frontend tail finish during that work;
  // PreStep sampling and image publication still join it before reading.
  if (head_after_dtm) finish_wide_head();
#endif
  DebugBootstrapOutputs& dtm_outputs = dtm_outputs_;
  MemoryStateInputs& memory_input = memory_input_;
  const MemoryStateOutputs& memory_output = memory_output_;
  const components::BoomUncachedOutputs& debug_path_output = memory_output.debug;
  auto& fabric_evaluation = fabric_evaluation_;
  auto& manager_feedback = manager_feedback_;
  const auto& fabric_output = *fabric_output_;
  (void)fabric_evaluation; (void)manager_feedback;

#ifdef CHISA_PHASE_TIMERS
  phase_counters_.pre_tsc += __rdtsc() - phase_step_t0;
#endif
#if !defined(CHISA_WIDE_MODEL)
  synchronize_frontend();
  head_sample_and_publish();
#endif

#if !defined(CHISA_WIDE_MODEL)
  if (boot_regs_pending_) {
    // First step: the cycle-0 record (zeros) is published above; from here
    // on the model computes with its reset-valued registers.
    std::memcpy(&image_->r, boot_regs_snapshot_.data(), sizeof(image_->r));
    boot_regs_pending_ = false;
  }
#endif

#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_mid_t0 = __rdtsc();
#endif
  // Hoisted out of the per-cycle path: the env switch never changes mid-run,
  // so read it once instead of calling getenv() every step (pure diagnostic).

  const bool first_request =
      !reset_asserted_ && !debug_.bootstrap_complete &&
      dtm_outputs.req_valid;
  if (first_request &&
      (dtm_outputs.req_addr != 0x10u || dtm_outputs.req_op != 2u ||
       (dtm_outputs.req_data & 1u) == 0u || !dtm_outputs.resp_ready)) {
    return StepResult{false, "unexpected first fesvr DMI request"};
  }
  const bool first_request_fire =
      first_request && debug_path_output.dmi_req_ready;
  const bool dmcontrol_write_fire =
      !reset_asserted_ && dtm_outputs.req_valid &&
      dtm_outputs.req_addr == 0x10u && dtm_outputs.req_op == 2u &&
      debug_path_output.dmi_req_ready;

  bool dmactive_next = debug_.dmactive_state;
  if (reset_asserted_)
    dmactive_next = false;
  else if (dmcontrol_write_fire)
    dmactive_next = (dtm_outputs.req_data & 1u) != 0;

  const bool reset_sync_2_next = !reset_asserted_;
  const bool reset_sync_1_next =
      !reset_asserted_ && debug_.reset_sync_2;
  const bool reset_sync_0_next =
      !reset_asserted_ && debug_.reset_sync_1;

  const bool top_ack_sync_2_next =
      !debug_reset_syncd && debug_.dmactive_state;
  const bool top_ack_sync_1_next =
      !debug_reset_syncd && debug_.top_dmactive_ack_sync_2;
  const bool top_ack_sync_0_next =
      !debug_reset_syncd && debug_.top_dmactive_ack_sync_1;
  const bool clock_en_next =
      debug_reset_syncd || debug_.top_dmactive_ack_sync_0;

  const bool outer_ack_sync_2_next =
      !reset_asserted_ && debug_.top_dmactive_ack_sync_0;
  const bool outer_ack_sync_1_next =
      !reset_asserted_ && debug_.outer_dmactive_ack_sync_2;
  const bool outer_ack_sync_0_next =
      !reset_asserted_ && debug_.outer_dmactive_ack_sync_1;

  bool inner_sync_2_next = debug_.inner_dmactive_sync_2;
  bool inner_sync_1_next = debug_.inner_dmactive_sync_1;
  bool inner_sync_0_next = debug_.inner_dmactive_sync_0;
  if (debug_.clock_en_state) {
    inner_sync_2_next = !debug_reset_syncd && debug_.dmactive_state;
    inner_sync_1_next =
        !debug_reset_syncd && debug_.inner_dmactive_sync_2;
    inner_sync_0_next =
        !debug_reset_syncd && debug_.inner_dmactive_sync_1;
  }

  // TLBusBypassBar may change selection whenever no multibeat transfer is in
  // flight.  DMI requests in this elaboration are one beat and all three
  // surviving beat counters are inductively zero, so `next_flight == 0` and
  // the selected value is refreshed every cycle.
  const bool dmi_bypass =
      !debug_.dmactive_state || !debug_.outer_dmactive_ack_sync_0;
  const bool bypass_reg_next = dmi_bypass;

  debug_.dmactive_state = dmactive_next;
  debug_.bypass_reg_state = bypass_reg_next;
  debug_.clock_en_state = clock_en_next;
  debug_.reset_sync_2 = reset_sync_2_next;
  debug_.reset_sync_1 = reset_sync_1_next;
  debug_.reset_sync_0 = reset_sync_0_next;
  debug_.top_dmactive_ack_sync_2 = top_ack_sync_2_next;
  debug_.top_dmactive_ack_sync_1 = top_ack_sync_1_next;
  debug_.top_dmactive_ack_sync_0 = top_ack_sync_0_next;
  debug_.outer_dmactive_ack_sync_2 = outer_ack_sync_2_next;
  debug_.outer_dmactive_ack_sync_1 = outer_ack_sync_1_next;
  debug_.outer_dmactive_ack_sync_0 = outer_ack_sync_0_next;
  debug_.inner_dmactive_sync_2 = inner_sync_2_next;
  debug_.inner_dmactive_sync_1 = inner_sync_1_next;
  debug_.inner_dmactive_sync_0 = inner_sync_0_next;
  if (first_request_fire) debug_.bootstrap_complete = true;

  // Backend edge.  With SYSMODEL_CORE_LIVE=1 the complete core runs: the
  // backend consumes the FetchBuffer's held cycle-start offer,
  // BoomUncachedPath's cycle-start outputs feed it, and the backend's newly
  // accepted LSU request is latched by that path on this same edge.  Calling
  // the path's step before the backend would delay every Debug-ROM
  // notification by one cycle.  With the gate off the starved ordering is
  // preserved bit-for-bit for the qualified baseline.
  // PTW, both TLBs, and the CSR file observe the same pre-edge architectural
  // image. BackendState mutates that image in place, so keep an explicit copy.
  // The CSR file is only written by the backend edge below; everything up
  // to that edge reads it in place, and the four fields consumed after the
  // edge are captured here (a CSR write must not affect its own edge).
  const GuiderCSR& ptw_csr = core_access::csr(backend_.core());
  const std::uint64_t csr_mstatus_pre = ptw_csr.mstatus;
  const bool csr_debug_pre = ptw_csr.debug;
  const std::uint8_t csr_prv_pre = ptw_csr.prv;
  std::array<std::uint64_t,boomcfg::NUM_HPM> csr_hpmevent_pre;
  std::copy(std::begin(ptw_csr.hpmevent),std::end(ptw_csr.hpmevent),csr_hpmevent_pre.begin());
  BackendFrontendControl ptw_sfence = backend_.cycle_start_sfence_control();
  if (!ptw_sfence.sfence_valid) {
    // PTW.scala reads the sfence payload only under sfence.valid; a fixed
    // idle payload keeps the walker's inputs equal across idle cycles.
    ptw_sfence.sfence_rs1 = false;
    ptw_sfence.sfence_rs2 = false;
    ptw_sfence.sfence_addr = 0;
  }
  const bool frontend_debug_mode = ptw_csr.debug;
  const bool frontend_vm_enabled =
      ptw_csr.satp_mode == 8 && ptw_csr.prv <= 1;
  const std::uint8_t frontend_privilege = ptw_csr.prv;
  FrontendInputs& frontend_input = frontend_input_main_;
  frontend_input = FrontendInputs{};
  frontend_input.reset = reset_asserted_;
  frontend_input.run = core_live_ && !reset_asserted_;
  frontend_input.debug_mode = frontend_debug_mode;
  frontend_input.itlb_vm_enabled = frontend_vm_enabled;
  frontend_input.itlb_privilege = frontend_privilege;
  // The backend input record persists across cycles: on a running cycle
  // every field is rewritten below, so only the reset/starved cycles pay
  // for the full default image (776 bytes, four uop payloads).
  BackendInputs& backend_input = backend_input_;
  if (!(core_live_ && !reset_asserted_)) backend_input = BackendInputs{};
  backend_input.reset = reset_asserted_;
#if defined(BOOM_GUIDER_FP)
  {
    const auto& fpu_output = fabric_.fpu_outputs();
    backend_input.fpu_response_connected = true;
    backend_input.fpu_response_valid = fpu_output.valid;
    backend_input.fpu_response_data = fpu_output.data;
    backend_input.fpu_response_data_bit64 = fpu_output.data_bit64;
    backend_input.fpu_response_flags = fpu_output.exception_flags;
#if defined(CHISA_WIDE_MODEL)
    const auto& divide=fabric_.fdivsqrt_outputs();
    backend_input.fdiv_response_connected=true;
    backend_input.fdiv_response_valid=divide.out_valid_div || divide.out_valid_sqrt;
    backend_input.fdiv_response_data=divide.out;
    backend_input.fdiv_response_data_bit64=divide.out_bit64;
    backend_input.fdiv_response_flags=divide.exception_flags;
    backend_input.fdiv_ready_div=divide.in_ready_div;
    backend_input.fdiv_ready_sqrt=divide.in_ready_sqrt;
#endif
  }
#endif
  backend_input.cacheable_response =
      memory_output.backend.cacheable_response;
  backend_input.hella_response = memory_output.backend.hella_response;
  // PTW.scala:135 RegNext(dcache.io.lsu.resp(0).bits.data) is not valid
  // gated.  When the hit response mux is inactive, DCache exposes the
  // response queue RAM at its current dequeue pointer, including while that
  // slot is invalid/empty.  Preserve that stale payload instead of holding
  // the last valid completion.
  last_lsu_resp_data_ = memory_output.backend.cacheable_response.valid
      ? memory_output.dcache.lsu_response_data
      : debug_path_output.response.valid
            ? debug_path_output.response.data
            : memory_output.dcache.lsu_response_data;
  backend_input.cacheable_nack = memory_output.backend.cacheable_nack;
  backend_input.hella_nack = memory_output.backend.hella_nack;
  backend_input.dmem_req_ready = memory_output.backend.dmem_req_ready;
  backend_input.dmem_ordered = memory_output.backend.dmem_ordered;
  backend_input.dmem_release_valid =
      memory_output.backend.dmem_release_valid;
  backend_input.dmem_release_address =
      memory_output.backend.dmem_release_address;
  // The DTLB lookup preview and BackendState::step must arbitrate from the
  // same registered miss-ready bit.  Leaving this at BackendInputs' default
  // made the preview grant a retry that the later core schedule rejected.
  backend_input.dtlb_miss_ready_registered =
      dtlb_miss_ready_registered_;

#if !defined(CHISA_WIDE_MODEL)
  HeldFetch held_fetch;
#endif
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t sub_t0 = __rdtsc();
  std::uint64_t sub_t1 = sub_t0, sub_t2 = sub_t0;
#endif

  components::SmallTlbCycleInputs& dtlb_state_input = dtlb_state_input_;
  dtlb_state_input = components::SmallTlbCycleInputs{};
  DtlbLookupCandidate dtlb;
  dtlb_state_input.reset = reset_asserted_;
  if (core_live_ && !reset_asserted_) {
    backend_input.run = true;
    backend_input.boot_pc = kSmallBootVector;
    {
      const auto& g = frontend_.ftq_get_pc(0);
      backend_input.ftq0_next_val = g.next_valid;
      backend_input.ftq0_pc = g.pc;
      backend_input.ftq0_next_pc = g.next_pc;
      backend_input.ftq0_cfi_valid = g.entry.cfi_valid;
      backend_input.ftq0_cfi_idx = g.entry.cfi_idx;
      backend_input.ftq0_start_bank = g.entry.start_bank;
    }
    {
      const auto& g = frontend_.ftq_get_pc(1);
      backend_input.ftq1_next_val = g.next_valid;
      backend_input.ftq1_pc = g.pc;
      backend_input.ftq1_next_pc = g.next_pc;
      backend_input.ftq1_cfi_valid = g.entry.cfi_valid;
      backend_input.ftq1_cfi_idx = g.entry.cfi_idx;
      backend_input.ftq1_start_bank = g.entry.start_bank;
    }
#if defined(CHISA_WIDE_MODEL)
    {
      // The dequeue row was unpacked and decoded by whoever committed the
      // frontend (FrontendHandoff); only the per-uop valid is reset-gated.
      const FrontendHandoff& handoff = frontend_handoff_[frontend_handoff_read_];
      backend_input.fetch_group = handoff.uops.data();
      const std::uint8_t offered = reset_asserted_ ? 0u : handoff.uop_valids;
      backend_input.fetch_offered = handoff.deq_valid && (offered & 1u) != 0;
      backend_input.fetch_offered_g[0] = backend_input.fetch_offered;
      for (unsigned lane=1;lane<boomcfg::CORE_WIDTH;++lane)
        backend_input.fetch_offered_g[lane]=(offered&(1u<<lane))!=0;
    }
#else
    held_fetch = frontend_.held_fetch(reset_asserted_);

    backend_input.fetch = *held_fetch.uop;
    backend_input.fetch_offered =
        held_fetch.deq_valid && held_fetch.uop_valid;
    // dequeue group (slot 0 = the pair above; the Small core is 1-wide)
    backend_input.fetch_g[0] = backend_input.fetch;
    backend_input.fetch_offered_g[0] = backend_input.fetch_offered;
    if constexpr (boomcfg::CORE_WIDTH>1) {
      for (unsigned lane=1;lane<boomcfg::CORE_WIDTH;++lane) {
        backend_input.fetch_g[lane]=*held_fetch.group[lane];
        backend_input.fetch_offered_g[lane]=(held_fetch.group_valid&(1u<<lane))!=0;
      }
    }
#endif

    // CSRFile raises an interrupt either for the external debug halt request
    // or after a DCSR single-step has retired one instruction. BOOM attaches
    // that interrupt to the offered decode uop. reg_singleStepped itself makes
    // the latter trap enter Debug Mode with dcsr.cause=4.
    const auto& interrupt_csr = core_access::csr(backend_.core());
    const bool debug_interrupt =
        debug_.int_sync_0 && !interrupt_csr.debug && !interrupt_csr.cease;
    const bool single_step_interrupt =
        interrupt_csr.single_stepped && !interrupt_csr.debug &&
        !interrupt_csr.cease;
    // decode.scala:511 applies the shared DecodeUnit interrupt input to every
    // lane, while refusing it on a short-forward-branch uop.  `fetch` is the
    // historical lane-0 alias; Large's remaining lanes live in fetch_g and
    // must receive the same interrupt independently, including a partially
    // consumed FetchBuffer row whose lane 0 has already fired.
    const bool decode_interrupt =
        debug_interrupt || single_step_interrupt;
    const std::uint64_t decode_interrupt_cause =
        debug_interrupt ? kDebugInterruptCause
                        : kSingleStepInterruptCause;
#if defined(CHISA_WIDE_MODEL)
    // Applied by the backend edge to its own copy of each offered uop.
    backend_input.decode_interrupt = decode_interrupt;
    backend_input.decode_interrupt_cause = decode_interrupt_cause;
#else
    const auto inject_decode_interrupt =
        [decode_interrupt, decode_interrupt_cause](MicroOp& uop,
                                                    bool offered) {
          if (!decode_interrupt || !offered || uop.is_sfb) return;
          uop.exception = 1;
          uop.exc_cause = decode_interrupt_cause;
        };
    inject_decode_interrupt(backend_input.fetch,
                            backend_input.fetch_offered);
    if constexpr (boomcfg::CORE_WIDTH > 1) {
      for (int w = 1; w < boomcfg::CORE_WIDTH; ++w) {
        inject_decode_interrupt(backend_input.fetch_g[w],
                                backend_input.fetch_offered_g[w]);
      }
    }
#endif
    backend_input.wfi_wakeup = debug_interrupt;
    // Independent bare-mode lookup: cacheability comes from the locked Small
    // PMA map.  A future VM/PTW path replaces miss=false with MemoryState's
    // stateful lookup.
    dtlb = backend_.dtlb_lookup_candidate(backend_input);
    const auto& csr = ptw_csr;
    const std::uint8_t dprv = ptw_dprv_;
    dtlb_state_input.request_valid = dtlb.valid;
    dtlb_state_input.virtual_address = dtlb.vaddr;
    dtlb_state_input.vm_enabled =
        !dtlb.passthrough && csr.satp_mode == 8 && dprv <= 1;
    dtlb_state_input.privilege = dprv;
    const auto sfence_now = core_access::sfence(backend_.core());
    dtlb_state_input.sfence.valid = sfence_now.valid;
    dtlb_state_input.sfence.rs1 = sfence_now.rs1;
    dtlb_state_input.sfence.rs2 = sfence_now.rs2;
    dtlb_state_input.sfence.address = sfence_now.address;
  }

  // Preview the two registered TLB request faces, then evaluate PTW without
  // taking an edge. The resulting ready/response/request wires all belong to
  // this same cycle.
#ifdef CHISA_PHASE_TIMERS
  sub_t1 = __rdtsc();
  phase_counters_.sub_tsc[0] += sub_t1 - sub_t0;
#endif
  const components::SmallTlbCycleOutputs dtlb_ptw_face =
      dtlb_.outputs(dtlb_state_input);
  if (lockstep_boundary_snapshots)
    last_ptw_boundary_.dtlb_state =
        static_cast<std::uint8_t>(dtlb_.state());
#if defined(CHISA_WIDE_MODEL)
  components::SmallTlbCycleInputs itlb_preview_input;
  FrontendState::itlb_cycle_inputs_from(frontend_handoff_[frontend_handoff_read_], frontend_input,
                                        itlb_preview_input);
#else
  const components::SmallTlbCycleInputs itlb_preview_input =
      frontend_.held_itlb_cycle_inputs(frontend_input);
#endif
  const components::SmallTlbCycleOutputs itlb_ptw_face =
      frontend_.itlb_for_diagnostic().outputs(itlb_preview_input);
  if (!ptw_input_valid_ || ptw_input_reset_ != reset_asserted_ ||
      ptw_input_dprv_ != ptw_dprv_ ||
      ptw_input_sfence_.sfence_valid != ptw_sfence.sfence_valid ||
      ptw_input_sfence_.sfence_rs1 != ptw_sfence.sfence_rs1 ||
      ptw_input_sfence_.sfence_rs2 != ptw_sfence.sfence_rs2 ||
      ptw_input_sfence_.sfence_addr != ptw_sfence.sfence_addr ||
      !ptw_csr_inputs_equal(ptw_input_csr_, ptw_csr)) {
    ptw_input_base_ =
        make_ptw_inputs(reset_asserted_, ptw_csr, ptw_dprv_, ptw_sfence);
    pmp_permissions_.configure(ptw_input_base_.pmp);
    ptw_input_csr_ = ptw_csr;
    ptw_input_sfence_ = ptw_sfence;
    ptw_input_dprv_ = ptw_dprv_;
    ptw_input_reset_ = reset_asserted_;
    ptw_input_valid_ = true;
  }
  protocol::PtwInputs& ptw_input = ptw_input_base_;
  ptw_input.requestors[0] = make_ptw_request(dtlb_ptw_face);
  ptw_input.requestors[1] = make_ptw_request(itlb_ptw_face);
  const protocol::PtwOutputs* ptw_output_p = &fabric_.evaluate_ptw(ptw_input);
  dtlb_state_input.ptw_request_ready = ptw_output_p->request_ready[0];
  dtlb_state_input.refill =
      make_tlb_refill(ptw_output_p->responses[0], pmp_permissions_,
                      dtlb_state_input.virtual_address, dtlb.size, false);
  frontend_input.itlb_ptw_request_ready = ptw_output_p->request_ready[1];
  frontend_input.itlb_refill =
      make_tlb_refill(ptw_output_p->responses[1], pmp_permissions_,
                      itlb_preview_input.virtual_address, 3, true);
  // lsu.scala wires DTLB.kill to the Hella request's s1_kill.  That kill is a
  // PTW output, so first evaluate the walker from its registered image, then
  // close this one combinational seam and replace the DTLB requestor payload
  // before the common edge is committed.
  dtlb_state_input.kill = dtlb.is_hella && ptw_output_p->memory_s1_kill;
  components::SmallTlbCycleOutputs dtlb_state_output =
      dtlb_.outputs(dtlb_state_input);
  ptw_input.requestors[0] = make_ptw_request(dtlb_state_output);
  if (dtlb_state_input.kill) {
    // kill only changes the DTLB request payload-valid bit, but re-evaluating
    // keeps the diagnostic PTW next-state face exact as well.
    ptw_output_p = &fabric_.evaluate_ptw(ptw_input);
    dtlb_state_input.ptw_request_ready = ptw_output_p->request_ready[0];
    dtlb_state_input.refill =
        make_tlb_refill(ptw_output_p->responses[0], pmp_permissions_,
                        dtlb_state_input.virtual_address, dtlb.size, false);
    frontend_input.itlb_ptw_request_ready = ptw_output_p->request_ready[1];
    frontend_input.itlb_refill =
        make_tlb_refill(ptw_output_p->responses[1], pmp_permissions_,
                        itlb_preview_input.virtual_address, 3, true);
    dtlb_state_output = dtlb_.outputs(dtlb_state_input);
    ptw_input.requestors[0] = make_ptw_request(dtlb_state_output);
  }
  if (lockstep_boundary_snapshots) {
    last_ptw_boundary_.requestors = ptw_input.requestors;
    last_ptw_boundary_.request_ready = ptw_output_p->request_ready;
    for (std::size_t i = 0; i < last_ptw_boundary_.response_valid.size(); ++i)
      last_ptw_boundary_.response_valid[i] = ptw_output_p->responses[i].valid;
    last_ptw_boundary_.memory_request = ptw_output_p->memory_request;
    last_ptw_boundary_.state =
        static_cast<std::uint8_t>(fabric_.ptw_oracles()[22]);
  }
  const std::uint64_t itlb_permission_address =
      frontend_input.itlb_refill.valid
          ? (static_cast<std::uint64_t>(
                 frontend_input.itlb_refill.data.ppn)
             << 12) |
                (itlb_preview_input.virtual_address & UINT64_C(0xfff))
          : itlb_ptw_face.physical_address;
  frontend_input.itlb_dynamic_execute_permission =
      tlb_execute_access(pmp_permissions_, itlb_permission_address, 3, true);
  if (lockstep_boundary_snapshots) {
    last_ptw_boundary_.dtlb_input = dtlb_state_input;
    last_ptw_boundary_.dtlb_output = dtlb_state_output;
  }

  {
    const auto& ptw = *ptw_output_p;
    backend_input.hella_request.valid = ptw.memory_request.valid;
    backend_input.hella_request.address = ptw.memory_request.address;
    backend_input.hella_request.tag = ptw.memory_request.tag;
    backend_input.hella_request.command = ptw.memory_request.command;
    backend_input.hella_request.size = ptw.memory_request.size;
    backend_input.hella_request.is_signed = ptw.memory_request.is_signed;
    backend_input.hella_request.dprv = ptw.memory_request.dprv;
    backend_input.hella_request.physical = ptw.memory_request.physical;
    backend_input.hella_request.no_allocate =
        ptw.memory_request.no_allocate;
    backend_input.hella_request.no_exception =
        ptw.memory_request.no_exception;
    backend_input.hella_request.data = ptw.memory_request.data;
    backend_input.hella_request.mask = ptw.memory_request.mask;
    backend_input.hella_s1_data = ptw.memory_s1_data;
    backend_input.hella_s1_kill = ptw.memory_s1_kill;
    backend_input.hella_s2_kill = ptw.memory_s2_kill;
  }

  if (core_live_ && !reset_asserted_) {
    const std::uint64_t translated_address =
        dtlb_state_input.vm_enabled ? dtlb_state_output.physical_address
                                    : dtlb.vaddr;
    const auto pma = components::SmallPma::lookup(translated_address);
    // NBDTLB shares one live PMA/PMP checker.  PTW physical requests are
    // checked as S-mode, as are refill writes; ordinary bypass requests use
    // dprv.  Homogeneous translated entries consume the permissions captured
    // in their entry instead, while the special entry uses this dynamic face.
    const std::uint64_t dynamic_permission_address =
        dtlb_state_input.refill.valid
            ? (static_cast<std::uint64_t>(dtlb_state_input.refill.data.ppn)
               << 12) |
                  (dtlb.vaddr & UINT64_C(0xfff))
            : translated_address;
    const std::uint8_t dynamic_permission_privilege =
        (dtlb_state_input.refill.valid || dtlb.passthrough)
            ? 1
            : dtlb_state_input.privilege;
    components::SmallDataTlbAccessInputs access_input;
    access_input.vm_enabled = dtlb_state_input.vm_enabled;
    access_input.virtual_address = dtlb.vaddr;
    access_input.size = dtlb.size;
    access_input.command = dtlb.cmd;
    access_input.privilege = dtlb_state_input.privilege;
    access_input.status_sum = ((ptw_csr.mstatus >> 18) & 1u) != 0;
    access_input.status_mxr = ((ptw_csr.mstatus >> 19) & 1u) != 0;
    access_input.translation = dtlb_state_output;
    access_input.dynamic_physical = tlb_data_physical_access(
        pmp_permissions_, dynamic_permission_address, dtlb.size,
        dynamic_permission_privilege);
    const components::SmallDataTlbAccessOutputs access =
        components::small_data_tlb_access(access_input);
    WP_LOG(
        "dtlb",
        "cand=%d h=%d sp=%d vm=%d va=%llx pa=%llx sz=%u cmd=%u prv=%u "
        "pte(u=%d sr=%d sw=%d sx=%d ae=%d pr=%d pw=%d c=%d) "
        "resp(miss=%d pf=%d/%d ae=%d/%d)",
        static_cast<int>(dtlb.valid), static_cast<int>(dtlb_state_output.hit),
        static_cast<int>(dtlb_state_output.special_hit),
        static_cast<int>(dtlb_state_input.vm_enabled),
        static_cast<unsigned long long>(dtlb.vaddr),
        static_cast<unsigned long long>(translated_address),
        static_cast<unsigned>(dtlb.size), static_cast<unsigned>(dtlb.cmd),
        static_cast<unsigned>(dtlb_state_input.privilege),
        static_cast<int>(dtlb_state_output.data.u),
        static_cast<int>(dtlb_state_output.data.sr),
        static_cast<int>(dtlb_state_output.data.sw),
        static_cast<int>(dtlb_state_output.data.sx),
        static_cast<int>(dtlb_state_output.data.ae),
        static_cast<int>(dtlb_state_output.data.pr),
        static_cast<int>(dtlb_state_output.data.pw),
        static_cast<int>(dtlb_state_output.data.c),
        static_cast<int>(dtlb_state_output.miss),
        static_cast<int>(access.pf_ld), static_cast<int>(access.pf_st),
        static_cast<int>(access.ae_ld), static_cast<int>(access.ae_st));
    last_dtlb_.agu_valid = core_access::mem_agu_valid(backend_.core());
    last_dtlb_.candidate_valid = dtlb.valid;
    last_dtlb_.candidate_vaddr = dtlb.vaddr;
    last_dtlb_.candidate_size = dtlb.size;
    last_dtlb_.candidate_cmd = dtlb.cmd;
    last_dtlb_.pma_legal = pma.legal;
    last_dtlb_.pma_cacheable = pma.cacheable;
    backend_input.mem_tlb_uncacheable_for_lcam =
        lsu_mem_tlb_packed_bit_;
    last_dtlb_.lcam_packed_pre = lsu_mem_tlb_packed_bit_;
    backend_input.dtlb_passthrough = dtlb.passthrough;
    backend_input.dtlb_req_ready = dtlb_state_output.request_ready;
    backend_input.dtlb_resp_miss =
        dtlb_state_input.vm_enabled && dtlb_state_output.miss;
    backend_input.dtlb_resp_pf_ld = access.pf_ld;
    backend_input.dtlb_resp_pf_st = access.pf_st;
    backend_input.dtlb_resp_ae_ld = access.ae_ld;
    backend_input.dtlb_resp_ae_st = access.ae_st;
    // NBDTLB drives cacheability as a raw combinational response even when
    // req.valid is low.  LSU's mem_tlb_uncacheable RegNext samples that wire
    // without a valid gate, so preserve the idle-cycle value as well.  The
    // actual LDQ address update remains gated by the active MEM uop below.
    const bool selected_cacheable =
        dtlb_state_input.vm_enabled
            ? (dtlb_state_output.hit && !dtlb_state_output.multiple_hits
                   ? (dtlb_state_output.special_hit
                          ? access_input.dynamic_physical.cacheable
                          : dtlb_state_output.data.c)
                   : false)
            : access_input.dynamic_physical.cacheable;
    backend_input.dtlb_resp_uncacheable = !selected_cacheable;
    last_dtlb_.response_uncacheable =
        backend_input.dtlb_resp_uncacheable;
    // Locked extern-tap lowering, TestHarness.h mem__v2_bank_0_3$next bit 0:
    // the concrete storage slot receives io_resp.cacheable (positive
    // polarity), even though the manifest retains the source RTL name
    // mem_tlb_uncacheable.  Only the LCAM's registered gate observes it.
    lsu_mem_tlb_packed_bit_ = selected_cacheable;
    last_dtlb_.lcam_packed_next = lsu_mem_tlb_packed_bit_;
    backend_input.dtlb_resp_paddr =
        dtlb_state_input.vm_enabled
            ? dtlb_state_output.physical_address
            : dtlb.vaddr & UINT64_C(0xffffffff);
  }
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_backend_t0 = __rdtsc();
  phase_counters_.tlbptw_tsc += phase_backend_t0 - phase_mid_t0;
  phase_counters_.sub_tsc[2] += phase_backend_t0 - sub_t2;
#endif
  // Frontend threading: evaluate the frontend from a preview of this edge's
  // backend links while the backend edge runs.  Everything the evaluation
  // reads is registered state or one of the previewed links; the commit-time
  // fields are patched in below once the real links exist.
  const bool frontend_previewed =
      frontend_threading_ != FrontendThreading::Off && frontend_input.run;
#ifdef CHISA_PHASE_TIMERS
  sub_t2 = __rdtsc();
  phase_counters_.sub_tsc[1] += sub_t2 - sub_t1;
#endif
#if defined(CHISA_WIDE_MODEL)
  if (frontend_previewed) {
    backend_.preview_frontend_links(backend_input, frontend_input.backend_control,
                                    frontend_feedback_preview_main_);
    frontend_input.fetch_ready = false;
    if (frontend_worker_ && memory_pending_) {
      // The worker copies the face itself once the memory worker's fabric
      // phase is done; this thread goes on to the backend edge.
      frontend_icache_from_memory_ = true;
      frontend_icache_memory_cycle_ = memory_cycle_;
    } else {
      synchronize_memory_fabric();
      frontend_icache_from_memory_ = false;
      frontend_input.icache_memory = fabric_output.icache;
    }
    if (frontend_worker_) {
      if (defer_frontend_tail) {
#ifdef CHISA_PHASE_TIMERS
        const auto tail_join_t0=__rdtsc();
#endif
        synchronize_frontend_runs();
#ifdef CHISA_PHASE_TIMERS
        phase_counters_.sub_tsc[8]+=__rdtsc()-tail_join_t0;
#endif
      }
      CHISA_DIAG(::chisa::diagnostic::require(
        "frontend", "request-retired-before-reuse", cycle_,
        ::chisa::diagnostic::Layer::Internal, ::chisa::diagnostic::Phase::Pre,
        frontend_worker_->records_ready(frontend_commit_cycle_),
        {{"previous_cycle", frontend_commit_cycle_}}));
      if (frontend_worker_samples_ < 0)
        frontend_worker_samples_ = ModelBindings::instance().export_ring() == nullptr ? 1 : 0;
      copy_changed_lines(&frontend_input_, &frontend_input, sizeof(FrontendInputs));
      copy_changed_lines(&frontend_feedback_preview_, &frontend_feedback_preview_main_,
                         sizeof(BackendFrontendFeedback));
      if (frontend_stats_reset_pending_) {
        frontend_stats_reset_pending_ = false;
        frontend_worker_->request_stats_reset();
      }
      frontend_worker_->post(cycle_, FrontendWorker::kEvaluate);
    } else {
      const std::uint64_t t0 = __rdtsc();
      frontend_.evaluate_into(frontend_evaluation_, frontend_input, frontend_feedback_preview_main_);
      frontend_thread_stats_.evaluate_ticks += __rdtsc() - t0;
    }
  }
#endif
  const BackendFrontendFeedback frontend_feedback =
      backend_.step(backend_input, debug_path_output);
  bool frontend_commit_posted = false;
  const auto post_frontend_commit = [&] {
    const auto& actual = backend_.frontend_control();
    frontend_late_links_.fetch_ready = actual.fetch_ready;
    frontend_late_links_.feedback = frontend_feedback;
    frontend_late_links_.control = actual;
    frontend_late_links_.handoff_index = static_cast<std::uint8_t>(frontend_handoff_read_ ^ 1u);
    frontend_late_links_.image_runs_destination =
        image_precopy_fn_ != nullptr ? image_precopy_fn_(image_precopy_context_) : nullptr;
    frontend_runs_destination_ = frontend_late_links_.image_runs_destination;
    frontend_runs_from_worker_ = true;
    frontend_runs_cycle_ = cycle_ + 1;
    frontend_commit_cycle_ = cycle_;
    frontend_commit_pending_ = true;
    frontend_handoff_swap_pending_ = true;
    frontend_worker_->post(cycle_, FrontendWorker::kCommit);
    frontend_commit_posted = true;
  };
#if defined(CHISA_WIDE_MODEL)
  if (record_publication_ == RecordPublication::Deferred) backend_.publish_record();
  else if (record_worker_) { record_posted_cycle_ = cycle_; record_worker_->post(cycle_, RecordWorker::kPublish); }
  if (record_publication_ != RecordPublication::Inline) ++record_cycles_;
  static const bool early_frontend_post = [] {
    const char* value = std::getenv("SYSMODEL_EARLY_FRONTEND_POST");
    return !(value && value[0] == '0');
  }();
  // Both actual late links are final at backend_.step's return. The code
  // before the old posting point uses copied TLB faces and the OLD handoff
  // bank (not the bank this commit writes); its HPM/debug/memory work need
  // not delay this independent frontend commit. Record-tail reuse is still
  // joined at the beginning of the next step.
  if (frontend_previewed && frontend_worker_ && early_frontend_post && !lockstep_boundary_snapshots)
    post_frontend_commit();
#endif
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_backend_t1 = __rdtsc();
  phase_counters_.backend_tsc += phase_backend_t1 - phase_backend_t0;
#endif
  ptw_input.memory = make_ptw_memory_inputs(
      backend_.last_hella_outputs(), backend_input.dmem_ordered,
      last_lsu_resp_data_);
  // fabric_.commit_ptw(ptw_input) runs in memory_commit_step below.
  const bool ptw_mprv = ((csr_mstatus_pre >> 17) & 1u) != 0;
  ptw_dprv_ = ptw_mprv && !csr_debug_pre
                  ? static_cast<std::uint8_t>((csr_mstatus_pre >> 11) & 3u)
                  : csr_prv_pre;
  // lsu.scala has two independent RegNext(dtlb.io.miss_rdy) sites.  Both
  // sample the old NBDTLB state on this edge, before dtlb_.step() commits its
  // transition, and therefore share this one exact delayed value.
  dtlb_miss_ready_registered_ = dtlb_ptw_face.miss_ready;
  dtlb_.step(dtlb_state_input);
#if defined(BOOM_GUIDER_FP)
  {
#if defined(CHISA_WIDE_MODEL)
    fabric_.commit_fdivsqrt(backend_.fdivsqrt_inputs());
    fabric_.commit_fpu(backend_.fpu_inputs());
#else
    const auto& core = backend_.core();
    protocol::FDivSqrtInputs fdiv_input;
    fdiv_input.reset = reset_asserted_;
    fdiv_input.in_valid = core.fdiv_inner_fire;
    fdiv_input.sqrt_op = core.fdiv_inner_sqrt;
    fdiv_input.a = core.fdiv_inner_a;
    fdiv_input.b = core.fdiv_inner_b;
    fdiv_input.a_bit64 = (core.fdiv_inner_hi & 1u) != 0;
    fdiv_input.b_bit64 = (core.fdiv_inner_hi & 2u) != 0;
    fdiv_input.rounding_mode = core.fdiv_inner_rm;
    fabric_.commit_fdivsqrt(fdiv_input);

    protocol::FpuInputs fpu_input;
    fpu_input.reset = reset_asserted_;
    fpu_input.valid = core.fpu_inner_valid;
    fpu_input.uopc = core.fpu_inner_uop.uopc;
    fpu_input.imm_packed = core.fpu_inner_uop.imm_packed;
    for (std::size_t i = 0; i < fpu_input.operands.size(); ++i)
      fpu_input.operands[i] = core.fpu_inner_rec_lo[i];
    fpu_input.operand_bit64 = core.fpu_inner_rec_hi;
    fpu_input.fcsr_rm = core.fpu_inner_fcsr_rm;
    fabric_.commit_fpu(fpu_input);
#endif
  }
#endif
  // BackendState owns cacheable/uncached arbitration and the same-cycle
  // branch/flush adapter.  Copy the exact transaction that its functional LSU
  // path consumed; the audit must not independently reconstruct it.
  last_memory_completion_boundary_ = &backend_.last_completion_boundary();
  // The memory worker's fabric phase of the previous cycle is joined here at
  // the latest: the HPM latch below reads the fabric view, and the tile
  // inputs written next are its.
  {
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t before = phase_counters_.sub_tsc[6];
#endif
    synchronize_memory_fabric();
#ifdef CHISA_PHASE_TIMERS
    phase_counters_.sub_tsc[7] += phase_counters_.sub_tsc[6] - before;  // this site's share
#endif
  }
  memory_input.request = backend_.memory_request();
#if defined(CHISA_LSU_PUBLICATION_PROBE)
  // The existing fabric join above has completed this cycle's memory
  // publication; the next memory request has not been posted. Observe both
  // native response views and their record here without an extra barrier.
  static const auto lsu_probe_range = [] {
    std::array<unsigned long long,2> range{};
    const char* value = std::getenv("CHISA_CONSUMER_OBSERVER_RANGE");
    if (value && std::sscanf(value,"%llu:%llu",&range[0],&range[1]) != 2)
      throw std::runtime_error("bad LSU publication probe range");
    return range;
  }();
  if (cycle_ >= lsu_probe_range[0] && cycle_ < lsu_probe_range[1]) {
    const auto& dc = memory_.dcache_for_diagnostic();
    const auto& raw = dc.bus_s2_oracle();
    const auto& rec = boom_model::wide::system_record();
    std::fprintf(stderr,"NATIVE_DCACHE cycle=%llu valid=%u functional=%llx raw_wire=%llx cache_valid=%u"
        " s2_addr=%llx size=%u way=%x respq_now=%llx respq_snapshot=%llx published_respq=%llx"
        " s3=%u/%llx/%llx s4=%u/%llx/%llx s5=%u/%llx/%llx\n",
        (unsigned long long)cycle_,unsigned(memory_output.dcache.response.valid),
        (unsigned long long)memory_output.dcache.response.data,
        (unsigned long long)memory_output.dcache.lsu_response_data,unsigned(memory_output.dcache.cache_response_valid),
        (unsigned long long)raw.address,unsigned(raw.size),unsigned(dc.s2_tag_match_way_oracle()),
        (unsigned long long)dc.respq_head_data_now(),(unsigned long long)dc.respq_head_data_oracle(),
        (unsigned long long)rec.c.dcacheMshrs.respq_ram_data_MPORT_1,
        unsigned(dc.s3_valid_oracle()),(unsigned long long)dc.s3_req_addr_oracle(),(unsigned long long)dc.s3_req_data_oracle(),
        unsigned(dc.s4_valid_oracle()),(unsigned long long)dc.s4_req_addr_oracle(),(unsigned long long)dc.s4_req_data_oracle(),
        unsigned(dc.s5_valid_oracle()),(unsigned long long)dc.s5_req_addr_oracle(),(unsigned long long)dc.s5_req_data_oracle());
  }
#endif
  memory_input.raw_attempt = backend_.raw_attempt();
  memory_input.lsu_release_ready = backend_.dmem_release_ready();
  memory_input.dcache_s1_kill = backend_.dmem_s1_kill();
  memory_input.branch_resolve_mask = core_access::b1_resolve(backend_.core());
  memory_input.branch_kill_mask = core_access::b1_mispredict(backend_.core());
  // core.scala:1141 io.lsu.exception := RegNext(rob.io.flush.valid).
  memory_input.lsu_exception = lsu_exception_prev_;

  // core.scala registers perfEvents.evaluate(eventSel) once before CSRFile's
  // wide counters consume it.  All sources below are the independently
  // modeled combinational wires for this same edge; selectors come from the
  // saved pre-edge CSR image so a CSR write cannot affect its own edge.
  // Latched before the memory side is posted: it reads this cycle's memory
  // outputs and fabric view, which the worker overwrites with the next
  // cycle's.
  {
    HpmEventInputs hpm;
    std::copy(csr_hpmevent_pre.begin(),csr_hpmevent_pre.end(),std::begin(hpm.selector));
    hpm.exception = core_access::rob_exception(backend_.core());
    hpm.flush = core_access::rob_flush(backend_.core());

#if defined(CHISA_WIDE_MODEL)
    // icache.evaluate: acquire_fire = held offer && tl_a_ready.  The offer is
    // registered state (the handoff carries it); the evaluation itself may
    // still be running on the worker here.
    hpm.ifu_acquire = frontend_handoff_[frontend_handoff_read_].icache_acquire.valid &&
                      fabric_output.icache.tl_a_ready;
#else
    hpm.ifu_acquire = frontend_evaluation_.icache.acquire_fire;
#endif

    hpm.lsu_acquire =
        memory_output.dcache.tile_a.valid && fabric_output.dcache_a_ready;
    const auto& tile_c = memory_output.dcache.tile_c;
    const bool c_fire = tile_c.valid && fabric_output.dcache_c_ready;
    const bool c_has_data = tile_c.opcode == 5 || tile_c.opcode == 7;
    hpm.lsu_release =
        c_fire && (!c_has_data ||
                   memory_output.dcache.writeback_release_beat + 1u ==
                       boomcfg::DCACHE_REFILL_BEATS);
    hpm.ifu_tlb_miss =
        itlb_ptw_face.ptw_request_valid && ptw_output_p->request_ready[1];
    hpm.lsu_tlb_miss =
        dtlb_ptw_face.ptw_request_valid && ptw_output_p->request_ready[0];
    hpm.ptw_l2_miss = ptw_output_p->perf_l2_miss;
    backend_.latch_hpm_events(hpm);
  }
  {
    static const bool dmi_trace = std::getenv("CHISA_DMI_TRACE") != nullptr;
    if (dmi_trace) {
      static int shown = 0;
      const bool event = dtm_outputs.req_valid ||
                         debug_path_output.dmi_resp_valid;
      if (event && shown < 80) {
        ++shown;
        std::fprintf(stderr,
                     "[DMI c%llu] rv=%d addr=%02x op=%u rdy=%d respv=%d\n",
                     (unsigned long long)cycle_, (int)dtm_outputs.req_valid,
                     (unsigned)dtm_outputs.req_addr,
                     (unsigned)dtm_outputs.req_op,
                     (int)debug_path_output.dmi_req_ready,
                     (int)debug_path_output.dmi_resp_valid);
        std::fprintf(stderr,
                     "[GATE c%llu] halt_now=%d ce=%d s0=%d csr_dbg=%d "
                     "wfi=%d rob=%u/%u\n",
                     (unsigned long long)cycle_,
                     (int)memory_.debug_halt_request(),
                     (int)debug_.clock_en_state, (int)debug_.int_sync_0,
                     (int)core_access::csr(backend_.core()).debug,
                     (int)core_access::csr(backend_.core()).wfi,
                     (unsigned)core_access::rob_head(backend_.core()),
                     (unsigned)core_access::rob_tail(backend_.core()));
      }
    }
  }
  // Per-cycle DMI snapshot for the live-sidecar producer: the request the
  // model consumed this step and the feedback it returned, in the exact
  // shape the reference-oracle cycle record carries.
  last_dmi_.req_valid = dtm_outputs.req_valid;
  last_dmi_.req_addr = dtm_outputs.req_addr;
  last_dmi_.req_op = dtm_outputs.req_op;
  last_dmi_.req_data = dtm_outputs.req_data;
  last_dmi_.resp_ready = dtm_outputs.resp_ready;
  last_dmi_.req_ready = debug_path_output.dmi_req_ready;
  last_dmi_.resp_valid = debug_path_output.dmi_resp_valid;
  last_dmi_.resp_response = debug_path_output.dmi_resp_response;
  last_dmi_.resp_data = debug_path_output.dmi_resp_data;
  last_dmi_.exit = dtm_outputs.exit;
  last_dmi_.reset = reset_asserted_;

  // Debug interrupt crossing edge: the source register samples the pre-edge
  // DMCONTROL.haltreq under the gated debug clock; the tile-side synchronizer
  // is free-running.  Everything above consumed this cycle's pre-shift
  // int_sync_0, so the shift commits last.
  {
    // Empirically the RTL chain is three edges from the latched DMCONTROL
    // bit to sync_0 in this elaboration's bookkeeping: the source register
    // sample coincides with the model's post-DMI view of haltreq, so it is
    // folded into the first synchronizer stage.  The sync_0 probe holds this
    // to the cycle across every halt/resume session.
    const bool halt_now = memory_.debug_halt_request();
    const bool sync_0_next = debug_.int_sync_1;
    const bool sync_1_next = debug_.int_sync_2;
    if (debug_.clock_en_state) debug_.int_sync_2 = halt_now;
    debug_.int_sync_1 = sync_1_next;
    debug_.int_sync_0 = sync_0_next;
  }

  // Frontend edge.  Live: the backend's retained combinational control closes
  // the fetch-ready link, and the I-cache TileLink boundary is closed by a
  // two-phase fabric evaluation -- the held D response is discovered first
  // (acquire ready does not depend on the offer), then the fabric view is
  // refreshed with the resulting acquire offer before the edge commits.
  // Starved: keep the independently qualified FetchBuffer reset only. The
  // ITLB ready/refill fields were fixed by the PTW preview above.
  // The frontend and CSR file commit on the same edge.  A debug entry taken
  // by backend_.step() therefore affects the ITLB starting on the next edge,
  // not the debug-entry lookup already in flight on this one.
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_frontend_t0 = __rdtsc();
  phase_counters_.postbackend_tsc += phase_frontend_t0 - phase_backend_t1;
#endif
  FrontendEvaluation& frontend_evaluation = frontend_evaluation_;
  if (frontend_previewed) {
    ++frontend_thread_stats_.previewed;
    const BackendFrontendControl& actual = backend_.frontend_control();
    frontend_input.fetch_ready = actual.fetch_ready;
    if (frontend_worker_) {
      // The worker verifies the preview against these links, patches the
      // late ones into the evaluation, commits and fills the handoff for
      // the next edge; this thread joins it at the start of the next step
      // (synchronize_frontend), not before its own memory commit.
      if (!frontend_commit_posted) post_frontend_commit();
      frontend_input.backend_control = actual;
    } else {
      bool control_ok = true, feedback_ok = true;
      const bool match = frontend_links_match(frontend_input.backend_control, actual,
                                              frontend_feedback_preview_main_, frontend_feedback,
                                              control_ok, feedback_ok);
      if (match) {
        frontend_input.backend_control = actual;
        patch_late_frontend_links(frontend_evaluation, actual.fetch_ready, frontend_feedback);
      } else {
        ++frontend_thread_stats_.fallbacks;
        frontend_thread_stats_.control_mismatches += !control_ok;
        frontend_thread_stats_.feedback_mismatches += !feedback_ok;
        report_preview_mismatch(cycle_, frontend_input.backend_control, actual,
                                frontend_feedback_preview_main_, frontend_feedback);
        frontend_input.backend_control = actual;
        frontend_.evaluate_into(frontend_evaluation, frontend_input, frontend_feedback);
      }
    }
  } else {
    // Not previewed this cycle (the frontend is not running): evaluated and
    // committed on this thread.  With a worker, its tail of the last posted
    // commit (the record lanes after its signal, the runs copy) may still be
    // running on the same evaluation buffer and frontend state: join it.
    if (frontend_worker_) {
      synchronize_frontend();
      synchronize_frontend_runs();
    }
    if (frontend_input.run) {
      const BackendFrontendControl frontend_control =
          backend_.frontend_control();
      frontend_input.fetch_ready = frontend_control.fetch_ready;
      frontend_input.backend_control = frontend_control;
      synchronize_memory_fabric();
      frontend_input.icache_memory = fabric_output.icache;
    }
    frontend_.evaluate_into(frontend_evaluation, frontend_input, frontend_feedback);
  }
  ++frontend_thread_stats_.cycles;
  ++frontend_thread_stats_.roi_cycles;

#ifdef CHISA_PHASE_TIMERS
  phase_counters_.frontend_tsc += __rdtsc() - phase_frontend_t0;
#endif

  if (lockstep_boundary_snapshots && frontend_input.run) {
    const auto& s1 = frontend_.f0_f2_for_diagnostic().s1();
    last_itlb_boundary_.input = frontend_evaluation.itlb_input;

    last_itlb_boundary_.raw_response = frontend_evaluation.itlb;
    last_itlb_boundary_.selected_response =
        frontend_evaluation.f0_f2.s1_tlb;

    last_itlb_boundary_.s1_valid = s1.valid;
    last_itlb_boundary_.s1_is_replay = s1.is_replay;
    last_itlb_boundary_.s1_is_sfence = s1.is_sfence;
    last_itlb_boundary_.s1_vpc = s1.vpc;
  } else if (lockstep_boundary_snapshots) {
    last_itlb_boundary_ = {};  // only read under the same switch
  }

#if defined(CHISA_WIDE_MODEL)
  // Same ownership boundary as Small's core export, after the HPM latch.
  backend_.export_oracles();
#endif
  sample_placed(SamplePlacement::Core);
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_frontend_t1 = __rdtsc();
#endif
  if (frontend_previewed && frontend_worker_) {
    // Posted above; joined at the start of the next step.
  } else if (frontend_previewed) {
    const std::uint64_t t0 = __rdtsc();
    frontend_.commit(frontend_evaluation);
    frontend_thread_stats_.commit_ticks += __rdtsc() - t0;
  } else {
    frontend_.commit(frontend_evaluation);
  }
#if defined(CHISA_WIDE_MODEL)
  if (!(frontend_previewed && frontend_worker_)) {
    // Committed on this thread: fill the handoff the next edge reads.
    FrontendHandoff& handoff = frontend_handoff_[frontend_handoff_read_ ^ 1u];
    frontend_.fill_handoff(handoff);
    handoff.image_runs_copied_to = nullptr;
    frontend_runs_destination_ = nullptr;
    frontend_runs_from_worker_ = false;
    frontend_runs_cycle_ = cycle_ + 1;
    frontend_handoff_swap_pending_ = true;
  }
#endif
  // The memory side of this cycle: on the worker (which then also runs the
  // next cycle's pre-edge phase, reading this cycle's frontend handoff, so it
  // is posted after that handoff is filled here or posted to the frontend
  // worker), or here.
  {
    MemoryRequest request;
    request.cycle = cycle_;
    request.reset = reset_asserted_;
    request.reset_next = (cycle_ + 1) < reset_cycles_;
    request.frontend_posted = frontend_commit_pending_;
    request.frontend_handoff_index = static_cast<std::uint8_t>(frontend_handoff_read_ ^ 1u);
    request.dtm_next = dtm_outputs_next_;
    request.reset_stats = memory_stats_reset_pending_;
    memory_stats_reset_pending_ = false;
    if (oracle_sampling_enabled_) {
      request.publish_fn = publish_fn_;
      request.publish_context = publish_context_;
    }
    if (memory_worker_) {
      request.image_runs_destination =
          image_precopy_fn_ != nullptr ? image_precopy_fn_(image_precopy_context_) : nullptr;
      memory_image_runs_destination_ = request.image_runs_destination;
      memory_image_runs_cycle_ = request.cycle + 1;
      memory_cycle_ = cycle_;
      memory_pending_ = true;
      memory_outputs_joined_ = false;
      memory_worker_->post(request);
    } else {
      memory_commit_step(request);
      memory_publish_end();
    }
  }
#ifdef CHISA_PHASE_TIMERS
  std::uint64_t phase_frontend_t2 = 0;
#endif
  // Everything below reads frontend state after its commit.  With a worker
  // it runs after the wait, once the memory side has committed.
  const auto finish_frontend = [&] {
  WATCHPOINT("ftq", {
    const auto& ftq = frontend_.ftq_for_diagnostic();
    std::uint32_t current_saw_mask = 0;
    for (std::size_t i = 0; i < boomcfg::NUM_FTQ; ++i) {
      if (ftq.ghist(i).current_saw_branch_not_taken)
        current_saw_mask |= std::uint32_t{1} << i;
    }

#if defined(CHISA_WIDE_MODEL)
    const auto& enq = *frontend_evaluation.ftq_input.enq_ref;
#else
    const auto& enq = *frontend_evaluation.ftq_input.enq;
#endif

    WP_LOG("ftq",
           "get1=%u raw_idx=%u raw_csnt=%d ghist_csnt=%08x "
           "enq_v=%d enq_r=%d enq_idx=%u enq_csnt=%d",
           static_cast<unsigned>(frontend_evaluation.ftq_input.get_pc_idx[1]),
           static_cast<unsigned>(ftq.oracle_ram_idx(3)),
           static_cast<int>(
               ftq.oracle_getpc1_ghist().current_saw_branch_not_taken),
           static_cast<unsigned>(current_saw_mask),
           static_cast<int>(frontend_evaluation.ftq_input.enq_valid),
           static_cast<int>(ftq.enq_ready()),
           static_cast<unsigned>(ftq.enq_idx()),
           static_cast<int>(enq.ghist.current_saw_branch_not_taken));
  });

#ifdef CHISA_PHASE_TIMERS
  phase_frontend_t2 = __rdtsc();
  phase_counters_.frontend_tsc += phase_frontend_t2 - phase_frontend_t1;
#endif
  // With a frontend worker the Frontend placement was sampled on its thread
  // right after the commit (see FrontendWorker::sample_frontend_placement).
  if (!(frontend_previewed && frontend_worker_ && frontend_worker_samples_ == 1))
    sample_placed(SamplePlacement::Frontend);
#ifdef CHISA_PHASE_TIMERS
  phase_counters_.frontend_sample_tsc += __rdtsc() - phase_frontend_t2;
#endif
  };  // finish_frontend
  if (!(frontend_previewed && frontend_worker_)) finish_frontend();
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t phase_tail_t0 = __rdtsc();
#endif

  // The memory side of this cycle was posted (or run) after the backend
  // edge above.

  // TestHarness reset shell.  The state is sampled before the edge, exactly
  // like the generated PRE register tap.  The exact SimDTM never asserts the
  // DMCONTROL.ndmreset bit that could set the next value (fesvr/dtm.cc), so
  // this is an inductive topology property rather than a quiet-trace guess.
  reset_clock_.ndmreset_delay_observed =
      reset_clock_.ndmreset_delay_state;
  reset_clock_.ndmreset_delay_state = false;

  // The complete Small harness hard-wires UInt<2>(0) into the two external
  // interrupt inputs.  With no gateway request, PLIC pending bits can only
  // hold or be cleared by a claim; starting from reset, both remain false.
  interrupts_.plic_pending_0_observed = interrupts_.plic_pending_0_state;
  interrupts_.plic_pending_1_observed = interrupts_.plic_pending_1_state;
  interrupts_.plic_pending_0_state = false;
  interrupts_.plic_pending_1_state = false;
  // The fixed CLINT endpoint has msip=0 and reset timecmp=0.  The first
  // non-reset edge therefore raises MTIP, giving the top-level two-bit source
  // {mtip,msip}=2 from the following cycle start onward.
  interrupts_.clint_source_state = reset_asserted_ ? 0u : 2u;

  // Debug/DMI cycle-start snapshot, then edge transition.  These four fields
  // are the first independently produced slice of the complete model.  No RTL
  // value enters here: the one-beat counters are elaboration invariants and
  // the error slave cannot be selected by the exact SimDTM address map.
  debug_.error_idle_observed = debug_.error_idle_state;
  if (reset_asserted_) debug_.error_idle_state = true;
  // A frontend commit posted to the worker is joined at the start of the
  // next step (synchronize_frontend), after this thread's memory commit and
  // publication have run alongside it.

  ++cycle_;
  lsu_exception_prev_ = core_access::rob_flush(backend_.core());
#ifdef CHISA_PHASE_TIMERS
  phase_counters_.tail_tsc += __rdtsc() - phase_tail_t0;
#endif

#if !defined(CHISA_WIDE_MODEL)
  if (oracle_sampling_enabled_) export_memory_image(*this, *image_);
#endif
  // ptw.mem_resp_data = RegNext(dcache.io.lsu.resp.bits.data), ungated.
#if !defined(CHISA_WIDE_MODEL)
  image_->r.ptw.mem_resp_data = last_lsu_resp_data_;
#endif

#if defined(CHISA_WIDE_MODEL)
  // The core's deferred record fields must be complete before anything reads
  // the record: the End placement, the writer, and the next step.
  if (record_worker_) record_wait_ticks_ += record_worker_->wait(record_posted_cycle_, RecordWorker::kPublish);
#endif
  sample_placed(SamplePlacement::End);
  if (oracle_sampling_enabled_) {
    ModelBindings::instance().publish_image_owned();
    // Predict-bound lanes: cycle t's value is this post-step state (the
    // core-side ones here; the memory worker patches the memory-side one
    // after this cycle's memory commit).
    if (publish_fn_ != nullptr) {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
      // This contract predicts four current-cycle FTQ RAM read ports.
      // Their source lanes are written in the frontend's deferred tail;
      // reading/storing them before that tail completes races the publisher.
      // Join the common dependency once, then reuse its existing four values.
      // Large has no frontend predicted ports; Small commits inline.
      synchronize_frontend();
      synchronize_frontend_runs();
#endif
      publish_fn_(publish_context_, *this, PublishPhase::Predicted);
    }
  }
#ifdef CHISA_PHASE_TIMERS
  phase_counters_.step_tsc += __rdtsc() - phase_step_t0;
  ++phase_counters_.steps;
#endif
  return StepResult{};
}


// Memory side, pre-edge phase of the cycle (steps 2-3 of the order in
// step()): the DMI request, the memory-side outputs arriving this cycle, the
// tile fabric view and the cold uncore evaluation with its feedback.  Reads
// only memory-side state and the frontend handoff; leaves its results in
// dtm_outputs_, memory_input_, memory_output_, fabric_evaluation_,
// manager_feedback_ and fabric_output_.
void SystemGuider::memory_pre_outputs(bool reset, const DebugBootstrapOutputs& dtm) {
  DebugBootstrapOutputs& dtm_outputs = dtm_outputs_;
  dtm_outputs = dtm;

  MemoryStateInputs& memory_input = memory_input_;
  memory_input = MemoryStateInputs{};
  memory_input.debug_reset = reset;
  memory_input.dcache_reset = reset;
  memory_input.fabric_reset = reset;
  memory_input.dmi = components::BoomDmiRequest{
      dtm_outputs.req_valid, static_cast<std::uint8_t>(dtm_outputs.req_addr),
      static_cast<std::uint8_t>(dtm_outputs.req_op), dtm_outputs.req_data};
  memory_input.dmi_response_ready = dtm_outputs.resp_ready;
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t mo_t0 = __rdtsc();
#endif
  memory_.outputs_into(memory_input, memory_output_);
#ifdef CHISA_PHASE_TIMERS
  g_phase_sub[kSubMemoryOutputs] += __rdtsc() - mo_t0;
#endif
}

void SystemGuider::memory_pre_fabric(bool reset, std::uint64_t cycle, unsigned frontend_handoff_index,
                                     char* image_runs_destination) {
  MemoryStateInputs& memory_input = memory_input_;
  const MemoryStateOutputs& memory_output = memory_output_;
  (void)cycle;
  // Preserve the producer face.  Do not rewrite this object with hot-core
  // qualifiers: raw candidate and consumer-visible transaction are distinct
  // pieces of evidence at a seam.
  last_dcache_candidate_ = &memory_output_.dcache;
  const components::BoomUncachedOutputs& debug_path_output =
      memory_output.debug;

  // Pre-edge fabric view and cold uncore evaluation, ahead of the sampler
  // and of every tile component.  Everything it reads is registered state:
  // the held I-cache acquire offer, the D-cache/uncached tile ports, the
  // reset shell.  Evaluating it here refreshes the cold wire oracles for
  // this cycle before they are sampled; the previous design recomputed the
  // same evaluation as a post-edge "lookahead" at the end of the preceding
  // step (audited: 245,376 of 245,376 ROI cycles had identical inputs).
  const auto fabric_read = [this](std::uint32_t address) {
    return backing_memory_.read64(address);
  };
  if (core_live_ && !reset) {
    // The acquire offer comes from registered I-cache/S2 state and does not
    // depend on tl_a_ready, so it is placed directly instead of paying a
    // preliminary full frontend evaluation for it.
#if defined(CHISA_WIDE_MODEL)
    const components::SmallICache::AcquireOffer offer =
        frontend_handoff_[frontend_handoff_index].icache_acquire;
#else
    (void)frontend_handoff_index;
    const components::SmallICache::AcquireOffer offer =
        frontend_.held_icache_acquire();
#endif
    memory_input.icache_a_valid = offer.valid;
    memory_input.icache_a_address = offer.address;
  }
  // The hot tile keeps its registered TLBuffer.  Its manager-side offers are
  // first sampled without feedback, then the exact cold coherence/memory
  // chain is evaluated and its ready/B/D/E values are fed back for this edge.
  components::SmallExternalManagerInputs& manager_feedback = manager_feedback_;
  manager_feedback = components::SmallExternalManagerInputs{};
  fabric_evaluation_ = memory_.prepare_hybrid_fabric(memory_input, memory_output, fabric_read);
  auto& fabric_evaluation = fabric_evaluation_;
  // Manager offers are already complete before feedback. Avoid copying and
  // resolving the entire tile-facing output just to read these five channels.
  const auto& fabric_offer = fabric_evaluation.output;
  {  // env-gated boot seam: the model's outgoing tile A per cycle
    static const long long seam_lo = [] {
      const char* w = std::getenv("CHISA_BOOT_SEAM");
      return w ? atoll(w) : -1;
    }();
    static const long long seam_hi = [] {
      const char* w = std::getenv("CHISA_BOOT_SEAM");
      const char* dash = w ? strchr(w, '-') : nullptr;
      return dash ? atoll(dash + 1) : -1;
    }();
    if (seam_lo >= 0 && static_cast<long long>(cycle) >= seam_lo &&
        static_cast<long long>(cycle) <= seam_hi &&
        fabric_offer.manager_a_valid) {
      std::fprintf(stderr,
                   "[MSEAM c%llu] a src=%u addr=%x size=%u op=%u\n",
                   static_cast<unsigned long long>(cycle),
                   static_cast<unsigned>(fabric_offer.manager_a.source),
                   static_cast<unsigned>(fabric_offer.manager_a.address),
                   static_cast<unsigned>(fabric_offer.manager_a.size),
                   static_cast<unsigned>(fabric_offer.manager_a.opcode));
    }
  }
  const CoherentMemoryInputs cold_memory_input =
      make_cold_memory_input(reset, fabric_offer);
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t cold_t0 = __rdtsc();
#endif
  const CoherentMemoryOutputs& cold_memory_output =
      fabric_.evaluate_coherent_memory(cold_memory_input);
#ifdef CHISA_PHASE_TIMERS
  {
    const std::uint64_t cold_dt = __rdtsc() - cold_t0;
    g_phase_sub[kSubColdEvaluate] += cold_dt;
    if (cold_dt > 2000) { ++g_cold_evaluate_active; g_cold_evaluate_active_ticks += cold_dt; }
  }
#endif
  if (capture_dram_access_)
    last_dram_access_ = fabric_.dram_access(backing_memory_);

  // The Debug register router changes state when it accepts A.  Its response
  // traverses the return fabric and reaches the IOMSHR later, so using the D
  // beat as the side-effect trigger makes abstract-command completion late.
  const auto& debug_manager_input = fabric_.debug_manager_inputs();
  memory_input.debug_manager_a_fire =
      debug_manager_input.tl_a_valid && debug_manager_input.tl_d_ready;
  memory_input.debug_manager_a_source =
      static_cast<std::uint8_t>(debug_manager_input.tl_a_source);

  manager_feedback.a_ready = cold_memory_output.tile_a_ready;
  manager_feedback.b.valid = cold_memory_output.tile_b.valid;
  manager_feedback.b.opcode = cold_memory_output.tile_b.opcode;
  manager_feedback.b.param = cold_memory_output.tile_b.param;
  manager_feedback.b.size = cold_memory_output.tile_b.size;
  manager_feedback.b.source =
      cold_memory_output.tile_b.source & boomcfg::TILE_SOURCE_MASK;
  manager_feedback.b.address = cold_memory_output.tile_b.address;
  manager_feedback.b.mask = cold_memory_output.tile_b.mask;
  manager_feedback.b.data = cold_memory_output.tile_b.data;
  manager_feedback.b.corrupt = cold_memory_output.tile_b.corrupt;
  manager_feedback.c_ready = cold_memory_output.tile_c_ready;
  manager_feedback.d.valid = cold_memory_output.tile_d.valid;
  manager_feedback.d.opcode = cold_memory_output.tile_d.opcode;
  manager_feedback.d.param = cold_memory_output.tile_d.param;
  manager_feedback.d.size = cold_memory_output.tile_d.size;
  manager_feedback.d.source =
      cold_memory_output.tile_d.source & boomcfg::TILE_SOURCE_MASK;
  manager_feedback.d.sink = cold_memory_output.tile_d.sink;
  manager_feedback.d.denied = cold_memory_output.tile_d.denied;
  manager_feedback.d.data = cold_memory_output.tile_d.data;
  manager_feedback.d.data_hi = cold_memory_output.tile_d.data_hi;
  manager_feedback.d.corrupt = cold_memory_output.tile_d.corrupt;
  {
    static const bool dseam_on = std::getenv("CHISA_DMI_TRACE") != nullptr;
    static int dshown = 0;
    if (dseam_on && dshown < 80 && manager_feedback.d.valid) {
      ++dshown;
      std::fprintf(stderr, "[DSEAM c%llu] d v=1 src=%u op=%u\n",
                   (unsigned long long)cycle,
                   (unsigned)manager_feedback.d.source,
                   (unsigned)manager_feedback.d.opcode);
    }
  }
  manager_feedback.e_ready = cold_memory_output.tile_e_ready;

  fabric_output_ = &memory_.resolve_hybrid_fabric_in_place(fabric_evaluation, manager_feedback);
#if defined(CHISA_WIDE_MODEL)
  // The pre-edge memory-run lanes (the cold uncore oracles just refreshed),
  // then this cycle's memory runs into the image position named for them.
  if (oracle_sampling_enabled_) {
    boom_model::wide::publish_system_early(*this);
    while (!try_memory_image_copy(cycle, image_runs_destination)) wait_task_or_pause();
  }
#else
  (void)image_runs_destination;
#endif
}

bool SystemGuider::try_memory_image_copy(std::uint64_t cycle, char* destination) {
#if defined(CHISA_WIDE_MODEL)
  if (destination == nullptr || !oracle_sampling_enabled_) return true;
  if (memory_worker_) {
    const auto state = record_copy_gate_.state(cycle);
    if (state == RecordCopyGate::State::Pending) return false;
    if (state == RecordCopyGate::State::Cancelled) return true;
  }
  const unsigned char* record = ModelBindings::instance().record().bytes;
  std::size_t count = 0;
  const ImageRun* runs = memory_image_runs(count);
  for (std::size_t i = 0; i < count; ++i) {
    CHISA_DIAG(observe_image_source(cycle,record,runs[i].begin,runs[i].end-runs[i].begin));
    std::memcpy(destination + runs[i].begin, record + runs[i].begin, runs[i].end - runs[i].begin);
  }
#else
  (void)cycle; (void)destination;
#endif
  return true;
}

bool SystemGuider::memory_fabric_ready_for_frontend() const {
  return memory_worker_->ready(frontend_icache_memory_cycle_, memory_worker_->frontend_phase());
}

bool SystemGuider::try_frontend_task() {
  return cooperative_workers_ && frontend_worker_ && frontend_worker_->poll();
}

bool SystemGuider::try_memory_task() {
  return cooperative_workers_ && memory_worker_ && memory_worker_->poll();
}

void SystemGuider::wait_task_or_pause() const {
  if (!wait_task_ || !wait_task_(wait_task_context_)) __builtin_ia32_pause();
}

void SystemGuider::memory_commit_step(const MemoryRequest& request) {
  memory_commit_tile_step(request);
  memory_commit_fabric(request.reset);
}

void SystemGuider::memory_commit_tile_step(const MemoryRequest& request) {
  (void)request;
  fabric_.commit_ptw(ptw_input_base_);
  memory_commit_tile();
}

void SystemGuider::synchronize_memory_outputs() {
  if (!memory_pending_ || memory_outputs_joined_) return;
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t waited =
#endif
  memory_worker_->wait(memory_cycle_, MemoryWorker::kOutputs);
#ifdef CHISA_PHASE_TIMERS
  memory_wait_ticks_ += waited;
  phase_counters_.sub_tsc[5] += waited;
#endif
  memory_outputs_joined_ = true;
  memory_pre_ready_ = true;
}

void SystemGuider::synchronize_memory_fabric() {
  if (!memory_pending_) return;
  synchronize_memory_outputs();
  // A DTM redo/window drain can precede next-cycle PreStep. Cancel only the
  // speculative copy; its source publication has not happened yet.
  if (record_copy_gate_.published() < memory_cycle_ + 1) {
    record_copy_gate_.cancel(memory_cycle_ + 1);
    memory_image_runs_destination_ = nullptr;
  }
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t waited =
#endif
  memory_worker_->wait(memory_cycle_, MemoryWorker::kFabric);
#ifdef CHISA_PHASE_TIMERS
  memory_fabric_wait_ticks_ += waited;
  phase_counters_.sub_tsc[6] += waited;
  if (waited > 200) { ++memory_fabric_wait_count_; if (waited > memory_fabric_wait_max_) memory_fabric_wait_max_ = waited; }
  // Where in the cycle this join happens and when the worker signalled, both
  // relative to the request's post (ROI averages).
  fabric_join_arrival_ticks_ += (__rdtsc() - waited) - memory_worker_->post_tsc();
  fabric_signal_after_post_ticks_ += memory_worker_->fabric_signal_tsc() - memory_worker_->post_tsc();
  ++fabric_join_count_;
#endif
  memory_pending_ = false;
  memory_outputs_joined_ = false;
  last_dram_access_main_ = last_dram_access_;
}

const SystemGuider::ImageRun* SystemGuider::memory_image_runs(std::size_t& count) {
#if defined(CHISA_WIDE_MODEL)
  namespace contract = chisa::boom_model::wide::contract;
  static const ImageRun runs[3] = {
      {contract::kOwnerRunBegin[contract::kRegMemory], contract::kOwnerRunEnd[contract::kRegMemory]},
      {contract::kOwnerRunBegin[contract::kRegMemoryCut], contract::kOwnerRunEnd[contract::kRegMemoryCut]},
      {contract::kOwnerRunBegin[contract::kCombMemory], contract::kOwnerRunEnd[contract::kCombMemory]}};
  count = 3;
  return runs;
#else
  count = 0;
  return nullptr;
#endif
}

const SystemGuider::ImageRun* SystemGuider::precopied_image_runs(const char* destination,
                                                                 std::size_t& count) const {
  static thread_local ImageRun merged[9];
  count = 0;
  if (destination == nullptr) return merged;
  std::size_t fcount = 0, mcount = 0;
  const ImageRun* f = frontend_image_runs_copied_to() == destination ? frontend_image_runs(fcount) : nullptr;
  // The memory worker copies its runs before this step's backend edge (it is
  // joined at the step's start); the destination it was given is the one.
  const ImageRun* m = (memory_worker_ && memory_image_runs_cycle_ == cycle_ &&
                      memory_image_runs_destination_ == destination)
                          ? memory_image_runs(mcount) : nullptr;
  // Merge the sorted lists by offset (insertion into a short array).
  const auto add = [&](const ImageRun* runs, std::size_t n) {
    for (std::size_t k = 0; k < n; ++k) {
      if (runs[k].end <= runs[k].begin) continue;
      std::size_t pos = count;
      while (pos > 0 && merged[pos - 1].begin > runs[k].begin) { merged[pos] = merged[pos - 1]; --pos; }
      merged[pos] = runs[k];
      ++count;
    }
  };
  add(f, fcount); add(m, mcount);
  return merged;
}


// Memory side, post-edge phase (steps 6-7), tile half: the D-cache and the
// uncached path take the edge.  Everything the next cycle's outputs read is
// final after it.  Reads memory_input_ (its backend-derived fields set after
// the backend edge), memory_output_ and fabric_output_.
void SystemGuider::memory_commit_tile() {
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t sub_t3 = __rdtsc();
#endif
  memory_.commit_hybrid_tile(memory_input_, memory_output_, *fabric_output_, memory_commit_carry_);
#ifdef CHISA_PHASE_TIMERS
  if (!memory_worker_) phase_counters_.sub_tsc[3] += __rdtsc() - sub_t3;
#endif
}

// Fabric half: the tile fabric commits this cycle's beats, the cold uncore
// commits, the AXI mirror follows.  Reads the carry the tile half left,
// manager_feedback_, fabric_output_ and fabric_evaluation_; memory_input_ may
// already hold the next cycle's pre-edge fields (memory_pre_outputs).
void SystemGuider::memory_commit_fabric(bool reset) {
  // Caller-owned backing RAM behind the shared manager path.  Until the
  // core-side producers run, no request reaches this callback and the
  // storage stays empty, which is byte-for-byte what the RTL's AXI RAM
  // holds at the same point.
  const auto backing_write = [this](std::uint32_t address,
                                    std::uint64_t data) {
    backing_memory_.write64(address, data);
  };
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t sub_t3 = __rdtsc();
#endif
  memory_.commit_hybrid_fabric(memory_commit_carry_, manager_feedback_, *fabric_output_,
                               backing_write, &fabric_evaluation_);
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t cold_c0 = __rdtsc();
#endif
  fabric_.commit_coherent_memory(backing_memory_);
#ifdef CHISA_PHASE_TIMERS
  {
    const std::uint64_t cold_dc = __rdtsc() - cold_c0;
    g_phase_sub[kSubColdCommit] += cold_dc;
    if (cold_dc > 500) { ++g_cold_commit_active; g_cold_commit_active_ticks += cold_dc; }
  }
  if (!memory_worker_) phase_counters_.sub_tsc[3] += __rdtsc() - sub_t3;
#endif

  // Advance the AXI-chain register mirror off this cycle's manager beats
  // (observer only; see components/axi_chain_mirror.h).  Must run after
  // memory_.step so the snapshot is this cycle's, not last cycle's.
  if (reset) axi_mirror_.reset();
  else axi_mirror_.step(
      memory_.fabric_for_diagnostic().last_beats(),
      static_cast<std::uint8_t>(
          memory_.dcache_for_diagnostic().mshr_for_diagnostic(0).state),
      static_cast<std::uint8_t>(
          memory_.dcache_for_diagnostic().mshr_for_diagnostic(1).state));

#if !defined(CHISA_WIDE_MODEL)
  sample_placed(SamplePlacement::Memory);
#endif
}

void SystemGuider::memory_commit_phase(bool reset) {
  memory_commit_tile();
  memory_commit_fabric(reset);
}

// The post-edge memory-run lanes (the wide model's Memory placement has
// nothing placed; the End placement publishes the core-run lanes).
void SystemGuider::memory_publish_end() {
  // The debug path took its edge in the tile half: the faces the memory-side
  // lanes read (debug_stream) are rebuilt on first use.
  debug_oracles_valid_ = false;
#if defined(CHISA_WIDE_MODEL)
  if (oracle_sampling_enabled_) boom_model::wide::publish_system_end_memory(*this);
#endif
}

void SystemGuider::wait_memory_fabric_for_frontend() {
  memory_worker_->wait(frontend_icache_memory_cycle_, memory_worker_->frontend_phase());
  frontend_input_.icache_memory = fabric_output_->icache;
}

std::uint64_t SystemGuider::debug_stream(DebugStream stream) const {
  // Nine predicted lanes read this view per step; build it once.
  if (!debug_oracles_valid_) {
    debug_oracles_ = memory_.debug_path_for_diagnostic().debug_hand_oracles();
    debug_oracles_valid_ = true;
  }
  const auto& o = debug_oracles_;
  switch (stream) {
    case DebugStream::OuterXbarReadysMask: return o.outer_xbar_readys_mask;
    case DebugStream::OuterASourceWidxBin: return o.outer_a_source_widx_bin;
    case DebugStream::OuterDSinkValidReg: return o.outer_d_sink_valid_reg;
    case DebugStream::OuterInnerCtrlReadyReg: return o.outer_inner_ctrl_ready_reg;
    case DebugStream::InnerCtrlState: return o.inner_ctrl_state;
    case DebugStream::InnerCtrlSinkValidReg: return o.inner_ctrl_sink_valid_reg;
    case DebugStream::InnerDSourceReadyReg: return o.inner_d_source_ready_reg;
    case DebugStream::InnerDSourceWidxBin: return o.inner_d_source_widx_bin;
    case DebugStream::InnerASinkCdcReg: return o.inner_a_sink_cdc_reg;
    case DebugStream::InnerASinkValidReg: return o.inner_a_sink_valid_reg;
    default: return 0;
  }
}

void SystemGuider::set_oracle_sampling_enabled(bool enabled) {
  // Workers read this flag and can still be sampling the previous edge.
  if (enabled != oracle_sampling_enabled_) {
    synchronize_frontend();
    synchronize_frontend_runs();
    synchronize_memory_fabric();
  }
  // Switching sampling back on after a gap: refresh the placed batches so
  // the first sampled cycle carries current values (see resample_after_gap).
  const bool resume = enabled && !oracle_sampling_enabled_ && cycle_ > 0;
  oracle_sampling_enabled_ = enabled;
  if (resume) {

#if !defined(CHISA_WIDE_MODEL)
    export_memory_image(*this, *image_);
#endif

#if defined(CHISA_WIDE_MODEL)
    backend_.export_oracles();
#endif
    synchronize_frontend();
    synchronize_frontend_runs();
    ModelBindings::instance().resample_after_gap(*this);
  }
}

void SystemGuider::synchronize_frontend() {
  if (frontend_commit_pending_) {
#ifdef CHISA_PHASE_TIMERS
    const std::uint64_t t0 = __rdtsc();
#endif
#ifdef CHISA_PHASE_TIMERS
    frontend_thread_stats_.wait_commit_ticks +=
#endif
        frontend_worker_->wait(frontend_commit_cycle_, FrontendWorker::kCommit);
    frontend_commit_pending_ = false;
    finish_frontend_deferred();
#ifdef CHISA_PHASE_TIMERS
    phase_counters_.sub_tsc[4] += __rdtsc() - t0;
#endif
  }
  if (frontend_handoff_swap_pending_) {
    frontend_handoff_read_ ^= 1u;
    frontend_handoff_swap_pending_ = false;
  }
}

const SystemGuider::ImageRun* SystemGuider::frontend_image_runs(std::size_t& count) {
#if defined(CHISA_WIDE_MODEL)
  namespace contract = chisa::boom_model::wide::contract;
  static const ImageRun runs[3] = {
      {contract::kOwnerRunBegin[contract::kRegFrontend], contract::kOwnerRunEnd[contract::kRegFrontend]},
      {contract::kOwnerRunBegin[contract::kRegFrontendCut], contract::kOwnerRunEnd[contract::kRegFrontendCut]},
      {contract::kOwnerRunBegin[contract::kCombFrontend], contract::kOwnerRunEnd[contract::kCombFrontend]}};
  count = 3;
  return runs;
#else
  count = 0;
  return nullptr;
#endif
}

const char* SystemGuider::frontend_image_runs_copied_to() const {
#if defined(CHISA_WIDE_MODEL)
  // Recorded by this thread when it posted (or ran) the previous cycle's
  // commit: readable before that commit is joined.
  return frontend_runs_cycle_ == cycle_ ? frontend_runs_destination_ : nullptr;
#else
  return nullptr;
#endif
}

void SystemGuider::synchronize_frontend_runs() {
  if (frontend_worker_) frontend_worker_->wait_runs(frontend_commit_cycle_);
}

void SystemGuider::finish_frontend_deferred() {
  // The Frontend placement is sampled on the worker right after its commit
  // unless an export ring is attached; then it is sampled here, before the
  // record is published.
  if (frontend_worker_samples_ != 1) {
    synchronize_frontend_runs();
    sample_placed(SamplePlacement::Frontend);
  }
}

void SystemGuider::sample_placed(ModelBindings::SamplePlacement placement) {
  if (!oracle_sampling_enabled_) return;
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t t0 = __rdtsc();
#endif
  ModelBindings::instance().sample_placed(placement, *this);
#ifdef CHISA_PHASE_TIMERS
  const std::uint64_t dt = __rdtsc() - t0;
  phase_counters_.sample_tsc += dt;
  const std::size_t p = static_cast<std::size_t>(placement);
  if (p < 5) phase_counters_.sample_by_placement_tsc[p] += dt;
#endif
}

bool SystemGuider::debug_roi_quiescent() const {
  const auto& core = backend_.core();
  return !reset_asserted_ && !core_access::csr(core).debug && !debug_.dmactive_state &&
         !debug_.clock_en_state && !debug_.top_dmactive_ack_sync_2 &&
         !debug_.top_dmactive_ack_sync_1 &&
         !debug_.top_dmactive_ack_sync_0 &&
         !debug_.outer_dmactive_ack_sync_2 &&
         !debug_.outer_dmactive_ack_sync_1 &&
         !debug_.outer_dmactive_ack_sync_0 &&
         !debug_.inner_dmactive_sync_2 &&
         !debug_.inner_dmactive_sync_1 &&
         !debug_.inner_dmactive_sync_0 && !debug_.int_sync_2 &&
         !debug_.int_sync_1 && !debug_.int_sync_0;
}

std::vector<std::string> SystemGuider::sentinel_failures() const {
  std::vector<std::string> failures;
  // Sentinels are added alongside the subsystem they guard. Each one is an
  // invariant over model state that must hold regardless of what the RTL does,
  // so it catches the model contradicting itself -- a class of bug the probes
  // cannot see, because there is no RTL signal to compare against.
  //
  // The archived Sodor model is the reference for the shape: fetch PC
  // alignment, enum fields inside their declared range, and the control and
  // datapath shadow copies of a hazard agreeing with each other.
  if (debug_.bypass_stall_beats_left != 0)
    failures.emplace_back("DMI bypass one-beat counter is nonzero");
  if (debug_.error_arbiter_beats_left != 0)
    failures.emplace_back("DMI error arbiter one-beat counter is nonzero");
  if (debug_.xbar_beats_left != 0)
    failures.emplace_back("DMI crossbar one-beat counter is nonzero");
  if (reset_clock_.ndmreset_delay_observed ||
      reset_clock_.ndmreset_delay_state)
    failures.emplace_back("TestHarness ndmreset delay is nonzero");
  if (interrupts_.plic_pending_0_observed ||
      interrupts_.plic_pending_1_observed ||
      interrupts_.plic_pending_0_state || interrupts_.plic_pending_1_state)
    failures.emplace_back(
        "PLIC pending state is nonzero with hard-wired-zero sources");
  if (!fabric_.coherent_memory_converged())
    failures.emplace_back("cold coherent memory boundary did not converge");
  return failures;
}

// Unified storage regions: watched fields stored inside these objects are
// committed by a line compare of the object's own memory instead of a
// field-by-field gather (see ModelBindings::unify_region).
void declare_unified_regions(const SystemGuider& model, ModelBindings& bindings) {
  bindings.unify_region(&model.backend(), sizeof(model.backend()), "backend");
  bindings.unify_region(&model.memory(), sizeof(model.memory()), "memory");
  bindings.unify_region(&model.dtlb(), sizeof(model.dtlb()), "dtlb");
  bindings.unify_region(&model.axi_mirror(), sizeof(model.axi_mirror()), "axi-mirror");
  bindings.unify_region(&model.debug(), sizeof(model.debug()), "debug");
#if defined(CHISA_WIDE_MODEL)
  bindings.unify_region(&model.frontend(),sizeof(model.frontend()),"native-frontend");
#define CHISA_NATIVE_UNIFY_COLD(accessor) \
  { const auto& source=model.fabric().accessor(); \
    bindings.unify_region(&source,sizeof(source),"native-" #accessor); }
  CHISA_NATIVE_UNIFY_COLD(system_bus_oracles)
  CHISA_NATIVE_UNIFY_COLD(periphery_bus_oracles)
  CHISA_NATIVE_UNIFY_COLD(coherent_memory_oracles)
  CHISA_NATIVE_UNIFY_COLD(mbus_memory_oracles)
  CHISA_NATIVE_UNIFY_COLD(mmio_memory_oracles)
  CHISA_NATIVE_UNIFY_COLD(ptw_oracles)
  CHISA_NATIVE_UNIFY_COLD(fpu_oracles)
  CHISA_NATIVE_UNIFY_COLD(fdivsqrt_oracles)
#undef CHISA_NATIVE_UNIFY_COLD
#endif
}

}  // namespace chisa::boom_system
