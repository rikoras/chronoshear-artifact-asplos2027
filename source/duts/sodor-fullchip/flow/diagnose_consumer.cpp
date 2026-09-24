// Diagnostic-only wrapper around the full-chip live runtime.  It permits a
// benchmark to continue when a compile-time experiment intentionally removes
// consumer shadow-state maintenance (for example ESSENT_ORACLE_VERIFY=0).
// Qualification and release builds must continue to use
// sidecar_sodor_fullchip.cpp directly.
#define SODOR_FULLCHIP_NO_MAIN 1
#include "sidecar_sodor_fullchip.cpp"

int main(int argc, char** argv) {
  if (argc < 4) {
    std::fprintf(stderr, "Usage: %s mem.bin max-cycles repetitions\n", argv[0]);
    return 2;
  }
  const char* const image = argv[1];
  const uint64_t max_cycles = std::strtoull(argv[2], nullptr, 0);
  const int repetitions = std::atoi(argv[3]);
  if (!max_cycles || repetitions <= 0) return 2;

  g_producer_mode = ProducerMode::Optimized;
  g_overlap = false;
  g_ring = std::make_unique<RingSlot[]>(kRingSlots);
  capture_process_affinity();

  const RunResult qualification = run_once(image, max_cycles, true, nullptr);
  print_result(qualification);
  if (!qualification.pass_cycle || qualification.tohost != 1 ||
      qualification.producer_error || qualification.output_mismatches ||
      qualification.sentinel_failures) {
    return 1;
  }

  std::vector<double> total;
  std::vector<double> kernel;
  std::vector<double> producer;
  for (int repetition = 0; repetition < repetitions; ++repetition) {
    RunTiming timing;
    const RunResult sample = run_once(image, max_cycles, false, &timing);
    if (!sample.pass_cycle || sample.tohost != 1 || sample.producer_error ||
        sample.output_mismatches || sample.sentinel_failures) {
      return 1;
    }
    total.push_back(timing.total_ns / timing.pass_cycles);
    kernel.push_back(timing.kernel_ns / timing.pass_cycles);
    producer.push_back(timing.producer_active_ns / timing.producer_cycles);
  }
  const Summary a = summarize(total);
  const Summary b = summarize(kernel);
  const Summary c = summarize(producer);
  std::printf(
      "DiagnosticBench: mean=%.2f sd=%.2f ns/cycle (%d reps)\n",
      a.mean, a.sd, repetitions);
  std::printf("DiagnosticKernel: mean=%.2f sd=%.2f ns/cycle\n",
              b.mean, b.sd);
  std::printf("DiagnosticProducer: mean=%.2f sd=%.2f ns/cycle\n",
              c.mean, c.sd);
  return 0;
}
