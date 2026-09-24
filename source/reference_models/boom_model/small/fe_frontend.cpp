// model frontend: fetch-unit glue.  See fe_frontend.h.
#include "fe_frontend.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace chisa::boom_system {

namespace fe = chisa::boom_model::fe;
using fe::kPcMask40;

namespace {
inline std::uint8_t b(bool v) { return v ? 1u : 0u; }
}  // namespace

FrontendState::FrontendState(boom_model::Image& image) : I_(image), bpd_(image) {}

// ---------------------------------------------------------------------------
// redirect reconstruction (core.scala's ungated b2 payload; see the previous
// frontend_state.h for the derivation)
// ---------------------------------------------------------------------------
std::uint64_t FrontendState::reconstructed_redirect_pc(const BackendFrontendControl& c,
                                                       const components::SmallFtqGetPcResponse& g1) {
  if (c.redirect_valid) return c.redirect_pc;
  constexpr std::uint64_t kBlockMask = ~UINT64_C(63);
  const std::uint64_t block_pc = g1.pc & kBlockMask;
  const std::uint64_t uop_pc = block_pc | (c.redirect_branch_pc_lob & 0x3fu);
  const std::uint64_t npc = uop_pc + ((c.redirect_branch_is_rvc || c.redirect_branch_edge_inst) ? UINT64_C(2) : UINT64_C(4));
  const std::int64_t edge_adjust = c.redirect_branch_edge_inst ? -2 : 0;
  const std::uint64_t jal_br_target = static_cast<std::uint64_t>(
      static_cast<std::int64_t>(uop_pc) + c.redirect_branch_target_offset + edge_adjust);
  const std::uint64_t branch_or_jalr = c.redirect_branch_cfi_type == 3 ? c.redirect_branch_jalr_target : jal_br_target;
  return (c.redirect_branch_pc_sel == PC_PLUS4 ? npc : branch_or_jalr) & kPcMask40;
}

void FrontendState::redirect_history(const BackendFrontendControl& c,
                                     const components::SmallFtqGetPcResponse& g0,
                                     const components::SmallFtqGetPcResponse& g1,
                                     fe::SmallGlobalHistory& out) {
  out = fe::SmallGlobalHistory{};
  if (c.redirect_from_rob_flush) {
    out.current_saw_branch_not_taken = true;
    out.ras_idx = static_cast<std::uint8_t>(g0.entry.ras_idx & 0x1fu);
    return;
  }
  const components::SmallFtqEntry& entry = g1.entry;
  constexpr std::uint64_t kBlockMask = ~UINT64_C(63);
  constexpr std::uint64_t kBankMask = ~UINT64_C(7);
  const std::uint64_t block_pc = g1.pc & kBlockMask;
  const std::uint64_t uop_pc = block_pc | (c.redirect_branch_pc_lob & 0x3fu);
  const std::uint64_t npc = uop_pc + ((c.redirect_branch_is_rvc || c.redirect_branch_edge_inst) ? UINT64_C(2) : UINT64_C(4));
  const bool b2_is_br = c.redirect_branch_cfi_type == 1;
  const bool use_same_history = b2_is_br && !c.redirect_branch_taken && (block_pc & kBankMask) == (npc & kBankMask);
  if (use_same_history) {
    out = g1.ghist;
    out.current_saw_branch_not_taken = true;
    return;
  }
  const std::uint8_t bank_xor = entry.start_bank ? std::uint8_t{8} : std::uint8_t{0};
  const std::uint8_t cfi_idx = static_cast<std::uint8_t>(((c.redirect_branch_pc_lob ^ bank_xor) >> 1u) & 3u);
  const unsigned cfi_fixed = cfi_idx & 3u;
  const std::uint8_t cfi_oh = static_cast<std::uint8_t>(1u << cfi_fixed);
  const std::uint8_t selected = static_cast<std::uint8_t>((cfi_oh << 1u) - 1u);
  const std::uint8_t taken_cfi = (b2_is_br && c.redirect_branch_taken) ? cfi_oh : 0u;
  const std::uint8_t not_taken = static_cast<std::uint8_t>(entry.br_mask & selected & static_cast<std::uint8_t>(~taken_cfi));
  fe::advance_global_history(g1.ghist, not_taken, b2_is_br, c.redirect_branch_taken, true, cfi_fixed, g1.pc, out);
  const bool is_call = entry.cfi_is_call && entry.cfi_idx == cfi_fixed;
  const bool is_ret = entry.cfi_is_ret && entry.cfi_idx == cfi_fixed;
  if (is_call) out.ras_idx = static_cast<std::uint8_t>((g1.ghist.ras_idx + 1u) & 0x1fu);
  else if (is_ret) out.ras_idx = static_cast<std::uint8_t>((g1.ghist.ras_idx - 1u) & 0x1fu);
  else out.ras_idx = static_cast<std::uint8_t>(g1.ghist.ras_idx & 0x1fu);
}

