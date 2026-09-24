// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness__Syms.h"
#include "VTestHarness___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__ico(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG

void VTestHarness___024root___eval_triggers__ico(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_triggers__ico\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VTestHarness___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__act(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG

void VTestHarness___024root___eval_triggers__act(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_triggers__act\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((~ (IData)(vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0)) 
                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0__0)));
    vlSelfRef.__VactTriggered.setBit(1U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__VactTriggered.setBit(2U, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset__0))));
    vlSelfRef.__VactTriggered.setBit(3U, ((IData)(vlSelfRef.reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__reset__0))));
    vlSelfRef.__VactTriggered.setBit(4U, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset__0))));
    vlSelfRef.__VactTriggered.setBit(5U, ((IData)(vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate_out) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__gated_clock_debug_clock_gate_out__0))));
    vlSelfRef.__VactTriggered.setBit(6U, ((~ (IData)(vlSelfRef.clock)) 
                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0__0 
        = vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0;
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset__0 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset;
    vlSelfRef.__Vtrigprevexpr___TOP__reset__0 = vlSelfRef.reset;
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset__0 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset;
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__gated_clock_debug_clock_gate_out__0 
        = vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate_out;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VTestHarness___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void VTestHarness___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle);
void VTestHarness___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle);
void VTestHarness___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle);
void VTestHarness___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle);

