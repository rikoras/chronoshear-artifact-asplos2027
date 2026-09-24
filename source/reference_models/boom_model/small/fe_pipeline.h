#pragma once
// ==========================================================================
// model frontend: fetch-pipeline components (F0-F2 control, F3 queues and
// assembly, F4 queue, FetchBuffer, FTQ, predictor-update arbiter, RAS).
//
// Same register-transfer semantics as guiders/boom-system/components/
// small_{f0_f2,f3_queues,f3_assembler,f4_queue,fetch_buffer,ftq,
// bpd_update_path,ras}.h; the structure differs:
//   * outputs that are registered state are read in place (references),
//     never copied into per-cycle output structures;
//   * per-cycle bundles are produced once, into a persistent slot, and the
//     consumers read that slot;
//   * work that only matters when a valid entry moves is gated by the
//     valid bit, and the F3 assembly is memoized on its inputs.
// ==========================================================================
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "../common/model_mode.h"
#include "../common/fetch_queues.h"

#include "../common/boom_config.h"
#include "../common/core_types.h"
#include "../../boom-system/components/small_f0_f2.h"
#include "../../boom-system/components/small_f3_queues.h"
#include "../../boom-system/components/small_fetch_buffer.h"
#include "../../boom-system/components/small_ftq.h"
#include "../../common/rvc_expand.h"

namespace chisa::boom_model::fe {

namespace components = chisa::boom_system::components;
using components::SmallBpdResponse;
using components::SmallFetchBundle;
using components::SmallFrontendPredictionResponse;
using components::SmallFrontendResp;
using components::SmallFrontendTlbResponse;
using components::SmallFtqBpdUpdate;
using components::SmallFtqEntry;
using components::SmallFtqGetPcResponse;
using components::SmallGlobalHistory;
using components::advance_global_history;

static_assert(boomcfg::NBANKS == 1 && boomcfg::FETCH_WIDTH == 4 && boomcfg::CORE_WIDTH == 1,
              "the model frontend is written for the Small (single-bank, 4-wide) fetch unit");

constexpr std::uint64_t kPcMask40 = (UINT64_C(1) << 40) - 1;
constexpr std::uint8_t kFetchMask = 0x0f;

// ---------------------------------------------------------------------------
// F3 queues: f3 (depth 1, pipe) and f3_bpd_resp (depth 1, pipe+flow).
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// F3 assembly (halfword alignment, RVC expansion, CFI decode).
// ---------------------------------------------------------------------------
struct F3Assembled {
  bool enq_valid = false;
  SmallFetchBundle bundle{};
  bool trailing_half_valid = false;
  std::uint16_t trailing_half = 0;
  std::uint8_t btb_mispredicts = 0;
  std::uint8_t br_mask = 0;
  std::uint8_t cfi_type = 0;
  bool cfi_is_call = false, cfi_is_ret = false, cfi_npc_plus4 = false;
  std::uint64_t predicted_target = 0;
  SmallGlobalHistory predicted_ghist{};
  bool ras_write_valid = false;
  std::uint8_t ras_write_idx = 0;
  std::uint64_t ras_write_addr = 0;
};

class F3Assembler {
 public:
  explicit F3Assembler(bool cache_static_decode = true) : cache_static_decode_(cache_static_decode) {}
  /** Evaluate for this cycle.  `bpd_key` identifies the predictor response
    * payload (a queue version, or a per-cycle live key); with the other
    * inputs it forms the memo key. */
  const F3Assembled& evaluate(bool clear, bool main_valid, const SmallFrontendResp& main,
                              std::uint32_t main_key, const SmallBpdResponse& bpd,
                              std::uint64_t bpd_key, std::uint64_t ras_read_addr);
  void commit(bool reset, bool clear, bool main_valid, bool deq_ready) {
    const bool fire = main_valid && deq_ready;
    if (fire) { prev_is_half_ = out_.trailing_half_valid; prev_half_ = out_.trailing_half; }
    if (reset || clear) prev_is_half_ = false;
    if (fire && out_.bundle.cfi_valid) prev_is_half_ = false;
  }
  F3Assembled& out() { return out_; }
  const F3Assembled& out() const { return out_; }
  std::uint16_t prev_half() const { return prev_half_; }
  bool prev_is_half() const { return prev_is_half_; }

 private:
  struct StaticSlotDecode {
    std::uint32_t key = 0, expanded = 0;
    std::uint64_t target_delta = 0;
    std::uint8_t cfi = 0;
    bool valid = false, rvc = false, call = false, ret = false;
    bool sfb = false, edge_sfb = false;
  };
  std::array<StaticSlotDecode, 4> decoded_{};
  bool cache_static_decode_ = true;
  const StaticSlotDecode& decode_slot(std::size_t slot, std::uint32_t raw) {
    const bool rvc = (raw & 3u) != 3u;
    const std::uint32_t key = rvc ? raw & 0xffffu : raw;
    StaticSlotDecode& d = decoded_[slot];
    if (cache_static_decode_ && d.valid && d.key == key) return d;
    d.key = key; d.valid = true; d.rvc = rvc; d.expanded = raw;
    if (rvc) { bool compressed = false; d.expanded = rvc_expand(static_cast<std::uint16_t>(raw), &compressed); }
    d.cfi = decode_cfi_type(d.expanded);
    d.call = (d.cfi == kCfiJal || d.cfi == kCfiJalr) && ((d.expanded >> 7) & 0x1fu) == 1u;
    d.ret = d.cfi == kCfiJalr &&
        ((((d.expanded >> 15) & 0x1fu) == 1u) || (((d.expanded >> 15) & 0x1fu) == 5u)) &&
        ((d.expanded >> 7) & 0x1fu) == 0u;
    d.target_delta = direct_target(0, d.expanded, d.cfi);
    d.sfb = is_sfb(d.expanded, slot, false);
    d.edge_sfb = is_sfb(d.expanded, slot, true);
    return d;
  }
  static constexpr std::uint8_t kCfiNone = 0, kCfiBranch = 1, kCfiJal = 2, kCfiJalr = 3;
  static std::uint8_t decode_cfi_type(std::uint32_t inst) {
    const std::uint8_t opcode = inst & 0x7fu;
    const std::uint8_t funct3 = static_cast<std::uint8_t>((inst >> 12) & 7u);
    if (opcode == 0x67u && funct3 == 0) return kCfiJalr;
    if (opcode == 0x6fu) return kCfiJal;
    if (opcode == 0x63u && (funct3 <= 1u || funct3 >= 4u)) return kCfiBranch;
    return kCfiNone;
  }
  static std::int64_t sext(std::uint64_t v, unsigned bits) {
    const unsigned sh = 64u - bits;
    return static_cast<std::int64_t>(v << sh) >> sh;
  }
  static std::uint64_t direct_target(std::uint64_t pc, std::uint32_t inst, std::uint8_t cfi) {
    std::uint64_t imm = 0; unsigned bits = 1;
    if (cfi == kCfiBranch) {
      imm = (((inst >> 31) & 1u) << 12) | (((inst >> 7) & 1u) << 11) | (((inst >> 25) & 0x3fu) << 5) | (((inst >> 8) & 0xfu) << 1);
      bits = 13;
    } else if (cfi == kCfiJal) {
      imm = (((inst >> 31) & 1u) << 20) | (((inst >> 12) & 0xffu) << 12) | (((inst >> 20) & 1u) << 11) | (((inst >> 21) & 0x3ffu) << 1);
      bits = 21;
    }
    return (pc + static_cast<std::uint64_t>(sext(imm, bits))) & kPcMask40;
  }
  static bool is_sfb(std::uint32_t inst, std::size_t slot, bool edge) {
    if (decode_cfi_type(inst) != kCfiBranch || ((inst >> 31) & 1u) != 0) return false;
    const std::uint32_t off = (((inst >> 7) & 1u) << 11) | (((inst >> 25) & 0x3fu) << 5) | (((inst >> 8) & 0xfu) << 1);
    if (off == 0 || off >= static_cast<std::uint32_t>(boomcfg::ICACHE_BLOCK_BYTES)) return false;
    const std::uint32_t packet_offset = static_cast<std::uint32_t>(slot * 2u) + off - (edge ? 2u : 0u);
    return packet_offset <= static_cast<std::uint32_t>(2 * boomcfg::FETCH_BYTES);
  }

