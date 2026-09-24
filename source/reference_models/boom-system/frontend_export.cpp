// The frontend's contract streams written into the model image (see
// scripts/gen_frontend_export.py); one function, called after commit().
#include <cstdio>
#include <cstdlib>
#include <cstring>

#if defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#include "frontend_state.h"

namespace chisa::boom_system {
#include "generated/frontend_export.inc"
}  // namespace chisa::boom_system
#endif  // BOOM_GUIDER_CFG_LARGEBOOM_RC
