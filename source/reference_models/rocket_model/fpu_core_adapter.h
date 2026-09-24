// Checked adapter for the CP-inactive FPU core interface. The specialized
// 41-leaf seam is complete; the retained-RTL audit profile deliberately leaves
// its three CP response outputs unavailable. Never mix generated profiles.
#pragma once
#include <stdexcept>

#include "fpu.h"
#ifndef ROCKET_MODEL_FPU_SEAM_HEADER
#define ROCKET_MODEL_FPU_SEAM_HEADER "generated/fpu_seam.h"
#endif
#include ROCKET_MODEL_FPU_SEAM_HEADER

namespace chisa::rocket_model {

struct FpuEvaluation {
  FpuIn inputs{};
  FpuWires wires{};
  bool state_ready = false;
  bool inputs_ready = false;
};

class FpuCoreAdapter {
 public:
  explicit FpuCoreAdapter(Fpu& model) : model_(model) {}

  void evaluate_state(FpuEvaluation& cycle) const {
    model_.evaluate_state(cycle.wires);
    cycle.state_ready = true;
    cycle.inputs_ready = false;
  }

  void evaluate_inputs(const FpuSeamInputs& input, FpuEvaluation& cycle) const {
    if (!cycle.state_ready) throw std::logic_error("FPU inputs require prepared state outputs");
    // Clear readiness before validation: a rejected updated input must not
    // leave the previous command available for a subsequent commit.
    cycle.inputs_ready = false;
    cycle.inputs = fpu_native_inputs(input);
    model_.evaluate_inputs(cycle.inputs, cycle.wires);
    cycle.inputs_ready = true;
  }

  FpuSeamOutputs outputs(const FpuEvaluation& cycle) const {
    require_prepared(cycle);
    return fpu_native_outputs(model_, cycle.wires);
  }

  void commit(FpuEvaluation& cycle) {
    require_prepared(cycle);
    model_.commit(cycle.inputs, cycle.wires);
    cycle.state_ready = cycle.inputs_ready = false;
  }

  // Call before the common edge for register oracles, and after the final
  // common edge for architectural convergence. No RTL state is sampled.
  template <class Image> void export_image(Image& image) const { model_.export_image(image); }
  hf::u128 rf(unsigned index) const {
    if (index >= 32) throw std::out_of_range("FPU register index");
    return model_.regfile_[index] & hf::mask128(65);
  }

 private:
  static void require_prepared(const FpuEvaluation& cycle) {
    if (!cycle.state_ready || !cycle.inputs_ready) throw std::logic_error("FPU cycle is not prepared or was already committed");
  }
  Fpu& model_;
};

}  // namespace chisa::rocket_model
