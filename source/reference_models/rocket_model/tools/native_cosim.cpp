// Independent native-system vs full-RTL diagnostic. Only common external DMI
// host inputs and the initial program image are shared. The native model never
// samples RTL internal wires, and the RTL never consumes native predictions.
// This gate checks all 1051 register streams plus DMI; the 41 combinational
// oracle streams remain an obligation of the complete checked consumer.
#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"
#include "native_system.h"
#include "system_config.h"
#include "dmi_host_api.h"
#include "generated/verilator_bindings.inc"
#include "dhrystone_functional.h"
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/mman.h>
#include <vector>
using namespace chisa::rocket_model;
using chisa::rocket_fullchip::DmiHostOutputs;

// Independent retirement sequences tolerate timing shifts but never discard
// a retired instruction. This supplements, and does not relax, the raw gate.
struct Retired {
  uint64_t pc=0,value=0;
  uint32_t instruction=0;
  unsigned rd=0;
  bool write=false,value_valid=false;
};
struct RetireCompare {
  std::deque<Retired> model,rtl;
  uint64_t compared=0,mismatches=0,values=0;
  void compare() {
    while(!model.empty() && !rtl.empty()) {
      const auto a=model.front(),b=rtl.front();model.pop_front();rtl.pop_front();
      const bool mismatch=a.pc!=b.pc || a.instruction!=b.instruction || a.write!=b.write ||
        (a.write && (a.rd!=b.rd || a.value_valid!=b.value_valid || (a.value_valid && a.value!=b.value)));
      ++compared;values+=a.write && a.value_valid;
      if(mismatch && mismatches++<12)
        std::printf("ORDERED_RETIRE_MISMATCH seq=%llu model_pc=%llx rtl_pc=%llx model_inst=%x rtl_inst=%x model_rd=%u rtl_rd=%u model_value=%llx rtl_value=%llx\n",
          (unsigned long long)compared,(unsigned long long)a.pc,(unsigned long long)b.pc,a.instruction,b.instruction,
          a.rd,b.rd,(unsigned long long)a.value,(unsigned long long)b.value);
    }
  }
};

