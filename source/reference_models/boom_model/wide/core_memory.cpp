#include "core.h"
#include "record_fields.h"
#include "../common/memory_data.h"
#include "../common/diagnostic_monitor.h"

namespace chisa::boom_model::wide {
namespace {
std::uint8_t bytes(std::uint64_t address, unsigned size) {
  return static_cast<std::uint8_t>(((1u<<(1u<<(size&3u)))-1u)<<(address&7u));
}
unsigned age(unsigned index, unsigned head) { return (index+kLsq-head)%kLsq; }
}
void Core::prepare_memory(CycleInputs& input, CycleOutputs& output, bool flush) {
  auto& q=state_.lsu;auto& m=state_.memory;auto& ports=output.memory_ports;
  const auto killed=input.branch.mispredicted,resolved=input.branch.resolved;
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    sample("lsu","memory_control",state_.cycle,Layer::Internal,Phase::Pre,
        {{"kill",killed},{"resolve",resolved},{"flush",flush},
         {"load_valid",q.load_valid},{"store_valid",q.store_valid},
         {"store_committed",q.store_committed},{"pending",m.pending.valid},
         {"pending_rob",m.pending.tag.rob},{"pending_ticket",m.pending.tag.ticket}});
    for(unsigned slot=0;slot<m.clear_store.size();++slot) {
      const auto& done=m.clear_store[slot];
      if(done.valid) sample("lsu","pending_store",state_.cycle,Layer::Internal,Phase::Pre,
          {{"slot",slot},{"valid",done.valid},{"due",done.due},
           {"floating",done.floating_data},{"rob",done.tag.rob},
           {"branch",done.tag.branch},{"store",done.tag.store},
           {"generation",done.tag.generation},{"kill",killed},{"resolve",resolved}});
    }
    // A one-edge handoff is observed here without imposing unproven
    // equivalence between the model's functional tags and RTL payload banks.
    if(m.search.valid || m.forward.valid || m.fp_store.valid)
      sample("lsu","memory_handoff",state_.cycle,Layer::Internal,Phase::Pre,
          {{"search",m.search.valid},{"search_branch",m.search.tag.branch},
           {"forward",m.forward.valid},{"forward_branch",m.forward.load.branch},
           {"fp_store",m.fp_store.valid},{"fp_branch",m.fp_store.tag.branch},
           {"fp_due",m.fp_store.due},{"kill",killed},{"resolve",resolved},{"flush",flush}});
  );
  MemoryPlan local;
  const MemoryPlan* prepared=input.memory.prepared_plan;
  if (prepared) {
    if (prepared->owner!=this || prepared->cycle+1!=state_.cycle)
      throw std::logic_error("Large memory PRE plan belongs to another cycle/core");
  } else {
    local=plan_memory(input.memory.control,input.branch);prepared=&local;
  }
  const auto& plan=*prepared;const auto& s=plan.schedule;
  ports.schedule=s;ports.translation=plan.translation;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
  if (cut_lanes_) write_record(*record_,fields::lsu_fired_load_incoming,s.load_incoming);   // lsu.scala:894
#endif
  ports.release_ready=s.release;
  ports.request=input.memory.prepared_request ? *input.memory.prepared_request
                                             : memory_request(plan,input.memory.translation);
  if (ports.request.valid && ports.request.tag.ticket!=m.next_ticket)
    throw std::logic_error("Large prepared memory request ticket changed");

