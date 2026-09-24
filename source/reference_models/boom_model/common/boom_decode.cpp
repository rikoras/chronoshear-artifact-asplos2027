#include "micro_op.h"
#include <cstdlib>
// Software instruction decoder. Control values follow instruction semantics;
// unused controls have explicit canonical values. No minimized RTL equations
// or generated DecodeUnit implementation participate in reference execution.

// ---------------------------------------------------------------------------
// BOOM DecodeUnit (first-cut, integer RV64I/M + system).
// Fills the decode-stage fields of a MicroOp from a raw 32-bit instruction:
// logical regs (lrs1/lrs2/ldst) + register types, ldst_val, iq_type, fu_code,
// uses_ldq/uses_stq, mem_cmd, is_br/is_jal/is_jalr, and ctrl.* (op1/op2/imm
// selects, alu fn, csr cmd). Mirrors rocket-chip's decode constants that BOOM
// reuses. Standalone BOOM Small has no FPU, so FP ops are left unhandled.
//
// NOTE: this is the model of the internal DecodeUnit; the harness feeds only the
// raw inst (see benchmarks/boom/gen_trace_boom.cpp::drive_fetchpacket), so the
// guider must decode exactly as the RTL does. Refined field-by-field against the
// scalar DUT during validation.
// ---------------------------------------------------------------------------

// fu_code one-hot bits (FU_ALU/JMP/MEM/MUL/DIV/CSR) now live in boom_guider.h
// (shared with issue select).

// ctrl.op1_sel (OP1_*): RS1=0, ZERO=1, PC=2  (BOOM Consts)
static constexpr uint8_t OP1_RS1 = 0, OP1_ZERO = 1, OP1_PC = 2;
// ctrl.op2_sel (OP2_*, consts.scala:81-91): RS2=0, IMM=1, ZERO=2, NEXT=3, IMMC=4
static constexpr uint8_t OP2_RS2 = 0, OP2_IMM = 1, OP2_ZERO = 2, OP2_NEXT = 3, OP2_IMMC = 4;
// imm_sel (IS_*): I=0, S=1, B=2, U=3, J=4  (matches BOOM IS_ enum ordering used here)
static constexpr uint8_t IS_I = 0, IS_S = 1, IS_B = 2, IS_U = 3, IS_J = 4;
// br_type constants (BR_*) live in boom_guider.h (shared with the compute path).

// ALU fn (shared with rocket ALU FN_*)
static constexpr uint8_t FN_ADD=0,FN_SL=1,FN_SEQ=2,FN_SNE=3,FN_XOR=4,FN_SR=5,
                         FN_OR=6,FN_AND=7,FN_SUB=10,FN_SRA=11,FN_SLT=12,FN_SGE=13,
                         FN_SLTU=14,FN_SGEU=15;

// mem_cmd (Consts M_*)
static constexpr uint8_t M_XRD=0, M_XWR=1;

// csr_cmd (CSR.scala): N=0,R=2,I=4,W=5,S=6,C=7
static constexpr uint8_t CSR_N=0,CSR_R=2,CSR_I=4,CSR_W=5,CSR_S=6,CSR_C=7;

static inline uint8_t bits(uint32_t x, int hi, int lo) {
    return static_cast<uint8_t>((x >> lo) & ((1u << (hi - lo + 1)) - 1));
}

