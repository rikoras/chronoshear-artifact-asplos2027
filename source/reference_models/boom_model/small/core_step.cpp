// model core: reset, the cycle-start snapshot, dispatch/decode, the
// end-of-cycle register advance and the contract-image export.  The phase
// order is the RTL evaluation order the previous model validated; only the
// storage changed.
#include "core.h"
#include "../common/integer_divider.h"
#include "../common/csr_logic.h"

namespace chisa::boom_model {

uint64_t decode_imm(const MicroOp& u);
uint64_t mul_op(uint8_t fn, uint64_t a, uint64_t b, bool word);

namespace {
constexpr uint16_t INT_FU = FU_ALU | FU_JMP | FU_MUL | FU_DIV | FU_CSR;
inline uint64_t load8(const uint8_t* p) { uint64_t v; std::memcpy(&v, p, 8); return v; }
inline int64_t sext(uint64_t x, int bits) {
  const uint64_t m = 1ULL << (bits - 1);
  return static_cast<int64_t>((x ^ m) - m);
}
}  // namespace

Core::Core() {
  std::memset(map_, 0, sizeof(map_));
  std::memset(fp_map_, 0, sizeof(fp_map_));
  std::memset(br_snap_, 0, sizeof(br_snap_));
  std::memset(fp_br_snap_, 0, sizeof(fp_br_snap_));
  std::memset(uop_packed_, 0, sizeof(uop_packed_));
  std::memset(rob_brmask_, 0, sizeof(rob_brmask_));
  std::memset(rob_fflags_, 0, sizeof(rob_fflags_));
  for (auto& u : inst_) u.clear();
  std::memset(&int_iq_, 0, sizeof(int_iq_));
  std::memset(&mem_iq_, 0, sizeof(mem_iq_));
  prf_.clear();
  prf_landed.clear();
  csr_.clear();
  ren_r_.clear(); disp_.clear(); dec_view_.clear(); fp_uop.clear();
}

// --------------------------------------------------------------------------
void Core::reset(uint64_t boot_pc) {
  ++sched_epoch_;
  (void)boot_pc;
  architectural_.reset();
  Image& I = *img_;
  reset_owned(I);   // only the streams this model owns (generated/image.h)
  iq_bind(int_iq_, true);
  iq_bind(mem_iq_, false);
  int_iq_.live = mem_iq_.live = 0;

  std::memset(map_, 0, sizeof(map_));
  std::memset(br_snap_, 0, sizeof(br_snap_));
  I.r.coreRename.freelist_free_list = boomcfg::pm_all(kPregs) & ~boomcfg::pm_bit(0);
  busy_ = 0;
  map_dirty_ = true;
  for (auto& u : inst_) u.clear();
  std::memset(uop_packed_, 0, sizeof(uop_packed_));
  std::memset(rob_brmask_, 0, sizeof(rob_brmask_));
  std::memset(rob_fflags_, 0, sizeof(rob_fflags_));
  enq_packed_idx_ = -1;
  rob_brmask_dirty_ = true;
  rob_val_ = rob_busy_ = rob_unsafe_ = rob_exc_ = 0;
  rob_flags_export_valid_ = false;
  rob_head_ = rob_tail_ = 0;
  rob_empty_ = true;
  rob_wait_empty_ = false;
  rob_xcpt_ = XcptRec{};
  rob_state_ = 0; rob_pnr_ = 0; pnr_maybe_at_tail_ = false; maybe_full_ = false;
  block_commit_r_ = block_commit_r2_ = false;
  rob_enq_fired_ = rob_deq_fired_ = rob_enq_unique_ = false;
  // Issue slots: RegInit of the slot uop has dst_rtype = RT_X, every other
  // payload field zero; the packed word is therefore zero.
  {
    uint8_t* cols[] = {int_iq_.rob, int_iq_.prs1, int_iq_.prs2, int_iq_.prs3, int_iq_.uopc, int_iq_.rt1,
                       int_iq_.rt2, int_iq_.br_mask, int_iq_.iq_flags, mem_iq_.rob, mem_iq_.prs1, mem_iq_.prs2,
                       mem_iq_.prs3, mem_iq_.uopc, mem_iq_.rt1, mem_iq_.rt2, mem_iq_.br_mask, mem_iq_.iq_flags};
    for (uint8_t* c : cols) std::memset(c, 0, kIq);
    std::memset(int_iq_.fu, 0, sizeof(int_iq_.fu));
    std::memset(mem_iq_.fu, 0, sizeof(mem_iq_.fu));
  }
  lsq_ = Lsq{};
  for (auto& w : lsq_.st_word) w = RT_X;   // STQ uop RegInit dst_rtype = RT_X; LDQ uops reset 0
  ldq_dirty_ = stq_dirty_ = true;
  prf_.clear();
  prf_landed.clear();
  csr_.clear();
  csr_.mstatus = 0x200001800ULL;
  csr_.misa = 0x8000000000001100ULL | (1ULL << 3) | (1ULL << 5);
  csr_.dcsr = 0x10000003ULL;
  csr_.prv = 3;
  csr_.debug = false;
  csr_retire_r_ = csr_exception_r_ = false;
  fp_uop_valid = false;
  br_mispredict_ = false; br_mispredict_tag_ = 0;
  branch_mask_ = branch_mask_start_ = 0;
  for (auto& b : br_pipe) b.clear();
  br_inject_.clear();
  br_kill_this_cycle = false;
  trap_active_ = 0; trap_tail_ = false; trap_take_pending_ = false; trap_pend_mini_ = false;
  trap_pend_pc_ = trap_pend_cause_ = 0;
  dis_valid_start_ = false; xcpt_kill_start = false; dis_fire_ = false;
  csr_wr_pend_ = CsrWrite{};
  csr_flush_target_ = 0;
  trap_rows_total_ = trap_clr_row_ = 0; trap_clr_valid_ = false;
  mem_rrd_snap_prs1_ = mem_rrd_snap_prs2_ = mem_rrd_snap_rt1_ = mem_rrd_snap_rt2_ = 0;
  conv_rrd_ldq_ = conv_exe_ldq_ = 0; conv_rrd_mask_ = 0;
  adp_valid_ = false; adp_mask_ = 0;
  wakeup_mask_s_ = 0;
  ren_r_valid_ = false; disp_.clear(); disp_valid_ = false;
  dmem_resp_valid = false; dmem_resp_data = 0; dmem_resp_uop_valid = false; dmem_resp_uop = MemUop{};
  dmem_resp_nack = false; dmem_nack_uses_ldq = false; dmem_nack_ldq_idx = 0;
  dmem_nack_uses_stq = false; dmem_nack_stq_idx = 0;
  dmem_req_ready = true; dmem_ordered = true; dmem_release_valid = false; dmem_release_address = 0;
  hella_incoming_candidate = hella_wakeup_candidate = false;
  dtlb_passthrough = true; dtlb_req_ready = true; dtlb_miss_ready_registered = true;
  dtlb_resp_miss = dtlb_resp_uncacheable = false;
  dtlb_resp_pf_ld = dtlb_resp_pf_st = dtlb_resp_ae_ld = dtlb_resp_ae_st = false;
  dtlb_resp_paddr = 0; mem_tlb_uncacheable_for_lcam = false; wfi_wakeup = false;
  std::memset(ext_irf_read_datas, 0, sizeof(ext_irf_read_datas));
  std::memset(wb_, 0, sizeof(wb_)); wb_mask_ = 0;
  dec_view_.clear(); dec_view_valid_ = false;
  iq_any_poison_ = false;
  mem_iss_ = Stage{}; mem_rrd_ = Stage{}; mem_agu_ = Stage{}; mem_agu_s_ = Stage{};
  mem_iss_rs1_ = mem_iss_rs2_ = mem_rrd_rs1_ = mem_rrd_rs2_ = mem_agu_rs1_ = mem_agu_rs2_ = 0;
  mem_agu_rs1_s_ = mem_agu_rs2_s_ = 0;
  dmem_pending = DmemPending{};
  dmem_pipelined_ = true;
  lcam_ldq_s1_ = -1; lcam_incoming_s1_ = lcam_fired_s1_ = lcam_store_search_s1_ = false;
  lcam_store_stq_s1_ = 0; lcam_store_addr_s1_ = 0; lcam_store_size_s1_ = 0;
  release_search_s1_ = false; release_address_s1_ = 0;
  nacking_loads_prev_ = 0;
  fwd_wb_ = FwdWb{};
  block_wakeup_next_ = false;
  ldq_block_p1_ = ldq_block_p2_ = ldq_block_now_r_ = 0;
  ldq_wakeup_idx_ = kLdq - 1; ldq_retry_idx_ = kLdq - 1; stq_retry_idx_ = kStq - 1;
  ldq_elig_s_ = ldq_retry_elig_s_ = stq_retry_elig_s_ = 0;
  ldq_head_s_ = stq_commit_head_s_ = 0;
  ld_exsucc_s_ = 0; mem_xcpt_brmask_s_ = 0;
  sched_s_ = boom_lsu::Schedule{};
  commit_load_at_rob_head_ = false;
  store_blocked_counter_ = 0;
  spec_s1_ = SpecWake{}; spec_s2_ = SpecWake{};
  store_clr_bsy_s1_ = ClrBsy{}; store_clr_bsy_s2_ = ClrBsy{}; stdf_clr_bsy_r_ = ClrBsy{};
  lsu_r_xcpt_ = XcptRec{}; mem_xcpt_ = XcptRec{};
  lsu_r_xcpt_killed_now_ = false;
  dmem_pending_kill_ = false;
  out_dmem_release_ready = 0;
  dis_ready_ = true;
  *int_iq_.ready = 1; *mem_iq_.ready = 1;
  int_iq_start_valid_ = mem_iq_start_valid_ = 0;
  int_port_consumed_ = mem_port_consumed_ = false;
  ghost_fast_wake_pdst_ = 0;
  ghost_int_v_ = ghost_mem_v_ = false;
  ghost_int_slot_ = ghost_mem_slot_ = -1;
  ghost_int_partial_slot_ = ghost_mem_partial_slot_ = -1;
  ghost_int_poison_ = ghost_mem_poison_ = false;
  fp_offered = false; fp_offered_inst = 0;
  std::memset(rd_addr_reg, 0, sizeof(rd_addr_reg));
  cycle_count_ = 0; minstret_count_ = 0; minstret_csr_reg_ = 0;
  div_block_from_ = 1; div_block_until_ = 0;
  cur_int_fu_ = 0;
  redirect_pending = false; redirect_pending_pc = 0; redirect_pending_ftq = 0;
  sfence_pending = SfencePending{};
  debug_jalr_flush_icache_pending_ = false;
  auto& R = I.r.coreRename;
  R.freelist_REG = 0;
  R.freelist_r = 1;
  ren2_alloc_now_ = false; ren2_alloc_ldst_ = ren2_alloc_pdst_ = 0;
  rob_wait_empty_ = false; trap_from_wait_empty_ = false;
  {
    MicroOp z; z.clear();
    boom_decode(z);
    z.exc_cause = 2;
    z.flush_on_commit = 0;
    z.uses_ldq = 1;
    z.lrs1_rtype = RT_FIX;
    ren_r_ = z;
    fp_ren_r_ = FpRenFields{};
    fp_disp_ = FpRenFields{};
    fp_reset();
  }
  out_ifu_commit_valid = 0; out_ifu_commit_bits = 0;
  out_ifu_sfence_valid = out_ifu_sfence_rs1 = out_ifu_sfence_rs2 = 0;
  out_ifu_sfence_addr = 0; out_ifu_flush_icache = 0;
  sys_pc2epc_deq_valid_r_ = false; sys_pc2epc_deq_idx_r_ = 0;
  out_ifu_get_pc_0_ftq_idx = out_ifu_get_pc_1_ftq_idx = 0;
  jmp_pc_req_valid_r_ = false; jmp_pc_req_bits_r_ = 0;
  dec_uop_ftq_wire_ = 0;
  rob_flush_now_ = false; rob_flush_ftq_now_ = 0;
  rob_exception_now_ = rob_commit_arch_now_ = false;
  flush_typ_now_ = 0;
  iresp_now_v_ = false; iresp_now_rob_ = 0; iresp_rob_r_ = 0;
  ll_now_v_ = false; ll_now_rob_ = 0;
  fp_ll_now_v_ = false; fp_ll_now_rob_ = 0;
  int_rrd_ = Stage{}; int_exe_ = Stage{};
  brinfo_uop_r_.clear(); brinfo_payload_r_ = BrPayload{};
  brinfo_valid_r_ = brinfo_mispredict_r_ = false;
  brupdate_b2_payload_r = BrPayload{}; brupdate_b2_mispredict_r_ = false;
  brupdate_b2_uop_r.clear();
  int_sel_now_ = int_iss_fired_ = int_squash_grant_ = false; int_sel_uop_now_.clear();
  ghost_int_uop_.clear(); ghost_mem_uop_.clear();
  mem_sel_now_ = mem_iss_fired_ = mem_iss_load_now_ = false; mem_sel_uop_now_.clear();
  pause_mem_r_ = false; sat_loads_ctr_ = 0; spec_bcast_now_ = ld_miss_now_ = false;
  spec_ld_r_ = false; spec_ld_ldq_r_ = 0;
  int_rrd_killed_ = false;
  oracle_exe_.clear(); oracle_b1_.clear(); oracle_b2_.clear(); oracle_b3_.clear(); oracle_b4_.clear();
  std::memset(alu_unit_valid_, 0, sizeof(alu_unit_valid_));
  std::memset(imul_unit_valid_, 0, sizeof(imul_unit_valid_));
  std::memset(ifpu_unit_valid_, 0, sizeof(ifpu_unit_valid_));
  int_iss_result_ = int_rrd_res_ = int_exe_res_ = 0;
  byp1_ = Byp{}; byp2_ = Byp{};
  std::memset(exe_rs1_data_, 0, sizeof(exe_rs1_data_));
  std::memset(exe_rs2_data_, 0, sizeof(exe_rs2_data_));
  brinfos_valid_r_ = brinfos_mispredict_r_ = brinfos_m_now_ = false;
  brexe_mispred_pre_ = brinfos_mispred_r_ = false;
  idiv_issue_fu_mask_r_ = 0x03ffu;
  div_resp_fired_ = false;
  imul_inpipe_v_ = imul_data_v_ = false;
  imul_in1_ = imul_in2_ = imul_data_b_ = imul_outpipe_ = 0; imul_fn_ = imul_dw_ = 0;
  mul_req_ = MulReq{}; div_req_ = DivReq{};
  div_r_uop_.clear();
  div_state_ = div_count_ = div_jump_ = 0;
  div_isHi_ = div_req_dw_ = div_neg_out_ = false;
  div_lhs_ = div_rhs_ = div_divisor_lo_ = 0; div_remainder_lo_[0] = div_remainder_lo_[1] = 0;
  div_divisor_hi_ = div_remainder_hi_ = 0;
  ifpu_in1_ = 0; ifpu_rm_ = ifpu_typ_ = ifpu_type_tag_in_ = 0; ifpu_wflags_ = false;
  std::memset(rob_read_bsy_now_, 0, sizeof(rob_read_bsy_now_));
  std::memset(rob_read_uop_packed_now_, 0, sizeof(rob_read_uop_packed_now_));
  wb_fwd_valid_r_ = false; wb_fwd_ldq_r_ = wb_fwd_stq_r_ = 0;
  mem_iss_vmir_ = mem_rrd_vmir_ = mem_agu_vmir_ = false;
  mem_rrd_killed_ = mem_agu_killed_ = false;
  mem_xcpt_rob_r_ = 0; mem_xcpt_brmask_r_ = lsu_xcpt_brmask_r_ = 0; lsu_xcpt_rob_r_ = 0;
  mem_incoming_ldq_r_ = mem_incoming_rob_r_ = mem_incoming_pdst_r_ = 0; mem_incoming_brmask_r_ = 0;
  mem_paddr_r_ = 0;
  fired_wakeup_now_ = fired_load_wakeup_r_ = canfire_load_incoming_ = fwd_match_now_ = false;
  ldq_b1_killed_now_ = 0; b1_mispred_mask_now_ = b1_resolve_mask_now_ = 0;
  flush_redirect_now_ = false; b1_mispred_now_ = false;
  commit_snap_ = CommitSnap{};
  mem_attempt_v = false; mem_attempt_addr = mem_attempt_data = 0;
  dmem_req_fired_now = false; dmem_req_mask_now = 0;
  resp_byp_v_ = false;
  rob_state_ = 0;
  // Reset-period register images that depend on the number of held edges.
  ++oracle_reset_ticks_;
  if (oracle_reset_ticks_ < 3) {
    R.freelist_r = 0;
    I.r.coreFpRename.freelist_r = 0;
  } else {
    R.freelist_r = 1;
    I.r.coreFpRename.freelist_r = 1;
  }
  if (oracle_reset_ticks_ >= 5) {
    oracle_exe_.dst_rtype = RT_X; oracle_b1_.dst_rtype = RT_X; oracle_b2_.dst_rtype = RT_X;
    oracle_b3_.dst_rtype = RT_X; oracle_b4_.dst_rtype = RT_X;
  }
  if (oracle_reset_ticks_ >= 2) fp_rrd_uop_.dst_rtype = RT_X;
  if (oracle_reset_ticks_ >= 3) fp_exe_uop_.dst_rtype = RT_X;
  rob_val_start_ = rob_busy_start_ = rob_unsafe_start_ = rob_exc_start_ = 0;
  rob_head_start_ = rob_tail_start_ = 0;
  rob_empty_start_ = true;
  csr_export();
  export_step();
}

// --------------------------------------------------------------------------
// CSRDecode legality is dynamic: re-evaluate the held decode wires against
// the current CSR state every cycle.
static void apply_dynamic_decode_legality(MicroOp& u, const GuiderCSR& csr) {
    csr_logic::decode_legality(u, csr);
}

// --------------------------------------------------------------------------
void Core::cycle_start() {
  architectural_.begin_cycle();
  cycle_debug_mode_ = csr_.debug;
  Image& I = *img_;
  // Pre-edge captures for this edge's RegEnables / RegNexts.
  int_exe_start_ = int_exe_;
  exe_rs1_start_[0] = exe_rs1_data_[0]; exe_rs1_start_[1] = exe_rs1_data_[1];
  fcsr_rm_start_ = static_cast<uint8_t>((csr_.fcsr >> 5) & 7u);
  rollback_restore_at_edge_ = trap_active_ > 0 && trap_clr_valid_;
  if (rollback_restore_at_edge_) {
    std::memcpy(map_start_, map_, sizeof(map_start_));
    std::memcpy(fp_map_start_, fp_map_, sizeof(fp_map_start_));
  }
  csr_single_step_start_ = ((csr_.dcsr >> 2) & 1u) != 0 && !csr_.debug;
  csr_retire_input_ = csr_retire_r_;
  csr_exception_input_ = csr_exception_r_;
  fp_cycle_start();

  // JALR mispredict decided at EXE against get_pc(0).
  if (br_pipe[1].v && br_pipe[1].is_jalr) {
    const ExtFtqGetPc& g = ext_ftq_get_pc0;
    const uint8_t cfi_idx = static_cast<uint8_t>(((br_pipe[1].pc_lob ^ (g.start_bank ? 8u : 0u)) >> 1) &
                                                 (boomcfg::FETCH_WIDTH - 1u));
    br_pipe[1].mispredict = !g.next_val || (g.next_pc & kPc40) != (br_pipe[1].target & kPc40) ||
                            !g.cfi_valid || g.cfi_idx != cfi_idx;
  }
  if (!csr_.wfi && !csr_.cease) {
    ++cycle_count_;
    if ((csr_.mcountinhibit & 1u) == 0) ++csr_.mcycle;
  }
  for (unsigned i = 0; i < 2; ++i) {
    if (csr_.hpm_inc_r[i] && (csr_.mcountinhibit & (uint8_t(1u) << (i + 3))) == 0)
      csr_.hpmcounter[i] = (csr_.hpmcounter[i] + 1) & ((UINT64_C(1) << 40) - 1);
    csr_.hpm_inc_r[i] = false;
  }
  minstret_csr_reg_ = minstret_count_;
  const bool debug_mode_start = csr_.debug;

  // Core -> frontend maintenance controls.
  out_ifu_sfence_valid = bit(sfence_pending.valid);
  out_ifu_sfence_rs1 = bit(sfence_pending.rs1);
  out_ifu_sfence_rs2 = bit(sfence_pending.rs2);
  out_ifu_sfence_addr = sfence_pending.addr;
  out_ifu_flush_icache = bit(debug_jalr_flush_icache_pending_);
  {
    const uint8_t size = inst(mem_agu_.u).mem_size;
    sfence_pending.valid = mem_agu_.v && mem_agu_.u.mem_cmd == 20;
    sfence_pending.rs1 = (size & 1u) != 0;
    sfence_pending.rs2 = (size & 2u) != 0;
    sfence_pending.addr = mem_agu_rs1_ & ((UINT64_C(1) << 39) - UINT64_C(1));
  }
  {
    const bool offered_jalr = (fp_uop.inst & UINT32_C(0x0000707f)) == UINT32_C(0x00000067);
    debug_jalr_flush_icache_pending_ = fp_offered && offered_jalr && debug_mode_start;
  }
  branch_mask_start_ = branch_mask_;
  any_brinfo_mispredict_pre_ = brinfo_valid_r_ && brinfo_mispredict_r_;
  out_ifu_get_pc_1_ftq_idx = brinfo_uop_r_.ftq_idx;
  dec_uop_ftq_wire_ = fp_uop.ftq_idx;
  rob_flush_now_ = false; rob_flush_ftq_now_ = 0;
  rob_exception_now_ = false;
  rob_commit_arch_now_ = false;
  flush_typ_now_ = 0;
  iresp_now_v_ = false; iresp_now_rob_ = 0;
  ll_now_v_ = false; ll_now_rob_ = 0;
  fp_ll_now_v_ = false; fp_ll_now_rob_ = 0;

  // Pre-edge ROB view.
  rob_val_start_ = rob_val_; rob_busy_start_ = rob_busy_;
  rob_unsafe_start_ = rob_unsafe_; rob_exc_start_ = rob_exc_;
  rob_head_start_ = rob_head_; rob_tail_start_ = rob_tail_;
  rob_empty_start_ = rob_empty_;
  fpiu_rob_start_ = fpiu_rob_r_;
  rob_pnr_start_ = rob_pnr_;
  lsu_xcpt_rob_start_ = lsu_xcpt_rob_r_;
  // Default payloads of the three asynchronous ROB read ports.
  {
    unsigned ll_read_idx = fp_exe_uop_.rob_idx & (kRob - 1);
    for (int q = 0; q < 3; ++q) if (fp_sdq_[q].v) { ll_read_idx = fp_sdq_[q].uop.rob_idx & (kRob - 1); break; }
    for (int q = 0; q < 8; ++q) if (f2i_q_[q].v) { ll_read_idx = f2i_q_[q].uop.rob_idx & (kRob - 1); break; }
    unsigned third_read_idx = oracle_b3_.rob & (kRob - 1);
    for (int q = 0; q < 4; ++q) if (from_int_q_[q].v) { third_read_idx = from_int_q_[q].uop.rob_idx & (kRob - 1); break; }
    const unsigned iresp_read_idx = div_r_uop_.rob & (kRob - 1);
    rob_read_port(0, ll_read_idx, (rob_busy_start_ >> ll_read_idx) & 1u);
    rob_read_port(1, iresp_read_idx, (rob_busy_start_ >> iresp_read_idx) & 1u);
    rob_read_port(2, third_read_idx, (rob_busy_start_ >> third_read_idx) & 1u);
  }
  // The commit-uop mux (state s_rollback reads the tail row), captured now:
  // this row can be re-dispatched on this same edge.
  {
    const int row = I.r.coreRob.rob_state == 2 ? rob_tail_ : rob_head_;
    const MicroOp& cu = inst_[row];
    commit_snap_.pc_lob = cu.pc_lob; commit_snap_.ftq_idx = cu.ftq_idx;
    commit_snap_.is_rvc = cu.is_rvc != 0; commit_snap_.edge_inst = cu.edge_inst != 0;
  }
  ren2_alloc_now_ = false; ren2_alloc_ldst_ = ren2_alloc_pdst_ = 0;
  fp_ren2_alloc_now_ = false; fp_ren2_alloc_ldst_ = fp_ren2_alloc_pdst_ = 0;
  rob_enq_fired_ = rob_deq_fired_ = false;
  rob_enq_unique_ = false;
  div_resp_fired_ = false;
  mem_iss_load_now_ = false;
  fired_wakeup_now_ = false;
  spec_bcast_now_ = false;
  ld_miss_now_ = false;
  fwd_match_now_ = false;
  b1_mispred_now_ = false;
  int_rrd_killed_ = false;
  mem_rrd_killed_ = mem_agu_killed_ = false;
  ldq_b1_killed_now_ = 0;
  lsu_r_xcpt_killed_now_ = false;
  int_squash_grant_ = false;
  b1_mispred_mask_now_ = b1_resolve_mask_now_ = 0;
  dmem_req_fired_now = false; dmem_req_mask_now = 0;
  ren1_ran_ = false;
  int_iss_result_ = 0;
  out_ext_irf_write_valids[0] = out_ext_irf_write_valids[1] = 0;
  dis_valid_start_ = disp_valid_;
  xcpt_kill_start = rob_xcpt_.v;
  fp_snapshot_stdata();
  wakeup_mask_s_ = lsq_.ld_brmask[ldq_wrap(ldq_wakeup_idx_)];
  std::memcpy(ld_brmask_s_, lsq_.ld_brmask, sizeof(ld_brmask_s_));
  for (int i = 0; i < kStq; ++i) st_brmask_s_[i] = StqWord::br_mask(lsq_.st_word[i]);
  mem_rrd_snap_prs1_ = mem_rrd_.u.prs1; mem_rrd_snap_prs2_ = mem_rrd_.u.prs2;
  mem_rrd_snap_rt1_ = mem_rrd_.u.lrs1_rtype; mem_rrd_snap_rt2_ = mem_rrd_.u.lrs2_rtype;
  if (xcpt_kill_start) {
    disp_valid_ = false; ren_r_valid_ = false; fp_uop_valid = false;
    fp_disp_valid_ = false; fp_ren_r_valid_ = false;
  }

  // Registered flush redirect.
  out_ifu_redirect_val = bit(redirect_pending);
  out_ifu_redirect_pc = redirect_pending ? redirect_pending_pc
                                        : brupdate_b2_uop_r.pc + (brupdate_b2_uop_r.is_rvc() ? 2 : 4);
  out_ifu_redirect_ftq_idx = redirect_pending ? redirect_pending_ftq : brupdate_b2_uop_r.ftq_idx;
  flush_redirect_now_ = redirect_pending;
  if (redirect_pending) {
    rob_wait_empty_ = false;
    disp_valid_ = false; ren_r_valid_ = false; fp_uop_valid = false;
    fp_disp_valid_ = false; fp_ren_r_valid_ = false;
    lsq_.ldq_head = lsq_.ldq_tail = 0;
    lsq_.ld_valid = lsq_.ld_addr_valid = lsq_.ld_executed = 0;
    lsq_.stq_tail = lsq_.stq_commit_head;
    const uint8_t speculative = static_cast<uint8_t>(lsq_.st_valid & ~lsq_.st_committed & ~lsq_.st_succeeded);
    const uint8_t keep = static_cast<uint8_t>(~speculative);
    lsq_.st_valid &= keep; lsq_.st_addr_valid &= keep; lsq_.st_data_valid &= keep;
    lsq_.st_committed &= keep; lsq_.st_succeeded &= keep;
    lsq_.live_store_mask = lsq_.st_valid;
    ldq_dirty_ = stq_dirty_ = true;
    mem_iss_.v = mem_rrd_.v = mem_agu_.v = false;
    lcam_ldq_s1_ = -1;
    lcam_incoming_s1_ = lcam_fired_s1_ = false;
    release_search_s1_ = false;
    fwd_wb_.v = false;
    int_rrd_.v = false; int_rrd_.u.clear();
    int_exe_.v = false; int_exe_.u.clear();
    iq_flush(int_iq_);
    iq_flush(mem_iq_);
    byp1_.v = byp2_.v = false;
    std::memset(alu_unit_valid_, 0, sizeof(alu_unit_valid_));
    std::memset(imul_unit_valid_, 0, sizeof(imul_unit_valid_));
    std::memset(ifpu_unit_valid_, 0, sizeof(ifpu_unit_valid_));
    mul_req_.v = false;
    if (div_req_.v && div_req_.left == 0) div_r_uop_ = div_req_.uop;
    div_req_.v = false;
    div_state_ = 0;
    mem_iss_vmir_ = mem_rrd_vmir_ = mem_agu_vmir_ = false;
    wb_mask_ = 0;
    div_block_from_ = 1; div_block_until_ = 0;
    spec_s1_.v = spec_s2_.v = false;
    branch_mask_ = 0;
    for (auto& b : br_pipe) b.v = false;
    br_inject_.v = false;
    store_clr_bsy_s1_.v = store_clr_bsy_s2_.v = false;
    if (dmem_pending.valid && dmem_pending.uop.uses_ldq) dmem_pending_kill_ = true;
    fp_flush();
  }
  redirect_pending = false;

  // Issue-slot occupancy at cycle start (before this cycle's b1 kills).
  if constexpr (kArchitecturalModel) {
    int_iq_start_valid_ = int_iq_.live;
    mem_iq_start_valid_ = mem_iq_.live;
  } else {
    uint8_t iv = 0, mv = 0;
    for (int i = 0; i < kIq; ++i) {
      if (int_iq_.state[i] != IS_INVALID) iv |= static_cast<uint8_t>(1u << i);
      if (mem_iq_.state[i] != IS_INVALID) mv |= static_cast<uint8_t>(1u << i);
    }
    int_iq_start_valid_ = iv; mem_iq_start_valid_ = mv;
  }
  mem_port_consumed_ = false;
  ghost_mem_v_ = false; ghost_mem_slot_ = -1; ghost_mem_partial_slot_ = -1;
  int_port_consumed_ = false;
  ghost_fast_wake_pdst_ = 0;
  ghost_int_v_ = false; ghost_int_slot_ = -1; ghost_int_partial_slot_ = -1;
  {
    uint16_t fus = INT_FU;
    if (cycle_count_ >= div_block_from_ && cycle_count_ <= div_block_until_) fus &= static_cast<uint16_t>(~FU_DIV);
    cur_int_fu_ = fus;
  }
  fp_iq_start_valid_ = 0;
  for (int i = 0; i < fp_iq_slots_; ++i)
    if (fp_iq_[i].state != IS_INVALID) fp_iq_start_valid_ |= static_cast<uint8_t>(1u << i);
  fp_port_consumed_ = false;
  ghost_fp_v_ = false; ghost_fp_slot_ = -1;
  fp_rrd_killed_ = false;
  {
    bool ifpu_busy = false;
    for (const auto& e : from_int_q_) if (e.v) { ifpu_busy = true; break; }
    if (!ifpu_busy) cur_int_fu_ |= FU_I2F;
  }
  // LSU pre-edge face.
  mem_agu_s_ = mem_agu_;
  mem_agu_rs1_s_ = mem_agu_rs1_; mem_agu_rs2_s_ = mem_agu_rs2_;
  mem_xcpt_brmask_s_ = mem_xcpt_brmask_r_;
  ldq_head_s_ = static_cast<uint8_t>(lsq_.ldq_head);
  stq_commit_head_s_ = static_cast<uint8_t>(lsq_.stq_commit_head);
  ld_valid_s_ = lsq_.ld_valid; ld_addr_valid_s_ = lsq_.ld_addr_valid;
  ld_virtual_s_ = lsq_.ld_virtual; ld_uncacheable_s_ = lsq_.ld_uncacheable;
  ld_fwd_std_val_s_ = lsq_.ld_fwd_std_val; ld_exc_s_ = lsq_.ld_exc;
  ld_exsucc_s_ = static_cast<uint8_t>(lsq_.ld_executed | lsq_.ld_succeeded);
  ldq_elig_s_ = static_cast<uint8_t>(lsq_.ld_valid & lsq_.ld_addr_valid & ~lsq_.ld_virtual &
                                     ~lsq_.ld_executed & ~lsq_.ld_succeeded);
  ldq_retry_elig_s_ = static_cast<uint8_t>(lsq_.ld_addr_valid & lsq_.ld_virtual);
  st_valid_s_ = lsq_.st_valid; st_addr_valid_s_ = lsq_.st_addr_valid; st_virtual_s_ = lsq_.st_virtual;
  st_data_valid_s_ = lsq_.st_data_valid; st_committed_s_ = lsq_.st_committed; st_succeeded_s_ = lsq_.st_succeeded;
  stq_retry_elig_s_ = static_cast<uint8_t>(lsq_.st_addr_valid & lsq_.st_virtual);
  st_exc_s_ = 0;
  if constexpr (kArchitecturalModel) {
    ldq_retry_elig_s_ &= lsq_.ld_valid;
    stq_retry_elig_s_ &= lsq_.st_valid;
  }
  for (unsigned slots = kArchitecturalModel ? lsq_.st_valid : 255u; slots; slots &= slots - 1u) {
    const unsigned i = __builtin_ctz(slots);
    if (StqWord::exception(lsq_.st_word[i])) st_exc_s_ |= static_cast<uint8_t>(1u << i);
  }
  {
    LsuScheduleInputs in;
    in.dmem_release_valid = dmem_release_valid;
    in.hella_incoming = hella_incoming_candidate;
    in.hella_wakeup = hella_wakeup_candidate;
    in.dtlb_miss_ready_registered = dtlb_miss_ready_registered;
    in.dmem_ordered = dmem_ordered;
    sched_s_ = compute_lsu_schedule(in);
  }
}

// dis_hazards (core.scala:711-741) from the cycle-start registered state.
void Core::dispatch_hazards() {
  const MicroOp& du = disp_;
  bool haz = false;
  if (du.is_unique) {
    if (!rob_empty_) haz = true;
    if (lsq_.st_valid) haz = true;
    if (!dmem_ordered) haz = true;
  }
  if (du.dst_rtype == RT_FIX && !img_->r.coreRename.freelist_REG) haz = true;
  int rob_cnt = rob_wrap(rob_tail_ - rob_head_);
  if (!rob_empty_ && rob_cnt == 0) rob_cnt = kRob;
  if (rob_cnt >= kRob) haz = true;
  if (!(*int_iq_.ready && *mem_iq_.ready)) haz = true;
  if (!fp_iq_ready_) haz = true;
  if (du.uses_ldq && ldq_wrap(lsq_.ldq_tail + 1) == lsq_.ldq_head) haz = true;
  if (du.uses_stq && stq_wrap(lsq_.stq_tail + 1) == lsq_.stq_head) haz = true;
  if (rob_wait_empty_) haz = true;
  if (trap_active_ > 0 || trap_take_pending_) haz = true;
  if (xcpt_kill_start) haz = true;
  if (br_kill_this_cycle) haz = true;
  if (flush_redirect_now_) haz = true;
  dis_ready_ = !(dis_valid_start_ && haz);
  dis_fire_ = disp_valid_ && dis_ready_;
}

// Decode-stage view of the offered packet and the fetchpacket ready.
void Core::decode_and_rename() {
  const bool trap_busy_start = trap_active_ > 0;
  bool dec_xcpt_wire = false;
  dec_view_valid_ = false;
  if (fp_offered) {
    dec_view_ = fp_uop;
    boom_decode_cached(dec_view_);
    apply_dynamic_decode_legality(dec_view_, csr_);
    dec_xcpt_wire = dec_view_.exception != 0;
    dec_view_valid_ = true;
  }
  uint8_t hz = 0;
  if (!dis_ready_) hz |= 1;
  if (br_kill_this_cycle) hz |= 2;
  if (out_ifu_redirect_val) hz |= 4;
  if (xcpt_kill_start) hz |= 4;
  if (trap_busy_start) hz |= 8;
  const uint8_t opc = fp_offered_inst & 0x7F;
  const bool needs_tag = (opc == 0x63) || (opc == 0x67);
  const uint8_t inflight = static_cast<uint8_t>(__builtin_popcount(branch_mask_start_));
  if (needs_tag && inflight >= kBr) hz |= 16;
  if (!fp_offered) hz |= 32;
  if (dec_xcpt_wire && jmp_pc_req_valid_r_) hz |= 64;
  out_ifu_fetchpacket_ready = hz == 0 ? 1 : 0;
  fp_uop_valid = fp_offered && out_ifu_fetchpacket_ready != 0;
  rename_step();
}

// Dispatch: stamp indices, allocate LDQ/STQ, re-read the busy bits.
void Core::dispatch_step() {
  if (!dis_fire_) return;
  MicroOp& du = disp_;
  du.rob_idx = static_cast<uint8_t>(rob_tail_);
  du.ldq_idx = static_cast<uint8_t>(lsq_.ldq_tail);
  du.stq_idx = static_cast<uint8_t>(lsq_.stq_tail);
  lsq_dispatch(du);
  const FpRenFields& fdu = fp_disp_;
  if (du.lrs1_rtype == RT_FLT) {
    du.prs1 = fdu.prs1;
    du.prs1_busy = ((fp_busy_ >> du.prs1) & 1u) ? 1 : 0;
  } else {
    if (du.lrs1_rtype != RT_FIX) du.prs1 = du.lrs1;
    du.prs1_busy = (du.lrs1_rtype == RT_FIX) && ((busy_ >> du.prs1) & 1u);
  }
  if (du.lrs2_rtype == RT_FLT) {
    du.prs2 = fdu.prs2;
    du.prs2_busy = ((fp_busy_ >> du.prs2) & 1u) ? 1 : 0;
  } else {
    du.prs2_busy = (du.lrs2_rtype == RT_FIX) && ((busy_ >> du.prs2) & 1u);
  }
  du.prs3 = fdu.prs3;
  du.prs3_busy = du.frs3_en ? (((fp_busy_ >> du.prs3) & 1u) ? 1 : 0) : 0;
}

// --------------------------------------------------------------------------
void Core::step() {
  cycle_start();
  br_kill_this_cycle = false;
  br_mispredict_ = false;
  branch_step();

  // RegNext(head is a load that cannot commit) for the uncacheable release.
  bool commit_load_at_rob_head_next;
  {
    const int head = rob_head_start_;
    const bool block_commit = trap_active_ > 0 || trap_take_pending_ || (rob_state_ != 1 && rob_state_ != 3);
    const bool valid = (rob_val_start_ >> head) & 1u;
    const bool can_throw = valid && ((rob_exc_start_ >> head) & 1u);
    const bool can_commit = valid && !((rob_busy_start_ >> head) & 1u) && !csr_.wfi && !csr_.cease;
    const bool will_commit = can_commit && !can_throw && !block_commit;
    commit_load_at_rob_head_next = inst_[head].uses_ldq && !will_commit;
  }

  uint8_t slow_wake[16];
  int n_slow_wake = 0;
  writeback_step(slow_wake, n_slow_wake);
  dispatch_hazards();
  const bool sys_pc2epc_next_valid = dis_fire_ && disp_.is_sys_pc2epc;
  const uint8_t sys_pc2epc_next_idx = disp_.ftq_idx;
  decode_and_rename();
  dispatch_step();
  if (csr_wr_pend_.v && --csr_wr_pend_.left == 0) {
    exec_csr(inst_[csr_wr_pend_.rob], csr_wr_pend_.csr_cmd, csr_wr_pend_.r1);
    csr_wr_pend_.v = false;
  }
  issue_step();
  for (int i = 0; i < n_slow_wake; ++i) {
    busy_ &= ~boomcfg::pm_bit(slow_wake[i]);
    iq_wake(int_iq_, slow_wake[i]);
    iq_wake(mem_iq_, slow_wake[i]);
  }
  trap_tail_ = trap_active_ > 0;
  rob_step();
  if (sys_pc2epc_deq_valid_r_) {
    out_ifu_commit_valid = 1;
    out_ifu_commit_bits = sys_pc2epc_deq_idx_r_;
  }
  sys_pc2epc_deq_valid_r_ = sys_pc2epc_next_valid;
  sys_pc2epc_deq_idx_r_ = sys_pc2epc_next_idx;
  if (wfi_wakeup && csr_.wfi) { csr_.wfi = false; img_->r.coreCsr.reg_wfi = 0; }
  lsu_step();
  commit_load_at_rob_head_ = commit_load_at_rob_head_next;
  fp_pipe_advance();
  // The response read above belongs to the PRE wrapper. Advance its four
  // registers only after consuming that response, then publish the POST image.
  fp_fpu_wrapper_advance();
  end_of_step();
}

// Register advance at the end of the cycle (RegNexts, ren2 reload, the
// execute payload chain, the multiplier/divider mirrors, ROB bookkeeping).
void Core::end_of_step() {
  ++sched_epoch_;
  Image& I = *img_;
  br_pipe[3] = br_pipe[2];
  br_pipe[2] = br_pipe[1];
  br_pipe[1] = br_pipe[0];
  br_pipe[0] = br_inject_;

  // ren2 register reload / rename r_uop refresh.
  if (kInternalSignalContract && dis_ready_ && !(flush_redirect_now_ || br_kill_this_cycle || xcpt_kill_start)) {
    if (!ren1_ran_) {
      if (dec_view_valid_) {
        ren_r_ = dec_view_;
      } else {
        ren_r_ = fp_uop;
        boom_decode_cached(ren_r_);
        apply_dynamic_decode_legality(ren_r_, csr_);
      }
      MicroOp& w = ren_r_;
      if (w.inst == 0) { w.flush_on_commit = 0; w.uses_ldq = 1; w.lrs1_rtype = RT_FIX; }
      if (wfi_wakeup) { w.exception = 1; w.exc_cause = (UINT64_C(1) << 63) | 14; }
      w.pdst = 0;
      const uint8_t* map_read = rollback_restore_at_edge_ ? map_start_ : map_;
      w.prs1 = map_read[w.lrs1 & 31];
      w.prs2 = map_read[w.lrs2 & 31];
      w.stale_pdst = map_read[w.ldst & 31];
      w.prs1_busy = (w.lrs1_rtype == RT_FIX) && ((busy_ >> w.prs1) & 1u);
      w.prs2_busy = (w.lrs2_rtype == RT_FIX) && ((busy_ >> w.prs2) & 1u);
      w.prs3 = map_read[w.lrs3 & 31];
      w.prs3_busy = 0;
      w.br_mask = branch_mask_;
      {
        const br_mask_t free = static_cast<br_mask_t>(~branch_mask_start_);
        w.br_tag = free ? static_cast<uint8_t>(__builtin_ctz(free)) : 0;
      }
      const uint8_t* fp_read = rollback_restore_at_edge_ ? fp_map_start_ : fp_map_;
      fp_ren_r_.prs1 = fp_read[w.lrs1 & 31];
      fp_ren_r_.prs2 = fp_read[w.lrs2 & 31];
      fp_ren_r_.prs3 = fp_read[w.lrs3 & 31];
      fp_ren_r_.stale_pdst = fp_read[w.ldst & 31];
      fp_ren_r_.pdst = 0;
      fp_ren_r_.prs1_busy = fp_ren_r_.prs2_busy = fp_ren_r_.prs3_busy = 0;
    }
  }
  if (dis_ready_) {
    if (kInternalSignalContract || ren_r_valid_) disp_ = ren_r_;
    disp_valid_ = ren_r_valid_;
    if (kInternalSignalContract || fp_ren_r_valid_) fp_disp_ = fp_ren_r_;
    fp_disp_valid_ = fp_ren_r_valid_;
  }
  if (fp_uop_valid) out_ifu_debug_fetch_pc_0 = fp_uop.debug_pc;

  // brinfos_0: the ALU's combinational mispredict recompute, registered.
  bool brinfo_mispredict_next;
  BrPayload payload_next;
  {
    const StageUop& bu = int_exe_start_.u;
    const MicroOp& bi = inst(bu);
    const uint64_t r1 = exe_rs1_data_[1];
    const uint64_t r2 = exe_rs2_data_[1];
    const bool br_eq = r1 == r2;
    const bool br_lt = static_cast<int64_t>(r1) < static_cast<int64_t>(r2);
    const bool br_ltu = r1 < r2;
    int pc_sel = 0;
    switch (bi.ctrl.br_type) {
      case 1: pc_sel = !br_eq; break;
      case 2: pc_sel = br_eq; break;
      case 3: pc_sel = !br_lt; break;
      case 4: pc_sel = !br_ltu; break;
      case 5: pc_sel = br_lt; break;
      case 6: pc_sel = br_ltu; break;
      case 7: pc_sel = 1; break;
      case 8: pc_sel = 2; break;
      default: pc_sel = 0; break;
    }
    const bool is_br_g = int_exe_.v && bu.is_br() && !bu.is_sfb();
    const bool is_jalr_g = int_exe_.v && bu.is_jalr();
    const ExtFtqGetPc& g = ext_ftq_get_pc0;
    const uint64_t jalr_target = (r1 + decode_imm(bi)) & ~UINT64_C(1);
    const uint8_t cfi_idx = static_cast<uint8_t>(((bu.pc_lob ^ (g.start_bank ? 8u : 0u)) >> 1) &
                                                 (boomcfg::FETCH_WIDTH - 1));
    const bool jalr_mispredict = !g.next_val || (g.next_pc & kPc40) != (jalr_target & kPc40) ||
                                 !g.cfi_valid || g.cfi_idx != cfi_idx;
    brinfo_mispredict_next = (pc_sel == 2) ? jalr_mispredict
                                           : ((is_br_g || is_jalr_g) && (pc_sel == 1 ? !bu.taken() : bu.taken()));
    brexe_mispred_pre_ = brinfo_mispredict_next;
    payload_next.pc_sel = static_cast<uint8_t>(pc_sel);
    payload_next.cfi_type = is_jalr_g ? uint8_t{3} : is_br_g ? uint8_t{1} : uint8_t{0};
    payload_next.taken = int_exe_.v && (bu.is_br() || bu.is_jalr() || bu.is_jal()) && pc_sel != PC_PLUS4;
    payload_next.target_offset = static_cast<int32_t>(sext(decode_imm(bi) & ((UINT64_C(1) << 21) - 1), 21));
    payload_next.jalr_target = jalr_target & kPc40;
  }

  // iregister_read exe_reg_rs*_data mirrors (bypass-muxed read data).
  {
    auto alu_req = [](const Stage& s) {
      return s.v && (s.u.fu_code == FU_ALU || s.u.fu_code == FU_JMP ||
                     (s.u.fu_code == FU_CSR && s.u.uopc != 0x6c));
    };
    auto byp = [&](uint8_t prs, uint8_t rtype, uint64_t raw) -> uint64_t {
      if (prs == 0 || rtype != RT_FIX) return raw;
      if (alu_req(int_exe_start_) && int_exe_start_.u.dst_rtype == RT_FIX && int_exe_start_.u.pdst == prs)
        return int_exe_res_;
      if (byp1_.v && byp1_.pdst == prs) return byp1_.data;
      if (byp2_.v && byp2_.pdst == prs) return byp2_.data;
      return raw;
    };
    uint64_t raw[boomcfg::IRF_READ_PORTS];
    for (int k = 0; k < boomcfg::IRF_READ_PORTS; ++k) {
      const uint64_t a = out_ext_irf_read_addrs[k];
      if (a == 0) { raw[k] = 0; continue; }
      uint64_t v = 0; bool hit = false;
      for (int wp = 0; wp < boomcfg::IRF_WRITE_PORTS; ++wp)
        if (out_ext_irf_write_valids[wp] && out_ext_irf_write_addrs[wp] == a) { v |= out_ext_irf_write_datas[wp]; hit = true; }
      raw[k] = hit ? v : ext_irf_read_datas[k];
    }
    exe_rs1_data_[0] = byp(mem_rrd_snap_prs1_, mem_rrd_snap_rt1_, raw[0]);
    exe_rs2_data_[0] = byp(mem_rrd_snap_prs2_, mem_rrd_snap_rt2_, raw[1]);
    mem_agu_rs1_ = exe_rs1_data_[0];
    mem_agu_rs2_ = exe_rs2_data_[0];
    exe_rs1_data_[1] = byp(int_rrd_.u.prs1, int_rrd_.u.lrs1_rtype, raw[2]);
    exe_rs2_data_[1] = byp(int_rrd_.u.prs2, int_rrd_.u.lrs2_rtype, raw[3]);
    const bool pipe_valid = alu_req(int_exe_start_) && int_exe_start_.u.dst_rtype == RT_FIX;
    byp2_ = byp1_;
    byp1_ = Byp{pipe_valid, int_exe_start_.u.pdst, int_exe_res_};
  }

  out_ifu_get_pc_0_ftq_idx = rob_flush_now_ ? rob_flush_ftq_now_
                           : (jmp_pc_req_valid_r_ ? jmp_pc_req_bits_r_ : dec_uop_ftq_wire_);
  jmp_pc_req_valid_r_ = (int_iss_fired_ || ghost_int_v_ || int_squash_grant_) && int_sel_now_ &&
                        int_sel_uop_now_.fu_code == FU_JMP;
  jmp_pc_req_bits_r_ = int_sel_now_ ? int_sel_uop_now_.ftq_idx : 0;
  idiv_issue_fu_mask_r_ = static_cast<uint16_t>(
      (~static_cast<uint16_t>(int_sel_now_ && (int_sel_uop_now_.fu_code & FU_DIV) != 0 ? FU_DIV : 0u)) & 0x03ffu);

  // IntToFP input registers (RegEnable on the raw IFPU request).
  {
    const StageUop& req = int_exe_start_.u;
    if (int_exe_start_.v && (req.fu_code & FU_I2F)) {
      const uint8_t encoded_rm = static_cast<uint8_t>(req.imm_packed & 7u);
      ifpu_in1_ = exe_rs1_start_[1];
      ifpu_rm_ = encoded_rm == 7 ? fcsr_rm_start_ : encoded_rm;
      ifpu_typ_ = static_cast<uint8_t>((req.imm_packed >> 8) & 3u);
      ifpu_type_tag_in_ = (req.uopc == uopFCVT_D_X || req.uopc == uopFMV_D_X) ? 1u : 0u;
      ifpu_wflags_ = req.uopc == uopFCVT_S_X || req.uopc == uopFCVT_D_X;
    }
    alu_unit_valid_[2] = alu_unit_valid_[1]; alu_unit_valid_[1] = alu_unit_valid_[0];
    imul_unit_valid_[2] = imul_unit_valid_[1]; imul_unit_valid_[1] = imul_unit_valid_[0];
    ifpu_unit_valid_[1] = ifpu_unit_valid_[0];
    const StageUop& e = int_exe_.u;
    alu_unit_valid_[0] = int_exe_.v && (e.fu_code == FU_ALU || e.fu_code == FU_JMP || (e.fu_code == FU_CSR && e.uopc != 108));
    imul_unit_valid_[0] = int_exe_.v && (e.fu_code & FU_MUL) != 0;
    ifpu_unit_valid_[0] = int_exe_.v && (e.fu_code & FU_I2F) != 0;
  }
  // Raw execution-payload chain.
  {
  oracle_b4_ = oracle_b3_;
  oracle_b3_ = oracle_b2_;
  oracle_b2_ = oracle_b1_;
  if (int_rrd_killed_) {
    const br_mask_t surviving = oracle_exe_.br_mask;
    oracle_b1_.clear();
    oracle_b1_.dst_rtype = RT_X;
    oracle_b1_.br_mask = surviving;
  } else {
    oracle_b1_ = oracle_exe_;
  }
  if (int_sel_now_) oracle_exe_ = int_sel_uop_now_;
  else { oracle_exe_.clear(); oracle_exe_.dst_rtype = RT_X; }
  }
  brupdate_b2_uop_r = brinfo_uop_r_;
  brupdate_b2_payload_r = brinfo_payload_r_;
  brupdate_b2_mispredict_r_ = any_brinfo_mispredict_pre_;
  brinfo_valid_r_ = int_exe_.v && (int_exe_start_.u.is_br() || int_exe_start_.u.is_jalr()) && !rob_flush_now_;
  brinfo_mispredict_r_ = brinfo_mispredict_next;
  brinfos_valid_r_ = brinfo_valid_r_;
  brinfos_mispredict_r_ = brinfos_m_now_;
  brinfos_m_now_ = br_pipe[1].v && br_pipe[1].mispredict;
  brinfo_uop_r_ = int_exe_start_.u;
  brinfo_payload_r_ = payload_next;
  int_exe_ = int_rrd_;
  if (int_rrd_killed_) {
    const br_mask_t surviving = int_rrd_.u.br_mask;
    int_exe_.u.clear();
    int_exe_.u.br_mask = surviving;
  }
  int_rrd_.v = int_iss_fired_;
  if (int_sel_now_) int_rrd_.u = int_sel_uop_now_; else int_rrd_.u.clear();
  int_exe_res_ = int_rrd_res_;
  int_rrd_res_ = int_iss_result_;

  // Pipelined multiplier mirror.
  {
    imul_outpipe_ = imul_data_v_ ? imul_data_b_ : imul_outpipe_;
    // Consume the held PRE operands before a newly arriving request below
    // replaces them. An invalid input stage holds data without multiplying.
    if (imul_inpipe_v_)
      imul_data_b_ = mul_op(imul_fn_, imul_in1_, imul_in2_, imul_dw_ == 0);
    imul_data_v_ = imul_inpipe_v_;
    bool arrive = false;
    if (mul_req_.v) {
      if (mul_req_.left) --mul_req_.left;
      else { arrive = true; mul_req_.v = false; }
    }
    if (arrive) {
      imul_in1_ = mul_req_.in1; imul_in2_ = mul_req_.in2;
      imul_fn_ = mul_req_.fn; imul_dw_ = mul_req_.dw;
      imul_inpipe_v_ = true;
    } else {
      imul_inpipe_v_ = false;
    }
  }
  // The arithmetic registers share the same transition with Large; Small
  // retains its original request delay, wrapper uop and response arbitration.
  {
    bool arrive=false;
    if (div_req_.v) {
      if (div_req_.left) --div_req_.left;
      else { arrive=true;div_req_.v=false; }
    }
    DividerRequest request;
    if (arrive) {
      request={div_req_.in1,div_req_.in2,div_req_.fn,div_req_.dw};
      div_r_uop_=div_req_.uop;
    }
    DividerStateView state{div_state_,div_count_,div_jump_,div_divisor_hi_,div_remainder_hi_,
        div_neg_out_,div_isHi_,div_req_dw_,div_lhs_,div_rhs_,div_divisor_lo_,div_remainder_lo_};
    clock_integer_divider(state,arrive ? &request : nullptr,div_resp_fired_);
  }
  // ROB bookkeeping (pnr / FSM / maybe_full / block_commit).
  {
    const bool enq = rob_enq_fired_, deq = rob_deq_fired_;
    const bool row_enq = enq && dis_ready_;
    const uint8_t pnr = rob_pnr_;
    const bool full = (rob_tail_start_ == rob_head_start_) && maybe_full_;
    const bool pnr_unsafe = ((rob_val_start_ >> pnr) & 1u) &&
                            (((rob_unsafe_start_ >> pnr) & 1u) || ((rob_exc_start_ >> pnr) & 1u));
    const bool do_inc = !pnr_unsafe && (pnr != rob_tail_start_ || (full && !pnr_maybe_at_tail_));
    const bool safe_to_inc = rob_state_ == 1 || rob_state_ == 3;
    const uint8_t pnr_comb = (safe_to_inc && do_inc) ? static_cast<uint8_t>((pnr + 1) & (kRob - 1)) : pnr;
    rob_pnr_ = (rob_empty_start_ && enq) ? static_cast<uint8_t>(rob_head_start_) : pnr_comb;
    pnr_maybe_at_tail_ = !deq && (do_inc || pnr_maybe_at_tail_);
    maybe_full_ = (!deq && (row_enq || maybe_full_)) || b1_mispred_now_;
    const uint8_t prev_st = rob_state_;
    uint8_t st = prev_st;
    if (st == 0) st = 1;
    if (trap_active_ > 0) st = 2;
    else if (st == 2) st = 1;
    if (rob_enq_fired_ && rob_enq_unique_) st = 3;
    else if (st == 3 && flush_redirect_now_) st = 1;
    rob_state_ = st;
    I.r.coreRob.rob_state = (st == 2 && prev_st == 1) ? uint8_t(1) : st;
    block_commit_r2_ = block_commit_r_;
    block_commit_r_ = trap_take_pending_;
  }
  pause_mem_r_ = mem_iss_load_now_;
  sat_loads_ctr_ = mem_iss_load_now_ ? static_cast<uint8_t>((sat_loads_ctr_ + 1) & 31) : 0;
  spec_ld_r_ = spec_bcast_now_;
  fired_load_wakeup_r_ = boom_lsu::registered_fire(fired_wakeup_now_, wakeup_mask_s_, b1_mispred_mask_now_);
  brinfos_mispred_r_ = brexe_mispred_pre_;
  csr_.single_stepped = csr_single_step_start_ && (csr_.single_stepped || csr_retire_input_ || csr_exception_input_);
  csr_retire_r_ = rob_commit_arch_now_;
  csr_exception_r_ = rob_exception_now_;
  export_step();
}

// --------------------------------------------------------------------------
// The contract image at the end of the step: packed bank words of the
// structures that changed, the register scalars, and the combinational
// read ports computed from the cycle-start state.
// --------------------------------------------------------------------------
void Core::export_step() {
  // Functional freelists, issue state and STQ address/data columns are updated
  // at their actual mutation sites. Everything below is an oracle projection.
  Image& I = *img_;
  if (map_dirty_) pack_map();
  if (fp_map_dirty_) pack_fp_map();
  lsq_pack();
  export_ren_r();
  fp_export();
  csr_export_counters();
  I.r.coreCsr.reg_singleStepped = bit(csr_.single_stepped);
  I.r.coreCsr.reg_wfi = bit(csr_.wfi);
  // ROB
  {
    auto& R = I.r.coreRob;
    if (rob_brmask_dirty_) {
      for (int bank = 0; bank < 4; ++bank) {
        uint64_t packed = 0;
        for (int item = 0; item < 8; ++item) packed = (packed << 8) | rob_brmask_[bank * 8 + item];
        R.rob_uopbank_0[bank] = packed;
      }
      rob_brmask_dirty_ = false;
    }
    R.REG = bit(block_commit_r_);
    R.REG_2 = bit(block_commit_r2_);
    R.maybe_full = bit(maybe_full_);
    R.r_xcpt_val = bit(rob_xcpt_.v);
    R.rob_head = static_cast<uint8_t>(rob_head_);
    R.rob_pnr = rob_pnr_;
    R.rob_tail = static_cast<uint8_t>(rob_tail_);
    // pending enqueue of the packed row (this cycle's read ports saw the old array)
    if (enq_packed_idx_ >= 0) { uop_packed_[enq_packed_idx_] = enq_packed_val_; enq_packed_idx_ = -1; }
    // Combinational read ports of the ROB arrays.  The record is copied as
    // the next position at the start of the next step, so a pure register
    // read is computed here from the committed (post-edge) state; the ports
    // that depend on this cycle's arbitration (bsy r3-r5, uop r2-r4) are
    // patched into this position as predicted lanes.
    auto& C = I.c.coreRob;
    C.state_rob_uop_r[0] = uop_packed_[R.rob_state == 2 ? rob_tail_ : rob_head_];
    C.state_rob_uop_r[1] = uop_packed_[rob_head_];
    C.state_rob_uop_r[2] = rob_read_uop_packed_now_[0];
    C.state_rob_uop_r[3] = rob_read_uop_packed_now_[1];
    C.state_rob_uop_r[4] = rob_read_uop_packed_now_[2];
    C.state_rob_uop_r[5] = uop_packed_[fpiu_rob_r_ & (kRob - 1)];
    C.rob_fflags_MPORT_4 = rob_fflags_[rob_head_] & 0x1f;
    // r0/r1: the assert reads behind the two LSU clr_bsy ports (memory port,
    // FP store-data port), indexed by their registered rob_idx whether or not
    // the port is valid; r6: the fpiu writeback port (rob.scala:451, 603).
    C.state_rob_bsy_r[0] = (rob_busy_ >> (store_clr_bsy_s2_.rob & (kRob - 1))) & 1u;
    C.state_rob_bsy_r[1] = (rob_busy_ >> (stdf_clr_bsy_r_.rob & (kRob - 1))) & 1u;
    C.state_rob_bsy_r[6] = (rob_busy_ >> (fpiu_rob_r_ & (kRob - 1))) & 1u;
    C.state_rob_bsy_r[2] = (rob_busy_ >> rob_head_) & 1u;
    C.state_rob_bsy_r[3] = bit(rob_read_bsy_now_[0]);
    C.state_rob_bsy_r[4] = bit(rob_read_bsy_now_[1]);
    C.state_rob_bsy_r[5] = bit(rob_read_bsy_now_[2]);
    C.state_rob_exception_r[0] = (rob_exc_ >> rob_head_) & 1u;
    C.state_rob_exception_r[33] = (rob_exc_ >> rob_pnr_) & 1u;
    C.state_rob_unsafe_r[0] = (rob_unsafe_ >> (lsu_xcpt_rob_r_ & (kRob - 1))) & 1u;
    C.state_rob_unsafe_r[33] = (rob_unsafe_ >> rob_pnr_) & 1u;
    const std::uint32_t changed_exc = rob_flags_export_valid_ ? exported_rob_exc_ ^ rob_exc_ : UINT32_MAX;
    const std::uint32_t changed_unsafe = rob_flags_export_valid_ ? exported_rob_unsafe_ ^ rob_unsafe_ : UINT32_MAX;
    for (std::uint32_t changed = changed_exc; changed; changed &= changed - 1) {
      const unsigned i = static_cast<unsigned>(__builtin_ctz(changed));
      C.state_rob_exception_r[1 + i] = (rob_exc_ >> i) & 1u;
    }
    for (std::uint32_t changed = changed_unsafe; changed; changed &= changed - 1) {
      const unsigned i = static_cast<unsigned>(__builtin_ctz(changed));
      C.state_rob_unsafe_r[1 + i] = (rob_unsafe_ >> i) & 1u;
    }
    exported_rob_exc_ = rob_exc_;
    exported_rob_unsafe_ = rob_unsafe_;
    rob_flags_export_valid_ = true;
    C.state_rob_predicated_r0 = 0;
  }
  // CSR exe unit
  {
    auto& E = I.r.coreCsrExe;
    E.alu_REG_1_2_is_amo = bit(oracle_b4_.is_amo());
    E.alu_REG_1_2_rob_idx = oracle_b4_.rob & 0x1f;
    E.alu_REG_1_2_uses_stq = bit(oracle_b4_.uses_stq());
    bool alu_r_valid_next = false;
    for (unsigned m = wb_mask_; m != 0; m &= m - 1) {
      const Wb& w = wb_[__builtin_ctz(m)];
      if (w.left == 1 && !w.is_mul && !w.is_div) { alu_r_valid_next = true; break; }
    }
    E.alu_REG_2 = bit(alu_r_valid_next);
    E.div_div_count = div_count_ & 0x7f;
    E.div_div_state = div_state_ & 7;
    E.div_r_uop_br_mask = div_r_uop_.br_mask;
    E.div_r_uop_is_amo = bit(div_r_uop_.is_amo());
    E.div_r_uop_rob_idx = div_r_uop_.rob & 0x1f;
    E.div_r_uop_uses_stq = bit(div_r_uop_.uses_stq());
    E.ifpu_REG_1_1_dst_rtype = oracle_b3_.dst_rtype & 3;
    E.ifpu_REG_1_1_pdst = oracle_b3_.pdst & 0x3f;
    E.ifpu_REG_1_1_rob_idx = oracle_b3_.rob & 0x1f;
    E.imul_REG_1_2_is_amo = bit(oracle_b4_.is_amo());
    E.imul_REG_1_2_rob_idx = oracle_b4_.rob & 0x1f;
    E.imul_REG_1_2_uses_stq = bit(oracle_b4_.uses_stq());
  }
  // integer register read
  {
    auto& G = I.r.coreIregRead;
    G.exe_reg_rs1_data[0] = exe_rs1_data_[0];
    G.exe_reg_rs1_data[1] = exe_rs1_data_[1];
    G.exe_reg_rs2_data_1 = exe_rs2_data_[1];
    G.exe_reg_uops_0_imm_packed = mem_agu_.u.imm_packed & 0xfffffu;
    G.exe_reg_uops_fu_code[0] = mem_agu_.u.fu_code & 0x3ffu;
    G.exe_reg_uops_fu_code[1] = int_exe_.u.fu_code & 0x3ffu;
    G.REG_1_br_mask = mem_rrd_.u.br_mask;
    G.REG_3_br_mask = int_rrd_.u.br_mask;
    G.exe_reg_uops_0_ctrl_is_sta = bit(mem_agu_.u.is_sta());
    G.exe_reg_uops_0_ctrl_is_std = bit(mem_agu_.u.is_std());
    G.exe_reg_uops_0_uopc = mem_agu_.u.uopc & 0x7f;
    G.exe_reg_valids[0] = bit(mem_agu_vmir_);
    G.exe_reg_valids[1] = bit(int_exe_.v);
  }
  // core misc
  {
    auto& M = I.r.coreMisc;
    M.REG_21 = idiv_issue_fu_mask_r_ & 0x3ffu;
    const uint8_t fl = bit(rob_flush_now_);
    M.REG_4 = fl; M.REG_12 = fl; M.REG_23 = fl; M.REG_30 = fl; M.REG_31 = fl; M.REG_33 = fl;
    M.int_issue_unit_io_flush_pipeline_REG = fl;
    M.mem_issue_unit_io_flush_pipeline_REG = fl;
    M.REG_5 = flush_typ_now_ & 7;
    M.REG_8 = commit_snap_.pc_lob & 0x3f;
    M.REG_9 = bit(commit_snap_.edge_inst);
    M.REG_10 = bit(commit_snap_.is_rvc);
    M.REG_11 = commit_snap_.ftq_idx & 15;
    M.REG_14_valid = bit(sfence_pending.valid);
    M.REG_20 = bit(mem_iss_load_now_);
    M.brinfos_0_mispredict = bit(brinfos_mispred_r_);
    M.brinfos_0_uop_br_tag = brinfo_uop_r_.br_tag & 7;
    M.brinfos_0_valid = bit(brinfos_valid_r_);
    M.dec_brmask_logic_branch_mask = branch_mask_;
    M.dec_finished_mask = 0;
    M.saturating_loads_counter = sat_loads_ctr_ & 31;
  }
  // LSU scalars
  {
    auto& L = I.r.lsu;
    L.REG_63 = store_blocked_counter_ & 15;
    L.REG_66 = bit(spec_bcast_now_);
    L.REG_67 = bit(spec_bcast_now_);
    L.REG_68 = spec_ld_ldq_r_ & 7;
    L.clr_bsy_brmask_0 = store_clr_bsy_s2_.br_mask;
    L.clr_bsy_rob_idx_0 = store_clr_bsy_s2_.rob & 0x1f;
    L.clr_bsy_valid_0 = bit(store_clr_bsy_s2_.v);
    for (int i = 0; i < kLdq; ++i) L.p1_block_load_mask[i] = (ldq_block_p1_ >> i) & 1u;
    L.r_xcpt_uop_br_mask = lsu_xcpt_brmask_r_;
    L.r_xcpt_uop_rob_idx = lsu_xcpt_rob_r_ & 0x1f;
    L.r_xcpt_valid = bit(lsu_r_xcpt_.v);
    L.stdf_clr_bsy_brmask = stdf_clr_bsy_r_.br_mask;
    L.stdf_clr_bsy_rob_idx = stdf_clr_bsy_r_.rob & 0x1f;
    L.stdf_clr_bsy_valid = bit(stdf_clr_bsy_r_.v);
    L.wb_forward_ldq_idx_0 = wb_fwd_ldq_r_ & 7;
    L.wb_forward_stq_idx_0 = wb_fwd_stq_r_ & 7;
    L.wb_forward_valid_0 = bit(wb_fwd_valid_r_);
    I.c.lsu.can_fire_load_incoming_0 = bit(canfire_load_incoming_);
    I.c.lsu.will_fire_load_wakeup_0 = bit(fired_wakeup_now_);
  }
  (void)load8;
}

}  // namespace chisa::boom_model
