// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCipher.h for the primary calling header

#include "VCipher__pch.h"
#include "VCipher__Syms.h"
#include "VCipher___024root.h"

void VCipher___024root___ctor_var_reset(VCipher___024root* vlSelf);

VCipher___024root::VCipher___024root(VCipher__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    VCipher___024root___ctor_var_reset(this);
}

void VCipher___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VCipher___024root::~VCipher___024root() {
}