// Decode into the flowing MicroOp's decode fields. inst is the (RVC-expanded)
// 32-bit instruction; caller has already set uop.inst / debug_pc / ftq_idx /
// is_rvc / taken / xcpt_* from the fetchpacket.
void boom_decode(MicroOp& u) {
    // Frontend/decode-neighbor producers may already have selected a higher-
    // priority exception (most importantly an interrupt).  Decode still has
    // to fill every control field, but its local default/illegal cause must not
    // overwrite that selected cause.  This mirrors decode.scala's PriorityMux,
    // where io.interrupt is the first exception source.
    const bool upstream_exception = u.exception != 0;
    const uint64_t upstream_cause = u.exc_cause;
    uint32_t inst = u.inst;
    uint8_t opcode = inst & 0x7F;
    uint8_t funct3 = bits(inst, 14, 12);
    uint8_t funct7 = bits(inst, 31, 25);

    // Register fields (fixed positions). lrs3 is raw inst bits in the RTL
    // (decode.scala reads RS3 unconditionally; FP-only semantically).
    u.ldst = bits(inst, 11, 7);
    u.lrs1 = bits(inst, 19, 15);
    u.lrs2 = bits(inst, 24, 20);
    u.lrs3 = bits(inst, 31, 27);

    // Defaults: no-op-ish integer bubble. Non-writing dest and unused sources are
    // RT_X (2), NOT RT_PAS (3) — matches BOOM's decode table (decode.scala): e.g.
    // ADDI has rs2=RT_X, stores/branches have dst=RT_X. set_dst/use_rs* promote to
    // RT_FIX where the op actually writes/reads an integer register.
    u.uopc = uopNOP;
    u.dst_rtype = RT_X; u.lrs1_rtype = RT_X; u.lrs2_rtype = RT_X;
    u.ldst_val = 0; u.iq_type = IQT_INT; u.fu_code = FU_ALU;
    u.uses_ldq = 0; u.uses_stq = 0; u.mem_cmd = 0;
    u.is_br = 0; u.is_jal = 0; u.is_jalr = 0;
    u.is_sys_pc2epc = 0;
    u.is_fence = u.is_fencei = u.is_amo = 0;
    u.is_unique = u.flush_on_commit = 0;
    u.fp_val = u.fp_single = u.frs3_en = 0;
    u.csr_addr = 0;
    u.exception = 0;
    u.ctrl.op1_sel = OP1_RS1; u.ctrl.op2_sel = OP2_RS2;
    u.ctrl.imm_sel = IS_I; u.ctrl.op_fcn = FN_ADD; u.ctrl.fcn_dw = 1;
    u.ctrl.csr_cmd = CSR_N; u.ctrl.is_load = 0; u.ctrl.is_sta = 0; u.ctrl.is_std = 0;
    u.ctrl.br_type = 0;

    // BOOM DecodeUnit: dst_rtype reflects the dest TYPE from the decode table
    // (RT_FIX for any int-producing op), INDEPENDENT of ldst==x0; ldst_val is
    // what accounts for x0 (writes only if int-dest && ldst!=0). Do not fold x0
    // into dst_rtype — RTL keeps r_uop_dst_rtype=RT_FIX even for `li x0`.
    auto set_dst = [&](bool val) { u.dst_rtype = val ? RT_FIX : RT_PAS;
                                   u.ldst_val  = (val && u.ldst != 0) ? 1 : 0; };
    auto use_rs1 = [&]{ u.lrs1_rtype = RT_FIX; };
    auto use_rs2 = [&]{ u.lrs2_rtype = RT_FIX; };

    switch (opcode) {
    case 0x37: // LUI
        u.uopc = uopLUI;
        u.ctrl.op1_sel = OP1_ZERO; u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_U;
        set_dst(true); break;
    case 0x17: // AUIPC (decoded to FU_JMP: uses the BRU for the PC read)
        u.uopc = uopAUIPC; u.fu_code = FU_JMP;
        u.ctrl.op1_sel = OP1_PC; u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_U;
        set_dst(true); break;
    case 0x6F: // JAL
        u.uopc = uopJAL; u.is_jal = 1; u.fu_code = FU_JMP; u.ctrl.imm_sel = IS_J;
        u.ctrl.br_type = BR_J; set_dst(true); break;
    case 0x67: // JALR
        if (funct3 != 0) goto instruction_illegal;
        u.uopc = uopJALR; u.is_jalr = 1; u.fu_code = FU_JMP; u.ctrl.imm_sel = IS_I;
        u.ctrl.br_type = BR_JR; use_rs1(); set_dst(true); break;
    case 0x63: // BRANCH (funct3: 0=BEQ 1=BNE 4=BLT 5=BGE 6=BLTU 7=BGEU)
        if (funct3 == 2 || funct3 == 3) goto instruction_illegal;
        u.uopc = (funct3==0)?uopBEQ:(funct3==1)?uopBNE:(funct3==4)?uopBLT:
                 (funct3==5)?uopBGE:(funct3==6)?uopBLTU:uopBGEU;
        u.is_br = 1; u.fu_code = FU_ALU; u.ctrl.imm_sel = IS_B;
        u.ctrl.br_type = (funct3==0)?BR_EQ:(funct3==1)?BR_NE:(funct3==4)?BR_LT:
                         (funct3==5)?BR_GE:(funct3==6)?BR_LTU:BR_GEU;
        use_rs1(); use_rs2(); break;
    case 0x03: // LOAD
        if (funct3 == 7) goto instruction_illegal;
        u.uopc = uopLD; u.fu_code = FU_MEM; u.iq_type = IQT_MEM; u.uses_ldq = 1;
        u.ctrl.is_load = 1; u.mem_cmd = M_XRD; u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_I;
        u.mem_size = funct3 & 3; u.mem_signed = ((funct3 >> 2) & 1) ? 0 : 1;
        use_rs1(); set_dst(true); break;
    case 0x23: // STORE (rename emits STA; issue splits into STA + STD)
        if (funct3 > 3) goto instruction_illegal;
        u.uopc = uopSTA; u.fu_code = FU_MEM; u.iq_type = IQT_MEM; u.uses_stq = 1;
        u.ctrl.is_sta = 1; u.ctrl.is_std = 1; u.mem_cmd = M_XWR;
        u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_S; u.mem_size = funct3 & 3;
        u.mem_signed = ((funct3 >> 2) & 1) ? 0 : 1;   // decode table sets it for stores too
        use_rs1(); use_rs2(); break;
    case 0x2f: { // RV64A: the operation and access width determine the route.
        if (funct3 != 2 && funct3 != 3) goto instruction_illegal;
        const unsigned operation = inst >> 27;
        switch (operation) {
        case 0x00: u.mem_cmd = 8; break;  // add
        case 0x01: u.mem_cmd = 4; break;  // swap
        case 0x02: u.mem_cmd = 6; break;  // load-reserved
        case 0x03: u.mem_cmd = 7; break;  // store-conditional
        case 0x04: u.mem_cmd = 9; break;  // xor
        case 0x08: u.mem_cmd = 10; break; // or
        case 0x0c: u.mem_cmd = 11; break; // and
        case 0x10: u.mem_cmd = 12; break; // signed min
        case 0x14: u.mem_cmd = 13; break; // signed max
        case 0x18: u.mem_cmd = 14; break; // unsigned min
        case 0x1c: u.mem_cmd = 15; break; // unsigned max
        default: goto instruction_illegal;
        }
        if (operation == 2 && u.lrs2 != 0) goto instruction_illegal;
        u.uopc = operation == 2 ? uopLD : uopAMO_AG;
        u.fu_code = FU_MEM;
        u.iq_type = IQT_MEM;
        use_rs1();          // address base
        set_dst(true);      // LR loads / SC writes success flag / AMO returns old value
        // decode.scala:257-280: every LR/SC/AMO row carries inst_unique = Y
        // and flush_on_commit = Y (the pipeline drains around the atomic and
        // is flushed after it commits).  First seen in dhrystone's
        // arch_spin_lock (amoswap.w) at cycle 1,456,717, past the 1M-cycle
        // gates.
        u.is_unique = 1; u.flush_on_commit = 1;
        if (bits(inst, 31, 27) == 0x02) {   // LR: load-reserved (rs2 unused)
            u.uses_ldq = 1; u.ctrl.is_load = 1;
        } else {                            // SC / AMO*: store-queue, atomic RMW
            u.uses_stq = 1; u.is_amo = 1; use_rs2();
        }
        break;
    }
    case 0x13: // OP-IMM (funct3: 0=ADDI 1=SLLI 2=SLTI 3=SLTIU 4=XORI 5=SR*I 6=ORI 7=ANDI)
        if ((funct3 == 1 && (inst >> 26) != 0) ||
            (funct3 == 5 && (inst >> 26) != 0 && (inst >> 26) != 16))
            goto instruction_illegal;
        u.uopc = (funct3==0)?uopADDI:(funct3==1)?uopSLLI:(funct3==2)?uopSLTI:
                 (funct3==3)?uopSLTIU:(funct3==4)?uopXORI:(funct3==6)?uopORI:
                 (funct3==7)?uopANDI:(((funct7>>5)&1)?uopSRAI:uopSRLI);
        u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_I; u.ctrl.fcn_dw = 1;
        u.ctrl.op_fcn = (funct3==0)?FN_ADD:(funct3==2)?FN_SLT:(funct3==3)?FN_SLTU:
                        (funct3==4)?FN_XOR:(funct3==6)?FN_OR:(funct3==7)?FN_AND:
                        (funct3==1)?FN_SL:((funct7>>5)&1?FN_SRA:FN_SR);
        use_rs1(); set_dst(true); break;
    case 0x1B: // OP-IMM-32
        if ((funct3 != 0 && funct3 != 1 && funct3 != 5) ||
            (funct3 == 1 && funct7 != 0) ||
            (funct3 == 5 && funct7 != 0 && funct7 != 0x20)) goto instruction_illegal;
        u.uopc = (funct3==0)?uopADDIW:(funct3==1)?uopSLLIW:(((funct7>>5)&1)?uopSRAIW:uopSRLIW);
        u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_I; u.ctrl.fcn_dw = 0;
        u.ctrl.op_fcn = (funct3==0)?FN_ADD:(funct3==1)?FN_SL:((funct7>>5)&1?FN_SRA:FN_SR);
        use_rs1(); set_dst(true); break;
    case 0x33: // OP (R-type: RV64I + RV64M)
        if (funct7 != 0 && funct7 != 1 &&
            !(funct7 == 0x20 && (funct3 == 0 || funct3 == 5))) goto instruction_illegal;
        if (funct7 == 0x01) { // MULDIV (funct3: 0=MUL 1=MULH 2=MULHSU 3=MULHU 4=DIV 5=DIVU 6=REM 7=REMU)
            bool is_div = funct3 >= 4;
            u.fu_code = is_div ? FU_DIV : FU_MUL;
            u.uopc = (funct3==0)?uopMUL:(funct3==1)?uopMULH:(funct3==2)?uopMULHSU:
                     (funct3==3)?uopMULHU:(funct3==4)?uopDIV:(funct3==5)?uopDIVU:
                     (funct3==6)?uopREM:uopREMU;
            u.ctrl.op_fcn = funct3; // MUL/MULH/.../DIV/DIVU/REM/REMU encoded in fn
        } else {
            u.uopc = (funct3==0)?(((funct7>>5)&1)?uopSUB:uopADD):(funct3==1)?uopSLL:
                     (funct3==2)?uopSLT:(funct3==3)?uopSLTU:(funct3==4)?uopXOR:
                     (funct3==5)?(((funct7>>5)&1)?uopSRA:uopSRL):(funct3==6)?uopOR:uopAND;
            u.ctrl.op_fcn = (funct3==0)?((funct7>>5)&1?FN_SUB:FN_ADD):
                            (funct3==1)?FN_SL:(funct3==2)?FN_SLT:(funct3==3)?FN_SLTU:
                            (funct3==4)?FN_XOR:(funct3==5)?(((funct7>>5)&1)?FN_SRA:FN_SR):
                            (funct3==6)?FN_OR:FN_AND;
        }
        u.ctrl.fcn_dw = 1; use_rs1(); use_rs2(); set_dst(true); break;
    case 0x3B: // OP-32 (RV64I word + RV64M word)
        if (funct7 == 1 ? (funct3 != 0 && funct3 < 4) :
            ((funct3 != 0 && funct3 != 1 && funct3 != 5) ||
             (funct7 != 0 && !(funct7 == 0x20 && funct3 != 1)))) goto instruction_illegal;
        if (funct7 == 0x01) {
            bool is_div = funct3 >= 4; u.fu_code = is_div?FU_DIV:FU_MUL;
            u.uopc = (funct3==0)?uopMULW:(funct3==4)?uopDIVW:(funct3==5)?uopDIVUW:
                     (funct3==6)?uopREMW:uopREMUW;
            u.ctrl.op_fcn = funct3;
        } else {
            u.uopc = (funct3==0)?(((funct7>>5)&1)?uopSUBW:uopADDW):(funct3==1)?uopSLLW:
                     (((funct7>>5)&1)?uopSRAW:uopSRLW);
            u.ctrl.op_fcn = (funct3==0)?((funct7>>5)&1?FN_SUB:FN_ADD):
                             (funct3==1)?FN_SL:(((funct7>>5)&1)?FN_SRA:FN_SR);
        }
        u.ctrl.fcn_dw = 0; use_rs1(); use_rs2(); set_dst(true); break;
    case 0x0F: // FENCE / FENCE.I
        if (funct3 > 1) goto instruction_illegal;
        if (funct3 == 1) { u.uopc = uopNOP; u.is_fencei = 1; u.is_unique = 1; u.flush_on_commit = 1; }
        else { u.uopc = uopFENCE; u.is_fence = 1; u.fu_code = FU_MEM; u.uses_stq = 1;
               u.is_unique = 1; u.flush_on_commit = 1; } // Ordering barrier; no memory access command.
        break;
    case 0x73: { // SYSTEM (CSR + ecall/ebreak)
        if (funct3 == 0) {
            // SFENCE.VMA is a serializing MEM-queue operation, despite sharing
            // the SYSTEM major opcode with the CSR/return instructions.  The
            // address-space invalidation uses the memory unit.
            const bool is_sfence =
                (inst & UINT32_C(0xfe007fff)) == UINT32_C(0x12000073);
            if (is_sfence) {
                u.uopc = uopSFENCE;
                u.iq_type = IQT_MEM;
                u.fu_code = FU_MEM;
                u.mem_cmd = 20;  // M_SFENCE
                use_rs1();
                use_rs2();
            } else {
                switch (inst) {
                case 0x00000073: case 0x00100073: // ECALL / EBREAK
                case 0x10200073: case 0x30200073: // SRET / MRET
                case 0x7b200073:                  // DRET
                    u.uopc = uopERET; break;
                case 0x10500073: u.uopc = uopWFI; break;
                default: goto instruction_illegal;
                }
                u.fu_code = FU_CSR;
                u.ctrl.csr_cmd = CSR_I;
            }
            // Only ECALL and EBREAK set EPC to their own PC.  xRET/DRET share
            // uopERET but must not trigger core.scala's early FTQ dequeue.
            u.is_sys_pc2epc =
                inst == UINT32_C(0x00000073) ||
                inst == UINT32_C(0x00100073);
            u.is_unique = 1; u.flush_on_commit = 1; break;
        }
        if (funct3 == 4) goto instruction_illegal;
        u.fu_code = FU_CSR; u.iq_type = IQT_INT;
        u.is_unique = 1; u.flush_on_commit = 1;  // CSR accesses serialize (decode.scala: is_unique + flush)
        u.csr_addr = (inst >> 20) & 0xFFF;  // 12-bit CSR address (used by the guider's CSR model, not the rename-stage reg)
#if !defined(BOOM_GUIDER_FP)
        // FP CSR access (fflags/frm/fcsr) is illegal on a no-FPU core (csr_decode
        // read/write_illegal -> id_illegal_insn, decode.scala:502). Marks the uop an
        // exception (like fscsr in the boot); it traps at commit.
        if (u.csr_addr >= 0x001 && u.csr_addr <= 0x003) { u.exception = 1; u.exc_cause = 2; }
#endif
        bool imm_form = (funct3 & 0x4) != 0;
        uint8_t base = (funct3 & 0x3); // 1=RW,2=RS,3=RC
        u.uopc = imm_form ? ((base==1)?uopCSRRWI:(base==2)?uopCSRRSI:uopCSRRCI)
                          : ((base==1)?uopCSRRW :(base==2)?uopCSRRS :uopCSRRC);
        u.ctrl.csr_cmd = (base==1)?CSR_W:(base==2)?CSR_S:CSR_C;
        if (!imm_form) use_rs1();
        else u.lrs1_rtype = RT_PAS;   // decode.scala:229-231 CSRRxI: lrs1 is the zimm pass-through
        set_dst(true);
        break;
    }
#if defined(BOOM_GUIDER_FP)
    // ---- RV64FD (FDecode + FDivSqrtDecode, exu/decode.scala:287-410). Column
    // meanings: uopc, iq_type, fu_code, dst/rs1/rs2 rtypes, frs3_en, fp_val,
    // fp_single ("is dst single-prec"). Loads use I immediates and stores S.
    case 0x07: { // FLW / FLD
        if (funct3 != 2 && funct3 != 3) goto fp_illegal;
        u.uopc = uopLD; u.fu_code = FU_MEM; u.iq_type = IQT_MEM; u.uses_ldq = 1;
        u.ctrl.is_load = 1; u.mem_cmd = M_XRD; u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_I;
        u.fp_val = 1; u.fp_single = (funct3 == 2) ? 1 : 0;
        u.lrs1_rtype = RT_FIX; u.dst_rtype = RT_FLT; u.ldst_val = 1;  // f-dest: x0 rule does not apply
        break;
    }
    case 0x27: { // FSW / FSD (IQT_MFP: dispatched to BOTH mem [addr] and fp [data] queues)
        if (funct3 != 2 && funct3 != 3) goto fp_illegal;
        u.uopc = uopSTA; u.fu_code = FU_F2I | FU_MEM; u.iq_type = IQT_MEM | IQT_FP; u.uses_stq = 1;
        u.ctrl.is_sta = 1; u.ctrl.is_std = 0; u.mem_cmd = M_XWR;   // data comes via fp_stdata, not STD
        u.ctrl.op2_sel = OP2_IMM; u.ctrl.imm_sel = IS_S;
        u.fp_val = 1; u.fp_single = (funct3 == 2) ? 1 : 0;
        u.lrs1_rtype = RT_FIX; u.lrs2_rtype = RT_FLT;
        break;
    }
    case 0x43: case 0x47: case 0x4B: case 0x4F: { // FMADD/FMSUB/FNMSUB/FNMADD
        uint8_t fmt = bits(inst, 26, 25);
        if (fmt > 1 || funct3 == 5 || funct3 == 6) goto fp_illegal;
        bool single = (fmt == 0);
        static const uint8_t fma_s[4] = { uopFMADD_S, uopFMSUB_S, uopFNMSUB_S, uopFNMADD_S };
        static const uint8_t fma_d[4] = { uopFMADD_D, uopFMSUB_D, uopFNMSUB_D, uopFNMADD_D };
        uint8_t k = (opcode >> 2) & 3;    // 0x43->0,0x47->1,0x4B->2,0x4F->3
        u.uopc = single ? fma_s[k] : fma_d[k];
        u.iq_type = IQT_FP; u.fu_code = FU_FPU;
        u.dst_rtype = RT_FLT; u.ldst_val = 1;
        u.lrs1_rtype = RT_FLT; u.lrs2_rtype = RT_FLT; u.frs3_en = 1;
        u.fp_val = 1; u.fp_single = single ? 1 : 0;
        break;
    }
    case 0x53: { // OP-FP
        uint8_t f7 = funct7;
        bool single = ((f7 & 3) == 0);        // fmt in f7[1:0]: 0=S, 1=D
        if ((f7 & 3) > 1) goto fp_illegal;
        const unsigned group = f7 >> 2;
        const bool rounded = group <= 3 || group == 8 || group == 11 || group == 24 || group == 26;
        if ((rounded && (funct3 == 5 || funct3 == 6)) ||
            (group == 4 && funct3 > 2) || (group == 5 && funct3 > 1) ||
            (group == 8 && u.lrs2 != (single ? 1 : 0)) ||
            (group == 11 && u.lrs2 != 0) || (group == 20 && funct3 > 2) ||
            ((group == 24 || group == 26) && u.lrs2 > 3) ||
            (group == 28 && (u.lrs2 != 0 || funct3 > 1)) ||
            (group == 30 && (u.lrs2 != 0 || funct3 != 0))) goto fp_illegal;
        u.iq_type = IQT_FP; u.fu_code = FU_FPU;
        u.dst_rtype = RT_FLT; u.ldst_val = 1;
        u.lrs1_rtype = RT_FLT; u.lrs2_rtype = RT_FLT;
        u.fp_val = 1; u.fp_single = single ? 1 : 0;
        switch (f7 >> 2) {
        case 0x00: u.uopc = single ? uopFADD_S : uopFADD_D; break;                      // FADD
        case 0x01: u.uopc = single ? uopFSUB_S : uopFSUB_D; break;                      // FSUB
        case 0x02: u.uopc = single ? uopFMUL_S : uopFMUL_D; break;                      // FMUL
        case 0x03: u.uopc = single ? uopFDIV_S : uopFDIV_D; u.fu_code = FU_FDV; break;  // FDIV
        case 0x0B:                                                                       // FSQRT
            u.uopc = single ? uopFSQRT_S : uopFSQRT_D; u.fu_code = FU_FDV;
            u.lrs2_rtype = RT_X; break;
        case 0x04: u.uopc = single ? uopFSGNJ_S : uopFSGNJ_D; break;                    // FSGNJ/N/X
        case 0x05: u.uopc = single ? uopFMINMAX_S : uopFMINMAX_D; break;                // FMIN/FMAX
        case 0x08:                                                                       // FCVT.S.D / FCVT.D.S
            u.uopc = single ? uopFCVT_S_D : uopFCVT_D_S; u.lrs2_rtype = RT_X; break;
        case 0x14:                                                                       // FEQ/FLT/FLE
            u.uopc = single ? uopCMPR_S : uopCMPR_D; u.fu_code = FU_F2I;
            u.dst_rtype = RT_FIX; u.ldst_val = (u.ldst != 0) ? 1 : 0; break;
        case 0x18:                                                                       // FCVT.W[U]/L[U] <- fp
            u.uopc = single ? uopFCVT_X_S : uopFCVT_X_D; u.fu_code = FU_F2I;
            u.dst_rtype = RT_FIX; u.ldst_val = (u.ldst != 0) ? 1 : 0;
            u.lrs2_rtype = RT_X; break;
        case 0x1A:                                                                       // FCVT fp <- W[U]/L[U] (int reg)
            u.uopc = single ? uopFCVT_S_X : uopFCVT_D_X; u.fu_code = FU_I2F;
            u.iq_type = IQT_INT; u.lrs1_rtype = RT_FIX; u.lrs2_rtype = RT_X; break;
        case 0x1C:                                                                       // FMV.X / FCLASS
            u.fu_code = FU_F2I; u.dst_rtype = RT_FIX; u.ldst_val = (u.ldst != 0) ? 1 : 0;
            u.lrs2_rtype = RT_X;
            u.uopc = (funct3 == 1) ? (single ? uopFCLASS_S : uopFCLASS_D)
                                   : (single ? uopFMV_X_S : uopFMV_X_D);
            break;
        case 0x1E:                                                                       // FMV.W.X / FMV.D.X
            u.uopc = single ? uopFMV_S_X : uopFMV_D_X; u.fu_code = FU_I2F;
            u.iq_type = IQT_INT; u.lrs1_rtype = RT_FIX; u.lrs2_rtype = RT_X; break;
        default: goto fp_illegal;
        }
        break;
    }
#endif
    default:
    instruction_illegal:
#if defined(BOOM_GUIDER_FP)
    fp_illegal:
#endif
        // Not in the RV64IM+system decode table (FP with no FPU, AMO without 'A', any
        // illegal encoding) -> decode_default gives legal=0 -> illegal instruction
        // (decode.scala:43,497-519). Fixed-default fields (exception/exc_cause, is_unique=0,
        // is_br=0, dst_rtype=RT_X, ldst_val=0, iq_type=INT) are already the defaults above.
        // An illegal instruction is a non-writing integer exception packet.
        u.exception = 1; u.exc_cause = 2;                 // Causes.illegal_instruction
        u.uopc = uopNOP; u.fu_code = FU_ALU; u.iq_type = IQT_INT;
        u.flush_on_commit = u.is_unique = 0;
        u.uses_ldq = u.uses_stq = u.is_amo = 0;
        u.fp_val = u.fp_single = u.frs3_en = 0;
        u.ldst_val = 0; u.dst_rtype = u.lrs1_rtype = u.lrs2_rtype = RT_X;
        break;
    }

    // bypassable: single-cycle ALU result -> eligible for fast issue wakeup
    // (core.scala fast_wakeup gates on bypassable && dst_rtype==RT_FIX && ldst_val).
    // True for single-cycle ALU ops (incl. LUI); false for mul/div (FU_MUL/DIV),
    // mem (FU_MEM), csr (FU_CSR), jumps (FU_JMP), and BRANCHES (fu_code==FU_ALU but
    // bypassable=N in decode.scala — they produce no register result to bypass).
    u.bypassable = (u.fu_code == FU_ALU && u.dst_rtype == RT_FIX && !u.is_br) ? 1 : 0;

    // Memory transfer controls are derived from the operation's encoding.
    // Other operations retain canonical unused values rather than a hardware
    // boolean minimizer's choices for don't-care outputs.
    u.mem_signed = ((inst >> 14) & 1) ? 0 : 1;
    if (u.mem_cmd == 5 || u.mem_cmd == 20)
        u.mem_size = static_cast<uint8_t>(((u.lrs2 != 0) << 1) | (u.lrs1 != 0));
    else
        u.mem_size = bits(inst, 13, 12);
    const uint8_t di = (u.ctrl.imm_sel == IS_S || u.ctrl.imm_sel == IS_B)
                       ? bits(inst, 11, 7) : bits(inst, 24, 20);
    u.imm_packed = (static_cast<uint32_t>(bits(inst, 31, 25)) << 13) |
                   (static_cast<uint32_t>(di) << 8) | bits(inst, 19, 12);
    // checkExceptions priority mux (interrupt / debug-breakpoint / breakpoint /
    // page-fault / access / illegal).  The frontend exception bits qualify the
    // exception even when the fetch-buffer entry itself carries no predecoded
    // `exception` bit.
    const bool decoded_illegal = u.exception != 0;
    u.exception = static_cast<uint8_t>(
        upstream_exception || u.bp_debug_if || u.bp_xcpt_if ||
        u.xcpt_pf_if || u.xcpt_ae_if || decoded_illegal);
    u.exc_cause = u.bp_debug_if ? 14 : u.bp_xcpt_if ? 3 :
                  u.xcpt_pf_if ? 12 : u.xcpt_ae_if ? 1 : 2;
    if (upstream_exception) {
        u.exception = 1;
        u.exc_cause = upstream_cause;
    }
}

