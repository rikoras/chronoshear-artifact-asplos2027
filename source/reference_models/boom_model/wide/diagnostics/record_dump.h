#pragma once
// Diagnostic-only capture of the complete published record for selected model
// cycles. A reported Oracle mismatch names one field; deciding whether that
// field was under an active control needs the other fields of the same cycle,
// which this writes out verbatim so they can be read back offline.
//
// The whole facility exists only in diagnostic builds. Performance builds
// compile out the call together with its arguments, so no cycle pays for the
// membership test, and nothing here changes the record, the comparison or the
// failure policy.
#if defined(CHISA_MODEL_DIAGNOSTICS)
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace chisa::diagnostic {

class RecordDump {
 public:
  static RecordDump& instance() {
    static RecordDump dump;
    return dump;
  }

  // `cycle` is the model cycle whose record is complete. Each selected cycle
  // is written once as a 16-byte header followed by the raw record bytes.
  void maybe_dump(std::uint64_t cycle, const void* bytes, std::size_t size) {
    if (out_ == nullptr || cycles_.find(cycle) == cycles_.end()) return;
    const std::uint64_t header[2] = {cycle, static_cast<std::uint64_t>(size)};
    if (std::fwrite(header, sizeof(header), 1, out_) != 1 ||
        std::fwrite(bytes, 1, size, out_) != size)
      throw std::runtime_error("record dump write failed");
    ++written_;
  }

  std::uint64_t written() const { return written_; }

  // Signals not carried by the record are published straight into the window
  // image, so their context has to be observed where the model computes it.
  // The same selected-cycle list decides when such an observation is kept, so
  // one run produces both the record and the surrounding context.
  bool selected(std::uint64_t cycle) const { return cycles_.find(cycle) != cycles_.end(); }

 private:
  RecordDump() {
    const char* path = std::getenv("CHISA_RECORD_DUMP");
    const char* list = std::getenv("CHISA_RECORD_DUMP_CYCLES");
    if (path == nullptr || *path == '\0' || list == nullptr || *list == '\0') return;
    std::FILE* cycles = std::fopen(list, "r");
    if (cycles == nullptr)
      throw std::runtime_error(std::string("cannot read dump cycle list: ") + list);
    unsigned long long value = 0;
    while (std::fscanf(cycles, "%llu", &value) == 1) cycles_.insert(value);
    if (std::ferror(cycles) || cycles_.empty())
      throw std::runtime_error(std::string("empty or unreadable cycle list: ") + list);
    std::fclose(cycles);
    // Refuse to overwrite: a dump is evidence bound to one run.
    out_ = std::fopen(path, "wbx");
    if (out_ == nullptr)
      throw std::runtime_error(std::string("cannot create record dump: ") + path);
  }
  ~RecordDump() {
    if (out_ == nullptr) return;
    if (std::fflush(out_) != 0 || std::fclose(out_) != 0) std::abort();
  }
  std::FILE* out_ = nullptr;
  std::uint64_t written_ = 0;
  std::unordered_set<std::uint64_t> cycles_;
};

}  // namespace chisa::diagnostic
#endif