  F3Assembled out_{};
  // memo
  bool memo_valid_ = false;
  std::uint32_t m_main_key_ = 0; std::uint64_t m_bpd_key_ = 0, m_ras_ = 0;
  std::uint16_t m_prev_half_ = 0; bool m_prev_is_half_ = false, m_clear_ = false, m_main_valid_ = false;

  std::uint16_t prev_half_ = 0;
  bool prev_is_half_ = false;
};

inline const F3Assembled& F3Assembler::evaluate(bool clear, bool main_valid, const SmallFrontendResp& main,
                                                std::uint32_t main_key, const SmallBpdResponse& bpd,
                                                std::uint64_t bpd_key, std::uint64_t ras_read_addr) {
  if constexpr (kArchitecturalModel) {
    if (!main_valid) {
      // No fetch entry can enqueue, train the BTB, or write the RAS. Leave
      // inactive data in place instead of rebuilding/decoding a dead packet.
      memo_valid_ = false;
      out_.enq_valid = false;
      out_.bundle.mask = 0;
      out_.bundle.cfi_valid = false;
      out_.btb_mispredicts = 0;
      out_.br_mask = 0;
      out_.ras_write_valid = false;
      return out_;
    }
  }
  // With F3 empty no slot is selected, so nothing the predictor payload
  // feeds is observable (the RAS write address and index still are: the
  // RTL registers those wires every cycle).  Dropping the payload from the
  // memo key then keeps the assembly cached across the idle cycles.
  if (!main_valid) bpd_key = 0;
  if (memo_valid_ && m_main_key_ == main_key && m_bpd_key_ == bpd_key && m_ras_ == ras_read_addr &&
      m_prev_half_ == prev_half_ && m_prev_is_half_ == prev_is_half_ && m_clear_ == clear &&
      m_main_valid_ == main_valid)
    return out_;
  memo_valid_ = true; m_main_key_ = main_key; m_bpd_key_ = bpd_key; m_ras_ = ras_read_addr;
  m_prev_half_ = prev_half_; m_prev_is_half_ = prev_is_half_; m_clear_ = clear; m_main_valid_ = main_valid;

  F3Assembled& r = out_;
  const std::uint8_t keep_fsrc = r.bundle.debug_fsrc;   // patched by the caller after F0-F2
  r = F3Assembled{};
  r.bundle.debug_fsrc = keep_fsrc;
  r.enq_valid = main_valid && !clear;
  SmallFetchBundle& B = r.bundle;
  B.pc = main.pc & kPcMask40;
  B.edge_inst = prev_is_half_;
  B.edge_insts[0] = prev_is_half_;
  B.xcpt_pf_if = main.xcpt_pf_if;
  B.xcpt_ae_if = main.xcpt_ae_if;
  B.bp_debug_mask = 0;
  B.bp_xcpt_mask = 0;
  B.shadowed_mask = 0;
  B.ras_top = ras_read_addr & kPcMask40;
  B.ghist = main.ghist;
  B.bpd_meta = bpd.meta;
  B.bpd_meta[3] &= 0x00ffffffu;
  B.ghist.ras_idx = static_cast<std::uint8_t>(B.ghist.ras_idx & 0x1fu);
  B.cfi_idx = boomcfg::FETCH_WIDTH - 1;

  const bool edge = prev_is_half_;
  const std::uint64_t data = main.data;
  const std::uint64_t aligned = boomcfg::fetch_bank_align(main.pc);
  std::array<std::uint32_t, 4> raw{};
  std::array<bool, 4> slot_valid{}, is_rvc{}, is_call{}, is_ret{}, npc_plus4{};
  std::array<std::uint8_t, 4> cfi{};
  std::array<std::uint64_t, 4> targets{};
  bool redirect_found = false;
  for (std::size_t s = 0; s < 4; ++s) {
    if (s == 0) {
      raw[0] = edge ? (static_cast<std::uint32_t>(data & 0xffffu) << 16) | prev_half_
                    : static_cast<std::uint32_t>(data & UINT64_C(0xffffffff));
      slot_valid[0] = true;
    } else if (s == 3) {
      raw[3] = static_cast<std::uint32_t>((data >> 48) & 0xffffu);
      const bool prev_consumes = ((B.mask >> 2) & 1u) && !is_rvc[2];
      slot_valid[3] = !prev_consumes && ((raw[3] & 3u) != 3u);
    } else {
      raw[s] = static_cast<std::uint32_t>(data >> (16 * s));
      const bool prev_consumes = ((B.mask >> (s - 1)) & 1u) && !is_rvc[s - 1];
      slot_valid[s] = !prev_consumes;
      if (s == 1) slot_valid[1] = edge || slot_valid[1];
    }
    if (kArchitecturalModel && !slot_valid[s]) {
      // This halfword belongs to the preceding 32-bit instruction. It is
      // excluded from both selection and BTB correction, so no decoder or
      // target calculation consumes it. Other unselected slots still train.
      is_rvc[s] = (raw[s] & 3u) != 3u;
      continue;
    }
    const StaticSlotDecode& decoded = decode_slot(s, raw[s]);
    is_rvc[s] = decoded.rvc;
    B.insts[s] = raw[s];
    B.expanded_insts[s] = decoded.expanded;
    const bool selected = main_valid && ((main.mask >> s) & 1u) && slot_valid[s] && !redirect_found;
    if (selected) B.mask |= static_cast<std::uint8_t>(1u << s);
    cfi[s] = decoded.cfi;
    is_call[s] = decoded.call;
    is_ret[s] = decoded.ret;
    npc_plus4[s] = !is_rvc[s] && !(s == 0 && edge);
    const std::uint64_t slot_pc = (aligned + static_cast<std::uint64_t>(s * 2u) - ((s == 0 && edge) ? UINT64_C(2) : 0)) & kPcMask40;
    targets[s] = cfi[s] == kCfiJalr ? (bpd.preds[s].predicted_pc & kPcMask40)
                                  : (slot_pc + decoded.target_delta) & kPcMask40;
    if (cfi[s] == kCfiJal && slot_valid[s] && bpd.preds[s].predicted_pc_valid &&
        (bpd.preds[s].predicted_pc & kPcMask40) != targets[s])
      r.btb_mispredicts |= static_cast<std::uint8_t>(1u << s);
    if (selected && cfi[s] == kCfiBranch) r.br_mask |= static_cast<std::uint8_t>(1u << s);
    const bool redirect = selected && (cfi[s] == kCfiJal || cfi[s] == kCfiJalr || (cfi[s] == kCfiBranch && bpd.preds[s].taken));
    if (redirect && !B.cfi_valid) { B.cfi_valid = true; B.cfi_idx = static_cast<std::uint8_t>(s); }
    if (selected && ((s == 0 && edge) ? decoded.edge_sfb : decoded.sfb))
      B.sfb_mask |= static_cast<std::uint8_t>(1u << s);
    redirect_found = redirect_found || redirect;
  }
  const std::uint16_t last_half = static_cast<std::uint16_t>((data >> 48) & 0xffffu);
  r.trailing_half = last_half;
  r.trailing_half_valid = !(((B.mask >> 2) & 1u) && !is_rvc[2]) && ((last_half & 3u) == 3u);

  const std::size_t ci = B.cfi_idx & 3u;
  r.cfi_type = cfi[ci];
  r.cfi_is_call = is_call[ci];
  r.cfi_is_ret = is_ret[ci];
  r.cfi_npc_plus4 = npc_plus4[ci];
  B.cfi_type = r.cfi_type; B.cfi_is_call = r.cfi_is_call; B.cfi_is_ret = r.cfi_is_ret; B.cfi_npc_plus4 = r.cfi_npc_plus4;
  B.br_mask = r.br_mask;
  r.predicted_target = B.cfi_valid ? (r.cfi_is_ret ? (ras_read_addr & kPcMask40) : targets[ci])
                                   : (boomcfg::fetch_next(main.pc) & kPcMask40);
  {  // GlobalHistory.update with the RAS index
    const unsigned cfi_fixed = B.cfi_idx & 3u;
    const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t selected = B.cfi_valid ? static_cast<std::uint8_t>((cfi_oh << 1) - 1u) : kFetchMask;
    const bool cfi_is_br = r.cfi_type == kCfiBranch;
    const std::uint8_t taken_cfi = (cfi_is_br && B.cfi_valid) ? cfi_oh : 0u;
    const std::uint8_t not_taken = static_cast<std::uint8_t>(r.br_mask & selected & static_cast<std::uint8_t>(~taken_cfi));
    advance_global_history(main.ghist, not_taken, cfi_is_br, B.cfi_valid, B.cfi_valid, cfi_fixed, main.pc, r.predicted_ghist);
    if (B.cfi_valid && r.cfi_is_call) r.predicted_ghist.ras_idx = static_cast<std::uint8_t>((main.ghist.ras_idx + 1u) & 0x1fu);
    else if (B.cfi_valid && r.cfi_is_ret) r.predicted_ghist.ras_idx = static_cast<std::uint8_t>((main.ghist.ras_idx - 1u) & 0x1fu);
    else r.predicted_ghist.ras_idx = main.ghist.ras_idx;
  }
  r.ras_write_valid = B.cfi_valid && r.cfi_is_call;
  r.ras_write_idx = static_cast<std::uint8_t>((main.ghist.ras_idx + 1u) & 0x1fu);
  r.ras_write_addr = (aligned + static_cast<std::uint64_t>(ci * 2u) + (r.cfi_npc_plus4 ? UINT64_C(4) : UINT64_C(2))) & kPcMask40;
  return out_;
}

// ---------------------------------------------------------------------------
// F4 queue (depth 1, pipe).
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// FetchBuffer (8 entries, one uop dequeued per cycle).
// ---------------------------------------------------------------------------
class FetchBuffer {
 public:
  static constexpr std::size_t kEntries = 8;

