// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VCipher__pch.h"

//============================================================
// Constructors

VCipher::VCipher(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VCipher__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , io_plaintext_0{vlSymsp->TOP.io_plaintext_0}
    , io_plaintext_1{vlSymsp->TOP.io_plaintext_1}
    , io_plaintext_2{vlSymsp->TOP.io_plaintext_2}
    , io_plaintext_3{vlSymsp->TOP.io_plaintext_3}
    , io_plaintext_4{vlSymsp->TOP.io_plaintext_4}
    , io_plaintext_5{vlSymsp->TOP.io_plaintext_5}
    , io_plaintext_6{vlSymsp->TOP.io_plaintext_6}
    , io_plaintext_7{vlSymsp->TOP.io_plaintext_7}
    , io_plaintext_8{vlSymsp->TOP.io_plaintext_8}
    , io_plaintext_9{vlSymsp->TOP.io_plaintext_9}
    , io_plaintext_10{vlSymsp->TOP.io_plaintext_10}
    , io_plaintext_11{vlSymsp->TOP.io_plaintext_11}
    , io_plaintext_12{vlSymsp->TOP.io_plaintext_12}
    , io_plaintext_13{vlSymsp->TOP.io_plaintext_13}
    , io_plaintext_14{vlSymsp->TOP.io_plaintext_14}
    , io_plaintext_15{vlSymsp->TOP.io_plaintext_15}
    , io_roundKey_0{vlSymsp->TOP.io_roundKey_0}
    , io_roundKey_1{vlSymsp->TOP.io_roundKey_1}
    , io_roundKey_2{vlSymsp->TOP.io_roundKey_2}
    , io_roundKey_3{vlSymsp->TOP.io_roundKey_3}
    , io_roundKey_4{vlSymsp->TOP.io_roundKey_4}
    , io_roundKey_5{vlSymsp->TOP.io_roundKey_5}
    , io_roundKey_6{vlSymsp->TOP.io_roundKey_6}
    , io_roundKey_7{vlSymsp->TOP.io_roundKey_7}
    , io_roundKey_8{vlSymsp->TOP.io_roundKey_8}
    , io_roundKey_9{vlSymsp->TOP.io_roundKey_9}
    , io_roundKey_10{vlSymsp->TOP.io_roundKey_10}
    , io_roundKey_11{vlSymsp->TOP.io_roundKey_11}
    , io_roundKey_12{vlSymsp->TOP.io_roundKey_12}
    , io_roundKey_13{vlSymsp->TOP.io_roundKey_13}
    , io_roundKey_14{vlSymsp->TOP.io_roundKey_14}
    , io_roundKey_15{vlSymsp->TOP.io_roundKey_15}
    , io_start{vlSymsp->TOP.io_start}
    , io_state_out_0{vlSymsp->TOP.io_state_out_0}
    , io_state_out_1{vlSymsp->TOP.io_state_out_1}
    , io_state_out_2{vlSymsp->TOP.io_state_out_2}
    , io_state_out_3{vlSymsp->TOP.io_state_out_3}
    , io_state_out_4{vlSymsp->TOP.io_state_out_4}
    , io_state_out_5{vlSymsp->TOP.io_state_out_5}
    , io_state_out_6{vlSymsp->TOP.io_state_out_6}
    , io_state_out_7{vlSymsp->TOP.io_state_out_7}
    , io_state_out_8{vlSymsp->TOP.io_state_out_8}
    , io_state_out_9{vlSymsp->TOP.io_state_out_9}
    , io_state_out_10{vlSymsp->TOP.io_state_out_10}
    , io_state_out_11{vlSymsp->TOP.io_state_out_11}
    , io_state_out_12{vlSymsp->TOP.io_state_out_12}
    , io_state_out_13{vlSymsp->TOP.io_state_out_13}
    , io_state_out_14{vlSymsp->TOP.io_state_out_14}
    , io_state_out_15{vlSymsp->TOP.io_state_out_15}
    , io_state_out_valid{vlSymsp->TOP.io_state_out_valid}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VCipher::VCipher(const char* _vcname__)
    : VCipher(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VCipher::~VCipher() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VCipher___024root___eval_debug_assertions(VCipher___024root* vlSelf);
#endif  // VL_DEBUG
void VCipher___024root___eval_static(VCipher___024root* vlSelf);
void VCipher___024root___eval_initial(VCipher___024root* vlSelf);
void VCipher___024root___eval_settle(VCipher___024root* vlSelf);
void VCipher___024root___eval(VCipher___024root* vlSelf);

void VCipher::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VCipher::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VCipher___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VCipher___024root___eval_static(&(vlSymsp->TOP));
        VCipher___024root___eval_initial(&(vlSymsp->TOP));
        VCipher___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VCipher___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VCipher::eventsPending() { return false; }

uint64_t VCipher::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VCipher::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VCipher___024root___eval_final(VCipher___024root* vlSelf);

VL_ATTR_COLD void VCipher::final() {
    VCipher___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VCipher::hierName() const { return vlSymsp->name(); }
const char* VCipher::modelName() const { return "VCipher"; }
unsigned VCipher::threads() const { return 1; }
void VCipher::prepareClone() const { contextp()->prepareClone(); }
void VCipher::atClone() const {
    contextp()->threadPoolpOnClone();
}
