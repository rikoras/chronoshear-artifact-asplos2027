// Live sidecar bring-up harness (v0, single-thread window interleave).
//
// The producer half steps the SystemGuider with its own fesvr DTM and fills
// one oracle block per window through the W-width SystemOracleWriter; the
// consumer half is the wide differential loop driving the generated W-lane
// TestHarness from the producer's per-cycle DMI records, verify on.
//
// Every oracle lane comes from the model through the writer; there is no
// trace or reference input. DMI feedback, io_success and RTL assertions are
// checked against the live producer. Report-only mode retains mismatch
// counts; it must not be interpreted as a zero-mismatch qualification.
#include <immintrin.h>
#include <fesvr/dtm.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <utility>
#include "terminal_window.h"
#if defined(CHISA_WINDOW_TIMELINE)
#include "window_timeline.h"
#define CHISA_TIMELINE(window, ...) do { \
  auto& trace_ptr=::chisa::boom_repcut::window_timeline; \
  if (trace_ptr && trace_ptr->selected(window)) { \
    auto& timeline=*trace_ptr;const auto row=timeline.row(window); \
    using TraceClock=::chisa::boom_repcut::WindowTimeline; \
    __VA_ARGS__; \
  } \
} while(false)
#else
#define CHISA_TIMELINE(...) ((void)0)
#endif
#if defined(CHISA_CPU_SAMPLING)
#include "../../../scripts/paper_experiments/paper_perf.h"
#endif
#ifdef CHISA_PHASE_TIMERS
#include <x86intrin.h>
#include "phase_sub.h"
#endif
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "TestHarness.h"
#if defined(CHISA_CONSUMER_ARCHITECTURE)
#include "consumer_architecture.h"
#if __has_include("consumer_architecture_owners.h")
#include "consumer_architecture_owners.h"
#if CHISA_PARTITION_ARCHITECTURE_SCHEMA == 1
#include "partition_architecture.h"
#define CHISA_HAS_PARTITION_ARCHITECTURE 1
#endif
#endif
#endif

#include "extmodule_adapters.h"
#include "extmodule_bindings.h"
#include "fesvr_debug_bootstrap.h"
#include "reference_oracle_trace.h"
#include "system_guider.h"
#if defined(CHISA_WIDE_MODEL)
#include "reference_model/native_system_oracle_writer.inc"
#elif defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#if defined(CHISA_LARGE_WIDTH_VARIANT)
#include "large_system_oracle_writer.inc"
#elif CHISA_CONSUMER_WIDTH == 16
#include "generated/system_oracle_writer_large_w16.inc"
#elif CHISA_CONSUMER_WIDTH == 4
#include "generated/system_oracle_writer_large.inc"
#else
#error "Generate a Large writer layout and define CHISA_LARGE_WIDTH_VARIANT"
#endif
#elif defined(CHISA_SMALL_WIDTH_VARIANT)
#include "reference_model/small_system_oracle_writer.inc"
#elif CHISA_CONSUMER_WIDTH == 32
#include "generated/system_oracle_writer_w32.inc"
#elif CHISA_CONSUMER_WIDTH == 16
#include "generated/system_oracle_writer_w16.inc"
#else
#include "generated/system_oracle_writer.inc"
#endif
#include "export_thread.h"
#include "oracle_delta_codec.h"
#include "oracle_image_codec.h"
#include "joint_executor.h"
#include "parallel_decode.h"
#include "partition_ready.h"
#if defined(CHISA_PARTITION_DELIVERY_HEADER)
#include CHISA_PARTITION_DELIVERY_HEADER
#endif
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
#include "overlap_ready_images.h"
#endif
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
#include "external_dram_adapter.h"
#endif
#if defined(CHISA_ADDITIONAL_ORACLE_HEADER) && defined(CHISA_SMALL_ORACLE_ADDITIONS)
#error "select only one supplemental oracle adapter"
#endif
#if defined(CHISA_ADDITIONAL_ORACLE_HEADER)
// The supplied header defines boom_system::additional_oracles with kCount,
// Snapshot, capture(PublishFn) and inject(), using model sources only.
#include CHISA_ADDITIONAL_ORACLE_HEADER
#define CHISA_HAS_ADDITIONAL_ORACLES 1
#elif defined(CHISA_SMALL_ORACLE_ADDITIONS)
#include "small_additional_oracles.h"
namespace chisa::boom_system {
namespace additional_oracles = small_additional_oracles;
}
#define CHISA_HAS_ADDITIONAL_ORACLES 1
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
static_assert(chisa::boom_system::dram_profile::kAdditionalRegisterStreams ==
              chisa::boom_system::additional_oracles::kCount,
              "additional model sources must exactly cover the consumer's added registers");
#endif

