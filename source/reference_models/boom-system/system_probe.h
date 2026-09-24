#pragma once
// ==========================================================================
// Complete-TestHarness probe registry — the breadth layer of the four-tool
// divergence stack described in docs/GUIDER_PARADIGM.md section 4.
//
                                                                        
                                                                          
                                                                            
                                                                       
//
// It differs from the retired Large probe framework (probe_framework_boom.h, removed) in one structural way,
// and the difference matters.
//
// The core-only framework reached into the DUT through a closure per probe:
// `std::function<uint64_t(const StandaloneBoomDUT&)>`.  That works when the
// probe set is hand-picked.  Here the probe set *is* the oracle manifest --
// 1,924 qualified streams that the model is contractually obliged to
// produce -- and the
// RTL side is already sampled, name-keyed and provenance-checked by the
// generated exact tap.  So probes are registered by manifest trace key and the
// RTL value arrives through observe(); no probe reaches into the DUT itself.
// The validation set cannot drift from the delivery set because they are the
// same list.
//
// The `care` predicate is also model-side rather than RTL-side, for the same
// reason: a live producer has no RTL to ask.  Note what this means for the
// contract.  In the core-only guider `care` decided whether a probe counted;
// here every stream must be exactly right on every cycle, because
// Micro-Lockstep compares every injected oracle against the RTL-computed next
// value with no notion of don't-care.  `care` is therefore a bring-up triage
// filter only.  SYSPROBE_STRICT=1 compares everything and is what a delivery
// gate must run.
//
// Env-gated, nothing retained when off:
//   SYSPROBE=all | sub1,sub2 | exact.trace.key
//   SYSPROBE_STRICT=1     ignore care; every stream compared every cycle
//   SYSPROBE_MAX=n        cap first-divergence detail lines (default 20)
//   SYSPROBE_SKIP=n       ignore the first n cycles (reset), default 0
//   SYSPROBE_CARE_ONLY=1  hide unmodeled rows from the summary
//   SYSPROBE_INVENTORY=profile|structural|state|all
//                         print the effective binding inventory as TSV
// ==========================================================================

#include <algorithm>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "generated/system_oracle_record.h"
#include "oracle_timing.h"

namespace chisa::boom_system {

class SystemGuider;

enum class TemporalHint : std::uint8_t {
  None,
  ModelLateOne,
  ModelEarlyOne,
  SwappedAcrossOneCycle,
};

inline constexpr const char* temporal_hint_name(TemporalHint hint) {
  switch (hint) {
    case TemporalHint::None: return "none";
    case TemporalHint::ModelLateOne: return "model-late-1";
    case TemporalHint::ModelEarlyOne: return "model-early-1";
    case TemporalHint::SwappedAcrossOneCycle: return "one-cycle-swap";
  }
  return "unknown";
}

/** One manifest stream plus the model's obligation for it. */
struct StreamProbe {
  std::string subsystem;  // scoping bucket: core / frontend / lsu / mbus / ...
  std::string key;        // manifest traceKey, the join with the generated tap
  std::string flat;       // hierarchical RTL path, for reading the source
  OracleKind kind = OracleKind::Register;
  BindingTiming timing = BindingTiming::PostStepCycle;

  // Empty predict => UNMODELED. Empty care => always compared.
  std::function<uint64_t(const SystemGuider&)> predict;
  std::function<bool(const SystemGuider&)> care;
  const OracleRecord* sampled_record = nullptr;
  int sampled_slot = -1;  // >= 0: the lane of sampled_record to read

  long compared = 0;
  long real_mismatch = 0;
  long benign_mismatch = 0;
  long long first_real = -1;
  uint64_t first_rtl = 0;
  uint64_t first_model = 0;

  // Register streams have two useful faces without any DUT-specific audit
  // code: the last aligned PRE image and the first divergent PRE image.  That
  // pair identifies the edge on which the split happened and classifies each
  // side as WRITE or HOLD.  Keep it on the probe so both the immediate line
  // and the end-of-run summary report the same evidence.
  bool first_have_previous = false;
  bool first_previous_aligned = false;
  bool first_rtl_changed = false;
  bool first_model_changed = false;
  uint64_t first_previous_rtl = 0;
  uint64_t first_previous_model = 0;

