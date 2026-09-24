// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VSodorFullChip.h for the primary calling header

#ifndef VERILATED_VSODORFULLCHIP___024ROOT_H_
#define VERILATED_VSODORFULLCHIP___024ROOT_H_  // guard

#include "verilated.h"


class VSodorFullChip__Syms;

class alignas(VL_CACHE_LINE_BYTES) VSodorFullChip___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clock,0,0);
        VL_IN8(reset,0,0);
        VL_IN8(io_host_valid,0,0);
        VL_IN8(io_host_write,0,0);
        VL_OUT8(io_host_ready,0,0);
        VL_OUT8(io_success,0,0);
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_dec_stall;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_exe_pc_sel;
        CData/*3:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_br_type;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_if_kill;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op1_sel;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_op2_sel;
        CData/*3:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_alu_fun;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_wb_sel;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_rf_wen;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_mem_val;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c_io_ctl_pipeline_kill;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_4;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_6;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT___csignals_T_782;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__cs0_7;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__dec_exception;
        CData/*4:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_wbaddr;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_exception;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_reg_is_csr;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__exe_inst_is_load;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_fencei_REG;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__c__DOT__io_ctl_mem_exception_REG;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_valid;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_valid;
        CData/*4:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_wbaddr;
        CData/*3:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_br_type;
        CData/*3:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_alu_fun;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_wb_sel;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_rf_wen;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_val;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_fcn;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_mem_typ;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_ctrl_csr_cmd;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_valid;
        CData/*4:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_wbaddr;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_rf_wen;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_val;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_fcn;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_mem_typ;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_wb_sel;
        CData/*2:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_ctrl_csr_cmd;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_valid;
        CData/*4:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbaddr;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_ctrl_rf_wen;
        CData/*1:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___GEN_91;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_0_0;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT____VdfgRegularize_h9e043280_3_9;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mpie;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mstatus_mie;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_mtip;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mip_msip;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_mtip;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mie_msip;
        CData/*5:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_;
        CData/*5:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_1;
        CData/*6:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__nextSmall_1;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_ebreakm;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dcsr_step;
    };
    struct {
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__wen;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__insn_ret;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_7;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_70;
        CData/*0:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT____VdfgRegularize_h94c28e87_0_80;
        CData/*0:0*/ SodorFullChip__DOT__memory__DOT__bytes_MPORT_4_en;
        CData/*2:0*/ SodorFullChip__DOT__memory__DOT__storeBytes;
        CData/*0:0*/ SodorFullChip__DOT__memory__DOT____VdfgRegularize_h1a45b6a8_0_3;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __VactContinue;
        SData/*15:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___T;
        VL_IN(io_host_addr,31,0);
        VL_IN(io_host_wdata,31,0);
        VL_OUT(io_host_rdata,31,0);
        VL_OUT(io_tohost,31,0);
        IData/*31:0*/ SodorFullChip__DOT__memory_io_core_0_resp_bits_data;
        IData/*31:0*/ SodorFullChip__DOT__regfile_io_rs2_data;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_reg_pc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_inst;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__dec_reg_pc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_inst;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_pc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_alu_op1;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__brjmp_offset;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_reg_rs2_data;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_pc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_inst;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_alu_out;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_reg_rs2_data;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__wb_reg_wbdata;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__if_pc_plus4;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__exe_adder_out;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___mem_wbdata_T_4;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__mem_wbdata;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___exe_alu_out_T_37;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT___dec_op2_data_T_18;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mepc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mcause;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mtval;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_mscratch;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_medeleg;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dpc;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__reg_dscratch;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_12;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___w_T_8;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mie_T_9;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dpc_T_8;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_dscratch_T_8;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mscratch_T_8;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___reg_mcause_T_11;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_36;
        IData/*31:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_37;
        VlWide<3>/*95:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_303;
        VlWide<3>/*89:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_304;
        VlWide<3>/*95:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_305;
        VlWide<3>/*89:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_306;
        IData/*31:0*/ __VactIterCount;
        QData/*57:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_;
        QData/*57:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_0;
        QData/*57:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__large_1;
        QData/*57:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_1;
    };
    struct {
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_2;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_3;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_4;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_5;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_6;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_7;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_8;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_9;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_10;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_11;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_12;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_13;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_14;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_15;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_16;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_17;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_18;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_19;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_20;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_21;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_22;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_23;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_24;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_25;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_26;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_27;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_28;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_29;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_30;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_31;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_32;
        QData/*39:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__small_33;
        QData/*34:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___new_mstatus_T_8;
        QData/*63:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_33;
        QData/*63:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT__w_34;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_107;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_108;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_109;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_110;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_111;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_112;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_113;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_114;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_115;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_116;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_117;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_118;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_119;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_120;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_121;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_122;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_123;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_124;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_125;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_126;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_127;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_128;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_129;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_130;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_131;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_132;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_133;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_134;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_135;
    };
    struct {
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_136;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_137;
        QData/*47:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_138;
        QData/*34:0*/ SodorFullChip__DOT__tile__DOT__core__DOT__d__DOT__csr__DOT___GEN_145;
        VlUnpacked<CData/*7:0*/, 2097152> SodorFullChip__DOT__memory__DOT__bytes;
        VlUnpacked<IData/*31:0*/, 32> SodorFullChip__DOT__regfile__DOT__regfile;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    VSodorFullChip__Syms* const vlSymsp;

    // CONSTRUCTORS
    VSodorFullChip___024root(VSodorFullChip__Syms* symsp, const char* v__name);
    ~VSodorFullChip___024root();
    VL_UNCOPYABLE(VSodorFullChip___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