template<class T> uint64_t tap_value(const T& v) { return static_cast<uint64_t>(v); }
template<class T, std::size_t N> uint64_t tap_value(const VlUnpacked<T,N>& v) { return static_cast<uint64_t>(v[0]); }
template<std::size_t N> uint64_t tap_value(const VlWide<N>& v) { return (uint64_t(v[1]) << 32) | v[0]; }
template<class F> void with_bank(VTestHarness___024root& root, unsigned bank, F f) {
  switch (bank) {
#define BANK(n) case n: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_##n); break
    BANK(0); BANK(1); BANK(2); BANK(3); BANK(4); BANK(5); BANK(6); BANK(7);
#undef BANK
  }
}
uint64_t rtl_memory(VTestHarness___024root& root, uint64_t address) {
  if ((address & 7) || address < 0x80000000 || address > 0x8ffffff8)
    throw std::out_of_range("RTL coherent read outside aligned DRAM");
#define DC(field) root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__##field
  const unsigned set = (address >> 6) & 63, tag = (address >> 12) & 0xfffff, row = (address >> 3) & 511;
  const uint32_t metadata[] = {DC(tag_array_0)[set], DC(tag_array_1)[set], DC(tag_array_2)[set], DC(tag_array_3)[set]};
  for (unsigned way = 0; way < 4; ++way) if ((metadata[way] >> 20) && (metadata[way]&0xfffff) == tag) {
    uint64_t value = 0;
#define COL(n) case n: value |= uint64_t(DC(data__DOT__data_arrays_0_##n)[row]) << (8*(n%8)); break
    for (unsigned byte = 0; byte < 8; ++byte) switch (way*8+byte) {
      COL(0);COL(1);COL(2);COL(3);COL(4);COL(5);COL(6);COL(7);
      COL(8);COL(9);COL(10);COL(11);COL(12);COL(13);COL(14);COL(15);
      COL(16);COL(17);COL(18);COL(19);COL(20);COL(21);COL(22);COL(23);
      COL(24);COL(25);COL(26);COL(27);COL(28);COL(29);COL(30);COL(31);
    }
#undef COL
    return value;
  }
#undef DC
  uint64_t value = 0;
  for (unsigned byte = 0; byte < 8; ++byte)
    with_bank(root, byte, [&](auto& bank) { value |= uint64_t(bank[(address-0x80000000)>>3]) << (8*byte); });
  return value;
}
extern "C" int debug_tick(svBit* valid, svBit, int*, int*, int*, svBit, svBit* ready, int, int) {
  *valid = *ready = 0; return 0;
}
int main(int argc, char** argv) {
  uint64_t cycles = 4096;
  bool require_completion = false;
  std::string image_path;
  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    if (a.rfind("--cycles=", 0) == 0) cycles = std::stoull(a.substr(9));
    else if (a.rfind("--image=", 0) == 0) image_path = a.substr(8);
    else if (a == "--require-completion") require_completion = true;
    else throw std::invalid_argument("unknown argument: " + a);
  }
  auto* memory = static_cast<uint8_t*>(mmap(nullptr, 0x10000000, PROT_READ | PROT_WRITE,
                                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
  if (memory == MAP_FAILED) throw std::runtime_error("native memory mmap failed");
  auto context = std::make_unique<VerilatedContext>();
  context->randReset(0); context->threads(1); context->commandArgs(argc, argv);
  auto rtl = std::make_unique<VTestHarness>(context.get());
  auto& root = *rtl->rootp;
  rtl->clock = 0; rtl->reset = 1; rtl->eval();
  if (!image_path.empty()) {
    std::ifstream file(image_path, std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("cannot open image");
    const auto bytes = file.tellg();
    if (bytes < 0 || bytes > 0x10000000) throw std::runtime_error("image size outside memory");
    file.seekg(0); file.read(reinterpret_cast<char*>(memory), bytes);
    for (size_t i = 0; i < static_cast<size_t>(bytes); ++i)
      with_bank(root, i & 7, [&](auto& bank) { bank[i >> 3] = memory[i]; });
  }
  NativeSystem native(0x10040, 32, NativeExecutionMode::Oracle);
  native.attach_memory(memory, 0x10000000);
  for (uint64_t address : {UINT64_C(0x80001000), UINT64_C(0x80001040)}) {
    native.write_dram_word(address, 0);
    for (unsigned byte = 0; byte < 8; ++byte)
      with_bank(root, byte, [&](auto& bank) { bank[(address - 0x80000000) >> 3] = 0; });
  }
  chisa::rocket_fullchip::dmi_host_configure(0x80000000, 0x80001000, 0x80001040);
  uint64_t mismatches = 0, boundary_mismatches = 0;
  std::vector<uint64_t> mismatch_count(kStreamCount), first_cycle(kStreamCount), first_native(kStreamCount), first_rtl(kStreamCount),
                        last_cycle(kStreamCount), postreset_count(kStreamCount), first_postreset(kStreamCount);
  Image image;
  SystemConfig config;
  uint64_t simulated = 0, console_streak = 0, terminal_streak = 0, tohost = 0;
  bool console_armed = true, terminal_requested = false;
  DhrystoneFunctional native_functional{"native"}, rtl_functional{"rtl"};
  RetireCompare retirement;
  auto read_native = [&](uint64_t address) { return native.read_memory_word(address); };
  auto read_rtl = [&](uint64_t address) { return rtl_memory(root, address); };
  for (uint64_t cycle = 0; cycle < cycles; ++cycle) {
    const bool reset = cycle < 64;
    const bool host_enabled = cycle > 64;
    const auto host = host_enabled ? chisa::rocket_fullchip::dmi_host_outputs() : DmiHostOutputs{};
    NativeSystemInputs in;
    in.reset = reset; in.dmi_req_valid = host.request_valid; in.dmi_req_addr = host.request_address;
    in.dmi_req_data = host.request_data; in.dmi_req_op = host.request_operation; in.dmi_resp_ready = host.response_ready;
    rtl->reset = reset;
    root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg = host.request_valid;
    root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg = host.request_address;
    root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg = host.request_operation;
    root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg = host.request_data;
    root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg = host.response_ready;
    root.TestHarness__DOT__SimDTM__DOT__exit_reg = 0;
    rtl->clock = 0; rtl->eval(); context->timeInc(1);
#define CORE(field) root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__##field
    if (CORE(csr_io_retire)) rtl_functional.observe(CORE(coreMonitorBundle_pc), CORE(rf)[20], read_rtl);
    if(!reset && CORE(csr_io_retire) && !CORE(csr_io_status_debug)) {
      Retired event;event.pc=CORE(coreMonitorBundle_pc);event.instruction=CORE(wb_reg_inst);
      event.rd=(event.instruction>>7)&31;event.write=CORE(wb_ctrl_wxd) && event.rd!=0;
      event.value_valid=event.write && !CORE(wb_set_sboard);event.value=CORE(rf_wdata);
      retirement.rtl.push_back(event);
    }
#undef CORE
    const auto out = native.step(in, &image);
    if (out.retirement.retired) native_functional.observe(out.retirement.pc, native.read_integer_register(11), read_native);
    if(out.retirement.retired && !out.retirement.debug_mode) {
      const auto& r=out.retirement;
      retirement.model.push_back({r.pc,r.xvalue,r.expanded_instruction,r.xrd,r.x_write,r.x_value_valid});
    }
    retirement.compare();
#define TAP(index, flat, member, width) do { \
      uint64_t value = 0; \
      std::memcpy(&value, reinterpret_cast<const char*>(&image) + kStreams[index].image_offset, kStreams[index].elem_bytes); \
      const uint64_t expected = tap_value(root.member) & (UINT64_MAX >> (64-width)); \
      if (value != expected) { \
        if (mismatch_count[index]++ == 0) { first_cycle[index] = cycle; first_native[index] = value; first_rtl[index] = expected; } \
        last_cycle[index] = cycle; \
        if (!reset && postreset_count[index]++ == 0) first_postreset[index] = cycle; \
        ++mismatches; \
      } \
    } while (0);
    ROCKET_MODEL_TAPS(TAP)
#undef TAP
    const bool boundary = out.dmi_req_ready != bool(root.TestHarness__DOT__SimDTM_debug_req_ready) ||
      out.dmi_resp_valid != bool(root.TestHarness__DOT__SimDTM_debug_resp_valid) ||
      (out.dmi_resp_valid && (out.dmi_resp_data != root.TestHarness__DOT__SimDTM_debug_resp_bits_data ||
                            out.dmi_resp_resp != root.TestHarness__DOT__SimDTM_debug_resp_bits_resp));
    if (boundary && boundary_mismatches++ < 12)
      std::printf("DMI_MISMATCH cycle=%llu native_ready=%u rtl_ready=%u native_valid=%u rtl_valid=%u\n",
                  (unsigned long long)cycle, out.dmi_req_ready, root.TestHarness__DOT__SimDTM_debug_req_ready,
                  out.dmi_resp_valid, root.TestHarness__DOT__SimDTM_debug_resp_valid);
    if (host_enabled) chisa::rocket_fullchip::dmi_host_advance(out.dmi_req_ready, out.dmi_resp_valid,
                                                           out.dmi_resp_resp, out.dmi_resp_data);
    rtl->clock = 1; rtl->eval(); context->timeInc(1);
    simulated = cycle + 1;
    namespace host_api = chisa::rocket_fullchip;
    if (host_api::dmi_host_failed()) throw std::runtime_error(host_api::dmi_host_error());
    if (host_api::dmi_host_tohost_reads()) tohost = host_api::dmi_host_last_tohost();
    const auto pc = native.committed_pc();
    bool console_wait = false;
    for (auto address : config.console_wait_pc) console_wait |= pc == address;
    if (!console_wait) { console_streak = 0; console_armed = true; }
    else if (console_armed) ++console_streak;
    terminal_streak = pc == config.exit_park_pc || pc == config.trap_park_pc ? terminal_streak + 1 : 0;
    if (!reset && !tohost && host_api::dmi_host_bootstrap_complete() && host_api::dmi_host_idle()) {
      bool exit_pending = false;
      if (!terminal_requested && simulated % 256 == 0) {
        const auto pending = native.read_memory_word(config.tohost_address);
        exit_pending = (pending >> 48) == 0 && (pending & 1) != 0;
      }
      if (!terminal_requested && (exit_pending || terminal_streak >= 8)) {
        terminal_requested = true; host_api::dmi_host_request_tohost_read();
      } else if (console_armed && console_streak >= 8) {
        console_armed = false; console_streak = 0; host_api::dmi_host_request_console_ack();
      }
    }
    if (tohost && simulated % 64 == 0) break;
  }
  for (unsigned index = 0; index < kStreamCount; ++index) if (mismatch_count[index])
    std::printf("ORACLE_MISMATCH index=%u first=%llu last=%llu count=%llu postreset=%llu first_postreset=%llu native=0x%llx rtl=0x%llx flat=%s\n", index,
                (unsigned long long)first_cycle[index], (unsigned long long)last_cycle[index],
                (unsigned long long)mismatch_count[index], (unsigned long long)postreset_count[index], (unsigned long long)first_postreset[index],
                (unsigned long long)first_native[index], (unsigned long long)first_rtl[index], kStreams[index].flat);
  uint64_t final_mismatches = 0;
  std::printf("ROCKET_ORDERED_RETIRE compared=%llu mismatches=%llu model_pending=%zu rtl_pending=%zu immediate_integer_values=%llu scope=nondebug-pc,expanded-instruction,integer-destination,available-value\n",
      (unsigned long long)retirement.compared,(unsigned long long)retirement.mismatches,
      retirement.model.size(),retirement.rtl.size(),(unsigned long long)retirement.values);
  final_mismatches += retirement.mismatches + retirement.model.size() + retirement.rtl.size();
  if (tohost == 1) {
    final_mismatches += !native_functional.finish(read_native);
    final_mismatches += !rtl_functional.finish(read_rtl);
  }
#define TILE(field) root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__##field
  for (unsigned index = 1; index < 32; ++index)
    if (native.read_integer_register(index) != TILE(core__DOT__rf)[31-index]) ++final_mismatches;
  for (unsigned index = 0; index < 32; ++index) {
    const auto& v = TILE(fpuOpt__DOT__regfile)[index];
    const hf::u128 expected = (hf::u128(v[2] & 1) << 64) | (uint64_t(v[1]) << 32) | v[0];
    if (native.read_float_recoded(index) != expected) ++final_mismatches;
  }
#undef TILE
  std::printf("ROCKET_NATIVE_COSIM cycles=%llu registers=1051 mismatch=%llu boundary_mismatch=%llu final_rf_mismatch=%llu tohost=%llu comb_checked=0\n",
              (unsigned long long)simulated, (unsigned long long)mismatches, (unsigned long long)boundary_mismatches,
              (unsigned long long)final_mismatches, (unsigned long long)tohost);
  munmap(memory, 0x10000000);
  return mismatches || boundary_mismatches || final_mismatches || (require_completion && tohost != 1) ? 1 : 0;
}
