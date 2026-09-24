#pragma once
// ==========================================================================
// boom_model::Core -- the rewritten Small BOOM backend (rename, issue, ROB, LSU,
// branch resolution, CSR, FP) whose registers live in the contract image.
//
// Layout principles (duts/boom-repcut/REWRITE_ARCHITECTURE.md):
//   * one static record per in-flight instruction (inst_[rob]); pipeline
//     stages and queues hold indices plus the few fields the RTL rewrites
//     or exposes while the row may be reused (StageUop, StqWord);
//   * queue status bits are bit columns (one byte per queue), so scans and
//     branch kills are word operations;
//   * every contract register field is written at the point it changes;
//     packed bank words are regenerated at the end of the step only when
//     their source changed;
//   * the combinational streams are computed from the cycle-start state and
//     written into the image's comb section during the step.
// ==========================================================================
#include <cstdint>
#include <cstring>
#include "fp_wrapper.h"
#include "../common/model_mode.h"
#include "../common/architectural_state.h"

#include "core_types.h"

namespace chisa::boom_model {

// Memory-op payload carried by the D-cache request/response seam.
struct MemUop {
  uint64_t pc = 0;
  uint8_t rob = 0, ldq_idx = 0, stq_idx = 0, pdst = 0;
  br_mask_t br_mask = 0;
  uint8_t mem_cmd = 0, mem_size = 0;
  uint8_t dst_rtype = RT_X;
  bool uses_ldq = false, uses_stq = false, is_amo = false, mem_signed = false;
  bool fp_val = false, exception = false;
  static MemUop from(const MicroOp& u, br_mask_t mask) {
    MemUop m;
    m.pc = u.debug_pc; m.rob = u.rob_idx; m.ldq_idx = u.ldq_idx; m.stq_idx = u.stq_idx;
    m.pdst = u.pdst; m.br_mask = mask; m.mem_cmd = u.mem_cmd; m.mem_size = u.mem_size;
    m.dst_rtype = u.dst_rtype; m.uses_ldq = u.uses_ldq; m.uses_stq = u.uses_stq;
    m.is_amo = u.is_amo; m.mem_signed = u.mem_signed; m.fp_val = u.fp_val;
    m.exception = u.exception;
    return m;
  }
  static MemUop from_stq(uint64_t w) {
    MemUop m;
    m.rob = StqWord::rob(w); m.ldq_idx = StqWord::ldq(w); m.stq_idx = StqWord::stq(w);
    m.pdst = StqWord::pdst(w); m.br_mask = StqWord::br_mask(w);
    m.mem_cmd = StqWord::mem_cmd(w); m.mem_size = StqWord::mem_size(w);
    m.dst_rtype = StqWord::dst_rtype(w); m.uses_ldq = StqWord::uses_ldq(w);
    m.uses_stq = StqWord::uses_stq(w); m.is_amo = StqWord::is_amo(w);
    m.mem_signed = StqWord::mem_signed(w); m.exception = StqWord::exception(w);
    return m;
  }
};

struct DmemPending {
  bool valid = false;
  MemUop uop;
  uint64_t addr = 0, data = 0;
};

struct ExtFtqGetPc {
  bool next_val = false;
  uint64_t pc = 0, next_pc = 0;
  bool cfi_valid = false;
  uint8_t cfi_idx = 0;
  bool start_bank = false;
};

// FP rename stage output register: identical DEC wires to the integer stage
// except for the map-table reads.
struct FpRenFields {
  uint8_t prs1 = 0, prs2 = 0, prs3 = 0, stale_pdst = 0, pdst = 0;
  uint8_t prs1_busy = 0, prs2_busy = 0, prs3_busy = 0;
};

// Sfence bundle registered toward the frontend.
struct SfencePending {
  bool valid = false, rs1 = false, rs2 = false;
  uint64_t addr = 0;
};

class Core {
 public:
  // Issue-queue columns; the status bits and the slot bank word live in the
  // image (pointers bound at reset).
  struct Iq {
    std::uint8_t live = 0;  // architectural occupancy, maintained with state writes
    uint8_t rob[kIq];
    uint8_t prs1[kIq], prs2[kIq], prs3[kIq];
    uint16_t fu[kIq];
    uint8_t uopc[kIq], rt1[kIq], rt2[kIq];   // slot_uop payload (shape-rewritten)
    uint8_t br_mask[kIq];
    uint8_t iq_flags[kIq];                    // bit0 fast-wake candidate, bit1 uses_ldq
    uint8_t* state; uint8_t* p1; uint8_t* p2; uint8_t* p3; uint8_t* ppred;
    uint8_t* p1_poison; uint8_t* p2_poison;
    uint32_t* packed;                          // slots_slot_uopbank_2_0[8]
    uint8_t* ready;                            // REG (RegNext num_available>0)
  };
  struct FpSlot {
    uint8_t state = 0;
    bool p1 = false, p2 = false, p3 = false, ppred = false, p1_poisoned = false, p2_poisoned = false;
    MicroOp uop;
  };

