#pragma once
#if defined(CHISA_WIDE_MODEL)
#include "../boom_model/wide/frontend.h"
namespace chisa::boom_system {
using FrontendState = boom_model::wide::FrontendState;
using FrontendEvaluation = boom_model::wide::FrontendEvaluation;
}
#else
#include "../boom_model/small/fe_frontend.h"
#endif
