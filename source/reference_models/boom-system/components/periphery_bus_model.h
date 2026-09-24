#pragma once
// Software peripheral fabric: atomic read/modify/write transactions, buffered
// request/response channels, FIFO ordering domains and four device fragmenters.
// Geometry and the observation bindings are separate from protocol execution.
// The former Small-only procedural model supplied the transaction structure;
// address routing, arbitration, AMO arithmetic and fragmentation now use
// software algorithms, with no generated or extracted RTL implementation.

#include <array>
#include <cstdint>
#include <cstring>

#include "../protocol/peripheral.h"

namespace chisa::boom_system::components {
using protocol::MbusTlA;
using protocol::PeripheralTlD;
using protocol::PeripheralManagerInputs;
using protocol::PeripheralManagerOutputs;
using protocol::PeripheryBusInputs;
using protocol::PeripheryBusOutputs;

class PeripheryBusModel {
 public:

  explicit PeripheryBusModel(unsigned fifo_source_base=0) : fifo_source_base_(fifo_source_base) {
    refresh_outputs(last_inputs_);
  }

  const PeripheryBusOutputs& outputs() const { return outputs_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return eval_count_; }
  std::uint64_t skipped_count() const { return skipped_count_; }

  /** Combinational evaluation from the pre-edge register image. */
  const PeripheryBusOutputs& evaluate(const PeripheryBusInputs& inputs) {
    pending_inputs_ = inputs;
    pending_valid_ = true;
    if (inputs != applied_inputs_) {
      refresh_outputs(inputs);
      applied_inputs_ = inputs;
    }
    return outputs_;
  }

  /** One clock edge with the last evaluated inputs, then a combinational
    * refresh.  Skipped when no register moved on the previous edge and the
    * inputs are unchanged: next state is a function of (state, inputs). */
  void commit_evaluated() {
    if (!pending_valid_) return;
    if (!active_ && pending_inputs_ == last_inputs_) {
      ++skipped_count_;
      pending_valid_ = false;
      return;
    }
    if (pending_inputs_ != last_inputs_) drain_cycles_=2;
    tick(pending_inputs_);
    if (drain_cycles_) --drain_cycles_;
    active_ = busy() || drain_cycles_!=0;
    refresh_outputs(pending_inputs_);
    last_inputs_ = pending_inputs_;
    applied_inputs_ = pending_inputs_;
    pending_valid_ = false;
    ++eval_count_;
  }

  void commit(const PeripheryBusInputs& inputs) {
    evaluate(inputs);
    commit_evaluated();
  }

 public:
  // ---- payload records (natural widths, masked at the producers) --------
  struct TlA {
    std::uint8_t opcode = 0, param = 0, size = 0, source = 0;
    std::uint32_t address = 0;
    std::uint8_t mask = 0;
    std::uint64_t data = 0;
    bool corrupt = false;
  };
  struct TlD {
    std::uint8_t opcode = 0, param = 0, size = 0;
    std::uint16_t source = 0;
    bool sink = false, denied = false;
    std::uint64_t data = 0;
    bool corrupt = false;
  };
  /** Chisel Queue(x, 2), flow = pipe = false.  FIR Queue_23/24/26/27. */
  struct Queue2A {
    bool value = false, value_1 = false, maybe_full = false;
    TlA ram[2];
  };
  struct Queue2D {
    bool value = false, value_1 = false, maybe_full = false;
    TlD ram[2];
  };
  struct Repeater {
    bool full = false;
    TlA saved;
  };
  struct Fragmenter {
    std::uint8_t acknum = 0;   // 3 bits, reset 0
    std::uint8_t dOrig = 0;    // 3 bits, no reset
    bool dToggle = false;      // reset 0
    std::uint8_t gennum = 0;   // 3 bits, reset 0
    bool aToggle_r = false;    // no reset
    Repeater rep;
  };
  struct State {
    // TLAtomicAutomata_1
    std::uint8_t cam_state = 0;   // 2 bits: FREE 0, ACK 1, AMO 2, GET 3
    TlA cam_a;                    // no reset
    std::uint64_t cam_d_data = 0; // no reset
    bool cam_d_denied = false, cam_d_corrupt = false;
    std::uint16_t at_beats_left = 0;  // 9 bits
    bool at_state0 = false, at_state1 = false;
    std::uint16_t at_d_first_counter = 0;  // 9 bits
    // TLBuffer_4
    Queue2A buf_a;  // Queue_23
    Queue2D buf_d;  // Queue_24
    // TLFIFOFixer_3
    std::uint16_t fx_a_first_counter = 0, fx_d_first_counter = 0;  // 9 bits
    std::uint32_t fx_flight = 0;   // 21 bits
    std::uint8_t fx_stalls_id = 0, fx_stalls_id_1 = 0;  // 3 bits, no reset
    // TLXbar_5 D arbiter
    std::uint16_t xb_beats_left = 0;  // 9 bits
    std::uint8_t xb_readys_mask = 0;  // 5 bits, reset 0x1f
    std::uint8_t xb_state = 0;        // 5 bits
    // ErrorDeviceWrapper: TLBuffer_5 + TLError
    Queue2A err_buf_a;  // Queue_26 (address 14 bits)
    Queue2D err_buf_d;  // Queue_27
    bool err_q_maybe_full = false;  // Queue_25 (depth 1)
    TlA err_q_ram;
    bool err_idle = false;  // reset 1, never written otherwise
    std::uint16_t err_a_last_counter = 0, err_counter = 0;  // 9 bits
    // Fragmenters: 0 plic, 1 clint, 2 debug, 3 bootrom
    Fragmenter frag[4];
  };

