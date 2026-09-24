// Single-instance (mono) replay of a reference-oracle trace: the same driver
// as run_partitioned_replay.cpp but calling the whole-design eval_forward /
// eval_reverse bodies, so a header emitted without partitions can be timed
// over [--timing-from, end) exactly like a partition thread.
// Derived from run_partitioned_replay.cpp; one host thread per emitted partition, each
// running its own TestHarness instance over the same reference-oracle trace.
// Partitions never exchange data inside a window (every cross-partition
// register read is an oracle stream), so the threads run fully decoupled;
// the wall time of the slowest thread is the per-cycle cost of the
// configuration. Compile against a header emitted with V2_PARTITION_FILE and
// SCRATCH_MODE=member (file-scope scratch would be shared between instances).
#include "TestHarness.h"

#include <pthread.h>
#include <sched.h>

#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include "extmodule_bindings.h"
#include "reference_oracle_trace.h"

#ifndef CAPTURE_W
#define CAPTURE_W 16
#endif
constexpr unsigned kReplayW = CAPTURE_W;

namespace {

using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::ReferenceOracleCycleRecord;
using chisa::boom_repcut::ReferenceOracleTraceHeader;
using chisa::boom_repcut::assign_port;
using chisa::boom_repcut::initialize_plusarg_readers;
using chisa::boom_repcut::kReferenceOracleTraceMagic;
using chisa::boom_repcut::kReferenceOracleTraceVersion;
using chisa::boom_repcut::port_value;
using chisa::boom_repcut::simdtm_ports;
using chisa::boom_repcut::trace_dmi_feedback;
using chisa::boom_repcut::trace_dtm_outputs;

struct Options {
  std::string trace_path;
  bool verbose = false;
  std::uint64_t timing_from = 0;
  int threads = -1;                 // default: every emitted partition
  int check_partition = 0;          // the partition that owns the harness sinks
  std::vector<int> cpus;            // optional pinning, one per thread
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(stderr,
               "usage: %s --trace=FILE [--threads=N] [--cpus=a,b,...] "
               "[--timing-from=N] [--check-partition=P] [--verbose]\n",
               program);
  std::exit(2);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    if (argument == "--") break;
    if (argument.rfind("--trace=", 0) == 0) { options.trace_path = argument.substr(8); continue; }
    if (argument == "--verbose") { options.verbose = true; continue; }
    if (argument.rfind("--timing-from=", 0) == 0) { options.timing_from = std::stoull(argument.substr(14)); continue; }
    if (argument.rfind("--threads=", 0) == 0) { options.threads = std::stoi(argument.substr(10)); continue; }
    if (argument.rfind("--check-partition=", 0) == 0) { options.check_partition = std::stoi(argument.substr(18)); continue; }
    if (argument.rfind("--cpus=", 0) == 0) {
      std::string list = argument.substr(7);
      std::size_t pos = 0;
      while (pos <= list.size()) {
        const std::size_t comma = list.find(',', pos);
        const std::string item = list.substr(pos, comma == std::string::npos ? std::string::npos : comma - pos);
        if (!item.empty()) options.cpus.push_back(std::stoi(item));
        if (comma == std::string::npos) break;
        pos = comma + 1;
      }
      continue;
    }
    if (argument.rfind("+", 0) == 0) continue;  // plusargs go to the harness
    usage(argv[0], ("unknown option " + argument).c_str());
  }
  if (options.trace_path.empty()) usage(argv[0], "--trace is required");
  return options;
}

struct Trace {
  ReferenceOracleTraceHeader header{};
  std::vector<ReferenceOracleCycleRecord> cycles;
  std::vector<char> blocks;
};

