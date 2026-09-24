#pragma once

#include "isa.h"
#include <cstdint>

namespace chisa::rocket_model {
DecodedCtrl decode(uint32_t inst);
}
