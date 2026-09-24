#include <fesvr/dtm.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <elf.h>

#include <array>
#include <cerrno>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "fesvr_debug_bootstrap.h"
#include "model_bindings.h"
#include "model_observer.h"
#include "scalar_reference_runtime.h"
#include "seam_contract.h"
#include "system_guider.h"
#include "system_probe.h"
#include "generated/system_probe_registry.inc"
#include "../../../reference_models/boom_model/small/env_knob.h"

namespace {

using chisa::boom_repcut::HalfDirection;
using chisa::boom_repcut::SeamRule;
using chisa::boom_repcut::SeamSignal;
using chisa::boom_repcut::TapPhase;
using chisa::boom_repcut::first_seam_mismatch;
using chisa::boom_repcut::seam_rule_name;
using chisa::boom_system::BoundaryConfig;
using chisa::boom_system::ModelObserver;
using chisa::boom_system::SystemGuider;
using chisa::boom_system::SystemProbes;
using chisa::boom_system::backend_completion_source_name;

// These are the same unconditional X-macro tap walks used by the stepper.
// Verify their finite key/phase set once; counting capture/end_cycle calls
// alone would also count disabled probes, filtered streams, and skipped cycles.
bool exact_probe_tap_contract() {
  using chisa::boom_system::OracleKind;
  std::map<std::string, OracleKind> taps;
  bool unique = true;
  const auto add = [&](const char* key, OracleKind kind) {
    if (!taps.emplace(key, kind).second) unique = false;
  };
#define REG_ORACLE(expr, name) add((name), OracleKind::Register)
#define REG_ORACLE_WORD(expr, i, name) add((name), OracleKind::Register)
#include "exact_reg_oracle_fields.inc"
#undef REG_ORACLE
#undef REG_ORACLE_WORD
#define PUSH_AS(expr, name) add((name), OracleKind::Combinational)
#include "exact_probe_fields_v2.inc"
#undef PUSH_AS
  if (!unique) return false;
  for (const auto& row : chisa::boom_system::kSystemProbeManifest) {
    const auto found = taps.find(row.key);
    if (found == taps.end() || found->second != row.kind) return false;
    taps.erase(found);  // also rejects duplicate registry keys
  }
  return taps.empty();
}

struct Options {
  uint64_t max_cycles = 32;
  uint64_t reset_cycles = 12;
  bool verbose = false;
  bool allow_timeout = false;
  bool allow_zero_model = false;
  bool quiesce_debug_at_entry = false;
  uint64_t roi_cycles = 0;
  int htif_start = -1;
  uint64_t checkpoint_at = 0;    // fork a checkpoint holder at this cycle (0 = off)
  std::string checkpoint_ctl;    // the holder's control fifo (default /tmp/lockstep-ckpt-<cycle>.fifo)
};

[[noreturn]] void usage(const char* program, const char* error = nullptr) {
  if (error) std::fprintf(stderr, "%s: %s\n", program, error);
  std::fprintf(
      stderr,
      "usage: %s [runner options] [+RTL_PLUSARG...] -- "
      "[HTIF_OPTIONS...] BINARY [TARGET_ARGS...]\n"
      "  --max-cycles=N       chronological cycles (default 32)\n"
      "  --reset-cycles=N     asserted reset cycles (default 12)\n"
      "  --verbose            enable generated RTL printfs\n"
      "  --allow-timeout      a workload timeout is not a runner failure\n"
      "  --quiesce-debug-at-entry\n"
      "                      stop fesvr and deactivate debug after loading\n"
      "  --roi-cycles=N       stop after N post-debug-quiescence cycles\n"
      "  --allow-zero-model   development-only: permit zero live bindings\n"
      "  --checkpoint-at=N    fork a holder process at cycle N; later runs\n"
      "                      resume from it through its control fifo\n"
      "                      (scripts/lockstep_ckpt.sh)\n"
      "  --checkpoint-ctl=P   the holder's control fifo path\n",
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
    if (argument == "--allow-timeout") {
      options.allow_timeout = true;
      continue;
    }
    if (argument == "--allow-zero-model") {
      options.allow_zero_model = true;
      continue;
    }
    if (argument == "--quiesce-debug-at-entry") {
      options.quiesce_debug_at_entry = true;
      continue;
    }
    constexpr const char* ckpt_prefix = "--checkpoint-at=";
    if (argument.rfind(ckpt_prefix, 0) == 0) {
      options.checkpoint_at = parse_u64(
          argv[0], "--checkpoint-at", argv[index] + std::strlen(ckpt_prefix));
      continue;
    }
    constexpr const char* ckpt_ctl_prefix = "--checkpoint-ctl=";
    if (argument.rfind(ckpt_ctl_prefix, 0) == 0) {
      options.checkpoint_ctl = argv[index] + std::strlen(ckpt_ctl_prefix);
      continue;
    }
    constexpr const char* max_prefix = "--max-cycles=";
    constexpr const char* reset_prefix = "--reset-cycles=";
    constexpr const char* roi_prefix = "--roi-cycles=";
    if (argument.rfind(max_prefix, 0) == 0) {
      options.max_cycles = parse_u64(
          argv[0], "--max-cycles", argv[index] + std::strlen(max_prefix));
      continue;
    }
    if (argument.rfind(reset_prefix, 0) == 0) {
      options.reset_cycles = parse_u64(
          argv[0], "--reset-cycles", argv[index] + std::strlen(reset_prefix));
      continue;
    }
    if (argument.rfind(roi_prefix, 0) == 0) {
      options.roi_cycles = parse_u64(
          argv[0], "--roi-cycles", argv[index] + std::strlen(roi_prefix));
      continue;
    }
    if (!argument.empty() && argument[0] == '+') continue;
    usage(argv[0],
          "runner options/RTL plusargs must be separated from HTIF by `--`");
  }
  if (options.htif_start < 0 || options.htif_start >= argc)
    usage(argv[0], "missing `-- BINARY`");
  if (options.max_cycles == 0) usage(argv[0], "--max-cycles must be positive");
  if (options.roi_cycles != 0 && !options.quiesce_debug_at_entry)
    usage(argv[0], "--roi-cycles requires --quiesce-debug-at-entry");
  return options;
}

constexpr std::uint64_t kDebugPcMask =
    (UINT64_C(1) << 41) - UINT64_C(1);

std::uint64_t elf_entry_point(const char* path) {
  std::FILE* file = std::fopen(path, "rb");
  if (!file) throw std::runtime_error("cannot open target ELF");
  unsigned char ident[EI_NIDENT]{};
  if (std::fread(ident, sizeof(ident), 1, file) != 1 ||
      std::memcmp(ident, ELFMAG, SELFMAG) != 0 ||
      ident[EI_DATA] != ELFDATA2LSB) {
    std::fclose(file);
    throw std::runtime_error("unsupported target ELF");
  }
  std::rewind(file);
  std::uint64_t entry = 0;
  if (ident[EI_CLASS] == ELFCLASS64) {
    Elf64_Ehdr header{};
    if (std::fread(&header, sizeof(header), 1, file) != 1) {
      std::fclose(file);
      throw std::runtime_error("truncated target ELF");
    }
    entry = header.e_entry;
  } else if (ident[EI_CLASS] == ELFCLASS32) {
    Elf32_Ehdr header{};
    if (std::fread(&header, sizeof(header), 1, file) != 1) {
      std::fclose(file);
      throw std::runtime_error("truncated target ELF");
    }
    entry = header.e_entry;
  } else {
    std::fclose(file);
    throw std::runtime_error("unsupported target ELF class");
  }
  std::fclose(file);
  return entry;
}

bool target_entry_reached(const SystemGuider& model, std::uint64_t entry) {
  const auto& core = model.backend().core();
  return !model.reset_asserted() && !core.csr().debug &&
         (core.out_ifu_debug_fetch_pc_0 & kDebugPcMask) ==
             (entry & kDebugPcMask);
}

bool chisa_mw_debug_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_MW_DEBUG")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

bool chisa_dcport_debug_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_DCPORT_DEBUG")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

bool chisa_seam_audit_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_SEAM_AUDIT")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

// Boundary contracts are cheap enough to run with every strict qualification
// so the first failing workload already contains causal seam evidence.  A
// range can narrow them for an interactive run; `off` is an explicit escape
// hatch.  This is separate from CHISA_SEAM_AUDIT, whose deep internal edge
// checks are intentionally opt-in.
bool chisa_boundary_audit_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static bool all = false;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_BOUNDARY_AUDIT")) {
      if (std::strcmp(window, "off") == 0) return true;
      if (std::strcmp(window, "all") == 0) {
        all = true;
        return true;
      }
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
      return true;
    }
    all = std::getenv("SYSPROBE_STRICT") != nullptr;
    return true;
  }();
  (void)initialized;
  return all ||
         (lo >= 0 && static_cast<long>(cycle) >= lo &&
          static_cast<long>(cycle) <= hi);
}

[[maybe_unused]] static bool chisa_tage_audit_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_TAGE_AUDIT")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

bool chisa_edge_audit_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_EDGE_AUDIT")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

// Unlike the oracle checker, this diagnostic compares the semantically-live
// PRE state on both sides before either machine takes the edge.  It is useful
// when an unselected state bit diverges several cycles before the first oracle
// that happens to consume it.  The audit is observation-only: no RTL value is
// ever fed back into the model.
[[maybe_unused]] bool chisa_state_audit_cycle(std::uint64_t cycle) {
  static long lo = -1;
  static long hi = -1;
  static const bool initialized = [] {
    if (const char* window = std::getenv("CHISA_STATE_AUDIT")) {
      long first = -1;
      long last = -1;
      if (std::sscanf(window, "%ld-%ld", &first, &last) == 2) {
        lo = first;
        hi = last;
      }
    }
    return true;
  }();
  (void)initialized;
  return lo >= 0 && static_cast<long>(cycle) >= lo &&
         static_cast<long>(cycle) <= hi;
}

}  // namespace


// ---- checkpoint -----------------------------------------------------------
// At --checkpoint-at the process forks a holder that keeps the whole
// simulation state (the emitted RTL simulator, the model, fesvr) at that
// cycle.  The holder waits on a fifo for lines
//   run <max_cycles> <out_file> [KEY=VAL ...]     or     quit
// and forks a child per run: the child applies the env knobs, re-reads the
// probe configuration, sends stdout/stderr to <out_file> and continues the
// main loop from the checkpoint.  Re-running an experiment that used to
// need the full simulation from cycle 0 then takes seconds.  The process is
// single-threaded (fesvr's contexts are ucontexts), so fork() is complete.
void checkpoint_hook(const Options& options, uint64_t& run_max_cycles) {
  std::fflush(stdout);
  std::fflush(stderr);
  std::string ctl = options.checkpoint_ctl;
  if (ctl.empty())
    ctl = "/tmp/lockstep-ckpt-" + std::to_string(options.checkpoint_at) + ".fifo";
  ::unlink(ctl.c_str());
  if (::mkfifo(ctl.c_str(), 0600) != 0) {
    std::perror("[CKPT] mkfifo");
    return;
  }
  const pid_t holder = ::fork();
  if (holder < 0) {
    std::perror("[CKPT] fork");
    return;
  }
  if (holder > 0) {
    std::fprintf(stderr, "[CKPT] cycle %llu held by pid %d, control fifo %s\n",
                 static_cast<unsigned long long>(options.checkpoint_at),
                 static_cast<int>(holder), ctl.c_str());
    return;  // the original run continues
  }
  ::setsid();
  ::signal(SIGHUP, SIG_IGN);
  for (;;) {
    std::FILE* f = std::fopen(ctl.c_str(), "r");  // blocks until a writer
    if (f == nullptr) std::_Exit(1);
    char line[4096];
    std::string cmd;
    if (std::fgets(line, sizeof line, f) != nullptr) cmd = line;
    std::fclose(f);
    while (!cmd.empty() && (cmd.back() == '\n' || cmd.back() == '\r' || cmd.back() == ' '))
      cmd.pop_back();
    if (cmd.empty()) continue;
    if (cmd == "quit") {
      ::unlink(ctl.c_str());
      std::_Exit(0);
    }
    std::vector<std::string> tok;
    {
      std::size_t i = 0;
      while (i < cmd.size()) {
        while (i < cmd.size() && cmd[i] == ' ') ++i;
        std::size_t j = i;
        while (j < cmd.size() && cmd[j] != ' ') ++j;
        if (j > i) tok.push_back(cmd.substr(i, j - i));
        i = j;
      }
    }
    if (tok.size() < 3 || tok[0] != "run") {
      std::fprintf(stderr, "[CKPT] bad command: %s\n", cmd.c_str());
      continue;
    }
    const uint64_t max_cycles = std::strtoull(tok[1].c_str(), nullptr, 0);
    const std::string out = tok[2];
    std::fflush(stdout);
    std::fflush(stderr);
    const pid_t child = ::fork();
    if (child < 0) {
      std::perror("[CKPT] fork");
      continue;
    }
    if (child == 0) {
      const int fd = ::open(out.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd >= 0) {
        ::dup2(fd, 1);
        ::dup2(fd, 2);
        ::close(fd);
      }
      for (std::size_t i = 3; i < tok.size(); ++i) {
        const std::size_t eq = tok[i].find('=');
        if (eq == std::string::npos) continue;
        ::setenv(tok[i].substr(0, eq).c_str(), tok[i].substr(eq + 1).c_str(), 1);
      }
      run_max_cycles = max_cycles;
      ++chisa::boom_model::g_env_generation;   // model-side env-gated traces re-read their knobs
      SystemProbes::instance().reconfigure_from_env();
      std::fprintf(stderr, "[CKPT] resumed from cycle %llu, max_cycles=%llu\n",
                   static_cast<unsigned long long>(options.checkpoint_at),
                   static_cast<unsigned long long>(max_cycles));
      return;  // continue the main loop from the checkpoint
    }
    int status = 0;
    ::waitpid(child, &status, 0);
    std::fprintf(stderr, "[CKPT] run to %llu finished, status=%d, output %s\n",
                 static_cast<unsigned long long>(max_cycles), status, out.c_str());
  }
}

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);

    std::vector<char*> htif_argv;
    htif_argv.reserve(static_cast<std::size_t>(argc - options.htif_start + 1));
    htif_argv.push_back(argv[0]);
    for (int index = options.htif_start; index < argc; ++index)
      htif_argv.push_back(argv[index]);

    SystemProbes& probes = SystemProbes::instance();
    probes.configure_from_env();
    chisa::boom_system::register_model_streams();
    const char* probe_spec = std::getenv("SYSPROBE");
    std::uint64_t probe_skip_cycles = 0;
    bool probe_skip_known = true;
    if (const char* skip = std::getenv("SYSPROBE_SKIP")) {
      char* end = nullptr;
      errno = 0;
      const long long value = std::strtoll(skip, &end, 10);
      probe_skip_known = errno == 0 && end != skip && *end == '\0' && value >= 0;
      if (probe_skip_known) probe_skip_cycles = static_cast<std::uint64_t>(value);
    }
    constexpr std::size_t tap_streams =
        chisa::boom_repcut::kExactRegisterTapCount +
        chisa::boom_repcut::kExactCombinationalTapCount;
    bool probe_contract_known = probes.active() && probes.strict() &&
        probe_spec && std::strcmp(probe_spec, "all") == 0 && probe_skip_known &&
        tap_streams != 0 && probes.registered_stream_count() == tap_streams &&
        probes.modeled_stream_count() == tap_streams &&
        probes.profile_assumption_stream_count() == 0 && exact_probe_tap_contract();

    auto model_dtm = std::make_unique<dtm_t>(
        static_cast<int>(htif_argv.size()), htif_argv.data());
    auto model_debug =
        std::make_unique<chisa::boom_repcut::FesvrDebugBootstrap<dtm_t>>(
            *model_dtm);
    BoundaryConfig config;
    config.image_path = argv[options.htif_start];
    config.argc = argc;
    config.argv = argv;
    config.reset_cycles = options.reset_cycles;
    config.debug_bootstrap = model_debug.get();
    SystemGuider model(config);
    ModelObserver<HalfDirection, TapPhase> observer(model);
    if (options.quiesce_debug_at_entry) {
      // Program loading establishes the initial full-chip state but is not the
      // target simulation region.  Keep stepping both sides while suppressing
      // coverage, mismatch and sentinel accounting until the clean handoff.
      probes.pause_measurement();
      observer.pause_measurement();
    }

    auto dut = std::make_unique<TestHarness>();
    auto dtm = std::make_unique<dtm_t>(
        static_cast<int>(htif_argv.size()), htif_argv.data());
    chisa::boom_repcut::W1ReferenceStepper<
        dtm_t, ModelObserver<HalfDirection, TapPhase>>
        stepper(*dut, *dtm, observer, argc, argv);

    bool success = false;
    bool entry_seen = false;
    bool debug_shutdown_started = false;
    bool roi_started = false;
    bool roi_complete = false;
    uint64_t entry_cycle = 0;
    uint64_t debug_shutdown_cycle = 0;
    uint64_t roi_start_cycle = 0;
    uint64_t comparison_start_cycle = 0;
    uint64_t compared_cycles = 0;
    bool seam_reported = false;
    bool boundary_mismatch = false;
    [[maybe_unused]] bool state_audit_reported = false;
    // The generated evaluator computes seam combinational wires from PRE
    // registers and commits those registers before the post-eval hook runs.
    // Keep the PRE register face explicitly; reading the DUT object in the
    // hook would mix next-state reasons with the current-edge event.
    struct DcachePreFace {
      bool s2_valid = false;
      bool s2_send = false;
      std::uint64_t s2_address = 0;
      std::uint8_t s2_type = 0;
      std::uint8_t s2_br_mask = 0;
      bool flush = false;
      std::uint8_t mshr0_state = 0;
      std::uint8_t mshr1_state = 0;
    } rtl_dcache_pre;
    std::uint8_t rtl_ptw_state_pre = 0;
    std::uint8_t rtl_dtlb_state_pre = 0;
    bool rtl_dtlb_refill_pre = false;
    std::uint32_t rtl_dtlb_refill_tag_pre = 0;
    std::uint32_t rtl_itlb_refill_tag_pre = 0;
    // EDGE audit keeps both state faces.  The post-eval hook can see RTL PRE
    // registers and generated `$next`, while the model has already committed
    // its edge.  Snapshot model PRE here so diagnostics can classify a seam as
    // WRITE/WRITE, WRITE/HOLD, HOLD/WRITE, or an older carried divergence.
    [[maybe_unused]] const auto pack_stq_bank01 = [](const auto& core) -> std::uint64_t {
      const auto& s1 = core.lsu.stq[1];
      const auto& s2 = core.lsu.stq[2];
      return (static_cast<std::uint64_t>(s1.uop.stq_idx & 0x7u) << 61) |
             (static_cast<std::uint64_t>(s1.uop.pdst & 0x3fu) << 55) |
             (static_cast<std::uint64_t>(s1.uop.exception) << 54) |
             (static_cast<std::uint64_t>(s1.uop.mem_cmd & 0x1fu) << 49) |
             (static_cast<std::uint64_t>(s1.uop.mem_size & 0x3u) << 47) |
             (static_cast<std::uint64_t>(s1.uop.mem_signed) << 46) |
             (static_cast<std::uint64_t>(s1.uop.is_fence) << 45) |
             (static_cast<std::uint64_t>(s1.uop.is_amo) << 44) |
             (static_cast<std::uint64_t>(s1.uop.uses_ldq) << 43) |
             (static_cast<std::uint64_t>(s1.uop.uses_stq) << 42) |
             (static_cast<std::uint64_t>(s1.uop.dst_rtype & 0x3u) << 40) |
             (static_cast<std::uint64_t>(s1.addr_valid) << 39) |
             (static_cast<std::uint64_t>(s1.data_valid) << 38) |
             (static_cast<std::uint64_t>(s1.committed) << 37) |
             (static_cast<std::uint64_t>(s1.succeeded) << 36) |
             (static_cast<std::uint64_t>(s2.valid) << 35) |
             (static_cast<std::uint64_t>(s2.uop.br_mask) << 27) |
             (static_cast<std::uint64_t>(s2.uop.rob_idx & 0x1fu) << 22) |
             (static_cast<std::uint64_t>(s2.uop.ldq_idx & 0x7u) << 19) |
             (static_cast<std::uint64_t>(s2.uop.stq_idx & 0x7u) << 16) |
             (static_cast<std::uint64_t>(s2.uop.pdst & 0x3fu) << 10) |
             (static_cast<std::uint64_t>(s2.uop.exception) << 9) |
             (static_cast<std::uint64_t>(s2.uop.mem_cmd & 0x1fu) << 4) |
             (static_cast<std::uint64_t>(s2.uop.mem_size & 0x3u) << 2) |
             (static_cast<std::uint64_t>(s2.uop.mem_signed) << 1) |
             static_cast<std::uint64_t>(s2.uop.is_fence);
    };
    [[maybe_unused]] std::uint64_t seam_rtl_stq_bank01_pre = 0;
    [[maybe_unused]] std::uint64_t seam_model_stq_bank01_pre = 0;
    [[maybe_unused]] MicroOp seam_model_disp_uop_pre{};
    [[maybe_unused]] bool seam_model_disp_valid_pre = false;
    [[maybe_unused]] int seam_model_stq_tail_pre = 0;
    [[maybe_unused]] bool edge_rtl_ren_exception_pre = false;
    [[maybe_unused]] bool edge_model_ren_exception_pre = false;
    [[maybe_unused]] bool edge_model_fetch_offered_pre = false;
    [[maybe_unused]] MicroOp edge_model_fetch_pre{};
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    std::uint8_t edge_rtl_ftq_get1_addr_pre = 0;
    std::uint16_t edge_model_f3_prev_half_pre = 0;
    bool edge_model_f3_prev_is_half_pre = false;
    struct FrontendQueuePreFace {
      bool f4_full = false;
      std::uint64_t f4_pc = 0;
      std::uint8_t f4_mask = 0;
      std::uint8_t f4_sfb_mask = 0;
      bool f4_cfi_valid = false;
      std::uint8_t f4_cfi_idx = 0;
      std::uint32_t fb_head = 0;
      std::uint32_t fb_tail = 0;
      bool fb_maybe_full = false;
      bool ftq_enq_ready = false;
      std::uint8_t ftq_enq_idx = 0;
      bool ic_s1_valid = false;
      bool ic_s2_valid = false;
      bool ic_s2_hit = false;
      bool ic_refill_valid = false;
      std::uint32_t ic_refill_paddr = 0;
      std::uint8_t ic_tag_read_set = 0;
    } edge_model_frontend_pre;
