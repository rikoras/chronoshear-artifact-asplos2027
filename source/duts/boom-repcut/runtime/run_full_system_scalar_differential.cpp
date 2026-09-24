#include <fesvr/dtm.h>

#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"

#include <cerrno>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "scalar_reference_runtime.h"

namespace {

using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::HalfDirection;
using chisa::boom_repcut::TapPhase;

struct Options {
  uint64_t max_cycles = 32;
  uint64_t reset_cycles = 12;
  bool verbose = false;
  bool allow_timeout = false;
  int htif_start = -1;
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(
      stderr,
      "usage: %s [runner options] [+RTL_PLUSARG...] -- "
      "[HTIF_OPTIONS...] BINARY [TARGET_ARGS...]\n"
      "  --max-cycles=N    chronological cycles to compare (default 32)\n"
      "  --reset-cycles=N  asserted reset cycles (default 12)\n"
      "  --verbose         enable generated RTL printfs\n"
      "  --allow-timeout   reaching max-cycles is a successful gate\n",
      program);
  std::exit(error ? 2 : 0);
}

uint64_t parse_u64(const char* program, const std::string& option,
                   const char* text) {
  if (!text || !*text) usage(program, (option + " requires a value").c_str());
  errno = 0;
  char* end = nullptr;
  const unsigned long long value = std::strtoull(text, &end, 0);
  if (errno != 0 || !end || *end != '\0')
    usage(program, ("invalid " + option + " value").c_str());
  return static_cast<uint64_t>(value);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg == "--") {
      options.htif_start = i + 1;
      break;
    }
    if (arg == "--help") usage(argv[0]);
    if (arg == "--verbose") {
      options.verbose = true;
      continue;
    }
    if (arg == "--allow-timeout") {
      options.allow_timeout = true;
      continue;
    }
    constexpr const char* max_prefix = "--max-cycles=";
    constexpr const char* reset_prefix = "--reset-cycles=";
    if (arg.rfind(max_prefix, 0) == 0) {
      options.max_cycles =
          parse_u64(argv[0], "--max-cycles", argv[i] + std::strlen(max_prefix));
      continue;
    }
    if (arg.rfind(reset_prefix, 0) == 0) {
      options.reset_cycles = parse_u64(
          argv[0], "--reset-cycles", argv[i] + std::strlen(reset_prefix));
      continue;
    }
    if (!arg.empty() && arg[0] == '+') continue;
    usage(argv[0],
          "runner options/RTL plusargs must be separated from HTIF by `--`");
  }
  if (options.htif_start < 0 || options.htif_start >= argc)
    usage(argv[0], "missing `-- BINARY`");
  if (options.max_cycles == 0) usage(argv[0], "--max-cycles must be positive");
  return options;
}

uint64_t width_mask(unsigned width) {
  return width == 64 ? std::numeric_limits<uint64_t>::max()
                     : (uint64_t{1} << width) - 1;
}

struct ExpectedTap {
  TapPhase phase;
  const char* trace_key;
  unsigned width;
  uint64_t value;
};

class ExactTapDifferentialObserver {
 public:
  ExactTapDifferentialObserver() {
    expected_.reserve(chisa::boom_repcut::kExactRegisterTapCount +
                      chisa::boom_repcut::kExactCombinationalTapCount);
  }

  bool capture_cycle(uint64_t cycle) const {
    // Value-initialized CHISA state and Verilator's zero rand-reset agree for
    // ordinary registers, but asserting an asynchronous reset makes the RTL
    // reset image observable before the first clock edge.  CHISA deliberately
    // applies every FIRRTL register update at a chronological edge, so its
    // pre-edge cycle-0 image is not a comparable RTL state.  Start exact tap
    // comparison after the first asserted-reset edge; the cycle-1 pre-state
    // then checks every reset result, including non-zero async-reset values.
    return cycle != 0;
  }

