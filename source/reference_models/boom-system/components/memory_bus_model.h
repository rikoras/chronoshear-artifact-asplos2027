#pragma once
#include "../protocol/memory_bus.h"
#include "../protocol/axi.h"
#include "../protocol/fifo.h"
#include <algorithm>
#include <array>
#include <cstdint>

namespace chisa::boom_system::components {

// 64-bit TileLink-to-AXI transport. Source tags remain outstanding until the
// final reply. Per-AXI-ID FIFO descriptors restore the source and size after
// the downstream interface removes the extra tag bits.
class MemoryBusModel {
 public:
  struct Echo {
    std::uint8_t size=0,source=0,extra_id=0;
    bool operator==(const Echo& o) const { return size==o.size && source==o.source && extra_id==o.extra_id; }
  };
  struct Address {
    bool valid=false,write=false;
    protocol::AxiAddress payload{};
    Echo echo{};
    bool operator==(const Address& o) const { return valid==o.valid && write==o.write && payload==o.payload && echo==o.echo; }
  };
  struct State {
    protocol::Fifo<Address,1> address;
    protocol::Fifo<protocol::AxiWriteData,1> data;
    std::array<protocol::Fifo<Echo,8>,16> read_echo,write_echo;
    std::array<bool,128> outstanding{};
    std::uint8_t a_remaining=0,b_delay=0;
    bool address_sent=false,read_holds_response=false,read_first=false,read_denied=false;
  };
  MemoryBusModel() { compute(); }
  const State& state() const { return state_; }
  const protocol::MbusCouplerOutputs& outputs() const { return output_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return commits_; }
  std::uint64_t skipped_count() const { return skipped_; }
  const protocol::MbusCouplerOutputs& evaluate(const protocol::MbusCouplerInputs& input) {
    input_=input;input_.tl_a.opcode &= 7;input_.tl_a.param &= 7;input_.tl_a.size &= 7;input_.tl_a.source &= 127;
    input_.axi_b.id &= 15;input_.axi_b.response &= 3;input_.axi_r.id &= 15;input_.axi_r.response &= 3;
    pending_=true;compute();return output_;
  }
  void commit(const protocol::MbusCouplerInputs& input) { evaluate(input);commit_evaluated(); }
  void commit_evaluated() {
    if (!pending_) return;
    const auto& i=input_;bool changed=false;
    const bool a_fire=i.tl_a.valid&&output_.tl_a_ready;
    const bool read_reply=i.axi_r.valid&&output_.axi_r_ready;
    const bool write_reply=i.axi_b.valid&&output_.axi_b_ready;
    const bool ar_fire=output_.axi_ar.valid&&i.axi_ar_ready;
    const bool aw_fire=output_.axi_aw.valid&&i.axi_aw_ready;
    const bool w_fire=output_.axi_w.valid&&i.axi_w_ready;
    const unsigned ar_id=output_.axi_ar.id,aw_id=output_.axi_aw.id;
    const unsigned r_id=i.axi_r.id,b_id=i.axi_b.id;
    const auto r_echo=state_.read_echo[r_id].head(),b_echo=state_.write_echo[b_id].head();
    const auto update_echo=[&](auto& queues,bool push,unsigned push_id,bool pop,unsigned pop_id) {
      bool difference=false;
      if (pop && i.reset && queues[pop_id].empty()) pop=false;
      if (push && pop && push_id==pop_id)
        difference=queues[push_id].commit(true,address_output_.echo,true,false);
      else {
        if (push) difference |= queues[push_id].commit(true,address_output_.echo,false,false);
        if (pop) difference |= queues[pop_id].commit(false,{},true,false);
      }
      if (i.reset) for (auto& queue:queues) difference |= queue.commit(false,{},false,true);
      return difference;
    };
    changed |= update_echo(state_.read_echo,ar_fire,ar_id,read_reply&&i.axi_r.last,r_id);
    changed |= update_echo(state_.write_echo,aw_fire,aw_id,write_reply,b_id);
    const bool address_accept=address_input_.valid&&!state_.address.full();
    const bool response_last=(read_reply&&i.axi_r.last)||write_reply;
    const unsigned response_source=read_reply?r_echo.source:b_echo.source;
    if (address_accept) { state_.outstanding[address_input_.echo.source]=!state_.outstanding[address_input_.echo.source];changed=true; }
    if (response_last) { state_.outstanding[response_source]=!state_.outstanding[response_source];changed=true; }
    if (state_.read_first) { const bool denied=i.axi_r.response==3;changed |= denied!=state_.read_denied;state_.read_denied=denied; }
    if (read_reply) { state_.read_holds_response=!i.axi_r.last;state_.read_first=i.axi_r.last;changed=true; }
    const auto delay=std::uint8_t(i.axi_b.valid&&!write_reply?(state_.b_delay+1)&7:0);
    changed |= delay!=state_.b_delay;state_.b_delay=delay;
    if (a_fire) {
      state_.address_sent=!a_last_;
      state_.a_remaining=state_.a_remaining?std::uint8_t(state_.a_remaining-1):a_beats_minus_one_;
      changed=true;
    }
    changed |= flow_commit(state_.address,address_input_,ar_fire||aw_fire,i.reset);
    changed |= flow_commit(state_.data,data_input_,w_fire,i.reset);
    if (i.reset) {
      changed |= state_.address_sent||state_.read_holds_response||!state_.read_first||state_.a_remaining;
      state_.address_sent=state_.read_holds_response=false;state_.read_first=true;state_.a_remaining=0;
      for (auto& occupied:state_.outstanding) { changed |= occupied;occupied=false; }
    }
    active_=changed;if (changed) ++commits_;else ++skipped_;
    pending_=false;compute();
  }
 private:
  template<class T> static bool flow_commit(protocol::Fifo<T,1>& queue,const T& value,bool dequeue,bool reset) {
    const bool empty=queue.empty();
    return queue.commit(value.valid&&!queue.full()&&!(empty&&dequeue),value,dequeue&&!empty,reset);
  }
  static protocol::MbusAxiAw address_channel(const protocol::AxiAddress& a) {
    return {a.valid,std::uint8_t(a.id&15),a.address,a.length,a.size,a.burst,a.lock,a.cache,a.protection,a.qos};
  }
  void compute() {
    const auto& i=input_;const auto& a=i.tl_a;
    const bool put=(a.opcode&4)==0;
    a_beats_minus_one_=put ? std::uint8_t(((1u<<std::min<unsigned>(a.size,6))-1)>>3) : 0;
    const bool first=state_.a_remaining==0;
    a_last_=state_.a_remaining==1 || a_beats_minus_one_==0;
    const bool stall=first&&state_.outstanding[a.source];
    const bool address_ready=!state_.address.full(),data_ready=!state_.data.full();
    address_input_={};address_input_.write=put;
    address_input_.payload.id=a.source;address_input_.payload.address=a.address;
    address_input_.payload.length=std::uint8_t(((1u<<a.size)-1)>>3);
    address_input_.payload.size=std::min<std::uint8_t>(a.size,3);address_input_.payload.burst=1;
    address_input_.payload.cache=std::uint8_t(a.bufferable|(a.modifiable<<1)|(a.readalloc<<2)|(a.writealloc<<3));
    address_input_.payload.protection=std::uint8_t(a.privileged|(!a.secure<<1)|(a.fetch<<2));
    address_input_.echo={a.size,a.source,std::uint8_t(a.source>>4)};
    address_input_.valid=!stall&&a.valid&&(!put || (!state_.address_sent&&data_ready));
    data_input_={};data_input_.valid=!stall&&a.valid&&put&&(state_.address_sent||address_ready);
    data_input_.data=a.data;data_input_.strobe=std::uint8_t(a.mask);data_input_.last=a_last_;
    output_.tl_a_ready=!stall&&(put?((state_.address_sent||address_ready)&&data_ready):address_ready);
    address_output_=state_.address.empty()?address_input_:state_.address.head();
    const auto data=state_.data.empty()?data_input_:state_.data.head();
    const bool address_valid=!state_.address.empty()||address_input_.valid;
    const bool data_valid=!state_.data.empty()||data_input_.valid;
    const unsigned id=address_output_.payload.id&15;
    output_.axi_ar=address_channel(address_output_.payload);output_.axi_aw=output_.axi_ar;
    output_.axi_ar.valid=address_valid&&!address_output_.write&&!state_.read_echo[id].full();
    output_.axi_aw.valid=address_valid&&address_output_.write&&!state_.write_echo[id].full();
    output_.axi_w={data_valid,data.data,data.strobe,data.last};
    const auto& r=state_.read_echo[i.axi_r.id].head();const auto& b=state_.write_echo[i.axi_b.id].head();
    const bool r_wins=(i.axi_r.valid&&state_.b_delay!=7)||state_.read_holds_response;
    output_.axi_r_ready=i.tl_d_ready&&r_wins;output_.axi_b_ready=i.tl_d_ready&&!r_wins;
    output_.tl_d={};output_.tl_d.valid=r_wins?i.axi_r.valid:i.axi_b.valid;
    output_.tl_d.opcode=r_wins?1:0;output_.tl_d.size=r_wins?r.size:b.size;output_.tl_d.source=r_wins?r.source:b.source;
    output_.tl_d.data=i.axi_r.data;
    output_.tl_d.denied=r_wins?(state_.read_first?i.axi_r.response==3:state_.read_denied):i.axi_b.response!=0;
    output_.tl_d.corrupt=r_wins&&(i.axi_r.response!=0||output_.tl_d.denied);
  }
  State state_{};
  protocol::MbusCouplerInputs input_{};
  protocol::MbusCouplerOutputs output_{};
  Address address_input_{},address_output_{};
  protocol::AxiWriteData data_input_{};
  std::uint64_t commits_=0,skipped_=0;
  std::uint8_t a_beats_minus_one_=0;
  bool pending_=false,active_=false,a_last_=true;
};
}
