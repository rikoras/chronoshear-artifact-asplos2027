#include <fesvr/dtm.h>

#include <algorithm>
#include <cerrno>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "scalar_reference_runtime.h"

namespace {

using chisa::boom_repcut::HalfDirection;
using chisa::boom_repcut::TapPhase;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::FesvrDtmAdapter;

bool same_dtm_outputs(const DtmOutputs& lhs, const DtmOutputs& rhs) {
  return lhs.req_valid == rhs.req_valid && lhs.req_addr == rhs.req_addr &&
         lhs.req_op == rhs.req_op && lhs.req_data == rhs.req_data &&
         lhs.resp_ready == rhs.resp_ready && lhs.exit == rhs.exit;
}

struct Options {
  uint64_t max_cycles = 32;
  uint64_t reset_cycles = 12;
  uint64_t tap_cycles = 32;
  bool verbose = false;
  bool allow_timeout = false;
  int htif_start = -1;
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(stderr,
      "usage: %s [runner options] [+RTL_PLUSARG...] -- "
      "[HTIF_OPTIONS...] BINARY [TARGET_ARGS...]\n"
      "  --max-cycles=N    chronological W=1 cycles (default 32)\n"
      "  --reset-cycles=N  asserted reset cycles (default 12)\n"
      "  --tap-cycles=N    initial cycles included in tap digest (default 32)\n"
      "  --verbose         enable generated RTL printfs\n"
      "  --allow-timeout   reaching max-cycles is a successful smoke run\n"
      "\n"
      "RTL plusargs must precede `--`; exact FESVR/target arguments follow it.\n",
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
    constexpr const char* tap_prefix = "--tap-cycles=";
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
    if (arg.rfind(tap_prefix, 0) == 0) {
      options.tap_cycles =
          parse_u64(argv[0], "--tap-cycles", argv[i] + std::strlen(tap_prefix));
      continue;
    }
    if (!arg.empty() && arg[0] == '+') continue;
    usage(argv[0], "runner options/RTL plusargs must be separated from HTIF by `--`");
  }
  if (options.htif_start < 0 || options.htif_start >= argc)
    usage(argv[0], "missing `-- BINARY`");
  if (options.max_cycles == 0) usage(argv[0], "--max-cycles must be positive");
  return options;
}

class DigestObserver {
 public:
  explicit DigestObserver(uint64_t tap_cycles) : tap_cycles_(tap_cycles) {
    if (const char* prefix = std::getenv("CHISA_TAP_TRACE"))
      trace_prefix_ = prefix;
    trace_changes_only_ = std::getenv("CHISA_TAP_TRACE_CHANGES") != nullptr;
    if (const char* profile = std::getenv("CHISA_TAP_PROFILE")) {
      profile_enabled_ = true;
      if (std::strcmp(profile, "1") != 0 && std::strcmp(profile, "all") != 0)
        profile_prefix_ = profile;
    }
    if (const char* limit = std::getenv("CHISA_TAP_PROFILE_MAX")) {
      char* end = nullptr;
      const unsigned long long parsed = std::strtoull(limit, &end, 10);
      if (end && *end == '\0') profile_max_ = parsed;
    }
  }

  bool capture_cycle(uint64_t cycle) const { return cycle < tap_cycles_; }

  void observe(uint64_t cycle, HalfDirection direction, TapPhase phase,
               const char* trace_key, uint64_t value) {
    mix(cycle);
    mix(static_cast<uint8_t>(direction));
    mix(static_cast<uint8_t>(phase));
    for (const unsigned char* p =
             reinterpret_cast<const unsigned char*>(trace_key);
         *p; ++p)
      mix(*p);
    mix(value);
    if (phase == TapPhase::pre_eval_register)
      ++pre_samples_;
    else
      ++post_samples_;

    if (profile_enabled_ &&
        (profile_prefix_.empty() ||
         std::strncmp(trace_key, profile_prefix_.c_str(),
                      profile_prefix_.size()) == 0)) {
      const std::string identity =
          std::string(chisa::boom_repcut::phase_name(phase)) + ":" + trace_key;
      TapProfile& profile = profiles_[identity];
      if (profile.samples == 0) {
        profile.first = value;
        profile.last = value;
        profile.or_reduce = value;
        profile.and_reduce = value;
      } else {
        if (profile.last != value) ++profile.changes;
        profile.last = value;
        profile.or_reduce |= value;
        profile.and_reduce &= value;
      }
      ++profile.samples;
    }

    if (!trace_prefix_.empty() &&
        std::strncmp(trace_key, trace_prefix_.c_str(), trace_prefix_.size()) ==
            0) {
      const std::string identity =
          std::string(chisa::boom_repcut::phase_name(phase)) + ":" + trace_key;
      const auto previous = traced_values_.find(identity);
      if (!trace_changes_only_ || previous == traced_values_.end() ||
          previous->second != value) {
        std::fprintf(stderr,
                     "[TAP c%" PRIu64 " %s %s] %s=0x%" PRIx64 "\n",
                     cycle, chisa::boom_repcut::direction_name(direction),
                     chisa::boom_repcut::phase_name(phase), trace_key, value);
      }
      traced_values_[identity] = value;
    }
  }

