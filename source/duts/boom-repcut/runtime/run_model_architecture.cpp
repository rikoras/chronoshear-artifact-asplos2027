#include <fesvr/dtm.h>
#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"
#include "verilated.h"
#include "architecture_compare.h"
#include "fesvr_debug_bootstrap.h"

#include <elf.h>
#include <array>
#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace {
using chisa::boom_repcut::ArchitectureComparison;
using chisa::boom_repcut::DmiFeedback;
using chisa::boom_repcut::DtmOutputs;
using chisa::boom_repcut::FesvrDtmAdapter;
using chisa::boom_model::RetirementEvent;
static_assert(chisa::boom_model::kArchitecturalModel,
              "architecture runner requires CHISA_MODEL_ARCHITECTURAL=1");

struct Options {
  std::uint64_t max_cycles = 4000000, reset_cycles = 12;
  int htif_start = -1;
};
Options options(int argc, char** argv) {
  Options result;
  for (int i = 1; i < argc; ++i) {
    const std::string arg(argv[i]);
    if (arg == "--") { result.htif_start = i + 1; break; }
    auto number = [&](const char* prefix, std::uint64_t& target) {
      if (arg.rfind(prefix, 0) != 0) return false;
      const char* begin = argv[i] + std::strlen(prefix);
      char* end = nullptr; errno = 0;
      const auto value = std::strtoull(begin, &end, 0);
      if (errno || begin == end || *end || *begin == '-')
        throw std::invalid_argument("invalid architecture runner cycle option");
      target = value;
      return true;
    };
    if (number("--max-cycles=", result.max_cycles) ||
        number("--reset-cycles=", result.reset_cycles)) continue;
    if (!arg.empty() && arg[0] == '+') continue;
    throw std::invalid_argument("usage: run-model-architecture [--max-cycles=N] [--reset-cycles=N] [+RTL_ARGS] -- BINARY [TARGET_ARGS]");
  }
  if (result.htif_start < 0 || result.htif_start >= argc ||
      result.max_cycles <= result.reset_cycles)
    throw std::invalid_argument("architecture runner requires a binary and a nonempty post-reset budget");
  return result;
}

struct Program { std::uint64_t entry = 0, tohost = 0, initial_tohost = 0; };
Program program(const char* path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) throw std::runtime_error("cannot open architecture target ELF");
  const std::vector<char> data{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
  const auto bytes = [&](std::uint64_t offset, std::uint64_t size) {
    if (offset > data.size() || size > data.size() - offset)
      throw std::runtime_error("truncated architecture target ELF");
    return data.data() + offset;
  };
  Elf64_Ehdr header;
  std::memcpy(&header, bytes(0, sizeof(header)), sizeof(header));
  if (std::memcmp(header.e_ident, ELFMAG, SELFMAG) ||
      header.e_ident[EI_CLASS] != ELFCLASS64 || header.e_ident[EI_DATA] != ELFDATA2LSB ||
      header.e_machine != EM_RISCV || header.e_shentsize != sizeof(Elf64_Shdr))
    throw std::runtime_error("architecture checker requires a little-endian RV64 ELF with symbols");
  const auto section = [&](unsigned index) {
    if (index >= header.e_shnum) throw std::runtime_error("invalid ELF section link");
    Elf64_Shdr result;
    std::memcpy(&result, bytes(header.e_shoff + std::uint64_t(index) * sizeof(result), sizeof(result)), sizeof(result));
    return result;
  };
  Program result{header.e_entry, 0, 0};
  for (unsigned i = 0; i < header.e_shnum; ++i) {
    const auto symbols = section(i);
    if (symbols.sh_type != SHT_SYMTAB && symbols.sh_type != SHT_DYNSYM) continue;
    if (symbols.sh_entsize != sizeof(Elf64_Sym) || symbols.sh_size % sizeof(Elf64_Sym))
      throw std::runtime_error("invalid ELF symbol table");
    const auto strings = section(symbols.sh_link);
    const char* names = bytes(strings.sh_offset, strings.sh_size);
    const char* table = bytes(symbols.sh_offset, symbols.sh_size);
    for (std::uint64_t at = 0; at < symbols.sh_size; at += sizeof(Elf64_Sym)) {
      Elf64_Sym symbol;
      std::memcpy(&symbol, table + at, sizeof(symbol));
      if (symbol.st_name >= strings.sh_size ||
          !std::memchr(names + symbol.st_name, 0, strings.sh_size - symbol.st_name))
        throw std::runtime_error("invalid ELF symbol name");
      if (std::strcmp(names + symbol.st_name, "tohost") == 0 && symbol.st_shndx != SHN_UNDEF) {
        if (result.tohost && result.tohost != symbol.st_value)
          throw std::runtime_error("ambiguous ELF tohost symbol");
        result.tohost = symbol.st_value;
        const auto storage = section(symbol.st_shndx);
        if (symbol.st_value < storage.sh_addr || symbol.st_value - storage.sh_addr > storage.sh_size ||
            storage.sh_size - (symbol.st_value - storage.sh_addr) < 8)
          throw std::runtime_error("ELF does not define the full initial tohost word");
        if (storage.sh_type == SHT_NOBITS) result.initial_tohost = 0;
        else if (storage.sh_type == SHT_PROGBITS)
          std::memcpy(&result.initial_tohost,
                      bytes(storage.sh_offset + symbol.st_value - storage.sh_addr, 8), 8);
        else throw std::runtime_error("unsupported initial tohost storage");
      }
    }
  }
  if (!result.entry || !result.tohost) throw std::runtime_error("ELF entry/tohost boundary is unavailable");
  return result;
}

