#include "native_system.h"
#include "architecture_reference.h"
#include "dmi_host_api.h"
#include <sys/mman.h>
#include <cinttypes>
#include <cstdio>
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

bool console_store(const arch::Sample& s, uint64_t tohost) {
  const unsigned opcode = s.expanded_instruction & 0x7f;
  return s.retired && !s.debug_mode && (opcode == 0x23 || opcode == 0x27) &&
         ((s.expanded_instruction >> 12) & 7) == 3 && s.store_address == tohost &&
         (s.store_value >> 56) == 1 && ((s.store_value >> 48) & 255) == 1;
}
}  // namespace

int main(int argc, char** argv) {
  try {
    const Options o = parse(argc, argv);
    const auto image = read_image(o.image);
    if (o.load_address < 0x80000000 || o.load_address > 0x90000000 - image.size())
      throw std::invalid_argument("image does not fit locked DRAM");
    arch::Configuration config;
    config.role = "native-model"; config.firrtl_sha256 = arch::kLockedFirrtlSha256;
    config.program_begin = o.load_address; config.program_end = o.load_address + image.size();
    config.tohost = o.tohost; config.image_bytes = image.size();
    config.image_fnv64 = arch::hash_bytes(image.data(), image.size());
    arch::Recorder recorder(config, o.trace);
    struct Memory {
      uint8_t* data = static_cast<uint8_t*>(mmap(nullptr, 0x10000000, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0));
      Memory() { if (data == MAP_FAILED) throw std::runtime_error("cannot map native DRAM"); }
      ~Memory() { munmap(data, 0x10000000); }
    } memory;
    for (size_t i = 0; i < image.size(); ++i) memory.data[o.load_address - 0x80000000 + i] = image[i];
    chisa::rocket_model::NativeSystem model;
    model.attach_memory(memory.data, 0x10000000);
    model.write_dram_word(o.tohost, 0); model.write_dram_word(o.fromhost, 0);
    host::dmi_host_configure(o.entry, o.tohost, o.fromhost);
    bool previous_reset = false, console_pending = false, terminal_requested = false;
    uint64_t cycles = 0;
    for (; cycles < o.max_cycles; ++cycles) {
      chisa::rocket_model::NativeSystemInputs input;
      input.reset = cycles < o.reset_cycles;
      const bool enabled = !input.reset && !previous_reset;
      const auto request = enabled ? host::dmi_host_outputs() : host::DmiHostOutputs{};
      const bool environment_debug = !host::dmi_host_idle();
      input.dmi_req_valid = request.request_valid; input.dmi_req_addr = request.request_address;
      input.dmi_req_data = request.request_data; input.dmi_req_op = request.request_operation;
      input.dmi_resp_ready = request.response_ready;
      const auto out = model.step(input);
      const auto& r = out.retirement;
      arch::Sample sample;
      sample.cycle = cycles; sample.reset = input.reset || out.core_reset;
      sample.retired = r.retired; sample.trapped = r.trapped; sample.debug_mode = r.debug_mode;
      sample.environment_debug = environment_debug; sample.pc = r.pc; sample.cause = r.cause;
      sample.instruction = r.instruction; sample.expanded_instruction = r.expanded_instruction;
      sample.privilege = r.privilege;
      sample.x_write = r.x_write; sample.x_value_valid = r.x_value_valid; sample.xrd = r.xrd; sample.xvalue = r.xvalue;
      sample.fp_write = r.fp_write; sample.frd = r.frd;
      sample.store_address = r.store_address; sample.store_value = r.store_value;
      const auto& late = model.core().late_integer_write();
      sample.late_x = {late.valid, late.rd, late.value};
      if (out.fp_write_count > 2) throw std::runtime_error("too many physical FP write ports");
      for (unsigned i = 0; i < out.fp_write_count; ++i) sample.fp[i] = {true, out.fp_writes[i].reg, out.fp_writes[i].value};
      const bool console = !sample.reset && console_store(sample, o.tohost);
      if (enabled) host::dmi_host_advance(out.dmi_req_ready, out.dmi_resp_valid, out.dmi_resp_resp, out.dmi_resp_data);
      previous_reset = input.reset;
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
    }
    const bool complete = recorder.finish(o.summary);
    std::printf("ROCKET_ARCH_MODEL status=%s cycles=%" PRIu64 " endpoint_cycle=%" PRIu64
                " tohost=%s confirmed=%d unresolved=%" PRIu64 " generated_rtl=none oracle_injection=off\n",
                complete ? "complete" : "incomplete", cycles, recorder.cutoff_cycle(),
                arch::hex(recorder.exit_value()).c_str(), recorder.tohost_confirmed(), recorder.unresolved_records());
    return complete ? 0 : 3;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "ROCKET_ARCH_MODEL_ERROR %s\n", error.what());
    return 2;
  }
}
