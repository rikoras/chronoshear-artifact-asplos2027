#pragma once
#if defined(CHISA_WIDE_MODEL)
#include "predictor_cut_config.h"
#if !defined(CHISA_PREDICTOR_TAIL_CUT) || !defined(CHISA_FRONTEND_EXTRA_CUT)
#error "regenerate predictor_cut_config.h with the current record-fields generator"
#endif
#else
#define CHISA_PREDICTOR_TAIL_CUT 0
#define CHISA_FRONTEND_EXTRA_CUT 0
#endif
// ==========================================================================
// model frontend: the branch-predictor bank (loop, TAGE, BTB, FA-uBTB, BIM
// and the composer) rewritten as one component.
//
// What changed against the five separate components:
//   * the F0->S1 pipeline registers and the registered update are shared
//     (the RTL clocks five identical copies; the model keeps one);
//   * the response composition is done in place: one F1/F2/F3 response
//     triple is written by the components in composer order instead of
//     being copied through four input/output structures per cycle;
//   * every lookup that is a pure function of the registered request and
//     the storage is memoized on (request, storage version), so a replaying
//     fetch (the common stall) costs a few compares;
//   * the contract streams are written into the model image where the
//     register is written (storage streams at the write site, read-port
//     streams when the read row or the row contents change).
// The register-transfer semantics are the ones qualified in
// guiders/boom-system/components/small_*_predictor.h; only the structure
// changed.
// ==========================================================================
#include <array>
#include <cstddef>
#include <cstdint>

#include "boom_config.h"
#include "../../boom-system/components/small_f0_f2.h"   // response types
#include "../../boom-system/components/small_ftq.h"     // SmallFtqBpdUpdate
#include "predictor_bank_image.h"
#include "model_mode.h"

namespace chisa::boom_model::fe {

namespace components = chisa::boom_system::components;
using components::SmallFrontendPrediction;
using components::SmallFrontendPredictionResponse;
using components::SmallFtqBpdUpdate;
using components::SmallBpdResponse;

constexpr std::uint64_t kPc40 = (UINT64_C(1) << 40) - 1;
constexpr unsigned kIdxWidth = 40u - static_cast<unsigned>(boomcfg::FETCH_IDX_SHIFT);  // 37
constexpr std::uint64_t kIdxMask = (UINT64_C(1) << kIdxWidth) - 1;

inline std::uint64_t fetch_index(std::uint64_t pc) {
  return ((pc & kPc40) >> boomcfg::FETCH_IDX_SHIFT) & kIdxMask;
}
// XOR-reduce the history's width-bit chunks with a logarithmic shift tree.
// TAGE uses history lengths <= 64 and widths 7/8/9; truncate the partial
// high chunk before folding, exactly as the original per-chunk loop did.
inline std::uint64_t fold_tage_history(std::uint64_t history, unsigned length, unsigned width) {
  history &= length == 64 ? UINT64_MAX : (UINT64_C(1) << length) - 1u;
  if (length > 8u * width) history ^= history >> (8u * width);
  if (length > 4u * width) history ^= history >> (4u * width);
  if (length > 2u * width) history ^= history >> (2u * width);
  if (length > width) history ^= history >> width;
  return history & ((UINT64_C(1) << width) - 1u);
}
inline std::uint8_t sat2(std::uint8_t v, bool up) {
  v &= 3u;
  if (up) return v == 3 ? 3 : static_cast<std::uint8_t>(v + 1);
  return v == 0 ? 0 : static_cast<std::uint8_t>(v - 1);
}
inline std::uint8_t sat3(std::uint8_t v, bool up) {
  v &= 7u;
  if (up) return v == 7 ? 7 : static_cast<std::uint8_t>(v + 1);
  return v == 0 ? 0 : static_cast<std::uint8_t>(v - 1);
}
inline std::int16_t sext13(std::uint16_t bits) {
  bits &= 0x1fffu;
  if (bits & 0x1000u) bits |= 0xe000u;
  return static_cast<std::int16_t>(bits);
}
inline std::uint64_t add_offset(std::uint64_t pc, std::size_t slot, std::int16_t off) {
  return (pc + static_cast<std::uint64_t>(slot << 1) +
          static_cast<std::uint64_t>(static_cast<std::int64_t>(off))) & kPc40;
}

/** Per-cycle inputs of the bank (the request, the S1 history for TAGE, the
  * F3 bpd-queue fire for the loop predictor, and the update). */
struct BpdIn {
  bool reset = false;
  bool f0_valid = false;
  std::uint64_t f0_pc = 0;        // raw icache request address (bank 0 aligns it)
  std::uint64_t f1_ghist = 0;     // s1.ghist.old_history
  bool f3_fire = false;           // f3 bpd queue enqueue fire
  bool update_valid = false;
  const SmallFtqBpdUpdate* update = nullptr;   // the update path's output
};

// ---- TAGE table update as the parent registers it (tage.scala) -----------
struct TageTableUpdate {
  bool active = false;            // any mask / u_mask bit (idle tables skip)
  std::uint8_t mask = 0;          // 4 lanes
  std::uint8_t taken = 0;
  std::uint8_t alloc = 0;
  std::uint8_t u_mask = 0;
  std::array<std::uint8_t, 4> old_ctr{};
  std::array<std::uint8_t, 4> u{};
  std::uint64_t pc = 0;
  std::uint64_t history = 0;
};

struct TageResp { std::uint8_t valid = 0, ctr = 0, u = 0; };

class TageTable {
 public:
  void init(std::uint16_t rows, std::uint8_t tag_bits, std::uint8_t hist_len);
  // One clock edge with the registered update and the F1 request.
  void step(bool reset, bool f1_valid, std::uint64_t f1_pc, std::uint64_t f1_hist,
            const TageTableUpdate& u);
  const std::array<TageResp, 4>& resp() const { return f3_resp_; }
  bool resp_changed() const { return resp_changed_; }

