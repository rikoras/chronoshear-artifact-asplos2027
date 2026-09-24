// rocket_model core offline replay.
//
// Replays a core boundary trace recorded from the validated hybrid producer
// (scratch build of guiders/rocket-system/system_guider.cpp with the
// CoreTraceRecorder hook).  Per cycle the record holds: cycle number, the
// number of binding values, the converged module inputs, the module outputs
// the old core produced for those inputs, the 181 hot-core binding values at
// the start of the cycle, the integer register file, and two legacy PCs.
//
// The new core is stepped on the recorded inputs; its outputs are compared
// field by field with the recorded outputs, and after commit its register
// state is compared with the next record's binding values.
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <chrono>
#include <vector>

#include "core.h"

using namespace chisa::rocket_model;

namespace {

struct Record {
  uint64_t cycle;
  uint64_t count;
  RocketFullSystemInputs in;
  RocketFullSystemOutputs out;
  uint64_t vals[181];
  uint64_t rf[32];
  uint64_t frontend_pc;
  uint64_t ibuf_imem_pc;
};
static_assert(sizeof(RocketFullSystemInputs) == 336, "seam input layout drifted");
static_assert(sizeof(RocketFullSystemOutputs) == 736, "seam output layout drifted");

bool read_record(FILE* f, Record& r) {
  if (std::fread(&r.cycle, sizeof r.cycle, 1, f) != 1) return false;
  if (std::fread(&r.count, sizeof r.count, 1, f) != 1) return false;
  if (r.count != 181) { std::fprintf(stderr, "unexpected binding count %" PRIu64 "\n", r.count); std::exit(2); }
  if (std::fread(&r.in, sizeof r.in, 1, f) != 1) return false;
  if (std::fread(&r.out, sizeof r.out, 1, f) != 1) return false;
  if (std::fread(r.vals, sizeof(uint64_t), 181, f) != 181) return false;
  if (std::fread(r.rf, sizeof(uint64_t), 32, f) != 32) return false;
  if (std::fread(&r.frontend_pc, 8, 1, f) != 1) return false;
  if (std::fread(&r.ibuf_imem_pc, 8, 1, f) != 1) return false;
  return true;
}

uint64_t g_mismatches = 0;
uint64_t g_first_mismatch_cycle = 0;
uint64_t g_max_report = 20;
bool g_stop_at_first = true;

void report(uint64_t cycle, const char* what, const char* name, uint64_t expected, uint64_t actual) {
  if (g_mismatches == 0) g_first_mismatch_cycle = cycle;
  if (g_mismatches < g_max_report)
    std::fprintf(stderr, "CORE_REPLAY_MISMATCH cycle=%" PRIu64 " %s %s expected=0x%" PRIx64 " actual=0x%" PRIx64 "\n",
                 cycle, what, name, expected, actual);
  ++g_mismatches;
}

#define CMP(field) \
  do { \
    const uint64_t e_ = static_cast<uint64_t>(exp.field); \
    const uint64_t a_ = static_cast<uint64_t>(act.field); \
    if (e_ != a_) report(cycle, "output", #field, e_, a_); \
  } while (0)

void compare_outputs(uint64_t cycle, const RocketFullSystemOutputs& exp,
                     const RocketFullSystemOutputs& act) {
  CMP(imem.might_request); CMP(imem.resp_ready); CMP(imem.req_valid); CMP(imem.req_pc);
  CMP(imem.req_speculative); CMP(imem.sfence_valid); CMP(imem.sfence_rs1); CMP(imem.sfence_rs2);
  CMP(imem.sfence_addr); CMP(imem.sfence_asid); CMP(imem.btb_update_valid);
  CMP(imem.btb_prediction.cfi_type); CMP(imem.btb_prediction.taken); CMP(imem.btb_prediction.mask);
  CMP(imem.btb_prediction.bridx); CMP(imem.btb_prediction.target); CMP(imem.btb_prediction.entry);
  CMP(imem.btb_prediction.bht_history); CMP(imem.btb_prediction.bht_value);
  CMP(imem.btb_pc); CMP(imem.btb_target); CMP(imem.btb_taken); CMP(imem.btb_is_valid);
  CMP(imem.btb_branch_pc); CMP(imem.btb_cfi_type); CMP(imem.bht_update_valid);
  CMP(imem.bht_prediction_history); CMP(imem.bht_prediction_value); CMP(imem.bht_pc);
  CMP(imem.bht_branch); CMP(imem.bht_taken); CMP(imem.bht_mispredict); CMP(imem.ras_update_valid);
  CMP(imem.ras_cfi_type); CMP(imem.ras_return_addr); CMP(imem.flush_icache);
  CMP(dmem.req_valid); CMP(dmem.req_addr); CMP(dmem.req_tag); CMP(dmem.req_cmd); CMP(dmem.req_size);
  CMP(dmem.req_signed); CMP(dmem.req_dprv); CMP(dmem.req_phys); CMP(dmem.req_no_alloc);
  CMP(dmem.req_no_xcpt); CMP(dmem.req_data); CMP(dmem.req_mask); CMP(dmem.s1_kill); CMP(dmem.s1_data);
  CMP(dmem.s1_mask); CMP(dmem.s2_kill); CMP(dmem.keep_clock_enabled);
  CMP(ptbr_mode); CMP(ptbr_asid); CMP(ptbr_ppn);
  CMP(status.debug); CMP(status.cease); CMP(status.wfi); CMP(status.isa); CMP(status.dprv); CMP(status.prv);
  CMP(status.sd); CMP(status.zero2); CMP(status.sxl); CMP(status.uxl); CMP(status.sd_rv32); CMP(status.zero1);
  CMP(status.tsr); CMP(status.tw); CMP(status.tvm); CMP(status.mxr); CMP(status.sum); CMP(status.mprv);
  CMP(status.xs); CMP(status.fs); CMP(status.mpp); CMP(status.vs); CMP(status.spp); CMP(status.mpie);
  CMP(status.hpie); CMP(status.spie); CMP(status.upie); CMP(status.mie); CMP(status.hie); CMP(status.sie);
  CMP(status.uie);
  for (unsigned i = 0; i < 8; ++i) {
    CMP(pmp[i].cfg_l); CMP(pmp[i].cfg_res); CMP(pmp[i].cfg_a); CMP(pmp[i].cfg_x); CMP(pmp[i].cfg_w);
    CMP(pmp[i].cfg_r); CMP(pmp[i].addr); CMP(pmp[i].mask);
  }
  for (unsigned i = 0; i < 4; ++i) { CMP(custom_csr_wen[i]); CMP(custom_csr_wdata[i]); CMP(custom_csr_value[i]); }
  CMP(fpu.hartid); CMP(fpu.time); CMP(fpu.inst); CMP(fpu.fromint_data); CMP(fpu.fcsr_rm);
  CMP(fpu.dmem_resp_valid); CMP(fpu.dmem_resp_type); CMP(fpu.dmem_resp_tag); CMP(fpu.dmem_resp_data);
  CMP(fpu.valid); CMP(fpu.killx); CMP(fpu.killm); CMP(fpu.keep_clock_enabled);
  CMP(rocc.cmd_valid); CMP(rocc.cmd_inst.funct); CMP(rocc.cmd_inst.rs2); CMP(rocc.cmd_inst.rs1);
  CMP(rocc.cmd_inst.xd); CMP(rocc.cmd_inst.xs1); CMP(rocc.cmd_inst.xs2); CMP(rocc.cmd_inst.rd);
  CMP(rocc.cmd_inst.opcode); CMP(rocc.cmd_rs1); CMP(rocc.cmd_rs2); CMP(rocc.resp_ready); CMP(rocc.exception);
  CMP(rocc.cmd_status.prv); CMP(rocc.cmd_status.mpp);
  CMP(trace.valid); CMP(trace.iaddr); CMP(trace.insn); CMP(trace.priv); CMP(trace.exception);
  CMP(trace.interrupt); CMP(trace.cause); CMP(trace.tval);
  CMP(bpwatch_valid); CMP(bpwatch_rvalid); CMP(bpwatch_wvalid); CMP(bpwatch_ivalid); CMP(bpwatch_action);
  CMP(cease); CMP(wfi);
}
#undef CMP

void compare_state(uint64_t cycle, const Record& r, const Core& c, const Image& I) {
  unsigned n = 0;
#define X(i, path, width, expr) \
  do { \
    const uint64_t a_ = (expr) & ((width) >= 64 ? ~UINT64_C(0) : ((UINT64_C(1) << (width)) - 1)); \
    const uint64_t e_ = r.vals[i] & ((width) >= 64 ? ~UINT64_C(0) : ((UINT64_C(1) << (width)) - 1)); \
    if (a_ != e_) report(cycle, "state", path, e_, a_); \
    ++n; \
  } while (0);
#include "generated/core_bindings_check.inc"
#undef X
  (void)n;
  for (unsigned i = 1; i < 32; ++i)
    if (r.rf[i] != c.rf(i)) {
      char name[16]; std::snprintf(name, sizeof name, "x%u", i);
      report(cycle, "rf", name, r.rf[i], c.rf(i));
    }
}

}  // namespace

int main(int argc, char** argv) {
  if (argc < 2) {
    std::fprintf(stderr, "usage: %s TRACE [--max-cycles=N] [--continue] [--report=N] [--quiet]\n", argv[0]);
    return 2;
  }
  uint64_t max_cycles = ~UINT64_C(0);
  bool quiet = false;
  uint64_t perturb_cycle = ~UINT64_C(0);
  bool bench = false;
  for (int i = 2; i < argc; ++i) {
    const std::string a = argv[i];
    if (a.rfind("--max-cycles=", 0) == 0) max_cycles = std::strtoull(a.c_str() + 13, nullptr, 0);
    else if (a == "--continue") g_stop_at_first = false;
    else if (a.rfind("--report=", 0) == 0) g_max_report = std::strtoull(a.c_str() + 9, nullptr, 0);
    else if (a == "--quiet") quiet = true;
    else if (a.rfind("--perturb=", 0) == 0) perturb_cycle = std::strtoull(a.c_str() + 10, nullptr, 0);
    else if (a == "--bench") bench = true;
  }
  FILE* f = std::fopen(argv[1], "rb");
  if (!f) { std::perror(argv[1]); return 2; }

  static Image image;
  Core core;
  core.bind(image.core);
  Record r{};
  uint64_t cycles = 0;
  bool first = true;
  CoreWires wires;
  RocketFullSystemOutputs out;
  if (bench) {
    // Time evaluate+commit alone: load the whole trace first, then step.
    std::vector<Record> records;
    records.reserve(250000);
    while (cycles < max_cycles && read_record(f, r)) { records.push_back(r); ++cycles; }
    std::fclose(f);
    core.reset(static_cast<uint32_t>(records[0].in.reset_vector));
    const auto t0 = std::chrono::steady_clock::now();
    for (const Record& rec : records) {
      core.evaluate(rec.in, wires, out);
      core.commit(rec.in, wires);
    }
    const double ns = std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - t0).count();
    std::printf("CORE_REPLAY_BENCH cycles=%zu ns_per_cycle=%.1f\n", records.size(), ns / records.size());
    return 0;
  }
  while (cycles < max_cycles && read_record(f, r)) {
    if (first) {
      core.reset(static_cast<uint32_t>(r.in.reset_vector));
      first = false;
    }
    if (r.cycle == perturb_cycle) r.in.imem.resp_data ^= 0x10;  // negative test of the checker
    compare_state(r.cycle, r, core, image);
    if (g_mismatches && g_stop_at_first) break;
    core.evaluate(r.in, wires, out);
    compare_outputs(r.cycle, r.out, out);
    if (g_mismatches && g_stop_at_first) break;
    core.commit(r.in, wires);
    ++cycles;
  }
  std::fclose(f);
  if (!quiet)
    std::printf("CORE_REPLAY status=%s cycles=%" PRIu64 " mismatches=%" PRIu64 " first_mismatch_cycle=%" PRIu64 "\n",
                g_mismatches ? "mismatch" : "pass", cycles, g_mismatches, g_first_mismatch_cycle);
  return g_mismatches ? 1 : 0;
}
