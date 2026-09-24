// Rocket FPU (tile/FPU.scala) for the locked DefaultConfig: single and double
// precision, sfmaLatency 3, dfmaLatency 4, iterative divide/sqrt, no clock
// gating. Native execution supports the core interface; the original FPU's
// CP ports are unconnected in the locked tile and are not implemented here.
//
// Event driven: an idle FPU (no instruction in any stage, no divide in
// flight, no load write-back) costs a handful of flag tests per cycle.  Each
// arithmetic result is computed once, at the clock edge where the hardware
// register that holds it is written.
#pragma once
#include <cstdint>
#include "floating_point.h"

namespace chisa::rocket_model {

using hf::u128;

struct FpuCtrlSigs {
  bool ldst, wen, ren1, ren2, ren3, swap12, swap23;
  uint8_t typeTagIn, typeTagOut;
  bool fromint, toint, fastpipe, fma, div, sqrt, wflags;
};

struct FpInput {
  FpuCtrlSigs c;
  uint8_t rm, fmaCmd, typ, fmt;
  u128 in1, in2, in3;   // 65 bits
};

struct FpuIn {
  uint32_t inst;
  uint64_t fromint_data;
  uint8_t fcsr_rm;
  bool dmem_resp_val;
  uint8_t dmem_resp_type, dmem_resp_tag;
  uint64_t dmem_resp_data;
  bool valid, killx, killm;
  bool reset;
};

struct FpuWires {
  FpuCtrlSigs dec;
  bool fcsr_flags_valid;
  uint8_t fcsr_flags;
  bool fcsr_rdy, nack_mem, illegal_rm;
  uint64_t store_data, toint_data;
  bool sboard_set, sboard_clr;
  uint8_t sboard_clra;
  // decisions carried to commit
  bool idle, state_idle;
  bool killm, killx;
  bool divSqrt_wen;
  uint8_t divSqrt_typeTag;
  u128 divSqrt_wdata;
  uint8_t divSqrt_flags;
  bool divSqrt_inFlight;
  uint8_t waddr, wtypeTag;
  u128 wdata;
  uint8_t wexc;
  bool regfile_write_pipe;
};

struct FmaSlot {
  bool valid = false, valid_stage0 = false, validout = false, out_valid = false;
  FpInput in = {};
  hf::PreMul pre = {};
  uint8_t rm0 = 0;
  hf::Raw raw = {};
  bool invalidExc = false;
  uint8_t rm1 = 0;
  u128 out_data = 0;     // dfma only: the extra output stage
  uint8_t out_exc = 0;
};

class Fpu {
 public:
  void set_architectural_mode(bool enabled) { architectural_mode_ = enabled; }
  bool architectural_mode() const { return architectural_mode_; }
  // Architectural FLEN=64 contents, with the standard NaN box for FP32.
  // This reverses recoding/swizzling; raw 65-bit helpers are not registers
  // in the ISA-visible floating-point state.
  uint64_t architectural_rf(unsigned index) const;
  // The core feedback uses only FPU registers. A system scheduler may call
  // evaluate_state before the core, then evaluate_inputs with the resulting
  // core command using the same Wires. Both stages are read-only; commit once.
  void evaluate_state(FpuWires& w) const;
  void evaluate_inputs(const FpuIn& in, FpuWires& w) const;
  void evaluate(const FpuIn& in, FpuWires& w) const;
  void commit(const FpuIn& in, const FpuWires& w);
  template <class S> void export_image(S& s) const;
  static FpuCtrlSigs decode(uint32_t inst);
  static bool is_fp_opcode(uint32_t inst);

  // registers
  bool ex_reg_valid_ = false;
  uint32_t ex_reg_inst_ = 0;
  FpuCtrlSigs ex_reg_ctrl_ = {};
  uint8_t ex_ra_[3] = {};
  bool load_wb_ = false;
  uint8_t load_wb_typeTag_ = 0;
  uint64_t load_wb_data_ = 0;
  uint8_t load_wb_tag_ = 0;
  bool mem_reg_valid_ = false;
  uint32_t mem_reg_inst_ = 0;
  bool wb_reg_valid_ = false;
  FpuCtrlSigs mem_ctrl_ = {}, wb_ctrl_ = {};
  u128 regfile_[32] = {};
  // FPToInt: captured input and its (fixed) outputs
  bool fpiu_valid_ = false;
  FpInput fpiu_in_ = {};
  uint64_t fpiu_store_ = 0, fpiu_toint_ = 0;
  uint8_t fpiu_exc_ = 0;
  bool fpiu_lt_ = false;
  // IntToFP / FPToFP: stage 1 (captured input) and stage 2 (result)
  bool ifpu_v1_ = false, ifpu_v2_ = false;
  FpInput ifpu_in_ = {};
  uint64_t ifpu_in1_ = 0;
  u128 ifpu_data_ = 0;
  uint8_t ifpu_exc_ = 0;
  bool fpmu_v1_ = false, fpmu_v2_ = false;
  FpInput fpmu_in_ = {};
  u128 fpmu_data_ = 0;
  uint8_t fpmu_exc_ = 0;
  FmaSlot sfma_, dfma_;
  uint8_t wen_ = 0;
  struct WbInfo { uint8_t rd, typeTag, pipeid; bool cp; } wbInfo_[3] = {};
  bool write_port_busy_ = false;
  uint8_t wb_toint_exc_ = 0;
  bool sboard_set_reg_ = false;
  uint8_t divSqrt_waddr_ = 0;
  bool divSqrt_killed_ = true;
  hf::DivSqrtState divS_, divD_;