  const State& state() const { return s_; }

 private:
  static constexpr int kPlic = 0, kClint = 1, kDebug = 2, kBootrom = 3;
  static constexpr std::uint32_t kAddressMask[4] = {0x0fffffffu, 0x03ffffffu,
                                                    0x00000fffu, 0x0001ffffu};
  static constexpr std::uint32_t kErrorAddressMask = 0x3fffu;

  // ---- helpers ---------------------------------------------------------
  /** Every record is created zero-filled (padding included) so the
    * whole-state memcmp behind active() never sees stale padding. */
  template <class T>
  static T zeroed() {
    T t;
    std::memset(static_cast<void*>(&t), 0, sizeof(T));
    return t;
  }
  // Device order is error, interrupt controller, timer, debug, boot ROM.
  // These are address-map regions, not a minimized hardware decode equation.
  static unsigned route(std::uint32_t address) {
    struct Region {std::uint32_t begin,bytes;};
    static constexpr Region regions[]={{0x3000,0x1000},{0xc000000,0x4000000},
      {0x2000000,0x10000},{0,0x1000},{0x10000,0x10000}};
    for (unsigned i=0;i<5;++i)
      if (address>=regions[i].begin && address-regions[i].begin<regions[i].bytes) return i+1;
    return 1; // An unmapped software request receives an access error.
  }
  static bool a_has_data(unsigned opcode) { return (opcode & 4u) == 0; }
  static bool d_has_data(unsigned opcode) { return (opcode & 1u) != 0; }
  /** not(bits(dshl(mask, size))) >> 3 with a 12-bit mask: beats - 1. */
  static unsigned beats1_12(unsigned size) {
    return (((1u << size) - 1u) & 0xfffu) >> 3;
  }
  static unsigned beats1_6(unsigned size) {
    return (((1u << size) - 1u) & 0x3fu) >> 3;
  }
  static unsigned oh1_6(unsigned size) { return ((1u << size) - 1u) & 0x3fu; }
  static unsigned oh1_3(unsigned size) { return ((1u << size) - 1u) & 0x7u; }
  /** TileLink full mask for an aligned transfer on an 8-byte beat. */
  static unsigned tl_mask(std::uint32_t address, unsigned size) {
    if (size >= 3) return 0xffu;
    if (size == 2) return 0x0fu << (((address >> 2) & 1u) * 4u);
    if (size == 1) return 0x03u << (((address >> 1) & 3u) * 2u);
    return 1u << (address & 7u);
  }
  static TlA truncate_a(const TlA& a, unsigned size_mask,
                        std::uint32_t address_mask) {
    TlA out = zeroed<TlA>();
    out = a;
    out.size = static_cast<std::uint8_t>(a.size & size_mask);
    out.address = a.address & address_mask;
    return out;
  }

  // ---- per-cycle combinational values --------------------------------
  struct FragComb {
    // D (device -> xbar)
    bool d_first = false;
    std::uint8_t d_first_size = 0, d_first_acknum = 0, ack_decrement = 0;
    bool d_toggle_next = false;
    bool drop = false;
    bool out_d_ready = false;   // to the device
    bool in_d_valid = false;    // to the xbar
    TlD in_d;                   // to the xbar (size/source rewritten)
    bool d_fire = false;        // out.d.ready && out.d.valid
    // A (xbar -> device)
    bool a_first = false;
    std::uint8_t new_gennum = 0;
    bool repeat = false;
    bool enq_fire = false, deq_fire = false;
    bool out_a_valid = false;
    TlA out_a;                  // device face (source is out_a_source9)
    std::uint16_t out_a_source9 = 0;
    bool in_a_ready = false;    // to the xbar
    bool a_fire = false;        // out.a.ready && out.a.valid
  };
  struct Comb {
    // atomics
    bool cam_free = false, cam_amo = false, cam_abusy = false,
         cam_dmatch = false;
    bool a_is_supported = false, a_allow = false;
    bool source_i_valid = false, source_i_ready = false;
    bool source_c_valid = false, source_c_ready = false;
    bool at_idle = false, at_latch = false;
    bool winner0 = false, winner1 = false;
    unsigned init_beats = 0;
    bool at_out_a_valid = false;
    TlA at_out_a;               // into buf_a
    bool in_a_ready = false;    // upstream_a_ready
    bool d_first = false;
    unsigned d_beats1 = 0;
    bool d_cam_sel = false, d_ackd = false;
    bool d_drop = false, d_replace = false;
    bool buf_d_deq_fire = false;
    bool in_d_valid = false;    // upstream_d.valid
    TlD in_d;                   // upstream_d
    // buf_a / buf_d
    bool buf_a_enq_fire = false, buf_a_deq_fire = false;
    bool buf_d_enq_fire = false;
    // fixer
    bool fx_stall = false, fx_a_fire = false, fx_d_fire = false;
    bool fx_a_first = false, fx_d_first = false;
    unsigned fx_a_beats1 = 0, fx_d_beats1 = 0, fx_a_id = 0;
    bool fx_sel0 = false, fx_sel1 = false;
    TlA fx_a;                   // buf_a.deq.bits
    TlD fx_d;                   // xbar in.d.bits
    // out_xbar
    bool req[5] = {};
    bool xb_idle = false, xb_latch = false;
    unsigned xb_valids = 0, xb_readys = 0, xb_winner = 0;
    unsigned xb_init_beats = 0;
    bool xb_in_d_valid = false;
    bool xb_sink_ready = false;
    bool out_d_ready[5] = {};
    // error device
    bool err_buf_a_enq_fire = false, err_buf_a_deq_fire = false;
    bool err_q_enq_fire = false, err_q_deq_fire = false;
    bool err_da_fire = false;
    bool err_a_last = false, err_da_first = false;
    unsigned err_a_beats1 = 0, err_da_beats1 = 0;
    TlD err_da;
    bool err_buf_d_enq_fire = false, err_buf_d_deq_fire = false;
    FragComb frag[4];
  };

