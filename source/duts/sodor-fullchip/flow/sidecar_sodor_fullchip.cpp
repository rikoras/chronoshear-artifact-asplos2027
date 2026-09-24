// Independent SodorGuider + integrated memory/RF -> full-chip CHISA consumer.

#ifndef ESSENT_ORACLE_VERIFY
#define ESSENT_ORACLE_VERIFY 1
#endif
#ifndef SODOR_ORACLE_CHECKS
#define SODOR_ORACLE_CHECKS 1
#endif
#ifndef SODOR_RING_SLOTS
// The consumer keeps copies of the slot lines it has read in its private L2.
// When the producer rewrites a slot, every such line first needs a cross-core
// invalidation, and the producer's stores wait on those.  With 512 slots
// (7 MiB of live window data) the copies have aged out of the consumer's L2
// into the shared L3 by the time the slot comes round again, so the stores
// take the lines from L3 instead.  Measured on Zen 4 with the W32 Sodor
// consumer: 32 slots left the producer at 58 ns/cycle against 38 ns/cycle
// standalone, 512 slots brought it to 46, and 1024 or more slots pushed the
// live data past the L3 and slowed the consumer instead.
#define SODOR_RING_SLOTS 512
#endif
#define main _generated_main
#include "SodorFullChip.h"
#undef main

#include "fullchip_env.h"
#include "sidecar_writer_gen.inc"

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <pthread.h>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

namespace {

static constexpr int kWidth = SW_WIDTH;
static constexpr int kCyclesPerWindow = SW_CPW;
static constexpr long kRingSlots = SODOR_RING_SLOTS;

static_assert(kCyclesPerWindow == 2 * kWidth, "sidecar/window mismatch");
static_assert(kRingSlots > 0, "sidecar ring must contain at least one slot");
static_assert(ORACLE_BLOCK_BYTES == SW_BLOCK_BYTES,
              "writer block disagrees with generated kernel");
static_assert(ORACLE_KERNEL_MIRRORED == SW_MIRRORED,
              "writer direction layout disagrees with generated kernel");
static_assert(sizeof(((SodorFullChip*)nullptr)->io_host_valid) /
                  sizeof(((SodorFullChip*)nullptr)->io_host_valid[0]) ==
              kWidth,
              "generated kernel width disagrees with writer");

struct alignas(64) RingSlot {
  alignas(64) char oracle[SW_BLOCK_BYTES];
  SodorDenseOracleBlockCache dense_cache;
  sodor::fullchip::CycleIO io[kCyclesPerWindow];
  // Recorded next to the window so a replay needs no reference model.
  uint8_t terminal = 0;
  uint64_t tohost = 0;
  uint64_t last_cycle = 0;
};

// Pre-recorded oracle trace (paper measurement protocol).  Recording captures
// every ring slot the consumer takes; replay drives the same consumer from the
// file with no reference model in the process, so the measured cost is RTL
// evaluation and Micro-Lockstep verification alone.
#pragma pack(push, 1)
struct TraceHeader {
  char magic[8];
  uint32_t width;
  uint32_t cycles_per_window;
  uint64_t block_bytes;
  uint32_t streams;
  uint32_t record_bytes;
  uint32_t mirrored;
  uint32_t reserved;
  uint64_t max_cycles;
};

struct TraceTrailer {
  char magic[8];
  uint64_t blocks;
  uint64_t pass_cycle;
  uint64_t final_cycle;
  uint64_t produced_cycles;
  uint64_t memory_hash;
  uint32_t tohost;
  uint32_t pc;
  uint32_t rf[32];
};
#pragma pack(pop)

static constexpr char kTraceMagic[8] = {'S', 'D', 'R', 'T', 'R', 'C', '0', '1'};
static constexpr char kTrailerMagic[8] = {'S', 'D', 'R', 'T', 'R', 'C', 'E',
                                          'N'};

static std::size_t trace_window_stride() {
  return static_cast<std::size_t>(SW_BLOCK_BYTES) +
         static_cast<std::size_t>(kCyclesPerWindow) *
             sizeof(sodor::fullchip::CycleIO) +
         1 + 8 + 8;
}

// The whole recorded trace is held in memory; replay copies one window per
// iteration so the timed loop never touches the filesystem.
struct TraceFile {
  std::vector<char> bytes;
  std::size_t stride = 0;
  uint64_t blocks = 0;
  TraceTrailer trailer{};

  const char* window(uint64_t index) const {
    return bytes.data() + sizeof(TraceHeader) + index * stride;
  }
};

struct ProducerFinal {
  uint64_t pass_cycle = 0;
  uint64_t final_cycle = 0;
  uint64_t produced_cycles = 0;
  uint32_t tohost = 0;
  uint32_t pc = 0;
  uint32_t rf[32]{};
  uint64_t memory_hash = 0;
  uint64_t sentinel_failures = 0;
  double active_ns = 0.0;
  double wait_ns = 0.0;
  uint64_t oracle_samples = 0;
  uint64_t oracle_stores = 0;
};

struct RunResult {
  uint64_t pass_cycle = 0;
  uint64_t final_cycle = 0;
  uint32_t tohost = 0;
  uint32_t pc = 0;
  uint32_t rf[32]{};
  uint64_t oracle_mismatches = 0;
  uint64_t output_mismatches = 0;
  uint64_t rf_mismatches = 0;
  uint64_t final_mismatches = 0;
  uint64_t sentinel_failures = 0;
  bool producer_error = false;