  // Contract faces.
  std::uint8_t doing_reset() const { return doing_reset_; }
  std::uint16_t reset_index() const { return reset_index_; }
  std::uint8_t bypass_enq_idx() const { return bypass_enq_idx_; }
  std::uint64_t packed_bypass() const;                      // wrbypass__v2_bank_0_0
  std::uint16_t read_data(std::size_t slot) const { return mport_[slot]; }
  std::uint8_t use_lo(std::size_t slot) const { return use_lo_[slot]; }
  std::uint8_t use_hi(std::size_t slot) const { return use_hi_[slot]; }
  bool ports_changed() const { return ports_changed_; }
  bool bypass_changed() const { return bypass_changed_; }
  std::uint16_t rows() const { return rows_; }

 private:
  // Each entry needs at most 13 bits (valid, 9-bit tag, 3-bit counter).
  // Keep it in one host halfword instead of a padded six-byte structure;
  // the same representation also serves the read-port oracle.
  struct Row { std::array<std::uint16_t, 4> e{}; std::uint8_t hi = 0, lo = 0; };
  struct Hash { std::uint16_t index = 0, tag = 0; };

  std::uint64_t fold(std::uint64_t h, unsigned width) const;
  Hash hash(std::uint64_t pc, std::uint64_t h) const;
  std::uint16_t packed_entry(std::uint16_t tag, std::uint8_t ctr) const {
    return static_cast<std::uint16_t>(valid_bit_ | ((tag & tag_mask_) << 3u) | (ctr & 7u));
  }
  void refresh_ports(std::uint16_t mport_row);

  std::uint16_t rows_ = 128, row_mask_ = 127, tag_mask_ = 127;
  std::uint16_t valid_bit_ = 1u << 10u, match_mask_ = (1u << 11u) - 8u;
  std::uint8_t tag_bits_ = 7, hist_len_ = 2, index_bits_ = 7;
  std::uint32_t clear_mask_ = (1u << 19) - 1;
  std::array<Row, 256> t_{};

