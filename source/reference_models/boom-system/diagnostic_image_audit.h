#pragma once
#if defined(CHISA_MODEL_DIAGNOSTICS)
#include <array>
#include <cstdint>
#include <cstring>
#include <map>
#include <mutex>
#include <stdexcept>
#include "../boom_model/common/diagnostic_monitor.h"

namespace chisa::boom_system {
// Snapshots come from each owner's source record at its actual copy/patch
// point. They never come from the destination being checked. Cycles remain
// distinct even if a staging address or ring position is reused.
template<std::size_t Bytes>
class DiagnosticImageAudit {
 public:
  void capture(std::uint64_t cycle, const unsigned char* source,
               std::size_t begin, std::size_t count) {
    if (begin > Bytes || count > Bytes - begin)
      throw std::out_of_range("diagnostic source range exceeds record");
    std::lock_guard<std::mutex> lock(mutex_);
    if (cycle < retired_before_)
      throw std::runtime_error("late diagnostic source for retired image");
    auto& entry = expected_[cycle];
    std::memcpy(entry.bytes.data()+begin, source+begin, count);
    std::memset(entry.seen.data()+begin, 1, count);
  }
  bool verify(std::uint64_t cycle, const unsigned char* image, unsigned position) {
    using namespace ::chisa::diagnostic;
    std::lock_guard<std::mutex> lock(mutex_);
    if (cycle < retired_before_)
      throw std::runtime_error("out-of-order diagnostic image verification");
    const auto it = expected_.find(cycle);
    std::size_t missing = Bytes, first = Bytes;
    if (it == expected_.end()) missing = 0;
    else for (std::size_t i=0; i<Bytes; ++i) {
      if (!it->second.seen[i] && missing==Bytes) missing=i;
      if (image[i]!=it->second.bytes[i] && first==Bytes) first=i;
    }
    const bool complete = missing==Bytes;
    require("transport", "source-owner-coverage", cycle, Layer::Publication, Phase::Post, complete,
        {{"position",position},{"first_missing_byte",missing},{"record_bytes",Bytes}});
    const bool equal = complete && first==Bytes;
    require("transport", "record-to-image", cycle, Layer::Transport, Phase::Post, equal,
        {{"position",position},{"first_byte",first},
         {"expected",it!=expected_.end() && first<Bytes ? it->second.bytes[first] : 0u},
         {"actual",first<Bytes ? image[first] : 0u}});
    if (it!=expected_.end()) expected_.erase(it);
    retired_before_=cycle+1;
    return equal;
  }
 private:
  struct Entry { std::array<unsigned char,Bytes> bytes{}, seen{}; };
  std::mutex mutex_;
  std::map<std::uint64_t,Entry> expected_;
  std::uint64_t retired_before_=0;
};
}  // namespace chisa::boom_system
#endif