namespace {
// These are precisely the fields written by boom_decode, excluding the
// exception priority mux. PC, FTQ/ROB identity, prediction and rename state
// must remain those of the current offered packet, even on a cache hit.
#define BOOM_STATIC_DECODE_FIELDS(X) \
    X(uopc) X(iq_type) X(fu_code) X(ctrl) X(is_br) X(is_jalr) X(is_jal) \
    X(imm_packed) X(csr_addr) X(bypassable) X(mem_cmd) X(mem_size) X(mem_signed) \
    X(is_fence) X(is_fencei) X(is_amo) X(uses_ldq) X(uses_stq) X(is_sys_pc2epc) \
    X(is_unique) X(flush_on_commit) X(ldst) X(lrs1) X(lrs2) X(lrs3) X(ldst_val) \
    X(dst_rtype) X(lrs1_rtype) X(lrs2_rtype) X(frs3_en) X(fp_val) X(fp_single)
struct StaticDecode {
#define FIELD(name) decltype(MicroOp::name) name{};
    BOOM_STATIC_DECODE_FIELDS(FIELD)
#undef FIELD
    bool illegal = false;
    void capture(const MicroOp& u) {
#define CAPTURE(name) name = u.name;
        BOOM_STATIC_DECODE_FIELDS(CAPTURE)
#undef CAPTURE
        illegal = u.exception != 0;
    }
    void apply(MicroOp& u) const {
#define APPLY(name) u.name = name;
        BOOM_STATIC_DECODE_FIELDS(APPLY)
#undef APPLY
    }
};
#undef BOOM_STATIC_DECODE_FIELDS

// Some decoder fields intentionally retain their input on other opcodes.
// Include them in the key instead of silently resetting invalid payloads.
std::uint64_t decode_passthrough(const MicroOp& u) {
    return std::uint64_t(u.flush_on_commit) | (std::uint64_t(u.fp_single) << 8) |
        (std::uint64_t(u.fp_val) << 16) | (std::uint64_t(u.frs3_en) << 24) |
        (std::uint64_t(u.is_amo) << 32) | (std::uint64_t(u.is_fence) << 40) |
        (std::uint64_t(u.is_fencei) << 48) | (std::uint64_t(u.is_unique) << 56);
}
struct StaticDecodeMemo {
    std::uint32_t inst = 0;
    std::uint16_t csr_addr = 0;
    std::uint64_t passthrough = 0;
    StaticDecode decoded{};
    bool valid = false;
};
thread_local StaticDecodeMemo static_decode_memo[256];
}  // namespace

