// Standalone directed trace-contract gate. This uses no model or RTL headers.
#include "architecture_reference.h"
#include <filesystem>
#include <iostream>

namespace arch = chisa::rocket_architecture;
namespace {
void require(bool condition, const char* why) { if (!condition) throw std::runtime_error(why); }
arch::Sample instruction(uint64_t cycle, uint64_t pc, uint32_t inst) {
  arch::Sample s;
  s.cycle = cycle; s.pc = pc; s.instruction = s.expanded_instruction = inst;
  s.retired = true; s.privilege = 3;
  return s;
}
arch::Configuration config(const std::string& role) {
  arch::Configuration c;
  c.role = role; c.firrtl_sha256 = arch::kLockedFirrtlSha256;
  c.program_begin = 0x80000000; c.program_end = 0x80001000;
  c.image_bytes = 0x1000; c.image_fnv64 = 0x1234;
  return c;
}
enum class Fault { None, NoConfirmation, WrongConfirmation, Unresolved, Orphan, CutoffOrphan, Outside, Atomic, Trap };
void fixture(const std::filesystem::path& directory, const std::string& name,
             const std::string& role, unsigned time_scale, Fault fault) {
  arch::Recorder recorder(config(role), (directory/(name+".jsonl")).string());
  auto observe = [&](arch::Sample s) { s.cycle *= time_scale; recorder.observe(s); };
  auto s = instruction(10,0x80000000,0x00500093);
  s.x_write=true;s.xrd=1;s.x_value_valid=true;s.xvalue=5;observe(s);
  s=instruction(11,0x80000004,0x020001d3);s.fp_write=true;s.frd=3;observe(s);
  s=instruction(12,0x80000008,0x0220c133);s.x_write=true;s.xrd=2;observe(s);
  s=instruction(13,0x8000000c,0x02000253);s.fp_write=true;s.frd=4;
  s.fp[0]={true,4,UINT64_C(0xffffffff3f800000)};observe(s);
  s={};s.cycle=14;s.fp[1]={true,3,UINT64_C(0x4000000000000000)};s.late_x={true,2,7};observe(s);
  s=instruction(15,0x80000010,0x020001d3);s.fp_write=true;s.frd=3;observe(s);
  s=instruction(16,0x80000014,0x00100023);s.store_address=0x80002007;s.store_value=UINT64_C(0x123456789abcdef0);
  if (fault==Fault::Orphan) s.fp[0]={true,7,9};
  if (fault==Fault::Outside) s.pc=0x10000;
  if (fault==Fault::Atomic) s.instruction=s.expanded_instruction=0x0800302f;
  observe(s);
  if (fault==Fault::Trap) {
    s={};s.cycle=16*time_scale+1;s.pc=0x80000018;s.trapped=true;s.cause=2;recorder.observe(s);
  }
  s=instruction(17,0x80000018,0x00103023);s.store_address=0x80001000;s.store_value=1;
  if (fault==Fault::CutoffOrphan) s.late_x={true,9,0x55};
  observe(s);
  require(recorder.cutoff_seen() && !recorder.done(), "cutoff must retain older pending FP result");
  s=instruction(18,0x8000001c,0x06600393);s.x_write=true;s.x_value_valid=true;s.xrd=7;s.xvalue=0x66;observe(s);
  if (fault!=Fault::Unresolved) { s={};s.cycle=19;s.fp[0]={true,3,UINT64_C(0xffffffff40000000)};observe(s); }
  s={};s.cycle=20;s.debug_mode=true;s.late_x={true,5,0xbad};observe(s);
  if (fault!=Fault::NoConfirmation) recorder.confirm_tohost(fault==Fault::WrongConfirmation?0:1);
  require(recorder.finish((directory/(name+".summary.json")).string()) == (fault==Fault::None), "fixture completion classification");
}
void reset_gate(const std::filesystem::path& directory) {
  arch::Recorder recorder(config("native-model"),(directory/"reset.jsonl").string());
  auto s=instruction(1,0x80000000,0x13);recorder.observe(s);s={};s.reset=true;s.cycle=2;
  bool threw=false;try {recorder.observe(s);} catch(const std::runtime_error&) {threw=true;}
  require(threw,"reset must reject a partially recorded epoch");
}
void dual_port_gate(const std::filesystem::path& directory) {
  arch::Recorder recorder(config("native-model"),(directory/"dual-port.jsonl").string());
  auto s=instruction(1,0x80000000,0x020001d3);s.fp_write=true;s.frd=3;recorder.observe(s);
  s.cycle=2;s.pc+=4;recorder.observe(s);
  s={};s.cycle=3;s.fp[0]={true,3,11};s.fp[1]={true,3,22};recorder.observe(s);
  s=instruction(4,0x80000008,0x00103023);s.store_address=0x80001000;s.store_value=1;recorder.observe(s);
  recorder.confirm_tohost(1);
  require(recorder.finish((directory/"dual-port.summary.json").string()),"same-address physical port completion order");
}
}  // namespace
int main(int argc,char**argv) {
  try {
    if (argc!=2) throw std::invalid_argument("usage: architecture_recorder_test OUTPUT_DIRECTORY");
    const std::filesystem::path directory(argv[1]);std::filesystem::create_directories(directory);
    fixture(directory,"reference","rtl-reference",1,Fault::None);
    fixture(directory,"model","native-model",3,Fault::None);
    for (auto pair : {std::pair<const char*,Fault>{"unconfirmed",Fault::NoConfirmation},
                     {"wrong-confirmation",Fault::WrongConfirmation},{"unresolved",Fault::Unresolved},
                     {"orphan",Fault::Orphan},{"cutoff-orphan",Fault::CutoffOrphan},
                     {"outside",Fault::Outside},{"atomic",Fault::Atomic},{"trap",Fault::Trap}})
      fixture(directory,pair.first,"native-model",3,pair.second);
    reset_gate(directory);dual_port_gate(directory);
    std::cout << "ARCHITECTURE_RECORDER_PASS fixtures=12\n";
    return 0;
  } catch(const std::exception& e) {
    std::cerr << "ARCHITECTURE_RECORDER_FAIL " << e.what() << '\n';return 1;
  }
}
