#pragma once
// A four-stage software FP execution pipeline. Arithmetic is performed by
// independent integer algorithms; each stage writes its selected observations
// at the same event that updates the actual payload, without a state scan.
#include <array>
#include "../protocol/floating_point.h"
#include "../../common/fma_math.h"
#include "../../boom_model/common/micro_op.h"

namespace chisa::boom_system::components {
class FpuModel {
 public:
  using Word=fp_format::Word;
  struct Control {
    bool fma=false,fast=false,toint=false,flags=false,second=false,third=false,add=false;
    bool input_double=false,output_double=false;
    unsigned operation=0;
  };
  struct Request {
    Control control{};
    unsigned rounding=0,integer_type=0;
    bool integer_64=false;
    Word a=0,b=0,c=0;
  };
  struct Result {Word data=0;std::uint8_t flags=0;};
  struct IntegerResult {std::uint64_t value=0;std::uint8_t flags=0;bool less=false;};
  template<unsigned Length,class Payload> struct Pipe {
    std::array<bool,Length> valid{};
    std::array<Payload,Length> data{};
    template<class Publish> void step(bool enable,const Payload& value,bool reset,Publish publish) {
      for(unsigned n=Length-1;n>0;--n) {if(valid[n-1]) {data[n]=data[n-1];publish(n,data[n]);}valid[n]=!reset&&valid[n-1];}
      if(enable) {data[0]=value;publish(0,data[0]);}valid[0]=!reset&&enable;
    }
    bool active() const {for(bool v:valid) if(v) return true;return false;}
  };
  struct Fma {
    Request input{};
    fma_math::Aligned aligned{};
    binary_float::Raw raw{};
    bool invalid=false,input_valid=false,aligned_valid=false,raw_valid=false,output_valid=false;
    unsigned aligned_rounding=0,raw_rounding=0;
    Result output{};
  };
  struct State {
    Fma single,double_precision;
    Request integer_input{},fast_input{};
    IntegerResult integer_result{};
    bool integer_valid=false,fast_valid=false;
    Pipe<3,IntegerResult> integer_pipe;
    Pipe<3,Result> fast_pipe;
    Pipe<4,bool> fast_double;
  };
  FpuModel() {refresh_outputs();}
  const State& state() const {return state_;}
  const protocol::FpuOutputs& outputs() const {return output_;}
  const protocol::FpuOracleState& oracles() const {return observations_;}
  bool active() const {return active_;}
  std::uint64_t eval_count() const {return eval_count_;}
  std::uint64_t skipped_count() const {return skipped_count_;}
  void commit(const protocol::FpuInputs& input) {
    if(!active_ && input==last_input_) {++skipped_count_;return;}
    if(input!=last_input_) drain_=6;
    const auto control=decode(input.uopc&127);
    const auto general=make_request(input,control,-1);
    const bool integer_enable=input.valid&&control.toint;
    const bool fast_enable=input.valid&&control.fast;
    // Consume the previous registered requests before capturing new operands.
    auto& s=state_;
    s.integer_pipe.step(s.integer_valid,s.integer_result,input.reset,[&](unsigned stage,const IntegerResult& result) {
      if(stage==0) observations_[10]=result.value;
      if(stage==2) {observations_[40]=result.value;observations_[68]=result.flags;}
    });
    Result fast_result;
    if(s.fast_valid) fast_result=fast_value(s.fast_input,s.integer_result.less);
    s.fast_pipe.step(s.fast_valid,fast_result,input.reset,[&](unsigned stage,const Result& result) {
      if(stage==0) publish_word(59,result.data);
      if(stage==2) {publish_word(49,result.data);observations_[66]=result.flags;}
    });
    s.fast_double.step(fast_enable,control.output_double,input.reset,[&](unsigned stage,bool value) {if(stage==3) observations_[69]=value;});
    if(input.valid&&(control.toint||(control.fast&&control.flags))) {
      s.integer_input=general;s.integer_result=integer_value(general);publish_word(36,general.a);publish_word(38,general.b);
    }
    if(fast_enable) {
      s.fast_input=general;publish_word(41,general.a);publish_word(43,general.b);
      observations_[45]=control.second;observations_[46]=general.rounding;observations_[47]=control.output_double;observations_[48]=control.flags;
    }
    s.integer_valid=integer_enable; // the request mirror has no synchronous reset
    s.fast_valid=!input.reset&&fast_enable;
    advance_fma(s.single,false,input.valid&&control.fma&&!control.output_double,make_request(input,control,0),input.reset);
    advance_fma(s.double_precision,true,input.valid&&control.fma&&control.output_double,make_request(input,control,1),input.reset);
    observations_[65]=s.fast_pipe.valid[2];observations_[67]=s.integer_pipe.valid[2];
    if(drain_) --drain_;
    active_=drain_ || s.integer_valid || s.fast_valid || s.integer_pipe.active() || s.fast_pipe.active() || s.fast_double.active() || fma_active(s.single) || fma_active(s.double_precision);
    last_input_=input;++eval_count_;refresh_outputs();
  }

