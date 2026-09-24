// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTestHarness.h for the primary calling header

#include "VTestHarness__pch.h"
#include "VTestHarness__Syms.h"
#include "VTestHarness___024unit.h"

extern "C" int debug_tick(svBit* debug_req_valid, svBit debug_req_ready, int* debug_req_bits_addr, int* debug_req_bits_op, int* debug_req_bits_data, svBit debug_resp_valid, svBit* debug_resp_ready, int debug_resp_bits_resp, int debug_resp_bits_data);

VL_INLINE_OPT void VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit(CData/*0:0*/ &debug_req_valid, CData/*0:0*/ debug_req_ready, IData/*31:0*/ &debug_req_bits_addr, IData/*31:0*/ &debug_req_bits_op, IData/*31:0*/ &debug_req_bits_data, CData/*0:0*/ debug_resp_valid, CData/*0:0*/ &debug_resp_ready, IData/*31:0*/ debug_resp_bits_resp, IData/*31:0*/ debug_resp_bits_data, IData/*31:0*/ &debug_tick__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VTestHarness___024unit____Vdpiimwrap_debug_tick_TOP____024unit\n"); );
    // Body
    svBit debug_req_valid__Vcvt;
    svBit debug_req_ready__Vcvt;
    for (size_t debug_req_ready__Vidx = 0; debug_req_ready__Vidx < 1; ++debug_req_ready__Vidx) debug_req_ready__Vcvt = debug_req_ready;
    int debug_req_bits_addr__Vcvt;
    int debug_req_bits_op__Vcvt;
    int debug_req_bits_data__Vcvt;
    svBit debug_resp_valid__Vcvt;
    for (size_t debug_resp_valid__Vidx = 0; debug_resp_valid__Vidx < 1; ++debug_resp_valid__Vidx) debug_resp_valid__Vcvt = debug_resp_valid;
    svBit debug_resp_ready__Vcvt;
    int debug_resp_bits_resp__Vcvt;
    for (size_t debug_resp_bits_resp__Vidx = 0; debug_resp_bits_resp__Vidx < 1; ++debug_resp_bits_resp__Vidx) debug_resp_bits_resp__Vcvt = debug_resp_bits_resp;
    int debug_resp_bits_data__Vcvt;
    for (size_t debug_resp_bits_data__Vidx = 0; debug_resp_bits_data__Vidx < 1; ++debug_resp_bits_data__Vidx) debug_resp_bits_data__Vcvt = debug_resp_bits_data;
    int debug_tick__Vfuncrtn__Vcvt;
    debug_tick__Vfuncrtn__Vcvt = debug_tick(&debug_req_valid__Vcvt, debug_req_ready__Vcvt, &debug_req_bits_addr__Vcvt, &debug_req_bits_op__Vcvt, &debug_req_bits_data__Vcvt, debug_resp_valid__Vcvt, &debug_resp_ready__Vcvt, debug_resp_bits_resp__Vcvt, debug_resp_bits_data__Vcvt);
    debug_req_valid = (1U & debug_req_valid__Vcvt);
    debug_req_bits_addr = debug_req_bits_addr__Vcvt;
    debug_req_bits_op = debug_req_bits_op__Vcvt;
    debug_req_bits_data = debug_req_bits_data__Vcvt;
    debug_resp_ready = (1U & debug_resp_ready__Vcvt);
    debug_tick__Vfuncrtn = debug_tick__Vfuncrtn__Vcvt;
}
