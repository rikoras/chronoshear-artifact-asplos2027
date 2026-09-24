#pragma once
#include <cstdint>
#include <type_traits>

namespace chisa::boom_model {
template<unsigned BrBits,unsigned RobBits,unsigned QueueBits,unsigned PregBits>
struct LsuUopWord {
  using Branch = std::conditional_t<(BrBits<=8),std::uint8_t,std::uint16_t>;
  static constexpr int kDst=0,kUsesStq=2,kUsesLdq=3,kAmo=4,kFence=5,
      kSigned=6,kSize=7,kCmd=9,kExc=14,kPdst=15,
      kStq=kPdst+PregBits,kLdq=kStq+QueueBits,kRob=kLdq+QueueBits,
      kBrMask=kRob+RobBits;
  static_assert(kBrMask+BrBits<=64);
  static constexpr std::uint64_t mask(unsigned bits) {
    return bits>=64 ? UINT64_MAX : (UINT64_C(1)<<bits)-1;
  }
  template<class U> static std::uint64_t make(const U& u) {
    return ((std::uint64_t(u.br_mask)&mask(BrBits))<<kBrMask) |
      ((std::uint64_t(u.rob_idx)&mask(RobBits))<<kRob) |
      ((std::uint64_t(u.ldq_idx)&mask(QueueBits))<<kLdq) |
      ((std::uint64_t(u.stq_idx)&mask(QueueBits))<<kStq) |
      ((std::uint64_t(u.pdst)&mask(PregBits))<<kPdst) |
      ((std::uint64_t(u.exception)&1u)<<kExc) |
      ((std::uint64_t(u.mem_cmd)&31u)<<kCmd) |
      ((std::uint64_t(u.mem_size)&3u)<<kSize) |
      ((std::uint64_t(u.mem_signed)&1u)<<kSigned) |
      ((std::uint64_t(u.is_fence)&1u)<<kFence) |
      ((std::uint64_t(u.is_amo)&1u)<<kAmo) |
      ((std::uint64_t(u.uses_ldq)&1u)<<kUsesLdq) |
      ((std::uint64_t(u.uses_stq)&1u)<<kUsesStq) | (std::uint64_t(u.dst_rtype)&3u);
  }
  static Branch br_mask(std::uint64_t w) { return (w>>kBrMask)&mask(BrBits); }
  static std::uint64_t set_br_mask(std::uint64_t w,Branch m) {
    return (w&~(mask(BrBits)<<kBrMask)) | ((std::uint64_t(m)&mask(BrBits))<<kBrMask);
  }
  static std::uint8_t rob(std::uint64_t w) { return (w>>kRob)&mask(RobBits); }
  static std::uint8_t ldq(std::uint64_t w) { return (w>>kLdq)&mask(QueueBits); }
  static std::uint8_t stq(std::uint64_t w) { return (w>>kStq)&mask(QueueBits); }
  static std::uint8_t pdst(std::uint64_t w) { return (w>>kPdst)&mask(PregBits); }
  static std::uint64_t set_pdst(std::uint64_t w,std::uint8_t p) {
    return (w&~(mask(PregBits)<<kPdst)) | ((std::uint64_t(p)&mask(PregBits))<<kPdst);
  }
  static bool exception(std::uint64_t w) { return (w>>kExc)&1u; }
  static std::uint64_t set_exception(std::uint64_t w) { return w|(UINT64_C(1)<<kExc); }
  static std::uint8_t mem_cmd(std::uint64_t w) { return (w>>kCmd)&31u; }
  static std::uint8_t mem_size(std::uint64_t w) { return (w>>kSize)&3u; }
  static bool mem_signed(std::uint64_t w) { return (w>>kSigned)&1u; }
  static bool is_fence(std::uint64_t w) { return (w>>kFence)&1u; }
  static bool is_amo(std::uint64_t w) { return (w>>kAmo)&1u; }
  static bool uses_ldq(std::uint64_t w) { return (w>>kUsesLdq)&1u; }
  static bool uses_stq(std::uint64_t w) { return (w>>kUsesStq)&1u; }
  static std::uint8_t dst_rtype(std::uint64_t w) { return w&3u; }
};
}  // namespace chisa::boom_model
