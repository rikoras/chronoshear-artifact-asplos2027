// Identical changing matrices and output consumption for every simulator.
// MODE: 0 = CHISA SIMD, 1 = ESSENT scalar, 2 = Verilator.
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "reference_model.h"
#ifdef PAPER_EXPERIMENT
#include "paper_perf.h"
#else
static void paper_perf_control(bool) {}
static void paper_perf_finish(unsigned long long) {}
#endif
#if MODE == 2
#include "VFeedForwardMatMul.h"
using Dut = VFeedForwardMatMul;
using Input = uint8_t;
using Output = uint32_t;
#else
#include "FeedForwardMatMul.h"
using Dut = FeedForwardMatMul;
using Input = UInt<8>;
using Output = UInt<32>;
#endif
#if MODE != 0
#undef WIDTH
#define WIDTH 1
#endif

constexpr unsigned N = 16, Elements = N*N, Frames = 1024, Latency = 1;
alignas(64) static uint8_t inputs_a[Elements][Frames], inputs_b[Elements][Frames];
static uint32_t expected[Frames][Elements];
static Input* a[Elements];
static Input* b[Elements];
static Output* outputs[Elements];
static uint32_t accum[WIDTH];
alignas(64) static char empty_oracle[64];
static volatile uint64_t observed;

static void stimuli() {
  uint32_t seed = 0x83ca9017;
  auto next = [&]() { seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5; return seed; };
  for (unsigned f=0; f<Frames; ++f)
    for (unsigned i=0; i<Elements; ++i) {
      inputs_a[i][f] = f == 0 ? 0 : f == 1 ? 255 : uint8_t(next());
      inputs_b[i][f] = f == 0 ? 0 : f == 1 ? 255 : uint8_t(next());
    }
  chisa::matmul_model::fill_expected<N,Frames>(inputs_a,inputs_b,expected);
}

static void bind(Dut& d) {
#if MODE == 0
#define PORT(name) d.name
#else
#define PORT(name) (&d.name)
#endif
#define INPUT_A(i, name) a[i] = PORT(name);
#define INPUT_B(i, name) b[i] = PORT(name);
#define OUTPUT(i, name) outputs[i] = PORT(name);
#include "ports.inc"
#undef INPUT_A
#undef INPUT_B
#undef OUTPUT
#undef PORT
}

static uint32_t read(Output value) {
#if MODE == 2
  return value;
#else
  return uint32_t(value.as_single_word());
#endif
}

static void reset(Dut& d) {
  for (unsigned i=0;i<Elements;++i)
    for (unsigned l=0;l<WIDTH;++l) a[i][l]=Input(0), b[i][l]=Input(0);
#if MODE == 0
  d.oracle_win_base = empty_oracle;
  d.reset = UInt<1>(1);
  for (unsigned i=0;i<8;++i) d.eval(true,false,false);
  d.reset = UInt<1>(0);
  d.oracle_cycle = 0;
  d.verify_mismatches = 0;
#elif MODE == 1
  d.reset = UInt<1>(1);
  for (unsigned i=0;i<8;++i) d.eval(true,false,false);
  d.reset = UInt<1>(0);
#else
  d.reset = 1;
  for (unsigned i=0;i<8;++i) { d.clock=0; d.eval(); d.clock=1; d.eval(); }
  d.reset = 0;
#endif
}

template<bool Check> static uint64_t run(Dut& d, uint64_t cycles) {
  std::fill(std::begin(accum),std::end(accum),0);
  for (uint64_t base=0; base<cycles; base+=WIDTH) {
    const bool reverse = (base/WIDTH)&1;
    for (unsigned i=0;i<Elements;++i)
      for (unsigned l=0;l<WIDTH;++l) {
        const unsigned f = unsigned(base+(reverse ? WIDTH-1-l : l))&(Frames-1);
        a[i][l] = Input(inputs_a[i][f]); b[i][l] = Input(inputs_b[i][f]);
      }
#if MODE == 0
    if (reverse) d.eval_reverse(true,false,true); else d.eval_forward(true,false,true);
#elif MODE == 1
    d.eval(true,false,true);
#else
    d.clock=0; d.eval(); // Observe pre-edge state, as in the FIRRTL simulator.
#endif
    // Prevent dead-store elimination even when a whole stimulus period repeats.
    asm volatile("" ::: "memory");
    for (unsigned i=0;i<Elements;++i)
      for (unsigned l=0;l<WIDTH;++l) {
        const auto value = read(outputs[i][l]);
        accum[l] ^= value;
        if constexpr(Check) {
          const uint64_t cycle = base+(reverse ? WIDTH-1-l : l);
          const uint32_t want = cycle<Latency ? 0 : expected[(cycle-Latency)&(Frames-1)][i];
          if (value != want) {
            std::fprintf(stderr,"mismatch cycle=%llu output=%u got=%u expected=%u\n",
                         (unsigned long long)cycle,i,value,want);
            throw std::runtime_error("matrix output mismatch");
          }
        }
      }
#if MODE == 2
    d.clock=1; d.eval();
#endif
  }
  uint64_t hash=0;
  for (auto value:accum) hash ^= value;
  return hash;
}

int main(int argc,char** argv) {
  try {
    const bool bench = argc>1 && std::string(argv[1])=="bench";
    const uint64_t cycles = argc>2 ? std::stoull(argv[2]) : 65536;
    const unsigned reps = argc>3 ? unsigned(std::stoul(argv[3])) : 3;
    if (!cycles || cycles%(2*WIDTH) || !reps) throw std::runtime_error("cycles must be positive and divisible by 2W; reps > 0");
    stimuli();
#if MODE == 2
    Verilated::threadContextp()->threads(CHRONOSHEAR_BASELINE_THREADS);
#endif
    auto dut = std::make_unique<Dut>(); bind(*dut);
    // Independent mathematical reference; both directions, cold start and re-reset.
    for (unsigned pass=0;pass<2;++pass) { reset(*dut); observed=run<true>(*dut,4096); }
#if MODE == 0
    if (dut->verify_mismatches) throw std::runtime_error("unexpected oracle mismatch");
#endif
    std::printf("CHECK mode=%d width=%d cycles=8192 outputs=%u mismatches=0\n",MODE,WIDTH,8192*Elements);
    if (!bench) return 0;
    std::vector<double> times;
    for (unsigned rep=0;rep<=reps;++rep) {
      reset(*dut); observed=run<false>(*dut,4096);
      if (rep) paper_perf_control(true);
      const auto begin=std::chrono::steady_clock::now();
      observed=run<false>(*dut,cycles);
      const double ns=std::chrono::duration<double,std::nano>(std::chrono::steady_clock::now()-begin).count()/cycles;
      if (rep) paper_perf_finish(cycles);
      if (rep) { times.push_back(ns); std::printf("SAMPLE ns_per_cycle=%.3f\n",ns); }
    }
    std::sort(times.begin(),times.end());
    const double median=times[times.size()/2];
    std::printf("BENCH mode=%d width=%d cycles=%llu reps=%u ns_per_cycle=%.3f kcycles_per_second=%.3f checksum=%llu\n",
                MODE,WIDTH,(unsigned long long)cycles,reps,median,1e6/median,(unsigned long long)observed);
  } catch(const std::exception& e) { std::fprintf(stderr,"%s\n",e.what()); return 1; }
}
