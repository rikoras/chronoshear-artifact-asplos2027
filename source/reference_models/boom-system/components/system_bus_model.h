#pragma once
// Software system fabric, with transaction queues and arbitration shared by
// the 64-bit Small/Medium and 128-bit Large geometries. Width conversion packs
// accepted beats directly; MMIO retains independent AXI response queues.

#include <array>
#include <cstdint>
#include <cstring>

#include "../protocol/system_bus.h"
#include "tl_width.h"
#include "../../boom_model/common/boom_config.h"
#include "../../boom_model/common/model_mode.h"

namespace chisa::boom_system::components {
using namespace protocol;

class SystemBusModel {
 public:
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  static constexpr bool kWide=true;
#else
  static constexpr bool kWide=false;
#endif
  static constexpr unsigned kIds=kWide?9:7,kFbus=0,kTile=1;
  static constexpr unsigned kFifoId=kWide?2:1,kIdMask=kWide?15:7;

  SystemBusModel() {
    refresh_outputs(last_inputs_);
  }

  const SystemBusOutputs& outputs() const { return outputs_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return eval_count_; }
  std::uint64_t skipped_count() const { return skipped_count_; }

  const SystemBusOutputs& evaluate(const SystemBusInputs& inputs) {
    pending_inputs_ = inputs;
    pending_valid_ = true;
    if (inputs != applied_inputs_) {
      refresh_outputs(inputs);
      applied_inputs_ = inputs;
    }
    return outputs_;
  }

  void commit_evaluated() {
    if (!pending_valid_) return;
    if (!active_ && pending_inputs_ == last_inputs_) {
      ++skipped_count_;
      pending_valid_ = false;
      return;
    }
    if(pending_inputs_!=last_inputs_) drain_=2;
    tick(pending_inputs_);
    if(drain_) --drain_;
    mmio_quiet_=mmio_quiescent();
    active_=busy() || drain_!=0;
    refresh_outputs(pending_inputs_);
    last_inputs_ = pending_inputs_;
    applied_inputs_ = pending_inputs_;
    pending_valid_ = false;
    ++eval_count_;
  }

  void commit(const SystemBusInputs& inputs) {
    evaluate(inputs);
    commit_evaluated();
  }

 public:
  // ---- records ----------------------------------------------------------
  using TlA=protocol::MbusTlA;
  using TlD=protocol::CoherentTlD;
  struct Arw {  // TLToAXI4 ARW record (FIR Queue_13 payload)
    std::uint8_t id = 0;        // 3 bits (4 after the id indexer)
    std::uint32_t addr = 0;     // 31 bits
    std::uint8_t len = 0, size = 0, burst = 0;
    bool lock = false;
    std::uint8_t cache = 0, prot = 0, qos = 0;
    std::uint8_t echo_size = 0, echo_source = 0;
    bool wen = false;
  };
  struct Wb {
    std::uint64_t data = 0;
    std::uint8_t strb = 0;
    bool last = false;
  };
  struct Bb {
    std::uint8_t id = 0, resp = 0;
  };
  struct Rb {
    std::uint8_t id = 0;
    std::uint64_t data = 0;
    std::uint8_t resp = 0;
    bool last = false;
    std::uint8_t echo_size = 0, echo_source = 0;
  };
  struct Echo {
    std::uint8_t size = 0, source = 0;
  };
  template <class T>
  struct Q2 {  // chisel Queue(2), no flow/pipe
    bool value = false, value_1 = false, maybe_full = false;
    T ram[2];
  };
  struct Q8R {  // Queue(8) of R beats (deinterleaver)
    std::uint8_t enq_ptr = 0, deq_ptr = 0;
    bool maybe_full = false;
    Rb ram[8];
  };
  struct QEcho {  // UserYanker per-id queue: depth 8 (ids 1, 2) or 1
    std::uint8_t enq_ptr = 0, deq_ptr = 0;
    bool maybe_full = false;
    Echo ram[8];
  };
  struct Arb {  // TLArbiter.roundRobin state
    std::uint16_t beats_left = 0;  // 9 bits
    std::uint8_t mask = 0;         // N bits, reset all-ones
    std::uint8_t state = 0;        // N bits
  };
  struct State {
    // TLFIFOFixer lane 0 (fbus), FIR L6662-L7147
    std::uint16_t fx_a_first_counter = 0, fx_d_first_counter = 0;  // 9 bits
    std::uint16_t fx_flight = 0;                                    // 16 bits
    std::uint8_t fx_stalls_id = 0, fx_stalls_id_1 = 0;              // 2 bits, no reset
    // TLXbar arbiters: A -> out 0/1/2 (N = 2), D -> in 0/1 (N = 3)
    Arb xa[3];
    Arb xd[2];
    // TLToAXI4, FIR L13069-L13732
    std::uint8_t t_counter = 0;   // 5 bits
    bool t_doneAW = false, t_r_holds_d = false;
    std::uint8_t t_b_delay = 0;   // 3 bits, no reset
    bool t_r_first = false;       // reset 1
    bool t_r_denied_r = false;    // no reset
    std::uint8_t t_count[kIds] = {}; // ids 0..6: widths 1,4,4,1,1,1,1
    std::array<bool,kIds> t_write{};
    bool t_w_full = false;        // Queue_12 (flow) maybe_full
    Wb t_w_ram;
    bool t_arw_full = false;      // Queue_13 (flow) maybe_full
    Arw t_arw_ram;
    // AXI4Deinterleaver, FIR L8288-L9260
    bool d_locked = false;
    std::uint8_t d_deq_id = 0;         // 4 bits, no reset
    std::uint8_t d_pending[kIds] = {};    // 4 bits each
    Q8R d_qs[kIds];
    // AXI4UserYanker, FIR L10054-L10682
    QEcho y_rq[kIds];
    QEcho y_wq[kIds];
    // AXI4Buffer, FIR L7733-L7845
    Q2<Arw> b_aw;
    Q2<Wb> b_w;
    Q2<Bb> b_b;
    Q2<Arw> b_ar;
    Q2<Rb> b_r;
    TlMerge<TlA> fbus_a_width;
    TlSplit<TlD> fbus_d_width;
    std::array<TlSplit<TlA>,3> a_width;
    std::array<TlMerge<TlD>,3> d_width;
    TlSplit<CoherentTlC> c_width;
    std::array<bool,16> fbus_source_upper{};
    bool fbus_held_upper=false;
  };

  const State& state() const {return s_;}
 private:
  static constexpr std::array<std::uint8_t,kIds> kYankDepth=[] {
    std::array<std::uint8_t,kIds> depth{};
    for(unsigned i=0;i<kIds;++i) depth[i]=(i==kFifoId || i==kFifoId+1)?8:1;
    return depth;
  }();