  bool enq_ready() const {
    if (((tail_ & head_) != 0) && maybe_full_) return false;
    for (unsigned d = 1; d < 4; ++d)
      if ((rot(tail_, d) & head_) != 0) return false;
    return true;
  }
  bool deq_valid() const {
    const std::size_t i = idx(head_);
    const bool collide = ((tail_ >> i) & 1u) && !maybe_full_;
    return !collide;
  }
  const MicroOp& head_uop() const { return ram_[idx(head_)]; }
  std::uint32_t head() const { return head_; }
  std::uint32_t tail() const { return tail_; }
  bool maybe_full() const { return maybe_full_; }
  const MicroOp& ram(std::size_t i) const { return ram_[i]; }

  void commit(bool reset, bool clear, bool enq_valid, const SmallFetchBundle& enq, std::uint8_t ftq_idx, bool deq_ready) {
    const bool do_enq = enq_ready();
    const bool do_deq = deq_ready && deq_valid();
    std::uint32_t next_tail = tail_;
    bool any = false;
    if (enq_valid) {
      for (std::size_t s = 0; s < 4; ++s) {
        if (!((enq.mask >> s) & 1u)) continue;
        any = true;
        if (do_enq) convert(ram_[idx(next_tail)], enq, s, ftq_idx);
        next_tail = rot(next_tail, 1);
      }
    }
    if (do_enq) { tail_ = next_tail; if (any) maybe_full_ = true; }
    if (do_deq) { head_ = rot(head_, 1); maybe_full_ = false; }
    if (clear || reset) { head_ = 1; tail_ = 1; maybe_full_ = false; }
  }

 private:
  static std::uint32_t rot(std::uint32_t v, unsigned k) {
    k &= 7u;
    return ((v << k) | (v >> (8u - k))) & 0xffu;
  }
  static std::size_t idx(std::uint32_t oh) { return static_cast<std::size_t>(__builtin_ctz(oh | 0x100u)) & 7u; }
  static void convert(MicroOp& uop, const SmallFetchBundle& b, std::size_t slot, std::uint8_t ftq_idx) {
    uop.clear();
    const std::uint64_t aligned = boomcfg::fetch_bank_align(b.pc) & kPcMask40;
    const std::uint64_t slot_pc = (aligned + static_cast<std::uint64_t>(slot * 2)) & kPcMask40;
    uop.inst = b.expanded_insts[slot];
    uop.debug_inst = b.insts[slot];
    uop.is_rvc = (b.insts[slot] & 3u) != 3u;
    uop.debug_pc = slot_pc;
    uop.pc_lob = static_cast<std::uint8_t>(slot_pc & 0x3fu);
    uop.is_sfb = 0;   // enableSFBOpt=false: sfb_mask and shadowed_mask are forced zero
    if (slot == 0 && b.edge_inst) {
      uop.debug_pc = (aligned - UINT64_C(2)) & kPcMask40;
      uop.pc_lob = static_cast<std::uint8_t>(aligned & 0x3fu);
      uop.edge_inst = 1;
    }
    uop.ftq_idx = static_cast<std::uint8_t>(ftq_idx & (boomcfg::NUM_FTQ - 1));
    uop.taken = static_cast<std::uint8_t>(b.cfi_valid && (b.cfi_idx & 3u) == slot);
    uop.xcpt_pf_if = static_cast<std::uint8_t>(b.xcpt_pf_if);
    uop.xcpt_ae_if = static_cast<std::uint8_t>(b.xcpt_ae_if);
    uop.bp_debug_if = static_cast<std::uint8_t>((b.bp_debug_mask >> slot) & 1u);
    uop.bp_xcpt_if = static_cast<std::uint8_t>((b.bp_xcpt_mask >> slot) & 1u);
    uop.debug_fsrc = static_cast<std::uint8_t>(b.debug_fsrc & 3u);
  }

