#pragma once
// ============================================================================
// Small BOOM I-cache path through the tile master xbar and TLBuffer_9.
//
// The locked artifact has two tile A clients (D-cache source 0--3 and
// I-cache source 4), followed by a depth-two A queue.  Returned D beats pass
// through a matching depth-two queue before source routing sends source 4 to
// the I-cache.  A line Get is fragmented into eight 64-bit manager reads.
//
// The protocol state lives here; backing storage does not.  `outputs()` and
// `step()` take a read64 callback so ROM, Debug Module state, and external
// DRAM can remain owned by their respective models.
// ============================================================================

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "queue.h"
#include "small_icache.h"
#include "small_pma.h"

namespace chisa::boom_system::components {

struct SmallTileARequest {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint32_t address = 0;
  std::uint16_t mask = 0;
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;
};

struct SmallTileBRequest {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint32_t address = 0;
  std::uint8_t mask = 0;
  std::uint64_t data = 0;
  bool corrupt = false;
};

struct SmallTileCRequest {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint32_t address = 0;
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;  // beat bytes 8..15 (zero on Small)
  bool corrupt = false;
};

struct SmallTileDResponse {
  bool valid = false;
  std::uint8_t opcode = 0;
  std::uint8_t param = 0;
  std::uint8_t size = 0;
  std::uint8_t source = 0;
  std::uint8_t sink = 0;
  bool denied = false;
  std::uint64_t data = 0;
  std::uint64_t data_hi = 0;  // beat bytes 8..15 (zero on Small)
  bool corrupt = false;
};

struct SmallTileERequest {
  bool valid = false;
  std::uint8_t sink = 0;
};

/** Cold-manager values returned to the registered tile TLBuffer. */
struct SmallExternalManagerInputs {
  bool a_ready = false;
  SmallTileBRequest b{};
  bool c_ready = false;
  SmallTileDResponse d{};
  bool e_ready = false;
};

struct SmallICacheMemoryPathInputs {
  bool reset = false;

  bool icache_a_valid = false;
  std::uint32_t icache_a_address = 0;

  // Temporary neighboring client boundary.  It is a packet offered by the
  // D-cache, not a ready/response value fed back from the memory RTL.
  SmallTileARequest dcache_a{};
  bool dcache_b_ready = false;
  SmallTileCRequest dcache_c{};
  bool dcache_d_ready = true;
  SmallTileERequest dcache_e{};
};

struct SmallICacheMemoryPathOutputs {
  SmallICacheMemoryInputs icache{};
  bool dcache_a_ready = false;
  SmallTileBRequest dcache_b{};
  bool dcache_c_ready = false;
  SmallTileDResponse dcache_d{};
  bool dcache_e_ready = false;

  bool tile_a_valid = false;
  bool tile_a_ready = false;
  SmallTileARequest tile_a{};
  bool manager_a_valid = false;
  SmallTileARequest manager_a{};
  bool manager_b_ready = false;
  SmallTileCRequest manager_c{};
  bool manager_d_ready = false;
  SmallTileERequest manager_e{};
  SmallTileDResponse tile_d{};

  bool memory_read_valid = false;
  std::uint32_t memory_read_address = 0;
  bool memory_write_valid = false;
  std::uint32_t memory_write_address = 0;
  std::uint64_t memory_write_data = 0;
  std::uint64_t memory_write_data_hi = 0;
  std::uint8_t response_beat = 0;
  bool response_valid = false;
  bool response_is_release = false;
  std::uint8_t response_source = 0;
  std::uint8_t response_startup = 0;
  bool route_valid = false;
  std::uint8_t route_source = 0;
  bool c_burst_active = false;
  std::uint8_t c_manager_beat = 0;
  bool pending_a_response_valid = false;
  std::uint8_t pending_a_response_source = 0;
  std::uint8_t pending_a_response_startup = 0;
  bool probe_waiting = false;
  bool probe_sent = false;
  std::uint8_t probe_startup = 0;
  std::uint8_t a_queue_count = 0;
  std::uint8_t d_queue_count = 0;
};

class SmallICacheMemoryPath {
 public:
  SmallICacheMemoryPath()
      : a_queue_(2), b_queue_(2), c_queue_(2), d_queue_(2), e_queue_(2) {}

  /** Per-cycle manager-side beat events recorded during step(), for the
    * AXI-chain register mirror (components/axi_chain_mirror.h). Purely
    * observational — nothing reads it back into the model. */
  struct ManagerBeats {
    bool a_fire = false;          // route register fired toward the manager
    SmallTileARequest a{};        // the routed request (Get-like)
    bool a_accept_fire = false;   // tile A beat accepted into the fabric queue
    std::uint8_t a_accept_source = 0;
    bool c_accept_fire = false;   // tile C beat accepted into the fabric queue
    bool a_enq_fire = false;      // A beat loaded into the route register
    SmallTileARequest a_enq{};    // that request (one cycle ahead of a_fire)
    bool c_write_fire = false;    // one PutFull data beat (release/probe data)
    std::uint64_t c_data = 0;
    std::uint64_t c_data_hi = 0;
    std::uint32_t c_address = 0;
    std::uint8_t c_beat = 0;
    bool c_first = false;
    bool c_last = false;
    bool d_deq_fire = false;      // one D beat consumed at the tile boundary
    std::uint8_t d_deq_source = 0;
    bool d_deq_has_data = false;
    bool d_fire = false;          // one D beat accepted by the tile side
    bool d_external = false;      // came from the cold coherence manager
    bool d_is_release = false;    // ReleaseAck (write acknowledgement)
    std::uint32_t d_address = 0;  // originating request address
    bool d_has_data = false;
    bool d_last = false;
    std::uint8_t d_source = 0;
    std::uint8_t d_size = 0;
  };
  const ManagerBeats& last_beats() const { return last_beats_; }
  unsigned long long debug_cycle_ = 0;



