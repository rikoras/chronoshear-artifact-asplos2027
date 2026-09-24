#pragma once
#include <array>
#include <cinttypes>
#include <cstdio>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "architecture_program.h"
#include "consumer_architecture_capture.h"
#include "retirement_observer.h"
#include "../../../reference_models/boom_model/common/architectural_state.h"
#include "../../../reference_models/common/softfloat_fp.h"

namespace chisa::boom_repcut {

// The two endpoints observe independent machines. Only finish() compares them;
// no expected value is ever fed into the consumer or its capture frame.
class ArchitecturalEndpoint {
 public:
  explicit ArchitecturalEndpoint(const ArchitecturalProgram& program) : program_(program) {
    known_header_zero_ = (((program.initial_tohost >> 48u) & 255u) == 0 ? 1u : 0u) |
                         (((program.initial_tohost >> 56u) & 255u) == 0 ? 2u : 0u);
  }
  void observe(const boom_model::RetirementEvent& event) {
    if (!event.valid || event.debug_mode || finished_ || event.sequence == last_sequence_) return;
    last_sequence_ = event.sequence;
    if (!started_) {
      if (event.pc != program_.entry) return;
      started_ = true;
    }
    state_.retire(event);
    if (event.memory_write) {
      if (event.memory_size > 3) throw std::runtime_error("architectural store size out of range");
      for (unsigned i = 0; i < (1u << event.memory_size); ++i) {
        const auto address = event.memory_address + i;
        const auto value = static_cast<std::uint8_t>(event.memory_value >> (8u * i));
        memory_[address] = value;
        if (address == program_.tohost + 6 || address == program_.tohost + 7) {
          const unsigned bit = 1u << (address - program_.tohost - 6);
          if (value == 0) known_header_zero_ |= bit; else known_header_zero_ &= ~bit;
        }
      }
      ++stores_;
      if (event.memory_address == program_.tohost && (event.memory_value & 1u) && known_header_zero_ == 3) {
        finished_ = true;
        exit_ = event.memory_value >> 1;
      }
    }
  }
  void compare(const ArchitecturalEndpoint& expected) const {
    if (!started_ || !expected.started_ || !finished_ || !expected.finished_)
      throw std::runtime_error("architectural check did not reach both target exit stores");
    if (exit_ || expected.exit_) throw std::runtime_error("architectural target reported failure");
    if (retired() != expected.retired() || stores_ != expected.stores_)
      throw std::runtime_error("architectural event count mismatch: RTL retired/stores=" +
          std::to_string(retired()) + "/" + std::to_string(stores_) + " model=" +
          std::to_string(expected.retired()) + "/" + std::to_string(expected.stores_));
    const auto& actual = state_.state(); const auto& reference = expected.state_.state();
    if (actual.last_pc != reference.last_pc)
      throw std::runtime_error("consumer final architectural PC mismatch");
    if (actual.x_written_mask != reference.x_written_mask || actual.f_written_mask != reference.f_written_mask)
      throw std::runtime_error("consumer architectural register coverage differs");
    for (unsigned reg = 0; reg < 32; ++reg) {
      if (((reference.x_written_mask >> reg) & 1u) && actual.x[reg] != reference.x[reg])
        throw std::runtime_error("consumer final x" + std::to_string(reg) + " mismatch: RTL=" +
                                 std::to_string(actual.x[reg]) + " model=" + std::to_string(reference.x[reg]));
      if (((reference.f_written_mask >> reg) & 1u) && actual.f[reg] != reference.f[reg])
        throw std::runtime_error("consumer final f" + std::to_string(reg) + " mismatch");
    }
    if (memory_ != expected.memory_)
      throw std::runtime_error("consumer final committed-store memory footprint mismatch");
  }
  std::uint64_t retired() const { return state_.state().retired; }
  std::uint64_t stores() const { return stores_; }
  std::size_t memory_bytes() const { return memory_.size(); }
  bool finished() const { return finished_; }
 private:
  ArchitecturalProgram program_;
  boom_model::ArchitecturalRetirement state_;
  std::unordered_map<std::uint64_t, std::uint8_t> memory_;
  std::uint64_t last_sequence_ = 0, stores_ = 0, exit_ = 0;
  unsigned known_header_zero_ = 0;
  bool started_ = false, finished_ = false;
};

class ConsumerArchitectureCheck {
 public:
  explicit ConsumerArchitectureCheck(const char* elf)
      : program_(read_architectural_program(elf)), model_(program_), consumer_(program_) {}
  template <class Dut>
  void initialize(const Dut& dut) {
    initialize(dut, dut);
  }
  template <class Dut>
  void initialize(const Dut& integer_dut, const Dut& floating_dut) {
    const auto& core = integer_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile.core;
    const auto& floating_core = floating_dut.ldut.tile_prci_domain.tile_reset_domain.boom_tile.core;
    static_assert(std::extent_v<decltype(core.iregfile.regfile)> == consumer_arch::kIntegerRegisters &&
                  std::extent_v<decltype(core.fp_pipeline.fregfile.regfile)> == consumer_arch::kFloatingRegisters,
                  "consumer checker requires the selected BOOM PRF geometry");
    for (unsigned i = 0; i < integer_.size(); ++i)
      integer_[i] = consumer_arch::word(core.iregfile.regfile[i]).lo;
    for (unsigned i = 0; i < floating_.size(); ++i)
      floating_[i] = consumer_arch::word(floating_core.fp_pipeline.fregfile.regfile[i]);
    consumer_arch::frame.enabled = true;
  }
  void observe_model(const boom_model::RetirementEvent& event);
  void begin_half() { consumer_arch::frame.begin_half(); }
  void consume_half(bool forward, std::uint64_t first, bool reset) {
    consume_half(forward, first, reset, consumer_arch::frame);
  }
  void consume_half(bool forward, std::uint64_t first, bool reset,
                    const consumer_arch::Frame& captured);
  void finish() const {
    std::exception_ptr failure;
    try {
      consumer_.compare(model_);
      std::fprintf(stderr, "CONSUMER_ENDPOINT status=pass\n");
    } catch (const std::exception& error) {
      failure = std::current_exception();
      std::fprintf(stderr, "CONSUMER_ENDPOINT status=failed reason=%s\n", error.what());
    }
    try { ordered_.finish(); } catch (...) { if (!failure) failure = std::current_exception(); }
    std::printf("CONSUMER_ARCHITECTURE status=%s model_retired=%" PRIu64
                " rtl_retired=%" PRIu64 " model_stores=%" PRIu64 " rtl_stores=%" PRIu64
                " memory_bytes=%zu register_scope=written-since-entry memory_scope=committed-store-footprint\n",
                failure ? "failed" : "pass", model_.retired(), consumer_.retired(), model_.stores(), consumer_.stores(), consumer_.memory_bytes());
    if (failure) std::rethrow_exception(failure);
  }
 private:
  ArchitecturalProgram program_;
  ArchitecturalEndpoint model_, consumer_;
  std::array<std::uint64_t, consumer_arch::kIntegerRegisters> integer_{};
  std::array<consumer_arch::Word, consumer_arch::kFloatingRegisters> floating_{};
  std::array<bool, consumer_arch::kRobRows * consumer_arch::kCommitWidth> debug_{};
  std::uint64_t sequence_ = 0;
  RetirementObserver ordered_;
};
} // namespace chisa::boom_repcut
