// Rocket instruction fetch front end (rocket/Frontend.scala, ICache.scala,
// BTB.scala) for the locked DefaultConfig: 16 KiB 4-way ICache with 64-byte
// lines and 64-bit refill beats, 2-cycle latency, no ECC/ITIM/prefetch;
// 28-entry BTB with 6 pages, 512-entry BHT (1-bit counters, 8-bit history,
// 3 hashed bits), 6-entry RAS; fetch width 2 parcels of 16 bits; a 5-entry
// flow-through fetch queue; the instruction TLB.
#pragma once
#include <cstdint>

#include "tlb.h"

namespace chisa::rocket_model {

constexpr uint64_t kVaMask40 = (UINT64_C(1) << 40) - 1;
constexpr uint64_t kVaMask39 = (UINT64_C(1) << 39) - 1;

// ---------------------------------------------------------------- ICache
struct ICacheIn {
  bool req_valid;
  uint64_t req_addr;   // 39 bits
  uint32_t s1_paddr;
  bool s1_kill, s2_kill, invalidate;
  bool a_ready;
  bool d_valid, d_corrupt;
  uint8_t d_opcode, d_size;
  uint64_t d_data;
  bool reset;
  bool architectural_mode = false;
};

struct ICacheWires {
  bool req_ready;
  bool resp_valid, resp_ae;
  uint32_t resp_data;
  bool a_valid;
  uint32_t a_address;
  // internals
  bool refill_one_beat, refill_done, d_done;
  uint16_t refill_cnt;
  bool s2_miss, s1_can_request_refill;
};

class ICache {
 public:
  void reset();
  void evaluate(const ICacheIn& in, ICacheWires& w) const;
  void commit(const ICacheIn& in, const ICacheWires& w);
  unsigned repl_way() const { return lfsr_ & 3; }

  bool s1_valid_ = false, s2_valid_ = false, s2_hit_ = false;
  bool invalidated_ = false, refill_valid_ = false;
  bool s2_request_refill_reg_ = false;
  uint32_t refill_paddr_ = 0;
  uint16_t counter_ = 0;          // TileLink D beat counter (9 bits)
  bool accrued_refill_error_ = false;
  uint64_t vb_[4] = {};           // valid bits, vb_[way] bit set
  uint8_t s2_tag_hit_ = 0;
  uint32_t s2_dout_[4] = {};
  bool s2_tl_error_ = false;
  uint16_t lfsr_ = 1;
  uint8_t tag_rd_addr_ = 0;       // SyncReadMem address pipe registers
  uint16_t data_rd_addr_[2] = {};
  uint32_t tag_[64][4] = {};      // [set][way] {tl_error, tag[19:0]}: one 16-byte row per set
  uint32_t data_[512][2][4] = {}; // [row][word][way]: the four ways of a word are 16 contiguous bytes
};

// ---------------------------------------------------------------- BTB
struct BtbUpdate {
  bool valid;
  uint8_t entry;     // 5 bits
  uint64_t pc;       // 39 bits
  uint64_t br_pc;    // 39 bits
  bool is_valid;
  uint8_t cfi_type;
};
struct BhtUpdate {
  bool valid;
  uint8_t history;
  uint64_t pc;
  bool branch, taken, mispredict;
};
struct BtbIn {
  uint64_t req_addr;   // s1_pc, 39 bits
  BtbUpdate btb_update;
  BhtUpdate bht_update;
  bool bht_advance_valid, bht_advance_taken;
  bool ras_update_valid;
  uint8_t ras_update_cfi_type;
  uint64_t ras_update_return_addr;  // 39 bits
  bool flush;
  bool reset;
};
struct BtbWires {
  bool resp_valid, resp_taken;
  uint64_t resp_target;   // 39 bits
  uint8_t resp_entry;     // 5 bits
  uint8_t resp_bridx;     // 1 bit
  uint8_t bht_history;
  uint8_t bht_value;
  bool ras_head_valid;
  uint64_t ras_head;      // 39 bits
  // internals
  uint32_t idx_hit;       // 28 bits
  uint8_t page_hit;       // 6 bits
  uint8_t resp_cfi_type, resp_mask;
};

class Btb {
 public:
  void reset();
  void evaluate(const BtbIn& in, BtbWires& w) const;
  void commit(const BtbIn& in, const BtbWires& w);
  void commit_side(const BtbIn& in, const BtbWires& w);