  bool clean() const {
    return pass_cycle != 0 && tohost == 1 && oracle_mismatches == 0 &&
           output_mismatches == 0 && rf_mismatches == 0 &&
           final_mismatches == 0 && sentinel_failures == 0 &&
           !producer_error;
  }
};

struct RunTiming {
  double total_ns = 0.0;
  double loop_ns = 0.0;
  double kernel_ns = 0.0;
  double oracle_decode_ns = 0.0;
  double consumer_wait_ns = 0.0;
  double producer_active_ns = 0.0;
  double producer_wait_ns = 0.0;
  uint64_t pass_cycles = 0;
  uint64_t producer_cycles = 0;
};

struct Summary {
  double mean = 0.0;
  double sd = 0.0;
};

static std::unique_ptr<RingSlot[]> g_ring;
// Change records for --producer=sparse only.  They live outside the ring
// slots so the dense ring stays compact.
static std::unique_ptr<SodorOracleDelta[]> g_deltas;
alignas(64) static std::atomic<long> g_blocks_ready{-1};
alignas(64) static std::atomic<long> g_blocks_done{-1};
alignas(64) static std::atomic<bool> g_stop{false};
alignas(64) static std::atomic<bool> g_producer_finished{false};
alignas(64) static std::atomic<bool> g_producer_error{false};
static const char* g_image_path = nullptr;
static uint64_t g_max_cycles = 0;
static bool g_strict_sentinels = false;
static bool g_overlap = false;
enum class ProducerMode { Baseline, Optimized, Sparse };
static ProducerMode g_producer_mode = ProducerMode::Optimized;
static ProducerFinal g_producer_final;
static std::string g_producer_error_text;
static cpu_set_t g_process_affinity;
static bool g_process_affinity_valid = false;
static const char* g_record_path = nullptr;
static const char* g_replay_path = nullptr;
static std::FILE* g_record_file = nullptr;
static uint64_t g_recorded_blocks = 0;
static bool g_replaying = false;
static TraceFile g_trace;
static double g_loop_ns = 0.0;

static void spin_pause() {
#if defined(__x86_64__) || defined(_M_X64)
  __builtin_ia32_pause();
#elif defined(__aarch64__)
  __asm__ __volatile__("yield");
#else
  std::this_thread::yield();
#endif
}

static Summary summarize(const std::vector<double>& values) {
  Summary result;
  if (values.empty()) return result;
  double sum = 0.0;
  double sum2 = 0.0;
  for (double value : values) {
    sum += value;
    sum2 += value * value;
  }
  result.mean = sum / values.size();
  result.sd = std::sqrt(std::max(
      0.0, sum2 / values.size() - result.mean * result.mean));
  return result;
}

static void capture_process_affinity() {
  if (pthread_getaffinity_np(pthread_self(), sizeof(g_process_affinity),
                             &g_process_affinity) == 0)
    g_process_affinity_valid = true;
}

static void restore_process_affinity() {
  if (g_process_affinity_valid)
    pthread_setaffinity_np(pthread_self(), sizeof(g_process_affinity),
                           &g_process_affinity);
}

static void pin_current_thread(const char* variable) {
  const char* text = std::getenv(variable);
  if (!text || !*text) return;
  const int cpu = std::atoi(text);
  if (cpu < 0 || cpu >= CPU_SETSIZE) return;
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(cpu, &set);
  const int error =
      pthread_setaffinity_np(pthread_self(), sizeof(set), &set);
  if (error)
    std::fprintf(stderr, "WARNING: cannot pin %s to CPU %d: %s\n",
                 variable, cpu, std::strerror(error));
}

static int element_index(int position) {
  if (!SW_MIRRORED || position < kWidth) return position;
  return 3 * kWidth - 1 - position;
}

static void fail_producer(const std::string& message) {
  g_producer_error_text = message;
  g_producer_error.store(true, std::memory_order_release);
  g_producer_finished.store(true, std::memory_order_release);
}

static bool producer_wait_for_slot(long block) {
  const auto begin = std::chrono::steady_clock::now();
  while (block - g_blocks_done.load(std::memory_order_acquire) >= kRingSlots) {
    if (g_stop.load(std::memory_order_relaxed)) return false;
    spin_pause();
  }
  g_producer_final.wait_ns += std::chrono::duration<double, std::nano>(
      std::chrono::steady_clock::now() - begin).count();
  return !g_stop.load(std::memory_order_relaxed);
}

// One producer state machine serves both execution modes.  Serial mode calls
// produce_block immediately before consuming that window and therefore uses
// one OS thread and no spin wait.  --overlap runs the same state machine in a
// producer thread behind the bounded ring.
class ProducerRunner {
 public:
  bool initialize() {
    const auto begin = std::chrono::steady_clock::now();
    if (!env_.init(g_image_path)) {
      add_active(begin);
      fail_producer(std::string("cannot load image: ") + g_image_path);
      return false;
    }
    initialized_ = true;
    add_active(begin);
    return true;
  }