 private:
  bool architectural_mode_ = false;
  // Pure decode memo, separate from architectural state and oracle export.
  // The complete instruction is the key, including inactive cycle payloads.
  // Reset and dynamic rounding/kill controls do not change static decode.
  mutable bool decode_cache_valid_ = false;
  mutable uint32_t decode_cache_inst_ = 0;
  mutable FpuCtrlSigs decode_cache_ctrl_ = {};
};

template <class S>
void Fpu::export_image(S& s) const {
  if (architectural_mode_) return;
  s.dfma_fma_roundRawFNToRecFN_io_in_b_isInf = dfma_.raw.isInf;
  s.dfma_fma_roundRawFNToRecFN_io_in_b_isNaN = dfma_.raw.isNaN;
  s.dfma_fma_roundRawFNToRecFN_io_in_b_isZero = dfma_.raw.isZero;
  s.dfma_fma_roundRawFNToRecFN_io_in_b_sExp = static_cast<uint16_t>(dfma_.raw.sExp) & 0x1fff;
  s.dfma_fma_roundRawFNToRecFN_io_in_b_sig = static_cast<uint64_t>(dfma_.raw.sig);
  s.dfma_fma_roundRawFNToRecFN_io_in_b_sign = dfma_.raw.sign;
  s.dfma_fma_roundRawFNToRecFN_io_invalidExc_b = dfma_.invalidExc;
  s.sfma_fma_roundRawFNToRecFN_io_in_b_isInf = sfma_.raw.isInf;
  s.sfma_fma_roundRawFNToRecFN_io_in_b_isNaN = sfma_.raw.isNaN;
  s.sfma_fma_roundRawFNToRecFN_io_in_b_isZero = sfma_.raw.isZero;
  s.sfma_fma_roundRawFNToRecFN_io_in_b_sExp = static_cast<uint16_t>(sfma_.raw.sExp) & 0x3ff;
  s.sfma_fma_roundRawFNToRecFN_io_in_b_sig = static_cast<uint32_t>(sfma_.raw.sig);
  s.sfma_fma_roundRawFNToRecFN_io_in_b_sign = sfma_.raw.sign;
  s.sfma_fma_roundRawFNToRecFN_io_invalidExc_b = sfma_.invalidExc;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_inReady = divS_.inReady;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_isInf_Z = divS_.isInf_Z;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_isNaN_Z = divS_.isNaN_Z;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_isZero_Z = divS_.isZero_Z;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_majorExc_Z = divS_.majorExc_Z;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_notZeroRem_Z = divS_.notZeroRem_Z;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_rawOutValid = divS_.rawOutValid;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_sExp_Z = static_cast<uint16_t>(divS_.sExp_Z) & 0x3ff;
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_sigX_Z = static_cast<uint32_t>(divS_.sigX_Z);
  s.divSqrt_divSqrtRecFNToRaw_divSqrtRawFN_sign_Z = divS_.sign_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_inReady = divD_.inReady;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_isInf_Z = divD_.isInf_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_isNaN_Z = divD_.isNaN_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_isZero_Z = divD_.isZero_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_majorExc_Z = divD_.majorExc_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_notZeroRem_Z = divD_.notZeroRem_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_rawOutValid = divD_.rawOutValid;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_sExp_Z = static_cast<uint16_t>(divD_.sExp_Z) & 0x1fff;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_sigX_Z = divD_.sigX_Z;
  s.divSqrt_1_divSqrtRecFNToRaw_divSqrtRawFN_sign_Z = divD_.sign_Z;
  s.divSqrt_killed = divSqrt_killed_;
  s.ex_ra_0 = ex_ra_[0]; s.ex_ra_1 = ex_ra_[1]; s.ex_ra_2 = ex_ra_[2];
  s.ex_reg_ctrl_div = ex_reg_ctrl_.div;
  s.ex_reg_ctrl_fastpipe = ex_reg_ctrl_.fastpipe;
  s.ex_reg_ctrl_fma = ex_reg_ctrl_.fma;
  s.ex_reg_ctrl_fromint = ex_reg_ctrl_.fromint;
  s.ex_reg_ctrl_ren3 = ex_reg_ctrl_.ren3;
  s.ex_reg_ctrl_sqrt = ex_reg_ctrl_.sqrt;
  s.ex_reg_ctrl_swap23 = ex_reg_ctrl_.swap23;
  s.ex_reg_ctrl_toint = ex_reg_ctrl_.toint;
  s.ex_reg_ctrl_typeTagIn = ex_reg_ctrl_.typeTagIn;
  s.ex_reg_ctrl_typeTagOut = ex_reg_ctrl_.typeTagOut;
  s.ex_reg_ctrl_wflags = ex_reg_ctrl_.wflags;
  s.ex_reg_inst = ex_reg_inst_;
  s.ex_reg_valid = ex_reg_valid_;
  s.mem_reg_valid = mem_reg_valid_;
  s.wb_reg_valid = wb_reg_valid_;
  s.wen = wen_;
}

}  // namespace chisa::rocket_model
