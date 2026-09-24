// Feasibility measurement for speculative segment-parallel oracle
// production: a speculative reference-model instance would start from a
// checkpoint whose slow state (predictor tables) is Delta cycles stale
// while its fast state is exact.  This harness boots two identical model
// instances (boot is cycle-deterministic), runs them in lockstep past the
// ROI entry, verifies they are bit-identical, then swaps Delta-stale
// predictor state into instance B and measures per-cycle divergence:
// how often B's oracle-visible state differs from A's, how long the
// mismatch bursts last, and whether B converges back to A.
//
//   DIVERGE_DELTA    staleness in cycles (default 65536)
//   DIVERGE_WARM     lockstep cycles before the swap, after quiesce
//                    (default 131072; the swap happens at its end)
//   DIVERGE_MEASURE  lockstep cycles measured after the swap (default 262144)
//   DIVERGE_STALE    comma list from {tage,btb,bim,loop,ubtb} (default all)
//
// usage: run-model-divergence -- BINARY

#include <fesvr/dtm.h>

#include <elf.h>

#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "fesvr_debug_bootstrap.h"
#include "system_guider.h"

namespace {

using chisa::boom_system::SystemGuider;

constexpr std::uint64_t kDebugPcMask = (UINT64_C(1) << 41) - UINT64_C(1);
constexpr std::uint64_t kMaxInitializationCycles = UINT64_C(10000000);
constexpr std::uint64_t kMaxDebugQuiesceCycles = UINT64_C(100000);

std::uint64_t elf_entry_point(const char* path) {
  std::FILE* file = std::fopen(path, "rb");
  if (!file) { std::perror(path); std::exit(2); }
  unsigned char ident[EI_NIDENT]{};
  if (std::fread(ident, sizeof(ident), 1, file) != 1 ||
      std::memcmp(ident, ELFMAG, SELFMAG) != 0 ||
      ident[EI_DATA] != ELFDATA2LSB) {
    std::fprintf(stderr, "unsupported target ELF: %s\n", path);
    std::exit(2);
  }
  std::rewind(file);
  std::uint64_t entry = 0;
  if (ident[EI_CLASS] == ELFCLASS64) {
    Elf64_Ehdr header{};
    if (std::fread(&header, sizeof(header), 1, file) != 1) std::exit(2);
    entry = header.e_entry;
  } else {
    Elf32_Ehdr header{};
    if (std::fread(&header, sizeof(header), 1, file) != 1) std::exit(2);
    entry = header.e_entry;
  }
  std::fclose(file);
  return entry;
}

bool target_entry_reached(const SystemGuider& model, std::uint64_t entry) {
  const auto& core = model.backend().core();
  return !model.reset_asserted() && !core.csr.debug &&
         (core.out_ifu_debug_fetch_pc_0 & kDebugPcMask) ==
             (entry & kDebugPcMask);
}

struct Instance {
  dtm_t dtm;
  chisa::boom_repcut::FesvrDebugBootstrap<dtm_t> debug;
  SystemGuider model;

  Instance(std::vector<char*>& htif_argv, int argc, char** argv,
           const char* image)
      : dtm(static_cast<int>(htif_argv.size()), htif_argv.data()),
        debug(dtm),
        model([&] {
          chisa::boom_system::BoundaryConfig config;
          config.image_path = image;
          config.argc = argc;
          config.argv = argv;
          config.debug_bootstrap = &debug;
          return config;
        }()) {
    model.set_oracle_sampling_enabled(false);
  }