  std::uint16_t read_row_ = 0;
  std::uint16_t s2_tag_ = 0;
  bool s2_valid_ = false;  // the next F3 response belongs to this accepted F1 request
  std::array<TageResp, 4> f3_resp_{};
  bool resp_changed_ = false;
  std::uint32_t resp_key_ = ~0u;       // (read_row, s2_tag, reset)
  bool resp_valid_ = false;           // only writes to the cached row invalidate it
  // query memo (pc, hist) -> hash
  std::uint64_t q_pc_ = 0, q_hist_ = 0; Hash q_hash_{}; bool q_valid_ = false;
  // read-port faces
  std::array<std::uint16_t, 4> mport_{};
  std::array<std::uint8_t, 4> use_lo_{}, use_hi_{};
  std::uint16_t mport_row_ = 0xffff, use_row_ = 0xffff;
  bool ports_changed_ = false;

  std::uint8_t doing_reset_ = 1;
  std::uint16_t reset_index_ = 0;
  std::uint32_t clear_u_counter_ = 0;
  std::array<std::uint16_t, 2> bypass_tag_{}, bypass_idx_{};
  std::array<std::array<std::uint8_t, 4>, 2> bypass_val_{};
  std::uint8_t bypass_enq_idx_ = 0;
  bool bypass_changed_ = false;
};

// ---- loop predictor column (loop.scala) -----------------------------------
struct LoopEntry {
  std::uint16_t tag = 0; std::uint8_t conf = 0, age = 0; std::uint16_t p_cnt = 0, s_cnt = 0;
  bool operator==(const LoopEntry& o) const {
    return tag == o.tag && conf == o.conf && age == o.age && p_cnt == o.p_cnt && s_cnt == o.s_cnt;
  }
  bool operator!=(const LoopEntry& o) const { return !(*this == o); }
};

class PredictorBank {
 public:
  PredictorBank(PredictorBankRegisters& registers, PredictorBankPorts& ports
#if CHISA_PREDICTOR_TAIL_CUT
                ,unsigned bank=0,void* record_image=nullptr
#endif
                );

  /** Compose this cycle's F1/F2/F3 responses from the registered state.
    * Idempotent until commit(). */
  void evaluate();
  void commit(const BpdIn& in);

  const SmallFrontendPredictionResponse& f1() const { return f1_; }
  const SmallFrontendPredictionResponse& f2() const { return f2_; }
  const SmallFrontendPredictionResponse& f3() const { return f3_; }
  std::uint64_t f1_pc() const { return f1_pc_; }
  std::uint64_t f2_pc() const { return f2_pc_; }
  std::uint64_t f3_pc() const { return f3_pc_; }
  const SmallBpdResponse& f3_response() const { return f3_resp_; }
  const std::array<std::uint32_t, boomcfg::BPD_META_WORDS>& f3_meta() const { return f3_resp_.meta; }
  const SmallFtqBpdUpdate& registered_update() const { return s1_upd_; }

