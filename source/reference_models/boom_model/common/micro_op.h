#pragma once
// BOOM instruction values and decode interface, independent of either core.
#include <cstdint>
#include <cstring>
#include "boom_config.h"

// uopc micro-op codes (BOOM uop.scala — subset; extend as decode is built)
// ---------------------------------------------------------------------------
// uopc micro-op codes — exact values from riscv-boom common/consts.scala.
static constexpr uint8_t uopNOP=0, uopLD=1, uopSTA=2, uopSTD=3, uopLUI=4,
    uopADDI=5, uopANDI=6, uopORI=7, uopXORI=8, uopSLTI=9, uopSLTIU=10,
    uopSLLI=11, uopSRAI=12, uopSRLI=13, uopSLL=14, uopADD=15, uopSUB=16,
    uopSLT=17, uopSLTU=18, uopAND=19, uopOR=20, uopXOR=21, uopSRA=22, uopSRL=23,
    uopBEQ=24, uopBNE=25, uopBGE=26, uopBGEU=27, uopBLT=28, uopBLTU=29,
    uopCSRRW=30, uopCSRRS=31, uopCSRRC=32, uopCSRRWI=33, uopCSRRSI=34, uopCSRRCI=35,
    uopJ=36, uopJAL=37, uopJALR=38, uopAUIPC=39, uopCFLSH=41, uopFENCE=42,
    uopADDIW=43, uopADDW=44, uopSUBW=45, uopSLLIW=46, uopSLLW=47, uopSRAIW=48,
    uopSRAW=49, uopSRLIW=50, uopSRLW=51, uopMUL=52, uopMULH=53, uopMULHU=54,
    uopMULHSU=55, uopMULW=56, uopDIV=57, uopDIVU=58, uopREM=59, uopREMU=60,
    uopDIVW=61, uopDIVUW=62, uopREMW=63, uopREMUW=64, uopFENCEI=65;
static constexpr uint8_t uopAMO_AG=67;
// FP uopc block (consts.scala:205-251); used only under BOOM_GUIDER_FP but the
// constants are harmless everywhere.
static constexpr uint8_t uopFMV_S_X=68, uopFMV_D_X=69, uopFMV_X_S=70, uopFMV_X_D=71,
    uopFSGNJ_S=72, uopFSGNJ_D=73, uopFCVT_S_D=74, uopFCVT_D_S=75,
    uopFCVT_S_X=76, uopFCVT_D_X=77, uopFCVT_X_S=78, uopFCVT_X_D=79,
    uopCMPR_S=80, uopCMPR_D=81, uopFCLASS_S=82, uopFCLASS_D=83,
    uopFMINMAX_S=84, uopFMINMAX_D=85,
    uopFADD_S=87, uopFSUB_S=88, uopFMUL_S=89, uopFADD_D=90, uopFSUB_D=91, uopFMUL_D=92,
    uopFMADD_S=93, uopFMSUB_S=94, uopFNMADD_S=95, uopFNMSUB_S=96,
    uopFMADD_D=97, uopFMSUB_D=98, uopFNMADD_D=99, uopFNMSUB_D=100,
    uopFDIV_S=101, uopFDIV_D=102, uopFSQRT_S=103, uopFSQRT_D=104;
static constexpr uint8_t uopWFI=105, uopERET=106, uopSFENCE=107;

// iq_type (issue-queue dispatch target, one-hot) — BOOM consts.scala:
// IQT_INT=1, IQT_MEM=2, IQT_FP=4 (guider previously had INT/MEM swapped).
static constexpr uint8_t IQT_INT = 0x1;
static constexpr uint8_t IQT_MEM = 0x2;
static constexpr uint8_t IQT_FP  = 0x4;

// rtype (register type) — BOOM RT_* encoding
static constexpr uint8_t RT_FIX = 0;  // fixed-point (integer)
static constexpr uint8_t RT_FLT = 1;  // floating-point
static constexpr uint8_t RT_PAS = 3;  // pass-through / x0 (not renamed)
static constexpr uint8_t RT_X   = 2;  // unused/killed operand (issue sets on store split)

// fu_code one-hot bits (FUConstants.scala) — shared by decode + issue select.
static constexpr uint16_t FU_ALU = 1u << 0;
static constexpr uint16_t FU_JMP = 1u << 1;
static constexpr uint16_t FU_MEM = 1u << 2;
static constexpr uint16_t FU_MUL = 1u << 3;
static constexpr uint16_t FU_DIV = 1u << 4;
static constexpr uint16_t FU_CSR = 1u << 5;
static constexpr uint16_t FU_FPU = 1u << 6;   // functional-unit.scala:47-50
static constexpr uint16_t FU_FDV = 1u << 7;
static constexpr uint16_t FU_I2F = 1u << 8;
static constexpr uint16_t FU_F2I = 1u << 9;

// Branch type (ctrl.br_type, consts.scala:65-73) + resolved pc select (pc_sel).
static constexpr uint8_t BR_N=0, BR_NE=1, BR_EQ=2, BR_GE=3, BR_GEU=4,
                         BR_LT=5, BR_LTU=6, BR_J=7, BR_JR=8;
