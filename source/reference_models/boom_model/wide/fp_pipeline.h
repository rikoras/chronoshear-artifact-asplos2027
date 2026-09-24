#pragma once
#include "../common/pipeline_uop.h"
#include "../common/fp_wrapper.h"
#include "../common/branch_flow_queue.h"
#include <array>
#include <cstdint>

namespace chisa::boom_model::wide {
struct FpTag {
  std::uint16_t br_mask=0,fu_code=0;
  std::uint8_t rob=0,pdst=0,stq_idx=0,uopc=0,dst_rtype=0,flags=0;
  bool is_amo() const { return flags&1u; }
  bool uses_stq() const { return flags&2u; }
  static FpTag from(const StageUop& u) {
    return {u.br_mask,u.fu_code,u.rob,u.pdst,u.stq_idx,u.uopc,u.dst_rtype,
            static_cast<std::uint8_t>(unsigned(u.is_amo())|unsigned(u.uses_stq())<<1)};
  }
  static FpTag from(const MicroOp& u) {
    return {u.br_mask,u.fu_code,u.rob_idx,u.pdst,u.stq_idx,u.uopc,u.dst_rtype,
            static_cast<std::uint8_t>(unsigned(u.is_amo)|unsigned(u.uses_stq)<<1)};
  }
};
struct FpReadTag : FpTag {
  std::uint32_t imm_packed=0;
  static FpReadTag from(const StageUop& u) {
    FpReadTag r;static_cast<FpTag&>(r)=FpTag::from(u);r.imm_packed=u.imm_packed;return r;
  }
};
struct FpValue {
  bool valid = false;
  FpTag uop;
  std::uint64_t data = 0, rec_lo = 0;
  std::uint8_t flags = 0, rec_hi = 0;
};
struct FpPending {
  FpValue value;
  std::uint64_t due = 0;
  bool external = false;
};
struct FpReadStage {
  bool valid = false;
  FpReadTag uop;
  std::array<std::uint8_t,3> addresses{};
  std::array<std::uint64_t,3> rec_lo{};
  std::uint8_t rec_hi = 0;
};
struct FpDivide {
  FpValue value;
  std::uint64_t due = 0, a = 0, b = 0;
  std::uint8_t hi = 0, rounding = 0, cycles = 0;
  bool sqrt = false, external = false;
};
struct FpModelResponse {
  // A connected result is produced by the independent model's cold FPU,
  // never by sampling the RTL consumer.
  bool connected = false, valid = false;
  std::uint64_t rec_lo = 0;
  std::uint8_t rec_hi = 0, flags = 0;
};
struct FloatingInputs {
  FpModelResponse fixed, divide;
  bool divide_ready = false;
};
struct FloatingPorts {
  FpReadStage fixed_request;
  std::uint8_t rounding = 0;
  bool divide_valid = false, divide_response_ready = false;
  FpDivide divide_request;
  FpValue main_writeback, long_writeback, integer_writeback, store_data;
};
struct FloatingImage {
  std::array<FpReadStage,2> read{};
  FpWrapperUop wrapper_uops[4]{};
  bool wrapper_valids[4]{};
  std::array<FpPending,10> fixed{};
  std::array<FpPending,5> from_integer_pipe{};
  std::array<FpDivide,3> divide_pipe{};
  FpDivide divide_buffer, divide_active;
  FpValue divide_output;
  bool divide_killed = false, divide_issue_mask = false;
  // Hardware queue depths. No compacted functional queue alongside them.
  BranchFlowQueue<FpValue,7> to_integer;
  BranchFlowQueue<FpValue,3> to_store;
  BranchFlowQueue<FpValue,5> from_integer;
  FpValue main_writeback, long_writeback;
  std::array<FpTag,2> integer_uops{};
  std::uint8_t integer_valids = 0;
  std::uint64_t integer_operand = 0;
  std::uint8_t integer_rounding = 0, integer_type = 0, integer_tag = 0;
  bool integer_wflags = false;
  std::uint64_t ifpu_rec_lo = 0;
  std::uint8_t ifpu_rec_hi = 0;
  bool queue_words_changed=true,divide_buffer_changed=true,divide_output_changed=true;
  bool divide_active_changed=true,ifpu_changed=true;
};
}  // namespace chisa::boom_model::wide
