// Online independent Cipher model + generated RTL. No oracle trace is opened.
#include "Cipher.h"
#include "aes_live_layout.h"
#include "cipher_model.h"
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <pthread.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>

namespace {
using chisa::aes_model::Bytes;
using chisa::aes_model::CipherModel;
constexpr unsigned W = std::extent<decltype(Cipher::io_start)>::value;
constexpr unsigned CPE = 2 * W;
constexpr unsigned slots = 32;
static_assert(W == aes_width && ORACLE_BLOCK_BYTES == aes_block_bytes);
static_assert(ORACLE_KERNEL_MIRRORED == aes_mirrored);
static_assert(ESSENT_ORACLE_VERIFY == 1, "Online measurements retain RTL oracle checks");
using Clock = std::chrono::steady_clock;

struct Inputs { Bytes plaintext{}, key{}; bool start = true; };
struct alignas(64) Packet {
  char oracle[aes_block_bytes]{};
  Inputs inputs[CPE];
  Bytes output[CPE];
  bool valid[CPE]{};
};
struct alignas(64) Cursor { std::atomic<std::uint64_t> value{0}; };
struct Ports { UInt<8>* pt[16]; UInt<8>* key[16]; UInt<8>* out[16]; };
Ports ports(Cipher& t) {
  Ports p;
#define P(i) p.pt[i]=t.io_plaintext_##i; p.key[i]=t.io_roundKey_##i; p.out[i]=t.io_state_out_##i;
  P(0) P(1) P(2) P(3) P(4) P(5) P(6) P(7)
  P(8) P(9) P(10) P(11) P(12) P(13) P(14) P(15)
#undef P
  return p;
}
void set_affinity(pthread_t thread, int cpu) {
  if (cpu < 0) return;
  if (cpu >= CPU_SETSIZE) throw std::runtime_error("CPU index out of range");
  cpu_set_t mask; CPU_ZERO(&mask); CPU_SET(cpu, &mask);
  if (pthread_setaffinity_np(thread, sizeof(mask), &mask))
    throw std::runtime_error("Cannot apply thread affinity");
  cpu_set_t actual; CPU_ZERO(&actual);
  if (pthread_getaffinity_np(thread, sizeof(actual), &actual) ||
      CPU_COUNT(&actual) != 1 || !CPU_ISSET(cpu, &actual))
    throw std::runtime_error("Applied thread affinity differs from request");
}
void pin(int cpu, bool report = false) {
  set_affinity(pthread_self(), cpu);
  if (report && cpu >= 0) std::printf("AES_LIVE_AFFINITY requested=%d actual=%d\n",cpu,sched_getcpu());
}
std::uint32_t random_word(std::uint32_t& s) {
  s ^= s << 13; s ^= s >> 17; s ^= s << 5; return s;
}
void supply(Packet& p, CipherModel& model, bool varied, bool check, std::uint32_t& random) {
  for (unsigned cycle = 0; cycle < CPE; ++cycle) {
    const unsigned index = aes_mirrored && cycle >= W ? 3 * W - 1 - cycle : cycle;
    for (unsigned b = 0; b < 16; ++b) p.oracle[aes_offsets[b]+index] = model.state[b];
    p.oracle[aes_offsets[16]+index] = model.rounds;
    p.oracle[aes_offsets[17]+index] = model.stm;
    auto& input = p.inputs[cycle];
    if (varied) {
      for (unsigned b = 0; b < 16; ++b) {
        input.plaintext[b] = random_word(random); input.key[b] = random_word(random);
      }
      input.start = (random_word(random) & 3) != 0;
    }
    if (check) { p.output[cycle] = model.output(); p.valid[cycle] = model.valid(); }
    if (varied) model.step(false, input.start, input.plaintext, input.key);
    else model.step(false, true, Bytes{}, Bytes{});
  }
#if defined(AES_LIVE_FAULT_INJECTION)
  // Qualification-only negative control. Never enabled by the build recipe.
  p.oracle[aes_offsets[17]] ^= 1;
#endif
}
void fold(std::uint64_t& hash, std::uint64_t value) {
  for (unsigned b = 0; b < 8; ++b) { hash ^= (value >> (8*b)) & 255; hash *= 1099511628211ULL; }
}
struct Result {
  std::uint64_t oracle_mismatches=0, output_mismatches=0, hash=14695981039346656037ULL;
  std::uint64_t accumulator=0, cycles=0;
  double wall_ns=0;
};
Result run(std::uint64_t logical_cycles, bool check, bool overlap, bool varied,
           int consumer_cpu, int producer_cpu) {
  auto packets = std::make_unique<Packet[]>(slots);
  Cursor ready, consumed;
  std::atomic<bool> failed{false};
  std::atomic<bool> start_producer{false};
  const std::uint64_t windows = (logical_cycles+CPE-1)/CPE;
  CipherModel model;
  std::uint32_t random = 0x1fc31ab7;
  Cipher t; auto p = ports(t);
  alignas(64) char reset_block[aes_block_bytes]{};
  t.oracle_cycle = 1; t.oracle_win_base = reset_block; t.reset = UInt<1>(1);
  for (unsigned lane=0; lane<W; ++lane) {
    t.io_start[lane] = UInt<1>(0);
    for (unsigned b=0; b<16; ++b) { p.pt[b][lane]=UInt<8>(0); p.key[b][lane]=UInt<8>(0); }
  }
  for (unsigned i=0; i<5; ++i) t.eval(true,false,false);
  t.reset = UInt<1>(0); t.verify_mismatches=0; t.assert_triggered=false;
  for (unsigned lane=0; lane<W; ++lane) t.io_start[lane]=UInt<1>(1);
  pin(consumer_cpu, check);
  Result result;
  std::uint8_t accum[W]{}, valid_accum[W]{};
  std::thread producer;
  const auto begin=Clock::now();
  if (overlap) producer=std::thread([&ready, &consumed, &failed, &start_producer,
                                    packets=packets.get(), windows, varied, check, producer_cpu] {
    try {
      while (!start_producer.load(std::memory_order_acquire)) _mm_pause();
      if (failed.load(std::memory_order_acquire)) return;
      pin(producer_cpu, check);
      CipherModel producer_model;
      std::uint32_t producer_random = 0x1fc31ab7;
      std::uint64_t available = slots;
      for (std::uint64_t w=0; w<windows; ++w) {
        while (w >= available) {
          available = consumed.value.load(std::memory_order_acquire)+slots;
          if (w >= available) _mm_pause();
        }
        supply(packets[w%slots], producer_model, varied, check, producer_random);
        if ((w+1)%8 == 0 || w+1 == windows) ready.value.store(w+1,std::memory_order_release);
      }
    } catch (...) { failed.store(true,std::memory_order_release); }
  });
  if (overlap) {
    try {
      // A new thread initially inherits the consumer's single-CPU affinity.
      // Place it before entering the consumer's busy wait; otherwise it can
      // wait a scheduler timeslice before it gets a chance to pin itself.
      set_affinity(producer.native_handle(), producer_cpu);
      start_producer.store(true,std::memory_order_release);
    } catch (...) {
      failed.store(true,std::memory_order_release);
      start_producer.store(true,std::memory_order_release);
      producer.join();
      throw;
    }
  }
  std::uint64_t available = 0;
  for (std::uint64_t w=0; w<windows; ++w) {
    if (overlap) {
      while (available<=w && !failed.load(std::memory_order_acquire)) {
        available = ready.value.load(std::memory_order_acquire);
        if (available<=w) _mm_pause();
      }
      if (failed.load(std::memory_order_acquire)) break;
    } else supply(packets[w%slots],model,varied,check,random);
    const auto& packet=packets[w%slots];
    t.oracle_win_base=packet.oracle;
    for (unsigned half=0; half<2; ++half) {
      if (varied) for (unsigned step=0; step<W; ++step) {
        const unsigned lane=half ? W-1-step : step;
        const auto& input=packet.inputs[half*W+step];
        t.io_start[lane]=UInt<1>(input.start);
        for (unsigned b=0; b<16; ++b) { p.pt[b][lane]=UInt<8>(input.plaintext[b]); p.key[b][lane]=UInt<8>(input.key[b]); }
      }
      if (half) t.eval_reverse(true,false,true); else t.eval_forward(true,false,true);
      if (check) {
        for (unsigned step=0; step<W; ++step) {
          const unsigned lane=half ? W-1-step : step, cycle=half*W+step;
          if (w*CPE+cycle >= logical_cycles) continue;
          const auto valid=t.io_state_out_valid[lane].as_single_word();
          result.output_mismatches += valid != packet.valid[cycle]; fold(result.hash,valid);
          for (unsigned b=0; b<16; ++b) {
            const auto value=p.out[b][lane].as_single_word();
            result.output_mismatches += value != packet.output[cycle][b]; fold(result.hash,value);
          }
        }
      } else {
        for (unsigned b=0; b<16; ++b)
          for (unsigned lane=0; lane<W; ++lane) accum[lane] ^= p.out[b][lane].val;
        for (unsigned lane=0; lane<W; ++lane) valid_accum[lane] ^= t.io_state_out_valid[lane].val;
      }
    }
    if ((w+1)%8 == 0 || w+1 == windows) consumed.value.store(w+1,std::memory_order_release);
  }
  if (producer.joinable()) producer.join();
  const auto end=Clock::now();
  if (failed.load()) throw std::runtime_error("Producer failed");
  result.wall_ns=std::chrono::duration<double,std::nano>(end-begin).count();
  result.oracle_mismatches=t.verify_mismatches;
  result.cycles=windows*CPE;
  for (unsigned lane=0; lane<W; ++lane)
    result.accumulator=(result.accumulator<<1)^(result.accumulator>>63)^accum[lane]^(std::uint64_t(valid_accum[lane])<<8);
  return result;
}
} // namespace

