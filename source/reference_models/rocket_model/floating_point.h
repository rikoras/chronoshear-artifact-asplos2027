#pragma once
// Rocket pipeline arithmetic API, backed by independent software algorithms.
// Stored field names describe the observation ABI; no RTL implementation is
// included or invoked by this interface.
#include <algorithm>
#include "../common/binary_float.h"
#include "../common/fma_math.h"
#include "../common/serial_fp.h"

namespace chisa::rocket_model::hf {
using u128=chisa::binary_float::Wide;
using s128=__int128;
constexpr unsigned RM_NEAR_EVEN=0,RM_MIN_MAG=1,RM_MIN=2,RM_MAX=3,RM_NEAR_MAX_MAG=4,RM_ODD=6;
constexpr unsigned OPT_SIG_MSB_ALWAYS_ZERO=1,OPT_SUBNORMS_ALWAYS_EXACT=2,OPT_NEVER_UNDERFLOWS=4,OPT_NEVER_OVERFLOWS=8;
inline std::uint64_t mask64(unsigned width) {return width>=64?UINT64_MAX:(UINT64_C(1)<<width)-1;}
inline u128 mask128(unsigned width) {return chisa::binary_float::low_mask(width);}
inline std::uint64_t bits64(std::uint64_t value,unsigned high,unsigned low) {return (value>>low)&mask64(high-low+1);}
inline u128 bits128(u128 value,unsigned high,unsigned low) {return (value>>low)&mask128(high-low+1);}
inline bool bit(u128 value,unsigned index) {return (value>>index)&1;}
inline std::int64_t sext64(std::uint64_t value,unsigned width) {return static_cast<std::int64_t>(value<<(64-width))>>(64-width);}
inline unsigned log2up(unsigned value) {unsigned width=0;for(unsigned last=value-1;last;last>>=1) ++width;return width;}
// Generic word utilities retained for downstream API compatibility.
inline unsigned clz(u128 value,unsigned width) {value&=mask128(width);return value?width-1-chisa::binary_float::leading_bit(value):width-1;}
inline u128 low_mask(std::int64_t value,int top,int bottom) {
  const auto length=std::clamp<std::int64_t>(top>bottom?value-bottom:bottom-value,0,top>bottom?top-bottom:bottom-top);
  return mask128(length);
}
inline u128 grouped_or(u128 value,unsigned width,unsigned group) {
  value&=mask128(width);u128 result=0;
  for(unsigned offset=0;offset<width;offset+=group)
    if((value>>offset)&mask128(std::min(group,width-offset))) result|=u128(1)<<(offset/group);
  return result;
}
inline u128 or_reduce_by2(u128 value,unsigned width) {return grouped_or(value,width,2);}
inline u128 or_reduce_by4(u128 value,unsigned width) {return grouped_or(value,width,4);}
inline u128 shifted_slice(u128 value,unsigned offset,unsigned high,unsigned low) {
  const unsigned width=high-low+1;
  if(low>=offset) return low-offset>=128?0:(value>>(low-offset))&mask128(width);
  return offset-low>=width?0:(value<<(offset-low))&mask128(width);
}
using Raw=chisa::binary_float::Raw;
inline bool is_sig_nan_raw(const Raw& raw,unsigned precision) {return chisa::binary_float::signaling_nan(raw,precision);}
inline Raw raw_from_recfn(unsigned e,unsigned p,u128 value) {return chisa::binary_float::unpack(e,p,value);}
inline Raw raw_from_fn(unsigned e,unsigned p,std::uint64_t value) {return raw_from_recfn(e,p,chisa::fp_format::encode(e,p,value));}
inline u128 recfn_from_fn(unsigned e,unsigned p,std::uint64_t value) {return chisa::fp_format::encode(e,p,value);}
inline std::uint64_t fn_from_recfn(unsigned e,unsigned p,u128 value) {return chisa::fp_format::decode(e,p,value);}
struct RoundOut {u128 out;std::uint8_t flags;};
inline RoundOut round_any_raw_to_recfn(unsigned ie,unsigned ip,unsigned e,unsigned p,unsigned options,
                                      bool invalid,bool infinite,const Raw& input,unsigned rm,bool after) {
  (void)options; // circuit range hints are unnecessary for exact integer rounding
  const auto result=chisa::binary_float::round(ie,ip,e,p,input,rm,after,invalid,infinite);
  return {result.recoded,result.flags};
}
inline RoundOut round_raw_to_recfn(unsigned e,unsigned p,bool invalid,bool infinite,const Raw& input,unsigned rm,bool after) {
  return round_any_raw_to_recfn(e,p+2,e,p,0,invalid,infinite,input,rm,after);
}
using PreMul=chisa::fma_math::Aligned;
using PostMul=chisa::fma_math::Normalized;
inline PreMul mul_add_pre(unsigned e,unsigned p,unsigned operation,u128 a,u128 b,u128 c) {return chisa::fma_math::prepare(e,p,operation,a,b,c);}
inline PostMul mul_add_post(unsigned e,unsigned p,const PreMul& input,unsigned rm) {return chisa::fma_math::normalize(e,p,input,rm);}
struct Cmp {bool lt,eq,gt;std::uint8_t flags;};
inline Cmp compare_recfn(unsigned e,unsigned p,u128 a,u128 b,bool signaling) {
  const auto result=chisa::binary_float::compare(e,p,a,b,signaling);return {result.less,result.equal,result.greater,result.flags};
}
struct ToInt {std::uint64_t out;std::uint8_t intFlags;};
inline ToInt recfn_to_in(unsigned e,unsigned p,unsigned width,u128 value,unsigned rm,bool sign) {
  const auto result=chisa::binary_float::to_integer(e,p,width,value,rm,sign);return {result.value,result.flags};
}
inline Raw raw_from_in(bool sign,std::uint64_t value,unsigned width) {return chisa::binary_float::integer_raw(sign,value,width);}
inline RoundOut in_to_recfn(unsigned width,unsigned e,unsigned p,bool sign,std::uint64_t value,unsigned rm,bool after) {
  const auto result=chisa::binary_float::from_integer(width,e,p,sign,value,rm,after);return {result.recoded,result.flags};
}
inline RoundOut recfn_to_recfn(unsigned ie,unsigned ip,unsigned e,unsigned p,u128 value,unsigned rm,bool after) {
  const auto result=chisa::binary_float::convert(ie,ip,e,p,value,rm,after);return {result.recoded,result.flags};
}
using DivSqrtState=chisa::serial_fp::State;
using DivSqrtIn=chisa::serial_fp::Input;
using DivSqrtOut=chisa::serial_fp::Output;
inline DivSqrtOut div_sqrt_outputs(unsigned e,unsigned p,const DivSqrtState& state) {(void)e;return chisa::serial_fp::output(p,state);}
inline void div_sqrt_step(unsigned e,unsigned p,DivSqrtState& state,const DivSqrtIn& input,bool reset) {chisa::serial_fp::step(e,p,state,input,reset);}
} // namespace chisa::rocket_model::hf