  // ---- helpers ------------------------------------------------------------
  template <class T>
  static T zeroed() {
    T t;
    std::memset(static_cast<void*>(&t), 0, sizeof(T));
    return t;
  }
  static bool a_has_data(unsigned opcode) { return (opcode & 4u) == 0; }
  static bool d_has_data(unsigned opcode) { return (opcode & 1u) != 0; }
  static unsigned beats1_12(unsigned size) {
    return (((1u << size) - 1u) & 0xfffu) >> 3;
  }
  static unsigned beats1_8(unsigned size) {
    return (((1u << size) - 1u) & 0xffu) >> 3;
  }
  static unsigned beats1_6(unsigned size) {
    return (((1u << size) - 1u) & 0x3fu) >> 3;
  }
  // Per-client AXI IDs: one per tile source and one shared ordered ID
  // for each eight-source front-bus client. This is fixed topology geometry.
  static unsigned axi_id_of(unsigned source) {
    if constexpr(kWide) {
      if(source<5) return source+4;
      if(source==5) return 1;
      if(source>=24) return 3;
      if(source>=16) return 2;
      return 0;
    } else {
      if(source<8) return 1;
      if(source<16) return 2;
      if(source<19) return source-12;
      if(source==19) return 3;
      return 0;
    }
  }
  /** TLArbiter.roundRobin, N sources (Arbiter.scala L74-L128). */
  struct ArbComb {
    bool idle = false, latch = false;
    unsigned readys = 0, winner = 0, mux = 0, allowed = 0;
    unsigned init_beats = 0;
    bool sink_valid = false;
  };
  static ArbComb arb_comb(const Arb& a, unsigned n, unsigned valids,
                          const unsigned* beats) {
    ArbComb c;
    const unsigned m = (1u << n) - 1u;
    const unsigned mask = a.mask & m;
    c.idle = a.beats_left == 0;
    unsigned start=n-1;
    if(mask) {unsigned last=0;while(!(mask&(1u<<last))) ++last;start=(last+n-1)%n;}
    for(unsigned step=0;step<n;++step) {
      const unsigned client=(start+n-step)%n;c.readys|=1u<<client;
      if(valids&(1u<<client)) break;
    }
    c.winner = c.readys & valids;
    for (unsigned i = 0; i < n; ++i)
      if (c.winner & (1u << i)) c.init_beats |= beats[i];
    c.mux = c.idle ? c.winner : (a.state & m);
    c.allowed = c.idle ? c.readys : (a.state & m);
    c.sink_valid = c.idle ? valids != 0 : ((a.state & valids & m) != 0);
    return c;
  }
  static void arb_tick(Arb& a, unsigned n, const ArbComb& c, unsigned valids,
                       bool sink_ready, bool reset) {
    const unsigned m = (1u << n) - 1u;
    const bool latch = c.idle && sink_ready;
    const unsigned fire = (c.sink_valid && sink_ready) ? 1u : 0u;
    if (latch && valids != 0) {
      unsigned chosen=0;while(!(c.winner&(1u<<chosen))) ++chosen;
      a.mask=static_cast<std::uint8_t>((m<<chosen)&m);
    }
    a.beats_left = static_cast<std::uint16_t>(
        (latch ? c.init_beats : (a.beats_left - fire)) & 0x1ffu);
    if (c.idle) a.state = static_cast<std::uint8_t>(c.winner);
    if (reset) {
      a.mask = static_cast<std::uint8_t>(m);
      a.beats_left = 0;
      a.state = 0;
    }
  }

  template <class T>
  static bool q2_empty(const Q2<T>& q) {
    return q.value == q.value_1 && !q.maybe_full;
  }
  template <class T>
  static bool q2_full(const Q2<T>& q) {
    return q.value == q.value_1 && q.maybe_full;
  }
  template <class T>
  static void q2_tick(Q2<T>& q, bool enq_fire, const T& enq, bool deq_fire,
                      bool reset) {
    if (enq_fire) {
      q.ram[q.value ? 1 : 0] = enq;
      q.value = !q.value;
    }
    if (deq_fire) q.value_1 = !q.value_1;
    if (enq_fire != deq_fire) q.maybe_full = enq_fire;
    if (reset) q.value = q.value_1 = q.maybe_full = false;
  }

  // ---- per-cycle combinational values ------------------------------------
  struct Comb {
    bool mmio_evaluated = true;
    WidthTransfer<TlA> fbus_a_width;
    WidthTransfer<TlD> fbus_d_width;
    std::array<WidthTransfer<TlA>,3> a_width;
    std::array<WidthTransfer<TlD>,3> d_width;
    std::array<TlD,3> narrow_d;
    TlA fbus_input;
    WidthTransfer<CoherentTlC> c_width;
    CoherentTlC c_input;
    bool req_a[2][3] = {};
    // fixer
    bool fx_gate = false, fx_a_first = false, fx_d_first = false;
    unsigned fx_a_beats1 = 0, fx_d_beats1 = 0, fx_a_id = 0;
    bool fx_a_notfifo = false, fx_sel0 = false, fx_sel1 = false;
    bool fx_a_fire = false, fx_d_fire = false;
    // xbar
    TlA in_a[2];
    bool in_a_valid[2] = {};
    unsigned beats_ai[2] = {};
    unsigned va[3] = {};  // per output: valids (bit i = input i)
    ArbComb xa[3];
    bool out_a_ready[3] = {};
    TlA out_a[3];
    bool out_a_valid[3] = {};
    bool in_a_ready[2] = {};
    TlD out_d[3];
    bool out_d_valid[3] = {};
    unsigned beats_do[3] = {};
    unsigned vd[2] = {};
    ArbComb xd[2];
    bool in_d_ready[2] = {};
    TlD in_d[2];
    bool in_d_valid[2] = {};
    bool out_d_ready[3] = {};
    // tl2axi4
    bool t_a_valid = false;
    TlA t_a;
    bool t_a_isPut = false, t_a_first = false, t_a_last = false;
    unsigned t_beats1 = 0;
    Arw t_arw;
    bool t_stall = false, t_a_ready = false;
    bool t_out_arw_valid = false, t_out_w_valid = false;
    bool t_out_arw_ready = false, t_out_w_ready = false;  // flow queue enq.ready
    Wb t_w_bits;
    bool t_arw_enq_fire = false, t_arw_deq_fire = false;
    bool t_w_enq_fire = false, t_w_deq_fire = false;
    bool t_arwq_valid = false;  // flow queue deq view
    Arw t_arwq_bits;
    bool t_wq_valid = false;
    Wb t_wq_bits;
    bool t_ar_valid = false, t_aw_valid = false, t_ar_ready = false,
         t_aw_ready = false, t_w_ready = false;
    bool t_r_wins = false;
    bool t_r_valid = false, t_b_valid = false;
    Rb t_r;      // after the id indexer (3-bit id) with echo
    Bb t_b;
    Echo t_b_echo;
    bool t_in_d_valid = false;
    TlD t_in_d;
    bool t_in_d_ready = false;
    bool t_r_ready = false, t_b_ready = false;
    bool t_r_fire = false, t_b_fire = false;
    unsigned t_inc = 0, t_dec = 0;  // bit k = AXI id k
    // deinterleaver
    bool d_r_ready = false;      // out.r.ready towards the yanker
    bool d_rin_valid = false;    // in.r.valid towards tl2axi4
    Rb d_rin;
    bool d_rin_ready = false;
    unsigned d_pending_next[kIds] = {};
    unsigned d_pending_mask = 0, d_winner = 0;
    bool d_enq_fire[kIds] = {};
    bool d_deq_fire[kIds] = {};
    bool d_rearb = false;
    // yanker
    bool y_ar_ok = false, y_aw_ok = false;
    bool y_aro_valid = false, y_awo_valid = false;
    bool y_in_ar_ready = false, y_in_aw_ready = false;
    bool y_ro_valid = false, y_bo_valid = false;
    Rb y_ro;       // buffer r deq view (4-bit id) with echo attached
    Bb y_bo;
    Echo y_bo_echo;
    bool y_ro_ready = false, y_bo_ready = false;
    bool y_rq_enq_fire[kIds] = {}, y_rq_deq_fire[kIds] = {};
    bool y_wq_enq_fire[kIds] = {}, y_wq_deq_fire[kIds] = {};
    // buffer
    bool b_aw_enq_fire = false, b_aw_deq_fire = false;
    bool b_w_enq_fire = false, b_w_deq_fire = false;
    bool b_b_enq_fire = false, b_b_deq_fire = false;
    bool b_ar_enq_fire = false, b_ar_deq_fire = false;
    bool b_r_enq_fire = false, b_r_deq_fire = false;
    Arw b_aw_enq, b_ar_enq;
    Wb b_w_enq;
    Bb b_b_enq;
    Rb b_r_enq;
  };