#endif
    const uint64_t entry = options.quiesce_debug_at_entry
                               ? elf_entry_point(argv[options.htif_start])
                               : 0;
    stepper.set_post_eval_hook(
        [&](TestHarness& hook_dut, uint64_t hook_cycle, HalfDirection) {
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
          if (chisa_mw_debug_cycle(hook_cycle)) {
            const auto& model_raw = model.backend().raw_attempt();
            const auto& model_fire = model.backend().memory_request();
            const auto& model_core = model.backend().core();
            const auto& model_dcache =
                model.memory().dcache_for_diagnostic();
            std::fprintf(
                stderr,
                "[LARGE-DREQ-POST] c=%llu "
                "rtl(req=%u ready=%u fire=%u addr=%llx cmd=%u sz=%u "
                "ld/st=%u/%u idx=%u/%u type.next=%u/%u ctl.next=%u/%u) "
                "model(raw=%u/%llx fire=%u/%llx type=%u/%u "
                "agu/iss=%u/%u ldq(h/t)=%u/%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_valid[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_req_ready[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$_T_25[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_addr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_mem_cmd[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_mem_size[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_uses_ldq[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_uses_stq[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_ldq_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_uop_stq_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$s1_type$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$s2_type$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$REG$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$REG_3$next[0]
                        .val),
                static_cast<unsigned>(model_raw.valid),
                static_cast<unsigned long long>(model_raw.address),
                static_cast<unsigned>(model_fire.valid),
                static_cast<unsigned long long>(model_fire.address),
                static_cast<unsigned>(model_dcache.oracle_s1_type()),
                static_cast<unsigned>(model_dcache.oracle_s2_type()),
                static_cast<unsigned>(model_core.mem_agu.v),
                static_cast<unsigned>(model_core.mem_iss_stage.v),
                static_cast<unsigned>(model_core.lsu.ldq_head),
                static_cast<unsigned>(model_core.lsu.ldq_tail));
            const auto& rtl_core =
                hook_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile
                    .core;
            const auto& rr = rtl_core.iregister_read;
            const auto& omir = model_core.omir;
            std::fprintf(
                stderr,
                "[LARGE-IREG-EDGE] c=%llu "
                "rtl(next=%llx post=%llx prs-post=%u rt-post=%u "
                "rfaddr-post=%u z-post=%u raw=%llx "
                "src=%llx/%llx/%llx/%llx/%llx "
                "g=%u%u/%u%u/%u%u/%u%u/%u%u common=%u%u) "
                "model(out=%llx rrd=%u/p%u/t%u "
                "b1=%u/p%u/%llx b2=%u/p%u/%llx)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$exe_reg_rs1_data_1$next[0]
                        .val),
                static_cast<unsigned long long>(
                    rr.exe_reg_rs1_data_1[0].val),
                static_cast<unsigned>(rr.REG_3_prs1[0].val),
                static_cast<unsigned>(rr.REG_3_lrs1_rtype[0].val),
                static_cast<unsigned>(rtl_core.iregfile.read_addrs_2[0].val),
                static_cast<unsigned>(rr.REG_10[0].val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregfile$io_read_ports_2_data[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_0_bits_data[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_1_bits_data[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_2_bits_data[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_3_bits_data[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_4_bits_data[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_70[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_72[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_90[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_92[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_110[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_112[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_130[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_132[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_150[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_152[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_191[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$_T_193[0]
                        .val),
                static_cast<unsigned long long>(omir.exe_rs1_data[1]),
                static_cast<unsigned>(model_core.int_rrd_at(0).v),
                static_cast<unsigned>(model_core.int_rrd_at(0).uop.prs1),
                static_cast<unsigned>(
                    model_core.int_rrd_at(0).uop.lrs1_rtype),
                static_cast<unsigned>(omir.byp1.v),
                static_cast<unsigned>(omir.byp1.pdst),
                static_cast<unsigned long long>(omir.byp1.data),
                static_cast<unsigned>(omir.byp2.v),
                static_cast<unsigned>(omir.byp2.pdst),
                static_cast<unsigned long long>(omir.byp2.data));
          }
#endif  // CHISA_LEGACY_CORE_DIAG
#endif
          if (chisa_mw_debug_cycle(hook_cycle)) {
            const auto& mi = model.last_itlb_boundary();
            std::fprintf(
                stderr,
                "[ITLBPOST] c=%llu "
                "rtl(v=%llx rep=%u vm=%u hits=%04llx refill=%u "
                "prot_x=%u ptwae=%04llx raw[m=%u ae=%u pf=%u]) "
                "model(v=%llx rep=%u vm=%u req=%u refill=%u "
                "entry[ae=%u px=%u sx=%u] raw[m=%u ae=%u pf=%u])\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned long long>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain
                        .boom_tile.frontend.s1_vpc[0]
                        .val),
                static_cast<unsigned>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain
                        .boom_tile.frontend.s1_is_replay[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$vm_enabled[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$hits[0]
                        .val),
                static_cast<unsigned>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain
                        .boom_tile.ptw.resp_valid_1[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$prot_x[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$ptw_ae_array[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$io_resp_miss[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$io_resp_ae_inst[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$io_resp_pf_inst[0]
                        .val),
                static_cast<unsigned long long>(mi.input.virtual_address),
                static_cast<unsigned>(mi.s1_is_replay),
                static_cast<unsigned>(mi.input.vm_enabled),
                static_cast<unsigned>(mi.input.request_valid),
                static_cast<unsigned>(mi.input.refill.valid),
                static_cast<unsigned>(mi.input.refill.data.ae),
                static_cast<unsigned>(mi.input.refill.data.px),
                static_cast<unsigned>(mi.input.refill.data.sx),
                static_cast<unsigned>(mi.raw_response.miss),
                static_cast<unsigned>(mi.raw_response.xcpt_ae_if),
                static_cast<unsigned>(mi.raw_response.xcpt_pf_if));
          }
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
          if (chisa_edge_audit_cycle(hook_cycle)) {
            const auto& core = model.backend().core();
            const unsigned rtl_interrupt =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$decode_units_0$_T_597[0]
                    .val;
            const unsigned rtl_bp_debug =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_bp_debug_if[0]
                    .val;
            const unsigned rtl_bp_xcpt =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_bp_xcpt_if[0]
                    .val;
            const unsigned rtl_pf =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_xcpt_pf_if[0]
                    .val;
            const unsigned rtl_ae =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_xcpt_ae_if[0]
                    .val;
            const unsigned rtl_dec_exception =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$decode_units_0$io_deq_uop_exception[0]
                    .val;
            const unsigned rtl_decode_other =
                rtl_dec_exception &&
                !(rtl_interrupt || rtl_bp_debug || rtl_bp_xcpt || rtl_pf ||
                  rtl_ae);
            std::fprintf(
                stderr,
                "[RENAME-EDGE] c=%llu "
                "rtl(reg=%u->%u dec=%u src=i%u/bd%u/bx%u/pf%u/ae%u/o%u "
                "inst=%08x fb=%u/%u decv/fire=%u/%u disrdy=%u kill=%u "
                "csr-illegal=f%u/r%u/w%u/s%u) "
                "model(reg=%u->%u held=%u inst=%08x "
                "src=e%u/bd%u/bx%u/pf%u/ae%u disrdy=%u flush=%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(edge_rtl_ren_exception_pre),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rename_stage$REG_1_exception$next[0]
                        .val),
                rtl_dec_exception, rtl_interrupt, rtl_bp_debug, rtl_bp_xcpt,
                rtl_pf, rtl_ae, rtl_decode_other,
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_inst[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_valid[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_valid[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$dec_valids_0[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$dec_fire_0[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rename_stage$io_dis_ready[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_ifu_redirect_flush[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr$io_decode_0_fp_illegal[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr$io_decode_0_read_illegal[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr$io_decode_0_write_illegal[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr$io_decode_0_system_illegal[0]
                        .val),
                static_cast<unsigned>(edge_model_ren_exception_pre),
                static_cast<unsigned>(core.ren_r_uop.exception),
                static_cast<unsigned>(edge_model_fetch_offered_pre),
                static_cast<unsigned>(edge_model_fetch_pre.inst),
                static_cast<unsigned>(edge_model_fetch_pre.exception),
                static_cast<unsigned>(edge_model_fetch_pre.bp_debug_if),
                static_cast<unsigned>(edge_model_fetch_pre.bp_xcpt_if),
                static_cast<unsigned>(edge_model_fetch_pre.xcpt_pf_if),
                static_cast<unsigned>(edge_model_fetch_pre.xcpt_ae_if),
                static_cast<unsigned>(core.dis_ready),
                static_cast<unsigned>(core.omir.flush_redirect_now ||
                                      core.br_kill_this_cycle));
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
            const auto& rtl_core =
                hook_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile.core;
            const auto& rtl_ftq = hook_dut.ldut.tile_prci_domain
                                      .tile_reset_domain.boom_tile.frontend.ftq;
            const auto& model_ftq = model.frontend().ftq_for_diagnostic();
            std::fprintf(
                stderr,
                "[FTQ-EDGE] c=%llu "
                "rtl(arb=%u xcpt=%u in2=%u j=%u:%u pc=%llx->%llx "
                "fbidx=%u,%u,%u) "
                "model(arb=%u dec=%u j=%u:%u flush=%u:%u pc=%llx) "
                "comftq(rtl=%u->%u model=%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ftq_arb$io_out_bits[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$xcpt_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ftq_arb$io_in_2_bits[0]
                        .val),
                static_cast<unsigned>(rtl_core.REG_15[0].val),
                static_cast<unsigned>(rtl_core.REG_16[0].val),
                static_cast<unsigned long long>(rtl_ftq.REG_18[0].val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$REG_18$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_ftq_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_1_bits_ftq_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_2_bits_ftq_idx[0]
                        .val),
                static_cast<unsigned>(core.out_ifu_get_pc_0_ftq_idx),
                static_cast<unsigned>(core.dec_uop_ftq_wire),
                static_cast<unsigned>(core.jmp_pc_req_valid_r),
                static_cast<unsigned>(core.jmp_pc_req_bits_r),
                static_cast<unsigned>(core.rob_flush_now),
                static_cast<unsigned>(core.rob_flush_ftq_now),
                static_cast<unsigned long long>(
                    model_ftq.registered_get_pc(0).pc),
                static_cast<unsigned>(rtl_core.REG_11[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$REG_11$next[0]
                        .val),
                static_cast<unsigned>(core.omir.commit_snap_uop.ftq_idx));
            std::uint32_t rtl_current_saw_mask = 0;
            for (std::size_t i = 0; i < boomcfg::NUM_FTQ; ++i) {
              if (rtl_ftq.ghist_1_current_saw_branch_not_taken[i].val != 0)
                rtl_current_saw_mask |= std::uint32_t{1} << i;
            }
            const unsigned rtl_addr_post = static_cast<unsigned>(
                (hook_dut
                     ._v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$ghist__v2_bank_0_0[0]
                     .val >>
                 15) &
                0x1fu);
            std::fprintf(
                stderr,
                "[FTQ-GHIST] c=%llu rtl(addr=%u->%u get1=%u raw=%u "
                "csnt=%08x) model(get1=%u raw_idx=%u raw=%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(edge_rtl_ftq_get1_addr_pre),
                rtl_addr_post,
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_ifu_get_pc_1_ftq_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$ghist_1_current_saw_branch_not_taken$MPORT_3[0]
                        .val),
                static_cast<unsigned>(rtl_current_saw_mask),
                static_cast<unsigned>(core.out_ifu_get_pc_1_ftq_idx),
                static_cast<unsigned>(model_ftq.oracle_ram_idx(3)),
                static_cast<unsigned>(model_ftq.oracle_getpc1_ghist()
                                          .current_saw_branch_not_taken));
            const auto& frontend_eval = model.frontend_evaluation_;
            const auto& assembler_eval = frontend_eval.output.f3_assembled;
            const auto& assembler_input = frontend_eval.assembler_input;
            const auto& rtl_frontend =
                hook_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile
                    .frontend;
            const auto& model_frontend = model.frontend();
            const auto& model_f4 =
                model_frontend.f4_queue_for_diagnostic();
            const auto& model_fb =
                model_frontend.fetch_buffer_for_diagnostic();
            const auto model_ftq_post =
                model_frontend.ftq_for_diagnostic().outputs({});
            unsigned rtl_f4_sfb_mask = 0;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_0[0].val) << 0;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_1[0].val) << 1;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_2[0].val) << 2;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_3[0].val) << 3;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_4[0].val) << 4;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_5[0].val) << 5;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_6[0].val) << 6;
            rtl_f4_sfb_mask |=
                static_cast<unsigned>(rtl_frontend.f4.ram_sfbs_7[0].val) << 7;
            std::fprintf(
                stderr,
                "[F4-EDGE] c=%llu "
                "rtl(f4=%u->%u dv/dr=%u/%u er/ev=%u/%u "
                "delay=%u mask/sfb/cfi=%02x/%02x/%u:%u pc=%llx "
                "fb=r%u ev=%u tail=%06x->%06x full=%u->%u "
                "ftq=r%u ev/fire=%u/%u ptr=%u->%u clear=%u) "
                "model(f4=%u->%u dv/dr=%u/%u er/ev=%u/%u "
                "delay=%u mask/sfb/cfi=%02x/%02x/%u:%u pc=%llx "
                "fb=r%u ev=%u tail=%06x->%06x full=%u->%u "
                "ftq=r%u ev=%u ptr=%u->%u clear=%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_frontend.f4.maybe_full[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f4$maybe_full$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f4$io_deq_valid[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f4$io_deq_ready[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f4$io_enq_ready[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f4$io_enq_valid[0]
                        .val),
                static_cast<unsigned>(
                    !_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$_T_2086[0]
                         .val),
                static_cast<unsigned>(rtl_frontend.f4.ram_mask[0].val),
                rtl_f4_sfb_mask,
                static_cast<unsigned>(
                    rtl_frontend.f4.ram_cfi_idx_valid[0].val),
                static_cast<unsigned>(rtl_frontend.f4.ram_cfi_idx_bits[0].val),
                static_cast<unsigned long long>(rtl_frontend.f4.ram_pc[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_enq_ready[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_enq_valid[0]
                        .val),
                static_cast<unsigned>(rtl_frontend.fb.tail[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$tail$next[0]
                        .val),
                static_cast<unsigned>(rtl_frontend.fb.maybe_full[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$maybe_full$next[0]
                        .val),
                static_cast<unsigned>(rtl_frontend.ftq.REG_12[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$io_enq_valid[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$do_enq[0]
                        .val),
                static_cast<unsigned>(rtl_frontend.ftq.enq_ptr[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$enq_ptr$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_clear[0]
                        .val),
                static_cast<unsigned>(edge_model_frontend_pre.f4_full),
                static_cast<unsigned>(model_f4.full()),
                static_cast<unsigned>(frontend_eval.f4_output.deq_valid),
                static_cast<unsigned>(frontend_eval.output.f4_deq_ready),
                static_cast<unsigned>(frontend_eval.f4_output.enq_ready),
                static_cast<unsigned>(frontend_eval.f4_input.enq_valid),
                static_cast<unsigned>(frontend_eval.output.f4_delay),
                static_cast<unsigned>(edge_model_frontend_pre.f4_mask),
                static_cast<unsigned>(edge_model_frontend_pre.f4_sfb_mask),
                static_cast<unsigned>(edge_model_frontend_pre.f4_cfi_valid),
                static_cast<unsigned>(edge_model_frontend_pre.f4_cfi_idx),
                static_cast<unsigned long long>(edge_model_frontend_pre.f4_pc),
                static_cast<unsigned>(frontend_eval.output.fetch_buffer_enq_ready),
                static_cast<unsigned>(frontend_eval.fetch_buffer_input.enq_valid),
                static_cast<unsigned>(edge_model_frontend_pre.fb_tail),
                static_cast<unsigned>(model_fb.tail()),
                static_cast<unsigned>(edge_model_frontend_pre.fb_maybe_full),
                static_cast<unsigned>(model_fb.maybe_full()),
                static_cast<unsigned>(frontend_eval.output.ftq_enq_ready),
                static_cast<unsigned>(frontend_eval.ftq_input.enq_valid),
                static_cast<unsigned>(edge_model_frontend_pre.ftq_enq_idx),
                static_cast<unsigned>(model_ftq_post.enq_idx),
                static_cast<unsigned>(frontend_eval.fetch_buffer_input.clear));
            std::fprintf(
                stderr,
                "[F3-EDGE] c=%llu "
                "rtl(prev=%04x->%04x half=%u->%u fire=%u banks=%u "
                "lo5=%04x last=%04x) "
                "model(prev=%04x->%04x half=%u->%u fire=%u clear=%u "
                "pc=%llx mask=%02x data=%016llx/%016llx out=%04x:%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain
                        .boom_tile.frontend.f3_prev_half[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f3_prev_half$next[0]
                        .val),
                static_cast<unsigned>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain
                        .boom_tile.frontend.f3_prev_is_half[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f3_prev_is_half$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$_T_1634[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$f3_bank_mask[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$lo_5[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$last_inst[0]
                        .val),
                static_cast<unsigned>(edge_model_f3_prev_half_pre),
                static_cast<unsigned>(
                    model.frontend().f3_assembler_for_diagnostic().prev_half()),
                static_cast<unsigned>(edge_model_f3_prev_is_half_pre),
                static_cast<unsigned>(
                    model.frontend().f3_assembler_for_diagnostic().prev_is_half()),
                static_cast<unsigned>(assembler_input.main_valid &&
                                      assembler_input.deq_ready),
                static_cast<unsigned>(assembler_input.clear),
                static_cast<unsigned long long>(assembler_input.main.pc),
                static_cast<unsigned>(assembler_input.main.mask),
                static_cast<unsigned long long>(
                    assembler_input.main.data_word(0)),
                static_cast<unsigned long long>(
                    assembler_input.main.data_word(1)),
                static_cast<unsigned>(assembler_eval.trailing_half),
                static_cast<unsigned>(assembler_eval.trailing_half_valid));
            unsigned rtl_ic_tag_hits = 0;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_0[0]
                                       .val)
                               << 0;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_1[0]
                                       .val)
                               << 1;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_2[0]
                                       .val)
                               << 2;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_3[0]
                                       .val)
                               << 3;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_4[0]
                                       .val)
                               << 4;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_5[0]
                                       .val)
                               << 5;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_6[0]
                                       .val)
                               << 6;
            rtl_ic_tag_hits |= static_cast<unsigned>(
                                   _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag_hit_7[0]
                                       .val)
                               << 7;
            unsigned model_ic_tag_hits = 0;
            for (std::size_t way = 0; way < boomcfg::ICACHE_WAYS; ++way)
              model_ic_tag_hits |=
                  static_cast<unsigned>(
                      frontend_eval.output.icache.s1_tag_hit[way])
                  << way;
            const auto& rtl_icache = rtl_frontend.icache;
            const auto& model_icache =
                model_frontend.icache_for_diagnostic();
            std::fprintf(
                stderr,
                "[IC-EDGE] c=%llu "
                "rtl(s1=%u->%u s2=%u->%u hit=%u->%u "
                "req=%u/%llx paddr=%08x kill=%u/%u "
                "idx/tag=%u/%05x hits=%02x refill=%u->%u/%08x beat/done=%u/%u) "
                "model(s1=%u->%u s2=%u->%u hit=%u->%u "
                "req=%u/%llx paddr=%08x kill=%u/%u "
                "idx=%u->%u hits=%02x refill=%u->%u/%08x beat/done=%u/%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_icache.s1_valid[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_valid$next[0]
                        .val),
                static_cast<unsigned>(rtl_icache.s2_valid[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s2_valid$next[0]
                        .val),
                static_cast<unsigned>(rtl_icache.s2_hit[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s2_hit$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$io_req_valid[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$io_req_bits_addr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$io_s1_paddr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$io_s1_kill[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$io_s2_kill[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$s1_tag[0]
                        .val),
                rtl_ic_tag_hits,
                static_cast<unsigned>(rtl_icache.refill_valid[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$refill_valid$next[0]
                        .val),
                static_cast<unsigned>(rtl_icache.refill_paddr[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$refill_one_beat[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$icache$refill_done[0]
                        .val),
                static_cast<unsigned>(edge_model_frontend_pre.ic_s1_valid),
                static_cast<unsigned>(model_icache.s1_valid()),
                static_cast<unsigned>(edge_model_frontend_pre.ic_s2_valid),
                static_cast<unsigned>(model_icache.s2_valid()),
                static_cast<unsigned>(edge_model_frontend_pre.ic_s2_hit),
                static_cast<unsigned>(model_icache.s2_hit()),
                static_cast<unsigned>(
                    frontend_eval.output.icache_input.req_valid),
                static_cast<unsigned long long>(
                    frontend_eval.output.icache_input.req_addr),
                static_cast<unsigned>(
                    frontend_eval.output.icache_input.s1_paddr),
                static_cast<unsigned>(
                    frontend_eval.output.icache_input.s1_kill),
                static_cast<unsigned>(
                    frontend_eval.output.icache_input.s2_kill),
                static_cast<unsigned>(edge_model_frontend_pre.ic_tag_read_set),
                static_cast<unsigned>(model_icache.tag_read_set()),
                model_ic_tag_hits,
                static_cast<unsigned>(
                    edge_model_frontend_pre.ic_refill_valid),
                static_cast<unsigned>(model_icache.refill_valid()),
                static_cast<unsigned>(model_icache.refill_paddr()),
                static_cast<unsigned>(
                    frontend_eval.output.icache.refill_one_beat),
                static_cast<unsigned>(
                    frontend_eval.output.icache.refill_done));
            std::fprintf(
                stderr,
                "[IC-CTRL] c=%llu "
                "rtl(flush=%u debug=%u reg=%u/%u/%u next=%u/%u/%u "
                "decv=%u/%u/%u jalr=%u/%u/%u "
                "inst=%08x/%08x/%08x) "
                "model(inv=%u out=%u debug=%u pending-next=%u "
                "offered=%u/%u/%u inst=%08x/%08x/%08x)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_ifu_flush_icache[0]
                        .val),
                static_cast<unsigned>(rtl_core.csr.reg_debug[0].val),
                static_cast<unsigned>(rtl_core.REG_1[0].val),
                static_cast<unsigned>(rtl_core.REG_2[0].val),
                static_cast<unsigned>(rtl_core.REG_3[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$REG_1$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$REG_2$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$REG_3$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$dec_valids_0[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$dec_valids_1[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$dec_valids_2[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$decode_units_0$io_deq_uop_is_jalr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$decode_units_1$io_deq_uop_is_jalr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$decode_units_2$io_deq_uop_is_jalr[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_0_bits_inst[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_1_bits_inst[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$fb$io_deq_bits_uops_2_bits_inst[0]
                        .val),
                static_cast<unsigned>(
                    frontend_eval.output.icache_input.invalidate),
                static_cast<unsigned>(core.out_ifu_flush_icache),
                static_cast<unsigned>(core.csr.debug),
                static_cast<unsigned>(
                    core.debug_jalr_flush_icache_pending),
                static_cast<unsigned>(core.fp_offered_at(0)),
                static_cast<unsigned>(core.fp_offered_at(1)),
                static_cast<unsigned>(core.fp_offered_at(2)),
                static_cast<unsigned>(core.fp_offered_inst_at(0)),
                static_cast<unsigned>(core.fp_offered_inst_at(1)),
                static_cast<unsigned>(core.fp_offered_inst_at(2)));
            std::fprintf(
                stderr,
                "[ROB-FSM] c=%llu "
                "rtl(state=%u next=%u unique-fire=%u/%u/%u enq=%u/%u/%u) "
                "model(state=%u wait=%u enq=%u unique=%u "
                "fire=%u/%u/%u valid=%u/%u/%u uniq=%u/%u/%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_core.rob.rob_state[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$rob_state$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$_T_2397[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$_T_2398[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$_T_2399[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$io_enq_valids_0[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$io_enq_valids_1[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$io_enq_valids_2[0]
                        .val),
                static_cast<unsigned>(core.omir.rob_state_oracle),
                static_cast<unsigned>(core.rob_wait_empty),
                static_cast<unsigned>(core.rob_enq_fired),
                static_cast<unsigned>(core.omir.rob_enq_unique),
                static_cast<unsigned>(core.dis_fire_g[0]),
                static_cast<unsigned>(core.dis_fire_g[1]),
                static_cast<unsigned>(core.dis_fire_g[2]),
                static_cast<unsigned>(core.disp_valid),
                static_cast<unsigned>(core.disp_valids_g[1]),
                static_cast<unsigned>(core.disp_valids_g[2]),
                static_cast<unsigned>(core.disp_uop.is_unique),
                static_cast<unsigned>(core.disp_uops_g[1].is_unique),
                static_cast<unsigned>(core.disp_uops_g[2].is_unique));
            std::fprintf(
                stderr,
                "[ROB-BR] c=%llu "
                "rtl(maybe=%u->%u b1=%04x "
                "brinfo=v%u%u%u/m%u%u%u/t%u%u%u) "
                "model(maybe=%u b1=%04x "
                "brinfo=v%u%u%u/m%u%u%u/t%u%u%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_core.rob.maybe_full[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$maybe_full$next[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$io_brupdate_b1_mispredict_mask[0]
                        .val),
                static_cast<unsigned>(rtl_core.brinfos_0_valid[0].val),
                static_cast<unsigned>(rtl_core.brinfos_1_valid[0].val),
                static_cast<unsigned>(rtl_core.brinfos_2_valid[0].val),
                static_cast<unsigned>(rtl_core.brinfos_0_mispredict[0].val),
                static_cast<unsigned>(rtl_core.brinfos_1_mispredict[0].val),
                static_cast<unsigned>(rtl_core.brinfos_2_mispredict[0].val),
                static_cast<unsigned>(rtl_core.brinfos_0_uop_br_tag[0].val),
                static_cast<unsigned>(rtl_core.brinfos_1_uop_br_tag[0].val),
                static_cast<unsigned>(rtl_core.brinfos_2_uop_br_tag[0].val),
                static_cast<unsigned>(core.omir.maybe_full),
                static_cast<unsigned>(core.omir.b1_mispred_mask_now),
                static_cast<unsigned>(core.brinfo_valid_r_g[0]),
                static_cast<unsigned>(core.brinfo_valid_r_g[1]),
                static_cast<unsigned>(core.brinfo_valid_r_g[2]),
                static_cast<unsigned>(core.brinfo_mispredict_r_g[0]),
                static_cast<unsigned>(core.brinfo_mispredict_r_g[1]),
                static_cast<unsigned>(core.brinfo_mispredict_r_g[2]),
                static_cast<unsigned>(core.brinfo_uop_r_at(0).br_tag),
                static_cast<unsigned>(core.brinfo_uop_r_at(1).br_tag),
                static_cast<unsigned>(core.brinfo_uop_r_at(2).br_tag));
            std::uint32_t rtl_iq_valid = 0;
            std::uint32_t rtl_iq_state2 = 0;
            std::uint32_t rtl_iq_p1 = 0;
            std::uint32_t rtl_iq_ppred = 0;
#define PACK_RTL_LARGE_IQ(I)                                             \
            do {                                                         \
              const auto& slot = rtl_core.int_issue_unit.slots_##I;      \
              rtl_iq_valid |= static_cast<std::uint32_t>(                \
                                  slot.state[0].val != 0)                \
                              << (I);                                    \
              rtl_iq_state2 |= static_cast<std::uint32_t>(               \
                                   slot.state[0].val == 2)               \
                               << (I);                                   \
              rtl_iq_p1 |= static_cast<std::uint32_t>(slot.p1[0].val)    \
                           << (I);                                       \
              rtl_iq_ppred |=                                            \
                  static_cast<std::uint32_t>(slot.ppred[0].val) << (I);  \
            } while (false)
            PACK_RTL_LARGE_IQ(0);
            PACK_RTL_LARGE_IQ(1);
            PACK_RTL_LARGE_IQ(2);
            PACK_RTL_LARGE_IQ(3);
            PACK_RTL_LARGE_IQ(4);
            PACK_RTL_LARGE_IQ(5);
            PACK_RTL_LARGE_IQ(6);
            PACK_RTL_LARGE_IQ(7);
            PACK_RTL_LARGE_IQ(8);
            PACK_RTL_LARGE_IQ(9);
            PACK_RTL_LARGE_IQ(10);
            PACK_RTL_LARGE_IQ(11);
            PACK_RTL_LARGE_IQ(12);
            PACK_RTL_LARGE_IQ(13);
            PACK_RTL_LARGE_IQ(14);
            PACK_RTL_LARGE_IQ(15);
            PACK_RTL_LARGE_IQ(16);
            PACK_RTL_LARGE_IQ(17);
            PACK_RTL_LARGE_IQ(18);
            PACK_RTL_LARGE_IQ(19);
            PACK_RTL_LARGE_IQ(20);
            PACK_RTL_LARGE_IQ(21);
            PACK_RTL_LARGE_IQ(22);
            PACK_RTL_LARGE_IQ(23);
            PACK_RTL_LARGE_IQ(24);
            PACK_RTL_LARGE_IQ(25);
            PACK_RTL_LARGE_IQ(26);
            PACK_RTL_LARGE_IQ(27);
            PACK_RTL_LARGE_IQ(28);
            PACK_RTL_LARGE_IQ(29);
            PACK_RTL_LARGE_IQ(30);
            PACK_RTL_LARGE_IQ(31);
#undef PACK_RTL_LARGE_IQ
            std::uint32_t model_iq_valid = 0;
            std::uint32_t model_iq_state2 = 0;
            std::uint32_t model_iq_p1 = 0;
            std::uint32_t model_iq_ppred = 0;
            for (int i = 0; i < core.int_iq.num_slots; ++i) {
              const auto& slot = core.int_iq.slot[i];
              model_iq_valid |= static_cast<std::uint32_t>(
                                    slot.state != IS_INVALID)
                                << i;
              model_iq_state2 |= static_cast<std::uint32_t>(
                                     slot.state == IS_VALID_2)
                                 << i;
              model_iq_p1 |= static_cast<std::uint32_t>(slot.p1) << i;
              model_iq_ppred |=
                  static_cast<std::uint32_t>(slot.ppred) << i;
            }
            std::uint32_t rtl_iq_recv_lo = 0;
            std::uint32_t rtl_iq_clear_lo = 0;
#define PACK_RTL_LARGE_IQ_CONTROL(I, RECV, CLEAR)                       \
            do {                                                        \
              rtl_iq_recv_lo |= static_cast<std::uint32_t>(             \
                  (RECV)[0].val)                                        \
                  << (I);                                               \
              rtl_iq_clear_lo |= static_cast<std::uint32_t>(            \
                  (CLEAR)[0].val)                                       \
                  << (I);                                               \
            } while (false)
            PACK_RTL_LARGE_IQ_CONTROL(0, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_0$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_0$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(1, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_1$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_1$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(2, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_2$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_2$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(3, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_3$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_3$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(4, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_4$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_4$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(5, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_5$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_5$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(6, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_6$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_6$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(7, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_7$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_7$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(8, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_8$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_8$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(9, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_9$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_9$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(10, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_10$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_10$io_clear);
            PACK_RTL_LARGE_IQ_CONTROL(11, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_11$io_in_uop_valid, _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_11$io_clear);
#undef PACK_RTL_LARGE_IQ_CONTROL
            const unsigned rtl_iq_iss =
                (static_cast<unsigned>(
                     _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$io_iss_valids_0[0]
                         .val)
                 << 0) |
                (static_cast<unsigned>(
                     _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$io_iss_valids_1[0]
                         .val)
                 << 1) |
                (static_cast<unsigned>(
                     _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$io_iss_valids_2[0]
                         .val)
                 << 2);
            const unsigned model_iq_iss =
                (static_cast<unsigned>(core.int_iss_fired_at(0)) << 0) |
                (static_cast<unsigned>(core.int_iss_fired_at(1)) << 1) |
                (static_cast<unsigned>(core.int_iss_fired_at(2)) << 2);
            std::fprintf(
                stderr,
                "[IQ-EDGE] c=%llu "
                "rtl(post v/s2/p1/pp=%08x/%08x/%08x/%08x "
                "recv/clear.lo=%03x/%03x iss=%x "
                "s7=u%u/b%04x/l%u%u) "
                "model(post v/s2/p1/pp=%08x/%08x/%08x/%08x "
                "start=%08x recv/clear=%08x/%08x iss=%x "
                "s7=u%u/b%04x/l%u%u)\n",
                static_cast<unsigned long long>(hook_cycle), rtl_iq_valid,
                rtl_iq_state2, rtl_iq_p1, rtl_iq_ppred,
                rtl_iq_recv_lo, rtl_iq_clear_lo, rtl_iq_iss,
                static_cast<unsigned>(
                    rtl_core.int_issue_unit.slots_7.slot_uop_uopc[0].val),
                static_cast<unsigned>(
                    rtl_core.int_issue_unit.slots_7.slot_uop_br_mask[0].val),
                static_cast<unsigned>(
                    rtl_core.int_issue_unit.slots_7.slot_uop_lrs1_rtype[0].val),
                static_cast<unsigned>(
                    rtl_core.int_issue_unit.slots_7.slot_uop_lrs2_rtype[0].val),
                model_iq_valid, model_iq_state2, model_iq_p1,
                model_iq_ppred,
                static_cast<unsigned>(core.int_iq_start_valid),
                static_cast<unsigned>(core.omir.int_iq_recv_now),
                static_cast<unsigned>(core.omir.int_iq_clear_now),
                model_iq_iss,
                static_cast<unsigned>(core.int_iq.slot[7].uop.uopc),
                static_cast<unsigned>(core.int_iq.slot[7].uop.br_mask),
                static_cast<unsigned>(core.int_iq.slot[7].uop.lrs1_rtype),
                static_cast<unsigned>(core.int_iq.slot[7].uop.lrs2_rtype));
            std::fprintf(
                stderr,
                "[ROB-PORT] c=%llu "
                "rtl(idx=%u/%u/%u b=%u/%u/%u u=%llx/%llx/%llx h=%u t=%u) "
                "model(idx=%u/%u/%u b=%u/%u/%u u=%llx/%llx/%llx h=%u t=%u "
                "now=ll%u:%u ir%u:%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ll_wbarb$io_out_bits_uop_rob_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$jmp_unit$io_iresp_bits_uop_rob_idx[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$row_idx_2[0]
                        .val << 2),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r3[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r4[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r5[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_uop$r2[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_uop$r3[0]
                        .val),
                static_cast<unsigned long long>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_uop$r4[0]
                        .val),
                static_cast<unsigned>(rtl_core.rob.rob_head[0].val),
                static_cast<unsigned>(rtl_core.rob.rob_tail[0].val),
                static_cast<unsigned>(core.omir.rob_read_uop_now[0].rob_idx),
                static_cast<unsigned>(core.omir.rob_read_uop_now[1].rob_idx),
                static_cast<unsigned>(core.omir.rob_read_uop_now[2].rob_idx),
                static_cast<unsigned>(core.omir.rob_read_bsy_now[0]),
                static_cast<unsigned>(core.omir.rob_read_bsy_now[1]),
                static_cast<unsigned>(core.omir.rob_read_bsy_now[2]),
                static_cast<unsigned long long>(chisa::boom_system::pack_rob_uop(
                    core.omir.rob_read_uop_now[0])),
                static_cast<unsigned long long>(chisa::boom_system::pack_rob_uop(
                    core.omir.rob_read_uop_now[1])),
                static_cast<unsigned long long>(chisa::boom_system::pack_rob_uop(
                    core.omir.rob_read_uop_now[2])),
                static_cast<unsigned>(core.rob.head),
                static_cast<unsigned>(core.rob.tail),
                static_cast<unsigned>(core.omir.ll_now_v),
                static_cast<unsigned>(core.omir.ll_now_rob),
                static_cast<unsigned>(core.omir.iresp_now_v),
                static_cast<unsigned>(core.omir.iresp_now_rob));
#endif
          }
#endif  // CHISA_LEGACY_CORE_DIAG
#if defined(CHISA_LEGACY_CORE_DIAG)  // TAGE write audit over the previous predictor component
          if (chisa_tage_audit_cycle(hook_cycle)) {
            const auto& rtl = hook_dut.ldut.tile_prci_domain.tile_reset_domain
                                  .boom_tile.frontend.bpd.banked_predictors_0
                                  .components_1;
            const auto& model_table =
                model.frontend().tage_for_diagnostic().table(0);
            const auto& tx = model_table.last_counter_write();
            const unsigned rtl_mask =
                (rtl.REG_12[0].val << 0) | (rtl.REG_18[0].val << 1) |
                (rtl.REG_24[0].val << 2) | (rtl.REG_30[0].val << 3);
            const unsigned rtl_taken =
                (rtl.REG_13[0].val << 0) | (rtl.REG_19[0].val << 1) |
                (rtl.REG_25[0].val << 2) | (rtl.REG_31[0].val << 3);
            const unsigned rtl_alloc =
                (rtl.REG_14[0].val << 0) | (rtl.REG_20[0].val << 1) |
                (rtl.REG_26[0].val << 2) | (rtl.REG_32[0].val << 3);
            const std::array<unsigned, 4> rtl_old{
                static_cast<unsigned>(rtl.REG_15[0].val),
                static_cast<unsigned>(rtl.REG_21[0].val),
                static_cast<unsigned>(rtl.REG_27[0].val),
                static_cast<unsigned>(rtl.REG_33[0].val)};
            const std::array<unsigned, 4> rtl_next{
                static_cast<unsigned>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_wdata_0_ctr[0].val),
                static_cast<unsigned>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_wdata_1_ctr[0].val),
                static_cast<unsigned>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_wdata_2_ctr[0].val),
                static_cast<unsigned>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_wdata_3_ctr[0].val)};
            unsigned model_mask = 0;
            unsigned model_taken = 0;
            unsigned model_alloc = 0;
            for (std::size_t slot = 0; slot < 4; ++slot) {
              model_mask |= static_cast<unsigned>(tx.input.mask[slot]) << slot;
              model_taken |= static_cast<unsigned>(tx.input.taken[slot]) << slot;
              model_alloc |= static_cast<unsigned>(tx.input.alloc[slot]) << slot;
            }
            std::fprintf(
                stderr,
                "[TAGE-TXN] c=%llu active rtl/model=%u/%u "
                "mask=%x/%x taken=%x/%x alloc=%x/%x "
                "idx=%u/%u tag=%u/%u bypass=%u:%u/%u:%u "
                "old=[%u,%u,%u,%u]/[%u,%u,%u,%u] "
                "next=[%u,%u,%u,%u]/[%u,%u,%u,%u]\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$_T_211[0].val),
                static_cast<unsigned>(tx.active), rtl_mask, model_mask,
                rtl_taken, model_taken, rtl_alloc, model_alloc,
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_idx[0].val),
                static_cast<unsigned>(tx.index),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$update_tag[0].val),
                static_cast<unsigned>(tx.tag),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$wrbypass_hit[0].val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$bpd$banked_predictors_0$components_1$tables_0$wrbypass_hit_idx[0].val),
                static_cast<unsigned>(tx.bypass_hit),
                static_cast<unsigned>(tx.bypass_hit_index), rtl_old[0],
                rtl_old[1], rtl_old[2], rtl_old[3],
                static_cast<unsigned>(tx.input.old_ctr[0]),
                static_cast<unsigned>(tx.input.old_ctr[1]),
                static_cast<unsigned>(tx.input.old_ctr[2]),
                static_cast<unsigned>(tx.input.old_ctr[3]), rtl_next[0],
                rtl_next[1], rtl_next[2], rtl_next[3],
                static_cast<unsigned>(tx.next_ctr[0]),
                static_cast<unsigned>(tx.next_ctr[1]),
                static_cast<unsigned>(tx.next_ctr[2]),
                static_cast<unsigned>(tx.next_ctr[3]));
          }
#endif  // CHISA_LEGACY_CORE_DIAG
          if (observer.capture_cycle(hook_cycle) &&
              chisa_boundary_audit_cycle(hook_cycle) && !seam_reported) {
          // Compare the decision made at the LSU/D-cache boundary before
          // looking at downstream ROB/IQ consequences.  All RTL values here
          // are live lowered combinational wires (or registers referenced by
          // those wires); the model side is the cycle-start decision that was
          // actually consumed by BackendState on this step.
          {
            const auto& dcache =
                hook_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile
                    .dcache;
            const auto& md = model.last_dcache_candidate();
            const auto& completion =
                model.last_memory_completion_boundary();
            const bool rtl_s2_valid = rtl_dcache_pre.s2_valid;
            [[maybe_unused]] const bool rtl_hit =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$s2_hit_0[0]
                    .val != 0;
            [[maybe_unused]] const bool rtl_block =
                rtl_s2_valid &&
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$io_block_hit_0[0]
                        .val !=
                    0;
            [[maybe_unused]] const bool rtl_probe =
                rtl_s2_valid && dcache.s2_type[0].val != 0 &&
                dcache.s2_nack_hit_0[0].val != 0;
            [[maybe_unused]] const bool rtl_victim =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$s2_nack_victim_0[0]
                    .val != 0;
            [[maybe_unused]] const bool rtl_wb =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$s2_nack_wb_0[0]
                    .val != 0;
            const bool rtl_resp =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_valid[0]
                    .val != 0;
            const bool rtl_resp_is_hella =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_is_hella[0]
                    .val != 0;
            const bool rtl_nack =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_nack_0_valid[0]
                    .val != 0;
            const bool rtl_ready =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_req_ready[0]
                    .val != 0;
            const std::uint64_t rtl_resp_data =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_data[0]
                    .val;
            const auto& hella = model.backend().last_hella_outputs();
            const bool rtl_hella_response =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_hellacache_resp_valid[0]
                    .val != 0;
            // The RTL D-cache output is a merged producer: normal LSU/IOMSHR
            // completions and Hella/PTW completions share io_lsu_resp.  The
            // model deliberately routes Hella traffic around the ordinary
            // LSU completion boundary, so reconstruct that same merged face
            // before comparing it.  Comparing rtl_resp directly with
            // completion.response drops every valid PTW response and reports
            // a false boundary split.
            const bool model_merged_resp =
                (md.response.valid && md.response.is_hella) ||
                completion.response.valid;
            const bool model_merged_nack =
                (md.nack.valid && md.nack.is_hella) ||
                completion.nack.valid;
            const bool model_resp_is_hella =
                md.response.valid && md.response.is_hella;
            // Declare what the consumers actually sample. ready/valid/nack
            // are events. PTW.scala unconditionally registers resp.bits.data,
            // so that payload is live even while resp.valid is low. Keeping
            // the rules in one ordered contract prevents a convenient valid
            // gate from hiding the earliest causal split.
            [[maybe_unused]] const auto dcache_seam = first_seam_mismatch({
                SeamSignal::event("dcache.req.ready", rtl_ready,
                                  md.request_ready),
                SeamSignal::event("dcache.resp.valid", rtl_resp,
                                  model_merged_resp),
                SeamSignal::event("dcache.resp.is_hella",
                                  rtl_resp && rtl_resp_is_hella,
                                  model_resp_is_hella),
                SeamSignal::event("dcache.nack.valid", rtl_nack,
                                  model_merged_nack),
                SeamSignal::event("hella.resp.valid", rtl_hella_response,
                                  hella.response.valid),
                SeamSignal::sampled_payload(
                    "dcache.resp.data->ptw", rtl_resp_data,
                    model.last_lsu_resp_data(), 64),
            });
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
            if (dcache_seam &&
                dcache_seam->rule == SeamRule::kSampledPayload) {
              seam_reported = true;
              boundary_mismatch = true;
              const auto& model_dcache =
                  model.memory().dcache_for_diagnostic();
              const auto& model_bus_s2 = model_dcache.bus_s2_oracle();
              std::fprintf(
                  stderr,
                  "[SEAM first-sampled-payload-divergence] c=%llu "
                  "dcache->ptw.data rtl=%016llx model=%016llx "
                  "rtl(cache-v=%u resp-v=%u s2-v/send=%u/%u "
                  "addr=%010llx cmd/size/sign=%u/%u/%u way=%x "
                  "respq=%016llx) "
                  "model(cache-v=%u resp-v=%u s2-v/send=%u/%u "
                  "addr=%010llx cmd/size/sign=%u/%u/%u way=%x "
                  "respq=%016llx datareg=%016llx/%016llx/%016llx/%016llx)\n",
                  static_cast<unsigned long long>(hook_cycle),
                  static_cast<unsigned long long>(rtl_resp_data),
                  static_cast<unsigned long long>(model.last_lsu_resp_data()),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$cache_resp_0_valid[0]
                          .val),
                  static_cast<unsigned>(rtl_resp),
                  static_cast<unsigned>(rtl_s2_valid),
                  static_cast<unsigned>(dcache.REG_15[0].val),
                  static_cast<unsigned long long>(dcache.s2_req_0_addr[0].val),
                  static_cast<unsigned>(dcache.s2_req_0_uop_mem_cmd[0].val),
                  static_cast<unsigned>(dcache.s2_req_0_uop_mem_size[0].val),
                  static_cast<unsigned>(dcache.s2_req_0_uop_mem_signed[0].val),
                  static_cast<unsigned>(dcache.s2_tag_match_way_0[0].val),
                  static_cast<unsigned long long>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$respq$ram_data$MPORT_1[0]
                          .val),
                  static_cast<unsigned>(
                      model_dcache.s2_valid_oracle() &&
                      model_dcache.s2_send_shadow_oracle()),
                  static_cast<unsigned>(completion.response.valid),
                  static_cast<unsigned>(model_dcache.s2_valid_oracle()),
                  static_cast<unsigned>(model_dcache.s2_send_shadow_oracle()),
                  static_cast<unsigned long long>(model_bus_s2.address),
                  static_cast<unsigned>(model_bus_s2.command),
                  static_cast<unsigned>(model_bus_s2.size),
                  static_cast<unsigned>(model_bus_s2.is_signed),
                  static_cast<unsigned>(
                      model_dcache.s2_tag_match_way_oracle()),
                  static_cast<unsigned long long>(
                      model_dcache.respq_head_data_oracle()),
                  static_cast<unsigned long long>(
                      model_dcache.oracle_data_reg(0)),
                  static_cast<unsigned long long>(
                      model_dcache.oracle_data_reg(1)),
                  static_cast<unsigned long long>(
                      model_dcache.oracle_data_reg(2)),
                  static_cast<unsigned long long>(
                      model_dcache.oracle_data_reg(3)));
              return;
            }
#endif  // small-tap diagnostics
            // Internal s2 occupancy is intentionally not itself a boundary
            // contract: an MSHR response can win the output while stale s2
            // payloads remain visible.  Trigger only when the LSU can observe
            // a different ready/response/nack decision; print the internal
            // reason bits merely to classify that real event difference.
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
            if (dcache_seam) {
              seam_reported = true;
              boundary_mismatch = true;
              const auto& model_dcache =
                  model.memory().dcache_for_diagnostic();
              std::fprintf(
                  stderr,
                  "[SEAM first-boundary-divergence] c=%llu %s rule=%s "
                  "rtl=%llx model=%llx dcache-decision "
                  "rtl(ready=%u v/send/h/block/probe/victim/wb/resp/nack="
                  "%u/%u/%u/%u/%u/%u/%u/%u/%u addr=%010llx type=%u "
                  "sec=%u miss/no-rdy=%u/%u mshr=%u/%u) "
                  "model(src=%s raw-resp/hella=%u/%u merged=%u "
                  "candidate-resp/nack=%u/%u hella-out=%u ready=%u "
                  "f-v/ctl-v/f-send/ctl-send="
                  "%u/%u/%u/%u h/block/probe/victim/wb/resp/nack="
                  "%u/%u/%u/%u/%u/%u/%u set=%u "
                  "kill rtl(br/flush/s2mask)=%02x/%u/%02x "
                  "model(resp-br/resp-flush/nack-br/nack-flush)="
                  "%u/%u/%u/%u next-ctl rtl/model=%u/%u "
                  "mshr=%u/%u req=%010llx/%010llx way=%x/%x\n",
                  static_cast<unsigned long long>(hook_cycle),
                  dcache_seam->name, seam_rule_name(dcache_seam->rule),
                  static_cast<unsigned long long>(dcache_seam->rtl),
                  static_cast<unsigned long long>(dcache_seam->model),
                  static_cast<unsigned>(rtl_ready),
                  static_cast<unsigned>(rtl_s2_valid),
                  static_cast<unsigned>(rtl_dcache_pre.s2_send),
                  static_cast<unsigned>(rtl_hit),
                  static_cast<unsigned>(rtl_block),
                  static_cast<unsigned>(rtl_probe),
                  static_cast<unsigned>(rtl_victim),
                  static_cast<unsigned>(rtl_wb),
                  static_cast<unsigned>(rtl_resp),
                  static_cast<unsigned>(rtl_nack),
                  static_cast<unsigned long long>(
                      rtl_dcache_pre.s2_address),
                  static_cast<unsigned>(rtl_dcache_pre.s2_type),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$io_secondary_miss_0[0]
                          .val),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$_T_355[0]
                          .val),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$_T_356[0]
                          .val),
                  static_cast<unsigned>(rtl_dcache_pre.mshr0_state),
                  static_cast<unsigned>(rtl_dcache_pre.mshr1_state),
                  backend_completion_source_name(completion.source),
                  static_cast<unsigned>(md.response.valid),
                  static_cast<unsigned>(md.response.is_hella),
                  static_cast<unsigned>(model_merged_resp),
                  static_cast<unsigned>(
                      completion.candidate_response.valid),
                  static_cast<unsigned>(completion.candidate_nack.valid),
                  static_cast<unsigned>(hella.response.valid),
                  static_cast<unsigned>(md.request_ready),
                  static_cast<unsigned>(md.s2_valid),
                  static_cast<unsigned>(md.s2_control_valid),
                  static_cast<unsigned>(md.s2_send_response),
                  static_cast<unsigned>(md.s2_control_send_response),
                  static_cast<unsigned>(md.s2_hit),
                  static_cast<unsigned>(md.s2_block_hit),
                  static_cast<unsigned>(md.s2_nack_probe),
                  static_cast<unsigned>(md.s2_nack_victim),
                  static_cast<unsigned>(md.s2_nack_writeback),
                  static_cast<unsigned>(completion.response.valid),
                  static_cast<unsigned>(completion.nack.valid),
                  static_cast<unsigned>(md.s2_nack_set_conflict),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_lsu_brupdate_b1_mispredict_mask[0]
                          .val),
                  static_cast<unsigned>(rtl_dcache_pre.flush),
                  static_cast<unsigned>(rtl_dcache_pre.s2_br_mask),
                  static_cast<unsigned>(
                      completion.response_branch_killed),
                  static_cast<unsigned>(
                      completion.response_flush_killed),
                  static_cast<unsigned>(
                      completion.nack_branch_killed),
                  static_cast<unsigned>(
                      completion.nack_flush_killed),
                  static_cast<unsigned>(
                      _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$REG_3$next[0]
                          .val),
                  static_cast<unsigned>(model_dcache.s2_valid_oracle()),
                  static_cast<unsigned>(md.mshr_state[0]),
                  static_cast<unsigned>(md.mshr_state[1]),
                  static_cast<unsigned long long>(
                      model_dcache.mshr_for_diagnostic(0).request.address),
                  static_cast<unsigned long long>(
                      model_dcache.mshr_for_diagnostic(1).request.address),
                  static_cast<unsigned>(
                      model_dcache.mshr_for_diagnostic(0).way_en),
                  static_cast<unsigned>(
                      model_dcache.mshr_for_diagnostic(1).way_en));
              return;
            }
#endif  // small-tap diagnostics
          }
          // TLB requestors and PTW are three independently stateful pieces.
          // Audit the exact pre-edge Decoupled contract so a missed walk is
          // reported on the accepting edge, one cycle before PTW registers
          // become the first mismatching manifest streams.
          {
            const auto& mp = model.last_ptw_boundary();
            const bool rtl_dreq =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_ptw_req_valid[0]
                    .val != 0;
            const bool rtl_dtlb_lookup_valid =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_valid[0]
                    .val != 0;
            const std::uint64_t rtl_dtlb_vaddr =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_bits_vaddr[0]
                    .val;
            const bool rtl_dtlb_passthrough =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_bits_passthrough[0]
                    .val != 0;
            const std::uint8_t rtl_dtlb_size =
                static_cast<std::uint8_t>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_bits_size[0]
                        .val);
            const bool rtl_dtlb_kill =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_kill[0]
                    .val != 0;
            const bool rtl_dtlb_sfence =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_sfence_valid[0]
                    .val != 0;
            const bool rtl_dtlb_vm =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$vm_enabled_0[0]
                    .val != 0;
            const std::uint8_t rtl_dtlb_state_next =
                static_cast<std::uint8_t>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$state$next[0]
                        .val);
            const bool rtl_dpayload =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_ptw_req_bits_valid[0]
                    .val != 0;
            const bool rtl_ireq =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$tlb$io_ptw_req_valid[0]
                    .val != 0;
            const bool rtl_out_ready =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$arb$io_out_ready[0]
                    .val != 0;
            const bool rtl_i_ready =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$arb$io_in_1_ready[0]
                    .val != 0;
            const bool rtl_arb_valid =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$arb$io_out_valid[0]
                    .val != 0;
            const bool rtl_arb_payload =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$arb$io_out_bits_valid[0]
                    .val != 0;
            const std::uint32_t rtl_arb_vpn =
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$arb$io_out_bits_bits_addr[0]
                    .val;
            const std::uint8_t rtl_ptw_state_next =
                static_cast<std::uint8_t>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$ptw$state$next[0]
                        .val);

            const auto& drequest = mp.requestors[0];
            const auto& irequest = mp.requestors[1];
            const auto& crequest = mp.requestors[2];
            const bool model_arb_valid =
                drequest.valid || irequest.valid || crequest.valid;
            const auto& selected = drequest.valid
                                       ? drequest
                                       : irequest.valid ? irequest : crequest;
            const std::uint8_t model_ptw_state_next =
                static_cast<std::uint8_t>(model.fabric().ptw_oracles()[22]);
            const std::uint8_t model_dtlb_state_next =
                static_cast<std::uint8_t>(model.dtlb().state());
            const auto& mdi = mp.dtlb_input;
            const auto ptw_seam = first_seam_mismatch({
                SeamSignal::event("dtlb.state.pre", rtl_dtlb_state_pre,
                                  mp.dtlb_state, 2),
                SeamSignal::event("dtlb.vm-enabled", rtl_dtlb_vm,
                                  mdi.vm_enabled),
                SeamSignal::valid_payload(
                    "dtlb.lookup.valid", rtl_dtlb_lookup_valid,
                    mdi.request_valid, 1, rtl_dtlb_vm, mdi.vm_enabled),
                SeamSignal::valid_payload(
                    "dtlb.lookup.vaddr", rtl_dtlb_vaddr,
                    mdi.virtual_address, 40, rtl_dtlb_lookup_valid,
                    mdi.request_valid),
                SeamSignal::valid_payload(
                    "dtlb.lookup.passthrough", rtl_dtlb_passthrough,
                    mdi.passthrough, 1,
                    rtl_dtlb_lookup_valid && rtl_dtlb_vm,
                    mdi.request_valid && mdi.vm_enabled),
                SeamSignal::valid_payload(
                    "dtlb.lookup.size", rtl_dtlb_size,
                    model.last_dtlb().candidate_size, 2,
                    rtl_dtlb_lookup_valid, mdi.request_valid),
                SeamSignal::event("dtlb.kill", rtl_dtlb_kill, mdi.kill),
                SeamSignal::event("dtlb.sfence", rtl_dtlb_sfence,
                                  mdi.sfence.valid),
                SeamSignal::event("dtlb.refill.valid", rtl_dtlb_refill_pre,
                                  mdi.refill.valid),
                SeamSignal::event("dtlb.state.next", rtl_dtlb_state_next,
                                  model_dtlb_state_next, 2),
                SeamSignal::event("ptw.state.pre", rtl_ptw_state_pre,
                                  mp.state, 3),
                SeamSignal::event("ptw.dtlb.req.valid", rtl_dreq,
                                  drequest.valid),
                SeamSignal::valid_payload(
                    "ptw.dtlb.req.payload-valid", rtl_dpayload,
                    drequest.payload_valid, 1, rtl_dreq, drequest.valid),
                SeamSignal::valid_payload(
                    "ptw.dtlb.req.vpn", rtl_dtlb_refill_tag_pre,
                    drequest.vpn, 27, rtl_dreq, drequest.valid),
                SeamSignal::event("ptw.itlb.req.valid", rtl_ireq,
                                  irequest.valid),
                SeamSignal::valid_payload(
                    "ptw.itlb.req.vpn", rtl_itlb_refill_tag_pre,
                    irequest.vpn, 27, rtl_ireq, irequest.valid),
                SeamSignal::event("ptw.arb.out.ready", rtl_out_ready,
                                  mp.request_ready[0]),
                SeamSignal::event("ptw.arb.in1.ready", rtl_i_ready,
                                  mp.request_ready[1]),
                SeamSignal::event("ptw.arb.out.valid", rtl_arb_valid,
                                  model_arb_valid),
                SeamSignal::valid_payload(
                    "ptw.arb.payload-valid", rtl_arb_payload,
                    selected.payload_valid, 1, rtl_arb_valid,
                    model_arb_valid),
                SeamSignal::valid_payload(
                    "ptw.arb.vpn", rtl_arb_vpn, selected.vpn, 27,
                    rtl_arb_valid, model_arb_valid),
                SeamSignal::event("ptw.state.next", rtl_ptw_state_next,
                                  model_ptw_state_next, 3),
            });
            if (ptw_seam) {
              seam_reported = true;
              boundary_mismatch = true;
              std::fprintf(
                  stderr,
                  "[SEAM first-ptw-boundary-divergence] c=%llu %s "
                  "rule=%s rtl=%llx model=%llx "
                  "rtl(dtlb=%u->%u lookup/vm/vaddr=%u/%u/%010llx "
                  "kill/sf/refill=%u/%u/%u ptw=%u->%u "
                  "dreq/payload/vpn=%u/%u/%07x "
                  "ireq/vpn=%u/%07x ready=%u/%u arb-v/payload/vpn="
                  "%u/%u/%07x) "
                  "model(dtlb=%u->%u lookup/vm/vaddr=%u/%u/%010llx "
                  "kill/sf/refill=%u/%u/%u ptw=%u->%u "
                  "dreq/payload/vpn=%u/%u/%07x "
                  "ireq/payload/vpn=%u/%u/%07x ready=%u/%u "
                  "arb-v/payload/vpn=%u/%u/%07x)\n",
                  static_cast<unsigned long long>(hook_cycle),
                  ptw_seam->name, seam_rule_name(ptw_seam->rule),
                  static_cast<unsigned long long>(ptw_seam->rtl),
                  static_cast<unsigned long long>(ptw_seam->model),
                  static_cast<unsigned>(rtl_dtlb_state_pre),
                  static_cast<unsigned>(rtl_dtlb_state_next),
                  static_cast<unsigned>(rtl_dtlb_lookup_valid),
                  static_cast<unsigned>(rtl_dtlb_vm),
                  static_cast<unsigned long long>(rtl_dtlb_vaddr),
                  static_cast<unsigned>(rtl_dtlb_kill),
                  static_cast<unsigned>(rtl_dtlb_sfence),
                  static_cast<unsigned>(rtl_dtlb_refill_pre),
                  static_cast<unsigned>(rtl_ptw_state_pre),
                  static_cast<unsigned>(rtl_ptw_state_next),
                  static_cast<unsigned>(rtl_dreq),
                  static_cast<unsigned>(rtl_dpayload), rtl_dtlb_refill_tag_pre,
                  static_cast<unsigned>(rtl_ireq), rtl_itlb_refill_tag_pre,
                  static_cast<unsigned>(rtl_out_ready),
                  static_cast<unsigned>(rtl_i_ready),
                  static_cast<unsigned>(rtl_arb_valid),
                  static_cast<unsigned>(rtl_arb_payload), rtl_arb_vpn,
                  static_cast<unsigned>(mp.dtlb_state),
                  static_cast<unsigned>(model_dtlb_state_next),
                  static_cast<unsigned>(mdi.request_valid),
                  static_cast<unsigned>(mdi.vm_enabled),
                  static_cast<unsigned long long>(mdi.virtual_address),
                  static_cast<unsigned>(mdi.kill),
                  static_cast<unsigned>(mdi.sfence.valid),
                  static_cast<unsigned>(mdi.refill.valid),
                  static_cast<unsigned>(mp.state),
                  static_cast<unsigned>(model_ptw_state_next),
                  static_cast<unsigned>(drequest.valid),
                  static_cast<unsigned>(drequest.payload_valid), drequest.vpn,
                  static_cast<unsigned>(irequest.valid),
                  static_cast<unsigned>(irequest.payload_valid), irequest.vpn,
                  static_cast<unsigned>(mp.request_ready[0]),
                  static_cast<unsigned>(mp.request_ready[1]),
                  static_cast<unsigned>(model_arb_valid),
                  static_cast<unsigned>(selected.payload_valid), selected.vpn);
              return;
            }
          }
          }
          if (!observer.capture_cycle(hook_cycle) ||
              !chisa_seam_audit_cycle(hook_cycle) || seam_reported)
            return;
          // One compact exception-conveyor flight record.  `mem_xcpt_*` is
          // the registered event consumed on this edge; ma/pf/ae are the
          // current combinational sources captured for the following edge.
          // Keeping both faces in one run avoids guessing whether a dead LSQ
          // payload write came from misalignment, translation, or access
          // permission logic.
          if (chisa_mw_debug_cycle(hook_cycle)) std::fprintf(
              stderr,
              "[SEAM xcpt-edge] c=%llu pending(v=%u ld=%u stq=%u rob=%u) "
              "capture(ma=%u/%u pf=%u/%u ae=%u/%u req=%u vaddr=%010llx)\n",
              static_cast<unsigned long long>(hook_cycle),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem_xcpt_valids_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem_xcpt_uops_0_uses_ldq[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem_xcpt_uops_0_stq_idx[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem_xcpt_uops_0_rob_idx[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ma_ld_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ma_st_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$pf_ld_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$pf_st_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ae_ld_0[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_resp_0_ae_st[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_valid[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$exe_tlb_vaddr_0[0]
                      .val));
#if defined(CHISA_LEGACY_CORE_DIAG)  // seam audit over the previous core model
          const std::uint8_t rtl_in =
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_0$io_in_uop_valid[0].val << 0) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_1$io_in_uop_valid[0].val << 1) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_2$io_in_uop_valid[0].val << 2) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_3$io_in_uop_valid[0].val << 3) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_4$io_in_uop_valid[0].val << 4) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_5$io_in_uop_valid[0].val << 5) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_6$io_in_uop_valid[0].val << 6) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_7$io_in_uop_valid[0].val << 7);
          const std::uint8_t rtl_clear =
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_0$io_clear[0].val << 0) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_1$io_clear[0].val << 1) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_2$io_clear[0].val << 2) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_3$io_clear[0].val << 3) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_4$io_clear[0].val << 4) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_5$io_clear[0].val << 5) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_6$io_clear[0].val << 6) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_7$io_clear[0].val << 7);
          const std::uint8_t rtl_ld_miss = static_cast<std::uint8_t>(
              _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_core_ld_miss[0].val);
          const auto& core = model.backend().core();
          if (rtl_in != core.omir.int_iq_recv_now ||
              rtl_clear != core.omir.int_iq_clear_now ||
              rtl_ld_miss != core.omir.ld_miss_now) {
            seam_reported = true;
            std::fprintf(
                stderr,
                "[SEAM first-control-divergence] c=%llu int-iq-post-eval "
                "rtl(in=%02x clear=%02x ldmiss=%u) "
                "model(in=%02x clear=%02x ldmiss=%u start=%02x "
                "consumed=%u ghost=%d b1mask=%02x)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_in),
                static_cast<unsigned>(rtl_clear),
                static_cast<unsigned>(rtl_ld_miss),
                static_cast<unsigned>(core.omir.int_iq_recv_now),
                static_cast<unsigned>(core.omir.int_iq_clear_now),
                static_cast<unsigned>(core.omir.ld_miss_now),
                static_cast<unsigned>(core.int_iq_start_valid),
                static_cast<unsigned>(core.int_port_consumed),
                static_cast<int>(core.ghost_int_slot),
                static_cast<unsigned>(core.omir.b1_mispred_mask_now));
            return;
          }

          const std::uint8_t rtl_mem_in =
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_0$io_in_uop_valid[0].val << 0) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_1$io_in_uop_valid[0].val << 1) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_2$io_in_uop_valid[0].val << 2) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_3$io_in_uop_valid[0].val << 3) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_4$io_in_uop_valid[0].val << 4) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_5$io_in_uop_valid[0].val << 5) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_6$io_in_uop_valid[0].val << 6) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_7$io_in_uop_valid[0].val << 7);
          const std::uint8_t rtl_mem_clear =
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_0$io_clear[0].val << 0) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_1$io_clear[0].val << 1) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_2$io_clear[0].val << 2) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_3$io_clear[0].val << 3) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_4$io_clear[0].val << 4) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_5$io_clear[0].val << 5) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_6$io_clear[0].val << 6) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_7$io_clear[0].val << 7);
          const std::uint8_t rtl_mem_wbv =
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_0$io_will_be_valid[0].val << 0) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_1$io_will_be_valid[0].val << 1) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_2$io_will_be_valid[0].val << 2) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_3$io_will_be_valid[0].val << 3) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_4$io_will_be_valid[0].val << 4) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_5$io_will_be_valid[0].val << 5) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_6$io_will_be_valid[0].val << 6) |
              (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_7$io_will_be_valid[0].val << 7);
          const std::uint8_t rtl_mem_ready_next =
              _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$REG$next[0].val;
          if (rtl_mem_in != core.omir.mem_iq_recv_now ||
              rtl_mem_clear != core.omir.mem_iq_clear_now ||
              rtl_mem_ready_next != core.mem_iq_ready) {
            seam_reported = true;
            std::fprintf(
                stderr,
                "[SEAM first-control-divergence] c=%llu mem-iq-edge "
                "rtl(in=%02x clear=%02x wbv=%02x ready.next=%u) "
                "model(in=%02x clear=%02x ready.next=%u start=%02x "
                "consumed=%u ghost=%d partial=%d ldmiss=%u)\n",
                static_cast<unsigned long long>(hook_cycle),
                static_cast<unsigned>(rtl_mem_in),
                static_cast<unsigned>(rtl_mem_clear),
                static_cast<unsigned>(rtl_mem_wbv),
                static_cast<unsigned>(rtl_mem_ready_next),
                static_cast<unsigned>(core.omir.mem_iq_recv_now),
                static_cast<unsigned>(core.omir.mem_iq_clear_now),
                static_cast<unsigned>(core.mem_iq_ready),
                static_cast<unsigned>(core.mem_iq_start_valid),
                static_cast<unsigned>(core.mem_port_consumed),
                static_cast<int>(core.ghost_mem_slot),
                static_cast<int>(core.ghost_mem_partial_slot),
                static_cast<unsigned>(core.omir.ld_miss_now));
            return;
          }

          // Compare the actual edge result, not a downstream oracle one cycle
          // later.  These generated `$next` values are the payload written by
          // this RTL evaluation; BoomGuider has already committed the matching
          // model edge.  A difference here with matching in/clear controls is
          // therefore a payload-transform/HOLD bug, not a scheduling bug.
          const std::array<std::uint32_t, 8> rtl_mem_bank2_next = {
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_0$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_1$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_2$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_3$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_4$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_5$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_6$slot_uop__v2_bank_2_0$next[0].val),
              static_cast<std::uint32_t>(_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_7$slot_uop__v2_bank_2_0$next[0].val),
          };
          const auto pack_bank2 = [](const MicroOp& uop) {
            return (static_cast<std::uint32_t>(uop.uopc & 0x7fu) << 12) |
                   (static_cast<std::uint32_t>(uop.br_mask) << 4) |
                   (static_cast<std::uint32_t>(uop.lrs1_rtype & 3u) << 2) |
                   static_cast<std::uint32_t>(uop.lrs2_rtype & 3u);
          };
          for (std::size_t slot = 0; slot < rtl_mem_bank2_next.size(); ++slot) {
            const std::uint32_t model_next =
                pack_bank2(core.mem_iq.slot[slot].uop);
            if (rtl_mem_bank2_next[slot] == model_next) continue;
            seam_reported = true;
            const std::uint8_t rtl_grants =
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_0$io_grant[0].val << 0) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_1$io_grant[0].val << 1) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_2$io_grant[0].val << 2) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_3$io_grant[0].val << 3) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_4$io_grant[0].val << 4) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_5$io_grant[0].val << 5) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_6$io_grant[0].val << 6) |
                (_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$slots_7$io_grant[0].val << 7);
            std::fprintf(
                stderr,
                "[SEAM first-edge-divergence] c=%llu mem-iq-payload "
                "slot=%zu rtl.next=%05x model.post=%05x "
                "controls(in=%02x clear=%02x grant=%02x wbv=%02x) "
                "model(start=%02x consumed=%u ghost=%d partial=%d sel=%u "
                "sel_uopc=%u sel_lrs=%u/%u)\n",
                static_cast<unsigned long long>(hook_cycle), slot,
                static_cast<unsigned>(rtl_mem_bank2_next[slot]),
                static_cast<unsigned>(model_next),
                static_cast<unsigned>(rtl_mem_in),
                static_cast<unsigned>(rtl_mem_clear),
                static_cast<unsigned>(rtl_grants),
                static_cast<unsigned>(rtl_mem_wbv),
                static_cast<unsigned>(core.mem_iq_start_valid),
                static_cast<unsigned>(core.mem_port_consumed),
                static_cast<int>(core.ghost_mem_slot),
                static_cast<int>(core.ghost_mem_partial_slot),
                static_cast<unsigned>(core.mem_sel_now),
                static_cast<unsigned>(core.mem_sel_uop_now.uopc),
                static_cast<unsigned>(core.mem_sel_uop_now.lrs1_rtype),
                static_cast<unsigned>(core.mem_sel_uop_now.lrs2_rtype));
            return;
          }