  static TlA to_tla(const MbusTlA& a) {
    TlA out = zeroed<TlA>();
    out.opcode = a.opcode & 7u;
    out.param = a.param & 7u;
    out.size = a.size & 15u;
    out.source = a.source & 31u;
    out.address = a.address & 0x0fffffffu;
    out.mask = a.mask;
    out.data = a.data;
    out.corrupt = a.corrupt;
    return out;
  }
  static TlD to_tld(const PeripheralTlD& d) {
    TlD out = zeroed<TlD>();
    out.opcode = d.opcode & 7u;
    out.param = d.param & 3u;
    out.size = d.size & 3u;
    out.source = d.source & 0x1ffu;
    out.sink = d.sink;
    out.denied = d.denied;
    out.data = d.data;
    out.corrupt = d.corrupt;
    return out;
  }

  /** TLFragmenter (FIR L19105-19344 for plic; _1/_2 identical apart from
    * the address width; _3 = bootrom folds dHasData = 1, aHasData = 0). */
  void frag_comb(int i, const Fragmenter& f, bool in_a_valid, const TlA& in_a,
                 bool out_a_ready, bool out_d_valid, const TlD& out_d,
                 bool in_d_ready, FragComb& c) const {
    const bool bootrom = i == kBootrom;
    // ---- D path ----
    const unsigned dsrc = out_d.source & 0x1ffu;
    const unsigned dsz = out_d.size & 3u;
    const unsigned d_fragnum = dsrc & 7u;
    c.d_first = f.acknum == 0;
    const bool d_last = d_fragnum == 0;
    const unsigned dsize_oh = (1u << dsz) & 0xfu;
    const unsigned dsize_oh1 = oh1_3(dsz);
    const bool d_has = bootrom ? true : d_has_data(out_d.opcode);
    c.d_first_acknum = static_cast<std::uint8_t>(d_fragnum);
    c.ack_decrement = static_cast<std::uint8_t>(d_has ? 1u : (dsize_oh >> 3));
    const unsigned x = ((d_fragnum << 3) | dsize_oh1) & 0x3fu;
    unsigned original_size=0;
    for(unsigned span=x;span!=0;span>>=1) ++original_size;
    c.d_first_size=static_cast<std::uint8_t>(original_size);
    c.d_toggle_next = ((dsrc >> 3) & 1u) != 0;
    c.drop = bootrom ? false : (!d_has && !d_last);
    c.out_d_ready = in_d_ready || c.drop;
    c.in_d_valid = out_d_valid && !c.drop;
    c.in_d = out_d;
    c.in_d.source = static_cast<std::uint16_t>((dsrc >> 4) & 0x1fu);
    c.in_d.size = c.d_first ? c.d_first_size : f.dOrig;
    c.d_fire = c.out_d_ready && out_d_valid;
    // ---- A path ----
    const bool deq_valid = in_a_valid || f.rep.full;
    const TlA& ia = f.rep.full ? f.rep.saved : in_a;
    const unsigned ia_size = ia.size & 7u;
    const unsigned a_frag = ia_size > 3 ? 3u : ia_size;
    const unsigned a_orig_oh1 = oh1_6(ia_size);
    const bool a_has = bootrom ? false : a_has_data(ia.opcode);
    c.a_first = f.gennum == 0;
    const unsigned old_gennum1 =
        c.a_first ? (a_orig_oh1 >> 3) : ((f.gennum - 1u) & 7u);
    c.new_gennum = static_cast<std::uint8_t>(old_gennum1);
    const unsigned a_fragnum = old_gennum1;
    const bool toggle_sel = c.a_first ? f.dToggle : f.aToggle_r;
    c.repeat = !a_has && a_fragnum != 0;
    c.out_a_valid = deq_valid;
    c.out_a.opcode = ia.opcode;
    c.out_a.param = ia.param;
    c.out_a.corrupt = ia.corrupt;
    const unsigned offset = ((beats1_6(ia_size)-old_gennum1)&7u)*8;
    c.out_a.address = (ia.address | offset) & kAddressMask[i];
    c.out_a_source9 = static_cast<std::uint16_t>(
        ((ia.source & 0x1fu) << 4) | ((toggle_sel ? 0u : 1u) << 3) | a_fragnum);
    c.out_a.size = static_cast<std::uint8_t>(a_frag);
    c.out_a.data = in_a.data;
    c.out_a.mask = f.rep.full ? 0xffu : in_a.mask;
    const bool enq_ready = out_a_ready && !f.rep.full;
    c.in_a_ready = enq_ready;
    c.enq_fire = enq_ready && in_a_valid;
    c.deq_fire = out_a_ready && deq_valid;
    c.a_fire = c.deq_fire;
  }

