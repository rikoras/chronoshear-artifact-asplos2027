#include "VTestHarness.h"
#include "VTestHarness__Dpi.h"
#include "VTestHarness___024root.h"

#include <cerrno>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "dmi_host_api.h"
#include "w1_reference_runtime.h"

namespace {

using chisa::rocket_fullchip::DmiHostOutputs;
using chisa::rocket_fullchip::HalfDirection;
using chisa::rocket_fullchip::TapPhase;

constexpr std::uint64_t kMemoryBase = UINT64_C(0x80000000);
constexpr std::uint64_t kMemoryBytes = UINT64_C(0x10000000);

struct Options {
  std::string image;
  std::uint64_t max_cycles = 50000;
  std::uint64_t reset_cycles = 10;
  std::uint64_t progress_cycles = 0;
  std::uint64_t load_address = kMemoryBase;
  std::uint64_t tohost_address = UINT64_C(0x80001000);
  std::uint64_t fromhost_address = UINT64_C(0x80001040);
  std::uint64_t console_wait_pc0 = UINT64_C(0x80001634);
  std::uint64_t console_wait_pc1 = UINT64_C(0x80001636);
  std::uint64_t console_wait_pc2 = UINT64_C(0x80001716);
  std::uint64_t console_wait_pc3 = UINT64_C(0x80001718);
  std::uint64_t exit_park_pc = UINT64_C(0x800016ae);
  std::uint64_t trap_park_pc = UINT64_C(0x800016be);
  bool allow_timeout = false;
};

[[noreturn]] void usage(const char* program) {
  std::fprintf(
      stderr,
      "usage: %s --image PATH [--max-cycles N] [--reset-cycles N] "
      "[--progress-cycles N] [--load-address N] [--tohost-address N] "
      "[--fromhost-address N] [--console-wait-pc0 N] "
      "[--console-wait-pc1 N] [--console-wait-pc2 N] "
      "[--console-wait-pc3 N] [--exit-park-pc N] [--trap-park-pc N] "
      "[--allow-timeout]\n",
      program);
  std::exit(2);
}

std::uint64_t parse_u64(const char* value, const char* option) {
  char* end = nullptr;
  errno = 0;
  const unsigned long long parsed = std::strtoull(value, &end, 0);
  if (errno != 0 || end == value || *end != '\0')
    throw std::invalid_argument(std::string("invalid ") + option + ": " +
                                value);
  return static_cast<std::uint64_t>(parsed);
}

Options parse_options(int argc, char** argv) {
  Options options;
  for (int index = 1; index < argc; ++index) {
    const std::string option = argv[index];
    if (option == "--help") usage(argv[0]);
    if (option == "--allow-timeout") {
      options.allow_timeout = true;
      continue;
    }
    if (index + 1 >= argc) usage(argv[0]);
    const char* value = argv[++index];
    if (option == "--image")
      options.image = value;
    else if (option == "--max-cycles")
      options.max_cycles = parse_u64(value, option.c_str());
    else if (option == "--reset-cycles")
      options.reset_cycles = parse_u64(value, option.c_str());
    else if (option == "--progress-cycles")
      options.progress_cycles = parse_u64(value, option.c_str());
    else if (option == "--load-address")
      options.load_address = parse_u64(value, option.c_str());
    else if (option == "--tohost-address")
      options.tohost_address = parse_u64(value, option.c_str());
    else if (option == "--fromhost-address")
      options.fromhost_address = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc0")
      options.console_wait_pc0 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc1")
      options.console_wait_pc1 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc2")
      options.console_wait_pc2 = parse_u64(value, option.c_str());
    else if (option == "--console-wait-pc3")
      options.console_wait_pc3 = parse_u64(value, option.c_str());
    else if (option == "--exit-park-pc")
      options.exit_park_pc = parse_u64(value, option.c_str());
    else if (option == "--trap-park-pc")
      options.trap_park_pc = parse_u64(value, option.c_str());
    else
      usage(argv[0]);
  }
  if (options.image.empty() || options.max_cycles == 0) usage(argv[0]);
  return options;
}

std::vector<std::uint8_t> read_image(const std::string& path) {
  std::ifstream source(path, std::ios::binary | std::ios::ate);
  if (!source) throw std::runtime_error("cannot open image: " + path);
  const std::streamoff size = source.tellg();
  if (size < 0 || static_cast<std::uint64_t>(size) > kMemoryBytes)
    throw std::runtime_error("invalid or oversized image: " + path);
  source.seekg(0);
  std::vector<std::uint8_t> bytes(static_cast<std::size_t>(size));
  if (!bytes.empty()) {
    source.read(reinterpret_cast<char*>(bytes.data()), size);
    if (!source) throw std::runtime_error("short read from image: " + path);
  }
  return bytes;
}

std::size_t memory_word_index(std::uint64_t address) {
  if (address < kMemoryBase || address >= kMemoryBase + kMemoryBytes)
    throw std::out_of_range("physical address is outside SimAXIMem");
  return static_cast<std::size_t>((address - kMemoryBase) >> 3);
}

UInt<8>* scalar_memory_bank(TestHarness& dut, unsigned bank) {
  switch (bank) {
    case 0: return dut.mem.srams.mem_0.get();
    case 1: return dut.mem.srams.mem_1.get();
    case 2: return dut.mem.srams.mem_2.get();
    case 3: return dut.mem.srams.mem_3.get();
    case 4: return dut.mem.srams.mem_4.get();
    case 5: return dut.mem.srams.mem_5.get();
    case 6: return dut.mem.srams.mem_6.get();
    case 7: return dut.mem.srams.mem_7.get();
  }
  throw std::out_of_range("invalid scalar SimAXIMem byte bank");
}

const UInt<8>* scalar_memory_bank(const TestHarness& dut, unsigned bank) {
  return scalar_memory_bank(const_cast<TestHarness&>(dut), bank);
}

auto& verilator_memory(VTestHarness___024root& root) {
  return root.TestHarness__DOT__mem__DOT__srams__DOT__mem__DOT__mem_ext__DOT__ram;
}

const auto& verilator_memory(const VTestHarness___024root& root) {
  return root.TestHarness__DOT__mem__DOT__srams__DOT__mem__DOT__mem_ext__DOT__ram;
}

void write_scalar_byte(TestHarness& dut, std::uint64_t address,
                       std::uint8_t value) {
  const unsigned bank = static_cast<unsigned>(address & 7);
  scalar_memory_bank(dut, bank)[memory_word_index(address)] = UInt<8>(value);
}

void write_verilator_byte(VTestHarness___024root& root, std::uint64_t address,
                          std::uint8_t value) {
  const std::size_t index = memory_word_index(address);
  const unsigned shift = static_cast<unsigned>((address & 7) * 8);
  const std::uint64_t mask = UINT64_C(0xff) << shift;
  const std::uint64_t old =
      static_cast<std::uint64_t>(verilator_memory(root)[index]);
  verilator_memory(root)[index] =
      (old & ~mask) | (static_cast<std::uint64_t>(value) << shift);
}

void load_image(TestHarness& scalar, VTestHarness___024root& verilator,
                std::uint64_t address,
                const std::vector<std::uint8_t>& bytes) {
  if (address < kMemoryBase || bytes.size() > kMemoryBytes ||
      address - kMemoryBase > kMemoryBytes - bytes.size())
    throw std::out_of_range("image does not fit in SimAXIMem");
  for (std::size_t index = 0; index < bytes.size(); ++index) {
    write_scalar_byte(scalar, address + index, bytes[index]);
    write_verilator_byte(verilator, address + index, bytes[index]);
  }
}

std::uint64_t read_scalar_word(const TestHarness& dut,
                               std::uint64_t address) {
  if ((address & 7) != 0)
    throw std::invalid_argument("unaligned scalar memory read");
  std::uint64_t value = 0;
  for (unsigned bank = 0; bank < 8; ++bank) {
    value |= chisa::rocket_fullchip::port_value(
                 scalar_memory_bank(dut, bank)[memory_word_index(address)])
             << (bank * 8);
  }
  return value;
}

std::uint64_t read_verilator_word(const VTestHarness___024root& root,
                                  std::uint64_t address) {
  if ((address & 7) != 0)
    throw std::invalid_argument("unaligned Verilator memory read");
  return static_cast<std::uint64_t>(
      verilator_memory(root)[memory_word_index(address)]);
}

void write_host_word(TestHarness& scalar, VTestHarness___024root& verilator,
                     std::uint64_t address, std::uint64_t value) {
  for (unsigned byte = 0; byte < 8; ++byte) {
    const std::uint8_t part = static_cast<std::uint8_t>(value >> (byte * 8));
    write_scalar_byte(scalar, address + byte, part);
    write_verilator_byte(verilator, address + byte, part);
  }
}

std::uint64_t observed_pc(const VTestHarness___024root& root) {
  return static_cast<std::uint64_t>(
      root.TestHarness__DOT__ldut__DOT__tile_prci_domain__DOT__tile_reset_domain_tile__DOT__core__DOT__coreMonitorBundle_pc);
}

struct DmiFeedback {
  bool request_ready = false;
  bool response_valid = false;
  std::uint32_t response_status = 0;
  std::uint32_t response_data = 0;

