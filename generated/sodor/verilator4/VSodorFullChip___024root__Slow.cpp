// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSodorFullChip.h for the primary calling header

#include "VSodorFullChip__pch.h"
#include "VSodorFullChip__Syms.h"
#include "VSodorFullChip___024root.h"

void VSodorFullChip___024root___ctor_var_reset(VSodorFullChip___024root* vlSelf);

VSodorFullChip___024root::VSodorFullChip___024root(VSodorFullChip__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __Vm_mtaskstate_9(1U)
    , __Vm_mtaskstate_7(1U)
    , __Vm_mtaskstate_23(1U)
    , __Vm_mtaskstate_25(2U)
    , __Vm_mtaskstate_26(2U)
    , __Vm_mtaskstate_22(1U)
    , __Vm_mtaskstate_29(1U)
    , __Vm_mtaskstate_8(3U)
    , __Vm_mtaskstate_10(2U)
    , __Vm_mtaskstate_24(4U)
    , __Vm_mtaskstate_18(2U)
    , __Vm_mtaskstate_14(2U)
    , __Vm_mtaskstate_21(2U)
    , __Vm_mtaskstate_11(3U)
    , __Vm_mtaskstate_30(2U)
    , __Vm_mtaskstate_20(2U)
    , __Vm_mtaskstate_6(2U)
    , __Vm_mtaskstate_17(1U)
    , __Vm_mtaskstate_16(1U)
    , __Vm_mtaskstate_27(1U)
    , __Vm_mtaskstate_12(2U)
    , __Vm_mtaskstate_final__0nba(4U)
    , vlSymsp{symsp}
 {
    // Reset structure values
    VSodorFullChip___024root___ctor_var_reset(this);
}

void VSodorFullChip___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VSodorFullChip___024root::~VSodorFullChip___024root() {
}
