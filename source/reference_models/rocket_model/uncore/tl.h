// rocket_model uncore: TileLink / AXI4 channel structures and the small building
// blocks the interconnect modules are made of (queues, arbiters, beat
// counters).  Written from the TileLink specification and the rocket-chip
// Chisel sources; no generated RTL is used.
#pragma once

#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace chisa::rocket_model::uncore {

// ---- TileLink message opcodes and permissions ------------------------------
enum : uint8_t {
  A_PutFullData = 0, A_PutPartialData = 1, A_ArithmeticData = 2, A_LogicalData = 3, A_Get = 4, A_Hint = 5,
  A_AcquireBlock = 6, A_AcquirePerm = 7,
  B_Probe = 6,
  C_ProbeAck = 4, C_ProbeAckData = 5, C_Release = 6, C_ReleaseData = 7,
  D_AccessAck = 0, D_AccessAckData = 1, D_HintAck = 2, D_Grant = 4, D_GrantData = 5, D_ReleaseAck = 6,
};
enum : uint8_t { P_toT = 0, P_toB = 1, P_toN = 2, P_NtoB = 0, P_NtoT = 1, P_BtoT = 2,
                 P_TtoB = 0, P_TtoN = 1, P_BtoN = 2, P_TtoT = 3, P_BtoB = 4, P_NtoN = 5 };

// Fragmenter appends four source bits to the five-bit system source: the
// register-device side really has nine bits (e.g. PLIC source 0x120).
struct TlA { uint8_t opcode = 0, param = 0, size = 0; uint16_t source = 0; uint32_t address = 0; uint8_t mask = 0; uint64_t data = 0; bool corrupt = false; };
struct TlB { uint8_t opcode = 0, param = 0, size = 0; uint16_t source = 0; uint32_t address = 0; uint8_t mask = 0; uint64_t data = 0; bool corrupt = false; };
struct TlC { uint8_t opcode = 0, param = 0, size = 0; uint16_t source = 0; uint32_t address = 0; uint64_t data = 0; bool corrupt = false; };
struct TlD { uint8_t opcode = 0, param = 0, size = 0; uint16_t source = 0; uint8_t sink = 0; bool denied = false; uint64_t data = 0; bool corrupt = false; };
struct TlE { uint8_t sink = 0; };

// AXI4 (64-bit data).  The echo fields (tl_state, extra_id, real_last) travel with the request.
struct AxiA { uint8_t id = 0; uint32_t addr = 0; uint8_t len = 0, size = 0, burst = 0; bool lock = false; uint8_t cache = 0, prot = 0, qos = 0;
              uint8_t echo_size = 0, echo_source = 0, echo_extra = 0; bool echo_last = false; };
struct AxiW { uint64_t data = 0; uint8_t strb = 0; bool last = false; bool corrupt = false; };
struct AxiB { uint8_t id = 0, resp = 0; uint8_t echo_size = 0, echo_source = 0, echo_extra = 0; bool echo_last = false; };
struct AxiR { uint8_t id = 0; uint64_t data = 0; uint8_t resp = 0; bool last = false; uint8_t echo_size = 0, echo_source = 0, echo_extra = 0; bool echo_last = false; };

// ---- bit helpers ----------------------------------------------------------
inline uint32_t left_or(uint32_t x, unsigned width) {   // bit i = OR of x[j] for j <= i
  for (unsigned s = 1; s < width; s <<= 1) x |= x << s;
  return width >= 32 ? x : (x & ((1u << width) - 1));
}
inline uint32_t right_or(uint32_t x) {                  // bit i = OR of x[j] for j >= i
  for (unsigned s = 1; s < 32; s <<= 1) x |= x >> s;
  return x;
}
inline uint32_t oh1(unsigned size, unsigned width) {   // UIntToOH1: (1 << size) - 1 limited to width bits
  const uint32_t v = size >= 32 ? 0xFFFFFFFFu : ((1u << size) - 1);
  return width >= 32 ? v : (v & ((1u << width) - 1));
}
inline unsigned oh1_to_uint(uint32_t x) { return static_cast<unsigned>(__builtin_popcount(x)); }