  friend bool operator==(const DmiFeedback& left, const DmiFeedback& right) {
    return left.request_ready == right.request_ready &&
           left.response_valid == right.response_valid &&
           left.response_status == right.response_status &&
           left.response_data == right.response_data;
  }
};

void drive_scalar_dmi(TestHarness& dut, const DmiHostOutputs& outputs) {
  auto& ports = chisa::rocket_fullchip::simdtm_ports(dut);
  chisa::rocket_fullchip::assign_port(ports.debug_req_valid[0],
                                     outputs.request_valid);
  chisa::rocket_fullchip::assign_port(ports.debug_req_bits_addr[0],
                                     outputs.request_address);
  chisa::rocket_fullchip::assign_port(ports.debug_req_bits_op[0],
                                     outputs.request_operation);
  chisa::rocket_fullchip::assign_port(ports.debug_req_bits_data[0],
                                     outputs.request_data);
  chisa::rocket_fullchip::assign_port(ports.debug_resp_ready[0],
                                     outputs.response_ready);
  chisa::rocket_fullchip::assign_port(ports.exit[0], 0);
}

DmiFeedback scalar_dmi_feedback(const TestHarness& dut) {
  const auto& ports = chisa::rocket_fullchip::simdtm_ports(
      const_cast<TestHarness&>(dut));
  return DmiFeedback{
      chisa::rocket_fullchip::port_value(ports.debug_req_ready[0]) != 0,
      chisa::rocket_fullchip::port_value(ports.debug_resp_valid[0]) != 0,
      static_cast<std::uint32_t>(chisa::rocket_fullchip::port_value(
          ports.debug_resp_bits_resp[0])),
      static_cast<std::uint32_t>(chisa::rocket_fullchip::port_value(
          ports.debug_resp_bits_data[0]))};
}

void drive_verilator_dmi(VTestHarness___024root& root,
                         const DmiHostOutputs& outputs) {
  root.TestHarness__DOT__SimDTM__DOT__debug_req_valid_reg =
      outputs.request_valid;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_addr_reg =
      outputs.request_address;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_op_reg =
      outputs.request_operation;
  root.TestHarness__DOT__SimDTM__DOT__debug_req_bits_data_reg =
      outputs.request_data;
  root.TestHarness__DOT__SimDTM__DOT__debug_resp_ready_reg =
      outputs.response_ready;
  root.TestHarness__DOT__SimDTM__DOT__exit_reg = 0;
}

DmiFeedback verilator_dmi_feedback(const VTestHarness___024root& root) {
  return DmiFeedback{
      root.TestHarness__DOT__SimDTM_debug_req_ready != 0,
      root.TestHarness__DOT__SimDTM_debug_resp_valid != 0,
      static_cast<std::uint32_t>(
          root.TestHarness__DOT__SimDTM_debug_resp_bits_resp),
      static_cast<std::uint32_t>(
          root.TestHarness__DOT__SimDTM_debug_resp_bits_data)};
}

struct ExpectedTap {
  TapPhase phase;
  const char* trace_key;
  unsigned width;
  std::uint64_t value;
};

class ExactTapObserver {
 public:
  ExactTapObserver() {
    expected_.reserve(chisa::rocket_fullchip::kExactRegisterTapCount +
                      chisa::rocket_fullchip::kExactCombinationalTapCount);
  }

