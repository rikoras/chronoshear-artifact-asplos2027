// Width-generic variant of run_w4_reference_oracle_differential.cpp.
// Consumes a reference-oracle trace whose blocks were assembled (or repacked)
// for CHISA_CONSUMER_WIDTH lanes, drives the DMI/boundary contract per lane,
// lets the generated verify statements cross-check every injected oracle, and
// optionally reports eval-only throughput. The W=4 tool remains authoritative
// for the formal artifact; this one exists so wider builds can be exercised
// against real workload data instead of zero-state benches.
#include "TestHarness.h"

#include <cerrno>
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
#include <vector>

#include "extmodule_bindings.h"
#include "reference_oracle_trace.h"

#ifndef CHISA_CONSUMER_WIDTH
#error "define CHISA_CONSUMER_WIDTH to the generated lane count"
#endif

namespace {

constexpr unsigned kW = CHISA_CONSUMER_WIDTH;

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
  bool eval_timing = false;
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(stderr,
               "usage: %s --trace=FILE [--verbose] [--eval-timing] "
               "[+RTL_PLUSARG...]\n",
               program);
  std::exit(error ? 2 : 0);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int index = 1; index < argc; ++index) {
    const std::string argument(argv[index]);
    if (argument == "--help") usage(argv[0]);
    if (argument == "--verbose") { options.verbose = true; continue; }
    if (argument == "--eval-timing") { options.eval_timing = true; continue; }
    constexpr const char* trace_prefix = "--trace=";
    if (argument.rfind(trace_prefix, 0) == 0) {
      options.trace_path = argument.substr(std::strlen(trace_prefix));
      continue;
    }
    if (!argument.empty() && argument[0] == '+') continue;
    usage(argv[0], "unknown option");
  }
  if (options.trace_path.empty()) usage(argv[0], "missing --trace=FILE");
  return options;
}

struct Trace {
  ReferenceOracleTraceHeader header;
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
  if (trace.header.width != kW ||
      trace.header.cycle_record_bytes != sizeof(ReferenceOracleCycleRecord) ||
      trace.header.oracle_block_bytes !=
          static_cast<std::uint64_t>(ORACLE_BLOCK_BYTES))
    throw std::runtime_error("trace and generated ABI disagree on width");
  if (trace.header.cycles == 0 || trace.header.cycles % (2 * kW) != 0 ||
      trace.header.reset_cycles >= trace.header.cycles ||
      trace.header.reset_cycles % kW != 0)
    throw std::runtime_error("trace does not contain complete SIMD halves");
  if (trace.header.cycles > static_cast<std::uint64_t>(ORACLE_NUM_CYCLES))
    throw std::runtime_error("ORACLE_NUM_CYCLES does not cover this trace");

