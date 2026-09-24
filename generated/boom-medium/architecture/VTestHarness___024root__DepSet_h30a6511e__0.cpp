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
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.TestHarness__DOT__ldut_debug_reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut_debug_reset__0))));
    vlSelfRef.__VactTriggered.setBit(1U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__VactTriggered.setBit(2U, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_clock__0))));
    vlSelfRef.__VactTriggered.setBit(3U, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset__0))));
    vlSelfRef.__VactTriggered.setBit(4U, ((IData)(vlSelfRef.reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__reset__0))));
    vlSelfRef.__VactTriggered.setBit(5U, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset__0))));
    vlSelfRef.__VactTriggered.setBit(6U, ((IData)(vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate_out) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__gated_clock_debug_clock_gate_out__0))));
    vlSelfRef.__VactTriggered.setBit(7U, ((~ (IData)(vlSelfRef.clock)) 
                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut_debug_reset__0 
        = vlSelfRef.TestHarness__DOT__ldut_debug_reset;
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
    vlSelfRef.__Vtrigprevexpr___TOP__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_clock__0 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_clock;
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

void VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit(CData/*0:0*/ &debug_req_valid, CData/*0:0*/ debug_req_ready, IData/*31:0*/ &debug_req_bits_addr, IData/*31:0*/ &debug_req_bits_op, IData/*31:0*/ &debug_req_bits_data, CData/*0:0*/ debug_resp_valid, CData/*0:0*/ &debug_resp_ready, IData/*31:0*/ debug_resp_bits_resp, IData/*31:0*/ debug_resp_bits_data, IData/*31:0*/ &debug_tick__Vfuncrtn);

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__17(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__17\n"); );
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
        VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit(__Vfunc_debug_tick__0__debug_req_valid, (IData)(vlSelfRef.TestHarness__DOT__SimDTM_debug_req_ready), __Vfunc_debug_tick__0__debug_req_bits_addr, __Vfunc_debug_tick__0__debug_req_bits_op, __Vfunc_debug_tick__0__debug_req_bits_data, (IData)(vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_valid), __Vfunc_debug_tick__0__debug_resp_ready, (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_5_2), vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_bits_data, __Vfunc_debug_tick__0__Vfuncout);
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