  static TlA tile_a_in(const MbusTlA& a) {
    TlA t = zeroed<TlA>();
    t.opcode = a.opcode & 7u;
    t.param = a.param & 7u;
    t.size = a.size & 15u;
    t.source = static_cast<std::uint8_t>((a.source & boomcfg::TILE_SOURCE_MASK) | (kWide?0u:0x10u));
    t.address = a.address;
    t.mask = a.mask & (kWide?65535:255);
    t.data = a.data;
    t.data_hi=kWide?a.data_hi:0;
    t.corrupt = a.corrupt;
    // FIR L20710-L20716: the tile client's amba_prot is hard-wired.
    t.privileged = true;
    t.secure = true;
    return t;
  }
  static TlA fbus_a_in(const MbusTlA& a) {
    TlA t = zeroed<TlA>();
    t.opcode = a.opcode & 7u;
    t.param = a.param & 7u;
    t.size = a.size & 15u;
    t.source = static_cast<std::uint8_t>((a.source & 15u) | (kWide?16u:0u));
    t.address = a.address;
    t.mask = a.mask & (kWide?65535:255);
    t.data = a.data;
    t.data_hi=kWide?a.data_hi:0;
    t.corrupt = a.corrupt;
    t.bufferable = a.bufferable;
    t.modifiable = a.modifiable;
    t.readalloc = a.readalloc;
    t.writealloc = a.writealloc;
    t.privileged = a.privileged;
    t.secure = a.secure;
    t.fetch = a.fetch;
    return t;
  }
  static TlD tld_in(const CoherentTlD& d, unsigned size_mask,
                    unsigned sink_mask) {
    TlD t = zeroed<TlD>();
    t.opcode = d.opcode & 7u;
    t.param = d.param & 3u;
    t.size = static_cast<std::uint8_t>(d.size & size_mask);
    t.source = d.source & 31u;
    t.sink = static_cast<std::uint8_t>(d.sink & sink_mask);
    t.denied = d.denied;
    t.data = d.data;
    t.data_hi=kWide?d.data_hi:0;
    t.corrupt = d.corrupt;
    return t;
  }

