#pragma once
#include "../common/pipeline_uop.h"
#include "../common/integer_divider.h"
#include <array>
#include <cstdint>

namespace chisa::boom_model::wide {
// Small's StageUop lives only through RegisterRead. Operands have separate
// register lifetimes; stage 1 operands are the final record's actual fields.
struct ReadStage {
  StageUop uop;
  std::uint64_t result = 0;
};
// Small's compact Wb, with Large's branch mask and physical port timing.
// CSR carries its operand in data until the CSR response is computed.
struct Writeback {
  std::uint64_t data = 0;
  std::uint32_t imm_packed = 0;   // partition-cut lanes of the unit's stage register
  std::uint16_t br_mask = 0;
  std::uint8_t rob = 0, pdst = 0, command = 0, flags = 0, dst_rtype = 0;
  bool bypassable = false;
  enum : std::uint8_t { WritesInteger=1, Csr=2, Multiply=4, IsAmo=8, UsesStq=16 };
  bool has(unsigned flag) const { return (flags&flag)!=0; }
};
static_assert(sizeof(Writeback)==24);
// Only branch resolution retains target/FTQ/recovery information, as in
// Small's BrStage/BrPayload. No operands, result or full StageUop here.
struct BranchEntry {
  std::uint64_t target = 0;
  std::int32_t offset = 0;
  std::uint16_t br_mask = 0;
  std::uint8_t rob_idx = 0, tag = 0, ftq_idx = 0, ldq_idx = 0, stq_idx = 0;
  std::uint8_t pc_lob = 0, pc_select = 0;
  bool valid = false, mispredict = false, taken = false;
  bool is_br = false, is_jalr = false, is_rvc = false, edge_inst = false;
  // Partition-cut lanes: the b2 register mirrors the whole brinfo entry.
  bool is_jal = false, is_sfb = false;
  std::uint64_t jalr_target = 0;
};
static_assert(sizeof(BranchEntry)==40);
struct CsrPort {
  std::uint64_t operand = 0, read_data = 0;
  std::uint16_t address = 0;
  std::uint8_t rob_idx = 0, command = 0;
  bool valid = false;
};
static_assert(sizeof(CsrPort)==24);
struct DividerControl {
  std::uint8_t count = 0, jump = 0;
  bool is_high = false, doubleword = false;
  std::uint64_t lhs = 0, rhs = 0;
};
struct ExecutionImage {
  std::array<std::array<ReadStage,2>,boomcfg::INT_ISSUE_WIDTH> read{};
  std::array<std::uint8_t,boomcfg::INT_ISSUE_WIDTH> read_valids{};
  std::array<std::uint64_t,boomcfg::INT_ISSUE_WIDTH> rrd_rs1{}, rrd_rs2{};
  // Two one-stage ALUs and the three-stage ALU/MUL port. Iterate only active
  // bits; no capacity scan and no generic pending instruction queue.
  std::array<Writeback,boomcfg::INT_ISSUE_WIDTH-1> alu{};
  std::array<Writeback,3> multiply{};
  std::array<std::uint8_t,boomcfg::INT_ISSUE_WIDTH> unit_valids{};
  Writeback& wb(unsigned port,unsigned stage) { return port==boomcfg::MUL_PORT ? multiply[stage] : alu[port<boomcfg::MUL_PORT ? port : port-1]; }
  const Writeback& wb(unsigned port,unsigned stage) const { return port==boomcfg::MUL_PORT ? multiply[stage] : alu[port<boomcfg::MUL_PORT ? port : port-1]; }
  std::array<BranchEntry,boomcfg::INT_ISSUE_WIDTH> brinfo{};
  BranchEntry branch_redirect;
  CsrPort csr_port;
  DividerControl divider;
  Writeback divider_wb;
  bool divider_response_fired = false;
  bool retired_r = false, exception_r = false;
};
}  // namespace chisa::boom_model::wide
