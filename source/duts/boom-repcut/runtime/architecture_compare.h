#pragma once
#include <cstdint>
#include <deque>
#include <stdexcept>
#include <string>
#include "../../../reference_models/boom_model/common/architectural_state.h"

namespace chisa::boom_repcut {

// Each side runs its own host/debug transport. Timing and debug polling may
// differ; compare the target's ordered retirement stream, never a same-cycle
// pairing. Neither queue supplies values to either executing machine.
class ArchitectureComparison {
 public:
  using Event = boom_model::RetirementEvent;
  ArchitectureComparison(std::uint64_t entry, std::uint64_t tohost,
                         std::uint64_t initial_tohost, std::size_t max_pending = 65536)
      : entry_(entry), tohost_(tohost), max_pending_(max_pending) {
    if (tohost == 0) throw std::invalid_argument("architecture comparison requires the ELF tohost symbol");
    const unsigned known_zero = (((initial_tohost >> 48u) & 255u) == 0 ? 1u : 0u) |
                                (((initial_tohost >> 56u) & 255u) == 0 ? 2u : 0u);
    model_.header_known_zero = rtl_.header_known_zero = known_zero;
  }

  void push_model(const Event& event) { push(model_, event); match(); }
  void push_rtl(const Event& event) { push(rtl_, event); match(); }
  std::uint64_t compared() const { return compared_; }
  std::uint64_t compared_stores() const { return compared_stores_; }
  std::uint64_t model_retired() const { return model_.committed.state().retired; }
  std::uint64_t rtl_retired() const { return rtl_.committed.state().retired; }
  std::uint64_t model_debug_retired() const { return model_.debug_retired; }
  std::uint64_t rtl_debug_retired() const { return rtl_.debug_retired; }
  std::size_t model_pending() const { return model_.pending.size(); }
  std::size_t rtl_pending() const { return rtl_.pending.size(); }
  bool model_started() const { return model_.started; }
  bool rtl_started() const { return rtl_.started; }
  bool model_finished() const { return model_.finished; }
  bool rtl_finished() const { return rtl_.finished; }

  // Call only after independently establishing both complete program exits.
  // It deliberately refuses an empty, partial, or one-sided instruction trace.
  void finish() const {
    if (!model_.started || !rtl_.started || compared_ == 0)
      throw std::runtime_error("architecture comparison has no complete target retirement coverage");
    if (!model_.finished || !rtl_.finished)
      throw std::runtime_error("architecture comparison did not reach both target exit stores");
    if (!model_.pending.empty() || !rtl_.pending.empty())
      throw std::runtime_error("architecture comparison ended with unmatched retirements");
    const auto& model = model_.committed.state();
    const auto& rtl = rtl_.committed.state();
    if (model.retired != rtl.retired || model.x_written_mask != rtl.x_written_mask ||
        model.f_written_mask != rtl.f_written_mask)
      throw std::runtime_error("architecture committed register coverage differs");
    for (unsigned reg = 0; reg < 32; ++reg) {
      if (((model.x_written_mask >> reg) & 1u) && model.x[reg] != rtl.x[reg])
        throw std::runtime_error("architecture final integer register mismatch");
      if (((model.f_written_mask >> reg) & 1u) && model.f[reg] != rtl.f[reg])
        throw std::runtime_error("architecture final floating register mismatch");
    }
  }

 private:
  struct Side {
    bool started = false, finished = false;
    unsigned header_known_zero = 0;
    std::uint64_t last_source_sequence = 0, debug_retired = 0;
    boom_model::ArchitecturalRetirement committed;
    std::deque<Event> pending;
  } model_, rtl_;
  std::uint64_t entry_, tohost_, compared_ = 0, compared_stores_ = 0;
  std::size_t max_pending_;

