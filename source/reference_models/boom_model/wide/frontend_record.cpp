#include "frontend.h"
#include "record_fields.h"
#include "../common/diagnostic_monitor.h"
namespace chisa::boom_model::wide {
namespace {
template<class A> std::uint64_t meta_word(const A& a, unsigned word) { return std::uint64_t(a[word*2]) | (std::uint64_t(a[word*2+1])<<32); }
// composer.scala:39-44 hands each predictor component the update metadata
// right-shifted by the total metadata width of the components after it, so
// every component reads its own slice from bit 0, and its register keeps the
// whole shifted remainder. These are the same shifts PredictorBank uses in
// update_metadata; test_frontend checks the two against each other.
inline constexpr unsigned kComponentMetaShift[5] = {73, 17, 16, 8, 0};
inline std::uint64_t component_meta_word(unsigned __int128 packed, unsigned component, unsigned word) {
  const unsigned shift = kComponentMetaShift[component] + word * 64u;
  return shift >= 128u ? 0 : static_cast<std::uint64_t>(packed >> shift);
}
template<class A> unsigned __int128 meta_pair(const A& a, unsigned bank) { return static_cast<unsigned __int128>(meta_word(a,bank*2+1))<<64 | meta_word(a,bank*2); }
}
void FrontendState::write_record_lanes(const FrontendEvaluation& out) {
  auto& I = record_;
  // FetchTargetQueue REG_12 is the registered enq.ready in both wide
  // configurations (fetch-target-queue.scala:308).
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendFtq.REG_12=ftq_.enq_ready();
#elif CHISA_FRONTEND_EXTRA_CUT
  write_record(I,fields::ftq_enq_ready_r,ftq_.enq_ready());
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_8_bits=banks_[0].btb_registered_f3(0).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_1_predicted_pc_bits=banks_[0].fa_registered_f3(0).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_8_valid=banks_[0].btb_registered_f3(0).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_1_predicted_pc_valid=banks_[0].fa_registered_f3(0).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_20_bits=banks_[0].btb_registered_f3(1).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_3_predicted_pc_bits=banks_[0].fa_registered_f3(1).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_20_valid=banks_[0].btb_registered_f3(1).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_3_predicted_pc_valid=banks_[0].fa_registered_f3(1).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_32_bits=banks_[0].btb_registered_f3(2).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_5_predicted_pc_bits=banks_[0].fa_registered_f3(2).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_32_valid=banks_[0].btb_registered_f3(2).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_5_predicted_pc_valid=banks_[0].fa_registered_f3(2).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_44_bits=banks_[0].btb_registered_f3(3).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_7_predicted_pc_bits=banks_[0].fa_registered_f3(3).predicted_pc;
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_44_valid=banks_[0].btb_registered_f3(3).predicted_pc_valid;
  I.r.frontendBpd.extra.banked_predictors_0_components_3_REG_7_predicted_pc_valid=banks_[0].fa_registered_f3(3).predicted_pc_valid;
  I.r.frontendF4Corr.deq_ptr_value=updates_.deq_ptr();
  I.r.frontendFtq.REG_8=ftq_.bpdupdate_pipe_valid();
  I.r.frontendFtq.REG_9=ftq_.bpdupdate_pipe_repair();
  I.r.frontendFtq.bpd_repair_pc=ftq_.repair_pc();
  I.r.frontendFtq.REG_16_cfi_idx_bits=ftq_.redirect_entry_pipeline().cfi_idx;
  I.r.frontendFtq.REG_16_cfi_idx_valid=ftq_.redirect_entry_pipeline().cfi_valid;
  I.r.frontendFtq.REG_16_cfi_is_call=ftq_.redirect_entry_pipeline().cfi_is_call;
  I.r.frontendFtq.REG_16_cfi_is_ret=ftq_.redirect_entry_pipeline().cfi_is_ret;
  I.r.frontendFtq.REG_16_cfi_mispredicted=ftq_.redirect_entry_pipeline().cfi_mispredicted;
  I.r.frontendFtq.REG_16_cfi_taken=ftq_.redirect_entry_pipeline().cfi_taken;
  I.r.frontendFtq.REG_16_cfi_type=ftq_.redirect_entry_pipeline().cfi_type;
  I.r.frontendFtq.REG_16_ras_idx=ftq_.redirect_entry_pipeline().ras_idx;
  I.r.frontendFtq.REG_16_ras_top=ftq_.redirect_entry_pipeline().ras_top;
  I.r.frontendFtq.REG_16_start_bank=ftq_.redirect_entry_pipeline().start_bank;
  I.r.frontendFtq.bpd_entry_br_mask=ftq_.bpd_entry().br_mask;
  I.r.frontendFtq.bpd_entry_cfi_idx_bits=ftq_.bpd_entry().cfi_idx;
  I.r.frontendFtq.bpd_entry_cfi_idx_valid=ftq_.bpd_entry().cfi_valid;
  for (unsigned port=0;port<4;++port) I.c.frontendFtq.state_ram_r[port]=ftq_.oracle_ram_read(port);
  I.c.frontendIcache.dataArrayWay_0_MPORT_2=icache_.data(0,icache_.data_read_row(0));
  I.c.frontendIcache.dataArrayWay_1_MPORT_4=icache_.data(1,icache_.data_read_row(1));
  I.c.frontendIcache.dataArrayWay_2_MPORT_6=icache_.data(2,icache_.data_read_row(2));
  I.c.frontendIcache.dataArrayWay_3_MPORT_8=icache_.data(3,icache_.data_read_row(3));
#endif
  const auto& history = out.f0_f2.output.bpd_f0_ghist;
  const bool shift = history.new_saw_branch_taken || history.new_saw_branch_not_taken;
  const auto history_next = shift ? (history.old_history<<1)|history.new_saw_branch_taken : history.old_history;
  const bool history_high = shift && (history.old_history>>63);
  { // f3_queues
  I.r.frontendMisc.REG_5 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(queues_.previous_main_enq_ready() ? 1u : 0u) & UINT64_C(0x1));
  I.r.frontendMisc.f3_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(queues_.main_full()) & UINT64_C(0x1));
  I.r.frontendMisc.f3_bpd_resp_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(queues_.bpd_full()) & UINT64_C(0x1));
  }
  { // f3_assembler
  I.r.frontendMisc.f3_prev_half = static_cast<std::uint16_t>(static_cast<std::uint64_t>(f3_assembler_for_diagnostic().prev_half()) & UINT64_C(0xffff));
  I.r.frontendMisc.f3_prev_is_half = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f3_assembler_for_diagnostic().prev_is_half()) & UINT64_C(0x1));
  }
  { // f4_queue
  I.r.frontendMisc.f4_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f4_queue_for_diagnostic().full()) & UINT64_C(0x1));
  }
  if (corr_epoch_ != updates_.version()) { // bpd_update_path
    corr_epoch_ = updates_.version();
  I.r.frontendF4Corr.enq_ptr_value = static_cast<std::uint8_t>(static_cast<std::uint64_t>(bpd_update_path_for_diagnostic().enq_ptr()) & UINT64_C(0x1));
  I.r.frontendF4Corr.maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(bpd_update_path_for_diagnostic().maybe_full()) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_cfi_idx_valid_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_valid) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_cfi_is_br_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_is_br) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_cfi_is_jal_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_is_jal) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_cfi_mispredicted_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_mispredicted) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_cfi_taken_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_taken) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_ghist_old_history_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(updates_.deq_payload().ghist.old_history));
  I.c.frontendF4Corr.ram_is_mispredict_update_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().is_mispredict_update) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_is_repair_update_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().is_repair_update) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_pc_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(bpd_update_path_for_diagnostic().payload(bpd_update_path_for_diagnostic().deq_ptr()).pc) & UINT64_C(0xffffffffff));
  I.c.frontendF4Corr.ram_target_io_deq_bits_MPORT = static_cast<std::uint64_t>(static_cast<std::uint64_t>(updates_.deq_payload().target) & UINT64_C(0xffffffffff));
  I.c.frontendF4Corr.ram_br_mask_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().br_mask) & UINT64_C(0xff));
  I.c.frontendF4Corr.ram_btb_mispredicts_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().btb_mispredicts) & UINT64_C(0xff));
  I.c.frontendF4Corr.ram_cfi_idx_bits_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().cfi_idx) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.c.frontendF4Corr.ram_ghist_new_saw_branch_not_taken_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().ghist.new_saw_branch_not_taken) & UINT64_C(0x1));
  I.c.frontendF4Corr.ram_ghist_new_saw_branch_taken_io_deq_bits_MPORT = static_cast<std::uint8_t>(static_cast<std::uint64_t>(updates_.deq_payload().ghist.new_saw_branch_taken) & UINT64_C(0x1));
