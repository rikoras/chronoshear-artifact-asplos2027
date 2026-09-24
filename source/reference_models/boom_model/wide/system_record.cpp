#include "core.h"
#include "record_bits.h"
#include "../../boom-system/model_bindings.h"
#include <array>
#include <cstring>

namespace chisa::boom_model::wide {
contract::Image& system_record() {
  static_assert(sizeof(contract::Image)==boom_system::kOracleRecordPaddedBytes,
                "Large model and transport must use the same final record");
  static_assert(contract::kLanes==boom_system::kOracleRecordLanes);
  return *reinterpret_cast<contract::Image*>(boom_system::ModelBindings::instance().record().bytes);
}
namespace {
// Same one-time register initialization as Small's SystemGuider constructor.
// The first publication precedes the first edge and therefore contains zero.
std::array<unsigned char, contract::kRegBytes> boot_registers;
bool boot_pending = false;
}
void prepare_cycle_zero() {
  auto& r = system_record().r;
  std::memcpy(boot_registers.data(), &r, sizeof(r));
  std::memset(&r, 0, sizeof(r));
  boot_pending = true;
}
void restore_cycle_zero() {
  if (!boot_pending) return;
  std::memcpy(&system_record().r, boot_registers.data(), boot_registers.size());
  boot_pending = false;
}
}  // namespace chisa::boom_model::wide