  template <typename Read64>
  SmallICacheMemoryPathOutputs outputs(
      const SmallICacheMemoryPathInputs& input,
      const Read64& read64) const {
    SmallICacheMemoryPathOutputs result;
    result.response_valid = response_valid_;
    result.response_is_release = response_is_release_;
    result.response_source = response_request_.source;
    result.response_startup = response_startup_;
    result.route_valid = route_valid_;
    result.route_source = route_request_.source;
    result.c_burst_active = c_burst_active_;
    result.c_manager_beat = c_manager_beat_;
    result.pending_a_response_valid = pending_a_response_valid_;
    result.pending_a_response_source = pending_a_response_.source;
    result.pending_a_response_startup = pending_a_response_startup_;
    result.probe_waiting = probe_waiting_;
    result.probe_sent = probe_sent_;
    result.probe_startup = probe_startup_;

    const bool d_deq_valid = d_queue_.deq_valid(false);
    const SmallTileDResponse& direct_d =
        d_payload_[d_queue_.deq_ptr()];
    result.icache.tl_d_valid =
        d_deq_valid && direct_d.source == kICacheSource;
    result.icache.tl_d_opcode = direct_d.opcode;
    result.icache.tl_d_size = direct_d.size;
    result.icache.tl_d_data = direct_d.data;
    result.icache.tl_d_data_hi = direct_d.data_hi;
    result.dcache_d = direct_d;
    result.dcache_d.valid =
        d_deq_valid && direct_d.source != kICacheSource;

    const bool d_deq_ready =
        !d_deq_valid || direct_d.source == kICacheSource ||
        input.dcache_d_ready;
    const bool d_enq_ready = d_queue_.enq_ready(d_deq_ready);
    if (response_valid_ && response_startup_ == 0) {
      result.tile_d.valid = true;
      result.tile_d.opcode =
          response_is_release_ ? 6
                               : response_opcode(response_request_.opcode);
      result.tile_d.size = response_request_.size;
      result.tile_d.source = response_request_.source;
      if (!response_is_release_ &&
          response_has_data(response_request_.opcode)) {
        result.memory_read_valid = true;
        result.memory_read_address =
            (response_request_.address &
             ~static_cast<std::uint32_t>(boomcfg::TILE_BEAT_BYTES - 1)) +
            static_cast<std::uint32_t>(response_beat_) *
                boomcfg::TILE_BEAT_BYTES;
        result.tile_d.data = read64(result.memory_read_address);
        if constexpr (boomcfg::ICACHE_BEAT_WORDS == 2) {
          result.tile_d.data_hi = read64(result.memory_read_address + 8u);
        }
      }
      result.response_beat = response_beat_;
    }

    const bool response_fire = result.tile_d.valid && d_enq_ready;
    const bool response_last =
        response_valid_ &&
        (response_is_release_ ||
         response_beat_ + 1u == response_beats(response_request_));
    // The external manager may accept one following A request while the
    // current multi-beat D response is draining.  Its memory latency then
    // overlaps those remaining beats, and pending_a_response_ holds it until
    // the D channel becomes available.  Restricting this overlap to a
    // ReleaseAck inserts a false startup bubble after ordinary refill data.
    const bool response_accepts_route =
        !response_valid_ || !pending_a_response_valid_;
    const bool c_probe_ack =
        input.dcache_c.valid && input.dcache_c.opcode == 4;
    const bool c_deq_valid = c_queue_.deq_valid(false);
    const SmallTileCRequest& manager_c =
        c_payload_[c_queue_.deq_ptr()];
    const bool c_manager_is_release =
        c_deq_valid && manager_c.opcode == 7;
    // Broadcast converts both ReleaseData and ProbeAckData into manager-side
    // writes.  Only voluntary ReleaseData needs a D-channel ReleaseAck, so a
    // ProbeAckData final beat never waits for a response slot.
    const bool release_response_slot =
        !response_valid_ ||
        (response_fire && response_last && !pending_a_response_valid_);
    const bool c_manager_ready =
        c_manager_beat_ + 1u < boomcfg::DCACHE_REFILL_BEATS ||
        !c_manager_is_release ||
        release_response_slot;
    const bool c_manager_fire = c_deq_valid && c_manager_ready;
    const bool c_manager_last =
        c_manager_fire &&
        c_manager_beat_ + 1u == boomcfg::DCACHE_REFILL_BEATS;
    const bool c_owns_manager = c_burst_active_ || c_deq_valid;
    // The final ReleaseData beat frees the manager pipeline on this edge, so
    // an A request may advance into the route register concurrently.
    const bool c_blocks_manager = c_owns_manager && !c_manager_last;
    const bool route_fire =
        route_valid_ && response_accepts_route && !c_blocks_manager;
    const bool route_accepts_a =
        !probe_waiting_ && !c_blocks_manager &&
        (!route_valid_ || route_fire);

    result.dcache_c_ready =
        c_probe_ack ? !probe_ack_valid_
                    : c_queue_.enq_ready(c_manager_ready);
    if (c_manager_fire) {
      result.memory_write_valid = true;
      result.memory_write_address =
          manager_c.address + static_cast<std::uint32_t>(c_manager_beat_) *
                                  boomcfg::TILE_BEAT_BYTES;
      result.memory_write_data = manager_c.data;
      result.memory_write_data_hi = manager_c.data_hi;
    }

    result.tile_a_valid = a_queue_.deq_valid(false);
    result.tile_a_ready = route_accepts_a;
    result.tile_a = a_payload_[a_queue_.deq_ptr()];
    result.tile_a.valid = result.tile_a_valid;
    result.manager_a_valid = route_valid_;
    result.manager_a = route_request_;
    result.manager_a.valid = route_valid_;

    if (probe_waiting_ && probe_startup_ == 0 && !probe_sent_) {
      result.dcache_b.valid = true;
      result.dcache_b.param = 1;  // toB
      result.dcache_b.size = 6;
      result.dcache_b.source = 0;
      result.dcache_b.address = probe_request_.address;
    }

    const ASelection selection = select_a(input);
    const bool a_enq_ready = a_queue_.enq_ready(route_accepts_a);
    result.icache.tl_a_ready = selection.icache_ready && a_enq_ready;
    result.dcache_a_ready = selection.dcache_ready && a_enq_ready;
    result.a_queue_count = static_cast<std::uint8_t>(a_queue_.count());
    result.d_queue_count = static_cast<std::uint8_t>(d_queue_.count());
    return result;
  }