  /** Whole-bus combinational evaluation from the pre-edge image. */
  void compute_comb(const PeripheryBusInputs& in, Comb& c) const {
    c = zeroed<Comb>();
    const State& s = s_;

    // ================= A path, device side first ===================
    // TLBuffer_4 A queue (Queue_23) deq face.
    const bool buf_a_deq_valid = !(s.buf_a.value == s.buf_a.value_1 &&
                                   !s.buf_a.maybe_full);
    const TlA& fx_a = s.buf_a.ram[s.buf_a.value_1 ? 1 : 0];
    c.fx_a = fx_a;
    // TLFIFOFixer_3 stall.
    c.fx_a_id = route(fx_a.address);
    const bool a_no_domain = c.fx_a_id == 0;
    c.fx_a_beats1 = a_has_data(fx_a.opcode) ? beats1_12(fx_a.size) : 0;
    c.fx_a_first = s.fx_a_first_counter == 0;
    c.fx_sel0 = (fx_a.source >> 3) == fifo_source_base_/8;
    c.fx_sel1 = (fx_a.source >> 3) == fifo_source_base_/8+1;
    const bool stalls_0 = c.fx_sel0 && c.fx_a_first &&
                          ((s.fx_flight >> fifo_source_base_) & 0xffu) != 0 &&
                          (a_no_domain || s.fx_stalls_id != c.fx_a_id);
    const bool stalls_1 = c.fx_sel1 && c.fx_a_first &&
                          ((s.fx_flight >> (fifo_source_base_+8)) & 0xffu) != 0 &&
                          (a_no_domain || s.fx_stalls_id_1 != c.fx_a_id);
    c.fx_stall = stalls_0 || stalls_1;
    const bool xb_in_a_valid = buf_a_deq_valid && !c.fx_stall;
    // TLXbar_5 A demux.
    for(unsigned i=0;i<5;++i) c.req[i]=c.fx_a_id==i+1;
    // out_0: error device buffer (Queue_26) enq.
    const bool err_buf_a_full = s.err_buf_a.value == s.err_buf_a.value_1 &&
                                s.err_buf_a.maybe_full;
    const bool out0_a_ready = !err_buf_a_full;
    const bool out0_a_valid = xb_in_a_valid && c.req[0];
    c.err_buf_a_enq_fire = out0_a_ready && out0_a_valid;
    // out_1..4: fragmenters.  Device faces: plic, clint, debug, bootrom.
    const PeripheralManagerInputs* faces[4] = {&in.plic, &in.clint, &in.debug,
                                               &in.bootrom};
    bool out_a_ready[5] = {out0_a_ready, false, false, false, false};
    for (int i = 0; i < 4; ++i) {
      const TlA in_a = truncate_a(fx_a, 7u, kAddressMask[i]);
      const bool in_a_valid = xb_in_a_valid && c.req[i + 1];
      const TlD out_d = to_tld(faces[i]->d);
      // in_d_ready (xbar side) is resolved by the D arbiter below; the A
      // path only needs the D-side registers, so evaluate D with a
      // placeholder and patch out_d_ready after the arbiter.
      frag_comb(i, s.frag[i], in_a_valid, in_a, faces[i]->a_ready,
                faces[i]->d.valid, out_d, false, c.frag[i]);
      out_a_ready[i + 1] = c.frag[i].in_a_ready;
    }
    bool xb_in_a_ready = false;
    for (int i = 0; i < 5; ++i)
      if (c.req[i] && out_a_ready[i]) xb_in_a_ready = true;
    // fixer in.a.ready / buf_a deq.
    const bool fx_in_a_ready = xb_in_a_ready && !c.fx_stall;
    c.fx_a_fire = fx_in_a_ready && buf_a_deq_valid;
    c.buf_a_deq_fire = c.fx_a_fire;

    // ================= atomics A =======================
    c.cam_free = s.cam_state == 0;
    c.cam_amo = s.cam_state == 2;
    c.cam_abusy = s.cam_state == 3 || s.cam_state == 2;
    c.cam_dmatch = s.cam_state != 0;
    const TlA a = to_tla(in.upstream_a);
    const bool err_hit = route(a.address)==1;
    const bool a_can_atomic = a.size <= 3 && err_hit;
    const bool a_is_logical = a.opcode == 3, a_is_arith = a.opcode == 2;
    c.a_is_supported =
        a_is_logical ? a_can_atomic : (a_is_arith ? a_can_atomic : true);
    c.a_allow = !c.cam_abusy && (c.a_is_supported || c.cam_free);
    c.source_i_valid = in.upstream_a.valid && c.a_allow;
    c.source_c_valid = c.cam_amo;
    const bool buf_a_full = s.buf_a.value == s.buf_a.value_1 &&
                            s.buf_a.maybe_full;
    const bool at_out_a_ready = !buf_a_full;
    c.at_idle = s.at_beats_left == 0;
    c.at_latch = c.at_idle && at_out_a_ready;
    const bool readys0 = true, readys1 = !c.source_c_valid;
    c.winner0 = readys0 && c.source_c_valid;
    c.winner1 = readys1 && c.source_i_valid;
    const unsigned beats_i =
        a_has_data(a.opcode) ? beats1_12(a.size) : 0;
    c.init_beats = c.winner1 ? beats_i : 0;
    const bool mux0 = c.at_idle ? c.winner0 : s.at_state0;
    const bool mux1 = c.at_idle ? c.winner1 : s.at_state1;
    const bool allowed0 = c.at_idle ? readys0 : s.at_state0;
    const bool allowed1 = c.at_idle ? readys1 : s.at_state1;
    c.source_c_ready = at_out_a_ready && allowed0;
    c.source_i_ready = at_out_a_ready && allowed1;
    c.at_out_a_valid =
        c.at_idle ? (c.source_c_valid || c.source_i_valid)
                  : ((s.at_state0 && c.source_c_valid) ||
                     (s.at_state1 && c.source_i_valid));
    c.in_a_ready = c.source_i_ready && c.a_allow;
    TlA source_i = a;
    if (!c.a_is_supported) {
      source_i.opcode = 4;
      source_i.param = 0;
    }
    TlA out_bits = zeroed<TlA>();
    if (mux0) {
      TlA source_c = zeroed<TlA>();
      source_c.opcode = 0;
      source_c.param = 0;
      source_c.size = s.cam_a.size;
      source_c.source = s.cam_a.source;
      source_c.address = s.cam_a.address;
      source_c.data = amo_data();
      source_c.corrupt = s.cam_a.corrupt || s.cam_d_corrupt;
      source_c.mask = static_cast<std::uint8_t>(
          tl_mask(s.cam_a.address, s.cam_a.size));
      out_bits = source_c;
    }
    if (mux1) {
      out_bits.opcode |= source_i.opcode;
      out_bits.param |= source_i.param;
      out_bits.size |= source_i.size;
      out_bits.source |= source_i.source;
      out_bits.address |= source_i.address;
      out_bits.mask |= source_i.mask;
      out_bits.data |= source_i.data;
      out_bits.corrupt = out_bits.corrupt || source_i.corrupt;
    }
    c.at_out_a = out_bits;
    c.buf_a_enq_fire = at_out_a_ready && c.at_out_a_valid;

    // ================= D path, device side first ===================
    // Error device: Queue_26 deq -> TLError (Queue_25 + counters) -> Queue_27.
    const bool err_buf_a_deq_valid =
        !(s.err_buf_a.value == s.err_buf_a.value_1 && !s.err_buf_a.maybe_full);
    const TlA& err_q_enq = s.err_buf_a.ram[s.err_buf_a.value_1 ? 1 : 0];
    const bool err_q_enq_ready = !s.err_q_maybe_full;
    c.err_buf_a_deq_fire = err_q_enq_ready && err_buf_a_deq_valid;
    c.err_q_enq_fire = c.err_buf_a_deq_fire;
    (void)err_q_enq;
    const bool err_q_deq_valid = s.err_q_maybe_full;
    const TlA& q = s.err_q_ram;
    c.err_a_beats1 = a_has_data(q.opcode) ? beats1_12(q.size) : 0;
    c.err_a_last = s.err_a_last_counter == 1 || c.err_a_beats1 == 0;
    static constexpr std::uint8_t kAdResponse[8] = {0, 0, 1, 1, 1, 2, 4, 4};
    c.err_da.opcode = kAdResponse[q.opcode & 7u];
    c.err_da.param = 0;
    c.err_da.size = q.size;
    c.err_da.source = q.source;
    c.err_da.sink = false;
    c.err_da.denied = true;
    c.err_da.data = 0;
    c.err_da.corrupt = (c.err_da.opcode & 1u) != 0;
    c.err_da_beats1 =
        d_has_data(c.err_da.opcode) ? beats1_12(c.err_da.size) : 0;
    c.err_da_first = s.err_counter == 0;
    const bool err_da_last = s.err_counter == 1 || c.err_da_beats1 == 0;
    const bool err_buf_d_full = s.err_buf_d.value == s.err_buf_d.value_1 &&
                                s.err_buf_d.maybe_full;
    const bool err_da_ready = !err_buf_d_full;  // Queue_27 enq.ready
    const bool err_da_valid = err_q_deq_valid && c.err_a_last && s.err_idle;
    const bool err_q_deq_ready =
        (err_da_ready && err_da_last && s.err_idle) || !c.err_a_last;
    c.err_q_deq_fire = err_q_deq_ready && err_q_deq_valid;
    c.err_da_fire = err_da_ready && err_da_valid;
    c.err_buf_d_enq_fire = c.err_da_fire;
    // Queue_27 deq = xbar out_0.d.
    const bool out0_d_valid =
        !(s.err_buf_d.value == s.err_buf_d.value_1 && !s.err_buf_d.maybe_full);
    const TlD& out0_d = s.err_buf_d.ram[s.err_buf_d.value_1 ? 1 : 0];

    // TLXbar_5 D arbiter.
    const bool buf_d_full = s.buf_d.value == s.buf_d.value_1 &&
                            s.buf_d.maybe_full;
    c.xb_sink_ready = !buf_d_full;  // fixer D is a wire into Queue_24
    bool v[5];
    unsigned beats[5];
    const TlD* dbits[5];
    v[0] = out0_d_valid;
    dbits[0] = &out0_d;
    beats[0] = d_has_data(out0_d.opcode) ? beats1_12(out0_d.size & 0xfu) : 0;
    for (int i = 0; i < 4; ++i) {
      v[i + 1] = c.frag[i].in_d_valid;
      dbits[i + 1] = &c.frag[i].in_d;
      const unsigned sz = c.frag[i].in_d.size & 7u;
      beats[i + 1] = (i == kBootrom || d_has_data(c.frag[i].in_d.opcode))
                         ? beats1_6(sz) : 0;
    }
    unsigned valids = 0;
    for (int i = 0; i < 5; ++i) valids |= (v[i] ? 1u : 0u) << i;
    c.xb_valids = valids;
    c.xb_idle = s.xb_beats_left == 0;
    c.xb_latch = c.xb_idle && c.xb_sink_ready;
    const unsigned mask = s.xb_readys_mask & 0x1fu;
    // Visit clients in descending cyclic priority. Every client before the
    // first valid offer may see ready; that first offer owns this transaction.
    unsigned first=4;
    if(mask!=0) {unsigned last=0;while(!(mask&(1u<<last))) ++last;first=(last+4)%5;}
    c.xb_readys=0;
    for(unsigned n=0;n<5;++n) {
      const unsigned client=(first+5-n)%5;c.xb_readys|=1u<<client;
      if(valids&(1u<<client)) break;
    }
    c.xb_winner = c.xb_readys & valids;
    c.xb_init_beats = 0;
    for (int i = 0; i < 5; ++i)
      if (c.xb_winner & (1u << i)) c.xb_init_beats |= beats[i];
    const unsigned mux_state = c.xb_idle ? c.xb_winner : s.xb_state;
    const unsigned allowed = c.xb_idle ? c.xb_readys : s.xb_state;
    for (int i = 0; i < 5; ++i)
      c.out_d_ready[i] = c.xb_sink_ready && ((allowed >> i) & 1u);
    c.xb_in_d_valid = c.xb_idle ? valids != 0 : (s.xb_state & valids) != 0;
    TlD in_d = zeroed<TlD>();
    for (int i = 0; i < 5; ++i) {
      if (!((mux_state >> i) & 1u)) continue;
      const TlD& b = *dbits[i];
      in_d.opcode |= b.opcode;
      in_d.param |= b.param;
      in_d.size |= b.size;
      in_d.source |= b.source;
      in_d.sink = in_d.sink || b.sink;
      in_d.denied = in_d.denied || b.denied;
      in_d.data |= b.data;
      in_d.corrupt = in_d.corrupt || b.corrupt;
    }
    c.fx_d = in_d;
    c.err_buf_d_deq_fire = c.out_d_ready[0] && out0_d_valid;
    for (int i = 0; i < 4; ++i) {
      // Patch the fragmenter D handshake with the arbiter's ready.
      FragComb& fc = c.frag[i];
      fc.out_d_ready = c.out_d_ready[i + 1] || fc.drop;
      fc.d_fire = fc.out_d_ready && faces[i]->d.valid;
    }
    // Fixer D (wire) and Queue_24 enq.
    c.fx_d_beats1 = d_has_data(in_d.opcode) ? beats1_12(in_d.size & 0xfu) : 0;
    c.fx_d_first = s.fx_d_first_counter == 0 && in_d.opcode != 6;
    c.fx_d_fire = c.xb_sink_ready && c.xb_in_d_valid;
    c.buf_d_enq_fire = c.fx_d_fire;

    // ================= atomics D =======================
    const bool buf_d_deq_valid = !(s.buf_d.value == s.buf_d.value_1 &&
                                   !s.buf_d.maybe_full);
    const TlD& d = s.buf_d.ram[s.buf_d.value_1 ? 1 : 0];
    c.d_beats1 = d_has_data(d.opcode) ? beats1_12(d.size & 0xfu) : 0;
    c.d_first = s.at_d_first_counter == 0;
    c.d_cam_sel = (s.cam_a.source == (d.source & 0x1fu)) && c.cam_dmatch;
    c.d_ackd = d.opcode == 1;
    const bool d_ack = d.opcode == 0;
    c.d_drop = c.d_first && c.d_ackd && c.d_cam_sel;
    c.d_replace = c.d_first && d_ack && c.d_cam_sel;
    c.in_d_valid = buf_d_deq_valid && !c.d_drop;
    const bool at_out_d_ready = in.upstream_d_ready || c.d_drop;
    c.buf_d_deq_fire = at_out_d_ready && buf_d_deq_valid;
    c.in_d = d;
    if (c.d_replace) {
      c.in_d.opcode = 1;
      c.in_d.data = s.cam_d_data;
      c.in_d.corrupt = s.cam_d_corrupt || d.denied;
      c.in_d.denied = s.cam_d_denied || d.denied;
    }
  }

