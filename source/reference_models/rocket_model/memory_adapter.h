// Complete Frontend/DCache module joins. Input bundles come only from the
// producer's independently evolving cold circuit. Every evaluation reads PRE
// state, and the final captured evaluation commits once at the common edge.
#pragma once
#include <stdexcept>
#include "frontend.h"
#include "dcache.h"
#ifndef ROCKET_MODEL_MEMORY_SEAM_HEADER
#define ROCKET_MODEL_MEMORY_SEAM_HEADER "generated/memory_seam.h"
#endif
#include ROCKET_MODEL_MEMORY_SEAM_HEADER

namespace chisa::rocket_model {

struct FrontendEvaluation {
  FrontendSeamInputs raw_inputs{};
  PmpSet pmp{};
  FrontendIn inputs{};
  FrontendWires wires{};
  bool prepared = false;
  FrontendEvaluation() = default;
  // inputs.pmp points into this cycle. Moving/copying a prepared evaluation
  // would silently change the input seen by commit.
  FrontendEvaluation(const FrontendEvaluation&) = delete;
  FrontendEvaluation& operator=(const FrontendEvaluation&) = delete;
};

struct DcacheEvaluation {
  DcacheSeamInputs raw_inputs{};
  PmpSet pmp{};
  DcacheIn inputs{};
  DcacheWires wires{};
  bool prepared = false;
  DcacheEvaluation() = default;
  DcacheEvaluation(const DcacheEvaluation&) = delete;
  DcacheEvaluation& operator=(const DcacheEvaluation&) = delete;
};

class FrontendAdapter {
 public:
  void set_architectural_mode(bool enabled) { model_.set_architectural_mode(enabled); }
  explicit FrontendAdapter(Frontend& model) : model_(model) {
    // Match scalar cold construction followed by memset(0). RTL RegInit
    // values take effect on real reset edges, not before cycle zero.
    model_ = Frontend{};
    model_.icache.lfsr_ = 0;
    model_.s2_replay_reg_ = false;
  }
  void evaluate(const FrontendSeamInputs& raw, FrontendEvaluation& cycle) const {
    cycle.prepared = false;
    cycle.raw_inputs = raw;
    cycle.inputs = frontend_native_inputs(cycle.raw_inputs, cycle.pmp);
    cycle.inputs.exact_seam = !model_.architectural_mode();
    model_.evaluate(cycle.inputs, cycle.wires);
    cycle.prepared = true;
  }
  FrontendSeamOutputs outputs(const FrontendEvaluation& cycle) const {
    require_prepared(cycle);
    return frontend_native_outputs(model_, cycle.inputs, cycle.wires, cycle.raw_inputs);
  }
  void commit(FrontendEvaluation& cycle) {
    require_prepared(cycle);
    model_.commit(cycle.inputs, cycle.wires);
    cycle.prepared = false;
  }
  template <class Image> void export_image(Image& image) const { model_.export_image(image); }
 private:
  static void require_prepared(const FrontendEvaluation& cycle) {
    if (!cycle.prepared) throw std::logic_error("Frontend cycle was not evaluated or already committed");
  }
  Frontend& model_;
};

class DcacheAdapter {
 public:
  void set_architectural_mode(bool enabled) { model_.set_architectural_mode(enabled); }
  explicit DcacheAdapter(Dcache& model) : model_(model) {
    model_ = Dcache{};
    model_.lfsr_ = 0;
    model_.flushCounter_ = 0;
  }
  void evaluate(const DcacheSeamInputs& raw, DcacheEvaluation& cycle) const {
    cycle.prepared = false;
    cycle.raw_inputs = raw;
    cycle.inputs = dcache_native_inputs(cycle.raw_inputs, cycle.pmp);
    cycle.inputs.exact_seam = !model_.architectural_mode();
    model_.evaluate(cycle.inputs, cycle.wires);
    cycle.prepared = true;
  }
  DcacheSeamOutputs outputs(const DcacheEvaluation& cycle) const {
    require_prepared(cycle);
    return dcache_native_outputs(model_, cycle.inputs, cycle.wires, cycle.raw_inputs);
  }
  void commit(DcacheEvaluation& cycle) {
    require_prepared(cycle);
    model_.commit(cycle.inputs, cycle.wires);
    cycle.prepared = false;
  }
  template <class Image> void export_image(Image& image) const { model_.export_image(image); }
 private:
  static void require_prepared(const DcacheEvaluation& cycle) {
    if (!cycle.prepared) throw std::logic_error("DCache cycle was not evaluated or already committed");
  }
  Dcache& model_;
};
}  // namespace chisa::rocket_model