  // Boot to the quiesced ROI boundary exactly the way the producer
  // benchmark does; returns the initialization cycle count or aborts.
  std::uint64_t boot(std::uint64_t entry, const char* tag) {
    std::uint64_t cycles = 0;
    while (!target_entry_reached(model, entry) &&
           cycles < kMaxInitializationCycles && !dtm.done()) {
      if (!model.step().ok) { std::fprintf(stderr, "%s: step failed\n", tag); std::exit(3); }
      ++cycles;
    }
    if (!target_entry_reached(model, entry)) {
      std::fprintf(stderr, "%s: ROI not reached\n", tag);
      std::exit(4);
    }
    while ((!debug.at_idle_nop_boundary() ||
            model.backend().core().csr.debug) &&
           cycles < kMaxInitializationCycles && !dtm.done()) {
      if (!model.step().ok) std::exit(3);
      ++cycles;
    }
    debug.begin_dmi_quiesce();
    std::uint64_t quiesce = 0;
    while (!(debug.dmi_quiesced() && model.debug_roi_quiescent()) &&
           quiesce < kMaxDebugQuiesceCycles) {
      if (!model.step().ok) std::exit(3);
      ++cycles;
      ++quiesce;
    }
    if (!(debug.dmi_quiesced() && model.debug_roi_quiescent())) {
      std::fprintf(stderr, "%s: no debug fixed point\n", tag);
      std::exit(4);
    }
    return cycles;
  }
};

// One stale-able predictor component: where it lives in both instances and
// a byte snapshot of A's copy taken Delta cycles before the swap.
struct StaleTarget {
  const char* name;
  const void* src;          // inside A
  void* dst;                // inside B
  std::size_t bytes;
  std::vector<unsigned char> snapshot;
  bool enabled = false;
};

template <class T>
StaleTarget make_target(const char* name, const T& a_ref, const T& b_ref) {
  return StaleTarget{name, &a_ref, const_cast<T*>(&b_ref), sizeof(T), {}, false};
}

std::uint64_t env_u64(const char* name, std::uint64_t fallback) {
  const char* text = std::getenv(name);
  if (text == nullptr) return fallback;
  char* end = nullptr;
  const std::uint64_t parsed = std::strtoull(text, &end, 0);
  return end != text && *end == '\0' ? parsed : fallback;
}

}  // namespace

