#include <fesvr/dtm.h>
#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"
#include "verilated.h"
#include "fesvr_debug_bootstrap.h"
#include "architecture_program.h"
#include "softfloat_fp.h"
#include "model_mode.h"
#include <algorithm>
#include <array>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <unordered_map>
#include "boom_architecture_fields.h"

namespace {
using Event = chisa::boom_model::RetirementEvent;
using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::FesvrDtmAdapter;
constexpr std::uint64_t kBegin = 0x800028aa, kEnd = 0x80002aaa;

struct Program {
  chisa::boom_repcut::ArchitecturalProgram boundary;
  struct Segment { std::uint64_t base, size; std::vector<unsigned char> bytes; };
  std::vector<Segment> segments;
  explicit Program(const char* path) : boundary(chisa::boom_repcut::read_architectural_program(path)) {
    std::ifstream input(path, std::ios::binary);
    const std::vector<unsigned char> data{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
    const auto copy = [&](std::size_t at, void* out, std::size_t count) {
      if (at > data.size() || count > data.size()-at) throw std::runtime_error("Truncated workload ELF");
      std::memcpy(out, data.data()+at, count);
    };
    Elf64_Ehdr header; copy(0, &header, sizeof(header));
    if (header.e_phentsize != sizeof(Elf64_Phdr)) throw std::runtime_error("Unsupported ELF program headers");
    for (unsigned i=0; i<header.e_phnum; ++i) {
      Elf64_Phdr ph; copy(header.e_phoff+i*sizeof(ph), &ph, sizeof(ph));
      if (ph.p_type != PT_LOAD) continue;
      if (ph.p_filesz > ph.p_memsz) throw std::runtime_error("Invalid ELF segment");
      Segment segment{ph.p_vaddr,ph.p_memsz,{}};
      segment.bytes.resize(ph.p_filesz); copy(ph.p_offset,segment.bytes.data(),ph.p_filesz);
      segments.push_back(std::move(segment));
    }
    // These instruction-defined boundaries enclose all 500 Dhrystone iterations,
    // before the second timer read; they are not chosen from comparison results.
    if (boundary.entry != 0x80000000 || boundary.tohost != 0x80001000 ||
        read(kBegin,2) != 0x4785 || read(kEnd,4) != 0xb00027f3 ||
        read(kBegin-0x14,4) != 0xb00027f3 || read(kEnd-4,4) != 0xe0e7d6e3)
      throw std::runtime_error("The architecture gate requires the packaged 500-iteration Dhrystone ELF");
  }
  unsigned char byte(std::uint64_t at) const {
    for (const auto& s:segments) if (at>=s.base && at-s.base<s.size)
      return at-s.base<s.bytes.size() ? s.bytes[at-s.base] : 0;
    throw std::runtime_error("Unobserved workload memory byte");
  }
  std::uint64_t read(std::uint64_t at,unsigned count) const {
    std::uint64_t value=0; for(unsigned i=0;i<count;++i) value|=std::uint64_t(byte(at+i))<<(8*i); return value;
  }
};

struct Ledger {
  chisa::boom_model::ArchitecturalRetirement registers;
  std::unordered_map<std::uint64_t,unsigned char> memory;
  std::uint64_t stores=0;
  void observe(const Event& e) {
    registers.retire(e);
    if (!e.memory_write) return;
    if (e.memory_size>3) throw std::runtime_error("Invalid architectural store size");
    ++stores;
    for(unsigned i=0;i<(1u<<e.memory_size);++i) memory[e.memory_address+i]=e.memory_value>>(8*i);
  }
  void compare(const Ledger& b) const {
    const auto& x=registers.state(); const auto& y=b.registers.state();
    if (x.retired!=y.retired || x.last_pc!=y.last_pc || x.x_written_mask!=y.x_written_mask ||
        x.f_written_mask!=y.f_written_mask || stores!=b.stores)
      throw std::runtime_error("Architectural endpoint coverage differs");
    for(unsigned r=0;r<32;++r) {
      if (((x.x_written_mask>>r)&1) && x.x[r]!=y.x[r]) throw std::runtime_error("Final written GPR differs");
      if (((x.f_written_mask>>r)&1) && x.f[r]!=y.f[r]) throw std::runtime_error("Final written FPR differs");
    }
    if(memory!=b.memory) throw std::runtime_error("Final committed-store memory differs");
  }
};

struct FunctionalResults {
  const Program& program;
  Ledger state;
  std::set<std::uint64_t> calls;
  bool started=false, exited=false;
  std::uint64_t last_sequence=0;
  unsigned checks=0;
  unsigned char byte(std::uint64_t at) const {
    const auto i=state.memory.find(at); return i==state.memory.end()?program.byte(at):i->second;
  }
  std::uint64_t read(std::uint64_t at,unsigned count) const {
    std::uint64_t value=0; for(unsigned i=0;i<count;++i)value|=std::uint64_t(byte(at+i))<<(8*i);return value;
  }
  void check(bool condition, const char* description) {
    ++checks; if(!condition) throw std::runtime_error(std::string("Dhrystone result differs: ")+description);
  }
  void observe(const Event& e) {
    if(!e.valid || e.debug_mode || exited || e.sequence==last_sequence) return;
    if(e.sequence<last_sequence)throw std::runtime_error("Functional retirement sequence moved backward");
    last_sequence=e.sequence;
    if(!started) { if(e.pc!=program.boundary.entry)return; started=true; }
    const std::pair<std::uint64_t,std::uint64_t> numeric[] = {
      {0x80002b50,5},{0x80002b76,1},{0x80002ba0,65},{0x80002bc8,66},
      {0x80002bf0,7},{0x80002c18,510},{0x80002c70,0},{0x80002c98,2},
      {0x80002cc0,17},{0x80002d40,0},{0x80002d68,1},{0x80002d90,18},
      {0x80002dd6,5},{0x80002df6,13},{0x80002e16,7},{0x80002e36,1}};
    const std::pair<std::uint64_t,const char*> strings[] = {
      {0x80002ce8,"DHRYSTONE PROGRAM, SOME STRING"},{0x80002db8,"DHRYSTONE PROGRAM, SOME STRING"},
      {0x80002e56,"DHRYSTONE PROGRAM, 1'ST STRING"},{0x80002e74,"DHRYSTONE PROGRAM, 2'ND STRING"}};
    const auto argument=state.registers.state().x[11];
    bool call=false;
    for(auto [pc,expected]:numeric) if(e.pc==pc) { check(argument==expected,"numeric report argument"); call=true; }
    for(auto [pc,expected]:strings) if(e.pc==pc) {
      bool same=true;for(unsigned i=0;i<=std::strlen(expected);++i)same&=byte(argument+i)==static_cast<unsigned char>(expected[i]);
      check(same,"string report argument"); call=true;
    }
    if(e.pc==0x80002c4a || e.pc==0x80002d1a) {
      check(argument!=0,"non-null result pointer"); check(argument==read(0x80006848,8),"result pointer relation");call=true;
    }
    if(call && !calls.insert(e.pc).second)throw std::runtime_error("Dhrystone result reported twice");
    state.observe(e);
    if(e.memory_write && e.memory_address==program.boundary.tohost && (e.memory_value&1) &&
       read(program.boundary.tohost+6,2)==0) {
      check(e.memory_value==1,"target exit code"); exited=true;
    }
  }
  void finish() {
    check(started && exited,"complete program boundaries");check(calls.size()==22,"all result reports observed");
    struct Expected { std::uint64_t address,value;unsigned bytes; };
    for(auto e:std::array<Expected,7>{{{0x80006850,5,4},{0x80006854,1,4},{0x80006858,65,1},
      {0x80006859,66,1},{0x80006918,7,4},{0x8000701c,510,4},{0x80006860,1,4}}})
      check(read(e.address,e.bytes)==e.value,"final benchmark memory");
  }
};

class Comparison {
 public:
  struct Side { bool entered=false,ended=false;std::uint64_t last=0;Ledger state;std::deque<Event> pending; };
  Side model,rtl;
  std::uint64_t compared=0,stores=0;
  bool inject=false,injected=false;
  void push(bool is_model,Event e) {
    Side& s=is_model?model:rtl;
    if(!e.valid || e.sequence==s.last)return;
    if(e.sequence<s.last)throw std::runtime_error("Retirement sequence moved backward");
    s.last=e.sequence;
    if(e.debug_mode || s.ended)return;
    if(!s.entered) { if(e.pc!=kBegin)return; s.entered=true; }
    if(e.pc==kEnd) { s.ended=true;return; }
    if(is_model && inject && !injected && e.writes_x) {e.value^=1;injected=true;}
    s.state.observe(e);s.pending.push_back(e);
    if(s.pending.size()>8192)throw std::runtime_error("Architecture observation queue exceeded bound");
    while(!model.pending.empty() && !rtl.pending.empty()) {
      const Event& a=model.pending.front();const Event& b=rtl.pending.front();
      const char* field=nullptr;
      if(a.pc!=b.pc)field="pc";
      else if(a.writes_x!=b.writes_x || a.writes_f!=b.writes_f)field="destination-kind";
      else if((a.writes_x||a.writes_f) && a.rd!=b.rd)field="destination-register";
      else if((a.writes_x||a.writes_f) && a.value!=b.value)field="writeback-value";
      else if(a.memory_write!=b.memory_write)field="memory-write";
      else if(a.memory_write && (a.memory_address!=b.memory_address || a.memory_value!=b.memory_value || a.memory_size!=b.memory_size))field="store";
      if(field) {
        std::fprintf(stderr,"ARCHITECTURE_FIRST_DIFFERENCE field=%s index=%" PRIu64 " model_cycle=%" PRIu64
          " rtl_cycle=%" PRIu64 " model_pc=%" PRIx64 " rtl_pc=%" PRIx64 " model_rd=%u rtl_rd=%u"
          " model_value=%" PRIx64 " rtl_value=%" PRIx64 " model_address=%" PRIx64 " rtl_address=%" PRIx64 "\n",
          field,compared+1,a.cycle,b.cycle,a.pc,b.pc,a.rd,b.rd,a.value,b.value,a.memory_address,b.memory_address);
        throw std::runtime_error("Independent architectural retirement comparison failed");
      }
      stores+=a.memory_write;++compared;model.pending.pop_front();rtl.pending.pop_front();
    }
  }
  void finish() const {
    if(!model.entered || !rtl.entered || !model.ended || !rtl.ended || compared<1000 ||
       !stores || !model.pending.empty() || !rtl.pending.empty())
      throw std::runtime_error("Incomplete Dhrystone computation interval");
    model.state.compare(rtl.state);
  }
};

class RtlRetirement {
  std::array<bool,32*kCommit> debug_{};
  std::array<bool,kCommit> enqueue_{};
  unsigned tail_=0;bool enq_debug_=false;
  std::uint64_t sequence_=0;
 public:
  std::array<Event,kCommit> before_edge(RtlFields f,std::uint64_t cycle,bool reset) {
    std::array<Event,kCommit> events{};enqueue_.fill(false);
    if(reset){debug_.fill(false);sequence_=0;return events;}
    if(f.core_clock())throw std::runtime_error("BOOM core clock did not reach low phase");
    unsigned store=f.store_head();
    for(unsigned b=0;b<kCommit;++b) {
      const bool commits_store=f.commit(b)&&f.store(b);
      if(f.valid(b)) {
        auto& e=events[b];e.valid=true;e.cycle=cycle;e.debug_mode=debug_[f.rob_head()*kCommit+b];
        e.pc=(((f.pc(f.ftq(b))&~UINT64_C(63))|f.pclow(b))-(f.edge(b)?2:0))&((UINT64_C(1)<<40)-1);
        e.rd=f.rd(b)&31;e.writes_x=f.rdvalid(b)&&f.rdtype(b)==0&&e.rd;e.writes_f=f.rdvalid(b)&&f.rdtype(b)==1;
        const unsigned p=f.pdst(b);
        if(e.writes_x) {
          if(p>=kInteger)throw std::runtime_error("Integer retirement PRF index out of range");
          e.value=f.integer(p);
          for(unsigned port=0;port<kCommit+1;++port)
            if(f.integer_write_valid(port)&&f.integer_write_address(port)==p)e.value=f.integer_write_data(port);
        }
        if(e.writes_f) {
          if(p>=kFloating)throw std::runtime_error("Floating retirement PRF index out of range");
          const auto& raw=f.floating(p);sfp::rec_t value=(sfp::rec_t(raw[2])<<64)|(std::uint64_t(raw[1])<<32)|raw[0];
          for(unsigned port=0;port<2;++port)
            if(f.floating_write_valid(port)&&f.floating_write_address(port)==p)value=f.floating_write_data(port);
          e.value=sfp::ieee64_view(value);
        }
        if(f.store(b)) {
          if(!commits_store || store>=kStores)throw std::runtime_error("Retirement store cursor invalid");
          e.memory_write=f.stq_command(store)==1;
          if(e.memory_write) {
            e.memory_size=f.stq_size(store);e.memory_address=f.stq_address(store);
            const unsigned bits=8u<<e.memory_size;e.memory_value=f.stq_data(store)&(bits==64?UINT64_MAX:(UINT64_C(1)<<bits)-1);
          }
        }
      }
      if(commits_store)store=(store+1)%kStores;
      enqueue_[b]=f.enq(b);
    }
    tail_=f.rob_tail();enq_debug_=f.debug();return events;
  }
  void after_edge(std::array<Event,kCommit>& events,bool core_edge) {
    for(auto& e:events){e.valid&=core_edge;if(e.valid)e.sequence=++sequence_;}
    if(core_edge)for(unsigned b=0;b<kCommit;++b)if(enqueue_[b])debug_[tail_*kCommit+b]=enq_debug_;
  }
};

void drive(RtlFields f,const DtmOutputs& d) {
  f.debug_req_valid_reg()=d.req_valid;f.debug_req_bits_addr_reg()=d.req_addr;f.debug_req_bits_op_reg()=d.req_op;
  f.debug_req_bits_data_reg()=d.req_data;f.debug_resp_ready_reg()=d.resp_ready;f.exit_reg()=d.exit;
}
DmiFeedback feedback(RtlFields f) {return {f.debug_req_ready()!=0,f.debug_resp_valid()!=0,f.debug_resp_bits_resp(),f.debug_resp_bits_data()};}
} // namespace

extern "C" int debug_tick(svBit* valid,svBit,int*,int*,int*,svBit,svBit* ready,int,int) {*valid=0;*ready=0;return 0;}

int main(int argc,char** argv) {
  Comparison comparison;
  std::uint64_t model_cycles=0,rtl_cycles=0,max_cycles=6000000;
  bool model_done=false,rtl_done=false,model_success=false,rtl_success=false;
  try {
    int first=-1;
    for(int i=1;i<argc;++i) {
      std::string arg=argv[i];
      if(arg=="--"){first=i+1;break;}
      if(arg=="--negative-control"){comparison.inject=true;continue;}
      if(arg.rfind("--max-cycles=",0)==0){max_cycles=std::stoull(arg.substr(13));continue;}
      if(!arg.empty()&&arg[0]=='+')continue;
      throw std::runtime_error("Usage: chronoshear-boom-architecture [--negative-control] -- WORKLOAD");
    }
    if(first<0||first>=argc)throw std::runtime_error("A packaged Dhrystone workload is required");
    Program program(argv[first]);FunctionalResults model_results{program},rtl_results{program};
    std::vector<char*> target{argv[0]};for(int i=first;i<argc;++i)target.push_back(argv[i]);
    dtm_t model_dtm(target.size(),target.data()),rtl_dtm(target.size(),target.data());
    chisa::boom_repcut::FesvrDebugBootstrap<dtm_t> model_debug(model_dtm);
    chisa::boom_system::BoundaryConfig config;
    config.image_path=argv[first];config.argc=argc;config.argv=argv;config.reset_cycles=12;config.debug_bootstrap=&model_debug;
    auto model=std::make_unique<chisa::boom_system::SystemGuider>(config);
    FesvrDtmAdapter<dtm_t> rtl_adapter(rtl_dtm);
    VerilatedContext context;context.threads(1);context.randReset(0);context.commandArgs(argc,argv);
    VTestHarness rtl(&context);rtl.clock=0;rtl.reset=1;rtl.eval();RtlRetirement retired;
    auto model_event=[&](const Event& e){model_results.observe(e);comparison.push(true,e);};
    while(!model_done || !rtl_done) {
      bool progressed=false;
      if(!model_done && comparison.model.pending.size()<4096) {
        if(model_cycles>=max_cycles)throw std::runtime_error("Independent software model timed out");
        auto result=model->step();++model_cycles;progressed=true;
        if(!result.ok)throw std::runtime_error(std::string("Software model step failed: ")+result.failure);
#if defined(CHISA_WIDE_MODEL)
        for(const auto& e:model->retirement_events())model_event(e);
#else
        model_event(model->retirement_event());
#endif
        const auto& dmi=model->last_dmi();model_success|=dmi.exit==1;
        model_done=model_dtm.done()&&dmi.exit!=0;
        if(model_done && model_dtm.exit_code())throw std::runtime_error("Software model program exit failed");
      }
      if(!rtl_done && comparison.rtl.pending.size()<4096) {
        if(rtl_cycles>=max_cycles)throw std::runtime_error("Independent original RTL timed out");
        const bool reset=rtl_cycles<12;const auto driven=rtl_adapter.outputs();
        rtl.reset=reset;drive({*rtl.rootp},driven);rtl.clock=0;rtl.eval();context.timeInc(1);
        auto events=retired.before_edge({*rtl.rootp},rtl_cycles,reset);auto dmi=feedback({*rtl.rootp});
        rtl_success|=rtl.io_success!=0;rtl.clock=1;rtl.eval();context.timeInc(1);
        retired.after_edge(events,RtlFields{*rtl.rootp}.core_clock()!=0);
        for(const auto& e:events){rtl_results.observe(e);comparison.push(false,e);}
        rtl_adapter.advance(reset,dmi);++rtl_cycles;progressed=true;
        rtl_done=rtl_dtm.done()&&driven.exit!=0;
        if(rtl_done && rtl_dtm.exit_code())throw std::runtime_error("Original RTL program exit failed");
        if(context.gotFinish()&&!rtl_done)throw std::runtime_error("Original RTL stopped before program exit");
      }
      if(!progressed)throw std::runtime_error("Independent architecture comparison stalled");
    }
    rtl.final();comparison.finish();model_results.finish();rtl_results.finish();
    if(!model_success||!rtl_success)throw std::runtime_error("Independent program success boundary absent");
    if(comparison.inject)throw std::runtime_error("Negative control was not detected");
    std::printf("ARCHITECTURE_CHECK status=pass workload=dhrystone-500 oracle_injection=none model_mode=%u"
      " compared_retirements=%" PRIu64 " compared_stores=%" PRIu64 " register_scope=written-in-computation"
      " memory_scope=committed-store-footprint memory_bytes=%zu model_cycles=%" PRIu64 " rtl_cycles=%" PRIu64
      " model_program_done=1 rtl_program_done=1 model_functional_checks=%u rtl_functional_checks=%u"
      " begin_pc=%" PRIx64 " end_pc_exclusive=%" PRIx64
      " compared_fields=pc,destination,value,store timer_and_htif_comparison=excluded\n",
      unsigned(chisa::boom_model::kArchitecturalModel),comparison.compared,comparison.stores,comparison.model.state.memory.size(),model_cycles,rtl_cycles,
      model_results.checks,rtl_results.checks,kBegin,kEnd);
    return 0;
  } catch(const std::exception& error) {
    std::fprintf(stderr,"ARCHITECTURE_CHECK status=fail compared_retirements=%" PRIu64
      " model_cycles=%" PRIu64 " rtl_cycles=%" PRIu64 " negative_control=%u injected=%u reason=%s\n",
      comparison.compared,model_cycles,rtl_cycles,comparison.inject,comparison.injected,error.what());return 2;
  }
}
