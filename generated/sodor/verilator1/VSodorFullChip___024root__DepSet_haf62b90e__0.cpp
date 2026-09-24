// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSodorFullChip.h for the primary calling header

#include "VSodorFullChip__pch.h"
#include "VSodorFullChip__Syms.h"
#include "VSodorFullChip___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__ico(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG

void VSodorFullChip___024root___eval_triggers__ico(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_triggers__ico\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSodorFullChip___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__act(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG

void VSodorFullChip___024root___eval_triggers__act(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_triggers__act\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSodorFullChip___024root___dump_triggers__act(vlSelf);
    }
#endif
}
