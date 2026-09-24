// model core: branch resolution (b1 mask clear / kill, b2 rewind + restore
// + redirect) and the brupdate broadcast over every in-flight copy.
#include "core.h"

namespace chisa::boom_model {

void Core::apply_brupdate(br_mask_t resolve, br_mask_t mispredict) {
  auto hit = [&](br_mask_t bm) { return (mispredict & bm) != 0; };
  const uint8_t keep = static_cast<uint8_t>(~resolve);

  // ROB rows: valid-gated GetNewBrMask, kill on a mispredict hit.
  for (uint32_t m = rob_val_; m != 0; m &= m - 1) {
    const int i = __builtin_ctz(m);
    if (hit(rob_brmask_[i])) {
      rob_val_ &= ~(1u << i);
    } else if (rob_brmask_[i] & resolve) {
      rob_brmask_[i] &= keep;
      rob_brmask_dirty_ = true;
    }
  }
  // Issue slots: the state kills on a hit; every slot's payload mask clears.
  for (Iq* q : {&int_iq_, &mem_iq_}) {
    for (int i = 0; i < kIq; ++i) {
      if (kArchitecturalModel && q->state[i] == IS_INVALID) continue;
      if (q->state[i] != IS_INVALID && hit(q->br_mask[i])) {
        q->state[i] = IS_INVALID;
        if constexpr (kArchitecturalModel) q->live &= static_cast<std::uint8_t>(~(1u << i));
      }
      if (q->br_mask[i] & resolve) {
        q->br_mask[i] &= keep;
        q->packed[i] = pack_iq_slot(q->uopc[i], q->br_mask[i], q->rt1[i], q->rt2[i]);
      }
    }
  }
  // LDQ/STQ: valid-gated payload updates.
  for (uint8_t m = lsq_.ld_valid; m != 0; m &= static_cast<uint8_t>(m - 1)) {
    const int i = __builtin_ctz(m);
    if (hit(lsq_.ld_brmask[i])) {
      ldq_b1_killed_now_ |= static_cast<uint8_t>(1u << i);
      lsq_.ld_valid &= static_cast<uint8_t>(~(1u << i));
      lsq_.ld_addr_valid &= static_cast<uint8_t>(~(1u << i));
    }
    lsq_.ld_brmask[i] &= keep;
    ldq_dirty_ = true;
  }
  for (uint8_t m = lsq_.st_valid; m != 0; m &= static_cast<uint8_t>(m - 1)) {
    const int i = __builtin_ctz(m);
    uint64_t w = lsq_.st_word[i];
    if (hit(StqWord::br_mask(w))) {
      const uint8_t clr = static_cast<uint8_t>(~(1u << i));
      lsq_.st_valid &= clr; lsq_.st_addr_valid &= clr; lsq_.st_data_valid &= clr;
      lsq_.live_store_mask &= clr;
    }
    lsq_.st_word[i] = StqWord::set_br_mask(w, StqWord::br_mask(w) & keep);
    stq_dirty_ = true;
  }
  // Rename/dispatch registers.
  if (disp_valid_ && hit(disp_.br_mask)) disp_valid_ = false;
  disp_.br_mask &= keep;
  if (ren_r_valid_ && hit(ren_r_.br_mask)) ren_r_valid_ = false;
  ren_r_.br_mask &= keep;
  // The FP rename registers carry the same br_mask as their integer twins.
  fp_disp_valid_ = fp_disp_valid_ && disp_valid_;
  fp_ren_r_valid_ = fp_ren_r_valid_ && ren_r_valid_;
  // issue->AGU stages
  if (mem_iss_.v && hit(mem_iss_.u.br_mask)) mem_iss_.v = false;
  mem_iss_.u.br_mask &= keep;
  if (hit(mem_rrd_.u.br_mask)) mem_rrd_killed_ = true;
  if (mem_agu_.v && hit(mem_agu_.u.br_mask)) mem_agu_killed_ = true;
  if (mem_rrd_.v && hit(mem_rrd_.u.br_mask)) mem_rrd_.v = false;
  mem_rrd_.u.br_mask &= keep;
  if (mem_agu_.v && hit(mem_agu_.u.br_mask)) mem_agu_.v = false;
  mem_agu_.u.br_mask &= keep;
  // INT rrd/exe
  if (hit(int_rrd_.u.br_mask)) int_rrd_killed_ = true;
  if (int_rrd_.v && hit(int_rrd_.u.br_mask)) int_rrd_.v = false;
  int_rrd_.u.br_mask &= keep;
  if (int_exe_.v && hit(int_exe_.u.br_mask)) int_exe_.v = false;
  int_exe_.u.br_mask &= keep;
  brinfo_uop_r_.br_mask &= keep;
  // functional-unit valid conveyors + raw payload chain
  {
    StageUop* raw[5] = {&oracle_exe_, &oracle_b1_, &oracle_b2_, &oracle_b3_, &oracle_b4_};
    for (int stage = 0; stage < 3; ++stage) {
      const bool killed = hit(raw[stage + 2]->br_mask);
      if (alu_unit_valid_[stage] && killed) alu_unit_valid_[stage] = false;
      if (imul_unit_valid_[stage] && killed) imul_unit_valid_[stage] = false;
      if (stage < 2 && ifpu_unit_valid_[stage] && killed) ifpu_unit_valid_[stage] = false;
    }
    for (StageUop* s : raw) s->br_mask &= keep;
  }
  for (auto& b : br_pipe) {
    if (!b.v) continue;
    if (hit(b.br_mask)) b.v = false; else b.br_mask &= keep;
  }
  if (br_inject_.v) { if (hit(br_inject_.br_mask)) br_inject_.v = false; else br_inject_.br_mask &= keep; }
  for (unsigned m = wb_mask_; m != 0; m &= m - 1) {
    const int i = __builtin_ctz(m);
    Wb& w = wb_[i];
    if (hit(w.br_mask)) {
      wb_mask_ &= static_cast<uint16_t>(~(1u << i));
      if (w.is_div) { div_block_from_ = 1; div_block_until_ = 0; }
    } else {
      w.br_mask &= keep;
    }
  }
  if (rob_xcpt_.v && hit(rob_xcpt_.br_mask)) rob_xcpt_.v = false;
  rob_xcpt_.br_mask &= keep;
  {
  if (mul_req_.v) {
    if (hit(mul_req_.br_mask) && mul_req_.left > 0) mul_req_.v = false;
    else mul_req_.br_mask &= keep;
  }
  const bool div_live_killed = hit(div_r_uop_.br_mask);
  div_r_uop_.br_mask &= keep;
  if (div_live_killed) div_state_ = 0;
  if (div_req_.v) {
    const bool div_arrival_killed = hit(div_req_.uop.br_mask);
    div_req_.uop.br_mask &= keep;
    if (div_arrival_killed) {
      if (div_req_.left == 0) div_r_uop_ = div_req_.uop;
      div_req_.v = false;
      div_state_ = 0;
    }
  }
  }
  mem_incoming_brmask_r_ &= keep;
  mem_xcpt_brmask_r_ &= keep;
  lsu_xcpt_brmask_r_ &= keep;
  if (lsu_r_xcpt_.v && hit(lsu_r_xcpt_.br_mask)) lsu_r_xcpt_killed_now_ = true;
  lsu_r_xcpt_.br_mask &= keep;
  if (spec_s1_.v) spec_s1_.br_mask &= keep;
  if (spec_s2_.v) spec_s2_.br_mask &= keep;
  if (store_clr_bsy_s1_.v && hit(store_clr_bsy_s1_.br_mask)) store_clr_bsy_s1_.v = false;
  if (store_clr_bsy_s2_.v && hit(store_clr_bsy_s2_.br_mask)) store_clr_bsy_s2_.v = false;
  store_clr_bsy_s1_.br_mask &= keep;
  store_clr_bsy_s2_.br_mask &= keep;
  if (dmem_pending.valid && hit(dmem_pending.uop.br_mask)) dmem_pending_kill_ = true;
  fp_apply_brupdate(resolve, mispredict);
}

void Core::branch_step() {
  // b2 (issue+4): pointer rewind + rename restore + frontend redirect.
  BrStage& b2 = br_pipe[3];
  if (b2.v && b2.mispredict) {
    rob_tail_ = rob_wrap(b2.rob_idx + 1);
    rob_empty_ = rob_head_ == rob_tail_;
    lsq_.ldq_tail = ldq_wrap(b2.ldq_idx);
    lsq_.stq_tail = stq_wrap(b2.stq_idx);
    lsq_.live_store_mask = lsq_.st_valid;
    ldq_dirty_ = stq_dirty_ = true;
    branch_mask_ &= b2.br_mask;
    br_mispredict_ = true;
    br_mispredict_tag_ = b2.tag;
    out_ifu_redirect_val = 1;
    out_ifu_redirect_pc = b2.target;
    out_ifu_redirect_ftq_idx = b2.ftq_idx;
    br_kill_this_cycle = true;
  }
  if (b2.v) b2.clear();
  // b1 (issue+3): mask clear + kill; ghost-grant detection over the pre-kill state.
  BrStage& b1 = br_pipe[2];
  const bool b1_valid = b1.v;
  const br_mask_t resolve = b1_valid ? static_cast<br_mask_t>(1u << b1.tag) : 0;
  const br_mask_t mispredict = (b1_valid && b1.mispredict) ? resolve : 0;
  if (!b1_valid) return;
  b1_mispred_mask_now_ = mispredict;
  b1_resolve_mask_now_ = resolve;
  if (kInternalSignalContract && mispredict) {
    const int gi = iq_peek(int_iq_, cur_int_fu_);
    if (gi >= 0 && (int_iq_.br_mask[gi] & mispredict)) {
      int_port_consumed_ = true;
      const MicroOp& gu = inst_[int_iq_.rob[gi]];
      if (gu.bypassable && gu.dst_rtype == RT_FIX && gu.ldst_val) ghost_fast_wake_pdst_ = gu.pdst;
      ghost_int_v_ = true;
      ghost_int_uop_ = iq_selected(int_iq_, gi);
      ghost_int_uop_.br_mask &= static_cast<br_mask_t>(~resolve);
      ghost_int_poison_ = int_iq_.p1_poison[gi] || int_iq_.p2_poison[gi];
      const bool vacate = int_iq_.state[gi] == IS_VALID_1 ||
                          (int_iq_.state[gi] == IS_VALID_2 && int_iq_.p1[gi] && int_iq_.p2[gi] && int_iq_.ppred[gi]);
      ghost_int_slot_ = vacate ? static_cast<int8_t>(gi) : -1;
      ghost_int_partial_slot_ = vacate ? -1 : static_cast<int8_t>(gi);
    }
    const bool pause_mem = pause_mem_r_ && sat_loads_ctr_ == 31;
    const int mi = iq_peek(mem_iq_, pause_mem ? 0 : FU_MEM);
    if (mi >= 0 && (mem_iq_.br_mask[mi] & mispredict)) {
      mem_port_consumed_ = true;
      ghost_mem_v_ = true;
      ghost_mem_uop_ = iq_selected(mem_iq_, mi);
      ghost_mem_uop_.br_mask &= static_cast<br_mask_t>(~resolve);
      ghost_mem_poison_ = mem_iq_.p1_poison[mi] || mem_iq_.p2_poison[mi];
      const bool vacate = mem_iq_.state[mi] == IS_VALID_1 ||
                          (mem_iq_.state[mi] == IS_VALID_2 && mem_iq_.p1[mi] && mem_iq_.p2[mi] && mem_iq_.ppred[mi]);
      ghost_mem_slot_ = vacate ? static_cast<int8_t>(mi) : -1;
      ghost_mem_partial_slot_ = vacate ? -1 : static_cast<int8_t>(mi);
    }
  }
  apply_brupdate(resolve, mispredict);
  branch_mask_ &= static_cast<br_mask_t>(~resolve);
  if (mispredict) { br_kill_this_cycle = true; b1_mispred_now_ = true; }
}

}  // namespace chisa::boom_model
