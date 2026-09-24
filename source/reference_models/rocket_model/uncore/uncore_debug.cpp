// rocket_model uncore: debug module (DMI transport, outer/inner halves, clock
// gating), PLIC and CLINT register semantics.
#include <cstring>

#include "uncore/uncore.h"
#include "uncore/uncore_wires.h"

namespace chisa::rocket_model::uncore {

namespace {

constexpr unsigned kDmiDmcontrol = 0x10, kDmiDmstatus = 0x11, kDmiHartinfo = 0x12, kDmiHaltsum1 = 0x13, kDmiHawindowsel = 0x14, kDmiHawindow = 0x15;
constexpr unsigned kDmiAbstractcs = 0x16, kDmiCommand = 0x17, kDmiAbstractauto = 0x18, kDmiData0 = 0x04, kDmiProgbuf0 = 0x20, kDmiHaltsum0 = 0x40;
constexpr uint8_t kStWaiting = 0, kStCheckGenerate = 1, kStExec = 2;
constexpr uint32_t kEbreak = 0x00100073, kNop = 0x00000013;
constexpr uint32_t kDebugRomBytes = 84;
constexpr uint8_t kDebugRom[kDebugRomBytes] = {
  0x6f, 0x00, 0xc0, 0x00, 0x6f, 0x00, 0x80, 0x03, 0x6f, 0x00, 0x40, 0x04,
  0x0f, 0x00, 0xf0, 0x0f, 0x73, 0x10, 0x24, 0x7b, 0x73, 0x24, 0x40, 0xf1,
  0x23, 0x20, 0x80, 0x10, 0x03, 0x44, 0x04, 0x40, 0x13, 0x74, 0x34, 0x00,
  0xe3, 0x08, 0x04, 0xfe, 0x13, 0x74, 0x14, 0x00, 0x63, 0x08, 0x04, 0x00,
  0x73, 0x24, 0x20, 0x7b, 0x23, 0x22, 0x00, 0x10, 0x67, 0x00, 0x00, 0x30,
  0x73, 0x24, 0x40, 0xf1, 0x23, 0x24, 0x80, 0x10, 0x73, 0x24, 0x20, 0x7b,
  0x73, 0x00, 0x20, 0x7b, 0x23, 0x26, 0x00, 0x10, 0x73, 0x00, 0x10, 0x00 };

// TileLink A bundle of the DMI crossing as the hardware concatenates it (55 bits).
inline uint64_t pack_dmi_a(const TlA& a) {
  return (static_cast<uint64_t>(a.opcode & 7) << 52) | (static_cast<uint64_t>(a.param & 7) << 49) | (static_cast<uint64_t>(a.size & 3) << 47) |
         (static_cast<uint64_t>(a.source & 1) << 46) | (static_cast<uint64_t>(a.address & 0x1FF) << 37) | (static_cast<uint64_t>(a.mask & 0xF) << 33) |
         (static_cast<uint64_t>(a.data & 0xFFFFFFFFu) << 1) | (a.corrupt ? 1 : 0);
}
inline TlA unpack_dmi_a(uint64_t v) {
  TlA a; a.opcode = (v >> 52) & 7; a.param = (v >> 49) & 7; a.size = (v >> 47) & 3; a.source = (v >> 46) & 1; a.address = (v >> 37) & 0x1FF;
  a.mask = (v >> 33) & 0xF; a.data = (v >> 1) & 0xFFFFFFFFu; a.corrupt = v & 1; return a;
}
inline uint64_t pack_dmi_d(const TlD& d) {
  return (static_cast<uint64_t>(d.opcode & 7) << 44) | (static_cast<uint64_t>(d.param & 3) << 42) | (static_cast<uint64_t>(d.size & 3) << 40) |
         (static_cast<uint64_t>(d.source & 1) << 39) | (static_cast<uint64_t>(d.sink & 1) << 38) | ((d.denied ? 1ull : 0) << 37) |
         (static_cast<uint64_t>(d.data & 0xFFFFFFFFu) << 1) | (d.corrupt ? 1 : 0);
}
inline TlD unpack_dmi_d(uint64_t v) {
  TlD d; d.opcode = (v >> 44) & 7; d.param = (v >> 42) & 3; d.size = (v >> 40) & 3; d.source = (v >> 39) & 1; d.sink = (v >> 38) & 1;
  d.denied = (v >> 37) & 1; d.data = (v >> 1) & 0xFFFFFFFFu; d.corrupt = v & 1; return d;
}

// AsyncQueue (depth 1) handshakes.  The next values are computed from the current registers.
struct SourceEval { bool sink_ready, enq_ready, fire, widx_next, ready_next; };
inline SourceEval source_eval(const AsyncSource& s, bool enq_valid) {
  SourceEval e;
  e.sink_ready = s.sink_valid.out();
  e.enq_ready = s.ready_reg && e.sink_ready;
  e.fire = enq_valid && e.enq_ready;
  e.widx_next = e.sink_ready ? (s.widx_bin ^ e.fire) : false;
  e.ready_next = e.sink_ready && (e.widx_next != (s.ridx_sync.out() ^ true));
  return e;
}
struct SinkEval { bool source_ready, deq_valid, fire, ridx_next, valid_next; };
inline SinkEval sink_eval(const AsyncSink& k, bool deq_ready) {
  SinkEval e;
  e.source_ready = k.source_valid.out();
  e.deq_valid = k.valid_reg && e.source_ready;
  e.fire = e.deq_valid && deq_ready;
  e.ridx_next = e.source_ready ? (k.ridx_bin ^ e.fire) : false;
  e.valid_next = e.source_ready && (e.ridx_next != k.widx_sync.out());
  return e;
}
// Register updates.  `rst_src` resets the source's own registers, `rst_both` the shared-reset synchronizers.
inline void source_commit(AsyncSource& s, const SourceEval& e, uint64_t bits, uint8_t bits_hi, const AsyncSink& k_old, bool rst_src, bool rst_both) {
  const bool sv0 = s.source_valid_0.out(), se = s.sink_extend.out();
  if (e.fire) { s.mem = bits; s.mem_hi = bits_hi; }
  s.widx_bin = e.widx_next; s.widx_reg = e.widx_next; s.ready_reg = e.ready_next;
  if (rst_src) { s.widx_bin = s.widx_reg = s.ready_reg = false; }
  s.ridx_sync.step(k_old.ridx_reg, rst_src, false);
  s.source_valid_0.step(true, rst_both, false);
  s.source_valid_1.step(sv0, rst_both, false);
  s.sink_extend.step(k_old.sink_valid_1.out(), rst_both, false);
  s.sink_valid.step(se, rst_src, false);
}
inline void sink_commit(AsyncSink& k, const SinkEval& e, const AsyncSource& s_old, bool rst_sink, bool rst_both) {
  const bool kv0 = k.sink_valid_0.out(), sx = k.source_extend.out();
  if (e.valid_next) { k.deq_reg = s_old.mem; k.deq_reg_hi = s_old.mem_hi; }
  k.ridx_bin = e.ridx_next; k.ridx_reg = e.ridx_next; k.valid_reg = e.valid_next;
  if (rst_sink) { k.ridx_bin = k.ridx_reg = k.valid_reg = false; }
  k.widx_sync.step(s_old.widx_reg, rst_sink, false);
  k.sink_valid_0.step(true, rst_both, false);
  k.sink_valid_1.step(kv0, rst_both, false);
  k.source_extend.step(s_old.source_valid_1.out(), rst_both, false);
  k.source_valid.step(sx, rst_sink, false);
}

}  // namespace

// ---- debug TL register map (word reads; the core's view at 0x0..0xFFF, 8-byte words) ----
uint64_t Uncore::debug_tl_read(uint32_t index) const {
  const DebugModule& d = dbg;
  const uint32_t byte = index << 3;
  if (byte == 0x100 || byte == 0x108) return 0;                     // HALTED/GOING/RESUMING/EXCEPTION are write-only notifies
  if (byte == 0x300) return 0x0380006F;                              // WHERETO: jal x0, +0x38 (ABSTRACT - WHERETO)
  if (byte == 0x338) return static_cast<uint64_t>(d.abstract_gen[0]) | (static_cast<uint64_t>(d.abstract_gen[1]) << 32);
  if (byte >= 0x340 && byte < 0x380) { uint64_t v = 0; std::memcpy(&v, d.progbuf + (byte - 0x340), 8); return v; }
  if (byte == 0x380) { uint64_t v = 0; std::memcpy(&v, d.data_mem, 8); return v; }
  if (byte >= 0x400 && byte < 0x800) { const uint8_t f = static_cast<uint8_t>((d.goReg ? 1 : 0) | (d.resumeReq ? 2 : 0)); uint64_t v = 0; for (unsigned i = 0; i < 8; ++i) v |= static_cast<uint64_t>(f) << (8 * i); return v; }
  if (byte >= 0x800 && byte < 0x800 + 88) { uint64_t v = 0; for (unsigned i = 0; i < 8; ++i) { const uint32_t o = byte - 0x800 + i; if (o < kDebugRomBytes) v |= static_cast<uint64_t>(kDebugRom[o]) << (8 * i); } return v; }
  return 0;
}

// ---- PLIC register map (8-byte words; nDevices = 2, nHarts = 2, 2 priority bits) ----
uint64_t Uncore::plic_read(uint32_t index, bool read) const {
  (void)read;
  const uint32_t byte = index << 3;
  if (byte == 0x0) return static_cast<uint64_t>(plic_priority[0] & 3) << 32;                      // priority 1 at 0x4
  if (byte == 0x8) return plic_priority[1] & 3;                                                   // priority 2 at 0x8
  if (byte == 0x1000) return (plic_pending[0] ? 2 : 0) | (plic_pending[1] ? 4 : 0);
  if (byte == 0x2000) return (plic_enable[0] & 3) << 1;
  if (byte == 0x2080) return (plic_enable[1] & 3) << 1;
  if (byte == 0x200000) return (plic_threshold[0] & 3) | (static_cast<uint64_t>(plic_maxdev[0] & 3) << 32);
  if (byte == 0x201000) return (plic_threshold[1] & 3) | (static_cast<uint64_t>(plic_maxdev[1] & 3) << 32);
  return 0;
}
void Uncore::plic_back_effects(const RegMapperReq& r) {
  const uint32_t byte = r.index << 3;
  if (r.read) {
    // claim: reading the claim/complete word of a hart clears the pending bit of its max device
    if (byte == 0x200000 || byte == 0x201000) {
      const unsigned hart = byte == 0x200000 ? 0 : 1;
      if ((r.mask >> 4) & 0xF) { const unsigned dev = plic_maxdev[hart] & 3; if (dev >= 1 && dev <= 2) plic_pending[dev - 1] = false; }
    }
    return;
  }
  auto wbyte = [&](unsigned b) { return (r.mask >> b) & 1; };
  if (byte == 0x0 && wbyte(4)) plic_priority[0] = static_cast<uint8_t>((r.data >> 32) & 3);
  if (byte == 0x8 && wbyte(0)) plic_priority[1] = static_cast<uint8_t>(r.data & 3);
  if (byte == 0x2000 && wbyte(0)) plic_enable[0] = static_cast<uint8_t>((r.data >> 1) & 3);
  if (byte == 0x2080 && wbyte(0)) plic_enable[1] = static_cast<uint8_t>((r.data >> 1) & 3);
  if ((byte == 0x200000 || byte == 0x201000)) {
    const unsigned hart = byte == 0x200000 ? 0 : 1;
    if (wbyte(0)) plic_threshold[hart] = static_cast<uint8_t>(r.data & 3);
    if (wbyte(4)) { const unsigned dev = (r.data >> 32) & 3; if (dev >= 1 && dev <= 2 && ((plic_enable[hart] >> (dev - 1)) & 1)) plic_gateway_inflight[dev - 1] = false; }
  }
}

// ============================================================================
// debug module evaluate
// ============================================================================
void Uncore::eval_debug(const UncoreIn& in, UncoreOut& out) {
  Wires& w = *w_;
  DebugModule& d = dbg;
  const bool dmi_reset = in.reset;
  const bool debug_reset = dmi_reset || !d.debug_reset_sync.out();
  w.debug_clk = d.clock_en;
  const bool dmactiveAck_ok = d.dmactiveAckSync.out();

  // ---- DMI request -> TileLink A ----
  TlA a; a.opcode = in.dmi_req_op == 2 ? A_PutFullData : A_Get; a.param = 0; a.size = 2; a.source = 0;
  a.address = in.dmi_req_op == 0 ? (kDmiHartinfo << 2) : (static_cast<uint32_t>(in.dmi_req_addr) << 2);
  a.mask = 0xF; a.data = in.dmi_req_op == 0 ? 0 : in.dmi_req_data; a.corrupt = false;
  w.dmi_a = a; w.dmi_a_valid = in.dmi_req_valid;
  const unsigned idx = a.address >> 2;
  w.dmi_to_outer = idx == kDmiDmcontrol || idx == kDmiHartinfo || idx == kDmiHawindowsel || idx == kDmiHawindow;

  // ---- dmOuter register map (combinational) ----
  uint32_t outer_rdata = 0;
  if (idx == kDmiDmcontrol) outer_rdata = ((d.dmactive && dmactiveAck_ok) ? 1u : 0) | (d.ndmreset ? 2u : 0) | (d.haltreq ? 0x80000000u : 0);
  else if (idx == kDmiHartinfo) outer_rdata = 0x00112380u;
  const bool outer_a_valid = w.dmi_a_valid && w.dmi_to_outer;
  TlD outer_d = TlD{}; outer_d.opcode = a.opcode == A_Get ? D_AccessAckData : D_AccessAck; outer_d.size = 2; outer_d.source = 0; outer_d.data = outer_rdata;

  // ---- bypass bar + error device + async source (A) / sink (D) ----
  const bool io_bypass = !d.dmactive || !dmactiveAck_ok;
  w.bypass = d.bar_in_reset ? io_bypass : d.bar_bypass_reg;
  const bool bar_a_first = d.bar_a_cnt.first();
  w.bar_stall = (w.bypass != io_bypass) && bar_a_first;
  const bool bar_in_valid = w.dmi_a_valid && !w.dmi_to_outer;
  // error device (out0)
  const bool err_a_valid = !w.bar_stall && bar_in_valid && w.bypass;
  TlD err_d; err_d.opcode = a.opcode == A_Get ? D_AccessAckData : D_AccessAck; err_d.param = 0; err_d.size = a.size; err_d.source = a.source; err_d.sink = 0;
  err_d.denied = true; err_d.data = 0; err_d.corrupt = d_has_data(err_d.opcode);
  const bool err_da_valid = err_a_valid && d.err_idle;
  w.errd_valids = err_da_valid ? 2u : 0;   // [dc, da]
  const bool err_d_valid = d.err_d.sink_valid(w.errd_valids);
  // async source (out1)
  const bool as_in_valid = !w.bar_stall && bar_in_valid && !w.bypass;
  const SourceEval as = source_eval(d.a_source, as_in_valid);
  // D back from the sink
  const AsyncSink& ds = d.d_sink;
  const bool ds_source_ready = ds.source_valid.out();
  const bool ds_deq_valid = ds.valid_reg && ds_source_ready;
  const TlD ds_d = unpack_dmi_d(ds.deq_reg);
  // bar in.d
  const bool bar_d_valid = w.bypass ? err_d_valid : ds_deq_valid;
  const TlD bar_d = w.bypass ? err_d : ds_d;

  // ---- dmiXbar in.d arbiter: [bypass bar, dmOuter] ----
  w.dx_valids = (bar_d_valid ? 1u : 0) | (outer_a_valid ? 2u : 0);
  const uint32_t win = d.dmiXbar_d.winner(w.dx_valids);
  w.dx_d = (win & 1) ? bar_d : (win & 2) ? outer_d : TlD{};
  w.dx_sink_ready = in.dmi_resp_ready;
  const bool dx_sink_valid = d.dmiXbar_d.sink_valid(w.dx_valids);
  w.dx_sink_fire = dx_sink_valid && w.dx_sink_ready;
  const uint32_t allowed = d.dmiXbar_d.allowed(w.dx_valids);
  const bool bar_d_ready = w.dx_sink_ready && (allowed & 1);
  const bool outer_d_ready = w.dx_sink_ready && ((allowed >> 1) & 1);
  out.dmi_resp_valid = dx_sink_valid; out.dmi_resp_data = static_cast<uint32_t>(w.dx_d.data);
  out.dmi_resp_resp = (w.dx_d.corrupt || w.dx_d.denied) ? 1 : 0;
  // readies back
  w.outer_fire = outer_a_valid && outer_d_ready; w.outer_read = a.opcode == A_Get; w.outer_wdata = static_cast<uint32_t>(a.data); w.outer_mask = a.mask; w.outer_index = idx;
  const bool err_d_ready = bar_d_ready && w.bypass;
  w.errd_sink_ready = err_d_ready; w.errd_sink_fire = err_d_valid && err_d_ready;
  const bool err_da_ready = err_d_ready && ((d.err_d.allowed(w.errd_valids) >> 1) & 1);
  const bool err_a_ready = err_da_ready && d.err_idle;   // (da.ready && da_last && idle) || !a_last, single beat
  w.err_a_fire = err_a_valid && err_a_ready;
  w.as_enq_fire = as.fire; w.as_bits = pack_dmi_a(a);
  const bool bar_a_ready = !w.bar_stall && (w.bypass ? err_a_ready : as.enq_ready);
  w.bar_a_fire = bar_in_valid && bar_a_ready;
  w.ds_deq_fire = ds_deq_valid && bar_d_ready && !w.bypass;
  w.bar_d_fire = bar_d_valid && bar_d_ready;
  {
    const bool inc = w.bar_a_fire && bar_a_first;
    const bool dec = w.bar_d_fire && d.bar_d_cnt.last(0);
    w.bar_flight_next = static_cast<uint8_t>((d.bar_flight + (inc ? 1 : 0) - (dec ? 1 : 0)) & 3);
  }
  const bool dmi_a_ready = w.dmi_to_outer ? outer_d_ready : bar_a_ready;
  out.dmi_req_ready = dmi_a_ready;
  w.dmi_a_fire = w.dmi_a_valid && dmi_a_ready;

  // ---- dmOuter write notifies ----
  const bool outer_write = w.outer_fire && !w.outer_read && idx == kDmiDmcontrol;
  const bool b0 = (a.mask & 1) != 0, b3 = (a.mask & 8) != 0;
  w.dmactiveWrEn = outer_write && b0; w.ndmresetWrEn = outer_write && b0; w.clrWrEn = outer_write && b0; w.setWrEn = outer_write && b0;
  w.ackWrEn = outer_write && b3; w.resumeWrEn = outer_write && b3; w.haltreqWrEn = outer_write && b3;
  const uint32_t wd = w.outer_wdata;
  // hrmask next (component 0 is always selected)
  bool hrmaskNxt = d.hrmaskReg;
  if (!d.dmactive) hrmaskNxt = false;
  else if (w.clrWrEn && ((wd >> 2) & 1)) hrmaskNxt = false;
  else if (w.setWrEn && ((wd >> 3) & 1)) hrmaskNxt = true;
  w.ic_hrmask = hrmaskNxt;
  const bool innerCtrlValid = w.resumeWrEn || w.ackWrEn || w.setWrEn || w.clrWrEn;
  w.innerCtrl_valid = innerCtrlValid || d.innerCtrlValidReg;
  w.ic_resumereq = (w.resumeWrEn && ((wd >> 30) & 1)) || d.innerCtrlResumeReqReg;
  w.ic_ackhavereset = (w.ackWrEn && ((wd >> 28) & 1)) || d.innerCtrlAckHaveResetReg;
  const SourceEval ics = source_eval(d.ic_source, w.innerCtrl_valid);
  w.innerCtrl_ready = ics.enq_ready;
  w.ics_enq_fire = ics.fire;
  w.ics_bits = (w.ic_resumereq ? 1u : 0) | (w.ic_ackhavereset ? 2u : 0) | (w.ic_hrmask ? 4u : 0);

  // ---- debug clock domain: a_sink -> dmInner DMI register map -> d_source; innerCtrl sink ----
  const AsyncSink& ak = d.a_sink;
  const bool ak_source_ready = ak.source_valid.out();
  const bool inner_a_valid = ak.valid_reg && ak_source_ready;
  const TlA ia = unpack_dmi_a(ak.deq_reg);
  const unsigned iidx = ia.address >> 2;
  // dmInner state views
  const bool dmactive_s = d.dmactive_synced.out();
  const bool hartHalted = d.haltedBit;
  const bool legal = d.ctrlState == kStWaiting;
  uint32_t inner_rdata = 0;
  {
    const bool resumeAcks = !d.resumeReq;   // (~resumeReqRegs & ~hamaskWrSel) when resumereq fires; handled in commit
    uint32_t st = 2u | (1u << 5) | (1u << 7);
    if (hartHalted) st |= (1u << 8) | (1u << 9); else st |= (1u << 10) | (1u << 11);
    if (resumeAcks) st |= (1u << 16) | (1u << 17);
    if (d.haveResetBit) st |= (1u << 18) | (1u << 19);
    if (iidx == kDmiDmstatus) inner_rdata = st;
    else if (iidx == kDmiHaltsum0) inner_rdata = hartHalted ? 1u : 0;
    else if (iidx == kDmiHaltsum1) inner_rdata = hartHalted ? 1u : 0;
    else if (iidx == kDmiAbstractcs) inner_rdata = 2u | (static_cast<uint32_t>(d.cmderr & 7) << 8) | ((legal ? 0u : 1u) << 12) | (16u << 24);
    else if (iidx == kDmiCommand) inner_rdata = d.command;
    else if (iidx == kDmiAbstractauto) inner_rdata = d.abstractauto;
    else if (iidx == kDmiData0 || iidx == kDmiData0 + 1) { uint32_t v = 0; std::memcpy(&v, d.data_mem + 4 * (iidx - kDmiData0), 4); inner_rdata = v; }
    else if (iidx >= kDmiProgbuf0 && iidx < kDmiProgbuf0 + 16) { uint32_t v = 0; std::memcpy(&v, d.progbuf + 4 * (iidx - kDmiProgbuf0), 4); inner_rdata = v; }
  }
  TlD inner_d; inner_d.opcode = ia.opcode == A_Get ? D_AccessAckData : D_AccessAck; inner_d.param = 0; inner_d.size = ia.size; inner_d.source = ia.source; inner_d.sink = 0;
  inner_d.denied = false; inner_d.data = inner_rdata; inner_d.corrupt = false;
  const SourceEval dsrc = source_eval(d.d_source, inner_a_valid);
  const bool inner_a_ready = dsrc.enq_ready;
  const SinkEval ak_e = sink_eval(ak, inner_a_ready);
  w.a_sink_deq_fire = ak_e.fire;
  w.inner_dmi_fire = ak_e.fire; w.inner_dmi_read = ia.opcode == A_Get; w.inner_index = iidx; w.inner_wdata = static_cast<uint32_t>(ia.data); w.inner_mask = ia.mask;
  w.d_source_enq_fire = dsrc.fire; w.d_source_bits = pack_dmi_d(inner_d);
  const SinkEval ds_e = sink_eval(ds, bar_d_ready && !w.bypass);
  const SinkEval ick = sink_eval(d.ic_sink, true);
  w.ic_sink_deq_fire = ick.fire;
  w.ic_fire = ick.fire;
  const uint32_t icbits = static_cast<uint32_t>(d.ic_sink.deq_reg);
  w.resumereq = ick.fire && (icbits & 1);
  w.ackhavereset_fire = ick.fire && (icbits & 2);
  (void)ds_e; (void)dmactive_s;

  // ---- dmInner: DMI-side write notifies and the abstract command state machine ----
  const bool iw = w.inner_dmi_fire && !w.inner_dmi_read;
  const bool ir = w.inner_dmi_fire && w.inner_dmi_read;
  const uint8_t im = w.inner_mask;
  bool csWrEnMaybe = false, cmdWrEnMaybe = false, autodataWrEnMaybe = false, autoprogWrEnMaybe = false;
  bool dataAccess = false, progAccess = false;
  uint32_t dataAccessVec = 0; uint64_t progAccessVec = 0;
  if (iidx == kDmiAbstractcs && iw && ((im >> 1) & 1)) { csWrEnMaybe = true; w.cmderr_wdata = static_cast<uint8_t>((w.inner_wdata >> 8) & 7); }
  if (iidx == kDmiCommand && iw && im == 0xF) { cmdWrEnMaybe = true; w.command_wdata = w.inner_wdata; }
  if (iidx == kDmiAbstractauto && iw) { if (im & 1) autodataWrEnMaybe = true; if ((im & 0xC) == 0xC) autoprogWrEnMaybe = true; w.auto_wdata = w.inner_wdata; }
  if ((iidx == kDmiData0 || iidx == kDmiData0 + 1) && (iw || ir)) {
    const unsigned base = 4 * (iidx - kDmiData0);
    for (unsigned b = 0; b < 4; ++b) if ((im >> b) & 1) { dataAccessVec |= 1u << (base + b); if (iw) { w.data_wr_mask |= static_cast<uint8_t>(1u << (base + b)); w.data_wr[base + b] = static_cast<uint8_t>(w.inner_wdata >> (8 * b)); } }
    dataAccess = dataAccessVec != 0;
  }
  if (iidx >= kDmiProgbuf0 && iidx < kDmiProgbuf0 + 16 && (iw || ir)) {
    const unsigned base = 4 * (iidx - kDmiProgbuf0);
    for (unsigned b = 0; b < 4; ++b) if ((im >> b) & 1) { progAccessVec |= 1ull << (base + b); if (iw) { w.progbuf_wr_mask |= 1ull << (base + b); w.progbuf_wr[base + b] = static_cast<uint8_t>(w.inner_wdata >> (8 * b)); } }
    progAccess = progAccessVec != 0;
  }
  w.cmderr_wr = csWrEnMaybe && legal;
  w.command_wr = cmdWrEnMaybe && legal;
  w.autoexecdata_wr = autodataWrEnMaybe && legal;
  w.autoexecprogbuf_wr = autoprogWrEnMaybe && legal;
  // autoexec
  bool autoexec = false;
  for (unsigned i = 0; i < 2; ++i) if (((dataAccessVec >> (4 * i)) & 1) && ((d.abstractauto >> i) & 1)) autoexec = true;
  for (unsigned i = 0; i < 16; ++i) if (((progAccessVec >> (4 * i)) & 1) && ((d.abstractauto >> (16 + i)) & 1)) autoexec = true;
  w.errorBusy = (csWrEnMaybe && !legal) || (autodataWrEnMaybe && !legal) || (autoprogWrEnMaybe && !legal) || (cmdWrEnMaybe && !legal) || (dataAccess && !legal) || (progAccess && !legal);
  // TL-side notifies (HALTED/GOING/RESUMING/EXCEPTION) from this cycle's core access
  if (w.dbg_tl_fire && !w.dbg_tl_read) {
    const uint32_t byte = w.dbg_tl_index << 3;
    if (byte == 0x100) { if ((w.dbg_tl_mask & 3) == 3) w.hartHaltedWrEn = true; if ((w.dbg_tl_mask & 0x30) == 0x30) w.hartGoingWrEn = true; }
    if (byte == 0x108) { if ((w.dbg_tl_mask & 3) == 3) w.hartResumingWrEn = true; if ((w.dbg_tl_mask & 0x30) == 0x30) w.hartExceptionWrEn = true; }
  }
  const bool cmdWrEn = w.command_wr;
  const uint32_t cmdWr = w.command_wdata;
  const bool commandWrIsAccessRegister = (cmdWr >> 24) == 0;
  const bool commandRegIsAccessRegister = (d.command >> 24) == 0;
  const bool commandWrIsUnsupported = cmdWrEn && !commandWrIsAccessRegister;
  const unsigned regno = d.command & 0xFFFF, size = (d.command >> 20) & 7;
  const bool transfer = (d.command >> 17) & 1;
  const bool legalSize = size == 2 || size == 3;
  const bool isGPR = regno >= 0x1000 && regno <= 0x101F && legalSize;
  bool commandRegIsUnsupported = true, commandRegBadHaltResume = false;
  if (commandRegIsAccessRegister && (!transfer || isGPR)) { commandRegIsUnsupported = false; commandRegBadHaltResume = !hartHalted; }
  const bool wrAccessRegisterCommand = cmdWrEn && commandWrIsAccessRegister && d.cmderr == 0;
  const bool regAccessRegisterCommand = autoexec && commandRegIsAccessRegister && d.cmderr == 0;
  w.ctrlStateNxt = d.ctrlState;
  if (d.ctrlState == kStWaiting) {
    if (wrAccessRegisterCommand || regAccessRegisterCommand) w.ctrlStateNxt = kStCheckGenerate;
    else if (commandWrIsUnsupported) w.errorUnsupported = true;
    else if (autoexec && commandRegIsUnsupported) w.errorUnsupported = true;
  } else if (d.ctrlState == kStCheckGenerate) {
    if (commandRegIsUnsupported) { w.errorUnsupported = true; w.ctrlStateNxt = kStWaiting; }
    else if (commandRegBadHaltResume) { w.errorHaltResume = true; w.ctrlStateNxt = kStWaiting; }
    else { w.ctrlStateNxt = kStExec; w.goAbstract = true; }
  } else if (d.ctrlState == kStExec) {
    if (!d.goReg && w.hartHaltedWrEn) w.ctrlStateNxt = kStWaiting;
    if (w.hartExceptionWrEn) { w.ctrlStateNxt = kStWaiting; w.errorException = true; }
  }
  (void)debug_reset;
}

// ============================================================================
// debug module commit
// ============================================================================
void Uncore::commit_debug(const UncoreIn& in) {
  Wires& w = *w_;
  DebugModule& d = dbg;
  const bool dmi_reset = in.reset;
  const bool debug_reset = dmi_reset || !d.debug_reset_sync.out();
  const bool clk = w.debug_clk;
  // snapshots of the crossing partners (values before this edge)
  const AsyncSource a_source_old = d.a_source, d_source_old = d.d_source, ic_source_old = d.ic_source;
  const AsyncSink a_sink_old = d.a_sink, d_sink_old = d.d_sink, ic_sink_old = d.ic_sink;
  const bool dmactive_old = d.dmactive;
  const bool ndmreset_old = d.ndmreset;
  const bool dmactive_ack_old = d.dmactiveAck_sync.out();
  const bool dmactive_synced_old = d.dmactive_synced.out();
  const bool hart_reset_old = d.hartIsInResetSync.out();
  const bool debug_interrupt_old = d.debugInt || d.hrDebugInt;

  // ---- DMI clock domain ----
  d.dmiXbar_d.step(w.dx_valids, w.dx_sink_ready, w.dx_sink_fire, 0);
  d.err_d.step(w.errd_valids, w.errd_sink_ready, w.errd_sink_fire, 0);
  if (w.bar_a_fire) d.bar_a_cnt.step(true, 0);
  if (w.bar_d_fire) d.bar_d_cnt.step(true, 0);
  if (d.bar_in_reset || w.bar_flight_next == 0) d.bar_bypass_reg = w.bypass == d.bar_bypass_reg ? (!d.dmactive || !d.dmactiveAckSync.out()) : (!d.dmactive || !d.dmactiveAckSync.out());
  d.bar_flight = w.bar_flight_next;
  d.bar_in_reset = false;
  // dmOuter registers
  {
    bool dmactive = d.dmactive, ndmreset = d.ndmreset, haltreq = d.haltreq;
    const uint32_t wd = w.outer_wdata;
    if (!dmactive_old) { ndmreset = false; haltreq = false; }
    else { if (w.ndmresetWrEn) ndmreset = (wd >> 1) & 1; if (w.haltreqWrEn) haltreq = (wd >> 31) & 1; }
    if (w.dmactiveWrEn) dmactive = wd & 1;
    d.dmactive = dmactive; d.ndmreset = ndmreset; d.haltreq = haltreq;
    if (!dmactive_old) d.debugInt = false; else if (w.haltreqWrEn) d.debugInt = (wd >> 31) & 1;   // hartsello is always 0
    d.innerCtrlValidReg = w.innerCtrl_valid && !w.innerCtrl_ready;
    d.innerCtrlResumeReqReg = w.ic_resumereq && !w.innerCtrl_ready;
    d.innerCtrlAckHaveResetReg = w.ic_ackhavereset && !w.innerCtrl_ready;
    d.hrmaskReg = w.ic_hrmask;
  }
  d.dmactiveAckSync.step(d.dmactiveAck_sync.out(), dmi_reset, false);
  {
    const SourceEval as{a_source_old.sink_valid.out(), a_source_old.ready_reg && a_source_old.sink_valid.out(), w.as_enq_fire, false, false};
    SourceEval e = as; e.widx_next = e.sink_ready ? (a_source_old.widx_bin ^ e.fire) : false; e.ready_next = e.sink_ready && (e.widx_next != (a_source_old.ridx_sync.out() ^ true));
    source_commit(d.a_source, e, w.as_bits, 0, a_sink_old, dmi_reset, dmi_reset || debug_reset);
  }
  {
    SinkEval e; e.source_ready = d_sink_old.source_valid.out(); e.deq_valid = d_sink_old.valid_reg && e.source_ready; e.fire = w.ds_deq_fire;
    e.ridx_next = e.source_ready ? (d_sink_old.ridx_bin ^ e.fire) : false; e.valid_next = e.source_ready && (e.ridx_next != d_sink_old.widx_sync.out());
    sink_commit(d.d_sink, e, d_source_old, dmi_reset, dmi_reset || debug_reset);
  }
  {
    SourceEval e; e.sink_ready = ic_source_old.sink_valid.out(); e.enq_ready = ic_source_old.ready_reg && e.sink_ready; e.fire = w.ics_enq_fire;
    e.widx_next = e.sink_ready ? (ic_source_old.widx_bin ^ e.fire) : false; e.ready_next = e.sink_ready && (e.widx_next != (ic_source_old.ridx_sync.out() ^ true));
    source_commit(d.ic_source, e, w.ics_bits, 0, ic_sink_old, dmi_reset, dmi_reset || debug_reset);
  }
  if (dmi_reset) {
    d.dmiXbar_d = RrArbiter<2>{}; d.err_d = LowArbiter<2>{}; d.err_idle = true; d.bar_in_reset = true; d.bar_flight = 0; d.bar_a_cnt.counter = 0; d.bar_d_cnt.counter = 0;
    d.dmactive = d.ndmreset = d.haltreq = false; d.debugInt = false; d.innerCtrlValidReg = d.innerCtrlResumeReqReg = d.innerCtrlAckHaveResetReg = false; d.hrmaskReg = false;
  }

  // ---- harness-level debug clock/reset ----
  d.debug_reset_sync.step(true, dmi_reset, false);
  d.dmactiveAck_sync.step(dmactive_old, debug_reset, false);
  d.clock_en = debug_reset ? true : dmactive_ack_old;

  // ---- debug clock domain (gated) ----
  if (clk) {
    // async crossings
    {
      SinkEval e; e.source_ready = a_sink_old.source_valid.out(); e.deq_valid = a_sink_old.valid_reg && e.source_ready; e.fire = w.a_sink_deq_fire;
      e.ridx_next = e.source_ready ? (a_sink_old.ridx_bin ^ e.fire) : false; e.valid_next = e.source_ready && (e.ridx_next != a_sink_old.widx_sync.out());
      sink_commit(d.a_sink, e, a_source_old, debug_reset, dmi_reset || debug_reset);
    }
    {
      SourceEval e; e.sink_ready = d_source_old.sink_valid.out(); e.enq_ready = d_source_old.ready_reg && e.sink_ready; e.fire = w.d_source_enq_fire;
      e.widx_next = e.sink_ready ? (d_source_old.widx_bin ^ e.fire) : false; e.ready_next = e.sink_ready && (e.widx_next != (d_source_old.ridx_sync.out() ^ true));
      source_commit(d.d_source, e, w.d_source_bits, 0, d_sink_old, debug_reset, dmi_reset || debug_reset);
    }
    {
      SinkEval e; e.source_ready = ic_sink_old.source_valid.out(); e.deq_valid = ic_sink_old.valid_reg && e.source_ready; e.fire = w.ic_sink_deq_fire;
      e.ridx_next = e.source_ready ? (ic_sink_old.ridx_bin ^ e.fire) : false; e.valid_next = e.source_ready && (e.ridx_next != ic_sink_old.widx_sync.out());
      sink_commit(d.ic_sink, e, ic_source_old, debug_reset, dmi_reset || debug_reset);
    }
    d.dmactive_synced.step(dmactive_old, debug_reset, false);
    d.hartIsInResetSync.step(in.reset, debug_reset, false);
    // dmInner registers (synchronous reset by debug_reset)
    const bool dmactive = dmactive_synced_old;
    const bool inReset = hart_reset_old;
    if (debug_reset) {
      d.haltedBit = d.resumeReq = d.haveResetBit = false; d.hrmask = d.hrDebugInt = false; d.cmderr = 0; d.abstractauto = 0; d.command = 0;
      std::memset(d.data_mem, 0, sizeof d.data_mem); std::memset(d.progbuf, 0, sizeof d.progbuf); d.goReg = false; d.ctrlState = kStWaiting;
    } else {
      // halted / resume request bits
      bool halted = d.haltedBit, resume = d.resumeReq;
      if (!dmactive) { halted = false; resume = false; }
      else {
        resume = d.resumeReq && !inReset;
        if (w.hartHaltedWrEn) halted = !inReset; else if (w.hartResumingWrEn) halted = false; else halted = d.haltedBit && !inReset;
        if (w.hartResumingWrEn) resume = false;
        if (w.resumereq) resume = !inReset;
      }
      bool haveReset = d.haveResetBit;
      if (!dmactive) haveReset = false;
      else if (w.ic_fire && w.ackhavereset_fire) haveReset = inReset;
      else haveReset = d.haveResetBit || inReset;
      bool hrmask = d.hrmask;
      if (!dmactive) hrmask = false; else if (w.ic_fire) hrmask = (ic_sink_old.deq_reg >> 2) & 1;
      bool hrDebugInt = d.hrDebugInt;
      if (!dmactive) hrDebugInt = false; else hrDebugInt = d.hrmask && (inReset || (d.hrDebugInt && !d.haltedBit));
      // abstract command control/status
      uint8_t cmderr = d.cmderr;
      if (!dmactive) cmderr = 0;
      else if (w.errorBusy) cmderr = 1;
      else if (w.errorException) cmderr = 3;
      else if (w.errorUnsupported) cmderr = 2;
      else if (w.errorHaltResume) cmderr = 4;
      else if (w.cmderr_wr) cmderr = static_cast<uint8_t>(cmderr & ~w.cmderr_wdata & 7);
      uint32_t aauto = d.abstractauto;
      if (!dmactive) aauto = 0;
      else { if (w.autoexecprogbuf_wr) aauto = (aauto & 0xFFFFu) | (w.auto_wdata & 0xFFFF0000u); if (w.autoexecdata_wr) aauto = (aauto & 0xFFFF0000u) | (w.auto_wdata & 3u); }
      uint32_t command = d.command;
      if (!dmactive) command = 0; else if (w.command_wr) command = w.command_wdata;
      // data / program buffer bytes: DMI writes (when legal), then core writes, then the dmactive clear
      const bool legal = d.ctrlState == kStWaiting;
      if (legal) for (unsigned i = 0; i < 8; ++i) if ((w.data_wr_mask >> i) & 1) d.data_mem[i] = w.data_wr[i];
      if (legal) for (unsigned i = 0; i < 64; ++i) if ((w.progbuf_wr_mask >> i) & 1) d.progbuf[i] = w.progbuf_wr[i];
      if (w.dbg_tl_fire && !w.dbg_tl_read) {
        const uint32_t byte = w.dbg_tl_index << 3;
        if (byte == 0x380) for (unsigned i = 0; i < 8; ++i) if ((w.dbg_tl_mask >> i) & 1) d.data_mem[i] = static_cast<uint8_t>(w.dbg_tl_wdata >> (8 * i));
        if (byte >= 0x340 && byte < 0x380) for (unsigned i = 0; i < 8; ++i) if ((w.dbg_tl_mask >> i) & 1) d.progbuf[byte - 0x340 + i] = static_cast<uint8_t>(w.dbg_tl_wdata >> (8 * i));
      }
      if (!dmactive) { std::memset(d.data_mem, 0, sizeof d.data_mem); std::memset(d.progbuf, 0, sizeof d.progbuf); }
      // go / generated instructions
      bool go = d.goReg;
      if (!dmactive) go = false; else if (w.goAbstract) go = true; else if (w.hartGoingWrEn) go = false;
      if (w.goAbstract) {
        const uint32_t cmd = d.command;
        const unsigned regno = cmd & 0xFFFF, size = (cmd >> 20) & 7;
        const bool transfer = (cmd >> 17) & 1, write = (cmd >> 16) & 1, postexec = (cmd >> 18) & 1;
        const uint32_t rd = regno & 0x1F;
        const uint32_t lw = 0x03u | (rd << 7) | (size << 12) | (0u << 15) | (0x380u << 20);
        const uint32_t sw = 0x23u | ((0x380u & 0x1F) << 7) | (size << 12) | (0u << 15) | (rd << 20) | ((0x380u >> 5) << 25);
        d.abstract_gen[0] = transfer ? (write ? lw : sw) : kNop;
        d.abstract_gen[1] = postexec ? kNop : kEbreak;
      }
      uint8_t st = w.ctrlStateNxt;
      if (!dmactive) st = kStWaiting;
      d.haltedBit = halted; d.resumeReq = resume; d.haveResetBit = haveReset; d.hrmask = hrmask; d.hrDebugInt = hrDebugInt;
      d.cmderr = cmderr; d.abstractauto = aauto; d.command = command; d.goReg = go; d.ctrlState = st;
    }
  }
  // tile-side debug interrupt synchronizer (no reset; runs on the tile clock)
  tile_debug_int_sync.step(debug_interrupt_old, false, false);
  // TestHarness: ldut_reset_reg = AsyncResetReg(ndreset)
  ldut_reset_reg = in.reset ? false : ndmreset_old;
}

}  // namespace chisa::rocket_model::uncore
