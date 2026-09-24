#include "fpu.h"

#include <stdexcept>

#include "fp_decode.h"

namespace chisa::rocket_model {

using hf::u128;
using hf::mask128;
using hf::bits128;

namespace {

constexpr unsigned S_E = 8, S_S = 24, D_E = 11, D_S = 53;
constexpr u128 kDQNaN = (static_cast<u128>(7) << 61) | (static_cast<u128>(1) << 51);
constexpr u128 kSQNaN = (static_cast<u128>(7) << 29) | (static_cast<u128>(1) << 22);
constexpr u128 kM65 = (static_cast<u128>(1) << 65) - 1;
constexpr u128 kM33 = (static_cast<u128>(1) << 33) - 1;

inline bool d_is_nan(u128 x) { return chisa::fp_format::is_nan(x); }
inline bool d_is_snan(u128 x) { return d_is_nan(x) && !hf::bit(x, 51); }
inline bool s_is_nan(u128 x) { return bits128(x, 31, 29) == 7; }
inline bool is_box(u128 x) { return chisa::fp_format::is_boxed_single(x); }
inline u128 unswizzle(u128 x) { return chisa::fp_format::extract_single(x); }

inline u128 unsafe_convert(u128 value,unsigned from_e,unsigned from_p,unsigned to_e,unsigned to_p) {
  return chisa::fp_format::resize_unrounded(value,from_e,from_p,to_e,to_p);
}
inline u128 s_to_d(u128 x) { return unsafe_convert(x, S_E, S_S, D_E, D_S); }
inline u128 d_to_s(u128 x) { return unsafe_convert(x, D_E, D_S, S_E, S_S) & kM33; }

inline u128 swizzled_nan(u128 wide,u128 single) {return chisa::fp_format::embed_single(wide,static_cast<uint64_t>(single));}
inline u128 box_s(u128 y) { return swizzled_nan(kM65, y); }
inline u128 box_tag(u128 x, unsigned tag) { return (tag & 1) ? (x & kM65) : box_s(x); }
inline u128 sanitize_nan_d(u128 x) { return d_is_nan(x) ? (x & ~((static_cast<u128>(1) << 52) | (static_cast<u128>(1) << 60))) : x; }

// unbox(x, tag, exactType)
inline u128 unbox_none(u128 x, unsigned tag) {
  if (tag & 1) return x & kM65;
  return is_box(x) ? s_to_d(unswizzle(x)) : kDQNaN;
}
inline u128 unbox_s(u128 x) { return (unswizzle(x) | (is_box(x) ? 0 : kSQNaN)) & kM33; }
inline u128 unbox_d(u128 x) { return x & kM65; }

inline u128 recode(uint64_t value,unsigned tag) {return chisa::fp_format::encode_register(value,(tag&1)==0);}
inline uint64_t ieee_d(u128 value) {return chisa::fp_format::read_register(value);}

inline uint32_t classify(u128 value,unsigned e,unsigned p) {
  const auto raw=chisa::binary_float::unpack(e,p,value);
  if(raw.isNaN) return 1u<<(chisa::binary_float::signaling_nan(raw,p)?8:9);
  if(raw.isInf) return 1u<<(raw.sign?0:7);
  if(raw.isZero) return 1u<<(raw.sign?3:4);
  const bool subnormal=raw.sExp<((INT64_C(1)<<(e-1))+2);
  return 1u<<(subnormal?(raw.sign?2:5):(raw.sign?1:6));
}

inline uint8_t latency_mask(const FpuCtrlSigs& c, unsigned offset) {
  uint8_t m = 0;
  if (c.fastpipe) m |= 1u << (2 - offset);
  if (c.fromint) m |= 1u << (2 - offset);
  if (c.fma && c.typeTagOut == 0) m |= 1u << (3 - offset);
  if (c.fma && c.typeTagOut == 1) m |= 1u << (4 - offset);
  return m;
}
inline uint8_t pipe_id(const FpuCtrlSigs& c) {
  uint8_t id = 0;
  if (c.fromint) id |= 1;
  if (c.fma && c.typeTagOut == 0) id |= 2;
  if (c.fma && c.typeTagOut == 1) id |= 3;
  return id;
}

}  // namespace

bool Fpu::is_fp_opcode(uint32_t inst) {
  const unsigned op = inst & 0x7f;
  return op == 0x07 || op == 0x27 || op == 0x43 || op == 0x47 || op == 0x4b || op == 0x4f || op == 0x53;
}

uint64_t Fpu::architectural_rf(unsigned index) const {
  if (index >= 32) throw std::out_of_range("architectural FP register index");
  return ieee_d(regfile_[index] & kM65);
}

// Software operation routing. A bit-transfer instruction uses the full-width
// register path to preserve its payload; numerical single-precision operands
// use the checked binary32 unboxing path. Unused controls are canonical zeros.
FpuCtrlSigs Fpu::decode(uint32_t inst) {
  const auto decoded = decode_fp_instruction(inst);
  FpuCtrlSigs s{};
  if (!decoded.legal()) return s;
  s.typeTagIn = decoded.input_type;
  s.typeTagOut = decoded.output_type;
  switch (decoded.operation) {
    case FpOperation::Load:
      s.ldst = s.wen = true;
      break;
    case FpOperation::Store:
      s.ldst = s.ren2 = s.swap12 = s.toint = true;
      s.typeTagIn = 1;
      break;
    case FpOperation::MoveFromInteger:
      s.wen = s.fromint = true;
      // ifpu recode already produces a complete boxed register.
      s.typeTagOut = 1;
      break;
    case FpOperation::FromInteger:
      s.wen = s.fromint = s.wflags = true;
      break;
    case FpOperation::MoveToInteger:
      s.ren1 = s.toint = true;
      s.typeTagIn = 1;
      break;
    case FpOperation::Classify:
      s.ren1 = s.toint = true;
      break;
    case FpOperation::ToInteger:
      s.ren1 = s.toint = s.wflags = true;
      break;
    case FpOperation::Compare:
      s.ren1 = s.ren2 = s.toint = s.wflags = true;
      break;
    case FpOperation::SignInject: case FpOperation::MinMax:
      s.wen = s.ren1 = s.ren2 = s.fastpipe = true;
      s.wflags = decoded.operation == FpOperation::MinMax;
      break;
    case FpOperation::ConvertFormat:
      s.wen = s.ren1 = s.fastpipe = s.wflags = true;
      break;
    case FpOperation::Add: case FpOperation::Subtract:
      s.swap23 = true;  // use rs2 as the addend, with a unit multiplier
      [[fallthrough]];
    case FpOperation::Multiply: case FpOperation::FusedMultiplyAdd:
      s.wen = s.ren1 = s.ren2 = s.fma = s.wflags = true;
      s.ren3 = decoded.operation == FpOperation::FusedMultiplyAdd;
      break;
    case FpOperation::Divide:
      s.wen = s.ren1 = s.ren2 = s.div = s.wflags = true;
      break;
    case FpOperation::SquareRoot:
      s.wen = s.ren1 = s.sqrt = s.wflags = true;
      break;
    case FpOperation::Illegal: break;
  }
  return s;
}

namespace {

// FPToInt combinational block from its registered input.
struct FpiuOut { uint64_t store, toint; uint8_t exc; bool lt; };
FpiuOut fpiu_eval(const FpInput& in) {
  FpiuOut o;
  const unsigned tag = in.c.typeTagOut & 1;
  const uint64_t ie = ieee_d(in.in1);
  const uint64_t store = tag == 0 ? ((ie & 0xffffffffu) | ((ie & 0xffffffffu) << 32)) : ie;
  uint64_t toint = store;
  bool intType = in.fmt & 1;
  uint8_t exc = 0;
  const hf::Cmp cmp = hf::compare_recfn(D_E, D_S, in.in1 & kM65, in.in2 & kM65, !((in.rm >> 1) & 1));
  if (in.rm & 1) {
    const uint32_t cls = tag == 0 ? classify(d_to_s(in.in1), S_E, S_S) : classify(in.in1, D_E, D_S);
    toint = cls | ((store >> 32) << 32);
    intType = false;
  }
  if (in.c.wflags) {
    const unsigned lteq = (cmp.lt << 1) | cmp.eq;
    toint = static_cast<uint64_t>(((~in.rm) & lteq) != 0) | ((store >> 32) << 32);
    exc = cmp.flags;
    intType = false;
    if (!in.c.ren2) {
      const bool cvtType = (in.typ >> 1) & 1;
      intType = cvtType;
      const bool signedOut = !(in.typ & 1);
      const hf::ToInt conv = hf::recfn_to_in(D_E, D_S, 64, in.in1 & kM65, in.rm, signedOut);
      toint = conv.out;
      exc = static_cast<uint8_t>((((conv.intFlags >> 1) & 3) != 0) << 4) | (conv.intFlags & 1);
      if (!cvtType) {
        const hf::ToInt narrow = hf::recfn_to_in(D_E, D_S, 32, in.in1 & kM65, in.rm, signedOut);
        const bool excSign = hf::bit(in.in1, 64) && !d_is_nan(in.in1);
        const uint64_t excOut = (static_cast<uint64_t>(signedOut == excSign) << 31) | (!excSign ? 0x7fffffffu : 0);
        const bool invalid = ((conv.intFlags >> 2) & 1) || ((narrow.intFlags >> 1) & 1);
        if (invalid) toint = ((conv.out >> 32) << 32) | excOut;
        exc = static_cast<uint8_t>((invalid << 4) | (!invalid && (conv.intFlags & 1)));
      }
    }
  }
  o.store = store;
  o.toint = intType ? toint : static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(toint & 0xffffffffu)));
  o.exc = exc;
  o.lt = cmp.lt || (hf::bit(in.in1, 64) && !hf::bit(in.in2, 64));
  return o;
}