#endif
  }
  { // fetch_buffer
  I.r.frontendMisc.fb_head = static_cast<std::uint8_t>(static_cast<std::uint64_t>(fetch_buffer_for_diagnostic().head()) & UINT64_C(0xff));
  I.r.frontendMisc.fb_maybe_full = static_cast<std::uint8_t>(static_cast<std::uint64_t>(fetch_buffer_for_diagnostic().maybe_full() ? 1 : 0) & UINT64_C(0x1));
  I.r.frontendMisc.fb_tail = static_cast<std::uint32_t>(static_cast<std::uint64_t>(fetch_buffer_.tail()) & UINT64_C(0xffffff));
  }
  { // ftq
  I.r.frontendFtq.REG_18 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().registered_get_pc(0).pc & ((UINT64_C(1) << 40) - 1)) & UINT64_C(0xffffffffff));
  I.r.frontendFtq.bpd_pc = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().bpd_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendFtq.bpd_update_repair = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().update_repair_flag()) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendFtq.prev_ghist_ras_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(ftq_for_diagnostic().previous_ghist().ras_idx) & UINT64_C(0x1f)) & UINT64_C(0x1f));
#endif
  I.c.frontendFtq.ghist_0_current_saw_branch_not_taken_bpd_ghist = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().oracle_ghist0().current_saw_branch_not_taken) & UINT64_C(0x1));
  I.c.frontendFtq.ghist_0_old_history_bpd_ghist = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().oracle_ghist0().old_history));
  I.c.frontendFtq.ghist_0_ras_idx_bpd_ghist = static_cast<std::uint8_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(ftq_for_diagnostic().oracle_ghist0().ras_idx) & UINT64_C(0x1f)) & UINT64_C(0x1f));
  I.c.frontendFtq.ghist_1_current_saw_branch_not_taken_MPORT_3 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().oracle_getpc1_ghist().current_saw_branch_not_taken) & UINT64_C(0x1));
  I.c.frontendFtq.ghist_1_new_saw_branch_not_taken_MPORT_3 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(ftq_for_diagnostic().oracle_getpc1_ghist().new_saw_branch_not_taken) & UINT64_C(0x1)) & UINT64_C(0x1));
  I.c.frontendFtq.ghist_1_new_saw_branch_taken_MPORT_3 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(ftq_for_diagnostic().oracle_getpc1_ghist().new_saw_branch_taken) & UINT64_C(0x1)) & UINT64_C(0x1));
  I.c.frontendFtq.ghist_1_old_history_MPORT_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_for_diagnostic().oracle_getpc1_ghist().old_history));
  I.c.frontendFtq.ghist_1_ras_idx_MPORT_3 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(ftq_for_diagnostic().oracle_getpc1_ghist().ras_idx) & UINT64_C(0x1f)) & UINT64_C(0x1f));
  I.r.frontendFtq.REG_23 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_.registered_get_pc(1).pc) & UINT64_C(0xffffffffff));
  I.r.frontendFtq.enq_ptr = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_.enq_idx()) & UINT64_C(0x1f));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendFtq.prev_ghist_old_history = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ftq_.previous_ghist().old_history));
  I.c.frontendFtq.ghist_0_new_saw_branch_not_taken_bpd_ghist = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_.oracle_ghist0().new_saw_branch_not_taken) & UINT64_C(0x1));
  I.c.frontendFtq.ghist_0_new_saw_branch_taken_bpd_ghist = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ftq_.oracle_ghist0().new_saw_branch_taken) & UINT64_C(0x1));
