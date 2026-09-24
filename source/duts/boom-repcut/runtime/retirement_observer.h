#pragma once
// Bounded, read-only comparison of the fields the consumer capture actually
// observes. Instruction bits and fflags are not part of this capture contract.
#include "../../../reference_models/boom_model/common/architectural_state.h"
#include <array>
#include <cinttypes>
#include <cstdio>
#include <deque>
#include <mutex>
#include <stdexcept>

namespace chisa::boom_repcut {
class RetirementObserver {
 public:
  using Event = boom_model::RetirementEvent;
  void model(const Event& event) { push(true, event); }
  void rtl(const Event& event) { push(false, event); }
  bool context_complete() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return first_failure_ && compared_ >= first_failure_ + 32;
  }
  void finish() const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::fprintf(stderr, "ARCHITECTURE_ORDERED compared=%" PRIu64 " mismatches=%" PRIu64
        " model_pending=%zu rtl_pending=%zu scope=pc,destination,value,store\n",
        compared_, failures_, model_.size(), rtl_.size());
    if (!model_.empty() || !rtl_.empty())
      throw std::runtime_error("ordered architectural observations ended unmatched");
    if (failures_) throw std::runtime_error("ordered architectural observations differ; first context saved");
  }
 private:
  struct Pair { Event model, rtl; std::uint64_t sequence = 0; };
  mutable std::mutex mutex_;
  std::deque<Event> model_, rtl_;
  std::array<Pair, 96> history_{};
  std::uint64_t compared_ = 0, failures_ = 0, first_failure_ = 0;
  static const char* difference(const Event& a, const Event& b) {
    if (a.pc != b.pc) return "pc";
    if (a.writes_x != b.writes_x || a.writes_f != b.writes_f) return "destination-kind";
    if ((a.writes_x || a.writes_f) && a.rd != b.rd) return "destination-register";
    if ((a.writes_x || a.writes_f) && a.value != b.value) return "writeback-value";
    if (a.memory_write != b.memory_write) return "memory-write";
    if (a.memory_write && (a.memory_address != b.memory_address ||
                          a.memory_value != b.memory_value || a.memory_size != b.memory_size)) return "store";
    return nullptr;
  }
  static void print(const Pair& pair, const char* kind) {
    const auto& a = pair.model; const auto& b = pair.rtl;
    std::fprintf(stderr, "ARCHITECTURE_CONTEXT kind=%s seq=%" PRIu64
        " model_cycle=%" PRIu64 " rtl_cycle=%" PRIu64
        " model_pc=%" PRIx64 " rtl_pc=%" PRIx64
        " model_instruction=%" PRIx32
        " model_x=%u rtl_x=%u model_f=%u rtl_f=%u model_rd=%u rtl_rd=%u"
        " model_value=%" PRIx64 " rtl_value=%" PRIx64
        " model_store=%u rtl_store=%u model_address=%" PRIx64 " rtl_address=%" PRIx64
        " model_data=%" PRIx64 " rtl_data=%" PRIx64 " model_size=%u rtl_size=%u\n",
        kind, pair.sequence, a.cycle, b.cycle, a.pc, b.pc, a.instruction,
        a.writes_x, b.writes_x, a.writes_f, b.writes_f, a.rd, b.rd, a.value, b.value,
        a.memory_write, b.memory_write, a.memory_address, b.memory_address,
        a.memory_value, b.memory_value, a.memory_size, b.memory_size);
  }
  void push(bool model_side, const Event& event) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto& queue = model_side ? model_ : rtl_;
    queue.push_back(event);
    if (queue.size() > 4096) throw std::runtime_error("ordered architectural observation skew exceeds bound");
    while (!model_.empty() && !rtl_.empty()) {
      Pair pair{model_.front(), rtl_.front(), ++compared_};
      model_.pop_front(); rtl_.pop_front();
      const char* field = difference(pair.model, pair.rtl);
      if (field) {
        ++failures_;
        if (!first_failure_) {
          first_failure_ = compared_;
          std::fprintf(stderr, "ARCHITECTURE_FIRST_DIFFERENCE field=%s seq=%" PRIu64 "\n", field, compared_);
          const std::uint64_t begin = compared_ > history_.size() ? compared_ - history_.size() : 1;
          for (auto n = begin; n < compared_; ++n) print(history_[(n - 1) % history_.size()], "before");
        }
      }
      if (first_failure_ && compared_ <= first_failure_ + 32) print(pair, field ? field : "after");
      history_[(compared_ - 1) % history_.size()] = pair;
    }
  }
};
} // namespace chisa::boom_repcut