  void prepare_cycle(VTestHarness___024root& root, uint64_t cycle,
                     HalfDirection direction) {
    begin_prepare(cycle, direction);
    {  // VDBG=lo-hi: Verilator LSU forwarding wires (post-eval of this cycle)
      static long vdbg_lo = -1, vdbg_hi = -1; static bool vdbg_init = false;
      if (!vdbg_init) { vdbg_init = true; if (const char* w = std::getenv("VDBG")) { long a, b; if (std::sscanf(w, "%ld-%ld", &a, &b) == 2) { vdbg_lo = a; vdbg_hi = b; } } }
      if (vdbg_lo >= 0 && (long)cycle >= vdbg_lo && (long)cycle <= vdbg_hi)
        std::fprintf(stderr, "[VLSU] c=%llu dir=%d canf=%llx mem_unc=%llx exe_unc=%llx wbfv=%llx lcam=%llx mfv=%llx reg3=%llx reg7=%llx reg9=%llx fidx=%llx tlb_c=%llx pma_c=%llx pa=%llx am1=%llx ldq6uc=%llx\n", (unsigned long long)cycle, (int)direction,
                     (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__can_forward_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__mem_tlb_uncacheable_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__exe_tlb_uncacheable_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__wb_forward_valid_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__lcam_ldq_idx_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__mem_forward_valid_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__REG_3, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__REG_7, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__REG_9, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__forwarding_idx_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__io_resp_0_cacheable, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__cacheable_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__dtlb__DOT__mpu_physaddr_0, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldst_addr_matches_0_1, (unsigned long long)root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__boom_tile__DOT__lsu__DOT__ldq_6_bits_addr_is_uncacheable);
    }
    if (!capture_cycle(cycle)) return;
#define VERILATOR_TAP(expr, trace_key, bit_width)                            \
  expected_.push_back(ExpectedTap{TapPhase::pre_eval_register, (trace_key),  \
                                  (bit_width),                               \
                                  static_cast<uint64_t>(expr)})
#include "verilator_reg_tap_fields.inc"
#undef VERILATOR_TAP
#define VERILATOR_TAP(expr, trace_key, bit_width)                            \
  expected_.push_back(ExpectedTap{TapPhase::post_eval_combinational,         \
                                  (trace_key), (bit_width),                  \
                                  static_cast<uint64_t>(expr)})
#include "verilator_comb_tap_fields.inc"
#undef VERILATOR_TAP
  }

  void prepare_terminal_registers(VTestHarness___024root& root, uint64_t cycle,
                                  HalfDirection direction) {
    begin_prepare(cycle, direction);
#define VERILATOR_TAP(expr, trace_key, bit_width)                            \
  expected_.push_back(ExpectedTap{TapPhase::pre_eval_register, (trace_key),  \
                                  (bit_width),                               \
                                  static_cast<uint64_t>(expr)})
#include "verilator_reg_tap_fields.inc"
#undef VERILATOR_TAP
  }

  void observe(uint64_t cycle, HalfDirection direction, TapPhase phase,
               const char* trace_key, uint64_t chisa_value) {
    if (cycle != cycle_ || direction != direction_)
      throw std::runtime_error("tap observer cycle/direction ordering drift");
    if (cursor_ >= expected_.size())
      throw std::runtime_error("CHISA emitted more taps than Verilator binding");
    const ExpectedTap& expected = expected_[cursor_++];
    if (phase != expected.phase || std::strcmp(trace_key, expected.trace_key) != 0) {
      std::fprintf(
          stderr,
          "TAP ORDER MISMATCH cycle=%" PRIu64 " direction=%s index=%zu "
          "chisa=%s/%s verilator=%s/%s\n",
          cycle, chisa::boom_repcut::direction_name(direction), cursor_ - 1,
          chisa::boom_repcut::phase_name(phase), trace_key,
          chisa::boom_repcut::phase_name(expected.phase), expected.trace_key);
      throw std::runtime_error("manifest tap order mismatch");
    }
    const uint64_t mask = width_mask(expected.width);
    const uint64_t actual = chisa_value & mask;
    const uint64_t reference = expected.value & mask;
    if (actual != reference) {
      std::fprintf(
          stderr,
          "FULL SYSTEM TAP MISMATCH cycle=%" PRIu64
          " direction=%s phase=%s index=%zu key=%s width=%u "
          "chisa=0x%016" PRIx64 " verilator=0x%016" PRIx64 "\n",
          cycle, chisa::boom_repcut::direction_name(direction),
          chisa::boom_repcut::phase_name(phase), cursor_ - 1, trace_key,
          expected.width, actual, reference);
      throw std::runtime_error("full-system tap mismatch");
    }
    mix(reference);
    ++compared_;
  }

  void finish_cycle() const {
    if (cursor_ != expected_.size())
      throw std::runtime_error("CHISA emitted fewer taps than Verilator binding");
  }

  uint64_t compared() const { return compared_; }
  uint64_t digest() const { return digest_; }

 private:
  void begin_prepare(uint64_t cycle, HalfDirection direction) {
    expected_.clear();
    cursor_ = 0;
    cycle_ = cycle;
    direction_ = direction;
  }

  void mix(uint64_t value) {
    for (unsigned byte = 0; byte < 8; ++byte) {
      digest_ ^= static_cast<uint8_t>(value >> (byte * 8));
      digest_ *= UINT64_C(1099511628211);
    }
  }

  std::vector<ExpectedTap> expected_;
  std::size_t cursor_ = 0;
  uint64_t cycle_ = 0;
  HalfDirection direction_ = HalfDirection::forward;
  uint64_t compared_ = 0;
  uint64_t digest_ = UINT64_C(1469598103934665603);
};

void drive_verilator_simdtm(VTestHarness___024root& root,
                            const DtmOutputs& outputs) {
  // Drive the five source registers that the real SimDTM would update at its
  // posedge.  The DPI stub below remains isolated: these registers are
  // overwritten before every DUT edge, so no second dtm_t can influence RTL.
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg = outputs.req_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg = outputs.req_addr;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg = outputs.req_op;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg = outputs.req_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg = outputs.resp_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = outputs.exit;
}

DmiFeedback verilator_dmi_feedback(const VTestHarness___024root& root) {
  return DmiFeedback{
      root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
      root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
      static_cast<uint32_t>(root.TestHarness__DOT__SimDTM_debug_resp_bits_resp),
      static_cast<uint32_t>(root.TestHarness__DOT__SimDTM_debug_resp_bits_data)};
}

void require_same_feedback(uint64_t cycle, const DmiFeedback& chisa,
                           const DmiFeedback& verilator) {
  if (chisa == verilator) return;
  std::fprintf(
      stderr,
      "DMI FEEDBACK MISMATCH cycle=%" PRIu64
      " chisa={ready=%u valid=%u resp=%u data=%08x} "
      "verilator={ready=%u valid=%u resp=%u data=%08x}\n",
      cycle, static_cast<unsigned>(chisa.req_ready),
      static_cast<unsigned>(chisa.resp_valid), chisa.resp, chisa.data,
      static_cast<unsigned>(verilator.req_ready),
      static_cast<unsigned>(verilator.resp_valid), verilator.resp,
      verilator.data);
  throw std::runtime_error("full-system DMI feedback mismatch");
}

} // namespace