#endif
  }
  { // icache
  I.r.frontendIcache.prng_state_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>((icache_for_diagnostic().lfsr() & 1u)) & UINT64_C(0x1));
  I.r.frontendIcache.refill_paddr = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_for_diagnostic().refill_paddr()) & UINT64_C(0xffffffff));
  I.r.frontendIcache.refill_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(icache_for_diagnostic().refill_valid()) & UINT64_C(0x1));
  I.r.frontendIcache.s2_hit = static_cast<std::uint8_t>(static_cast<std::uint64_t>(icache_for_diagnostic().s2_hit() ? 1 : 0) & UINT64_C(0x1));
  I.r.frontendIcache.s2_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(icache_for_diagnostic().s2_valid() ? 1 : 0) & UINT64_C(0x1));
  if (cut_lanes_) {
#if CHISA_FRONTEND_EXTRA_CUT
    // Additional cuts retain these already committed pipeline values.
    // Keep publication beside the corresponding frontend edge, with no
    // extra sampling pass or duplicate predictor state.
    for (unsigned s=0;s<2;++s) write_record(I,fields::bpd_pc_tail[s],predictor_pc_[s+1]);
    write_record(I,fields::fe_previous_reset,f0_f2_.previous_reset());
    write_record(I,fields::fe_replay_ae,f0_f2_.replay_tlb().xcpt_ae_if);
    write_record(I,fields::fe_replay_pf,f0_f2_.replay_tlb().xcpt_pf_if);
    for (unsigned b=0;b<boomcfg::NBANKS;++b) {
      write_record(I,fields::bpd_bim_f3_meta[b],banks_[b].bim_registered_meta());
      write_record(I,fields::bpd_bim_s2_valid[b],banks_[b].bim_read_valid());
      for (unsigned s=0;s<4;++s) {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
        const auto& btb=banks_[b].btb_registered_f3(s);
        const auto& fa=banks_[b].fa_registered_f3(s);
        write_record(I,fields::bpd_btb_f3_pc_bits[b][s],btb.predicted_pc);
        write_record(I,fields::bpd_btb_f3_pc_valid[b][s],btb.predicted_pc_valid);
        write_record(I,fields::bpd_fa_f3_pc_bits[b][s],fa.predicted_pc);
        write_record(I,fields::bpd_fa_f3_pc_valid[b][s],fa.predicted_pc_valid);
#endif
        const auto& f2=banks_[b].fa_registered_f2(s);
        write_record(I,fields::bpd_fa_f2_is_br[b][s],f2.is_br);
        write_record(I,fields::bpd_fa_f2_is_jal[b][s],f2.is_jal);
      }
    }
#endif
    // tage.scala/bim.scala/loop.scala: table reset counters and the loop
    // predictor's f4 entry confidence, per bank.
    for (unsigned b = 0; b < boomcfg::NBANKS; ++b) {
      for (unsigned t = 0; t < 6; ++t) write_record(I, fields::bpd_tage_reset_idx[b][t], banks_[b].tage_reset_index(t));
      write_record(I, fields::bpd_bim_reset_idx[b], banks_[b].bim_reset_index());
      for (unsigned c = 0; c < 4; ++c) write_record(I, fields::bpd_loop_f4_conf[b][c], banks_[b].loop_f4_conf(c));
    }
    write_record(I, fields::icache_refill_valid_r, icache_for_diagnostic().delayed_refill_valid());   // icache.scala:165
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_s1_is_replay_r, f0_f2_for_diagnostic().s2().replay_reg);   // frontend.scala:450
    // fetch-target-queue.scala:353-359, read port 0.
    const auto& p0 = ftq_.registered_get_pc(0);
    write_record(I, fields::ftq_port0_pc_r, p0.pc);
    write_record(I, fields::ftq_port0_next_valid_r, p0.next_valid);
    write_record(I, fields::ftq_port0_com_pc_r, p0.commit_pc);
    write_record(I, fields::ftq_port0_entry_cfi_valid_r, p0.entry.cfi_valid);
    write_record(I, fields::ftq_port0_entry_cfi_bits_r, p0.entry.cfi_idx);
    write_record(I, fields::ftq_port0_entry_start_bank_r, p0.entry.start_bank);
#endif
  }
  }
  { // ras
  I.r.frontendMisc.ras_REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(ras_for_diagnostic().bypass_reg()) & UINT64_C(0x1));
  I.r.frontendMisc.ras_REG_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ras_for_diagnostic().write_addr_reg()) & UINT64_C(0xffffffffff));
  I.r.frontendMisc.ras_REG_2 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(ras_for_diagnostic().read_data_reg()) & UINT64_C(0xffffffffff));
  }
  { // f0_f2
  I.r.frontendMisc.s1_ghist_new_saw_branch_not_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().ghist.new_saw_branch_not_taken) & UINT64_C(0x1));
  I.r.frontendMisc.s1_ghist_new_saw_branch_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().ghist.new_saw_branch_taken) & UINT64_C(0x1));
  I.r.frontendMisc.s1_ghist_old_history = static_cast<std::uint64_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().ghist.old_history));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendMisc.s1_ghist_ras_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().ghist.ras_idx) & UINT64_C(0x1f));