  std::array<MicroOp, kEntries> ram_{};
  std::uint32_t head_ = 1, tail_ = 1;
  bool maybe_full_ = false;
};

// ---------------------------------------------------------------------------
// Fetch Target Queue (16 entries).
// ---------------------------------------------------------------------------
struct FtqIn {
  bool reset = false;
  bool enq_valid = false;
  const SmallFetchBundle* enq = nullptr;
  bool deq_valid = false; std::uint8_t deq_idx = 0;
  bool redirect_valid = false; std::uint8_t redirect_idx = 0;
  bool brupdate_mispredict = false; std::uint8_t brupdate_ftq_idx = 0, brupdate_pc_lob = 0; bool brupdate_taken = false;
  std::array<std::uint8_t, 2> get_pc_idx{};
};

class Ftq {
 public:
  // ---- registered outputs (valid between commits) ----
  bool enq_ready() const { return ready_reg_; }
  std::uint8_t enq_idx() const { return enq_ptr_; }
  bool full() const { return inc(inc(enq_ptr_)) == bpd_ptr_ || inc(enq_ptr_) == bpd_ptr_; }
  bool bpdupdate_valid() const { return bpdupdate_valid_; }
  const SmallFtqBpdUpdate& bpdupdate() const { return bpdupdate_; }
  bool ras_update() const { return ras_update_; }
  std::uint8_t ras_update_idx() const { return ras_update_idx_; }
  std::uint64_t ras_update_pc() const { return ras_update_pc_; }
  const SmallFtqGetPcResponse& registered_get_pc(std::size_t p) const { return get_pc_[p]; }
  bool do_commit_update(const FtqIn& in) const {
    return !bpd_update_mispredict_ && !bpd_update_repair_ && bpd_ptr_ != deq_ptr_ &&
           enq_ptr_ != inc(bpd_ptr_) && !in.brupdate_mispredict && !in.redirect_valid && !prev_redirect_;
  }
  void commit(const FtqIn& in, bool do_commit_update_now);

  // ---- diagnostic / oracle faces ----
  std::uint64_t oracle_ram_read(std::size_t p) const { return oracle_ram_read_[p]; }
  std::uint8_t oracle_ram_idx(std::size_t p) const { return oracle_ram_idx_[p]; }
  const SmallGlobalHistory& oracle_ghist0() const { return oracle_ghist0_; }
  const SmallGlobalHistory& oracle_getpc1_ghist() const { return oracle_getpc1_ghist_; }
  bool oracle_do_commit() const { return oracle_do_commit_; }
  bool oracle_written(std::size_t i) const { return (oracle_written_ >> (i & 7)) & 1u; }
  const SmallFtqEntry& entry(std::size_t i) const { return entries_[i]; }
  const SmallGlobalHistory& ghist(std::size_t i) const { return ghists_[i]; }
  std::uint64_t pc(std::size_t i) const { return pcs_[i]; }
  const SmallFtqEntry& bpd_entry() const { return bpd_entry_; }
  const SmallFtqEntry& redirect_entry_pipeline() const { return redirect_entry_pipe_; }
  const SmallGlobalHistory& previous_ghist() const { return prev_ghist_; }
  std::uint64_t bpd_pc() const { return bpd_pc_; }
  std::uint64_t repair_pc() const { return bpd_repair_pc_; }
  bool bpdupdate_pipe_repair() const { return bpdupdate_pipe_repair_; }
  bool update_repair_flag() const { return bpd_update_repair_; }
  bool update_mispredict_flag() const { return bpd_update_mispredict_; }
  std::uint8_t repair_idx() const { return bpd_repair_idx_; }
  std::uint8_t bpd_read_ptr() const { return bpd_ptr_; }
  std::uint8_t deq_idx() const { return deq_ptr_; }
  static std::uint64_t pack_entry(const SmallFtqEntry& e) {
    return (std::uint64_t(e.cfi_valid) << 60) | ((std::uint64_t(e.cfi_idx) & 3) << 58) |
           (std::uint64_t(e.cfi_taken) << 57) | (std::uint64_t(e.cfi_mispredicted) << 56) |
           ((std::uint64_t(e.cfi_type) & 7) << 53) | ((std::uint64_t(e.br_mask) & 0xf) << 49) |
           (std::uint64_t(e.cfi_is_call) << 48) | (std::uint64_t(e.cfi_is_ret) << 47) |
           (std::uint64_t(e.cfi_npc_plus4) << 46) | ((std::uint64_t(e.ras_top) & kPcMask40) << 6) |
           ((std::uint64_t(e.ras_idx) & 0x1f) << 1) | (std::uint64_t(e.start_bank) & 1);
  }

 private:
  static std::uint8_t mask_index(std::uint8_t i) { return static_cast<std::uint8_t>(i & (boomcfg::NUM_FTQ - 1)); }
  static std::uint8_t inc(std::uint8_t i) { return static_cast<std::uint8_t>((i + 1u) & (boomcfg::NUM_FTQ - 1)); }
  static std::uint8_t mask_lower(std::uint8_t i) {
    return static_cast<std::uint8_t>(((std::uint16_t{1} << ((i & 3u) + 1u)) - 1u) & kFetchMask);
  }
  static SmallFtqEntry make_entry(const SmallFetchBundle& b) {
    SmallFtqEntry r;
    r.cfi_valid = b.cfi_valid;
    r.cfi_idx = static_cast<std::uint8_t>(b.cfi_idx & 3u);
    r.cfi_taken = b.cfi_valid;
    r.cfi_mispredicted = false;
    r.cfi_type = static_cast<std::uint8_t>(b.cfi_type & 7u);
    r.br_mask = static_cast<std::uint8_t>(b.br_mask & b.mask & kFetchMask);
    r.cfi_is_call = b.cfi_is_call;
    r.cfi_is_ret = b.cfi_is_ret;
    r.cfi_npc_plus4 = b.cfi_npc_plus4;
    r.ras_top = b.ras_top & kPcMask40;
    r.ras_idx = static_cast<std::uint8_t>(b.ghist.ras_idx & 0x1fu);
    r.start_bank = boomcfg::fetch_bank_one(b.pc);
    return r;
  }
  static SmallGlobalHistory update_history(const SmallGlobalHistory& h, const SmallFtqEntry& e, std::uint64_t pc) {
    const unsigned cfi_fixed = e.cfi_idx & 3u;
    const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t selected = e.cfi_valid ? static_cast<std::uint8_t>((cfi_oh << 1u) - 1u) : kFetchMask;
    const bool cfi_is_br = ((e.br_mask >> cfi_fixed) & 1u) != 0;
    const std::uint8_t taken_cfi = (cfi_is_br && e.cfi_taken) ? cfi_oh : 0u;
    const std::uint8_t not_taken = static_cast<std::uint8_t>(e.br_mask & selected & static_cast<std::uint8_t>(~taken_cfi));
    SmallGlobalHistory r;
    advance_global_history(h, not_taken, cfi_is_br, e.cfi_taken, e.cfi_valid, cfi_fixed, pc, r);
    if (e.cfi_valid && e.cfi_is_call) r.ras_idx = static_cast<std::uint8_t>((h.ras_idx + 1u) & 0x1fu);
    else if (e.cfi_valid && e.cfi_is_ret) r.ras_idx = static_cast<std::uint8_t>((h.ras_idx - 1u) & 0x1fu);
    else r.ras_idx = static_cast<std::uint8_t>(h.ras_idx & 0x1fu);
    return r;
  }
  void write_entry(std::uint8_t i, const SmallFtqEntry& e) {
    entries_[i] = e;
    packed_[i] = pack_entry(e);
  }
  void refresh_registered_outputs();

