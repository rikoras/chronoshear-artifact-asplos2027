// Rocket blocking data cache (rocket/DCache.scala) for the locked
// DefaultConfig: 16 KiB 4-way, 64-byte lines, 64-bit rows, no ECC, random
// replacement, one uncached request in flight, atomics executed in the cache,
// TileLink-C coherence client (Acquire/Release/Probe) below a broadcast hub,
// with the data TLB.
#pragma once
#include <cstdint>
#include <cstring>

#include "tlb.h"

namespace chisa::rocket_model {

enum : uint8_t {
  DC_S_READY = 0, DC_S_VOLUNTARY_WRITEBACK = 1, DC_S_PROBE_REP_DIRTY = 2, DC_S_PROBE_REP_CLEAN = 3,
  DC_S_PROBE_RETRY = 4, DC_S_PROBE_REP_MISS = 5, DC_S_VOLUNTARY_WRITE_META = 6, DC_S_PROBE_WRITE_META = 7,
  DC_S_DUMMY = 8, DC_S_VOLUNTARY_RELEASE = 9
};

struct HellaReq {
  uint64_t addr;   // 40 bits
  uint8_t tag;     // 7 bits
  uint8_t cmd;     // 5 bits
  uint8_t size;    // 2 bits
  bool signed_;
  uint8_t dprv;
  bool phys, no_alloc, no_xcpt;
  uint64_t data = 0;
  uint8_t mask = 0;
};

struct TlA {
  bool valid;
  uint8_t opcode, param, size, source;
  uint32_t address;
  uint8_t mask;
  uint64_t data;
  bool corrupt;
};
struct TlC {
  bool valid;
  uint8_t opcode, param, size, source;
  uint32_t address;
  uint64_t data;
  bool corrupt;
};

struct DcacheIn {
  bool req_valid;
  HellaReq req;
  bool s1_kill;
  uint64_t s1_data;
  uint8_t s1_mask;
  bool s2_kill;
  // TileLink
  bool a_ready;
  bool b_valid;
  uint32_t b_address;
  uint8_t b_param, b_size, b_source;
  bool c_ready;
  bool d_valid;
  uint8_t d_opcode, d_param, d_size, d_source, d_sink;
  bool d_denied, d_corrupt;
  uint64_t d_data;
  bool e_ready;
  // TLB side
  PtwToTlb ptw;
  uint8_t dprv;
  bool debug, sum, mxr;
  uint8_t ptbr_mode;
  const PmpSet* pmp;
  bool reset;
  // Complete ExtModule joins observe invalid payloads too. The standalone
  // component API retains its activity-gated path unless explicitly selected.
  bool exact_seam = false;
};

struct DcacheWires {
  // cpu outputs
  bool req_ready;
  bool s2_nack, s2_nack_cause_raw, s2_uncached;
  uint32_t s2_paddr;
  bool resp_valid;
  uint64_t resp_addr;
  uint8_t resp_tag, resp_cmd, resp_size;
  bool resp_signed, resp_replay, resp_has_data;
  uint64_t resp_data, resp_data_word_bypass, resp_data_raw, resp_store_data;
  bool replay_next;
  bool xcpt_ma_ld, xcpt_ma_st, xcpt_pf_ld, xcpt_pf_st, xcpt_ae_ld, xcpt_ae_st;
  bool ordered;
  bool perf_grant, perf_release, perf_acquire;
  // TileLink outputs
  TlA a;
  bool b_ready;
  TlC c;
  bool d_ready;
  bool e_valid;
  uint8_t e_sink;
  // ptw
  bool ptw_req_valid;
  uint32_t ptw_req_addr;
  // decisions for commit
  bool idle;
  TlbIn tlb_in;
  TlbWires tlb;
  bool tlb_used;
  bool s0_clk_en;
  HellaReq s0_req;
  bool s1_nack, s1_valid_not_nacked;
  uint32_t s1_paddr;
  uint8_t s1_hit_way, s1_hit_state;
  bool s1_meta_clk_en;
  uint8_t s1_mask;
  bool s1_write, s1_sfence, s1_raw_hazard, s1_xcpt_valid, s1_did_read_next;
  // data array port
  bool data_sram_valid, data_write;
  uint16_t data_row;
  uint64_t data_wdata;
  uint8_t data_eccmask, data_way_en;
  bool data_in2_fire;
  // meta array port
  bool meta_valid, meta_write;
  uint8_t meta_idx, meta_way_en;
  uint32_t meta_data;
  // s2
  bool s2_valid_masked, s2_valid_hit, s2_valid_cached_miss, s2_store_valid, s2_victimize;
  bool s2_hit, s2_lr, s2_uncached_plain;
  uint8_t s2_victim_or_hit_way;
  uint32_t s2_victim_tag;
  bool pstore_drain, advance_pstore1;
  uint64_t pstore1_storegen_data;
  // TileLink internals
  bool a_fire, b_fire, c_fire, d_fire;
  bool d_last, c_first;
  bool grantIsCached, grantIsUncached, grantIsUncachedData, grantIsVoluntary;
  bool s1_release_data_valid_next, s2_release_data_valid_next;
  uint8_t s1_data_way_sel;
  bool s2_data_en;
  uint64_t uncachedResp_addr;
  uint8_t uncachedResp_size, uncachedResp_tag;
  bool uncachedResp_signed;
  bool blockUncachedGrant_next;
  uint8_t next_release_state;
  bool release_state_set, s1_probe_set;
  bool perf_tlb_miss, perf_blocked, perf_store_buffer_empty_after_load, perf_store_buffer_empty_after_store;
  bool perf_can_accept_store_then_load, perf_can_accept_store_then_rmw, perf_can_accept_load_then_load;
};

class Dcache {
 public:
  void set_architectural_mode(bool enabled) { architectural_mode_ = enabled; }
  bool architectural_mode() const { return architectural_mode_; }
  void evaluate(const DcacheIn& in, DcacheWires& w) const;
  void commit(const DcacheIn& in, const DcacheWires& w);
  template <class S> void export_image(S& s) const;

