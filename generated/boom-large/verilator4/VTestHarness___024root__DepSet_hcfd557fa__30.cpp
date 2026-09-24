// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__23(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__23\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2_io_deq_uop_exception 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT___T_597) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_bp_debug_if) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_bp_xcpt_if) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_xcpt_pf_if) 
                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_xcpt_ae_if) 
                             | (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_23) 
                                     | ((0x37U == (0x7fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                        | ((0x13U == 
                                            (0x707fU 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                           | (((0x7013U 
                                                == 
                                                (0x707fU 
                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                               | ((0x6013U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                  | ((0x4013U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                     | ((0x2013U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                        | ((0x3013U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                           | ((0x1033U 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                              | ((0x33U 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                 | ((0x40000033U 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                    | ((0x2033U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                       | ((0x3033U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                          | ((0x7033U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                             | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2001033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2003033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2002033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x200003bU 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | (0x2004033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)))))))))))))))))))))) 
                                              | ((0x2005033U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                 | (((0x2006033U 
                                                      == 
                                                      (0xfe00707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                     | ((0x2007033U 
                                                         == 
                                                         (0xfe00707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                        | ((0x200403bU 
                                                            == 
                                                            (0xfe00707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                           | ((0x200503bU 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                              | ((0x200603bU 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                 | ((0x200703bU 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                    | ((0x17U 
                                                                        == 
                                                                        (0x7fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                       | ((0x6fU 
                                                                           == 
                                                                           (0x7fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                          | ((0x67U 
                                                                              == 
                                                                              (0x707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                             | ((0x63U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x1063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x5063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x7063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x4063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x6063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x1073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x3073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x5073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x6073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x7073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x12000073U 
                                                                                == 
                                                                                (0xfe007fffU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x73U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | ((0x100073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | ((0x10200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | ((0x30200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | ((0x7b200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | ((0x10500073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst) 
                                                                                | (0x100fU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)))))))))))))))))))))))))))))) 
                                                    | ((0xfU 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                       | (((0x202fU 
                                                            == 
                                                            (0xf800707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                           | ((0x2000202fU 
                                                               == 
                                                               (0xf800707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                              | ((0x800202fU 
                                                                  == 
                                                                  (0xf800707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                 | ((0x6000202fU 
                                                                     == 
                                                                     (0xf800707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                    | ((0x4000202fU 
                                                                        == 
                                                                        (0xf800707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                       | ((0x8000202fU 
                                                                           == 
                                                                           (0xf800707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                          | ((0xc000202fU 
                                                                              == 
                                                                              (0xf800707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                             | ((0xa000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xe000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x6000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x4000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x8000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_13) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_12) 
                                                                                | ((0x1000302fU 
                                                                                == 
                                                                                (0xf9f0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x1800202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x1800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x3007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2027U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_17) 
                                                                                | ((0xe2001053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | (0xf0000053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst))))))))))))))))))))))))))) 
                                                          | ((0xf2000053U 
                                                              == 
                                                              (0xfff0707fU 
                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                             | (((0xe0000053U 
                                                                  == 
                                                                  (0xfff0707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                 | ((0xe2000053U 
                                                                     == 
                                                                     (0xfff0707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                    | ((0x20000053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                       | ((0x22000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                          | ((0x20002053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                             | ((0x22002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x20001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x22001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x40100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x42000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd0000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd0100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd0200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd0300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd2000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd2100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xd2200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_11) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_10) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_22) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_21) 
                                                                                | ((0xc2300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xa0002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xa0001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | (0xa0000053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)))))))))))))))))))))))))) 
                                                                | ((0xa2002053U 
                                                                    == 
                                                                    (0xfe00707fU 
                                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                   | (((0xa2001053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                       | ((0xa2000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                          | ((0x28000053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_16) 
                                                                                | ((0x2a001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x53U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x8000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x10000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0xa000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_15) 
                                                                                | ((0x47U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x4fU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x4bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x2000043U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_9) 
                                                                                | ((0x200004bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x18000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_20) 
                                                                                | ((0x5a000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((0x3003U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT____VdfgRegularize_hbb470ff5_0_18) 
                                                                                | ((0x1013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                                                | (0x5013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst))))))))))))))))))))))))) 
                                                                      | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_234)))))))))))))) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2_io_deq_uop_fp_val) 
                                    & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs)))) 
                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT__csr_en) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_io_decode_2_read_illegal) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT___T_589) 
                                          & (3U == 
                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst 
                                              >> 0x1eU))))) 
                                   | (((0x6bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2_io_deq_uop_uopc)) 
                                       | (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2__DOT__cs_csr_cmd))) 
                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_2_read_illegal_T_1) 
                                         | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
                                              & (0x10000000U 
                                                 == 
                                                 (0x32200000U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst))) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_10) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret_2))) 
                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret_2) 
                                                & (IData)(
                                                          ((0x48000000U 
                                                            == 
                                                            (0x48000000U 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)) 
                                                           & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_debug))))) 
                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_0_read_illegal_T_298) 
                                                  & (0x2000000U 
                                                     == 
                                                     (0x42000000U 
                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_inst)))))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1_io_deq_uop_exception 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT___T_597) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_bp_debug_if) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_bp_xcpt_if) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_xcpt_pf_if) 
                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_xcpt_ae_if) 
                             | (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_23) 
                                     | ((0x37U == (0x7fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                        | ((0x13U == 
                                            (0x707fU 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                           | (((0x7013U 
                                                == 
                                                (0x707fU 
                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                               | ((0x6013U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                  | ((0x4013U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                     | ((0x2013U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                        | ((0x3013U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                           | ((0x1033U 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                              | ((0x33U 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                 | ((0x40000033U 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                    | ((0x2033U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                       | ((0x3033U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                          | ((0x7033U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                             | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2001033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2003033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2002033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x200003bU 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | (0x2004033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)))))))))))))))))))))) 
                                              | ((0x2005033U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                 | (((0x2006033U 
                                                      == 
                                                      (0xfe00707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                     | ((0x2007033U 
                                                         == 
                                                         (0xfe00707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                        | ((0x200403bU 
                                                            == 
                                                            (0xfe00707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                           | ((0x200503bU 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                              | ((0x200603bU 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                 | ((0x200703bU 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                    | ((0x17U 
                                                                        == 
                                                                        (0x7fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                       | ((0x6fU 
                                                                           == 
                                                                           (0x7fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                          | ((0x67U 
                                                                              == 
                                                                              (0x707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                             | ((0x63U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x1063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x5063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x7063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x4063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x6063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x1073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x3073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x5073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x6073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x7073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x12000073U 
                                                                                == 
                                                                                (0xfe007fffU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x73U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | ((0x100073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | ((0x10200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | ((0x30200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | ((0x7b200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | ((0x10500073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst) 
                                                                                | (0x100fU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)))))))))))))))))))))))))))))) 
                                                    | ((0xfU 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                       | (((0x202fU 
                                                            == 
                                                            (0xf800707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                           | ((0x2000202fU 
                                                               == 
                                                               (0xf800707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                              | ((0x800202fU 
                                                                  == 
                                                                  (0xf800707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                 | ((0x6000202fU 
                                                                     == 
                                                                     (0xf800707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                    | ((0x4000202fU 
                                                                        == 
                                                                        (0xf800707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                       | ((0x8000202fU 
                                                                           == 
                                                                           (0xf800707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                          | ((0xc000202fU 
                                                                              == 
                                                                              (0xf800707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                             | ((0xa000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xe000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x6000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x4000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x8000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_13) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_12) 
                                                                                | ((0x1000302fU 
                                                                                == 
                                                                                (0xf9f0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x1800202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x1800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x3007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2027U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_17) 
                                                                                | ((0xe2001053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | (0xf0000053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst))))))))))))))))))))))))))) 
                                                          | ((0xf2000053U 
                                                              == 
                                                              (0xfff0707fU 
                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                             | (((0xe0000053U 
                                                                  == 
                                                                  (0xfff0707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                 | ((0xe2000053U 
                                                                     == 
                                                                     (0xfff0707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                    | ((0x20000053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                       | ((0x22000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                          | ((0x20002053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                             | ((0x22002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x20001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x22001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x40100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x42000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd0000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd0100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd0200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd0300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd2000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd2100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xd2200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_11) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_10) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_22) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_21) 
                                                                                | ((0xc2300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xa0002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xa0001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | (0xa0000053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)))))))))))))))))))))))))) 
                                                                | ((0xa2002053U 
                                                                    == 
                                                                    (0xfe00707fU 
                                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                   | (((0xa2001053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                       | ((0xa2000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                          | ((0x28000053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_16) 
                                                                                | ((0x2a001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x53U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x8000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x10000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0xa000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_15) 
                                                                                | ((0x47U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x4fU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x4bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x2000043U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_9) 
                                                                                | ((0x200004bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x18000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_20) 
                                                                                | ((0x5a000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((0x3003U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT____VdfgRegularize_hbb470ff5_0_18) 
                                                                                | ((0x1013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                                                | (0x5013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst))))))))))))))))))))))))) 
                                                                      | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_231)))))))))))))) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1_io_deq_uop_fp_val) 
                                    & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs)))) 
                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT__csr_en) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_io_decode_1_read_illegal) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT___T_589) 
                                          & (3U == 
                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst 
                                              >> 0x1eU))))) 
                                   | (((0x6bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1_io_deq_uop_uopc)) 
                                       | (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1__DOT__cs_csr_cmd))) 
                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_1_read_illegal_T_1) 
                                         | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
                                              & (0x10000000U 
                                                 == 
                                                 (0x32200000U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst))) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_10) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret_1))) 
                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret_1) 
                                                & (IData)(
                                                          ((0x48000000U 
                                                            == 
                                                            (0x48000000U 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)) 
                                                           & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_debug))))) 
                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_0_read_illegal_T_298) 
                                                  & (0x2000000U 
                                                     == 
                                                     (0x42000000U 
                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_inst)))))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0_io_deq_uop_exception 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT___T_597) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_bp_debug_if) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_bp_xcpt_if) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_xcpt_pf_if) 
                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_xcpt_ae_if) 
                             | (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_23) 
                                     | ((0x37U == (0x7fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                        | ((0x13U == 
                                            (0x707fU 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                           | (((0x7013U 
                                                == 
                                                (0x707fU 
                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                               | ((0x6013U 
                                                   == 
                                                   (0x707fU 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                  | ((0x4013U 
                                                      == 
                                                      (0x707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                     | ((0x2013U 
                                                         == 
                                                         (0x707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                        | ((0x3013U 
                                                            == 
                                                            (0x707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                           | ((0x1033U 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                              | ((0x33U 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                 | ((0x40000033U 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                    | ((0x2033U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                       | ((0x3033U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                          | ((0x7033U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                             | ((0x6033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x4033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x40005033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x5033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2000033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2001033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2003033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2002033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x200003bU 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | (0x2004033U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)))))))))))))))))))))) 
                                              | ((0x2005033U 
                                                  == 
                                                  (0xfe00707fU 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                 | (((0x2006033U 
                                                      == 
                                                      (0xfe00707fU 
                                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                     | ((0x2007033U 
                                                         == 
                                                         (0xfe00707fU 
                                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                        | ((0x200403bU 
                                                            == 
                                                            (0xfe00707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                           | ((0x200503bU 
                                                               == 
                                                               (0xfe00707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                              | ((0x200603bU 
                                                                  == 
                                                                  (0xfe00707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                 | ((0x200703bU 
                                                                     == 
                                                                     (0xfe00707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                    | ((0x17U 
                                                                        == 
                                                                        (0x7fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                       | ((0x6fU 
                                                                           == 
                                                                           (0x7fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                          | ((0x67U 
                                                                              == 
                                                                              (0x707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                             | ((0x63U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x1063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x5063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x7063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x4063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x6063U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x1073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x3073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x5073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x6073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x7073U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x12000073U 
                                                                                == 
                                                                                (0xfe007fffU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x73U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | ((0x100073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | ((0x10200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | ((0x30200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | ((0x7b200073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | ((0x10500073U 
                                                                                == vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst) 
                                                                                | (0x100fU 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)))))))))))))))))))))))))))))) 
                                                    | ((0xfU 
                                                        == 
                                                        (0x707fU 
                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                       | (((0x202fU 
                                                            == 
                                                            (0xf800707fU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                           | ((0x2000202fU 
                                                               == 
                                                               (0xf800707fU 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                              | ((0x800202fU 
                                                                  == 
                                                                  (0xf800707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                 | ((0x6000202fU 
                                                                     == 
                                                                     (0xf800707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                    | ((0x4000202fU 
                                                                        == 
                                                                        (0xf800707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                       | ((0x8000202fU 
                                                                           == 
                                                                           (0xf800707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                          | ((0xc000202fU 
                                                                              == 
                                                                              (0xf800707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                             | ((0xa000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xe000202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x6000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x4000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x8000302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_13) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_12) 
                                                                                | ((0x1000302fU 
                                                                                == 
                                                                                (0xf9f0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x1800202fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x1800302fU 
                                                                                == 
                                                                                (0xf800707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x3007U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2027U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_17) 
                                                                                | ((0xe2001053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | (0xf0000053U 
                                                                                == 
                                                                                (0xfff0707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst))))))))))))))))))))))))))) 
                                                          | ((0xf2000053U 
                                                              == 
                                                              (0xfff0707fU 
                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                             | (((0xe0000053U 
                                                                  == 
                                                                  (0xfff0707fU 
                                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                 | ((0xe2000053U 
                                                                     == 
                                                                     (0xfff0707fU 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                    | ((0x20000053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                       | ((0x22000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                          | ((0x20002053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                             | ((0x22002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x20001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x22001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x40100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x42000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd0000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd0100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd0200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd0300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd2000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd2100053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xd2200053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_11) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_10) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_22) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_21) 
                                                                                | ((0xc2300053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xa0002053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xa0001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | (0xa0000053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)))))))))))))))))))))))))) 
                                                                | ((0xa2002053U 
                                                                    == 
                                                                    (0xfe00707fU 
                                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                   | (((0xa2001053U 
                                                                        == 
                                                                        (0xfe00707fU 
                                                                         & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                       | ((0xa2000053U 
                                                                           == 
                                                                           (0xfe00707fU 
                                                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                          | ((0x28000053U 
                                                                              == 
                                                                              (0xfe00707fU 
                                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_16) 
                                                                                | ((0x2a001053U 
                                                                                == 
                                                                                (0xfe00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x53U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x8000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x10000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0xa000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_15) 
                                                                                | ((0x47U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x4fU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x4bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x2000043U 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_9) 
                                                                                | ((0x200004bU 
                                                                                == 
                                                                                (0x600007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x18000053U 
                                                                                == 
                                                                                (0xfe00007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_20) 
                                                                                | ((0x5a000053U 
                                                                                == 
                                                                                (0xfff0007fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((0x3003U 
                                                                                == 
                                                                                (0x707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT____VdfgRegularize_hbb470ff5_0_18) 
                                                                                | ((0x1013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                                                | (0x5013U 
                                                                                == 
                                                                                (0xfc00707fU 
                                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst))))))))))))))))))))))))) 
                                                                      | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_228)))))))))))))) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0_io_deq_uop_fp_val) 
                                    & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs)))) 
                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT__csr_en) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr_io_decode_0_read_illegal) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT___T_589) 
                                          & (3U == 
                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst 
                                              >> 0x1eU))))) 
                                   | (((0x6bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0_io_deq_uop_uopc)) 
                                       | (4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0__DOT__cs_csr_cmd))) 
                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_0_read_illegal_T_1) 
                                         | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_9) 
                                              & (0x10000000U 
                                                 == 
                                                 (0x32200000U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst))) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_10) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret))) 
                                            | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__is_ret) 
                                                & (IData)(
                                                          ((0x48000000U 
                                                            == 
                                                            (0x48000000U 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)) 
                                                           & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT__reg_debug))))) 
                                               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__csr__DOT___io_decode_0_read_illegal_T_298) 
                                                  & (0x2000000U 
                                                     == 
                                                     (0x42000000U 
                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_inst)))))))))))))));
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__24(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__24\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_371) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87 
            = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_187)) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_is_replay) 
                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_tlb_miss))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__s2_vpc;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_35) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_388) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87 
                = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_29)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f2_predicted_target;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_27));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_29;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87 
            = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_27));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_29;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_226 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_33)
                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87)
                  : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_34)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87)
                      : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_1815)
                          ? (~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3__DOT__ram_xcpt_ae_inst
                                [0U] | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3__DOT__ram_xcpt_pf_inst
                                [0U])) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_205 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_34)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_1815)
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__f3_predicted_target
                : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_14_valid)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_val)
               : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_1634)
                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_226)
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_87))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_14_valid)
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_14_bits_addr
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush)
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_pc
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___T_1634)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT____VdfgRegularize_h77f4856b_1_33)
                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88
                        : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_205)
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT___GEN_88)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__s0_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid));
    if ((1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                       >> 3U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0_io_f0_pc 
            = (0xffffffffffULL & (8ULL + (~ (7ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_1_io_f0_pc 
            = (0xffffffffffULL & (~ (7ULL | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0_io_f0_valid 
            = ((7U != (7U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                     >> 3U)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0_io_f0_pc 
            = (0xffffffffffULL & (~ (7ULL | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_1_io_f0_pc 
            = (0xffffffffffULL & (8ULL + (~ (7ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT__banked_predictors_0_io_f0_valid 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache_io_req_valid;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd__DOT____VdfgRegularize_hb7d7dc25_2_1 
        = (0xfU & (((IData)(0xffU) << (3U & (IData)(
                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                                     >> 1U)))) 
                   & ((7U == (7U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                            >> 3U))))
                       ? 0xfU : 0xffU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT___T_101 
        = (0xffU & ((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                             >> 4U)) + (1U & (IData)(
                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                                      >> 3U)))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__refill_one_beat) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__dataArrayB1Way_0_MPORT_2_addr 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT___T_97));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__dataArrayB0Way_0_MPORT_1_addr 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT___T_97;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__dataArrayB1Way_0_MPORT_2_addr 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__bpd_io_f0_req_bits_pc 
                                >> 4U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT__dataArrayB0Way_0_MPORT_1_addr 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__icache__DOT___T_101;
    }
}

VL_INLINE_OPT void VTestHarness___024root___nba_comb__TOP__25(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_comb__TOP__25\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_stalls_1;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_stalls_1 = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165 = 0;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_1_io_deq_uop_exception) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_0_io_deq_uop_exception) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__xcpt_idx 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0)
            ? 0U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_1)
                     ? 1U : 2U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_455 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_enq_partial_stall) 
           | ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob__DOT__rob_state)) 
              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_valid) 
                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_15)) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_0) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_xcpts_1) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__decode_units_2_io_deq_uop_exception) 
                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_2)))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_valid)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_flush_bits_ftq_idx)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_15)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__REG_16)
                : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__xcpt_idx))
                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_2_bits_ftq_idx)
                    : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__xcpt_idx))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_1_bits_ftq_idx)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb_io_deq_bits_uops_0_bits_ftq_idx)))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_455) 
              | ((((0xffffU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT__branch_mask)) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic_io_is_branch_0)) 
                  | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
                 | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_679))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___T_199 
        = (((0x1fU & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) 
            == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__enq_ptr)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__meta_0_MPORT_2_en));
    if ((0x1bU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_27_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_27;
    } else if ((0x1aU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_26_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_26;
    } else if ((0x19U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_25_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_25;
    } else if ((0x18U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_24_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_24;
    } else if ((0x17U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_23_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_23;
    } else if ((0x16U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_22_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_22;
    } else if ((0x15U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_21_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_21;
    } else if ((0x14U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_20_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_20;
    } else if ((0x13U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_19_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_19;
    } else if ((0x12U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_18_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_18;
    } else if ((0x11U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_17_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_17;
    } else if ((0x10U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_16_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_16;
    } else if ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_15_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_15;
    } else if ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_14_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_14;
    } else if ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_13_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_13;
    } else if ((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_12_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_12;
    } else if ((0xbU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_11_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_11;
    } else if ((0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_10_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_10;
    } else if ((9U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_9_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_9;
    } else if ((8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_8_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_8;
    } else if ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_7_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_7;
    } else if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_6_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_6;
    } else if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_5_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_5;
    } else if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_4_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_4;
    } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_3_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_3;
    } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_2_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_2;
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__ftq_arb_io_out_bits))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_1_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3362 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_cfi_idx_valid;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3330 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_cfi_idx_bits;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3042 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_ras_idx;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3010 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__ram_0_start_bank;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_3394 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT__pcs_0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__ftq__DOT___GEN_2979 
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_0));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_stalls_1 
        = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_hazards_0) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_455) 
                 | ((((0xffffU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_52)) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic_io_is_branch_1)) 
                     | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
                    | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_679)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_161 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_490))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_51)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT__branch_mask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready 
        = ((~ ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_stalls_1) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_2) 
                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_455) 
                     | ((((0xffffU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105)) 
                          & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask) 
                                 >> 2U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_510))) 
                         | (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_mispredict_mask))) 
                        | (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_679)))))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_1 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_stalls_1)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_valids_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT__do_deq 
        = ((~ (IData)((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__frontend__DOT__fb__DOT__slot_will_hit_tail)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_485 
        = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready) 
             << 2U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_1) 
                        << 1U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_0))) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_finished_mask));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage_io_dec_fire_1) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_500))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT__tag_masks_1) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_161))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_161));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_redirect_flush) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_299 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_3_br_mask;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_463 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_5_br_mask;
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rob_io_enq_partial_stall) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_299 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_3_br_mask;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_463 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT__REG_5_br_mask;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_299 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_resolve_mask)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_161));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__rename_stage__DOT___GEN_463 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_resolve_mask)) 
               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_173 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_lsu_brupdate_b1_resolve_mask)) 
           & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core_io_ifu_fetchpacket_ready) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT___T_510))
                ? (((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                     ? ((2U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                         ? ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                             ? ((8U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                 ? ((0x10U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                     ? ((0x20U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                         ? ((0x40U 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                             ? ((0x80U 
                                                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                 ? 
                                                ((0x100U 
                                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                  ? 
                                                 ((0x200U 
                                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                   ? 
                                                  ((0x400U 
                                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                    ? 
                                                   ((0x800U 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                     ? 
                                                    ((0x1000U 
                                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                      ? 
                                                     ((0x2000U 
                                                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                       ? 
                                                      ((0x4000U 
                                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                        ? 
                                                       ((0x8000U 
                                                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_105))
                                                         ? 0U
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
                                         : 0x20U) : 0x10U)
                                 : 8U) : 4U) : 2U) : 1U) 
                   | (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165))
                : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__dec_brmask_logic__DOT___T_165)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_mispredict)
                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__core__DOT__b2_uop_br_mask)
                  : 0xffffU)));
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
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-large/verilog/TestHarness.v", 434213, "", "Input combinational region did not converge.");
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
            VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-large/verilog/TestHarness.v", 434213, "", "NBA region did not converge.");
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
                VL_FATAL_MT("/home/server/chronoshear-artifact-layout-20260923/generated/boom-large/verilog/TestHarness.v", 434213, "", "Active region did not converge.");
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