// ---------------------------------------------------------------------------
// evaluate
// ---------------------------------------------------------------------------
void FrontendState::evaluate_into(FrontendEvaluation& r, const FrontendInputs& in,
                                  const BackendFrontendFeedback& fb) {
  r.reset = in.reset;
  r.run = in.run;
  if (!in.run) return;
  ++cycle_;
  bpd_.evaluate();
  const bool clear = frontend_clear(in);
  r.clear = clear;

  // Registered faces read in place.
  const components::SmallICacheResponse raw_icache = icache_.held_response();
  const fe::SmallFetchBundle& held_f4 = f4_queue_.payload();
  const bool f4_enq_valid = f3_queues_.main_full() && !clear;
  const bool delay = held_f4.sfb_mask != 0 && !held_f4.cfi_valid && !f4_enq_valid &&
                     !held_f4.xcpt_pf_if && !held_f4.xcpt_ae_if;
  const bool fb_enq_ready = fetch_buffer_.enq_ready();
  const bool ftq_enq_ready = ftq_.enq_ready();
  const bool f4_deq_ready = fb_enq_ready && ftq_enq_ready && !delay;
  const bool f4_enq_ready = f4_queue_.enq_ready(f4_deq_ready);
  const bool f4_deq_valid = f4_queue_.deq_valid();
  const std::uint64_t ras_read = ras_.read_addr();

  held_itlb_cycle_inputs_into(in, r.itlb_input);
  r.itlb = itlb_.outputs(r.itlb_input, in.debug_mode);

  // F3 queues (their outputs depend only on registered state and f4 ready).
  const bool f3_main_deq_valid = f3_queues_.main_deq_valid();
  const bool f3_main_enq_ready = f3_queues_.main_enq_ready(f4_enq_ready);
  const bool f3_bpd_enq_valid = f3_queues_.bpd_enq_valid();
  const bool f3_bpd_enq_ready = f3_queues_.bpd_enq_ready(f4_enq_ready);
  const bool f3_bpd_deq_valid = f3_queues_.bpd_deq_valid();
  const fe::SmallFrontendResp& f3_main = f3_queues_.main_deq();
  const bool bpd_from_ram = f3_queues_.bpd_full();
  const fe::SmallBpdResponse& f3_bpd = bpd_from_ram ? f3_queues_.bpd_payload() : bpd_.f3_response();
  const std::uint64_t bpd_key = bpd_from_ram ? std::uint64_t(f3_queues_.bpd_version())
                                             : ((UINT64_C(1) << 63) | cycle_);
  const fe::F3Assembled& assembled = f3_assembler_.evaluate(
      clear, f3_main_deq_valid, f3_main, f3_queues_.main_version(), f3_bpd, bpd_key, ras_read);

  // F0-F2 control.
  fe::F0F2In fi;
  fi.reset = in.reset;
  fi.f3_enq_ready = f3_main_enq_ready;
  fi.icache_resp_valid = raw_icache.valid;
  fi.icache_resp_data = raw_icache.data;
  fi.tlb = &r.itlb;
  fi.bpd_f1 = &bpd_.f1();
  fi.bpd_f2 = &bpd_.f2();
  fi.f3_deq_valid = f3_main_deq_valid;
  fi.f4_ready = f4_enq_ready;
  fi.f3_predicted_target = assembled.predicted_target;
  fi.f3_predicted_ghist = &assembled.predicted_ghist;
  fi.f3_fsrc = f3_main.fsrc;
  fi.f3_xcpt_pf_if = f3_main.xcpt_pf_if;
  fi.f3_xcpt_ae_if = f3_main.xcpt_ae_if;
  fi.sfence_valid = in.backend_control.sfence_valid;
  fi.sfence_addr = in.backend_control.sfence_addr;
  fi.redirect_flush = in.backend_control.redirect_flush;
  fi.redirect_valid = in.backend_control.redirect_valid;
  // F0-F2 consumes this reconstruction only on redirect_flush. Keep its
  // real flush behavior, including flushes that do not issue a new fetch.
  if (boom_model::kInternalSignalContract || fi.redirect_flush) {
    fi.redirect_pc = reconstructed_redirect_pc(in.backend_control, ftq_.registered_get_pc(1));
    redirect_history(in.backend_control, ftq_.registered_get_pc(0), ftq_.registered_get_pc(1), r.redirect_ghist);
  }
  fi.redirect_ghist = &r.redirect_ghist;
  f0_f2_.evaluate(fi, r.f0_f2);
  const components::SmallF0F2Outputs& f0 = r.f0_f2.out;

  // I-cache.
  components::SmallICacheInputs& ii = r.icache_input;
  ii.reset = in.reset;
  ii.req_valid = f0.icache_req_valid;
  ii.req_addr = f0.icache_req_addr;
  ii.s1_paddr = static_cast<std::uint32_t>(f0.icache_s1_paddr);
  ii.s1_kill = f0.icache_s1_kill;
  ii.s2_kill = f0.icache_s2_kill;
  ii.invalidate = in.backend_control.icache_invalidate;
  ii.tl_a_ready = in.icache_memory.tl_a_ready;
  ii.tl_d_valid = in.icache_memory.tl_d_valid;
  ii.tl_d_opcode = in.icache_memory.tl_d_opcode;
  ii.tl_d_size = in.icache_memory.tl_d_size;
  ii.tl_d_data = in.icache_memory.tl_d_data;
  ii.tl_d_data_hi = in.icache_memory.tl_d_data_hi;
  r.icache = icache_.outputs(ii);

  // The assembled bundle's source tag is the final F0-F2 decision.
  f3_assembler_.out().bundle.debug_fsrc = static_cast<std::uint8_t>(f0.final_fsrc & 3u);
  const bool f3_main_enq_valid = f0.f3_enq_valid;

  // Predictor update arbiter.
  const bool f3_fire = f3_main_deq_valid && f4_enq_ready;
  const bool ftq_upd_valid = ftq_.bpdupdate_valid();
  r.bpd_update_valid = bpd_update_path_.update_valid(ftq_upd_valid);
  r.bpd_update = &bpd_update_path_.update(ftq_upd_valid, ftq_.bpdupdate());
  r.f3_fire = f3_fire;
  r.f3_btb_mispredicts = assembled.btb_mispredicts;

  // RAS.
  const bool f3_enq_fire = f3_main_enq_valid && f3_main_enq_ready;
  r.ras_read_idx = f3_enq_fire ? static_cast<std::uint8_t>(f0.f3_enq.ghist.ras_idx & 0x1fu) : ras_read_idx_;
  r.ras_write_valid = f3_main_deq_valid && f4_enq_ready && assembled.ras_write_valid;
  r.ras_write_idx = assembled.ras_write_idx;
  r.ras_write_addr = assembled.ras_write_addr;
  if (ftq_.ras_update()) {
    r.ras_write_valid = true;
    r.ras_write_idx = ftq_.ras_update_idx();
    r.ras_write_addr = ftq_.ras_update_pc();
  }

  // frontend.scala:388 -- the F2-stage clears decided above gate the TLB
  // request so a cleared s1 does not start the miss state machine.
  {
    const auto& s1 = f0_f2_.s1();
    r.itlb_input.request_valid = ((s1.valid && !s1.is_replay && !f0.f1_clear && !clear) || s1.is_sfence);
  }
  r.next_itlb_sfence.valid = in.backend_control.sfence_valid;
  r.next_itlb_sfence.rs1 = in.backend_control.sfence_rs1;
  r.next_itlb_sfence.rs2 = in.backend_control.sfence_rs2;
  r.next_itlb_sfence.address = in.backend_control.sfence_addr;

  // Queue controls.
  r.f4_reset = in.reset || clear;
  r.f4_enq_valid = f4_enq_valid;
  r.f4_enq_ready = f4_enq_ready;
  r.f4_deq_ready = f4_deq_ready;
  r.f4_delay = delay;
  r.fb_enq_valid = f4_deq_valid && ftq_enq_ready && !delay;
  r.fb_ftq_idx = static_cast<std::uint8_t>(ftq_.enq_idx() & (boomcfg::NUM_FTQ - 1));
  r.fb_deq_ready = in.fetch_ready;
  r.ftq_upd_valid = ftq_upd_valid;
  fe::FtqIn& q = r.ftq_input;
  q.reset = in.reset;
  q.enq_valid = f4_deq_valid && fb_enq_ready && !delay;
  q.enq = &held_f4;
  q.deq_valid = fb.ftq_deq_valid;
  q.deq_idx = fb.ftq_deq_idx;
  q.redirect_valid = fb.ftq_redirect_valid;
  q.redirect_idx = fb.ftq_redirect_idx;
  q.brupdate_mispredict = fb.ftq_brupdate_mispredict;
  q.brupdate_ftq_idx = fb.ftq_brupdate_idx;
  q.brupdate_pc_lob = fb.ftq_brupdate_pc_lob;
  q.brupdate_taken = fb.ftq_brupdate_taken;
  q.get_pc_idx[0] = fb.ftq_get_pc_0_idx;
  q.get_pc_idx[1] = fb.ftq_get_pc_1_idx;
  r.ftq_do_commit = ftq_.do_commit_update(q);
  r.f3_main_enq_valid = f3_main_enq_valid;
  r.f3_main_enq_ready = f3_main_enq_ready;
  r.f3_bpd_enq_valid = f3_bpd_enq_valid;
  r.f3_bpd_enq_ready = f3_bpd_enq_ready;
  r.f3_bpd_deq_valid = f3_bpd_deq_valid;
  r.f3_deq_ready = f4_enq_ready;

  fe::BpdIn& bi = r.bpd_in;
  bi.reset = in.reset;
  bi.f0_valid = f0.icache_req_valid;
  bi.f0_pc = f0.icache_req_addr;
  bi.f1_ghist = f0_f2_.s1().ghist.old_history;
  bi.f3_fire = f3_bpd_enq_valid && f3_bpd_enq_ready;
  bi.update_valid = r.bpd_update_valid;
  bi.update = r.bpd_update;
}

