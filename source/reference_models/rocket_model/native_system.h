#pragma once
// All-native DefaultConfig system. Execution mode is selected at construction:
// architectural mode omits inactive payload work; oracle mode preserves it and
// publishes the complete PRE state plus the explicitly phased comb streams.
#include <cstddef>
#include <cstdint>
#include "core.h"
#include "fpu.h"
#include "frontend.h"
#include "dcache.h"
#include "ptw.h"
#include "uncore/uncore.h"

namespace chisa::rocket_model {

enum class NativeExecutionMode { Architectural, Oracle };

struct NativeSystemInputs {
  bool reset = false;
  bool dmi_req_valid = false;
  uint8_t dmi_req_addr = 0;
  uint32_t dmi_req_data = 0;
  uint8_t dmi_req_op = 0;
  bool dmi_resp_ready = false;
};
struct NativeFloatWrite {
  uint8_t reg = 0;
  uint64_t value = 0; // architectural FLEN=64 IEEE/NaN-boxed value
};
struct NativeSystemOutputs {
  uint64_t cycle = 0;
  bool dmi_req_ready = false, dmi_resp_valid = false;
  uint32_t dmi_resp_data = 0;
  uint8_t dmi_resp_resp = 0;
  bool interrupt_debug = false, interrupt_msip = false, interrupt_mtip = false;
  bool interrupt_meip = false, interrupt_seip = false, core_reset = false;
  unsigned feedback_iterations = 0;
  CoreRetirement retirement{};
  uint8_t fp_write_count = 0;
  NativeFloatWrite fp_writes[2]{}; // physical write-port order: load, then pipe
};

class NativeSystem {
 public:
  explicit NativeSystem(uint32_t reset_vector = 0x10040, unsigned feedback_limit = 16,
                        NativeExecutionMode mode = NativeExecutionMode::Architectural);
  NativeSystem(const NativeSystem&) = delete;
  NativeSystem& operator=(const NativeSystem&) = delete;
  void attach_memory(uint8_t* backing, uint64_t bytes);
  NativeSystemOutputs step(const NativeSystemInputs& input, Image* oracle = nullptr);
  uint64_t read_integer_register(unsigned index) const;
  uint64_t read_float_register(unsigned index) const;
  hf::u128 read_float_recoded(unsigned index) const;
  uint64_t writeback_pc() const { return core_.wb_pc(); }
  uint64_t committed_pc() const { return core_.committed_pc(); }
  uint64_t cycles() const { return cycles_; }
  const Core& core() const { return core_; }
  const uncore::Uncore& uncore_state() const { return uncore_; }
  void set_uncore_evaluation_reuse(bool enabled) { uncore_.set_evaluation_reuse(enabled); }
  void set_ptw_idle_skip(bool enabled) { ptw_idle_skip_enabled_ = enabled; }
  // Coherent architectural read overlays resident D-cache data on DRAM.
  uint64_t read_memory_word(uint64_t address) const;
  // Loader/diagnostic backing access; running host traffic should use DMI.
  uint64_t read_dram_word(uint64_t address) const { return uncore_.read_memory_word(address); }
  void write_dram_word(uint64_t address, uint64_t value, uint8_t mask = 0xff) {
    uncore_.write_memory_word(address, value, mask);
  }
  bool architectural_mode() const { return mode_ == NativeExecutionMode::Architectural; }
  bool publishes_oracles() const { return mode_ == NativeExecutionMode::Oracle; }

 private:
  uint32_t reset_vector_;
  unsigned feedback_limit_;
  NativeExecutionMode mode_;
  bool ptw_idle_skip_enabled_ = true;
  Image image_{};
  uint64_t cycles_ = 0;
  Core core_;
  Fpu fpu_;
  Frontend frontend_;
  Dcache dcache_;
  Ptw ptw_;
  uncore::Uncore uncore_;
  PmpSet pmp_{};
  CoreWires core_wires_{};
  FpuWires fpu_wires_{};
  FrontendWires frontend_wires_{};
  DcacheWires dcache_wires_{};
  PtwWires ptw_wires_{};
  RocketFullSystemInputs core_input_{};
  RocketFullSystemOutputs core_output_{};
  FpuIn fpu_input_{};
  FrontendIn frontend_input_{};
  DcacheIn dcache_input_{};
  PtwIn ptw_input_{};
  uncore::UncoreIn uncore_input_{};
  uncore::UncoreOut uncore_output_{};
  // HellaCacheArbiter requestor 0 is PTW; requestor 1 is Core.
  uint8_t s1_owner_ = 0, s2_owner_ = 0;
  void capture_pmp();
  void evaluate_fpu(bool reset);
  void evaluate_memory(bool reset, const PtwWires& ptw, const uncore::UncoreOut& fabric);
  void evaluate_ptw(bool reset);
  void evaluate_uncore(const NativeSystemInputs& input);
  RocketFullSystemInputs feedback(bool reset) const;
};
}  // namespace chisa::rocket_model
