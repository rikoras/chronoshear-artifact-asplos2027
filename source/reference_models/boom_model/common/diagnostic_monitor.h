#pragma once
// Diagnostic observations never participate in model decisions. With the
// compile switch absent, even hook arguments disappear (including side effects).
#if !defined(CHISA_MODEL_DIAGNOSTICS)
#define CHISA_DIAG(...) do { } while (0)
#else
#define CHISA_DIAG(...) do { __VA_ARGS__; } while (0)

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <map>
#include <stdexcept>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>

namespace chisa::diagnostic {
enum class Layer { Internal, Publication, Transport, Injection };
enum class Phase { Pre, Post, Combinational, Window };
struct Field { const char* name; std::uint64_t value; };
inline const char* name(Layer x) {
  switch (x) {
    case Layer::Internal: return "internal";
    case Layer::Publication: return "publication";
    case Layer::Transport: return "transport";
    case Layer::Injection: return "injection";
  }
  return "unknown";
}
inline const char* name(Phase x) {
  switch (x) {
    case Phase::Pre: return "pre";
    case Phase::Post: return "post";
    case Phase::Combinational: return "comb";
    case Phase::Window: return "window";
  }
  return "unknown";
}
inline constexpr std::uint64_t unknown_cycle = UINT64_MAX;

class Monitor {
 public:
  static Monitor& instance() { static thread_local Monitor m; return m; }
  void set_cycle(std::uint64_t cycle) { global_cycle_ = cycle; }
  std::uint64_t cycle() const { return global_cycle_; }
  std::uint64_t failures() const { return failures_; }

  void observe(const char* domain, const char* rule, std::uint64_t cycle,
               Layer layer, Phase phase, bool checked, bool ok,
               std::initializer_list<Field> fields) {
    if (fields.size() > Event{}.fields.size())
      throw std::length_error("diagnostic field capacity exceeded");
    auto& d = domains_[domain];
    const std::string key = std::string(rule) + "/" + name(layer) + "/" + name(phase);
    auto& count = d.counts[key];
    ++count.samples;
    count.checked += checked;
    count.failed += checked && !ok;
    Event e{rule, cycle, global_cycle_, layer, phase, checked, ok, {}, fields.size()};
    std::copy(fields.begin(), fields.end(), e.fields.begin());
    d.history[d.next] = e;
    d.next = (d.next + 1) % d.history.size();
    if (d.size < d.history.size()) ++d.size;
    if (checked && !ok) {
      ++failures_;
      if (count.failed == 1) {
        // A new rule failure saves its own preceding context, even if another
        // rule in this domain has already fired. Repeats still count in full.
        for (const auto& entry : domains_) {
          const auto& h = entry.second;
          for (std::size_t i = 0; i < h.size; ++i)
            emit("context", entry.first.c_str(), h.history[(h.next + h.history.size() - h.size + i) % h.history.size()]);
        }
        emit("first_failure", domain, e);
        d.follow = 32;
        std::fflush(out_);
        return;
      }
    }
    if (d.follow) { emit("following", domain, e); --d.follow; }
  }

  // Sparse join points are always retained. Caller supplies the global window
  // identity and hashes of the actual bytes, not a reconstructed transport.
  void checkpoint(const char* domain, const char* rule, std::uint64_t cycle,
                  Layer layer, std::initializer_list<Field> fields) {
    if (fields.size() > Event{}.fields.size())
      throw std::length_error("diagnostic field capacity exceeded");
    Event e{rule, cycle, cycle, layer, Phase::Window, false, true, {}, fields.size()};
    std::copy(fields.begin(), fields.end(), e.fields.begin());
    emit("checkpoint", domain, e);
  }

  ~Monitor() {
    for (const auto& domain : domains_) {
      for (const auto& row : domain.second.counts) {
        std::fputs("{\"type\":\"coverage\",\"domain\":", out_); quoted(domain.first.c_str());
        std::fputs(",\"rule\":", out_); quoted(row.first.c_str());
        std::fprintf(out_, ",\"samples\":%llu,\"checked\":%llu,\"failed\":%llu}\n",
                     ull(row.second.samples), ull(row.second.checked), ull(row.second.failed));
      }
    }
    std::fprintf(out_, "{\"type\":\"summary\",\"failed\":%llu}\n", ull(failures_));
    if (std::fflush(out_) != 0) std::abort();
    if (owned_ && std::fclose(out_) != 0) std::abort();
  }

