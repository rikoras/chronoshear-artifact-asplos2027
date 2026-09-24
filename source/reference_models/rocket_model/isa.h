#pragma once
// rocket_model: ISA-level constants and decoded control bundle for the hand-written
// Rocket DefaultConfig reference model. Numeric control codes describe the
// pipeline observation ABI; instruction semantics live in rocket_decode.cpp.
#include <cstdint>

namespace chisa::rocket_model {

// ALU function codes (from ALU.scala)
static constexpr uint8_t FN_ADD  = 0;
static constexpr uint8_t FN_SL   = 1;
static constexpr uint8_t FN_SEQ  = 2;
static constexpr uint8_t FN_SNE  = 3;
static constexpr uint8_t FN_XOR  = 4;
static constexpr uint8_t FN_SR   = 5;
static constexpr uint8_t FN_OR   = 6;
static constexpr uint8_t FN_AND  = 7;
static constexpr uint8_t FN_SUB  = 10;
static constexpr uint8_t FN_SRA  = 11;
static constexpr uint8_t FN_SLT  = 12;
static constexpr uint8_t FN_SGE  = 13;
static constexpr uint8_t FN_SLTU = 14;
static constexpr uint8_t FN_SGEU = 15;

// Operand selects (from Consts.scala)
static constexpr uint8_t A1_ZERO = 0;
static constexpr uint8_t A1_RS1  = 1;
static constexpr uint8_t A1_PC   = 2;

static constexpr uint8_t A2_ZERO = 0;
static constexpr uint8_t A2_SIZE = 1;
static constexpr uint8_t A2_RS2  = 2;
static constexpr uint8_t A2_IMM  = 3;

// Immediate types
static constexpr uint8_t IMM_S  = 0;
static constexpr uint8_t IMM_SB = 1;
static constexpr uint8_t IMM_U  = 2;
static constexpr uint8_t IMM_UJ = 3;
static constexpr uint8_t IMM_I  = 4;
static constexpr uint8_t IMM_Z  = 5;

// Data width
static constexpr uint8_t DW_32  = 0;
static constexpr uint8_t DW_64  = 1;
static constexpr uint8_t DW_XPR = 1;

// CSR commands (from CSR.scala)
static constexpr uint8_t CSR_N = 0;
static constexpr uint8_t CSR_R = 2;
static constexpr uint8_t CSR_I = 4;
static constexpr uint8_t CSR_W = 5;
static constexpr uint8_t CSR_S = 6;
static constexpr uint8_t CSR_C = 7;

// Memory commands (from Consts.scala)
static constexpr uint8_t M_XRD       = 0;
static constexpr uint8_t M_XWR       = 1;
static constexpr uint8_t M_PFR       = 2;
static constexpr uint8_t M_PFW       = 3;
static constexpr uint8_t M_XA_SWAP   = 4;
static constexpr uint8_t M_FLUSH_ALL = 5;
static constexpr uint8_t M_XLR       = 6;
static constexpr uint8_t M_XSC       = 7;
static constexpr uint8_t M_XA_ADD    = 8;
static constexpr uint8_t M_XA_XOR    = 9;
static constexpr uint8_t M_XA_OR     = 10;
static constexpr uint8_t M_XA_AND    = 11;
static constexpr uint8_t M_XA_MIN    = 12;
static constexpr uint8_t M_XA_MAX    = 13;
static constexpr uint8_t M_XA_MINU   = 14;
static constexpr uint8_t M_XA_MAXU   = 15;
static constexpr uint8_t M_FLUSH     = 16;
static constexpr uint8_t M_PWR       = 17;
static constexpr uint8_t M_SFENCE    = 20;


struct DecodedCtrl {
    uint8_t branch;
    uint8_t jal;
    uint8_t jalr;
    uint8_t rxs2;
    uint8_t rxs1;
    uint8_t sel_alu2;
    uint8_t sel_alu1;
    uint8_t sel_imm;
    uint8_t alu_dw;
    uint8_t alu_fn;
    uint8_t mem;
    uint8_t mem_cmd;
    uint8_t div;
    uint8_t wxd;
    uint8_t csr;
    uint8_t fence_i;
    uint8_t fp;
    uint8_t mul;
    uint8_t fence;
    uint8_t amo;
    uint8_t rocc;
    uint8_t scie;
    uint8_t rfs3;
    uint8_t dp;
    uint8_t rfs1;
    uint8_t rfs2;
    uint8_t wfd;
    // Recognized instruction encoding. CSR permissions, ISA enable bits and
    // dynamic rounding legality are checked separately by the core.
    uint8_t legal;
};

struct BtbResp {
    uint8_t  cfiType;
    uint8_t  taken;
    uint8_t  mask;
    uint8_t  bridx;
    uint64_t target;
    uint8_t  entry;
    uint8_t  bht_history;
    uint8_t  bht_value;
};

}  // namespace chisa::rocket_model