  Core();
  void bind(Image* image) { img_ = image; rob_flags_export_valid_ = false; }
  Image& img() { return *img_; }
  const Image& img() const { return *img_; }

  void reset(uint64_t boot_pc = 0);
  void step();
  void latch_hpm_events(const HpmEventInputs& input);

  boom_lsu::Candidates lsu_schedule_candidates(const LsuScheduleInputs& input) const;
  boom_lsu::Schedule compute_lsu_schedule(const LsuScheduleInputs& input) const;
  DtlbLookupCandidate dtlb_lookup_candidate(const boom_lsu::Schedule& schedule) const;

  // ---- inputs (driven by the backend wrapper before step) ---------------
  MicroOp fp_uop;                  // io.ifu.fetchpacket uop 0 (held wires)
  bool fp_offered = false;
  uint32_t fp_offered_inst = 0;
  bool fp_uop_valid = false;       // accepted this cycle (self-closed)
  bool dmem_resp_valid = false;
  uint64_t dmem_resp_data = 0;
  bool dmem_resp_uop_valid = false;
  MemUop dmem_resp_uop;
  bool dmem_resp_nack = false;
  bool dmem_nack_uses_ldq = false;
  uint8_t dmem_nack_ldq_idx = 0;
  bool dmem_nack_uses_stq = false;
  uint8_t dmem_nack_stq_idx = 0;
  bool dmem_req_ready = true;
  bool dmem_ordered = true;
  bool dmem_release_valid = false;
  uint64_t dmem_release_address = 0;
  bool hella_incoming_candidate = false;
  bool hella_wakeup_candidate = false;
  bool dtlb_passthrough = true;
  bool dtlb_req_ready = true;
  bool dtlb_miss_ready_registered = true;
  bool dtlb_resp_miss = false;
  bool dtlb_resp_uncacheable = false;
  bool dtlb_resp_pf_ld = false, dtlb_resp_pf_st = false;
  bool dtlb_resp_ae_ld = false, dtlb_resp_ae_st = false;
  uint64_t dtlb_resp_paddr = 0;
  bool mem_tlb_uncacheable_for_lcam = false;
  bool wfi_wakeup = false;
  uint64_t ext_irf_read_datas[boomcfg::IRF_READ_PORTS] = {};
  ExtFtqGetPc ext_ftq_get_pc0, ext_ftq_get_pc1;
  bool ext_fpu_response_connected = false;
  bool ext_fpu_response_valid = false;
  uint64_t ext_fpu_response_data = 0;
  bool ext_fpu_response_data_bit64 = false;
  uint8_t ext_fpu_response_flags = 0;

  // ---- outputs ---------------------------------------------------------
  uint8_t out_ifu_fetchpacket_ready = 0;
  uint8_t out_ifu_redirect_val = 0;
  uint64_t out_ifu_redirect_pc = 0;
  uint8_t out_ifu_redirect_ftq_idx = 0;
  uint8_t out_ifu_commit_valid = 0;
  uint8_t out_ifu_commit_bits = 0;
  uint8_t out_ifu_sfence_valid = 0, out_ifu_sfence_rs1 = 0, out_ifu_sfence_rs2 = 0;
  uint64_t out_ifu_sfence_addr = 0;
  uint8_t out_ifu_flush_icache = 0;
  uint64_t out_ifu_debug_fetch_pc_0 = 0;
  uint8_t out_ifu_get_pc_0_ftq_idx = 0, out_ifu_get_pc_1_ftq_idx = 0;
  uint8_t out_dmem_s1_kill = 0;
  uint8_t out_dmem_release_ready = 0;
  uint8_t out_ext_irf_read_addrs[boomcfg::IRF_READ_PORTS] = {};
  uint8_t out_ext_irf_write_valids[boomcfg::IRF_WRITE_PORTS] = {};
  uint8_t out_ext_irf_write_addrs[boomcfg::IRF_WRITE_PORTS] = {};
  uint64_t out_ext_irf_write_datas[boomcfg::IRF_WRITE_PORTS] = {};
  // Seam transients read by the wrapper after step().
  bool mem_attempt_v = false;
  MemUop mem_attempt_uop;
  uint64_t mem_attempt_addr = 0, mem_attempt_data = 0;
  bool dmem_req_fired_now = false;
  br_mask_t dmem_req_mask_now = 0;
  DmemPending dmem_pending;
  bool redirect_pending = false;
  uint64_t redirect_pending_pc = 0;
  uint8_t redirect_pending_ftq = 0;
  bool br_kill_this_cycle = false;
  bool xcpt_kill_start = false;
  SfencePending sfence_pending;
  Prf prf_landed;
  uint8_t rd_addr_reg[boomcfg::IRF_READ_PORTS] = {};
  // Registered b2 view for the frontend feedback (brupdate.b2 at cycle start).
  BrStage br_pipe[4];
  StageUop brupdate_b2_uop_r;
  BrPayload brupdate_b2_payload_r;
  // FP inner-FPU seam (one-cycle edge record).
  MicroOp fpu_inner_uop;
  bool fpu_inner_valid = false;
  uint64_t fpu_inner_rec_lo[3] = {};
  uint8_t fpu_inner_rec_hi = 0;
  uint8_t fpu_inner_fcsr_rm = 0;
  bool fdiv_inner_fire = false;
  uint64_t fdiv_inner_a = 0, fdiv_inner_b = 0;
  uint8_t fdiv_inner_hi = 0, fdiv_inner_rm = 0;
  bool fdiv_inner_sqrt = false;

