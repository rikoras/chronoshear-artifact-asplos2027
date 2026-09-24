#include "core.h"
#include "ifpu_publication.h"
#include "record_fields.h"
#include "../common/fp_execute.h"
#include "../common/fp_semantics.h"

namespace chisa::boom_model::wide {
namespace {
void recode(FpValue& value, const MicroOp& u) {
  const auto rec=fp_result_rec(u,value.data);
  value.rec_lo=static_cast<std::uint64_t>(rec);
  value.rec_hi=static_cast<std::uint8_t>((rec>>64)&1u);
}
void model_result(FpValue& value, const FpModelResponse& response, bool integer) {
  const sfp::rec_t rec=(sfp::rec_t(response.rec_hi&1u)<<64)|response.rec_lo;
  value.data=integer ? response.rec_lo : sfp::ieee64_view(rec);
  value.rec_lo=response.rec_lo;value.rec_hi=response.rec_hi&1u;value.flags=response.flags&31u;
}
}
void Core::publish_completion(CycleInputs& input, const Completion& value) const {
  if (!value.valid) return;
  for (auto& destination : input.completions) {
    if (!destination.valid) { destination=value;return; }
  }
  throw std::overflow_error("combined Large completion capacity");
}
void Core::publish_fp(CycleInputs& input, const FpValue& value, unsigned source_port) const {
  if (!value.valid) return;
  Completion result;
  result.valid=result.clear_busy=true;result.rob=value.uop.rob;result.pdst=value.uop.pdst;
  result.writes_integer=value.uop.dst_rtype==RT_FIX;
  result.writes_float=value.uop.dst_rtype==RT_FLT;
  result.data=value.data;result.fflags=value.flags;
  result.source_port=static_cast<std::uint8_t>(source_port);
  result.floating_rec_valid=result.writes_float;
  result.floating_rec_lo=value.rec_lo;result.floating_rec_hi=value.rec_hi;
  publish_completion(input,result);
}
void Core::floating_availability(CycleInputs& input) const {
  const auto& f=state_.floating;
  bool request_now=false;
  for (const auto& request:f.divide_pipe) request_now |= request.value.valid && request.due<=state_.cycle;
  input.issue.floating_fu=FU_FPU;
  if (!f.divide_buffer.value.valid && !request_now && !f.divide_issue_mask) input.issue.floating_fu |= FU_FDV;
  if (f.to_integer.empty() && f.to_store.empty()) input.issue.floating_fu |= FU_F2I;
  unsigned reserved=f.from_integer.occupancy();
  for (const auto& entry:f.from_integer_pipe) reserved+=entry.value.valid;
  const auto& e=state_.execution;
  for (unsigned active=e.read_valids[1];active;active&=active-1)
    reserved+=(e.read[1][__builtin_ctz(active)].uop.fu_code&FU_I2F)!=0;
  input.i2f_ready=f.from_integer.empty() && reserved<5;
  input.issue.memory_fu=state_.memory.issued_load && state_.memory.load_issue_count==31 ? 0 : FU_MEM;
}
void Core::flush_floating() {
  auto& f=state_.floating;
  for (auto& stage : f.read) stage.valid=false;
  for (auto& valid : f.wrapper_valids) valid=false;
  for (auto& entry : f.fixed) entry.value.valid=false;
  for (auto& entry : f.from_integer_pipe) entry.value.valid=false;
  for (auto& entry : f.divide_pipe) entry.value.valid=false;
  f.divide_buffer.value.valid=false;f.divide_output.valid=false;
  if (f.divide_active.value.valid) f.divide_killed=true;
  f.divide_issue_mask=false;f.integer_valids=0;
  f.to_integer.flush();f.to_store.flush();f.from_integer.flush();
  f.main_writeback.valid=f.long_writeback.valid=false;f.queue_words_changed=true;
}
void Core::prepare_floating(CycleInputs& input, CycleOutputs& output, bool flush) {
  auto& f=state_.floating;
  const auto resolved=input.branch.resolved, killed=input.branch.mispredicted;
  if(resolved || killed || flush) {
    f.queue_words_changed=true;
    if(f.divide_output.valid) f.divide_output_changed=true;
  }
  const auto filter=[&](FpValue& value) {
    if (value.valid && ((value.uop.br_mask&killed) || flush)) value.valid=false;
    value.uop.br_mask &= static_cast<BranchMask>(~resolved);
  };
  for (auto& stage : f.read) {
    if ((stage.uop.br_mask&killed) || flush) stage.valid=false;
    stage.uop.br_mask &= static_cast<BranchMask>(~resolved);
  }
  for (auto& entry : f.fixed) filter(entry.value);
  for (auto& entry : f.from_integer_pipe) filter(entry.value);
  for (auto& entry : f.divide_pipe) filter(entry.value);
  filter(f.divide_buffer.value);filter(f.divide_output);
  if (f.divide_active.value.valid) {
    if ((f.divide_active.value.uop.br_mask&killed) || flush) f.divide_killed=true;
    f.divide_active.value.uop.br_mask &= static_cast<BranchMask>(~resolved);
  }
  output.fp.fixed_request=f.read[1];
  output.fp.fixed_request.valid &= (f.read[1].uop.fu_code&(FU_FPU|FU_F2I))!=0;
  output.fp.rounding=static_cast<std::uint8_t>((state_.csr.fcsr>>5)&7u);
  f.main_writeback.valid=f.long_writeback.valid=false;
  FpValue to_integer, to_store, from_integer;
  bool fixed_response=false, external_consumed=false;
  FpWrapperUop wrapper=f.wrapper_uops[3];
  const bool wrapper_valid=f.wrapper_valids[3] && !(wrapper.br_mask&killed) && !flush;
  wrapper.br_mask &= static_cast<BranchMask>(~resolved);
  for (auto& entry : f.fixed) {
    if (!entry.value.valid || entry.due>state_.cycle) continue;
    auto value=entry.value;entry.value.valid=false;
    const bool store=value.uop.uopc==uopSTA || value.uop.uopc==uopSTD;
    if (store) {
      if (to_store.valid) throw std::logic_error("multiple FP store-data arrivals");
      to_store=value;continue;
    }
    if (fixed_response) throw std::logic_error("multiple fixed FPU responses");
    fixed_response=true;
    if (entry.external) {
      require_external_fp_result(input.fp.fixed.connected,input.fp.fixed.valid,
          wrapper_valid,wrapper,{value.uop.br_mask,value.uop.rob,value.uop.fu_code},
          external_consumed,state_.cycle);
      external_consumed=true;
      model_result(value,input.fp.fixed,value.uop.dst_rtype==RT_FIX);
    }
    if (value.uop.fu_code&FU_F2I) to_integer=value;
    else { f.main_writeback=value;publish_fp(input,value); }
  }
  const bool active=f.divide_active.value.valid;
  const bool buffered=f.divide_buffer.value.valid;
  const bool held_output=f.divide_output.valid;
  if (held_output && !fixed_response) {
    f.main_writeback=f.divide_output;publish_fp(input,f.divide_output);
    f.divide_output.valid=false;
  }
  output.fp.divide_response_ready=active && !held_output;
  if (active) {
    auto& body=f.divide_active;
    if (body.external && !input.fp.divide.connected)
      throw std::logic_error("cold FP divider disconnected while active");
    const bool done=body.external ? input.fp.divide.valid && output.fp.divide_response_ready
                                 : state_.cycle>=body.due;
    if (done) {
      auto value=body.value;
      if (body.external) model_result(value,input.fp.divide,false);
      value.valid=!f.divide_killed && !flush;
      f.divide_output=value;body.value.valid=false;f.divide_killed=false;f.divide_output_changed=true;
    }
  }
  if (!active && !held_output && buffered) {
    output.fp.divide_valid=true;output.fp.divide_request=f.divide_buffer;
    if (!f.divide_buffer.external || input.fp.divide_ready) {
      f.divide_active=f.divide_buffer;f.divide_active_changed=true;
      f.divide_active.due=state_.cycle+f.divide_buffer.cycles;
      f.divide_buffer.value.valid=false;f.divide_killed=false;
    }
  }
  for (auto& entry : f.divide_pipe) {
    if (!entry.value.valid || entry.due>state_.cycle) continue;
    if (f.divide_buffer.value.valid) throw std::overflow_error("FP divide request buffer");
    f.divide_buffer=entry;entry.value.valid=false;f.divide_buffer_changed=true;
  }
  for (auto& entry : f.from_integer_pipe) {
    if (!entry.value.valid) continue;
    // io_out_b_data takes its edge one cycle before the registered response
    // is consumed by this model. Publish that POST value from the pending
    // result already computed at issue; native completion timing is unchanged.
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    constexpr unsigned ifpu_unit = 1;
#else
    constexpr unsigned ifpu_unit = 0;
#endif
    if constexpr (fields::ifpu_out_data[ifpu_unit].count != 0) {
    if (cut_lanes_ && entry.due == state_.cycle + 1) {
      const auto full = (sfp::rec_t(entry.value.rec_hi & 1u) << 64) | entry.value.rec_lo;
      const auto pipe = ifpu_pipe_data(entry.value.uop.uopc, full);
      f.ifpu_rec_lo = static_cast<std::uint64_t>(pipe);
      f.ifpu_rec_hi = static_cast<std::uint8_t>((pipe >> 64) & 1u);
      f.ifpu_changed = true;
    }
    }
    if (entry.due>state_.cycle) continue;
    if (from_integer.valid) throw std::logic_error("multiple IntToFP responses");
    from_integer=entry.value;entry.value.valid=false;
  }
  const bool integer_ready=!output.memory_ports.integer_response;
  const bool floating_ready=!output.memory_ports.floating_response.valid;
  const auto integer=f.to_integer.front(to_integer,resolved,killed,flush);
  const auto store=f.to_store.front(to_store,resolved,killed,flush);
  const auto converted=f.from_integer.front(from_integer,resolved,killed,flush);
  if (integer.valid && integer_ready) {
    output.fp.integer_writeback=integer;publish_fp(input,integer,0);
  } else if (!integer.valid && store.valid && integer_ready) {
    const auto& u=store.uop;
    if (u.stq_idx>=kLsq) throw std::out_of_range("FP store queue index");
    const auto& descriptor=state_.lsu.stores[u.stq_idx];
    if (test(state_.lsu.store_valid,u.stq_idx) && descriptor.rob()==u.rob &&
        !(descriptor.branch()&killed) && !flush) {
      store_data(u.stq_idx,store.data);
      state_.memory.fp_store={true,memory_tag(false,u.stq_idx),state_.cycle+1};
      output.fp.store_data=store;
    }
  }
  if (!floating_ready) {
    const auto& response=output.memory_ports.floating_response;
    const auto& u=instruction(response.tag.rob);
    FpValue value;
    value.valid=true;value.uop=FpTag::from(u);
    value.uop.br_mask=response.tag.branch;value.uop.pdst=response.tag.pdst;
    value.data=response.tag.single ? sfp::box32(static_cast<std::uint32_t>(response.data)) : response.data;
    const auto rec=sfp::hf_recode64(response.data,response.tag.single);
    value.rec_lo=static_cast<std::uint64_t>(rec);
    value.rec_hi=static_cast<std::uint8_t>((rec>>64)&1u);
    f.long_writeback=value;publish_fp(input,value,kWritebackPorts-2);
  } else if (converted.valid) {
    f.long_writeback=converted;publish_fp(input,converted,kWritebackPorts-2);
  }
  if(to_integer.valid || to_store.valid || from_integer.valid ||
     (integer.valid && integer_ready) || (store.valid && integer_ready && !integer.valid) ||
     (converted.valid && floating_ready)) f.queue_words_changed=true;
  if((!f.to_integer.empty() && !f.to_integer.valids[f.to_integer.dequeue]) ||
     (!f.to_store.empty() && !f.to_store.valids[f.to_store.dequeue]) ||
     (!f.from_integer.empty() && !f.from_integer.valids[f.from_integer.dequeue])) f.queue_words_changed=true;
  f.to_integer.step(to_integer,integer_ready,resolved,killed,flush);
  f.to_store.step(to_store,integer_ready && !integer.valid,resolved,killed,flush);
  f.from_integer.step(from_integer,floating_ready,resolved,killed,flush);
  output.fp.main_writeback=f.main_writeback;output.fp.long_writeback=f.long_writeback;
  const auto integer_valids=f.integer_valids;
  f.integer_uops[1]=f.integer_uops[0];
  f.integer_valids=static_cast<std::uint8_t>((unsigned(integer_valids)<<1)&3u);
  for (unsigned stage=0;stage<2;++stage) {
    if ((f.integer_uops[stage].br_mask&killed) || flush) f.integer_valids &= static_cast<std::uint8_t>(~(1u<<stage));
    f.integer_uops[stage].br_mask &= static_cast<BranchMask>(~resolved);
  }
  if (output.i2f.valid && !flush) {
    const auto& stage=output.i2f.uop;
    const auto& u=instruction(stage.rob);
    f.integer_uops[0]=FpTag::from(stage);f.integer_valids |= 1u;
    f.integer_operand=output.i2f.operand;f.integer_rounding=fp_rm(u,state_.csr);
    f.integer_type=static_cast<std::uint8_t>((u.imm_packed>>8)&3u);
    f.integer_tag=u.uopc==uopFCVT_D_X || u.uopc==uopFMV_D_X ? 1 : 0;
    f.integer_wflags=u.uopc==uopFCVT_S_X || u.uopc==uopFCVT_D_X;
    write_ifpu_input();
    const auto result=fp_compute_i2f(u,fp_rm(u,state_.csr),output.i2f.operand);
    FpPending* slot=nullptr;
    for (auto& entry : f.from_integer_pipe) if (!entry.value.valid) { slot=&entry;break; }
    if (!slot) throw std::overflow_error("IntToFP pipeline capacity");
    *slot={};slot->value.valid=true;slot->value.uop=FpTag::from(stage);
    slot->value.data=result.ieee;slot->value.flags=result.exc;
    recode(slot->value,u);
    // Two RegisterRead stages have elapsed at this handoff; IntToFP adds two.
    slot->due=state_.cycle+2;
  }
}
void Core::launch_floating(const CycleInputs& input, const CycleOutputs& output) {
  auto& f=state_.floating;
  const auto& wrapper=output.fp.fixed_request;
  advance_fp_wrapper<true>(f.wrapper_uops,f.wrapper_valids,
      {wrapper.uop.br_mask,wrapper.uop.rob,wrapper.uop.fu_code,wrapper.uop.pdst,wrapper.uop.stq_idx,
       wrapper.uop.uopc,wrapper.uop.dst_rtype,wrapper.uop.flags},wrapper.valid,
      input.branch.resolved,input.branch.mispredicted,output.exception || output.serializing);
  f.read[1]=f.read[0];
  const auto& raw=output.floating;
  const auto& grant=output.floating;
  f.read[0].valid=grant.valid;
  if (raw.selected) {
    f.read[0].uop=FpReadTag::from(raw.uop);
    f.read[0].uop.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
    constexpr unsigned address_mask=(1u<<boomcfg::index_width_for_entries(boomcfg::NUM_FPREGS))-1;
    f.read[0].addresses={{static_cast<std::uint8_t>(raw.uop.prs1&address_mask),
                         static_cast<std::uint8_t>(raw.uop.prs2&address_mask),
                         static_cast<std::uint8_t>(raw.prs3&address_mask)}};
    f.read[0].rec_hi=0;
    for (unsigned operand=0;operand<3;++operand) {
      const auto index=f.read[0].addresses[operand];
      if (index>=boomcfg::NUM_FPREGS) throw std::out_of_range("FP read register outside configured file");
      f.read[0].rec_lo[operand]=index ? state_.floating_rec_lo[index] : 0;
      f.read[0].rec_hi |= static_cast<std::uint8_t>((index ? state_.floating_rec_hi[index]&1u : 0u)<<operand);
    }
  }
  f.divide_issue_mask=raw.selected && (raw.uop.fu_code&FU_FDV);
  if (!grant.valid) return;
  const auto& stage=grant.uop;
  const auto& u=instruction(stage.rob);
  const auto a=state_.floating_registers[stage.prs1],b=state_.floating_registers[stage.prs2],
             c=state_.floating_registers[grant.prs3];
  FpValue value;value.valid=true;value.uop=FpTag::from(stage);
  const bool store=u.uopc==uopSTA || u.uopc==uopSTD;
  if (u.fu_code&FU_FDV) {
    FpDivide* slot=nullptr;
    for (auto& entry : f.divide_pipe) if (!entry.value.valid) { slot=&entry;break; }
    if (!slot) throw std::overflow_error("FP divide input pipeline");
    *slot={};slot->value=value;slot->due=state_.cycle+2;
    slot->external=input.fp.divide.connected;
    slot->rounding=static_cast<std::uint8_t>((state_.csr.fcsr>>5)&7u);
    slot->sqrt=u.uopc==uopFSQRT_S || u.uopc==uopFSQRT_D;
    const bool single=u.uopc==uopFDIV_S || u.uopc==uopFSQRT_S;
    const auto widen=[single](std::uint64_t data) {
      return sfp::rec65_from_fn64(single ? sfp::cvt_s_to_d(0,sfp::unbox32(data)).ieee : data);
    };
    const auto ar=widen(a),br=slot->sqrt ? ar : widen(b);
    slot->a=static_cast<std::uint64_t>(ar);slot->b=static_cast<std::uint64_t>(br);
    slot->hi=static_cast<std::uint8_t>(((ar>>64)&1u)|(((br>>64)&1u)<<1));
    if (!slot->external) {
      const auto saved=softfloat_detectTininess;
      softfloat_detectTininess=softfloat_tininess_beforeRounding;
      const auto result=fp_compute(u,slot->rounding,a,b,c);
      softfloat_detectTininess=saved;
      slot->value.data=result.ieee;slot->value.flags=result.exc;recode(slot->value,u);
      slot->cycles=fp_divsqrt_special(u,a,b) ? 1 : (slot->sqrt ? 26 : 18);
    }
    return;
  }
  FpPending* slot=nullptr;
  for (auto& entry : f.fixed) if (!entry.value.valid) { slot=&entry;break; }
  if (!slot) throw std::overflow_error("fixed FP pipeline capacity");
  *slot={};slot->value=value;
  slot->due=state_.cycle+(store ? 2u : 6u);
  slot->external=!store && input.fp.fixed.connected;
  if (store) slot->value.data=fp_store_bits(b,u.fp_single);
  else if (!slot->external) {
    const auto result=fp_compute(u,fp_rm(u,state_.csr),a,b,c);
    slot->value.data=result.ieee;slot->value.flags=result.exc;recode(slot->value,u);
  }
}
}  // namespace chisa::boom_model::wide