// Generated names/widths are checked against the newly emitted public root
// header. A missing architectural field is a build error, never zero-filled.
struct RtlFields {
  const VTestHarness___024root& root;
#define ARCHITECTURE_RTL_FIELD(name, width, member) \
  std::uint64_t name() const { return root.member; }
#include "small_architecture_fields.inc"
#undef ARCHITECTURE_RTL_FIELD
};

class RtlRetirement {
 public:
  RetirementEvent before_edge(const VTestHarness___024root& root, std::uint64_t cycle, bool reset) {
    RetirementEvent result;
    enq_valid_ = false;
    if (reset) { debug_.fill(false); sequence_ = 0; return result; }
    const RtlFields fields{root};
    if (fields.core_clock()) throw std::runtime_error("reference core clock did not reach its low phase");
    if (fields.valid()) {
      result.valid = true; result.sequence = sequence_ + 1; result.cycle = cycle;
      result.pc = fields.pc(); result.is_rvc = fields.is_rvc();
      result.debug_mode = debug_[fields.rob_head() & 31u];
      result.instruction = fields.instruction() & (result.is_rvc ? UINT32_C(0xffff) : UINT32_MAX);
      result.expanded_instruction = fields.expanded_instruction();
      result.rd = fields.rd() & 31u;
      result.writes_x = fields.rd_valid() && fields.rd_type() == RT_FIX && result.rd != 0;
      result.writes_f = fields.rd_valid() && fields.rd_type() == RT_FLT;
      if (result.writes_x || result.writes_f) result.value = fields.value();
      result.fflags = fields.fflags_valid() ? fields.fflags() : 0;
      if (fields.uses_stq()) {
        std::uint64_t command = 0, size = 0, address = 0, data = 0;
#define READ_STQ(slot) case slot: \
        command = fields.stq##slot##_command(); size = fields.stq##slot##_size(); \
        address = fields.stq##slot##_address(); data = fields.stq##slot##_data(); break;
        switch (fields.stq_slot() & 7u) {
          READ_STQ(0) READ_STQ(1) READ_STQ(2) READ_STQ(3)
          READ_STQ(4) READ_STQ(5) READ_STQ(6) READ_STQ(7)
        }
#undef READ_STQ
        result.memory_write = command == 1;
        if (result.memory_write) {
          result.memory_size = size;
          result.memory_address = address;
          const unsigned bits = 8u << (size & 3u);
          result.memory_value = data & (bits == 64 ? UINT64_MAX : (UINT64_C(1) << bits) - 1);
        }
      }
    }
    // Read the retiring row before a same-edge enqueue can reuse it. DRET's
    // identity is its dispatch privilege, not CSR state already changed at EXE.
    enq_valid_ = fields.enq_valid();
    enq_tail_ = fields.rob_tail() & 31u;
    enq_debug_ = fields.debug_mode();
    return result;
  }
  void after_edge(const RetirementEvent& event, bool core_edge) {
    if (!core_edge) return;
    if (event.valid) ++sequence_;
    if (enq_valid_) debug_[enq_tail_] = enq_debug_;
  }
 private:
  std::array<bool, 32> debug_{};
  std::uint64_t sequence_ = 0;
  bool enq_valid_ = false, enq_debug_ = false;
  unsigned enq_tail_ = 0;
};

