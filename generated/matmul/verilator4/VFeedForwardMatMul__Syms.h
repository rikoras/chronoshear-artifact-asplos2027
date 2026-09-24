// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VFEEDFORWARDMATMUL__SYMS_H_
#define VERILATED_VFEEDFORWARDMATMUL__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VFeedForwardMatMul.h"

// INCLUDE MODULE CLASSES
#include "VFeedForwardMatMul___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VFeedForwardMatMul__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VFeedForwardMatMul* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MULTI-THREADING
    VlThreadPool* __Vm_threadPoolp;
    bool __Vm_even_cycle__ico = false;
    bool __Vm_even_cycle__act = false;
    bool __Vm_even_cycle__nba = false;

    // MODULE INSTANCE STATE
    VFeedForwardMatMul___024root   TOP;

    // CONSTRUCTORS
    VFeedForwardMatMul__Syms(VerilatedContext* contextp, const char* namep, VFeedForwardMatMul* modelp);
    ~VFeedForwardMatMul__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
