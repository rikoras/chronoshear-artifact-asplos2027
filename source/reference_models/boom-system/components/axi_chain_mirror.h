#pragma once
// ==========================================================================
// Register mirror of the mbus AXI conversion chain + SimAXIMem timing.
//
// Register-level mirror of the memory-side AXI chain (the blueprint it
// implements lived in docs/AXI_MIRROR_BLUEPRINT.md, removed 2026-08-28;
// see git history).  A pure observer: driven each
// cycle by the fabric's ManagerBeats (the TL beats entering the memory bus;
// the fixer and 1x1 xbar between are pure wires), it steps its own copies of
// every register in TLToAXI4_1, AXI4UserYanker_2 and the harness-side
// fragmenter/buffer/AXI4RAM handshake state, so the live oracle writer can
// export their values. Nothing here feeds back into model behavior.
//
// The chain is a deterministic function of the incoming beats (blueprint
// section 10); its emergent D-side timing must agree with the fabric's
// modeled response latency — the per-stream lockstep is the referee.
// ==========================================================================

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "small_icache_memory_path.h"

namespace chisa::boom_system::components {

class AxiChainMirror {
 public:
  // ---- TLToAXI4_1 ----
  struct FlowQueue1 {  // depth-1 flow queue: only maybe_full + one ram slot
    bool maybe_full = false;
  };
  std::uint8_t t2a_counter = 0;      // 3b Put beat countdown
  bool t2a_doneAW = false;
  bool t2a_r_holds_d = false;
  std::uint8_t t2a_b_delay = 0;      // 3b
  bool t2a_r_first = true;
  bool t2a_r_denied = false;
  std::array<bool, 128> t2a_count{};   // per-id in-flight (maxFlight 1)
  FlowQueue1 t2a_wq{};                 // W queue
  FlowQueue1 t2a_arwq{};               // ARW queue

  // ---- AXI4UserYanker_2: 16 AR + 16 AW echo queues, depth 8 ----
  struct YankQueue {
    struct Entry { std::uint8_t size = 0; std::uint8_t source = 0;
                   std::uint8_t extra_id = 0; };
    std::array<Entry, 8> ram{};
    std::uint8_t enq_ptr = 0;   // 3b
    std::uint8_t deq_ptr = 0;   // 3b
    bool maybe_full = false;
    bool empty() const { return enq_ptr == deq_ptr && !maybe_full; }
    bool full() const { return enq_ptr == deq_ptr && maybe_full; }
    void enq(const Entry& e) {
      ram[enq_ptr] = e;
      enq_ptr = (enq_ptr + 1u) & 7u;
      maybe_full = true;
    }
    void deq() {
      deq_ptr = (deq_ptr + 1u) & 7u;
      maybe_full = false;
    }
  };
  std::array<YankQueue, 16> yank_ar{};
  std::array<YankQueue, 16> yank_aw{};

  // ---- TLBroadcast trackers (4x) ----
  // Latched at the broadcast in.a fire (= the fabric's a_enq beat, one cycle
  // ahead of the manager route fire).  got_e falls at that latch and returns
  // a fixed 18 cycles after the read's last data beat (measured constant on
  // ten transactions: tile D delivery + GrantAck return path); sent_d sets
  // at the last data beat.  Probes resolve at the latch edge (single inner
  // cache, the filter never probes the requester), so `count` stays 0.
  struct BroadcastTracker {
    std::uint32_t address = 0;
    std::uint8_t opcode = 0;
    std::uint8_t size = 0;
    std::uint8_t source = 0;   // 5b inner (sbus) source
    bool got_e = true;
    bool sent_d = true;
    std::uint8_t o_enq_ptr = 0;   // o_data queue counters, 3b
    std::uint8_t o_deq_ptr = 0;
    bool o_maybe_full = false;
    int got_e_countdown = -1;     // cycles until got_e sets; -1 = none
    bool idle() const { return got_e && sent_d; }
  };
  std::array<BroadcastTracker, 4> trackers{};