  void compute_comb(const SystemBusInputs& in, Comb& c) const {
    c = zeroed<Comb>();
    const State& s = s_;

    // ================= 1. FIFO fixer lane 0 (fbus), L6757-L6937 ==========
    c.fbus_input=fbus_a_in(in.fbus_a);c.fbus_input.valid=in.fbus_a.valid;
    if constexpr(kWide) c.fbus_a_width=s.fbus_a_width.evaluate(c.fbus_input,false);
    const TlA& fa=kWide?c.fbus_a_width.output:c.fbus_input;
    c.fx_a_notfifo = ((fa.address >> 31) & 1u) != 0;
    c.fx_a_id = ((fa.address >> 30) & 1u) ? 2u : 1u;
    c.fx_a_beats1 = a_has_data(fa.opcode) ? beats1_12(fa.size)/(kWide?2:1) : 0;
    c.fx_a_first = s.fx_a_first_counter == 0;
    c.fx_sel0 = ((fa.source & 15u) >> 3) == 0;
    c.fx_sel1 = ((fa.source & 15u) >> 3) == 1;
    const bool stalls_0 = c.fx_sel0 && c.fx_a_first &&
                          (s.fx_flight & 0xffu) != 0 &&
                          s.fx_stalls_id != c.fx_a_id;
    const bool stalls_1 = c.fx_sel1 && c.fx_a_first &&
                          ((s.fx_flight >> 8) & 0xffu) != 0 &&
                          s.fx_stalls_id_1 != c.fx_a_id;
    c.fx_gate = c.fx_a_notfifo || !(stalls_0 || stalls_1);

    // ================= 2. xbar A fan-out and arbiters ====================
    c.in_a[kFbus]=fa;c.in_a_valid[kFbus]=fa.valid && c.fx_gate;
    c.in_a[kTile]=tile_a_in(in.tile_a);c.in_a_valid[kTile]=in.tile_a.valid;
    for(unsigned i=0;i<2;++i)
      c.beats_ai[i]=a_has_data(c.in_a[i].opcode)?beats1_12(c.in_a[i].size)/(kWide?2:1):0;
    for (int i = 0; i < 2; ++i) {
      const unsigned hi = (c.in_a[i].address >> 30) & 3u;
      c.req_a[i][0] = hi == 0;
      c.req_a[i][1] = hi == 2;
      c.req_a[i][2] = hi == 1;
    }
    for (int o = 0; o < 3; ++o) {
      for (int i = 0; i < 2; ++i)
        if (c.in_a_valid[i] && c.req_a[i][o]) c.va[o] |= 1u << i;
      c.xa[o] = arb_comb(s.xa[o], 2, c.va[o], c.beats_ai);
      c.out_a_valid[o] = c.xa[o].sink_valid;
      TlA bits = zeroed<TlA>();
      for (int i = 0; i < 2; ++i) {
        if (!((c.xa[o].mux >> i) & 1u)) continue;
        const TlA& b = c.in_a[i];
        bits.opcode |= b.opcode;
        bits.param |= b.param;
        bits.size |= b.size;
        bits.source |= b.source;
        bits.address |= b.address;
        bits.mask |= b.mask;
        bits.data |= b.data;
        bits.data_hi |= b.data_hi;
        bits.corrupt = bits.corrupt || b.corrupt;
        bits.bufferable = bits.bufferable || b.bufferable;
        bits.modifiable = bits.modifiable || b.modifiable;
        bits.readalloc = bits.readalloc || b.readalloc;
        bits.writealloc = bits.writealloc || b.writealloc;
        bits.privileged = bits.privileged || b.privileged;
        bits.secure = bits.secure || b.secure;
        bits.fetch = bits.fetch || b.fetch;
      }
      c.out_a[o] = bits;
    }
    c.out_a[0].address &= 0x0fffffffu;  // cbus: 28-bit address, L20776
    c.out_a[1].size &= 7u;              // L2: 3-bit size, L20853
    c.out_a[2].address &= 0x7fffffffu;  // mmio: 31-bit address, L20912

    c.mmio_evaluated = true;

    // ================= 3. TLToAXI4 forward path, L13171-L13330 ===========
    if constexpr(kWide) {
      for(unsigned port=0;port<3;++port) {
        c.out_a[port].valid=c.out_a_valid[port];
        const auto& held=s.a_width[port].holding?s.a_width[port].saved:c.out_a[port];
        c.a_width[port]=s.a_width[port].evaluate(c.out_a[port],false,(held.address&8)!=0);
      }
    }
    const TlA& A = kWide?c.a_width[2].output:c.out_a[2];
    c.t_a_valid = kWide?A.valid:c.out_a_valid[2];
    c.t_a = A;
    c.t_a_isPut = a_has_data(A.opcode);
    c.t_beats1 = c.t_a_isPut ? beats1_8(A.size) : 0;
    c.t_a_first = s.t_counter == 0;
    c.t_a_last = s.t_counter == 1 || c.t_beats1 == 0;
    {
      Arw& w = c.t_arw;
      w.wen = c.t_a_isPut;
      w.id = static_cast<std::uint8_t>(axi_id_of(A.source));
      w.addr = A.address & 0x7fffffffu;
      w.len = static_cast<std::uint8_t>((((1u << A.size) - 1u) & 0x7ffu) >> 3);
      w.size = static_cast<std::uint8_t>(A.size > 3 ? 3u : A.size);
      w.burst = 1;
      w.lock = false;
      w.qos = 0;
      w.prot = static_cast<std::uint8_t>((A.fetch ? 4u : 0u) |
                                         (A.secure ? 0u : 2u) |
                                         (A.privileged ? 1u : 0u));
      w.cache = static_cast<std::uint8_t>((A.writealloc ? 8u : 0u) |
                                          (A.readalloc ? 4u : 0u) |
                                          (A.modifiable ? 2u : 0u) |
                                          (A.bufferable ? 1u : 0u));
      w.echo_size = A.size;
      w.echo_source = A.source;
    }
    bool id_stall[kIds];
    for(unsigned id=0;id<kIds;++id)
      id_stall[id]=s.t_count[id]==kYankDepth[id] || (kYankDepth[id]>1 && s.t_count[id]!=0 && s.t_write[id]!=c.t_a_isPut);
    c.t_stall = id_stall[c.t_arw.id] && c.t_a_first;
    c.t_out_arw_ready = !s.t_arw_full;  // Queue_13 enq.ready, L10720
    c.t_out_w_ready = !s.t_w_full;      // Queue_12 enq.ready
    c.t_a_ready = !c.t_stall &&
                  (c.t_a_isPut ? ((s.t_doneAW || c.t_out_arw_ready) && c.t_out_w_ready)
                               : c.t_out_arw_ready);
    c.t_out_arw_valid = !c.t_stall && c.t_a_valid &&
                        (c.t_a_isPut ? (!s.t_doneAW && c.t_out_w_ready) : true);
    c.t_out_w_valid = !c.t_stall && c.t_a_valid && c.t_a_isPut &&
                      (s.t_doneAW || c.t_out_arw_ready);
    c.t_w_bits.data = A.data;
    c.t_w_bits.strb = A.mask;
    c.t_w_bits.last = c.t_a_last;
    // Flow-queue dequeue views (Queue_13 / Queue_12, L10718-L10732).
    c.t_arwq_valid = s.t_arw_full || c.t_out_arw_valid;
    c.t_arwq_bits = s.t_arw_full ? s.t_arw_ram : c.t_arw;
    c.t_wq_valid = s.t_w_full || c.t_out_w_valid;
    c.t_wq_bits = s.t_w_full ? s.t_w_ram : c.t_w_bits;
    c.t_ar_valid = c.t_arwq_valid && !c.t_arwq_bits.wen;
    c.t_aw_valid = c.t_arwq_valid && c.t_arwq_bits.wen;
    // UserYanker AR/AW (L10160-L10190, L10428-L10458); ids are 0..6.
    const unsigned ar_id = c.t_arwq_bits.id & kIdMask;
    const bool rq_ready = ar_id < kIds && !yq_full(s.y_rq[ar_id], kYankDepth[ar_id]);
    const bool wq_ready = ar_id < kIds && !yq_full(s.y_wq[ar_id], kYankDepth[ar_id]);
    c.y_ar_ok = rq_ready;
    c.y_aw_ok = wq_ready;
    const bool aro_ready = !q2_full(s.b_ar);
    const bool awo_ready = !q2_full(s.b_aw);
    c.y_aro_valid = c.t_ar_valid && c.y_ar_ok;
    c.y_awo_valid = c.t_aw_valid && c.y_aw_ok;
    c.y_in_ar_ready = aro_ready && c.y_ar_ok;
    c.y_in_aw_ready = awo_ready && c.y_aw_ok;
    c.t_ar_ready = c.y_in_ar_ready;
    c.t_aw_ready = c.y_in_aw_ready;
    c.t_w_ready = !q2_full(s.b_w);  // W is a wire through the yanker
    const bool arwq_ready = c.t_arwq_bits.wen ? c.t_aw_ready : c.t_ar_ready;
    // Queue_13 (ARW) and Queue_12 (W) flow-queue handshakes, L10700-L10736.
    {
      const bool empty = !s.t_arw_full;
      bool do_enq = c.t_out_arw_ready && c.t_out_arw_valid;
      bool do_deq = arwq_ready && c.t_arwq_valid;
      if (empty) {
        do_deq = false;
        if (arwq_ready) do_enq = false;
      }
      c.t_arw_enq_fire = do_enq;
      c.t_arw_deq_fire = do_deq;
    }
    {
      const bool empty = !s.t_w_full;
      bool do_enq = c.t_out_w_ready && c.t_out_w_valid;
      bool do_deq = c.t_w_ready && c.t_wq_valid;
      if (empty) {
        do_deq = false;
        if (c.t_w_ready) do_enq = false;
      }
      c.t_w_enq_fire = do_enq;
      c.t_w_deq_fire = do_deq;
    }
    // Buffer enqueues (aw/ar/w).
    c.b_aw_enq_fire = awo_ready && c.y_awo_valid;
    c.b_ar_enq_fire = aro_ready && c.y_aro_valid;
    c.b_w_enq_fire = c.t_w_ready && c.t_wq_valid;
    c.b_aw_enq = c.t_arwq_bits;
    c.b_ar_enq = c.t_arwq_bits;
    c.b_w_enq = c.t_wq_bits;
    // Yanker queue enqueues: valid uses the downstream ready, L10288.
    for (unsigned i = 0; i < kIds; ++i) {
      c.y_rq_enq_fire[i] = c.t_ar_valid && aro_ready && ar_id == i && rq_ready;
      c.y_wq_enq_fire[i] = c.t_aw_valid && awo_ready && ar_id == i && wq_ready;
    }
    // AXI-side A counters (inc), L13399-L13435.
    if (c.t_out_arw_valid && c.t_out_arw_ready) c.t_inc = 1u << c.t_arw.id;

    // ================= 5. Response path ==================================
    // AXI4Buffer B/R dequeue views.
    c.y_bo_valid = !q2_empty(s.b_b);
    c.y_bo = s.b_b.ram[s.b_b.value_1 ? 1 : 0];
    c.y_ro_valid = !q2_empty(s.b_r);
    c.y_ro = s.b_r.ram[s.b_r.value_1 ? 1 : 0];
    // UserYanker echo attach: head of the per-id queue, read regardless of
    // validity (L10236-L10245, L10504-L10511).
    {
      const unsigned rid = c.y_ro.id & 15u;
      if (rid < kIds) {
        const QEcho& q = s.y_rq[rid];
        const Echo& e = q.ram[q.deq_ptr & 7u];
        c.y_ro.echo_size = e.size;
        c.y_ro.echo_source = e.source;
      }
      const unsigned bid = c.y_bo.id & 15u;
      if (bid < kIds) {
        const QEcho& q = s.y_wq[bid];
        const Echo& e = q.ram[q.deq_ptr & 7u];
        c.y_bo_echo = e;
      }
    }
    // Deinterleaver R input side: R = yanker in.r (L8598-L8614, L9115-L9188).
    const unsigned r_id = c.y_ro.id & 15u;
    c.d_r_ready = r_id < kIds && !q8_full(s.d_qs[r_id]);
    c.y_ro_ready = c.d_r_ready;
    // Deinterleaver output towards TLToAXI4 (L8931-L9034).
    c.d_rin_valid = s.d_locked;
    {
      const unsigned did = s.d_deq_id & 15u;
      if (did < kIds) {
        const Q8R& q = s.d_qs[did];
        c.d_rin = q.ram[q.deq_ptr & 7u];
      }
    }
    // TLToAXI4 D side (L13350-L13398): id indexer truncates ids to 3 bits.
    c.t_r_valid = c.d_rin_valid;
    c.t_r = c.d_rin;
    c.t_r.id &= kIdMask;
    c.t_b_valid = c.y_bo_valid;
    c.t_b = c.y_bo;
    c.t_b.id &= kIdMask;
    c.t_b_echo = c.y_bo_echo;
    c.t_r_wins = (c.t_r_valid && s.t_b_delay != 7) || s.t_r_holds_d;
    c.t_in_d_valid = c.t_r_wins ? c.t_r_valid : c.t_b_valid;
    {
      const bool r_denied = s.t_r_first ? (c.t_r.resp == 3) : s.t_r_denied_r;
      const bool r_corrupt = c.t_r.resp != 0;
      const bool b_denied = c.t_b.resp != 0;
      TlD d = zeroed<TlD>();
      if (c.t_r_wins) {
        d.opcode = 1;
        d.size = c.t_r.echo_size;
        d.source = c.t_r.echo_source;
        d.denied = r_denied;
        d.corrupt = r_corrupt || r_denied;
      } else {
        d.opcode = 0;
        d.size = c.t_b_echo.size;
        d.source = c.t_b_echo.source;
        d.denied = b_denied;
        d.corrupt = false;
      }
      d.data = c.t_r.data;  // always the R data, L13398
      c.t_in_d = d;
    }
    compute_tl_return(in, c);
    // TLToAXI4 D readies (L13353-L13358).
    c.t_in_d_ready = kWide?c.d_width[2].input_ready:c.out_d_ready[2];
    c.t_r_ready = c.t_in_d_ready && c.t_r_wins;
    c.t_b_ready = c.t_in_d_ready && !c.t_r_wins;
    c.t_r_fire = c.t_r_valid && c.t_r_ready;
    c.t_b_fire = c.t_b_valid && c.t_b_ready;
    {
      const bool d_last = c.t_r_wins ? c.t_r.last : true;
      const unsigned d_id = (c.t_r_wins ? c.t_r.id : c.t_b.id) & kIdMask;
      if (d_last && c.t_in_d_valid && c.t_in_d_ready) c.t_dec = 1u << d_id;
    }
    // Deinterleaver bookkeeping (L8607-L8930).
    c.d_rin_ready = c.t_r_ready;
    {
      const bool rin_fire = c.d_rin_valid && c.d_rin_ready;
      const unsigned did = s.d_deq_id & 15u;
      const bool r_fire = c.y_ro_valid && c.d_r_ready;
      for (unsigned i = 0; i < kIds; ++i) {
        const bool inc = r_id == i && r_fire && c.y_ro.last;
        const bool dec = did == i && rin_fire && c.d_rin.last;
        c.d_pending_next[i] = (s.d_pending[i] + (inc ? 1u : 0u) - (dec ? 1u : 0u)) & 15u;
        if (c.d_pending_next[i] != 0) c.d_pending_mask |= 1u << i;
        c.d_enq_fire[i] = r_id == i && r_fire;
        c.d_deq_fire[i] = did == i && rin_fire;
      }
      c.d_winner = c.d_pending_mask & (~c.d_pending_mask + 1u);  // lowest set bit
      c.d_rearb = !s.d_locked || (rin_fire && c.d_rin.last);
    }
    // Yanker dequeues (L10284-L10287, L10550-L10552) and buffer B/R deq.
    c.y_bo_ready = c.t_b_ready;  // in.b.ready = TLToAXI4 out.b.ready
    for (unsigned i = 0; i < kIds; ++i) {
      c.y_rq_deq_fire[i] = c.y_ro_valid && c.y_ro_ready && r_id == i && c.y_ro.last;
      c.y_wq_deq_fire[i] = c.y_bo_valid && c.y_bo_ready && (c.y_bo.id & 15u) == i;
    }
    c.b_r_deq_fire = c.y_ro_ready && c.y_ro_valid;
    c.b_b_deq_fire = c.y_bo_ready && c.y_bo_valid;
    // Buffer B/R enqueues from the AXI port; AW/AR/W dequeues to the port.
    c.b_b_enq_fire = !q2_full(s.b_b) && in.mmio_axi_b.valid;
    c.b_b_enq.id = in.mmio_axi_b.id & 15u;
    c.b_b_enq.resp = in.mmio_axi_b.response & 3u;
    c.b_r_enq_fire = !q2_full(s.b_r) && in.mmio_axi_r.valid;
    c.b_r_enq.id = in.mmio_axi_r.id & 15u;
    c.b_r_enq.data = in.mmio_axi_r.data;
    c.b_r_enq.resp = in.mmio_axi_r.response & 3u;
    c.b_r_enq.last = in.mmio_axi_r.last;
    c.b_aw_deq_fire = in.mmio_axi_aw_ready && !q2_empty(s.b_aw);
    c.b_ar_deq_fire = in.mmio_axi_ar_ready && !q2_empty(s.b_ar);
    c.b_w_deq_fire = in.mmio_axi_w_ready && !q2_empty(s.b_w);
  }

