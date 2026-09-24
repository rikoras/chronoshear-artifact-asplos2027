#pragma once
// ==========================================================================
// SoftFloat-backed FP execution for the rocket guider (M2, 2026-08-15).
//
// Computes the IEEE result + fflags of every FP operation the rocket-rc DUT
// can issue, in the IEEE domain (values enter/leave the guider's FP RF as
// IEEE bits; the recFN view is derived at the write point). Semantics follow
// the RISC-V F/D spec as implemented by rocket-chip tile/FPU.scala:
//   - FPToFP  (fastpipe): fsgnj*, fmin/fmax, fcvt.s.d / fcvt.d.s
//   - FPUFMAPipe (sfma/dfma): fadd/fsub/fmul/fmadd/fmsub/fnmsub/fnmadd
//   - IntToFP (ifpu): fcvt.{s,d}.{w,wu,l,lu}, fmv.w.x / fmv.d.x
//   - FPToInt (fpiu): fcvt.{w,wu,l,lu}.{s,d}, fmv.x.{w,d}, fclass, feq/flt/fle
//   - DivSqrt: fdiv/fsqrt (latency maintained by the calling microarchitecture model)
//
// Flag encoding: RISC-V fflags bit i == softfloat_flag_* bit i
// (NX=1, UF=2, OF=4, DZ=8, NV=16) — no translation needed.
// Rounding: RISC-V frm 0..4 -> softfloat_round_{near_even,minMag,min,max,
// near_maxMag}. rm==7 (DYN) must be resolved to fcsr.frm by the CALLER
// (FPU.scala fuInput: rm := Mux(inst(14,12)===7, io.fcsr_rm, inst(14,12))).
// ==========================================================================

#include <cstdint>

extern "C" {
#include "softfloat.h"
}

