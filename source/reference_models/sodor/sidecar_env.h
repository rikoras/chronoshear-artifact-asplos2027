#pragma once

#include <cstdint>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "sodor_guider.h"

namespace sodor::sidecar {

static constexpr uint32_t kMemBytes = 1u << 21;
static constexpr uint32_t kTohost = 0x1000u;

struct Memory {
  std::vector<uint8_t> bytes = std::vector<uint8_t>(kMemBytes, 0);

  uint32_t index(uint32_t address) const { return address & (kMemBytes - 1); }

  void clear() { std::memset(bytes.data(), 0, bytes.size()); }

  bool load_file(const char* path) {
    std::ifstream stream(path, std::ios::binary);
    if (!stream) return false;
    stream.seekg(0, std::ios::end);
    const std::streamoff size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    if (size < 0 || static_cast<uint64_t>(size) > bytes.size()) return false;
    stream.read(reinterpret_cast<char*>(bytes.data()), size);
    return stream.good() || stream.eof();
  }

  uint32_t read32(uint32_t address) const {
    const uint32_t first = index(address);
    if (first <= kMemBytes - sizeof(uint32_t)) {
      uint32_t value;
      std::memcpy(&value, bytes.data() + first, sizeof(value));
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      value = __builtin_bswap32(value);
#endif
      return value;
    }
    // Preserve the historical modulo-memory behavior for the three
    // addresses that would wrap at the end of the 2 MiB backing store.
    uint32_t value = 0;
    for (unsigned byte = 0; byte < 4; ++byte)
      value |= static_cast<uint32_t>(bytes[index(address + byte)]) << (8 * byte);
    return value;
  }

  void store(uint32_t address, uint32_t data, uint8_t type) {
    const unsigned count = type == MT_B ? 1 : type == MT_H ? 2 : 4;
    for (unsigned byte = 0; byte < count; ++byte)
      bytes[index(address + byte)] = static_cast<uint8_t>(data >> (8 * byte));
  }

  uint32_t tohost() const { return read32(kTohost); }
};

struct RegisterFile {
  uint32_t values[32]{};

  void clear() { std::memset(values, 0, sizeof(values)); }
  uint32_t read(uint8_t address) const { return address ? values[address & 31] : 0; }
  void write(uint8_t address, uint32_t value) {
    if (address) values[address & 31] = value;
  }
};

// One logical RTL cycle at the sidecar boundary. Inputs and outputs are both
// sampled before the clock edge; the model state is advanced afterwards.
// Keeping the complete boundary record lets the runtime harness apply the
// same valid-aware checks as the scalar lockstep validator.
struct CycleIO {
  uint64_t cycle = 0;
  Inputs in{};
  Outputs out{};
};

class SidecarEnv {
 public:
  bool init(const char* image_path) {
    guider_ = SodorGuider{};
    memory_.clear();
    regfile_.clear();
    cycle_ = 0;
    pass_cycle_ = 0;
    if (!memory_.load_file(image_path)) return false;

    Inputs reset_inputs;
    reset_inputs.reset = true;
    reset_inputs.imem_resp_valid = true;
    reset_inputs.dmem_resp_valid = true;
    for (unsigned reset_cycle = 0; reset_cycle < 5; ++reset_cycle)
      guider_.step(reset_inputs);
    return true;
  }

  // Advance exactly one cycle even after tohost becomes non-zero. A temporal
  // SIMD consumer always evaluates a complete 2W window, so the producer must
  // provide exact post-termination tail lanes rather than replaying zeros or
  // silently handing those lanes semantics from the microarchitecture model.
  void step_cycle(CycleIO& io) {
    const Outputs before = guider_.outputs();
    Inputs inputs;
    inputs.imem_req_ready = true;
    inputs.imem_resp_valid = true;
    inputs.imem_resp_data = memory_.read32(before.imem_req_addr);
    inputs.dmem_req_ready = true;
    inputs.dmem_resp_valid = true;
    // The RTL receives the raw word starting at the request address and
    // performs byte/half extension.
    // This matches gen_trace.cpp; using the model's typed load here would make
    // invalid payload bits differ even when architectural values agree.
    inputs.dmem_resp_data = memory_.read32(before.dmem_req_addr);
    inputs.rf_rs1_data = regfile_.read(before.rf_rs1_addr);
    inputs.rf_rs2_data = regfile_.read(before.rf_rs2_addr);

    io.cycle = ++cycle_;
    io.in = inputs;
    io.out = before;
    guider_.step(inputs);

    if (io.out.dmem_req_valid && io.out.dmem_req_fcn == M_XWR)
      memory_.store(io.out.dmem_req_addr, io.out.dmem_req_data,
                    io.out.dmem_req_typ);
    if (io.out.rf_wen)
      regfile_.write(io.out.rf_waddr, io.out.rf_wdata);
    regfile_.values[0] = 0;

    if (pass_cycle_ == 0 && memory_.tohost() != 0) pass_cycle_ = cycle_;
  }

  const SodorGuider& guider() const { return guider_; }
  const Memory& memory() const { return memory_; }
  const RegisterFile& regfile() const { return regfile_; }
  uint64_t cycle() const { return cycle_; }
  uint64_t pass_cycle() const { return pass_cycle_; }
  uint32_t tohost() const { return memory_.tohost(); }
  uint32_t pc() const { return guider_.dpath().if_reg_pc; }
  std::vector<std::string> sentinel_failures() const {
    return guider_.sentinel_failures();
  }

 private:
  SodorGuider guider_{};
  Memory memory_{};
  RegisterFile regfile_{};
  uint64_t cycle_ = 0;
  uint64_t pass_cycle_ = 0;
};

}  // namespace sodor::sidecar