  // PRE masks, pointers and selectors are sampled once; no descriptor-array
  // copy or second scheduling pass is needed.
  const auto ld_valid=q.load_valid,ld_addr=q.load_address,ld_virtual=q.load_virtual;
  const auto ld_exsucc=q.load_executed|q.load_succeeded,ld_forward=q.load_forwarded;
  const auto st_valid=q.store_valid,st_addr=q.store_address,st_data=q.store_data;
  const auto st_virtual=q.store_virtual,st_committed=q.store_committed,st_succeeded=q.store_succeeded;
  const auto ld_head=q.load_head,st_head=q.store_head,st_commit=q.store_commit;
  const auto old_block1=m.block1;
  const auto wake_eligible=ld_valid&ld_addr&~(ld_virtual|ld_exsucc|q.load_order_fail|q.load_exception);
  const auto retry_eligible=ld_valid&ld_addr&ld_virtual&~(q.load_order_fail|q.load_exception);
  const auto store_retry_eligible=st_valid&st_addr&st_virtual&~q.store_exception;
  const auto previous_translation_fault=m.translation_fault;
  const auto previous_exception=m.exception;
  const auto previous_forward=m.forward;
  const auto previous_search=m.search;
  const auto spec1=m.speculative[0],spec2=m.speculative[1];
  // REG108/148 is RegNext(mem_incoming_uop.ldq_idx): the MEM
  // payload already lives in incoming_load_index. Sample that PRE value
  // before advancing it from the current EXE/read-stage input.
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  record_->r.lsu.REG_108=m.incoming_load_index;
#else
  record_->r.lsu.REG_148=m.incoming_load_index;
#endif
  m.incoming_load_index=m.read[1].valid ? m.read[1].uop.ldq_idx : 0;
  if (cut_lanes_) {
    // lsu.scala mem_incoming_uop / mem_ldq_incoming_e: RegNext of the EXE
    // request's uop (zeros when idle) and of the LDQ entry it indexes.
    const auto& in=m.read[1];const bool live=in.valid;
    write_record(*record_,fields::mem_incoming_uop_ldq_idx,live ? in.uop.ldq_idx : 0);
    write_record(*record_,fields::mem_incoming_uop_stq_idx,live ? in.uop.stq_idx : 0);
    write_record(*record_,fields::mem_incoming_uop_pdst,live ? in.uop.pdst : 0);
    write_record(*record_,fields::mem_incoming_uop_fp_val,live && in.uop.fp_val());
    const unsigned index=live && in.uop.ldq_idx<kLsq ? in.uop.ldq_idx : 0;
    const auto& entry=q.loads[index];
    write_record(*record_,fields::mem_ldq_incoming_uop_br_mask,static_cast<BranchMask>(entry.branch()&~resolved));
    write_record(*record_,fields::mem_ldq_incoming_uop_rob_idx,entry.rob());
    write_record(*record_,fields::mem_ldq_incoming_uop_stq_idx,entry.store_index());
    write_record(*record_,fields::mem_ldq_incoming_uop_mem_size,entry.size());
    // lsu.scala:1041-1043: the load entry's st_dep_mask is the live store set
    // it was dispatched behind, cleared as those stores leave the queue head.
    QueueMask dep=0;
    for (unsigned s=st_head;s!=q.youngest_store[index];s=static_cast<unsigned>(LsqGeometry::wrap(int(s)+1)))
      if (test(st_valid,s) && test(q.dependencies[index],s)) dep|=bit(s);
    write_record(*record_,fields::mem_ldq_incoming_st_dep_mask,dep);
    // lsu.scala:413/910: mem_stq_incoming_e is the STQ entry the request's
    // stq_idx names, latched every edge; its bits matter when a store fires.
    const unsigned sidx=live && in.uop.stq_idx<kLsq ? in.uop.stq_idx : 0;
    const auto& sentry=q.stores[sidx];
    write_record(*record_,fields::mem_stq_incoming_valid,test(st_valid,sidx));
    write_record(*record_,fields::mem_stq_incoming_uop_br_mask,static_cast<BranchMask>(sentry.branch()&~resolved));
    write_record(*record_,fields::mem_stq_incoming_uop_rob_idx,sentry.rob());
    write_record(*record_,fields::mem_stq_incoming_uop_stq_idx,sidx);
    write_record(*record_,fields::mem_stq_incoming_uop_mem_size,sentry.size());
    write_record(*record_,fields::mem_stq_incoming_uop_is_amo,sentry.amo());
    write_record(*record_,fields::mem_stq_incoming_addr_valid,test(st_addr,sidx));
    write_record(*record_,fields::mem_stq_incoming_addr_is_virtual,test(st_virtual,sidx));
    write_record(*record_,fields::mem_stq_incoming_data_valid,test(st_data,sidx));
  }
  m.forward.valid=false;m.search.valid=false;m.translation_fault.valid=false;m.exception.valid=false;
  for (auto& stage : m.read) {
    if ((stage.uop.br_mask&killed) || flush) stage.valid=false;
    stage.uop.br_mask &= static_cast<BranchMask>(~resolved);
  }
  ports.s1_kill=m.pending.valid &&
      (m.pending_fault || !memory_tag_live(m.pending.tag,killed,flush));
  if (ports.s1_kill && m.pending.tag.uses_load && m.pending.tag.load<kLsq &&
      q.load_ticket[m.pending.tag.load]==m.pending.tag.ticket)
    q.load_ticket[m.pending.tag.load]=0;

