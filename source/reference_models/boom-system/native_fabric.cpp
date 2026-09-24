#include <cstring>
#include "native_fabric.h"

#include "components/page_walker_model.h"

// Independent software protocol and arithmetic components.
#include <array>
#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <cstdlib>

#ifdef CHISA_PHASE_TIMERS
#include <x86intrin.h>
#endif
namespace chisa::boom_system {
// Per-module cost of the cold uncore fixed point (phase builds): ticks and
// calls of each module's evaluate (kind 0) and commit (kind 1).
enum ColdModule : unsigned {
  kColdDebugInner, kColdSbus, kColdBootrom, kColdPlic, kColdCbus, kColdMmioFrag, kColdMmioBuf, kColdMmioRam,
  kColdCoherence, kColdMbus, kColdAxiFrag, kColdAxiBuf, kColdAxiRam, kColdOracles, kColdBoundary, kColdModuleCount
};
#ifdef CHISA_PHASE_TIMERS
static std::uint64_t g_cold_ticks[kColdModuleCount][2], g_cold_calls[kColdModuleCount][2];
static inline std::uint64_t cold_now() { return __rdtsc(); }
static inline void cold_add(ColdModule m, int kind, std::uint64_t t0) { g_cold_ticks[m][kind] += __rdtsc() - t0; ++g_cold_calls[m][kind]; }
void cold_module_timing_reset() { std::memset(g_cold_ticks, 0, sizeof(g_cold_ticks)); std::memset(g_cold_calls, 0, sizeof(g_cold_calls)); }
void cold_module_sizes_report();
void cold_module_timing_report(double ns_per_tick, double cycles) {
  cold_module_sizes_report();
  static const char* const names[kColdModuleCount] = {"debug_inner", "sbus", "bootrom", "plic", "cbus", "mmio_frag", "mmio_buf", "mmio_ram",
                                                      "coherence", "mbus", "axi_frag", "axi_buf", "axi_ram", "oracles", "boundary"};
  std::fprintf(stderr, "SYSBENCH_COLD per-cycle ns (calls, ns each) evaluate/commit:");
  for (unsigned m = 0; m < kColdModuleCount; ++m)
    std::fprintf(stderr, " %s=%.1f(%llu,%.0f)/%.1f(%llu,%.0f)", names[m],
                 g_cold_ticks[m][0] * ns_per_tick / cycles, static_cast<unsigned long long>(g_cold_calls[m][0]),
                 g_cold_calls[m][0] ? g_cold_ticks[m][0] * ns_per_tick / g_cold_calls[m][0] : 0.0,
                 g_cold_ticks[m][1] * ns_per_tick / cycles, static_cast<unsigned long long>(g_cold_calls[m][1]),
                 g_cold_calls[m][1] ? g_cold_ticks[m][1] * ns_per_tick / g_cold_calls[m][1] : 0.0);
  std::fprintf(stderr, "\n");
}
#else
static inline std::uint64_t cold_now() { return 0; }
static inline void cold_add(ColdModule, int, std::uint64_t) {}
void cold_module_timing_reset() {}
void cold_module_timing_report(double, double) {}
#endif
}  // namespace chisa::boom_system

#include "components/small_plic.h"
#include "components/axi_buffer_model.h"
#include "components/axi_fragmenter_model.h"
#include "components/coherence_model.h"
#include "components/fdiv64_model.h"
#include "components/fpu_model.h"
#include "protocol/memory_bus.h"
#include "components/memory_bus_model.h"
#include "protocol/peripheral.h"
#include "components/periphery_bus_model.h"
#include "protocol/ptw.h"
#include "components/axi_ram_model.h"
#include "protocol/system_bus.h"
#include "components/system_bus_model.h"

#if defined(CHISA_WIDE_MODEL)
constexpr std::size_t kSbusReadysMaskSlot = chisa::boom_system::cold_contract::sbus_readys;
constexpr std::size_t kSbusState1Slot = chisa::boom_system::cold_contract::sbus_state1;
#else
constexpr std::size_t kSbusReadysMaskSlot = 84;
constexpr std::size_t kSbusState1Slot = 95;
#endif

#include "components/boot_rom_model.h"

namespace chisa::boom_system {

struct NativeFabric::Impl {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  components::CoherenceModel coherence_manager{0,5};
#else
  components::CoherenceModel coherence_manager;
#endif
  components::SystemBusModel system_bus;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  components::PeripheryBusModel periphery_bus{16};
#else
  components::PeripheryBusModel periphery_bus;
#endif
  components::SmallPlic plic;
  components::BootRomModel bootrom;
  // Main-thread FP work must not share cache lines with the memory owner.
  // PTW evaluation/commit crosses those owners deliberately, but its own
  // line boundaries must not also invalidate FP or MemoryBus state. Keep
  // these boundaries stable when generated bus representations change size.
  alignas(64) components::Fdiv64Model fdivsqrt;
  alignas(64) components::FpuModel fpu;
  alignas(64) components::PageWalkerModel ptw;
  alignas(64) components::MemoryBusModel memory_bus;
  components::AxiFragmenterModel axi_fragmenter;
  components::AxiBufferModel axi_buffer;
  components::SparseAxiRam axi_ram;
  components::AxiFragmenterModel mmio_axi_fragmenter{31};
  components::AxiBufferModel mmio_axi_buffer{31};
  components::SparseAxiRam mmio_axi_ram{UINT32_C(0x1ff)};

  protocol::AxiStageInputs axi_fragmenter_inputs{};
  protocol::AxiStageInputs axi_buffer_inputs{};
  protocol::SparseAxiRamInputs axi_ram_inputs{};
  protocol::SparseAxiRamOutputs axi_ram_outputs{};
  protocol::AxiStageInputs mmio_axi_fragmenter_inputs{};
  protocol::AxiStageInputs mmio_axi_buffer_inputs{};
  protocol::SparseAxiRamInputs mmio_axi_ram_inputs{};
  protocol::SparseAxiRamOutputs mmio_axi_ram_outputs{};
  protocol::CoherenceManagerInputs coherence_manager_inputs{};
  protocol::SystemBusInputs system_bus_inputs{};
  protocol::PeripheryBusInputs periphery_bus_inputs{};
  protocol::DebugInnerInputs debug_inner_inputs{};
  protocol::DebugInnerOutputs debug_inner_outputs{};
  std::uint64_t (*debug_reader)(const void*, std::uint32_t, bool) = nullptr;
  const void* debug_reader_context = nullptr;
  protocol::RomInputs bootrom_inputs{};
  protocol::MbusCouplerInputs memory_bus_inputs{};
  CoherentMemoryOutputs coherent_memory_outputs{};
  MbusMemoryOracleState mbus_memory_oracles{};
  MbusMemoryOracleState mmio_memory_oracles{};
  CoherentMemoryOracleState coherent_memory_oracles{};
  SystemBusOracleState system_bus_oracles{};
  PeripheryBusOracleState periphery_bus_oracles{};
  SystemBusBoundaryTransaction last_system_bus_boundary_transaction{};
  CoherenceBoundaryTransaction last_coherence_boundary_transaction{};
  bool coherent_memory_converged = true;
  bool coherent_memory_pending = false;
  std::uint64_t coherent_memory_lookahead_skipped = 0;
  // Idle-skip trackers.  The committed snapshot gates the pre-edge skip
  // (whose pending=false also no-ops the commit): an input may only skip
  // commit when the identical input was already committed.  The evaluated
  // snapshot tracks whichever path filled the output/oracle caches last,
  // gating cache reuse.  A lookahead input must never satisfy the commit
  // gate: it previews the next pre-edge offer, and treating it as committed
  // drops that offer's edge entirely (boot hangs on the first A beat).
  CoherentMemoryInputs last_coherent_memory_input{};
  bool coherent_memory_input_valid = false;
  CoherentMemoryInputs last_evaluated_coherent_memory_input{};
  bool coherent_memory_evaluated_valid = false;
  std::uint64_t coherent_memory_skipped = 0;
  // Lookahead audit: pre-edge evaluations whose input equals the previous
  // step's lookahead input (the lookahead was exact), and how many of those
  // still re-ran the fixed point because the fabric was active.
  std::uint64_t coherent_memory_pre_edge_equal_lookahead = 0;
  std::uint64_t coherent_memory_pre_edge_recomputed = 0;
  std::uint64_t coherent_memory_pre_edge_total = 0;

