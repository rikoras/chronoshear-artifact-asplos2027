// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VCipher.h for the primary calling header

#ifndef VERILATED_VCIPHER___024ROOT_H_
#define VERILATED_VCIPHER___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_threads.h"


class VCipher__Syms;

class alignas(VL_CACHE_LINE_BYTES) VCipher___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*3:0*/ Cipher__DOT__rounds;
        CData/*1:0*/ Cipher__DOT__STM;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_0;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_5;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_10;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_15;
        VL_IN8(io_plaintext_3,7,0);
        VL_IN8(io_roundKey_3,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_3;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_3;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_9;
        VL_IN8(io_plaintext_9,7,0);
        VL_IN8(io_roundKey_9,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_9;
        VL_IN8(io_plaintext_8,7,0);
        VL_IN8(io_roundKey_8,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_8;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_8;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_14;
        VL_IN8(io_plaintext_14,7,0);
        VL_IN8(io_roundKey_14,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_14;
        VL_IN8(io_plaintext_13,7,0);
        VL_IN8(io_roundKey_13,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_13;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_13;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_12;
        VL_IN8(io_plaintext_12,7,0);
        VL_IN8(io_roundKey_12,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_12;
        VL_IN8(io_plaintext_10,7,0);
        VL_IN8(io_roundKey_10,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_10;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_10;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_11;
        VL_IN8(io_plaintext_11,7,0);
        VL_IN8(io_roundKey_11,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_11;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_8;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_13;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_2;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_7;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_1;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_6;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_11;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_12;
        VL_IN8(io_plaintext_15,7,0);
        VL_IN8(io_roundKey_15,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_15;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_15;
        VL_IN8(reset,0,0);
        VL_IN8(io_start,0,0);
        VL_OUT8(io_state_out_0,7,0);
        VL_OUT8(io_state_out_1,7,0);
        VL_OUT8(io_state_out_2,7,0);
        VL_OUT8(io_state_out_3,7,0);
        VL_OUT8(io_state_out_4,7,0);
        VL_OUT8(io_state_out_5,7,0);
        VL_OUT8(io_state_out_6,7,0);
        VL_OUT8(io_state_out_7,7,0);
        VL_OUT8(io_state_out_8,7,0);
        VL_OUT8(io_state_out_9,7,0);
        VL_OUT8(io_state_out_10,7,0);
        VL_OUT8(io_state_out_11,7,0);
    };
    struct {
        VL_OUT8(io_state_out_12,7,0);
        VL_OUT8(io_state_out_13,7,0);
        VL_OUT8(io_state_out_14,7,0);
        VL_OUT8(io_state_out_15,7,0);
        VL_OUT8(io_state_out_valid,0,0);
        CData/*7:0*/ Cipher__DOT__state_3;
        CData/*7:0*/ Cipher__DOT__state_4;
        CData/*3:0*/ Cipher__DOT___T_253;
        CData/*1:0*/ Cipher__DOT___GEN_1;
        CData/*7:0*/ Cipher__DOT__state_1;
        CData/*7:0*/ Cipher__DOT__state_6;
        CData/*7:0*/ Cipher__DOT__state_0;
        CData/*7:0*/ Cipher__DOT__state_5;
        CData/*7:0*/ Cipher__DOT__state_11;
        CData/*7:0*/ Cipher__DOT__state_12;
        CData/*7:0*/ Cipher__DOT__state_2;
        CData/*7:0*/ Cipher__DOT__state_7;
        CData/*7:0*/ Cipher__DOT__state_9;
        CData/*7:0*/ Cipher__DOT__state_14;
        CData/*7:0*/ Cipher__DOT__state_8;
        CData/*7:0*/ Cipher__DOT__state_13;
        CData/*7:0*/ Cipher__DOT__state_10;
        CData/*7:0*/ Cipher__DOT__state_15;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_1;
        VL_IN8(io_plaintext_1,7,0);
        VL_IN8(io_roundKey_1,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_1;
        VL_IN8(io_plaintext_0,7,0);
        VL_IN8(io_roundKey_0,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_0;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_0;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_4;
        VL_IN8(io_plaintext_4,7,0);
        VL_IN8(io_roundKey_4,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_4;
        VL_IN8(io_plaintext_2,7,0);
        VL_IN8(io_roundKey_2,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_2;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_2;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_6;
        VL_IN8(io_plaintext_6,7,0);
        VL_IN8(io_roundKey_6,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_6;
        VL_IN8(io_plaintext_5,7,0);
        VL_IN8(io_roundKey_5,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_5;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_5;
        CData/*7:0*/ Cipher__DOT__AddRoundKeyModule_io_state_out_7;
        VL_IN8(io_plaintext_7,7,0);
        VL_IN8(io_roundKey_7,7,0);
        CData/*7:0*/ Cipher__DOT__MixColumnsModule_io_state_out_7;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_3;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_4;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_9;
        CData/*7:0*/ Cipher__DOT__SubBytesModule_io_state_out_14;
        VL_IN8(clock,0,0);
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        IData/*31:0*/ __VactIterCount;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;
    VlMTaskVertex __Vm_mtaskstate_16;
    VlMTaskVertex __Vm_mtaskstate_10;
    VlMTaskVertex __Vm_mtaskstate_15;
    VlMTaskVertex __Vm_mtaskstate_21;
    VlMTaskVertex __Vm_mtaskstate_2;
    VlMTaskVertex __Vm_mtaskstate_6;
    VlMTaskVertex __Vm_mtaskstate_11;
    VlMTaskVertex __Vm_mtaskstate_17;
    VlMTaskVertex __Vm_mtaskstate_22;
    VlMTaskVertex __Vm_mtaskstate_3;
    VlMTaskVertex __Vm_mtaskstate_7;
    VlMTaskVertex __Vm_mtaskstate_8;
    VlMTaskVertex __Vm_mtaskstate_13;
    VlMTaskVertex __Vm_mtaskstate_18;
    VlMTaskVertex __Vm_mtaskstate_23;
    VlMTaskVertex __Vm_mtaskstate_4;
    VlMTaskVertex __Vm_mtaskstate_20;
    VlMTaskVertex __Vm_mtaskstate_9;
    VlMTaskVertex __Vm_mtaskstate_14;
    VlMTaskVertex __Vm_mtaskstate_19;
    VlMTaskVertex __Vm_mtaskstate_final__0nba;

    // INTERNAL VARIABLES
    VCipher__Syms* const vlSymsp;

    // CONSTRUCTORS
    VCipher___024root(VCipher__Syms* symsp, const char* v__name);
    ~VCipher___024root();
    VL_UNCOPYABLE(VCipher___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