namespace sfp {

struct FpRes {
    uint64_t ieee;   // result bits (FLEN view; singles NaN-boxed by caller if stored)
    uint8_t  exc;    // RISC-V fflags accrued by this op
};

inline uint_fast8_t rm_to_softfloat(uint32_t rm) {
    switch (rm & 7) {
    case 0: return softfloat_round_near_even;
    case 1: return softfloat_round_minMag;
    case 2: return softfloat_round_min;
    case 3: return softfloat_round_max;
    case 4: return softfloat_round_near_maxMag;
    default: return softfloat_round_near_even;   // 5/6 illegal; FPU.scala:io.illegal_rm
    }
}

// RISC-V NaN-boxing: a single stored in an FLEN=64 register is valid only if
// bits 63:32 are all ones; otherwise the input is treated as the canonical
// qNaN (spec §"NaN Boxing of Narrower Values"; rocket unboxes the same way).
inline uint32_t unbox32(uint64_t v) {
    return ((v >> 32) == 0xFFFFFFFFu) ? (uint32_t)v : 0x7FC00000u;
}
inline uint64_t box32(uint32_t v) { return 0xFFFFFFFF00000000ULL | v; }

inline bool is_nan32(uint32_t f)  { return ((f >> 23) & 0xFF) == 0xFF && (f & 0x7FFFFF); }
inline bool is_snan32(uint32_t f) { return is_nan32(f) && !((f >> 22) & 1); }
inline bool is_nan64(uint64_t f)  { return ((f >> 52) & 0x7FF) == 0x7FF && (f & 0xFFFFFFFFFFFFFULL); }
inline bool is_snan64(uint64_t f) { return is_nan64(f) && !((f >> 51) & 1); }
constexpr uint32_t QNAN32 = 0x7FC00000u;
constexpr uint64_t QNAN64 = 0x7FF8000000000000ULL;

// Run one softfloat op with the given rounding mode; capture flags.
template <typename Fn>
inline FpRes run(uint32_t rm, Fn&& fn) {
    softfloat_roundingMode = rm_to_softfloat(rm);
    softfloat_exceptionFlags = 0;
    uint64_t v = fn();
    return FpRes{v, (uint8_t)(softfloat_exceptionFlags & 0x1F)};
}

// ---- FMA pipe (FPUFMAPipe): opc = major opcode, funct5 = inst[31:27] ------
// fadd/fsub/fmul come through OP-FP funct5 0x00/0x01/0x02; the four fused ops
// come through their own major opcodes 0x43/0x47/0x4B/0x4F (RISC-V spec).
// Fused sign variants (spec table): fmadd  a*b+c ; fmsub  a*b-c ;
// fnmsub -(a*b)+c ; fnmadd -(a*b)-c.
inline FpRes fma_op32(uint32_t inst, uint32_t rm, uint32_t a, uint32_t b, uint32_t c) {
    uint32_t opc = inst & 0x7F;
    return run(rm, [&]() -> uint64_t {
        float32_t fa{a}, fb{b}, fc{c};
        float32_t r;
        if (opc == 0x53) {                    // OP-FP: add/sub/mul
            uint32_t f5 = inst >> 27;
            if (f5 == 0x00)      r = f32_add(fa, fb);
            else if (f5 == 0x01) r = f32_sub(fa, fb);
            else                 r = f32_mul(fa, fb);
        } else {
            float32_t na{a ^ 0x80000000u}, nc{c ^ 0x80000000u};
            switch (opc) {
            case 0x43: r = f32_mulAdd(fa, fb, fc); break;          // fmadd
            case 0x47: r = f32_mulAdd(fa, fb, nc); break;          // fmsub
            case 0x4B: r = f32_mulAdd(na, fb, fc); break;          // fnmsub
            default:   r = f32_mulAdd(na, fb, nc); break;          // fnmadd (0x4F)
            }
        }
        return r.v;
    });
}
inline FpRes fma_op64(uint32_t inst, uint32_t rm, uint64_t a, uint64_t b, uint64_t c) {
    uint32_t opc = inst & 0x7F;
    return run(rm, [&]() -> uint64_t {
        float64_t fa{a}, fb{b}, fc{c};
        float64_t r;
        if (opc == 0x53) {
            uint32_t f5 = inst >> 27;
            if (f5 == 0x00)      r = f64_add(fa, fb);
            else if (f5 == 0x01) r = f64_sub(fa, fb);
            else                 r = f64_mul(fa, fb);
        } else {
            float64_t na{a ^ 0x8000000000000000ULL}, nc{c ^ 0x8000000000000000ULL};
            switch (opc) {
            case 0x43: r = f64_mulAdd(fa, fb, fc); break;
            case 0x47: r = f64_mulAdd(fa, fb, nc); break;
            case 0x4B: r = f64_mulAdd(na, fb, fc); break;
            default:   r = f64_mulAdd(na, fb, nc); break;
            }
        }
        return r.v;
    });
}

// ---- fastpipe (FPToFP): fsgnj*/fmin/fmax/fcvt between formats -------------
inline FpRes fastpipe32(uint32_t inst, uint32_t rm, uint32_t a, uint32_t b) {
    uint32_t f5 = inst >> 27, rmf = (inst >> 12) & 7;
    if (f5 == 0x04) {                          // fsgnj / fsgnjn / fsgnjx
        uint32_t s = (rmf == 0) ? (b & 0x80000000u)
                   : (rmf == 1) ? (~b & 0x80000000u)
                                : ((a ^ b) & 0x80000000u);
        return FpRes{(a & 0x7FFFFFFFu) | s, 0};
    }
    if (f5 == 0x05) {                          // fmin / fmax (F spec 2.2 semantics)
        uint8_t exc = (is_snan32(a) || is_snan32(b)) ? 0x10 : 0;
        if (is_nan32(a) && is_nan32(b)) return FpRes{QNAN32, exc};
        if (is_nan32(a)) return FpRes{b, exc};
        if (is_nan32(b)) return FpRes{a, exc};
        softfloat_exceptionFlags = 0;
        bool a_lt = f32_lt_quiet(float32_t{a}, float32_t{b});
        bool eq_zero = ((a | b) & 0x7FFFFFFFu) == 0;
        bool pick_a;
        if (rmf == 0)  pick_a = a_lt || (eq_zero && (a >> 31));           // fmin: -0 < +0
        else           pick_a = (!a_lt && !(eq_zero && (a >> 31)));       // fmax
        return FpRes{pick_a ? a : b, exc};
    }
    // f5 == 0x08: fcvt.s.d (rs2=1 -> src double)  [handled in the 64 variant when
    // typeTagIn==D]; fcvt with same width doesn't exist.
    (void)rm; (void)b;
    return FpRes{a, 0};
}
inline FpRes fastpipe64(uint32_t inst, uint32_t rm, uint64_t a, uint64_t b) {
    uint32_t f5 = inst >> 27, rmf = (inst >> 12) & 7;
    if (f5 == 0x04) {
        uint64_t s = (rmf == 0) ? (b & 0x8000000000000000ULL)
                   : (rmf == 1) ? (~b & 0x8000000000000000ULL)
                                : ((a ^ b) & 0x8000000000000000ULL);
        return FpRes{(a & 0x7FFFFFFFFFFFFFFFULL) | s, 0};
    }
    if (f5 == 0x05) {
        uint8_t exc = (is_snan64(a) || is_snan64(b)) ? 0x10 : 0;
        if (is_nan64(a) && is_nan64(b)) return FpRes{QNAN64, exc};
        if (is_nan64(a)) return FpRes{b, exc};
        if (is_nan64(b)) return FpRes{a, exc};
        bool a_lt = f64_lt_quiet(float64_t{a}, float64_t{b});
        bool eq_zero = ((a | b) & 0x7FFFFFFFFFFFFFFFULL) == 0;
        bool pick_a;
        if (rmf == 0)  pick_a = a_lt || (eq_zero && (a >> 63));
        else           pick_a = (!a_lt && !(eq_zero && (a >> 63)));
        return FpRes{pick_a ? a : b, exc};
    }
    (void)rm; (void)b;
    return FpRes{a, 0};
}
// fcvt.s.d (double -> single, rounded) and fcvt.d.s (single -> double, exact).
inline FpRes cvt_d_to_s(uint32_t rm, uint64_t a) {
    return run(rm, [&]() -> uint64_t { return f64_to_f32(float64_t{a}).v; });
}
inline FpRes cvt_s_to_d(uint32_t rm, uint32_t a) {
    return run(rm, [&]() -> uint64_t { return f32_to_f64(float32_t{a}).v; });
}

// ---- ifpu (IntToFP) -------------------------------------------------------
// funct5 0x1A: fcvt.fmt.int (rs2 field: 0=w,1=wu,2=l,3=lu); 0x1E: fmv (raw).
inline FpRes int_to_fp(uint32_t inst, uint32_t rm, bool to_double, uint64_t rs1) {
    uint32_t f5 = inst >> 27, cvtsel = (inst >> 20) & 3;
    if (f5 == 0x1E) return FpRes{to_double ? rs1 : (uint64_t)(uint32_t)rs1, 0};  // fmv.d.x / fmv.w.x
    return run(rm, [&]() -> uint64_t {
        if (to_double) {
            float64_t r;
            switch (cvtsel) {
            case 0: r = i32_to_f64((int32_t)rs1); break;
            case 1: r = ui32_to_f64((uint32_t)rs1); break;
            case 2: r = i64_to_f64((int64_t)rs1); break;
            default: r = ui64_to_f64(rs1); break;
            }
            return r.v;
        } else {
            float32_t r;
            switch (cvtsel) {
            case 0: r = i32_to_f32((int32_t)rs1); break;
            case 1: r = ui32_to_f32((uint32_t)rs1); break;
            case 2: r = i64_to_f32((int64_t)rs1); break;
            default: r = ui64_to_f32(rs1); break;
            }
            return r.v;
        }
    });
}

// ---- fpiu (FPToInt): result goes to the INTEGER register file -------------
inline uint32_t fclass32(uint32_t f) {
    bool sign = f >> 31; uint32_t exp = (f >> 23) & 0xFF, sig = f & 0x7FFFFF;
    if (exp == 0xFF) {
        if (sig) return ((sig >> 22) & 1) ? (1u << 9) : (1u << 8);   // qNaN / sNaN
        return sign ? (1u << 0) : (1u << 7);
    }
    if (exp == 0) {
        if (!sig) return sign ? (1u << 3) : (1u << 4);
        return sign ? (1u << 2) : (1u << 5);
    }
    return sign ? (1u << 1) : (1u << 6);
}
inline uint32_t fclass64(uint64_t f) {
    bool sign = f >> 63; uint32_t exp = (f >> 52) & 0x7FF; uint64_t sig = f & 0xFFFFFFFFFFFFFULL;
    if (exp == 0x7FF) {
        if (sig) return ((sig >> 51) & 1) ? (1u << 9) : (1u << 8);
        return sign ? (1u << 0) : (1u << 7);
    }
    if (exp == 0) {
        if (!sig) return sign ? (1u << 3) : (1u << 4);
        return sign ? (1u << 2) : (1u << 5);
    }
    return sign ? (1u << 1) : (1u << 6);
}

// funct5 0x14: feq/flt/fle (rm field: 2/1/0); 0x18: fcvt.int.fmt; 0x1C: fmv.x/fclass.
inline FpRes fp_to_int32(uint32_t inst, uint32_t rm, uint32_t a, uint32_t b) {
    uint32_t f5 = inst >> 27, rmf = (inst >> 12) & 7, cvtsel = (inst >> 20) & 3;
    switch (f5) {
    case 0x14:
        return run(0, [&]() -> uint64_t {
            float32_t fa{a}, fb{b};
            bool r = (rmf == 2) ? f32_eq(fa, fb)
                   : (rmf == 1) ? f32_lt(fa, fb)
                                : f32_le(fa, fb);
            return r ? 1 : 0;
        });
    case 0x18:
        return run(rm, [&]() -> uint64_t {
            float32_t fa{a};
            switch (cvtsel) {
            case 0: return (uint64_t)(int64_t)f32_to_i32(fa, softfloat_roundingMode, true);
            case 1: return (uint64_t)(int64_t)(int32_t)f32_to_ui32(fa, softfloat_roundingMode, true);
            case 2: return (uint64_t)f32_to_i64(fa, softfloat_roundingMode, true);
            default: return f32_to_ui64(fa, softfloat_roundingMode, true);
            }
        });
    default:  // 0x1C: fmv.x.w (rm 0, sign-extended raw) / fclass (rm 1)
        if (rmf == 1) return FpRes{fclass32(a), 0};
        return FpRes{(uint64_t)(int64_t)(int32_t)a, 0};
    }
}
inline FpRes fp_to_int64(uint32_t inst, uint32_t rm, uint64_t a, uint64_t b) {
    uint32_t f5 = inst >> 27, rmf = (inst >> 12) & 7, cvtsel = (inst >> 20) & 3;
    switch (f5) {
    case 0x14:
        return run(0, [&]() -> uint64_t {
            float64_t fa{a}, fb{b};
            bool r = (rmf == 2) ? f64_eq(fa, fb)
                   : (rmf == 1) ? f64_lt(fa, fb)
                                : f64_le(fa, fb);
            return r ? 1 : 0;
        });
    case 0x18:
        return run(rm, [&]() -> uint64_t {
            float64_t fa{a};
            switch (cvtsel) {
            case 0: return (uint64_t)(int64_t)f64_to_i32(fa, softfloat_roundingMode, true);
            case 1: return (uint64_t)(int64_t)(int32_t)f64_to_ui32(fa, softfloat_roundingMode, true);
            case 2: return (uint64_t)f64_to_i64(fa, softfloat_roundingMode, true);
            default: return f64_to_ui64(fa, softfloat_roundingMode, true);
            }
        });
    default:
        if (rmf == 1) return FpRes{fclass64(a), 0};
        return FpRes{a, 0};                        // fmv.x.d
    }
}

// ---- div / sqrt (values; latency handled by the caller) -------------------
inline FpRes div_op32(uint32_t rm, uint32_t a, uint32_t b) {
    return run(rm, [&]() -> uint64_t { return f32_div(float32_t{a}, float32_t{b}).v; });
}
inline FpRes div_op64(uint32_t rm, uint64_t a, uint64_t b) {
    return run(rm, [&]() -> uint64_t { return f64_div(float64_t{a}, float64_t{b}).v; });
}
inline FpRes sqrt_op32(uint32_t rm, uint32_t a) {
    return run(rm, [&]() -> uint64_t { return f32_sqrt(float32_t{a}).v; });
}
inline FpRes sqrt_op64(uint32_t rm, uint64_t a) {
    return run(rm, [&]() -> uint64_t { return f64_sqrt(float64_t{a}).v; });
}

// Recoded images are an interchange format at the observation boundary.
// The codecs use an independent software format implementation.
} // namespace sfp