  void compute_tl_return(const SystemBusInputs& in, Comb& c) const {
    const State& s = s_;
    // ================= 4. A readies back to the clients ==================
    c.out_a_ready[0] = in.cbus_a_ready;
    c.out_a_ready[1] = in.l2_a_ready;
    c.out_a_ready[2] = c.t_a_ready;
    if constexpr(kWide) {
      for(unsigned port=0;port<3;++port) {
        const auto& held=s.a_width[port].holding?s.a_width[port].saved:c.out_a[port];
        c.a_width[port]=s.a_width[port].evaluate(c.out_a[port],c.out_a_ready[port],(held.address&8)!=0);
        c.out_a_ready[port]=c.a_width[port].input_ready;
      }
    }
    for (int i = 0; i < 2; ++i) {
      bool r = false;
      for (int o = 0; o < 3; ++o)
        if (c.req_a[i][o] && c.out_a_ready[o] && ((c.xa[o].allowed >> i) & 1u))
          r = true;
      c.in_a_ready[i] = r;
    }
    if constexpr(kWide) c.fbus_a_width=s.fbus_a_width.evaluate(c.fbus_input,c.in_a_ready[kFbus] && c.fx_gate);
    c.fx_a_fire=c.in_a_valid[kFbus] && c.in_a_ready[kFbus];

    // xbar D sources: out_2[0] = cbus, out_2[1] = L2, out_2[2] = mmio.
    c.out_d_valid[0] = in.cbus_d.valid;
    c.out_d[0] = tld_in(in.cbus_d, 15u, 1u);
    c.out_d_valid[1] = in.l2_d.valid;
    c.out_d[1] = tld_in(in.l2_d, 7u, 3u);
    c.out_d_valid[2] = c.t_in_d_valid;
    c.out_d[2] = c.t_in_d;
    if constexpr(kWide) for(unsigned port=0;port<3;++port) {
      c.narrow_d[port]=c.out_d[port];c.narrow_d[port].valid=c.out_d_valid[port];
      c.d_width[port]=s.d_width[port].evaluate(c.narrow_d[port],false);
      c.out_d[port]=c.d_width[port].output;c.out_d_valid[port]=c.out_d[port].valid;
    }
    c.beats_do[0] = d_has_data(c.out_d[0].opcode) ? beats1_12(c.out_d[0].size) : 0;
    c.beats_do[1] = d_has_data(c.out_d[1].opcode) ? beats1_6(c.out_d[1].size) : 0;
    c.beats_do[2] = d_has_data(c.out_d[2].opcode) ? beats1_8(c.out_d[2].size) : 0;

    if constexpr(kWide) for(auto& length:c.beats_do) length/=2;
    // ================= 6. xbar D arbiters (N = 3), L22786-L23383 =========
    bool req_d[3][2];
    for (int o = 0; o < 3; ++o) {
      const unsigned src = c.out_d[o].source & 31u;
      req_d[o][kFbus]=kWide?src>=16:src<16;
      req_d[o][kTile]=kWide?src<16:(src>>3)==2;
    }
    c.in_d_ready[kFbus]=in.fbus_d_ready && (!kWide || !s.fbus_d_width.holding);
    c.in_d_ready[kTile]=in.tile_d_ready;
    for (int i = 0; i < 2; ++i) {
      for (int o = 0; o < 3; ++o)
        if (c.out_d_valid[o] && req_d[o][i]) c.vd[i] |= 1u << o;
      c.xd[i] = arb_comb(s.xd[i], 3, c.vd[i], c.beats_do);
      c.in_d_valid[i] = c.xd[i].sink_valid;
      TlD bits = zeroed<TlD>();
      for (int o = 0; o < 3; ++o) {
        if (!((c.xd[i].mux >> o) & 1u)) continue;
        const TlD& b = c.out_d[o];
        bits.opcode |= b.opcode;
        bits.param |= b.param;
        bits.size |= b.size;
        bits.source |= b.source;
        bits.sink |= b.sink;
        bits.denied = bits.denied || b.denied;
        bits.data |= b.data;
        bits.data_hi |= b.data_hi;
        bits.corrupt = bits.corrupt || b.corrupt;
      }
      c.in_d[i] = bits;
    }
    c.in_d[kFbus].source &= 15u;  // fbus: 4-bit source, L20701
    c.in_d[kTile].source &= boomcfg::TILE_SOURCE_MASK;
    for (int o = 0; o < 3; ++o) {
      bool r = false;
      for (int i = 0; i < 2; ++i)
        if (req_d[o][i] && c.in_d_ready[i] && ((c.xd[i].allowed >> o) & 1u))
          r = true;
      c.out_d_ready[o] = r;
    }
    TlD fbus_d=c.in_d[kFbus];fbus_d.valid=c.in_d_valid[kFbus];
    if constexpr(kWide) {
      const auto& held=s.fbus_d_width.holding?s.fbus_d_width.saved:fbus_d;
      const bool select=held.size<4 && (s.fbus_d_width.second?s.fbus_held_upper:s.fbus_source_upper[held.source&15]);
      c.fbus_d_width=s.fbus_d_width.evaluate(fbus_d,in.fbus_d_ready,select);
      fbus_d=c.fbus_d_width.output;
      for(unsigned port=0;port<3;++port) c.d_width[port]=s.d_width[port].evaluate(c.narrow_d[port],c.out_d_ready[port]);
    }
    const auto& fixer_d=c.in_d[kFbus];
    c.fx_d_beats1=d_has_data(fixer_d.opcode)?beats1_12(fixer_d.size)/(kWide?2:1):0;
    c.fx_d_first=s.fx_d_first_counter==0 && fixer_d.opcode!=6;
    c.fx_d_fire=c.in_d_valid[kFbus] && c.in_d_ready[kFbus];
  }

