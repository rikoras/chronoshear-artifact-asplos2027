// model frontend: branch-predictor bank.  See bpd.h.
#include "predictor_bank.h"
#if CHISA_PREDICTOR_TAIL_CUT
#include "record_fields.h"
#endif

#include <cstring>

namespace chisa::boom_model::fe {

namespace {
inline std::uint8_t b(bool v) { return v ? 1u : 0u; }
}  // namespace

// ===========================================================================
// construction / lane binding
// ===========================================================================
PredictorBank::PredictorBank(PredictorBankRegisters& registers, PredictorBankPorts& ports
#if CHISA_PREDICTOR_TAIL_CUT
                             ,unsigned bank,void* record_image
#endif
                             )
    : R_(registers), C_(ports)
#if CHISA_PREDICTOR_TAIL_CUT
      ,bank_id_(bank),record_image_(record_image)
#endif
{
  tage_[0].init(128, 7, 2);
  tage_[1].init(128, 7, 4);
  tage_[2].init(256, 8, 8);
  tage_[3].init(256, 8, 16);
  tage_[4].init(128, 9, 32);
  tage_[5].init(128, 9, 64);
  bind_lanes();
}

void PredictorBank::bind_lanes() {
#define FA_META(w, s, k) fa_meta_lane_[w][s] = &R_.banked_predictors_0_components_3_metabank_##k##_0;
  FA_META(0,0,0) FA_META(1,0,1) FA_META(2,0,2) FA_META(3,0,3) FA_META(4,0,4) FA_META(5,0,5)
  FA_META(6,0,6) FA_META(7,0,7) FA_META(8,0,8) FA_META(9,0,9) FA_META(10,0,10) FA_META(11,0,11)
  FA_META(12,0,12)
  FA_META(0,1,16) FA_META(1,1,17) FA_META(2,1,18) FA_META(3,1,19) FA_META(4,1,20) FA_META(5,1,21)
  FA_META(6,1,22) FA_META(7,1,23) FA_META(8,1,24) FA_META(9,1,25) FA_META(10,1,26) FA_META(11,1,27)
  FA_META(12,1,28)
  FA_META(0,2,32) FA_META(1,2,33) FA_META(2,2,34) FA_META(3,2,35) FA_META(4,2,36) FA_META(5,2,37)
  FA_META(6,2,38) FA_META(7,2,39) FA_META(8,2,40) FA_META(9,2,41) FA_META(10,2,42) FA_META(11,2,43)
  FA_META(12,2,44)
  FA_META(0,3,48) FA_META(1,3,49) FA_META(2,3,50) FA_META(3,3,51) FA_META(4,3,52) FA_META(5,3,53)
  FA_META(6,3,54) FA_META(7,3,55) FA_META(8,3,56) FA_META(9,3,57) FA_META(10,3,58) FA_META(11,3,59)
  FA_META(12,3,60)
#undef FA_META
  fa_f2_pc_lane_ = {&R_.banked_predictors_0_components_3_REG_predicted_pc_bits,
                    &R_.banked_predictors_0_components_3_REG_2_predicted_pc_bits,
                    &R_.banked_predictors_0_components_3_REG_4_predicted_pc_bits,
                    &R_.banked_predictors_0_components_3_REG_6_predicted_pc_bits};
  fa_f2_valid_lane_ = {&R_.banked_predictors_0_components_3_REG_predicted_pc_valid,
                       &R_.banked_predictors_0_components_3_REG_2_predicted_pc_valid,
                       &R_.banked_predictors_0_components_3_REG_4_predicted_pc_valid,
                       &R_.banked_predictors_0_components_3_REG_6_predicted_pc_valid};
  bim_f3_lane_ = {&R_.banked_predictors_0_components_4_REG, &R_.banked_predictors_0_components_4_REG_1,
                  &R_.banked_predictors_0_components_4_REG_2, &R_.banked_predictors_0_components_4_REG_3};
  btb_meta_lane_[0] = {&C_.banked_predictors_0_components_2_meta_0_0_MPORT_2,
                       &C_.banked_predictors_0_components_2_meta_0_1_MPORT_2,
                       &C_.banked_predictors_0_components_2_meta_0_2_MPORT_2,
                       &C_.banked_predictors_0_components_2_meta_0_3_MPORT_2};
  btb_meta_lane_[1] = {&C_.banked_predictors_0_components_2_meta_1_0_MPORT_3,
                       &C_.banked_predictors_0_components_2_meta_1_1_MPORT_3,
                       &C_.banked_predictors_0_components_2_meta_1_2_MPORT_3,
                       &C_.banked_predictors_0_components_2_meta_1_3_MPORT_3};
  for (std::size_t s = 0; s < 4; ++s)
    btb_tgt_lane_[0][s] = &C_.banked_predictors_0_components_2_btb_0_MPORT[s];
  btb_tgt_lane_[1] = {&C_.banked_predictors_0_components_2_btb_1_0_MPORT_1,
                      &C_.banked_predictors_0_components_2_btb_1_1_MPORT_1,
                      &C_.banked_predictors_0_components_2_btb_1_2_MPORT_1,
                      &C_.banked_predictors_0_components_2_btb_1_3_MPORT_1};
  btb_f2_pc_lane_ = {&R_.banked_predictors_0_components_2_REG_2_bits,
                     &R_.banked_predictors_0_components_2_REG_14_bits,
                     &R_.banked_predictors_0_components_2_REG_26_bits,
                     &R_.banked_predictors_0_components_2_REG_38_bits};
  btb_f2_valid_lane_ = {&R_.banked_predictors_0_components_2_REG_2_valid,
                        &R_.banked_predictors_0_components_2_REG_14_valid,
                        &R_.banked_predictors_0_components_2_REG_26_valid,
                        &R_.banked_predictors_0_components_2_REG_38_valid};
  btb_f2_br_lane_ = {&R_.banked_predictors_0_components_2_REG_3, &R_.banked_predictors_0_components_2_REG_15,
                     &R_.banked_predictors_0_components_2_REG_27, &R_.banked_predictors_0_components_2_REG_39};
  btb_f2_jal_lane_ = {&R_.banked_predictors_0_components_2_REG_4, &R_.banked_predictors_0_components_2_REG_16,
                      &R_.banked_predictors_0_components_2_REG_28, &R_.banked_predictors_0_components_2_REG_40};
  btb_f2_ovr_lane_ = {&R_.banked_predictors_0_components_2_REG_1, &R_.banked_predictors_0_components_2_REG_13,
                      &R_.banked_predictors_0_components_2_REG_25, &R_.banked_predictors_0_components_2_REG_37};
  btb_f2_force_lane_ = {&R_.banked_predictors_0_components_2_REG_5, &R_.banked_predictors_0_components_2_REG_17,
                        &R_.banked_predictors_0_components_2_REG_29, &R_.banked_predictors_0_components_2_REG_41};
  btb_f3_ovr_lane_ = {&R_.banked_predictors_0_components_2_REG_7, &R_.banked_predictors_0_components_2_REG_19,
                      &R_.banked_predictors_0_components_2_REG_31, &R_.banked_predictors_0_components_2_REG_43};
  btb_f3_force_lane_ = {&R_.banked_predictors_0_components_2_REG_12, &R_.banked_predictors_0_components_2_REG_24,
                        &R_.banked_predictors_0_components_2_REG_36, &R_.banked_predictors_0_components_2_REG_48};
#define TAGE_T(t) \
  tage_resp_lane_[t] = {&R_.banked_predictors_0_components_1_tables_REG[t], \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_1, &R_.banked_predictors_0_components_1_tables_##t##_REG_2, \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_3, &R_.banked_predictors_0_components_1_tables_##t##_REG_4, \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_5, &R_.banked_predictors_0_components_1_tables_##t##_REG_6, \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_7, &R_.banked_predictors_0_components_1_tables_##t##_REG_8, \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_9, &R_.banked_predictors_0_components_1_tables_##t##_REG_10, \
      &R_.banked_predictors_0_components_1_tables_##t##_REG_11}; \
  tage_byp_lane_[t] = &R_.banked_predictors_0_components_1_tables_##t##_wrbypassbank_0_0; \
  tage_mport_lane_[t] = C_.banked_predictors_0_components_1_tables_##t##_table_MPORT; \
  tage_hi_lane_[t] = C_.banked_predictors_0_components_1_tables_##t##_hi_us_s2_req_rhius; \
  tage_lo_lane_[t] = C_.banked_predictors_0_components_1_tables_##t##_lo_us_s2_req_rlous;
  TAGE_T(0) TAGE_T(1) TAGE_T(2) TAGE_T(3) TAGE_T(4) TAGE_T(5)
#undef TAGE_T
  lfsr_lane_ = {&R_.banked_predictors_0_components_1_prng_state_0, &R_.banked_predictors_0_components_1_prng_1_state_0,
                &R_.banked_predictors_0_components_1_prng_2_state_0, &R_.banked_predictors_0_components_1_prng_3_state_0};
}

// ===========================================================================
// evaluate: compose F1/F2/F3 from the registered state
// ===========================================================================
void PredictorBank::evaluate() {
  if (eval_valid_) return;
  eval_valid_ = true;

  // component 3 (FA-uBTB): F1 lookup, registered F2/F3.
  fa_lookup();                 // writes f1_
  f2_ = fa_f2_;
  f3_ = fa_f3_;
  // component 4 (BIM): F2/F3 taken bits.
  for (std::size_t s = 0; s < 4; ++s) {
    bim_f2_taken_[s] = bim_s2_valid_ && ((bim_s2_rdata_[s] >> 1u) & 1u) != 0 && !bim_doing_reset_;
    f2_.preds[s].taken = bim_f2_taken_[s];
    f3_.preds[s].taken = bim_f3_taken_[s];
  }
  // component 2 (BTB): S1 lookup; registered F2/F3 overrides.
  btb_lookup();
  for (std::size_t s = 0; s < 4; ++s) {
    if (btb_f2_ovr_[s]) {
      SmallFrontendPrediction& p = f2_.preds[s];
      const SmallFrontendPrediction& q = btb_f2_pred_.preds[s];
      p.predicted_pc_valid = q.predicted_pc_valid; p.predicted_pc = q.predicted_pc;
      p.is_br = q.is_br; p.is_jal = q.is_jal;
      p.taken = p.taken || btb_f2_force_[s];
    }
    if (btb_f3_ovr_[s]) {
      SmallFrontendPrediction& p = f3_.preds[s];
      const SmallFrontendPrediction& q = btb_f3_pred_.preds[s];
      p.predicted_pc_valid = q.predicted_pc_valid; p.predicted_pc = q.predicted_pc;
      p.is_br = q.is_br; p.is_jal = q.is_jal;
      p.taken = p.taken || btb_f3_force_[s];
    }
  }
  // component 1 (TAGE): F3 taken from the provider.
  std::uint8_t alt = 0;
  for (std::size_t s = 0; s < 4; ++s) alt |= static_cast<std::uint8_t>(b(f3_.preds[s].taken) << s);
  tage_evaluate(alt);
  for (std::size_t s = 0; s < 4; ++s) {
    f3_.preds[s].taken = tage_slot_[s].pred;
    f3_taken_tage_[s] = tage_slot_[s].pred;
  }
  // component 0 (loop): F3 override.
  loop_evaluate();
  std::uint64_t loop_meta = 0;
  for (std::size_t s = 0; s < 4; ++s) {
    f3_.preds[s].taken = loop_ev_[s].overrides ? !f3_taken_tage_[s] : f3_taken_tage_[s];
    loop_meta |= static_cast<std::uint64_t>(loop_ev_[s].f3_meta_s_cnt & 0x3ffu) << (s * 10u);
  }
  // composer metadata: loop | TAGE | BTB | FA | BIM (BIM at bits 0..7).
  std::array<std::uint32_t, 4> m{};
  m[0] = std::uint32_t(bim_f3_meta_) | (std::uint32_t(fa_meta2_) << 8u) | (std::uint32_t(btb_meta2_ & 1u) << 16u);
  {
    const std::uint64_t local = tage_meta_ & ((UINT64_C(1) << 56) - 1);
    m[0] = (m[0] & 0x0001ffffu) | static_cast<std::uint32_t>(local << 17u);
    m[1] = static_cast<std::uint32_t>(local >> 15u);
    m[2] = (m[2] & ~UINT32_C(0x1ff)) | static_cast<std::uint32_t>((local >> 47u) & 0x1ffu);
  }
  {
    const std::uint64_t local = loop_meta & ((UINT64_C(1) << 40) - 1);
    m[2] = (m[2] & 0x1ffu) | static_cast<std::uint32_t>((local & 0x7fffffu) << 9u);
    m[3] = (m[3] & ~UINT32_C(0x1ffff)) | static_cast<std::uint32_t>((local >> 23u) & 0x1ffffu);
  }
  m[3] &= 0x00ffffffu;
  f3_resp_.pc = f3_pc_;
  for (unsigned word=0;word<4;++word) f3_resp_.meta[word]=m[word];
  for (std::size_t s = 0; s < 4; ++s) {
    f3_resp_.preds[s].taken = f3_.preds[s].taken;
    f3_resp_.preds[s].predicted_pc_valid = f3_.preds[s].predicted_pc_valid;
    f3_resp_.preds[s].predicted_pc = f3_.preds[s].predicted_pc & kPc40;
  }
}

// ===========================================================================
// commit: one clock edge
// ===========================================================================
void PredictorBank::commit(const BpdIn& in) {
  evaluate();
  // The five components read the shared S1 registers; each commit reads the
  // pre-edge values, so the shared registers advance last.
  fa_commit(in);
  bim_commit(in);
  btb_commit(in);
  tage_commit(in);
  loop_commit(in);

  const std::uint64_t f0_pc = in.f0_pc & ~UINT64_C(7);   // bankAlign
  s1_valid_ = in.f0_valid;
  s1_pc_ = f0_pc & kPc40;
  s1_idx_ = fetch_index(f0_pc);
  s1_upd_valid_ = in.update_valid;
  // All training consumers qualify this payload with s1_upd_valid_.
  // Retain the previous payload on an idle edge in the relaxed mode.
  if (kInternalSignalContract || in.update_valid) {
    if (in.update != nullptr) {
      s1_upd_ = *in.update;
    } else {
      s1_upd_ = SmallFtqBpdUpdate{};
    }
    s1_upd_.pc = (s1_upd_.pc & ~UINT64_C(7)) & kPc40;
    s1_upd_.target &= kPc40;
    s1_upd_idx_ = fetch_index(s1_upd_.pc);
  }
  f3_pc_ = f2_pc_;
  f2_pc_ = f1_pc_;
  f1_pc_ = in.f0_pc & kPc40;
  write_update_lanes();
  eval_valid_ = false;
}

void PredictorBank::write_update_lanes() {
  const SmallFtqBpdUpdate& u = s1_upd_;
  R_.banked_predictors_0_components_s1_valid[0] = b(s1_valid_);
  R_.banked_predictors_0_components_s1_valid[3] = b(s1_valid_);
  R_.banked_predictors_0_components_s1_valid[4] = b(s1_valid_);
  R_.banked_predictors_0_components_s1_idx[0] = s1_idx_;
  R_.banked_predictors_0_components_s1_idx[2] = s1_idx_;
  R_.banked_predictors_0_components_s1_idx[3] = s1_idx_;
  R_.banked_predictors_0_components_3_s1_pc = s1_pc_;
  R_.banked_predictors_0_components_s1_update_idx[0] = s1_upd_idx_;
  R_.banked_predictors_0_components_s1_update_idx[3] = s1_upd_idx_;
  R_.banked_predictors_0_components_1_s1_update_bits_ghist = u.ghist.old_history;
  const std::uint8_t brm = u.br_mask & 0x0fu;
  R_.banked_predictors_0_components_s1_update_bits_br_mask[0] = brm;
  R_.banked_predictors_0_components_s1_update_bits_br_mask[1] = brm;
  R_.banked_predictors_0_components_s1_update_bits_br_mask[3] = brm;
  const std::uint8_t bm = u.btb_mispredicts & 0x0fu;
  R_.banked_predictors_0_components_s1_update_bits_btb_mispredicts[1] = bm;
  R_.banked_predictors_0_components_s1_update_bits_btb_mispredicts[3] = bm;
  const std::uint8_t ci = u.cfi_idx & 3u;
  R_.banked_predictors_0_components_s1_update_bits_cfi_idx_bits[1] = ci;
  R_.banked_predictors_0_components_s1_update_bits_cfi_idx_bits[3] = ci;
  R_.banked_predictors_0_components_s1_update_bits_cfi_idx_valid[1] = b(u.cfi_valid);
  R_.banked_predictors_0_components_s1_update_bits_cfi_idx_valid[3] = b(u.cfi_valid);
  R_.banked_predictors_0_components_s1_update_bits_cfi_mispredicted[0] = b(u.cfi_mispredicted);
  R_.banked_predictors_0_components_s1_update_bits_cfi_mispredicted[1] = b(u.cfi_mispredicted);
  R_.banked_predictors_0_components_s1_update_bits_cfi_taken[1] = b(u.cfi_taken);
  R_.banked_predictors_0_components_s1_update_bits_cfi_taken[3] = b(u.cfi_taken);
  R_.banked_predictors_0_components_s1_update_bits_is_mispredict_update[1] = b(u.is_mispredict_update);
  R_.banked_predictors_0_components_s1_update_bits_is_mispredict_update[3] = b(u.is_mispredict_update);
  R_.banked_predictors_0_components_s1_update_bits_is_repair_update[0] = b(u.is_repair_update);
  R_.banked_predictors_0_components_s1_update_bits_is_repair_update[1] = b(u.is_repair_update);
  R_.banked_predictors_0_components_s1_update_bits_is_repair_update[3] = b(u.is_repair_update);
  R_.banked_predictors_0_components_3_s1_update_bits_cfi_is_jal = b(u.cfi_is_jal);
}

// ===========================================================================
// FA micro-BTB (component 3)
// ===========================================================================
std::uint8_t PredictorBank::fa_fold_index(std::uint64_t value, unsigned phase) {
  value &= kIdxMask;
  std::uint8_t out = 0;
  for (unsigned j = 0; j < 4; ++j) {
    const std::uint64_t mask = (UINT64_C(0x1111111111111111) << j) & kIdxMask;
    if (__builtin_parityll(value & mask)) out ^= static_cast<std::uint8_t>(1u << ((j + phase) & 3u));
  }
  return out;
}

void PredictorBank::fa_lookup() {
  if (fa_m_ver_ == fa_ver_ && fa_m_pc_ == s1_pc_ && fa_m_valid_ == s1_valid_) return;
  fa_m_ver_ = fa_ver_; fa_m_pc_ = s1_pc_; fa_m_valid_ = s1_valid_;
  std::uint16_t any = 0;
  fa_hit_mask_ = 0;
  for (std::size_t s = 0; s < 4; ++s) {
    std::uint16_t oh = 0;
    const std::uint64_t* tags = fa_tag_[s].data();
    for (std::size_t w = 0; w < kWays; ++w)
      oh |= static_cast<std::uint16_t>(std::uint16_t(tags[w] == s1_idx_) << w);
    fa_hit_oh_[s] = oh;
    any |= oh;
    const bool hit = oh != 0;
    std::uint8_t way = 15;   // PriorityEncoder of zero lowers to 15
    if (hit) way = static_cast<std::uint8_t>(__builtin_ctz(oh));
    const bool is_br = fa_isbr_[s][way] != 0;
    SmallFrontendPrediction& p = f1_.preds[s];
    p.predicted_pc_valid = s1_valid_ && hit;
    p.predicted_pc = add_offset(s1_pc_, s, fa_off_[way][s]);
    p.is_br = p.predicted_pc_valid && is_br;
    p.is_jal = p.predicted_pc_valid && !is_br;
    p.taken = !is_br || ((fa_ctr_[s][way] >> 1u) & 1u) != 0;
    if (hit) fa_hit_mask_ |= static_cast<std::uint8_t>(1u << s);
  }
  const std::uint8_t alloc = static_cast<std::uint8_t>((fa_fold_index(s1_idx_, 0) ^ fa_fold_) & 0x0fu);
  fa_write_way_ = any != 0 ? static_cast<std::uint8_t>(__builtin_ctz(any)) : alloc;
  fa_s1_meta_ = static_cast<std::uint8_t>((fa_hit_mask_ << 4u) | (fa_write_way_ & 0x0fu));
}

void PredictorBank::fa_write_meta_lane(std::size_t way, std::size_t slot) {
  if (way < 13) {
    *fa_meta_lane_[way][slot] = (((fa_tag_[slot][way] & kIdxMask) << 3u) |
                                 (std::uint64_t(fa_isbr_[slot][way] & 1u) << 2u) |
                                 std::uint64_t(fa_ctr_[slot][way] & 3u)) & ((UINT64_C(1) << 40) - 1);
  } else {
    fa_write_meta64_lane();
#if CHISA_PREDICTOR_TAIL_CUT
    fa_write_cut_lane(way,slot);
#endif
  }
}

#if CHISA_PREDICTOR_TAIL_CUT
void PredictorBank::fa_write_cut_lane(std::size_t way,std::size_t slot) {
  if (record_image_) {
    auto& image=*static_cast<wide::contract::Image*>(record_image_);
    wide::write_record(image,wide::fields::bpd_fa_tail_tag[bank_id_][way-13][slot],fa_tag_[slot][way]);
    wide::write_record(image,wide::fields::bpd_fa_tail_is_br[bank_id_][way-13][slot],fa_isbr_[slot][way]);
  }
}
#endif

void PredictorBank::fa_write_meta64_lane() {
  std::uint32_t v = 0;
  unsigned sh = 22;
  for (std::size_t w = 13; w < 16; ++w)
    for (std::size_t s = 0; s < 4; ++s) {
      v |= std::uint32_t(fa_ctr_[s][w] & 3u) << sh;
      sh -= 2;
    }
  R_.banked_predictors_0_components_3_metabank_64_0 = v & 0xffffffu;
}

void PredictorBank::fa_commit(const BpdIn& in) {
  const SmallFtqBpdUpdate& u = s1_upd_;
  const bool commit = !u.is_mispredict_update && !u.is_repair_update && (u.btb_mispredicts & 0x0fu) == 0;
  const std::uint8_t local_meta = static_cast<std::uint8_t>((u.meta[0] >> 8u) & 0xffu);
  const std::uint8_t update_way = local_meta & 0x0fu;
  const std::uint8_t cfi_slot = u.cfi_idx & 3u;
  const std::uint64_t uidx = s1_upd_idx_;

  if (s1_upd_valid_ && commit && u.cfi_valid && u.cfi_taken) {
    const std::uint64_t base = (u.pc + (std::uint64_t(cfi_slot) << 1u)) & kPc40;
    const std::int16_t off = sext13(static_cast<std::uint16_t>((u.target - base) & 0x1fffu));
    if (fa_off_[update_way][cfi_slot] != off) {
      fa_off_[update_way][cfi_slot] = off;
      ++fa_ver_;
      {
      std::uint64_t packed = 0;
      for (std::size_t s = 0; s < 4; ++s)
        packed |= std::uint64_t(static_cast<std::uint16_t>(fa_off_[update_way][s]) & 0x1fffu) << ((3u - s) * 13u);
      R_.banked_predictors_0_components_3_btbbank_0[update_way] = packed & ((UINT64_C(1) << 52) - 1);
      }
    }
  }
  if (s1_upd_valid_ && commit) {
    for (std::size_t s = 0; s < 4; ++s) {
      const bool branch = ((u.br_mask >> s) & 1u) != 0;
      const bool taken_cfi = u.cfi_valid && cfi_slot == s && u.cfi_taken;
      if (!branch && !taken_cfi) continue;
      const bool was_taken = u.cfi_valid && cfi_slot == s && (u.cfi_taken || u.cfi_is_jal);
      std::uint64_t& tag = fa_tag_[s][update_way];
      std::uint8_t& isbr = fa_isbr_[s][update_way];
      std::uint8_t& ctr = fa_ctr_[s][update_way];
      const std::uint64_t prev_tag = tag;
      const std::uint8_t prev_isbr = isbr, prev_ctr = ctr;
      isbr = b(branch);
      const unsigned phase = static_cast<unsigned>(((update_way * 4u + s + 1u) * kIdxWidth) & 3u);
      fa_fold_ = static_cast<std::uint8_t>(fa_fold_ ^ fa_fold_index(tag, phase) ^ fa_fold_index(uidx, phase));
      tag = uidx;
      const bool local_hit = ((local_meta >> (4u + s)) & 1u) != 0;
      ctr = local_hit ? sat2(ctr, was_taken) : (was_taken ? 3u : 0u);
      if (isbr != prev_isbr || tag != prev_tag || ctr != prev_ctr) {
        ++fa_ver_;
        fa_write_meta_lane(update_way, s);
      }
    }
  }

  // pipeline
  fa_f3_ = fa_f2_;
  fa_f2_ = f1_;
  fa_meta2_ = fa_meta1_;
  fa_meta1_ = fa_s1_meta_;
  {
  for (std::size_t s = 0; s < 4; ++s) {
    *fa_f2_pc_lane_[s] = fa_f2_.preds[s].predicted_pc & kPc40;
    *fa_f2_valid_lane_[s] = b(fa_f2_.preds[s].predicted_pc_valid);
  }
  R_.banked_predictors_0_components_3_REG_9 = fa_meta2_;
  }

  if (in.reset) {
    bool changed = false;
    for (std::size_t w = 0; w < kWays; ++w)
      for (std::size_t s = 0; s < 4; ++s) {
        if (fa_isbr_[s][w] || fa_tag_[s][w] != 0 || fa_ctr_[s][w] != 0) {
          fa_isbr_[s][w] = 0; fa_tag_[s][w] = 0; fa_ctr_[s][w] = 0;
          changed = true;
          if (w < 13) fa_write_meta_lane(w, s);
#if CHISA_PREDICTOR_TAIL_CUT
          else fa_write_cut_lane(w,s);
#endif
        }
      }
    if (changed) { ++fa_ver_; fa_write_meta64_lane(); }
    fa_fold_ = 0;
  }
}

// ===========================================================================
// BIM (component 4)
// ===========================================================================
void PredictorBank::bim_write_bypass_lane() {
  std::uint64_t v = (std::uint64_t(bim_byp_idx_[0] & 0x7ffu) << 27) | (std::uint64_t(bim_byp_idx_[1] & 0x7ffu) << 16);
  v |= std::uint64_t(bim_byp_val_[0][0] & 3u) << 14; v |= std::uint64_t(bim_byp_val_[0][1] & 3u) << 12;
  v |= std::uint64_t(bim_byp_val_[0][2] & 3u) << 10; v |= std::uint64_t(bim_byp_val_[0][3] & 3u) << 8;
  v |= std::uint64_t(bim_byp_val_[1][0] & 3u) << 6;  v |= std::uint64_t(bim_byp_val_[1][1] & 3u) << 4;
  v |= std::uint64_t(bim_byp_val_[1][2] & 3u) << 2;  v |= std::uint64_t(bim_byp_val_[1][3] & 3u);
  R_.banked_predictors_0_components_4_wrbypassbank_0_0 = v & ((UINT64_C(1) << 38) - 1);
}

void PredictorBank::bim_commit(const BpdIn& in) {
  const SmallFtqBpdUpdate& u = s1_upd_;
  const std::uint16_t uidx = static_cast<std::uint16_t>((u.pc >> boomcfg::FETCH_IDX_SHIFT) & 0x7ffu);
  const bool is_commit = !u.is_mispredict_update && !u.is_repair_update && (u.btb_mispredicts & 0x0fu) == 0;
  const bool update_write = s1_upd_valid_ && is_commit;
  const bool bypass_hit = !bim_doing_reset_ && (bim_byp_idx_[0] == uidx || bim_byp_idx_[1] == uidx);
  const std::uint8_t hit_idx = (!bim_doing_reset_ && bim_byp_idx_[0] == uidx) ? 0 : 1;
  std::uint8_t wmask = 0;
  std::array<std::uint8_t, 4> wdata{};
  if (update_write) for (std::size_t s = 0; s < 4; ++s) {
    const bool selected = ((u.br_mask >> s) & 1u) != 0 || (u.cfi_valid && (u.cfi_idx & 3u) == s);
    if (selected) wmask |= static_cast<std::uint8_t>(1u << s);
    const bool was_taken = u.cfi_valid && (u.cfi_idx & 3u) == s &&
                           ((u.cfi_is_br && ((u.br_mask >> s) & 1u) != 0 && u.cfi_taken) || u.cfi_is_jal);
    const std::uint8_t old = bypass_hit ? bim_byp_val_[hit_idx][s]
                                        : static_cast<std::uint8_t>((u.meta[0] >> (s * 2u)) & 3u);
    wdata[s] = sat2(old, was_taken);
  }

  // read-before-write of the registered address
  const std::array<std::uint8_t, 4> next_s2 = bim_ctr_[bim_addr_];
  bim_port_ = next_s2;
  const std::array<bool, 4> next_f3_taken = bim_f2_taken_;
  std::uint8_t next_f3_meta = 0;
  for (std::size_t s = 0; s < 4; ++s) next_f3_meta |= static_cast<std::uint8_t>((bim_s2_rdata_[s] & 3u) << (s * 2u));

  if (bim_doing_reset_) {
    bim_ctr_[bim_reset_idx_] = {2, 2, 2, 2};
  } else if (update_write) {
    for (std::size_t s = 0; s < 4; ++s)
      if ((wmask >> s) & 1u) bim_ctr_[uidx][s] = wdata[s];
  }
  if (wmask != 0 && update_write) {
    const std::uint8_t dest = bypass_hit ? hit_idx : bim_byp_enq_;
    bim_byp_val_[dest] = wdata;
    if (!bypass_hit) {
      bim_byp_idx_[dest] = uidx;
      bim_byp_enq_ ^= 1u;
    }
    bim_write_bypass_lane();
  }
  const std::uint16_t next_reset_idx = static_cast<std::uint16_t>((bim_reset_idx_ + (bim_doing_reset_ ? 1u : 0u)) & 0x7ffu);
  const bool next_doing_reset = bim_doing_reset_ && bim_reset_idx_ != 0x7ffu;

  const std::array<std::uint8_t, 4> s2_rdata_now = bim_cold_ != 0 ? bim_s2_rdata_ : next_s2;
  if (bim_cold_ != 0) --bim_cold_; else bim_s2_rdata_ = s2_rdata_now;
  bim_f3_taken_ = next_f3_taken;
  bim_f3_meta_ = next_f3_meta;
  bim_s2_valid_ = s1_valid_;
  if (in.f0_valid) bim_addr_ = static_cast<std::uint16_t>(((in.f0_pc & ~UINT64_C(7)) >> boomcfg::FETCH_IDX_SHIFT) & 0x7ffu);
  bim_reset_idx_ = next_reset_idx;
  bim_doing_reset_ = next_doing_reset;
  if (in.reset) {
    bim_reset_idx_ = 0;
    bim_doing_reset_ = true;
    if (bim_byp_enq_ != 0) { bim_byp_enq_ = 0; }
  }
  // Read the counters of the registered address byte by byte: a whole-row
  // load right after this cycle's byte-wise counter writes to the same row
  // cannot be forwarded and stalls until the writes retire.
  std::array<std::uint8_t, 4> comb_now{};
  if (bim_cold_ != 0) comb_now = bim_port_;
  else for (std::size_t s = 0; s < 4; ++s) comb_now[s] = bim_ctr_[bim_addr_][s];
  bim_comb_ = comb_now;

  // lanes (from the values computed above, not the members just stored)
  for (std::size_t s = 0; s < 4; ++s) {
    R_.banked_predictors_0_components_4_s2_req_rdata[s] = s2_rdata_now[s] & 3u;
    C_.banked_predictors_0_components_4_data_MPORT[s] = comb_now[s] & 3u;
    *bim_f3_lane_[s] = b(next_f3_taken[s]);
  }
  R_.banked_predictors_0_components_4_doing_reset = b(bim_doing_reset_);
  R_.banked_predictors_0_components_4_wrbypass_enq_idx = bim_byp_enq_ & 1u;
}

// ===========================================================================
// BTB (component 2)
// ===========================================================================
void PredictorBank::btb_lookup() {
  const BtbRow& row = btb_rows_[btb_read_row_];
  if (btb_m_ver_ == row.version && btb_m_pc_ == s1_pc_ && btb_m_valid_ == s1_valid_ &&
      btb_m_reset_ == btb_doing_reset_ && btb_m_row_ == btb_read_row_)
    return;
  btb_m_ver_ = row.version; btb_m_pc_ = s1_pc_; btb_m_valid_ = s1_valid_;
  btb_m_reset_ = btb_doing_reset_; btb_m_row_ = btb_read_row_;
  const std::uint32_t tag = static_cast<std::uint32_t>((s1_idx_ >> 7u) & kBtbTagMask);
  std::uint8_t any = 0;
  btb_hit_mask_ = 0;
  for (std::size_t s = 0; s < 4; ++s) {
    std::uint8_t oh = 0;
    if (row.meta[0][s].tag == tag) oh |= 1u;
    if (row.meta[1][s].tag == tag) oh |= 2u;
    any |= oh;
    const bool hit = oh != 0;
    const std::uint8_t way = (oh & 1u) ? 0 : 1;
    btb_hit_way_[s] = way;
    if (hit) btb_hit_mask_ |= static_cast<std::uint8_t>(1u << s);
    const BtbMeta& m = row.meta[way][s];
    const BtbTarget& t = row.tgt[way][s];
    SmallFrontendPrediction& p = btb_s1_resp_.preds[s];
    p.taken = false;
    p.predicted_pc_valid = !btb_doing_reset_ && s1_valid_ && hit;
    p.predicted_pc = t.ext ? row.extended : add_offset(s1_pc_, s, t.off);
    p.is_br = !btb_doing_reset_ && p.predicted_pc_valid && m.is_br != 0;
    p.is_jal = !btb_doing_reset_ && p.predicted_pc_valid && m.is_br == 0;
  }
  // Preserve the RTL's XOR/parity replacement choice. Row tag parity is
  // maintained at writes, so a lookup need not re-read all eight tags.
  const bool alloc = __builtin_parity(tag ^ row.tag_xor) != 0;
  btb_write_way_ = any != 0 ? ((any & 1u) ? 0 : 1) : static_cast<std::uint8_t>(alloc);
}

void PredictorBank::btb_write_port_lanes() {
  const BtbRow& row = btb_rows_[btb_read_row_];
  C_.banked_predictors_0_components_2_ebtb_s1_req_rebtb = row.extended & kPc40;
  for (std::size_t w = 0; w < 2; ++w)
    for (std::size_t s = 0; s < 4; ++s) {
      const BtbMeta& m = row.meta[w][s];
      *btb_meta_lane_[w][s] = ((std::uint32_t(m.is_br & 1u) << kBtbTagWidth) | (m.tag & kBtbTagMask)) & 0x7fffffffu;
      const BtbTarget& t = row.tgt[w][s];
      *btb_tgt_lane_[w][s] = static_cast<std::uint16_t>((((static_cast<std::uint16_t>(t.off) & 0x1fffu) << 1u) | (t.ext & 1u)) & 0x3fffu);
    }
  btb_port_row_ = btb_read_row_;
}

void PredictorBank::btb_commit(const BpdIn& in) {
  const SmallFtqBpdUpdate& u = s1_upd_;
  const bool commit = !u.is_mispredict_update && !u.is_repair_update && (u.btb_mispredicts & 0x0fu) == 0;
  const std::size_t update_way = (u.meta[0] >> 16u) & 1u;
  const std::uint8_t update_row = static_cast<std::uint8_t>(s1_upd_idx_ & 0x7fu);
  const std::uint32_t update_tag = static_cast<std::uint32_t>((s1_upd_idx_ >> 7u) & kBtbTagMask);
  std::uint8_t wbtb = 0;
  if (s1_upd_valid_ && commit && u.cfi_valid && u.cfi_taken) wbtb = static_cast<std::uint8_t>(1u << (u.cfi_idx & 3u));
  const std::uint8_t candidate = static_cast<std::uint8_t>(wbtb | (u.br_mask & 0x0fu));
  const std::uint8_t enable = static_cast<std::uint8_t>((s1_upd_valid_ && commit ? 0x0fu : 0u) |
                                                        (s1_upd_valid_ ? (u.btb_mispredicts & 0x0fu) : 0u));
  const std::uint8_t wmeta = static_cast<std::uint8_t>(candidate & enable);
  // update offset (40-bit signed difference)
  std::int64_t off40;
  {
    const std::uint64_t base = (u.pc + (std::uint64_t(u.cfi_idx & 3u) << 1u)) & kPc40;
    std::uint64_t d = (u.target - base) & kPc40;
    if (d & (UINT64_C(1) << 39)) d |= ~kPc40;
    off40 = static_cast<std::int64_t>(d);
  }
  const bool ext = off40 > 4095 || off40 < -4096;
  const std::int16_t off = sext13(static_cast<std::uint16_t>(static_cast<std::uint64_t>(off40) & 0x1fffu));

  bool wrote = false;
  if (btb_doing_reset_) {
    BtbRow& row = btb_rows_[btb_reset_idx_];
    for (std::size_t w = 0; w < 2; ++w)
      for (std::size_t s = 0; s < 4; ++s) { row.meta[w][s] = BtbMeta{}; row.tgt[w][s] = BtbTarget{}; }
    row.tag_xor = 0;
    ++row.version;
    wrote = true;
  } else if (wbtb != 0 || wmeta != 0) {
    BtbRow& row = btb_rows_[update_row];
    for (std::size_t s = 0; s < 4; ++s) {
      if ((wbtb >> s) & 1u) { row.tgt[update_way][s].off = off; row.tgt[update_way][s].ext = b(ext); }
      if ((wmeta >> s) & 1u) {
        row.meta[update_way][s].is_br = b(((u.br_mask >> s) & 1u) != 0);
        auto& tag = row.meta[update_way][s].tag;
        const auto next_tag = ((u.btb_mispredicts >> s) & 1u) != 0 ? 0u : update_tag;
        row.tag_xor ^= tag ^ next_tag;
        tag = next_tag;
      }
    }
    ++row.version;
    wrote = true;
  }
  if (wbtb != 0 && ext) {
    auto& row = btb_rows_[update_row];
    row.extended = u.target & kPc40;
    ++row.version;
    wrote = true;
  }

  // pipeline registers (from this cycle's evaluation)
  btb_f3_pred_ = f2_;
  btb_f3_ovr_ = btb_f3_ovr1_;
  btb_f3_force_ = btb_f3_force1_;
  for (std::size_t s = 0; s < 4; ++s) {
    btb_f3_ovr1_[s] = ((btb_hit_mask_ >> s) & 1u) != 0;
    btb_f3_force1_[s] = btb_s1_resp_.preds[s].is_jal;
    btb_f2_ovr_[s] = btb_f3_ovr1_[s];
    btb_f2_force_[s] = btb_s1_resp_.preds[s].is_jal;
  }
  btb_f2_pred_ = btb_s1_resp_;
  btb_meta2_ = btb_meta1_;
  btb_meta1_ = btb_write_way_;
  const std::uint8_t prev_read_row = btb_read_row_;
  if (in.f0_valid) btb_read_row_ = static_cast<std::uint8_t>(fetch_index(in.f0_pc & ~UINT64_C(7)) & 0x7fu);
  const std::uint8_t next_reset_idx = static_cast<std::uint8_t>((btb_reset_idx_ + (btb_doing_reset_ ? 1u : 0u)) & 0x7fu);
  const bool next_doing_reset = btb_doing_reset_ && btb_reset_idx_ != 0x7fu;
  btb_reset_idx_ = next_reset_idx;
  btb_doing_reset_ = next_doing_reset;
  if (in.reset) { btb_reset_idx_ = 0; btb_doing_reset_ = true; }

  // lanes
  // btb_f2_pred_ was just copied from btb_s1_resp_ above; read the source,
  // not the fresh copy (store-forwarding).
  for (std::size_t s = 0; s < 4; ++s) {
    *btb_f2_pc_lane_[s] = btb_s1_resp_.preds[s].predicted_pc & kPc40;
    *btb_f2_valid_lane_[s] = b(btb_s1_resp_.preds[s].predicted_pc_valid);
    *btb_f2_br_lane_[s] = b(btb_s1_resp_.preds[s].is_br);
    *btb_f2_jal_lane_[s] = b(btb_s1_resp_.preds[s].is_jal);
    *btb_f2_ovr_lane_[s] = b(btb_f2_ovr_[s]);
    *btb_f2_force_lane_[s] = b(btb_f2_force_[s]);
    *btb_f3_ovr_lane_[s] = b(btb_f3_ovr_[s]);
    *btb_f3_force_lane_[s] = b(btb_f3_force_[s]);
  }
  R_.banked_predictors_0_components_2_f3_meta_write_way = btb_meta2_ & 1u;
  R_.banked_predictors_0_components_2_reset_idx = btb_reset_idx_ & 0x7fu;
  if (wrote || btb_read_row_ != prev_read_row || btb_port_row_ != btb_read_row_) btb_write_port_lanes();
}

// ===========================================================================
// TAGE table
// ===========================================================================
void TageTable::init(std::uint16_t rows, std::uint8_t tag_bits, std::uint8_t hist_len) {
  rows_ = rows; row_mask_ = static_cast<std::uint16_t>(rows - 1u);
  tag_bits_ = tag_bits; tag_mask_ = static_cast<std::uint16_t>((1u << tag_bits) - 1u);
  valid_bit_ = static_cast<std::uint16_t>(1u << (tag_bits + 3u));
  match_mask_ = static_cast<std::uint16_t>(valid_bit_ | (tag_mask_ << 3u));
  hist_len_ = hist_len; index_bits_ = rows == 256 ? 8 : 7;
  clear_mask_ = (UINT32_C(1) << (11u + index_bits_ + 1u)) - 1u;
}

std::uint64_t TageTable::fold(std::uint64_t h, unsigned width) const {
  return fold_tage_history(h, hist_len_, width);
}

TageTable::Hash TageTable::hash(std::uint64_t pc, std::uint64_t h) const {
  const std::uint64_t unhashed = (pc & kPc40) >> boomcfg::FETCH_IDX_SHIFT;
  Hash r;
  const std::uint64_t index_fold = fold(h, index_bits_);
  const std::uint64_t tag_fold = tag_bits_ == index_bits_ ? index_fold : fold(h, tag_bits_);
  r.index = static_cast<std::uint16_t>((unhashed ^ index_fold) & row_mask_);
  r.tag = static_cast<std::uint16_t>(((unhashed >> index_bits_) ^ tag_fold) & tag_mask_);
  return r;
}

std::uint64_t TageTable::packed_bypass() const {
  std::uint64_t v;
  if (tag_bits_ == 7) {
    v = (std::uint64_t(bypass_tag_[0] & 0x7f) << 45) | (std::uint64_t(bypass_idx_[0] & 0x7f) << 38) |
        (std::uint64_t(bypass_tag_[1] & 0x7f) << 31) | (std::uint64_t(bypass_idx_[1] & 0x7f) << 24);
  } else if (tag_bits_ == 8) {
    v = (std::uint64_t(bypass_tag_[0] & 0xff) << 48) | (std::uint64_t(bypass_idx_[0] & 0xff) << 40) |
        (std::uint64_t(bypass_tag_[1] & 0xff) << 32) | (std::uint64_t(bypass_idx_[1] & 0xff) << 24);
  } else {
    v = (std::uint64_t(bypass_tag_[0] & 0x1ff) << 47) | (std::uint64_t(bypass_idx_[0] & 0x7f) << 40) |
        (std::uint64_t(bypass_tag_[1] & 0x1ff) << 31) | (std::uint64_t(bypass_idx_[1] & 0x7f) << 24);
  }
  v |= std::uint64_t(bypass_val_[1][0] & 7u) << 21; v |= std::uint64_t(bypass_val_[0][0] & 7u) << 18;
  v |= std::uint64_t(bypass_val_[1][1] & 7u) << 15; v |= std::uint64_t(bypass_val_[0][1] & 7u) << 12;
  v |= std::uint64_t(bypass_val_[1][2] & 7u) << 9;  v |= std::uint64_t(bypass_val_[0][2] & 7u) << 6;
  v |= std::uint64_t(bypass_val_[1][3] & 7u) << 3;  v |= std::uint64_t(bypass_val_[0][3] & 7u);
  const unsigned width = tag_bits_ == 7 ? 52u : 56u;
  return v & ((UINT64_C(1) << width) - 1u);
}

void TageTable::refresh_ports(std::uint16_t mport_row) {
  const Row& mr = t_[mport_row];
  mport_ = mr.e;
  const Row& ur = t_[read_row_];
  for (std::size_t s = 0; s < 4; ++s) {
    use_lo_[s] = (ur.lo >> s) & 1u;
    use_hi_[s] = (ur.hi >> s) & 1u;
  }
  mport_row_ = mport_row;
  use_row_ = read_row_;
  ports_changed_ = true;
}

void TageTable::step(bool reset, bool f1_valid, std::uint64_t f1_pc, std::uint64_t f1_hist,
                     const TageTableUpdate& u) {
  const bool was_doing_reset = doing_reset_ != 0;
  bypass_changed_ = false;
  ports_changed_ = false;
  resp_changed_ = false;
  if (kArchitecturalModel && !reset && !doing_reset_ && !u.active &&
      !f1_valid && !s2_valid_ && (clear_u_counter_ & 2047u) != 0) {
    clear_u_counter_ = (clear_u_counter_ + 1u) & clear_mask_;
    return;
  }
  if ((kInternalSignalContract || f1_valid) &&
      (!q_valid_ || f1_pc != q_pc_ || f1_hist != q_hist_)) {
    q_hash_ = hash(f1_pc, f1_hist); q_pc_ = f1_pc; q_hist_ = f1_hist; q_valid_ = true;
  }
  const Hash q = q_hash_;

  const bool doing_clear = (clear_u_counter_ & 2047u) == 0;
  const bool clear_hi = doing_clear && ((clear_u_counter_ >> (11u + index_bits_)) & 1u) != 0;
  const bool clear_lo = doing_clear && !clear_hi;
  const std::uint16_t clear_row = static_cast<std::uint16_t>((clear_u_counter_ >> 11u) & row_mask_);

  // F3 response registers capture the pre-write row: a function of the
  // read row, the S2 tag, the reset flag and the row contents.
  if (kInternalSignalContract || s2_valid_) {
    const std::uint32_t key = std::uint32_t(read_row_) | (std::uint32_t(s2_tag_) << 16u) |
                              (std::uint32_t(doing_reset_ & 1u) << 31u);
    if (!resp_valid_ || key != resp_key_) {
      resp_key_ = key;
      resp_valid_ = true;
      const Row& r = t_[read_row_];
      const std::uint16_t wanted = packed_entry(s2_tag_, 0);
      // Build the four responses as three packed 32-bit words in registers
      // and compare/store them word-wise. Byte-wise building followed by a
      // wider read-back, or byte stores merged by the compiler and re-read at
      // another offset, both defeat store-to-load forwarding on this host.
      static_assert(sizeof(TageResp) == 3 && sizeof(f3_resp_) == 12, "packed F3 response layout");
      std::uint32_t next[3] = {0, 0, 0};
      for (std::size_t s = 0; s < 4; ++s) {
        const std::uint32_t valid = b((r.e[s] & match_mask_) == wanted && !doing_reset_);
        const std::uint32_t ctr = r.e[s] & 7u;
        const std::uint32_t u = (((r.hi >> s) & 1u) << 1u) | ((r.lo >> s) & 1u);
        const std::uint32_t packed = valid | (ctr << 8) | (u << 16);  // {valid, ctr, u} bytes
        const std::size_t bit = s * 24u;  // byte offset 3*s, little-endian words
        next[bit / 32] |= packed << (bit % 32);
        if ((bit % 32) > 8) next[bit / 32 + 1] |= packed >> (32 - (bit % 32));
      }
      std::uint32_t cur[3];
      std::memcpy(cur, f3_resp_.data(), sizeof(cur));
      if (cur[0] != next[0] || cur[1] != next[1] || cur[2] != next[2]) {
        std::memcpy(f3_resp_.data(), next, sizeof(next));
        resp_changed_ = true;
      }
    }
  }

  bool row_written = false;
  std::uint16_t written_row = 0xffff, written_row2 = 0xffff;
  const auto mark_write = [&](std::uint16_t row) {
    row_written = true;
    if (written_row == 0xffff || written_row == row) written_row = row;
    else written_row2 = row;
    // f3_resp_ above observed this row BEFORE the write. Rebuild on the
    // following edge if it is still selected; never replace read-old data.
    if (row == read_row_) resp_valid_ = false;
  };
  const auto write_use = [&](std::uint16_t row, bool high, std::uint8_t value) {
    auto& destination = high ? t_[row].hi : t_[row].lo;
    if (destination != value) { destination = value; mark_write(row); }
  };
  const auto write_entry = [&](std::uint16_t row, std::size_t slot, std::uint16_t value) {
    std::uint16_t& destination = t_[row].e[slot];
    if (destination != value) {
      destination = value;
      mark_write(row);
    }
  };
  if (!doing_reset_ && !u.active) {
    if (clear_hi) write_use(clear_row, true, 0);
    if (clear_lo) write_use(clear_row, false, 0);
  } else {
    const Hash uh = hash(u.pc, u.history);
    const bool hit0 = !doing_reset_ && bypass_tag_[0] == uh.tag && bypass_idx_[0] == uh.index;
    const bool hit1 = !doing_reset_ && bypass_tag_[1] == uh.tag && bypass_idx_[1] == uh.index;
    const bool bypass_hit = hit0 || hit1;
    const std::uint8_t hit_idx = hit0 ? 0 : 1;
    std::array<std::uint8_t, 4> ctr{};
    for (std::size_t s = 0; s < 4; ++s) {
      const std::uint8_t old = bypass_hit ? bypass_val_[hit_idx][s] : u.old_ctr[s];
      const bool taken = ((u.taken >> s) & 1u) != 0;
      ctr[s] = ((u.alloc >> s) & 1u) ? static_cast<std::uint8_t>(taken ? 4 : 3) : sat3(old, taken);
    }
    if (doing_reset_) {
      for (std::size_t s = 0; s < 4; ++s) write_entry(reset_index_, s, 0);
      write_use(reset_index_, true, 0);
      write_use(reset_index_, false, 0);
    } else {
      Row& r = t_[uh.index];
      for (std::size_t s = 0; s < 4; ++s) {
        if (!((u.mask >> s) & 1u)) continue;
        write_entry(uh.index, s, packed_entry(uh.tag, ctr[s]));
      }
      if (clear_hi) write_use(clear_row, true, 0);
      else for (std::size_t s = 0; s < 4; ++s)
        if ((u.u_mask >> s) & 1u) {
          write_use(uh.index, true,
              static_cast<std::uint8_t>((r.hi & ~(1u << s)) | (((u.u[s] >> 1u) & 1u) << s)));
        }
      if (clear_lo) write_use(clear_row, false, 0);
      else for (std::size_t s = 0; s < 4; ++s)
        if ((u.u_mask >> s) & 1u) {
          write_use(uh.index, false,
              static_cast<std::uint8_t>((r.lo & ~(1u << s)) | ((u.u[s] & 1u) << s)));
        }
    }
    if (u.mask != 0) {
      const std::uint8_t dest = bypass_hit ? hit_idx : bypass_enq_idx_;
      bypass_val_[dest] = ctr;
      if (!bypass_hit) {
        bypass_tag_[dest] = uh.tag;
        bypass_idx_[dest] = uh.index;
        bypass_enq_idx_ ^= 1u;
      }
      bypass_changed_ = true;
    }
  }

  const std::uint16_t mport_row = f1_valid ? q.index : read_row_;
  if (kInternalSignalContract || f1_valid) s2_tag_ = q.tag;
  s2_valid_ = f1_valid;
  if (f1_valid) read_row_ = q.index;

  const std::uint16_t next_reset_index = static_cast<std::uint16_t>((reset_index_ + (doing_reset_ ? 1u : 0u)) & row_mask_);
  const bool next_doing_reset = doing_reset_ && reset_index_ != row_mask_;
  if (reset) { reset_index_ = 0; doing_reset_ = 1; }
  else { reset_index_ = next_reset_index; doing_reset_ = b(next_doing_reset); }
  if (reset) {
    clear_u_counter_ = 0;
    if (bypass_enq_idx_ != 0) { bypass_enq_idx_ = 0; bypass_changed_ = true; }
  } else if (was_doing_reset) {
    clear_u_counter_ = 1;
  } else {
    clear_u_counter_ = (clear_u_counter_ + 1u) & clear_mask_;
  }

  // Read-port faces: the MPORT row and the usefulness row, post-write.
  const bool touched = row_written && (written_row == mport_row || written_row == read_row_ ||
                                       written_row2 == mport_row || written_row2 == read_row_);
  if (touched || mport_row != mport_row_ || read_row_ != use_row_) refresh_ports(mport_row);
}

// ===========================================================================
// TAGE parent (component 1)
// ===========================================================================
std::uint8_t PredictorBank::tage_prio(std::uint8_t bits) {
  if (bits == 0) return 7;   // PriorityEncoder of the widened zero mask
  return static_cast<std::uint8_t>(__builtin_ctz(bits));
}

void PredictorBank::tage_evaluate(std::uint8_t alt_taken) {
  if (!tage_m_valid_ || tage_m_alt_ != alt_taken) {
    tage_m_valid_ = true;
    tage_m_alt_ = alt_taken;
    tage_provider_meta_ = 0;
    for (std::size_t s = 0; s < 4; ++s) {
      TageSlot& d = tage_slot_[s];
      std::uint8_t hits = 0, unused = 0;
      for (std::size_t t = 0; t < kTables; ++t) {
        const TageResp& r = tage_[t].resp()[s];
        if (r.valid) hits |= static_cast<std::uint8_t>(1u << t);
        else if (r.u == 0) unused |= static_cast<std::uint8_t>(1u << t);
      }
      // The longest matching history is the provider. Its alternate is
      // the next matching table's counter direction, even when that
      // alternate's own counter is weak; otherwise use the BIM/BTB input.
      d.prov_valid = hits != 0;
      d.prov = hits ? static_cast<std::uint8_t>(31u - __builtin_clz(unsigned(hits))) : 0;
      d.prov_u = tage_[d.prov].resp()[s].u;
      d.prov_ctr = tage_[d.prov].resp()[s].ctr;
      bool alt = ((alt_taken >> s) & 1u) != 0;
      d.pred = alt;
      if (hits) {
        const unsigned below = hits & ((1u << d.prov) - 1u);
        if (below) alt = (tage_[31u - __builtin_clz(below)].resp()[s].ctr & 4u) != 0;
        d.pred = (d.prov_ctr == 3 || d.prov_ctr == 4) ? alt : (d.prov_ctr & 4u) != 0;
        unused &= static_cast<std::uint8_t>(~((1u << (d.prov + 1u)) - 1u));
      }
      d.alt_differs = alt != d.pred;
      d.allocatable = unused;
      tage_provider_meta_ |= std::uint64_t(b(unused != 0)) << (s * 4u + 3u);
      tage_provider_meta_ |= std::uint64_t(d.prov_ctr & 7u) << (16u + s * 3u);
      tage_provider_meta_ |= std::uint64_t(d.prov_u & 3u) << (28u + s * 2u);
      tage_provider_meta_ |= std::uint64_t(b(d.alt_differs)) << (36u + s);
      tage_provider_meta_ |= std::uint64_t(d.prov & 7u) << (40u + s * 4u);
      tage_provider_meta_ |= std::uint64_t(b(d.prov_valid)) << (43u + s * 4u);
    }
  }
  // Only allocation depends on the per-cycle LFSR. Reuse the rest of the
  // metadata rather than repacking every provider field on a held query.
  std::uint64_t meta = tage_provider_meta_;
  for (std::size_t s = 0; s < 4; ++s) {
    const TageSlot& d = tage_slot_[s];
    const std::uint8_t masked = static_cast<std::uint8_t>(d.allocatable & lfsr_[s]);
    const std::uint8_t alloc = tage_prio(masked != 0 ? masked : d.allocatable);
    meta |= std::uint64_t(alloc & 7u) << (s * 4u);
  }
  tage_meta_ = meta & ((UINT64_C(1) << 56) - 1);
}

void PredictorBank::tage_compute_updates(std::array<TageTableUpdate, kTables>& out) const {
  const SmallFtqBpdUpdate& u = s1_upd_;
  for (TageTableUpdate& t : out) {
    t = TageTableUpdate{};
    t.pc = u.pc & kPc40;
    t.history = u.ghist.old_history;
  }
  if (!s1_upd_valid_) return;   // inactive on every table: nothing observable
  // local metadata (56 bits at offset 17 of the composed words)
  const std::uint64_t low = std::uint64_t(u.meta[0]) | (std::uint64_t(u.meta[1]) << 32u);
  const std::uint64_t local = ((low >> 17u) | (std::uint64_t(u.meta[2] & 0x1ffu) << 47u)) & ((UINT64_C(1) << 56) - 1);
  struct Slot { std::uint8_t alloc_bits, prov_bits, prov_ctr, prov_u; bool alloc_valid, prov_valid, alt_differs; };
  std::array<Slot, 4> md{};
  for (std::size_t s = 0; s < 4; ++s) {
    md[s].alloc_bits = (local >> (s * 4u)) & 7u;
    md[s].alloc_valid = ((local >> (s * 4u + 3u)) & 1u) != 0;
    md[s].prov_ctr = (local >> (16u + s * 3u)) & 7u;
    md[s].prov_u = (local >> (28u + s * 2u)) & 3u;
    md[s].alt_differs = ((local >> (36u + s)) & 1u) != 0;
    md[s].prov_bits = (local >> (40u + s * 4u)) & 7u;
    md[s].prov_valid = ((local >> (43u + s * 4u)) & 1u) != 0;
  }
  const bool commit = !u.is_mispredict_update && !u.is_repair_update && (u.btb_mispredicts & 0x0fu) == 0;
  const std::uint8_t cfi_slot = u.cfi_idx & 3u;
  for (TageTableUpdate& t : out)
    for (std::size_t s = 0; s < 4; ++s) {
      if (u.cfi_valid && cfi_slot == s && u.cfi_taken) t.taken |= static_cast<std::uint8_t>(1u << s);
      t.old_ctr[s] = md[s].prov_ctr;
    }
  for (std::size_t s = 0; s < 4; ++s) {
    if (!commit || ((u.br_mask >> s) & 1u) == 0 || !md[s].prov_valid) continue;
    const std::uint8_t prov = md[s].prov_bits;
    if (prov >= kTables) continue;
    TageTableUpdate& t = out[prov];
    t.mask |= static_cast<std::uint8_t>(1u << s);
    t.u_mask |= static_cast<std::uint8_t>(1u << s);
    t.alloc &= static_cast<std::uint8_t>(~(1u << s));
    // update_usefulness
    std::uint8_t use = md[s].prov_u & 3u;
    if (md[s].alt_differs) {
      const bool misp = u.cfi_mispredicted && cfi_slot == s;
      use = misp ? (use == 0 ? 0 : use - 1u) : (use == 3 ? 3 : use + 1u);
    }
    t.u[s] = use;
  }
  if (commit && u.cfi_mispredicted && u.cfi_valid) {
    const std::size_t s = cfi_slot;
    if (md[s].alloc_valid && md[s].alloc_bits < kTables) {
      TageTableUpdate& t = out[md[s].alloc_bits];
      t.mask |= static_cast<std::uint8_t>(1u << s);
      if (u.cfi_taken) t.taken |= static_cast<std::uint8_t>(1u << s);
      else t.taken &= static_cast<std::uint8_t>(~(1u << s));
      t.alloc |= static_cast<std::uint8_t>(1u << s);
      t.u_mask |= static_cast<std::uint8_t>(1u << s);
      t.u[s] = 0;
    } else if (md[s].prov_valid) {
      for (std::size_t t = md[s].prov_bits + 1u; t < kTables; ++t) {
        out[t].u_mask |= static_cast<std::uint8_t>(1u << s);
        out[t].u[s] = 0;
      }
    }
  }
  for (TageTableUpdate& t : out) t.active = (t.mask | t.u_mask) != 0;
}

void PredictorBank::tage_commit(const BpdIn& in) {
  for (std::size_t t = 0; t < kTables; ++t) {
    tage_[t].step(in.reset, s1_valid_, s1_pc_, in.f1_ghist, tage_upd_[t]);
    const TageTable& T = tage_[t];
    if (T.resp_changed()) tage_m_valid_ = false;
    if (T.resp_changed()) {
      const auto& r = T.resp();
      for (std::size_t s = 0; s < 4; ++s) {
        *tage_resp_lane_[t][s * 3 + 0] = r[s].valid & 1u;
        *tage_resp_lane_[t][s * 3 + 1] = r[s].u & 3u;
        *tage_resp_lane_[t][s * 3 + 2] = r[s].ctr & 7u;
      }
    }
    if (T.ports_changed()) {
      const std::uint16_t wmask = static_cast<std::uint16_t>((1u << (T.rows() == 256 ? 12u : (t >= 4 ? 13u : 11u))) - 1u);
      for (std::size_t s = 0; s < 4; ++s) {
        tage_mport_lane_[t][s] = T.read_data(s) & wmask;
        tage_hi_lane_[t][s] = T.use_hi(s) & 1u;
        tage_lo_lane_[t][s] = T.use_lo(s) & 1u;
      }
    }
    if (T.bypass_changed()) *tage_byp_lane_[t] = T.packed_bypass();
    R_.banked_predictors_0_components_1_tables_doing_reset[t] = T.doing_reset() & 1u;
    R_.banked_predictors_0_components_1_tables_wrbypass_enq_idx[t] = T.bypass_enq_idx() & 1u;
  }
  if (s1_upd_valid_) {
    tage_compute_updates(tage_upd_);
    tage_upd_any_ = true;
  } else if (tage_upd_any_) {
    for (TageTableUpdate& t : tage_upd_) t = TageTableUpdate{};
    tage_upd_any_ = false;
  }
  for (std::size_t s = 0; s < 4; ++s) {
    if (in.reset) {
      lfsr_[s] = 1;
    } else {
      const std::uint8_t st = lfsr_[s] & 0x3fu;
      lfsr_[s] = static_cast<std::uint8_t>(((st << 1u) & 0x3eu) | (((st >> 5u) ^ (st >> 4u)) & 1u));
    }
    *lfsr_lane_[s] = lfsr_[s] & 1u;
  }
}

// ===========================================================================
// loop predictor (component 0)
// ===========================================================================
LoopEntry PredictorBank::loop_trained(const LoopEntry& old, std::uint16_t tag, std::uint16_t cnt) {
  LoopEntry r = loop_norm(old);
  tag &= 0x3ffu; cnt &= 0x3ffu;
  const bool tm = r.tag == tag, cm = r.p_cnt == cnt;
  if (r.conf == 7 && tm) { r.s_cnt = 0; r.conf = 0; }
  else if (r.conf == 7 && !tm) { }
  else if (r.conf != 0 && tm && cm) { r.conf = static_cast<std::uint8_t>(r.conf + 1u); r.s_cnt = 0; }
  else if (r.conf != 0 && tm && !cm) { r.conf = 0; r.s_cnt = 0; r.p_cnt = cnt; }
  else if (r.conf != 0 && !tm && r.age == 0) { r.tag = tag; r.conf = 1; r.s_cnt = 0; r.p_cnt = cnt; }
  else if (r.conf != 0 && !tm && r.age != 0) { r.age = static_cast<std::uint8_t>(r.age - 1u); }
  else if (r.conf == 0 && tm && cm) { r.conf = 1; r.age = 7; r.s_cnt = 0; }
  else if (r.conf == 0 && tm && !cm) { r.p_cnt = cnt; r.age = 7; r.s_cnt = 0; }
  else { r.tag = tag; r.conf = 1; r.age = 7; r.s_cnt = 0; r.p_cnt = cnt; }
  return loop_norm(r);
}

void PredictorBank::loop_evaluate() {
  const SmallFtqBpdUpdate& u = s1_upd_;
  const std::uint64_t upd_idx = s1_upd_idx_ & kIdxMask;
  const std::uint64_t local = ((std::uint64_t(u.meta[2]) >> 9u) | (std::uint64_t(u.meta[3] & 0x1ffffu) << 23u)) & ((UINT64_C(1) << 40) - 1);
  for (std::size_t l = 0; l < 4; ++l) {
    const LoopColumn& c = loop_[l];
    const bool repair = s1_upd_valid_ && ((u.br_mask >> l) & 1u) != 0 && u.is_repair_update;
    const std::uint16_t meta_s_cnt = static_cast<std::uint16_t>((local >> (l * 10u)) & 0x3ffu);
    LoopEval& e = loop_ev_[l];
    e.f3_meta_s_cnt = (repair && upd_idx == c.f3_index) ? meta_s_cnt : c.f3_entry.s_cnt;
    e.overrides = c.f3_entry.tag == c.f3_tag && c.f3_entry.conf == 7 && e.f3_meta_s_cnt == c.f3_entry.p_cnt;
  }
}

void PredictorBank::write_loop_port_lanes(std::size_t l) {
  const LoopColumn& c = loop_[l];
  std::uint32_t* r23 = nullptr; std::uint16_t* r10 = nullptr; std::uint8_t* r3 = nullptr;
  switch (l) {
    case 0: r23 = C_.banked_predictors_0_components_0_columns_0_state_entries_r; r10 = C_.banked_predictors_0_components_0_columns_0_state_entries_1_r; r3 = C_.banked_predictors_0_components_0_columns_0_state_entries_0_r; break;
    case 1: r23 = C_.banked_predictors_0_components_0_columns_1_state_entries_r; r10 = C_.banked_predictors_0_components_0_columns_1_state_entries_1_r; r3 = C_.banked_predictors_0_components_0_columns_1_state_entries_0_r; break;
    case 2: r23 = C_.banked_predictors_0_components_0_columns_2_state_entries_r; r10 = C_.banked_predictors_0_components_0_columns_2_state_entries_1_r; r3 = C_.banked_predictors_0_components_0_columns_2_state_entries_0_r; break;
    default: r23 = C_.banked_predictors_0_components_0_columns_3_state_entries_r; r10 = C_.banked_predictors_0_components_0_columns_3_state_entries_1_r; r3 = C_.banked_predictors_0_components_0_columns_3_state_entries_0_r; break;
  }
  const LoopEntry* ports[2] = {&c.s2_port, &c.upd_port};
  for (std::size_t p = 0; p < 2; ++p) {
    const LoopEntry& e = *ports[p];
    r23[p] = ((std::uint32_t(e.tag) << 13u) | (std::uint32_t(e.conf) << 10u) | std::uint32_t(e.p_cnt)) & 0x7fffffu;
    r10[p] = e.s_cnt & 0x3ffu;
    r3[p] = e.age & 7u;
  }
}

void PredictorBank::loop_commit(const BpdIn& in) {
  const SmallFtqBpdUpdate& u = s1_upd_;
  const std::uint64_t query_idx = loop_s2_idx_ & kIdxMask;
  const std::uint64_t upd_idx = s1_upd_idx_ & kIdxMask;
  const std::uint64_t local = ((std::uint64_t(u.meta[2]) >> 9u) | (std::uint64_t(u.meta[3] & 0x1ffffu) << 23u)) & ((UINT64_C(1) << 40) - 1);
  const std::uint8_t qrow = static_cast<std::uint8_t>(query_idx & 0x0fu);
  const std::uint8_t urow = static_cast<std::uint8_t>(upd_idx & 0x0fu);
  const std::uint16_t qtag = static_cast<std::uint16_t>((query_idx >> 4u) & 0x3ffu);
  const std::uint16_t utag = static_cast<std::uint16_t>((upd_idx >> 4u) & 0x3ffu);

  // Quiet columns (no registered update, no F3 fire, no F4 progression, no
  // reset sweep) only shift their pipeline registers.
  bool quiet = !s1_upd_valid_ && !in.f3_fire && !in.reset;
  for (std::size_t l = 0; l < 4 && quiet; ++l)
    quiet = !loop_[l].doing_reset && !loop_[l].f4_fire;
  if (quiet) {
    for (std::size_t l = 0; l < 4; ++l) {
      LoopColumn& c = loop_[l];
      const LoopEntry next_f3 = c.e[qrow];
      c.f4_entry = c.f3_entry;
      c.f4_tag = c.f3_tag;
      c.f4_scnt = loop_ev_[l].f3_meta_s_cnt;
      c.f4_idx = c.f4_index1;
      c.f3_entry = loop_norm(next_f3);
      c.f3_index = query_idx;
      c.f3_tag = qtag;
      c.f4_index1 = query_idx;
    }
  } else
  for (std::size_t l = 0; l < 4; ++l) {
    LoopColumn& c = loop_[l];
    const bool br = ((u.br_mask >> l) & 1u) != 0;
    const bool upd_misp = s1_upd_valid_ && br && u.is_mispredict_update && u.cfi_mispredicted;
    const bool upd_repair = s1_upd_valid_ && br && u.is_repair_update;
    const std::uint16_t meta_s_cnt = static_cast<std::uint16_t>((local >> (l * 10u)) & 0x3ffu);
    const bool f3_req_fire = loop_s3_valid_ && ((loop_s3_mask_ >> l) & 1u) != 0 && in.f3_fire && loop_f2_br_[l];

    const bool f4_progress = c.f4_fire && c.f4_entry.tag == c.f4_tag;
    const bool f4_resets = f4_progress && c.f4_entry.conf == 7 && c.f4_scnt == c.f4_entry.p_cnt;
    const bool upd_tag_match = c.e[urow].tag == utag;
    const bool misp_write = upd_misp && !c.doing_reset;
    const bool repair_write = !upd_misp && upd_repair && !c.doing_reset && upd_tag_match &&
                              !(c.f4_fire && upd_idx == c.f4_idx);

    // f2_entry read of the cycle-start array with repair/mispredict forwarding
    LoopEntry next_f3 = c.e[qrow];
    if (upd_repair && upd_idx == query_idx) next_f3.s_cnt = meta_s_cnt;
    else if (upd_misp && upd_idx == query_idx) next_f3.s_cnt = 0;
    const LoopEntry old_upd = c.e[urow];

    if (f4_progress) {
      LoopEntry& e = c.e[c.f4_idx & 0x0fu];
      if (f4_resets) { e.age = 7; e.s_cnt = 0; }
      else { e.s_cnt = static_cast<std::uint16_t>((c.f4_scnt + 1u) & 0x3ffu); e.age = c.f4_entry.age == 7 ? 7 : static_cast<std::uint8_t>((c.f4_entry.age & 7u) + 1u); }
    }
    if (misp_write) c.e[urow] = loop_trained(old_upd, utag, meta_s_cnt);
    else if (repair_write) { LoopEntry r = old_upd; r.s_cnt = meta_s_cnt; c.e[urow] = r; }
    if (c.doing_reset) c.e[c.reset_idx] = LoopEntry{};

    const bool next_doing_reset = c.doing_reset && c.reset_idx != kLoopEntries - 1u;
    const std::uint8_t next_reset_idx = static_cast<std::uint8_t>((c.reset_idx + (c.doing_reset ? 1u : 0u)) & 0x0fu);
    const LoopEntry next_f4_entry = c.f3_entry;
    const std::uint16_t next_f4_tag = c.f3_tag;
    const std::uint16_t next_f4_scnt = loop_ev_[l].f3_meta_s_cnt;
    const std::uint64_t next_f4_idx = c.f4_index1;
    c.f3_entry = loop_norm(next_f3);
    c.f3_index = query_idx;
    c.f3_tag = qtag;
    c.f4_fire = f3_req_fire;
    c.f4_entry = loop_norm(next_f4_entry);
    c.f4_tag = next_f4_tag;
    c.f4_scnt = next_f4_scnt;
    c.f4_idx = next_f4_idx;
    c.f4_index1 = query_idx;
    if (in.reset) { c.doing_reset = true; c.reset_idx = 0; }
    else { c.doing_reset = next_doing_reset; c.reset_idx = next_reset_idx; }
  }

  // shared pipeline
  loop_s2_idx_ = s1_idx_;
  loop_s3_valid_ = loop_s2_valid_;
  loop_s2_valid_ = s1_valid_;
  loop_s3_mask_ = loop_s2_mask_;
  loop_s2_mask_ = loop_s1_mask_;
  loop_s1_mask_ = in.reset ? std::uint8_t{0x0f} : static_cast<std::uint8_t>(boomcfg::fetch_mask(in.f0_pc) & 0x0fu);
  for (std::size_t l = 0; l < 4; ++l)
    loop_f2_br_[l] = f2_.preds[l].predicted_pc_valid && f2_.preds[l].is_br;

  // read ports and lanes (post-step: s2 row of the new s2 index, the row of
  // the new update index)
  const std::uint8_t s2row = static_cast<std::uint8_t>(loop_s2_idx_ & 0x0fu);
  const std::uint8_t urow2 = static_cast<std::uint8_t>(fetch_index((in.update != nullptr ? in.update->pc : 0) & ~UINT64_C(7)) & 0x0fu);
  for (std::size_t l = 0; l < 4; ++l) {
    LoopColumn& c = loop_[l];
    const LoopEntry& s2 = c.e[s2row];
    const LoopEntry& up = c.e[urow2];
    if (s2 != c.s2_port || up != c.upd_port) {
      c.s2_port = s2; c.upd_port = up;
      write_loop_port_lanes(l);
    }
    R_.banked_predictors_0_components_0_columns_REG[l] = c.f4_index1 & kIdxMask;
    R_.banked_predictors_0_components_0_columns_f3_entry_p_cnt[l] = c.f3_entry.p_cnt & 0x3ffu;
    R_.banked_predictors_0_components_0_columns_f3_entry_s_cnt[l] = c.f3_entry.s_cnt & 0x3ffu;
    R_.banked_predictors_0_components_0_columns_f3_entry_tag[l] = c.f3_entry.tag & 0x3ffu;
    R_.banked_predictors_0_components_0_columns_f3_tag[l] = c.f3_tag & 0x3ffu;
    R_.banked_predictors_0_components_0_columns_f3_entry_age[l] = c.f3_entry.age & 7u;
    R_.banked_predictors_0_components_0_columns_f3_entry_conf[l] = c.f3_entry.conf & 7u;
    R_.banked_predictors_0_components_0_columns_reset_idx[l] = c.reset_idx & 0x0fu;
  }
  R_.banked_predictors_0_components_0_s1_mask = loop_s1_mask_ & 0x0fu;
}

}  // namespace chisa::boom_model::fe
