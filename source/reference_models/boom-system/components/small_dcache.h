#pragma once
#include "../../boom_model/common/boom_config.h"
#include "../../boom_model/common/model_mode.h"
// ============================================================================
// Exercised SmallBoom nonblocking L1 D-cache.
//
// The locked Small configuration is 64 sets x 4 ways x 64-byte lines with
// two MSHRs.  This component owns the cache request pipeline, tags/data,
// refill line buffers, replay queues and MSHR arbitration.  It intentionally
// does not own the TileLink fabric or backing memory; those are connected by
// SmallICacheMemoryPath/MemoryState.
// ============================================================================

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "boom_uncached_path.h"
#include "small_icache_memory_path.h"

namespace chisa::boom_system::components {
/** Diagnostic switch, read once: getenv() per cycle showed up at ~1% of the
  * producer in perf. */
inline bool small_dcache_store_debug_enabled() {
  static const bool enabled = std::getenv("SYSDC_STORE_DEBUG") != nullptr;
  return enabled;
}
}  // namespace chisa::boom_system::components


namespace chisa::boom_system::components {
inline unsigned long long g_dc_step_n = 0;

struct SmallDcacheInputs {
  BoomUncachedRequest raw_request{};
  // The IOMSHR offers its TL-A access this cycle (source 4 of the MSHR
  // file's acquire arbiter; a partition-cut lane).
  bool iomshr_mem_access = false;
  // True when the LSU request fired before MemoryState's PMA routing.  An
  // uncached/debug-window request does not enter the functional D-cache, but
  // it still wins the RTL D-cache s0 request-bus mux and records t_lsu.
  bool raw_request_fire = false;
  // LSU kills the request currently in the D-cache s1 stage when it obtains
  // the load from store-to-load forwarding or an in-flight uop is flushed.
  bool s1_kill = false;
  boomcfg::br_mask_t branch_resolve_mask = 0;
  // brupdate.b1.mispredict_mask this cycle (IsKilledByBranch) and
  // io.lsu.exception (= RegNext(rob.io.flush.valid)).
  boomcfg::br_mask_t branch_kill_mask = 0;
  bool exception = false;
  bool oracle_io_resp_valid = false;
  std::uint64_t oracle_io_resp_data = 0;
  bool reset = false;
  BoomUncachedRequest request{};
  bool tile_a_ready = false;
  SmallTileBRequest tile_b{};
  bool tile_c_ready = false;
  SmallTileDResponse tile_d{};
  bool tile_e_ready = true;
  // Internal DCache -> LSU release search.  This is not TileLink C: it marks
  // loads observed before a dirty victim becomes externally visible.
  bool lsu_release_ready = true;
  // The random replacer advances on every accepted DCache miss, including a
  // request routed to the separate IOMSHR rather than a coherent MSHR.
  bool external_miss_fire = false;
};

struct SmallDcacheOutputs {
  BoomUncachedCompletion response{};
  BoomUncachedCompletion nack{};
  // Exact io.lsu.resp.bits.data mux, intentionally not valid-gated.  BOOM's
  // PTW unconditionally RegNexts this payload, so store acknowledgements and
  // idle response-queue words remain architecturally observable to CHISA.
  std::uint64_t lsu_response_data = 0;
  bool cache_response_valid = false;
  bool request_ready = true;
  bool ordered = true;
  bool tile_d_ready = true;
  SmallTileARequest tile_a{};
  bool tile_b_ready = false;
  SmallTileCRequest tile_c{};
  SmallTileERequest tile_e{};
  bool lsu_release_valid = false;
  std::uint64_t lsu_release_address = 0;

  bool s1_valid = false;
  bool s2_valid = false;
  // Diagnostic copy of the exact RTL pipeline-control shadows.  Keep these
  // beside the compact functional occupancy so seam checks can compare the
  // same cycle-start face instead of accidentally reading the post-step
  // oracle state.
  bool s1_control_valid = false;
  bool s2_control_valid = false;
  bool s2_send_response = false;
  bool s2_control_send_response = false;
  bool s2_hit = false;
  bool s2_miss = false;
  bool s2_primary_miss = false;
  bool s2_secondary_miss = false;
  bool s2_block_hit = false;
  bool s2_nack_writeback = false;
  bool s2_nack_probe = false;
  bool s2_nack_victim = false;
  bool s2_nack_set_conflict = false;
  std::uint8_t s2_hit_way = 0;
  std::array<std::uint8_t, boomcfg::DCACHE_MSHRS> mshr_state{};
  std::array<std::uint8_t, boomcfg::DCACHE_MSHRS> mshr_rpq_count{};
  std::uint8_t mshr_head = 0;
  std::uint8_t mshr_alloc_index = 0;
  std::uint8_t acquire_source = 0;
  std::uint16_t replacement_lfsr = 1;
  std::uint8_t replacement_way = 1;
  std::uint8_t writeback_state = 0;
  std::uint8_t writeback_read_count = 0;
  std::uint8_t writeback_release_beat = 0;
  std::uint8_t prober_state = 0;
};

class SmallDcache {
  friend struct SmallDcachePublicationTest;
 public:
  static constexpr std::size_t kSets = 64;
  static constexpr std::size_t kWays = boomcfg::DCACHE_WAYS;
  // Functional storage stays split into 64-bit words so ordinary LSU loads
  // and stores remain cheap.  TileLink, the refill line buffer, the data
  // array and the writeback unit are instead one beat wide: 64 bits on
  // Small, 128 bits on Large.
  static constexpr std::size_t kLineWords = boomcfg::DCACHE_LINE_WORDS;
  static constexpr std::size_t kTransferBeats =
      boomcfg::DCACHE_REFILL_BEATS;
  static constexpr std::size_t kWordsPerBeat = boomcfg::DCACHE_BEAT_WORDS;
  static constexpr std::size_t kBeats = kLineWords;
  static constexpr std::size_t kMshrs = boomcfg::DCACHE_MSHRS;
  static constexpr std::size_t kRpqDepth = 16;
  static constexpr std::size_t kSdqDepth = 17;
  static constexpr std::uint32_t kSdqFullMask =
      (std::uint32_t{1} << kSdqDepth) - 1u;
  static constexpr std::uint8_t kAllWaysMask =
      static_cast<std::uint8_t>((1u << kWays) - 1u);
  static constexpr std::size_t kLastMshr = kMshrs - 1u;

  static_assert(kWays <= 8 && (kWays & (kWays - 1u)) == 0,
                "D-cache way masks require a power-of-two width <= 8");
  static_assert((kMshrs & (kMshrs - 1u)) == 0,
                "MSHR pointer masks require a power-of-two count");
  static_assert(kTransferBeats * kWordsPerBeat == kLineWords,
                "D-cache transfer geometry must cover one cache line");

  enum class MshrState : std::uint8_t {
    kIdle = 0,
    kAcquire = 1,
    kRefill = 2,
    kDrainLoads = 3,
    kMetaRead = 4,
    kMetaResp1 = 5,
    kMetaResp2 = 6,
    kMetaClear = 7,
    kWritebackMetaRead = 8,
    kWritebackReq = 9,
    kWritebackResp = 10,
    kCommitLine = 11,
    kReplay = 12,
    kMetaWrite = 13,
    kFinish1 = 14,
    kFinish2 = 15,
  };

  enum class WritebackState : std::uint8_t {
    kIdle = 0,
    kFillBuffer = 1,
    kLsuRelease = 2,
    kActive = 3,
    kGrant = 4,
  };

  enum class ProberState : std::uint8_t {
    kIdle = 0,
    kMetaRead = 1,
    kMetaResp = 2,
    kMshrReq = 3,
    kMshrResp = 4,
    kLsuRelease = 5,
    kRelease = 6,
    kWritebackReq = 7,
    kWritebackResp = 8,
    kMetaWrite = 9,
    kMetaWriteResp = 10,
  };

  SmallDcache() { reset(); }

  void reset() {
    s1_ = BoomUncachedRequest{};
    s2_ = BoomUncachedRequest{};
    s1_replay_ = false;
    s2_replay_ = false;
    s1_send_response_ = false;
    s2_send_response_ = false;
    s1_lookup_ = Lookup{};
    s2_lookup_ = Lookup{};
    writeback_s1_valid_ = false;
    writeback_s2_valid_ = false;
    writeback_s1_beat_ = 0;
    writeback_s2_beat_ = 0;
    respq_enq_ = 0;
    respq_deq_ = 0;
    respq_maybe_full_ = false;
    respq_count_ = 0;
    respq_valid_.fill(false);
    respq_head_prev_ = 0;
    s2_wb_idx_match_ = false;
    s2_nack_hit_ = false;
    writeback_ = Writeback{};
    prober_ = Prober{};
    mshr_head_ = 0;
    mshr_alloc_index_ = 0;
    replacement_lfsr_ = UINT16_C(1);
    // RegNext(replacer.way) reads the LFSR's pre-reset zero image at cycle
    // 1 and the reset value afterwards.
    s2_replacement_way_ = dc_steps_ == 1 ? 0 : 1;
    replay_store_write_pipe_.fill(false);
    sdq_val_ = 0;
    sdq_alloc_view_ = 0;
    metadata_reset_cycles_ = kSets;
    for (auto& set : meta_) {
      set.valid.fill(false);
      set.dirty.fill(false);
      set.writable.fill(false);
      set.tag.fill(0);
    }
    for (auto& way : data_)
      for (auto& set : way) set.fill(0);
    for (Mshr& mshr : mshrs_) mshr = Mshr{};
  }

  SmallDcacheOutputs outputs(const SmallDcacheInputs& input) const {

    SmallDcacheOutputs result;

    outputs_into(input, result);

    return result;

  }

  /** The cycle-start face, evaluated at most once per cycle for a given
    * (kill mask, exception) pair: the cache does not change between the
    * MemoryState evaluation and the step that consumes it.  eval_gen_
    * advances at the end of step(). */
  const SmallDcacheOutputs& evaluate(const SmallDcacheInputs& input) const {
    if (eval_cache_gen_ != eval_gen_ || eval_cache_kill_ != input.branch_kill_mask ||
        eval_cache_exc_ != input.exception) {
      outputs_into(input, eval_cache_);
      eval_cache_gen_ = eval_gen_;
      eval_cache_kill_ = input.branch_kill_mask;
      eval_cache_exc_ = input.exception;
    }
    return eval_cache_;
  }

  // The commit phase needs classification and valid bits, not the complete
  // TileLink/response-data projection. Recompute this narrow face after the
  // queue changes; reusing the earlier PRE output would lose those changes.
  struct PipelineOutputs {
    struct Completion { bool valid = false; } response, nack;
    bool request_ready = false, cache_response_valid = false;
    bool s2_block_hit = false, s2_hit = false, s2_miss = false;
    bool s2_nack_probe = false, s2_nack_victim = false, s2_nack_writeback = false;
    bool s2_secondary_miss = false, s2_nack_set_conflict = false, s2_primary_miss = false;
    std::uint8_t s2_hit_way = 0;
  };

  template <bool WithData, typename Result>
  void pipeline_outputs_into(const SmallDcacheInputs& input, Result& result) const {
    const auto reply = [&](auto& completion, std::uint64_t data = 0) {
      if constexpr (WithData) completion = completion_for(s2_, data);
      else completion.valid = true;
    };
    const Lookup lookup = s2_lookup_;
    // A replay carries the MSHR-selected way because metadata is installed
    // only after the RPQ drains.  RTL therefore treats every replay as a hit
    // without consulting the ordinary tag/permission result.
    // An allocated MSHR continues to own its line until the replay/metadata
    // sequence finishes.  The tag SRAM can still contain the old matching
    // entry in the meantime, but BoomMSHRFile.io.block_hit suppresses that
    // apparent hit so the request joins (or retries behind) the MSHR.
    result.s2_block_hit =
        s2_.valid && !s2_replay_ && mshr_blocks_hit(s2_.address);
    const bool pipeline_hit =
        s2_replay_ ||
        (request_hits_pipeline(s2_, lookup) && !result.s2_block_hit);
    result.s2_hit = s2_.valid && pipeline_hit;
    result.s2_miss = s2_.valid && !pipeline_hit;
    result.s2_hit_way = lookup.way;

    int matching_mshr = -1;
    int conflicting_mshr = -1;
    int idle_mshr = -1;
    // BoomMSHRFile gates every coherent primary/secondary request with
    // sdq_rdy, even a load that would not allocate an SDQ entry.  This is a
    // cycle-start register view: a replay freeing an entry on this edge does
    // not make the same edge's s2 request ready.
    const bool sdq_ready = sdq_has_free_slot(sdq_val_);
    result.s2_nack_probe =
        s2_.valid && s2_nack_hit_ && !s2_replay_;
    // dcache.scala:722-723.  A miss to another tag in the same set may have
    // selected the way that still contains this request's apparent hit.  The
    // line is already a victim even though its old tag/data have not yet been
    // overwritten, so consuming that stale hit would race the active MSHR.
    result.s2_nack_victim =
        s2_.valid && pipeline_hit && !s2_replay_ &&
        mshr_owns_hit_way_for_other_tag(s2_.address, lookup.way);
    result.s2_nack_writeback = result.s2_miss && s2_wb_idx_match_;
    if (result.s2_miss && !result.s2_nack_probe &&
        !result.s2_nack_writeback) {
      matching_mshr = find_matching_mshr(s2_.address);
      if (matching_mshr < 0)
        conflicting_mshr = find_matching_set_mshr(s2_.address);
      if (matching_mshr < 0 && conflicting_mshr < 0)
        idle_mshr = selected_idle_mshr();
      result.s2_secondary_miss = matching_mshr >= 0;
      // BoomMSHRFile keys primary allocation by cache index, not full line.
      // A different tag already occupying the set is neither a secondary
      // miss nor a legal primary miss; the request is nacked and retried.
      result.s2_nack_set_conflict = conflicting_mshr >= 0;
      // This describes the offered MSHR request.  Allocation readiness is a
      // separate question: RTL keeps req.valid high and nacks when all MSHRs
      // are occupied.
      result.s2_primary_miss =
          matching_mshr < 0 && conflicting_mshr < 0;
    }

    if (s2_.valid && s2_send_response_) {
      if (result.s2_nack_probe || result.s2_nack_victim) {
        reply(result.nack);
      } else if (pipeline_hit) {
        // cache_resp.bits.data is driven by LoadGen for every s2 response,
        // including stores.  The LSU ignores a store's data payload, but PTW
        // captures io.lsu.resp.bits.data with an unconditional RegNext, so
        // replacing this don't-care-looking value with zero is observable.
        reply(result.response, WithData ? load_from_cache(s2_, lookup.way) : 0);
      } else if (result.s2_nack_writeback) {
        reply(result.nack);
      } else if (matching_mshr >= 0) {
        if (sdq_ready &&
            mshr_accepts_secondary(mshrs_[matching_mshr]) &&
            !needs_second_acquire(s2_, mshrs_[matching_mshr].request) &&
            mshrs_[matching_mshr].rpq_count < kRpqDepth) {
          if (is_store(s2_)) reply(result.response);
        } else {
          reply(result.nack);
        }
      } else if (conflicting_mshr >= 0) {
        reply(result.nack);
      } else if (sdq_ready && idle_mshr >= 0) {
        if (is_store(s2_)) reply(result.response);
      } else {
        reply(result.nack);
      }
    }

    // dcache.scala:832-850 selects the cache-pipeline payload whenever its
    // Valid is asserted; otherwise it exposes the response-queue RAM even
    // when that queue is empty.  `response.data` is a functional completion
    // and is allowed to use zero for a store acknowledgement, so it cannot be
    // reused for this ungated wire.
    result.cache_response_valid = result.response.valid;
    if constexpr (WithData) result.lsu_response_data = result.cache_response_valid
                                   ? cache_response_data_oracle()
                                   : respq_data_[respq_deq_ & 3u];

    // MSHR load returns pass through the real four-entry response queue.  The
    // exercised single-port adapter can consume one response every cycle;
    // cache hits retain priority over this queued response.
    const bool respq_empty =
        respq_enq_ == respq_deq_ && !respq_maybe_full_;
    const std::size_t respq_head = respq_deq_ & 3u;
    const bool respq_head_killed =
        (respq_br_mask_[respq_head] & input.branch_kill_mask) != 0 ||
        (input.exception && respq_completion_[respq_head].uses_ldq);
    if (!result.response.valid && !respq_empty &&
        respq_valid_[respq_head] && !respq_head_killed) {
      if constexpr (WithData) result.response = respq_completion_[respq_head];
      else result.response.valid = true;
    }
  }

  PipelineOutputs pipeline_outputs(const SmallDcacheInputs& input) const {
    PipelineOutputs result;
    result.request_ready = request_pipeline_ready();
    pipeline_outputs_into<false>(input, result);
    return result;
  }