  /** Production path: the five registered TileLink queues remain in the hot
    * model. Every manager-facing request is closed by the cold full-chip RTL;
    * no address-dependent fixed-latency response is synthesized here. */
  // One PRE-register/local-memory projection can serve both the manager
  // offer and the feedback closure. The caller owns its lifetime and must
  // prepare again after an edge or a change to the local backing contents.
  struct HybridEvaluation {
    SmallICacheMemoryPathOutputs output{};
    SmallTileARequest selected_a{};
    bool icache_selected = false;
    bool local_d_selected = false, a_is_external = false, local_a_ready = false;
    bool d_deq_ready = false, d_enq_ready = false;
    bool local_response_fire = false, local_response_last = false;
    bool local_route_fire = false;
    bool a_enq_ready[2] = {}, c_enq_ready[2] = {}, e_enq_ready[2] = {};
    bool icache_selected_ready = false, dcache_selected_ready = false;
  };

  template <typename Read64>
  HybridEvaluation prepare_hybrid(const SmallICacheMemoryPathInputs& input,
                                   const Read64& read64) const {
    HybridEvaluation evaluation;
    auto& result = evaluation.output;
    result.response_valid = response_valid_;
    result.response_is_release = false;
    result.response_source = response_request_.source;
    result.response_startup = response_startup_;
    result.route_valid = route_valid_;
    result.route_source = route_request_.source;

    const bool b_deq_valid = b_queue_.deq_valid(false);
    result.dcache_b = b_payload_[b_queue_.deq_ptr()];
    result.dcache_b.valid = b_deq_valid;
    result.manager_b_ready = b_queue_.enq_ready(input.dcache_b_ready);

    const bool d_deq_valid = d_queue_.deq_valid(false);
    const SmallTileDResponse& direct_d = d_payload_[d_queue_.deq_ptr()];
    result.icache.tl_d_valid =
        d_deq_valid && direct_d.source == kICacheSource;
    result.icache.tl_d_opcode = direct_d.opcode;
    result.icache.tl_d_size = direct_d.size;
    result.icache.tl_d_data = direct_d.data;
    result.icache.tl_d_data_hi = direct_d.data_hi;
    result.dcache_d = direct_d;
    result.dcache_d.valid =
        d_deq_valid && direct_d.source != kICacheSource;
    const bool d_deq_ready =
        !d_deq_valid || direct_d.source == kICacheSource ||
        input.dcache_d_ready;
    const bool d_enq_ready = d_queue_.enq_ready(d_deq_ready);

    SmallTileDResponse local_d;
    if (response_valid_ && response_startup_ == 0) {
      local_d.valid = true;
      local_d.opcode = response_opcode(response_request_.opcode);
      local_d.size = response_request_.size;
      local_d.source = response_request_.source;
      if (response_has_data(response_request_.opcode)) {
        result.memory_read_valid = true;
        result.memory_read_address =
            (response_request_.address &
             ~static_cast<std::uint32_t>(boomcfg::TILE_BEAT_BYTES - 1)) +
            static_cast<std::uint32_t>(response_beat_) *
                boomcfg::TILE_BEAT_BYTES;
        local_d.data = read64(result.memory_read_address);
        if constexpr (boomcfg::ICACHE_BEAT_WORDS == 2) {
          local_d.data_hi = read64(result.memory_read_address + 8u);
        }
      }
      result.response_beat = response_beat_;
    }
    const bool local_d_selected = local_d.valid;
    result.manager_d_ready = !local_d_selected && d_enq_ready;
    result.tile_d = local_d;
    evaluation.local_d_selected = local_d_selected;
    const bool local_response_fire = local_d.valid && d_enq_ready;
    const bool local_response_last =
        response_valid_ &&
        response_beat_ + 1u == response_beats(response_request_);
    evaluation.d_deq_ready = d_deq_ready;
    evaluation.d_enq_ready = d_enq_ready;
    evaluation.local_response_fire = local_response_fire;
    evaluation.local_response_last = local_response_last;

    const bool a_deq_valid = a_queue_.deq_valid(false);
    const SmallTileARequest& queued_a = a_payload_[a_queue_.deq_ptr()];
    const bool a_is_external =
        a_deq_valid && routes_via_cold_manager(queued_a.address);
    const bool local_response_slot =
        !response_valid_ || (local_response_fire && local_response_last);
    const bool local_route_fire = route_valid_ && local_response_slot;
    evaluation.a_is_external = a_is_external;
    evaluation.local_a_ready = !route_valid_ || local_route_fire;
    evaluation.local_route_fire = local_route_fire;
    result.tile_a_valid = a_deq_valid;
    result.tile_a = queued_a;
    result.tile_a.valid = a_deq_valid;
    result.manager_a_valid = a_is_external;
    result.manager_a = queued_a;
    result.manager_a.valid = a_is_external;

    const bool c_deq_valid = c_queue_.deq_valid(false);
    result.manager_c = c_payload_[c_queue_.deq_ptr()];
    result.manager_c.valid = c_deq_valid;
    evaluation.c_enq_ready[0] = c_queue_.enq_ready(false);
    evaluation.c_enq_ready[1] = c_queue_.enq_ready(true);

    const bool e_deq_valid = e_queue_.deq_valid(false);
    result.manager_e = e_payload_[e_queue_.deq_ptr()];
    result.manager_e.valid = e_deq_valid;
    evaluation.e_enq_ready[0] = e_queue_.enq_ready(false);
    evaluation.e_enq_ready[1] = e_queue_.enq_ready(true);

    const ASelection selection = select_a(input);
    evaluation.a_enq_ready[0] = a_queue_.enq_ready(false);
    evaluation.a_enq_ready[1] = a_queue_.enq_ready(true);
    evaluation.selected_a = selection.request;
    evaluation.icache_selected = selection.icache_selected;
    evaluation.icache_selected_ready = selection.icache_ready;
    evaluation.dcache_selected_ready = selection.dcache_ready;
    result.a_queue_count = static_cast<std::uint8_t>(a_queue_.count());
    result.d_queue_count = static_cast<std::uint8_t>(d_queue_.count());
    return evaluation;
  }

