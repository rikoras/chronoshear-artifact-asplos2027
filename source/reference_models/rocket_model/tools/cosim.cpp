// rocket_model co-simulation against the all-public Verilator model of the locked
// Rocket DefaultConfig TestHarness.
//
// The RTL runs the complete chip.  Each modelled unit is driven from the RTL
// wires at its own boundary, its combinational outputs are compared with the
// RTL wires of the same cycle, and after the clock edge its registers are
// compared with the RTL registers.  Units that are not modelled yet are simply
// the RTL.  The DMI host is the same explicit host the live runtime uses.
#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"

#include <chrono>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <x86intrin.h>

#include "core.h"
#include "dcache.h"
#include "dmi_host_api.h"
#include "fpu.h"
#include "frontend.h"
#include "unit_trace.h"
#include "isa.h"
#include "ptw.h"
#include "tlb.h"
#include "generated/seam_convert.h"

using namespace chisa::rocket_model;
using chisa::rocket_fullchip::DmiHostOutputs;

namespace {

constexpr uint64_t kMemoryBase = UINT64_C(0x80000000);
constexpr uint64_t kMemoryBytes = UINT64_C(0x10000000);

struct Options {
  std::string image;
  uint64_t max_cycles = 5000000;
  uint64_t reset_cycles = 64;
  uint64_t progress_cycles = 0;
  uint64_t report = 20;
  uint64_t dump_cycle = ~UINT64_C(0);
  bool poll_tohost = false;
  std::string record;
  bool stop_at_first = true;
  bool check_outputs = true;
  bool check_regs = true;
  bool unit_core = true, unit_itlb = true, unit_dtlb = true, unit_ptw = true, unit_frontend = true, unit_dcache = true, unit_fpu = true;
  uint64_t load_address = kMemoryBase;
  uint64_t tohost_address = UINT64_C(0x80001000);
  uint64_t fromhost_address = UINT64_C(0x80001040);
  uint64_t console_wait_pc[4] = {UINT64_C(0x80001634), UINT64_C(0x80001636),
                                 UINT64_C(0x80001716), UINT64_C(0x80001718)};
  uint64_t exit_park_pc = UINT64_C(0x800016ae);
  uint64_t trap_park_pc = UINT64_C(0x800016be);
};

uint64_t parse_u64(const char* v) { return std::strtoull(v, nullptr, 0); }

Options parse(int argc, char** argv) {
  Options o;
  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    auto value = [&](const char* name) -> const char* {
      if (a.rfind(name, 0) == 0 && a.size() > std::strlen(name) && a[std::strlen(name)] == '=')
        return a.c_str() + std::strlen(name) + 1;
      return nullptr;
    };
    if (const char* v = value("--image")) o.image = v;
    else if (const char* v = value("--max-cycles")) o.max_cycles = parse_u64(v);
    else if (const char* v = value("--reset-cycles")) o.reset_cycles = parse_u64(v);
    else if (const char* v = value("--progress-cycles")) o.progress_cycles = parse_u64(v);
    else if (const char* v = value("--report")) o.report = parse_u64(v);
    else if (const char* v = value("--dump-at")) o.dump_cycle = parse_u64(v);
    else if (a == "--poll-tohost") o.poll_tohost = true;
    else if (const char* v = value("--tohost")) o.tohost_address = parse_u64(v);
    else if (const char* v = value("--fromhost")) o.fromhost_address = parse_u64(v);
    else if (const char* v = value("--record")) o.record = v;
    else if (a == "--continue") o.stop_at_first = false;
    else if (a == "--no-outputs") o.check_outputs = false;
    else if (a == "--no-regs") o.check_regs = false;
    else if (const char* v = value("--units")) {
      o.unit_core = o.unit_itlb = o.unit_dtlb = o.unit_ptw = o.unit_frontend = o.unit_dcache = o.unit_fpu = false;
      const std::string u = v;
      o.unit_fpu = u.find("fpu") != std::string::npos;
      o.unit_dcache = u.find("dcache") != std::string::npos;
      o.unit_frontend = u.find("frontend") != std::string::npos;
      o.unit_core = u.find("core") != std::string::npos;
      o.unit_itlb = u.find("itlb") != std::string::npos;
      o.unit_dtlb = u.find("dtlb") != std::string::npos;
      o.unit_ptw = u.find("ptw") != std::string::npos;
    }
    else { std::fprintf(stderr, "unknown option %s\n", argv[i]); std::exit(2); }
  }
  if (o.image.empty()) { std::fprintf(stderr, "--image=PATH required\n"); std::exit(2); }
  return o;
}

std::vector<uint8_t> read_file(const std::string& path) {
  std::ifstream f(path, std::ios::binary | std::ios::ate);
  if (!f) throw std::runtime_error("cannot open " + path);
  const std::streamoff n = f.tellg();
  f.seekg(0);
  std::vector<uint8_t> bytes(static_cast<size_t>(n));
  if (n > 0) f.read(reinterpret_cast<char*>(bytes.data()), n);
  return bytes;
}

// SimAXIMem is eight byte banks: bank = address & 7, index = (address - base) >> 3.
template <class F>
void with_bank(VTestHarness___024root& root, unsigned b, F&& f) {
  switch (b) {
    case 0: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_0); break;
    case 1: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_1); break;
    case 2: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_2); break;
    case 3: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_3); break;
    case 4: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_4); break;
    case 5: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_5); break;
    case 6: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_6); break;
    default: f(root.TestHarness__DOT__mem__DOT__srams__DOT__mem_7); break;
  }
}

void write_byte(VTestHarness___024root& root, uint64_t address, uint8_t value) {
  const size_t index = static_cast<size_t>((address - kMemoryBase) >> 3);
  with_bank(root, static_cast<unsigned>(address & 7), [&](auto& bank) { bank[index] = value; });
}

uint64_t read_word(VTestHarness___024root& root, uint64_t address) {
  const size_t index = static_cast<size_t>((address - kMemoryBase) >> 3);
  uint64_t v = 0;
  for (unsigned b = 0; b < 8; ++b)
    with_bank(root, b, [&](auto& bank) { v |= static_cast<uint64_t>(bank[index]) << (8 * b); });
  return v;
}

// A Verilator register may be a plain integer, a one-element unpacked array
// (Verilog memories of depth one) or a wide word.
template <class T> uint64_t tap_value(const T& v) { return static_cast<uint64_t>(v); }
template <class T, std::size_t N> uint64_t tap_value(const VlUnpacked<T, N>& v) { return static_cast<uint64_t>(v[0]); }
template <std::size_t N> uint64_t tap_value(const VlWide<N>& v) {
  return (static_cast<uint64_t>(v[1]) << 32) | static_cast<uint64_t>(v[0]);
}

// Read a word the way the program sees it: from the RTL data cache if the
// line is present there, else from DRAM.
uint64_t read_word_coherent(VTestHarness___024root& root, uint64_t address) {
  const uint32_t set = static_cast<uint32_t>((address >> 6) & 63);
  const uint32_t tag = static_cast<uint32_t>(address >> 12) & 0xFFFFF;
  const uint32_t row = static_cast<uint32_t>((address >> 3) & 0x1ff);
  const VlUnpacked<IData, 64>* tags[4] = {
      &root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tag_array_0,
      &root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tag_array_1,
      &root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tag_array_2,
      &root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__tag_array_3};
  for (unsigned way = 0; way < 4; ++way) {
    const uint32_t m = (*tags[way])[set];
    if (((m >> 20) & 3) != 0 && (m & 0xFFFFF) == tag) {
      uint64_t v = 0;
#define COL(k) case k: v |= static_cast<uint64_t>(root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__dcache__DOT__data__DOT__data_arrays_0_##k[row]) << (8 * (k % 8)); break;
      for (unsigned b = 0; b < 8; ++b) {
        switch (way * 8 + b) {
          COL(0) COL(1) COL(2) COL(3) COL(4) COL(5) COL(6) COL(7) COL(8) COL(9) COL(10) COL(11) COL(12) COL(13) COL(14) COL(15)
          COL(16) COL(17) COL(18) COL(19) COL(20) COL(21) COL(22) COL(23) COL(24) COL(25) COL(26) COL(27) COL(28) COL(29) COL(30) COL(31)
          default: break;
        }
      }
#undef COL
      return v;
    }
  }
  return read_word(root, address);
}

struct DmiFeedback {
  bool request_ready, response_valid;
  uint32_t response_status, response_data;
};

void drive_dmi(VTestHarness___024root& root, const DmiHostOutputs& o) {
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg = o.request_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg = o.request_address;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg = o.request_operation;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg = o.request_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg = o.response_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = 0;
}

DmiFeedback dmi_feedback(const VTestHarness___024root& root) {
  return DmiFeedback{root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
                     root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
                     static_cast<uint32_t>(root.TestHarness__DOT__SimDTM_debug_resp_bits_resp),
                     static_cast<uint32_t>(root.TestHarness__DOT__SimDTM_debug_resp_bits_data)};
}

uint64_t observed_pc(const VTestHarness___024root& root) {
  return static_cast<uint64_t>(
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__core__DOT__coreMonitorBundle_pc);
}

inline uint64_t width_mask(unsigned width) {
  return width >= 64 ? ~UINT64_C(0) : ((UINT64_C(1) << width) - 1);
}

struct UnitTimer { uint64_t ticks = 0; uint64_t t0 = 0; void start() { t0 = __rdtsc(); } void stop() { ticks += __rdtsc() - t0; } };
UnitTimer g_t_core, g_t_itlb, g_t_dtlb, g_t_ptw, g_t_fe, g_t_dc, g_t_fpu;
double g_ghz = 0;

uint64_t g_mismatches = 0;
uint64_t g_first_mismatch = 0;

void report(const Options& o, uint64_t cycle, const char* what, const char* name,
            uint64_t expected, uint64_t actual) {
  if (g_mismatches == 0) g_first_mismatch = cycle;
  if (g_mismatches < o.report)
    std::fprintf(stderr, "COSIM_MISMATCH cycle=%" PRIu64 " %s %s model=0x%" PRIx64 " rtl=0x%" PRIx64 "\n",
                 cycle, what, name, expected, actual);
  ++g_mismatches;
}

// Read the model's value of manifest stream `index` from the image.
uint64_t image_value(const Image& image, unsigned index) {
  const StreamInfo& s = kStreams[index];
  const uint8_t* p = reinterpret_cast<const uint8_t*>(&image) + s.image_offset;
  uint64_t v = 0;
  std::memcpy(&v, p, s.elem_bytes);
  return v & width_mask(s.width);
}

bool modeled_oracle(const Options& o, unsigned index) {
  const uint32_t offset = kStreams[index].image_offset;
  return (o.unit_core && offset >= offsetof(Image, core) && offset < offsetof(Image, core) + sizeof(Image::Core)) ||
         (o.unit_frontend && offset >= offsetof(Image, frontend) && offset < offsetof(Image, frontend) + sizeof(Image::Frontend)) ||
         (o.unit_dcache && offset >= offsetof(Image, dcache) && offset < offsetof(Image, dcache) + sizeof(Image::Dcache)) ||
         (o.unit_fpu && offset >= offsetof(Image, fpu) && offset < offsetof(Image, fpu) + sizeof(Image::Fpu)) ||
         (o.unit_ptw && offset >= offsetof(Image, ptw) && offset < offsetof(Image, ptw) + sizeof(Image::Ptw));
}

// A selected unit must have exactly one correctly named and sized tap for
// every exported stream. A missing generated binding must not narrow the test.
void audit_oracles(const Options& o) {
  unsigned covered[kStreamCount] = {};
#define X(index, flat_name, rootm, bits) \
  if (modeled_oracle(o, index)) { \
    const StreamInfo& s = kStreams[index]; \
    if (std::strcmp(s.flat, flat_name) != 0 || s.width != bits || s.kind != StreamKind::kReg || ++covered[index] != 1) \
      throw std::runtime_error(std::string("invalid unit oracle binding: ") + flat_name); \
  }
  ROCKET_MODEL_TAPS(X)
#undef X
  unsigned count = 0;
  for (unsigned i = 0; i < kStreamCount; ++i) {
    if (!modeled_oracle(o, i)) continue;
    if (covered[i] != 1) throw std::runtime_error(std::string("missing unit oracle binding: ") + kStreams[i].flat);
    ++count;
  }
  std::printf("COSIM_ORACLES register_streams=%u boundary=rtl-unit-inputs\n", count);
}


#define TILE(n) root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain__DOT__tile__DOT__##n

inline void check(const Options& o, uint64_t cycle, const char* what, const char* name, uint64_t e, uint64_t a,
                  unsigned width, uint64_t& counter) {
  e &= width_mask(width);
  a &= width_mask(width);
  if (e != a) report(o, cycle, what, name, e, a);
  ++counter;
}

