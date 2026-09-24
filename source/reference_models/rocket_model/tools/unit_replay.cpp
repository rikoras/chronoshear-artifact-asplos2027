// Replays a unit input trace recorded by the co-simulation harness through
// the models without Verilator: exact per-unit timing, and (later) a
// differential check of a fast implementation against the reference one.
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "unit_trace.h"

using namespace chisa::rocket_model;

namespace {
struct Timer {
  double ns = 0;
  std::chrono::steady_clock::time_point t0;
  void start() { t0 = std::chrono::steady_clock::now(); }
  void stop() { ns += std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - t0).count(); }
};
}  // namespace

int main(int argc, char** argv) {
  if (argc < 2) { std::fprintf(stderr, "usage: %s TRACE [--max-cycles=N] [--units=...]\n", argv[0]); return 2; }
  uint64_t max_cycles = ~UINT64_C(0);
  std::string units = "core,itlb,dtlb,ptw,frontend,dcache,fpu";
  for (int i = 2; i < argc; ++i) {
    const std::string a = argv[i];
    if (a.rfind("--max-cycles=", 0) == 0) max_cycles = std::strtoull(a.c_str() + 13, nullptr, 0);
    else if (a.rfind("--units=", 0) == 0) units = a.substr(8);
  }
  const bool u_core = units.find("core") != std::string::npos, u_itlb = units.find("itlb") != std::string::npos;
  const bool u_dtlb = units.find("dtlb") != std::string::npos, u_ptw = units.find("ptw") != std::string::npos;
  const bool u_fe = units.find("frontend") != std::string::npos, u_dc = units.find("dcache") != std::string::npos;
  const bool u_fpu = units.find("fpu") != std::string::npos;

  FILE* f = std::fopen(argv[1], "rb");
  if (!f) { std::perror(argv[1]); return 2; }
  std::vector<UnitTraceRecord> recs;
  recs.reserve(300000);
  UnitTraceRecord r;
  while (recs.size() < max_cycles && std::fread(&r, sizeof r, 1, f) == 1) recs.push_back(r);
  std::fclose(f);
  for (UnitTraceRecord& x : recs) { x.fe.pmp = x.dc.pmp = x.itlb.pmp = x.dtlb.pmp = x.ptw.pmp = &x.pmp; }
  std::printf("loaded %zu cycles (%zu bytes/record)\n", recs.size(), sizeof(UnitTraceRecord));

  static Image image;
  Core core; core.bind(image.core);
  CoreWires cw; RocketFullSystemOutputs cout_;
  Tlb itlb{true, 2}, dtlb{false, 3}; TlbWires tw_i, tw_d;
  Ptw ptw; PtwWires pw;
  Frontend fe; FrontendWires fw;
  fe = Frontend{}; fe.icache.lfsr_ = 0; fe.s2_replay_reg_ = false;
  Dcache dc; DcacheWires dw;
  dc.lfsr_ = 0; dc.flushCounter_ = 0;
  Fpu fpu; FpuWires fpw;
  fpu.divS_.inReady = false; fpu.divD_.inReady = false; fpu.divSqrt_killed_ = false;
  bool core_reset_done = false;

  Timer t_core, t_itlb, t_dtlb, t_ptw, t_fe, t_dc, t_fpu;
  const auto wall0 = std::chrono::steady_clock::now();
  for (const UnitTraceRecord& x : recs) {
    if (u_core) {
      if (!core_reset_done) { core.reset(static_cast<uint32_t>(x.core_in.reset_vector)); core_reset_done = true; }
      t_core.start(); core.evaluate(x.core_in, cw, cout_); core.commit(x.core_in, cw); t_core.stop();
    }
    if (u_itlb) { t_itlb.start(); itlb.evaluate(x.itlb, tw_i); itlb.commit(x.itlb, tw_i); t_itlb.stop(); }
    if (u_dtlb) { t_dtlb.start(); dtlb.evaluate(x.dtlb, tw_d); dtlb.commit(x.dtlb, tw_d); t_dtlb.stop(); }
    if (u_ptw) { t_ptw.start(); ptw.evaluate(x.ptw, pw); ptw.commit(x.ptw, pw); t_ptw.stop(); }
    if (u_fe) { t_fe.start(); fe.evaluate(x.fe, fw); fe.commit(x.fe, fw); t_fe.stop(); }
    if (u_dc) { t_dc.start(); dc.evaluate(x.dc, dw); dc.commit(x.dc, dw); t_dc.stop(); }
    if (u_fpu) { t_fpu.start(); fpu.evaluate(x.fpu, fpw); fpu.commit(x.fpu, fpw); t_fpu.stop(); }
  }
  const double wall = std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - wall0).count();
  const double n = static_cast<double>(recs.size());
  std::printf("UNIT_REPLAY ns_per_cycle core=%.1f itlb=%.1f dtlb=%.1f ptw=%.1f frontend=%.1f dcache=%.1f fpu=%.1f wall=%.1f\n",
              t_core.ns / n, t_itlb.ns / n, t_dtlb.ns / n, t_ptw.ns / n, t_fe.ns / n, t_dc.ns / n, t_fpu.ns / n, wall / n);
  // Keep the models alive for the optimizer.
  volatile uint64_t sink = core.rf(1) ^ fe.s2_pc_ ^ dc.s2_data_ ^ static_cast<uint64_t>(fpu.regfile_[1]);
  (void)sink;
  return 0;
}
