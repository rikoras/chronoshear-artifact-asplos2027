// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCipher.h for the primary calling header

#include "VCipher__pch.h"
#include "VCipher___024root.h"

VL_ATTR_COLD void VCipher___024root___stl_sequent__TOP__3(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___stl_sequent__TOP__3\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_12 
        = ((IData)(vlSelfRef.io_roundKey_12) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_12)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_12))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_13 
        = ((IData)(vlSelfRef.io_roundKey_13) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_13)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_13))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_14 
        = ((IData)(vlSelfRef.io_roundKey_14) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_14)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_14))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_15 
        = ((IData)(vlSelfRef.io_roundKey_15) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_15)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_15))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_8 
        = ((IData)(vlSelfRef.io_roundKey_8) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_8)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_8)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_8))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_9 
        = ((IData)(vlSelfRef.io_roundKey_9) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_9)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_13)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_9))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_10 
        = ((IData)(vlSelfRef.io_roundKey_10) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_10)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_2)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_10))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_11 
        = ((IData)(vlSelfRef.io_roundKey_11) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_11)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_7)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_11))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_4 
        = ((IData)(vlSelfRef.io_roundKey_4) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_4)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_4)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_4))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_5 
        = ((IData)(vlSelfRef.io_roundKey_5) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_5)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_9)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_5))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_6 
        = ((IData)(vlSelfRef.io_roundKey_6) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_6)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_14)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_6))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_7 
        = ((IData)(vlSelfRef.io_roundKey_7) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_7)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_3)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_7))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_0 
        = ((IData)(vlSelfRef.io_roundKey_0) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_0)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_0)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_0))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_1 
        = ((IData)(vlSelfRef.io_roundKey_1) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_1)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_5)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_1))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_2 
        = ((IData)(vlSelfRef.io_roundKey_2) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_2)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_10)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_2))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_3 
        = ((IData)(vlSelfRef.io_roundKey_3) ^ ((1U 
                                                == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                ? (IData)(vlSelfRef.io_plaintext_3)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                    ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_15)
                                                    : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_3))));
}

VL_ATTR_COLD void VCipher___024root___eval_triggers__stl(VCipher___024root* vlSelf);
VL_ATTR_COLD void VCipher___024root___eval_stl(VCipher___024root* vlSelf);

VL_ATTR_COLD bool VCipher___024root___eval_phase__stl(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_phase__stl\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VCipher___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        VCipher___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__ico(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___dump_triggers__ico\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__act(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___dump_triggers__act\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__nba(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___dump_triggers__nba\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VCipher___024root___ctor_var_reset(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___ctor_var_reset\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_plaintext_0 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_1 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_2 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_3 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_4 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_5 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_6 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_7 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_8 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_9 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_10 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_11 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_12 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_13 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_14 = VL_RAND_RESET_I(8);
    vlSelf->io_plaintext_15 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_0 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_1 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_2 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_3 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_4 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_5 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_6 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_7 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_8 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_9 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_10 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_11 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_12 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_13 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_14 = VL_RAND_RESET_I(8);
    vlSelf->io_roundKey_15 = VL_RAND_RESET_I(8);
    vlSelf->io_start = VL_RAND_RESET_I(1);
    vlSelf->io_state_out_0 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_1 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_2 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_3 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_4 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_5 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_6 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_7 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_8 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_9 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_10 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_11 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_12 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_13 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_14 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_15 = VL_RAND_RESET_I(8);
    vlSelf->io_state_out_valid = VL_RAND_RESET_I(1);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_0 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_1 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_2 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_3 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_4 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_5 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_6 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_7 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_8 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_9 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_10 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_11 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_12 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_13 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_14 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__AddRoundKeyModule_io_state_out_15 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_0 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_1 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_2 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_3 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_4 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_5 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_6 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_7 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_8 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_9 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_10 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_11 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_12 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_13 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_14 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__SubBytesModule_io_state_out_15 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_0 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_1 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_2 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_3 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_4 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_5 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_6 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_7 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_8 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_9 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_10 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_11 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_12 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_13 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_14 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__MixColumnsModule_io_state_out_15 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_0 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_1 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_2 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_3 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_4 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_5 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_6 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_7 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_8 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_9 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_10 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_11 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_12 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_13 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_14 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__state_15 = VL_RAND_RESET_I(8);
    vlSelf->Cipher__DOT__rounds = VL_RAND_RESET_I(4);
    vlSelf->Cipher__DOT__STM = VL_RAND_RESET_I(2);
    vlSelf->Cipher__DOT___T_253 = VL_RAND_RESET_I(4);
    vlSelf->Cipher__DOT___GEN_1 = VL_RAND_RESET_I(2);
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
}