// IntToFP second-stage value from the stage-1 registers.
void ifpu_eval(const FpInput& in, uint64_t in1, u128& data, uint8_t& exc) {
  const unsigned tag = in.c.typeTagIn & 1;
  data = recode(in1, tag);
  exc = 0;
  if (in.c.wflags) {
    uint64_t intValue = in1;
    if (!((in.typ >> 1) & 1)) {
      const uint32_t small = static_cast<uint32_t>(in1);
      intValue = (in.typ & 1) ? static_cast<uint64_t>(small) : static_cast<uint64_t>(static_cast<int64_t>(static_cast<int32_t>(small)));
    }
    const bool signedIn = !(in.typ & 1);
    const hf::RoundOut rs = hf::in_to_recfn(64, S_E, S_S, signedIn, intValue, in.rm, true);
    const hf::RoundOut rd = hf::in_to_recfn(64, D_E, D_S, signedIn, intValue, in.rm, true);
    const u128 dataS = rs.out & kM33;
    const u128 dataD = sanitize_nan_d(rd.out & kM65);
    if (tag == 0) { data = ((dataD >> 33) << 33) | dataS; exc = rs.flags; }
    else { data = dataD; exc = rd.flags; }
  }
}

// FPToFP second-stage value from the stage-1 registers.
void fpmu_eval(const FpInput& in, bool lt, u128& data, uint8_t& exc) {
  const u128 in1 = in.in1 & kM65, in2 = in.in2 & kM65;
  const u128 signNum = ((in.rm >> 1) & 1) ? (in1 ^ in2) : ((in.rm & 1) ? (~in2 & kM65) : in2);
  u128 fsgnj_data = (static_cast<u128>(hf::bit(signNum, 64)) << 64) | bits128(in1, 63, 0);
  uint8_t fsgnj_exc = 0;
  if (in.c.wflags) {
    const bool isnan1 = d_is_nan(in1), isnan2 = d_is_nan(in2);
    const bool isInvalid = d_is_snan(in1) || d_is_snan(in2);
    const bool isNaNOut = isnan1 && isnan2;
    const bool isLHS = isnan2 || (((in.rm & 1) != 0) != lt && !isnan1);
    fsgnj_exc = static_cast<uint8_t>(isInvalid << 4);
    fsgnj_data = isNaNOut ? kDQNaN : (isLHS ? in1 : in2);
  }
  const unsigned outTag = in.c.typeTagOut & 1;
  if (in.c.wflags && !in.c.ren2) {
    fsgnj_data = d_is_nan(in1) ? kDQNaN : in1;
    fsgnj_exc = static_cast<uint8_t>(d_is_snan(in1) << 4);
  }
  data = fsgnj_data;
  exc = fsgnj_exc;
  if (outTag == 0) data = ((fsgnj_data >> 33) << 33) | d_to_s(fsgnj_data);
  if (in.c.wflags && !in.c.ren2 && outTag == 0) {
    const hf::RoundOut r = hf::recfn_to_recfn(D_E, D_S, S_E, S_S, in1, in.rm, true);
    data = ((fsgnj_data >> 33) << 33) | (r.out & kM33);
    exc = r.flags;
  }
}

}  // namespace