  // A mismatch is often a correct value on the wrong row.  Retain one prior
  // pair so the probe can distinguish that pattern from a genuinely wrong
  // value without another instrumented rebuild.  The transition requirement
  // avoids classifying two equal stale/constant values as timing evidence.
  bool have_previous = false;
  uint64_t previous_rtl = 0;
  uint64_t previous_model = 0;
  long model_late_one = 0;
  long model_early_one = 0;
  TemporalHint first_temporal_hint = TemporalHint::None;

  bool modeled() const {
    return sampled_slot >= 0 || static_cast<bool>(predict);
  }
  bool profile_assumption() const {
    return timing == BindingTiming::ProfileConstant;
  }
  bool structural_constant() const {
    return timing == BindingTiming::StructuralConstant;
  }
  bool state_derived() const {
    return modeled() && !profile_assumption() && !structural_constant();
  }
  uint64_t prediction(const SystemGuider& model) const {
    return sampled_slot >= 0
               ? sampled_record->load(static_cast<std::size_t>(sampled_slot))
               : predict(model);
  }
};

class SystemProbes {
 public:
  static SystemProbes& instance() {
    static SystemProbes probes;
    return probes;
  }

  void configure_from_env() {
    if (const char* spec = getenv("SYSPROBE")) {
      if (!strcmp(spec, "all")) all_ = true;
      else parse_list(spec, enabled_);
    }
    if (const char* n = getenv("SYSPROBE_MAX")) max_details_ = atoi(n);
    if (const char* n = getenv("SYSPROBE_SKIP")) skip_ = atoll(n);
    if (getenv("SYSPROBE_STRICT")) strict_ = true;
    if (const char* w = getenv("SYSPROBE_TRACE")) {
      // "lo-hi": print every enabled stream's real mismatch per cycle in
      // the window (phase-diff evidence; off unless set).
      trace_lo_ = atoll(w);
      if (const char* dash = strchr(w, '-')) trace_hi_ = atoll(dash + 1);
    }
    if (getenv("SYSPROBE_CARE_ONLY")) care_only_ = true;
    if (const char* value = getenv("SYSPROBE_INVENTORY"))
      inventory_ = value;
    if (const char* w = getenv("SYSPROBE_WATCH")) watch_ = w;
    if (const char* n = getenv("SYSPROBE_WATCH_FROM")) watch_from_ = atoll(n);
    if (const char* n = getenv("SYSPROBE_WATCH_TO")) watch_to_ = atoll(n);
  }

  /** A resumed checkpoint child re-reads the per-experiment knobs (watch
    * and trace windows, detail cap, skip); the counters describe the whole
    * run and stay. */
  void reconfigure_from_env() {
    watch_.clear();
    watch_from_ = 0;
    watch_to_ = -1;
    trace_lo_ = -1;
    trace_hi_ = -1;
    details_ = 0;
    configure_from_env();
  }
  bool active() const { return all_ || !enabled_.empty(); }
  bool strict() const { return strict_; }
  std::size_t registered_stream_count() const {
    std::size_t total = 0;
    for (const auto& [name, count] : registered_) {
      (void)name;
      total += static_cast<std::size_t>(count.total);
    }
    return total;
  }
  std::size_t modeled_stream_count() const {
    std::size_t total = 0;
    for (const auto& [name, count] : registered_) {
      (void)name;
      total += static_cast<std::size_t>(count.modeled);
    }
    return total;
  }
  std::size_t state_derived_stream_count() const {
    std::size_t total = 0;
    for (const auto& [name, count] : registered_) {
      (void)name;
      total += static_cast<std::size_t>(count.state_derived);
    }
    return total;
  }
  std::size_t profile_assumption_stream_count() const {
    std::size_t total = 0;
    for (const auto& [name, count] : registered_) {
      (void)name;
      total += static_cast<std::size_t>(count.profile_assumption);
    }
    return total;
  }
  std::size_t structural_constant_stream_count() const {
    std::size_t total = 0;
    for (const auto& [name, count] : registered_) {
      (void)name;
      total += static_cast<std::size_t>(count.structural_constant);
    }
    return total;
  }
  std::size_t unknown_key_count() const { return unknown_keys_.size(); }
  unsigned long long sampled_cycle_count() const { return sampled_cycles_; }
  long model_late_one_count(const char* key) const {
    const auto found = by_key_.find(key);
    return found == by_key_.end() ? 0 : probes_[found->second].model_late_one;
  }
  long model_early_one_count(const char* key) const {
    const auto found = by_key_.find(key);
    return found == by_key_.end() ? 0 : probes_[found->second].model_early_one;
  }

