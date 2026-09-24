#pragma once
#include "../protocol/axi.h"
#include "../protocol/fifo.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>

namespace chisa::boom_system::components {

// Convert a burst to single-beat requests, retaining the original request
// until its last fragment. A one-entry flow buffer decouples each request
// channel. Responses carry an internal last-fragment marker until reassembly.
class AxiFragmenterModel {
 public:
  struct Cursor { bool busy=false;std::uint32_t address=0;std::uint8_t length=0; };
  struct State {
    protocol::Fifo<protocol::AxiAddress,1> ar,aw;
    protocol::Fifo<protocol::AxiWriteData,1> w;
    Cursor read,write;
    std::array<std::uint8_t,16> response_error{};
    bool write_length_latched=false;
    std::uint16_t write_beats=0;
  };
  explicit AxiFragmenterModel(unsigned address_bits=32)
      : address_mask_(address_bits==32 ? UINT32_MAX : UINT32_MAX>>1) {
    if (address_bits!=31 && address_bits!=32) throw std::invalid_argument("AXI address width");
    compute();
  }
  const State& state() const { return state_; }
  const protocol::AxiStageOutputs& outputs() const { return outputs_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return commits_; }
  std::uint64_t skipped_count() const { return skipped_; }
  const protocol::AxiStageOutputs& evaluate(const protocol::AxiStageInputs& input) {
    pending_=input;
    pending_.in_ar=normalize(input.in_ar);pending_.in_aw=normalize(input.in_aw);
    pending_.out_b.id &= 15;pending_.out_b.response &= 3;
    pending_.out_r.id &= 15;pending_.out_r.response &= 3;
    pending_valid_=true;compute();return outputs_;
  }
  void commit(const protocol::AxiStageInputs& input) { evaluate(input);commit_evaluated(); }
  void commit_evaluated() {
    if (!pending_valid_) return;
    const auto& i=pending_;const auto o=outputs_;
    const bool ar_fire=o.out_ar.valid&&i.out_ar_ready,aw_fire=o.out_aw.valid&&i.out_aw_ready;
    const bool w_fire=o.out_w.valid&&i.out_w_ready,b_fire=i.out_b.valid&&o.out_b_ready;
    bool changed=flow_commit(state_.ar,i.in_ar,ar_fire&&read_last_,i.reset);
    changed |= flow_commit(state_.aw,i.in_aw,aw_fire&&write_last_,i.reset);
    changed |= flow_commit(state_.w,i.in_w,w_fire,i.reset);
    if (ar_fire) { state_.read={ !read_last_,read_next_address_,read_next_length_ };changed=true; }
    if (aw_fire) { state_.write={ !write_last_,write_next_address_,write_next_length_ };changed=true; }
    const bool latched=(state_.write_length_latched || (write_length_valid_&&write_idle_)) && !aw_fire;
    const auto beats=std::uint16_t(write_todo_-unsigned(w_fire));
    changed |= latched!=state_.write_length_latched || beats!=state_.write_beats;
    state_.write_length_latched=latched;state_.write_beats=beats;
    if (b_fire) {
      auto& error=state_.response_error[i.out_b.id];
      const auto next=std::uint8_t(i.out_b.echo_real_last ? 0 : error|i.out_b.response);
      changed |= error!=next;error=next;
    }
    if (i.reset) {
      changed |= state_.read.busy || state_.write.busy || state_.write_length_latched || state_.write_beats;
      state_.read.busy=state_.write.busy=state_.write_length_latched=false;state_.write_beats=0;
      for (auto& error:state_.response_error) { changed |= error!=0;error=0; }
    }
    active_=changed;if (changed) ++commits_;else ++skipped_;
    pending_valid_=false;compute();
  }
 private:
  template<class T> static bool flow_commit(protocol::Fifo<T,1>& queue,const T& input,bool dequeue,bool reset) {
    const bool empty=queue.empty();
    return queue.commit(input.valid&&!queue.full()&&!(empty&&dequeue),input,dequeue&&!empty,reset);
  }
  protocol::AxiAddress normalize(protocol::AxiAddress a) const {
    a.address &= address_mask_;a.id &= 15;a.size &= 7;a.burst &= 3;
    a.cache &= 15;a.protection &= 7;a.qos &= 15;return a;
  }
  protocol::AxiAddress fragment(const protocol::AxiAddress& a,const Cursor& cursor,
                                bool& last,std::uint32_t& next_address,std::uint8_t& next_length) const {
    const auto address=cursor.busy?cursor.address:a.address;
    const auto length=cursor.busy?cursor.length:a.length;
    last=length==0;next_length=std::uint8_t(length-1);
    const auto stride=std::uint32_t(1)<<a.size;
    next_address=(address+stride)&address_mask_;
    if (a.burst==0) next_address=address;
    else if (a.burst==2) {
      const auto wrap_mask=(std::uint32_t(a.length)+1)*stride-1;
      next_address=((address&~wrap_mask)|((address+stride)&wrap_mask))&address_mask_;
    }
    auto result=a;result.address=address&~((std::uint32_t(1)<<std::min<unsigned>(a.size,3))-1);
    result.length=0;result.echo_real_last=last;return result;
  }
  void compute() {
    const auto& i=pending_;
    const auto& ar=state_.ar.empty()?i.in_ar:state_.ar.head();
    const auto& aw=state_.aw.empty()?i.in_aw:state_.aw.head();
    const auto& w=state_.w.empty()?i.in_w:state_.w.head();
    const bool ar_valid=!state_.ar.empty()||i.in_ar.valid,aw_valid=!state_.aw.empty()||i.in_aw.valid;
    const bool w_valid=!state_.w.empty()||i.in_w.valid;
    outputs_.in_ar_ready=!state_.ar.full();outputs_.in_aw_ready=!state_.aw.full();outputs_.in_w_ready=!state_.w.full();
    outputs_.out_ar=fragment(ar,state_.read,read_last_,read_next_address_,read_next_length_);outputs_.out_ar.valid=ar_valid;
    outputs_.out_aw=fragment(aw,state_.write,write_last_,write_next_address_,write_next_length_);
    write_idle_=state_.write_beats==0;write_length_valid_=aw_valid&&!state_.write_length_latched;
    write_todo_=write_idle_?unsigned(write_length_valid_):state_.write_beats;
    outputs_.out_aw.valid=aw_valid&&(write_idle_||state_.write_length_latched);
    outputs_.out_w=w;outputs_.out_w.valid=w_valid&&(!write_idle_||write_length_valid_);outputs_.out_w.last=write_todo_==1;
    outputs_.in_b=i.out_b;outputs_.in_b.valid=i.out_b.valid&&i.out_b.echo_real_last;
    outputs_.in_b.response |= state_.response_error[i.out_b.id];outputs_.in_b.echo_real_last=false;
    outputs_.out_b_ready=i.in_b_ready||!i.out_b.echo_real_last;
    outputs_.in_r=i.out_r;outputs_.in_r.last=i.out_r.last&&i.out_r.echo_real_last;outputs_.in_r.echo_real_last=false;
    outputs_.out_r_ready=i.in_r_ready;
  }
  State state_{};
  protocol::AxiStageInputs pending_{};
  protocol::AxiStageOutputs outputs_{};
  std::uint32_t address_mask_,read_next_address_=0,write_next_address_=0;
  std::uint8_t read_next_length_=0,write_next_length_=0;
  std::uint16_t write_todo_=0;
  std::uint64_t commits_=0,skipped_=0;
  bool pending_valid_=false,active_=false,read_last_=true,write_last_=true,write_idle_=true,write_length_valid_=false;
};
}  // namespace chisa::boom_system::components
