#include "core.h"
#include "record_fields.h"
#include "../common/diagnostic_monitor.h"
#include "diagnostics/record_dump.h"

namespace chisa::boom_model::wide {
namespace {
bool alu(std::uint16_t fu) { return fu==FU_ALU || fu==FU_JMP || fu==FU_CSR; }
// functional-unit.scala encodeVirtualAddress for the 40-bit extended address.
std::uint64_t encode_virtual_address(std::uint64_t ea) {
  const auto a=static_cast<std::int64_t>(ea)>>39;
  const bool msb=(a==0 || a==-1) ? ((ea>>39)&1u) : !((ea>>38)&1u);
  return (std::uint64_t(msb)<<39)|(ea&((UINT64_C(1)<<39)-1));
}
Writeback writeback(const StageUop& s,const MicroOp& u,std::uint64_t data) {
  Writeback w;w.data=data;w.br_mask=s.br_mask;w.rob=s.rob;w.pdst=s.pdst;w.command=s.csr_cmd;
  w.imm_packed=s.imm_packed;w.dst_rtype=s.dst_rtype;w.bypassable=s.bypassable();
  if (u.ldst_val && s.dst_rtype==RT_FIX && s.pdst) w.flags |= Writeback::WritesInteger;
  if (s.fu_code&FU_CSR) w.flags |= Writeback::Csr;
  if (s.fu_code&FU_MUL) w.flags |= Writeback::Multiply;
  if (s.is_amo()) w.flags |= Writeback::IsAmo;
  if (s.uses_stq()) w.flags |= Writeback::UsesStq;
  return w;
}
}
DividerStateView Core::divider_state() {
  auto& d=state_.execution.divider;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  auto& r=record_->r.coreCsrExe;
  return {r.div_div_state,d.count,d.jump,r.div_div_divisor_2,
          r.div_div_remainder_3,r.div_div_neg_out,d.is_high,d.doubleword,
          d.lhs,d.rhs,r.div_div_divisor_1,&r.div_div_remainder[1]};
#else
  auto& r=record_->r.coreMisc;
  return {r.jmp_unit_div_div_state,d.count,d.jump,r.jmp_unit_div_div_divisor_2,
          r.jmp_unit_div_div_remainder_3,r.jmp_unit_div_div_neg_out,d.is_high,d.doubleword,
          d.lhs,d.rhs,r.jmp_unit_div_div_divisor_1,&r.jmp_unit_div_div_remainder[1]};
#endif
}
BranchMask Core::pending_b1_mispredict_mask() const {
  BranchMask mask=0;const auto& r=record_->r.coreMisc;
  for (unsigned port=0;port<kWidth;++port)
    if (r.brinfos_valid[port] && r.brinfos_mispredict[port]) mask |= BranchMask{1}<<r.brinfos_uop_br_tag[port];
  return mask;
}
const BranchEntry* Core::oldest_b1_mispredict() const {
  const BranchEntry* result=nullptr;const auto& e=state_.execution;const auto& r=record_->r.coreMisc;
  const unsigned head=RobGeometry::encode(state_.rob.head,0);
  for (unsigned port=0;port<kWidth;++port) {
    const auto& b=e.brinfo[port];
    if (!r.brinfos_valid[port] || !r.brinfos_mispredict[port]) continue;
    if (!result || ((unsigned(b.rob_idx)-head)&kRobMask)<((unsigned(result->rob_idx)-head)&kRobMask)) result=&b;
  }
  return result;
}
void Core::preview_branch(BranchUpdate& branch, Redirect& redirect) const {
  branch={};redirect={};
  const auto& r=record_->r.coreMisc;
  for (unsigned port=0;port<kWidth;++port) {
    if (!r.brinfos_valid[port]) continue;
    const BranchMask mask=BranchMask{1}<<r.brinfos_uop_br_tag[port];
    branch.resolved |= mask;
    if (r.brinfos_mispredict[port]) branch.mispredicted |= mask;
  }
  const auto& b2=state_.execution.branch_redirect;
  if (b2.valid && b2.mispredict) {
    branch.redirect=true;branch.tag=b2.tag;branch.rob=b2.rob_idx;
    branch.load_tail=b2.ldq_idx;branch.store_tail=b2.stq_idx;branch.surviving=b2.br_mask;
    redirect={true,true,b2.taken,b2.is_br,b2.is_rvc,b2.edge_inst,b2.ftq_idx,b2.pc_lob,b2.pc_select,b2.offset,b2.target};
  }
}
std::array<std::uint16_t,kWidth> Core::integer_availability(bool i2f_ready) const {
  const auto& e=state_.execution;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  bool busy=record_->r.coreCsrExe.div_div_state!=0;
#else
  bool busy=record_->r.coreMisc.jmp_unit_div_div_state!=0;
#endif
  for (unsigned active=e.read_valids[boomcfg::DIV_PORT];active;active&=active-1)
    busy |= (e.read[boomcfg::DIV_PORT][__builtin_ctz(active)].uop.fu_code&FU_DIV)!=0;
  std::array<std::uint16_t,kWidth> result{};
  for(unsigned port=0;port<kWidth;++port) {
    result[port]=FU_ALU;
    if(port==boomcfg::JMP_PORT)result[port]|=FU_JMP;
    if(port==boomcfg::CSR_PORT)result[port]|=FU_CSR;
    if(port==boomcfg::MUL_PORT)result[port]|=FU_MUL;
    if(port==boomcfg::DIV_PORT && !busy)result[port]|=FU_DIV;
    if(port==boomcfg::I2F_PORT && i2f_ready)result[port]|=FU_I2F;
  }
  return result;
}
void Core::prepare_execution(CycleInputs& input,CycleOutputs& output) {
  auto& e=state_.execution;e.csr_port.valid=false;e.divider_response_fired=false;
  input.issue.integer_fu=integer_availability(input.i2f_ready);
  const auto& r=record_->r.coreMisc;
  for (unsigned port=0;port<kWidth;++port) {
    if (!r.brinfos_valid[port]) continue;
    const BranchMask mask=BranchMask{1}<<r.brinfos_uop_br_tag[port];
    input.branch.resolved |= mask;
    if (r.brinfos_mispredict[port]) input.branch.mispredicted |= mask;
  }
  const auto& b2=e.branch_redirect;
  if (b2.valid && b2.mispredict) {
    if (input.branch.redirect && input.branch.rob!=b2.rob_idx) throw std::logic_error("conflicting B2 redirects");
    input.branch.redirect=true;input.branch.tag=b2.tag;input.branch.rob=b2.rob_idx;
    input.branch.load_tail=b2.ldq_idx;input.branch.store_tail=b2.stq_idx;input.branch.surviving=b2.br_mask;
    output.redirect={true,true,b2.taken,b2.is_br,b2.is_rvc,b2.edge_inst,b2.ftq_idx,b2.pc_lob,b2.pc_select,b2.offset,b2.target};
  }
  const BranchEntry* oldest=oldest_b1_mispredict();
  if (oldest) {
    e.branch_redirect=*oldest;e.branch_redirect.valid=e.branch_redirect.mispredict=true;
    e.branch_redirect.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
  } else e.branch_redirect.valid=e.branch_redirect.mispredict=false;
  if (cut_lanes_) {
    // core.scala:200-216: b2 takes the oldest mispredicting brinfo, else
    // brinfos(0); jalr_target always comes from the jump unit.
    const BranchEntry& src=oldest ? *oldest : e.brinfo[boomcfg::JMP_PORT];
    write_record(*record_,fields::b2_mispredict,oldest!=nullptr);
    write_record(*record_,fields::b2_cfi_type,src.is_jalr ? 3u : (src.is_br && !src.is_sfb) ? 1u : 0u);
    write_record(*record_,fields::b2_taken,src.taken);
    write_record(*record_,fields::b2_pc_sel,src.pc_select);
    write_record(*record_,fields::b2_target_offset,static_cast<std::uint32_t>(src.offset));
    write_record(*record_,fields::b2_jalr_target,e.brinfo[boomcfg::JMP_PORT].jalr_target);
    write_record(*record_,fields::b2_uop_edge_inst,src.edge_inst);
    write_record(*record_,fields::b2_uop_ftq_idx,src.ftq_idx);
    write_record(*record_,fields::b2_uop_is_rvc,src.is_rvc);
    write_record(*record_,fields::b2_uop_ldq_idx,src.ldq_idx);
    write_record(*record_,fields::b2_uop_pc_lob,src.pc_lob);
    write_record(*record_,fields::b2_uop_stq_idx,src.stq_idx);
  }
  prepare_issue(input,output);

  CHISA_DIAG(
    // The branch update masks and the per-port occupancy are published into
    // the window image rather than the record, so a selected cycle keeps them
    // here, where the model applies them. Diagnostic builds only.
    using namespace ::chisa::diagnostic;
    if (RecordDump::instance().selected(state_.cycle)) {
      checkpoint("execute","branch-update",state_.cycle,Layer::Internal,
          {{"resolved",input.branch.resolved},{"mispredicted",input.branch.mispredicted},
           {"read_valids_0",e.read_valids[0]},{"read_valids_1",e.read_valids[1]},
           {"read_valids_2",kWidth>2 ? e.read_valids[2] : 0u},
           {"unit_valids_0",e.unit_valids[0]},{"unit_valids_1",e.unit_valids[1]},
           {"read_0_1_br_mask",e.read[0][1].uop.br_mask},
           {"read_2_1_br_mask",kWidth>2 ? e.read[2][1].uop.br_mask : 0u},
           {"divider_br_mask",e.divider_wb.br_mask}});
    }
  );

  for (unsigned port=0;port<kWidth;++port) {
    for (unsigned active=e.read_valids[port];active;active&=active-1) {
      const unsigned stage=static_cast<unsigned>(__builtin_ctz(active));auto& u=e.read[port][stage].uop;
      if (u.br_mask&input.branch.mispredicted) e.read_valids[port]&=static_cast<std::uint8_t>(~(1u<<stage));
      if (u.br_mask&input.branch.resolved) {
        u.br_mask &= static_cast<BranchMask>(~input.branch.resolved);write_integer_read(port,stage,true);
      }
    }
    for (unsigned active=e.unit_valids[port];active;active&=active-1) {
      const unsigned stage=static_cast<unsigned>(__builtin_ctz(active));auto& w=e.wb(port,stage);
      if (w.br_mask&input.branch.mispredicted) e.unit_valids[port]&=static_cast<std::uint8_t>(~(1u<<stage));
      if (w.br_mask&input.branch.resolved) {
        w.br_mask &= static_cast<BranchMask>(~input.branch.resolved);
        if (stage==(boomcfg::alu_latency(port)-1)) write_integer_result(port,true);
      }
    }
  }
  auto d=divider_state();auto& div=e.divider_wb;
  if (div.br_mask&input.branch.mispredicted) d.state=0;
  if (div.br_mask&input.branch.resolved) {
    div.br_mask &= static_cast<BranchMask>(~input.branch.resolved);write_divider_uop();
  }
  const auto& i2f=e.read[boomcfg::I2F_PORT][1];
  if ((e.read_valids[boomcfg::I2F_PORT]&2u) && (i2f.uop.fu_code&FU_I2F))
    output.i2f={true,i2f.uop,record_->r.coreIregRead.exe_reg_rs1_data[boomcfg::I2F_PORT+1]};
  bool divider_port_wrote=false;
  for (unsigned port=0;port<kWidth;++port) {
    const unsigned stage=boomcfg::alu_latency(port)-1;
    if (!(e.unit_valids[port]&(1u<<stage))) continue;
    const auto& w=e.wb(port,stage);
    Completion c;c.valid=c.clear_busy=true;c.rob=w.rob;c.pdst=w.pdst;
    c.writes_integer=w.has(Writeback::WritesInteger);c.data=w.data;c.source_port=static_cast<std::uint8_t>(port+1);
    if (w.has(Writeback::Csr)) {
      auto& csr=e.csr_port;csr.valid=true;csr.rob_idx=w.rob;csr.command=w.command;csr.operand=w.data;
      csr.address=instruction(w.rob).csr_addr;
      csr.read_data=csr_logic::read(state_.csr,state_.retired_counter,csr.address,0);c.data=csr.read_data;
    }
    publish_completion(input,c);divider_port_wrote |= port==boomcfg::DIV_PORT;
  }
  if (d.state==7 && !divider_port_wrote) {
    Completion c;c.valid=c.clear_busy=true;c.rob=div.rob;c.pdst=div.pdst;
    c.writes_integer=div.has(Writeback::WritesInteger);c.data=div.data;c.source_port=boomcfg::DIV_PORT+1;
    publish_completion(input,c);e.divider_response_fired=true;
  }
}
void Core::launch_execution(const CycleInputs& input,CycleOutputs& output) {
  auto& e=state_.execution;auto& rr=record_->r.coreIregRead;
  const auto& arriving=e.read[boomcfg::DIV_PORT][1];
  const bool divide_arrives=(e.read_valids[boomcfg::DIV_PORT]&2u) && (arriving.uop.fu_code&FU_DIV);
  DividerRequest request;
  if (divide_arrives) {
    const auto& u=instruction(arriving.uop.rob);
    request={rr.exe_reg_rs1_data[boomcfg::DIV_PORT+1],rr.exe_reg_rs2_data[boomcfg::DIV_PORT+1],u.ctrl.op_fcn,u.ctrl.fcn_dw};
    e.divider_wb=writeback(arriving.uop,u,arriving.result);write_divider_uop();
  }
  auto divider=divider_state();
  clock_integer_divider(divider,divide_arrives ? &request : nullptr,e.divider_response_fired);
  for (unsigned port=0;port<kWidth;++port) {
    const unsigned before=e.read_valids[port];const auto& read=e.read[port][1];const auto& u=read.uop;
    const bool incoming=(before&2u)!=0;
    const bool unit_incoming=incoming && (alu(u.fu_code) || (port==boomcfg::MUL_PORT && (u.fu_code&FU_MUL)));
    const auto a=incoming ? rr.exe_reg_rs1_data[port+1] : 0;
    const auto b=incoming ? rr.exe_reg_rs2_data[port+1] : 0;
    if (port==boomcfg::MUL_PORT && incoming && (u.fu_code&FU_MUL)) {
      auto& m=record_->r.coreMisc;const auto& decoded=instruction(u.rob);
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
      m.jmp_unit_imul_imul_inPipe_bits_in1=a;m.jmp_unit_imul_imul_inPipe_bits_in2=b;
      m.jmp_unit_imul_imul_inPipe_bits_fn=decoded.ctrl.op_fcn;
      m.jmp_unit_imul_imul_inPipe_bits_dw=decoded.ctrl.fcn_dw;
#else
      m.ALUExeUnitinst_imul_imul_inPipe_bits_in1=a;m.ALUExeUnitinst_imul_imul_inPipe_bits_in2=b;
      m.ALUExeUnitinst_imul_imul_inPipe_bits_fn=decoded.ctrl.op_fcn;
      m.ALUExeUnitinst_imul_imul_inPipe_bits_dw=decoded.ctrl.fcn_dw;
#endif
    }
    const unsigned unit_before=e.unit_valids[port];
    if (port==boomcfg::MUL_PORT) {
      if (unit_before&2u) e.multiply[2]=e.multiply[1];
      if (unit_before&1u) e.multiply[1]=e.multiply[0];
    }
    if (unit_incoming) {
      const auto& decoded=instruction(u.rob);
      e.wb(port,0)=writeback(u,decoded,(u.fu_code&FU_CSR) ? a : read.result);
    }
    e.unit_valids[port]=static_cast<std::uint8_t>(((unit_before<<1)|unsigned(unit_incoming)) & ((1u<<boomcfg::alu_latency(port))-1u));
    write_integer_result(port,port==boomcfg::MUL_PORT ? (unit_before&2u)!=0 : unit_incoming);

    // Branch payload is born at the ALU request, then occupies B1/B2 only.
    // In particular it never enters the late ALU/MUL result stages.
    auto& info=e.brinfo[port];info.valid=false;
    // The b2 lanes default to the jump port's brinfo register, which the RTL
    // rewrites every cycle from whatever micro-op that port executes
    // (functional-unit.scala:381-425), a null micro-op included.
    const bool cut_jmp=cut_lanes_ && port==boomcfg::JMP_PORT;
    if (incoming) {
      info.rob_idx=u.rob;info.tag=u.br_tag;info.br_mask=u.br_mask;
      info.ftq_idx=u.ftq_idx;info.ldq_idx=u.ldq_idx;info.stq_idx=u.stq_idx;info.pc_lob=u.pc_lob;
      info.is_br=u.is_br();info.is_jalr=u.is_jalr();info.is_rvc=u.is_rvc();info.edge_inst=u.edge_inst();
      info.is_jal=u.is_jal();info.is_sfb=u.is_sfb();
      info.valid=alu(u.fu_code) && ((u.is_br() && !u.is_sfb()) || u.is_jalr()) && !output.exception && !output.serializing;
      info.mispredict=false;
      if (info.valid || cut_jmp) {
        const auto& decoded=instruction(u.rob);
        const auto imm=decode_imm(decoded);
        info.pc_select=branch_pc_sel(decoded.ctrl.br_type,a,b);
        info.taken=(u.is_br() || u.is_jalr() || u.is_jal()) && info.pc_select!=PC_PLUS4;
        info.offset=static_cast<std::int32_t>(imm);
        info.target=info.pc_select==PC_JALR ? (a+imm)&~UINT64_C(1)
            : info.pc_select==PC_BRJMP ? u.pc+imm : u.pc+(u.is_rvc() ? 2u : 4u);
        if (cut_jmp) info.jalr_target=encode_virtual_address(a+imm)&~UINT64_C(1);
        if (info.valid && u.is_jalr()) {
          const auto& ftq=input.ftq0;const unsigned cfi=((u.pc_lob^(ftq.start_bank ? 8u : 0u))>>1)&(boomcfg::FETCH_WIDTH-1);
          constexpr auto mask=(UINT64_C(1)<<40)-1;
          info.mispredict=!ftq.next_valid || !ftq.cfi_valid || ftq.cfi_index!=cfi || (ftq.next_pc&mask)!=(info.target&mask);
        } else if (info.valid) info.mispredict=info.taken!=u.taken();
      }
    } else if (cut_jmp) {
      info=BranchEntry{};
    }
    write_branch_info(port,incoming);

    if (before&1u) e.read[port][1]=e.read[port][0];
    // register-read.scala:196-201 writes the operand registers every edge,
    // including an edge whose micro-op is killed; the zeros of an idle stage
    // come from the null micro-op's source registers, kept below.
    rr.exe_reg_rs1_data[port+1]=e.rrd_rs1[port];
    rr.exe_reg_rs2_data[port+1]=e.rrd_rs2[port];
    const auto& grant=output.integer[port];
    e.read_valids[port]=static_cast<std::uint8_t>(((before<<1)|unsigned(grant.valid))&3u);
    if (grant.selected) {
      auto& read0=e.read[port][0];read0.uop=grant.uop;const auto& s=read0.uop;
      // register-read.scala:168-175 takes a bypassed result only when that
      // source's type is integer; any other source reads the register file,
      // which the model keeps apart from the bypassed values.
      const auto operand=[&](std::uint8_t preg,std::uint8_t rtype) -> std::uint64_t {
        if (!preg) return 0;
        return rtype==RT_FIX ? state_.integer_values[preg] : state_.integer_registers[preg];
      };
      const auto r1=operand(s.prs1,s.lrs1_rtype),r2=operand(s.prs2,s.lrs2_rtype);
      e.rrd_rs1[port]=r1;e.rrd_rs2[port]=r2;
      if (grant.valid) {
        if (s.is_jalr() && port!=boomcfg::JMP_PORT) throw std::logic_error("JALR outside port 0");
        const auto& decoded=instruction(s.rob);const bool csr=(s.fu_code&FU_CSR)!=0,i2f=(s.fu_code&FU_I2F)!=0;
        read0.result=(csr || i2f) ? 0 : compute_int_result(decoded,r1,r2);
        if (!csr && !i2f && decoded.ldst_val && s.dst_rtype==RT_FIX && s.pdst) state_.integer_values[s.pdst]=read0.result;
        // core.scala:850-855 suppresses the fast wake-up only for a uop that
        // was issued on load speculation, not for every uop on a load-miss
        // edge. The grant already carries that slot's poison, so use it here:
        // the squash itself is only resolved later, in select_issue.
        if (decoded.bypassable && decoded.ldst_val && s.dst_rtype==RT_FIX && s.pdst &&
            !(input.load_miss && grant.poisoned)) {
          state_.rename.integer.busy &= ~(PhysicalMask{1}<<s.pdst);
          wake(state_.integer_issue,{true,false,false,s.pdst});wake(state_.memory_issue,{true,false,false,s.pdst});
        }
      }
    } else {
      // Nothing selected: the null micro-op reads register 0 on both sources.
      e.rrd_rs1[port]=0;e.rrd_rs2[port]=0;
    }
    write_integer_read(port,0,grant.selected);write_integer_read(port,1,(before&1u)!=0);
  }
}
}  // namespace chisa::boom_model::wide