#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
          const std::uint64_t rtl_stq_bank01_next =
              _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_1$next[0]
                  .val;
          const std::uint64_t model_stq_bank01_post = pack_stq_bank01(core);
          if (rtl_stq_bank01_next != model_stq_bank01_post) {
            seam_reported = true;
            const bool rtl_changed =
                seam_rtl_stq_bank01_pre != rtl_stq_bank01_next;
            const bool model_changed =
                seam_model_stq_bank01_pre != model_stq_bank01_post;
            std::fprintf(
                stderr,
                "[SEAM first-edge-divergence] c=%llu stq-bank01 "
                "rtl(%s pre=%016llx next=%016llx) "
                "model(%s pre=%016llx post=%016llx) xor=%016llx\n"
                "  stq1.exception rtl=%u->%u model=%u->%u "
                "rtl-edge(ld_enq=%u st_enq=%u tail=%u ren_exc=%u "
                "clear=%u b1=%02x) "
                "model-edge(dis_v=%u dis_ready=%u uses_stq=%u exc=%u "
                "tail=%d->%d)\n",
                static_cast<unsigned long long>(hook_cycle),
                rtl_changed ? "WRITE" : "HOLD",
                static_cast<unsigned long long>(seam_rtl_stq_bank01_pre),
                static_cast<unsigned long long>(rtl_stq_bank01_next),
                model_changed ? "WRITE" : "HOLD",
                static_cast<unsigned long long>(seam_model_stq_bank01_pre),
                static_cast<unsigned long long>(model_stq_bank01_post),
                static_cast<unsigned long long>(rtl_stq_bank01_next ^
                                                model_stq_bank01_post),
                static_cast<unsigned>((seam_rtl_stq_bank01_pre >> 54) & 1u),
                static_cast<unsigned>((rtl_stq_bank01_next >> 54) & 1u),
                static_cast<unsigned>((seam_model_stq_bank01_pre >> 54) & 1u),
                static_cast<unsigned>((model_stq_bank01_post >> 54) & 1u),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_52[0]
                        .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_55[0]
                        .val),
                static_cast<unsigned>(
                    hook_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile
                        .lsu.stq_tail[0]
                        .val),
                static_cast<unsigned>(hook_dut.ldut.tile_prci_domain
                                          .tile_reset_domain.boom_tile.core
                                          .rename_stage.REG_1_exception[0]
                                          .val),
                static_cast<unsigned>(
                    _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$clear_store[0]
                        .val),
                static_cast<unsigned>(core.omir.b1_mispred_mask_now),
                static_cast<unsigned>(seam_model_disp_valid_pre),
                static_cast<unsigned>(core.dis_ready),
                static_cast<unsigned>(seam_model_disp_uop_pre.uses_stq),
                static_cast<unsigned>(seam_model_disp_uop_pre.exception),
                seam_model_stq_tail_pre, core.lsu.stq_tail);
            return;
          }
