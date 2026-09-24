// rocket_model uncore model implementation.  See uncore.h for the module inventory.
//
// evaluate() computes one cycle's combinational values in dependency order:
// response (D/B/R) valids are register-derived and come first, their readies
// flow back; then requests (A/C/E, AW/W/AR) flow forward from the tile and
// their readies flow back.  commit() advances the registers with the
// handshakes recorded in Wires.
#include "uncore/uncore.h"

#include <cstring>
#include <cstddef>
#include <initializer_list>

#include "generated/image.h"
#include "uncore/bootrom_contents.h"
#include "uncore/uncore_wires.h"

namespace chisa::rocket_model::uncore {

namespace {

constexpr uint8_t kTileSourceBase = 16;   // the tile's source ids on the system bus
constexpr unsigned kSbusMaxLg = 12;       // 4 KiB max transfer (error device) -> 9-bit beat counters
constexpr unsigned kL2MaxLg = 6;          // 64-byte lines on the l2/mbus edges
enum { kCbus = 0, kL2 = 1, kMmio = 2 };
enum { kDevErr = 0, kDevPlic = 1, kDevClint = 2, kDevDebug = 3, kDevRom = 4 };
enum { kFrPlic = 0, kFrClint = 1, kFrDebug = 2, kFrRom = 3 };
constexpr uint8_t kFree = 0, kAck = 1, kAmo = 2, kGet = 3;
constexpr uint8_t kTransformT = 3, kTransformB = 2, kDrop = 1, kPass = 0;
constexpr uint8_t kAxiOkay = 0, kAxiSlvErr = 2, kAxiDecErr = 3;

inline unsigned sbus_route(uint32_t addr) {
  if (addr & 0x80000000u) return kL2;
  if (((addr >> 29) & 3) == 3) return kMmio;
  return kCbus;
}
inline unsigned cbus_route(uint32_t addr) {
  if (addr < 0x1000) return kDevDebug;
  if (addr >= 0x3000 && addr < 0x4000) return kDevErr;
  if (addr >= 0x10000 && addr < 0x20000) return kDevRom;
  if (addr >= 0x2000000 && addr < 0x2010000) return kDevClint;
  if (addr >= 0xC000000 && addr < 0x10000000) return kDevPlic;
  return kDevErr;
}
inline uint8_t cbus_fifo_domain(uint32_t address) {
  // A FIFO domain is the selected software device, including the error target.
  return static_cast<uint8_t>(cbus_route(address) + 1);
}
inline bool need_t(const TlA& a) {
  switch (a.opcode) {
    case A_PutFullData: case A_PutPartialData: case A_ArithmeticData: case A_LogicalData: return true;
    case A_Get: return false;
    case A_Hint: return a.param == 1;
    default: return a.param != P_NtoB;   // AcquireBlock/AcquirePerm: NtoT, BtoT need T
  }
}
inline TlD access_ack(uint16_t source, uint8_t size, bool data, uint64_t d = 0, bool denied = false, bool corrupt = false) {
  TlD r; r.opcode = data ? D_AccessAckData : D_AccessAck; r.param = 0; r.size = size; r.source = source; r.sink = 0;
  r.denied = denied; r.data = d; r.corrupt = corrupt; return r;
}
inline uint64_t byte_merge(uint64_t old, uint64_t nw, uint8_t mask) {
  uint64_t m = 0;
  for (unsigned i = 0; i < 8; ++i) if ((mask >> i) & 1) m |= UINT64_C(0xFF) << (8 * i);
  return (old & ~m) | (nw & m);
}
inline unsigned lowest_bit(uint32_t x) { return static_cast<unsigned>(__builtin_ctz(x)); }
inline uint32_t lowest_oh(uint32_t x) { return x & (~x + 1); }

// ---- register-mapped device helpers ---------------------------------------------
// A TileLink A beat presented to a RegMapper with concurrency 0: the response is
// combinational; the caller decides the handshake.
struct RegAccess { bool read; uint32_t index; uint8_t mask; uint64_t data; uint16_t source; uint8_t size; };
inline RegAccess reg_access(const TlA& a, unsigned lg_bytes) {
  return RegAccess{a.opcode == A_Get, a.address >> lg_bytes, a.mask, a.data, a.source, a.size};
}

// Fragmenter in front of a combinational register device.  `dev_data` returns the
// read data of the addressed word; `dev_ready` says whether the device can take the beat.
void frag_forward(const Fragmenter& f, FragWires& w) {
  // repeater
  const TlA& a = f.rep_full ? f.rep_saved : w.in;
  const unsigned aOrig = a.size, aFrag = aOrig > 3 ? 3 : aOrig;
  const bool aHasData = a_has_data(a.opcode);
  const unsigned bytes = 1u << (aOrig > 6 ? 6 : aOrig);
  const unsigned fragments = bytes < 8 ? 1 : bytes / 8;
  w.aFirst = f.gennum == 0;
  const unsigned remaining = w.aFirst ? fragments-1 : (f.gennum-1)&7;
  w.new_gennum = static_cast<uint8_t>(remaining);
  const unsigned aFragnum = remaining;
  const bool aToggle = !(w.aFirst ? f.dToggle : f.aToggle_hold);
  w.repeat = !aHasData && aFragnum != 0;
  w.out = a;
  const unsigned fragment_offset = ((fragments-1-remaining)*8) & (bytes-1) & ~7u;
  w.out.address = a.address | fragment_offset;
  w.out.source = static_cast<uint16_t>((a.source << 4) | (aToggle ? 8 : 0) | aFragnum);
  w.out.size = static_cast<uint8_t>(aFrag);
  w.out.data = w.in.data;
  w.out.mask = f.rep_full ? 0xFF : w.in.mask;
  w.out_fire = false;
}
inline bool frag_out_valid(const Fragmenter& f, const FragWires& w) { return w.in_valid || f.rep_full; }
// Response side: the device answered `d` (valid); computes the upward response and the drop.
void frag_response(const Fragmenter& f, FragWires& w) {
  const TlD& d = w.d;
  const unsigned dFragnum = d.source & 7;
  w.dFirst = f.acknum == 0;
  const bool dLast = dFragnum == 0;
  const uint32_t dsizeOH = 1u << d.size, dsizeOH1 = oh1(d.size, 3);
  const bool dHasData = d_has_data(d.opcode);
  w.dFirst_acknum = static_cast<uint8_t>(dFragnum);
  w.ack_decrement = static_cast<uint8_t>(dHasData ? 1 : (dsizeOH >> 3));
  w.dFirst_size = static_cast<uint8_t>(oh1_to_uint((dFragnum << 3) | dsizeOH1));
  const bool drop = !dHasData && !dLast;
  w.up_valid = w.d_valid && !drop;
  w.up = d;
  w.up.source = static_cast<uint8_t>(d.source >> 4);
  w.up.size = w.dFirst ? w.dFirst_size : f.dOrig;
  w.d_fire = false;   // set by the caller: out.d.ready = in.d.ready || drop
  w.device_a_ready = false;
}
inline void frag_commit(Fragmenter& f, const FragWires& w) {
  if (w.rep_enq_fire && w.repeat) { f.rep_full = true; f.rep_saved = w.in; }
  if (w.rep_deq_fire && !w.repeat) f.rep_full = false;
  if (w.out_fire) f.gennum = w.new_gennum;
  if (w.aFirst) f.aToggle_hold = f.dToggle;
  if (w.d_fire) {
    f.acknum = static_cast<uint8_t>(w.dFirst ? w.dFirst_acknum : ((f.acknum - w.ack_decrement) & 7));
    if (w.dFirst) { f.dOrig = w.dFirst_size; f.dToggle = (w.d.source >> 3) & 1; }
  }
}

// ---- AXI4 memory (fragmenter + buffer + RAM) --------------------------------------------
// Forward: AW/W/AR from the yanker (valids/bits given) down to the RAM; computes readies back.
struct AxiIn { bool aw_valid, w_valid, ar_valid; AxiA aw, ar; AxiW w; bool b_ready, r_ready; };
struct AxiOutReady { bool aw_ready, w_ready, ar_ready; bool b_valid, r_valid; AxiB b; AxiR r; };

void axi_mem_eval(const AxiMem& m, const AxiIn& in, AxiMemWires& w, AxiOutReady& o, uint32_t index_mask, uint32_t base, uint32_t size,
                  const uint8_t* mem_bytes) {
  // The SRAM's registered address and readAndHold's retained value are
  // distinct. A write to the held address can change the raw access oracle
  // without changing an AXI response retained while ren_prev is false.
  std::memcpy(&w.raw_read_data, mem_bytes + static_cast<size_t>(m.r_addr_prev) * 8, 8);
  const uint64_t read_data = m.ren_prev ? w.raw_read_data : m.rdata;
  // ---- RAM responses (registers) into the buffer ----
  AxiB b; b.id = m.w_id; b.resp = m.w_sel1 ? kAxiOkay : kAxiDecErr; b.echo_last = m.w_echo_last; b.echo_size = m.w_echo_size; b.echo_source = m.w_echo_source; b.echo_extra = m.w_echo_extra;
  AxiR r; r.id = m.r_id; r.resp = m.r_sel1 ? kAxiOkay : kAxiDecErr; r.data = read_data; r.last = true; r.echo_last = m.r_echo_last; r.echo_size = m.r_echo_size; r.echo_source = m.r_echo_source; r.echo_extra = m.r_echo_extra;
  w.b_buf_valid = m.w_full; w.b_buf = b; w.r_buf_valid = m.r_full; w.r_buf = r;
  const bool ram_b_ready = m.b_b.enq_ready(), ram_r_ready = m.b_r.enq_ready();
  w.ram_b_fire = m.w_full && ram_b_ready; w.ram_r_fire = m.r_full && ram_r_ready;
  // buffer -> fragmenter (B/R) -> yanker
  const bool bq_valid = !m.b_b.empty(); const AxiB& bq = m.b_b.head();
  const bool rq_valid = !m.b_r.empty(); const AxiR& rq = m.b_r.head();
  w.b_last = bq.echo_last;
  o.b_valid = bq_valid && w.b_last; o.b = bq; o.b.resp = static_cast<uint8_t>(bq.resp | m.error[bq.id & 15]);
  o.r_valid = rq_valid; o.r = rq; o.r.last = rq.last && rq.echo_last;
  const bool b_up_ready = in.b_ready, r_up_ready = in.r_ready;
  w.b_up_fire = o.b_valid && b_up_ready; w.b_up = o.b;
  w.r_up_fire = o.r_valid && r_up_ready; w.r_up = o.r;
  w.b_out_fire = bq_valid && (b_up_ready || !w.b_last); w.b_out = bq;   // out.b.ready = in.b.ready || !b_last
  w.r_out_fire = rq_valid && r_up_ready; w.r_out = rq;
  // ---- requests: yanker -> fragmenter queues ----
  const bool ar_q_valid = m.q_ar.deq_valid(in.ar_valid); const AxiA& ar_a = m.q_ar.deq_bits(in.ar);
  const bool aw_q_valid = m.q_aw.deq_valid(in.aw_valid); const AxiA& aw_a = m.q_aw.deq_bits(in.aw);
  const bool w_q_valid = m.q_w.deq_valid(in.w_valid); const AxiW& w_a = m.q_w.deq_bits(in.w);
  // fragment(ar)
  const uint8_t ar_len = m.ar_busy ? m.ar_len : ar_a.len;
  const uint32_t ar_addr = m.ar_busy ? m.ar_addr : ar_a.addr;
  w.ar_last = ar_len == 0;
  w.ar_mux_addr = ar_addr + (1u << ar_a.size);
  w.ar_len = static_cast<uint8_t>(ar_len - 1);
  w.ar_out = ar_a; w.ar_out.len = 0; w.ar_out.addr = ar_addr & ~oh1(ar_a.size, 3); w.ar_out.echo_last = w.ar_last;
  // fragment(aw)
  const uint8_t aw_len = m.aw_busy ? m.aw_len : aw_a.len;
  const uint32_t aw_addr = m.aw_busy ? m.aw_addr : aw_a.addr;
  w.aw_last = aw_len == 0;
  w.aw_mux_addr = aw_addr + (1u << aw_a.size);
  w.aw_len = static_cast<uint8_t>(aw_len - 1);
  w.aw_out = aw_a; w.aw_out.len = 0; w.aw_out.addr = aw_addr & ~oh1(aw_a.size, 3); w.aw_out.echo_last = w.aw_last;
  // W beats
  const bool w_idle = m.w_counter == 0;
  w.wbeats_ready = w_idle;
  w.wbeats_valid = aw_q_valid && !m.wbeats_latched;
  w.w_todo = static_cast<uint16_t>(w_idle ? (w.wbeats_valid ? 1 : 0) : m.w_counter);
  const bool w_last = w.w_todo == 1;
  const bool aw_gate = w.wbeats_ready || m.wbeats_latched;
  const bool out_aw_valid = aw_q_valid && aw_gate;
  const bool out_ar_valid = ar_q_valid;
  const bool out_w_valid = w_q_valid && (!w.wbeats_ready || w.wbeats_valid);
  w.w_out = w_a; w.w_out.last = w_last;
  // buffer enq readies
  const bool buf_aw_ready = m.b_aw.enq_ready(), buf_ar_ready = m.b_ar.enq_ready(), buf_w_ready = m.b_w.enq_ready();
  w.aw_out_fire = out_aw_valid && buf_aw_ready;
  w.ar_out_fire = out_ar_valid && buf_ar_ready;
  w.w_out_fire = out_w_valid && buf_w_ready;
  // fragmenter input readies: a.ready = out.ready && last (ar); aw: in_aw.ready = out.aw.ready && gate, then && last
  const bool ar_q_deq = ar_q_valid && buf_ar_ready && w.ar_last;
  const bool aw_q_deq = aw_q_valid && buf_aw_ready && aw_gate && w.aw_last;
  const bool w_q_deq = w_q_valid && buf_w_ready && (!w.wbeats_ready || w.wbeats_valid);
  (void)ar_q_deq; (void)aw_q_deq; (void)w_q_deq;   // recomputed in commit from the out fires
  w.ar_in_fire = in.ar_valid && m.q_ar.enq_ready(); w.ar_in = in.ar;
  w.aw_in_fire = in.aw_valid && m.q_aw.enq_ready(); w.aw_in = in.aw;
  w.w_in_fire = in.w_valid && m.q_w.enq_ready(); w.w_in = in.w;
  o.ar_ready = m.q_ar.enq_ready(); o.aw_ready = m.q_aw.enq_ready(); o.w_ready = m.q_w.enq_ready();
  // ---- buffer -> RAM ----
  const bool baw_valid = !m.b_aw.empty(); const AxiA& baw = m.b_aw.head();
  const bool bar_valid = !m.b_ar.empty(); const AxiA& bar = m.b_ar.head();
  const bool bw_valid = !m.b_w.empty(); const AxiW& bw = m.b_w.head();
  const bool ram_aw_ready = bw_valid && (ram_b_ready || !m.w_full);
  const bool ram_w_ready = baw_valid && (ram_b_ready || !m.w_full);
  const bool ram_ar_ready = ram_r_ready || !m.r_full;
  w.ram_aw_fire = baw_valid && ram_aw_ready; w.ram_aw = baw;
  w.ram_w_fire = bw_valid && ram_w_ready; w.ram_w = bw;
  w.ram_ar_fire = bar_valid && ram_ar_ready; w.ram_ar = bar;
  w.ram_w_index = (baw.addr >> 3) & index_mask; w.ram_w_sel0 = baw.addr >= base && baw.addr - base < size;
  w.ram_r_index = (bar.addr >> 3) & index_mask; w.ram_r_sel0 = bar.addr >= base && bar.addr - base < size;
  w.ram_rdata_next = read_data;
}

}  // namespace

// The queue dequeues of the AXI fragmenter are recomputed here from the stored wires.
void axi_mem_commit(AxiMem& m, const AxiMemWires& w, uint8_t* mem_bytes) {
  // The fragmenter queue dequeues, recomputed from the out fires exactly as in evaluate.
  const bool ar_deq = w.ar_out_fire && w.ar_last;
  const bool aw_deq = w.aw_out_fire && w.aw_last;
  const bool w_deq = w.w_out_fire;
  const bool wb_latch_set = w.wbeats_valid && w.wbeats_ready;
  // RAM write happens before the read data capture? Reads return pre-write contents (computed in evaluate).
  if (w.ram_aw_fire && w.ram_w_sel0) {
    uint8_t* p = mem_bytes + static_cast<size_t>(w.ram_w_index) * 8;
    for (unsigned i = 0; i < 8; ++i) if ((w.ram_w.strb >> i) & 1) p[i] = static_cast<uint8_t>(w.ram_w.data >> (8 * i));
  }
  if (w.ram_b_fire) m.w_full = false;
  if (w.ram_aw_fire) { m.w_full = true; m.w_id = w.ram_aw.id; m.w_sel1 = w.ram_w_sel0; m.w_echo_last = w.ram_aw.echo_last; m.w_echo_size = w.ram_aw.echo_size; m.w_echo_source = w.ram_aw.echo_source; m.w_echo_extra = w.ram_aw.echo_extra; }
  if (m.ren_prev) m.rdata = w.raw_read_data;
  m.ren_prev = w.ram_ar_fire;
  if (w.ram_r_fire) m.r_full = false;
  if (w.ram_ar_fire) { m.r_full = true; m.r_id = w.ram_ar.id; m.r_sel1 = w.ram_r_sel0; m.r_echo_last = w.ram_ar.echo_last; m.r_echo_size = w.ram_ar.echo_size; m.r_echo_source = w.ram_ar.echo_source; m.r_echo_extra = w.ram_ar.echo_extra; m.r_addr_prev = w.ram_r_index; }
  // buffer queues
  m.b_aw.step(w.aw_out_fire, w.aw_out, w.ram_aw_fire);
  m.b_ar.step(w.ar_out_fire, w.ar_out, w.ram_ar_fire);
  m.b_w.step(w.w_out_fire, w.w_out, w.ram_w_fire);
  m.b_b.step(w.ram_b_fire, w.b_buf, w.b_out_fire);
  m.b_r.step(w.ram_r_fire, w.r_buf, w.r_out_fire);
  // fragmenter state
  if (w.ar_out_fire) { m.ar_busy = !w.ar_last; m.ar_addr = w.ar_mux_addr; m.ar_len = w.ar_len; }
  if (w.aw_out_fire) { m.aw_busy = !w.aw_last; m.aw_addr = w.aw_mux_addr; m.aw_len = w.aw_len; }
  if (wb_latch_set) m.wbeats_latched = true;
  if (w.aw_out_fire) m.wbeats_latched = false;
  m.w_counter = static_cast<uint16_t>(w.w_todo - (w.w_out_fire ? 1 : 0));
  if (w.b_out_fire) { const unsigned id = w.b_out.id & 15; m.error[id] = static_cast<uint8_t>(w.b_last ? 0 : (m.error[id] | w.b_out.resp)); }
  m.q_ar.step(w.ar_in_fire, w.ar_in, ar_deq);
  m.q_aw.step(w.aw_in_fire, w.aw_in, aw_deq);
  m.q_w.step(w.w_in_fire, w.w_in, w_deq);
}

Uncore::Uncore() : w_(new Wires) {
  // Scalar cold construction zeroes all state before real reset edges.
  tile_arb.mask = cb_d_arb.mask = dbg.dmiXbar_d.mask = 0;
  for (auto& arb : sb_a) arb.mask = 0;
  for (auto& arb : sb_d) arb.mask = 0;
  for (auto& tracker : trk) { tracker.address = 0; tracker.got_e = tracker.sent_d = false; }
  for (unsigned id = 0; id < 5; ++id) {
    const unsigned depth = id == 1 || id == 2 ? 8 : 1;
    mm_rq_big[id].set_depth(depth);
    mm_wq_big[id].set_depth(depth);
  }
  dbg.bar_in_reset = false; dbg.err_idle = false; dbg.clock_en = false;
  mb_axi.r_first = mm_axi.r_first = false;
  for (unsigned i = 0; i < 512; ++i) rom_[i] = kBootRom[i];
}

Uncore::~Uncore() { delete w_; }

void Uncore::attach_memory(uint8_t* dram, uint64_t bytes) {
  if (dram == nullptr || bytes < UINT64_C(0x10000000))
    throw std::invalid_argument("Rocket uncore requires its full 256 MiB DRAM backing");
  if (evaluated_) throw std::logic_error("cannot replace memory during a prepared uncore cycle");
  dram_ = dram; dram_bytes_ = bytes;
}

uint64_t Uncore::read_memory_word(uint64_t address) const {
  if (dram_ == nullptr || address < UINT64_C(0x80000000) ||
      address - UINT64_C(0x80000000) > dram_bytes_ - sizeof(uint64_t))
    throw std::out_of_range("uncore DRAM read outside attached memory");
  uint64_t value;
  std::memcpy(&value, dram_ + address - UINT64_C(0x80000000), sizeof value);
  return value;
}

void Uncore::write_memory_word(uint64_t address, uint64_t value, uint8_t byte_mask) {
  if (evaluated_) throw std::logic_error("cannot mutate DRAM during a prepared uncore cycle");
  const uint64_t prior = read_memory_word(address);
  const uint64_t next = byte_merge(prior, value, byte_mask);
  std::memcpy(dram_ + address - UINT64_C(0x80000000), &next, sizeof next);
}

// ============================================================================
// evaluate
// ============================================================================
void Uncore::evaluate(const UncoreIn& in, UncoreOut& out) {
  if (dram_ == nullptr) throw std::logic_error("Rocket uncore memory is not attached");
  const bool no_requests = !in.dc_a_valid && !in.ic_a_valid && !in.dc_c_valid && !in.dc_e_valid;
  const bool same_external = in.reset == captured_input_.reset &&
      in.dmi_req_valid == captured_input_.dmi_req_valid && in.dmi_req_addr == captured_input_.dmi_req_addr &&
      in.dmi_req_data == captured_input_.dmi_req_data && in.dmi_req_op == captured_input_.dmi_req_op &&
      in.dmi_resp_ready == captured_input_.dmi_resp_ready;
  if (evaluation_reuse_enabled_ && evaluated_ && same_external && (transport_evaluated_ || no_requests)) {
    // All five tile boundary queues are depth-two, without pipe or flow.
    // Within one PRE epoch, current cache inputs affect only enqueue/dequeue
    // decisions at this boundary; the internal buses and DMI computation are
    // already final. A first request after the idle shortcut requires a full
    // internal evaluation, because the old transport wires were not prepared.
    captured_input_ = in;
    out = transport_output_;
    evaluate_boundary(in, out);
    transport_output_ = out;
    ++reused_evaluations_;
    return;
  }
  evaluated_ = false;
  captured_input_ = in;
  Wires& w = *w_;
  if (idle_skip_enabled_ && can_skip_transport_ && !in.reset && !ldut_reset_reg &&
      !in.dc_a_valid && !in.ic_a_valid && !in.dc_c_valid && !in.dc_e_valid) {
    // Empty queues and settled arbiters cannot observe invalid cache payloads.
    // DMI crossings, interrupts and RTC remain live on every cycle.
    transport_evaluated_ = false;
    idle_ = true;
    out = transport_output_;
    const std::size_t debug_begin = offsetof(Wires, dmi_a_valid);
    std::memset(reinterpret_cast<char*>(&w) + debug_begin, 0, sizeof(Wires) - debug_begin);
    w.plic_in_fire = w.plic_out_fire = w.clint_write = w.dbg_tl_fire = false;
    w.mem.ram_aw_fire = false;
    std::memcpy(&w.mem.raw_read_data, dram_ + static_cast<size_t>(mem.r_addr_prev) * 8, 8);
    eval_debug(in, out);
    out.int_debug = tile_debug_int_sync.out();
    out.int_msip = int_clint_reg[0]; out.int_mtip = int_clint_reg[1];
    out.int_meip = int_plic_reg[0]; out.int_seip = int_plic_reg[1];
    out.system_reset = false;
    w.rtc_tick = rtc_div == 99;
    debug_comb_ = !dbg.dmactive_synced.out();
    evaluated_ = true;
    transport_output_ = out;
    return;
  }
  transport_evaluated_ = true;
  // A speculative full evaluation may change the combinational output guess.
  // Do not reuse that guess as a quiescent image in a later closure round.
  can_skip_transport_ = false;
  idle_ = false;
  w = Wires{};
  const bool reset = in.reset;

  // ---------------------------------------------------------------- memory bus AXI chain: responses first
  // TLToAXI4 (mbus) response side.  R/B come from mem (buffer -> fragmenter) through the yanker/indexer.
  // -- memory: response valids (register-derived)
  AxiOutReady mem_o{}; AxiIn mem_in{};
  AxiOutReady mm_o{}; AxiIn mm_in{};
  // mbus TLToAXI4 in.d (from mem R/B): needs the yanker echo restore and indexer id restore
  // Yanker: in.r = out.r with echo from rqueues[rid]
  auto yank_r = [&](const AxiR& r, const Queue<YankEcho, 8>* rq, unsigned nq, AxiR& outr) {
    outr = r; const unsigned id = r.id % nq; const YankEcho& e = rq[id].head(); outr.echo_size = e.size; outr.echo_source = e.source; outr.echo_extra = e.extra;
  };
  auto yank_b = [&](const AxiB& b, const Queue<YankEcho, 8>* wq, unsigned nq, AxiB& outb) {
    outb = b; const unsigned id = b.id % nq; const YankEcho& e = wq[id].head(); outb.echo_size = e.size; outb.echo_source = e.source; outb.echo_extra = e.extra;
  };
  // ---- mem side valids ----
  {
    const AxiMem& m = mem;
    const bool bq_valid = !m.b_b.empty(); const AxiB& bq = m.b_b.head();
    const bool rq_valid = !m.b_r.empty(); const AxiR& rq = m.b_r.head();
    AxiB bf = bq; bf.resp = static_cast<uint8_t>(bq.resp | m.error[bq.id & 15]);
    AxiR rf = rq; rf.last = rq.last && rq.echo_last;
    AxiR ry; AxiB by; yank_r(rf, mb_rq, 16, ry); yank_b(bf, mb_wq, 16, by);
    // IdIndexer(4): restore the TL source from extra_id
    ry.id = static_cast<uint8_t>((ry.echo_extra << 4) | (ry.id & 15));
    by.id = static_cast<uint8_t>((by.echo_extra << 4) | (by.id & 15));
    w.mb.r_valid = rq_valid; w.mb.r = ry;
    w.mb.b_valid = bq_valid && bq.echo_last; w.mb.b = by;
  }
  {
    const AxiMem& m = mmio;
    const bool bq_valid = !m.b_b.empty(); const AxiB& bq = m.b_b.head();
    const bool rq_valid = !m.b_r.empty(); const AxiR& rq = m.b_r.head();
    AxiB bf = bq; bf.resp = static_cast<uint8_t>(bq.resp | m.error[bq.id & 15]);
    AxiR rf = rq; rf.last = rq.last && rq.echo_last;
    // sbus coupler AXI4Buffer (mm_buf_b / mm_buf_r) sits between the mmio_mem and the yanker
    w.mmb_b_enq = false; w.mmb_r_enq = false;   // set with readies below
    w.mmb_b_bits = bf; w.mmb_r_bits = rf;
    const bool bb_valid = !mm_buf_b.empty(); const AxiB& bb = mm_buf_b.head();
    const bool rb_valid = !mm_buf_r.empty(); const AxiR& rb = mm_buf_r.head();
    AxiR ry; AxiB by; yank_r(rb, mm_rq_big, 5, ry); yank_b(bb, mm_wq_big, 5, by);
    // Deinterleaver: r goes through per-id queues; b passes
    w.mm_deint_enq_bits = ry;
    (void)rb_valid; (void)bq_valid; (void)rq_valid;
    w.mm.b_valid = bb_valid; w.mm.b = by;
    // deinterleaver output
    const bool locked = mm_deint_locked; const unsigned deq_id = mm_deint_id;
    w.mm.r_valid = locked; w.mm.r = mm_deint_q[deq_id].head();
  }
  // TLToAXI4 D valids (mbus and mmio)
  auto toaxi_resp = [&](const ToAxi4& t, ToAxiWires& tw) {
    tw.r_wins = (tw.r_valid && t.b_delay != 7) || t.r_holds_d;
    tw.d_valid = tw.r_wins ? tw.r_valid : tw.b_valid;
    if (tw.r_wins) {
      const bool r_denied = t.r_first ? (tw.r.resp == kAxiDecErr) : t.r_denied_hold;
      const bool r_corrupt = tw.r.resp != kAxiOkay;
      tw.d = access_ack(tw.r.echo_source, tw.r.echo_size, true, tw.r.data, r_denied, r_corrupt || r_denied);
      tw.d_last = tw.r.last; tw.d_id = tw.r.id;
    } else {
      tw.d = access_ack(tw.b.echo_source, tw.b.echo_size, false, tw.r.data, tw.b.resp != kAxiOkay, false);
      tw.d_last = true; tw.d_id = tw.b.id;
    }
  };
  toaxi_resp(mb_axi, w.mb);
  toaxi_resp(mm_axi, w.mm);

  // ---------------------------------------------------------------- control bus: D from the buffer through the atomics
  {
    const bool d_valid = !cb_d.empty(); const TlD& d = cb_d.head();
    const Atomics& at = cb_atomics;
    w.at_d_first = at.d_first.first();
    w.at_d_beats1 = beats1(d.size, d_has_data(d.opcode), kSbusMaxLg);
    const bool cam_dmatch = at.cam_state != kFree;
    w.at_d_sel = cam_dmatch && at.cam_a.source == d.source;
    const bool d_ackd = d.opcode == D_AccessAckData, d_ack = d.opcode == D_AccessAck;
    w.at_d_drop = w.at_d_first && d_ackd && w.at_d_sel;
    const bool d_replace = w.at_d_first && d_ack && w.at_d_sel;
    w.cb_d_valid_up = d_valid && !w.at_d_drop;
    w.at_d_out = d;
    if (d_replace) { w.at_d_out.opcode = D_AccessAckData; w.at_d_out.data = at.cam_d_data; w.at_d_out.corrupt = at.cam_d_corrupt || d.denied; w.at_d_out.denied = at.cam_d_denied || d.denied; }
    w.cb_d_up = w.at_d_out;
  }

  // ---------------------------------------------------------------- l2 hub: D side (from mbus) and C side valids
  {
    const TlD& od = w.mb.d;     // out.d = mbus D (tl2axi4 in.d)
    const bool od_valid = w.mb.d_valid;
    const unsigned d_what = (od.source >> 5) & 3;
    const bool d_drop = d_what == kDrop;
    const bool d_hasData = d_has_data(od.opcode);
    TlD dn = od; dn.source = od.source & 0x1F;
    if (d_what & 2) { dn.opcode = d_hasData ? D_GrantData : D_ReleaseAck; dn.param = d_hasData ? ((d_what & 1) ? P_toT : P_toB) : 0; }
    w.l2_d_first = l2_d_cnt.first();
    uint8_t oh = 0;
    for (unsigned t = 0; t < 4; ++t) if (!trk[t].sent_d && trk[t].source == dn.source) oh |= 1u << t;
    w.l2_trackerOH = w.l2_d_first ? oh : d_trackerOH_hold;
    { uint8_t s = 0; for (unsigned t = 0; t < 4; ++t) if ((w.l2_trackerOH >> t) & 1) s |= static_cast<uint8_t>(t); dn.sink = s; }   // OHToUInt
    const bool dn_valid = od_valid && !d_drop;
    w.l2_dn_beats1 = beats1(dn.size, d_hasData, kL2MaxLg);
    // releaseack from C
    const bool c_valid = !tb_c.empty(); TlC c = tb_c.head(); c.source = static_cast<uint8_t>(c.source + kTileSourceBase);
    w.l2_c_valid = c_valid; w.l2_c = c;
    const bool c_release = c.opcode == C_Release;
    TlD ra; ra.opcode = D_ReleaseAck; ra.param = 0; ra.size = c.size; ra.source = c.source; ra.sink = 0; ra.denied = false; ra.data = 0; ra.corrupt = false;
    const bool ra_valid = c_valid && c_release;
    // in.d arbiter (lowest): [releaseack, d_normal]
    w.l2d_valids = (ra_valid ? 1u : 0) | (dn_valid ? 2u : 0);
    const uint32_t win = l2_d_arb.winner(w.l2d_valids);
    w.l2_outd_valid = l2_d_arb.sink_valid(w.l2d_valids);
    w.l2_outd = (win & 1) ? ra : (win & 2) ? dn : TlD{};
    w.l2d_beats1 = (win & 1) ? 0 : (win & 2) ? w.l2_dn_beats1 : 0;
    w.out_d_valid[kL2] = w.l2_outd_valid; w.out_d[kL2] = w.l2_outd;
    // stash for later
    w.l2_dnormal_fire = false;
  }
  // cbus D towards the sbus
  w.out_d_valid[kCbus] = w.cb_d_valid_up; w.out_d[kCbus] = w.cb_d_up;
  // mmio D
  w.out_d_valid[kMmio] = w.mm.d_valid; w.out_d[kMmio] = w.mm.d;

  // ---------------------------------------------------------------- system bus D arbiters -> tile buffer d
  {
    // input 1 (tile) sees the responses whose source is in [16, 20); input 0 (fbus) the others
    for (unsigned i = 0; i < 2; ++i) w.sb_d_valids[i] = 0;
    for (unsigned o = 0; o < 3; ++o) {
      if (!w.out_d_valid[o]) continue;
      const unsigned i = (w.out_d[o].source >= kTileSourceBase) ? 1 : 0;
      w.sb_d_valids[i] |= 1u << o;
    }
    w.sb_d_ready[1] = tb_d.enq_ready();
    w.sb_d_ready[0] = true;   // the front bus never receives anything
    for (unsigned i = 0; i < 2; ++i) {
      const uint32_t win = sb_d[i].winner(w.sb_d_valids[i]);
      const bool sv = sb_d[i].sink_valid(w.sb_d_valids[i]);
      w.sb_d_fire[i] = sv && w.sb_d_ready[i];
      w.sb_d_beats1[i] = 0;
      if (win) { const unsigned o = lowest_bit(win); w.sb_d_beats1[i] = beats1(w.out_d[o].size, d_has_data(w.out_d[o].opcode), kSbusMaxLg); }
      if (i == 1) {
        w.tb_d_enq_fire = w.sb_d_fire[1];
        if (win) { const unsigned o = lowest_bit(win); w.tb_d_enq = w.out_d[o]; w.tb_d_enq.source = static_cast<uint8_t>(w.out_d[o].source & 3); }
      }
    }
    for (unsigned o = 0; o < 3; ++o) {
      const unsigned i = (w.out_d[o].source >= kTileSourceBase) ? 1 : 0;
      w.out_d_ready[o] = w.sb_d_ready[i] && ((sb_d[i].allowed(w.sb_d_valids[i]) >> o) & 1);
    }
  }
  // l2 hub D readies
  bool l2_outd_ready = w.out_d_ready[kL2];
  bool l2_dn_ready, l2_ra_ready;
  {
    const uint32_t allowed = l2_d_arb.allowed(w.l2d_valids);
    l2_ra_ready = l2_outd_ready && (allowed & 1);
    l2_dn_ready = l2_outd_ready && ((allowed >> 1) & 1);
    w.l2d_sink_ready = l2_outd_ready;
    w.l2d_sink_fire = w.l2_outd_valid && l2_outd_ready;
    const TlD& od = w.mb.d; const bool od_valid = w.mb.d_valid;
    const bool d_drop = ((od.source >> 5) & 3) == kDrop;
    const bool d_hasData = d_has_data(od.opcode);
    const bool outd_ready = (l2_dn_ready) || d_drop;          // d_allow is always true (BroadcastFilter)
    w.l2_outd_fire = od_valid && outd_ready;
    w.l2_dnormal_fire = od_valid && !d_drop && l2_dn_ready;
    const bool d_response = d_hasData || !(((od.source >> 5) & 2) != 0);
    const bool d_last = l2_d_cnt.last(w.l2_dn_beats1);
    for (unsigned t = 0; t < 4; ++t) {
      const bool sel = (w.l2_trackerOH >> t) & 1;
      w.trk_d_last[t] = sel && w.l2_dnormal_fire && d_response && d_last;
      w.trk_probedack[t] = sel && w.l2_outd_fire && d_drop;
    }
    w.mb.d_fire = w.l2_outd_fire;   // tl2axi4 in.d.ready = hub out.d.ready
  }
  // mbus TLToAXI4 R/B readies (in.d.ready = hub out.d ready)
  {
    ToAxiWires& t = w.mb;
    // in.d.ready of the bridge is the hub's out.d.ready
    const TlD& od = w.mb.d; const bool d_drop = ((od.source >> 5) & 3) == kDrop;
    const bool ind_ready = l2_dn_ready || d_drop;
    t.r_fire = t.r_valid && ind_ready && t.r_wins;
    t.b_fire = t.b_valid && ind_ready && !t.r_wins;
    t.d_fire = t.d_valid && ind_ready;
    mem_in.r_ready = ind_ready && t.r_wins;
    mem_in.b_ready = ind_ready && !t.r_wins;
  }
  // mmio TLToAXI4 readies (in.d.ready = sbus out2 d ready)
  {
    ToAxiWires& t = w.mm;
    const bool ind_ready = w.out_d_ready[kMmio];
    t.r_fire = t.r_valid && ind_ready && t.r_wins;
    t.b_fire = t.b_valid && ind_ready && !t.r_wins;
    t.d_fire = t.d_valid && ind_ready;
    // deinterleaver: in.r.fire
    w.mm_deint_in_r_fire = t.r_fire;
    // b path: mm_buf_b deq = b fire (yanker passes b)
    w.mmb_b_deq = t.b_fire;
    // r: deinterleaver queue deq
    for (unsigned i = 0; i < 5; ++i) w.mm_deint_q_deq[i] = (mm_deint_id == i) && t.r_fire;
  }

  // buffer_1 a -> sbus in_1 a
  w.tile_a_valid = !tb_a.empty();
  w.tile_a = tb_a.head(); w.tile_a.source = static_cast<uint8_t>(w.tile_a.source + kTileSourceBase);
  w.tile_route = sbus_route(w.tile_a.address);
  for (unsigned o = 0; o < 3; ++o) {
    w.sb_a_valids[o] = (w.tile_a_valid && w.tile_route == o) ? 2u : 0;
    const uint32_t win = sb_a[o].winner(w.sb_a_valids[o]);
    w.sb_a_out[o] = (win & 2) ? w.tile_a : TlA{};
    w.sb_a_beats1[o] = (win & 2) ? beats1(w.tile_a.size, a_has_data(w.tile_a.opcode), kSbusMaxLg) : 0;
  }
  const bool sb_a_out_valid[3] = { sb_a[0].sink_valid(w.sb_a_valids[0]), sb_a[1].sink_valid(w.sb_a_valids[1]), sb_a[2].sink_valid(w.sb_a_valids[2]) };

  // ---------------------------------------------------------------- control bus request path
  bool cbus_a_ready = false;
  {
    const bool a_valid = sb_a_out_valid[kCbus]; const TlA& a = w.sb_a_out[kCbus];
    w.cb_a_in_valid = a_valid; w.cb_a_in = a;
    Atomics& at = cb_atomics;
    const bool a_isLogical = a.opcode == A_LogicalData, a_isArith = a.opcode == A_ArithmeticData;
    const bool native = a.address >= 0x3000 && a.address < 0x4000;   // only the error device supports atomics natively
    w.at_supported = a_isLogical ? native : a_isArith ? native : true;
    const bool cam_free = at.cam_state == kFree, cam_amo = at.cam_state == kAmo;
    const bool cam_abusy = at.cam_state == kGet || at.cam_state == kAmo;
    const bool a_allow = !cam_abusy && (w.at_supported || cam_free);
    // source_c: the AMO put from the CAM
    TlA sc; uint64_t amo_data = 0;
    if (cam_amo) {
      const uint64_t aa = at.cam_a.data, ad = at.cam_d_data;
      // logical
      uint64_t logic_out;
      switch (at.cam_a.param & 3) {
        case 0: logic_out = aa ^ ad; break;  // TLAtomics.XOR
        case 1: logic_out = aa | ad; break;  // TLAtomics.OR
        case 2: logic_out = aa & ad; break;  // TLAtomics.AND
        default: logic_out = aa; break;     // TLAtomics.SWAP
      }
      // arithmetic
      const bool unsigned_ = (at.cam_a.param >> 1) & 1, take_max = at.cam_a.param & 1, adder = (at.cam_a.param >> 2) & 1;
      const uint8_t mask = at.cam_a.mask;
      const uint8_t signSel = static_cast<uint8_t>(~(~mask | (mask >> 1)));
      uint8_t signbits_a = 0, signbits_d = 0;
      for (unsigned i = 0; i < 8; ++i) { signbits_a |= static_cast<uint8_t>(((aa >> (8 * i + 7)) & 1) << i); signbits_d |= static_cast<uint8_t>(((ad >> (8 * i + 7)) & 1) << i); }
      const uint8_t signbit_a = static_cast<uint8_t>((signbits_a & signSel) << 1), signbit_d = static_cast<uint8_t>((signbits_d & signSel) << 1);
      uint64_t signext_a = 0, signext_d = 0, wide_mask = 0;
      const uint8_t la = static_cast<uint8_t>(left_or(signbit_a, 8)), ld = static_cast<uint8_t>(left_or(signbit_d, 8));
      for (unsigned i = 0; i < 8; ++i) { if ((la >> i) & 1) signext_a |= UINT64_C(0xFF) << (8 * i); if ((ld >> i) & 1) signext_d |= UINT64_C(0xFF) << (8 * i); if ((mask >> i) & 1) wide_mask |= UINT64_C(0xFF) << (8 * i); }
      const uint64_t a_ext = (aa & wide_mask) | signext_a, d_ext = (ad & wide_mask) | signext_d;
      const uint64_t d_inv = adder ? d_ext : ~d_ext;
      const uint64_t adder_out = a_ext + d_inv;
      const bool a_bigger_uneq = unsigned_ == ((a_ext >> 63) & 1);
      const bool a_bigger = (((a_ext >> 63) & 1) == ((d_ext >> 63) & 1)) ? !((adder_out >> 63) & 1) : a_bigger_uneq;
      const bool pick_a = take_max == a_bigger;
      const uint64_t arith_out = adder ? adder_out : (pick_a ? aa : ad);
      amo_data = (at.cam_a.opcode & 1) ? logic_out : arith_out;
      sc.opcode = A_PutFullData; sc.param = 0; sc.size = at.cam_a.size; sc.source = at.cam_a.source; sc.address = at.cam_a.address;
      sc.mask = tl_mask(at.cam_a.address, at.cam_a.size); sc.data = amo_data; sc.corrupt = at.cam_a.corrupt || at.cam_d_corrupt;
    }
    TlA si = a; if (!w.at_supported) { si.opcode = A_Get; si.param = 0; }
    const bool si_valid = a_valid && a_allow;
    w.at_valids = (cam_amo ? 1u : 0) | (si_valid ? 2u : 0);
    const uint32_t win = at.arb.winner(w.at_valids);
    w.at_out = (win & 1) ? sc : (win & 2) ? si : TlA{};
    w.at_beats1 = (win & 2) ? beats1(si.size, a_has_data(si.opcode), kSbusMaxLg) : 0;
    w.at_sink_ready = cb_a.enq_ready();
    w.at_sink_fire = at.arb.sink_valid(w.at_valids) && w.at_sink_ready;
    const uint32_t allowed = at.arb.allowed(w.at_valids);
    w.at_source_c_fire = cam_amo && w.at_sink_ready && (allowed & 1);
    w.at_source_i_fire = si_valid && w.at_sink_ready && ((allowed >> 1) & 1);
    cbus_a_ready = w.at_sink_ready && ((allowed >> 1) & 1) && a_allow;
    w.cb_a_enq_fire = w.at_sink_fire;
  }
  // buffer a -> fixer -> out_xbar -> devices
  {
    const TlA& a = cb_a.head();
    const bool a_valid = !cb_a.empty() && cb_fixer.allow(a, false, cbus_fifo_domain(a.address));
    w.cb_a_head = a;
    w.cb_fixer_beats1 = beats1(a.size, a_has_data(a.opcode), kSbusMaxLg);
    const unsigned dev = cbus_route(a.address);
    bool dev_ready = false;
    // device D valids (combinational for the register devices) -> D arbiter
    uint32_t dvalids = 0; TlD dbits[5];
    // error device: its response comes from its own queues (registers)
    {
      const ErrorDevice& e = cb_err;
      const bool ea_valid = !e.a.empty(); const TlA& ea = e.a.head();
      w.er_a_beats1 = beats1(ea.size, a_has_data(ea.opcode), kSbusMaxLg);
      const bool a_last = e.a_last.last(w.er_a_beats1);
      TlD da; da.opcode = static_cast<uint8_t>(ea.opcode < 2 ? D_AccessAck : ea.opcode < 5 ? D_AccessAckData : ea.opcode == 5 ? D_HintAck : D_Grant);
      da.param = 0; da.size = ea.size; da.source = ea.source; da.sink = 0; da.denied = true; da.data = 0; da.corrupt = d_has_data(da.opcode);
      const bool da_valid = ea_valid && a_last && e.idle;
      w.er_d = da;
      // in.d <> da -> buf_d enq
      const bool bufd_ready = e.buf_d.enq_ready();
      w.er_bufd_enq_fire = da_valid && bufd_ready;
      // a.ready = (da.ready && da_last(true) && idle) || !a_last
      w.er_a_deq_fire = ea_valid && ((bufd_ready && e.idle) || !a_last);
      // buf_a -> a queue
      const bool bufa_valid = !e.buf_a.empty();
      w.er_a_enq_fire = bufa_valid && e.a.enq_ready();
      w.er_bufa_deq_fire = w.er_a_enq_fire;
      dvalids |= (!e.buf_d.empty() ? 1u : 0) << kDevErr; dbits[kDevErr] = e.buf_d.head();
    }
    // fragmenter devices
    const Fragmenter* frs[4] = { &fr_plic, &fr_clint, &fr_debug, &fr_rom };
    const unsigned devof[4] = { kDevPlic, kDevClint, kDevDebug, kDevRom };
    for (unsigned k = 0; k < 4; ++k) {
      FragWires& fw = w.fr[k];
      fw.in_valid = a_valid && dev == devof[k]; fw.in = a;
      frag_forward(*frs[k], fw);
      const bool out_valid = frag_out_valid(*frs[k], fw);
      // device response (combinational)
      fw.d_valid = out_valid;
      TlD d = access_ack(fw.out.source, fw.out.size, fw.out.opcode == A_Get);
      const RegAccess ra = reg_access(fw.out, 3);
      uint64_t rdata = 0;
      if (k == kFrRom) {
        const unsigned index = (fw.out.address >> 3) & 511; const bool high = (fw.out.address >> 12) & 0xF;
        rdata = high ? 0 : rom_[index]; d.opcode = D_AccessAckData;
      } else if (k == kFrClint) {
        const unsigned index = ra.index & 0x1fff;
        if (index == 0) rdata = clint_ipi ? 1 : 0;
        else if (index == 0x800) rdata = clint_timecmp;
        else if (index == 0x17FF) rdata = clint_time;
      } else if (k == kFrDebug) {
        rdata = debug_tl_read(ra.index);
      } else {  // plic: register reads happen at the back of its queue; handled below
        rdata = 0;
      }
      d.data = rdata;
      fw.d = d;
      if (k == kFrPlic) {
        // RegMapper with concurrency 1: front -> queue -> back
        const bool back_valid = !plic_back.empty();
        const RegMapperReq& br = plic_back.head();
        TlD bd = access_ack(br.source, br.size, br.read);
        bd.data = plic_read(br.index, br.read);
        fw.d_valid = back_valid; fw.d = bd;
      }
      frag_response(*frs[k], fw);
      dvalids |= (fw.up_valid ? 1u : 0) << devof[k]; dbits[devof[k]] = fw.up;
    }
    // D arbiter of the out_xbar (5 sources) -> cbus buffer d
    w.cbd_valids = dvalids;
    w.cbd_sink_ready = cb_d.enq_ready();
    const uint32_t win = cb_d_arb.winner(dvalids);
    w.cbd_sink_fire = cb_d_arb.sink_valid(dvalids) && w.cbd_sink_ready;
    w.cbd_beats1 = 0;
    if (win) { const unsigned s = lowest_bit(win); w.cb_d_enq = dbits[s]; w.cbd_beats1 = beats1(dbits[s].size, d_has_data(dbits[s].opcode), kSbusMaxLg); }
    w.cb_d_enq_fire = w.cbd_sink_fire;
    const uint32_t allowed = cb_d_arb.allowed(dvalids);
    auto dready = [&](unsigned s) { return w.cbd_sink_ready && ((allowed >> s) & 1); };
    // error device buf_d deq
    w.er_bufd_deq_fire = !cb_err.buf_d.empty() && dready(kDevErr);
    // fragmenter devices: d fire and a readies
    for (unsigned k = 0; k < 4; ++k) {
      FragWires& fw = w.fr[k];
      const Fragmenter& f = *frs[k];
      const unsigned s = devof[k];
      const bool up_ready = dready(s);
      const bool drop = fw.d_valid && !fw.up_valid;
      const bool d_ready = up_ready || drop;   // out.d.ready = in.d.ready || drop
      fw.d_fire = fw.d_valid && d_ready;
      // device a ready
      bool a_ready;
      if (k == kFrPlic) {
        // in.ready = queue.enq_ready (iready true); back leaves when d_ready
        a_ready = plic_back.enq_ready();
        w.plic_out_fire = !plic_back.empty() && d_ready;
        w.plic_in_fire = frag_out_valid(f, fw) && a_ready;
        w.plic_req = RegMapperReq{fw.out.opcode == A_Get, (fw.out.address >> 3) & 0x7FFFFF, fw.out.data, fw.out.mask, fw.out.source, fw.out.size};
      } else {
        a_ready = d_ready;   // combinational register device: a.ready = d.ready
      }
      fw.device_a_ready = a_ready;
      const bool out_valid = frag_out_valid(f, fw);
      fw.out_fire = out_valid && a_ready;
      fw.rep_deq_fire = fw.out_fire;
      fw.rep_enq_fire = fw.in_valid && a_ready && !f.rep_full;
      if (dev == devof[k]) dev_ready = a_ready && !f.rep_full;
      if (fw.out_fire) {
        if (k == kFrClint && fw.out.opcode != A_Get) { w.clint_write = true; w.clint_index = (fw.out.address >> 3); w.clint_mask = fw.out.mask; w.clint_wdata = fw.out.data; }
        if (k == kFrDebug) { w.dbg_tl_fire = true; w.dbg_tl_read = fw.out.opcode == A_Get; w.dbg_tl_index = (fw.out.address >> 3) & 0x1FF; w.dbg_tl_mask = fw.out.mask; w.dbg_tl_wdata = fw.out.data; }
      }
    }
    if (dev == kDevErr) {
      w.er_bufa_enq_fire = a_valid && cb_err.buf_a.enq_ready();
      dev_ready = cb_err.buf_a.enq_ready();
    }
    w.cb_a_deq_fire = a_valid && dev_ready;
    // cbus D buffer deq (towards the sbus through the atomics)
    const bool d_valid = !cb_d.empty();
    w.at_d_fire = d_valid && (w.out_d_ready[kCbus] || w.at_d_drop);
    w.cb_d_deq_fire = w.at_d_fire;
  }

  // ---------------------------------------------------------------- l2 hub: A/B/C/E
  bool l2_a_ready = false;
  {
    const bool a_valid = sb_a_out_valid[kL2]; const TlA& a = w.sb_a_out[kL2];
    w.l2_a_valid = a_valid; w.l2_a = a;
    w.l2_a_first = l2_a_cnt.first();
    const bool probe_busy = probe_todo;
    uint32_t free = 0, match = 0, readys = 0;
    for (unsigned t = 0; t < 4; ++t) {
      const bool idle = trk[t].got_e && trk[t].sent_d;
      if (idle) free |= 1u << t;
      if ((trk[t].address >> 6) == (a.address >> 6)) match |= 1u << t;
      if ((idle || !w.l2_a_first) && trk[t].o_data.enq_ready()) readys |= 1u << t;
    }
    const uint32_t alloc = lowest_oh(free);
    w.l2_select = match ? match : alloc;
    const bool trackerReady = (w.l2_select & readys) != 0;
    l2_a_ready = (!w.l2_a_first || !probe_busy) && trackerReady;
    w.l2_a_ready = l2_a_ready;
    w.l2_req_fire = a_valid && w.l2_a_first && trackerReady && !probe_busy;   // filter request/response fire
    const bool a_cache = a.source == kTileSourceBase;
    w.l2_needT = need_t(a);
    const bool leaveB = false;   // gaveT is always true
    const uint8_t others = static_cast<uint8_t>(1 & ~(a_cache ? 1 : 0));
    w.l2_todo = !leaveB && others;
    w.l2_mshr = w.l2_select ? lowest_bit(w.l2_select) : 0;
    for (unsigned t = 0; t < 4; ++t) {
      const bool sel = (w.l2_select >> t) & 1;
      const bool in_a_valid = a_valid && sel && (!w.l2_a_first || !probe_busy);
      const bool idle = trk[t].got_e && trk[t].sent_d;
      w.trk_in_fire[t] = in_a_valid && (idle || !w.l2_a_first) && trk[t].o_data.enq_ready();
      w.trk_odata_enq[t] = w.trk_in_fire[t];
      w.trk_probe_valid[t] = w.l2_req_fire && w.l2_mshr == t;
    }
    // B: probe
    const bool b_valid = probe_busy;
    TlB b; b.opcode = B_Probe; b.param = probe_perms; b.size = 6; b.source = kTileSourceBase; b.address = probe_line << 6; b.mask = 0xFF; b.data = 0; b.corrupt = false;
    w.tb_b_enq = b; w.tb_b_enq.source = 0;   // trimmed for the tile
    w.tb_b_enq_fire = b_valid && tb_b.enq_ready();
    w.l2_b_fire = w.tb_b_enq_fire;
    // C
    const bool c_valid = w.l2_c_valid; const TlC& c = w.l2_c;
    const bool c_probeack = c.opcode == C_ProbeAck, c_probeackdata = c.opcode == C_ProbeAckData, c_releasedata = c.opcode == C_ReleaseData, c_release = c.opcode == C_Release;
    uint32_t c_oh = 0; for (unsigned t = 0; t < 4; ++t) if ((trk[t].address >> 6) == (c.address >> 6)) c_oh |= 1u << t;
    uint8_t c_src = 0; for (unsigned t = 0; t < 4; ++t) if ((c_oh >> t) & 1) c_src |= trk[t].source;
    const bool whoC = c.source == kTileSourceBase;
    const bool CisN = c.param == P_TtoN || c.param == P_BtoN || c.param == P_NtoN;
    // putfull (index 0 of the out.a arbiter)
    TlA pf; pf.opcode = A_PutFullData; pf.param = 0; pf.size = c.size;
    pf.source = static_cast<uint8_t>(((c_releasedata ? kTransformB : kDrop) << 5) | (c_releasedata ? c.source : c_src));
    pf.address = c.address; pf.mask = tl_mask(c.address, c.size); pf.data = c.data; pf.corrupt = false;
    const bool pf_valid = c_valid && (c_probeackdata || c_releasedata);
    // out.a arbiter (lowest): [putfull, trackers]
    uint32_t avalids = pf_valid ? 1u : 0;
    TlA tout[4]; uint32_t tb1[4] = {};
    for (unsigned t = 0; t < 4; ++t) {
      const Tracker& k = trk[t];
      const bool probe_done = k.count == 0;
      const bool acquire = k.opcode == A_AcquireBlock || k.opcode == A_AcquirePerm;
      const bool ov = !k.o_data.empty() && probe_done;
      if (ov) avalids |= 1u << (t + 1);
      TlA& o = tout[t];
      o.opcode = acquire ? A_Get : k.opcode; o.param = acquire ? 0 : k.param; o.size = k.size;
      o.source = static_cast<uint8_t>(((acquire ? (k.shared ? kTransformB : kTransformT) : kPass) << 5) | k.source);
      o.address = k.address; o.mask = k.o_data.head().mask; o.data = k.o_data.head().data; o.corrupt = false;
      tb1[t] = beats1(o.size, a_has_data(o.opcode), kL2MaxLg);
    }
    w.l2a_valids = avalids;
    const uint32_t win = l2_a_arb.winner(avalids);
    if (win & 1) { w.l2_out_a = pf; w.l2a_beats1 = beats1(pf.size, true, kL2MaxLg); }
    else if (win) { const unsigned t = lowest_bit(win) - 1; w.l2_out_a = tout[t]; w.l2a_beats1 = tb1[t]; }
    else { w.l2_out_a = TlA{}; w.l2a_beats1 = 0; }
    w.mb.a_valid = l2_a_arb.sink_valid(avalids); w.mb.a = w.l2_out_a;
    // E
    const bool e_valid = !tb_e.empty();
    w.l2_e_fire = e_valid; w.l2_e_sink = tb_e.head().sink;
    w.tb_e_deq_fire = e_valid;
    for (unsigned t = 0; t < 4; ++t) w.trk_e_last[t] = e_valid && w.l2_e_sink == t;
    (void)c_probeack; (void)whoC; (void)CisN; (void)c_release;
  }

  // ---------------------------------------------------------------- memory bus TLToAXI4 request side + memory
  {
    ToAxi4& t = mb_axi; ToAxiWires& tw = w.mb;
    const TlA& a = tw.a;
    tw.a_first = t.a_cnt.first();
    const uint32_t b1 = beats1(a.size, a_has_data(a.opcode), kL2MaxLg);
    tw.a_last = t.a_cnt.last(b1);
    tw.is_put = a_has_data(a.opcode);
    tw.a_id = a.source;
    tw.stall = (t.count[a.source] != 0) && tw.a_first;
    ToAxi4::Arw arw; arw.wen = tw.is_put;
    arw.a.id = a.source; arw.a.addr = a.address; arw.a.len = static_cast<uint8_t>(oh1(a.size, 11) >> 3); arw.a.size = a.size >= 3 ? 3 : a.size;
    arw.a.burst = 1; arw.a.lock = false; arw.a.cache = 0; arw.a.prot = 1; arw.a.qos = 0;
    arw.a.echo_size = a.size; arw.a.echo_source = a.source; arw.a.echo_extra = 0; arw.a.echo_last = false;
    tw.arw = arw;
    const bool arw_ready = t.q_arw.enq_ready(), w_ready = t.q_w.enq_ready();
    tw.arw_valid = !tw.stall && tw.a_valid && (tw.is_put ? (!t.doneAW && w_ready) : true);
    tw.w_valid = !tw.stall && tw.a_valid && tw.is_put && (t.doneAW || arw_ready);
    tw.w.data = a.data; tw.w.strb = a.mask; tw.w.last = tw.a_last; tw.w.corrupt = a.corrupt;
    const bool a_ready = !tw.stall && (tw.is_put ? ((t.doneAW || arw_ready) && w_ready) : arw_ready);
    tw.a_fire = tw.a_valid && a_ready;
    tw.arw_fire = tw.arw_valid && arw_ready;
    tw.w_fire = tw.w_valid && w_ready;
    // queue outputs -> IdIndexer -> UserYanker -> mem fragmenter
    const bool qarw_valid = t.q_arw.deq_valid(tw.arw_valid); const ToAxi4::Arw& qa = t.q_arw.deq_bits(tw.arw);
    const bool qw_valid = t.q_w.deq_valid(tw.w_valid); const AxiW& qw = t.q_w.deq_bits(tw.w);
    AxiA ax = qa.a; ax.echo_extra = static_cast<uint8_t>(qa.a.id >> 4); ax.id = qa.a.id & 15;   // IdIndexer(4)
    tw.ar_out_valid = qarw_valid && !qa.wen; tw.aw_out_valid = qarw_valid && qa.wen; tw.ar_out = ax; tw.aw_out = ax;
    tw.w_out_valid = qw_valid; tw.w_out = qw;
    // yanker
    const unsigned yid = ax.id & 15;
    const bool ar_ready_y = mb_rq[yid].enq_ready(), aw_ready_y = mb_wq[yid].enq_ready();
    mem_in.ar_valid = tw.ar_out_valid && ar_ready_y; mem_in.ar = ax;
    mem_in.aw_valid = tw.aw_out_valid && aw_ready_y; mem_in.aw = ax;
    mem_in.w_valid = tw.w_out_valid; mem_in.w = qw;
    axi_mem_eval(mem, mem_in, w.mem, mem_o, 0x1FFFFFF, 0x80000000u, 0x10000000u, dram_);
    const bool out_ar_ready = mem_o.ar_ready, out_aw_ready = mem_o.aw_ready;
    const bool in_ar_ready = out_ar_ready && ar_ready_y, in_aw_ready = out_aw_ready && aw_ready_y;
    w.mb_rq_enq[yid] = tw.ar_out_valid && out_ar_ready && ar_ready_y; w.mb_rq_bits = YankEcho{ax.echo_size, ax.echo_source, ax.echo_extra};
    w.mb_wq_enq[yid] = tw.aw_out_valid && out_aw_ready && aw_ready_y; w.mb_wq_bits = w.mb_rq_bits;
    tw.q_arw_deq_fire = qarw_valid && (qa.wen ? in_aw_ready : in_ar_ready);
    tw.q_w_deq_fire = qw_valid && mem_o.w_ready;
    // yanker deq on the last beat of the response
    const unsigned rid = w.mem.r_up.id & 15, bid = w.mem.b_up.id & 15;
    if (w.mem.r_up_fire && w.mem.r_up.last) w.mb_rq_deq[rid] = true;
    if (w.mem.b_up_fire) w.mb_wq_deq[bid] = true;
    // hub side ready
    w.l2a_sink_ready = a_ready;
    w.l2a_sink_fire = tw.a_fire;
  }
  // now the l2 C readies and the out.a / in.d arbiter decisions
  {
    const uint32_t allowed_a = l2_a_arb.allowed(w.l2a_valids);
    const bool putfull_ready = w.l2a_sink_ready && (allowed_a & 1);
    for (unsigned t = 0; t < 4; ++t) w.trk_odata_deq[t] = ((w.l2a_valids >> (t + 1)) & 1) && w.l2a_sink_ready && ((allowed_a >> (t + 1)) & 1);
    const bool c_valid = w.l2_c_valid; const TlC& c = w.l2_c;
    const bool c_probeack = c.opcode == C_ProbeAck, c_probeackdata = c.opcode == C_ProbeAckData, c_release = c.opcode == C_Release;
    const bool c_ready = c_probeack || (c_release ? l2_ra_ready : putfull_ready);
    w.l2_c_fire = c_valid && c_ready;
    w.tb_c_deq_fire = w.l2_c_fire;
    uint32_t c_oh = 0; for (unsigned t = 0; t < 4; ++t) if ((trk[t].address >> 6) == (c.address >> 6)) c_oh |= 1u << t;
    const bool whoC = c.source == kTileSourceBase;
    const bool CisN = c.param == P_TtoN || c.param == P_BtoN || c.param == P_NtoN;
    const uint8_t clearOH = (w.l2_c_fire && (c_probeack || c_probeackdata) && CisN) ? (whoC ? 1 : 0) : 0;
    for (unsigned t = 0; t < 4; ++t) {
      const bool sel = (c_oh >> t) & 1;
      w.trk_clearOH[t] = sel ? clearOH : 0;
      w.trk_probenack[t] = w.l2_c_fire && c_probeack && sel;
      w.trk_probesack[t] = w.l2_c_fire && sel && (c_probeack || c_probeackdata) && (c.param == P_TtoB || c.param == P_BtoB);
    }
  }

  // ---------------------------------------------------------------- mmio path: TLToAXI4 (sbus) -> IdIndexer -> Deinterleaver -> UserYanker -> AXI4Buffer -> mmio_mem
  bool mmio_a_ready = false;
  {
    ToAxi4& t = mm_axi; ToAxiWires& tw = w.mm;
    tw.a_valid = sb_a_out_valid[kMmio]; tw.a = w.sb_a_out[kMmio];
    const TlA& a = tw.a;
    tw.a_first = t.a_cnt.first();
    const uint32_t b1 = beats1(a.size, a_has_data(a.opcode), 8);
    tw.a_last = t.a_cnt.last(b1);
    tw.is_put = a_has_data(a.opcode);
    // sourceTable: icache(18)->0, fbus 0..7->1, 8..15->2, dcache 16->3, 17->4
    const uint8_t id = a.source == 18 ? 0 : a.source < 8 ? 1 : a.source < 16 ? 2 : a.source == 16 ? 3 : 4;
    tw.a_id = id;
    const unsigned maxCount = (id == 1 || id == 2) ? 8 : 1;
    const bool idle = t.count[id] == 0;
    const bool mismatch = maxCount > 1 && t.write[id] != tw.is_put;
    tw.stall = ((!idle && mismatch) || t.count[id] == maxCount) && tw.a_first;
    ToAxi4::Arw arw; arw.wen = tw.is_put;
    arw.a.id = id; arw.a.addr = a.address; arw.a.len = static_cast<uint8_t>(oh1(a.size, 11) >> 3); arw.a.size = a.size >= 3 ? 3 : a.size;
    arw.a.burst = 1; arw.a.prot = 1; arw.a.echo_size = a.size; arw.a.echo_source = a.source;
    tw.arw = arw;
    const bool arw_ready = t.q_arw.enq_ready(), w_ready = t.q_w.enq_ready();
    tw.arw_valid = !tw.stall && tw.a_valid && (tw.is_put ? (!t.doneAW && w_ready) : true);
    tw.w_valid = !tw.stall && tw.a_valid && tw.is_put && (t.doneAW || arw_ready);
    tw.w.data = a.data; tw.w.strb = a.mask; tw.w.last = tw.a_last; tw.w.corrupt = a.corrupt;
    const bool a_ready = !tw.stall && (tw.is_put ? ((t.doneAW || arw_ready) && w_ready) : arw_ready);
    tw.a_fire = tw.a_valid && a_ready; tw.arw_fire = tw.arw_valid && arw_ready; tw.w_fire = tw.w_valid && w_ready;
    mmio_a_ready = a_ready;
    const bool qarw_valid = t.q_arw.deq_valid(tw.arw_valid); const ToAxi4::Arw& qa = t.q_arw.deq_bits(tw.arw);
    const bool qw_valid = t.q_w.deq_valid(tw.w_valid); const AxiW& qw = t.q_w.deq_bits(tw.w);
    AxiA ax = qa.a;   // IdIndexer(4) with 5 ids: no extra bits
    tw.ar_out_valid = qarw_valid && !qa.wen; tw.aw_out_valid = qarw_valid && qa.wen; tw.ar_out = ax; tw.aw_out = ax;
    tw.w_out_valid = qw_valid; tw.w_out = qw;
    // deinterleaver passes ar/aw/w; yanker
    const unsigned yid = ax.id % 5;
    const bool ar_ready_y = mm_rq_big[yid].enq_ready(), aw_ready_y = mm_wq_big[yid].enq_ready();
    // AXI4Buffer (coupler) enq readies
    const bool buf_ar_ready = mm_buf_ar.enq_ready(), buf_aw_ready = mm_buf_aw.enq_ready(), buf_w_ready = mm_buf_w.enq_ready();
    const bool y_ar_valid = tw.ar_out_valid && ar_ready_y, y_aw_valid = tw.aw_out_valid && aw_ready_y;
    w.mmb_ar_enq = y_ar_valid && buf_ar_ready; w.mmb_ar_bits = ax;
    w.mmb_aw_enq = y_aw_valid && buf_aw_ready; w.mmb_aw_bits = ax;
    w.mmb_w_enq = tw.w_out_valid && buf_w_ready; w.mmb_w_bits = qw;
    w.mm_rq_enq[yid] = tw.ar_out_valid && buf_ar_ready && ar_ready_y; w.mm_rq_bits = YankEcho{ax.echo_size, ax.echo_source, 0};
    w.mm_wq_enq[yid] = tw.aw_out_valid && buf_aw_ready && aw_ready_y; w.mm_wq_bits = w.mm_rq_bits;
    const bool in_ar_ready = buf_ar_ready && ar_ready_y, in_aw_ready = buf_aw_ready && aw_ready_y;
    tw.q_arw_deq_fire = qarw_valid && (qa.wen ? in_aw_ready : in_ar_ready);
    tw.q_w_deq_fire = qw_valid && buf_w_ready;
    // buffer -> mmio_mem
    mm_in.ar_valid = !mm_buf_ar.empty(); mm_in.ar = mm_buf_ar.head();
    mm_in.aw_valid = !mm_buf_aw.empty(); mm_in.aw = mm_buf_aw.head();
    mm_in.w_valid = !mm_buf_w.empty(); mm_in.w = mm_buf_w.head();
    mm_in.b_ready = mm_buf_b.enq_ready(); mm_in.r_ready = mm_buf_r.enq_ready();
    axi_mem_eval(mmio, mm_in, w.mmio, mm_o, 0x1FF, 0x60000000u, 0x1000u, mmio_mem_);
    w.mmb_ar_deq = mm_in.ar_valid && mm_o.ar_ready; w.mmb_aw_deq = mm_in.aw_valid && mm_o.aw_ready; w.mmb_w_deq = mm_in.w_valid && mm_o.w_ready;
    w.mmb_b_enq = w.mmio.b_up_fire; w.mmb_r_enq = w.mmio.r_up_fire;
    // buffer b/r -> yanker -> deinterleaver (r) / tl2axi4 (b)
    const bool rb_valid = !mm_buf_r.empty(); const AxiR& rb = mm_buf_r.head();
    const unsigned enq_id = rb.id % 5;
    const bool deint_enq_ready = mm_deint_q[enq_id].enq_ready();
    w.mmb_r_deq = rb_valid && deint_enq_ready;
    w.mm_deint_q_enq[enq_id] = w.mmb_r_deq;
    if (w.mmb_r_deq && rb.last) w.mm_rq_deq[enq_id] = true;
    if (w.mmb_b_deq) w.mm_wq_deq[mm_buf_b.head().id % 5] = true;
    // deinterleaver pending/lock update
    for (unsigned i = 0; i < 5; ++i) {
      w.mm_deint_inc[i] = (enq_id == i) && w.mmb_r_deq && rb.last;
      w.mm_deint_dec[i] = (mm_deint_id == i) && w.mm_deint_in_r_fire && w.mm.r.last;
      const unsigned next = mm_deint_count[i] + (w.mm_deint_inc[i] ? 1 : 0) - (w.mm_deint_dec[i] ? 1 : 0);
      if (next != 0) w.mm_deint_pending |= 1u << i;
    }
  }

  // ---------------------------------------------------------------- system bus A readies
  {
    const bool sink_ready[3] = { cbus_a_ready, l2_a_ready, mmio_a_ready };
    for (unsigned o = 0; o < 3; ++o) {
      w.sb_a_ready[o] = sink_ready[o];
      w.sb_a_fire[o] = sb_a_out_valid[o] && sink_ready[o];
    }
    const unsigned o = w.tile_route;
    const bool tile_ready = w.sb_a_ready[o] && ((sb_a[o].allowed(w.sb_a_valids[o]) >> 1) & 1);
    w.tb_a_deq_fire = w.tile_a_valid && tile_ready;
  }
  evaluate_boundary(in, out);

  // ---------------------------------------------------------------- debug module / DMI
  eval_debug(in, out);

  // ---------------------------------------------------------------- interrupts
  out.int_debug = tile_debug_int_sync.out();
  out.int_msip = int_clint_reg[0]; out.int_mtip = int_clint_reg[1];
  out.int_meip = int_plic_reg[0]; out.int_seip = int_plic_reg[1];
  out.system_reset = in.reset || ldut_reset_reg;
  w.rtc_tick = rtc_div == 99;
  debug_comb_ = !dbg.dmactive_synced.out();
  evaluated_ = true;
  transport_output_ = out;
  (void)reset;
}

void Uncore::evaluate_boundary(const UncoreIn& in, UncoreOut& out) {
  auto& w = *w_;
  w.tx_valids = (in.dc_a_valid ? 1u : 0) | (in.ic_a_valid ? 2u : 0);
  w.tx_sink_ready = tb_a.enq_ready();
  const uint32_t win = tile_arb.winner(w.tx_valids);
  if (win & 1) w.tx_a = in.dc_a;
  else if (win & 2) { w.tx_a = in.ic_a; w.tx_a.source = static_cast<uint16_t>(in.ic_a.source + 2); }
  else w.tx_a = TlA{};
  w.tx_beats1 = win ? beats1(w.tx_a.size, a_has_data(w.tx_a.opcode), kSbusMaxLg) : 0;
  w.tx_sink_fire = tile_arb.sink_valid(w.tx_valids) && w.tx_sink_ready;
  const uint32_t allowed = tile_arb.allowed(w.tx_valids);
  out.dc_a_ready = w.tx_sink_ready && (allowed & 1);
  out.ic_a_ready = w.tx_sink_ready && ((allowed >> 1) & 1);
  out.dc_c_ready = tb_c.enq_ready(); w.tb_c_enq_fire = in.dc_c_valid && out.dc_c_ready;
  out.dc_e_ready = tb_e.enq_ready(); w.tb_e_enq_fire = in.dc_e_valid && out.dc_e_ready;
  const bool d_valid = !tb_d.empty(); const TlD& d = tb_d.head();
  const bool to_dc = d.source < 2;
  out.dc_d_valid = d_valid && to_dc; out.dc_d = d; out.dc_d.source = static_cast<uint16_t>(d.source & 1);
  out.ic_d_valid = d_valid && !to_dc; out.ic_d = d; out.ic_d.source = 0;
  w.tb_d_deq_fire = d_valid && (to_dc ? in.dc_d_ready : in.ic_d_ready);
  out.dc_b_valid = !tb_b.empty(); out.dc_b = tb_b.head();
  w.tb_b_deq_fire = out.dc_b_valid && in.dc_b_ready;
}


namespace {
void toaxi_commit(ToAxi4& model, const ToAxiWires& w, bool mmio) {
  // Only the selected ID(s) can change; avoid scanning 128 inactive counters.
  const unsigned aid = w.arw.a.id;
  const unsigned did = w.d_id;
  auto update = [&](unsigned id, bool inc, bool dec) {
    const unsigned mask = mmio && (id == 1 || id == 2) ? 15 : 1;
    model.count[id] = static_cast<uint16_t>((model.count[id] + inc - dec) & mask);
    if (inc) model.write[id] = w.arw.wen;
  };
  const bool inc = w.arw_fire;
  const bool dec = w.d_fire && w.d_last;
  if (inc && dec && aid == did) update(aid, true, true);
  else {
    if (inc) update(aid, true, false);
    if (dec) update(did, false, true);
  }
  if (model.r_first) model.r_denied_hold = w.r.resp == kAxiDecErr;
  if (w.r_fire) { model.r_holds_d = !w.r.last; model.r_first = w.r.last; }
  model.b_delay = static_cast<uint8_t>(w.b_valid && !w.b_fire ? (model.b_delay + 1) & 7 : 0);
  if (w.a_fire) model.doneAW = !w.a_last;
  model.a_cnt.step(w.a_fire, beats1(w.a.size, a_has_data(w.a.opcode), mmio ? 8 : 6));
  model.q_arw.step(w.arw_fire, w.arw, w.q_arw_deq_fire);
  model.q_w.step(w.w_fire, w.w, w.q_w_deq_fire);
}
void reset_toaxi(ToAxi4& t) {
  t.q_arw.reset(); t.q_w.reset();
  t.doneAW = t.r_holds_d = false; t.r_first = true;
  t.a_cnt.counter = 0;
  for (auto& count : t.count) count = 0;
}
void reset_axi_mem(AxiMem& m) {
  m.q_ar.reset(); m.q_aw.reset(); m.q_w.reset();
  m.b_aw.reset(); m.b_ar.reset(); m.b_w.reset(); m.b_b.reset(); m.b_r.reset();
  m.ar_busy = m.aw_busy = m.wbeats_latched = false;
  m.w_counter = 0; m.w_full = m.r_full = false;
  for (auto& error : m.error) error = 0;
}
void reset_fragmenter(Fragmenter& f) { f.acknum = f.gennum = 0; f.dToggle = f.rep_full = false; }
}

void commit_datapath(Uncore& u, const UncoreIn& in) {
  auto& w = *u.w_;
  const bool reset = in.reset || u.ldut_reset_reg;
  // Capture device/back-queue data before any queue writes this edge.
  const RegMapperReq plic_request = u.plic_back.head();
  uint8_t next_maxdev[2], next_max_priority[2];
  const TlA error_request = u.cb_err.buf_a.head();
  const TlD atomic_response = u.cb_d.head();

  // Registered interrupt crossings see PRE device outputs.
  u.int_clint_reg[0] = !reset && u.clint_ipi;
  u.int_clint_reg[1] = !reset && u.clint_time >= u.clint_timecmp;
  for (unsigned hart = 0; hart < 2; ++hart) {
    u.int_plic_reg[hart] = !reset && u.plic_max_priority[hart] > u.plic_threshold[hart];
    unsigned priority = 0, device = 0;
    for (unsigned source = 0; source < 2; ++source) {
      const unsigned p = (u.plic_pending[source] && ((u.plic_enable[hart] >> source) & 1)) ? u.plic_priority[source] : 0;
      if (p > priority) { priority = p; device = source + 1; }
    }
    next_maxdev[hart] = static_cast<uint8_t>(device);
    next_max_priority[hart] = static_cast<uint8_t>(priority);
  }
  // TestHarness drives the two external PLIC interrupt inputs low. Pending
  // bits can be cleared by a real claim, and the retained priority/enables
  // still obey their MMIO register map; no synthetic interrupts are injected.
  if (w.plic_out_fire) u.plic_back_effects(plic_request);
  for (unsigned hart = 0; hart < 2; ++hart) {
    u.plic_maxdev[hart] = next_maxdev[hart];
    u.plic_max_priority[hart] = next_max_priority[hart];
  }
  u.plic_back.step(w.plic_in_fire, w.plic_req, w.plic_out_fire);
  if (w.rtc_tick) ++u.clint_time;
  u.rtc_div = static_cast<uint8_t>(w.rtc_tick ? 0 : u.rtc_div + 1);
  if (w.clint_write) {
    const unsigned index = w.clint_index & 0x1fff;
    if (index == 0 && (w.clint_mask & 1)) u.clint_ipi = w.clint_wdata & 1;
    if (index == 0x800) u.clint_timecmp = byte_merge(u.clint_timecmp, w.clint_wdata, w.clint_mask);
    if (index == 0x17ff) u.clint_time = byte_merge(u.clint_time, w.clint_wdata, w.clint_mask);
  }
  if (!u.transport_evaluated_) return;

  u.tile_arb.step(w.tx_valids, w.tx_sink_ready, w.tx_sink_fire, w.tx_beats1);
  u.tb_a.step(w.tx_sink_fire, w.tx_a, w.tb_a_deq_fire);
  u.tb_b.step(w.tb_b_enq_fire, w.tb_b_enq, w.tb_b_deq_fire);
  u.tb_c.step(w.tb_c_enq_fire, in.dc_c, w.tb_c_deq_fire);
  u.tb_d.step(w.tb_d_enq_fire, w.tb_d_enq, w.tb_d_deq_fire);
  u.tb_e.step(w.tb_e_enq_fire, in.dc_e, w.tb_e_deq_fire);
  for (unsigned i = 0; i < 3; ++i) u.sb_a[i].step(w.sb_a_valids[i], w.sb_a_ready[i], w.sb_a_fire[i], w.sb_a_beats1[i]);
  for (unsigned i = 0; i < 2; ++i) u.sb_d[i].step(w.sb_d_valids[i], w.sb_d_ready[i], w.sb_d_fire[i], w.sb_d_beats1[i]);

  auto& atomic = u.cb_atomics;
  atomic.arb.step(w.at_valids, w.at_sink_ready, w.at_sink_fire, w.at_beats1);
  if (w.at_source_i_fire && !w.at_supported) {
    atomic.cam_a = w.cb_a_in;
    atomic.cam_state = kGet;
  }
  if (w.at_source_c_fire) atomic.cam_state = kAck;
  if (w.at_d_fire && w.at_d_first && w.at_d_sel) {
    if (atomic_response.opcode == D_AccessAckData) {
      atomic.cam_d_data = atomic_response.data;
      atomic.cam_d_denied = atomic_response.denied;
      atomic.cam_d_corrupt = atomic_response.corrupt;
      atomic.cam_state = kAmo;
    } else atomic.cam_state = kFree;
  }
  atomic.d_first.step(w.at_d_fire, w.at_d_beats1);
  u.cb_fixer.step(w.cb_a_deq_fire, w.cb_a_head, false, cbus_fifo_domain(w.cb_a_head.address),
                  w.cb_d_enq_fire, w.cb_d_enq, reset);
  // TestHarness ties the AXI frontend request valids low. No transaction can
  // enter source IDs [0,16); the system-bus fixer is still clocked and reset.
  u.fbus.commit(reset, w.sb_d_valids[0] != 0);
  u.sb_fixer.step(false, TlA{}, false, 1, false, TlD{}, reset);
  u.cb_a.step(w.cb_a_enq_fire, w.at_out, w.cb_a_deq_fire);
  u.cb_d.step(w.cb_d_enq_fire, w.cb_d_enq, w.cb_d_deq_fire);
  u.cb_d_arb.step(w.cbd_valids, w.cbd_sink_ready, w.cbd_sink_fire, w.cbd_beats1);
  u.cb_err.buf_a.step(w.er_bufa_enq_fire, w.cb_a_head, w.er_bufa_deq_fire);
  u.cb_err.a.step(w.er_a_enq_fire, error_request, w.er_a_deq_fire);
  u.cb_err.a_last.step(w.er_a_deq_fire, w.er_a_beats1);
  u.cb_err.buf_d.step(w.er_bufd_enq_fire, w.er_d, w.er_bufd_deq_fire);
  Fragmenter* fragmenters[] = {&u.fr_plic, &u.fr_clint, &u.fr_debug, &u.fr_rom};
  for (unsigned i = 0; i < 4; ++i) frag_commit(*fragmenters[i], w.fr[i]);

  u.l2_a_cnt.step(w.l2_a_valid && w.l2_a_ready, beats1(w.l2_a.size, a_has_data(w.l2_a.opcode), 6));
  u.l2_d_cnt.step(w.l2_dnormal_fire, w.l2_dn_beats1);
  if (w.l2_d_first) u.d_trackerOH_hold = w.l2_trackerOH;
  if (w.l2_b_fire) u.probe_todo = false;
  if (w.l2_req_fire) {
    u.probe_todo = w.l2_todo;
    u.probe_line = w.l2_a.address >> 6;
    u.probe_perms = w.l2_needT ? P_toN : P_toB;
  }
  for (unsigned i = 0; i < 4; ++i) {
    auto& t = u.trk[i];
    const uint8_t old_count = t.count;
    if (w.trk_in_fire[i] && w.l2_a_first) {
      t.sent_d = t.shared = false;
      t.got_e = w.l2_a.opcode != A_AcquireBlock && w.l2_a.opcode != A_AcquirePerm;
      t.opcode = w.l2_a.opcode; t.param = w.l2_a.param; t.size = w.l2_a.size;
      t.source = static_cast<uint8_t>(w.l2_a.source); t.address = w.l2_a.address;
      t.count = 1;
    }
    t.cacheOH &= ~w.trk_clearOH[i];
    if (w.trk_probe_valid[i]) { t.count = w.l2_todo; t.cacheOH = 1; }
    if (w.trk_d_last[i]) t.sent_d = true;
    if (w.trk_e_last[i]) t.got_e = true;
    if (w.trk_probenack[i] || w.trk_probedack[i])
      t.count = static_cast<uint8_t>((old_count - w.trk_probenack[i] - w.trk_probedack[i]) & 1);
    if (w.trk_probesack[i]) t.shared = true;
    t.o_data.step(w.trk_odata_enq[i], Tracker::Beat{w.l2_a.mask, w.l2_a.data}, w.trk_odata_deq[i]);
  }
  u.l2_a_arb.step(w.l2a_valids, w.l2a_sink_ready, w.l2a_sink_fire, w.l2a_beats1);
  u.l2_d_arb.step(w.l2d_valids, w.l2d_sink_ready, w.l2d_sink_fire, w.l2d_beats1);
  toaxi_commit(u.mb_axi, w.mb, false);
  toaxi_commit(u.mm_axi, w.mm, true);
  for (unsigned i = 0; i < 16; ++i) {
    u.mb_rq[i].step(w.mb_rq_enq[i], w.mb_rq_bits, w.mb_rq_deq[i]);
    u.mb_wq[i].step(w.mb_wq_enq[i], w.mb_wq_bits, w.mb_wq_deq[i]);
  }
  for (unsigned i = 0; i < 5; ++i) {
    u.mm_rq_big[i].step(w.mm_rq_enq[i], w.mm_rq_bits, w.mm_rq_deq[i]);
    u.mm_wq_big[i].step(w.mm_wq_enq[i], w.mm_wq_bits, w.mm_wq_deq[i]);
    u.mm_deint_q[i].step(w.mm_deint_q_enq[i], w.mm_deint_enq_bits, w.mm_deint_q_deq[i]);
    u.mm_deint_count[i] = static_cast<uint8_t>((u.mm_deint_count[i] + w.mm_deint_inc[i] - w.mm_deint_dec[i]) & 15);
  }
  if (!u.mm_deint_locked || (w.mm_deint_in_r_fire && w.mm.r.last)) {
    u.mm_deint_locked = w.mm_deint_pending != 0;
    u.mm_deint_id = w.mm_deint_pending ? static_cast<uint8_t>(lowest_bit(w.mm_deint_pending)) : 0;
  }
  u.mm_buf_aw.step(w.mmb_aw_enq, w.mmb_aw_bits, w.mmb_aw_deq);
  u.mm_buf_ar.step(w.mmb_ar_enq, w.mmb_ar_bits, w.mmb_ar_deq);
  u.mm_buf_w.step(w.mmb_w_enq, w.mmb_w_bits, w.mmb_w_deq);
  u.mm_buf_b.step(w.mmb_b_enq, w.mmb_b_bits, w.mmb_b_deq);
  u.mm_buf_r.step(w.mmb_r_enq, w.mmb_r_bits, w.mmb_r_deq);
  axi_mem_commit(u.mem, w.mem, u.dram_);
  axi_mem_commit(u.mmio, w.mmio, u.mmio_mem_);

  if (reset) {
    u.tile_arb = RrArbiter<2>{};
    u.tb_a.reset(); u.tb_b.reset(); u.tb_c.reset(); u.tb_d.reset(); u.tb_e.reset();
    for (auto& a : u.sb_a) a = RrArbiter<2>{};
    for (auto& d : u.sb_d) d = RrArbiter<3>{};
    u.cb_a.reset(); u.cb_d.reset(); u.cb_d_arb = RrArbiter<5>{};
    atomic.arb = LowArbiter<2>{}; atomic.d_first.counter = 0; atomic.cam_state = kFree;
    u.cb_err.buf_a.reset(); u.cb_err.buf_d.reset(); u.cb_err.a.reset(); u.cb_err.a_last.counter = 0;
    for (auto* f : fragmenters) reset_fragmenter(*f);
    u.plic_back.reset(); u.clint_time = 0; u.clint_ipi = false; u.rtc_div = 0;
    for (unsigned i = 0; i < 2; ++i) { u.plic_pending[i] = false; u.plic_gateway_inflight[i] = false; }
    u.probe_todo = false; u.l2_a_cnt.counter = u.l2_d_cnt.counter = 0;
    u.l2_a_arb = LowArbiter<5>{}; u.l2_d_arb = LowArbiter<2>{};
    for (unsigned i = 0; i < 4; ++i) { u.trk[i].got_e = u.trk[i].sent_d = true; u.trk[i].address = i << 6; u.trk[i].o_data.reset(); }
    reset_toaxi(u.mb_axi); reset_toaxi(u.mm_axi);
    for (unsigned i = 0; i < 16; ++i) { u.mb_rq[i].reset(); u.mb_wq[i].reset(); }
    for (unsigned i = 0; i < 5; ++i) { u.mm_rq_big[i].reset(); u.mm_wq_big[i].reset(); u.mm_deint_q[i].reset(); u.mm_deint_count[i] = 0; }
    u.mm_deint_locked = false;
    u.mm_buf_aw.reset(); u.mm_buf_ar.reset(); u.mm_buf_w.reset(); u.mm_buf_b.reset(); u.mm_buf_r.reset();
  }
  // SimAXIMem sits in TestHarness: ndmreset resets the DUT, not its external memories.
  if (in.reset) { reset_axi_mem(u.mem); reset_axi_mem(u.mmio); }
}

void Uncore::commit() {
  if (!evaluated_) throw std::logic_error("uncore commit without a final evaluate");
  commit_datapath(*this, captured_input_);
  commit_debug(captured_input_);
  if (transport_evaluated_)
    can_skip_transport_ = !captured_input_.reset && !captured_input_.dc_a_valid &&
      !captured_input_.ic_a_valid && !captured_input_.dc_c_valid && !captured_input_.dc_e_valid &&
      !transport_output_.dc_b_valid && !transport_output_.dc_d_valid && !transport_output_.ic_d_valid &&
      quiescent_transport();
  evaluated_ = false;
}
void Uncore::commit(const UncoreIn&) { commit(); }

bool Uncore::quiescent_transport() const {
  auto quiet_arbiter = [](const auto& arb) { return arb.beats_left == 0 && arb.state == 0; };
  auto quiet_axi = [](const AxiMem& m) {
    return !m.ar_busy && !m.aw_busy && !m.wbeats_latched && m.w_counter == 0 &&
      !m.w_full && !m.r_full && !m.ren_prev && m.q_ar.empty() && m.q_aw.empty() && m.q_w.empty() &&
      m.b_aw.empty() && m.b_ar.empty() && m.b_w.empty() && m.b_b.empty() && m.b_r.empty();
  };
  if (!tb_a.empty() || !tb_b.empty() || !tb_c.empty() || !tb_d.empty() || !tb_e.empty() ||
      !cb_a.empty() || !cb_d.empty() || !plic_back.empty() || !cb_err.a.empty() ||
      !cb_err.buf_a.empty() || !cb_err.buf_d.empty() || cb_atomics.cam_state != kFree ||
      probe_todo || !quiet_arbiter(tile_arb) || !quiet_arbiter(cb_d_arb) ||
      !quiet_arbiter(cb_atomics.arb) || !quiet_arbiter(l2_a_arb) || !quiet_arbiter(l2_d_arb)) return false;
  for (const auto& arb : sb_a) if (!quiet_arbiter(arb)) return false;
  for (const auto& arb : sb_d) if (!quiet_arbiter(arb)) return false;
  for (const auto& t : trk) if (!t.got_e || !t.sent_d || !t.o_data.empty() || t.count) return false;
  for (const auto* f : {&fr_plic, &fr_clint, &fr_debug, &fr_rom})
    if (f->rep_full || f->acknum || f->gennum) return false;
  for (const auto* a : {&mb_axi, &mm_axi}) {
    if (!a->q_arw.empty() || !a->q_w.empty() || a->doneAW || a->r_holds_d || a->b_delay || a->a_cnt.counter) return false;
    for (auto count : a->count) if (count) return false;
  }
  for (unsigned i = 0; i < 16; ++i) if (!mb_rq[i].empty() || !mb_wq[i].empty()) return false;
  for (unsigned i = 0; i < 5; ++i)
    if (!mm_rq_big[i].empty() || !mm_wq_big[i].empty() || !mm_deint_q[i].empty() || mm_deint_count[i]) return false;
  return !mm_deint_locked && mm_buf_aw.empty() && mm_buf_ar.empty() && mm_buf_w.empty() &&
      mm_buf_b.empty() && mm_buf_r.empty() && quiet_axi(mem) && quiet_axi(mmio);
}

}  // namespace chisa::rocket_model::uncore
