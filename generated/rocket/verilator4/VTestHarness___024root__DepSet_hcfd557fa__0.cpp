// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

void VTestHarness___024root___ico_sequent__TOP__0(VTestHarness___024root* vlSelf);

void VTestHarness___024root___eval_ico(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_ico\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VTestHarness___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void VTestHarness___024root___ico_sequent__TOP__0(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___ico_sequent__TOP__0\n"); );
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
    vlSelfRef.io_success = (1U == vlSelfRef.TestHarness__DOT__SimDTM__DOT__exit_reg);
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__asource__DOT__bundleOut_0_a_source__DOT__source_valid_0_reset 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__debug_reset_syncd_debug_reset_sync__DOT__output_chain__DOT__sync_0)) 
                 | (IData)(vlSelfRef.reset)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__latch 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)) 
           & (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_haltreq 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
           & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
              >> 0x1fU));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_clrresethaltreq 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
           & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
              >> 2U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmOuter__DOT__DMCONTROLWrData_setresethaltreq 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg)) 
           & (vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg 
              >> 3U));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_trace_0_exception) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__trapToDebug) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_62 
                = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mepc);
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_55 
                = (0xffffffffffULL & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)
                                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc
                                       : (~ (1ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc)))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_54 
                = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_sepc);
        } else {
            if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__delegate) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_62 
                    = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mepc);
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_54 
                    = (0xffffffffffULL & (~ (1ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc))));
            } else {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_62 
                    = (0xffffffffffULL & (~ (1ULL | 
                                             (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc))));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_54 
                    = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_sepc);
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_55 
                = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc);
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_62 
            = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mepc);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_55 
            = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_54 
            = (0xffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_sepc);
    }
    if ((1U & (~ (IData)(vlSelfRef.clock)))) {
        vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate__DOT__en_latched 
            = vlSelfRef.TestHarness__DOT__clock_en;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_data 
        = ((0x1eU >= (0x1fU & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1))))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf
           [(0x1fU & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1)))]
            : 0ULL);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_id_rs_MPORT_1_data 
        = ((0x1eU >= (0x1fU & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2))))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf
           [(0x1fU & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2)))]
            : 0ULL);
    if ((2U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address 
            = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg) 
               << 2U);
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 4U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address 
            = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg) 
               << 2U);
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_opcode = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_out_1_a_bits_address = 0x48U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut_reset_reg__DOT__reg_) 
           | (IData)(vlSelfRef.reset));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_6 
        = (0xffffffffffULL & (~ ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc) 
                                 | (QData)((IData)(
                                                   ((1U 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa 
                                                                >> 2U)))
                                                     ? 1U
                                                     : 3U))))));
    vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate_out 
        = ((IData)(vlSelfRef.TestHarness__DOT__gated_clock_debug_clock_gate__DOT__en_latched) 
           & (IData)(vlSelfRef.clock));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
        = (0xffffffffffULL & (~ (1ULL | (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid)
                                             ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_exception) 
                                                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_eret))
                                                 ? 
                                                ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__insn_ret)
                                                  ? 
                                                 ((0x20000000U 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst)
                                                   ? 
                                                  ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_0)
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_6
                                                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_4)
                                                   : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__lo_8)
                                                  : 
                                                 ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__trapToDebug)
                                                   ? (QData)((IData)(
                                                                     ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)
                                                                       ? 
                                                                      ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__insn_break)
                                                                        ? 0x800U
                                                                        : 0x808U)
                                                                       : 0x800U)))
                                                   : 
                                                  (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__notDebugTVec_base) 
                                                    & (IData)(
                                                              (0x8000000000000000ULL 
                                                               == 
                                                               (0x80000000000000c0ULL 
                                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__cause))))
                                                    ? 
                                                   ((0xffffffffffffff00ULL 
                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__notDebugTVec_base) 
                                                    | (QData)((IData)(
                                                                      (0xfcU 
                                                                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__cause) 
                                                                          << 2U)))))
                                                    : 
                                                   (0xfffffffffffffffcULL 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__notDebugTVec_base))))
                                                 : 
                                                ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__replay_wb_common)
                                                  ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc
                                                  : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_npc))
                                             : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_replay)
                                                 ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_pc
                                                 : 
                                                (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_taken)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_5)
                                                   : 
                                                  ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_btb_taken)
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_5)
                                                    : 
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_valid) 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictReturn_1)) 
                                                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_5))))
                                                  ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_head_bits
                                                  : 
                                                 ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_taken)
                                                   ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT___GEN_46
                                                   : 
                                                  ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_btb_taken)
                                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT___GEN_46
                                                    : 
                                                   (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_valid) 
                                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictBranch_1) 
                                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictJump_1)))
                                                     ? 
                                                    (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_prevRVI_1)
                                                       ? 
                                                      ((2ULL 
                                                        | (~ 
                                                           (3ULL 
                                                            | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_pc)))) 
                                                       - 2ULL)
                                                       : 
                                                      (2ULL 
                                                       | (~ 
                                                          (3ULL 
                                                           | (~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_pc))))) 
                                                     + 
                                                     (((QData)((IData)(
                                                                       (0xffU 
                                                                        & (- (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT___taken_npc_T_9 
                                                                                >> 0x1fU)))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT___taken_npc_T_9))))
                                                     : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT___GEN_46))))))))));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_ren 
        = ((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                       >> 2U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_ren_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_valid) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                      >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT___mem_idx_T_1)
                      : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                                 >> 3U))));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
        = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___wdata_T_6 
           & (((2U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_cmd))
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_rdata
                : 0ULL) | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_wdata));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_368 = 0xc0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_439 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___GEN_70 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_440 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_585 = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_586 = 0ULL;
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
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0));
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
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT____VdfgRegularize_h7ef8c9b1_0_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_mie_T_4 
        = (((~ (0x222ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg)) 
            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie) 
           | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_sip_T_2);
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

void VTestHarness___024root___eval_triggers__ico(VTestHarness___024root* vlSelf);

