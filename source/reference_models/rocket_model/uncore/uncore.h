// rocket_model uncore model: everything outside the Rocket tile in the DefaultConfig
// system (tile crossbar and boundary buffers, system/control/front/memory
// buses, broadcast coherence hub, TileLink-to-AXI4 bridges, the simulated
// AXI memories, boot ROM, CLINT, PLIC, debug module and its DMI transport,
// interrupt plumbing).  Written from the rocket-chip Chisel sources and the
// TileLink/AXI4 specifications; the elaboration parameters (id ranges,
// queue depths, address map) are those of freechips.rocketchip.system.DefaultConfig.
//
// Each module keeps exactly the registers the hardware has (plus queue
// contents), so the oracle streams of the contract can be produced without a
// separate export pass. The top level checks for idle modules and skips their
// transition work when no channel or state machine can advance.
#pragma once

#include <cstdint>

#include "uncore/tl.h"
#include "uncore/front_bus.h"

namespace chisa::rocket_model { struct Image; }

namespace chisa::rocket_model::uncore {

// ---- boundary bundles ---------------------------------------------------------
struct UncoreIn {
  bool reset = false;
  // tile master crossbar inputs: index 0 = data cache, index 1 = instruction cache
  bool dc_a_valid = false; TlA dc_a;
  bool dc_c_valid = false; TlC dc_c;
  bool dc_e_valid = false; TlE dc_e;
  bool dc_b_ready = false, dc_d_ready = false;
  bool ic_a_valid = false; TlA ic_a;
  bool ic_d_ready = false;
  // debug module interface (from the DMI host)
  bool dmi_req_valid = false; uint8_t dmi_req_addr = 0; uint32_t dmi_req_data = 0; uint8_t dmi_req_op = 0;
  bool dmi_resp_ready = false;
};

struct UncoreOut {
  bool dc_a_ready = false, dc_c_ready = false, dc_e_ready = false;
  bool dc_b_valid = false; TlB dc_b;
  bool dc_d_valid = false; TlD dc_d;
  bool ic_a_ready = false;
  bool ic_d_valid = false; TlD ic_d;
  bool dmi_req_ready = false;
  bool dmi_resp_valid = false; uint32_t dmi_resp_data = 0; uint8_t dmi_resp_resp = 0;
  bool int_debug = false, int_msip = false, int_mtip = false, int_meip = false, int_seip = false;
  bool system_reset = false;
};

// ---- TileLink modules ---------------------------------------------------------

// TLFragmenter(minSize = 8, maxSize = 64) in front of a register-mapped device.
struct Fragmenter {
  uint8_t acknum = 0;      // 3 bits
  uint8_t dOrig = 0;       // response size of the original request
  bool dToggle = false;
  uint8_t gennum = 0;      // 3 bits
  bool aToggle_hold = false;  // RegEnable(dToggle, aFirst)
  // Repeater
  bool rep_full = false; TlA rep_saved;
};

// Register-mapped device transport state shared by the debug module, CLINT and PLIC.
struct RegMapperReq { bool read = false; uint32_t index = 0; uint64_t data = 0; uint8_t mask = 0; uint16_t source = 0; uint8_t size = 0; };

// TLError (cbus built-in error device, buffered) and its TLBuffer.
struct ErrorDevice {
  Queue<TlA, 2> buf_a; Queue<TlD, 2> buf_d;   // wrapped_error_device.buffer
  Queue<TlA, 1> a;                            // Queue(in.a, 1)
  BeatCounter a_last;                         // edge.last(a)
  bool idle = true;
};

// TLAtomicAutomata (cbus), one CAM entry.
struct Atomics {
  uint8_t cam_state = 0;        // FREE 0, ACK 1, AMO 2, GET 3
  TlA cam_a;
  uint64_t cam_d_data = 0; bool cam_d_denied = false, cam_d_corrupt = false;
  LowArbiter<2> arb;            // out.a: [source_c, source_i]
  BeatCounter d_first;          // edgeOut.first(out.d)
};

// TLBroadcast tracker.
struct Tracker {
  bool got_e = true, sent_d = true, shared = false;
  uint8_t opcode = 0, param = 0, size = 0, source = 0;
  uint32_t address;             // RegInit(id << 6)
  uint8_t count = 0;            // 1 bit (one cache)
  uint8_t cacheOH = 0;          // 1 bit
  struct Beat { uint8_t mask = 0; uint64_t data = 0; };
  Queue<Beat, 8> o_data;
};

// TLToAXI4 (combinational, depth-1 flow queues).
struct ToAxi4 {
  struct Arw { AxiA a; bool wen = false; };
  Queue<Arw, 1, true> q_arw;
  Queue<AxiW, 1, true> q_w;
  bool doneAW = false;
  bool r_holds_d = false;
  uint8_t b_delay = 0;          // 3 bits
  bool r_first = true;
  bool r_denied_hold = false;   // holdUnless r_first
  BeatCounter a_cnt;            // edgeIn.firstlast(in.a)
  // per AXI id: count (1 bit; the mmio port has two ids with 4-bit counts and a write flag)
  uint16_t count[128] = {};
  bool write[128] = {};
};

// AXI4UserYanker queue entry: the echo fields of the request.
struct YankEcho { uint8_t size = 0, source = 0, extra = 0; };

// AXI4Fragmenter and AXI4Buffer in front of an AXI4RAM (SimAXIMem).
struct AxiMem {
  // AXI4Fragmenter
  Queue<AxiA, 1, true> q_ar, q_aw;   // deq, deq_1
  Queue<AxiW, 1, true> q_w;          // in_w_deq
  bool ar_busy = false; uint32_t ar_addr = 0; uint8_t ar_len = 0;   // busy/r_addr/r_len
  bool aw_busy = false; uint32_t aw_addr = 0; uint8_t aw_len = 0;   // busy_1/r_addr_1/r_len_1
  bool wbeats_latched = false;
  uint16_t w_counter = 0;            // 9 bits
  uint8_t error[16] = {};            // per id resp accumulation (2 bits)
  // AXI4Buffer (depth 2 each)
  Queue<AxiA, 2> b_aw, b_ar; Queue<AxiW, 2> b_w; Queue<AxiB, 2> b_b; Queue<AxiR, 2> b_r;
  // AXI4RAM
  bool w_full = false; uint8_t w_id = 0; bool w_sel1 = false; bool w_echo_last = false; uint8_t w_echo_size = 0, w_echo_source = 0, w_echo_extra = 0;
  bool r_full = false; uint8_t r_id = 0; bool r_sel1 = false; bool r_echo_last = false; uint8_t r_echo_size = 0, r_echo_source = 0, r_echo_extra = 0;
  uint64_t rdata = 0;                // readAndHold output
  bool ren_prev = false;
  uint32_t r_addr_prev = 0;          // address of the last enabled read
  // comb streams: the SRAM port addresses presented this cycle
  uint32_t port_raddr = 0, port_waddr = 0;
};

// ---- debug module ----------------------------------------------------------
struct AsyncSource {           // AsyncQueueSource, depth 1, sync 3, safe
  bool widx_bin = false;       // 1-bit binary counter (gray of 1 bit = itself)
  bool ready_reg = false, widx_reg = false;
  SyncChain<3> ridx_sync;      // ridx_gray synchronizer
  SyncChain<3> source_valid_0, source_valid_1, sink_extend, sink_valid;
  uint64_t mem = 0; uint8_t mem_hi = 0;  // one entry (bits packed by the user)
};
struct AsyncSink {             // AsyncQueueSink, depth 1, sync 3, safe
  bool ridx_bin = false;
  bool valid_reg = false, ridx_reg = false;
  SyncChain<3> widx_sync;
  SyncChain<3> sink_valid_0, sink_valid_1, source_extend, source_valid;
  uint64_t deq_reg = 0; uint8_t deq_reg_hi = 0;  // ClockCrossingReg (cdc_reg)
};

struct DebugModule {
  // ---- DMI clock domain (dmOuter side) ----
  RrArbiter<2> dmiXbar_d;      // dmiXbar in.d arbiter over [bypass, dmOuter]
  // dmOuter registers
  bool dmactive = false, ndmreset = false, haltreq = false;
  bool debugInt = false;       // debugIntRegs(0)
  bool innerCtrlValidReg = false, innerCtrlResumeReqReg = false, innerCtrlAckHaveResetReg = false;
  bool hrmaskReg = false;
  // TLBusBypass bar
  bool bar_in_reset = true; bool bar_bypass_reg = false; uint8_t bar_flight = 0; BeatCounter bar_a_cnt, bar_d_cnt;
  // bypass error device (unbuffered, acquire-capable)
  bool err_idle = true; LowArbiter<2> err_d;
  SyncChain<3> dmactiveAckSync;  // dmactiveAck synchronised into the DMI domain
  AsyncSource a_source;        // asource.bundleOut_0_a_source (A channel to dmInner)
  AsyncSink d_sink;            // asource.bundleIn_0_d_sink (D channel back)
  AsyncSource ic_source;       // io_innerCtrl_source
  // ---- debug clock domain (gated) ----
  AsyncSink a_sink;            // dmiXing.bundleOut_0_a_sink
  AsyncSource d_source;        // dmiXing.bundleIn_0_d_source
  AsyncSink ic_sink;           // dmactive_synced_dmInner_io_innerCtrl_sink
  SyncChain<3> dmactive_synced;
  SyncChain<3> hartIsInResetSync;
  // dmInner registers
  bool haltedBit = false, resumeReq = false, haveResetBit = false;
  bool hrmask = false, hrDebugInt = false;
  uint8_t cmderr = 0; bool abstract_busy = false;
  uint32_t abstractauto = 0;
  uint32_t command = 0;
  uint8_t data_mem[8] = {};
  uint8_t progbuf[64] = {};
  bool goReg = false;
  uint32_t abstract_gen[2] = {};
  uint8_t ctrlState = 0;       // Waiting 0, CheckGenerate 1, Exec 2
  // ---- harness-level debug clock/reset ----
  SyncChain<3> debug_reset_sync;   // AsyncResetSynchronizerShiftReg(true, 3) under dmi_reset
  SyncChain<3> dmactiveAck_sync;   // ResetSynchronizerShiftReg(dmactive, 3) under debug_reset
  bool clock_en = true;
};

// ---- the uncore ---------------------------------------------------------------
class Uncore {
 public:
  Uncore();
  ~Uncore();
  Uncore(const Uncore&) = delete;
  Uncore& operator=(const Uncore&) = delete;
  void attach_memory(uint8_t* dram, uint64_t dram_bytes);   // 0x8000_0000 region
  uint64_t read_memory_word(uint64_t address) const;
  void write_memory_word(uint64_t address, uint64_t value, uint8_t byte_mask = 0xff);
  void evaluate(const UncoreIn& in, UncoreOut& out);
  void commit(const UncoreIn& in);
  void commit();
  void export_image(Image& img) const;
  void export_post_image(Image& img) const;
  bool idle() const { return idle_; }
  // Diagnostic control for the same functional model, without the idle fast path.
  void set_idle_skip(bool enabled) { idle_skip_enabled_ = enabled; }
  void set_evaluation_reuse(bool enabled) { evaluation_reuse_enabled_ = enabled; }
  uint64_t reused_evaluations() const { return reused_evaluations_; }

