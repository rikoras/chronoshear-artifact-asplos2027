// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VCipher.h for the primary calling header

#include "VCipher__pch.h"
#include "VCipher___024root.h"

VL_INLINE_OPT void VCipher___024root___nba_sequent__TOP__21(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___nba_sequent__TOP__21\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*31:0*/ __Vdeeptemp_h1b1f9087__0;
    CData/*31:0*/ __Vdeeptemp_h6099d607__0;
    CData/*31:0*/ __Vdeeptemp_h475e2978__0;
    CData/*31:0*/ __Vdeeptemp_h3c20a2ef__0;
    CData/*31:0*/ __Vdeeptemp_h9acb3116__0;
    CData/*31:0*/ __Vdeeptemp_h32f85062__0;
    // Body
    __Vdeeptemp_h1b1f9087__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                 ? 0xeeU : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                             ? 0xecU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                 ? 0xeaU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                  ? 0xe8U
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                   ? 0xe6U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                    ? 0xe4U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                     ? 0xe2U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                      ? 0xe0U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                       ? 0xdeU
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                        ? 0xdcU
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                         ? 0xdaU
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                          ? 0xd8U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                           ? 0xd6U
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                            ? 0xd4U
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                             ? 0xd2U
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                              ? 0xd0U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                               ? 0xceU
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                ? 0xccU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                 ? 0xcaU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                  ? 0xc8U
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                   ? 0xc6U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                    ? 0xc4U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                     ? 0xc2U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                      ? 0xc0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                       ? 0xbeU
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                        ? 0xbcU
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                         ? 0xbaU
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                          ? 0xb8U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                           ? 0xb6U
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                            ? 0xb4U
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                             ? 0xb2U
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                              ? 0xb0U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                               ? 0xaeU
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                ? 0xacU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xaaU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xa6U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xa0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9cU
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9aU
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x96U
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x90U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x88U
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7cU
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7aU
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x76U
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x70U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6eU
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x68U
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x64U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x62U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4cU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4aU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3eU
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x38U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x34U
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x32U
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2cU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2aU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x26U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x20U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1cU
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1aU
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x16U
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x10U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xeU
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 8U
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 4U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 2U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h9acb3116__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                 ? 0xc7U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                             ? 0xc1U
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                 ? 0xc3U
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                  ? 0xcdU
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                   ? 0xcfU
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                    ? 0xc9U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                     ? 0xcbU
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                      ? 0xd5U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                       ? 0xd7U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                        ? 0xd1U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                         ? 0xd3U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                          ? 0xddU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                           ? 0xdfU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                            ? 0xd9U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                             ? 0xdbU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                              ? 0xa5U
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                               ? 0xa7U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                ? 0xa1U
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                 ? 0xa3U
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                  ? 0xadU
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                   ? 0xafU
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                    ? 0xa9U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                     ? 0xabU
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                      ? 0xb5U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                       ? 0xb7U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                        ? 0xb1U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                         ? 0xb3U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                          ? 0xbdU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                           ? 0xbfU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                            ? 0xb9U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                             ? 0xbbU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                              ? 0x85U
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                               ? 0x87U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                ? 0x81U
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x95U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x93U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9fU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x99U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x67U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x61U
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6dU
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x6bU
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x75U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x73U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7fU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x79U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x49U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x25U
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x23U
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2fU
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x29U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x37U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x31U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3dU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x3bU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 7U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 1U
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 3U
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xdU
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xbU
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x15U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x13U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1fU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x19U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xfaU
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                                 ? 0xf0U
                                                                                 : __Vdeeptemp_h1b1f9087__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h6099d607__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                 ? 0xc5U : __Vdeeptemp_h9acb3116__0);
    __Vdeeptemp_h475e2978__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0x99U : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                             ? 0x9aU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                 ? 0x9fU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                  ? 0x9cU
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                   ? 0x95U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0x96U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0x93U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0x90U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0xb1U
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0xb2U
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 0xb7U
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 0xb4U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 0xbdU
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 0xbeU
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0xbbU
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0xb8U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 0xa9U
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0xaaU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                 ? 0xafU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                  ? 0xacU
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                   ? 0xa5U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                    ? 0xa6U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                     ? 0xa3U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                      ? 0xa0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                       ? 0xe1U
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                        ? 0xe2U
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                         ? 0xe7U
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                          ? 0xe4U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                           ? 0xedU
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                            ? 0xeeU
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                             ? 0xebU
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                              ? 0xe8U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                               ? 0xf9U
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                ? 0xfaU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xffU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf5U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf3U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd1U
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd2U
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd7U
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd4U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xddU
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdeU
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdbU
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd8U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc9U
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcaU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcfU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xccU
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc5U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc6U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc3U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc0U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 3U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h32f85062__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0x29U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                             ? 0x2cU
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                 ? 0x2fU
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                  ? 0x26U
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                   ? 0x25U
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0x20U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0x23U
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0x32U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0x31U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0x34U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 0x37U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 0x3eU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 0x3dU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 0x38U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0x3bU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0x7aU
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 0x79U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0x7cU
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                 ? 0x7fU
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                  ? 0x76U
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                   ? 0x75U
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                    ? 0x70U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                     ? 0x73U
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                      ? 0x62U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                       ? 0x61U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                        ? 0x64U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                         ? 0x67U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                          ? 0x6eU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                           ? 0x6dU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                            ? 0x68U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                             ? 0x6bU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                              ? 0x4aU
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                               ? 0x49U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                ? 0x4cU
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdaU
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd9U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdcU
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdfU
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd6U
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd5U
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd0U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xd3U
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc2U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc1U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc4U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc7U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xceU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcdU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xc8U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcbU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xeaU
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xe9U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xecU
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xefU
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xe6U
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xe5U
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xe0U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xe3U
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf1U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf7U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfdU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfbU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xbaU
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xb9U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xbcU
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xbfU
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xb6U
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xb5U
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xb0U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xb3U
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa1U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa7U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xaeU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xadU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xabU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x85U
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x81U
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x87U
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x88U
                                                                                 : __Vdeeptemp_h475e2978__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h3c20a2ef__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0x2aU : __Vdeeptemp_h32f85062__0);
    vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_13 
        = (((IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12) 
            ^ ((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                ? 0xe5U : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                            ? 0xe7U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                        ? 0xe1U : (
                                                   (0xfcU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                    ? 0xe3U
                                                    : 
                                                   ((0xfbU 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                     ? 0xedU
                                                     : 
                                                    ((0xfaU 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                      ? 0xefU
                                                      : 
                                                     ((0xf9U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                       ? 0xe9U
                                                       : 
                                                      ((0xf8U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                        ? 0xebU
                                                        : 
                                                       ((0xf7U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                         ? 0xf5U
                                                         : 
                                                        ((0xf6U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                          ? 0xf7U
                                                          : 
                                                         ((0xf5U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                           ? 0xf1U
                                                           : 
                                                          ((0xf4U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                            ? 0xf3U
                                                            : 
                                                           ((0xf3U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                             ? 0xfdU
                                                             : 
                                                            ((0xf2U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                              ? 0xffU
                                                              : 
                                                             ((0xf1U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                               ? 0xf9U
                                                               : 
                                                              ((0xf0U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1))
                                                                ? 0xfbU
                                                                : __Vdeeptemp_h6099d607__0))))))))))))))))) 
           ^ (((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                ? 0x1aU : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                            ? 0x19U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                        ? 0x1cU : (
                                                   (0xfcU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0x1fU
                                                    : 
                                                   ((0xfbU 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0x16U
                                                     : 
                                                    ((0xfaU 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0x15U
                                                      : 
                                                     ((0xf9U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0x10U
                                                       : 
                                                      ((0xf8U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0x13U
                                                        : 
                                                       ((0xf7U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 2U
                                                         : 
                                                        ((0xf6U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 1U
                                                          : 
                                                         ((0xf5U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 4U
                                                           : 
                                                          ((0xf4U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 7U
                                                            : 
                                                           ((0xf3U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0xeU
                                                             : 
                                                            ((0xf2U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0xdU
                                                              : 
                                                             ((0xf1U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 8U
                                                               : 
                                                              ((0xf0U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0xbU
                                                                : __Vdeeptemp_h3c20a2ef__0)))))))))))))))) 
              ^ (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11)));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_13 
        = ((IData)(vlSelfRef.io_roundKey_13) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_13)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_13))));
}

VL_INLINE_OPT void VCipher___024root___nba_sequent__TOP__22(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___nba_sequent__TOP__22\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*31:0*/ __Vdeeptemp_h865d5c10__0;
    CData/*31:0*/ __Vdeeptemp_h587e09a3__0;
    CData/*31:0*/ __Vdeeptemp_h0ad28bb0__0;
    CData/*31:0*/ __Vdeeptemp_h7180186a__0;
    CData/*31:0*/ __Vdeeptemp_h4e33a727__0;
    CData/*31:0*/ __Vdeeptemp_ha84e887c__0;
    // Body
    __Vdeeptemp_h865d5c10__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0xeeU : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                             ? 0xecU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                 ? 0xeaU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                  ? 0xe8U
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                   ? 0xe6U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0xe4U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0xe2U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0xe0U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0xdeU
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0xdcU
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 0xdaU
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 0xd8U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 0xd6U
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 0xd4U
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0xd2U
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0xd0U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 0xceU
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0xccU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                 ? 0xcaU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                  ? 0xc8U
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                   ? 0xc6U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                    ? 0xc4U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                     ? 0xc2U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                      ? 0xc0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                       ? 0xbeU
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                        ? 0xbcU
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                         ? 0xbaU
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                          ? 0xb8U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                           ? 0xb6U
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                            ? 0xb4U
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                             ? 0xb2U
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                              ? 0xb0U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                               ? 0xaeU
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                ? 0xacU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xaaU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa6U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xa0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9cU
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9aU
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x96U
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x90U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x88U
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7cU
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7aU
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x76U
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x70U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6eU
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x68U
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x64U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x62U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4cU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4aU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3eU
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x38U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x34U
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x32U
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2cU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2aU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x26U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x20U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1cU
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1aU
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x16U
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x10U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xeU
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 8U
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 4U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 2U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h4e33a727__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0xc7U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                             ? 0xc1U
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                 ? 0xc3U
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                  ? 0xcdU
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                   ? 0xcfU
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0xc9U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0xcbU
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0xd5U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0xd7U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0xd1U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 0xd3U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 0xddU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 0xdfU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 0xd9U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0xdbU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0xa5U
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 0xa7U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0xa1U
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                 ? 0xa3U
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                  ? 0xadU
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                   ? 0xafU
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                    ? 0xa9U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                     ? 0xabU
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                      ? 0xb5U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                       ? 0xb7U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                        ? 0xb1U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                         ? 0xb3U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                          ? 0xbdU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                           ? 0xbfU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                            ? 0xb9U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                             ? 0xbbU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                              ? 0x85U
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                               ? 0x87U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                ? 0x81U
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x95U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x93U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9fU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x99U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x67U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x61U
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6dU
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x6bU
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x75U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x73U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7fU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x79U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x49U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x25U
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x23U
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2fU
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x29U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x37U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x31U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3dU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x3bU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 7U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 1U
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 3U
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xdU
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xbU
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x15U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x13U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1fU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x19U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xfaU
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                                 ? 0xf0U
                                                                                 : __Vdeeptemp_h865d5c10__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h587e09a3__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                 ? 0xc5U : __Vdeeptemp_h4e33a727__0);
    __Vdeeptemp_h0ad28bb0__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0x99U : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                             ? 0x9aU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                 ? 0x9fU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                  ? 0x9cU
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                   ? 0x95U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0x96U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0x93U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 0x90U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 0xb1U
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 0xb2U
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 0xb7U
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0xb4U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0xbdU
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 0xbeU
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0xbbU
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                              ? 0xb8U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                               ? 0xa9U
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                ? 0xaaU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                 ? 0xafU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                  ? 0xacU
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                   ? 0xa5U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                    ? 0xa6U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                     ? 0xa3U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                      ? 0xa0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                       ? 0xe1U
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                        ? 0xe2U
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                         ? 0xe7U
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                          ? 0xe4U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                           ? 0xedU
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                            ? 0xeeU
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                             ? 0xebU
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                              ? 0xe8U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                               ? 0xf9U
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                ? 0xfaU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xffU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf5U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf3U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd1U
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd2U
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd7U
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd4U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xddU
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdeU
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdbU
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd8U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc9U
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcaU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcfU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xccU
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc5U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc6U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc3U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc0U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 3U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_ha84e887c__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0x29U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                             ? 0x2cU
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                 ? 0x2fU
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                  ? 0x26U
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                   ? 0x25U
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0x20U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0x23U
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 0x32U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 0x31U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 0x34U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 0x37U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0x3eU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0x3dU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 0x38U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0x3bU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                              ? 0x7aU
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                               ? 0x79U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                ? 0x7cU
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                 ? 0x7fU
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                  ? 0x76U
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                   ? 0x75U
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                    ? 0x70U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                     ? 0x73U
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                      ? 0x62U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                       ? 0x61U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                        ? 0x64U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                         ? 0x67U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                          ? 0x6eU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                           ? 0x6dU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                            ? 0x68U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                             ? 0x6bU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                              ? 0x4aU
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                               ? 0x49U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                ? 0x4cU
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdaU
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd9U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdcU
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdfU
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd6U
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd5U
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd0U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xd3U
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc2U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc1U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc4U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc7U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xceU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcdU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xc8U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcbU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xeaU
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xe9U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xecU
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xefU
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xe6U
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xe5U
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xe0U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xe3U
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf1U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf7U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfdU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfbU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xbaU
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xb9U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xbcU
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xbfU
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xb6U
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xb5U
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xb0U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xb3U
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa1U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa7U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xaeU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xadU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xabU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x85U
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x81U
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x87U
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x88U
                                                                                 : __Vdeeptemp_h0ad28bb0__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h7180186a__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0x2aU : __Vdeeptemp_ha84e887c__0);
    vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_14 
        = (((IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12) 
            ^ (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1)) 
           ^ (((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                ? 0xe5U : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                            ? 0xe7U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                        ? 0xe1U : (
                                                   (0xfcU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                    ? 0xe3U
                                                    : 
                                                   ((0xfbU 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                     ? 0xedU
                                                     : 
                                                    ((0xfaU 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                      ? 0xefU
                                                      : 
                                                     ((0xf9U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                       ? 0xe9U
                                                       : 
                                                      ((0xf8U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                        ? 0xebU
                                                        : 
                                                       ((0xf7U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                         ? 0xf5U
                                                         : 
                                                        ((0xf6U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                          ? 0xf7U
                                                          : 
                                                         ((0xf5U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                           ? 0xf1U
                                                           : 
                                                          ((0xf4U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                            ? 0xf3U
                                                            : 
                                                           ((0xf3U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                             ? 0xfdU
                                                             : 
                                                            ((0xf2U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                              ? 0xffU
                                                              : 
                                                             ((0xf1U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                               ? 0xf9U
                                                               : 
                                                              ((0xf0U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6))
                                                                ? 0xfbU
                                                                : __Vdeeptemp_h587e09a3__0)))))))))))))))) 
              ^ ((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                  ? 0x1aU : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                              ? 0x19U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                          ? 0x1cU : 
                                         ((0xfcU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                           ? 0x1fU : 
                                          ((0xfbU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                            ? 0x16U
                                            : ((0xfaU 
                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                ? 0x15U
                                                : (
                                                   (0xf9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0x10U
                                                    : 
                                                   ((0xf8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0x13U
                                                     : 
                                                    ((0xf7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 2U
                                                      : 
                                                     ((0xf6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 1U
                                                       : 
                                                      ((0xf5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 4U
                                                        : 
                                                       ((0xf4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 7U
                                                         : 
                                                        ((0xf3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0xeU
                                                          : 
                                                         ((0xf2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0xdU
                                                           : 
                                                          ((0xf1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 8U
                                                            : 
                                                           ((0xf0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0xbU
                                                             : __Vdeeptemp_h7180186a__0))))))))))))))))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_14 
        = ((IData)(vlSelfRef.io_roundKey_14) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_14)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_14))));
}

VL_INLINE_OPT void VCipher___024root___nba_sequent__TOP__23(VCipher___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VCipher___024root___nba_sequent__TOP__23\n"); );
    VCipher__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*31:0*/ __Vdeeptemp_he8c61e9b__0;
    CData/*31:0*/ __Vdeeptemp_heac811dc__0;
    CData/*31:0*/ __Vdeeptemp_hb815cc1d__0;
    CData/*31:0*/ __Vdeeptemp_h215aa9fe__0;
    CData/*31:0*/ __Vdeeptemp_h02892c17__0;
    CData/*31:0*/ __Vdeeptemp_hfb0c7ce0__0;
    // Body
    __Vdeeptemp_he8c61e9b__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                 ? 0x99U : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                             ? 0x9aU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                 ? 0x9fU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                  ? 0x9cU
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                   ? 0x95U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                    ? 0x96U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                     ? 0x93U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                      ? 0x90U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                       ? 0xb1U
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                        ? 0xb2U
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                         ? 0xb7U
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                          ? 0xb4U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                           ? 0xbdU
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                            ? 0xbeU
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                             ? 0xbbU
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                              ? 0xb8U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                               ? 0xa9U
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                ? 0xaaU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                 ? 0xafU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                  ? 0xacU
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                   ? 0xa5U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                    ? 0xa6U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                     ? 0xa3U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                      ? 0xa0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                       ? 0xe1U
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                        ? 0xe2U
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                         ? 0xe7U
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                          ? 0xe4U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                           ? 0xedU
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                            ? 0xeeU
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                             ? 0xebU
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                              ? 0xe8U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                               ? 0xf9U
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                ? 0xfaU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xffU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf5U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf3U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd1U
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd2U
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd7U
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd4U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xddU
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xdeU
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xdbU
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd8U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc9U
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xcaU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xcfU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xccU
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc5U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc6U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc3U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc0U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 3U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h02892c17__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                 ? 0x29U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                             ? 0x2cU
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                 ? 0x2fU
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                  ? 0x26U
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                   ? 0x25U
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                    ? 0x20U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                     ? 0x23U
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                      ? 0x32U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                       ? 0x31U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                        ? 0x34U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                         ? 0x37U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                          ? 0x3eU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                           ? 0x3dU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                            ? 0x38U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                             ? 0x3bU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                              ? 0x7aU
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                               ? 0x79U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                ? 0x7cU
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                 ? 0x7fU
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                  ? 0x76U
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                   ? 0x75U
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                    ? 0x70U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                     ? 0x73U
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                      ? 0x62U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                       ? 0x61U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                        ? 0x64U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                         ? 0x67U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                          ? 0x6eU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                           ? 0x6dU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                            ? 0x68U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                             ? 0x6bU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                              ? 0x4aU
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                               ? 0x49U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                ? 0x4cU
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xdaU
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd9U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xdcU
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xdfU
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd6U
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd5U
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd0U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xd3U
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc2U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc1U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc4U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc7U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xceU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xcdU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xc8U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xcbU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xeaU
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xe9U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xecU
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xefU
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xe6U
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xe5U
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xe0U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xe3U
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf1U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf7U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xfdU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xfbU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xbaU
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xb9U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xbcU
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xbfU
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xb6U
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xb5U
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xb0U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xb3U
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xa1U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xa7U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xaeU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xadU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0xabU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x85U
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x81U
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x87U
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                                                 ? 0x88U
                                                                                 : __Vdeeptemp_he8c61e9b__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_heac811dc__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                 ? 0x2aU : __Vdeeptemp_h02892c17__0);
    __Vdeeptemp_hb815cc1d__0 = ((0x77U == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0xeeU : ((0x76U 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                             ? 0xecU
                                             : ((0x75U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                 ? 0xeaU
                                                 : 
                                                ((0x74U 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                  ? 0xe8U
                                                  : 
                                                 ((0x73U 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                   ? 0xe6U
                                                   : 
                                                  ((0x72U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0xe4U
                                                    : 
                                                   ((0x71U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0xe2U
                                                     : 
                                                    ((0x70U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 0xe0U
                                                      : 
                                                     ((0x6fU 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 0xdeU
                                                       : 
                                                      ((0x6eU 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 0xdcU
                                                        : 
                                                       ((0x6dU 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 0xdaU
                                                         : 
                                                        ((0x6cU 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0xd8U
                                                          : 
                                                         ((0x6bU 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0xd6U
                                                           : 
                                                          ((0x6aU 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 0xd4U
                                                            : 
                                                           ((0x69U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0xd2U
                                                             : 
                                                            ((0x68U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                              ? 0xd0U
                                                              : 
                                                             ((0x67U 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                               ? 0xceU
                                                               : 
                                                              ((0x66U 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                ? 0xccU
                                                                : 
                                                               ((0x65U 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                 ? 0xcaU
                                                                 : 
                                                                ((0x64U 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                  ? 0xc8U
                                                                  : 
                                                                 ((0x63U 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                   ? 0xc6U
                                                                   : 
                                                                  ((0x62U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                    ? 0xc4U
                                                                    : 
                                                                   ((0x61U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                     ? 0xc2U
                                                                     : 
                                                                    ((0x60U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                      ? 0xc0U
                                                                      : 
                                                                     ((0x5fU 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                       ? 0xbeU
                                                                       : 
                                                                      ((0x5eU 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                        ? 0xbcU
                                                                        : 
                                                                       ((0x5dU 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                         ? 0xbaU
                                                                         : 
                                                                        ((0x5cU 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                          ? 0xb8U
                                                                          : 
                                                                         ((0x5bU 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                           ? 0xb6U
                                                                           : 
                                                                          ((0x5aU 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                            ? 0xb4U
                                                                            : 
                                                                           ((0x59U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                             ? 0xb2U
                                                                             : 
                                                                            ((0x58U 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                              ? 0xb0U
                                                                              : 
                                                                             ((0x57U 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                               ? 0xaeU
                                                                               : 
                                                                              ((0x56U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                ? 0xacU
                                                                                : 
                                                                               ((0x55U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xaaU
                                                                                 : 
                                                                                ((0x54U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa8U
                                                                                 : 
                                                                                ((0x53U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa6U
                                                                                 : 
                                                                                ((0x52U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa4U
                                                                                 : 
                                                                                ((0x51U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa2U
                                                                                 : 
                                                                                ((0x50U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xa0U
                                                                                 : 
                                                                                ((0x4fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9eU
                                                                                 : 
                                                                                ((0x4eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9cU
                                                                                 : 
                                                                                ((0x4dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9aU
                                                                                 : 
                                                                                ((0x4cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x98U
                                                                                 : 
                                                                                ((0x4bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x96U
                                                                                 : 
                                                                                ((0x4aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x94U
                                                                                 : 
                                                                                ((0x49U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x92U
                                                                                 : 
                                                                                ((0x48U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x90U
                                                                                 : 
                                                                                ((0x47U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8eU
                                                                                 : 
                                                                                ((0x46U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8cU
                                                                                 : 
                                                                                ((0x45U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8aU
                                                                                 : 
                                                                                ((0x44U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x88U
                                                                                 : 
                                                                                ((0x43U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x86U
                                                                                 : 
                                                                                ((0x42U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x84U
                                                                                 : 
                                                                                ((0x41U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x82U
                                                                                 : 
                                                                                ((0x40U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x80U
                                                                                 : 
                                                                                ((0x3fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7eU
                                                                                 : 
                                                                                ((0x3eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7cU
                                                                                 : 
                                                                                ((0x3dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7aU
                                                                                 : 
                                                                                ((0x3cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x78U
                                                                                 : 
                                                                                ((0x3bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x76U
                                                                                 : 
                                                                                ((0x3aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x74U
                                                                                 : 
                                                                                ((0x39U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x72U
                                                                                 : 
                                                                                ((0x38U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x70U
                                                                                 : 
                                                                                ((0x37U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6eU
                                                                                 : 
                                                                                ((0x36U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6cU
                                                                                 : 
                                                                                ((0x35U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6aU
                                                                                 : 
                                                                                ((0x34U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x68U
                                                                                 : 
                                                                                ((0x33U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x66U
                                                                                 : 
                                                                                ((0x32U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x64U
                                                                                 : 
                                                                                ((0x31U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x62U
                                                                                 : 
                                                                                ((0x30U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x60U
                                                                                 : 
                                                                                ((0x2fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5eU
                                                                                 : 
                                                                                ((0x2eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5cU
                                                                                 : 
                                                                                ((0x2dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5aU
                                                                                 : 
                                                                                ((0x2cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x58U
                                                                                 : 
                                                                                ((0x2bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x56U
                                                                                 : 
                                                                                ((0x2aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x54U
                                                                                 : 
                                                                                ((0x29U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x52U
                                                                                 : 
                                                                                ((0x28U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x50U
                                                                                 : 
                                                                                ((0x27U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4eU
                                                                                 : 
                                                                                ((0x26U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4cU
                                                                                 : 
                                                                                ((0x25U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4aU
                                                                                 : 
                                                                                ((0x24U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x48U
                                                                                 : 
                                                                                ((0x23U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x46U
                                                                                 : 
                                                                                ((0x22U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x44U
                                                                                 : 
                                                                                ((0x21U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x42U
                                                                                 : 
                                                                                ((0x20U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x40U
                                                                                 : 
                                                                                ((0x1fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3eU
                                                                                 : 
                                                                                ((0x1eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3cU
                                                                                 : 
                                                                                ((0x1dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3aU
                                                                                 : 
                                                                                ((0x1cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x38U
                                                                                 : 
                                                                                ((0x1bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x36U
                                                                                 : 
                                                                                ((0x1aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x34U
                                                                                 : 
                                                                                ((0x19U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x32U
                                                                                 : 
                                                                                ((0x18U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x30U
                                                                                 : 
                                                                                ((0x17U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2eU
                                                                                 : 
                                                                                ((0x16U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2cU
                                                                                 : 
                                                                                ((0x15U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2aU
                                                                                 : 
                                                                                ((0x14U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x28U
                                                                                 : 
                                                                                ((0x13U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x26U
                                                                                 : 
                                                                                ((0x12U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x24U
                                                                                 : 
                                                                                ((0x11U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x22U
                                                                                 : 
                                                                                ((0x10U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x20U
                                                                                 : 
                                                                                ((0xfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1eU
                                                                                 : 
                                                                                ((0xeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1cU
                                                                                 : 
                                                                                ((0xdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1aU
                                                                                 : 
                                                                                ((0xcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x18U
                                                                                 : 
                                                                                ((0xbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x16U
                                                                                 : 
                                                                                ((0xaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x12U
                                                                                 : 
                                                                                ((8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x10U
                                                                                 : 
                                                                                ((7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xeU
                                                                                 : 
                                                                                ((6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xcU
                                                                                 : 
                                                                                ((5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xaU
                                                                                 : 
                                                                                ((4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 8U
                                                                                 : 
                                                                                ((3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 6U
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 4U
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 2U
                                                                                 : 0U)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_hfb0c7ce0__0 = ((0xeeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0xc7U : ((0xedU 
                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                             ? 0xc1U
                                             : ((0xecU 
                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                 ? 0xc3U
                                                 : 
                                                ((0xebU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                  ? 0xcdU
                                                  : 
                                                 ((0xeaU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                   ? 0xcfU
                                                   : 
                                                  ((0xe9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0xc9U
                                                    : 
                                                   ((0xe8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0xcbU
                                                     : 
                                                    ((0xe7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 0xd5U
                                                      : 
                                                     ((0xe6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 0xd7U
                                                       : 
                                                      ((0xe5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 0xd1U
                                                        : 
                                                       ((0xe4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 0xd3U
                                                         : 
                                                        ((0xe3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0xddU
                                                          : 
                                                         ((0xe2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0xdfU
                                                           : 
                                                          ((0xe1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 0xd9U
                                                            : 
                                                           ((0xe0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0xdbU
                                                             : 
                                                            ((0xdfU 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                              ? 0xa5U
                                                              : 
                                                             ((0xdeU 
                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                               ? 0xa7U
                                                               : 
                                                              ((0xddU 
                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                ? 0xa1U
                                                                : 
                                                               ((0xdcU 
                                                                 == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                 ? 0xa3U
                                                                 : 
                                                                ((0xdbU 
                                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                  ? 0xadU
                                                                  : 
                                                                 ((0xdaU 
                                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                   ? 0xafU
                                                                   : 
                                                                  ((0xd9U 
                                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                    ? 0xa9U
                                                                    : 
                                                                   ((0xd8U 
                                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                     ? 0xabU
                                                                     : 
                                                                    ((0xd7U 
                                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                      ? 0xb5U
                                                                      : 
                                                                     ((0xd6U 
                                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                       ? 0xb7U
                                                                       : 
                                                                      ((0xd5U 
                                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                        ? 0xb1U
                                                                        : 
                                                                       ((0xd4U 
                                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                         ? 0xb3U
                                                                         : 
                                                                        ((0xd3U 
                                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                          ? 0xbdU
                                                                          : 
                                                                         ((0xd2U 
                                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                           ? 0xbfU
                                                                           : 
                                                                          ((0xd1U 
                                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                            ? 0xb9U
                                                                            : 
                                                                           ((0xd0U 
                                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                             ? 0xbbU
                                                                             : 
                                                                            ((0xcfU 
                                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                              ? 0x85U
                                                                              : 
                                                                             ((0xceU 
                                                                               == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                               ? 0x87U
                                                                               : 
                                                                              ((0xcdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                ? 0x81U
                                                                                : 
                                                                               ((0xccU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x83U
                                                                                 : 
                                                                                ((0xcbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8dU
                                                                                 : 
                                                                                ((0xcaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8fU
                                                                                 : 
                                                                                ((0xc9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x89U
                                                                                 : 
                                                                                ((0xc8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x8bU
                                                                                 : 
                                                                                ((0xc7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x95U
                                                                                 : 
                                                                                ((0xc6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x97U
                                                                                 : 
                                                                                ((0xc5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x91U
                                                                                 : 
                                                                                ((0xc4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x93U
                                                                                 : 
                                                                                ((0xc3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9dU
                                                                                 : 
                                                                                ((0xc2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9fU
                                                                                 : 
                                                                                ((0xc1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x99U
                                                                                 : 
                                                                                ((0xc0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x9bU
                                                                                 : 
                                                                                ((0xbfU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x65U
                                                                                 : 
                                                                                ((0xbeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x67U
                                                                                 : 
                                                                                ((0xbdU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x61U
                                                                                 : 
                                                                                ((0xbcU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x63U
                                                                                 : 
                                                                                ((0xbbU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6dU
                                                                                 : 
                                                                                ((0xbaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6fU
                                                                                 : 
                                                                                ((0xb9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x69U
                                                                                 : 
                                                                                ((0xb8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x6bU
                                                                                 : 
                                                                                ((0xb7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x75U
                                                                                 : 
                                                                                ((0xb6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x77U
                                                                                 : 
                                                                                ((0xb5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x71U
                                                                                 : 
                                                                                ((0xb4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x73U
                                                                                 : 
                                                                                ((0xb3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7dU
                                                                                 : 
                                                                                ((0xb2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7fU
                                                                                 : 
                                                                                ((0xb1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x79U
                                                                                 : 
                                                                                ((0xb0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x7bU
                                                                                 : 
                                                                                ((0xafU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x45U
                                                                                 : 
                                                                                ((0xaeU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x47U
                                                                                 : 
                                                                                ((0xadU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x41U
                                                                                 : 
                                                                                ((0xacU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x43U
                                                                                 : 
                                                                                ((0xabU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4dU
                                                                                 : 
                                                                                ((0xaaU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4fU
                                                                                 : 
                                                                                ((0xa9U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x49U
                                                                                 : 
                                                                                ((0xa8U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x4bU
                                                                                 : 
                                                                                ((0xa7U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x55U
                                                                                 : 
                                                                                ((0xa6U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x57U
                                                                                 : 
                                                                                ((0xa5U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x51U
                                                                                 : 
                                                                                ((0xa4U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x53U
                                                                                 : 
                                                                                ((0xa3U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5dU
                                                                                 : 
                                                                                ((0xa2U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5fU
                                                                                 : 
                                                                                ((0xa1U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x59U
                                                                                 : 
                                                                                ((0xa0U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x5bU
                                                                                 : 
                                                                                ((0x9fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x25U
                                                                                 : 
                                                                                ((0x9eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x27U
                                                                                 : 
                                                                                ((0x9dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x21U
                                                                                 : 
                                                                                ((0x9cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x23U
                                                                                 : 
                                                                                ((0x9bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2dU
                                                                                 : 
                                                                                ((0x9aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2fU
                                                                                 : 
                                                                                ((0x99U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x29U
                                                                                 : 
                                                                                ((0x98U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x2bU
                                                                                 : 
                                                                                ((0x97U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x35U
                                                                                 : 
                                                                                ((0x96U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x37U
                                                                                 : 
                                                                                ((0x95U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x31U
                                                                                 : 
                                                                                ((0x94U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x33U
                                                                                 : 
                                                                                ((0x93U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3dU
                                                                                 : 
                                                                                ((0x92U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3fU
                                                                                 : 
                                                                                ((0x91U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x39U
                                                                                 : 
                                                                                ((0x90U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x3bU
                                                                                 : 
                                                                                ((0x8fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 5U
                                                                                 : 
                                                                                ((0x8eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 7U
                                                                                 : 
                                                                                ((0x8dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 1U
                                                                                 : 
                                                                                ((0x8cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 3U
                                                                                 : 
                                                                                ((0x8bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xdU
                                                                                 : 
                                                                                ((0x8aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfU
                                                                                 : 
                                                                                ((0x89U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 9U
                                                                                 : 
                                                                                ((0x88U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xbU
                                                                                 : 
                                                                                ((0x87U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x15U
                                                                                 : 
                                                                                ((0x86U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0x85U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x11U
                                                                                 : 
                                                                                ((0x84U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x13U
                                                                                 : 
                                                                                ((0x83U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1dU
                                                                                 : 
                                                                                ((0x82U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1fU
                                                                                 : 
                                                                                ((0x81U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x19U
                                                                                 : 
                                                                                ((0x80U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0x1bU
                                                                                 : 
                                                                                ((0x7fU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfeU
                                                                                 : 
                                                                                ((0x7eU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfcU
                                                                                 : 
                                                                                ((0x7dU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xfaU
                                                                                 : 
                                                                                ((0x7cU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf8U
                                                                                 : 
                                                                                ((0x7bU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf6U
                                                                                 : 
                                                                                ((0x7aU 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf4U
                                                                                 : 
                                                                                ((0x79U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf2U
                                                                                 : 
                                                                                ((0x78U 
                                                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                                                 ? 0xf0U
                                                                                 : __Vdeeptemp_hb815cc1d__0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
    __Vdeeptemp_h215aa9fe__0 = ((0xefU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                 ? 0xc5U : __Vdeeptemp_hfb0c7ce0__0);
    vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_15 
        = ((((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
              ? 0x1aU : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                          ? 0x19U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                      ? 0x1cU : ((0xfcU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                  ? 0x1fU
                                                  : 
                                                 ((0xfbU 
                                                   == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                   ? 0x16U
                                                   : 
                                                  ((0xfaU 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                    ? 0x15U
                                                    : 
                                                   ((0xf9U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                     ? 0x10U
                                                     : 
                                                    ((0xf8U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                      ? 0x13U
                                                      : 
                                                     ((0xf7U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                       ? 2U
                                                       : 
                                                      ((0xf6U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                        ? 1U
                                                        : 
                                                       ((0xf5U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                         ? 4U
                                                         : 
                                                        ((0xf4U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                          ? 7U
                                                          : 
                                                         ((0xf3U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                           ? 0xeU
                                                           : 
                                                          ((0xf2U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                            ? 0xdU
                                                            : 
                                                           ((0xf1U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                             ? 8U
                                                             : 
                                                            ((0xf0U 
                                                              == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_12))
                                                              ? 0xbU
                                                              : __Vdeeptemp_heac811dc__0)))))))))))))))) 
            ^ (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_1)) 
           ^ ((IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_6) 
              ^ ((0xffU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                  ? 0xe5U : ((0xfeU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                              ? 0xe7U : ((0xfdU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                          ? 0xe1U : 
                                         ((0xfcU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                           ? 0xe3U : 
                                          ((0xfbU == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                            ? 0xedU
                                            : ((0xfaU 
                                                == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                ? 0xefU
                                                : (
                                                   (0xf9U 
                                                    == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                    ? 0xe9U
                                                    : 
                                                   ((0xf8U 
                                                     == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                     ? 0xebU
                                                     : 
                                                    ((0xf7U 
                                                      == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                      ? 0xf5U
                                                      : 
                                                     ((0xf6U 
                                                       == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                       ? 0xf7U
                                                       : 
                                                      ((0xf5U 
                                                        == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                        ? 0xf1U
                                                        : 
                                                       ((0xf4U 
                                                         == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                         ? 0xf3U
                                                         : 
                                                        ((0xf3U 
                                                          == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                          ? 0xfdU
                                                          : 
                                                         ((0xf2U 
                                                           == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                           ? 0xffU
                                                           : 
                                                          ((0xf1U 
                                                            == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                            ? 0xf9U
                                                            : 
                                                           ((0xf0U 
                                                             == (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11))
                                                             ? 0xfbU
                                                             : __Vdeeptemp_h215aa9fe__0))))))))))))))))));
    vlSelfRef.Cipher__DOT__AddRoundKeyModule_io_state_out_15 
        = ((IData)(vlSelfRef.io_roundKey_15) ^ ((1U 
                                                 == (IData)(vlSelfRef.Cipher__DOT__STM))
                                                 ? (IData)(vlSelfRef.io_plaintext_15)
                                                 : 
                                                ((0xaU 
                                                  == (IData)(vlSelfRef.Cipher__DOT__rounds))
                                                  ? (IData)(vlSelfRef.Cipher__DOT__SubBytesModule_io_state_out_11)
                                                  : (IData)(vlSelfRef.Cipher__DOT__MixColumnsModule_io_state_out_15))));
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