  SmallICacheMemoryPathOutputs resolve_hybrid(
      const HybridEvaluation& evaluation, const SmallExternalManagerInputs& manager) const {
    auto result = evaluation.output;
    resolve_hybrid_into(result, evaluation, manager);
    return result;
  }

  const SmallICacheMemoryPathOutputs& resolve_hybrid_in_place(
      HybridEvaluation& evaluation, const SmallExternalManagerInputs& manager) const {
    resolve_hybrid_into(evaluation.output, evaluation, manager);
    return evaluation.output;
  }

  static void resolve_hybrid_into(
      SmallICacheMemoryPathOutputs& result, const HybridEvaluation& evaluation,
      const SmallExternalManagerInputs& manager) {
    result.tile_d = evaluation.local_d_selected ? result.tile_d : manager.d;
    result.tile_a_ready = evaluation.a_is_external ? manager.a_ready : evaluation.local_a_ready;
    const bool a_ready = evaluation.a_enq_ready[result.tile_a_ready ? 1 : 0];
    result.icache.tl_a_ready = evaluation.icache_selected_ready && a_ready;
    result.dcache_a_ready = evaluation.dcache_selected_ready && a_ready;
    result.dcache_c_ready = evaluation.c_enq_ready[manager.c_ready ? 1 : 0];
    result.dcache_e_ready = evaluation.e_enq_ready[manager.e_ready ? 1 : 0];
  }

  template <typename Read64>
  SmallICacheMemoryPathOutputs hybrid_outputs(
      const SmallICacheMemoryPathInputs& input, const SmallExternalManagerInputs& manager,
      const Read64& read64) const {
    return resolve_hybrid(prepare_hybrid(input, read64), manager);
  }