#define PMP_ENTRY(set, P, i) \
  set.e[i].addr = static_cast<uint32_t>(TILE(P##_##i##_addr)); \
  set.e[i].mask = static_cast<uint32_t>(TILE(P##_##i##_mask)); \
  set.e[i].l = TILE(P##_##i##_cfg_l); set.e[i].r = TILE(P##_##i##_cfg_r); \
  set.e[i].w = TILE(P##_##i##_cfg_w); set.e[i].x = TILE(P##_##i##_cfg_x); \
  set.e[i].a = static_cast<uint8_t>(TILE(P##_##i##_cfg_a));
#define PMP_READ(set, P) \
  PMP_ENTRY(set, P, 0) PMP_ENTRY(set, P, 1) PMP_ENTRY(set, P, 2) PMP_ENTRY(set, P, 3) \
  PMP_ENTRY(set, P, 4) PMP_ENTRY(set, P, 5) PMP_ENTRY(set, P, 6) PMP_ENTRY(set, P, 7) \
  set.any_enabled = false; for (int i_ = 0; i_ < 8; ++i_) set.any_enabled |= set.e[i_].a != 0;

#define PTW_RESP_READ(in, P) \
  in.ptw.req_ready = TILE(P##_req_ready); in.ptw.resp_valid = TILE(P##_resp_valid); \
  in.ptw.resp_ae = TILE(P##_resp_bits_ae); in.ptw.pte.ppn = tap_value(TILE(P##_resp_bits_pte_ppn)); \
  in.ptw.pte.d = TILE(P##_resp_bits_pte_d); in.ptw.pte.a = TILE(P##_resp_bits_pte_a); \
  in.ptw.pte.g = TILE(P##_resp_bits_pte_g); in.ptw.pte.u = TILE(P##_resp_bits_pte_u); \
  in.ptw.pte.x = TILE(P##_resp_bits_pte_x); in.ptw.pte.w = TILE(P##_resp_bits_pte_w); \
  in.ptw.pte.r = TILE(P##_resp_bits_pte_r); in.ptw.pte.v = TILE(P##_resp_bits_pte_v); \
  in.ptw.level = static_cast<uint8_t>(TILE(P##_resp_bits_level)); \
  in.ptw.homogeneous = TILE(P##_resp_bits_homogeneous); in.ptw.fragmented_superpage = false;

// TLB internal registers: P is the module prefix (e.g. frontend__DOT__tlb__DOT__).
#define TLB_REG_CHECKS(P, tlb, what) \
  check(o, cycles, what, "state", tlb.state_, TILE(P##state), 2, reg_checks); \
  check(o, cycles, what, "r_refill_tag", tlb.r_refill_tag_, TILE(P##r_refill_tag), 27, reg_checks); \
  check(o, cycles, what, "r_sectored_hit", tlb.r_sectored_hit_, TILE(P##r_sectored_hit), 1, reg_checks); \
  check(o, cycles, what, "r_sectored_hit_addr", tlb.r_sectored_hit_addr_, TILE(P##r_sectored_hit_addr), 3, reg_checks); \
  check(o, cycles, what, "r_sectored_repl_addr", tlb.r_sectored_repl_addr_, TILE(P##r_sectored_repl_addr), 3, reg_checks); \
  check(o, cycles, what, "r_superpage_repl_addr", tlb.r_superpage_repl_addr_, TILE(P##r_superpage_repl_addr), 2, reg_checks); \
  check(o, cycles, what, "sectored_plru", tlb.sectored_plru_, TILE(P##state_vec_0), 7, reg_checks); \
  check(o, cycles, what, "superpage_plru", tlb.superpage_plru_, TILE(P##state_reg_1), 3, reg_checks); \
  TLB_SECT(P, tlb, what, 0) TLB_SECT(P, tlb, what, 1) TLB_SECT(P, tlb, what, 2) TLB_SECT(P, tlb, what, 3) \
  TLB_SECT(P, tlb, what, 4) TLB_SECT(P, tlb, what, 5) TLB_SECT(P, tlb, what, 6) TLB_SECT(P, tlb, what, 7) \
  TLB_SUPER(P, tlb, what, 0) TLB_SUPER(P, tlb, what, 1) TLB_SUPER(P, tlb, what, 2) TLB_SUPER(P, tlb, what, 3) \
  check(o, cycles, what, "special_tag", tlb.special_.tag, TILE(P##special_entry_tag), 27, reg_checks); \
  check(o, cycles, what, "special_level", tlb.special_.level, TILE(P##special_entry_level), 2, reg_checks); \
  check(o, cycles, what, "special_valid", tlb.special_.valid, TILE(P##special_entry_valid_0), 1, reg_checks); \
  check(o, cycles, what, "special_data", tlb.special_.data[0], tap_value(TILE(P##special_entry_data_0)), 35, reg_checks);
#define TLB_SECT(P, tlb, what, i) \
  check(o, cycles, what, "sectored_" #i "_tag", tlb.sectored_[i].tag, TILE(P##sectored_entries_0_##i##_tag), 27, reg_checks); \
  check(o, cycles, what, "sectored_" #i "_valid", tlb.sectored_[i].valid, \
        (TILE(P##sectored_entries_0_##i##_valid_0) | (TILE(P##sectored_entries_0_##i##_valid_1) << 1) | \
         (TILE(P##sectored_entries_0_##i##_valid_2) << 2) | (TILE(P##sectored_entries_0_##i##_valid_3) << 3)), 4, reg_checks); \
  TLB_SECT_DATA(P, tlb, what, i, 0) TLB_SECT_DATA(P, tlb, what, i, 1) TLB_SECT_DATA(P, tlb, what, i, 2) TLB_SECT_DATA(P, tlb, what, i, 3)
#define TLB_SECT_DATA(P, tlb, what, i, j) \
  if (tlb.sectored_[i].valid & (1u << j)) \
    check(o, cycles, what, "sectored_" #i "_data_" #j, tlb.sectored_[i].data[j], tap_value(TILE(P##sectored_entries_0_##i##_data_##j)), 35, reg_checks);
#define TLB_SUPER(P, tlb, what, i) \
  check(o, cycles, what, "superpage_" #i "_tag", tlb.superpage_[i].tag, TILE(P##superpage_entries_##i##_tag), 27, reg_checks); \
  check(o, cycles, what, "superpage_" #i "_level", tlb.superpage_[i].level, TILE(P##superpage_entries_##i##_level), 1, reg_checks); \
  check(o, cycles, what, "superpage_" #i "_valid", tlb.superpage_[i].valid, TILE(P##superpage_entries_##i##_valid_0), 1, reg_checks); \
  if (tlb.superpage_[i].valid) \
    check(o, cycles, what, "superpage_" #i "_data", tlb.superpage_[i].data[0], tap_value(TILE(P##superpage_entries_##i##_data_0)), 35, reg_checks);

struct ItlbUnit {
  Tlb tlb{true, 2};
  TlbIn in{};
  TlbWires w{};
  PmpSet pmp{};
  void sample(VTestHarness___024root& root, bool reset) {
    in = TlbIn{};
    in.req_valid = TILE(frontend__DOT__tlb_io_req_valid);
    in.vaddr = tap_value(TILE(frontend__DOT__tlb_io_req_bits_vaddr)) & width_mask(40);
    in.passthrough = false;
    in.size = 2;
    in.cmd = M_XRD;
    in.sfence_valid = TILE(frontend__DOT__tlb_io_sfence_valid);
    in.sfence_rs1 = TILE(frontend__DOT__tlb_io_sfence_bits_rs1);
    in.sfence_rs2 = TILE(frontend__DOT__tlb_io_sfence_bits_rs2);
    in.sfence_addr = tap_value(TILE(frontend__DOT__tlb_io_sfence_bits_addr)) & width_mask(39);
    in.kill = TILE(frontend__DOT__tlb_io_kill);
    PTW_RESP_READ(in, frontend__DOT__tlb_io_ptw)
    in.prv = static_cast<uint8_t>(TILE(frontend__DOT__tlb_io_ptw_status_prv));
    in.dprv = in.prv;
    in.debug = TILE(frontend__DOT__tlb_io_ptw_status_debug);
    in.sum = TILE(ptw_io_dpath_status_sum);
    in.mxr = TILE(ptw_io_dpath_status_mxr);
    in.ptbr_mode = static_cast<uint8_t>(TILE(frontend__DOT__tlb_io_ptw_ptbr_mode));
    PMP_READ(pmp, frontend__DOT__tlb_io_ptw_pmp)
    in.pmp = &pmp;
    in.reset = reset;
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& output_checks) {
    check(o, cycles, "itlb", "req_ready", w.req_ready, TILE(frontend__DOT__tlb_io_req_ready), 1, output_checks);
    check(o, cycles, "itlb", "resp_miss", w.miss, TILE(frontend__DOT__tlb_io_resp_miss), 1, output_checks);
    check(o, cycles, "itlb", "resp_paddr", w.paddr, TILE(frontend__DOT__tlb_io_resp_paddr), 32, output_checks);
    check(o, cycles, "itlb", "resp_pf_inst", w.pf_inst, TILE(frontend__DOT__tlb_io_resp_pf_inst), 1, output_checks);
    check(o, cycles, "itlb", "resp_ae_inst", w.ae_inst, TILE(frontend__DOT__tlb_io_resp_ae_inst), 1, output_checks);
    check(o, cycles, "itlb", "resp_cacheable", w.cacheable, TILE(frontend__DOT__tlb_io_resp_cacheable), 1, output_checks);
    check(o, cycles, "itlb", "ptw_req_valid", w.ptw_req_valid, TILE(frontend__DOT__tlb_io_ptw_req_valid), 1, output_checks);
    check(o, cycles, "itlb", "ptw_req_bits_valid", w.ptw_req_bits_valid, TILE(frontend__DOT__tlb_io_ptw_req_bits_valid), 1, output_checks);
    check(o, cycles, "itlb", "ptw_req_addr", w.ptw_req_addr, TILE(frontend__DOT__tlb_io_ptw_req_bits_bits_addr), 27, output_checks);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    TLB_REG_CHECKS(frontend__DOT__tlb__DOT__, tlb, "itlb-reg")
  }
};

struct DtlbUnit {
  Tlb tlb{false, 3};
  TlbIn in{};
  TlbWires w{};
  PmpSet pmp{};
  void sample(VTestHarness___024root& root, bool reset) {
    in = TlbIn{};
    in.req_valid = TILE(dcache__DOT__tlb_io_req_valid);
    in.vaddr = tap_value(TILE(dcache__DOT__tlb_io_req_bits_vaddr)) & width_mask(40);
    in.passthrough = TILE(dcache__DOT__tlb_io_req_bits_passthrough);
    in.size = static_cast<uint8_t>(TILE(dcache__DOT__tlb_io_req_bits_size));
    in.cmd = static_cast<uint8_t>(TILE(dcache__DOT__tlb_io_req_bits_cmd));
    in.sfence_valid = TILE(dcache__DOT__tlb_io_sfence_valid);
    in.sfence_rs1 = TILE(dcache__DOT__tlb_io_sfence_bits_rs1);
    in.sfence_rs2 = TILE(dcache__DOT__tlb_io_sfence_bits_rs2);
    in.sfence_addr = tap_value(TILE(dcache__DOT__tlb_io_sfence_bits_addr)) & width_mask(39);
    in.kill = false;  // the core ties io.dmem.s2_kill low; Verilator folded the wire
    PTW_RESP_READ(in, dcache__DOT__tlb_io_ptw)
    in.dprv = static_cast<uint8_t>(TILE(dcache__DOT__tlb_io_ptw_status_dprv));
    in.prv = in.dprv;
    in.debug = TILE(dcache__DOT__tlb_io_ptw_status_debug);
    in.sum = TILE(dcache__DOT__tlb_io_ptw_status_sum);
    in.mxr = TILE(dcache__DOT__tlb_io_ptw_status_mxr);
    in.ptbr_mode = static_cast<uint8_t>(TILE(dcache__DOT__tlb_io_ptw_ptbr_mode));
    PMP_READ(pmp, dcache__DOT__tlb_io_ptw_pmp)
    in.pmp = &pmp;
    in.reset = reset;
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& output_checks) {
    check(o, cycles, "dtlb", "req_ready", w.req_ready, TILE(dcache__DOT__tlb_io_req_ready), 1, output_checks);
    check(o, cycles, "dtlb", "resp_miss", w.miss, TILE(dcache__DOT__tlb_io_resp_miss), 1, output_checks);
    check(o, cycles, "dtlb", "resp_paddr", w.paddr, TILE(dcache__DOT__tlb_io_resp_paddr), 32, output_checks);
    check(o, cycles, "dtlb", "resp_pf_ld", w.pf_ld, TILE(dcache__DOT__tlb_io_resp_pf_ld), 1, output_checks);
    check(o, cycles, "dtlb", "resp_pf_st", w.pf_st, TILE(dcache__DOT__tlb_io_resp_pf_st), 1, output_checks);
    check(o, cycles, "dtlb", "resp_ae_ld", w.ae_ld, TILE(dcache__DOT__tlb_io_resp_ae_ld), 1, output_checks);
    check(o, cycles, "dtlb", "resp_ae_st", w.ae_st, TILE(dcache__DOT__tlb_io_resp_ae_st), 1, output_checks);
    check(o, cycles, "dtlb", "resp_ma_ld", w.ma_ld, TILE(dcache__DOT__tlb_io_resp_ma_ld), 1, output_checks);
    check(o, cycles, "dtlb", "resp_ma_st", w.ma_st, TILE(dcache__DOT__tlb_io_resp_ma_st), 1, output_checks);
    check(o, cycles, "dtlb", "resp_cacheable", w.cacheable, TILE(dcache__DOT__tlb_io_resp_cacheable), 1, output_checks);
    check(o, cycles, "dtlb", "ptw_req_valid", w.ptw_req_valid, TILE(dcache__DOT__tlb_io_ptw_req_valid), 1, output_checks);
    check(o, cycles, "dtlb", "ptw_req_addr", w.ptw_req_addr, TILE(dcache__DOT__tlb_io_ptw_req_bits_bits_addr), 27, output_checks);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    TLB_REG_CHECKS(dcache__DOT__tlb__DOT__, tlb, "dtlb-reg")
  }
};

struct PtwUnit {
  Ptw ptw;
  PtwIn in{};
  PtwWires w{};
  PmpSet pmp{};
  void sample(VTestHarness___024root& root, bool reset) {
    in = PtwIn{};
    in.req_valid[0] = TILE(ptw_io_requestor_0_req_valid);
    in.req_bits_valid[0] = true;
    in.req_addr[0] = static_cast<uint32_t>(TILE(ptw_io_requestor_0_req_bits_bits_addr));
    in.req_valid[1] = TILE(ptw_io_requestor_1_req_valid);
    in.req_bits_valid[1] = TILE(ptw_io_requestor_1_req_bits_valid);
    in.req_addr[1] = static_cast<uint32_t>(TILE(ptw_io_requestor_1_req_bits_bits_addr));
    in.mem_req_ready = TILE(ptw_io_mem_req_ready);
    in.mem_resp_valid = TILE(ptw_io_mem_resp_valid);
    in.mem_resp_data = tap_value(TILE(ptw_io_mem_resp_bits_data));
    in.mem_s2_nack = TILE(ptw_io_mem_s2_nack);
    in.mem_s2_xcpt_ae_ld = TILE(ptw_io_mem_s2_xcpt_ae_ld);
    in.ptbr_ppn = tap_value(TILE(ptw_io_dpath_ptbr_ppn));
    in.ptbr_mode = static_cast<uint8_t>(TILE(ptw_io_dpath_ptbr_mode));
    in.sfence_valid = TILE(ptw_io_dpath_sfence_valid);
    in.sfence_rs1 = TILE(ptw_io_dpath_sfence_bits_rs1);
    PMP_READ(pmp, ptw_io_dpath_pmp)
    in.pmp = &pmp;
    in.reset = reset;
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& output_checks) {
    check(o, cycles, "ptw", "req_ready_0", w.req_ready[0], TILE(ptw_io_requestor_0_req_ready), 1, output_checks);
    check(o, cycles, "ptw", "req_ready_1", w.req_ready[1], TILE(ptw_io_requestor_1_req_ready), 1, output_checks);
    check(o, cycles, "ptw", "resp_valid_0", w.resp_valid[0], TILE(ptw_io_requestor_0_resp_valid), 1, output_checks);
    check(o, cycles, "ptw", "resp_valid_1", w.resp_valid[1], TILE(ptw_io_requestor_1_resp_valid), 1, output_checks);
    check(o, cycles, "ptw", "resp_ae", w.resp_ae, TILE(ptw_io_requestor_0_resp_bits_ae), 1, output_checks);
    check(o, cycles, "ptw", "resp_level", w.resp_level, TILE(ptw_io_requestor_0_resp_bits_level), 2, output_checks);
    check(o, cycles, "ptw", "resp_homogeneous", w.resp_homogeneous, TILE(ptw_io_requestor_0_resp_bits_homogeneous), 1, output_checks);
    check(o, cycles, "ptw", "resp_pte_ppn", w.resp_pte.ppn, tap_value(TILE(ptw_io_requestor_0_resp_bits_pte_ppn)), 54, output_checks);
    check(o, cycles, "ptw", "resp_pte_v", w.resp_pte.v, TILE(ptw_io_requestor_0_resp_bits_pte_v), 1, output_checks);
    check(o, cycles, "ptw", "resp_pte_flags",
          (w.resp_pte.d << 7) | (w.resp_pte.a << 6) | (w.resp_pte.g << 5) | (w.resp_pte.u << 4) |
          (w.resp_pte.x << 3) | (w.resp_pte.w << 2) | (w.resp_pte.r << 1),
          (TILE(ptw_io_requestor_0_resp_bits_pte_d) << 7) | (TILE(ptw_io_requestor_0_resp_bits_pte_a) << 6) |
          (TILE(ptw_io_requestor_0_resp_bits_pte_g) << 5) | (TILE(ptw_io_requestor_0_resp_bits_pte_u) << 4) |
          (TILE(ptw_io_requestor_0_resp_bits_pte_x) << 3) | (TILE(ptw_io_requestor_0_resp_bits_pte_w) << 2) |
          (TILE(ptw_io_requestor_0_resp_bits_pte_r) << 1), 8, output_checks);
    check(o, cycles, "ptw", "mem_req_valid", w.mem_req_valid, TILE(ptw_io_mem_req_valid), 1, output_checks);
    check(o, cycles, "ptw", "mem_req_addr", w.mem_req_addr, tap_value(TILE(ptw_io_mem_req_bits_addr)), 40, output_checks);
    check(o, cycles, "ptw", "mem_s1_kill", w.mem_s1_kill, TILE(ptw_io_mem_s1_kill), 1, output_checks);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    check(o, cycles, "ptw-reg", "state", ptw.state_, TILE(ptw__DOT__state), 3, reg_checks);
    check(o, cycles, "ptw-reg", "count", ptw.count_, TILE(ptw__DOT__count), 2, reg_checks);
    check(o, cycles, "ptw-reg", "resp_valid_0", ptw.resp_valid_[0], TILE(ptw__DOT__resp_valid_0), 1, reg_checks);
    check(o, cycles, "ptw-reg", "resp_valid_1", ptw.resp_valid_[1], TILE(ptw__DOT__resp_valid_1), 1, reg_checks);
    check(o, cycles, "ptw-reg", "resp_ae", ptw.resp_ae_, TILE(ptw__DOT__resp_ae), 1, reg_checks);
    check(o, cycles, "ptw-reg", "r_req_addr", ptw.r_req_addr_, TILE(ptw__DOT__r_req_addr), 27, reg_checks);
    check(o, cycles, "ptw-reg", "r_req_dest", ptw.r_req_dest_, TILE(ptw__DOT__r_req_dest), 1, reg_checks);
    check(o, cycles, "ptw-reg", "r_pte_ppn", ptw.r_pte_.ppn, tap_value(TILE(ptw__DOT__r_pte_ppn)), 54, reg_checks);
    check(o, cycles, "ptw-reg", "r_pte_flags",
          (ptw.r_pte_.d << 7) | (ptw.r_pte_.a << 6) | (ptw.r_pte_.g << 5) | (ptw.r_pte_.u << 4) |
          (ptw.r_pte_.x << 3) | (ptw.r_pte_.w << 2) | (ptw.r_pte_.r << 1) | ptw.r_pte_.v,
          (TILE(ptw__DOT__r_pte_d) << 7) | (TILE(ptw__DOT__r_pte_a) << 6) | (TILE(ptw__DOT__r_pte_g) << 5) |
          (TILE(ptw__DOT__r_pte_u) << 4) | (TILE(ptw__DOT__r_pte_x) << 3) | (TILE(ptw__DOT__r_pte_w) << 2) |
          (TILE(ptw__DOT__r_pte_r) << 1) | TILE(ptw__DOT__r_pte_v), 8, reg_checks);
    check(o, cycles, "ptw-reg", "mem_resp_valid", ptw.mem_resp_valid_, TILE(ptw__DOT__mem_resp_valid), 1, reg_checks);
    check(o, cycles, "ptw-reg", "mem_resp_data", ptw.mem_resp_data_, tap_value(TILE(ptw__DOT__mem_resp_data)), 64, reg_checks);
    check(o, cycles, "ptw-reg", "valid", ptw.pc_valid_, TILE(ptw__DOT__valid), 8, reg_checks);
    check(o, cycles, "ptw-reg", "plru", ptw.pc_plru_, TILE(ptw__DOT__state_reg), 7, reg_checks);
    check(o, cycles, "ptw-reg", "invalidated", ptw.invalidated_, TILE(ptw__DOT__invalidated), 1, reg_checks);
    check(o, cycles, "ptw-reg", "l2_refill", ptw.l2_refill_, TILE(ptw__DOT__l2_refill), 1, reg_checks);
#define PC(i) \
    if (ptw.pc_valid_ & (1u << i)) { \
      check(o, cycles, "ptw-reg", "tags_" #i, ptw.pc_tags_[i], TILE(ptw__DOT__tags_##i), 32, reg_checks); \
      check(o, cycles, "ptw-reg", "data_" #i, ptw.pc_data_[i], TILE(ptw__DOT__data_##i), 20, reg_checks); }
    PC(0) PC(1) PC(2) PC(3) PC(4) PC(5) PC(6) PC(7)
#undef PC
  }
};


struct FrontendUnit {
  Frontend fe;
  FrontendIn in{};
  FrontendWires w{};
  PmpSet pmp{};
  bool did_reset = false;
  void sample(VTestHarness___024root& root, bool reset) {
    in = FrontendIn{};
    in.req_valid = TILE(frontend_io_cpu_req_valid);
    in.req_pc = tap_value(TILE(frontend_io_cpu_req_bits_pc)) & width_mask(40);
    in.req_speculative = TILE(frontend_io_cpu_req_bits_speculative);
    in.sfence_valid = TILE(frontend_io_cpu_sfence_valid);
    in.sfence_rs1 = TILE(frontend_io_cpu_sfence_bits_rs1);
    in.sfence_rs2 = TILE(frontend_io_cpu_sfence_bits_rs2);
    in.sfence_addr = tap_value(TILE(frontend_io_cpu_sfence_bits_addr)) & width_mask(39);
    in.resp_ready = TILE(frontend_io_cpu_resp_ready);
    in.btb_update.valid = TILE(frontend_io_cpu_btb_update_valid);
    in.btb_update.entry = static_cast<uint8_t>(TILE(frontend_io_cpu_btb_update_bits_prediction_entry));
    in.btb_update.pc = tap_value(TILE(frontend_io_cpu_btb_update_bits_pc)) & width_mask(39);
    in.btb_update.br_pc = tap_value(TILE(frontend_io_cpu_btb_update_bits_br_pc)) & width_mask(39);
    in.btb_update.is_valid = TILE(frontend_io_cpu_btb_update_bits_isValid);
    in.btb_update.cfi_type = static_cast<uint8_t>(TILE(frontend_io_cpu_btb_update_bits_cfiType));
    in.bht_update.valid = TILE(frontend_io_cpu_bht_update_valid);
    in.bht_update.history = static_cast<uint8_t>(TILE(frontend_io_cpu_bht_update_bits_prediction_history));
    in.bht_update.pc = tap_value(TILE(frontend_io_cpu_bht_update_bits_pc)) & width_mask(39);
    in.bht_update.branch = TILE(frontend_io_cpu_bht_update_bits_branch);
    in.bht_update.taken = TILE(frontend_io_cpu_bht_update_bits_taken);
    in.bht_update.mispredict = TILE(frontend_io_cpu_bht_update_bits_mispredict);
    in.flush_icache = TILE(frontend_io_cpu_flush_icache);
    in.chicken = static_cast<uint32_t>(TILE(frontend_io_ptw_customCSRs_csrs_0_value));
    in.a_ready = TILE(frontend__DOT__auto_icache_master_out_a_ready);
    in.d_valid = TILE(frontend__DOT__auto_icache_master_out_d_valid);
    in.d_corrupt = TILE(frontend__DOT__auto_icache_master_out_d_bits_corrupt);
    in.d_opcode = static_cast<uint8_t>(TILE(frontend__DOT__auto_icache_master_out_d_bits_opcode));
    in.d_size = static_cast<uint8_t>(TILE(frontend__DOT__auto_icache_master_out_d_bits_size));
    in.d_data = tap_value(TILE(frontend__DOT__auto_icache_master_out_d_bits_data));
    PTW_RESP_READ(in, frontend_io_ptw)
    in.prv = static_cast<uint8_t>(TILE(frontend_io_ptw_status_prv));
    in.debug = TILE(frontend_io_ptw_status_debug);
    in.ptbr_mode = static_cast<uint8_t>(TILE(frontend_io_ptw_ptbr_mode));
    PMP_READ(pmp, frontend_io_ptw_pmp)
    in.pmp = &pmp;
    in.reset = reset;
    // Start from the all-zero state Verilator uses (--x-initial 0); the reset
    // cycles then set the registers with reset values exactly like the RTL.
    if (!did_reset) { fe = Frontend{}; fe.icache.lfsr_ = 0; fe.s2_replay_reg_ = false; did_reset = true; }
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& n) {
    check(o, cycles, "fe", "npc", w.npc, tap_value(TILE(frontend_io_cpu_npc)), 40, n);
    check(o, cycles, "fe", "resp_valid", w.resp_valid, TILE(frontend_io_cpu_resp_valid), 1, n);
    if (w.resp_valid) {
      check(o, cycles, "fe", "resp_pc", w.resp.pc, tap_value(TILE(frontend_io_cpu_resp_bits_pc)), 40, n);
      check(o, cycles, "fe", "resp_data", w.resp.data, TILE(frontend_io_cpu_resp_bits_data), 32, n);
      check(o, cycles, "fe", "resp_replay", w.resp.replay, TILE(frontend_io_cpu_resp_bits_replay), 1, n);
      check(o, cycles, "fe", "resp_btb_taken", w.resp.btb_taken, TILE(frontend_io_cpu_resp_bits_btb_taken), 1, n);
      check(o, cycles, "fe", "resp_btb_bridx", w.resp.btb_bridx, TILE(frontend_io_cpu_resp_bits_btb_bridx), 1, n);
      check(o, cycles, "fe", "resp_btb_entry", w.resp.btb_entry, TILE(frontend_io_cpu_resp_bits_btb_entry), 5, n);
      check(o, cycles, "fe", "resp_bht_history", w.resp.bht_history, TILE(frontend_io_cpu_resp_bits_btb_bht_history), 8, n);
      check(o, cycles, "fe", "resp_xcpt_pf", w.resp.pf_inst, TILE(frontend_io_cpu_resp_bits_xcpt_pf_inst), 1, n);
      check(o, cycles, "fe", "resp_xcpt_ae", w.resp.ae_inst, TILE(frontend_io_cpu_resp_bits_xcpt_ae_inst), 1, n);
    }
    check(o, cycles, "fe", "a_valid", w.a_valid, TILE(frontend__DOT__auto_icache_master_out_a_valid), 1, n);
    if (w.a_valid) check(o, cycles, "fe", "a_address", w.a_address, TILE(frontend__DOT__auto_icache_master_out_a_bits_address), 32, n);
    check(o, cycles, "fe", "ptw_req_valid", w.ptw_req_valid, TILE(frontend_io_ptw_req_valid), 1, n);
    check(o, cycles, "fe", "ptw_req_bits_valid", w.ptw_req_bits_valid, TILE(frontend_io_ptw_req_bits_valid), 1, n);
    check(o, cycles, "fe", "ptw_req_addr", w.ptw_req_addr, TILE(frontend_io_ptw_req_bits_bits_addr), 27, n);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    TLB_REG_CHECKS(frontend__DOT__tlb__DOT__, fe.tlb, "fe-tlb")
    // frontend pipeline
    check(o, cycles, "fe-reg", "s1_valid", fe.s1_valid_, TILE(frontend__DOT__s1_valid), 1, reg_checks);
    check(o, cycles, "fe-reg", "s1_pc", fe.s1_pc_, tap_value(TILE(frontend__DOT__s1_pc)), 40, reg_checks);
    check(o, cycles, "fe-reg", "s1_speculative", fe.s1_speculative_, TILE(frontend__DOT__s1_speculative), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_valid", fe.s2_valid_, TILE(frontend__DOT__s2_valid), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_pc", fe.s2_pc_, tap_value(TILE(frontend__DOT__s2_pc)), 40, reg_checks);
    check(o, cycles, "fe-reg", "s2_speculative", fe.s2_speculative_, TILE(frontend__DOT__s2_speculative), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_btb_resp_valid", fe.s2_btb_resp_valid_, TILE(frontend__DOT__s2_btb_resp_valid), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_btb_taken", fe.s2_btb_taken_bit_, TILE(frontend__DOT__s2_btb_resp_bits_taken), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_btb_bridx", fe.s2_btb_bridx_, TILE(frontend__DOT__s2_btb_resp_bits_bridx), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_btb_entry", fe.s2_btb_entry_, TILE(frontend__DOT__s2_btb_resp_bits_entry), 5, reg_checks);
    check(o, cycles, "fe-reg", "s2_bht_history", fe.s2_bht_history_, TILE(frontend__DOT__s2_btb_resp_bits_bht_history), 8, reg_checks);
    check(o, cycles, "fe-reg", "s2_bht_value", fe.s2_bht_value_, TILE(frontend__DOT__s2_btb_resp_bits_bht_value), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_tlb_miss", fe.s2_tlb_miss_, TILE(frontend__DOT__s2_tlb_resp_miss), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_tlb_pf", fe.s2_tlb_pf_inst_, TILE(frontend__DOT__s2_tlb_resp_pf_inst), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_tlb_ae", fe.s2_tlb_ae_inst_, TILE(frontend__DOT__s2_tlb_resp_ae_inst), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_tlb_cacheable", fe.s2_tlb_cacheable_, TILE(frontend__DOT__s2_tlb_resp_cacheable), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_partial_insn_valid", fe.s2_partial_insn_valid_, TILE(frontend__DOT__s2_partial_insn_valid), 1, reg_checks);
    if (fe.s2_partial_insn_valid_)
      check(o, cycles, "fe-reg", "s2_partial_insn", fe.s2_partial_insn_, TILE(frontend__DOT__s2_partial_insn), 16, reg_checks);
    check(o, cycles, "fe-reg", "wrong_path", fe.wrong_path_, TILE(frontend__DOT__wrong_path), 1, reg_checks);
    check(o, cycles, "fe-reg", "s2_replay_REG", fe.s2_replay_reg_, TILE(frontend__DOT__s2_replay_REG), 1, reg_checks);
    check(o, cycles, "fe-reg", "fq_io_enq_valid_REG", fe.fq_enq_valid_reg_, TILE(frontend__DOT__fq_io_enq_valid_REG), 1, reg_checks);
    // fetch queue
    check(o, cycles, "fe-fq", "valid", fe.fq_valid(),
          TILE(frontend__DOT__fq__DOT__valid_0) | (TILE(frontend__DOT__fq__DOT__valid_1) << 1) | (TILE(frontend__DOT__fq__DOT__valid_2) << 2) |
          (TILE(frontend__DOT__fq__DOT__valid_3) << 3) | (TILE(frontend__DOT__fq__DOT__valid_4) << 4), 5, reg_checks);
#define FQ(i) \
    { const FetchBundle& el = fe.fq_elt(i); \
      check(o, cycles, "fe-fq", "elts_" #i "_pc", el.pc, tap_value(TILE(frontend__DOT__fq__DOT__elts_##i##_pc)), 40, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_data", el.data, TILE(frontend__DOT__fq__DOT__elts_##i##_data), 32, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_replay", el.replay, TILE(frontend__DOT__fq__DOT__elts_##i##_replay), 1, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_btb_taken", el.btb_taken, TILE(frontend__DOT__fq__DOT__elts_##i##_btb_taken), 1, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_btb_bridx", el.btb_bridx, TILE(frontend__DOT__fq__DOT__elts_##i##_btb_bridx), 1, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_btb_entry", el.btb_entry, TILE(frontend__DOT__fq__DOT__elts_##i##_btb_entry), 5, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_bht_history", el.bht_history, TILE(frontend__DOT__fq__DOT__elts_##i##_btb_bht_history), 8, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_pf", el.pf_inst, TILE(frontend__DOT__fq__DOT__elts_##i##_xcpt_pf_inst), 1, reg_checks); \
      check(o, cycles, "fe-fq", "elts_" #i "_ae", el.ae_inst, TILE(frontend__DOT__fq__DOT__elts_##i##_xcpt_ae_inst), 1, reg_checks); }
    FQ(0) FQ(1) FQ(2) FQ(3) FQ(4)
#undef FQ
    // icache
    const ICache& ic = fe.icache;
    check(o, cycles, "fe-ic", "s1_valid", ic.s1_valid_, TILE(frontend__DOT__icache__DOT__s1_valid), 1, reg_checks);
    check(o, cycles, "fe-ic", "s2_valid", ic.s2_valid_, TILE(frontend__DOT__icache__DOT__s2_valid), 1, reg_checks);
    check(o, cycles, "fe-ic", "s2_hit", ic.s2_hit_, TILE(frontend__DOT__icache__DOT__s2_hit), 1, reg_checks);
    check(o, cycles, "fe-ic", "invalidated", ic.invalidated_, TILE(frontend__DOT__icache__DOT__invalidated), 1, reg_checks);
    check(o, cycles, "fe-ic", "refill_valid", ic.refill_valid_, TILE(frontend__DOT__icache__DOT__refill_valid), 1, reg_checks);
    check(o, cycles, "fe-ic", "s2_request_refill_REG", ic.s2_request_refill_reg_, TILE(frontend__DOT__icache__DOT__s2_request_refill_REG), 1, reg_checks);
    check(o, cycles, "fe-ic", "refill_paddr", ic.refill_paddr_, TILE(frontend__DOT__icache__DOT__refill_paddr), 32, reg_checks);
    check(o, cycles, "fe-ic", "counter", ic.counter_, TILE(frontend__DOT__icache__DOT__counter), 9, reg_checks);
    check(o, cycles, "fe-ic", "s2_tl_error", ic.s2_tl_error_, TILE(frontend__DOT__icache__DOT__s2_tl_error), 1, reg_checks);
    check(o, cycles, "fe-ic", "s2_tag_hit", ic.s2_tag_hit_,
          TILE(frontend__DOT__icache__DOT__s2_tag_hit_0) | (TILE(frontend__DOT__icache__DOT__s2_tag_hit_1) << 1) |
          (TILE(frontend__DOT__icache__DOT__s2_tag_hit_2) << 2) | (TILE(frontend__DOT__icache__DOT__s2_tag_hit_3) << 3), 4, reg_checks);
    check(o, cycles, "fe-ic", "s2_dout_0", ic.s2_dout_[0], TILE(frontend__DOT__icache__DOT__s2_dout_0), 32, reg_checks);
    check(o, cycles, "fe-ic", "s2_dout_1", ic.s2_dout_[1], TILE(frontend__DOT__icache__DOT__s2_dout_1), 32, reg_checks);
    check(o, cycles, "fe-ic", "s2_dout_2", ic.s2_dout_[2], TILE(frontend__DOT__icache__DOT__s2_dout_2), 32, reg_checks);
    check(o, cycles, "fe-ic", "s2_dout_3", ic.s2_dout_[3], TILE(frontend__DOT__icache__DOT__s2_dout_3), 32, reg_checks);
    {
      uint32_t lf = 0;
#define LF(i) lf |= static_cast<uint32_t>(TILE(frontend__DOT__icache__DOT__repl_way_v0_prng__DOT__state_##i)) << i;
      LF(0) LF(1) LF(2) LF(3) LF(4) LF(5) LF(6) LF(7) LF(8) LF(9) LF(10) LF(11) LF(12) LF(13) LF(14) LF(15)
#undef LF
      check(o, cycles, "fe-ic", "lfsr", ic.lfsr_, lf, 16, reg_checks);
      const auto& vb = TILE(frontend__DOT__icache__DOT__vb_array);
      for (unsigned way = 0; way < 4; ++way) {
        const uint64_t rtl = (static_cast<uint64_t>(vb[2 * way + 1]) << 32) | vb[2 * way];
        check(o, cycles, "fe-ic", "vb_array", ic.vb_[way], rtl, 64, reg_checks);
      }
      if ((cycles & 0xff) == 0) {  // arrays: full sweep every 256 cycles
        for (unsigned set = 0; set < 64; ++set) {
          check(o, cycles, "fe-ic", "tag_0", ic.tag_[set][0], TILE(frontend__DOT__icache__DOT__tag_array_0)[set], 21, reg_checks);
          check(o, cycles, "fe-ic", "tag_1", ic.tag_[set][1], TILE(frontend__DOT__icache__DOT__tag_array_1)[set], 21, reg_checks);
          check(o, cycles, "fe-ic", "tag_2", ic.tag_[set][2], TILE(frontend__DOT__icache__DOT__tag_array_2)[set], 21, reg_checks);
          check(o, cycles, "fe-ic", "tag_3", ic.tag_[set][3], TILE(frontend__DOT__icache__DOT__tag_array_3)[set], 21, reg_checks);
        }
        for (unsigned row = 0; row < 512; ++row) {
          check(o, cycles, "fe-ic", "data_0_0", ic.data_[row][0][0], TILE(frontend__DOT__icache__DOT__data_arrays_0_0)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_0_1", ic.data_[row][0][1], TILE(frontend__DOT__icache__DOT__data_arrays_0_1)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_0_2", ic.data_[row][0][2], TILE(frontend__DOT__icache__DOT__data_arrays_0_2)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_0_3", ic.data_[row][0][3], TILE(frontend__DOT__icache__DOT__data_arrays_0_3)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_1_0", ic.data_[row][1][0], TILE(frontend__DOT__icache__DOT__data_arrays_1_0)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_1_1", ic.data_[row][1][1], TILE(frontend__DOT__icache__DOT__data_arrays_1_1)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_1_2", ic.data_[row][1][2], TILE(frontend__DOT__icache__DOT__data_arrays_1_2)[row], 32, reg_checks);
          check(o, cycles, "fe-ic", "data_1_3", ic.data_[row][1][3], TILE(frontend__DOT__icache__DOT__data_arrays_1_3)[row], 32, reg_checks);
        }
      }
    }
    // btb
    const Btb& b = fe.btb;
    check(o, cycles, "fe-btb", "isValid", b.is_valid_, TILE(frontend__DOT__btb__DOT__isValid), 28, reg_checks);
    check(o, cycles, "fe-btb", "pageValid", b.page_valid_, TILE(frontend__DOT__btb__DOT__pageValid), 6, reg_checks);
    check(o, cycles, "fe-btb", "nextPageRepl", b.next_page_repl_, TILE(frontend__DOT__btb__DOT__nextPageRepl), 3, reg_checks);
    check(o, cycles, "fe-btb", "plru", b.plru_, TILE(frontend__DOT__btb__DOT__state_reg), 27, reg_checks);
    check(o, cycles, "fe-btb", "r_update_valid", b.r_update_valid_, TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_valid), 1, reg_checks);
    if (b.r_update_valid_) {
      check(o, cycles, "fe-btb", "r_update_pc", b.r_update_.pc, tap_value(TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_bits_pc)), 39, reg_checks);
      check(o, cycles, "fe-btb", "r_update_entry", b.r_update_.entry, TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_bits_prediction_entry), 5, reg_checks);
      check(o, cycles, "fe-btb", "r_update_cfi", b.r_update_.cfi_type, TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_bits_cfiType), 2, reg_checks);
      check(o, cycles, "fe-btb", "r_update_br_pc", b.r_update_.br_pc, tap_value(TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_bits_br_pc)), 39, reg_checks);
      check(o, cycles, "fe-btb", "r_update_isValid", b.r_update_.is_valid, TILE(frontend__DOT__btb__DOT__r_btb_updatePipe_bits_isValid), 1, reg_checks);
    }
    check(o, cycles, "fe-btb", "r_resp_valid", b.r_resp_valid_, TILE(frontend__DOT__btb__DOT__r_respPipe_valid), 1, reg_checks);
    if (b.r_resp_valid_) {
      check(o, cycles, "fe-btb", "r_resp_taken", b.r_resp_taken_, TILE(frontend__DOT__btb__DOT__r_respPipe_bits_taken), 1, reg_checks);
      check(o, cycles, "fe-btb", "r_resp_entry", b.r_resp_entry_, TILE(frontend__DOT__btb__DOT__r_respPipe_bits_entry), 5, reg_checks);
    }
    check(o, cycles, "fe-btb", "history", b.history_, TILE(frontend__DOT__btb__DOT__history), 8, reg_checks);
    check(o, cycles, "fe-btb", "reset_waddr", b.reset_waddr_, TILE(frontend__DOT__btb__DOT__reset_waddr), 10, reg_checks);
    check(o, cycles, "fe-btb", "ras_count", b.ras_count_, TILE(frontend__DOT__btb__DOT__count), 3, reg_checks);
    check(o, cycles, "fe-btb", "ras_pos", b.ras_pos_, TILE(frontend__DOT__btb__DOT__pos), 3, reg_checks);
#define PG(i) check(o, cycles, "fe-btb", "pages_" #i, b.pages_[i], TILE(frontend__DOT__btb__DOT__pages_##i), 25, reg_checks);
    PG(0) PG(1) PG(2) PG(3) PG(4) PG(5)
#undef PG
#define RS(i) if (b.ras_count_ > i) check(o, cycles, "fe-btb", "stack_" #i, b.ras_stack_[i], tap_value(TILE(frontend__DOT__btb__DOT__stack_##i)), 39, reg_checks);
    RS(0) RS(1) RS(2) RS(3) RS(4) RS(5)
#undef RS
#define BE(i) \
    if (b.is_valid_ & (1u << i)) { \
      check(o, cycles, "fe-btb", "idxs_" #i, b.idxs_[i], TILE(frontend__DOT__btb__DOT__idxs_##i), 13, reg_checks); \
      check(o, cycles, "fe-btb", "tgts_" #i, b.tgts_[i], TILE(frontend__DOT__btb__DOT__tgts_##i), 13, reg_checks); \
      check(o, cycles, "fe-btb", "idxPages_" #i, b.idx_pages_[i], TILE(frontend__DOT__btb__DOT__idxPages_##i), 3, reg_checks); \
      check(o, cycles, "fe-btb", "tgtPages_" #i, b.tgt_pages_[i], TILE(frontend__DOT__btb__DOT__tgtPages_##i), 3, reg_checks); \
      check(o, cycles, "fe-btb", "cfiType_" #i, b.cfi_type_[i], TILE(frontend__DOT__btb__DOT__cfiType_##i), 2, reg_checks); \
      check(o, cycles, "fe-btb", "brIdx_" #i, b.br_idx_[i], TILE(frontend__DOT__btb__DOT__brIdx_##i), 1, reg_checks); }
    BE(0) BE(1) BE(2) BE(3) BE(4) BE(5) BE(6) BE(7) BE(8) BE(9) BE(10) BE(11) BE(12) BE(13)
    BE(14) BE(15) BE(16) BE(17) BE(18) BE(19) BE(20) BE(21) BE(22) BE(23) BE(24) BE(25) BE(26) BE(27)
#undef BE
    if ((cycles & 0xff) == 0)
      for (unsigned i = 0; i < 512; ++i)
        check(o, cycles, "fe-btb", "table", b.table_[i], TILE(frontend__DOT__btb__DOT__table_)[i], 1, reg_checks);
  }
};


struct DcacheUnit {
  Dcache dc;
  DcacheIn in{};
  DcacheWires w{};
  PmpSet pmp{};
  bool did_init = false;
  void sample(VTestHarness___024root& root, bool reset) {
    in = DcacheIn{};
    in.req_valid = TILE(dcache_io_cpu_req_valid);
    in.req.addr = tap_value(TILE(dcache_io_cpu_req_bits_addr)) & width_mask(40);
    in.req.tag = static_cast<uint8_t>(TILE(dcache_io_cpu_req_bits_tag));
    in.req.cmd = static_cast<uint8_t>(TILE(dcache_io_cpu_req_bits_cmd));
    in.req.size = static_cast<uint8_t>(TILE(dcache_io_cpu_req_bits_size));
    in.req.signed_ = TILE(dcache_io_cpu_req_bits_signed);
    in.req.dprv = 0;
    in.req.phys = TILE(dcache_io_cpu_req_bits_phys);
    in.req.no_alloc = false;
    in.req.no_xcpt = false;
    in.s1_kill = TILE(dcache_io_cpu_s1_kill);
    in.s1_data = tap_value(TILE(dcache_io_cpu_s1_data_data));
    in.s1_mask = 0;
    in.s2_kill = false;
    in.a_ready = TILE(dcache_auto_out_a_ready);
    in.b_valid = TILE(dcache_auto_out_b_valid);
    in.b_address = static_cast<uint32_t>(TILE(dcache_auto_out_b_bits_address));
    in.b_param = static_cast<uint8_t>(TILE(dcache_auto_out_b_bits_param));
    in.b_size = static_cast<uint8_t>(TILE(dcache_auto_out_b_bits_size));
    in.b_source = static_cast<uint8_t>(TILE(dcache_auto_out_b_bits_source));
    in.c_ready = TILE(dcache_auto_out_c_ready);
    in.d_valid = TILE(dcache_auto_out_d_valid);
    in.d_opcode = static_cast<uint8_t>(TILE(dcache_auto_out_d_bits_opcode));
    in.d_param = static_cast<uint8_t>(TILE(dcache_auto_out_d_bits_param));
    in.d_size = static_cast<uint8_t>(TILE(dcache_auto_out_d_bits_size));
    in.d_source = static_cast<uint8_t>(TILE(dcache_auto_out_d_bits_source));
    in.d_sink = static_cast<uint8_t>(TILE(dcache_auto_out_d_bits_sink));
    in.d_denied = TILE(dcache_auto_out_d_bits_denied);
    in.d_corrupt = false;
    in.d_data = tap_value(TILE(dcache_auto_out_d_bits_data));
    in.e_ready = TILE(dcache_auto_out_e_ready);
    PTW_RESP_READ(in, dcache_io_ptw)
    in.dprv = static_cast<uint8_t>(TILE(dcache_io_ptw_status_dprv));
    in.debug = TILE(dcache_io_ptw_status_debug);
    in.sum = TILE(dcache_io_ptw_status_sum);
    in.mxr = TILE(dcache_io_ptw_status_mxr);
    in.ptbr_mode = static_cast<uint8_t>(TILE(dcache_io_ptw_ptbr_mode));
    PMP_READ(pmp, dcache_io_ptw_pmp)
    in.pmp = &pmp;
    in.reset = reset;
    if (!did_init) { dc = Dcache{}; dc.lfsr_ = 0; dc.flushCounter_ = 0; did_init = true; }
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& n) {
    if (cycles == o.dump_cycle) {
      std::fprintf(stderr, "DC_DUMP cycle=%" PRIu64 " d_valid=%d d_opcode=%d d_size=%d d_source=%d d_ready(model)=%d d_ready(rtl)=%d counter=%d d_last=%d "
                   "grantCached=%d a_valid=%d/%d s2_valid=%d s2_req_cmd=%d s2_req_addr=%llx cached_grant_wait=%d uncachedInFlight=%d release_state=%d "
                   "rtl_perf_grant=%d rtl_d_valid=%d\n",
                   cycles, in.d_valid, in.d_opcode, in.d_size, in.d_source, w.d_ready, (int)TILE(dcache_auto_out_d_ready), dc.d_counter_, w.d_last,
                   w.grantIsCached, w.a.valid, (int)TILE(dcache_auto_out_a_valid), dc.s2_valid_, dc.s2_req_.cmd, (unsigned long long)dc.s2_req_.addr,
                   dc.cached_grant_wait_, dc.uncachedInFlight_, dc.release_state_, (int)TILE(dcache_io_cpu_perf_grant), (int)TILE(dcache_auto_out_d_valid));
    }
    check(o, cycles, "dc", "req_ready", w.req_ready, TILE(dcache_io_cpu_req_ready), 1, n);
    check(o, cycles, "dc", "s2_nack", w.s2_nack, TILE(dcache_io_cpu_s2_nack), 1, n);
    check(o, cycles, "dc", "resp_valid", w.resp_valid, TILE(dcache_io_cpu_resp_valid), 1, n);
    if (w.resp_valid) {
      check(o, cycles, "dc", "resp_tag", w.resp_tag, TILE(dcache_io_cpu_resp_bits_tag), 7, n);
      check(o, cycles, "dc", "resp_size", w.resp_size, TILE(dcache_io_cpu_resp_bits_size), 2, n);
      check(o, cycles, "dc", "resp_data", w.resp_data, tap_value(TILE(dcache_io_cpu_resp_bits_data)), 64, n);
      check(o, cycles, "dc", "resp_replay", w.resp_replay, TILE(dcache_io_cpu_resp_bits_replay), 1, n);
      check(o, cycles, "dc", "resp_has_data", w.resp_has_data, TILE(dcache_io_cpu_resp_bits_has_data), 1, n);
      check(o, cycles, "dc", "resp_data_word_bypass", w.resp_data_word_bypass, tap_value(TILE(dcache_io_cpu_resp_bits_data_word_bypass)), 64, n);
    }
    check(o, cycles, "dc", "replay_next", w.replay_next, TILE(dcache_io_cpu_replay_next), 1, n);
    check(o, cycles, "dc", "s2_xcpt", (w.xcpt_ma_ld << 5) | (w.xcpt_ma_st << 4) | (w.xcpt_pf_ld << 3) | (w.xcpt_pf_st << 2) | (w.xcpt_ae_ld << 1) | w.xcpt_ae_st,
          (TILE(dcache_io_cpu_s2_xcpt_ma_ld) << 5) | (TILE(dcache_io_cpu_s2_xcpt_ma_st) << 4) | (TILE(dcache_io_cpu_s2_xcpt_pf_ld) << 3) |
          (TILE(dcache_io_cpu_s2_xcpt_pf_st) << 2) | (TILE(dcache_io_cpu_s2_xcpt_ae_ld) << 1) | TILE(dcache_io_cpu_s2_xcpt_ae_st), 6, n);
    check(o, cycles, "dc", "ordered", w.ordered, TILE(dcache_io_cpu_ordered), 1, n);
    check(o, cycles, "dc", "perf_grant", w.perf_grant, TILE(dcache_io_cpu_perf_grant), 1, n);
    check(o, cycles, "dc", "perf_release", w.perf_release, TILE(dcache_io_cpu_perf_release), 1, n);
    check(o, cycles, "dc", "a_valid", w.a.valid, TILE(dcache_auto_out_a_valid), 1, n);
    if (w.a.valid) {
      check(o, cycles, "dc", "a_opcode", w.a.opcode, TILE(dcache_auto_out_a_bits_opcode), 3, n);
      check(o, cycles, "dc", "a_param", w.a.param, TILE(dcache_auto_out_a_bits_param), 3, n);
      check(o, cycles, "dc", "a_size", w.a.size, TILE(dcache_auto_out_a_bits_size), 4, n);
      check(o, cycles, "dc", "a_source", w.a.source, TILE(dcache_auto_out_a_bits_source), 1, n);
      check(o, cycles, "dc", "a_address", w.a.address, TILE(dcache_auto_out_a_bits_address), 32, n);
      check(o, cycles, "dc", "a_mask", w.a.mask, TILE(dcache_auto_out_a_bits_mask), 8, n);
      check(o, cycles, "dc", "a_data", w.a.data, tap_value(TILE(dcache_auto_out_a_bits_data)), 64, n);
    }
    check(o, cycles, "dc", "b_ready", w.b_ready, TILE(dcache_auto_out_b_ready), 1, n);
    check(o, cycles, "dc", "c_valid", w.c.valid, TILE(dcache_auto_out_c_valid), 1, n);
    if (w.c.valid) {
      check(o, cycles, "dc", "c_opcode", w.c.opcode, TILE(dcache_auto_out_c_bits_opcode), 3, n);
      check(o, cycles, "dc", "c_param", w.c.param, TILE(dcache_auto_out_c_bits_param), 3, n);
      check(o, cycles, "dc", "c_size", w.c.size, TILE(dcache_auto_out_c_bits_size), 4, n);
      check(o, cycles, "dc", "c_source", w.c.source, TILE(dcache_auto_out_c_bits_source), 1, n);
      check(o, cycles, "dc", "c_address", w.c.address, TILE(dcache_auto_out_c_bits_address), 32, n);
      check(o, cycles, "dc", "c_data", w.c.data, tap_value(TILE(dcache_auto_out_c_bits_data)), 64, n);
    }
    check(o, cycles, "dc", "d_ready", w.d_ready, TILE(dcache_auto_out_d_ready), 1, n);
    check(o, cycles, "dc", "e_valid", w.e_valid, TILE(dcache_auto_out_e_valid), 1, n);
    if (w.e_valid) check(o, cycles, "dc", "e_sink", w.e_sink, TILE(dcache_auto_out_e_bits_sink), 2, n);
    check(o, cycles, "dc", "ptw_req_valid", w.ptw_req_valid, TILE(dcache_io_ptw_req_valid), 1, n);
    check(o, cycles, "dc", "ptw_req_addr", w.ptw_req_addr, TILE(dcache_io_ptw_req_bits_bits_addr), 27, n);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    TLB_REG_CHECKS(dcache__DOT__tlb__DOT__, dc.tlb, "dc-tlb")
    const Dcache& d = dc;
#define R(name, val, rtl, width) check(o, cycles, "dc-reg", name, val, rtl, width, reg_checks);
    R("s1_valid", d.s1_valid_, TILE(dcache__DOT__s1_valid), 1)
    R("s1_probe", d.s1_probe_, TILE(dcache__DOT__s1_probe), 1)
    R("probe_bits_address", d.probe_bits_address_, TILE(dcache__DOT__probe_bits_address), 32)
    R("probe_bits_param", d.probe_bits_param_, TILE(dcache__DOT__probe_bits_param), 2)
    R("probe_bits_size", d.probe_bits_size_, TILE(dcache__DOT__probe_bits_size), 4)
    R("probe_bits_source", d.probe_bits_source_, TILE(dcache__DOT__probe_bits_source), 1)
    R("s1_req_addr", d.s1_req_.addr, tap_value(TILE(dcache__DOT__s1_req_addr)), 40)
    R("s1_req_cmd", d.s1_req_.cmd, TILE(dcache__DOT__s1_req_cmd), 5)
    R("s1_req_size", d.s1_req_.size, TILE(dcache__DOT__s1_req_size), 2)
    R("s1_req_tag", d.s1_req_.tag, TILE(dcache__DOT__s1_req_tag), 7)
    R("s1_req_signed", d.s1_req_.signed_, TILE(dcache__DOT__s1_req_signed), 1)
    R("s1_tlb_req_vaddr", d.s1_tlb_req_vaddr_, tap_value(TILE(dcache__DOT__s1_tlb_req_vaddr)), 40)
    R("s1_tlb_req_passthrough", d.s1_tlb_req_passthrough_, TILE(dcache__DOT__s1_tlb_req_passthrough), 1)
    R("s1_tlb_req_size", d.s1_tlb_req_size_, TILE(dcache__DOT__s1_tlb_req_size), 2)
    R("s1_tlb_req_cmd", d.s1_tlb_req_cmd_, TILE(dcache__DOT__s1_tlb_req_cmd), 5)
    R("cached_grant_wait", d.cached_grant_wait_, TILE(dcache__DOT__cached_grant_wait), 1)
    R("resetting", d.resetting_, TILE(dcache__DOT__resetting), 1)
    R("flushCounter", d.flushCounter_, TILE(dcache__DOT__flushCounter), 8)
    R("release_ack_wait", d.release_ack_wait_, TILE(dcache__DOT__release_ack_wait), 1)
    R("release_ack_addr", d.release_ack_addr_, TILE(dcache__DOT__release_ack_addr), 32)
    R("release_state", d.release_state_, TILE(dcache__DOT__release_state), 4)
    R("refill_way", d.refill_way_, TILE(dcache__DOT__refill_way), 4)
    R("uncachedInFlight", d.uncachedInFlight_, TILE(dcache__DOT__uncachedInFlight_0), 1)
    if (d.uncachedInFlight_) {
      R("uncachedReq_addr", d.uncachedReq_.addr, tap_value(TILE(dcache__DOT__uncachedReqs_0_addr)), 40)
      R("uncachedReq_size", d.uncachedReq_.size, TILE(dcache__DOT__uncachedReqs_0_size), 2)
      R("uncachedReq_tag", d.uncachedReq_.tag, TILE(dcache__DOT__uncachedReqs_0_tag), 7)
      R("uncachedReq_signed", d.uncachedReq_.signed_, TILE(dcache__DOT__uncachedReqs_0_signed), 1)
    }
    R("s2_valid", d.s2_valid_, TILE(dcache__DOT__s2_valid), 1)
    R("s2_probe", d.s2_probe_, TILE(dcache__DOT__s2_probe), 1)
    R("s2_not_nacked_in_s1", d.s2_not_nacked_in_s1_, TILE(dcache__DOT__s2_not_nacked_in_s1), 1)
    R("s2_req_addr", d.s2_req_.addr, tap_value(TILE(dcache__DOT__s2_req_addr)), 40)
    R("s2_req_cmd", d.s2_req_.cmd, TILE(dcache__DOT__s2_req_cmd), 5)
    R("s2_req_size", d.s2_req_.size, TILE(dcache__DOT__s2_req_size), 2)
    R("s2_req_tag", d.s2_req_.tag, TILE(dcache__DOT__s2_req_tag), 7)
    R("s2_req_signed", d.s2_req_.signed_, TILE(dcache__DOT__s2_req_signed), 1)
    R("s2_tlb_xcpt", (d.s2_tlb_ma_ld_ << 5) | (d.s2_tlb_ma_st_ << 4) | (d.s2_tlb_pf_ld_ << 3) | (d.s2_tlb_pf_st_ << 2) | (d.s2_tlb_ae_ld_ << 1) | d.s2_tlb_ae_st_,
      (TILE(dcache__DOT__s2_tlb_xcpt_ma_ld) << 5) | (TILE(dcache__DOT__s2_tlb_xcpt_ma_st) << 4) | (TILE(dcache__DOT__s2_tlb_xcpt_pf_ld) << 3) |
      (TILE(dcache__DOT__s2_tlb_xcpt_pf_st) << 2) | (TILE(dcache__DOT__s2_tlb_xcpt_ae_ld) << 1) | TILE(dcache__DOT__s2_tlb_xcpt_ae_st), 6)
    R("s2_pma_cacheable", d.s2_pma_cacheable_, TILE(dcache__DOT__s2_pma_cacheable), 1)
    R("s2_vaddr_r", d.s2_vaddr_r_ >> 12, tap_value(TILE(dcache__DOT__s2_vaddr_r)) >> 12, 28)
    R("s2_meta_0", d.s2_meta_corrected_[0], TILE(dcache__DOT__s2_meta_corrected_r), 22)
    R("s2_meta_1", d.s2_meta_corrected_[1], TILE(dcache__DOT__s2_meta_corrected_r_1), 22)
    R("s2_meta_2", d.s2_meta_corrected_[2], TILE(dcache__DOT__s2_meta_corrected_r_2), 22)
    R("s2_meta_3", d.s2_meta_corrected_[3], TILE(dcache__DOT__s2_meta_corrected_r_3), 22)
    R("s2_data", d.s2_data_, tap_value(TILE(dcache__DOT__s2_data)), 64)
    R("s2_probe_way", d.s2_probe_way_, TILE(dcache__DOT__s2_probe_way), 4)
    R("s2_probe_state", d.s2_probe_state_, TILE(dcache__DOT__s2_probe_state_state), 2)
    R("s2_hit_way", d.s2_hit_way_, TILE(dcache__DOT__s2_hit_way), 4)
    R("s2_hit_state", d.s2_hit_state_, TILE(dcache__DOT__s2_hit_state_state), 2)
    R("s2_victim_way_r", d.s2_victim_way_r_, TILE(dcache__DOT__s2_victim_way_r), 2)
    R("lrscCount", d.lrscCount_, TILE(dcache__DOT__lrscCount), 7)
    R("pstore1_cmd", d.pstore1_cmd_, TILE(dcache__DOT__pstore1_cmd), 5)
    R("pstore1_addr", d.pstore1_addr_, tap_value(TILE(dcache__DOT__pstore1_addr)), 40)
    R("pstore1_data", d.pstore1_data_, tap_value(TILE(dcache__DOT__pstore1_data)), 64)
    R("pstore1_way", d.pstore1_way_, TILE(dcache__DOT__pstore1_way), 4)
    R("pstore1_mask", d.pstore1_mask_, TILE(dcache__DOT__pstore1_mask), 8)
    R("pstore1_rmw", d.pstore1_rmw_, TILE(dcache__DOT__pstore1_rmw_r), 1)
    R("pstore1_held", d.pstore1_held_, TILE(dcache__DOT__pstore1_held), 1)
    R("pstore2_valid", d.pstore2_valid_, TILE(dcache__DOT__pstore2_valid), 1)
    R("pstore2_addr", d.pstore2_addr_, tap_value(TILE(dcache__DOT__pstore2_addr)), 40)
    R("pstore2_way", d.pstore2_way_, TILE(dcache__DOT__pstore2_way), 4)
    R("pstore2_storegen_data", d.pstore2_storegen_data_, tap_value(TILE(dcache__DOT__pstore2_storegen_data)), 64)
    R("d_counter", d.d_counter_, TILE(dcache__DOT__counter), 9)
    R("c_counter", d.c_counter_, TILE(dcache__DOT__counter_1), 9)
    R("grantInProgress", d.grantInProgress_, TILE(dcache__DOT__grantInProgress), 1)
    R("blockProbeAfterGrantCount", d.blockProbeAfterGrantCount_, TILE(dcache__DOT__blockProbeAfterGrantCount), 3)
    R("blockUncachedGrant", d.blockUncachedGrant_, TILE(dcache__DOT__blockUncachedGrant), 1)
    R("s1_release_data_valid", d.s1_release_data_valid_, TILE(dcache__DOT__s1_release_data_valid), 1)
    R("s2_release_data_valid", d.s2_release_data_valid_, TILE(dcache__DOT__s2_release_data_valid), 1)
    R("doUncachedResp", d.doUncachedResp_, TILE(dcache__DOT__doUncachedResp), 1)
    R("s2_xcpt_REG", d.s2_xcpt_reg_, TILE(dcache__DOT__io_cpu_s2_xcpt_REG), 1)
    R("pstore_drain_on_miss_REG", d.pstore_drain_on_miss_reg_, TILE(dcache__DOT__pstore_drain_on_miss_REG), 1)
    R("s1_did_read", d.s1_did_read_, TILE(dcache__DOT__s1_did_read), 1)
    R("tag_rd_addr", d.tag_rd_addr_, TILE(dcache__DOT__tag_array_0_s1_meta_addr_pipe_0), 6)
    R("data_rd_addr", d.data_rd_addr_, TILE(dcache__DOT__data__DOT__data_arrays_0_0_rdata_data_addr_pipe_0), 9)
    {
      uint32_t lf = 0;
#define LF(i) lf |= static_cast<uint32_t>(TILE(dcache__DOT__lfsr_prng__DOT__state_##i)) << i;
      LF(0) LF(1) LF(2) LF(3) LF(4) LF(5) LF(6) LF(7) LF(8) LF(9) LF(10) LF(11) LF(12) LF(13) LF(14) LF(15)
#undef LF
      R("lfsr", d.lfsr_, lf, 16)
    }
    if ((cycles & 0xff) == 0) {
      for (unsigned set = 0; set < 64; ++set) {
        R("tag_0", d.tag_[set][0], TILE(dcache__DOT__tag_array_0)[set], 22)
        R("tag_1", d.tag_[set][1], TILE(dcache__DOT__tag_array_1)[set], 22)
        R("tag_2", d.tag_[set][2], TILE(dcache__DOT__tag_array_2)[set], 22)
        R("tag_3", d.tag_[set][3], TILE(dcache__DOT__tag_array_3)[set], 22)
      }
#define COL(k) for (unsigned row = 0; row < 512; ++row) R("data_col_" #k, d.data_[(k) / 8][row >> 3][(row & 7) * 8 + (k) % 8], TILE(dcache__DOT__data__DOT__data_arrays_0_##k)[row], 8)
      COL(0) COL(1) COL(2) COL(3) COL(4) COL(5) COL(6) COL(7) COL(8) COL(9) COL(10) COL(11) COL(12) COL(13) COL(14) COL(15)
      COL(16) COL(17) COL(18) COL(19) COL(20) COL(21) COL(22) COL(23) COL(24) COL(25) COL(26) COL(27) COL(28) COL(29) COL(30) COL(31)
#undef COL
    }
#undef R
  }
};


template <class T> chisa::rocket_model::hf::u128 wide_to_u128(const T& v) { return static_cast<chisa::rocket_model::hf::u128>(v); }
template <std::size_t N> chisa::rocket_model::hf::u128 wide_to_u128(const VlWide<N>& v) {
  chisa::rocket_model::hf::u128 r = 0;
  for (std::size_t i = 0; i < N && i < 4; ++i) r |= static_cast<chisa::rocket_model::hf::u128>(v[i]) << (32 * i);
  return r;
}
inline void check128(const Options& o, uint64_t cycle, const char* what, const char* name, chisa::rocket_model::hf::u128 e,
                     chisa::rocket_model::hf::u128 a, unsigned width, uint64_t& counter) {
  const chisa::rocket_model::hf::u128 m = chisa::rocket_model::hf::mask128(width);
  e &= m; a &= m;
  if (e != a) {
    report(o, cycle, what, name, static_cast<uint64_t>(e), static_cast<uint64_t>(a));
    if (g_mismatches <= o.report)
      std::fprintf(stderr, "   (high words) model=0x%" PRIx64 " rtl=0x%" PRIx64 "\n", static_cast<uint64_t>(e >> 64), static_cast<uint64_t>(a >> 64));
  }
  ++counter;
}

struct FpuUnit {
  Fpu fpu;
  FpuIn in{};
  FpuWires w{};
  bool did_init = false;
  void sample(VTestHarness___024root& root, bool reset) {
    in = FpuIn{};
    in.inst = static_cast<uint32_t>(TILE(fpuOpt_io_inst));
    in.fromint_data = tap_value(TILE(fpuOpt_io_fromint_data));
    in.fcsr_rm = static_cast<uint8_t>(TILE(fpuOpt_io_fcsr_rm));
    in.dmem_resp_val = TILE(fpuOpt_io_dmem_resp_val);
    in.dmem_resp_type = static_cast<uint8_t>(TILE(fpuOpt_io_dmem_resp_type));
    in.dmem_resp_tag = static_cast<uint8_t>(TILE(fpuOpt_io_dmem_resp_tag));
    in.dmem_resp_data = tap_value(TILE(fpuOpt_io_dmem_resp_data));
    in.valid = TILE(fpuOpt_io_valid);
    in.killx = TILE(fpuOpt_io_killx);
    in.killm = TILE(fpuOpt_io_killm);
    in.reset = reset;
    if (!did_init) { fpu = Fpu{}; fpu.divS_.inReady = false; fpu.divD_.inReady = false; fpu.divSqrt_killed_ = false; did_init = true; }
  }
  void compare_outputs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& n) {
    // Decode is observable by the core even on invalid/non-FP ID cycles.
    check(o, cycles, "fpu", "dec_ren1", w.dec.ren1, TILE(fpuOpt_io_dec_ren1), 1, n);
    check(o, cycles, "fpu", "dec_ren2", w.dec.ren2, TILE(fpuOpt_io_dec_ren2), 1, n);
    check(o, cycles, "fpu", "dec_ren3", w.dec.ren3, TILE(fpuOpt_io_dec_ren3), 1, n);
    check(o, cycles, "fpu", "dec_wen", w.dec.wen, TILE(fpuOpt_io_dec_wen), 1, n);
    check(o, cycles, "fpu", "fcsr_flags_valid", w.fcsr_flags_valid, TILE(fpuOpt_io_fcsr_flags_valid), 1, n);
    if (w.fcsr_flags_valid) check(o, cycles, "fpu", "fcsr_flags", w.fcsr_flags, TILE(fpuOpt_io_fcsr_flags_bits), 5, n);
    check(o, cycles, "fpu", "fcsr_rdy", w.fcsr_rdy, TILE(fpuOpt_io_fcsr_rdy), 1, n);
    check(o, cycles, "fpu", "illegal_rm", w.illegal_rm, TILE(fpuOpt_io_illegal_rm), 1, n);
    check(o, cycles, "fpu", "nack_mem", w.nack_mem, TILE(fpuOpt_io_nack_mem), 1, n);
    check(o, cycles, "fpu", "sboard_set", w.sboard_set, TILE(fpuOpt_io_sboard_set), 1, n);
    check(o, cycles, "fpu", "sboard_clr", w.sboard_clr, TILE(fpuOpt_io_sboard_clr), 1, n);
    check(o, cycles, "fpu", "sboard_clra", w.sboard_clra, TILE(fpuOpt_io_sboard_clra), 5, n);
    check(o, cycles, "fpu", "store_data", w.store_data, tap_value(TILE(fpuOpt_io_store_data)), 64, n);
    check(o, cycles, "fpu", "toint_data", w.toint_data, tap_value(TILE(fpuOpt_io_toint_data)), 64, n);
  }
  void compare_regs(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    const Fpu& f = fpu;
#define R(name, val, rtl, width) check(o, cycles, "fpu-reg", name, val, rtl, width, reg_checks);
#define R128(name, val, rtl, width) check128(o, cycles, "fpu-reg", name, val, wide_to_u128(rtl), width, reg_checks);
    R("ex_reg_valid", f.ex_reg_valid_, TILE(fpuOpt__DOT__ex_reg_valid), 1)
    R("ex_reg_inst", f.ex_reg_inst_, TILE(fpuOpt__DOT__ex_reg_inst), 32)
    R("ex_ra_0", f.ex_ra_[0], TILE(fpuOpt__DOT__ex_ra_0), 5)
    R("ex_ra_1", f.ex_ra_[1], TILE(fpuOpt__DOT__ex_ra_1), 5)
    R("ex_ra_2", f.ex_ra_[2], TILE(fpuOpt__DOT__ex_ra_2), 5)
    R("ex_ctrl", (f.ex_reg_ctrl_.div << 12) | (f.ex_reg_ctrl_.fastpipe << 11) | (f.ex_reg_ctrl_.fma << 10) | (f.ex_reg_ctrl_.fromint << 9) |
                 (f.ex_reg_ctrl_.ren2 << 8) | (f.ex_reg_ctrl_.ren3 << 7) | (f.ex_reg_ctrl_.sqrt << 6) | (f.ex_reg_ctrl_.swap23 << 5) |
                 (f.ex_reg_ctrl_.toint << 4) | (f.ex_reg_ctrl_.typeTagIn << 2) | (f.ex_reg_ctrl_.typeTagOut << 0),
      (TILE(fpuOpt__DOT__ex_reg_ctrl_div) << 12) | (TILE(fpuOpt__DOT__ex_reg_ctrl_fastpipe) << 11) | (TILE(fpuOpt__DOT__ex_reg_ctrl_fma) << 10) |
      (TILE(fpuOpt__DOT__ex_reg_ctrl_fromint) << 9) | (TILE(fpuOpt__DOT__ex_reg_ctrl_ren2) << 8) | (TILE(fpuOpt__DOT__ex_reg_ctrl_ren3) << 7) |
      (TILE(fpuOpt__DOT__ex_reg_ctrl_sqrt) << 6) | (TILE(fpuOpt__DOT__ex_reg_ctrl_swap23) << 5) | (TILE(fpuOpt__DOT__ex_reg_ctrl_toint) << 4) |
      (TILE(fpuOpt__DOT__ex_reg_ctrl_typeTagIn) << 2) | TILE(fpuOpt__DOT__ex_reg_ctrl_typeTagOut), 13)
    R("ex_ctrl_wflags", f.ex_reg_ctrl_.wflags, TILE(fpuOpt__DOT__ex_reg_ctrl_wflags), 1)
    R("load_wb", f.load_wb_, TILE(fpuOpt__DOT__load_wb), 1)
    if (f.load_wb_) {
      R("load_wb_data", f.load_wb_data_, tap_value(TILE(fpuOpt__DOT__load_wb_data)), 64)
      R("load_wb_tag", f.load_wb_tag_, TILE(fpuOpt__DOT__load_wb_tag), 5)
      R("load_wb_typeTag", f.load_wb_typeTag_, TILE(fpuOpt__DOT__load_wb_typeTag), 2)
    }
    R("mem_reg_valid", f.mem_reg_valid_, TILE(fpuOpt__DOT__mem_reg_valid), 1)
    R("mem_reg_inst", f.mem_reg_inst_, TILE(fpuOpt__DOT__mem_reg_inst), 32)
    R("wb_reg_valid", f.wb_reg_valid_, TILE(fpuOpt__DOT__wb_reg_valid), 1)
    R("mem_ctrl", (f.mem_ctrl_.div << 7) | (f.mem_ctrl_.fastpipe << 6) | (f.mem_ctrl_.fma << 5) | (f.mem_ctrl_.fromint << 4) |
                  (f.mem_ctrl_.sqrt << 3) | (f.mem_ctrl_.toint << 2) | (f.mem_ctrl_.typeTagOut << 1) | f.mem_ctrl_.wflags,
      (TILE(fpuOpt__DOT__mem_ctrl_div) << 7) | (TILE(fpuOpt__DOT__mem_ctrl_fastpipe) << 6) | (TILE(fpuOpt__DOT__mem_ctrl_fma) << 5) |
      (TILE(fpuOpt__DOT__mem_ctrl_fromint) << 4) | (TILE(fpuOpt__DOT__mem_ctrl_sqrt) << 3) | (TILE(fpuOpt__DOT__mem_ctrl_toint) << 2) |
      (TILE(fpuOpt__DOT__mem_ctrl_typeTagOut) << 1) | TILE(fpuOpt__DOT__mem_ctrl_wflags), 8)
    R("wb_ctrl_toint", f.wb_ctrl_.toint, TILE(fpuOpt__DOT__wb_ctrl_toint), 1)
    R("wen", f.wen_, TILE(fpuOpt__DOT__wen), 3)
#define WB(i) if ((f.wen_ >> i) & 1) { \
      R("wbInfo_" #i "_rd", f.wbInfo_[i].rd, TILE(fpuOpt__DOT__wbInfo_##i##_rd), 5) \
      R("wbInfo_" #i "_typeTag", f.wbInfo_[i].typeTag, TILE(fpuOpt__DOT__wbInfo_##i##_typeTag), 1) \
      R("wbInfo_" #i "_pipeid", f.wbInfo_[i].pipeid, TILE(fpuOpt__DOT__wbInfo_##i##_pipeid), 2) }
    WB(0) WB(1) WB(2)
#undef WB
    R("write_port_busy", f.write_port_busy_, TILE(fpuOpt__DOT__write_port_busy), 1)
    R("wb_toint_exc", f.wb_toint_exc_, TILE(fpuOpt__DOT__wb_toint_exc), 5)
    R("sboard_set_REG", f.sboard_set_reg_, TILE(fpuOpt__DOT__io_sboard_set_REG), 1)
    R("divSqrt_waddr", f.divSqrt_waddr_, TILE(fpuOpt__DOT__divSqrt_waddr), 5)
    R("divSqrt_killed", f.divSqrt_killed_, TILE(fpuOpt__DOT__divSqrt_killed), 1)
    // fpiu registers
    R128("fpiu_in1", f.fpiu_in_.in1, TILE(fpuOpt__DOT__fpiu__DOT__in_in1), 65)
    R128("fpiu_in2", f.fpiu_in_.in2, TILE(fpuOpt__DOT__fpiu__DOT__in_in2), 65)
    R("fpiu_rm", f.fpiu_in_.rm, TILE(fpuOpt__DOT__fpiu__DOT__in_rm), 3)
    R("fpiu_typ", f.fpiu_in_.typ, TILE(fpuOpt__DOT__fpiu__DOT__in_typ), 2)
    R("fpiu_fmt", f.fpiu_in_.fmt, TILE(fpuOpt__DOT__fpiu__DOT__in_fmt), 2)
    R("fpiu_ren2", f.fpiu_in_.c.ren2, TILE(fpuOpt__DOT__fpiu__DOT__in_ren2), 1)
    R("fpiu_wflags", f.fpiu_in_.c.wflags, TILE(fpuOpt__DOT__fpiu__DOT__in_wflags), 1)
    R("fpiu_typeTagOut", f.fpiu_in_.c.typeTagOut, TILE(fpuOpt__DOT__fpiu__DOT__in_typeTagOut), 2)
    // ifpu / fpmu second stages
    R128("ifpu_out_data", f.ifpu_data_, TILE(fpuOpt__DOT__ifpu__DOT__io_out_b_data), 65)
    R("ifpu_out_exc", f.ifpu_exc_, TILE(fpuOpt__DOT__ifpu__DOT__io_out_b_exc), 5)
    R128("fpmu_out_data", f.fpmu_data_, TILE(fpuOpt__DOT__fpmu__DOT__io_out_b_data), 65)
    R("fpmu_out_exc", f.fpmu_exc_, TILE(fpuOpt__DOT__fpmu__DOT__io_out_b_exc), 5)
    // FMA pipes
#define FMA(P, p, W, EW) \
    R(#P "_valid", f.p.valid, TILE(fpuOpt__DOT__##P##__DOT__valid), 1) \
    R128(#P "_in1", f.p.in.in1, TILE(fpuOpt__DOT__##P##__DOT__in_in1), W) \
    R128(#P "_in2", f.p.in.in2, TILE(fpuOpt__DOT__##P##__DOT__in_in2), W) \
    R128(#P "_in3", f.p.in.in3, TILE(fpuOpt__DOT__##P##__DOT__in_in3), W) \
    R(#P "_in_rm", f.p.in.rm, TILE(fpuOpt__DOT__##P##__DOT__in_rm), 3) \
    R(#P "_in_fmaCmd", f.p.in.fmaCmd, TILE(fpuOpt__DOT__##P##__DOT__in_fmaCmd), 2) \
    R(#P "_valid_stage0", f.p.valid_stage0, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__valid_stage0_v), 1) \
    R(#P "_pre_flags", (f.p.pre.isSigNaNAny << 9) | (f.p.pre.isNaNAOrB << 8) | (f.p.pre.isInfA << 7) | (f.p.pre.isZeroA << 6) | (f.p.pre.isInfB << 5) | \
                        (f.p.pre.isZeroB << 4) | (f.p.pre.signProd << 3) | (f.p.pre.isNaNC << 2) | (f.p.pre.isInfC << 1) | f.p.pre.isZeroC, \
      (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isSigNaNAny) << 9) | (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNAOrB) << 8) | \
      (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfA) << 7) | (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroA) << 6) | \
      (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfB) << 5) | (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroB) << 4) | \
      (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_signProd) << 3) | (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isNaNC) << 2) | \
      (TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isInfC) << 1) | TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_isZeroC), 10) \
    R(#P "_pre_sExpSum", static_cast<uint64_t>(f.p.pre.sExpSum), TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_sExpSum), EW + 2) \
    R(#P "_pre_doSubMags", f.p.pre.doSubMags, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_doSubMags), 1) \
    R(#P "_pre_CIsDominant", f.p.pre.CIsDominant, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CIsDominant), 1) \
    R(#P "_pre_CDom_CAlignDist", f.p.pre.CDom_CAlignDist, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_CDom_CAlignDist), 6) \
    R128(#P "_pre_highAlignedSigC", f.p.pre.highAlignedSigC, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_highAlignedSigC), (W - EW - 1) + 2) \
    R(#P "_pre_bit0AlignedSigC", f.p.pre.bit0AlignedSigC, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_fromPreMul_b_bit0AlignedSigC), 1) \
    R128(#P "_mulAddResult", f.p.pre.mulAddResult, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__mulAddRecFNToRaw_postMul_io_mulAddResult_b), 2 * (W - EW - 1) + 1) \
    R(#P "_rm0", f.p.rm0, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundingMode_stage0_b), 3) \
    R(#P "_raw_isNaN", f.p.raw.isNaN, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isNaN), 1) \
    R(#P "_raw_isInf", f.p.raw.isInf, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isInf), 1) \
    R(#P "_raw_isZero", f.p.raw.isZero, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_isZero), 1) \
    R(#P "_raw_sign", f.p.raw.sign, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sign), 1) \
    R(#P "_raw_sExp", static_cast<uint64_t>(f.p.raw.sExp), TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sExp), EW + 2) \
    R(#P "_raw_sig", static_cast<uint64_t>(f.p.raw.sig), tap_value(TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_in_b_sig)), (W - EW - 1) + 3) \
    R(#P "_invalidExc", f.p.invalidExc, TILE(fpuOpt__DOT__##P##__DOT__fma__DOT__roundRawFNToRecFN_io_invalidExc_b), 1)
    FMA(sfma, sfma_, 33, 8)
    FMA(dfma, dfma_, 65, 11)
#undef FMA
    R("dfma_validout", f.dfma_.validout, TILE(fpuOpt__DOT__dfma__DOT__fma__DOT__io_validout_v), 1)
    R128("dfma_out_data", f.dfma_.out_data, TILE(fpuOpt__DOT__dfma__DOT__io_out_b_data), 65)
    R("dfma_out_exc", f.dfma_.out_exc, TILE(fpuOpt__DOT__dfma__DOT__io_out_b_exc), 5)
    // div/sqrt state machines
#define DS(P, z, EW, SW) \
    R(#P "_cycleNum", f.z.cycleNum, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__cycleNum), 6) \
    R(#P "_inReady", f.z.inReady, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__inReady), 1) \
    R(#P "_rawOutValid", f.z.rawOutValid, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__rawOutValid), 1) \
    R(#P "_sqrtOp_Z", f.z.sqrtOp_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sqrtOp_Z), 1) \
    R(#P "_majorExc_Z", f.z.majorExc_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__majorExc_Z), 1) \
    R(#P "_isNaN_Z", f.z.isNaN_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__isNaN_Z), 1) \
    R(#P "_isInf_Z", f.z.isInf_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__isInf_Z), 1) \
    R(#P "_isZero_Z", f.z.isZero_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__isZero_Z), 1) \
    R(#P "_sign_Z", f.z.sign_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sign_Z), 1) \
    R(#P "_sExp_Z", static_cast<uint64_t>(f.z.sExp_Z), TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sExp_Z), EW + 2) \
    R(#P "_fractB_Z", f.z.fractB_Z, tap_value(TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__fractB_Z)), SW) \
    R(#P "_roundingMode_Z", f.z.roundingMode_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__roundingMode_Z), 3) \
    R(#P "_rem_Z", f.z.rem_Z, tap_value(TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__rem_Z)), SW + 2) \
    R(#P "_notZeroRem_Z", f.z.notZeroRem_Z, TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__notZeroRem_Z), 1) \
    R(#P "_sigX_Z", f.z.sigX_Z, tap_value(TILE(fpuOpt__DOT__##P##__DOT__divSqrtRecFNToRaw__DOT__divSqrtRawFN___DOT__sigX_Z)), SW + 2)
    DS(divSqrt, divS_, 8, 24)
    DS(divSqrt_1, divD_, 11, 53)
#undef DS
    if ((cycles & 63) == 0) compare_rf(root, o, cycles, reg_checks);
#undef R
#undef R128
  }
  void compare_rf(VTestHarness___024root& root, const Options& o, uint64_t cycles, uint64_t& reg_checks) {
    for (unsigned i = 0; i < 32; ++i) {
      char name[24];
      std::snprintf(name, sizeof name, "regfile[%u]", i);
      check128(o, cycles, "fpu-reg", name, fpu.regfile_[i], wide_to_u128(TILE(fpuOpt__DOT__regfile)[i]), 65, reg_checks);
    }
  }
};

}  // namespace

// The Verilated SimDTM DPI instance stays inert; the explicit DMI host drives
// its public registers directly.
extern "C" int debug_tick(svBit* debug_req_valid, svBit debug_req_ready,
                          int* debug_req_bits_addr, int* debug_req_bits_op,
                          int* debug_req_bits_data, svBit debug_resp_valid,
                          svBit* debug_resp_ready, int debug_resp_bits_resp,
                          int debug_resp_bits_data) {
  (void)debug_req_ready; (void)debug_req_bits_addr; (void)debug_req_bits_op;
  (void)debug_req_bits_data; (void)debug_resp_valid; (void)debug_resp_bits_resp;
  (void)debug_resp_bits_data;
  *debug_req_valid = 0;
  *debug_resp_ready = 0;
  return 0;
}

int main(int argc, char** argv) {
  const Options o = parse(argc, argv);
  if (o.check_regs) audit_oracles(o);
  const std::vector<uint8_t> image_bytes = read_file(o.image);

  auto context = std::make_unique<VerilatedContext>();
  context->randReset(0);
  context->commandArgs(argc, argv);
  auto dut = std::make_unique<VTestHarness>(context.get());
  VTestHarness___024root& root = *dut->rootp;
  dut->clock = 0;
  dut->reset = 1;
  dut->eval();
  for (size_t i = 0; i < image_bytes.size(); ++i) write_byte(root, o.load_address + i, image_bytes[i]);
  for (unsigned b = 0; b < 8; ++b) { write_byte(root, o.tohost_address + b, 0); write_byte(root, o.fromhost_address + b, 0); }
  chisa::rocket_fullchip::dmi_host_configure(o.load_address, o.tohost_address, o.fromhost_address);

  static Image image;
  Core core;
  core.bind(image.core);
  CoreWires wires;
  RocketFullSystemOutputs out;
  bool core_reset_done = false;
  ItlbUnit itlb;
  DtlbUnit dtlb;
  PtwUnit ptwu;
  FrontendUnit feu;
  DcacheUnit dcu;
  FpuUnit fpuu;

  bool simdtm_reset_delay = false;
  bool console_ack_armed = true;
  bool terminal_read_requested = false;
  uint64_t console_wait_streak = 0, terminal_streak = 0, terminal_pc = 0, final_tohost = 0;
  uint64_t cycles = 0;
  uint64_t output_checks = 0, reg_checks = 0;
  uint64_t poll_reads_seen = 0;
  FILE* rec = nullptr;
  if (!o.record.empty()) { rec = std::fopen(o.record.c_str(), "wb"); if (!rec) { std::perror(o.record.c_str()); return 2; } }

  for (; cycles < o.max_cycles; ++cycles) {
    const bool reset = cycles < o.reset_cycles;
    const bool simdtm_enabled = !reset && !simdtm_reset_delay;
    const DmiHostOutputs host = simdtm_enabled ? chisa::rocket_fullchip::dmi_host_outputs() : DmiHostOutputs{};
    dut->reset = reset;
    drive_dmi(root, host);
    dut->clock = 0;
    dut->eval();
    context->timeInc(1);

    // ---- modelled units: sample inputs, evaluate, compare combinational outputs ----
    SeamIn sin{};
    // Ports Verilator folded away are constants of this elaboration.
    sin.io_hartid = 0;
    sin.io_reset_vector = 0x10040;
    sin.io_imem_clock_enabled = 1;
    sin.io_dmem_clock_enabled = 1;
    sin.io_ptw_clock_enabled = 1;
#define X(member, rootm, width) sin.member = static_cast<uint64_t>(root.rootm) & width_mask(width);
    ROCKET_MODEL_SEAM_INS(X)
#undef X
    RocketFullSystemInputs in = seam_to_inputs(sin);
    in.reset = reset;
    if (!core_reset_done) {
      core.reset(static_cast<uint32_t>(in.reset_vector));
      core_reset_done = true;
    }
    if (o.unit_itlb) { itlb.sample(root, reset); g_t_itlb.start(); itlb.tlb.evaluate(itlb.in, itlb.w); g_t_itlb.stop(); }
    if (o.unit_dtlb) { dtlb.sample(root, reset); g_t_dtlb.start(); dtlb.tlb.evaluate(dtlb.in, dtlb.w); g_t_dtlb.stop(); }
    if (o.unit_ptw) { ptwu.sample(root, reset); g_t_ptw.start(); ptwu.ptw.evaluate(ptwu.in, ptwu.w); g_t_ptw.stop(); }
    if (o.unit_frontend) { feu.sample(root, reset); g_t_fe.start(); feu.fe.evaluate(feu.in, feu.w); g_t_fe.stop(); }
    if (o.unit_dcache) { dcu.sample(root, reset); g_t_dc.start(); dcu.dc.evaluate(dcu.in, dcu.w); g_t_dc.stop(); }
    if (o.unit_fpu) { fpuu.sample(root, reset); g_t_fpu.start(); fpuu.fpu.evaluate(fpuu.in, fpuu.w); g_t_fpu.stop(); }
    if (rec) {
      UnitTraceRecord r{};
      r.cycle = cycles; r.reset = reset;
      r.core_in = in; r.fe = feu.in; r.dc = dcu.in; r.fpu = fpuu.in; r.itlb = itlb.in; r.dtlb = dtlb.in; r.ptw = ptwu.in;
      r.pmp = dtlb.pmp;
      r.fe.pmp = r.dc.pmp = r.itlb.pmp = r.dtlb.pmp = r.ptw.pmp = nullptr;
      std::fwrite(&r, sizeof r, 1, rec);
    }
    if (o.check_outputs && !reset) {
      if (o.unit_fpu) fpuu.compare_outputs(root, o, cycles, output_checks);
      if (o.unit_frontend) feu.compare_outputs(root, o, cycles, output_checks);
      if (o.unit_dcache) dcu.compare_outputs(root, o, cycles, output_checks);
      if (o.unit_itlb) itlb.compare_outputs(root, o, cycles, output_checks);
      if (o.unit_dtlb) dtlb.compare_outputs(root, o, cycles, output_checks);
      if (o.unit_ptw) ptwu.compare_outputs(root, o, cycles, output_checks);
      if (g_mismatches && o.stop_at_first) break;
    }
    g_t_core.start(); core.evaluate(in, wires, out); g_t_core.stop();
    if (o.check_outputs && !reset && o.unit_core) {
      const SeamOut expected = outputs_to_seam(out);
#define X(member, rootm, width) \
      do { \
        const uint64_t e_ = expected.member & width_mask(width); \
        const uint64_t a_ = static_cast<uint64_t>(root.rootm) & width_mask(width); \
        if (e_ != a_) report(o, cycles, "output", #member, e_, a_); \
        ++output_checks; \
      } while (0);
      ROCKET_MODEL_SEAM_OUTS(X)
#undef X
      if (g_mismatches && o.stop_at_first) break;
    }

    const DmiFeedback fb = dmi_feedback(root);
    if (simdtm_enabled)
      chisa::rocket_fullchip::dmi_host_advance(fb.request_ready, fb.response_valid, fb.response_status, fb.response_data);
    simdtm_reset_delay = reset;

    dut->clock = 1;
    dut->eval();
    context->timeInc(1);

    // ---- commit and compare registers (post-edge) ----
    g_t_core.start(); core.commit(in, wires); g_t_core.stop();
    if (o.unit_itlb) { g_t_itlb.start(); itlb.tlb.commit(itlb.in, itlb.w); g_t_itlb.stop(); }
    if (o.unit_dtlb) { g_t_dtlb.start(); dtlb.tlb.commit(dtlb.in, dtlb.w); g_t_dtlb.stop(); }
    if (o.unit_ptw) { g_t_ptw.start(); ptwu.ptw.commit(ptwu.in, ptwu.w); g_t_ptw.stop(); }
    if (o.unit_frontend) { g_t_fe.start(); feu.fe.commit(feu.in, feu.w); g_t_fe.stop(); }
    if (o.unit_dcache) { g_t_dc.start(); dcu.dc.commit(dcu.in, dcu.w); g_t_dc.stop(); }
    if (o.unit_fpu) { g_t_fpu.start(); fpuu.fpu.commit(fpuu.in, fpuu.w); g_t_fpu.stop(); }
    if (o.check_regs) {
      if (o.unit_fpu) fpuu.compare_regs(root, o, cycles, reg_checks);
      if (o.unit_frontend) feu.compare_regs(root, o, cycles, reg_checks);
      if (o.unit_dcache) dcu.compare_regs(root, o, cycles, reg_checks);
      if (o.unit_itlb) itlb.compare_regs(root, o, cycles, reg_checks);
      if (o.unit_dtlb) dtlb.compare_regs(root, o, cycles, reg_checks);
      if (o.unit_ptw) ptwu.compare_regs(root, o, cycles, reg_checks);
      if (g_mismatches && o.stop_at_first) break;
    }
    if (o.check_regs) {
      // The live manifest compares registers unconditionally. Checking only
      // valid protocol payloads can miss a wrong invalid-cycle oracle (for
      // example ShiftQueue.elts_0 after a dequeue or redirect).
      if (o.unit_frontend) feu.fe.export_image(image.frontend);
      if (o.unit_dcache) dcu.dc.export_image(image.dcache);
      if (o.unit_fpu) fpuu.fpu.export_image(image.fpu);
      if (o.unit_ptw) ptwu.ptw.export_image(image.ptw);
#define X(index, flat, rootm, width) \
      if (modeled_oracle(o, index)) { \
        const uint64_t e_ = image_value(image, index); \
        const uint64_t a_ = tap_value(root.rootm) & width_mask(width); \
        if (e_ != a_) report(o, cycles, "reg", flat, e_, a_); \
        ++reg_checks; \
      }
      ROCKET_MODEL_TAPS(X)
#undef X
      if (g_mismatches && o.stop_at_first) break;
    }

    if (chisa::rocket_fullchip::dmi_host_failed())
      throw std::runtime_error(chisa::rocket_fullchip::dmi_host_error());
    if (!o.poll_tohost && chisa::rocket_fullchip::dmi_host_tohost_reads() != 0) {
      final_tohost = chisa::rocket_fullchip::dmi_host_last_tohost();
      ++cycles;
      break;
    }
    const uint64_t pc = observed_pc(root);
    if (o.poll_tohost) {
      // The program's tohost store may sit dirty in the L1: look there first.
      if ((cycles & 31) == 0) {
        const uint64_t th = read_word_coherent(root, o.tohost_address);
        if (th != 0) { final_tohost = th; terminal_pc = pc; ++cycles; break; }
      }
      if (o.progress_cycles && (cycles + 1) % o.progress_cycles == 0)
        std::fprintf(stderr, "COSIM_PROGRESS cycles=%" PRIu64 " pc=0x%" PRIx64 " mismatches=%" PRIu64 "\n", cycles + 1, pc, g_mismatches);
      continue;
    }
    const bool console_wait = pc == o.console_wait_pc[0] || pc == o.console_wait_pc[1] ||
                              pc == o.console_wait_pc[2] || pc == o.console_wait_pc[3];
    const bool terminal_wait = pc == o.exit_park_pc || pc == o.trap_park_pc;
    if (!console_wait) { console_wait_streak = 0; console_ack_armed = true; }
    else if (console_ack_armed) ++console_wait_streak;
    terminal_streak = terminal_wait ? terminal_streak + 1 : 0;
    if (chisa::rocket_fullchip::dmi_host_bootstrap_complete() && chisa::rocket_fullchip::dmi_host_idle()) {
      if (!terminal_read_requested && terminal_streak >= 8) {
        terminal_pc = pc;
        terminal_read_requested = true;
        chisa::rocket_fullchip::dmi_host_request_tohost_read();
      } else if (console_ack_armed && console_wait_streak >= 8) {
        console_ack_armed = false;
        console_wait_streak = 0;
        chisa::rocket_fullchip::dmi_host_request_console_ack();
      }
    }
    if (o.progress_cycles && (cycles + 1) % o.progress_cycles == 0)
      std::fprintf(stderr, "COSIM_PROGRESS cycles=%" PRIu64 " pc=0x%" PRIx64 " mismatches=%" PRIu64 "\n",
                   cycles + 1, pc, g_mismatches);
  }
  (void)read_word(root, o.tohost_address);
  // Completion need not land on the periodic RF sweep. Check all 65 recoded
  // bits at the final observed edge as well as the manifest pipeline state.
  if (o.check_regs && o.unit_fpu) fpuu.compare_rf(root, o, cycles, reg_checks);
  {
    // TSC calibration against the steady clock over a short spin.
    const auto c0 = std::chrono::steady_clock::now(); const uint64_t r0 = __rdtsc();
    while (std::chrono::duration<double>(std::chrono::steady_clock::now() - c0).count() < 0.05) {}
    const uint64_t r1 = __rdtsc();
    g_ghz = static_cast<double>(r1 - r0) / std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - c0).count();
    auto ns = [&](const UnitTimer& t) { return static_cast<double>(t.ticks) / g_ghz / (cycles ? cycles : 1); };
    std::fprintf(stderr, "MODEL_COST ns_per_cycle core=%.1f itlb=%.1f dtlb=%.1f ptw=%.1f frontend=%.1f dcache=%.1f fpu=%.1f total=%.1f\n",
                 ns(g_t_core), ns(g_t_itlb), ns(g_t_dtlb), ns(g_t_ptw), ns(g_t_fe), ns(g_t_dc), ns(g_t_fpu),
                 ns(g_t_core) + ns(g_t_itlb) + ns(g_t_dtlb) + ns(g_t_ptw) + ns(g_t_fe) + ns(g_t_dc) + ns(g_t_fpu));
  }
  const bool pass = final_tohost == 1 && g_mismatches == 0;
  std::printf("ROCKET_MODEL_COSIM status=%s cycles=%" PRIu64 " tohost=0x%" PRIx64 " pc=0x%" PRIx64
              " output_checks=%" PRIu64 " reg_checks=%" PRIu64 " mismatches=%" PRIu64
              " first_mismatch_cycle=%" PRIu64 " dmi_transactions=%" PRIu64 "\n",
              pass ? "pass" : (g_mismatches ? "mismatch" : "fail"), cycles, final_tohost,
              terminal_pc ? terminal_pc : observed_pc(root), output_checks, reg_checks, g_mismatches,
              g_first_mismatch, chisa::rocket_fullchip::dmi_host_transactions());
  if (rec) std::fclose(rec);
  dut->final();
  return pass ? 0 : (g_mismatches ? 1 : 4);
}