// Identical SimDTM driving convention to run_full_system_scalar_differential:
// keep the artifact's DPI call inert and overwrite its public output registers
// before each low/posedge pair using this RTL instance's own FESVR adapter.
void drive_dtm(VTestHarness___024root& root, const DtmOutputs& output) {
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg = output.req_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg = output.req_addr;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg = output.req_op;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg = output.req_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg = output.resp_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = output.exit;
}
DmiFeedback feedback(const VTestHarness___024root& root) {
  return {root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
          root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
          root.TestHarness__DOT__SimDTM_debug_resp_bits_resp,
          root.TestHarness__DOT__SimDTM_debug_resp_bits_data};
}
struct DmiAudit {
  std::uint64_t requests = 0, responses = 0;
  void observe(bool reset, bool request, bool ready, bool response, bool response_ready) {
    if (reset) { requests = responses = 0; return; }
    requests += request && ready;
    responses += response && response_ready;
    if (responses > requests) throw std::runtime_error("DMI response has no accepted request");
  }
};
}  // namespace

extern "C" int debug_tick(svBit* req_valid, svBit, int*, int*, int*, svBit,
                          svBit* resp_ready, int, int) {
  *req_valid = 0; *resp_ready = 0; return 0;
}

int main(int argc, char** argv) {
  std::unique_ptr<ArchitectureComparison> comparison;
  std::uint64_t model_cycles = 0, rtl_cycles = 0;
  bool model_done = false, rtl_done = false, model_success = false, rtl_success = false;
  int model_exit = -1, rtl_exit = -1;
  DmiAudit model_dmi, rtl_dmi;
  try {
    const Options run = options(argc, argv);
    const Program target = program(argv[run.htif_start]);
    comparison = std::make_unique<ArchitectureComparison>(target.entry, target.tohost, target.initial_tohost);
    std::vector<char*> htif{argv[0]};
    for (int i = run.htif_start; i < argc; ++i) htif.push_back(argv[i]);
    auto model_dtm = std::make_unique<dtm_t>(static_cast<int>(htif.size()), htif.data());
    chisa::boom_repcut::FesvrDebugBootstrap<dtm_t> model_debug(*model_dtm);
    chisa::boom_system::BoundaryConfig config;
    config.image_path = argv[run.htif_start]; config.argc = argc; config.argv = argv;
    config.reset_cycles = run.reset_cycles; config.debug_bootstrap = &model_debug;
    chisa::boom_system::SystemGuider model(config);

    auto rtl_dtm = std::make_unique<dtm_t>(static_cast<int>(htif.size()), htif.data());
    FesvrDtmAdapter<dtm_t> rtl_adapter(*rtl_dtm);
    auto context = std::make_unique<VerilatedContext>();
    context->randReset(0); context->commandArgs(argc, argv);
    auto rtl = std::make_unique<VTestHarness>(context.get());
    rtl->clock = 0; rtl->reset = 1; rtl->eval();
    RtlRetirement retired;

    while ((!model_done && model_cycles < run.max_cycles) ||
           (!rtl_done && rtl_cycles < run.max_cycles)) {
      if (!model_done && model_cycles < run.max_cycles) {
        const auto result = model.step();
        if (!result.ok) throw std::runtime_error(std::string("architectural model step failed: ") + result.failure);
        const auto& dmi = model.last_dmi();
        model_dmi.observe(dmi.reset, dmi.req_valid, dmi.req_ready, dmi.resp_valid, dmi.resp_ready);
        comparison->push_model(model.backend().core().retirement_event());
        ++model_cycles;
        model_success |= dmi.exit == 1;
        model_done = model_dtm->done() && dmi.exit != 0;
        if (model_done) model_exit = model_dtm->exit_code();
      }
      if (!rtl_done && rtl_cycles < run.max_cycles) {
        const bool reset = rtl_cycles < run.reset_cycles;
        const DtmOutputs driven = rtl_adapter.outputs();
        rtl->reset = reset; drive_dtm(*rtl->rootp, driven);
        rtl->clock = 0; rtl->eval(); context->timeInc(1);
        auto event = retired.before_edge(*rtl->rootp, rtl_cycles, reset);
        const auto dmi = feedback(*rtl->rootp);
        rtl_dmi.observe(reset, driven.req_valid, dmi.req_ready, dmi.resp_valid, driven.resp_ready);
        rtl_success |= rtl->io_success != 0;
        rtl->clock = 1; rtl->eval(); context->timeInc(1);
        const bool core_edge = RtlFields{*rtl->rootp}.core_clock() != 0;
        retired.after_edge(event, core_edge);
        event.valid &= core_edge;
        rtl_adapter.advance(reset, dmi);
        comparison->push_rtl(event);
        ++rtl_cycles;
        rtl_done = rtl_dtm->done() && driven.exit != 0;
        if (rtl_done) rtl_exit = rtl_dtm->exit_code();
        if (context->gotFinish() && !rtl_done)
          throw std::runtime_error("RTL stopped before a normal FESVR program exit");
      }
    }
    rtl->final();
    if (!model_done || !rtl_done) throw std::runtime_error("architecture program comparison timed out");
    if (model_exit != 0 || rtl_exit != 0 || !model_success || !rtl_success)
      throw std::runtime_error("architecture program exit/success boundary failed");
    comparison->finish();
    std::printf("ARCHITECTURAL_VALIDATION schema=1 status=pass model_cycles=%" PRIu64
                " rtl_cycles=%" PRIu64 " compared_retirements=%" PRIu64
                " compared_stores=%" PRIu64 " model_retired=%" PRIu64 " rtl_retired=%" PRIu64
                " model_exit=%d rtl_exit=%d program_done=1 final_registers_compared=1"
                " register_scope=written-since-entry"
                " initialization_compared=0 internal_oracles_compared=0 dmi_cycle_compared=0"
                " dmi_model_requests=%" PRIu64 " dmi_model_responses=%" PRIu64
                " dmi_rtl_requests=%" PRIu64 " dmi_rtl_responses=%" PRIu64
                " scope=entry-through-htif-exit-store\n",
                model_cycles, rtl_cycles, comparison->compared(), comparison->compared_stores(),
                comparison->model_retired(), comparison->rtl_retired(), model_exit, rtl_exit,
                model_dmi.requests, model_dmi.responses, rtl_dmi.requests, rtl_dmi.responses);
    return 0;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "ARCHITECTURAL_VALIDATION schema=1 status=fail model_cycles=%" PRIu64
                 " rtl_cycles=%" PRIu64 " compared_retirements=%" PRIu64
                 " model_exit=%d rtl_exit=%d program_done=%u\narchitecture error: %s\n",
                 model_cycles, rtl_cycles, comparison ? comparison->compared() : 0,
                 model_exit, rtl_exit, unsigned(model_done && rtl_done), error.what());
    return 2;
  }
}