  // Oracle-array versions: bumped by every refresh, so a watch on the
  // version (one hot line) stands for the whole array.
  // One line each: a bump of one array must not wake the others' watchers.
  alignas(64) std::uint64_t system_bus_oracle_version = 0;
  alignas(64) std::uint64_t periphery_bus_oracle_version = 0;
  alignas(64) std::uint64_t mbus_memory_oracle_version = 0;
  alignas(64) std::uint64_t mmio_memory_oracle_version = 0;
  alignas(64) std::uint64_t coherent_memory_oracle_version = 0;

  void refresh_system_bus_oracles() {
    ++system_bus_oracle_version;
    const auto& s=system_bus.state();
#if defined(CHISA_WIDE_MODEL)
#include "system_bus_native_capture.inc"
#else
#include "generated/system_bus_native_capture.inc"
#endif
  }

  void refresh_periphery_bus_oracles() {
    ++periphery_bus_oracle_version;
    const auto& s = periphery_bus.state();
#if defined(CHISA_WIDE_MODEL)
#include "periphery_bus_native_capture.inc"
#else
#include "generated/periphery_bus_native_capture.inc"
#endif
  }

  const protocol::PeripheryBusOutputs& periphery_bus_outputs() const {
    return periphery_bus.outputs();
  }
  bool periphery_bus_active() const { return periphery_bus.active(); }

  static void capture_axi_memory_oracles(
      const components::AxiFragmenterModel::State& fragmenter_state,
      const components::AxiBufferModel::State& buffer_state, const components::SparseAxiRam& ram,
      unsigned address_bits, MbusMemoryOracleState& oracles) {
    const auto& b = buffer_state.b;
    oracles.buf_b_maybe_full = b.wrap_state();
    oracles.buf_b_enq_ptr = b.write_index();
    oracles.buf_b_deq_ptr = b.read_index();
    oracles.buf_b_echo_real_last = b.head().echo_real_last;
    oracles.buf_b_id = b.head().id;
    oracles.buf_b_resp = b.head().response;

    const auto& r = buffer_state.r;
    oracles.buf_r_maybe_full = r.wrap_state();
    oracles.buf_r_enq_ptr = r.write_index();
    oracles.buf_r_deq_ptr = r.read_index();
    oracles.buf_r_data = r.head().data;
    oracles.buf_r_echo_real_last = r.head().echo_real_last;
    oracles.buf_r_id = r.head().id;
    oracles.buf_r_last = r.head().last;
    oracles.buf_r_resp = r.head().response;

    const auto& ar = buffer_state.ar;
    oracles.buf_ar_maybe_full = ar.wrap_state();
    oracles.buf_ar_enq_ptr = ar.write_index();
    oracles.buf_ar_deq_ptr = ar.read_index();
    oracles.buf_ar_addr = ar.head().address;
    oracles.buf_ar_echo_real_last = ar.head().echo_real_last;
    oracles.buf_ar_id = ar.head().id;

    const auto& aw = buffer_state.aw;
    oracles.buf_aw_maybe_full = aw.wrap_state();
    oracles.buf_aw_deq_ptr = aw.read_index();
    oracles.buf_aw_addr = aw.head().address;
    oracles.buf_aw_echo_real_last = aw.head().echo_real_last;
    oracles.buf_aw_id = aw.head().id;

    const auto& w = buffer_state.w;
    oracles.buf_w_maybe_full = w.wrap_state();
    oracles.buf_w_enq_ptr = w.write_index();
    oracles.buf_w_deq_ptr = w.read_index();
    oracles.buf_w_data = w.head().data;
    oracles.buf_w_last = w.head().last;
    oracles.buf_w_strb = w.head().strobe;

    const auto pack_fragmenter_request = [&](const protocol::AxiAddress& request) {
      const std::uint64_t mask = address_bits == 32 ? UINT32_MAX : UINT32_MAX >> 1;
      return (std::uint64_t(request.id & 15) << (address_bits + 13)) |
             ((std::uint64_t(request.address) & mask) << 13) |
             (std::uint64_t(request.length) << 5) | (std::uint64_t(request.size) << 2) | request.burst;
    };
    const auto& ar_request=fragmenter_state.ar.head();
    const auto& aw_request=fragmenter_state.aw.head();
    oracles.frag_busy=fragmenter_state.read.busy;
    oracles.frag_busy_1=fragmenter_state.write.busy;
    oracles.frag_deq_maybe_full=fragmenter_state.ar.wrap_state();
    oracles.frag_deq_1_maybe_full=fragmenter_state.aw.wrap_state();
    oracles.frag_deq_bank=pack_fragmenter_request(ar_request);
    oracles.frag_deq_1_bank=pack_fragmenter_request(aw_request);
    oracles.frag_deq_id=ar_request.id;
    oracles.frag_deq_addr=ar_request.address;
    oracles.frag_deq_len=ar_request.length;
    oracles.frag_deq_size=ar_request.size;
    oracles.frag_deq_burst=ar_request.burst;
    oracles.frag_deq_1_id=aw_request.id;
    oracles.frag_deq_1_addr=aw_request.address;
    oracles.frag_deq_1_len=aw_request.length;
    oracles.frag_deq_1_size=aw_request.size;
    oracles.frag_deq_1_burst=aw_request.burst;
    oracles.frag_in_w_maybe_full=fragmenter_state.w.wrap_state();
    oracles.frag_in_w_data=fragmenter_state.w.head().data;
    oracles.frag_in_w_strb=fragmenter_state.w.head().strobe;
    oracles.frag_r_addr=fragmenter_state.read.address;
    oracles.frag_r_addr_1=fragmenter_state.write.address;
    oracles.frag_r_len=fragmenter_state.read.length;
    oracles.frag_r_len_1=fragmenter_state.write.length;
    oracles.frag_w_counter=fragmenter_state.write_beats;
    oracles.frag_wbeats_latched=fragmenter_state.write_length_latched;

    oracles.ram_r_full = ram.r_full();
    oracles.ram_r_id = ram.r_id();
    oracles.ram_rdata_addr_pipe = ram.read_address_pipe();
    oracles.ram_w_echo_real_last = ram.w_echo_real_last();
    oracles.ram_w_full = ram.w_full();
    oracles.ram_w_id = ram.w_id();
  }

