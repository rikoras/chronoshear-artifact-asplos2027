#pragma once
// Software conversion between IEEE bits and the normalized recoded interchange
// format used at the observation boundary. This describes a data format;
// arithmetic execution uses IEEE values and the software floating-point library.
#include <cstdint>

namespace chisa::fp_format {
using Word=unsigned __int128;
inline std::uint64_t mask(unsigned bits) {return bits==64?UINT64_MAX:(UINT64_C(1)<<bits)-1;}

inline Word encode(unsigned exponent_bits,unsigned precision,std::uint64_t ieee) {
  const unsigned fraction_bits=precision-1;
  const auto fraction_mask=mask(fraction_bits),exponent_mask=mask(exponent_bits);
  const auto sign=(ieee>>(fraction_bits+exponent_bits))&1;
  const auto exponent=(ieee>>fraction_bits)&exponent_mask;
  auto fraction=ieee&fraction_mask;
  const unsigned offset=1u<<(exponent_bits-1);
  unsigned normalized_exponent;
  if(exponent==exponent_mask) {
    normalized_exponent=(fraction?7u:6u)<<(exponent_bits-2);
  } else if(exponent!=0) {
    normalized_exponent=static_cast<unsigned>(exponent)+offset+1;
  } else if(fraction!=0) {
    const unsigned leading=63-__builtin_clzll(fraction);
    const unsigned shift=fraction_bits-leading;
    normalized_exponent=offset+2-shift;
    fraction=(fraction<<shift)&fraction_mask;
  } else {
    // Zero ignores the low exponent bits. Keep the established observation
    // ABI's fixed representative instead of changing every stored zero image.
    normalized_exponent=(offset+3-precision)&mask(exponent_bits-2);
  }
  return (Word(sign)<<(exponent_bits+precision)) |
         (Word(normalized_exponent)<<fraction_bits) | fraction;
}

inline std::uint64_t decode(unsigned exponent_bits,unsigned precision,Word recoded) {
  const unsigned fraction_bits=precision-1;
  const auto fraction_mask=mask(fraction_bits),exponent_mask=mask(exponent_bits);
  const auto sign=std::uint64_t(recoded>>(exponent_bits+precision))&1;
  const auto exponent=std::uint64_t(recoded>>fraction_bits)&mask(exponent_bits+1);
  const auto fraction=std::uint64_t(recoded)&fraction_mask;
  const auto sign_word=sign<<(exponent_bits+fraction_bits);
  const unsigned category=exponent>>(exponent_bits-2);
  if(category==0) return sign_word;
  if(category>=6) return sign_word|(exponent_mask<<fraction_bits)|(category==7?fraction:0);
  const unsigned smallest_normal=(1u<<(exponent_bits-1))+2;
  if(exponent<smallest_normal) {
    const unsigned shift=smallest_normal-exponent;
    const std::uint64_t significand=(UINT64_C(1)<<fraction_bits)|fraction;
    return sign_word|(shift<64?significand>>shift:0);
  }
  return sign_word|((exponent-smallest_normal+1)<<fraction_bits)|fraction;
}

// Resize an internal normalized-format view, preserving NaN payloads and
// signaling status. This is used for operand unboxing/exact widening;
// floating-point conversion instructions use binary_float::convert to round.
inline Word resize_unrounded(Word value,unsigned from_e,unsigned from_p,unsigned to_e,unsigned to_p) {
  if(from_e==to_e && from_p==to_p) return value;
  const auto sign=static_cast<std::uint64_t>(value>>(from_e+from_p))&1;
  const auto exponent=static_cast<std::uint64_t>(value>>(from_p-1))&mask(from_e+1);
  Word fraction=value&mask(from_p-1);
  if(to_p>=from_p) fraction<<=to_p-from_p;else fraction>>=from_p-to_p;
  const unsigned category=exponent>>(from_e-2);
  auto resized_exponent=(exponent+(UINT64_C(1)<<to_e)-(UINT64_C(1)<<from_e))&mask(to_e+1);
  if(category==0 || category>=6) resized_exponent=(std::uint64_t(category)<<(to_e-2))|(resized_exponent&mask(to_e-2));
  return (Word(sign)<<(to_e+to_p))|(Word(resized_exponent)<<(to_p-1))|(fraction&mask(to_p-1));
}

inline bool is_nan(Word value) {return ((value>>61)&7)==7;}
inline bool is_boxed_single(Word value) {return ((value>>60)&31)==31;}
inline Word embed_single(Word double_image,std::uint64_t single_image) {
  if(!is_nan(double_image)) return double_image;
  const auto replace=[](Word original,unsigned position,unsigned width,std::uint64_t value) {
    const Word field_mask=Word(mask(width))<<position;
    return (original&~field_mask)|(Word(value&mask(width))<<position);
  };
  // The single sign and exponent-MSB have distinct positions in a boxed
  // double NaN; all other single bits occupy the low31 positions directly.
  double_image=replace(double_image,60,1,((double_image>>32)&mask(20))==mask(20));
  double_image=replace(double_image,52,1,single_image>>31);
  double_image=replace(double_image,31,1,single_image>>32);
  return replace(double_image,0,31,single_image);
}
inline std::uint64_t extract_single(Word value) {
  const std::uint64_t low=value;
  return (low&mask(31))|(((low>>52)&1)<<31)|(((low>>31)&1)<<32);
}
inline Word encode_register(std::uint64_t ieee,bool single) {
  if(single) ieee=UINT64_C(0xffffffff00000000)|static_cast<std::uint32_t>(ieee);
  return embed_single(encode(11,53,ieee),static_cast<std::uint64_t>(encode(8,24,static_cast<std::uint32_t>(ieee))));
}
inline Word box_single(std::uint64_t single) {return embed_single((Word(1)<<65)-1,single);}
inline std::uint64_t read_single(Word value) {return is_boxed_single(value)?decode(8,24,extract_single(value)):UINT32_C(0x7fc00000);}
inline std::uint64_t read_register(Word value) {
  const auto ieee=decode(11,53,value);
  return is_nan(value)?(ieee&UINT64_C(0xffffffff00000000))|decode(8,24,extract_single(value)):ieee;
}
} // namespace chisa::fp_format