  /** Keep registration and manifest-drift checks alive while excluding setup
    * traffic from the target-region statistics.  A post-load ROI runner pauses
    * before cycle zero and starts a fresh measurement only after debug has
    * drained to its quiescent handoff. */
  void pause_measurement() {
    measurement_enabled_ = false;
    reset_measurements();
  }

  void begin_measurement() {
    reset_measurements();
    measurement_enabled_ = true;
  }

  /** Register one manifest stream. Called once per stream at startup, from the
    * generated registration file, so an unregistered key later means the
    * manifest and the model have drifted apart -- which observe() reports. */
  void add(const char* subsystem, const char* key, const char* flat,
           OracleKind kind,
           std::function<uint64_t(const SystemGuider&)> predict = {},
           std::function<bool(const SystemGuider&)> care = {},
           BindingTiming timing = BindingTiming::PostStepCycle) {
    registered_[subsystem].total++;
    if (predict) note_binding_class(registered_[subsystem], timing);
    known_keys_.emplace(key);
    if (!all_ && !enabled_.count(subsystem) && !enabled_.count(key)) return;
    StreamProbe probe;
    probe.subsystem = subsystem;
    probe.key = key;
    probe.flat = flat;
    probe.kind = kind;
    probe.timing = timing;
    probe.predict = std::move(predict);
    probe.care = std::move(care);
    by_key_.emplace(probe.key, probes_.size());
    probes_.push_back(std::move(probe));
  }

  /** Register a sample-buffer source without manufacturing one distinct
    * capturing lambda type per manifest row.  Besides shrinking the binary,
    * this keeps a one-line probe edit from turning model_registration.cpp into
    * a multi-gigabyte, multi-minute compile.  Bindings are finalized before
    * registration, so the backing vector no longer reallocates. */
  void add_sampled(const char* subsystem, const char* key, const char* flat,
                   OracleKind kind, const OracleRecord* sampled_record,
                   std::uint16_t sampled_lane,
                   BindingTiming timing = BindingTiming::PreStepSample) {
    if (sampled_record == nullptr || sampled_lane >= kOracleRecordLanes) {
      fprintf(stderr,
              "[SYSPROBE] invalid sampled source for %s (lane=%u lanes=%zu record=%p)\n",
              key, static_cast<unsigned>(sampled_lane), kOracleRecordLanes,
              static_cast<const void*>(sampled_record));
      abort();
    }
    registered_[subsystem].total++;
    note_binding_class(registered_[subsystem], timing);
    known_keys_.emplace(key);
    if (!all_ && !enabled_.count(subsystem) && !enabled_.count(key)) return;
    StreamProbe probe;
    probe.subsystem = subsystem;
    probe.key = key;
    probe.flat = flat;
    probe.kind = kind;
    probe.timing = timing;
    probe.sampled_record = sampled_record;
    probe.sampled_slot = static_cast<int>(sampled_lane);
    by_key_.emplace(probe.key, probes_.size());
    probes_.push_back(std::move(probe));
  }

