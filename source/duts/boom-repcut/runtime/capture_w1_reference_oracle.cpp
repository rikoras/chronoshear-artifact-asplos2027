#include <fesvr/dtm.h>

#include <cerrno>
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

#include "reference_oracle_layout.inc"
#include "reference_oracle_trace.h"
#include "scalar_reference_runtime.h"

namespace {

using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::HalfDirection;
using chisa::boom_repcut::ReferenceOracleCycleRecord;
using chisa::boom_repcut::ReferenceOracleSpec;
using chisa::boom_repcut::ReferenceOracleTraceHeader;
using chisa::boom_repcut::TapPhase;
using chisa::boom_repcut::kReferenceCombinationalOracleSpecs;
using chisa::boom_repcut::kReferenceOracleBlockBytes;

// Window width of the produced trace layout. The manifest baked into
// reference_oracle_layout.inc must come from an emit at this same width:
// block offsets and blockBytes are width-specific. W=4 remains the formal
// default; wider gates compile the same tool with -DCAPTURE_W=<W>.
#ifndef CAPTURE_W
#define CAPTURE_W 4
#endif
constexpr unsigned kCaptureW = CAPTURE_W;
static_assert(kCaptureW >= 1 && (kCaptureW & (kCaptureW - 1)) == 0,
              "CAPTURE_W must be a power of two");

using chisa::boom_repcut::kReferenceOracleStreamCount;
using chisa::boom_repcut::kReferenceRegisterOracleSpecs;
using chisa::boom_repcut::make_reference_oracle_cycle;

struct Options {
  std::uint64_t max_cycles = 32;
  std::uint64_t reset_cycles = 12;
  std::string trace_path;
  bool verbose = false;
  int htif_start = -1;
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(
      stderr,
      "usage: %s --trace=FILE [--max-cycles=N] [--reset-cycles=N] "
      "[+RTL_PLUSARG...] -- BINARY [TARGET_ARGS...]\n",
      program);
  std::exit(error ? 2 : 0);
}

std::uint64_t parse_u64(const char* program, const char* option,
                        const char* text) {
  if (!text || !*text) usage(program, "missing numeric option value");
  errno = 0;
  char* end = nullptr;
  const unsigned long long value = std::strtoull(text, &end, 0);
  if (errno != 0 || !end || *end != '\0') usage(program, option);
  return static_cast<std::uint64_t>(value);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int index = 1; index < argc; ++index) {
    const std::string argument(argv[index]);
    if (argument == "--") {
      options.htif_start = index + 1;
      break;
    }
    if (argument == "--help") usage(argv[0]);
    if (argument == "--verbose") {
      options.verbose = true;
      continue;
    }
    constexpr const char* trace_prefix = "--trace=";
    constexpr const char* max_prefix = "--max-cycles=";
    constexpr const char* reset_prefix = "--reset-cycles=";
    if (argument.rfind(trace_prefix, 0) == 0) {
      options.trace_path = argument.substr(std::strlen(trace_prefix));
      continue;
    }
    if (argument.rfind(max_prefix, 0) == 0) {
      options.max_cycles = parse_u64(
          argv[0], "invalid --max-cycles", argv[index] + std::strlen(max_prefix));
      continue;
    }
    if (argument.rfind(reset_prefix, 0) == 0) {
      options.reset_cycles = parse_u64(
          argv[0], "invalid --reset-cycles",
          argv[index] + std::strlen(reset_prefix));
      continue;
    }
    if (!argument.empty() && argument[0] == '+') continue;
    usage(argv[0], "runner options and plusargs must precede `-- BINARY`");
  }
  if (options.trace_path.empty()) usage(argv[0], "missing --trace=FILE");
  if (options.htif_start < 0 || options.htif_start >= argc)
    usage(argv[0], "missing `-- BINARY`");
  if (options.max_cycles == 0 || options.max_cycles % (2 * CAPTURE_W) != 0)
    usage(argv[0], "--max-cycles must be a positive multiple of 2*CAPTURE_W");
  if (options.reset_cycles >= options.max_cycles ||
      options.reset_cycles % CAPTURE_W != 0)
    usage(argv[0], "--reset-cycles must be a smaller multiple of CAPTURE_W");
  return options;
}

class OracleBlockObserver {
 public:
  void begin_cycle(std::uint64_t cycle, bool reset) {
    cycle_ = cycle;
    active_ = !reset;
    register_cursor_ = 0;
    combinational_cursor_ = 0;
    const std::uint64_t half = cycle / kCaptureW;
    forward_ = (half % 2) == 0;
    step_ = static_cast<unsigned>(cycle % kCaptureW);
    if (!active_) return;
    const std::size_t required = (block_ + 1) * kReferenceOracleBlockBytes;
    if (blocks_.size() < required) blocks_.resize(required, 0);
    element_ = forward_ ? step_ : (2u * kCaptureW - 1u) - step_;
  }

  bool capture_cycle(std::uint64_t cycle) const {
    return active_ && cycle == cycle_;
  }