  const auto& request_valid() const { return s1_valid_; }
  const auto& request_pc() const { return s1_pc_; }
  const auto& update_valid() const { return s1_upd_valid_; }
  const auto& update_index() const { return s1_upd_idx_; }
  std::uint64_t update_metadata(unsigned component) const {
    const unsigned shift[5]={73,17,16,8,0};
    const unsigned width[5]={40,56,1,8,8};
    const unsigned __int128 packed=(static_cast<unsigned __int128>(s1_upd_.meta[3])<<96) |
        (static_cast<unsigned __int128>(s1_upd_.meta[2])<<64) |
        (static_cast<unsigned __int128>(s1_upd_.meta[1])<<32) | s1_upd_.meta[0];
    return static_cast<std::uint64_t>(packed>>shift[component]) & ((UINT64_C(1)<<width[component])-1);
  }
  const auto& random_state(unsigned slot) const { return lfsr_[slot]; }
  const auto& btb_registered_f3(unsigned slot) const { return btb_f3_pred_.preds[slot]; }
  const auto& fa_registered_f3(unsigned slot) const { return fa_f3_.preds[slot]; }
  const auto& fa_registered_f2(unsigned slot) const { return fa_f2_.preds[slot]; }
  const auto& bim_registered_meta() const { return bim_f3_meta_; }
  const auto& bim_read_valid() const { return bim_s2_valid_; }
  const auto& btb_override_delay(unsigned slot) const { return btb_f3_ovr1_[slot]; }
  const auto& btb_force_delay(unsigned slot) const { return btb_f3_force1_[slot]; }
  const auto& btb_write_way_register() const { return btb_meta1_; }
  const auto& loop_f4_age(unsigned slot) const { return loop_[slot].f4_entry.age; }
  // Partition-cut lanes.
  const auto& loop_f4_conf(unsigned slot) const { return loop_[slot].f4_entry.conf; }
  std::uint16_t tage_reset_index(unsigned table) const { return tage_[table].reset_index(); }
  std::uint16_t bim_reset_index() const { return bim_reset_idx_; }
  const auto& loop_f4_fire(unsigned slot) const { return loop_[slot].f4_fire; }
  const auto& fa_tag(unsigned way,unsigned slot) const { return fa_tag_[slot][way]; }
  const auto& fa_counter(unsigned way,unsigned slot) const { return fa_ctr_[slot][way]; }
  const auto& fa_is_branch(unsigned way,unsigned slot) const { return fa_isbr_[slot][way]; }
  std::uint64_t fa_offset(unsigned way,unsigned slot) const { return static_cast<std::uint16_t>(fa_off_[way][slot])&0x1fffu; }
  const auto& fa_offset_storage(unsigned way,unsigned slot) const { return fa_off_[way][slot]; }

 private:
  static constexpr std::size_t kTables = 6, kWays = 16, kBtbSets = 128, kLoopEntries = 16;
  static constexpr unsigned kBtbTagWidth = kIdxWidth - 7u;
  static constexpr std::uint32_t kBtbTagMask = (UINT32_C(1) << kBtbTagWidth) - 1;

  // ---- shared S1 registers ----
  bool s1_valid_ = false;
  std::uint64_t s1_pc_ = 0;      // bank-aligned, 40-bit
  std::uint64_t s1_idx_ = 0;     // fetch_index(s1_pc_)
  bool s1_upd_valid_ = false;
  SmallFtqBpdUpdate s1_upd_{};
  std::uint64_t s1_upd_idx_ = 0;
  std::uint64_t f1_pc_ = 0, f2_pc_ = 0, f3_pc_ = 0;   // composer pc pipeline (raw pc)

  // ---- composed responses ----
  bool eval_valid_ = false;
  SmallFrontendPredictionResponse f1_{}, f2_{}, f3_{};
  SmallBpdResponse f3_resp_{};
  std::array<bool, 4> f3_taken_tage_{};   // loop's f3_pred_in

  // ---- FA micro-BTB (component 3) ----
  // [slot][way]: one contiguous tag row per slot for the way compare.
  std::array<std::array<std::uint64_t, kWays>, 4> fa_tag_{};
  std::array<std::array<std::uint8_t, kWays>, 4> fa_isbr_{}, fa_ctr_{};
  std::array<std::array<std::int16_t, 4>, kWays> fa_off_{};
  std::uint8_t fa_fold_ = 0;
  std::uint32_t fa_ver_ = 1;                    // storage version
  SmallFrontendPredictionResponse fa_f2_{}, fa_f3_{};
  std::uint8_t fa_meta1_ = 0, fa_meta2_ = 0;    // f3_meta stage1/2
  // lookup memo
  std::uint64_t fa_m_pc_ = ~UINT64_C(0); bool fa_m_valid_ = false; std::uint32_t fa_m_ver_ = 0;
  std::array<std::uint16_t, 4> fa_hit_oh_{};
  std::uint8_t fa_hit_mask_ = 0, fa_write_way_ = 0, fa_s1_meta_ = 0;
  static std::uint8_t fa_fold_index(std::uint64_t v, unsigned phase);
  void fa_lookup();
  void fa_commit(const BpdIn& in);
  void fa_write_meta_lane(std::size_t way, std::size_t slot);
  void fa_write_meta64_lane();
#if CHISA_PREDICTOR_TAIL_CUT
  void fa_write_cut_lane(std::size_t way,std::size_t slot);
#endif