void boom_decode_cached(MicroOp& u) {
    static const bool enabled = [] {
        const char* setting = std::getenv("SYSMODEL_STATIC_DECODE_CACHE");
        return setting == nullptr || std::strcmp(setting, "0") != 0;
    }();
    if (!enabled) { boom_decode(u); return; }
    const bool upstream_exception = u.exception != 0;
    const std::uint64_t upstream_cause = u.exc_cause;
    const std::uint64_t passthrough = decode_passthrough(u);
    auto& entry = static_decode_memo[(u.inst ^ (u.inst >> 10) ^ (u.inst >> 20)) & 255u];
    if (!entry.valid || entry.inst != u.inst || entry.csr_addr != u.csr_addr ||
        entry.passthrough != passthrough) {
        MicroOp instruction = u;
        instruction.exception = 0;
        instruction.exc_cause = 0;
        instruction.bp_debug_if = instruction.bp_xcpt_if = 0;
        instruction.xcpt_pf_if = instruction.xcpt_ae_if = 0;
        boom_decode(instruction);
        entry.inst = u.inst;
        entry.csr_addr = u.csr_addr;
        entry.passthrough = passthrough;
        entry.decoded.capture(instruction);
        entry.valid = true;
    }
    entry.decoded.apply(u);
    u.exception = static_cast<std::uint8_t>(upstream_exception || u.bp_debug_if ||
        u.bp_xcpt_if || u.xcpt_pf_if || u.xcpt_ae_if || entry.decoded.illegal);
    u.exc_cause = u.bp_debug_if ? 14 : u.bp_xcpt_if ? 3 : u.xcpt_pf_if ? 12 : u.xcpt_ae_if ? 1 : 2;
    if (upstream_exception) { u.exception = 1; u.exc_cause = upstream_cause; }
}