  const auto publish_fault=[&](MemoryFault fault) {
    if (!fault.valid || !memory_tag_live(fault.tag,killed,flush)) return;
    Completion completion;
    completion.valid=completion.exception=completion.tval_valid=true;
    completion.rob=fault.tag.rob;completion.cause=fault.cause;completion.tval=fault.address;
    publish_completion(input,completion);
  };
  publish_fault(previous_exception);
  if (previous_translation_fault.valid && memory_tag_live(previous_translation_fault.tag,killed,flush)) {
    const auto& tag=previous_translation_fault.tag;
    if (tag.uses_load) q.set_load_mask(q.load_exception,q.load_exception|(bit(tag.load)));
    else if (tag.uses_store) q.set_store_mask(q.store_exception,q.store_exception|(bit(tag.store)));
  }
  for (auto& done : m.clear_store) {
    if (!done.valid) continue;
    // clr_bsy is registered from the MEM-stage operation using this edge's
    // branch update. Waiting for the completion's due edge publishes a
    // killed operation for one cycle and retains already-resolved mask bits.
    const bool branch_killed=(done.tag.branch&killed)!=0;
    done.tag.branch &= static_cast<BranchMask>(~resolved);
    if (branch_killed) { done.valid=false;continue; }
    if (done.due>state_.cycle) continue;
    done.valid=false;
    CHISA_DIAG(
      using namespace ::chisa::diagnostic;
      sample("lsu","store_completion_candidate",state_.cycle,Layer::Internal,Phase::Combinational,
          {{"due",done.due},{"rob",done.tag.rob},{"branch",done.tag.branch},
           {"store",done.tag.store},{"generation",done.tag.generation},
           {"queue_generation",done.tag.uses_store && done.tag.store<kLsq
               ? q.store_generation[done.tag.store] : 0u},
           {"live",memory_tag_live(done.tag,killed,flush)},
           {"kill",killed},{"resolve",resolved},{"flush",flush}});
    );
    if (!memory_tag_live(done.tag,killed,flush)) continue;
    CHISA_DIAG(
      using namespace ::chisa::diagnostic;
      require("lsu","store_completion_live",state_.cycle,Layer::Internal,Phase::Post,
          done.due<=state_.cycle && memory_tag_live(done.tag,killed,flush),
          {{"due",done.due},{"rob",done.tag.rob},{"branch",done.tag.branch},
           {"store",done.tag.store},{"generation",done.tag.generation},
           {"kill",killed},{"resolve",resolved},{"flush",flush}});
    );
    Completion completion;completion.valid=completion.clear_busy=true;completion.rob=done.tag.rob;
    completion.source_port=done.floating_data ? kWritebackPorts+1 : kWritebackPorts;
    publish_completion(input,completion);
  }
  const auto clear_later=[&](MemoryTag tag, unsigned delay, bool floating_data = false) {
    for (auto& done : m.clear_store) {
      if (done.valid) continue;
      tag.branch &= static_cast<BranchMask>(~resolved);
      done={true,tag,state_.cycle+delay,floating_data};return;
    }
    throw std::overflow_error("store clear-busy pipeline");
  };
  if (m.fp_store.valid && m.fp_store.due<=state_.cycle) {
    const auto tag=m.fp_store.tag;m.fp_store.valid=false;
    if (memory_tag_live(tag,killed,flush) && test(st_addr,tag.store) &&
        !test(st_virtual,tag.store) && !tag.amo) clear_later(tag,1,true);
  }

