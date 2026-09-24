#pragma once
#include <cstdint>
#include <cstring>

namespace chisa::boom_model::byte_columns {
inline constexpr std::uint64_t kOnes = UINT64_C(0x0101010101010101);
inline constexpr std::uint64_t k7f = UINT64_C(0x7f7f7f7f7f7f7f7f);
inline std::uint64_t load8(const std::uint8_t* p) {
  std::uint64_t value; std::memcpy(&value,p,8); return value;
}
inline void store8(std::uint8_t* p,std::uint64_t value) { std::memcpy(p,&value,8); }
inline std::uint64_t eq_bytes(std::uint64_t x,std::uint8_t b) {
  const auto t=x^(kOnes*b);
  return (~(((t&k7f)+k7f)|t|k7f))>>7;
}
inline std::uint8_t compact8(std::uint64_t ones) {
  return static_cast<std::uint8_t>((ones*UINT64_C(0x0102040810204080))>>56);
}
inline std::uint32_t nonzero_mask(const std::uint8_t* p,unsigned count) {
  std::uint32_t result=0;
  unsigned i=0;
  for(;i+8<=count;i+=8)
    result |= std::uint32_t(compact8(kOnes^eq_bytes(load8(p+i),0)))<<i;
  for(;i<count;++i) if(p[i]) result|=std::uint32_t{1}<<i;
  return result;
}
inline void clear(std::uint8_t* p,unsigned count) {
  unsigned i=0;
  for(;i+8<=count;i+=8)if(load8(p+i))store8(p+i,0);
  for(;i<count;++i)p[i]=0;
}
}  // namespace chisa::boom_model::byte_columns
