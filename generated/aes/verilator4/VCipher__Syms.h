// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCIPHER__SYMS_H_
#define VERILATED_VCIPHER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VCipher.h"

// INCLUDE MODULE CLASSES
#include "VCipher___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VCipher__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VCipher* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MULTI-THREADING
    VlThreadPool* __Vm_threadPoolp;
    bool __Vm_even_cycle__ico = false;
    bool __Vm_even_cycle__act = false;
    bool __Vm_even_cycle__nba = false;

    // MODULE INSTANCE STATE
    VCipher___024root              TOP;

    // CONSTRUCTORS
    VCipher__Syms(VerilatedContext* contextp, const char* namep, VCipher* modelp);
    ~VCipher__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