  /** Feed one RTL-sampled value in. Call from the tap observer, once per
    * stream per cycle, with the value the RTL actually holds. */
  void observe(long long cycle, const char* key, ObservationPhase phase,
               uint64_t rtl_value,
               const SystemGuider& model) {
    // `SYSPROBE_SKIP=n` means exactly the first n cycles.  The old `<=`
    // accidentally skipped cycle zero even at the default n=0, masking the
    // generated simulator's pre-first-edge register values.
    if (cycle < skip_) return;
    auto found = by_key_.find(key);
    if (found == by_key_.end()) {
      // The generated tap visits the complete manifest even when a diagnostic
      // run enables only one subsystem.  A registered-but-filtered stream is
      // intentionally ignored; only a key absent from registration indicates
      // actual manifest drift.
      if (known_keys_.count(key)) return;
      if (unknown_keys_.insert(key).second && unknown_reported_ < 10) {
        ++unknown_reported_;
        fprintf(stderr, "[SYSPROBE] tap key not registered: %s\n", key);
      }
      return;
    }
    if (!measurement_enabled_) return;
    StreamProbe& probe = probes_[found->second];
    if (!observation_matches(probe.kind, phase)) {
      ++phase_mismatches_;
      if (phase_reported_++ < 10)
        fprintf(stderr,
                "[SYSPROBE] tap phase mismatch c%lld %s manifest=%s tap=%s\n",
                cycle, key, oracle_kind_name(probe.kind),
                observation_phase_name(phase));
      return;
    }
    if (!watch_.empty() && cycle >= watch_from_ && cycle <= watch_to_ &&
        strstr(key, watch_.c_str())) {
      const uint64_t predicted = probe.modeled() ? probe.prediction(model) : 0;
      if (rtl_value != 0 || predicted != 0)
        fprintf(stderr, "[WATCH] c%lld %s rtl=%llx model=%llx\n", cycle, key,
                (unsigned long long)rtl_value, (unsigned long long)predicted);
    }
    if (!probe.modeled()) {
      ++unmodeled_samples_;
      return;
    }
    const bool care = strict_ || !probe.care || probe.care(model);
    const uint64_t predicted = probe.prediction(model);

    // Save the old pair before advancing the one-deep history.  For a
    // register stream, cN's PRE image is the result of the cN-1 edge.  Thus a
    // first mismatch at cN plus an equal pair at cN-1 is already a precise
    // PRE -> POST edge audit; no hand-packed `$next` probe is required.
    const bool had_previous = probe.have_previous;
    const uint64_t previous_rtl = probe.previous_rtl;
    const uint64_t previous_model = probe.previous_model;
    const bool model_late_one =
        had_previous && predicted == previous_rtl &&
        rtl_value != previous_rtl;
    const bool model_early_one =
        had_previous && rtl_value == previous_model &&
        predicted != previous_model;
    const TemporalHint temporal_hint =
        model_late_one && model_early_one
            ? TemporalHint::SwappedAcrossOneCycle
            : model_late_one ? TemporalHint::ModelLateOne
                             : model_early_one ? TemporalHint::ModelEarlyOne
                                               : TemporalHint::None;
    probe.have_previous = true;
    probe.previous_rtl = rtl_value;
    probe.previous_model = predicted;
    if (!care) {
      if (predicted != rtl_value) probe.benign_mismatch++;
      return;
    }
    probe.compared++;
    if (predicted == rtl_value) return;
    if (trace_hi_ > 0 && cycle >= trace_lo_ && cycle <= trace_hi_) {
      fprintf(stderr, "[TRACE c%llu] %s rtl=%llx model=%llx\n",
              static_cast<unsigned long long>(cycle), probe.key.c_str(),
              static_cast<unsigned long long>(rtl_value),
              static_cast<unsigned long long>(predicted));
    }
    probe.real_mismatch++;
    if (model_late_one) ++probe.model_late_one;
    if (model_early_one) ++probe.model_early_one;
    if (probe.first_real >= 0) return;
    probe.first_real = cycle;
    probe.first_rtl = rtl_value;
    probe.first_model = predicted;
    probe.first_temporal_hint = temporal_hint;
    probe.first_have_previous = had_previous;
    probe.first_previous_aligned =
        had_previous && previous_rtl == previous_model;
    probe.first_rtl_changed = had_previous && rtl_value != previous_rtl;
    probe.first_model_changed =
        had_previous && predicted != previous_model;
    probe.first_previous_rtl = previous_rtl;
    probe.first_previous_model = previous_model;
    if (details_ >= max_details_) return;
    ++details_;
    fprintf(stderr,
            "[SYSPROBE first-real c%lld] %s.%s  rtl=0x%" PRIx64
            " model=0x%" PRIx64 "  binding=%s%s%s\n    %s\n",
            cycle, probe.subsystem.c_str(), probe.key.c_str(), rtl_value,
            predicted, binding_timing_name(probe.timing),
            temporal_hint == TemporalHint::None ? "" : "  temporal=",
            temporal_hint == TemporalHint::None
                ? "" : temporal_hint_name(temporal_hint),
            probe.flat.c_str());
    if (probe.kind == OracleKind::Register && had_previous) {
      fprintf(stderr,
              "    [EDGE %s] rtl=%s model=%s  previous(rtl=0x%" PRIx64
              " model=0x%" PRIx64 ")  xor-now=0x%" PRIx64 "\n",
              previous_rtl == previous_model ? "FIRST-SPLIT" : "CARRIED",
              rtl_value == previous_rtl ? "HOLD" : "WRITE",
              predicted == previous_model ? "HOLD" : "WRITE",
              previous_rtl, previous_model, rtl_value ^ predicted);
    }
  }

