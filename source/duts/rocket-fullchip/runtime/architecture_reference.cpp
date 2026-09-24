#include "VTestHarness.h"
#include "VTestHarness___024root.h"
#include "VTestHarness__Dpi.h"
#include "architecture_contract.h"
#include "dmi_host_api.h"

#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace arch = chisa::rocket_architecture;
namespace host = chisa::rocket_fullchip;

namespace {
struct Options {
  std::string image, trace, summary;
  uint64_t load_address = 0x80000000, entry = 0x80000000;
  uint64_t tohost = 0x80001000, fromhost = 0x80001040;
  uint64_t reset_cycles = 64, max_cycles = 5000000, drain_cycles = 4096;
};

Options parse(int argc, char** argv) {
  Options o;
  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (!arg.empty() && arg.front() == '+') continue;
    const auto split = arg.find('=');
    if (split == std::string::npos) throw std::invalid_argument("expected --name=value: " + arg);
    const std::string key = arg.substr(0, split), value = arg.substr(split + 1);
    if (key == "--image") o.image = value;
    else if (key == "--trace") o.trace = value;
    else if (key == "--summary") o.summary = value;
    else {
      size_t used = 0;
      const uint64_t number = std::stoull(value, &used, 0);
      if (used != value.size()) throw std::invalid_argument("invalid integer: " + arg);
      if (key == "--load-address") o.load_address = number;
      else if (key == "--entry") o.entry = number;
      else if (key == "--tohost") o.tohost = number;
      else if (key == "--fromhost") o.fromhost = number;
      else if (key == "--reset-cycles") o.reset_cycles = number;
      else if (key == "--max-cycles") o.max_cycles = number;
      else if (key == "--drain-cycles") o.drain_cycles = number;
      else throw std::invalid_argument("unknown option: " + key);
    }
  }
  if (o.image.empty() || o.trace.empty() || o.summary.empty())
    throw std::invalid_argument("--image, --trace and --summary are required");
  return o;
}

std::vector<uint8_t> read_image(const std::string& path) {
  std::ifstream input(path, std::ios::binary | std::ios::ate);
  if (!input) throw std::runtime_error("cannot read image " + path);
  const auto bytes = input.tellg();
  if (bytes <= 0 || bytes > 0x10000000) throw std::runtime_error("invalid image size");
  std::vector<uint8_t> data(static_cast<size_t>(bytes));
  input.seekg(0);
  input.read(reinterpret_cast<char*>(data.data()), bytes);
  if (!input) throw std::runtime_error("short image read");
  return data;
}

void drive_dmi(VTestHarness___024root& root, const host::DmiHostOutputs& in) {
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg = in.request_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg = in.request_address;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg = in.request_operation;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg = in.request_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg = in.response_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = 0;
}

bool console_store(const arch::Sample& s, uint64_t tohost) {
  const unsigned opcode = s.expanded_instruction & 0x7f;
  return s.retired && !s.debug_mode && (opcode == 0x23 || opcode == 0x27) &&
         ((s.expanded_instruction >> 12) & 7) == 3 && s.store_address == tohost &&
         (s.store_value >> 56) == 1 && ((s.store_value >> 48) & 255) == 1;
}
}  // namespace

// SimDTM keeps its normal registered transport. The explicit host presents
// the current registered values before each target edge; this DPI body never
// supplies oracle/model state and never requests termination.
extern "C" int debug_tick(svBit* request_valid, svBit request_ready,
                          int* address, int* operation, int* data,
                          svBit response_valid, svBit* response_ready,
                          int response_status, int response_data) {
  (void)request_ready; (void)address; (void)operation; (void)data;
  (void)response_valid; (void)response_status; (void)response_data;
  *request_valid = 0; *response_ready = 0;
  return 0;
}