// TileLink A/B/C/D data-beat helpers for an 8-byte beat.
inline bool a_has_data(uint8_t opcode) { return !(opcode & 4); }
inline bool c_has_data(uint8_t opcode) { return opcode & 1; }
inline bool d_has_data(uint8_t opcode) { return opcode & 1; }
// numBeats1: beats - 1 when the message carries data, else 0 (max_lg_size bounds the size field).
inline uint32_t beats1(uint8_t size, bool has_data, unsigned max_lg_size) {
  return has_data ? (oh1(size, max_lg_size) >> 3) : 0;
}
// TileLink byte mask of an aligned access of 2^size bytes at addr (8-byte beat).
inline uint8_t tl_mask(uint32_t addr, uint8_t size) {
  if (size >= 3) return 0xFF;
  const unsigned bytes = 1u << size;
  return static_cast<uint8_t>(((1u << bytes) - 1) << (addr & 7 & ~(bytes - 1)));
}

// edge.firstlast counter: first = counter == 0; last = counter == 1 || beats1 == 0.
struct BeatCounter {
  uint16_t counter = 0;
  bool first() const { return counter == 0; }
  bool last(uint32_t b1) const { return counter == 1 || b1 == 0; }
  uint32_t count(uint32_t b1) const { return b1 & ~static_cast<uint32_t>(counter - 1); }
  void step(bool fire, uint32_t b1) { if (fire) counter = static_cast<uint16_t>(first() ? b1 : counter - 1); }
};

// TLFIFOFixer: two FIFO-requesting clients, with source ranges [0,8)
// and [8,16). Tile sources [16,19) do not request FIFO ordering. Requests
// capture their destination domain on every accepted A beat; flight changes
// only on the first A/D beat. A simultaneous response has clearing priority.
// The domain register is RegEnable, without reset, and therefore retains its
// value across reset edges (the scalar simulator cold-initializes it to zero).
struct FifoFixer {
  BeatCounter a_first, d_first;
  uint32_t flight = 0;
  uint8_t domain[2] = {};
  bool allow(const TlA& a, bool not_fifo, uint8_t id) const {
    if (not_fifo || a.source >= 16 || !a_first.first()) return true;
    const unsigned client = a.source >> 3;
    return !(flight & (UINT32_C(255) << (client * 8))) ||
           (id != 0 && domain[client] == id);
  }
  void step(bool a_fire, const TlA& a, bool not_fifo, uint8_t id,
            bool d_fire, const TlD& d, bool reset) {
    if (a_fire) {
      if (a.source >= 32) throw std::out_of_range("FIFO fixer source");
      if (a_first.first()) {
        const uint32_t bit = UINT32_C(1) << a.source;
        flight = not_fifo ? flight & ~bit : flight | bit;
      }
      if (a.source < 16 && !not_fifo) domain[a.source >> 3] = id;
    }
    if (d_fire && d_first.first() && d.opcode != D_ReleaseAck) {
      if (d.source >= 32) throw std::out_of_range("FIFO fixer response source");
      flight &= ~(UINT32_C(1) << d.source);
    }
    a_first.step(a_fire, beats1(a.size, a_has_data(a.opcode), 12));
    d_first.step(d_fire, beats1(d.size, d_has_data(d.opcode), 12));
    if (reset) { flight = 0; a_first.counter = d_first.counter = 0; }
  }
};

// ---- chisel3.util.Queue ----------------------------------------------------
// Entries N (power of two or 1), optional flow.  deq bits read the ram at deq_ptr even when empty
// (downstream modules can observe those stale bits), so the ram is kept exactly.
template <typename T, unsigned N, bool kFlow = false>
struct Queue {
  static_assert(N > 0 && N <= 128 && (N & (N - 1)) == 0);
  T ram[N];
  uint8_t enq_ptr = 0, deq_ptr = 0;
  bool maybe_full = false;
  // Mixed-depth per-ID Yanker arrays use their elaborated depth. Storage for
  // unused slots remains unreachable; their pointers wrap at the real depth.
  uint8_t depth = N;
  Queue() { for (unsigned i = 0; i < N; ++i) ram[i] = T{}; }
  bool ptr_match() const { return enq_ptr == deq_ptr; }
  bool empty() const { return ptr_match() && !maybe_full; }
  bool full() const { return ptr_match() && maybe_full; }
  bool enq_ready() const { return !full(); }
  bool deq_valid(bool enq_valid) const { return !empty() || (kFlow && enq_valid); }
  const T& deq_bits(const T& enq) const { return (kFlow && empty()) ? enq : ram[deq_ptr]; }
  const T& head() const { return ram[deq_ptr]; }
  unsigned count() const { return full() ? depth : ((enq_ptr - deq_ptr) & (depth - 1)); }
  void set_depth(unsigned value) {
    if (!empty() || value == 0 || value > N || (value & (value - 1)))
      throw std::invalid_argument("invalid live queue depth change");
    depth = static_cast<uint8_t>(value);
  }
  // Advance one cycle.  enq_fire/deq_fire are the handshakes seen at the queue's own ports.
  void step(bool enq_fire, const T& bits, bool deq_fire) {
    bool do_enq = enq_fire, do_deq = deq_fire;
    if (kFlow && empty()) { do_deq = false; if (deq_fire) do_enq = false; }
    if (do_enq) { ram[enq_ptr] = bits; enq_ptr = static_cast<uint8_t>((enq_ptr + 1) & (depth - 1)); }
    if (do_deq) deq_ptr = static_cast<uint8_t>((deq_ptr + 1) & (depth - 1));
    if (do_enq != do_deq) maybe_full = do_enq;
  }
  void reset() { enq_ptr = deq_ptr = 0; maybe_full = false; }
};