  // LSQ payload the wrapper needs to tag a completion.
  MemUop ldq_uop(int idx) const;
  MemUop stq_uop(int idx) const;
  // Cycle-start LSU face for the pre-step DTLB request.
  bool mem_agu_valid() const { return mem_agu_.v; }
  unsigned stq_execute_head_dbg() const { return lsq_.stq_execute_head; }
  unsigned stq_head_dbg() const { return lsq_.stq_head; }

  const GuiderCSR& csr() const { return csr_; }
  uint64_t cycle_count() const { return cycle_count_; }
  const ArchitecturalState& architectural_state() const { return architectural_.state(); }
  const RetirementEvent& retirement_event() const { return architectural_.event(); }
  int rob_head() const { return rob_head_; }
  int rob_tail() const { return rob_tail_; }
  uint8_t rob_state() const { return rob_state_; }
  bool rob_flush_now() const { return rob_flush_now_; }
  bool rob_exception_now() const { return rob_exception_now_; }
  br_mask_t b1_resolve_mask_now() const { return b1_resolve_mask_now_; }
  br_mask_t b1_mispred_mask_now() const { return b1_mispred_mask_now_; }
  // The SFENCE request the memory stage presents this cycle (pre-step view).
  struct SfenceRequest { bool valid = false, rs1 = false, rs2 = false; uint64_t address = 0; };
  SfenceRequest sfence_request() const {
    SfenceRequest r;
    const uint8_t size = inst(mem_agu_.u).mem_size;
    r.valid = mem_agu_.v && mem_agu_.u.mem_cmd == 20;
    r.rs1 = (size & 1u) != 0;
    r.rs2 = (size & 2u) != 0;
    r.address = mem_agu_rs1_;
    return r;
  }
  const MicroOp& inst(int rob) const { return inst_[rob & (kRob - 1)]; }
  const MicroOp& inst(const StageUop& s) const { return s.null() ? NullInst::get() : inst_[s.rob]; }

  enum class OracleIssueQueue { Integer, Memory, Floating };
  std::uint64_t oracle_issue_bank0(OracleIssueQueue queue, unsigned slot) const;
  std::uint32_t oracle_rob_valid() const { return rob_val_; }
  std::uint64_t oracle_div_remainder(unsigned word) const {
    if (word < 2) return div_remainder_lo_[word];
    if (word == 2) return div_remainder_hi_ & 3u;
    throw std::out_of_range("Small divider oracle word");
  }

 private:
  Image* img_ = nullptr;
  ArchitecturalRetirement architectural_;

  // ---- per-instruction records ------------------------------------------
  MicroOp inst_[kRob];
  bool retirement_debug_[kRob] = {};  // privilege at dispatch, including DRET
  bool cycle_debug_mode_ = false;
  uint64_t uop_packed_[kRob];      // pack_rob_uop, written at enqueue (edge-delayed)
  uint8_t rob_brmask_[kRob];       // ROB row br_mask register (valid-gated updates)
  uint8_t rob_fflags_[kRob];
  // pending enqueue of the packed word (the read ports see the pre-edge array)
  int enq_packed_idx_ = -1;
  uint64_t enq_packed_val_ = 0;
  bool rob_brmask_dirty_ = false;   // regenerate rob_uopbank_0[4] at step end
  std::uint32_t exported_rob_exc_ = 0, exported_rob_unsafe_ = 0;
  bool rob_flags_export_valid_ = false;

