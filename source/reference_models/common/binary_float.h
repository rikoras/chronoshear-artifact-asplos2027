#pragma once
// Integer arithmetic for rounding a normalized binary value. A significand
// and a power-of-two scale describe the exact number; rounding selects the
// nearest representable integer at the target format's quantum. No circuit
// masks, synthesized equations or hardware evaluator are used.
#include <cstdint>
#include "recoded_float.h"

namespace chisa::binary_float {
using Wide=fp_format::Word;
struct Raw {
  bool isNaN=false,isInf=false,isZero=false,sign=false;
  std::int64_t sExp=0;
  Wide sig=0;
};
struct Rounded {std::uint64_t ieee=0;Wide recoded=0;std::uint8_t flags=0;};
inline Raw unpack(unsigned exponent_bits,unsigned precision,Wide recoded) {
  Raw result;
  result.sign=(recoded>>(exponent_bits+precision))&1;
  result.sExp=static_cast<std::uint64_t>(recoded>>(precision-1))&fp_format::mask(exponent_bits+1);
  const unsigned category=static_cast<unsigned>(result.sExp)>>(exponent_bits-2);
  result.isNaN=category==7;result.isInf=category==6;result.isZero=category==0;
  result.sig=static_cast<std::uint64_t>(recoded)&fp_format::mask(precision-1);
  if(!result.isZero) result.sig|=Wide(1)<<(precision-1);
  return result;
}
inline bool signaling_nan(const Raw& value,unsigned precision) {return value.isNaN && ((value.sig>>(precision-2))&1)==0;}
inline unsigned leading_bit(Wide value) {
  const auto upper=static_cast<std::uint64_t>(value>>64);
  return upper?127u-__builtin_clzll(upper):63u-__builtin_clzll(static_cast<std::uint64_t>(value));
}
inline Wide low_mask(unsigned bits) {return bits>=128?~Wide(0):(Wide(1)<<bits)-1;}

inline Rounded round(unsigned input_exponent_bits,unsigned input_precision,
                     unsigned exponent_bits,unsigned precision,const Raw& input,
                     unsigned mode,bool tininess_after,bool invalid=false,bool infinite=false) {
  Rounded result;
  const unsigned fraction_bits=precision-1;
  const auto exponent_mask=fp_format::mask(exponent_bits),fraction_mask=fp_format::mask(fraction_bits);
  const std::uint64_t sign=std::uint64_t(input.sign)<<(exponent_bits+fraction_bits);
  result.flags=(invalid?16:0)|(infinite?8:0);
  const auto finish=[&](std::uint64_t bits) {result.ieee=bits;result.recoded=fp_format::encode(exponent_bits,precision,bits);return result;};
  if(invalid || input.isNaN) return finish((exponent_mask<<fraction_bits)|(UINT64_C(1)<<(fraction_bits-1)));
  if(infinite || input.isInf) return finish(sign|(exponent_mask<<fraction_bits));
  if(input.isZero || input.sig==0) return finish(sign);

  // Exact value = sig *2^scale. Select the output quantum without first
  // discarding any precision, including for subnormal target results.
  const auto scale=input.sExp-(INT64_C(1)<<input_exponent_bits)-(input_precision-1);
  const unsigned leading=leading_bit(input.sig);
  const auto exponent=scale+leading;
  const std::int64_t bias=(INT64_C(1)<<(exponent_bits-1))-1;
  const auto minimum=1-bias,maximum=bias;
  const bool tiny_before=exponent<minimum;
  const auto target_exponent=tiny_before?minimum:exponent;
  const auto shift=target_exponent-fraction_bits-scale;
  Wide integer;
  bool inexact=false,above_half=false,half=false;
  if(shift<=0) {
    integer=input.sig<<static_cast<unsigned>(-shift);
  } else if(shift>=128) {
    integer=0;inexact=true;
    if(shift==128) {const Wide threshold=Wide(1)<<127;above_half=input.sig>threshold;half=input.sig==threshold;}
  } else {
    integer=input.sig>>static_cast<unsigned>(shift);
    const Wide remainder=input.sig&low_mask(static_cast<unsigned>(shift));
    const Wide threshold=Wide(1)<<static_cast<unsigned>(shift-1);
    inexact=remainder!=0;above_half=remainder>threshold;half=remainder==threshold;
  }
  bool increment=false;
  switch(mode) {
    case 0:increment=above_half || (half && (integer&1));break;
    case 2:increment=input.sign && inexact;break;
    case 3:increment=!input.sign && inexact;break;
    case 4:increment=above_half || half;break;
    case 6:if(inexact) integer|=1;break;
    default:break;
  }
  integer+=increment;
  auto rounded_exponent=target_exponent;
  if(integer>=(Wide(1)<<precision)) {integer>>=1;++rounded_exponent;}
  if(rounded_exponent>maximum) {
    result.flags|=5;
    const bool to_infinity=mode==0 || mode==4 || (mode==2 && input.sign) || (mode==3 && !input.sign);
    return finish(sign|(to_infinity?(exponent_mask<<fraction_bits):((exponent_mask-1)<<fraction_bits)|fraction_mask));
  }
  const bool subnormal=integer<(Wide(1)<<fraction_bits);
  if(inexact) {
    result.flags|=1;
    // After-rounding tininess uses destination precision with an UNBOUNDED
    // exponent range. A second rounding to the subnormal grid can produce
    // the smallest normal value while underflow must still be reported.
    bool tiny=tiny_before;
    if(tininess_after && tiny && exponent==minimum-1 && leading>=precision) {
      const unsigned unbounded_shift=leading-(precision-1);
      Wide unbounded=input.sig>>unbounded_shift;
      const auto tail=input.sig&low_mask(unbounded_shift),middle=Wide(1)<<(unbounded_shift-1);
      switch(mode) {
        case 0:unbounded+=tail>middle || (tail==middle && (unbounded&1));break;
        case 2:unbounded+=input.sign && tail!=0;break;
        case 3:unbounded+=!input.sign && tail!=0;break;
        case 4:unbounded+=tail>=middle;break;
        case 6:if(tail) unbounded|=1;break;
        default:break;
      }
      tiny=unbounded<(Wide(1)<<precision);
    }
    if(tiny) result.flags|=2;
  }
  const std::uint64_t encoded_exponent=subnormal?0:rounded_exponent+bias;
  return finish(sign|(encoded_exponent<<fraction_bits)|(static_cast<std::uint64_t>(integer)&fraction_mask));
}

struct Comparison {bool less=false,equal=false,greater=false;std::uint8_t flags=0;};
inline Comparison compare(unsigned exponent_bits,unsigned precision,Wide left,Wide right,bool signaling) {
  const auto a=unpack(exponent_bits,precision,left),b=unpack(exponent_bits,precision,right);
  if(a.isNaN || b.isNaN) return {false,false,false,static_cast<std::uint8_t>(signaling || signaling_nan(a,precision) || signaling_nan(b,precision)?16:0)};
  int order;
  if(a.isZero && b.isZero) order=0;
  else if(a.sign!=b.sign) order=a.sign?-1:1;
  else {
    int magnitude;
    if(a.isInf || b.isInf) magnitude=a.isInf==b.isInf?0:(a.isInf?1:-1);
    else if(a.isZero || b.isZero) magnitude=a.isZero==b.isZero?0:(a.isZero?-1:1);
    else if(a.sExp!=b.sExp) magnitude=a.sExp<b.sExp?-1:1;
    else magnitude=a.sig==b.sig?0:(a.sig<b.sig?-1:1);
    order=a.sign?-magnitude:magnitude;
  }
  return {order<0,order==0,order>0,0};
}

struct IntegerResult {std::uint64_t value=0;std::uint8_t flags=0;}; // invalid/overflow/inexact =4/2/1
inline IntegerResult to_integer(unsigned exponent_bits,unsigned precision,unsigned width,
                                Wide recoded,unsigned mode,bool signed_result) {
  const auto input=unpack(exponent_bits,precision,recoded);
  const auto width_mask=fp_format::mask(width);
  const auto signed_limit=UINT64_C(1)<<(width-1);
  const auto saturate=[&]() {
    if(signed_result) return input.sign && !input.isNaN?signed_limit:signed_limit-1;
    return input.sign && !input.isNaN?UINT64_C(0):width_mask;
  };
  if(input.isNaN || input.isInf) return {saturate(),4};
  if(input.isZero) return {};
  const auto scale=input.sExp-(INT64_C(1)<<exponent_bits)-(precision-1);
  Wide magnitude=0;bool inexact=false,above=false,half=false,overflow=false;
  if(scale>=0) {
    overflow=scale>=128 || leading_bit(input.sig)+scale>=128;
    if(!overflow) magnitude=input.sig<<static_cast<unsigned>(scale);
  } else {
    const auto shift=-scale;
    if(shift>=128) {inexact=input.sig!=0;if(shift==128) {above=input.sig>(Wide(1)<<127);half=input.sig==(Wide(1)<<127);}}
    else {
      magnitude=input.sig>>static_cast<unsigned>(shift);
      const auto remainder=input.sig&low_mask(static_cast<unsigned>(shift));
      const auto threshold=Wide(1)<<static_cast<unsigned>(shift-1);
      inexact=remainder!=0;above=remainder>threshold;half=remainder==threshold;
    }
  }
  switch(mode) {
    case 0:magnitude+=above || (half && (magnitude&1));break;
    case 2:magnitude+=input.sign && inexact;break;
    case 3:magnitude+=!input.sign && inexact;break;
    case 4:magnitude+=above || half;break;
    case 6:if(inexact) magnitude|=1;break;
    default:break;
  }
  const Wide limit=signed_result?Wide(signed_limit)-(input.sign?0:1):Wide(width_mask);
  overflow|=magnitude>limit || (!signed_result && input.sign && magnitude!=0);
  if(overflow) return {saturate(),2};
  const auto bits=static_cast<std::uint64_t>(magnitude);
  return {(input.sign?UINT64_C(0)-bits:bits)&width_mask,static_cast<std::uint8_t>(inexact?1:0)};
}

inline Raw integer_raw(bool signed_input,std::uint64_t bits,unsigned width) {
  bits&=fp_format::mask(width);
  Raw raw;raw.sign=signed_input && ((bits>>(width-1))&1);raw.isZero=bits==0;
  const auto magnitude=raw.sign?(UINT64_C(0)-bits)&fp_format::mask(width):bits;
  unsigned exponent_bits=1;while((1u<<(exponent_bits-1))<width) ++exponent_bits;
  raw.sExp=INT64_C(1)<<exponent_bits;
  if(magnitude) {const unsigned leading=63-__builtin_clzll(magnitude);raw.sExp+=leading;raw.sig=Wide(magnitude)<<(width-1-leading);}
  return raw;
}
inline Rounded from_integer(unsigned width,unsigned exponent_bits,unsigned precision,bool signed_input,
                            std::uint64_t bits,unsigned mode,bool tininess_after) {
  unsigned input_exponent_bits=1;while((1u<<(input_exponent_bits-1))<width) ++input_exponent_bits;
  return round(input_exponent_bits,width,exponent_bits,precision,integer_raw(signed_input,bits,width),mode,tininess_after);
}
inline Rounded convert(unsigned input_exponent_bits,unsigned input_precision,unsigned exponent_bits,
                       unsigned precision,Wide recoded,unsigned mode,bool tininess_after) {
  const auto input=unpack(input_exponent_bits,input_precision,recoded);
  return round(input_exponent_bits,input_precision,exponent_bits,precision,input,mode,tininess_after,signaling_nan(input,input_precision));
}
} // namespace chisa::binary_float