  void end_of_cycle() {
    if (measurement_enabled_) ++sampled_cycles_;
  }

  long real_mismatch_count() const {
    long total = 0;
    for (const StreamProbe& probe : probes_) total += probe.real_mismatch;
    return total;
  }
  long state_derived_mismatch_count() const {
    long total = 0;
    for (const StreamProbe& probe : probes_)
      if (probe.state_derived()) total += probe.real_mismatch;
    return total;
  }
  long profile_assumption_mismatch_count() const {
    long total = 0;
    for (const StreamProbe& probe : probes_)
      if (probe.profile_assumption()) total += probe.real_mismatch;
    return total;
  }
  long structural_constant_mismatch_count() const {
    long total = 0;
    for (const StreamProbe& probe : probes_)
      if (probe.structural_constant()) total += probe.real_mismatch;
    return total;
  }
  unsigned long long phase_mismatch_count() const { return phase_mismatches_; }

  long long first_real_cycle() const {
    long long first = -1;
    for (const StreamProbe& probe : probes_)
      if (probe.first_real >= 0 && (first < 0 || probe.first_real < first))
        first = probe.first_real;
    return first;
  }

  void summary() const {
    if (!active()) return;
    long total = 0, modeled = 0, state_derived = 0;
    long profile_assumption = 0, structural_constant = 0;
    for (const auto& [name, count] : registered_) {
      total += count.total;
      modeled += count.modeled;
      state_derived += count.state_derived;
      profile_assumption += count.profile_assumption;
      structural_constant += count.structural_constant;
    }
    fprintf(stderr, "\n=== [SYSPROBE] complete-TestHarness stream validation ===\n");
    fprintf(stderr,
            "  manifest streams %ld  modeled %ld  unmodeled %ld"
            "   (%s)\n",
            total, modeled, total - modeled,
            strict_ ? "STRICT: care ignored" : "care predicates active");
    fprintf(stderr,
            "  binding truth   state-derived %ld  profile-assumption %ld  "
            "structural-constant %ld\n",
            state_derived, profile_assumption, structural_constant);
    if (!inventory_.empty()) {
      fprintf(stderr, "\n  binding inventory (%s):\n", inventory_.c_str());
      for (const StreamProbe& probe : probes_) {
        const bool selected =
            inventory_ == "all" ||
            (inventory_ == "profile" && probe.profile_assumption()) ||
            (inventory_ == "structural" && probe.structural_constant()) ||
            (inventory_ == "state" && probe.state_derived());
        if (!selected) continue;
        fprintf(stderr, "[BINDING]\t%s\t%s\t%s\t%s\n",
                probe.subsystem.c_str(), binding_timing_name(probe.timing),
                probe.key.c_str(), probe.flat.c_str());
      }
    }
    fprintf(stderr, "  sampled %zu enabled stream(s) over %llu cycle(s)\n",
            probes_.size(), (unsigned long long)sampled_cycles_);
    if (phase_mismatches_ != 0)
      fprintf(stderr, "  tap/manifest phase mismatches %llu\n",
              phase_mismatches_);

    const StreamProbe* first = nullptr;
    const StreamProbe* first_state = nullptr;
    const StreamProbe* first_profile = nullptr;
    const StreamProbe* first_structural = nullptr;
    for (const StreamProbe& probe : probes_) {
      if (probe.first_real < 0) continue;
      if (!first || probe.first_real < first->first_real) first = &probe;
      if (probe.state_derived() &&
          (!first_state || probe.first_real < first_state->first_real))
        first_state = &probe;
      if (probe.profile_assumption() &&
          (!first_profile || probe.first_real < first_profile->first_real))
        first_profile = &probe;
      if (probe.structural_constant() &&
          (!first_structural ||
           probe.first_real < first_structural->first_real))
        first_structural = &probe;
    }
    if (first) {
      fprintf(stderr,
              "\n  >>> FIRST REAL DIVERGENCE: %s.%s @ c%lld"
              "  rtl=0x%" PRIx64 " model=0x%" PRIx64
              "  binding=%s%s%s\n      %s\n",
              first->subsystem.c_str(), first->key.c_str(), first->first_real,
              first->first_rtl, first->first_model,
              binding_timing_name(first->timing),
              first->first_temporal_hint == TemporalHint::None
                  ? "" : "  temporal=",
              first->first_temporal_hint == TemporalHint::None
                  ? "" : temporal_hint_name(first->first_temporal_hint),
              first->flat.c_str());
      if (first->kind == OracleKind::Register &&
          first->first_have_previous) {
        fprintf(stderr,
                "      EDGE %s: rtl=%s model=%s  previous(rtl=0x%" PRIx64
                " model=0x%" PRIx64 ") xor-now=0x%" PRIx64 "\n",
                first->first_previous_aligned ? "FIRST-SPLIT" : "CARRIED",
                first->first_rtl_changed ? "WRITE" : "HOLD",
                first->first_model_changed ? "WRITE" : "HOLD",
                first->first_previous_rtl, first->first_previous_model,
                first->first_rtl ^ first->first_model);
      }
      const auto print_class_first = [](const char* label,
                                        const StreamProbe* probe) {
        if (!probe) return;
        fprintf(stderr,
                "  >>> FIRST %-20s %s.%s @ c%lld  rtl=0x%" PRIx64
                " model=0x%" PRIx64 "\n",
                label, probe->subsystem.c_str(), probe->key.c_str(),
                probe->first_real, probe->first_rtl, probe->first_model);
      };
      print_class_first("STATE-DERIVED", first_state);
      print_class_first("PROFILE WAKEUP", first_profile);
      print_class_first("STRUCTURAL VIOLATION", first_structural);
    } else if (modeled == 0) {
      fprintf(stderr, "\n  >>> no stream is modeled yet: nothing was compared\n");
    } else {
      fprintf(stderr, "\n  >>> no real divergence among modeled streams\n");
    }

    struct Row {
      long streams = 0, modeled = 0, green = 0, real = 0, benign = 0;
      long long first = -1;
    };
    std::map<std::string, Row> rows;
    for (const StreamProbe& probe : probes_) {
      Row& row = rows[probe.subsystem];
      row.streams++;
      if (!probe.modeled()) continue;
      row.modeled++;
      row.real += probe.real_mismatch;
      row.benign += probe.benign_mismatch;
      if (probe.compared > 0 && probe.real_mismatch == 0) row.green++;
      if (probe.first_real >= 0 && (row.first < 0 || probe.first_real < row.first))
        row.first = probe.first_real;
    }
    fprintf(stderr, "\n  %-14s %8s %8s %7s %7s %8s %11s\n", "subsystem",
            "sampled", "modeled", "green", "REAL", "benign", "first-real");
    for (const auto& [name, row] : rows) {
      if (care_only_ && row.modeled == 0) continue;
      char first_cell[16];
      if (row.modeled == 0) snprintf(first_cell, sizeof first_cell, "unmodeled");
      else if (row.first < 0) snprintf(first_cell, sizeof first_cell, "-");
      else snprintf(first_cell, sizeof first_cell, "c%lld", row.first);
      fprintf(stderr, "  %-14s %8ld %8ld %7ld %7ld %8ld %11s\n", name.c_str(),
              row.streams, row.modeled, row.green, row.real, row.benign,
              first_cell);
    }

    std::vector<const StreamProbe*> hot;
    for (const StreamProbe& probe : probes_)
      if (probe.real_mismatch > 0) hot.push_back(&probe);
    std::sort(hot.begin(), hot.end(),
              [](const StreamProbe* a, const StreamProbe* b) {
                if (a->first_real != b->first_real)
                  return a->first_real < b->first_real;
                return a->real_mismatch > b->real_mismatch;
              });
    if (!hot.empty()) {
      fprintf(stderr, "\n  Top REAL streams (earliest first):\n");
      std::size_t shown = 0;
      for (const StreamProbe* probe : hot) {
        if (shown++ >= 25) {
          fprintf(stderr, "    ... (%zu more)\n", hot.size() - 25);
          break;
        }
        fprintf(stderr,
                "    %-44s real=%-7ld first c%-7lld rtl=0x%" PRIx64
                " model=0x%" PRIx64 " binding=%s late1=%ld early1=%ld\n",
                (probe->subsystem + "." + probe->key).c_str(),
                probe->real_mismatch, probe->first_real, probe->first_rtl,
                probe->first_model, binding_timing_name(probe->timing),
                probe->model_late_one,
                probe->model_early_one);
      }
    }
    if (!unknown_keys_.empty())
      fprintf(stderr,
              "\n  WARNING: %zu tap key(s) had no registered probe;"
              " manifest and registration have drifted\n",
              unknown_keys_.size());
  }

