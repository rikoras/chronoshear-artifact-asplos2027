#pragma once
#include <cstdint>
#include <utility>

namespace chisa::boom_model {
// Rocket MulDiv's divide-only register transition, extracted from Small.
// Both cores retain their own request/wrapper/branch timing around this state.
struct DividerRequest {
  std::uint64_t in1 = 0, in2 = 0;
  std::uint8_t fn = 0, dw = 0;
};
struct IntegerDivider {
  std::uint8_t state = 0, count = 0, jump = 0, divisor_hi = 0, remainder_hi = 0;
  bool negate = false, is_high = false, doubleword = false;
  std::uint64_t lhs = 0, rhs = 0, divisor = 0, remainder[2]{};
  bool response_valid() const { return state==7; }
};
struct DividerStateView {
  std::uint8_t& state;
  std::uint8_t& count;
  std::uint8_t& jump;
  std::uint8_t& divisor_hi;
  std::uint8_t& remainder_hi;
  bool& negate;
  bool& is_high;
  bool& doubleword;
  std::uint64_t& lhs;
  std::uint64_t& rhs;
  std::uint64_t& divisor;
  std::uint64_t* remainder;
};
template<class State>
inline void clock_integer_divider(State& s, const DividerRequest* request, bool response_fired) {
  const auto set64=[&](std::uint64_t value) {
    s.remainder[0]=value;s.remainder[1]=0;s.remainder_hi=0;
  };
  const auto subtract=[&]() {
    const auto low=s.remainder[1]-s.divisor;
    const unsigned borrow=s.remainder[1]<s.divisor;
    const auto high=static_cast<std::uint8_t>(((s.remainder_hi&1u)-(s.divisor_hi&1u)-borrow)&1u);
    return std::pair<std::uint64_t,std::uint8_t>{low,high};
  };
  if (request) {
    const auto& q=*request;
    const bool uns=(q.fn&1u)!=0,rem=(q.fn&2u)!=0;
    const auto extend=[&](std::uint64_t value) {
      if (q.dw) return value;
      const auto low=static_cast<std::uint32_t>(value);
      return uns ? std::uint64_t(low) : std::uint64_t(std::int64_t(std::int32_t(low)));
    };
    const auto lhs=extend(q.in1),rhs=extend(q.in2);
    const bool lhs_sign=!uns && std::int64_t(lhs)<0, rhs_sign=!uns && std::int64_t(rhs)<0;
    const auto absolute_lhs=lhs_sign ? 0-lhs : lhs,absolute_rhs=rhs_sign ? 0-rhs : rhs;
    const auto log=[](std::uint64_t value) { return value ? 63-__builtin_clzll(value) : 0; };
    unsigned jump=0;
    if (absolute_rhs) {
      const int position=63-((log(absolute_lhs)-log(absolute_rhs))&63);
      if (position>=1) jump=static_cast<unsigned>(position);
    }
    s.lhs=lhs;s.rhs=rhs;s.jump=static_cast<std::uint8_t>(jump);
    s.negate=rem ? lhs_sign : lhs_sign!=rhs_sign;
    s.divisor=rhs;s.divisor_hi=rhs_sign ? 1 : 0;
    set64(lhs);s.is_high=rem;s.doubleword=q.dw!=0;s.count=0;
    s.state=(lhs_sign || rhs_sign) ? 1 : 3;
    return;
  }
  switch (s.state) {
    case 1: {
      const auto difference=subtract();
      if (s.remainder[0]>>63) set64(0-s.remainder[0]);
      if (s.divisor>>63) { s.divisor=difference.first;s.divisor_hi=difference.second; }
      s.state=3;break;
    }
    case 3: {
      const auto old_count=s.count;
      const auto old_low=s.remainder[0],old_high=s.remainder[1];
      const auto difference=subtract();
      const bool less=difference.second!=0;
      const bool zero=old_count==0 && !less;
      if (old_count==0 && !zero && s.jump) {
        s.remainder[0]=old_low<<s.jump;s.remainder[1]=old_low>>(64-s.jump);s.remainder_hi=0;
      } else {
        const auto upper=less ? old_high : difference.first;
        s.remainder[0]=(old_low<<1)|(less ? 0u : 1u);
        s.remainder[1]=(upper<<1)|(old_low>>63);
        s.remainder_hi=static_cast<std::uint8_t>((upper>>63)&1u);
      }
      s.count=old_count==0 && s.jump ? s.jump : static_cast<std::uint8_t>(old_count+1);
      if (old_count==64) s.state=s.negate ? 5 : 7;
      if (zero && !s.is_high) s.negate=false;
      break;
    }
    case 5: {
      const auto result=s.is_high ? (s.remainder[1]>>1)|(std::uint64_t(s.remainder_hi&1u)<<63)
                                 : s.remainder[0];
      set64(0-result);s.state=7;break;
    }
    case 7: if (response_fired) s.state=0;break;
    default: break;
  }
}
}  // namespace chisa::boom_model