namespace {
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
// Keep the probe out of Options, the main stack frame and task captures.
// Altering those layouts can perturb the shared runtime's cache behavior.
std::string diagnostic_ready_image_path;
std::unique_ptr<chisa::boom_repcut::OverlapReadyImages> diagnostic_ready_images;
#endif

std::unique_ptr<TestHarness> make_kernel() {
#if defined(ESSENT_PARTITION_FACTORY)
  return std::unique_ptr<TestHarness>(chisa_new_partition_kernel());
#else
  return std::make_unique<TestHarness>();
#endif
}

// Waiting threads spin with the pause hint instead of sched_yield: a
// hyperthread sibling that hammers the yield syscall halves the throughput of
// the partition sharing its core, whereas pause hands the core's resources
// over (measured on the six-partition Ryzen placement: slow partitions ran
// at half the trace-replay speed while their fast siblings spun).
static inline void spin_wait_hint() {
  for (int i = 0; i < 32; ++i) _mm_pause();
}
// One half-window of the kernel. A partitioned header (ESSENT_PARTITIONS > 0)
// has no whole-DUT eval: every partition runs in turn on this one instance,
// which is exact because a partition reads the registers of the others only
// through oracle lanes. This is the correctness harness for partition-cut
// lanes, not the threaded consumer.
template <class Dut>
auto eval_half(Dut& dut, bool forward, bool done_reset, int)
    -> decltype(dut.eval_partition(0, true, true, false, true), void()) {
  // Every partition's reverse half advances the instance's window cursor
  // (oracle_cycle, oracle_win_base) as if it were the only one: rewind it
  // before each partition and keep a single advance.
  const auto cycle0 = dut.oracle_cycle;
  const auto base0 = dut.oracle_win_base;
  auto cycle1 = cycle0;
  auto base1 = base0;
  for (int p = 0; p < Dut::ESSENT_PARTITIONS; ++p) {
    dut.oracle_cycle = cycle0;
    dut.oracle_win_base = base0;
    dut.eval_partition(p, forward, true, false, done_reset);
    if (p == 0) { cycle1 = dut.oracle_cycle; base1 = dut.oracle_win_base; }
  }
  dut.oracle_cycle = cycle1;
  dut.oracle_win_base = base1;
}
template <class Dut>
void eval_half(Dut& dut, bool forward, bool done_reset, long) {
  if (forward) dut.eval_forward(true, false, done_reset);
  else dut.eval_reverse(true, false, done_reset);
}
// One partition of one half-window on its own instance (--partition-threads).
template <class Dut>
auto eval_one_partition(Dut& dut, int p, bool forward, bool done_reset, int)
    -> decltype(dut.eval_partition(0, true, true, false, true), void()) {
  dut.eval_partition(p, forward, true, false, done_reset);
}
template <class Dut>
void eval_one_partition(Dut&, int, bool, bool, long) {
  throw std::runtime_error("this kernel was emitted without partitions");
}
}  // namespace
namespace {

using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::IsolatedAtomic;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::ReferenceOracleCycleRecord;
using chisa::boom_system::SystemGuider;
using chisa::boom_repcut::assign_port;
using chisa::boom_repcut::port_value;
using chisa::boom_repcut::simdtm_ports;
using chisa::boom_repcut::initialize_plusarg_readers;

#ifndef CHISA_CONSUMER_WIDTH
#error "define CHISA_CONSUMER_WIDTH"
#endif
constexpr unsigned kW = CHISA_CONSUMER_WIDTH;
static_assert(kW==chisa::boom_system::kSystemOracleWidth,
              "consumer width and generated writer width must agree");
constexpr unsigned kWindow = 2 * kW;
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
constexpr std::size_t kConsumerOracleBlockBytes =
    chisa::boom_system::dram_profile::kBlockBytes;
#if defined(CHISA_DRAM_PROFILE_CONSUMER_STREAM_COUNT)
constexpr std::size_t kConsumerOracleStreams =
    CHISA_DRAM_PROFILE_CONSUMER_STREAM_COUNT;
#else
constexpr std::size_t kConsumerOracleStreams =
    chisa::boom_system::kSystemOracleModeledStreams +
    std::size(chisa::boom_system::dram_profile::kAccessStreams)
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
    + chisa::boom_system::additional_oracles::kCount
#endif
    ;
#endif
#else
constexpr std::size_t kConsumerOracleBlockBytes =
    chisa::boom_system::kSystemOracleBlockBytes;
constexpr std::size_t kConsumerOracleStreams =
    chisa::boom_system::kSystemOracleModeledStreams;
#endif

struct Options {
  std::uint64_t max_cycles = 0;
  std::uint64_t reset_cycles = 32;
  bool eval_timing = false;
  bool skip_consumer = false;  // producer alone in the live process
  bool require_success = false;
  bool overlap = false;
  int consumer_cpu = -1, producer_cpu = -1, decoder_cpu = -1;
  // --producer-decode: the producer expands every window into a ring of
  // expansion buffers (copy-forward of the previous window, then decode) and
  // the consumer only points at its slot; the decode leaves the consumer.
  bool producer_decode = false;
  // --producer-decode-lanes=S: with --producer-decode, the producer expands
  // lanes [0,S) and the consumer lanes [S,N) of every window (0 = all on the
  // consumer, N = all on the producer). Balances the two threads.
  std::uint32_t producer_decode_lanes = 0xffffffffu;
  // --decode-thread: the whole expansion runs on a third thread between the
  // producer and the consumer (implies --producer-decode with every lane).
  bool decode_thread = false;
  // --export-offload: the oracle field resolution and block writing leave
  // the model's thread (ExportThread).  With --decode-thread the expander
  // thread does that work; otherwise the exporter runs its own thread.
  // Needs --overlap and producer-side expansion (the consumer must not read
  // a block before the worker sealed it).
  bool export_offload = false;
  // --image-transport: the producer ships one whole record image per cycle
  // (no change detection, no change lists) and the expander transposes the
  // 2W images of a window into the lane layout (oracle_image_codec.h).
  bool image_transport = false;
  // Transport of the oracle windows.  Image (whole record per cycle) is the
  // default: its decoder is a vectorized transpose (1.2k ns/cycle on the
  // Ryzen) whereas the row form's per-lane expansion costs 5.5k and the
  // producer gains nothing from writing fewer bytes (PLAN §18.3–18.5).
  // --row-transport: record rows that moved (kOracleRowLane); correct, kept
  // for machines where cross-core lines are expensive.  --delta-transport:
  // the legacy per-lane change list, which delivers predict-bound lanes one
  // position late (PLAN §18.1); also what --export-offload uses.
  bool row_transport = false;
  bool delta_transport = false;
  // --stage-image: the producer writes each record image into a small ring
  // that stays in its own L2; the decoder thread copies it into the window
  // block (needs --decode-thread and the image transport).
  bool stage_image = false;
  bool continue_oracle_mismatches = false;
  bool architecture_check = false;
  std::uint64_t mismatch_log_limit = 16;
  std::uint64_t timing_from = 0;  // first cycle counted by --eval-timing
  std::uint64_t timing_until = 0; // exclusive; zero selects max_cycles
  bool timed(std::uint64_t first) const {
    return first >= timing_from && first < timing_until;
  }
  std::string dump_path;          // --dump-blocks=FILE: every produced window
  int htif_start = -1;
  // --partition-threads: a partitioned kernel consumed by one thread and one
  // kernel instance per partition (the two-level parallel consumer);
  // --partition-cpus=a,b,... pins them; --check-partition=N names the
  // partition whose DMI/io_success outputs the harness checks.
  bool partition_threads = false;
  std::vector<int> partition_cpus;
  bool joint_execution = false;
  std::vector<int> joint_cpus{0, 1, 2, 3, 4, 5};
  std::vector<int> joint_partition_workers{4, 1, 2, 4, 5, 3};
  std::vector<int> joint_decode_workers{1, 2, 3};
  int joint_frontend_worker = 4;
  int joint_memory_worker = 5;
  bool joint_parallel_decode = true;
  bool joint_partition_ready = false;
  std::vector<int> joint_decode_priority;
  unsigned joint_decode_group_lanes=32;
  bool joint_decode_regroup=false;
  bool joint_decode_in_kernel = false;
  unsigned joint_model_budget = 4;
  int check_partition = 0;
  bool joint_allow_smt = false;
  std::size_t joint_physical_cores = 0;
  unsigned joint_source_ahead = 0;
  unsigned joint_idle_pauses = 1;
};

[[noreturn]] void usage(const char* p, const char* e = nullptr) {
  if (e) std::fprintf(stderr, "%s: %s\n", p, e);
  std::fprintf(stderr,
               "usage: %s --max-cycles=N [--reset-cycles=N] [--overlap] "
               "[--eval-timing] [--timing-from=N] [--timing-until=N] [--dump-blocks=FILE] [--producer-decode] [--decode-thread] "
               "[--export-offload] [--image-transport] [--require-success] "
               "[--continue-oracle-mismatches] [--mismatch-log-limit=N] [--architecture-check] "
               "[--consumer-cpu=N] [--producer-cpu=N] [--decoder-cpu=N] "
               "[--execution=joint --joint-cpus=0,1,2,3,4,5 --joint-partition-workers=4,1,2,4,5,3] "
               "[--joint-frontend-worker=4 --joint-memory-worker=5 --joint-decode-workers=1,2,3] "
               "[--joint-serial-decode] [--joint-allow-smt] [--joint-partition-ready] [--joint-decode-priority=1,2] "
               "[--joint-decode-group-lanes=32] [--joint-decode-regroup] "
               "-- BINARY...\n", p);
  std::exit(2);
}

std::pair<int, int> physical_core(int cpu) {
  const std::string prefix = "/sys/devices/system/cpu/cpu" + std::to_string(cpu) + "/topology/";
  int package = -1, core = -1;
  if (!(std::ifstream(prefix + "physical_package_id") >> package) ||
      !(std::ifstream(prefix + "core_id") >> core))
    throw std::runtime_error("CPU topology unavailable for CPU " + std::to_string(cpu));
  return {package, core};
}

bool bind_current_thread(const char* role, int cpu) {
  if (cpu < 0) return true;  // Preserve the inherited affinity when omitted.
  cpu_set_t requested, actual;
  CPU_ZERO(&requested);
  CPU_SET(cpu, &requested);
  int error = pthread_setaffinity_np(pthread_self(), sizeof(requested), &requested);
  if (!error) error = pthread_getaffinity_np(pthread_self(), sizeof(actual), &actual);
  if (error) {
    std::fprintf(stderr, "LIVE_THREAD_AFFINITY status=fail role=%s requested_cpu=%d error=%s\n",
                 role, cpu, std::strerror(error));
    return false;
  }
  if (CPU_COUNT(&actual) != 1 || !CPU_ISSET(cpu, &actual)) {
    std::fprintf(stderr, "LIVE_THREAD_AFFINITY status=fail role=%s requested_cpu=%d error=affinity-not-applied\n",
                 role, cpu);
    return false;
  }
  // Topology was checked before any worker started; reporting cannot turn a
  // worker exception into std::terminate while the consumer waits on it.
  try {
    const auto core = physical_core(cpu);
    std::fprintf(stderr, "LIVE_THREAD_AFFINITY status=applied role=%s tid=%ld requested_cpu=%d"
                 " actual_cpu=%d allowed_count=1 package=%d core=%d\n",
                 role, long(::syscall(SYS_gettid)), cpu, ::sched_getcpu(), core.first, core.second);
  } catch (const std::exception& e) {
    std::fprintf(stderr, "LIVE_THREAD_AFFINITY status=fail role=%s requested_cpu=%d error=%s\n",
                 role, cpu, e.what());
    return false;
  }
  return true;
}

Options parse(int argc, char** argv) {
  Options o;
  for (int i = 1; i < argc; ++i) {
    const std::string a(argv[i]);
    if (a == "--") { o.htif_start = i + 1; break; }
    if (a.rfind("--max-cycles=", 0) == 0) { o.max_cycles = std::stoull(a.substr(13)); continue; }
    if (a.rfind("--reset-cycles=", 0) == 0) { o.reset_cycles = std::stoull(a.substr(15)); continue; }
    if (a == "--eval-timing") { o.eval_timing = true; continue; }
    if (a == "--skip-consumer") { o.skip_consumer = true; continue; }
    if (a == "--require-success") { o.require_success = true; continue; }
    if (a.rfind("--timing-from=", 0) == 0) { o.timing_from = std::stoull(a.substr(14)); continue; }
    if (a.rfind("--timing-until=", 0) == 0) { o.timing_until = std::stoull(a.substr(15)); continue; }
    if (a.rfind("--dump-blocks=", 0) == 0) { o.dump_path = a.substr(14); continue; }
    if (a == "--overlap") { o.overlap = true; continue; }
    const auto parse_cpu = [&](const std::string& text) {
      std::size_t used = 0;
      const int cpu = std::stoi(text, &used);
      if (used != text.size() || cpu < 0 || cpu >= CPU_SETSIZE)
        usage(argv[0], "thread CPU must be a nonnegative supported CPU index");
      return cpu;
    };
    if (a.rfind("--consumer-cpu=", 0) == 0) { o.consumer_cpu = parse_cpu(a.substr(15)); continue; }
    if (a.rfind("--producer-cpu=", 0) == 0) { o.producer_cpu = parse_cpu(a.substr(15)); continue; }
    if (a.rfind("--decoder-cpu=", 0) == 0) { o.decoder_cpu = parse_cpu(a.substr(14)); continue; }
    if (a == "--producer-decode") { o.producer_decode = true; continue; }
    if (a == "--decode-thread") { o.producer_decode = true; o.decode_thread = true; continue; }
    if (a == "--stage-image") { o.stage_image = true; continue; }
    if (a == "--export-offload") { o.export_offload = true; continue; }
    if (a == "--image-transport") { o.image_transport = true; continue; }
    if (a == "--row-transport") { o.row_transport = true; continue; }
    if (a == "--delta-transport") { o.delta_transport = true; continue; }
    if (a == "--continue-oracle-mismatches") { o.continue_oracle_mismatches = true; continue; }
    if (a == "--architecture-check") { o.architecture_check = true; continue; }
    if (a.rfind("--mismatch-log-limit=", 0) == 0) {
      o.mismatch_log_limit = std::stoull(a.substr(21)); continue;
    }
    if (a.rfind("--producer-decode-lanes=", 0) == 0) {
      o.producer_decode = true;
      o.producer_decode_lanes = static_cast<std::uint32_t>(std::stoul(a.substr(24)));
      continue;
    }
    if (a == "--partition-threads") { o.partition_threads = true; continue; }
    if (a == "--execution=joint") { o.joint_execution = true; continue; }
    if (a == "--execution=sidecar") { o.joint_execution = false; continue; }
    if (a == "--joint-serial-decode") { o.joint_parallel_decode = false; continue; }
    if (a == "--joint-parallel-decode") { o.joint_parallel_decode = true; continue; }
    if (a.rfind("--joint-frontend-worker=", 0) == 0) {
      o.joint_frontend_worker = parse_cpu(a.substr(a.find('=') + 1)); continue;
    }
    if (a.rfind("--joint-memory-worker=", 0) == 0) {
      o.joint_memory_worker = parse_cpu(a.substr(a.find('=') + 1)); continue;
    }
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
    if (a.rfind("--diagnostic-ready-images=", 0) == 0) {
      diagnostic_ready_image_path = a.substr(a.find('=') + 1);
      if (diagnostic_ready_image_path.empty()) usage(argv[0], "empty diagnostic image path");
      continue;
    }
#endif
    if (a == "--joint-decode-in-kernel") { o.joint_decode_in_kernel = true; continue; }
    if (a == "--joint-partition-ready") { o.joint_partition_ready = true; continue; }
    if (a == "--joint-decode-regroup") { o.joint_decode_regroup = true; continue; }
    if (a.rfind("--joint-decode-group-lanes=",0)==0) {
      o.joint_decode_group_lanes=std::stoul(a.substr(a.find('=')+1));
      if (o.joint_decode_group_lanes<8 || o.joint_decode_group_lanes>256)
        usage(argv[0],"joint decode group lanes must be 8..256");
      continue;
    }
    if (a.rfind("--joint-model-budget=", 0) == 0) {
      o.joint_model_budget = std::stoul(a.substr(a.find('=')+1));
      if (o.joint_model_budget < 1 || o.joint_model_budget > 8) usage(argv[0], "joint model budget must be 1 through 8");
      continue;
    }
    if (a.rfind("--joint-cpus=", 0) == 0 || a.rfind("--joint-partition-workers=", 0) == 0 ||
        a.rfind("--joint-decode-workers=", 0) == 0 || a.rfind("--joint-decode-priority=", 0) == 0) {
      const bool cpus = a.rfind("--joint-cpus=", 0) == 0;
      const bool decode = a.rfind("--joint-decode-workers=", 0) == 0;
      const bool priority = a.rfind("--joint-decode-priority=", 0) == 0;
      auto& values = cpus ? o.joint_cpus : decode ? o.joint_decode_workers :
          priority ? o.joint_decode_priority : o.joint_partition_workers;
      values.clear();
      const std::string rest = a.substr(a.find('=') + 1);
      for (std::size_t start = 0; start <= rest.size();) {
        const auto comma = rest.find(',', start);
        values.push_back(parse_cpu(rest.substr(start, comma == std::string::npos ? comma : comma-start)));
        if (comma == std::string::npos) break;
        start = comma + 1;
      }
      continue;
    }
    if (a.rfind("--partition-cpus=", 0) == 0) {
      std::string rest = a.substr(17);
      for (std::size_t start = 0; start <= rest.size();) {
        const auto comma = rest.find(',', start);
        const auto item = rest.substr(start, comma == std::string::npos ? std::string::npos : comma - start);
        if (!item.empty()) o.partition_cpus.push_back(parse_cpu(item));
        if (comma == std::string::npos) break;
        start = comma + 1;
      }
      continue;
    }
    if (a.rfind("--check-partition=", 0) == 0) { o.check_partition = std::stoi(a.substr(18)); continue; }
    if (a == "--joint-allow-smt") { o.joint_allow_smt = true; continue; }
    if (a.rfind("--joint-source-ahead=",0)==0) { o.joint_source_ahead=std::stoul(a.substr(21)); continue; }
    if (a.rfind("--joint-idle-pauses=",0)==0) {
      const auto count=std::stoul(a.substr(a.find('=')+1));
      if (count<1 || count>64) usage(argv[0],"joint idle pauses must be 1 through 64");
      o.joint_idle_pauses=static_cast<unsigned>(count);continue;
    }
    if (!a.empty() && a[0] == '+') continue;
    usage(argv[0], "unknown option");
  }
  if (o.htif_start < 0 || o.htif_start >= argc) usage(argv[0], "missing -- BINARY");
  if (o.joint_partition_ready || !o.joint_decode_priority.empty() || o.joint_decode_regroup || o.joint_decode_group_lanes!=32) {
#if !defined(CHISA_PARTITION_DELIVERY_HEADER)
    usage(argv[0], "partition delivery requires an audited build-time reader contract");
#endif
#if defined(CHISA_BOOM_EXTERNAL_DRAM) || defined(CHISA_HAS_ADDITIONAL_ORACLES)
    usage(argv[0], "partition delivery does not yet cover auxiliary oracle channels");
#endif
    if (!o.joint_execution || !o.joint_parallel_decode)
      usage(argv[0], "partition delivery requires joint parallel image expansion");
  }
  if (o.joint_execution) {
#if !defined(CHISA_WIDE_MODEL)
    usage(argv[0], "joint model tasks require the wide model");
#endif
    if (o.joint_cpus.size() < 6 || o.joint_partition_workers.size() != 6)
      usage(argv[0], "joint execution requires at least six CPUs and six partition owners");
    std::vector<std::pair<int,int>> joint_cores;
    std::vector<int> logical_cpus;
    for (int cpu : o.joint_cpus) {
      if (std::find(logical_cpus.begin(),logical_cpus.end(),cpu)!=logical_cpus.end())
        usage(argv[0], "joint CPUs must be distinct logical processors");
      logical_cpus.push_back(cpu);
      const auto core = physical_core(cpu);
      if (std::find(joint_cores.begin(), joint_cores.end(), core) != joint_cores.end()) {
        if (!o.joint_allow_smt) usage(argv[0], "joint CPUs must belong to distinct physical cores (or explicitly use --joint-allow-smt)");
      } else joint_cores.push_back(core);
    }
    o.joint_physical_cores=joint_cores.size();
    if (o.joint_physical_cores<6) usage(argv[0], "joint execution requires at least six physical cores");
    for (int worker : o.joint_partition_workers)
      if (worker < 1 || worker >= static_cast<int>(o.joint_cpus.size()))
        usage(argv[0], "joint partition owner must be a non-producer worker in --joint-cpus");
    for (int worker : o.joint_decode_workers)
      if (worker >= static_cast<int>(o.joint_cpus.size())) usage(argv[0], "joint decode owner exceeds worker count");
    if (o.joint_decode_workers.empty()) usage(argv[0], "joint execution requires a decode owner");
    if (o.joint_frontend_worker < 1 || o.joint_memory_worker < 1 ||
        o.joint_frontend_worker >= static_cast<int>(o.joint_cpus.size()) ||
        o.joint_memory_worker >= static_cast<int>(o.joint_cpus.size()) ||
        o.joint_frontend_worker == o.joint_memory_worker)
      usage(argv[0], "frontend and memory need distinct non-producer workers in --joint-cpus");
    if (o.stage_image || o.export_offload || o.row_transport || o.delta_transport || o.decode_thread ||
        o.consumer_cpu >= 0 || o.decoder_cpu >= 0 || o.producer_cpu >= 0 || !o.partition_cpus.empty())
      usage(argv[0], "joint execution uses --joint-cpus and in-place image transport");
    o.overlap = o.partition_threads = o.producer_decode = o.image_transport = true;
    o.producer_cpu = o.joint_cpus[0];
  }
  if (o.require_success && o.skip_consumer)
    usage(argv[0], "--require-success needs a checked consumer");
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
  if (!diagnostic_ready_image_path.empty()) {
    if (!o.joint_execution || o.architecture_check || !o.dump_path.empty())
      usage(argv[0], "ready-image timing requires joint execution without architectural observer or dumping");
#if defined(CHISA_BOOM_EXTERNAL_DRAM) || defined(CHISA_HAS_ADDITIONAL_ORACLES)
    usage(argv[0], "ready-image capture does not contain auxiliary oracle channels");
#endif
  }
#endif
  if (o.partition_threads && (!o.overlap || !o.producer_decode || o.skip_consumer))
    usage(argv[0], "--partition-threads needs --overlap with --producer-decode/--decode-thread");
#if !defined(CHISA_HAS_PARTITION_ARCHITECTURE)
  if (o.partition_threads && o.architecture_check)
    usage(argv[0], "partition architecture check requires generated observation owners");
#endif
  if (o.architecture_check && o.skip_consumer)
    usage(argv[0], "--architecture-check requires executing the RTL consumer");
#if !defined(CHISA_CONSUMER_ARCHITECTURE)
  if (o.architecture_check)
    usage(argv[0], "--architecture-check requires a consumer with verified observation bindings");
#endif
  if (o.row_transport && o.delta_transport)
    usage(argv[0], "--row-transport and --delta-transport are exclusive");
  if (o.stage_image && (o.row_transport || o.delta_transport || o.export_offload || !o.decode_thread))
    usage(argv[0], "--stage-image needs the image transport and --decode-thread");
  if (!o.row_transport && !o.delta_transport && !o.export_offload) o.image_transport = true;
  if (o.image_transport) o.row_transport = o.delta_transport = false;
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
  // The access profile remaps the model image directly into the consumer.
  // Compact change entries encode the base offsets and cannot be reused.
  o.image_transport = true;
  if (o.export_offload)
    usage(argv[0], "external DRAM uses image transport without export offload");
  if (!o.dump_path.empty())
    usage(argv[0], "external DRAM access records are not part of the legacy dump format");
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
  if (o.export_offload || !o.image_transport)
    usage(argv[0], "additional oracles require in-thread image publication");
#endif
  if (o.export_offload && !(o.overlap && o.producer_decode))
    usage(argv[0], "--export-offload needs --overlap with --decode-thread or --producer-decode");
  if (o.producer_cpu >= 0 && !o.overlap)
    usage(argv[0], "--producer-cpu requires --overlap");
  if (o.decoder_cpu >= 0 && !(o.overlap && o.decode_thread))
    usage(argv[0], "--decoder-cpu requires --overlap --decode-thread");
  std::vector<std::pair<int, int>> cores;
  for (const int cpu : {o.consumer_cpu, o.producer_cpu, o.decoder_cpu}) {
    if (cpu < 0) continue;
    const auto core = physical_core(cpu);
    if (std::find(cores.begin(), cores.end(), core) != cores.end())
      usage(argv[0], "explicit thread CPUs must belong to distinct physical cores");
    cores.push_back(core);
  }
  if (o.max_cycles == 0 || o.max_cycles % kWindow != 0)
    usage(argv[0], "--max-cycles must be a positive multiple of 2W");
  if (o.reset_cycles % kWindow != 0 || o.reset_cycles >= o.max_cycles)
    usage(argv[0], "--reset-cycles must be a smaller multiple of 2W");
  if (o.timing_from % kWindow != 0 || o.timing_from >= o.max_cycles)
    usage(argv[0], "--timing-from must be a smaller multiple of 2W");
  if (!o.timing_until) o.timing_until = o.max_cycles;
  if (o.timing_until % kWindow || o.timing_until <= o.timing_from || o.timing_until > o.max_cycles)
    usage(argv[0], "--timing-until must be an aligned upper bound after --timing-from and at most --max-cycles");
  // The generated verify checks are bounded by the compile-time cycle count;
  // beyond it a window would run unverified, which is never acceptable here.
  if (o.max_cycles > ORACLE_NUM_CYCLES)
    usage(argv[0], "--max-cycles exceeds the consumer's ORACLE_NUM_CYCLES");
  return o;
}

template <typename Ports>
void drive_lane(Ports& ports, int lane, const ReferenceOracleCycleRecord& r) {
  assign_port(ports.debug_req_valid[lane], r.req_valid);
  assign_port(ports.debug_req_bits_addr[lane], r.req_addr);
  assign_port(ports.debug_req_bits_op[lane], r.req_op);
  assign_port(ports.debug_req_bits_data[lane], r.req_data);
  assign_port(ports.debug_resp_ready[lane], r.resp_ready);
  assign_port(ports.exit[lane], r.exit);
}

template <typename Ports>
DmiFeedback feedback_lane(const Ports& ports, int lane) {
  return DmiFeedback{
      port_value(ports.debug_req_ready[lane]) != 0,
      port_value(ports.debug_resp_valid[lane]) != 0,
      static_cast<std::uint32_t>(port_value(ports.debug_resp_bits_resp[lane])),
      static_cast<std::uint32_t>(port_value(ports.debug_resp_bits_data[lane]))};
}

template <typename Dut>
auto configure_oracle_policy(Dut& dut, const Options& options, int)
    -> decltype(dut.set_oracle_mismatch_policy(true, UINT64_C(16)), void()) {
  dut.set_oracle_mismatch_policy(!options.continue_oracle_mismatches,
                                 options.mismatch_log_limit);
}

template <typename Dut>
void configure_oracle_policy(Dut&, const Options& options, long) {
  if (options.continue_oracle_mismatches)
    throw std::runtime_error("report-only oracle checks require a regenerated consumer header");
}

template <class Dut>
auto window_boundary_statistics(const Dut& dut, int)
    -> decltype(dut.window_boundary_oracle_mismatches, std::pair<bool, std::uint64_t>{}) {
  return {true, dut.window_boundary_oracle_mismatches};
}

template <class Dut>
std::pair<bool, std::uint64_t> window_boundary_statistics(const Dut&, long) {
  return {false, 0};
}

}  // namespace

