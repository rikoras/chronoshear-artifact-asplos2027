#pragma once

#include "extmodule_adapters.h"
#include "system_guider.h"

namespace chisa::boom_repcut {

/** Exact model-side DTM used by the complete debug-module model.
  *
  * The owner supplies a DTM instance distinct from the one driving the DUT.
  * SystemGuider advances it for the full run only with independently
  * predicted DMI feedback.  The historical class name is retained so older
  * runners do not need an API-only rename. */
template <typename Dtm>
class FesvrDebugBootstrap final
    : public boom_system::DebugBootstrapTransport {
 public:
  explicit FesvrDebugBootstrap(Dtm& dtm) : adapter_(dtm) {}

  bool at_idle_nop_boundary() const {
    return adapter_.at_idle_nop_boundary();
  }
  void begin_dmi_quiesce() { adapter_.begin_dmi_quiesce(); }
  bool dmi_quiescing() const { return adapter_.dmi_quiescing(); }
  bool dmi_quiesced() const { return adapter_.dmi_quiesced(); }

  boom_system::DebugBootstrapOutputs outputs() const override {
    const auto& outputs = adapter_.outputs();
    return boom_system::DebugBootstrapOutputs{
        outputs.req_valid, outputs.req_addr, outputs.req_op, outputs.req_data,
        outputs.resp_ready, outputs.exit};
  }

  void advance(
      bool reset,
      const boom_system::DebugBootstrapFeedback& feedback) override {
    adapter_.advance(
        reset,
        DmiFeedback{feedback.req_ready, feedback.resp_valid, feedback.resp,
                    feedback.data});
  }

 private:
  FesvrDtmAdapter<Dtm> adapter_;
};

}  // namespace chisa::boom_repcut
