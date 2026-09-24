#pragma once
#include "../protocol/axi.h"
#include "../protocol/fifo.h"
#include <cstdint>
#include <stdexcept>

namespace chisa::boom_system::components {

// Five independent depth-two channel queues. All outputs are read before a
// commit; no generated module, clock toggling or whole-state snapshot is used.
class AxiBufferModel {
 public:
  struct State {
    protocol::Fifo<protocol::AxiAddress,2> aw,ar;
    protocol::Fifo<protocol::AxiWriteData,2> w;
    protocol::Fifo<protocol::AxiWriteResponse,2> b;
    protocol::Fifo<protocol::AxiReadResponse,2> r;
  };
  explicit AxiBufferModel(unsigned address_bits=32)
      : address_mask_(address_bits==32 ? UINT32_MAX : UINT32_MAX>>1) {
    if (address_bits!=31 && address_bits!=32) throw std::invalid_argument("AXI address width");
    refresh();
  }
  const State& state() const { return state_; }
  const protocol::AxiStageOutputs& outputs() const { return outputs_; }
  bool active() const { return active_; }
  std::uint64_t eval_count() const { return commits_; }
  std::uint64_t skipped_count() const { return skipped_; }
  const protocol::AxiStageOutputs& evaluate(const protocol::AxiStageInputs& input) {
    pending_=input;pending_valid_=true;
    return outputs_;
  }
  void commit(const protocol::AxiStageInputs& input) { evaluate(input);commit_evaluated(); }
  void commit_evaluated() {
    if (!pending_valid_) return;
    const auto& i=pending_;const auto o=outputs_;
    auto address=[&](protocol::AxiAddress a) {
      a.address &= address_mask_;a.id &= 15;a.size &= 7;a.burst &= 3;
      a.cache &= 15;a.protection &= 7;a.qos &= 15;return a;
    };
    auto b=i.out_b;b.id &= 15;b.response &= 3;
    auto r=i.out_r;r.id &= 15;r.response &= 3;
    bool changed=state_.aw.commit(i.in_aw.valid&&o.in_aw_ready,address(i.in_aw),o.out_aw.valid&&i.out_aw_ready,i.reset);
    changed |= state_.ar.commit(i.in_ar.valid&&o.in_ar_ready,address(i.in_ar),o.out_ar.valid&&i.out_ar_ready,i.reset);
    changed |= state_.w.commit(i.in_w.valid&&o.in_w_ready,i.in_w,o.out_w.valid&&i.out_w_ready,i.reset);
    changed |= state_.b.commit(i.out_b.valid&&o.out_b_ready,b,o.in_b.valid&&i.in_b_ready,i.reset);
    changed |= state_.r.commit(i.out_r.valid&&o.out_r_ready,r,o.in_r.valid&&i.in_r_ready,i.reset);
    active_=changed;if (changed) ++commits_;else ++skipped_;
    pending_valid_=false;refresh();
  }
 private:
  void refresh() {
    outputs_.in_aw_ready=!state_.aw.full();outputs_.out_aw=state_.aw.head();outputs_.out_aw.valid=!state_.aw.empty();
    outputs_.in_ar_ready=!state_.ar.full();outputs_.out_ar=state_.ar.head();outputs_.out_ar.valid=!state_.ar.empty();
    outputs_.in_w_ready=!state_.w.full();outputs_.out_w=state_.w.head();outputs_.out_w.valid=!state_.w.empty();
    outputs_.out_b_ready=!state_.b.full();outputs_.in_b=state_.b.head();outputs_.in_b.valid=!state_.b.empty();
    outputs_.out_r_ready=!state_.r.full();outputs_.in_r=state_.r.head();outputs_.in_r.valid=!state_.r.empty();
  }
  State state_{};
  protocol::AxiStageInputs pending_{};
  protocol::AxiStageOutputs outputs_{};
  std::uint32_t address_mask_;
  std::uint64_t commits_=0,skipped_=0;
  bool pending_valid_=false,active_=false;
};
}  // namespace chisa::boom_system::components