  Tlb tlb{false, 3};
  // registers (names follow DCache.scala)
  bool clock_en_reg_ = false;
  bool s1_valid_ = false, s1_probe_ = false;
  uint32_t probe_bits_address_ = 0;
  uint8_t probe_bits_param_ = 0, probe_bits_size_ = 0, probe_bits_source_ = 0;
  HellaReq s1_req_ = {};
  uint64_t s1_tlb_req_vaddr_ = 0;
  bool s1_tlb_req_passthrough_ = false;
  uint8_t s1_tlb_req_size_ = 0, s1_tlb_req_cmd_ = 0;
  bool s1_flush_valid_ = false;
  bool cached_grant_wait_ = false;
  bool resetting_ = false, reset_next_ = false;
  uint8_t flushCounter_ = 192;
  bool release_ack_wait_ = false;
  uint32_t release_ack_addr_ = 0;
  uint8_t release_state_ = DC_S_READY;
  uint8_t refill_way_ = 0;
  bool uncachedInFlight_ = false;
  HellaReq uncachedReq_ = {};
  bool s2_valid_ = false, s2_probe_ = false, s2_not_nacked_in_s1_ = false;
  HellaReq s2_req_ = {};
  bool s2_tlb_pf_ld_ = false, s2_tlb_pf_st_ = false, s2_tlb_ae_ld_ = false, s2_tlb_ae_st_ = false;
  bool s2_tlb_ma_ld_ = false, s2_tlb_ma_st_ = false;
  bool s2_pma_cacheable_ = false, s2_pma_must_alloc_ = false;
  uint64_t s2_uncached_resp_addr_ = 0;
  uint64_t s2_vaddr_r_ = 0;
  bool s2_flush_valid_pre_tag_ecc_ = false;
  uint32_t s2_meta_corrected_[4] = {};
  uint64_t s2_data_ = 0;
  uint8_t s2_probe_way_ = 0, s2_probe_state_ = 0;
  uint8_t s2_hit_way_ = 0, s2_hit_state_ = 0;
  uint8_t s2_victim_way_r_ = 0;
  uint8_t lrscCount_ = 0;
  uint64_t lrscAddr_ = 0;
  uint8_t pstore1_cmd_ = 0;
  uint64_t pstore1_addr_ = 0, pstore1_data_ = 0;
  uint8_t pstore1_way_ = 0, pstore1_mask_ = 0;
  bool pstore1_rmw_ = false;
  bool pstore2_valid_ = false, pstore1_held_ = false;
  uint64_t pstore2_addr_ = 0;
  uint8_t pstore2_way_ = 0;
  uint64_t pstore2_storegen_data_ = 0;
  uint8_t pstore2_storegen_mask_ = 0;
  uint16_t d_counter_ = 0, c_counter_ = 0;
  bool grantInProgress_ = false;
  uint8_t blockProbeAfterGrantCount_ = 0;
  bool blockUncachedGrant_ = false;
  bool s1_release_data_valid_ = false, s2_release_data_valid_ = false;
  uint64_t s2_uncached_data_word_ = 0;
  bool doUncachedResp_ = false;
  bool s2_xcpt_reg_ = false;
  bool pstore_drain_on_miss_reg_ = false;
  bool s2_nack_cause_raw_reg_ = false;
  bool s1_did_read_ = false;
  uint16_t lfsr_ = 1;
  uint8_t tag_rd_addr_ = 0;
  uint16_t data_rd_addr_ = 0;
  uint8_t perf_refill_count_ = 0;
  uint32_t tag_[64][4] = {};        // [set][way] {state[21:20], tag[19:0]}: one 16-byte row per set
  uint8_t data_[4][64][64] = {};    // [way][set][byte]: one contiguous line