  void outputs_into(const SmallDcacheInputs& input, SmallDcacheOutputs& result) const {
    result = SmallDcacheOutputs{};
    result.s1_valid = s1_.valid;
    result.s2_valid = s2_.valid;
    result.s1_control_valid = s1_valid_shadow_;
    result.s2_control_valid = s2_valid_shadow_;
    result.s2_send_response = s2_send_response_;
    result.s2_control_send_response = s2_send_shadow_;
    result.request_ready = request_pipeline_ready();
    result.tile_d_ready = true;
    result.replacement_lfsr = replacement_lfsr_;
    result.replacement_way = s2_replacement_way_;
    result.writeback_state =
        static_cast<std::uint8_t>(writeback_.state);
    result.writeback_read_count = writeback_.read_count;
    result.writeback_release_beat = writeback_.release_beat;
    result.prober_state = static_cast<std::uint8_t>(prober_.state);
    result.tile_b_ready = prober_.state == ProberState::kIdle;
    const bool wb_lsu_release =
        writeback_.state == WritebackState::kLsuRelease;
    result.lsu_release_valid =
        wb_lsu_release || prober_.state == ProberState::kLsuRelease;
    result.lsu_release_address =
        wb_lsu_release ? writeback_.address : prober_.request.address;

    pipeline_outputs_into<true>(input, result);

    int acquire = -1;
    int grant_ack = -1;
    for (std::size_t index = 0; index < kMshrs; ++index) {
      result.mshr_state[index] =
          static_cast<std::uint8_t>(mshrs_[index].state);
      result.mshr_rpq_count[index] =
          static_cast<std::uint8_t>(mshrs_[index].rpq_count);
      if (acquire < 0 && mshrs_[index].state == MshrState::kAcquire)
        acquire = static_cast<int>(index);
      if (grant_ack < 0 && mshrs_[index].state == MshrState::kFinish1 &&
          mshrs_[index].grant_ack_valid)
        grant_ack = static_cast<int>(index);
    }
    if (acquire >= 0) {
      const Mshr& mshr = mshrs_[acquire];
      result.tile_a.valid = true;
      result.tile_a.opcode = 6;  // AcquireBlock
      result.tile_a.param =
          mshr.upgrade ? 2 : (is_store(mshr.request) ? 1 : 0);
      result.tile_a.size = 6;
      result.tile_a.source = static_cast<std::uint8_t>(acquire);
      result.tile_a.address =
          static_cast<std::uint32_t>(line_address(mshr.request.address));
      result.tile_a.mask = (UINT32_C(1) << boomcfg::TILE_BEAT_BYTES) - 1u;
      result.acquire_source = static_cast<std::uint8_t>(acquire);
    }
    if (grant_ack >= 0) {
      result.tile_e.valid = true;
      result.tile_e.sink = mshrs_[grant_ack].grant_sink;
    }

    if (writeback_.state == WritebackState::kActive) {
      result.tile_c.valid = true;
      result.tile_c.opcode = writeback_.probe ? 5 : 7;
      result.tile_c.param = writeback_.probe ? writeback_.probe_param : 1;
      result.tile_c.size = 6;
      // BoomWritebackUnit hard-wires every writeback packet's TL source to
      // cfg.nMSHRs (2), including manager-requested ProbeAckData.  Unlike the
      // Rocket implementation, it does not echo WritebackReq.source.
      result.tile_c.source = static_cast<std::uint8_t>(kMshrs);
      result.tile_c.address = writeback_.address;
      const std::size_t word =
          static_cast<std::size_t>(writeback_.release_beat) * kWordsPerBeat;
      result.tile_c.data = writeback_.line[word];
      if constexpr (kWordsPerBeat == 2)
        result.tile_c.data_hi = writeback_.line[word + 1u];
    } else if (prober_.state == ProberState::kRelease) {
      result.tile_c.valid = true;
      result.tile_c.opcode = 4;  // ProbeAck
      result.tile_c.param = probe_report_param();
      result.tile_c.size = prober_.request.size;
      result.tile_c.source = prober_.request.source;
      result.tile_c.address =
          static_cast<std::uint32_t>(line_address(prober_.request.address));
    }

    result.mshr_head = mshr_head_;
    result.mshr_alloc_index = mshr_alloc_index_;
    // io.lsu.ordered observes the shared cache s1/s2 valid registers, not
    // merely LSU-originated traffic.  A prober metadata read occupies s1 in
    // MetaResp and s2 in MshrReq even though it never produces an LSU reply.
    const bool prober_in_cache_pipeline =
        prober_.state == ProberState::kMetaResp ||
        prober_.state == ProberState::kMshrReq;
    const bool respq_empty = respq_enq_ == respq_deq_ && !respq_maybe_full_;
    result.ordered = !s1_.valid && !s2_.valid &&
                     !prober_in_cache_pipeline &&
                     !writeback_s1_valid_ && !writeback_s2_valid_ &&
                     respq_empty && all_mshrs_idle();
    return;
  }

  void step(const SmallDcacheInputs& input) {
    ++dc_steps_;
    update_arbiters(input);
    snap_dirty_ = snap_dirty_ || !all_mshrs_idle() ||
                  !(respq_enq_ == respq_deq_ && !respq_maybe_full_);

    // Exact four-entry BranchKillableQueue edge.  DCache cache responses have
    // priority over MSHR responses, so respq.io.deq.ready is low on a cache
    // hit even though the queue is non-empty.  An invalid head still advances
    // automatically.  Derive both decisions from the pre-edge image; valids
    // are not equivalent to a contiguous count after branch/flush kills.
    // cache_response_valid is the cache pipeline's own response; it does
    // not depend on the kill inputs, so any same-cycle evaluation serves.
    const bool cache_response_blocks_respq =
        eval_cache_gen_ == eval_gen_ ? eval_cache_.cache_response_valid
                                     : evaluate(input).cache_response_valid;
    const std::uint8_t respq_enq_before = respq_enq_;
    const bool respq_maybe_full_before = respq_maybe_full_;
    const bool respq_empty_before =
        respq_enq_ == respq_deq_ && !respq_maybe_full_;
    const bool respq_full_before =
        respq_enq_ == respq_deq_ && respq_maybe_full_;
    const bool respq_head_valid_before =
        respq_valid_[respq_deq_ & 3u];
    const bool respq_did_deq =
        (!cache_response_blocks_respq || !respq_head_valid_before) &&
        !respq_empty_before;

    for (std::size_t slot = 0; slot < respq_valid_.size(); ++slot) {
      const boomcfg::br_mask_t old_mask = respq_br_mask_[slot];
      if (respq_valid_[slot]) {
        const bool killed =
            (old_mask & input.branch_kill_mask) != 0 ||
            (input.exception && respq_completion_[slot].uses_ldq);
        respq_valid_[slot] = !killed;
        respq_br_mask_[slot] = static_cast<boomcfg::br_mask_t>(
            old_mask & ~input.branch_resolve_mask);
      }
    }

    // SDQ allocation and replay free are parallel combinational decisions in
    // BoomMSHRFile.  Allocation's PriorityEncoder observes the cycle-start
    // bitmap, so a slot freed by this cycle's replay cannot be reallocated on
    // the same edge.  Keep that allocation view separate from sdq_val_, which
    // replay processing may mutate before the new s2 miss is enqueued below.
    sdq_alloc_view_ = sdq_val_;
    std::array<std::size_t, kMshrs> rpq_head_before{};
    std::array<std::size_t, kMshrs> rpq_tail_before{};
    std::array<std::size_t, kMshrs> rpq_count_before{};
    std::array<std::uint32_t, kMshrs> rpq_valid_before{};
    std::array<bool, kMshrs> rpq_maybe_full_before{};
    for (std::size_t i = 0; i < kMshrs; ++i) {
      rpq_head_before[i] = mshrs_[i].rpq_head;
      rpq_tail_before[i] = mshrs_[i].rpq_tail;
      rpq_count_before[i] = mshrs_[i].rpq_count;
      rpq_maybe_full_before[i] = mshrs_[i].rpq_maybe_full;
      for (std::size_t n = 0; n < mshrs_[i].rpq_count; ++n) {
        const auto slot = (mshrs_[i].rpq_head + n) % kRpqDepth;
        if (mshrs_[i].rpq[slot].valid)
          rpq_valid_before[i] |= UINT32_C(1) << slot;
      }
    }

    respq_head_prev_ = respq_data_[respq_deq_ & 3u];
    if (respq_did_deq) {
      respq_valid_[respq_deq_ & 3u] = false;
      respq_deq_ = (respq_deq_ + 1u) & 3u;
      --respq_count_;
    }

    // Raw stage shadows (oracle export only): the RTL s1/s2 registers latch
    // the s0 arbitration winner every cycle — LSU request, MSHR replay,
    // writeback read or probe — with no enable.  raw_s0_ defaults to the
    // LSU request and the internal issue sites overwrite it below; the s1
    // latch happens at the end of the step.
    // Array-port views from the held addresses; the shadow arrays apply
    // every write two steps late, matching the RTL write stage.
    ow_apply_old();
    // Selected cache-array and request-pipeline oracles remain live in the
    // relaxed payload mode. Their consumers can use them on a valid miss.
    ow_meta_apply_d1();
    // rpq deq port (sync-read, read-ahead): while entries are pending the
    // port re-reads the head each cycle -- captured BEFORE this step's
    // enqueues land; a pop re-captures the NEXT head at the pop site.
    for (Mshr& mshr : mshrs_)
      if (mshr.rpq_count != 0) {
        mshr.rpq_port_slot = static_cast<std::uint8_t>(mshr.rpq_head);
        mshr.rpq_port_req = mshr.rpq[mshr.rpq_head].request;
        mshr.rpq_port_sdq = mshr.rpq_sdq_id[mshr.rpq_head];
      }
    for (Mshr& mshr : mshrs_) mshr.rpq_auto_popped = false;

    // Evaluate the replay arbiter from the cycle-start RPQ image and this
    // cycle's kill/exception inputs before committing any queue pop.  This is
    // a POST combinational projection, not a value that can be reconstructed
    // from either the previous or the already-mutated MSHR state.  Arbiter
    // payloads fall through to input 1 whenever input 0 is not *valid*;
    // state==Replay alone is insufficient when the RPQ head is killed.
    std::size_t replay_source_for_oracle = kLastMshr;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      if (mshrs_[i].state == MshrState::kReplay &&
          rpq_head_deq_valid(mshrs_[i], input)) {
        replay_source_for_oracle = i;
        break;
      }
    }
    const bool m0_replay_valid_for_oracle =
        mshrs_[0].state == MshrState::kReplay &&
        rpq_head_deq_valid(mshrs_[0], input);
    const Mshr& replay_src = mshrs_[replay_source_for_oracle];
    replay_arb_m0_valid_oracle_ = m0_replay_valid_for_oracle;
    replay_arb_source_oracle_ =
        static_cast<std::uint8_t>(replay_source_for_oracle);
    sdq_port_address_oracle_ = replay_src.rpq_port_sdq;
    sdq_port_cycle_oracle_ =
        sdq_port_address_oracle_ < sdq_data_.size()
            ? sdq_data_[sdq_port_address_oracle_]
            : 0;

    // The s0 request bus uses the same replay-arbiter fall-through payload.
    fallthrough_bus_ = replay_src.rpq_port_req;
    fallthrough_bus_.address = line_address(replay_src.request.address) |
                               (fallthrough_bus_.address & 0x3fu);
    fallthrough_bus_.data = sdq_port_cycle_oracle_;
    {
      static long lo = -1, hi = -1;
      static bool init = [] {
        if (const char* w = std::getenv("SYSDC_BUS_DEBUG")) {
          long a, b;
          if (std::sscanf(w, "%ld-%ld", &a, &b) == 2) { lo = a; hi = b; }
        }
        return true;
      }();
      (void)init;
      if (lo >= 0 && static_cast<long>(dc_steps_) >= lo &&
          static_cast<long>(dc_steps_) <= hi)
        std::fprintf(stderr,
                     "[DCBUS] n=%llu m0=%d src=%u st=%d cnt=%zu head=%zu tail=%zu "
                     "slot=%u sdqid=%u sdq=%llx port=%llx valid=%d reqaddr=%llx "
                     "ft=%llx m0st=%d m0cnt=%zu m0addr=%llx\n",
                     static_cast<unsigned long long>(dc_steps_),
                     static_cast<int>(m0_replay_valid_for_oracle),
                     static_cast<unsigned>(replay_arb_source_oracle_),
                     static_cast<int>(replay_src.state), replay_src.rpq_count,
                     replay_src.rpq_head, replay_src.rpq_tail,
                     static_cast<unsigned>(replay_src.rpq_port_slot),
                     static_cast<unsigned>(sdq_port_address_oracle_),
                     static_cast<unsigned long long>(sdq_port_cycle_oracle_),
                     static_cast<unsigned long long>(replay_src.rpq_port_req.address),
                     static_cast<int>(replay_src.rpq[replay_src.rpq_head].valid),
                     static_cast<unsigned long long>(replay_src.request.address),
                     static_cast<unsigned long long>(fallthrough_bus_.address),
                     static_cast<int>(mshrs_[0].state), mshrs_[0].rpq_count,
                     static_cast<unsigned long long>(mshrs_[0].request.address));
    }
    // BranchKillableQueue: do_deq = (deq.ready || !valids(deq_ptr)) && !empty.
    // A head killed on an earlier edge leaves on its own this cycle, and
    // the MSHR cannot consume anything else from that queue meanwhile.
    for (Mshr& mshr : mshrs_) {
      if (mshr.rpq_count != 0 && !mshr.rpq[mshr.rpq_head].valid) {
        mshr.rpq_head = (mshr.rpq_head + 1) % kRpqDepth;
        mshr.rpq_port_slot = static_cast<std::uint8_t>(mshr.rpq_head);
        mshr.rpq_port_req = mshr.rpq[mshr.rpq_head].request;
        mshr.rpq_port_sdq = mshr.rpq_sdq_id[mshr.rpq_head];
        mshr.rpq_maybe_full = false;
        --mshr.rpq_count;
        mshr.rpq_auto_popped = true;
      }
    }
    {
      static const bool dbg = getenv("SYSDC2_DEBUG") != nullptr;
      
      ++g_dc_step_n;
      const unsigned long long n = g_dc_step_n;
      if (dbg && n >= 1498 && n <= 1515)
        fprintf(stderr, "[DC2] n=%llu raw=%d ldq=%d stq=%d addr=%llx req=%d mset=%zu\n",
                n, (int)input.raw_request.valid, (int)input.raw_request.uses_ldq,
                (int)input.raw_request.uses_stq,
                (unsigned long long)input.raw_request.address,
                (int)input.request.valid, oracle_meta_set_[3]);
    }
    // dcache.scala:869-903: the store-data pipeline consumes the current s2
    // request/data view while this edge advances s1 into s2.  Preserve that
    // pre-edge view before updating the s2 shadows below.
    // s2_req is the unconditional RegNext of the s0 request-bus payload.
    // Even with no valid winner that bus exposes the replay arbiter's stale
    // input-1 bits, which bus_s2_ mirrors; raw_s2_ intentionally represents
    // only a functional request and therefore loses those idle-cycle bits.
    {
    const BoomUncachedRequest s2_req_now = bus_s2_;
    const std::uint8_t s2_type_now = oracle_s2_type_;
    const std::uint8_t s2_way_now = s2_tag_match_way_;
    std::array<std::uint64_t, kWordsPerBeat> s2_array_beat{};
    for (std::size_t way = 0; way < kWays; ++way)
      if ((s2_way_now >> way) & 1u)
        for (std::size_t lane = 0; lane < kWordsPerBeat; ++lane)
          s2_array_beat[lane] |= oracle_array_port_reg_[way][lane];
    const std::uint64_t s2_array_word =
        s2_array_beat[(s2_req_now.address >> 3) &
                      (kWordsPerBeat - 1u)];
    // BoomWritebackUnit does not snapshot the victim line when it accepts a
    // request.  Each cache-array read returns through the ordinary s1/s2
    // pipeline and only then updates one persistent wb_buffer register.  The
    // current s2 way/data view is exactly io.data_resp for the request whose
    // beat index travelled beside writeback_s{1,2}_valid_.
    if (writeback_s2_valid_ &&
        writeback_.state == WritebackState::kFillBuffer) {
      const std::size_t first_word =
          static_cast<std::size_t>(writeback_s2_beat_) * kWordsPerBeat;
      for (std::size_t lane = 0; lane < kWordsPerBeat; ++lane) {
        if constexpr (boom_model::kArchitecturalModel)
          writeback_.line[first_word + lane] = architectural_wb_s2_[lane];
        else
          writeback_.line[first_word + lane] = s2_array_beat[lane];
      }
    }
    std::uint64_t s2_data_word = s2_array_word;
    if (s5_valid_ && same_word(s2_req_now.address, s5_req_addr_))
      s2_data_word = s5_req_data_;
    if (s4_valid_ && same_word(s2_req_now.address, s4_req_addr_))
      s2_data_word = s4_req_data_;
    if (s3_valid_ && same_word(s2_req_now.address, s3_req_addr_))
      s2_data_word = s3_req_data_;

    const std::uint64_t next_s3_data =
        amoalu(s2_req_now.address, s2_req_now.size,
               s2_req_now.command, s2_data_word, s2_req_now.data);
    bool s2_write_hit = s2_type_now == 0 || s2_type_now == 2;
    if (s2_type_now == 4 && s2_way_now != 0) {
      std::uint8_t hit_coh = 0;
      for (std::size_t way = 0; way < kWays; ++way)
        if ((s2_way_now >> way) & 1u) hit_coh |= oracle_coh_reg_[way];
      // All writes reach s3 only once the line is Dirty.  A same-line MSHR
      // blocks an otherwise matching hit until its replay completes.
      s2_write_hit = hit_coh == 3 && find_matching_mshr(s2_req_now.address) < 0;
    }
    // dcache.scala:871 additionally gates the s3 store-bypass install on the
    // store not being nacked back to the LSU (!(s2_send_nack && s2_nack)).
    // A nacked store never reaches s3 in the RTL, so it must not
    // shadow-forward into a same-word load's raw response word here: the
    // store replays later, the functional path re-converges, and only PTW's
    // ungated RegNext of the response wire sees the difference (first
    // exposed by DMI-throttled poll interleaving at dhrystone c878795).
    // For a write hit the only reachable nacks are the probe-set conflict
    // and the victim-way race; both mirror the functional expressions in
    // outputs() (s2_nack_probe / s2_nack_victim), which evaluate from the
    // same cycle-start state.
    int s2_hit_way_index = -1;
    for (std::size_t way = 0; way < kWays; ++way)
      if ((s2_way_now >> way) & 1u)
        s2_hit_way_index = static_cast<int>(way);
    const bool s2_nack_probe_now =
        s2_.valid && s2_nack_hit_ && !s2_replay_;
    const bool s2_nack_victim_now =
        s2_.valid && !s2_replay_ && s2_hit_way_index >= 0 &&
        mshr_owns_hit_way_for_other_tag(
            s2_req_now.address,
            static_cast<std::uint8_t>(s2_hit_way_index));
    const bool next_s3_valid =
        s2_valid_shadow_ && s2_write_hit &&
        is_write_command(s2_req_now.command) &&
        !s2_nack_probe_now && !s2_nack_victim_now;

    s5_valid_ = s4_valid_;
    s5_req_addr_ = s4_req_addr_;
    s5_req_data_ = s4_req_data_;
    s4_valid_ = s3_valid_;
    s4_req_addr_ = s3_req_addr_;
    s4_req_data_ = s3_req_data_;
    s3_valid_ = next_s3_valid;
    s3_req_addr_ = s2_req_now.address;
    s3_req_data_ = next_s3_data;

    oracle_s2_type_ = oracle_s1_type_;

    // dcache.scala:616-627/642: s2_tag_match_way is a RegNext of a mux
    // selected by the *registered* s1_type.  The three special inputs are
    // themselves unconditional payload registers, so their stale one-hot
    // way remains visible even when the corresponding request is invalid.
    // For an ordinary LSU/probe lookup, compare the current metadata SRAM
    // response against the registered s1 request address.
    std::uint8_t ordinary_tag_match = 0;
    const std::uint32_t s1_tag =
        static_cast<std::uint32_t>((raw_s1_.address >> 12) & 0x0fffffffu);
    for (std::size_t way = 0; way < kWays; ++way)
      if (oracle_coh_now_[way] != 0 &&
          (oracle_tag_now_[way] & 0x000fffffu) == s1_tag)
        ordinary_tag_match |= static_cast<std::uint8_t>(1u << way);
    switch (oracle_s2_type_) {
      case 0: s2_tag_match_way_ = s1_replay_way_en_; break;
      case 2: s2_tag_match_way_ = s1_wb_way_en_; break;
      case 3: s2_tag_match_way_ = s1_mshr_meta_read_way_en_; break;
      default: s2_tag_match_way_ = ordinary_tag_match; break;
    }

    // The arbiters fall through to MSHR 1 when MSHR 0 is not offering a
    // valid request.  Capture their combinational payloads for the next edge,
    // exactly as the three RTL s1_*_way_en registers do.  The writeback unit
    // has a single held request payload.
    std::size_t replay_payload_index = kLastMshr;
    std::size_t meta_read_payload_index = kLastMshr;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      if (replay_payload_index == kLastMshr &&
          mshrs_[i].state == MshrState::kReplay &&
          rpq_head_deq_valid(mshrs_[i], input))
        replay_payload_index = i;
      if (meta_read_payload_index == kLastMshr &&
          mshrs_[i].state == MshrState::kMetaRead)
        meta_read_payload_index = i;
    }
    s1_replay_way_en_ = mshrs_[replay_payload_index].way_en;
    s1_mshr_meta_read_way_en_ = mshrs_[meta_read_payload_index].way_en;
    s1_wb_way_en_ = writeback_.way_en;

