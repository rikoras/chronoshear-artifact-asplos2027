#pragma once
// Fixed-point reciprocal/root refinement with three transaction slots and a
// shared pipelined multiplier. Polynomial coefficients are numerical data;
// software microsteps compute the actual accumulator/retained observations.
// No RTL evaluator, extracted expression graph or replay stream participates.
#include <array>
#include <stdexcept>
#include "../protocol/floating_point.h"
#include "../../common/binary_float.h"

namespace chisa::boom_system::components {
class Fdiv64Model {
 public:
  using Wide=binary_float::Wide;
  struct Classification {
    bool sqrt=false,major=false,nan=false,infinity=false,zero=false,sign=false;
    bool normal() const {return !nan&&!infinity&&!zero;}
  };
  struct Packet {
    bool valid=false;
    Classification kind{};
    std::int64_t exponent=0;
    std::uint64_t fraction_b=0;
    bool numerator_lsb=false;
    std::uint8_t rounding=0;
  };
  struct Multiplier {
    bool valid1=false,valid2=false;
    std::uint64_t a1=0,b1=0,a2=0,b2=0;
    Wide result=0;
  };
  struct State {
    Packet a,b,c;
    std::uint8_t phase_a=0,phase_b=0,phase_c=0,phase_e=0;
    std::uint64_t fraction_a=0;
    std::uint32_t reciprocal0=0,square0_high=0,negative_sigma0=0,next_a9=0,next_b9=0;
    std::uint32_t root_r1=0,square_r1=0;
    std::uint64_t x1=0,square_sigma1=0,xn=0;
    std::uint32_t root_u=0;
    bool divide_scale=false;
    std::uint64_t trial=0;
    bool remainder_negative=false,remainder_zero=false;
    Multiplier multiply;
  };
  Fdiv64Model() {refresh_outputs(false);}
  const State& state() const {return state_;}
  const protocol::FDivSqrtOutputs& outputs() const {return output_;}
  const protocol::FDivSqrtOracleState& oracles() const {return observations_;}
  bool active() const {return active_;}
  std::uint64_t eval_count() const {return eval_count_;}
  std::uint64_t skipped_count() const {return skipped_count_;}
  void commit(const protocol::FDivSqrtInputs& input) {
    if(!active_ && input==last_input_) {++skipped_count_;return;}
    advance(input);refresh_outputs(input.detect_tininess);last_input_=input;++eval_count_;
    const auto& s=state_;
    active_=s.a.valid||s.b.valid||s.c.valid||s.phase_a||s.phase_b||s.phase_c||s.phase_e||s.multiply.valid1||s.multiply.valid2;
  }
 private:
  static constexpr std::uint64_t mask52=(UINT64_C(1)<<52)-1,mask54=(UINT64_C(1)<<54)-1,mask58=(UINT64_C(1)<<58)-1;
  // Piecewise fixed-point polynomial data for the locked approximation format.
  static constexpr std::array<unsigned,8> reciprocal_slope={0x1c7,0x16c,0x12a,0xf8,0xd2,0xb4,0x9c,0x89};
  static constexpr std::array<unsigned,8> reciprocal_intercept={0xfe3,0xc5d,0x98a,0x739,0x54b,0x3a9,0x242,0x10b};
  static constexpr std::array<unsigned,4> root_quadratic={0x1c8,0xc1,0x143,0x89},root_linear={0x3d0,0x220,0x2b2,0x181},root_intercept={0x1fe5,0x1435,0xd2c,0x4e8};
  struct Control {bool leave_a=false,leave_b=false,leave_c=false,ready_a=false,ready_b=false,ready_c=false,divide_ready=false,root_ready=false;};
  Control control() const {
    const auto& s=state_;Control c;
    c.leave_c=s.c.valid&&(!s.c.kind.normal()||s.phase_e==1);c.ready_c=!s.c.valid||c.leave_c;
    c.leave_b=s.b.valid&&(s.b.kind.normal()?s.phase_c==3:c.ready_c);c.ready_b=!s.b.valid||c.leave_b;
    const bool normal_a_leaves=(s.phase_b==4&&s.a.valid&&!s.a.kind.sqrt)||s.phase_b==7;
    c.leave_a=s.a.valid&&(s.a.kind.normal()?normal_a_leaves:c.ready_b);c.ready_a=!s.a.valid||c.leave_a;
    const bool root_b_456=s.phase_b>=4&&s.phase_b<=6&&s.b.valid&&s.b.kind.sqrt;
    c.divide_ready=c.ready_a&&!root_b_456&&s.phase_b!=7&&s.phase_b!=3&&s.phase_b!=2&&!(s.phase_b==1&&s.b.kind.sqrt)&&s.phase_c!=5&&s.phase_c!=4;
    c.root_ready=c.ready_a&&!root_b_456&&!(s.phase_b==2&&!s.b.kind.sqrt)&&!(s.phase_b==1&&s.b.kind.sqrt);
    return c;
  }
  static Classification classify(bool sqrt,const binary_float::Raw& a,const binary_float::Raw& b) {
    Classification c;c.sqrt=sqrt;
    const bool invalid=sqrt?(!b.isNaN&&!b.isZero&&b.sign):((a.isZero&&b.isZero)||(a.isInf&&b.isInf));
    c.major=binary_float::signaling_nan(b,53)||invalid||(!sqrt&&(binary_float::signaling_nan(a,53)||(!a.isNaN&&!a.isInf&&b.isZero)));
    c.nan=b.isNaN||invalid||(!sqrt&&a.isNaN);c.infinity=sqrt?b.isInf:(a.isInf||b.isZero);c.zero=sqrt?b.isZero:(a.isZero||b.isInf);
    c.sign=b.sign^(!sqrt&&a.sign);return c;
  }
  static std::int64_t exponent13(std::int64_t value) {const auto code=static_cast<std::uint64_t>(value)&8191;return code>=4096?static_cast<std::int64_t>(code)-8192:code;}
  struct Seed {
    unsigned writes=0,r0=0,square=0,sigma=0,a=0,b=0,r1=0,root_r1=0;
  };
  Seed seed_step(bool start,const Classification& input_kind,const binary_float::Raw& operand_b) const {
    const auto& s=state_;Seed next;
    const bool sqrt=start?input_kind.sqrt:s.a.kind.sqrt;
    const unsigned step=start?(sqrt?7:4):s.phase_a;
    if(step==0) return next;
    const auto fraction=start?static_cast<std::uint64_t>(operand_b.sig)&mask52:s.a.fraction_b;
    const auto denominator=(UINT64_C(1)<<52)|fraction;
    const bool odd=(start?operand_b.sExp:s.a.exponent)&1;
    const unsigned piece=2*unsigned(odd)+unsigned((fraction>>51)&1);
    std::uint64_t sum=0;
    if(start&&!sqrt) {
      const unsigned interval=fraction>>49,coordinate=(fraction>>40)&511;
      sum=coordinate*reciprocal_slope[interval]+((UINT64_C(1)<<21)-1)-std::uint64_t(reciprocal_intercept[interval])*256;
    } else if(start) {
      const unsigned coordinate=(fraction>>42)&511;
      sum=root_quadratic[piece]*coordinate+((UINT64_C(1)<<20)-1)-std::uint64_t(root_linear[piece])*1024;
    } else if(step==6) {
      sum=std::uint64_t(s.next_a9)*s.next_b9+((UINT64_C(1)<<20)-1)-std::uint64_t(root_intercept[piece])*64;
    } else if(step==5) {
      const std::uint64_t r=512+s.reciprocal0;sum=r*r;
    } else {
      sum=std::uint64_t(s.next_a9)*s.next_b9;
      if(step==4) sum+=(1024+((s.square0_high&512)?((denominator>>26)&((1u<<21)-1)):0))&((1u<<21)-1);
      else if(step==3&&!sqrt) sum+=(((denominator>>26)&((1u<<21)-1))+1024)&((1u<<21)-1);
      else if(step==3||step==2) sum+=s.negative_sigma0;
      else if(step==1) sum+=std::uint64_t(s.reciprocal0)<<(sqrt?16:15);
    }
    sum&=(UINT64_C(1)<<25)-1;
    if(start&&!sqrt) {
      next.r0=(sum&(1u<<20))?(~(sum>>11)&511):0;next.a=(fraction>>35)&511;next.b=next.r0;next.writes=1|8|16;
    } else if(step==7) {
      next.a=(~(sum>>11))&511;next.b=(fraction>>42)&511;next.writes=8|16;
    } else if(step==6) {
      next.r0=(sum&(1u<<19))?(~(sum>>10)&511):0;next.a=next.b=next.r0;next.writes=1|8|16;
    } else if(step==5) {
      const auto square=sum<<unsigned(odd);next.square=(square>>10)&1023;next.a=(denominator>>44)&511;next.b=(square>>1)&511;next.writes=2|8|16;
    } else if(step==4) {
      next.sigma=sum&((1u<<21)-1);next.a=(denominator>>35)&511;next.b=s.square0_high&511;next.writes=4|8|16;
    } else if(step==3) {
      next.sigma=sum>>9;next.a=(denominator>>44)&511;next.writes=4|8;
    } else if(step==2) {
      next.a=(sum&(1u<<11))?(~(sum>>2)&511):0;next.b=256|(s.reciprocal0>>1);next.writes=8|16;
    } else {
      next.r1=32768|unsigned(sum>>(sqrt?10:9));next.root_r1=next.r1<<unsigned(odd);
      if(sqrt) next.writes=32;
    }
    return next;
  }
  struct MultiplyCommand {bool valid=false,latch_a=false,latch_b=false;std::uint64_t a=0,b=0;Wide addend=0;};
  MultiplyCommand multiplication(const Seed& seed) const {
    const auto& s=state_;MultiplyCommand command;
    const auto result=s.multiply.result;
    const auto x=static_cast<std::uint64_t>(result>>47)&mask58;
    const auto sigma=(~static_cast<std::uint64_t>(result>>45))&((UINT64_C(1)<<46)-1);
    const bool scale=((result>>104)&1)==0;
    const auto trial=s.c.kind.sqrt?static_cast<std::uint64_t>(result>>51)&mask54:
        scale?((UINT64_C(1)<<53)|(static_cast<std::uint64_t>(result>>50)&((UINT64_C(1)<<53)-1))):
              static_cast<std::uint64_t>(result>>51)&mask54;
    const auto complement=mask54-trial;
    const auto choose=[&](std::uint64_t a,bool set_b,std::uint64_t b) {command.valid=command.latch_a=true;command.a=a;if(set_b) {command.latch_b=true;command.b=b;}};
    if(s.phase_a==1) choose(s.a.kind.sqrt?std::uint64_t(seed.root_r1)<<36:(UINT64_C(1)<<52)|s.a.fraction_b,true,std::uint64_t(seed.r1)<<36);
    if(s.phase_b==7) choose((UINT64_C(1)<<52)|s.a.fraction_b,true,std::uint64_t(s.square_r1)<<19);
    if(s.phase_b==6) {
      command.valid=true;
      if(s.a.valid&&!s.a.kind.sqrt) choose((UINT64_C(1)<<52)|s.fraction_a,false,0);
      if(s.b.valid&&s.b.kind.sqrt) {command.latch_b=true;command.b=std::uint64_t(s.root_r1)<<36;}
    }
    if(s.phase_b==4) choose(sigma>>12,true,sigma);
    if(s.phase_b==3) choose(x>>12,false,0);
    if(s.phase_b==2&&s.b.kind.sqrt) command.valid=true; // repeat the held operands
    if(s.phase_c==6) choose(x>>12,true,(s.square_sigma1>>1)&((UINT64_C(1)<<30)-1));
    if(s.phase_c==4) choose(s.b.kind.sqrt?std::uint64_t(s.root_u)<<15:((s.xn>>25)&((UINT64_C(1)<<33)-1))<<13,true,s.square_sigma1);
    if(s.phase_c==1) choose(s.c.kind.sqrt?complement:(UINT64_C(1)<<52)|s.c.fraction_b,true,complement);
    // The product's third cycle adds a retained estimate or the low bits of
    // a mathematically scaled remainder, modulo the105-bit accumulator.
    if(s.phase_b==1) command.addend=Wide(s.x1)<<47;
    if(s.phase_c==6) command.addend=Wide(s.x1)<<46;
    if((s.phase_c==4&&s.b.kind.sqrt)||s.phase_c==2) command.addend=Wide(s.xn)<<47;
    if(s.phase_e==3) {
      if(!s.c.kind.sqrt) {if(!s.divide_scale) command.addend=Wide(s.c.numerator_lsb)<<53;}
      else {
        const auto denominator=(UINT64_C(1)<<52)|s.c.fraction_b;
        static constexpr unsigned residue[4]={0,3,2,1};
        const auto low=(s.c.exponent&1)?2*(denominator&1):residue[denominator&3];
        command.addend=Wide((low+((s.trial&1)?0:2))%4)<<54;
      }
    }
    command.a&=mask54;command.b&=mask54;return command;
  }
  void update_multiplier(const MultiplyCommand& command) {
    auto& m=state_.multiply;
    if(m.valid2) {m.result=(Wide(m.a2)*m.b2+command.addend)&binary_float::low_mask(105);observations_[37]=static_cast<std::uint64_t>(m.result);observations_[38]=static_cast<std::uint64_t>(m.result>>64);}
    if(m.valid1) {m.a2=m.a1;m.b2=m.b1;}
    m.valid2=m.valid1;m.valid1=command.valid;observations_[34]=m.valid1;
    if(command.valid&&command.latch_a) {m.a1=command.a;observations_[32]=m.a1;}
    if(command.valid&&command.latch_b) {m.b1=command.b;observations_[33]=m.b1;}
  }
  void publish_classification(unsigned stage,const Classification& kind) {
    observations_[6+stage]=kind.infinity;observations_[9+stage]=kind.nan;observations_[14+stage]=kind.zero;observations_[26+stage]=kind.sqrt;
    if(stage==2) {observations_[17]=kind.major;observations_[25]=kind.sign;}
  }
  void advance(const protocol::FDivSqrtInputs& input) {
    auto& s=state_;const auto readiness=control();
    const auto a=binary_float::unpack(11,53,(Wide(input.a_bit64)<<64)|input.a),b=binary_float::unpack(11,53,(Wide(input.b_bit64)<<64)|input.b);
    const auto kind=classify(input.sqrt_op,a,b);
    const bool accept=input.in_valid&&(input.sqrt_op?readiness.root_ready:readiness.divide_ready);
    // BOOM's FDivSqrtUnit gates may_fire_input with !r_divsqrt_val. Its second
    // operation can wait in the wrapper's input buffer, but cannot enter this
    // arithmetic seam until the executing operation has retired from it.
    if(accept&&!input.reset&&(s.a.valid||s.b.valid||s.c.valid))
      throw std::logic_error("BOOM divider seam permits one executing operation");
    const bool start=accept&&kind.normal();
    const auto seed=seed_step(start,kind,b);
    const auto command=multiplication(seed);
    const unsigned next_a=start?(kind.sqrt?6:3):(s.phase_a?s.phase_a-1:0);
    const unsigned next_b=s.phase_a==1?(s.a.kind.sqrt?10:6):(s.phase_b?s.phase_b-1:0);
    const unsigned next_c=s.phase_b==1?(s.b.kind.sqrt?6:5):(s.phase_c?s.phase_c-1:0);
    const unsigned next_e=s.phase_c==1?4:(s.phase_e?s.phase_e-1:0);
    const bool enter_a=start||(accept&&(s.a.valid||!readiness.ready_b));
    const bool enter_b=readiness.leave_a||(accept&&!kind.normal()&&!s.a.valid&&(readiness.leave_b||(!s.b.valid&&!readiness.ready_c)));
    const bool enter_c=readiness.leave_b||(accept&&!kind.normal()&&!s.a.valid&&!s.b.valid&&readiness.ready_c);
    const bool normal_b=s.a.valid&&s.a.kind.normal()&&((s.phase_b==4&&!s.a.kind.sqrt)||s.phase_b==7);
    const bool normal_c=s.b.valid&&s.b.kind.normal()&&s.phase_c==3;
    const Wide product=s.multiply.result;
    const auto x=static_cast<std::uint64_t>(product>>47)&mask58;
    if(s.phase_b==8) s.square_r1=static_cast<std::uint32_t>(product>>72);
    if(s.phase_b==3) s.x1=x;
    if(s.phase_b==1) s.square_sigma1=static_cast<std::uint64_t>(product>>47)&((UINT64_C(1)<<33)-1);
    if(s.phase_c==6||(s.phase_c==5&&!s.b.kind.sqrt)||(s.phase_c==3&&s.b.kind.sqrt)) {s.xn=x;observations_[24]=s.xn;}
    if(s.phase_c==5&&s.b.kind.sqrt) s.root_u=(x>>26)&((UINT64_C(1)<<31)-1);
    if(s.phase_c==1) {
      s.divide_scale=((product>>104)&1)==0;
      s.trial=!s.c.kind.sqrt&&s.divide_scale?(UINT64_C(1)<<53)|(static_cast<std::uint64_t>(product>>50)&((UINT64_C(1)<<53)-1)):static_cast<std::uint64_t>(product>>51)&mask54;
      observations_[0]=s.divide_scale;observations_[23]=s.trial;
    }
    if(s.phase_e==2) {
      const auto remainder=static_cast<std::uint64_t>(product)&((UINT64_C(1)<<56)-1);
      s.remainder_negative=(remainder>>(s.c.kind.sqrt?55:53))&1;
      s.remainder_zero=(remainder&(s.c.kind.sqrt?((UINT64_C(1)<<56)-1):mask54))==0;
      observations_[12]=s.remainder_negative;observations_[13]=s.remainder_zero;
    }
    if(seed.writes&1) {s.reciprocal0=seed.r0;observations_[4]=s.reciprocal0;}
    if(seed.writes&2) {s.square0_high=seed.square;observations_[5]=s.square0_high;}
    if(seed.writes&4) {s.negative_sigma0=seed.sigma;observations_[20]=s.negative_sigma0;}
    if(seed.writes&8) {s.next_a9=seed.a;observations_[18]=s.next_a9;}
    if(seed.writes&16) {s.next_b9=seed.b;observations_[19]=s.next_b9;}
    if(seed.writes&32) s.root_r1=seed.root_r1;
    update_multiplier(command);
    // Move packets back to front. Classification moves for every transaction;
    // numerical payloads only move for the normal arithmetic path.
    if(enter_c) {s.c.kind=s.b.valid?s.b.kind:kind;publish_classification(2,s.c.kind);}
    if(normal_c) {s.c.exponent=s.b.exponent;s.c.fraction_b=s.b.fraction_b;s.c.numerator_lsb=s.b.numerator_lsb;s.c.rounding=s.b.rounding;}
    if(enter_b) {s.b.kind=s.a.valid?s.a.kind:kind;publish_classification(1,s.b.kind);}
    if(normal_b) {s.b.exponent=s.a.exponent;s.b.fraction_b=s.a.fraction_b;s.b.numerator_lsb=s.fraction_a&1;s.b.rounding=s.a.rounding;}
    if(enter_a) {s.a.kind=kind;publish_classification(0,s.a.kind);}
    if(start) {
      auto exponent=kind.sqrt?b.sExp:a.sExp-b.sExp+2047;
      if(!kind.sqrt&&exponent>=3584) exponent=3072+exponent%512;
      s.a.exponent=exponent13(exponent);s.a.fraction_b=static_cast<std::uint64_t>(b.sig)&mask52;s.a.rounding=input.rounding_mode&7;
      observations_[22]=static_cast<std::uint64_t>(s.a.exponent);observations_[3]=s.a.fraction_b;observations_[21]=s.a.rounding;
      if(!kind.sqrt) {s.fraction_a=static_cast<std::uint64_t>(a.sig)&mask52;observations_[2]=s.fraction_a;}
    }
    if(enter_a||readiness.leave_a) s.a.valid=enter_a;
    if(enter_b||readiness.leave_b) s.b.valid=enter_b;
    if(enter_c||readiness.leave_c) s.c.valid=enter_c;
    s.phase_a=next_a;s.phase_b=next_b;s.phase_c=next_c;s.phase_e=next_e;
    if(input.reset) {s.a.valid=s.b.valid=s.c.valid=false;s.phase_a=s.phase_b=s.phase_c=s.phase_e=0;}
    observations_[29]=s.a.valid;observations_[30]=s.b.valid;observations_[31]=s.c.valid;
    observations_[1]=s.phase_a;observations_[35]=s.phase_b;observations_[36]=s.phase_c;observations_[39]=s.phase_e;
  }
  void refresh_outputs(bool tininess_after) {
    const auto& s=state_;const auto readiness=control();
    output_.in_ready_div=readiness.divide_ready;output_.in_ready_sqrt=readiness.root_ready;
    output_.out_valid_div=readiness.leave_c&&!s.c.kind.sqrt;output_.out_valid_sqrt=readiness.leave_c&&s.c.kind.sqrt;
    const bool below=s.c.kind.sqrt?(!s.remainder_negative&&!s.remainder_zero):s.remainder_negative;
    binary_float::Raw value{s.c.kind.nan,s.c.kind.infinity,s.c.kind.zero,s.c.kind.sign,
        s.c.kind.sqrt?s.c.exponent/2+1024:s.c.exponent+(s.divide_scale?0:1),
        (Wide(below?s.trial:s.trial+1)<<1)|unsigned(!s.remainder_zero)};
    const auto rounded=binary_float::round(11,55,11,53,value,s.c.rounding,tininess_after,s.c.kind.major&&s.c.kind.nan,s.c.kind.major&&!s.c.kind.nan);
    output_.out=static_cast<std::uint64_t>(rounded.recoded);output_.out_bit64=(rounded.recoded>>64)&1;output_.exception_flags=rounded.flags;
  }
  State state_{};
  protocol::FDivSqrtOracleState observations_{};
  protocol::FDivSqrtInputs last_input_{};
  protocol::FDivSqrtOutputs output_{};
  bool active_=false;
  std::uint64_t eval_count_=0,skipped_count_=0;
};
} // namespace chisa::boom_system::components