#endif
  I.r.frontendMisc.s1_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().valid ? 1 : 0) & UINT64_C(0x1));
  I.r.frontendMisc.s1_vpc = static_cast<std::uint64_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s1().vpc) & UINT64_C(0xffffffffff));
  I.r.frontendMisc.s2_ghist_current_saw_branch_not_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ghist.current_saw_branch_not_taken) & UINT64_C(0x1));
  I.r.frontendMisc.s2_ghist_new_saw_branch_not_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ghist.new_saw_branch_not_taken) & UINT64_C(0x1));
  I.r.frontendMisc.s2_ghist_new_saw_branch_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ghist.new_saw_branch_taken) & UINT64_C(0x1));
  I.r.frontendMisc.s2_ghist_old_history = static_cast<std::uint64_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ghist.old_history));
  I.r.frontendMisc.s2_ghist_ras_idx = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ghist.ras_idx) & UINT64_C(0x1f));
  I.r.frontendMisc.s2_ppc = static_cast<std::uint32_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().ppc) & UINT64_C(0xffffffff));
  I.r.frontendMisc.s2_tlb_miss = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().tlb_miss) & UINT64_C(0x1));
  I.r.frontendMisc.s2_tlb_resp_ae_inst = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().tlb.xcpt_ae_if ? 1u : 0u) & UINT64_C(0x1));
  I.r.frontendMisc.s2_tlb_resp_pf_inst = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().tlb.xcpt_pf_if) & UINT64_C(0x1));
  I.r.frontendMisc.s2_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_for_diagnostic().s2().valid) & UINT64_C(0x1));
  I.r.frontendMisc.s1_is_replay = static_cast<std::uint8_t>(static_cast<std::uint64_t>(f0_f2_.s1().is_replay) & UINT64_C(0x1));
  }
  { // itlb
  I.r.frontendTlb.r_refill_tag = static_cast<std::uint32_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().refill_tag()) & UINT64_C(0x7ffffff));
  I.r.frontendTlb.r_sectored_hit = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_hit()) & UINT64_C(0x1));
  I.r.frontendTlb.r_sectored_hit_addr = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_hit_address()) & UINT64_C(0x7));
  I.r.frontendTlb.r_sectored_repl_addr = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_replacement_address()) & UINT64_C(0x7));
  I.r.frontendTlb.r_superpage_repl_addr = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().superpage_replacement_address()) & UINT64_C(0x3));
  I.r.frontendTlb.state = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().state()) & UINT64_C(0x3));
  }
  { // bpd_top
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  // The one-bank predictor registers the current F0 64-bit history.
  // Large uses this generated name for its first-bank selector instead.
  I.r.frontendBpd.extra.REG = history.old_history;
#else
  I.r.frontendBpd.extra.REG = static_cast<std::uint8_t>(!boomcfg::fetch_bank_one(out.f0_f2.output.icache_req_addr));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.REG_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(history.old_history));
  I.r.frontendBpd.extra.REG_11 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(out.f0_f2.output.icache_req_addr) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.REG_2_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(history_next));
  I.r.frontendBpd.extra.REG_2_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(history_high) & UINT64_C(0x1));
  I.r.frontendBpd.extra.REG_3_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(history_next));
  I.r.frontendBpd.extra.REG_3_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(history_high) & UINT64_C(0x1));
  I.r.frontendBpd.extra.REG_4 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(history.old_history));
  I.r.frontendBpd.extra.REG_5 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(out.bank_input[0].f0_valid) & UINT64_C(0x1));
  I.r.frontendBpd.extra.REG_8 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(out.bank_input[1].f0_valid) & UINT64_C(0x1));
#endif
  }
  { // bpd_control
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_entry_age[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_age(0)) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_fire[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_fire(0)) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_entry_age[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_age(1)) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_fire[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_fire(1)) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_entry_age[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_age(2)) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_fire[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_fire(2)) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_entry_age[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_age(3)) & UINT64_C(0x7));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_0_columns_f4_fire[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].loop_f4_fire(3)) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].update_valid()) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
#else
  I.r.frontendBpd.extra.banked_predictors_components_1_REG[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_10 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_11 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_4 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_5 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_6 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_7 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_8 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_REG_9 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].request_pc()) & UINT64_C(0xffffffffff));
  // Partition-cut lanes may read any bit of the TAGE allocation LFSRs; bit 0 is
  // written by the bank itself, the rest go by bit address (no-ops when absent).
  for (unsigned k=0;k<4;++k) { const unsigned s=banks_[0].random_state(k); for (unsigned bit=1;bit<6;++bit) write_record(I, fields::bpd_prng_state[0][k][bit], (s>>bit)&1u); }
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_11 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_force_delay(0)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_18 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_override_delay(1)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_23 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_force_delay(1)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_30 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_override_delay(2)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_35 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_force_delay(2)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_42 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_override_delay(3)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_47 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_force_delay(3)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_REG_6 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_override_delay(0)) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_components_2_REG_write_way[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].btb_write_way_register()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].update_valid()) & UINT64_C(0x1));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
#else
  I.r.frontendBpd.extra.banked_predictors_components_2_s1_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].request_valid()) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].update_valid()) & UINT64_C(0x1));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_valid[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_entry_age[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_age(0)) & UINT64_C(0x7));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_fire[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_fire(0)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_entry_age[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_age(1)) & UINT64_C(0x7));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_fire[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_fire(1)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_entry_age[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_age(2)) & UINT64_C(0x7));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_fire[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_fire(2)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_entry_age[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_age(3)) & UINT64_C(0x7));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_columns_f4_fire[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].loop_f4_fire(3)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_1_REG[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_10 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_11 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_2 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_4 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_5 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_6 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_7 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_8 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_REG_9 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].request_pc()) & UINT64_C(0xffffffffff));
  for (unsigned k=0;k<4;++k) { const unsigned s=banks_[1].random_state(k); for (unsigned bit=1;bit<6;++bit) write_record(I, fields::bpd_prng_state[1][k][bit], (s>>bit)&1u); }
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_11 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_force_delay(0)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_18 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_override_delay(1)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_23 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_force_delay(1)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_30 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_override_delay(2)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_35 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_force_delay(2)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_42 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_override_delay(3)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_47 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_force_delay(3)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_REG_6 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_override_delay(0)) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_2_REG_write_way[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].btb_write_way_register()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_2_s1_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].request_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].update_valid()) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_valid[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].update_valid()) & UINT64_C(0x1));
#endif
  }
  if (out.bank_input[0].update_valid || out.reset) { // bpd_update_0
    const auto packed_meta_0 = meta_pair(banks_[0].registered_update().meta,0);
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_is_mispredict_update[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().is_mispredict_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_0_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,0,0));
  I.r.frontendBpd.extra.banked_predictors_0_components_0_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,0,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,1,0));
  I.r.frontendBpd.extra.banked_predictors_0_components_1_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,1,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_pc[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].registered_update().pc) & UINT64_C(0xffffffffff));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_br_mask = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().br_mask) & UINT64_C(0xf));
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_br_mask[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().br_mask) & UINT64_C(0xf));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_btb_mispredicts = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().btb_mispredicts) & UINT64_C(0xf));
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_btb_mispredicts[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().btb_mispredicts) & UINT64_C(0xf));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_cfi_idx_bits = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_idx) & UINT64_C(0x3));
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_idx_bits[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_idx) & UINT64_C(0x3));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_cfi_idx_valid = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_valid) & UINT64_C(0x1));
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_idx_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_valid) & UINT64_C(0x1));
#endif
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_cfi_taken = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_taken) & UINT64_C(0x1));
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_taken[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_taken) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_is_mispredict_update[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().is_mispredict_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_is_repair_update[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().is_repair_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,2,0));
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,2,1) & UINT64_C(0xffffffffffffff));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  // predictor.scala registers PC40 >> FETCH_IDX_SHIFT: 37 bits on
  // Medium's eight-byte fetch group, 36 bits on Large's sixteen bytes.
  I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_idx = banks_[0].update_index() & fe::kIdxMask;
