// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSodorFullChip.h for the primary calling header

#include "VSodorFullChip__pch.h"
#include "VSodorFullChip___024root.h"

void VSodorFullChip___024root___ico_sequent__TOP__0(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root___eval_ico(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_ico\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VSodorFullChip___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VSodorFullChip___024root___ico_sequent__TOP__0(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___ico_sequent__TOP__0\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.io_host_rdata = (((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                 [(0x1fffffU & ((IData)(3U) 
                                                + vlSelfRef.io_host_addr))] 
                                 << 0x18U) | (vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                              [(0x1fffffU 
                                                & ((IData)(2U) 
                                                   + vlSelfRef.io_host_addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                   [(0x1fffffU & ((IData)(1U) 
                                                  + vlSelfRef.io_host_addr))] 
                                   << 8U) | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                  [(0x1fffffU & vlSelfRef.io_host_addr)]));
    vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes_MPORT_4_en 
        = ((IData)(vlSelfRef.io_host_valid) & (IData)(vlSelfRef.io_host_write));
    vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3 
        = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val) 
           & ((~ (IData)(vlSelfRef.io_host_valid)) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_fcn)));
    if (vlSelfRef.reset) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___GEN_91 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
    } else {
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen) {
            if ((0xb00U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                    = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                               >> 0x1aU));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                               >> 6U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                    = (((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                                 >> 0x1aU)) << 0x1aU) 
                       | (IData)(((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                                   >> 6U) >> 0x20U)));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] 
                    = ((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                                >> 0x1aU)) >> 6U);
            } else {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                    = (IData)(((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                    << 0x20U) | (QData)((IData)(
                                                                (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_) 
                                                                  << 6U) 
                                                                 | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))
                                : (QData)((IData)((0x7fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] 
                    = (IData)((((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_) 
                                                                   << 6U) 
                                                                  | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))
                                 : (QData)((IData)(
                                                   (0x7fU 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                    = (IData)(((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                    << 0x1aU) | (QData)((IData)(
                                                                (0x3ffffffU 
                                                                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_)))))
                                : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                    = (IData)((((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                     << 0x1aU) | (QData)((IData)(
                                                                 (0x3ffffffU 
                                                                  & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_)))))
                                 : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
            }
            if ((0xb02U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                               >> 6U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                    = (((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                                 >> 0x1aU)) << 0x1aU) 
                       | (IData)(((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                                   >> 6U) >> 0x20U)));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] 
                    = ((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                                >> 0x1aU)) >> 6U);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                    = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                               >> 0x1aU));
            } else {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                    = (IData)(((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                    << 0x1aU) | (QData)((IData)(
                                                                (0x3ffffffU 
                                                                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1)))))
                                : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                    = (IData)((((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                     << 0x1aU) | (QData)((IData)(
                                                                 (0x3ffffffU 
                                                                  & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1)))))
                                 : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                    = (IData)(((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                    << 0x20U) | (QData)((IData)(
                                                                (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1) 
                                                                  << 6U) 
                                                                 | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1)))))
                                : (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1))));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] 
                    = (IData)((((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1) 
                                                                   << 6U) 
                                                                  | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1)))))
                                 : (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1))) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
            }
        } else {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                = (0x7fU & ((IData)(1U) + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0);
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0 
                           >> 0x20U));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1);
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1 
                           >> 0x20U));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
        }
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___GEN_91 
            = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) 
                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))
                ? 0U : (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                         & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))
                         ? ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                             ? 0U : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_4))
                         : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_fcn)));
    }
}

void VSodorFullChip___024root___eval_triggers__ico(VSodorFullChip___024root* vlSelf);

