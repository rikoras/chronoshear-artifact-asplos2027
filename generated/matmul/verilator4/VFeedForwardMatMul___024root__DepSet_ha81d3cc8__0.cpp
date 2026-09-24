// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VFeedForwardMatMul.h for the primary calling header

#include "VFeedForwardMatMul__pch.h"
#include "VFeedForwardMatMul__Syms.h"
#include "VFeedForwardMatMul___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__ico(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG

void VFeedForwardMatMul___024root___eval_triggers__ico(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_triggers__ico\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFeedForwardMatMul___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VFeedForwardMatMul___024root___dump_triggers__act(VFeedForwardMatMul___024root* vlSelf);
#endif  // VL_DEBUG

void VFeedForwardMatMul___024root___eval_triggers__act(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_triggers__act\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VFeedForwardMatMul___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void VFeedForwardMatMul___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle);
void VFeedForwardMatMul___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle);
void VFeedForwardMatMul___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle);
void VFeedForwardMatMul___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle);

void VFeedForwardMatMul___024root___eval_nba(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root___eval_nba\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->__Vm_even_cycle__nba = !vlSymsp->__Vm_even_cycle__nba;
    vlSymsp->__Vm_threadPoolp->workerp(0)->addTask(&VFeedForwardMatMul___024root____Vthread__nba__t0__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(1)->addTask(&VFeedForwardMatMul___024root____Vthread__nba__t1__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSymsp->__Vm_threadPoolp->workerp(2)->addTask(&VFeedForwardMatMul___024root____Vthread__nba__t2__s0, vlSelf, vlSymsp->__Vm_even_cycle__nba);
    VFeedForwardMatMul___024root____Vthread__nba__t3__s0(vlSelf, vlSymsp->__Vm_even_cycle__nba);
    vlSelf->__Vm_mtaskstate_final__0nba.waitUntilUpstreamDone(vlSymsp->__Vm_even_cycle__nba);
    Verilated::mtaskId(0);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__0(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask0(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask0\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 0;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__0(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__1(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask1(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask1\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 1;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__1(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__2(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask2(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask2\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 2;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__2(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__3(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask3(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask3\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 3;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__3(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__4(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask4(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask4\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 4;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__4(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__5(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask5(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask5\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 5;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__5(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__6(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask6(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask6\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 6;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__6(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__7(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask7(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask7\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 7;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__7(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__8(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask8(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask8\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 8;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__8(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__9(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask9(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask9\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 9;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__9(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__10(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask10(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask10\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 10;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__10(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root___nba_sequent__TOP__11(VFeedForwardMatMul___024root* vlSelf);

void VFeedForwardMatMul___024root__nba_mtask11(VFeedForwardMatMul___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root__nba_mtask11\n"); );
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    static constexpr unsigned taskId = 11;
    Verilated::mtaskId(taskId);
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VFeedForwardMatMul___024root___nba_sequent__TOP__11(vlSelf);
    }
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
}

void VFeedForwardMatMul___024root____Vthread__nba__t0__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root____Vthread__nba__t0__s0\n"); );
    // Body
    VFeedForwardMatMul___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFeedForwardMatMul___024root*>(voidSelf);
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VFeedForwardMatMul___024root__nba_mtask3(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask7(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask11(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VFeedForwardMatMul___024root____Vthread__nba__t1__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root____Vthread__nba__t1__s0\n"); );
    // Body
    VFeedForwardMatMul___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFeedForwardMatMul___024root*>(voidSelf);
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VFeedForwardMatMul___024root__nba_mtask1(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask5(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask9(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VFeedForwardMatMul___024root____Vthread__nba__t2__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root____Vthread__nba__t2__s0\n"); );
    // Body
    VFeedForwardMatMul___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFeedForwardMatMul___024root*>(voidSelf);
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VFeedForwardMatMul___024root__nba_mtask2(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask6(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask10(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}

void VFeedForwardMatMul___024root____Vthread__nba__t3__s0(void* voidSelf, bool even_cycle) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VFeedForwardMatMul___024root____Vthread__nba__t3__s0\n"); );
    // Body
    VFeedForwardMatMul___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VFeedForwardMatMul___024root*>(voidSelf);
    VFeedForwardMatMul__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VFeedForwardMatMul___024root__nba_mtask0(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask4(vlSelf);
    VFeedForwardMatMul___024root__nba_mtask8(vlSelf);
    vlSelf->__Vm_mtaskstate_final__0nba.signalUpstreamDone(even_cycle);
}