  static bool yq_full(const QEcho& q, unsigned depth) {
    return depth == 1 ? q.maybe_full
                      : (q.enq_ptr == q.deq_ptr && q.maybe_full);
  }
  static bool q8_full(const Q8R& q) {
    return q.enq_ptr == q.deq_ptr && q.maybe_full;
  }
  static void yq_tick(QEcho& q, unsigned depth, bool enq_fire, const Echo& e,
                      bool deq_fire, bool reset) {
    if (depth == 1) {
      if (enq_fire) q.ram[0] = e;
      if (enq_fire != deq_fire) q.maybe_full = enq_fire;
      if (reset) q.maybe_full = false;
      return;
    }
    if (enq_fire) {
      q.ram[q.enq_ptr & 7u] = e;
      q.enq_ptr = static_cast<std::uint8_t>((q.enq_ptr + 1u) & 7u);
    }
    if (deq_fire) q.deq_ptr = static_cast<std::uint8_t>((q.deq_ptr + 1u) & 7u);
    if (enq_fire != deq_fire) q.maybe_full = enq_fire;
    if (reset) {
      q.enq_ptr = q.deq_ptr = 0;
      q.maybe_full = false;
    }
  }
  static void q8_tick(Q8R& q, bool enq_fire, const Rb& e, bool deq_fire,
                      bool reset) {
    if (enq_fire) {
      q.ram[q.enq_ptr & 7u] = e;
      q.enq_ptr = static_cast<std::uint8_t>((q.enq_ptr + 1u) & 7u);
    }
    if (deq_fire) q.deq_ptr = static_cast<std::uint8_t>((q.deq_ptr + 1u) & 7u);
    if (enq_fire != deq_fire) q.maybe_full = enq_fire;
    if (reset) {
      q.enq_ptr = q.deq_ptr = 0;
      q.maybe_full = false;
    }
  }

