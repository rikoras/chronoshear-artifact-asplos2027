// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VTestHarness.h for the primary calling header

#ifndef VERILATED_VTESTHARNESS___024UNIT_H_
#define VERILATED_VTESTHARNESS___024UNIT_H_  // guard

#include "verilated.h"


class VTestHarness__Syms;

class alignas(VL_CACHE_LINE_BYTES) VTestHarness___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    VTestHarness__Syms* const vlSymsp;

    // CONSTRUCTORS
    VTestHarness___024unit(VTestHarness__Syms* symsp, const char* v__name);
    ~VTestHarness___024unit();
    VL_UNCOPYABLE(VTestHarness___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
