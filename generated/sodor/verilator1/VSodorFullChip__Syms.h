// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSODORFULLCHIP__SYMS_H_
#define VERILATED_VSODORFULLCHIP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VSodorFullChip.h"

// INCLUDE MODULE CLASSES
#include "VSodorFullChip___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)VSodorFullChip__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VSodorFullChip* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VSodorFullChip___024root       TOP;

    // CONSTRUCTORS
    VSodorFullChip__Syms(VerilatedContext* contextp, const char* namep, VSodorFullChip* modelp);
    ~VSodorFullChip__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