  bool produce_block(long block, bool wait_for_slot) {
    if (!initialized_) return false;
    if (wait_for_slot && !producer_wait_for_slot(block)) return false;
    const auto begin = std::chrono::steady_clock::now();
    RingSlot& slot = g_ring[block % kRingSlots];
    slot.terminal = 0;
    slot.tohost = 0;
    slot.last_cycle = 0;
    if (g_producer_mode == ProducerMode::Sparse)
      optimized_writer_.begin_window(g_deltas[block % kRingSlots]);
    else if (g_producer_mode == ProducerMode::Optimized)
      dense_writer_.begin_window(slot.oracle, &slot.dense_cache);
    else if (g_producer_mode == ProducerMode::Baseline)
      std::memset(slot.oracle, 0, sizeof(slot.oracle));
    for (int position = 0; position < kCyclesPerWindow; ++position) {
      if (g_producer_mode == ProducerMode::Sparse)
        optimized_writer_.write_cycle(env_, g_deltas[block % kRingSlots],
                                      position);
      else if (g_producer_mode == ProducerMode::Optimized)
        dense_writer_.write_cycle(env_, slot.oracle, position,
                                  element_index(position));
      else
        sw_write_cycle_baseline(env_, slot.oracle, element_index(position));
      env_.step_cycle(slot.io[position]);
      if (slot.io[position].out.success) {
        saw_pass_ = true;
        slot.terminal = 1;
      }
      if (g_strict_sentinels) {
        const auto failures = env_.sentinel_failures();
        if (!failures.empty()) {
          ++g_producer_final.sentinel_failures;
          add_active(begin);
          fail_producer("cycle " + std::to_string(env_.cycle()) +
                        " sentinel: " + failures.front());
          return false;
        }
      }
    }
    slot.tohost = slot.io[kCyclesPerWindow - 1].out.tohost;
    slot.last_cycle = slot.io[kCyclesPerWindow - 1].cycle;
    g_producer_final.produced_cycles = env_.cycle();
    g_blocks_ready.store(block, std::memory_order_release);
    add_active(begin);
    return true;
  }

  bool saw_pass() const { return saw_pass_; }

  void finish() {
    if (!initialized_ || finalized_) return;
    const auto begin = std::chrono::steady_clock::now();
    g_producer_final.pass_cycle = env_.pass_cycle();
    g_producer_final.final_cycle = env_.cycle();
    g_producer_final.tohost = env_.tohost();
    g_producer_final.pc = env_.pc();
    std::memcpy(g_producer_final.rf, env_.regfile().values,
                sizeof(g_producer_final.rf));
    g_producer_final.memory_hash =
        sodor::fullchip::hash_memory(env_.memory());
    g_producer_final.oracle_samples =
        g_producer_mode == ProducerMode::Sparse
            ? optimized_writer_.sampled()
            : env_.cycle() * static_cast<uint64_t>(SW_NUM_STREAMS);
    g_producer_final.oracle_stores =
        g_producer_mode == ProducerMode::Sparse
            ? optimized_writer_.stored()
            : env_.cycle() * static_cast<uint64_t>(SW_NUM_STREAMS);
    add_active(begin);
    finalized_ = true;
    g_producer_finished.store(true, std::memory_order_release);
  }

 private:
  void add_active(std::chrono::steady_clock::time_point begin) {
    g_producer_final.active_ns += std::chrono::duration<double, std::nano>(
        std::chrono::steady_clock::now() - begin).count();
  }

