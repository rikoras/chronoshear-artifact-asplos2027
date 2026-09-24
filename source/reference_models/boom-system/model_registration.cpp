// Registers every manifest stream with the probe registry, attaching a model
// binding where one exists. This is the only place the generated obligation
// list and the hand-written claims meet.

#include <immintrin.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <array>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "model_bindings.h"
#include "system_guider.h"
#include "system_probe.h"
#include "generated/system_probe_registry.inc"

namespace chisa::boom_system {

void ModelBindings::bind(const char* trace_key, PredictFn predict,
                         CareFn care) {
  if (predict == nullptr) {
    fprintf(stderr, "[BIND] %s bound with a null predictor\n", trace_key);
    abort();
  }
  ModelBinding binding;
  binding.predict = predict;
  binding.care = care;
  binding.timing = BindingTiming::PostStepCycle;
  auto [it, inserted] = bindings_.emplace(trace_key, binding);
  if (!inserted) {
    // Two subsystems each believing they own a stream means one of them is
    // silently not being checked. Fail here rather than at 2,000 cycles.
    fprintf(stderr, "[BIND] duplicate binding for %s\n", trace_key);
    abort();
  }
  (void)it;
}

std::uint16_t ModelBindings::lane_for_key(const char* trace_key) {
  // Lane == manifest index == kSystemProbeManifest row; built once.
  static const std::unordered_map<std::string_view, std::uint16_t> lanes = [] {
    std::unordered_map<std::string_view, std::uint16_t> table;
    table.reserve(kSystemProbeManifestCount);
    for (std::size_t i = 0; i < kSystemProbeManifestCount; ++i)
      table.emplace(kSystemProbeManifest[i].key, static_cast<std::uint16_t>(i));
    return table;
  }();
  const auto found = lanes.find(trace_key);
  return found == lanes.end() ? kOracleRecordPadLane : found->second;
}

void ModelBindings::build_predicted_lanes() {
  predicted_.clear();
  for (const auto& [key, binding] : bindings_) {
    if (binding.predict == nullptr) continue;
    const std::uint16_t lane = lane_for_key(key.c_str());
    if (lane == kOracleRecordPadLane) continue;  // reported by finalize()
    predicted_.push_back(PredictedLane{binding.predict, lane, key.find("dcache") != std::string::npos});
  }
  if (predicted_.size() > kPredictedCapacity) {
    fprintf(stderr, "[BIND] %zu predicted lanes exceed the change-list capacity %zu\n",
            predicted_.size(), kPredictedCapacity);
    abort();
  }
  predicted_built_ = true;
}

void ModelBindings::bind_sampled(const char* trace_key, SampleFn sample) {
  if (sample == nullptr) {
    fprintf(stderr, "[BIND] %s bound with a null sampler\n", trace_key);
    abort();
  }
  const int slot = static_cast<int>(lane_of_slot_.size());
  lane_of_slot_.push_back(lane_for_key(trace_key));
  shadow_slots_.push_back(0);
  individual_samplers_.push_back(
      IndividualSampler{sample, static_cast<std::size_t>(slot)});
  ModelBinding binding;
  binding.sampled_slot = slot;
  binding.timing = BindingTiming::PreStepSample;
  auto [it, inserted] = bindings_.emplace(trace_key, binding);
  if (!inserted) {
    fprintf(stderr, "[BIND] duplicate binding for %s\n", trace_key);
    abort();
  }
  (void)it;
}

void ModelBindings::reserve_image_owned(const char* trace_key, bool combinational) {
  // The lane keeps a slot so the probe path (system_probe.h) reads it from
  // the record like any sampled lane; nothing ever stores through the slot.
  const int slot = static_cast<int>(lane_of_slot_.size());
  const std::uint16_t lane = lane_for_key(trace_key);
  lane_of_slot_.push_back(lane);
  shadow_slots_.push_back(0);
  owned_lanes_.push_back(lane);
  ModelBinding binding;
  binding.sampled_slot = slot;
  binding.timing = combinational ? BindingTiming::PreStepCombinational
                                 : BindingTiming::PreStepSample;
  auto [it, inserted] = bindings_.emplace(trace_key, binding);
  if (!inserted) {
    fprintf(stderr, "[BIND] duplicate binding for %s\n", trace_key);
    abort();
  }
  (void)it;
}

int ModelBindings::reserve_sampled(const char* trace_key) {
  const int slot = static_cast<int>(lane_of_slot_.size());
  lane_of_slot_.push_back(lane_for_key(trace_key));
  shadow_slots_.push_back(0);
  ModelBinding binding;
  binding.sampled_slot = slot;
  binding.timing = BindingTiming::PreStepSample;
  auto [it, inserted] = bindings_.emplace(trace_key, binding);
  if (!inserted) {
    fprintf(stderr, "[BIND] duplicate binding for %s\n", trace_key);
    abort();
  }
  (void)it;
  return slot;
}

void ModelBindings::finalize() {
  unclaimed_.clear();

  for (const auto& [key, binding] : bindings_) {
    (void)binding;
    if (!registered_.count(key)) unclaimed_.push_back(key);
  }
}

void register_model_streams() {
  register_model_bindings();
  ModelBindings& bindings = ModelBindings::instance();
  SystemProbes& probes = SystemProbes::instance();

  std::size_t total = 0;
  std::size_t modeled = 0;
  std::array<std::size_t, 2> kind_counts{};
  std::array<std::size_t, 6> timing_counts{};
  std::vector<std::string> timing_debt;
  std::vector<std::string> profile_debt;
  std::size_t reg_from_post = 0;
  std::size_t comb_from_pre = 0;

  for (const SystemProbeManifestRow& row : kSystemProbeManifest) {
    ++total;
    ++kind_counts[row.kind == OracleKind::Register ? 0u : 1u];
    bindings.note_registered(row.key);
    if (const ModelBinding* bound = bindings.find(row.key)) {
      ++modeled;
      ++timing_counts[static_cast<std::size_t>(bound->timing)];
      if (bound->timing == BindingTiming::ProfileConstant)
        profile_debt.emplace_back(row.key);
      if (!binding_matches(row.kind, bound->timing)) {
        if (row.kind == OracleKind::Register) ++reg_from_post;
        else ++comb_from_pre;
        timing_debt.emplace_back(
            std::string(row.key) + " manifest=" + oracle_kind_name(row.kind) +
            " binding=" + binding_timing_name(bound->timing));
      }
      if (bound->sampled_slot >= 0) {
        probes.add_sampled(row.subsystem, row.key, row.flat, row.kind,
                           &bindings.published_record(),
                           static_cast<std::uint16_t>(
                               bindings.lane_of_slot(bound->sampled_slot)),
                           bound->timing);
      } else {
        probes.add(row.subsystem, row.key, row.flat, row.kind, bound->predict,
                   bound->care, bound->timing);
      }
    } else {
      probes.add(row.subsystem, row.key, row.flat, row.kind);
      if (std::getenv("SYSMODEL_BINDING_AUDIT") != nullptr)
        std::fprintf(stderr, "[UNMODELED] %s %s %s\n", row.subsystem,
                     oracle_kind_name(row.kind), row.key);
    }
  }

  bindings.finalize();
  if (!bindings.unclaimed().empty()) {
    // The model claims streams this manifest does not select. Either the
    // manifest was regenerated and the bindings are stale, or a binding has a
    // typo -- both mean the model is being checked against a contract that no
    // longer exists.
    fprintf(stderr,
            "[BIND] %zu bound stream(s) are absent from the manifest:\n",
            bindings.unclaimed().size());
    std::size_t shown = 0;
    for (const std::string& key : bindings.unclaimed()) {
      if (shown++ >= 10) {
        fprintf(stderr, "  ... (%zu more)\n", bindings.unclaimed().size() - 10);
        break;
      }
      fprintf(stderr, "  %s\n", key.c_str());
    }
#if defined(CHISA_SUBSET_CONTRACT_EXPERIMENT)
    // A producer built against an explicit experimental subset
    // of the qualified contract (oracle-budget / decision-level experiments)
    // keeps the full binding set; the unclaimed bindings map to the pad lane.
    fprintf(stderr, "[BIND] tolerated (explicit subset-contract experiment)\n");
#else
    abort();
#endif
  }

  const std::size_t profile_constants =
      timing_counts[static_cast<std::size_t>(BindingTiming::ProfileConstant)];
  const std::size_t structural_constants = timing_counts[
      static_cast<std::size_t>(BindingTiming::StructuralConstant)];
  fprintf(stderr,
          "[BIND] %zu manifest stream(s), %zu bound: %zu state-derived, "
          "%zu profile assumption, %zu structural constant\n",
          total, modeled, modeled - profile_constants - structural_constants,
          profile_constants, structural_constants);
  fprintf(stderr,
          "[BIND] timing contract reg=%zu comb=%zu; pre-step=%zu "
          "post-step-cycle=%zu pre-step-comb=%zu post-step-reg-snapshot=%zu "
          "profile-constant=%zu structural-constant=%zu; "
          "unproven-cross-phase=%zu (reg<-post=%zu comb<-pre=%zu)\n",
          kind_counts[0], kind_counts[1],
          timing_counts[static_cast<std::size_t>(BindingTiming::PreStepSample)],
          timing_counts[static_cast<std::size_t>(BindingTiming::PostStepCycle)],
          timing_counts[static_cast<std::size_t>(BindingTiming::PreStepCombinational)],
          timing_counts[static_cast<std::size_t>(BindingTiming::PostStepRegisterSnapshot)],
          timing_counts[static_cast<std::size_t>(BindingTiming::ProfileConstant)],
          timing_counts[static_cast<std::size_t>(BindingTiming::StructuralConstant)],
          timing_debt.size(), reg_from_post, comb_from_pre);
  if (!profile_debt.empty()) {
    // A value copied from one workload's profile is not a prediction.  The
    // model either derives the stream from its own state or has no source;
    // there is no bring-up tier any more.
    fprintf(stderr, "[BIND] %zu stream(s) bound as profile assumptions:\n",
            profile_debt.size());
    for (const std::string& key : profile_debt)
      fprintf(stderr, "  %s\n", key.c_str());
    abort();
  }
  if (!timing_debt.empty()) {
    const bool verbose = std::getenv("SYSMODEL_PHASE_AUDIT") != nullptr;
    const std::size_t limit = verbose ? timing_debt.size() : 12u;
    fprintf(stderr, "[BIND] oracle timing proof debt%s:\n",
            verbose ? " (complete)" : " (first 12; SYSMODEL_PHASE_AUDIT=1 for all)");
    for (std::size_t i = 0; i < timing_debt.size() && i < limit; ++i)
      fprintf(stderr, "  %s\n", timing_debt[i].c_str());
    if (std::getenv("SYSMODEL_PHASE_STRICT") != nullptr) abort();
  }
}

// ---- image-owned lanes under export offload --------------------------------
void ModelBindings::snapshot_image_owned() {
  if (owned_ranges_.empty() && !owned_lanes_.empty()) {
    std::vector<std::pair<std::uint32_t, std::uint32_t>> ranges;
    owned_lane_at_byte_.assign(kOracleRecordPaddedBytes, 0xffffu);
    for (const std::uint16_t lane : owned_lanes_) {
      const OracleRecordLane& d = kOracleRecordLane[lane];
      ranges.emplace_back(d.offset, d.offset + d.bytes);
      for (unsigned b = 0; b < d.bytes; ++b) owned_lane_at_byte_[d.offset + b] = lane;
    }
    std::sort(ranges.begin(), ranges.end());
    for (const auto& r : ranges) {
      if (!owned_ranges_.empty() && r.first <= owned_ranges_.back().second)
        owned_ranges_.back().second = std::max(owned_ranges_.back().second, r.second);
      else
        owned_ranges_.push_back(r);
    }
  }
  owned_shadow_.assign(record_.bytes, record_.bytes + kOracleRecordPaddedBytes);
}

void ModelBindings::sync_owned_changes() {
  if (owned_lanes_.empty()) return;
  if (owned_ranges_.empty()) {
    snapshot_image_owned();
    for (const std::uint16_t lane : owned_lanes_)
      lane_cell_[lane].value = apply_bits(record_.load(lane), lane_bits_[lane]);
    // One 64-byte-aligned span over every owned byte: the per-lane ranges
    // are thousands of 1..8-byte pieces, far too many to walk one by one.
    // Bytes inside the span that no owned lane covers map to no lane and
    // are skipped when they change.
    owned_span_lo_ = owned_ranges_.front().first & ~std::uint32_t{63};
    owned_span_hi_ = std::min<std::uint32_t>(
        static_cast<std::uint32_t>(kOracleRecordPaddedBytes),
        (owned_ranges_.back().second + 63u) & ~std::uint32_t{63});
    return;
  }
  const unsigned char* rec = record_.bytes;
  unsigned char* sh = owned_shadow_.data();
  std::uint16_t last = 0xffffu;
  const auto changed_byte = [&](std::uint32_t at) {
    const std::uint16_t lane = owned_lane_at_byte_[at];
    if (lane == 0xffffu || lane == last) return;
    last = lane;
    lane_cell_[lane].value = apply_bits(record_.load(lane), lane_bits_[lane]);
    changed_lanes_[change_count_] = lane;
    change_count_ += change_count_ < kChangeCapacity;
  };
  std::uint32_t pos = owned_span_lo_;
#if defined(__AVX512BW__)
  for (; pos + 64 <= owned_span_hi_; pos += 64) {
    const __m512i a = _mm512_loadu_si512(reinterpret_cast<const void*>(rec + pos));
    const __m512i b = _mm512_loadu_si512(reinterpret_cast<const void*>(sh + pos));
    __mmask64 m = _mm512_cmpneq_epi8_mask(a, b);
    if (m == 0) continue;
    while (m) {
      const unsigned k = static_cast<unsigned>(__builtin_ctzll(m));
      changed_byte(pos + k);
      m &= m - 1;
    }
    _mm512_storeu_si512(reinterpret_cast<void*>(sh + pos), a);
  }
#endif
  for (; pos < owned_span_hi_; pos += 8) {
    const unsigned n = std::min<std::uint32_t>(8, owned_span_hi_ - pos);
    std::uint64_t a = 0, b = 0;
    std::memcpy(&a, rec + pos, n);
    std::memcpy(&b, sh + pos, n);
    if (a == b) continue;
    const std::uint64_t x = a ^ b;
    for (unsigned k = 0; k < n; ++k)
      if (((x >> (8 * k)) & 0xffu) != 0) changed_byte(pos + k);
    std::memcpy(sh + pos, &a, n);
  }
}

void ModelBindings::publish_image_owned() {
  if (ring_ == nullptr || owned_ranges_.empty()) return;
  const unsigned char* rec = record_.bytes;
  unsigned char* sh = owned_shadow_.data();
  for (const auto& range : owned_ranges_) {
    for (std::uint32_t pos = range.first; pos < range.second; pos += 8) {
      const unsigned n = std::min<std::uint32_t>(8, range.second - pos);
      std::uint64_t a = 0, b = 0;
      std::memcpy(&a, rec + pos, n);
      std::memcpy(&b, sh + pos, n);
      if (a == b) continue;
      const std::uint64_t x = a ^ b;
      std::uint16_t last = 0xffffu;
      for (unsigned k = 0; k < n; ++k) {
        if (((x >> (8 * k)) & 0xffu) == 0) continue;
        const std::uint16_t lane = owned_lane_at_byte_[pos + k];
        if (lane == 0xffffu || lane == last) continue;
        last = lane;
        ring_->push_pair(lane, apply_bits(record_.load(lane), lane_bits_[lane]), lane_bits_[lane]);
      }
      std::memcpy(sh + pos, &a, n);
    }
  }
}

}  // namespace chisa::boom_system