  // ---- TLBroadcast arbiters ----
  // D-side (in.d): both memory responses and the synthesized ReleaseAck
  // arrive through input 1 (input 0 never fires here; its state element was
  // dead-pruned from the contract).  A-side (out.a): input 0 = the putfull (release data)
  // path, inputs 1..4 = trackers 0..3.  state holds the winner until the
  // next latch; beatsLeft counts the granted burst's remaining beats.
  std::uint8_t darb_beatsLeft = 0;
  std::array<bool, 2> darb_state{};
  std::uint8_t aarb_beatsLeft = 0;
  std::array<bool, 5> aarb_state{};
  bool gen257 = false;  // TLToAXI4 stall probe: count[presented out.a source]
  std::array<std::uint8_t, 4> tile_d_beats_{};  // per-dcache-source beat count
  // RTL MSHR refill bookkeeping: the first/last counter latches 7 at the
  // first grant beat at the tile and counts down; refill_ctr advances one
  // cycle behind each beat.
  std::array<std::uint8_t, 2> mshr_counter{};
  std::array<std::uint8_t, 2> mshr_refill{};
  std::array<std::uint8_t, 2> mshr_refill_pending{};
  // The E beat lands at the broadcast two edges after the MSHR enters its
  // finish state (tile boundary + bus buffer); the countdown decrements
  // starting the step after it is armed and fires when it drops below zero.
  static constexpr int kGrantAckDelay = 1;
  // in-flight route order: a_enq assigns a tracker, the route fire pops it
  std::array<std::uint8_t, 8> route_order{};
  std::uint8_t route_head = 0, route_tail = 0;


  // ---- harness side (fragmenter + AXI buffer + AXI4RAM timing) ----
  // The fragmenter splits every 8-beat burst into single-beat AXI ops, one
  // per cycle starting the edge the burst arrives; the buffer is a depth-2
  // queue per channel draining one per cycle (the RAM is always ready and
  // answers reads with one cycle of latency, writes with an immediate B).
  // Measured on the read at edge 1397 and the writeback at edge 24004:
  //   AR/AW/W fragment i enqueues at T+i and dequeues at T+1+i;
  //   R data enqueues at T+2+i and dequeues at T+3+i (= the tl2axi4 R
  //   beats the fabric's response machinery already reproduces);
  //   B enqueues at T+2+i and dequeues at T+3+i.
  // The whole schedule is driven off the burst-arrival edge; the traffic in
  // the qualification window never overlaps read and write at the RAM, and
  // the per-stream lockstep referees any future case that does.
  struct FragSide {
    std::uint32_t r_addr = 0;
    std::uint8_t r_len = 0;      // remaining-1; rests at 0xff after a burst
    bool busy = false;           // deq flow-queue maybe_full
  };
  FragSide frag_rd, frag_wr;
  struct AxiBufQueue {
    struct Entry {
      std::uint32_t addr = 0;
      std::uint64_t data = 0;
      std::uint8_t id = 0;
      std::uint8_t strb = 0;
      bool last = false;
      bool echo_real_last = false;
    };
    std::array<Entry, 2> ram{};
    std::uint8_t enq_ptr = 0, deq_ptr = 0;  // 1-bit counters
    bool maybe_full = false;
    void enq(const Entry& e) {
      ram[enq_ptr] = e;
      enq_ptr ^= 1u;
    }
    void deq() { deq_ptr ^= 1u; }
    // rocket Queue: maybe_full only changes when exactly one side fires
    void settle(bool did_enq, bool did_deq) {
      if (did_enq != did_deq) maybe_full = did_enq;
    }
    const Entry& head() const { return ram[deq_ptr]; }
  };
  AxiBufQueue buf_ar, buf_aw, buf_w, buf_r, buf_b;

  // AXI4RAM response registers: occupied from the fragment accept until a
  // handoff cycle with no refill behind it; ids and the write echo latch
  // per accepted fragment and rest at their final values.
  bool srams_r_full = false, srams_w_full = false;
  std::uint8_t srams_r_id = 0, srams_w_id = 0;
  bool srams_w_echo_real_last = false;

  // Per-burst stage engines: each stage runs 8 events, starting `delay`
  // edges after the burst-arrival edge, one per cycle.
  struct BurstStages {
    std::uint32_t base = 0;
    std::uint64_t data[8] = {};
    std::uint8_t id = 0;
    long long t0 = -1;      // arrival edge (mirror cycle)
    int got = 0;            // write side: c beats banked so far
    bool active = false;
  };
  BurstStages rd_burst, wr_burst;