#include "recoded_float.h"

namespace sfp {
using rec_t=chisa::fp_format::Word;
inline uint64_t hf_recfn_from_fn(int exponent_bits,int precision,uint64_t value,rec_t* wide) {
    const auto result=chisa::fp_format::encode(exponent_bits,precision,value);
    if(wide) *wide=result;
    return static_cast<uint64_t>(result);
}
inline uint64_t rec33_from_fn32(uint32_t value) {return static_cast<uint64_t>(chisa::fp_format::encode(8,24,value));}
inline rec_t rec65_from_fn64(uint64_t value) {return chisa::fp_format::encode(11,53,value);}
inline uint64_t hf_fn_from_recfn(int exponent_bits,int precision,rec_t value) {return chisa::fp_format::decode(exponent_bits,precision,value);}
inline uint32_t fn32_from_rec33(uint64_t value) {return static_cast<uint32_t>(chisa::fp_format::decode(8,24,value));}
inline uint64_t fn64_from_rec65(rec_t value) {return chisa::fp_format::decode(11,53,value);}
inline bool rec65_is_nan(rec_t value) {return chisa::fp_format::is_nan(value);}
inline bool rec65_isbox(rec_t value) {return chisa::fp_format::is_boxed_single(value);}
inline rec_t hf_priv_box65(rec_t wide,uint64_t narrow) {return chisa::fp_format::embed_single(wide,narrow);}
inline rec_t hf_recode64(uint64_t value,bool single) {return chisa::fp_format::encode_register(value,single);}
inline rec_t hf_pub_box_s(uint64_t value) {return chisa::fp_format::box_single(value);}
inline uint64_t s_lane_view(rec_t value) {return chisa::fp_format::read_single(value);}
inline uint64_t ieee64_view(rec_t value) {return chisa::fp_format::read_register(value);}
} // namespace sfp
