// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__76(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__76\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913 = 0;
    VlWide<3>/*95:0*/ __Vtemp_7;
    VlWide<3>/*95:0*/ __Vtemp_12;
    VlWide<3>/*95:0*/ __Vtemp_13;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_14_cfi_idx_valid 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_14_cfi_idx_valid;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_idx_valid 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_idx_valid;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_type 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_type;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_start_bank 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_start_bank;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_14_br_mask 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_14_br_mask;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_br_mask 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_br_mask;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_ras_top 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_ras_top;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_ras_idx 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_ras_idx;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_mispredicted 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_16_cfi_mispredicted;
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_not_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_not_taken[0U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_not_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_taken[0U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_new_saw_branch_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0[0U][0U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0__v0[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0[0U][1U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0__v0[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0[0U][2U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0__v0[2U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0[0U][3U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_bpd_meta_0__v0[3U];
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_current_saw_branch_not_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_current_saw_branch_not_taken[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_current_saw_branch_not_taken__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_current_saw_branch_not_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_not_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_not_taken[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_not_taken__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_not_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_taken[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_taken__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_new_saw_branch_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_ras_idx__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_ras_idx[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_ras_idx__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_ras_idx__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0][0U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0][1U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0][2U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0[2U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0][3U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0__v0[3U];
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_current_saw_branch_not_taken__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_current_saw_branch_not_taken[0U] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_current_saw_branch_not_taken__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT___T_24 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_29) 
           | (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__REG_1_br_mask) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_175 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F10_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_179 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F11_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_183 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F12_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_187 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F13_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_199 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F16_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_203 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F17_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_207 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F18_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT___T_211 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_uop___05F19_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT____VdfgRegularize_heb752a5c_0_8 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__valids_0) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_39)) 
              & (0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__uops_0_br_mask)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT____VdfgRegularize_heb752a5c_0_7 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__valids_1) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_39)) 
              & (0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__uops_1_br_mask)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT____VdfgRegularize_heb752a5c_0_6 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__valids_2) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_39)) 
              & (0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__uops_2_br_mask)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT____VdfgRegularize_heb752a5c_0_5 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__valids_3) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_39)) 
              & (0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__uops_3_br_mask)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_29 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_1_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_1_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_28 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_2_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_2_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_27 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_3_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_3_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_26 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_4_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_4_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_23 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_7_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_7_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_7));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_22 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_8_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_8_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_8));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_21 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_9_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_9_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_9));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_20 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_10_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_10_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_10));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_19 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_11_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_11_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_11));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT____VdfgRegularize_he36db265_0_18 
        = ((~ ((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_12_br_mask))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__uops_12_uses_ldq)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__rpq__DOT__valids_12));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3646 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3658 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3730 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3742 
        = (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_br_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__ifpu_io_resp_valid 
        = ((0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__ifpu__DOT__REG_1_1_br_mask) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__ifpu__DOT__REG___05F1));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_fire_load_incoming_0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ma_ld_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__mem_units_0__DOT__MemAddrCalcUnit_io_resp_bits_mxcpt_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1220 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_0_ldq_idx;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ma_ld_0 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1220 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_io_deq_valid) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_io_empty) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fpu__DOT__REG_1_3_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fpu__DOT__REG_1_3_rob_idx;
        } else if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_6_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_6_rob_idx;
        } else if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_5_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_5_rob_idx;
        } else if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_4_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_4_rob_idx;
        } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_3_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_3_rob_idx;
        } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_2_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_2_rob_idx;
        } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__value_1))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_1_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_1_rob_idx;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_0_stq_idx;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue__DOT__uops_0_rob_idx;
        }
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1_io_empty) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregister_read__DOT__exe_reg_uops_0_stq_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fregister_read__DOT__exe_reg_uops_0_rob_idx;
    } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__value_1))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_2_stq_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_2_rob_idx;
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__value_1))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_1_stq_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_1_rob_idx;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_0_stq_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_rob_idx 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__BranchKillableQueue_1__DOT__uops_0_rob_idx;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1085 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sta_incoming_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_stad_incoming_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1014 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_fire_load_incoming_0) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_stad_incoming_0) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sta_incoming_0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT___GEN_51 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__lsu_release_arb_io_in_0_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb_io_lsu_release_valid))
            ? 3U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT__state));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___GEN_24 
        = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
            ? ((1U & ((~ ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT__state)) 
                          & ((0x3fU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__req_address 
                                       >> 6U)) == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT__req_idx)))) 
                      & ((~ ((~ ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__meta_hazard)) 
                                 & (((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__state)) 
                                     | (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__state))) 
                                    | (((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__state)) 
                                        | (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__state))) 
                                       | ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__state)) 
                                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_1__DOT__grantack_valid)))))) 
                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__idx_matches_0_1) 
                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs_io_req_is_probe_0)))) 
                         & (~ ((~ ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__meta_hazard)) 
                                   & (((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__state)) 
                                       | (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__state))) 
                                      | (((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__state)) 
                                          | (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__state))) 
                                         | ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__state)) 
                                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__mshrs_0__DOT__grantack_valid)))))) 
                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__idx_matches_0_0) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs_io_req_is_probe_0)))))))
                ? 4U : 1U) : ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                               ? (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__way_en)) 
                                   & ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                      | ((2U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                         & ((1U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                            & ((0U 
                                                != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                               & ((7U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                                  | ((6U 
                                                      != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                                     & ((5U 
                                                         != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                                        & ((4U 
                                                            != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)) 
                                                           & (0xbU 
                                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT___T)))))))))))
                                   ? 7U : 5U) : ((5U 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                  ? 
                                                 ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb_io_lsu_release_valid)) 
                                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__lsu_release_arb_io_in_0_ready)) 
                                                   & (5U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state)))
                                                   ? 6U
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                  : 
                                                 ((6U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                   ? 
                                                  (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__tlMasterXbar_auto_in_0_c_ready) 
                                                    & ((0U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__beatsLeft))
                                                        ? 
                                                       (~ 
                                                        (1U 
                                                         & (VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT___readys_T), 1U) 
                                                            >> 1U)))
                                                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__state_1)))
                                                    ? 
                                                   ((0U 
                                                     != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__way_en))
                                                     ? 9U
                                                     : 0U)
                                                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                   : 
                                                  ((7U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                    ? 
                                                   (((0U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT__state)) 
                                                     & (7U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state)))
                                                     ? 8U
                                                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                    : 
                                                   ((8U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                     ? 
                                                    ((0U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__wb__DOT__state))
                                                      ? 9U
                                                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                     : 
                                                    ((9U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                      ? 
                                                     ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__meta_write_arb_io_out_valid)) 
                                                        & (0x40U 
                                                           <= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__meta_0__DOT__rst_cnt))) 
                                                       & (9U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state)))
                                                       ? 0xaU
                                                       : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                      : 
                                                     ((0xaU 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state))
                                                       ? 0U
                                                       : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__prober__DOT__state)))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1263 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_std_incoming_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_stad_incoming_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_sfence_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__mem_units_0__DOT__MemAddrCalcUnit_io_resp_bits_sfence_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_sfence_bits_rs1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_0_mem_size));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_sfence_bits_rs2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_0_mem_size) 
              >> 1U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_kill 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_passthrough) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_mem_s1_kill));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_valid_0) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_passthrough))
            ? 1U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__io_status_dprv_REG));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__vm_enabled_0 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_satp_mode) 
            >> 3U) & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_passthrough)) 
                      & (1U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__io_status_dprv_REG))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1063 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_passthrough)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__hella_req_addr
            : 0ULL);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_897 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_hella_wakeup_0)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_869));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1714)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1726)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1741)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1746)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269)
                        : ((3U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_267)) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269))
                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269)))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24269))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_30202 
        = ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_uop_rob_idx)
            : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_uop_rob_idx)
                : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_uop_rob_idx)
                    : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_uop_rob_idx)
                        : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_uop_rob_idx)
                            : ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_uop_rob_idx)
                                : ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_uop_rob_idx)
                                    : ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_uop_rob_idx)
                                        : ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_uop_rob_idx)
                                            : ((6U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_uop_rob_idx)
                                                : (
                                                   (5U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_uop_rob_idx)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_uop_rob_idx)
                                                     : 
                                                    ((3U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_uop_rob_idx)
                                                      : 
                                                     ((2U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_uop_rob_idx)
                                                       : 
                                                      ((1U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_uop_rob_idx)
                                                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_uop_rob_idx))))))))))))))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_uses_ldq) {
        if ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_uop_uses_stq;
        } else if ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_uop_uses_stq;
        } else if ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_uop_uses_stq;
        } else if ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_uop_uses_stq;
        } else if ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_uop_uses_stq;
        } else if ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_uop_uses_stq;
        } else if ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_uop_uses_stq;
        } else if ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_uop_uses_stq;
        } else if ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_uop_uses_stq;
        } else if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_uop_uses_stq;
        } else if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_uop_uses_stq;
        } else if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_uop_uses_stq;
        } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_uop_uses_stq;
        } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_uop_uses_stq;
        } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_ldq_idx))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_uop_uses_stq;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_uop_is_amo;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_uop_uses_stq;
        }
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_30202;
    } else if ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_uop_rob_idx;
    } else if ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_uop_rob_idx;
    } else if ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_uop_rob_idx;
    } else if ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_uop_rob_idx;
    } else if ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_uop_rob_idx;
    } else if ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_uop_rob_idx;
    } else if ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_uop_rob_idx;
    } else if ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_uop_rob_idx;
    } else if ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_uop_rob_idx;
    } else if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_uop_rob_idx;
    } else if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_uop_rob_idx;
    } else if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_uop_rob_idx;
    } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_rob_idx;
    } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_rob_idx;
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache_io_lsu_resp_0_bits_uop_stq_idx))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_rob_idx;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32279 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_is_amo;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32277 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_uses_stq;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_32301 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_rob_idx;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3888 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_mispredict));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_23 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_br_mask) 
                    >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits)) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_taken)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_13 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_val;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_15 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_ftq_idx;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_1355 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_8)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__first_empty));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_63 
        = (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_repair_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_1316 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_repair_idx) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_158 = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_mispredict) 
                                                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_ptr = 0U;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__do_commit_update) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_ptr 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_84;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_289 
        = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_cfi_type)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_taken));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_238 
        = (0xffffffffffULL & ((~ (0x3fULL | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_23))) 
                              | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_uop_pc_lob))));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_159 = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_pc 
                                                  == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_repair_pc);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__brinfos_0_uop_ftq_idx 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_1_ftq_idx;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT___T_2 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__ptr_match) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__BranchKillableQueue__DOT__maybe_full))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit__DOT__ifpu_io_resp_valid));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1085) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ma_st_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__mem_units_0__DOT__MemAddrCalcUnit_io_resp_bits_mxcpt_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1242 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_0_stq_idx;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ma_st_0 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1242 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1056 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1014) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1266 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1263)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_0_stq_idx)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__Arbiter_io_out_bits_uop_stq_idx));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__arb_io_out_bits_valid 
        = (1U & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__state))
                  ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_kill))
                  : (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__state))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_7 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_6 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_5 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_4 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_3 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_2 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore_1 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT__res_ignore 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l)) 
           & (1U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0_io_prv)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0 
        = (((~ ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_order_fail)
                 : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_order_fail)
                     : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_order_fail)
                         : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_order_fail)
                             : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_order_fail)
                                 : ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_order_fail)
                                     : ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_order_fail)
                                         : ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_order_fail)
                                             : ((7U 
                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_order_fail)
                                                 : 
                                                ((6U 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_order_fail)
                                                  : 
                                                 ((5U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_order_fail)
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_order_fail)
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_order_fail)
                                                     : 
                                                    ((2U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_order_fail)
                                                      : 
                                                     ((1U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_order_fail)
                                                       : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_order_fail))))))))))))))))) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_665) 
               & ((~ ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_15)
                       : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_14)
                           : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_13)
                               : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_12)
                                   : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_11)
                                       : ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_10)
                                           : ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_9)
                                               : ((8U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_8)
                                                   : 
                                                  ((7U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_7)
                                                    : 
                                                   ((6U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_6)
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_5)
                                                      : 
                                                     ((4U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_4)
                                                       : 
                                                      ((3U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_3)
                                                        : 
                                                       ((2U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_2)
                                                         : 
                                                        ((1U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_1)
                                                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p2_block_load_mask_0))))))))))))))))) 
                  & (((~ ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_15)
                           : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_14)
                               : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_13)
                                   : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_12)
                                       : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_11)
                                           : ((0xaU 
                                               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_10)
                                               : ((9U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_9)
                                                   : 
                                                  ((8U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_8)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_7)
                                                     : 
                                                    ((6U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_6)
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_5)
                                                       : 
                                                      ((4U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_4)
                                                        : 
                                                       ((3U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_3)
                                                         : 
                                                        ((2U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_2)
                                                          : 
                                                         ((1U 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_1)
                                                           : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__p1_block_load_mask_0))))))))))))))))) 
                      & (((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_valid)
                           : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_valid)
                               : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_valid)
                                   : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_valid)
                                       : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_valid)
                                           : ((0xaU 
                                               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_valid)
                                               : ((9U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_valid)
                                                   : 
                                                  ((8U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_valid)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_valid)
                                                     : 
                                                    ((6U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_valid)
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_valid)
                                                       : 
                                                      ((4U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_valid)
                                                        : 
                                                       ((3U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_valid)
                                                         : 
                                                        ((2U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_valid)
                                                          : 
                                                         ((1U 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_valid)
                                                           : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_valid)))))))))))))))) 
                         & (((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_addr_valid)
                              : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_addr_valid)
                                  : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_addr_valid)
                                      : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_addr_valid)
                                          : ((0xbU 
                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_addr_valid)
                                              : ((0xaU 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_addr_valid)
                                                  : 
                                                 ((9U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_addr_valid)
                                                   : 
                                                  ((8U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_addr_valid)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_addr_valid)
                                                     : 
                                                    ((6U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_addr_valid)
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_addr_valid)
                                                       : 
                                                      ((4U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_addr_valid)
                                                        : 
                                                       ((3U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_addr_valid)
                                                         : 
                                                        ((2U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_addr_valid)
                                                          : 
                                                         ((1U 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_addr_valid)
                                                           : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_addr_valid)))))))))))))))) 
                            & ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_addr_is_virtual)
                                : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_14_bits_addr_is_virtual)
                                    : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_13_bits_addr_is_virtual)
                                        : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_12_bits_addr_is_virtual)
                                            : ((0xbU 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_11_bits_addr_is_virtual)
                                                : (
                                                   (0xaU 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_10_bits_addr_is_virtual)
                                                    : 
                                                   ((9U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_9_bits_addr_is_virtual)
                                                     : 
                                                    ((8U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_8_bits_addr_is_virtual)
                                                      : 
                                                     ((7U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_7_bits_addr_is_virtual)
                                                       : 
                                                      ((6U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_addr_is_virtual)
                                                        : 
                                                       ((5U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_5_bits_addr_is_virtual)
                                                         : 
                                                        ((4U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_4_bits_addr_is_virtual)
                                                          : 
                                                         ((3U 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                           ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_3_bits_addr_is_virtual)
                                                           : 
                                                          ((2U 
                                                            == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_2_bits_addr_is_virtual)
                                                            : 
                                                           ((1U 
                                                             == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_1_bits_addr_is_virtual)
                                                             : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_0_bits_addr_is_virtual))))))))))))))))))) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__REG))))) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_863) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_838)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_897)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1790)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1802)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1817)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1822)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406)
                        : ((4U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_269)) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406))
                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406)))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24406))));
    __Vtemp_7[1U] = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_23) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid))
                      ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history) 
                          >> 0x1fU) | ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history 
                                                >> 0x20U)) 
                                       << 1U)) : ((
                                                   (0U 
                                                    != 
                                                    ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_br_mask) 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid)
                                                         ? 
                                                        (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_23)
                                                           ? 
                                                          (~ 
                                                           ((IData)(1U) 
                                                            << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits)))
                                                           : 0xfU) 
                                                         & ((((IData)(1U) 
                                                              << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits)) 
                                                             | VL_SHIFTR_III(4,4,32, 
                                                                             (0xfU 
                                                                              & ((IData)(1U) 
                                                                                << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 1U)) 
                                                            | (VL_SHIFTR_III(4,4,32, 
                                                                             (0xfU 
                                                                              & ((IData)(1U) 
                                                                                << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 2U) 
                                                               | VL_SHIFTR_III(4,4,32, 
                                                                               (0xfU 
                                                                                & ((IData)(1U) 
                                                                                << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 3U))))
                                                         : 0xfU))) 
                                                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_current_saw_branch_not_taken))
                                                   ? 
                                                  (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history) 
                                                    >> 0x1fU) 
                                                   | ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history 
                                                               >> 0x20U)) 
                                                      << 1U))
                                                   : (IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history 
                                                              >> 0x20U))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_current_saw_branch_not_taken
        [0U]) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx_MPORT_data 
            = (0x1fU & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_ras_idx
               [0U]);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history_MPORT_data 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4__DOT__ram_ghist_old_history
            [0U];
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_ras_idx_MPORT_data 
            = (0x1fU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_is_call))
                         ? ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_ras_idx))
                         : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_ras_idx) 
                            - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_is_ret)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_0_old_history_MPORT_data 
            = (((QData)((IData)(__Vtemp_7[1U])) << 0x20U) 
               | (QData)((IData)((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_23) 
                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid))
                                   ? (1U | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history) 
                                            << 1U))
                                   : (((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_br_mask) 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_valid)
                                                   ? 
                                                  (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_23)
                                                     ? 
                                                    (~ 
                                                     ((IData)(1U) 
                                                      << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits)))
                                                     : 0xfU) 
                                                   & ((((IData)(1U) 
                                                        << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits)) 
                                                       | VL_SHIFTR_III(4,4,32, 
                                                                       (0xfU 
                                                                        & ((IData)(1U) 
                                                                           << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 1U)) 
                                                      | (VL_SHIFTR_III(4,4,32, 
                                                                       (0xfU 
                                                                        & ((IData)(1U) 
                                                                           << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 2U) 
                                                         | VL_SHIFTR_III(4,4,32, 
                                                                         (0xfU 
                                                                          & ((IData)(1U) 
                                                                             << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_entry_cfi_idx_bits))), 3U))))
                                                   : 0xfU))) 
                                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_current_saw_branch_not_taken))
                                       ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history) 
                                          << 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__prev_ghist_old_history))))));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_242 
        = (0xffffffffffULL & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_238 
                              + (QData)((IData)((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_uop_edge_inst) 
                                                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_uop_is_rvc))
                                                  ? 2U
                                                  : 4U)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_1322 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_mispredict) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_6) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair))
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair)
               : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair)
                   ? ((~ (((0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_repair_idx))) 
                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_end_idx)) 
                          | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_159))) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair))
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_update_repair))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq_io_bpdupdate_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_8) 
           & ((~ ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_159) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_9))) 
              & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__first_empty)) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_valid) 
                    | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_br_mask))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state_barrier_io_x 
        = (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__hella_state)) 
            & ((1U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__hella_state)) 
               & (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__hella_state))))
            ? 1U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_valid)
                     ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__traverse)
                         ? 1U : 0U) : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___r_pte_T_1)
                                        ? 0U : ((0U 
                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                 ? 
                                                ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___T_22)
                                                  ? 
                                                 ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__arb_io_out_bits_valid)
                                                   ? 1U
                                                   : 0U)
                                                  : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                 : 
                                                ((1U 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                  ? 
                                                 ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__pte_cache_hit)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state)
                                                   : 
                                                  ((0U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__hella_state))
                                                    ? 2U
                                                    : 1U))
                                                  : 
                                                 ((2U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                   ? 
                                                  ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_dpath_perf_l2hit)
                                                    ? 1U
                                                    : 4U)
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                    ? 
                                                   ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu_io_hellacache_s2_xcpt_ae_ld)
                                                     ? 0U
                                                     : 5U)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                     ? 0U
                                                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state)))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17324 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17325 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17326 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17327 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17328 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17329 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17330 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17331 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17332 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17333 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17334 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17335 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17336 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_17337 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
           & (0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_919 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_863));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_922 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_838));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1866)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1878)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1893)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1898)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543)
                        : ((5U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_271)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24543))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_84 
        = (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_ptr)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_269 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_taken)) 
           & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_cfi_type)) 
              & ((0xffffffffffULL & (~ (0x3fULL | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_23)))) 
                 == (0xffffffffffULL & (~ (7ULL | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_242)))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections_io_deq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq_io_bpdupdate_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections_io_deq_valid) 
           & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq_io_bpdupdate_valid)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq_io_bpdupdate_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_btb_mispredicts = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_is_mispredict_update 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_10;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_is_repair_update 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_11;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_pc 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_pc;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_idx_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_idx_bits 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_taken 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_taken;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_mispredicted 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_mispredicted;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_is_jal 
            = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_type)) 
               | (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_type)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_target 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_target;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_bpd_meta_addr_pipe_0][0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_bpd_meta_addr_pipe_0][1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_bpd_meta_addr_pipe_0][2U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[3U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_bpd_meta_addr_pipe_0][3U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_br_mask 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_valid)
                ? (((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_bits)) 
                     | VL_SHIFTR_III(4,4,32, (0xfU 
                                              & ((IData)(1U) 
                                                 << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_bits))), 1U)) 
                    | (VL_SHIFTR_III(4,4,32, (0xfU 
                                              & ((IData)(1U) 
                                                 << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_bits))), 2U) 
                       | VL_SHIFTR_III(4,4,32, (0xfU 
                                                & ((IData)(1U) 
                                                   << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_cfi_idx_bits))), 3U))) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_br_mask))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__bpd_entry_br_mask));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_btb_mispredicts 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_btb_mispredicts
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_is_mispredict_update 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_is_mispredict_update
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_is_repair_update 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_is_repair_update
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_pc 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_pc
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_idx_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_cfi_idx_valid
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_idx_bits 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_cfi_idx_bits
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_taken 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_cfi_taken
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_mispredicted 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_cfi_mispredicted
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_cfi_is_jal 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_cfi_is_jal
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_target 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_target
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value][0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value][1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value][2U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_meta_0[3U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_meta_0
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value][3U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_update_arbiter_io_out_bits_br_mask 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__ram_br_mask
            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f4_btb_corrections__DOT__deq_ptr_value];
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_uops_1_ftq_idx 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT___T_35)
            ? 0U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__REG_3_ftq_idx));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sta_retry_0 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_16970) 
            & ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_addr_valid)
                : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_addr_valid)
                    : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_addr_valid)
                        : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_addr_valid)
                            : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_addr_valid)
                                : ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_addr_valid)
                                    : ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_addr_valid)
                                        : ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_addr_valid)
                                            : ((7U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_addr_valid)
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_addr_valid)
                                                    : 
                                                   ((5U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_addr_valid)
                                                     : 
                                                    ((4U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_addr_valid)
                                                      : 
                                                     ((3U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_addr_valid)
                                                       : 
                                                      ((2U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_addr_valid)
                                                        : 
                                                       ((1U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_addr_valid)
                                                         : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_addr_valid))))))))))))))))) 
           & ((((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_bits_addr_is_virtual)
                 : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_bits_addr_is_virtual)
                     : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_bits_addr_is_virtual)
                         : ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_bits_addr_is_virtual)
                             : ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_bits_addr_is_virtual)
                                 : ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_bits_addr_is_virtual)
                                     : ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_bits_addr_is_virtual)
                                         : ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_bits_addr_is_virtual)
                                             : ((7U 
                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_bits_addr_is_virtual)
                                                 : 
                                                ((6U 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_bits_addr_is_virtual)
                                                  : 
                                                 ((5U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_bits_addr_is_virtual)
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_bits_addr_is_virtual)
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_addr_is_virtual)
                                                     : 
                                                    ((2U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_addr_is_virtual)
                                                      : 
                                                     ((1U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_retry_idx))
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_addr_is_virtual)
                                                       : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_addr_is_virtual)))))))))))))))) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__REG_1)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_919) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_922) 
                    & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0)) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_803))))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1942)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1954)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1969)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1974)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680)
                        : ((6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_273)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24680))));
    __Vtemp_12[1U] = (((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_22_br_mask) 
                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_289)
                                    ? (~ ((IData)(1U) 
                                          << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0)))
                                    : 0xfU) & ((((IData)(1U) 
                                                 << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0)) 
                                                | VL_SHIFTR_III(4,4,32, 
                                                                (0xfU 
                                                                 & ((IData)(1U) 
                                                                    << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 1U)) 
                                               | (VL_SHIFTR_III(4,4,32, 
                                                                (0xfU 
                                                                 & ((IData)(1U) 
                                                                    << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 2U) 
                                                  | VL_SHIFTR_III(4,4,32, 
                                                                  (0xfU 
                                                                   & ((IData)(1U) 
                                                                      << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 3U)))))) 
                       | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken
                       [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken_MPORT_3_addr_pipe_0])
                       ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]) 
                           >> 0x1fU) | ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                                 [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0] 
                                                 >> 0x20U)) 
                                        << 1U)) : (IData)(
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                                           [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0] 
                                                           >> 0x20U)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_289) {
        __Vtemp_13[0U] = (1U | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                        [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]) 
                                << 1U));
        __Vtemp_13[2U] = ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0] 
                                   >> 0x20U)) >> 0x1fU);
    } else if (((0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__REG_22_br_mask) 
                        & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_289)
                             ? (~ ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0)))
                             : 0xfU) & ((((IData)(1U) 
                                          << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0)) 
                                         | VL_SHIFTR_III(4,4,32, 
                                                         (0xfU 
                                                          & ((IData)(1U) 
                                                             << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 1U)) 
                                        | (VL_SHIFTR_III(4,4,32, 
                                                         (0xfU 
                                                          & ((IData)(1U) 
                                                             << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 2U) 
                                           | VL_SHIFTR_III(4,4,32, 
                                                           (0xfU 
                                                            & ((IData)(1U) 
                                                               << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT____VdfgRegularize_ha9547c87_2_0))), 3U)))))) 
                | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken
                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_current_saw_branch_not_taken_MPORT_3_addr_pipe_0])) {
        __Vtemp_13[0U] = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                  [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]) 
                          << 1U);
        __Vtemp_13[2U] = ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0] 
                                   >> 0x20U)) >> 0x1fU);
    } else {
        __Vtemp_13[0U] = (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                 [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]);
        __Vtemp_13[2U] = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_ghist_old_history 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_9)
            ? 0ULL : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_269)
                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]
                       : (((QData)((IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_289)
                                             ? (((IData)(
                                                         vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0]) 
                                                 >> 0x1fU) 
                                                | ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history
                                                            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ghist_1_old_history_MPORT_3_addr_pipe_0] 
                                                            >> 0x20U)) 
                                                   << 1U))
                                             : __Vtemp_12[1U]))) 
                           << 0x20U) | (QData)((IData)(
                                                       __Vtemp_13[0U])))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1072 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1056) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sta_retry_0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1066 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sfence_0)
            ? (0x7fffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__exe_reg_rs1_data_0)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_load_retry_0)
                ? ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_retry_idx))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_15_bits_addr_bits
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_19929)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__will_fire_sta_retry_0)
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_19914
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1063)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2018)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2030)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2045)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2050)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817)
                        : ((7U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_275)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24817))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__REG_3_ftq_idx 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__RegisterReadDecode_1_io_rrd_uop_ftq_idx;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_vaddr 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1014)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__mem_units_0__DOT__MemAddrCalcUnit_io_resp_bits_addr
            : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_1066);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2094)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2106)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2121)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2126)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954)
                        : ((8U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_277)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_24954))));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_425 = ((0xc0000U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_data_0 
                                                               >> 0x20U)) 
                                                      << 0x12U)) 
                                                  | ((0x3fe00U 
                                                      & (((1U 
                                                           > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_level))
                                                           ? 
                                                          (0x7fffe00U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_vaddr 
                                                                      >> 0xcU)))
                                                           : 0U) 
                                                         | (0xffe00U 
                                                            & (IData)(
                                                                      (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_data_0 
                                                                       >> 0xeU))))) 
                                                     | (0x1ffU 
                                                        & (((2U 
                                                             > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_level))
                                                             ? 
                                                            (0x7ffffffU 
                                                             & (IData)(
                                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_vaddr 
                                                                        >> 0xcU)))
                                                             : 0U) 
                                                           | (0xfffffU 
                                                              & (IData)(
                                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_data_0 
                                                                         >> 0xeU)))))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2170)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2182)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2197)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2202)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091)
                        : ((9U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_279)) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091))
                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091)))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25091))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__mpu_ppn_0 
        = (0xfffffffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_valid_0)
                          ? (0xfffffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_ppn))
                          : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__vm_enabled_0)
                              ? vlSelfRef.__VdfgRegularize_hd87f99a1_1_425
                              : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_vaddr 
                                         >> 0xcU)))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2246)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2258)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2273)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2278)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228)
                        : ((0xaU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_281)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25228))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__pmp_0__DOT____VdfgRegularize_h574322a0_0_0 
        = ((0x1ffffe00U & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__mpu_ppn_0 
                           << 9U)) | (0x1ffU & (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb_io_req_0_bits_vaddr 
                                                        >> 3U))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2322)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2334)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2349)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2354)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365)
                        : ((0xbU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_283)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25365))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2398)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2410)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2425)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2430)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502)
                        : ((0xcU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_285)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25502))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2474)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2486)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2501)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2506)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639)
                        : ((0xdU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_287)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25639))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2550)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2562)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2577)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2582)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776)
                        : ((0xeU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_289)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25776))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2626)
            ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2638)
                ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2653)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2656)
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913)
                        : ((0xfU != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0))
                            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_291)) 
                               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913))
                            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913)))
                    : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___GEN_25913))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2820 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_bits_uop_is_fence)) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2815) 
               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_mask_0)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2796) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2780 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_bits_uop_is_fence)) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2775) 
               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_mask_0)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2756) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2740 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_bits_uop_is_fence)) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2735) 
               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_mask_0)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2716) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2700 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_bits_uop_is_fence)) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2695) 
               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_mask_0)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2676) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldst_addr_matches_0_3 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT____VdfgRegularize_hbcd0008a_0_467) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2820) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2825) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_2828))));
}

