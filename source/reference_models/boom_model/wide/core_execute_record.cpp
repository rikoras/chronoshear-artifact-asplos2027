#include "core.h"
#include "record_fields.h"

namespace chisa::boom_model::wide {
void Core::write_divider_uop() {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  const auto& w=state_.execution.divider_wb;auto& r=record_->r.coreCsrExe;
  r.div_r_uop_br_mask=w.br_mask;r.div_r_uop_rob_idx=w.rob;
  r.div_r_uop_is_amo=w.has(Writeback::IsAmo);r.div_r_uop_uses_stq=w.has(Writeback::UsesStq);
#else
  const auto& w=state_.execution.divider_wb;auto& r=record_->r.coreMisc;
  r.jmp_unit_div_r_uop_br_mask=w.br_mask;r.jmp_unit_div_r_uop_rob_idx=w.rob;
  r.jmp_unit_div_r_uop_is_amo=w.has(Writeback::IsAmo);r.jmp_unit_div_r_uop_uses_stq=w.has(Writeback::UsesStq);
#endif
  if (cut_lanes_) {
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    constexpr unsigned unit=1;
#else
    constexpr unsigned unit=0;
#endif
    write_record(*record_,fields::div_uop_bypassable[unit],w.bypassable);
    write_record(*record_,fields::div_uop_dst_rtype[unit],w.dst_rtype);
    write_record(*record_,fields::div_uop_pdst[unit],w.pdst);
  }
}
void Core::write_integer_read(unsigned port,unsigned stage,bool payload) {
  const auto& e=state_.execution;const auto& u=e.read[port][stage].uop;auto& rr=record_->r.coreIregRead;
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  if (stage==0 && payload) {
    if (port==0) rr.REG_3_br_mask=u.br_mask;
    if (port==1) rr.REG_5_br_mask=u.br_mask;
  }
  if (stage==1 && port==1) {
    // register-read.scala:196-201 writes this stage's payload on every edge and
    // issue-unit-age-ordered.scala:93-101 supplies a null micro-op when nothing
    // issues, so an idle port latches zeros instead of holding its last value.
    const bool live=(e.read_valids[1]&2u)!=0;
    rr.exe_reg_valids[2]=live;
    rr.exe_reg_uops_fu_code[2]=live ? u.fu_code : 0;
  }
#else
  if (stage==0 && payload) {
    if (port==1) rr.REG_5_br_mask=u.br_mask;
    if (port==2) rr.REG_7_br_mask=u.br_mask;
    if (port==0 && cut_lanes_) write_record(*record_,fields::iregread_stage0_br_mask,u.br_mask);
  }
  if (cut_lanes_ && stage==0 && port==boomcfg::JMP_PORT) {
    // core.scala:533-534 jmp_pc_req: RegNext of the jump port's issue.
    const bool live=(e.read_valids[port]&1u)!=0;
    write_record(*record_,fields::core_jmp_pc_req_valid,live && u.fu_code==FU_JMP);
    write_record(*record_,fields::core_jmp_pc_req_ftq,live ? u.ftq_idx : 0);
  }
  if (stage==1 && port==0) {
    // register-read.scala:196-201, as above: an idle port latches zeros.
    const bool live=(e.read_valids[0]&2u)!=0;
    rr.exe_reg_valids[1]=live;
    rr.exe_reg_uops_br_mask[1]=live ? u.br_mask : 0;
    if (cut_lanes_) {
      const auto& d=instruction(u.rob);
      write_record(*record_,fields::iregread_uop_fp_val,live && u.fp_val());
      write_record(*record_,fields::iregread_uop_is_amo,live && u.is_amo());
      write_record(*record_,fields::iregread_uop_ldq_idx,live ? u.ldq_idx : 0);
      write_record(*record_,fields::iregread_uop_mem_cmd,live ? u.mem_cmd : 0);
      write_record(*record_,fields::iregread_uop_mem_signed,live && d.mem_signed);
      write_record(*record_,fields::iregread_uop_mem_size,live ? d.mem_size : 0);
      write_record(*record_,fields::iregread_uop_pdst,live ? u.pdst : 0);
      write_record(*record_,fields::iregread_uop_rob_idx,live ? u.rob : 0);
      write_record(*record_,fields::iregread_uop_stq_idx,live ? u.stq_idx : 0);
      write_record(*record_,fields::iregread_uop_uses_ldq,live && u.uses_ldq());
      write_record(*record_,fields::iregread_uop_uses_stq,live && u.uses_stq());
    }
    rr.exe_reg_uops_fu_code[1]=live ? u.fu_code : 0;
  }
#endif
}
void Core::write_branch_info(unsigned port,bool payload) {
  const auto& b=state_.execution.brinfo[port];auto& r=record_->r.coreMisc;
  r.brinfos_valid[port]=b.valid;
  if (payload) {
    r.brinfos_uop_br_tag[port]=b.tag;r.brinfos_mispredict[port]=b.mispredict;
    if (cut_lanes_) {
      write_record(*record_,fields::brinfo_uop_ftq_idx[port],b.ftq_idx);
      write_record(*record_,fields::brinfo_uop_rob_idx[port],b.rob_idx);
    }
  }
}
void Core::write_integer_result(unsigned port,bool payload) {
  const auto& e=state_.execution;const unsigned stage=boomcfg::alu_latency(port)-1;
  const auto& w=e.wb(port,stage);const bool live=(e.unit_valids[port]&(1u<<stage))!=0;
  auto& m=record_->r.coreMisc;auto& c=record_->r.coreCsrExe;
  // Partition-cut lanes of the same stage register (unit order of
  // fields::exe_uop_*: jmp alu 1_0, csr alu 1_0, ALU 1_2, IMUL 1_2, then
  // Medium's jmp alu 1_2 and imul 1_2).
  // functional-unit.scala:233 latches io.req.bits.uop every edge, and the
  // register-read stage drives NullMicroOp (consts.scala:268-289) when nothing
  // issues: bypassable/pdst/csr_cmd zero, dst_rtype RT_X (2). imm_packed is
  // DontCare there and keeps whatever the issue mux drove, so it is written
  // only with a payload.
  const auto cut=[&](unsigned unit) {
    if (!cut_lanes_) return;
    write_record(*record_,fields::exe_uop_bypassable[unit],live && w.bypassable);
    write_record(*record_,fields::exe_uop_dst_rtype[unit],live ? w.dst_rtype : 2u);
    write_record(*record_,fields::exe_uop_pdst[unit],live ? w.pdst : 0u);
    write_record(*record_,fields::exe_uop_ctrl_csr_cmd[unit],live ? w.command : 0u);
    if (payload) write_record(*record_,fields::exe_uop_imm_packed[unit],w.imm_packed);
  };
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
  if (port==0) {
    m.jmp_unit_alu_REG_2=live && !w.has(Writeback::Multiply);
    m.jmp_unit_imul_REG_2=live && w.has(Writeback::Multiply);
    if (payload) {
      m.jmp_unit_alu_REG_1_2_rob_idx=m.jmp_unit_imul_REG_1_2_rob_idx=w.rob;
      m.jmp_unit_alu_REG_1_2_is_amo=m.jmp_unit_imul_REG_1_2_is_amo=w.has(Writeback::IsAmo);
      m.jmp_unit_alu_REG_1_2_uses_stq=m.jmp_unit_imul_REG_1_2_uses_stq=w.has(Writeback::UsesStq);
    }
    cut(4);cut(5);
  } else {
    c.alu_REG_0=live;
    if (payload) {
      c.alu_REG_1_0_rob_idx=w.rob;c.alu_REG_1_0_is_amo=w.has(Writeback::IsAmo);
      c.alu_REG_1_0_uses_stq=w.has(Writeback::UsesStq);
    }
    cut(1);
  }
#else
  if (port==0) {
    m.jmp_unit_alu_REG_0=live;
    if (payload) {
      m.jmp_unit_alu_REG_1_0_br_mask=w.br_mask;m.jmp_unit_alu_REG_1_0_rob_idx=w.rob;
      m.jmp_unit_alu_REG_1_0_is_amo=w.has(Writeback::IsAmo);m.jmp_unit_alu_REG_1_0_uses_stq=w.has(Writeback::UsesStq);
    }
    cut(0);
  } else if (port==1) {
    c.alu_REG_0=live;
    // functional-unit.scala: r_data(0) is RegNext(alu.io.out); a null micro-op adds zeros.
    if (cut_lanes_) write_record(*record_,fields::csr_alu_r_data,live ? w.data : 0);
    if (payload) {
      c.alu_REG_1_0_br_mask=w.br_mask;c.alu_REG_1_0_rob_idx=w.rob;
      c.alu_REG_1_0_is_amo=w.has(Writeback::IsAmo);c.alu_REG_1_0_uses_stq=w.has(Writeback::UsesStq);
    }
    cut(1);
  } else {
    m.ALUExeUnitinst_alu_REG_2=live && !w.has(Writeback::Multiply);
    m.ALUExeUnitinst_imul_REG_2=live && w.has(Writeback::Multiply);
    if (payload) {
      m.ALUExeUnitinst_alu_REG_1_2_br_mask=w.br_mask;m.ALUExeUnitinst_alu_REG_1_2_rob_idx=w.rob;
      m.ALUExeUnitinst_alu_REG_1_2_is_amo=w.has(Writeback::IsAmo);m.ALUExeUnitinst_alu_REG_1_2_uses_stq=w.has(Writeback::UsesStq);
      m.ALUExeUnitinst_imul_REG_1_2_br_mask=w.br_mask;m.ALUExeUnitinst_imul_REG_1_2_rob_idx=w.rob;
      m.ALUExeUnitinst_imul_REG_1_2_is_amo=w.has(Writeback::IsAmo);m.ALUExeUnitinst_imul_REG_1_2_uses_stq=w.has(Writeback::UsesStq);
    }
    cut(2);cut(3);
  }
#endif
}
}  // namespace chisa::boom_model::wide