  bool capture_cycle(std::uint64_t cycle) const { return cycle != 0; }

  void prepare_cycle(VTestHarness___024root& root, std::uint64_t cycle,
                     HalfDirection direction) {
    begin(cycle, direction);
    if (!capture_cycle(cycle)) return;
#define VERILATOR_TAP(expr, trace_key, bit_width)                             \
  expected_.push_back(ExpectedTap{TapPhase::pre_eval_register, (trace_key),   \
                                  (bit_width),                                \
                                  static_cast<std::uint64_t>(expr)})
#include "verilator_reg_tap_fields.inc"
#undef VERILATOR_TAP
#define VERILATOR_TAP(expr, trace_key, bit_width)                             \
  expected_.push_back(ExpectedTap{TapPhase::post_eval_combinational,          \
                                  (trace_key), (bit_width),                    \
                                  static_cast<std::uint64_t>(expr)})
#include "verilator_comb_tap_fields.inc"
#undef VERILATOR_TAP
  }

  void prepare_terminal(VTestHarness___024root& root, std::uint64_t cycle,
                        HalfDirection direction) {
    begin(cycle, direction);
#define VERILATOR_TAP(expr, trace_key, bit_width)                             \
  expected_.push_back(ExpectedTap{TapPhase::pre_eval_register, (trace_key),   \
                                  (bit_width),                                \
                                  static_cast<std::uint64_t>(expr)})
#include "verilator_reg_tap_fields.inc"
#undef VERILATOR_TAP
  }