  // ---- ROB control (bit columns, row i = bit i) --------------------------
  uint32_t rob_val_ = 0, rob_busy_ = 0, rob_unsafe_ = 0, rob_exc_ = 0;
  int rob_head_ = 0, rob_tail_ = 0;
  bool rob_empty_ = true;
  bool rob_wait_empty_ = false;
  XcptRec rob_xcpt_;               // r_xcpt_val / r_xcpt_uop{rob, br_mask, exc_cause}
  uint8_t rob_state_ = 1, rob_pnr_ = 0;
  bool pnr_maybe_at_tail_ = false, maybe_full_ = false;
  bool block_commit_r_ = false, block_commit_r2_ = false;
  bool rob_enq_fired_ = false, rob_deq_fired_ = false, rob_enq_unique_ = false;
  bool b1_mispred_now_ = false;
  // cycle-start (pre-edge) views
  uint32_t rob_val_start_ = 0, rob_busy_start_ = 0, rob_unsafe_start_ = 0, rob_exc_start_ = 0;
  int rob_head_start_ = 0, rob_tail_start_ = 0;
  bool rob_empty_start_ = true;
  uint8_t rob_pnr_start_ = 0, lsu_xcpt_rob_start_ = 0, fpiu_rob_start_ = 0;
  uint8_t map_start_[32] = {}, fp_map_start_[32] = {};
  bool rollback_restore_at_edge_ = false;
  Stage int_exe_start_;
  bool any_brinfo_mispredict_pre_ = false;
  bool csr_single_step_start_ = false, csr_retire_input_ = false, csr_exception_input_ = false;
  uint8_t st_exc_s_ = 0;
  // trap pipeline
  int trap_active_ = 0;
  bool trap_tail_ = false, trap_take_pending_ = false, trap_pend_mini_ = false;
  bool trap_from_wait_empty_ = false;
  uint64_t trap_pend_pc_ = 0, trap_pend_cause_ = 0;
  int trap_rows_total_ = 0, trap_clr_row_ = 0;
  bool trap_clr_valid_ = false;
  // commit-port RegNext mirrors
  CommitSnap commit_snap_, commit_p_, commit_r_;
  bool rob_flush_now_ = false, rob_exception_now_ = false, rob_commit_arch_now_ = false;
  uint8_t rob_flush_ftq_now_ = 0, flush_typ_now_ = 0;
  bool sys_pc2epc_deq_valid_r_ = false;
  uint8_t sys_pc2epc_deq_idx_r_ = 0;

  // ---- rename -----------------------------------------------------------
  uint8_t map_[32];
  uint8_t br_snap_[kBr][32];
  preg_mask_t busy_ = 0;
  bool map_dirty_ = false;
  br_mask_t branch_mask_ = 0, branch_mask_start_ = 0;
  bool br_mispredict_ = false;
  uint8_t br_mispredict_tag_ = 0;
  // rename stage registers
  MicroOp ren_r_;   bool ren_r_valid_ = false;     // rename_stage r_uop (REG_1_*)
  MicroOp disp_;    bool disp_valid_ = false;      // ren2 / dispatch register
  bool dis_ready_ = true, dis_valid_start_ = false, dis_fire_ = false;
  bool ren1_ran_ = false;
  bool ren2_alloc_now_ = false;
  uint8_t ren2_alloc_ldst_ = 0, ren2_alloc_pdst_ = 0;
  MicroOp dec_view_;
  bool dec_view_valid_ = false;
  uint8_t dec_uop_ftq_wire_ = 0;
  // FP rename
  uint8_t fp_map_[32];
  uint8_t fp_br_snap_[kBr][32];
  preg_mask_t fp_busy_ = 0;
  bool fp_map_dirty_ = false;
  FpRenFields fp_ren_r_, fp_disp_;
  bool fp_ren_r_valid_ = false, fp_disp_valid_ = false;
  bool fp_ren2_alloc_now_ = false;
  uint8_t fp_ren2_alloc_ldst_ = 0, fp_ren2_alloc_pdst_ = 0;

