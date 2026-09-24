// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VTestHarness__pch.h"
#include "VTestHarness.h"
#include "VTestHarness___024root.h"
#include "VTestHarness___024unit.h"

// FUNCTIONS
VTestHarness__Syms::~VTestHarness__Syms()
{
}

VTestHarness__Syms::VTestHarness__Syms(VerilatedContext* contextp, const char* namep, VTestHarness* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP____024unit{this, Verilated::catName(namep, "$unit")}
{
        // Check resources
        Verilated::stackCheck(40513);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT____024unit = &TOP____024unit;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP____024unit.__Vconfigure(true);
    // Setup scopes
    __Vscope_TestHarness.configure(this, name(), "TestHarness", "TestHarness", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_TestHarness__SimDTM.configure(this, name(), "TestHarness.SimDTM", "SimDTM", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core.configure(this, name(), "TestHarness.ldut.tile_prci_domain.tile_reset_domain.tile.core", "core", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core__csr.configure(this, name(), "TestHarness.ldut.tile_prci_domain.tile_reset_domain.tile.core.csr", "csr", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_TestHarness__mem__srams.configure(this, name(), "TestHarness.mem.srams", "srams", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TestHarness.varInsert(__Vfinal,"SimDTM_debug_req_ready", &(TOP.TestHarness__DOT__SimDTM_debug_req_ready), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_TestHarness.varInsert(__Vfinal,"SimDTM_debug_resp_bits_data", &(TOP.TestHarness__DOT__SimDTM_debug_resp_bits_data), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TestHarness.varInsert(__Vfinal,"SimDTM_debug_resp_bits_resp", &(TOP.TestHarness__DOT__SimDTM_debug_resp_bits_resp), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_TestHarness.varInsert(__Vfinal,"SimDTM_debug_resp_valid", &(TOP.TestHarness__DOT__SimDTM_debug_resp_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"debug_req_bits_addr_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,6,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"debug_req_bits_data_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"debug_req_bits_op_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,1,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"debug_req_valid_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"debug_resp_ready_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_TestHarness__SimDTM.varInsert(__Vfinal,"exit_reg", &(TOP.TestHarness__DOT__SimDTM__DOT__exit_reg), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core.varInsert(__Vfinal,"rf", &(TOP.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__rf), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,30 ,63,0);
        __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core.varInsert(__Vfinal,"wb_reg_pc", &(TOP.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__wb_reg_pc), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,39,0);
        __Vscope_TestHarness__ldut__tile_prci_domain__tile_reset_domain__tile__core__csr.varInsert(__Vfinal,"reg_dpc", &(TOP.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__csr__DOT__reg_dpc), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,39,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_0", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_0), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_1", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_1), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_2", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_2), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_3", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_3), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_4", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_4), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_5", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_5), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_6", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_6), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
        __Vscope_TestHarness__mem__srams.varInsert(__Vfinal,"mem_7", &(TOP.TestHarness__DOT__mem__DOT__srams__DOT__mem_7), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,33554431 ,7,0);
    }
}
