// SYSMODEL_DEV_PROBES: unconverged candidates.
//
//  - s2_tlb_resp_ae_inst: raw-vs-gated TLB payload registration.
//  - ras_REG_1: twelve mismatches in 50k; update-enable timing.
//  - f3_bpd_resp_ram_preds_3_predicted_pc_bits: payload source differs.
//  - rob_state: three transient mismatches around the debug-interrupt flip.

#include <cstdlib>
#include <string>

#include "model_bindings.h"
#include "system_guider.h"

namespace chisa::boom_system {

namespace {

bool dev_probes_enabled() {
  const char* env = std::getenv("SYSMODEL_DEV_PROBES");
  return env != nullptr && env[0] == '1';
}

uint64_t sample_red_0(const SystemGuider& m) {
  return static_cast<uint64_t>(m.frontend().f0_f2_for_diagnostic().s2().tlb.xcpt_ae_if);
}
uint64_t sample_red_1(const SystemGuider& m) {
  return static_cast<uint64_t>(m.frontend().ras_for_diagnostic().write_addr_reg());
}
uint64_t sample_red_2(const SystemGuider& m) {
  return static_cast<uint64_t>(m.frontend().f3_queues_for_diagnostic().bpd_payload().preds[3].predicted_pc);
}
uint64_t sample_red_3(const SystemGuider& m) {

  return static_cast<uint64_t>(m.backend().core().rob_state());

}

void register_remainders() {
  ModelBindings& b = ModelBindings::instance();
  const std::string fe = "ldut_tile_prci_domain_tile_reset_domain_boom_tile_frontend_";
  const std::string co = "ldut_tile_prci_domain_tile_reset_domain_boom_tile_core_";
  b.bind_sampled((fe+"s2_tlb_resp_ae_inst").c_str(), sample_red_0);
  b.bind_sampled((fe+"ras_REG_1").c_str(), sample_red_1);
  b.bind_sampled((fe+"f3_bpd_resp_ram_preds_3_predicted_pc_bits").c_str(),
                 sample_red_2);
  b.bind_sampled((co+"rob_rob_state").c_str(), sample_red_3);
}

}  // namespace

void register_core_bringup_probes_if_enabled() {
  if (dev_probes_enabled()) register_remainders();
}

}  // namespace chisa::boom_system