  // ---- issue queues (columns; state/p-bits live in the image) -----------
  Iq int_iq_, mem_iq_;
  uint8_t int_iq_start_valid_ = 0, mem_iq_start_valid_ = 0;
  bool iq_any_poison_ = false;
  bool int_port_consumed_ = false, mem_port_consumed_ = false;
  int8_t ghost_int_slot_ = -1, ghost_mem_slot_ = -1;
  int8_t ghost_int_partial_slot_ = -1, ghost_mem_partial_slot_ = -1;
  uint8_t ghost_fast_wake_pdst_ = 0;
  bool ghost_int_v_ = false, ghost_mem_v_ = false;
  StageUop ghost_int_uop_, ghost_mem_uop_;
  bool ghost_int_poison_ = false, ghost_mem_poison_ = false;
  uint16_t cur_int_fu_ = 0;
  uint64_t div_block_from_ = 1, div_block_until_ = 0;
  // this cycle's selects
  bool int_sel_now_ = false, int_iss_fired_ = false, int_squash_grant_ = false;
  StageUop int_sel_uop_now_;
  bool mem_sel_now_ = false, mem_iss_fired_ = false, mem_iss_load_now_ = false;
  StageUop mem_sel_uop_now_;
  bool pause_mem_r_ = false;
  uint8_t sat_loads_ctr_ = 0;
  bool spec_bcast_now_ = false, ld_miss_now_ = false;
  SpecWake spec_s1_, spec_s2_;
  bool spec_ld_r_ = false;
  uint8_t spec_ld_ldq_r_ = 0;

  // ---- integer execute pipeline ----------------------------------------
  Stage int_rrd_, int_exe_;
  bool int_rrd_killed_ = false;
  StageUop oracle_exe_, oracle_b1_, oracle_b2_, oracle_b3_, oracle_b4_;
  bool alu_unit_valid_[3] = {}, imul_unit_valid_[3] = {}, ifpu_unit_valid_[2] = {};
  uint64_t int_iss_result_ = 0, int_rrd_res_ = 0, int_exe_res_ = 0;
  struct Byp { bool v = false; uint8_t pdst = 0; uint64_t data = 0; } byp1_, byp2_;
  uint64_t exe_rs1_data_[2] = {}, exe_rs2_data_[2] = {};
  uint8_t mem_rrd_snap_prs1_ = 0, mem_rrd_snap_prs2_ = 0, mem_rrd_snap_rt1_ = 0, mem_rrd_snap_rt2_ = 0;
  StageUop brinfo_uop_r_;
  BrPayload brinfo_payload_r_;
  bool brinfo_valid_r_ = false, brinfo_mispredict_r_ = false;
  bool brinfos_valid_r_ = false, brinfos_mispredict_r_ = false, brinfos_m_now_ = false;
  bool brexe_mispred_pre_ = false, brinfos_mispred_r_ = false;
  bool brupdate_b2_mispredict_r_ = false;
  BrStage br_inject_;
  bool jmp_pc_req_valid_r_ = false;
  uint8_t jmp_pc_req_bits_r_ = 0;
  uint16_t idiv_issue_fu_mask_r_ = 0x3ff;
  Wb wb_[16];
  uint16_t wb_mask_ = 0;
  bool iresp_now_v_ = false;
  uint8_t iresp_now_rob_ = 0, iresp_rob_r_ = 0;
  bool ll_now_v_ = false;
  uint8_t ll_now_rob_ = 0;
  bool div_resp_fired_ = false;
  // multiplier / divider register mirrors
  bool imul_inpipe_v_ = false, imul_data_v_ = false;
  uint64_t imul_in1_ = 0, imul_in2_ = 0, imul_data_b_ = 0, imul_outpipe_ = 0;
  uint8_t imul_fn_ = 0, imul_dw_ = 0;
  struct MulReq { bool v = false; uint8_t left = 0; uint64_t in1 = 0, in2 = 0; uint8_t fn = 0, dw = 0; br_mask_t br_mask = 0; } mul_req_;
  struct DivReq { bool v = false; uint8_t left = 0; uint64_t in1 = 0, in2 = 0; uint8_t fn = 0, dw = 0; StageUop uop; } div_req_;
  StageUop div_r_uop_;
  uint8_t div_state_ = 0, div_count_ = 0, div_jump_ = 0;
  bool div_isHi_ = false, div_req_dw_ = false, div_neg_out_ = false;
  uint64_t div_lhs_ = 0, div_rhs_ = 0, div_divisor_lo_ = 0, div_remainder_lo_[2] = {};
  uint8_t div_divisor_hi_ = 0, div_remainder_hi_ = 0;
  // IntToFP input registers
  uint64_t ifpu_in1_ = 0;
  uint8_t ifpu_rm_ = 0, ifpu_typ_ = 0, ifpu_type_tag_in_ = 0;
  bool ifpu_wflags_ = false;
  // ROB read ports (this cycle)
  bool rob_read_bsy_now_[3] = {};
  uint64_t rob_read_uop_packed_now_[3] = {};

