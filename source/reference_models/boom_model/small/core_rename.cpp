// model core: rename (RenameMapTable + RenameFreeList + RenameBusyTable,
// plWidth = 1) for the integer and FP stages.  The free list, the branch
// allocation lists and the freelist pre-selection registers are the image
// fields themselves; the map table is a private byte array whose contract
// bank words are regenerated at the end of a step in which it changed.
#include "core.h"

namespace chisa::boom_model {

namespace {
inline int ctz64(uint64_t x) { return __builtin_ctzll(x); }
}  // namespace

void Core::rename_step() {
  auto& R = img_->r.coreRename;
  // SelectFirstN is combinational over the PRE-edge free_list register.
  const preg_mask_t free_select_view = R.freelist_free_list;
  const preg_mask_t fp_free_select_view = img_->r.coreFpRename.freelist_free_list;

  // (0) Branch mispredict: restore the map, return the speculative pregs.
  if (br_mispredict_) {
    const uint8_t tag = br_mispredict_tag_ & (kBr - 1);
    std::memcpy(map_, br_snap_[tag], sizeof(map_));
    map_dirty_ = true;
    const preg_mask_t returned = R.freelist_br_alloc_lists[tag];
    R.freelist_free_list |= returned;
    for (int b = 0; b < kBr; ++b) R.freelist_br_alloc_lists[b] &= ~returned;
    fp_restore(tag);
  }

  // (1) ren2 / dispatch: the dispatching uop takes its pdst from the
  //     pre-selection, writes the map, sets busy, snapshots for its branch.
  bool reqs = false;
  if (disp_valid_ && dis_ready_) {
    MicroOp& du = disp_;
    const bool writes_reg = du.ldst_val && du.dst_rtype == RT_FIX && du.ldst != 0;
    if (writes_reg && R.freelist_REG) {
      const uint8_t p = R.freelist_r;
      du.pdst = p;
      map_write(du.ldst, p);
      busy_ |= boomcfg::pm_bit(p);
      ren2_alloc_now_ = true;
      ren2_alloc_ldst_ = du.ldst;
      ren2_alloc_pdst_ = p;
      for (int b = 0; b < kBr; ++b) R.freelist_br_alloc_lists[b] |= boomcfg::pm_bit(p);
      reqs = true;
    } else {
      du.pdst = 0;
    }
    if (du.is_br || du.is_jalr) {
      const uint8_t tag = du.br_tag & (kBr - 1);
      std::memcpy(br_snap_[tag], map_, sizeof(map_));
      R.freelist_br_alloc_lists[tag] = 0;
    }
  }

  // (2) Freelist pre-selection (rename-freelist.scala:54-89).
  {
    const preg_mask_t cand = free_select_view & ~preg_mask_t{1};
    const bool can_sel = cand != 0;
    const bool sel_fire = (!R.freelist_REG || reqs) && can_sel;
    if (sel_fire) {
      const int p = ctz64(cand);
      R.freelist_r = static_cast<uint8_t>(p);
      R.freelist_free_list &= ~boomcfg::pm_bit(p);
    }
    R.freelist_REG = bit((R.freelist_REG && !reqs) || can_sel);
  }

  fp_rename_ren2(fp_free_select_view);

  // (3) ren1: map/busy reads for the accepted uop + branch tag/mask fold.
  const bool rename_kill = flush_redirect_now_ || br_kill_this_cycle || xcpt_kill_start;
  {
    br_mask_t alloc_fold = branch_mask_start_;
    br_mask_t curr_fold = branch_mask_;
    const bool ren_valid = fp_uop_valid && !rename_kill;
    if (!ren_valid) {
      ren_r_valid_ = false;
      fp_ren_r_valid_ = false;
    } else {
      ren_r_ = dec_view_;                // the DEC wires of the accepted packet
      MicroOp& u = ren_r_;
      // Specifiers from the source packet: reading them back from the copy
      // just stored above defeats store-to-load forwarding.
      u.prs1 = map_[dec_view_.lrs1 & 31];
      u.prs2 = map_[dec_view_.lrs2 & 31];
      u.stale_pdst = map_[dec_view_.ldst & 31];
      u.prs1_busy = (u.lrs1_rtype == RT_FIX) && ((busy_ >> u.prs1) & 1u);
      u.prs2_busy = (u.lrs2_rtype == RT_FIX) && ((busy_ >> u.prs2) & 1u);
      u.prs3 = map_[u.lrs3 & 31];
      u.prs3_busy = 0;
      u.pdst = 0;
      {
        const br_mask_t inv = static_cast<br_mask_t>(~alloc_fold);
        u.br_tag = inv ? static_cast<uint8_t>(__builtin_ctz(inv)) : 0;
      }
      u.br_mask = curr_fold;
      if (u.is_jalr || u.is_br) {
        const br_mask_t free = static_cast<br_mask_t>(~alloc_fold);
        if (free) {
          const uint8_t tag = static_cast<uint8_t>(__builtin_ctz(free));
          u.br_tag = tag;
          alloc_fold |= static_cast<br_mask_t>(1u << tag);
          curr_fold |= static_cast<br_mask_t>(1u << tag);
        }
      }
      ren_r_valid_ = true;
      // FP rename stage: the same wires with the FP map reads.
      fp_ren_r_.prs1 = fp_map_[u.lrs1 & 31];
      fp_ren_r_.prs2 = fp_map_[u.lrs2 & 31];
      fp_ren_r_.prs3 = fp_map_[u.lrs3 & 31];
      fp_ren_r_.stale_pdst = fp_map_[u.ldst & 31];
      fp_ren_r_.pdst = 0;
      fp_ren_r_.prs1_busy = fp_ren_r_.prs2_busy = fp_ren_r_.prs3_busy = 0;
      fp_ren_r_valid_ = true;
      ren1_ran_ = true;
    }
    branch_mask_ = curr_fold;
  }

  // The map-table write ports bypass into the r_uop payload registers
  // (youngest port wins): match addresses from the NEW payload, values from
  // the OLD ren2 allocation.
  if (ren2_alloc_now_) {
    MicroOp& next = ren_r_;
    const uint8_t ldst = ren2_alloc_ldst_ & 31;
    const uint8_t pdst = ren2_alloc_pdst_;
    if ((next.lrs1 & 31) == ldst) { next.prs1 = pdst; next.prs1_busy = 1; }
    if ((next.lrs2 & 31) == ldst) { next.prs2 = pdst; next.prs2_busy = 1; }
    if ((next.ldst & 31) == ldst) next.stale_pdst = pdst;
  }
  if (fp_ren2_alloc_now_) {
    const MicroOp& next = ren_r_;
    const uint8_t ldst = fp_ren2_alloc_ldst_ & 31;
    const uint8_t pdst = fp_ren2_alloc_pdst_;
    if ((next.lrs1 & 31) == ldst) { fp_ren_r_.prs1 = pdst; fp_ren_r_.prs1_busy = 1; }
    if ((next.lrs2 & 31) == ldst) { fp_ren_r_.prs2 = pdst; fp_ren_r_.prs2_busy = 1; }
    if ((next.lrs3 & 31) == ldst) { fp_ren_r_.prs3 = pdst; fp_ren_r_.prs3_busy = 1; }
    if ((next.ldst & 31) == ldst) fp_ren_r_.stale_pdst = pdst;
  }
}

// FP RenameStage ren2 half (rename-stage.scala float=true; core.scala:674
// merges the two stages' outputs by register type).
void Core::fp_rename_ren2(preg_mask_t free_select_view) {
  auto& F = img_->r.coreFpRename;
  bool reqs = false;
  if (dis_fire_) {
    MicroOp& merged = disp_;
    FpRenFields& fdu = fp_disp_;
    const bool writes_freg = merged.ldst_val && merged.dst_rtype == RT_FLT;
    if (writes_freg && F.freelist_REG) {
      const uint8_t p = F.freelist_r;
      fdu.pdst = p;
      merged.pdst = p;
      merged.stale_pdst = fdu.stale_pdst;
      fp_map_write(merged.ldst, p);
      fp_busy_ |= boomcfg::pm_bit(p);
      for (int b = 0; b < kBr; ++b) F.freelist_br_alloc_lists[b] |= boomcfg::pm_bit(p);
      reqs = true;
      fp_ren2_alloc_now_ = true;
      fp_ren2_alloc_ldst_ = merged.ldst;
      fp_ren2_alloc_pdst_ = p;
    } else {
      fdu.pdst = 0;
      if (writes_freg) merged.pdst = 0;
    }
    if ((merged.is_br && !merged.is_sfb) || merged.is_jalr) {
      const uint8_t tag = merged.br_tag & (kBr - 1);
      std::memcpy(fp_br_snap_[tag], fp_map_, sizeof(fp_map_));
      F.freelist_br_alloc_lists[tag] = 0;
    }
  }
  const preg_mask_t cand = free_select_view & ~preg_mask_t{1};
  const bool can_sel = cand != 0;
  const bool sel_fire = (!F.freelist_REG || reqs) && can_sel;
  if (sel_fire) {
    const int p = ctz64(cand);
    F.freelist_r = static_cast<uint8_t>(p);
    F.freelist_free_list &= ~boomcfg::pm_bit(p);
  }
  F.freelist_REG = bit((F.freelist_REG && !reqs) || can_sel);
}

// Mispredict restore of the FP map + speculative fp preg return.
void Core::fp_restore(uint8_t tag) {
  auto& F = img_->r.coreFpRename;
  tag &= (kBr - 1);
  std::memcpy(fp_map_, fp_br_snap_[tag], sizeof(fp_map_));
  fp_map_dirty_ = true;
  const preg_mask_t returned = F.freelist_br_alloc_lists[tag];
  F.freelist_free_list |= returned;
  for (int b = 0; b < kBr; ++b) F.freelist_br_alloc_lists[b] &= ~returned;
}

// Contract image of the rename stage's r_uop register (rename_stage.REG_1_*
// and the FP stage's map-read fields).
void Core::export_ren_r() {
  auto& R = img_->r.coreRename;
  const MicroOp& u = ren_r_;
  R.REG_1_imm_packed = u.imm_packed & 0xfffffu;
  R.REG_1_fu_code = u.fu_code & 0x3ffu;
  R.REG = bit(disp_valid_);
  R.REG_1_br_tag = u.br_tag & 7;
  R.REG_1_dst_rtype = u.dst_rtype & 3;
  R.REG_1_edge_inst = u.edge_inst & 1;
  R.REG_1_exception = u.exception & 1;
  R.REG_1_flush_on_commit = u.flush_on_commit & 1;
  R.REG_1_ftq_idx = u.ftq_idx & 15;
  R.REG_1_iq_type = u.iq_type & 7;
  R.REG_1_is_amo = u.is_amo & 1;
  R.REG_1_is_br = u.is_br & 1;
  R.REG_1_is_fence = u.is_fence & 1;
  R.REG_1_is_fencei = u.is_fencei & 1;
  R.REG_1_is_jal = u.is_jal & 1;
  R.REG_1_is_jalr = u.is_jalr & 1;
  R.REG_1_is_rvc = u.is_rvc & 1;
  R.REG_1_is_sfb = u.is_sfb & 1;
  R.REG_1_is_sys_pc2epc = u.is_sys_pc2epc & 1;
  R.REG_1_is_unique = u.is_unique & 1;
  R.REG_1_ldst = u.ldst & 0x3f;
  R.REG_1_ldst_val = u.ldst_val & 1;
  R.REG_1_lrs1 = u.lrs1 & 0x3f;
  R.REG_1_lrs1_rtype = u.lrs1_rtype & 3;
  R.REG_1_lrs2_rtype = u.lrs2_rtype & 3;
  R.REG_1_mem_cmd = u.mem_cmd & 0x1f;
  R.REG_1_mem_signed = u.mem_signed & 1;
  R.REG_1_mem_size = u.mem_size & 3;
  R.REG_1_pc_lob = u.pc_lob & 0x3f;
  R.REG_1_prs1 = u.prs1 & 0x3f;
  R.REG_1_prs2 = u.prs2 & 0x3f;
  R.REG_1_stale_pdst = u.stale_pdst & 0x3f;
  R.REG_1_taken = u.taken & 1;
  R.REG_1_uopc = u.uopc & 0x7f;
  R.REG_1_uses_ldq = u.uses_ldq & 1;
  R.REG_1_uses_stq = u.uses_stq & 1;
  auto& F = img_->r.coreFpRename;
  F.REG_1_br_tag = u.br_tag & 7;
  F.REG_1_dst_rtype = u.dst_rtype & 3;
  F.REG_1_is_br = u.is_br & 1;
  F.REG_1_is_jalr = u.is_jalr & 1;
  F.REG_1_is_sfb = u.is_sfb & 1;
  F.REG_1_ldst_val = u.ldst_val & 1;
  F.REG_1_prs1 = fp_ren_r_.prs1 & 0x3f;
  F.REG_1_prs2 = fp_ren_r_.prs2 & 0x3f;
  F.REG_1_prs3 = fp_ren_r_.prs3 & 0x3f;
  F.REG_1_stale_pdst = fp_ren_r_.stale_pdst & 0x3f;
}

// map_table__v2_bank_0_k: lregs 1..10 / 11..20 / 21..30, six bits each,
// oldest lreg in the top bits; x31 is its own stream.
void Core::pack_map() {
  auto& R = img_->r.coreRename;
  for (int bank = 0; bank < 3; ++bank) {
    uint64_t w = 0;
    for (int k = 0; k < 10; ++k) w = (w << 6) | (map_[1 + bank * 10 + k] & 0x3fu);
    R.maptable_map_tablebank_0[bank] = w;
  }
  R.maptable_map_table_31 = map_[31] & 0x3f;
  map_dirty_ = false;
}

// The FP map covers f0..f31: three ten-entry banks and a two-entry tail.
void Core::pack_fp_map() {
  auto& F = img_->r.coreFpRename;
  for (int bank = 0; bank < 3; ++bank) {
    uint64_t w = 0;
    for (int k = 0; k < 10; ++k) w = (w << 6) | (fp_map_[bank * 10 + k] & 0x3fu);
    F.maptable_map_tablebank_0[bank] = w;
  }
  F.maptable_map_tablebank_0_3 =
      static_cast<uint16_t>(((fp_map_[30] & 0x3fu) << 6) | (fp_map_[31] & 0x3fu));
  fp_map_dirty_ = false;
}

}  // namespace chisa::boom_model