  void observe(std::uint64_t cycle, HalfDirection direction, TapPhase phase,
               const char* trace_key, std::uint64_t scalar_value) {
    if (cycle != cycle_ || direction != direction_)
      throw std::runtime_error("tap observer cycle/direction drift");
    if (cursor_ >= expected_.size())
      throw std::runtime_error("CHISA emitted more taps than Verilator");
    const ExpectedTap& expected = expected_[cursor_++];
    if (phase != expected.phase ||
        std::strcmp(trace_key, expected.trace_key) != 0) {
      std::fprintf(stderr,
                   "ROCKET_W1_TAP_ORDER_MISMATCH cycle=%" PRIu64
                   " direction=%s index=%zu scalar=%s/%s rtl=%s/%s\n",
                   cycle, chisa::rocket_fullchip::direction_name(direction),
                   cursor_ - 1, chisa::rocket_fullchip::phase_name(phase),
                   trace_key,
                   chisa::rocket_fullchip::phase_name(expected.phase),
                   expected.trace_key);
      throw std::runtime_error("manifest tap order mismatch");
    }
    const std::uint64_t mask =
        chisa::rocket_fullchip::width_mask(expected.width);
    const std::uint64_t actual = scalar_value & mask;
    const std::uint64_t reference = expected.value & mask;
    if (actual != reference) {
      std::fprintf(stderr,
                   "ROCKET_W1_TAP_MISMATCH cycle=%" PRIu64
                   " direction=%s phase=%s index=%zu key=%s width=%u"
                   " scalar=0x%016" PRIx64 " verilator=0x%016" PRIx64 "\n",
                   cycle, chisa::rocket_fullchip::direction_name(direction),
                   chisa::rocket_fullchip::phase_name(phase), cursor_ - 1,
                   trace_key, expected.width, actual, reference);
      throw std::runtime_error("manifest-exact scalar mismatch");
    }
    mix(reference);
    ++comparisons_;
  }

  void finish() const {
    if (cursor_ != expected_.size())
      throw std::runtime_error("CHISA emitted fewer taps than Verilator");
  }

  std::uint64_t comparisons() const { return comparisons_; }
  std::uint64_t digest() const { return digest_; }

 private:
  void begin(std::uint64_t cycle, HalfDirection direction) {
    expected_.clear();
    cursor_ = 0;
    cycle_ = cycle;
    direction_ = direction;
  }

  void mix(std::uint64_t value) {
    for (unsigned byte = 0; byte < 8; ++byte) {
      digest_ ^= static_cast<std::uint8_t>(value >> (byte * 8));
      digest_ *= UINT64_C(1099511628211);
    }
  }

  std::vector<ExpectedTap> expected_;
  std::size_t cursor_ = 0;
  std::uint64_t cycle_ = 0;
  HalfDirection direction_ = HalfDirection::forward;
  std::uint64_t comparisons_ = 0;
  std::uint64_t digest_ = UINT64_C(1469598103934665603);
};

void require_same_feedback(std::uint64_t cycle, const DmiFeedback& scalar,
                           const DmiFeedback& verilator) {
  if (scalar == verilator) return;
  std::fprintf(
      stderr,
      "ROCKET_W1_DMI_MISMATCH cycle=%" PRIu64
      " scalar={ready=%u valid=%u status=%u data=%08" PRIx32 "}"
      " verilator={ready=%u valid=%u status=%u data=%08" PRIx32 "}\n",
      cycle, static_cast<unsigned>(scalar.request_ready),
      static_cast<unsigned>(scalar.response_valid), scalar.response_status,
      scalar.response_data, static_cast<unsigned>(verilator.request_ready),
      static_cast<unsigned>(verilator.response_valid),
      verilator.response_status, verilator.response_data);
  throw std::runtime_error("DMI feedback mismatch");
}

}  // namespace