 private:
  struct Event {
    const char* rule = "";
    std::uint64_t cycle = 0, global_cycle = unknown_cycle;
    Layer layer = Layer::Internal;
    Phase phase = Phase::Pre;
    bool checked = false, ok = true;
    std::array<Field, 24> fields{};
    std::size_t size = 0;
  };
  struct Count { std::uint64_t samples = 0, checked = 0, failed = 0; };
  struct Domain {
    std::array<Event, 96> history{};
    std::size_t next = 0, size = 0, follow = 0;
    std::map<std::string, Count> counts;
  };
  Monitor() {
    const char* directory = std::getenv("CHISA_DIAGNOSTIC_DIR");
    if (directory && *directory) {
      const std::string path = std::string(directory) + "/diagnostic-" +
          std::to_string(::getpid()) + "-" + std::to_string(::syscall(SYS_gettid)) + ".jsonl";
      out_ = std::fopen(path.c_str(), "wx");
      if (!out_) throw std::runtime_error("cannot create diagnostic log: " + path);
      owned_ = true;
    } else out_ = stderr;
    std::fputs("{\"type\":\"identity\",\"schema\":1,\"build\":", out_);
    const char* identity = std::getenv("CHISA_DIAGNOSTIC_BUILD_ID");
    quoted(identity ? identity : "unrecorded");
#if defined(BOOM_GUIDER_CFG_MEDIUMBOOM_RC)
    const char* configuration = "medium";
#elif defined(BOOM_GUIDER_CFG_LARGEBOOM_RC)
    const char* configuration = "large";
#else
    const char* configuration = "other";
#endif
    std::fputs(",\"configuration\":", out_); quoted(configuration);
    std::fprintf(out_, ",\"pid\":%ld,\"tid\":%ld}\n", long(::getpid()), long(::syscall(SYS_gettid)));
  }
  static unsigned long long ull(std::uint64_t x) { return static_cast<unsigned long long>(x); }
  void quoted(const char* text) {
    std::fputc('"', out_);
    for (const unsigned char* p = reinterpret_cast<const unsigned char*>(text); *p; ++p) {
      if (*p == '"' || *p == '\\') { std::fputc('\\', out_); std::fputc(*p, out_); }
      else if (*p < 32) std::fprintf(out_, "\\u%04x", unsigned(*p));
      else std::fputc(*p, out_);
    }
    std::fputc('"', out_);
  }
  void emit(const char* type, const char* domain, const Event& e) {
    std::fputs("{\"type\":", out_); quoted(type);
    std::fputs(",\"domain\":", out_); quoted(domain);
    std::fputs(",\"rule\":", out_); quoted(e.rule);
    std::fprintf(out_, ",\"cycle\":%llu,\"global_cycle\":%llu,\"layer\":\"%s\",\"phase\":\"%s\",\"checked\":%s,\"ok\":%s,\"fields\":{",
                 ull(e.cycle), ull(e.global_cycle), name(e.layer), name(e.phase),
                 e.checked ? "true" : "false", e.ok ? "true" : "false");
    for (std::size_t i = 0; i < e.size; ++i) {
      if (i) std::fputc(',', out_);
      quoted(e.fields[i].name);
      std::fprintf(out_, ":%llu", ull(e.fields[i].value));
    }
    std::fputs("}}\n", out_);
    if (std::ferror(out_)) throw std::runtime_error("diagnostic log write failed");
  }
  std::FILE* out_ = nullptr;
  bool owned_ = false;
  std::uint64_t global_cycle_ = unknown_cycle, failures_ = 0;
  std::map<std::string, Domain> domains_;
};

inline void set_cycle(std::uint64_t cycle) { Monitor::instance().set_cycle(cycle); }
inline std::uint64_t cycle() { return Monitor::instance().cycle(); }
inline void sample(const char* domain, const char* rule, std::uint64_t cycle,
                   Layer layer, Phase phase, std::initializer_list<Field> fields) {
  Monitor::instance().observe(domain, rule, cycle, layer, phase, false, true, fields);
}
inline void require(const char* domain, const char* rule, std::uint64_t cycle,
                    Layer layer, Phase phase, bool condition, std::initializer_list<Field> fields) {
  Monitor::instance().observe(domain, rule, cycle, layer, phase, true, condition, fields);
}
inline void checkpoint(const char* domain, const char* rule, std::uint64_t cycle,
                       Layer layer, std::initializer_list<Field> fields) {
  Monitor::instance().checkpoint(domain, rule, cycle, layer, fields);
}
// Correlation digest, not a cryptographic build identity. Hashes preserve byte
// order and length; source/binary identities are separately bound by receipts.
inline std::uint64_t digest(const void* data, std::size_t size) {
  const auto* bytes = static_cast<const unsigned char*>(data);
  std::uint64_t hash = UINT64_C(14695981039346656037);
  for (std::size_t i = 0; i < size; ++i) hash = (hash ^ bytes[i]) * UINT64_C(1099511628211);
  return hash;
}
}  // namespace chisa::diagnostic
#endif