int main(int argc, char** argv) {
  try {
    const Options options = parse(argc, argv);
#if !defined(ESSENT_ORACLE_VERIFY) || !ESSENT_ORACLE_VERIFY
    if (!options.skip_consumer)
      throw std::runtime_error("BOOM live consumer was compiled without oracle verification");
#endif
    std::vector<char*> htif_argv;
    htif_argv.push_back(argv[0]);
    for (int i = options.htif_start; i < argc; ++i) htif_argv.push_back(argv[i]);

    dtm_t model_dtm(static_cast<int>(htif_argv.size()), htif_argv.data());
    chisa::boom_repcut::FesvrDebugBootstrap<dtm_t> model_debug(model_dtm);
    chisa::boom_system::BoundaryConfig config;
    config.image_path = argv[options.htif_start];
    config.argc = argc;
    config.argv = argv;
    config.reset_cycles = options.reset_cycles;
    config.debug_bootstrap = &model_debug;
    config.cooperative_workers = options.joint_execution;
    SystemGuider model(config);
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
    model.enable_dram_access_capture(true);
    chisa::boom_system::ExternalDramAdapter dram_adapter;
#endif
    chisa::boom_system::SystemOracleWriter writer;
    if (options.image_transport) writer.set_image_mode(true);
    CHISA_DIAG(if (options.image_transport && !options.export_offload)
      writer.enable_owner_diagnostics());
    if (options.row_transport && !options.image_transport && !options.export_offload) writer.set_row_mode(true);
    std::unique_ptr<chisa::boom_system::ExportThread> exporter;
    if (options.export_offload)
      exporter = std::make_unique<chisa::boom_system::ExportThread>(
          writer, &model, /*own_thread=*/!options.decode_thread);

    // Raw producer output for offline comparison against a W1 capture: per
    // window, kWindow cycle records followed by the oracle block.
    std::FILE* dump = nullptr;
    if (!options.dump_path.empty()) {
      dump = std::fopen(options.dump_path.c_str(), "wb");
      if (dump == nullptr) throw std::runtime_error("cannot open --dump-blocks file");
    }

    auto dut = make_kernel();
    configure_oracle_policy(*dut, options, 0);
#if defined(CHISA_CONSUMER_ARCHITECTURE)
    std::unique_ptr<chisa::boom_repcut::ConsumerArchitectureCheck> architecture;
    if (options.architecture_check) {
      architecture = std::make_unique<chisa::boom_repcut::ConsumerArchitectureCheck>(argv[options.htif_start]);
      if (!options.partition_threads) architecture->initialize(*dut);
    }
#endif
    initialize_plusarg_readers<kW>(*dut, argc, argv);
    auto& ports = simdtm_ports(*dut);
    // One kernel instance per partition for --partition-threads: instance 0
    // is `dut`, the others are created here and fed the same windows.
    using Ports = std::remove_reference_t<decltype(simdtm_ports(*dut))>;
    const int partitions = TestHarness::ESSENT_PARTITIONS;
    if (options.partition_threads && partitions <= 0)
      throw std::runtime_error("--partition-threads needs a kernel emitted with partitions");
    if (options.partition_threads && (options.check_partition < 0 || options.check_partition >= partitions))
      throw std::runtime_error("--check-partition out of range");
    std::vector<std::unique_ptr<TestHarness>> extra_duts;
    std::vector<TestHarness*> partition_duts;
    std::vector<Ports*> partition_ports;
    if (options.partition_threads) {
      partition_duts.push_back(dut.get());
      partition_ports.push_back(&ports);
      for (int p = 1; p < partitions; ++p) {
        extra_duts.push_back(make_kernel());
        TestHarness& d = *extra_duts.back();
        configure_oracle_policy(d, options, 0);
        initialize_plusarg_readers<kW>(d, argc, argv);
        partition_duts.push_back(&d);
        partition_ports.push_back(&simdtm_ports(d));
      }
    }

#ifndef CHISA_LIVE_RING_WINDOWS
#define CHISA_LIVE_RING_WINDOWS 4
#endif
    constexpr unsigned kRing = CHISA_LIVE_RING_WINDOWS;
    const unsigned source_ahead=options.joint_source_ahead ? options.joint_source_ahead : kRing-1;
    if (source_ahead>=kRing) throw std::runtime_error("source lookahead must be smaller than the ring");
    // The legacy wait deliberately yields 32 PAUSEs to an SMT sibling.
    // Joint owners normally have separate physical cores and must observe
    // per-cycle requests promptly, including dedicated model-only owners.
    const auto joint_wait_hint = [&] {
      for (unsigned i=0;i<options.joint_idle_pauses;++i) _mm_pause();
    };
    CHISA_DIAG(::chisa::diagnostic::checkpoint("transport","injection-topology",0,
      ::chisa::diagnostic::Layer::Injection,
      {{"partitions",options.partition_threads ? static_cast<std::uint64_t>(partitions) : 1u},
       {"check_partition",options.partition_threads ? static_cast<std::uint64_t>(options.check_partition) : 0u}}));
    static_assert(kRing >= 2 && kRing <= 64 && (kRing & (kRing - 1)) == 0,
                  "live ring must contain 2..64 power-of-two windows");
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
    using ArchitectureFrames = chisa::boom_repcut::PartitionArchitectureFrames<kRing>;
    std::unique_ptr<ArchitectureFrames> partition_architecture;
    std::vector<std::atomic<std::uint64_t>> architecture_completed(options.partition_threads ? partitions : 0);
    if (options.partition_threads && architecture) {
      namespace capture = chisa::boom_repcut::consumer_arch;
      if (capture::kArchitecturePartitions != static_cast<unsigned>(partitions))
        throw std::runtime_error("architecture owner contract/partition count mismatch");
      chisa::boom_repcut::PartitionArchitectureOwners owners{
          capture::kArchitecturePartitions, capture::kArchitectureSignalOwners,
          capture::kArchitectureIntegerOwners, capture::kArchitectureFloatingOwners};
      partition_architecture = std::make_unique<ArchitectureFrames>(owners);
      architecture->initialize(*partition_duts[owners.integer[0]], *partition_duts[owners.floating[0]]);
      capture::frame.enabled = false;  // every partition binds its private frame below
      for (auto& completed : architecture_completed) completed.store(0, std::memory_order_relaxed);
    }
    const auto observer_range = [] {
      std::array<std::uint64_t, 2> range{};
      const char* value = std::getenv("CHISA_CONSUMER_OBSERVER_RANGE");
      if (value && std::sscanf(value, "%" SCNu64 ":%" SCNu64, &range[0], &range[1]) != 2)
        throw std::runtime_error("CHISA_CONSUMER_OBSERVER_RANGE requires FROM:UNTIL");
      return range;
    }();
#endif
    struct Slot {
      chisa::boom_system::OracleBlockBytes block;  // 64-byte aligned (see OracleBlockAllocator)
      std::vector<ReferenceOracleCycleRecord> records;
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
      std::array<chisa::boom_system::protocol::AxiRamAccess, kWindow> dram_access{};
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
      std::array<chisa::boom_system::additional_oracles::Snapshot, kWindow> additional{};
#endif
    };
    std::vector<Slot> ring(kRing);
    for (auto& s : ring) {
      s.block.assign(chisa::boom_system::oracle_compact_capacity(), 0);
      // Constants never change. Initialize each reusable backing block once;
      // dynamic lanes are overwritten at every position before consumption.
      s.records.resize(kWindow);
    }

    // One hot expansion buffer: the consumer walks windows strictly in
    // order, so a single reusable buffer keeps the injection reads and
    // the decoder writes L2-resident instead of streaming cold ring
    // blocks.
    std::vector<char> expanded(kConsumerOracleBlockBytes, 0);
    chisa::boom_system::OracleDeltaDecoder oracle_decoder;
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
    chisa::boom_system::OracleImageDecoder image_decoder(
        dram_adapter.base_offsets().data(), dram_adapter.base_offsets().size());
#else
    chisa::boom_system::OracleImageDecoder image_decoder;
#endif
    if (options.joint_partition_ready || !options.joint_decode_priority.empty() || options.joint_decode_regroup || options.joint_decode_group_lanes!=32) {
#if defined(CHISA_PARTITION_DELIVERY_HEADER)
      namespace delivery=chisa::boom_repcut::delivery;
      static_assert(delivery::width==chisa::boom_system::kSystemOracleWidth);
      static_assert(delivery::readers.size()==chisa::boom_system::kSystemOracleModeledStreams);
      if (delivery::partitions!=static_cast<unsigned>(partitions))
        throw std::runtime_error("partition delivery count mismatch");
      for (std::size_t lane=0;lane<delivery::offsets.size();++lane)
        if (delivery::offsets[lane]!=chisa::boom_system::kSystemOracleStreams[lane].block_offset)
          throw std::runtime_error("partition delivery destination layout mismatch");
      image_decoder.partition_groups(delivery::readers.data(),delivery::readers.size(),
          delivery::partitions,options.joint_decode_priority,options.joint_decode_group_lanes,options.joint_decode_regroup);
#endif
    }
    // Whole-window expansion in the transport's form (the image decoder
    // takes no lane range: every lane, every window).
    auto decode_full = [&](const Slot& slot, char* dst, std::uint64_t first) {
      const bool ok = options.image_transport
          ? image_decoder.decode(slot.block.data(), dst, first)
          : oracle_decoder.decode(slot.block.data(), dst);
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
      if (ok) dram_adapter.inject(slot.dram_access.data(), dst);
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
      if (ok) chisa::boom_system::additional_oracles::inject(slot.additional.data(), dst);
#endif
      return ok;
    };
    // --producer-decode: one expansion buffer per ring slot. Slot w holds the
    // full window image (copy of slot w-1 plus window w's changes); the
    // producer writes it before publishing w, the consumer only reads it.
    std::vector<std::vector<char>> expanded_ring;
    const std::uint32_t split_lane = std::min<std::uint32_t>(
        options.image_transport ? 0xffffffffu : options.producer_decode_lanes,
        chisa::boom_system::kSystemOracleModeledStreams);
    chisa::boom_system::OracleDeltaDecoder consumer_decoder;  // lanes [split, N)
    if (options.producer_decode) {
      expanded_ring.assign(kRing, std::vector<char>(kConsumerOracleBlockBytes, 0));
      oracle_decoder.set_lane_range(0, split_lane);
      consumer_decoder.set_lane_range(split_lane, chisa::boom_system::kSystemOracleModeledStreams);
    }
    // Windows whose expansion the producer has completed (its lane share);
    // the consumer starts window w only after this passes w. The consumer's
    // own share of window w is done at the start of consume_window(w), after
    // which consumed_started = w+1 tells the producer slot w is complete.
    IsolatedAtomic<std::uint64_t> expanded_windows{0};
    // Partition threads block here between windows instead of spinning: a
    // spinning hyperthread sibling halves the throughput of the partition
    // sharing its core, while a sleeping one hands the whole core over (the
    // six-partition Ryzen placement pairs partitions on cores).
    std::mutex expanded_mutex;
    std::condition_variable expanded_cv;
    std::atomic<std::uint64_t> consumed_started{0};
    // Per-partition progress for --partition-threads; the producer and the
    // expander see the slowest partition.
    std::vector<std::atomic<std::uint64_t>> partition_started(options.partition_threads ? partitions : 0);
    std::vector<std::atomic<std::uint64_t>> partition_consumed(options.partition_threads ? partitions : 0);
    const auto slowest = [](const std::vector<std::atomic<std::uint64_t>>& counters) {
      std::uint64_t value = ~UINT64_C(0);
      for (const auto& c : counters) value = std::min(value, c.load(std::memory_order_acquire));
      return value;
    };
    const std::uint64_t total_windows = options.max_cycles / kWindow;
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
    if (!diagnostic_ready_image_path.empty())
      diagnostic_ready_images = std::make_unique<chisa::boom_repcut::OverlapReadyImages>(
        diagnostic_ready_image_path, total_windows,
        kWindow * sizeof(ReferenceOracleCycleRecord),
        chisa::boom_system::kOracleImageHeaderBytes +
            kWindow * chisa::boom_system::kOracleRecordPaddedBytes,
        options.reset_cycles / kWindow, kWindow,
        chisa::boom_system::kOracleRecordPaddedBytes);
    std::printf("OVERLAP_DIAGNOSTIC mode=%s capture_bytes=%zu normal_checks=1 transport_included=1\n",
                diagnostic_ready_images ? "ready-images" : "online",
                diagnostic_ready_images ? diagnostic_ready_images->bytes() : 0);
#endif
    IsolatedAtomic<std::uint64_t> produced_windows{0};
    // --stage-image: positions the producer has finished (absolute cycles,
    // reset windows included though never written), positions the decoder
    // thread has copied into the window blocks, and the windows it has
    // completed (the block readiness expand_ready() then waits on).
    // Deep enough that the decoder's expansion of one whole window (about
    // 40 us on the Ryzen, 70 us on the Xeon) never stalls the producer: it
    // drains only between expansions, so the ring must hold more positions
    // than the producer writes during one expansion.  16 images = 232 KB.
    constexpr unsigned kStagingPositions = 16;
    chisa::boom_system::OracleBlockBytes staging(
        options.stage_image ? kStagingPositions * chisa::boom_system::kOracleRecordPaddedBytes : 0, 0);
    if (options.stage_image) writer.set_image_staging(staging.data(), kStagingPositions);
    std::atomic<std::uint64_t> staged_positions{0};
    std::atomic<std::uint64_t> drained_positions{0};
    std::atomic<std::uint64_t> drained_windows{0};
    auto drain_staging = [&]() {
      std::uint64_t d = drained_positions.load(std::memory_order_relaxed);
      const std::uint64_t s = staged_positions.load(std::memory_order_acquire);
      while (d < s) {
        const std::uint64_t w = d / kWindow, pos = d % kWindow;
        if (d >= options.reset_cycles) {
          Slot& slot = ring[w % kRing];
          std::memcpy(slot.block.data() + chisa::boom_system::kOracleImageHeaderBytes +
                          pos * chisa::boom_system::kOracleRecordPaddedBytes,
                      staging.data() + (d % kStagingPositions) * chisa::boom_system::kOracleRecordPaddedBytes,
                      chisa::boom_system::kOracleRecordPaddedBytes);
          if (pos == kWindow - 1) {
            const std::uint32_t positions = kWindow;
            const std::uint32_t image_bytes = chisa::boom_system::kOracleRecordPaddedBytes;
            std::memcpy(slot.block.data(), &chisa::boom_system::kOracleImageMagic, 4);
            std::memcpy(slot.block.data() + 4, &positions, 4);
            std::memcpy(slot.block.data() + 8, &image_bytes, 4);
            CHISA_DIAG(writer.diagnostic_seal(slot.block.data(),w*kWindow));
          }
        }
        ++d;
        drained_positions.store(d, std::memory_order_release);
        if (pos == kWindow - 1) drained_windows.store(w + 1, std::memory_order_release);
      }
    };
    std::atomic<bool> producer_failed{false};
    IsolatedAtomic<std::uint64_t> consumed_windows_{0};

    std::uint64_t produced_cycles = 0;
    std::uint64_t consumed_cycles = 0;
    std::uint64_t boundary_mismatches = 0;
    std::uint32_t consumed_exit = 0;
    std::uint64_t active_blocks = 0;
    std::uint64_t verify_windows = 0;
    std::uint64_t timed_cycles = 0;
    bool dut_success = false;
    IsolatedAtomic<bool> stop_producer{false};
    IsolatedAtomic<bool> producer_done{false};
    std::atomic<std::uint64_t> partition_terminal_window{UINT64_MAX};
    std::atomic<std::uint64_t> architecture_consumed{0};
    std::chrono::duration<double> producer_elapsed{}, consumer_elapsed{}, wall_elapsed{};
    std::chrono::duration<double> producer_wait_elapsed{}, consumer_wait_elapsed{};
    // Transport accounting for the timed region: decode time, change records
    // per window, and whole-lane re-fills done by the decoder.
    std::chrono::duration<double> decode_elapsed{};
    // Written only by the expansion owner, unlike consumer-side decoding.
    std::chrono::duration<double> expansion_elapsed{};
    std::uint64_t decode_windows = 0, decode_deltas = 0, decode_releveled = 0;
    // Cold-RTL activity counters over the timed region (serial mode only):
    // tells how often the coherent-memory fixed point and the bus sidecars
    // actually evaluate under live fesvr traffic, mirroring the producer
    // benchmark's report.
    struct ColdCounters {
      std::uint64_t cm_skip = 0, cm_la_skip = 0;
      std::uint64_t sbus_eval = 0, sbus_skip = 0;
      std::uint64_t cm_pre = 0, cm_pre_eq = 0, cm_pre_recomputed = 0;
      static ColdCounters capture(const chisa::boom_system::SystemGuider& m) {
        const auto& cold = m.fabric();
        return ColdCounters{cold.coherent_memory_skipped_count(),
                            cold.coherent_memory_lookahead_skipped_count(),
                            cold.system_bus_eval_count(),
                            cold.system_bus_skipped_count(),
                            cold.coherent_memory_pre_edge_total_count(),
                            cold.coherent_memory_pre_edge_equal_lookahead_count(),
                            cold.coherent_memory_pre_edge_recomputed_count()};
      }
    };
    ColdCounters roi_cold{};
    ColdCounters roi_cold_end{};
    bool roi_cold_valid = false;

    std::uint64_t dmi_requests_timed = 0;
#ifdef CHISA_PHASE_TIMERS
    std::uint64_t write_tsc = 0, produce_tsc = 0;
    bool phase_armed = false;
    auto roi_phase_end = model.phase_counters();
    const auto reset_model_timers = [&] {
      // Window production has joined both model owners before this point.
      model.reset_phase_counters();
      for (auto& ticks : chisa::boom_system::g_phase_sub) ticks = 0;
      chisa::boom_system::g_cold_evaluate_active = 0;
      chisa::boom_system::g_cold_evaluate_active_ticks = 0;
      chisa::boom_system::g_cold_commit_active = 0;
      chisa::boom_system::g_cold_commit_active_ticks = 0;
      chisa::boom_system::cold_module_timing_reset();
    };
#endif
    auto produce_window = [&](std::uint64_t w) {
#if defined(CHISA_OVERLAP_DIAGNOSTIC)
      if (diagnostic_ready_images) {
        auto& slot = ring[w % kRing];
        diagnostic_ready_images->copy_window(w, slot.records.data(), slot.block.data());
        if (options.timed(w * kWindow))
          for (const auto& record : slot.records) dmi_requests_timed += record.req_valid != 0;
        return true;
      }
#endif
      // Pending publishers hold the writer's context. Drain them on every
      // return/exception path while that writer is still alive.
      struct PendingPublishers {
        chisa::boom_system::SystemGuider& model;
        ~PendingPublishers() {
          model.synchronize_memory_side();
          model.synchronize_frontend_runs();
        }
      } pending_publishers{model};
      Slot& slot = ring[w % kRing];
      const std::uint64_t first = w * kWindow;
      const bool reset_window = first < options.reset_cycles;
      for (unsigned pos = 0; pos < kWindow; ++pos) {
        if (options.stage_image && !reset_window) {
          // The staging slot for this cycle is free once the decoder thread
          // has copied the position written into it kStagingPositions
          // cycles ago.
          // Two slots: the frontend thread copies its record runs for the
          // next position during this step (SystemOracleWriter::next_image_destination).
          const std::uint64_t cycle = first + pos;
          while (drained_positions.load(std::memory_order_acquire) + kStagingPositions <= cycle + 1) {
            if (stop_producer.load() || producer_failed.load()) return false;
            spin_wait_hint();
          }
        }
#ifdef CHISA_PHASE_TIMERS
        const std::uint64_t wt0 = exporter ? exporter->producer_ticks() : writer.publish_ticks();
#endif
        const auto step_result =
            reset_window ? model.step()
            : exporter   ? exporter->step_and_export(model, slot.block.data(), pos)
                         : writer.step_and_write(model, slot.block.data(), pos
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
                             , &chisa::boom_system::additional_oracles::capture,
                             &slot.additional[pos]
#else
                             , nullptr, nullptr
#endif
                             , !reset_window);
        if (!step_result.ok) { producer_failed.store(true); return false; }
#if defined(CHISA_CONSUMER_ARCHITECTURE)
#if defined(CHISA_WIDE_MODEL)
        if (architecture)
          for (const auto& event : model.retirement_events()) architecture->observe_model(event);
#else
        if (architecture) architecture->observe_model(model.retirement_event());
#endif
#endif
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
        slot.dram_access[pos] = model.last_dram_access();
#endif
#ifdef CHISA_PHASE_TIMERS
        if (options.timed(first))
          write_tsc += (exporter ? exporter->producer_ticks() : writer.publish_ticks()) - wt0;
#endif
        const auto& d = model.last_dmi();
        if (options.partition_threads && d.exit==1)
          chisa::boom_repcut::note_terminal_window(partition_terminal_window,w);
        if (options.timed(first) && d.req_valid) ++dmi_requests_timed;
        slot.records[pos] = ReferenceOracleCycleRecord{
            d.req_addr, d.req_op, d.req_data,
            d.exit, d.resp_response, d.resp_data,
            static_cast<std::uint8_t>(d.req_valid),
            static_cast<std::uint8_t>(d.resp_ready),
            static_cast<std::uint8_t>(d.req_ready),
            static_cast<std::uint8_t>(d.resp_valid),
            static_cast<std::uint8_t>(d.exit == 1),
            static_cast<std::uint8_t>(d.reset),
            {0, 0}};
        // The previous position is complete now (the memory worker finishes
        // a position's Predicted lanes during the following step, and this
        // step joined it); the last one is marked below.
        if (options.stage_image) staged_positions.store(first + pos, std::memory_order_release);
      }
      // Every position of the window, including the last one's Predicted
      // lanes still on the memory worker and the frontend worker's copy of
      // its runs.
      model.synchronize_memory_side();
      model.synchronize_frontend_runs();
      CHISA_DIAG(if (!reset_window && !options.stage_image) writer.diagnostic_seal(slot.block.data(),first));
      if (options.stage_image) staged_positions.store(first + kWindow, std::memory_order_release);
      // With the exporter the worker seals the block later; the window mark
      // tells it (and expand_ready) when every position is in, and the dump
      // moves to expand_window.
      if (exporter) exporter->mark_window(w);
      if (dump != nullptr && !exporter) {
        std::fwrite(slot.records.data(), sizeof(slot.records[0]),
                    slot.records.size(), dump);
        std::fwrite(slot.block.data(), 1, slot.block.size(), dump);
      }
      return true;
    };

    // Producer-side expansion of window w into its ring slot: copy slot w-1
    // forward (complete once the consumer has started w-1), then apply the
    // producer's lane share. Reset windows carry no oracle content.
    auto expand_window = [&](std::uint64_t w) {
      const std::uint64_t first = w * kWindow;
      if (dump != nullptr && exporter) {
        const Slot& slot = ring[w % kRing];
        std::fwrite(slot.records.data(), sizeof(slot.records[0]),
                    slot.records.size(), dump);
        std::fwrite(slot.block.data(), 1, slot.block.size(), dump);
      }
      if (first >= options.reset_cycles) {
        char* dst = expanded_ring[w % kRing].data();
        // The delta form fills only moved lanes: it needs the previous
        // window's buffer as the base.  The image form writes every element.
        if (w > 0 && !options.image_transport) {
          const auto& prev = expanded_ring[(w - 1) % kRing];
          std::memcpy(dst, prev.data(), prev.size());
        }
        const auto d0 = std::chrono::steady_clock::now();
        if (!decode_full(ring[w % kRing], dst, first)) {
          std::fprintf(stderr, "malformed oracle window block\n");
          std::exit(6);
        }
        if (options.timed(first)) {
          const auto elapsed = std::chrono::steady_clock::now() - d0;
          decode_elapsed += elapsed;
          expansion_elapsed += elapsed;
          ++decode_windows;
        }
      }
      CHISA_TIMELINE(w,timeline.expanded[row].first=TraceClock::now());
      expanded_windows.store(w + 1, std::memory_order_release);
      CHISA_TIMELINE(w,timeline.expanded[row].second=TraceClock::now());
      { std::lock_guard<std::mutex> lk(expanded_mutex); }
      expanded_cv.notify_all();
    };
    // Expand every produced window whose predecessor the consumer has started.
    auto expand_ready = [&]() {
      std::uint64_t e = expanded_windows.load(std::memory_order_relaxed);
      // Windows whose block is complete: sealed by the export worker, or
      // written in place by the producer.
      const std::uint64_t p = exporter ? exporter->sealed_windows()
                              : options.stage_image ? drained_windows.load(std::memory_order_acquire)
                                                    : produced_windows.load(std::memory_order_acquire);
      // Window e is expanded into expanded_ring[e % kRing], last used by window
      // e - kRing. With partition threads the slot is free once the slowest
      // partition has consumed that window, so the decoder may run up to
      // kRing - 1 windows ahead of it; the ring of blocks gives the producer
      // the same slack, and window e - 1 (the delta base) is still resident.
      // Expanding only one window ahead of the slowest partition's start made
      // the per-window maximum across partitions the pipeline period.
      const std::uint64_t cs = options.partition_threads ? slowest(partition_consumed) + kRing - 1
                                                         : consumed_started.load(std::memory_order_acquire);
      while (e < p && cs >= e) { expand_window(e); ++e; }
    };

    // One small transpose group per invocation. Workers share this bounded
    // background task; the try-lock never makes a model task wait. The
    // completed-window release remains the sole RTL input readiness gate.
    chisa::boom_repcut::IsolatedClaim decode_claim;
    std::size_t decode_group = 0;
    chisa::boom_system::OracleImageDecoder::Window decode_window;
    auto try_decode_group_serial = [&]() -> bool {
      // Empty queues are common. Avoid bouncing an exclusive cache line
      // among idle workers just to discover that there is no image to decode.
      if (expanded_windows.load(std::memory_order_acquire) >=
          produced_windows.load(std::memory_order_acquire)) return false;
      if (decode_claim.flag.test_and_set(std::memory_order_acquire)) return false;
      struct Release { std::atomic_flag& flag; ~Release() { flag.clear(std::memory_order_release); } } release{decode_claim.flag};
      const auto w = expanded_windows.load(std::memory_order_relaxed);
      if (w >= produced_windows.load(std::memory_order_acquire) ||
          w >= consumed_windows_.load(std::memory_order_acquire) + kRing - 1) return false;
      const auto first = w * kWindow;
      const bool timed = options.eval_timing && options.timed(first);
#ifdef CHISA_PHASE_TIMERS
      const auto t0 = timed ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
#endif
      if (first >= options.reset_cycles) {
        if (decode_group == 0 && !image_decoder.validate_window(
              ring[w % kRing].block.data(), expanded_ring[w % kRing].data(), decode_window))
          throw std::runtime_error("malformed cooperative oracle image");
        if (!image_decoder.decode_group(decode_window, decode_group++))
          throw std::runtime_error("invalid cooperative decode group");
#ifdef CHISA_PHASE_TIMERS
        if (timed) decode_elapsed += std::chrono::steady_clock::now() - t0;
#endif
        if (decode_group < image_decoder.group_count()) return true;
#if defined(CHISA_MODEL_DIAGNOSTICS)
        image_decoder.diagnostic_verify(ring[w % kRing].block.data(), expanded_ring[w % kRing].data(), first);
#endif
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
        dram_adapter.inject(ring[w % kRing].dram_access.data(), expanded_ring[w % kRing].data());
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
        chisa::boom_system::additional_oracles::inject(ring[w % kRing].additional.data(), expanded_ring[w % kRing].data());
#endif
        if (timed) ++decode_windows;
      }
      decode_group = 0;
      CHISA_TIMELINE(w,timeline.expanded[row].first=TraceClock::now());
      expanded_windows.store(w + 1, std::memory_order_release);
      CHISA_TIMELINE(w,timeline.expanded[row].second=TraceClock::now());
      return true;
    };
    // Each worker owns its accounting. A decoded window is published only
    // after all groups finish; source slots keep the existing reader lifetime.
    struct alignas(64) DecodeAccounting {
      std::chrono::duration<double> elapsed{};
      std::uint64_t windows = 0;
    };
    std::vector<DecodeAccounting> parallel_decode_accounting(options.joint_cpus.size());
    using ImageWindow = chisa::boom_system::OracleImageDecoder::Window;
    chisa::boom_repcut::ParallelDecode<ImageWindow> parallel_decode;
    std::array<chisa::boom_repcut::PartitionReady<6>,kRing> partition_ready;
    std::array<unsigned,6> partition_group_counts{};
    const bool configured_delivery=options.joint_partition_ready || !options.joint_decode_priority.empty() ||
        options.joint_decode_regroup || options.joint_decode_group_lanes!=32;
    if (configured_delivery) {
      for (std::size_t g=0;g<image_decoder.group_count();++g)
        for (unsigned p=0;p<6;++p)
          if (image_decoder.group_readers(g) & (UINT64_C(1)<<p)) ++partition_group_counts[p];
    }
    if (configured_delivery)
      std::printf("PARTITION_DELIVERY early=%d groups=%zu dependencies=%u,%u,%u,%u,%u,%u\n",
          int(options.joint_partition_ready),image_decoder.group_count(),
          partition_group_counts[0],partition_group_counts[1],partition_group_counts[2],
          partition_group_counts[3],partition_group_counts[4],partition_group_counts[5]);
    auto try_decode_group_parallel = [&](unsigned worker) -> bool {
      const auto w = expanded_windows.load(std::memory_order_acquire);
      if (w >= produced_windows.load(std::memory_order_acquire) ||
          w >= consumed_windows_.load(std::memory_order_acquire) + kRing - 1) return false;
      const auto first = w * kWindow;
      const bool reset = first < options.reset_cycles;
      const bool timed = options.eval_timing && options.timed(first);
      chisa::boom_repcut::ParallelDecode<ImageWindow>::Ticket ticket{};
      if (!parallel_decode.claim(w, reset ? 1 : image_decoder.group_count(),
          [&](ImageWindow& context) {
            if (!reset && !image_decoder.validate_window(ring[w % kRing].block.data(),
                  expanded_ring[w % kRing].data(), context))
              throw std::runtime_error("malformed parallel oracle image");
            if (options.joint_partition_ready) {
              std::array<unsigned,6> counts=partition_group_counts;
              if (reset) counts.fill(1);
              partition_ready[w%kRing].begin(w,counts);
            }
          }, ticket)) return false;
#ifdef CHISA_PHASE_TIMERS
      const auto t0 = timed ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
#endif
      if (!reset && !image_decoder.decode_group(ticket.context, ticket.group))
        throw std::runtime_error("invalid parallel decode group");
      if (options.joint_partition_ready)
        partition_ready[w%kRing].complete(w,reset ? UINT64_C(63) : image_decoder.group_readers(ticket.group),
          [&](unsigned p,bool after) {
            CHISA_TIMELINE(w, (after ? timeline.ready[p][row].second : timeline.ready[p][row].first)=TraceClock::now());
          });
#ifdef CHISA_PHASE_TIMERS
      if (timed) parallel_decode_accounting[worker].elapsed += std::chrono::steady_clock::now() - t0;
#endif
      if (parallel_decode.complete(ticket)) {
        if (!reset) {
#if defined(CHISA_MODEL_DIAGNOSTICS)
          image_decoder.diagnostic_verify(ring[w % kRing].block.data(), expanded_ring[w % kRing].data(), first);
#endif
#if defined(CHISA_BOOM_EXTERNAL_DRAM)
          dram_adapter.inject(ring[w % kRing].dram_access.data(), expanded_ring[w % kRing].data());
#endif
#if defined(CHISA_HAS_ADDITIONAL_ORACLES)
          chisa::boom_system::additional_oracles::inject(ring[w % kRing].additional.data(), expanded_ring[w % kRing].data());
#endif
          if (timed) ++parallel_decode_accounting[worker].windows;
        }
        CHISA_TIMELINE(w,timeline.expanded[row].first=TraceClock::now());
        expanded_windows.store(w + 1, std::memory_order_release);
        CHISA_TIMELINE(w,timeline.expanded[row].second=TraceClock::now());
      }
      return true;
    };
    using chisa::boom_repcut::TryTask;
    std::vector<chisa::boom_repcut::JointTaskPump> joint_pumps(options.joint_cpus.size());
    auto make_decode_task = [&](unsigned worker) {
      return [&, worker] { return options.joint_parallel_decode
          ? try_decode_group_parallel(worker) : try_decode_group_serial(); };
    };
    std::vector<decltype(make_decode_task(0))> decode_tasks;
    decode_tasks.reserve(joint_pumps.size());
    for (unsigned worker = 0; worker < joint_pumps.size(); ++worker)
      decode_tasks.push_back(make_decode_task(worker));
    auto frontend_task = [&] { return model.try_frontend_task(); };
    auto memory_task = [&] { return model.try_memory_task(); };
    auto producer_background = [&] {
      if (!joint_pumps[0].background()) return false;
      ++joint_pumps[0].background_tasks;
      return true;
    };
    if (options.joint_execution) {
      if (partitions != 6) throw std::runtime_error("joint schedule requires six partitions");
      joint_pumps[options.joint_frontend_worker].priority = TryTask::bind(frontend_task);
      joint_pumps[options.joint_memory_worker].priority = TryTask::bind(memory_task);
      for (auto& pump : joint_pumps) {
        pump.priority_budget = options.joint_model_budget;
        pump.background_in_kernel = options.joint_decode_in_kernel;
      }
      for (int worker : options.joint_decode_workers) joint_pumps[worker].background = TryTask::bind(decode_tasks[worker]);
      for (int p = 0; p < partitions; ++p)
        if (!chisa::boom_repcut::bind_joint_pump(*partition_duts[p],
              joint_pumps[options.joint_partition_workers[p]], 0))
          throw std::runtime_error("joint execution requires a --cooperative-poll consumer");
      const auto task = joint_pumps[0].background.function ? TryTask::bind(producer_background) : TryTask{};
      model.set_wait_task(task.function, task.context);
      std::printf("JOINT_EXECUTION physical_cores=%zu threads=%zu frontend_worker=%d memory_worker=%d parallel_decode=%d source_ahead=%u idle_pauses=%u\n",
                  options.joint_physical_cores, joint_pumps.size(), options.joint_frontend_worker,
                  options.joint_memory_worker, int(options.joint_parallel_decode),source_ahead,options.joint_idle_pauses);
    }

    auto consume_window = [&](std::uint64_t w) {
      Slot& slot = ring[w % kRing];
      const std::uint64_t first = w * kWindow;
      const bool reset_window = first < options.reset_cycles;
      // Reset windows are never produced (no oracle content); the lanes
      // run under reset and consume nothing, so skip the decode and
      // leave the expansion buffer holding whatever it has.
      if (!reset_window && !dut->checks_enabled)
        throw std::runtime_error("BOOM live consumer oracle checks are disabled");
      if (options.producer_decode) {
        if (!reset_window && split_lane < chisa::boom_system::kSystemOracleModeledStreams) {
          const auto d0 = std::chrono::steady_clock::now();
          if (!consumer_decoder.decode(slot.block.data(), expanded_ring[w % kRing].data())) {
            std::fprintf(stderr, "malformed oracle window block\n");
            std::exit(6);
          }
          if (options.timed(first)) decode_elapsed += std::chrono::steady_clock::now() - d0;
        }
        // Slot w now holds the complete image: the producer may copy it
        // forward into slot w+1 while this window is evaluated.
        consumed_started.store(w + 1, std::memory_order_release);
      }
      if (!reset_window && !options.producer_decode) {
        const bool timed = options.timed(first);
        const std::uint64_t releveled0 = oracle_decoder.releveled_lanes();
        const std::uint64_t changed0 = oracle_decoder.changed_lanes();
        const auto d0 = std::chrono::steady_clock::now();
        if (!decode_full(slot, expanded.data(), first)) {
          std::fprintf(stderr, "malformed oracle window block\n");
          std::exit(6);
        }
        if (timed) {
          decode_elapsed += std::chrono::steady_clock::now() - d0;
          decode_deltas += oracle_decoder.changed_lanes() - changed0;
          decode_releveled += oracle_decoder.releveled_lanes() - releveled0;
          ++decode_windows;
        }
      }
      dut->oracle_win_base = options.producer_decode ? expanded_ring[w % kRing].data()
                                                     : expanded.data();
      CHISA_DIAG(
        if (!reset_window && options.image_transport)
          image_decoder.diagnostic_verify(slot.block.data(), dut->oracle_win_base, first, true);
      );
      for (int half = 0; half < 2; ++half) {
        const bool forward = half == 0;
        for (unsigned step = 0; step < kW; ++step) {
          const int lane = forward ? static_cast<int>(step)
                                   : static_cast<int>(kW - 1 - step);
          drive_lane(ports, lane, slot.records[half * kW + step]);
        }
        assign_port(dut->reset, reset_window);
#if defined(CHISA_CONSUMER_ARCHITECTURE)
        if (architecture) architecture->begin_half();
#endif
        eval_half(*dut, forward, !reset_window, 0);
#if defined(CHISA_CONSUMER_ARCHITECTURE)
        if (architecture) architecture->consume_half(forward, first + half * kW, reset_window);
#endif
        for (unsigned step = 0; step < kW && !reset_window; ++step) {
          const int lane = forward ? static_cast<int>(step)
                                   : static_cast<int>(kW - 1 - step);
          const auto& record = slot.records[half * kW + step];
          const std::uint64_t cycle = first + half * kW + step;
          const auto actual_feedback = feedback_lane(ports, lane);
          const auto expected_feedback = chisa::boom_repcut::trace_dmi_feedback(record);
          if (actual_feedback != expected_feedback) {
            ++boundary_mismatches;
            if (!options.continue_oracle_mismatches)
              throw std::runtime_error("live DMI feedback mismatch at cycle " + std::to_string(cycle));
            if (boundary_mismatches <= options.mismatch_log_limit)
              std::fprintf(stderr,
                  "LIVE_BOUNDARY_MISMATCH kind=dmi cycle=%" PRIu64
                  " req_valid=%u req_addr=0x%x req_op=%u resp_ready=%u"
                  " actual_req_ready=%u expected_req_ready=%u"
                  " actual_resp_valid=%u expected_resp_valid=%u"
                  " actual_resp=%u expected_resp=%u"
                  " actual_data=0x%x expected_data=0x%x\n",
                  cycle, unsigned(record.req_valid), unsigned(record.req_addr),
                  unsigned(record.req_op), unsigned(record.resp_ready),
                  unsigned(actual_feedback.req_ready), unsigned(expected_feedback.req_ready),
                  unsigned(actual_feedback.resp_valid), unsigned(expected_feedback.resp_valid),
                  unsigned(actual_feedback.resp), unsigned(expected_feedback.resp),
                  unsigned(actual_feedback.data), unsigned(expected_feedback.data));
          }
          const bool success = port_value(dut->io_success[lane]) != 0;
          if (success != (record.io_success != 0)) {
            ++boundary_mismatches;
            if (!options.continue_oracle_mismatches)
              throw std::runtime_error("live io_success mismatch at cycle " + std::to_string(cycle));
            if (boundary_mismatches <= options.mismatch_log_limit)
              std::fprintf(stderr, "LIVE_BOUNDARY_MISMATCH kind=io_success cycle=%" PRIu64 "\n", cycle);
          }
          if (success) dut_success = true;
        }
      }
      consumed_cycles += kWindow;
      consumed_exit = slot.records.back().exit;
      if (!reset_window) { ++active_blocks; ++verify_windows; }
      if (dut->assert_triggered) {
        stop_producer.store(true);
        throw std::runtime_error("live RTL assertion, exit=" + std::to_string(dut->assert_exit_code));
      }
      if (dut->verify_mismatches != 0 && !options.continue_oracle_mismatches) {
        stop_producer.store(true);
        throw std::runtime_error(
            "live verify mismatch at window ending cycle " +
            std::to_string(first + kWindow));
      }
    };

    if (!options.overlap && !bind_current_thread("consumer", options.consumer_cpu))
      throw std::runtime_error("consumer CPU affinity failed");
#if defined(CHISA_WINDOW_TIMELINE)
    if (!options.joint_execution || !options.eval_timing ||
        options.timing_until<=options.timing_from ||
        options.timing_from%kWindow || options.timing_until%kWindow)
      throw std::runtime_error("window timeline requires joint execution and an aligned, nonempty timing ROI");
    chisa::boom_repcut::window_timeline=std::make_unique<chisa::boom_repcut::WindowTimeline>(
        options.timing_from/kWindow,options.timing_until/kWindow,partitions,options.joint_partition_ready);
#endif
    auto wall0_timed = std::chrono::steady_clock::now();
    auto wall_end_timed = wall0_timed;
    if (options.overlap) {
      std::chrono::steady_clock::time_point producer_timed_start{}, producer_timed_end{};
      std::vector<std::chrono::steady_clock::time_point> partition_timed_end(
          options.partition_threads ? partitions : 0);
      std::exception_ptr producer_failure;
      std::thread producer([&] {
        struct Finished { std::atomic<bool>& done; ~Finished() { done.store(true, std::memory_order_release); } } finished{producer_done};
        try {
        if (!bind_current_thread("producer", options.producer_cpu)) {
          producer_failed.store(true);
          return;
        }
        for (std::uint64_t w = 0; w < total_windows && !stop_producer.load(); ++w) {
          if (w > partition_terminal_window.load(std::memory_order_acquire)) break;
          const bool timed = options.eval_timing && options.timed(w * kWindow);
          const auto wait0 = timed ? std::chrono::steady_clock::now()
                                   : std::chrono::steady_clock::time_point{};
          if (timed && w * kWindow == options.timing_from) producer_timed_start = wait0;
          const bool owns_expansion = options.producer_decode && !options.decode_thread && !options.joint_execution;
          const auto expansion0 = owns_expansion
              ? expansion_elapsed : std::chrono::duration<double>{};
          const auto account_wait = [&] {
            const auto active = owns_expansion ? expansion_elapsed - expansion0
                                               : std::chrono::duration<double>{};
            // expand_ready may do useful work while the ring is full.
            producer_elapsed += active;
            if (timed)
              producer_wait_elapsed += std::chrono::steady_clock::now() - wait0 - active;
          };
          // back-pressure: stay at most kRing-1 windows ahead of the consumer
          while (produced_windows.load(std::memory_order_acquire) >=
                 consumed_windows_.load(std::memory_order_acquire) + source_ahead) {
            if (stop_producer.load()) {
              account_wait();
              return;
            }
            if (options.producer_decode && !options.decode_thread && !options.joint_execution) expand_ready();
            if (options.joint_execution) {
              if (!producer_background()) joint_wait_hint();
            } else spin_wait_hint();
          }
          account_wait();
#if defined(CHISA_CPU_SAMPLING)
          if (timed && w*kWindow==options.timing_from) paper_perf_control(true);
#endif
#ifdef CHISA_PHASE_TIMERS
          if (timed && !phase_armed) {
            reset_model_timers();
            phase_armed = true;
          }
          const auto produce_begin_tsc = timed ? __rdtsc() : 0;
#endif
          const auto p0 = std::chrono::steady_clock::now();
          CHISA_TIMELINE(w,timeline.producer_begin[row]=TraceClock::ns(p0));
          if (!produce_window(w)) return;
#ifdef CHISA_PHASE_TIMERS
          if (timed) {
            produce_tsc += __rdtsc() - produce_begin_tsc;
            roi_phase_end = model.phase_counters();
          }
#endif
          CHISA_TIMELINE(w,timeline.source[row].first=TraceClock::now());
          produced_windows.store(w + 1, std::memory_order_release);
          CHISA_TIMELINE(w,timeline.source[row].second=TraceClock::now());
#if defined(CHISA_CPU_SAMPLING)
          if (timed && (w+1)*kWindow==options.timing_until)
            paper_perf_finish(options.timing_until-options.timing_from);
#endif
          if (timed) {
            producer_timed_end = std::chrono::steady_clock::now();
            producer_elapsed += producer_timed_end - p0;
          }
          const auto expanded_before = owns_expansion
              ? expansion_elapsed : std::chrono::duration<double>{};
          if (options.producer_decode && !options.decode_thread && !options.joint_execution) expand_ready();
          if (owns_expansion) producer_elapsed += expansion_elapsed - expanded_before;
        }
        // Drain: windows produced but not yet expandable wait for the consumer.
        if (options.producer_decode && !options.decode_thread && !options.joint_execution) {
          const auto expansion0 = expansion_elapsed;
          const auto drain0 = options.eval_timing ? std::chrono::steady_clock::now()
              : std::chrono::steady_clock::time_point{};
          while (!stop_producer.load() &&
                 expanded_windows.load(std::memory_order_acquire) <
                     produced_windows.load(std::memory_order_acquire)) {
            expand_ready();
            spin_wait_hint();
          }
          const auto active = expansion_elapsed - expansion0;
          producer_elapsed += active;
          if (options.eval_timing && produced_windows.load() &&
              options.timed((produced_windows.load() - 1) * kWindow))
            producer_wait_elapsed += std::chrono::steady_clock::now() - drain0 - active;
        }
        } catch (...) {
          producer_failure = std::current_exception();
          producer_failed.store(true, std::memory_order_release);
          stop_producer.store(true, std::memory_order_release);
          expanded_cv.notify_all();
        }
      });
      // Third thread: expands every produced window (copy-forward + decode)
      // as soon as its predecessor's slot is complete; the consumer waits on
      // expanded_windows exactly as with --producer-decode.
      std::thread expander;
      if (!options.joint_execution) expander = std::thread([&] {
        if (!options.decode_thread) return;
        if (!bind_current_thread("decoder", options.decoder_cpu)) {
          producer_failed.store(true);
          return;
        }
        while (!stop_producer.load() && !producer_failed.load() &&
               expanded_windows.load(std::memory_order_acquire) < total_windows) {
          if (exporter) {
            // Export worker and expander on one thread: apply what the
            // model's thread shipped (sealing windows), then expand the
            // sealed windows.
            const bool busy = exporter->drain(4096) != 0;
            expand_ready();
            if (!busy) {
#if defined(__x86_64__)
              __builtin_ia32_pause();
#endif
            }
            continue;
          }
          if (options.stage_image) drain_staging();
          expand_ready();
          spin_wait_hint();
        }
      });
      // --partition-threads: partition p runs on its own kernel instance and
      // thread over the shared expanded windows. Partitions never wait for
      // each other inside a window (cross-partition reads are oracle lanes);
      // the ring's reuse follows the slowest one. The check partition owns
      // the DMI/io_success comparison and the window accounting.
      std::atomic<bool> partition_success{false};
      std::atomic<bool> partition_exit_observed{false};
      std::vector<std::chrono::duration<double>> partition_elapsed(options.partition_threads ? partitions : 0);
      std::vector<std::exception_ptr> partition_failure(options.partition_threads
          ? std::max<std::size_t>(partitions, options.joint_execution ? joint_pumps.size() : 0) : 0);
      const auto publish_consumed = [&] {
        auto value = slowest(partition_consumed);
        // Early readers may finish while a completing decoder still owns
        // the slot. Retire all expansion writers before recycling storage.
        if (options.joint_partition_ready)
          value=std::min(value,expanded_windows.load(std::memory_order_acquire));
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
        if (partition_architecture) value = std::min(value, architecture_consumed.load(std::memory_order_acquire));
#endif
        auto old = consumed_windows_.load(std::memory_order_relaxed);
        while (value > old && !consumed_windows_.compare_exchange_weak(old, value,
            std::memory_order_release, std::memory_order_relaxed)) {}
      };
      std::uint64_t architecture_next = 0;  // check-partition executor owns aggregation
      const auto collect_architecture = [&] {
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
        if (partition_architecture) {
          const auto completed = slowest(architecture_completed);
          while (architecture_next < completed) {
            const auto w = architecture_next;
            const auto first = w * kWindow;
            const bool reset_window = first < options.reset_cycles;
            for (unsigned half = 0; half < 2; ++half) {
              namespace capture = chisa::boom_repcut::consumer_arch;
              for (unsigned position = 0; position < kW; ++position) {
                const auto cycle = first + half * kW + position;
                if (cycle < observer_range[0] || cycle >= observer_range[1]) continue;
                const unsigned lane = half == 0 ? position : kW - 1 - position;
                for (int source = 0; source < partitions; ++source) {
                  const auto& raw = partition_architecture->captured_frame(source, w, half);
                  for (unsigned probe = 0; probe < capture::kObserverProbeCount; ++probe) {
                    const unsigned signal = capture::kObserverProbeBegin + probe;
                    if (raw.seen[signal])
                      std::fprintf(stderr, "CONSUMER_CHAIN cycle=%" PRIu64 " partition=%d field=%s lo=%" PRIx64 " hi=%" PRIx64 "\n",
                        cycle, source, capture::kObserverProbeNames[probe],
                        raw.signals[signal][lane].lo, raw.signals[signal][lane].hi);
                  }
                }
              }
              const auto frame = partition_architecture->merge(w, half);
              architecture->consume_half(half == 0, first + half * kW, reset_window, frame);
            }
            ++architecture_next;
            architecture_consumed.store(architecture_next, std::memory_order_release);
          }
          publish_consumed();
        }
#endif
        if (options.joint_partition_ready) publish_consumed();
        if (consumed_windows_.load(std::memory_order_acquire) >
            partition_terminal_window.load(std::memory_order_acquire)) {
          if (!partition_exit_observed.load(std::memory_order_acquire))
            throw std::runtime_error("reference exit boundary was not confirmed by RTL");
          partition_success.store(true, std::memory_order_release);
        }
      };
      const auto evaluate_partition_window = [&](int p, std::uint64_t w) {
        TestHarness& d = *partition_duts[p];
        Ports& pp = *partition_ports[p];
        const bool check = p == options.check_partition;
        const bool timed = options.timed(w * kWindow);
        if (check && options.timing_from != 0 && w * kWindow == options.timing_from)
          wall0_timed = std::chrono::steady_clock::now();
        const auto c0 = std::chrono::steady_clock::now();
        CHISA_TIMELINE(w,timeline.consumer[p][row].first=TraceClock::ns(c0));
        Slot& slot = ring[w % kRing];
        const std::uint64_t first = w * kWindow;
        const bool reset_window = first < options.reset_cycles;
        partition_started[static_cast<std::size_t>(p)].store(w + 1, std::memory_order_release);
        d.oracle_win_base = expanded_ring[w % kRing].data();
        CHISA_DIAG(if (!reset_window && options.image_transport)
          image_decoder.diagnostic_verify(slot.block.data(),d.oracle_win_base,first,true,p,check));
        for (int half = 0; half < 2; ++half) {
          const bool forward = half == 0;
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
          chisa::boom_repcut::consumer_arch::FrameScope capture_scope(
              partition_architecture ? &partition_architecture->begin_half(p) : nullptr);
#endif
          for (unsigned step = 0; step < kW; ++step) {
            const int lane = forward ? static_cast<int>(step) : static_cast<int>(kW - 1 - step);
            drive_lane(pp, lane, slot.records[half * kW + step]);
          }
          assign_port(d.reset, reset_window);
          eval_one_partition(d, p, forward, !reset_window, 0);
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
          if (partition_architecture) partition_architecture->finish_half(p, w, half);
#endif
          if (!check) continue;
          for (unsigned step = 0; step < kW && !reset_window; ++step) {
            const int lane = forward ? static_cast<int>(step) : static_cast<int>(kW - 1 - step);
            const auto& record = slot.records[half * kW + step];
            const std::uint64_t cycle = first + half * kW + step;
            const auto actual_feedback = feedback_lane(pp, lane);
            const auto expected_feedback = chisa::boom_repcut::trace_dmi_feedback(record);
            if (actual_feedback != expected_feedback) {
              ++boundary_mismatches;
              if (!options.continue_oracle_mismatches)
                throw std::runtime_error("live DMI feedback mismatch at cycle " + std::to_string(cycle));
              if (boundary_mismatches <= options.mismatch_log_limit)
                std::fprintf(stderr,
                    "LIVE_BOUNDARY_MISMATCH kind=dmi cycle=%" PRIu64 " partition=%d"
                    " req_valid=%u req_addr=0x%x req_op=%u resp_ready=%u"
                    " actual_req_ready=%u expected_req_ready=%u"
                    " actual_resp_valid=%u expected_resp_valid=%u"
                    " actual_resp=%u expected_resp=%u actual_data=0x%x expected_data=0x%x\n",
                    cycle, p, unsigned(record.req_valid), unsigned(record.req_addr),
                    unsigned(record.req_op), unsigned(record.resp_ready),
                    unsigned(actual_feedback.req_ready), unsigned(expected_feedback.req_ready),
                    unsigned(actual_feedback.resp_valid), unsigned(expected_feedback.resp_valid),
                    unsigned(actual_feedback.resp), unsigned(expected_feedback.resp),
                    unsigned(actual_feedback.data), unsigned(expected_feedback.data));
            }
            const bool success = port_value(d.io_success[lane]) != 0;
            if (success != (record.io_success != 0)) {
              ++boundary_mismatches;
              if (!options.continue_oracle_mismatches)
                throw std::runtime_error("live io_success mismatch at cycle " + std::to_string(cycle));
              if (boundary_mismatches <= options.mismatch_log_limit)
                std::fprintf(stderr, "LIVE_BOUNDARY_MISMATCH kind=io_success cycle=%" PRIu64 "\n", cycle);
            }
            if (success) {
              partition_exit_observed.store(true,std::memory_order_release);
              chisa::boom_repcut::note_terminal_window(partition_terminal_window,w);
            }
          }
        }
        if (check) {
          consumed_cycles += kWindow;
          consumed_exit = slot.records.back().exit;
          if (!reset_window) { ++active_blocks; ++verify_windows; }
        }
        if (d.assert_triggered) {
          stop_producer.store(true);
          throw std::runtime_error("live RTL assertion in partition " + std::to_string(p) +
                                   ", exit=" + std::to_string(d.assert_exit_code));
        }
        if (d.verify_mismatches != 0 && !options.continue_oracle_mismatches) {
          stop_producer.store(true);
          throw std::runtime_error("live verify mismatch in partition " + std::to_string(p) +
                                   " at window ending cycle " + std::to_string(first + kWindow));
        }
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
        if (partition_architecture) architecture_completed[p].store(w + 1, std::memory_order_release);
#endif
        if (timed) {
          const auto now = std::chrono::steady_clock::now();
          CHISA_TIMELINE(w,timeline.consumer[p][row].second=TraceClock::ns(now));
          partition_elapsed[static_cast<std::size_t>(p)] += now - c0;
          partition_timed_end[p] = now;
          if (check) { wall_end_timed = now; timed_cycles += kWindow; }
        }
        partition_consumed[p].store(w + 1, std::memory_order_release);
        publish_consumed();
      };
      auto run_partition = [&](int p) {
        try {
          const int cpu = static_cast<std::size_t>(p) < options.partition_cpus.size()
                              ? options.partition_cpus[p] : -1;
          if (!bind_current_thread("partition", cpu)) throw std::runtime_error("partition CPU affinity failed");
          for (std::uint64_t w = 0; w < total_windows && !partition_success.load(std::memory_order_acquire); ++w) {
            if (w > partition_terminal_window.load(std::memory_order_acquire)) break;
            while (expanded_windows.load(std::memory_order_acquire) <= w) {
              if (producer_failed.load()) throw std::runtime_error("producer failed");
              if (stop_producer.load() || partition_success.load()) return;
              std::unique_lock<std::mutex> lk(expanded_mutex);
              expanded_cv.wait_for(lk, std::chrono::microseconds(100), [&] {
                return expanded_windows.load(std::memory_order_acquire) > w || producer_failed.load() ||
                       stop_producer.load() || partition_success.load();
              });
            }
            evaluate_partition_window(p, w);
            if (p == options.check_partition) {
              collect_architecture();
#if defined(CHISA_HAS_PARTITION_ARCHITECTURE)
              while (partition_architecture && architecture_next <= w) {
                if (stop_producer.load() || producer_failed.load())
                  throw std::runtime_error("partition failed before architectural frame completion");
                collect_architecture();
                spin_wait_hint();
              }
#endif
              if (w == partition_terminal_window.load(std::memory_order_acquire)) {
                while (!partition_success.load(std::memory_order_acquire)) {
                  if (stop_producer.load() || producer_failed.load()) return;
                  collect_architecture();
                  spin_wait_hint();
                }
              }
            }
          }
        } catch (...) {
          partition_failure[p] = std::current_exception();
          partition_success.store(true, std::memory_order_release);
          stop_producer.store(true);
        }
      };
      auto run_joint_worker = [&](int worker) {
        auto& pump = joint_pumps[worker];
        const bool owns_check = options.joint_partition_workers[options.check_partition] == worker;
        std::vector<unsigned> owned;
        for (unsigned p = 0; p < static_cast<unsigned>(partitions); ++p)
          if (options.joint_partition_workers[p] == worker) owned.push_back(p);
        unsigned cursor = 0;
        try {
          if (!bind_current_thread("joint-worker", options.joint_cpus[worker]))
            throw std::runtime_error("joint worker CPU affinity failed");
          if (owned.empty()) {
            // Dedicated model/decode owners need no repeated scans of the
            // six RTL progress counters. Model tasks remain alive for the
            // producer's drain even after the RTL requests a stop.
            for (;;) {
              if (stop_producer.load(std::memory_order_acquire)) {
                if (producer_done.load(std::memory_order_acquire)) break;
                if (!pump.priority()) joint_wait_hint();
              } else if (producer_done.load(std::memory_order_acquire) && !pump.background.function) {
                break;
              } else if (!pump.poll()) joint_wait_hint();
            }
            return;
          }
          for (;;) {
            if (owns_check) collect_architecture();
            const bool complete = slowest(partition_consumed) >= total_windows;
            if (stop_producer.load(std::memory_order_acquire) || partition_success.load(std::memory_order_acquire) || complete) {
              stop_producer.store(true, std::memory_order_release);
              // The producer's final position still owns publication
              // contexts. Keep both model executors alive until its drain
              // finishes, including an RTL/observer failure path.
              if (producer_done.load(std::memory_order_acquire)) break;
              if (!pump.priority()) joint_wait_hint();
              continue;
            }
            bool busy = pump.poll();
            for (unsigned n = 0; n < owned.size(); ++n) {
              const unsigned index = (cursor + n) % owned.size();
              const unsigned p = owned[index];
              const auto w = partition_consumed[p].load(std::memory_order_relaxed);
              if (w >= total_windows || w > partition_terminal_window.load(std::memory_order_acquire) ||
                  (options.joint_partition_ready ? !partition_ready[w%kRing].ready(w,p) :
                   expanded_windows.load(std::memory_order_acquire) <= w)) continue;
              evaluate_partition_window(p, w);
              cursor = (index + 1) % owned.size();
              busy = true;
              break;
            }
            if (!busy) joint_wait_hint();
          }
        } catch (...) {
          partition_failure[worker] = std::current_exception();
          stop_producer.store(true, std::memory_order_release);
          while (!producer_done.load(std::memory_order_acquire))
            if (!pump.priority()) joint_wait_hint();
        }
      };
      // A consumer failure must not leave the producer thread joinable at
      // unwind; join it first, then rethrow.
      std::exception_ptr failure;
      try {
        if (options.partition_threads) {
          std::vector<std::thread> workers;
          if (options.joint_execution) {
            for (unsigned worker = 2; worker < joint_pumps.size(); ++worker) workers.emplace_back(run_joint_worker, worker);
            run_joint_worker(1);
          } else {
            for (int p = 1; p < partitions; ++p) workers.emplace_back(run_partition, p);
            run_partition(0);
          }
          for (auto& worker : workers) worker.join();
          for (auto& f : partition_failure) if (f) std::rethrow_exception(f);
          dut_success = partition_success.load();
          consumer_elapsed = partition_elapsed[static_cast<std::size_t>(options.check_partition)];
          for (int p = 0; p < partitions; ++p) {
            std::printf("LIVE_PARTITION partition=%d completed_windows=%" PRIu64 " oracle_mismatch_signals=%" PRIu64 " timed_eval_ns_per_cycle=%.1f\n", p,
                        partition_consumed[p].load(), partition_duts[p]->oracle_mismatch_signal_count(),
                        timed_cycles ? 1e9 * partition_elapsed[static_cast<std::size_t>(p)].count() / double(timed_cycles) : 0.0);
            std::printf("ORACLE_MISMATCH_DETAIL partition=%d raw_events=%" PRIu64 "\n", p,
                        static_cast<std::uint64_t>(partition_duts[p]->verify_mismatches));
          }
          if (options.joint_execution)
            for (unsigned worker = 0; worker < joint_pumps.size(); ++worker)
              std::printf("JOINT_WORKER worker=%u cpu=%d polls=%" PRIu64 " model_tasks=%" PRIu64 " decode_tasks=%" PRIu64 "\n",
                worker, options.joint_cpus[worker], joint_pumps[worker].polls,
                joint_pumps[worker].priority_tasks, joint_pumps[worker].background_tasks);
        } else {
        if (!bind_current_thread("consumer", options.consumer_cpu))
          throw std::runtime_error("consumer CPU affinity failed");
        for (std::uint64_t w = 0; w < total_windows && !dut_success; ++w) {
          const bool timed = options.timed(w * kWindow);
          if (options.timing_from != 0 && w * kWindow == options.timing_from)
            wall0_timed = std::chrono::steady_clock::now();
          const auto wait0 = options.eval_timing && timed
              ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
          while ((options.producer_decode ? expanded_windows : produced_windows)
                     .load(std::memory_order_acquire) <= w) {
            if (producer_failed.load()) throw std::runtime_error("producer failed");
            spin_wait_hint();
          }
          if (options.eval_timing && timed)
            consumer_wait_elapsed += std::chrono::steady_clock::now() - wait0;
          const auto c0 = options.eval_timing && timed
              ? std::chrono::steady_clock::now() : std::chrono::steady_clock::time_point{};
          if (!options.skip_consumer) consume_window(w);
          if (options.eval_timing && timed) {
            wall_end_timed = std::chrono::steady_clock::now();
            consumer_elapsed += wall_end_timed - c0;
          }
          consumed_windows_.store(w + 1, std::memory_order_release);
          if (timed) timed_cycles += kWindow;
        }
        }
        stop_producer.store(true);  // also ends the producer's expansion drain
      } catch (...) {
        failure = std::current_exception();
        stop_producer.store(true);
      }
      producer.join();
      if (expander.joinable()) expander.join();
      if (options.joint_execution && options.joint_parallel_decode)
        for (const auto& counters : parallel_decode_accounting) {
          decode_elapsed += counters.elapsed;
          decode_windows += counters.windows;
        }
      model.set_wait_task(nullptr, nullptr);
      if (producer_failure) std::rethrow_exception(producer_failure);
      if (failure) std::rethrow_exception(failure);
      if (options.eval_timing && timed_cycles) {
        // Include generation of the first ROI window and completion of the
        // slowest RTL partition. A check partition can lead either endpoint
        // by several ring slots; increasing the ring must not hide that work.
        const auto legacy_elapsed = wall_end_timed - wall0_timed;
        wall0_timed = std::min(wall0_timed, producer_timed_start);
        wall_end_timed = std::max(wall_end_timed, producer_timed_end);
        for (const auto end : partition_timed_end) wall_end_timed = std::max(wall_end_timed, end);
        std::printf("LIVE_SIDECAR_TIMING_SCOPE begin=first-producer-or-consumer end=last-owner"
                    " ring_windows=%u legacy_check_partition_ns_per_cycle=%.1f\n", kRing,
                    std::chrono::duration<double>(legacy_elapsed).count() * 1e9 / double(timed_cycles));
      }
      produced_cycles = produced_windows.load() * kWindow;
    } else {
      for (std::uint64_t w = 0; w < total_windows && !dut_success; ++w) {
        const bool timed = options.timed(w * kWindow);
        if (w * kWindow == options.timing_from) {
          wall0_timed = std::chrono::steady_clock::now();
          roi_cold = ColdCounters::capture(model);
          roi_cold_valid = true;
        }
#ifdef CHISA_PHASE_TIMERS
        if (timed && !phase_armed) { reset_model_timers(); phase_armed = true; }
        const std::uint64_t pt0 = __rdtsc();
#endif
        const auto p0 = std::chrono::steady_clock::now();
        if (!produce_window(w))
          throw std::runtime_error("model lost lockstep confidence");
        produced_windows.store(w + 1, std::memory_order_release);
        if (options.producer_decode) { consumed_started.store(w, std::memory_order_release); expand_ready(); }
#ifdef CHISA_PHASE_TIMERS
        if (timed) produce_tsc += __rdtsc() - pt0;
#endif
        produced_cycles += kWindow;
        if (timed) producer_elapsed += std::chrono::steady_clock::now() - p0;
        const auto c0 = std::chrono::steady_clock::now();
        if (!options.skip_consumer) consume_window(w);
        if (timed) {
          wall_end_timed = std::chrono::steady_clock::now();
          consumer_elapsed += wall_end_timed - c0;
          timed_cycles += kWindow;
          if ((w + 1) * kWindow == options.timing_until || dut_success) {
            roi_cold_end = ColdCounters::capture(model);
#ifdef CHISA_PHASE_TIMERS
            roi_phase_end = model.phase_counters();
#endif
          }
        }
      }
    }
    wall_elapsed = wall_end_timed - wall0_timed;
    if (dump != nullptr) std::fclose(dump);
    if (options.require_success && !dut_success)
      throw std::runtime_error("cycle limit reached without successful program completion");
    bool architecture_compared = false;
#if defined(CHISA_CONSUMER_ARCHITECTURE)
    if (architecture) { architecture->finish(); architecture_compared = true; }
#endif

    std::uint64_t total_verify_mismatches = dut->verify_mismatches;
    for (const auto& d : extra_duts) total_verify_mismatches += d->verify_mismatches;
    std::uint64_t oracle_signal_union[TestHarness::oracle_mismatch_signal_words()]{};
    dut->oracle_mismatch_signal_union(oracle_signal_union);
    for (const auto& d : extra_duts) d->oracle_mismatch_signal_union(oracle_signal_union);
    std::uint64_t oracle_mismatch_signals = 0;
    for (std::uint64_t bits : oracle_signal_union)
      oracle_mismatch_signals += __builtin_popcountll(bits);
    const auto oracle_checked_signals = TestHarness::oracle_checked_signal_count();
    std::printf(
        "%s width=%u cycles=%" PRIu64 " active_blocks=%" PRIu64
        " verify_windows=%" PRIu64 " oracle_mismatch_signals=%" PRIu64 " oracle_checked_signals=%u"
        " dut_success=%d\n",
        options.continue_oracle_mismatches ? "LIVE_SIDECAR_COMPLETED" : "LIVE_SIDECAR_OK",
        kW, produced_cycles, active_blocks, verify_windows,
        oracle_mismatch_signals, oracle_checked_signals,
        dut_success ? 1 : 0);
    std::printf("ORACLE_MISMATCH_DETAIL raw_events=%" PRIu64 "\n", total_verify_mismatches);
    const auto window_boundary = window_boundary_statistics(*dut, 0);
    std::printf(
        "MODEL_VALIDATION schema=2 comparison_start_cycle=%" PRIu64
        " compared_cycles=%" PRIu64 " compared_windows=%" PRIu64
        " consumed_cycles=%" PRIu64 " reset_cycles=%" PRIu64
        " streams=%zu oracle_mismatch_signals=%" PRIu64 " oracle_checked_signals=%u boundary_mismatches=%" PRIu64
        " initialization_compared=%d consumer=%s program_done=%d program_exit=%" PRId64
        " architectural_state_compared=%d architecture_status=%s"
        " window_boundary_oracle_mismatches_supported=%d"
        " window_boundary_oracle_mismatches=%" PRIu64 "\n",
        options.reset_cycles, verify_windows * kWindow, verify_windows,
        consumed_cycles, options.reset_cycles, kConsumerOracleStreams,
        oracle_mismatch_signals, oracle_checked_signals, boundary_mismatches,
        !options.skip_consumer && verify_windows != 0 ? 1 : 0,
        options.skip_consumer ? "skipped" : options.continue_oracle_mismatches ? "verify-report-only" : "verify",
        (consumed_exit & 1u) ? 1 : 0,
        (consumed_exit & 1u) ? static_cast<std::int64_t>(consumed_exit >> 1) : INT64_C(-1),
        architecture_compared ? 1 : 0, architecture_compared ? "pass" : "not-run",
        window_boundary.first ? 1 : 0, window_boundary.second);
    if (options.eval_timing && timed_cycles != 0) {
      std::printf("LIVE_SIDECAR_TIMING_RANGE begin=%" PRIu64 " end=%" PRIu64
                  " measured_end=%" PRIu64 " window=%u\n",
                  options.timing_from, options.timing_until,
                  options.timing_from + timed_cycles, kWindow);
      const double ps = producer_elapsed.count();
      const double cs = consumer_elapsed.count();
      const double ws = wall_elapsed.count();
      const double n = static_cast<double>(timed_cycles);
      if (options.overlap)
        std::printf("LIVE_SIDECAR_TIMING overlap timed_cycles=%" PRIu64
                    " producer_ns_per_cycle=%.1f wall_ns_per_cycle=%.1f"
                    " consumer_ns_per_cycle=%.1f producer_wait_ns_per_cycle=%.1f"
                    " consumer_wait_ns_per_cycle=%.1f\n",
                    timed_cycles, ps * 1e9 / n, ws * 1e9 / n, cs * 1e9 / n,
                    producer_wait_elapsed.count() * 1e9 / n,
                    consumer_wait_elapsed.count() * 1e9 / n);
      else
        std::printf(
            "LIVE_SIDECAR_TIMING timed_cycles=%" PRIu64
            " producer_ns_per_cycle=%.1f consumer_ns_per_cycle=%.1f "
            "serial_total_ns_per_cycle=%.1f wall_ns_per_cycle=%.1f\n",
            timed_cycles, ps * 1e9 / n, cs * 1e9 / n, (ps + cs) * 1e9 / n,
            ws * 1e9 / n);
      std::printf("LIVE_SIDECAR_DMI timed_cycles=%" PRIu64 " requests=%" PRIu64
                  " per_kcycle=%.2f\n", timed_cycles, dmi_requests_timed,
                  dmi_requests_timed * 1000.0 / n);
#ifdef CHISA_PHASE_TIMERS
      if (produce_tsc != 0) {
        const double ns_per_tick = ps * 1e9 / static_cast<double>(produce_tsc);
        const auto& pc = roi_phase_end;
        const double sample_ns = pc.sample_tsc * ns_per_tick / n;
        const double model_ns = (static_cast<double>(pc.step_tsc) - pc.sample_tsc -
                                 pc.lookahead_tsc - write_tsc) * ns_per_tick / n;
        const double write_ns = write_tsc * ns_per_tick / n;
        const double step_ns = pc.step_tsc * ns_per_tick / n;
        const double lookahead_ns = pc.lookahead_tsc * ns_per_tick / n;
        // Both publish callbacks run inside SystemGuider::step. The writer
        // is already removed from model_ns; subtracting it from the outer
        // harness again loses that cost from the producer decomposition.
        std::printf("LIVE_SIDECAR_PHASES sample_ns_per_cycle=%.1f model_ns_per_cycle=%.1f"
                    " write_ns_per_cycle=%.1f harness_ns_per_cycle=%.1f"
                    " lookahead_ns_per_cycle=%.1f\n",
                    sample_ns, model_ns, write_ns, ps * 1e9 / n - step_ns, lookahead_ns);
        std::printf("LIVE_MODEL_PHASES pre=%.1f backend=%.1f tlbptw=%.1f postbackend=%.1f tail=%.1f"
                    " memory_outputs_wait=%.1f memory_fabric_wait=%.1f frontend_join=%.1f\n",
          pc.pre_tsc * ns_per_tick / n, pc.backend_tsc * ns_per_tick / n,
          pc.tlbptw_tsc * ns_per_tick / n, pc.postbackend_tsc * ns_per_tick / n,
          pc.tail_tsc * ns_per_tick / n, pc.sub_tsc[5] * ns_per_tick / n,
          pc.sub_tsc[6] * ns_per_tick / n, pc.sub_tsc[4] * ns_per_tick / n);
        std::printf("LIVE_MODEL_PRE frontend_tail=%.1f head_publish=%.1f memory_prepare=%.1f dtm=%.1f\n",
            pc.sub_tsc[8] * ns_per_tick / n, pc.sub_tsc[9] * ns_per_tick / n,
            pc.sub_tsc[10] * ns_per_tick / n, pc.sub_tsc[11] * ns_per_tick / n);
        // The global fine counters run until shutdown. Only label them as
        // ROI measurements when the run itself ends at the ROI boundary.
        if (produced_cycles == options.timing_until) {
          const auto& g = chisa::boom_system::g_phase_sub;
          std::printf("LIVE_MODEL_MEMORY ns_per_cycle: fabric_commit=%.1f dcache_step=%.1f"
                      " debug_path_step=%.1f dcache_snapshots=%.1f memory_outputs=%.1f"
                      " cold_evaluate=%.1f cold_commit=%.1f\n",
              g[0] * ns_per_tick / n, g[1] * ns_per_tick / n,
              g[2] * ns_per_tick / n, g[3] * ns_per_tick / n,
              g[7] * ns_per_tick / n, g[8] * ns_per_tick / n, g[9] * ns_per_tick / n);
          chisa::boom_system::cold_module_timing_report(ns_per_tick, n);
        }
      }
#endif
      if (decode_windows != 0) {
        const double dw = static_cast<double>(decode_windows);
        std::printf(
            "LIVE_SIDECAR_TRANSPORT timed_windows=%" PRIu64
            " deltas_per_window=%.1f releveled_per_window=%.1f"
            " decode_ns_per_cycle=%.1f decode_timing=%s\n",
            decode_windows, static_cast<double>(decode_deltas) / dw,
            static_cast<double>(decode_releveled) / dw,
            decode_elapsed.count() * 1e9 / n,
#ifdef CHISA_PHASE_TIMERS
            "enabled"
#else
            options.joint_execution ? "groups-disabled" : "window"
#endif
            );
      }
      if (!options.overlap && roi_cold_valid) {
        const ColdCounters& now = roi_cold_end;
        std::printf(
            "LIVE_SIDECAR_COLD timed_cycles=%" PRIu64 " cm_skip=%" PRIu64
            " cm_la_skip=%" PRIu64 " sbus_eval=%" PRIu64
            " sbus_skip=%" PRIu64 " cm_pre=%" PRIu64 " cm_pre_eq_lookahead=%" PRIu64
            " cm_pre_recomputed=%" PRIu64 "\n",
            timed_cycles, now.cm_skip - roi_cold.cm_skip,
            now.cm_la_skip - roi_cold.cm_la_skip,
            now.sbus_eval - roi_cold.sbus_eval,
            now.sbus_skip - roi_cold.sbus_skip,
            now.cm_pre - roi_cold.cm_pre,
            now.cm_pre_eq - roi_cold.cm_pre_eq,
            now.cm_pre_recomputed - roi_cold.cm_pre_recomputed);
      }
    }
#if defined(CHISA_WINDOW_TIMELINE)
    chisa::boom_repcut::window_timeline->write(kWindow);
#endif
    return 0;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "live sidecar error: %s\n", error.what());
    return 2;
  }
}