 private:
  SystemProbes() = default;

  void reset_measurements() {
    for (StreamProbe& probe : probes_) {
      probe.compared = 0;
      probe.real_mismatch = 0;
      probe.benign_mismatch = 0;
      probe.first_real = -1;
      probe.first_rtl = 0;
      probe.first_model = 0;
      probe.first_have_previous = false;
      probe.first_previous_aligned = false;
      probe.first_rtl_changed = false;
      probe.first_model_changed = false;
      probe.first_previous_rtl = 0;
      probe.first_previous_model = 0;
      probe.have_previous = false;
      probe.previous_rtl = 0;
      probe.previous_model = 0;
      probe.model_late_one = 0;
      probe.model_early_one = 0;
      probe.first_temporal_hint = TemporalHint::None;
    }
    details_ = 0;
    sampled_cycles_ = 0;
    unmodeled_samples_ = 0;
    phase_mismatches_ = 0;
    phase_reported_ = 0;
  }

  static void parse_list(const char* spec, std::unordered_set<std::string>& out) {
    const char* cursor = spec;
    while (*cursor) {
      while (*cursor == ',' || *cursor == ' ') ++cursor;
      const char* start = cursor;
      while (*cursor && *cursor != ',' && *cursor != ' ') ++cursor;
      if (cursor > start) out.emplace(start, cursor);
    }
  }