  uint64_t digest() const { return digest_; }
  uint64_t pre_samples() const { return pre_samples_; }
  uint64_t post_samples() const { return post_samples_; }

  /** Read-only bring-up aid.  A stable tap is only a candidate for source
    * inspection; this report never turns it into a model binding.  That
    * distinction prevents one quiet workload from being mistaken for a
    * design invariant. */
  void print_profile() const {
    if (!profile_enabled_) return;
    std::vector<std::pair<std::string, TapProfile>> ordered(
        profiles_.begin(), profiles_.end());
    std::sort(ordered.begin(), ordered.end(),
              [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
    std::size_t stable = 0;
    for (const auto& entry : ordered)
      stable += static_cast<std::size_t>(entry.second.changes == 0);
    std::fprintf(stderr,
                 "\n=== [TAP PROFILE] prefix='%s' streams=%zu stable=%zu dynamic=%zu ===\n",
                 profile_prefix_.c_str(), ordered.size(), stable,
                 ordered.size() - stable);
    std::size_t shown = 0;
    for (const auto& [identity, profile] : ordered) {
      if (shown >= profile_max_) break;
      ++shown;
      std::fprintf(stderr,
                   "[TAP PROFILE %s] %s samples=%" PRIu64
                   " changes=%" PRIu64 " first=0x%" PRIx64
                   " last=0x%" PRIx64 " or=0x%" PRIx64
                   " and=0x%" PRIx64 "\n",
                   profile.changes == 0 ? "stable" : "dynamic",
                   identity.c_str(), profile.samples, profile.changes,
                   profile.first, profile.last, profile.or_reduce,
                   profile.and_reduce);
    }
    if (shown < ordered.size())
      std::fprintf(stderr, "[TAP PROFILE] ... %zu stream(s) omitted\n",
                   ordered.size() - shown);
  }

 private:
  struct TapProfile {
    uint64_t samples = 0;
    uint64_t changes = 0;
    uint64_t first = 0;
    uint64_t last = 0;
    uint64_t or_reduce = 0;
    uint64_t and_reduce = 0;
  };

  void mix(uint64_t value) {
    // Deterministic FNV-1a over eight bytes; intended as a smoke/differential
    // fingerprint, not as a cryptographic commitment.
    for (unsigned byte = 0; byte < 8; ++byte) {
      digest_ ^= static_cast<uint8_t>(value >> (byte * 8));
      digest_ *= UINT64_C(1099511628211);
    }
  }

  uint64_t tap_cycles_ = 0;
  uint64_t digest_ = UINT64_C(1469598103934665603);
  uint64_t pre_samples_ = 0;
  uint64_t post_samples_ = 0;
  std::string trace_prefix_;
  bool trace_changes_only_ = false;
  std::unordered_map<std::string, uint64_t> traced_values_;
  bool profile_enabled_ = false;
  std::string profile_prefix_;
  std::size_t profile_max_ = 100;
  std::unordered_map<std::string, TapProfile> profiles_;
};

} // namespace

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);

    std::vector<char*> htif_argv;
    htif_argv.reserve(static_cast<std::size_t>(argc - options.htif_start + 1));
    htif_argv.push_back(argv[0]);
    for (int i = options.htif_start; i < argc; ++i)
      htif_argv.push_back(argv[i]);