  std::array<std::uint64_t, boomcfg::NUM_FTQ> pcs_{};
  std::array<SmallFtqEntry, boomcfg::NUM_FTQ> entries_{};
  std::array<std::uint64_t, boomcfg::NUM_FTQ> packed_{};
  std::array<SmallGlobalHistory, boomcfg::NUM_FTQ> ghists_{};
  std::array<std::array<std::uint32_t, 4>, boomcfg::NUM_FTQ> metas_{};

  std::uint8_t bpd_ptr_ = 0, deq_ptr_ = 0, enq_ptr_ = 1;
  bool ready_reg_ = false;
  SmallGlobalHistory prev_ghist_{}; SmallFtqEntry prev_entry_{}; std::uint64_t prev_pc_ = 0;
  bool bpd_update_mispredict_ = false, bpd_update_repair_ = false, first_empty_ = true;
  bool bpdupdate_pipe_valid_ = false, bpdupdate_pipe_mispredict_ = false, bpdupdate_pipe_repair_ = false;
  std::uint8_t bpd_repair_idx_ = 0, bpd_end_idx_ = 0;
  std::uint64_t bpd_repair_pc_ = 0;
  SmallFtqEntry bpd_entry_{}; SmallGlobalHistory bpd_ghist_{}; std::array<std::uint32_t, 4> bpd_meta_{};
  std::uint64_t bpd_pc_ = 0, bpd_target_ = 0;
  bool prev_redirect_ = false; std::uint8_t prev_redirect_idx_ = 0;
  SmallFtqEntry redirect_entry_pipe_{};
  bool prev_brupdate_mispredict_ = false; std::uint8_t prev_brupdate_ftq_idx_ = 0;
  bool prev_bpd_update_mispredict_ = false; std::uint8_t prev_enq_ptr_ = 0;
  bool ras_update_ = false; std::uint8_t ras_update_idx_ = 0; std::uint64_t ras_update_pc_ = 0;
  std::array<SmallFtqGetPcResponse, 2> get_pc_{};
  // derived registered output
  bool bpdupdate_valid_ = false;
  SmallFtqBpdUpdate bpdupdate_{};
  // oracle faces
  std::array<std::uint64_t, 4> oracle_ram_read_{};
  std::array<std::uint8_t, 4> oracle_ram_idx_{};
  SmallGlobalHistory oracle_ghist0_{}, oracle_getpc1_ghist_{};
  bool oracle_do_commit_ = false;
  std::uint8_t oracle_written_ = 0;
};

inline void Ftq::refresh_registered_outputs() {
  bpdupdate_valid_ = bpdupdate_pipe_valid_ && !first_empty_ &&
                     (bpd_entry_.cfi_valid || bpd_entry_.br_mask != 0) &&
                     !(bpdupdate_pipe_repair_ && bpd_pc_ == bpd_repair_pc_);
  if (kArchitecturalModel && !bpdupdate_valid_) return;
  SmallFtqBpdUpdate& u = bpdupdate_;
  u.is_mispredict_update = bpdupdate_pipe_mispredict_;
  u.is_repair_update = bpdupdate_pipe_repair_;
  u.btb_mispredicts = 0;
  u.pc = bpd_pc_ & kPcMask40;
  u.br_mask = bpd_entry_.cfi_valid ? static_cast<std::uint8_t>(mask_lower(bpd_entry_.cfi_idx) & bpd_entry_.br_mask) : bpd_entry_.br_mask;
  u.cfi_valid = bpd_entry_.cfi_valid;
  u.cfi_idx = static_cast<std::uint8_t>(bpd_entry_.cfi_idx & 3u);
  u.cfi_taken = bpd_entry_.cfi_taken;
  u.cfi_mispredicted = bpd_entry_.cfi_mispredicted;
  u.cfi_is_br = ((bpd_entry_.br_mask >> u.cfi_idx) & 1u) != 0;
  u.cfi_is_jal = bpd_entry_.cfi_type == 2 || bpd_entry_.cfi_type == 3;
  u.cfi_is_jalr = false;
  u.ghist = bpd_ghist_;
  u.lhist = false;
  u.target = bpd_target_ & kPcMask40;
  u.meta = bpd_meta_;
}

inline void Ftq::commit(const FtqIn& in, bool do_commit_update_now) {
      oracle_do_commit_ = do_commit_update_now || bpd_update_repair_ || bpd_update_mispredict_;
  const bool do_enq = in.enq_valid && ready_reg_;
  SmallFtqEntry enq_entry{};
  SmallGlobalHistory enq_ghist{};
  if (do_enq) {
    enq_entry = make_entry(*in.enq);
    if (in.enq->ghist.current_saw_branch_not_taken) {
      enq_ghist = in.enq->ghist;
      enq_ghist.ras_idx = static_cast<std::uint8_t>(enq_ghist.ras_idx & 0x1fu);
    } else {
      enq_ghist = update_history(prev_ghist_, prev_entry_, prev_pc_);
    }
  }

  const std::uint8_t bpd_idx = in.redirect_valid ? mask_index(in.redirect_idx)
                               : ((bpd_update_repair_ || bpd_update_mispredict_) ? bpd_repair_idx_ : bpd_ptr_);
  const std::uint8_t redirect_idx = mask_index(in.redirect_idx);
  {
    oracle_ram_idx_[0] = bpd_idx;
    oracle_ghist0_ = ghists_[bpd_idx];
    oracle_ram_idx_[1] = redirect_idx;
  }

  // reads of the cycle-start arrays
  const SmallFtqEntry next_bpd_entry = entries_[bpd_idx];
  const SmallGlobalHistory next_bpd_ghist = ghists_[bpd_idx];
  const std::array<std::uint32_t, 4> next_bpd_meta = metas_[bpd_idx];
  const std::uint64_t next_bpd_pc = pcs_[bpd_idx];
  const std::uint64_t next_bpd_target = pcs_[inc(bpd_idx)];

  const SmallFtqEntry redirect_entry = entries_[redirect_idx];
  SmallFtqEntry redirect_new_entry = redirect_entry;
  if (in.redirect_valid && in.brupdate_mispredict) {
    const std::uint8_t bank_xor = redirect_entry.start_bank ? std::uint8_t{8} : std::uint8_t{0};
    const std::uint8_t new_cfi_idx = static_cast<std::uint8_t>(((in.brupdate_pc_lob ^ bank_xor) >> 1u) & 3u);
    redirect_new_entry.cfi_valid = true;
    redirect_new_entry.cfi_idx = new_cfi_idx;
    redirect_new_entry.cfi_mispredicted = true;
    redirect_new_entry.cfi_taken = in.brupdate_taken;
    redirect_new_entry.cfi_is_call = redirect_entry.cfi_is_call && redirect_entry.cfi_idx == new_cfi_idx;
    redirect_new_entry.cfi_is_ret = redirect_entry.cfi_is_ret && redirect_entry.cfi_idx == new_cfi_idx;
  }
  const bool next_ready = !full() || do_commit_update_now;
  const bool next_first_empty = bpdupdate_pipe_valid_ ? false : first_empty_;
  const bool next_pipe_valid = do_commit_update_now || bpd_update_repair_ || bpd_update_mispredict_;

  // These outputs have no PRE consumers inside commit. Capture the
  // cycle-start arrays directly, before enqueue/redirect writes, instead
  // of clearing a temporary response pair and copying it back later.
  const std::uint8_t commit_idx = mask_index(in.deq_valid ? in.deq_idx : deq_ptr_);
  for (std::size_t p = 0; p < 2; ++p) {
    SmallFtqGetPcResponse& out = get_pc_[p];
    const std::uint8_t index = mask_index(in.get_pc_idx[p]);
    const std::uint8_t next_index = inc(index);
    const bool next_is_enq = next_index == enq_ptr_ && do_enq;
    out.entry = entries_[index];
    oracle_ram_idx_[2 + p] = index;
    if (p == 1) {
      const SmallGlobalHistory& g = (do_enq && index == enq_ptr_) ? enq_ghist : ghists_[index];
      oracle_getpc1_ghist_ = g;
      out.ghist = g;
    }
    out.pc = pcs_[index];
    out.next_pc = next_is_enq ? (in.enq->pc & kPcMask40) : pcs_[next_index];
    out.next_valid = next_index != enq_ptr_ || next_is_enq;
    out.commit_pc = pcs_[commit_idx];
  }
      for (std::size_t p = 0; p < 4; ++p) oracle_ram_read_[p] = packed_[oracle_ram_idx_[p]];

  std::uint8_t next_enq_ptr = enq_ptr_, next_deq_ptr = deq_ptr_, next_bpd_ptr = bpd_ptr_;
  bool next_update_mispredict = bpd_update_mispredict_, next_update_repair = bpd_update_repair_;
  std::uint8_t next_repair_idx = bpd_repair_idx_, next_end_idx = bpd_end_idx_;
  std::uint64_t next_repair_pc = bpd_repair_pc_;
  SmallFtqEntry next_prev_entry = prev_entry_;
  SmallGlobalHistory next_prev_ghist = prev_ghist_;
  std::uint64_t next_prev_pc = prev_pc_;

  if (do_enq) {
    pcs_[enq_ptr_] = in.enq->pc & kPcMask40;
    write_entry(enq_ptr_, enq_entry);
          oracle_written_ |= std::uint8_t(1u << (enq_ptr_ & 7));   // enqueue only, as before
    ghists_[enq_ptr_] = enq_ghist;
    metas_[enq_ptr_] = in.enq->bpd_meta;
    metas_[enq_ptr_][3] &= 0x00ffffffu;
    next_prev_pc = in.enq->pc & kPcMask40;
    next_prev_entry = enq_entry;
    next_prev_ghist = enq_ghist;
    next_enq_ptr = inc(enq_ptr_);
  }
  if (in.deq_valid) next_deq_ptr = mask_index(in.deq_idx);

  if (in.redirect_valid) {
    next_update_mispredict = false;
    next_update_repair = false;
  } else if (prev_brupdate_mispredict_) {
    next_update_mispredict = true;
    next_repair_idx = prev_brupdate_ftq_idx_;
    next_end_idx = prev_enq_ptr_;
  } else if (bpd_update_mispredict_) {
    next_update_mispredict = false;
    next_update_repair = true;
    next_repair_idx = inc(bpd_repair_idx_);
  } else if (bpd_update_repair_ && prev_bpd_update_mispredict_) {
    next_repair_pc = bpd_pc_;
    next_repair_idx = inc(bpd_repair_idx_);
  } else if (bpd_update_repair_) {
    next_repair_idx = inc(bpd_repair_idx_);
    if (inc(bpd_repair_idx_) == bpd_end_idx_ || bpd_pc_ == bpd_repair_pc_) next_update_repair = false;
  }
  if (do_commit_update_now) next_bpd_ptr = inc(bpd_ptr_);
  if (in.redirect_valid) next_enq_ptr = inc(in.redirect_idx);
  if (!in.redirect_valid && prev_redirect_) {
    write_entry(prev_redirect_idx_, redirect_entry_pipe_);
    next_prev_entry = redirect_entry_pipe_;
    next_prev_ghist = bpd_ghist_;
    next_prev_pc = bpd_pc_;
  }

  ready_reg_ = next_ready;
  prev_redirect_ = in.redirect_valid;
  prev_redirect_idx_ = redirect_idx;
  redirect_entry_pipe_ = redirect_new_entry;
  prev_brupdate_mispredict_ = in.brupdate_mispredict;
  prev_brupdate_ftq_idx_ = mask_index(in.brupdate_ftq_idx);
  prev_bpd_update_mispredict_ = bpd_update_mispredict_;
  prev_enq_ptr_ = enq_ptr_;
  bpd_entry_ = next_bpd_entry;
  bpd_ghist_ = next_bpd_ghist;
  bpd_meta_ = next_bpd_meta;
  bpd_pc_ = next_bpd_pc;
  bpd_target_ = next_bpd_target;
  ras_update_ = in.redirect_valid;
  ras_update_idx_ = in.redirect_valid ? redirect_entry.ras_idx : 0;
  ras_update_pc_ = in.redirect_valid ? redirect_entry.ras_top : 0;
  first_empty_ = next_first_empty;
  bpdupdate_pipe_valid_ = next_pipe_valid;
  bpdupdate_pipe_mispredict_ = bpd_update_mispredict_;
  bpdupdate_pipe_repair_ = bpd_update_repair_;

  enq_ptr_ = next_enq_ptr;
  deq_ptr_ = next_deq_ptr;
  bpd_ptr_ = next_bpd_ptr;
  bpd_update_mispredict_ = next_update_mispredict;
  bpd_update_repair_ = next_update_repair;
  bpd_repair_idx_ = next_repair_idx;
  bpd_end_idx_ = next_end_idx;
  bpd_repair_pc_ = next_repair_pc;
  prev_entry_ = next_prev_entry;
  prev_ghist_ = next_prev_ghist;
  prev_pc_ = next_prev_pc;

  if (in.reset) {
    bpd_ptr_ = 0; deq_ptr_ = 0; enq_ptr_ = 1;
    bpd_update_mispredict_ = false; bpd_update_repair_ = false; first_empty_ = true;
    prev_entry_ = SmallFtqEntry{}; prev_ghist_ = SmallGlobalHistory{}; prev_pc_ = 0;
  }
  refresh_registered_outputs();
}

// ---------------------------------------------------------------------------
// Branch-predictor update arbiter with the two-entry correction queue.
// ---------------------------------------------------------------------------
class BpdUpdatePath {
 public:
  bool correction_deq_valid() const { return !empty(); }
  std::uint32_t enq_ptr() const { return enq_ptr_; }
  std::uint32_t deq_ptr() const { return deq_ptr_; }
  bool maybe_full() const { return maybe_full_; }
  const SmallFtqBpdUpdate& payload(std::size_t i) const { return payloads_[i]; }
  const SmallFtqBpdUpdate& deq_payload() const { return payloads_[deq_ptr_]; }
  std::uint32_t version() const { return ver_; }