  // ---- state (public for the co-simulation checks) ----
  // tile master crossbar
  RrArbiter<2> tile_arb;
  // tile_prci_domain.buffer_1
  Queue<TlA, 2> tb_a; Queue<TlB, 2> tb_b; Queue<TlC, 2> tb_c; Queue<TlD, 2> tb_d; Queue<TlE, 2> tb_e;
  // system bus crossbar: A arbiters per output [cbus, l2, mmio], D arbiters per input [fbus, tile]
  RrArbiter<2> sb_a[3];
  RrArbiter<3> sb_d[2];
  // control bus
  Atomics cb_atomics;
  Queue<TlA, 2> cb_a; Queue<TlD, 2> cb_d;    // subsystem_cbus.buffer
  FifoFixer cb_fixer;
  FifoFixer sb_fixer;                       // fbus input; tile has no FIFO clients
  ClosedFrontBus fbus;
  RrArbiter<5> cb_d_arb;                     // out_xbar in.d over [error, plic, clint, debug, bootrom]
  ErrorDevice cb_err;
  Fragmenter fr_plic, fr_clint, fr_debug, fr_rom;
  // PLIC
  uint8_t plic_priority[2] = {}; uint8_t plic_threshold[2] = {}; bool plic_pending[2] = {}; uint8_t plic_enable[2] = {};
  uint8_t plic_maxdev[2] = {}, plic_max_priority[2] = {}; bool plic_gateway_inflight[2] = {};
  Queue<RegMapperReq, 1> plic_back;          // out_back
  // CLINT
  uint64_t clint_time = 0, clint_timecmp = 0; bool clint_ipi = false; uint8_t rtc_div = 0;
  // broadcast hub
  Tracker trk[4];
  bool probe_todo = false; uint32_t probe_line = 0; uint8_t probe_perms = 0;
  uint8_t d_trackerOH_hold = 0;              // REG (holdUnless d_first)
  LowArbiter<2> l2_d_arb;                    // in.d: [releaseack, d_normal]
  LowArbiter<5> l2_a_arb;                    // out.a: [putfull, trk0..3]
  BeatCounter l2_d_cnt;                      // counter: firstlast(d_normal)
  BeatCounter l2_a_cnt;                      // counter_2: first(in.a)
  // memory bus AXI chain
  ToAxi4 mb_axi;
  Queue<YankEcho, 8> mb_rq[16], mb_wq[16];   // UserYanker
  AxiMem mem;
  // mmio port AXI chain
  ToAxi4 mm_axi;
  Queue<YankEcho, 8> mm_rq_big[5], mm_wq_big[5];   // ids 1,2 use depth 8, others depth 1 (kept in the same type)
  bool mm_deint_locked = false; uint8_t mm_deint_id = 0; uint8_t mm_deint_count[5] = {};
  Queue<AxiR, 8> mm_deint_q[5];
  Queue<AxiA, 2> mm_buf_aw, mm_buf_ar; Queue<AxiW, 2> mm_buf_w; Queue<AxiB, 2> mm_buf_b; Queue<AxiR, 2> mm_buf_r;
  AxiMem mmio;
  // debug
  DebugModule dbg;
  SyncChain<3> tile_debug_int_sync;          // tile_prci_domain.intsink chain (no reset)
  bool int_clint_reg[2] = {}; bool int_plic_reg[2] = {};   // AsyncResetRegVec sources
  bool ldut_reset_reg = false;

 private:
  struct Wires;
  friend void commit_datapath(Uncore&, const UncoreIn&);
  void eval_debug(const UncoreIn& in, UncoreOut& out);
  void commit_debug(const UncoreIn& in);
  uint64_t debug_tl_read(uint32_t index) const;
  uint64_t plic_read(uint32_t index, bool read) const;
  void plic_back_effects(const RegMapperReq& r);
  Wires* w_;
  uint8_t* dram_ = nullptr; uint64_t dram_bytes_ = 0;
  uint8_t mmio_mem_[4096] = {};
  bool idle_ = false;
  bool evaluated_ = false;
  bool debug_comb_ = true;
  UncoreIn captured_input_{};
  bool idle_skip_enabled_ = true;
  bool evaluation_reuse_enabled_ = true;
  uint64_t reused_evaluations_ = 0;
  bool can_skip_transport_ = false;
  bool transport_evaluated_ = true;
  UncoreOut transport_output_{};
  bool quiescent_transport() const;
  void evaluate_boundary(const UncoreIn& in, UncoreOut& out);
  uint64_t rom_[512];
};

}  // namespace chisa::rocket_model::uncore
