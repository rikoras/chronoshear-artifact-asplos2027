// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

VL_ATTR_COLD void VTestHarness___024root___ctor_var_reset_0(VTestHarness___024root* vlSelf);
VL_ATTR_COLD void VTestHarness___024root___ctor_var_reset_1(VTestHarness___024root* vlSelf);

VL_ATTR_COLD void VTestHarness___024root___ctor_var_reset(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___ctor_var_reset\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VTestHarness___024root___ctor_var_reset_0(vlSelf);
    VTestHarness___024root___ctor_var_reset_1(vlSelf);
}