static constexpr uint8_t PC_PLUS4=0, PC_BRJMP=1, PC_JALR=2;

// ---------------------------------------------------------------------------
// MicroOp — BOOM's uniform micro-op bundle (verbatim from StandaloneBoomDUT
// io.ifu.fetchpacket.bits.uops[0].bits; the same bundle flows through rename,
// dispatch, issue, ROB, and commit). Field widths match the RTL exactly.
// ---------------------------------------------------------------------------
struct MicroCtrl {
    uint8_t  br_type;   // :4
    uint8_t  op1_sel;   // :2
    uint8_t  op2_sel;   // :3
    uint8_t  imm_sel;   // :3
    uint8_t  op_fcn;    // :4  (ALU function, same encoding as rocket ALU FN_*)
    uint8_t  fcn_dw;    // :1  (0=DW_32, 1=DW_64)
    uint8_t  csr_cmd;   // :3
    uint8_t  is_load;   // :1
    uint8_t  is_sta;    // :1  (store address)
    uint8_t  is_std;    // :1  (store data)
};

struct MicroOp {
    uint8_t  uopc;        // :7
    uint32_t inst;        // :32
    uint32_t debug_inst;  // :32
    uint8_t  is_rvc;      // :1
    uint64_t debug_pc;    // :41
    uint8_t  iq_type;     // :3
    uint16_t fu_code;     // :10
    MicroCtrl ctrl;

    uint8_t  iw_state;      // :2  (issue-window slot state)
    uint8_t  iw_p1_poisoned;// :1
    uint8_t  iw_p2_poisoned;// :1
    uint8_t  is_br;         // :1
    uint8_t  is_jalr;       // :1
    uint8_t  is_jal;        // :1
    uint8_t  is_sfb;        // :1  (short-forward-branch)

    boomcfg::br_mask_t br_mask;   // branches this uop is speculative under
    uint8_t  br_tag;        // :2  (branch's own tag, if is_br)
    uint8_t  ftq_idx;       // :3
    uint8_t  edge_inst;     // :1
    uint8_t  pc_lob;        // :6  (low bits of PC)
    uint8_t  taken;         // :1
    uint32_t imm_packed;    // :20
    uint16_t csr_addr;      // :12

    uint8_t  rob_idx;       // :4
    uint8_t  ldq_idx;       // :2
    uint8_t  stq_idx;       // :2
    uint8_t  rxq_idx;       // :2
    uint8_t  pdst;          // :6  (physical dest)
    uint8_t  prs1;          // :6  (physical src1)
    uint8_t  prs2;          // :6
    uint8_t  prs3;          // :6
    uint8_t  ppred;         // :3
    uint8_t  prs1_busy;     // :1
    uint8_t  prs2_busy;     // :1
    uint8_t  prs3_busy;     // :1
    uint8_t  ppred_busy;    // :1
    uint8_t  stale_pdst;    // :6  (previous mapping of ldst, freed at commit)
    uint8_t  exception;     // :1
    uint64_t exc_cause;     // :64
    uint8_t  bypassable;    // :1

    uint8_t  mem_cmd;       // :5  (M_XRD, M_XWR, ...)
    uint8_t  mem_size;      // :2
    uint8_t  mem_signed;    // :1
    uint8_t  is_fence;      // :1
    uint8_t  is_fencei;     // :1
    uint8_t  is_amo;        // :1
    uint8_t  uses_ldq;      // :1
    uint8_t  uses_stq;      // :1
    uint8_t  is_sys_pc2epc; // :1
    uint8_t  is_unique;     // :1
    uint8_t  flush_on_commit;// :1
    uint8_t  ldst_is_rs1;   // :1

    uint8_t  ldst;          // :5  (logical dest)
    uint8_t  lrs1;          // :5  (logical src1)
    uint8_t  lrs2;          // :5
    uint8_t  lrs3;          // :5
    uint8_t  ldst_val;      // :1  (writes a register)
    uint8_t  dst_rtype;     // :2
    uint8_t  lrs1_rtype;    // :2
    uint8_t  lrs2_rtype;    // :2
    uint8_t  frs3_en;       // :1
    uint8_t  fp_val;        // :1
    uint8_t  fp_single;     // :1

    uint8_t  xcpt_pf_if;    // :1
    uint8_t  xcpt_ae_if;    // :1
    uint8_t  xcpt_ma_if;    // :1
    uint8_t  bp_debug_if;   // :1
    uint8_t  bp_xcpt_if;    // :1
    uint8_t  debug_fsrc;    // :2
    uint8_t  debug_tsrc;    // :2

    void clear() { memset(this, 0, sizeof(*this)); }
};

// BOOM DecodeUnit: fill the decode-stage fields of a MicroOp from its raw inst.
// (Defined in boom_decode.cpp.)
void boom_decode(MicroOp& u);
// Instruction-static decode with the same pass-through and exception rules.
// CSR-dependent legality remains the caller's per-cycle responsibility.
void boom_decode_cached(MicroOp& u);