  void commit_hybrid(const SmallICacheMemoryPathInputs& input,
                     const SmallExternalManagerInputs& manager,
                     const SmallICacheMemoryPathOutputs& output,
                     const HybridEvaluation* prepared = nullptr) {
    if (input.reset) {
      a_queue_.step(true, false, false);
      b_queue_.step(true, false, false);
      c_queue_.step(true, false, false);
      d_queue_.step(true, false, false);
      e_queue_.step(true, false, false);
      response_valid_ = false;
      response_is_release_ = false;
      response_startup_ = 0;
      response_request_ = SmallTileARequest{};
      response_beat_ = 0;
      route_valid_ = false;
      route_request_ = SmallTileARequest{};
      c_manager_beat_ = 0;
      prefer_icache_ = true;
      last_beats_ = ManagerBeats{};
      return;
    }

    // The producer already resolved this edge. Reuse its local decisions;
    // standalone diagnostics may still call the compatibility path.
    const ASelection selection = prepared
        ? ASelection{prepared->selected_a.valid, prepared->icache_selected,
                     prepared->icache_selected_ready,
                     prepared->dcache_selected_ready, prepared->selected_a}
        : select_a(input);
    const bool b_enq_ready = output.manager_b_ready;

    const bool d_deq_valid = d_queue_.deq_valid(false);
    const SmallTileDResponse& direct_d = d_payload_[d_queue_.deq_ptr()];
    const bool d_deq_ready = prepared ? prepared->d_deq_ready :
        (!d_deq_valid || direct_d.source == kICacheSource || input.dcache_d_ready);
    const bool d_enq_ready = prepared ? prepared->d_enq_ready :
        d_queue_.enq_ready(d_deq_ready);
    const bool d_enq_valid = output.tile_d.valid;

    const bool local_d_selected = prepared ? prepared->local_d_selected :
        (response_valid_ && response_startup_ == 0);
    const bool local_response_fire = prepared ? prepared->local_response_fire :
        (local_d_selected && d_enq_ready);
    const bool local_response_last = prepared ? prepared->local_response_last :
        (response_valid_ && response_beat_ + 1u == response_beats(response_request_));

    const bool a_deq_valid = output.tile_a_valid;
    const SmallTileARequest& queued_a = output.tile_a;
    const bool a_is_external = output.manager_a_valid;
    const bool local_response_slot =
        !response_valid_ || (local_response_fire && local_response_last);
    const bool local_route_fire = prepared ? prepared->local_route_fire :
        (route_valid_ && local_response_slot);
    const bool a_deq_ready = output.tile_a_ready;
    const bool a_deq_fire = a_deq_valid && a_deq_ready;
    const bool local_a_accept = a_deq_fire && !a_is_external;

    const bool a_enq_ready = prepared ? prepared->a_enq_ready[a_deq_ready] :
        a_queue_.enq_ready(a_deq_ready);
    const bool a_enq_fire = selection.valid && a_enq_ready;
    const bool c_enq_ready = output.dcache_c_ready;
    const bool c_deq_valid = output.manager_c.valid;
    const SmallTileCRequest& queued_c = output.manager_c;
    const bool c_deq_fire = c_deq_valid && manager.c_ready;
    const bool c_has_data = queued_c.opcode == 5 || queued_c.opcode == 7;
    const bool c_last = c_deq_fire &&
                        (!c_has_data ||
                         c_manager_beat_ + 1u ==
                             boomcfg::DCACHE_REFILL_BEATS);
    const bool e_enq_ready = output.dcache_e_ready;

    last_beats_ = ManagerBeats{};
    if (a_deq_fire) {
      last_beats_.a_enq_fire = true;
      last_beats_.a_enq = queued_a;
      if (a_is_external) {
        last_beats_.a_fire = true;
        last_beats_.a = queued_a;
      }
    }
    if (local_route_fire) {
      last_beats_.a_fire = true;
      last_beats_.a = route_request_;
    }
    if (a_enq_fire) {
      a_payload_[a_queue_.enq_ptr()] = selection.request;
      prefer_icache_ = !selection.icache_selected;
      last_beats_.a_accept_fire = true;
      last_beats_.a_accept_source = selection.request.source;
    }
    if (manager.b.valid && b_enq_ready)
      b_payload_[b_queue_.enq_ptr()] = manager.b;
    if (input.dcache_c.valid && c_enq_ready) {
      c_payload_[c_queue_.enq_ptr()] = input.dcache_c;
      last_beats_.c_accept_fire = true;
    }
    if (c_deq_fire) {
      last_beats_.c_write_fire = c_has_data;
      last_beats_.c_address = queued_c.address +
          static_cast<std::uint32_t>(c_manager_beat_) *
              boomcfg::TILE_BEAT_BYTES;
      last_beats_.c_data = queued_c.data;
      last_beats_.c_data_hi = queued_c.data_hi;
      last_beats_.c_beat = c_manager_beat_;
      last_beats_.c_first = c_manager_beat_ == 0;
      last_beats_.c_last = c_last;
    }
    if (d_enq_valid && d_enq_ready) {
      d_payload_[d_queue_.enq_ptr()] = output.tile_d;
      last_beats_.d_fire = true;
      last_beats_.d_external = !local_d_selected;
      last_beats_.d_has_data =
          output.tile_d.opcode == 1 || output.tile_d.opcode == 5;
      last_beats_.d_source = output.tile_d.source;
      last_beats_.d_size = output.tile_d.size;
      last_beats_.d_is_release = output.tile_d.opcode == 6;
      if (local_d_selected) {
        last_beats_.d_address = response_request_.address;
        last_beats_.d_last = local_response_last;
      }
    }
    if (input.dcache_e.valid && e_enq_ready)
      e_payload_[e_queue_.enq_ptr()] = input.dcache_e;

    if (d_deq_valid && d_deq_ready) {
      last_beats_.d_deq_fire = true;
      last_beats_.d_deq_source = direct_d.source;
      last_beats_.d_deq_has_data =
          direct_d.opcode == 1 || direct_d.opcode == 5;
    }

    if (response_valid_ && response_startup_ != 0) {
      --response_startup_;
    } else if (local_response_fire) {
      if (local_response_last) {
        response_valid_ = false;
        response_beat_ = 0;
      } else {
        ++response_beat_;
      }
    }
    if (local_route_fire) {
      response_valid_ = true;
      response_is_release_ = false;
      response_request_ = route_request_;
      response_startup_ = boomcfg::LOCAL_RESPONSE_STARTUP;
      response_beat_ = 0;
    }
    if (local_a_accept) {
      route_valid_ = true;
      route_request_ = queued_a;
    } else if (local_route_fire) {
      route_valid_ = false;
      route_request_ = SmallTileARequest{};
    }
    if (c_deq_fire) {
      if (c_last)
        c_manager_beat_ = 0;
      else if (c_has_data)
        ++c_manager_beat_;
    }

    a_queue_.step(false, selection.valid, a_deq_ready);
    b_queue_.step(false, manager.b.valid, input.dcache_b_ready);
    c_queue_.step(false, input.dcache_c.valid, manager.c_ready);
    d_queue_.step(false, d_enq_valid, d_deq_ready);
    e_queue_.step(false, input.dcache_e.valid, manager.e_ready);
  }