#else
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_idx[2] = banks_[0].update_index() & fe::kIdxMask;
#endif
  CHISA_DIAG(
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    const auto published_index=I.r.frontendBpd.extra.banked_predictors_0_components_2_s1_update_idx;
#else
    const auto published_index=I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_idx[2];
#endif
    chisa::diagnostic::require("frontend", "btb-update-index-publication", chisa::diagnostic::cycle(),
        chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
        banks_[0].update_index() == published_index,
        {{"index", 0}, {"pc", banks_[0].registered_update().pc},
         {"native", banks_[0].update_index()}, {"published", published_index},
         {"index_width", fe::kIdxWidth}});
  );
  I.r.frontendBpd.extra.banked_predictors_0_components_3_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,3,0));
  I.r.frontendBpd.extra.banked_predictors_0_components_3_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,3,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_pc[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].registered_update().pc) & UINT64_C(0xffffffffff));
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_3_s1_update_bits_target = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].registered_update().target) & UINT64_C(0xffffffffff));
#else
  I.r.frontendBpd.extra.banked_predictors_components_3_s1_update_bits_target[0] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[0].registered_update().target) & UINT64_C(0xffffffffff));
#endif
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_br_mask[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().br_mask) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_btb_mispredicts[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().btb_mispredicts) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_idx_bits[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_idx) & UINT64_C(0x3));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_idx_valid[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_valid) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_4_s1_update_bits_cfi_is_br[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_is_br) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_4_s1_update_bits_cfi_is_jal[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_is_jal) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_cfi_taken[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().cfi_taken) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_is_mispredict_update[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().is_mispredict_update) & UINT64_C(0x1));
#endif
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_bits_is_repair_update[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[0].registered_update().is_repair_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_0_components_4_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,4,0));
  I.r.frontendBpd.extra.banked_predictors_0_components_4_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_0,4,1) & UINT64_C(0xffffffffffffff));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendBpd.extra.banked_predictors_0_components_s1_update_idx[4] = banks_[0].update_index() & fe::kIdxMask;
#endif
  }
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  if (out.bank_input[1].update_valid || out.reset) { // bpd_update_1
    const auto packed_meta_1 = meta_pair(banks_[1].registered_update().meta,0);
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_is_mispredict_update[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().is_mispredict_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,0,0));
  I.r.frontendBpd.extra.banked_predictors_1_components_0_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,0,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,1,0));
  I.r.frontendBpd.extra.banked_predictors_1_components_1_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,1,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_pc[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].registered_update().pc) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_br_mask[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().br_mask) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_btb_mispredicts[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().btb_mispredicts) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_idx_bits[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_idx) & UINT64_C(0x3));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_idx_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_valid) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_taken[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_taken) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_is_mispredict_update[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().is_mispredict_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_is_repair_update[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().is_repair_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,2,0));
  I.r.frontendBpd.extra.banked_predictors_1_components_2_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,2,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_idx[2] = banks_[1].update_index() & fe::kIdxMask;
  CHISA_DIAG(chisa::diagnostic::require("frontend", "btb-update-index-publication", chisa::diagnostic::cycle(),
      chisa::diagnostic::Layer::Publication, chisa::diagnostic::Phase::Post,
      banks_[1].update_index() == I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_idx[2],
      {{"index", 1}, {"pc", banks_[1].registered_update().pc},
       {"native", banks_[1].update_index()}, {"published", I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_idx[2]},
       {"index_width", fe::kIdxWidth}}));
  I.r.frontendBpd.extra.banked_predictors_1_components_3_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,3,0));
  I.r.frontendBpd.extra.banked_predictors_1_components_3_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,3,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_pc[3] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].registered_update().pc) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_components_3_s1_update_bits_target[1] = static_cast<std::uint64_t>(static_cast<std::uint64_t>(banks_[1].registered_update().target) & UINT64_C(0xffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_br_mask[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().br_mask) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_btb_mispredicts[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().btb_mispredicts) & UINT64_C(0xf));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_idx_bits[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_idx) & UINT64_C(0x3));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_idx_valid[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_valid) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_4_s1_update_bits_cfi_is_br[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_is_br) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_components_4_s1_update_bits_cfi_is_jal[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_is_jal) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_cfi_taken[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().cfi_taken) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_is_mispredict_update[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().is_mispredict_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_bits_is_repair_update[4] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(banks_[1].registered_update().is_repair_update) & UINT64_C(0x1));
  I.r.frontendBpd.extra.banked_predictors_1_components_4_s1_update_bits_meta[1] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,4,0));
  I.r.frontendBpd.extra.banked_predictors_1_components_4_s1_update_bits_meta[2] = static_cast<std::uint64_t>(component_meta_word(packed_meta_1,4,1) & UINT64_C(0xffffffffffffff));
  I.r.frontendBpd.extra.banked_predictors_1_components_s1_update_idx[4] = banks_[1].update_index() & fe::kIdxMask;
  }
