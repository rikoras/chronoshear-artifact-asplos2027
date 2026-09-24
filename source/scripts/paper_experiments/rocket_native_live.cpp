// Complete checked RTL consumer supplied by the independently executing native
// model. No trace, RTL sidecar or internal RTL-to-model feedback is used.
#include "rocket_native_live_consumer.h"
#include "native_system.h"
#include "oracle_window.h"
#include "system_config.h"
#include "dmi_host_api.h"
#include "tools/dhrystone_functional.h"
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <fstream>
#include <memory>
#include <pthread.h>
#include <sched.h>
#include <stdexcept>
#include <string>
#include <sys/mman.h>
#include <thread>
#include <vector>
namespace {
using namespace chisa::rocket_model;
namespace host = chisa::rocket_fullchip;
constexpr unsigned W = CHISA_CONSUMER_WIDTH, CYCLES = 2*W;
static_assert(W == 4 || W == 8 || W == 16 || W == 32);
void baseline_expand(const std::array<Image,CYCLES>& images, char* block) {
  for (unsigned step = 0; step < CYCLES; ++step) {
    const unsigned slot = step < W ? step : 3*W-1-step;
    for (const auto& stream : kStreams)
      std::memcpy(block + window_offset<W>(stream) + slot*stream.elem_bytes,
                  reinterpret_cast<const char*>(&images[step]) + stream.image_offset, stream.elem_bytes);
  }
}
void pin(unsigned cpu) {
  cpu_set_t mask; CPU_ZERO(&mask); CPU_SET(cpu, &mask);
  if (pthread_setaffinity_np(pthread_self(), sizeof mask, &mask)) throw std::runtime_error("cannot pin execution thread");
}
std::string physical_core(int cpu) {
  const std::string path = "/sys/devices/system/cpu/cpu" + std::to_string(cpu) + "/topology/";
  std::string package, core;
  if (!(std::ifstream(path+"physical_package_id") >> package) || !(std::ifstream(path+"core_id") >> core))
    throw std::runtime_error("cannot establish physical CPU topology");
  return package + ":" + core;
}
struct Join {
  std::thread& thread; std::atomic<bool>& done;
  ~Join() { done.store(true, std::memory_order_release); if (thread.joinable()) thread.join(); }
};
void wait_for_peer(bool pause) {
#if defined(__x86_64__)
  if (pause) { __builtin_ia32_pause(); return; }
#else
  (void)pause;
#endif
  std::this_thread::yield();
}
}
int main(int argc, char** argv) {
  try {
    if (argc < 2) throw std::invalid_argument("usage: run IMAGE [--max-cycles=N]");
    uint64_t max_cycles = 5000000;
    uint64_t inject_cycle = UINT64_MAX;
    bool inject_comb = false, baseline_pack = false, verify_pack = false, profile = false;
    int producer_cpu = -1, consumer_cpu = -1;
    bool pause_wait = true;
    bool ptw_idle_skip = true;
    bool continue_oracle_mismatches = false;
    uint64_t mismatch_log_limit = 4;
    for (int i = 2; i < argc; ++i) {
      const std::string a = argv[i];
      if (a.rfind("--max-cycles=", 0) == 0) max_cycles = std::stoull(a.substr(13));
      else if (a.rfind("--inject-cycle=", 0) == 0) inject_cycle = std::stoull(a.substr(15));
      else if (a == "--inject-kind=comb") inject_comb = true;
      else if (a == "--pack=baseline") baseline_pack = true;
      else if (a == "--pack=transpose") baseline_pack = false;
      else if (a == "--verify-pack") verify_pack = true;
      else if (a == "--profile") profile = true;
      else if (a.rfind("--producer-cpu=", 0) == 0) producer_cpu = std::stoi(a.substr(15));
      else if (a.rfind("--consumer-cpu=", 0) == 0) consumer_cpu = std::stoi(a.substr(15));
      else if (a == "--wait=yield") pause_wait = false;
      else if (a == "--wait=pause") pause_wait = true;
      else if (a == "--ptw-idle-skip=0") ptw_idle_skip = false;
      else if (a == "--ptw-idle-skip=1") ptw_idle_skip = true;
      else if (a == "--continue-oracle-mismatches") continue_oracle_mismatches = true;
      else if (a.rfind("--mismatch-log-limit=", 0) == 0) mismatch_log_limit = std::stoull(a.substr(21));
      else throw std::invalid_argument("unexpected argument: " + a);
    }
    if (max_cycles == 0) throw std::invalid_argument("max-cycles must be positive");
    if (producer_cpu < -1 || consumer_cpu < -1 || producer_cpu >= CPU_SETSIZE || consumer_cpu >= CPU_SETSIZE)
      throw std::invalid_argument("CPU index out of range");
    const bool parallel = consumer_cpu >= 0;
    if (parallel && (producer_cpu < 0 || physical_core(producer_cpu) == physical_core(consumer_cpu)))
      throw std::invalid_argument("parallel mode requires two explicitly named distinct physical cores");
    if (producer_cpu >= 0) pin(producer_cpu);
    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    if (!file) throw std::runtime_error("cannot open native image");
    const auto bytes = file.tellg();
    if (bytes < 0 || bytes > kMemoryBytes) throw std::runtime_error("image outside DRAM");
    auto* memory = static_cast<uint8_t*>(mmap(nullptr, kMemoryBytes, PROT_READ | PROT_WRITE,
                                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
    if (memory == MAP_FAILED) throw std::runtime_error("native DRAM allocation failed");
    file.seekg(0); file.read(reinterpret_cast<char*>(memory), bytes);
    NativeSystem model(0x10040, 32, NativeExecutionMode::Oracle);
    model.set_ptw_idle_skip(ptw_idle_skip);
    model.attach_memory(memory, kMemoryBytes);
    model.write_dram_word(0x80001000, 0); model.write_dram_word(0x80001040, 0);
    host::dmi_host_configure(0x80000000, 0x80001000, 0x80001040);
    rocket_native_live::Consumer rtl(argc, argv, !continue_oracle_mismatches, mismatch_log_limit);
    struct Window {
      std::vector<char> block;
      std::array<rocket_native_live::Cycle,CYCLES> records;
      uint64_t first = 0; bool reset = false;
    };
    std::array<Window,4> ring;
    for (auto& window : ring) window.block.resize(rtl.block_bytes());
    std::vector<char> reference_block(rtl.block_bytes());
    std::array<Image,CYCLES> images;
    OracleWindowExpander<W> expander; // Plan field geometry once, outside timing.
    SystemConfig config;
    DhrystoneFunctional functional{"native"};
    auto read_result = [&](uint64_t address) { return model.read_memory_word(address); };
    uint64_t cycles = 0, console_streak = 0, terminal_streak = 0, tohost = 0;
    bool console_armed = true, terminal_requested = false;
    uint64_t verified_windows = 0;
    double model_ns = 0, pack_ns = 0, consumer_ns = 0;
    using Clock = std::chrono::steady_clock;
    auto elapsed = [](Clock::time_point start) { return std::chrono::duration<double,std::nano>(Clock::now()-start).count(); };
    alignas(64) std::atomic<uint64_t> produced{0};
    alignas(64) std::atomic<uint64_t> consumed{0};
    std::atomic<bool> producer_done{false}, consumer_failed{false};
    std::exception_ptr consumer_error;
    std::thread worker;
    Join join{worker, producer_done};
    uint64_t submitted = 0;
    const auto begin = std::chrono::steady_clock::now();
    if (parallel) worker = std::thread([&] {
      try {
        pin(consumer_cpu);
        uint64_t next = 0;
        for (;;) {
          if (next < produced.load(std::memory_order_acquire)) {
            auto& window = ring[next % ring.size()];
            const auto stage = profile ? Clock::now() : Clock::time_point{};
            rtl.evaluate(window.block.data(), window.records.data(), window.first, window.reset);
            if (profile) consumer_ns += elapsed(stage);
            consumed.store(++next, std::memory_order_release);
          } else if (producer_done.load(std::memory_order_acquire) &&
                     next == produced.load(std::memory_order_acquire)) break;
          else wait_for_peer(pause_wait);
        }
      } catch (...) { consumer_error = std::current_exception(); consumer_failed.store(true, std::memory_order_release); }
    });
    while (cycles < max_cycles && !tohost) {
      if (parallel) {
        while (submitted-consumed.load(std::memory_order_acquire) == ring.size()) {
          if (consumer_failed.load(std::memory_order_acquire)) std::rethrow_exception(consumer_error);
          wait_for_peer(pause_wait);
        }
      }
      auto stage_begin = profile ? Clock::now() : Clock::time_point{};
      const uint64_t first = cycles;
      const bool reset_window = cycles < 64;
      auto& window = ring[submitted % ring.size()];
      auto& block = window.block; auto& records = window.records;
      window.first = first; window.reset = reset_window;
      for (unsigned step = 0; step < CYCLES; ++step, ++cycles) {
        const bool reset = cycles < 64, host_enabled = cycles > 64;
        if (reset != reset_window) throw std::runtime_error("reset crosses window");
        const auto request = host_enabled ? host::dmi_host_outputs() : host::DmiHostOutputs{};
        NativeSystemInputs input;
        input.reset = reset; input.dmi_req_valid = request.request_valid;
        input.dmi_req_addr = request.request_address; input.dmi_req_op = request.request_operation;
        input.dmi_req_data = request.request_data; input.dmi_resp_ready = request.response_ready;
        auto& image = images[step];
        const auto output = model.step(input, &image);
        // debug_printf's first instruction leaves a1 and ra intact. Select
        // real report calls by their saved return PC, not "should be" calls.
        if (output.retirement.retired && output.retirement.pc == 0x80001178)
          functional.observe(model.read_integer_register(1)-4, model.read_integer_register(11), read_result);
        records[step] = {request.request_valid, request.response_ready, request.request_address,
                        request.request_operation, request.request_data, output.dmi_req_ready,
                        output.dmi_resp_valid, output.dmi_resp_resp, output.dmi_resp_data};
        if (cycles == inject_cycle) {
          if (inject_comb) image.mem.srams_mem_0_access_write_0_MPORT_enable ^= 1;
          else image.debug.dmInner_dmInner_ctrlStateReg ^= 1;
          std::fprintf(stderr, "ROCKET_NATIVE_INJECT cycle=%llu stream=%u mask=1\n", (unsigned long long)cycles,
                       inject_comb ? 1054u : 0u);
        }
        if (host_enabled) host::dmi_host_advance(output.dmi_req_ready, output.dmi_resp_valid,
                                               output.dmi_resp_resp, output.dmi_resp_data);
        if (host::dmi_host_failed()) throw std::runtime_error(host::dmi_host_error());
        if (host::dmi_host_tohost_reads()) tohost = host::dmi_host_last_tohost();
        const auto pc = model.committed_pc();
        bool console_wait = false;
        for (auto address : config.console_wait_pc) console_wait |= pc == address;
        if (!console_wait) { console_streak = 0; console_armed = true; }
        else if (console_armed) ++console_streak;
        terminal_streak = pc == config.exit_park_pc || pc == config.trap_park_pc ? terminal_streak+1 : 0;
        if (!reset && !tohost && host::dmi_host_bootstrap_complete() && host::dmi_host_idle()) {
          bool exit_pending = false;
          if (!terminal_requested && (cycles+1)%256 == 0) {
            const auto pending = model.read_memory_word(config.tohost_address);
            exit_pending = (pending >> 48) == 0 && (pending & 1) != 0;
          }
          if (!terminal_requested && (exit_pending || terminal_streak >= 8)) {
            terminal_requested = true; host::dmi_host_request_tohost_read();
          } else if (console_armed && console_streak >= 8) {
            console_armed = false; console_streak = 0; host::dmi_host_request_console_ack();
          }
        }
      }
      if (profile) { model_ns += elapsed(stage_begin); stage_begin = Clock::now(); }
      if (baseline_pack) baseline_expand(images, block.data());
      else expander.expand(images, block.data());
      if (profile) { pack_ns += elapsed(stage_begin); stage_begin = Clock::now(); }
      if (verify_pack) {
        baseline_expand(images, reference_block.data());
        if (block != reference_block) throw std::runtime_error("complete oracle block differs from baseline packing");
        ++verified_windows;
      }
      if (parallel) produced.store(++submitted, std::memory_order_release);
      else {
        rtl.evaluate(block.data(), records.data(), first, reset_window);
        ++submitted;
        if (profile) consumer_ns += elapsed(stage_begin);
      }
    }
    producer_done.store(true, std::memory_order_release);
    if (worker.joinable()) worker.join();
    if (consumer_error) std::rethrow_exception(consumer_error);
    const auto endpoint = rtl.endpoint();
    uint64_t final_mismatches = endpoint.pc != model.writeback_pc();
    for (unsigned index = 0; index < 32; ++index) {
      if (endpoint.x[index] != model.read_integer_register(index)) ++final_mismatches;
      const auto expected = model.read_float_recoded(index);
      if (endpoint.f_low[index] != uint64_t(expected) || endpoint.f_high[index] != uint64_t(expected >> 64)) ++final_mismatches;
    }
    const bool functional_pass = tohost == 1 && functional.finish(read_result);
    const double ns = std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now()-begin).count();
    const bool pass = functional_pass && final_mismatches == 0 && (continue_oracle_mismatches || rtl.mismatches() == 0);
    std::printf("ROCKET_NATIVE_LIVE status=%s width=%u cycles=%llu streams=1092 oracle_mismatch_signals=%llu oracle_checked_signals=%llu boundary_mismatches=0 final_mismatches=%llu tohost=%llu model=native trace=none threads=%u physical_cores=%u wall_ns_per_cycle=%.3f producer_cpu=%d consumer_cpu=%d\n",
                pass ? "pass" : "fail", W, (unsigned long long)cycles,
                (unsigned long long)rtl.oracle_mismatch_signals(), (unsigned long long)rtl.oracle_checked_signals(),
                (unsigned long long)final_mismatches, (unsigned long long)tohost, parallel ? 2u : 1u, parallel ? 2u : 1u,
                ns/cycles, sched_getcpu(), consumer_cpu);
    std::printf("ORACLE_MISMATCH_DETAIL raw_events=%llu\n", (unsigned long long)rtl.mismatches());
    std::printf("ROCKET_ORACLE_POLICY mode=%s checks=enabled\n", continue_oracle_mismatches ? "report-only" : "strict");
    if (verify_pack) std::printf("ROCKET_NATIVE_PACK_MATCH windows=%llu streams=1092 bytes_per_window=%llu\n",
                                 (unsigned long long)verified_windows, (unsigned long long)reference_block.size());
    if (profile) std::printf("ROCKET_NATIVE_PROFILE model_ns_per_cycle=%.3f pack_ns_per_cycle=%.3f consumer_ns_per_cycle=%.3f\n",
                             model_ns/cycles, pack_ns/cycles, consumer_ns/cycles);
    munmap(memory, kMemoryBytes);
    return pass ? 0 : 1;
  } catch (const std::exception& e) {
    std::fprintf(stderr, "ROCKET_NATIVE_LIVE_ERROR %s\n", e.what()); return 2;
  }
}