  void commit(const SmallICacheMemoryPathInputs& input,
              const SmallICacheMemoryPathOutputs& output) {
    if (input.reset) {
      a_queue_.step(true, false, false);
      b_queue_.step(true, false, false);
      c_queue_.step(true, false, false);
      d_queue_.step(true, false, false);
      e_queue_.step(true, false, false);
      route_valid_ = false;
      response_valid_ = false;
      response_is_release_ = false;
      response_startup_ = 0;
      response_beat_ = 0;
      pending_a_response_valid_ = false;
      pending_a_response_ = SmallTileARequest{};
      pending_a_response_startup_ = 0;
      probe_ack_valid_ = false;
      probe_ack_ = SmallTileCRequest{};
      probe_waiting_ = false;
      probe_sent_ = false;
      probe_startup_ = 0;
      probe_request_ = SmallTileARequest{};
      probe_data_finish_pending_ = false;
      probe_data_finish_startup_ = 0;
      c_burst_active_ = false;
      c_manager_beat_ = 0;
      prefer_icache_ = true;
      return;
    }

    const ASelection selection = select_a(input);

    const bool d_deq_valid = d_queue_.deq_valid(false);
    const SmallTileDResponse& direct_d =
        d_payload_[d_queue_.deq_ptr()];
    const bool d_deq_ready =
        !d_deq_valid || direct_d.source == kICacheSource ||
        input.dcache_d_ready;
    const bool d_enq_ready = d_queue_.enq_ready(d_deq_ready);
    const bool response_fire = output.tile_d.valid && d_enq_ready;
    const bool response_last =
        response_valid_ &&
        (response_is_release_ ||
         response_beat_ + 1u == response_beats(response_request_));
    const bool response_accepts_route =
        !response_valid_ || !pending_a_response_valid_;
    const bool c_probe_ack =
        input.dcache_c.valid && input.dcache_c.opcode == 4;
    const bool c_deq_valid = c_queue_.deq_valid(false);
    const SmallTileCRequest& manager_c =
        c_payload_[c_queue_.deq_ptr()];
    const bool c_manager_is_release =
        c_deq_valid && manager_c.opcode == 7;
    const bool release_response_slot =
        !response_valid_ ||
        (response_fire && response_last && !pending_a_response_valid_);
    const bool c_manager_ready =
        c_manager_beat_ + 1u < boomcfg::DCACHE_REFILL_BEATS ||
        !c_manager_is_release ||
        release_response_slot;
    const bool c_manager_fire = c_deq_valid && c_manager_ready;
    const bool c_manager_last =
        c_manager_fire &&
        c_manager_beat_ + 1u == boomcfg::DCACHE_REFILL_BEATS;
    const bool c_owns_manager = c_burst_active_ || c_deq_valid;
    const bool c_blocks_manager = c_owns_manager && !c_manager_last;
    const bool route_fire =
        route_valid_ && response_accepts_route && !c_blocks_manager;
    const bool route_accepts_a =
        !probe_waiting_ && !c_blocks_manager &&
        (!route_valid_ || route_fire);

    ++debug_cycle_;
    static const bool fabric_debug = getenv("SYSFABRIC_DEBUG") != nullptr;
    if (fabric_debug &&
        (route_fire || c_manager_fire || response_fire))
      fprintf(stderr, "[FAB] c%llu rf=%d src=%u addr=%x cf=%d resp=%d rsrc=%u raddr=%x last=%d\n",
              (unsigned long long)debug_cycle_,
              route_fire, route_request_.source, route_request_.address,
              c_manager_fire, response_fire, response_request_.source,
              response_request_.address, response_last);
    // Record this cycle's manager-side beats for the AXI-chain mirror.
    last_beats_ = ManagerBeats{};
    if (d_deq_valid && d_deq_ready) {
      last_beats_.d_deq_fire = true;
      last_beats_.d_deq_source = direct_d.source;
      // direct_d.opcode is a response opcode: AccessAckData=1, GrantData=5.
      last_beats_.d_deq_has_data =
          direct_d.opcode == 1 || direct_d.opcode == 5;
    }
    last_beats_.a_fire = route_fire;
    if (route_fire) last_beats_.a = route_request_;
    if (c_manager_fire) {
      last_beats_.c_write_fire = true;
      last_beats_.c_address = manager_c.address +
          static_cast<std::uint32_t>(c_manager_beat_) *
              boomcfg::TILE_BEAT_BYTES;
      last_beats_.c_data = manager_c.data;
      last_beats_.c_data_hi = manager_c.data_hi;
      last_beats_.c_beat = c_manager_beat_;
      last_beats_.c_first = (c_manager_beat_ == 0);
      last_beats_.c_last = c_manager_last;
    }
    if (response_fire) {
      last_beats_.d_fire = true;
      last_beats_.d_is_release = response_is_release_;
      last_beats_.d_has_data =
          !response_is_release_ && response_has_data(response_request_.opcode);
      last_beats_.d_last = response_last;
      last_beats_.d_source = response_request_.source;
      last_beats_.d_address = response_request_.address;
      last_beats_.d_size = response_request_.size;
    }

    const bool a_enq_ready = a_queue_.enq_ready(route_accepts_a);
    const bool a_enq_fire = selection.valid && a_enq_ready;
    const bool a_deq_fire =
        a_queue_.deq_valid(selection.valid) && route_accepts_a;
    const SmallTileARequest dequeued_a =
        a_payload_[a_queue_.deq_ptr()];
    if (a_deq_fire) {
      last_beats_.a_enq_fire = true;
      last_beats_.a_enq = dequeued_a;
    }

    if (a_enq_fire) {
      a_payload_[a_queue_.enq_ptr()] = selection.request;
      prefer_icache_ = !selection.icache_selected;
      last_beats_.a_accept_fire = true;
      last_beats_.a_accept_source = selection.request.source;
    }
    const bool c_enq_valid = input.dcache_c.valid && !c_probe_ack;
    const bool c_enq_ready = c_queue_.enq_ready(c_manager_ready);
    if (c_enq_valid && c_enq_ready) {
      c_payload_[c_queue_.enq_ptr()] = input.dcache_c;
      last_beats_.c_accept_fire = true;
    }
    if (response_fire)
      d_payload_[d_queue_.enq_ptr()] = output.tile_d;

    if (pending_a_response_valid_ && pending_a_response_startup_ != 0)
      --pending_a_response_startup_;

    if (c_manager_last && c_manager_is_release) {
      response_valid_ = true;
      response_is_release_ = true;
      response_request_ = SmallTileARequest{};
      response_request_.size = 6;
      response_request_.source = 2;
      response_startup_ = 2;
      response_beat_ = 0;
    } else if (response_valid_ && response_startup_ != 0) {
      --response_startup_;
    } else if (response_fire) {
      if (response_last) {
        if (pending_a_response_valid_) {
          response_valid_ = true;
          response_is_release_ = false;
          response_request_ = pending_a_response_;
          response_startup_ = pending_a_response_startup_;
          response_beat_ = 0;
          pending_a_response_valid_ = false;
          pending_a_response_ = SmallTileARequest{};
          pending_a_response_startup_ = 0;
        } else {
          response_valid_ = false;
          response_is_release_ = false;
          response_startup_ = 0;
          response_beat_ = 0;
        }
      } else {
        ++response_beat_;
      }
    }

    if (route_fire) {
      // DRAM responses traverse the external AXI AR queue, synchronous RAM,
      // and R queue.  The existing two registered startup stages already
      // model this path for AcquireBlock; coherent I-cache Gets use it too.
      const std::uint8_t startup =
          route_request_.opcode == 6 ||
                  SmallPma::lookup(route_request_.address).cacheable
              ? 2
              : 0;
      if (response_valid_) {
        pending_a_response_valid_ = true;
        pending_a_response_ = route_request_;
        pending_a_response_startup_ = startup;
      } else {
        response_valid_ = true;
        response_is_release_ = false;
        response_request_ = route_request_;
        response_startup_ = startup;
        response_beat_ = 0;
      }
    }

    if (c_manager_fire && !c_manager_last) {
      c_burst_active_ = true;
      ++c_manager_beat_;
    } else if (c_manager_last) {
      c_burst_active_ = false;
      c_manager_beat_ = 0;
    }

    if (probe_waiting_ && probe_startup_ != 0) --probe_startup_;
    if (output.dcache_b.valid && input.dcache_b_ready) probe_sent_ = true;

    if (a_deq_fire) {
      if (dequeued_a.source == kICacheSource &&
          SmallPma::lookup(dequeued_a.address).cacheable) {
        probe_waiting_ = true;
        probe_sent_ = false;
        probe_startup_ = 1;
        probe_request_ = dequeued_a;
      } else {
        route_valid_ = true;
        route_request_ = dequeued_a;
      }
    } else if (route_fire) {
      route_valid_ = false;
    }

    // The final ProbeAckData manager write traverses the same two registered
    // external-response startup stages as the other DRAM transactions.  The
    // blocked Get becomes eligible on the following edge, after that write
    // response has retired.
    if (probe_data_finish_pending_) {
      if (probe_data_finish_startup_ != 0) {
        --probe_data_finish_startup_;
      } else {
        route_valid_ = true;
        route_request_ = probe_request_;
        probe_waiting_ = false;
        probe_sent_ = false;
        probe_startup_ = 0;
        probe_request_ = SmallTileARequest{};
        probe_data_finish_pending_ = false;
      }
    }

    // ProbeAckData carries the dirty line through the manager write path but
    // is still the response to the outstanding B probe.  The blocked Get may
    // proceed only after its eighth beat has been consumed; no D-channel ack
    // is generated for this C opcode.
    if (c_manager_last && manager_c.opcode == 5 && probe_waiting_ &&
        probe_sent_ && manager_c.address == probe_request_.address) {
      probe_data_finish_pending_ = true;
      probe_data_finish_startup_ = 2;
    }

    // Tile C crosses one registered ingress boundary before Broadcast sees a
    // ProbeAck.  Consume the held packet here; a newly accepted packet below
    // becomes visible on the following cycle.
    if (probe_ack_valid_ && probe_waiting_ && probe_sent_ &&
        probe_ack_.address == probe_request_.address) {
      route_valid_ = true;
      route_request_ = probe_request_;
      probe_waiting_ = false;
      probe_sent_ = false;
      probe_startup_ = 0;
      probe_request_ = SmallTileARequest{};
      probe_ack_valid_ = false;
      probe_ack_ = SmallTileCRequest{};
    }

    if (c_probe_ack && output.dcache_c_ready) {
      probe_ack_valid_ = true;
      probe_ack_ = input.dcache_c;
    }

    a_queue_.step(false, selection.valid, route_accepts_a);
    c_queue_.step(false, c_enq_valid, c_manager_ready);
    d_queue_.step(false, output.tile_d.valid, d_deq_ready);
  }

