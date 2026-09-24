#pragma once
// Four software coherence transactions sharing a broadcast probe channel.
// Payloads live in their transaction FIFO; response tags carry pass/drop/
// grant transformations across the memory bus. No RTL evaluator is used.
#include <array>
#include <cstdint>
#include "../protocol/coherence.h"
#include "../protocol/fifo.h"

namespace chisa::boom_system::components {
class CoherenceModel {
 public:
  struct Beat {
    std::uint8_t mask=0;std::uint64_t data=0;
    bool operator==(const Beat& other) const {return mask==other.mask && data==other.data;}
  };
  struct Tracker {
    bool got_e=false,sent_d=false,shared=false;
    bool probe_pending=false;
    protocol::MbusTlA request{};
    protocol::Fifo<Beat,8> data;
  };
  struct Arbiter {std::uint8_t remaining=0,owner=0;};
  struct State {
    std::array<Tracker,4> trackers;
    Arbiter memory_a,tile_d;
    std::uint8_t a_remaining=0,d_remaining=0,d_trackers=0;
    bool probe_valid=false;
    std::uint32_t probe_line=0;
    std::uint8_t probe_permissions=0;
  };
  explicit CoherenceModel(unsigned cache_source_begin=16,unsigned cache_sources=3)
      : cache_source_begin_(cache_source_begin),cache_sources_(cache_sources) { refresh(last_inputs_); }
  const State& state() const { return state_; }
  const protocol::CoherenceManagerOutputs& outputs() const { return outputs_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return eval_count_; }
  std::uint64_t skipped_count() const { return skipped_count_; }
  const protocol::CoherenceManagerOutputs& evaluate(const protocol::CoherenceManagerInputs& input) {
    pending_=input;pending_valid_=true;
    if(input!=applied_) { refresh(input);applied_=input; }
    return outputs_;
  }
  void commit_evaluated() {
    if(!pending_valid_) return;
    pending_valid_=false;
    if(!active_ && pending_==last_inputs_) {++skipped_count_;return;}
    if(pending_!=last_inputs_) drain_=2;
    edge(pending_);
    if(drain_) --drain_;
    refresh(pending_);last_inputs_=applied_=pending_;++eval_count_;
    active_=drain_ || state_.probe_valid || state_.a_remaining || state_.d_remaining ||
      state_.memory_a.remaining || state_.tile_d.remaining;
    for(const auto& t:state_.trackers) active_|=!t.got_e || !t.sent_d || !t.data.empty();
  }
 private:
  struct Choice {unsigned allowed=0,selected=0,beats=0;bool valid=false;};
  struct Comb {
    Choice memory_a,tile_d;
    std::array<bool,4> accept{},pop{},probe_nack{},probe_data_ack{},shared{},done_d{};
    unsigned a_select=0,d_select=0;
    bool first_a=false,first_d=false,normal_d_fire=false;
    bool probe_request=false,probe_needed=false;
    unsigned normal_d_beats=0;
  } comb_{};
  static unsigned first(unsigned mask) {unsigned index=0;while(mask && !(mask&1)) {mask>>=1;++index;}return index;}
  static unsigned beats(unsigned size,bool data) {return data && size>3 ? ((1u<<(size&7))-1)/8 : 0;}
  static Choice choose(const Arbiter& arb,unsigned clients,unsigned valids,const unsigned* lengths) {
    Choice result;
    if(arb.remaining) result.allowed=arb.owner;
    else for(unsigned i=0;i<clients;++i) {result.allowed|=1u<<i;if(valids&(1u<<i)) break;}
    result.selected=arb.remaining?arb.owner:(result.allowed&valids);
    result.valid=(result.allowed&valids)!=0;
    for(unsigned i=0;i<clients;++i) if(result.selected&(1u<<i)) result.beats|=lengths[i];
    return result;
  }
  static void advance(Arbiter& arb,const Choice& choice,bool ready,bool reset) {
    const bool idle=arb.remaining==0;
    if(idle && ready) arb.remaining=choice.beats&7;
    else if(choice.valid && ready) arb.remaining=(arb.remaining-1)&7;
    if(idle) arb.owner=choice.selected;
    if(reset) arb={};
  }
  static void count_beat(std::uint8_t& count,bool fire,unsigned initial,bool reset) {
    if(fire) count=count==0?initial&7:(count-1)&7;
    if(reset) count=0;
  }
  static protocol::MbusTlA request(protocol::MbusTlA value) {
    value.opcode&=7;value.param&=7;value.size&=7;value.source&=31;value.mask&=255;value.data_hi=0;
    return value;
  }
  static bool needs_exclusive(const protocol::MbusTlA& a) {
    switch(a.opcode) {case 4:return false;case 5:return a.param==1;case 6:case 7:return a.param==1 || a.param==2;default:return true;}
  }
  void refresh(const protocol::CoherenceManagerInputs& in) {
    comb_={};outputs_={};auto& c=comb_;auto& o=outputs_;const auto& s=state_;
    const auto a=request(in.tile_a);const auto& release=in.tile_c;
    c.first_a=s.a_remaining==0;c.first_d=s.d_remaining==0;
    unsigned free=0,line_match=0,ready=0,response_match=0,c_match=0,c_source=0;
    for(unsigned i=0;i<4;++i) {
      const auto& t=s.trackers[i];const bool idle=t.got_e && t.sent_d;
      if(idle) free|=1u<<i;
      if((t.request.address>>6)==(a.address>>6)) line_match|=1u<<i;
      if((idle || !c.first_a) && !t.data.full()) ready|=1u<<i;
      if(!t.sent_d && t.request.source==(in.mbus_d.source&31)) response_match|=1u<<i;
      if((t.request.address>>6)==(release.address>>6)) {c_match|=1u<<i;c_source|=t.request.source;}
    }
    c.a_select=line_match?line_match:(free?(1u<<first(free)):0);
    const bool a_allowed=!c.first_a || !s.probe_valid;
    o.tile_a_ready=a_allowed && (c.a_select&ready)!=0;
    c.probe_request=a.valid && c.first_a && o.tile_a_ready;
    c.probe_needed=a.source<cache_source_begin_ || a.source>=cache_source_begin_+cache_sources_;
    for(unsigned i=0;i<4;++i) c.accept[i]=a.valid && a_allowed && ((c.a_select&ready)&(1u<<i));
    o.tile_b.valid=s.probe_valid;o.tile_b.opcode=6;o.tile_b.param=s.probe_permissions;
    o.tile_b.size=6;o.tile_b.source=cache_source_begin_;o.tile_b.address=s.probe_line<<6;o.tile_b.mask=255;
    o.tile_e_ready=true;

    // Recover a coherent response from the transformation tag.
    const auto& d=in.mbus_d;const unsigned transform=(d.source>>5)&3;
    const bool drop=transform==1,has_data=(d.opcode&1)!=0;
    c.d_select=c.first_d?response_match:s.d_trackers;
    protocol::CoherentTlD normal;
    normal.valid=d.valid && !drop;normal.opcode=d.opcode&7;normal.param=d.param&3;
    normal.size=d.size&7;normal.source=d.source&31;normal.denied=d.denied;normal.data=d.data;normal.corrupt=d.corrupt;
    for(unsigned i=0;i<4;++i) if(c.d_select&(1u<<i)) normal.sink|=i;
    if(transform>=2) {normal.opcode=has_data?5:6;normal.param=has_data?(transform==3?0:1):0;}
    c.normal_d_beats=beats(normal.size,has_data);
    protocol::CoherentTlD ack;
    ack.valid=release.valid && release.opcode==6;ack.opcode=6;ack.size=release.size&7;ack.source=release.source&31;
    const unsigned d_lengths[]={0,c.normal_d_beats};
    c.tile_d=choose(s.tile_d,2,(ack.valid?1:0)|(normal.valid?2:0),d_lengths);
    if(c.tile_d.selected&1) o.tile_d=ack;
    if(c.tile_d.selected&2) o.tile_d=normal;
    o.tile_d.valid=c.tile_d.valid;
    const bool normal_ready=in.tile_d_ready && (c.tile_d.allowed&2);
    o.mbus_d_ready=normal_ready || drop;
    c.normal_d_fire=normal.valid && normal_ready;
    const bool d_last=s.d_remaining==1 || c.normal_d_beats==0;
    for(unsigned i=0;i<4;++i) {
      c.done_d[i]=(c.d_select&(1u<<i)) && c.normal_d_fire && (has_data || transform<2) && d_last;
      c.probe_data_ack[i]=(c.d_select&(1u<<i)) && d.valid && o.mbus_d_ready && drop;
    }

    // A release carrying data becomes a memory write. Probe data writes are
    // tagged for acknowledgement consumption at this hub.
    protocol::MbusTlA write;
    write.valid=release.valid && (release.opcode==5 || release.opcode==7);
    write.opcode=0;write.size=release.size&7;
    write.source=((release.opcode==7?2:1)<<5)|(release.opcode==7?(release.source&31):c_source);
    write.address=release.address;write.mask=write.size>=3?255:((1u<<(1u<<write.size))-1)<<(write.address&7);write.data=release.data;
    // A coherence writeback is a privileged, secure cacheable data write.
    write.bufferable=write.modifiable=write.readalloc=write.writealloc=true;
    write.privileged=write.secure=true;write.fetch=false;
    unsigned a_valids=write.valid?1:0;unsigned lengths[5]={beats(write.size,true)};
    std::array<protocol::MbusTlA,4> requests;
    for(unsigned i=0;i<4;++i) {
      const auto& t=s.trackers[i];auto& output=requests[i];output=t.request;
      const bool acquire=output.opcode==6 || output.opcode==7;
      output.valid=!t.data.empty() && !t.probe_pending;
      if(acquire) {output.opcode=4;output.param=0;output.source|=(t.shared?2:3)<<5;}
      output.mask=t.data.head().mask;output.data=t.data.head().data;output.corrupt=false;
      if(output.valid) a_valids|=1u<<(i+1);
      lengths[i+1]=beats(output.size,output.opcode<4);
    }
    c.memory_a=choose(s.memory_a,5,a_valids,lengths);
    if(c.memory_a.selected&1) o.mbus_a=write;
    for(unsigned i=0;i<4;++i) {
      if(c.memory_a.selected&(1u<<(i+1))) o.mbus_a=requests[i];
      c.pop[i]=requests[i].valid && in.mbus_a_ready && (c.memory_a.allowed&(1u<<(i+1)));
    }
    o.mbus_a.valid=c.memory_a.valid;
    o.tile_c_ready=release.opcode==4 || (release.opcode==6 ? in.tile_d_ready && (c.tile_d.allowed&1) : in.mbus_a_ready && (c.memory_a.allowed&1));
    const bool c_fire=release.valid && o.tile_c_ready;
    for(unsigned i=0;i<4;++i) {
      c.probe_nack[i]=c_fire && (c_match&(1u<<i)) && release.opcode==4;
      c.shared[i]=c_fire && (c_match&(1u<<i)) && (release.opcode==4 || release.opcode==5) && (release.param==0 || release.param==4);
    }
  }
  void edge(const protocol::CoherenceManagerInputs& in) {
    auto& s=state_;const auto& c=comb_;const auto a=request(in.tile_a);
    if(c.first_d) s.d_trackers=c.d_select;
    if(outputs_.tile_b.valid && in.tile_b_ready) s.probe_valid=false;
    if(c.probe_request) {s.probe_valid=c.probe_needed;s.probe_line=a.address>>6;s.probe_permissions=needs_exclusive(a)?2:1;}
    for(unsigned i=0;i<4;++i) {
      auto& t=s.trackers[i];const bool old_probe=t.probe_pending;
      if(c.accept[i] && c.first_a) {t.request=a;t.sent_d=t.shared=false;t.got_e=a.opcode!=6 && a.opcode!=7;t.probe_pending=true;}
      if(c.probe_request && first(c.a_select)==i) t.probe_pending=c.probe_needed;
      if(c.done_d[i]) t.sent_d=true;
      if(in.tile_e.valid && (in.tile_e.sink&3)==i) t.got_e=true;
      if(c.probe_nack[i] || c.probe_data_ack[i]) t.probe_pending=(unsigned(old_probe)-c.probe_nack[i]-c.probe_data_ack[i])&1;
      if(c.shared[i]) t.shared=true;
      t.data.commit(c.accept[i],Beat{static_cast<std::uint8_t>(a.mask),a.data},c.pop[i],in.reset);
      if(in.reset) {t.got_e=t.sent_d=true;t.request.address=i*64;}
    }
    advance(s.memory_a,c.memory_a,in.mbus_a_ready,in.reset);
    advance(s.tile_d,c.tile_d,in.tile_d_ready,in.reset);
    count_beat(s.a_remaining,a.valid && outputs_.tile_a_ready,beats(a.size,a.opcode<4),in.reset);
    count_beat(s.d_remaining,c.normal_d_fire,c.normal_d_beats,in.reset);
    if(in.reset) s.probe_valid=false;
  }
  State state_{};
  unsigned cache_source_begin_,cache_sources_,drain_=0;
  protocol::CoherenceManagerInputs pending_{},applied_{},last_inputs_{};
  protocol::CoherenceManagerOutputs outputs_{};
  bool pending_valid_=false,active_=false;
  std::uint64_t eval_count_=0,skipped_count_=0;
};
} // namespace chisa::boom_system::components