  // ---- LSU --------------------------------------------------------------
  struct Lsq {
    // LDQ columns (bit i = entry i)
    uint8_t ld_valid = 0, ld_addr_valid = 0, ld_executed = 0, ld_succeeded = 0,
            ld_order_fail = 0, ld_observed = 0, ld_fwd_std_val = 0, ld_virtual = 0,
            ld_uncacheable = 0, ld_exc = 0;
    uint64_t ld_addr[kLdq] = {};
    uint8_t ld_stdep[kLdq] = {}, ld_fwd_stq[kLdq] = {}, ld_youngest[kLdq] = {};
    uint8_t ld_pdst[kLdq] = {}, ld_brmask[kLdq] = {}, ld_rob[kLdq] = {};
    // STQ columns
    uint8_t st_valid = 0, st_addr_valid = 0, st_virtual = 0, st_data_valid = 0,
            st_committed = 0, st_succeeded = 0;
    uint64_t st_word[kStq] = {};            // StqWord
    int ldq_head = 0, ldq_tail = 0;
    int stq_head = 0, stq_tail = 0, stq_commit_head = 0, stq_execute_head = 0;
    lsq_mask_t live_store_mask = 0;
  } lsq_;
  bool ldq_dirty_ = true, stq_dirty_ = true;   // regenerate bank words at step end
  uint64_t lsq_ptr_sig_ = ~UINT64_C(0);        // last packed queue pointers (bank words carry them)
  // pipeline
  Stage mem_iss_, mem_rrd_, mem_agu_;
  uint64_t mem_iss_rs1_ = 0, mem_iss_rs2_ = 0, mem_rrd_rs1_ = 0, mem_rrd_rs2_ = 0;
  uint64_t mem_agu_rs1_ = 0, mem_agu_rs2_ = 0;
  bool mem_iss_vmir_ = false, mem_rrd_vmir_ = false, mem_agu_vmir_ = false;
  bool mem_rrd_killed_ = false, mem_agu_killed_ = false;
  bool dmem_pipelined_ = true;
  int8_t lcam_ldq_s1_ = -1;
  bool lcam_fired_s1_ = false, lcam_incoming_s1_ = false, lcam_store_search_s1_ = false;
  uint8_t lcam_store_stq_s1_ = 0, lcam_store_size_s1_ = 0;
  uint64_t lcam_store_addr_s1_ = 0;
  bool release_search_s1_ = false;
  uint64_t release_address_s1_ = 0;
  lsq_mask_t nacking_loads_prev_ = 0;
  FwdWb fwd_wb_;
  bool wb_fwd_valid_r_ = false;
  uint8_t wb_fwd_ldq_r_ = 0, wb_fwd_stq_r_ = 0;
  bool block_wakeup_next_ = false;
  lsq_mask_t ldq_block_p1_ = 0, ldq_block_p2_ = 0, ldq_block_now_r_ = 0;
  uint8_t ldq_wakeup_idx_ = 7, ldq_retry_idx_ = 7, stq_retry_idx_ = 7;
  bool commit_load_at_rob_head_ = false;
  uint8_t store_blocked_counter_ = 0;
  ClrBsy store_clr_bsy_s1_, store_clr_bsy_s2_, stdf_clr_bsy_r_;
  XcptRec lsu_r_xcpt_, mem_xcpt_;
  bool lsu_r_xcpt_killed_now_ = false;
  uint8_t mem_xcpt_rob_r_ = 0;
  br_mask_t mem_xcpt_brmask_r_ = 0, lsu_xcpt_brmask_r_ = 0;
  uint8_t lsu_xcpt_rob_r_ = 0;
  uint8_t mem_incoming_ldq_r_ = 0, mem_incoming_rob_r_ = 0, mem_incoming_pdst_r_ = 0;
  br_mask_t mem_incoming_brmask_r_ = 0;
  uint8_t conv_rrd_ldq_ = 0, conv_exe_ldq_ = 0;
  br_mask_t conv_rrd_mask_ = 0;
  bool dmem_pending_kill_ = false;
  bool adp_valid_ = false;
  br_mask_t adp_mask_ = 0;
  uint64_t mem_paddr_r_ = 0;
  bool fired_wakeup_now_ = false, fired_load_wakeup_r_ = false, canfire_load_incoming_ = false;
  bool fwd_match_now_ = false;
  uint8_t ldq_b1_killed_now_ = 0;
  br_mask_t b1_mispred_mask_now_ = 0, b1_resolve_mask_now_ = 0;
  bool flush_redirect_now_ = false;
  // cycle-start LSU snapshots (masks only: the columns move during the step)
  uint8_t ld_valid_s_ = 0, ld_addr_valid_s_ = 0, ld_virtual_s_ = 0, ld_uncacheable_s_ = 0,
          ld_fwd_std_val_s_ = 0, ld_exc_s_ = 0, ld_exsucc_s_ = 0;
  uint8_t st_valid_s_ = 0, st_addr_valid_s_ = 0, st_virtual_s_ = 0, st_data_valid_s_ = 0,
          st_committed_s_ = 0, st_succeeded_s_ = 0;
  uint8_t ldq_head_s_ = 0, stq_commit_head_s_ = 0;
  uint8_t ldq_elig_s_ = 0, ldq_retry_elig_s_ = 0, stq_retry_elig_s_ = 0;
  br_mask_t wakeup_mask_s_ = 0, mem_xcpt_brmask_s_ = 0;
  // pre-edge br_masks of the queue entries: a request handed to the D-cache
  // carries the register value (the cache applies the branch update itself)
  uint8_t ld_brmask_s_[kLdq] = {};
  uint8_t st_brmask_s_[kStq] = {};
  boom_lsu::Schedule sched_s_;
  Stage mem_agu_s_;
  uint64_t mem_agu_rs1_s_ = 0, mem_agu_rs2_s_ = 0;