// The locked Verilator model still contains the artifact SimDTM DPI call.
// Keep it inert and drive the public SimDTM output registers from the one
// exact dtm_t owned by the CHISA reference stepper.
extern "C" int debug_tick(svBit* debug_req_valid, svBit debug_req_ready,
                          int* debug_req_bits_addr, int* debug_req_bits_op,
                          int* debug_req_bits_data, svBit debug_resp_valid,
                          svBit* debug_resp_ready, int debug_resp_bits_resp,
                          int debug_resp_bits_data) {
  (void)debug_req_ready;
  (void)debug_req_bits_addr;
  (void)debug_req_bits_op;
  (void)debug_req_bits_data;
  (void)debug_resp_valid;
  (void)debug_resp_bits_resp;
  (void)debug_resp_bits_data;
  *debug_req_valid = 0;
  *debug_resp_ready = 0;
  return 0;
}

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);

    std::vector<char*> htif_argv;
    htif_argv.reserve(static_cast<std::size_t>(argc - options.htif_start + 1));
    htif_argv.push_back(argv[0]);
    for (int i = options.htif_start; i < argc; ++i)
      htif_argv.push_back(argv[i]);

    auto scalar = std::make_unique<TestHarness>();
    auto dtm = std::make_unique<dtm_t>(
        static_cast<int>(htif_argv.size()), htif_argv.data());
    ExactTapDifferentialObserver observer;
    chisa::boom_repcut::W1ReferenceStepper<
        dtm_t, ExactTapDifferentialObserver>
        stepper(*scalar, *dtm, observer, argc, argv);

    auto context = std::make_unique<VerilatedContext>();
    context->randReset(0);
    context->commandArgs(argc, argv);
    auto verilator = std::make_unique<VTestHarness>(context.get());
    verilator->clock = 0;
    verilator->reset = 1;
    verilator->eval();

    bool success = false;
    uint64_t dmi_request_handshakes = 0;
    uint64_t dmi_response_handshakes = 0;
    while (stepper.cycle() < options.max_cycles) {
      const uint64_t cycle = stepper.cycle();
      const bool reset = cycle < options.reset_cycles;
      const DtmOutputs driven_dtm = stepper.dtm_adapter().outputs();

      verilator->reset = reset;
      drive_verilator_simdtm(*verilator->rootp, driven_dtm);
      verilator->clock = 0;
      verilator->eval();
      context->timeInc(1);

      observer.prepare_cycle(*verilator->rootp, cycle,
                             stepper.expected_direction());
      const DmiFeedback verilator_feedback =
          verilator_dmi_feedback(*verilator->rootp);
      const bool verilator_success = verilator->io_success != 0;

      const auto result = stepper.step(stepper.expected_direction(), reset,
                                       options.verbose);
      observer.finish_cycle();
      require_same_feedback(cycle, result.dmi_feedback, verilator_feedback);
      if (result.io_success != verilator_success)
        throw std::runtime_error("full-system io_success mismatch");

      if (driven_dtm.req_valid && result.dmi_feedback.req_ready)
        ++dmi_request_handshakes;
      if (driven_dtm.resp_ready && result.dmi_feedback.resp_valid)
        ++dmi_response_handshakes;

      // The low phase above represents the cycle's stable combinational
      // behavior.  Commit the same edge only after CHISA has evaluated and
      // all pre-state/combinational observations have been checked.
      verilator->clock = 1;
      verilator->eval();
      context->timeInc(1);

      if (!reset && (dtm->done() || result.io_success)) {
        success = true;
        break;
      }
    }

    // A next-state bug in the last requested cycle would otherwise have no
    // following pre-eval observation.  Compare the terminal register image
    // once more without advancing either design.
    const uint64_t terminal_cycle = stepper.cycle();
    const bool terminal_reset = terminal_cycle < options.reset_cycles;
    verilator->reset = terminal_reset;
    drive_verilator_simdtm(*verilator->rootp,
                           stepper.dtm_adapter().outputs());
    verilator->clock = 0;
    verilator->eval();
    observer.prepare_terminal_registers(
        *verilator->rootp, terminal_cycle, stepper.expected_direction());
    chisa::boom_repcut::sample_exact_register_tap(
        *scalar, observer, terminal_cycle, stepper.expected_direction());
    observer.finish_cycle();

    const bool timed_out = !success && stepper.cycle() == options.max_cycles;
    const int exit_code = dtm->exit_code();
    const char* status = success ? (exit_code == 0 ? "pass" : "fail")
                                 : (timed_out ? "max-cycles" : "stopped");
    std::printf(
        "FULL_SYSTEM_SCALAR_DIFF status=%s cycles=%" PRIu64
        " reset_cycles=%" PRIu64 " reg_taps=%zu comb_taps=%zu "
        "comparisons=%" PRIu64 " digest=%016" PRIx64
        " dmi_requests=%" PRIu64 " dmi_responses=%" PRIu64
        " dtm_exit=%d\n",
        status, stepper.cycle(), options.reset_cycles,
        chisa::boom_repcut::kExactRegisterTapCount,
        chisa::boom_repcut::kExactCombinationalTapCount,
        observer.compared(), observer.digest(), dmi_request_handshakes,
        dmi_response_handshakes, exit_code);

    if (success) return exit_code;
    return timed_out && options.allow_timeout ? 0 : 2;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "full-system scalar differential error: %s\n",
                 error.what());
    return 2;
  }
}