// ---------------------------------------------------------------------------
// commit
// ---------------------------------------------------------------------------
void FrontendState::commit(const FrontendEvaluation& e) {
  if (!e.run && !e.reset) return;
  if (!e.run) { commit_reset(e.reset); return; }

  // The predictor bank reads the update through a pointer into the FTQ or
  // the correction queue: commit it before either of those advances.
  bpd_.commit(e.bpd_in);
  // The FetchBuffer and FTQ read the F4 payload in place: before F4 moves.
  fetch_buffer_.commit(e.reset, e.clear, e.fb_enq_valid, f4_queue_.payload(), e.fb_ftq_idx, e.fb_deq_ready);
  ftq_.commit(e.ftq_input, e.ftq_do_commit);
  f4_queue_.commit(e.f4_reset, e.f4_enq_valid, e.f4_enq_ready, f3_assembler_.out().bundle, e.f4_deq_ready);
  bpd_update_path_.commit(e.reset, e.f3_fire, e.f3_btb_mispredicts, f3_assembler_.out().bundle,
                          e.ftq_upd_valid);
  f3_assembler_.commit(e.reset, e.clear, f3_queues_.main_deq_valid(), e.f3_deq_ready);
  f3_queues_.commit(e.reset, e.clear, e.f3_main_enq_valid, e.f3_main_enq_ready, e.f0_f2.out.f3_enq,
                    e.f3_bpd_enq_valid, e.f3_bpd_enq_ready, e.f3_bpd_deq_valid, bpd_.f3_response(),
                    e.f3_deq_ready);
  itlb_.step(e.itlb_input);
  itlb_sfence_r_ = e.next_itlb_sfence;
  f0_f2_.commit(e.reset, e.f0_f2);
  icache_.commit(e.icache_input, e.icache);
  ras_.step(e.ras_read_idx, e.ras_write_valid, e.ras_write_idx, e.ras_write_addr);
  if (e.f3_main_enq_valid && e.f3_main_enq_ready)
    ras_read_idx_ = static_cast<std::uint8_t>(e.f0_f2.out.f3_enq.ghist.ras_idx & 0x1fu);
  if (e.reset) ras_read_idx_ = 0;
  write_lanes();
}

