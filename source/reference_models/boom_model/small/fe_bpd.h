#pragma once
#include "../common/predictor_bank.h"
#include "generated/image.h"

namespace chisa::boom_model::fe {
class Bpd : public PredictorBank {
 public:
  explicit Bpd(Image& image) : PredictorBank(image.r.frontendBpd,image.c.frontendBpd) {}
};
}  // namespace chisa::boom_model::fe
