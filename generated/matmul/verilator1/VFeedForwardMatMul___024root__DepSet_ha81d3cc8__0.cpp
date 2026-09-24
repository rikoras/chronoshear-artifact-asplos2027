// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFeedForwardMatMul.h for the primary calling header

#include "VFeedForwardMatMul__pch.h"
#include "VFeedForwardMatMul__Syms.h"
#include "VFeedForwardMatMul___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__ico(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG

void VFeedForwardMatMul___024root___eval_triggers__ico(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_triggers__ico\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFeedForwardMatMul___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__act(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG

void VFeedForwardMatMul___024root___eval_triggers__act(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_triggers__act\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFeedForwardMatMul___024root___dump_triggers__act(vlSelf);
    }
#endif
}