  // ---- BIM (component 4) ----
  std::array<std::array<std::uint8_t, 4>, 2048> bim_ctr_{};
  bool bim_s2_valid_ = false;
  std::uint16_t bim_addr_ = 0;                       // registered read address
  std::array<std::uint8_t, 4> bim_s2_rdata_{}, bim_port_{}, bim_comb_{};
  int bim_cold_ = 2;
  std::array<bool, 4> bim_f3_taken_{};
  std::uint8_t bim_f3_meta_ = 0;
  bool bim_doing_reset_ = true;
  std::uint16_t bim_reset_idx_ = 0;
  std::array<std::uint16_t, 2> bim_byp_idx_{};
  std::array<std::array<std::uint8_t, 4>, 2> bim_byp_val_{};
  std::uint8_t bim_byp_enq_ = 0;
  std::array<bool, 4> bim_f2_taken_{};              // this cycle's evaluation
  void bim_commit(const BpdIn& in);
  void bim_write_bypass_lane();

  // ---- BTB (component 2) ----
  struct BtbMeta { std::uint32_t tag = 0; std::uint8_t is_br = 0; };
  struct BtbTarget { std::int16_t off = 0; std::uint8_t ext = 0; };
  struct BtbRow {
    std::array<std::array<BtbMeta, 4>, 2> meta{};
    std::array<std::array<BtbTarget, 4>, 2> tgt{};
    std::uint64_t extended = 0;
    std::uint32_t tag_xor = 0, version = 0;
  };
  std::array<BtbRow, kBtbSets> btb_rows_{};
  std::uint8_t btb_read_row_ = 0;
  std::array<bool, 4> btb_f2_ovr_{}, btb_f2_force_{}, btb_f3_ovr1_{}, btb_f3_ovr_{},
      btb_f3_force1_{}, btb_f3_force_{};
  SmallFrontendPredictionResponse btb_f2_pred_{}, btb_f3_pred_{};
  std::uint8_t btb_meta1_ = 0, btb_meta2_ = 0;
  bool btb_doing_reset_ = true;
  std::uint8_t btb_reset_idx_ = 0;
  // lookup memo
  std::uint64_t btb_m_pc_ = ~UINT64_C(0); bool btb_m_valid_ = false, btb_m_reset_ = true;
  std::uint8_t btb_m_row_ = 0xff; std::uint32_t btb_m_ver_ = 0;
  std::uint8_t btb_hit_mask_ = 0, btb_write_way_ = 0;
  std::array<std::uint8_t, 4> btb_hit_way_{};
  SmallFrontendPredictionResponse btb_s1_resp_{};
  std::uint8_t btb_port_row_ = 0xff;             // row the port faces show
  void btb_lookup();
  void btb_commit(const BpdIn& in);
  void btb_write_port_lanes();

