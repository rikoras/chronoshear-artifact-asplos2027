// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VSodorFullChip__pch.h"

//============================================================
// Constructors

VSodorFullChip::VSodorFullChip(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VSodorFullChip__Syms(contextp(), _vcname__, this)}
    , io_host_wdata{vlSymsp->TOP.io_host_wdata}
    , io_host_addr{vlSymsp->TOP.io_host_addr}
    , io_success{vlSymsp->TOP.io_success}
    , io_host_rdata{vlSymsp->TOP.io_host_rdata}
    , io_tohost{vlSymsp->TOP.io_tohost}
    , reset{vlSymsp->TOP.reset}
    , io_host_valid{vlSymsp->TOP.io_host_valid}
    , clock{vlSymsp->TOP.clock}
    , io_host_write{vlSymsp->TOP.io_host_write}
    , io_host_ready{vlSymsp->TOP.io_host_ready}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VSodorFullChip::VSodorFullChip(const char* _vcname__)
    : VSodorFullChip(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VSodorFullChip::~VSodorFullChip() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VSodorFullChip___024root___eval_debug_assertions(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG
void VSodorFullChip___024root___eval_static(VSodorFullChip___024root* vlSelf);
void VSodorFullChip___024root___eval_initial(VSodorFullChip___024root* vlSelf);
void VSodorFullChip___024root___eval_settle(VSodorFullChip___024root* vlSelf);
void VSodorFullChip___024root___eval(VSodorFullChip___024root* vlSelf);

void VSodorFullChip::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSodorFullChip::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VSodorFullChip___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VSodorFullChip___024root___eval_static(&(vlSymsp->TOP));
        VSodorFullChip___024root___eval_initial(&(vlSymsp->TOP));
        VSodorFullChip___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VSodorFullChip___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VSodorFullChip::eventsPending() { return false; }

uint64_t VSodorFullChip::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VSodorFullChip::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VSodorFullChip___024root___eval_final(VSodorFullChip___024root* vlSelf);

VL_ATTR_COLD void VSodorFullChip::final() {
    VSodorFullChip___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VSodorFullChip::hierName() const { return vlSymsp->name(); }
const char* VSodorFullChip::modelName() const { return "VSodorFullChip"; }
unsigned VSodorFullChip::threads() const { return 4; }
void VSodorFullChip::prepareClone() const { contextp()->prepareClone(); }
void VSodorFullChip::atClone() const {
    vlSymsp->__Vm_threadPoolp = static_cast<VlThreadPool*>(contextp()->threadPoolpOnClone());
}