void FrontendState::commit_reset(bool reset) {
  // Every component takes its reset edge with default inputs, as the
  // RTL does while reset is held.
  fe::BpdIn bi;
  bi.reset = true;
  bpd_.commit(bi);
  fetch_buffer_.commit(true, false, false, f4_queue_.payload(), 0, false);
  fe::FtqIn q;
  q.reset = true;
  ftq_.commit(q, ftq_.do_commit_update(q));
  f4_queue_.commit(true, false, f4_queue_.enq_ready(false), f3_assembler_.out().bundle, false);
  bpd_update_path_.commit(true, false, 0, f3_assembler_.out().bundle, false);
  f3_assembler_.commit(true, false, false, false);
  {
    // Reset edges present the default (all-zero) enqueue payloads.
    static const fe::SmallBpdResponse kZeroBpd{};
    f3_queues_.commit(true, false, false, f3_queues_.main_enq_ready(false), f3_queues_.main_deq(),
                      f3_queues_.bpd_enq_valid(), f3_queues_.bpd_enq_ready(false), f3_queues_.bpd_deq_valid(),
                      kZeroBpd, false);
  }
  {
    // The S2 exception payload is not reset in RTL: the invalid address-0
    // lookup is denied and its ae.inst bit is latched even under reset.
    const components::SmallFrontendTlbResponse tlb = itlb_.outputs(0, false);
    static const fe::SmallFrontendPredictionResponse kEmptyResp{};
    static const fe::SmallGlobalHistory kEmptyGhist{};
    fe::F0F2In fi;
    fi.reset = true;
    fi.tlb = &tlb;
    fi.bpd_f1 = &kEmptyResp;
    fi.bpd_f2 = &kEmptyResp;
    fi.f3_predicted_ghist = &kEmptyGhist;
    fi.redirect_ghist = &kEmptyGhist;
    fe::F0F2Eval ev;
    f0_f2_.evaluate(fi, ev);
    f0_f2_.commit(true, ev);
  }
  {
    components::SmallICacheInputs ii;
    ii.reset = true;
    icache_.commit(ii, icache_.outputs(ii));
  }
  // The RTL RAS write-addr wire carries the assembler's fall-through value
  // while reset holds: 2*(fetchWidth-1)+2.
  ras_.step(0, false, 0, 2u * (boomcfg::FETCH_WIDTH - 1) + 2u);
  itlb_.step(0, false, reset);
  itlb_sfence_r_ = {};
  ras_read_idx_ = 0;
  write_lanes();
}

