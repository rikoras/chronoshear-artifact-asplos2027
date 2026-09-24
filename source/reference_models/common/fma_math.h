#pragma once
// A software fixed-point multiply/add accumulator. The aligned addend and
// product are split at the existing pipeline's storage boundary; normalization
// reconstructs that integer and derives guard/sticky bits by exact arithmetic.
// This avoids the circuit's grouped OR masks and leading-zero network.
#include <boost/multiprecision/cpp_int.hpp>
#include "binary_float.h"

namespace chisa::fma_math {
using Wide=binary_float::Wide;
using Accumulator=boost::multiprecision::uint256_t;
struct Aligned {
  bool isSigNaNAny=false,isNaNAOrB=false,isInfA=false,isZeroA=false,isInfB=false,isZeroB=false,signProd=false,isNaNC=false,isInfC=false,isZeroC=false;
  std::int64_t sExpSum=0;
  bool doSubMags=false,CIsDominant=false;
  unsigned CDom_CAlignDist=0;
  Wide highAlignedSigC=0;
  bool bit0AlignedSigC=false;
  Wide mulAddResult=0;
};
struct Normalized {bool invalidExc=false;binary_float::Raw rawOut{};};
inline Accumulator low_mask(unsigned bits) {return (Accumulator(1)<<bits)-1;}
inline std::int64_t signed_field(std::int64_t value,unsigned width) {
  const auto modulus=UINT64_C(1)<<width,code=static_cast<std::uint64_t>(value)&(modulus-1);
  return code&(modulus>>1)?static_cast<std::int64_t>(code)-static_cast<std::int64_t>(modulus):static_cast<std::int64_t>(code);
}
inline Wide narrow(const Accumulator& value) {
  return (Wide(static_cast<std::uint64_t>(value>>64))<<64)|static_cast<std::uint64_t>(value);
}
inline Aligned prepare(unsigned exponent_bits,unsigned precision,unsigned operation,Wide av,Wide bv,Wide cv) {
  const auto a=binary_float::unpack(exponent_bits,precision,av);
  const auto b=binary_float::unpack(exponent_bits,precision,bv);
  const auto c=binary_float::unpack(exponent_bits,precision,cv);
  Aligned result;
  result.signProd=a.sign^b.sign^((operation&2)!=0);
  const bool c_sign=c.sign^((operation&1)!=0);
  result.doSubMags=result.signProd!=c_sign;
  // In product-LSB units C's scale is c.exp-a.exp-b.exp+2^E+P-1.
  // The accumulation window reserves two high words and three low guard bits.
  const auto product_exponent=a.sExp+b.sExp-(INT64_C(1)<<exponent_bits);
  const auto distance=product_exponent+precision+3-c.sExp;
  const bool zero_product=a.isZero || b.isZero;
  const unsigned window_bits=3*precision+3;
  const unsigned alignment=zero_product || distance<0?0:(distance>=window_bits-1?window_bits-1:static_cast<unsigned>(distance));
  result.CIsDominant=!c.isZero && (zero_product || distance<=precision);
  unsigned alignment_bits=0;while((1u<<alignment_bits)<precision+1) ++alignment_bits;
  result.CDom_CAlignDist=alignment&((1u<<alignment_bits)-1);
  result.sExpSum=signed_field(result.CIsDominant?c.sExp:product_exponent+3,exponent_bits+2);

  const Accumulator scaled_c=Accumulator(c.sig)<<(2*precision+5);
  const bool tail=(scaled_c&low_mask(alignment+3))!=0;
  auto aligned=scaled_c>>alignment;
  // One's-complement storage defers subtraction's unit carry to normalization.
  if(result.doSubMags) aligned=low_mask(window_bits+3)-aligned;
  result.highAlignedSigC=narrow((aligned>>(2*precision+3))&low_mask(precision+2));
  result.bit0AlignedSigC=result.doSubMags?!tail:tail;
  const auto addend=narrow((aligned>>3)&low_mask(2*precision));
  result.mulAddResult=(a.sig*b.sig+addend)&binary_float::low_mask(2*precision+1);
  result.isSigNaNAny=binary_float::signaling_nan(a,precision)||binary_float::signaling_nan(b,precision)||binary_float::signaling_nan(c,precision);
  result.isNaNAOrB=a.isNaN||b.isNaN;result.isInfA=a.isInf;result.isZeroA=a.isZero;
  result.isInfB=b.isInf;result.isZeroB=b.isZero;result.isNaNC=c.isNaN;result.isInfC=c.isInf;result.isZeroC=c.isZero;
  return result;
}

inline Normalized normalize(unsigned exponent_bits,unsigned precision,const Aligned& input,unsigned mode) {
  const unsigned product_bits=2*precision;
  const Wide carry=input.mulAddResult>>product_bits;
  const auto high=(input.highAlignedSigC+carry)&binary_float::low_mask(precision+2);
  const Accumulator sum=(Accumulator(high)<<(product_bits+1)) |
      (Accumulator(input.mulAddResult&binary_float::low_mask(product_bits))<<1) | unsigned(input.bit0AlignedSigC);
  bool arithmetic_sign=false,cancellation=false;std::int64_t exponent;Wide significand;
  const bool c_sign=input.signProd^input.doSubMags;
  if(input.CIsDominant) {
    // C is at least four times the product; at most one normalization bit is
    // needed after subtraction. Keep the complete integer tail for rounding.
    const Accumulator magnitude=input.doSubMags?low_mask(3*precision+3)-sum:sum;
    const unsigned discard=input.doSubMags?precision+1:precision+2;
    const bool discarded=(magnitude&low_mask(discard))!=0;
    const auto shifted=(magnitude>>discard)<<input.CDom_CAlignDist;
    const bool sticky=discarded || (shifted&low_mask(precision))!=0;
    significand=(narrow(shifted>>precision)<<1)|unsigned(sticky);
    exponent=input.sExpSum-(input.doSubMags?1:0);arithmetic_sign=c_sign;
  } else {
    const bool negative=((sum>>(product_bits+3))&1)!=0;
    const auto low=narrow(sum&low_mask(product_bits+3));
    const Wide magnitude=(negative?~low:low+unsigned(input.doSubMags))&binary_float::low_mask(product_bits+3);
    const unsigned leading=magnitude?binary_float::leading_bit(magnitude):0;
    // Two-bit normalization groups permit a one-bit slack in the raw format.
    const unsigned shift=product_bits+2-(magnitude?(leading&~1u):0);
    const Wide shifted=magnitude<<shift;
    const bool sticky=(shifted&binary_float::low_mask(precision+2))!=0;
    significand=((shifted>>(precision+2))<<1)|unsigned(sticky);
    cancellation=magnitude==0;arithmetic_sign=cancellation?mode==2:input.signProd^negative;
    exponent=input.sExpSum-shift;
  }
  const bool infinite_product=input.isInfA||input.isInfB;
  const bool infinite_output=infinite_product||input.isInfC;
  const bool add_zeros=(input.isZeroA||input.isZeroB)&&input.isZeroC;
  Normalized result;
  result.invalidExc=input.isSigNaNAny || (input.isInfA&&input.isZeroB) || (input.isInfB&&input.isZeroA) || (!input.isNaNAOrB&&infinite_product&&input.isInfC&&input.doSubMags);
  auto& raw=result.rawOut;
  raw.isNaN=input.isNaNAOrB||input.isNaNC;raw.isInf=infinite_output;raw.isZero=add_zeros||(!input.CIsDominant&&cancellation);
  if(infinite_product) raw.sign|=input.signProd;
  if(input.isInfC) raw.sign|=c_sign;
  if(add_zeros) raw.sign|=mode==2?(input.signProd||c_sign):(input.signProd&&c_sign);
  if(!infinite_output&&!add_zeros) raw.sign|=arithmetic_sign;
  raw.sExp=signed_field(exponent,exponent_bits+2);
  raw.sig=significand&binary_float::low_mask(precision+3);
  return result;
}
} // namespace chisa::fma_math
