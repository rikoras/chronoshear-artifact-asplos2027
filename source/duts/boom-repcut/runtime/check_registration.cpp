// Registration coverage only; this is not a behavioral qualification.
#if !defined(CHISA_WIDE_MODEL)
#error "This runner must link the selected Wide implementation."
#endif
#include <cstdio>
#include "model_bindings.h"
#include "system_probe.h"
#include "generated/system_probe_registry.inc"

int main() {
  using namespace chisa::boom_system;
  register_model_streams();
  auto& bindings=ModelBindings::instance();
  bindings.finalize();
  std::size_t missing=0;
  for(std::size_t i=0;i<kSystemProbeManifestCount;++i) {
    const auto* key=kSystemProbeManifest[i].key;
    if(!bindings.find(key)) { std::fprintf(stderr,"UNBOUND %s\n",key);++missing; }
  }
  std::printf("MODEL_REGISTRATION required=%zu bound=%zu missing=%zu behavior=not-tested\n",
              kSystemProbeManifestCount,bindings.size(),missing);
  return missing || bindings.size()!=kSystemProbeManifestCount ? 1 : 0;
}