    if (raw_s1_way_override_ >= 0) {
      raw_s2_lookup_ = Lookup{};
      raw_s2_lookup_.hit = true;
      raw_s2_lookup_.way = static_cast<std::uint8_t>(raw_s1_way_override_);
    } else {
      raw_s2_lookup_ = lookup_line(raw_s1_.address);
    }
    raw_s2_ = raw_s1_;
    raw_s2_.br_mask &=
        static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
    }
    raw_s0_ = input.raw_request;
    // Metadata and data use independent RTL arbiters.  An MSHR metadata read
    // can win metaReadArb while an unaccepted LSU request simultaneously wins
    // dataReadArb and retargets every data SRAM port.  Keep a separate data
    // winner so metadata-only passes cannot erase that LSU read.
    raw_data_s0_ = input.raw_request;
    raw_s0_way_override_ = -1;
    raw_s0_type_ = 4;  // t_lsu; internal issue sites override
    // Every LSU request fire reads the data arrays with way_en=~0
    // (dcache.scala:488-490) -- stores and loads alike.
    raw_s0_read_ways_ = input.raw_request.valid ? kAllWaysMask : 0u;
    if (input.reset) {
      reset();
      ++eval_gen_;
      snap_dirty_ = true;
      return;
    }

    if (metadata_reset_cycles_ != 0) --metadata_reset_cycles_;
    // Tag/coherence SRAM data is captured when the request enters s0.  A tag
    // write on a later edge must not retroactively turn an already-pipelined
    // request into a hit.
    const Lookup next_s1_lookup =
        input.request.valid ? lookup_line(input.request.address) : Lookup{};
    const PipelineOutputs current_output = pipeline_outputs(input);
    if (small_dcache_store_debug_enabled() &&
        ((input.request.valid &&
          line_address(input.request.address) == UINT64_C(0x80029040)) ||
         (s1_.valid &&
          line_address(s1_.address) == UINT64_C(0x80029040)) ||
         (s2_.valid &&
          line_address(s2_.address) == UINT64_C(0x80029040)) ||
         (mshrs_[0].state != MshrState::kIdle &&
          line_address(mshrs_[0].request.address) == UINT64_C(0x80029040)) ||
         (mshrs_[1].state != MshrState::kIdle &&
          line_address(mshrs_[1].request.address) == UINT64_C(0x80029040)))) {
      std::fprintf(
          stderr,
          "[DCPIPE] n=%llu in=%d/%llx/%llx kill=%d "
          "s1=%d/%llx/%llx/r%d s2=%d/%llx/%llx/r%d "
          "hit=%d miss=%d nack=%d wbmatch=%d lookup=%d/w%u/d%d "
          "m0=%u/%u/%llx m1=%u/%u/%llx\n",
          static_cast<unsigned long long>(g_dc_step_n),
          static_cast<int>(input.request.valid),
          static_cast<unsigned long long>(input.request.address),
          static_cast<unsigned long long>(input.request.data),
          static_cast<int>(input.s1_kill), static_cast<int>(s1_.valid),
          static_cast<unsigned long long>(s1_.address),
          static_cast<unsigned long long>(s1_.data),
          static_cast<int>(s1_replay_), static_cast<int>(s2_.valid),
          static_cast<unsigned long long>(s2_.address),
          static_cast<unsigned long long>(s2_.data),
          static_cast<int>(s2_replay_), static_cast<int>(current_output.s2_hit),
          static_cast<int>(current_output.s2_miss),
          static_cast<int>(current_output.nack.valid),
          static_cast<int>(s2_wb_idx_match_),
          static_cast<int>(s2_lookup_.hit),
          static_cast<unsigned>(s2_lookup_.way),
          static_cast<int>(s2_lookup_.dirty),
          static_cast<unsigned>(mshrs_[0].state),
          static_cast<unsigned>(mshrs_[0].rpq_count),
          static_cast<unsigned long long>(mshrs_[0].request.address),
          static_cast<unsigned>(mshrs_[1].state),
          static_cast<unsigned>(mshrs_[1].rpq_count),
          static_cast<unsigned long long>(mshrs_[1].request.address));
    }
    const bool s2_store_failed =
        s2_.valid && is_store(s2_) && current_output.nack.valid;
    // RTL registers the s1 comparison against the writeback unit's
    // cycle-start victim index.  Keep it separate from the current WB state:
    // the hazard survives the edge on which writeback itself changes state.
    const bool next_s2_wb_idx_match =
        writeback_.state != WritebackState::kIdle &&
        set_index(bus_s1_.address) == set_index(writeback_.address);
    // dcache.scala:612/721.  A probe owns its set from acceptance until the
    // ProbeUnit returns to Idle.  The set comparison is made in s1 and then
    // registered, so even a cache hit in s2 is nacked one cycle later.
    // `bus_s1_` is the exact unconditional RTL s1_req payload; unlike the
    // functional s1_ it also preserves bits while invalid.
    const bool next_s2_nack_hit =
        prober_.state != ProberState::kIdle &&
        set_index(bus_s1_.address) == set_index(prober_.request.address);
    // Before the first edge the RTL LFSR still holds the zero image, so
    // RegNext(replacer.way) reads 0 at cycle 1 regardless of the reset value.
    const std::uint8_t replacement_way_before =
        static_cast<std::uint8_t>(replacement_lfsr_ & (kWays - 1u));
    const int next_idle_mshr = select_idle_mshr();
    // With no ready candidate, Chisel's PriorityEncoder selects the final
    // padded candidate; truncating it to log2Ceil(kMshrs) leaves kMshrs-1.
    const std::uint8_t next_mshr_alloc_index =
        static_cast<std::uint8_t>(next_idle_mshr >= 0
                                      ? next_idle_mshr
                                      : kLastMshr);

