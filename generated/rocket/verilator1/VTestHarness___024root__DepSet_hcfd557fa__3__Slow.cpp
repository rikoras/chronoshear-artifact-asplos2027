// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness___024root.h"

extern const VlWide<8>/*255:0*/ VTestHarness__ConstPool__CONST_h4e9f510d_0;

VL_ATTR_COLD void VTestHarness___024root___stl_sequent__TOP__3(VTestHarness___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTestHarness___024root___stl_sequent__TOP__3\n"); );
    VTestHarness__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready = 0;
    CData/*5:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_3;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_3 = 0;
    CData/*5:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_3;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_3 = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3 = 0;
    CData/*5:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_4;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_4 = 0;
    CData/*5:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_4;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_4 = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4 = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15 = 0;
    CData/*2:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_2;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_c_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_c_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2 = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8 = 0;
    IData/*16:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner = 0;
    SData/*15:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T = 0;
    CData/*7:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1 = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_13;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_13 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_15;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_15 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT____VdfgRegularize_hf19bc0bf_0_4;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT____VdfgRegularize_hf19bc0bf_0_4 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0;
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_3_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_3_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_2_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_2_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_0_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_0_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_2 = 0;
    CData/*4:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys = 0;
    CData/*4:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T = 0;
    CData/*4:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_3;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_3 = 0;
    CData/*1:0*/ TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_23;
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_23 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT____VdfgRegularize_h3b583b83_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT____VdfgRegularize_h3b583b83_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_aw_valid;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_aw_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_ar_valid;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_ar_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0;
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0 = 0;
    CData/*1:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probenack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probenack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probedack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probedack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probenack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probenack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probedack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probedack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probenack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probenack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probedack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probedack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probenack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probenack = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probedack;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probedack = 0;
    CData/*4:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472 = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_499;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_499 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_19;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_19 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__monitor__DOT____VdfgRegularize_h9d8fea46_0_5;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__monitor__DOT____VdfgRegularize_h9d8fea46_0_5 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2;
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_b_ready;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_b_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_32;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_32 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en = 0;
    CData/*4:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_299;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_299 = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_303;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_303 = 0;
    CData/*3:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_313;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_313 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_38;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_38 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_46;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_46 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_62;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_62 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_8;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_8 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_18;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_18 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_28;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_28 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_38;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_38 = 0;
    QData/*63:0*/ TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_48;
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_48 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0;
    TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0;
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8;
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_in_d_bits_denied = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready = 0;
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
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__out_1_ready = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__error__DOT__done = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345 = 0;
    CData/*0:0*/ TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302;
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302 = 0;
    CData/*0:0*/ TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid;
    TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid = 0;
    CData/*0:0*/ TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_1;
    TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_1 = 0;
    CData/*0:0*/ TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT____VdfgRegularize_h93dec8dc_0_0;
    TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT____VdfgRegularize_h93dec8dc_0_0 = 0;
    CData/*0:0*/ TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT____VdfgRegularize_h93dec8dc_0_0;
    TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT____VdfgRegularize_h93dec8dc_0_0 = 0;
    CData/*0:0*/ TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0;
    TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0 = 0;
    CData/*0:0*/ __VdfgRegularize_hd87f99a1_1_180;
    __VdfgRegularize_hd87f99a1_1_180 = 0;
    VlWide<3>/*95:0*/ __Vtemp_2;
    VlWide<3>/*95:0*/ __Vtemp_3;
    VlWide<3>/*95:0*/ __Vtemp_9;
    VlWide<3>/*95:0*/ __Vtemp_11;
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
    VlWide<4>/*127:0*/ __Vtemp_255;
    VlWide<4>/*127:0*/ __Vtemp_256;
    VlWide<4>/*127:0*/ __Vtemp_257;
    VlWide<4>/*127:0*/ __Vtemp_258;
    VlWide<4>/*127:0*/ __Vtemp_259;
    VlWide<4>/*127:0*/ __Vtemp_260;
    VlWide<4>/*127:0*/ __Vtemp_261;
    VlWide<4>/*127:0*/ __Vtemp_262;
    VlWide<4>/*127:0*/ __Vtemp_263;
    VlWide<4>/*127:0*/ __Vtemp_264;
    VlWide<4>/*127:0*/ __Vtemp_265;
    VlWide<4>/*127:0*/ __Vtemp_266;
    VlWide<4>/*127:0*/ __Vtemp_267;
    VlWide<4>/*127:0*/ __Vtemp_268;
    VlWide<4>/*127:0*/ __Vtemp_269;
    VlWide<4>/*127:0*/ __Vtemp_270;
    VlWide<4>/*127:0*/ __Vtemp_271;
    VlWide<8>/*255:0*/ __Vtemp_272;
    VlWide<8>/*255:0*/ __Vtemp_273;
    VlWide<8>/*255:0*/ __Vtemp_274;
    VlWide<8>/*255:0*/ __Vtemp_275;
    VlWide<8>/*255:0*/ __Vtemp_276;
    VlWide<8>/*255:0*/ __Vtemp_277;
    VlWide<8>/*255:0*/ __Vtemp_278;
    VlWide<8>/*255:0*/ __Vtemp_279;
    VlWide<8>/*255:0*/ __Vtemp_280;
    VlWide<8>/*255:0*/ __Vtemp_281;
    VlWide<8>/*255:0*/ __Vtemp_282;
    // Body
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__o_data__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__o_data_io_deq_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__count)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft_1))
                     ? (~ (0xfU & (VL_SHIFTL_III(5,5,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T_16), 1U) 
                                   >> 1U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state_1_1)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__o_data__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__o_data_io_deq_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__count)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft_1))
                     ? (~ (7U & (VL_SHIFTL_III(5,5,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T_16), 1U) 
                                 >> 2U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state_1_2)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__o_data__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__o_data_io_deq_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__count)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft_1))
                     ? (~ (3U & (VL_SHIFTL_III(5,5,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T_16), 1U) 
                                 >> 3U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state_1_3)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__o_data__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__o_data_io_deq_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__count)) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft_1))
                     ? (~ (1U & (VL_SHIFTL_III(5,5,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T_16), 1U) 
                                 >> 4U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state_1_4)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_2_130) 
           & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_a_bits_opcode) 
                  >> 2U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_2_128)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_2_130) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_a_bits_opcode) 
               >> 2U) | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__doneAW)) 
                         & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_4 
        = ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_4)) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_4)) 
            << 3U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_3 
        = ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_3)) 
             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_3)) 
            << 3U) | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[0U] 
        = (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_146_5);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[1U] 
        = (IData)((vlSelfRef.__VdfgRegularize_hd87f99a1_146_5 
                   >> 0x20U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN_io_out[2U] 
        = vlSelfRef.__VdfgRegularize_hd87f99a1_146_0;
    __Vtemp_2[0U] = (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shin);
    __Vtemp_2[1U] = (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shin 
                             >> 0x20U));
    __Vtemp_2[2U] = (IData)((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn) 
                              >> 3U) & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shin 
                                        >> 0x3fU)));
    VL_SHIFTRS_WWI(65,65,6, __Vtemp_3, __Vtemp_2, (
                                                   (((IData)(
                                                             (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu_io_in2 
                                                              >> 5U)) 
                                                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_dw)) 
                                                    << 5U) 
                                                   | (0x1fU 
                                                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu_io_in2))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r 
        = (((QData)((IData)(__Vtemp_3[1U])) << 0x20U) 
           | (QData)((IData)(__Vtemp_3[0U])));
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
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__beatsLeft)
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__state_0)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__readys_readys)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_198 = (((QData)((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_213)) 
                                                   << 0x34U) 
                                                  | (0xfffffffffffffULL 
                                                     & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h66486a49_0_4))
                                                          ? 
                                                         ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                           ? 0x8000000000000ULL
                                                           : 0ULL)
                                                          : 
                                                         ((1U 
                                                           & (IData)(
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sigX_Z 
                                                                      >> 0x36U)))
                                                           ? 
                                                          (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                           >> 1U)
                                                           : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig)) 
                                                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_1__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                            ? 0xfffffffffffffULL
                                                            : 0ULL))));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys 
        = (0x1fU & (~ (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_unready) 
                        >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_unready))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___io_imem_ready_T_4 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nIC) 
                 - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nICReady)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__acq_needT 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_param)) 
           | (1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_param)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_95 = ((6U 
                                                  != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_opcode)) 
                                                 & (7U 
                                                    != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_opcode)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_460 
        = (((((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__address 
               >> 6U) == (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_address 
                          >> 6U)) << 3U) | (((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__address 
                                              >> 6U) 
                                             == (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_address 
                                                 >> 6U)) 
                                            << 2U)) 
           | ((((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__address 
                 >> 6U) == (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_address 
                            >> 6U)) << 1U) | ((vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__address 
                                               >> 6U) 
                                              == (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_address 
                                                  >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_size 
        = ((3U <= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size))
            ? 3U : (7U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id 
        = ((0x12U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
            ? 0U : ((0x11U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                     ? 3U : ((0x10U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                              ? 4U : ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                       ? 2U : ((0xeU 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                ? 2U
                                                : (
                                                   (0xdU 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                    ? 2U
                                                    : 
                                                   ((0xcU 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                     ? 2U
                                                     : 
                                                    ((0xbU 
                                                      == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                      ? 2U
                                                      : 
                                                     ((0xaU 
                                                       == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                       ? 2U
                                                       : 
                                                      ((9U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                        ? 2U
                                                        : 
                                                       ((8U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                         ? 2U
                                                         : 1U)))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_bits_last 
        = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter)) 
           | (0U == ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode))
                      ? 0U : (0x1fU & (~ (0x1fU & (
                                                   ((IData)(0xffU) 
                                                    << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size)) 
                                                   >> 3U)))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2 
        = (1U & ((~ ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3)) 
                     | ((1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                                  >> 2U))) == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__write_2)))) 
                 | (8U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_canLogical 
        = ((3U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_size)) 
           & (0U == (0xa012000U & (0x2000U ^ vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_address))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_78)
                     ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_tag) 
                        >> 2U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__req_tag)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div_io_resp_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_78)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_74));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_bits_write) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb_io_out_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_d_ready));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor__DOT____VdfgRegularize_h68575f32_0_2) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantIsCached) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_231 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_ack_wait;
            TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_73;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng_io_increment 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__d_last;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_231 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_205;
            TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way 
                = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantIsUncached)
                    ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantIsUncachedData)
                        ? 0x10U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_73))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_73));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng_io_increment = 0U;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_231 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_ack_wait;
        TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_73;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng_io_increment = 0U;
    }
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantIsCached) 
           & ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__ram_denied
               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__value_1]) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__d_last) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor__DOT____VdfgRegularize_h68575f32_0_2))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_replay_next 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor__DOT____VdfgRegularize_h68575f32_0_2) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantIsUncachedData));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT___readys_mask_T 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_filter_lo));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor_1__DOT__a_first_done 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q_io_enq_ready) 
            & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__beatsLeft))
                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_readys) 
                   >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__state_1))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache_auto_master_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__earlyWinner_1 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_readys) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache_auto_master_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__earlyWinner_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_in_0_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__beatsLeft))
               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__readys_readys)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__state_0)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__inc_addr_1 
        = (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__addr_1 
           + (0xffffU & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_size))));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___GEN_58 
        = (0x7fffU & (((0xffU | ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_len) 
                                 << 8U)) << (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_bits_size)) 
                      >> 8U));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__inc_addr 
        = (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__addr 
           + (0xffffU & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_bits_size))));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___GEN_49 
        = (0x7fffU & (((0xffU | ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_bits_len) 
                                 << 8U)) << (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_bits_size)) 
                      >> 8U));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__len)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_aw_ready) 
           & (0U == (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__len_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)
            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___GEN_95))
            : ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___GEN_15)));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_28 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_23 
        = (0x3fU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_4) 
                    | VL_SHIFTR_III(6,6,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_4), 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_22 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_opcode_MPORT_en)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_16 
        = (0x3fU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_3) 
                    | VL_SHIFTR_III(6,6,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_3), 1U)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_8 
        = (VL_SHIFTR_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r, 0x20U) 
           | (0xffffffff00000000ULL & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r, 0x20U)));
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
    __Vtemp_9[0U] = (IData)((((QData)((IData)(((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)) 
                                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sign_Z)))) 
                              << 0x20U) | (QData)((IData)(
                                                          ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                ? 0x1bfU
                                                                : 0x1ffU) 
                                                              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                   ? 0x17fU
                                                                   : 0x1ffU) 
                                                                 & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                      ? 0x6bU
                                                                      : 0x1ffU) 
                                                                    & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4)
                                                                         ? 0x3fU
                                                                         : 0x1ffU) 
                                                                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp))))) 
                                                             | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                   ? 0x6bU
                                                                   : 0U) 
                                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                     ? 0x17fU
                                                                     : 0U)) 
                                                                | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                     ? 0x180U
                                                                     : 0U) 
                                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                       ? 0x1c0U
                                                                       : 0U)))) 
                                                            << 0x17U) 
                                                           | (0x7fffffU 
                                                              & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4))
                                                                   ? 
                                                                  ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                    ? 0x400000U
                                                                    : 0U)
                                                                   : 
                                                                  ((0x2000000U 
                                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sigX_Z)
                                                                    ? 
                                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                                    >> 1U)
                                                                    : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig)) 
                                                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                     ? 0x7fffffU
                                                                     : 0U))))))));
    __Vtemp_9[1U] = (IData)(((((QData)((IData)(((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sign_Z)))) 
                               << 0x20U) | (QData)((IData)(
                                                           ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                 ? 0x1bfU
                                                                 : 0x1ffU) 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                    ? 0x17fU
                                                                    : 0x1ffU) 
                                                                  & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                       ? 0x6bU
                                                                       : 0x1ffU) 
                                                                     & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4)
                                                                          ? 0x3fU
                                                                          : 0x1ffU) 
                                                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp))))) 
                                                              | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                    ? 0x6bU
                                                                    : 0U) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                      ? 0x17fU
                                                                      : 0U)) 
                                                                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                      ? 0x180U
                                                                      : 0U) 
                                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                        ? 0x1c0U
                                                                        : 0U)))) 
                                                             << 0x17U) 
                                                            | (0x7fffffU 
                                                               & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4))
                                                                    ? 
                                                                   ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                     ? 0x400000U
                                                                     : 0U)
                                                                    : 
                                                                   ((0x2000000U 
                                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sigX_Z)
                                                                     ? 
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                                     >> 1U)
                                                                     : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig)) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                      ? 0x7fffffU
                                                                      : 0U))))))) 
                             >> 0x20U));
    __Vtemp_11[0U] = (IData)((((QData)((IData)(((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sign)))) 
                               << 0x20U) | (QData)((IData)(
                                                           ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                 ? 0x1bfU
                                                                 : 0x1ffU) 
                                                               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                    ? 0x17fU
                                                                    : 0x1ffU) 
                                                                  & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                       ? 0x6bU
                                                                       : 0x1ffU) 
                                                                     & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4)
                                                                          ? 0x3fU
                                                                          : 0x1ffU) 
                                                                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp))))) 
                                                              | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                    ? 0x6bU
                                                                    : 0U) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                      ? 0x17fU
                                                                      : 0U)) 
                                                                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                      ? 0x180U
                                                                      : 0U) 
                                                                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                        ? 0x1c0U
                                                                        : 0U)))) 
                                                             << 0x17U) 
                                                            | (0x7fffffU 
                                                               & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4))
                                                                    ? 
                                                                   ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                     ? 0x400000U
                                                                     : 0U)
                                                                    : 
                                                                   ((0x4000000U 
                                                                     & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sig)
                                                                     ? 
                                                                    (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                                     >> 1U)
                                                                     : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig)) 
                                                                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                      ? 0x7fffffU
                                                                      : 0U))))))));
    __Vtemp_11[1U] = (IData)(((((QData)((IData)(((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)) 
                                                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sign)))) 
                                << 0x20U) | (QData)((IData)(
                                                            ((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                  ? 0x1bfU
                                                                  : 0x1ffU) 
                                                                & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                     ? 0x17fU
                                                                     : 0x1ffU) 
                                                                   & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                        ? 0x6bU
                                                                        : 0x1ffU) 
                                                                      & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4)
                                                                           ? 0x3fU
                                                                           : 0x1ffU) 
                                                                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__sRoundedExp))))) 
                                                               | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMinNonzeroMagOut)
                                                                     ? 0x6bU
                                                                     : 0U) 
                                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                       ? 0x17fU
                                                                       : 0U)) 
                                                                  | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__notNaN_isInfOut)
                                                                       ? 0x180U
                                                                       : 0U) 
                                                                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                         ? 0x1c0U
                                                                         : 0U)))) 
                                                              << 0x17U) 
                                                             | (0x7fffffU 
                                                                & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut) 
                                                                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT____VdfgRegularize_h058b3fb2_0_4))
                                                                     ? 
                                                                    ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__isNaNOut)
                                                                      ? 0x400000U
                                                                      : 0U)
                                                                     : 
                                                                    ((0x4000000U 
                                                                      & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sig)
                                                                      ? 
                                                                     (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig 
                                                                      >> 1U)
                                                                      : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__roundedSig)) 
                                                                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__sfma__DOT__fma__DOT__roundRawFNToRecFN__DOT__roundAnyRawFNToRecFN__DOT__pegMaxFiniteMagOut)
                                                                       ? 0x7fffffU
                                                                       : 0U))))))) 
                              >> 0x20U));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_wen) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_typeTag) {
            if ((7U == (7U & ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_213) 
                              >> 9U)))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
                    = (IData)((0xefefffffffffffffULL 
                               & vlSelfRef.__VdfgRegularize_hd87f99a1_1_198));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
                    = (IData)(((0xefefffffffffffffULL 
                                & vlSelfRef.__VdfgRegularize_hd87f99a1_1_198) 
                               >> 0x20U));
            } else {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
                    = (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_198);
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
                    = (IData)((vlSelfRef.__VdfgRegularize_hd87f99a1_1_198 
                               >> 0x20U));
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] 
                = vlSelfRef.__VdfgRegularize_hd87f99a1_1_175;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
                = __Vtemp_9[0U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
                = __Vtemp_9[1U];
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] = 0U;
        }
    } else if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wbInfo_0_pipeid))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__dfma__DOT__io_out_b_data[2U];
    } else if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wbInfo_0_pipeid))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
            = __Vtemp_11[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
            = __Vtemp_11[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] = 0U;
    } else if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wbInfo_0_pipeid))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ifpu__DOT__io_out_b_data[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ifpu__DOT__io_out_b_data[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ifpu__DOT__io_out_b_data[2U];
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[0U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__io_out_b_data[0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[1U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__io_out_b_data[1U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT___wdata_T_19[2U] 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fpmu__DOT__io_out_b_data[2U];
    }
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_0_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys)
               : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_0)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_filter_lo));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_1 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_2 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
            >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_3 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
            >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_4 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
            >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_deq_valid));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
                  >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter_auto_out_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
                  >> 4U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_4)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_3_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
                  >> 3U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_3)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_2_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))
               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__readys_readys) 
                  >> 2U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_2)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472 
        = ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_460))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_460)
            : ((~ (0x1eU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_464) 
                             | VL_SHIFTL_III(4,4,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_464), 2U)) 
                            << 1U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_450)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_13 
        = (1U & (~ (((0x12U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_1)
                      : ((0x11U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_4)
                          : ((0x10U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_5)
                              : ((0xfU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                  : ((0xeU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                      : ((0xdU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                          ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                          : ((0xcU 
                                              == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                              : ((0xbU 
                                                  == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                                  : 
                                                 ((0xaU 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                                   : 
                                                  ((9U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                                    : 
                                                   ((8U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source))
                                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__idStall_2)
                                                     : 
                                                    ((~ 
                                                      ((0U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2)) 
                                                       | ((1U 
                                                           & (~ 
                                                              ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                                                               >> 2U))) 
                                                          == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__write_1)))) 
                                                     | (8U 
                                                        == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2)))))))))))))) 
                    & (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__counter)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_isSupported 
        = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_opcode))
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_canLogical)
            : ((2U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_opcode)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_canLogical)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_78) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div_io_resp_ready) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div_io_resp_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT___GEN_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng_io_increment)
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT__state_13) 
               ^ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT__state_15) 
                  ^ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT__state_10) 
                     ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT__state_12))))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__lfsr_prng__DOT__state_0));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_136 = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_bits_way_en)
                                                   : 
                                                  ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid)
                                                    ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__refill_way)
                                                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_4_bits_way_en)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__resetting) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_data = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_idx 
            = (0x3fU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__flushCounter));
    } else if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_data 
            = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_grow_param) 
                << 0x14U) | (0xfffffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_addr 
                                                 >> 0xcU))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_idx 
            = (0x3fU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_addr 
                                >> 6U)));
    } else if (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_data 
            = ((((0xcU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___metaArb_io_in_3_bits_data_T_1))
                  ? 3U : ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___metaArb_io_in_3_bits_data_T_1))
                           ? 2U : ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___metaArb_io_in_3_bits_data_T_1))
                                    ? 2U : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___metaArb_io_in_3_bits_data_T_1))
                                             ? 1U : 0U)))) 
                << 0x14U) | (0xfffffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_addr 
                                                 >> 0xcU))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_idx 
            = (0x3fU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_addr 
                                >> 6U)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_data 
            = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_79)
                  ? 0U : ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                           ? 2U : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                    ? 2U : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                             ? 1U : 
                                            ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                              ? 0U : 
                                             ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                               ? 1U
                                               : ((6U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                                   ? 1U
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___T_118))
                                                    ? 1U
                                                    : 0U)))))))) 
                << 0x14U) | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__probe_bits_address 
                             >> 0xcU));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_idx 
            = (0x3fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_4_valid)
                         ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__probe_bits_address 
                            >> 6U) : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_6_valid)
                                       ? ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
                                           ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__probe_bits_address 
                                              >> 6U)
                                           : (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__ram_address
                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1] 
                                              >> 6U))
                                       : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr 
                                                  >> 6U)))));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_write 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__resetting) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid) 
              | ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_4_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s0_req_addr 
        = ((0xffffffffc0ULL & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__resetting)
                                ? (((QData)((IData)(
                                                    (0xfffffffU 
                                                     & (IData)(
                                                               (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr 
                                                                >> 0xcU))))) 
                                    << 0xcU) | (QData)((IData)(
                                                               (0xfc0U 
                                                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__flushCounter) 
                                                                   << 6U)))))
                                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid)
                                    ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_bits_addr
                                    : ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid)
                                        ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_bits_addr
                                        : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_4_valid)
                                            ? (((QData)((IData)(
                                                                (0xfffffffU 
                                                                 & (IData)(
                                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr 
                                                                            >> 0xcU))))) 
                                                << 0xcU) 
                                               | (QData)((IData)(
                                                                 (0xfffU 
                                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__probe_bits_address))))
                                            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_6_valid)
                                                ? (
                                                   (4U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
                                                    ? 
                                                   (((QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr 
                                                                                >> 0x20U))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__probe_bits_address)))
                                                    : 
                                                   (((QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(
                                                                                (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr 
                                                                                >> 0x20U))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__ram_address
                                                                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1]))))
                                                : vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr)))))) 
           | (QData)((IData)((0x3fU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_addr)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__resetting) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid) 
              | (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_3_valid)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_replay_next) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__inWriteback) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_did_read) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_read_mask))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__dcache_kill_mem 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_80) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_replay_next));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT___GEN_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor_1__DOT__a_first_done)
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_13) 
               ^ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_15) 
                  ^ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_10) 
                     ^ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_12))))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_0));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__beatsLeft))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__earlyWinner_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__earlyWinner_0;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__state_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__state_0;
    }
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_62 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_in_0_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_s2_nack 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_valid_uncached_pending) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_in_0_a_ready))) 
           & ((~ (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_valid_masked) 
                   & (0x17U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_cmd))) 
                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_valid_hit_pre_data_ecc_and_waw))) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_valid_no_xcpt)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)
            ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0)
            : ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0)));
    TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_deq_valid));
    TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq_io_deq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_ar_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_aw_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    __Vtemp_18[0U] = 1U;
    __Vtemp_18[1U] = 0U;
    __Vtemp_18[2U] = 0U;
    __Vtemp_18[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_19, __Vtemp_18, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_510 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_128) 
                 + ((__Vtemp_19[3U] >> 0x1fU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_20[0U] = 1U;
    __Vtemp_20[1U] = 0U;
    __Vtemp_20[2U] = 0U;
    __Vtemp_20[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_21, __Vtemp_20, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_506 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_127) 
                 + ((__Vtemp_21[3U] >> 0x1eU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_22[0U] = 1U;
    __Vtemp_22[1U] = 0U;
    __Vtemp_22[2U] = 0U;
    __Vtemp_22[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_23, __Vtemp_22, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_502 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_126) 
                 + ((__Vtemp_23[3U] >> 0x1dU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_24[0U] = 1U;
    __Vtemp_24[1U] = 0U;
    __Vtemp_24[2U] = 0U;
    __Vtemp_24[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_25, __Vtemp_24, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_498 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_125) 
                 + ((__Vtemp_25[3U] >> 0x1cU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_26[0U] = 1U;
    __Vtemp_26[1U] = 0U;
    __Vtemp_26[2U] = 0U;
    __Vtemp_26[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_27, __Vtemp_26, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_494 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_124) 
                 + ((__Vtemp_27[3U] >> 0x1bU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_28[0U] = 1U;
    __Vtemp_28[1U] = 0U;
    __Vtemp_28[2U] = 0U;
    __Vtemp_28[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_29, __Vtemp_28, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_490 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_123) 
                 + ((__Vtemp_29[3U] >> 0x1aU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_30[0U] = 1U;
    __Vtemp_30[1U] = 0U;
    __Vtemp_30[2U] = 0U;
    __Vtemp_30[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_31, __Vtemp_30, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_486 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_122) 
                 + ((__Vtemp_31[3U] >> 0x19U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_32[0U] = 1U;
    __Vtemp_32[1U] = 0U;
    __Vtemp_32[2U] = 0U;
    __Vtemp_32[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_33, __Vtemp_32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_482 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_121) 
                 + ((__Vtemp_33[3U] >> 0x18U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_34[0U] = 1U;
    __Vtemp_34[1U] = 0U;
    __Vtemp_34[2U] = 0U;
    __Vtemp_34[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_35, __Vtemp_34, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_478 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_120) 
                 + ((__Vtemp_35[3U] >> 0x17U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_36[0U] = 1U;
    __Vtemp_36[1U] = 0U;
    __Vtemp_36[2U] = 0U;
    __Vtemp_36[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_37, __Vtemp_36, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_474 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_119) 
                 + ((__Vtemp_37[3U] >> 0x16U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_38[0U] = 1U;
    __Vtemp_38[1U] = 0U;
    __Vtemp_38[2U] = 0U;
    __Vtemp_38[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_39, __Vtemp_38, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_470 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_118) 
                 + ((__Vtemp_39[3U] >> 0x15U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_40[0U] = 1U;
    __Vtemp_40[1U] = 0U;
    __Vtemp_40[2U] = 0U;
    __Vtemp_40[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_41, __Vtemp_40, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_466 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_117) 
                 + ((__Vtemp_41[3U] >> 0x14U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_42[0U] = 1U;
    __Vtemp_42[1U] = 0U;
    __Vtemp_42[2U] = 0U;
    __Vtemp_42[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_43, __Vtemp_42, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_462 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_116) 
                 + ((__Vtemp_43[3U] >> 0x13U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_44[0U] = 1U;
    __Vtemp_44[1U] = 0U;
    __Vtemp_44[2U] = 0U;
    __Vtemp_44[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_45, __Vtemp_44, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_458 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_115) 
                 + ((__Vtemp_45[3U] >> 0x12U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_46[0U] = 1U;
    __Vtemp_46[1U] = 0U;
    __Vtemp_46[2U] = 0U;
    __Vtemp_46[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_47, __Vtemp_46, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_454 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_114) 
                 + ((__Vtemp_47[3U] >> 0x11U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_48[0U] = 1U;
    __Vtemp_48[1U] = 0U;
    __Vtemp_48[2U] = 0U;
    __Vtemp_48[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_49, __Vtemp_48, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_450 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_113) 
                 + ((__Vtemp_49[3U] >> 0x10U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_50[0U] = 1U;
    __Vtemp_50[1U] = 0U;
    __Vtemp_50[2U] = 0U;
    __Vtemp_50[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_51, __Vtemp_50, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_446 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_112) 
                 + ((__Vtemp_51[3U] >> 0xfU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_52[0U] = 1U;
    __Vtemp_52[1U] = 0U;
    __Vtemp_52[2U] = 0U;
    __Vtemp_52[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_53, __Vtemp_52, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_442 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_111) 
                 + ((__Vtemp_53[3U] >> 0xeU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_54[0U] = 1U;
    __Vtemp_54[1U] = 0U;
    __Vtemp_54[2U] = 0U;
    __Vtemp_54[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_55, __Vtemp_54, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_438 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_110) 
                 + ((__Vtemp_55[3U] >> 0xdU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_56[0U] = 1U;
    __Vtemp_56[1U] = 0U;
    __Vtemp_56[2U] = 0U;
    __Vtemp_56[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_57, __Vtemp_56, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_434 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_109) 
                 + ((__Vtemp_57[3U] >> 0xcU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_58[0U] = 1U;
    __Vtemp_58[1U] = 0U;
    __Vtemp_58[2U] = 0U;
    __Vtemp_58[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_59, __Vtemp_58, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_430 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_108) 
                 + ((__Vtemp_59[3U] >> 0xbU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_60[0U] = 1U;
    __Vtemp_60[1U] = 0U;
    __Vtemp_60[2U] = 0U;
    __Vtemp_60[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_61, __Vtemp_60, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_426 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_107) 
                 + ((__Vtemp_61[3U] >> 0xaU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_62[0U] = 1U;
    __Vtemp_62[1U] = 0U;
    __Vtemp_62[2U] = 0U;
    __Vtemp_62[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_63, __Vtemp_62, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_422 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_106) 
                 + ((__Vtemp_63[3U] >> 9U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_64[0U] = 1U;
    __Vtemp_64[1U] = 0U;
    __Vtemp_64[2U] = 0U;
    __Vtemp_64[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_65, __Vtemp_64, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_418 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_105) 
                 + ((__Vtemp_65[3U] >> 8U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_66[0U] = 1U;
    __Vtemp_66[1U] = 0U;
    __Vtemp_66[2U] = 0U;
    __Vtemp_66[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_67, __Vtemp_66, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_414 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_104) 
                 + ((__Vtemp_67[3U] >> 7U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_68[0U] = 1U;
    __Vtemp_68[1U] = 0U;
    __Vtemp_68[2U] = 0U;
    __Vtemp_68[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_69, __Vtemp_68, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_410 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_103) 
                 + ((__Vtemp_69[3U] >> 6U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_70[0U] = 1U;
    __Vtemp_70[1U] = 0U;
    __Vtemp_70[2U] = 0U;
    __Vtemp_70[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_71, __Vtemp_70, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_406 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_102) 
                 + ((__Vtemp_71[3U] >> 5U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_72[0U] = 1U;
    __Vtemp_72[1U] = 0U;
    __Vtemp_72[2U] = 0U;
    __Vtemp_72[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_73, __Vtemp_72, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_402 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_101) 
                 + ((__Vtemp_73[3U] >> 4U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_74[0U] = 1U;
    __Vtemp_74[1U] = 0U;
    __Vtemp_74[2U] = 0U;
    __Vtemp_74[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_75, __Vtemp_74, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_398 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_100) 
                 + ((__Vtemp_75[3U] >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_76[0U] = 1U;
    __Vtemp_76[1U] = 0U;
    __Vtemp_76[2U] = 0U;
    __Vtemp_76[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_77, __Vtemp_76, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_394 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_99) 
                 + ((__Vtemp_77[3U] >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_78[0U] = 1U;
    __Vtemp_78[1U] = 0U;
    __Vtemp_78[2U] = 0U;
    __Vtemp_78[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_79, __Vtemp_78, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_390 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_98) 
                 + ((__Vtemp_79[3U] >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_80[0U] = 1U;
    __Vtemp_80[1U] = 0U;
    __Vtemp_80[2U] = 0U;
    __Vtemp_80[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_81, __Vtemp_80, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_386 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_97) 
                 + (__Vtemp_81[3U] & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_82[0U] = 1U;
    __Vtemp_82[1U] = 0U;
    __Vtemp_82[2U] = 0U;
    __Vtemp_82[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_83, __Vtemp_82, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_382 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_96) 
                 + ((__Vtemp_83[2U] >> 0x1fU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_84[0U] = 1U;
    __Vtemp_84[1U] = 0U;
    __Vtemp_84[2U] = 0U;
    __Vtemp_84[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_85, __Vtemp_84, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_378 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_95) 
                 + ((__Vtemp_85[2U] >> 0x1eU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_86[0U] = 1U;
    __Vtemp_86[1U] = 0U;
    __Vtemp_86[2U] = 0U;
    __Vtemp_86[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_87, __Vtemp_86, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_374 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_94) 
                 + ((__Vtemp_87[2U] >> 0x1dU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_88[0U] = 1U;
    __Vtemp_88[1U] = 0U;
    __Vtemp_88[2U] = 0U;
    __Vtemp_88[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_89, __Vtemp_88, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_370 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_93) 
                 + ((__Vtemp_89[2U] >> 0x1cU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_90[0U] = 1U;
    __Vtemp_90[1U] = 0U;
    __Vtemp_90[2U] = 0U;
    __Vtemp_90[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_91, __Vtemp_90, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_366 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_92) 
                 + ((__Vtemp_91[2U] >> 0x1bU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_92[0U] = 1U;
    __Vtemp_92[1U] = 0U;
    __Vtemp_92[2U] = 0U;
    __Vtemp_92[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_93, __Vtemp_92, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_362 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_91) 
                 + ((__Vtemp_93[2U] >> 0x1aU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_94[0U] = 1U;
    __Vtemp_94[1U] = 0U;
    __Vtemp_94[2U] = 0U;
    __Vtemp_94[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_95, __Vtemp_94, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_358 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_90) 
                 + ((__Vtemp_95[2U] >> 0x19U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_96[0U] = 1U;
    __Vtemp_96[1U] = 0U;
    __Vtemp_96[2U] = 0U;
    __Vtemp_96[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_97, __Vtemp_96, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_354 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_89) 
                 + ((__Vtemp_97[2U] >> 0x18U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_98[0U] = 1U;
    __Vtemp_98[1U] = 0U;
    __Vtemp_98[2U] = 0U;
    __Vtemp_98[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_99, __Vtemp_98, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_350 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_88) 
                 + ((__Vtemp_99[2U] >> 0x17U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_100[0U] = 1U;
    __Vtemp_100[1U] = 0U;
    __Vtemp_100[2U] = 0U;
    __Vtemp_100[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_101, __Vtemp_100, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_346 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_87) 
                 + ((__Vtemp_101[2U] >> 0x16U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_102[0U] = 1U;
    __Vtemp_102[1U] = 0U;
    __Vtemp_102[2U] = 0U;
    __Vtemp_102[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_103, __Vtemp_102, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_342 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_86) 
                 + ((__Vtemp_103[2U] >> 0x15U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_104[0U] = 1U;
    __Vtemp_104[1U] = 0U;
    __Vtemp_104[2U] = 0U;
    __Vtemp_104[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_105, __Vtemp_104, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_338 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_85) 
                 + ((__Vtemp_105[2U] >> 0x14U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_106[0U] = 1U;
    __Vtemp_106[1U] = 0U;
    __Vtemp_106[2U] = 0U;
    __Vtemp_106[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_107, __Vtemp_106, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_334 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_84) 
                 + ((__Vtemp_107[2U] >> 0x13U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_108[0U] = 1U;
    __Vtemp_108[1U] = 0U;
    __Vtemp_108[2U] = 0U;
    __Vtemp_108[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_109, __Vtemp_108, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_330 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_83) 
                 + ((__Vtemp_109[2U] >> 0x12U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_110[0U] = 1U;
    __Vtemp_110[1U] = 0U;
    __Vtemp_110[2U] = 0U;
    __Vtemp_110[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_111, __Vtemp_110, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_326 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_82) 
                 + ((__Vtemp_111[2U] >> 0x11U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_112[0U] = 1U;
    __Vtemp_112[1U] = 0U;
    __Vtemp_112[2U] = 0U;
    __Vtemp_112[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_113, __Vtemp_112, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_322 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_81) 
                 + ((__Vtemp_113[2U] >> 0x10U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_114[0U] = 1U;
    __Vtemp_114[1U] = 0U;
    __Vtemp_114[2U] = 0U;
    __Vtemp_114[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_115, __Vtemp_114, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_318 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_80) 
                 + ((__Vtemp_115[2U] >> 0xfU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_116[0U] = 1U;
    __Vtemp_116[1U] = 0U;
    __Vtemp_116[2U] = 0U;
    __Vtemp_116[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_117, __Vtemp_116, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_314 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_79) 
                 + ((__Vtemp_117[2U] >> 0xeU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_118[0U] = 1U;
    __Vtemp_118[1U] = 0U;
    __Vtemp_118[2U] = 0U;
    __Vtemp_118[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_119, __Vtemp_118, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_310 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_78) 
                 + ((__Vtemp_119[2U] >> 0xdU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_120[0U] = 1U;
    __Vtemp_120[1U] = 0U;
    __Vtemp_120[2U] = 0U;
    __Vtemp_120[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_121, __Vtemp_120, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_306 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_77) 
                 + ((__Vtemp_121[2U] >> 0xcU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_122[0U] = 1U;
    __Vtemp_122[1U] = 0U;
    __Vtemp_122[2U] = 0U;
    __Vtemp_122[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_123, __Vtemp_122, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_302 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_76) 
                 + ((__Vtemp_123[2U] >> 0xbU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_124[0U] = 1U;
    __Vtemp_124[1U] = 0U;
    __Vtemp_124[2U] = 0U;
    __Vtemp_124[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_125, __Vtemp_124, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_298 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_75) 
                 + ((__Vtemp_125[2U] >> 0xaU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_126[0U] = 1U;
    __Vtemp_126[1U] = 0U;
    __Vtemp_126[2U] = 0U;
    __Vtemp_126[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_127, __Vtemp_126, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_294 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_74) 
                 + ((__Vtemp_127[2U] >> 9U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_128[0U] = 1U;
    __Vtemp_128[1U] = 0U;
    __Vtemp_128[2U] = 0U;
    __Vtemp_128[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_129, __Vtemp_128, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_290 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_73) 
                 + ((__Vtemp_129[2U] >> 8U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_130[0U] = 1U;
    __Vtemp_130[1U] = 0U;
    __Vtemp_130[2U] = 0U;
    __Vtemp_130[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_131, __Vtemp_130, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_286 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_72) 
                 + ((__Vtemp_131[2U] >> 7U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_132[0U] = 1U;
    __Vtemp_132[1U] = 0U;
    __Vtemp_132[2U] = 0U;
    __Vtemp_132[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_133, __Vtemp_132, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_282 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_71) 
                 + ((__Vtemp_133[2U] >> 6U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_134[0U] = 1U;
    __Vtemp_134[1U] = 0U;
    __Vtemp_134[2U] = 0U;
    __Vtemp_134[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_135, __Vtemp_134, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_278 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_70) 
                 + ((__Vtemp_135[2U] >> 5U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_136[0U] = 1U;
    __Vtemp_136[1U] = 0U;
    __Vtemp_136[2U] = 0U;
    __Vtemp_136[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_137, __Vtemp_136, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_274 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_69) 
                 + ((__Vtemp_137[2U] >> 4U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_138[0U] = 1U;
    __Vtemp_138[1U] = 0U;
    __Vtemp_138[2U] = 0U;
    __Vtemp_138[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_139, __Vtemp_138, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_270 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_68) 
                 + ((__Vtemp_139[2U] >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_140[0U] = 1U;
    __Vtemp_140[1U] = 0U;
    __Vtemp_140[2U] = 0U;
    __Vtemp_140[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_141, __Vtemp_140, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_266 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_67) 
                 + ((__Vtemp_141[2U] >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_142[0U] = 1U;
    __Vtemp_142[1U] = 0U;
    __Vtemp_142[2U] = 0U;
    __Vtemp_142[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_143, __Vtemp_142, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_262 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_66) 
                 + ((__Vtemp_143[2U] >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_144[0U] = 1U;
    __Vtemp_144[1U] = 0U;
    __Vtemp_144[2U] = 0U;
    __Vtemp_144[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_145, __Vtemp_144, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_258 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_65) 
                 + (__Vtemp_145[2U] & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_146[0U] = 1U;
    __Vtemp_146[1U] = 0U;
    __Vtemp_146[2U] = 0U;
    __Vtemp_146[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_147, __Vtemp_146, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_254 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_64) 
                 + ((__Vtemp_147[1U] >> 0x1fU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_148[0U] = 1U;
    __Vtemp_148[1U] = 0U;
    __Vtemp_148[2U] = 0U;
    __Vtemp_148[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_149, __Vtemp_148, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_250 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_63) 
                 + ((__Vtemp_149[1U] >> 0x1eU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_150[0U] = 1U;
    __Vtemp_150[1U] = 0U;
    __Vtemp_150[2U] = 0U;
    __Vtemp_150[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_151, __Vtemp_150, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_246 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_62) 
                 + ((__Vtemp_151[1U] >> 0x1dU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_152[0U] = 1U;
    __Vtemp_152[1U] = 0U;
    __Vtemp_152[2U] = 0U;
    __Vtemp_152[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_153, __Vtemp_152, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_242 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_61) 
                 + ((__Vtemp_153[1U] >> 0x1cU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_154[0U] = 1U;
    __Vtemp_154[1U] = 0U;
    __Vtemp_154[2U] = 0U;
    __Vtemp_154[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_155, __Vtemp_154, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_238 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_60) 
                 + ((__Vtemp_155[1U] >> 0x1bU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_156[0U] = 1U;
    __Vtemp_156[1U] = 0U;
    __Vtemp_156[2U] = 0U;
    __Vtemp_156[3U] = 0U;
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_addr 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_addr
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_len 
            = (0xffU & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_len
               [0U]);
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_size
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_echo_tl_state_source
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen 
            = (1U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_wen
               [0U]);
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_size 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_size
            [0U];
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id
            [0U];
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_addr 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_address;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_len 
            = (0xffU & (~ (0xffU & (((IData)(0x7ffU) 
                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size)) 
                                    >> 3U))));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_size 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_size;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_echo_tl_state_source 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_source;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen 
            = (1U & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                        >> 2U)));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_size 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_size;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id;
    }
    VL_SHIFTL_WWI(128,128,7, __Vtemp_157, __Vtemp_156, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_234 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_59) 
                 + ((__Vtemp_157[1U] >> 0x1aU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_158[0U] = 1U;
    __Vtemp_158[1U] = 0U;
    __Vtemp_158[2U] = 0U;
    __Vtemp_158[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_159, __Vtemp_158, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_230 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_58) 
                 + ((__Vtemp_159[1U] >> 0x19U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_160[0U] = 1U;
    __Vtemp_160[1U] = 0U;
    __Vtemp_160[2U] = 0U;
    __Vtemp_160[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_161, __Vtemp_160, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_226 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_57) 
                 + ((__Vtemp_161[1U] >> 0x18U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_162[0U] = 1U;
    __Vtemp_162[1U] = 0U;
    __Vtemp_162[2U] = 0U;
    __Vtemp_162[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_163, __Vtemp_162, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_222 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_56) 
                 + ((__Vtemp_163[1U] >> 0x17U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_164[0U] = 1U;
    __Vtemp_164[1U] = 0U;
    __Vtemp_164[2U] = 0U;
    __Vtemp_164[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_165, __Vtemp_164, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_218 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_55) 
                 + ((__Vtemp_165[1U] >> 0x16U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_166[0U] = 1U;
    __Vtemp_166[1U] = 0U;
    __Vtemp_166[2U] = 0U;
    __Vtemp_166[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_167, __Vtemp_166, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_214 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_54) 
                 + ((__Vtemp_167[1U] >> 0x15U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_168[0U] = 1U;
    __Vtemp_168[1U] = 0U;
    __Vtemp_168[2U] = 0U;
    __Vtemp_168[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_169, __Vtemp_168, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_210 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_53) 
                 + ((__Vtemp_169[1U] >> 0x14U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_170[0U] = 1U;
    __Vtemp_170[1U] = 0U;
    __Vtemp_170[2U] = 0U;
    __Vtemp_170[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_171, __Vtemp_170, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_206 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_52) 
                 + ((__Vtemp_171[1U] >> 0x13U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_172[0U] = 1U;
    __Vtemp_172[1U] = 0U;
    __Vtemp_172[2U] = 0U;
    __Vtemp_172[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_173, __Vtemp_172, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_202 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_51) 
                 + ((__Vtemp_173[1U] >> 0x12U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_174[0U] = 1U;
    __Vtemp_174[1U] = 0U;
    __Vtemp_174[2U] = 0U;
    __Vtemp_174[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_175, __Vtemp_174, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_198 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_50) 
                 + ((__Vtemp_175[1U] >> 0x11U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_176[0U] = 1U;
    __Vtemp_176[1U] = 0U;
    __Vtemp_176[2U] = 0U;
    __Vtemp_176[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_177, __Vtemp_176, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_194 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_49) 
                 + ((__Vtemp_177[1U] >> 0x10U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_178[0U] = 1U;
    __Vtemp_178[1U] = 0U;
    __Vtemp_178[2U] = 0U;
    __Vtemp_178[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_179, __Vtemp_178, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_190 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_48) 
                 + ((__Vtemp_179[1U] >> 0xfU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_180[0U] = 1U;
    __Vtemp_180[1U] = 0U;
    __Vtemp_180[2U] = 0U;
    __Vtemp_180[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_181, __Vtemp_180, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_186 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_47) 
                 + ((__Vtemp_181[1U] >> 0xeU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_182[0U] = 1U;
    __Vtemp_182[1U] = 0U;
    __Vtemp_182[2U] = 0U;
    __Vtemp_182[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_183, __Vtemp_182, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_182 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_46) 
                 + ((__Vtemp_183[1U] >> 0xdU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_184[0U] = 1U;
    __Vtemp_184[1U] = 0U;
    __Vtemp_184[2U] = 0U;
    __Vtemp_184[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_185, __Vtemp_184, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_178 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_45) 
                 + ((__Vtemp_185[1U] >> 0xcU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_186[0U] = 1U;
    __Vtemp_186[1U] = 0U;
    __Vtemp_186[2U] = 0U;
    __Vtemp_186[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_187, __Vtemp_186, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_174 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_44) 
                 + ((__Vtemp_187[1U] >> 0xbU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_188[0U] = 1U;
    __Vtemp_188[1U] = 0U;
    __Vtemp_188[2U] = 0U;
    __Vtemp_188[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_189, __Vtemp_188, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_170 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_43) 
                 + ((__Vtemp_189[1U] >> 0xaU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_190[0U] = 1U;
    __Vtemp_190[1U] = 0U;
    __Vtemp_190[2U] = 0U;
    __Vtemp_190[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_191, __Vtemp_190, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_166 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_42) 
                 + ((__Vtemp_191[1U] >> 9U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_192[0U] = 1U;
    __Vtemp_192[1U] = 0U;
    __Vtemp_192[2U] = 0U;
    __Vtemp_192[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_193, __Vtemp_192, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_162 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_41) 
                 + ((__Vtemp_193[1U] >> 8U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_194[0U] = 1U;
    __Vtemp_194[1U] = 0U;
    __Vtemp_194[2U] = 0U;
    __Vtemp_194[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_195, __Vtemp_194, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_158 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_40) 
                 + ((__Vtemp_195[1U] >> 7U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_196[0U] = 1U;
    __Vtemp_196[1U] = 0U;
    __Vtemp_196[2U] = 0U;
    __Vtemp_196[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_197, __Vtemp_196, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_154 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_39) 
                 + ((__Vtemp_197[1U] >> 6U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_198[0U] = 1U;
    __Vtemp_198[1U] = 0U;
    __Vtemp_198[2U] = 0U;
    __Vtemp_198[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_199, __Vtemp_198, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_150 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_38) 
                 + ((__Vtemp_199[1U] >> 5U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_200[0U] = 1U;
    __Vtemp_200[1U] = 0U;
    __Vtemp_200[2U] = 0U;
    __Vtemp_200[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_201, __Vtemp_200, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_146 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_37) 
                 + ((__Vtemp_201[1U] >> 4U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_202[0U] = 1U;
    __Vtemp_202[1U] = 0U;
    __Vtemp_202[2U] = 0U;
    __Vtemp_202[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_203, __Vtemp_202, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_142 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_36) 
                 + ((__Vtemp_203[1U] >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_204[0U] = 1U;
    __Vtemp_204[1U] = 0U;
    __Vtemp_204[2U] = 0U;
    __Vtemp_204[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_205, __Vtemp_204, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_138 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_35) 
                 + ((__Vtemp_205[1U] >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_206[0U] = 1U;
    __Vtemp_206[1U] = 0U;
    __Vtemp_206[2U] = 0U;
    __Vtemp_206[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_207, __Vtemp_206, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_134 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_34) 
                 + ((__Vtemp_207[1U] >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_208[0U] = 1U;
    __Vtemp_208[1U] = 0U;
    __Vtemp_208[2U] = 0U;
    __Vtemp_208[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_209, __Vtemp_208, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_130 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_33) 
                 + (__Vtemp_209[1U] & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_210[0U] = 1U;
    __Vtemp_210[1U] = 0U;
    __Vtemp_210[2U] = 0U;
    __Vtemp_210[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_211, __Vtemp_210, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_126 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_32) 
                 + ((__Vtemp_211[0U] >> 0x1fU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_212[0U] = 1U;
    __Vtemp_212[1U] = 0U;
    __Vtemp_212[2U] = 0U;
    __Vtemp_212[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_213, __Vtemp_212, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_122 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_31) 
                 + ((__Vtemp_213[0U] >> 0x1eU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_214[0U] = 1U;
    __Vtemp_214[1U] = 0U;
    __Vtemp_214[2U] = 0U;
    __Vtemp_214[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_215, __Vtemp_214, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_118 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_30) 
                 + ((__Vtemp_215[0U] >> 0x1dU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_216[0U] = 1U;
    __Vtemp_216[1U] = 0U;
    __Vtemp_216[2U] = 0U;
    __Vtemp_216[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_217, __Vtemp_216, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_114 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_29) 
                 + ((__Vtemp_217[0U] >> 0x1cU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_218[0U] = 1U;
    __Vtemp_218[1U] = 0U;
    __Vtemp_218[2U] = 0U;
    __Vtemp_218[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_219, __Vtemp_218, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_110 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_28) 
                 + ((__Vtemp_219[0U] >> 0x1bU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_220[0U] = 1U;
    __Vtemp_220[1U] = 0U;
    __Vtemp_220[2U] = 0U;
    __Vtemp_220[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_221, __Vtemp_220, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_106 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_27) 
                 + ((__Vtemp_221[0U] >> 0x1aU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_222[0U] = 1U;
    __Vtemp_222[1U] = 0U;
    __Vtemp_222[2U] = 0U;
    __Vtemp_222[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_223, __Vtemp_222, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_102 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_26) 
                 + ((__Vtemp_223[0U] >> 0x19U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_224[0U] = 1U;
    __Vtemp_224[1U] = 0U;
    __Vtemp_224[2U] = 0U;
    __Vtemp_224[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_225, __Vtemp_224, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_98 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_25) 
                 + ((__Vtemp_225[0U] >> 0x18U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_226[0U] = 1U;
    __Vtemp_226[1U] = 0U;
    __Vtemp_226[2U] = 0U;
    __Vtemp_226[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_227, __Vtemp_226, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_94 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_24) 
                 + ((__Vtemp_227[0U] >> 0x17U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_228[0U] = 1U;
    __Vtemp_228[1U] = 0U;
    __Vtemp_228[2U] = 0U;
    __Vtemp_228[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_229, __Vtemp_228, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_90 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_23) 
                 + ((__Vtemp_229[0U] >> 0x16U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_230[0U] = 1U;
    __Vtemp_230[1U] = 0U;
    __Vtemp_230[2U] = 0U;
    __Vtemp_230[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_231, __Vtemp_230, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_86 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_22) 
                 + ((__Vtemp_231[0U] >> 0x15U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_232[0U] = 1U;
    __Vtemp_232[1U] = 0U;
    __Vtemp_232[2U] = 0U;
    __Vtemp_232[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_233, __Vtemp_232, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_82 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_21) 
                 + ((__Vtemp_233[0U] >> 0x14U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_234[0U] = 1U;
    __Vtemp_234[1U] = 0U;
    __Vtemp_234[2U] = 0U;
    __Vtemp_234[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_235, __Vtemp_234, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_78 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_20) 
                 + ((__Vtemp_235[0U] >> 0x13U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_236[0U] = 1U;
    __Vtemp_236[1U] = 0U;
    __Vtemp_236[2U] = 0U;
    __Vtemp_236[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_237, __Vtemp_236, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_74 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_19) 
                 + ((__Vtemp_237[0U] >> 0x12U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_238[0U] = 1U;
    __Vtemp_238[1U] = 0U;
    __Vtemp_238[2U] = 0U;
    __Vtemp_238[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_239, __Vtemp_238, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_70 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_18) 
                 + ((__Vtemp_239[0U] >> 0x11U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_240[0U] = 1U;
    __Vtemp_240[1U] = 0U;
    __Vtemp_240[2U] = 0U;
    __Vtemp_240[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_241, __Vtemp_240, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_66 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_17) 
                 + ((__Vtemp_241[0U] >> 0x10U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_242[0U] = 1U;
    __Vtemp_242[1U] = 0U;
    __Vtemp_242[2U] = 0U;
    __Vtemp_242[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_243, __Vtemp_242, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_62 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_16) 
                 + ((__Vtemp_243[0U] >> 0xfU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_244[0U] = 1U;
    __Vtemp_244[1U] = 0U;
    __Vtemp_244[2U] = 0U;
    __Vtemp_244[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_245, __Vtemp_244, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_58 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_15) 
                 + ((__Vtemp_245[0U] >> 0xeU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_246[0U] = 1U;
    __Vtemp_246[1U] = 0U;
    __Vtemp_246[2U] = 0U;
    __Vtemp_246[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_247, __Vtemp_246, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_54 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_14) 
                 + ((__Vtemp_247[0U] >> 0xdU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_248[0U] = 1U;
    __Vtemp_248[1U] = 0U;
    __Vtemp_248[2U] = 0U;
    __Vtemp_248[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_249, __Vtemp_248, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_50 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_13) 
                 + ((__Vtemp_249[0U] >> 0xcU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_250[0U] = 1U;
    __Vtemp_250[1U] = 0U;
    __Vtemp_250[2U] = 0U;
    __Vtemp_250[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_251, __Vtemp_250, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_46 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_12) 
                 + ((__Vtemp_251[0U] >> 0xbU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_252[0U] = 1U;
    __Vtemp_252[1U] = 0U;
    __Vtemp_252[2U] = 0U;
    __Vtemp_252[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_253, __Vtemp_252, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_42 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_11) 
                 + ((__Vtemp_253[0U] >> 0xaU) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_254[0U] = 1U;
    __Vtemp_254[1U] = 0U;
    __Vtemp_254[2U] = 0U;
    __Vtemp_254[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_255, __Vtemp_254, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_38 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_10) 
                 + ((__Vtemp_255[0U] >> 9U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_256[0U] = 1U;
    __Vtemp_256[1U] = 0U;
    __Vtemp_256[2U] = 0U;
    __Vtemp_256[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_257, __Vtemp_256, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_34 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_9) 
                 + ((__Vtemp_257[0U] >> 8U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_258[0U] = 1U;
    __Vtemp_258[1U] = 0U;
    __Vtemp_258[2U] = 0U;
    __Vtemp_258[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_259, __Vtemp_258, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_30 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_8) 
                 + ((__Vtemp_259[0U] >> 7U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_260[0U] = 1U;
    __Vtemp_260[1U] = 0U;
    __Vtemp_260[2U] = 0U;
    __Vtemp_260[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_261, __Vtemp_260, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_26 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_7) 
                 + ((__Vtemp_261[0U] >> 6U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_262[0U] = 1U;
    __Vtemp_262[1U] = 0U;
    __Vtemp_262[2U] = 0U;
    __Vtemp_262[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_263, __Vtemp_262, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_22 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_6) 
                 + ((__Vtemp_263[0U] >> 5U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_264[0U] = 1U;
    __Vtemp_264[1U] = 0U;
    __Vtemp_264[2U] = 0U;
    __Vtemp_264[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_265, __Vtemp_264, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_18 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_5) 
                 + ((__Vtemp_265[0U] >> 4U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_266[0U] = 1U;
    __Vtemp_266[1U] = 0U;
    __Vtemp_266[2U] = 0U;
    __Vtemp_266[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_267, __Vtemp_266, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_14 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_4) 
                 + ((__Vtemp_267[0U] >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_268[0U] = 1U;
    __Vtemp_268[1U] = 0U;
    __Vtemp_268[2U] = 0U;
    __Vtemp_268[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_269, __Vtemp_268, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_10 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_3) 
                 + ((__Vtemp_269[0U] >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    __Vtemp_270[0U] = 1U;
    __Vtemp_270[1U] = 0U;
    __Vtemp_270[2U] = 0U;
    __Vtemp_270[3U] = 0U;
    VL_SHIFTL_WWI(128,128,7, __Vtemp_271, __Vtemp_270, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_6 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_2) 
                 + ((__Vtemp_271[0U] >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___count_T_2 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__count_1) 
                 + (VL_SHIFTL_III(1,1,7, (IData)(1U), (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                    & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)
            ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0)
            : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready)) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h2c1d6623_0_0)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_4 
        = (0x3fU & ((VL_SHIFTR_III(6,6,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_23), 1U) 
                     | VL_SHIFTR_III(6,6,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_23), 3U)) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_4) 
                       << 3U)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_3 
        = (0x3fU & ((VL_SHIFTR_III(6,6,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_16), 1U) 
                     | VL_SHIFTR_III(6,6,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_unready_T_16), 3U)) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_mask_3) 
                       << 3U)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_18 
        = ((0xffff0000ffffULL & (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_8 
                                 >> 0x10U)) | (0xffff0000ffff0000ULL 
                                               & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_8, 0x10U)));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_0_d_ready));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_3 
        = (0x1fU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T) 
                    | VL_SHIFTL_III(5,5,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T), 1U)));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__beatsLeft))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_3 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_4 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__earlyWinner_0;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_3 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_4 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__state_0;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_out_d_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_1_d_ready) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__drop));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_enq_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater__DOT__full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_d_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_3_d_ready) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__drop));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_d_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_out_2_d_ready) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__drop));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_in_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_18)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_in_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid) 
           & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
               >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_18)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_in_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid) 
           & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
               >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_18)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_in_a_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid) 
           & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
               >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_18)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_499 
        = (0xfU & ((1U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
                          >> 4U)) | (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_19 
        = (0U != ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_472) 
                  & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_in_a_ready) 
                       << 3U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_in_a_ready) 
                                 << 2U)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_in_a_ready) 
                                             << 1U) 
                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_in_a_ready)))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79 
        = ((7U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
           & ((6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
              & ((5U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                 & ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                     ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full))
                     : ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                         ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full))
                         : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7_io_enq_ready)
                             : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6_io_enq_ready)
                                 : (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full)))))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15 
        = ((7U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
           & ((6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
              & ((5U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                 & ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                     ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full))
                     : ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                         ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full))
                         : ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_2_io_enq_ready)
                             : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_1_io_enq_ready)
                                 : (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full)))))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_15 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_13) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_13) 
           & ((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode))
               ? (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full))
               : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_12))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_allow 
        = ((~ ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state)) 
               | (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state)))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_isSupported) 
              | (0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___T_132 
        = (0xfffffffeU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen)
                            ? (~ ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr)))
                            : 0xffffffffU) & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_waddr 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen)
                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr)
                     : (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                        >> 7U)));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_stalld 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_valid) 
            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_wxd) 
                & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_60) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_61)) 
                    | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_63) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_64)) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_65) 
                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_66)))) 
                   & ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_csr)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_jalr) 
                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_mem) 
                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_div) 
                               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_fp))))))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_wfd) 
                  & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren1) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_61)) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren2) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_64)) 
                        | (((0x40U == (0x50U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                            & ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_raw 
                                >> 0x1bU) == (0x1fU 
                                              & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_inst 
                                                 >> 7U)))) 
                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_wen) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_66)))))))) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid) 
               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__data_hazard_mem) 
                   & ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_csr)) 
                      | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_mem) 
                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_slow_bypass)) 
                         | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_div) 
                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_fp))))) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ctrl_wfd) 
                     & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren1) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_67)) 
                        | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren2) 
                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_68)) 
                           | (((0x40U == (0x50U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                               & ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_raw 
                                   >> 0x1bU) == (0x1fU 
                                                 & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_inst 
                                                    >> 7U)))) 
                              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_wen) 
                                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_69)))))))) 
              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_valid) 
                  & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_wxd) 
                      & ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_60) 
                           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_70)) 
                          | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_63) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_71)) 
                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_65) 
                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_72)))) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_set_sboard))) 
                     | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_wfd) 
                        & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren1) 
                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_70)) 
                           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren2) 
                               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_71)) 
                              | (((0x40U == (0x50U 
                                             & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                                  & ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_raw 
                                      >> 0x1bU) == 
                                     (0x1fU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                               >> 7U)))) 
                                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_wen) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_72)))))))) 
                 | ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_60) 
                      & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen) 
                             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr) 
                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1)))) 
                         & ((0xfffffffeU & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r) 
                            >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1)))) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_63) 
                         & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen) 
                                & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr) 
                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2)))) 
                            & ((0xfffffffeU & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r) 
                               >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2)))) 
                        | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_65) 
                           & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen) 
                                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_waddr) 
                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rd)))) 
                              & ((0xfffffffeU & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___r) 
                                 >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rd)))))) 
                    | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_singleStep) 
                        & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_valid) 
                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid) 
                              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_valid)))) 
                       | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_csr_en) 
                           & (IData)(((0U == (0x90000000U 
                                              & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_raw)) 
                                      & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_ctrl_wflags) 
                                          & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__ex_reg_valid)) 
                                         | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__mem_ctrl_wflags) 
                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__mem_reg_valid)) 
                                            | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wb_toint_valid) 
                                               | ((0U 
                                                   != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__wen)) 
                                                  | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__divSqrt_inFlight)))))))) 
                          | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_ctrl_decoder_1) 
                              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren1) 
                                  & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_stall_fpu___05Fr 
                                     >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs1))) 
                                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_ren2) 
                                     & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_stall_fpu___05Fr 
                                        >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rs2))) 
                                    | (((0x40U == (0x50U 
                                                   & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                                        & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_stall_fpu___05Fr 
                                           >> (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_raw 
                                               >> 0x1bU))) 
                                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__fp_decoder_io_sigs_wen) 
                                          & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_stall_fpu___05Fr 
                                             >> (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_rd))))))) 
                             | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_ctrl_decoder_14) 
                                 & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_perf_grant)) 
                                    & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__blocked))) 
                                | (((0x2000030U == 
                                     (0x2000074U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                                    & ((~ ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__state)) 
                                           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_74) 
                                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div_io_resp_valid)))) 
                                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div_io_req_valid))) 
                                   | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_mem_busy) 
                                       & ((IData)((0x2002008U 
                                                   == 
                                                   (0x2006048U 
                                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits))) 
                                          | ((0x1008U 
                                              == (0x3058U 
                                                  & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__exp_io_out_bits)) 
                                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_reg_fence) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_ctrl_decoder_14))))) 
                                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_csr_stall) 
                                         | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_reg_pause))))))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_2) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_4_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___s2_data_T_15 
        = ((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en) 
             & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way))
             ? (((QData)((IData)((((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7
                                    [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_7_rdata_data_addr_pipe_0] 
                                    << 0x18U) | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6
                                                 [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_6_rdata_data_addr_pipe_0] 
                                                 << 0x10U)) 
                                  | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5
                                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_5_rdata_data_addr_pipe_0] 
                                      << 8U) | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4
                                     [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_4_rdata_data_addr_pipe_0])))) 
                 << 0x20U) | (QData)((IData)((((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3
                                                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_3_rdata_data_addr_pipe_0] 
                                                << 0x18U) 
                                               | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2
                                                  [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_2_rdata_data_addr_pipe_0] 
                                                  << 0x10U)) 
                                              | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1
                                                  [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_1_rdata_data_addr_pipe_0] 
                                                  << 8U) 
                                                 | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0
                                                 [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_0_rdata_data_addr_pipe_0])))))
             : 0ULL) | (((((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en) 
                           & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way) 
                              >> 1U)) ? (((QData)((IData)(
                                                          (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15
                                                             [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_15_rdata_data_addr_pipe_0] 
                                                             << 0x18U) 
                                                            | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_14
                                                               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_14_rdata_data_addr_pipe_0] 
                                                               << 0x10U)) 
                                                           | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13
                                                               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_13_rdata_data_addr_pipe_0] 
                                                               << 8U) 
                                                              | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12
                                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_12_rdata_data_addr_pipe_0])))) 
                                          << 0x20U) 
                                         | (QData)((IData)(
                                                           (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11
                                                              [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_11_rdata_data_addr_pipe_0] 
                                                              << 0x18U) 
                                                             | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10
                                                                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_10_rdata_data_addr_pipe_0] 
                                                                << 0x10U)) 
                                                            | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9
                                                                [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_9_rdata_data_addr_pipe_0] 
                                                                << 8U) 
                                                               | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8
                                                               [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_8_rdata_data_addr_pipe_0])))))
                           : 0ULL) | (((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en) 
                                       & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way) 
                                          >> 2U)) ? 
                                      (((QData)((IData)(
                                                        (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23
                                                           [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_23_rdata_data_addr_pipe_0] 
                                                           << 0x18U) 
                                                          | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_22
                                                             [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_22_rdata_data_addr_pipe_0] 
                                                             << 0x10U)) 
                                                         | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21
                                                             [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_21_rdata_data_addr_pipe_0] 
                                                             << 8U) 
                                                            | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20
                                                            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_20_rdata_data_addr_pipe_0])))) 
                                        << 0x20U) | (QData)((IData)(
                                                                    (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19
                                                                       [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_19_rdata_data_addr_pipe_0] 
                                                                       << 0x18U) 
                                                                      | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18
                                                                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_18_rdata_data_addr_pipe_0] 
                                                                         << 0x10U)) 
                                                                     | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17
                                                                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_17_rdata_data_addr_pipe_0] 
                                                                         << 8U) 
                                                                        | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16
                                                                        [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_16_rdata_data_addr_pipe_0])))))
                                       : 0ULL)) | (
                                                   (((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en) 
                                                     & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way) 
                                                        >> 3U))
                                                     ? 
                                                    (((QData)((IData)(
                                                                      (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31
                                                                         [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_31_rdata_data_addr_pipe_0] 
                                                                         << 0x18U) 
                                                                        | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30
                                                                           [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_30_rdata_data_addr_pipe_0] 
                                                                           << 0x10U)) 
                                                                       | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29
                                                                           [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_29_rdata_data_addr_pipe_0] 
                                                                           << 8U) 
                                                                          | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28
                                                                          [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_28_rdata_data_addr_pipe_0])))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(
                                                                       (((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27
                                                                          [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_27_rdata_data_addr_pipe_0] 
                                                                          << 0x18U) 
                                                                         | (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26
                                                                            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_26_rdata_data_addr_pipe_0] 
                                                                            << 0x10U)) 
                                                                        | ((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25
                                                                            [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_25_rdata_data_addr_pipe_0] 
                                                                            << 8U) 
                                                                           | vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24
                                                                           [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_24_rdata_data_addr_pipe_0])))))
                                                     : 0ULL) 
                                                   | (((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_word_en) 
                                                       & ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_data_way) 
                                                          >> 4U))
                                                       ? 
                                                      vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__ram_data
                                                      [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_d_q__DOT__value_1]
                                                       : 0ULL))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_a_bits_param 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_bits_param)
            : 0U);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_a_bits_opcode 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_bits_opcode)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1)
                       ? 4U : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_a_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_bits_size)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1)
                       ? 6U : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_a_bits_source 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_bits_source)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1)
                       ? 2U : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_out_a_bits_address 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_a_bits_address
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__muxStateEarly_1)
                       ? (0xffffffc0U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__refill_paddr)
                       : 0U));
    if (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_62) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_180 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__cached_grant_wait) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_pma_cacheable));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_168 
            = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_pma_cacheable)) 
                     | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__uncachedInFlight_0)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_180 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__cached_grant_wait;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_168 
            = (1U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__uncachedInFlight_0));
    }
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_38 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_read) 
               & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore1_valid_likely) 
                   & (((0x1ffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore1_addr 
                                          >> 3U))) 
                       == (0x1ffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_addr 
                                             >> 3U)))) 
                      & (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore1_mask) 
                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_mask_xwr))))) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_valid) 
                     & (((0x1ffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__pstore2_addr 
                                            >> 3U))) 
                         == (0x1ffU & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_addr 
                                               >> 3U)))) 
                        & (0U != ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__mask) 
                                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_mask_xwr)))))))) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_s2_nack) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_2_valid) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid) 
                    & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_cmd_uses_tlb) 
                       & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__resp_valid_0) 
                          | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__tlb_miss) 
                             | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__multipleHits))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_requestor_1_s2_nack 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_s2_nack) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb__DOT__s2_id));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full) 
           & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_ar_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_ar_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___GEN_15));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__maybe_full)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_ar_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_aw_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_aw_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___GEN_95));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4index_auto_out_aw_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4 
        = (7U & (~ (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_4) 
                     >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_4))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3 
        = (7U & (~ (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_3) 
                     >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_unready_3))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_28 
        = ((0xff00ff00ff00ffULL & (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_18 
                                   >> 8U)) | (0xff00ff00ff00ff00ULL 
                                              & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_18, 8U)));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_6 
        = (0x1fU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_3) 
                    | VL_SHIFTL_III(5,5,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT___readys_mask_T_3), 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__monitor__DOT__d_first_done 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__maybe_full));
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
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_deq_valid) 
           & ((4U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_deq_bits_opcode)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_d_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_enq_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater__DOT__full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_enq_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater__DOT__full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_13 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_deq_valid) 
           & ((4U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_deq_bits_opcode)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_d_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__o_data__DOT__ram_mask_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__o_data_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_1) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_in_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter_2)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_in_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__o_data__DOT__ram_mask_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__o_data_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_1) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_in_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter_2)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_in_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__o_data__DOT__ram_mask_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__o_data_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_1) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_in_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter_2)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_in_a_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__o_data__DOT__ram_mask_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__o_data_io_enq_ready) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_1) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_in_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_in_a_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter_2)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_in_a_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr 
        = (((IData)((0U != (3U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_499) 
                                  >> 2U)))) << 1U) 
           | (IData)((0U != (0xaU & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___T_499)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter_2)) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_19)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_18) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_19));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79))
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_15) 
           & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
                  >> 2U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_12)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_15) 
           & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_bits_opcode) 
               >> 2U) | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__doneAW)) 
                         & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_2 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_16 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_2) 
                     - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_a_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_allow));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_imem_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_stalld)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT____VdfgRegularize_h1e19e3de_0_0) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nICReady) 
                  >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT__nIC)) 
                 | (1U >= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___io_imem_ready_T_4)))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_b_ready 
        = (1U & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__block_probe_for_core_progress) 
                     | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__releaseInFlight) 
                         | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_ack_wait) 
                             & (0U == (0x7fffU & ((
                                                   vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__ram_address
                                                   [vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q__DOT__value_1] 
                                                   ^ vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_ack_addr) 
                                                  >> 6U)))) 
                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__grantInProgress))) 
                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_65)))) 
                 & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_0))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_299 
        = ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_0)
                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_284)
                : 0U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_284));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_0) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_in_6_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_nack 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_probe)
                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_prb_ack_data) 
                     | (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__releaseDone)) 
                         | (0U < (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_probe_state_state))) 
                        | (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_38)))
                  : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_38)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_flush_icache 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_valid) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_requestor_1_s2_nack)) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_fence_i)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__replay_wb_common 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_requestor_1_s2_nack) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_replay));
    TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT____VdfgRegularize_h93dec8dc_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_ar_valid));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_ar_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ram_tl_state_size_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
              & ((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 7U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size_MPORT_en 
        = (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 8U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 9U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xaU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xbU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ram_tl_state_size_MPORT_en 
        = (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12_io_enq_ready) 
                   & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                      & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                         >> 0xcU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ram_tl_state_size_MPORT_en 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13_io_enq_ready) 
                 & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xdU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ram_tl_state_size_MPORT_en 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14_io_enq_ready) 
                 & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xeU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ram_tl_state_size_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15_io_enq_ready) 
            & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_7_0)) 
           & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
              >> 0xfU));
    TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT____VdfgRegularize_h93dec8dc_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_aw_valid));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_aw_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ram_tl_state_size_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
              & ((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                         & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 4U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ram_tl_state_size_MPORT_en 
        = (0x7ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ram_tl_state_size_MPORT_en 
        = (0x3ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 6U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ram_tl_state_size_MPORT_en 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23_io_enq_ready) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                        & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                           >> 7U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ram_tl_state_size_MPORT_en 
        = (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 8U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 9U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xaU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27_io_enq_ready) 
                    & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                       & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                          >> 0xbU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__ram_tl_state_size_MPORT_en 
        = (0xfU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28_io_enq_ready) 
                   & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                      & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                         >> 0xcU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__ram_tl_state_size_MPORT_en 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29_io_enq_ready) 
                 & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xdU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__ram_tl_state_size_MPORT_en 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30_io_enq_ready) 
                 & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0) 
                    & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
                       >> 0xeU))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__ram_tl_state_size_MPORT_en 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31_io_enq_ready) 
            & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_2_0)) 
           & (((IData)(1U) << (0xfU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))) 
              >> 0xfU));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_2 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
            >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_1_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_0 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F1_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_1 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_1_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_filter_lo_3));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestDOI_0_0) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
               & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))
                   ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3)
                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0)))) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestDOI_0_1) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))
                     ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4)
                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_2 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
            >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_2_0_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_0 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered___05F0_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_1 
        = (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
            >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__portsDIO_filtered_1_0_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready 
        = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_source) 
                >> 4U)) & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
                           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))
                               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
                                  >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_1)))) 
           | (IData)((((0x10U == (0x1cU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_source))) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready)) 
                      & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))
                          ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
                             >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_1)))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready 
        = (((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_source) 
                >> 4U)) & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_d_ready) 
                           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))
                               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_3) 
                                  >> 2U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_2)))) 
           | (IData)((((0x10U == (0x1cU & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_source))) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_d_ready)) 
                      & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))
                          ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_4) 
                             >> 2U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_2)))));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_38 
        = ((0xf0f0f0f0f0f0f0fULL & (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_28 
                                    >> 4U)) | (0xf0f0f0f0f0f0f0f0ULL 
                                               & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_28, 4U)));
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
    TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__monitor__DOT__d_first_done) 
           & vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_read
           [0U]);
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_13 
        = ((~ vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_read
            [0U]) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__monitor__DOT__d_first_done));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__d_first 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__d_first_counter)) 
           & (6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_d_bits_opcode)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_272, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_104 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_272[3U] >> 0xeU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_273, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_200 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_273[3U] >> 0xaU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_274, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_410 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_274[3U] >> 0xdU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_275, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_491 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_275[3U] >> 9U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_276, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_731 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_276[3U] >> 0xcU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_277, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_811 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_277[3U] >> 0x10U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                                >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_278, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_931 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_278[3U] >> 8U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_279, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_1067 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_279[3U] >> 0xbU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_280, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_wivalid_1_1139 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_280[3U] >> 0xfU)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                               >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_281, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_527 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & __Vtemp_281[1U]) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                     >> 0xbU)));
    VL_SHIFTL_WWI(256,256,8, __Vtemp_282, VTestHarness__ConstPool__CONST_h4e9f510d_0, 
                  (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                            >> 3U)));
    TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345 
        = (((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT____VdfgRegularize_h8dc8acdf_2_302) 
            & (__Vtemp_282[1U] >> 1U)) & (~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter_auto_out_a_bits_address) 
                                             >> 0xbU)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__wrapped_error_device__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_0)) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_plic__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
              | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_2) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
                 | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_3) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_debug__DOT__fragmenter__DOT__repeater_io_enq_ready)) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar__DOT__requestAIO_0_4) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_bootrom__DOT__fragmenter__DOT__repeater_io_enq_ready))))));
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_13) 
                 & (IData)(((0U == (0x3ff8U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address)) 
                            & (((IData)(1U) << (3U 
                                                & (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address 
                                                   >> 0xeU))) 
                               >> 1U)))));
    TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_8 
        = (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_13) 
                 & (IData)(((0x3ff8U == (0x3ff8U & vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address)) 
                            & (((IData)(1U) << (3U 
                                                & (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__coupler_to_clint__DOT__fragmenter_auto_out_a_bits_address 
                                                   >> 0xeU))) 
                               >> 2U)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__sent_d));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_1 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2)
            ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_95)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__got_e));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___GEN_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__sent_d));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___GEN_1 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___GEN_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2)
            ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_95)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__got_e));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___GEN_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__sent_d));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___GEN_1 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___GEN_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2)
            ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_95)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__got_e));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_0 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__sent_d));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_1 
        = ((~ (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__shared));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2)
            ? (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_95)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__got_e));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch_1 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_1)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_10 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_1) 
                     - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_a_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en 
        = ((~ (IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20)) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq_io_enq_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full)
            ? (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)
            : ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready)) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___readys_T 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid) 
            << 1U) | (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_imem_ready) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_4 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_0) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_1) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_1 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_2) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_2 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_3) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_3));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_3 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_4) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_4));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_4 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_4)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_0)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_1 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_1)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_2 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_2)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__wen_3 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_3)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_3));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__monitor__DOT__b_first_done 
        = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_b_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_in_0_b_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__monitor__DOT__b_first_done 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleIn_0_b_q_io_deq_valid) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar__DOT__requestBOI_0_0) 
              & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_auto_out_b_ready)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_303 
        = ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__releaseDone)
                ? 0U : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_299))
            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_299));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_1) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid_not_nacked 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_nack)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_32 
        = ((~ ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state)) 
               & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__resp_valid_0)) 
                  & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_phys))))) 
           & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb__DOT____VdfgRegularize_h4b4ef710_0_1)) 
              & ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__dataArb__DOT____VdfgRegularize_hf924e94e_0_1) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s0_read))) 
                 & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state)) 
                    & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__cached_grant_wait)) 
                       & (~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_nack)))))));
    __VdfgRegularize_hd87f99a1_1_180 = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__replay_wb_common) 
                                        | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_exception));
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en 
            = TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT____VdfgRegularize_h93dec8dc_0_0;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__ram_id_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_ready)) 
               & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT____VdfgRegularize_h93dec8dc_0_0));
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq__DOT__do_deq = 0U;
    }
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_io_deq_valid));
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en 
            = TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT____VdfgRegularize_h93dec8dc_0_0;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_ready) 
               & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__ram_id_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_ready)) 
               & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT____VdfgRegularize_h93dec8dc_0_0));
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1__DOT__do_deq = 0U;
    }
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___GEN_9 
        = (0x1ffU & (((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_aw_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_valid))
                      ? ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__len_1) 
                         - (IData)(1U)) : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__r_len_1)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_aw_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_0));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__wbeats_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__wbeats_latched)) 
           & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__deq_1_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_26 
        = (7U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23) 
                 | VL_SHIFTL_III(3,3,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_23), 1U)));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_4))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_4_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_4_1;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_18 
        = (7U & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15) 
                 | VL_SHIFTL_III(3,3,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___readys_mask_T_15), 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_d_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_d_ready) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__d_drop));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_3))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__earlyWinner_3_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_3_1;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__latch 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__monitor__DOT____VdfgRegularize_h9d8fea46_0_5 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_c_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_11) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_2)
               ? ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready) 
                  & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft))
                      ? (~ (3U & VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T), 1U)))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state___05F0)))
               : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_a_ready) 
                  & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft_1))
                      ? (~ (0x1fU & VL_SHIFTL_III(5,5,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T_16), 1U)))
                      : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state_1_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__out_1_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_d_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft))
               ? (~ (1U & (VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___readys_T), 1U) 
                           >> 1U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__state___05F1)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT____VdfgRegularize_hf19bc0bf_0_4 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_out_b_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4index_auto_out_r_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_48 
        = ((0x3333333333333333ULL & (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_38 
                                     >> 2U)) | (0xccccccccccccccccULL 
                                                & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_38, 2U)));
    vlSelfRef.TestHarness__DOT__SimDTM_debug_req_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_0) 
            & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready)) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar__DOT__requestAIO_0_1) 
              & (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_1_d_ready)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__a_first_done 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar_auto_in_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiXbar_auto_out_0_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT___claimedDevs_T 
        = (0xfU & ((IData)(1U) << ((((IData)(TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0) 
                                     & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_11) 
                                        & (0U != vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_14)))
                                     ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_0)
                                     : 0U) | (((IData)(TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_0) 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_12) 
                                                  & (0U 
                                                     != vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_14)))
                                               ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__maxDevs_1)
                                               : 0U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_11 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_13) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_12));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_14 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_13) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_11));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_405 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_527) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_449))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__goReg));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_631 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_527) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_448));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_449 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_449));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_448 
        = ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_woready_1_345) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_womask_448));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_1) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__out_xbar_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_1 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_2));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_3 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_4 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_5 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_5));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_6 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_6));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_7 
        = ((IData)(TestHarness__DOT__ldut__DOT__clint__DOT__out_woready_0) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_womask_7));
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
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en 
            = TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__do_deq = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT__ram_data_MPORT_en 
            = ((IData)(vlSelfRef.__VdfgRegularize_hd87f99a1_1_20) 
               & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__deq__DOT____VdfgRegularize_ha23c470c_0_0));
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_2 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_1) 
                 + (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                    & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_14 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_4) 
                 + (0x1fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                              >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_18 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_5) 
                 + (0xfU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                             >> 4U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_2 
        = (0x3fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                     >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_1 
        = (0x7fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_enq_bits_id)) 
                     >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT____VdfgRegularize_h5a61dbbe_0_0)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq__DOT__maybe_full) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_ready) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_wen)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_valid 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__beatsLeft))
            ? ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state)) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid))
            : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_0) 
                & (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))) 
               | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_1) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_opcode_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__earlyWinner_0 
        = ((~ (3U & VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___readys_T), 1U))) 
           & (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__earlyWinner_1 
        = ((~ (1U & (VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___readys_T), 1U) 
                     >> 1U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid));
    if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__beatsLeft))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__earlyWinner_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__earlyWinner_1;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_1;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__out_1_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
           & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__beatsLeft))
               ? (~ (1U & (VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___readys_T), 1U) 
                           >> 1U))) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_1)));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_313 
        = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__releaseDone)
                ? 7U : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_303))
            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_303));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tag_array_0_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_write) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s0_clk_en 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_bits_write)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__metaArb_io_out_valid));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_46 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid_not_nacked) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_flush_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_req_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_48)
            ? ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__tlMasterXbar_auto_in_0_d_valid)) 
               & (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_32))
            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_32));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_retire 
        = ((~ (IData)(__VdfgRegularize_hd87f99a1_1_180)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__take_pc_wb 
        = ((IData)(__VdfgRegularize_hd87f99a1_1_180) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_eret) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_flush_pipe)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___GEN_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en)
                      ? ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__len) 
                         - (IData)(1U)) : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__r_len)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_aw_valid));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__w_todo 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__w_counter))
            ? ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__wbeats_valid)
                ? 1U : 0U) : (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__w_counter));
    TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_1 
        = ((0U != (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__w_counter)) 
           | (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__wbeats_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_sink 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__out_2_0_d_bits_sink)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_sink)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_param 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_param)
                       : 0U));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_d_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_size
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_size)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_2)
                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_size)
                                  : 0U)));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_246 = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_4_0)
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_sink 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__out_2_0_d_bits_sink)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_sink)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_param 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__ram_param
            [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleIn_0_d_q__DOT__value_1]
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_param)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_denied 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_denied)) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_denied)) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_d_bits_denied))));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_d_bits_opcode)
             : 0U) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_1)
                        ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_d_bits_opcode)
                        : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__muxStateEarly_3_2)
                                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)
                                      ? 1U : 0U) : 0U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___beatsLeft_T_4 
        = (7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__beatsLeft) 
                 - (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__monitor__DOT____VdfgRegularize_h9d8fea46_0_5)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_c_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_c_valid) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_c_ready));
    vlSelfRef.__VdfgRegularize_hd87f99a1_1_219 = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__out_1_ready) 
                                                   & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__out_1_earlyValid)) 
                                                  & (((~ 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_d_bits_source) 
                                                        >> 6U)) 
                                                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT__d_first_beats1_opdata)) 
                                                     & ((1U 
                                                         == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__counter)) 
                                                        | (0U 
                                                           == 
                                                           ((1U 
                                                             & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__out_1_bits_opcode))
                                                             ? 
                                                            (7U 
                                                             & (~ 
                                                                (7U 
                                                                 & (((IData)(0x3fU) 
                                                                     << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_d_bits_size)) 
                                                                    >> 3U))))
                                                             : 0U)))));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__out_1_ready) 
           | (1U == (3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_d_bits_source) 
                           >> 5U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT__d_first_beats1_opdata)) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__monitor__DOT____VdfgRegularize_hf19bc0bf_0_4));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank_auto_out_b_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4index_auto_out_r_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__locked));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__out 
        = (((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)) 
            | (0xaU == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)))
            ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu_io_adder_out
            : ((QData)((IData)(((0xcU <= (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)) 
                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__slt)))) 
               | (((((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)) 
                     | (6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)))
                     ? vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__in1_xor_in2
                     : 0ULL) | (((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)) 
                                 | (7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn)))
                                 ? (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu_io_in1 
                                    & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu_io_in2)
                                 : 0ULL)) | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT____VdfgRegularize_hca53fb73_0_3)
                                               ? TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT__shout_r
                                               : 0ULL) 
                                             | ((1U 
                                                 == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_alu_fn))
                                                 ? 
                                                ((0x5555555555555555ULL 
                                                  & (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_48 
                                                     >> 1U)) 
                                                 | (0xaaaaaaaaaaaaaaaaULL 
                                                    & VL_SHIFTL_QQI(64,64,32, TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__alu__DOT___shout_l_T_48, 1U)))
                                                 : 0ULL)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__next_flight 
        = (3U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__flight) 
                  + ((IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo) 
                     + VL_SHIFTR_III(2,2,32, ((((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__counter)) 
                                                & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__a_first_done)) 
                                               << 1U) 
                                              | (IData)(TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__inc_lo)), 1U))) 
                 - ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done) 
                    + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmOuter__DOT__dmiBypass__DOT__bar__DOT__monitor__DOT__d_first_done), 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_4 
        = (7U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_14) 
                  & ((0xffffffffU == vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_14) 
                     & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__enables_0_0) 
                         << 1U) >> (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                                                  [0U] 
                                                  >> 0x20U)))))) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_woready_11) 
                    & ((0xffffffffU == vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT____VdfgRegularize_ha6a15a5a_2_14) 
                       & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__enables_1_0) 
                           << 1U) >> (3U & (IData)(
                                                   (vlSelfRef.TestHarness__DOT__ldut__DOT__plicDomainWrapper__DOT__plic__DOT__out_back__DOT__ram_data
                                                    [0U] 
                                                    >> 0x20U))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT___GEN_2114 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_449)
            ? 0U : (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__goReg)) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__out_f_woready_631))
                     ? 0U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__debug_1__DOT__dmInner__DOT__dmInner__DOT__ctrlStateReg)));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT___timecmp_0_T 
        = (((QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_7)
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_7)
                                 : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                            >> 0x38U))) 
                               << 0x18U) | (0xff0000U 
                                            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_6)
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_8)
                                                 : (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                            >> 0x30U))) 
                                               << 0x10U))) 
                             | ((0xff00U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_5)
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_5)
                                              : (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                         >> 0x28U))) 
                                            << 8U)) 
                                | (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_4)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_6)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                        >> 0x20U)))))))) 
            << 0x20U) | (QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_3)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_3)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                        >> 0x18U))) 
                                           << 0x18U) 
                                          | (0xff0000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_2)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_4)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                             >> 0x10U))) 
                                                << 0x10U))) 
                                         | ((0xff00U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_1)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_1)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0 
                                                             >> 8U))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_2)
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__timecmp_0))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT___time_T_2 
        = (((QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_15)
                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_7)
                                 : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                            >> 0x38U))) 
                               << 0x18U) | (0xff0000U 
                                            & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_14)
                                                 ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_8)
                                                 : (IData)(
                                                           (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                            >> 0x30U))) 
                                               << 0x10U))) 
                             | ((0xff00U & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_13)
                                              ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_5)
                                              : (IData)(
                                                        (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                         >> 0x28U))) 
                                            << 8U)) 
                                | (0xffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_12)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_6)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                        >> 0x20U)))))))) 
            << 0x20U) | (QData)((IData)((((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_11)
                                             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_3)
                                             : (IData)(
                                                       (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                        >> 0x18U))) 
                                           << 0x18U) 
                                          | (0xff0000U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_10)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_4)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                             >> 0x10U))) 
                                                << 0x10U))) 
                                         | ((0xff00U 
                                             & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_9)
                                                  ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_1)
                                                  : (IData)(
                                                            (vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_ 
                                                             >> 8U))) 
                                                << 8U)) 
                                            | (0xffU 
                                               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__out_f_woready_8)
                                                   ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT____VdfgRegularize_h18e761f9_0_2)
                                                   : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__clint__DOT__time_))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_79)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_aw_deq_io_enq_ready) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_aw_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq__DOT__ram_id_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid) 
              & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___GEN_15)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_6_0 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleOut_0_ar_deq_io_enq_ready) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_out_ar_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___beatsLeft_T_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__beatsLeft) 
                     - (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_opcode_MPORT_en)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_23 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__out_1_ready) 
            & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_isSupported)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__source_i_valid)))
            ? ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))
                ? 3U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__out_1_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_allow));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_322 
        = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__release_state))
            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__releaseDone)
                ? 7U : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_313))
            : (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_313));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_meta_clk_en 
        = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_46) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_probe));
    if (TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT____VdfgRegularize_hc4d58fb9_1_46) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_60 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_cmd;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_59 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_tag;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_61 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_size;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_62 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_signed;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_58 
            = (QData)((IData)(((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_paddr_hi 
                                << 0xcU) | (0xfffU 
                                            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_addr)))));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_60 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_cmd;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_59 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_tag;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_61 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_size;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_62 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_signed;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT___GEN_58 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_addr;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state_barrier_io_x 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb__DOT__s2_id)) 
            & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_s2_nack))
            ? 1U : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__mem_resp_valid)
                     ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__traverse)
                         ? 1U : 0U) : ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                        ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT____VdfgRegularize_h25d95197_1_22)
                                            ? (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_valid) 
                                                | (1U 
                                                   == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state)))
                                                ? 1U
                                                : 0U)
                                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                        : ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                            ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__pte_cache_hit)
                                                ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state)
                                                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_req_ready)
                                                    ? 2U
                                                    : 1U))
                                            : ((2U 
                                                == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                                ? 4U
                                                : (
                                                   (4U 
                                                    == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                                    ? 
                                                   ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_s2_xcpt_ae_ld)
                                                     ? 0U
                                                     : 5U)
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))
                                                     ? 0U
                                                     : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state))))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_requestor_1_req_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_mem_req_bits_phys)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache_io_cpu_req_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___id_stall_fpu_T_5 
        = (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_stall_fpu___05Fr 
           | (((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_dcache_miss) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_wfd)) 
                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt_io_sboard_set)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_retire))
               ? ((IData)(1U) << (0x1fU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_inst 
                                           >> 7U)))
               : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__nextSmall 
        = (0x7fU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_lo) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_retire)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_wen 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_retire) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_ctrl_wxd));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_bht_update_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__take_pc_wb)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__take_pc_wb) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_bht_update_bits_mispredict) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_sfence))));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf__DOT___GEN_70 = 0U;
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_21 
            = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0)
                ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__monitor_1__DOT__b_first_done)
                    ? ((~ ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG) 
                               << 1U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG))
                    : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__REG)));
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
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killm 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__dcache_kill_mem) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__take_pc_wb) 
                    | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_valid)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_reg_xcpt)))));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_w_deq__DOT__ram_data_MPORT_en 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_w_deq_io_enq_ready) 
           & ((IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid) 
              & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_1)));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleOut_0_w_deq_io_enq_ready) 
           & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT____VdfgRegularize_h55402cce_5_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__d_first_counter)) 
           & (6U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_d_bits_opcode)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_c_q__DOT__do_deq) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_11));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT____VdfgRegularize_h3b583b83_0_2 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_d_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_b_ready 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT__d_first_beats1_opdata)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_r_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__widget_auto_out_d_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT__d_first_beats1_opdata));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_12 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_3) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_2)) 
                   - (0x3fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___count_T_8 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__count_2) 
                    + (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__inc_1)) 
                   - (0x7fU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__d_sel_shiftAmount)) 
                                >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h4906b29d_2_18)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 3U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
               >> 4U)) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__do_deq 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
            & ((IData)(1U) << vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id
               [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1])) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
                 >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq) 
              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___bsel_T) 
                 >> 2U)));
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___GEN_42 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last;
        TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready 
            = (1U & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT___GEN_42 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__r_first;
        TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready = 0U;
    }
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready 
        = (0x7fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready 
        = (0x3fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready 
        = (0x1fffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                       >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready 
        = (0xfffU & ((((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__deq_id)) 
                      >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4)));
    TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_2 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__a_first_counter)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ram_tl_state_size_MPORT_en 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full)) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
              & ((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ram_tl_state_size_MPORT_en 
        = (0x7fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_6_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 1U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ram_tl_state_size_MPORT_en 
        = (0x3fffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_7_io_enq_ready) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 2U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ram_tl_state_size_MPORT_en 
        = (0x1fffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full)) 
                      & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                         & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                            >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ram_tl_state_size_MPORT_en 
        = (0xfffU & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full)) 
                     & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT____VdfgRegularize_h60d1478f_2_0) 
                        & (((IData)(1U) << (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4__DOT__queue_arw_deq_io_deq_bits_id)) 
                           >> 4U))));
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
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__a_isSupported) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_opcode 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_opcode;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_param 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_param;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_opcode = 4U;
            vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_param = 0U;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_opcode = 0U;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_param = 0U;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_size 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_size)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_size)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_source 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0)
             ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_source)
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1)
                       ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_source)
                       : 0U));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics_auto_out_a_bits_address 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_0)
             ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_a_0_bits_address
             : 0U) | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__muxStateEarly_1)
                       ? vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_bits_address
                       : 0U));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_25 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q_io_enq_ready) 
            & (((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__beatsLeft))
                 ? (~ (3U & VL_SHIFTL_III(2,2,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___readys_T), 1U)))
                 : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__state_0)) 
               & (2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))))
            ? ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT__cam_s_0_state))
                ? 1U : (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_23))
            : (IData)(TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__atomics__DOT___GEN_23));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__latch 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT___beatsLeft_T_4 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft) 
                     - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready) 
                        & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_out_a_valid))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestAIO_1_0) 
            & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready) 
               & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft))
                   ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys) 
                      >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state___05F1)))) 
           | (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestAIO_1_1) 
               & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_in_a_ready) 
                  & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_1))
                      ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_1) 
                         >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_1_1)))) 
              | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestAIO_1_2) 
                 & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__tl2axi4_auto_in_a_ready) 
                    & ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__beatsLeft_2))
                        ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__readys_readys_2) 
                           >> 1U) : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__state_2_1))))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar__DOT__requestAIO_0_0) 
            & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_cbus__DOT__widget_auto_in_a_ready) 
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__replay_ex 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_replay) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_valid) 
              & (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb_io_requestor_1_req_ready)) 
                  & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_mem)) 
                 | (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__div__DOT__state)) 
                     & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_ctrl_div)) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_dcache_miss) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_load_use))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___id_stall_fpu_T_11 
        = ((((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__dmem_resp_replay) 
             & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_tag) 
                >> 1U)) ? (~ ((IData)(1U) << (0x1fU 
                                              & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s2_req_tag) 
                                                 >> 2U))))
             : 0xffffffffU) & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___id_stall_fpu_T_5);
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT___GEN_1 
        = (0x3ffffffffffffffULL & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_hi 
                                   + (QData)((IData)(
                                                     ((~ 
                                                       ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit) 
                                                        >> 2U)) 
                                                      & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__nextSmall) 
                                                         >> 6U))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_58 
        = (QData)((IData)(((4U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_mcountinhibit))
                            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__value_lo)
                            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__nextSmall))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf_wen 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_wen) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ll_wen));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_btb_update_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_bht_update_valid) 
           & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_bht_update_bits_mispredict) 
              & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_btb_update_bits_isValid)) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT____VdfgRegularize_ha780a2de_2_83) 
                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT___io_imem_btb_update_bits_cfiType_T)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq_reset 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__subsystem_sbus_clock_groups_auto_out_3_member_subsystem_l2_1_reset));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_redirect 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_btb_taken)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken)
                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT____VdfgRegularize_h8010c0ff_0_0) 
                   | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid))
                : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killd 
        = (1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_valid)) 
                 | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ibuf_io_inst_0_bits_replay) 
                    | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
                       | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_stalld) 
                          | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr_io_interrupt))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache_io_req_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s0_fq_has_space));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killm 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killm) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_xcpt) 
              | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__fpu_kill_mem)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__killm 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killm) 
           | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt_io_nack_mem));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid_masked 
        = ((~ ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcacheArb__DOT__s1_id)
                ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killm) 
                   | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__mem_ldst_xcpt) 
                      | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__fpu_kill_mem)))
                : (2U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__state)))) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid));
    if (vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__maybe_full) {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__ram_data_MPORT_en 
            = TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0;
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__do_deq 
            = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready) 
               & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_valid));
    } else {
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__ram_data_MPORT_en 
            = ((~ (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq_io_deq_ready)) 
               & (IData)(TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT____VdfgRegularize_ha23c470c_0_0));
        vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT__in_w_deq__DOT__do_deq = 0U;
    }
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probenack 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_5));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probenack 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_6));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probenack 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_7));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probenack 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_21) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_8));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT____VdfgRegularize_h39034418_5_1 
        = (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT__d_first_beats1_opdata)) 
            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last)) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT____VdfgRegularize_h3b583b83_0_2));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__fixer__DOT__monitor__DOT____VdfgRegularize_h3b583b83_0_2) 
           & (0x20U == (0x60U & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4_auto_in_d_bits_source))));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready 
        = (1U & ((~ vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_echo_real_last
                  [vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1]) 
                 | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_b_ready)));
    TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_b_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_b_valid));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_out_r_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0__DOT__ptr_match))) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count) 
                    + ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_22) 
                       & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21))) 
                   - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_0_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1__DOT__ptr_match))) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_1 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_1) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21))) 
                   - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_1_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2__DOT__ptr_match))) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_2 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_2) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21))) 
                   - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_2_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3__DOT__ptr_match))) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_3 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_3) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21))) 
                   - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_3_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4__DOT__ptr_match))) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_4 
        = (0xfU & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_count_4) 
                    + (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4yank__DOT___rsel_T) 
                        >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_21))) 
                   - ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__qs_queue_4_io_deq_ready) 
                      & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint_auto_in_r_bits_last))));
    if (TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT____VdfgRegularize_h491beaf3_0_2) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_21 
            = ((0U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_0));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_22 
            = ((1U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_1));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_23 
            = ((2U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_2));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_24 
            = ((3U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_3));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_25 
            = ((4U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_4));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_26 
            = ((5U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_5));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_27 
            = ((6U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_6));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_28 
            = ((7U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_7));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_29 
            = ((8U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_8));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_30 
            = ((9U == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_9));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_31 
            = ((0xaU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_10));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_32 
            = ((0xbU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_11));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_33 
            = ((0xcU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_12));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_34 
            = ((0xdU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_13));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_35 
            = ((0xeU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_14));
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_36 
            = ((0xfU == vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__ram_source
                [vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__value_1]) 
               | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_15));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_21 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_22 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_23 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_24 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_25 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_4;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_26 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_5;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_27 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_6;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_28 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_7;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_29 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_8;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_30 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_9;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_31 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_10;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_32 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_11;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_33 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_12;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_34 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_13;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_35 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_14;
        vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT___GEN_36 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_cbus__DOT__fixer__DOT__flight_15;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__buffer_1__DOT__bundleOut_0_a_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer_auto_out_1_a_valid) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_1_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_a_ready 
        = ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__system_bus_xbar_auto_in_0_a_ready) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_3));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killx 
        = (1U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_req_valid) 
                 | ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ex_reg_valid)) 
                    | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__replay_ex))));
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
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__btb_io_btb_update_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_btb_update_valid)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_imem_btb_update_valid)
            : ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_14) 
               & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__fq__DOT__valid_1)) 
                  & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_taken)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_10)
                      : (((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_btb_resp_valid)) 
                          & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictBranch_1) 
                              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__s2_btb_resp_bits_bht_value)) 
                             | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictJump_1) 
                                | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__taken_predictReturn_1)))) 
                         | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT____VdfgRegularize_h861801f5_1_10))))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__ctrl_killd)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__id_ctrl_decoder_1));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_valid 
        = ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache_io_req_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__data_arrays_0_0_MPORT_1_addr 
        = (0x1ffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__refill_one_beat)
                      ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT___mem_idx_T_1)
                      : (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                                 >> 3U))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb_io_req_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid_masked) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_cmd_uses_tlb));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb_io_sfence_valid 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_valid_masked) 
           & (0x14U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_req_cmd)));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probedack 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
           & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probedack 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
            >> 1U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probedack 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
            >> 2U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29));
    TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probedack 
        = (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT___GEN_1) 
            >> 3U) & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_2_29));
    vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq_io_deq_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag_auto_out_b_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_17__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 1U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_18__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_19__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 3U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_20__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 4U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_21__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 5U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_22__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 6U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_23__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 7U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_24__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 8U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_25__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 9U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_26__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xaU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_27__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xbU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_28__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xcU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_29__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xdU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_30__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xeU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_31__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4frag__DOT___T_22) 
                 >> 0xfU)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_16__DOT__ptr_match))) 
           & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT____VdfgRegularize_hb0a5bc62_6_15) 
              & ((IData)(1U) << vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__ram_id
                 [vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_b_deq__DOT__value_1])));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT___GEN_260 
        = ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq)
            ? (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last)
            : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__tl2axi4__DOT__r_first));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_1__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 1U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_2__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 2U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_3__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 3U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_4__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 4U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_5__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 5U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_6__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 6U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_7__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 7U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_8__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 8U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_9__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 9U) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_10__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xaU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_11__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xbU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_12__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xcU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_13__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xdU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_14__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xeU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility_15__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT___rsel_T) 
                  >> 0xfU) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__do_deq 
        = ((~ ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__maybe_full)) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank__DOT__QueueCompatibility__DOT__ptr_match))) 
           & ((IData)(vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__do_deq) 
              & (((IData)(1U) << vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__ram_id
                  [vlSelfRef.TestHarness__DOT__mem__DOT__axi4buf__DOT__bundleIn_0_r_deq__DOT__value_1]) 
                 & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_mbus__DOT__coupler_to_memory_controller_port_named_axi4__DOT__axi4yank_auto_in_r_bits_last))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_20 
        = ((((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_4)) 
             << 4U) | (((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_3)) 
                        << 3U) | ((0U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_2)) 
                                  << 2U))) | (((0U 
                                                != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next_1)) 
                                               << 1U) 
                                              | (0U 
                                                 != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__pending_next))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_out_a_valid) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_from_bus_named_subsystem_fbus__DOT__widget_auto_in_a_ready));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__killx 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core_io_fpu_killx) 
           | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__mem_reg_valid) 
              & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__fpuOpt__DOT__killm)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_ren 
        = ((~ (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                       >> 2U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_valid));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_ren_1 
        = ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend__DOT__icache__DOT__s0_valid) 
           & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__frontend_io_cpu_npc 
                      >> 2U)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_589 
        = (((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state)) 
            & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb_io_req_valid) 
               & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__tlb_miss)))
            ? 1U : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state));
    TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32 
        = (1U & (~ ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state)) 
                    | ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__state)) 
                       | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb_io_sfence_valid)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT___GEN_20 
        = (3U & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probedack) 
                  | (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probenack))
                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__count) 
                     - (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probedack) 
                         & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_io_probenack))
                         ? 2U : 1U)) : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0) 
                                         & ((IData)(1U) 
                                            << (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr)))
                                         ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                                         : ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT____VdfgRegularize_h4e8e2b51_0_2) 
                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker__DOT__count)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT___GEN_20 
        = (3U & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probedack) 
                  | (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probenack))
                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__count) 
                     - (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probedack) 
                         & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1_io_probenack))
                         ? 2U : 1U)) : ((7U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0) 
                                               & (((IData)(1U) 
                                                   << (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr)) 
                                                  >> 1U)))
                                         ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                                         : ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT____VdfgRegularize_h8efdf0ef_0_2) 
                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_1__DOT__count)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT___GEN_20 
        = (3U & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probedack) 
                  | (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probenack))
                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__count) 
                     - (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probedack) 
                         & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2_io_probenack))
                         ? 2U : 1U)) : ((3U & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0) 
                                               & (((IData)(1U) 
                                                   << (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr)) 
                                                  >> 2U)))
                                         ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                                         : ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT____VdfgRegularize_hbf6482b9_0_2) 
                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_2__DOT__count)))));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT___GEN_20 
        = (3U & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probedack) 
                  | (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probenack))
                  ? ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__count) 
                     - (((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probedack) 
                         & (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3_io_probenack))
                         ? 2U : 1U)) : (((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT____VdfgRegularize_h6f4cae8c_1_0) 
                                         & (((IData)(1U) 
                                             << (IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__BroadcastFilter_io_request_bits_mshr)) 
                                            >> 3U))
                                         ? (0x10U != (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_bus_named_subsystem_l2__DOT__widget_auto_out_a_bits_source))
                                         : ((IData)(TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT____VdfgRegularize_h8aa7e64b_0_2) 
                                            | (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_l2_wrapper__DOT__broadcast_1__DOT__TLBroadcastTracker_3__DOT__count)))));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2 
        = (0xffffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_20) 
                      | VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_20), 1U)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_2 
        = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT__a_first_counter)) 
           & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_fbus__DOT__buffer__DOT__bundleOut_0_a_q__DOT__do_deq));
    if ((2U > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__count))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_273 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_274 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_275 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_276 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_283 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_284 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_285 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_286 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_293 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_294 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_295 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_296 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_303 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_304 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_305 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_306 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_313 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_314 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_315 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_316 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_323 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_324 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_325 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_326 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_333 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_334 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_335 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_336 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_343 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_344 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_345 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_346 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
    } else {
        if ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_273 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_274 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_275 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_276 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_273 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_274 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_275 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_276 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_3;
        }
        if ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_283 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_284 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_285 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_286 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_283 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_284 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_285 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_286 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
        }
        if ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_293 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_294 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_295 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_296 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_293 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_294 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_295 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_296 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_3;
        }
        if ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_303 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_304 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_305 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_306 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_303 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_304 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_305 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_306 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_3;
        }
        if ((4U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_313 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_314 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_315 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_316 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_313 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_314 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_315 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_316 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_3;
        }
        if ((5U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_323 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_324 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_325 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_326 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_323 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_324 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_325 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_326 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_3;
        }
        if ((6U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_333 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_334 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_335 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_336 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_333 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_334 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_335 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_336 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_3;
        }
        if ((7U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__waddr))) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_343 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((0U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_0))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_344 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((1U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_1))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_345 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((2U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_2))));
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_346 
                = ((IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32) 
                   & ((3U == (3U & vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_refill_tag)) 
                      | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_sectored_hit) 
                         & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_3))));
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_343 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_344 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_345 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_346 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
        }
    }
    if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__resp_valid_0) {
        if (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw_io_requestor_0_resp_bits_homogeneous) {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_455 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__special_entry_valid_0;
            if ((2U > (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__ptw__DOT__count))) {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_459 
                    = ((0U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_0_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_463 
                    = ((1U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_1_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_467 
                    = ((2U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_2_valid_0));
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_471 
                    = ((3U == (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__r_superpage_repl_addr))
                        ? (IData)(TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32)
                        : (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_3_valid_0));
            } else {
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_459 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_0_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_463 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_1_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_467 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_2_valid_0;
                vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_471 
                    = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_3_valid_0;
            }
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_473 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_273;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_474 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_274;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_475 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_275;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_476 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_276;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_483 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_283;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_484 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_284;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_485 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_285;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_486 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_286;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_493 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_293;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_494 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_294;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_495 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_295;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_496 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_296;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_503 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_303;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_504 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_304;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_505 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_305;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_506 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_306;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_513 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_313;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_514 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_314;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_515 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_315;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_516 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_316;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_523 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_323;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_524 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_324;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_525 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_325;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_526 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_326;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_533 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_333;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_534 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_334;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_535 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_335;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_536 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_336;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_543 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_343;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_544 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_344;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_545 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_345;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_546 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_346;
        } else {
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_455 
                = TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_32;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_459 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_0_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_463 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_1_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_467 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_471 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_3_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_473 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_474 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_475 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_476 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_483 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_484 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_485 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_486 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_493 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_494 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_495 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_496 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_503 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_504 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_505 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_506 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_513 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_514 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_515 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_516 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_523 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_524 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_525 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_526 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_533 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_534 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_535 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_536 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_3;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_543 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_0;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_544 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_1;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_545 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_2;
            vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_546 
                = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
        }
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_455 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__special_entry_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_459 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_0_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_463 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_1_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_467 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_471 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__superpage_entries_3_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_473 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_474 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_475 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_476 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_0_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_483 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_484 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_485 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_486 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_1_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_493 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_494 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_495 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_496 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_2_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_503 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_504 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_505 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_506 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_3_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_513 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_514 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_515 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_516 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_4_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_523 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_524 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_525 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_526 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_5_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_533 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_534 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_535 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_536 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_6_valid_3;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_543 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_0;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_544 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_1;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_545 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_2;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_546 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT__sectored_entries_0_7_valid_3;
    }
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5 
        = (0xffffU & ((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2) 
                      | VL_SHIFTL_III(16,16,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_2), 2U)));
    if (TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__fixer__DOT____VdfgRegularize_h4b6161a1_34_2) {
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
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8 
        = (0xffffU & ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5) 
                      | VL_SHIFTL_III(16,16,32, (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_5), 4U)));
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_3 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_605 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_473));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_606 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_474));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_607 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_475));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_608 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_476));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_605 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_473;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_606 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_474;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_607 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_475;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_608 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_476;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_9 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_633 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_483));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_634 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_484));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_635 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_485));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_636 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_486));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_633 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_483;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_634 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_484;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_635 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_485;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_636 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_486;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_15 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_661 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_493));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_662 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_494));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_663 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_495));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_664 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_496));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_661 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_493;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_662 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_494;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_663 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_495;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_664 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_496;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_21 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_689 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_503));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_690 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_504));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_691 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_505));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_692 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_506));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_689 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_503;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_690 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_504;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_691 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_505;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_692 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_506;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_27 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_717 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_513));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_718 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_514));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_719 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_515));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_720 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_516));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_717 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_513;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_718 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_514;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_719 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_515;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_720 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_516;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_33 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_745 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_523));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_746 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_524));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_747 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_525));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_748 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_526));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_745 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_523;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_746 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_524;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_747 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_525;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_748 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_526;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_39 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_773 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_533));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_774 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_534));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_775 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_535));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_776 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_536));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_773 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_533;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_774 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_534;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_775 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_535;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_776 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_536;
    }
    if ((0U == (0x1ffffffU & (vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___sector_hits_T_45 
                              >> 2U)))) {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_801 
            = ((0U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_543));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_802 
            = ((1U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_544));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_803 
            = ((2U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_545));
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_804 
            = ((3U != (3U & (IData)((vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__s1_tlb_req_vaddr 
                                     >> 0xcU)))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_546));
    } else {
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_801 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_543;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_802 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_544;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_803 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_545;
        vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_804 
            = vlSelfRef.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tlb__DOT___GEN_546;
    }
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner 
        = ((~ (0x1fffeU & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8) 
                            | VL_SHIFTL_III(16,16,32, (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___winner_T_8), 8U)) 
                           << 1U))) & (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_20));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T 
        = (0xffffU & ((1U & (TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner 
                             >> 0x10U)) | TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__winner));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1 
        = (0xffU & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T) 
                     >> 8U) | (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T)));
    TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_2 
        = (0xfU & (((IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1) 
                    >> 4U) | (IData)(TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___deq_id_T_1)));
    vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT___GEN_1 
        = ((1U & ((~ (IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT__locked)) 
                  | ((IData)(vlSelfRef.TestHarness__DOT__ldut__DOT__subsystem_sbus__DOT__coupler_to_port_named_mmio_port_axi4__DOT__axi4deint__DOT____VdfgRegularize_h4fafcd4c_2_4) 
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
