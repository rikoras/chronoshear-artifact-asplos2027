// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFeedForwardMatMul.h for the primary calling header

#include "VFeedForwardMatMul__pch.h"
#include "VFeedForwardMatMul__Syms.h"
#include "VFeedForwardMatMul___024root.h"

void VFeedForwardMatMul___024root___ctor_var_reset(VFeedForwardMatMul___024root* vlSelf);

VFeedForwardMatMul___024root::VFeedForwardMatMul___024root(VFeedForwardMatMul__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __Vm_mtaskstate_final__0nba(4U)
    , vlSymsp{symsp}
 {
    // Reset structure values
    VFeedForwardMatMul___024root___ctor_var_reset(this);
}

void VFeedForwardMatMul___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VFeedForwardMatMul___024root::~VFeedForwardMatMul___024root() {
}