// ---------------------------------------------------------------------------
// contract lanes of the fetch pipeline (the predictor bank writes its own)
// ---------------------------------------------------------------------------
void FrontendState::write_itlb_lanes() {
  const components::SmallInstructionTlb& t = itlb_.state_for_diagnostic();
  auto& T = I_.r.frontendTlb;
  T.r_refill_tag = t.refill_tag() & 0x7ffffffu;
  T.r_sectored_hit = b(t.sectored_hit());
  T.r_sectored_hit_addr = t.sectored_hit_address() & 7u;
  T.r_sectored_repl_addr = t.sectored_replacement_address() & 7u;
  T.r_superpage_repl_addr = t.superpage_replacement_address() & 3u;
  T.state = static_cast<std::uint8_t>(t.state()) & 3u;
  if (t.entries_epoch() == itlb_epoch_) return;
  itlb_epoch_ = t.entries_epoch();
  T.special_entry_data_0 = components::SmallInstructionTlb::pack_entry_data(t.special_entry().data[0]) & ((UINT64_C(1) << 35) - 1);
  T.special_entry_valid_0 = b(t.special_entry().valid[0]);
  std::uint8_t* sect[8] = {T.sectored_entries_0_0_valid, T.sectored_entries_0_1_valid, T.sectored_entries_0_2_valid,
                           T.sectored_entries_0_3_valid, T.sectored_entries_0_4_valid, T.sectored_entries_0_5_valid,
                           T.sectored_entries_0_6_valid, T.sectored_entries_0_7_valid};
  for (std::size_t e = 0; e < 8; ++e)
    for (std::size_t s = 0; s < 4; ++s) sect[e][s] = b(t.sectored_entry(e).valid[s]);
  for (std::size_t e = 0; e < 4; ++e) T.superpage_entries_valid_0[e] = b(t.superpage_entry(e).valid[0]);
}