  // The selected byte lanes form one aligned operand. Arithmetic uses
  // its signed/unsigned value; logical operations act directly on the bits.
  std::uint64_t amo_data() const {
    const auto a=s_.cam_a.data,d=s_.cam_d_data;
    const unsigned operation=s_.cam_a.param;
    if(s_.cam_a.opcode==3) {
      switch(operation&3u) {case 0:return a^d;case 1:return a|d;case 2:return a&d;default:return a;}
    }
    std::uint64_t mask=0;unsigned width=0;
    for(unsigned byte=0;byte<8;++byte) if(s_.cam_a.mask&(1u<<byte)) {mask|=UINT64_C(255)<<(8*byte);width=8*(byte+1);}
    const auto extend=[&](std::uint64_t value) {
      value&=mask;
      if(width!=0 && width<64 && ((value>>(width-1))&1)) value|=UINT64_MAX<<width;
      return value;
    };
    const auto left=extend(a),right=extend(d);
    if(operation&4u) return left+right;
    const bool greater=(operation&2u) ? left>right : static_cast<std::int64_t>(left)>static_cast<std::int64_t>(right);
    return (operation&1u) ? (greater?a:d) : (greater?d:a);
  }

  static void queue_tick_a(Queue2A& q, bool enq_fire, const TlA& enq,
                           bool deq_fire, bool reset) {
    if (enq_fire) {
      q.ram[q.value ? 1 : 0] = enq;
      q.value = !q.value;
    }
    if (deq_fire) q.value_1 = !q.value_1;
    if (enq_fire != deq_fire) q.maybe_full = enq_fire;
    if (reset) q.value = q.value_1 = q.maybe_full = false;
  }
  static void queue_tick_d(Queue2D& q, bool enq_fire, const TlD& enq,
                           bool deq_fire, bool reset) {
    if (enq_fire) {
      q.ram[q.value ? 1 : 0] = enq;
      q.value = !q.value;
    }
    if (deq_fire) q.value_1 = !q.value_1;
    if (enq_fire != deq_fire) q.maybe_full = enq_fire;
    if (reset) q.value = q.value_1 = q.maybe_full = false;
  }