  // ---- TAGE (component 1) ----
  std::array<TageTable, kTables> tage_{};
  std::array<TageTableUpdate, kTables> tage_upd_{};   // registered parent update
  bool tage_upd_any_ = false;                          // some table update is active
  std::array<std::uint8_t, 4> lfsr_{};
  // provider memo: (responses, alternate base) -> per-slot decision
  bool tage_m_valid_ = false; std::uint8_t tage_m_alt_ = 0;
  struct TageSlot {
    bool pred = false, prov_valid = false, alt_differs = false;
    std::uint8_t prov = 0, prov_u = 0, prov_ctr = 0, allocatable = 0;
  };
  std::array<TageSlot, 4> tage_slot_{};
  std::uint64_t tage_provider_meta_ = 0;         // unchanged until provider inputs change
  std::uint64_t tage_meta_ = 0;                  // this cycle's 56-bit local metadata
  void tage_evaluate(std::uint8_t alt_taken);
  void tage_commit(const BpdIn& in);
  void tage_compute_updates(std::array<TageTableUpdate, kTables>& out) const;
  static std::uint8_t tage_prio(std::uint8_t bits);

  // ---- loop (component 0) ----
  struct LoopColumn {
    std::array<LoopEntry, kLoopEntries> e{};
    bool doing_reset = true; std::uint8_t reset_idx = 0;
    LoopEntry f3_entry{}; std::uint64_t f3_index = 0; std::uint16_t f3_tag = 0;
    bool f4_fire = false; LoopEntry f4_entry{}; std::uint16_t f4_tag = 0, f4_scnt = 0;
    std::uint64_t f4_index1 = 0, f4_idx = 0;
    // read ports (post-step)
    LoopEntry s2_port{}, upd_port{};
  };
  std::array<LoopColumn, 4> loop_{};
  std::uint64_t loop_s2_idx_ = 0;
  bool loop_s2_valid_ = false, loop_s3_valid_ = false;
  std::uint8_t loop_s1_mask_ = 0x0f, loop_s2_mask_ = 0, loop_s3_mask_ = 0;
  std::array<bool, 4> loop_f2_br_{};
  // this cycle's column decisions
  struct LoopEval { std::uint16_t f3_meta_s_cnt = 0; bool overrides = false; };
  std::array<LoopEval, 4> loop_ev_{};
  void loop_evaluate();
  void loop_commit(const BpdIn& in);
  static LoopEntry loop_trained(const LoopEntry& old, std::uint16_t tag, std::uint16_t cnt);
  static LoopEntry loop_norm(LoopEntry e) {
    e.tag &= 0x3ff; e.conf &= 7; e.age &= 7; e.p_cnt &= 0x3ff; e.s_cnt &= 0x3ff; return e;
  }

  // ---- image lane pointers (named fields) ----
  PredictorBankRegisters& R_;
  PredictorBankPorts& C_;
#if CHISA_PREDICTOR_TAIL_CUT
  unsigned bank_id_=0;
  void* record_image_=nullptr;
#endif
  std::array<std::array<std::uint64_t*, 4>, 13> fa_meta_lane_{};
  std::array<std::uint64_t*, 4> fa_f2_pc_lane_{};
  std::array<std::uint8_t*, 4> fa_f2_valid_lane_{};
  std::array<std::uint8_t*, 4> bim_f3_lane_{};
  std::array<std::array<std::uint32_t*, 4>, 2> btb_meta_lane_{};
  std::array<std::array<std::uint16_t*, 4>, 2> btb_tgt_lane_{};
  std::array<std::uint64_t*, 4> btb_f2_pc_lane_{};
  std::array<std::uint8_t*, 4> btb_f2_valid_lane_{}, btb_f2_br_lane_{}, btb_f2_jal_lane_{},
      btb_f2_ovr_lane_{}, btb_f2_force_lane_{}, btb_f3_ovr_lane_{}, btb_f3_force_lane_{};
  std::array<std::array<std::uint8_t*, 12>, kTables> tage_resp_lane_{};
  std::array<std::uint64_t*, kTables> tage_byp_lane_{};
  std::array<std::uint16_t*, kTables> tage_mport_lane_{};
  std::array<std::uint8_t*, kTables> tage_hi_lane_{}, tage_lo_lane_{};
  std::array<std::uint8_t*, 4> lfsr_lane_{};
  void bind_lanes();
  void write_update_lanes();
  void write_loop_port_lanes(std::size_t lane);
};

}  // namespace chisa::boom_model::fe
