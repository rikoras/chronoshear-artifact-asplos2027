// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__3(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__3\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmactive_synced_dmactiveSync__DOT__output_chain__DOT__sync_0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_65 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_631)
                ? (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__hartIsInResetSync_0_debug_hartReset_0__DOT__output_chain__DOT__sync_0)))
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_448)
                    ? 0U : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__hartIsInResetSync_0_debug_hartReset_0__DOT__output_chain__DOT__sync_0)) 
                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_66 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumereq)
                ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__hartIsInResetSync_0_debug_hartReset_0__DOT__output_chain__DOT__sync_0)) 
                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeReqRegs) 
                      | (0U == (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg) 
                                          >> 4U)))))
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_448)
                    ? 0U : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__hartIsInResetSync_0_debug_hartReset_0__DOT__output_chain__DOT__sync_0)) 
                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeReqRegs))));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_65 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_66 = 0U;
    }
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__4(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__4\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_7;
    VlWide<4>/*127:0*/ __Vtemp_8;
    VlWide<4>/*127:0*/ __Vtemp_14;
    VlWide<4>/*127:0*/ __Vtemp_15;
    VlWide<4>/*127:0*/ __Vtemp_21;
    VlWide<4>/*127:0*/ __Vtemp_22;
    VlWide<4>/*127:0*/ __Vtemp_28;
    VlWide<4>/*127:0*/ __Vtemp_29;
    VlWide<4>/*127:0*/ __Vtemp_36;
    VlWide<4>/*127:0*/ __Vtemp_37;
    VlWide<4>/*127:0*/ __Vtemp_43;
    VlWide<4>/*127:0*/ __Vtemp_44;
    VlWide<4>/*127:0*/ __Vtemp_56;
    VlWide<4>/*127:0*/ __Vtemp_57;
    VlWide<4>/*127:0*/ __Vtemp_63;
    VlWide<4>/*127:0*/ __Vtemp_64;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_36) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_4 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__REG));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_valid) 
           & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask) 
                  >> 1U)) & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT___T_423) 
                                >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask)) 
              & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT___T_423))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_clear));
    __Vtemp_3[0U] = 1U;
    __Vtemp_3[1U] = 0U;
    __Vtemp_3[2U] = 0U;
    __Vtemp_3[3U] = 0U;
    VL_SHIFTL_WWI(128,128,6, __Vtemp_4, __Vtemp_3, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist__DOT__r));
    __Vtemp_7[0U] = 1U;
    __Vtemp_7[1U] = 0U;
    __Vtemp_7[2U] = 0U;
    __Vtemp_7[3U] = 0U;
    VL_SHIFTL_WWI(128,128,6, __Vtemp_8, __Vtemp_7, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist__DOT__r_1));
    __Vtemp_14[0U] = 1U;
    __Vtemp_14[1U] = 0U;
    __Vtemp_14[2U] = 0U;
    __Vtemp_14[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_15, __Vtemp_14, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ll_wbarb_io_out_bits_uop_pdst));
    __Vtemp_21[0U] = 1U;
    __Vtemp_21[1U] = 0U;
    __Vtemp_21[2U] = 0U;
    __Vtemp_21[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_22, __Vtemp_21, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__RegisterReadDecode_1_io_rrd_uop_pdst));
    __Vtemp_28[0U] = 1U;
    __Vtemp_28[1U] = 0U;
    __Vtemp_28[2U] = 0U;
    __Vtemp_28[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_29, __Vtemp_28, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__jmp_unit_io_iresp_bits_uop_pdst));
    __Vtemp_36[0U] = 1U;
    __Vtemp_36[1U] = 0U;
    __Vtemp_36[2U] = 0U;
    __Vtemp_36[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_37, __Vtemp_36, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregister_read__DOT__RegisterReadDecode_2_io_rrd_uop_pdst));
    __Vtemp_43[0U] = 1U;
    __Vtemp_43[1U] = 0U;
    __Vtemp_43[2U] = 0U;
    __Vtemp_43[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_44, __Vtemp_43, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_exe_unit_io_iresp_bits_uop_pdst));
    __Vtemp_56[0U] = 1U;
    __Vtemp_56[1U] = 0U;
    __Vtemp_56[2U] = 0U;
    __Vtemp_56[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_57, __Vtemp_56, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_ren2_uops_0_pdst));
    __Vtemp_63[0U] = 1U;
    __Vtemp_63[1U] = 0U;
    __Vtemp_63[2U] = 0U;
    __Vtemp_63[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_64, __Vtemp_63, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_ren2_uops_1_pdst));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT___GEN_38 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[0U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[1U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[2U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[3U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[0U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[1U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[2U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[3U] = 0U;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_537)
                ? (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_allocOH)))
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor_1__DOT___b_first_T)
                    ? ((~ ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG) 
                               << 1U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT___GEN_38 
            = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__replay_arb_io_out_valid) 
                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_MPORT_en))
                ? (((~ (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__replay_arb_io_out_bits_sdq_id)) 
                        & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT___T_26) 
                            & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__replay_arb_io_out_bits_uop_mem_cmd)) 
                               | ((0x11U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__replay_arb_io_out_bits_uop_mem_cmd)) 
                                  | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_96))))
                            ? 0x1ffffU : 0U))) & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val) 
                   | (((1U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                        ? ((2U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                            ? ((4U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                ? ((8U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                    ? ((0x10U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                        ? ((0x20U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                            ? ((0x40U 
                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                ? (
                                                   (0x80U 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                    ? 
                                                   ((0x100U 
                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                     ? 
                                                    ((0x200U 
                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                      ? 
                                                     ((0x400U 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                       ? 
                                                      ((0x800U 
                                                        & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                        ? 
                                                       ((0x1000U 
                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                         ? 
                                                        ((0x2000U 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                          ? 
                                                         ((0x4000U 
                                                           & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                           ? 
                                                          ((0x8000U 
                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                            ? 
                                                           ((0x10000U 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val)
                                                             ? 0U
                                                             : 0x10000U)
                                                            : 0x8000U)
                                                           : 0x4000U)
                                                          : 0x2000U)
                                                         : 0x1000U)
                                                        : 0x800U)
                                                       : 0x400U)
                                                      : 0x200U)
                                                     : 0x100U)
                                                    : 0x80U)
                                                : 0x40U)
                                            : 0x20U)
                                        : 0x10U) : 8U)
                                : 4U) : 2U) : 1U) & 
                      ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_MPORT_en)
                        ? 0x1ffffU : 0U))) : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__dcache__DOT__mshrs__DOT__sdq_val);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[0U] 
            = ((IData)(((~ (((1ULL << (0x3fU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__ll_wbarb_io_out_bits_uop_pdst))) 
                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__ll_wbarb_io_out_valid)
                                 ? 0xffffffffffffffffULL
                                 : 0ULL)) | ((1ULL 
                                              << (0x3fU 
                                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit_io_fresp_bits_uop_pdst))) 
                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline_io_wakeups_1_valid)
                                                 ? 0xffffffffffffffffULL
                                                 : 0ULL)))) 
                        & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT__busy_table)) 
               | ((__Vtemp_4[0U] & (IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist_io_reqs_0)
                                             ? 0xffffffffffffffffULL
                                             : 0ULL))) 
                  | (__Vtemp_8[0U] & (IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist_io_reqs_1)
                                               ? 0xffffffffffffffffULL
                                               : 0ULL)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[1U] 
            = ((IData)((((~ (((1ULL << (0x3fU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__ll_wbarb_io_out_bits_uop_pdst))) 
                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__ll_wbarb_io_out_valid)
                                  ? 0xffffffffffffffffULL
                                  : 0ULL)) | ((1ULL 
                                               << (0x3fU 
                                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline__DOT__fpiu_unit_io_fresp_bits_uop_pdst))) 
                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_pipeline_io_wakeups_1_valid)
                                                  ? 0xffffffffffffffffULL
                                                  : 0ULL)))) 
                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT__busy_table) 
                        >> 0x20U)) | ((__Vtemp_4[1U] 
                                       & (IData)((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist_io_reqs_0)
                                                    ? 0xffffffffffffffffULL
                                                    : 0ULL) 
                                                  >> 0x20U))) 
                                      | (__Vtemp_8[1U] 
                                         & (IData)(
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__freelist_io_reqs_1)
                                                      ? 0xffffffffffffffffULL
                                                      : 0ULL) 
                                                    >> 0x20U)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[2U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__fp_rename_stage__DOT__busytable__DOT___GEN_3[3U] = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[0U] 
            = (((~ ((__Vtemp_15[0U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile_io_write_ports_0_valid)
                                        ? 0xffffffffU
                                        : 0U)) | ((
                                                   (__Vtemp_22[0U] 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_1_valid)
                                                        ? 0xffffffffU
                                                        : 0U)) 
                                                   | (__Vtemp_29[0U] 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_2_valid)
                                                          ? 0xffffffffU
                                                          : 0U))) 
                                                  | ((__Vtemp_37[0U] 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_3_valid)
                                                          ? 0xffffffffU
                                                          : 0U)) 
                                                     | (__Vtemp_44[0U] 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_4_valid)
                                                            ? 0xffffffffU
                                                            : 0U)))))) 
                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT__busy_table[0U]) 
               | ((__Vtemp_57[0U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_0)
                                      ? 0xffffffffU
                                      : 0U)) | (__Vtemp_64[0U] 
                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_1)
                                                    ? 0xffffffffU
                                                    : 0U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[1U] 
            = (((~ ((__Vtemp_15[1U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile_io_write_ports_0_valid)
                                        ? 0xffffffffU
                                        : 0U)) | ((
                                                   (__Vtemp_22[1U] 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_1_valid)
                                                        ? 0xffffffffU
                                                        : 0U)) 
                                                   | (__Vtemp_29[1U] 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_2_valid)
                                                          ? 0xffffffffU
                                                          : 0U))) 
                                                  | ((__Vtemp_37[1U] 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_3_valid)
                                                          ? 0xffffffffU
                                                          : 0U)) 
                                                     | (__Vtemp_44[1U] 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_4_valid)
                                                            ? 0xffffffffU
                                                            : 0U)))))) 
                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT__busy_table[1U]) 
               | ((__Vtemp_57[1U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_0)
                                      ? 0xffffffffU
                                      : 0U)) | (__Vtemp_64[1U] 
                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_1)
                                                    ? 0xffffffffU
                                                    : 0U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[2U] 
            = (((~ ((__Vtemp_15[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__iregfile_io_write_ports_0_valid)
                                        ? 0xffffU : 0U)) 
                    | (((__Vtemp_22[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_1_valid)
                                            ? 0xffffU
                                            : 0U)) 
                        | (__Vtemp_29[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_2_valid)
                                              ? 0xffffU
                                              : 0U))) 
                       | ((__Vtemp_37[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_3_valid)
                                              ? 0xffffU
                                              : 0U)) 
                          | (__Vtemp_44[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_wakeups_4_valid)
                                                ? 0xffffU
                                                : 0U)))))) 
                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT__busy_table[2U]) 
               | ((__Vtemp_57[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_0)
                                      ? 0xffffU : 0U)) 
                  | (__Vtemp_64[2U] & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__freelist_io_reqs_1)
                                        ? 0xffffU : 0U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__busytable__DOT___GEN_8[3U] = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__in_reset)
                  ? (~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_5_0))
                  : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass_reg)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_4008 
        = (0xffffU & ((~ (((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                               & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_4002))) 
                              << 0xfU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3999))) 
                                          << 0xeU)) 
                            | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3996))) 
                                << 0xdU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                             & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3993))) 
                                            << 0xcU))) 
                           | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3990))) 
                                << 0xbU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                             & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3987))) 
                                            << 0xaU)) 
                              | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                   & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3984))) 
                                  << 9U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                             & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3981))) 
                                            << 8U)))) 
                          | ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3978))) 
                                << 7U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3975))) 
                                          << 6U)) | 
                              ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3972))) 
                                << 5U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3969))) 
                                          << 4U))) 
                             | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                   & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3966))) 
                                  << 3U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                             & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3963))) 
                                            << 2U)) 
                                | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                     & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3960))) 
                                    << 1U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3953) 
                                              & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)) 
                                                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3957)))))))) 
                      & ((~ (((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_15_valid) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3814)) 
                                 << 0xfU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_14_valid) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3802)) 
                                             << 0xeU)) 
                               | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_13_valid) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3790)) 
                                   << 0xdU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_12_valid) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3778)) 
                                               << 0xcU))) 
                              | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_11_valid) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3766)) 
                                   << 0xbU) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_10_valid) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3754)) 
                                               << 0xaU)) 
                                 | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_9_valid) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3742)) 
                                     << 9U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_8_valid) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3730)) 
                                               << 8U)))) 
                             | ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_7_valid) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3718)) 
                                   << 7U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_6_valid) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3706)) 
                                             << 6U)) 
                                 | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_5_valid) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3694)) 
                                     << 5U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_4_valid) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3682)) 
                                               << 4U))) 
                                | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_3_valid) 
                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3670)) 
                                     << 3U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_2_valid) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3658)) 
                                               << 2U)) 
                                   | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_1_valid) 
                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3646)) 
                                       << 1U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__stq_0_valid) 
                                                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_3634))))))) 
                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_133)
                             ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_112) 
                                | ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dispatcher_io_dis_uops_2_1_bits_stq_idx)))
                             : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT___T_112)))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_18) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_16 
            = (1U & (~ (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_is_replay)
                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__REG_2_ae_inst)
                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_ae_inst)) 
                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_is_replay)
                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__REG_2_pf_inst)
                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__tlb_io_resp_pf_inst)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_18 
            = (0xffffffffffULL & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_do_redirect)
                                   ? ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_3_predicted_pc_bits
                                       : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_2_predicted_pc_bits
                                           : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f1_redirect_idx))
                                               ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_1_predicted_pc_bits
                                               : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0__DOT__components_0_io_resp_f1_0_predicted_pc_bits)))
                                   : (8ULL + (~ (7ULL 
                                                 | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s1_vpc))))));
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_4) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_16 = 1U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_18 
            = (0xffffffffffULL & 0x10040ULL);
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_16 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_18 
            = (0xffffffffffULL & 0ULL);
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleIn_0_a_ready_T 
        = (1U & (~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__stall_counter)) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass) 
                       != (1U & (~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_5_0)))))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_181) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65 
            = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_92)) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_is_replay) 
                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_tlb_miss))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_vpc;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_21) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_198) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65 
                = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_16)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_target;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_16));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_18;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65 
            = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_16));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_18;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_161 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_19)
                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65)
                  : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_20)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65)
                      : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_771)
                          ? (~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3__DOT__ram_xcpt_ae_inst
                                [0U] | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3__DOT__ram_xcpt_pf_inst
                                [0U])) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_140 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_20)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_771)
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3_predicted_target
                : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_19_valid)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_val)
               : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_661)
                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_161)
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_65))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_19_valid)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_19_bits_addr
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush)
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_pc
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_661)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_19)
                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66
                        : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_140)
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_66)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__s0_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__dataArrayWay_0_MPORT_1_addr 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT___T_64)
                      : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                 >> 3U))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__5(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__5\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_346;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_346 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0 = 0;
    // Body
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_484 = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_485 = 0ULL;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__csr_wen) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_484 
            = ((0x305U == (0xfffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_exe_unit__DOT__alu__DOT__REG_1_0_imm_packed 
                                     >> 8U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mtvec)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_485 
            = ((0x320U == (0xfffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_exe_unit__DOT__alu__DOT__REG_1_0_imm_packed 
                                     >> 8U))) ? (0xfffffffffffffffdULL 
                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__wdata)
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_484 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mtvec));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___GEN_485 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0_io_deq_uop_exception) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_valid)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_bits_ftq_idx)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_20)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_21)
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0)
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_ftq_idx)
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_ftq_idx))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_346 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_enq_partial_stall) 
           | ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_state)) 
              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_valid) 
                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_20)) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1_io_deq_uop_exception) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_143 
        = (((0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) 
            == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__enq_ptr)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_MPORT_2_en));
    if ((0x1bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_27;
    } else if ((0x1aU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_26;
    } else if ((0x19U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_25;
    } else if ((0x18U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_24;
    } else if ((0x17U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_23;
    } else if ((0x16U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_22;
    } else if ((0x15U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_21;
    } else if ((0x14U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_20;
    } else if ((0x13U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_19;
    } else if ((0x12U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_18;
    } else if ((0x11U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_17;
    } else if ((0x10U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_16;
    } else if ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_15;
    } else if ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_14;
    } else if ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_13;
    } else if ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_12;
    } else if ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_11;
    } else if ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_10;
    } else if ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_9;
    } else if ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_8;
    } else if ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_7;
    } else if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_6;
    } else if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_5;
    } else if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_4;
    } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_3;
    } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_2;
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3356 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3036 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3004 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3388 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_2973 
        = ((0x1cU == (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_28
            : ((0x1bU == (0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_27
                : ((0x1aU == (0x1fU & ((IData)(1U) 
                                       + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_26
                    : ((0x19U == (0x1fU & ((IData)(1U) 
                                           + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_25
                        : ((0x18U == (0x1fU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_24
                            : ((0x17U == (0x1fU & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_23
                                : ((0x16U == (0x1fU 
                                              & ((IData)(1U) 
                                                 + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_22
                                    : ((0x15U == (0x1fU 
                                                  & ((IData)(1U) 
                                                     + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_21
                                        : ((0x14U == 
                                            (0x1fU 
                                             & ((IData)(1U) 
                                                + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_20
                                            : ((0x13U 
                                                == 
                                                (0x1fU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_19
                                                : (
                                                   (0x12U 
                                                    == 
                                                    (0x1fU 
                                                     & ((IData)(1U) 
                                                        + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_18
                                                    : 
                                                   ((0x11U 
                                                     == 
                                                     (0x1fU 
                                                      & ((IData)(1U) 
                                                         + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_17
                                                     : 
                                                    ((0x10U 
                                                      == 
                                                      (0x1fU 
                                                       & ((IData)(1U) 
                                                          + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_16
                                                      : 
                                                     ((0xfU 
                                                       == 
                                                       (0x1fU 
                                                        & ((IData)(1U) 
                                                           + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_15
                                                       : 
                                                      ((0xeU 
                                                        == 
                                                        (0x1fU 
                                                         & ((IData)(1U) 
                                                            + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_14
                                                        : 
                                                       ((0xdU 
                                                         == 
                                                         (0x1fU 
                                                          & ((IData)(1U) 
                                                             + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_13
                                                         : 
                                                        ((0xcU 
                                                          == 
                                                          (0x1fU 
                                                           & ((IData)(1U) 
                                                              + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_12
                                                          : 
                                                         ((0xbU 
                                                           == 
                                                           (0x1fU 
                                                            & ((IData)(1U) 
                                                               + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_11
                                                           : 
                                                          ((0xaU 
                                                            == 
                                                            (0x1fU 
                                                             & ((IData)(1U) 
                                                                + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_10
                                                            : 
                                                           ((9U 
                                                             == 
                                                             (0x1fU 
                                                              & ((IData)(1U) 
                                                                 + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                             ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_9
                                                             : 
                                                            ((8U 
                                                              == 
                                                              (0x1fU 
                                                               & ((IData)(1U) 
                                                                  + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                              ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_8
                                                              : 
                                                             ((7U 
                                                               == 
                                                               (0x1fU 
                                                                & ((IData)(1U) 
                                                                   + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                               ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_7
                                                               : 
                                                              ((6U 
                                                                == 
                                                                (0x1fU 
                                                                 & ((IData)(1U) 
                                                                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_6
                                                                : 
                                                               ((5U 
                                                                 == 
                                                                 (0x1fU 
                                                                  & ((IData)(1U) 
                                                                     + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_5
                                                                 : 
                                                                ((4U 
                                                                  == 
                                                                  (0x1fU 
                                                                   & ((IData)(1U) 
                                                                      + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                  ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_4
                                                                  : 
                                                                 ((3U 
                                                                   == 
                                                                   (0x1fU 
                                                                    & ((IData)(1U) 
                                                                       + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_3
                                                                   : 
                                                                  ((2U 
                                                                    == 
                                                                    (0x1fU 
                                                                     & ((IData)(1U) 
                                                                        + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_2
                                                                    : 
                                                                   ((1U 
                                                                     == 
                                                                     (0x1fU 
                                                                      & ((IData)(1U) 
                                                                         + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))))
                                                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_1
                                                                     : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_0))))))))))))))))))))))))))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0) 
           & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_346) 
              | ((((0xfffU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT__branch_mask)) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic_io_is_branch_0)) 
                  | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
                 | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_518))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready 
        = ((~ ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1) 
                  & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_346) 
                     | ((((0xfffU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_40)) 
                          & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask) 
                                 >> 1U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_381))) 
                         | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
                        | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_518)))))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT__do_deq 
        = ((~ (IData)((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT__slot_will_hit_tail)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_366 
        = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready) 
             << 1U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0)) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_84 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_371))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_39)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT__branch_mask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_299 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_3_br_mask)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_enq_partial_stall)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_3_br_mask)
                : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_resolve_mask)) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_84))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__34(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__34\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
        = vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_bits_data;
    vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg 
        = (3U & vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fdebug_req_bits_op);
    if ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_haltreq 
            = (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
               >> 0x1fU);
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_clrresethaltreq 
            = (1U & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
                     >> 2U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address 
            = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg) 
               << 2U);
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_haltreq = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_clrresethaltreq = 0U;
        if ((1U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 4U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address 
                = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg) 
                   << 2U);
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 0U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address = 0x48U;
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_bits_opcode 
        = ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
            ? 4U : ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
                     ? 4U : ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
                              ? 2U : ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
                                       ? 1U : ((3U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
                                                ? 1U
                                                : (
                                                   (2U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))
                                                    ? 1U
                                                    : 0U))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1 
        = ((0U == (0x1f4U & (0x40U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))) 
           | (0U == (0x1f8U & (0x50U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0 
        = ((0U == (0x1c0U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address))) 
           | ((0U == (0x1f4U & (0x44U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))) 
              | ((0U == (0x1f8U & (0x58U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))) 
                 | ((0U == (0x1e0U & (0x60U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))) 
                    | ((0U == (0x180U & (0x80U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))) 
                       | (0U == (0x100U & (0x100U ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address)))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__35(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__35\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__6(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__6\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready = 0;
    CData/*1:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___T;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___T = 0;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleOut_0_a_valid_T_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleIn_0_a_ready_T) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT___a_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source_io_enq_ready) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleOut_0_a_valid_T_1)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleOut_0_a_valid_T_1) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__idle));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__earlyWinner_1 
        = ((~ (1U & (VL_SHIFTL_III(2,2,32, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid) 
                                            << 1U), 1U) 
                     >> 1U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__beatsLeft) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_valid 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__state_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_denied 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__state_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_denied 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__earlyWinner_1;
    }
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_denied)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_bits_opcode)
            : 0U);
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_denied 
            = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_denied));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_opcode 
            = (7U & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink_io_deq_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_denied 
            = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                             >> 0x21U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_opcode 
            = (7U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                             >> 0x28U)));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid) 
            << 1U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
            ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0)) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1)))
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter 
        = ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_mask)) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo)) 
            << 2U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready 
        = (0xfU & ((VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter), 1U) 
                    | VL_SHIFTR_III(4,4,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter), 2U)) 
                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_mask) 
                      << 2U)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys 
        = (3U & (~ (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready) 
                     >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT___readys_mask_T 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_1 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_0 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1)
               : ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
                  >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0)
               : (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid) 
           & ((4U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready) 
                 & (IData)(((0U == (0x14U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address))) 
                            & ((IData)(1U) << (1U & 
                                               ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address) 
                                                >> 3U))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT___d_first_T 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___d_first_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_denied));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter_io_innerCtrl_bits_resumereq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6) 
            & ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
               & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
                  >> 0x1eU))) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__innerCtrlResumeReqReg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter_io_innerCtrl_bits_ackhavereset 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6) 
            & ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
               & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
                  >> 0x1cU))) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__innerCtrlAckHaveResetReg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT___GEN_23 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6) 
            & ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
               & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
                  >> 3U))) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__hrmaskReg_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter_io_innerCtrl_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__innerCtrlValidReg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__ridx_incremented 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__ridx_ridx_bin) 
              + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT___d_first_T)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___d_first_T) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter_3)) 
              & (IData)((4U == (6U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_opcode))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__latch 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__beatsLeft)) 
           & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__monitor__DOT___d_first_T 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__state_1)
               : (~ (1U & (VL_SHIFTL_III(2,2,32, ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid) 
                                                  << 1U), 1U) 
                           >> 1U)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT___widx_T_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter_io_innerCtrl_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___T 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__idle));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___GEN_12 
        = ((~ ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___T) 
               & (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_bits_opcode)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__idle));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT___bundleIn_0_a_ready_T) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)
               ? (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source_io_enq_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0) 
            & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready)) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___a_first_T 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__next_flight 
        = (3U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__flight) 
                  + ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo) 
                     + VL_SHIFTR_III(2,2,32, ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___a_first_T)) 
                                               << 1U) 
                                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo)), 1U))) 
                 - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___d_first_T) 
                    + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT___d_first_T), 1U))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__36(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__36\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__37(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__37\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut_debug_reset) 
           | (IData)(vlSelfRef.reset));
}

void VTestHarness___024root___eval_triggers__act(VTestHarness___024root* vlSelf);
void VTestHarness___024root___eval_act(VTestHarness___024root* vlSelf);

bool VTestHarness___024root___eval_phase__act(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_phase__act\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<7> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VTestHarness___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VTestHarness___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void VTestHarness___024root___eval_nba(VTestHarness___024root* vlSelf);

bool VTestHarness___024root___eval_phase__nba(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_phase__nba\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VTestHarness___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__ico(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG
bool VTestHarness___024root___eval_phase__ico(VTestHarness___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__nba(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VTestHarness___024root___dump_triggers__act(VTestHarness___024root* vlSelf);
#endif  // VL_DEBUG

void VTestHarness___024root___eval(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            VTestHarness___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-medium/verilog/TestHarness.v", 351602, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VTestHarness___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VTestHarness___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-medium/verilog/TestHarness.v", 351602, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VTestHarness___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-medium/verilog/TestHarness.v", 351602, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VTestHarness___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VTestHarness___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VTestHarness___024root___eval_debug_assertions(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_debug_assertions\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");}
}
#endif  // VL_DEBUG
