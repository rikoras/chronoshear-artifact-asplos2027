// model core: ROB commit / exception / enqueue (rob.scala) over bit
// columns, plus the writeback queue that clears row busy bits.
#include "core.h"

namespace chisa::boom_model {

void Core::wb_schedule(uint8_t rob, uint8_t pdst, uint8_t left, bool slow_wake, uint64_t data,
                       br_mask_t br_mask, bool drives_port, bool is_div, bool is_mul) {
  if (wb_mask_ == 0xffffu) return;
  const int i = __builtin_ctz(static_cast<unsigned>(~wb_mask_) & 0xffffu);
  wb_mask_ |= static_cast<uint16_t>(1u << i);
  Wb& w = wb_[i];
  w.rob = rob; w.pdst = pdst; w.left = left ? left : 1; w.slow_wake = slow_wake;
  w.data = data; w.br_mask = br_mask; w.drives_port = drives_port;
  w.is_div = is_div; w.is_mul = is_mul;
}

// Asynchronous ROB read port p sees the pre-edge row.
void Core::rob_read_port(int p, unsigned idx, bool busy_start_bit) {
  rob_read_bsy_now_[p] = busy_start_bit;
  rob_read_uop_packed_now_[p] = uop_packed_[idx & (kRob - 1)];
}

// (1) Functional-unit writebacks: clear busy/unsafe, drive write port 1,
//     collect slow wakeups (applied after issue).  (2) Store clr_bsy.
void Core::writeback_step(uint8_t* slow_wake, int& n_slow_wake) {
  const uint32_t busy_start = rob_busy_;
  auto fire = [&](Wb& w, int i) {
    wb_mask_ &= static_cast<uint16_t>(~(1u << i));
    if (w.is_div) div_resp_fired_ = true;
    iresp_rob_r_ = w.rob;
    iresp_now_v_ = true; iresp_now_rob_ = w.rob;
    rob_read_port(1, w.rob, (busy_start >> w.rob) & 1u);
    rob_busy_ &= ~(1u << w.rob);
    rob_unsafe_ &= ~(1u << w.rob);
    if (w.pdst != 0 || w.drives_port) {
      out_ext_irf_write_valids[1] = 1;
      out_ext_irf_write_addrs[1] = w.pdst;
      out_ext_irf_write_datas[1] = w.data;
      prf_landed.wr(w.pdst, w.data);
      if (w.slow_wake && n_slow_wake < 16) slow_wake[n_slow_wake++] = w.pdst;
    }
  };
  bool alu_fired = false;
  for (unsigned m = wb_mask_; m != 0; m &= m - 1) {
    const int i = __builtin_ctz(m);
    Wb& w = wb_[i];
    if (w.is_div) continue;
    if (--w.left != 0) continue;
    fire(w, i);
    alu_fired = true;
  }
  for (unsigned m = wb_mask_; m != 0; m &= m - 1) {
    const int i = __builtin_ctz(m);
    Wb& w = wb_[i];
    if (!w.is_div) continue;
    if (--w.left != 0) continue;
    if (alu_fired) {           // the divider yields the shared write port
      w.left = 1;
      ++div_block_until_;
      continue;
    }
    fire(w, i);
  }
  if (store_clr_bsy_s2_.v) {
    rob_busy_ &= ~(1u << store_clr_bsy_s2_.rob);
    rob_unsafe_ &= ~(1u << store_clr_bsy_s2_.rob);
  }
  if (stdf_clr_bsy_r_.v) {
    rob_busy_ &= ~(1u << stdf_clr_bsy_r_.rob);
    rob_unsafe_ &= ~(1u << stdf_clr_bsy_r_.rob);
  }
}

void Core::rob_step() {
  out_ifu_commit_valid = 0;
  out_ifu_commit_bits = 0;
  auto& R = img_->r.coreRename;
  auto& F = img_->r.coreFpRename;

  const bool lxcpt_valid = lsu_r_xcpt_.v && !flush_redirect_now_ && !lsu_r_xcpt_killed_now_;
  const XcptRec rob_xcpt_start = rob_xcpt_;

  // --- exception trap in progress: rollback one row per cycle ---
  if (trap_active_ > 0) {
    --trap_active_;
    if (trap_clr_valid_) {
      const int idx = trap_clr_row_;
      if ((rob_val_ >> idx) & 1u) {
        const MicroOp& u = inst_[idx];
        if (u.ldst_val && u.pdst != 0 && u.dst_rtype == RT_FIX) {
          map_write(u.ldst, u.stale_pdst);
          R.freelist_free_list |= boomcfg::pm_bit(u.pdst);
        }
        fp_rollback(u);
      }
      rob_val_ &= ~(1u << idx);
      rob_exc_ &= ~(1u << idx);
      trap_clr_valid_ = false;
    }
    const int k = trap_rows_total_ + 1 - trap_active_;
    if (k >= 0 && k < trap_rows_total_) {
      rob_tail_ = rob_wrap(rob_tail_ - 1);
      trap_clr_row_ = rob_tail_;
      trap_clr_valid_ = true;
      rob_deq_fired_ = true;
    }
    if (trap_active_ == 0) rob_empty_ = true;
    return;
  }
  if (trap_take_pending_) {
    if (!trap_pend_mini_) take_trap(trap_pend_pc_, trap_pend_cause_, inst_[rob_head_].inst);
    trap_take_pending_ = false;
    trap_rows_total_ = rob_wrap(rob_tail_ - rob_head_);
    if (trap_rows_total_ == 0 && !rob_empty_) trap_rows_total_ = kRob;
    trap_active_ = trap_rows_total_ + (trap_from_wait_empty_ ? 2 : 3);
    trap_from_wait_empty_ = false;
    trap_clr_valid_ = false;
    return;
  }

  // --- commit / throw at the head ---
  const int hidx = rob_head_;
  const bool hval = (rob_val_ >> hidx) & 1u;
  const bool can_throw = hval && ((rob_exc_ >> hidx) & 1u);
  const bool can_commit = hval && !((rob_busy_start_ >> hidx) & 1u) && !can_throw &&
                          !csr_.wfi && !csr_.cease;
  if (can_commit) {
    const MicroOp& cu = inst_[hidx];
    rob_commit_arch_now_ = true;
    RetirementEvent retired;
    retired.cycle = cycle_count_;
    retired.pc = cu.debug_pc;
    retired.is_rvc = cu.is_rvc != 0;
    retired.debug_mode = retirement_debug_[hidx];
    retired.instruction = cu.debug_inst & (retired.is_rvc ? UINT32_C(0xffff) : UINT32_MAX);
    retired.expanded_instruction = cu.inst;
    retired.rd = cu.ldst;
    retired.writes_x = cu.ldst_val && cu.dst_rtype == RT_FIX && cu.ldst != 0;
    retired.writes_f = cu.ldst_val && cu.dst_rtype == RT_FLT;
    // This row is no longer busy. Its physical destination cannot be freed
    // until a younger overwrite retires, so these are this instruction's
    // completed values, copied once into independent committed storage.
    if (retired.writes_x) retired.value = prf_landed.rd(cu.pdst);
    if (retired.writes_f) retired.value = fp_prf_[cu.pdst % boomcfg::NUM_FPREGS];
    retired.fflags = cu.fp_val && !cu.uses_stq ? rob_fflags_[hidx] & 0x1fu : 0;
    retired.memory_write = cu.uses_stq && cu.mem_cmd == 1;
    if (retired.memory_write) {
      const unsigned slot = stq_wrap(cu.stq_idx);
      retired.memory_size = cu.mem_size;
      retired.memory_address = img_->r.lsu.stq_bits_addr_bits[slot];
      const unsigned bits = 8u << (cu.mem_size & 3u);
      const std::uint64_t mask = bits == 64 ? UINT64_MAX : (UINT64_C(1) << bits) - 1;
      retired.memory_value = img_->r.lsu.stq_bits_data_bits[slot] & mask;
    }
    architectural_.retire(retired);
    if (cu.ldst_val && cu.stale_pdst != 0 && cu.dst_rtype == RT_FIX)
      R.freelist_free_list |= boomcfg::pm_bit(cu.stale_pdst);
    fp_commit_free(cu);
    fp_commit(cu);
    if (cu.uses_stq) {
      const int si = stq_wrap(cu.stq_idx);
      lsq_.st_committed |= static_cast<uint8_t>(1u << si);
      lsq_.stq_commit_head = stq_wrap(cu.stq_idx + 1);
      stq_dirty_ = true;
    }
    if (cu.uses_ldq) {
      const uint8_t clr = static_cast<uint8_t>(~(1u << lsq_.ldq_head));
      lsq_.ld_valid &= clr; lsq_.ld_addr_valid &= clr; lsq_.ld_executed &= clr;
      lsq_.ld_succeeded &= clr; lsq_.ld_order_fail &= clr; lsq_.ld_fwd_std_val &= clr;
      lsq_.ldq_head = ldq_wrap(lsq_.ldq_head + 1);
      ldq_dirty_ = true;
    }
    rob_val_ &= ~(1u << hidx);
    if ((csr_.mcountinhibit & 4u) == 0) ++minstret_count_;
    out_ifu_commit_valid = 1;
    out_ifu_commit_bits = cu.ftq_idx;
    if (cu.is_fencei) out_ifu_flush_icache = 1;
    bool flush = false; uint64_t fpc = 0; uint8_t fft = 0; uint8_t flush_typ = 0;
    if (cu.flush_on_commit) {
      flush = true;
      fpc = (cu.uopc == uopERET) ? csr_flush_target_ : cu.debug_pc + (cu.is_rvc ? 2 : 4);
      fft = cu.ftq_idx;
      flush_typ = (cu.uopc == uopERET) ? 3 : (cu.is_sys_pc2epc ? 2 : 4);
    }
    rob_head_ = rob_wrap(rob_head_ + 1);
    rob_deq_fired_ = true;
    if (rob_head_ == rob_tail_ && !((rob_val_ >> rob_head_) & 1u)) rob_empty_ = true;
    if (flush) {
      redirect_pending = true;
      redirect_pending_pc = fpc;
      redirect_pending_ftq = fft;
      rob_flush_now_ = true;
      rob_flush_ftq_now_ = fft;
      flush_typ_now_ = flush_typ;
    }
  }
  if (can_throw) {
    const MicroOp& xu = inst_[hidx];
    const bool tracked_head = rob_xcpt_.v && (rob_xcpt_.rob & (kRob - 1)) == static_cast<unsigned>(hidx);
    const uint64_t cause = tracked_head ? rob_xcpt_.exc_cause : xu.exc_cause;
    const bool mini = cause == 16;
    rob_exception_now_ = true;
    const uint64_t target = mini ? xu.debug_pc : trap_target(cause, xu.inst);
    redirect_pending = true;
    redirect_pending_pc = target;
    redirect_pending_ftq = xu.ftq_idx;
    rob_flush_now_ = true;
    rob_flush_ftq_now_ = xu.ftq_idx;
    flush_typ_now_ = mini ? 2 : 1;
    rob_xcpt_.v = false;
    out_ifu_commit_valid = mini ? 0 : 1;
    out_ifu_commit_bits = xu.ftq_idx;
    trap_take_pending_ = true;
    trap_pend_mini_ = mini;
    trap_from_wait_empty_ = rob_wait_empty_;
    trap_pend_pc_ = xu.debug_pc;
    trap_pend_cause_ = cause;
    return;
  }

  // --- enqueue ---
  if (disp_valid_ && dis_ready_) {
    MicroOp& du = disp_;
    const int t = rob_tail_;
    rob_enq_fired_ = true;
    rob_enq_unique_ = rob_enq_unique_ || du.is_unique;
    if (du.is_unique) rob_wait_empty_ = true;
    if (du.exception && !rob_xcpt_.v) {
      rob_xcpt_.v = true;
      rob_xcpt_.rob = static_cast<uint8_t>(t);
      rob_xcpt_.br_mask = du.br_mask;
      rob_xcpt_.exc_cause = du.exc_cause;
    }
    rob_val_ |= 1u << t;
    if (du.is_fence || du.is_fencei) rob_busy_ &= ~(1u << t); else rob_busy_ |= 1u << t;
    const bool unsafe = du.uses_ldq || (du.uses_stq && !du.is_fence) || du.is_br || du.is_jalr;
    if (unsafe) rob_unsafe_ |= 1u << t; else rob_unsafe_ &= ~(1u << t);
    if (du.exception) rob_exc_ |= 1u << t; else rob_exc_ &= ~(1u << t);
    inst_[t] = du;
    retirement_debug_[t] = cycle_debug_mode_;
    {
      enq_packed_idx_ = t;
      enq_packed_val_ = pack_rob_uop(du);
    }
    rob_brmask_[t] = du.br_mask;
    rob_brmask_dirty_ = true;
    {
      if (du.fp_val) img_->r.coreRob.rob_uopbank_1_0 |= 1u << (31 - t);
      else img_->r.coreRob.rob_uopbank_1_0 &= ~(1u << (31 - t));
    }
    rob_fflags_[t] = 0;
    rob_tail_ = rob_wrap(rob_tail_ + 1);
    rob_empty_ = false;
  }

  // The LSU exception port writes the row's exception bit and the oldest
  // exception record on this edge (visible to the head next cycle).
  if (lxcpt_valid) {
    const unsigned idx = lsu_r_xcpt_.rob & (kRob - 1);
    rob_exc_ |= 1u << idx;
    if (!rob_xcpt_start.v || lsq_is_older(lsu_r_xcpt_.rob, rob_xcpt_start.rob, rob_head_start_)) {
      rob_xcpt_.v = true;
      rob_xcpt_.rob = lsu_r_xcpt_.rob;
      rob_xcpt_.br_mask = lsu_r_xcpt_.br_mask;
      rob_xcpt_.exc_cause = lsu_r_xcpt_.cause;
    } else {
      rob_xcpt_ = rob_xcpt_start;
    }
  }
  (void)F;
}

}  // namespace chisa::boom_model
