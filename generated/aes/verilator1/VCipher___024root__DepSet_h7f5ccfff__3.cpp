// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCipher.h for the primary calling header

#include "VCipher__pch.h"
#include "VCipher___024root.h"

VL_INLINE_OPT void VCipher___024root___nba_sequent__TOP__3(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___nba_sequent__TOP__3\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.io_state_out_valid) {
        vlSelfRef.io_state_out_0 = vlSelfRef.Cipher__DOT__state_0;
        vlSelfRef.io_state_out_1 = vlSelfRef.Cipher__DOT__state_1;
        vlSelfRef.io_state_out_2 = vlSelfRef.Cipher__DOT__state_2;
        vlSelfRef.io_state_out_3 = vlSelfRef.Cipher__DOT__state_3;
        vlSelfRef.io_state_out_4 = vlSelfRef.Cipher__DOT__state_4;
        vlSelfRef.io_state_out_5 = vlSelfRef.Cipher__DOT__state_5;
        vlSelfRef.io_state_out_6 = vlSelfRef.Cipher__DOT__state_6;
        vlSelfRef.io_state_out_7 = vlSelfRef.Cipher__DOT__state_7;
        vlSelfRef.io_state_out_8 = vlSelfRef.Cipher__DOT__state_8;
        vlSelfRef.io_state_out_9 = vlSelfRef.Cipher__DOT__state_9;
        vlSelfRef.io_state_out_10 = vlSelfRef.Cipher__DOT__state_10;
        vlSelfRef.io_state_out_11 = vlSelfRef.Cipher__DOT__state_11;
        vlSelfRef.io_state_out_12 = vlSelfRef.Cipher__DOT__state_12;
        vlSelfRef.io_state_out_13 = vlSelfRef.Cipher__DOT__state_13;
        vlSelfRef.io_state_out_14 = vlSelfRef.Cipher__DOT__state_14;
        vlSelfRef.io_state_out_15 = vlSelfRef.Cipher__DOT__state_15;
    } else {
        vlSelfRef.io_state_out_0 = 0U;
        vlSelfRef.io_state_out_1 = 0U;
        vlSelfRef.io_state_out_2 = 0U;
        vlSelfRef.io_state_out_3 = 0U;
        vlSelfRef.io_state_out_4 = 0U;
        vlSelfRef.io_state_out_5 = 0U;
        vlSelfRef.io_state_out_6 = 0U;
        vlSelfRef.io_state_out_7 = 0U;
        vlSelfRef.io_state_out_8 = 0U;
        vlSelfRef.io_state_out_9 = 0U;
        vlSelfRef.io_state_out_10 = 0U;
        vlSelfRef.io_state_out_11 = 0U;
        vlSelfRef.io_state_out_12 = 0U;
        vlSelfRef.io_state_out_13 = 0U;
        vlSelfRef.io_state_out_14 = 0U;
        vlSelfRef.io_state_out_15 = 0U;
    }
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

void VCipher___024root___eval_triggers__act(VCipher___024root* vlSelf);
void VCipher___024root___eval_act(VCipher___024root* vlSelf);

bool VCipher___024root___eval_phase__act(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_phase__act\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VCipher___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VCipher___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void VCipher___024root___eval_nba(VCipher___024root* vlSelf);

bool VCipher___024root___eval_phase__nba(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_phase__nba\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VCipher___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__ico(VCipher___024root* vlSelf);
#endif  // VL_DEBUG
bool VCipher___024root___eval_phase__ico(VCipher___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__nba(VCipher___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__act(VCipher___024root* vlSelf);
#endif  // VL_DEBUG

void VCipher___024root___eval(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VCipher___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/aes/verilog/Cipher.v", 12477, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VCipher___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VCipher___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/aes/verilog/Cipher.v", 12477, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VCipher___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/aes/verilog/Cipher.v", 12477, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VCipher___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VCipher___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VCipher___024root___eval_debug_assertions(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_debug_assertions\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.io_start & 0xfeU)))) {
        Verilated::overWidthError("io_start");}
}
#endif  // VL_DEBUG
