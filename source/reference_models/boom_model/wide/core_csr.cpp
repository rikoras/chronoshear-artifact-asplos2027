#include "core.h"

namespace chisa::boom_model::wide {
void Core::reset_csr() {
  state_.csr.clear();
  state_.csr.mstatus=UINT64_C(0x200001800);
  // Literal reset value from the Large FIRRTL CSRFile, not Small's ISA hint.
  state_.csr.misa=UINT64_C(0x0800000000094112d);
  state_.csr.dcsr=UINT64_C(0x10000003);
  state_.csr.prv=3;
  state_.retired_counter=state_.csr.minstret=state_.csr_flush_target=0;
  mark_csr_record();
}
void Core::latch_hpm_events(const HpmEventInputs& input) {
  csr_logic::latch_hpm_events(state_.csr,input);
}
bool Core::csr_cycle_start() {
  auto& csr=state_.csr;
  const bool stepping=(csr.dcsr & 4u) && !csr.debug;
  if (stepping && (state_.execution.retired_r || state_.execution.exception_r))
    csr.single_stepped=true;
  if (!csr.wfi && !csr.cease && !(csr.mcountinhibit & 1u)) ++csr.mcycle;
  for (unsigned counter=0;counter<boomcfg::NUM_HPM;++counter) {
    if (csr.hpm_inc_r[counter] && !(csr.mcountinhibit & (1u<<(counter+3))))
      csr.hpmcounter[counter]=(csr.hpmcounter[counter]+1)&((UINT64_C(1)<<40)-1);
    csr.hpm_inc_r[counter]=false;
  }
  csr.minstret=state_.retired_counter;
  if (!state_.trap_pending) return false;
  if (!state_.trap_mini) {
    csr_logic::take_trap(csr,state_.trap_pc,state_.trap_cause,state_.trap_instruction);
    if (state_.trap_tval_valid && !csr.debug) {
      const auto address=state_.trap_tval&((UINT64_C(1)<<40)-1);
      if (csr.prv==1) csr.stval=address;else csr.mtval=address;
    }
  }
  mark_csr_record();
  state_.trap_pending=false;
  // As in Small: the trap edge precedes the tail/read stage and the following
  // row-restore stage. Large restores the three banks in reverse lane order.
  begin_rollback(1);
  return true;
}
void Core::csr_cycle_end(const CycleInputs& input, CycleOutputs& output) {
  const auto old_fcsr=state_.csr.fcsr;const auto old_status=state_.csr.mstatus;
  unsigned retired=0;
  for (const auto& event : output.retired) {
    if (!event.valid) continue;
    ++retired;
    if (event.writes_f || event.fflags) {
      state_.csr.fcsr |= event.fflags & 31u;
      state_.csr.mstatus |= UINT64_C(3)<<13;
    }
  }
  if (!(state_.csr.mcountinhibit & 4u)) state_.retired_counter+=retired;
  retired_count_=static_cast<std::uint8_t>(retired);

  const auto request=state_.execution.csr_port;
  sys_insn_now_=request.valid && request.command==4;   // CSR.I: a system instruction in the CSR unit
  sys_insn_addr_=request.address;
  if (request.valid && !output.exception && !state_.rob.rolling_back) {
    const auto& u=instruction(request.rob_idx);
    const auto effect=csr_logic::execute(
        {state_.csr,state_.retired_counter,state_.csr.minstret,state_.csr_flush_target,
         input.wfi_wakeup,0,true,request.read_data},
        u,request.command,request.operand);
    if(effect.changed) mark_csr_record();
  }
  state_.execution.csr_port.valid=false;
  if (input.wfi_wakeup && state_.csr.wfi) { state_.csr.wfi=false;mark_csr_record(); }
  if(old_fcsr!=state_.csr.fcsr || old_status!=state_.csr.mstatus) mark_csr_record();
  state_.execution.retired_r=retired!=0;
  state_.execution.exception_r=output.exception;

  if (output.exception && !state_.rob.rolling_back) {
    const auto& u=instruction(output.exception_rob);
    state_.trap_pending=true;
    state_.trap_mini=output.exception_cause==16;
    state_.trap_pc=u.debug_pc;state_.trap_cause=output.exception_cause;
    state_.trap_instruction=u.inst;
    const auto index=dense(output.exception_rob);
    state_.trap_tval_valid=state_.rob.exception_tval_valid[index];
    state_.trap_tval=state_.rob.exception_tval[index];
    const auto target=state_.trap_mini ? u.debug_pc
        : csr_logic::trap_target(state_.csr,output.exception_cause,u.inst);
    output.redirect={true,false,false,false,false,false,u.ftq_idx,u.pc_lob,0,0,target};
  }
}
}  // namespace chisa::boom_model::wide