  /** One clock edge.  Registers with a reset value take it last, exactly
    * like the FIRRTL reset mux; registers without one follow their normal
    * update even while reset is asserted. */
  void tick(const PeripheryBusInputs& in) {
    // evaluate() already computed this exact PRE state and input combination.
    const Comb& c = evaluated_comb_;
    State& s = s_;
    const bool reset = in.reset;
    const TlA a = to_tla(in.upstream_a);

    // ---- atomics ----
    {
      const unsigned fire = c.buf_a_enq_fire ? 1u : 0u;
      s.at_beats_left = static_cast<std::uint16_t>(
          (c.at_latch ? c.init_beats : (s.at_beats_left - fire)) & 0x1ffu);
      if (c.at_idle) {
        s.at_state0 = c.winner0;
        s.at_state1 = c.winner1;
      }
      if (c.source_i_ready && c.source_i_valid && !c.a_is_supported &&
          c.cam_free) {
        s.cam_a = a;
        s.cam_state = 3;
      }
      if (c.source_c_ready && c.source_c_valid && c.cam_amo) s.cam_state = 1;
      const TlD& d = s.buf_d.ram[s.buf_d.value_1 ? 1 : 0];
      if (c.buf_d_deq_fire) {
        s.at_d_first_counter = static_cast<std::uint16_t>(
            (c.d_first ? c.d_beats1 : (s.at_d_first_counter - 1u)) & 0x1ffu);
        if (c.d_first) {
          if (c.d_cam_sel && c.d_ackd) {
            s.cam_d_data = d.data;
            s.cam_d_denied = d.denied;
            s.cam_d_corrupt = d.corrupt;
          }
          if (c.d_cam_sel) s.cam_state = c.d_ackd ? 2 : 0;
        }
      }
      if (reset) {
        s.cam_state = 0;
        s.at_beats_left = 0;
        s.at_state0 = s.at_state1 = false;
        s.at_d_first_counter = 0;
      }
    }

    // ---- TLBuffer_4 queues ----
    // The atomics D side reads buf_d before this edge (captured in c);
    // the queues update from the fires computed above.
    queue_tick_a(s.buf_a, c.buf_a_enq_fire, c.at_out_a, c.buf_a_deq_fire,
                 reset);
    queue_tick_d(s.buf_d, c.buf_d_enq_fire, c.fx_d, c.buf_d_deq_fire, reset);

    // ---- fixer ----
    {
      if (c.fx_a_fire)
        s.fx_a_first_counter = static_cast<std::uint16_t>(
            (c.fx_a_first ? c.fx_a_beats1 : (s.fx_a_first_counter - 1u)) &
            0x1ffu);
      if (c.fx_d_fire)
        s.fx_d_first_counter = static_cast<std::uint16_t>(
            ((s.fx_d_first_counter == 0) ? c.fx_d_beats1
                                         : (s.fx_d_first_counter - 1u)) &
            0x1ffu);
      if (c.fx_a_first && c.fx_a_fire && c.fx_a.source >= fifo_source_base_ && c.fx_a.source < fifo_source_base_+16)
        s.fx_flight |= 1u << c.fx_a.source;
      if (c.fx_d_first && c.fx_d_fire && (c.fx_d.source & 0x1fu) >= fifo_source_base_ && (c.fx_d.source & 0x1fu) < fifo_source_base_+16)
        s.fx_flight &= ~(1u << (c.fx_d.source & 0x1fu));
      if (c.fx_a_fire && c.fx_sel0) s.fx_stalls_id = static_cast<std::uint8_t>(c.fx_a_id);
      if (c.fx_a_fire && c.fx_sel1) s.fx_stalls_id_1 = static_cast<std::uint8_t>(c.fx_a_id);
      if (reset) {
        s.fx_a_first_counter = 0;
        s.fx_d_first_counter = 0;
        s.fx_flight = 0;
      }
    }

    // ---- out_xbar D arbiter ----
    {
      if (c.xb_latch && c.xb_valids != 0) {
        unsigned chosen=0;while(!(c.xb_winner&(1u<<chosen))) ++chosen;
        s.xb_readys_mask=static_cast<std::uint8_t>((0x1fu<<chosen)&0x1fu);
      }
      const unsigned fire = (c.xb_in_d_valid && c.xb_sink_ready) ? 1u : 0u;
      s.xb_beats_left = static_cast<std::uint16_t>(
          (c.xb_latch ? c.xb_init_beats : (s.xb_beats_left - fire)) & 0x1ffu);
      if (c.xb_idle) s.xb_state = static_cast<std::uint8_t>(c.xb_winner);
      if (reset) {
        s.xb_readys_mask = 0x1f;
        s.xb_beats_left = 0;
        s.xb_state = 0;
      }
    }

    // ---- error device ----
    {
      const TlA err_enq = truncate_a(c.fx_a, 0xfu, kErrorAddressMask);
      const TlA err_q_enq = s.err_buf_a.ram[s.err_buf_a.value_1 ? 1 : 0];
      queue_tick_a(s.err_buf_a, c.err_buf_a_enq_fire, err_enq,
                   c.err_buf_a_deq_fire, reset);
      // Queue_25 (depth 1): ram written on enq, maybe_full toggles.
      if (c.err_q_enq_fire) s.err_q_ram = err_q_enq;
      if (c.err_q_enq_fire != c.err_q_deq_fire)
        s.err_q_maybe_full = c.err_q_enq_fire;
      if (c.err_q_deq_fire)
        s.err_a_last_counter = static_cast<std::uint16_t>(
            ((s.err_a_last_counter == 0) ? c.err_a_beats1
                                         : (s.err_a_last_counter - 1u)) &
            0x1ffu);
      if (c.err_da_fire)
        s.err_counter = static_cast<std::uint16_t>(
            (c.err_da_first ? c.err_da_beats1 : (s.err_counter - 1u)) &
            0x1ffu);
      queue_tick_d(s.err_buf_d, c.err_buf_d_enq_fire, c.err_da,
                   c.err_buf_d_deq_fire, reset);
      if (reset) {
        s.err_q_maybe_full = false;
        s.err_idle = true;
        s.err_a_last_counter = 0;
        s.err_counter = 0;
      }
    }

    // ---- fragmenters ----
    for (int i = 0; i < 4; ++i) {
      Fragmenter& f = s.frag[i];
      const FragComb& fc = c.frag[i];
      const TlA in_a = truncate_a(c.fx_a, 7u, kAddressMask[i]);
      // All registers update from the pre-edge image: aToggle_r samples
      // dToggle as it was before this edge, even if a first D beat lands.
      const bool d_toggle_before = f.dToggle;
      if (fc.d_fire) {
        f.acknum = static_cast<std::uint8_t>(
            fc.d_first ? fc.d_first_acknum
                       : ((f.acknum - fc.ack_decrement) & 7u));
        if (fc.d_first) {
          f.dOrig = fc.d_first_size;
          f.dToggle = fc.d_toggle_next;
        }
      }
      if (fc.a_first) f.aToggle_r = d_toggle_before;
      if (fc.a_fire) f.gennum = fc.new_gennum;
      if (fc.enq_fire && fc.repeat) {
        f.rep.full = true;
        f.rep.saved = in_a;
      }
      if (fc.deq_fire && !fc.repeat) f.rep.full = false;
      if (reset) {
        f.acknum = 0;
        f.dToggle = false;
        f.gennum = 0;
        f.rep.full = false;
      }
    }
  }

