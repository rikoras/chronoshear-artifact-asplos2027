// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness__Syms.h"
#include "VTestHarness___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__stl(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void VTestHarness___024root___eval_triggers__stl(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_triggers__stl\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VTestHarness___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