  /** The arbiter output: FTQ update first, else the queued correction. */
  bool update_valid(bool ftq_valid) const { return ftq_valid || !empty(); }
  const SmallFtqBpdUpdate& update(bool ftq_valid, const SmallFtqBpdUpdate& ftq_update) const {
    return ftq_valid ? ftq_update : payloads_[deq_ptr_];
  }

  void commit(bool reset, bool f3_fire, std::uint8_t f3_btb_mispredicts, const SmallFetchBundle& f3_bundle,
              bool ftq_valid) {
    const bool enq_valid = f3_fire && (f3_btb_mispredicts & kFetchMask) != 0;
    const bool deq_ready = !ftq_valid;
    const bool enq_ready = !full();
    if (!reset && enq_valid && enq_ready) {
      SmallFtqBpdUpdate& c = payloads_[enq_ptr_];
      c = SmallFtqBpdUpdate{};
      c.btb_mispredicts = static_cast<std::uint8_t>(f3_btb_mispredicts & kFetchMask);
      c.pc = f3_bundle.pc & kPcMask40;
      c.ghist = f3_bundle.ghist;
      c.meta = f3_bundle.bpd_meta;
      c.meta[3] &= 0x00ffffffu;
      ++ver_;
    }
    if (reset) { enq_ptr_ = 0; deq_ptr_ = 0; maybe_full_ = false; ++ver_; return; }
    const bool do_enq = enq_ready && enq_valid;
    const bool do_deq = deq_ready && !empty();
    if (do_enq) enq_ptr_ ^= 1u;
    if (do_deq) deq_ptr_ ^= 1u;
    if (do_enq != do_deq) maybe_full_ = do_enq;
    if (do_enq || do_deq) ++ver_;
  }

