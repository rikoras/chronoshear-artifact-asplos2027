// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__0(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__0\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 = 0;
    // Body
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_200 = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__intsource_1__DOT__reg___DOT__reg_) 
                                                   << 0xbU) 
                                                  | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__intsource_2__DOT__reg___DOT__reg_) 
                                                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_seip)) 
                                                      << 9U) 
                                                     | ((0x80U 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__intsource__DOT__reg___DOT__reg_) 
                                                            << 6U)) 
                                                        | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_stip) 
                                                            << 5U) 
                                                           | ((8U 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__intsource__DOT__reg___DOT__reg_) 
                                                                  << 3U)) 
                                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_ssip) 
                                                                 << 1U))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__pending_interrupts 
        = ((QData)((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_200)) 
           & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_rdata 
        = (((0x7a1U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___T_7
             : 0ULL) | ((((0x7a2U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                      >> 0x14U)) ? 
                          (((QData)((IData)(((1U & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_address 
                                                            >> 0x26U)))
                                              ? 0x1ffffffU
                                              : 0U))) 
                            << 0x27U) | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_address)
                           : 0ULL) | ((0x301U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                  >> 0x14U))
                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa
                                       : 0ULL)) | (
                                                   ((0x300U 
                                                     == 
                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                      >> 0x14U))
                                                     ? 
                                                    (0xa00000000ULL 
                                                     | (((QData)((IData)(
                                                                         (3U 
                                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs)))) 
                                                         << 0x3fU) 
                                                        | (QData)((IData)(
                                                                          ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tsr) 
                                                                             << 0x16U) 
                                                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tw) 
                                                                                << 0x15U) 
                                                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tvm) 
                                                                                << 0x14U))) 
                                                                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mxr) 
                                                                               << 0x13U) 
                                                                              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_sum) 
                                                                                << 0x12U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mprv) 
                                                                                << 0x11U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs) 
                                                                                << 0xdU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mpp) 
                                                                                << 0xbU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_spp) 
                                                                                << 8U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mpie) 
                                                                                << 7U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_spie) 
                                                                                << 5U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mie) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_sie) 
                                                                                << 1U)))))))))))))))
                                                     : 0ULL) 
                                                   | (((0x305U 
                                                        == 
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                         >> 0x14U))
                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__read_mtvec
                                                        : 0ULL) 
                                                      | ((QData)((IData)(
                                                                         ((0x344U 
                                                                           == 
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                            >> 0x14U))
                                                                           ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_200)
                                                                           : 0U))) 
                                                         | (((0x304U 
                                                              == 
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                               >> 0x14U))
                                                              ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie
                                                              : 0ULL) 
                                                            | (((0x340U 
                                                                 == 
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                  >> 0x14U))
                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mscratch
                                                                 : 0ULL) 
                                                               | (((0x341U 
                                                                    == 
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                     >> 0x14U))
                                                                    ? 
                                                                   (((QData)((IData)(
                                                                                ((1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_4 
                                                                                >> 0x27U)))
                                                                                 ? 0xffffffU
                                                                                 : 0U))) 
                                                                     << 0x28U) 
                                                                    | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_4)
                                                                    : 0ULL) 
                                                                  | (((0x343U 
                                                                       == 
                                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                        >> 0x14U))
                                                                       ? 
                                                                      (((QData)((IData)(
                                                                                ((1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mtval 
                                                                                >> 0x27U)))
                                                                                 ? 0xffffffU
                                                                                 : 0U))) 
                                                                        << 0x28U) 
                                                                       | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mtval)
                                                                       : 0ULL) 
                                                                     | (((0x342U 
                                                                          == 
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                           >> 0x14U))
                                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcause
                                                                          : 0ULL) 
                                                                        | ((QData)((IData)(
                                                                                ((0x7b0U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0x40000000U 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_ebreakm) 
                                                                                << 0xfU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_ebreaks) 
                                                                                << 0xdU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_ebreaku) 
                                                                                << 0xcU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_cause) 
                                                                                << 6U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_step) 
                                                                                << 2U) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_prv)))))))
                                                                                 : 0U))) 
                                                                           | (((0x7b1U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                ? 
                                                                               (((QData)((IData)(
                                                                                ((1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_6 
                                                                                >> 0x27U)))
                                                                                 ? 0xffffffU
                                                                                 : 0U))) 
                                                                                << 0x28U) 
                                                                                | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_6)
                                                                                : 0ULL) 
                                                                              | (((0x7b2U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dscratch
                                                                                 : 0ULL) 
                                                                                | ((QData)((IData)(
                                                                                ((1U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_fflags)
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((2U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_frm)
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((3U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_frm) 
                                                                                << 5U) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_fflags))
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x320U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit)
                                                                                 : 0U))) 
                                                                                | (((0xb00U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_time
                                                                                 : 0ULL) 
                                                                                | (((0xb02U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value
                                                                                 : 0ULL) 
                                                                                | ((QData)((IData)(
                                                                                ((0x306U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (7U 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcounteren)
                                                                                 : 0U))) 
                                                                                | (((0xc00U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_time
                                                                                 : 0ULL) 
                                                                                | (((0xc02U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value
                                                                                 : 0ULL) 
                                                                                | (((0x100U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0x200000000ULL 
                                                                                | (((QData)((IData)(
                                                                                (3U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs)))) 
                                                                                << 0x3fU) 
                                                                                | (QData)((IData)(
                                                                                (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mxr) 
                                                                                << 0x13U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_sum) 
                                                                                << 0x12U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs) 
                                                                                << 0xdU) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_spp) 
                                                                                << 8U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_spie) 
                                                                                << 5U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_sie) 
                                                                                << 1U))))))))))
                                                                                 : 0ULL) 
                                                                                | (((0x144U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0x222ULL 
                                                                                & ((QData)((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_200)) 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg))
                                                                                 : 0ULL) 
                                                                                | (((0x104U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0x222ULL 
                                                                                & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg))
                                                                                 : 0ULL) 
                                                                                | (((0x140U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_sscratch
                                                                                 : 0ULL) 
                                                                                | (((0x142U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_scause
                                                                                 : 0ULL) 
                                                                                | (((0x143U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (((QData)((IData)(
                                                                                ((1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_stval 
                                                                                >> 0x27U)))
                                                                                 ? 0xffffffU
                                                                                 : 0U))) 
                                                                                << 0x28U) 
                                                                                | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_stval)
                                                                                 : 0ULL) 
                                                                                | (((0x180U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (((QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_satp_mode)) 
                                                                                << 0x3cU) 
                                                                                | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_satp_ppn)
                                                                                 : 0ULL) 
                                                                                | (((0x141U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (((QData)((IData)(
                                                                                ((1U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_8 
                                                                                >> 0x27U)))
                                                                                 ? 0xffffffU
                                                                                 : 0U))) 
                                                                                << 0x28U) 
                                                                                | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_8)
                                                                                 : 0ULL) 
                                                                                | (((0x105U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__read_stvec
                                                                                 : 0ULL) 
                                                                                | ((QData)((IData)(
                                                                                ((0x106U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (7U 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_scounteren)
                                                                                 : 0U))) 
                                                                                | (((0x303U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0x222ULL 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg)
                                                                                 : 0ULL) 
                                                                                | (((0x302U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (0xb15dULL 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_medeleg)
                                                                                 : 0ULL) 
                                                                                | (((0x3a0U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 
                                                                                (((QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l)) 
                                                                                << 0x3fU) 
                                                                                | (((QData)((IData)(
                                                                                (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_a) 
                                                                                << 0x1bU) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_x) 
                                                                                << 0x1aU)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_w) 
                                                                                << 0x19U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_r) 
                                                                                << 0x18U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                                                                                << 0x17U)))) 
                                                                                | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_a) 
                                                                                << 0x13U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_x) 
                                                                                << 0x12U)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_w) 
                                                                                << 0x11U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_r) 
                                                                                << 0x10U))) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                                                                                << 0xfU) 
                                                                                | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_a) 
                                                                                << 0xbU) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_x) 
                                                                                << 0xaU)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_w) 
                                                                                << 9U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_r) 
                                                                                << 8U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_r)))))))))))) 
                                                                                << 0x20U) 
                                                                                | (QData)((IData)(
                                                                                (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                                                                                << 0x1fU) 
                                                                                | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_a) 
                                                                                << 0x1bU) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_x) 
                                                                                << 0x1aU)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_w) 
                                                                                << 0x19U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_r) 
                                                                                << 0x18U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                                                                                << 0x17U)))) 
                                                                                | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_a) 
                                                                                << 0x13U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_x) 
                                                                                << 0x12U)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_w) 
                                                                                << 0x11U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_r) 
                                                                                << 0x10U))) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                                                                                << 0xfU) 
                                                                                | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_a) 
                                                                                << 0xbU) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_x) 
                                                                                << 0xaU)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_w) 
                                                                                << 9U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_r) 
                                                                                << 8U) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l) 
                                                                                << 7U) 
                                                                                | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_a) 
                                                                                << 3U) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_x) 
                                                                                << 2U)) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_w) 
                                                                                << 1U) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_r)))))))))))))))
                                                                                 : 0ULL) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b0U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b1U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b2U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b3U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b4U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b5U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b6U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_addr
                                                                                 : 0U))) 
                                                                                | ((QData)((IData)(
                                                                                ((0x3b7U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_addr
                                                                                 : 0U))) 
                                                                                | (((0x7c1U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_custom_0
                                                                                 : 0ULL) 
                                                                                | (((0xf12U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 1ULL
                                                                                 : 0ULL) 
                                                                                | ((0xf13U 
                                                                                == 
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                                                >> 0x14U))
                                                                                 ? 0x20181004ULL
                                                                                 : 0ULL))))))))))))))))))))))))))))))))))))))))))))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
        = (0x222ULL & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__pending_interrupts 
                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
        = (~ ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__pending_interrupts) 
              | (0x222ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
        = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___wdata_T_6 
           & (((2U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_cmd))
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_rdata
                : 0ULL) | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_wdata));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_MPORT_data 
        = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_tag) 
                >> 1U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__dmem_resp_valid))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_resp_bits_data
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen)
                ? (((QData)((IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__req_dw)
                                      ? (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__result 
                                                 >> 0x20U))
                                      : ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__loOut 
                                          >> 0x1fU)
                                          ? 0xffffffffU
                                          : 0U)))) 
                    << 0x20U) | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__loOut)))
                : ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_csr))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_wdata
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_rdata)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_77 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 0xfU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_76 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 0xeU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 0xdU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_74 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 0xcU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_73 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 0xbU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_72 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_71 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 7U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 9U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_69 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_68 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 5U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_67 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                      >> 8U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_66 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
           & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_90 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 0xfU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_89 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 0xeU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_88 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 0xdU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_87 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 0xcU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_86 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 0xbU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_85 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_84 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 7U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_83 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 9U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_82 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_81 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 5U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 8U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_79 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_78 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_8) 
           & (IData)((TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___m_interrupts_T_5 
                      >> 4U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_misa_T_8 
        = ((0x102dULL & (~ ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata) 
                            | (QData)((IData)((8U & 
                                               ((~ (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                                            >> 5U))) 
                                                << 3U))))))) 
           | (0xffffffffffffefd2ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_custom_0_T_3 
        = ((0x208ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata) 
           | (0xfffffffffffffdf7ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_custom_0));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_430 
            = ((0x306U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcounteren)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_429 
            = ((0x106U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_scounteren)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_424 
            = ((0x105U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_stvec);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_412 
            = ((3U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                       >> 0x14U)) ? VL_SHIFTR_QQI(64,64,32, vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata, 5U)
                : ((2U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                    : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_frm))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_432 
            = ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode)) 
                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)))
                ? ((0x7a2U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                               >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_address)
                : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_address);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_512 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_41))) 
                & (0x3b6U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_519 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l) 
                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_41))) 
                & (0x3b7U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_470 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_a)))))) 
                & (0x3b0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_477 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_a)))))) 
                & (0x3b1U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_484 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_a)))))) 
                & (0x3b2U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_491 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_a)))))) 
                & (0x3b3U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_498 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_a)))))) 
                & (0x3b4U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_addr)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_505 
            = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l) 
                       & (IData)((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_a)))))) 
                & (0x3b5U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                              >> 0x14U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_addr)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_430 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcounteren));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_429 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_scounteren));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_424 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_stvec;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_412 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_frm));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_432 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_address;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_512 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_519 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_470 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_477 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_484 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_491 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_498 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_addr));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_505 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_addr));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_sip_T_2 
        = (0x222ULL & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_wen) {
        if ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_0 
                = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_waddr) 
                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_MPORT_data
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_data);
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_1 
                = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_waddr) 
                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_MPORT_data
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_1_data);
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_data;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_1 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_1_data;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_data;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_rs_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_1_data;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_interrupt 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__io_status_cease_r) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug))) 
           & (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_singleStep)) 
               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__intsink__DOT__chain__DOT__output_chain__DOT__sync_0) 
                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_90) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_89) 
                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_88) 
                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_87))))) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_86) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_85) 
                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_84) 
                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_83) 
                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_82) 
                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_81) 
                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80) 
                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_79) 
                                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_78) 
                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_77) 
                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_76) 
                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_75) 
                                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_74) 
                                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_73) 
                                                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_72))))))))))))))) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_71) 
                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70) 
                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_69) 
                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_68) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_67) 
                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_66) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
                                          & (IData)(
                                                    (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___s_interrupts_T_5 
                                                     >> 4U)))))))))))) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_singleStepped)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_mie_T_4 
        = (((~ (0x222ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg)) 
            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie) 
           | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_sip_T_2);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_xcpt 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__bpu_io_debug_if) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_interrupt) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__bpu_io_xcpt_if) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_xcpt0_pf_inst) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_xcpt0_ae_inst) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_xcpt1_pf_inst) 
                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_xcpt1_ae_inst) 
                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_illegal_insn))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killd 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_valid)) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_replay) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_stalld) 
                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_interrupt))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killd)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_ctrl_decoder_1));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__16(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__16\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__sink_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__1(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__1\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_0;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_4;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_4 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_0;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_4;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_4 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_8;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_8 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_12;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_12 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_16;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_16 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_20;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_20 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_24;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_24 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_28;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_28 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_32;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_32 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_36;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_36 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_40;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_40 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_44;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_44 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_48;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_48 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_52;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_52 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_56;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_56 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_60;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_60 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321 = 0;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumereq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg) 
            >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink_io_deq_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_1) 
           & (0x40000000000000ULL == (0x70000000000000ULL 
                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321 
        = ((4U != (7U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                 >> 0x34U)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeAcks 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumereq)
                  ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeReqRegs)) 
                     & (0U != (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg) 
                                         >> 4U)))) : 
                 (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeReqRegs))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F96 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_320));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F0 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_319));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F31 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_318));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F23 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_317));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F35 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_316));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F78 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_315));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F91 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_314));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F11 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_313));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F19 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_312));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F74 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_311));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F86 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_310));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F27 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_309));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F4 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_308));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F82 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_307));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F70 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_306));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F39 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_305));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F15 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_304));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F100 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_9) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_303));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_65 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(((0x80400000000ULL == (0x280400000000ULL 
                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg)) 
                      & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                         >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_90 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & ((IData)(((0x80000000000ULL == (0x280000000000ULL 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg)) 
                       & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                          >> 7U))) & ((0xffU == ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                             >> 0x24U)))
                                                  ? 0xffU
                                                  : 0U)) 
                                      & ((0xffU == 
                                          ((1U & (IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                          >> 0x23U)))
                                            ? 0xffU
                                            : 0U)) 
                                         & ((0xffU 
                                             == ((1U 
                                                  & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                             >> 0x22U)))
                                                  ? 0xffU
                                                  : 0U)) 
                                            & (0xffU 
                                               == (
                                                   (1U 
                                                    & (IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                               >> 0x21U)))
                                                    ? 0xffU
                                                    : 0U)))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F8 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(((0x80000000000ULL == (0x280000000000ULL 
                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg)) 
                      & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                         >> 8U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F96 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_320));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F0 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_319));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F31 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_318));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F23 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_317));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F35 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_316));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F78 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_315));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F91 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_314));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F11 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_313));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F19 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_312));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F74 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_311));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F86 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_310));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F27 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_309));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F4 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_308));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F82 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_307));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F70 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_306));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F39 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_305));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F15 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_304));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F100 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_321) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_303));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner_auto_dmi_in_d_bits_data 
        = (((0x1fU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
             ? (0U == (0x50U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                        >> 0x27U))))
             : ((0x1eU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                 ? (0U == (0x50U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                            >> 0x27U))))
                 : ((0x1dU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                     ? (0U == (0x50U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                >> 0x27U))))
                     : ((0x1cU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                         ? (0U == (0x50U & (IData)(
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                    >> 0x27U))))
                         : ((0x1bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                             ? (0U == (0x50U & (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                        >> 0x27U))))
                             : ((0x1aU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                 ? (0U == (0x50U & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                            >> 0x27U))))
                                 : ((0x19U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                     ? (0U == (0x50U 
                                               & (IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                          >> 0x27U))))
                                     : ((0x18U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                         ? (0U == (0x50U 
                                                   & (IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                              >> 0x27U))))
                                         : ((0x17U 
                                             == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                             ? (0U 
                                                == 
                                                (0x50U 
                                                 & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                            >> 0x27U))))
                                             : ((0x16U 
                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                 ? 
                                                (0U 
                                                 == 
                                                 (0x50U 
                                                  & (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                             >> 0x27U))))
                                                 : 
                                                ((0x15U 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                  ? 
                                                 (0U 
                                                  == 
                                                  (0x50U 
                                                   & (IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                              >> 0x27U))))
                                                  : 
                                                 ((0x14U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                   ? 
                                                  (0U 
                                                   == 
                                                   (0x50U 
                                                    & (IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                               >> 0x27U))))
                                                   : 
                                                  ((0x13U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                    ? 
                                                   (0U 
                                                    == 
                                                    (0x50U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                >> 0x27U))))
                                                    : 
                                                   ((0x12U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                     ? 
                                                    (0U 
                                                     == 
                                                     (0x50U 
                                                      & (IData)(
                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                 >> 0x27U))))
                                                     : 
                                                    ((0x11U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                      ? 
                                                     (0U 
                                                      == 
                                                      (0x50U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                  >> 0x27U))))
                                                      : 
                                                     ((0x10U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                       ? 
                                                      (0U 
                                                       == 
                                                       (0x50U 
                                                        & (IData)(
                                                                  (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                   >> 0x27U))))
                                                       : 
                                                      ((0xfU 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                       | ((0xeU 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                          | ((0xdU 
                                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                             | ((0xcU 
                                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                                | ((0xbU 
                                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                                   | ((0xaU 
                                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                                      | ((9U 
                                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                                         | ((8U 
                                                                             == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                             ? 
                                                                            (0x10U 
                                                                             == 
                                                                             (0x50U 
                                                                              & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                             : 
                                                                            ((7U 
                                                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                              ? 
                                                                             (0x10U 
                                                                              == 
                                                                              (0x50U 
                                                                               & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                              : 
                                                                             ((6U 
                                                                               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                               ? 
                                                                              (0x10U 
                                                                               == 
                                                                               (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                               : 
                                                                              ((5U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                                ? 
                                                                               (0U 
                                                                                == 
                                                                                (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                                : 
                                                                               ((4U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                                 ? 
                                                                                (0x10U 
                                                                                == 
                                                                                (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex)) 
                                                                                | ((1U 
                                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                                 ? 
                                                                                (0x10U 
                                                                                == 
                                                                                (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U))))
                                                                                 : 
                                                                                (0x40U 
                                                                                == 
                                                                                (0x50U 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x27U)))))))))))))))))))))))))))))))))))
            ? ((0x1fU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                ? ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_63) 
                     << 0x18U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_62) 
                                  << 0x10U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_61) 
                                                 << 8U) 
                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_60)))
                : ((0x1eU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_13
                    : ((0x1dU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                        ? ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_55) 
                             << 0x18U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_54) 
                                          << 0x10U)) 
                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_53) 
                               << 8U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_52)))
                        : ((0x1cU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_58
                            : ((0x1bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                ? ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_47) 
                                     << 0x18U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_46) 
                                                  << 0x10U)) 
                                   | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_45) 
                                       << 8U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_44)))
                                : ((0x1aU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_5
                                    : ((0x19U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                        ? ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_39) 
                                             << 0x18U) 
                                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_38) 
                                               << 0x10U)) 
                                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_37) 
                                               << 8U) 
                                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_36)))
                                        : ((0x18U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_70
                                            : ((0x17U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                ? (
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_31) 
                                                     << 0x18U) 
                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_30) 
                                                       << 0x10U)) 
                                                   | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_29) 
                                                       << 8U) 
                                                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_28)))
                                                : (
                                                   (0x16U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_16
                                                    : 
                                                   ((0x15U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                     ? 
                                                    ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_23) 
                                                       << 0x18U) 
                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_22) 
                                                         << 0x10U)) 
                                                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_21) 
                                                         << 8U) 
                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_20)))
                                                     : 
                                                    ((0x14U 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_73
                                                      : 
                                                     ((0x13U 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                       ? 
                                                      ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_15) 
                                                         << 0x18U) 
                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_14) 
                                                           << 0x10U)) 
                                                       | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_13) 
                                                           << 8U) 
                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_12)))
                                                       : 
                                                      ((0x12U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_28
                                                        : 
                                                       ((0x11U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                         ? 
                                                        ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_7) 
                                                           << 0x18U) 
                                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_6) 
                                                             << 0x10U)) 
                                                         | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_5) 
                                                             << 8U) 
                                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_4)))
                                                         : 
                                                        ((0x10U 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_25
                                                          : 
                                                         ((0xfU 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                           ? 0U
                                                           : 
                                                          ((0xeU 
                                                            == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                            ? 0U
                                                            : 
                                                           ((0xdU 
                                                             == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                             ? 0U
                                                             : 
                                                            ((0xcU 
                                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                              ? 0U
                                                              : 
                                                             ((0xbU 
                                                               == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                               ? 0U
                                                               : 
                                                              ((0xaU 
                                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                ? 0U
                                                                : 
                                                               ((9U 
                                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                 ? 0U
                                                                 : 
                                                                ((8U 
                                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                  ? 
                                                                 (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                   << 0x10U) 
                                                                  | (3U 
                                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecdata)))
                                                                  : 
                                                                 ((7U 
                                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                   ? 
                                                                  (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDRdData_cmdtype) 
                                                                    << 0x18U) 
                                                                   | vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDRdData_control)
                                                                   : 
                                                                  ((6U 
                                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                    ? 
                                                                   (0x10000002U 
                                                                    | (((0U 
                                                                         != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)) 
                                                                        << 0xcU) 
                                                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTCSReg_cmderr) 
                                                                          << 8U)))
                                                                    : 
                                                                   ((5U 
                                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                     ? 
                                                                    ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_7) 
                                                                       << 0x18U) 
                                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_6) 
                                                                         << 0x10U)) 
                                                                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_5) 
                                                                         << 8U) 
                                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_4)))
                                                                     : 
                                                                    ((4U 
                                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_76
                                                                      : 
                                                                     ((3U 
                                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs)
                                                                       : 
                                                                      ((2U 
                                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                        ? 0U
                                                                        : 
                                                                       ((1U 
                                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_iindex))
                                                                         ? 
                                                                        (0xa2U 
                                                                         | ((0xc0000U 
                                                                             & ((- (IData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haveResetBitRegs))) 
                                                                                << 0x12U)) 
                                                                            | ((0x30000U 
                                                                                & ((- (IData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__resumeAcks))) 
                                                                                << 0x10U)) 
                                                                               | ((0x800U 
                                                                                & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs)) 
                                                                                << 0xbU)) 
                                                                                | ((0x400U 
                                                                                & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs)) 
                                                                                << 0xaU)) 
                                                                                | (0x300U 
                                                                                & ((- (IData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs))) 
                                                                                << 8U)))))))
                                                                         : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__haltedBitRegs))))))))))))))))))))))))))))))))
            : 0U);
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_38 
        = (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)) 
            & ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)) 
               & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__commandRegIsUnsupported)) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__commandRegBadHaltResume))))
            ? 4U : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_65) 
                     & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)))
                     ? ((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                    >> 9U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTCSReg_cmderr))
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTCSReg_cmderr)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_90) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrEn 
            = (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg));
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrData_cmdtype 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                >> 0x19U)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrEn = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrData_cmdtype = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_8 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F8) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_10 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F8) 
           & ((0xffU == ((1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                        >> 0x24U)))
                          ? 0xffU : 0U)) & (0xffU == 
                                            ((1U & (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                            >> 0x23U)))
                                              ? 0xffU
                                              : 0U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_97 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F96) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_98 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F96) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_99 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F96) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_96 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F96) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F0) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F0) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_3 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F0) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F0) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_32 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F31) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_33 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F31) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_34 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F31) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_31 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F31) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_24 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F23) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_25 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F23) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_26 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F23) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_23 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F23) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_36 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F35) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_37 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F35) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_38 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F35) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_35 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F35) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_79 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F78) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_80 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F78) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_81 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F78) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_78 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F78) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_92 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F91) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_93 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F91) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_94 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F91) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_91 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F91) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_12 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F11) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_13 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F11) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_14 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F11) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_11 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F11) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_20 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F19) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_21 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F19) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_22 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F19) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_19 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F19) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_75 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F74) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_76 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F74) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_77 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F74) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_74 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F74) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_87 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F86) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_88 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F86) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_89 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F86) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_86 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F86) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_28 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F27) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_29 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F27) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_30 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F27) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_27 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F27) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_5 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F4) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_6 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F4) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_7 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F4) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F4) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_83 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F82) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_84 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F82) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_85 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F82) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_82 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F82) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_71 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F70) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_72 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F70) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_73 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F70) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_70 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F70) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_40 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F39) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_41 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F39) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_42 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F39) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_39 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F39) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_16 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F15) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_17 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F15) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_18 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F15) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_15 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F15) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_101 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F100) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x22U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_102 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F100) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x23U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_103 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F100) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x24U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_100 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready___05F100) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                      >> 0x21U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__wrAccessRegisterCommand 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrEn) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDWrData_cmdtype)) 
              & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTCSReg_cmderr))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_96) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F96) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F0) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_31) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F31) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_23) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F23) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_8 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_35) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F35) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_12 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_78) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F78) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_16 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_91) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F91) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_20 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_11) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F11) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_24 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_19) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F19) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_28 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_74) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F74) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_32 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_86) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F86) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_36 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_27) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F27) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_40 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_4) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F4) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_44 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_82) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F82) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_48 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_70) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F70) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_52 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_39) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F39) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_56 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_15) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F15) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_60 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_100) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F100) 
              & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                         >> 0x21U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__autoexec 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecdata)) 
           | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_4) 
               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecdata) 
                  >> 1U)) | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_0) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf)) 
                             | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_4) 
                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                    >> 1U)) | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_8) 
                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                   >> 2U)) 
                                               | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_12) 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                      >> 3U)) 
                                                  | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_16) 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                         >> 4U)) 
                                                     | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_20) 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                            >> 5U)) 
                                                        | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_24) 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                               >> 6U)) 
                                                           | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_28) 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                  >> 7U)) 
                                                              | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_32) 
                                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                     >> 8U)) 
                                                                 | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_36) 
                                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                        >> 9U)) 
                                                                    | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_40) 
                                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                           >> 0xaU)) 
                                                                       | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_44) 
                                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                              >> 0xbU)) 
                                                                          | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_48) 
                                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                                >> 0xcU)) 
                                                                             | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_52) 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                                >> 0xdU)) 
                                                                                | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_56) 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                                >> 0xeU)) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_60) 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTAUTOReg_autoexecprogbuf) 
                                                                                >> 0xfU)))))))))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__errorBusy 
        = ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_65) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_8) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_10) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_90) 
                       | (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_0) 
                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_97) 
                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F96) 
                                  & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                             >> 0x22U)))) 
                              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_98) 
                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F96) 
                                     & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                >> 0x23U)))) 
                                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_99) 
                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F96) 
                                        & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                   >> 0x24U)))) 
                                    | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiAbstractDataAccessVec_4) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_1) 
                                          | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F0) 
                                              & (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                         >> 0x22U))) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_2) 
                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F0) 
                                                    & (IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                               >> 0x23U))) 
                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_3) 
                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F0) 
                                                         & (IData)(
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                    >> 0x24U))))))))))))) 
                          | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_0) 
                             | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_32) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F31) 
                                    & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                               >> 0x22U)))) 
                                | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_33) 
                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F31) 
                                         & (IData)(
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                    >> 0x23U)))) 
                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_34) 
                                        | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F31) 
                                            & (IData)(
                                                      (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                       >> 0x24U))) 
                                           | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_4) 
                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_24) 
                                                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F23) 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                >> 0x22U))) 
                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_25) 
                                                       | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F23) 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                      >> 0x23U))) 
                                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_26) 
                                                             | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F23) 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                            >> 0x24U))) 
                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_8) 
                                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_36) 
                                                                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F35) 
                                                                          & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_37) 
                                                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F35) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_38) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F35) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_12) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_79) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F78) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_80) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F78) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_81) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F78) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_16) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_92) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F91) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_93) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F91) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_94) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F91) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_20) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_12) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F11) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_13) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F11) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_14) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F11) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_24) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_20) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F19) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_21) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F19) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_22) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F19) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_28) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_75) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F74) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_76) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F74) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U)))))))))))))))))))))))))))))))))))))))))))))))))))) 
                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_77) 
                                       | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F74) 
                                           & (IData)(
                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                      >> 0x24U))) 
                                          | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_32) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_87) 
                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F86) 
                                                    & (IData)(
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                               >> 0x22U))) 
                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_88) 
                                                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F86) 
                                                          & (IData)(
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                     >> 0x23U))) 
                                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_89) 
                                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F86) 
                                                                & (IData)(
                                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                           >> 0x24U))) 
                                                               | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_36) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_28) 
                                                                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F27) 
                                                                         & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_29) 
                                                                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F27) 
                                                                               & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_30) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F27) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_40) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_5) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F4) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_6) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F4) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_7) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F4) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_44) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_83) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F82) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_84) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F82) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_85) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F82) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_48) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_71) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F70) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_72) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F70) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_73) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F70) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_52) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_40) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F39) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_41) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F39) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_42) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F39) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_56) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_16) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F15) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x22U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_17) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F15) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x23U))) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_18) 
                                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F15) 
                                                                                & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                                >> 0x24U))) 
                                                                                | (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__dmiProgramBufferAccessVec_60))))))))))))))))))))))))))))))))))))))))))))))))))))) 
                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_101) 
                                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F100) 
                                          & (IData)(
                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                     >> 0x22U))) 
                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_102) 
                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F100) 
                                                & (IData)(
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                           >> 0x23U))) 
                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_103) 
                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_roready___05F100) 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                                                >> 0x24U)))))))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__regAccessRegisterCommand 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__autoexec) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__COMMANDRdData_cmdtype)) 
              & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ABSTRACTCSReg_cmderr))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__17(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__17\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__hrmaskReg_0 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__hrmaskReg_0;
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLReg_dmactive 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLReg_dmactive;
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut_reset_reg__DOT__reg_) 
           | (IData)(vlSelfRef.reset));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__widx_gray 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0) 
                                                   && (1U 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__widx_widx_bin) 
                                                          + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT___widx_T_1)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__widx_gray 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0) 
                                                   && (1U 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__widx_widx_bin) 
                                                          + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT__a_first_done)))));
    vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_1));
    vlSelfRef.__VdfgRegularize_hd87f99a1_4_0 = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLReg_dmactive) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmactiveAck_dmactiveAckSync__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__widx_widx_bin 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__widx_widx_bin;
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__widx_widx_bin 
        = vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__widx_widx_bin;
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source_io_enq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__ready_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source_io_enq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__ready_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__18(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__18\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__source_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleIn_0_d_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__2(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__2\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*31:0*/ __Vdeeptemp_h9317c8e4__0;
    CData/*31:0*/ __Vdeeptemp_hf1e61f59__0;
    QData/*63:0*/ __Vdeeptemp_h897aaade__0;
    QData/*63:0*/ __Vdeeptemp_hb98ca724__0;
    CData/*31:0*/ __Vdeeptemp_h6d57d9b5__0;
    QData/*63:0*/ __Vdeeptemp_hc0537470__0;
    // Body
    __Vdeeptemp_h9317c8e4__0 = ((0x7fU == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U))) 
                                | ((0x7eU == (0xffU 
                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                 >> 3U))) 
                                   | ((0x7dU == (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U))) 
                                      | ((0x7cU == 
                                          (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U))) 
                                         | ((0x7bU 
                                             == (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U))) 
                                            | ((0x7aU 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U))) 
                                               | ((0x79U 
                                                   == 
                                                   (0xffU 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U))) 
                                                  | ((0x78U 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U))) 
                                                     | ((0x77U 
                                                         == 
                                                         (0xffU 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U))) 
                                                        | ((0x76U 
                                                            == 
                                                            (0xffU 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U))) 
                                                           | ((0x75U 
                                                               == 
                                                               (0xffU 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                   >> 3U))) 
                                                              | ((0x74U 
                                                                  == 
                                                                  (0xffU 
                                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                      >> 3U))) 
                                                                 | ((0x73U 
                                                                     == 
                                                                     (0xffU 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                         >> 3U))) 
                                                                    | ((0x72U 
                                                                        == 
                                                                        (0xffU 
                                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                            >> 3U))) 
                                                                       | ((0x71U 
                                                                           == 
                                                                           (0xffU 
                                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                               >> 3U))) 
                                                                          | ((0x70U 
                                                                              == 
                                                                              (0xffU 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              ? 
                                                                             (0U 
                                                                              == 
                                                                              (0x100U 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              : 
                                                                             ((0x6fU 
                                                                               == 
                                                                               (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               ? 
                                                                              (0U 
                                                                               == 
                                                                               (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               : 
                                                                              ((0x6eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                ? 
                                                                               (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                : 
                                                                               ((0x6dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x6cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x6bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x6aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x69U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x68U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x67U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x66U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x65U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x64U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x63U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x62U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x61U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x60U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x5fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x5eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x5dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x5cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x5bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x5aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x59U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x58U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x57U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x56U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x55U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x54U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x53U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x52U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x51U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x50U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x4aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x49U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x48U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x47U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x46U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x45U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x44U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x43U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x42U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x41U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x40U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x3aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x39U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x38U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x37U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x36U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x35U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x34U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x33U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x32U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x31U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x30U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x2aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x29U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x28U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x27U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x26U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x25U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x24U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x23U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x22U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x21U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x20U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x1eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x1dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x1cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x1bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x1aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x19U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x18U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x17U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x16U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x15U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x14U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x13U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x12U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x11U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0x10U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0xfU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0xeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0xdU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0xcU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | ((0xbU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))) 
                                                                                | (0x100U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h6d57d9b5__0 = ((0xf4U == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 ? (0U == (0x100U & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 : ((0xf3U == (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     ? (0U == (0x100U 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     : ((0xf2U == (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         ? (0U == (0x100U 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         : ((0xf1U 
                                             == (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                                             ? (0U 
                                                == 
                                                (0x100U 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                                             : ((0xf0U 
                                                 == 
                                                 (0xffU 
                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                     >> 3U)))
                                                 ? 
                                                (0U 
                                                 == 
                                                 (0x100U 
                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                     >> 3U)))
                                                 : 
                                                ((0xefU 
                                                  == 
                                                  (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                                  ? 
                                                 (0U 
                                                  == 
                                                  (0x100U 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                                  : 
                                                 ((0xeeU 
                                                   == 
                                                   (0xffU 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   ? 
                                                  (0U 
                                                   == 
                                                   (0x100U 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   : 
                                                  ((0xedU 
                                                    == 
                                                    (0xffU 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    ? 
                                                   (0U 
                                                    == 
                                                    (0x100U 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    : 
                                                   ((0xecU 
                                                     == 
                                                     (0xffU 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     ? 
                                                    (0U 
                                                     == 
                                                     (0x100U 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     : 
                                                    ((0xebU 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      ? 
                                                     (0U 
                                                      == 
                                                      (0x100U 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      : 
                                                     ((0xeaU 
                                                       == 
                                                       (0xffU 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       ? 
                                                      (0U 
                                                       == 
                                                       (0x100U 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       : 
                                                      ((0xe9U 
                                                        == 
                                                        (0xffU 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                            >> 3U)))
                                                        ? 
                                                       (0U 
                                                        == 
                                                        (0x100U 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                            >> 3U)))
                                                        : 
                                                       ((0xe8U 
                                                         == 
                                                         (0xffU 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U)))
                                                         ? 
                                                        (0U 
                                                         == 
                                                         (0x100U 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U)))
                                                         : 
                                                        ((0xe7U 
                                                          == 
                                                          (0xffU 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                              >> 3U)))
                                                          ? 
                                                         (0U 
                                                          == 
                                                          (0x100U 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                              >> 3U)))
                                                          : 
                                                         ((0xe6U 
                                                           == 
                                                           (0xffU 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                               >> 3U)))
                                                           ? 
                                                          (0U 
                                                           == 
                                                           (0x100U 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                               >> 3U)))
                                                           : 
                                                          ((0xe5U 
                                                            == 
                                                            (0xffU 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U)))
                                                            ? 
                                                           (0U 
                                                            == 
                                                            (0x100U 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U)))
                                                            : 
                                                           ((0xe4U 
                                                             == 
                                                             (0xffU 
                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                 >> 3U)))
                                                             ? 
                                                            (0U 
                                                             == 
                                                             (0x100U 
                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                 >> 3U)))
                                                             : 
                                                            ((0xe3U 
                                                              == 
                                                              (0xffU 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                  >> 3U)))
                                                              ? 
                                                             (0U 
                                                              == 
                                                              (0x100U 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                  >> 3U)))
                                                              : 
                                                             ((0xe2U 
                                                               == 
                                                               (0xffU 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                   >> 3U)))
                                                               ? 
                                                              (0U 
                                                               == 
                                                               (0x100U 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                   >> 3U)))
                                                               : 
                                                              ((0xe1U 
                                                                == 
                                                                (0xffU 
                                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                    >> 3U)))
                                                                ? 
                                                               (0U 
                                                                == 
                                                                (0x100U 
                                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                    >> 3U)))
                                                                : 
                                                               ((0xe0U 
                                                                 == 
                                                                 (0xffU 
                                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                     >> 3U)))
                                                                 ? 
                                                                (0U 
                                                                 == 
                                                                 (0x100U 
                                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                     >> 3U)))
                                                                 : 
                                                                ((0xdfU 
                                                                  == 
                                                                  (0xffU 
                                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                      >> 3U)))
                                                                  ? 
                                                                 (0U 
                                                                  == 
                                                                  (0x100U 
                                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                      >> 3U)))
                                                                  : 
                                                                 ((0xdeU 
                                                                   == 
                                                                   (0xffU 
                                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                       >> 3U)))
                                                                   ? 
                                                                  (0U 
                                                                   == 
                                                                   (0x100U 
                                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                       >> 3U)))
                                                                   : 
                                                                  ((0xddU 
                                                                    == 
                                                                    (0xffU 
                                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                        >> 3U)))
                                                                    ? 
                                                                   (0U 
                                                                    == 
                                                                    (0x100U 
                                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                        >> 3U)))
                                                                    : 
                                                                   ((0xdcU 
                                                                     == 
                                                                     (0xffU 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                         >> 3U)))
                                                                     ? 
                                                                    (0U 
                                                                     == 
                                                                     (0x100U 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                         >> 3U)))
                                                                     : 
                                                                    ((0xdbU 
                                                                      == 
                                                                      (0xffU 
                                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                          >> 3U)))
                                                                      ? 
                                                                     (0U 
                                                                      == 
                                                                      (0x100U 
                                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                          >> 3U)))
                                                                      : 
                                                                     ((0xdaU 
                                                                       == 
                                                                       (0xffU 
                                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                           >> 3U)))
                                                                       ? 
                                                                      (0U 
                                                                       == 
                                                                       (0x100U 
                                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                           >> 3U)))
                                                                       : 
                                                                      ((0xd9U 
                                                                        == 
                                                                        (0xffU 
                                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                            >> 3U)))
                                                                        ? 
                                                                       (0U 
                                                                        == 
                                                                        (0x100U 
                                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                            >> 3U)))
                                                                        : 
                                                                       ((0xd8U 
                                                                         == 
                                                                         (0xffU 
                                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                             >> 3U)))
                                                                         ? 
                                                                        (0U 
                                                                         == 
                                                                         (0x100U 
                                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                             >> 3U)))
                                                                         : 
                                                                        ((0xd7U 
                                                                          == 
                                                                          (0xffU 
                                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                              >> 3U)))
                                                                          ? 
                                                                         (0U 
                                                                          == 
                                                                          (0x100U 
                                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                              >> 3U)))
                                                                          : 
                                                                         ((0xd6U 
                                                                           == 
                                                                           (0xffU 
                                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                               >> 3U)))
                                                                           ? 
                                                                          (0U 
                                                                           == 
                                                                           (0x100U 
                                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                               >> 3U)))
                                                                           : 
                                                                          ((0xd5U 
                                                                            == 
                                                                            (0xffU 
                                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                            ? 
                                                                           (0U 
                                                                            == 
                                                                            (0x100U 
                                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                            : 
                                                                           ((0xd4U 
                                                                             == 
                                                                             (0xffU 
                                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                             ? 
                                                                            (0U 
                                                                             == 
                                                                             (0x100U 
                                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                             : 
                                                                            ((0xd3U 
                                                                              == 
                                                                              (0xffU 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              ? 
                                                                             (0U 
                                                                              == 
                                                                              (0x100U 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              : 
                                                                             ((0xd2U 
                                                                               == 
                                                                               (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               ? 
                                                                              (0U 
                                                                               == 
                                                                               (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               : 
                                                                              ((0xd1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                ? 
                                                                               (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                : 
                                                                               ((0xd0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xcfU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xceU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xcdU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xccU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xafU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xadU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xacU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xabU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x99U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x98U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x97U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x96U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x95U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x94U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x93U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x92U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x91U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x90U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x89U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x88U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x87U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x86U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x85U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x84U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x83U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x82U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x81U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : 
                                                                                ((0x80U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 
                                                                                (0U 
                                                                                == 
                                                                                (0x100U 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 : __Vdeeptemp_h9317c8e4__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_hf1e61f59__0 = ((0xf7U == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 ? (0U == (0x100U & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 : ((0xf6U == (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     ? (0U == (0x100U 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     : ((0xf5U == (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         ? (0U == (0x100U 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         : __Vdeeptemp_h6d57d9b5__0)));
    __Vdeeptemp_h897aaade__0 = ((0x75U == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 ? 0ULL : ((0x74U == 
                                            (0xffU 
                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                >> 3U)))
                                            ? 0ULL : 
                                           ((0x73U 
                                             == (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                                             ? 0ULL
                                             : ((0x72U 
                                                 == 
                                                 (0xffU 
                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                     >> 3U)))
                                                 ? 0ULL
                                                 : 
                                                ((0x71U 
                                                  == 
                                                  (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                                  ? 0ULL
                                                  : 
                                                 ((0x70U 
                                                   == 
                                                   (0xffU 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   ? 
                                                  (((QData)((IData)(
                                                                    ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_7) 
                                                                       << 0x18U) 
                                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_6) 
                                                                         << 0x10U)) 
                                                                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_5) 
                                                                         << 8U) 
                                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractDataMem_4))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_76)))
                                                   : 
                                                  ((0x6fU 
                                                    == 
                                                    (0xffU 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    ? 
                                                   (((QData)((IData)(
                                                                     ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_63) 
                                                                        << 0x18U) 
                                                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_62) 
                                                                          << 0x10U)) 
                                                                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_61) 
                                                                          << 8U) 
                                                                         | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_60))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_13)))
                                                    : 
                                                   ((0x6eU 
                                                     == 
                                                     (0xffU 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     ? 
                                                    (((QData)((IData)(
                                                                      ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_55) 
                                                                         << 0x18U) 
                                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_54) 
                                                                           << 0x10U)) 
                                                                       | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_53) 
                                                                           << 8U) 
                                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_52))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_58)))
                                                     : 
                                                    ((0x6dU 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      ? 
                                                     (((QData)((IData)(
                                                                       ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_47) 
                                                                          << 0x18U) 
                                                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_46) 
                                                                            << 0x10U)) 
                                                                        | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_45) 
                                                                            << 8U) 
                                                                           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_44))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_5)))
                                                      : 
                                                     ((0x6cU 
                                                       == 
                                                       (0xffU 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       ? 
                                                      (((QData)((IData)(
                                                                        ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_39) 
                                                                           << 0x18U) 
                                                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_38) 
                                                                             << 0x10U)) 
                                                                         | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_37) 
                                                                             << 8U) 
                                                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_36))))) 
                                                        << 0x20U) 
                                                       | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_70)))
                                                       : 
                                                      ((0x6bU 
                                                        == 
                                                        (0xffU 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                            >> 3U)))
                                                        ? 
                                                       (((QData)((IData)(
                                                                         ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_31) 
                                                                            << 0x18U) 
                                                                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_30) 
                                                                              << 0x10U)) 
                                                                          | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_29) 
                                                                              << 8U) 
                                                                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_28))))) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_16)))
                                                        : 
                                                       ((0x6aU 
                                                         == 
                                                         (0xffU 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U)))
                                                         ? 
                                                        (((QData)((IData)(
                                                                          ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_23) 
                                                                             << 0x18U) 
                                                                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_22) 
                                                                               << 0x10U)) 
                                                                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_21) 
                                                                               << 8U) 
                                                                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_20))))) 
                                                          << 0x20U) 
                                                         | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_73)))
                                                         : 
                                                        ((0x69U 
                                                          == 
                                                          (0xffU 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                              >> 3U)))
                                                          ? 
                                                         (((QData)((IData)(
                                                                           ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_15) 
                                                                              << 0x18U) 
                                                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_14) 
                                                                                << 0x10U)) 
                                                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_13) 
                                                                                << 8U) 
                                                                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_12))))) 
                                                           << 0x20U) 
                                                          | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_28)))
                                                          : 
                                                         ((0x68U 
                                                           == 
                                                           (0xffU 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                               >> 3U)))
                                                           ? 
                                                          (((QData)((IData)(
                                                                            ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_7) 
                                                                               << 0x18U) 
                                                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_6) 
                                                                                << 0x10U)) 
                                                                             | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_5) 
                                                                                << 8U) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__programBufferMem_4))))) 
                                                            << 0x20U) 
                                                           | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_25)))
                                                           : 
                                                          ((0x67U 
                                                            == 
                                                            (0xffU 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U)))
                                                            ? 
                                                           (((QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractGeneratedMem_1)) 
                                                             << 0x20U) 
                                                            | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__abstractGeneratedMem_0)))
                                                            : 
                                                           ((0x66U 
                                                             == 
                                                             (0xffU 
                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                 >> 3U)))
                                                             ? 0ULL
                                                             : 
                                                            ((0x65U 
                                                              == 
                                                              (0xffU 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                  >> 3U)))
                                                              ? 0ULL
                                                              : 
                                                             ((0x64U 
                                                               == 
                                                               (0xffU 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                   >> 3U)))
                                                               ? 0ULL
                                                               : 
                                                              ((0x63U 
                                                                == 
                                                                (0xffU 
                                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                    >> 3U)))
                                                                ? 0ULL
                                                                : 
                                                               ((0x62U 
                                                                 == 
                                                                 (0xffU 
                                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                     >> 3U)))
                                                                 ? 0ULL
                                                                 : 
                                                                ((0x61U 
                                                                  == 
                                                                  (0xffU 
                                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                      >> 3U)))
                                                                  ? 0ULL
                                                                  : 
                                                                 ((0x60U 
                                                                   == 
                                                                   (0xffU 
                                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                       >> 3U)))
                                                                   ? 0x380006fULL
                                                                   : 
                                                                  ((0x5fU 
                                                                    == 
                                                                    (0xffU 
                                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                        >> 3U)))
                                                                    ? 0ULL
                                                                    : 
                                                                   ((0x5eU 
                                                                     == 
                                                                     (0xffU 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                         >> 3U)))
                                                                     ? 0ULL
                                                                     : 
                                                                    ((0x5dU 
                                                                      == 
                                                                      (0xffU 
                                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                          >> 3U)))
                                                                      ? 0ULL
                                                                      : 
                                                                     ((0x5cU 
                                                                       == 
                                                                       (0xffU 
                                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                           >> 3U)))
                                                                       ? 0ULL
                                                                       : 
                                                                      ((0x5bU 
                                                                        == 
                                                                        (0xffU 
                                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                            >> 3U)))
                                                                        ? 0ULL
                                                                        : 
                                                                       ((0x5aU 
                                                                         == 
                                                                         (0xffU 
                                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                             >> 3U)))
                                                                         ? 0ULL
                                                                         : 
                                                                        ((0x59U 
                                                                          == 
                                                                          (0xffU 
                                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                              >> 3U)))
                                                                          ? 0ULL
                                                                          : 
                                                                         ((0x58U 
                                                                           == 
                                                                           (0xffU 
                                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                               >> 3U)))
                                                                           ? 0ULL
                                                                           : 
                                                                          ((0x57U 
                                                                            == 
                                                                            (0xffU 
                                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                            ? 0ULL
                                                                            : 
                                                                           ((0x56U 
                                                                             == 
                                                                             (0xffU 
                                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                             ? 0ULL
                                                                             : 
                                                                            ((0x55U 
                                                                              == 
                                                                              (0xffU 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              ? 0ULL
                                                                              : 
                                                                             ((0x54U 
                                                                               == 
                                                                               (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               ? 0ULL
                                                                               : 
                                                                              ((0x53U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                ? 0ULL
                                                                                : 
                                                                               ((0x52U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x51U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x50U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x49U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x48U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x47U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x46U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x45U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x44U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x43U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x42U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x41U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x40U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x39U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x38U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x37U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x36U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x35U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x34U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x33U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x32U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x31U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x30U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x29U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x28U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x27U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x26U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x25U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x24U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x23U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x22U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x21U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x20U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x19U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x18U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x17U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x16U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x15U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x14U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x13U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x12U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x11U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x10U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xfU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xdU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xcU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xbU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0xaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x100073ULL
                                                                                 : 
                                                                                ((9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x100026237b200073ULL
                                                                                 : 
                                                                                ((8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x7b20247310802423ULL
                                                                                 : 
                                                                                ((7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0xf140247330000067ULL
                                                                                 : 
                                                                                ((6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x100022237b202473ULL
                                                                                 : 
                                                                                ((5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x4086300147413ULL
                                                                                 : 
                                                                                ((4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0xfe0408e300347413ULL
                                                                                 : 
                                                                                ((3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0x4004440310802023ULL
                                                                                 : 
                                                                                ((2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0xf14024737b241073ULL
                                                                                 : 
                                                                                ((1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0xff0000f0440006fULL
                                                                                 : 0x380006f00c0006fULL)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_hc0537470__0 = ((0xeaU == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                 : ((0xe9U == (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                     : ((0xe8U == (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                         : ((0xe7U 
                                             == (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                                             ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                             : ((0xe6U 
                                                 == 
                                                 (0xffU 
                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                     >> 3U)))
                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                 : 
                                                ((0xe5U 
                                                  == 
                                                  (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                                  ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                  : 
                                                 ((0xe4U 
                                                   == 
                                                   (0xffU 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                   : 
                                                  ((0xe3U 
                                                    == 
                                                    (0xffU 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                    : 
                                                   ((0xe2U 
                                                     == 
                                                     (0xffU 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                     : 
                                                    ((0xe1U 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                      : 
                                                     ((0xe0U 
                                                       == 
                                                       (0xffU 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                       : 
                                                      ((0xdfU 
                                                        == 
                                                        (0xffU 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                            >> 3U)))
                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                        : 
                                                       ((0xdeU 
                                                         == 
                                                         (0xffU 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U)))
                                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                         : 
                                                        ((0xddU 
                                                          == 
                                                          (0xffU 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                              >> 3U)))
                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                          : 
                                                         ((0xdcU 
                                                           == 
                                                           (0xffU 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                               >> 3U)))
                                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                           : 
                                                          ((0xdbU 
                                                            == 
                                                            (0xffU 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U)))
                                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                            : 
                                                           ((0xdaU 
                                                             == 
                                                             (0xffU 
                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                 >> 3U)))
                                                             ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                             : 
                                                            ((0xd9U 
                                                              == 
                                                              (0xffU 
                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                  >> 3U)))
                                                              ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                              : 
                                                             ((0xd8U 
                                                               == 
                                                               (0xffU 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                   >> 3U)))
                                                               ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                               : 
                                                              ((0xd7U 
                                                                == 
                                                                (0xffU 
                                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                    >> 3U)))
                                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                : 
                                                               ((0xd6U 
                                                                 == 
                                                                 (0xffU 
                                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                     >> 3U)))
                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                 : 
                                                                ((0xd5U 
                                                                  == 
                                                                  (0xffU 
                                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                      >> 3U)))
                                                                  ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                  : 
                                                                 ((0xd4U 
                                                                   == 
                                                                   (0xffU 
                                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                       >> 3U)))
                                                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                   : 
                                                                  ((0xd3U 
                                                                    == 
                                                                    (0xffU 
                                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                        >> 3U)))
                                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                    : 
                                                                   ((0xd2U 
                                                                     == 
                                                                     (0xffU 
                                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                         >> 3U)))
                                                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                     : 
                                                                    ((0xd1U 
                                                                      == 
                                                                      (0xffU 
                                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                          >> 3U)))
                                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                      : 
                                                                     ((0xd0U 
                                                                       == 
                                                                       (0xffU 
                                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                           >> 3U)))
                                                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                       : 
                                                                      ((0xcfU 
                                                                        == 
                                                                        (0xffU 
                                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                            >> 3U)))
                                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                        : 
                                                                       ((0xceU 
                                                                         == 
                                                                         (0xffU 
                                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                             >> 3U)))
                                                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                         : 
                                                                        ((0xcdU 
                                                                          == 
                                                                          (0xffU 
                                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                              >> 3U)))
                                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                          : 
                                                                         ((0xccU 
                                                                           == 
                                                                           (0xffU 
                                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                               >> 3U)))
                                                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                           : 
                                                                          ((0xcbU 
                                                                            == 
                                                                            (0xffU 
                                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                            : 
                                                                           ((0xcaU 
                                                                             == 
                                                                             (0xffU 
                                                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                             ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                             : 
                                                                            ((0xc9U 
                                                                              == 
                                                                              (0xffU 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                              ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                              : 
                                                                             ((0xc8U 
                                                                               == 
                                                                               (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                               ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                               : 
                                                                              ((0xc7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                : 
                                                                               ((0xc6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xafU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xadU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xacU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xabU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x99U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x98U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x97U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x96U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x95U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x94U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x93U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x92U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x91U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x90U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x89U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x88U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x87U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x86U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x85U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x84U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x83U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x82U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x81U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x80U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x79U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x78U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x77U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : 
                                                                                ((0x76U 
                                                                                == 
                                                                                (0xffU 
                                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                                >> 3U)))
                                                                                 ? 0ULL
                                                                                 : __Vdeeptemp_h897aaade__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_hb98ca724__0 = ((0xedU == (0xffU & 
                                           ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                            >> 3U)))
                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                 : ((0xecU == (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                  >> 3U)))
                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                     : ((0xebU == (0xffU 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                         : __Vdeeptemp_hc0537470__0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_in_d_bits_data 
        = (((0xffU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                >> 3U))) ? (0U == (0x100U 
                                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                      >> 3U)))
             : ((0xfeU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                    >> 3U))) ? (0U 
                                                == 
                                                (0x100U 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                 : ((0xfdU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                        >> 3U))) ? 
                    (0U == (0x100U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                      >> 3U))) : ((0xfcU 
                                                   == 
                                                   (0xffU 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   ? 
                                                  (0U 
                                                   == 
                                                   (0x100U 
                                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                       >> 3U)))
                                                   : 
                                                  ((0xfbU 
                                                    == 
                                                    (0xffU 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    ? 
                                                   (0U 
                                                    == 
                                                    (0x100U 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    : 
                                                   ((0xfaU 
                                                     == 
                                                     (0xffU 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     ? 
                                                    (0U 
                                                     == 
                                                     (0x100U 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     : 
                                                    ((0xf9U 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      ? 
                                                     (0U 
                                                      == 
                                                      (0x100U 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      : 
                                                     ((0xf8U 
                                                       == 
                                                       (0xffU 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       ? 
                                                      (0U 
                                                       == 
                                                       (0x100U 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       : __Vdeeptemp_hf1e61f59__0))))))))
            ? ((0xffU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                   >> 3U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                : ((0xfeU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                       >> 3U))) ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                    : ((0xfdU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                           >> 3U)))
                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                        : ((0xfcU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 3U)))
                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                            : ((0xfbU == (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                   >> 3U)))
                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                : ((0xfaU == (0xffU 
                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                 >> 3U)))
                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                    : ((0xf9U == (0xffU 
                                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                     >> 3U)))
                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                        : ((0xf8U == 
                                            (0xffU 
                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                >> 3U)))
                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                            : ((0xf7U 
                                                == 
                                                (0xffU 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                    >> 3U)))
                                                ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                : (
                                                   (0xf6U 
                                                    == 
                                                    (0xffU 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                        >> 3U)))
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                    : 
                                                   ((0xf5U 
                                                     == 
                                                     (0xffU 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                         >> 3U)))
                                                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                     : 
                                                    ((0xf4U 
                                                      == 
                                                      (0xffU 
                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                          >> 3U)))
                                                      ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                      : 
                                                     ((0xf3U 
                                                       == 
                                                       (0xffU 
                                                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                           >> 3U)))
                                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                       : 
                                                      ((0xf2U 
                                                        == 
                                                        (0xffU 
                                                         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                            >> 3U)))
                                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                        : 
                                                       ((0xf1U 
                                                         == 
                                                         (0xffU 
                                                          & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                             >> 3U)))
                                                         ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                         : 
                                                        ((0xf0U 
                                                          == 
                                                          (0xffU 
                                                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                              >> 3U)))
                                                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                          : 
                                                         ((0xefU 
                                                           == 
                                                           (0xffU 
                                                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                               >> 3U)))
                                                           ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                           : 
                                                          ((0xeeU 
                                                            == 
                                                            (0xffU 
                                                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                                >> 3U)))
                                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_prepend_86
                                                            : __Vdeeptemp_hb98ca724__0))))))))))))))))))
            : 0ULL);
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_405 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_527) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_449))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__goReg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_2114 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_449)
            ? 0U : (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__goReg)) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_631))
                     ? 0U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)));
}

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
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_opcode = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done = 0;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_368 = 0xc0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_439 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___GEN_70 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_440 = 0U;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_368 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__flushCounter) 
                         + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__resetting)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0)
                ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor_1__DOT__b_first_done)
                    ? ((~ ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG) 
                               << 1U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_439 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__r_btb_updatePipe_valid)
                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pageValid) 
                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__tgtPageReplEn) 
                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxPageReplEn)))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pageValid));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___GEN_70 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid)
                ? 0U : (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_stalld)
                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nBufValid)
                               : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq_io_deq_valid) 
                                   & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT____VdfgRegularize_h1e19e3de_0_0) 
                                      & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nICReady) 
                                          < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nIC)) 
                                         & (1U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___io_imem_ready_T_4)))))
                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___io_imem_ready_T_4)
                                   : ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nBufValid)) 
                                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT____VdfgRegularize_h1e19e3de_0_0)))
                                       ? 0U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nBufValid) 
                                               - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nReady)))))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_440 
            = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_13) 
                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_16))
                ? 0U : ((1U & ((IData)((6U == (6U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                               | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit 
                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_1)) 
                                  | ((IData)((0x18U 
                                              == (0x18U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                     | ((((IData)((0x60U 
                                                   == 
                                                   (0x60U 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_4) 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_4))) 
                                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_2) 
                                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_5))) 
                                        | ((IData)(
                                                   (0x300U 
                                                    == 
                                                    (0x300U 
                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                           | (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit 
                                                >> 7U) 
                                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_7)) 
                                              | ((IData)(
                                                         (0xc00U 
                                                          == 
                                                          (0xc00U 
                                                           & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                 | (((((IData)(
                                                               (0x3000U 
                                                                == 
                                                                (0x3000U 
                                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_11) 
                                                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_10))) 
                                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_9) 
                                                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_11))) 
                                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_6) 
                                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_12))) 
                                                    | ((IData)(
                                                               (0x18000U 
                                                                == 
                                                                (0x18000U 
                                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                       | (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit 
                                                            >> 0xeU) 
                                                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_14)) 
                                                          | ((IData)(
                                                                     (0x60000U 
                                                                      == 
                                                                      (0x60000U 
                                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                             | ((((IData)(
                                                                          (0x180000U 
                                                                           == 
                                                                           (0x180000U 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_18) 
                                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_17))) 
                                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_16) 
                                                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_18))) 
                                                                | ((IData)(
                                                                           (0xc00000U 
                                                                            == 
                                                                            (0xc00000U 
                                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                                   | (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit 
                                                                        >> 0x15U) 
                                                                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_20)) 
                                                                      | ((IData)(
                                                                                (0x3000000U 
                                                                                == 
                                                                                (0x3000000U 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                                         | (((((IData)(
                                                                                (0xc000000U 
                                                                                == 
                                                                                (0xc000000U 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit))) 
                                                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_25) 
                                                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_23))) 
                                                                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_23) 
                                                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_24))) 
                                                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_20) 
                                                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_25))) 
                                                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_6) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_12)) 
                                                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__leftOne_20) 
                                                                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__rightOne_25))))))))))))))))))))
                         ? ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__idxHit) 
                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__isValid)
                         : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__r_btb_updatePipe_valid)
                             ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__r_btb_updatePipe_bits_isValid)
                                 ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__isValid 
                                    | ((IData)(1U) 
                                       << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__waddr)))
                                 : ((~ ((IData)(1U) 
                                        << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__waddr))) 
                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__isValid))
                             : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__isValid)));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__in_reset)
                  ? (~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_4_0))
                  : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass_reg)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_0 
        = (1U & (~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__stall_counter)) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass) 
                       != (1U & (~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_4_0)))))));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)) 
           & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT__a_first_done 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_a_valid) 
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
    vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
            ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0)) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1)))
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__monitor__DOT__d_first_done 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter 
        = ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_mask)) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo)) 
            << 2U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready 
        = (0xfU & ((VL_SHIFTR_III(4,4,32, (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter), 1U) 
                    | VL_SHIFTR_III(4,4,32, (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter), 2U)) 
                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_mask) 
                      << 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys 
        = (3U & (~ (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready) 
                     >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_unready))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT___readys_mask_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_filter_lo));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_1 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1)
               : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
                  >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft) {
        TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_1;
        TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0;
    } else {
        TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_1;
        TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__earlyWinner_0;
    }
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid) 
           & ((4U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
              & ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready) 
                 & (IData)(((0U == (0x14U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address))) 
                            & ((IData)(1U) << (1U & 
                                               ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address) 
                                                >> 3U))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT__d_first_done 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)) 
            & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter_io_innerCtrl_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__out_woready_6) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__innerCtrlValidReg));
    vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_bits_data 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0)
             ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)
                 ? 0U : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg 
                                 >> 1U))) : 0U) | ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_1)
                                                    ? 
                                                   ((0U 
                                                     == 
                                                     (5U 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address) 
                                                         >> 2U)))
                                                     ? 
                                                    ((8U 
                                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address))
                                                      ? 0x112380U
                                                      : 
                                                     (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLReg_haltreq) 
                                                       << 0x1fU) 
                                                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLReg_ndmreset) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_4_0))))
                                                     : 0U)
                                                    : 0U));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_denied));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__ridx_incremented 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__source_valid__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__ridx_ridx_bin) 
              + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__monitor__DOT__d_first_done)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter_3)) 
              & (IData)((4U == (6U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_d_bits_opcode))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__latch 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__beatsLeft)) 
           & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_0_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__monitor__DOT__d_first_done 
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
    vlSelfRef.__VdfgRegularize_hd87f99a1_4_2 = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__muxStateEarly_0) 
                                                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)
                                                     ? 
                                                    ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_d_bits_denied) 
                                                     & ((7U 
                                                         != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
                                                        & ((6U 
                                                            != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
                                                           & ((5U 
                                                               != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
                                                              & ((4U 
                                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
                                                                 | ((3U 
                                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode)) 
                                                                    | (2U 
                                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode))))))))
                                                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleIn_0_d_sink__DOT__io_deq_bits_deq_bits_reg__DOT__cdc_reg))) 
                                                | (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_valid));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__idle));
    vlSelfRef.TestHarness__DOT__SimDTM_debug_resp_bits_resp 
        = vlSelfRef.__VdfgRegularize_hd87f99a1_4_2;
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT___GEN_12 
        = ((~ ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done) 
               & (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__da_bits_opcode)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__idle));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_0) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__bypass)
               ? (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error_auto_in_a_ready)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source_io_enq_ready)));
    vlSelfRef.TestHarness__DOT__SimDTM_debug_req_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0) 
            & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready)) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1) 
              & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__a_first_done 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__next_flight 
        = (3U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__flight) 
                  + ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo) 
                     + VL_SHIFTR_III(2,2,32, ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__a_first_done)) 
                                               << 1U) 
                                              | (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo)), 1U))) 
                 - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done) 
                    + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done), 1U))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__5(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__5\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_585 = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_586 = 0ULL;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_585 
            = ((0x305U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mtvec)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_586 
            = ((0x320U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                           >> 0x14U)) ? (0xfffffffffffffffdULL 
                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)
                : (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_585 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mtvec));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_586 
            = (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit));
    }
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__19(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__19\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmactive_synced_dmInner_io_innerCtrl_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__sink_extend__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmiXing__DOT__bundleOut_0_a_sink__DOT__sink_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_1__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_0 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__io_innerCtrl_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0__DOT__io_out_source_valid_0__DOT__output_chain__DOT__sync_2 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__20(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__20\n"); );
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

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__21(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__21\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0)) 
                 | (IData)(vlSelfRef.reset)));
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
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/rocket/verilog/instrumented/TestHarness.v", 189396, "", "Input combinational region did not converge.");
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
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/rocket/verilog/instrumented/TestHarness.v", 189396, "", "NBA region did not converge.");
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
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/rocket/verilog/instrumented/TestHarness.v", 189396, "", "Active region did not converge.");
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