  uint16_t idxs_[28] = {};      // 13 bits
  uint32_t idx_map_[8192];      // entries whose idxs_ equals the index (validity applied at lookup)
  Btb() { for (uint32_t& m : idx_map_) m = 0; idx_map_[0] = (1u << 28) - 1; }
  uint8_t idx_pages_[28] = {};  // 3 bits
  uint16_t tgts_[28] = {};      // 13 bits
  uint8_t tgt_pages_[28] = {};  // 3 bits
  uint32_t pages_[6] = {};      // 25 bits
  uint8_t page_valid_ = 0;      // 6 bits
  uint32_t is_valid_ = 0;       // 28 bits
  uint8_t cfi_type_[28] = {};   // 2 bits
  uint8_t br_idx_[28] = {};     // 1 bit
  bool r_update_valid_ = false;
  BtbUpdate r_update_ = {};
  uint8_t next_page_repl_ = 0;  // 3 bits
  uint32_t plru_ = 0;           // 27 bits
  bool r_resp_valid_ = false, r_resp_taken_ = false;
  uint8_t r_resp_entry_ = 0;
  // BHT
  uint8_t history_ = 0;
  uint16_t reset_waddr_ = 0;    // 10 bits
  uint8_t table_[512] = {};     // 1 bit each
  // RAS
  uint8_t ras_count_ = 0, ras_pos_ = 0;
  uint64_t ras_stack_[6] = {};  // 39 bits
};

// ---------------------------------------------------------------- fetch queue
struct FetchBundle {
  bool btb_taken;
  uint8_t btb_bridx;    // 1 bit
  uint8_t btb_entry;    // 5 bits
  uint8_t bht_history;
  uint8_t bht_value;
  uint64_t pc;          // 40 bits
  uint32_t data;
  bool replay;
  bool pf_inst, ae_inst;
  uint8_t btb_cfi_type = 0, btb_mask = 0, mask = 0;
  uint64_t btb_target = 0;
};

// ---------------------------------------------------------------- Frontend
struct FrontendIn {
  bool req_valid;
  uint64_t req_pc;       // 40 bits
  bool req_speculative;
  bool sfence_valid, sfence_rs1, sfence_rs2;
  uint64_t sfence_addr;
  bool resp_ready;
  BtbUpdate btb_update;
  BhtUpdate bht_update;
  bool flush_icache;
  uint32_t chicken;      // custom CSR 0 (bit 3 = disableSpeculativeICacheRefill)
  bool a_ready;
  bool d_valid, d_corrupt;
  uint8_t d_opcode, d_size;
  uint64_t d_data;
  PtwToTlb ptw;
  uint8_t prv;
  bool debug;
  uint8_t ptbr_mode;
  const PmpSet* pmp;
  bool reset;
  uint32_t reset_vector = 0x10040;
  bool might_request = false;
  bool exact_seam = false;
};

struct FrontendWires {
  bool idle = false;
  // outputs
  uint64_t npc;          // 40 bits
  bool resp_valid;
  FetchBundle resp;
  bool a_valid;
  uint32_t a_address;
  bool ptw_req_valid, ptw_req_bits_valid;
  uint32_t ptw_req_addr;
  // internals
  TlbWires tlb;
  ICacheWires icache;
  BtbWires btb;
  ICacheIn icache_in;
  BtbIn btb_in;
  TlbIn tlb_in;
  bool s0_valid, s2_replay, s2_redirect, enq_fire, s2_btb_taken;
  bool s1_speculative_next;   // value written into s1_speculative
  bool taken;                 // decode-stage taken
  bool wrong_path_set;        // scanInsns sets wrong_path
  bool partial_set;           // idx 1 leaves a partial instruction
  uint16_t partial_bits;
  FetchBundle enq;            // fq.io.enq.bits
  bool enq_valid;
  uint64_t predicted_npc;
  bool predicted_taken;
};

class Frontend {
 public:
  void set_architectural_mode(bool enabled) { architectural_mode_ = enabled; }
  bool architectural_mode() const { return architectural_mode_; }
  void reset(uint64_t reset_vector);
  void evaluate(const FrontendIn& in, FrontendWires& w) const;
  void commit(const FrontendIn& in, const FrontendWires& w);
  template <class S> void export_image(S& s) const;

  Tlb tlb{true, 2};
  ICache icache;
  Btb btb;
  // Physical ShiftQueue slots. Valid bits are contiguous, but invalid slots
  // retain their RTL values too: elts(0) is exported even when the queue is empty.
  FetchBundle fq_[5] = {};
  uint8_t fq_count_ = 0;
  uint8_t fq_valid() const { return static_cast<uint8_t>((1u << fq_count_) - 1); }
  const FetchBundle& fq_elt(unsigned i) const { return fq_[i]; }
  // pipeline registers
  bool s1_valid_ = false;
  uint64_t s1_pc_ = 0;
  bool s1_speculative_ = false;
  bool s2_valid_ = false;
  uint64_t s2_pc_ = 0;
  bool s2_btb_resp_valid_ = false;
  bool s2_btb_taken_bit_ = false;   // s2_btb_resp_bits.taken
  uint8_t s2_btb_bridx_ = 0, s2_btb_entry_ = 0, s2_bht_history_ = 0, s2_bht_value_ = 0;
  bool s2_tlb_miss_ = false, s2_tlb_pf_inst_ = false, s2_tlb_ae_inst_ = false, s2_tlb_cacheable_ = false;
  bool s2_speculative_ = false;
  bool s2_partial_insn_valid_ = false;
  uint16_t s2_partial_insn_ = 0;
  bool wrong_path_ = false;
  bool s2_replay_reg_ = true;
  bool fq_enq_valid_reg_ = false;
  // These unreset payloads are observable on the complete module seam even
  // though the conservative register-oracle set does not select them.
  bool clock_en_reg_ = false;
  uint8_t s2_btb_cfi_type_ = 0, s2_btb_mask_ = 0;
  uint64_t s2_btb_target_ = 0;