Trace read_trace(const std::string& path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::runtime_error("cannot open trace: " + path);
  Trace trace;
  input.read(reinterpret_cast<char*>(&trace.header), sizeof(trace.header));
  if (!input || trace.header.magic != kReferenceOracleTraceMagic ||
      trace.header.version != kReferenceOracleTraceVersion)
    throw std::runtime_error("invalid reference-oracle trace header");
  if (trace.header.width != kReplayW ||
      trace.header.cycle_record_bytes != sizeof(ReferenceOracleCycleRecord) ||
      trace.header.oracle_block_bytes != static_cast<std::uint64_t>(ORACLE_BLOCK_BYTES))
    throw std::runtime_error("trace and generated ABI disagree");
  if (trace.header.cycles == 0 || trace.header.cycles % (2 * kReplayW) != 0 ||
      trace.header.reset_cycles >= trace.header.cycles ||
      trace.header.reset_cycles % kReplayW != 0)
    throw std::runtime_error("trace does not contain complete halves");
  if (trace.header.cycles > static_cast<std::uint64_t>(ORACLE_NUM_CYCLES))
    throw std::runtime_error("ORACLE_NUM_CYCLES does not cover this trace");
  trace.cycles.resize(static_cast<std::size_t>(trace.header.cycles));
  trace.blocks.resize(static_cast<std::size_t>(trace.header.oracle_blocks * trace.header.oracle_block_bytes));
  input.read(reinterpret_cast<char*>(trace.cycles.data()),
             static_cast<std::streamsize>(trace.cycles.size() * sizeof(trace.cycles[0])));
  input.read(trace.blocks.data(), static_cast<std::streamsize>(trace.blocks.size()));
  if (!input) throw std::runtime_error("truncated reference-oracle trace");
  return trace;
}

template <typename Ports>
void drive_lane(Ports& ports, int lane, const DtmOutputs& outputs) {
  assign_port(ports.debug_req_valid[lane], outputs.req_valid);
  assign_port(ports.debug_req_bits_addr[lane], outputs.req_addr);
  assign_port(ports.debug_req_bits_op[lane], outputs.req_op);
  assign_port(ports.debug_req_bits_data[lane], outputs.req_data);
  assign_port(ports.debug_resp_ready[lane], outputs.resp_ready);
  assign_port(ports.exit[lane], outputs.exit);
}

template <typename Ports>
DmiFeedback feedback_lane(const Ports& ports, int lane) {
  return DmiFeedback{
      port_value(ports.debug_req_ready[lane]) != 0,
      port_value(ports.debug_resp_valid[lane]) != 0,
      static_cast<std::uint32_t>(port_value(ports.debug_resp_bits_resp[lane])),
      static_cast<std::uint32_t>(port_value(ports.debug_resp_bits_data[lane]))};
}

struct ThreadStats {
  double eval_seconds = 0;
  std::uint64_t timed_cycles = 0;
  std::uint64_t mismatches = 0;
  bool assert_triggered = false;
  std::string error;
};