  // ---- tile-boundary TLBuffer pointer queues (prci_domain buffer_1) ----
  // Only the counters survive dead-pruning; each queue holds one beat for
  // one cycle in the traffic seen here.  a: enq at the fabric accept, deq
  // at the route-register load.  c: enq one edge before each manager put
  // beat.  d: enq at the tile-side dequeue, deq one edge later.  e: the
  // GrantAck crosses one edge after the MSHR enters its finish state and
  // leaves the next.
  struct PtrQueue {
    std::uint8_t enq_ptr = 0, deq_ptr = 0;
    bool maybe_full = false;
    void settle(bool did_enq, bool did_deq) {
      if (did_enq) enq_ptr ^= 1u;
      if (did_deq) deq_ptr ^= 1u;
      if (did_enq != did_deq) maybe_full = did_enq;
    }
  };
  PtrQueue tb_a, tb_c, tb_d, tb_e;
  // cbus boundary buffer: A enq at the route load, deq at the route fire;
  // D enq at the device-side beat (fragmenter emission or single-beat ack),
  // deq at the manager response beat.
  PtrQueue cq_a, cq_d;
  bool cbus_emit_now_ = false;
  std::uint32_t cbus_emit_addr_ = 0;

  // ---- remaining hand-modeled bus arbiters ----
  // SystemBus arbitration now comes from the exact cold RTL sidecar.  Only
  // the still-hot tile-master and control-bus seams remain here.
  bool cbus_state3 = false, cbus_state4 = false;
  // tile master xbar: only the dcache's release bursts engage the
  // multi-beat C arbiter (input 1); reads are single-beat pass-throughs.
  bool tlmx_state_0 = false, tlmx_state_1 = false;
  std::uint8_t tlmx_readys_mask = 3;
  std::uint16_t tlmx_c_left = 0;
  std::uint16_t cbus_beatsLeft = 0;
  std::uint8_t cbus_readys_mask = 0x1f;
  static std::uint8_t cbus_device_id(std::uint32_t address) {
    if ((address >> 16) == 1u) return 4;          // bootrom
    if (address < 0x1000u) return 3;              // debug module
    if ((address >> 24) == 0x02u) return 1;       // clint
    if ((address >> 24) == 0x0cu) return 2;       // plic
    return 0;                                     // error device
  }

  // ---- cbus: bootrom fragmenter + atomics front ----
  // The bootrom coupler answers an icache line fetch as eight 64-bit
  // fragments starting the route edge; the repeater holds the request
  // while they stream and dToggle flips once per burst.  The atomics
  // stage's d_first counter tracks the beats remaining of whatever D
  // burst is crossing the control bus (bootrom or debug-ROM fetches).
  std::uint8_t br_gennum = 0;
  bool br_repeater_full = false;
  std::uint8_t br_saved_size = 0;
  std::uint8_t br_saved_source = 0;
  bool br_dToggle = false;
  bool br_active = false;
  // debug-module coupler fragmenter (same machinery, 0x000-0xfff window)
  std::uint8_t dbg_gennum = 0;
  bool dbg_repeater_full = false;
  std::uint8_t dbg_saved_size = 0;
  std::uint8_t dbg_saved_source = 0;
  std::uint8_t dbg_saved_opcode = 0;
  bool dbg_dToggle = false;
  bool dbg_active = false;
  bool cbus_state1 = false;
  std::uint16_t cbus_d_first_counter = 0;
  static bool bootrom_address(std::uint32_t address) {
    return (address >> 16) == 1u;
  }
  std::uint8_t tb_e_enq_arm_ = 0;     // set at the MSHR finish edge
  std::uint8_t tb_e_enq_ready_ = 0;   // fires the following edge
  std::uint8_t tb_e_deq_pending_ = 0;

  void reset() { *this = AxiChainMirror{}; }

  /** One cycle. `beats` = the fabric's manager-side events this cycle. */
  // ---- calibrated tile->mbus phase ----
  // The fabric's manager beats land on the same lockstep step as the
  // mbus-side register updates (the 12-cycle gap first measured was a
  // bookkeeping artifact: the fabric's debug counter starts after reset,
  // the lockstep cycle does not).  The ring stays so a nonzero phase can
  // be re-dialed if a contended case ever needs it; Micro-Lockstep is the
  // referee either way.
  static constexpr unsigned kPhase = 0;
  unsigned long long cycle_ = 0;
  static bool mbus_address(std::uint32_t address) {
    return (address & UINT32_C(0x80000000)) != 0;
  }
  static bool debug_enabled() {
    static const bool on = getenv("SYSMIRROR_DEBUG") != nullptr;
    return on;
  }
  std::array<SmallICacheMemoryPath::ManagerBeats, 16> ring_{};
  unsigned ring_wr_ = 0;