  template <typename Read64>
  void step(const SmallICacheMemoryPathInputs& input,
            const Read64& read64) {
    if (input.reset) {
      commit(input, SmallICacheMemoryPathOutputs{});
      return;
    }
    commit(input, outputs(input, read64));
  }

  std::uint8_t a_queue_count() const {
    return static_cast<std::uint8_t>(a_queue_.count());
  }
  std::uint8_t d_queue_count() const {
    return static_cast<std::uint8_t>(d_queue_.count());
  }
  const Queue& a_queue_for_diagnostic() const { return a_queue_; }
  const Queue& b_queue_for_diagnostic() const { return b_queue_; }
  const Queue& c_queue_for_diagnostic() const { return c_queue_; }
  const Queue& d_queue_for_diagnostic() const { return d_queue_; }
  const Queue& e_queue_for_diagnostic() const { return e_queue_; }
  bool route_valid() const { return route_valid_; }
  bool response_valid() const { return response_valid_; }
  std::uint8_t response_beat() const { return response_beat_; }
  std::uint8_t response_startup() const { return response_startup_; }

 private:
  static constexpr std::uint8_t kICacheSource = boomcfg::ICACHE_TL_SOURCE;

  static bool routes_via_cold_manager(std::uint32_t address) {
    (void)address;
    return true;
  }

