#pragma once
// Lightweight first-divergence checker for model/component boundaries.
//
// A TileLink/Decoupled `valid` is not a universal payload care mask.  Some
// downstream RTL registers payload bits without consulting valid; those bits
// are sampled payloads and must be compared every cycle.  Call sites declare
// that sampling rule explicitly so the diagnostic cannot quietly discard the
// exact class of mismatch it is meant to localize.

#include <cstdint>
#include <initializer_list>
#include <optional>

namespace chisa::boom_repcut {

enum class SeamRule : std::uint8_t {
  kEvent,
  kValidPayload,
  kSampledPayload,
};

inline const char* seam_rule_name(SeamRule rule) {
  switch (rule) {
    case SeamRule::kEvent: return "event";
    case SeamRule::kValidPayload: return "valid-payload";
    case SeamRule::kSampledPayload: return "sampled-payload";
  }
  return "unknown";
}

struct SeamSignal {
  const char* name = "";
  std::uint64_t rtl = 0;
  std::uint64_t model = 0;
  std::uint64_t mask = UINT64_MAX;
  SeamRule rule = SeamRule::kEvent;
  bool compare = true;

  static constexpr std::uint64_t width_mask(unsigned width) {
    return width >= 64 ? UINT64_MAX
                       : width == 0 ? UINT64_C(0)
                                    : (UINT64_C(1) << width) - 1;
  }

  static SeamSignal event(const char* name, std::uint64_t rtl,
                          std::uint64_t model, unsigned width = 1) {
    return SeamSignal{name, rtl, model, width_mask(width),
                      SeamRule::kEvent, true};
  }

  static SeamSignal valid_payload(const char* name, std::uint64_t rtl,
                                  std::uint64_t model, unsigned width,
                                  bool rtl_valid, bool model_valid) {
    return SeamSignal{name, rtl, model, width_mask(width),
                      SeamRule::kValidPayload, rtl_valid && model_valid};
  }

  static SeamSignal sampled_payload(const char* name, std::uint64_t rtl,
                                    std::uint64_t model, unsigned width) {
    return SeamSignal{name, rtl, model, width_mask(width),
                      SeamRule::kSampledPayload, true};
  }
};

struct SeamMismatch {
  const char* name = "";
  std::uint64_t rtl = 0;
  std::uint64_t model = 0;
  std::uint64_t xor_value = 0;
  SeamRule rule = SeamRule::kEvent;
};

inline std::optional<SeamMismatch> first_seam_mismatch(
    std::initializer_list<SeamSignal> signals) {
  for (const SeamSignal& signal : signals) {
    if (!signal.compare) continue;
    const std::uint64_t rtl = signal.rtl & signal.mask;
    const std::uint64_t model = signal.model & signal.mask;
    if (rtl != model)
      return SeamMismatch{signal.name, rtl, model, rtl ^ model,
                          signal.rule};
  }
  return std::nullopt;
}

}  // namespace chisa::boom_repcut