bool VSodorFullChip___024root___eval_phase__ico(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_phase__ico\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VSodorFullChip___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VSodorFullChip___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VSodorFullChip___024root___eval_act(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_act\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VSodorFullChip___024root___nba_sequent__TOP__0(VSodorFullChip___024root* vlSelf);

void VSodorFullChip___024root___eval_nba(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_nba\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSodorFullChip___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VSodorFullChip___024root___nba_sequent__TOP__0(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___nba_sequent__TOP__0\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_eq;
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_eq = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_lt;
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_lt = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_ltu;
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_ltu = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_50;
    SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_50 = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_51;
    SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_51 = 0;
    IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr_io_rw_rdata;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr_io_rw_rdata = 0;
    QData/*63:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value = 0;
    QData/*63:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value_1;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value_1 = 0;
    QData/*34:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__read_mstatus;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__read_mstatus = 0;
    SData/*15:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_1;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_1 = 0;
    IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_2;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_2 = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call = 0;
    CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_1;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_1 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_2;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_2 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_3;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_3 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_4;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_4 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_5;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_5 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_6;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_6 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_7;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_7 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_8;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_8 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_9;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_9 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_10;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_10 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_11;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_11 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_12;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_12 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_13;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_13 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_14;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_14 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_15;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_15 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_16;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_16 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_17;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_17 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_18;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_18 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_19;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_19 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_20;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_20 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_21;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_21 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_22;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_22 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_23;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_23 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_24;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_24 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_25;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_25 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_26;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_26 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_27;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_27 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_28;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_28 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_29;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_29 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_30;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_30 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_31;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_31 = 0;
    QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_32;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_32 = 0;
    QData/*34:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75;
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75 = 0;
    SData/*15:0*/ SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2;
    SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2 = 0;
    IData/*31:0*/ __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc = 0;
    CData/*4:0*/ __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr = 0;
    CData/*0:0*/ __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen = 0;
    CData/*4:0*/ __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr = 0;
    IData/*31:0*/ __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v0;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v0 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v0;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v0 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v0;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v0 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v1;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v1 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v1;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v1 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v1;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v1 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v2;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v2 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v2;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v2 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v2;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v2 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v3;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v3 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v3;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v3 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v3;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v3 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v4;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v4 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v4;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v4 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v4;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v4 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v5;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v5 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v5;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v5 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v5;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v5 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v6;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v6 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v6;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v6 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v6;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v6 = 0;
    CData/*7:0*/ __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v7;
    __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v7 = 0;
    IData/*20:0*/ __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v7;
    __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v7 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v7;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v7 = 0;
    IData/*31:0*/ __VdlyVal__SodorFullChip__DOT__regfile__DOT__regfile__v0;
    __VdlyVal__SodorFullChip__DOT__regfile__DOT__regfile__v0 = 0;
    CData/*4:0*/ __VdlyDim0__SodorFullChip__DOT__regfile__DOT__regfile__v0;
    __VdlyDim0__SodorFullChip__DOT__regfile__DOT__regfile__v0 = 0;
    CData/*0:0*/ __VdlySet__SodorFullChip__DOT__regfile__DOT__regfile__v0;
    __VdlySet__SodorFullChip__DOT__regfile__DOT__regfile__v0 = 0;
    // Body
    __VdlySet__SodorFullChip__DOT__regfile__DOT__regfile__v0 = 0U;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v0 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v1 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v2 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v3 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v4 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v5 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v6 = 0U;
    __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v7 = 0U;
    __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc;
    if (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_ctrl_rf_wen) 
         & (0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr)))) {
        __VdlyVal__SodorFullChip__DOT__regfile__DOT__regfile__v0 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata;
        __VdlyDim0__SodorFullChip__DOT__regfile__DOT__regfile__v0 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr;
        __VdlySet__SodorFullChip__DOT__regfile__DOT__regfile__v0 = 1U;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (1U 
                                                   & ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen)
                                                       ? 
                                                      ((0x300U 
                                                        == 
                                                        (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                         >> 0x14U))
                                                        ? (IData)(
                                                                  (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mstatus_T_8 
                                                                   >> 7U))
                                                        : 
                                                       (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret) 
                                                         & (~ 
                                                            (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                             >> 0x1eU))) 
                                                        | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie)))
                                                       : 
                                                      (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret) 
                                                        & (~ 
                                                           (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                            >> 0x1eU))) 
                                                       | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie)))));
    if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
        __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata 
            = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out
                : ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
                    ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out
                    : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
                        ? vlSelfRef.SodorFullChip__DOT__memory_io_core_0_resp_bits_data
                        : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___mem_wbdata_T_4)));
        __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr;
    }
    if (((IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3) 
         & (0U < (IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT__storeBytes)))) {
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v0 
            = (0xffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data);
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v0 
            = (0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out);
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v0 = 1U;
    }
    if (((IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3) 
         & (1U < (IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT__storeBytes)))) {
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v1 
            = (0xffU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data 
                        >> 8U));
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v1 
            = (0x1fffffU & ((IData)(1U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v1 = 1U;
    }
    if (((IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3) 
         & (2U < (IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT__storeBytes)))) {
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v2 
            = (0xffU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data 
                        >> 0x10U));
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v2 
            = (0x1fffffU & ((IData)(2U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v2 = 1U;
    }
    if (((IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3) 
         & (3U < (IData)(vlSelfRef.SodorFullChip__DOT__memory__DOT__storeBytes)))) {
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v3 
            = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data 
               >> 0x18U);
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v3 
            = (0x1fffffU & ((IData)(3U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v3 = 1U;
    }
    if (vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes_MPORT_4_en) {
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v4 
            = (0xffU & vlSelfRef.io_host_wdata);
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v4 
            = (0x1fffffU & vlSelfRef.io_host_addr);
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v4 = 1U;
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v5 
            = (0xffU & (vlSelfRef.io_host_wdata >> 8U));
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v5 
            = (0x1fffffU & ((IData)(1U) + vlSelfRef.io_host_addr));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v5 = 1U;
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v6 
            = (0xffU & (vlSelfRef.io_host_wdata >> 0x10U));
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v6 
            = (0x1fffffU & ((IData)(2U) + vlSelfRef.io_host_addr));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v6 = 1U;
        __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v7 
            = (vlSelfRef.io_host_wdata >> 0x18U);
        __VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v7 
            = (0x1fffffU & ((IData)(3U) + vlSelfRef.io_host_addr));
        __VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v7 = 1U;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_135);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_134);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_133);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_132);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_131);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_130);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_129);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_128);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_127);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_126);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_125);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_124);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_122);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_121);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_118);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_109);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_123);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_108);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_107);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_110);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_114);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_117);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_120);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_119);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_111);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_112);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_113);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_115);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_116);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_136);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_137);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33 
        = (0xffffffffffULL & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_138);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_mtip 
        = (1U & (~ (IData)(vlSelfRef.reset)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_ 
        = (0x3fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U]);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
        = (0x3ffffffffffffffULL & (((QData)((IData)(
                                                    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U]))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
        = (0x3ffffffffffffffULL & (((QData)((IData)(
                                                    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U]))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1 
        = (0x3fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U]);
    if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
         & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr 
            = ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                ? 0U : (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                 >> 7U)));
    } else if (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
                & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr = 0U;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_valid 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) 
                                                   & ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_valid) 
                                                      & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG)))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mie 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (1U 
                                                   & ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen)
                                                       ? 
                                                      ((0x300U 
                                                        == 
                                                        (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                         >> 0x14U))
                                                        ? (IData)(
                                                                  (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mstatus_T_8 
                                                                   >> 3U))
                                                        : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_7))
                                                       : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_7))));
    if ((1U & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)))) {
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_pc 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data;
        }
    }
    if (vlSelfRef.reset) {
        __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc = 0x80000000U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_inst_is_load = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_is_csr = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_fcn = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_msip = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_mtip = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_ebreakm = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_step = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_msip = 0U;
    } else {
        if ((((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
             | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))) {
            if ((1U & (~ ((((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_7) 
                              | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_fencei_REG)) 
                             & (0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))) 
                            & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall))) 
                           & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
                          & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)))))) {
                __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc 
                    = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_pc_plus4
                        : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                            ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
                               + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc)
                            : ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out
                                : ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80)
                                    ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc
                                    : (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret) 
                                        & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x1eU))
                                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dpc
                                        : 0x80000004U)))));
            }
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_inst_is_load 
                = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_mem_val) 
                   & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_4)));
        }
        if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
             & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_is_csr 
                = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                   && ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6)) 
                       & (4U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6))));
        } else if (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_is_csr = 0U;
        }
        if ((1U & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)))) {
            if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_fcn 
                    = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_fcn;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ 
                    = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_typ;
            }
        }
        if ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
             | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type = 0U;
        } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type 
                = ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                    ? 0U : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type));
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd = 0U;
        } else if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_val;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd;
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen) {
            if ((0x304U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_msip 
                    = (1U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mie_T_9 
                             >> 3U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_mtip 
                    = (1U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mie_T_9 
                             >> 7U));
            }
            if ((0x7b0U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_ebreakm 
                    = (1U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w 
                             >> 0xfU));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_step 
                    = (1U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w 
                             >> 2U));
            }
            if ((0x344U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_msip 
                    = (1U & ((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
                              & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                                   ? (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T)
                                   : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)) 
                             >> 3U));
            }
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)))) {
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out 
                = ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_wb_sel))
                    ? ((IData)(4U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc)
                    : ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out
                        : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_wb_sel;
            __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr;
        }
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc 
        = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_145);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_fencei_REG 
        = ((0x2003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           && ((3U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
               && ((0x4003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                   && ((0x1003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       && (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT___csignals_T_782)))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0 
        = (0x3ffffffffffffffULL & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                                   + (QData)((IData)(
                                                     (1U 
                                                      & (((IData)(1U) 
                                                          + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)) 
                                                         >> 6U))))));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value 
        = ((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
            << 6U) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value_1 
        = ((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
            << 6U) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_fcn 
        = (1U & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___GEN_91));
    vlSelfRef.SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3 
        = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val) 
           & ((~ (IData)(vlSelfRef.io_host_valid)) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_fcn)));
    vlSelfRef.SodorFullChip__DOT__memory__DOT__storeBytes 
        = ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
            ? 2U : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
                     ? 1U : 4U));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1 
        = (0x7fU & ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1) 
                    + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_valid)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_1 
        = (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_mtip) 
            << 7U) | ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_msip) 
                      << 3U));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_2 
        = (0x40000003U | (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_ebreakm) 
                           << 0xfU) | ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_step) 
                                       << 2U)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__read_mstatus 
        = (0x300000000ULL | (QData)((IData)((0x1800U 
                                             | (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie) 
                                                 << 7U) 
                                                | ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mie) 
                                                   << 3U))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70 
        = ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
           | (3U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T 
        = (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_mtip) 
            << 7U) | ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_msip) 
                      << 3U));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1 
        = (0x3ffffffffffffffULL & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                                   + (QData)((IData)(
                                                     (1U 
                                                      & ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1) 
                                                         >> 6U))))));
    if ((1U & (~ (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
                   & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
                  | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))))) {
        if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
             & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
                = ((((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr) 
                       == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                    >> 0x14U))) & (0U 
                                                   != 
                                                   (0x1fU 
                                                    & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                       >> 0x14U)))) 
                     & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen)) 
                    & (0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel)))
                    ? ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out
                        : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37)
                    : ((((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr) 
                           == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                        >> 0x14U))) 
                          & (0U != (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                             >> 0x14U)))) 
                         & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen)) 
                        & (0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel)))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_wbdata
                        : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___dec_op2_data_T_18));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data 
                = (((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr) 
                      == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                   >> 0x14U))) & (0U 
                                                  != 
                                                  (0x1fU 
                                                   & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                      >> 0x14U)))) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen))
                    ? ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out
                        : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37)
                    : (((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr) 
                          == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                       >> 0x14U))) 
                         & (0U != (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                            >> 0x14U)))) 
                        & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen))
                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_wbdata
                        : ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_3_9)
                            ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata
                            : vlSelfRef.SodorFullChip__DOT__regfile_io_rs2_data)));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_wb_sel 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
                = ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel))
                    ? (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                >> 0xfU)) : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel))
                                              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_pc
                                              : ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr) 
                                                   == 
                                                   (0x1fU 
                                                    & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                       >> 0xfU))) 
                                                  & ((0U 
                                                      != 
                                                      (0x1fU 
                                                       & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                          >> 0xfU))) 
                                                     & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen)))
                                                  ? 
                                                 ((0U 
                                                   == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                                   ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out
                                                   : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37)
                                                  : 
                                                 ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr) 
                                                    == 
                                                    (0x1fU 
                                                     & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                        >> 0xfU))) 
                                                   & ((0U 
                                                       != 
                                                       (0x1fU 
                                                        & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                           >> 0xfU))) 
                                                      & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen)))
                                                   ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_wbdata
                                                   : 
                                                  ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr) 
                                                     == 
                                                     (0x1fU 
                                                      & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                         >> 0xfU))) 
                                                    & ((0U 
                                                        != 
                                                        (0x1fU 
                                                         & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                            >> 0xfU))) 
                                                       & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_ctrl_rf_wen)))
                                                    ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata
                                                    : 
                                                   ((0U 
                                                     == 
                                                     (0x1fU 
                                                      & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                         >> 0xfU)))
                                                     ? 0U
                                                     : 
                                                    vlSelfRef.SodorFullChip__DOT__regfile__DOT__regfile
                                                    [
                                                    (0x1fU 
                                                     & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                        >> 0xfU))]))))));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun;
        }
    }
    if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen) {
        if ((0x302U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_medeleg 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_37;
        }
        if ((0x343U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mtval 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_36;
        }
        if ((0x340U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mscratch 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mscratch_T_8;
        }
        if ((0x7b2U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dscratch 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dscratch_T_8;
        }
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause 
            = ((0x342U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mcause_T_11
                : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_12);
        if ((0x7b1U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dpc 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dpc_T_8;
        }
    } else {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_12;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
        = ((3U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd))
            ? (~ vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)
            : 0xffffffffU);
    if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst = 0x4033U;
    } else if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst;
    }
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr_io_rw_rdata 
        = (((IData)(((0xb00U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                 >> 0x14U)) ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value
                      : 0ULL)) | (IData)(((0xb02U == 
                                           (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                           ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value_1
                                           : 0ULL))) 
           | (((IData)((QData)((IData)(((0xf13U == 
                                         (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                          >> 0x14U))
                                         ? 0x8000U : 0U)))) 
               | (IData)((QData)((IData)(((0x301U == 
                                           (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                           ? 0x100U
                                           : 0U))))) 
              | ((IData)(((0x300U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                      >> 0x14U)) ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__read_mstatus
                           : 0ULL)) | ((IData)((QData)((IData)(
                                                               ((0x305U 
                                                                 == 
                                                                 (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                  >> 0x14U))
                                                                 ? 0x100U
                                                                 : 0U)))) 
                                       | ((IData)((QData)((IData)(
                                                                  ((0x344U 
                                                                    == 
                                                                    (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                     >> 0x14U))
                                                                    ? (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T)
                                                                    : 0U)))) 
                                          | ((IData)((QData)((IData)(
                                                                     ((0x304U 
                                                                       == 
                                                                       (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                        >> 0x14U))
                                                                       ? (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_1)
                                                                       : 0U)))) 
                                             | (((0x340U 
                                                  == 
                                                  (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                   >> 0x14U))
                                                  ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mscratch
                                                  : 0U) 
                                                | (((0x341U 
                                                     == 
                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                      >> 0x14U))
                                                     ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc
                                                     : 0U) 
                                                   | (((0x343U 
                                                        == 
                                                        (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                         >> 0x14U))
                                                        ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mtval
                                                        : 0U) 
                                                      | (((0x342U 
                                                           == 
                                                           (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                            >> 0x14U))
                                                           ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause
                                                           : 0U) 
                                                         | (((0x7b0U 
                                                              == 
                                                              (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                               >> 0x14U))
                                                              ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_2
                                                              : 0U) 
                                                            | (((0x7b1U 
                                                                 == 
                                                                 (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                  >> 0x14U))
                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dpc
                                                                 : 0U) 
                                                               | (((0x7b2U 
                                                                    == 
                                                                    (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                     >> 0x14U))
                                                                    ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dscratch
                                                                    : 0U) 
                                                                  | (((0x302U 
                                                                       == 
                                                                       (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                        >> 0x14U))
                                                                       ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_medeleg
                                                                       : 0U) 
                                                                     | ((IData)(
                                                                                ((0xb03U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2
                                                                                 : 0ULL)) 
                                                                        | ((IData)(
                                                                                ((0xb83U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2
                                                                                 : 0ULL)) 
                                                                           | ((IData)(
                                                                                ((0xb04U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3
                                                                                 : 0ULL)) 
                                                                              | ((IData)(
                                                                                ((0xb84U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb05U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb85U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb06U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb86U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb07U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb87U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb08U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb88U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb09U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb89U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0aU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8aU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0bU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8bU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0cU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8cU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0dU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8dU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0eU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8eU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb0fU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb8fU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb10U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb90U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb11U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb91U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb12U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb92U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb13U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb93U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb14U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb94U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb15U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb95U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb16U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb96U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb17U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb97U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb18U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb98U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb19U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb99U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1aU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9aU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1bU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9bU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1cU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9cU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1dU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9dU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1eU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9eU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb1fU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb9fU 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb20U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xba0U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb21U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xba1U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32
                                                                                 : 0ULL)) 
                                                                                | ((IData)(
                                                                                ((0xb22U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33
                                                                                 : 0ULL)) 
                                                                                | (IData)(
                                                                                ((0xba2U 
                                                                                == 
                                                                                (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33
                                                                                 : 0ULL)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret 
        = (0x3fU & ((4U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
                    & (((IData)(1U) << (7U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                              >> 0x14U))) 
                       >> 2U)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call 
        = ((4U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
           & ((IData)(1U) << (7U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                    >> 0x14U))));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break 
        = (0x7fU & ((4U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
                    & (((IData)(1U) << (7U & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                              >> 0x14U))) 
                       >> 1U)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen 
        = ((~ (IData)((3U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                              >> 0x1eU)))) & ((4U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
                                              & ((0U 
                                                  != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)) 
                                                 & (5U 
                                                    != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd)))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mcause_T_11 
        = (0x8000001fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
                          & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                               ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause
                               : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_36 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mtval
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mscratch_T_8 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mscratch
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_37 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_medeleg
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dpc_T_8 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dpc
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dscratch_T_8 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dscratch
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_2
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mstatus_T_8 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__read_mstatus
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mie_T_9 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
           & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                ? (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T_1)
                : 0U) | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_1 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_2 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_3 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_4 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_5 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_6 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_7 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_8 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_9 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_10 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_11 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_12 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_13 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_14 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_15 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_16 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_17 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_18 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_19 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_20 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_21 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_22 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_23 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_24 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_25 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_26 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_27 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_28 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_29 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_30 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_31 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_32 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
        = ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
              ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__value_1
              : 0ULL) | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))) 
           & (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr 
        = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr;
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata 
        = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata;
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr 
        = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr;
    if (__VdlySet__SodorFullChip__DOT__regfile__DOT__regfile__v0) {
        vlSelfRef.SodorFullChip__DOT__regfile__DOT__regfile[__VdlyDim0__SodorFullChip__DOT__regfile__DOT__regfile__v0] 
            = __VdlyVal__SodorFullChip__DOT__regfile__DOT__regfile__v0;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___mem_wbdata_T_4 
        = ((3U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
            ? SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr_io_rw_rdata
            : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80 
        = ((~ (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
               >> 0x1eU)) & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
           + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1);
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_eq 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
           == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data);
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_lt 
        = VL_LTS_III(32, vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1, vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data);
    SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_ltu 
        = (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
           < vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_ctrl_rf_wen 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) 
                                                   & ((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG)) 
                                                      & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen))));
    if ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
          & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
         | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr = 0U;
    } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr 
            = ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                ? 0U : (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                 >> 7U)));
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_7 
        = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80)
            ? (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie)
            : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mie));
    if (vlSelfRef.reset) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_val = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_typ = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_valid = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd = 0U;
        __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen 
            = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_valid = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst = 0x4033U;
    } else {
        if ((1U & (~ (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
                       & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
                      | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))))) {
            if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
                if ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))) {
                    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_typ 
                        = ((0x2003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                            ? 3U : ((3U == (0x707fU 
                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                     ? 1U : ((0x4003U 
                                              == (0x707fU 
                                                  & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                              ? 5U : 
                                             ((0x1003U 
                                               == (0x707fU 
                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                               ? 2U
                                               : ((0x5003U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                                   ? 6U
                                                   : 
                                                  ((0x2023U 
                                                    == 
                                                    (0x707fU 
                                                     & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                                    ? 3U
                                                    : 
                                                   ((0x23U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                                     ? 1U
                                                     : 
                                                    ((0x1023U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))
                                                      ? 2U
                                                      : 0U))))))));
                }
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc 
                    = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_pc;
            }
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_valid = 0U;
        } else if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_valid 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_valid;
        }
        if ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
             | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_val = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_valid = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst = 0x4033U;
        } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_val 
                = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                   && (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_mem_val));
            if ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd = 0U;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst = 0x4033U;
            } else {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd 
                    = ((IData)(((0U == (0xf8000U & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                & ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6)) 
                                   | (3U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6)))))
                        ? 5U : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst 
                    = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst;
            }
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_valid 
                = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                   && (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_valid));
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill) {
            __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen = 0U;
        } else if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) {
            __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen;
        }
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen 
            = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37 
        = ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
            ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
               - vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset)
            : ((5U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1)
                : ((6U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                    ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
                       | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1)
                    : ((7U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                        ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset 
                           ^ vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1)
                        : ((8U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                            ? VL_LTS_III(32, vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1, vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset)
                            : ((9U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
                                   < vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset)
                                : ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                    ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
                                       << (0x1fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset))
                                    : ((4U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                        ? VL_SHIFTRS_III(32,32,5, vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1, 
                                                         (0x1fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset))
                                        : ((3U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                            ? (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1 
                                               >> (0x1fU 
                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset))
                                            : ((0xaU 
                                                == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1
                                                : (
                                                   (0xbU 
                                                    == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun))
                                                    ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset
                                                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst)))))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG 
        = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_exception;
    if (vlSelfRef.reset) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_valid = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_pc = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst = 0x4033U;
    } else {
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_valid = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst = 0x4033U;
        } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_valid 
                = (1U & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_if_kill)));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_if_kill)
                    ? 0x4033U : (((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                   [(0x1fffffU & ((IData)(3U) 
                                                  + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc))] 
                                   << 0x18U) | (vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                                [(0x1fffffU 
                                                  & ((IData)(2U) 
                                                     + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc))] 
                                                << 0x10U)) 
                                 | ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                     [(0x1fffffU & 
                                       ((IData)(1U) 
                                        + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc))] 
                                     << 8U) | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                    [(0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc)])));
        }
        if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen) {
            if ((0xb00U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                    = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                               >> 0x1aU));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                               >> 6U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                    = (((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                                 >> 0x1aU)) << 0x1aU) 
                       | (IData)(((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33 
                                   >> 6U) >> 0x20U)));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] 
                    = ((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_ 
                                >> 0x1aU)) >> 6U);
            } else {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                    = (IData)(((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                    << 0x20U) | (QData)((IData)(
                                                                (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_) 
                                                                  << 6U) 
                                                                 | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))
                                : (QData)((IData)((0x7fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] 
                    = (IData)((((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_) 
                                                                   << 6U) 
                                                                  | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))
                                 : (QData)((IData)(
                                                   (0x7fU 
                                                    & ((IData)(1U) 
                                                       + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)))))) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                    = (IData)(((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                    << 0x1aU) | (QData)((IData)(
                                                                (0x3ffffffU 
                                                                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_)))))
                                : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                    = (IData)((((0xb80U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33)) 
                                     << 0x1aU) | (QData)((IData)(
                                                                 (0x3ffffffU 
                                                                  & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_)))))
                                 : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
            }
            if ((0xb02U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                               >> 6U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                    = (((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                                 >> 0x1aU)) << 0x1aU) 
                       | (IData)(((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                                   >> 6U) >> 0x20U)));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] 
                    = ((IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                                >> 0x1aU)) >> 6U);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                    = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34);
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] 
                    = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1 
                               >> 0x1aU));
            } else {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                    = (IData)(((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                    << 0x1aU) | (QData)((IData)(
                                                                (0x3ffffffU 
                                                                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1)))))
                                : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                    = (IData)((((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                     << 0x1aU) | (QData)((IData)(
                                                                 (0x3ffffffU 
                                                                  & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1)))))
                                 : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                    = (IData)(((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                           >> 0x14U))
                                ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                    << 0x20U) | (QData)((IData)(
                                                                (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1) 
                                                                  << 6U) 
                                                                 | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1)))))
                                : (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1))));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] 
                    = (IData)((((0xb82U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                                            >> 0x14U))
                                 ? (((QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34)) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1) 
                                                                   << 6U) 
                                                                  | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1)))))
                                 : (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1))) 
                               >> 0x20U));
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
            }
        } else {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[0U] 
                = (0x7fU & ((IData)(1U) + (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_)));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[1U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[0U] 
                = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0);
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[1U] 
                = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0 
                           >> 0x20U));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[0U] 
                = (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1);
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[1U] 
                = (IData)((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1 
                           >> 0x20U));
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306[2U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[0U] 
                = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[1U] = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305[2U] = 0U;
        }
        if ((1U & (~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)))) {
            if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                 & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
                vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_pc 
                    = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc;
            }
        }
        if ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0)) 
             | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen = 0U;
        } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen 
                = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                   && (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_rf_wen));
        }
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc 
        = __Vdly__SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc;
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v0) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v0] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v0;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v1) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v1] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v1;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v2) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v2] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v2;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v3) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v3] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v3;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v4) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v4] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v4;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v5) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v5] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v5;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v6) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v6] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v6;
    }
    if (__VdlySet__SodorFullChip__DOT__memory__DOT__bytes__v7) {
        vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes[__VdlyDim0__SodorFullChip__DOT__memory__DOT__bytes__v7] 
            = __VdlyVal__SodorFullChip__DOT__memory__DOT__bytes__v7;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_12 
        = ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break)
            ? 3U : ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call)
                     ? 0xbU : ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG)
                                ? 2U : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause)));
    SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75 
        = (QData)((IData)((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG) 
                            | ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call) 
                               | (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break)))
                            ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_pc
                            : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc)));
    if (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_107 
            = ((0xb03U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_1)
                : ((0xb83U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_1)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_108 
            = ((0xb04U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_2)
                : ((0xb84U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_2)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_109 
            = ((0xb05U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_3)
                : ((0xb85U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_3)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_110 
            = ((0xb06U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_4)
                : ((0xb86U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_4)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_111 
            = ((0xb07U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_5)
                : ((0xb87U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_5)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_112 
            = ((0xb08U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_6)
                : ((0xb88U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_6)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_113 
            = ((0xb09U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_7)
                : ((0xb89U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_7)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_114 
            = ((0xb0aU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_8)
                : ((0xb8aU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_8)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_115 
            = ((0xb0bU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_9)
                : ((0xb8bU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_9)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_116 
            = ((0xb0cU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_10)
                : ((0xb8cU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_10)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_117 
            = ((0xb0dU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_11)
                : ((0xb8dU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_11)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_118 
            = ((0xb0eU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_12)
                : ((0xb8eU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_12)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_119 
            = ((0xb0fU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_13)
                : ((0xb8fU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_13)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_120 
            = ((0xb10U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_14)
                : ((0xb90U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_14)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_121 
            = ((0xb11U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_15)
                : ((0xb91U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_15)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_122 
            = ((0xb12U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_16)
                : ((0xb92U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_16)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_123 
            = ((0xb13U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_17)
                : ((0xb93U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_17)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_124 
            = ((0xb14U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_18)
                : ((0xb94U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_18)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_125 
            = ((0xb15U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_19)
                : ((0xb95U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_19)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_126 
            = ((0xb16U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_20)
                : ((0xb96U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_20)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_127 
            = ((0xb17U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_21)
                : ((0xb97U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_21)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_128 
            = ((0xb18U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_22)
                : ((0xb98U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_22)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_129 
            = ((0xb19U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_23)
                : ((0xb99U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_23)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_130 
            = ((0xb1aU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_24)
                : ((0xb9aU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_24)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_131 
            = ((0xb1bU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_25)
                : ((0xb9bU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_25)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_132 
            = ((0xb1cU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_26)
                : ((0xb9cU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_26)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_133 
            = ((0xb1dU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_27)
                : ((0xb9dU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_27)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_134 
            = ((0xb1eU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_28)
                : ((0xb9eU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_28)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_135 
            = ((0xb1fU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_29)
                : ((0xb9fU == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_29)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_136 
            = ((0xb20U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_30)
                : ((0xba0U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_30)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_137 
            = ((0xb21U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_31)
                : ((0xba1U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_31)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_138 
            = ((0xb22U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? (((QData)((IData)(
                                                          (0xffU 
                                                           & (IData)(
                                                                     (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33 
                                                                      >> 0x20U))))) 
                                          << 0x28U) 
                                         | SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_32)
                : ((0xba2U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                               >> 0x14U)) ? (((QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_32)))) 
                                              << 0x20U) 
                                             | (QData)((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33)))
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33));
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_145 
            = ((0x341U == (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst 
                           >> 0x14U)) ? ((QData)((IData)(
                                                         VL_SHIFTR_III(32,32,32, 
                                                                       (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8 
                                                                        & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70)
                                                                             ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc
                                                                             : 0U) 
                                                                           | vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)), 2U))) 
                                         << 2U) : SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75);
    } else {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_107 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_108 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_109 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_110 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_111 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_112 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_113 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_114 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_115 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_116 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_117 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_118 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_119 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_120 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_121 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_122 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_123 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_124 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_125 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_126 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_127 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_128 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_129 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_130 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_131 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_132 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_133 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_134 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_135 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_136 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_137 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_138 
            = vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_145 
            = SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill 
        = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG) 
           | ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_call) 
              | ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_break) 
                 | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret))));
    if (vlSelfRef.reset) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_exception = 0U;
    } else if (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_exception 
            = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
               && (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__dec_exception));
    } else if (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall) 
                & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_exception = 0U;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel 
        = ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill)
            ? 3U : ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                     ? 0U : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                              ? ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_eq)
                                  ? 0U : 1U) : ((2U 
                                                 == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                 ? 
                                                ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_eq)
                                                  ? 1U
                                                  : 0U)
                                                 : 
                                                ((3U 
                                                  == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                  ? 
                                                 ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_lt)
                                                   ? 0U
                                                   : 1U)
                                                  : 
                                                 ((4U 
                                                   == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                   ? 
                                                  ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_ltu)
                                                    ? 0U
                                                    : 1U)
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                    ? 
                                                   ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_lt)
                                                     ? 1U
                                                     : 0U)
                                                    : 
                                                   ((6U 
                                                     == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                     ? 
                                                    ((IData)(SodorFullChip__DOT__tile__DOT__core__DOT__d_io_dat_exe_br_ltu)
                                                      ? 1U
                                                      : 0U)
                                                     : 
                                                    ((7U 
                                                      == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                      ? 1U
                                                      : 
                                                     ((8U 
                                                       == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type))
                                                       ? 2U
                                                       : 0U))))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_pc_plus4 
        = ((IData)(4U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc);
    vlSelfRef.io_host_rdata = (((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                 [(0x1fffffU & ((IData)(3U) 
                                                + vlSelfRef.io_host_addr))] 
                                 << 0x18U) | (vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                              [(0x1fffffU 
                                                & ((IData)(2U) 
                                                   + vlSelfRef.io_host_addr))] 
                                              << 0x10U)) 
                               | ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                   [(0x1fffffU & ((IData)(1U) 
                                                  + vlSelfRef.io_host_addr))] 
                                   << 8U) | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                  [(0x1fffffU & vlSelfRef.io_host_addr)]));
    vlSelfRef.io_tohost = (((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                             [0x1003U] << 0x18U) | 
                            (vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                             [0x1002U] << 0x10U)) | 
                           ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                             [0x1001U] << 8U) | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                            [0x1000U]));
    SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2 
        = ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
            [(0x1fffffU & ((IData)(1U) + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))] 
            << 8U) | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
           [(0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)]);
    if ((0x2003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((3U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x4003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x1003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x5003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x2023U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 2U;
    } else if ((0x23U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 2U;
    } else if ((0x1023U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 2U;
    } else if ((0x17U == (0x7fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 4U;
    } else if ((0x37U == (0x7fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xbU;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 4U;
    } else if ((0x13U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x7013U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 5U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x6013U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 6U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x4013U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 7U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x2013U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 8U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x3013U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 9U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x1013U == (0xfc00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 2U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x40005013U == (0xfc00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 4U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x5013U == (0xfc00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 3U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x1033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 2U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x33U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x40000033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x2033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 8U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x3033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 9U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x7033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 5U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x6033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 6U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x4033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 7U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x40005033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 4U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x5033U == (0xfe00707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 3U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    } else if ((0x6fU == (0x7fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 7U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 2U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 5U;
    } else if ((0x67U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 8U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 2U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 1U;
    } else if ((0x63U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 2U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else if ((0x1063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 1U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else if ((0x5063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 3U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else if ((0x7063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 4U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else if ((0x4063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 5U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else if ((0x6063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 6U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 0U;
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 3U;
    } else {
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type = 0U;
        if ((0x5073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 2U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 1U;
        } else if ((0x6073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 2U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 2U;
        } else if ((0x1073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 1U;
        } else if ((0x2073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 2U;
        } else if ((0x3073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 3U;
        } else if ((0x7073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))) {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 2U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0xaU;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 3U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 = 3U;
        } else {
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel = 0U;
            vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6 
                = ((0x73U == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)
                    ? 4U : ((0x30200073U == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)
                             ? 4U : ((0x7b200073U == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)
                                      ? 4U : ((0x100073U 
                                               == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)
                                               ? 4U
                                               : 0U))));
        }
        vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel = 0U;
    }
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_mem_val 
        = ((0x2003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           | ((3U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              | ((0x4003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 | ((0x1003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    | ((0x5003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       | ((0x2023U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          | ((0x23U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                             | ((0x1023U == (0x707fU 
                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                | ((0x17U != (0x7fU 
                                              & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                   & ((0x37U != (0x7fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                      & ((0x13U != 
                                          (0x707fU 
                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                         & ((0x7013U 
                                             != (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                            & ((0x6013U 
                                                != 
                                                (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                               & ((0x4013U 
                                                   != 
                                                   (0x707fU 
                                                    & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                  & ((0x2013U 
                                                      != 
                                                      (0x707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                     & ((0x3013U 
                                                         != 
                                                         (0x707fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                        & ((0x1013U 
                                                            != 
                                                            (0xfc00707fU 
                                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                           & ((0x40005013U 
                                                               != 
                                                               (0xfc00707fU 
                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                              & ((0x5013U 
                                                                  != 
                                                                  (0xfc00707fU 
                                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                 & ((0x1033U 
                                                                     != 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                    & ((0x33U 
                                                                        != 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                       & ((0x40000033U 
                                                                           != 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                          & ((0x2033U 
                                                                              != 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                             & ((0x3033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x4033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x40005033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6fU 
                                                                                != 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x67U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x63U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x4063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x2073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x3073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x73U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x30200073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x7b200073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x100073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x10500073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x100fU 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & (0xfU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)))))))))))))))))))))))))))))))))))))))))))))))))));
    vlSelfRef.SodorFullChip__DOT__regfile_io_rs2_data 
        = ((0U == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                            >> 0x14U))) ? 0U : vlSelfRef.SodorFullChip__DOT__regfile__DOT__regfile
           [(0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                      >> 0x14U))]);
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT___csignals_T_782 
        = ((0x5003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           & ((0x2023U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              & ((0x23U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 & ((0x1023U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    & ((0x17U != (0x7fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       & ((0x37U != (0x7fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          & ((0x13U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                             & ((0x7013U != (0x707fU 
                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                & ((0x6013U != (0x707fU 
                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                   & ((0x4013U != (0x707fU 
                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                      & ((0x2013U != 
                                          (0x707fU 
                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                         & ((0x3013U 
                                             != (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                            & ((0x1013U 
                                                != 
                                                (0xfc00707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                               & ((0x40005013U 
                                                   != 
                                                   (0xfc00707fU 
                                                    & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                  & ((0x5013U 
                                                      != 
                                                      (0xfc00707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                     & ((0x1033U 
                                                         != 
                                                         (0xfe00707fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                        & ((0x33U 
                                                            != 
                                                            (0xfe00707fU 
                                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                           & ((0x40000033U 
                                                               != 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                              & ((0x2033U 
                                                                  != 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                 & ((0x3033U 
                                                                     != 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                    & ((0x7033U 
                                                                        != 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                       & ((0x6033U 
                                                                           != 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                          & ((0x4033U 
                                                                              != 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                             & ((0x40005033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5033U 
                                                                                != 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6fU 
                                                                                != 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x67U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x63U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x4063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x2073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x3073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7073U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x73U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x30200073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x7b200073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x100073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & ((0x10500073U 
                                                                                != vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                & (0x100fU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst))))))))))))))))))))))))))))))))))))))))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_4 
        = ((0x2003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           & ((3U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              & ((0x4003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 & ((0x1003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    & ((0x5003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       & ((0x2023U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          | ((0x23U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                             | (0x1023U == (0x707fU 
                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_3_9 
        = (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr) 
            == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                         >> 0x14U))) & ((0U != (0x1fU 
                                                & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                   >> 0x14U))) 
                                        & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_ctrl_rf_wen)));
    SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_50 
        = ((0x5073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           | ((0x6073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              | ((0x1073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 | ((0x2073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    | ((0x3073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       | (0x7073U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__dec_exception 
        = (1U & (~ ((0x2003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    | ((3U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       | ((0x4003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          | ((0x1003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                             | ((0x5003U == (0x707fU 
                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                | ((0x2023U == (0x707fU 
                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                   | ((0x23U == (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                      | ((0x1023U == 
                                          (0x707fU 
                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                         | ((0x17U 
                                             == (0x7fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                            | ((0x37U 
                                                == 
                                                (0x7fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                               | ((0x13U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                  | ((0x7013U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                     | ((0x6013U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                        | ((0x4013U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                           | ((0x2013U 
                                                               == 
                                                               (0x707fU 
                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                              | ((0x3013U 
                                                                  == 
                                                                  (0x707fU 
                                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                 | ((0x1013U 
                                                                     == 
                                                                     (0xfc00707fU 
                                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                    | ((0x40005013U 
                                                                        == 
                                                                        (0xfc00707fU 
                                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                       | ((0x5013U 
                                                                           == 
                                                                           (0xfc00707fU 
                                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                          | ((0x1033U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                             | ((0x33U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x2033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x3033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6fU 
                                                                                == 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x67U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x63U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x1063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x1073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x2073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x3073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x73U 
                                                                                == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                | ((0x30200073U 
                                                                                == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                | ((0x7b200073U 
                                                                                == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                | ((0x100073U 
                                                                                == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                | ((0x10500073U 
                                                                                == vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                                                | ((0x100fU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | (0xfU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)))))))))))))))))))))))))))))))))))))))))))))))))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0 = 1U;
    vlSelfRef.io_success = (1U == vlSelfRef.io_tohost);
    vlSelfRef.SodorFullChip__DOT__memory_io_core_0_resp_bits_data 
        = ((6U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
            ? (IData)(SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2)
            : ((5U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
                ? vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
               [(0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)]
                : ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
                    ? ((((0x80U & vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                          [(0x1fffffU & ((IData)(1U) 
                                         + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))])
                          ? 0xffffU : 0U) << 0x10U) 
                       | (IData)(SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2))
                    : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ))
                        ? ((((0x80U & vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                              [(0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)])
                              ? 0xffffffU : 0U) << 8U) 
                           | vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                           [(0x1fffffU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out)])
                        : ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                            [(0x1fffffU & ((IData)(3U) 
                                           + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))] 
                            << 0x18U) | ((vlSelfRef.SodorFullChip__DOT__memory__DOT__bytes
                                          [(0x1fffffU 
                                            & ((IData)(2U) 
                                               + vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out))] 
                                          << 0x10U) 
                                         | (IData)(SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_2)))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_7 
        = ((0x2003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           & ((3U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              & ((0x4003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 & ((0x1003U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT___csignals_T_782)))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___dec_op2_data_T_18 
        = (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_3_9) 
            & (0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel)))
            ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata
            : ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                ? vlSelfRef.SodorFullChip__DOT__regfile_io_rs2_data
                : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                    ? ((((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                          >> 0x1fU) ? 0xfffffU : 0U) 
                        << 0xcU) | (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                    >> 0x14U)) : ((2U 
                                                   == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                                                   ? 
                                                  ((((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                      >> 0x1fU)
                                                      ? 0xfffffU
                                                      : 0U) 
                                                    << 0xcU) 
                                                   | ((0xfe0U 
                                                       & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                          >> 0x14U)) 
                                                      | (0x1fU 
                                                         & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                            >> 7U))))
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                                                    ? 
                                                   ((((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                       >> 0x1fU)
                                                       ? 0x7ffffU
                                                       : 0U) 
                                                     << 0xdU) 
                                                    | (((0x1000U 
                                                         & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                            >> 0x13U)) 
                                                        | (0x800U 
                                                           & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                              << 4U))) 
                                                       | ((0x7e0U 
                                                           & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                              >> 0x14U)) 
                                                          | (0x1eU 
                                                             & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                                >> 7U)))))
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                                                     ? 
                                                    (0xfffff000U 
                                                     & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel))
                                                      ? 
                                                     (((((vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                          >> 0x1fU)
                                                          ? 0x7ffU
                                                          : 0U) 
                                                        << 0x15U) 
                                                       | (0x100000U 
                                                          & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                             >> 0xbU))) 
                                                      | (((0xff000U 
                                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst) 
                                                          | (0x800U 
                                                             & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                                >> 9U))) 
                                                         | (0x7feU 
                                                            & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                                               >> 0x14U))))
                                                      : 0U)))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_rf_wen 
        = ((0x2003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           | ((3U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              | ((0x4003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 | ((0x1003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    | ((0x5003U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       | ((0x2023U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          & ((0x23U != (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                             & ((0x1023U != (0x707fU 
                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                & ((0x17U == (0x7fU 
                                              & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                   | ((0x37U == (0x7fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                      | ((0x13U == 
                                          (0x707fU 
                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                         | ((0x7013U 
                                             == (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                            | ((0x6013U 
                                                == 
                                                (0x707fU 
                                                 & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                               | ((0x4013U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                  | ((0x2013U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                     | ((0x3013U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                        | ((0x1013U 
                                                            == 
                                                            (0xfc00707fU 
                                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                           | ((0x40005013U 
                                                               == 
                                                               (0xfc00707fU 
                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                              | ((0x5013U 
                                                                  == 
                                                                  (0xfc00707fU 
                                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                 | ((0x1033U 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                    | ((0x33U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                       | ((0x40000033U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                          | ((0x2033U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                             | ((0x3033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6fU 
                                                                                == 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x67U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x63U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x4063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6063U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_50))))))))))))))))))))))))))))))))))))));
    SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_51 
        = ((0x63U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
           | ((0x1063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
              | ((0x5063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                 | ((0x7063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                    | ((0x4063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                       | ((0x6063U == (0x707fU & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                          | (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_50)))))));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_wbdata 
        = ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
            ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out
            : ((2U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
                ? vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out
                : ((1U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel))
                    ? vlSelfRef.SodorFullChip__DOT__memory_io_core_0_resp_bits_data
                    : vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___mem_wbdata_T_4)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_if_kill 
        = ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
           | ((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_7) 
              | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_fencei_REG)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall 
        = (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_inst_is_load) 
            & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr) 
                == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                             >> 0xfU))) & ((0U != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr)) 
                                           & ((0U == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                                              & ((0x2003U 
                                                  == 
                                                  (0x707fU 
                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                 | ((3U 
                                                     == 
                                                     (0x707fU 
                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                    | ((0x4003U 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                       | ((0x1003U 
                                                           == 
                                                           (0x707fU 
                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                          | ((0x5003U 
                                                              == 
                                                              (0x707fU 
                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                             | ((0x2023U 
                                                                 == 
                                                                 (0x707fU 
                                                                  & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                | ((0x23U 
                                                                    == 
                                                                    (0x707fU 
                                                                     & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                   | ((0x1023U 
                                                                       == 
                                                                       (0x707fU 
                                                                        & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                      | ((0x17U 
                                                                          != 
                                                                          (0x7fU 
                                                                           & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                         & ((0x37U 
                                                                             != 
                                                                             (0x7fU 
                                                                              & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                            & ((0x13U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                               | ((0x7013U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6013U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4013U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x2013U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x3013U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x1013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40005013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x1033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x33U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x2033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x3033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6fU 
                                                                                != 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x67U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_51)))))))))))))))))))))))))))))))))))) 
           | (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_inst_is_load) 
               & (((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr) 
                   == (0x1fU & (vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst 
                                >> 0x14U))) & ((0U 
                                                != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr)) 
                                               & ((0U 
                                                   == (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel)) 
                                                  & ((0x2003U 
                                                      != 
                                                      (0x707fU 
                                                       & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                     & ((3U 
                                                         != 
                                                         (0x707fU 
                                                          & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                        & ((0x4003U 
                                                            != 
                                                            (0x707fU 
                                                             & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                           & ((0x1003U 
                                                               != 
                                                               (0x707fU 
                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                              & ((0x5003U 
                                                                  != 
                                                                  (0x707fU 
                                                                   & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                 & ((0x2023U 
                                                                     == 
                                                                     (0x707fU 
                                                                      & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                    | ((0x23U 
                                                                        == 
                                                                        (0x707fU 
                                                                         & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                       | ((0x1023U 
                                                                           == 
                                                                           (0x707fU 
                                                                            & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                          | ((0x17U 
                                                                              != 
                                                                              (0x7fU 
                                                                               & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                             & ((0x37U 
                                                                                != 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x13U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x7013U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x6013U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x4013U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x2013U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x3013U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1013U 
                                                                                != 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x40005013U 
                                                                                != 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x5013U 
                                                                                != 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x1033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x33U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x2033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x3033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x7033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                | ((0x6fU 
                                                                                != 
                                                                                (0x7fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & ((0x67U 
                                                                                != 
                                                                                (0x707fU 
                                                                                & vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst)) 
                                                                                & (IData)(SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT____VdfgRegularize_hcf0192af_1_51)))))))))))))))))))))))))))))))))))) 
              | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_is_csr)));
    vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___GEN_91 
        = ((IData)(vlSelfRef.reset) ? 0U : ((((IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0) 
                                              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                                             | (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill))
                                             ? 0U : 
                                            (((~ (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall)) 
                                              & (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0))
                                              ? ((0U 
                                                  != (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel))
                                                  ? 0U
                                                  : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_4))
                                              : (IData)(vlSelfRef.SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_fcn))));
}

void VSodorFullChip___024root___eval_triggers__act(VSodorFullChip___024root* vlSelf);

bool VSodorFullChip___024root___eval_phase__act(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_phase__act\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VSodorFullChip___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VSodorFullChip___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VSodorFullChip___024root___eval_phase__nba(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_phase__nba\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VSodorFullChip___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__ico(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__nba(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VSodorFullChip___024root___dump_triggers__act(VSodorFullChip___024root* vlSelf);
#endif  // VL_DEBUG

void VSodorFullChip___024root___eval(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            VSodorFullChip___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/sodor/verilog/SodorFullChip.v", 3110, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VSodorFullChip___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VSodorFullChip___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/sodor/verilog/SodorFullChip.v", 3110, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VSodorFullChip___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/sodor/verilog/SodorFullChip.v", 3110, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VSodorFullChip___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VSodorFullChip___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VSodorFullChip___024root___eval_debug_assertions(VSodorFullChip___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSodorFullChip___024root___eval_debug_assertions\n"); );
    VSodorFullChip__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY(((vlSelfRef.io_host_valid & 0xfeU)))) {
        Verilated::overWidthError("io_host_valid");}
    if (VL_UNLIKELY(((vlSelfRef.io_host_write & 0xfeU)))) {
        Verilated::overWidthError("io_host_write");}
}
#endif  // VL_DEBUG