#endif
  if (icache_epoch_ != icache_.oracle_read_epoch_for_diagnostic()) { // icache_ports
    icache_epoch_ = icache_.oracle_read_epoch_for_diagnostic();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.c.frontendIcache.dataArrayB0Way_0_lo_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(0)));
  I.c.frontendIcache.dataArrayB0Way_1_lo_2 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(1)));
  I.c.frontendIcache.dataArrayB0Way_2_lo_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(2)));
  I.c.frontendIcache.dataArrayB0Way_3_lo_4 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(3)));
  I.c.frontendIcache.dataArrayB0Way_4_lo_5 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(4)));
  I.c.frontendIcache.dataArrayB0Way_5_lo_6 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(5)));
  I.c.frontendIcache.dataArrayB0Way_6_lo_7 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(6)));
  I.c.frontendIcache.dataArrayB0Way_7_lo_8 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank0_read_for_diagnostic(7)));
  I.c.frontendIcache.dataArrayB1Way_0_hi_1 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(0)));
  I.c.frontendIcache.dataArrayB1Way_1_hi_2 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(1)));
  I.c.frontendIcache.dataArrayB1Way_2_hi_3 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(2)));
  I.c.frontendIcache.dataArrayB1Way_3_hi_4 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(3)));
  I.c.frontendIcache.dataArrayB1Way_4_hi_5 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(4)));
  I.c.frontendIcache.dataArrayB1Way_5_hi_6 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(5)));
  I.c.frontendIcache.dataArrayB1Way_6_hi_7 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(6)));
  I.c.frontendIcache.dataArrayB1Way_7_hi_8 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(icache_.oracle_bank1_read_for_diagnostic(7)));
  I.c.frontendIcache.tag_array_tag_rdata[4] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_.oracle_tag_read_for_diagnostic(4)) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[5] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_.oracle_tag_read_for_diagnostic(5)) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[6] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_.oracle_tag_read_for_diagnostic(6)) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[7] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_.oracle_tag_read_for_diagnostic(7)) & UINT64_C(0xfffff));
#endif
  I.c.frontendIcache.tag_array_tag_rdata[0] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(static_cast<uint64_t>(icache_for_diagnostic().tag(0, icache_for_diagnostic().tag_read_set())) & UINT64_C(0xfffff)) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[1] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_for_diagnostic().tag(1, icache_for_diagnostic().tag_read_set())) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[2] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_for_diagnostic().tag(2, icache_for_diagnostic().tag_read_set())) & UINT64_C(0xfffff));
  I.c.frontendIcache.tag_array_tag_rdata[3] = static_cast<std::uint32_t>(static_cast<std::uint64_t>(icache_for_diagnostic().tag(3, icache_for_diagnostic().tag_read_set())) & UINT64_C(0xfffff));
  }
  if (itlb_epoch_ != itlb_.state_for_diagnostic().entries_epoch()) { // itlb_entries
    itlb_epoch_ = itlb_.state_for_diagnostic().entries_epoch();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  I.r.frontendTlb.sectored_entries_0_0_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(0).valid[0]) & UINT64_C(0x1));
#endif
  I.r.frontendTlb.sectored_entries_0_0_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(0).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_0_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(0).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_0_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(0).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_1_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(1).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_1_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(1).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_1_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(1).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_1_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(1).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_2_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(2).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_2_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(2).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_2_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(2).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_2_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(2).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_3_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(3).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_3_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(3).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_3_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(3).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_3_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(3).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_4_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(4).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_4_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(4).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_4_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(4).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_4_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(4).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_5_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(5).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_5_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(5).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_5_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(5).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_5_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(5).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_6_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(6).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_6_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(6).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_6_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(6).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_6_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(6).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_7_valid[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(7).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_7_valid[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(7).valid[1]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_7_valid[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(7).valid[2]) & UINT64_C(0x1));
  I.r.frontendTlb.sectored_entries_0_7_valid[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().sectored_entry(7).valid[3]) & UINT64_C(0x1));
  I.r.frontendTlb.special_entry_data_0 = static_cast<std::uint64_t>(static_cast<std::uint64_t>(components::SmallInstructionTlb::pack_entry_data( itlb_for_diagnostic().special_entry().data[0])) & UINT64_C(0x7ffffffff));
  I.r.frontendTlb.special_entry_valid_0 = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().special_entry().valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.superpage_entries_valid_0[0] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().superpage_entry(0).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.superpage_entries_valid_0[1] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().superpage_entry(1).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.superpage_entries_valid_0[2] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().superpage_entry(2).valid[0]) & UINT64_C(0x1));
  I.r.frontendTlb.superpage_entries_valid_0[3] = static_cast<std::uint8_t>(static_cast<std::uint64_t>(itlb_for_diagnostic().superpage_entry(3).valid[0]) & UINT64_C(0x1));
  }
  if (out.f0_f2.output.f3_enq_valid && out.main_enq_ready) { // f3_payload
    const auto& p = queues_.main_payload();
    // Medium has one 64-bit fetch bank; evaluating data_word(1) would
    // access its empty high-bank array even when the record uses 64 bits.
    if constexpr (boomcfg::NBANKS > 1)
      write_record(I, fields::fe_f3_ram_data, (static_cast<unsigned __int128>(p.data_word(1))<<64)|p.data_word(0));
    else
      write_record(I, fields::fe_f3_ram_data, p.data_word(0));
    write_record(I, fields::fe_f3_ram_ghist_current_saw_branch_not_taken, p.ghist.current_saw_branch_not_taken);
    write_record(I, fields::fe_f3_ram_ghist_new_saw_branch_not_taken, p.ghist.new_saw_branch_not_taken);
    write_record(I, fields::fe_f3_ram_ghist_new_saw_branch_taken, p.ghist.new_saw_branch_taken);
    write_record(I, fields::fe_f3_ram_ghist_old_history, p.ghist.old_history);
    write_record(I, fields::fe_f3_ram_ghist_ras_idx, p.ghist.ras_idx);
    write_record(I, fields::fe_f3_ram_mask, p.mask);
    write_record(I, fields::fe_f3_ram_pc, p.pc);
    write_record(I, fields::fe_f3_ram_xcpt_ae_inst, p.xcpt_ae_if);
    write_record(I, fields::fe_f3_ram_xcpt_pf_inst, p.xcpt_pf_if);
  }
  if (out.bpd_enq_valid && out.bpd_enq_ready) { // f3_bpd_resp_payload
    const auto& p = queues_.bpd_payload();
    write_record(I, fields::fe_f3_bpd_resp_ram_meta_0, meta_pair(p.meta, 0));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f3_bpd_resp_ram_meta_1, meta_pair(p.meta, 1));