  std::uint32_t nacks=0;
  const auto& nack=input.memory.nack;
  if (nack.valid && memory_tag_live(nack.tag,killed,flush)) {
    if (nack.tag.uses_load && q.load_ticket[nack.tag.load]==nack.tag.ticket) {
      nacks=bit(nack.tag.load);q.set_load_mask(q.load_executed,q.load_executed&(~nacks));q.load_ticket[nack.tag.load]=0;
    } else if (nack.tag.uses_store && q.store_ticket[nack.tag.store]==nack.tag.ticket) {
      q.store_ticket[nack.tag.store]=0;
      if (age(nack.tag.store,st_head)<age(q.store_execute,st_head)) q.store_execute=nack.tag.store;
    }
  }
  if (m.release) {
    for (auto slots=ld_valid&ld_addr;slots;slots&=slots-1) {
      const auto i=static_cast<unsigned>(__builtin_ctz(slots));
      if ((q.loads[i].address>>6)==(m.release_address>>6)) q.set_load_mask(q.load_observed,q.load_observed|(bit(i)));
    }
  }
  const auto response_live=[&](const MemoryResponse& response) {
    if (!response.valid || !memory_tag_live(response.tag,killed,flush)) return false;
    return response.tag.uses_load ? q.load_ticket[response.tag.load]==response.tag.ticket && response.tag.ticket!=0
         : response.tag.uses_store && q.store_ticket[response.tag.store]==response.tag.ticket && response.tag.ticket!=0;
  };
  const auto& response=input.memory.response;
  const bool response_pre_live=response_live(response);
  const bool response_port_busy=response_pre_live && (response.tag.uses_load || response.tag.amo);
  const bool forward_live=previous_forward.valid &&
      memory_tag_live(previous_forward.load,killed,flush) && previous_forward.store<kLsq &&
      test(st_valid&st_data,previous_forward.store) &&
      q.store_generation[previous_forward.store]==previous_forward.store_generation;
  std::uint32_t failed=0;
  bool match_without_forward=false;
  const auto searchable=ld_valid&ld_addr&~ld_virtual;
  if (previous_search.valid && memory_tag_live(previous_search.tag,killed,flush)) {
    const auto& search=previous_search;
    if (!search.load) {
      const unsigned store=search.tag.store;
      for (auto slots=searchable;slots;slots&=slots-1) {
        const auto i=static_cast<unsigned>(__builtin_ctz(slots));
        const bool forwarding=forward_live && previous_forward.load.load==i && !response_port_busy;
        if (!test(q.dependencies[i],store) || (!test(ld_exsucc,i) && !forwarding)) continue;
        if ((q.loads[i].address>>3)!=(search.address>>3) ||
            !(bytes(q.loads[i].address,q.loads[i].size())&bytes(search.address,search.tag.size))) continue;
        const unsigned from=forwarding ? previous_forward.store : q.forwarded_store[i];
        const auto youngest=q.youngest_store[i];
        if ((!forwarding && !test(ld_forward,i)) ||
            (from!=store && age(from,youngest)<age(store,youngest))) {
          failed |= bit(i);q.set_load_mask(q.load_order_fail,q.load_order_fail|(bit(i)));
        }
      }
    } else {
      const unsigned load=search.tag.load;
      bool load_blocked=false,match=false,can_forward=false;
      unsigned from=0;
      for (auto slots=searchable&~bit(load);slots;slots&=slots-1) {
        const auto i=static_cast<unsigned>(__builtin_ctz(slots));
        if ((q.loads[i].address>>3)!=(search.address>>3) ||
            !(bytes(q.loads[i].address,q.loads[i].size())&bytes(search.address,search.tag.size))) continue;
        if (age(i,ld_head)>age(load,ld_head)) continue;
        if (!test(ld_exsucc,i) || test(nacks|m.nacks,i)) load_blocked=true;
      }
      const auto dependencies=q.dependencies[load]&st_valid;
      for (unsigned offset=1;offset<=kLsq;++offset) {
        const auto i=static_cast<unsigned>(LsqGeometry::wrap(int(q.youngest_store[load])-int(offset)));
        if (!test(dependencies,i)) continue;
        const auto& store=q.stores[i];
        if (store.fence() || store.amo()) { match=true;break; }
        // Unknown store addresses are speculative, not a global load stall.
        // A later store-address search detects an ordering violation.
        if (!test(st_addr,i) || test(st_virtual,i) || (store.address>>3)!=(search.address>>3)) continue;
        const auto load_bytes=bytes(search.address,search.tag.size),store_bytes=bytes(store.address,store.size());
        if (!(load_bytes&store_bytes)) continue;
        match=true;from=i;can_forward=(load_bytes&store_bytes)==load_bytes;break;
      }
      can_forward &= !load_blocked && !test(q.load_uncacheable,load);
      if (match || load_blocked) {
        if (search.fired && m.pending.valid && m.pending.tag.uses_load &&
            m.pending.tag.ticket==search.tag.ticket) {
          ports.s1_kill=true;q.load_ticket[load]=0;
        }
        q.set_load_mask(q.load_executed,q.load_executed&(~bit(load)));
        if (can_forward)
          m.forward={true,search.tag,static_cast<std::uint8_t>(from),q.store_generation[from]};
      } else if (search.fired && !test(nacks,load)) q.set_load_mask(q.load_executed,q.load_executed|(bit(load)));
      match_without_forward=match && !can_forward;
    }
  }
  const auto finish_load=[&](MemoryTag tag, std::uint64_t data) {
    tag.branch &= static_cast<BranchMask>(~resolved);
    q.loads[tag.load].data = data;q.set_load_mask(q.load_succeeded,q.load_succeeded|(bit(tag.load)));
    if (tag.floating) ports.floating_response={true,tag,data};
    else {
      Completion completion;completion.valid=completion.clear_busy=true;
      completion.rob=tag.rob;completion.pdst=tag.pdst;completion.writes_integer=true;completion.data=data;
      completion.source_port=0;
      publish_completion(input,completion);ports.integer_response=true;
    }
  };
  bool spec_hit=false;
  if (response_live(response)) {
    const auto& tag=response.tag;
    if (response.exception) {
      m.translation_fault={true,tag,response.cause,
          tag.uses_load ? q.loads[tag.load].virtual_address : q.stores[tag.store].virtual_address};
    } else {
      if (tag.uses_load) {
        finish_load(tag,response.data);
        spec_hit=spec2.valid && tag.load==spec2.tag.load && tag.generation==spec2.tag.generation;
      } else if (tag.amo) {
        Completion completion;completion.valid=completion.clear_busy=true;
        completion.rob=tag.rob;completion.pdst=tag.pdst;completion.writes_integer=true;completion.data=response.data;
        completion.source_port=0;
        publish_completion(input,completion);ports.integer_response=true;
      }
      if (tag.uses_store) q.set_store_mask(q.store_succeeded,q.store_succeeded|(bit(tag.store)));
    }
  }
  if (forward_live && !response_port_busy) {
    const auto& forward=previous_forward;
    const auto& load=q.loads[forward.load.load];
    const auto& store=q.stores[forward.store];
    finish_load(forward.load,fwd_extract(load.address,load.size(),load.signed_load(),store.size(),store.data));
    q.set_load_mask(q.load_forwarded,q.load_forwarded|(bit(forward.load.load)));q.set_load_value(q.forwarded_store[forward.load.load],forward.store,forward.load.load);
    spec_hit |= spec2.valid && forward.load.load==spec2.tag.load && forward.load.generation==spec2.tag.generation;
  }
  const bool spec2_live=spec2.valid && memory_tag_live(spec2.tag,killed,flush);
  ports.load_miss=spec2_live && !spec_hit;input.load_miss |= ports.load_miss;
  if (spec1.valid && memory_tag_live(spec1.tag,killed,flush)) {
    ports.speculative_wakeup=true;ports.speculative_pdst=spec1.tag.pdst;
    bool inserted=false;
    for (auto& wakeup : input.wakeups) {
      if (wakeup.valid) continue;
      wakeup={true,false,true,spec1.tag.pdst};inserted=true;break;
    }
    if (!inserted) throw std::overflow_error("speculative wakeup capacity");
  }

