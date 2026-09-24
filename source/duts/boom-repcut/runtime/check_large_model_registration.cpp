// Build/registration gate only. No RTL or program cycles are compared here.
#if !defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#error "this gate requires the Large BOOM configuration"
#endif
#include <cstdio>
#include <cstdlib>

#include "model_bindings.h"
#include "system_probe.h"

int main() {
  using namespace chisa::boom_system;
  static_assert(kOracleRecordLanes == 3997);
  setenv("SYSMODEL_PHASE_STRICT", "1", 1);
  setenv("SYSMODEL_BINDING_AUDIT", "1", 1);
  register_model_streams();
  const auto& probes = SystemProbes::instance();
  const auto& bindings = ModelBindings::instance();
  for (const auto& key : bindings.unclaimed())
    std::fprintf(stderr, "[EXTRA] %s\n", key.c_str());
  const bool complete = probes.registered_stream_count() == kOracleRecordLanes &&
      probes.modeled_stream_count() == kOracleRecordLanes &&
      probes.profile_assumption_stream_count() == 0 && bindings.unclaimed().empty();
  std::printf("LARGE_MODEL_REGISTRATION manifest=%zu modeled=%zu profile=%zu extra=%zu "
              "compared_cycles=0 exact=%u\n",
              probes.registered_stream_count(), probes.modeled_stream_count(),
              probes.profile_assumption_stream_count(), bindings.unclaimed().size(),
              static_cast<unsigned>(complete));
  return complete ? 0 : 2;
}