  struct Registered {
    long total = 0, modeled = 0;
    long state_derived = 0;
    long profile_assumption = 0;
    long structural_constant = 0;
  };

  static void note_binding_class(Registered& registered,
                                 BindingTiming timing) {
    ++registered.modeled;
    if (timing == BindingTiming::ProfileConstant)
      ++registered.profile_assumption;
    else if (timing == BindingTiming::StructuralConstant)
      ++registered.structural_constant;
    else
      ++registered.state_derived;
  }

  std::vector<StreamProbe> probes_;
  std::unordered_map<std::string, std::size_t> by_key_;
  std::map<std::string, Registered> registered_;
  std::unordered_set<std::string> known_keys_;
  std::unordered_set<std::string> enabled_;
  std::unordered_set<std::string> unknown_keys_;
  bool all_ = false;
  bool strict_ = false;
  std::string watch_;
  std::string inventory_;
  long long watch_from_ = 0;
  long long watch_to_ = -1;
  bool care_only_ = false;
  int max_details_ = 20;
  int details_ = 0;
  int unknown_reported_ = 0;
  int phase_reported_ = 0;
  long long skip_ = 0;
  bool measurement_enabled_ = true;
  unsigned long long sampled_cycles_ = 0;
  unsigned long long unmodeled_samples_ = 0;
  long long trace_lo_ = 0;
  long long trace_hi_ = 0;
  unsigned long long phase_mismatches_ = 0;
};

// Registration helpers, mirroring PROBE_REG/PROBE_RTL ergonomics. `m` is the
// model inside the closures.
#define SYSPROBE_MODELED(subsystem, key, flat, predict_expr)                  \
  ::chisa::boom_system::SystemProbes::instance().add(                        \
      subsystem, key, flat, ::chisa::boom_system::OracleKind::Register,      \
      [](const ::chisa::boom_system::SystemGuider& m) -> uint64_t {           \
        return (predict_expr);                                                \
      })

#define SYSPROBE_MODELED_CARE(subsystem, key, flat, predict_expr, care_expr)  \
  ::chisa::boom_system::SystemProbes::instance().add(                        \
      subsystem, key, flat, ::chisa::boom_system::OracleKind::Register,      \
      [](const ::chisa::boom_system::SystemGuider& m) -> uint64_t {           \
        return (predict_expr);                                                \
      },                                                                      \
      [](const ::chisa::boom_system::SystemGuider& m) -> bool {               \
        return (care_expr);                                                   \
      })

#define SYSPROBE_UNMODELED(subsystem, key, flat)                              \
  ::chisa::boom_system::SystemProbes::instance().add(                        \
      subsystem, key, flat, ::chisa::boom_system::OracleKind::Register)

}  // namespace chisa::boom_system