 private:
  bool empty() const { return enq_ptr_ == deq_ptr_ && !maybe_full_; }
  bool full() const { return enq_ptr_ == deq_ptr_ && maybe_full_; }
  std::uint32_t enq_ptr_ = 0, deq_ptr_ = 0;
  bool maybe_full_ = false;
  std::array<SmallFtqBpdUpdate, 2> payloads_{};
  std::uint32_t ver_ = 1;
};

// ---------------------------------------------------------------------------
// Return-address stack storage.
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// F0-F2 fetch control (s0 selection, s1/s2 pipeline registers).
// ---------------------------------------------------------------------------
struct F0F2In {
  bool reset = false;
  std::uint64_t reset_vector = UINT64_C(0x10040);
  bool f3_enq_ready = false;
  bool icache_resp_valid = false;
  std::uint64_t icache_resp_data = 0;
  const SmallFrontendTlbResponse* tlb = nullptr;
  const SmallFrontendPredictionResponse* bpd_f1 = nullptr;
  const SmallFrontendPredictionResponse* bpd_f2 = nullptr;
  bool f3_deq_valid = false, f4_ready = false;
  std::uint64_t f3_predicted_target = 0;
  const SmallGlobalHistory* f3_predicted_ghist = nullptr;
  std::uint8_t f3_fsrc = 0;
  bool f3_xcpt_pf_if = false, f3_xcpt_ae_if = false;
  bool sfence_valid = false; std::uint64_t sfence_addr = 0;
  bool redirect_flush = false, redirect_valid = false;
  std::uint64_t redirect_pc = 0;
  const SmallGlobalHistory* redirect_ghist = nullptr;
};

struct F0F2Eval {
  components::SmallF0F2Outputs out{};
  bool s0_valid = false;
  std::uint64_t s0_vpc = 0;
  SmallGlobalHistory s0_ghist{};
  std::uint8_t s0_tsrc = 0;
  bool s0_is_replay = false, s0_is_sfence = false, s0_s1_use_f3_bpd_resp = false;
  SmallFrontendTlbResponse s1_tlb{};
  std::uint64_t s1_ppc = 0;
  bool s1_tlb_miss = false;
  SmallGlobalHistory next_s2_ghist{};
};

class F0F2 {
 public:
  using S1 = components::SmallF1PipelineState;
  using S2 = components::SmallF2PipelineState;
  void evaluate(const F0F2In& in, F0F2Eval& r) const;
  void commit(bool reset, const F0F2Eval& e) {
    S1 n1;
    n1.vpc = e.s0_vpc; n1.valid = e.s0_valid; n1.ghist = e.s0_ghist;
    n1.is_replay = e.s0_is_replay; n1.is_sfence = e.s0_is_sfence; n1.tsrc = e.s0_tsrc;
    S2 n2;
    n2.vpc = s1_.vpc; n2.valid = s1_.valid && !e.out.f1_clear; n2.ghist = e.next_s2_ghist;
    n2.ppc = e.s1_ppc; n2.tlb = e.s1_tlb; n2.tlb_miss = e.s1_tlb_miss;
    n2.replay_reg = s1_.is_replay; n2.tsrc = s1_.tsrc;
    if (reset) { n1.valid = false; n2.valid = false; }
    replay_tlb_ = s2_.tlb;
    replay_ppc_ = s2_.ppc;
    s1_ = n1;
    s2_ = n2;
    previous_reset_ = reset;
  }
  const S1& s1() const { return s1_; }
  const S2& s2() const { return s2_; }
  static bool s2_exception(const S2& s2) {
    return s2.valid && (s2.tlb.xcpt_ae_if || s2.tlb.xcpt_pf_if) && !s2.is_replay();
  }
  bool held_s2_kill() const { return s2_exception(s2_); }
  bool previous_reset() const { return previous_reset_; }

 private:
  static constexpr std::uint8_t kBsrc1 = 0, kBsrc2 = 1, kBsrc3 = 2, kBsrcCore = 3;
  struct Decision {
    std::uint8_t branches = 0, redirect_idx = 3;
    bool do_redirect = false;
    std::uint64_t target = 0;
    SmallGlobalHistory ghist{};
  };
  static bool histories_differ(const SmallGlobalHistory& a, const SmallGlobalHistory& b) {
    return a.old_history != b.old_history || a.new_saw_branch_not_taken != b.new_saw_branch_not_taken ||
           a.new_saw_branch_taken != b.new_saw_branch_taken;
  }
  static void prediction(bool stage_valid, std::uint64_t pc, const SmallGlobalHistory& h,
                         const SmallFrontendPredictionResponse& resp, Decision& d) {
    d = Decision{};
    // The F0 selection and history correction consume this decision only
    // when its stage is valid. The strict path still projects idle wires.
    if (kArchitecturalModel && !stage_valid) return;
    const std::uint8_t mask = boomcfg::fetch_mask(pc);
    for (std::size_t s = 0; s < 4; ++s) {
      const components::SmallFrontendPrediction& p = resp.preds[s];
      if (p.is_br && p.predicted_pc_valid && ((mask >> s) & 1u)) d.branches |= static_cast<std::uint8_t>(1u << s);
      const bool redirect = stage_valid && ((mask >> s) & 1u) && p.predicted_pc_valid && (p.is_jal || (p.is_br && p.taken));
      if (redirect && !d.do_redirect) { d.do_redirect = true; d.redirect_idx = static_cast<std::uint8_t>(s); }
    }
    const components::SmallFrontendPrediction& sel = resp.preds[d.redirect_idx & 3u];
    d.target = d.do_redirect ? (sel.predicted_pc & kPcMask40) : (boomcfg::fetch_next(pc) & kPcMask40);
    // update_history
    const unsigned cfi_fixed = d.redirect_idx & 3u;
    const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
    const std::uint8_t selected = d.do_redirect ? static_cast<std::uint8_t>((cfi_oh << 1) - 1u) : kFetchMask;
    const bool cfi_taken = sel.taken && d.do_redirect;
    const std::uint8_t taken_cfi = (sel.is_br && cfi_taken) ? cfi_oh : 0u;
    const std::uint8_t not_taken = static_cast<std::uint8_t>(d.branches & selected & static_cast<std::uint8_t>(~taken_cfi));
    advance_global_history(h, not_taken, sel.is_br, cfi_taken, d.do_redirect, cfi_fixed, pc, d.ghist);
    d.ghist.ras_idx = h.ras_idx;
  }

