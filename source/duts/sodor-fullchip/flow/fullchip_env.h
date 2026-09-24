#pragma once

#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "sidecar_env.h"

namespace sodor::fullchip {

struct HostInputs {
  bool valid = false;
  bool write = false;
  uint32_t addr = 0;
  uint32_t wdata = 0;
};

struct ChipOutputs {
  bool host_ready = true;
  uint32_t host_rdata = 0;
  bool success = false;
  uint32_t tohost = 0;
};

// One complete full-chip cycle.  Core-side memory/RF traffic is deliberately
// not a DUT input here: the integrated RTL and this independent environment
// each derive it from their own core state.
struct CycleIO {
  uint64_t cycle = 0;
  HostInputs in{};
  ChipOutputs out{};
};

struct MemoryReadAccess {
  uint32_t address = 0;
  uint8_t data = 0;
};

struct MemoryWriteAccess {
  bool enable = false;
  uint32_t address = 0;
  uint8_t data = 0;
};

// Words sampled once from the actual pre-edge memory.  The dense writer
// expands them directly into the existing byte-port oracle streams.
struct MemoryAccessSnapshot {
  uint32_t dmem_word = 0;
  uint32_t imem_word = 0;
  uint32_t host_word = 0;
  uint32_t tohost_word = 0;
  uint64_t core_write_control = 0;
  uint32_t core_write_data = 0;
};

// Exact lowered byte-memory port order, retained for diagnostics and the
// straightforward/sparse writers.  Disabled write payloads stay canonical 0.
struct MemoryAccessTrace : MemoryAccessSnapshot {
  std::array<MemoryReadAccess, 16> reads{};
  std::array<MemoryWriteAccess, 8> writes{};
};

class FullChipEnv {
 public:
  bool init(const char* image_path) {
    guider_ = SodorGuider{};
    memory_.clear();
    regfile_.clear();
    host_ = HostInputs{};
    cycle_ = 0;
    pass_cycle_ = 0;
    memory_access_cycle_ = UINT64_MAX;
    memory_access_trace_cycle_ = UINT64_MAX;
    if (!memory_.load_file(image_path)) return false;

    Inputs reset_inputs;
    reset_inputs.reset = true;
    reset_inputs.imem_req_ready = true;
    reset_inputs.imem_resp_valid = true;
    reset_inputs.dmem_req_ready = true;
    reset_inputs.dmem_resp_valid = true;
    for (unsigned reset_cycle = 0; reset_cycle < 5; ++reset_cycle)
      guider_.step(reset_inputs);
    outputs_ = guider_.outputs();
    return true;
  }

  uint8_t read8(uint32_t address) const {
    return memory_.bytes[memory_.index(address)];
  }

  static uint32_t extend_load(uint32_t raw, uint8_t type) {
    switch (type) {
      case MT_B:
        return static_cast<uint32_t>(static_cast<int32_t>(
            static_cast<int8_t>(raw & 0xff)));
      case MT_H:
        return static_cast<uint32_t>(static_cast<int32_t>(
            static_cast<int16_t>(raw & 0xffff)));
      case MT_BU: return raw & 0xff;
      case MT_HU: return raw & 0xffff;
      default: return raw;
    }
  }

  uint32_t raw_reg(uint8_t address) const {
    return regfile_.values[address & 31];
  }

  const MemoryAccessSnapshot& memory_access_snapshot() const {
    if (memory_access_cycle_ == cycle_) return memory_access_snapshot_;
    MemoryAccessSnapshot& snapshot = memory_access_snapshot_;
    const Outputs& core = outputs_;
    snapshot.dmem_word = memory_.read32(core.dmem_req_addr);
    snapshot.imem_word = memory_.read32(core.imem_req_addr);
    snapshot.host_word = memory_.read32(host_.addr);
    snapshot.tohost_word = memory_.read32(sidecar::kTohost);
    const bool core_store = !host_.valid && core.dmem_req_valid &&
                            core.dmem_req_fcn == M_XWR;
    snapshot.core_write_control = core_store
        ? (static_cast<uint64_t>(core.dmem_req_addr) |
           (static_cast<uint64_t>(core.dmem_req_typ) << 32) |
           (UINT64_C(1) << 40)) : 0;
    snapshot.core_write_data = core_store ? core.dmem_req_data : 0;
    memory_access_cycle_ = cycle_;
    return snapshot;
  }

