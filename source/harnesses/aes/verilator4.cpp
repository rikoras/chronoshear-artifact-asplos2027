// Verilator TB for AES Cipher MT4 baseline.
#include "VCipher.h"
#include "verilated.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>

static constexpr unsigned kVerilatorThreads = 4;

static void dut_cycle(VCipher* t) {
    t->clock = 0;
    t->eval();
    t->clock = 1;
    t->eval();
}

// Timed-path output consumption, identical on all four AES simulators — see
// tb_cipher_t1.cpp for the rationale.
static inline void consume(uint64_t& acc, const VCipher& top) {
    for (int k = 0; k < 16; k++) acc ^= (uint64_t)(&top.io_state_out_0)[k];
    acc ^= (uint64_t)top.io_state_out_valid;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <cycles> <reps>\n", argv[0]);
        return 1;
    }
    int cycles = atoi(argv[1]);
    int reps = atoi(argv[2]);

    VerilatedContext ctx;
    ctx.commandArgs(argc, argv);
    ctx.threads(kVerilatorThreads);

    uint64_t acc = 0;
    std::vector<double> ns_per_cycle(reps);
    for (int r = 0; r < reps; r++) {
        VCipher top{&ctx};
        top.reset = 1;
        for (int i = 0; i < 5; i++) {
            dut_cycle(&top);
        }
        top.reset = 0;
        top.io_start = 1;
        for (int i = 0; i < 100; i++) {
            dut_cycle(&top);
        }

        auto t0 = std::chrono::steady_clock::now();
        for (int c = 0; c < cycles; c++) {
            dut_cycle(&top);
            consume(acc, top);
        }
        auto t1 = std::chrono::steady_clock::now();
        ns_per_cycle[r]
            = std::chrono::duration<double, std::nano>(t1 - t0).count() / (double)cycles;
    }

    double sum = 0, sum2 = 0;
    for (double x : ns_per_cycle) {
        sum += x;
        sum2 += x * x;
    }
    double mean = sum / reps;
    double sd = std::sqrt(std::max(0.0, sum2 / reps - mean * mean));
    printf("Benchmark: %.2f +/- %.2f ns/cycle (%d reps) OUT_ACC=0x%016llx\n",
           mean, sd, reps, (unsigned long long)acc);
    return 0;
}