// The public SimDTM output registers are driven by the same explicit DMI host
// used by the W=1 model.  Keep the Verilated DPI instance inert.
extern "C" int debug_tick(svBit* debug_req_valid, svBit debug_req_ready,
                          int* debug_req_bits_addr, int* debug_req_bits_op,
                          int* debug_req_bits_data, svBit debug_resp_valid,
                          svBit* debug_resp_ready, int debug_resp_bits_resp,
                          int debug_resp_bits_data) {
  (void)debug_req_ready;
  (void)debug_req_bits_addr;
  (void)debug_req_bits_op;
  (void)debug_req_bits_data;
  (void)debug_resp_valid;
  (void)debug_resp_bits_resp;
  (void)debug_resp_bits_data;
  *debug_req_valid = 0;
  *debug_resp_ready = 0;
  return 0;
}

int main(int argc, char** argv) {
  try {
    const Options options = parse_options(argc, argv);
    const std::vector<std::uint8_t> image = read_image(options.image);

    auto scalar = std::make_unique<TestHarness>();
    chisa::rocket_fullchip::initialize_plusarg_readers(*scalar, argc, argv);
    char empty_oracle = 0;
    scalar->oracle_win_base = &empty_oracle;

    auto context = std::make_unique<VerilatedContext>();
    context->randReset(0);
    context->commandArgs(argc, argv);
    auto verilator = std::make_unique<VTestHarness>(context.get());
    verilator->clock = 0;
    verilator->reset = 1;
    verilator->eval();

    load_image(*scalar, *verilator->rootp, options.load_address, image);
    write_host_word(*scalar, *verilator->rootp, options.tohost_address, 0);
    write_host_word(*scalar, *verilator->rootp, options.fromhost_address, 0);
    chisa::rocket_fullchip::dmi_host_configure(
        options.load_address, options.tohost_address, options.fromhost_address);

    ExactTapObserver observer;
    HalfDirection direction = HalfDirection::forward;
    bool simdtm_reset_delay = false;
    bool console_ack_armed = true;
    bool terminal_read_requested = false;
    std::uint64_t console_wait_streak = 0;
    std::uint64_t terminal_streak = 0;
    std::uint64_t terminal_pc = 0;
    std::uint64_t final_tohost = 0;
    std::uint64_t cycles = 0;

    for (; cycles < options.max_cycles; ++cycles) {
      const bool reset = cycles < options.reset_cycles;
      const bool simdtm_enabled = !reset && !simdtm_reset_delay;
      const DmiHostOutputs outputs =
          simdtm_enabled ? chisa::rocket_fullchip::dmi_host_outputs()
                         : DmiHostOutputs{};

      chisa::rocket_fullchip::assign_port(scalar->reset, reset);
      drive_scalar_dmi(*scalar, outputs);
      verilator->reset = reset;
      drive_verilator_dmi(*verilator->rootp, outputs);
      verilator->clock = 0;
      verilator->eval();
      context->timeInc(1);

      observer.prepare_cycle(*verilator->rootp, cycles, direction);
      if (observer.capture_cycle(cycles))
        chisa::rocket_fullchip::sample_exact_register_tap(
            *scalar, observer, cycles, direction);

      if (direction == HalfDirection::forward)
        scalar->eval_forward(true, false, !reset);
      else
        scalar->eval_reverse(true, false, !reset);
      if (scalar->assert_triggered)
        throw std::runtime_error("generated W1 model asserted");

      if (observer.capture_cycle(cycles))
        chisa::rocket_fullchip::sample_exact_combinational_tap(
            observer, cycles, direction);
      observer.finish();

      const DmiFeedback scalar_feedback = scalar_dmi_feedback(*scalar);
      const DmiFeedback verilator_feedback =
          verilator_dmi_feedback(*verilator->rootp);
      require_same_feedback(cycles, scalar_feedback, verilator_feedback);
      if (chisa::rocket_fullchip::port_value(scalar->io_success[0]) !=
          static_cast<std::uint64_t>(verilator->io_success != 0))
        throw std::runtime_error("io_success mismatch");
      if (simdtm_enabled) {
        chisa::rocket_fullchip::dmi_host_advance(
            scalar_feedback.request_ready, scalar_feedback.response_valid,
            scalar_feedback.response_status, scalar_feedback.response_data);
      }
      simdtm_reset_delay = reset;

      verilator->clock = 1;
      verilator->eval();
      context->timeInc(1);

      if (chisa::rocket_fullchip::dmi_host_failed())
        throw std::runtime_error(chisa::rocket_fullchip::dmi_host_error());
      if (chisa::rocket_fullchip::dmi_host_tohost_reads() != 0) {
        final_tohost = chisa::rocket_fullchip::dmi_host_last_tohost();
        ++cycles;
        break;
      }

      const std::uint64_t scalar_backing =
          read_scalar_word(*scalar, options.tohost_address);
      const std::uint64_t verilator_backing =
          read_verilator_word(*verilator->rootp, options.tohost_address);
      if (scalar_backing != verilator_backing)
        throw std::runtime_error("SimAXIMem tohost backing mismatch");

      const std::uint64_t pc = observed_pc(*verilator->rootp);
      const bool console_wait =
          pc == options.console_wait_pc0 || pc == options.console_wait_pc1 ||
          pc == options.console_wait_pc2 || pc == options.console_wait_pc3;
      const bool terminal_wait =
          pc == options.exit_park_pc || pc == options.trap_park_pc;
      if (!console_wait) {
        console_wait_streak = 0;
        console_ack_armed = true;
      } else if (console_ack_armed) {
        ++console_wait_streak;
      }
      terminal_streak = terminal_wait ? terminal_streak + 1 : 0;
      if (chisa::rocket_fullchip::dmi_host_bootstrap_complete() &&
          chisa::rocket_fullchip::dmi_host_idle()) {
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

      if (options.progress_cycles != 0 &&
          (cycles + 1) % options.progress_cycles == 0) {
        std::fprintf(stderr,
                     "ROCKET_W1_PROGRESS cycles=%" PRIu64
                     " pc=0x%016" PRIx64 " comparisons=%" PRIu64
                     " dmi_stage=%s transactions=%" PRIu64 "\n",
                     cycles + 1, pc, observer.comparisons(),
                     chisa::rocket_fullchip::dmi_host_stage(),
                     chisa::rocket_fullchip::dmi_host_transactions());
      }
      direction = direction == HalfDirection::forward
                      ? HalfDirection::reverse
                      : HalfDirection::forward;
    }

    // Compare the final next-state register image even when the requested
    // window ended immediately after an edge.
    const bool terminal_reset = cycles < options.reset_cycles;
    chisa::rocket_fullchip::assign_port(scalar->reset, terminal_reset);
    drive_scalar_dmi(*scalar, chisa::rocket_fullchip::dmi_host_outputs());
    verilator->reset = terminal_reset;
    drive_verilator_dmi(*verilator->rootp,
                        chisa::rocket_fullchip::dmi_host_outputs());
    verilator->clock = 0;
    verilator->eval();
    observer.prepare_terminal(*verilator->rootp, cycles, direction);
    chisa::rocket_fullchip::sample_exact_register_tap(
        *scalar, observer, cycles, direction);
    observer.finish();

    const bool pass = final_tohost == 1;
    const bool timed_out = final_tohost == 0 && cycles >= options.max_cycles;
    const char* status = pass ? "pass" : (timed_out ? "max-cycles" : "fail");
    std::printf(
        "ROCKET_W1_SCALAR_DIFF status=%s cycles=%" PRIu64
        " reset_cycles=%" PRIu64 " image_bytes=%zu tohost=0x%" PRIx64
        " pc=0x%016" PRIx64 " reg_taps=%zu comb_taps=%zu"
        " comparisons=%" PRIu64 " digest=%016" PRIx64
        " dmi_transactions=%" PRIu64 " htif_acks=%" PRIu64 "\n",
        status, cycles, options.reset_cycles, image.size(), final_tohost,
        terminal_pc != 0 ? terminal_pc : observed_pc(*verilator->rootp),
        chisa::rocket_fullchip::kExactRegisterTapCount,
        chisa::rocket_fullchip::kExactCombinationalTapCount,
        observer.comparisons(), observer.digest(),
        chisa::rocket_fullchip::dmi_host_transactions(),
        chisa::rocket_fullchip::dmi_host_console_acks());
    verilator->final();
    if (pass) return 0;
    return timed_out && options.allow_timeout ? 0 : 4;
  } catch (const std::exception& error) {
    std::fprintf(stderr, "Rocket W1 scalar differential error: %s\n",
                 error.what());
    return 2;
  }
}