  void tick(const SystemBusInputs& in) {
    // evaluate() already computed this exact PRE state and input combination.
    const Comb& c = evaluated_comb_;
    State& s = s_;
    const bool reset = in.reset;

    if constexpr(kWide) {
      TlD fbus_d=c.in_d[kFbus];fbus_d.valid=c.in_d_valid[kFbus];
      const auto& held=s.fbus_d_width.holding?s.fbus_d_width.saved:fbus_d;
      if(!s.fbus_d_width.second) s.fbus_held_upper=s.fbus_source_upper[held.source&15];
      if(c.fbus_input.valid && c.fbus_a_width.input_ready) s.fbus_source_upper[c.fbus_input.source&15]=(c.fbus_input.address&8)!=0;
      s.fbus_a_width.commit(c.fbus_input,c.fbus_a_width,reset);
      s.fbus_d_width.commit(fbus_d,in.fbus_d_ready,c.fbus_d_width,reset);
      const bool ready[3]={in.cbus_a_ready,in.l2_a_ready,c.t_a_ready};
      for(unsigned port=0;port<3;++port) {
        s.a_width[port].commit(c.out_a[port],ready[port],c.a_width[port],reset);
        s.d_width[port].commit(c.narrow_d[port],c.d_width[port],reset);
      }
      s.c_width.commit(c.c_input,in.l2_c_ready,c.c_width,reset);
    }

    // ---- fixer lane 0 (L6808-L6913) ----
    {
      const TlA fa = fbus_a_in(in.fbus_a);
      if (c.fx_a_fire)
        s.fx_a_first_counter = static_cast<std::uint16_t>(
            (c.fx_a_first ? c.fx_a_beats1 : (s.fx_a_first_counter - 1u)) & 0x1ffu);
      if (c.fx_d_fire)
        s.fx_d_first_counter = static_cast<std::uint16_t>(
            ((s.fx_d_first_counter == 0) ? c.fx_d_beats1
                                         : (s.fx_d_first_counter - 1u)) & 0x1ffu);
      if (c.fx_a_first && c.fx_a_fire) {
        if (c.fx_a_notfifo) s.fx_flight &= static_cast<std::uint16_t>(~(1u << (fa.source & 15u)));
        else s.fx_flight |= static_cast<std::uint16_t>(1u << (fa.source & 15u));
      }
      if (c.fx_d_first && c.fx_d_fire)
        s.fx_flight &= static_cast<std::uint16_t>(~(1u << (c.in_d[kFbus].source & 15u)));
      if (c.fx_a_fire && c.fx_sel0 && !c.fx_a_notfifo)
        s.fx_stalls_id = static_cast<std::uint8_t>(c.fx_a_id);
      if (c.fx_a_fire && c.fx_sel1 && !c.fx_a_notfifo)
        s.fx_stalls_id_1 = static_cast<std::uint8_t>(c.fx_a_id);
      if (reset) {
        s.fx_a_first_counter = 0;
        s.fx_d_first_counter = 0;
        s.fx_flight = 0;
      }
    }

    // ---- xbar arbiters ----
    for (int o = 0; o < 3; ++o)
      arb_tick(s.xa[o], 2, c.xa[o], c.va[o], c.out_a_ready[o], reset);
    for (int i = 0; i < 2; ++i)
      arb_tick(s.xd[i], 3, c.xd[i], c.vd[i], c.in_d_ready[i], reset);

    if (!c.mmio_evaluated) return;

    // ---- TLToAXI4 (L13193-L13196, L13263-L13267, L13333-L13371, L13431-L13545) ----
    {
      if (c.t_a_valid && c.t_a_ready) {
        s.t_counter = static_cast<std::uint8_t>(
            (c.t_a_first ? c.t_beats1 : (s.t_counter - 1u)) & 0x1fu);
        s.t_doneAW = !c.t_a_last;
      }
      if (s.t_r_first) s.t_r_denied_r = c.t_r.resp == 3;
      if (c.t_r_fire) {
        s.t_r_holds_d = !c.t_r.last;
        s.t_r_first = c.t_r.last;
      }
      s.t_b_delay = static_cast<std::uint8_t>(
          (c.t_b_valid && !c.t_b_ready) ? ((s.t_b_delay + 1u) & 7u) : 0u);
      for (unsigned k = 0; k < kIds; ++k) {
        const unsigned inc = (c.t_inc >> k) & 1u, dec = (c.t_dec >> k) & 1u;
        s.t_count[k] = static_cast<std::uint8_t>((s.t_count[k] + inc - dec) & (2*kYankDepth[k]-1));
      }
      for(unsigned id=0;id<kIds;++id) if(kYankDepth[id]>1 && (c.t_inc&(1u<<id))) s.t_write[id]=c.t_arw.wen;
      if (c.t_arw_enq_fire) s.t_arw_ram = c.t_arw;
      if (c.t_arw_enq_fire != c.t_arw_deq_fire) s.t_arw_full = c.t_arw_enq_fire;
      if (c.t_w_enq_fire) s.t_w_ram = c.t_w_bits;
      if (c.t_w_enq_fire != c.t_w_deq_fire) s.t_w_full = c.t_w_enq_fire;
      if (reset) {
        s.t_counter = 0;
        s.t_doneAW = false;
        s.t_r_holds_d = false;
        s.t_r_first = true;
        for (unsigned k = 0; k < kIds; ++k) s.t_count[k] = 0;
        s.t_arw_full = false;
        s.t_w_full = false;
      }
    }

    // ---- deinterleaver (L8620, L8901-L8930, queue edges) ----
    {
      for (unsigned i = 0; i < kIds; ++i)
        s.d_pending[i] = static_cast<std::uint8_t>(c.d_pending_next[i]);
      if (c.d_rearb) {
        s.d_locked = c.d_pending_mask != 0;
        unsigned id = 0;
        for (unsigned i = 0; i < kIds; ++i)
          if (c.d_winner & (1u << i)) id = i;
        s.d_deq_id = static_cast<std::uint8_t>(id);
      }
      for (unsigned i = 0; i < kIds; ++i)
        q8_tick(s.d_qs[i], c.d_enq_fire[i], c.y_ro, c.d_deq_fire[i], reset);
      if (reset) {
        s.d_locked = false;
        for (unsigned i = 0; i < kIds; ++i) s.d_pending[i] = 0;
      }
    }

    // ---- yanker queues ----
    {
      Echo e = zeroed<Echo>();
      e.size = c.t_arwq_bits.echo_size;
      e.source = c.t_arwq_bits.echo_source;
      for (unsigned i = 0; i < kIds; ++i) {
        yq_tick(s.y_rq[i], kYankDepth[i], c.y_rq_enq_fire[i], e,
                c.y_rq_deq_fire[i], reset);
        yq_tick(s.y_wq[i], kYankDepth[i], c.y_wq_enq_fire[i], e,
                c.y_wq_deq_fire[i], reset);
      }
    }

    // ---- AXI4Buffer queues ----
    q2_tick(s.b_aw, c.b_aw_enq_fire, c.b_aw_enq, c.b_aw_deq_fire, reset);
    q2_tick(s.b_w, c.b_w_enq_fire, c.b_w_enq, c.b_w_deq_fire, reset);
    q2_tick(s.b_b, c.b_b_enq_fire, c.b_b_enq, c.b_b_deq_fire, reset);
    q2_tick(s.b_ar, c.b_ar_enq_fire, c.b_ar_enq, c.b_ar_deq_fire, reset);
    q2_tick(s.b_r, c.b_r_enq_fire, c.b_r_enq, c.b_r_deq_fire, reset);
  }

  bool mmio_quiescent() const {
    const auto& s = s_;
    if (s.xa[2].beats_left || s.t_counter || s.t_doneAW || s.t_r_holds_d ||
        s.t_b_delay || s.t_w_full || s.t_arw_full || s.d_locked ||
        !q2_empty(s.b_aw) || !q2_empty(s.b_w) || !q2_empty(s.b_b) ||
        !q2_empty(s.b_ar) || !q2_empty(s.b_r)) return false;
    for (unsigned i = 0; i < kIds; ++i) {
      const auto& q = s.d_qs[i];
      const auto empty_echo = [](const QEcho& e, unsigned depth) {
        return depth == 1 ? !e.maybe_full : e.enq_ptr == e.deq_ptr && !e.maybe_full;
      };
      if (s.t_count[i] || s.d_pending[i] || q.enq_ptr != q.deq_ptr || q.maybe_full ||
          !empty_echo(s.y_rq[i], kYankDepth[i]) || !empty_echo(s.y_wq[i], kYankDepth[i])) return false;
    }
    return true;
  }