  std::uint32_t blocked_now=0;
  MemoryTag translated=plan.translated;
  translated.branch &= static_cast<BranchMask>(~resolved);
  const bool translated_live=memory_tag_live(plan.translated,killed,flush);
  const auto& translation=input.memory.translation;
  const bool passthrough=plan.control.passthrough || translation.passthrough;
  const bool miss=!passthrough && translation.miss;
  const auto physical=passthrough ? plan.virtual_address : translation.physical;
  const auto address=(miss ? plan.virtual_address : physical)&((UINT64_C(1)<<40)-1);
  const bool uncached=!passthrough && !miss && translation.uncacheable;
  const bool translating_load=s.load_incoming || s.load_retry;
  const bool translating_store=s.stad_incoming || s.sta_incoming || s.sta_retry;
  bool fault=false;
  if (translating_load || translating_store) {
    const bool incoming=s.load_incoming || s.stad_incoming || s.sta_incoming;
    const bool misaligned=incoming && (plan.virtual_address&((UINT64_C(1)<<(translated.size&3u))-1));
    const bool page=!passthrough && (translating_load ? translation.page_fault_load : translation.page_fault_store);
    const bool access=!passthrough && (translating_load ? translation.access_fault_load : translation.access_fault_store);
    fault=misaligned || page || access;
    if (fault && translated_live) {
      MemoryFault next{true,translated,
        misaligned ? (translating_load ? 4u : 6u) : page ? (translating_load ? 13u : 15u) : (translating_load ? 5u : 7u),
        plan.virtual_address};
      if (!m.translation_fault.valid ||
          ((unsigned(next.tag.rob)-RobGeometry::encode(state_.rob.head,0))&kRobMask) <
          ((unsigned(m.translation_fault.tag.rob)-RobGeometry::encode(state_.rob.head,0))&kRobMask))
        m.translation_fault=next;
    }
    if (translating_load && translated_live) {
      const unsigned i=translated.load;
      q.set_load_value(q.loads[i].address,address,i);if (s.load_incoming) q.loads[i].virtual_address = plan.virtual_address;
      q.set_load_mask(q.load_address,q.load_address|(bit(i)));assign(q.load_virtual,i,miss);assign(q.load_uncacheable,i,uncached);
      blocked_now |= bit(i);
      if (!miss && !fault) m.search={true,true,false,translated,physical};
    } else if (translating_store && translated_live) {
      const unsigned i=translated.store;
      q.set_store_value(q.stores[i].address,address,i);
      if (s.stad_incoming || s.sta_incoming) q.stores[i].virtual_address = plan.virtual_address;
      assign(q.store_address,i,!(s.sta_retry && translation.page_fault_store && !passthrough));
      assign(q.store_virtual,i,miss);
      if (!miss && !fault) m.search={true,false,false,translated,physical};
    }
  }
  if ((s.stad_incoming || s.std_incoming) && translated_live)
    store_data(translated.store,plan.incoming_data);
  if ((translating_store || s.std_incoming) && translated_live && !translated.amo &&
      test(q.store_address&q.store_data,translated.store) &&
      !test(q.store_virtual|q.store_exception,translated.store) && !fault)
    clear_later(translated,2);
  if (s.sfence && translated_live) {
    clear_later(translated,2);ports.sfence=true;
    ports.sfence_rs1=plan.incoming.prs1!=0;ports.sfence_rs2=plan.incoming.prs2!=0;
    ports.sfence_address=plan.virtual_address;
  }
  if (s.load_wakeup && memory_tag_live(plan.cache,killed,flush)) {
    blocked_now |= bit(plan.cache.load);
    m.search={true,true,false,plan.cache,plan.cache_address};
    m.search.tag.branch &= static_cast<BranchMask>(~resolved);
  }
  ports.fired=ports.request.valid && input.memory.control.request_ready;
  m.pending=ports.request;m.pending.valid=ports.fired;
  m.pending_fault=ports.fired && ((fault && ports.request.tag.uses_load) ||
      !memory_tag_live(ports.request.tag,killed,flush));
  if (ports.fired) {
    ++m.next_ticket;
    const auto& tag=ports.request.tag;
    if (memory_tag_live(tag,killed,flush)) {
      if (tag.uses_load) q.load_ticket[tag.load]=tag.ticket;
      else if (tag.uses_store) {
        q.store_ticket[tag.store]=tag.ticket;q.set_store_mask(q.store_succeeded,q.store_succeeded&(~bit(tag.store)));
        // A PRE nack rewinds after this edge's issue-head increment.
        if (!(nack.valid && nack.tag.uses_store && memory_tag_live(nack.tag,killed,flush)))
          q.store_execute=static_cast<std::uint8_t>(LsqGeometry::wrap(tag.store+1));
      }
    }
    if (m.search.valid && m.search.load && m.search.tag.load==tag.load && tag.uses_load) {
      m.search.fired=true;m.search.tag.ticket=tag.ticket;
    }
  }
  if (s.store_commit || !plan.candidates.store_commit) m.store_blocked=0;
  else m.store_blocked=m.store_blocked==15 ? 0 : 15;
  if (boom_lsu::clear_store(test(st_valid,st_head),test(st_committed,st_head),
      q.stores[st_head].fence(),test(st_succeeded,st_head),input.memory.control.ordered)) {
    const bool fence=q.stores[st_head].fence();
    drain_store(input.memory.control.ordered);
    if (fence) q.store_execute=static_cast<std::uint8_t>(LsqGeometry::wrap(q.store_execute+1));
  }
  // Old registered TLB fault and this LCAM search compete by ROB age.
  MemoryFault selected=previous_translation_fault;bool load_selected=false;
  if (failed) {
    const unsigned i=boom_lsu::age_priority_pick<kLsq>(failed,ld_head);
    const auto tag=memory_tag(true,i);
    if (!selected.valid || ((unsigned(tag.rob)-RobGeometry::encode(state_.rob.head,0))&kRobMask) <
        ((unsigned(selected.tag.rob)-RobGeometry::encode(state_.rob.head,0))&kRobMask)) {
      selected={true,tag,16,q.loads[i].virtual_address};load_selected=true;
    }
  }
  if (selected.valid && memory_tag_live(selected.tag,killed,flush)) {
    selected.tag.branch &= static_cast<BranchMask>(~resolved);m.exception=selected;
  }
  if (cut_lanes_) {
    // lsu.scala:1241-1251: r_xcpt.cause/badvaddr are RegNext of the exception
    // mux every cycle: the registered TLB fault's cause (7, the mux default,
    // when there is none) unless an older load-ordering failure wins (16);
    // badvaddr is the previous TLB request's virtual address.
    write_record(*record_,fields::lsu_r_xcpt_cause,
                 load_selected ? 16u : (previous_translation_fault.valid ? previous_translation_fault.cause : 7u));
    write_record(*record_,fields::lsu_r_xcpt_badvaddr,tlb_vaddr_r_);
    tlb_vaddr_r_=plan.virtual_address;
    // lsu.scala:1025/1066/1221: wb_forward_ld_addr and clr_unsafe's rob
    // index are RegNext of the mem-stage LCAM address and uop, which this
    // model formed one step earlier as its search; with nothing searched the
    // address is the dcache request's (mem_paddr) or zero, the rob index zero.
    write_record(*record_,fields::lsu_wb_forward_ld_addr,lcam_prev_addr_);
    write_record(*record_,fields::lsu_lcam_rob_r,lcam_prev_rob_);
    lcam_prev_addr_=m.search.valid ? m.search.address : (ports.request.valid ? ports.request.address : 0);
    lcam_prev_rob_=m.search.valid ? m.search.tag.rob : 0;
  }
  m.load_wakeup=boom_lsu::age_priority_pick<kLsq>(wake_eligible&~(blocked_now|old_block1),ld_head);
  m.load_retry=boom_lsu::age_priority_pick<kLsq>(retry_eligible&~(blocked_now|old_block1),ld_head);
  m.store_retry=boom_lsu::age_priority_pick<kLsq>(store_retry_eligible,st_commit);
  m.block2=m.block1;m.block1=blocked_now;m.nacks=nacks;m.block_wakeup=match_without_forward;
  m.release=s.release;m.release_address=input.memory.control.release_address;
  m.speculative[1]=spec1;
  m.speculative[1].valid &= memory_tag_live(spec1.tag,killed,flush);
  m.speculative[1].tag.branch &= static_cast<BranchMask>(~resolved);
  m.speculative[0].valid=s.load_incoming && translated_live && !translated.floating && translated.pdst!=0;
  m.speculative[0].tag=translated;
  m.commit_load_head=false;
  for (unsigned bank=0;bank<kWidth;++bank) {
    if (!test(state_.rob.valid[bank],state_.rob.head)) continue;
    m.commit_load_head=state_.rob.instructions[state_.rob.head*kWidth+bank].decoded.uses_ldq;
    break;
  }
  CHISA_DIAG(
    using namespace ::chisa::diagnostic;
    for(unsigned slot=0;slot<m.clear_store.size();++slot) {
      const auto& done=m.clear_store[slot];
      if(done.valid) sample("lsu","pending_store",state_.cycle,Layer::Internal,Phase::Post,
          {{"slot",slot},{"valid",done.valid},{"due",done.due},
           {"floating",done.floating_data},{"rob",done.tag.rob},
           {"branch",done.tag.branch},{"store",done.tag.store},
           {"generation",done.tag.generation},{"kill",killed},{"resolve",resolved}});
      require("lsu","pending_store_branch",state_.cycle,Layer::Internal,Phase::Post,
          !done.valid || (done.tag.branch & (killed|resolved))==0,
          {{"slot",slot},{"valid",done.valid},{"due",done.due},{"rob",done.tag.rob},
           {"branch",done.tag.branch},{"kill",killed},{"resolve",resolved}});
      require("lsu","pending_store_due",state_.cycle,Layer::Internal,Phase::Post,
          !done.valid || done.due>state_.cycle,
          {{"slot",slot},{"valid",done.valid},{"due",done.due},{"rob",done.tag.rob}});
    }
  );
}
}  // namespace chisa::boom_model::wide