  sodor::fullchip::FullChipEnv env_;
  SodorDenseOracleWriter dense_writer_;
  SodorOracleWriter optimized_writer_;
  bool initialized_ = false;
  bool finalized_ = false;
  bool saw_pass_ = false;
};

static void produce_oracles() {
  pin_current_thread("SIDECAR_CPU_PROD");
  ProducerRunner producer;
  if (!producer.initialize()) return;

  const long block_count = static_cast<long>(
      (g_max_cycles + kCyclesPerWindow - 1) / kCyclesPerWindow);
  for (long block = 0; block < block_count; ++block) {
    if (!producer.produce_block(block, true)) {
      if (g_producer_error.load(std::memory_order_acquire)) return;
      break;
    }
    if (producer.saw_pass()) break;
  }
  producer.finish();
}

static int start_producer_thread(pthread_t* thread) {
  pthread_attr_t attributes;
  int error = pthread_attr_init(&attributes);
  if (error) return error;
  const char* requested_cpu = std::getenv("SIDECAR_CPU_PROD");
  if (requested_cpu && *requested_cpu) {
    const int cpu = std::atoi(requested_cpu);
    if (cpu < 0 || cpu >= CPU_SETSIZE) {
      pthread_attr_destroy(&attributes);
      return EINVAL;
    }
    cpu_set_t affinity;
    CPU_ZERO(&affinity);
    CPU_SET(cpu, &affinity);
    error = pthread_attr_setaffinity_np(&attributes, sizeof(affinity), &affinity);
  }
  if (!error) {
    // Set affinity before the worker enters user code.  Inheriting the
    // consumer's single-core mask and moving only inside produce_oracles()
    // can leave the worker waiting for a scheduler timeslice while its parent
    // spins on that same core.  Oracle production still starts inside the
    // existing whole-run timer, and no window is produced ahead of that timer.
    error = pthread_create(thread, &attributes, [](void*) -> void* {
      produce_oracles();
      return nullptr;
    }, nullptr);
  }
  pthread_attr_destroy(&attributes);
  return error;
}

static bool wait_for_block(long block, double* wait_ns) {
  const auto begin = std::chrono::steady_clock::now();
  while (g_blocks_ready.load(std::memory_order_acquire) < block) {
    if (g_producer_error.load(std::memory_order_acquire)) return false;
    if (g_producer_finished.load(std::memory_order_acquire) &&
        g_blocks_ready.load(std::memory_order_acquire) < block)
      return false;
    spin_pause();
  }
  if (wait_ns)
    *wait_ns += std::chrono::duration<double, std::nano>(
        std::chrono::steady_clock::now() - begin).count();
  return true;
}

// Reads and validates a recorded trace.  A file whose geometry does not match
// this binary is refused: replaying another width's or another contract's
// windows would silently measure the wrong thing.
static bool load_trace(const char* path) {
  std::FILE* file = std::fopen(path, "rb");
  if (!file) {
    std::fprintf(stderr, "FULLCHIP TRACE ERROR: cannot open %s\n", path);
    return false;
  }
  std::fseek(file, 0, SEEK_END);
  const long size = std::ftell(file);
  std::fseek(file, 0, SEEK_SET);
  if (size < static_cast<long>(sizeof(TraceHeader) + sizeof(TraceTrailer))) {
    std::fclose(file);
    std::fprintf(stderr, "FULLCHIP TRACE ERROR: %s is too short\n", path);
    return false;
  }
  g_trace.bytes.resize(static_cast<std::size_t>(size));
  const bool read_ok =
      std::fread(g_trace.bytes.data(), 1, g_trace.bytes.size(), file) ==
      g_trace.bytes.size();
  std::fclose(file);
  if (!read_ok) {
    std::fprintf(stderr, "FULLCHIP TRACE ERROR: short read on %s\n", path);
    return false;
  }

  TraceHeader header{};
  std::memcpy(&header, g_trace.bytes.data(), sizeof(header));
  if (std::memcmp(header.magic, kTraceMagic, sizeof(kTraceMagic))) {
    std::fprintf(stderr, "FULLCHIP TRACE ERROR: bad magic in %s\n", path);
    return false;
  }
  if (header.width != static_cast<uint32_t>(kWidth) ||
      header.cycles_per_window != static_cast<uint32_t>(kCyclesPerWindow) ||
      header.block_bytes != static_cast<uint64_t>(SW_BLOCK_BYTES) ||
      header.streams != static_cast<uint32_t>(SW_NUM_STREAMS) ||
      header.record_bytes != sizeof(sodor::fullchip::CycleIO) ||
      header.mirrored != static_cast<uint32_t>(SW_MIRRORED)) {
    std::fprintf(stderr,
        "FULLCHIP TRACE ERROR: %s geometry does not match this binary "
        "(file W=%u cpw=%u block=%llu streams=%u record=%u mirrored=%u; "
        "binary W=%d cpw=%d block=%lld streams=%d record=%zu mirrored=%d)\n",
        path, header.width, header.cycles_per_window,
        static_cast<unsigned long long>(header.block_bytes), header.streams,
        header.record_bytes, header.mirrored, kWidth, kCyclesPerWindow,
        static_cast<long long>(SW_BLOCK_BYTES), SW_NUM_STREAMS,
        sizeof(sodor::fullchip::CycleIO), SW_MIRRORED);
    return false;
  }

  g_trace.stride = trace_window_stride();
  const std::size_t payload =
      g_trace.bytes.size() - sizeof(TraceHeader) - sizeof(TraceTrailer);
  if (!g_trace.stride || payload % g_trace.stride) {
    std::fprintf(stderr,
        "FULLCHIP TRACE ERROR: %s payload is not a whole number of windows\n",
        path);
    return false;
  }
  g_trace.blocks = payload / g_trace.stride;
  std::memcpy(&g_trace.trailer,
              g_trace.bytes.data() + g_trace.bytes.size() -
                  sizeof(TraceTrailer),
              sizeof(TraceTrailer));
  if (std::memcmp(g_trace.trailer.magic, kTrailerMagic,
                  sizeof(kTrailerMagic))) {
    std::fprintf(stderr, "FULLCHIP TRACE ERROR: bad trailer magic in %s\n",
                 path);
    return false;
  }
  if (g_trace.trailer.blocks != g_trace.blocks) {
    std::fprintf(stderr,
        "FULLCHIP TRACE ERROR: %s trailer claims %llu windows, file holds "
        "%llu\n", path,
        static_cast<unsigned long long>(g_trace.trailer.blocks),
        static_cast<unsigned long long>(g_trace.blocks));
    return false;
  }
  return true;
}

static void replay_fill(long block, RingSlot& slot) {
  const char* cursor = g_trace.window(static_cast<uint64_t>(block));
  std::memcpy(slot.oracle, cursor, static_cast<std::size_t>(SW_BLOCK_BYTES));
  cursor += SW_BLOCK_BYTES;
  const std::size_t io_bytes = static_cast<std::size_t>(kCyclesPerWindow) *
                               sizeof(sodor::fullchip::CycleIO);
  std::memcpy(slot.io, cursor, io_bytes);
  cursor += io_bytes;
  std::memcpy(&slot.terminal, cursor, 1);
  cursor += 1;
  std::memcpy(&slot.tohost, cursor, 8);
  cursor += 8;
  std::memcpy(&slot.last_cycle, cursor, 8);
}

static bool record_slot(const RingSlot& slot) {
  const std::size_t block_bytes = static_cast<std::size_t>(SW_BLOCK_BYTES);
  if (std::fwrite(slot.oracle, 1, block_bytes, g_record_file) != block_bytes)
    return false;
  const std::size_t cycles = static_cast<std::size_t>(kCyclesPerWindow);
  if (std::fwrite(slot.io, sizeof(sodor::fullchip::CycleIO), cycles,
                  g_record_file) != cycles)
    return false;
  const uint8_t terminal = slot.terminal;
  const uint64_t tohost = slot.tohost;
  const uint64_t last_cycle = slot.last_cycle;
  if (std::fwrite(&terminal, 1, 1, g_record_file) != 1) return false;
  if (std::fwrite(&tohost, 8, 1, g_record_file) != 1) return false;
  if (std::fwrite(&last_cycle, 8, 1, g_record_file) != 1) return false;
  ++g_recorded_blocks;
  return true;
}

static const sodor::fullchip::CycleIO& cycle_io(uint64_t cycle) {
  const uint64_t zero_based = cycle - 1;
  const long block = static_cast<long>(zero_based / kCyclesPerWindow);
  const int position = static_cast<int>(zero_based % kCyclesPerWindow);
  return g_ring[block % kRingSlots].io[position];
}

static void drive_lane(SodorFullChip& top, int lane,
                       const sodor::fullchip::HostInputs& host) {
  top.io_host_valid[lane] = UInt<1>(host.valid);
  top.io_host_write[lane] = UInt<1>(host.write);
  top.io_host_addr[lane] = UInt<32>(host.addr);
  top.io_host_wdata[lane] = UInt<32>(host.wdata);
}

static void report_mismatch(RunResult& result, uint64_t cycle, int lane,
                            const char* field, uint64_t rtl,
                            uint64_t model) {
  if (rtl == model) return;
  if (result.output_mismatches < 20) {
    std::fprintf(stderr,
        "FULLCHIP OUTPUT MISMATCH cycle=%llu lane=%d field=%s "
        "rtl=0x%llx model=0x%llx\n",
        static_cast<unsigned long long>(cycle), lane, field,
        static_cast<unsigned long long>(rtl),
        static_cast<unsigned long long>(model));
  }
  ++result.output_mismatches;
}

static void compare_lane(SodorFullChip& top, int lane,
                         const sodor::fullchip::CycleIO& io,
                         RunResult& result) {
#define CHECK(NAME, RTL, MODEL) \
  report_mismatch(result, io.cycle, lane, NAME, \
                  static_cast<uint64_t>(RTL), \
                  static_cast<uint64_t>(MODEL))
  CHECK("host.ready", top.io_host_ready[lane].as_single_word(),
        io.out.host_ready);
  CHECK("host.rdata", top.io_host_rdata[lane].as_single_word(),
        io.out.host_rdata);
  CHECK("success", top.io_success[lane].as_single_word(), io.out.success);
  CHECK("tohost", top.io_tohost[lane].as_single_word(), io.out.tohost);
#undef CHECK
  if (io.out.success && result.pass_cycle == 0) {
    result.pass_cycle = io.cycle;
    result.tohost = io.out.tohost;
  }
}

static void initialize_top_state(SodorFullChip& top) {
  // The 2 MiB RTL memory is deliberately absent from the consumer.  Its read
  // data is injected and its complete ordered access trace is checked instead.
  for (unsigned index = 0; index < 32; ++index)
    top.regfile.regfile[index] = UInt<32>(0);
}

static bool consume(SodorFullChip& top, RunResult& result, RunTiming* timing,
                    ProducerRunner* serial_producer) {
  alignas(64) static const char reset_oracles[SW_BLOCK_BYTES] = {};
  alignas(64) std::array<char, static_cast<std::size_t>(SW_BLOCK_BYTES)>
      expanded_oracles{};
  SodorOracleDecoder oracle_decoder;
  top.oracle_cycle = 1;
  top.oracle_win_base = reset_oracles;
  top.reset = UInt<1>(1);
  const sodor::fullchip::HostInputs idle{};
  for (unsigned reset_cycle = 0; reset_cycle < 5; ++reset_cycle) {
    for (int lane = 0; lane < kWidth; ++lane) drive_lane(top, lane, idle);
    top.eval(true, false, false);
  }
  top.reset = UInt<1>(0);
  top.verify_mismatches = 0;
  top.assert_triggered = false;
  top.checks_enabled = SODOR_ORACLE_CHECKS != 0;

  long block_count = static_cast<long>(
      (g_max_cycles + kCyclesPerWindow - 1) / kCyclesPerWindow);
  if (g_replaying && block_count > static_cast<long>(g_trace.blocks))
    block_count = static_cast<long>(g_trace.blocks);
  // Loop-only timing: excludes trace reading, kernel construction, reset and
  // the final-state comparison, so a replay measures evaluation alone.
  const auto loop_begin = std::chrono::steady_clock::now();
  for (long block = 0; block < block_count; ++block) {
    RingSlot& slot = g_ring[block % kRingSlots];
    if (g_replaying) {
      replay_fill(block, slot);
    } else if (serial_producer) {
      if (!serial_producer->produce_block(block, false)) return false;
    } else if (!wait_for_block(
                   block, timing ? &timing->consumer_wait_ns : nullptr)) {
      return false;
    }
    if (g_record_file && !record_slot(slot)) {
      std::fprintf(stderr, "FULLCHIP TRACE WRITE ERROR block=%ld\n", block);
      return false;
    }
    if (g_producer_mode == ProducerMode::Sparse) {
      const auto decode_begin = std::chrono::steady_clock::now();
      if (!oracle_decoder.decode(g_deltas[block % kRingSlots],
                                 expanded_oracles.data())) {
        std::fprintf(stderr, "FULLCHIP ORACLE DELTA DECODE ERROR block=%ld\n",
                     block);
        return false;
      }
      if (timing)
        timing->oracle_decode_ns += std::chrono::duration<double, std::nano>(
            std::chrono::steady_clock::now() - decode_begin).count();
      top.oracle_win_base = expanded_oracles.data();
    } else {
      top.oracle_win_base = slot.oracle;
    }
    const int first = top.oracle_cycle;

    uint64_t forward_cycles[kWidth];
    uint64_t reverse_cycles[kWidth];
    for (int lane = 0; lane < kWidth; ++lane) {
      forward_cycles[lane] = static_cast<uint64_t>(first + lane);
      reverse_cycles[lane] =
          static_cast<uint64_t>(first + 2 * kWidth - 1 - lane);
      drive_lane(top, lane, cycle_io(forward_cycles[lane]).in);
    }
    const auto f_begin = std::chrono::steady_clock::now();
    top.eval_forward(true, false, true);
    const auto f_end = std::chrono::steady_clock::now();
    for (int lane = 0; lane < kWidth; ++lane)
      compare_lane(top, lane, cycle_io(forward_cycles[lane]), result);

    for (int lane = 0; lane < kWidth; ++lane)
      drive_lane(top, lane, cycle_io(reverse_cycles[lane]).in);
    const auto r_begin = std::chrono::steady_clock::now();
    top.eval_reverse(true, false, true);
    const auto r_end = std::chrono::steady_clock::now();
    for (int lane = kWidth - 1; lane >= 0; --lane)
      compare_lane(top, lane, cycle_io(reverse_cycles[lane]), result);

    if (timing) {
      timing->kernel_ns += std::chrono::duration<double, std::nano>(
          f_end - f_begin).count();
      timing->kernel_ns += std::chrono::duration<double, std::nano>(
          r_end - r_begin).count();
    }
    result.final_cycle = reverse_cycles[0];
    g_blocks_done.store(block, std::memory_order_release);
    if (result.pass_cycle || top.assert_triggered) break;
  }
  g_loop_ns = std::chrono::duration<double, std::nano>(
      std::chrono::steady_clock::now() - loop_begin).count();
  if (timing) timing->loop_ns = g_loop_ns;

  result.oracle_mismatches = top.verify_mismatches;
  result.pc = static_cast<uint32_t>(
      top.tile.core.d.if_reg_pc[0].as_single_word());
  for (unsigned index = 0; index < 32; ++index)
    result.rf[index] = static_cast<uint32_t>(
        top.regfile.regfile[index].as_single_word());
  return result.pass_cycle != 0;
}

static RunResult run_once(const char* image, uint64_t max_cycles,
                          bool strict_sentinels, RunTiming* timing) {
  const auto begin = std::chrono::steady_clock::now();
  RunResult result;
  g_image_path = image;
  g_max_cycles = max_cycles;
  g_strict_sentinels = strict_sentinels;
  g_producer_final = ProducerFinal{};
  g_producer_error_text.clear();
  g_blocks_ready.store(-1, std::memory_order_release);
  g_blocks_done.store(-1, std::memory_order_release);
  g_stop.store(false, std::memory_order_release);
  g_producer_finished.store(false, std::memory_order_release);
  g_producer_error.store(false, std::memory_order_release);

  SodorFullChip top;
  std::memset(&top.tile, 0, sizeof(top.tile));
  initialize_top_state(top);
  oracle_kernel_base = g_ring[0].oracle;

  restore_process_affinity();
  pin_current_thread("SIDECAR_CPU_CONS");
  if (g_replaying) {
    // No FullChipEnv, no SodorGuider, one thread: the oracles and the
    // producer's final state both come from the recorded file.
    consume(top, result, timing, nullptr);
    g_producer_final.pass_cycle = g_trace.trailer.pass_cycle;
    g_producer_final.final_cycle = g_trace.trailer.final_cycle;
    g_producer_final.produced_cycles = g_trace.trailer.produced_cycles;
    g_producer_final.tohost = g_trace.trailer.tohost;
    g_producer_final.pc = g_trace.trailer.pc;
    std::memcpy(g_producer_final.rf, g_trace.trailer.rf,
                sizeof(g_producer_final.rf));
    g_producer_final.memory_hash = g_trace.trailer.memory_hash;
    g_producer_final.oracle_samples = g_producer_final.produced_cycles *
                                      static_cast<uint64_t>(SW_NUM_STREAMS);
    g_producer_final.oracle_stores = g_producer_final.oracle_samples;
  } else if (g_overlap) {
    pthread_t producer;
    const int start_error = start_producer_thread(&producer);
    if (start_error) {
      fail_producer(std::string("cannot start producer: ") +
                    std::strerror(start_error));
    } else {
      consume(top, result, timing, nullptr);
      g_stop.store(true, std::memory_order_release);
      const int join_error = pthread_join(producer, nullptr);
      if (join_error)
        fail_producer(std::string("cannot join producer: ") +
                      std::strerror(join_error));
    }
  } else {
    ProducerRunner producer;
    if (producer.initialize()) {
      consume(top, result, timing, &producer);
      producer.finish();
    }
  }

  result.producer_error = g_producer_error.load(std::memory_order_acquire);
  result.sentinel_failures = g_producer_final.sentinel_failures;
  if (result.pass_cycle != g_producer_final.pass_cycle ||
      result.final_cycle != g_producer_final.final_cycle ||
      result.tohost != g_producer_final.tohost ||
      result.pc != g_producer_final.pc) {
    ++result.final_mismatches;
    std::fprintf(stderr,
        "FULLCHIP FINAL MISMATCH "
        "rtl pass/final/tohost/pc=%llu/%llu/0x%x/0x%x "
        "model=%llu/%llu/0x%x/0x%x\n",
        static_cast<unsigned long long>(result.pass_cycle),
        static_cast<unsigned long long>(result.final_cycle), result.tohost,
        result.pc,
        static_cast<unsigned long long>(g_producer_final.pass_cycle),
        static_cast<unsigned long long>(g_producer_final.final_cycle),
        g_producer_final.tohost, g_producer_final.pc);
  }
  for (unsigned index = 0; index < 32; ++index) {
    if (result.rf[index] == g_producer_final.rf[index]) continue;
    if (result.rf_mismatches < 20)
      std::fprintf(stderr,
          "FULLCHIP RF MISMATCH x%u rtl=0x%x model=0x%x\n", index,
          result.rf[index], g_producer_final.rf[index]);
    ++result.rf_mismatches;
  }

  if (timing) {
    timing->total_ns = std::chrono::duration<double, std::nano>(
        std::chrono::steady_clock::now() - begin).count();
    timing->producer_active_ns = g_producer_final.active_ns;
    timing->producer_wait_ns = g_producer_final.wait_ns;
    timing->pass_cycles = result.pass_cycle;
    timing->producer_cycles = g_producer_final.produced_cycles;
  }
  return result;
}

static void print_result(const RunResult& result) {
  const char* producer_mode = "optimized";
  if (g_producer_mode == ProducerMode::Baseline) producer_mode = "baseline";
  if (g_producer_mode == ProducerMode::Sparse) producer_mode = "sparse";
  std::printf(
      "tohost=0x%x pass=%llu final=%llu oracle_mismatches=%llu "
      "output_mismatches=%llu rf_mismatches=%llu final_mismatches=%llu "
      "sentinel_failures=%llu memory_hash=0x%016llx (%s) "
      "W=%d FULLCHIP_SIDECAR\n",
      result.tohost, static_cast<unsigned long long>(result.pass_cycle),
      static_cast<unsigned long long>(result.final_cycle),
      static_cast<unsigned long long>(result.oracle_mismatches),
      static_cast<unsigned long long>(result.output_mismatches),
      static_cast<unsigned long long>(result.rf_mismatches),
      static_cast<unsigned long long>(result.final_mismatches),
      static_cast<unsigned long long>(result.sentinel_failures),
      static_cast<unsigned long long>(g_producer_final.memory_hash),
      result.clean() ? "PASS" : "FAIL", kWidth);
  std::printf(
      "SODOR_FULLCHIP_TIMING mode=%s width=%d cycles=%llu "
      "loop_ns_per_cycle=%.2f\n",
      g_replaying ? "replay" : (g_overlap ? "overlap" : "serial"), kWidth,
      static_cast<unsigned long long>(result.pass_cycle),
      result.pass_cycle
          ? g_loop_ns / static_cast<double>(result.pass_cycle)
          : 0.0);
  std::printf("Producer: mode=%s execution=%s oracle_stores=%llu/%llu "
              "(%.2f%%)\n",
      producer_mode,
      g_replaying ? "replay" : (g_overlap ? "overlap" : "serial"),
      static_cast<unsigned long long>(g_producer_final.oracle_stores),
      static_cast<unsigned long long>(g_producer_final.oracle_samples),
      g_producer_final.oracle_samples
          ? 100.0 * static_cast<double>(g_producer_final.oracle_stores) /
                static_cast<double>(g_producer_final.oracle_samples)
          : 0.0);
  if (result.producer_error && !g_producer_error_text.empty())
    std::fprintf(stderr, "FULLCHIP PRODUCER ERROR: %s\n",
                 g_producer_error_text.c_str());
}

}  // namespace