  void refresh_outputs(const PeripheryBusInputs& in) {
    compute_comb(in, evaluated_comb_);
    const Comb& c = evaluated_comb_;
    outputs_.upstream_a_ready = c.in_a_ready;
    outputs_.upstream_d.valid = c.in_d_valid;
    outputs_.upstream_d.opcode = c.in_d.opcode;
    outputs_.upstream_d.param = c.in_d.param;
    outputs_.upstream_d.size = c.in_d.size;
    outputs_.upstream_d.source = static_cast<std::uint8_t>(c.in_d.source);
    outputs_.upstream_d.sink = c.in_d.sink ? 1 : 0;
    outputs_.upstream_d.denied = c.in_d.denied;
    outputs_.upstream_d.data = c.in_d.data;
    outputs_.upstream_d.corrupt = c.in_d.corrupt;
    PeripheralManagerOutputs* faces[4] = {&outputs_.plic, &outputs_.clint,
                                          &outputs_.debug, &outputs_.bootrom};
    for (int i = 0; i < 4; ++i) {
      const FragComb& fc = c.frag[i];
      PeripheralManagerOutputs& o = *faces[i];
      o.a.valid = fc.out_a_valid;
      o.a.opcode = fc.out_a.opcode;
      o.a.param = fc.out_a.param;
      o.a.size = fc.out_a.size;
      o.a.source = fc.out_a_source9;
      o.a.address = fc.out_a.address;
      o.a.mask = fc.out_a.mask;
      o.a.data = fc.out_a.data;
      o.a.corrupt = fc.out_a.corrupt;
      o.d_ready = fc.out_d_ready;
    }
  }