  static void fill_axi_aw(MbusAxiAw& o, bool valid, const Arw& a) {
    o.valid = valid;
    o.id = a.id & 15u;
    o.address = a.addr & 0x7fffffffu;
    o.length = a.len;
    o.size = a.size & 7u;
    o.burst = a.burst & 3u;
    o.lock = a.lock;
    o.cache = a.cache & 15u;
    o.protection = a.prot & 7u;
    o.qos = a.qos & 15u;
  }

  void refresh_outputs(const SystemBusInputs& in) {
    compute_comb(in, evaluated_comb_);
    Comb& c = evaluated_comb_;
    const State& s = s_;
    SystemBusOutputs& o = outputs_;
    o.tile_a_ready = c.in_a_ready[kTile];
    o.fbus_a_ready = kWide?c.fbus_a_width.input_ready:(c.in_a_ready[kFbus] && c.fx_gate);
    // B: single source (L2), routed to the tile when source is 16..23.
    {
      const unsigned bsrc = in.l2_b.source & 31u;
      const bool to_tile = kWide?bsrc<16:(bsrc>>3)==2;
      o.tile_b.valid = in.l2_b.valid && to_tile;
      o.tile_b.opcode = in.l2_b.opcode & 7u;
      o.tile_b.param = in.l2_b.param & 3u;
      o.tile_b.size = in.l2_b.size & 7u;
      o.tile_b.source = static_cast<std::uint8_t>(bsrc & boomcfg::TILE_SOURCE_MASK);
      o.tile_b.address = in.l2_b.address;
      o.tile_b.mask = in.l2_b.mask;
      o.tile_b.data = in.l2_b.data;
      o.tile_b.corrupt = in.l2_b.corrupt;
      o.l2_b_ready = to_tile ? in.tile_b_ready : false;
    }
    // C and E: wires between the tile and the L2 port.
    o.tile_c_ready = in.l2_c_ready;
    o.l2_c.valid = in.tile_c.valid;
    o.l2_c.opcode = in.tile_c.opcode & 7u;
    o.l2_c.param = in.tile_c.param & 7u;
    o.l2_c.size = in.tile_c.size & 7u;
    o.l2_c.source = static_cast<std::uint8_t>((in.tile_c.source & 7u) | (kWide?0u:0x10u));
    o.l2_c.address = in.tile_c.address;
    o.l2_c.bufferable = false;
    o.l2_c.modifiable = false;
    o.l2_c.readalloc = false;
    o.l2_c.writealloc = false;
    o.l2_c.privileged = true;
    o.l2_c.secure = true;
    o.l2_c.fetch = false;
    o.l2_c.data = in.tile_c.data;
    o.l2_c.data_hi = kWide?in.tile_c.data_hi:0;
    o.l2_c.corrupt = in.tile_c.corrupt;
    if constexpr(kWide) {
      c.c_input=o.l2_c;
      const auto& held=s.c_width.holding?s.c_width.saved:c.c_input;
      c.c_width=s.c_width.evaluate(c.c_input,in.l2_c_ready,(held.address&8)!=0);
      o.l2_c=c.c_width.output;o.tile_c_ready=c.c_width.input_ready;
    }
    o.tile_e_ready = in.l2_e_ready;
    o.l2_e.valid = in.tile_e.valid;
    o.l2_e.sink = in.tile_e.sink & 3u;
    // D towards the clients.
    const auto put_d = [](CoherentTlD& d, bool valid, const TlD& b) {
      d.valid = valid;
      d.opcode = b.opcode;
      d.param = b.param;
      d.size = b.size;
      d.source = b.source;
      d.sink = b.sink;
      d.denied = b.denied;
      d.data = b.data;
      d.data_hi = b.data_hi;
      d.corrupt = b.corrupt;
    };
    put_d(o.tile_d,c.in_d_valid[kTile],c.in_d[kTile]);
    if constexpr(kWide) o.fbus_d=c.fbus_d_width.output;
    else put_d(o.fbus_d,c.in_d_valid[kFbus],c.in_d[kFbus]);
    // A towards cbus and L2.
    const auto put_a = [](MbusTlA& a, bool valid, const TlA& b) {
      a.valid = valid;
      a.opcode = b.opcode;
      a.param = b.param;
      a.size = b.size;
      a.source = b.source;
      a.address = b.address;
      a.bufferable = b.bufferable;
      a.modifiable = b.modifiable;
      a.readalloc = b.readalloc;
      a.writealloc = b.writealloc;
      a.privileged = b.privileged;
      a.secure = b.secure;
      a.fetch = b.fetch;
      a.mask = b.mask;
      a.data = b.data;
      a.data_hi = b.data_hi;
      a.corrupt = b.corrupt;
    };
    put_a(o.cbus_a,kWide?c.a_width[0].output.valid:c.out_a_valid[0],kWide?c.a_width[0].output:c.out_a[0]);
    put_a(o.l2_a,kWide?c.a_width[1].output.valid:c.out_a_valid[1],kWide?c.a_width[1].output:c.out_a[1]);
    o.cbus_d_ready=kWide?c.d_width[0].input_ready:c.out_d_ready[0];
    o.l2_d_ready=kWide?c.d_width[1].input_ready:c.out_d_ready[1];
    // AXI port = AXI4Buffer dequeue faces / enqueue readies.
    fill_axi_aw(o.mmio_axi_aw, !q2_empty(s.b_aw), s.b_aw.ram[s.b_aw.value_1 ? 1 : 0]);
    fill_axi_aw(o.mmio_axi_ar, !q2_empty(s.b_ar), s.b_ar.ram[s.b_ar.value_1 ? 1 : 0]);
    {
      const Wb& w = s.b_w.ram[s.b_w.value_1 ? 1 : 0];
      o.mmio_axi_w.valid = !q2_empty(s.b_w);
      o.mmio_axi_w.data = w.data;
      o.mmio_axi_w.strobe = w.strb;
      o.mmio_axi_w.last = w.last;
    }
    o.mmio_axi_b_ready = !q2_full(s.b_b);
    o.mmio_axi_r_ready = !q2_full(s.b_r);
  }

  bool busy() const {
    if(!mmio_quiet_ || s_.fx_a_first_counter || s_.fx_d_first_counter || s_.fx_flight) return true;
    for(const auto& arb:s_.xa) if(arb.beats_left) return true;
    for(const auto& arb:s_.xd) if(arb.beats_left) return true;
    if constexpr(kWide) {
      if(s_.fbus_a_width.second || s_.fbus_d_width.holding || s_.c_width.holding) return true;
      for(unsigned port=0;port<3;++port) if(s_.a_width[port].holding || s_.d_width[port].second) return true;
    }
    const auto& in=pending_inputs_;
    return in.tile_a.valid || in.tile_c.valid || in.tile_e.valid || in.fbus_a.valid || in.l2_b.valid || in.l2_d.valid || in.cbus_d.valid || in.mmio_axi_b.valid || in.mmio_axi_r.valid;
  }

  bool mmio_quiet_ = true;
  Comb evaluated_comb_{};
  State s_{};
  unsigned drain_=0;
  SystemBusInputs last_inputs_{};
  SystemBusInputs applied_inputs_{};
  SystemBusInputs pending_inputs_{};
  SystemBusOutputs outputs_{};
  bool pending_valid_ = false;
  bool active_ = false;
  std::uint64_t eval_count_ = 0;
  std::uint64_t skipped_count_ = 0;
#ifdef CHISA_NATIVE_PROTOCOL_TEST
 public:
  const auto& evaluated_for_test() const {return evaluated_comb_;}
#endif
};

}  // namespace chisa::boom_system::components