void Fpu::evaluate_state(FpuWires& w) const {
  // ---- idle fast path: nothing in any stage, nothing pending ----
  const bool div_busy = divS_.cycleNum != 0 || divD_.cycleNum != 0;
  const bool pipes_busy = sfma_.valid || sfma_.valid_stage0 || sfma_.validout || dfma_.valid || dfma_.valid_stage0 ||
                          dfma_.validout || dfma_.out_valid || ifpu_v1_ || ifpu_v2_ || fpmu_v1_ || fpmu_v2_ || fpiu_valid_;
  const bool settled_dividers = divS_.inReady && divD_.inReady && !divS_.rawOutValid && !divD_.rawOutValid;
  w.state_idle = !ex_reg_valid_ && !mem_reg_valid_ && !wb_reg_valid_ && !load_wb_ &&
           wen_ == 0 && (!divSqrt_killed_ || (architectural_mode_ && settled_dividers)) && !div_busy && !pipes_busy;
  if (architectural_mode_ && w.state_idle) {
    w = FpuWires{};
    w.state_idle = true;
    w.fcsr_rdy = true;
    w.nack_mem = write_port_busy_;
    return;
  }
  w.store_data = fpiu_store_;
  w.toint_data = fpiu_toint_;
  w.sboard_clra = wbInfo_[0].rd;
  if (w.state_idle) {
    w.fcsr_flags_valid = false; w.fcsr_flags = 0;
    w.fcsr_rdy = true;
    w.nack_mem = write_port_busy_;
    w.sboard_set = false; w.sboard_clr = false;
    w.divSqrt_wen = false; w.divSqrt_inFlight = false;
    w.regfile_write_pipe = false;
    return;
  }

  // ---- divide / square root completion ----
  bool divSqrt_wen = false;
  u128 divSqrt_wdata = 0;
  uint8_t divSqrt_flags = 0, divSqrt_typeTag = 0;
  if (divS_.rawOutValid) {
    const hf::DivSqrtOut o = hf::div_sqrt_outputs(S_E, S_S, divS_);
    const hf::RoundOut r = hf::round_raw_to_recfn(S_E, S_S, o.invalidExc, o.infiniteExc, o.rawOut, o.rmOut, true);
    divSqrt_wen = !divSqrt_killed_; divSqrt_wdata = r.out & kM33; divSqrt_flags = r.flags; divSqrt_typeTag = 0;
  }
  if (divD_.rawOutValid) {
    const hf::DivSqrtOut o = hf::div_sqrt_outputs(D_E, D_S, divD_);
    const hf::RoundOut r = hf::round_raw_to_recfn(D_E, D_S, o.invalidExc, o.infiniteExc, o.rawOut, o.rmOut, true);
    divSqrt_wen = !divSqrt_killed_; divSqrt_wdata = sanitize_nan_d(r.out & kM65); divSqrt_flags = r.flags; divSqrt_typeTag = 1;
  }
  const bool divSqrt_inFlight = (!divS_.inReady || !divD_.inReady) && !divSqrt_killed_;
  w.divSqrt_wen = divSqrt_wen; w.divSqrt_wdata = divSqrt_wdata; w.divSqrt_flags = divSqrt_flags;
  w.divSqrt_typeTag = divSqrt_typeTag; w.divSqrt_inFlight = divSqrt_inFlight;

  // ---- write-back selection (only when something writes) ----
  const bool wen0 = wen_ & 1;
  w.waddr = divSqrt_wen ? divSqrt_waddr_ : wbInfo_[0].rd;
  w.wtypeTag = divSqrt_wen ? divSqrt_typeTag : wbInfo_[0].typeTag;
  w.sboard_clra = w.waddr;
  u128 pipe_data = 0; uint8_t pipe_exc = 0;
  if (wen0) {
    switch (wbInfo_[0].pipeid & 3) {
      case 0: pipe_data = fpmu_data_; pipe_exc = fpmu_exc_; break;
      case 1: pipe_data = ifpu_data_; pipe_exc = ifpu_exc_; break;
      case 2: {
        const hf::RoundOut r = hf::round_raw_to_recfn(S_E, S_S, sfma_.invalidExc, false, sfma_.raw, sfma_.rm1, true);
        pipe_data = r.out & kM33; pipe_exc = r.flags;
        break;
      }
      default: pipe_data = dfma_.out_data; pipe_exc = dfma_.out_exc; break;
    }
  }
  w.wdata = (wen0 || divSqrt_wen) ? box_tag(divSqrt_wen ? divSqrt_wdata : pipe_data, w.wtypeTag) : 0;
  w.wexc = pipe_exc;
  w.regfile_write_pipe = (!wbInfo_[0].cp && wen0) || divSqrt_wen;

  const bool wb_toint_valid = wb_reg_valid_ && wb_ctrl_.toint;
  w.fcsr_flags_valid = wb_toint_valid || divSqrt_wen || wen0;
  w.fcsr_flags = static_cast<uint8_t>((wb_toint_valid ? wb_toint_exc_ : 0) | (divSqrt_wen ? divSqrt_flags : 0) | (wen0 ? pipe_exc : 0));
  const bool divSqrt_write_port_busy = (mem_ctrl_.div || mem_ctrl_.sqrt) && wen_ != 0;
  w.fcsr_rdy = !((ex_reg_valid_ && ex_reg_ctrl_.wflags) || (mem_reg_valid_ && mem_ctrl_.wflags) || wb_toint_valid || wen_ != 0 || divSqrt_inFlight);
  w.nack_mem = write_port_busy_ || divSqrt_write_port_busy || divSqrt_inFlight;
  w.sboard_set = wb_reg_valid_ && sboard_set_reg_;
  w.sboard_clr = divSqrt_wen || (wen0 && (wbInfo_[0].pipeid & 3) == 3);
}