  const MemoryAccessTrace& memory_access_trace() const {
    if (memory_access_trace_cycle_ == cycle_) return memory_access_cache_;
    MemoryAccessTrace& trace = memory_access_cache_;
    static_cast<MemoryAccessSnapshot&>(trace) = memory_access_snapshot();
    const Outputs& core = outputs_;
    const uint32_t addresses[] = {core.dmem_req_addr, core.imem_req_addr,
                                  host_.addr, sidecar::kTohost};
    const uint32_t words[] = {trace.dmem_word, trace.imem_word,
                              trace.host_word, trace.tohost_word};
    for (unsigned group = 0; group < 4; ++group) {
      for (unsigned byte = 0; byte < 4; ++byte) {
        const unsigned offset = 3 - byte;
        trace.reads[group * 4 + byte] = MemoryReadAccess{
            memory_.index(addresses[group] + offset),
            static_cast<uint8_t>(words[group] >> (8 * offset))};
      }
    }
    const bool core_store = !host_.valid && core.dmem_req_valid &&
                            core.dmem_req_fcn == M_XWR;
    const unsigned core_bytes = core.dmem_req_typ == MT_B ? 1u :
                                core.dmem_req_typ == MT_H ? 2u : 4u;
    const bool host_store = host_.valid && host_.write;
    for (unsigned byte = 0; byte < 4; ++byte) {
      const bool enabled = core_store && byte < core_bytes;
      trace.writes[byte] = MemoryWriteAccess{
          enabled, enabled ? memory_.index(core.dmem_req_addr + byte) : 0u,
          enabled ? static_cast<uint8_t>(core.dmem_req_data >> (8 * byte))
                  : uint8_t{0}};
      trace.writes[4 + byte] = MemoryWriteAccess{
          host_store, host_store ? memory_.index(host_.addr + byte) : 0u,
          host_store ? static_cast<uint8_t>(host_.wdata >> (8 * byte))
                     : uint8_t{0}};
    }
    memory_access_trace_cycle_ = cycle_;
    return trace;
  }

  void set_host(const HostInputs& host) {
    host_ = host;
    memory_access_cycle_ = UINT64_MAX;
    memory_access_trace_cycle_ = UINT64_MAX;
  }

  // Read ports observe the pre-edge image.  Writes then commit in the RTL's
  // priority order: any valid host transaction blocks the core store, and a
  // host write wins.  RF writes use the same read-old convention.
  void step_cycle(CycleIO& io) {
    // Keep the core boundary image once per cycle.  The oracle writer and
    // memory/RF environment consume the same pre-edge values; recomputing
    // SodorGuider::outputs() at every generated oracle expression was pure
    // producer overhead.  The pre-edge image stays in outputs_ until the
    // memory and register-file commits below have used it, so no copy is
    // taken and the post-edge image is written in place afterwards.
    const Outputs& before = outputs_;
    const MemoryAccessSnapshot& memory_access = memory_access_snapshot();

    io.cycle = ++cycle_;
    io.in = host_;
    io.out.host_ready = true;
    io.out.host_rdata = memory_access.host_word;
    io.out.tohost = memory_access.tohost_word;
    io.out.success = io.out.tohost == 1;

    Inputs inputs;
    inputs.imem_req_ready = true;
    inputs.imem_resp_valid = true;
    inputs.imem_resp_data = memory_access.imem_word;
    inputs.dmem_req_ready = true;
    inputs.dmem_resp_valid = true;
    // SodorFullChipMemory, unlike the old externally-fed Top fixture,
    // performs the architectural byte/half load extension inside RTL.
    inputs.dmem_resp_data = extend_load(memory_access.dmem_word,
                                        before.dmem_req_typ);
    inputs.rf_rs1_data = regfile_.read(before.rf_rs1_addr);
    inputs.rf_rs2_data = regfile_.read(before.rf_rs2_addr);
    guider_.step(inputs);

    if (!host_.valid && before.dmem_req_valid &&
        before.dmem_req_fcn == M_XWR) {
      memory_.store(before.dmem_req_addr, before.dmem_req_data,
                    before.dmem_req_typ);
    }
    if (host_.valid && host_.write)
      memory_.store(host_.addr, host_.wdata, MT_W);
    if (before.rf_wen)
      regfile_.write(before.rf_waddr, before.rf_wdata);
    regfile_.values[0] = 0;
    guider_.outputs_into(outputs_);

    if (pass_cycle_ == 0 && io.out.success) pass_cycle_ = cycle_;
  }

  const SodorGuider& guider() const { return guider_; }
  const Outputs& outputs() const { return outputs_; }
  const sidecar::Memory& memory() const { return memory_; }
  const sidecar::RegisterFile& regfile() const { return regfile_; }
  const HostInputs& host() const { return host_; }
  uint64_t cycle() const { return cycle_; }
  uint64_t pass_cycle() const { return pass_cycle_; }
  uint32_t tohost() const { return memory_.tohost(); }
  uint32_t pc() const { return guider_.dpath().if_reg_pc; }
  std::vector<std::string> sentinel_failures() const {
    return guider_.sentinel_failures();
  }

 private:
  SodorGuider guider_{};
  Outputs outputs_{};
  sidecar::Memory memory_{};
  sidecar::RegisterFile regfile_{};
  HostInputs host_{};
  uint64_t cycle_ = 0;
  uint64_t pass_cycle_ = 0;
  mutable MemoryAccessSnapshot memory_access_snapshot_{};
  mutable uint64_t memory_access_cycle_ = UINT64_MAX;
  mutable MemoryAccessTrace memory_access_cache_{};
  mutable uint64_t memory_access_trace_cycle_ = UINT64_MAX;
};

inline uint64_t hash_memory(const sidecar::Memory& memory) {
  uint64_t hash = 1469598103934665603ULL;
  for (uint8_t byte : memory.bytes) {
    hash ^= byte;
    hash *= 1099511628211ULL;
  }
  return hash;
}

}  // namespace sodor::fullchip