int main(int argc,char** argv) {
  try {
    std::uint64_t cycles=100000;
    bool overlap=false,varied=false;
    int consumer_cpu=-1,producer_cpu=-1;
    for(int i=1;i<argc;++i) {
      const std::string arg=argv[i];
      if(arg=="--overlap") overlap=true;
      else if(arg=="--varied") varied=true;
      else if(arg=="--cycles" && i+1<argc) cycles=std::stoull(argv[++i]);
      else if(arg=="--consumer-cpu" && i+1<argc) consumer_cpu=std::stoi(argv[++i]);
      else if(arg=="--producer-cpu" && i+1<argc) producer_cpu=std::stoi(argv[++i]);
      else throw std::runtime_error("Unknown or incomplete option: "+arg);
    }
    if(!cycles || cycles >= ORACLE_NUM_CYCLES) throw std::runtime_error("Cycle count exceeds verified compiled contract");
    if(overlap && ((consumer_cpu<0)!=(producer_cpu<0) ||
                   (consumer_cpu>=0 && consumer_cpu==producer_cpu)))
      throw std::runtime_error("Overlap requires two distinct CPUs or neither CPU specified");
    auto checked=run(cycles,true,overlap,varied,consumer_cpu,producer_cpu);
    std::printf("AES_LIVE_CHECK width=%u cycles=%llu oracle_mismatches=%llu output_mismatches=%llu OUT_HASH=0x%016llx\n",
      W,(unsigned long long)cycles,(unsigned long long)checked.oracle_mismatches,
      (unsigned long long)checked.output_mismatches,(unsigned long long)checked.hash);
    if(checked.oracle_mismatches || checked.output_mismatches) return 2;
    auto timed=run(cycles,false,overlap,varied,consumer_cpu,producer_cpu);
    std::printf("AES_LIVE_TIMING execution=%s width=%u logical_cycles=%llu evaluated_cycles=%llu wall_ns_per_cycle=%.6f oracle_mismatches=%llu OUT_ACC=0x%llx\n",
      overlap?"overlap":"serial",W,(unsigned long long)cycles,(unsigned long long)timed.cycles,
      timed.wall_ns/cycles,(unsigned long long)timed.oracle_mismatches,(unsigned long long)timed.accumulator);
    return timed.oracle_mismatches ? 2 : 0;
  } catch(const std::exception& e) { std::fprintf(stderr,"AES_LIVE_ERROR %s\n",e.what()); return 2; }
}