extern const VlWide<8>/*255:0*/ VTestHarness__ConstPool__CONST_h4e9f510d_0;

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__77(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__77\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15 = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_1;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_1 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0 = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2 = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5 = 0;
    IData/*16:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T = 0;
    CData/*7:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1 = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___out_arw_valid_T_1;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___out_arw_valid_T_1 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT___d_first_T;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT___d_first_T = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_ar_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_ar_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___bundleIn_0_a_ready_T;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___bundleIn_0_a_ready_T = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT____VdfgRegularize_h063f9c6d_0_1;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT____VdfgRegularize_h063f9c6d_0_1 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__out_1_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__out_1_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_6_0;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_6_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_aw_ready;
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_aw_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_1;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_1 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_x;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_x = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0;
    TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8;
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345 = 0;
    CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_118;
    __VdfgRegularize_hd87f99a1_1_118 = 0;
    CData/*0:0*/ __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 = 0;
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_7;
    VlWide<4>/*127:0*/ __Vtemp_8;
    VlWide<4>/*127:0*/ __Vtemp_9;
    VlWide<4>/*127:0*/ __Vtemp_10;
    VlWide<4>/*127:0*/ __Vtemp_11;
    VlWide<4>/*127:0*/ __Vtemp_12;
    VlWide<4>/*127:0*/ __Vtemp_13;
    VlWide<4>/*127:0*/ __Vtemp_14;
    VlWide<4>/*127:0*/ __Vtemp_15;
    VlWide<4>/*127:0*/ __Vtemp_16;
    VlWide<4>/*127:0*/ __Vtemp_17;
    VlWide<4>/*127:0*/ __Vtemp_18;
    VlWide<4>/*127:0*/ __Vtemp_19;
    VlWide<4>/*127:0*/ __Vtemp_20;
    VlWide<4>/*127:0*/ __Vtemp_21;
    VlWide<4>/*127:0*/ __Vtemp_22;
    VlWide<4>/*127:0*/ __Vtemp_23;
    VlWide<4>/*127:0*/ __Vtemp_24;
    VlWide<4>/*127:0*/ __Vtemp_25;
    VlWide<4>/*127:0*/ __Vtemp_26;
    VlWide<4>/*127:0*/ __Vtemp_27;
    VlWide<4>/*127:0*/ __Vtemp_28;
    VlWide<4>/*127:0*/ __Vtemp_29;
    VlWide<4>/*127:0*/ __Vtemp_30;
    VlWide<4>/*127:0*/ __Vtemp_31;
    VlWide<4>/*127:0*/ __Vtemp_32;
    VlWide<4>/*127:0*/ __Vtemp_33;
    VlWide<4>/*127:0*/ __Vtemp_34;
    VlWide<4>/*127:0*/ __Vtemp_35;
    VlWide<4>/*127:0*/ __Vtemp_36;
    VlWide<4>/*127:0*/ __Vtemp_37;
    VlWide<4>/*127:0*/ __Vtemp_38;
    VlWide<4>/*127:0*/ __Vtemp_39;
    VlWide<4>/*127:0*/ __Vtemp_40;
    VlWide<4>/*127:0*/ __Vtemp_41;
    VlWide<4>/*127:0*/ __Vtemp_42;
    VlWide<4>/*127:0*/ __Vtemp_43;
    VlWide<4>/*127:0*/ __Vtemp_44;
    VlWide<4>/*127:0*/ __Vtemp_45;
    VlWide<4>/*127:0*/ __Vtemp_46;
    VlWide<4>/*127:0*/ __Vtemp_47;
    VlWide<4>/*127:0*/ __Vtemp_48;
    VlWide<4>/*127:0*/ __Vtemp_49;
    VlWide<4>/*127:0*/ __Vtemp_50;
    VlWide<4>/*127:0*/ __Vtemp_51;
    VlWide<4>/*127:0*/ __Vtemp_52;
    VlWide<4>/*127:0*/ __Vtemp_53;
    VlWide<4>/*127:0*/ __Vtemp_54;
    VlWide<4>/*127:0*/ __Vtemp_55;
    VlWide<4>/*127:0*/ __Vtemp_56;
    VlWide<4>/*127:0*/ __Vtemp_57;
    VlWide<4>/*127:0*/ __Vtemp_58;
    VlWide<4>/*127:0*/ __Vtemp_59;
    VlWide<4>/*127:0*/ __Vtemp_60;
    VlWide<4>/*127:0*/ __Vtemp_61;
    VlWide<4>/*127:0*/ __Vtemp_62;
    VlWide<4>/*127:0*/ __Vtemp_63;
    VlWide<4>/*127:0*/ __Vtemp_64;
    VlWide<4>/*127:0*/ __Vtemp_65;
    VlWide<4>/*127:0*/ __Vtemp_66;
    VlWide<4>/*127:0*/ __Vtemp_67;
    VlWide<4>/*127:0*/ __Vtemp_68;
    VlWide<4>/*127:0*/ __Vtemp_69;
    VlWide<4>/*127:0*/ __Vtemp_70;
    VlWide<4>/*127:0*/ __Vtemp_71;
    VlWide<4>/*127:0*/ __Vtemp_72;
    VlWide<4>/*127:0*/ __Vtemp_73;
    VlWide<4>/*127:0*/ __Vtemp_74;
    VlWide<4>/*127:0*/ __Vtemp_75;
    VlWide<4>/*127:0*/ __Vtemp_76;
    VlWide<4>/*127:0*/ __Vtemp_77;
    VlWide<4>/*127:0*/ __Vtemp_78;
    VlWide<4>/*127:0*/ __Vtemp_79;
    VlWide<4>/*127:0*/ __Vtemp_80;
    VlWide<4>/*127:0*/ __Vtemp_81;
    VlWide<4>/*127:0*/ __Vtemp_82;
    VlWide<4>/*127:0*/ __Vtemp_83;
    VlWide<4>/*127:0*/ __Vtemp_84;
    VlWide<4>/*127:0*/ __Vtemp_85;
    VlWide<4>/*127:0*/ __Vtemp_86;
    VlWide<4>/*127:0*/ __Vtemp_87;
    VlWide<4>/*127:0*/ __Vtemp_88;
    VlWide<4>/*127:0*/ __Vtemp_89;
    VlWide<4>/*127:0*/ __Vtemp_90;
    VlWide<4>/*127:0*/ __Vtemp_91;
    VlWide<4>/*127:0*/ __Vtemp_92;
    VlWide<4>/*127:0*/ __Vtemp_93;
    VlWide<4>/*127:0*/ __Vtemp_94;
    VlWide<4>/*127:0*/ __Vtemp_95;
    VlWide<4>/*127:0*/ __Vtemp_96;
    VlWide<4>/*127:0*/ __Vtemp_97;
    VlWide<4>/*127:0*/ __Vtemp_98;
    VlWide<4>/*127:0*/ __Vtemp_99;
    VlWide<4>/*127:0*/ __Vtemp_100;
    VlWide<4>/*127:0*/ __Vtemp_101;
    VlWide<4>/*127:0*/ __Vtemp_102;
    VlWide<4>/*127:0*/ __Vtemp_103;
    VlWide<4>/*127:0*/ __Vtemp_104;
    VlWide<4>/*127:0*/ __Vtemp_105;
    VlWide<4>/*127:0*/ __Vtemp_106;
    VlWide<4>/*127:0*/ __Vtemp_107;
    VlWide<4>/*127:0*/ __Vtemp_108;
    VlWide<4>/*127:0*/ __Vtemp_109;
    VlWide<4>/*127:0*/ __Vtemp_110;
    VlWide<4>/*127:0*/ __Vtemp_111;
    VlWide<4>/*127:0*/ __Vtemp_112;
    VlWide<4>/*127:0*/ __Vtemp_113;
    VlWide<4>/*127:0*/ __Vtemp_114;
    VlWide<4>/*127:0*/ __Vtemp_115;
    VlWide<4>/*127:0*/ __Vtemp_116;
    VlWide<4>/*127:0*/ __Vtemp_117;
    VlWide<4>/*127:0*/ __Vtemp_118;
    VlWide<4>/*127:0*/ __Vtemp_119;
    VlWide<4>/*127:0*/ __Vtemp_120;
    VlWide<4>/*127:0*/ __Vtemp_121;
    VlWide<4>/*127:0*/ __Vtemp_122;
    VlWide<4>/*127:0*/ __Vtemp_123;
    VlWide<4>/*127:0*/ __Vtemp_124;
    VlWide<4>/*127:0*/ __Vtemp_125;
    VlWide<4>/*127:0*/ __Vtemp_126;
    VlWide<4>/*127:0*/ __Vtemp_127;
    VlWide<4>/*127:0*/ __Vtemp_128;
    VlWide<4>/*127:0*/ __Vtemp_129;
    VlWide<4>/*127:0*/ __Vtemp_130;
    VlWide<4>/*127:0*/ __Vtemp_131;
    VlWide<4>/*127:0*/ __Vtemp_132;
    VlWide<4>/*127:0*/ __Vtemp_133;
    VlWide<4>/*127:0*/ __Vtemp_134;
    VlWide<4>/*127:0*/ __Vtemp_135;
    VlWide<4>/*127:0*/ __Vtemp_136;
    VlWide<4>/*127:0*/ __Vtemp_137;
    VlWide<4>/*127:0*/ __Vtemp_138;
    VlWide<4>/*127:0*/ __Vtemp_139;
    VlWide<4>/*127:0*/ __Vtemp_140;
    VlWide<4>/*127:0*/ __Vtemp_141;
    VlWide<4>/*127:0*/ __Vtemp_142;
    VlWide<4>/*127:0*/ __Vtemp_143;
    VlWide<4>/*127:0*/ __Vtemp_144;
    VlWide<4>/*127:0*/ __Vtemp_145;
    VlWide<4>/*127:0*/ __Vtemp_146;
    VlWide<4>/*127:0*/ __Vtemp_147;
    VlWide<4>/*127:0*/ __Vtemp_148;
    VlWide<4>/*127:0*/ __Vtemp_149;
    VlWide<4>/*127:0*/ __Vtemp_150;
    VlWide<4>/*127:0*/ __Vtemp_151;
    VlWide<4>/*127:0*/ __Vtemp_152;
    VlWide<4>/*127:0*/ __Vtemp_153;
    VlWide<4>/*127:0*/ __Vtemp_154;
    VlWide<4>/*127:0*/ __Vtemp_155;
    VlWide<4>/*127:0*/ __Vtemp_156;
    VlWide<4>/*127:0*/ __Vtemp_157;
    VlWide<4>/*127:0*/ __Vtemp_158;
    VlWide<4>/*127:0*/ __Vtemp_159;
    VlWide<4>/*127:0*/ __Vtemp_160;
    VlWide<4>/*127:0*/ __Vtemp_161;
    VlWide<4>/*127:0*/ __Vtemp_162;
    VlWide<4>/*127:0*/ __Vtemp_163;
    VlWide<4>/*127:0*/ __Vtemp_164;
    VlWide<4>/*127:0*/ __Vtemp_165;
    VlWide<4>/*127:0*/ __Vtemp_166;
    VlWide<4>/*127:0*/ __Vtemp_167;
    VlWide<4>/*127:0*/ __Vtemp_168;
    VlWide<4>/*127:0*/ __Vtemp_169;
    VlWide<4>/*127:0*/ __Vtemp_170;
    VlWide<4>/*127:0*/ __Vtemp_171;
    VlWide<4>/*127:0*/ __Vtemp_172;
    VlWide<4>/*127:0*/ __Vtemp_173;
    VlWide<4>/*127:0*/ __Vtemp_174;
    VlWide<4>/*127:0*/ __Vtemp_175;
    VlWide<4>/*127:0*/ __Vtemp_176;
    VlWide<4>/*127:0*/ __Vtemp_177;
    VlWide<4>/*127:0*/ __Vtemp_178;
    VlWide<4>/*127:0*/ __Vtemp_179;
    VlWide<4>/*127:0*/ __Vtemp_180;
    VlWide<4>/*127:0*/ __Vtemp_181;
    VlWide<4>/*127:0*/ __Vtemp_182;
    VlWide<4>/*127:0*/ __Vtemp_183;
    VlWide<4>/*127:0*/ __Vtemp_184;
    VlWide<4>/*127:0*/ __Vtemp_185;
    VlWide<4>/*127:0*/ __Vtemp_186;
    VlWide<4>/*127:0*/ __Vtemp_187;
    VlWide<4>/*127:0*/ __Vtemp_188;
    VlWide<4>/*127:0*/ __Vtemp_189;
    VlWide<4>/*127:0*/ __Vtemp_190;
    VlWide<4>/*127:0*/ __Vtemp_191;
    VlWide<4>/*127:0*/ __Vtemp_192;
    VlWide<4>/*127:0*/ __Vtemp_193;
    VlWide<4>/*127:0*/ __Vtemp_194;
    VlWide<4>/*127:0*/ __Vtemp_195;
    VlWide<4>/*127:0*/ __Vtemp_196;
    VlWide<4>/*127:0*/ __Vtemp_197;
    VlWide<4>/*127:0*/ __Vtemp_198;
    VlWide<4>/*127:0*/ __Vtemp_199;
    VlWide<4>/*127:0*/ __Vtemp_200;
    VlWide<4>/*127:0*/ __Vtemp_201;
    VlWide<4>/*127:0*/ __Vtemp_202;
    VlWide<4>/*127:0*/ __Vtemp_203;
    VlWide<4>/*127:0*/ __Vtemp_204;
    VlWide<4>/*127:0*/ __Vtemp_205;
    VlWide<4>/*127:0*/ __Vtemp_206;
    VlWide<4>/*127:0*/ __Vtemp_207;
    VlWide<4>/*127:0*/ __Vtemp_208;
    VlWide<4>/*127:0*/ __Vtemp_209;
    VlWide<4>/*127:0*/ __Vtemp_210;
    VlWide<4>/*127:0*/ __Vtemp_211;
    VlWide<4>/*127:0*/ __Vtemp_212;
    VlWide<4>/*127:0*/ __Vtemp_213;
    VlWide<4>/*127:0*/ __Vtemp_214;
    VlWide<4>/*127:0*/ __Vtemp_215;
    VlWide<4>/*127:0*/ __Vtemp_216;
    VlWide<4>/*127:0*/ __Vtemp_217;
    VlWide<4>/*127:0*/ __Vtemp_218;
    VlWide<4>/*127:0*/ __Vtemp_219;
    VlWide<4>/*127:0*/ __Vtemp_220;
    VlWide<4>/*127:0*/ __Vtemp_221;
    VlWide<4>/*127:0*/ __Vtemp_222;
    VlWide<4>/*127:0*/ __Vtemp_223;
    VlWide<4>/*127:0*/ __Vtemp_224;
    VlWide<4>/*127:0*/ __Vtemp_225;
    VlWide<4>/*127:0*/ __Vtemp_226;
    VlWide<4>/*127:0*/ __Vtemp_227;
    VlWide<4>/*127:0*/ __Vtemp_228;
    VlWide<4>/*127:0*/ __Vtemp_229;
    VlWide<4>/*127:0*/ __Vtemp_230;
    VlWide<4>/*127:0*/ __Vtemp_231;
    VlWide<4>/*127:0*/ __Vtemp_232;
    VlWide<4>/*127:0*/ __Vtemp_233;
    VlWide<4>/*127:0*/ __Vtemp_234;
    VlWide<4>/*127:0*/ __Vtemp_235;
    VlWide<4>/*127:0*/ __Vtemp_236;
    VlWide<4>/*127:0*/ __Vtemp_237;
    VlWide<4>/*127:0*/ __Vtemp_238;
    VlWide<4>/*127:0*/ __Vtemp_239;
    VlWide<4>/*127:0*/ __Vtemp_240;
    VlWide<4>/*127:0*/ __Vtemp_241;
    VlWide<4>/*127:0*/ __Vtemp_242;
    VlWide<4>/*127:0*/ __Vtemp_243;
    VlWide<4>/*127:0*/ __Vtemp_244;
    VlWide<4>/*127:0*/ __Vtemp_245;
    VlWide<4>/*127:0*/ __Vtemp_246;
    VlWide<4>/*127:0*/ __Vtemp_247;
    VlWide<4>/*127:0*/ __Vtemp_248;
    VlWide<4>/*127:0*/ __Vtemp_249;
    VlWide<4>/*127:0*/ __Vtemp_250;
    VlWide<4>/*127:0*/ __Vtemp_251;
    VlWide<4>/*127:0*/ __Vtemp_252;
    VlWide<4>/*127:0*/ __Vtemp_253;
    VlWide<4>/*127:0*/ __Vtemp_254;
    VlWide<8>/*255:0*/ __Vtemp_255;
    VlWide<8>/*255:0*/ __Vtemp_256;
    VlWide<8>/*255:0*/ __Vtemp_257;
    VlWide<8>/*255:0*/ __Vtemp_258;
    VlWide<8>/*255:0*/ __Vtemp_259;
    VlWide<8>/*255:0*/ __Vtemp_260;
    VlWide<8>/*255:0*/ __Vtemp_261;
    VlWide<8>/*255:0*/ __Vtemp_262;
    VlWide<8>/*255:0*/ __Vtemp_263;
    CData/*31:0*/ __Vtemp_267;
    CData/*31:0*/ __Vtemp_274;
    // Body
    __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0;
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value 
        = vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value;
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1[vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_ready 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_lock 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) 
           & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_lock
           [0U]);
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_cache 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__ram_cache
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_prot 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__ram_prot
            [0U];
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_cache = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_prot = 0U;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6__v0;
    }
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__monitor__DOT__d_first_beats1_opdata 
        = (1U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode
           [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]);
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__monitor__DOT__d_first_beats1_decode 
        = (0x1ffU & (~ (0x1ffU & (((IData)(0xfffU) 
                                   << vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]) 
                                  >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_deq_valid) 
           & (~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT___do_enq_T 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_3 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)
            ? (0x1fU & (~ (0x1fU & (((IData)(0xffU) 
                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_size)) 
                                    >> 3U)))) : 0U);
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_2_MPORT_5_data = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_3_MPORT_5_data = 0U;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_2_MPORT_5_data 
            = ((0x40000000U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_br_mask) 
                               << 0x1cU)) | ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_btb_mispredicts))
                                              ? 0U : 
                                             (0x3fffffffU 
                                              & (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_idx 
                                                         >> 7U)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_3_MPORT_5_data 
            = ((0x40000000U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_br_mask) 
                               << 0x1bU)) | ((8U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_btb_mispredicts))
                                              ? 0U : 
                                             (0x3fffffffU 
                                              & (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_idx 
                                                         >> 7U)))));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___GEN_14 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_0_0)
                  ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_0
                     [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_0_MPORT_2_addr_pipe_0] 
                     >> 0x1eU) : (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_1_0
                                  [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_1_0_MPORT_3_addr_pipe_0] 
                                  >> 0x1eU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_0_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_0_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_1_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_1_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_2_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_2_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wmeta_mask 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wbtb_mask) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_br_mask)) 
           & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___T_716) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fvalid))
                ? 0xfU : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fvalid)
                                  ? 0xfU : 0U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update___05Fbits_btb_mispredicts))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT____VdfgRegularize_hbb64a946_10_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_valid));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_49 
        = (0x7fffU & (((0xffU | ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_len) 
                                 << 8U)) << (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_size)) 
                      >> 8U));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__addr 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__busy)
            ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__r_addr
            : vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_addr);
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_corrupt 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata) 
           & ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_resp)) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___GEN_47)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__latch 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_todo 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter))
            ? ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_valid)
                ? 1U : 0U) : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___in_aw_ready_T)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_10 
        = (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_valid) 
            & (0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter))) 
           | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_latched));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___bundleOut_0_w_valid_T_1 
        = ((0U != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter)) 
           | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_23) 
               & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                >> 3U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                >> 4U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                >> 5U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                >> 6U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 1U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
                 [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 2U) & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
                 [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1])));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__monitor__DOT__d_first_beats1_decode 
        = (0x1ffU & (~ (0x1ffU & (((IData)(0xfffU) 
                                   << vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]) 
                                  >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__monitor__DOT__d_first_beats1_opdata 
        = (1U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode
           [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]);
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_aw_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_0)
            ? 0U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_1)
                     ? 1U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_2)
                              ? 2U : 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_0) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_1) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirects_2) 
                 | (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_valid) 
                            & ((((IData)(0xfU) << (3U 
                                                   & (IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_vpc 
                                                              >> 1U)))) 
                                >> 3U) & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_predicted_pc_valid) 
                                          & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__REG_37)
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__REG_40)
                                               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_3__DOT__REG_6_is_jal)) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_is_br) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_taken))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_out_a_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_0)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_out_a_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_1));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60 
        = (((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_3_is_br)
             : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_2_is_br)
                 : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_1_is_br)
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_0_is_br)))) 
           & (((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_3_taken)
                : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_2_taken)
                    : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_1_taken)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_0_taken)))) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_do_redirect)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__widget_auto_out_a_valid 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__beatsLeft))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_ar_valid) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_out_valid))
            : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_ar_valid) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__state_0)) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__state_1) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_out_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT___cycleNum_B_T_2 
        = (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B) 
                   - (IData)(1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cyc_C4_sqrt 
        = ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_C)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__sqrtOp_PB));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cyc_B2_sqrt 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__sqrtOp_PB));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT___io_latchMulAddA_0_T 
        = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_A)) 
           | (7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT____VdfgRegularize_hc64607eb_0_3 
        = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)) 
           | (6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_C)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_184 = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_rawOut_sig 
                                                  & VL_SHIFTR_QQI(56,56,32, 
                                                                  (3ULL 
                                                                   | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7 
                                                                      << 2U)), 1U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundPosMask 
        = ((~ VL_SHIFTR_QQI(56,56,32, (3ULL | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7 
                                               << 2U)), 1U)) 
           & (3ULL | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7 
                      << 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_20 
        = ((0ULL == (0xc8010000ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr)) 
           | (0ULL == (0xc8000000ULL & (0x8000000ULL 
                                        ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_1 
        = ((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_opcode))
            ? (7U & (~ (7U & (((IData)(0x3fU) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_size)) 
                              >> 3U)))) : 0U);
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_valid_0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_154 
            = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_requestor_0_resp_bits_homogeneous)) 
                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_valid_0)));
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_requestor_0_resp_bits_homogeneous) {
            if ((2U > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_158 
                    = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__r_superpage_repl_addr)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_0_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_162 
                    = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__r_superpage_repl_addr)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_1_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_166 
                    = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__r_superpage_repl_addr)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_2_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_170 
                    = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__r_superpage_repl_addr)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_3_valid_0));
            } else {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_158 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_0_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_162 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_1_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_166 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_2_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_170 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_3_valid_0;
            }
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_158 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_0_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_162 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_1_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_166 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_170 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_3_valid_0;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_154 
            = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__special_entry_valid_0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_158 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_0_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_162 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_1_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_166 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT___GEN_170 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__superpage_entries_3_valid_0;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_valid_1) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_requestor_0_resp_bits_homogeneous) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_455 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__special_entry_valid_0;
            if ((2U > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_459 
                    = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_467 
                    = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_471 
                    = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_valid_0));
            } else {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_459 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_467 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_471 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_valid_0;
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_486 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_286;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_493 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_293;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_494 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_294;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_495 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_295;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_546 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_346;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_455 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_32;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_459 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_467 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_471 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_486 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_493 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_494 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_495 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_546 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_455 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__special_entry_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_459 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_467 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_471 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_486 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_493 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_494 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_495 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_546 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___GEN_1150 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___r_pte_T_1)
            ? 2U : ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                     ? 0U : (3U & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count) 
                                       + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__pte_cache_hit))
                                    : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count)
                                        : ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count)
                                            : ((7U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__state))
                                                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw_io_requestor_0_resp_bits_homogeneous)
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count)
                                                    : 2U)
                                                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_in_d_valid) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_in_d_valid) 
                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_in_d_valid) 
                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_deq_valid)))))
               : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_0)) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_in_d_valid) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_1)) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_in_d_valid) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_2)) 
                        | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_in_d_valid) 
                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_3)) 
                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_deq_valid) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_4))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_pf_inst 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__bad_va) 
           | (0U != ((~ (0x2000U | ((((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mstatus_prv))
                                       ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___priv_x_ok_T))
                                       : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___priv_x_ok_T)) 
                                     & (((((0x1000U 
                                            & ((IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__special_entry_data_0 
                                                        >> 0xaU)) 
                                               << 0xcU)) 
                                           | (0x800U 
                                              & ((IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_data_0 
                                                          >> 0xaU)) 
                                                 << 0xbU))) 
                                          | ((0x400U 
                                              & ((IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_data_0 
                                                          >> 0xaU)) 
                                                 << 0xaU)) 
                                             | (0x200U 
                                                & ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_1_data_0 
                                                            >> 0xaU)) 
                                                   << 9U)))) 
                                         | ((0x100U 
                                             & ((IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_data_0 
                                                         >> 0xaU)) 
                                                << 8U)) 
                                            | ((0x80U 
                                                & ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_584 
                                                            >> 0xaU)) 
                                                   << 7U)) 
                                               | (0x40U 
                                                  & ((IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_580 
                                                              >> 0xaU)) 
                                                     << 6U))))) 
                                        | (((0x20U 
                                             & ((IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_576 
                                                         >> 0xaU)) 
                                                << 5U)) 
                                            | ((0x10U 
                                                & ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_572 
                                                            >> 0xaU)) 
                                                   << 4U)) 
                                               | (8U 
                                                  & ((IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_568 
                                                              >> 0xaU)) 
                                                     << 3U)))) 
                                           | ((4U & 
                                               ((IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_564 
                                                         >> 0xaU)) 
                                                << 2U)) 
                                              | ((2U 
                                                  & ((IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_560 
                                                              >> 0xaU)) 
                                                     << 1U)) 
                                                 | (1U 
                                                    & (IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_556 
                                                               >> 0xaU)))))))) 
                                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__ptw_ae_array)))) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__hits))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))
               ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F0_valid) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_0_valid) 
                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_0_valid)))
               : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F0_valid)) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_1) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_0_valid)) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_2) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_0_valid))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor_1__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))
               ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F1_valid) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_1_valid) 
                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_1_valid)))
               : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F1_valid)) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_1) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_1_valid)) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_2) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_1_valid))))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_v 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__res_v;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_d 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 7U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_a 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 6U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_g 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 5U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_u 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 4U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_x 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 3U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_w 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 2U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_r 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                             >> 1U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_ppn 
            = (QData)((IData)((0xfffffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__mem_resp_data 
                                                   >> 0xaU)))));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_v 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___r_pte_T_1) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT____VdfgRegularize_h25d95197_1_13)
                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_v)
                   : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___GEN_1125) 
                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_v))));
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___r_pte_T_1) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_d 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 5U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_a 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 4U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_g 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__s2_g_vec_0));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_u 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 3U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 2U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_w 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 1U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_r 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_ppn 
                = (QData)((IData)((0xfffffU & (IData)(
                                                      (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                                       >> 6U)))));
        } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT____VdfgRegularize_h25d95197_1_13) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_d 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_d));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_a 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_a));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_g 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_g));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_u 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_u));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_x 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_x));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_w 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_w));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_r 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_r));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_ppn 
                = ((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__count))
                    ? ((0x3ffffffffffe00ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_ppn) 
                       | (QData)((IData)((0x1ffU & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_req_addr))))
                    : ((0x3ffffffffc0000ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_ppn) 
                       | (QData)((IData)((0x3ffffU 
                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_req_addr)))));
        } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___GEN_1125) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_d 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 5U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_a 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 4U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_g 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__s2_g_vec_0));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_u 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 3U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 2U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_w 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1 
                                 >> 1U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_r 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_1));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_ppn 
                = (QData)((IData)(((((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_0
                                      : 0U) | ((2U 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_1
                                                : 0U)) 
                                   | ((((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_2
                                         : 0U) | ((8U 
                                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_3
                                                   : 0U)) 
                                      | (((0x10U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_4
                                           : 0U) | 
                                         (((0x20U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_5
                                            : 0U) | 
                                          (((0x40U 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                             ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_6
                                             : 0U) 
                                           | ((0x80U 
                                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__hits))
                                               ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__data_7
                                               : 0U))))))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_d 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_d));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_a 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_a));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_g 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_g));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_u 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_u));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_x 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_x));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_w 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_w));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_r 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_r));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_barrier_io_x_ppn 
                = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT___T_22)
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_satp_ppn
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_ppn);
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_miss 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_valid_1) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__tlb_miss) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__multipleHits)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_x 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
           & (((0ULL == (0xca000000ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT____VdfgRegularize_hd81bb910_0_22)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_r_T_6) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_7)
                     ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_7) 
                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_x) 
                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_7)))
                     : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_6)
                         ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_6) 
                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_x) 
                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_6)))
                         : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_5)
                             ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_5) 
                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_x) 
                                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_5)))
                             : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_4)
                                 ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_4) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_x) 
                                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_4)))
                                 : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_3)
                                     ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_3) 
                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_x) 
                                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_3)))
                                     : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_2)
                                         ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_2) 
                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_x) 
                                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_2)))
                                         : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_1)
                                             ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_1) 
                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_x) 
                                                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_1)))
                                             : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit)
                                                 ? 
                                                ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned) 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_x) 
                                                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore)))
                                                 : 
                                                (1U 
                                                 < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp_io_prv)))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___readys_mask_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__readys_filter_lo));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_mask 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_mask
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_1)
                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q__DOT__ram_mask
                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q__DOT__value_1]
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_data 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_data
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]
             : 0ULL) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_1)
                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q__DOT__ram_data
                        [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q__DOT__value_1]
                         : 0ULL));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_prot 
        = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_0) 
             & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_user_amba_prot_fetch
             [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
            << 2U) | ((2U & ((~ (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_0) 
                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_user_amba_prot_secure
                                  [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
                                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_1))) 
                             << 1U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_0) 
                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_user_amba_prot_privileged
                                         [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_2_1))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cyc_B6_div 
        = ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT____VdfgRegularize_hc64607eb_0_13));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_address 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__muxStateEarly_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__r_addr
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__muxStateEarly_1)
                       ? ((((0xcU >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_size)) 
                            & (0U == (0xfffff000U & 
                                      (0x3000U ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr)))) 
                           | (((6U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_size)) 
                               & ((0U == (0xfffff000U 
                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr)) 
                                  | ((0U == (0xffff0000U 
                                             & (0x2000000U 
                                                ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr))) 
                                     | ((0U == (0xfc000000U 
                                                & (0xc000000U 
                                                   ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr))) 
                                        | (0U == (0xf0000000U 
                                                  & (0x80000000U 
                                                     ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr))))))) 
                              | ((8U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_size)) 
                                 & (0U == (0xe0000000U 
                                           & (0x60000000U 
                                              ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr))))))
                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr
                           : (0x3000U | (7U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_bits_addr)))
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__muxStateEarly_0)
             ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_id) 
                 << 3U) | (7U & VL_SHIFTL_III(3,3,32, 
                                              ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_id)
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__r_count_1)
                                                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__r_count_0)), 1U)))
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__muxStateEarly_1)
                       ? (1U | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1_io_deq_bits_id) 
                                 << 3U) | (6U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1_io_deq_bits_id)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_count_1)
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__w_count_0)) 
                                                 << 1U))))
                       : 0U));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___out_arw_valid_T_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___bundleIn_0_a_ready_T) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_valid));
    __Vtemp_1[0U] = 1U;
    __Vtemp_1[1U] = 0U;
    __Vtemp_1[2U] = 0U;
    __Vtemp_1[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_2, __Vtemp_1, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_510 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_128) 
                 + ((__Vtemp_2[3U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_3[0U] = 1U;
    __Vtemp_3[1U] = 0U;
    __Vtemp_3[2U] = 0U;
    __Vtemp_3[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_4, __Vtemp_3, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_506 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_127) 
                 + ((__Vtemp_4[3U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_5[0U] = 1U;
    __Vtemp_5[1U] = 0U;
    __Vtemp_5[2U] = 0U;
    __Vtemp_5[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_6, __Vtemp_5, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_502 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_126) 
                 + ((__Vtemp_6[3U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_7[0U] = 1U;
    __Vtemp_7[1U] = 0U;
    __Vtemp_7[2U] = 0U;
    __Vtemp_7[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_8, __Vtemp_7, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_498 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_125) 
                 + ((__Vtemp_8[3U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_9[0U] = 1U;
    __Vtemp_9[1U] = 0U;
    __Vtemp_9[2U] = 0U;
    __Vtemp_9[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_10, __Vtemp_9, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_494 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_124) 
                 + ((__Vtemp_10[3U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_11[0U] = 1U;
    __Vtemp_11[1U] = 0U;
    __Vtemp_11[2U] = 0U;
    __Vtemp_11[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_12, __Vtemp_11, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_490 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_123) 
                 + ((__Vtemp_12[3U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_13[0U] = 1U;
    __Vtemp_13[1U] = 0U;
    __Vtemp_13[2U] = 0U;
    __Vtemp_13[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_14, __Vtemp_13, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_486 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_122) 
                 + ((__Vtemp_14[3U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_15[0U] = 1U;
    __Vtemp_15[1U] = 0U;
    __Vtemp_15[2U] = 0U;
    __Vtemp_15[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_16, __Vtemp_15, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_482 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_121) 
                 + ((__Vtemp_16[3U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_17[0U] = 1U;
    __Vtemp_17[1U] = 0U;
    __Vtemp_17[2U] = 0U;
    __Vtemp_17[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_18, __Vtemp_17, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_478 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_120) 
                 + ((__Vtemp_18[3U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_19[0U] = 1U;
    __Vtemp_19[1U] = 0U;
    __Vtemp_19[2U] = 0U;
    __Vtemp_19[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_20, __Vtemp_19, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_474 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_119) 
                 + ((__Vtemp_20[3U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_21[0U] = 1U;
    __Vtemp_21[1U] = 0U;
    __Vtemp_21[2U] = 0U;
    __Vtemp_21[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_22, __Vtemp_21, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_470 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_118) 
                 + ((__Vtemp_22[3U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_23[0U] = 1U;
    __Vtemp_23[1U] = 0U;
    __Vtemp_23[2U] = 0U;
    __Vtemp_23[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_24, __Vtemp_23, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_466 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_117) 
                 + ((__Vtemp_24[3U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_25[0U] = 1U;
    __Vtemp_25[1U] = 0U;
    __Vtemp_25[2U] = 0U;
    __Vtemp_25[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_26, __Vtemp_25, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_462 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_116) 
                 + ((__Vtemp_26[3U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_27[0U] = 1U;
    __Vtemp_27[1U] = 0U;
    __Vtemp_27[2U] = 0U;
    __Vtemp_27[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_28, __Vtemp_27, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_458 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_115) 
                 + ((__Vtemp_28[3U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_29[0U] = 1U;
    __Vtemp_29[1U] = 0U;
    __Vtemp_29[2U] = 0U;
    __Vtemp_29[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_30, __Vtemp_29, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_454 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_114) 
                 + ((__Vtemp_30[3U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_31[0U] = 1U;
    __Vtemp_31[1U] = 0U;
    __Vtemp_31[2U] = 0U;
    __Vtemp_31[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_32, __Vtemp_31, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_450 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_113) 
                 + ((__Vtemp_32[3U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_33[0U] = 1U;
    __Vtemp_33[1U] = 0U;
    __Vtemp_33[2U] = 0U;
    __Vtemp_33[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_34, __Vtemp_33, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_446 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_112) 
                 + ((__Vtemp_34[3U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_35[0U] = 1U;
    __Vtemp_35[1U] = 0U;
    __Vtemp_35[2U] = 0U;
    __Vtemp_35[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_36, __Vtemp_35, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_442 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_111) 
                 + ((__Vtemp_36[3U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_37[0U] = 1U;
    __Vtemp_37[1U] = 0U;
    __Vtemp_37[2U] = 0U;
    __Vtemp_37[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_38, __Vtemp_37, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_438 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_110) 
                 + ((__Vtemp_38[3U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_39[0U] = 1U;
    __Vtemp_39[1U] = 0U;
    __Vtemp_39[2U] = 0U;
    __Vtemp_39[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_40, __Vtemp_39, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_434 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_109) 
                 + ((__Vtemp_40[3U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_41[0U] = 1U;
    __Vtemp_41[1U] = 0U;
    __Vtemp_41[2U] = 0U;
    __Vtemp_41[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_42, __Vtemp_41, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_430 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_108) 
                 + ((__Vtemp_42[3U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_43[0U] = 1U;
    __Vtemp_43[1U] = 0U;
    __Vtemp_43[2U] = 0U;
    __Vtemp_43[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_44, __Vtemp_43, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_426 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_107) 
                 + ((__Vtemp_44[3U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_45[0U] = 1U;
    __Vtemp_45[1U] = 0U;
    __Vtemp_45[2U] = 0U;
    __Vtemp_45[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_46, __Vtemp_45, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_422 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_106) 
                 + ((__Vtemp_46[3U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_47[0U] = 1U;
    __Vtemp_47[1U] = 0U;
    __Vtemp_47[2U] = 0U;
    __Vtemp_47[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_48, __Vtemp_47, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_418 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_105) 
                 + ((__Vtemp_48[3U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_49[0U] = 1U;
    __Vtemp_49[1U] = 0U;
    __Vtemp_49[2U] = 0U;
    __Vtemp_49[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_50, __Vtemp_49, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_414 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_104) 
                 + ((__Vtemp_50[3U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_51[0U] = 1U;
    __Vtemp_51[1U] = 0U;
    __Vtemp_51[2U] = 0U;
    __Vtemp_51[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_52, __Vtemp_51, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_410 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_103) 
                 + ((__Vtemp_52[3U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_53[0U] = 1U;
    __Vtemp_53[1U] = 0U;
    __Vtemp_53[2U] = 0U;
    __Vtemp_53[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_54, __Vtemp_53, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_406 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_102) 
                 + ((__Vtemp_54[3U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_55[0U] = 1U;
    __Vtemp_55[1U] = 0U;
    __Vtemp_55[2U] = 0U;
    __Vtemp_55[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_56, __Vtemp_55, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_402 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_101) 
                 + ((__Vtemp_56[3U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_57[0U] = 1U;
    __Vtemp_57[1U] = 0U;
    __Vtemp_57[2U] = 0U;
    __Vtemp_57[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_58, __Vtemp_57, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_398 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_100) 
                 + ((__Vtemp_58[3U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_59[0U] = 1U;
    __Vtemp_59[1U] = 0U;
    __Vtemp_59[2U] = 0U;
    __Vtemp_59[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_60, __Vtemp_59, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_394 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_99) 
                 + ((__Vtemp_60[3U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_61[0U] = 1U;
    __Vtemp_61[1U] = 0U;
    __Vtemp_61[2U] = 0U;
    __Vtemp_61[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_62, __Vtemp_61, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_390 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_98) 
                 + ((__Vtemp_62[3U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_63[0U] = 1U;
    __Vtemp_63[1U] = 0U;
    __Vtemp_63[2U] = 0U;
    __Vtemp_63[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_64, __Vtemp_63, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_386 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_97) 
                 + (__Vtemp_64[3U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_65[0U] = 1U;
    __Vtemp_65[1U] = 0U;
    __Vtemp_65[2U] = 0U;
    __Vtemp_65[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_66, __Vtemp_65, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_382 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_96) 
                 + ((__Vtemp_66[2U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_67[0U] = 1U;
    __Vtemp_67[1U] = 0U;
    __Vtemp_67[2U] = 0U;
    __Vtemp_67[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_68, __Vtemp_67, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_378 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_95) 
                 + ((__Vtemp_68[2U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_69[0U] = 1U;
    __Vtemp_69[1U] = 0U;
    __Vtemp_69[2U] = 0U;
    __Vtemp_69[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_70, __Vtemp_69, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_374 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_94) 
                 + ((__Vtemp_70[2U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_71[0U] = 1U;
    __Vtemp_71[1U] = 0U;
    __Vtemp_71[2U] = 0U;
    __Vtemp_71[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_72, __Vtemp_71, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_370 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_93) 
                 + ((__Vtemp_72[2U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_73[0U] = 1U;
    __Vtemp_73[1U] = 0U;
    __Vtemp_73[2U] = 0U;
    __Vtemp_73[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_74, __Vtemp_73, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_366 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_92) 
                 + ((__Vtemp_74[2U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_75[0U] = 1U;
    __Vtemp_75[1U] = 0U;
    __Vtemp_75[2U] = 0U;
    __Vtemp_75[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_76, __Vtemp_75, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_362 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_91) 
                 + ((__Vtemp_76[2U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_77[0U] = 1U;
    __Vtemp_77[1U] = 0U;
    __Vtemp_77[2U] = 0U;
    __Vtemp_77[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_78, __Vtemp_77, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_358 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_90) 
                 + ((__Vtemp_78[2U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_79[0U] = 1U;
    __Vtemp_79[1U] = 0U;
    __Vtemp_79[2U] = 0U;
    __Vtemp_79[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_80, __Vtemp_79, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_354 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_89) 
                 + ((__Vtemp_80[2U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_81[0U] = 1U;
    __Vtemp_81[1U] = 0U;
    __Vtemp_81[2U] = 0U;
    __Vtemp_81[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_82, __Vtemp_81, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_350 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_88) 
                 + ((__Vtemp_82[2U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_83[0U] = 1U;
    __Vtemp_83[1U] = 0U;
    __Vtemp_83[2U] = 0U;
    __Vtemp_83[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_84, __Vtemp_83, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_346 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_87) 
                 + ((__Vtemp_84[2U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_85[0U] = 1U;
    __Vtemp_85[1U] = 0U;
    __Vtemp_85[2U] = 0U;
    __Vtemp_85[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_86, __Vtemp_85, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_342 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_86) 
                 + ((__Vtemp_86[2U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_87[0U] = 1U;
    __Vtemp_87[1U] = 0U;
    __Vtemp_87[2U] = 0U;
    __Vtemp_87[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_88, __Vtemp_87, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_338 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_85) 
                 + ((__Vtemp_88[2U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_89[0U] = 1U;
    __Vtemp_89[1U] = 0U;
    __Vtemp_89[2U] = 0U;
    __Vtemp_89[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_90, __Vtemp_89, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_334 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_84) 
                 + ((__Vtemp_90[2U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_91[0U] = 1U;
    __Vtemp_91[1U] = 0U;
    __Vtemp_91[2U] = 0U;
    __Vtemp_91[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_92, __Vtemp_91, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_330 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_83) 
                 + ((__Vtemp_92[2U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_93[0U] = 1U;
    __Vtemp_93[1U] = 0U;
    __Vtemp_93[2U] = 0U;
    __Vtemp_93[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_94, __Vtemp_93, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_326 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_82) 
                 + ((__Vtemp_94[2U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_95[0U] = 1U;
    __Vtemp_95[1U] = 0U;
    __Vtemp_95[2U] = 0U;
    __Vtemp_95[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_96, __Vtemp_95, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_322 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_81) 
                 + ((__Vtemp_96[2U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_97[0U] = 1U;
    __Vtemp_97[1U] = 0U;
    __Vtemp_97[2U] = 0U;
    __Vtemp_97[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_98, __Vtemp_97, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_318 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_80) 
                 + ((__Vtemp_98[2U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_99[0U] = 1U;
    __Vtemp_99[1U] = 0U;
    __Vtemp_99[2U] = 0U;
    __Vtemp_99[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_100, __Vtemp_99, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_314 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_79) 
                 + ((__Vtemp_100[2U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_101[0U] = 1U;
    __Vtemp_101[1U] = 0U;
    __Vtemp_101[2U] = 0U;
    __Vtemp_101[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_102, __Vtemp_101, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_310 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_78) 
                 + ((__Vtemp_102[2U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_103[0U] = 1U;
    __Vtemp_103[1U] = 0U;
    __Vtemp_103[2U] = 0U;
    __Vtemp_103[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_104, __Vtemp_103, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_306 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_77) 
                 + ((__Vtemp_104[2U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_105[0U] = 1U;
    __Vtemp_105[1U] = 0U;
    __Vtemp_105[2U] = 0U;
    __Vtemp_105[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_106, __Vtemp_105, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_302 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_76) 
                 + ((__Vtemp_106[2U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_107[0U] = 1U;
    __Vtemp_107[1U] = 0U;
    __Vtemp_107[2U] = 0U;
    __Vtemp_107[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_108, __Vtemp_107, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_298 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_75) 
                 + ((__Vtemp_108[2U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_109[0U] = 1U;
    __Vtemp_109[1U] = 0U;
    __Vtemp_109[2U] = 0U;
    __Vtemp_109[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_110, __Vtemp_109, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_294 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_74) 
                 + ((__Vtemp_110[2U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_111[0U] = 1U;
    __Vtemp_111[1U] = 0U;
    __Vtemp_111[2U] = 0U;
    __Vtemp_111[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_112, __Vtemp_111, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_290 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_73) 
                 + ((__Vtemp_112[2U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_113[0U] = 1U;
    __Vtemp_113[1U] = 0U;
    __Vtemp_113[2U] = 0U;
    __Vtemp_113[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_114, __Vtemp_113, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_286 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_72) 
                 + ((__Vtemp_114[2U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_115[0U] = 1U;
    __Vtemp_115[1U] = 0U;
    __Vtemp_115[2U] = 0U;
    __Vtemp_115[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_116, __Vtemp_115, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_282 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_71) 
                 + ((__Vtemp_116[2U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_117[0U] = 1U;
    __Vtemp_117[1U] = 0U;
    __Vtemp_117[2U] = 0U;
    __Vtemp_117[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_118, __Vtemp_117, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_278 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_70) 
                 + ((__Vtemp_118[2U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_119[0U] = 1U;
    __Vtemp_119[1U] = 0U;
    __Vtemp_119[2U] = 0U;
    __Vtemp_119[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_120, __Vtemp_119, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_274 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_69) 
                 + ((__Vtemp_120[2U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_121[0U] = 1U;
    __Vtemp_121[1U] = 0U;
    __Vtemp_121[2U] = 0U;
    __Vtemp_121[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_122, __Vtemp_121, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_270 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_68) 
                 + ((__Vtemp_122[2U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_123[0U] = 1U;
    __Vtemp_123[1U] = 0U;
    __Vtemp_123[2U] = 0U;
    __Vtemp_123[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_124, __Vtemp_123, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_266 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_67) 
                 + ((__Vtemp_124[2U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_125[0U] = 1U;
    __Vtemp_125[1U] = 0U;
    __Vtemp_125[2U] = 0U;
    __Vtemp_125[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_126, __Vtemp_125, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_262 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_66) 
                 + ((__Vtemp_126[2U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_127[0U] = 1U;
    __Vtemp_127[1U] = 0U;
    __Vtemp_127[2U] = 0U;
    __Vtemp_127[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_128, __Vtemp_127, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_258 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_65) 
                 + (__Vtemp_128[2U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_129[0U] = 1U;
    __Vtemp_129[1U] = 0U;
    __Vtemp_129[2U] = 0U;
    __Vtemp_129[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_130, __Vtemp_129, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_254 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_64) 
                 + ((__Vtemp_130[1U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_131[0U] = 1U;
    __Vtemp_131[1U] = 0U;
    __Vtemp_131[2U] = 0U;
    __Vtemp_131[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_132, __Vtemp_131, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_250 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_63) 
                 + ((__Vtemp_132[1U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_133[0U] = 1U;
    __Vtemp_133[1U] = 0U;
    __Vtemp_133[2U] = 0U;
    __Vtemp_133[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_134, __Vtemp_133, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_246 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_62) 
                 + ((__Vtemp_134[1U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_135[0U] = 1U;
    __Vtemp_135[1U] = 0U;
    __Vtemp_135[2U] = 0U;
    __Vtemp_135[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_136, __Vtemp_135, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_242 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_61) 
                 + ((__Vtemp_136[1U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_137[0U] = 1U;
    __Vtemp_137[1U] = 0U;
    __Vtemp_137[2U] = 0U;
    __Vtemp_137[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_138, __Vtemp_137, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_238 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_60) 
                 + ((__Vtemp_138[1U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_139[0U] = 1U;
    __Vtemp_139[1U] = 0U;
    __Vtemp_139[2U] = 0U;
    __Vtemp_139[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_140, __Vtemp_139, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_234 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_59) 
                 + ((__Vtemp_140[1U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_141[0U] = 1U;
    __Vtemp_141[1U] = 0U;
    __Vtemp_141[2U] = 0U;
    __Vtemp_141[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_142, __Vtemp_141, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_230 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_58) 
                 + ((__Vtemp_142[1U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_143[0U] = 1U;
    __Vtemp_143[1U] = 0U;
    __Vtemp_143[2U] = 0U;
    __Vtemp_143[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_144, __Vtemp_143, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_226 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_57) 
                 + ((__Vtemp_144[1U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_145[0U] = 1U;
    __Vtemp_145[1U] = 0U;
    __Vtemp_145[2U] = 0U;
    __Vtemp_145[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_146, __Vtemp_145, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_222 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_56) 
                 + ((__Vtemp_146[1U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_147[0U] = 1U;
    __Vtemp_147[1U] = 0U;
    __Vtemp_147[2U] = 0U;
    __Vtemp_147[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_148, __Vtemp_147, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_218 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_55) 
                 + ((__Vtemp_148[1U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_149[0U] = 1U;
    __Vtemp_149[1U] = 0U;
    __Vtemp_149[2U] = 0U;
    __Vtemp_149[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_150, __Vtemp_149, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_214 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_54) 
                 + ((__Vtemp_150[1U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_151[0U] = 1U;
    __Vtemp_151[1U] = 0U;
    __Vtemp_151[2U] = 0U;
    __Vtemp_151[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_152, __Vtemp_151, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_210 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_53) 
                 + ((__Vtemp_152[1U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_153[0U] = 1U;
    __Vtemp_153[1U] = 0U;
    __Vtemp_153[2U] = 0U;
    __Vtemp_153[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_154, __Vtemp_153, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_206 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_52) 
                 + ((__Vtemp_154[1U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_155[0U] = 1U;
    __Vtemp_155[1U] = 0U;
    __Vtemp_155[2U] = 0U;
    __Vtemp_155[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_156, __Vtemp_155, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_202 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_51) 
                 + ((__Vtemp_156[1U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_157[0U] = 1U;
    __Vtemp_157[1U] = 0U;
    __Vtemp_157[2U] = 0U;
    __Vtemp_157[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_158, __Vtemp_157, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_198 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_50) 
                 + ((__Vtemp_158[1U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_159[0U] = 1U;
    __Vtemp_159[1U] = 0U;
    __Vtemp_159[2U] = 0U;
    __Vtemp_159[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_160, __Vtemp_159, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_194 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_49) 
                 + ((__Vtemp_160[1U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_161[0U] = 1U;
    __Vtemp_161[1U] = 0U;
    __Vtemp_161[2U] = 0U;
    __Vtemp_161[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_162, __Vtemp_161, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_190 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_48) 
                 + ((__Vtemp_162[1U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_163[0U] = 1U;
    __Vtemp_163[1U] = 0U;
    __Vtemp_163[2U] = 0U;
    __Vtemp_163[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_164, __Vtemp_163, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_186 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_47) 
                 + ((__Vtemp_164[1U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_165[0U] = 1U;
    __Vtemp_165[1U] = 0U;
    __Vtemp_165[2U] = 0U;
    __Vtemp_165[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_166, __Vtemp_165, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_182 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_46) 
                 + ((__Vtemp_166[1U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_167[0U] = 1U;
    __Vtemp_167[1U] = 0U;
    __Vtemp_167[2U] = 0U;
    __Vtemp_167[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_168, __Vtemp_167, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_178 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_45) 
                 + ((__Vtemp_168[1U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_169[0U] = 1U;
    __Vtemp_169[1U] = 0U;
    __Vtemp_169[2U] = 0U;
    __Vtemp_169[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_170, __Vtemp_169, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_174 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_44) 
                 + ((__Vtemp_170[1U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_171[0U] = 1U;
    __Vtemp_171[1U] = 0U;
    __Vtemp_171[2U] = 0U;
    __Vtemp_171[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_172, __Vtemp_171, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_170 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_43) 
                 + ((__Vtemp_172[1U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_173[0U] = 1U;
    __Vtemp_173[1U] = 0U;
    __Vtemp_173[2U] = 0U;
    __Vtemp_173[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_174, __Vtemp_173, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_166 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_42) 
                 + ((__Vtemp_174[1U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_175[0U] = 1U;
    __Vtemp_175[1U] = 0U;
    __Vtemp_175[2U] = 0U;
    __Vtemp_175[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_176, __Vtemp_175, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_162 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_41) 
                 + ((__Vtemp_176[1U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_177[0U] = 1U;
    __Vtemp_177[1U] = 0U;
    __Vtemp_177[2U] = 0U;
    __Vtemp_177[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_178, __Vtemp_177, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_158 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_40) 
                 + ((__Vtemp_178[1U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_179[0U] = 1U;
    __Vtemp_179[1U] = 0U;
    __Vtemp_179[2U] = 0U;
    __Vtemp_179[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_180, __Vtemp_179, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_154 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_39) 
                 + ((__Vtemp_180[1U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_181[0U] = 1U;
    __Vtemp_181[1U] = 0U;
    __Vtemp_181[2U] = 0U;
    __Vtemp_181[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_182, __Vtemp_181, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_150 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_38) 
                 + ((__Vtemp_182[1U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_183[0U] = 1U;
    __Vtemp_183[1U] = 0U;
    __Vtemp_183[2U] = 0U;
    __Vtemp_183[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_184, __Vtemp_183, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_146 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_37) 
                 + ((__Vtemp_184[1U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_185[0U] = 1U;
    __Vtemp_185[1U] = 0U;
    __Vtemp_185[2U] = 0U;
    __Vtemp_185[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_186, __Vtemp_185, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_142 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_36) 
                 + ((__Vtemp_186[1U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_187[0U] = 1U;
    __Vtemp_187[1U] = 0U;
    __Vtemp_187[2U] = 0U;
    __Vtemp_187[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_188, __Vtemp_187, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_138 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_35) 
                 + ((__Vtemp_188[1U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_189[0U] = 1U;
    __Vtemp_189[1U] = 0U;
    __Vtemp_189[2U] = 0U;
    __Vtemp_189[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_190, __Vtemp_189, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_134 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_34) 
                 + ((__Vtemp_190[1U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_191[0U] = 1U;
    __Vtemp_191[1U] = 0U;
    __Vtemp_191[2U] = 0U;
    __Vtemp_191[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_192, __Vtemp_191, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_130 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_33) 
                 + (__Vtemp_192[1U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_193[0U] = 1U;
    __Vtemp_193[1U] = 0U;
    __Vtemp_193[2U] = 0U;
    __Vtemp_193[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_194, __Vtemp_193, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_126 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_32) 
                 + ((__Vtemp_194[0U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_195[0U] = 1U;
    __Vtemp_195[1U] = 0U;
    __Vtemp_195[2U] = 0U;
    __Vtemp_195[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_196, __Vtemp_195, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_122 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_31) 
                 + ((__Vtemp_196[0U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_197[0U] = 1U;
    __Vtemp_197[1U] = 0U;
    __Vtemp_197[2U] = 0U;
    __Vtemp_197[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_198, __Vtemp_197, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_118 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_30) 
                 + ((__Vtemp_198[0U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_199[0U] = 1U;
    __Vtemp_199[1U] = 0U;
    __Vtemp_199[2U] = 0U;
    __Vtemp_199[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_200, __Vtemp_199, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_114 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_29) 
                 + ((__Vtemp_200[0U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_201[0U] = 1U;
    __Vtemp_201[1U] = 0U;
    __Vtemp_201[2U] = 0U;
    __Vtemp_201[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_202, __Vtemp_201, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_110 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_28) 
                 + ((__Vtemp_202[0U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_203[0U] = 1U;
    __Vtemp_203[1U] = 0U;
    __Vtemp_203[2U] = 0U;
    __Vtemp_203[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_204, __Vtemp_203, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_106 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_27) 
                 + ((__Vtemp_204[0U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_205[0U] = 1U;
    __Vtemp_205[1U] = 0U;
    __Vtemp_205[2U] = 0U;
    __Vtemp_205[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_206, __Vtemp_205, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_102 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_26) 
                 + ((__Vtemp_206[0U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_207[0U] = 1U;
    __Vtemp_207[1U] = 0U;
    __Vtemp_207[2U] = 0U;
    __Vtemp_207[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_208, __Vtemp_207, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_98 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_25) 
                 + ((__Vtemp_208[0U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_209[0U] = 1U;
    __Vtemp_209[1U] = 0U;
    __Vtemp_209[2U] = 0U;
    __Vtemp_209[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_210, __Vtemp_209, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_94 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_24) 
                 + ((__Vtemp_210[0U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_211[0U] = 1U;
    __Vtemp_211[1U] = 0U;
    __Vtemp_211[2U] = 0U;
    __Vtemp_211[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_212, __Vtemp_211, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_90 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_23) 
                 + ((__Vtemp_212[0U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_213[0U] = 1U;
    __Vtemp_213[1U] = 0U;
    __Vtemp_213[2U] = 0U;
    __Vtemp_213[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_214, __Vtemp_213, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_86 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_22) 
                 + ((__Vtemp_214[0U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_215[0U] = 1U;
    __Vtemp_215[1U] = 0U;
    __Vtemp_215[2U] = 0U;
    __Vtemp_215[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_216, __Vtemp_215, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_82 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_21) 
                 + ((__Vtemp_216[0U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_217[0U] = 1U;
    __Vtemp_217[1U] = 0U;
    __Vtemp_217[2U] = 0U;
    __Vtemp_217[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_218, __Vtemp_217, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_78 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_20) 
                 + ((__Vtemp_218[0U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_219[0U] = 1U;
    __Vtemp_219[1U] = 0U;
    __Vtemp_219[2U] = 0U;
    __Vtemp_219[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_220, __Vtemp_219, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_74 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_19) 
                 + ((__Vtemp_220[0U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_221[0U] = 1U;
    __Vtemp_221[1U] = 0U;
    __Vtemp_221[2U] = 0U;
    __Vtemp_221[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_222, __Vtemp_221, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_70 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_18) 
                 + ((__Vtemp_222[0U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_223[0U] = 1U;
    __Vtemp_223[1U] = 0U;
    __Vtemp_223[2U] = 0U;
    __Vtemp_223[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_224, __Vtemp_223, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_66 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_17) 
                 + ((__Vtemp_224[0U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_225[0U] = 1U;
    __Vtemp_225[1U] = 0U;
    __Vtemp_225[2U] = 0U;
    __Vtemp_225[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_226, __Vtemp_225, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_62 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_16) 
                 + ((__Vtemp_226[0U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_227[0U] = 1U;
    __Vtemp_227[1U] = 0U;
    __Vtemp_227[2U] = 0U;
    __Vtemp_227[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_228, __Vtemp_227, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_58 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_15) 
                 + ((__Vtemp_228[0U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_229[0U] = 1U;
    __Vtemp_229[1U] = 0U;
    __Vtemp_229[2U] = 0U;
    __Vtemp_229[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_230, __Vtemp_229, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_54 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_14) 
                 + ((__Vtemp_230[0U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_231[0U] = 1U;
    __Vtemp_231[1U] = 0U;
    __Vtemp_231[2U] = 0U;
    __Vtemp_231[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_232, __Vtemp_231, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_50 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_13) 
                 + ((__Vtemp_232[0U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_233[0U] = 1U;
    __Vtemp_233[1U] = 0U;
    __Vtemp_233[2U] = 0U;
    __Vtemp_233[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_234, __Vtemp_233, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_46 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_12) 
                 + ((__Vtemp_234[0U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_235[0U] = 1U;
    __Vtemp_235[1U] = 0U;
    __Vtemp_235[2U] = 0U;
    __Vtemp_235[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_236, __Vtemp_235, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_42 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_11) 
                 + ((__Vtemp_236[0U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_237[0U] = 1U;
    __Vtemp_237[1U] = 0U;
    __Vtemp_237[2U] = 0U;
    __Vtemp_237[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_238, __Vtemp_237, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_38 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_10) 
                 + ((__Vtemp_238[0U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_239[0U] = 1U;
    __Vtemp_239[1U] = 0U;
    __Vtemp_239[2U] = 0U;
    __Vtemp_239[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_240, __Vtemp_239, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_34 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_9) 
                 + ((__Vtemp_240[0U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_241[0U] = 1U;
    __Vtemp_241[1U] = 0U;
    __Vtemp_241[2U] = 0U;
    __Vtemp_241[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_242, __Vtemp_241, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_30 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_8) 
                 + ((__Vtemp_242[0U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_243[0U] = 1U;
    __Vtemp_243[1U] = 0U;
    __Vtemp_243[2U] = 0U;
    __Vtemp_243[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_244, __Vtemp_243, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_26 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_7) 
                 + ((__Vtemp_244[0U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_245[0U] = 1U;
    __Vtemp_245[1U] = 0U;
    __Vtemp_245[2U] = 0U;
    __Vtemp_245[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_246, __Vtemp_245, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_22 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_6) 
                 + ((__Vtemp_246[0U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_247[0U] = 1U;
    __Vtemp_247[1U] = 0U;
    __Vtemp_247[2U] = 0U;
    __Vtemp_247[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_248, __Vtemp_247, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_18 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_5) 
                 + ((__Vtemp_248[0U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_249[0U] = 1U;
    __Vtemp_249[1U] = 0U;
    __Vtemp_249[2U] = 0U;
    __Vtemp_249[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_250, __Vtemp_249, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_14 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_4) 
                 + ((__Vtemp_250[0U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_251[0U] = 1U;
    __Vtemp_251[1U] = 0U;
    __Vtemp_251[2U] = 0U;
    __Vtemp_251[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_252, __Vtemp_251, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_10 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_3) 
                 + ((__Vtemp_252[0U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    __Vtemp_253[0U] = 1U;
    __Vtemp_253[1U] = 0U;
    __Vtemp_253[2U] = 0U;
    __Vtemp_253[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_254, __Vtemp_253, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_6 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_2) 
                 + ((__Vtemp_254[0U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_3));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_4));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestDOI_0_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
               & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))
                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3)
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0)))) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestDOI_0_1) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4)
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
              & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys)
                  : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_0))));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
                  >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_1)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_out_b_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_1 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___T_1)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_1 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___T_1)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___GEN_46 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__r_first));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
              & ((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 7U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size_MPORT_en 
        = (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 8U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 9U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xaU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xbU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size_MPORT_en 
        = (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12_io_enq_ready) 
                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                      & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                         >> 0xcU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size_MPORT_en 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13_io_enq_ready) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xdU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size_MPORT_en 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14_io_enq_ready) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xeU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15_io_enq_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0)) 
           & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
              >> 0xfU));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
              & ((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19_io_enq_ready) 
                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size_MPORT_en 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23_io_enq_ready) 
                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 7U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size_MPORT_en 
        = (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 8U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 9U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xaU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27_io_enq_ready) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xbU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__ram_tl_state_size_MPORT_en 
        = (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28_io_enq_ready) 
                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                      & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                         >> 0xcU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__ram_tl_state_size_MPORT_en 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29_io_enq_ready) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xdU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__ram_tl_state_size_MPORT_en 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30_io_enq_ready) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xeU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__ram_tl_state_size_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31_io_enq_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0)) 
           & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
              >> 0xfU));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_sink 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__out_2_0_d_bits_sink)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_sink)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_sink 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__out_2_0_d_bits_sink)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_sink)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_param 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_param)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_param 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_param)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___GEN_19 
        = (1U & (((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_428)) 
                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T) 
                     >> 1U)) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___T_1)
                                 ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_90)
                                 : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__got_e))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___GEN_19 
        = (1U & (((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_428)) 
                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T) 
                     >> 2U)) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___T_1)
                                 ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_90)
                                 : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__got_e))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_19 
        = (1U & (((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_428)) 
                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T) 
                     >> 3U)) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___T_1)
                                 ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_90)
                                 : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__got_e))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_opcode 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_opcode)
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_opcode)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2)
                                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)
                                      ? 1U : 0U) : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_denied 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_denied)) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_denied)) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_denied))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_denied 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_denied)) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_denied)) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_denied))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_19 
        = (1U & (((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_428)) 
                  & ((IData)(1U) << vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_e_q__DOT__ram_sink
                     [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_e_q__DOT__value_1])) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___T_1)
                     ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_90)
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__got_e))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_size)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2)
                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_size)
                                  : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_size)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2)
                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_size)
                                  : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_source 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source
                    [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
                     : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_source)
                                : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2)
                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_source)
                                          : 0U))));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_556 = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
                                                    ? 
                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source
                                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
                                                    : 0U) 
                                                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_source)
                                                       : 0U) 
                                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2)
                                                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_source)
                                                         : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_opcode)
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_opcode)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2)
                                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)
                                      ? 1U : 0U) : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready 
        = (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready 
        = (0x7fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready 
        = (0x3fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready 
        = (0x1fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready 
        = (0xfffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                      >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5_io_deq_ready 
        = (0x7ffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                      >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6_io_deq_ready 
        = (0x3ffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                      >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater__DOT___T_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_deq_valid));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_param 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_sink 
            = (1U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]);
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_denied 
            = (1U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]);
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_param = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_sink = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_denied = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_1)
                         ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_in_d_bits_size)
                         : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_2)
                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_in_d_bits_size)
                                   : 0U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_3)
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_in_d_bits_size)
                                               : 0U) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_4)
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter_auto_in_d_bits_size)
                                                 : 0U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_source 
        = (0x1fU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0)
                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source
                     [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
                      : 0U) | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_1)
                                  ? (vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_extra_tlrr_extra_source
                                     [0U] >> 4U) : 0U) 
                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_2)
                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_deq_bits_source)
                                    : 0U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_3)
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_deq_bits_source)
                                                : 0U) 
                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_4)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_deq_bits_source)
                                                  : 0U)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_opcode 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_1)
                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_read
                        [0U] : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_2)
                                       ? (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_deq_bits_opcode))
                                       : 0U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_3)
                                                   ? 
                                                  (4U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_deq_bits_opcode))
                                                   : 0U) 
                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_4)
                                                     ? 1U
                                                     : 0U))));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_255, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_104 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_255[3U] >> 0xeU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_256, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_200 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_256[3U] >> 0xaU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_257, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_410 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_257[3U] >> 0xdU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_258, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_491 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_258[3U] >> 9U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_259, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_731 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_259[3U] >> 0xcU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_260, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_811 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_260[3U] >> 0x10U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_261, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_931 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_261[3U] >> 8U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_262, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_1067 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_262[3U] >> 0xbU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_2_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_3_a_valid));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_263, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_294) 
            & (__Vtemp_263[1U] >> 1U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_0)) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
              | (((0U == (0xa010000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_42)) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_3) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_4) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_enq_ready))))));
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_10) 
                 & (IData)(((0x3ff8U == (0x3ff8U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address)) 
                            & (((IData)(1U) << (3U 
                                                & (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address 
                                                   >> 0xeU))) 
                               >> 2U)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_18 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
            & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_527)) 
           | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___T_1)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__sent_d)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_18 
        = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
             >> 3U) & (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_527)) 
           | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___T_1)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__sent_d)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___T_2) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_data 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0)
             ? ((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_opcode))
                 ? (((QData)((IData)(((((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                            >> ((2U 
                                                 & ((IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                             >> 0x3fU)) 
                                                    << 1U)) 
                                                | (1U 
                                                   & (IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                              >> 0x3fU))))) 
                                           << 0x1fU) 
                                          | (0x40000000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                 >> 
                                                 ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                               >> 0x3eU)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                >> 0x3eU))))) 
                                                << 0x1eU))) 
                                         | ((0x20000000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                 >> 
                                                 ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                               >> 0x3dU)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                >> 0x3dU))))) 
                                                << 0x1dU)) 
                                            | (0x10000000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x3cU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x3cU))))) 
                                                  << 0x1cU)))) 
                                        | (((0x8000000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                 >> 
                                                 ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                               >> 0x3bU)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                >> 0x3bU))))) 
                                                << 0x1bU)) 
                                            | (0x4000000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x3aU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x3aU))))) 
                                                  << 0x1aU))) 
                                           | ((0x2000000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x39U)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x39U))))) 
                                                  << 0x19U)) 
                                              | (0x1000000U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x38U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x38U))))) 
                                                    << 0x18U))))) 
                                       | ((((0x800000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                 >> 
                                                 ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                               >> 0x37U)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                >> 0x37U))))) 
                                                << 0x17U)) 
                                            | (0x400000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x36U)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x36U))))) 
                                                  << 0x16U))) 
                                           | ((0x200000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x35U)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x35U))))) 
                                                  << 0x15U)) 
                                              | (0x100000U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x34U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x34U))))) 
                                                    << 0x14U)))) 
                                          | (((0x80000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x33U)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x33U))))) 
                                                  << 0x13U)) 
                                              | (0x40000U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x32U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x32U))))) 
                                                    << 0x12U))) 
                                             | ((0x20000U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x31U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x31U))))) 
                                                    << 0x11U)) 
                                                | (0x10000U 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                       >> 
                                                       ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                     >> 0x30U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                      >> 0x30U))))) 
                                                      << 0x10U)))))) 
                                      | (((((0x8000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                 >> 
                                                 ((2U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                               >> 0x2fU)) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                >> 0x2fU))))) 
                                                << 0xfU)) 
                                            | (0x4000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x2eU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x2eU))))) 
                                                  << 0xeU))) 
                                           | ((0x2000U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x2dU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x2dU))))) 
                                                  << 0xdU)) 
                                              | (0x1000U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x2cU)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x2cU))))) 
                                                    << 0xcU)))) 
                                          | (((0x800U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x2bU)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x2bU))))) 
                                                  << 0xbU)) 
                                              | (0x400U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x2aU)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x2aU))))) 
                                                    << 0xaU))) 
                                             | ((0x200U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x29U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x29U))))) 
                                                    << 9U)) 
                                                | (0x100U 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                       >> 
                                                       ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                     >> 0x28U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                      >> 0x28U))))) 
                                                      << 8U))))) 
                                         | ((((0x80U 
                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                   >> 
                                                   ((2U 
                                                     & ((IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                 >> 0x27U)) 
                                                        << 1U)) 
                                                    | (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                  >> 0x27U))))) 
                                                  << 7U)) 
                                              | (0x40U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x26U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x26U))))) 
                                                    << 6U))) 
                                             | ((0x20U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x25U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x25U))))) 
                                                    << 5U)) 
                                                | (0x10U 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                       >> 
                                                       ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                     >> 0x24U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                      >> 0x24U))))) 
                                                      << 4U)))) 
                                            | (((8U 
                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                     >> 
                                                     ((2U 
                                                       & ((IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                   >> 0x23U)) 
                                                          << 1U)) 
                                                      | (1U 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                    >> 0x23U))))) 
                                                    << 3U)) 
                                                | (4U 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                       >> 
                                                       ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                     >> 0x22U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                      >> 0x22U))))) 
                                                      << 2U))) 
                                               | ((2U 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                       >> 
                                                       ((2U 
                                                         & ((IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                     >> 0x21U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                      >> 0x21U))))) 
                                                      << 1U)) 
                                                  | (1U 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                        >> 
                                                        ((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                      >> 0x20U)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                       >> 0x20U))))))))))))) 
                     << 0x20U) | (QData)((IData)(((
                                                   ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                        >> 
                                                        ((2U 
                                                          & ((IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                      >> 0x1fU)) 
                                                             << 1U)) 
                                                         | (1U 
                                                            & (IData)(
                                                                      (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                       >> 0x1fU))))) 
                                                       << 0x1fU) 
                                                      | (0x40000000U 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                             >> 
                                                             ((2U 
                                                               & ((IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                           >> 0x1eU)) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                            >> 0x1eU))))) 
                                                            << 0x1eU))) 
                                                     | ((0x20000000U 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                             >> 
                                                             ((2U 
                                                               & ((IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                           >> 0x1dU)) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                            >> 0x1dU))))) 
                                                            << 0x1dU)) 
                                                        | (0x10000000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x1cU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x1cU))))) 
                                                              << 0x1cU)))) 
                                                    | (((0x8000000U 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                             >> 
                                                             ((2U 
                                                               & ((IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                           >> 0x1bU)) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                            >> 0x1bU))))) 
                                                            << 0x1bU)) 
                                                        | (0x4000000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x1aU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x1aU))))) 
                                                              << 0x1aU))) 
                                                       | ((0x2000000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x19U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x19U))))) 
                                                              << 0x19U)) 
                                                          | (0x1000000U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0x18U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0x18U))))) 
                                                                << 0x18U))))) 
                                                   | ((((0x800000U 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                             >> 
                                                             ((2U 
                                                               & ((IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                           >> 0x17U)) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                            >> 0x17U))))) 
                                                            << 0x17U)) 
                                                        | (0x400000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x16U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x16U))))) 
                                                              << 0x16U))) 
                                                       | ((0x200000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x15U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x15U))))) 
                                                              << 0x15U)) 
                                                          | (0x100000U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0x14U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0x14U))))) 
                                                                << 0x14U)))) 
                                                      | (((0x80000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0x13U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0x13U))))) 
                                                              << 0x13U)) 
                                                          | (0x40000U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0x12U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0x12U))))) 
                                                                << 0x12U))) 
                                                         | ((0x20000U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0x11U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0x11U))))) 
                                                                << 0x11U)) 
                                                            | (0x10000U 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                   >> 
                                                                   ((2U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                                >> 0x10U)) 
                                                                        << 1U)) 
                                                                    | (1U 
                                                                       & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0x10U))))) 
                                                                  << 0x10U)))))) 
                                                  | (((((0x8000U 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                             >> 
                                                             ((2U 
                                                               & ((IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                           >> 0xfU)) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                            >> 0xfU))))) 
                                                            << 0xfU)) 
                                                        | (0x4000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0xeU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0xeU))))) 
                                                              << 0xeU))) 
                                                       | ((0x2000U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0xdU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0xdU))))) 
                                                              << 0xdU)) 
                                                          | (0x1000U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0xcU)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0xcU))))) 
                                                                << 0xcU)))) 
                                                      | (((0x800U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 0xbU)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 0xbU))))) 
                                                              << 0xbU)) 
                                                          | (0x400U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 0xaU)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 0xaU))))) 
                                                                << 0xaU))) 
                                                         | ((0x200U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 9U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 9U))))) 
                                                                << 9U)) 
                                                            | (0x100U 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                   >> 
                                                                   ((2U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                                >> 8U)) 
                                                                        << 1U)) 
                                                                    | (1U 
                                                                       & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 8U))))) 
                                                                  << 8U))))) 
                                                     | ((((0x80U 
                                                           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                               >> 
                                                               ((2U 
                                                                 & ((IData)(
                                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                             >> 7U)) 
                                                                    << 1U)) 
                                                                | (1U 
                                                                   & (IData)(
                                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                              >> 7U))))) 
                                                              << 7U)) 
                                                          | (0x40U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 6U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 6U))))) 
                                                                << 6U))) 
                                                         | ((0x20U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 5U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 5U))))) 
                                                                << 5U)) 
                                                            | (0x10U 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                   >> 
                                                                   ((2U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                                >> 4U)) 
                                                                        << 1U)) 
                                                                    | (1U 
                                                                       & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 4U))))) 
                                                                  << 4U)))) 
                                                        | (((8U 
                                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                 >> 
                                                                 ((2U 
                                                                   & ((IData)(
                                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                               >> 3U)) 
                                                                      << 1U)) 
                                                                  | (1U 
                                                                     & (IData)(
                                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 3U))))) 
                                                                << 3U)) 
                                                            | (4U 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                   >> 
                                                                   ((2U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                                >> 2U)) 
                                                                        << 1U)) 
                                                                    | (1U 
                                                                       & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 2U))))) 
                                                                  << 2U))) 
                                                           | ((2U 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                   >> 
                                                                   ((2U 
                                                                     & ((IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data 
                                                                                >> 1U)) 
                                                                        << 1U)) 
                                                                    | (1U 
                                                                       & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data 
                                                                                >> 1U))))) 
                                                                  << 1U)) 
                                                              | (1U 
                                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_lut) 
                                                                    >> 
                                                                    ((2U 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data) 
                                                                         << 1U)) 
                                                                     | (1U 
                                                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data)))))))))))))
                 : ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_param))
                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__adder_out
                     : (((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_param)) 
                         == (1U & (((1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_a_ext 
                                                   >> 0x3fU))) 
                                    == (1U & (IData)(
                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_d_ext 
                                                      >> 0x3fU))))
                                    ? (~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__adder_out 
                                                  >> 0x3fU)))
                                    : ((1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_param) 
                                              >> 1U)) 
                                       == (1U & (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_a_ext 
                                                         >> 0x3fU)))))))
                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_data
                         : vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_d_0_data)))
             : 0ULL) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1)
                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_data
                         : 0ULL));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestAIO_0_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready) 
               & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft))
                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys)
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state___05F0)))) 
           | (((0U == (0xc0000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0)) 
               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_a_ready) 
                  & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_1))
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_1)
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_1_0)))) 
              | ((0U == (0xc0000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_1)) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready) 
                    & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_2))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_2)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_2_0))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_3 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_5 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_6 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_6));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_7 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_7));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 4U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 5U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 6U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 7U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 8U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 9U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xaU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xbU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xcU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xdU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xeU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xfU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(1U) << vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id
                 [vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1])));
    if (vlSelfRef.reset) {
        __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) {
            __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en;
        }
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_full 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___GEN_41));
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___T_14) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_echo_real_last 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_qos 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_qos
            [0U];
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst = 1U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_qos = 0U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___T_14) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_id 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ptr_match 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value) 
           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__maybe_full) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__do_deq 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last)) 
            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
               & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__counter)) 
                  | (0U == ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__monitor__DOT__d_first_beats1_opdata)
                             ? (0x1ffU & (~ (0x1ffU 
                                             & (((IData)(0xfffU) 
                                                 << 
                                                 vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_size
                                                 [0U]) 
                                                >> 3U))))
                             : 0U))))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79))
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15)));
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams_auto_in_ar_ready) 
         & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_deq_valid))) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5_rdata_MPORT_addr_pipe_0 
            = (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_hi) 
                << 4U) | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_lo));
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6_rdata_MPORT_addr_pipe_0 
            = (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_hi) 
                << 4U) | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_lo));
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7_rdata_MPORT_addr_pipe_0 
            = (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_hi) 
                << 4U) | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_lo));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___GEN_28 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_1_0)
                       ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1
                          [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_1_MPORT_addr_pipe_0] 
                          >> 1U) : (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1
                                    [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_1_MPORT_1_addr_pipe_0] 
                                    >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___GEN_46 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hit_ohs_2_0)
                       ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2
                          [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_0_2_MPORT_addr_pipe_0] 
                          >> 1U) : (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2
                                    [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__btb_1_2_MPORT_1_addr_pipe_0] 
                                    >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_0_MPORT_5_mask 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wmeta_mask)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_1_MPORT_5_mask 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wmeta_mask) 
                    >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_2_MPORT_5_mask 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wmeta_mask) 
                    >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__meta_0_3_MPORT_5_mask 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_update_wmeta_mask) 
              >> 3U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_0_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT____VdfgRegularize_hbb64a946_10_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_1_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT____VdfgRegularize_hbb64a946_10_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_2_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT____VdfgRegularize_hbb64a946_10_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_3_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT____VdfgRegularize_hbb64a946_10_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_hits_3));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__inc_addr 
        = (0x7fffffffU & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__addr 
                          + (0xffffU & ((IData)(1U) 
                                        << (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_size)))));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___bundleOut_0_w_valid_T_1)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___bundleOut_0_w_valid_T_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__monitor__DOT__d_first_beats1_opdata 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__d_replace) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__monitor__DOT__d_first_beats1_opdata));
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT___do_enq_T;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_ready)) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT___do_enq_T));
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__do_deq = 0U;
    }
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153 
        = (((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_is_br)
             : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_2_is_br)
                 : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_1_is_br)
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_0_is_br)))) 
           & (((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_taken)
                : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_2_taken)
                    : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_1_taken)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_0_taken)))) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_target 
        = (0xffffffffffULL & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect)
                               ? ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_predicted_pc_bits
                                   : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_2_predicted_pc_bits
                                       : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))
                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_1_predicted_pc_bits
                                           : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_0_predicted_pc_bits)))
                               : (8ULL + (~ (7ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_vpc))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT___T_2 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full) 
              | (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_enq_ready) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_183 = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_rawOut_sig 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundPosMask);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_al 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_20));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_31 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_20) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT____VdfgRegularize_hd81bb910_0_22)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_636 
        = ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___sector_hits_T_9 
                                 >> 2U))) ? ((3U != 
                                              (3U & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                                             >> 0xcU)))) 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_486))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_486));
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___sector_hits_T_15 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_661 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_493));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_662 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_494));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_663 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_495));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_661 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_493;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_662 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_494;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_663 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_495;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_804 
        = ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___sector_hits_T_45 
                                 >> 2U))) ? ((3U != 
                                              (3U & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                                             >> 0xcU)))) 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_546))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_546));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___beatsLeft_T_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__monitor__DOT___d_first_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_22 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor__DOT___d_first_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_28 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor_1__DOT___d_first_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_18 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_is_replay)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_miss))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_prot 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_prot
           [0U] : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_prot));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_ae_inst 
        = (0U != ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__ptw_ae_array)) 
                      & ((((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_x)
                              ? 3U : 0U) << 0xcU) | 
                           ((0x800U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_3_data_0 
                                                >> 7U)) 
                                       << 0xbU)) | 
                            (0x400U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_2_data_0 
                                                >> 7U)) 
                                       << 0xaU)))) 
                          | ((0x200U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_1_data_0 
                                                 >> 7U)) 
                                        << 9U)) | (
                                                   (0x100U 
                                                    & ((IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__superpage_entries_0_data_0 
                                                                >> 7U)) 
                                                       << 8U)) 
                                                   | (0x80U 
                                                      & ((IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_584 
                                                                  >> 7U)) 
                                                         << 7U))))) 
                         | ((((0x40U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_580 
                                                 >> 7U)) 
                                        << 6U)) | (0x20U 
                                                   & ((IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_576 
                                                               >> 7U)) 
                                                      << 5U))) 
                             | ((0x10U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_572 
                                                   >> 7U)) 
                                          << 4U)) | 
                                (8U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_568 
                                                >> 7U)) 
                                       << 3U)))) | 
                            ((4U & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_564 
                                             >> 7U)) 
                                    << 2U)) | ((2U 
                                                & ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_560 
                                                            >> 7U)) 
                                                   << 1U)) 
                                               | (1U 
                                                  & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_556 
                                                             >> 7U))))))))) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__hits)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_latchMulAddA_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT___io_latchMulAddA_0_T) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cyc_B6_div) 
              | (((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)) 
                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT____VdfgRegularize_hc64607eb_0_3)) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT____VdfgRegularize_hc64607eb_0_5))));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___bundleIn_0_a_ready_T 
        = (1U & (~ (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source) 
                         >> 3U)) & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__a_first_counter)) 
                                    & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_0) 
                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_1) 
                                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_2) 
                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_3) 
                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_4) 
                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_5) 
                                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_6) 
                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_7)))))))) 
                                       & ((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_address 
                                           >> 0x1fU) 
                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__stalls_id) 
                                             != (0U 
                                                 == 
                                                 (0x80000000U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_address))))))) 
                    | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source) 
                        >> 3U) & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__a_first_counter)) 
                                  & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_8) 
                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_9) 
                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_10) 
                                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_11) 
                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_12) 
                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_13) 
                                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_14) 
                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_15)))))))) 
                                     & ((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_address 
                                         >> 0x1fU) 
                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__stalls_id_1) 
                                           != (0U == 
                                               (0x80000000U 
                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_address))))))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___out_arw_valid_T_1) 
           & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                  >> 2U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___bundleIn_0_a_ready_T_1)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___out_arw_valid_T_1) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
               >> 2U) | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__doneAW)) 
                         & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_18 
        = (7U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15) 
                 | VL_SHIFTL_III(3,3,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15), 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_26 
        = (7U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23) 
                 | VL_SHIFTL_III(3,3,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23), 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__d_drop)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT___T_7 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__drop)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_16 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT___d_first_T));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_out_b_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter)) 
           & (6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count) 
                    + ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_23) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_1 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_1) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_2 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_2) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_3 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_3) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_4 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_4) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_5 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_5) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_5_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6__DOT__ptr_match))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_6 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_6) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22))) 
                   - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_6_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__d_first 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__d_first_counter)) 
           & (6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_opcode)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater__DOT___GEN_0 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__monitor__DOT___a_first_T) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_repeat)) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater__DOT__full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater__DOT___GEN_0 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__monitor__DOT___a_first_T) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_repeat)) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater__DOT__full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_449 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_449));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_448 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_448));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q_io_deq_valid) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___bundleIn_0_a_ready_T) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_8 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_9 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_10 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_11 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_12 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_13 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_14 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_6));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_15 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_7));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_a_valid) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___bundleIn_0_a_ready_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT___timecmp_0_T 
        = (((QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_7)
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_6)
                                 : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                            >> 0x38U))) 
                               << 0x18U) | (0xff0000U 
                                            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_6)
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_7)
                                                 : (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                            >> 0x30U))) 
                                               << 0x10U))) 
                             | ((0xff00U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_5)
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_4)
                                              : (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                         >> 0x28U))) 
                                            << 8U)) 
                                | (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_4)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_5)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                        >> 0x20U)))))))) 
            << 0x20U) | (QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_3)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_2)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                        >> 0x18U))) 
                                           << 0x18U) 
                                          | (0xff0000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_2)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_3)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                             >> 0x10U))) 
                                                << 0x10U))) 
                                         | ((0xff00U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_1)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_0)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                             >> 8U))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_1)
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0))))))));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
        = __Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0;
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1 
        = vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1;
    if (vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id[vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0] 
            = vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_deq_valid 
        = (1U & (~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ptr_match))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___T_82 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_0_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___T_101 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_1_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___T_120 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_2_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT___T_139 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__doing_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_2__DOT__s1_resp_3_valid));
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT__ram_data_MPORT_en 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT___do_enq_T;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT__ram_data_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready)) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT___do_enq_T));
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_w_deq__DOT__do_deq = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__monitor__DOT__d_first_beats1_opdata)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__monitor__DOT__d_first_beats1_decode)
            : 0U);
    __Vtemp_267 = ((0U != ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_is_br) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_3_predicted_pc_valid)) 
                              << 3U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_2_is_br) 
                                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_2_predicted_pc_valid)) 
                                        << 2U)) | (
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_1_is_br) 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_1_predicted_pc_valid)) 
                                                    << 1U) 
                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_0_is_br) 
                                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f2_0_predicted_pc_valid)))) 
                           & (((IData)(0xfU) << (3U 
                                                 & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_vpc 
                                                            >> 1U)))) 
                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect)
                                  ? (0xfU & (((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153)
                                               ? (~ 
                                                  ((IData)(1U) 
                                                   << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx)))
                                               : 0xfU) 
                                             & ((((IData)(1U) 
                                                  << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx)) 
                                                 | VL_SHIFTR_III(4,4,32, 
                                                                 (0xfU 
                                                                  & ((IData)(1U) 
                                                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))), 1U)) 
                                                | (VL_SHIFTR_III(4,4,32, 
                                                                 (0xfU 
                                                                  & ((IData)(1U) 
                                                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))), 2U) 
                                                   | VL_SHIFTR_III(4,4,32, 
                                                                   (0xfU 
                                                                    & ((IData)(1U) 
                                                                       << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_redirect_idx))), 3U)))))
                                  : 0xfU)))) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_current_saw_branch_not_taken));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_ghist_old_history 
        = (((QData)((IData)((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect))
                              ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history) 
                                  >> 0x1fU) | ((IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history 
                                                        >> 0x20U)) 
                                               << 1U))
                              : (__Vtemp_267 ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history) 
                                                 >> 0x1fU) 
                                                | ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history 
                                                            >> 0x20U)) 
                                                   << 1U))
                                  : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history 
                                             >> 0x20U)))))) 
            << 0x20U) | (QData)((IData)((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_153) 
                                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_do_redirect))
                                          ? (1U | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history) 
                                                   << 1U))
                                          : (__Vtemp_267
                                              ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history) 
                                                 << 1U)
                                              : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_ghist_old_history))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT___GEN_0 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__monitor__DOT___a_first_T) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_repeat)) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__anyRound 
        = (0U != (vlSelfRef.__VdfgRegularize_hd87f99a1_1_183 
                  | vlSelfRef.__VdfgRegularize_hd87f99a1_1_184));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T 
        = (((QData)((IData)((0xfffffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_ppn)))) 
            << 0xfU) | (QData)((IData)(((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_u) 
                                            << 0xeU) 
                                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_g) 
                                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__r_pte_v)) 
                                              << 0xdU)) 
                                          | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__ptw__DOT__resp_ae) 
                                              << 0xcU) 
                                             | ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_124) 
                                                << 0xbU))) 
                                         | ((((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_125) 
                                              << 0xaU) 
                                             | ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_126) 
                                                << 9U)) 
                                            | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_31) 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_r_T_6) 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_7)
                                                        ? 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_7) 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_w) 
                                                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_7)))
                                                        : 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_6)
                                                         ? 
                                                        ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_6) 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_w) 
                                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_6)))
                                                         : 
                                                        ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_5)
                                                          ? 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_5) 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_w) 
                                                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_5)))
                                                          : 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_4)
                                                           ? 
                                                          ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_4) 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_w) 
                                                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_4)))
                                                           : 
                                                          ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_3)
                                                            ? 
                                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_3) 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_w) 
                                                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_3)))
                                                            : 
                                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_2)
                                                             ? 
                                                            ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_2) 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_w) 
                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_2)))
                                                             : 
                                                            ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_1)
                                                              ? 
                                                             ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_1) 
                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_w) 
                                                                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_1)))
                                                              : 
                                                             ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit)
                                                               ? 
                                                              ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned) 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_w) 
                                                                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore)))
                                                               : 
                                                              (1U 
                                                               < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp_io_prv)))))))))))) 
                                                << 8U) 
                                               | ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_x) 
                                                  << 7U)))) 
                                        | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_r_T_6) 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_7)
                                                     ? 
                                                    ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_7) 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_r) 
                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_7)))
                                                     : 
                                                    ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_6)
                                                      ? 
                                                     ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_6) 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_r) 
                                                         | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_6)))
                                                      : 
                                                     ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_5)
                                                       ? 
                                                      ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_5) 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_r) 
                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_5)))
                                                       : 
                                                      ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_4)
                                                        ? 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_4) 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_r) 
                                                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_4)))
                                                        : 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_3)
                                                         ? 
                                                        ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_3) 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_r) 
                                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_3)))
                                                         : 
                                                        ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_2)
                                                          ? 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_2) 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_r) 
                                                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_2)))
                                                          : 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit_1)
                                                           ? 
                                                          ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned_1) 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_r) 
                                                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore_1)))
                                                           : 
                                                          ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_hit)
                                                            ? 
                                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_aligned) 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_r) 
                                                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp__DOT__res_ignore)))
                                                            : 
                                                           (1U 
                                                            < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__pmp_io_prv)))))))))))) 
                                             << 6U) 
                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___prot_w_T_31) 
                                                << 5U) 
                                               | (0x18U 
                                                  & ((- (IData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__prot_al))) 
                                                     << 3U)))) 
                                           | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
                                                & ((0ULL 
                                                    == 
                                                    (0xca012000ULL 
                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr)) 
                                                   | ((0ULL 
                                                       == 
                                                       (0xca010000ULL 
                                                        & (0x2000000ULL 
                                                           ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr))) 
                                                      | ((0ULL 
                                                          == 
                                                          (0xc8000000ULL 
                                                           & (0x8000000ULL 
                                                              ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr))) 
                                                         | (0ULL 
                                                            == 
                                                            (0xc0000000ULL 
                                                             & (0x40000000ULL 
                                                                ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr))))))) 
                                               << 2U) 
                                              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__legal_address) 
                                                  & (0ULL 
                                                     == 
                                                     (0x80000000ULL 
                                                      & (0x80000000ULL 
                                                         ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__mpu_physaddr)))) 
                                                 << 1U)))))));
    __Vtemp_274 = ((0U != ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_3_is_br) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_3_predicted_pc_valid)) 
                              << 3U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_2_is_br) 
                                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_2_predicted_pc_valid)) 
                                        << 2U)) | (
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_1_is_br) 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_1_predicted_pc_valid)) 
                                                    << 1U) 
                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_0_is_br) 
                                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_0_predicted_pc_valid)))) 
                           & (((IData)(0xfU) << (3U 
                                                 & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                                            >> 1U)))) 
                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_do_redirect)
                                  ? (0xfU & (((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60)
                                               ? (~ 
                                                  ((IData)(1U) 
                                                   << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx)))
                                               : 0xfU) 
                                             & ((((IData)(1U) 
                                                  << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx)) 
                                                 | VL_SHIFTR_III(4,4,32, 
                                                                 (0xfU 
                                                                  & ((IData)(1U) 
                                                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))), 1U)) 
                                                | (VL_SHIFTR_III(4,4,32, 
                                                                 (0xfU 
                                                                  & ((IData)(1U) 
                                                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))), 2U) 
                                                   | VL_SHIFTR_III(4,4,32, 
                                                                   (0xfU 
                                                                    & ((IData)(1U) 
                                                                       << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))), 3U)))))
                                  : 0xfU)))) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_current_saw_branch_not_taken));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_18) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_19 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_23 
            = (((QData)((IData)((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_do_redirect))
                                  ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history) 
                                      >> 0x1fU) | ((IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history 
                                                            >> 0x20U)) 
                                                   << 1U))
                                  : (__Vtemp_274 ? 
                                     (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history) 
                                       >> 0x1fU) | 
                                      ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history 
                                                >> 0x20U)) 
                                       << 1U)) : (IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history 
                                                          >> 0x20U)))))) 
                << 0x20U) | (QData)((IData)((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_60) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_do_redirect))
                                              ? (1U 
                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history) 
                                                    << 1U))
                                              : (__Vtemp_274
                                                  ? 
                                                 ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history) 
                                                  << 1U)
                                                  : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history))))));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_19 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_23 = 0ULL;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__mul_io_val_s0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_latchMulAddA_0) 
           | ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cycleNum_B)) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__cyc_B2_sqrt)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_19)) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT___do_enq_T 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)
            : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full));
    TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT___T_7) 
           & vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_read
           [0U]);
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_6 
        = ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_read
            [0U]) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT___T_7));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 3U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 4U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 5U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 6U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(1U) << vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
                 >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
                 >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21 
        = (((((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_6)) 
              << 6U) | ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_5)) 
                        << 5U)) | (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_4)) 
                                    << 4U) | ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_3)) 
                                              << 3U))) 
           | (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_2)) 
               << 2U) | (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_1)) 
                          << 1U) | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next)))));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_1 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__a_first_counter)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__monitor__DOT___a_first_T));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT___time_T_2 
        = (((QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_15)
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_6)
                                 : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                            >> 0x38U))) 
                               << 0x18U) | (0xff0000U 
                                            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_14)
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_7)
                                                 : (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                            >> 0x30U))) 
                                               << 0x10U))) 
                             | ((0xff00U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_13)
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_4)
                                              : (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                         >> 0x28U))) 
                                            << 8U)) 
                                | (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_12)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_5)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                        >> 0x20U)))))))) 
            << 0x20U) | (QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_11)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_2)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                        >> 0x18U))) 
                                           << 0x18U) 
                                          | (0xff0000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_10)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_3)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                             >> 0x10U))) 
                                                << 0x10U))) 
                                         | ((0xff00U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_9)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_0)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                             >> 8U))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_8)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_1)
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_))))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_1 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__a_first_counter)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__monitor__DOT___a_first_T));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ptr_match 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value) 
           == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ptr_match 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value) 
           == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_hi 
        = (0x1fU & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr
                    [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1] 
                    >> 7U));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_addr_lo 
        = (0xfU & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr
                   [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1] 
                   >> 3U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_opcode_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___bundleIn_0_a_ready_T) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__widget_auto_out_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___bundleIn_0_a_ready_T) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready));
    __VdfgRegularize_hd87f99a1_1_118 = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_new_saw_branch_taken)) 
                                         & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_new_saw_branch_not_taken)) 
                                            & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_ghist_old_history 
                                               == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_ghist_old_history))) 
                                        & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc 
                                           == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_target));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
        = (0x7fffffffffffffULL & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT___roundIncr_T) 
                                    & (0U != vlSelfRef.__VdfgRegularize_hd87f99a1_1_183)) 
                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMagUp) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__anyRound)))
                                   ? ((((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__roundingMode_PC)) 
                                        & ((~ (IData)(
                                                      (0U 
                                                       != vlSelfRef.__VdfgRegularize_hd87f99a1_1_184))) 
                                           & (0U != vlSelfRef.__VdfgRegularize_hd87f99a1_1_183)))
                                        ? (~ (1ULL 
                                              | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7 
                                                 << 1U)))
                                        : 0x7fffffffffffffULL) 
                                      & (1ULL + (0x3fffffffffffffULL 
                                                 & ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_rawOut_sig 
                                                     >> 2U) 
                                                    | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7))))
                                   : ((0x3fffffffffffffULL 
                                       & ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMask_hi_7) 
                                          & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_rawOut_sig 
                                             >> 2U))) 
                                      | (((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__roundingMode_PC)) 
                                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__anyRound))
                                          ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundPosMask 
                                             >> 1U)
                                          : 0ULL))));
    if ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_refill_tag))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_57 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_83 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_109 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_135 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_161 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_187 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_213 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_239 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_57 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_0_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_83 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_109 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_135 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_3_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_161 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_4_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_187 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_5_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_213 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_6_data_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_239 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_data_0;
    }
    if ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_refill_tag))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_58 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_84 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_110 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_136 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_162 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_188 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_214 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_240 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_58 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_0_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_84 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_110 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_136 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_3_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_162 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_4_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_188 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_5_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_214 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_6_data_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_240 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_data_1;
    }
    if ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_refill_tag))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_59 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_85 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_111 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_137 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_163 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_189 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_215 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_241 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_59 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_0_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_85 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_111 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_137 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_3_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_163 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_4_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_189 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_5_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_215 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_6_data_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_241 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_data_2;
    }
    if ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__r_refill_tag))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_60 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_86 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_112 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_138 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_164 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_190 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_216 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_242 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___special_entry_data_0_T;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_60 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_0_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_86 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_1_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_112 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_2_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_138 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_3_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_164 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_4_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_190 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_5_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_216 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_6_data_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT___GEN_242 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb__DOT__sectored_entries_0_7_data_3;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT___do_enq_T;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en 
            = ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_19) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT___do_enq_T));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_2 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_1) 
                 + (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_14 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_4) 
                 + (0x1fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                              >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_26 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_7) 
                 + (3U & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                           >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_22 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_6) 
                 + (7U & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                           >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_18 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_5) 
                 + (0xfU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                             >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_2 
        = (0x3fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                     >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_1 
        = (0x7fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                     >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT___do_enq_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT___claimedDevs_T 
        = (0xfU & ((IData)(1U) << ((((IData)(TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0) 
                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_4) 
                                        & (0U != vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_7)))
                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_0)
                                     : 0U) | (((IData)(TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0) 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_5) 
                                                  & (0U 
                                                     != vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_7)))
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_1)
                                               : 0U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_11 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_6) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_14 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_6) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_4));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2 
        = (0xffffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21) 
                      | VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21), 1U)));
    if (TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_1) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_23 
            = ((0U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_24 
            = ((1U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_25 
            = ((2U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_26 
            = ((3U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_3));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_27 
            = ((4U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_28 
            = ((5U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_5));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_29 
            = ((6U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_6));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_30 
            = ((7U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_7));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_31 
            = ((8U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_8));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_32 
            = ((9U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_9));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_33 
            = ((0xaU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_10));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_34 
            = ((0xbU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_11));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_35 
            = ((0xcU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_12));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_36 
            = ((0xdU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_13));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_37 
            = ((0xeU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_14));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_38 
            = ((0xfU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_15));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_23 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_24 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_25 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_26 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_27 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_28 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_5;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_29 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_6;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_30 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_7;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_31 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_8;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_32 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_9;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_33 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_10;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_34 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_11;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_35 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_12;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_36 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_13;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_37 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_14;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_38 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_15;
    }
    if (TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_1) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_18 
            = ((0U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_19 
            = ((1U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_20 
            = ((2U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_21 
            = ((3U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F3));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_22 
            = ((4U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_23 
            = ((5U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F5));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_24 
            = ((6U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F6));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_25 
            = ((7U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F7));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_26 
            = ((8U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F8));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_27 
            = ((9U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F9));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_28 
            = ((0xaU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F10));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_29 
            = ((0xbU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F11));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_30 
            = ((0xcU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F12));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_31 
            = ((0xdU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F13));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_32 
            = ((0xeU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F14));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_33 
            = ((0xfU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1])
                ? (0U != (0x80000000U & vlSelfRef.__VdfgRegularize_hd87f99a1_1_0))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F15));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_18 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_19 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_20 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_21 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_22 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_23 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F5;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_24 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F6;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_25 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F7;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_26 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F8;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_27 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F9;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_28 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F10;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_29 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F11;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_30 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F12;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_31 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F13;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_32 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F14;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT___GEN_33 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__flight___05F15;
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_deq_valid 
        = (1U & (~ ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ptr_match))));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_deq_valid 
        = (1U & (~ ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__maybe_full)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ptr_match))));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready 
        = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ptr_match) 
                    & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__maybe_full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__latch 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__beatsLeft)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__beatsLeft))
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__readys_readys)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__state_0)));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__out_1_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__beatsLeft))
               ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__readys_readys) 
                  >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__state_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__monitor__DOT___a_first_T 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_in_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__widget_auto_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_17 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_valid) 
           & (IData)(__VdfgRegularize_hd87f99a1_1_118));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_198 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_valid)) 
                 | ((~ (IData)(__VdfgRegularize_hd87f99a1_1_118)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp 
        = (0x3fffU & (VL_EXTENDS_II(14,13, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw_io_rawOut_sExp)) 
                      + VL_EXTENDS_II(14,13, (3U & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                            >> 0x35U))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_12 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_2)) 
                   - (0x3fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_16)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_8 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_1)) 
                   - (0x7fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_16)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_3 
        = (7U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_14) 
                  & ((0xffffffffU == vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_7) 
                     & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__enables_0_0) 
                         << 1U) >> (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                                                  [0U] 
                                                  >> 0x20U)))))) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_11) 
                    & ((0xffffffffU == vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_7) 
                       & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__enables_1_0) 
                           << 1U) >> (3U & (IData)(
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                                                    [0U] 
                                                    >> 0x20U))))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5 
        = (0xffffU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2) 
                      | VL_SHIFTL_III(16,16,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2), 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_full));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams_auto_in_ar_ready 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_full)) 
                 | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq_io_enq_ready)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___T_12 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_ar_valid));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_6_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__maybe_full) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_ar_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_ar_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT___GEN_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_w_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_valid));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__out_1_ready) 
           & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__w_todo)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_w_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___beatsLeft_T_4 
        = (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__beatsLeft) 
                    - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__monitor__DOT___a_first_T)));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT____VdfgRegularize_h063f9c6d_0_1 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__a_first_counter)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__monitor__DOT___a_first_T));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__commonCase) 
           & (VL_GTS_III(14, 0x3ceU, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundMagUp) 
                 | (6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__roundingMode_PC)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h0bea23db_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__divSqrtRecF64ToRaw__DOT__isZero_PC) 
           | VL_GTS_III(14, 0x3ceU, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__overflow 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__commonCase) 
           & VL_LTES_III(4, 3U, (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp) 
                                         >> 0xaU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full)) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
              & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__maybe_full)) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full)) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
              & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full)) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8 
        = (0xffffU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5) 
                      | VL_SHIFTL_III(16,16,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5), 4U)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___T_14 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams_auto_in_ar_ready));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en)
                      ? ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len) 
                         - (IData)(1U)) : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__r_len)));
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT___do_enq_T;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_ready)) 
               & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT___do_enq_T));
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__do_deq = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_extra_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_6_0) 
              & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_id))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_extra_id_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1_io_enq_ready) 
            & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_6_0)) 
           & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_io_deq_bits_id)) 
              >> 1U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__maybe_full) 
            & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_ar_ready)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag_auto_out_ar_bits_echo_real_last));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___T_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_ar_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_w_deq__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_w_ready)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___bundleOut_0_w_valid_T_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___T_36 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_out_aw_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_2_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag_auto_out_aw_valid) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_aw_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_aw_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT___GEN_9));
    if (TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT____VdfgRegularize_h063f9c6d_0_1) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_18 
            = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_19 
            = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_20 
            = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_21 
            = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_3));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_22 
            = ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_23 
            = ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_5));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_24 
            = ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_6));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_25 
            = ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_7));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_26 
            = ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_8));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_27 
            = ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_9));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_28 
            = ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_10));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_29 
            = ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_11));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_30 
            = ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_12));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_31 
            = ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_13));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_32 
            = ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_14));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_33 
            = ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer_auto_out_a_bits_source)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_15));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_18 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_19 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_20 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_21 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_22 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_23 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_5;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_24 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_6;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_25 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_7;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_26 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_8;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_27 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_9;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_28 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_10;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_29 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_11;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_30 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_12;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_31 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_13;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_32 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_14;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT___GEN_33 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__fixer__DOT__flight_15;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isSpecialInfOut) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__overflow) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__overflow_roundMagUp)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__overflow_roundMagUp)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__overflow));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner 
        = ((~ (0x1fffeU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8) 
                            | VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8), 8U)) 
                           << 1U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___GEN_41 
        = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___T_14) 
           | ((~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en)) 
              & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_full)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___GEN_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___T_2)
                      ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__len) 
                         - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__beats))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__r_len)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_extra_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_2_0) 
              & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1_io_deq_bits_id))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_extra_id_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3_io_enq_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb2c28821_2_0)) 
           & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1_io_deq_bits_id)) 
              >> 1U));
    TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_aw_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_aw_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___in_aw_ready_T));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_514 = ((
                                                   ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                     ? 0xdffU
                                                     : 0xfffU) 
                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                        ? 0xbffU
                                                        : 0xfffU) 
                                                      & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                           ? 0x3ceU
                                                           : 0xfffU) 
                                                         & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h0bea23db_0_2)
                                                              ? 0x1ffU
                                                              : 0xfffU) 
                                                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp))))) 
                                                  | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                        ? 0x3ceU
                                                        : 0U) 
                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                          ? 0xbffU
                                                          : 0U)) 
                                                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                          ? 0xc00U
                                                          : 0U) 
                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                            ? 0xe00U
                                                            : 0U))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T 
        = (0xffffU & ((1U & (TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner 
                             >> 0x10U)) | TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1__DOT__maybe_full) 
            & (IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_aw_ready)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag_auto_out_aw_bits_echo_real_last));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___T_5 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__in_aw_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__deq_1__DOT__maybe_full));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_435 = (((QData)((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_514)) 
                                                   << 0x34U) 
                                                  | (0xfffffffffffffULL 
                                                     & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h0bea23db_0_2))
                                                          ? 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                           ? 0x8000000000000ULL
                                                           : 0ULL)
                                                          : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig) 
                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit__DOT__fdivsqrt__DOT__divsqrt__DOT__ds__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                            ? 0xfffffffffffffULL
                                                            : 0ULL))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1 
        = (0xffU & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T) 
                     >> 8U) | (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___GEN_9 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT___T_5)
                      ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__len_1) 
                         - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__w_beats))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4frag__DOT__r_len_1)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2 
        = (0xfU & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1) 
                    >> 4U) | (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___GEN_1 
        = ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__locked)) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___pending_dec_T_1) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))))
            ? (((0x10U & (TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner 
                          >> 0xcU)) | ((((IData)((0U 
                                                  != 
                                                  (0xffU 
                                                   & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T) 
                                                      >> 8U)))) 
                                         << 1U) | (0U 
                                                   != 
                                                   (0xfU 
                                                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1) 
                                                       >> 4U)))) 
                                       << 2U)) | (((IData)(
                                                           (0U 
                                                            != 
                                                            (3U 
                                                             & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2) 
                                                                >> 2U)))) 
                                                   << 1U) 
                                                  | (IData)(
                                                            (0U 
                                                             != 
                                                             (0xaU 
                                                              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2))))))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id));
}