 private:
  bool architectural_mode_ = false;
};

template <class S>
void Dcache::export_image(S& s) const {
  if (architectural_mode_) return;
  tlb.export_image(s);
  s.pstore1_data = pstore1_data_;
  s.pstore2_addr = pstore2_addr_;
  s.s1_req_addr = s1_req_.addr;
  s.s2_data = s2_data_;
  s.s2_req_addr = s2_req_.addr;
  s.probe_bits_address = probe_bits_address_;
  s.release_ack_addr = release_ack_addr_;
  s.s2_meta_corrected_r = s2_meta_corrected_[0];
  s.s2_meta_corrected_r_1 = s2_meta_corrected_[1];
  s.s2_meta_corrected_r_2 = s2_meta_corrected_[2];
  s.s2_meta_corrected_r_3 = s2_meta_corrected_[3];
  s.counter = d_counter_;
  s.counter_1 = c_counter_;
  s.blockUncachedGrant = blockUncachedGrant_;
  s.cached_grant_wait = cached_grant_wait_;
  s.doUncachedResp = doUncachedResp_;
  s.io_cpu_s2_xcpt_REG = s2_xcpt_reg_;
  s.lfsr_prng_state_0 = lfsr_ & 1;
  s.probe_bits_param = probe_bits_param_;
  s.probe_bits_size = probe_bits_size_;
  s.probe_bits_source = probe_bits_source_;
  s.pstore1_mask = pstore1_mask_;
  s.pstore1_rmw_r = pstore1_rmw_;
  s.pstore2_valid = pstore2_valid_;
  s.release_ack_wait = release_ack_wait_;
  s.release_state = release_state_;
  s.resetting = resetting_;
  s.s1_probe = s1_probe_;
  s.s1_req_cmd = s1_req_.cmd;
  s.s1_req_size = s1_req_.size;
  s.s1_tlb_req_passthrough = s1_tlb_req_passthrough_;
  s.s1_tlb_req_size = s1_tlb_req_size_;
  s.s1_tlb_req_vaddr = s1_tlb_req_vaddr_;
  s.s1_valid = s1_valid_;
  s.s2_hit_state_state = s2_hit_state_;
  s.s2_hit_way = s2_hit_way_;
  s.s2_not_nacked_in_s1 = s2_not_nacked_in_s1_;
  s.s2_pma_cacheable = s2_pma_cacheable_;
  s.s2_probe_state_state = s2_probe_state_;
  s.s2_probe_way = s2_probe_way_;
  s.s2_release_data_valid = s2_release_data_valid_;
  s.s2_req_cmd = s2_req_.cmd;
  s.s2_req_signed = s2_req_.signed_;
  s.s2_req_size = s2_req_.size;
  s.s2_req_tag = s2_req_.tag;
  s.s2_tlb_xcpt_ae_ld = s2_tlb_ae_ld_;
  s.s2_tlb_xcpt_ae_st = s2_tlb_ae_st_;
  s.s2_tlb_xcpt_ma_ld = s2_tlb_ma_ld_;
  s.s2_tlb_xcpt_ma_st = s2_tlb_ma_st_;
  s.s2_tlb_xcpt_pf_ld = s2_tlb_pf_ld_;
  s.s2_tlb_xcpt_pf_st = s2_tlb_pf_st_;
  s.s2_valid = s2_valid_;
  s.s2_victim_way_r = s2_victim_way_r_;
  s.uncachedInFlight_0 = uncachedInFlight_;
}

}  // namespace chisa::rocket_model
