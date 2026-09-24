// model core: FP subsystems (fp-pipeline.scala + the FP halves of
// rename/rob/lsu), ported from the validated model.  Values are computed
// by the connected generated FPU or, for standalone execution / FDIV / I2F,
// by SoftFloat. The idle paths skip work when nothing is in flight.
#include "core.h"
#include "../common/fp_semantics.h"
#include "../common/fp_execute.h"

#include "../../common/softfloat_fp.h"

namespace chisa::boom_model {

namespace {
constexpr uint16_t FP_PORT_FU = FU_FPU | FU_FDV | FU_F2I;

inline bool fp_writes_freg(const MicroOp& u) { return u.dst_rtype == RT_FLT; }
inline void fp_set_null_uop(MicroOp& u) { u.clear(); u.dst_rtype = RT_X; }
inline bool fpq_empty(const FpQEntry* q, int n) { for (int i = 0; i < n; ++i) if (q[i].v) return false; return true; }
inline int fpq_push(FpQEntry* q, int n, const MicroOp& u, uint64_t d, uint8_t fl) {
  for (int i = 0; i < n; ++i) if (!q[i].v) { q[i].v = true; q[i].uop = u; q[i].data = d; q[i].flags = fl; return i; }
  return -1;
}
inline int fpq_head(const FpQEntry* q, int n) { for (int i = 0; i < n; ++i) if (q[i].v) return i; return -1; }
inline void fpq_pop(FpQEntry* q, int n, int idx) {
  for (int i = idx; i + 1 < n; ++i) {
    if (kInternalSignalContract || q[i + 1].v) q[i] = q[i + 1];
    else q[i].v = false;
  }
  if constexpr (kInternalSignalContract) q[n - 1].clear();
  else q[n - 1].v = false;
}
inline void fpq_kill(FpQEntry* q, int n, br_mask_t res, br_mask_t mis) {
  if constexpr (kArchitecturalModel) {
    int live = 0;
    for (int i = 0; i < n; ++i) {
      if (!q[i].v || (q[i].uop.br_mask & mis)) continue;
      if (live != i) q[live] = q[i];
      q[live++].uop.br_mask &= static_cast<br_mask_t>(~res);
    }
    for (; live < n; ++live) q[live].v = false;
    return;
  }
  int w = 0;
  FpQEntry tmp[8];
  for (int i = 0; i < n && i < 8; ++i) tmp[i] = q[i];
  for (int i = 0; i < n; ++i) {
    if (!tmp[i].v) continue;
    if (tmp[i].uop.br_mask & mis) continue;
    tmp[i].uop.br_mask &= static_cast<br_mask_t>(~res);
    q[w++] = tmp[i];
  }
  for (; w < n; ++w) q[w].clear();
}
}  // namespace

// --------------------------------------------------------------------------
void Core::fp_reset() {
  auto& F = img_->r.coreFpRename;
  std::memset(fp_map_, 0, sizeof(fp_map_));
  std::memset(fp_br_snap_, 0, sizeof(fp_br_snap_));
  fp_busy_ = 0;
  fp_map_dirty_ = true;
  for (int b = 0; b < kBr; ++b) F.freelist_br_alloc_lists[b] = 0;
  F.freelist_free_list = boomcfg::pm_all(boomcfg::NUM_FPREGS) & ~boomcfg::pm_bit(0);
  F.freelist_REG = 0;
  F.freelist_r = 0;
  fp_ren_r_ = FpRenFields{}; fp_ren_r_valid_ = false;
  fp_disp_ = FpRenFields{}; fp_disp_valid_ = false;
  fp_ren2_alloc_now_ = false; fp_ren2_alloc_ldst_ = fp_ren2_alloc_pdst_ = 0;
  for (auto& s : fp_iq_) { s = FpSlot{}; s.uop.clear(); s.uop.dst_rtype = RT_X; }
  fp_iq_dirty_ = true;
  std::memset(fp_prf_, 0, sizeof(fp_prf_));
  std::memset(fp_prf_rec_lo_, 0, sizeof(fp_prf_rec_lo_));
  std::memset(fp_prf_rec_hi_, 0, sizeof(fp_prf_rec_hi_));
  fp_iq_start_valid_ = 0;
  fp_iq_ready_ = true;
  fp_port_consumed_ = false;
  ghost_fp_slot_ = -1; ghost_fp_v_ = false; ghost_fp_uop_.clear();
  fdv_mask_this_ = false;
  fp_rrd_uop_.clear(); fp_rrd_valid_ = false;
  fp_exe_uop_.clear(); fp_exe_valid_ = false;
  fp_quiet_streak_ = 0;
  std::memset(fp_read_addrs_, 0, sizeof(fp_read_addrs_));
  for (bool& z : fp_read_zero_r_) z = true;
  fp_rrd_killed_ = false;
  std::memset(fp_rrd_rec_lo_, 0, sizeof(fp_rrd_rec_lo_)); fp_rrd_rec_hi_ = 0;
  std::memset(fp_exe_rec_lo_, 0, sizeof(fp_exe_rec_lo_)); fp_exe_rec_hi_ = 0;
  fpu_inner_uop.clear(); fpu_inner_valid = false;
  std::memset(fpu_inner_rec_lo, 0, sizeof(fpu_inner_rec_lo)); fpu_inner_rec_hi = 0; fpu_inner_fcsr_rm = 0;
  ext_fpu_response_connected = false; ext_fpu_response_valid = false;
  ext_fpu_response_data = 0; ext_fpu_response_data_bit64 = false; ext_fpu_response_flags = 0;
  for (auto& u : fpu_wrapper_uops_) u.clear();
  for (bool& v : fpu_wrapper_valids_) v = false;
  for (auto& e : fpu_pipe_) e.clear();
  for (bool& external : fpu_external_result_) external = false;
  for (auto& e : i2f_pipe_) e.clear();
  for (auto& e : fdiv_req_pipe_) e.clear();
  fdiv_buffer_.clear();
  std::memset(fdiv_buffer_fin_lo_, 0, sizeof(fdiv_buffer_fin_lo_)); fdiv_buffer_fin_hi_ = 0;
  fdiv_pend_.clear(); fdiv_pend_killed_ = false;
  fdiv_out_.clear();
  fdiv_inner_fire = false; fdiv_inner_a = fdiv_inner_b = 0; fdiv_inner_hi = fdiv_inner_rm = 0; fdiv_inner_sqrt = false;
  for (auto& e : f2i_q_) e.clear();
  for (auto& e : fp_sdq_) e.clear();
  for (auto& e : from_int_q_) e.clear();
  f2i_q_mirror_.clear(); fp_sdq_mirror_.clear(); from_int_q_mirror_.clear();
  const sfp::rec_t ifpu_reset_rec = sfp::hf_pub_box_s(0);
  ifpu_out_rec_lo_ = static_cast<uint64_t>(ifpu_reset_rec);
  ifpu_out_rec_hi_ = static_cast<uint8_t>((ifpu_reset_rec >> 64) & 1u);
  ll_wr_reg_.clear();
  ll_wr_rec_lo_ = ifpu_out_rec_lo_;
  ll_wr_rec_hi_ = ifpu_out_rec_hi_;
  std::memset(rob_fflags_, 0, sizeof(rob_fflags_));
  n_fp_slow_wake_ = 0;
  fp_stdata_fire_s1_v_ = false; fp_stdata_fire_s1_stq_ = 0; fp_stdata_fire_s1_brmask_ = 0; fp_stdata_fire_s1_rob_ = 0;
  fp_stdata_stq_qual_start_ = false; fp_stdata_fire_s1_killed_now_ = false;
  fp_ll_ld_v_ = false; fp_ll_ld_uop_ = MemUop{}; fp_ll_ld_data_ = 0;
  fp_ll_rob_r_ = fpiu_rob_r_ = stdf_rob_r_ = 0;
  fpiu_rob_start_ = 0;
}

void Core::fp_flush() {
  fp_set_null_uop(fp_rrd_uop_); fp_rrd_valid_ = false;
  fp_set_null_uop(fp_exe_uop_); fp_exe_valid_ = false;
  fp_quiet_streak_ = 0;
  std::memset(fp_read_addrs_, 0, sizeof(fp_read_addrs_));
  for (bool& z : fp_read_zero_r_) z = true;
  std::memset(fp_rrd_rec_lo_, 0, sizeof(fp_rrd_rec_lo_)); fp_rrd_rec_hi_ = 0;
  std::memset(fp_exe_rec_lo_, 0, sizeof(fp_exe_rec_lo_)); fp_exe_rec_hi_ = 0;
  fp_rrd_killed_ = false;
  for (auto& e : fpu_pipe_) e.clear();
  for (auto& e : i2f_pipe_) e.clear();
  for (auto& e : fdiv_req_pipe_) e.clear();
  fdiv_buffer_.clear();
  fdiv_out_.v = false;
  fdiv_pend_killed_ = fdiv_pend_.v;
  fdv_mask_this_ = false;
  for (auto& e : f2i_q_) e.clear();
  for (auto& e : fp_sdq_) e.clear();
  for (auto& e : from_int_q_) e.clear();
  for (auto& s : fp_iq_) s.state = IS_INVALID;
  fp_iq_dirty_ = true;
}

void Core::fp_apply_brupdate(br_mask_t res, br_mask_t mis) {
  const br_mask_t keep = static_cast<br_mask_t>(~res);
  if (fp_rrd_uop_.br_mask & mis) fp_rrd_killed_ = true;
  if (fp_rrd_valid_ && (fp_rrd_uop_.br_mask & mis)) fp_rrd_valid_ = false;
  fp_rrd_uop_.br_mask &= keep;
  for (int i = 0; i < fp_iq_slots_; ++i) {
    FpSlot& s = fp_iq_[i];
    if (kArchitecturalModel && s.state == IS_INVALID) continue;
    if (s.state != IS_INVALID && (s.uop.br_mask & mis)) s.state = IS_INVALID;
    s.uop.br_mask &= keep;
  }
  fp_iq_dirty_ = true;
  auto kill_infl = [&](FpInflight& e) {
    if (!e.v) return;
    if (e.uop.br_mask & mis) e.v = false; else e.uop.br_mask &= keep;
  };
  for (auto& e : fpu_pipe_) kill_infl(e);
  for (auto& e : i2f_pipe_) kill_infl(e);
  for (auto& e : fdiv_req_pipe_) kill_infl(e);
  kill_infl(fdiv_buffer_);
  if (fdiv_out_.v && (fdiv_out_.uop.br_mask & mis)) fdiv_out_.v = false;
  fdiv_out_.uop.br_mask &= keep;
  if (fdiv_pend_.v) {
    if (fdiv_pend_.uop.br_mask & mis) fdiv_pend_killed_ = true;
    fdiv_pend_.uop.br_mask &= keep;
  }
  fpq_kill(f2i_q_, 8, res, mis);
  fpq_kill(fp_sdq_, 3, res, mis);
  fpq_kill(from_int_q_, 4, res, mis);
  if (fp_stdata_fire_s1_v_) {
    if (fp_stdata_fire_s1_brmask_ & mis) fp_stdata_fire_s1_killed_now_ = true;
    fp_stdata_fire_s1_brmask_ &= keep;
  }
}

// Cycle-start captures of the FP subsystem: the FPUUnit wrapper input, the
// cold-FPU seam record, and the flow-queue read ports of this cycle.
void Core::fp_cycle_start() {
  fpu_wrapper_input_valid_ = fp_exe_valid_ && (fp_exe_uop_.fu_code & (FU_FPU | FU_F2I));
  fp_flush_pipeline_now_ = redirect_pending;
  fpu_inner_valid = fpu_wrapper_input_valid_;
  if (kArchitecturalModel && !fpu_wrapper_input_valid_) return;
  fpu_wrapper_input_uop_ = fp_exe_uop_;
  fpu_inner_uop = fpu_wrapper_input_uop_;
  std::memcpy(fpu_inner_rec_lo, fp_exe_rec_lo_, sizeof(fpu_inner_rec_lo));
  fpu_inner_rec_hi = fp_exe_rec_hi_;
  fpu_inner_fcsr_rm = static_cast<uint8_t>((csr_.fcsr >> 5) & 7u);
}

void Core::fp_snapshot_stdata() {
  fp_stdata_stq_qual_start_ = false;
  fp_stdata_fire_s1_killed_now_ = false;
  if (fp_stdata_fire_s1_v_) {
    const int i = stq_wrap(fp_stdata_fire_s1_stq_);
    fp_stdata_stq_qual_start_ = ((lsq_.st_valid >> i) & 1u) && ((lsq_.st_addr_valid >> i) & 1u) &&
                                !((lsq_.st_virtual >> i) & 1u) && !StqWord::is_amo(lsq_.st_word[i]);
  }
}

void Core::fp_fpu_wrapper_advance() {
  advance_fp_wrapper<kInternalSignalContract>(fpu_wrapper_uops_, fpu_wrapper_valids_,
      {fpu_wrapper_input_uop_.br_mask, fpu_wrapper_input_uop_.rob_idx,
       fpu_wrapper_input_uop_.fu_code}, fpu_wrapper_input_valid_,
      b1_resolve_mask_now_, b1_mispred_mask_now_, fp_flush_pipeline_now_);
}

// --------------------------------------------------------------------------
// FP issue queue (collapsing, one port).
// --------------------------------------------------------------------------
static bool fp_collapse_issue(Core::FpSlot* slot, int N, uint16_t port_fu, uint8_t start_valid,
                              bool port_consumed, bool disp_v, const MicroOp& du,
                              MicroOp& granted_out, int& avail_out, int ghost_slot) {
  int grant_idx = -1;
  if (!port_consumed)
    for (int i = 0; i < N; ++i) {
      const Core::FpSlot& s = slot[i];
      if (s.state == IS_INVALID) continue;
      const bool req = (s.state == IS_VALID_1) ? (s.p1 && s.p2 && s.p3 && s.ppred) : ((s.p1 || s.p2) && s.ppred);
      if (req && (s.uop.fu_code & port_fu)) { grant_idx = i; break; }
    }
  bool store_partial = false;
  if (grant_idx >= 0) {
    Core::FpSlot& gs = slot[grant_idx];
    granted_out = gs.uop;
    if (gs.state == IS_VALID_2) {
      if (gs.p1 && gs.p2 && gs.ppred) {
      } else if (gs.p1) {
        granted_out.lrs2_rtype = RT_X;
        gs.uop.uopc = uopSTD; gs.uop.lrs1_rtype = RT_X; gs.state = IS_VALID_1;
        store_partial = true;
      } else {
        granted_out.uopc = uopSTD; granted_out.lrs1_rtype = RT_X;
        gs.uop.lrs2_rtype = RT_X; gs.state = IS_VALID_1;
        store_partial = true;
      }
    }
  }
  auto issued = [&](int i) { return i == grant_idx && !store_partial; };
  bool vac[9], wbv[9], shamt[9], killed[9];
  for (int i = 0; i < N; ++i) {
    const bool was_valid = ((start_valid >> i) & 1) &&
                           (kInternalSignalContract || slot[i].state != IS_INVALID);
    vac[i] = !was_valid;
    killed[i] = was_valid && (slot[i].state == IS_INVALID);
    wbv[i] = was_valid && !issued(i) && i != ghost_slot;
  }
  vac[N] = !disp_v; wbv[N] = disp_v; killed[N] = false;
  shamt[0] = false;
  for (int i = 1; i <= N; ++i) shamt[i] = shamt[i - 1] || vac[i - 1];
  avail_out = 0;
  for (int i = 0; i < N; ++i) {
    const bool recv_in = shamt[i + 1] && wbv[i + 1];
    if ((!wbv[i] || shamt[i]) && !recv_in) avail_out++;
    if (recv_in) {
      Core::FpSlot& dst = slot[i];
      if (i + 1 == N) {
        const bool two = (du.uopc == uopSTA && du.lrs2_rtype == RT_FIX) || du.uopc == uopAMO_AG;
        dst.state = two ? IS_VALID_2 : IS_VALID_1;
        dst.uop = du;
        dst.p1 = !du.prs1_busy; dst.p2 = !du.prs2_busy; dst.p3 = !du.prs3_busy; dst.ppred = !du.ppred_busy;
        dst.p1_poisoned = dst.p2_poisoned = false;
      } else {
        const Core::FpSlot& src = slot[i + 1];
        dst = src;
        if (killed[i + 1]) dst.state = IS_INVALID;
      }
    } else if (shamt[i]) {
      slot[i].state = IS_INVALID;
    } else if (issued(i)) {
      slot[i].state = IS_INVALID;
    }
  }
  return grant_idx >= 0;
}

static void fp_wake_slots(Core::FpSlot* slot, int N, uint8_t p) {
  for (int i = 0; i < N; ++i) {
    Core::FpSlot& s = slot[i];
    if (kArchitecturalModel && s.state == IS_INVALID) continue;
    if (s.uop.prs1 == p) s.p1 = true;
    if (s.uop.prs2 == p) s.p2 = true;
    if (s.uop.prs3 == p) s.p3 = true;
  }
}

void Core::fp_issue_step(bool to_fp) {
  uint16_t fu = FU_FPU;
  bool fdiv_req_now = false;
  for (const auto& e : fdiv_req_pipe_) fdiv_req_now |= e.v && e.left == 1;
  const bool fdiv_busy = fdiv_buffer_.v || fdiv_req_now;
  if (!fdiv_busy && !fdv_mask_this_) fu |= FU_FDV;
  const bool fpiu_busy = !fpq_empty(f2i_q_, 8) || !fpq_empty(fp_sdq_, 3);
  if (!fpiu_busy) fu |= FU_F2I;
  cur_fp_fu_ = fu;

  const bool fp_quiet = fp_iq_start_valid_ == 0 && !to_fp && !ghost_fp_v_ && !fp_rrd_killed_ &&
                        !fp_rrd_valid_ && !fp_exe_valid_;
  if (fp_quiet && (kArchitecturalModel || fp_quiet_streak_ >= 2)) {
    fp_iq_ready_ = true;
    fdv_mask_this_ = false;
    return;
  }
  fp_iq_dirty_ = true;

  MicroOp du = disp_;
  if (to_fp && du.uopc == uopSTA) { du.lrs1_rtype = RT_X; du.prs1_busy = 0; }

  MicroOp grant;
  if constexpr (kInternalSignalContract) fp_set_null_uop(grant);
  int avail = 0;
  const bool iss = fp_collapse_issue(fp_iq_, fp_iq_slots_, cur_fp_fu_, fp_iq_start_valid_, fp_port_consumed_,
                                     to_fp, du, grant, avail, ghost_fp_v_ ? ghost_fp_slot_ : -1);
  fp_iq_ready_ = avail > 0;
  fdv_mask_this_ = iss && (grant.fu_code & FU_FDV);

  if constexpr (kArchitecturalModel) {
    fp_exe_valid_ = fp_rrd_valid_ && !fp_rrd_killed_;
    if (fp_exe_valid_) fp_exe_uop_ = fp_rrd_uop_;
  } else if (fp_rrd_killed_) {
    const br_mask_t surviving = fp_rrd_uop_.br_mask;
    fp_set_null_uop(fp_exe_uop_);
    fp_exe_uop_.br_mask = surviving;
    fp_exe_valid_ = false;
  } else {
    fp_exe_uop_ = fp_rrd_uop_;
    fp_exe_valid_ = fp_rrd_valid_;
  }
  if (kInternalSignalContract || fp_exe_valid_) {
    std::memcpy(fp_exe_rec_lo_, fp_rrd_rec_lo_, sizeof(fp_exe_rec_lo_));
    fp_exe_rec_hi_ = fp_rrd_rec_hi_;
  }
  if (kInternalSignalContract || iss) fp_rrd_uop_ = grant;
  fp_rrd_valid_ = iss;
  if (kInternalSignalContract || iss) {
  fp_read_addrs_[0] = grant.prs1 & 0x3f;
  fp_read_addrs_[1] = grant.prs2 & 0x3f;
  fp_read_addrs_[2] = grant.prs3 & 0x3f;
  fp_rrd_rec_hi_ = 0;
  for (int i = 0; i < 3; ++i) {
    fp_read_zero_r_[i] = fp_read_addrs_[i] == 0;
    const int idx = fp_read_addrs_[i] % boomcfg::NUM_FPREGS;
    const sfp::rec_t rec = fp_read_zero_r_[i] ? static_cast<sfp::rec_t>(0)
                          : ((static_cast<sfp::rec_t>(fp_prf_rec_hi_[idx] & 1u) << 64) | fp_prf_rec_lo_[idx]);
    fp_rrd_rec_lo_[i] = static_cast<uint64_t>(rec);
    fp_rrd_rec_hi_ |= static_cast<uint8_t>(((rec >> 64) & 1u) << i);
  }
  }
  fp_rrd_killed_ = false;
  fp_quiet_streak_ = (fp_quiet && !iss) ? static_cast<uint8_t>(fp_quiet_streak_ < 2 ? fp_quiet_streak_ + 1 : 2) : 0;
  if (!iss) return;

  const uint32_t rm = fp_rm(grant, csr_);
  const uint64_t a = fp_prf_[grant.prs1 % boomcfg::NUM_FPREGS];
  const uint64_t b = fp_prf_[grant.prs2 % boomcfg::NUM_FPREGS];
  const uint64_t c = fp_prf_[grant.prs3 % boomcfg::NUM_FPREGS];
  if (grant.uopc == uopSTA) {
    const uint64_t data = fp_store_bits(b, grant.fp_single);
    for (auto& e : fpu_pipe_)
      if (!e.v) {
        fpu_external_result_[&e - fpu_pipe_] = false;
        e.v = true; e.uop = grant; e.left = 3; e.ieee = data; e.flags = 0; return;
      }
    return;
  }
  if (grant.fu_code & FU_FDV) {
    // This elaboration's wrapper takes CSR frm and lowers both floating
    // tininess inputs (declared DontCare) to zero: before rounding.
    const uint32_t div_rm = (csr_.fcsr >> 5) & 7u;
    const auto saved_tininess = softfloat_detectTininess;
    softfloat_detectTininess = softfloat_tininess_beforeRounding;
    const sfp::FpRes r = fp_compute(grant, div_rm, a, b, c);
    softfloat_detectTininess = saved_tininess;
    FpInflight* request = nullptr;
    for (auto& e : fdiv_req_pipe_) if (!e.v) { request = &e; break; }
    if (!request) return;
    request->clear();
    request->v = true;
    request->uop = grant;
    request->left = 3;
    request->ieee = r.ieee;
    request->flags = r.exc;
    const bool single = grant.uopc == uopFDIV_S || grant.uopc == uopFSQRT_S;
    auto recode_operand = [single](uint64_t operand) {
      if (!single) return sfp::rec65_from_fn64(operand);
      const sfp::FpRes widened = sfp::cvt_s_to_d(0, sfp::unbox32(operand));
      return sfp::rec65_from_fn64(widened.ieee);
    };
    const sfp::rec_t rec_a = recode_operand(a);
    const sfp::rec_t rec_b = recode_operand(b);
    request->rec_a = static_cast<uint64_t>(rec_a);
    request->rec_b = static_cast<uint64_t>(rec_b);
    request->rec_hi = static_cast<uint8_t>(((rec_a >> 64) & 1u) | (((rec_b >> 64) & 1u) << 1));
    request->rm = static_cast<uint8_t>(div_rm);
    request->sqrt = grant.uopc == uopFSQRT_S || grant.uopc == uopFSQRT_D;
    if (request->sqrt) {
      request->rec_b = request->rec_a;
      request->rec_hi = static_cast<uint8_t>((request->rec_hi & 1u) | ((request->rec_hi & 1u) << 1));
    }
    const bool special = fp_divsqrt_special(grant, a, b);
    request->exec_cycles = special ? 1 : (request->sqrt ? 26 : 18);
    return;
  }
  // The connected generated FPU supplies the exact result and flags. In
  // that mode the software pipe carries only identity/latency; standalone
  // core execution keeps its original SoftFloat implementation.
  const bool external_result = ext_fpu_response_connected;
  const sfp::FpRes r = external_result ? sfp::FpRes{0, 0} : fp_compute(grant, rm, a, b, c);
  for (auto& e : fpu_pipe_)
    if (!e.v) {
      fpu_external_result_[&e - fpu_pipe_] = external_result;
      e.v = true; e.uop = grant; e.left = 7; e.ieee = r.ieee; e.flags = r.exc; return;
    }
}

void Core::fp_i2f_launch(const MicroOp& u, uint64_t rs1) {
  const sfp::FpRes r = fp_compute_i2f(u, fp_rm(u, csr_), rs1);
  for (auto& e : i2f_pipe_)
    if (!e.v) { e.v = true; e.uop = u; e.left = 5; e.ieee = r.ieee; e.flags = r.exc; return; }
}

void Core::fp_wakeup(uint8_t pdst, uint8_t rob, uint8_t flags) {
  rob_busy_ &= ~(1u << rob);
  rob_unsafe_ &= ~(1u << rob);
  rob_fflags_[rob & (kRob - 1)] = flags;
  if (n_fp_slow_wake_ < 8) fp_slow_wake_[n_fp_slow_wake_++] = pdst;
}

// --------------------------------------------------------------------------
void Core::fp_pipe_advance() {
  FpWrapperUop wrapper_response = fpu_wrapper_uops_[3];
  const bool wrapper_response_valid = fpu_wrapper_valids_[3] &&
      !(wrapper_response.br_mask & b1_mispred_mask_now_) && !fp_flush_pipeline_now_;
  wrapper_response.br_mask &= static_cast<br_mask_t>(~b1_resolve_mask_now_);
  fdiv_inner_fire = false;
  fp_stdata_fire_s1_v_ = false;
  {
    bool idle = !fdiv_buffer_.v && !fdiv_pend_.v && !fdiv_out_.v && !fp_ll_ld_v_ && n_fp_slow_wake_ == 0;
    for (const auto& e : fpu_pipe_) idle = idle && !e.v;
    for (const auto& e : i2f_pipe_) idle = idle && !e.v;
    for (const auto& e : fdiv_req_pipe_) idle = idle && !e.v;
    idle = idle && fpq_empty(f2i_q_, 8) && fpq_empty(fp_sdq_, 3) && fpq_empty(from_int_q_, 4);
    if (idle) {
      ll_wr_reg_.clear();
      ll_wr_reg_.uop = inst(oracle_b3_);
      ll_wr_reg_.uop.br_mask = oracle_b3_.br_mask;
      ll_wr_rec_lo_ = ifpu_out_rec_lo_;
      ll_wr_rec_hi_ = ifpu_out_rec_hi_;
      static const FpQEntry kNoEnq = [] { FpQEntry e; e.clear(); return e; }();
      const br_mask_t queue_resolve = b1_resolve_mask_now_;
      const br_mask_t queue_mispredict = b1_mispred_mask_now_;
      const bool queue_flush = flush_redirect_now_;
      const bool int_ll_deq_ready = !out_ext_irf_write_valids[0];
      const bool f2i_deq_valid = f2i_q_mirror_.deq_valid(false, queue_mispredict, queue_flush);
      const bool fp_sdq_deq_ready = int_ll_deq_ready && !f2i_deq_valid;
      // The mirrors only move when something is queued or a kill arrives.
      if (!from_int_q_mirror_.empty() || !f2i_q_mirror_.empty() || !fp_sdq_mirror_.empty() ||
          queue_mispredict || queue_flush || queue_resolve) {
        from_int_q_mirror_.step(false, kNoEnq, true, queue_resolve, queue_mispredict, queue_flush);
        f2i_q_mirror_.step(false, kNoEnq, int_ll_deq_ready, queue_resolve, queue_mispredict, queue_flush);
        fp_sdq_mirror_.step(false, kNoEnq, fp_sdq_deq_ready, queue_resolve, queue_mispredict, queue_flush);
      }
      fpiu_rob_r_ = wrapper_response_valid ? wrapper_response.rob_idx : fdiv_out_.uop.rob_idx;
      return;
    }
  }
  FpQEntry ll_winner;
  ll_winner.clear();
  sfp::rec_t ll_winner_rec = (static_cast<sfp::rec_t>(ifpu_out_rec_hi_ & 1u) << 64) | ifpu_out_rec_lo_;
  FpQEntry f2i_enq, fp_sdq_enq, from_int_enq;
  f2i_enq.clear(); fp_sdq_enq.clear(); from_int_enq.clear();
  {
    ll_winner.uop = inst(oracle_b3_);
    ll_winner.uop.br_mask = oracle_b3_.br_mask;
  }

  // (1) FPU fixed pipe expiries.
  bool fpu_resp_valid = false;
  bool external_result_consumed = false;
  for (unsigned slot = 0; slot < 10; ++slot) {
    auto& e = fpu_pipe_[slot];
    if (!e.v) continue;
    if (--e.left != 0) continue;
    if (fpu_external_result_[slot]) {
      require_external_fp_result(ext_fpu_response_connected, ext_fpu_response_valid,
          wrapper_response_valid, wrapper_response,
          {e.uop.br_mask, e.uop.rob_idx, e.uop.fu_code}, external_result_consumed, cycle_count_);
      external_result_consumed = true;
    }
    e.v = false;
    if (e.uop.uopc == uopSTA) {
      fp_sdq_enq.v = true; fp_sdq_enq.uop = e.uop; fp_sdq_enq.data = e.ieee; fp_sdq_enq.flags = 0;
      fpq_push(fp_sdq_, 3, e.uop, e.ieee, 0);
    } else if (e.uop.fu_code & FU_F2I) {
      if (ext_fpu_response_connected && ext_fpu_response_valid) { e.ieee = ext_fpu_response_data; e.flags = ext_fpu_response_flags; }
      fpu_resp_valid = true;
      f2i_enq.v = true; f2i_enq.uop = e.uop; f2i_enq.data = e.ieee; f2i_enq.flags = e.flags;
      fpq_push(f2i_q_, 8, e.uop, e.ieee, e.flags);
    } else {
      sfp::rec_t exact_rec = 0;
      bool exact_rec_valid = false;
      if (ext_fpu_response_connected && ext_fpu_response_valid) {
        exact_rec = (static_cast<sfp::rec_t>(ext_fpu_response_data_bit64 ? 1u : 0u) << 64) | ext_fpu_response_data;
        e.ieee = sfp::ieee64_view(exact_rec);
        e.flags = ext_fpu_response_flags;
        exact_rec_valid = true;
      }
      fpu_resp_valid = true;
      if (fp_writes_freg(e.uop) && e.uop.pdst != 0) {
        const int idx = e.uop.pdst % boomcfg::NUM_FPREGS;
        fp_prf_[idx] = e.ieee;
        const sfp::rec_t rec = exact_rec_valid ? exact_rec : fp_result_rec(e.uop, e.ieee);
        fp_prf_rec_lo_[idx] = static_cast<uint64_t>(rec);
        fp_prf_rec_hi_[idx] = static_cast<uint8_t>((rec >> 64) & 1u);
      }
      fp_wakeup(e.uop.pdst, e.uop.rob_idx, e.flags);
    }
  }

  // (2) FDivSqrt stages.
  const bool fdiv_active_at_start = fdiv_pend_.v;
  const bool fdiv_buffer_at_start = fdiv_buffer_.v;
  const bool fdiv_out_at_start = fdiv_out_.v;
  if (fdiv_out_at_start && !fpu_resp_valid) {
    const FpInflight done = fdiv_out_;
    fdiv_out_.v = false;
    if (fp_writes_freg(done.uop) && done.uop.pdst != 0) {
      const int idx = done.uop.pdst % boomcfg::NUM_FPREGS;
      fp_prf_[idx] = done.ieee;
      const sfp::rec_t rec = fp_result_rec(done.uop, done.ieee);
      fp_prf_rec_lo_[idx] = static_cast<uint64_t>(rec);
      fp_prf_rec_hi_[idx] = static_cast<uint8_t>((rec >> 64) & 1u);
    }
    fp_wakeup(done.uop.pdst, done.uop.rob_idx, done.flags);
  }
  if (fdiv_active_at_start && --fdiv_pend_.left == 0) {
    const FpInflight done = fdiv_pend_;
    fdiv_pend_.clear();
    fdiv_out_ = done;
    fdiv_out_.v = !fdiv_pend_killed_;
    fdiv_pend_killed_ = false;
  }
  if (!fdiv_active_at_start && !fdiv_out_at_start && fdiv_buffer_at_start) {
    fdiv_pend_ = fdiv_buffer_;
    fdiv_pend_.v = true;
    fdiv_pend_.left = fdiv_pend_.exec_cycles;
    fdiv_pend_killed_ = false;
    fdiv_inner_fire = true;
    fdiv_inner_a = fdiv_buffer_.rec_a;
    fdiv_inner_b = fdiv_buffer_.rec_b;
    fdiv_inner_hi = fdiv_buffer_.rec_hi;
    fdiv_inner_rm = fdiv_buffer_.rm;
    fdiv_inner_sqrt = fdiv_buffer_.sqrt;
    fdiv_buffer_.clear();
  }
  for (auto& e : fdiv_req_pipe_) {
    if (!e.v || --e.left != 0) continue;
    if (!fdiv_buffer_.v) {
      fdiv_buffer_ = e;
      fdiv_buffer_.v = true;
      fdiv_buffer_fin_lo_[0] = e.rec_a;
      fdiv_buffer_fin_lo_[1] = e.rec_b;
      fdiv_buffer_fin_hi_ = static_cast<uint8_t>(e.rec_hi & 3u);
    }
    e.clear();
  }

  // (3) IntToFP pipe expiries -> from_int queue.
  for (auto& e : i2f_pipe_) {
    if (!e.v) continue;
    if (--e.left != 0) continue;
    e.v = false;
    from_int_enq.v = true; from_int_enq.uop = e.uop; from_int_enq.data = e.ieee; from_int_enq.flags = e.flags;
    const sfp::rec_t ifpu_result = fp_result_rec(e.uop, e.ieee);
    ifpu_out_rec_lo_ = static_cast<uint64_t>(ifpu_result);
    ifpu_out_rec_hi_ = static_cast<uint8_t>((ifpu_result >> 64) & 1u);
    fpq_push(from_int_q_, 4, e.uop, e.ieee, e.flags);
  }

  const br_mask_t queue_resolve = b1_resolve_mask_now_;
  const br_mask_t queue_mispredict = b1_mispred_mask_now_;
  const bool queue_flush = flush_redirect_now_;
  const bool from_int_deq_ready = !fp_ll_ld_v_;
  const bool int_ll_deq_ready = !out_ext_irf_write_valids[0];
  const bool f2i_deq_valid = f2i_q_mirror_.deq_valid(f2i_enq.v, queue_mispredict, queue_flush);
  const bool fp_sdq_deq_ready = int_ll_deq_ready && !f2i_deq_valid;

  // (4) fp ll arb: mem FP load (priority) vs from_int head.
  if (fp_ll_ld_v_) {
    const MemUop& lu = fp_ll_ld_uop_;
    ll_winner.v = true;
    ll_winner.uop = inst_[lu.rob];
    ll_winner.uop.br_mask = lu.br_mask;
    ll_winner.uop.pdst = lu.pdst;
    ll_winner.data = fp_ll_ld_data_;
    ll_winner.flags = 0;
    ll_winner_rec = sfp::hf_recode64(fp_ll_ld_data_, lu.fp_val && inst_[lu.rob].fp_single);
    if (lu.pdst != 0) {
      const int idx = lu.pdst % boomcfg::NUM_FPREGS;
      fp_prf_[idx] = inst_[lu.rob].fp_single ? sfp::box32(static_cast<uint32_t>(fp_ll_ld_data_)) : fp_ll_ld_data_;
      const sfp::rec_t rec = sfp::hf_recode64(fp_ll_ld_data_, inst_[lu.rob].fp_single);
      fp_prf_rec_lo_[idx] = static_cast<uint64_t>(rec);
      fp_prf_rec_hi_[idx] = static_cast<uint8_t>((rec >> 64) & 1u);
    }
    rob_fflags_[lu.rob & (kRob - 1)] = 0;
    if (n_fp_slow_wake_ < 8) fp_slow_wake_[n_fp_slow_wake_++] = lu.pdst;
    fp_ll_ld_v_ = false;
  } else {
    const int h = fpq_head(from_int_q_, 4);
    if (h >= 0) {
      const FpQEntry e = from_int_q_[h];
      ll_winner = e;
      ll_winner_rec = fp_result_rec(e.uop, e.data);
      fpq_pop(from_int_q_, 4, h);
      // Small's third asynchronous ROB read port observes the live image.
      rob_read_bsy_now_[2] = (rob_busy_ >> (e.uop.rob_idx & (kRob - 1))) & 1u;
      rob_read_uop_packed_now_[2] = uop_packed_[e.uop.rob_idx & (kRob - 1)];
      if (e.uop.pdst != 0) {
        const int idx = e.uop.pdst % boomcfg::NUM_FPREGS;
        fp_prf_[idx] = e.data;
        const sfp::rec_t rec = fp_result_rec(e.uop, e.data);
        fp_prf_rec_lo_[idx] = static_cast<uint64_t>(rec);
        fp_prf_rec_hi_[idx] = static_cast<uint8_t>((rec >> 64) & 1u);
      }
      fp_wakeup(e.uop.pdst, e.uop.rob_idx, e.flags);
    }
  }
  {
    ll_wr_reg_ = ll_winner;
    ll_wr_rec_lo_ = static_cast<uint64_t>(ll_winner_rec);
    ll_wr_rec_hi_ = static_cast<uint8_t>((ll_winner_rec >> 64) & 1u);
  }

  // (5) fpiu ll_iresp: f2i queue > fp_sdq, one per cycle.
  const int fh = fpq_head(f2i_q_, 8);
  if (fh >= 0) {
    if (!out_ext_irf_write_valids[0]) {
      const FpQEntry e = f2i_q_[fh];
      fpq_pop(f2i_q_, 8, fh);
      fpiu_rob_r_ = e.uop.rob_idx;
      const unsigned rob = e.uop.rob_idx & (kRob - 1);
      rob_read_port(0, rob, (rob_busy_start_ >> rob) & 1u);
      rob_busy_ &= ~(1u << rob);
      rob_unsafe_ &= ~(1u << rob);
      rob_fflags_[rob] = e.flags;
      if (e.uop.pdst != 0) { prf_.wr(e.uop.pdst, e.data); prf_landed.wr(e.uop.pdst, e.data); }
      out_ext_irf_write_valids[0] = 1;
      out_ext_irf_write_addrs[0] = e.uop.pdst;
      out_ext_irf_write_datas[0] = e.data;
      busy_ &= ~boomcfg::pm_bit(e.uop.pdst);
      iq_wake(int_iq_, e.uop.pdst);
      iq_wake(mem_iq_, e.uop.pdst);
    }
  } else {
    const int sh = fpq_head(fp_sdq_, 3);
    if (sh >= 0) {
      const FpQEntry e = fp_sdq_[sh];
      fpq_pop(fp_sdq_, 3, sh);
      stdf_rob_r_ = e.uop.rob_idx;
      const int si = stq_wrap(e.uop.stq_idx);
      if ((lsq_.st_valid >> si) & 1u) {
        img_->r.lsu.stq_bits_data_bits[si] = storegen_replicate(StqWord::mem_size(lsq_.st_word[si]), e.data);
        lsq_.st_data_valid |= static_cast<uint8_t>(1u << si);
        stq_dirty_ = true;
        fp_stdata_fire_s1_v_ = true;
        fp_stdata_fire_s1_stq_ = e.uop.stq_idx;
        fp_stdata_fire_s1_brmask_ = e.uop.br_mask;
        fp_stdata_fire_s1_rob_ = e.uop.rob_idx;
      }
    }
  }
  {
    from_int_q_mirror_.step(from_int_enq.v, from_int_enq, from_int_deq_ready, queue_resolve, queue_mispredict, queue_flush);
    f2i_q_mirror_.step(f2i_enq.v, f2i_enq, int_ll_deq_ready, queue_resolve, queue_mispredict, queue_flush);
    fp_sdq_mirror_.step(fp_sdq_enq.v, fp_sdq_enq, fp_sdq_deq_ready, queue_resolve, queue_mispredict, queue_flush);
    fpiu_rob_r_ = wrapper_response_valid ? wrapper_response.rob_idx : fdiv_out_.uop.rob_idx;
  }

  // (6) Deferred FP wakeups (registered).
  for (int i = 0; i < n_fp_slow_wake_; ++i) {
    fp_busy_ &= ~boomcfg::pm_bit(fp_slow_wake_[i]);
    fp_wake_slots(fp_iq_, fp_iq_slots_, fp_slow_wake_[i]);
  }
  if (n_fp_slow_wake_) fp_iq_dirty_ = true;
  n_fp_slow_wake_ = 0;
}

void Core::fp_commit(const MicroOp& u) {
  if (u.fp_val && !u.uses_stq) {
    const uint8_t fl = rob_fflags_[u.rob_idx & (kRob - 1)];
    csr_.fcsr = (csr_.fcsr & ~0x1FULL) | ((csr_.fcsr | fl) & 0x1F);
    csr_.mstatus |= (3ULL << 13);
    csr_export();
  }
}

void Core::fp_commit_free(const MicroOp& u) {
  if (u.ldst_val && u.dst_rtype == RT_FLT) {
    if (u.stale_pdst != 0) img_->r.coreFpRename.freelist_free_list |= boomcfg::pm_bit(u.stale_pdst);
  }
}

void Core::fp_rollback(const MicroOp& u) {
  if (u.ldst_val && u.dst_rtype == RT_FLT) {
    fp_map_write(u.ldst, u.stale_pdst);
    if (u.pdst != 0) img_->r.coreFpRename.freelist_free_list |= boomcfg::pm_bit(u.pdst);
  }
}

// Contract image of the FP pipeline registers the hot model owns.
void Core::fp_export() {
  auto& F = img_->r.coreFp;
  if (fp_iq_dirty_) {
    for (int i = 0; i < 8; ++i) {
      const FpSlot& s = fp_iq_[i];
      F.fp_issue_unit_slots_p1[i] = bit(s.p1);
      F.fp_issue_unit_slots_p2[i] = bit(s.p2);
      F.fp_issue_unit_slots_p3[i] = bit(s.p3);
      F.fp_issue_unit_slots_ppred[i] = bit(s.ppred);
      F.fp_issue_unit_slots_state[i] = s.state & 3;
      F.fp_issue_unit_slots_slot_uopbank_2_0[i] = pack_fp_iq_slot(s.uop.uopc, s.uop.br_mask);
    }
    fp_iq_dirty_ = false;
  }
  F.fp_issue_unit_REG = bit(fp_iq_ready_);
  F.REG = fdv_mask_this_ ? 0x37f : 0x3ff;
  F.REG_1_valid = bit(ll_wr_reg_.v);
  F.REG_1_bits_addr = ll_wr_reg_.uop.pdst & 0x3f;
  F.fpiu_unit_BranchKillableQueueinst_uopsbank_1_0 = f2i_q_mirror_.packed_br_masks_bank(0);
  F.fpiu_unit_BranchKillableQueueinst_maybe_full = bit(f2i_q_mirror_.maybe_full);
  F.fpiu_unit_BranchKillableQueueinst_validsbank_0_0 = static_cast<uint8_t>(f2i_q_mirror_.packed_valids());
  F.fpiu_unit_BranchKillableQueueinst_value = f2i_q_mirror_.enq_ptr & 7;
  F.fpiu_unit_BranchKillableQueueinst_value_1 = f2i_q_mirror_.deq_ptr & 7;
  F.fpiu_unit_BranchKillableQueue_1_uopsbank_1_0 = static_cast<uint32_t>(fp_sdq_mirror_.packed_br_masks_bank(0));
  F.fpiu_unit_BranchKillableQueue_1_maybe_full = bit(fp_sdq_mirror_.maybe_full);
  F.fpiu_unit_BranchKillableQueue_1_validsbank_0_0 = static_cast<uint8_t>(fp_sdq_mirror_.packed_valids());
  F.fpiu_unit_BranchKillableQueue_1_value = fp_sdq_mirror_.enq_ptr & 3;
  F.fpiu_unit_BranchKillableQueue_1_value_1 = fp_sdq_mirror_.deq_ptr & 3;
  F.fpiu_unit_fdivsqrt_r_buffer_val = bit(fdiv_buffer_.v);
  F.fpiu_unit_fdivsqrt_r_out_uop_br_mask = fdiv_out_.uop.br_mask;
  F.fpiu_unit_fdivsqrt_r_out_uop_dst_rtype = fdiv_out_.uop.dst_rtype & 3;
  F.fpiu_unit_fdivsqrt_r_out_uop_rob_idx = fdiv_out_.uop.rob_idx & 0x1f;
  F.fpiu_unit_fdivsqrt_r_out_val = bit(fdiv_out_.v);
  F.fpiu_unit_fpu_REG_1_3_fu_code = fpu_wrapper_uops_[3].fu_code & 0x3ff;
  F.fpiu_unit_fpu_REG_3 = bit(fpu_wrapper_valids_[3]);
  F.fregfile_read_addrs[0] = fp_read_addrs_[0] & 0x3f;
  F.fregfile_read_addrs[1] = fp_read_addrs_[1] & 0x3f;
  F.fregfile_read_addrs[2] = fp_read_addrs_[2] & 0x3f;
  F.fregister_read_REG_1_br_mask = fp_rrd_uop_.br_mask;
  F.fregister_read_REG_2 = bit(fp_read_zero_r_[0]);
  F.fregister_read_REG_3 = bit(fp_read_zero_r_[1]);
  F.fregister_read_REG_4 = bit(fp_read_zero_r_[2]);
  F.fregister_read_exe_reg_uops_0_fu_code = fp_exe_uop_.fu_code & 0x3ff;
  F.fregister_read_exe_reg_uops_0_dst_rtype = fp_exe_uop_.dst_rtype & 3;
  F.fregister_read_exe_reg_uops_0_is_amo = fp_exe_uop_.is_amo & 1;
  F.fregister_read_exe_reg_uops_0_pdst = fp_exe_uop_.pdst & 0x3f;
  F.fregister_read_exe_reg_uops_0_rob_idx = fp_exe_uop_.rob_idx & 0x1f;
  F.fregister_read_exe_reg_uops_0_stq_idx = fp_exe_uop_.stq_idx & 7;
  F.fregister_read_exe_reg_uops_0_uopc = fp_exe_uop_.uopc & 0x7f;
  F.fregister_read_exe_reg_uops_0_uses_stq = fp_exe_uop_.uses_stq & 1;
  F.fregister_read_exe_reg_valids_0 = bit(fp_exe_valid_);
  auto& E = img_->r.coreCsrExe;
  E.BranchKillableQueueinst_uopsbank_0_0 = from_int_q_mirror_.packed_br_masks_bank(0);
  E.BranchKillableQueueinst_maybe_full = bit(from_int_q_mirror_.maybe_full);
  E.BranchKillableQueueinst_validsbank_0_0 = static_cast<uint8_t>(from_int_q_mirror_.packed_valids());
  E.BranchKillableQueueinst_value = from_int_q_mirror_.enq_ptr & 7;
  E.BranchKillableQueueinst_value_1 = from_int_q_mirror_.deq_ptr & 7;
  // Flow-queue read ports at deq_ptr: pure register reads of the post-edge
  // mirrors (the next position's value).
  img_->c.coreCsrExe.BranchKillableQueueinst_ram_fflags_bits_uop_rob_idx_MPORT_1 = from_int_q_mirror_.ram_fflags_rob_idx_at_deq();
  img_->c.coreFp.fpiu_unit_BranchKillableQueueinst_ram_fflags_bits_uop_rob_idx_MPORT_1 = f2i_q_mirror_.ram_fflags_rob_idx_at_deq();
  img_->c.coreFp.fpiu_unit_BranchKillableQueue_1_ram_fflags_bits_uop_rob_idx_MPORT_1 = fp_sdq_mirror_.ram_fflags_rob_idx_at_deq();
}

}  // namespace chisa::boom_model