  // ---- CSR --------------------------------------------------------------
  GuiderCSR csr_;
  bool csr_retire_r_ = false, csr_exception_r_ = false;
  CsrWrite csr_wr_pend_;
  uint64_t csr_flush_target_ = 0;
  uint64_t cycle_count_ = 0, minstret_count_ = 0, minstret_csr_reg_ = 0;
  // Advances at every end_of_step()/reset(): the LSU schedule memo is keyed on
  // it, so the pre-step callers and cycle_start() share one computation.
  uint64_t sched_epoch_ = 0;
  bool debug_jalr_flush_icache_pending_ = false;
  Prf prf_;
  bool resp_byp_v_ = false;
  uint8_t resp_byp_pdst_ = 0;
  uint64_t resp_byp_data_ = 0;
  int oracle_reset_ticks_ = 0;

  // ---- FP subsystem (ported; rare activity) ------------------------------
  FpSlot fp_iq_[8];
  bool fp_iq_dirty_ = true;
  uint64_t fp_prf_[boomcfg::NUM_FPREGS] = {};
  uint64_t fp_prf_rec_lo_[boomcfg::NUM_FPREGS] = {};
  uint8_t fp_prf_rec_hi_[boomcfg::NUM_FPREGS] = {};
  uint8_t fp_iq_start_valid_ = 0;
  bool fp_iq_ready_ = true, fp_port_consumed_ = false;
  int ghost_fp_slot_ = -1; bool ghost_fp_v_ = false; MicroOp ghost_fp_uop_;
  uint16_t cur_fp_fu_ = 0;
  bool fdv_mask_this_ = false;
  MicroOp fp_rrd_uop_; bool fp_rrd_valid_ = false;
  MicroOp fp_exe_uop_; bool fp_exe_valid_ = false;
  uint8_t fp_read_addrs_[3] = {};
  bool fp_read_zero_r_[3] = {true, true, true};
  bool fp_rrd_killed_ = false;
  uint64_t fp_rrd_rec_lo_[3] = {}; uint8_t fp_rrd_rec_hi_ = 0;
  uint64_t fp_exe_rec_lo_[3] = {}; uint8_t fp_exe_rec_hi_ = 0;
  FpWrapperUop fpu_wrapper_uops_[4]; bool fpu_wrapper_valids_[4] = {};
  FpInflight fpu_pipe_[10], i2f_pipe_[8], fdiv_req_pipe_[4];
  bool fpu_external_result_[10] = {};
  FpInflight fdiv_buffer_, fdiv_pend_, fdiv_out_;
  uint64_t fdiv_buffer_fin_lo_[2] = {}; uint8_t fdiv_buffer_fin_hi_ = 0;
  bool fdiv_pend_killed_ = false;
  FpQEntry f2i_q_[8], fp_sdq_[3], from_int_q_[4];
  FpBranchQueueMirror<7, true> f2i_q_mirror_;
  FpBranchQueueMirror<3, false> fp_sdq_mirror_;
  FpBranchQueueMirror<5, true> from_int_q_mirror_;
  uint64_t ifpu_out_rec_lo_ = 0; uint8_t ifpu_out_rec_hi_ = 0;
  FpQEntry ll_wr_reg_;
  uint64_t ll_wr_rec_lo_ = 0; uint8_t ll_wr_rec_hi_ = 0;
  uint8_t fp_slow_wake_[8]; int n_fp_slow_wake_ = 0;
  uint8_t fp_quiet_streak_ = 0;
  bool fp_stdata_fire_s1_v_ = false; uint8_t fp_stdata_fire_s1_stq_ = 0;
  br_mask_t fp_stdata_fire_s1_brmask_ = 0; uint8_t fp_stdata_fire_s1_rob_ = 0;
  bool fp_stdata_stq_qual_start_ = false, fp_stdata_fire_s1_killed_now_ = false;
  bool fp_ll_ld_v_ = false; MemUop fp_ll_ld_uop_; uint64_t fp_ll_ld_data_ = 0;
  bool fp_ll_now_v_ = false;
  uint8_t fp_ll_now_rob_ = 0;
  uint8_t fp_ll_rob_r_ = 0, fpiu_rob_r_ = 0, stdf_rob_r_ = 0;
  bool fp_disp_v_now_ = false;
  bool fp_flush_pipeline_now_ = false;
  MicroOp fpu_wrapper_input_uop_; bool fpu_wrapper_input_valid_ = false;
  uint8_t fcsr_rm_start_ = 0;
  uint64_t exe_rs1_start_[2] = {};
  int fp_iq_slots_ = boomcfg::NUM_FP_IQ_SLOTS;
  // fp rename freelist pre-selection
  uint8_t fp_alloc_sel_ = 0; bool fp_alloc_valid_ = false;

