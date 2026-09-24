#pragma once
#include "contract.h"
#include <cstring>
#include <iterator>
#include <utility>
#include <initializer_list>
#include <type_traits>
#include <cstdint>

namespace chisa::boom_model::wide {
// A bit-layout address, not a value cache or an observer. Used only by the
// module performing an actual state update. Whole-word layouts compile to
// direct stores; packed fields preserve adjacent, independently owned bits.
struct RecordFragment {
  std::uint16_t offset;
  std::uint8_t bytes, width, low, source_low;
};
struct RecordField {
  std::uint8_t count;
  RecordFragment fragment[8];   // a union of partition contracts can place one field in several words
};
template<class T,class V> [[gnu::always_inline]] inline void patch_record_word(unsigned char* address,RecordFragment f,V value) {
  const auto mask=f.width==64 ? UINT64_MAX : (UINT64_C(1)<<f.width)-1;
  std::uint64_t bits;
  if constexpr(sizeof(V)>8) bits=static_cast<std::uint64_t>(value>>f.source_low)&mask;
  else bits=(f.source_low<64 ? static_cast<std::uint64_t>(value)>>f.source_low : 0)&mask;
  T next;
  if (f.low==0 && f.width==sizeof(T)*8) next=static_cast<T>(bits);
  else {
    std::memcpy(&next,address,sizeof(T));
    next=static_cast<T>((std::uint64_t(next)&~(mask<<f.low))|(bits<<f.low));
  }
  std::memcpy(address,&next,sizeof(T));
}
template<class V> [[gnu::always_inline]] inline void write_record_fragments(contract::Image& record,const RecordField& field,V value) {
  auto* bytes=reinterpret_cast<unsigned char*>(&record);
  for (unsigned i=0;i<field.count;++i) {
    const auto f=field.fragment[i];auto* address=bytes+f.offset;
    switch(f.bytes) {
      case 1: patch_record_word<std::uint8_t>(address,f,value);break;
      case 2: patch_record_word<std::uint16_t>(address,f,value);break;
      case 4: patch_record_word<std::uint32_t>(address,f,value);break;
      case 8: patch_record_word<std::uint64_t>(address,f,value);break;
    }
  }
}
// One copy of the generic fragment writer (record_bits.cpp) for the call
// sites whose descriptor is only known at run time.
void write_record_generic(contract::Image& record,const RecordField& field,std::uint64_t value);
void write_record_generic(contract::Image& record,const RecordField& field,unsigned __int128 value);
// A descriptor that is a compile-time constant folds to plain stores when
// inlined; one picked with a run-time index used to expand the whole generic
// writer (fragment loop, width switch, mask arithmetic: about a kilobyte of
// code) at every such site, which is what made the publish path a hundred
// kilobytes of straight-line code.  Those sites now call the one shared copy.
template<class V> [[gnu::always_inline]] inline void write_record(contract::Image& record,const RecordField& field,V value) {
  if (__builtin_constant_p(field.count) && __builtin_constant_p(field.fragment[0].offset)) {
    write_record_fragments(record,field,value);
  } else if constexpr(sizeof(V)>8) {
    write_record_generic(record,field,static_cast<unsigned __int128>(value));
  } else {
    write_record_generic(record,field,static_cast<std::uint64_t>(value));
  }
}
inline constexpr std::uint16_t kAbsentSlot=0xffffu;
// A family whose members share one width but sit in words of different
// sizes (a union of partition layouts can place an FTQ entry's field in a
// 4-byte word for one entry and an 8-byte word for another): the word size
// is a per-member byte and the write switches on it, four short masked
// stores instead of the generic fragment writer.
template<unsigned Width,bool Packed> struct RecordSlotVar {
  std::uint16_t offset;
  std::uint8_t low;
  std::uint8_t bytes;
};
template<class T,unsigned Width,bool Packed> [[gnu::always_inline]] inline void store_slot_word(unsigned char* address,std::uint8_t low,std::uint64_t bits) {
  constexpr std::uint64_t mask=Width==64 ? UINT64_MAX : (UINT64_C(1)<<Width)-1;
  T next;
  if constexpr(!Packed) {
    next=static_cast<T>(bits);
  } else {
    std::memcpy(&next,address,sizeof(T));
    next=static_cast<T>((std::uint64_t(next)&~(mask<<low))|(bits<<low));
  }
  std::memcpy(address,&next,sizeof(T));
}
template<unsigned Width,bool Packed,class V> [[gnu::always_inline]] inline void write_record(contract::Image& record,RecordSlotVar<Width,Packed> slot,V value) {
  static_assert(Width>=1 && Width<=64);
  if (slot.offset==kAbsentSlot) return;
  constexpr std::uint64_t mask=Width==64 ? UINT64_MAX : (UINT64_C(1)<<Width)-1;
  const std::uint64_t bits=static_cast<std::uint64_t>(value)&mask;
  auto* address=reinterpret_cast<unsigned char*>(&record)+slot.offset;
  switch(slot.bytes) {
    case 1: store_slot_word<std::uint8_t,Width,Packed>(address,slot.low,bits);break;
    case 2: store_slot_word<std::uint16_t,Width,Packed>(address,slot.low,bits);break;
    case 4: store_slot_word<std::uint32_t,Width,Packed>(address,slot.low,bits);break;
    default: store_slot_word<std::uint64_t,Width,Packed>(address,slot.low,bits);break;
  }
}
// A field family whose members all live in words of one size and width (the
// common case: a register array or one uop field across lanes) is emitted as
// RecordSlot<Bytes,Width>: only the word offset and the bit position vary per
// member, so the write is a typed store (whole word) or one masked
// read-modify-write with a constant mask.  A member the layout does not carry
// has kAbsentSlot as its offset.
// Packed: the members share their words with other fields (bit position
// varies), so a write is a masked read-modify-write.  Unpacked: every member
// owns its whole word; the bits above the field's width are padding that
// nothing else writes and that stays zero, so the masked value is stored as
// the whole word with no read (no store-forwarding chain behind the write).
template<unsigned Bytes,unsigned Width,bool Packed> struct RecordSlot {
  std::uint16_t offset;
  std::uint8_t low;
};
template<unsigned Bytes,unsigned Width,bool Packed,class V> [[gnu::always_inline]] inline void write_record(contract::Image& record,RecordSlot<Bytes,Width,Packed> slot,V value) {
  static_assert(Bytes==1||Bytes==2||Bytes==4||Bytes==8);
  static_assert(Width>=1 && Width<=Bytes*8);
  using T=std::conditional_t<Bytes==1,std::uint8_t,std::conditional_t<Bytes==2,std::uint16_t,std::conditional_t<Bytes==4,std::uint32_t,std::uint64_t>>>;
  if (slot.offset==kAbsentSlot) return;
  constexpr std::uint64_t mask=Width==64 ? UINT64_MAX : (UINT64_C(1)<<Width)-1;
  const std::uint64_t bits=static_cast<std::uint64_t>(value)&mask;
  auto* address=reinterpret_cast<unsigned char*>(&record)+slot.offset;
  T next;
  if constexpr(!Packed) {
    next=static_cast<T>(bits);
  } else {
    std::memcpy(&next,address,sizeof(T));
    next=static_cast<T>((std::uint64_t(next)&~(mask<<slot.low))|(bits<<slot.low));
  }
  std::memcpy(address,&next,sizeof(T));
}
// The cold module already owns these words. Expand the fixed ABI addresses at
// compile time; no runtime dispatch, expression evaluation or second snapshot.
template<const auto& Fields,class Values,std::size_t... I>
inline void write_record_columns(contract::Image& record,const Values& values,std::index_sequence<I...>) {
  (void)std::initializer_list<int>{(write_record(record,Fields[I],values[I]),0)...};
}
template<const auto& Fields,class Values>
inline void write_record_columns(contract::Image& record,const Values& values) {
  write_record_columns<Fields>(record,values,std::make_index_sequence<std::size(Fields)>{});
}
}  // namespace chisa::boom_model::wide