 private:
  static constexpr Word mask65=(Word(1)<<65)-1;
  static constexpr Word qnan_double=(Word(7)<<61)|(Word(1)<<51);
  static constexpr Word qnan_single=(Word(7)<<29)|(Word(1)<<22);
  static bool fma_active(const Fma& f) {return f.input_valid||f.aligned_valid||f.raw_valid||f.output_valid;}
  static Control decode(unsigned operation) {
    Control c;
    switch(operation) {
      case uopFCLASS_S:case uopFMV_X_S:case uopFCVT_X_S:case uopCMPR_S:
        c.toint=true;c.second=operation==uopCMPR_S;c.flags=operation==uopFCVT_X_S||c.second;c.input_double=operation==uopFMV_X_S;break;
      case uopFCLASS_D:case uopFMV_X_D:case uopFCVT_X_D:case uopCMPR_D:
        c.toint=true;c.second=operation==uopCMPR_D;c.flags=operation==uopFCVT_X_D||c.second;c.input_double=c.output_double=true;break;
      case uopFSGNJ_S:case uopFMINMAX_S:c.fast=c.second=true;c.flags=operation==uopFMINMAX_S;break;
      case uopFSGNJ_D:case uopFMINMAX_D:c.fast=c.second=c.input_double=c.output_double=true;c.flags=operation==uopFMINMAX_D;break;
      case uopFCVT_S_D:c.fast=c.flags=c.input_double=true;break;
      case uopFCVT_D_S:c.fast=c.flags=c.output_double=true;break;
      case uopFADD_S:case uopFSUB_S:case uopFMUL_S:case uopFMADD_S:case uopFMSUB_S:case uopFNMADD_S:case uopFNMSUB_S:
        c.fma=c.flags=c.second=true;c.add=operation==uopFADD_S||operation==uopFSUB_S;c.third=operation>=uopFMADD_S;
        c.operation=operation==uopFSUB_S||operation==uopFMSUB_S?1:operation==uopFNMADD_S?3:operation==uopFNMSUB_S?2:0;break;
      case uopFADD_D:case uopFSUB_D:case uopFMUL_D:case uopFMADD_D:case uopFMSUB_D:case uopFNMADD_D:case uopFNMSUB_D:
        c.fma=c.flags=c.second=c.input_double=c.output_double=true;c.add=operation==uopFADD_D||operation==uopFSUB_D;c.third=operation>=uopFMADD_D;
        c.operation=operation==uopFSUB_D||operation==uopFMSUB_D?1:operation==uopFNMADD_D?3:operation==uopFNMSUB_D?2:0;break;
      default:break; // integer-to-FP and divide/sqrt belong to other execution units
    }
    return c;
  }
  static Word operand(Word image,bool is_double,int exact_type) {
    if(exact_type==1 || (exact_type<0&&is_double)) return image&mask65;
    const auto single=fp_format::extract_single(image);
    if(exact_type==0) return single|(fp_format::is_boxed_single(image)?Word(0):qnan_single);
    return fp_format::is_boxed_single(image)?fp_format::resize_unrounded(single,8,24,11,53):qnan_double;
  }
  static Request make_request(const protocol::FpuInputs& input,const Control& control,int exact_type) {
    Request request;request.control=control;
    const unsigned mode=input.imm_packed&7;request.rounding=mode==7?input.fcsr_rm&7:mode;
    request.integer_type=(input.imm_packed>>8)&3;
    request.integer_64=control.input_double && input.uopc!=uopFMV_X_S;
    Word values[3];for(unsigned i=0;i<3;++i) values[i]=operand((Word((input.operand_bit64>>i)&1)<<64)|input.operands[i],control.input_double,exact_type);
    request.a=values[0];request.b=values[1];request.c=control.add?values[1]:values[2];
    return request;
  }
  static std::uint32_t classify(Word value,unsigned e,unsigned p) {
    const auto raw=binary_float::unpack(e,p,value);
    if(raw.isNaN) return 1u<<(binary_float::signaling_nan(raw,p)?8:9);
    if(raw.isInf) return 1u<<(raw.sign?0:7);
    if(raw.isZero) return 1u<<(raw.sign?3:4);
    return 1u<<(raw.sExp<((INT64_C(1)<<(e-1))+2)?(raw.sign?2:5):(raw.sign?1:6));
  }
  static IntegerResult integer_value(const Request& request) {
    IntegerResult result;
    const auto comparison=binary_float::compare(11,53,request.a,request.b,(request.rounding&2)==0);
    result.less=comparison.less||(((request.a>>64)&1)&&!((request.b>>64)&1));
    const auto ieee=fp_format::read_register(request.a);
    std::uint64_t value=request.control.output_double?ieee:(ieee&UINT32_MAX)|((ieee&UINT32_MAX)<<32);
    bool wide=request.integer_64;
    if(request.control.flags) {
      if(request.control.second) {
        switch(request.rounding&3) {case 0:value=comparison.less||comparison.equal;break;case 1:value=comparison.less;break;case 2:value=comparison.equal;break;default:value=0;break;}
        result.flags=comparison.flags;wide=false;
      } else {
        wide=(request.integer_type&2)!=0;
        const auto integer=binary_float::to_integer(11,53,wide?64:32,request.a,request.rounding,(request.integer_type&1)==0);
        value=integer.value;result.flags=(integer.flags&6)?16:(integer.flags&1);
      }
    } else if(request.rounding&1) {
      value=request.control.output_double?classify(request.a,11,53):classify(fp_format::resize_unrounded(request.a,11,53,8,24),8,24);wide=false;
    }
    result.value=wide?value:static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(value)));
    return result;
  }
  static Result fast_value(const Request& request,bool less) {
    Result result;const auto a=binary_float::unpack(11,53,request.a),b=binary_float::unpack(11,53,request.b);
    const bool sign=(request.rounding&2)?a.sign^b.sign:(request.rounding&1)?!b.sign:b.sign;
    Word selected=(request.a&((Word(1)<<64)-1))|(Word(sign)<<64);
    if(request.control.flags) {
      if(request.control.second) {
        result.flags=binary_float::signaling_nan(a,53)||binary_float::signaling_nan(b,53)?16:0;
        const bool take_a=b.isNaN||((((request.rounding&1)!=0)!=less)&&!a.isNaN);
        selected=a.isNaN&&b.isNaN?qnan_double:take_a?request.a:request.b;
      } else {
        selected=a.isNaN?qnan_double:request.a;result.flags=binary_float::signaling_nan(a,53)?16:0;
      }
    }
    result.data=selected;
    if(!request.control.output_double) {
      Word narrow=fp_format::resize_unrounded(selected,11,53,8,24);
      if(request.control.flags&&!request.control.second) {
        const auto converted=binary_float::convert(11,53,8,24,request.a,request.rounding,true);
        narrow=converted.recoded;result.flags=converted.flags;
      }
      result.data=(selected&~((Word(1)<<33)-1))|narrow;
    }
    return result;
  }
  void publish_word(unsigned index,Word value) {observations_[index]=static_cast<std::uint64_t>(value);observations_[index+1]=static_cast<std::uint64_t>(value>>64)&1;}
  void advance_fma(Fma& stage,bool double_precision,bool enable,const Request& input,bool reset) {
    const unsigned e=double_precision?11:8,p=double_precision?53:24;
    if(stage.raw_valid) {
      const auto rounded=binary_float::round(e,p+2,e,p,stage.raw,stage.raw_rounding,true,stage.invalid);
      stage.output={rounded.recoded,rounded.flags};
      if(double_precision&&fp_format::is_nan(stage.output.data)) stage.output.data&=~((Word(1)<<52)|(Word(1)<<60));
      publish_word(double_precision?34:57,stage.output.data);observations_[double_precision?62:64]=stage.output.flags;
    }
    stage.output_valid=!reset&&stage.raw_valid;observations_[double_precision?61:63]=stage.output_valid;
    if(stage.aligned_valid) {
      const auto result=fma_math::normalize(e,p,stage.aligned,stage.aligned_rounding);
      stage.raw=result.rawOut;stage.invalid=result.invalidExc;stage.raw_rounding=stage.aligned_rounding;
      if(double_precision) {observations_[5]=stage.raw.isZero;observations_[6]=static_cast<std::uint64_t>(stage.raw.sExp);observations_[7]=static_cast<std::uint64_t>(stage.raw.sig);observations_[8]=stage.raw.sign;observations_[9]=stage.invalid;}
    }
    stage.raw_valid=!reset&&stage.aligned_valid;
    if(stage.input_valid) {
      stage.aligned=fma_math::prepare(e,p,stage.input.control.operation,stage.input.a,stage.input.b,stage.input.c);stage.aligned_rounding=stage.input.rounding;
      const auto& a=stage.aligned;
      if(double_precision) {observations_[0]=a.isInfA;observations_[1]=a.isInfB;observations_[2]=a.isInfC;observations_[3]=a.isNaNAOrB;observations_[4]=a.isNaNC;}
      else {
        observations_[11]=a.CDom_CAlignDist;observations_[12]=a.CIsDominant;observations_[13]=a.bit0AlignedSigC;observations_[14]=a.doSubMags;observations_[15]=static_cast<std::uint64_t>(a.highAlignedSigC);
        observations_[16]=a.isInfA;observations_[17]=a.isInfB;observations_[18]=a.isInfC;observations_[19]=a.isNaNAOrB;observations_[20]=a.isNaNC;observations_[21]=a.isSigNaNAny;observations_[22]=a.isZeroA;observations_[23]=a.isZeroB;observations_[24]=a.isZeroC;observations_[25]=static_cast<std::uint64_t>(a.sExpSum);observations_[26]=a.signProd;observations_[27]=static_cast<std::uint64_t>(a.mulAddResult);
      }
    }
    stage.aligned_valid=!reset&&stage.input_valid;
    if(enable) {
      stage.input=input;
      if(input.control.add) stage.input.b=Word(1)<<(e+p-1);
      if(!input.control.third&&!input.control.add) stage.input.c=(input.a^input.b)&(Word(1)<<(e+p));
      const unsigned first=double_precision?28:51;
      publish_word(first,stage.input.a);publish_word(first+2,stage.input.b);publish_word(first+4,stage.input.c);
    }
    stage.input_valid=enable;
  }
  void refresh_outputs() {
    const auto& s=state_;Word data;std::uint8_t flags;
    output_.valid=s.double_precision.output_valid||s.single.output_valid||s.integer_pipe.valid[2]||s.fast_pipe.valid[2];
    if(s.double_precision.output_valid) {data=s.double_precision.output.data;flags=s.double_precision.output.flags;}
    else if(s.single.output_valid) {data=fp_format::box_single(static_cast<std::uint64_t>(s.single.output.data));flags=s.single.output.flags;}
    else if(s.integer_pipe.valid[2]) {data=s.integer_pipe.data[2].value;flags=s.integer_pipe.data[2].flags;}
    else {const auto& result=s.fast_pipe.data[2];data=s.fast_double.data[3]?result.data:fp_format::box_single(static_cast<std::uint64_t>(result.data));flags=result.flags;}
    output_.data=static_cast<std::uint64_t>(data);output_.data_bit64=(data>>64)&1;output_.exception_flags=flags;
  }
  State state_{};
  protocol::FpuOracleState observations_{};
  protocol::FpuInputs last_input_{};
  protocol::FpuOutputs output_{};
  unsigned drain_=0;
  bool active_=false;
  std::uint64_t eval_count_=0,skipped_count_=0;
};
} // namespace chisa::boom_system::components