void VTestHarness___024root___eval_nba(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_nba\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->__Vm_even_cycle__nba = !vlSymsp->__Vm_even_cycle__nba;
    vlSymsp->__Vm_threadPoolp->workerp(0)->addTask(&VTestHarness___024root____Vthread__nba__t0__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(1)->addTask(&VTestHarness___024root____Vthread__nba__t1__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(2)->addTask(&VTestHarness___024root____Vthread__nba__t2__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    VTestHarness___024root____Vthread__nba__t3__s0(vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSelf->__Vm_mtaskstate_final__0nba.waitUntilUpstreamDone(vlSymsp->__Vm_even_cycle__nba);
    Verilated::mtaskId(0);
}

void VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit(CData/*0:0*/ &debug_req_valid, CData/*0:0*/ debug_req_ready, IData/*31:0*/ &debug_req_bits_addr, IData/*31:0*/ &debug_req_bits_op, IData/*31:0*/ &debug_req_bits_data, CData/*0:0*/ debug_resp_valid, CData/*0:0*/ &debug_resp_ready, IData/*31:0*/ debug_resp_bits_resp, IData/*31:0*/ debug_resp_bits_data, IData/*31:0*/ &debug_tick__Vfuncrtn);

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__39(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__39\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vfunc_debug_tick__0__Vfuncout;
    __Vfunc_debug_tick__0__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_debug_tick__0__debug_req_valid;
    __Vfunc_debug_tick__0__debug_req_valid = 0;
    IData/*31:0*/ __Vfunc_debug_tick__0__debug_req_bits_addr;
    __Vfunc_debug_tick__0__debug_req_bits_addr = 0;
    IData/*31:0*/ __Vfunc_debug_tick__0__debug_req_bits_op;
    __Vfunc_debug_tick__0__debug_req_bits_op = 0;
    IData/*31:0*/ __Vfunc_debug_tick__0__debug_req_bits_data;
    __Vfunc_debug_tick__0__debug_req_bits_data = 0;
    CData/*0:0*/ __Vfunc_debug_tick__0__debug_resp_ready;
    __Vfunc_debug_tick__0__debug_resp_ready = 0;
    // Body
    if (((IData)(vlSelfRef.reset) | (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__r_reset))) {
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_valid = 0U;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_resp_ready = 0U;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fexit = 0U;
    } else {
        VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit(__Vfunc_debug_tick__0__debug_req_valid, (IData)(vlSelfRef.TestHarness__DOT__SimDTM_debug_req_ready), __Vfunc_debug_tick__0__debug_req_bits_addr, __Vfunc_debug_tick__0__debug_req_bits_op, __Vfunc_debug_tick__0__debug_req_bits_data, (IData)(vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_valid), __Vfunc_debug_tick__0__debug_resp_ready, (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_4_2), vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_bits_data, __Vfunc_debug_tick__0__Vfuncout);
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_valid 
            = __Vfunc_debug_tick__0__debug_req_valid;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_bits_addr 
            = __Vfunc_debug_tick__0__debug_req_bits_addr;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_bits_op 
            = __Vfunc_debug_tick__0__debug_req_bits_op;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_bits_data 
            = __Vfunc_debug_tick__0__debug_req_bits_data;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_resp_ready 
            = __Vfunc_debug_tick__0__debug_resp_ready;
        vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fexit 
            = __Vfunc_debug_tick__0__Vfuncout;
    }
    vlSelfRef.TestHarness__DOT__SimDTM__DOT__r_reset 
        = vlSelfRef.reset;
}

void VTestHarness___024root___nba_sequent__TOP__0(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask0(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask0\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 0;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__0(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__1(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask1(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask1\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 1;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__1(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__2(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__3(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__4(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask2(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask2\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 2;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__4(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__5(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__6(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask3(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask3\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 3;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((0x20ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__6(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__7(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__8(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__9(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__10(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask4(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask4\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 4;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__7(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__8(vlSelf);
    }
    if ((0x20ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__9(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__10(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__11(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask5(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask5\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 5;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__11(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__12(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask6(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask6\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 6;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__12(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__13(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask7(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask7\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 7;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__13(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__14(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask8(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask8\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 8;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__14(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__15(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask9(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask9\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 9;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__15(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__16(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask10(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask10\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 10;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__16(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__17(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__18(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask11(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask11\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 11;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__17(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__18(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__19(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask12(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask12\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 12;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__19(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__20(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask13(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask13\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 13;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__20(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__21(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask14(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask14\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 14;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__21(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__22(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask15(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask15\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 15;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__22(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__23(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__24(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__25(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__26(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__28(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__0(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__1(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask16(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask16\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 16;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__23(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__24(vlSelf);
    }
    if ((0x20ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__25(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__26(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__28(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__0(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__1(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__29(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask17(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask17\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 17;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__29(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__30(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask18(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask18\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 18;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__30(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__31(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask19(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask19\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 19;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__31(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__32(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask20(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask20\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 20;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__32(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__33(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__2(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask21(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask21\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 21;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__33(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__2(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__34(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask22(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask22\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 22;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__34(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__35(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__36(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__37(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__38(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__40(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__3(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__41(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__42(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__43(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__44(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__45(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__4(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__46(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__47(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__48(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__49(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask23(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask23\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 23;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__35(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__36(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__37(vlSelf);
    }
    if ((0x20ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__38(vlSelf);
    }
    if ((0x40ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__39(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__40(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__3(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__41(vlSelf);
    }
    if ((0x30ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__42(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__43(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__44(vlSelf);
    }
    if ((0x12ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__45(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__4(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__46(vlSelf);
    }
    if ((0x30ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__47(vlSelf);
    }
    if ((0x12ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__48(vlSelf);
    }
    if ((0x30ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__49(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__50(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__5(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask24(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask24\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 24;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__50(vlSelf);
    }
    if ((0x22ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__5(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__51(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask25(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask25\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 25;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__51(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__52(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask26(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask26\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 26;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__52(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__53(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask27(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask27\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 27;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__53(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__54(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask28(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask28\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 28;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__54(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__55(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask29(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask29\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 29;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__55(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__56(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask30(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask30\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 30;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__56(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__57(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask31(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask31\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 31;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__57(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__58(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask32(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask32\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 32;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__58(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__59(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask33(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask33\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 33;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__59(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__60(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask34(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask34\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 34;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__60(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__61(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask35(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask35\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 35;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__61(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__62(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__6(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask36(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask36\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 36;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__62(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__6(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__63(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask37(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask37\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 37;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__63(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__64(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask38(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask38\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 38;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__64(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__65(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask39(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask39\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 39;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__65(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__66(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask40(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask40\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 40;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__66(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__67(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__68(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__69(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__71(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__7(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__72(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__8(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__73(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__9(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__74(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__10(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask41(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask41\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 41;
    Verilated::mtaskId(taskId);
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__67(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__68(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__69(vlSelf);
    }
    if ((0x30ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__71(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__7(vlSelf);
    }
    if ((0x12ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__72(vlSelf);
    }
    if ((0x22ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__8(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__73(vlSelf);
    }
    if ((0x23ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__9(vlSelf);
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__74(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__10(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__75(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask42(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask42\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 42;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__75(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__76(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__11(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__77(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__12(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask43(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask43\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 43;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__76(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__11(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__77(vlSelf);
        VTestHarness___024root___nba_comb__TOP__12(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__78(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask44(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask44\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 44;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__78(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root___nba_sequent__TOP__79(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__13(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_sequent__TOP__80(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__14(VTestHarness___024root* vlSelf);
void VTestHarness___024root___nba_comb__TOP__15(VTestHarness___024root* vlSelf);

void VTestHarness___024root__nba_mtask45(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root__nba_mtask45\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 45;
    Verilated::mtaskId(taskId);
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__79(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__13(vlSelf);
    }
    if ((0x21ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_sequent__TOP__80(vlSelf);
    }
    if ((0xaULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__14(vlSelf);
    }
    if ((0xeULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VTestHarness___024root___nba_comb__TOP__15(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VTestHarness___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root____Vthread__nba__t0__s0\n"); );
    // Body
    VTestHarness___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTestHarness___024root*>(voidSelf);
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VTestHarness___024root__nba_mtask4(vlSelf);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_14.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask1(vlSelf);
    vlSelf->__Vm_mtaskstate_20.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_19.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask19(vlSelf);
    vlSelf->__Vm_mtaskstate_43.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask21(vlSelf);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_30.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_31.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask18(vlSelf);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_30.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_29.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask29(vlSelf);
    vlSelf->__Vm_mtaskstate_34.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_41.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_26.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask26(vlSelf);
    vlSelf->__Vm_mtaskstate_33.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_34.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_35.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_36.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_38.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_37.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask37(vlSelf);
    vlSelf->__Vm_mtaskstate_45.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask45(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VTestHarness___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root____Vthread__nba__t1__s0\n"); );
    // Body
    VTestHarness___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTestHarness___024root*>(voidSelf);
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VTestHarness___024root__nba_mtask6(vlSelf);
    vlSelf->__Vm_mtaskstate_8.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_13.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask10(vlSelf);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask12(vlSelf);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask7(vlSelf);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask5(vlSelf);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_14.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask14(vlSelf);
    vlSelf->__Vm_mtaskstate_17.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_22.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask11(vlSelf);
    vlSelf->__Vm_mtaskstate_17.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_20.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask23(vlSelf);
    vlSelf->__Vm_mtaskstate_33.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_37.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_41.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_28.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask28(vlSelf);
    vlSelf->__Vm_mtaskstate_36.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_39.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_32.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask32(vlSelf);
    vlSelf->__Vm_mtaskstate_38.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask38(vlSelf);
    vlSelf->__Vm_mtaskstate_40.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_44.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_43.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask43(vlSelf);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_35.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask35(vlSelf);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_42.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask42(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VTestHarness___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root____Vthread__nba__t2__s0\n"); );
    // Body
    VTestHarness___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTestHarness___024root*>(voidSelf);
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VTestHarness___024root__nba_mtask3(vlSelf);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask9(vlSelf);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_8.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask8(vlSelf);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask16(vlSelf);
    vlSelf->__Vm_mtaskstate_19.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask24(vlSelf);
    vlSelf->__Vm_mtaskstate_31.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask31(vlSelf);
    vlSelf->__Vm_mtaskstate_40.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_43.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_41.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask41(vlSelf);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_36.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask36(vlSelf);
    vlSelf->__Vm_mtaskstate_44.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_33.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask33(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VTestHarness___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root____Vthread__nba__t3__s0\n"); );
    // Body
    VTestHarness___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTestHarness___024root*>(voidSelf);
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VTestHarness___024root__nba_mtask2(vlSelf);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_13.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask13(vlSelf);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask0(vlSelf);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_19.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_15.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask15(vlSelf);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_17.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask17(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_22.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask22(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_29.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_20.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask20(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_29.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_31.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask25(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_28.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_31.signalUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask27(vlSelf);
    vlSelf->__Vm_mtaskstate_32.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_35.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_36.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_37.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_41.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_30.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask30(vlSelf);
    vlSelf->__Vm_mtaskstate_36.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_37.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_43.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_39.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask39(vlSelf);
    vlSelf->__Vm_mtaskstate_34.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask34(vlSelf);
    vlSelf->__Vm_mtaskstate_42.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_40.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask40(vlSelf);
    vlSelf->__Vm_mtaskstate_45.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_44.waitUntilUpstreamDone(even_cycle);
    VTestHarness___024root__nba_mtask44(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}