#endif
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_0_predicted_pc_bits, p.preds[0].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_0_predicted_pc_valid, p.preds[0].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_0_taken, p.preds[0].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_1_predicted_pc_bits, p.preds[1].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_1_predicted_pc_valid, p.preds[1].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_1_taken, p.preds[1].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_2_predicted_pc_bits, p.preds[2].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_2_predicted_pc_valid, p.preds[2].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_2_taken, p.preds[2].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_3_predicted_pc_bits, p.preds[3].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_3_predicted_pc_valid, p.preds[3].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_3_taken, p.preds[3].taken);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_4_predicted_pc_bits, p.preds[4].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_4_predicted_pc_valid, p.preds[4].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_4_taken, p.preds[4].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_5_predicted_pc_bits, p.preds[5].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_5_predicted_pc_valid, p.preds[5].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_5_taken, p.preds[5].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_6_predicted_pc_bits, p.preds[6].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_6_predicted_pc_valid, p.preds[6].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_6_taken, p.preds[6].taken);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_7_predicted_pc_bits, p.preds[7].predicted_pc);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_7_predicted_pc_valid, p.preds[7].predicted_pc_valid);
    write_record(I, fields::fe_f3_bpd_resp_ram_preds_7_taken, p.preds[7].taken);
#endif
  }
  if (out.f4_enq_valid && out.f4_enq_ready) { // f4_payload
    const auto& p = f4_.payload();
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_0, (p.bp_debug_mask >> 0) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_1, (p.bp_debug_mask >> 1) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_2, (p.bp_debug_mask >> 2) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_3, (p.bp_debug_mask >> 3) & 1u);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_4, (p.bp_debug_mask >> 4) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_5, (p.bp_debug_mask >> 5) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_6, (p.bp_debug_mask >> 6) & 1u);
    write_record(I, fields::fe_f4_ram_bp_debug_if_oh_7, (p.bp_debug_mask >> 7) & 1u);
#endif
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_0, (p.bp_xcpt_mask >> 0) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_1, (p.bp_xcpt_mask >> 1) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_2, (p.bp_xcpt_mask >> 2) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_3, (p.bp_xcpt_mask >> 3) & 1u);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_4, (p.bp_xcpt_mask >> 4) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_5, (p.bp_xcpt_mask >> 5) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_6, (p.bp_xcpt_mask >> 6) & 1u);
    write_record(I, fields::fe_f4_ram_bp_xcpt_if_oh_7, (p.bp_xcpt_mask >> 7) & 1u);
#endif
    write_record(I, fields::fe_f4_ram_bpd_meta_0, meta_pair(p.bpd_meta, 0));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_bpd_meta_1, meta_pair(p.bpd_meta, 1));
#endif
    write_record(I, fields::fe_f4_ram_br_mask, p.br_mask);
    write_record(I, fields::fe_f4_ram_cfi_idx_bits, p.cfi_idx);
    write_record(I, fields::fe_f4_ram_cfi_idx_valid, p.cfi_valid);
    write_record(I, fields::fe_f4_ram_cfi_is_call, p.cfi_is_call);
    write_record(I, fields::fe_f4_ram_cfi_is_ret, p.cfi_is_ret);
    write_record(I, fields::fe_f4_ram_cfi_type, p.cfi_type);
    write_record(I, fields::fe_f4_ram_edge_inst_0, p.edge_insts[0]);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_edge_inst_1, p.edge_insts[1]);
#endif
    write_record(I, fields::fe_f4_ram_exp_insts_0, p.expanded_insts[0]);
    write_record(I, fields::fe_f4_ram_exp_insts_1, p.expanded_insts[1]);
    write_record(I, fields::fe_f4_ram_exp_insts_2, p.expanded_insts[2]);
    write_record(I, fields::fe_f4_ram_exp_insts_3, p.expanded_insts[3]);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_exp_insts_4, p.expanded_insts[4]);
    write_record(I, fields::fe_f4_ram_exp_insts_5, p.expanded_insts[5]);
    write_record(I, fields::fe_f4_ram_exp_insts_6, p.expanded_insts[6]);
    write_record(I, fields::fe_f4_ram_exp_insts_7, p.expanded_insts[7]);
#endif
    write_record(I, fields::fe_f4_ram_ghist_current_saw_branch_not_taken, p.ghist.current_saw_branch_not_taken);
    write_record(I, fields::fe_f4_ram_ghist_new_saw_branch_not_taken, p.ghist.new_saw_branch_not_taken);
    write_record(I, fields::fe_f4_ram_ghist_new_saw_branch_taken, p.ghist.new_saw_branch_taken);
    write_record(I, fields::fe_f4_ram_ghist_old_history, p.ghist.old_history);
    write_record(I, fields::fe_f4_ram_ghist_ras_idx, p.ghist.ras_idx);
    write_record(I, fields::fe_f4_ram_insts_0, p.insts[0]);
    write_record(I, fields::fe_f4_ram_insts_1, p.insts[1]);
    write_record(I, fields::fe_f4_ram_insts_2, p.insts[2]);
    write_record(I, fields::fe_f4_ram_insts_3, p.insts[3]);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_insts_4, p.insts[4]);
    write_record(I, fields::fe_f4_ram_insts_5, p.insts[5]);
    write_record(I, fields::fe_f4_ram_insts_6, p.insts[6]);
    write_record(I, fields::fe_f4_ram_insts_7, p.insts[7]);