  void push(Side& side, const Event& event) {
    if (!event.valid) return;
    if (event.sequence == 0)
      throw std::runtime_error("architecture source retirement has no sequence");
    if (event.sequence == side.last_source_sequence) return;  // no new Core::step
    if (event.sequence < side.last_source_sequence)
      throw std::runtime_error("architecture source retirement sequence moved backwards");
    side.last_source_sequence = event.sequence;
    if (event.debug_mode) { ++side.debug_retired; return; }
    if (side.finished) return;  // HTIF completion polling has a variable spin suffix
    if (event.memory_write) {
      if (event.memory_size > 3) throw std::runtime_error("invalid architectural store size");
      const unsigned bytes = 1u << event.memory_size;
      const std::uint64_t mask = bytes == 8 ? UINT64_MAX : (UINT64_C(1) << (bytes * 8u)) - 1;
      if (event.memory_value & ~mask) throw std::runtime_error("architectural store value is not byte-normalized");
      // HTIF housekeeping can clear tohost between target instructions. A
      // known zero header byte stays zero across those clears; a nonzero
      // target write loses that knowledge until the target writes zero again.
      // This accepts SW/SB exits without treating their absent upper bytes as
      // proof that an earlier console command's device/command was zero.
      for (unsigned byte = 0; byte < bytes; ++byte) {
        const auto address = event.memory_address + byte;
        if (address < tohost_ + 6 || address > tohost_ + 7) continue;
        const unsigned bit = 1u << (address - tohost_ - 6);
        if (((event.memory_value >> (byte * 8u)) & 255u) == 0) side.header_known_zero |= bit;
        else side.header_known_zero &= ~bit;
      }
    }
    if (!side.started) {
      if (event.pc != entry_) return;
      side.started = true;
    }
    if (event.writes_x && event.writes_f)
      throw std::runtime_error("architecture event writes both register files");
    side.committed.retire(event);
    side.pending.push_back(event);
    side.finished = event.memory_write && event.memory_address == tohost_ &&
                    (event.memory_value & 1u) != 0 && side.header_known_zero == 3;
    if (side.pending.size() > max_pending_)
      throw std::runtime_error("architecture retirement skew exceeded the bounded queue");
  }
  void match() {
    while (!model_.pending.empty() && !rtl_.pending.empty()) {
      const auto& a = model_.pending.front();
      const auto& b = rtl_.pending.front();
      const char* field = nullptr;
      if (a.pc != b.pc) field = "pc";
      else if (a.is_rvc != b.is_rvc || a.instruction != b.instruction) field = "instruction";
      else if (a.writes_x != b.writes_x || a.writes_f != b.writes_f) field = "destination-kind";
      else if ((a.writes_x || a.writes_f) && a.rd != b.rd) field = "destination-register";
      else if ((a.writes_x || a.writes_f) && a.value != b.value) field = "writeback-value";
      else if (a.fflags != b.fflags) field = "fflags";
      else if (a.memory_write != b.memory_write) field = "memory-write";
      else if (a.memory_write && (a.memory_address != b.memory_address ||
               a.memory_value != b.memory_value || a.memory_size != b.memory_size)) field = "store";
      if (field) {
        throw std::runtime_error(std::string("architecture retirement mismatch field=") + field +
            " target_sequence=" + std::to_string(compared_ + 1) +
            " model_cycle=" + std::to_string(a.cycle) + " rtl_cycle=" + std::to_string(b.cycle) +
            " model_pc=" + std::to_string(a.pc) + " rtl_pc=" + std::to_string(b.pc) +
            " model_instruction=" + std::to_string(a.instruction) +
            " rtl_instruction=" + std::to_string(b.instruction) +
            " model_value=" + std::to_string(a.value) + " rtl_value=" + std::to_string(b.value) +
            " model_fflags=" + std::to_string(a.fflags) + " rtl_fflags=" + std::to_string(b.fflags));
      }
      compared_stores_ += a.memory_write;
      model_.pending.pop_front(); rtl_.pending.pop_front(); ++compared_;
    }
  }
};
}  // namespace chisa::boom_repcut