void Fpu::evaluate_inputs(const FpuIn& in, FpuWires& w) const {
  // ID decode and kill commands do not feed back into the state outputs.
  if (architectural_mode_ && !is_fp_opcode(in.inst)) {
    w.dec = FpuCtrlSigs{};
  } else {
    // Decode unissued FP candidates too: Core hazard checking can deassert
    // in.valid while still consuming their operand enables.
    if (!decode_cache_valid_ || decode_cache_inst_ != in.inst) {
      decode_cache_ctrl_ = decode(in.inst);
      decode_cache_inst_ = in.inst;
      decode_cache_valid_ = true;
    }
    w.dec = decode_cache_ctrl_;
  }
  const unsigned rm3 = (in.inst >> 12) & 7;
  w.illegal_rm = rm3 == 5 || rm3 == 6 || (rm3 == 7 && in.fcsr_rm >= 5);
  w.idle = w.state_idle && !in.valid && !in.dmem_resp_val;
  w.killm = in.killm || w.nack_mem;
  w.killx = in.killx || (mem_reg_valid_ && w.killm);
}

void Fpu::evaluate(const FpuIn& in, FpuWires& w) const {
  evaluate_state(w);
  evaluate_inputs(in, w);
}

void Fpu::commit(const FpuIn& in, const FpuWires& w) {
  if (w.idle) {
    // Registers whose next value follows held control state.
    if (mem_ctrl_.toint) wb_toint_exc_ = fpiu_exc_;
    sboard_set_reg_ = (mem_ctrl_.fma && mem_ctrl_.typeTagOut == 1) || mem_ctrl_.div || mem_ctrl_.sqrt;
    if (in.reset) divSqrt_killed_ = true;
    return;
  }
  const bool ex_reg_valid_old = ex_reg_valid_;
  const uint32_t ex_reg_inst_old = ex_reg_inst_;
  const FpuCtrlSigs ex_ctrl = ex_reg_ctrl_;
  const bool mem_reg_valid_old = mem_reg_valid_;
  const FpuCtrlSigs mem_ctrl_old = mem_ctrl_;
  const uint32_t mem_reg_inst_old = mem_reg_inst_;
  const uint8_t wen_old = wen_;
  const WbInfo wbInfo_old[3] = {wbInfo_[0], wbInfo_[1], wbInfo_[2]};
  const bool killm = w.killm;
  // Pre-edge values of the FPToInt unit (read by the divider and the WB flags).
  const FpInput fpiu_in_old = fpiu_in_;
  const uint8_t fpiu_exc_old = fpiu_exc_;
  const bool fpiu_lt_old = fpiu_lt_;

  // ---- pipeline stages advance (each computed once, from the previous stage's registers) ----
  // IntToFP / FPToFP second stages
  const bool mem_result_needed = !architectural_mode_ || !killm;
  ifpu_v2_ = ifpu_v1_ && mem_result_needed;
  if (ifpu_v2_) ifpu_eval(ifpu_in_, ifpu_in1_, ifpu_data_, ifpu_exc_);
  fpmu_v2_ = fpmu_v1_ && mem_result_needed;
  if (fpmu_v2_) fpmu_eval(fpmu_in_, fpiu_lt_old, fpmu_data_, fpmu_exc_);
  // FMA pipes
  auto advance_fma = [&](FmaSlot& p, unsigned E, unsigned S, bool extra_stage) {
    if (extra_stage) {
      p.out_valid = p.validout;
      if (p.validout) {
        const hf::RoundOut r = hf::round_raw_to_recfn(E, S, p.invalidExc, false, p.raw, p.rm1, true);
        p.out_data = sanitize_nan_d(r.out & kM65);
        p.out_exc = r.flags;
      }
    }
    const bool valid_stage0_old = p.valid_stage0;
    p.validout = valid_stage0_old;
    if (valid_stage0_old) {
      const hf::PostMul post = hf::mul_add_post(E, S, p.pre, p.rm0);
      p.raw = post.rawOut; p.invalidExc = post.invalidExc; p.rm1 = p.rm0;
    }
    const bool valid_old = p.valid && mem_result_needed;
    p.valid_stage0 = valid_old;
    if (valid_old) {
      const u128 m = E == 11 ? kM65 : kM33;
      p.pre = hf::mul_add_pre(E, S, p.in.fmaCmd, p.in.in1 & m, p.in.in2 & m, p.in.in3 & m);
      p.rm0 = p.in.rm;
    }
  };
  advance_fma(sfma_, S_E, S_S, false);
  advance_fma(dfma_, D_E, D_S, true);

  // ---- EX stage: operand fetch and unit capture, once per instruction (pre-edge register file) ----
  bool fpiu_cap = false, ifpu_cap = false, fpmu_cap = false, sfma_cap = false, dfma_cap = false;
  if (ex_reg_valid_old && (!architectural_mode_ || !w.killx)) {
    const uint8_t ex_rm = ((ex_reg_inst_old >> 12) & 7) == 7 ? in.fcsr_rm : static_cast<uint8_t>((ex_reg_inst_old >> 12) & 7);
    const u128 rs0 = regfile_[ex_ra_[0] & 31], rs1 = regfile_[ex_ra_[1] & 31], rs2 = regfile_[ex_ra_[2] & 31];
    auto fu_input = [&](int minT) {
      FpInput r{};
      r.c = ex_ctrl;
      r.rm = ex_rm;
      const unsigned tag = ex_ctrl.typeTagIn;
      if (minT < 0) { r.in1 = unbox_none(rs0, tag); r.in2 = unbox_none(rs1, tag); r.in3 = unbox_none(rs2, tag); }
      else if (minT == 0) { r.in1 = unbox_s(rs0); r.in2 = unbox_s(rs1); r.in3 = unbox_s(rs2); }
      else { r.in1 = unbox_d(rs0); r.in2 = unbox_d(rs1); r.in3 = unbox_d(rs2); }
      r.typ = (ex_reg_inst_old >> 20) & 3;
      r.fmt = (ex_reg_inst_old >> 25) & 3;
      r.fmaCmd = fp_fma_operation(ex_reg_inst_old);
      return r;
    };
    fpiu_cap = ex_ctrl.toint || ex_ctrl.div || ex_ctrl.sqrt || (ex_ctrl.fastpipe && ex_ctrl.wflags);
    ifpu_cap = ex_ctrl.fromint;
    fpmu_cap = ex_ctrl.fastpipe;
    sfma_cap = ex_ctrl.fma && ex_ctrl.typeTagOut == 0;
    dfma_cap = ex_ctrl.fma && ex_ctrl.typeTagOut == 1;
    if (fpiu_cap || ifpu_cap || fpmu_cap) {
      const FpInput fin = fu_input(-1);
      if (fpiu_cap) {
        fpiu_in_ = fin;
        const FpiuOut o = fpiu_eval(fin);
        fpiu_store_ = o.store; fpiu_toint_ = o.toint; fpiu_exc_ = o.exc; fpiu_lt_ = o.lt;
      }
      if (ifpu_cap) { ifpu_in_ = fin; ifpu_in1_ = in.fromint_data; }
      if (fpmu_cap) fpmu_in_ = fin;
    }
    auto fma_prepare = [&](FpInput r, unsigned E, unsigned S) {
      const u128 one = static_cast<u128>(1) << (S + E - 1);
      const u128 zero = (r.in1 ^ r.in2) & (static_cast<u128>(1) << (S + E));
      if (r.c.swap23) r.in2 = one;
      if (!(r.c.ren3 || r.c.swap23)) r.in3 = zero;
      return r;
    };
    if (sfma_cap) sfma_.in = fma_prepare(fu_input(0), S_E, S_S);
    if (dfma_cap) dfma_.in = fma_prepare(fu_input(1), D_E, D_S);
  }
  fpiu_valid_ = fpiu_cap;
  ifpu_v1_ = ifpu_cap;
  fpmu_v1_ = fpmu_cap;
  sfma_.valid = sfma_cap;
  dfma_.valid = dfma_cap;

  // ---- register file (after the operand reads) ----
  if (load_wb_) regfile_[load_wb_tag_ & 31] = recode(load_wb_data_, load_wb_typeTag_);
  if (w.regfile_write_pipe) regfile_[w.waddr & 31] = w.wdata & kM65;

  // ---- ID -> EX ----
  ex_reg_valid_ = in.valid;
  if (in.valid) {
    const FpuCtrlSigs& id_ctrl = w.dec;
    ex_reg_inst_ = in.inst;
    ex_reg_ctrl_ = id_ctrl;
    if (id_ctrl.ren1) {
      if (!id_ctrl.swap12) ex_ra_[0] = (in.inst >> 15) & 31;
      if (id_ctrl.swap12) ex_ra_[1] = (in.inst >> 15) & 31;
    }
    if (id_ctrl.ren2) {
      if (id_ctrl.swap12) ex_ra_[0] = (in.inst >> 20) & 31;
      if (id_ctrl.swap23) ex_ra_[2] = (in.inst >> 20) & 31;
      if (!id_ctrl.swap12 && !id_ctrl.swap23) ex_ra_[1] = (in.inst >> 20) & 31;
    }
    if (id_ctrl.ren3) ex_ra_[2] = (in.inst >> 27) & 31;
  }
  load_wb_ = in.dmem_resp_val;
  if (in.dmem_resp_val) {
    load_wb_typeTag_ = static_cast<uint8_t>((in.dmem_resp_type - 2) & 3);
    load_wb_data_ = in.dmem_resp_data;
    load_wb_tag_ = in.dmem_resp_tag & 31;
  }

  // ---- EX -> MEM -> WB control ----
  mem_reg_valid_ = ex_reg_valid_old && !w.killx;
  if (ex_reg_valid_old) { mem_reg_inst_ = ex_reg_inst_old; mem_ctrl_ = ex_ctrl; }
  wb_reg_valid_ = mem_reg_valid_old && !killm;
  if (mem_reg_valid_old) wb_ctrl_ = mem_ctrl_old;
  if (mem_ctrl_old.toint) wb_toint_exc_ = fpiu_exc_old;
  sboard_set_reg_ = (mem_ctrl_old.fma && mem_ctrl_old.typeTagOut == 1) || mem_ctrl_old.div || mem_ctrl_old.sqrt;

  // ---- write-back bookkeeping ----
  const uint8_t memLatencyMask = latency_mask(mem_ctrl_old, 2);
  const bool mem_wen = mem_reg_valid_old && (mem_ctrl_old.fma || mem_ctrl_old.fastpipe || mem_ctrl_old.fromint);
  for (unsigned i = 0; i < 2; ++i) if ((wen_old >> (i + 1)) & 1) wbInfo_[i] = wbInfo_old[i + 1];
  uint8_t wen = wen_old >> 1;
  if (mem_wen) {
    if (!killm) wen = static_cast<uint8_t>((wen_old >> 1) | memLatencyMask);
    for (unsigned i = 0; i < 3; ++i) {
      if (!write_port_busy_ && ((memLatencyMask >> i) & 1)) {
        wbInfo_[i].cp = false;
        wbInfo_[i].typeTag = mem_ctrl_old.typeTagOut & 1;
        wbInfo_[i].pipeid = pipe_id(mem_ctrl_old);
        wbInfo_[i].rd = (mem_reg_inst_old >> 7) & 31;
      }
    }
  }
  wen_ = wen & 7;
  if (ex_reg_valid_old)
    write_port_busy_ = (mem_wen && (memLatencyMask & latency_mask(ex_ctrl, 1)) != 0) || (wen_old & latency_mask(ex_ctrl, 0)) != 0;

  // ---- divide / square root ----
  const bool divSqrt_inValid = mem_reg_valid_old && (mem_ctrl_old.div || mem_ctrl_old.sqrt) && !w.divSqrt_inFlight &&
                               (!architectural_mode_ || !killm);
  if (divSqrt_inValid) divSqrt_waddr_ = (mem_reg_inst_old >> 7) & 31;
  if (divSqrt_inValid || divS_.cycleNum != 0 || divD_.cycleNum != 0 || divSqrt_killed_) {
    const unsigned mtag = mem_ctrl_old.typeTagOut & 1;
    hf::DivSqrtIn di{};
    di.sqrtOp = mem_ctrl_old.sqrt;
    di.rm = fpiu_in_old.rm;
    di.inValid = divSqrt_inValid && mtag == 0;
    di.a = hf::raw_from_recfn(S_E, S_S, d_to_s(fpiu_in_old.in1));
    di.b = hf::raw_from_recfn(S_E, S_S, d_to_s(fpiu_in_old.in2));
    hf::div_sqrt_step(S_E, S_S, divS_, di, divSqrt_killed_);
    di.inValid = divSqrt_inValid && mtag == 1;
    di.a = hf::raw_from_recfn(D_E, D_S, fpiu_in_old.in1 & kM65);
    di.b = hf::raw_from_recfn(D_E, D_S, fpiu_in_old.in2 & kM65);
    hf::div_sqrt_step(D_E, D_S, divD_, di, divSqrt_killed_);
  }
  divSqrt_killed_ = divSqrt_inValid && killm;

  if (in.reset) {
    ex_reg_valid_ = false; mem_reg_valid_ = false; wb_reg_valid_ = false; wen_ = 0; divSqrt_killed_ = true;
  }
}

}  // namespace chisa::rocket_model