  void refresh_mbus_memory_oracles() {
    ++mbus_memory_oracle_version;
    ++mmio_memory_oracle_version;
    capture_axi_memory_oracles(axi_fragmenter.state(),
                               axi_buffer.state(), axi_ram,
                               32, mbus_memory_oracles);
    capture_axi_memory_oracles(mmio_axi_fragmenter.state(),
                               mmio_axi_buffer.state(),
                               mmio_axi_ram, 31, mmio_memory_oracles);
  }

  void refresh_coherent_memory_oracles() {
    ++coherent_memory_oracle_version;
    const auto& broadcast = coherence_manager.state();
    for (unsigned index=0;index<4;++index) {
      const auto& input=broadcast.trackers[index];
      auto& out=coherent_memory_oracles.trackers[index];
      out.address=input.request.address;out.count=input.probe_pending;
      out.got_e=input.got_e;out.sent_d=input.sent_d;out.shared=input.shared;
      out.opcode=input.request.opcode;out.size=input.request.size;out.source=input.request.source;
      out.o_maybe_full=input.data.wrap_state();out.o_enq_ptr=input.data.write_index();out.o_deq_ptr=input.data.read_index();
    }
    const auto& tracker = coherent_memory_oracles.trackers[0];
    coherent_memory_oracles.tracker_address = tracker.address;
    coherent_memory_oracles.tracker_got_e = tracker.got_e;
    coherent_memory_oracles.tracker_o_maybe_full = tracker.o_maybe_full;
    coherent_memory_oracles.tracker_o_enq_ptr = tracker.o_enq_ptr;
    coherent_memory_oracles.tracker_o_deq_ptr = tracker.o_deq_ptr;
    coherent_memory_oracles.tracker_opcode = tracker.opcode;
    coherent_memory_oracles.tracker_sent_d = tracker.sent_d;
    coherent_memory_oracles.tracker_size = tracker.size;
    coherent_memory_oracles.tracker_source = tracker.source;
    coherent_memory_oracles.broadcast_beats_left=broadcast.tile_d.remaining;
    coherent_memory_oracles.broadcast_beats_left_1=broadcast.memory_a.remaining;
    coherent_memory_oracles.broadcast_state_1_0=broadcast.memory_a.owner&1;
    coherent_memory_oracles.broadcast_state_1_1=(broadcast.memory_a.owner>>1)&1;
    coherent_memory_oracles.broadcast_state_1_2=(broadcast.memory_a.owner>>2)&1;
    coherent_memory_oracles.broadcast_state_1_3=(broadcast.memory_a.owner>>3)&1;
    coherent_memory_oracles.broadcast_state_1_4=(broadcast.memory_a.owner>>4)&1;
    coherent_memory_oracles.broadcast_state__0=broadcast.tile_d.owner&1;
    coherent_memory_oracles.broadcast_state__1=(broadcast.tile_d.owner>>1)&1;
    coherent_memory_oracles.broadcast_reg=broadcast.probe_valid;
    coherent_memory_oracles.broadcast_reg_1=broadcast.probe_line;
    coherent_memory_oracles.broadcast_reg_2=broadcast.probe_permissions;
    coherent_memory_oracles.broadcast_counter_2=broadcast.a_remaining;
    coherent_memory_oracles.broadcast_counter=broadcast.d_remaining;
    coherent_memory_oracles.broadcast_r=broadcast.d_trackers;

    const auto& bus=memory_bus.state();
    for (std::size_t index=0;index<32;++index) {
      const auto& queue=index<16?bus.read_echo[index]:bus.write_echo[index-16];
      auto& out=coherent_memory_oracles.all_yank[index];
      out.deq_ptr=queue.read_index();out.enq_ptr=queue.write_index();out.maybe_full=queue.wrap_state();
      out.extra_id=queue.head().extra_id;out.size=queue.head().size;out.source=queue.head().source;
    }
    coherent_memory_oracles.yank[0]=coherent_memory_oracles.all_yank[0];
    coherent_memory_oracles.yank[1]=coherent_memory_oracles.all_yank[1];
    coherent_memory_oracles.yank[2]=coherent_memory_oracles.all_yank[18];
    coherent_memory_oracles.tl2axi4_counter=bus.a_remaining;
    coherent_memory_oracles.tl2axi4_done_aw=bus.address_sent;
    coherent_memory_oracles.tl2axi4_r_holds_d=bus.read_holds_response;
    coherent_memory_oracles.tl2axi4_b_delay=bus.b_delay;
    coherent_memory_oracles.tl2axi4_deq_maybe_full=bus.data.wrap_state();
    coherent_memory_oracles.tl2axi4_deq_data=bus.data.head().data;
    coherent_memory_oracles.tl2axi4_deq_strb=bus.data.head().strobe;
    coherent_memory_oracles.tl2axi4_arw_maybe_full=bus.address.wrap_state();
    const auto& arw=bus.address.head();
    const auto& address=arw.payload;
    coherent_memory_oracles.tl2axi4_arw_id=address.id;
    coherent_memory_oracles.tl2axi4_arw_addr=address.address;
    coherent_memory_oracles.tl2axi4_arw_len=address.length;
    coherent_memory_oracles.tl2axi4_arw_size=address.size;
    coherent_memory_oracles.tl2axi4_arw_burst=address.burst;
    coherent_memory_oracles.tl2axi4_arw_wen=arw.write;
    coherent_memory_oracles.tl2axi4_arw_echo_tl_state_size=arw.echo.size;
    coherent_memory_oracles.tl2axi4_arw_echo_tl_state_source=arw.echo.source;
    coherent_memory_oracles.tl2axi4_arw_bank=
        (std::uint64_t(address.id&127)<<57) | (std::uint64_t(address.address)<<25) |
        (std::uint64_t(address.length)<<17) | (std::uint64_t(address.size)<<14) |
        (std::uint64_t(address.burst)<<12) | (std::uint64_t(arw.echo.size)<<8) |
        (std::uint64_t(arw.echo.source)<<1) | arw.write;
    // The live upstream source can change during the post-edge fixed point.
    coherent_memory_oracles.tl2axi4_gen_257=bus.outstanding[coherence_manager.outputs().mbus_a.source&127];
  }
};

NativeFabric::NativeFabric() : impl_(std::make_unique<Impl>()) {
  impl_->refresh_system_bus_oracles();
  impl_->refresh_periphery_bus_oracles();
}
NativeFabric::~NativeFabric() = default;

void NativeFabric::commit_fdivsqrt(
    const protocol::FDivSqrtInputs& inputs) {
  impl_->fdivsqrt.commit(inputs);
}

const protocol::FDivSqrtOutputs&
NativeFabric::fdivsqrt_outputs() const {
  return impl_->fdivsqrt.outputs();
}

const protocol::FDivSqrtOracleState&
NativeFabric::fdivsqrt_oracles() const {
  return impl_->fdivsqrt.oracles();
}

bool NativeFabric::fdivsqrt_active() const {
  return impl_->fdivsqrt.active();
}

std::uint64_t NativeFabric::fdivsqrt_eval_count() const {
  return impl_->fdivsqrt.eval_count();
}

std::uint64_t NativeFabric::fdivsqrt_skipped_count() const {
  return impl_->fdivsqrt.skipped_count();
}

void NativeFabric::commit_fpu(const protocol::FpuInputs& inputs) {
  impl_->fpu.commit(inputs);
}

const protocol::FpuOutputs& NativeFabric::fpu_outputs() const {
  return impl_->fpu.outputs();
}

const protocol::FpuOracleState& NativeFabric::fpu_oracles() const {
  return impl_->fpu.oracles();
}

bool NativeFabric::fpu_active() const { return impl_->fpu.active(); }

std::uint64_t NativeFabric::fpu_eval_count() const {
  return impl_->fpu.eval_count();
}

std::uint64_t NativeFabric::fpu_skipped_count() const {
  return impl_->fpu.skipped_count();
}

const protocol::PtwOutputs& NativeFabric::evaluate_ptw(
    const protocol::PtwInputs& inputs) {
  return impl_->ptw.evaluate(inputs);
}

void NativeFabric::commit_ptw(const protocol::PtwInputs& inputs) {
  impl_->ptw.commit(inputs);
}

const protocol::PtwOutputs& NativeFabric::ptw_outputs() const {
  return impl_->ptw.outputs();
}

const protocol::PtwOracleState& NativeFabric::ptw_oracles() const {
  return impl_->ptw.oracles();
}

bool NativeFabric::ptw_active() const { return impl_->ptw.active(); }
std::uint64_t NativeFabric::ptw_eval_count() const { return impl_->ptw.eval_count(); }
std::uint64_t NativeFabric::ptw_skipped_count() const { return impl_->ptw.skipped_count(); }

namespace {

protocol::AxiAddress to_axi_address(
    const protocol::MbusAxiAw& input) {
  protocol::AxiAddress result;
  result.valid = input.valid;
  result.id = input.id;
  result.address = input.address;
  result.length = input.length;
  result.size = input.size;
  result.burst = input.burst;
  result.lock = input.lock;
  result.cache = input.cache;
  result.protection = input.protection;
  result.qos = input.qos;
  return result;
}

protocol::AxiWriteData to_axi_write(
    const protocol::MbusAxiW& input) {
  protocol::AxiWriteData result;
  result.valid = input.valid;
  result.data = input.data;
  result.strobe = input.strobe;
  result.last = input.last;
  return result;
}

protocol::MbusAxiB to_mbus_b(
    const protocol::AxiWriteResponse& input) {
  protocol::MbusAxiB result;
  result.valid = input.valid;
  result.id = input.id;
  result.response = input.response;
  return result;
}

protocol::MbusAxiR to_mbus_r(
    const protocol::AxiReadResponse& input) {
  protocol::MbusAxiR result;
  result.valid = input.valid;
  result.id = input.id;
  result.data = input.data;
  result.response = input.response;
  result.last = input.last;
  return result;
}

}  // namespace

void NativeFabric::set_debug_reader(
    std::uint64_t (*reader)(const void*, std::uint32_t, bool), const void* context) {
  impl_->debug_reader = reader;
  impl_->debug_reader_context = context;
}

const protocol::DebugInnerInputs&
NativeFabric::debug_manager_inputs() const {
  return impl_->debug_inner_inputs;
}

namespace {
/** Hand-written CBus manager face of the Debug Module: the register router
  * answers in the cycle of the request (a.ready = d.ready, d.valid =
  * a.valid), AccessAckData for a Get with the 64-bit word of the hand
  * memory map, AccessAck for a Put.  The uncached path applies hart-write
  * side effects (HALTED/GOING/RESUMING, DATA) on this face's A handshake. */
protocol::DebugInnerOutputs hand_debug_manager_face(
    const protocol::DebugInnerInputs& in,
    std::uint64_t (*reader)(const void*, std::uint32_t, bool), const void* ctx) {
  protocol::DebugInnerOutputs out;
  out.tl_a_ready = in.tl_d_ready;
  out.tl_d_valid = in.tl_a_valid;
  const bool get = in.tl_a_opcode == 4;
  out.tl_d_opcode = get ? 1 : 0;
  out.tl_d_param = 0;
  out.tl_d_size = in.tl_a_size;
  out.tl_d_source = in.tl_a_source;
  out.tl_d_sink = false;
  out.tl_d_denied = false;
  out.tl_d_corrupt = false;
  out.tl_d_data = (in.tl_a_valid && reader != nullptr)
                      ? reader(ctx, static_cast<std::uint32_t>(in.tl_a_address) &
                                        ~UINT32_C(7), get)
                      : 0;
  return out;
}
}  // namespace

const CoherentMemoryOutputs& NativeFabric::evaluate_coherent_memory(
    const CoherentMemoryInputs& external, bool is_lookahead) {
  // Idle skip: if no fabric register changed on the last committed edge
  // (!coherent_memory_active(), which covers every stateful module in the
  // fixed point) and this boundary input is bit-identical to the input of
  // the last full evaluation, the wires are a function of unchanged
  // registers and an unchanged input, so the cached outputs and wire
  // oracles are already exact.  That is enough for the post-edge lookahead.
  // The pre-edge skip additionally sets pending=false, which no-ops the
  // paired commit, so it further requires equality with the last committed
  // input -- an input only previewed by a lookahead still needs its edge.
  const bool equals_lookahead =
      impl_->coherent_memory_evaluated_valid &&
      external == impl_->last_evaluated_coherent_memory_input;
  if (!is_lookahead) {
    ++impl_->coherent_memory_pre_edge_total;
    if (equals_lookahead) ++impl_->coherent_memory_pre_edge_equal_lookahead;
  }
  if (!external.reset && impl_->coherent_memory_evaluated_valid &&
      !coherent_memory_active() &&
      equals_lookahead) {
    if (is_lookahead) {
      ++impl_->coherent_memory_lookahead_skipped;
      return impl_->coherent_memory_outputs;
    }
    // coherent_memory_active() covers this chain's queues and pending
    // transactions. FPU/PTW/standalone-mbus activity has a separate commit
    // owner and must not wake the otherwise unchanged memory fabric.
    if (impl_->coherent_memory_input_valid &&
        external == impl_->last_coherent_memory_input) {
      ++impl_->coherent_memory_skipped;
      // Leaving coherent_memory_pending false also no-ops the paired commit.
      impl_->coherent_memory_pending = false;
      return impl_->coherent_memory_outputs;
    }
  }
  impl_->last_evaluated_coherent_memory_input = external;
  impl_->coherent_memory_evaluated_valid = true;
  if (!is_lookahead) {
    if (equals_lookahead) ++impl_->coherent_memory_pre_edge_recomputed;
    impl_->last_coherent_memory_input = external;
    impl_->coherent_memory_input_valid = true;
  }
  impl_->coherent_memory_converged = false;
  impl_->coherent_memory_pending = true;

  // Every component is evaluated from the same pre-edge register image.  The
  // loop only resolves ready/valid paths; no register is committed here.
  for (unsigned iteration = 0; iteration < 24; ++iteration) {
    bool changed = false;
    const auto needs_evaluation = [&](auto& previous, const auto& next) {
      const bool dirty = !(previous == next);
      changed |= dirty;
      if (dirty) previous = next;
      // The first pass observes the new PRE state and arms every component's
      // pending edge. Later passes only propagate changed dependencies; no
      // component commits inside this fixed point.
      return iteration == 0 || dirty;
    };

    const auto& coherence_before = impl_->coherence_manager.outputs();
    const auto& periphery_before = impl_->periphery_bus_outputs();

    // The Debug Module is the selected CBus manager, not a parallel shortcut
    // from the hot IOMSHR.  Its hand-written register-router face is
    // evaluated from the same pre-edge register image as PeripheryBus so
    // A-ready and D-valid participate in this fixed point.
    protocol::DebugInnerInputs debug_inner = impl_->debug_inner_inputs;
    debug_inner.tl_a_valid = periphery_before.debug.a.valid;
    debug_inner.tl_a_opcode = periphery_before.debug.a.opcode;
    debug_inner.tl_a_param = periphery_before.debug.a.param;
    debug_inner.tl_a_size = periphery_before.debug.a.size;
    debug_inner.tl_a_source = periphery_before.debug.a.source;
    debug_inner.tl_a_address = periphery_before.debug.a.address;
    debug_inner.tl_a_mask = periphery_before.debug.a.mask;
    debug_inner.tl_a_data = periphery_before.debug.a.data;
    debug_inner.tl_a_corrupt = periphery_before.debug.a.corrupt;
    debug_inner.tl_d_ready = periphery_before.debug.d_ready;
    if (needs_evaluation(impl_->debug_inner_inputs, debug_inner)) {
      const std::uint64_t t0 = cold_now();
      impl_->debug_inner_outputs = hand_debug_manager_face(
          debug_inner, impl_->debug_reader, impl_->debug_reader_context);
      cold_add(kColdDebugInner, 0, t0);
    }
    const auto& debug_before = impl_->debug_inner_outputs;

    protocol::SystemBusInputs system_bus;
    system_bus.reset = external.reset;
    system_bus.tile_a = external.tile_a;
    system_bus.tile_b_ready = external.tile_b_ready;
    system_bus.tile_c = external.tile_c;
    system_bus.tile_d_ready = external.tile_d_ready;
    system_bus.tile_e = external.tile_e;
    system_bus.l2_a_ready = coherence_before.tile_a_ready;
    system_bus.l2_b = coherence_before.tile_b;
    system_bus.l2_c_ready = coherence_before.tile_c_ready;
    system_bus.l2_d = coherence_before.tile_d;
    system_bus.l2_e_ready = coherence_before.tile_e_ready;
    // FBus is structurally tied off in the locked TestHarness.  CBus is closed
    // by the extracted PeripheryBus below; device endpoints remain explicit so
    // each one can be replaced or independently differential-tested.
    system_bus.cbus_a_ready = periphery_before.upstream_a_ready;
    system_bus.cbus_d = periphery_before.upstream_d;
    const auto& mmio_fragmenter_before =
        impl_->mmio_axi_fragmenter.outputs();
    system_bus.mmio_axi_aw_ready = mmio_fragmenter_before.in_aw_ready;
    system_bus.mmio_axi_w_ready = mmio_fragmenter_before.in_w_ready;
    system_bus.mmio_axi_b = to_mbus_b(mmio_fragmenter_before.in_b);
    system_bus.mmio_axi_ar_ready = mmio_fragmenter_before.in_ar_ready;
    system_bus.mmio_axi_r = to_mbus_r(mmio_fragmenter_before.in_r);
    if (needs_evaluation(impl_->system_bus_inputs, system_bus))
      { const std::uint64_t t0 = cold_now(); impl_->system_bus.evaluate(system_bus); cold_add(kColdSbus, 0, t0); }
    const auto& system_bus_output = impl_->system_bus.outputs();

    protocol::RomInputs bootrom;
    bootrom.reset = external.reset;
    bootrom.a = periphery_before.bootrom.a;
    bootrom.d_ready = periphery_before.bootrom.d_ready;
    if (needs_evaluation(impl_->bootrom_inputs, bootrom))
      { const std::uint64_t t0 = cold_now(); impl_->bootrom.evaluate(bootrom); cold_add(kColdBootrom, 0, t0); }
    const auto& bootrom_output = impl_->bootrom.outputs();

    components::SmallPlicInputs plic;
    plic.reset = external.reset;
    plic.a = periphery_before.plic.a;
    plic.d_ready = periphery_before.plic.d_ready;
    const std::uint64_t plic_t0 = cold_now();
    const auto& plic_output = impl_->plic.evaluate(plic);
    cold_add(kColdPlic, 0, plic_t0);

    protocol::PeripheryBusInputs periphery;
    periphery.reset = external.reset;
    periphery.upstream_a = system_bus_output.cbus_a;
    {
      static const long long lo = [] {
        const char* w = std::getenv("CHISA_BOOT_SEAM");
        return w ? atoll(w) : -1;
      }();
      [[maybe_unused]] static const long long hi = [] {
        const char* w = std::getenv("CHISA_BOOT_SEAM");
        const char* dash = w ? strchr(w, '-') : nullptr;
        return dash ? atoll(dash + 1) : -1;
      }();
      static long long beat = 0;
      ++beat;  // evaluation count, not cycles; still localizes the window
      if (lo >= 0 && system_bus_output.cbus_a.valid && beat <= 4000) {
        std::fprintf(stderr, "[CSEAM e%lld] cbus_a v=1 src=%u addr=%x rdy=%d\n",
                     beat,
                     static_cast<unsigned>(system_bus_output.cbus_a.source),
                     static_cast<unsigned>(system_bus_output.cbus_a.address),
                     static_cast<int>(periphery_before.upstream_a_ready));
      }
    }
    periphery.upstream_d_ready = system_bus_output.cbus_d_ready;
    periphery.bootrom = bootrom_output;

    // Device endpoints participate in the same fixed point as PeripheryBus.
    // PLIC is a small functional model whose one-entry RegisterRouter queue
    // preserves the exact request/response latency without extracting the
    // otherwise cold interrupt controller RTL.
    periphery.debug.a_ready = debug_before.tl_a_ready;
    periphery.debug.d.valid = debug_before.tl_d_valid;
    periphery.debug.d.opcode = debug_before.tl_d_opcode;
    periphery.debug.d.param = debug_before.tl_d_param;
    periphery.debug.d.size = debug_before.tl_d_size;
    periphery.debug.d.source = debug_before.tl_d_source;
    periphery.debug.d.sink = debug_before.tl_d_sink;
    periphery.debug.d.denied = debug_before.tl_d_denied;
    periphery.debug.d.data = debug_before.tl_d_data;
    periphery.debug.d.corrupt = debug_before.tl_d_corrupt;
    periphery.clint.a_ready = true;
    periphery.plic = plic_output;
    if (needs_evaluation(impl_->periphery_bus_inputs, periphery))
      { const std::uint64_t t0 = cold_now(); (void)impl_->periphery_bus.evaluate(periphery); cold_add(kColdCbus, 0, t0); }

    const auto& mmio_buffer_before = impl_->mmio_axi_buffer.outputs();
    protocol::AxiStageInputs mmio_fragmenter;
    mmio_fragmenter.reset = external.reset;
    mmio_fragmenter.in_aw = to_axi_address(system_bus_output.mmio_axi_aw);
    mmio_fragmenter.in_w = to_axi_write(system_bus_output.mmio_axi_w);
    mmio_fragmenter.in_b_ready = system_bus_output.mmio_axi_b_ready;
    mmio_fragmenter.in_ar = to_axi_address(system_bus_output.mmio_axi_ar);
    mmio_fragmenter.in_r_ready = system_bus_output.mmio_axi_r_ready;
    mmio_fragmenter.out_aw_ready = mmio_buffer_before.in_aw_ready;
    mmio_fragmenter.out_w_ready = mmio_buffer_before.in_w_ready;
    mmio_fragmenter.out_b = mmio_buffer_before.in_b;
    mmio_fragmenter.out_ar_ready = mmio_buffer_before.in_ar_ready;
    mmio_fragmenter.out_r = mmio_buffer_before.in_r;
    if (needs_evaluation(impl_->mmio_axi_fragmenter_inputs, mmio_fragmenter))
      { const std::uint64_t t0 = cold_now(); impl_->mmio_axi_fragmenter.evaluate(mmio_fragmenter); cold_add(kColdMmioFrag, 0, t0); }
    const auto& mmio_fragmenter_output = impl_->mmio_axi_fragmenter.outputs();

    protocol::AxiStageInputs mmio_buffer;
    mmio_buffer.reset = external.reset;
    mmio_buffer.in_aw = mmio_fragmenter_output.out_aw;
    mmio_buffer.in_w = mmio_fragmenter_output.out_w;
    mmio_buffer.in_b_ready = mmio_fragmenter_output.out_b_ready;
    mmio_buffer.in_ar = mmio_fragmenter_output.out_ar;
    mmio_buffer.in_r_ready = mmio_fragmenter_output.out_r_ready;
    mmio_buffer.out_aw_ready = impl_->mmio_axi_ram_outputs.aw_ready;
    mmio_buffer.out_w_ready = impl_->mmio_axi_ram_outputs.w_ready;
    mmio_buffer.out_b = impl_->mmio_axi_ram_outputs.b;
    mmio_buffer.out_ar_ready = impl_->mmio_axi_ram_outputs.ar_ready;
    mmio_buffer.out_r = impl_->mmio_axi_ram_outputs.r;
    if (needs_evaluation(impl_->mmio_axi_buffer_inputs, mmio_buffer))
      { const std::uint64_t t0 = cold_now(); impl_->mmio_axi_buffer.evaluate(mmio_buffer); cold_add(kColdMmioBuf, 0, t0); }
    const auto& mmio_buffer_output = impl_->mmio_axi_buffer.outputs();

    protocol::SparseAxiRamInputs mmio_ram;
    mmio_ram.reset = external.reset;
    mmio_ram.aw = mmio_buffer_output.out_aw;
    mmio_ram.w = mmio_buffer_output.out_w;
    mmio_ram.b_ready = mmio_buffer_output.out_b_ready;
    mmio_ram.ar = mmio_buffer_output.out_ar;
    mmio_ram.r_ready = mmio_buffer_output.out_r_ready;
    if (needs_evaluation(impl_->mmio_axi_ram_inputs, mmio_ram))
      impl_->mmio_axi_ram_outputs = impl_->mmio_axi_ram.outputs(mmio_ram);

    const auto& memory_before = impl_->memory_bus.outputs();
    protocol::CoherenceManagerInputs coherence;
    coherence.reset = external.reset;
    coherence.tile_a = system_bus_output.l2_a;
    coherence.tile_b_ready = system_bus_output.l2_b_ready;
    coherence.tile_c = system_bus_output.l2_c;
    coherence.tile_d_ready = system_bus_output.l2_d_ready;
    coherence.tile_e = system_bus_output.l2_e;
    coherence.mbus_a_ready = memory_before.tl_a_ready;
    coherence.mbus_d = memory_before.tl_d;
    if (needs_evaluation(impl_->coherence_manager_inputs, coherence))
      { const std::uint64_t t0 = cold_now(); impl_->coherence_manager.evaluate(coherence); cold_add(kColdCoherence, 0, t0); }
    const auto& coherence_output = impl_->coherence_manager.outputs();

    const auto& fragmenter_before = impl_->axi_fragmenter.outputs();
    protocol::MbusCouplerInputs memory_bus;
    memory_bus.reset = external.reset;
    memory_bus.tl_a = coherence_output.mbus_a;
    memory_bus.tl_d_ready = coherence_output.mbus_d_ready;
    memory_bus.axi_aw_ready = fragmenter_before.in_aw_ready;
    memory_bus.axi_w_ready = fragmenter_before.in_w_ready;
    memory_bus.axi_b = to_mbus_b(fragmenter_before.in_b);
    memory_bus.axi_ar_ready = fragmenter_before.in_ar_ready;
    memory_bus.axi_r = to_mbus_r(fragmenter_before.in_r);
    if (needs_evaluation(impl_->memory_bus_inputs, memory_bus))
      { const std::uint64_t t0 = cold_now(); impl_->memory_bus.evaluate(memory_bus); cold_add(kColdMbus, 0, t0); }
    const auto& memory_output = impl_->memory_bus.outputs();

    const auto& buffer_before = impl_->axi_buffer.outputs();
    protocol::AxiStageInputs fragmenter;
    fragmenter.reset = external.reset;
    fragmenter.in_aw = to_axi_address(memory_output.axi_aw);
    fragmenter.in_w = to_axi_write(memory_output.axi_w);
    fragmenter.in_b_ready = memory_output.axi_b_ready;
    fragmenter.in_ar = to_axi_address(memory_output.axi_ar);
    fragmenter.in_r_ready = memory_output.axi_r_ready;
    fragmenter.out_aw_ready = buffer_before.in_aw_ready;
    fragmenter.out_w_ready = buffer_before.in_w_ready;
    fragmenter.out_b = buffer_before.in_b;
    fragmenter.out_ar_ready = buffer_before.in_ar_ready;
    fragmenter.out_r = buffer_before.in_r;
    if (needs_evaluation(impl_->axi_fragmenter_inputs, fragmenter))
      { const std::uint64_t t0 = cold_now(); impl_->axi_fragmenter.evaluate(fragmenter); cold_add(kColdAxiFrag, 0, t0); }
    const auto& fragmenter_output = impl_->axi_fragmenter.outputs();

    protocol::AxiStageInputs buffer;
    buffer.reset = external.reset;
    buffer.in_aw = fragmenter_output.out_aw;
    buffer.in_w = fragmenter_output.out_w;
    buffer.in_b_ready = fragmenter_output.out_b_ready;
    buffer.in_ar = fragmenter_output.out_ar;
    buffer.in_r_ready = fragmenter_output.out_r_ready;
    buffer.out_aw_ready = impl_->axi_ram_outputs.aw_ready;
    buffer.out_w_ready = impl_->axi_ram_outputs.w_ready;
    buffer.out_b = impl_->axi_ram_outputs.b;
    buffer.out_ar_ready = impl_->axi_ram_outputs.ar_ready;
    buffer.out_r = impl_->axi_ram_outputs.r;
    if (needs_evaluation(impl_->axi_buffer_inputs, buffer))
      { const std::uint64_t t0 = cold_now(); impl_->axi_buffer.evaluate(buffer); cold_add(kColdAxiBuf, 0, t0); }
    const auto& buffer_output = impl_->axi_buffer.outputs();

    protocol::SparseAxiRamInputs ram;
    ram.reset = external.reset;
    ram.aw = buffer_output.out_aw;
    ram.w = buffer_output.out_w;
    ram.b_ready = buffer_output.out_b_ready;
    ram.ar = buffer_output.out_ar;
    ram.r_ready = buffer_output.out_r_ready;
    if (needs_evaluation(impl_->axi_ram_inputs, ram))
      impl_->axi_ram_outputs = impl_->axi_ram.outputs(ram);

    if (!changed) {
      impl_->coherent_memory_converged = true;
      break;
    }
  }

  const auto& output = impl_->system_bus.outputs();
  impl_->coherent_memory_outputs.tile_a_ready = output.tile_a_ready;
  impl_->coherent_memory_outputs.tile_b = output.tile_b;
  impl_->coherent_memory_outputs.tile_c_ready = output.tile_c_ready;
  impl_->coherent_memory_outputs.tile_d = output.tile_d;
  impl_->coherent_memory_outputs.tile_e_ready = output.tile_e_ready;
  // Register snapshots are refreshed again after the edge in commit(), but
  // wire oracles such as TLToAXI4._GEN_257 also depend on the newly presented
  // TileLink source.  A post-edge lookahead evaluate must therefore refresh
  // the snapshot without clocking the generated modules a second time.
  impl_->refresh_coherent_memory_oracles();
  return impl_->coherent_memory_outputs;
}

protocol::AxiRamAccess NativeFabric::dram_access(
    const SparseBackingMemory& memory) const {
  return impl_->axi_ram.access_trace(impl_->axi_ram_inputs,
      [&memory](std::uint32_t address) { return memory.read64(address); });
}

void NativeFabric::commit_coherent_memory(SparseBackingMemory& memory) {
  if (!impl_->coherent_memory_pending) return;
#if !defined(CHISA_MODEL_ARCHITECTURAL) || !CHISA_MODEL_ARCHITECTURAL
  auto& system_bus_transaction =
      impl_->last_system_bus_boundary_transaction;
  system_bus_transaction = SystemBusBoundaryTransaction{};
  system_bus_transaction.a_valid = impl_->system_bus_inputs.tile_a.valid;
  system_bus_transaction.a_ready = impl_->system_bus.outputs().tile_a_ready;
  system_bus_transaction.a_fire = system_bus_transaction.a_valid &&
                                  system_bus_transaction.a_ready;
  system_bus_transaction.a_opcode = impl_->system_bus_inputs.tile_a.opcode;
  system_bus_transaction.a_size = impl_->system_bus_inputs.tile_a.size;
  system_bus_transaction.a_source = impl_->system_bus_inputs.tile_a.source;
  system_bus_transaction.a_address = impl_->system_bus_inputs.tile_a.address;
  system_bus_transaction.readys_mask_before = impl_->system_bus_oracles[kSbusReadysMaskSlot];
  system_bus_transaction.state_1_before = impl_->system_bus_oracles[kSbusState1Slot];
  auto& transaction = impl_->last_coherence_boundary_transaction;
  transaction = CoherenceBoundaryTransaction{};
  transaction.c_valid = impl_->coherence_manager_inputs.tile_c.valid;
  transaction.c_ready = impl_->coherence_manager.outputs().tile_c_ready;
  transaction.c_fire = transaction.c_valid && transaction.c_ready;
  transaction.c_opcode = impl_->coherence_manager_inputs.tile_c.opcode;
  transaction.c_param = impl_->coherence_manager_inputs.tile_c.param;
  transaction.c_size = impl_->coherence_manager_inputs.tile_c.size;
  transaction.c_source = impl_->coherence_manager_inputs.tile_c.source;
  transaction.c_address = impl_->coherence_manager_inputs.tile_c.address;
  transaction.c_data = impl_->coherence_manager_inputs.tile_c.data;
  transaction.c_data_hi = impl_->coherence_manager_inputs.tile_c.data_hi;
  transaction.c_corrupt = impl_->coherence_manager_inputs.tile_c.corrupt;
  const bool is_probe_ack = transaction.c_opcode == 4 ||
                            transaction.c_opcode == 5;
  const bool reports_shared = transaction.c_param == 0 ||
                              transaction.c_param == 4;
  for (std::size_t index = 0; index < transaction.line_match.size(); ++index) {
    const auto& tracker = impl_->coherent_memory_oracles.trackers[index];
    transaction.shared_before[index] =
        static_cast<std::uint8_t>(tracker.shared & 1u);
    transaction.line_match[index] =
        (tracker.address >> 6) == (transaction.c_address >> 6);
    transaction.probe_ack[index] =
        transaction.c_fire && is_probe_ack && reports_shared &&
        transaction.line_match[index];
  }
#endif
  // The oracle snapshots below are refreshed only for modules that actually
  // evaluated this cycle (a skipped module's state, and so every oracle
  // captured from it, is unchanged; the publish step keys on the snapshot
  // versions and stays quiet as well).  Evaluated = its skip count did not
  // advance in commit_evaluated().
  const auto commit_evaluated_of = [](auto& module, ColdModule tag) {
    const std::uint64_t skipped = module.skipped_count();
    const std::uint64_t t0 = cold_now();
    module.commit_evaluated();
    cold_add(tag, 1, t0);
    return module.skipped_count() == skipped;
  };
  const bool sbus_evaluated = commit_evaluated_of(impl_->system_bus, kColdSbus);
  const bool cbus_evaluated = commit_evaluated_of(impl_->periphery_bus, kColdCbus);
  // The PLIC has no skip count; its one published lane is its queue's
  // maybe_full, so a transition of that flag is what counts.
  const bool plic_before = impl_->plic.active();
  impl_->plic.commit_evaluated();
  const bool plic_moved = plic_before != impl_->plic.active();
  { const std::uint64_t t0 = cold_now();
  if (sbus_evaluated) impl_->refresh_system_bus_oracles();
  if (cbus_evaluated) impl_->refresh_periphery_bus_oracles();
  cold_add(kColdOracles, 1, t0); }
#if !defined(CHISA_MODEL_ARCHITECTURAL) || !CHISA_MODEL_ARCHITECTURAL
  system_bus_transaction.readys_mask_after = impl_->system_bus_oracles[kSbusReadysMaskSlot];
  system_bus_transaction.state_1_after = impl_->system_bus_oracles[kSbusState1Slot];
#endif
  bool memory_side_evaluated = commit_evaluated_of(impl_->coherence_manager, kColdCoherence);
  if (commit_evaluated_of(impl_->memory_bus, kColdMbus)) memory_side_evaluated = true;
  if (commit_evaluated_of(impl_->axi_fragmenter, kColdAxiFrag)) memory_side_evaluated = true;
  if (commit_evaluated_of(impl_->axi_buffer, kColdAxiBuf)) memory_side_evaluated = true;
  if (commit_evaluated_of(impl_->mmio_axi_fragmenter, kColdMmioFrag)) memory_side_evaluated = true;
  if (commit_evaluated_of(impl_->mmio_axi_buffer, kColdMmioBuf)) memory_side_evaluated = true;
  // The RAM models commit unconditionally: they moved if they carried a
  // transaction before or after this edge.
  const bool ram_before = impl_->axi_ram.active() || impl_->mmio_axi_ram.active();
  const std::uint64_t ram_t0 = cold_now();
  impl_->axi_ram.commit(
      impl_->axi_ram_inputs,
      [&memory](std::uint32_t address) { return memory.read64(address); },
      [&memory](std::uint32_t address, std::uint64_t data,
                std::uint8_t strobe) {
        memory.write64_masked(address, data, strobe);
      });
  impl_->axi_ram_outputs = impl_->axi_ram.outputs(impl_->axi_ram_inputs);
  impl_->mmio_axi_ram.commit(
      impl_->mmio_axi_ram_inputs,
      [&memory](std::uint32_t address) { return memory.read64(address); },
      [&memory](std::uint32_t address, std::uint64_t data,
                std::uint8_t strobe) {
        memory.write64_masked(address, data, strobe);
      });
  impl_->mmio_axi_ram_outputs =
      impl_->mmio_axi_ram.outputs(impl_->mmio_axi_ram_inputs);
  cold_add(kColdAxiRam, 1, ram_t0);
  if (memory_side_evaluated || plic_moved || ram_before ||
      impl_->axi_ram.active() || impl_->mmio_axi_ram.active()) {
    const std::uint64_t t0 = cold_now();
    impl_->refresh_mbus_memory_oracles();
    impl_->refresh_coherent_memory_oracles();
    cold_add(kColdOracles, 1, t0);
  }
#if !defined(CHISA_MODEL_ARCHITECTURAL) || !CHISA_MODEL_ARCHITECTURAL
  for (std::size_t index = 0; index < transaction.shared_after.size(); ++index)
    transaction.shared_after[index] = static_cast<std::uint8_t>(
        impl_->coherent_memory_oracles.trackers[index].shared & 1u);
#endif
  impl_->coherent_memory_pending = false;
}

bool NativeFabric::coherent_memory_converged() const {
  return impl_->coherent_memory_converged;
}

bool NativeFabric::coherent_memory_active() const {
  // Must cover every stateful module in the evaluate_coherent_memory fixed
  // point, since the pre-edge idle skip trusts it.  bootrom (tl_rom) is
  // stateless (active()==false) so its output tracks its input, guarded by the
  // skip's input-equality check.
  return impl_->system_bus.active() || impl_->periphery_bus_active() ||
         impl_->plic.active() ||
         impl_->coherence_manager.active() ||
         impl_->memory_bus.active() ||
         impl_->axi_fragmenter.active() || impl_->axi_buffer.active() ||
         impl_->axi_ram.active() || impl_->mmio_axi_fragmenter.active() ||
         impl_->mmio_axi_buffer.active() || impl_->mmio_axi_ram.active();
}

std::uint64_t NativeFabric::coherent_memory_skipped_count() const {
  return impl_->coherent_memory_skipped;
}

std::uint64_t NativeFabric::coherent_memory_pre_edge_total_count() const {
  return impl_->coherent_memory_pre_edge_total;
}
std::uint64_t NativeFabric::coherent_memory_pre_edge_equal_lookahead_count() const {
  return impl_->coherent_memory_pre_edge_equal_lookahead;
}
std::uint64_t NativeFabric::coherent_memory_pre_edge_recomputed_count() const {
  return impl_->coherent_memory_pre_edge_recomputed;
}
std::uint64_t NativeFabric::coherent_memory_lookahead_skipped_count() const {
  return impl_->coherent_memory_lookahead_skipped;
}

bool NativeFabric::system_bus_active() const {
  return impl_->system_bus.active();
}

std::uint64_t NativeFabric::system_bus_eval_count() const {
  return impl_->system_bus.eval_count();
}

std::uint64_t NativeFabric::system_bus_skipped_count() const {
  return impl_->system_bus.skipped_count();
}

std::uint64_t NativeFabric::coherence_manager_eval_count() const {
  return impl_->coherence_manager.eval_count();
}

std::uint64_t NativeFabric::coherence_manager_skipped_count() const {
  return impl_->coherence_manager.skipped_count();
}

std::uint64_t NativeFabric::memory_bus_eval_count() const {
  return impl_->memory_bus.eval_count();
}

std::uint64_t NativeFabric::memory_bus_skipped_count() const {
  return impl_->memory_bus.skipped_count();
}

std::uint64_t NativeFabric::axi_fragmenter_eval_count() const {
  return impl_->axi_fragmenter.eval_count();
}

std::uint64_t NativeFabric::axi_fragmenter_skipped_count() const {
  return impl_->axi_fragmenter.skipped_count();
}

std::uint64_t NativeFabric::axi_buffer_eval_count() const {
  return impl_->axi_buffer.eval_count();
}

std::uint64_t NativeFabric::axi_buffer_skipped_count() const {
  return impl_->axi_buffer.skipped_count();
}

const MbusMemoryOracleState& NativeFabric::mbus_memory_oracles() const {
  return impl_->mbus_memory_oracles;
}

const std::uint64_t& NativeFabric::system_bus_oracle_version() const {
  return impl_->system_bus_oracle_version;
}
const std::uint64_t& NativeFabric::periphery_bus_oracle_version() const {
  return impl_->periphery_bus_oracle_version;
}
const std::uint64_t& NativeFabric::mbus_memory_oracle_version() const {
  return impl_->mbus_memory_oracle_version;
}
const std::uint64_t& NativeFabric::mmio_memory_oracle_version() const {
  return impl_->mmio_memory_oracle_version;
}
const std::uint64_t& NativeFabric::coherent_memory_oracle_version() const {
  return impl_->coherent_memory_oracle_version;
}
const MbusMemoryOracleState& NativeFabric::mmio_memory_oracles() const {
  return impl_->mmio_memory_oracles;
}

const CoherentMemoryOracleState&
NativeFabric::coherent_memory_oracles() const {
  return impl_->coherent_memory_oracles;
}

const SystemBusOracleState& NativeFabric::system_bus_oracles() const {
  return impl_->system_bus_oracles;
}

const PeripheryBusOracleState&
NativeFabric::periphery_bus_oracles() const {
  return impl_->periphery_bus_oracles;
}

std::uint64_t NativeFabric::plic_out_back_maybe_full() const {
  return impl_->plic.maybe_full() ? 1u : 0u;
}

std::uint64_t NativeFabric::plic_out_back_bank_0() const {
  return impl_->plic.out_back_bank_0();
}

std::uint64_t NativeFabric::plic_out_back_bank_1() const {
  return impl_->plic.out_back_bank_1();
}

std::uint64_t NativeFabric::plic_out_back_data() const {
  return impl_->plic.out_back_data();
}

const SystemBusBoundaryTransaction&
NativeFabric::last_system_bus_boundary_transaction() const {
  return impl_->last_system_bus_boundary_transaction;
}

const CoherenceBoundaryTransaction&
NativeFabric::last_coherence_boundary_transaction() const {
  return impl_->last_coherence_boundary_transaction;
}

void cold_module_sizes_report() { NativeFabric::report_sizes(); }
#ifdef CHISA_PHASE_TIMERS
void NativeFabric::report_sizes() {
  std::fprintf(stderr, "SYSBENCH_COLD_SIZES bytes: sbus=%zu cbus=%zu coherence=%zu mbus=%zu axi_frag=%zu axi_buf=%zu"
                       " mmio_frag=%zu mmio_buf=%zu ptw=%zu fpu=%zu fdivsqrt=%zu impl=%zu\n",
               sizeof(decltype(NativeFabric::Impl::system_bus)), sizeof(decltype(NativeFabric::Impl::periphery_bus)),
               sizeof(decltype(NativeFabric::Impl::coherence_manager)),
               sizeof(decltype(NativeFabric::Impl::memory_bus)), sizeof(decltype(NativeFabric::Impl::axi_fragmenter)),
               sizeof(decltype(NativeFabric::Impl::axi_buffer)), sizeof(decltype(NativeFabric::Impl::mmio_axi_fragmenter)),
               sizeof(decltype(NativeFabric::Impl::mmio_axi_buffer)), sizeof(decltype(NativeFabric::Impl::ptw)),
               sizeof(decltype(NativeFabric::Impl::fpu)), sizeof(decltype(NativeFabric::Impl::fdivsqrt)), sizeof(NativeFabric::Impl));
}
#else
void NativeFabric::report_sizes() {}
#endif
}  // namespace chisa::boom_system
