// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VSodorFullChip__pch.h"
#include "VSodorFullChip.h"
#include "VSodorFullChip___024root.h"

// FUNCTIONS
VSodorFullChip__Syms::~VSodorFullChip__Syms()
{
}

VSodorFullChip__Syms::VSodorFullChip__Syms(VerilatedContext* contextp, const char* namep, VSodorFullChip* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    , __Vm_threadPoolp{static_cast<VlThreadPool*>(contextp->threadPoolp())}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(897);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