// ---- TLArbiter (round robin) over N sources ----------------------------------
// readys = policy(valids, latch); the winner holds the sink for beats1+1 beats.
template <unsigned N>
struct RrArbiter {
  static_assert(N > 0 && N < 32);
  uint32_t mask = (1u << N) - 1;   // RegInit(all ones)
  uint16_t beats_left = 0;
  uint32_t state = 0;              // one bit per source
  bool idle() const { return beats_left == 0; }
  uint32_t readys(uint32_t valids) const {
    // Descending priority, first the entries beyond the previous winner,
    // then wrap. Include idle entries visited before the first requester:
    // their ready pins are observable even when they have no valid payload.
    uint32_t ready = 0;
    for (unsigned pass = 0; pass < 2; ++pass)
      for (unsigned i = N; i-- > 0;) {
        const uint32_t bit = UINT32_C(1) << i;
        if (bool(mask & bit) != bool(pass)) continue;
        ready |= bit;
        if (valids & bit) return ready;
      }
    return ready;
  }
  // Which sources may drive the sink this cycle (before the ready qualification).
  uint32_t allowed(uint32_t valids) const { return idle() ? readys(valids) : state; }
  uint32_t winner(uint32_t valids) const { return idle() ? (readys(valids) & valids) : state; }
  bool sink_valid(uint32_t valids) const { return idle() ? valids != 0 : (state & valids) != 0; }
  // latch = idle && sink_ready.  beats: beats1 of the winner (0 if none).
  void step(uint32_t valids, bool sink_ready, bool sink_fire, uint32_t winner_beats1) {
    const bool was_idle = idle();
    const bool latch = was_idle && sink_ready;
    // The mask and held winner are registers on the same edge.  Computing
    // state from the newly rotated mask would lock the *next* source while
    // the current source still owns the remaining beats of its transaction.
    const uint32_t selected = readys(valids) & valids;
    if (latch && valids != 0) mask = left_or(selected, N);
    if (was_idle) state = selected;
    beats_left = static_cast<uint16_t>(latch ? winner_beats1 : beats_left - (sink_fire ? 1 : 0));
  }
};

// TLArbiter.lowestIndexFirst over N sources (no mask register).
template <unsigned N>
struct LowArbiter {
  uint16_t beats_left = 0;
  uint32_t state = 0;
  bool idle() const { return beats_left == 0; }
  static uint32_t readys(uint32_t valids) {
    uint32_t ready=0;
    for (unsigned i=0;i<N;++i) { const uint32_t bit=UINT32_C(1)<<i; ready|=bit; if(valids&bit) break; }
    return ready;
  }
  uint32_t winner(uint32_t valids) const { return idle() ? (readys(valids) & valids) : state; }
  uint32_t allowed(uint32_t valids) const { return idle() ? readys(valids) : state; }
  bool sink_valid(uint32_t valids) const { return idle() ? valids != 0 : (state & valids) != 0; }
  void step(uint32_t valids, bool sink_ready, bool sink_fire, uint32_t winner_beats1) {
    const bool latch = idle() && sink_ready;
    if (idle()) state = readys(valids) & valids;
    beats_left = static_cast<uint16_t>(latch ? winner_beats1 : beats_left - (sink_fire ? 1 : 0));
  }
};

// Synchronizer chain of `depth` flops (output = the last stage).  reset_value applies while reset is high.
template <unsigned Depth>
struct SyncChain {
  uint8_t stages = 0;   // bit i = stage i; stage 0 is the output
  bool out() const { return stages & 1; }
  void step(bool in, bool reset, bool reset_value) {
    if (reset) { stages = reset_value ? static_cast<uint8_t>((1u << Depth) - 1) : 0; return; }
    stages = static_cast<uint8_t>(((stages >> 1) | (in ? (1u << (Depth - 1)) : 0)) & ((1u << Depth) - 1));
  }
};

}  // namespace chisa::rocket_model::uncore