void FrontendState::write_lanes() {
  // ---- F0-F2 ----
  {
    const auto& s1 = f0_f2_.s1();
    const auto& s2 = f0_f2_.s2();
    auto& M = I_.r.frontendMisc;
    I_.r.frontendBpd.REG = s1.ghist.old_history;
    M.s1_ghist_old_history = s1.ghist.old_history;
    M.s1_vpc = s1.vpc & kPcMask40;
    M.s2_ghist_old_history = s2.ghist.old_history;
    M.s2_ppc = s2.ppc;
    M.REG_4 = b(s2.replay_reg);
    M.s1_ghist_new_saw_branch_not_taken = b(s1.ghist.new_saw_branch_not_taken);
    M.s1_ghist_new_saw_branch_taken = b(s1.ghist.new_saw_branch_taken);
    M.s1_ghist_ras_idx = s1.ghist.ras_idx & 0x1fu;
    M.s1_valid = b(s1.valid);
    M.s2_ghist_current_saw_branch_not_taken = b(s2.ghist.current_saw_branch_not_taken);
    M.s2_ghist_new_saw_branch_not_taken = b(s2.ghist.new_saw_branch_not_taken);
    M.s2_ghist_new_saw_branch_taken = b(s2.ghist.new_saw_branch_taken);
    M.s2_ghist_ras_idx = s2.ghist.ras_idx & 0x1fu;
    M.s2_tlb_miss = b(s2.tlb_miss);
    M.s2_tlb_resp_ae_inst = b(s2.tlb.xcpt_ae_if);
    M.s2_tlb_resp_pf_inst = b(s2.tlb.xcpt_pf_if);
    M.s2_valid = b(s2.valid);
    // ---- F3 queues / assembler / F4 / FetchBuffer / RAS ----
    M.f3_ram_data = f3_queues_.main_payload().data;
    M.f3_ram_ghist_old_history = f3_queues_.main_payload().ghist.old_history;
    M.f3_ram_pc = f3_queues_.main_payload().pc & kPcMask40;
    M.f3_bpd_resp_ram_preds_3_predicted_pc_bits = f3_queues_.bpd_payload().preds[3].predicted_pc & kPcMask40;
    M.REG_5 = b(f3_queues_.previous_main_enq_ready());
    M.f3_maybe_full = b(f3_queues_.main_full());
    M.f3_bpd_resp_maybe_full = b(f3_queues_.bpd_full());
    M.ras_REG_1 = ras_.write_addr_reg() & kPcMask40;
    M.ras_REG_2 = ras_.read_data_reg() & kPcMask40;
    M.ras_REG = b(ras_.bypass_reg());
    M.f3_prev_half = f3_assembler_.prev_half();
    M.f3_prev_is_half = b(f3_assembler_.prev_is_half());
    M.f4_maybe_full = b(f4_queue_.full());
    M.fb_head = fetch_buffer_.head();
    M.fb_maybe_full = b(fetch_buffer_.maybe_full());
    M.fb_tail = fetch_buffer_.tail();
  }
  // ---- FTQ ----
  {
    auto& F = I_.r.frontendFtq;
    auto& FC = I_.c.frontendFtq;
    const auto& rp = ftq_.redirect_entry_pipeline();
    F.REG_16_ras_top = rp.ras_top & kPcMask40;
    F.REG_18 = ftq_.registered_get_pc(0).pc & kPcMask40;
    F.bpd_pc = ftq_.bpd_pc() & kPcMask40;
    F.bpd_repair_pc = ftq_.repair_pc() & kPcMask40;
    FC.ghist_0_old_history_bpd_ghist = ftq_.oracle_ghist0().old_history;
    FC.ghist_1_old_history_MPORT_3 = ftq_.oracle_getpc1_ghist().old_history;
    F.REG_16_cfi_idx_bits = rp.cfi_idx & 3u;
    F.REG_16_cfi_idx_valid = b(rp.cfi_valid);
    F.REG_16_cfi_is_call = b(rp.cfi_is_call);
    F.REG_16_cfi_is_ret = b(rp.cfi_is_ret);
    F.REG_16_cfi_mispredicted = b(rp.cfi_mispredicted);
    F.REG_16_cfi_taken = b(rp.cfi_taken);
    F.REG_16_cfi_type = rp.cfi_type & 7u;
    F.REG_16_ras_idx = rp.ras_idx & 0x1fu;
    F.REG_16_start_bank = b(rp.start_bank);
    F.REG_8 = b(ftq_.oracle_do_commit());
    F.REG_9 = b(ftq_.bpdupdate_pipe_repair());
    F.bpd_entry_br_mask = ftq_.bpd_entry().br_mask & 0x0fu;
    F.bpd_entry_cfi_idx_bits = ftq_.bpd_entry().cfi_idx & 3u;
    F.bpd_entry_cfi_idx_valid = b(ftq_.bpd_entry().cfi_valid);
    F.bpd_update_repair = b(ftq_.update_repair_flag());
    F.enq_ptr = ftq_.enq_idx() & 0x0fu;
    F.meta_0_bpd_meta_addr_pipe_0 = ftq_.oracle_ram_idx(0) & 0x0fu;
    F.prev_ghist_ras_idx = ftq_.previous_ghist().ras_idx & 0x1fu;
    FC.ghist_0_current_saw_branch_not_taken_bpd_ghist = b(ftq_.oracle_ghist0().current_saw_branch_not_taken);
    FC.ghist_0_ras_idx_bpd_ghist = ftq_.oracle_ghist0().ras_idx & 0x1fu;
    FC.ghist_1_current_saw_branch_not_taken_MPORT_3 = b(ftq_.oracle_getpc1_ghist().current_saw_branch_not_taken);
    FC.ghist_1_new_saw_branch_not_taken_MPORT_3 = b(ftq_.oracle_getpc1_ghist().new_saw_branch_not_taken);
    FC.ghist_1_new_saw_branch_taken_MPORT_3 = b(ftq_.oracle_getpc1_ghist().new_saw_branch_taken);
    FC.ghist_1_ras_idx_MPORT_3 = ftq_.oracle_getpc1_ghist().ras_idx & 0x1fu;
  }
  // ---- correction queue (arbiter input 1) ----
  {
    auto& R = I_.r.frontendF4Corr;
    R.deq_ptr_value = bpd_update_path_.deq_ptr() & 1u;
    R.enq_ptr_value = bpd_update_path_.enq_ptr() & 1u;
    R.maybe_full = b(bpd_update_path_.maybe_full());
    if (bpd_update_path_.version() != corr_ver_) {
      corr_ver_ = bpd_update_path_.version();
      auto& C = I_.c.frontendF4Corr;
      const auto& p = bpd_update_path_.deq_payload();
      C.ram_ghist_old_history_io_deq_bits_MPORT = p.ghist.old_history;
      C.ram_pc_io_deq_bits_MPORT = p.pc & kPcMask40;
      C.ram_target_io_deq_bits_MPORT = p.target & kPcMask40;
      C.ram_br_mask_io_deq_bits_MPORT = p.br_mask & 0x0fu;
      C.ram_btb_mispredicts_io_deq_bits_MPORT = p.btb_mispredicts & 0x0fu;
      C.ram_cfi_idx_bits_io_deq_bits_MPORT = p.cfi_idx & 3u;
      C.ram_cfi_idx_valid_io_deq_bits_MPORT = b(p.cfi_valid);
      C.ram_cfi_is_br_io_deq_bits_MPORT = b(p.cfi_is_br);
      C.ram_cfi_is_jal_io_deq_bits_MPORT = b(p.cfi_is_jal);
      C.ram_cfi_mispredicted_io_deq_bits_MPORT = b(p.cfi_mispredicted);
      C.ram_cfi_taken_io_deq_bits_MPORT = b(p.cfi_taken);
      C.ram_is_mispredict_update_io_deq_bits_MPORT = b(p.is_mispredict_update);
      C.ram_is_repair_update_io_deq_bits_MPORT = b(p.is_repair_update);
    }
  }
  // ---- I-cache ----
  {
    auto& R = I_.r.frontendIcache;
    R.refill_paddr = icache_.refill_paddr();
    R.prng_state_0 = icache_.lfsr() & 1u;
    R.refill_valid = b(icache_.refill_valid());
    R.s2_hit = b(icache_.s2_hit());
    R.s2_valid = b(icache_.s2_valid());
    {
      // The data port shows the word at the held read row (its parity
      // selects the bank); the row moves with every accepted request.
      auto& C = I_.c.frontendIcache;
      C.dataArrayWay_0_MPORT_2 = icache_.data(0, icache_.data_read_row(0));
      C.dataArrayWay_1_MPORT_4 = icache_.data(1, icache_.data_read_row(1));
      C.dataArrayWay_2_MPORT_6 = icache_.data(2, icache_.data_read_row(2));
      C.dataArrayWay_3_MPORT_8 = icache_.data(3, icache_.data_read_row(3));
      for (std::size_t w = 0; w < 4; ++w)
        C.tag_array_tag_rdata[w] = icache_.tag(w, icache_.tag_read_set()) & 0xfffffu;
    }
  }
  write_itlb_lanes();
}

}  // namespace chisa::boom_system