  trace.cycles.resize(static_cast<std::size_t>(trace.header.cycles));
  trace.blocks.resize(static_cast<std::size_t>(
      trace.header.oracle_blocks * trace.header.oracle_block_bytes));
  input.read(reinterpret_cast<char*>(trace.cycles.data()),
             static_cast<std::streamsize>(trace.cycles.size() *
                                          sizeof(trace.cycles[0])));
  input.read(trace.blocks.data(), static_cast<std::streamsize>(trace.blocks.size()));
  if (!input) throw std::runtime_error("truncated reference-oracle trace");
  char extra = 0;
  if (input.read(&extra, 1))
    throw std::runtime_error("reference-oracle trace has trailing data");
  if (trace.blocks.empty())
    throw std::runtime_error("reference-oracle trace has no active block");
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

void require_feedback(std::uint64_t cycle, const DmiFeedback& actual,
                      const DmiFeedback& expected) {
  if (actual == expected) return;
  char message[320];
  std::snprintf(
      message, sizeof(message),
      "DMI mismatch at cycle %" PRIu64
      ": ready=%u/%u valid=%u/%u resp=%u/%u data=%08x/%08x",
      cycle, static_cast<unsigned>(actual.req_ready),
      static_cast<unsigned>(expected.req_ready),
      static_cast<unsigned>(actual.resp_valid),
      static_cast<unsigned>(expected.resp_valid), actual.resp, expected.resp,
      actual.data, expected.data);
  throw std::runtime_error(message);
}

}  // namespace

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);
    const Trace trace = read_trace(options.trace_path);
    auto dut = std::make_unique<TestHarness>();
    initialize_plusarg_readers<kW>(*dut, argc, argv);
    dut->oracle_win_base = trace.blocks.data();
    auto& ports = simdtm_ports(*dut);

    std::size_t expected_block = 0;
    std::chrono::duration<double> eval_elapsed{};
    for (std::uint64_t first = 0; first < trace.header.cycles; first += kW) {
      const bool forward = ((first / kW) % 2) == 0;
      const bool reset = trace.cycles[static_cast<std::size_t>(first)].reset != 0;
      for (unsigned step = 0; step < kW; ++step) {
        const auto& record =
            trace.cycles[static_cast<std::size_t>(first + step)];
        if ((record.reset != 0) != reset)
          throw std::runtime_error("reset changes inside a SIMD half-window");
        const int lane = forward ? static_cast<int>(step)
                                 : static_cast<int>(kW - 1 - step);
        drive_lane(ports, lane, trace_dtm_outputs(record));
      }

      assign_port(dut->reset, reset);
      const char* expected_pointer =
          trace.blocks.data() + expected_block * ORACLE_BLOCK_BYTES;
      if (!reset && dut->oracle_win_base != expected_pointer)
        throw std::runtime_error("generated oracle block pointer drift");
      const auto eval_begin = std::chrono::steady_clock::now();
      if (forward)
        dut->eval_forward(true, options.verbose, !reset);
      else
        dut->eval_reverse(true, options.verbose, !reset);
      const auto eval_end = std::chrono::steady_clock::now();
      if (options.eval_timing) eval_elapsed += eval_end - eval_begin;

      for (unsigned step = 0; step < kW; ++step) {
        const std::uint64_t cycle = first + step;
        const auto& record = trace.cycles[static_cast<std::size_t>(cycle)];
        const int lane = forward ? static_cast<int>(step)
                                 : static_cast<int>(kW - 1 - step);
        require_feedback(cycle, feedback_lane(ports, lane),
                         trace_dmi_feedback(record));
        const bool success = port_value(dut->io_success[lane]) != 0;
        if (success != (record.io_success != 0))
          throw std::runtime_error("io_success mismatch at cycle " +
                                   std::to_string(cycle));
      }
      if (!reset && !forward) ++expected_block;
    }

    if (expected_block != trace.header.oracle_blocks ||
        dut->verify_mismatches != 0 || dut->assert_triggered)
      throw std::runtime_error("oracle verification did not finish cleanly");
    std::printf(
        "W%u_REFERENCE_ORACLE_DIFF_OK cycles=%" PRIu64 " reset=%" PRIu64
        " streams=%" PRIu64 " blocks=%" PRIu64 " mismatches=%" PRIu64
        "\n",
        kW, trace.header.cycles, trace.header.reset_cycles,
        trace.header.oracle_streams, trace.header.oracle_blocks,
        dut->verify_mismatches);
    if (options.eval_timing) {
      const double seconds = eval_elapsed.count();
      std::printf(
          "W%u_REFERENCE_ORACLE_EVAL cycles=%" PRIu64
          " eval_calls=%" PRIu64 " eval_seconds=%.9f "
          "cycles_per_second=%.3f ns_per_cycle=%.3f\n",
          kW, trace.header.cycles, trace.header.cycles / kW, seconds,
          static_cast<double>(trace.header.cycles) / seconds,
          seconds * 1.0e9 / static_cast<double>(trace.header.cycles));
    }
    return 0;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "wide reference-oracle differential error: %s\n",
                 error.what());
    return 2;
  }
}
