#include "frontend.h"

#include <cstring>

#include "core.h"   // decode_imm
#include "isa.h"
#include "plru.h"

namespace chisa::rocket_model {

// ================================================================ ICache
namespace {
constexpr uint8_t kTlAccessAckData = 1;
inline bool is_rvc(uint32_t bits) { return (bits & 3) != 3; }
}  // namespace

void ICache::reset() { *this = ICache{}; }

void ICache::evaluate(const ICacheIn& in, ICacheWires& w) const {
  const bool has_data = in.d_opcode == kTlAccessAckData;
  const bool d_fire = in.d_valid;  // d.ready is constant true
  w.refill_one_beat = d_fire && has_data;
  // TileLink edge.count on channel D.
  const uint16_t beats1 = has_data ? static_cast<uint16_t>(((1u << in.d_size) - 1) >> 3) : 0;
  const bool first = counter_ == 0;
  const bool last = counter_ == 1 || beats1 == 0;
  w.d_done = last && d_fire;
  const uint16_t counter1 = static_cast<uint16_t>((counter_ - 1) & 0x1ff);
  w.refill_cnt = static_cast<uint16_t>(beats1 & ~counter1 & 0x1ff);
  (void)first;
  w.refill_done = w.refill_one_beat && w.d_done;
  w.req_ready = !w.refill_one_beat;

  w.s2_miss = s2_valid_ && !s2_hit_ && !in.s2_kill;
  w.s1_can_request_refill = !(w.s2_miss || refill_valid_);
  const bool s2_request_refill = w.s2_miss && s2_request_refill_reg_;
  w.a_valid = s2_request_refill;
  w.a_address = refill_paddr_ & ~UINT32_C(63);

  uint32_t data = 0;
  if (!in.architectural_mode || s2_valid_)
    for (unsigned way = 0; way < 4; ++way) if ((s2_tag_hit_ >> way) & 1) data |= s2_dout_[way];
  w.resp_data = data;
  w.resp_ae = s2_tl_error_;
  w.resp_valid = s2_valid_ && s2_hit_;
}

void ICache::commit(const ICacheIn& in, const ICacheWires& w) {
  const bool s0_valid = in.req_valid && w.req_ready;
  const uint64_t s0_vaddr = in.req_addr & kVaMask39;
  const unsigned repl = repl_way();
  const bool refill_fire = w.a_valid && in.a_ready;
  const uint32_t refill_idx = (refill_paddr_ >> 6) & 63;
  const uint32_t refill_tag = refill_paddr_ >> 12;
  const bool refill_error = in.d_corrupt || (w.refill_cnt > 0 && accrued_refill_error_);

  // ---- stage 1 (uses this cycle's s1_paddr) ----
  const uint32_t s1_idx = (in.s1_paddr >> 6) & 63;
  const uint32_t s1_tag = in.s1_paddr >> 12;
  uint8_t s1_tag_hit = 0;
  bool s1_tl_error = false;
  if (!in.architectural_mode || s1_valid_) {
    const uint32_t* row = tag_[tag_rd_addr_];
    for (unsigned way = 0; way < 4; ++way) {
      const uint32_t enc = row[way];
      if (((vb_[way] >> s1_idx) & 1) && (enc & 0xFFFFF) == s1_tag) {
        s1_tag_hit |= 1u << way;
        if ((enc >> 20) & 1) s1_tl_error = true;
      }
    }
  }
  const bool s1_hit = s1_tag_hit != 0;
  const unsigned s1_word = (in.s1_paddr >> 2) & 1;
  uint32_t s1_dout[4];
  if (!in.architectural_mode || s1_valid_)
    std::memcpy(s1_dout, data_[data_rd_addr_[s1_word]][s1_word], sizeof s1_dout);  // pre-edge read data

  // ---- refill bookkeeping and array writes ----
  if (w.refill_done) {
    tag_[refill_idx][repl] = (static_cast<uint32_t>(refill_error) << 20) | (refill_tag & 0xFFFFF);
  }
  if (w.refill_one_beat) {
    accrued_refill_error_ = refill_error;
    const uint64_t bit = UINT64_C(1) << refill_idx;
    if (w.refill_done && !invalidated_) vb_[repl] |= bit; else vb_[repl] &= ~bit;
  }
  bool invalidated_next = invalidated_;
  if (in.invalidate) { for (auto& v : vb_) v = 0; invalidated_next = true; }
  if (w.refill_one_beat) {
    if (!invalidated_) {
      const uint32_t mem_idx = (refill_idx << 3) | w.refill_cnt;
      data_[mem_idx][0][repl] = static_cast<uint32_t>(in.d_data);
      data_[mem_idx][1][repl] = static_cast<uint32_t>(in.d_data >> 32);
    }
  } else if (s0_valid) {
    data_rd_addr_[(s0_vaddr >> 2) & 1] = static_cast<uint16_t>((s0_vaddr >> 3) & 0x1ff);
  }
  if (!w.refill_done && s0_valid) tag_rd_addr_ = static_cast<uint8_t>((s0_vaddr >> 6) & 63);

  // ---- pipeline registers ----
  const bool s1_valid_old = s1_valid_;
  if (s1_valid_old) {
    s2_tag_hit_ = s1_tag_hit;
    for (unsigned way = 0; way < 4; ++way) s2_dout_[way] = s1_dout[way];
    s2_tl_error_ = s1_tl_error;
  }
  s2_hit_ = s1_hit;
  s2_valid_ = s1_valid_old && !in.s1_kill;
  s1_valid_ = s0_valid;
  s2_request_refill_reg_ = w.s1_can_request_refill;
  if (s1_valid_old && w.s1_can_request_refill) refill_paddr_ = in.s1_paddr;

  // TileLink D beat counter.
  if (in.d_valid) {
    const uint16_t beats1 = (in.d_opcode == kTlAccessAckData) ? static_cast<uint16_t>(((1u << in.d_size) - 1) >> 3) : 0;
    counter_ = static_cast<uint16_t>((counter_ == 0 ? beats1 : counter_ - 1) & 0x1ff);
  }
  if (refill_fire) {
    // LFSR(16) with taps 16, 14, 13, 11.
    const unsigned fb = ((lfsr_ >> 15) ^ (lfsr_ >> 13) ^ (lfsr_ >> 12) ^ (lfsr_ >> 10)) & 1;
    lfsr_ = static_cast<uint16_t>(((lfsr_ << 1) | fb) & 0xffff);
  }
  if (!refill_valid_) invalidated_next = false;
  invalidated_ = invalidated_next;
  if (refill_fire) refill_valid_ = true;
  if (w.refill_done) refill_valid_ = false;

  if (in.reset) {
    s1_valid_ = false; s2_valid_ = false; refill_valid_ = false;
    for (auto& v : vb_) v = 0;
    lfsr_ = 1; counter_ = 0;
  }
}

// ================================================================ BTB
namespace {
constexpr unsigned kBtbEntries = 28;
constexpr unsigned kPages = 6;
constexpr unsigned kMatchBits = 14;
constexpr uint8_t CFI_BRANCH = 0, CFI_JUMP = 1, CFI_CALL = 2, CFI_RET = 3;

inline uint32_t btb_page(uint64_t addr) { return static_cast<uint32_t>((addr & kVaMask39) >> kMatchBits); }
inline uint16_t btb_idx(uint64_t addr) { return static_cast<uint16_t>((addr >> 1) & 0x1fff); }

inline uint32_t bht_index(uint64_t addr, uint8_t history) {
  const uint64_t hi = (addr & kVaMask39) >> 2;
  const uint32_t hash_addr = static_cast<uint32_t>((hi & 0x1ff) ^ ((hi >> 9) & 3));
  const uint32_t hash_hist = ((221u * history) >> 5) & 7;
  return (hash_addr ^ (hash_hist << 6)) & 0x1ff;
}
}  // namespace

void Btb::reset() { *this = Btb{}; }

void Btb::evaluate(const BtbIn& in, BtbWires& w) const {
  const uint64_t addr = in.req_addr & kVaMask39;
  uint8_t page_hit = 0;
  {
    const uint32_t pg = btb_page(addr);
    for (unsigned i = 0; i < kPages; ++i)
      if (((page_valid_ >> i) & 1) && pages_[i] == pg) page_hit |= 1u << i;
  }
  const uint32_t idx_hit = idx_map_[btb_idx(addr)] & is_valid_;
  w.page_hit = page_hit;
  w.idx_hit = idx_hit;

  uint32_t sel_idx_page = 0, sel_tgt_page = 0, sel_tgt = 0, sel_bridx = 0, sel_cfi_type = 0;
  bool is_branch = false, do_peek = false;
  for (uint32_t m = idx_hit; m != 0; m &= m - 1) {
    const unsigned i = static_cast<unsigned>(__builtin_ctz(m));
    sel_idx_page |= idx_pages_[i];
    sel_tgt_page |= tgt_pages_[i];
    sel_tgt |= tgts_[i];
    sel_bridx |= br_idx_[i];
    sel_cfi_type |= cfi_type_[i];
    if (cfi_type_[i] == CFI_BRANCH) is_branch = true;
    if (cfi_type_[i] == CFI_RET) do_peek = true;
  }
  w.resp_valid = ((static_cast<uint32_t>(page_hit) << 1) >> sel_idx_page) & 1;
  const uint32_t page = (sel_tgt_page < kPages && ((page_valid_ >> sel_tgt_page) & 1)) ? pages_[sel_tgt_page] : 0;
  uint64_t target = (static_cast<uint64_t>(page) << kMatchBits) | (static_cast<uint64_t>(sel_tgt) << 1);
  w.resp_entry = static_cast<uint8_t>(oh_to_uint(idx_hit, kBtbEntries));
  w.resp_bridx = static_cast<uint8_t>(sel_bridx & 1);
  // BHT
  const bool resetting = !((reset_waddr_ >> 9) & 1);
  const uint8_t value = resetting ? 0 : table_[bht_index(addr, history_)];
  w.bht_history = history_;
  w.bht_value = value;
  bool taken = true;
  if (!(value & 1) && is_branch) taken = false;
  w.resp_taken = taken;
  w.resp_cfi_type = static_cast<uint8_t>(sel_cfi_type);
  w.resp_mask = taken && !w.resp_bridx ? 1 : 3;
  // RAS
  const bool empty = ras_count_ == 0;
  w.ras_head_valid = !empty;
  w.ras_head = ras_stack_[ras_pos_ % 6];
  if (!empty && do_peek) target = w.ras_head;
  w.resp_target = target & kVaMask39;
}

void Btb::commit(const BtbIn& in, const BtbWires& w) {
  const uint64_t update_target = in.req_addr & kVaMask39;
  // r_btb_update is the pipelined update from the previous cycle.
  const bool upd_valid = r_update_valid_;
  const BtbUpdate& upd = r_update_;
  if (!upd_valid) {
    // No table write: only the replacement state, the BHT, the RAS and the pipes move.
    if (r_resp_valid_ && r_resp_taken_) plru_ = plru_next_state(plru_, r_resp_entry_, kBtbEntries);
    uint32_t is_valid = is_valid_;
    if (__builtin_popcount(w.idx_hit) >= 2) is_valid &= ~w.idx_hit;
    if (in.flush) is_valid = 0;
    is_valid_ = is_valid & ((1u << kBtbEntries) - 1);
    commit_side(in, w);
    return;
  }

  uint8_t update_page_hit = 0;
  for (unsigned i = 0; i < kPages; ++i)
    if (((page_valid_ >> i) & 1) && pages_[i] == btb_page(upd.pc)) update_page_hit |= 1u << i;
  const bool update_hit = upd.entry < kBtbEntries;
  const uint32_t update_hit_addr = upd.entry;
  const bool use_update_page_hit = update_page_hit != 0;
  const bool use_page_hit = w.page_hit != 0;
  const bool do_idx_page_repl = !use_update_page_hit;
  const uint32_t rot_page_hit = ((w.page_hit & 0x1f) << 1) | (w.page_hit >> 5);
  const uint32_t idx_page_repl = rot_page_hit | (use_page_hit ? 0 : (1u << next_page_repl_));
  const uint32_t idx_page_update_oh = use_update_page_hit ? update_page_hit : idx_page_repl;
  const uint32_t idx_page_update = oh_to_uint(idx_page_update_oh, 8);
  const uint32_t idx_page_repl_en = do_idx_page_repl ? idx_page_repl : 0;
  const bool same_page = btb_page(upd.pc) == btb_page(update_target);
  const bool do_tgt_page_repl = !same_page && !use_page_hit;
  const uint32_t tgt_page_repl = same_page ? idx_page_update_oh : (((idx_page_update_oh & 0x1f) << 1) | ((idx_page_update_oh >> 5) & 1));
  const uint32_t tgt_page_update = oh_to_uint(w.page_hit | (use_page_hit ? 0 : tgt_page_repl), 8);
  const uint32_t tgt_page_repl_en = do_tgt_page_repl ? tgt_page_repl : 0;

  if (upd_valid && (do_idx_page_repl || do_tgt_page_repl)) {
    const bool both = do_idx_page_repl && do_tgt_page_repl;
    const uint32_t next = (next_page_repl_ + (both ? 2 : 1)) & 7;
    next_page_repl_ = static_cast<uint8_t>(next >= kPages ? (next & 1) : next);
  }

  const uint32_t repl_way = plru_replace_way(plru_, kBtbEntries);
  const uint32_t waddr = update_hit ? update_hit_addr : repl_way;
  if ((r_resp_valid_ && r_resp_taken_) || upd_valid)
    plru_ = plru_next_state(plru_, upd_valid ? waddr : r_resp_entry_, kBtbEntries);

  uint32_t is_valid = is_valid_;
  if (upd_valid) {
    const uint32_t mask = 1u << waddr;
    {
      const uint16_t nidx = btb_idx(upd.pc);
      idx_map_[idxs_[waddr]] &= ~(1u << waddr);
      idxs_[waddr] = nidx;
      idx_map_[nidx] |= 1u << waddr;
    }
    tgts_[waddr] = btb_idx(update_target);
    idx_pages_[waddr] = static_cast<uint8_t>((idx_page_update + 1) & 7);
    tgt_pages_[waddr] = static_cast<uint8_t>(tgt_page_update & 7);
    cfi_type_[waddr] = upd.cfi_type;
    is_valid = upd.is_valid ? (is_valid | mask) : (is_valid & ~mask);
    br_idx_[waddr] = static_cast<uint8_t>((upd.br_pc >> 1) & 1);
    const bool idx_writes_even = !(idx_page_update & 1);
    const uint32_t even_en = idx_writes_even ? idx_page_repl_en : tgt_page_repl_en;
    const uint32_t even_data = idx_writes_even ? btb_page(upd.pc) : btb_page(update_target);
    const uint32_t odd_en = idx_writes_even ? tgt_page_repl_en : idx_page_repl_en;
    const uint32_t odd_data = idx_writes_even ? btb_page(update_target) : btb_page(upd.pc);
    for (unsigned i = 0; i < kPages; i += 2) if ((even_en >> i) & 1) pages_[i] = even_data;
    for (unsigned i = 1; i < kPages; i += 2) if ((odd_en >> i) & 1) pages_[i] = odd_data;
    page_valid_ = static_cast<uint8_t>((page_valid_ | tgt_page_repl_en | idx_page_repl_en) & 0x3f);
  }
  if (__builtin_popcount(w.idx_hit) >= 2) is_valid &= ~w.idx_hit;
  if (in.flush) is_valid = 0;
  is_valid_ = is_valid & ((1u << kBtbEntries) - 1);
  commit_side(in, w);
}

void Btb::commit_side(const BtbIn& in, const BtbWires& w) {
  // BHT
  const bool resetting = !((reset_waddr_ >> 9) & 1);
  bool wen = resetting;
  uint32_t bht_waddr = reset_waddr_ & 0x1ff;
  uint8_t wdata = 0;
  uint8_t history = history_;
  if (in.bht_advance_valid) history = static_cast<uint8_t>((in.bht_advance_taken << 7) | (history_ >> 1));
  if (in.bht_update.valid) {
    if (in.bht_update.branch) {
      wen = true;
      if (!resetting) { bht_waddr = bht_index(in.bht_update.pc, in.bht_update.history); wdata = in.bht_update.taken; }
      if (in.bht_update.mispredict)
        history = static_cast<uint8_t>((in.bht_update.taken << 7) | (in.bht_update.history >> 1));
    } else if (in.bht_update.mispredict) {
      history = in.bht_update.history;
    }
  }
  if (resetting) reset_waddr_ = static_cast<uint16_t>((reset_waddr_ + 1) & 0x3ff);
  if (wen) table_[bht_waddr] = wdata & 1;
  history_ = history;

  // RAS
  if (in.ras_update_valid) {
    if (in.ras_update_cfi_type == CFI_CALL) {
      if (ras_count_ < 6) ++ras_count_;
      const uint8_t next_pos = ras_pos_ < 5 ? ras_pos_ + 1 : 0;
      ras_stack_[next_pos] = in.ras_update_return_addr & kVaMask39;
      ras_pos_ = next_pos;
    } else if (in.ras_update_cfi_type == CFI_RET) {
      if (ras_count_ != 0) {
        --ras_count_;
        ras_pos_ = ras_pos_ > 0 ? ras_pos_ - 1 : 5;
      }
    }
  }

  // Pipes.
  r_update_valid_ = in.btb_update.valid;
  if (in.btb_update.valid) r_update_ = in.btb_update;
  r_resp_valid_ = w.resp_valid;
  if (w.resp_valid) { r_resp_taken_ = w.resp_taken; r_resp_entry_ = w.resp_entry; }

  if (in.reset) {
    page_valid_ = 0; is_valid_ = 0; r_update_valid_ = false; next_page_repl_ = 0; plru_ = 0;
    r_resp_valid_ = false; history_ = 0; reset_waddr_ = 0; ras_count_ = 0; ras_pos_ = 0;
  }
}

// ================================================================ Frontend
namespace {
inline uint64_t align_pc(uint64_t pc) { return pc & ~UINT64_C(1) & kVaMask40; }
inline int64_t sext(uint64_t v, unsigned bits) { return static_cast<int64_t>(v << (64 - bits)) >> (64 - bits); }
inline int64_t rvc_b_imm(uint32_t x) {
  const uint64_t v = (((x >> 12) & 1) << 8) | (((x >> 5) & 3) << 6) | (((x >> 2) & 1) << 5) |
                     (((x >> 10) & 3) << 3) | (((x >> 3) & 3) << 1);
  return sext(v, 9);
}
inline int64_t rvc_j_imm(uint32_t x) {
  const uint64_t v = (((x >> 12) & 1) << 11) | (((x >> 8) & 1) << 10) | (((x >> 9) & 3) << 8) |
                     (((x >> 6) & 1) << 7) | (((x >> 7) & 1) << 6) | (((x >> 2) & 1) << 5) |
                     (((x >> 11) & 1) << 4) | (((x >> 3) & 7) << 1);
  return sext(v, 12);
}
}  // namespace

void Frontend::reset(uint64_t reset_vector) {
  tlb.reset();
  icache.reset();
  btb.reset();
  fq_count_ = 0;
  s1_valid_ = false; s1_pc_ = 0; s1_speculative_ = false;
  s2_valid_ = false;
  s2_pc_ = align_pc(reset_vector);
  s2_btb_resp_valid_ = false; s2_btb_taken_bit_ = false; s2_btb_bridx_ = 0; s2_btb_entry_ = 0;
  s2_bht_history_ = 0; s2_bht_value_ = 0;
  s2_tlb_miss_ = s2_tlb_pf_inst_ = s2_tlb_ae_inst_ = s2_tlb_cacheable_ = false;
  s2_speculative_ = false;
  s2_partial_insn_valid_ = false; s2_partial_insn_ = 0;
  wrong_path_ = false;
  s2_replay_reg_ = true;
  fq_enq_valid_reg_ = false;
  clock_en_reg_ = false;
  s2_btb_cfi_type_ = s2_btb_mask_ = 0; s2_btb_target_ = 0;
}

void Frontend::evaluate(const FrontendIn& in, FrontendWires& w) const {
  w.idle = false;
  // A full queue with a stalled consumer and drained request pipelines has
  // no lookup to perform. Background resets, table writes, refills, fences
  // and redirects are explicit wakeups; none is hidden by this fast path.
  if (architectural_mode_ && fq_count_ == 5 && !in.resp_ready && s2_replay_reg_ &&
      !s1_valid_ && !s2_valid_ && !icache.s1_valid_ && !icache.s2_valid_ &&
      !icache.refill_valid_ && tlb.state_ == TLB_S_READY &&
      ((btb.reset_waddr_ >> 9) & 1) && !btb.r_update_valid_ &&
      !in.req_valid && !in.sfence_valid && !in.flush_icache && !in.d_valid &&
      !in.ptw.resp_valid && !in.btb_update.valid && !in.bht_update.valid && !in.reset) {
    w = FrontendWires{};
    w.idle = true;
    w.resp_valid = true;
    w.resp = fq_[0];
    w.s2_replay = true;
    w.npc = align_pc(s2_pc_);
    w.s1_speculative_next = s2_speculative_;
    return;
  }
  // ---- stage 0 admission ----
  const uint8_t mask = fq_valid();
  const bool s0_fq_has_space = !((mask >> 2) & 1) ||
                               (!((mask >> 3) & 1) && (!s1_valid_ || !s2_valid_)) ||
                               (!((mask >> 4) & 1) && (!s1_valid_ && !s2_valid_));
  const bool s0_valid = in.req_valid || s0_fq_has_space;
  w.s0_valid = s0_valid;

  // ---- s2 kill conditions (registers only) ----
  const bool s2_xcpt = s2_tlb_ae_inst_ || s2_tlb_pf_inst_;
  const bool disable_spec_refill = (in.chicken >> 3) & 1;
  const bool s2_can_speculatively_refill = s2_tlb_cacheable_ && !disable_spec_refill;
  const bool icache_s2_kill = (s2_speculative_ && !s2_can_speculatively_refill) || s2_xcpt;

  // ---- icache outputs ----
  ICacheIn& ic = w.icache_in;
  ic = ICacheIn{};
  ic.s2_kill = icache_s2_kill;
  ic.a_ready = in.a_ready;
  ic.d_valid = in.d_valid; ic.d_opcode = in.d_opcode; ic.d_size = in.d_size; ic.d_data = in.d_data; ic.d_corrupt = in.d_corrupt;
  ic.invalidate = in.flush_icache;
  ic.reset = in.reset;
  ic.architectural_mode = architectural_mode_;
  icache.evaluate(ic, w.icache);

  // ---- fetch queue enqueue ----
  const bool enq_ready = fq_count_ < 5;
  const bool enq_valid = fq_enq_valid_reg_ && s2_valid_ && (w.icache.resp_valid || (!s2_tlb_miss_ && icache_s2_kill));
  const bool enq_fire = enq_valid && enq_ready;
  w.enq_valid = enq_valid;
  w.enq_fire = enq_fire;
  const bool s2_replay = (s2_valid_ && !enq_fire) || s2_replay_reg_;
  w.s2_replay = s2_replay;

  // ---- TLB (stage 1) ----
  TlbIn& ti = w.tlb_in;
  ti = TlbIn{};
  ti.req_valid = s1_valid_ && !s2_replay;
  ti.vaddr = s1_pc_ & kVaMask40;
  ti.passthrough = false;
  ti.size = 2;
  ti.cmd = M_XRD;
  ti.sfence_valid = in.sfence_valid; ti.sfence_rs1 = in.sfence_rs1; ti.sfence_rs2 = in.sfence_rs2; ti.sfence_addr = in.sfence_addr;
  ti.kill = !s2_valid_;
  ti.ptw = in.ptw;
  ti.prv = in.prv; ti.dprv = in.prv; ti.debug = in.debug; ti.sum = false; ti.mxr = false;
  ti.ptbr_mode = in.ptbr_mode;
  ti.pmp = in.pmp;
  ti.reset = in.reset;
  tlb.evaluate(ti, w.tlb);

  // ---- BTB lookup (stage 1) ----
  BtbIn& bi = w.btb_in;
  bi = BtbIn{};
  bi.req_addr = s1_pc_ & kVaMask39;
  bi.reset = in.reset;
  btb.evaluate(bi, w.btb);

  const uint64_t s1_base_pc = s1_pc_ & ~UINT64_C(3) & kVaMask40;
  const uint64_t ntpc = (s1_base_pc + 4) & kVaMask40;
  uint64_t predicted_npc = ntpc;
  bool predicted_taken = false;
  if (w.btb.resp_valid && w.btb.resp_taken) {
    predicted_npc = static_cast<uint64_t>(sext(w.btb.resp_target, 39)) & kVaMask40;
    predicted_taken = true;
  }

  // ---- stage 2 fetch bundle ----
  FetchBundle& e = w.enq;
  e = FetchBundle{};
  e.pc = s2_pc_ & kVaMask40;
  e.data = w.icache.resp_data;
  e.replay = (icache_s2_kill && !w.icache.resp_valid && !s2_xcpt);  // icache replay (disparity) is never set
  const bool s2_btb_taken = s2_btb_resp_valid_ && s2_btb_taken_bit_;
  w.s2_btb_taken = s2_btb_taken;
  e.btb_taken = s2_btb_taken;
  e.btb_bridx = s2_btb_bridx_;
  e.btb_entry = s2_btb_entry_;
  e.bht_history = s2_bht_history_;
  e.bht_value = s2_bht_value_;
  e.btb_cfi_type = s2_btb_cfi_type_;
  e.btb_mask = s2_btb_mask_;
  e.btb_target = s2_btb_target_;
  e.pf_inst = s2_tlb_pf_inst_;
  e.ae_inst = s2_tlb_ae_inst_ || (w.icache.resp_valid && w.icache.resp_ae);
  const uint8_t fetch_mask = static_cast<uint8_t>((3u << ((s2_pc_ >> 1) & 1)) & 3);
  e.mask = fetch_mask;

  // ---- branch/jump pre-decode over the two parcels ----
  const bool force_taken = false;  // no branch-prediction-mode CSR in this configuration
  const uint64_t s2_base_pc = s2_pc_ & ~UINT64_C(3) & kVaMask40;
  bool btb_flush = false;
  bool wrong_path_set = false;
  bool use_ras = false, update_btb = false;
  bool ras_update_valid = false;
  uint8_t ras_cfi = CFI_JUMP;
  unsigned taken_idx = 0, after_idx = 1;
  bool bht_advance_valid = false;
  bool partial_set = false;
  uint16_t partial_bits = 0;
  bool taken_acc = false;
  bool prev_valid = s2_partial_insn_valid_;
  uint32_t prev_bits = s2_partial_insn_;
  for (unsigned idx = 0; idx < 2 && ((in.exact_seam && !architectural_mode_) || s2_valid_); ++idx) {
    const bool prev_taken = taken_acc;
    const bool prev_rvi = prev_valid && !is_rvc(prev_bits);
    const bool valid = ((fetch_mask >> idx) & 1) && !prev_rvi;
    const uint32_t bits = (e.data >> (16 * idx)) & 0xffff;
    const bool rvc = is_rvc(bits);
    const uint32_t rvi_bits = (bits << 16) | prev_bits;
    const uint32_t op = rvi_bits & 0x7f;
    const bool rvi_branch = op == 0x63;
    const bool rvi_jump = op == 0x6f;
    const bool rvi_jalr = op == 0x67;
    const bool rvi_return = rvi_jalr && !((rvi_bits >> 7) & 1) && (((rvi_bits >> 15) & 0x1b) == 0x01);
    const bool rvi_call = (rvi_jalr || rvi_jump) && ((rvi_bits >> 7) & 1);
    const bool rvc_branch = (bits & 0xe003) == 0xc001 || (bits & 0xe003) == 0xe001;
    const bool rvc_jump = (bits & 0xe003) == 0xa001;
    const int64_t rvc_imm = ((bits >> 14) & 1) ? rvc_b_imm(bits) : rvc_j_imm(bits);
    const bool rvc_jr = (bits & 0xf003) == 0x8002 && ((bits >> 2) & 0x1f) == 0;
    const bool rvc_return = rvc_jr && (((bits >> 7) & 0x1b) == 0x01);
    const bool rvc_jalr = (bits & 0xf003) == 0x9002 && ((bits >> 2) & 0x1f) == 0;
    const bool rvc_call = rvc_jalr;
    const int64_t rvi_imm = static_cast<int64_t>(decode_imm(rvi_bits, ((rvi_bits >> 3) & 1) ? IMM_UJ : IMM_SB));
    const bool predict_taken = (s2_bht_value_ & 1) || force_taken;
    const bool taken = (prev_rvi && (rvi_jump || rvi_jalr || (rvi_branch && predict_taken))) ||
                       (valid && (rvc_jump || rvc_jalr || rvc_jr || (rvc_branch && predict_taken)));
    const bool predict_return = w.btb.ras_head_valid && ((prev_rvi && rvi_return) || (valid && rvc_return));
    const bool predict_jump = (prev_rvi && rvi_jump) || (valid && rvc_jump);
    const bool predict_branch = predict_taken && ((prev_rvi && rvi_branch) || (valid && rvc_branch));

    if (s2_valid_ && s2_btb_resp_valid_ && s2_btb_bridx_ == idx && valid && !rvc) {
      btb_flush = true;
      e.replay = true;
      wrong_path_set = true;
    }
    if (!prev_taken) {
      taken_idx = idx;
      after_idx = idx + 1;
      ras_update_valid = enq_fire && !wrong_path_ && ((prev_rvi && (rvi_call || rvi_return)) || (valid && (rvc_call || rvc_return)));
      const bool is_ret = prev_rvi ? rvi_return : rvc_return;
      const bool is_call = prev_rvi ? rvi_call : rvc_call;
      const bool is_br = (prev_rvi ? rvi_branch : rvc_branch) && !force_taken;
      ras_cfi = is_ret ? CFI_RET : is_call ? CFI_CALL : is_br ? CFI_BRANCH : CFI_JUMP;
      if (!s2_btb_taken) {
        if (enq_fire && taken && !predict_branch && !predict_jump && !predict_return) wrong_path_set = true;
        if (s2_valid_ && predict_return) use_ras = true;
        if (s2_valid_ && (predict_branch || predict_jump)) {
          const uint64_t pc = s2_base_pc | (idx * 2);
          int64_t npc;
          if (idx == 0) npc = static_cast<int64_t>(pc) + (prev_rvi ? rvi_imm - 2 : rvc_imm);
          else npc = static_cast<int64_t>(prev_rvi ? ((pc - 2) & kVaMask40) : pc) + (prev_rvi ? rvi_imm : rvc_imm);
          predicted_npc = static_cast<uint64_t>(npc) & kVaMask40;
        }
      }
      if ((prev_rvi && rvi_branch) || (valid && rvc_branch)) bht_advance_valid = enq_fire && !wrong_path_;
      if (!s2_btb_resp_valid_ && ((predict_branch && (s2_bht_value_ == 1)) || predict_jump || predict_return)) update_btb = true;
    }
    if (idx == 1) {
      if (enq_fire) {
        if (valid && !prev_taken && !rvc) { partial_set = true; partial_bits = static_cast<uint16_t>(bits | 3); }
      }
    }
    taken_acc = prev_taken || taken;
    prev_valid = valid;
    prev_bits = bits;
  }
  const bool taken = taken_acc;
  w.taken = taken;
  w.wrong_path_set = wrong_path_set;
  w.partial_set = partial_set;
  w.partial_bits = partial_bits;
  if (use_ras) predicted_npc = w.btb.ras_head & kVaMask40;

  bool s2_redirect = in.req_valid;
  if (!s2_btb_taken && taken) {
    e.btb_bridx = static_cast<uint8_t>(taken_idx);
    e.btb_taken = true;
    e.btb_entry = kBtbEntries;
    if (enq_fire) s2_redirect = true;
  }
  w.s2_redirect = s2_redirect;

  // ---- BTB update inputs ----
  bi.bht_update = in.bht_update;
  if (force_taken) bi.bht_update.valid = false;
  bi.btb_update = in.btb_update;
  if (!in.btb_update.valid) {
    const bool fetch_bubble_likely = fq_count_ < 2;
    bi.btb_update.valid = enq_fire && !wrong_path_ && fetch_bubble_likely && update_btb;
    bi.btb_update.entry = kBtbEntries;
    bi.btb_update.is_valid = true;
    bi.btb_update.cfi_type = ras_cfi;
    bi.btb_update.br_pc = (s2_base_pc | (static_cast<uint64_t>(taken_idx) << 1)) & kVaMask39;
    bi.btb_update.pc = s2_base_pc & kVaMask39;
  }
  bi.ras_update_valid = ras_update_valid;
  bi.ras_update_cfi_type = ras_cfi;
  bi.ras_update_return_addr = (s2_base_pc + (static_cast<uint64_t>(after_idx) << 1)) & kVaMask39;
  bi.bht_advance_valid = bht_advance_valid;
  bi.bht_advance_taken = s2_bht_value_ & 1;
  bi.flush = btb_flush;

  // ---- next PC ----
  const uint64_t npc = s2_replay ? (s2_pc_ & kVaMask40) : predicted_npc;
  const uint64_t cpu_npc = align_pc(in.req_valid ? in.req_pc : npc);
  w.npc = cpu_npc;
  w.predicted_npc = predicted_npc;
  w.predicted_taken = predicted_taken;
  const bool s0_speculative = s1_speculative_ || (s2_valid_ && !s2_speculative_) || predicted_taken;
  w.s1_speculative_next = in.req_valid ? in.req_speculative : (s2_replay ? s2_speculative_ : s0_speculative);

  // ---- icache inputs that depend on this cycle's logic ----
  ic.req_valid = s0_valid;
  ic.req_addr = cpu_npc & kVaMask39;
  ic.s1_paddr = w.tlb.paddr;
  ic.s1_kill = s2_redirect || w.tlb.miss || s2_replay;

  // ---- outputs ----
  w.resp_valid = fq_count_ != 0 || enq_valid;
  w.resp = fq_count_ != 0 ? fq_[0] : e;
  w.a_valid = w.icache.a_valid;
  w.a_address = w.icache.a_address;
  w.ptw_req_valid = w.tlb.ptw_req_valid;
  w.ptw_req_bits_valid = w.tlb.ptw_req_bits_valid;
  w.ptw_req_addr = w.tlb.ptw_req_addr;
}

void Frontend::commit(const FrontendIn& in, const FrontendWires& w) {
  if (architectural_mode_ && w.idle) {
    clock_en_reg_ = true;
    s1_pc_ = w.npc;
    s1_speculative_ = w.s1_speculative_next;
    fq_enq_valid_reg_ = false;
    icache.s2_request_refill_reg_ = true;
    return;
  }
  tlb.commit(w.tlb_in, w.tlb);
  btb.commit(w.btb_in, w.btb);
  icache.commit(w.icache_in, w.icache);
  clock_en_reg_ = true;  // !rocketParams.clockGate in the locked DefaultConfig

  // ---- physical ShiftQueue register writes (util/ShiftQueue.scala) ----
  {
    const unsigned count = fq_count_;
    if (in.resp_ready) {
      // Ascending order preserves each pre-edge source. The final occupied
      // slot holds on a dequeue without enqueue; empty flow-through holds all
      // slots. These residual values are part of the register-oracle contract.
      for (unsigned i = 0; i < count; ++i) {
        if (i + 1 < count) fq_[i] = fq_[i + 1];
        else if (w.enq_fire) fq_[i] = w.enq;
      }
      fq_count_ = static_cast<uint8_t>(count ? count - 1 + w.enq_fire : 0);
    } else if (w.enq_fire) {
      fq_[count] = w.enq;
      fq_count_ = static_cast<uint8_t>(count + 1);
    }
    // The queue reset only resets valid bits. Its unreset elts registers
    // still take the writes above on a reset or CPU redirect edge.
    if (in.reset || in.req_valid) fq_count_ = 0;
  }

  // ---- pipeline registers ----
  const bool s2_replay = w.s2_replay;
  fq_enq_valid_reg_ = s1_valid_;
  s2_replay_reg_ = s2_replay && !w.s0_valid;
  if (!s2_replay) {
    s2_valid_ = !w.s2_redirect;
    s2_pc_ = s1_pc_ & kVaMask40;
    s2_speculative_ = s1_speculative_;
    s2_tlb_miss_ = w.tlb.miss;
    s2_tlb_pf_inst_ = w.tlb.pf_inst;
    s2_tlb_ae_inst_ = w.tlb.ae_inst;
    s2_tlb_cacheable_ = w.tlb.cacheable;
    s2_btb_resp_valid_ = w.btb.resp_valid;
    s2_btb_taken_bit_ = w.btb.resp_taken;
    s2_btb_bridx_ = w.btb.resp_bridx;
    s2_btb_entry_ = w.btb.resp_entry;
    s2_bht_history_ = w.btb.bht_history;
    s2_bht_value_ = w.btb.bht_value;
    s2_btb_cfi_type_ = w.btb.resp_cfi_type;
    s2_btb_mask_ = w.btb.resp_mask;
    s2_btb_target_ = w.btb.resp_target;
  } else {
    s2_valid_ = false;
  }
  s1_valid_ = w.s0_valid;
  s1_pc_ = w.npc;
  s1_speculative_ = w.s1_speculative_next;

  // partial instruction and wrong path
  if (w.enq_fire) {
    s2_partial_insn_valid_ = false;
    if (w.partial_set) { s2_partial_insn_valid_ = true; s2_partial_insn_ = w.partial_bits; }
  }
  if (w.enq_fire && (w.s2_btb_taken || w.taken)) s2_partial_insn_valid_ = false;
  if (w.s2_redirect) s2_partial_insn_valid_ = false;
  if (w.wrong_path_set) wrong_path_ = true;
  if (in.req_valid) wrong_path_ = false;

  if (in.reset) {
    s2_valid_ = false;
    s2_pc_ = align_pc(in.reset_vector);
    s2_speculative_ = false;
    s2_partial_insn_valid_ = false;
    wrong_path_ = false;
    s2_replay_reg_ = true;
    fq_count_ = 0;
  }
}

}  // namespace chisa::rocket_model
