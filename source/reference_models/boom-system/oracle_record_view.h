#pragma once

// Explicit selection: the compact Small Image is not a layout for Large.
// Both views below address the selected OracleRecord's bytes directly.
#if defined(BOOM_GUIDER_CFG_SMALLBOOM_RC) && defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#error "select exactly one BOOM record view configuration"
#elif defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
#include "generated/oracle_record_view_large.h"
namespace chisa::boom_system { namespace selected_record_view = record_view::large; }
#elif defined(BOOM_GUIDER_CFG_SMALLBOOM_RC)
#include "generated/oracle_record_view_small.h"
namespace chisa::boom_system { namespace selected_record_view = record_view::small; }
#else
#error "BOOM record views require an explicit Small or Large configuration"
#endif