#endif
    write_record(I, fields::fe_f4_ram_mask, p.mask);
    write_record(I, fields::fe_f4_ram_pc, p.pc);
    write_record(I, fields::fe_f4_ram_ras_top, p.ras_top);
    write_record(I, fields::fe_f4_ram_sfbs_0, (p.sfb_mask >> 0) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_1, (p.sfb_mask >> 1) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_2, (p.sfb_mask >> 2) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_3, (p.sfb_mask >> 3) & 1u);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_sfbs_4, (p.sfb_mask >> 4) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_5, (p.sfb_mask >> 5) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_6, (p.sfb_mask >> 6) & 1u);
    write_record(I, fields::fe_f4_ram_sfbs_7, (p.sfb_mask >> 7) & 1u);
#endif
    write_record(I, fields::fe_f4_ram_shadowed_mask_0, (p.shadowed_mask >> 0) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_1, (p.shadowed_mask >> 1) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_2, (p.shadowed_mask >> 2) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_3, (p.shadowed_mask >> 3) & 1u);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    write_record(I, fields::fe_f4_ram_shadowed_mask_4, (p.shadowed_mask >> 4) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_5, (p.shadowed_mask >> 5) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_6, (p.shadowed_mask >> 6) & 1u);
    write_record(I, fields::fe_f4_ram_shadowed_mask_7, (p.shadowed_mask >> 7) & 1u);
#endif
    write_record(I, fields::fe_f4_ram_xcpt_ae_if, p.xcpt_ae_if);
    write_record(I, fields::fe_f4_ram_xcpt_pf_if, p.xcpt_pf_if);
  }
  if (fb_epoch_ != fetch_buffer_.ram_epoch_for_diagnostic()) {
    fb_epoch_ = fetch_buffer_.ram_epoch_for_diagnostic();
    std::uint64_t* const words[boomcfg::NUM_FB_ENTRIES] = {
      &I.r.frontendMisc.fb_fb_uop_rambank_0_0, &I.r.frontendMisc.fb_fb_uop_rambank_1_0, &I.r.frontendMisc.fb_fb_uop_rambank_2_0, &I.r.frontendMisc.fb_fb_uop_rambank_3_0, &I.r.frontendMisc.fb_fb_uop_rambank_4_0, &I.r.frontendMisc.fb_fb_uop_rambank_5_0, &I.r.frontendMisc.fb_fb_uop_rambank_6_0, &I.r.frontendMisc.fb_fb_uop_rambank_7_0, &I.r.frontendMisc.fb_fb_uop_rambank_8_0, &I.r.frontendMisc.fb_fb_uop_rambank_9_0, &I.r.frontendMisc.fb_fb_uop_rambank_10_0, &I.r.frontendMisc.fb_fb_uop_rambank_11_0, &I.r.frontendMisc.fb_fb_uop_rambank_12_0, &I.r.frontendMisc.fb_fb_uop_rambank_13_0, &I.r.frontendMisc.fb_fb_uop_rambank_14_0, &I.r.frontendMisc.fb_fb_uop_rambank_15_0
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
      , &I.r.frontendMisc.fb_fb_uop_rambank_16_0, &I.r.frontendMisc.fb_fb_uop_rambank_17_0, &I.r.frontendMisc.fb_fb_uop_rambank_18_0, &I.r.frontendMisc.fb_fb_uop_rambank_19_0, &I.r.frontendMisc.fb_fb_uop_rambank_20_0, &I.r.frontendMisc.fb_fb_uop_rambank_21_0, &I.r.frontendMisc.fb_fb_uop_rambank_22_0, &I.r.frontendMisc.fb_fb_uop_rambank_23_0
#endif
    };
    for (unsigned row=0; row<boomcfg::NUM_FB_ENTRIES; ++row) {
      const auto epoch = fetch_buffer_.ram_entry_epoch_for_diagnostic(row);
      if (fb_row_epoch_[row] == epoch) continue;
      fb_row_epoch_[row] = epoch;
      *words[row] = fetch_buffer_.packed_ram(row);
    }
  }
  if (ftq_epoch_ != ftq_.entry_epoch_for_diagnostic()) {
    ftq_epoch_ = ftq_.entry_epoch_for_diagnostic();
    for (unsigned row=0; row<32; ++row) {
      const auto epoch = ftq_.entry_epoch_for_diagnostic(row);
      if (ftq_row_epoch_[row] == epoch) continue;
      ftq_row_epoch_[row] = epoch;
      const auto& p = ftq_.entry(row);
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
      write_record(I, fields::ftq_br_mask[row], p.br_mask);
      write_record(I, fields::ftq_cfi_idx_bits[row], p.cfi_idx);
      write_record(I, fields::ftq_cfi_idx_valid[row], p.cfi_valid);
      write_record(I, fields::ftq_cfi_is_call[row], p.cfi_is_call);
      write_record(I, fields::ftq_cfi_is_ret[row], p.cfi_is_ret);
      write_record(I, fields::ftq_cfi_mispredicted[row], p.cfi_mispredicted);
      write_record(I, fields::ftq_cfi_taken[row], p.cfi_taken);
      write_record(I, fields::ftq_cfi_type[row], p.cfi_type);
      write_record(I, fields::ftq_ras_idx[row], p.ras_idx);
      write_record(I, fields::ftq_ras_top[row], p.ras_top);
      write_record(I, fields::ftq_start_bank[row], p.start_bank);
#endif
    }
  }
}
}  // namespace chisa::boom_model::wide
