// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCipher.h for the primary calling header

#include "VCipher__pch.h"
#include "VCipher__Syms.h"
#include "VCipher___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__ico(VCipher___024root* vlSelf);
#endif  // VL_DEBUG

void VCipher___024root___eval_triggers__ico(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_triggers__ico\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCipher___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VCipher___024root___dump_triggers__act(VCipher___024root* vlSelf);
#endif  // VL_DEBUG

void VCipher___024root___eval_triggers__act(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_triggers__act\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VCipher___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void VCipher___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle);
void VCipher___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle);
void VCipher___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle);
void VCipher___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle);

void VCipher___024root___eval_nba(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___eval_nba\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->__Vm_even_cycle__nba = !vlSymsp->__Vm_even_cycle__nba;
    vlSymsp->__Vm_threadPoolp->workerp(0)->addTask(&VCipher___024root____Vthread__nba__t0__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(1)->addTask(&VCipher___024root____Vthread__nba__t1__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(2)->addTask(&VCipher___024root____Vthread__nba__t2__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    VCipher___024root____Vthread__nba__t3__s0(vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSelf->__Vm_mtaskstate_final__0nba.waitUntilUpstreamDone(vlSymsp->__Vm_even_cycle__nba);
    Verilated::mtaskId(0);
}

void VCipher___024root___nba_sequent__TOP__0(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask0(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask0\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 0;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__0(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__1(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask1(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask1\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 1;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__1(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__2(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask2(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask2\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 2;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__2(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__3(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask3(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask3\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 3;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__3(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__4(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask4(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask4\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 4;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__4(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__5(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask5(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask5\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 5;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__5(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__6(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask6(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask6\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 6;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__6(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__7(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask7(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask7\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 7;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__7(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__8(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask8(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask8\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 8;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__8(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__9(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask9(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask9\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 9;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__9(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__10(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask10(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask10\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 10;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__10(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__11(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask11(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask11\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 11;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__11(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__12(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask12(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask12\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 12;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__12(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__13(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask13(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask13\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 13;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__13(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__14(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask14(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask14\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 14;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__14(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__15(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask15(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask15\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 15;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__15(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__16(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask16(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask16\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 16;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__16(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__17(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask17(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask17\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 17;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__17(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__18(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask18(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask18\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 18;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__18(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__19(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask19(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask19\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 19;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__19(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__20(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask20(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask20\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 20;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__20(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__21(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask21(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask21\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 21;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__21(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__22(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask22(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask22\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 22;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__22(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root___nba_sequent__TOP__23(VCipher___024root* vlSelf);

void VCipher___024root__nba_mtask23(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root__nba_mtask23\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 23;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VCipher___024root___nba_sequent__TOP__23(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VCipher___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root____Vthread__nba__t0__s0\n"); );
    // Body
    VCipher___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCipher___024root*>(voidSelf);
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VCipher___024root__nba_mtask0(vlSelf);
    vlSelf->__Vm_mtaskstate_2.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_3.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_4.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_6.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_7.signalUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask1(vlSelf);
    vlSelf->__Vm_mtaskstate_8.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_9.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask5(vlSelf);
    vlSelf->__Vm_mtaskstate_17.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_19.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask16(vlSelf);
    vlSelf->__Vm_mtaskstate_10.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask10(vlSelf);
    vlSelf->__Vm_mtaskstate_15.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask15(vlSelf);
    vlSelf->__Vm_mtaskstate_21.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask21(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VCipher___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root____Vthread__nba__t1__s0\n"); );
    // Body
    VCipher___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCipher___024root*>(voidSelf);
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSelf->__Vm_mtaskstate_2.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask2(vlSelf);
    vlSelf->__Vm_mtaskstate_20.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_6.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask6(vlSelf);
    vlSelf->__Vm_mtaskstate_13.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_14.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_15.signalUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask12(vlSelf);
    vlSelf->__Vm_mtaskstate_11.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask11(vlSelf);
    vlSelf->__Vm_mtaskstate_17.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask17(vlSelf);
    vlSelf->__Vm_mtaskstate_22.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask22(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VCipher___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root____Vthread__nba__t2__s0\n"); );
    // Body
    VCipher___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCipher___024root*>(voidSelf);
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSelf->__Vm_mtaskstate_3.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask3(vlSelf);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_17.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_19.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_7.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask7(vlSelf);
    vlSelf->__Vm_mtaskstate_9.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_10.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_8.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask8(vlSelf);
    vlSelf->__Vm_mtaskstate_13.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask13(vlSelf);
    vlSelf->__Vm_mtaskstate_18.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask18(vlSelf);
    vlSelf->__Vm_mtaskstate_23.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask23(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VCipher___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root____Vthread__nba__t3__s0\n"); );
    // Body
    VCipher___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VCipher___024root*>(voidSelf);
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSelf->__Vm_mtaskstate_4.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask4(vlSelf);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_22.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_20.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask20(vlSelf);
    vlSelf->__Vm_mtaskstate_9.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask9(vlSelf);
    vlSelf->__Vm_mtaskstate_14.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask14(vlSelf);
    vlSelf->__Vm_mtaskstate_19.waitUntilUpstreamDone(even_cycle);
    VCipher___024root__nba_mtask19(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}