  struct ASelection {
    bool valid = false;
    bool icache_selected = false;
    bool icache_ready = false;
    bool dcache_ready = false;
    SmallTileARequest request{};
  };

  ASelection select_a(const SmallICacheMemoryPathInputs& input) const {
    const bool i_valid = input.icache_a_valid;
    const bool d_valid = input.dcache_a.valid;
    ASelection result;

    if (!i_valid && !d_valid) {
      result.icache_ready = true;
      result.dcache_ready = true;
      return result;
    }

    if (i_valid && d_valid) {
      result.icache_selected = prefer_icache_;
      result.icache_ready = prefer_icache_;
      result.dcache_ready = !prefer_icache_;
    } else if (i_valid) {
      result.icache_selected = true;
      result.icache_ready = true;
      // The artifact's mask-based round-robin arbiter also raises ready for
      // the absent preferred input.
      result.dcache_ready = !prefer_icache_;
    } else {
      result.icache_selected = false;
      result.dcache_ready = true;
      result.icache_ready = prefer_icache_;
    }

    result.valid = true;
    if (result.icache_selected) {
      result.request.valid = true;
      result.request.opcode = 4;  // Get
      result.request.size = 6;    // 64-byte line
      result.request.source = kICacheSource;
      result.request.address =
          input.icache_a_address & UINT32_C(0xffffffc0);
      result.request.mask = (UINT32_C(1) << boomcfg::TILE_BEAT_BYTES) - 1u;
    } else {
      result.request = input.dcache_a;
      result.request.source &= boomcfg::DCACHE_SOURCE_MASK;
    }
    return result;
  }

  static bool response_has_data(std::uint8_t request_opcode) {
    return request_opcode == 4 || request_opcode == 6;
  }

  static std::uint8_t response_opcode(std::uint8_t request_opcode) {
    if (request_opcode == 4) return 1;  // AccessAckData
    if (request_opcode == 6) return 5;  // GrantData
    return 0;                           // AccessAck
  }

  static unsigned response_beats(const SmallTileARequest& request) {
    if (!response_has_data(request.opcode) ||
        request.size <= boomcfg::TILE_BEAT_SHIFT)
      return 1;
    return 1u << (request.size - boomcfg::TILE_BEAT_SHIFT);
  }

  Queue a_queue_;
  Queue b_queue_;
  Queue c_queue_;
  Queue d_queue_;
  Queue e_queue_;
  std::array<SmallTileARequest, 2> a_payload_{};
  std::array<SmallTileBRequest, 2> b_payload_{};
  std::array<SmallTileCRequest, 2> c_payload_{};
  std::array<SmallTileDResponse, 2> d_payload_{};
  std::array<SmallTileERequest, 2> e_payload_{};

  bool prefer_icache_ = true;
  bool route_valid_ = false;
  SmallTileARequest route_request_{};
  bool response_valid_ = false;
  bool response_is_release_ = false;
  std::uint8_t response_startup_ = 0;
  SmallTileARequest response_request_{};
  std::uint8_t response_beat_ = 0;
  bool pending_a_response_valid_ = false;
  SmallTileARequest pending_a_response_{};
  std::uint8_t pending_a_response_startup_ = 0;
  bool c_burst_active_ = false;
  std::uint8_t c_manager_beat_ = 0;
  ManagerBeats last_beats_{};
  bool probe_ack_valid_ = false;
  SmallTileCRequest probe_ack_{};
  bool probe_waiting_ = false;
  bool probe_sent_ = false;
  std::uint8_t probe_startup_ = 0;
  SmallTileARequest probe_request_{};
  bool probe_data_finish_pending_ = false;
  std::uint8_t probe_data_finish_startup_ = 0;
};

}  // namespace chisa::boom_system::components