  S1 s1_{};
  S2 s2_{};
  SmallFrontendTlbResponse replay_tlb_{};
  std::uint64_t replay_ppc_ = 0;
  bool previous_reset_ = false;
};

inline void F0F2::evaluate(const F0F2In& in, F0F2Eval& r) const {
  constexpr std::uint64_t kPaddrMask = UINT64_C(0xffffffff);
  components::SmallF0F2Outputs& o = r.out;
  o = components::SmallF0F2Outputs{};
  r.s0_valid = false; r.s0_vpc = 0; r.s0_ghist = SmallGlobalHistory{}; r.s0_tsrc = 0;
  r.s0_is_replay = false; r.s0_is_sfence = false; r.s0_s1_use_f3_bpd_resp = false;

  const SmallFrontendTlbResponse& tlb = *in.tlb;
  r.s1_tlb = s1_.is_replay ? replay_tlb_ : tlb;
  r.s1_ppc = (s1_.is_replay ? replay_ppc_ : tlb.paddr) & kPaddrMask;
  r.s1_tlb_miss = !s1_.is_replay && tlb.miss;
  r.next_s2_ghist = s1_.ghist;

  const bool s1_fault = r.s1_tlb.xcpt_ae_if || r.s1_tlb.xcpt_pf_if;
  const bool s2_replay = s2_.is_replay();
  const bool s2_fault = s2_.tlb.xcpt_ae_if || s2_.tlb.xcpt_pf_if;
  const bool s2_xcpt = s2_exception(s2_);

  Decision f1, f2;
  prediction(s1_.valid, s1_.vpc, s1_.ghist, *in.bpd_f1, f1);
  prediction(s2_.valid, s2_.vpc, s2_.ghist, *in.bpd_f2, f2);

  if (previous_reset_ && !in.reset) {
    r.s0_valid = true;
    r.s0_vpc = in.reset_vector & kPcMask40;
    r.s0_ghist = SmallGlobalHistory{};
    r.s0_tsrc = kBsrcCore;
  }
  if (s1_.valid && !r.s1_tlb_miss) {
    r.s0_valid = !s1_fault;
    r.s0_vpc = f1.target;
    r.s0_ghist = f1.ghist;
    r.s0_is_replay = false;
    r.s0_tsrc = kBsrc1;
  }
  o.f2_correct_f1_ghist = histories_differ(s1_.ghist, f2.ghist);
  std::uint8_t s2_fsrc = kBsrc1;
  const bool f2_stall = (s2_.valid && !in.icache_resp_valid) || (s2_.valid && in.icache_resp_valid && !in.f3_enq_ready);
  if (f2_stall) {
    r.s0_valid = !s2_fault || s2_replay || s2_.tlb_miss;
    r.s0_vpc = s2_.vpc;
    r.s0_is_replay = s2_.valid && in.icache_resp_valid;
    r.s0_s1_use_f3_bpd_resp = !s2_replay;
    r.s0_ghist = s2_.ghist;
    r.s0_tsrc = s2_.tsrc;
    o.f1_clear = true;
  } else if (s2_.valid && in.f3_enq_ready) {
    if (s1_.valid && s1_.vpc == f2.target && !o.f2_correct_f1_ghist) r.next_s2_ghist = f2.ghist;
    if (!s1_.valid || s1_.vpc != f2.target || o.f2_correct_f1_ghist) {
      o.f1_clear = true;
      r.s0_valid = !(s2_fault && !s2_replay);
      r.s0_vpc = f2.target;
      r.s0_is_replay = false;
      r.s0_ghist = f2.ghist;
      r.s0_tsrc = kBsrc2;
      s2_fsrc = kBsrc2;
    }
  }
  const SmallGlobalHistory& f3g = *in.f3_predicted_ghist;
  o.f3_correct_f1_ghist = histories_differ(s1_.ghist, f3g);
  o.f3_correct_f2_ghist = histories_differ(s2_.ghist, f3g);
  const bool f3_fire = in.f3_deq_valid && in.f4_ready;
  bool f3_restarted = false, f3_overrides_enq_ghist = false;
  if (f3_fire) {
    if (s2_.valid && s2_.vpc == in.f3_predicted_target && !o.f3_correct_f2_ghist) {
      f3_overrides_enq_ghist = true;
    } else if (!s2_.valid && s1_.valid && s1_.vpc == in.f3_predicted_target && !o.f3_correct_f1_ghist) {
      r.next_s2_ghist = f3g;
    } else {
      o.f2_clear = true;
      o.f1_clear = true;
      r.s0_valid = !(in.f3_xcpt_pf_if || in.f3_xcpt_ae_if);
      r.s0_vpc = in.f3_predicted_target & kPcMask40;
      r.s0_is_replay = false;
      r.s0_ghist = f3g;
      r.s0_tsrc = kBsrc3;
      f3_restarted = true;
    }
  }
  if (in.sfence_valid) {
    o.f1_clear = true; o.f2_clear = true;
    r.s0_valid = false;
    r.s0_vpc = in.sfence_addr & kPcMask40;
    r.s0_is_replay = false;
    r.s0_is_sfence = true;
  } else if (in.redirect_flush) {
    o.f1_clear = true; o.f2_clear = true;
    r.s0_valid = in.redirect_valid;
    r.s0_vpc = in.redirect_pc & kPcMask40;
    r.s0_ghist = *in.redirect_ghist;
    r.s0_tsrc = kBsrcCore;
    r.s0_is_replay = false;
  }
  o.icache_req_valid = r.s0_valid;
  o.icache_req_addr = r.s0_vpc & ((UINT64_C(1) << 39) - 1);
  o.bpd_f0_ghist = r.s0_ghist;
  o.s0_is_replay = r.s0_is_replay;
  o.s0_is_sfence = r.s0_is_sfence;
  o.s0_s1_use_f3_bpd_resp = r.s0_s1_use_f3_bpd_resp;
  o.tlb_req_valid = (s1_.valid && !s1_.is_replay && !o.f1_clear) || s1_.is_sfence;
  o.tlb_req_vaddr = s1_.vpc;
  o.icache_s1_paddr = r.s1_ppc;
  o.icache_s1_kill = tlb.miss || o.f1_clear;
  o.icache_s2_kill = s2_xcpt;
  o.f3_enq_valid = s2_.valid && !o.f2_clear && (in.icache_resp_valid || (s2_fault && !s2_.tlb_miss));
  o.f3_enq.pc = s2_.vpc & kPcMask40;
  o.f3_enq.data = s2_xcpt ? 0 : in.icache_resp_data;
  o.f3_enq.mask = boomcfg::fetch_mask(s2_.vpc);
  o.f3_enq.xcpt_pf_if = s2_.tlb.xcpt_pf_if;
  o.f3_enq.xcpt_ae_if = s2_.tlb.xcpt_ae_if;
  o.f3_enq.ghist = f3_overrides_enq_ghist ? f3g : s2_.ghist;
  o.f3_enq.fsrc = s2_fsrc;
  o.final_fsrc = f3_restarted ? kBsrc3 : static_cast<std::uint8_t>(in.f3_fsrc & 3u);
}

}  // namespace chisa::boom_model::fe