 private:
  bool architectural_mode_ = false;
};

template <class S>
void Frontend::export_image(S& s) const {
  if (architectural_mode_) return;
  tlb.export_image(s);
  s.tlb_state = tlb.state_;
  s.btb_r_btb_updatePipe_bits_pc = btb.r_update_.pc;
  s.btb_r_btb_updatePipe_bits_cfiType = btb.r_update_.cfi_type;
  s.btb_r_btb_updatePipe_bits_prediction_entry = btb.r_update_.entry;
  s.btb_r_btb_updatePipe_valid = btb.r_update_valid_;
  s.btb_isValid = btb.is_valid_;
  s.btb_pageValid = btb.page_valid_;
  s.btb_pages_0 = btb.pages_[0]; s.btb_pages_1 = btb.pages_[1]; s.btb_pages_2 = btb.pages_[2];
  s.btb_pages_3 = btb.pages_[3]; s.btb_pages_4 = btb.pages_[4]; s.btb_pages_5 = btb.pages_[5];
  s.btb_state_reg = btb.plru_;
  {
    const FetchBundle& h = fq_[0];
    s.fq_elts_0_pc = h.pc;
    s.fq_elts_0_data = h.data;
    s.fq_elts_0_btb_bridx = h.btb_bridx;
    s.fq_elts_0_btb_taken = h.btb_taken;
    s.fq_elts_0_replay = h.replay;
    const uint8_t v = fq_valid();
    s.fq_valid_0 = v & 1; s.fq_valid_1 = (v >> 1) & 1; s.fq_valid_2 = (v >> 2) & 1; s.fq_valid_3 = (v >> 3) & 1; s.fq_valid_4 = (v >> 4) & 1;
  }
  s.fq_io_enq_valid_REG = fq_enq_valid_reg_;
  s.icache_refill_paddr = icache.refill_paddr_;
  s.icache_repl_way_v0_prng_state_0 = icache.lfsr_ & 1;
  s.icache_s2_dout_0 = icache.s2_dout_[0]; s.icache_s2_dout_1 = icache.s2_dout_[1];
  s.icache_s2_dout_2 = icache.s2_dout_[2]; s.icache_s2_dout_3 = icache.s2_dout_[3];
  s.icache_s2_hit = icache.s2_hit_;
  s.icache_s2_request_refill_REG = icache.s2_request_refill_reg_;
  s.icache_s2_tag_hit_0 = (icache.s2_tag_hit_ >> 0) & 1; s.icache_s2_tag_hit_1 = (icache.s2_tag_hit_ >> 1) & 1;
  s.icache_s2_tag_hit_2 = (icache.s2_tag_hit_ >> 2) & 1; s.icache_s2_tag_hit_3 = (icache.s2_tag_hit_ >> 3) & 1;
  s.icache_s2_tl_error = icache.s2_tl_error_;
  s.icache_s2_valid = icache.s2_valid_;
  s.s1_pc = s1_pc_;
  s.s2_btb_resp_bits_bht_history = s2_bht_history_;
  s.s2_btb_resp_bits_bht_value = s2_bht_value_;
  s.s2_btb_resp_bits_bridx = s2_btb_bridx_;
  s.s2_btb_resp_bits_taken = s2_btb_taken_bit_;
  s.s2_btb_resp_valid = s2_btb_resp_valid_;
  s.s2_partial_insn = s2_partial_insn_;
  s.s2_partial_insn_valid = s2_partial_insn_valid_;
  s.s2_pc = s2_pc_;
  s.s2_speculative = s2_speculative_;
  s.s2_tlb_resp_ae_inst = s2_tlb_ae_inst_;
  s.s2_tlb_resp_cacheable = s2_tlb_cacheable_;
  s.s2_tlb_resp_miss = s2_tlb_miss_;
  s.s2_tlb_resp_pf_inst = s2_tlb_pf_inst_;
  s.s2_valid = s2_valid_;
  s.wrong_path = wrong_path_;
}

}  // namespace chisa::rocket_model
