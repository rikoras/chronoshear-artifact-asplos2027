#include "frontend.h"
#include "../common/diagnostic_monitor.h"
#include <stdexcept>

namespace chisa::boom_model::wide {
namespace {
template<std::size_t... Bank>
auto predictor_banks(contract::Image& record, std::index_sequence<Bank...>) {
  return std::array<fe::PredictorBank,sizeof...(Bank)>{{
    fe::PredictorBank(record.r.frontendBpd.bank[Bank],record.c.frontendBpd.bank[Bank]
#if CHISA_PREDICTOR_TAIL_CUT
                     ,Bank,&record
#endif
                     )...}};
}
}
FrontendState::FrontendState()
    : record_(system_record()),
      banks_(predictor_banks(record_,std::make_index_sequence<boomcfg::NBANKS>{})) {
  static_assert(boomcfg::BANK_WIDTH==4);
}
HeldFetch FrontendState::held_fetch(bool reset) const {
  fetch_buffer_.outputs_into(reset,fetch_offer_);
  HeldFetch result;result.enq_ready=fetch_offer_.enq_ready;
  result.deq_valid=fetch_offer_.deq_valid;result.uop_valid=fetch_offer_.uop_valid;
  result.uop=&fetch_offer_.uops_g[0];
  for (unsigned lane=0;lane<boomcfg::CORE_WIDTH;++lane) {
    result.group[lane]=&fetch_offer_.uops_g[lane];
    if (fetch_offer_.uop_valids_g[lane]) result.group_valid |= 1u<<lane;
  }
  return result;
}
void FrontendState::held_itlb_cycle_inputs_into(const FrontendInputs& input,
                                               components::SmallTlbCycleInputs& output) const {
  output={};const auto& s1=f0_f2_.s1();
  output.reset=input.reset;
  output.request_valid=input.run && ((s1.valid && !s1.is_replay && !clear(input)) || s1.is_sfence);
  output.virtual_address=s1.vpc;output.vm_enabled=input.itlb_vm_enabled;
  output.privilege=input.itlb_privilege;output.dynamic_execute_permission=input.itlb_dynamic_execute_permission;
  output.ptw_request_ready=input.itlb_ptw_request_ready;output.refill=input.itlb_refill;output.sfence=sfence_;
}
void FrontendState::fill_handoff(FrontendHandoff& h) const {
  h.deq_valid=fetch_buffer_.dequeue_row_into(h.uops,h.uop_valids);
  // Decoded once per dequeue row, on the thread that committed the row;
  // decode reads only the instruction, and the edge patches its interrupt
  // and exception state on its own copy.
  for (unsigned w=0;w<boomcfg::CORE_WIDTH;++w)
    if (h.uop_valids&(1u<<w)) boom_decode_cached(h.uops[w]);
  for (unsigned port=0;port<2;++port) {
    const auto& g=ftq_ports_[port];auto& p=h.ftq[port];
    p.next_valid=g.next_valid;p.pc=g.pc;p.next_pc=g.next_pc;
    p.cfi_valid=g.entry.cfi_valid;p.cfi_idx=g.entry.cfi_idx;p.start_bank=g.entry.start_bank;
  }
  const auto& s1=f0_f2_.s1();
  h.s1.valid=s1.valid;h.s1.is_replay=s1.is_replay;h.s1.is_sfence=s1.is_sfence;h.s1.vpc=s1.vpc;
  h.sfence=sfence_;
  h.icache_acquire=held_icache_acquire();
}
void FrontendState::itlb_cycle_inputs_from(const FrontendHandoff& h,const FrontendInputs& input,
                                           components::SmallTlbCycleInputs& output) {
  output={};
  output.reset=input.reset;
  output.request_valid=input.run && ((h.s1.valid && !h.s1.is_replay && !clear(input)) || h.s1.is_sfence);
  output.virtual_address=h.s1.vpc;output.vm_enabled=input.itlb_vm_enabled;
  output.privilege=input.itlb_privilege;output.dynamic_execute_permission=input.itlb_dynamic_execute_permission;
  output.ptw_request_ready=input.itlb_ptw_request_ready;output.refill=input.itlb_refill;output.sfence=h.sfence;
}
void FrontendState::compose_predictions() {
  for (auto& bank : banks_) bank.evaluate();
  prediction_.pc=predictor_pc_[2];
  const unsigned first1=boomcfg::fetch_bank_one(predictor_pc_[0]);
  const unsigned first2=boomcfg::fetch_bank_one(predictor_pc_[1]);
  const unsigned first3=boomcfg::fetch_bank_one(predictor_pc_[2]);
  for (unsigned logical=0;logical<boomcfg::NBANKS;++logical) {
    for (unsigned slot=0;slot<4;++slot) {
      prediction_f1_.preds[logical*4+slot]=banks_[first1^logical].f1().preds[slot];
      prediction_f2_.preds[logical*4+slot]=banks_[first2^logical].f2().preds[slot];
      prediction_.preds[logical*4+slot]=banks_[first3^logical].f3_response().preds[slot];
    }
  }
  // Metadata stays in physical-bank order while the instruction/prediction
  // lanes rotate into fetch order. The FTQ preserves this distinction.
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank)
    for (unsigned word=0;word<4;++word) prediction_.meta[bank*4+word]=banks_[bank].f3_meta()[word];
}
void FrontendState::split_updates(FrontendEvaluation& out) {
  const auto& top=*out.update;
  const unsigned first=boomcfg::fetch_bank_one(top.pc);
  const unsigned request_first=boomcfg::fetch_bank_one(out.f0_f2.output.icache_req_addr);
  const unsigned history_first=boomcfg::fetch_bank_one(f0_f2_.s1().vpc);
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank) {
    const unsigned logical=bank^first;
    if constexpr (boomcfg::NBANKS>1) {
      auto& update=out.bank_update[bank];update=top;
      update.pc=logical ? boomcfg::fetch_next_bank(top.pc) : top.pc;
      update.br_mask=static_cast<std::uint8_t>((top.br_mask>>(4*logical))&15u);
      update.btb_mispredicts=static_cast<std::uint8_t>((top.btb_mispredicts>>(4*logical))&15u);
      update.cfi_valid=top.cfi_valid && (top.cfi_idx>>2)==logical;
      update.cfi_idx=top.cfi_idx&3u;
      update.ghist.old_history=top.ghist.history_word(logical);
      for (unsigned word=0;word<4;++word) update.meta[word]=top.meta[bank*4+word];
    }
    auto& in=out.bank_input[bank];in.reset=out.reset;
    const unsigned request_logical=bank^request_first;
    const auto pc=out.f0_f2.output.icache_req_addr;
    in.f0_pc=request_logical ? boomcfg::fetch_next_bank(pc) : pc;
    in.f0_valid=out.f0_f2.output.icache_req_valid &&
        (!request_logical || !boomcfg::fetch_may_not_be_dual_banked(pc));
    in.f1_ghist=f0_f2_.s1().ghist.history_word(bank^history_first);
    in.f3_fire=out.bpd_enq_valid && out.bpd_enq_ready && (boomcfg::NBANKS==1 || (predictor_valids_[bank]&4u));
    const bool second_reachable=!boomcfg::fetch_may_not_be_dual_banked(top.pc) &&
        !(top.cfi_valid && top.cfi_idx<4);
    in.update_valid=out.update_valid && (!logical || second_reachable);
    if constexpr (boomcfg::NBANKS==1) in.update=out.update;
    else in.update=&out.bank_update[bank];
  }
}
void FrontendState::evaluate_into(FrontendEvaluation& out, const FrontendInputs& input,
                                   const BackendFrontendFeedback& feedback) {
  evaluate_independent(out,input,feedback);
  evaluate_memory(out,input.icache_memory);
}
void FrontendState::evaluate_independent(FrontendEvaluation& out, const FrontendInputs& input,
                                          const BackendFrontendFeedback& feedback) {
  out.reset=input.reset;out.run=input.run;out.clear=clear(input);
  if (!input.run && !input.reset) return;
  compose_predictions();
  const auto& held=f4_.payload();
  const bool delay=held.sfb_mask && !held.cfi_valid && !queues_.main_full() &&
                   !held.xcpt_pf_if && !held.xcpt_ae_if;
  out.f4_deq_ready=fetch_buffer_.enq_ready() && ftq_.enq_ready() && !delay;
  out.f4_enq_ready=f4_.enq_ready(out.f4_deq_ready);
  out.f4_enq_valid=queues_.main_full() && !out.clear;
  out.fb_enq_valid=f4_.deq_valid() && ftq_.enq_ready() && !delay;
  out.fb_deq_ready=input.fetch_ready;out.fb_ftq_idx=ftq_.enq_idx();
  auto& fq=out.ftq_input;
  fq={};fq.reset=input.reset;fq.enq_ref=&held;
  fq.enq_valid=f4_.deq_valid() && fetch_buffer_.enq_ready() && !delay;
  fq.deq_valid=feedback.ftq_deq_valid;fq.deq_idx=feedback.ftq_deq_idx;
  fq.redirect_valid=feedback.ftq_redirect_valid;fq.redirect_idx=feedback.ftq_redirect_idx;
  fq.brupdate_mispredict=feedback.ftq_brupdate_mispredict;
  fq.brupdate_ftq_idx=feedback.ftq_brupdate_idx;fq.brupdate_pc_lob=feedback.ftq_brupdate_pc_lob;
  fq.brupdate_taken=feedback.ftq_brupdate_taken;
  fq.get_pc_idx={{feedback.ftq_get_pc_0_idx,feedback.ftq_get_pc_1_idx}};
  ftq_.outputs_into(fq,out.ftq_output);
  held_itlb_cycle_inputs_into(input,out.itlb_input);
  out.itlb=itlb_.outputs(out.itlb_input,input.debug_mode);
  out.main_enq_ready=queues_.main_enq_ready(out.f4_enq_ready);
  out.bpd_enq_valid=queues_.bpd_enq_valid();
  out.bpd_enq_ready=queues_.bpd_enq_ready(out.f4_enq_ready);
  out.bpd_deq_valid=queues_.bpd_deq_valid();
  auto& ai=out.assembler_input;
  ai.reset=input.reset;ai.clear=out.clear;ai.deq_ready=out.f4_enq_ready;
  ai.main_valid=queues_.main_deq_valid();
  ai.main=queues_.main_deq();
  ai.bpd=queues_.bpd_full() ? queues_.bpd_payload() : prediction_;
  ai.ras_read_addr=ras_.read_addr();ai.final_fsrc_valid=false;
  const auto bpd_key=queues_.bpd_full() ? std::uint64_t(queues_.bpd_version())
                                      : (UINT64_C(1)<<63)|cycle_;
  if (!assembled_valid_ || input.reset || out.clear || assemble_main_!=queues_.main_version() ||
      assemble_bpd_!=bpd_key || assemble_ras_!=ai.ras_read_addr) {
    assembler_.outputs_into(ai,assembled_);
    assemble_main_=queues_.main_version();assemble_bpd_=bpd_key;assemble_ras_=ai.ras_read_addr;
    assembled_valid_=true;
  }
  auto& fi=out.f0_input;
  fi={};fi.reset=input.reset;fi.f3_enq_ready=out.main_enq_ready;
  const auto cache_response=icache_.held_response();
  fi.icache_resp_valid=cache_response.valid;fi.icache_resp_data=cache_response.data;
  fi.icache_resp_data_hi=cache_response.data_hi;fi.tlb=out.itlb;
  fi.bpd_f1=prediction_f1_;fi.bpd_f2=prediction_f2_;
  fi.f3_deq_valid=queues_.main_deq_valid();fi.f4_ready=out.f4_enq_ready;
  fi.f3_predicted_target=assembled_.predicted_target;fi.f3_predicted_ghist=assembled_.predicted_ghist;
  fi.f3_fsrc=ai.main.fsrc;fi.f3_xcpt_pf_if=ai.main.xcpt_pf_if;fi.f3_xcpt_ae_if=ai.main.xcpt_ae_if;
  const auto& control=input.backend_control;
  fi.sfence_valid=control.sfence_valid;fi.sfence_addr=control.sfence_addr;
  fi.redirect_flush=control.redirect_flush;fi.redirect_valid=control.redirect_valid;
  fi.redirect_pc=control.redirect_pc;
  if (control.redirect_flush) {
    const auto& pc=ftq_ports_[1];const auto& entry=pc.entry;
    fi.redirect_ghist=pc.ghist;
    const unsigned slot=((control.redirect_branch_pc_lob^(entry.start_bank ? 8u : 0u))>>1)&(boomcfg::FETCH_WIDTH-1);
    const auto before=static_cast<std::uint8_t>((1u<<slot)-1u);
    const auto not_taken=static_cast<std::uint8_t>(entry.br_mask&before);
    if (control.redirect_from_branch_mispredict) {
      components::advance_global_history(pc.ghist,not_taken,control.redirect_branch_is_br,
          control.redirect_branch_taken,true,slot,pc.pc,fi.redirect_ghist);
      fi.redirect_ghist.ras_idx=pc.ghist.ras_idx;
    }
  }
  f0_f2_.evaluate_into(fi,out.f0_f2);
  const auto& fc=out.f0_f2.output;
  assembled_.bundle.debug_fsrc=fc.final_fsrc&3u;
  auto& ii=out.icache_input;
  ii={};ii.reset=input.reset;ii.req_valid=fc.icache_req_valid;ii.req_addr=fc.icache_req_addr;
  ii.s1_paddr=static_cast<std::uint32_t>(fc.icache_s1_paddr);
  ii.s1_kill=fc.icache_s1_kill;ii.s2_kill=fc.icache_s2_kill;ii.invalidate=control.icache_invalidate;
  out.f3_fire=queues_.main_deq_valid() && out.f4_enq_ready;
  out.update_valid=updates_.update_valid(out.ftq_output.bpdupdate_valid);
  out.update=&updates_.update(out.ftq_output.bpdupdate_valid,out.ftq_output.bpdupdate);
  out.ras_read_idx=fc.f3_enq_valid && out.main_enq_ready ? fc.f3_enq.ghist.ras_idx&31u : ras_read_idx_;
  out.ras_write_valid=out.f3_fire && assembled_.ras_write_valid;
  out.ras_write_idx=assembled_.ras_write_idx;out.ras_write_addr=assembled_.ras_write_addr;
  if (out.ftq_output.ras_update) {
    out.ras_write_valid=true;out.ras_write_idx=out.ftq_output.ras_update_idx;
    out.ras_write_addr=out.ftq_output.ras_update_pc;
  }
  const auto& s1=f0_f2_.s1();
  out.itlb_input.request_valid=(s1.valid && !s1.is_replay && !fc.f1_clear && !out.clear) || s1.is_sfence;
  out.next_itlb_sfence={control.sfence_valid,control.sfence_rs1,control.sfence_rs2,control.sfence_addr};
  split_updates(out);
}
void FrontendState::evaluate_memory(FrontendEvaluation& out,
                                     const components::SmallICacheMemoryInputs& memory) {
  if (!out.run && !out.reset) return;
  auto& ii=out.icache_input;
  ii.tl_a_ready=memory.tl_a_ready;ii.tl_d_valid=memory.tl_d_valid;
  ii.tl_d_opcode=memory.tl_d_opcode;ii.tl_d_size=memory.tl_d_size;
  ii.tl_d_data=memory.tl_d_data;ii.tl_d_data_hi=memory.tl_d_data_hi;
  out.icache=icache_.outputs(ii);
}
void FrontendState::commit_early(const FrontendEvaluation& out) {
  commit_independent(out);
  commit_memory(out);
}
void FrontendState::commit_memory(const FrontendEvaluation& out) {
  if (!out.run && !out.reset) return;
  icache_.commit(out.icache_input,out.icache);
}
void FrontendState::commit_independent(const FrontendEvaluation& out) {
  if (!out.run && !out.reset) return;
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank) banks_[bank].commit(out.bank_input[bank]);
  updates_.commit(out.reset,out.f3_fire,assembled_.btb_mispredicts,assembled_.bundle,out.ftq_output.bpdupdate_valid);
  queues_.commit(out.reset,out.clear,out.f0_f2.output.f3_enq_valid,out.main_enq_ready,
      out.f0_f2.output.f3_enq,out.bpd_enq_valid,out.bpd_enq_ready,out.bpd_deq_valid,prediction_,out.f4_enq_ready);
  itlb_.step(out.itlb_input);sfence_=out.next_itlb_sfence;
  f0_f2_.commit(out.f0_input,out.f0_f2);
  ras_.step(out.ras_read_idx,out.ras_write_valid,out.ras_write_idx,out.ras_write_addr);
  ras_read_idx_=out.reset ? 0 : out.ras_read_idx;
  predictor_pc_[2]=predictor_pc_[1];predictor_pc_[1]=predictor_pc_[0];
  predictor_pc_[0]=out.f0_f2.output.icache_req_addr;
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank)
    predictor_valids_[bank]=((predictor_valids_[bank]<<1)|out.bank_input[bank].f0_valid)&7u;
}
void FrontendState::commit_late(const FrontendEvaluation& out, bool write_lanes) {
  if (!out.run && !out.reset) return;
  components::SmallFetchBufferInputs fb;
  fb.reset=out.reset;fb.clear=out.clear;fb.enq_valid=out.fb_enq_valid;fb.deq_ready=out.fb_deq_ready;
  fb.enq=f4_.payload();fb.enq.ftq_idx=out.fb_ftq_idx;
  fb.enq.sfb_mask=fb.enq.shadowed_mask=0;
  fetch_buffer_.step(fb);
  ftq_.commit(out.ftq_input,out.ftq_output);
  components::SmallFtqOutputs next_ports;
  ftq_.outputs_into(components::SmallFtqInputs{},next_ports);ftq_ports_=next_ports.get_pc;
  f4_.commit(out.reset || out.clear,out.f4_enq_valid,out.f4_enq_ready,assembled_.bundle,out.f4_deq_ready);
  assembler_.commit(out.assembler_input,assembled_);
  if (out.reset || out.clear || (out.assembler_input.main_valid && out.assembler_input.deq_ready))
    assembled_valid_=false;
  if (write_lanes) write_record_lanes(out);
  ++cycle_;
}
void FrontendState::commit(const FrontendEvaluation& out) {
  if (!out.run && !out.reset) return;
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    sample("ftq", "update-context", cycle_, Layer::Internal, Phase::Pre,
      {{"reset", out.reset}, {"clear", out.clear},
       {"first_empty", ftq_.first_empty()}, {"pipe_valid", ftq_.bpdupdate_pipe_valid()},
       {"pipe_repair", ftq_.bpdupdate_pipe_repair()},
       {"do_commit", out.ftq_output.do_commit_update},
       {"update_valid", out.ftq_output.bpdupdate_valid},
       {"entry_cfi_valid", ftq_.bpd_entry().cfi_valid},
       {"entry_br_mask", ftq_.bpd_entry().br_mask},
       {"bpd_pc", ftq_.bpd_pc()}, {"repair_pc", ftq_.repair_pc()},
       {"redirect", out.ftq_input.redirect_valid}, {"redirect_idx", out.ftq_input.redirect_idx},
       {"branch_mispredict", out.ftq_input.brupdate_mispredict},
       {"enq_valid", out.ftq_input.enq_valid}, {"enq_ready", out.ftq_output.enq_ready}});
    require("frontend", "predictor-bank-geometry", cycle_, Layer::Internal, Phase::Pre,
      banks_.size() == boomcfg::NBANKS && boomcfg::FETCH_WIDTH == 4 * boomcfg::NBANKS,
      {{"banks", banks_.size()}, {"configured_banks", boomcfg::NBANKS},
       {"fetch_width", boomcfg::FETCH_WIDTH}});
  );
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank) banks_[bank].commit(out.bank_input[bank]);
  components::SmallFetchBufferInputs fb;
  fb.reset=out.reset;fb.clear=out.clear;fb.enq_valid=out.fb_enq_valid;fb.deq_ready=out.fb_deq_ready;
  fb.enq=f4_.payload();fb.enq.ftq_idx=out.fb_ftq_idx;
  // F4 stores raw SFB candidates. The disabled enableSFBOpt gate is at the
  // FetchBuffer input, as in Small's FetchBuffer::convert. A raw candidate
  // must still execute as an ordinary branch in this configuration.
  fb.enq.sfb_mask=fb.enq.shadowed_mask=0;
  fetch_buffer_.step(fb);
  ftq_.commit(out.ftq_input,out.ftq_output);
  components::SmallFtqOutputs next_ports;
  ftq_.outputs_into(components::SmallFtqInputs{},next_ports);ftq_ports_=next_ports.get_pc;
  f4_.commit(out.reset || out.clear,out.f4_enq_valid,out.f4_enq_ready,assembled_.bundle,out.f4_deq_ready);
  updates_.commit(out.reset,out.f3_fire,assembled_.btb_mispredicts,assembled_.bundle,out.ftq_output.bpdupdate_valid);
  assembler_.commit(out.assembler_input,assembled_);
  if (out.reset || out.clear || (out.assembler_input.main_valid && out.assembler_input.deq_ready))
    assembled_valid_=false;
  queues_.commit(out.reset,out.clear,out.f0_f2.output.f3_enq_valid,out.main_enq_ready,
      out.f0_f2.output.f3_enq,out.bpd_enq_valid,out.bpd_enq_ready,out.bpd_deq_valid,prediction_,out.f4_enq_ready);
  itlb_.step(out.itlb_input);sfence_=out.next_itlb_sfence;
  f0_f2_.commit(out.f0_input,out.f0_f2);icache_.commit(out.icache_input,out.icache);
  ras_.step(out.ras_read_idx,out.ras_write_valid,out.ras_write_idx,out.ras_write_addr);
  ras_read_idx_=out.reset ? 0 : out.ras_read_idx;
  predictor_pc_[2]=predictor_pc_[1];predictor_pc_[1]=predictor_pc_[0];
  predictor_pc_[0]=out.f0_f2.output.icache_req_addr;
  for (unsigned bank=0;bank<boomcfg::NBANKS;++bank)
    predictor_valids_[bank]=((predictor_valids_[bank]<<1)|out.bank_input[bank].f0_valid)&7u;
  write_record_lanes(out);
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    sample("ftq", "read-register-context", cycle_, Layer::Publication, Phase::Post,
      {{"read0_idx", ftq_.oracle_ram_idx(0)}, {"read0", ftq_.oracle_ram_read(0)},
       {"read1_idx", ftq_.oracle_ram_idx(1)}, {"read1", ftq_.oracle_ram_read(1)},
       {"bpd_cfi_valid", ftq_.bpd_entry().cfi_valid},
       {"redirect_cfi_valid", ftq_.redirect_entry_pipeline().cfi_valid},
       {"pipe_valid", ftq_.bpdupdate_pipe_valid()}, {"first_empty", ftq_.first_empty()}});
  );
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  CHISA_DIAG(
    ::chisa::diagnostic::sample("ftq", "published-entry", cycle_,
      ::chisa::diagnostic::Layer::Publication, ::chisa::diagnostic::Phase::Post,
      {{"bpd_cfi_valid", record_.r.frontendFtq.bpd_entry_cfi_idx_valid},
       {"redirect_cfi_valid", record_.r.frontendFtq.REG_16_cfi_idx_valid}});
  );
#endif
  ++cycle_;
}
}  // namespace chisa::boom_model::wide
