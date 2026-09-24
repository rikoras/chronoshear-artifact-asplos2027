#pragma once
// Software restoring division and digit-by-digit square root. Each iteration
// doubles the remainder, tests one trial divisor and appends one result bit.
// The request/response cadence and retained payloads form the observation ABI.
#include "binary_float.h"

namespace chisa::serial_fp {
struct State {
  std::uint8_t cycleNum=0;
  bool inReady=true,rawOutValid=false;
  bool sqrtOp_Z=false,majorExc_Z=false,isNaN_Z=false,isInf_Z=false,isZero_Z=false,sign_Z=false;
  std::int64_t sExp_Z=0;
  std::uint64_t fractB_Z=0;
  std::uint8_t roundingMode_Z=0;
  std::uint64_t rem_Z=0;
  bool notZeroRem_Z=false;
  std::uint64_t sigX_Z=0;
};
struct Input {bool inValid=false,sqrtOp=false;binary_float::Raw a{},b{};unsigned rm=0;};
struct Output {
  bool inReady=false,rawOutValid_div=false,rawOutValid_sqrt=false,invalidExc=false,infiniteExc=false;
  unsigned rmOut=0;
  binary_float::Raw rawOut{};
};
inline std::int64_t signed_exponent(std::int64_t value,unsigned bits) {
  const auto code=static_cast<std::uint64_t>(value)&fp_format::mask(bits);
  return code&(UINT64_C(1)<<(bits-1))?static_cast<std::int64_t>(code)-(INT64_C(1)<<bits):static_cast<std::int64_t>(code);
}
inline Output output(unsigned precision,const State& state) {
  Output result;
  result.inReady=state.inReady;result.rawOutValid_div=state.rawOutValid&&!state.sqrtOp_Z;result.rawOutValid_sqrt=state.rawOutValid&&state.sqrtOp_Z;
  result.invalidExc=state.majorExc_Z&&state.isNaN_Z;result.infiniteExc=state.majorExc_Z&&!state.isNaN_Z;result.rmOut=state.roundingMode_Z;
  result.rawOut={state.isNaN_Z,state.isInf_Z,state.isZero_Z,state.sign_Z,state.sExp_Z,
      ((binary_float::Wide(state.sigX_Z)<<1)|unsigned(state.notZeroRem_Z))&binary_float::low_mask(precision+3)};
  return result;
}
inline void step(unsigned exponent_bits,unsigned precision,State& state,const Input& input,bool reset) {
  const bool was_ready=state.inReady,was_sqrt=state.sqrtOp_Z;
  const unsigned cycle=state.cycleNum;
  const bool accept=was_ready&&input.inValid;
  const bool special_a=input.a.isZero||input.a.isInf||input.a.isNaN;
  const bool special_b=input.b.isZero||input.b.isInf||input.b.isNaN;
  const bool normal=input.sqrtOp?!special_a&&!input.a.sign:!special_a&&!special_b;
  const bool odd_exponent=(input.a.sExp&1)!=0;

  // One result bit may already occupy the spare leading position. The last
  // redundant iteration is then omitted; the outgoing value still overlaps
  // acceptance of the next request at cycle1.
  if(cycle!=0 || accept) {
    const unsigned next=accept?(normal?(input.sqrtOp?(odd_exponent?precision:precision+1):precision+2):1):
        (cycle==3 && ((state.sigX_Z>>(precision+1))&1)?1:cycle-1);
    state.cycleNum=next;state.inReady=next<=1;state.rawOutValid=next==1;
  }

  if(accept || !was_ready) {
    std::uint64_t numerator,trial;
    if(was_ready) {
      numerator=static_cast<std::uint64_t>(input.a.sig)<<(input.sqrtOp&&odd_exponent?3:1);
      if(input.sqrtOp&&odd_exponent) numerator-=UINT64_C(1)<<(precision+1);
      trial=input.sqrtOp?(odd_exponent?UINT64_C(5)<<(precision-1):UINT64_C(1)<<precision):static_cast<std::uint64_t>(input.b.sig)<<1;
    } else {
      numerator=state.rem_Z<<1;
      trial=state.fractB_Z+(was_sqrt?(state.sigX_Z<<1):(UINT64_C(1)<<precision));
    }
    numerator&=fp_format::mask(precision+3);
    const bool digit=numerator>=trial;
    const auto remainder=(digit?numerator-trial:numerator)&fp_format::mask(precision+2);
    if(was_ready || digit) state.notZeroRem_Z=numerator!=trial;
    state.rem_Z=remainder;
    if(was_ready) {
      state.sigX_Z=input.sqrtOp?(UINT64_C(1)<<precision):std::uint64_t(digit)<<(precision+1);
      if(input.sqrtOp&&odd_exponent) state.sigX_Z|=std::uint64_t(digit)<<(precision-1);
    } else if(digit) state.sigX_Z|=(UINT64_C(1)<<cycle)>>2;
    state.sigX_Z&=fp_format::mask(precision+2);
  }
  if(accept) {
    if(input.sqrtOp) state.fractB_Z=UINT64_C(1)<<(precision-(odd_exponent?2:1));
    else state.fractB_Z=(static_cast<std::uint64_t>(input.b.sig)&fp_format::mask(precision-1))<<1;
  } else if(!was_ready&&was_sqrt) state.fractB_Z>>=1;

  if(accept) {
    const bool invalid_div=(input.a.isZero&&input.b.isZero)||(input.a.isInf&&input.b.isInf);
    const bool invalid_sqrt=!input.a.isNaN&&!input.a.isZero&&input.a.sign;
    state.sqrtOp_Z=input.sqrtOp;
    if(input.sqrtOp) {
      state.majorExc_Z=binary_float::signaling_nan(input.a,precision)||invalid_sqrt;
      state.isNaN_Z=input.a.isNaN||invalid_sqrt;state.isInf_Z=input.a.isInf;state.isZero_Z=input.a.isZero;
      state.sign_Z=input.a.sign;state.sExp_Z=input.a.sExp/2+(INT64_C(1)<<(exponent_bits-1));
    } else {
      state.majorExc_Z=binary_float::signaling_nan(input.a,precision)||binary_float::signaling_nan(input.b,precision)||invalid_div||(!input.a.isNaN&&!input.a.isInf&&input.b.isZero);
      state.isNaN_Z=input.a.isNaN||input.b.isNaN||invalid_div;state.isInf_Z=input.a.isInf||input.b.isZero;state.isZero_Z=input.a.isZero||input.b.isInf;
      state.sign_Z=input.a.sign^input.b.sign;
      auto exponent=input.a.sExp-input.b.sExp+(INT64_C(1)<<exponent_bits)-1;
      const auto chunk=INT64_C(1)<<(exponent_bits-2);
      if(exponent>=7*chunk) exponent=6*chunk+exponent%chunk;
      state.sExp_Z=exponent;
    }
    state.sExp_Z=signed_exponent(state.sExp_Z,exponent_bits+2);state.roundingMode_Z=input.rm&7;
  }
  if(reset) {state.cycleNum=0;state.inReady=true;state.rawOutValid=false;}
}
} // namespace chisa::serial_fp