  // ---- step phases --------------------------------------------------------
  void cycle_start();
  void branch_step();
  void apply_brupdate(br_mask_t resolve, br_mask_t mispredict);
  void writeback_step(uint8_t* slow_wake, int& n_slow_wake);
  void dispatch_hazards();
  void decode_and_rename();
  void rename_step();
  void dispatch_step();
  void issue_step();
  void rob_step();
  void lsu_step();
  void end_of_step();
  void export_step();

  // rename helpers
  void export_ren_r();
  void map_write(uint8_t lreg, uint8_t preg) { map_[lreg & 31] = preg; map_dirty_ = true; }
  void fp_map_write(uint8_t lreg, uint8_t preg) { fp_map_[lreg & 31] = preg; fp_map_dirty_ = true; }
  void pack_map();
  void pack_fp_map();
  // issue helpers
  void iq_bind(Iq& q, bool is_int);
  void iq_load_slot(Iq& q, int i, const MicroOp& du);
  void iq_move_slot(Iq& q, int destination, int source);
  void iq_wake(Iq& q, uint8_t p);
  bool iq_spec_wake(Iq& q, uint8_t p);
  int iq_peek(const Iq& q, uint16_t port_fu) const;
  bool iq_req(const Iq& q, int i) const;
  bool iq_collapse(Iq& q, uint16_t port_fu, uint8_t start_valid, bool port_consumed,
                   bool disp_v, const MicroOp& du, int ghost_slot, int squash_slot,
                   int& grant_slot, StageUop& grant, int& avail);
  StageUop iq_selected(const Iq& q, int i) const;
  void iq_flush(Iq& q);
  // rob helpers
  uint64_t packed_at_start(int idx) const {
    return idx == enq_packed_idx_ ? uop_packed_[idx] : uop_packed_[idx];
  }
  void rob_read_port(int p, unsigned idx, bool busy_start_bit);
  // lsu helpers
  void lsq_dispatch(const MicroOp& du);
  void lsq_pack();
  void wb_schedule(uint8_t rob, uint8_t pdst, uint8_t left, bool slow_wake, uint64_t data,
                   br_mask_t br_mask, bool drives_port, bool is_div, bool is_mul);
  // csr
  uint64_t compute_csr_rdata(uint32_t addr) const;
  void exec_csr(const MicroOp& u, uint8_t cmd, uint64_t rs1_val);
  uint64_t take_trap(uint64_t epc, uint64_t cause, uint32_t inst = 0);
  uint64_t trap_target(uint64_t cause, uint32_t inst = 0) const;
  bool trap_to_debug(uint64_t cause, uint32_t inst = 0) const;
  void csr_export();
  void csr_export_counters();
  // fp
  void fp_reset();
  void fp_flush();
  void fp_apply_brupdate(br_mask_t resolve, br_mask_t mispredict);
  void fp_fpu_wrapper_advance();
  void fp_restore(uint8_t tag);
  void fp_rename_ren2(preg_mask_t free_select_view);
  void fp_issue_step(bool to_fp);
  void fp_i2f_launch(const MicroOp& u, uint64_t rs1);
  void fp_pipe_advance();
  void fp_commit(const MicroOp& u);
  void fp_commit_free(const MicroOp& u);
  void fp_rollback(const MicroOp& u);
  void fp_export();
  void fp_wakeup(uint8_t pdst, uint8_t rob, uint8_t flags);
  void fp_cycle_start();
  void fp_snapshot_stdata();
  void fp_export_queue_mirrors();

  friend class Backend;
};

}  // namespace chisa::boom_model