#endif  // CHISA_LEGACY_CORE_DIAG
#endif  // small-tap diagnostics
        });
    uint64_t run_max_cycles = options.max_cycles;  // a resumed checkpoint child may change it
    while (stepper.cycle() < run_max_cycles) {
      const uint64_t cycle = stepper.cycle();
      if (options.checkpoint_at != 0 && cycle == options.checkpoint_at) {
        checkpoint_hook(options, run_max_cycles);
        // Checkpoint children can change sticky probe configuration. Without
        // a probe API exposing the resulting filter/skip state, only the
        // already compared prefix is known; do not certify the resumed tail.
        probe_contract_known = false;
      }
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
      if (chisa_edge_audit_cycle(cycle)) {
        edge_rtl_ren_exception_pre =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                .rename_stage.REG_1_exception[0]
                .val != 0;
        const auto& core = model.backend().core();
        edge_model_ren_exception_pre = core.ren_r_uop.exception != 0;
        const auto held = model.frontend().held_fetch(
            cycle < options.reset_cycles);
        edge_model_fetch_offered_pre = held.deq_valid && held.uop_valid;
        edge_model_fetch_pre = held.uop;
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
        edge_rtl_ftq_get1_addr_pre = static_cast<std::uint8_t>(
            (dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$ftq$ghist__v2_bank_0_0[0]
                 .val >>
             15) &
            0x1fu);
        edge_model_f3_prev_half_pre =
            model.frontend().f3_assembler_for_diagnostic().prev_half();
        edge_model_f3_prev_is_half_pre =
            model.frontend().f3_assembler_for_diagnostic().prev_is_half();
        const auto& edge_model_frontend = model.frontend();
        const auto& edge_model_f4 =
            edge_model_frontend.f4_queue_for_diagnostic();
        const auto& edge_model_f4_payload = edge_model_f4.payload();
        const auto& edge_model_fb =
            edge_model_frontend.fetch_buffer_for_diagnostic();
        const auto edge_model_ftq =
            edge_model_frontend.ftq_for_diagnostic().outputs({});
        edge_model_frontend_pre.f4_full = edge_model_f4.full();
        edge_model_frontend_pre.f4_pc = edge_model_f4_payload.pc;
        edge_model_frontend_pre.f4_mask = edge_model_f4_payload.mask;
        edge_model_frontend_pre.f4_sfb_mask = edge_model_f4_payload.sfb_mask;
        edge_model_frontend_pre.f4_cfi_valid =
            edge_model_f4_payload.cfi_valid;
        edge_model_frontend_pre.f4_cfi_idx = edge_model_f4_payload.cfi_idx;
        edge_model_frontend_pre.fb_head = edge_model_fb.head();
        edge_model_frontend_pre.fb_tail = edge_model_fb.tail();
        edge_model_frontend_pre.fb_maybe_full = edge_model_fb.maybe_full();
        edge_model_frontend_pre.ftq_enq_ready = edge_model_ftq.enq_ready;
        edge_model_frontend_pre.ftq_enq_idx = edge_model_ftq.enq_idx;
        const auto& edge_model_icache =
            edge_model_frontend.icache_for_diagnostic();
        edge_model_frontend_pre.ic_s1_valid = edge_model_icache.s1_valid();
        edge_model_frontend_pre.ic_s2_valid = edge_model_icache.s2_valid();
        edge_model_frontend_pre.ic_s2_hit = edge_model_icache.s2_hit();
        edge_model_frontend_pre.ic_refill_valid =
            edge_model_icache.refill_valid();
        edge_model_frontend_pre.ic_refill_paddr =
            edge_model_icache.refill_paddr();
        edge_model_frontend_pre.ic_tag_read_set =
            edge_model_icache.tag_read_set();
#endif
      }
#endif  // CHISA_LEGACY_CORE_DIAG
      const bool dcport_debug = chisa_dcport_debug_cycle(cycle);
      const bool measurement_active = observer.capture_cycle(cycle);
      [[maybe_unused]] const bool seam_audit =
          measurement_active && chisa_seam_audit_cycle(cycle);
      [[maybe_unused]] const bool boundary_audit =
          measurement_active && chisa_boundary_audit_cycle(cycle);
      std::uint16_t rtl_dc_addr3_pre = 0;
      std::uint16_t model_dc_addr3_pre = 0;
      std::uint64_t model_dc_port3_pre = 0;
      std::uint8_t rtl_mshr1_pre = 0;
      std::uint8_t model_mshr1_pre = 0;
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
      if (chisa_state_audit_cycle(cycle) && !state_audit_reported) {
        const auto& core = model.backend().core();
        const auto& rtl_core =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core;
        const auto& rtl_lsu =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu;

        const std::uint8_t rtl_rob_head = rtl_core.rob.rob_head[0].val;
        const std::uint8_t rtl_rob_tail = rtl_core.rob.rob_tail[0].val;
        const std::uint8_t model_rob_head = core.rob.head & 31;
        const std::uint8_t model_rob_tail = core.rob.tail & 31;
        const std::uint32_t rtl_rob_val =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_bitset_rob_val_bank_0[0]
                .val;
        std::uint32_t model_rob_val = 0;
        std::uint32_t rtl_rob_busy = 0;
        std::uint32_t model_rob_busy = 0;
        std::uint32_t rtl_rob_unsafe = 0;
        std::uint32_t model_rob_unsafe = 0;
        std::uint32_t rtl_rob_exception = 0;
        std::uint32_t model_rob_exception = 0;
        for (unsigned row = 0; row < 32; ++row) {
          model_rob_val |= static_cast<std::uint32_t>(core.rob.val[row]) << row;
          rtl_rob_busy |= static_cast<std::uint32_t>(
                              rtl_core.rob.__v2_state_rob_bsy[row].val)
                          << row;
          model_rob_busy |=
              static_cast<std::uint32_t>(core.rob.busy[row]) << row;
          rtl_rob_unsafe |= static_cast<std::uint32_t>(
                                rtl_core.rob.__v2_state_rob_unsafe[row].val)
                            << row;
          model_rob_unsafe |=
              static_cast<std::uint32_t>(core.rob.unsafe[row]) << row;
          rtl_rob_exception |= static_cast<std::uint32_t>(
                                   rtl_core.rob.__v2_state_rob_exception[row]
                                       .val)
                               << row;
          model_rob_exception |=
              static_cast<std::uint32_t>(core.rob.exception[row]) << row;
        }
        const std::uint32_t rob_live = rtl_rob_val & model_rob_val;
        const std::uint32_t rob_val_diff = rtl_rob_val ^ model_rob_val;
        const std::uint32_t rob_busy_diff =
            (rtl_rob_busy ^ model_rob_busy) & rob_live;
        const std::uint32_t rob_unsafe_diff =
            (rtl_rob_unsafe ^ model_rob_unsafe) & rob_live;
        const std::uint32_t rob_exception_diff =
            (rtl_rob_exception ^ model_rob_exception) & rob_live;

        const std::uint64_t rtl_ldq_bank0 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_0_0[0]
                .val;
        std::uint8_t rtl_ldq_valid = 0;
        std::uint8_t rtl_ldq_addr_valid = 0;
        std::uint8_t rtl_ldq_executed = 0;
        std::uint8_t model_ldq_valid = 0;
        std::uint8_t model_ldq_addr_valid = 0;
        std::uint8_t model_ldq_executed = 0;
        std::uint8_t model_ldq_succeeded = 0;
        for (unsigned slot = 0; slot < 8; ++slot) {
          const unsigned valid_bit = 23 - 3 * slot;
          rtl_ldq_valid |= ((rtl_ldq_bank0 >> valid_bit) & 1u) << slot;
          rtl_ldq_addr_valid |=
              ((rtl_ldq_bank0 >> (valid_bit - 1)) & 1u) << slot;
          rtl_ldq_executed |=
              ((rtl_ldq_bank0 >> (valid_bit - 2)) & 1u) << slot;
          model_ldq_valid |=
              static_cast<std::uint8_t>(core.lsu.ldq[slot].valid) << slot;
          model_ldq_addr_valid |=
              static_cast<std::uint8_t>(core.lsu.ldq[slot].addr_valid) << slot;
          model_ldq_executed |=
              static_cast<std::uint8_t>(core.lsu.ldq[slot].executed) << slot;
          model_ldq_succeeded |=
              static_cast<std::uint8_t>(core.lsu.ldq[slot].succeeded) << slot;
        }
        const std::uint64_t rtl_ldq_bank10 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_1_0[0]
                .val;
        const std::uint64_t rtl_ldq_bank11 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_1_1[0]
                .val;
        const std::uint64_t rtl_ldq_bank12 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_1_2[0]
                .val;
        const std::uint64_t rtl_ldq_bank13 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_1_3[0]
                .val;
        const std::uint64_t rtl_ldq_pointer_bank =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq__v2_bank_15_2[0]
                .val;
        const std::uint8_t rtl_ldq_head =
            (rtl_ldq_pointer_bank >> 3) & 7u;
        const std::uint8_t rtl_ldq_tail = rtl_ldq_pointer_bank & 7u;
        const std::uint8_t rtl_ldq_succeeded =
            (((rtl_ldq_bank10 >> 45) & 1u) << 0) |
            (((rtl_ldq_bank10 >> 19) & 1u) << 1) |
            (((rtl_ldq_bank11 >> 54) & 1u) << 2) |
            (((rtl_ldq_bank11 >> 28) & 1u) << 3) |
            (((rtl_ldq_bank11 >> 2) & 1u) << 4) |
            (((rtl_ldq_bank12 >> 37) & 1u) << 5) |
            (((rtl_ldq_bank12 >> 11) & 1u) << 6) |
            (((rtl_ldq_bank13 >> 17) & 1u) << 7);
        const std::uint8_t ldq_live = rtl_ldq_valid & model_ldq_valid;
        const std::uint8_t ldq_valid_diff =
            rtl_ldq_valid ^ model_ldq_valid;
        const std::uint8_t ldq_addr_diff =
            (rtl_ldq_addr_valid ^ model_ldq_addr_valid) & ldq_live;
        const std::uint8_t ldq_executed_diff =
            (rtl_ldq_executed ^ model_ldq_executed) & ldq_live;
        const std::uint8_t ldq_succeeded_diff =
            (rtl_ldq_succeeded ^ model_ldq_succeeded) & ldq_live;

        const std::array<std::uint64_t, 6> rtl_stq_banks = {
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_0[0].val,
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_1[0].val,
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_2[0].val,
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_3[0].val,
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_4[0].val,
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_5[0].val};
        constexpr std::array<unsigned, 8> stq_valid_bank = {0, 0, 1, 2,
                                                             2, 3, 4, 4};
        constexpr std::array<unsigned, 8> stq_valid_bit = {61, 16, 35, 53,
                                                            8, 26, 45, 0};
        constexpr std::array<unsigned, 8> stq_status_bank = {0, 1, 2, 2,
                                                              3, 4, 4, 5};
        constexpr std::array<unsigned, 8> stq_addr_bit = {20, 39, 57, 12,
                                                           30, 49, 4, 16};
        // Slot 7 additionally packs addr_is_virtual between addr_valid and
        // data_valid; the other seven layouts are contiguous here.
        constexpr std::array<unsigned, 8> stq_data_bit = {19, 38, 56, 11,
                                                           29, 48, 3, 14};
        std::uint8_t rtl_stq_valid = 0;
        std::uint8_t rtl_stq_addr_valid = 0;
        std::uint8_t rtl_stq_data_valid = 0;
        std::uint8_t rtl_stq_committed = 0;
        std::uint8_t rtl_stq_succeeded = 0;
        std::uint8_t model_stq_valid = 0;
        std::uint8_t model_stq_addr_valid = 0;
        std::uint8_t model_stq_data_valid = 0;
        std::uint8_t model_stq_committed = 0;
        std::uint8_t model_stq_succeeded = 0;
        for (unsigned slot = 0; slot < 8; ++slot) {
          rtl_stq_valid |=
              ((rtl_stq_banks[stq_valid_bank[slot]] >> stq_valid_bit[slot]) &
               1u)
              << slot;
          const std::uint64_t status = rtl_stq_banks[stq_status_bank[slot]];
          rtl_stq_addr_valid |= ((status >> stq_addr_bit[slot]) & 1u) << slot;
          rtl_stq_data_valid |=
              ((status >> stq_data_bit[slot]) & 1u) << slot;
          rtl_stq_committed |=
              ((status >> (stq_data_bit[slot] - 1)) & 1u) << slot;
          rtl_stq_succeeded |=
              ((status >> (stq_data_bit[slot] - 2)) & 1u) << slot;
          model_stq_valid |=
              static_cast<std::uint8_t>(core.lsu.stq[slot].valid) << slot;
          model_stq_addr_valid |=
              static_cast<std::uint8_t>(core.lsu.stq[slot].addr_valid) << slot;
          model_stq_data_valid |=
              static_cast<std::uint8_t>(core.lsu.stq[slot].data_valid) << slot;
          model_stq_committed |=
              static_cast<std::uint8_t>(core.lsu.stq[slot].committed) << slot;
          model_stq_succeeded |=
              static_cast<std::uint8_t>(core.lsu.stq[slot].succeeded) << slot;
        }
        const std::uint8_t stq_live = rtl_stq_valid & model_stq_valid;
        const std::uint8_t stq_valid_diff =
            rtl_stq_valid ^ model_stq_valid;
        const std::uint8_t stq_addr_diff =
            (rtl_stq_addr_valid ^ model_stq_addr_valid) & stq_live;
        const std::uint8_t stq_data_diff =
            (rtl_stq_data_valid ^ model_stq_data_valid) & stq_live;
        const std::uint8_t stq_committed_diff =
            (rtl_stq_committed ^ model_stq_committed) & stq_live;
        const std::uint8_t stq_succeeded_diff =
            (rtl_stq_succeeded ^ model_stq_succeeded) & stq_live;
        const std::uint8_t rtl_stq_head = (rtl_stq_banks[5] >> 9) & 7u;
        const std::uint8_t rtl_stq_commit_head =
            (rtl_stq_banks[5] >> 6) & 7u;
        const std::uint8_t rtl_stq_execute_head =
            (rtl_stq_banks[5] >> 3) & 7u;
        // stq_tail was not folded into the external state banks and remains a
        // live scalar register in the generated reference.
        const std::uint8_t rtl_stq_tail = rtl_lsu.stq_tail[0].val;

        std::uint16_t rtl_int_iq_state = 0;
        std::uint16_t rtl_mem_iq_state = 0;
        std::uint16_t model_int_iq_state = 0;
        std::uint16_t model_mem_iq_state = 0;
        std::uint8_t rtl_int_iq_p1 = 0;
        std::uint8_t rtl_int_iq_p2 = 0;
        std::uint8_t model_int_iq_p1 = 0;
        std::uint8_t model_int_iq_p2 = 0;
        std::uint8_t rtl_mem_iq_p1 = 0;
        std::uint8_t rtl_mem_iq_p2 = 0;
        std::uint8_t model_mem_iq_p1 = 0;
        std::uint8_t model_mem_iq_p2 = 0;
#define PACK_AUDIT_IQ_SLOT(I)                                            \
        do {                                                             \
          rtl_int_iq_state |=                                            \
              static_cast<std::uint16_t>(                                \
                  rtl_core.int_issue_unit.slots_##I.state[0].val & 3u)   \
              << (2 * (I));                                              \
          rtl_mem_iq_state |=                                            \
              static_cast<std::uint16_t>(                                \
                  rtl_core.mem_issue_unit.slots_##I.state[0].val & 3u)   \
              << (2 * (I));                                              \
          model_int_iq_state |=                                          \
              static_cast<std::uint16_t>(core.int_iq.slot[I].state & 3u) \
              << (2 * (I));                                              \
          model_mem_iq_state |=                                          \
              static_cast<std::uint16_t>(core.mem_iq.slot[I].state & 3u) \
              << (2 * (I));                                              \
          rtl_int_iq_p1 |=                                               \
              rtl_core.int_issue_unit.slots_##I.p1[0].val << (I);        \
          rtl_int_iq_p2 |=                                               \
              rtl_core.int_issue_unit.slots_##I.p2[0].val << (I);        \
          model_int_iq_p1 |=                                             \
              static_cast<std::uint8_t>(core.int_iq.slot[I].p1) << (I);  \
          model_int_iq_p2 |=                                             \
              static_cast<std::uint8_t>(core.int_iq.slot[I].p2) << (I);  \
          rtl_mem_iq_p1 |=                                               \
              rtl_core.mem_issue_unit.slots_##I.p1[0].val << (I);        \
          rtl_mem_iq_p2 |=                                               \
              rtl_core.mem_issue_unit.slots_##I.p2[0].val << (I);        \
          model_mem_iq_p1 |=                                             \
              static_cast<std::uint8_t>(core.mem_iq.slot[I].p1) << (I);  \
          model_mem_iq_p2 |=                                             \
              static_cast<std::uint8_t>(core.mem_iq.slot[I].p2) << (I);  \
        } while (false)
        PACK_AUDIT_IQ_SLOT(0);
        PACK_AUDIT_IQ_SLOT(1);
        PACK_AUDIT_IQ_SLOT(2);
        PACK_AUDIT_IQ_SLOT(3);
        PACK_AUDIT_IQ_SLOT(4);
        PACK_AUDIT_IQ_SLOT(5);
        PACK_AUDIT_IQ_SLOT(6);
        PACK_AUDIT_IQ_SLOT(7);
#undef PACK_AUDIT_IQ_SLOT
        std::uint8_t int_iq_live = 0;
        std::uint8_t mem_iq_live = 0;
        for (unsigned slot = 0; slot < 8; ++slot) {
          if (((rtl_int_iq_state >> (2 * slot)) & 3u) != 0 &&
              ((model_int_iq_state >> (2 * slot)) & 3u) != 0)
            int_iq_live |= 1u << slot;
          if (((rtl_mem_iq_state >> (2 * slot)) & 3u) != 0 &&
              ((model_mem_iq_state >> (2 * slot)) & 3u) != 0)
            mem_iq_live |= 1u << slot;
        }
        const std::uint8_t int_iq_p1_diff =
            (rtl_int_iq_p1 ^ model_int_iq_p1) & int_iq_live;
        const std::uint8_t int_iq_p2_diff =
            (rtl_int_iq_p2 ^ model_int_iq_p2) & int_iq_live;
        const std::uint8_t mem_iq_p1_diff =
            (rtl_mem_iq_p1 ^ model_mem_iq_p1) & mem_iq_live;
        const std::uint8_t mem_iq_p2_diff =
            (rtl_mem_iq_p2 ^ model_mem_iq_p2) & mem_iq_live;

        const bool rob_diff = rtl_rob_head != model_rob_head ||
                              rtl_rob_tail != model_rob_tail ||
                              rob_val_diff || rob_busy_diff ||
                              rob_unsafe_diff || rob_exception_diff;
        const bool ldq_diff =
            rtl_ldq_head != (core.lsu.ldq_head & 7) ||
            rtl_ldq_tail != (core.lsu.ldq_tail & 7) ||
            ldq_valid_diff || ldq_addr_diff || ldq_executed_diff ||
            ldq_succeeded_diff;
        const bool stq_diff =
            rtl_stq_head != (core.lsu.stq_head & 7) ||
            rtl_stq_tail != (core.lsu.stq_tail & 7) ||
            rtl_stq_commit_head != (core.lsu.stq_commit_head & 7) ||
            rtl_stq_execute_head != (core.lsu.stq_execute_head & 7) ||
            stq_valid_diff || stq_addr_diff || stq_data_diff ||
            stq_committed_diff || stq_succeeded_diff;
        const bool iq_diff = rtl_int_iq_state != model_int_iq_state ||
                             rtl_mem_iq_state != model_mem_iq_state ||
                             int_iq_p1_diff || int_iq_p2_diff ||
                             mem_iq_p1_diff || mem_iq_p2_diff;
        if (rob_diff || ldq_diff || stq_diff || iq_diff) {
          state_audit_reported = true;
          std::fprintf(
              stderr,
              "[STATE-AUDIT first-pre-divergence] c=%llu\n"
              "  ROB ptr(h/t)=%u/%u:%u/%u val=%08x:%08x diff=%08x "
              "live-diff(b/u/x)=%08x/%08x/%08x\n"
              "  LDQ ptr(h/t)=%u/%u:%u/%u v/a/e/s=%02x/%02x/%02x/%02x:"
              "%02x/%02x/%02x/%02x diff=%02x/%02x/%02x/%02x\n"
              "  STQ ptr(h/t/c/e)=%u/%u/%u/%u:%u/%u/%u/%u "
              "v/a/d/c/s=%02x/%02x/%02x/%02x/%02x:"
              "%02x/%02x/%02x/%02x/%02x "
              "diff=%02x/%02x/%02x/%02x/%02x\n"
              "  IQ state(i/m)=%04x/%04x:%04x/%04x "
              "live-ready-diff(i1/i2/m1/m2)=%02x/%02x/%02x/%02x\n",
              static_cast<unsigned long long>(cycle), rtl_rob_head,
              rtl_rob_tail, model_rob_head, model_rob_tail, rtl_rob_val,
              model_rob_val, rob_val_diff, rob_busy_diff, rob_unsafe_diff,
              rob_exception_diff, rtl_ldq_head,
              rtl_ldq_tail, core.lsu.ldq_head & 7,
              core.lsu.ldq_tail & 7, rtl_ldq_valid, rtl_ldq_addr_valid,
              rtl_ldq_executed, rtl_ldq_succeeded, model_ldq_valid,
              model_ldq_addr_valid, model_ldq_executed,
              model_ldq_succeeded, ldq_valid_diff, ldq_addr_diff,
              ldq_executed_diff, ldq_succeeded_diff,
              rtl_stq_head, rtl_stq_tail, rtl_stq_commit_head,
              rtl_stq_execute_head, core.lsu.stq_head & 7,
              core.lsu.stq_tail & 7, core.lsu.stq_commit_head & 7,
              core.lsu.stq_execute_head & 7, rtl_stq_valid,
              rtl_stq_addr_valid, rtl_stq_data_valid, rtl_stq_committed,
              rtl_stq_succeeded, model_stq_valid, model_stq_addr_valid,
              model_stq_data_valid, model_stq_committed,
              model_stq_succeeded, stq_valid_diff, stq_addr_diff,
              stq_data_diff, stq_committed_diff, stq_succeeded_diff,
              rtl_int_iq_state, rtl_mem_iq_state, model_int_iq_state,
              model_mem_iq_state, int_iq_p1_diff, int_iq_p2_diff,
              mem_iq_p1_diff, mem_iq_p2_diff);
        }
      }
#endif  // CHISA_LEGACY_CORE_DIAG
#endif  // small-tap diagnostics
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
      if (seam_audit) {
        const auto& rtl_iq =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                .int_issue_unit;
        std::uint16_t rtl_states = 0;
#define PACK_RTL_IQ_STATE(I)                                             \
        rtl_states |= static_cast<std::uint16_t>(                        \
                          rtl_iq.slots_##I.state[0].val & 3u)             \
                      << (2 * (I))
        PACK_RTL_IQ_STATE(0);
        PACK_RTL_IQ_STATE(1);
        PACK_RTL_IQ_STATE(2);
        PACK_RTL_IQ_STATE(3);
        PACK_RTL_IQ_STATE(4);
        PACK_RTL_IQ_STATE(5);
        PACK_RTL_IQ_STATE(6);
        PACK_RTL_IQ_STATE(7);
#undef PACK_RTL_IQ_STATE
        const auto& core = model.backend().core();
        seam_rtl_stq_bank01_pre =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq__v2_bank_0_1[0]
                .val;
        seam_model_stq_bank01_pre = pack_stq_bank01(core);
        seam_model_disp_uop_pre = core.disp_uop;
        seam_model_disp_valid_pre = core.disp_valid;
        seam_model_stq_tail_pre = core.lsu.stq_tail;
        std::uint16_t model_states = 0;
        for (int i = 0; i < core.int_iq.num_slots; ++i)
          model_states |= static_cast<std::uint16_t>(core.int_iq.slot[i].state & 3u)
                          << (2 * i);
        if (!seam_reported && rtl_states != model_states) {
          seam_reported = true;
          std::fprintf(stderr,
                       "[SEAM first-control-divergence] c=%llu int-iq-state-pre "
                       "rtl=%04x model=%04x\n",
                       static_cast<unsigned long long>(cycle),
                       static_cast<unsigned>(rtl_states),
                       static_cast<unsigned>(model_states));
        }
        if (!seam_reported) {
          const std::uint8_t rtl_prs2[3] = {
              static_cast<std::uint8_t>(
                  (dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_5$slot_uop__v2_bank_0_1[0].val >> 13) & 0x3f),
              static_cast<std::uint8_t>(
                  (dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_6$slot_uop__v2_bank_0_1[0].val >> 13) & 0x3f),
              static_cast<std::uint8_t>(
                  (dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$int_issue_unit$slots_7$slot_uop__v2_bank_0_1[0].val >> 13) & 0x3f),
          };
          const std::uint8_t model_prs2[3] = {
              core.int_iq.slot[5].uop.prs2,
              core.int_iq.slot[6].uop.prs2,
              core.int_iq.slot[7].uop.prs2,
          };
          const std::uint8_t rtl_poison =
              (rtl_iq.slots_5.p2_poisoned[0].val << 5) |
              (rtl_iq.slots_6.p2_poisoned[0].val << 6) |
              (rtl_iq.slots_7.p2_poisoned[0].val << 7);
          const std::uint8_t rtl_ready =
              (rtl_iq.slots_5.p2[0].val << 5) |
              (rtl_iq.slots_6.p2[0].val << 6) |
              (rtl_iq.slots_7.p2[0].val << 7);
          const std::uint8_t model_poison =
              (static_cast<std::uint8_t>(core.int_iq.slot[5].p2_poisoned) << 5) |
              (static_cast<std::uint8_t>(core.int_iq.slot[6].p2_poisoned) << 6) |
              (static_cast<std::uint8_t>(core.int_iq.slot[7].p2_poisoned) << 7);
          const std::uint8_t model_ready =
              (static_cast<std::uint8_t>(core.int_iq.slot[5].p2) << 5) |
              (static_cast<std::uint8_t>(core.int_iq.slot[6].p2) << 6) |
              (static_cast<std::uint8_t>(core.int_iq.slot[7].p2) << 7);
          if (rtl_prs2[0] != model_prs2[0] ||
              rtl_prs2[1] != model_prs2[1] ||
              rtl_prs2[2] != model_prs2[2] ||
              rtl_ready != model_ready ||
              rtl_poison != model_poison) {
            seam_reported = true;
            std::fprintf(
                stderr,
                "[SEAM first-control-divergence] c=%llu int-iq-cam-pre "
                "rtl(prs2=%u/%u/%u p2=%02x poison=%02x) "
                "model(prs2=%u/%u/%u p2=%02x poison=%02x)\n",
                static_cast<unsigned long long>(cycle),
                static_cast<unsigned>(rtl_prs2[0]),
                static_cast<unsigned>(rtl_prs2[1]),
                static_cast<unsigned>(rtl_prs2[2]),
                static_cast<unsigned>(rtl_ready),
                static_cast<unsigned>(rtl_poison),
                static_cast<unsigned>(model_prs2[0]),
                static_cast<unsigned>(model_prs2[1]),
                static_cast<unsigned>(model_prs2[2]),
                static_cast<unsigned>(model_ready),
                static_cast<unsigned>(model_poison));
          }
        }
      }
#endif  // CHISA_LEGACY_CORE_DIAG
      if (dcport_debug) {
        rtl_dc_addr3_pre = static_cast<std::uint16_t>(
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.data
                .array_3_0_0_MPORT_7_addr_pipe_0[0]
                .val);
        const auto& dcache = model.memory().dcache_for_diagnostic();
        model_dc_addr3_pre = dcache.oracle_data_address(3);
        model_dc_port3_pre = dcache.oracle_data_port(3);
        rtl_mshr1_pre = static_cast<std::uint8_t>(
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache
                .mshrs.mshrs_1.state[0]
                .val);
        model_mshr1_pre = static_cast<std::uint8_t>(
            dcache.mshr_for_diagnostic(1).state);
      }
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
      if (boundary_audit) {
        const auto& dcache =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache;
        rtl_dcache_pre.s2_valid = dcache.REG_3[0].val != 0;
        rtl_dcache_pre.s2_send = dcache.REG_15[0].val != 0;
        rtl_dcache_pre.s2_address = dcache.s2_req_0_addr[0].val;
        rtl_dcache_pre.s2_type =
            static_cast<std::uint8_t>(dcache.s2_type[0].val);
        rtl_dcache_pre.s2_br_mask =
            static_cast<std::uint8_t>(dcache.s2_req_0_uop_br_mask[0].val);
        rtl_dcache_pre.flush =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                .REG_30[0]
                .val != 0;
        rtl_dcache_pre.mshr0_state = static_cast<std::uint8_t>(
            dcache.mshrs.mshrs_0.state[0].val);
        rtl_dcache_pre.mshr1_state = static_cast<std::uint8_t>(
            dcache.mshrs.mshrs_1.state[0].val);
        const auto& ptw =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.ptw;
        rtl_ptw_state_pre = static_cast<std::uint8_t>(ptw.state[0].val);
        rtl_dtlb_state_pre = static_cast<std::uint8_t>(
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.dtlb
                .state[0]
                .val);
        rtl_dtlb_refill_pre = ptw.resp_valid_0[0].val != 0;
        rtl_dtlb_refill_tag_pre = static_cast<std::uint32_t>(
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.dtlb
                .r_refill_tag[0]
                .val);
        rtl_itlb_refill_tag_pre = static_cast<std::uint32_t>(
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend.tlb
                .r_refill_tag[0]
                .val);
      }
#endif  // small-tap diagnostics
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
      if (chisa_mw_debug_cycle(cycle)) {
        const auto rtl_dtm = stepper.dtm_adapter().outputs();
        const auto model_dtm_out = model_debug->outputs();
        const auto model_debug_pre =
            model.memory().debug_path_for_diagnostic().debug_hand_oracles();
        const auto model_debug_path_pre =
            model.memory().debug_path_for_diagnostic().outputs();
        const auto& model_dmi_pre = model.last_dmi();
        const auto& model_debug_manager_pre =
            model.fabric().debug_manager_inputs();
        const auto& rtl_dmi_ports =
            chisa::boom_repcut::simdtm_ports(*dut);
        const auto& rtl_debug = dut->ldut.debug_1;
        std::fprintf(
            stderr,
            "[DDBG-PRE] c=%llu dtm(r=%u/%02x/%u/%08x "
            "m=%u/%02x/%u/%08x) "
            "resp(r=%u/%08x m=%u/%08x) "
            "rtl(mask=%u ctrlr=%u sinkv=%u state=%u halt=%u resume=%u) "
            "model(mask=%llu ctrlr=%llu sinkv=%llu state=%llu busy=%u "
            "goa=%u halt=%u resume=%u mgr=%u/%u src=%u addr=%x op=%u)\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned>(rtl_dtm.req_valid),
            static_cast<unsigned>(rtl_dtm.req_addr),
            static_cast<unsigned>(rtl_dtm.req_op),
            static_cast<unsigned>(rtl_dtm.req_data),
            static_cast<unsigned>(model_dtm_out.req_valid),
            static_cast<unsigned>(model_dtm_out.req_addr),
            static_cast<unsigned>(model_dtm_out.req_op),
            static_cast<unsigned>(model_dtm_out.req_data),
            static_cast<unsigned>(rtl_dmi_ports.debug_resp_valid[0].val),
            static_cast<unsigned>(rtl_dmi_ports.debug_resp_bits_data[0].val),
            static_cast<unsigned>(model_dmi_pre.resp_valid),
            static_cast<unsigned>(model_dmi_pre.resp_data),
            static_cast<unsigned>(
                rtl_debug.dmOuter.dmiXbar.readys_mask[0].val),
            static_cast<unsigned>(
                rtl_debug.dmOuter.io_innerCtrl_source.ready_reg[0].val),
            static_cast<unsigned>(
                rtl_debug.dmInner.dmactive_synced_dmInner_io_innerCtrl_sink
                    .valid_reg[0]
                    .val),
            static_cast<unsigned>(
                rtl_debug.dmInner.dmInner.ctrlStateReg[0].val),
            static_cast<unsigned>(
                rtl_debug.dmInner.dmInner.haltedBitRegs[0].val),
            static_cast<unsigned>(
                rtl_debug.dmInner.dmInner.resumeReqRegs[0].val),
            static_cast<unsigned long long>(
                model_debug_pre.outer_xbar_readys_mask),
            static_cast<unsigned long long>(
                model_debug_pre.outer_inner_ctrl_ready_reg),
            static_cast<unsigned long long>(
                model_debug_pre.inner_ctrl_sink_valid_reg),
            static_cast<unsigned long long>(
                model_debug_pre.inner_ctrl_state),
            static_cast<unsigned>(model_debug_path_pre.abstract_busy),
            static_cast<unsigned>(model_debug_path_pre.go_abstract),
            static_cast<unsigned>(model_debug_path_pre.halted),
            static_cast<unsigned>(model_debug_path_pre.resume_requested),
            static_cast<unsigned>(model_debug_manager_pre.tl_a_valid),
            static_cast<unsigned>(model_debug_manager_pre.tl_d_ready),
            static_cast<unsigned>(model_debug_manager_pre.tl_a_source),
            static_cast<unsigned>(model_debug_manager_pre.tl_a_address),
            static_cast<unsigned>(model_debug_manager_pre.tl_a_opcode));
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
        {
          const auto& core = model.backend().core();
          const unsigned model_idx = core.store_clr_bsy_s2.rob_idx;
          const unsigned model_slot = static_cast<unsigned>(boomcfg::rob_mk(
              boomcfg::rob_row(static_cast<int>(model_idx)), 0));
          const unsigned rtl_idx = static_cast<unsigned>(
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu
                  .clr_bsy_rob_idx_0[0]
                  .val);
          std::fprintf(
              stderr,
              "[LARGE-ROBR0-PRE] c=%llu "
              "rtl(v=%u idx=%u row=%u r0=%u bank=%u) "
              "model(s1=%u/%u s2=%u/%u row=%u slot=%u busy=%u)\n",
              static_cast<unsigned long long>(cycle),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_core_clr_bsy_0_valid[0]
                      .val),
              rtl_idx, rtl_idx >> boomcfg::ROB_BANK_SHIFT,
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r0[0]
                      .val),
              static_cast<unsigned>(
                  dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                      .rob.__v2_state_rob_bsy[rtl_idx >>
                                             boomcfg::ROB_BANK_SHIFT]
                      .val),
              static_cast<unsigned>(core.store_clr_bsy_s1.v),
              static_cast<unsigned>(core.store_clr_bsy_s1.rob_idx),
              static_cast<unsigned>(core.store_clr_bsy_s2.v), model_idx,
              static_cast<unsigned>(boomcfg::rob_row(
                  static_cast<int>(model_idx))),
              model_slot, static_cast<unsigned>(core.rob.busy[model_slot]));
        }
#endif  // CHISA_LEGACY_CORE_DIAG
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
        {
          const auto& rtl_core =
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core;
          const auto& rr = rtl_core.iregister_read;
          const auto& alu = rtl_core.ALUExeUnit$$inst.alu;
          const auto& core = model.backend().core();
          const auto& omir = core.omir;
          std::fprintf(
              stderr,
              "[LARGE-IREG-PRE] c=%llu "
              "rtl(rs1=%llx next=%llx prs=%u z=%u raw=%llx "
              "src=%llx/%llx/%llx/%llx/%llx "
              "hit=%u@p%u/%u@p%u/%u@p%u/%u@p%u/%u@p%u) "
              "model(rrd=%u/p%u/t%u exe=%u/p%u "
              "rawaddr=p%u raw=%llx b0=%u/p%u/%llx "
              "b1=%u/p%u/%llx b2=%u/p%u/%llx out=%llx)\n",
              static_cast<unsigned long long>(cycle),
              static_cast<unsigned long long>(rr.exe_reg_rs1_data_1[0].val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$exe_reg_rs1_data_1$next[0]
                      .val),
              static_cast<unsigned>(rr.REG_3_prs1[0].val),
              static_cast<unsigned>(rr.REG_10[0].val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregfile$io_read_ports_2_data[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_0_bits_data[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_1_bits_data[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_2_bits_data[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_3_bits_data[0]
                      .val),
              static_cast<unsigned long long>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_bypass_4_bits_data[0]
                      .val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$jmp_unit$alu$io_req_valid[0]
                      .val),
              static_cast<unsigned>(rr.exe_reg_uops_1_pdst[0].val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$io_req_valid[0]
                      .val),
              static_cast<unsigned>(rr.exe_reg_uops_2_pdst[0].val),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ALUExeUnit$$inst$alu$io_req_valid[0]
                      .val),
              static_cast<unsigned>(rr.exe_reg_uops_3_pdst[0].val),
              static_cast<unsigned>(alu.r_val_0[0].val),
              static_cast<unsigned>(alu.REG_1_0_pdst[0].val),
              static_cast<unsigned>(alu.r_val_1[0].val),
              static_cast<unsigned>(alu.REG_1_1_pdst[0].val),
              static_cast<unsigned>(core.int_rrd_at(0).v),
              static_cast<unsigned>(core.int_rrd_at(0).uop.prs1),
              static_cast<unsigned>(core.int_rrd_at(0).uop.lrs1_rtype),
              static_cast<unsigned>(core.int_exe_at(0).v),
              static_cast<unsigned>(core.int_exe_at(0).uop.pdst),
              static_cast<unsigned>(core.out_ext_irf_read_addrs[2]),
              static_cast<unsigned long long>(core.ext_irf_read_datas[2]),
              static_cast<unsigned>(omir.b0v_pre),
              static_cast<unsigned>(core.int_exe_at(0).uop.pdst),
              static_cast<unsigned long long>(omir.int_exe_res),
              static_cast<unsigned>(omir.byp1.v),
              static_cast<unsigned>(omir.byp1.pdst),
              static_cast<unsigned long long>(omir.byp1.data),
              static_cast<unsigned>(omir.byp2.v),
              static_cast<unsigned>(omir.byp2.pdst),
              static_cast<unsigned long long>(omir.byp2.data),
              static_cast<unsigned long long>(omir.exe_rs1_data[1]));
        }
#endif  // CHISA_LEGACY_CORE_DIAG
      }
#endif
      observer.begin_cycle();
#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
      if (chisa_mw_debug_cycle(cycle)) {
        const auto model_debug_post =
            model.memory().debug_path_for_diagnostic().debug_hand_oracles();
        std::fprintf(
            stderr,
            "[DDBG-POSTM] c=%llu mask=%llu ctrlr=%llu sinkv=%llu\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned long long>(
                model_debug_post.outer_xbar_readys_mask),
            static_cast<unsigned long long>(
                model_debug_post.outer_inner_ctrl_ready_reg),
            static_cast<unsigned long long>(
                model_debug_post.inner_ctrl_sink_valid_reg));
        {
          const auto& core = model.backend().core();
          const unsigned model_idx = core.store_clr_bsy_s2.rob_idx;
          const unsigned model_slot = static_cast<unsigned>(boomcfg::rob_mk(
              boomcfg::rob_row(static_cast<int>(model_idx)), 0));
          std::fprintf(
              stderr,
              "[LARGE-ROBR0-POSTM] c=%llu "
              "model(s1=%u/%u s2=%u/%u row=%u slot=%u busy=%u)\n",
              static_cast<unsigned long long>(cycle),
              static_cast<unsigned>(core.store_clr_bsy_s1.v),
              static_cast<unsigned>(core.store_clr_bsy_s1.rob_idx),
              static_cast<unsigned>(core.store_clr_bsy_s2.v), model_idx,
              static_cast<unsigned>(boomcfg::rob_row(
                  static_cast<int>(model_idx))),
              model_slot, static_cast<unsigned>(core.rob.busy[model_slot]));
        }
        {
          const auto& core = model.backend().core();
          const auto& omir = core.omir;
          std::fprintf(
              stderr,
              "[LARGE-IREG-POSTM] c=%llu out=%llx "
              "rrd0=%u/p%u exe0=%u/p%u "
              "rrd1=%u/p%u exe1=%u/p%u "
              "rrd2=%u/p%u exe2=%u/p%u "
              "res=%llx/%llx b1=%u/p%u/%llx b2=%u/p%u/%llx\n",
              static_cast<unsigned long long>(cycle),
              static_cast<unsigned long long>(omir.exe_rs1_data[1]),
              static_cast<unsigned>(core.int_rrd_at(0).v),
              static_cast<unsigned>(core.int_rrd_at(0).uop.pdst),
              static_cast<unsigned>(core.int_exe_at(0).v),
              static_cast<unsigned>(core.int_exe_at(0).uop.pdst),
              static_cast<unsigned>(core.int_rrd_at(1).v),
              static_cast<unsigned>(core.int_rrd_at(1).uop.pdst),
              static_cast<unsigned>(core.int_exe_at(1).v),
              static_cast<unsigned>(core.int_exe_at(1).uop.pdst),
              static_cast<unsigned>(core.int_rrd_at(2).v),
              static_cast<unsigned>(core.int_rrd_at(2).uop.pdst),
              static_cast<unsigned>(core.int_exe_at(2).v),
              static_cast<unsigned>(core.int_exe_at(2).uop.pdst),
              static_cast<unsigned long long>(omir.int_rrd_res),
              static_cast<unsigned long long>(omir.int_exe_res),
              static_cast<unsigned>(omir.byp1.v),
              static_cast<unsigned>(omir.byp1.pdst),
              static_cast<unsigned long long>(omir.byp1.data),
              static_cast<unsigned>(omir.byp2.v),
              static_cast<unsigned>(omir.byp2.pdst),
              static_cast<unsigned long long>(omir.byp2.data));
        }
        const auto& rtl_dcache =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache;
        const auto& rtl_lsu =
            dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu;
        const auto& model_dcache =
            model.memory().dcache_for_diagnostic();
        const auto& model_iom =
            model.memory().debug_path_for_diagnostic().iomshr_active_oracle();
        const auto& model_lsu = model.backend().core().lsu;
        const auto& model_raw = model.backend().raw_attempt();
        const auto& model_fire = model.backend().memory_request();
        const unsigned rtl_ldq_valid =
            (static_cast<unsigned>(rtl_lsu.ldq_0_valid[0].val) << 0) |
            (static_cast<unsigned>(rtl_lsu.ldq_1_valid[0].val) << 1) |
            (static_cast<unsigned>(rtl_lsu.ldq_2_valid[0].val) << 2) |
            (static_cast<unsigned>(rtl_lsu.ldq_3_valid[0].val) << 3);
        unsigned model_ldq_valid = 0;
        for (unsigned i = 0; i < 4; ++i)
          model_ldq_valid |= static_cast<unsigned>(model_lsu.ldq[i].valid)
                             << i;
        std::fprintf(
            stderr,
            "[LARGE-DC-PRE] c=%llu rtl(type=%u/%u) "
            "model(type=%u/%u s2q=%u raw=%u/%llx/q%u fire=%u/%llx/q%u) "
            "iom=%u/%u(cd=%u a=%llx cmd=%u) "
            "lsq-tail=%u/%u:%u/%u ldq-v=%x:%x\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned>(rtl_dcache.s1_type[0].val),
            static_cast<unsigned>(rtl_dcache.s2_type[0].val),
            static_cast<unsigned>(model_dcache.oracle_s1_type()),
            static_cast<unsigned>(model_dcache.oracle_s2_type()),
            static_cast<unsigned>(model_dcache.bus_s2_oracle().stq_idx),
            static_cast<unsigned>(model_raw.valid),
            static_cast<unsigned long long>(model_raw.address),
            static_cast<unsigned>(model_raw.stq_idx),
            static_cast<unsigned>(model_fire.valid),
            static_cast<unsigned long long>(model_fire.address),
            static_cast<unsigned>(model_fire.stq_idx),
            static_cast<unsigned>(
                rtl_dcache.mshrs.mmios_0.state[0].val),
            static_cast<unsigned>(
                model.memory().debug_path_for_diagnostic()
                    .iomshr_state_oracle()),
            static_cast<unsigned>(
                model.memory().debug_path_for_diagnostic()
                    .iomshr_countdown_oracle()),
            static_cast<unsigned long long>(model_iom.address),
            static_cast<unsigned>(model_iom.command),
            static_cast<unsigned>(rtl_lsu.ldq_tail[0].val),
            static_cast<unsigned>(rtl_lsu.stq_tail[0].val),
            static_cast<unsigned>(model_lsu.ldq_tail),
            static_cast<unsigned>(model_lsu.stq_tail), rtl_ldq_valid,
            model_ldq_valid);
      }
#endif  // CHISA_LEGACY_CORE_DIAG
#endif
      if (chisa_mw_debug_cycle(cycle)) {
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
        {
          const auto& rr =
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                  .fp_pipeline.fregister_read;
          const auto& rtl_fma =
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                  .fp_pipeline.fpiu_unit.fpu.fpu.dfma.fma;
          const auto& mc = model.backend().core();
          const auto& fpu_oracles = model.fabric().fpu_oracles();
          const auto& fpu_output = model.fabric().fpu_outputs();
          const std::uint64_t rtl_rs1 =
              rr.exe_reg_rs1_data_0[0].bits<63, 0>().as_single_word();
          const std::uint64_t rtl_rs2 =
              rr.exe_reg_rs2_data_0[0].bits<63, 0>().as_single_word();
          const std::uint64_t rtl_rs3 =
              rr.exe_reg_rs3_data_0[0].bits<63, 0>().as_single_word();
          const unsigned rtl_hi =
              static_cast<unsigned>(
                  rr.exe_reg_rs1_data_0[0].bits<64, 64>().as_single_word()) |
              (static_cast<unsigned>(
                   rr.exe_reg_rs2_data_0[0].bits<64, 64>().as_single_word())
               << 1) |
              (static_cast<unsigned>(
                   rr.exe_reg_rs3_data_0[0].bits<64, 64>().as_single_word())
               << 2);
          const unsigned rtl_fu = rr.exe_reg_uops_0_fu_code[0].val;
          const bool rtl_inner_valid =
              rr.exe_reg_valids_0[0].val != 0 &&
              (rtl_fu & (FU_FPU | FU_F2I)) != 0;
          const auto& rtl_resp_data =
              _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$fp_pipeline$fpiu_unit$fpu$fpu$io_resp_bits_data[0];
          const std::uint64_t rtl_resp_lo =
              rtl_resp_data.bits<63, 0>().as_single_word();
          const unsigned rtl_resp_hi = static_cast<unsigned>(
              rtl_resp_data.bits<64, 64>().as_single_word());
          std::fprintf(
              stderr,
              "[FPUBOUNDARY-PRE] c=%llu "
              "rtl(v=%u/%u u=%u fu=%03x imm=%05x "
              "hi=%x rs=%016llx/%016llx/%016llx) "
              "model(exe=%u/%u u=%u fu=%03x imm=%05x "
              "hi=%x rs=%016llx/%016llx/%016llx; "
              "last=%u u=%u hi=%x rs=%016llx/%016llx/%016llx) "
              "state(sExp=%llx/%llx) "
              "resp(rtl=%u/%x:%016llx/%x model=%u/%x:%016llx/%x "
              "wrap3=%u/p%u/u%u)\n",
              static_cast<unsigned long long>(cycle),
              static_cast<unsigned>(rr.exe_reg_valids_0[0].val),
              static_cast<unsigned>(rtl_inner_valid),
              static_cast<unsigned>(rr.exe_reg_uops_0_uopc[0].val), rtl_fu,
              static_cast<unsigned>(rr.exe_reg_uops_0_imm_packed[0].val),
              rtl_hi, static_cast<unsigned long long>(rtl_rs1),
              static_cast<unsigned long long>(rtl_rs2),
              static_cast<unsigned long long>(rtl_rs3),
              static_cast<unsigned>(mc.fp_exe_valid),
              static_cast<unsigned>(
                  mc.fp_exe_valid &&
                  (mc.fp_exe_uop.fu_code & (FU_FPU | FU_F2I)) != 0),
              static_cast<unsigned>(mc.fp_exe_uop.uopc),
              static_cast<unsigned>(mc.fp_exe_uop.fu_code),
              static_cast<unsigned>(mc.fp_exe_uop.imm_packed),
              static_cast<unsigned>(mc.fp_exe_rec_hi),
              static_cast<unsigned long long>(mc.fp_exe_rec_lo[0]),
              static_cast<unsigned long long>(mc.fp_exe_rec_lo[1]),
              static_cast<unsigned long long>(mc.fp_exe_rec_lo[2]),
              static_cast<unsigned>(mc.fpu_inner_valid),
              static_cast<unsigned>(mc.fpu_inner_uop.uopc),
              static_cast<unsigned>(mc.fpu_inner_rec_hi),
              static_cast<unsigned long long>(mc.fpu_inner_rec_lo[0]),
              static_cast<unsigned long long>(mc.fpu_inner_rec_lo[1]),
              static_cast<unsigned long long>(mc.fpu_inner_rec_lo[2]),
              static_cast<unsigned long long>(
                  rtl_fma.roundRawFNToRecFN_io_in_b_sExp[0]
                      .as_single_word()),
              static_cast<unsigned long long>(fpu_oracles[6]),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$fp_pipeline$fpiu_unit$fpu$fpu$io_resp_valid[0]
                      .val),
              rtl_resp_hi, static_cast<unsigned long long>(rtl_resp_lo),
              static_cast<unsigned>(
                  _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$fp_pipeline$fpiu_unit$fpu$fpu$io_resp_bits_fflags_bits_flags[0]
                      .val),
              static_cast<unsigned>(fpu_output.valid),
              static_cast<unsigned>(fpu_output.data_bit64),
              static_cast<unsigned long long>(fpu_output.data),
              static_cast<unsigned>(fpu_output.exception_flags),
              static_cast<unsigned>(mc.fpu_wrapper_valids[3]),
              static_cast<unsigned>(mc.fpu_wrapper_uops[3].pdst),
              static_cast<unsigned>(mc.fpu_wrapper_uops[3].uopc));
        }
#endif  // CHISA_LEGACY_CORE_DIAG
        const std::uint64_t bank03 =
            dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem__v2_bank_0_3[0]
                .val;
        const auto& dtlb = model.last_dtlb();
        std::fprintf(
            stderr,
            "[LSUPRE] c=%llu rtl(bank03=%llx mem_unc=%u mem_miss=%u) "
            "model(agu_v=%u cand_v=%u va=%llx sz=%u cmd=%u legal=%u "
            "pma_c=%u resp_unc=%u packed=%u->%u)\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned long long>(bank03),
            static_cast<unsigned>(bank03 & UINT64_C(1)),
            static_cast<unsigned>((bank03 >> 1) & UINT64_C(1)),
            static_cast<unsigned>(dtlb.agu_valid),
            static_cast<unsigned>(dtlb.candidate_valid),
            static_cast<unsigned long long>(dtlb.candidate_vaddr),
            static_cast<unsigned>(dtlb.candidate_size),
            static_cast<unsigned>(dtlb.candidate_cmd),
            static_cast<unsigned>(dtlb.pma_legal),
            static_cast<unsigned>(dtlb.pma_cacheable),
            static_cast<unsigned>(dtlb.response_uncacheable),
            static_cast<unsigned>(dtlb.lcam_packed_pre),
            static_cast<unsigned>(dtlb.lcam_packed_next));
        const auto& sbus_edge =
            model.fabric().last_system_bus_boundary_transaction();
        const auto& sbus_state = model.fabric().system_bus_oracles();
        std::fprintf(
            stderr,
            "[SBUSPRE] c=%llu rtl(a_v=%u a_r=%u mask=%llx state1=%llx) "
            "model(last_a=%u/%u/fire%u op=%u sz=%u src=%u addr=%x "
            "mask=%llx->%llx state1=%llx->%llx now=%llx/%llx)\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned>(
                _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_a_q$io_deq_valid[0].val),
            static_cast<unsigned>(
                _s_ldut$subsystem_sbus$system_bus_xbar$auto_in_1_a_ready[0].val),
            static_cast<unsigned long long>(
                dut->ldut.subsystem_sbus.system_bus_xbar.readys_mask[0].val),
            static_cast<unsigned long long>(
                dut->ldut.subsystem_sbus.system_bus_xbar.state__1[0].val),
            static_cast<unsigned>(sbus_edge.a_valid),
            static_cast<unsigned>(sbus_edge.a_ready),
            static_cast<unsigned>(sbus_edge.a_fire),
            static_cast<unsigned>(sbus_edge.a_opcode),
            static_cast<unsigned>(sbus_edge.a_size),
            static_cast<unsigned>(sbus_edge.a_source),
            static_cast<unsigned>(sbus_edge.a_address),
            static_cast<unsigned long long>(sbus_edge.readys_mask_before),
            static_cast<unsigned long long>(sbus_edge.readys_mask_after),
            static_cast<unsigned long long>(sbus_edge.state_1_before),
            static_cast<unsigned long long>(sbus_edge.state_1_after),
            static_cast<unsigned long long>(sbus_state[84]),
            static_cast<unsigned long long>(sbus_state[95]));
      }
      const auto result = stepper.step(
          stepper.expected_direction(), cycle < options.reset_cycles,
          options.verbose);
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
      if (boundary_audit && !seam_reported) {
        // The C channel is the first exercised hot-tile/cold-coherence seam.
        // Its ready/valid controls matter every cycle; payload is meaningful
        // under valid. Check it before a tracker register or downstream AXI
        // oracle turns the same bug into a much less local failure.
        const auto& transaction =
            model.fabric().last_coherence_boundary_transaction();
        const bool rtl_valid =
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$io_deq_valid[0]
                .val != 0;
        const bool rtl_ready =
            _s_ldut$subsystem_l2_wrapper$broadcast_1$auto_in_c_ready[0].val !=
            0;
        const std::uint8_t rtl_opcode = static_cast<std::uint8_t>(
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_opcode$io_deq_bits_MPORT[0]
                .val);
        const std::uint8_t rtl_param = static_cast<std::uint8_t>(
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_param$io_deq_bits_MPORT[0]
                .val);
        const std::uint8_t rtl_size = static_cast<std::uint8_t>(
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_size$io_deq_bits_MPORT[0]
                .val);
        const std::uint8_t rtl_source = static_cast<std::uint8_t>(
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_source$io_deq_bits_MPORT[0]
                .val);
        const std::uint32_t rtl_address = static_cast<std::uint32_t>(
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_address$io_deq_bits_MPORT[0]
                .val);
        const std::uint64_t rtl_data =
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_data$io_deq_bits_MPORT[0]
                .val;
        const bool rtl_corrupt =
            _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_corrupt$io_deq_bits_MPORT[0]
                .val != 0;
        const auto coherence_seam = first_seam_mismatch({
            SeamSignal::event("tile->coherence.c.valid", rtl_valid,
                              transaction.c_valid),
            SeamSignal::event("coherence->tile.c.ready", rtl_ready,
                              transaction.c_ready),
            SeamSignal::valid_payload(
                "tile->coherence.c.opcode", rtl_opcode,
                transaction.c_opcode, 3, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.param", rtl_param,
                transaction.c_param, 3, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.size", rtl_size,
                transaction.c_size, 4, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.source", rtl_source,
                transaction.c_source, 3, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.address", rtl_address,
                transaction.c_address, 32, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.data", rtl_data,
                transaction.c_data, 64, rtl_valid, transaction.c_valid),
            SeamSignal::valid_payload(
                "tile->coherence.c.corrupt", rtl_corrupt,
                transaction.c_corrupt, 1, rtl_valid, transaction.c_valid),
        });
        if (coherence_seam) {
          seam_reported = true;
          boundary_mismatch = true;
          std::fprintf(
              stderr,
              "[SEAM first-boundary-divergence] c=%llu %s rule=%s "
              "rtl=%llx model=%llx\n"
              "  rtl C(v/r=%u/%u op/p/sz/src=%u/%u/%u/%u "
              "addr=%08x data=%016llx corrupt=%u)\n"
              "  model C(v/r=%u/%u op/p/sz/src=%u/%u/%u/%u "
              "addr=%08x data=%016llx corrupt=%u)\n",
              static_cast<unsigned long long>(cycle), coherence_seam->name,
              seam_rule_name(coherence_seam->rule),
              static_cast<unsigned long long>(coherence_seam->rtl),
              static_cast<unsigned long long>(coherence_seam->model),
              static_cast<unsigned>(rtl_valid),
              static_cast<unsigned>(rtl_ready),
              static_cast<unsigned>(rtl_opcode),
              static_cast<unsigned>(rtl_param),
              static_cast<unsigned>(rtl_size),
              static_cast<unsigned>(rtl_source),
              static_cast<unsigned>(rtl_address),
              static_cast<unsigned long long>(rtl_data),
              static_cast<unsigned>(rtl_corrupt),
              static_cast<unsigned>(transaction.c_valid),
              static_cast<unsigned>(transaction.c_ready),
              static_cast<unsigned>(transaction.c_opcode),
              static_cast<unsigned>(transaction.c_param),
              static_cast<unsigned>(transaction.c_size),
              static_cast<unsigned>(transaction.c_source),
              static_cast<unsigned>(transaction.c_address),
              static_cast<unsigned long long>(transaction.c_data),
              static_cast<unsigned>(transaction.c_corrupt));
        }
      }
#endif  // small-tap diagnostics
      if (chisa_edge_audit_cycle(cycle)) {
        const auto& transaction =
            model.fabric().last_coherence_boundary_transaction();
        std::fprintf(
            stderr,
            "[EDGE-COH] c=%llu "
            "rtl(c=%u/%u op=%u p=%u a=%08x match=%u ack=%u shared=%u) "
            "model(c=%u/%u op=%u p=%u a=%08x match=%u ack=%u "
            "shared=%u->%u)\n",
            static_cast<unsigned long long>(cycle),
            static_cast<unsigned>(
                _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$io_deq_valid[0]
                    .val),
            static_cast<unsigned>(
                _s_ldut$subsystem_l2_wrapper$broadcast_1$auto_in_c_ready[0]
                    .val),
            static_cast<unsigned>(
                _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_opcode$io_deq_bits_MPORT[0]
                    .val),
            static_cast<unsigned>(
                _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_param$io_deq_bits_MPORT[0]
                    .val),
            static_cast<unsigned>(
                _s_ldut$tile_prci_domain$buffer_1$bundleOut_0_c_q$ram_address$io_deq_bits_MPORT[0]
                    .val),
            static_cast<unsigned>(
                _s_ldut$subsystem_l2_wrapper$broadcast_1$_T_113[0].val),
            static_cast<unsigned>(
                _s_ldut$subsystem_l2_wrapper$broadcast_1$TLBroadcastTracker$$inst$io_probesack[0]
                    .val),
            static_cast<unsigned>(
                dut->ldut.subsystem_l2_wrapper.broadcast_1
                    .TLBroadcastTracker$$inst.shared[0]
                    .val),
            static_cast<unsigned>(transaction.c_valid),
            static_cast<unsigned>(transaction.c_ready),
            static_cast<unsigned>(transaction.c_opcode),
            static_cast<unsigned>(transaction.c_param),
            static_cast<unsigned>(transaction.c_address),
            static_cast<unsigned>(transaction.line_match[0]),
            static_cast<unsigned>(transaction.probe_ack[0]),
            static_cast<unsigned>(transaction.shared_before[0]),
            static_cast<unsigned>(transaction.shared_after[0]));
      }
      observer.end_cycle();
      if (probe_contract_known && measurement_active &&
          cycle >= options.reset_cycles && cycle >= probe_skip_cycles) {
        if (compared_cycles == 0) comparison_start_cycle = cycle;
        ++compared_cycles;
      }
      if (dcport_debug) {
        const auto& dcache = model.memory().dcache_for_diagnostic();
        const auto& raw = dcache.raw_data_for_diagnostic();
        std::fprintf(
            stderr,
            "[DCPORT] c=%llu dir=%s "
            "rtl(addr=%03x->%03x mport=%016llx) "
            "model(addr=%03x->%03x port=%016llx->%016llx "
            "raw_v=%u raw_addr=%010llx ways=%x) "
            "mshr1(rtl=%u->%u model=%u->%u)\n",
            static_cast<unsigned long long>(cycle),
            chisa::boom_repcut::direction_name(result.direction),
            static_cast<unsigned>(rtl_dc_addr3_pre),
            static_cast<unsigned>(
                dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache
                    .data.array_3_0_0_MPORT_7_addr_pipe_0[0]
                    .val),
            static_cast<unsigned long long>(
                _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$data$array_3_0_0$MPORT_7[0]
                    .val),
            static_cast<unsigned>(model_dc_addr3_pre),
            static_cast<unsigned>(dcache.oracle_data_address(3)),
            static_cast<unsigned long long>(model_dc_port3_pre),
            static_cast<unsigned long long>(dcache.oracle_data_port(3)),
            static_cast<unsigned>(raw.valid),
            static_cast<unsigned long long>(raw.address),
            static_cast<unsigned>(dcache.raw_data_way_mask_for_diagnostic()),
            static_cast<unsigned>(rtl_mshr1_pre),
            static_cast<unsigned>(
                dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache
                    .mshrs.mshrs_1.state[0]
                    .val),
            static_cast<unsigned>(model_mshr1_pre),
            static_cast<unsigned>(dcache.mshr_for_diagnostic(1).state));
      }
      {  // env-gated RTL meta-arbiter probe (CHISA_MW_DEBUG=lo-hi)
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)  // small-tap diagnostics
#if defined(CHISA_LEGACY_CORE_DIAG)  // diagnostics over the previous core model
        if (chisa_mw_debug_cycle(cycle)) {
          {
            const auto& ro = model.backend().core().omir;
            const auto& mc = model.backend().core();
            const auto pack_uop = [](const auto& uop) {
              return chisa::boom_system::pack_rob_uop(uop);
            };
            fprintf(stderr,
                    "[ROBPORT] c=%llu rtl_idx=%u/%u/%u rtl_b=%u/%u/%u "
                    "model_b=%u/%u/%u now(ll=%u/%u ir=%u/%u/%u) "
                    "pipe=%u/%u/%u/%u/%u "
                    "r3(model_snap=%llx array0=%llx enq=%u@%u/%llx)\n",
                    (unsigned long long)cycle,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ll_wbarb$io_out_bits_uop_rob_idx[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$io_iresp_bits_uop_rob_idx[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$fp_pipeline$ll_wbarb$io_out_bits_uop_rob_idx[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r3[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r4[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_state_rob_bsy$r5[0].val,
                    (unsigned)ro.rob_read_bsy_now[0],
                    (unsigned)ro.rob_read_bsy_now[1],
                    (unsigned)ro.rob_read_bsy_now[2],
                    (unsigned)ro.ll_now_v, (unsigned)ro.ll_now_rob,
                    (unsigned)ro.iresp_now_v, (unsigned)ro.iresp_now_rob,
                    (unsigned)ro.iresp_now_alu,
                    (unsigned)ro.oracle_exe_uop.rob_idx,
                    (unsigned)ro.oracle_b1_uop.rob_idx,
                    (unsigned)ro.oracle_b2_uop.rob_idx,
                    (unsigned)ro.oracle_b3_uop.rob_idx,
                    (unsigned)ro.oracle_b4_uop.rob_idx,
                    (unsigned long long)pack_uop(ro.rob_read_uop_now[1]),
                    (unsigned long long)pack_uop(mc.rob.uop[0]),
                    (unsigned)mc.rob_enq_fired,
                    (unsigned)mc.rob_tail_start,
                    (unsigned long long)pack_uop(mc.disp_uop));
          }
          {
            const auto& mf = model.frontend().f0_f2_for_diagnostic();
            const auto& mi = model.last_itlb_boundary();
            fprintf(stderr,
                    "[ITLB] c=%llu rtl(s1v=%u s1pc=%llx s1ae=%u s2ae=%u) "
                    "model(s1v=%u s1pc=%llx rep=%u sf=%u vm=%u req=%u "
                    "raw[m=%u ae=%u pf=%u pa=%x] sel[m=%u ae=%u pf=%u] "
                    "s2v=%u s2pc=%llx s2ae=%u dbg=%u)\n",
                    (unsigned long long)cycle,
                    (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend.s1_valid[0].val,
                    (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend.s1_vpc[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$frontend$s1_tlb_resp_ae_inst[0].val,
                    (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend.s2_tlb_resp_ae_inst[0].val,
                    (unsigned)mf.s1().valid,
                    (unsigned long long)mf.s1().vpc,
                    (unsigned)mi.s1_is_replay,
                    (unsigned)mi.s1_is_sfence,
                    (unsigned)mi.input.vm_enabled,
                    (unsigned)mi.input.request_valid,
                    (unsigned)mi.raw_response.miss,
                    (unsigned)mi.raw_response.xcpt_ae_if,
                    (unsigned)mi.raw_response.xcpt_pf_if,
                    (unsigned)mi.raw_response.paddr,
                    (unsigned)mi.selected_response.miss,
                    (unsigned)mi.selected_response.xcpt_ae_if,
                    (unsigned)mi.selected_response.xcpt_pf_if,
                    (unsigned)mf.s2().valid,
                    (unsigned long long)mf.s2().vpc,
                    (unsigned)mf.s2().tlb.xcpt_ae_if,
                    (unsigned)model.backend().core().csr.debug);
          }
          {  // frontend redirect: RTL core.io_ifu_redirect vs model control
            const auto fc = model.backend().frontend_control();
            const auto& mc = model.backend().core();
            fprintf(stderr,
                    "[IFU] c=%llu rtl(redir=%d pc=%llx mispred_next=%d "
                    "rob_flush=%d) model(redir=%d pc=%llx from_br=%d "
                    "from_rob=%d br_kill=%d rob_flush=%d xcpt=%d)\n",
                    (unsigned long long)cycle,
                    (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_ifu_redirect_val[0].val,
                    (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$io_ifu_redirect_pc[0].val,
                    (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$brinfos_0_mispredict$next[0].val,
                    (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$io_flush_valid[0].val,
                    (int)fc.redirect_valid, (unsigned long long)fc.redirect_pc,
                    (int)fc.redirect_from_branch_mispredict,
                    (int)fc.redirect_from_rob_flush, (int)mc.br_kill_this_cycle,
                    (int)mc.rob_flush_now, (int)mc.xcpt_kill_start);
          }
          {  // Branch-info carrier: payload is meaningful even when valid=0.
            const auto& mc = model.backend().core();
            const auto& mu = mc.brinfo_uop_r;
            // SmallBoom's jump/CSR ALU consumes FTQ port 0
            // (core.scala:569-572).  Printing port 1 here previously made a
            // correct port-0 value look one cycle late during JALR diagnosis.
            const auto& mg = mc.ext_ftq_get_pc0;
            const auto& rr =
                dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core
                    .iregister_read;
            const auto& rf =
                dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.frontend
                    .ftq;
            fprintf(
                stderr,
                "[BRINFO] c=%llu rtl(eval req=%u br=%u jalr=%u pcsel=%u "
                "misp=%u; next-exe v=%u bt=%u jalr=%u ftq=%u pclob=%u "
                "taken=%u; ftq nv=%u npc=%llx cfiv=%u cfii=%u sb=%u) "
                "model(eval v=%u bt=%u br=%u jalr=%u ftq=%u pclob=%u "
                "taken=%u misp=%u; ftq nv=%u npc=%llx cfiv=%u cfii=%u "
                "sb=%u)\n",
                (unsigned long long)cycle,
                (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$io_req_valid[0].val,
                (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$is_br[0].val,
                (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$is_jalr[0].val,
                (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$pc_sel[0].val,
                (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$csr_exe_unit$alu$io_brinfo_mispredict[0].val,
                (unsigned)rr.exe_reg_valids_1[0].val,
                (unsigned)rr.exe_reg_uops_1_ctrl_br_type[0].val,
                (unsigned)rr.exe_reg_uops_1_is_jalr[0].val,
                (unsigned)rr.exe_reg_uops_1_ftq_idx[0].val,
                (unsigned)rr.exe_reg_uops_1_pc_lob[0].val,
                (unsigned)rr.exe_reg_uops_1_taken[0].val,
                (unsigned)rf.REG_20[0].val,
                (unsigned long long)rf.REG_19[0].val,
                (unsigned)rf.REG_17_cfi_idx_valid[0].val,
                (unsigned)rf.REG_17_cfi_idx_bits[0].val,
                (unsigned)rf.REG_17_start_bank[0].val,
                (unsigned)mc.omir.brinfos_valid_r,
                (unsigned)mu.ctrl.br_type, (unsigned)mu.is_br,
                (unsigned)mu.is_jalr, (unsigned)mu.ftq_idx,
                (unsigned)mu.pc_lob, (unsigned)mu.taken,
                (unsigned)mc.omir.brexe_mispred_pre,
                (unsigned)mg.next_val, (unsigned long long)mg.next_pc,
                (unsigned)mg.cfi_valid, (unsigned)mg.cfi_idx,
                (unsigned)mg.start_bank);
          }
          {  // LSU queues: RTL current registers vs model LsuState
#define RL(x) (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.x[0].val
            const auto& ml = model.backend().core().lsu;
            const auto& mo = model.backend().core().omir;
            fprintf(stderr,
                    "[LSU] c=%llu rtl wbfwd(v=%llu ldq=%llu stq=%llu) blk=%llu%llu%llu%llu%llu%llu%llu%llu"
                    " | model wbfwd(v=%d ldq=%u stq=%u) heads ldq=%d/%d stq=%d/%d cmt=%d exe=%d live=%02x\n",
                    (unsigned long long)cycle, RL(wb_forward_valid_0), RL(wb_forward_ldq_idx_0),
                    RL(wb_forward_stq_idx_0), RL(p1_block_load_mask_7), RL(p1_block_load_mask_6),
                    RL(p1_block_load_mask_5), RL(p1_block_load_mask_4), RL(p1_block_load_mask_3),
                    RL(p1_block_load_mask_2), RL(p1_block_load_mask_1), RL(p1_block_load_mask_0),
                    (int)mo.wb_fwd_valid_r, (unsigned)mo.wb_fwd_ldq_r, (unsigned)mo.wb_fwd_stq_r,
                    ml.ldq_head, ml.ldq_tail, ml.stq_head, ml.stq_tail, ml.stq_commit_head,
                    ml.stq_execute_head, (unsigned)ml.live_store_mask);
#define STQ(i) fprintf(stderr, "[LSU]   stq" #i " rtl(v=%llu av=%llu a=%llx dv=%llu d=%llx rob=%llu cmt=%llu ok=%llu)" \
                " model(v=%d av=%d a=%llx dv=%d d=%llx rob=%u cmt=%d ok=%d)\n", \
                RL(stq_##i##_valid), RL(stq_##i##_bits_addr_valid), RL(stq_##i##_bits_addr_bits), \
                RL(stq_##i##_bits_data_valid), RL(stq_##i##_bits_data_bits), RL(stq_##i##_bits_uop_rob_idx), \
                RL(stq_##i##_bits_committed), RL(stq_##i##_bits_succeeded), \
                (int)ml.stq[i].valid, (int)ml.stq[i].addr_valid, (unsigned long long)ml.stq[i].addr, \
                (int)ml.stq[i].data_valid, (unsigned long long)ml.stq[i].data, (unsigned)ml.stq[i].uop.rob_idx, \
                (int)ml.stq[i].committed, (int)ml.stq[i].succeeded)
#define LDQ(i) fprintf(stderr, "[LSU]   ldq" #i " rtl(v=%llu av=%llu a=%llx ex=%llu ok=%llu dep=%llx of=%llu fsv=%llu fsi=%llu rob=%llu pdst=%llu)" \
                " model(v=%d av=%d a=%llx ex=%d ok=%d dep=%x of=%d fsv=%d fsi=%u rob=%u pdst=%u)\n", \
                RL(ldq_##i##_valid), RL(ldq_##i##_bits_addr_valid), RL(ldq_##i##_bits_addr_bits), \
                RL(ldq_##i##_bits_executed), RL(ldq_##i##_bits_succeeded), RL(ldq_##i##_bits_st_dep_mask), \
                RL(ldq_##i##_bits_order_fail), RL(ldq_##i##_bits_forward_std_val), RL(ldq_##i##_bits_forward_stq_idx), \
                RL(ldq_##i##_bits_uop_rob_idx), RL(ldq_##i##_bits_uop_pdst), \
                (int)ml.ldq[i].valid, (int)ml.ldq[i].addr_valid, (unsigned long long)ml.ldq[i].addr, \
                (int)ml.ldq[i].executed, (int)ml.ldq[i].succeeded, (unsigned)ml.ldq[i].st_dep_mask, \
                (int)ml.ldq[i].order_fail, (int)ml.ldq[i].forward_std_val, (unsigned)ml.ldq[i].forward_stq_idx, \
                (unsigned)ml.ldq[i].uop.rob_idx, (unsigned)ml.ldq[i].uop.pdst)
            STQ(0); STQ(1); STQ(2); STQ(3); STQ(4); STQ(5); STQ(6); STQ(7);
            LDQ(0); LDQ(1); LDQ(2); LDQ(3); LDQ(4); LDQ(5); LDQ(6); LDQ(7);
#undef LDQ
#undef STQ
#undef RL
          }
          {  // can_forward sub-terms (RTL wires of this cycle) vs model
            const auto& mc2 = model.backend().core();
            const unsigned am = ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_0[0].val << 0) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_1[0].val << 1) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_2[0].val << 2) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_3[0].val << 3) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_4[0].val << 4) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_5[0].val << 5) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_6[0].val << 6) | ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_7[0].val << 7);
            fprintf(stderr, "[LSU2] c=%llu rtl(canf=%u base=%u exe_unc=%u mem_unc_post=%u tlb_c=%u pma_c=%u legal=%u pa=%llx va=%llx tv=%u vm=%u miss=%u am=%02x s1kill=%u fire=%u ptwresp=%u)"
                    " model(unc=%d inc_s1=%d fired_s1=%d lcam=%d)\n", (unsigned long long)cycle,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_forward_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9329[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$exe_tlb_uncacheable_0[0].val,
                    (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.mem_tlb_uncacheable_0[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_resp_0_cacheable[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$cacheable_0[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$legal_address_0[0].val,
                    (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$mpu_physaddr_0[0].val,
                    (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_bits_vaddr[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_req_0_valid[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$vm_enabled_0[0].val,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$exe_tlb_miss_0[0].val, am,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_s1_kill_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dmem_req_fire_0[0].val,
                    (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.ptw.resp_valid_0[0].val,
                    (int)mc2.dtlb_resp_uncacheable, (int)mc2.lcam_incoming_s1, (int)mc2.lcam_fired_s1, (int)mc2.lcam_ldq_s1);
          }
          {  // post-edge ($next) LDQ/fired registers + this cycle's search wires
            const auto& mc3 = model.backend().core();
            unsigned m_uc = 0, m_v = 0, m_av = 0, m_ex = 0;
            for (int k = 0; k < 8; ++k) { m_uc |= (unsigned)mc3.lsu.ldq[k].addr_is_uncacheable << k; m_v |= (unsigned)mc3.lsu.ldq[k].valid << k;
              m_av |= (unsigned)mc3.lsu.ldq[k].addr_valid << k; m_ex |= (unsigned)mc3.lsu.ldq[k].executed << k; }
            fprintf(stderr, "[LSU3] c=%llu wires(t1132=%u t1168=%u lcam=%u search=%u exe_unc=%u canfire_inc=%u willfire_retry=%u t990=%u t1052=%u fire=%u)"
                    " next(inc=%u retry=%u wake=%u mem_unc=%u ldq_uc=%02x v=%02x av=%02x ex=%02x)"
                    " bank03=%llx model(uc=%02x v=%02x av=%02x ex=%02x inc_s1=%d wake_r=%d wake_now=%d lcam=%d canfire=%d agu_v=%d)\n", (unsigned long long)cycle,
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_1132[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_1168[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$lcam_ldq_idx_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$do_ld_search_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$exe_tlb_uncacheable_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_fire_load_incoming_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$will_fire_load_retry_0[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_990[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_1052[0].val, (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dmem_req_fire_0[0].val,
                    (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.REG_3[0].val, (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.REG_7[0].val, (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.REG_9[0].val, (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.mem_tlb_uncacheable_0[0].val,
                    (unsigned)(((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_0_bits_addr_is_uncacheable[0].val << 0) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_1_bits_addr_is_uncacheable[0].val << 1) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_2_bits_addr_is_uncacheable[0].val << 2) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_3_bits_addr_is_uncacheable[0].val << 3) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_4_bits_addr_is_uncacheable[0].val << 4) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_5_bits_addr_is_uncacheable[0].val << 5) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_6_bits_addr_is_uncacheable[0].val << 6) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_7_bits_addr_is_uncacheable[0].val << 7)), (unsigned)(((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_0_valid[0].val << 0) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_1_valid[0].val << 1) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_2_valid[0].val << 2) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_3_valid[0].val << 3) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_4_valid[0].val << 4) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_5_valid[0].val << 5) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_6_valid[0].val << 6) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_7_valid[0].val << 7)), (unsigned)(((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_0_bits_addr_valid[0].val << 0) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_1_bits_addr_valid[0].val << 1) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_2_bits_addr_valid[0].val << 2) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_3_bits_addr_valid[0].val << 3) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_4_bits_addr_valid[0].val << 4) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_5_bits_addr_valid[0].val << 5) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_6_bits_addr_valid[0].val << 6) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_7_bits_addr_valid[0].val << 7)), (unsigned)(((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_0_bits_executed[0].val << 0) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_1_bits_executed[0].val << 1) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_2_bits_executed[0].val << 2) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_3_bits_executed[0].val << 3) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_4_bits_executed[0].val << 4) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_5_bits_executed[0].val << 5) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_6_bits_executed[0].val << 6) | ((unsigned)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu.ldq_7_bits_executed[0].val << 7)),
                    (unsigned long long)dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem__v2_bank_0_3[0].val, m_uc, m_v, m_av, m_ex, (int)mc3.lcam_incoming_s1, (int)mc3.omir.fired_load_wakeup_r, (int)mc3.omir.fired_wakeup_now, (int)mc3.lcam_ldq_s1, (int)mc3.omir.canfire_load_incoming, (int)mc3.mem_agu.v);
          }
          const auto& model_raw = model.backend().raw_attempt();
          const auto& model_fire = model.backend().memory_request();
          const auto& model_dcache =
              model.memory().dcache_for_diagnostic();
          const std::size_t model_set =
              static_cast<std::size_t>((model_raw.address >> 6) & 0x3f);
          const std::size_t model_beat =
              static_cast<std::size_t>((model_raw.address >> 3) & 0x7);
          fprintf(stderr,
                  "[DREQ] c=%llu rtl(v=%d r=%d f=%d a=%llx d=%llx inc=%d retry=%d "
                  "wakeup=%d store=%d dr_v=%d dr_a=%llx dr_n=%llx) "
                  "model(raw=%d a=%llx d=%llx z=%u ld=%d st=%d fire=%d fa=%llx fd=%llx "
                  "set=%zu beat=%zu data0=%llx data3=%llx "
                  "port0=%llx port3=%llx)\n",
                  (unsigned long long)cycle,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_valid[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_req_ready[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$_T_25[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_addr[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_req_bits_0_bits_data[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_fire_load_incoming_0[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$will_fire_load_retry_0[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$will_fire_load_wakeup_0[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$will_fire_store_commit_0[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$data$io_read_0_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$dataReadArb$io_out_bits_req_0_addr[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$data$array_0_0_0_MPORT_1_addr_pipe_0$next[0].val,
                  (int)model_raw.valid,
                  (unsigned long long)model_raw.address,
                  (unsigned long long)model_raw.data,
                  (unsigned)model_raw.size,
                  (int)model_raw.uses_ldq, (int)model_raw.uses_stq,
                  (int)model_fire.valid,
                  (unsigned long long)model_fire.address,
                  (unsigned long long)model_fire.data,
                  model_set, model_beat,
                  (unsigned long long)model_dcache.data(
                      0, model_set, model_beat),
                  (unsigned long long)model_dcache.data(
                      3, model_set, model_beat),
                  (unsigned long long)model_dcache.oracle_data_port(0),
                  (unsigned long long)model_dcache.oracle_data_port(3));
          const auto& model_core = model.backend().core();
          fprintf(stderr,
                  "[MPIPE] c=%llu rtl(iss=%d pdst=%llu ld=%d rrd=%llu "
                  "exe=%llu epdst=%llu eld=%llu kill=%llu b1=%llx "
                  "rrdbm=%llx rrdstd=%llu exestd=%llu) "
                  "model(iss=%d rrd=%d agu=%d ipdst=%u rpdst=%u "
                  "apdst=%u)\n",
                  (unsigned long long)cycle,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$io_iss_valids_0[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$io_iss_uops_0_pdst[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$mem_issue_unit$io_iss_uops_0_uses_ldq[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.REG[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.exe_reg_valids_0[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.exe_reg_uops_0_pdst[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.exe_reg_uops_0_uses_ldq[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.REG_23[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$iregister_read$io_brupdate_b1_mispredict_mask[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.REG_1_br_mask[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.REG_1_ctrl_is_std[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.iregister_read.exe_reg_uops_0_ctrl_is_std[0].val,
                  (int)model_core.mem_iss_stage.v,
                  (int)model_core.mem_rrd.v,
                  (int)model_core.mem_agu.v,
                  (unsigned)model_core.mem_iss_stage.uop.pdst,
                  (unsigned)model_core.mem_rrd.uop.pdst,
                  (unsigned)model_core.mem_agu.uop.pdst);
          const unsigned rtl_head = static_cast<unsigned>(
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.core.rob
                  .rob_head[0]
                  .val);
          const unsigned model_head =
              static_cast<unsigned>(model_core.rob.head) & 31u;
          fprintf(stderr,
                  "[RESP] c=%llu "
                  "rtl(dc_v=%u ld=%u st=%u lq=%u sq=%u data=%llx "
                  "iresp=%u irob=%u ipdst=%u wb=%u wrob=%u wpdst=%u) "
                  "model(resp=%u nack=%u data=%llx pend=%u ld=%u st=%u "
                  "lq=%u sq=%u rob=%u pdst=%u addr=%llx)\n",
                  (unsigned long long)cycle,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_uop_uses_ldq[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_uop_uses_stq[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_uop_ldq_idx[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_uop_stq_idx[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_resp_0_bits_data[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_core_exe_0_iresp_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_core_exe_0_iresp_bits_uop_rob_idx[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_core_exe_0_iresp_bits_uop_pdst[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ll_wbarb$io_out_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ll_wbarb$io_out_bits_uop_rob_idx[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$ll_wbarb$io_out_bits_uop_pdst[0].val,
                  (unsigned)model_core.dmem_resp_valid,
                  (unsigned)model_core.dmem_resp_nack,
                  (unsigned long long)model_core.dmem_resp_data,
                  (unsigned)model_core.dmem_pending.valid,
                  (unsigned)model_core.dmem_pending.uop.uses_ldq,
                  (unsigned)model_core.dmem_pending.uop.uses_stq,
                  (unsigned)model_core.dmem_pending.uop.ldq_idx,
                  (unsigned)model_core.dmem_pending.uop.stq_idx,
                  (unsigned)model_core.dmem_pending.uop.rob_idx,
                  (unsigned)model_core.dmem_pending.uop.pdst,
                  (unsigned long long)model_core.dmem_pending.addr);
          fprintf(stderr,
                  "[ROB] c=%llu rtl(h=%u val=%u busy=%u unsafe=%u exc=%u "
                  "row7=%u/%u/%u/%u) "
                  "model(h=%u val=%u busy=%u unsafe=%u exc=%u "
                  "row7=%u/%u/%u/%u start_h=%u start_busy=%u)\n",
                  (unsigned long long)cycle, rtl_head,
                  (unsigned)((dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_bitset_rob_val_bank_0[0]
                                  .val >>
                              rtl_head) &
                             1u),
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_bsy[rtl_head]
                      .val,
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_unsafe[rtl_head]
                      .val,
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_exception[rtl_head]
                      .val,
                  (unsigned)((dut->_v2_bank_ldut$tile_prci_domain$tile_reset_domain$boom_tile$core$rob$__v2_bitset_rob_val_bank_0[0]
                                  .val >>
                              7) &
                             1u),
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_bsy[7]
                      .val,
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_unsafe[7]
                      .val,
                  (unsigned)dut->ldut.tile_prci_domain.tile_reset_domain
                      .boom_tile.core.rob.__v2_state_rob_exception[7]
                      .val,
                  model_head, (unsigned)model_core.rob.val[model_head],
                  (unsigned)model_core.rob.busy[model_head],
                  (unsigned)model_core.rob.unsafe[model_head],
                  (unsigned)model_core.rob.exception[model_head],
                  (unsigned)model_core.rob.val[7],
                  (unsigned)model_core.rob.busy[7],
                  (unsigned)model_core.rob.unsafe[7],
                  (unsigned)model_core.rob.exception[7],
                  (unsigned)model_core.rob_head_start,
                  (unsigned)model_core.rob_busy_start[
                      model_core.rob_head_start & 31u]);
          const auto& rtl_lsu =
              dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.lsu;
          const auto& model_ld1 = model_core.lsu.ldq[1];
          const auto& model_st0 = model_core.lsu.stq[0];
          fprintf(stderr,
                  "[LSUDBG] c=%llu "
                  "rtl(search=%u lq=%llu a=%llx canf=%u am0=%u fi=%llu "
                  "mf=%u wb=%u/%llu/%llu "
                  "ld1=%u/%u:a%llx:dep%llx:y%llu "
                  "st0=%u/%u/%u:a%llx:z%u:f%u:m%u "
                  "sc=%u/%u ctr=%llu clr=%u/%llu) "
                  "model(search=%u/%u/%u lq=%d fwd=%u/%u/%u "
                  "ld1=%u/%u:a%llx:dep%x:y%u "
                  "st0=%u/%u/%u:a%llx:z%u:f%u:m%u "
                  "ctr=%u clr1=%u/%u clr2=%u/%u)\n",
                  (unsigned long long)cycle,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$do_ld_search_0[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$lcam_ldq_idx_0[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$lcam_addr_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_forward_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_0[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$forwarding_idx_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$mem_forward_valid_0[0].val,
                  (unsigned)rtl_lsu.wb_forward_valid_0[0].val,
                  (unsigned long long)rtl_lsu.wb_forward_ldq_idx_0[0].val,
                  (unsigned long long)rtl_lsu.wb_forward_stq_idx_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_bits_addr_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_bits_addr_bits[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_bits_st_dep_mask[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_bits_youngest_stq_idx[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_bits_addr_valid[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_bits_data_valid[0].val,
                  (unsigned long long)rtl_lsu.stq_0_bits_addr_bits[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_bits_uop_mem_size[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_bits_uop_is_fence[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_0_bits_uop_is_amo[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_fire_store_commit_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$will_fire_store_commit_0[0].val,
                  (unsigned long long)rtl_lsu.REG_63[0].val,
                  (unsigned)rtl_lsu.clr_bsy_valid_0[0].val,
                  (unsigned long long)rtl_lsu.clr_bsy_rob_idx_0[0].val,
                  (unsigned)model_core.lcam_incoming_s1,
                  (unsigned)model_core.omir.fired_load_wakeup_r,
                  (unsigned)model_core.lcam_fired_s1,
                  (int)model_core.lcam_ldq_s1,
                  (unsigned)model_core.omir.wb_fwd_valid_r,
                  (unsigned)model_core.omir.wb_fwd_ldq_r,
                  (unsigned)model_core.omir.wb_fwd_stq_r,
                  (unsigned)model_ld1.valid,
                  (unsigned)model_ld1.addr_valid,
                  (unsigned long long)model_ld1.addr,
                  (unsigned)model_ld1.st_dep_mask,
                  (unsigned)model_ld1.youngest_stq_idx,
                  (unsigned)model_st0.valid,
                  (unsigned)model_st0.addr_valid,
                  (unsigned)model_st0.data_valid,
                  (unsigned long long)model_st0.addr,
                  (unsigned)model_st0.uop.mem_size,
                  (unsigned)model_st0.uop.is_fence,
                  (unsigned)model_st0.uop.is_amo,
                  (unsigned)model_core.store_blocked_counter,
                  (unsigned)model_core.store_clr_bsy_s1.v,
                  (unsigned)model_core.store_clr_bsy_s1.rob_idx,
                  (unsigned)model_core.store_clr_bsy_s2.v,
                  (unsigned)model_core.store_clr_bsy_s2.rob_idx);
          fprintf(stderr, "[LDQDBG] c=%llu head rtl=%llu model=%u\n",
                  (unsigned long long)cycle,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_head[0].val,
                  (unsigned)model_core.lsu.ldq_head);
          fprintf(stderr,
                  "[LDQGATE] c=%llu tlb(ex=%u mem=%u cache=%u) "
                  "base=%u after=%u%u%u%u%u%u%u final=%u ld1uc=%u/%u\n",
                  (unsigned long long)cycle,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$exe_tlb_uncacheable_0[0].val,
                  (unsigned)rtl_lsu.mem_tlb_uncacheable_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$dtlb$io_resp_0_cacheable[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_T_1168[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_8843[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_8924[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9005[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9086[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9167[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9248[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$_GEN_9329[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$can_forward_0[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_1_bits_addr_is_uncacheable[0].val,
                  (unsigned)model_core.lsu.ldq[1].addr_is_uncacheable);
          const unsigned rtl_st_matches =
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_0[0].val << 0) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_1[0].val << 1) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_2[0].val << 2) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_3[0].val << 3) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_4[0].val << 4) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_5[0].val << 5) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_6[0].val << 6) |
              ((unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldst_addr_matches_0_7[0].val << 7);
          fprintf(stderr,
                  "[LCAMALL] c=%llu kill=%u matches=%02x "
                  "rtl-ld5(dep=%llx y=%llu) model-ld5(dep=%x y=%u)\n",
                  (unsigned long long)cycle,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$io_dmem_s1_kill_0[0].val,
                  rtl_st_matches,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_5_bits_st_dep_mask[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_5_bits_youngest_stq_idx[0].val,
                  (unsigned)model_core.lsu.ldq[5].st_dep_mask,
                  (unsigned)model_core.lsu.ldq[5].youngest_stq_idx);
#define PRINT_STQ_ENTRY(I)                                               \
          do {                                                           \
            const auto& model_stq = model_core.lsu.stq[I];              \
            fprintf(stderr,                                              \
                    "[STQDBG] %d rtl(v=%u av=%u a=%llx sz=%u "         \
                    "f=%u amo=%u) model(v=%u av=%u a=%llx sz=%u "      \
                    "f=%u amo=%u)\n",                                  \
                    I,                                                    \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_##I##_valid[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_##I##_bits_addr_valid[0].val, \
                    (unsigned long long)dut->ldut.tile_prci_domain       \
                        .tile_reset_domain.boom_tile.lsu                 \
                        .stq_##I##_bits_addr_bits[0].val,                 \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_##I##_bits_uop_mem_size[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_##I##_bits_uop_is_fence[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$stq_##I##_bits_uop_is_amo[0].val, \
                    (unsigned)model_stq.valid,                            \
                    (unsigned)model_stq.addr_valid,                       \
                    (unsigned long long)model_stq.addr,                   \
                    (unsigned)model_stq.uop.mem_size,                     \
                    (unsigned)model_stq.uop.is_fence,                     \
                    (unsigned)model_stq.uop.is_amo);                      \
          } while (false)
          PRINT_STQ_ENTRY(0);
          PRINT_STQ_ENTRY(1);
          PRINT_STQ_ENTRY(2);
          PRINT_STQ_ENTRY(3);
          PRINT_STQ_ENTRY(4);
          PRINT_STQ_ENTRY(5);
          PRINT_STQ_ENTRY(6);
          PRINT_STQ_ENTRY(7);
#undef PRINT_STQ_ENTRY
#define PRINT_LDQ_ENTRY(I, NACK_REG)                                      \
          do {                                                            \
            const auto& model_ldq = model_core.lsu.ldq[I];                \
            fprintf(stderr,                                               \
                    "[LDQDBG] %d rtl(v=%u av=%u a=%llx sz=%u "           \
                    "ex=%u ok=%u obs=%u uc=%u s1=%u nack=%u/%u) "        \
                    "model(v=%u av=%u a=%llx sz=%u ex=%u ok=%u "         \
                    "obs=%u)\n",                                         \
                    I,                                                     \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_valid[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_addr_valid[0].val, \
                    (unsigned long long)                                  \
                        _s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_addr_bits[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_uop_mem_size[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_executed[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_succeeded[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_observed[0].val, \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$ldq_##I##_bits_addr_is_uncacheable[0].val, \
                    (unsigned)rtl_lsu.s1_executing_loads_##I[0].val,      \
                    (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$lsu$nacking_loads_##I[0].val, \
                    (unsigned)rtl_lsu.REG_##NACK_REG[0].val,              \
                    (unsigned)model_ldq.valid,                             \
                    (unsigned)model_ldq.addr_valid,                        \
                    (unsigned long long)model_ldq.addr,                    \
                    (unsigned)model_ldq.uop.mem_size,                      \
                    (unsigned)model_ldq.executed,                          \
                    (unsigned)model_ldq.succeeded,                         \
                    (unsigned)model_ldq.observed);                         \
          } while (false)
          PRINT_LDQ_ENTRY(0, 21);
          PRINT_LDQ_ENTRY(1, 23);
          PRINT_LDQ_ENTRY(2, 25);
          PRINT_LDQ_ENTRY(3, 27);
          PRINT_LDQ_ENTRY(4, 29);
          PRINT_LDQ_ENTRY(5, 31);
          PRINT_LDQ_ENTRY(6, 33);
          PRINT_LDQ_ENTRY(7, 35);
#undef PRINT_LDQ_ENTRY
          fprintf(stderr,
                  "[MW] c=%llu wv=%d widx=%llu wway=%llx wcoh=%llu wtag=%llx "
                  "g1=%d rv=%d ridx=%llu lsur=%d rpv=%d rpa=%llx m1rp=%d\n",
                  (unsigned long long)cycle,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$io_out_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$io_out_bits_idx[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$io_out_bits_way_en[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$io_out_bits_data_coh_state[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$io_out_bits_data_tag[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaWriteArb$grant_1[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaReadArb$io_out_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$metaReadArb$io_out_bits_req_0_idx[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$io_lsu_req_ready[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$replay_arb$io_out_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$replay_arb$io_out_bits_addr[0].val,
                  (int)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$mshrs_1$io_replay_valid[0].val);
          const auto& mm0 = model_dcache.mshr_for_diagnostic(0);
          const auto& mm1 = model_dcache.mshr_for_diagnostic(1);
          fprintf(stderr,
                  "[RPQ] c=%llu rtl-sdq=%llx "
                  "r0(st=%llu req=%llx h=%llu t=%llu full=%llu port=%llu) "
                  "m0(st=%u req=%llx h=%zu t=%zu n=%zu full=%d port=%u) "
                  "r1(st=%llu req=%llx h=%llu t=%llu full=%llu port=%llu) "
                  "m1(st=%u req=%llx h=%zu t=%zu n=%zu full=%d port=%u) "
                  "model-sdq=%x\n",
                  (unsigned long long)cycle,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.sdq_val[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_0.state[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_0.req_addr[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_0.rpq.value_1[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_0.rpq.value[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_0.rpq.maybe_full[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$mshrs_0$rpq$ram_sdq_id$MPORT_1[0].val,
                  static_cast<unsigned>(mm0.state),
                  (unsigned long long)mm0.request.address,
                  mm0.rpq_head, mm0.rpq_tail, mm0.rpq_count,
                  static_cast<int>(mm0.rpq_maybe_full),
                  static_cast<unsigned>(mm0.rpq_sdq_id[mm0.rpq_head]),
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_1.state[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_1.req_addr[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_1.rpq.value_1[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_1.rpq.value[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.mshrs.mshrs_1.rpq.maybe_full[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$mshrs$mshrs_1$rpq$ram_sdq_id$MPORT_1[0].val,
                  static_cast<unsigned>(mm1.state),
                  (unsigned long long)mm1.request.address,
                  mm1.rpq_head, mm1.rpq_tail, mm1.rpq_count,
                  static_cast<int>(mm1.rpq_maybe_full),
                  static_cast<unsigned>(mm1.rpq_sdq_id[mm1.rpq_head]),
                  model_dcache.sdq_val_oracle());
          const auto& mwb = model_dcache.writeback_for_diagnostic();
          const auto& mrd = model_dcache.raw_data_for_diagnostic();
          fprintf(stderr,
                  "[WB] c=%llu rtl(st=%llu cnt=%llu v=%u addr=%llx "
                  "way=%llx outway=%llx lsu-rdy=%u) "
                  "model(st=%u cnt=%u addr=%x owner=%u way=%u "
                  "raw=%u raddr=%llx rway=%x)\n",
                  (unsigned long long)cycle,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.wb.state[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.wb.data_req_cnt[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$wb$io_data_req_valid[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$wb$io_data_req_bits_addr[0].val,
                  (unsigned long long)dut->ldut.tile_prci_domain.tile_reset_domain.boom_tile.dcache.wb.req_way_en[0].val,
                  (unsigned long long)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$dataReadArb$io_out_bits_req_0_way_en[0].val,
                  (unsigned)_s_ldut$tile_prci_domain$tile_reset_domain$boom_tile$dcache$dataReadArb$io_in_2_ready[0].val,
                  static_cast<unsigned>(mwb.state),
                  static_cast<unsigned>(mwb.read_count), mwb.address,
                  static_cast<unsigned>(mwb.owner),
                  static_cast<unsigned>(mwb.way),
                  static_cast<unsigned>(mrd.valid),
                  (unsigned long long)mrd.address,
                  static_cast<unsigned>(model_dcache.raw_data_way_mask_for_diagnostic()));
        }
#endif  // CHISA_LEGACY_CORE_DIAG
#endif  // small-tap diagnostics
      }
      if (options.quiesce_debug_at_entry) {
        if (!entry_seen && target_entry_reached(model, entry)) {
          entry_seen = true;
          entry_cycle = stepper.cycle();
        }
        if (entry_seen && !debug_shutdown_started &&
            !model.backend().core().csr().debug &&
            model_debug->at_idle_nop_boundary() &&
            stepper.dtm_adapter().at_idle_nop_boundary()) {
          model_debug->begin_dmi_quiesce();
          stepper.dtm_adapter().begin_dmi_quiesce();
          debug_shutdown_started = true;
          debug_shutdown_cycle = stepper.cycle();
        }
        if (debug_shutdown_started && !roi_started &&
            model_debug->dmi_quiesced() &&
            stepper.dtm_adapter().dmi_quiesced() &&
            model.debug_roi_quiescent()) {
          probes.begin_measurement();
          observer.begin_measurement();
          roi_started = true;
          roi_start_cycle = stepper.cycle();
        }
        if (roi_started && options.roi_cycles != 0 &&
            stepper.cycle() - roi_start_cycle >= options.roi_cycles) {
          roi_complete = true;
          break;
        }
      }
      if (!result.io_success && (cycle < options.reset_cycles || !dtm->done()))
        continue;
      success = true;
      break;
    }

    probes.summary();
    const std::size_t modeled = probes.modeled_stream_count();
    const std::size_t state_derived = probes.state_derived_stream_count();
    const std::size_t profile_assumptions =
        probes.profile_assumption_stream_count();
    const std::size_t structural_constants =
        probes.structural_constant_stream_count();
    const bool timed_out =
        !success && !roi_complete && stepper.cycle() == run_max_cycles;
    const bool zero_model = modeled == 0;
    const bool clean = observer.clean() && probes.unknown_key_count() == 0 &&
                       !boundary_mismatch;
    const uint64_t expected_comparison_start = options.quiesce_debug_at_entry
        ? (roi_started ? roi_start_cycle : stepper.cycle()) : options.reset_cycles;
    const bool oracle_coverage_complete = probe_contract_known && compared_cycles != 0 &&
        comparison_start_cycle == expected_comparison_start &&
        stepper.cycle() > expected_comparison_start &&
        compared_cycles == stepper.cycle() - expected_comparison_start;
    const char* status = zero_model ? "unmodeled"
                         : clean ? (!oracle_coverage_complete ? "unverified"
                                    : roi_complete ? "roi-pass"
                                    : success ? "pass" : "max-cycles")
                                 : "mismatch";
    std::printf(
        "SYSTEM_MODEL_LOCKSTEP status=%s cycles=%" PRIu64
        " manifest=%zu modeled=%zu state_derived=%zu profile=%zu structural=%zu"
        " real=%ld state_real=%ld profile_real=%ld structural_real=%ld"
        " boundary_real=%u"
        " sentinels=%" PRIu64
        " step_failures=%" PRIu64 " dtm_exit=%d\n",
        status, stepper.cycle(), probes.registered_stream_count(), modeled,
        state_derived, profile_assumptions, structural_constants,
        probes.real_mismatch_count(), probes.state_derived_mismatch_count(),
        probes.profile_assumption_mismatch_count(),
        probes.structural_constant_mismatch_count(),
        static_cast<unsigned>(boundary_mismatch),
        observer.sentinel_failures(),
        observer.step_failures(), dtm->exit_code());
    // Quiescing FESVR deliberately stops its host work. Even a resulting
    // dtm->done()/status=pass is ROI termination, not a completed program.
    const bool program_done = success && !options.quiesce_debug_at_entry;
    const bool initialization_compared = !options.quiesce_debug_at_entry &&
        oracle_coverage_complete;
    const std::int64_t observed_oracle_mismatches =
        static_cast<std::int64_t>(probes.real_mismatch_count()) +
        static_cast<std::int64_t>(probes.phase_mismatch_count());
    // Existing seam checks are optional internal audits, not a complete
    // independent DMI/io_success boundary comparison. Preserve known seam
    // failures, but report unknown (-1), never zero, for the missing boundary
    // obligation. A complete-program gate must reject consumer=incomplete.
    std::printf(
        "MODEL_VALIDATION schema=1 comparison_start_cycle=%" PRId64
        " compared_cycles=%" PRIu64 " compared_windows=%" PRIu64
        " streams=%zu oracle_mismatches=%" PRId64
        " boundary_mismatches=%d initialization_compared=%u consumer=%s"
        " program_done=%u program_exit=%d boundary_coverage=unavailable\n",
        compared_cycles ? static_cast<std::int64_t>(comparison_start_cycle) : -1,
        compared_cycles, compared_cycles, tap_streams,
        observed_oracle_mismatches || compared_cycles ? observed_oracle_mismatches : -1,
        boundary_mismatch ? 1 : -1, static_cast<unsigned>(initialization_compared),
        probes.active() ? "incomplete" : "off", static_cast<unsigned>(program_done),
        program_done ? dtm->exit_code() : -1);
    if (options.quiesce_debug_at_entry) {
      std::printf(
          "DEBUG_ROI entry_seen=%u entry_cycle=%" PRIu64
          " shutdown_started=%u shutdown_cycle=%" PRIu64
          " roi_started=%u roi_start_cycle=%" PRIu64
          " roi_complete=%u roi_cycles=%" PRIu64
          " sampled_cycles=%llu\n",
          static_cast<unsigned>(entry_seen), entry_cycle,
          static_cast<unsigned>(debug_shutdown_started),
          debug_shutdown_cycle, static_cast<unsigned>(roi_started),
          roi_start_cycle, static_cast<unsigned>(roi_complete),
          roi_started ? stepper.cycle() - roi_start_cycle : 0,
          probes.sampled_cycle_count());
    }
    std::printf("COLD_RTL system_bus eval=%" PRIu64 "\n",
                model.fabric().system_bus_eval_count());
    std::printf("COLD_RTL axi_fragmenter eval=%" PRIu64
                " skipped=%" PRIu64 "\n",
                model.fabric().axi_fragmenter_eval_count(),
                model.fabric().axi_fragmenter_skipped_count());
    std::printf("COLD_RTL axi_buffer eval=%" PRIu64
                " skipped=%" PRIu64 "\n",
                model.fabric().axi_buffer_eval_count(),
                model.fabric().axi_buffer_skipped_count());
    std::printf(
        "COLD_RTL fdivsqrt eval=%" PRIu64
        " skipped=%" PRIu64 " active=%u\n",
        model.fabric().fdivsqrt_eval_count(),
        model.fabric().fdivsqrt_skipped_count(),
        static_cast<unsigned>(model.fabric().fdivsqrt_active()));
    std::printf(
        "COLD_RTL fpu eval=%" PRIu64 " skipped=%" PRIu64 " active=%u\n",
        model.fabric().fpu_eval_count(),
        model.fabric().fpu_skipped_count(),
        static_cast<unsigned>(model.fabric().fpu_active()));

    if (zero_model) return options.allow_zero_model ? 0 : 3;
    if (!clean) return 2;
    if (!oracle_coverage_complete) return 5;
    if (roi_complete) return 0;
    if (success) return dtm->exit_code();
    return timed_out && options.allow_timeout ? 0 : 4;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "system model lockstep error: %s\n", error.what());
    return 2;
  }
}
