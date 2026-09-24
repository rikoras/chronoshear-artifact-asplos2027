// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSodorFullChip.h for the primary calling header

#include "VSodorFullChip__pch.h"
#include "VSodorFullChip__Syms.h"
#include "VSodorFullChip___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__ico(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG

void VSodorFullChip___024root___eval_triggers__ico(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_triggers__ico\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSodorFullChip___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__act(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG

void VSodorFullChip___024root___eval_triggers__act(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_triggers__act\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSodorFullChip___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void VSodorFullChip___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle);
void VSodorFullChip___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle);
void VSodorFullChip___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle);
void VSodorFullChip___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle);

void VSodorFullChip___024root___eval_nba(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_nba\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->__Vm_even_cycle__nba = !vlSymsp->__Vm_even_cycle__nba;
    vlSymsp->__Vm_threadPoolp->workerp(0)->addTask(&VSodorFullChip___024root____Vthread__nba__t0__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(1)->addTask(&VSodorFullChip___024root____Vthread__nba__t1__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(2)->addTask(&VSodorFullChip___024root____Vthread__nba__t2__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    VSodorFullChip___024root____Vthread__nba__t3__s0(vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSelf->__Vm_mtaskstate_final__0nba.waitUntilUpstreamDone(vlSymsp->__Vm_even_cycle__nba);
    Verilated::mtaskId(0);
}

void VSodorFullChip___024root___nba_sequent__TOP__0(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask0(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask0\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 0;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__0(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__1(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask1(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask1\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 1;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__1(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__2(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask2(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask2\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 2;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__2(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__3(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask3(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask3\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 3;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__3(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__4(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask4(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask4\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 4;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__4(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__5(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask5(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask5\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 5;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__5(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__6(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask6(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask6\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 6;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__6(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__7(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask7(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask7\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 7;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__7(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__8(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask8(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask8\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 8;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__8(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__9(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask9(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask9\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 9;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__9(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__10(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask10(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask10\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 10;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__10(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__11(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask11(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask11\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 11;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__11(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__12(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask12(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask12\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 12;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__12(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__13(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask13(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask13\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 13;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__13(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__14(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask14(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask14\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 14;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__14(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__15(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask15(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask15\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 15;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__15(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__16(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask16(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask16\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 16;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__16(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__17(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask17(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask17\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 17;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__17(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__18(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask18(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask18\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 18;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__18(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__19(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask19(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask19\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 19;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__19(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__20(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask20(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask20\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 20;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__20(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__21(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask21(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask21\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 21;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__21(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__22(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask22(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask22\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 22;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__22(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__23(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask23(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask23\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 23;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__23(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__24(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask24(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask24\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 24;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__24(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__25(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask25(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask25\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 25;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__25(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__26(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask26(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask26\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 26;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__26(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__27(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask27(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask27\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 27;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__27(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__28(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask28(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask28\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 28;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__28(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__29(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask29(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask29\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 29;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__29(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__30(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask30(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask30\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 30;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__30(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root___nba_sequent__TOP__31(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root__nba_mtask31(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root__nba_mtask31\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 31;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__31(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VSodorFullChip___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root____Vthread__nba__t0__s0\n"); );
    // Body
    VSodorFullChip___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VSodorFullChip___024root*>(voidSelf);
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VSodorFullChip___024root__nba_mtask5(vlSelf);
    vlSelf->__Vm_mtaskstate_8.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_9.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask9(vlSelf);
    vlSelf->__Vm_mtaskstate_10.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_7.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask7(vlSelf);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_20.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_24.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_27.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_30.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask23(vlSelf);
    vlSelf->__Vm_mtaskstate_25.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask25(vlSelf);
    vlSelf->__Vm_mtaskstate_26.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask26(vlSelf);
    vlSelf->__Vm_mtaskstate_22.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask22(vlSelf);
    vlSelf->__Vm_mtaskstate_29.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask29(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VSodorFullChip___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root____Vthread__nba__t1__s0\n"); );
    // Body
    VSodorFullChip___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VSodorFullChip___024root*>(voidSelf);
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VSodorFullChip___024root__nba_mtask4(vlSelf);
    vlSelf->__Vm_mtaskstate_6.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_8.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask8(vlSelf);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_17.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_10.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask10(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_24.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask24(vlSelf);
    vlSelf->__Vm_mtaskstate_26.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_18.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask18(vlSelf);
    vlSelf->__Vm_mtaskstate_14.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask14(vlSelf);
    vlSelf->__Vm_mtaskstate_21.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask21(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VSodorFullChip___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root____Vthread__nba__t2__s0\n"); );
    // Body
    VSodorFullChip___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VSodorFullChip___024root*>(voidSelf);
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VSodorFullChip___024root__nba_mtask0(vlSelf);
    vlSelf->__Vm_mtaskstate_6.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_8.signalUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask2(vlSelf);
    vlSelf->__Vm_mtaskstate_10.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_12.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_14.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask11(vlSelf);
    vlSelf->__Vm_mtaskstate_12.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_14.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_24.signalUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask15(vlSelf);
    vlSelf->__Vm_mtaskstate_30.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask30(vlSelf);
    VSodorFullChip___024root__nba_mtask13(vlSelf);
    vlSelf->__Vm_mtaskstate_20.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask20(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VSodorFullChip___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root____Vthread__nba__t3__s0\n"); );
    // Body
    VSodorFullChip___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VSodorFullChip___024root*>(voidSelf);
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VSodorFullChip___024root__nba_mtask3(vlSelf);
    vlSelf->__Vm_mtaskstate_8.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_9.signalUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask1(vlSelf);
    vlSelf->__Vm_mtaskstate_6.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask6(vlSelf);
    vlSelf->__Vm_mtaskstate_7.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_11.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_17.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask17(vlSelf);
    vlSelf->__Vm_mtaskstate_18.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_20.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_21.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_22.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_23.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_24.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_16.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask16(vlSelf);
    vlSelf->__Vm_mtaskstate_24.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_25.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_30.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_27.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask27(vlSelf);
    VSodorFullChip___024root__nba_mtask28(vlSelf);
    vlSelf->__Vm_mtaskstate_29.signalUpstreamDone(even_cycle);
    vlSelf->__Vm_mtaskstate_12.waitUntilUpstreamDone(even_cycle);
    VSodorFullChip___024root__nba_mtask12(vlSelf);
    VSodorFullChip___024root__nba_mtask19(vlSelf);
    VSodorFullChip___024root__nba_mtask31(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}
