// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTESTHARNESS__SYMS_H_
#define VERILATED_VTESTHARNESS__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VTestHarness.h"

// INCLUDE MODULE CLASSES
#include "VTestHarness___024root.h"
#include "VTestHarness___024unit.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VTestHarness__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VTestHarness* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MULTI-THREADING
    VlThreadPool* __Vm_threadPoolp;
    bool __Vm_even_cycle__ico = false;
    bool __Vm_even_cycle__act = false;
    bool __Vm_even_cycle__nba = false;

    // MODULE INSTANCE STATE
    VTestHarness___024root         TOP;
    VTestHarness___024unit         TOP____024unit;

    // SCOPE NAMES
    VerilatedScope __Vscope_TestHarness;
    VerilatedScope __Vscope_TestHarness__SimDTM;
    VerilatedScope __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core;
    VerilatedScope __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core__csr;
    VerilatedScope __Vscope_TestHarness__mem__srams;

    // CONSTRUCTORS
    VTestHarness__Syms(VerilatedContext* contextp, const char* namep, VTestHarness* modelp);
    ~VTestHarness__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