  bool busy() const {
    const auto nonempty=[](const auto& queue) {return queue.value!=queue.value_1 || queue.maybe_full;};
    if(s_.cam_state || s_.at_beats_left || s_.at_d_first_counter || s_.xb_beats_left ||
       s_.fx_a_first_counter || s_.fx_d_first_counter || s_.fx_flight ||
       nonempty(s_.buf_a) || nonempty(s_.buf_d) || nonempty(s_.err_buf_a) || nonempty(s_.err_buf_d) ||
       s_.err_q_maybe_full || s_.err_a_last_counter || s_.err_counter) return true;
    for(const auto& f:s_.frag) if(f.rep.full || f.gennum || f.acknum) return true;
    const auto& in=pending_inputs_;
    return in.upstream_a.valid || in.plic.d.valid || in.clint.d.valid || in.debug.d.valid || in.bootrom.d.valid;
  }

  Comb evaluated_comb_{};
  State s_{};
  unsigned fifo_source_base_=0;
  unsigned drain_cycles_=0;
  PeripheryBusInputs last_inputs_{};
  PeripheryBusInputs applied_inputs_{};
  PeripheryBusInputs pending_inputs_{};
  PeripheryBusOutputs outputs_{};
  bool pending_valid_ = false;
  bool active_ = false;
  std::uint64_t eval_count_ = 0;
  std::uint64_t skipped_count_ = 0;
};

}  // namespace chisa::boom_system::components