  // Model tile source -> sbus inner source (RTL): the dcache MSHR sources
  // sit at 16+n in the system-bus numbering; the broadcast hub prefixes
  // acquires with transform=3 (single core: never shared).  Releases carry
  // the dedicated release source 18 with prefix 0b10.
  static std::uint8_t read_axi_source(std::uint8_t model_source) {
    return static_cast<std::uint8_t>(0x60u | (16u + model_source));
  }
  static constexpr std::uint8_t kWriteAxiSource = 0x52;  // 0b10_10010
  std::uint8_t writes_inflight_ = 0;

  std::array<std::uint8_t, 2> prev_mshr_state_{};
  void step(const SmallICacheMemoryPath::ManagerBeats& beats_now,
            std::uint8_t mshr0_state, std::uint8_t mshr1_state) {
    ++cycle_;
    ring_[ring_wr_ & 15u] = beats_now;
    const SmallICacheMemoryPath::ManagerBeats& beats =
        ring_[(ring_wr_ + 16u - kPhase) & 15u];
    ++ring_wr_;

    // Quiet cycle: no beat in the consumed slot, no burst engine within its
    // schedule, no countdown pending and no MSHR finish edge.  Every
    // register below then either holds or re-latches its idle value; apply
    // those idle re-latches and return.
    {
      const long long now_q = static_cast<long long>(cycle_);
      const bool beat = beats.a_fire || beats.a_accept_fire || beats.c_accept_fire ||
                        beats.a_enq_fire || beats.c_write_fire || beats.d_deq_fire ||
                        beats.d_fire;
      const bool rd_busy = rd_burst.active && now_q - rd_burst.t0 <= 10;
      const bool wr_busy = wr_burst.active && now_q - wr_burst.t0 <= 10;
      bool countdown = false;
      for (const auto& t : trackers) countdown |= t.got_e_countdown >= 0;
      const bool quiet = !beat && !rd_busy && !wr_busy && !countdown &&
                         !mshr_refill_pending[0] && !mshr_refill_pending[1] &&
                         mshr0_state == prev_mshr_state_[0] &&
                         mshr1_state == prev_mshr_state_[1] &&
                         !br_active && !dbg_active && tb_e_enq_arm_ == 0 &&
                         tb_e_enq_ready_ == 0 && tb_e_deq_pending_ == 0;
      if (quiet) {
        gen257 = false;
        if (aarb_beatsLeft == 0) aarb_state = {};
        if (darb_beatsLeft == 0) darb_state = {};
        t2a_b_delay = 0;
        cbus_state1 = false;
        cbus_emit_now_ = false;
        tlmx_state_0 = tlmx_state_1 = false;
        if (cbus_beatsLeft == 0) cbus_state3 = cbus_state4 = false;
        return;
      }
    }

    if (debug_enabled() && (beats.a_fire || beats.c_write_fire || beats.d_fire))
      fprintf(stderr,
              "[MIRROR] c%llu a=%d src=%u sz=%u addr=%x cw=%d cf=%d cl=%d "
              "caddr=%x d=%d has=%d last=%d dsrc=%u daddr=%x\n",
              (unsigned long long)cycle_, beats.a_fire, beats.a.source,
              beats.a.size, beats.a.address, beats.c_write_fire, beats.c_first,
              beats.c_last, beats.c_address, beats.d_fire, beats.d_has_data,
              beats.d_last, beats.d_source, beats.d_address);

    // ---------- TLBroadcast trackers ----------
    for (auto& t : trackers)
      if (t.got_e_countdown >= 0 && --t.got_e_countdown < 0) t.got_e = true;
    if (beats.a_enq_fire && mbus_address(beats.a_enq.address)) {
      const std::uint32_t line = beats.a_enq.address >> 6;
      int pick = -1;
      for (int i = 0; i < 4; ++i)
        if (trackers[i].address >> 6 == line) { pick = i; break; }
      if (pick < 0)
        for (int i = 0; i < 4; ++i)
          if (trackers[i].idle()) { pick = i; break; }
      if (pick >= 0) {
        BroadcastTracker& t = trackers[pick];
        t.address = beats.a_enq.address;
        t.opcode = beats.a_enq.opcode;
        t.size = beats.a_enq.size;
        t.source = static_cast<std::uint8_t>(16u + beats.a_enq.source);
        t.sent_d = false;
        t.got_e =
            beats.a_enq.opcode != 6 && beats.a_enq.opcode != 7;
        t.got_e_countdown = -1;
        t.o_enq_ptr = (t.o_enq_ptr + 1u) & 7u;
        t.o_maybe_full = true;
        route_order[route_tail & 7u] = static_cast<std::uint8_t>(pick);
        ++route_tail;
      }
    }

    for (int i = 0; i < 2; ++i) {
      if (mshr_refill_pending[i]) {
        mshr_refill[i] =
            static_cast<std::uint8_t>((mshr_refill[i] + 1u) & 7u);
        mshr_refill_pending[i] = 0;
      }
    }
    if (beats.d_deq_fire && beats.d_deq_has_data && beats.d_deq_source < 2) {
      const int i = beats.d_deq_source;
      mshr_counter[i] = mshr_counter[i] == 0
                            ? 7u
                            : static_cast<std::uint8_t>(mshr_counter[i] - 1u);
      mshr_refill_pending[i] = 1;
    }

    // GrantAck: the dcache MSHR enters its finish state (state 14) exactly
    // when the RTL mshr arbitrates its mem_finish; the E beat reaches the
    // broadcast a fixed pipe later.  MSHR index n acquires with source n.
    const std::array<std::uint8_t, 2> mshr_now{mshr0_state, mshr1_state};
    for (int i = 0; i < 2; ++i) {
      if (mshr_now[i] == 14u && prev_mshr_state_[i] != 14u) {
        if (debug_enabled())
          fprintf(stderr, "[MIRROR] c%llu mshr%d-finish\n",
                  (unsigned long long)cycle_, i);
        // A GrantAck is only owed when the grant came through the broadcast
        // (a tracker is waiting); un-tracked fills answer with plain acks.
        const std::uint8_t inner = static_cast<std::uint8_t>(16u + i);
        for (auto& t : trackers)
          if (t.source == inner && !t.got_e && t.got_e_countdown < 0) {
            t.got_e_countdown = kGrantAckDelay;
            ++tb_e_enq_arm_;
            break;
          }
      }
      prev_mshr_state_[i] = mshr_now[i];
    }

    // Only traffic the RTL routes to the memory bus: DRAM-range addresses.
    // The model funnels bootrom/debug reads through the same manager, but
    // in RTL those traverse the control bus instead.
    const bool a_get_fire = beats.a_fire && mbus_address(beats.a.address);
    const bool a_put_beat =
        beats.c_write_fire && mbus_address(beats.c_address);
    const bool a_put_first = a_put_beat && beats.c_first;
    const bool a_put_last = a_put_beat && beats.c_last;

    // GEN_257 uses the pre-update in-flight bit of the source presented on
    // out.a this cycle (nonzero only when a same-source op is still open).
    // Reads flow through: the in-flight bit is pre-edge (set only when a
    // same-source op is still open).  Writes: the AW crosses the buffer one
    // cycle before the first data beat, so the bit reads set on every beat.
    // ... and the whole W presentation leads these beats by one, so the
    // stall window covers every beat but the last.
    gen257 = a_get_fire ? t2a_count[read_axi_source(beats.a.source)]
                        : (a_put_beat && !a_put_last);

    // out.a arbiter: while idle the winner one-hot re-latches every cycle
    // (zero when nothing is presented); it holds only across a multi-beat
    // burst.  Gets latch a zero beat count; the putfull burst counts 7..0.
    if (a_get_fire) {
      aarb_state = {};
      // route_order head was assigned at the route-register load; peek the
      // tracker that owns this fire (popped below in the same cycle).
      const std::uint8_t trk =
          route_head != route_tail ? route_order[route_head & 7u] : 0u;
      aarb_state[1u + trk] = true;
      aarb_beatsLeft = 0;
    } else if (a_put_first) {
      aarb_state = {};
      aarb_state[0] = true;
      aarb_beatsLeft = 7;
    } else if (a_put_beat) {
      aarb_beatsLeft = static_cast<std::uint8_t>(aarb_beatsLeft - 1);
    } else if (aarb_beatsLeft == 0) {
      aarb_state = {};  // idle re-latch with no requester
    }

    // in.d arbiter: memory-response bursts latch 7 and count down; the
    // single-beat ReleaseAck latches zero.
    {
      const bool d_data =
          beats.d_fire && beats.d_has_data && beats.d_external;
      if (d_data) {
        if (darb_beatsLeft == 0) {
          darb_state = {};
          darb_state[1] = true;
          darb_beatsLeft = 7;
        } else {
          darb_beatsLeft = static_cast<std::uint8_t>(darb_beatsLeft - 1);
        }
      } else if (beats.d_fire && beats.d_is_release) {
        darb_state = {};
        darb_state[1] = true;
        darb_beatsLeft = 0;
      } else if (darb_beatsLeft == 0) {
        darb_state = {};  // idle re-latch with no requester
      }
    }

    // ---------- TLToAXI4 A-side ----------
    // counter tracks remaining beats of the current TL A burst; doneAW is
    // "AW already issued, burst still streaming".
    if (a_get_fire) {
      t2a_counter = 0;
      t2a_doneAW = false;
    }
    if (a_put_beat) {
      if (a_put_first) t2a_counter = 7;  // 64B line: beats1 = 7
      else t2a_counter = static_cast<std::uint8_t>(t2a_counter - 1);
      t2a_doneAW = !a_put_last;
    }

    if (a_get_fire) {
      if (route_head != route_tail) {
        BroadcastTracker& t = trackers[route_order[route_head & 7u]];
        ++route_head;
        t.o_deq_ptr = (t.o_deq_ptr + 1u) & 7u;
        t.o_maybe_full = false;
      }
      const std::uint8_t src = read_axi_source(beats.a.source);
      t2a_count[src] = true;
      YankQueue::Entry e;
      e.size = beats.a.size;
      e.source = src;
      e.extra_id = static_cast<std::uint8_t>((src >> 4) & 7u);
      yank_ar[src & 0xf].enq(e);
    }
    if (a_put_first) {
      const std::uint8_t src = kWriteAxiSource;
      t2a_count[src] = true;
      YankQueue::Entry e;
      e.size = 6;  // release bursts are full lines
      e.source = src;
      e.extra_id = static_cast<std::uint8_t>((src >> 4) & 7u);
      yank_aw[src & 0xf].enq(e);
      ++writes_inflight_;
    }

    // ---------- D side ----------
    const bool d_mbus = beats.d_fire && beats.d_external;
    if (d_mbus && beats.d_has_data) {
      // R data beat toward the tile; on last, the AR yank entry pops and
      // the in-flight bit clears.
      t2a_r_holds_d = !beats.d_last;
      t2a_r_first = beats.d_last;
      if (beats.d_last) {
        const std::uint8_t src = read_axi_source(beats.d_source);
        if (!yank_ar[src & 0xf].empty()) yank_ar[src & 0xf].deq();
        t2a_count[src] = false;
        const std::uint8_t inner =
            static_cast<std::uint8_t>(16u + beats.d_source);
        for (auto& t : trackers)
          if (t.source == inner && !t.sent_d) {
            t.sent_d = true;
            break;
          }
      }
    } else if (beats.d_fire && beats.d_is_release && writes_inflight_ != 0) {
      // Write acknowledgement (ReleaseAck upstream): AW yank entry pops.
      // Identified semantically -- the fabric does not carry the write
      // address on the ack, so the DRAM filter must not be applied here.
      const std::uint8_t src = kWriteAxiSource;
      if (!yank_aw[src & 0xf].empty()) yank_aw[src & 0xf].deq();
      t2a_count[src] = false;
      --writes_inflight_;
    }
    if (t2a_b_delay != 0) t2a_b_delay = 0;  // R never starves B here

    // ---------- cbus fragmenter + atomics ----------
    cbus_state1 =
        beats.a_enq_fire && !mbus_address(beats.a_enq.address);
    cbus_emit_now_ = false;
    if (beats.a_fire && !mbus_address(beats.a.address))
      cbus_emit_addr_ = beats.a.address;
    if (beats.a_fire && bootrom_address(beats.a.address) &&
        beats.a.size >= 4) {
      cbus_emit_now_ = true;
      br_active = true;
      br_gennum = 7;
      br_repeater_full = true;
      br_saved_size = beats.a.size;
      br_saved_source = 0x14;  // icache fetches; lockstep flags other sources
      br_dToggle = !br_dToggle;
    } else if (br_active) {
      if (br_gennum == 0) {
        br_active = false;
      } else {
        cbus_emit_now_ = true;
        --br_gennum;
        br_repeater_full = br_gennum != 0;
      }
    }
    if (beats.a_fire && beats.a.address < 0x1000u)
      dbg_dToggle = !dbg_dToggle;  // flips per response burst, any size
    if (beats.a_fire && beats.a.address < 0x1000u && beats.a.size >= 4) {
      cbus_emit_now_ = true;
      dbg_active = true;
      dbg_gennum = 7;
      dbg_repeater_full = true;
      dbg_saved_size = beats.a.size;
      dbg_saved_source = 0x14;
      dbg_saved_opcode = beats.a.opcode;
    } else if (dbg_active) {
      if (dbg_gennum == 0) {
        dbg_active = false;
      } else {
        cbus_emit_now_ = true;
        --dbg_gennum;
        dbg_repeater_full = dbg_gennum != 0;
      }
    }
    if (beats.d_fire && !beats.d_external) {
      if (cbus_d_first_counter != 0)
        --cbus_d_first_counter;
      else if (beats.d_has_data && beats.d_size == 6)
        cbus_d_first_counter = 7;
    }

    // cbus boundary buffer counters
    {
      const bool a_cbus_enq =
          beats.a_enq_fire && !mbus_address(beats.a_enq.address);
      const bool a_cbus_deq = beats.a_fire && !mbus_address(beats.a.address);
      cq_a.settle(a_cbus_enq, a_cbus_deq);
      const bool small_ack = beats.a_fire &&
                             !mbus_address(beats.a.address) &&
                             beats.a.size < 4;
      const bool d_cbus_deq = beats.d_fire && !beats.d_is_release &&
                              !beats.d_external;
      cq_d.settle(cbus_emit_now_ || small_ack, d_cbus_deq);
    }

    // ---------- crossbar arbiters ----------
    {
      // tile master xbar A arbiter: input 0 = dcache, input 1 = icache;
      // single-beat grants pulse at the fabric accept.
      if (beats.a_accept_fire) {
        const bool icache_won =
            beats.a_accept_source == boomcfg::ICACHE_TL_SOURCE;
        tlmx_state_0 = !icache_won;
        tlmx_state_1 = icache_won;
        tlmx_readys_mask = icache_won ? 0x2 : 0x3;
      } else {
        tlmx_state_0 = tlmx_state_1 = false;
      }

      // cbus D arbiter: device beats (fragmenter emissions / single acks).
      const bool small_ack2 = beats.a_fire &&
                              !mbus_address(beats.a.address) &&
                              beats.a.size < 4;
      const bool dev_beat = cbus_emit_now_ || small_ack2;
      if (dev_beat) {
        const std::uint8_t dev = cbus_device_id(
            cbus_emit_now_ && !small_ack2 ? cbus_emit_addr_ : beats.a.address);
        if (cbus_beatsLeft == 0) {
          cbus_state3 = dev == 3;
          cbus_state4 = dev == 4;
          cbus_readys_mask =
              static_cast<std::uint8_t>(~((1u << dev) - 1u) & 0x1fu);
          cbus_beatsLeft = cbus_emit_now_ ? 7 : 0;
        } else {
          --cbus_beatsLeft;
        }
      } else if (cbus_beatsLeft == 0) {
        cbus_state3 = cbus_state4 = false;
      }
    }

    // ---------- tile-boundary buffer counters ----------
    tb_a.settle(beats.a_accept_fire, beats.a_enq_fire);
    tb_c.settle(beats.c_accept_fire, beats.c_write_fire);
    // d: enqueue rides the fabric's response beat, dequeue the tile-side
    // consume, both same-edge.
    tb_d.settle(beats.d_fire, beats.d_deq_fire);
    {
      const bool e_enq = tb_e_enq_ready_ != 0;
      const bool e_deq = tb_e_deq_pending_ != 0;
      if (e_enq) --tb_e_enq_ready_;
      if (e_deq) --tb_e_deq_pending_;
      if (e_enq) ++tb_e_deq_pending_;
      tb_e.settle(e_enq, e_deq);
      // the finish block above runs earlier in this same step; shift its
      // arm into ready so the enqueue lands one edge after the finish.
      tb_e_enq_ready_ = static_cast<std::uint8_t>(tb_e_enq_ready_ + tb_e_enq_arm_);
      tb_e_enq_arm_ = 0;
    }

    // ---------- harness fragmenter + buffer + RAM timing ----------
    if (a_get_fire) {
      rd_burst = BurstStages{};
      rd_burst.base = beats.a.address;
      rd_burst.id = read_axi_source(beats.a.source) & 0xf;
      rd_burst.t0 = static_cast<long long>(cycle_);
      rd_burst.active = true;
    }
    if (a_put_first) {
      wr_burst = BurstStages{};
      wr_burst.base = beats.c_address;
      wr_burst.id = kWriteAxiSource & 0xf;
      wr_burst.t0 = static_cast<long long>(cycle_);
      wr_burst.active = true;
    }
    if (a_put_beat && wr_burst.active && wr_burst.got < 8)
      wr_burst.data[wr_burst.got++] = beats.c_data;

    const long long now = static_cast<long long>(cycle_);
    auto stage_index = [now](const BurstStages& b, int delay) {
      // event index firing this cycle for the given stage, or -1
      if (!b.active) return -1;
      const long long i = now - b.t0 - delay;
      return (i >= 0 && i < 8) ? static_cast<int>(i) : -1;
    };

    // read side
    const bool rd_e0 = stage_index(rd_burst, 0) >= 0;
    const bool rd_e1 = stage_index(rd_burst, 1) >= 0;
    const bool rd_e2 = stage_index(rd_burst, 2) >= 0;
    const bool rd_e3 = stage_index(rd_burst, 3) >= 0;
    const bool wr_e0 = stage_index(wr_burst, 0) >= 0;
    const bool wr_e1 = stage_index(wr_burst, 1) >= 0;
    const bool wr_e2 = stage_index(wr_burst, 2) >= 0;
    const bool wr_e3 = stage_index(wr_burst, 3) >= 0;
    if (int i = stage_index(rd_burst, 0); i >= 0) {
      frag_rd.busy = i < 7;
      frag_rd.r_addr = rd_burst.base + 8u * static_cast<std::uint32_t>(i + 1);
      frag_rd.r_len = i == 7 ? 0xff : static_cast<std::uint8_t>(6 - i);
      AxiBufQueue::Entry e;
      e.addr = rd_burst.base + 8u * static_cast<std::uint32_t>(i);
      e.id = rd_burst.id;
      e.echo_real_last = i == 7;
      buf_ar.enq(e);
    }
    if (stage_index(rd_burst, 1) >= 0) buf_ar.deq();
    if (int i = stage_index(rd_burst, 2); i >= 0) {
      AxiBufQueue::Entry e;
      e.id = rd_burst.id;
      e.last = true;
      e.echo_real_last = i == 7;
      buf_r.enq(e);
    }
    if (stage_index(rd_burst, 3) >= 0) buf_r.deq();
    if (rd_e1) {
      srams_r_full = true;
      srams_r_id = rd_burst.id;
    } else if (rd_e2) {
      srams_r_full = false;
    }

    // write side
    if (int i = stage_index(wr_burst, 0); i >= 0) {
      frag_wr.busy = i < 7;
      frag_wr.r_addr = wr_burst.base + 8u * static_cast<std::uint32_t>(i + 1);
      frag_wr.r_len = i == 7 ? 0xff : static_cast<std::uint8_t>(6 - i);
      AxiBufQueue::Entry a;
      a.addr = wr_burst.base + 8u * static_cast<std::uint32_t>(i);
      a.id = wr_burst.id;
      a.echo_real_last = i == 7;
      buf_aw.enq(a);
      AxiBufQueue::Entry w;
      w.data = wr_burst.data[i];
      w.strb = 0xff;
      w.last = true;
      buf_w.enq(w);
    }
    if (stage_index(wr_burst, 1) >= 0) { buf_aw.deq(); buf_w.deq(); }
    if (int i = stage_index(wr_burst, 2); i >= 0) {
      AxiBufQueue::Entry e;
      e.id = wr_burst.id;
      e.echo_real_last = i == 7;
      buf_b.enq(e);
    }
    if (stage_index(wr_burst, 3) >= 0) buf_b.deq();
    if (int i = stage_index(wr_burst, 1); i >= 0) {
      srams_w_full = true;
      srams_w_id = wr_burst.id;
      srams_w_echo_real_last = i == 7;
    } else if (wr_e2) {
      srams_w_full = false;
    }
    buf_ar.settle(rd_e0, rd_e1);
    buf_r.settle(rd_e2, rd_e3);
    buf_aw.settle(wr_e0, wr_e1);
    buf_w.settle(wr_e0, wr_e1);
    buf_b.settle(wr_e2, wr_e3);
  }
};

}  // namespace chisa::boom_system::components
