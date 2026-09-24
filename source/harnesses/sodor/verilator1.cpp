#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <vector>

#include "VSodorFullChip.h"
#include "VSodorFullChip___024root.h"
#include "verilated.h"

namespace {

constexpr std::size_t kMemoryBytes = 1u << 21;

struct Sample {
  uint64_t cycles = 0;
  uint32_t tohost = 0;
  uint64_t memory_hash = 0;
  uint32_t x0 = 0;
  double execution_ns = 0.0;
  double total_ns = 0.0;

  bool passed(uint64_t expected_cycles, uint64_t expected_hash) const {
    return tohost == 1 && (!expected_cycles || cycles == expected_cycles) &&
           (!expected_hash || memory_hash == expected_hash) && x0 == 0;
  }
};

struct Summary {
  double mean = 0.0;
  double sd = 0.0;
};

static std::vector<uint8_t> load_image(const char* path) {
  std::vector<uint8_t> image(kMemoryBytes, 0);
  std::ifstream stream(path, std::ios::binary);
  if (!stream) return {};
  stream.read(reinterpret_cast<char*>(image.data()), image.size());
  if (!stream.good() && !stream.eof()) return {};
  return image;
}

static inline void drive_idle(VSodorFullChip& top) {
  top.io_host_valid = 0;
  top.io_host_write = 0;
  top.io_host_addr = 0;
  top.io_host_wdata = 0;
}

static inline void tick(VSodorFullChip& top) {
  top.clock = 0;
  top.eval();
  top.clock = 1;
  top.eval();
}

static bool check_host_loader(VSodorFullChip& top) {
  top.io_host_valid = 1;
  top.io_host_write = 1;
  top.io_host_addr = 0x1ffu;
  top.io_host_wdata = 0xa55ac33cu;
  tick(top);

  top.io_host_write = 0;
  top.clock = 0;
  top.eval();
  return top.io_host_ready && top.io_host_rdata == 0xa55ac33cu;
}

static void load_backdoor(VSodorFullChip& top,
                          const std::vector<uint8_t>& image) {
  auto* const root = top.rootp;
  for (std::size_t index = 0; index < kMemoryBytes; ++index)
    root->SodorFullChip__DOT__memory__DOT__bytes[index] = image[index];
  for (unsigned index = 0; index < 32; ++index)
    root->SodorFullChip__DOT__regfile__DOT__regfile[index] = 0;
}

static uint64_t hash_memory(const VSodorFullChip& top) {
  uint64_t hash = 1469598103934665603ULL;
  const auto* const root = top.rootp;
  for (std::size_t index = 0; index < kMemoryBytes; ++index) {
    hash ^= root->SodorFullChip__DOT__memory__DOT__bytes[index];
    hash *= 1099511628211ULL;
  }
  return hash;
}

static Sample run_once(const char* image_path, uint64_t max_cycles) {
  const auto total_begin = std::chrono::steady_clock::now();
  Sample sample;
  const std::vector<uint8_t> image = load_image(image_path);
  if (image.size() != kMemoryBytes) return sample;

  VerilatedContext context;
  auto top = std::make_unique<VSodorFullChip>(&context);
  top->clock = 0;
  top->reset = 1;
  drive_idle(*top);
  // Execute Verilator's initialization before installing the deterministic
  // backdoor image.  No public-flat option is needed, so observing the memory
  // for setup and the final hash does not perturb the measured RTL schedule.
  top->eval();
  if (!check_host_loader(*top)) return sample;
  load_backdoor(*top, image);
  drive_idle(*top);

  for (unsigned cycle = 0; cycle < 5; ++cycle) tick(*top);
  top->reset = 0;

  const auto execution_begin = std::chrono::steady_clock::now();
  for (uint64_t cycle = 1; cycle <= max_cycles; ++cycle) {
    // Sodor's live model publishes the pre-edge tohost value and still
    // commits the corresponding edge.  Sample in the same order so the pass
    // cycle is directly comparable to the locked full-chip qualification.
    top->clock = 0;
    top->eval();
    const bool success = top->io_success;
    top->clock = 1;
    top->eval();
    if (context.gotFinish()) break;
    if (success) {
      sample.cycles = cycle;
      break;
    }
  }
  const auto execution_end = std::chrono::steady_clock::now();

  sample.tohost = top->io_tohost;
  sample.memory_hash = hash_memory(*top);
  sample.x0 = top->rootp->SodorFullChip__DOT__regfile__DOT__regfile[0];
  top->final();
  sample.execution_ns = std::chrono::duration<double, std::nano>(
      execution_end - execution_begin).count();
  sample.total_ns = std::chrono::duration<double, std::nano>(
      std::chrono::steady_clock::now() - total_begin).count();
  return sample;
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

}  // namespace

int main(int argc, char** argv) {
  Verilated::commandArgs(argc, argv);
  if (argc < 3) {
    std::fprintf(stderr,
        "Usage: %s mem.bin max-cycles [reps] [expected-cycles] "
        "[expected-memory-hash]\n",
        argv[0]);
    return 2;
  }
  const char* const image = argv[1];
  const uint64_t max_cycles = std::strtoull(argv[2], nullptr, 0);
  const int repetitions = argc > 3 ? std::atoi(argv[3]) : 10;
  const uint64_t expected_cycles =
      argc > 4 ? std::strtoull(argv[4], nullptr, 0) : 0;
  const uint64_t expected_hash =
      argc > 5 ? std::strtoull(argv[5], nullptr, 0) : 0;
  if (!max_cycles || repetitions <= 0) return 2;

  // One untimed qualification also warms the file cache and generated code.
  const Sample qualification = run_once(image, max_cycles);
  std::printf(
      "SODOR_FULLCHIP_VERILATOR status=%s cycles=%llu tohost=0x%x "
      "memory_hash=0x%016llx x0=0x%x\n",
      qualification.passed(expected_cycles, expected_hash) ? "pass" : "fail",
      static_cast<unsigned long long>(qualification.cycles),
      qualification.tohost,
      static_cast<unsigned long long>(qualification.memory_hash),
      qualification.x0);
  if (!qualification.passed(expected_cycles, expected_hash)) return 1;

  std::vector<double> execution;
  std::vector<double> total;
  for (int repetition = 0; repetition < repetitions; ++repetition) {
    const Sample sample = run_once(image, max_cycles);
    if (!sample.passed(expected_cycles, expected_hash)) {
      std::fprintf(stderr,
          "measurement %d failed: cycles=%llu tohost=0x%x "
          "memory_hash=0x%016llx x0=0x%x\n",
          repetition, static_cast<unsigned long long>(sample.cycles),
          sample.tohost, static_cast<unsigned long long>(sample.memory_hash),
          sample.x0);
      return 1;
    }
    execution.push_back(sample.execution_ns / sample.cycles);
    total.push_back(sample.total_ns / sample.cycles);
    std::printf("sample=%d execution=%.2f total=%.2f ns/cycle\n",
                repetition + 1, execution.back(), total.back());
  }

  const Summary execution_summary = summarize(execution);
  const Summary total_summary = summarize(total);
  std::printf(
      "VerilatorExecution: mean=%.2f sd=%.2f ns/cycle "
      "(%d reps, load/reset/final-hash excluded)\n",
      execution_summary.mean, execution_summary.sd, repetitions);
  std::printf(
      "VerilatorTotal: mean=%.2f sd=%.2f ns/cycle "
      "(%d reps, full-chip setup/run/final-hash)\n",
      total_summary.mean, total_summary.sd, repetitions);
  return 0;
}