int main(int argc, char** argv) {
  int separator = -1;
  for (int index = 1; index < argc; ++index)
    if (std::strcmp(argv[index], "--") == 0) { separator = index; break; }
  if (separator < 0 || separator + 1 >= argc) {
    std::fprintf(stderr, "usage: %s -- BINARY\n", argv[0]);
    return 2;
  }
  std::vector<char*> htif_argv;
  htif_argv.push_back(argv[0]);
  for (int index = separator + 1; index < argc; ++index)
    htif_argv.push_back(argv[index]);
  const char* image = argv[separator + 1];
  const std::uint64_t entry = elf_entry_point(image);

  const std::uint64_t delta = env_u64("DIVERGE_DELTA", 65536);
  const std::uint64_t warm = env_u64("DIVERGE_WARM", 131072);
  const std::uint64_t measure = env_u64("DIVERGE_MEASURE", 262144);
  const std::string stale_list = [] {
    const char* text = std::getenv("DIVERGE_STALE");
    return std::string(text ? text : "tage,btb,bim,loop,ubtb");
  }();
  if (delta > warm) { std::fprintf(stderr, "DELTA must be <= WARM\n"); return 2; }

  // Two independent instances; boot is cycle-deterministic (the producer
  // bench digest is run-stable), verified below by a byte comparison.
  std::vector<char*> htif_argv_b = htif_argv;
  Instance a(htif_argv, argc, argv, image);
  Instance b(htif_argv_b, argc, argv, image);
  const std::uint64_t boot_a = a.boot(entry, "A");
  const std::uint64_t boot_b = b.boot(entry, "B");
  if (boot_a != boot_b) {
    std::fprintf(stderr, "boot cycle counts differ: %" PRIu64 " vs %" PRIu64
                         " -- boots are not deterministic\n", boot_a, boot_b);
    return 5;
  }

  StaleTarget targets[] = {
      make_target("tage", a.model.frontend().tage_for_diagnostic(),
                  b.model.frontend().tage_for_diagnostic()),
      make_target("btb", a.model.frontend().btb_for_diagnostic(),
                  b.model.frontend().btb_for_diagnostic()),
      make_target("bim", a.model.frontend().bim_for_diagnostic(),
                  b.model.frontend().bim_for_diagnostic()),
      make_target("loop", a.model.frontend().loop_for_diagnostic(),
                  b.model.frontend().loop_for_diagnostic()),
      make_target("ubtb", a.model.frontend().fa_micro_btb_for_diagnostic(),
                  b.model.frontend().fa_micro_btb_for_diagnostic()),
  };
  for (StaleTarget& t : targets)
    t.enabled = stale_list.find(t.name) != std::string::npos;

  const auto& omir_a = a.model.backend().core().omir;
  const auto& omir_b = b.model.backend().core().omir;
  const std::size_t omir_bytes = sizeof(a.model.backend().core().omir);

  const auto step_both = [&](const char* where) {
    if (!a.model.step().ok || !b.model.step().ok) {
      std::fprintf(stderr, "step failed during %s\n", where);
      std::exit(3);
    }
  };
  const auto equal_now = [&] {
    return std::memcmp(&omir_a, &omir_b, omir_bytes) == 0 &&
           (a.model.backend().core().out_ifu_debug_fetch_pc_0 ==
            b.model.backend().core().out_ifu_debug_fetch_pc_0);
  };

  // Determinism check before anything is perturbed.
  if (!equal_now()) {
    std::fprintf(stderr, "instances differ right after boot -- aborting\n");
    return 5;
  }

  // Warm in lockstep; snapshot A's predictor state Delta cycles before the
  // swap point.
  for (std::uint64_t cycle = 0; cycle < warm; ++cycle) {
    if (cycle == warm - delta)
      for (StaleTarget& t : targets)
        if (t.enabled) {
          t.snapshot.resize(t.bytes);
          std::memcpy(t.snapshot.data(), t.src, t.bytes);
        }
    step_both("warm");
  }
  if (!equal_now()) {
    std::fprintf(stderr, "instances diverged during warm -- aborting\n");
    return 5;
  }

  // The swap: B's slow state becomes Delta cycles stale; everything else
  // stays exact.  This is the speculative instance's starting condition.
  std::size_t stale_bytes_total = 0, stale_bytes_diff = 0;
  for (StaleTarget& t : targets) {
    if (!t.enabled) continue;
    stale_bytes_total += t.bytes;
    for (std::size_t i = 0; i < t.bytes; ++i)
      stale_bytes_diff +=
          t.snapshot[i] != static_cast<const unsigned char*>(t.src)[i];
    std::memcpy(t.dst, t.snapshot.data(), t.bytes);
  }

  // Measure: per-cycle divergence of the core oracle mirror + fetch PC,
  // burst statistics, and a residual curve for the stale objects.
  std::uint64_t divergent = 0, bursts = 0, burst_len = 0, max_burst = 0;
  std::uint64_t first_divergence = UINT64_C(0) - 1, last_divergence = 0;
  std::uint64_t tail_divergent = 0;
  const std::uint64_t tail_start = measure > 65536 ? measure - 65536 : 0;
  const std::uint64_t curve_every = 16384;
  for (std::uint64_t cycle = 0; cycle < measure; ++cycle) {
    step_both("measure");
    const bool diff = !equal_now();
    if (diff) {
      ++divergent;
      if (first_divergence == UINT64_C(0) - 1) first_divergence = cycle;
      last_divergence = cycle;
      if (burst_len == 0) ++bursts;
      ++burst_len;
      if (burst_len > max_burst) max_burst = burst_len;
      if (cycle >= tail_start) ++tail_divergent;
    } else {
      burst_len = 0;
    }
    if ((cycle + 1) % curve_every == 0) {
      std::size_t residual = 0;
      for (const StaleTarget& t : targets) {
        if (!t.enabled) continue;
        const auto* pa = static_cast<const unsigned char*>(t.src);
        const auto* pb = static_cast<const unsigned char*>(t.dst);
        for (std::size_t i = 0; i < t.bytes; ++i) residual += pa[i] != pb[i];
      }
      std::printf("DIVERGE_CURVE cycle=%" PRIu64 " divergent_so_far=%" PRIu64
                  " stale_residual_bytes=%zu\n",
                  cycle + 1, divergent, residual);
    }
  }

  std::printf(
      "DIVERGE_RESULT delta=%" PRIu64 " warm=%" PRIu64 " measure=%" PRIu64
      " stale=%s stale_bytes=%zu stale_bytes_initially_different=%zu"
      " divergent_cycles=%" PRIu64 " rate=%.6f bursts=%" PRIu64
      " max_burst=%" PRIu64 " first=%" PRIu64 " last=%" PRIu64
      " tail64k_rate=%.6f\n",
      delta, warm, measure, stale_list.c_str(), stale_bytes_total,
      stale_bytes_diff, divergent,
      static_cast<double>(divergent) / static_cast<double>(measure), bursts,
      max_burst, first_divergence == UINT64_C(0) - 1 ? 0 : first_divergence,
      last_divergence,
      static_cast<double>(tail_divergent) /
          static_cast<double>(measure - tail_start));
  return 0;
}