int main(int argc, char** argv) {
  try {
    const Options o = parse(argc, argv);
    const auto image = read_image(o.image);
    if (o.load_address < 0x80000000 || o.load_address > 0x90000000 - image.size())
      throw std::invalid_argument("image does not fit locked DRAM");
    arch::Configuration config;
    config.role = "rtl-reference"; config.firrtl_sha256 = arch::kReferenceFirrtlSha256;
    config.program_begin = o.load_address; config.program_end = o.load_address + image.size();
    config.tohost = o.tohost; config.image_bytes = image.size();
    config.image_fnv64 = arch::hash_bytes(image.data(), image.size());
    arch::Recorder recorder(config, o.trace);
    auto context = std::make_unique<VerilatedContext>();
    context->randReset(0); context->commandArgs(argc, argv);
    auto dut = std::make_unique<VTestHarness>(context.get());
    auto& root = *dut->rootp;
    dut->clock = 0; dut->reset = 1; dut->eval();
    for (size_t i = 0; i < image.size(); ++i) arch::write_reference_byte(root, o.load_address + i, image[i]);
    for (unsigned i = 0; i < 8; ++i) {
      arch::write_reference_byte(root, o.tohost + i, 0);
      arch::write_reference_byte(root, o.fromhost + i, 0);
    }
    host::dmi_host_configure(o.entry, o.tohost, o.fromhost);
    bool previous_reset = false, console_pending = false, terminal_requested = false;
    uint64_t cycles = 0;
    for (; cycles < o.max_cycles; ++cycles) {
      const bool reset = cycles < o.reset_cycles;
      const bool enabled = !reset && !previous_reset;
      const auto outputs = enabled ? host::dmi_host_outputs() : host::DmiHostOutputs{};
      dut->reset = reset;
      drive_dmi(root, outputs);
      dut->clock = 0; dut->eval(); context->timeInc(1);
      auto sample = arch::sample_reference(root, cycles, reset);
      sample.environment_debug = !host::dmi_host_idle();
      const bool console = !reset && console_store(sample, o.tohost);
      if (enabled) host::dmi_host_advance(root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
          root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
          root.TestHarness__DOT__SimDTM_debug_resp_bits_resp,
          root.TestHarness__DOT__SimDTM_debug_resp_bits_data);
      previous_reset = reset;
      dut->clock = 1; dut->eval(); context->timeInc(1);
      recorder.observe(sample);
      if (console) console_pending = true;
      if (!recorder.cutoff_seen() && console_pending && host::dmi_host_bootstrap_complete() && host::dmi_host_idle()) {
        host::dmi_host_request_console_ack(); console_pending = false;
      }
      if (recorder.cutoff_seen() && !terminal_requested && host::dmi_host_bootstrap_complete() && host::dmi_host_idle()) {
        host::dmi_host_request_tohost_read(); terminal_requested = true;
      }
      if (host::dmi_host_failed()) throw std::runtime_error(host::dmi_host_error());
      if (terminal_requested && host::dmi_host_tohost_reads()) {
        recorder.confirm_tohost(host::dmi_host_last_tohost());
        if (recorder.done() || !recorder.tohost_confirmed()) { ++cycles; break; }
      }
      if (recorder.cutoff_seen() && cycles - recorder.cutoff_cycle() >= o.drain_cycles) break;
      if (context->gotFinish()) throw std::runtime_error("RTL finished before the architecture endpoint");
    }
    const bool complete = recorder.finish(o.summary);
    std::printf("ROCKET_ARCH_REFERENCE status=%s cycles=%" PRIu64 " endpoint_cycle=%" PRIu64
                " tohost=%s unresolved=%" PRIu64 " oracle_injection=off\n",
                complete ? "complete" : "incomplete", cycles, recorder.cutoff_cycle(),
                arch::hex(recorder.exit_value()).c_str(), recorder.unresolved_records());
    dut->final();
    return complete ? 0 : 3;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "ROCKET_ARCH_REFERENCE_ERROR %s\n", error.what());
    return 2;
  }
}