    auto dut = std::make_unique<TestHarness>();
    auto dtm = std::make_unique<dtm_t>(
        static_cast<int>(htif_argv.size()), htif_argv.data());
    // Diagnostic only: prove that two independent FESVR sessions initialized
    // from the same one-time workload/configuration produce identical host
    // requests when presented with the same feedback history.  The future
    // model instance will receive model-predicted feedback instead; this mode
    // deliberately uses captured RTL feedback only to validate that owning a
    // second dtm_t is deterministic and does not corrupt either session.
    const bool dual_dtm_audit =
        std::getenv("CHISA_DUAL_DTM_AUDIT") != nullptr;
    std::unique_ptr<dtm_t> audit_dtm;
    std::unique_ptr<FesvrDtmAdapter<dtm_t>> audit_adapter;
    if (dual_dtm_audit) {
      audit_dtm = std::make_unique<dtm_t>(
          static_cast<int>(htif_argv.size()), htif_argv.data());
      audit_adapter = std::make_unique<FesvrDtmAdapter<dtm_t>>(*audit_dtm);
    }
    DigestObserver observer(options.tap_cycles);
    chisa::boom_repcut::W1ReferenceStepper<dtm_t, DigestObserver> stepper(
        *dut, *dtm, observer, argc, argv);

    bool success = false;
    uint64_t dmi_request_handshakes = 0;
    uint64_t dmi_response_handshakes = 0;
    const bool trace_dmi = std::getenv("CHISA_DMI_TRACE") != nullptr;
    while (stepper.cycle() < options.max_cycles) {
      const uint64_t cycle = stepper.cycle();
      const bool reset = cycle < options.reset_cycles;
      const auto driven_dtm = stepper.dtm_adapter().outputs();
      if (audit_adapter &&
          !same_dtm_outputs(driven_dtm, audit_adapter->outputs())) {
        throw std::runtime_error("independent dtm_t output divergence at cycle " +
                                 std::to_string(cycle));
      }
      const auto result = stepper.step(
          stepper.expected_direction(), reset, options.verbose);
      if (audit_adapter) audit_adapter->advance(reset, result.dmi_feedback);
      if (trace_dmi) {
        std::fprintf(
            stderr,
            "[DMI c%" PRIu64 "] drive(v=%u a=0x%x op=%u data=0x%08x "
            "rr=%u exit=%u) feedback(ready=%u valid=%u resp=%u "
            "data=0x%08x)\n",
            cycle, static_cast<unsigned>(driven_dtm.req_valid),
            driven_dtm.req_addr, driven_dtm.req_op, driven_dtm.req_data,
            static_cast<unsigned>(driven_dtm.resp_ready), driven_dtm.exit,
            static_cast<unsigned>(result.dmi_feedback.req_ready),
            static_cast<unsigned>(result.dmi_feedback.resp_valid),
            result.dmi_feedback.resp, result.dmi_feedback.data);
      }
      if (driven_dtm.req_valid && result.dmi_feedback.req_ready)
        ++dmi_request_handshakes;
      if (driven_dtm.resp_ready && result.dmi_feedback.resp_valid)
        ++dmi_response_handshakes;
      if (!reset && (dtm->done() || result.io_success)) {
        success = true;
        break;
      }
    }

    const bool timed_out = !success && stepper.cycle() == options.max_cycles;
    const int exit_code = dtm->exit_code();
    if (audit_dtm && (audit_dtm->done() != dtm->done() ||
                      audit_dtm->exit_code() != exit_code))
      throw std::runtime_error("independent dtm_t completion state diverged");
    const char* status = success ? (exit_code == 0 ? "pass" : "fail")
                                 : (timed_out ? "max-cycles" : "stopped");
    observer.print_profile();
    std::printf(
        "SCALAR_REFERENCE status=%s cycles=%" PRIu64
        " reset_cycles=%" PRIu64 " tap_cycles=%" PRIu64
        " pre_taps=%zu post_taps=%zu pre_samples=%" PRIu64
        " post_samples=%" PRIu64 " tap_digest=%016" PRIx64
        " dmi_requests=%" PRIu64 " dmi_responses=%" PRIu64
        " dtm_exit=%d\n",
        status, stepper.cycle(), options.reset_cycles, options.tap_cycles,
        chisa::boom_repcut::kExactRegisterTapCount,
        chisa::boom_repcut::kExactCombinationalTapCount,
        observer.pre_samples(), observer.post_samples(), observer.digest(),
        dmi_request_handshakes, dmi_response_handshakes, exit_code);
    if (audit_adapter)
      std::printf("DUAL_DTM_AUDIT_OK cycles=%" PRIu64 "\n", stepper.cycle());

    if (success) return exit_code;
    return timed_out && options.allow_timeout ? 0 : 2;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "scalar reference error: %s\n", error.what());
    return 2;
  }
}