bool VTestHarness___024root___eval_phase__ico(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_phase__ico\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VTestHarness___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        VTestHarness___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VTestHarness___024root___eval_act(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___eval_act\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__0(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__0\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 = 0;
    SData/*8:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 = 0;
    CData/*1:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 0;
    CData/*0:0*/ __VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0;
    __VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 0;
    IData/*30:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0 = 0;
    CData/*2:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0 = 0;
    IData/*30:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0 = 0;
    CData/*2:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0 = 0;
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
    // Body
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_3__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_2__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_1__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_2__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_3__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_1__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_echo_real_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_burst__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_len__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
    __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_en) 
         & (3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0)))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_3__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0_MPORT_2_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_3__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_3__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_3__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_3__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_3__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_en) 
         & (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0)))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_2__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0_MPORT_2_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_2__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_2__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_2__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_2__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_2__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_en) 
         & (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0)))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_1__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0_MPORT_2_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_1__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_1__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_1__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_1__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_1__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_en) 
         & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0)))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0_MPORT_2_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_1_0__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_1) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 8U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_3) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x18U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_4) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x20U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_3) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x18U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_2) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x10U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_7) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x38U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_4) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x20U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_4) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x20U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_6) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x30U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_5) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x28U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_2) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x10U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_5) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x28U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_5) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x28U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_2) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x10U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_2) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x10U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_1) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 8U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_7) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x38U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 2U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_6) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x30U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_7) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x38U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_5) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x28U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_1) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 8U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_7) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x38U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_1) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 8U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_3) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 1U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x18U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_3) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x18U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en) 
         & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__eccMask_4) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_way_en) 
               >> 3U)))) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_wdata 
                                >> 0x20U)));
        __VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        __VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__w_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__w_sel1)
                ? 0U : 3U);
        __VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__w_echo_real_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__maybe_full)
                ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id
               [0U] : vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1]);
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 
            = (0x7fffffffU & (~ ((~ vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__addr) 
                                 | (7U & (~ ((IData)(7U) 
                                             << (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_size)))))));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0 
            = (0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_echo_real_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)
                ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id
               [0U] : vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1]);
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 = 1U;
    }
    if (vlSelfRef.reset) {
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__flight = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter_3 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__busy = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_12 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_14 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value)));
        }
        vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__flight 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__next_flight;
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter_3 
                = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter1_3))) 
                   && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter1_3));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_valid))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__busy 
                = (0U != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xcU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_12 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_12_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xeU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_14 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_14_T));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__maybe_full 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_enq_ready)
                    ? ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_ready))) 
                       && ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_enq_ready) 
                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_deq_valid)))
                    : ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_enq_ready) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_deq_valid)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_enq_ready)
                    ? ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_ready))) 
                       && ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_enq_ready) 
                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_deq_valid)))
                    : ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_enq_ready) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_deq_valid)));
        }
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 
            = (0x7fffffffU & (~ ((~ vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__addr_1) 
                                 | (7U & (~ ((IData)(7U) 
                                             << (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_size)))))));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_echo_real_last__v0 
            = (0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len_1));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_echo_real_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_addr;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_addr__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_len;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_len__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_burst__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen = 0U;
        __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__b_count_0 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__b_count_1 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_1 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__doneAW = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__counter = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_15 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_14 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_13 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_12 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_11 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_10 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_9 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_8 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_7 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_6 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_5 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_4 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_3 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_2 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_1 = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value)));
        }
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__mem_wen)
                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__killm)
                    ? (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen) 
                             >> 1U)) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wen_T_2))
                : (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen) 
                         >> 1U)));
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) {
            __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT___value_T_3;
        }
        if ((3U & (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_b_bits_echo_real_last)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_b_valid)) 
                   & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__q_b_deq_io_deq_bits_id))))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__b_count_0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___b_count_0_T_1;
        }
        if ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi4yank_auto_in_b_bits_echo_real_last)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl_auto_in_b_valid)) 
             & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__q_b_deq_io_deq_bits_id)) 
                >> 1U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT__b_count_1 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__axi42tl__DOT___b_count_1_T_1;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en;
        }
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_12;
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__doneAW 
                = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_bits_last)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_a_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__counter 
                = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__a_first)
                          ? ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_a_bits_opcode))
                              ? 0U : (~ (7U & (((IData)(0x3fU) 
                                                << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_a_bits_size)) 
                                               >> 3U))))
                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__counter1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor_1__DOT__a_first_done) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_15 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_14;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_14 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_13;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_13 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_12;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_12 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_11;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_11 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_10;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_10 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_9;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_9 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_8;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_8 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_7;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_7 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_6;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_6 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_5;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_5 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_4;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_4 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_3 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_2 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_1 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_0;
        }
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 
            = (((QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                     ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7
                                    [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7_rdata_MPORT_addr_pipe_0]
                                     : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_7)) 
                                   << 0x18U) | (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                  ? 
                                                 vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6
                                                 [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_6_rdata_MPORT_addr_pipe_0]
                                                  : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_6)) 
                                                << 0x10U)) 
                                 | ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                       ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5
                                      [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5_rdata_MPORT_addr_pipe_0]
                                       : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_5)) 
                                     << 8U) | ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4
                                               [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4_rdata_MPORT_addr_pipe_0]
                                                : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_4)))))) 
                << 0x20U) | (QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                 ? 
                                                vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3
                                                [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_3_rdata_MPORT_addr_pipe_0]
                                                 : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_3)) 
                                               << 0x18U) 
                                              | (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                   ? 
                                                  vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2
                                                  [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_2_rdata_MPORT_addr_pipe_0]
                                                   : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_2)) 
                                                 << 0x10U)) 
                                             | ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                   ? 
                                                  vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1
                                                  [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1_rdata_MPORT_addr_pipe_0]
                                                   : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_1)) 
                                                 << 8U) 
                                                | ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_REG)
                                                    ? 
                                                   vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0
                                                   [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_rdata_MPORT_addr_pipe_0]
                                                    : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__rdata_r_0)))))));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 
            = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_sel1)
                ? 0U : 3U);
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__r_echo_real_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 = 1U;
    }
    vlSelfRef.TestHarness__DOT__SimDTM__DOT__exit_reg 
        = vlSelfRef.TestHarness__DOT__SimDTM__DOT_____05Fexit;
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu_io_in_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__inPipe_bits_in2[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu_io_in_bits_in2[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__inPipe_bits_in2[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu_io_in_bits_in2[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__inPipe_bits_in2[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu_io_in_bits_in2[2U];
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__advance_pstore1) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_hi_lo_hi 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 0x28U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_lo_lo_lo 
            = (0xffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_lo_lo_hi 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 8U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_lo_hi_lo 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 0x10U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_hi_lo_lo 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 0x20U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_hi_hi_lo 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 0x30U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_storegen_data_hi_hi_hi 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__amoalu_io_out 
                                >> 0x38U)));
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
         & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_valid))) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__r_addr 
            = (0x7fffffffU & ((0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_burst))
                               ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_addr
                               : ((2U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_burst))
                                   ? ((~ ((~ vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_io_deq_bits_addr) 
                                          | vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_49)) 
                                      | (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__inc_addr 
                                         & vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_49))
                                   : vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__inc_addr)));
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__w_full 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams_auto_in_aw_ready) 
                                                    & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_deq_valid)) 
                                                   | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT___GEN_0)));
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_valid) 
         & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_write)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_22_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_14_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28_rdata_data_addr_pipe_0 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_addr) 
                         >> 3U));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_1) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__write_1 
            = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                        >> 2U)));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_2) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__write_2 
            = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                        >> 2U)));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_4 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_14) 
                     - (0x1fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                  >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_5 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_18) 
                     - (0xfU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                 >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_2) 
                     - (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18)))));
    __Vtemp_1[0U] = 1U;
    __Vtemp_1[1U] = 0U;
    __Vtemp_1[2U] = 0U;
    __Vtemp_1[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_2, __Vtemp_1, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_2 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_6) 
                     - ((__Vtemp_2[0U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_3[0U] = 1U;
    __Vtemp_3[1U] = 0U;
    __Vtemp_3[2U] = 0U;
    __Vtemp_3[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_4, __Vtemp_3, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_3 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_10) 
                     - ((__Vtemp_4[0U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_5[0U] = 1U;
    __Vtemp_5[1U] = 0U;
    __Vtemp_5[2U] = 0U;
    __Vtemp_5[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_6, __Vtemp_5, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_4 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_14) 
                     - ((__Vtemp_6[0U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_7[0U] = 1U;
    __Vtemp_7[1U] = 0U;
    __Vtemp_7[2U] = 0U;
    __Vtemp_7[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_8, __Vtemp_7, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_5 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_18) 
                     - ((__Vtemp_8[0U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_9[0U] = 1U;
    __Vtemp_9[1U] = 0U;
    __Vtemp_9[2U] = 0U;
    __Vtemp_9[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_10, __Vtemp_9, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_6 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_22) 
                     - ((__Vtemp_10[0U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_11[0U] = 1U;
    __Vtemp_11[1U] = 0U;
    __Vtemp_11[2U] = 0U;
    __Vtemp_11[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_12, __Vtemp_11, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_7 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_26) 
                     - ((__Vtemp_12[0U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_13[0U] = 1U;
    __Vtemp_13[1U] = 0U;
    __Vtemp_13[2U] = 0U;
    __Vtemp_13[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_14, __Vtemp_13, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_8 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_30) 
                     - ((__Vtemp_14[0U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_15[0U] = 1U;
    __Vtemp_15[1U] = 0U;
    __Vtemp_15[2U] = 0U;
    __Vtemp_15[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_16, __Vtemp_15, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_9 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_34) 
                     - ((__Vtemp_16[0U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_17[0U] = 1U;
    __Vtemp_17[1U] = 0U;
    __Vtemp_17[2U] = 0U;
    __Vtemp_17[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_18, __Vtemp_17, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_18 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_70) 
                     - ((__Vtemp_18[0U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_19[0U] = 1U;
    __Vtemp_19[1U] = 0U;
    __Vtemp_19[2U] = 0U;
    __Vtemp_19[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_20, __Vtemp_19, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_19 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_74) 
                     - ((__Vtemp_20[0U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_21[0U] = 1U;
    __Vtemp_21[1U] = 0U;
    __Vtemp_21[2U] = 0U;
    __Vtemp_21[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_22, __Vtemp_21, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_20 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_78) 
                     - ((__Vtemp_22[0U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_23[0U] = 1U;
    __Vtemp_23[1U] = 0U;
    __Vtemp_23[2U] = 0U;
    __Vtemp_23[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_24, __Vtemp_23, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_21 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_82) 
                     - ((__Vtemp_24[0U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_25[0U] = 1U;
    __Vtemp_25[1U] = 0U;
    __Vtemp_25[2U] = 0U;
    __Vtemp_25[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_26, __Vtemp_25, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_30 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_118) 
                     - ((__Vtemp_26[0U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_27[0U] = 1U;
    __Vtemp_27[1U] = 0U;
    __Vtemp_27[2U] = 0U;
    __Vtemp_27[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_28, __Vtemp_27, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_31 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_122) 
                     - ((__Vtemp_28[0U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_29[0U] = 1U;
    __Vtemp_29[1U] = 0U;
    __Vtemp_29[2U] = 0U;
    __Vtemp_29[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_30, __Vtemp_29, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_32 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_126) 
                     - ((__Vtemp_30[0U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_31[0U] = 1U;
    __Vtemp_31[1U] = 0U;
    __Vtemp_31[2U] = 0U;
    __Vtemp_31[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_32, __Vtemp_31, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_33 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_130) 
                     - (__Vtemp_32[1U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_33[0U] = 1U;
    __Vtemp_33[1U] = 0U;
    __Vtemp_33[2U] = 0U;
    __Vtemp_33[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_34, __Vtemp_33, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_50 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_198) 
                     - ((__Vtemp_34[1U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_35[0U] = 1U;
    __Vtemp_35[1U] = 0U;
    __Vtemp_35[2U] = 0U;
    __Vtemp_35[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_36, __Vtemp_35, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_51 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_202) 
                     - ((__Vtemp_36[1U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_37[0U] = 1U;
    __Vtemp_37[1U] = 0U;
    __Vtemp_37[2U] = 0U;
    __Vtemp_37[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_38, __Vtemp_37, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_53 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_210) 
                     - ((__Vtemp_38[1U] >> 0x14U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_39[0U] = 1U;
    __Vtemp_39[1U] = 0U;
    __Vtemp_39[2U] = 0U;
    __Vtemp_39[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_40, __Vtemp_39, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_54 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_214) 
                     - ((__Vtemp_40[1U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_41[0U] = 1U;
    __Vtemp_41[1U] = 0U;
    __Vtemp_41[2U] = 0U;
    __Vtemp_41[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_42, __Vtemp_41, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_55 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_218) 
                     - ((__Vtemp_42[1U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_43[0U] = 1U;
    __Vtemp_43[1U] = 0U;
    __Vtemp_43[2U] = 0U;
    __Vtemp_43[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_44, __Vtemp_43, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_56 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_222) 
                     - ((__Vtemp_44[1U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_45[0U] = 1U;
    __Vtemp_45[1U] = 0U;
    __Vtemp_45[2U] = 0U;
    __Vtemp_45[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_46, __Vtemp_45, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_61 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_242) 
                     - ((__Vtemp_46[1U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_47[0U] = 1U;
    __Vtemp_47[1U] = 0U;
    __Vtemp_47[2U] = 0U;
    __Vtemp_47[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_48, __Vtemp_47, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_62 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_246) 
                     - ((__Vtemp_48[1U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_49[0U] = 1U;
    __Vtemp_49[1U] = 0U;
    __Vtemp_49[2U] = 0U;
    __Vtemp_49[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_50, __Vtemp_49, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_67 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_266) 
                     - ((__Vtemp_50[2U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_51[0U] = 1U;
    __Vtemp_51[1U] = 0U;
    __Vtemp_51[2U] = 0U;
    __Vtemp_51[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_52, __Vtemp_51, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_68 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_270) 
                     - ((__Vtemp_52[2U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_53[0U] = 1U;
    __Vtemp_53[1U] = 0U;
    __Vtemp_53[2U] = 0U;
    __Vtemp_53[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_54, __Vtemp_53, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_108 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_430) 
                     - ((__Vtemp_54[3U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_55[0U] = 1U;
    __Vtemp_55[1U] = 0U;
    __Vtemp_55[2U] = 0U;
    __Vtemp_55[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_56, __Vtemp_55, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_109 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_434) 
                     - ((__Vtemp_56[3U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_57[0U] = 1U;
    __Vtemp_57[1U] = 0U;
    __Vtemp_57[2U] = 0U;
    __Vtemp_57[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_58, __Vtemp_57, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_110 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_438) 
                     - ((__Vtemp_58[3U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_59[0U] = 1U;
    __Vtemp_59[1U] = 0U;
    __Vtemp_59[2U] = 0U;
    __Vtemp_59[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_60, __Vtemp_59, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_111 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_442) 
                     - ((__Vtemp_60[3U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_61[0U] = 1U;
    __Vtemp_61[1U] = 0U;
    __Vtemp_61[2U] = 0U;
    __Vtemp_61[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_62, __Vtemp_61, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_112 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_446) 
                     - ((__Vtemp_62[3U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_63[0U] = 1U;
    __Vtemp_63[1U] = 0U;
    __Vtemp_63[2U] = 0U;
    __Vtemp_63[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_64, __Vtemp_63, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_52 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_206) 
                     - ((__Vtemp_64[1U] >> 0x13U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_65[0U] = 1U;
    __Vtemp_65[1U] = 0U;
    __Vtemp_65[2U] = 0U;
    __Vtemp_65[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_66, __Vtemp_65, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_128 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_510) 
                     - ((__Vtemp_66[3U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_67[0U] = 1U;
    __Vtemp_67[1U] = 0U;
    __Vtemp_67[2U] = 0U;
    __Vtemp_67[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_68, __Vtemp_67, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_125 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_498) 
                     - ((__Vtemp_68[3U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_69[0U] = 1U;
    __Vtemp_69[1U] = 0U;
    __Vtemp_69[2U] = 0U;
    __Vtemp_69[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_70, __Vtemp_69, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_124 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_494) 
                     - ((__Vtemp_70[3U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_71[0U] = 1U;
    __Vtemp_71[1U] = 0U;
    __Vtemp_71[2U] = 0U;
    __Vtemp_71[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_72, __Vtemp_71, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_98 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_390) 
                     - ((__Vtemp_72[3U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_73[0U] = 1U;
    __Vtemp_73[1U] = 0U;
    __Vtemp_73[2U] = 0U;
    __Vtemp_73[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_74, __Vtemp_73, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_97 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_386) 
                     - (__Vtemp_74[3U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_75[0U] = 1U;
    __Vtemp_75[1U] = 0U;
    __Vtemp_75[2U] = 0U;
    __Vtemp_75[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_76, __Vtemp_75, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_96 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_382) 
                     - ((__Vtemp_76[2U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_77[0U] = 1U;
    __Vtemp_77[1U] = 0U;
    __Vtemp_77[2U] = 0U;
    __Vtemp_77[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_78, __Vtemp_77, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_95 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_378) 
                     - ((__Vtemp_78[2U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_79[0U] = 1U;
    __Vtemp_79[1U] = 0U;
    __Vtemp_79[2U] = 0U;
    __Vtemp_79[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_80, __Vtemp_79, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_94 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_374) 
                     - ((__Vtemp_80[2U] >> 0x1dU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_81[0U] = 1U;
    __Vtemp_81[1U] = 0U;
    __Vtemp_81[2U] = 0U;
    __Vtemp_81[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_82, __Vtemp_81, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_89 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_354) 
                     - ((__Vtemp_82[2U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_83[0U] = 1U;
    __Vtemp_83[1U] = 0U;
    __Vtemp_83[2U] = 0U;
    __Vtemp_83[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_84, __Vtemp_83, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_88 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_350) 
                     - ((__Vtemp_84[2U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_85[0U] = 1U;
    __Vtemp_85[1U] = 0U;
    __Vtemp_85[2U] = 0U;
    __Vtemp_85[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_86, __Vtemp_85, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_83 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_330) 
                     - ((__Vtemp_86[2U] >> 0x12U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_87[0U] = 1U;
    __Vtemp_87[1U] = 0U;
    __Vtemp_87[2U] = 0U;
    __Vtemp_87[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_88, __Vtemp_87, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_82 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_326) 
                     - ((__Vtemp_88[2U] >> 0x11U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_89[0U] = 1U;
    __Vtemp_89[1U] = 0U;
    __Vtemp_89[2U] = 0U;
    __Vtemp_89[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_90, __Vtemp_89, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_72 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_286) 
                     - ((__Vtemp_90[2U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_91[0U] = 1U;
    __Vtemp_91[1U] = 0U;
    __Vtemp_91[2U] = 0U;
    __Vtemp_91[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_92, __Vtemp_91, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_71 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_282) 
                     - ((__Vtemp_92[2U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_93[0U] = 1U;
    __Vtemp_93[1U] = 0U;
    __Vtemp_93[2U] = 0U;
    __Vtemp_93[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_94, __Vtemp_93, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_70 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_278) 
                     - ((__Vtemp_94[2U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_1 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_2) 
                     - (VL_SHIFTL_III(1,1,7, (IData)(1U), (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_addr__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_addr__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28[__VdlyDim0__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp[__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1 
        = __Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1;
    vlSelfRef.io_success = (1U == vlSelfRef.TestHarness__DOT__SimDTM__DOT__exit_reg);
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter1_3 
        = (1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter_3)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT___GEN_0));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__1(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__1\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
    __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value = 0;
    CData/*2:0*/ __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos;
    __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos = 0;
    CData/*3:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 0;
    CData/*0:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 0;
    CData/*3:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 0;
    CData/*3:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*4:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 0;
    CData/*2:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0 = 0;
    IData/*30:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0 = 0;
    CData/*3:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 = 0;
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0 = 0;
    CData/*1:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0;
    CData/*7:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0 = 0;
    CData/*1:0*/ __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0;
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
    // Body
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0 = 0U;
    __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_source__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_wen__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1;
    __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_burst__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_len__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_last__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1;
    __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_last__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 = 0U;
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en) {
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_size;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_address;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0 
            = (0xffU & (~ (0xffU & (((IData)(0x7ffU) 
                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size)) 
                                    >> 3U))));
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_wen__v0 
            = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                        >> 2U)));
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_wen__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_en) 
         & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
            >> 5U))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data
                                [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
                                >> 0x28U)));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_5__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_en) 
         & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
            >> 4U))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data
                                [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
                                >> 0x20U)));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_4__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_en) 
         & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
            >> 1U))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data
                                [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
                                >> 8U)));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_1__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_en) 
         & (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
            >> 7U))) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0 
            = (0xffU & (IData)((vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data
                                [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1] 
                                >> 0x38U)));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_0_MPORT_addr;
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__srams__DOT__mem_7__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_id__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_burst
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_len
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1];
        vlSelfRef.__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_burst
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 1U;
        __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_len
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1];
        __VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0 = 1U;
    }
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_latched 
        = ((1U & (~ (IData)(vlSelfRef.reset))) && (
                                                   (1U 
                                                    & (~ 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
                                                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_aw_valid)))) 
                                                   && (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_valid) 
                                                        & (0U 
                                                           == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter))) 
                                                       | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_latched))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_addr;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_addr__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_len;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_len__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_len__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_burst__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full) {
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data
                [0U];
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_strb
                [0U];
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_last__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_last
                [0U];
        } else {
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_data;
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_mask;
            vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_last__v0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_bits_last;
        }
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_strb__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_param;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_source;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_sink;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_denied;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_corrupt)) 
               | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_corrupt)) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_corrupt))));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error_auto_in_d_bits_opcode;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_size
            [0U];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_source
            [0U];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_source__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_sink__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_denied__v0 = 1U;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__monitor__DOT__d_first_beats1_opdata;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_corrupt__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_resp;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_resp;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_resp;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_id;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_data;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_resp;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_in_r_bits_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1];
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_data__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp
            [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1];
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 
            = (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_echo_real_last
               [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1] 
               & vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last
               [vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1]);
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_last__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_extra_id__v0 = 1U;
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_aw_ready) 
         & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_valid))) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__r_addr_1 
            = (0x7fffffffU & ((0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_burst))
                               ? vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_addr
                               : ((2U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_burst))
                                   ? ((~ ((~ vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_addr) 
                                          | vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_58)) 
                                      | (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__inc_addr_1 
                                         & vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___GEN_58))
                                   : vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__inc_addr_1)));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_valid) {
        if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_cfiType))) {
            if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_2 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
            if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_0 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
            if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_5 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
            if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_1 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
            if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_3 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
            if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__nextPos))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_4 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_returnAddr;
            }
        }
    }
    __Vtemp_2[0U] = 1U;
    __Vtemp_2[1U] = 0U;
    __Vtemp_2[2U] = 0U;
    __Vtemp_2[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_3, __Vtemp_2, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_10 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_38) 
                     - ((__Vtemp_3[0U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_4[0U] = 1U;
    __Vtemp_4[1U] = 0U;
    __Vtemp_4[2U] = 0U;
    __Vtemp_4[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_5, __Vtemp_4, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_11 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_42) 
                     - ((__Vtemp_5[0U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_6[0U] = 1U;
    __Vtemp_6[1U] = 0U;
    __Vtemp_6[2U] = 0U;
    __Vtemp_6[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_7, __Vtemp_6, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_12 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_46) 
                     - ((__Vtemp_7[0U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_8[0U] = 1U;
    __Vtemp_8[1U] = 0U;
    __Vtemp_8[2U] = 0U;
    __Vtemp_8[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_9, __Vtemp_8, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_13 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_50) 
                     - ((__Vtemp_9[0U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_10[0U] = 1U;
    if (vlSelfRef.reset) {
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__busy_1 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_13 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_11 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_10 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_9 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_8 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_7 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_6 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_5 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_3 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_1 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_4 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_0 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_2 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_15 = 0U;
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__in_aw_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1_io_deq_valid))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__busy_1 
                = (0U != (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__len_1));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xdU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_13 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_13_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xbU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_11 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_11_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xaU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_10 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_10_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 9U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_9 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_9_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 8U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_8 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_8_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 7U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_7 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_7_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 6U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_6 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_6_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 5U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_5 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_5_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 3U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_3 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_3_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 1U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_1 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_1_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 4U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_4 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_4_T));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
             & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_0 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_0_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 2U) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_2 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_2_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___T_22) 
              >> 0xfU) & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__error_15 
                = ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT___error_15_T));
        }
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter 
            = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_todo) 
                         - (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en)));
    }
    __Vtemp_10[1U] = 0U;
    __Vtemp_10[2U] = 0U;
    __Vtemp_10[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_11, __Vtemp_10, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_14 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_54) 
                     - ((__Vtemp_11[0U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 = 0U;
        __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 = 0U;
        __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__counter = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last_counter = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_1 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_1 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_4 = 7U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_3 = 7U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_2 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_2 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__enq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__enq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__maybe_full = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3 = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full = 0U;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_valid) {
            if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_cfiType))) {
                __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos 
                    = ((5U > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___nextPos_T_3)
                        : 0U);
            } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_update_bits_cfiType))) {
                __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT___GEN_411;
            }
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__monitor__DOT__b_first_done) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__coupler_from_port_named_slave_port_axi4__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) {
            __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error_auto_in_d_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__counter 
                = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__da_first)
                              ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__monitor__DOT__d_first_beats1_opdata)
                                  ? (~ (0x1ffU & (((IData)(0xfffU) 
                                                   << 
                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_size
                                                   [0U]) 
                                                  >> 3U)))
                                  : 0U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__counter1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_opcode_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_opcode_MPORT_en;
        }
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_8;
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter 
                = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_first)
                              ? ((1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode))
                                  ? (~ (0x1ffU & (((IData)(0xfffU) 
                                                   << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_size)) 
                                                  >> 3U)))
                                  : 0U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_id_MPORT_en;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_io_deq_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__maybe_full))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last_counter 
                = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last_first)
                              ? ((4U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_opcode
                                  [0U]) ? 0U : (~ (0x1ffU 
                                                   & (((IData)(0xfffU) 
                                                       << 
                                                       vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_size
                                                       [0U]) 
                                                      >> 3U))))
                              : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a_last_counter1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full 
                = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_ready)
                    ? ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready))) 
                       && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_ready) 
                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid)))
                    : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_ready) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter 
                = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__a_first)
                             ? ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode))
                                 ? 0U : (~ (0x1fU & 
                                            (((IData)(0xffU) 
                                              << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size)) 
                                             >> 3U))))
                             : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter1)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en;
        }
        if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_1 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_2 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_2;
        }
        if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_1 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_2 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_2;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_4) 
             & (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_4)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_4 
                = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_26) 
                         | VL_SHIFTL_III(3,3,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_26), 2U)));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_3) 
             & (0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_3)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_3 
                = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_18) 
                         | VL_SHIFTL_III(3,3,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_18), 2U)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__enq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT___value_T_1;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__enq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT___value_T_1;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full 
                = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_ready)
                    ? ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20) 
                       && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_ready) 
                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid)))
                    : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_ready) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid)));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__enq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT___value_T_1;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__enq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT___value_T_1;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_opcode_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__error__DOT__a__DOT__ram_opcode_MPORT_en;
        }
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_4)
                ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_0)
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_0)
                     : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_1)
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_1)
                                : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_2)
                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_2)
                                          : 0U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_28));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_3)
                ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_0)
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_0)
                     : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_1)
                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_1)
                                : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_2)
                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsDO_2)
                                          : 0U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_22));
    }
    __Vtemp_12[0U] = 1U;
    __Vtemp_12[1U] = 0U;
    __Vtemp_12[2U] = 0U;
    __Vtemp_12[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_13, __Vtemp_12, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_15 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_58) 
                     - ((__Vtemp_13[0U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_14[0U] = 1U;
    __Vtemp_14[1U] = 0U;
    __Vtemp_14[2U] = 0U;
    __Vtemp_14[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_15, __Vtemp_14, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_16 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_62) 
                     - ((__Vtemp_15[0U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_16[0U] = 1U;
    __Vtemp_16[1U] = 0U;
    __Vtemp_16[2U] = 0U;
    __Vtemp_16[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_17, __Vtemp_16, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_17 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_66) 
                     - ((__Vtemp_17[0U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_18[0U] = 1U;
    __Vtemp_18[1U] = 0U;
    __Vtemp_18[2U] = 0U;
    __Vtemp_18[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_19, __Vtemp_18, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_22 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_86) 
                     - ((__Vtemp_19[0U] >> 0x15U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_20[0U] = 1U;
    __Vtemp_20[1U] = 0U;
    __Vtemp_20[2U] = 0U;
    __Vtemp_20[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_21, __Vtemp_20, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_23 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_90) 
                     - ((__Vtemp_21[0U] >> 0x16U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_22[0U] = 1U;
    __Vtemp_22[1U] = 0U;
    __Vtemp_22[2U] = 0U;
    __Vtemp_22[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_23, __Vtemp_22, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_24 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_94) 
                     - ((__Vtemp_23[0U] >> 0x17U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_24[0U] = 1U;
    __Vtemp_24[1U] = 0U;
    __Vtemp_24[2U] = 0U;
    __Vtemp_24[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_25, __Vtemp_24, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_25 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_98) 
                     - ((__Vtemp_25[0U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_26[0U] = 1U;
    __Vtemp_26[1U] = 0U;
    __Vtemp_26[2U] = 0U;
    __Vtemp_26[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_27, __Vtemp_26, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_26 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_102) 
                     - ((__Vtemp_27[0U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_28[0U] = 1U;
    __Vtemp_28[1U] = 0U;
    __Vtemp_28[2U] = 0U;
    __Vtemp_28[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_29, __Vtemp_28, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_27 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_106) 
                     - ((__Vtemp_29[0U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_30[0U] = 1U;
    __Vtemp_30[1U] = 0U;
    __Vtemp_30[2U] = 0U;
    __Vtemp_30[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_31, __Vtemp_30, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_28 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_110) 
                     - ((__Vtemp_31[0U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_32[0U] = 1U;
    __Vtemp_32[1U] = 0U;
    __Vtemp_32[2U] = 0U;
    __Vtemp_32[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_33, __Vtemp_32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_29 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_114) 
                     - ((__Vtemp_33[0U] >> 0x1cU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_34[0U] = 1U;
    __Vtemp_34[1U] = 0U;
    __Vtemp_34[2U] = 0U;
    __Vtemp_34[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_35, __Vtemp_34, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_34 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_134) 
                     - ((__Vtemp_35[1U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_36[0U] = 1U;
    __Vtemp_36[1U] = 0U;
    __Vtemp_36[2U] = 0U;
    __Vtemp_36[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_37, __Vtemp_36, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_35 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_138) 
                     - ((__Vtemp_37[1U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_38[0U] = 1U;
    __Vtemp_38[1U] = 0U;
    __Vtemp_38[2U] = 0U;
    __Vtemp_38[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_39, __Vtemp_38, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_36 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_142) 
                     - ((__Vtemp_39[1U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_40[0U] = 1U;
    __Vtemp_40[1U] = 0U;
    __Vtemp_40[2U] = 0U;
    __Vtemp_40[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_41, __Vtemp_40, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_37 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_146) 
                     - ((__Vtemp_41[1U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_42[0U] = 1U;
    __Vtemp_42[1U] = 0U;
    __Vtemp_42[2U] = 0U;
    __Vtemp_42[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_43, __Vtemp_42, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_38 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_150) 
                     - ((__Vtemp_43[1U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_44[0U] = 1U;
    __Vtemp_44[1U] = 0U;
    __Vtemp_44[2U] = 0U;
    __Vtemp_44[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_45, __Vtemp_44, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_39 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_154) 
                     - ((__Vtemp_45[1U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_46[0U] = 1U;
    __Vtemp_46[1U] = 0U;
    __Vtemp_46[2U] = 0U;
    __Vtemp_46[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_47, __Vtemp_46, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_40 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_158) 
                     - ((__Vtemp_47[1U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_48[0U] = 1U;
    __Vtemp_48[1U] = 0U;
    __Vtemp_48[2U] = 0U;
    __Vtemp_48[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_49, __Vtemp_48, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_41 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_162) 
                     - ((__Vtemp_49[1U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_50[0U] = 1U;
    __Vtemp_50[1U] = 0U;
    __Vtemp_50[2U] = 0U;
    __Vtemp_50[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_51, __Vtemp_50, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_42 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_166) 
                     - ((__Vtemp_51[1U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_52[0U] = 1U;
    __Vtemp_52[1U] = 0U;
    __Vtemp_52[2U] = 0U;
    __Vtemp_52[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_53, __Vtemp_52, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_43 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_170) 
                     - ((__Vtemp_53[1U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_54[0U] = 1U;
    __Vtemp_54[1U] = 0U;
    __Vtemp_54[2U] = 0U;
    __Vtemp_54[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_55, __Vtemp_54, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_44 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_174) 
                     - ((__Vtemp_55[1U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_56[0U] = 1U;
    __Vtemp_56[1U] = 0U;
    __Vtemp_56[2U] = 0U;
    __Vtemp_56[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_57, __Vtemp_56, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_45 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_178) 
                     - ((__Vtemp_57[1U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_58[0U] = 1U;
    __Vtemp_58[1U] = 0U;
    __Vtemp_58[2U] = 0U;
    __Vtemp_58[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_59, __Vtemp_58, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_46 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_182) 
                     - ((__Vtemp_59[1U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_60[0U] = 1U;
    __Vtemp_60[1U] = 0U;
    __Vtemp_60[2U] = 0U;
    __Vtemp_60[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_61, __Vtemp_60, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_47 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_186) 
                     - ((__Vtemp_61[1U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_62[0U] = 1U;
    __Vtemp_62[1U] = 0U;
    __Vtemp_62[2U] = 0U;
    __Vtemp_62[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_63, __Vtemp_62, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_48 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_190) 
                     - ((__Vtemp_63[1U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_64[0U] = 1U;
    __Vtemp_64[1U] = 0U;
    __Vtemp_64[2U] = 0U;
    __Vtemp_64[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_65, __Vtemp_64, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_49 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_194) 
                     - ((__Vtemp_65[1U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_66[0U] = 1U;
    __Vtemp_66[1U] = 0U;
    __Vtemp_66[2U] = 0U;
    __Vtemp_66[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_67, __Vtemp_66, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_57 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_226) 
                     - ((__Vtemp_67[1U] >> 0x18U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_68[0U] = 1U;
    __Vtemp_68[1U] = 0U;
    __Vtemp_68[2U] = 0U;
    __Vtemp_68[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_69, __Vtemp_68, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_58 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_230) 
                     - ((__Vtemp_69[1U] >> 0x19U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_70[0U] = 1U;
    __Vtemp_70[1U] = 0U;
    __Vtemp_70[2U] = 0U;
    __Vtemp_70[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_71, __Vtemp_70, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_59 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_234) 
                     - ((__Vtemp_71[1U] >> 0x1aU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_72[0U] = 1U;
    __Vtemp_72[1U] = 0U;
    __Vtemp_72[2U] = 0U;
    __Vtemp_72[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_73, __Vtemp_72, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_60 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_238) 
                     - ((__Vtemp_73[1U] >> 0x1bU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_74[0U] = 1U;
    __Vtemp_74[1U] = 0U;
    __Vtemp_74[2U] = 0U;
    __Vtemp_74[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_75, __Vtemp_74, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_63 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_250) 
                     - ((__Vtemp_75[1U] >> 0x1eU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_76[0U] = 1U;
    __Vtemp_76[1U] = 0U;
    __Vtemp_76[2U] = 0U;
    __Vtemp_76[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_77, __Vtemp_76, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_64 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_254) 
                     - ((__Vtemp_77[1U] >> 0x1fU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_78[0U] = 1U;
    __Vtemp_78[1U] = 0U;
    __Vtemp_78[2U] = 0U;
    __Vtemp_78[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_79, __Vtemp_78, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_65 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_258) 
                     - (__Vtemp_79[2U] & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_80[0U] = 1U;
    __Vtemp_80[1U] = 0U;
    __Vtemp_80[2U] = 0U;
    __Vtemp_80[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_81, __Vtemp_80, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_66 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_262) 
                     - ((__Vtemp_81[2U] >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_82[0U] = 1U;
    __Vtemp_82[1U] = 0U;
    __Vtemp_82[2U] = 0U;
    __Vtemp_82[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_83, __Vtemp_82, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_69 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_274) 
                     - ((__Vtemp_83[2U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_84[0U] = 1U;
    __Vtemp_84[1U] = 0U;
    __Vtemp_84[2U] = 0U;
    __Vtemp_84[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_85, __Vtemp_84, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_100 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_398) 
                     - ((__Vtemp_85[3U] >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_86[0U] = 1U;
    __Vtemp_86[1U] = 0U;
    __Vtemp_86[2U] = 0U;
    __Vtemp_86[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_87, __Vtemp_86, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_101 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_402) 
                     - ((__Vtemp_87[3U] >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_88[0U] = 1U;
    __Vtemp_88[1U] = 0U;
    __Vtemp_88[2U] = 0U;
    __Vtemp_88[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_89, __Vtemp_88, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_102 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_406) 
                     - ((__Vtemp_89[3U] >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_90[0U] = 1U;
    __Vtemp_90[1U] = 0U;
    __Vtemp_90[2U] = 0U;
    __Vtemp_90[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_91, __Vtemp_90, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_103 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_410) 
                     - ((__Vtemp_91[3U] >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_92[0U] = 1U;
    __Vtemp_92[1U] = 0U;
    __Vtemp_92[2U] = 0U;
    __Vtemp_92[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_93, __Vtemp_92, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_104 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_414) 
                     - ((__Vtemp_93[3U] >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_94[0U] = 1U;
    __Vtemp_94[1U] = 0U;
    __Vtemp_94[2U] = 0U;
    __Vtemp_94[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_95, __Vtemp_94, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_106 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_422) 
                     - ((__Vtemp_95[3U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_96[0U] = 1U;
    __Vtemp_96[1U] = 0U;
    __Vtemp_96[2U] = 0U;
    __Vtemp_96[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_97, __Vtemp_96, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_107 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_426) 
                     - ((__Vtemp_97[3U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_98[0U] = 1U;
    __Vtemp_98[1U] = 0U;
    __Vtemp_98[2U] = 0U;
    __Vtemp_98[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_99, __Vtemp_98, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_113 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_450) 
                     - ((__Vtemp_99[3U] >> 0x10U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_100[0U] = 1U;
    __Vtemp_100[1U] = 0U;
    __Vtemp_100[2U] = 0U;
    __Vtemp_100[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_101, __Vtemp_100, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_114 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_454) 
                     - ((__Vtemp_101[3U] >> 0x11U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_102[0U] = 1U;
    __Vtemp_102[1U] = 0U;
    __Vtemp_102[2U] = 0U;
    __Vtemp_102[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_103, __Vtemp_102, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_115 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_458) 
                     - ((__Vtemp_103[3U] >> 0x12U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_104[0U] = 1U;
    __Vtemp_104[1U] = 0U;
    __Vtemp_104[2U] = 0U;
    __Vtemp_104[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_105, __Vtemp_104, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_105 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_418) 
                     - ((__Vtemp_105[3U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_106[0U] = 1U;
    __Vtemp_106[1U] = 0U;
    __Vtemp_106[2U] = 0U;
    __Vtemp_106[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_107, __Vtemp_106, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_81 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_322) 
                     - ((__Vtemp_107[2U] >> 0x10U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_108[0U] = 1U;
    __Vtemp_108[1U] = 0U;
    __Vtemp_108[2U] = 0U;
    __Vtemp_108[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_109, __Vtemp_108, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_123 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_490) 
                     - ((__Vtemp_109[3U] >> 0x1aU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_110[0U] = 1U;
    __Vtemp_110[1U] = 0U;
    __Vtemp_110[2U] = 0U;
    __Vtemp_110[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_111, __Vtemp_110, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_127 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_506) 
                     - ((__Vtemp_111[3U] >> 0x1eU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_112[0U] = 1U;
    __Vtemp_112[1U] = 0U;
    __Vtemp_112[2U] = 0U;
    __Vtemp_112[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_113, __Vtemp_112, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_126 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_502) 
                     - ((__Vtemp_113[3U] >> 0x1dU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_114[0U] = 1U;
    __Vtemp_114[1U] = 0U;
    __Vtemp_114[2U] = 0U;
    __Vtemp_114[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_115, __Vtemp_114, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_122 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_486) 
                     - ((__Vtemp_115[3U] >> 0x19U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_116[0U] = 1U;
    __Vtemp_116[1U] = 0U;
    __Vtemp_116[2U] = 0U;
    __Vtemp_116[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_117, __Vtemp_116, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_121 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_482) 
                     - ((__Vtemp_117[3U] >> 0x18U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_118[0U] = 1U;
    __Vtemp_118[1U] = 0U;
    __Vtemp_118[2U] = 0U;
    __Vtemp_118[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_119, __Vtemp_118, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_120 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_478) 
                     - ((__Vtemp_119[3U] >> 0x17U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_120[0U] = 1U;
    __Vtemp_120[1U] = 0U;
    __Vtemp_120[2U] = 0U;
    __Vtemp_120[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_121, __Vtemp_120, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_119 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_474) 
                     - ((__Vtemp_121[3U] >> 0x16U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_122[0U] = 1U;
    __Vtemp_122[1U] = 0U;
    __Vtemp_122[2U] = 0U;
    __Vtemp_122[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_123, __Vtemp_122, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_118 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_470) 
                     - ((__Vtemp_123[3U] >> 0x15U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_124[0U] = 1U;
    __Vtemp_124[1U] = 0U;
    __Vtemp_124[2U] = 0U;
    __Vtemp_124[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_125, __Vtemp_124, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_117 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_466) 
                     - ((__Vtemp_125[3U] >> 0x14U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_126[0U] = 1U;
    __Vtemp_126[1U] = 0U;
    __Vtemp_126[2U] = 0U;
    __Vtemp_126[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_127, __Vtemp_126, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_116 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_462) 
                     - ((__Vtemp_127[3U] >> 0x13U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_128[0U] = 1U;
    __Vtemp_128[1U] = 0U;
    __Vtemp_128[2U] = 0U;
    __Vtemp_128[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_129, __Vtemp_128, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_99 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_394) 
                     - ((__Vtemp_129[3U] >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_130[0U] = 1U;
    __Vtemp_130[1U] = 0U;
    __Vtemp_130[2U] = 0U;
    __Vtemp_130[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_131, __Vtemp_130, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_93 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_370) 
                     - ((__Vtemp_131[2U] >> 0x1cU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_132[0U] = 1U;
    __Vtemp_132[1U] = 0U;
    __Vtemp_132[2U] = 0U;
    __Vtemp_132[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_133, __Vtemp_132, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_92 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_366) 
                     - ((__Vtemp_133[2U] >> 0x1bU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_134[0U] = 1U;
    __Vtemp_134[1U] = 0U;
    __Vtemp_134[2U] = 0U;
    __Vtemp_134[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_135, __Vtemp_134, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_91 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_362) 
                     - ((__Vtemp_135[2U] >> 0x1aU) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_136[0U] = 1U;
    __Vtemp_136[1U] = 0U;
    __Vtemp_136[2U] = 0U;
    __Vtemp_136[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_137, __Vtemp_136, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_90 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_358) 
                     - ((__Vtemp_137[2U] >> 0x19U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_138[0U] = 1U;
    __Vtemp_138[1U] = 0U;
    __Vtemp_138[2U] = 0U;
    __Vtemp_138[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_139, __Vtemp_138, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_87 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_346) 
                     - ((__Vtemp_139[2U] >> 0x16U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_140[0U] = 1U;
    __Vtemp_140[1U] = 0U;
    __Vtemp_140[2U] = 0U;
    __Vtemp_140[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_141, __Vtemp_140, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_86 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_342) 
                     - ((__Vtemp_141[2U] >> 0x15U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_142[0U] = 1U;
    __Vtemp_142[1U] = 0U;
    __Vtemp_142[2U] = 0U;
    __Vtemp_142[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_143, __Vtemp_142, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_85 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_338) 
                     - ((__Vtemp_143[2U] >> 0x14U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_144[0U] = 1U;
    __Vtemp_144[1U] = 0U;
    __Vtemp_144[2U] = 0U;
    __Vtemp_144[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_145, __Vtemp_144, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_84 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_334) 
                     - ((__Vtemp_145[2U] >> 0x13U) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_146[0U] = 1U;
    __Vtemp_146[1U] = 0U;
    __Vtemp_146[2U] = 0U;
    __Vtemp_146[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_147, __Vtemp_146, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_80 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_318) 
                     - ((__Vtemp_147[2U] >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_148[0U] = 1U;
    __Vtemp_148[1U] = 0U;
    __Vtemp_148[2U] = 0U;
    __Vtemp_148[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_149, __Vtemp_148, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_79 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_314) 
                     - ((__Vtemp_149[2U] >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_150[0U] = 1U;
    __Vtemp_150[1U] = 0U;
    __Vtemp_150[2U] = 0U;
    __Vtemp_150[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_151, __Vtemp_150, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_78 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_310) 
                     - ((__Vtemp_151[2U] >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_152[0U] = 1U;
    __Vtemp_152[1U] = 0U;
    __Vtemp_152[2U] = 0U;
    __Vtemp_152[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_153, __Vtemp_152, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_77 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_306) 
                     - ((__Vtemp_153[2U] >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_154[0U] = 1U;
    __Vtemp_154[1U] = 0U;
    __Vtemp_154[2U] = 0U;
    __Vtemp_154[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_155, __Vtemp_154, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_76 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_302) 
                     - ((__Vtemp_155[2U] >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_156[0U] = 1U;
    __Vtemp_156[1U] = 0U;
    __Vtemp_156[2U] = 0U;
    __Vtemp_156[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_157, __Vtemp_156, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_75 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_298) 
                     - ((__Vtemp_157[2U] >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_158[0U] = 1U;
    __Vtemp_158[1U] = 0U;
    __Vtemp_158[2U] = 0U;
    __Vtemp_158[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_159, __Vtemp_158, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_74 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_294) 
                     - ((__Vtemp_159[2U] >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    __Vtemp_160[0U] = 1U;
    __Vtemp_160[1U] = 0U;
    __Vtemp_160[2U] = 0U;
    __Vtemp_160[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_161, __Vtemp_160, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_73 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_290) 
                     - ((__Vtemp_161[2U] >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1)))));
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst[0U] = 1U;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq__DOT__ram_len__v0;
    }
    if (__VdlySet__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0) {
        vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len[0U] 
            = __VdlyVal__TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__deq_1__DOT__ram_len__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos 
        = __Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos;
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value 
        = __Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value;
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ram_echo_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ram_echo_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ram_echo_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ram_echo_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_source__v0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_ras_head_bits 
        = ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_5
            : ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_4
                : ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_3
                    : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_2
                        : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__pos))
                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_1
                            : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb__DOT__stack_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_first 
        = (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter1 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter) 
                     - (IData)(1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__a_first 
        = (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter1 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter) 
                    - (IData)(1U)));
    vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT____VdfgRegularize_h65569c2e_5_0 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__w_counter)) 
           | (IData)(vlSelfRef.TestHarness__DOT__mmio_mem__DOT__axi4frag__DOT__wbeats_latched));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__2(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__2\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*6:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 = 0;
    CData/*2:0*/ __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0;
    __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 0;
    CData/*2:0*/ __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0;
    CData/*3:0*/ __VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0;
    __VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 0;
    CData/*0:0*/ __VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0;
    __VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 0;
    CData/*1:0*/ __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0;
    CData/*1:0*/ __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0;
    CData/*0:0*/ __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0;
    // Body
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 0U;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 0U;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l;
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_extra_id__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size__v0 = 0U;
    __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 0U;
    vlSelfRef.__VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 = 0U;
    vlSelfRef.__Vdly__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value 
        = vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
    __VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 0U;
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en) {
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_size;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst;
        __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_burst;
        __VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0 = 1U;
    }
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && ((1U & (~ (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full)) 
                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_deq_valid)) 
                         & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_repeat))))) 
               && ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_enq_ready) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_a_valid)) 
                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_repeat)) 
                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater__DOT__full))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__io_status_cease_r 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && ((IData)(((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_cmd)) 
                        & (0x20000000U == (0x20200000U 
                                           & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst)))) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__io_status_cease_r)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size_MPORT_en) {
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size__v0 = 1U;
        __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source;
        __VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__enq_ptr_value;
        __VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_extra_id__v0 
            = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id) 
                     >> 4U));
        vlSelfRef.__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_extra_id__v0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__enq_ptr_value;
        vlSelfRef.__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_extra_id__v0 = 1U;
    }
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) {
        __VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mem__DOT__srams__DOT__w_id;
        __VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 
            = vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        __VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 
            = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__srams__DOT__w_sel1)
                ? 0U : 3U);
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 
            = vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_resp__v0 = 1U;
        vlSelfRef.__VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mem__DOT__srams__DOT__w_echo_real_last;
        vlSelfRef.__VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 
            = vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value;
        vlSelfRef.__VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last__v0 = 1U;
    }
    if (vlSelfRef.reset) {
        vlSelfRef.__Vdly__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_13 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_11 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_10 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_9 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_4 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_0 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_2 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_15 = 0U;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__maybe_full = 0U;
    } else {
        if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) {
            vlSelfRef.__Vdly__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value 
                = (1U & ((IData)(1U) + (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value)));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 0xdU) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_13 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_13_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 0xbU) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_11 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_11_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 0xaU) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_10 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_10_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 9U) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_9 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_9_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 4U) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_4 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_4_T));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
             & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_0 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_0_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 2U) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_2 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_2_T));
        }
        if ((((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
              >> 0xfU) & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready) 
                          & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid)))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__error_15 
                = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf_auto_in_b_bits_echo_real_last)
                    ? 0U : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___error_15_T));
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en) 
             != (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq))) {
            vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__maybe_full 
                = vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id_MPORT_en;
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__fanin_1__DOT____VdfgRegularize_he8d05a2b_0_0)
            ? (4U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__fanin_1__DOT__effectivePriority_1))
            : 2U);
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__fanin__DOT____VdfgRegularize_he8d05a2b_0_0)
            ? (4U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__fanin__DOT__effectivePriority_1))
            : 2U);
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_out_d_ready) 
         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full))) {
        if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__acknum))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dOrig 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dFirst_size;
        }
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
        if ((0x140U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_sscratch 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata;
        }
        if ((0x180U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            if (((0U == (0xfU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                         >> 0x3cU)))) 
                 | (8U == (0xfU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                           >> 0x3cU)))))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_satp_ppn 
                    = (QData)((IData)((0xfffffU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata))));
            }
        }
        if ((0x344U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_seip 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_mip_T_8 
                                 >> 9U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_stip 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_mip_T_8 
                                 >> 5U)));
        }
        if ((0x104U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_mie_T_4;
        } else if ((0x304U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                               >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mie 
                = (0xaaaULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata);
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 2U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_w 
                = (IData)((3ULL == (3ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_r 
                = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x32U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_w 
                = (IData)((0x3000000000000ULL == (0x3000000000000ULL 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x30U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0xaU)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_w 
                = (IData)((0x300ULL == (0x300ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 8U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x12U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_w 
                = (IData)((0x30000ULL == (0x30000ULL 
                                          & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x10U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x2aU)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_w 
                = (IData)((0x30000000000ULL == (0x30000000000ULL 
                                                & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x28U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x1aU)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_w 
                = (IData)((0x3000000ULL == (0x3000000ULL 
                                            & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x18U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x22U)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_w 
                = (IData)((0x300000000ULL == (0x300000000ULL 
                                              & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x20U)));
        }
        if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                         >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_x 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x3aU)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_w 
                = (IData)((0x300000000000000ULL == 
                           (0x300000000000000ULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_r 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                 >> 0x38U)));
        }
        if ((0x144U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_ssip 
                = (1U & (((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg 
                                      >> 1U))) & (IData)(
                                                         ((QData)((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_200)) 
                                                          >> 1U))) 
                         | (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_sip_T_2 
                                    >> 1U))));
        } else if ((0x344U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                               >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mip_ssip 
                = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___new_mip_T_8 
                                 >> 1U)));
        }
        if ((0x303U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 0x14U))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mideleg 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata;
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mpie 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen)
                      ? ((0x300U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                     >> 0x14U)) ? (IData)(
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                                           >> 7U))
                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_177))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_177))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_lo 
        = (0x3fU & (IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset)
                             ? 0ULL : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen)
                                        ? ((0xb02U 
                                            == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                >> 0x14U))
                                            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata
                                            : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_58)
                                        : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_58))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mie 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen)
                      ? ((0x300U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                     >> 0x14U)) ? (IData)(
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                                           >> 3U))
                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_176))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_176))));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__gennum))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__aToggle_r 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dToggle;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_4 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_3 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcause = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi_1 = 0ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tw = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tsr = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_prv = 3U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_custom_0 = 0x208ULL;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__deq_ptr_value = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__deq_ptr_value = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_a = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_a = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__gennum = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dToggle = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__acknum = 0U;
    } else {
        if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_4 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_4;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_3 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_3;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen) 
             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_set_sboard) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_wen)))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r 
                = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___T_132 
                   | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_set_sboard) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_wen))
                       ? ((IData)(1U) << (0x1fU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                   >> 7U)))
                       : 0U));
        } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___T_132;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcause 
                = ((0x342U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                               >> 0x14U)) ? (0x800000000000000fULL 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_137);
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi 
                = (0x3ffffffffffffffULL & ((0xb02U 
                                            == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                >> 0x14U))
                                            ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                               >> 6U)
                                            : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_1));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi_1 
                = (0x3ffffffffffffffULL & ((0xb00U 
                                            == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                                >> 0x14U))
                                            ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                               >> 6U)
                                            : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_3));
            if ((0x300U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tw 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x15U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tsr 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x16U)));
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_prv 
                = (3U & ((0x7b0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                     >> 0x14U)) ? (
                                                   (2U 
                                                    == 
                                                    (3U 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata)))
                                                    ? 0U
                                                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata))
                          : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_122)));
            if ((0x7c1U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_custom_0 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_custom_0_T_3;
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 7U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_0_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 3U)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x37U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_6_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x33U)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0xfU)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_1_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0xbU)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x17U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_2_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x13U)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x2fU)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_5_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x2bU)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x1fU)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_3_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x1bU)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x27U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_4_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x23U)));
            }
            if (((0x3a0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                             >> 0x14U)) & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l)))) {
                vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_l 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x3fU)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_pmp_7_cfg_a 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x3bU)));
            }
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcause 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_137;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi 
                = (0x3ffffffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_1);
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi_1 
                = (0x3ffffffffffffffULL & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_3);
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_prv 
                = (3U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_122));
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT___value_T_3;
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__do_deq) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__deq_ptr_value 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT___value_T_3;
        }
        if (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full)) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_deq_valid))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__gennum 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__new_gennum;
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_out_d_ready) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full))) {
            if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__acknum))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dToggle 
                    = (1U & (vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_extra_tlrr_extra_source
                             [0U] >> 3U));
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__acknum 
                = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__dFirst)
                          ? vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_extra_tlrr_extra_source
                         [0U] : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT___acknum_T_1)));
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__b_delay 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_b_valid) 
            & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_b_ready)))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___b_delay_T_1)
            : 0U);
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_burst[0U] = 1U;
    }
    if (__VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst[0U] 
            = __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_burst__v0;
    }
    if (__VdlySet__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst[0U] 
            = __VdlyVal__TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_burst__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size[0U] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size__v0;
    }
    if (__VdlySet__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source[__VdlyDim0__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0] 
            = __VdlyVal__TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_source__v0;
    }
    if (__VdlySet__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id[__VdlyDim0__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0] 
            = __VdlyVal__TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id__v0;
    }
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__3(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__3\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__intsource_1__DOT__reg___DOT__reg_ 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__bundleOut_0_0_REG) 
               > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__threshold_0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__intsource_2__DOT__reg___DOT__reg_ 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__bundleOut_1_0_REG) 
               > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__threshold_1)));
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__4(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__4\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_14) 
         & vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_mask
         [0U])) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__threshold_0 
            = (3U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                            [0U]));
    }
    if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_11) 
         & vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_mask
         [0U])) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__threshold_1 
            = (3U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                            [0U]));
    }
}

VL_INLINE_OPT void VTestHarness___024root___nba_sequent__TOP__5(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___nba_sequent__TOP__5\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_8;
    VlWide<4>/*127:0*/ __Vtemp_12;
    VlWide<4>/*127:0*/ __Vtemp_13;
    // Body
    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode 
        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode;
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_wfi 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && ((1U & (~ (((0U != vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__pending_interrupts) 
                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__intsink__DOT__chain__DOT__output_chain__DOT__sync_0)) 
                         | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_trace_0_exception)))) 
               && ((((IData)(((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_rw_cmd)) 
                              & (0x10000000U == (0x32200000U 
                                                 & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst)))) 
                     & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_singleStep))) 
                    & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug))) 
                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_wfi))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcounteren 
        = (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_430);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_scounteren 
        = (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_429);
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tvm = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs = 0U;
        vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_cause = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_action = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_x = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_w = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_r = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa = 0x800000000094112dULL;
    } else {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
            if ((0x300U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_tvm 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 0x14U)));
            }
            if ((0x100U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs 
                    = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                             >> 0xdU))))
                        ? 3U : 0U);
            } else if ((0x300U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                   >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs 
                    = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                             >> 0xdU))))
                        ? 3U : 0U);
            }
            if ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)))) {
                if ((0x7a1U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                >> 0x14U))) {
                    vlSelfRef.__Vdly__TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode 
                        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__dMode;
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_action 
                        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__dMode) 
                           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___newBPC_T_8 
                                      >> 0xcU)));
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_x 
                        = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                         >> 2U)));
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_w 
                        = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                         >> 1U)));
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_r 
                        = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata));
                }
            }
            if ((0x301U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                if ((1U & ((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc 
                                       >> 1U))) | (IData)(
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                                           >> 2U))))) {
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa 
                        = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___reg_misa_T_8;
                }
            }
        }
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_trace_0_exception) {
            if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__trapToDebug) {
                if ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)))) {
                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dcsr_cause 
                        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_singleStepped)
                            ? 4U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__causeIsDebugInt)
                                     ? 3U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__causeIsDebugTrigger)
                                              ? 2U : 1U)));
                }
            }
        }
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__valid_stage0_v) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_invalidExc_b 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny) 
               | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfA) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroB)) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroA)) 
                     | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB)) 
                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_isInfProd) 
                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC)))))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isNaN 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNC));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isInf 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_isInf;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isZero 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
               | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)) 
                  & (0U == (0xc0000U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT___notCDom_mainSig_T[1U]))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sign 
            = (1U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_isInfProd) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd)) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)) 
                        | (((2U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b)) 
                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)))) 
                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
                               & ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b)) 
                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)))) 
                              | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_isInf)) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros)) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)
                                        : ((0U == (3U 
                                                   & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT___notCDom_mainSig_T[1U] 
                                                      >> 0x12U)))
                                            ? (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b))
                                            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                               ^ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__sigSum_hi_hi 
                                                  >> 2U)))))))))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sExp 
            = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)
                          ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum) 
                             - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags))
                          : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum) 
                             - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notCDom_nearNormDist))));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b 
            = (0x1ffffffffffffULL & ((0xffffffffffffULL 
                                      & ((QData)((IData)(
                                                         (((0U 
                                                            != 
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in1[0U] 
                                                             >> 0x1dU)) 
                                                           << 0x17U) 
                                                          | (0x7fffffU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in1[0U])))) 
                                         * (QData)((IData)(
                                                           (((0U 
                                                              != 
                                                              (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U] 
                                                               >> 0x1dU)) 
                                                             << 0x17U) 
                                                            | (0x7fffffU 
                                                               & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U])))))) 
                                     + (0xffffffffffffULL 
                                        & (((QData)((IData)(
                                                            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[1U])) 
                                            << 0x1dU) 
                                           | ((QData)((IData)(
                                                              vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[0U])) 
                                              >> 3U)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroC 
            = (0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U] 
                      >> 0x1dU));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroB 
            = (0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U] 
                      >> 0x1dU));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB 
            = (IData)((0xc0000000U == (0xe0000000U 
                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U])));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC 
            = (IData)((0xc0000000U == (0xe0000000U 
                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U])));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum 
            = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul_io_toPostMul_CIsDominant)
                          ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U] 
                             >> 0x17U) : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__sExpAlignedProd) 
                                          - (IData)(0x18U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny 
            = (((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in1[0U] 
                    >> 0x16U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__rawA___05FisNaN)) 
               | (((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U] 
                       >> 0x16U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__rawB___05FisNaN)) 
                  | ((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U] 
                         >> 0x16U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul_io_toPostMul_isNaNC))));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__valid_stage0_v) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sig 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_sig;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_roundingMode_b 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundingMode_stage0_b;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__io_validout_v) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_exc 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_exceptionFlags;
        if ((7U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[1U] 
                    >> 0x1dU))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[0U] 
                = (IData)((0xefefffffffffffffULL & vlSelfRef.__VdfgRegularize_hd87f99a1_146_5));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[1U] 
                = (IData)(((0xefefffffffffffffULL & vlSelfRef.__VdfgRegularize_hd87f99a1_146_5) 
                           >> 0x20U));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[2U] 
                = vlSelfRef.__VdfgRegularize_hd87f99a1_146_0;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[0U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[0U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[1U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[1U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[2U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[2U];
        }
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__io_status_dprv_REG 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mprv) 
            & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_mpp)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_prv));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__csr_wen) {
        if ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_dmode)) 
                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_debug)))) {
            if ((0x7a1U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                            >> 0x14U))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_tmatch 
                    = (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 7U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_m 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 6U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_s 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 4U)));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_bp_0_control_u 
                    = (1U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__wdata 
                                     >> 3U)));
            }
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killd)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_load_use 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid) 
               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__data_hazard_mem) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_mem)));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_pc_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_mem 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_mem;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_wxd 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_wxd;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_cause 
            = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_xcpt_interrupt) 
                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_xcpt))
                ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_cause
                : (QData)((IData)(((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_76)
                                    ? 0U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_debug_breakpoint)
                                             ? 0xeU
                                             : 3U)))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_wdata 
            = ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_xcpt)) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_fp)) 
                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_wxd))
                ? ((1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__in_wflags)
                           ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__in_ren2)) 
                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__in_typ) 
                                 >> 1U)) : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__in_rm)) 
                                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__in_fmt))))
                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__toint
                    : (((QData)((IData)(((1U & (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__toint 
                                                        >> 0x1fU)))
                                          ? 0xffffffffU
                                          : 0U))) << 0x20U) 
                       | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpiu__DOT__toint))))
                : (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_xcpt)) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_jalr) 
                       ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_npc_misaligned)))
                    ? (((QData)((IData)((0xffffffU 
                                         & (- (IData)(
                                                      (1U 
                                                       & (IData)(
                                                                 (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_br_target 
                                                                  >> 0x27U)))))))) 
                        << 0x28U) | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_br_target)
                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_wdata));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_pc;
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__valid_stage0_v) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_invalidExc_b 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny) 
               | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfA) 
                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroB)) 
                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroA)) 
                     | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB)) 
                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_isInfProd) 
                           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC)))))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isNaN 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNC));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isInf 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_isInf;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isZero 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
               | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)) 
                  & (0U == (0x3000U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT___notCDom_mainSig_T[3U]))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sign 
            = (1U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_isInfProd) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd)) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)) 
                        | (((2U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b)) 
                            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)))) 
                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros) 
                               & ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b)) 
                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)))) 
                              | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_isInf)) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notNaN_addZeros)) 
                                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)
                                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__CDom_sign)
                                        : ((0U == (3U 
                                                   & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT___notCDom_mainSig_T[3U] 
                                                      >> 0xcU)))
                                            ? (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_roundingMode_b))
                                            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) 
                                               ^ (IData)(
                                                         (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__sigSum_hi_hi 
                                                          >> 2U))))))))))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sExp 
            = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant)
                           ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum) 
                              - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags))
                           : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum) 
                              - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul__DOT__notCDom_nearNormDist))));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__valid) {
        __Vtemp_4[0U] = (IData)((((QData)((IData)((0U 
                                                   != 
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[1U] 
                                                    >> 0x1dU)))) 
                                  << 0x34U) | (0xfffffffffffffULL 
                                               & (((QData)((IData)(
                                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[1U])) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(
                                                                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[0U]))))));
        __Vtemp_4[1U] = (IData)(((((QData)((IData)(
                                                   (0U 
                                                    != 
                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[1U] 
                                                     >> 0x1dU)))) 
                                   << 0x34U) | (0xfffffffffffffULL 
                                                & (((QData)((IData)(
                                                                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[1U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[0U]))))) 
                                 >> 0x20U));
        __Vtemp_4[2U] = 0U;
        __Vtemp_4[3U] = 0U;
        __Vtemp_5[0U] = (IData)((((QData)((IData)((0U 
                                                   != 
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U] 
                                                    >> 0x1dU)))) 
                                  << 0x34U) | (0xfffffffffffffULL 
                                               & (((QData)((IData)(
                                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U])) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(
                                                                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[0U]))))));
        __Vtemp_5[1U] = (IData)(((((QData)((IData)(
                                                   (0U 
                                                    != 
                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U] 
                                                     >> 0x1dU)))) 
                                   << 0x34U) | (0xfffffffffffffULL 
                                                & (((QData)((IData)(
                                                                    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[0U]))))) 
                                 >> 0x20U));
        __Vtemp_5[2U] = 0U;
        __Vtemp_5[3U] = 0U;
        VL_MUL_W(4, __Vtemp_6, __Vtemp_4, __Vtemp_5);
        __Vtemp_8[0U] = __Vtemp_6[0U];
        __Vtemp_8[1U] = __Vtemp_6[1U];
        __Vtemp_8[2U] = __Vtemp_6[2U];
        __Vtemp_8[3U] = (0x3ffU & __Vtemp_6[3U]);
        __Vtemp_12[0U] = ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[1U] 
                           << 0x1dU) | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[0U] 
                                        >> 3U));
        __Vtemp_12[1U] = ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[2U] 
                           << 0x1dU) | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[1U] 
                                        >> 3U));
        __Vtemp_12[2U] = ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[3U] 
                           << 0x1dU) | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[2U] 
                                        >> 3U));
        __Vtemp_12[3U] = (0x3ffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__mainAlignedSigC[3U] 
                                    >> 3U));
        VL_ADD_W(4, __Vtemp_13, __Vtemp_8, __Vtemp_12);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b[0U] 
            = __Vtemp_13[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b[1U] 
            = __Vtemp_13[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b[2U] 
            = __Vtemp_13[2U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b[3U] 
            = (0x7ffU & __Vtemp_13[3U]);
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroC 
            = (0U == (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U] 
                      >> 0x1dU));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB 
            = (IData)((0xc0000000U == (0xe0000000U 
                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U])));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC 
            = (IData)((0xc0000000U == (0xe0000000U 
                                       & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U])));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum 
            = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul_io_toPostMul_CIsDominant)
                           ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U] 
                              >> 0x14U) : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__sExpAlignedProd) 
                                           - (IData)(0x35U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny 
            = (((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in1[1U] 
                    >> 0x13U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__rawA___05FisNaN)) 
               | (((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in2[1U] 
                       >> 0x13U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul__DOT__rawB___05FisNaN)) 
                  | ((~ (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U] 
                         >> 0x13U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_preMul_io_toPostMul_isNaNC))));
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__valid_stage0_v) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sig 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_rawOut_sig;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN_io_roundingMode_b 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundingMode_stage0_b;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__io_validout_v 
        = ((1U & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset))) 
           && (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__valid_stage0_v));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_decode_0_fp_illegal 
        = (1U & ((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_misa 
                             >> 5U))) | (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mstatus_fs))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_valid) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_swap23) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U] = 0x80000000U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[1U] = 0U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[2U] = 0U;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[0U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_bits_in2[0U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[1U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_bits_in2[1U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in2[2U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_bits_in2[2U];
        }
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_ren3) 
             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_swap23))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U] 
                = (IData)(((((QData)((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][0U] 
                                              >> 0x1fU))) 
                             << 0x20U) | (QData)((IData)(
                                                         ((0x80000000U 
                                                           & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][1U] 
                                                              << 0xbU)) 
                                                          | (0x7fffffffU 
                                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                             [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][0U]))))) 
                           | ((0x1fU == (0x1fU & ((
                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][2U] 
                                                   << 4U) 
                                                  | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                     [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][1U] 
                                                     >> 0x1cU))))
                               ? 0ULL : 0xe0400000ULL)));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[1U] 
                = (IData)((((((QData)((IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][0U] 
                                               >> 0x1fU))) 
                              << 0x20U) | (QData)((IData)(
                                                          ((0x80000000U 
                                                            & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][1U] 
                                                               << 0xbU)) 
                                                           | (0x7fffffffU 
                                                              & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][0U]))))) 
                            | ((0x1fU == (0x1fU & (
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                    [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][2U] 
                                                    << 4U) 
                                                   | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                                                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][1U] 
                                                      >> 0x1cU))))
                                ? 0ULL : 0xe0400000ULL)) 
                           >> 0x20U));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[2U] = 0U;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[0U] = 0U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[1U] 
                = (1U & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_bits_in1[1U] 
                         ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma_io_in_bits_in2[1U]));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__in_in3[2U] = 0U;
        }
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma_io_in_valid) {
        if (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_ren3) 
             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_swap23))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[0U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][0U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][1U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[2U] 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_2][2U];
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[0U] = 0U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[1U] = 0U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__in_in3[2U] 
                = (1U & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_0][2U] 
                         ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__regfile
                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_ra_1][2U]));
        }
    }
}