#ifndef SODOR_FULLCHIP_NO_MAIN
int main(int argc, char** argv) {
  if (argc < 3) {
    std::fprintf(stderr,
        "Usage: %s mem.bin max_cycles [--bench N] "
        "[--producer=optimized|baseline|sparse] [--overlap]\n"
        "       [--record-trace=PATH] [--replay-trace=PATH]\n"
        "  optional affinity: SIDECAR_CPU_CONS=N SIDECAR_CPU_PROD=M\n",
        argv[0]);
    return 1;
  }
  const char* image = argv[1];
  const uint64_t max_cycles = std::strtoull(argv[2], nullptr, 0);
  int repetitions = 0;
  for (int index = 3; index < argc; ++index) {
    if (!std::strcmp(argv[index], "--bench") && index + 1 < argc)
      repetitions = std::atoi(argv[++index]);
    else if (!std::strcmp(argv[index], "--producer=optimized"))
      g_producer_mode = ProducerMode::Optimized;
    else if (!std::strcmp(argv[index], "--producer=baseline"))
      g_producer_mode = ProducerMode::Baseline;
    else if (!std::strcmp(argv[index], "--producer=sparse"))
      g_producer_mode = ProducerMode::Sparse;
    else if (!std::strcmp(argv[index], "--overlap"))
      g_overlap = true;
    else if (!std::strncmp(argv[index], "--record-trace=", 15))
      g_record_path = argv[index] + 15;
    else if (!std::strncmp(argv[index], "--replay-trace=", 15))
      g_replay_path = argv[index] + 15;
    else
      return 2;
  }
  if (!max_cycles) return 2;
  if (g_record_path && g_replay_path) {
    std::fprintf(stderr,
        "ERROR: --record-trace and --replay-trace are exclusive\n");
    return 2;
  }
  if ((g_record_path || g_replay_path) &&
      g_producer_mode == ProducerMode::Sparse) {
    std::fprintf(stderr,
        "ERROR: oracle traces hold dense windows; use "
        "--producer=optimized\n");
    return 2;
  }
  if (g_record_path && repetitions > 0) {
    std::fprintf(stderr,
        "ERROR: --record-trace records one run; drop --bench\n");
    return 2;
  }
  if (g_replay_path) {
    g_replaying = true;
    g_overlap = false;
    if (!load_trace(g_replay_path)) return 2;
  }

  g_ring = std::make_unique<RingSlot[]>(kRingSlots);
  if (g_producer_mode == ProducerMode::Sparse)
    g_deltas = std::make_unique<SodorOracleDelta[]>(kRingSlots);
  capture_process_affinity();
  if (g_record_path) {
    g_record_file = std::fopen(g_record_path, "wb");
    if (!g_record_file) {
      std::fprintf(stderr, "ERROR: cannot create oracle trace %s\n",
                   g_record_path);
      return 2;
    }
    TraceHeader header{};
    std::memcpy(header.magic, kTraceMagic, sizeof(kTraceMagic));
    header.width = static_cast<uint32_t>(kWidth);
    header.cycles_per_window = static_cast<uint32_t>(kCyclesPerWindow);
    header.block_bytes = static_cast<uint64_t>(SW_BLOCK_BYTES);
    header.streams = static_cast<uint32_t>(SW_NUM_STREAMS);
    header.record_bytes =
        static_cast<uint32_t>(sizeof(sodor::fullchip::CycleIO));
    header.mirrored = static_cast<uint32_t>(SW_MIRRORED);
    header.max_cycles = max_cycles;
    if (std::fwrite(&header, sizeof(header), 1, g_record_file) != 1) {
      std::fprintf(stderr, "ERROR: cannot write oracle trace header\n");
      return 2;
    }
  }
  const RunResult result = run_once(image, max_cycles, true, nullptr);
  if (g_record_file) {
    TraceTrailer trailer{};
    std::memcpy(trailer.magic, kTrailerMagic, sizeof(kTrailerMagic));
    trailer.blocks = g_recorded_blocks;
    trailer.pass_cycle = g_producer_final.pass_cycle;
    trailer.final_cycle = g_producer_final.final_cycle;
    trailer.produced_cycles = g_producer_final.produced_cycles;
    trailer.memory_hash = g_producer_final.memory_hash;
    trailer.tohost = g_producer_final.tohost;
    trailer.pc = g_producer_final.pc;
    std::memcpy(trailer.rf, g_producer_final.rf, sizeof(trailer.rf));
    const bool written =
        std::fwrite(&trailer, sizeof(trailer), 1, g_record_file) == 1;
    const bool closed = std::fclose(g_record_file) == 0;
    g_record_file = nullptr;
    if (!written || !closed) {
      std::fprintf(stderr, "ERROR: cannot finish oracle trace %s\n",
                   g_record_path);
      return 2;
    }
    std::printf("SODOR_TRACE_RECORDED path=%s width=%d blocks=%llu "
                "cycles=%llu block_bytes=%lld stride=%zu bytes=%zu\n",
        g_record_path, kWidth,
        static_cast<unsigned long long>(g_recorded_blocks),
        static_cast<unsigned long long>(g_recorded_blocks) * kCyclesPerWindow,
        static_cast<long long>(SW_BLOCK_BYTES), trace_window_stride(),
        sizeof(TraceHeader) +
            static_cast<std::size_t>(g_recorded_blocks) *
                trace_window_stride() +
            sizeof(TraceTrailer));
  }
  print_result(result);
  if (!result.clean()) return 1;

  if (repetitions > 0) {
    std::vector<double> total;
    std::vector<double> loop;
    std::vector<double> kernel;
    std::vector<double> oracle_decode;
    std::vector<double> wait;
    std::vector<double> producer;
    std::vector<double> producer_wait;
    for (int repetition = 0; repetition < repetitions; ++repetition) {
      RunTiming timing;
      const RunResult sample = run_once(image, max_cycles, false, &timing);
      if (!sample.clean()) {
        print_result(sample);
        return 1;
      }
      const double pass = static_cast<double>(timing.pass_cycles);
      const double produced = static_cast<double>(timing.producer_cycles);
      total.push_back(timing.total_ns / pass);
      loop.push_back(timing.loop_ns / pass);
      kernel.push_back(timing.kernel_ns / pass);
      oracle_decode.push_back(timing.oracle_decode_ns / pass);
      wait.push_back(timing.consumer_wait_ns / pass);
      producer.push_back(timing.producer_active_ns / produced);
      producer_wait.push_back(timing.producer_wait_ns / produced);
    }
    const Summary a = summarize(total);
    const Summary b = summarize(kernel);
    const Summary c = summarize(wait);
    const Summary d = summarize(producer);
    const Summary e = summarize(producer_wait);
    const Summary f = summarize(oracle_decode);
    const Summary g = summarize(loop);
    std::printf("Bench: mean=%.2f sd=%.2f ns/cycle (%d reps, full-chip %s)\n",
                a.mean, a.sd, repetitions, g_replaying ? "replay" : "live");
    std::printf("Loop: mean=%.2f sd=%.2f ns/cycle (%s)\n", g.mean, g.sd,
                g_replaying ? "replay" : "live");
    std::printf("KernelEval: mean=%.2f sd=%.2f ns/cycle\n", b.mean, b.sd);
    std::printf("OracleDecode: mean=%.2f sd=%.2f ns/cycle\n", f.mean, f.sd);
    std::printf("ConsumerWait: mean=%.2f sd=%.2f ns/cycle\n", c.mean, c.sd);
    std::printf("ProducerActive: mean=%.2f sd=%.2f ns/cycle\n", d.mean, d.sd);
    std::printf("ProducerRingWait: mean=%.2f sd=%.2f ns/cycle\n",
                e.mean, e.sd);
  }
  return 0;
}
#endif
