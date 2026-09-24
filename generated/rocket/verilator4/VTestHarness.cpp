// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VTestHarness__pch.h"

//============================================================
// Constructors

VTestHarness::VTestHarness(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VTestHarness__Syms(contextp(), _vcname__, this)}
    , reset{vlSymsp->TOP.reset}
    , io_success{vlSymsp->TOP.io_success}
    , clock{vlSymsp->TOP.clock}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VTestHarness::VTestHarness(const char* _vcname__)
    : VTestHarness(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VTestHarness::~VTestHarness() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VTestHarness___024root___eval_debug_assertions(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG
void VTestHarness___024root___eval_static(VTestHarness___024root* vlSelf);
void VTestHarness___024root___eval_initial(VTestHarness___024root* vlSelf);
void VTestHarness___024root___eval_settle(VTestHarness___024root* vlSelf);
void VTestHarness___024root___eval(VTestHarness___024root* vlSelf);

void VTestHarness::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VTestHarness::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VTestHarness___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VTestHarness___024root___eval_static(&(vlSymsp->TOP));
        VTestHarness___024root___eval_initial(&(vlSymsp->TOP));
        VTestHarness___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VTestHarness___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VTestHarness::eventsPending() { return false; }

uint64_t VTestHarness::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VTestHarness::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VTestHarness___024root___eval_final(VTestHarness___024root* vlSelf);

VL_ATTR_COLD void VTestHarness::final() {
    VTestHarness___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VTestHarness::hierName() const { return vlSymsp->name(); }
const char* VTestHarness::modelName() const { return "VTestHarness"; }
unsigned VTestHarness::threads() const { return 4; }
void VTestHarness::prepareClone() const { contextp()->prepareClone(); }
void VTestHarness::atClone() const {
    vlSymsp->__Vm_threadPoolp = static_cast<VlThreadPool*>(contextp()->threadPoolpOnClone());
}