    // Advance independent refill/replay state before allocating this cycle's
    // s2 miss.  This matches the registered state view used to form ready.
    const bool writeback_response =
        writeback_.state == WritebackState::kFillBuffer &&
        writeback_.read_count == kTransferBeats &&
        writeback_.response_tail == 1;
    bool writeback_available =
        writeback_.state == WritebackState::kIdle;
    bool replay_owns_cache_read_ports = false;
    int replay_data_owner = -1;
    bool mshr_metadata_write_requested = false;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      const Mshr& mshr = mshrs_[i];
      const bool replay_valid =
          mshr.state == MshrState::kReplay && rpq_head_deq_valid(mshr, input);
      replay_owns_cache_read_ports |= replay_valid;
      if (replay_valid && replay_data_owner < 0)
        replay_data_owner = static_cast<int>(i);
      mshr_metadata_write_requested |=
          mshr.state == MshrState::kMetaClear ||
          mshr.state == MshrState::kMetaWrite;
    }
    const bool prober_meta_read_requested =
        prober_.state == ProberState::kMetaRead;
    const bool prober_meta_write_requested =
        prober_.state == ProberState::kMetaWrite;
    const bool metadata_write_blocks_reads =
        mshr_metadata_write_requested || prober_meta_write_requested;
    // Cache read arbitration is replay, prober, writeback, MSHR metadata,
    // then the LSU pipeline.
    const bool writeback_read_ports_available =
        !replay_owns_cache_read_ports && !prober_meta_read_requested &&
        !metadata_write_blocks_reads;
    const bool writeback_owns_cache_read_ports =
        writeback_.state == WritebackState::kFillBuffer &&
        writeback_.read_count < kTransferBeats;
    const bool writeback_s0_fire =
        writeback_owns_cache_read_ports &&
        writeback_read_ports_available;
    const std::uint8_t writeback_s0_beat = writeback_.read_count;
    const bool wb_lsu_release_owns =
        writeback_.state == WritebackState::kLsuRelease;
    const bool wb_c_owns =
        writeback_.state == WritebackState::kActive;
    // replay.valid is sufficient to win dataReadArb input 0 even when the
    // independent metadata arbiter prevents the coupled replay fire.  Keep
    // driving the held head/way while the state machine itself stalls.
    if (replay_data_owner >= 0) {
      const Mshr& owner = mshrs_[static_cast<std::size_t>(replay_data_owner)];
      raw_data_s0_ = owner.rpq[owner.rpq_head].request;
      raw_data_s0_.valid = true;
      raw_data_s0_.address =
          line_address(owner.request.address) |
          (raw_data_s0_.address & 0x3fu);
      raw_s0_read_ways_ = std::uint8_t(1u << owner.way);
    }
    // Writeback's metadata and data handshakes are coupled for advancing its
    // beat counter, but the two arbiters are independent.  While a metadata
    // write blocks the coupled fire, wb.io.data_req.valid still wins the data
    // arbiter and repeatedly drives the current beat instead of allowing a
    // stalled LSU request to retarget all ways.
    const bool writeback_drives_data_port =
        writeback_owns_cache_read_ports && !replay_owns_cache_read_ports;
    if (writeback_drives_data_port) {
      raw_data_s0_ = BoomUncachedRequest{};
      raw_data_s0_.valid = true;
      raw_data_s0_.address =
          writeback_.address +
          boomcfg::TILE_BEAT_BYTES *
              static_cast<std::uint32_t>(writeback_.read_count);
      raw_s0_read_ways_ = std::uint8_t(1u << writeback_.way);
    }
    step_writeback(input, writeback_read_ports_available);
    BoomUncachedCompletion produced_miss_response{};
    // The refill line buffer is a single-ported Mem.  Incoming GrantData
    // writes win over every read; otherwise the fixed-priority read arbiter
    // gives the first MSHR that needs a read the port for this cycle.
    bool line_buffer_read_available =
        !(input.tile_d.valid && input.tile_d.opcode == 5 &&
          input.tile_d.source < kMshrs);
    bool cache_replay_available = !metadata_write_blocks_reads;
    bool mshr_meta_read_available =
        !metadata_write_blocks_reads && !replay_owns_cache_read_ports &&
        !prober_meta_read_requested && !writeback_owns_cache_read_ports;
    const bool prober_meta_read_available =
        !metadata_write_blocks_reads && !replay_owns_cache_read_ports;
    const bool prober_meta_read_fire =
        prober_meta_read_requested && prober_meta_read_available;
    const bool prober_meta_write_available =
        !mshr_metadata_write_requested;
    bool replay_store_issued = false;
    bool refill_write_available = !replay_store_write_pipe_[2];
    step_prober(input, prober_meta_read_available,
                prober_meta_write_available, wb_lsu_release_owns,
                wb_c_owns, writeback_available);
    if (prober_meta_read_fire) {
      raw_s0_ = BoomUncachedRequest{};
      raw_s0_.valid = true;
      // dcache.scala:555 prober_req.addr = Cat(tag, idx) << blockOffBits.
      raw_s0_.address = line_address(prober_.request.address);
      raw_s0_type_ = 1;  // t_probe
    }
    // Snapshot MSHR state registers before stepping them: the s2 miss
    // allocation below is combinational off these registers in RTL, so an
    // MSHR retiring to idle THIS cycle still owns its line/set for the
    // allocation decision (freed only at the next edge).
    std::array<MshrState, kMshrs> mshr_state_pre_step;
    for (std::size_t i = 0; i < kMshrs; ++i)
      mshr_state_pre_step[i] = mshrs_[i].state;
    for (std::size_t index = 0; index < kMshrs; ++index)
      step_mshr(index, input, produced_miss_response,
                writeback_response, writeback_available,
                line_buffer_read_available, !respq_full_before, cache_replay_available,
                mshr_meta_read_available, replay_store_issued,
                refill_write_available);
    const bool respq_did_enq = respq_enq_ != respq_enq_before;
    if (respq_did_enq != respq_did_deq)
      respq_maybe_full_ = respq_did_enq;
    else
      respq_maybe_full_ = respq_maybe_full_before;

    // A normal hit is already in s2 and reaches the store-write stage next
    // cycle.  An MSHR replay issued above is entering s0 and reaches that same
    // stage three cycles later.  The pipeline occupancy, not the early model
    // data update, owns priority over an MSHR refill write.
    const bool external_store_enters_s3 =
        s2_.valid && !s2_replay_ && is_store(s2_) &&
        current_output.s2_hit && !current_output.s2_nack_probe &&
        !current_output.s2_nack_victim;
    replay_store_write_pipe_[2] =
        replay_store_write_pipe_[1] || external_store_enters_s3;
    replay_store_write_pipe_[1] = replay_store_write_pipe_[0];
    replay_store_write_pipe_[0] = replay_store_issued;

    // dcache.scala:729/747: the writeback-index hazard only nacks a MISS
    // (s2_nack_wb requires !s2_hit).  A store that hits a set whose other
    // way is being written back still writes the data array at s3, so the
    // hazard must not gate the hit path; it only blocks MSHR allocation.
    if (s2_.valid && !s2_replay_ && !s2_nack_hit_ &&
        !current_output.s2_nack_victim) {
      const Lookup lookup = s2_lookup_;
      if (current_output.s2_hit) {
        if (is_store(s2_)) {
          store_to_cache(s2_, lookup.way);
          meta_[set_index(s2_.address)].dirty[lookup.way] = true;
          // A store hit requires the line already Dirty; RTL writes no
          // metadata for it (state unchanged), so no shadow write either.
        }
      } else if (!s2_wb_idx_match_) {
        const int matching =
            find_matching_mshr(s2_.address, mshr_state_pre_step);
        if (matching >= 0) {
          if (sdq_has_free_slot(sdq_alloc_view_) &&
              mshr_accepts_secondary(mshr_state_pre_step[matching]) &&
              !needs_second_acquire(s2_, mshrs_[matching].request) &&
              mshrs_[matching].rpq_count < kRpqDepth) {
            // req_sec_val && req_sec_rdy: req.uop.mem_cmd := dirtier_cmd and,
            // when the held permission already covers it, new_coh :=
            // dirtier_coh (mshrs.scala:121-122, 171-176).
            if (is_store(s2_) && !is_store(mshrs_[matching].request)) {
              mshrs_[matching].request.uses_stq = true;
              mshrs_[matching].request.command = s2_.command;
              if (mshrs_[matching].new_coh >= 2) mshrs_[matching].new_coh = 3;
            }
            enqueue_rpq(mshrs_[matching], s2_);
            advance_replacement();
          }
        } else {
          // pri_val in BoomMSHRFile is gated by !idx_match: two MSHRs may
          // never own different tags in the same set concurrently.
          if (find_matching_set_mshr(s2_.address, mshr_state_pre_step) < 0) {
            const int idle = selected_idle_mshr();
            if (sdq_has_free_slot(sdq_alloc_view_) && idle >= 0) {
              allocate_mshr(static_cast<std::size_t>(idle), s2_, lookup);
              advance_replacement();
            }
          }
        }
      }
    }

    if (input.external_miss_fire) advance_replacement();

    // mshrs.scala s_drain_rpq retires only when the RPQ was empty at the
    // start of the cycle AND no secondary request is enqueued this cycle:
    //
    //   when (rpq.io.empty && !rpq.io.enq.valid) { state := s_meta_write_req }
    //
    // The s2 miss arbitration above runs after step_mshr() in this model, so
    // finalizing the empty-RPQ transition inside step_mshr() would miss a
    // same-edge enqueue.  Use the cycle-start queue image here; this also
    // keeps Replay for one edge when BranchKillableQueue auto-pops a killed
    // final head during the cycle.
    for (std::size_t i = 0; i < kMshrs; ++i) {
      const bool did_enq = mshrs_[i].rpq_tail != rpq_tail_before[i];
      if (mshr_state_pre_step[i] == MshrState::kReplay &&
          rpq_count_before[i] == 0 && !did_enq) {
        Mshr& mshr = mshrs_[i];
        mshr.state = MshrState::kMetaWrite;
        // The RTL's final meta write fires one edge after the drain ends.
        // A refill's final write blanks the port on its write cycle; the
        // silent metadata-only upgrade shows the old word through it.
        const std::size_t est = set_index(mshr.request.address);
        ow_meta_d1(mshr.way, est, address_tag(mshr.request.address),
                   mshr.new_coh != 0, mshr.new_coh == 3,
                   mshr.new_coh >= 2, 0, !mshr.metadata_only);
      }
    }

    // BranchKillableQueue updates maybe_full only when enqueue and dequeue
    // differ.  The state-machine code above performs pops before the new s2
    // miss is enqueued, so repair that sequential C++ ordering into the RTL's
    // single-edge XOR rule here.
    for (std::size_t i = 0; i < kMshrs; ++i) {
      const bool did_enq = mshrs_[i].rpq_tail != rpq_tail_before[i];
      const bool did_deq = mshrs_[i].rpq_head != rpq_head_before[i];
      mshrs_[i].rpq_maybe_full =
          did_enq != did_deq ? did_enq : rpq_maybe_full_before[i];
    }

    // dcache.scala:604-607 / 634-637: a branch mispredict or an exception
    // (loads only) kills the LSU request in s0 and s1.
    const bool squash_s1 =
        input.s1_kill ||
        (s2_store_failed && !s1_replay_ && is_store(s1_)) ||
        (!s1_replay_ && ((s1_.br_mask & input.branch_kill_mask) != 0 ||
                         (input.exception && s1_.uses_ldq)));
    const bool squash_s0 =
        (s2_store_failed && is_store(input.request)) ||
        (input.request.br_mask & input.branch_kill_mask) != 0 ||
        (input.exception && input.request.uses_ldq);
    const bool replay_s0 = raw_s0_.valid && raw_s0_type_ == 0;
    BoomUncachedRequest functional_s0 =
        replay_s0 ? raw_s0_ : input.request;
    Lookup functional_s0_lookup = next_s1_lookup;
    if (replay_s0) {
      functional_s0_lookup = Lookup{};
      functional_s0_lookup.hit = true;
      functional_s0_lookup.dirty = true;
      functional_s0_lookup.writable = true;
      for (std::uint8_t way = 0; way < kWays; ++way)
        if ((raw_s0_read_ways_ >> way) & 1u) {
          functional_s0_lookup.way = way;
          break;
        }
    }
    // Compact transaction-level pipeline trace.  Unlike the older
    // address-specific store debug, this shows both the functional request
    // objects and the literal RTL control shadows, plus every condition that
    // can discard an LSU request between s0 and s2.  The range is expressed
    // in D-cache step numbers, which match SystemGuider cycles after reset:
    //   SYSDC_PIPE_DEBUG=27918-27934 ./system-model-lockstep ...
    {
      static long lo = -1, hi = -1;
      static bool init = [] {
        if (const char* range = std::getenv("SYSDC_PIPE_DEBUG")) {
          long first = -1, last = -1;
          if (std::sscanf(range, "%ld-%ld", &first, &last) == 2) {
            lo = first;
            hi = last;
          }
        }
        return true;
      }();
      (void)init;
      if (lo >= 0 && static_cast<long>(dc_steps_) >= lo &&
          static_cast<long>(dc_steps_) <= hi) {
        std::fprintf(
            stderr,
            "[DCPIPE n=%llu] raw=%d/fire%d/h%d/%llx "
            "s0=%d/h%d/%llx replay%d squash%d lookup%d/w%u "
            "s1=%d/h%d/%llx replay%d send%d ctl%d/%d squash%d "
            "s2=%d/h%d/%llx replay%d send%d ctl%d/%d "
            "hit%d resp%d nack%d kill%d exc%d br=%02x/%02x ready%d\n",
            static_cast<unsigned long long>(dc_steps_),
            static_cast<int>(input.raw_request.valid),
            static_cast<int>(input.raw_request_fire),
            static_cast<int>(input.raw_request.is_hella),
            static_cast<unsigned long long>(input.raw_request.address),
            static_cast<int>(functional_s0.valid),
            static_cast<int>(functional_s0.is_hella),
            static_cast<unsigned long long>(functional_s0.address),
            static_cast<int>(replay_s0), static_cast<int>(squash_s0),
            static_cast<int>(functional_s0_lookup.hit),
            static_cast<unsigned>(functional_s0_lookup.way),
            static_cast<int>(s1_.valid), static_cast<int>(s1_.is_hella),
            static_cast<unsigned long long>(s1_.address),
            static_cast<int>(s1_replay_), static_cast<int>(s1_send_response_),
            static_cast<int>(s1_valid_shadow_),
            static_cast<int>(s1_send_shadow_), static_cast<int>(squash_s1),
            static_cast<int>(s2_.valid), static_cast<int>(s2_.is_hella),
            static_cast<unsigned long long>(s2_.address),
            static_cast<int>(s2_replay_), static_cast<int>(s2_send_response_),
            static_cast<int>(s2_valid_shadow_),
            static_cast<int>(s2_send_shadow_),
            static_cast<int>(current_output.s2_hit),
            static_cast<int>(current_output.response.valid),
            static_cast<int>(current_output.nack.valid),
            static_cast<int>(input.s1_kill),
            static_cast<int>(input.exception),
            static_cast<unsigned>(input.branch_resolve_mask),
            static_cast<unsigned>(input.branch_kill_mask),
            static_cast<int>(current_output.request_ready));
      }
    }
    s2_wb_idx_match_ = next_s2_wb_idx_match;
    s2_nack_hit_ = next_s2_nack_hit;
    // dcache.scala:633 s2_valid(0): s1_valid killed by s1_kill, or by a
    // failed store while an LSU store sits in s1; 732 RegNext(s1_send).
    s2_valid_shadow_ = s1_valid_shadow_ && !input.s1_kill &&
                       !(s2_store_failed && oracle_s1_type_ == 4 &&
                         raw_s1_.uses_stq) &&
                       (raw_s1_.br_mask & input.branch_kill_mask) == 0 &&
                       !(input.exception && raw_s1_.uses_ldq);
    s2_send_shadow_ = s1_send_shadow_;
    s2_ = squash_s1 ? BoomUncachedRequest{} : s1_;
    s2_.br_mask &=
        static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
    s2_lookup_ = squash_s1 ? Lookup{} : s1_lookup_;
    s2_replay_ = squash_s1 ? false : s1_replay_;
    s2_send_response_ = squash_s1 ? false : s1_send_response_;
    s1_ = (!replay_s0 && squash_s0) ? BoomUncachedRequest{}
                                      : functional_s0;
    s1_.br_mask &=
        static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
    s1_lookup_ = (!replay_s0 && squash_s0) ? Lookup{}
                                            : functional_s0_lookup;
    s1_replay_ = replay_s0;
    // Ordinary LSU requests always ask the cache pipeline for a response or
    // nack.  Replayed stores already received their acknowledgement when the
    // MSHR accepted them; only replayed reads respond a second time.
    s1_send_response_ = replay_s0 ? is_read_command(functional_s0.command)
                                  : input.request.valid;
    s2_replacement_way_ = replacement_way_before;
    mshr_alloc_index_ = next_mshr_alloc_index;
    if constexpr (boom_model::kArchitecturalModel) {
      // Keep only accepted writeback reads. They retain the same two edges
      // and delayed SRAM writes as the old all-way port conveyor.
      if (writeback_s1_valid_) architectural_wb_s2_ = architectural_wb_s1_;
      if (writeback_s0_fire) {
        const std::size_t set = set_index(writeback_.address);
        const std::size_t first = static_cast<std::size_t>(writeback_s0_beat) * kWordsPerBeat;
        for (std::size_t lane = 0; lane < kWordsPerBeat; ++lane)
          architectural_wb_s1_[lane] = sh_data_[writeback_.way][set][first + lane];
      }
    }
    writeback_s2_valid_ = writeback_s1_valid_;
    writeback_s2_beat_ = writeback_s1_beat_;
    writeback_s1_valid_ = writeback_s0_fire;
    writeback_s1_beat_ = writeback_s0_beat;
    {
    raw_s1_ = raw_s0_;
  raw_s1_.br_mask &=
      static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
  raw_s1_way_override_ = raw_s0_way_override_;
  // s0 request-bus mux (dcache.scala:581-586): the fired winner's bits, or
  // the replay arbiter's deq bits when nothing fires (a 2-input Arbiter's
  // bits fall through to in(1) when neither MSHR offers a replay).
  bus_s2_ = bus_s1_;
  bus_s2_.br_mask &=
      static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
  ++bus_step_n_;
  if (raw_s0_.valid && (raw_s0_type_ != 4 || input.raw_request_fire)) {
    bus_s1_ = raw_s0_;
  } else {
    // Nothing fired into s0: s1_req latches the replay arbiter's
    // fall-through bits captured at cycle start.
    bus_s1_ = fallthrough_bus_;
  }
  bus_s1_.br_mask &=
      static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
  // dcache.scala's s1_type records the cache-pipeline winner, not whichever
  // independent SRAM port happened to see an address.  In particular, a
  // stalled LSU request may still retarget dataReadArb but does not become
  // t_lsu until io.lsu.req.fire.  Preserve the RTL priority exactly:
  // LSU, writeback, prober, MSHR metadata, then replay/idle (type zero).
  oracle_s1_type_ = (input.raw_request_fire || input.request.valid) ? 4
                    : writeback_s0_fire ? 2
                    : prober_meta_read_fire ? 1
                    : raw_s0_.valid && raw_s0_type_ == 3 ? 3
                    : 0;
  // dcache.scala:603 s1_valid(0) and 597 s0_send_resp_or_nack for the
  // request entering s1 on this edge.
  s1_valid_shadow_ =
      oracle_s1_type_ == 4
          ? (raw_s0_.valid && !(s2_store_failed && raw_s0_.uses_stq) &&
             (raw_s0_.br_mask & input.branch_kill_mask) == 0 &&
             !(input.exception && raw_s0_.uses_ldq))
          : (oracle_s1_type_ != 0 || replay_s0);
  s1_send_shadow_ =
      oracle_s1_type_ == 4
          ? raw_s0_.valid
          : (replay_s0 && is_read_command(raw_s0_.command));
    }
  // BranchKillableQueue (util.scala:478-499) resolves masks using PRE valid
  // bits, including an entry dequeued on this edge. Already-invalid slots
  // retain their payload. Enqueue overrides the kill/update, and dequeue
  // has the final priority over the valid bit.
  for (std::size_t i = 0; i < kMshrs; ++i) {
    Mshr& mshr = mshrs_[i];
    const bool did_enq = mshr.rpq_tail != rpq_tail_before[i];
    const bool did_deq = mshr.rpq_head != rpq_head_before[i];
    std::uint32_t slots = rpq_valid_before[i];
    if (did_enq) slots |= UINT32_C(1) << rpq_tail_before[i];
    while (slots != 0) {
      const auto slot = static_cast<std::size_t>(__builtin_ctz(slots));
      slots &= slots - 1u;
      RpqEntry& e = mshr.rpq[slot];
      const bool enqueued = did_enq && slot == rpq_tail_before[i];
      e.valid = enqueued ||
          ((e.request.br_mask & input.branch_kill_mask) == 0 &&
           !(input.exception && e.request.uses_ldq));
      e.request.br_mask &=
          static_cast<boomcfg::br_mask_t>(~input.branch_resolve_mask);
    }
    if (did_deq) mshr.rpq[rpq_head_before[i]].valid = false;
  }
  // The synchronous metadata response advances only for an accepted read.
  // A metadata write blocks a new read; ow_meta separately preserves the
  // pending response's read-before-write value on an address collision.
  {
  const bool meta_s0_fire =
      input.raw_request_fire || input.request.valid ||
      writeback_s0_fire || prober_meta_read_fire ||
      (raw_s0_.valid &&
       (raw_s0_type_ == 0 || raw_s0_type_ == 2 || raw_s0_type_ == 3));
  if (meta_s0_fire) {
    for (std::size_t w = 0; w < kWays; ++w)
      oracle_meta_set_[w] = set_index(raw_s0_.address);
  }
  if (raw_data_s0_.valid) {
    for (std::size_t w = 0; w < kWays; ++w)
      if ((raw_s0_read_ways_ >> w) & 1u) {
        oracle_data_set_[w] = set_index(raw_data_s0_.address);
        oracle_data_beat_[w] =
            (raw_data_s0_.address >> 3) & (kBeats - 1);
      }
  }
  oracle_data_reg_ = oracle_data_now_;
  oracle_array_port_reg_ = oracle_array_port_now_;
  oracle_coh_reg_ = oracle_coh_now_;
  for (std::size_t w = 0; w < kWays; ++w) {
    oracle_data_now_[w] =
        sh_data_[w][oracle_data_set_[w]][oracle_data_beat_[w]];
    const std::size_t row_first_word =
        oracle_data_beat_[w] & ~(kWordsPerBeat - 1u);
    for (std::size_t lane = 0; lane < kWordsPerBeat; ++lane)
      oracle_array_port_now_[w][lane] =
          sh_data_[w][oracle_data_set_[w]][row_first_word + lane];
    const std::size_t ms = oracle_meta_set_[w];
    const std::uint8_t coh =
        !sh_meta_[ms].valid[w] ? 0
        : sh_meta_[ms].dirty[w] ? 3
        : sh_meta_[ms].writable[w] ? 2 : 1;
    oracle_coh_now_[w] = coh;
    oracle_tag_now_[w] = (std::uint32_t(coh) << 20) |
                         (sh_meta_[ms].tag[w] & 0xfffffu);
    if ((meta_pre_valid_ >> w) & 1u) {
      // A pending read of the word being written observes its old value.
      // A pending read of another set observes that other set normally.
      oracle_tag_now_[w] = meta_pre_set_[w] == ms
                               ? meta_pre_word_[w]
                               : oracle_tag_now_[w];
      oracle_coh_now_[w] =
          static_cast<std::uint8_t>((oracle_tag_now_[w] >> 20) & 3u);
    }
  }
  meta_pre_valid_ = 0;
  meta_write_this_step_ = false;
  }
  ++eval_gen_;
  snap_dirty_ = snap_dirty_ || !all_mshrs_idle() ||
                !(respq_enq_ == respq_deq_ && !respq_maybe_full_);
  }

  bool valid(std::size_t way, std::size_t set) const {
    return meta_[set].valid[way];
  }
  bool dirty(std::size_t way, std::size_t set) const {
    return meta_[set].dirty[way];
  }
  std::uint32_t tag(std::size_t way, std::size_t set) const {
    return meta_[set].tag[way];
  }
  std::uint64_t data(std::size_t way, std::size_t set,
                     std::size_t beat) const {
    return data_[way][set][beat];
  }

 public:
  struct RpqEntry {
    BoomUncachedRequest request{};
    // BranchKillableQueue valids(i): cleared by a mispredicting branch or by
    // an exception flush of loads; an invalid head is dequeued on its own.
    bool valid = false;
  };

  struct Mshr {
    MshrState state = MshrState::kIdle;
    std::array<std::uint8_t, 16> rpq_sdq_id{};  // oracle: sdq slot per entry
    BoomUncachedRequest request{};
    std::uint8_t way = 0;
    // The hardware stores a one-hot request payload.  Its reset value zero
    // is distinct from way 0 and remains visible while the MSHR is idle.
    std::uint8_t way_en = 0;
    std::uint8_t refill_beat = 0;
    std::uint8_t commit_beat = 0;
    // mshrs.scala:140 commit_line reg: cleared entering s_drain_rpq_loads
    // (241), set on a load deq.fire (269).  If the rpq drains empty without a
    // single load firing -- every queued load killed by a branch/flush -- the
    // MSHR skips the metadata write and jumps straight to s_mem_finish_1.
    bool commit_line = false;
    std::array<std::uint64_t, kBeats> line{};
    std::array<RpqEntry, kRpqDepth> rpq{};
    std::size_t rpq_head = 0;
    std::size_t rpq_tail = 0;
    std::size_t rpq_count = 0;
    // Mirrors the Chisel Queue's maybe_full register: set when the last
    // count-changing operation was an enqueue.
    bool rpq_maybe_full = false;
    bool metadata_only = false;
    // The rpq ram is a sync-read memory with a read-ahead deq port: the
    // port value is CAPTURED at each read (pre-write content), held between.
    std::uint8_t rpq_port_slot = 0;
    BoomUncachedRequest rpq_port_req{};
    std::uint8_t rpq_port_sdq = 0;
    bool upgrade = false;
    bool victim_dirty = false;
    // Mirrors BoomMSHR.grantack.valid.  A metadata-only hit still passes
    // through Finish1, but has no manager Grant to acknowledge on TL-E.
    bool grant_ack_valid = false;
    std::uint8_t grant_sink = 0;
    // Mirrors BoomMSHR.new_coh and req.old_meta.coh (ClientMetadata state:
    // 0 Nothing, 1 Branch, 2 Trunk, 3 Dirty).  Payload registers: they
    // persist after the transaction like the other request fields.
    std::uint8_t new_coh = 0;
    std::uint8_t old_meta_coh = 0;
    bool rpq_auto_popped = false;  // transient: queue dequeued a dead head
    std::uint32_t victim_tag = 0;
    std::array<std::uint64_t, kBeats> victim_line{};
  };

  struct Writeback {
    WritebackState state = WritebackState::kIdle;
    std::uint8_t owner = 0;
    // Victim way is part of WritebackReq. Probe-originated writebacks do not
    // have an MSHR owner, so it cannot be recovered from mshrs_[owner].
    std::uint8_t way = 0;
    std::uint8_t way_en = 0;
    std::uint8_t read_count = 0;
    std::uint8_t response_tail = 0;
    std::uint8_t release_beat = 0;
    std::uint32_t address = 0;
    std::array<std::uint64_t, kBeats> line{};
    bool acked = false;
    bool probe = false;
    std::uint8_t probe_param = 0;
  };

  struct Lookup {
    bool hit = false;
    std::uint8_t way = 0;
    bool dirty = false;
    bool writable = false;
  };

  struct Prober {
    ProberState state = ProberState::kIdle;
    SmallTileBRequest request{};
    Lookup lookup{};
  };

  static std::uint64_t line_address(std::uint64_t address) {
    return address & ~UINT64_C(0x3f);
  }
  static std::size_t set_index(std::uint64_t address) {
    return static_cast<std::size_t>((address >> 6) & 0x3f);
  }
  static std::uint32_t address_tag(std::uint64_t address) {
    return static_cast<std::uint32_t>(address >> 12);
  }
  static bool is_store(const BoomUncachedRequest& request) {
    return request.uses_stq || request.command == 1;
  }
  static bool is_write_command(std::uint8_t command) {
    return command == 1 || command == 4 || command == 7 ||
           (command >= 8 && command <= 15) || command == 17;
  }

  static bool is_read_command(std::uint8_t command) {
    // rocket Consts.isRead: M_XRD(0), M_XLR(6), M_XSC(7), and isAMO
    // (M_XA_SWAP(4), M_XA_ADD..M_XA_MAXU(8..15)).  The dcache sends a replay
    // response for any read command (dcache.scala:596), which includes a PTW
    // HellaCache load (M_XRD, uses_ldq=0) -- not just LSU ldq/amo loads.
    return command == 0 || command == 4 || command == 6 || command == 7 ||
           (command >= 8 && command <= 15);
  }
  // RTL ClientMetadata.onSecondaryAccess (Metadata.scala:103):
  //   needs_second_acq = isWriteIntent(second_cmd) && !isWriteIntent(first_cmd).
  // A write-intent secondary against a non-write primary must re-acquire, so
  // BoomMSHR.sec_rdy is low and the request is nacked+retried (mshrs.scala:125).
  // Without this the model wrongly absorbs e.g. a store that hits an in-flight
  // load-miss MSHR (sv39's sfence + same-line ld-then-sd loop, where load_retry
  // beats sta_retry so the load allocates the MSHR first).
  static bool needs_second_acquire(const BoomUncachedRequest& secondary,
                                   const BoomUncachedRequest& primary) {
    return is_write_command(secondary.command) &&
           !is_write_command(primary.command);
  }
  static bool same_word(std::uint64_t lhs, std::uint64_t rhs) {
    return (lhs >> 3) == (rhs >> 3);
  }
  static std::uint8_t store_mask(std::uint64_t address,
                                 std::uint8_t size) {
    const unsigned bytes = 1u << (size & 3u);
    const unsigned offset = static_cast<unsigned>(address & 7u);
    const unsigned base = bytes == 8 ? 0xffu : ((1u << bytes) - 1u);
    return static_cast<std::uint8_t>((base << offset) & 0xffu);
  }
  static std::uint64_t amoalu(std::uint64_t address, std::uint8_t size,
                              std::uint8_t command, std::uint64_t lhs,
                              std::uint64_t rhs) {
    const std::uint8_t mask = store_mask(address, size);
    const bool is_max = command == 13 || command == 15;
    const bool is_min = command == 12 || command == 14;
    const bool is_add = command == 8;
    const bool logic_and = command == 10 || command == 11;
    const bool logic_xor = command == 9 || command == 10;

    std::uint64_t adder_mask = UINT64_MAX;
    if ((mask & 0x08u) == 0) adder_mask &= ~(UINT64_C(1) << 31);
    const std::uint64_t adder =
        (lhs & adder_mask) + (rhs & adder_mask);

    const bool signed_compare = (command & 2u) == 0;
    auto less_width = [&](unsigned bits) {
      if (bits == 32) {
        const std::uint32_t x = static_cast<std::uint32_t>(lhs);
        const std::uint32_t y = static_cast<std::uint32_t>(rhs);
        const bool sx = (x >> 31) != 0;
        const bool sy = (y >> 31) != 0;
        return sx == sy ? x < y : (signed_compare ? sx : sy);
      }
      const bool sx = (lhs >> 63) != 0;
      const bool sy = (rhs >> 63) != 0;
      return sx == sy ? lhs < rhs : (signed_compare ? sx : sy);
    };
    const bool less = less_width((mask & 0x10u) != 0 ? 64u : 32u);
    const std::uint64_t minmax = (less ? is_min : is_max) ? lhs : rhs;
    const std::uint64_t logic =
        (logic_and ? (lhs & rhs) : 0) |
        (logic_xor ? (lhs ^ rhs) : 0);
    const std::uint64_t result =
        is_add ? adder : ((logic_and || logic_xor) ? logic : minmax);

    std::uint64_t byte_mask = 0;
    for (unsigned byte = 0; byte < 8; ++byte)
      if ((mask >> byte) & 1u) byte_mask |= UINT64_C(0xff) << (8u * byte);
    return (byte_mask & result) | (~byte_mask & lhs);
  }
  // rpq.io.deq.valid: a live head that is not being killed on this edge.
  static bool rpq_head_deq_valid(const Mshr& mshr,
                                 const SmallDcacheInputs& input) {
    const RpqEntry& head = mshr.rpq[mshr.rpq_head];
    return mshr.rpq_count != 0 && !mshr.rpq_auto_popped && head.valid &&
           (head.request.br_mask & input.branch_kill_mask) == 0 &&
           !(input.exception && head.request.uses_ldq);
  }
  // ClientMetadata state of one line, from the functional arrays.
  std::uint8_t line_coh(std::size_t way, std::size_t set) const {
    return !meta_[set].valid[way] ? 0 : meta_[set].dirty[way] ? 3 : meta_[set].writable[way] ? 2 : 1;
  }

  Lookup lookup_line(std::uint64_t address) const {
    Lookup result;
    const std::size_t set = set_index(address);
    const std::uint32_t tag = address_tag(address);
    for (std::size_t way = 0; way < kWays; ++way) {
      if (meta_[set].valid[way] && meta_[set].tag[way] == tag) {
        result.hit = true;
        result.way = static_cast<std::uint8_t>(way);
        result.dirty = meta_[set].dirty[way];
        result.writable = meta_[set].writable[way];
        break;
      }
    }
    return result;
  }

  static constexpr std::uint8_t probe_report_param_for(
      bool hit, bool writable, std::uint8_t requested_cap) {
    // TLPermissions report encoding is distinct from the shrink encoding:
    // TtoB=0, TtoN=1, BtoN=2, TtoT=3, BtoB=4, NtoN=5.
    // Reusing BtoN (2) for BtoB loses the fact that another cache still has
    // a shared copy, which in turn leaves Broadcast's tracker.shared clear.
    if (!hit) return 5;                 // NtoN
    if (requested_cap == 2)
      return writable ? 1 : 2;         // TtoN / BtoN
    return writable ? 0 : 4;           // TtoB / BtoB
  }

  std::uint8_t probe_report_param() const {
    return probe_report_param_for(prober_.lookup.hit,
                                  prober_.lookup.writable,
                                  prober_.request.param);
  }

  bool probe_mshrs_ready(std::uint64_t address) const {
    const std::size_t set = set_index(address);
    for (const Mshr& mshr : mshrs_) {
      if (mshr.state == MshrState::kIdle ||
          set_index(mshr.request.address) != set)
        continue;
      if (mshr.state != MshrState::kAcquire &&
          mshr.state != MshrState::kRefill &&
          mshr.state != MshrState::kDrainLoads)
        return false;
    }
    return true;
  }

  void apply_probe_metadata() {
    if (!prober_.lookup.hit) return;
    const std::size_t way = prober_.lookup.way;
    const std::size_t set = set_index(prober_.request.address);
    if (prober_.request.param == 2) {
      meta_[set].valid[way] = false;
      meta_[set].dirty[way] = false;
      meta_[set].writable[way] = false;
      // MetaWrite owns the array port, so there is no accepted read whose
      // response needs read-before-write forwarding on this edge.
      ow_meta(way, set, meta_[set].tag[way], false, false, false,
              /*show_pre=*/false);
    } else {
      meta_[set].dirty[way] = false;
      meta_[set].writable[way] = false;
      // TtoB/BtoB is also a real metadata write: the line remains valid but
      // loses Dirty/Trunk permission. Keep the oracle SRAM shadow in sync.
      ow_meta(way, set, meta_[set].tag[way], true, false, false,
              /*show_pre=*/false);
    }
  }

  bool request_hits_pipeline(const BoomUncachedRequest& request,
                             const Lookup& lookup) const {
    if (!lookup.hit) return false;
    if (!is_store(request)) return true;
    // A clean Trunk line has write permission, but changing its metadata to
    // Dirty still goes through an MSHR replay.  Only an already-Dirty line is
    // a store hit in the ordinary s2/s3 pipeline.
    return lookup.dirty;
  }

  static BoomUncachedCompletion completion_for(
      const BoomUncachedRequest& request, std::uint64_t data) {
    return BoomUncachedCompletion{true, data, request.uses_ldq,
                                  request.uses_stq, request.ldq_idx,
                                  request.stq_idx, request.is_hella, request.is_amo};
  }

  static std::uint64_t extend_load(std::uint64_t value,
                                   std::uint8_t size, bool sign) {
    const unsigned bits = 8u << size;
    if (bits >= 64) return value;
    const std::uint64_t mask = (UINT64_C(1) << bits) - 1;
    value &= mask;
    if (sign && ((value >> (bits - 1)) & 1u)) value |= ~mask;
    return value;
  }

  std::uint64_t load_from_cache(const BoomUncachedRequest& request,
                                std::size_t way) const {
    const std::size_t set = set_index(request.address);
    const std::size_t beat = (request.address >> 3) & 7u;
    const unsigned shift = static_cast<unsigned>(request.address & 7u) * 8u;
    return extend_load(data_[way][set][beat] >> shift, request.size,
                       request.is_signed);
  }

  // Exact cache_resp.bits.data projection from the raw RTL pipeline shadows.
  // These shadows retain the SRAM port word and unconditional s2_req payload
  // even when the functional request object has already been consumed.
  std::uint64_t cache_response_data_oracle() const {
    std::uint64_t word = 0;
    for (std::size_t way = 0; way < kWays; ++way)
      if ((s2_tag_match_way_ >> way) & 1u)
        word |= oracle_array_port_reg_[way]
                    [(bus_s2_.address >> 3) & (kWordsPerBeat - 1u)];
    if (s5_valid_ && same_word(bus_s2_.address, s5_req_addr_))
      word = s5_req_data_;
    if (s4_valid_ && same_word(bus_s2_.address, s4_req_addr_))
      word = s4_req_data_;
    if (s3_valid_ && same_word(bus_s2_.address, s3_req_addr_))
      word = s3_req_data_;
    const unsigned shift =
        static_cast<unsigned>(bus_s2_.address & 7u) * 8u;
    return extend_load(word >> shift, bus_s2_.size,
                       bus_s2_.is_signed);
  }

  static std::uint64_t load_from_line(
      const Mshr& mshr, const BoomUncachedRequest& request) {
    const std::size_t beat = (request.address >> 3) & 7u;
    const unsigned shift = static_cast<unsigned>(request.address & 7u) * 8u;
    return extend_load(mshr.line[beat] >> shift, request.size,
                       request.is_signed);
  }

  void store_to_cache(const BoomUncachedRequest& request, std::size_t way,
                      int write_delay = 1) {
    const std::size_t set = set_index(request.address);
    const std::size_t beat = (request.address >> 3) & 7u;
    const unsigned bytes = 1u << request.size;
    const unsigned offset = static_cast<unsigned>(request.address & 7u);
    std::uint64_t mask = UINT64_MAX;
    if (bytes < 8) mask = ((UINT64_C(1) << (bytes * 8u)) - 1u);
    mask <<= offset * 8u;
    const std::uint64_t old_data = data_[way][set][beat];
    data_[way][set][beat] =
        (old_data & ~mask) | (request.data & mask);
    if (small_dcache_store_debug_enabled() &&
        request.address == UINT64_C(0x80029068)) {
      std::fprintf(stderr,
                   "[DCSTORE] n=%llu way=%zu set=%zu beat=%zu old=%llx "
                   "req=%llx new=%llx delay=%d\n",
                   static_cast<unsigned long long>(bus_step_n_), way, set,
                   beat, static_cast<unsigned long long>(old_data),
                   static_cast<unsigned long long>(request.data),
                   static_cast<unsigned long long>(data_[way][set][beat]),
                   write_delay);
    }
    ow_data(way, set, beat, data_[way][set][beat], write_delay);
  }

  int find_matching_mshr(std::uint64_t address) const {
    const std::uint64_t line = line_address(address);
    for (std::size_t index = 0; index < kMshrs; ++index) {
      if (mshrs_[index].state != MshrState::kIdle &&
          line_address(mshrs_[index].request.address) == line)
        return static_cast<int>(index);
    }
    return -1;
  }

  int find_matching_set_mshr(std::uint64_t address) const {
    const std::size_t set = set_index(address);
    for (std::size_t index = 0; index < kMshrs; ++index)
      if (mshrs_[index].state != MshrState::kIdle &&
          set_index(mshrs_[index].request.address) == set)
        return static_cast<int>(index);
    return -1;
  }

  // RTL reads the MSHR state REGISTERS combinationally, so a same-cycle
  // finish->idle transition (step_mshr, above) must not free the line/set for
  // a new allocation until the next edge.  These overloads take a cycle-start
  // state snapshot for the allocation decision (io.idx.valid := state =/=
  // s_invalid holds through s_mem_finish_1/2).
  int find_matching_mshr(std::uint64_t address,
                         const std::array<MshrState, kMshrs>& state_at) const {
    const std::uint64_t line = line_address(address);
    for (std::size_t index = 0; index < kMshrs; ++index)
      if (state_at[index] != MshrState::kIdle &&
          line_address(mshrs_[index].request.address) == line)
        return static_cast<int>(index);
    return -1;
  }

  int find_matching_set_mshr(std::uint64_t address,
                             const std::array<MshrState, kMshrs>& state_at) const {
    const std::size_t set = set_index(address);
    for (std::size_t index = 0; index < kMshrs; ++index)
      if (state_at[index] != MshrState::kIdle &&
          set_index(mshrs_[index].request.address) == set)
        return static_cast<int>(index);
    return -1;
  }

  static bool mshr_accepts_secondary(MshrState state) {
    return state != MshrState::kIdle &&
           state != MshrState::kMetaWrite &&
           state != MshrState::kFinish1 &&
           state != MshrState::kFinish2;
  }

  bool mshr_blocks_hit(std::uint64_t address) const {
    for (const Mshr& mshr : mshrs_)
      if (mshr.state != MshrState::kIdle &&
          line_address(mshr.request.address) == line_address(address))
        return true;
    return false;
  }

  bool mshr_owns_hit_way_for_other_tag(std::uint64_t address,
                                       std::uint8_t hit_way) const {
    const std::size_t set = set_index(address);
    bool index_match = false;
    bool tag_match = false;
    bool way_match = false;
    const std::uint8_t hit_way_en =
        static_cast<std::uint8_t>(1u << (hit_way & (kWays - 1u)));
    for (const Mshr& mshr : mshrs_) {
      // BoomMSHR.io.{idx,tag}.valid are state =/= s_invalid, and this locked
      // Small configuration does not instantiate the optional prefetch
      // states for which io.way.valid would differ.
      if (mshr.state == MshrState::kIdle ||
          set_index(mshr.request.address) != set)
        continue;
      index_match = true;
      tag_match |= address_tag(mshr.request.address) == address_tag(address);
      way_match |= mshr.way_en == hit_way_en;
    }
    // mshrs.scala:746: idx_match && way_match && !tag_match.
    return index_match && way_match && !tag_match;
  }

  static bool mshr_accepts_secondary(const Mshr& mshr) {
    // BoomMSHR keeps idx/tag visible through its finish states, so a request
    // to the same line still blocks primary allocation.  Its secondary input
    // is deliberately closed while metadata is being installed and during
    // the two finish cycles; such a request must be nacked and retried.
    return mshr.state != MshrState::kIdle &&
           mshr.state != MshrState::kMetaWrite &&
           mshr.state != MshrState::kFinish1 &&
           mshr.state != MshrState::kFinish2;
  }

  int select_idle_mshr() const {
    for (std::size_t delta = 0; delta < kMshrs; ++delta) {
      const std::size_t index = (mshr_head_ + delta) & (kMshrs - 1);
      if (mshrs_[index].state == MshrState::kIdle)
        return static_cast<int>(index);
    }
    return -1;
  }

  int selected_idle_mshr() const {
    const std::size_t index = mshr_alloc_index_ & (kMshrs - 1u);
    return mshrs_[index].state == MshrState::kIdle
               ? static_cast<int>(index)
               : -1;
  }

  int selected_finish_mshr() const {
    for (std::size_t index = 0; index < kMshrs; ++index)
      if (mshrs_[index].state == MshrState::kFinish1 &&
          mshrs_[index].grant_ack_valid)
        return static_cast<int>(index);
    return -1;
  }

  bool all_mshrs_idle() const {
    for (const Mshr& mshr : mshrs_)
      if (mshr.state != MshrState::kIdle) return false;
    return true;
  }

  bool request_pipeline_ready() const {
    // L1MetadataArray clears one set per cycle after reset and rejects reads
    // while that write walk owns its single SRAM port.
    if (metadata_reset_cycles_ != 0) return false;
    if (writeback_.state == WritebackState::kFillBuffer &&
        writeback_.read_count < kTransferBeats)
      return false;
    if (prober_.state == ProberState::kMetaRead ||
        prober_.state == ProberState::kMetaWrite)
      return false;
    // D-cache pipeline reads lose arbitration to MSHR replay and metadata
    // maintenance.  Refill writes use the independent write port.
    for (const Mshr& mshr : mshrs_) {
      if ((mshr.state == MshrState::kReplay && mshr.rpq_count != 0) ||
          mshr.state == MshrState::kMetaRead ||
          mshr.state == MshrState::kMetaClear ||
          mshr.state == MshrState::kMetaWrite)
        return false;
    }
    return true;
  }

  static bool sdq_has_free_slot(std::uint32_t value) {
    return (value & kSdqFullMask) != kSdqFullMask;
  }

  void enqueue_rpq(Mshr& mshr, const BoomUncachedRequest& request) {
    mshr.rpq_maybe_full = true;
    if (mshr.rpq_count == kRpqDepth) return;
    if (!sdq_has_free_slot(sdq_alloc_view_)) return;
    // BoomMSHR writes every RPQ payload field on every enqueue.  sdq_id is
    // always the PriorityEncoder of the cycle-start free-slot bitmap, even
    // for a load that does not actually allocate the selected SDQ entry.
    // Thus a load must overwrite a stale ring-slot payload with the current
    // lowest-free index, not with a literal zero.
    std::uint8_t id = 0;
    while (id < kSdqDepth && (sdq_alloc_view_ >> id) & 1u) ++id;
    // A real store cannot enqueue when all 17 slots are occupied.  Preserve
    // the RTL PriorityEncoder's deterministic last-index fallback for any
    // non-store payload observed in that otherwise degenerate state.
    if (id == kSdqDepth) id = kSdqDepth - 1u;
    if (is_store(request)) {
      // Oracle: the RTL allocates the lowest free store-data-queue slot at
      // enqueue and parks the data there until the replay pops it.
      if (((sdq_alloc_view_ >> id) & 1u) == 0) {
        sdq_alloc_view_ |= (1u << id);
        sdq_val_ |= (1u << id);
        sdq_data_[id] = request.data;
      } else {
        // A full SDQ prevents a real store enqueue.  Keep the payload
        // deterministic if a diagnostic caller violates that precondition.
        id = 0;
      }
    }
    mshr.rpq_sdq_id[mshr.rpq_tail] = id;
    mshr.rpq[mshr.rpq_tail].request = request;
    mshr.rpq[mshr.rpq_tail].valid = true;
    mshr.rpq_tail = (mshr.rpq_tail + 1) % kRpqDepth;
    ++mshr.rpq_count;
  }

  void allocate_mshr(std::size_t index,
                     const BoomUncachedRequest& request,
                     const Lookup& lookup) {
    Mshr& mshr = mshrs_[index];
    // RTL MSHR payload registers (request fields, way, rpq ring position)
    // persist across transactions; only the transient bookkeeping resets.
    mshr.state = MshrState::kIdle;
    mshr.refill_beat = 0;
    mshr.commit_beat = 0;
    mshr.rpq_count = 0;
    mshr.metadata_only = false;
    mshr.upgrade = false;
    mshr.victim_dirty = false;
    mshr.grant_ack_valid = false;
    mshr.request = request;
    const std::size_t set = set_index(request.address);
    if (lookup.hit) {
      mshr.way = lookup.way;
      // handle_pri_req with tag_match: old_meta.coh is the hit state; a
      // permitted store goes straight to coh_on_hit (Dirty), otherwise the
      // upgrade keeps old_coh until the grant.
      mshr.old_meta_coh = line_coh(lookup.way, set);
      mshr.new_coh = (is_store(request) && lookup.writable) ? 3 : mshr.old_meta_coh;
      mshr.metadata_only =
          is_store(request) && lookup.writable;
      mshr.upgrade = is_store(request) && !lookup.writable;
      mshr.state = mshr.metadata_only ? MshrState::kReplay
                                      : MshrState::kAcquire;
    } else {
      mshr.state = MshrState::kAcquire;
      mshr.way = s2_replacement_way_;
      // No tag match: old_meta is the replaced way's metadata and new_coh
      // restarts from Nothing (ClientMetadata.onReset).
      mshr.old_meta_coh = line_coh(mshr.way, set);
      mshr.new_coh = 0;
      mshr.victim_dirty = meta_[set].dirty[mshr.way];
      mshr.victim_tag = meta_[set].tag[mshr.way];
      mshr.victim_line = data_[mshr.way][set];
    }
    mshr.way_en = static_cast<std::uint8_t>(1u << mshr.way);
    enqueue_rpq(mshr, request);
    mshr_head_ = static_cast<std::uint8_t>(
        (mshr_head_ + 1u) & (kMshrs - 1u));
    // Chisel's 16-bit Fibonacci LFSR advances only on a primary miss.  Its
    // low log2Ceil(kWays) bits select the victim way.
  }

  void advance_replacement() {
    const std::uint16_t feedback = static_cast<std::uint16_t>(
        ((replacement_lfsr_ >> 15) ^ (replacement_lfsr_ >> 13) ^
         (replacement_lfsr_ >> 12) ^ (replacement_lfsr_ >> 10)) & 1u);
    replacement_lfsr_ = static_cast<std::uint16_t>(
        (replacement_lfsr_ << 1) | feedback);
    if (replacement_lfsr_ == 0) replacement_lfsr_ = 1;
  }

  void step_writeback(const SmallDcacheInputs& input,
                      bool read_ports_available) {
    switch (writeback_.state) {
      case WritebackState::kIdle:
        break;
      case WritebackState::kFillBuffer:
        if (writeback_.read_count < kTransferBeats &&
            read_ports_available) {
          ++writeback_.read_count;
          raw_s0_ = BoomUncachedRequest{};
          raw_s0_.valid = true;
          raw_s0_.address =
              writeback_.address +
              boomcfg::TILE_BEAT_BYTES *
                  static_cast<std::uint32_t>(writeback_.read_count - 1u);
          raw_data_s0_ = raw_s0_;
          raw_s0_type_ = 2;  // t_wb
          raw_s0_read_ways_ = std::uint8_t(1u << writeback_.way);
          if (writeback_.read_count == kTransferBeats)
            writeback_.response_tail = 2;
        } else if (writeback_.response_tail > 1) {
          --writeback_.response_tail;
        } else if (writeback_.response_tail == 1) {
          writeback_.response_tail = 0;
          writeback_.read_count = 0;  // the counter re-runs for the release
          writeback_.state = WritebackState::kLsuRelease;
        }
        break;
      case WritebackState::kLsuRelease:
        if (input.lsu_release_ready) {
          writeback_.release_beat = 0;
          writeback_.state = WritebackState::kActive;
        }
        break;
      case WritebackState::kActive:
        if (input.tile_c_ready) {
          writeback_.read_count =
              static_cast<std::uint8_t>(writeback_.read_count + 1u);
          if (writeback_.release_beat + 1 == kTransferBeats) {
            writeback_.release_beat = 0;
            // ProbeAckData is the response to a manager-originated B probe;
            // unlike a voluntary ReleaseData it has no ReleaseAck returning
            // to this cache.  BoomWritebackUnit therefore becomes ready as
            // soon as its final probe beat is accepted.
            if (writeback_.probe) {
              writeback_.state = WritebackState::kIdle;  // payload persists
            } else
              writeback_.state = WritebackState::kGrant;
          } else {
            ++writeback_.release_beat;
          }
        }
        break;
      case WritebackState::kGrant:
        if (writeback_.acked) {
          writeback_.state = WritebackState::kIdle;  // payload persists
          writeback_.acked = false;
        } else if (input.tile_d.valid && input.tile_d.source == kMshrs &&
                   input.tile_d.opcode == 6) {
          writeback_.acked = true;
        }
        break;
    }
  }

  void start_writeback(std::size_t index, const Mshr& mshr) {
    writeback_.state = WritebackState::kFillBuffer;
    writeback_.read_count = 0;
    writeback_.response_tail = 0;
    writeback_.release_beat = 0;
    writeback_.acked = false;
    writeback_.probe = false;
    writeback_.owner = static_cast<std::uint8_t>(index);
    writeback_.way = mshr.way;
    writeback_.way_en = mshr.way_en;
    writeback_.address = static_cast<std::uint32_t>(
        (static_cast<std::uint64_t>(mshr.victim_tag) << 12) |
        (static_cast<std::uint64_t>(set_index(mshr.request.address)) << 6));
  }

  void start_probe_writeback() {
    writeback_.state = WritebackState::kFillBuffer;
    writeback_.read_count = 0;
    writeback_.response_tail = 0;
    writeback_.release_beat = 0;
    writeback_.acked = false;
    writeback_.probe = false;
    writeback_.way = prober_.lookup.way;
    writeback_.way_en =
        static_cast<std::uint8_t>(1u << prober_.lookup.way);
    writeback_.address = static_cast<std::uint32_t>(
        line_address(prober_.request.address));
    writeback_.probe = true;
    writeback_.probe_param = probe_report_param();
  }

  void step_prober(const SmallDcacheInputs& input,
                   bool meta_read_available,
                   bool meta_write_available,
                   bool writeback_lsu_release_owns,
                   bool writeback_c_owns,
                   bool& writeback_available) {
    switch (prober_.state) {
      case ProberState::kIdle:
        if (input.tile_b.valid) {
          prober_ = Prober{};
          prober_.request = input.tile_b;
          prober_.state = ProberState::kMetaRead;
        }
        break;

      case ProberState::kMetaRead:
        if (meta_read_available)
          prober_.state = ProberState::kMetaResp;
        break;

      case ProberState::kMetaResp:
        // The metadata SRAM response reaches the ordinary D-cache s2 lookup
        // one cycle after the arbitrated read.
        prober_.state = ProberState::kMshrReq;
        break;

      case ProberState::kMshrReq: {
        // BoomProbeUnit captures way_en/block_state from the s2 lookup here.
        // If either an MSHR for this set or the writeback unit conflicts, the
        // lookup is retried from the metadata-read state.
        const Lookup lookup = lookup_line(prober_.request.address);
        const bool writeback_ready =
            writeback_.state == WritebackState::kIdle ||
            set_index(writeback_.address) !=
                set_index(prober_.request.address);
        if (probe_mshrs_ready(prober_.request.address) &&
            writeback_ready) {
          prober_.lookup = lookup;
          prober_.state = ProberState::kMshrResp;
        } else {
          prober_.state = ProberState::kMetaRead;
        }
        break;
      }

      case ProberState::kMshrResp:
        prober_.state =
            prober_.lookup.hit && prober_.lookup.dirty
                ? ProberState::kWritebackReq
                : ProberState::kLsuRelease;
        break;

      case ProberState::kLsuRelease:
        if (!writeback_lsu_release_owns && input.lsu_release_ready)
          prober_.state = ProberState::kRelease;
        break;

      case ProberState::kRelease:
        if (!writeback_c_owns && input.tile_c_ready) {
          if (prober_.lookup.hit)
            prober_.state = ProberState::kMetaWrite;
          else
            // BoomProbeUnit only returns the FSM to s_invalid.  Its req,
            // way_en and metadata payload registers retain their last bits.
            prober_.state = ProberState::kIdle;
        }
        break;

      case ProberState::kWritebackReq:
        if (writeback_available) {
          start_probe_writeback();
          writeback_available = false;
          prober_.state = ProberState::kWritebackResp;
        }
        break;

      case ProberState::kWritebackResp:
        // wb.io.req.ready rises again only on the cycle after the final
        // ProbeAckData beat returned the writeback unit to Idle.
        if (writeback_available)
          prober_.state = ProberState::kMetaWrite;
        break;

      case ProberState::kMetaWrite:
        if (meta_write_available) {
          apply_probe_metadata();
          prober_.state = ProberState::kMetaWriteResp;
        }
        break;

      case ProberState::kMetaWriteResp:
        // Payload registers are intentionally not reset on retirement; they
        // remain observable while state is invalid until the next Probe.
        prober_.state = ProberState::kIdle;
        break;
    }
  }

  void step_mshr(std::size_t index, const SmallDcacheInputs& input,
                 BoomUncachedCompletion& produced_response,
                 bool writeback_response, bool& writeback_available,
                 bool& line_buffer_read_available,
                 bool response_queue_ready,
                 bool& cache_replay_available,
                 bool& mshr_meta_read_available,
                 bool& replay_store_issued,
                 bool& refill_write_available) {
    Mshr& mshr = mshrs_[index];
    switch (mshr.state) {
      case MshrState::kIdle:
        break;

      case MshrState::kAcquire: {
        // tile_a is offered by the first MSHR in Acquire (the same scan the
        // cycle face performs, on the current state).
        int acquire = -1;
        for (std::size_t i = 0; i < kMshrs; ++i)
          if (mshrs_[i].state == MshrState::kAcquire) { acquire = static_cast<int>(i); break; }
        if (input.tile_a_ready && acquire == static_cast<int>(index)) {
          mshr.state = MshrState::kRefill;
          mshr.refill_beat = 0;
        }
        break;
      }

      case MshrState::kRefill:
        if (input.tile_d.valid && input.tile_d.source == index) {
          const std::size_t word =
              static_cast<std::size_t>(mshr.refill_beat) * kWordsPerBeat;
          mshr.line[word] = input.tile_d.data;
          if constexpr (kWordsPerBeat == 2)
            mshr.line[word + 1u] = input.tile_d.data_hi;
          if (mshr.refill_beat + 1 == kTransferBeats) {
            // refill_done: new_coh := new_coh.onGrant(req cmd, grant param)
            // (toT=0 -> Dirty for a write else Trunk, toB=1 -> Branch).
            mshr.new_coh = input.tile_d.param == 0
                               ? (is_store(mshr.request) ? 3 : 2)
                               : (input.tile_d.param == 1 ? 1 : 0);
            mshr.grant_ack_valid =
                input.tile_d.opcode == 4 || input.tile_d.opcode == 5;
            mshr.grant_sink = input.tile_d.sink;
            mshr.state = MshrState::kDrainLoads;
            mshr.refill_beat = 0;
            mshr.commit_line = false;   // mshrs.scala:241
          } else {
            ++mshr.refill_beat;
          }
        }
        break;

      case MshrState::kDrainLoads:
        if (mshr.rpq_count == 0) {
          // mshrs.scala:271-282: rpq empty with no load ever drained
          // (commit_line still false, e.g. all queued loads killed by the
          // order-fail flush) skips the metadata write -> s_mem_finish_1;
          // otherwise the normal post-drain metadata path.
          mshr.state = mshr.commit_line ? MshrState::kMetaRead
                                        : MshrState::kFinish1;
        } else {
          const BoomUncachedRequest& request =
              mshr.rpq[mshr.rpq_head].request;
          if (!rpq_head_deq_valid(mshr, input)) {
            // deq.valid low: nothing drains this cycle.
          } else if (request.uses_ldq || request.is_hella) {
            // mshrs.scala:259-264: lb_read.valid does not depend on
            // resp.ready. A stalled drain still owns the line-buffer port,
            // while only an accepted response may pop its RPQ entry.
            const bool line_buffer_granted = line_buffer_read_available;
            line_buffer_read_available = false;
            if (!produced_response.valid && line_buffer_granted && response_queue_ready) {
              produced_response = completion_for(
                  request, load_from_line(mshr, request));
              const std::size_t respq_slot = respq_enq_ & 3u;
              respq_data_[respq_slot] = produced_response.data;
              respq_completion_[respq_slot] = produced_response;
              respq_br_mask_[respq_slot] =
                  static_cast<boomcfg::br_mask_t>(
                      request.br_mask & ~input.branch_resolve_mask);
              respq_is_hella_[respq_slot] = request.is_hella;
              respq_valid_[respq_slot] = true;
              respq_enq_ = (respq_enq_ + 1u) & 3u;
              ++respq_count_;
              mshr.rpq_head = (mshr.rpq_head + 1) % kRpqDepth;
              // Sync-read rpq ram: the deq port pre-reads the NEW head.
              mshr.rpq_port_slot = static_cast<std::uint8_t>(mshr.rpq_head);
              mshr.rpq_port_req = mshr.rpq[mshr.rpq_head].request;
              mshr.rpq_port_sdq = mshr.rpq_sdq_id[mshr.rpq_head];
              mshr.rpq_maybe_full = false;
              --mshr.rpq_count;
              mshr.commit_line = true;   // mshrs.scala:269 deq.fire
            }
          } else {
            mshr.state = MshrState::kMetaRead;
          }
        }
        break;

      case MshrState::kMetaRead:
        if (mshr_meta_read_available) {
          mshr_meta_read_available = false;
          // The meta pass carries only the line address; the uop/data
          // payload rides the replay pass instead.
          raw_s0_ = BoomUncachedRequest{};
          raw_s0_.valid = true;
          // dcache.scala:519 mshr_read_req.addr = Cat(tag, idx) << blockOffBits.
          raw_s0_.address = line_address(mshr.request.address);
          raw_s0_way_override_ = mshr.way;
          raw_s0_type_ = 3;  // t_mshr_meta_read
          mshr.state = MshrState::kMetaResp1;
        }
        break;
      case MshrState::kMetaResp1:
        mshr.state = MshrState::kMetaResp2;
        break;
      case MshrState::kMetaResp2:
        if (mshr.victim_dirty) {
          mshr.state = MshrState::kMetaClear;
        } else {
          mshr.state = MshrState::kCommitLine;
          mshr.commit_beat = 0;
        }
        break;

      case MshrState::kMetaClear: {
        // This is a metadata-array write, not a read-arbiter winner.  The
        // cache s0 request bus therefore continues to show replay-arbiter
        // fallback bits; exposing mshr.request here incorrectly leaked its
        // uop into s1/s2 for two cycles.
        const std::size_t set = set_index(mshr.request.address);
        meta_[set].valid[mshr.way] = false;
        meta_[set].dirty[mshr.way] = false;
        meta_[set].writable[mshr.way] = false;
        // RTL's clear writes the NEW request's tag with coh=Nothing
        // (mshrs.scala:300-301); the port shows the written word already
        // on the write cycle.
        ow_meta(mshr.way, set, address_tag(mshr.request.address), false,
                false, false, /*show_pre=*/false);
        mshr.state = MshrState::kWritebackReq;
        break;
      }
      case MshrState::kWritebackMetaRead:
        break;
      case MshrState::kWritebackReq:
        if (writeback_available) {
          start_writeback(index, mshr);
          writeback_available = false;
          mshr.state = MshrState::kWritebackResp;
        }
        break;
      case MshrState::kWritebackResp:
        if (writeback_response && !writeback_.probe &&
            writeback_.owner == index) {
          mshr.state = MshrState::kCommitLine;
          mshr.commit_beat = 0;
        }
        break;

      case MshrState::kCommitLine: {
        if (!line_buffer_read_available) break;
        line_buffer_read_available = false;
        if (!refill_write_available) break;
        refill_write_available = false;
        const std::size_t set = set_index(mshr.request.address);
        const std::size_t first_word =
            static_cast<std::size_t>(mshr.commit_beat) * kWordsPerBeat;
        // This state-machine edge is the RTL array-write edge.  The current
        // MPORT was sampled before step_mshr(), while the next cycle must see
        // the committed beat.  One extra shadow delay only becomes visible
        // when CommitLine turns directly into Replay.
        for (std::size_t lane = 0; lane < kWordsPerBeat; ++lane) {
          const std::size_t word = first_word + lane;
          ow_data(mshr.way, set, word, mshr.line[word], 0);
          data_[mshr.way][set][word] = mshr.line[word];
        }
        if (small_dcache_store_debug_enabled() && set == 1 &&
            first_word <= 5 && 5 < first_word + kWordsPerBeat) {
          std::fprintf(stderr,
                       "[DCREFILL] n=%llu way=%u set=%zu beat=5 data=%llx\n",
                       static_cast<unsigned long long>(bus_step_n_),
                       static_cast<unsigned>(mshr.way), set,
                       static_cast<unsigned long long>(mshr.line[5]));
        }
        if (mshr.commit_beat + 1 == kTransferBeats) {
          mshr.state = MshrState::kReplay;
          mshr.commit_beat = 0;
        } else {
          ++mshr.commit_beat;
        }
        break;
      }

      case MshrState::kReplay:
        // The empty-queue retirement depends on this cycle's RPQ enqueue and
        // is therefore finalized after s2 miss arbitration in step().
        if (mshr.rpq_count != 0 && cache_replay_available &&
            rpq_head_deq_valid(mshr, input)) {
          cache_replay_available = false;
          const BoomUncachedRequest request =
              mshr.rpq[mshr.rpq_head].request;
          raw_s0_ = request;
          raw_s0_.valid = true;
          // BoomMSHRFile overwrites replay.bits.data with the asynchronous
          // SDQ read for every replay, including loads.  A load does not use
          // the payload functionally, but s1_req/s2_req latch it unconditionally
          // and the oracle contract observes that stale word.
          raw_s0_.data = sdq_port_cycle_oracle_;
          raw_data_s0_ = raw_s0_;
          raw_s0_type_ = 0;  // t_replay
          raw_s0_read_ways_ = std::uint8_t(1u << mshr.way);
          if (is_store(request)) {
            const std::uint8_t id = mshr.rpq_sdq_id[mshr.rpq_head];
            sdq_val_ &= ~(1u << id);
            sdq_data_read_ = sdq_data_[id];
            if (small_dcache_store_debug_enabled() &&
                request.address == UINT64_C(0x80029068)) {
              std::fprintf(stderr,
                           "[DCREPLAY] n=%llu mshr=%zu id=%u req=%llx "
                           "sdq=%llx count=%u\n",
                           static_cast<unsigned long long>(bus_step_n_), index,
                           static_cast<unsigned>(id),
                           static_cast<unsigned long long>(request.data),
                           static_cast<unsigned long long>(sdq_data_[id]),
                           static_cast<unsigned>(mshr.rpq_count));
            }
          }
          if (is_store(request)) {
            // io.replay.fire && isWrite: new_coh := coh_on_hit (Dirty).
            mshr.new_coh = 3;
            store_to_cache(request, mshr.way, 3);
            replay_store_issued = true;
            const std::size_t set = set_index(request.address);
            meta_[set].writable[mshr.way] = true;
            meta_[set].dirty[mshr.way] = true;
          }
          mshr.rpq_head = (mshr.rpq_head + 1) % kRpqDepth;
          // Sync-read rpq ram: the deq port pre-reads the NEW head.
          mshr.rpq_port_slot = static_cast<std::uint8_t>(mshr.rpq_head);
          mshr.rpq_port_req = mshr.rpq[mshr.rpq_head].request;
          mshr.rpq_port_sdq = mshr.rpq_sdq_id[mshr.rpq_head];
          mshr.rpq_maybe_full = false;
          --mshr.rpq_count;
        }
        break;

      case MshrState::kMetaWrite: {
        const std::size_t set = set_index(mshr.request.address);
        // s_meta_write_req writes new_coh, not the primary command.
        meta_[set].valid[mshr.way] = mshr.new_coh != 0;
        meta_[set].dirty[mshr.way] = mshr.new_coh == 3;
        meta_[set].writable[mshr.way] = mshr.new_coh >= 2;
        meta_[set].tag[mshr.way] = address_tag(mshr.request.address);
        mshr.state = MshrState::kFinish1;
        break;
      }
      case MshrState::kFinish1:
        // GrantAck is a real TileLink E beat.  Holding Finish1 until the
        // registered E queue accepts it prevents the cold Broadcast tracker
        // from being released early under backpressure.  Transactions that
        // never received a Grant have no E beat and leave Finish1 directly.
        if (!mshr.grant_ack_valid ||
            (input.tile_e_ready && selected_finish_mshr() ==
                                       static_cast<int>(index))) {
          mshr.grant_ack_valid = false;
          mshr.state = MshrState::kFinish2;
        }
        break;
      case MshrState::kFinish2:
        // Payload registers persist in the RTL; only the FSM leaves.
        mshr.state = MshrState::kIdle;
        break;
    }
  }

  // Raw stage shadows: the RTL s1/s2 registers latch every LSU request
  // (cacheable or not) with no enable; kept purely for oracle export.
  // respq oracle: the four-deep response queue between the MSHR drain and
  // the LSU; enqueue at the drain handoff, dequeue one cycle later.
  std::uint8_t respq_enq_ = 0, respq_deq_ = 0;
  bool respq_maybe_full_ = false;
  std::uint8_t respq_count_ = 0;
  std::array<bool, 4> respq_valid_{};
  std::array<std::uint64_t, 4> respq_data_{};
  std::array<BoomUncachedCompletion, 4> respq_completion_{};
  std::array<boomcfg::br_mask_t, 4> respq_br_mask_{};
  std::array<bool, 4> respq_is_hella_{};
  std::uint64_t respq_head_prev_ = 0;
  // Array-port oracle: the SyncReadMem address registers hold between
  // enabled reads; the port views read SHADOW arrays that apply every
  // write two steps late (the model's pipeline effects lead the RTL's
  // write stage by two edges).
  std::array<std::array<std::array<std::uint64_t, kBeats>, kSets>, kWays>
      sh_data_{};
  // One record per set: a lookup reads every way's tag and coherence
  // bits of one set, so keep them in one line per set instead of one
  // line per way per array.
  struct SetMeta {
    std::array<std::uint32_t, kWays> tag{};
    std::array<bool, kWays> valid{};
    std::array<bool, kWays> dirty{};
    std::array<bool, kWays> writable{};
  };
  std::array<SetMeta, kSets> sh_meta_{};
  struct OracleWrite {
    std::uint8_t kind;  // 0=data 1=meta 2=clear
    std::uint8_t way, set, beat;
    std::uint64_t data;
    std::uint32_t tag;
    bool valid, dirty, writable;
    std::uint8_t hops = 0;  // extra steps in the delayed lane
  };
  std::array<std::array<OracleWrite, 8>, 3> ow_ring_{};
  std::array<int, 3> ow_n_{};
  int ow_phase_ = 0;
  void ow_data(std::size_t w, std::size_t st, std::size_t b,
               std::uint64_t d, int delay = 1) {
    // W=1 extern-tap emits no same-cycle write forwarding for this state
    // array.  The MPORT therefore keeps the pre-write word on a collision;
    // sh_data_ already contains exactly that word until the delayed write
    // below lands, so no artificial zero/blank override is needed.
    if (delay <= 0) {
      // The model has already exported this cycle's MPORT.  A write
      // committed here is therefore the array image for the next cycle and
      // can be installed directly without creating same-cycle forwarding.
      sh_data_[w][st][b] = d;
      return;
    }
    OracleWrite entry{0, (std::uint8_t)w, (std::uint8_t)st,
                      (std::uint8_t)b, d, 0, false, false, false, 0};
    if (delay >= 2) {
      // MSHR replay stores write the array later than the ordinary hit
      // path (their s0 enters at the replay pop; the write is at their s3).
      entry.hops = static_cast<std::uint8_t>(delay - 1);
      if (ow_pend_b_n_ < 4) ow_pend_b_[ow_pend_b_n_++] = entry;
      return;
    }
    if (ow_pend_a_n_ < 8) ow_pend_a_[ow_pend_a_n_++] = entry;
  }
  std::array<OracleWrite, 8> ow_pend_a_{};
  std::array<OracleWrite, 4> ow_pend_b_{};
  int ow_pend_a_n_ = 0, ow_pend_b_n_ = 0;
  void ow_meta(std::size_t w, std::size_t st, std::uint32_t tag, bool v,
               bool dt, bool wr, bool show_pre = true) {
    // L1MetadataArray is a synchronous-read SeqMem.  Save the word at the
    // write address before mutation so a simultaneous response for that same
    // address gets read-before-write data.  The response address itself is
    // tracked independently by oracle_meta_set_.
    if (show_pre) {
      const std::uint8_t pre_coh = !sh_meta_[st].valid[w] ? 0
                                   : sh_meta_[st].dirty[w] ? 3
                                   : sh_meta_[st].writable[w] ? 2 : 1;
      meta_pre_word_[w] = (std::uint32_t(pre_coh) << 20) |
                          (sh_meta_[st].tag[w] & 0xfffffu);
      meta_pre_set_[w] = static_cast<std::uint8_t>(st);
      meta_pre_valid_ |= static_cast<std::uint8_t>(1u << w);
    }
    sh_meta_[st].tag[w] = tag;
    sh_meta_[st].valid[w] = v;
    sh_meta_[st].dirty[w] = dt;
    sh_meta_[st].writable[w] = wr;
    meta_write_this_step_ = true;
  }
  std::array<std::uint32_t, kWays> meta_pre_word_{};
  std::array<std::uint8_t, kWays> meta_pre_set_{};
  std::uint8_t meta_pre_valid_ = 0;
  bool meta_write_this_step_ = false;
  BoomUncachedRequest bus_s1_{}, bus_s2_{};
  unsigned long long bus_step_n_ = 0;
  // One-step-delayed meta write: RTL fires these on the edge AFTER the
  // model's processing step (store-hit upgrades; refill final writes).
  struct OwMetaD1 { std::uint8_t w, st; std::uint32_t tag; bool v, dt, wr;
                    std::uint8_t delay; };
  void ow_meta_d1(std::size_t w, std::size_t st, std::uint32_t tag, bool v,
                  bool dt, bool wr, std::uint8_t delay = 0,
                  bool blank = true) {
    // delay = steps from now until the RTL write cycle; the pre-write-word
    // capture happens when the write applies (in ow_meta).
    (void)blank;
    if (delay == 0) {
      ow_meta(w, st, tag, v, dt, wr);
      return;
    }
    if (ow_meta_d1_n_ < static_cast<int>(kWays))
      ow_meta_d1_[ow_meta_d1_n_++] =
          OwMetaD1{(std::uint8_t)w, (std::uint8_t)st, tag, v, dt, wr,
                   static_cast<std::uint8_t>(delay - 1)};
  }
  void ow_meta_apply_d1() {
    int keep = 0;
    for (int i = 0; i < ow_meta_d1_n_; ++i) {
      OwMetaD1& o = ow_meta_d1_[i];
      if (o.delay == 0) {
        ow_meta(o.w, o.st, o.tag, o.v, o.dt, o.wr);
      } else if (o.delay == 1) {
        o.delay = 0;
        ow_meta_d1_[keep++] = o;
      } else {
        --o.delay;
        ow_meta_d1_[keep++] = o;
      }
    }
    ow_meta_d1_n_ = keep;
  }
  struct BlankM { std::uint8_t w, st; };
  BlankM meta_blank_[kWays]{};
  int meta_blank_n_ = 0;
  OwMetaD1 ow_meta_d1_[kWays]{};
  int ow_meta_d1_n_ = 0;
  void ow_apply_old() {
    // Entries pushed during the previous step land now (one-step delay);
    // the delayed lane moves up and lands one step later.
    for (int i = 0; i < ow_pend_a_n_; ++i) {
      const OracleWrite& o = ow_pend_a_[i];
      sh_data_[o.way][o.set][o.beat] = o.data;
    }
    ow_pend_a_n_ = 0;
    int keep = 0;
    for (int i = 0; i < ow_pend_b_n_; ++i) {
      OracleWrite& o = ow_pend_b_[i];
      if (o.hops <= 1) {
        if (ow_pend_a_n_ < 8) ow_pend_a_[ow_pend_a_n_++] = o;
      } else {
        --o.hops;
        ow_pend_b_[keep++] = o;
      }
    }
    ow_pend_b_n_ = keep;
  }
  std::array<std::size_t, kWays> oracle_data_set_{}, oracle_data_beat_{};
  std::array<std::size_t, kWays> oracle_meta_set_{};
  std::array<std::size_t, kWays> oracle_data_set_next_{},
      oracle_data_beat_next_{};
  std::size_t oracle_meta_set_next_ = 0;
  std::uint8_t raw_s0_read_ways_ = 0;
  // `oracle_data_*` is the functional 64-bit word selected by address bit 3.
  // The physical SRAM is one TileLink beat wide, so Large exposes two
  // separate 64-bit MPORT banks at a shared addr>>4 row.  Keep that physical
  // face separately; conflating it with the selected LSU word is invisible
  // on Small, where kWordsPerBeat == 1.
  std::array<std::uint64_t, kWays> oracle_data_now_{}, oracle_data_reg_{};
  std::array<std::array<std::uint64_t, kWordsPerBeat>, kWays>
      oracle_array_port_now_{}, oracle_array_port_reg_{};
  std::array<std::uint8_t, kWays> oracle_coh_now_{}, oracle_coh_reg_{};
  std::array<std::uint32_t, kWays> oracle_tag_now_{};
  std::uint8_t oracle_s1_type_ = 0, oracle_s2_type_ = 0;
  std::uint8_t s2_tag_match_way_ = 0;
  std::uint8_t s1_mshr_meta_read_way_en_ = 0;
  std::uint8_t s1_replay_way_en_ = 0;
  std::uint8_t s1_wb_way_en_ = 0;
  bool s3_valid_ = false, s4_valid_ = false, s5_valid_ = false;
  std::uint64_t s3_req_addr_ = 0, s4_req_addr_ = 0, s5_req_addr_ = 0;
  std::uint64_t s3_req_data_ = 0, s4_req_data_ = 0, s5_req_data_ = 0;
  std::uint8_t raw_s0_type_ = 0;
  bool raw_s0_reads_data_ = false;
  std::uint32_t sdq_val_ = 0;
  std::uint32_t sdq_alloc_view_ = 0;
  std::array<std::uint64_t, kSdqDepth> sdq_data_{};
  std::uint64_t sdq_data_read_ = 0;
  // POST-combinational oracle projection for the asynchronous SDQ replay
  // read.  These are captured before the RPQ/SDQ commit mutates its sources.
  std::uint64_t sdq_port_cycle_oracle_ = 0;
  std::uint8_t sdq_port_address_oracle_ = 0;
  std::uint8_t replay_arb_source_oracle_ = 1;
  bool replay_arb_m0_valid_oracle_ = false;
  BoomUncachedRequest raw_s0_{};
  BoomUncachedRequest raw_data_s0_{};
  BoomUncachedRequest raw_s1_{};
  int raw_s0_way_override_ = -1;   // meta passes observe the install way
  int raw_s1_way_override_ = -1;
  BoomUncachedRequest raw_s2_{};
  Lookup raw_s2_lookup_{};
  BoomUncachedRequest s1_{};
  BoomUncachedRequest s2_{};
  bool s1_replay_ = false;
  bool s2_replay_ = false;
  bool s1_send_response_ = false;
  bool s2_send_response_ = false;
  Lookup s1_lookup_{};
  Lookup s2_lookup_{};
  // WritebackUnit data reads use the same s0/s1/s2 cache pipeline as LSU and
  // probe metadata reads.  Keep their two registered occupancy bits because
  // io.lsu.ordered is defined over all s1/s2 traffic, not only LSU requests.
  bool writeback_s1_valid_ = false;
  std::uint8_t arb_a_state_ = 0, arb_e_state_ = 0, arb_c_state_ = 0, arb_c_beats_left_ = 0;
  // Pre-edge image of the three arbiters: the source vectors are the same
  // ones the cycle face offers, the winner is the lowest valid source, and a
  // multi-beat release holds the grant until its beats have drained.
  void update_arbiters(const SmallDcacheInputs& input) {
    unsigned a_valids = 0, e_valids = 0;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      if (mshrs_[i].state == MshrState::kAcquire) a_valids |= 1u << i;
      if (mshrs_[i].state == MshrState::kFinish1 && mshrs_[i].grant_ack_valid) e_valids |= 1u << i;
    }
    if (input.iomshr_mem_access) a_valids |= 1u << kMshrs;
    // Acquire and GrantAck are single-beat: those arbiters are always idle.
    arb_a_state_ = a_valids ? static_cast<std::uint8_t>(1u << __builtin_ctz(a_valids)) : 0;
    arb_e_state_ = e_valids ? static_cast<std::uint8_t>(1u << __builtin_ctz(e_valids)) : 0;
    const bool wb_valid = writeback_.state == WritebackState::kActive;
    const bool prober_valid = prober_.state == ProberState::kRelease;
    const unsigned c_valids = (wb_valid ? 1u : 0u) | (prober_valid ? 2u : 0u);
    const bool idle = arb_c_beats_left_ == 0;
    const unsigned winner = c_valids ? (1u << __builtin_ctz(c_valids)) : 0;
    const bool sink_valid = idle ? c_valids != 0 : (arb_c_state_ & c_valids) != 0;
    const bool fire = sink_valid && input.tile_c_ready;
    if (idle) {
      arb_c_state_ = static_cast<std::uint8_t>(winner);
      arb_c_beats_left_ = static_cast<std::uint8_t>(
          input.tile_c_ready && winner == 1u ? kTransferBeats - 1 : 0);
    } else {
      arb_c_beats_left_ = static_cast<std::uint8_t>(arb_c_beats_left_ - (fire ? 1u : 0u));
    }
  }
  std::uint8_t writeback_s1_beat_ = 0;
  // Oracle-only shadows of dcache.scala s1_valid/s2_valid and the
  // s1/s2 send_resp_or_nack registers; the s0 fall-through bus view.
  bool s1_valid_shadow_ = false, s2_valid_shadow_ = false;
  bool s1_send_shadow_ = false, s2_send_shadow_ = false;
  BoomUncachedRequest fallthrough_bus_{};
  bool writeback_s2_valid_ = false;
  std::uint8_t writeback_s2_beat_ = 0;
  std::array<std::uint64_t, kWordsPerBeat> architectural_wb_s1_{}, architectural_wb_s2_{};
  bool s2_wb_idx_match_ = false;
  bool s2_nack_hit_ = false;

  /** Live-oracle diagnostic access to the raw MSHR/writeback/prober state. */
  const Mshr& mshr_for_diagnostic(std::size_t index) const {
    return mshrs_[index];
  }
  const Writeback& writeback_for_diagnostic() const { return writeback_; }
  // Partition-cut lanes: the TileLink arbiters' one-hot "granted last cycle"
  // registers (rocket-chip Arbiter.scala:87-119) of the MSHR file's acquire
  // (4 MSHRs + IOMSHR) and finish (4 MSHRs) channels and the cache's release
  // channel (write-back unit, probe unit).
  std::uint8_t arbiter_a_state_oracle() const { return arb_a_state_; }
  std::uint8_t arbiter_e_state_oracle() const { return arb_e_state_; }
  std::uint8_t arbiter_c_state_oracle() const { return arb_c_state_; }
  bool s1_req_is_hella_oracle() const { return bus_s1_.is_hella; }
  const BoomUncachedCompletion& respq_completion_oracle(std::size_t slot) const { return respq_completion_[slot]; }
  const std::uint32_t& sdq_val_oracle() const { return sdq_val_; }
  const BoomUncachedRequest& raw_data_for_diagnostic() const {
    return raw_data_s0_;
  }
  std::uint8_t raw_data_way_mask_for_diagnostic() const {
    return raw_s0_read_ways_;
  }
  const std::uint64_t& oracle_data_port(std::size_t w) const {
    return oracle_array_port_now_[w][0];
  }
  const std::uint64_t& oracle_data_port_lane(std::size_t w,
                                             std::size_t lane) const {
    return oracle_array_port_now_[w][lane];
  }
  const std::uint64_t& oracle_data_reg(std::size_t w) const { return oracle_data_reg_[w]; }
  const std::uint64_t& oracle_data_reg_lane(std::size_t w,
                                            std::size_t lane) const {
    return oracle_array_port_reg_[w][lane];
  }
  std::uint16_t oracle_data_address(std::size_t w) const {
    return static_cast<std::uint16_t>(
        (oracle_data_set_[w] & (kSets - 1)) * kTransferBeats +
        (oracle_data_beat_[w] / kWordsPerBeat));
  }
  const std::uint32_t& oracle_tag_port(std::size_t w) const { return oracle_tag_now_[w]; }
  const std::uint8_t& oracle_coh_reg(std::size_t w) const { return oracle_coh_reg_[w]; }
  std::uint8_t oracle_s1_type() const { return oracle_s1_type_; }
  const std::uint8_t& oracle_s2_type() const { return oracle_s2_type_; }
  std::uint8_t s2_tag_match_way_now() const {
    return static_cast<std::uint8_t>(s2_tag_match_way_ & kAllWaysMask);
  }
  const std::uint64_t& s3_req_data_oracle() const { return s3_req_data_; }
  // Partition-cut lanes: the store pipeline's s3/s4/s5 request registers.
  bool s3_valid_oracle() const { return s3_valid_; }
  std::uint64_t s3_req_addr_oracle() const { return s3_req_addr_; }
  bool s4_valid_oracle() const { return s4_valid_; }
  std::uint64_t s4_req_addr_oracle() const { return s4_req_addr_; }
  bool s5_valid_oracle() const { return s5_valid_; }
  std::uint64_t s5_req_addr_oracle() const { return s5_req_addr_; }
  std::uint64_t s5_req_data_oracle() const { return s5_req_data_; }
  /** The s1/s2 request registers shift every cycle from the s0 bus mux,
    * whose idle default is the replay arbiter's (rpq head) bits. */
  const BoomUncachedRequest& bus_s1_oracle() const { return bus_s1_; }
  const BoomUncachedRequest& bus_s2_oracle() const { return bus_s2_; }
  const BoomUncachedRequest& functional_s1_for_diagnostic() const {
    return s1_;
  }
  const BoomUncachedRequest& functional_s2_for_diagnostic() const {
    return s2_;
  }
  const bool& s1_send_response_for_diagnostic() const { return s1_send_response_; }
  const bool& s2_send_response_for_diagnostic() const { return s2_send_response_; }
  const std::uint8_t& respq_enq_oracle() const { return respq_enq_; }
  const std::uint8_t& respq_deq_oracle() const { return respq_deq_; }
  const bool& respq_maybe_full_oracle() const { return respq_maybe_full_; }
  std::uint64_t respq_head_data_now() const {
    return respq_data_[respq_deq_ & 3u];
  }
  std::uint64_t respq_head_prev_oracle() const { return respq_head_prev_; }
  bool respq_is_hella_port_now() const {
    return respq_is_hella_[respq_deq_ & 3u];
  }
  std::uint64_t respq_br_mask_bank_oracle() const {
    std::uint64_t packed = 0;
    constexpr std::uint64_t kMask =
        (UINT64_C(1) << boomcfg::MAX_BR_COUNT) - UINT64_C(1);
    for (std::size_t lane = 0; lane < respq_br_mask_.size(); ++lane)
      packed |= (std::uint64_t(respq_br_mask_[lane]) & kMask)
                << (boomcfg::MAX_BR_COUNT *
                    (respq_br_mask_.size() - lane - 1u));
    return packed;
  }
  void oracle_io_push(std::uint64_t data) {
    snap_dirty_ = true;
    if (respq_enq_ == respq_deq_ && respq_maybe_full_) return;
    const std::size_t slot = respq_enq_ & 3u;
    respq_data_[slot] = data;
    respq_completion_[slot] = BoomUncachedCompletion{};
    respq_completion_[slot].valid = true;
    respq_completion_[slot].data = data;
    respq_br_mask_[slot] = 0;
    respq_is_hella_[slot] = false;
    respq_valid_[slot] = true;
    respq_enq_ = (respq_enq_ + 1u) & 3u;
    respq_maybe_full_ = true;
    ++respq_count_;
  }
  std::uint8_t respq_valids_now() const {
    std::uint8_t v = 0;
    for (std::uint8_t slot = 0; slot < 4; ++slot)
      if (respq_valid_[slot])
        v |= std::uint8_t(1u << (3u - slot));
    return v;
  }
  std::uint64_t sdq_read_oracle() const { return sdq_data_read_; }
  std::uint64_t sdq_port_cycle_oracle() const {
    return sdq_port_cycle_oracle_;
  }
  std::uint8_t sdq_port_address_oracle() const {
    return sdq_port_address_oracle_;
  }
  std::uint8_t replay_arb_source_oracle() const {
    return replay_arb_source_oracle_;
  }
  bool replay_arb_m0_valid_oracle() const {
    return replay_arb_m0_valid_oracle_;
  }
  // BranchKillableQueue stores only the uop branch mask in the separately
  // selected RPQ uops bank.  The physical bank order is slot 0 in the most
  // significant byte, matching the lowered RTL register image.
  std::uint64_t rpq_uop_br_mask_bank_now(std::size_t mshr_index,
                                          std::size_t bank) const {
    const Mshr& mshr = mshrs_[mshr_index];
    std::uint64_t packed = 0;
    constexpr std::size_t kSlotsPerWord = 64u / boomcfg::MAX_BR_COUNT;
    constexpr std::uint64_t kMask =
        (UINT64_C(1) << boomcfg::MAX_BR_COUNT) - UINT64_C(1);
    const std::size_t first = bank * kSlotsPerWord;
    const auto count=std::min(kSlotsPerWord,mshr.rpq.size()-first);
    for (std::size_t lane=0;lane<count;++lane)
      packed |= (std::uint64_t(mshr.rpq[first+lane].request.br_mask)&kMask)
                << (boomcfg::MAX_BR_COUNT*(count-lane-1));
    return packed;
  }
  bool rpq_is_hella_port_now(std::size_t mshr_index) const {
    const Mshr& mshr = mshrs_[mshr_index];
    return mshr.rpq[mshr.rpq_head].request.is_hella;
  }
  // BoomMSHRFile's lb read is an asynchronous Mem port.  Arbiter payloads
  // fall through to MSHR 1 when MSHR 0 has no valid read, even if neither
  // input is valid; the MPORT therefore exposes a real stale line-buffer word
  // on idle cycles.  This is an observability projection, not a functional
  // cache access.
  std::uint64_t line_buffer_port_now() const {
    const auto read_valid = [](const Mshr& mshr) {
      if (mshr.state == MshrState::kCommitLine) return true;
      if (mshr.state != MshrState::kDrainLoads || mshr.rpq_count == 0)
        return false;
      const RpqEntry& head = mshr.rpq[mshr.rpq_head];
      return head.valid && (head.request.uses_ldq || head.request.is_hella) &&
             !is_write_command(head.request.command) &&
             head.request.command != 6;  // M_XLR replays through the cache
    };
    std::size_t owner = kLastMshr;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      if (read_valid(mshrs_[i])) {
        owner = i;
        break;
      }
    }
    const Mshr& mshr = mshrs_[owner];
    const std::size_t offset =
        mshr.state == MshrState::kDrainLoads
            ? static_cast<std::size_t>(
                  (mshr.rpq[mshr.rpq_head].request.address >>
                   boomcfg::TILE_BEAT_SHIFT) &
                  (kTransferBeats - 1u))
            : static_cast<std::size_t>(mshr.commit_beat &
                                       (kTransferBeats - 1u));
    return mshr.line[offset * kWordsPerBeat];
  }
  // dcache.scala:603 s1_valid(0) / 633 s2_valid(0): any s0 winner, i.e. the
  // functional LSU/replay request, a writeback data read, a probe metadata
  // read or an MSHR metadata read.
  const bool& s1_valid_oracle() const { return s1_valid_shadow_; }
  const bool& s2_valid_oracle() const { return s2_valid_shadow_; }
  const bool& s2_send_shadow_oracle() const { return s2_send_shadow_; }
  // dcache.scala:717 RegNext(replacer.way).
  std::uint8_t s2_replacement_way_now() const {
    return static_cast<std::uint8_t>(s2_replacement_way_ & (kWays - 1u));
  }
  // mshrs.scala:694 mshr_alloc_idx.
  std::uint8_t mshr_alloc_index_now() const {
    return static_cast<std::uint8_t>(mshr_alloc_index_ & (kMshrs - 1u));
  }
  // mshrs.scala:754 sdq(replay_arb.io.out.bits.sdq_id): the SDQ port reads
  // the head slot of the replaying MSHR, else the arbiter's fall-through
  // input (MSHR 1).
  std::uint64_t sdq_port_oracle() const {
    std::size_t owner = kLastMshr;
    for (std::size_t i = 0; i < kMshrs; ++i) {
      if (mshrs_[i].state == MshrState::kReplay &&
          mshrs_[i].rpq_count != 0) {
        owner = i;
        break;
      }
    }
    const Mshr& src = mshrs_[owner];
    const std::size_t id = src.rpq_port_sdq;
    return id < sdq_data_.size() ? sdq_data_[id] : 0;
  }
  // Arbiter.scala:87 beatsLeft of the tl_out.c arbiter: beats still owed
  // after the ones already accepted for the current release burst.
  std::uint16_t writeback_beats_left_now() const {
    return (writeback_.state == WritebackState::kActive &&
            writeback_.release_beat != 0)
               ? static_cast<std::uint16_t>(kTransferBeats -
                                            writeback_.release_beat)
               : 0;
  }
  const std::uint8_t& mshr_new_coh_oracle(std::size_t i) const {
    return mshrs_[i].new_coh;
  }
  const std::uint8_t& mshr_old_meta_coh_oracle(std::size_t i) const {
    return mshrs_[i].old_meta_coh;
  }
  /** Post-step faces of the computed oracle views (`*_now()`), refreshed by
    * refresh_oracle_snapshots() once the cycle's dcache state is final, so the
    * sampler binds them as plain fields and its batches gate on these few
    * bytes instead of the whole component. */
  struct OracleSnapshot {
    std::uint8_t s2_tag_match_way = 0;
    std::uint64_t respq_head_data = 0;
    bool respq_is_hella_port = false;
    std::uint8_t respq_valids = 0;
    std::uint64_t rpq_uop_br_mask_bank[kMshrs][2] = {};
    bool rpq_is_hella_port[kMshrs] = {};
    std::uint64_t line_buffer_port = 0;
    std::uint8_t s2_replacement_way = 0;
    std::uint8_t mshr_alloc_index = 0;
    std::uint16_t writeback_beats_left = 0;
  };
  void refresh_oracle_snapshots() {
    snap_.s2_tag_match_way = s2_tag_match_way_now();
    // The queue/RPQ/line-buffer faces only move while an MSHR or the
    // response queue is active (or the IOMSHR pushed a response).
    if (snap_dirty_) {
      snap_dirty_ = false;
      snap_.respq_head_data = respq_head_data_now();
      snap_.respq_is_hella_port = respq_is_hella_port_now();
      snap_.respq_valids = respq_valids_now();
      for (std::size_t i = 0; i < kMshrs; ++i) {
        snap_.rpq_uop_br_mask_bank[i][0] = rpq_uop_br_mask_bank_now(i, 0);
        snap_.rpq_uop_br_mask_bank[i][1] = rpq_uop_br_mask_bank_now(i, 1);
        snap_.rpq_is_hella_port[i] = rpq_is_hella_port_now(i);
      }
      snap_.line_buffer_port = line_buffer_port_now();
    }
    snap_.s2_replacement_way = s2_replacement_way_now();
    snap_.mshr_alloc_index = mshr_alloc_index_now();
    snap_.writeback_beats_left = writeback_beats_left_now();
  }
  const std::uint8_t& s2_tag_match_way_oracle() const { return snap_.s2_tag_match_way; }
  const std::uint64_t& respq_head_data_oracle() const { return snap_.respq_head_data; }
  const bool& respq_is_hella_port_oracle() const { return snap_.respq_is_hella_port; }
  const std::uint8_t& respq_valids_oracle() const { return snap_.respq_valids; }
  const std::uint64_t& rpq_uop_br_mask_bank_oracle(std::size_t i, std::size_t bank) const {
    return snap_.rpq_uop_br_mask_bank[i][bank];
  }
  const bool& rpq_is_hella_port_oracle(std::size_t i) const { return snap_.rpq_is_hella_port[i]; }
  const std::uint64_t& line_buffer_port_oracle() const { return snap_.line_buffer_port; }
  const std::uint8_t& s2_replacement_way_oracle() const { return snap_.s2_replacement_way; }
  const std::uint8_t& mshr_alloc_index_oracle() const { return snap_.mshr_alloc_index; }
  const std::uint16_t& writeback_beats_left_oracle() const { return snap_.writeback_beats_left; }

  const bool& s2_nack_hit_oracle() const { return s2_nack_hit_; }
  const bool& s2_wb_idx_match_oracle() const { return s2_wb_idx_match_; }
  const std::uint64_t& s4_req_data_oracle() const { return s4_req_data_; }
  const std::uint64_t& writeback_buffer_lane_oracle(std::size_t beat,
                                                     std::size_t lane) const {
    return writeback_.line[beat * kWordsPerBeat + lane];
  }
  const BoomUncachedRequest& s1_for_diagnostic() const { return raw_s1_; }
  const BoomUncachedRequest& s2_for_diagnostic() const { return raw_s2_; }
  const Lookup& s2_lookup_for_diagnostic() const { return raw_s2_lookup_; }
  const Prober& prober_for_diagnostic() const { return prober_; }
  const std::uint16_t& lfsr_for_diagnostic() const { return replacement_lfsr_; }

 private:
  std::array<Mshr, kMshrs> mshrs_{};
  OracleSnapshot snap_{};
  bool snap_dirty_ = true;
  mutable SmallDcacheOutputs eval_cache_{};
  mutable unsigned long long eval_gen_ = 0;
  mutable unsigned long long eval_cache_gen_ = ~0ull;
  mutable boomcfg::br_mask_t eval_cache_kill_ = 0;
  mutable bool eval_cache_exc_ = false;
  Writeback writeback_{};
  Prober prober_{};
  std::uint8_t mshr_head_ = 0;
  std::uint8_t mshr_alloc_index_ = 0;
  std::uint16_t replacement_lfsr_ = 1;
  // Zero image before the first edge: RegNext(replacer.way) is 0 at cycle 1
  // even though the LFSR resets to 1.
  std::uint8_t s2_replacement_way_ = 0;
  unsigned long long dc_steps_ = 0;  // step() calls, including reset steps
  std::array<bool, 3> replay_store_write_pipe_{};
  std::size_t metadata_reset_cycles_ = kSets;

  std::array<SetMeta, kSets> meta_{};
  std::array<std::array<std::array<std::uint64_t, kBeats>, kSets>, kWays>
      data_{};
};

}  // namespace chisa::boom_system::components
