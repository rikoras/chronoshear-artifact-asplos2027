#pragma once
#include <cstdint>

namespace chisa::boom_system {

/** Where in the model's step a sampling batch runs.  PreStep batches run
  * at the cycle start (cold wire oracles refreshed by the fabric
  * evaluation); the others run right after the component they read has
  * committed, while its state is still in L1, and therefore produce the
  * NEXT cycle's pre-edge values into the record. */
enum class SamplePlacement : std::uint8_t { PreStep, Core, Frontend, Memory, End };

}  // namespace chisa::boom_system