void run_partition(int p, const Options& options, const Trace& trace,
                   int argc, char** argv, int cpu, ThreadStats& stats) {
  if (cpu >= 0) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);
    pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
  }
  try {
    auto dut = std::make_unique<TestHarness>();
    initialize_plusarg_readers<kReplayW>(*dut, argc, argv);
    dut->oracle_win_base = trace.blocks.data();
    auto& ports = simdtm_ports(*dut);
    std::size_t expected_block = 0;
    std::chrono::duration<double> eval_elapsed{};
    for (std::uint64_t first = 0; first < trace.header.cycles; first += kReplayW) {
      const bool forward = ((first / kReplayW) % 2) == 0;
      const bool reset = trace.cycles[static_cast<std::size_t>(first)].reset != 0;
      for (unsigned step = 0; step < kReplayW; ++step) {
        const auto& record = trace.cycles[static_cast<std::size_t>(first + step)];
        if ((record.reset != 0) != reset)
          throw std::runtime_error("reset changes inside a SIMD half-window");
        const int lane = forward ? static_cast<int>(step) : static_cast<int>(kReplayW - 1 - step);
        drive_lane(ports, lane, trace_dtm_outputs(record));
      }
      assign_port(dut->reset, reset);
      dut->oracle_win_base = trace.blocks.data() + expected_block * ORACLE_BLOCK_BYTES;
      const auto eval_begin = std::chrono::steady_clock::now();
      if (forward) dut->eval_forward(true, options.verbose, !reset);
      else dut->eval_reverse(true, options.verbose, !reset);
      const auto eval_end = std::chrono::steady_clock::now();
      if (first >= options.timing_from) {
        eval_elapsed += eval_end - eval_begin;
        stats.timed_cycles += kReplayW;
      }
      if (p == options.check_partition) {
        for (unsigned step = 0; step < kReplayW; ++step) {
          const std::uint64_t cycle = first + step;
          const auto& record = trace.cycles[static_cast<std::size_t>(cycle)];
          const int lane = forward ? static_cast<int>(step) : static_cast<int>(kReplayW - 1 - step);
          const DmiFeedback actual = feedback_lane(ports, lane);
          const DmiFeedback expected = trace_dmi_feedback(record);
          if (!(actual == expected))
            throw std::runtime_error("DMI feedback mismatch at cycle " + std::to_string(cycle));
          const bool success = port_value(dut->io_success[lane]) != 0;
          if (success != (record.io_success != 0))
            throw std::runtime_error("io_success mismatch at cycle " + std::to_string(cycle));
        }
      }
      if (!reset && !forward) ++expected_block;
    }
    stats.eval_seconds = eval_elapsed.count();
    stats.mismatches = dut->verify_mismatches;
    stats.assert_triggered = dut->assert_triggered;
  } catch (const std::exception& e) {
    stats.error = e.what();
  }
}

}  // namespace

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);
    const int threads = 1;  // mono: one whole-design instance
    const Trace trace = read_trace(options.trace_path);
    std::vector<ThreadStats> stats(static_cast<std::size_t>(threads));
    std::vector<std::thread> workers;
    const auto wall_begin = std::chrono::steady_clock::now();
    for (int p = 0; p < threads; ++p) {
      const int cpu = static_cast<std::size_t>(p) < options.cpus.size() ? options.cpus[static_cast<std::size_t>(p)] : -1;
      workers.emplace_back(run_partition, p, std::cref(options), std::cref(trace), argc, argv, cpu,
                           std::ref(stats[static_cast<std::size_t>(p)]));
    }
    for (auto& worker : workers) worker.join();
    const std::chrono::duration<double> wall = std::chrono::steady_clock::now() - wall_begin;
    bool ok = true;
    double max_ns = 0, sum_ns = 0;
    for (int p = 0; p < threads; ++p) {
      const auto& s = stats[static_cast<std::size_t>(p)];
      const double ns = s.timed_cycles ? s.eval_seconds * 1e9 / static_cast<double>(s.timed_cycles) : 0;
      max_ns = std::max(max_ns, ns);
      sum_ns += ns;
      std::printf("PARTITION p=%d timed_cycles=%" PRIu64 " eval_seconds=%.6f ns_per_cycle=%.1f mismatches=%" PRIu64 "%s%s%s\n",
                  p, s.timed_cycles, s.eval_seconds, ns, s.mismatches,
                  s.assert_triggered ? " ASSERT" : "", s.error.empty() ? "" : " error=", s.error.c_str());
      if (!s.error.empty() || s.mismatches != 0 || s.assert_triggered) ok = false;
    }
    std::printf("%s threads=%d cycles=%" PRIu64 " max_ns_per_cycle=%.1f sum_ns_per_cycle=%.1f wall_seconds=%.3f\n",
                ok ? "MONO_REPLAY_OK" : "MONO_REPLAY_FAILED", threads, trace.header.cycles,
                max_ns, sum_ns, wall.count());
    return ok ? 0 : 1;
  } catch (const std::exception& e) {
    std::fprintf(stderr, "error: %s\n", e.what());
    return 1;
  }
}