  void observe(std::uint64_t cycle, HalfDirection direction, TapPhase phase,
               const char* trace_key, std::uint64_t value) {
    (void)direction;
    if (!active_ || cycle != cycle_)
      throw std::runtime_error("oracle observer cycle ordering drift");
    if (phase == TapPhase::pre_eval_register) {
      if (register_cursor_ >= kReferenceRegisterOracleSpecs.size())
        throw std::runtime_error("too many register oracle samples");
      write(kReferenceRegisterOracleSpecs[register_cursor_++], trace_key, value);
    } else {
      if (combinational_cursor_ >=
          kReferenceCombinationalOracleSpecs.size())
        throw std::runtime_error("too many combinational oracle samples");
      write(kReferenceCombinationalOracleSpecs[combinational_cursor_++],
            trace_key, value);
    }
  }

  void end_cycle() {
    if (!active_) return;
    if (register_cursor_ != kReferenceRegisterOracleSpecs.size() ||
        combinational_cursor_ != kReferenceCombinationalOracleSpecs.size())
      throw std::runtime_error("incomplete manifest tap capture");
    if (!forward_ && step_ == kCaptureW - 1) ++block_;
  }

  const std::vector<char>& blocks() const { return blocks_; }

 private:
  void write(const ReferenceOracleSpec& spec, const char* trace_key,
             std::uint64_t value) {
    if (std::strcmp(spec.trace_key, trace_key) != 0) {
      throw std::runtime_error(
          std::string("manifest/tap order mismatch: expected ") +
          spec.trace_key + ", got " + trace_key);
    }
    if (spec.width < 64) value &= (std::uint64_t{1} << spec.width) - 1;
    char* destination = blocks_.data() + block_ * kReferenceOracleBlockBytes +
                        spec.block_offset + element_ * spec.elem_bytes;
    for (unsigned byte = 0; byte < spec.elem_bytes; ++byte)
      destination[byte] = static_cast<char>(value >> (8u * byte));
  }

  std::vector<char> blocks_;
  std::size_t block_ = 0;
  std::uint64_t cycle_ = 0;
  std::size_t register_cursor_ = 0;
  std::size_t combinational_cursor_ = 0;
  unsigned step_ = 0;
  unsigned element_ = 0;
  bool active_ = false;
  bool forward_ = true;
};

void write_trace(const Options& options,
                 const std::vector<ReferenceOracleCycleRecord>& cycles,
                 const std::vector<char>& blocks) {
  ReferenceOracleTraceHeader header;
  header.cycle_record_bytes = sizeof(ReferenceOracleCycleRecord);
  header.cycles = cycles.size();
  header.reset_cycles = options.reset_cycles;
  header.width = kCaptureW;
  header.oracle_blocks = blocks.size() / kReferenceOracleBlockBytes;
  header.oracle_block_bytes = kReferenceOracleBlockBytes;
  header.oracle_streams = kReferenceOracleStreamCount;

  std::ofstream output(options.trace_path, std::ios::binary | std::ios::trunc);
  if (!output) throw std::runtime_error("cannot create trace: " + options.trace_path);
  output.write(reinterpret_cast<const char*>(&header), sizeof(header));
  output.write(reinterpret_cast<const char*>(cycles.data()),
               static_cast<std::streamsize>(cycles.size() * sizeof(cycles[0])));
  output.write(blocks.data(), static_cast<std::streamsize>(blocks.size()));
  if (!output) throw std::runtime_error("failed writing trace: " + options.trace_path);
}

}  // namespace

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);
    std::vector<char*> htif_argv;
    htif_argv.reserve(static_cast<std::size_t>(argc - options.htif_start + 1));
    htif_argv.push_back(argv[0]);
    for (int index = options.htif_start; index < argc; ++index)
      htif_argv.push_back(argv[index]);

    auto dut = std::make_unique<TestHarness>();
    auto dtm = std::make_unique<dtm_t>(
        static_cast<int>(htif_argv.size()), htif_argv.data());
    OracleBlockObserver observer;
    chisa::boom_repcut::W1ReferenceStepper<dtm_t, OracleBlockObserver> stepper(
        *dut, *dtm, observer, argc, argv);
    std::vector<ReferenceOracleCycleRecord> records;
    records.reserve(options.max_cycles);
    std::uint64_t dmi_requests = 0;
    std::uint64_t dmi_responses = 0;

    while (stepper.cycle() < options.max_cycles) {
      const std::uint64_t cycle = stepper.cycle();
      const bool reset = cycle < options.reset_cycles;
      const DtmOutputs outputs = stepper.dtm_adapter().outputs();
      observer.begin_cycle(cycle, reset);
      const auto result = stepper.step(
          stepper.expected_direction(), reset, options.verbose);
      observer.end_cycle();
      if (outputs.req_valid && result.dmi_feedback.req_ready) ++dmi_requests;
      if (outputs.resp_ready && result.dmi_feedback.resp_valid) ++dmi_responses;
      records.push_back(make_reference_oracle_cycle(
          outputs, result.dmi_feedback, result.io_success, reset));
    }

    write_trace(options, records, observer.blocks());
    std::printf(
        "W1_ORACLE_TRACE_OK cycles=%" PRIu64 " reset=%" PRIu64
        " streams=%zu blocks=%zu block_bytes=%zu dmi_requests=%" PRIu64
        " dmi_responses=%" PRIu64 " file=%s\n",
        options.max_cycles, options.reset_cycles,
        kReferenceOracleStreamCount,
        observer.blocks().size() / kReferenceOracleBlockBytes,
        kReferenceOracleBlockBytes, dmi_requests, dmi_responses,
        options.trace_path.c_str());
    return 0;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "W=1 oracle capture error: %s\n", error.what());
    return 2;
  }
}
