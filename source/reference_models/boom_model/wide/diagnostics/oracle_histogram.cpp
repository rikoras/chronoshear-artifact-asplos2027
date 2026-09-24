// Diagnostic-only link interposer. No RTL/model/checker code is changed.
// It recognizes the exact generated Oracle fprintf formats, aggregates every
// event, and forwards all other calls (including unsupported Oracle formats).
// Enable with CHISA_ORACLE_HISTOGRAM=/new/path/report.json. Both fprintf and
// glibc's fortified __fprintf_chk must be wrapped when linking.
#include <algorithm>
#include <array>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <inttypes.h>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>
#include "../../common/diagnostic_monitor.h"

extern "C" int __vfprintf_chk(FILE*, int, const char*, va_list);
namespace {
constexpr uint64_t kSeed = UINT64_C(14695981039346656037), kPrime = UINT64_C(1099511628211);
struct Event { int lane = 0, cycle = 0; uint64_t rtl = 0, oracle = 0; unsigned variant = 0; };
struct Field {
  std::string kind, name;
  int word = -1;
  uint64_t count = 0, digest = kSeed;
  std::array<uint64_t,3> variants{};
  Event first{}, last{};
  std::array<Event,4> samples{};
  unsigned sample_count = 0;
};
struct Format { bool known = false; Field* field = nullptr; unsigned variant = 0; size_t fixed_chars = 0; const char* diagnostic_rule = nullptr; };
struct State {
  std::string output;
  std::mutex mutex;
  std::map<std::string,Field> fields;
  std::unordered_map<const char*,Format> formats;
  uint64_t total = 0, parsed = 0, unsupported = 0;
  State() { if (const char* p = std::getenv("CHISA_ORACLE_HISTOGRAM")) output = p; }
};
State& state() { static State* s = new State; return *s; }
const char* variant_name(unsigned n) { return n == 1 ? "window-boundary" : n == 2 ? "quiet-hold" : "regular"; }

Format identify(State& s, const char* text) {
  Format result;
  const std::string fmt(text), prefix("ORACLE MISMATCH ");
  const std::string marker(" lane=%d cyc=%d rtl=0x%" PRIx64 " oracle=0x%" PRIx64);
  const auto pos = fmt.find(marker, prefix.size());
  if (pos == std::string::npos) return result;
  const std::string suffix = fmt.substr(pos + marker.size());
  unsigned variant;
  if (suffix == "\n") variant = 0;
  else if (suffix == " [window-boundary]\n") variant = 1;
  else if (suffix == " [quiet-hold]\n") variant = 2;
  else return result;
  std::string label = fmt.substr(prefix.size(), pos-prefix.size());
  if (label.find('%') != std::string::npos) return result;
  std::string kind;
  if (label.rfind("reg=",0) == 0) kind = "reg";
  else if (label.rfind("comb=",0) == 0) kind = "comb";
  else return result;
  label.erase(0, kind.size()+1);
  int word = -1;
  if (const auto word_pos = label.find(" word="); word_pos != std::string::npos) {
    const auto digits = label.substr(word_pos+6);
    if (digits.empty() || digits.find_first_not_of("0123456789") != std::string::npos) return result;
    unsigned long value = std::strtoul(digits.c_str(), nullptr, 10);
    if (value > 1000000) return result;
    word = static_cast<int>(value); label.resize(word_pos);
  }
  if (label.empty() || label.find_first_of(" \t\n") != std::string::npos) return result;
  const std::string key = kind + "=" + label + (word < 0 ? "" : " word=" + std::to_string(word));
  auto [it, inserted] = s.fields.try_emplace(key);
  if (inserted) { it->second.kind = kind; it->second.name = label; it->second.word = word; }
  result.known = true; result.field = &it->second; result.variant = variant;
  result.diagnostic_rule = it->first.c_str();
  // Four conversions, with no flags/width/precision: preserve fprintf's
  // successful return length while avoiding a format/allocation per event.
  result.fixed_chars = fmt.size() - 2*std::strlen("%d") - 2*std::strlen("%" PRIx64);
  return result;
}
unsigned decimal_chars(int v) {
  const bool negative = v < 0;
  uint64_t magnitude = negative ? uint64_t(-int64_t(v)) : uint64_t(v);
  unsigned n = 1 + negative;
  while (magnitude >= 10) { magnitude /= 10; ++n; }
  return n;
}
unsigned hex_chars(uint64_t v) { return v == 0 ? 1 : (64-__builtin_clzll(v)+3)/4; }
void add(Field& f, const Event& e) {
  if (f.count == 0 || e.cycle < f.first.cycle) f.first = e;
  if (f.count == 0 || e.cycle > f.last.cycle) f.last = e;
  if (f.sample_count < f.samples.size()) f.samples[f.sample_count++] = e;
  ++f.count; ++f.variants[e.variant];
  for (uint64_t v : {uint64_t(int64_t(e.lane)), uint64_t(int64_t(e.cycle)), e.rtl, e.oracle, uint64_t(e.variant)})
    f.digest = (f.digest ^ v) * kPrime;
}
int intercept(FILE* stream, int fortified, const char* fmt, va_list args) {
  auto& s = state();
  if (s.output.empty() || std::strncmp(fmt, "ORACLE MISMATCH ", 16) != 0)
    return fortified < 0 ? std::vfprintf(stream, fmt, args) : __vfprintf_chk(stream, fortified, fmt, args);
  {
    std::lock_guard<std::mutex> lock(s.mutex);
    auto [it, inserted] = s.formats.try_emplace(fmt);
    if (inserted) it->second = identify(s, fmt);
    ++s.total;
    const auto& format = it->second;
    if (format.known) {
      Event e;
      e.lane = va_arg(args,int); e.cycle = va_arg(args,int);
      e.rtl = va_arg(args,uint64_t); e.oracle = va_arg(args,uint64_t); e.variant = format.variant;
      add(*format.field,e); ++s.parsed;
      // A first RTL difference also saves available native/publication history
      // in the persistent monitor. It is an exact comparison failure, not a
      // claim that an inactive payload affected an architectural operation.
      // Field names are owned by the stable map for the process lifetime.
      CHISA_DIAG(
        if (format.field->count == 1)
          chisa::diagnostic::require("rtl", format.diagnostic_rule,
            chisa::diagnostic::cycle(), chisa::diagnostic::Layer::Injection,
            chisa::diagnostic::Phase::Window, e.rtl == e.oracle,
            {{"reporter_cycle", static_cast<std::uint64_t>(static_cast<std::int64_t>(e.cycle))},
             {"lane", static_cast<std::uint64_t>(static_cast<std::int64_t>(e.lane))},
             {"word", static_cast<std::uint64_t>(static_cast<std::int64_t>(format.field->word))},
             {"rtl", e.rtl}, {"oracle", e.oracle}, {"variant", e.variant}});
      );
      return static_cast<int>(format.fixed_chars + decimal_chars(e.lane) + decimal_chars(e.cycle) +
                              hex_chars(e.rtl) + hex_chars(e.oracle));
    }
    ++s.unsupported;
  }
  // Fail open for logging; the external validator rejects incomplete format
  // coverage. Never suppress an Oracle format that has not been understood.
  return fortified < 0 ? std::vfprintf(stream, fmt, args) : __vfprintf_chk(stream, fortified, fmt, args);
}
void quote(FILE* file, const std::string& text) {
  std::fputc('"',file);
  for (unsigned char c : text) {
    if (c == '"' || c == '\\') { std::fputc('\\',file); std::fputc(c,file); }
    else if (c < 32) std::fprintf(file,"\\u%04x",c);
    else std::fputc(c,file);
  }
  std::fputc('"',file);
}
void event(FILE* file, const Event& e) {
  std::fprintf(file,"{\"lane\":%d,\"cycle\":%d,\"rtl\":\"0x%" PRIx64 "\",\"oracle\":\"0x%" PRIx64 "\",\"variant\":\"%s\"}",
               e.lane,e.cycle,e.rtl,e.oracle,variant_name(e.variant));
}
void dump() {
  auto& s = state();
  if (s.output.empty()) return;
  std::lock_guard<std::mutex> lock(s.mutex);
  FILE* file = std::fopen(s.output.c_str(),"w");
  if (!file) { std::perror("ORACLE_HISTOGRAM_OPEN"); return; }
  std::fprintf(file,"{\n\"schemaVersion\":1,\"wrapped_oracle_calls\":%" PRIu64 ",\"parsed_events\":%" PRIu64 ",\"unsupported_oracle_calls\":%" PRIu64 ",\"format_coverage_complete\":%s,\"unique_formats\":%zu,\"fields\":[\n",
               s.total,s.parsed,s.unsupported,s.unsupported ? "false":"true",s.formats.size());
  bool comma = false;
  for (const auto& [key,f] : s.fields) {
    if (comma) std::fputs(",\n",file); comma = true;
    std::fputs("{\"key\":",file);quote(file,key);std::fputs(",\"kind\":",file);quote(file,f.kind);
    std::fputs(",\"name\":",file);quote(file,f.name);
    std::fprintf(file,",\"word\":%d,\"count\":%" PRIu64 ",\"first\":",f.word,f.count);event(file,f.first);
    std::fputs(",\"last\":",file);event(file,f.last);
    std::fprintf(file,",\"digest\":\"0x%" PRIx64 "\",\"variants\":{\"regular\":%" PRIu64 ",\"window-boundary\":%" PRIu64 ",\"quiet-hold\":%" PRIu64 "},\"samples\":[",
                 f.digest,f.variants[0],f.variants[1],f.variants[2]);
    for (unsigned i=0;i<f.sample_count;++i) { if(i)std::fputc(',',file);event(file,f.samples[i]); }
    std::fputs("]}",file);
  }
  std::fputs("\n]}\n",file);
  if (std::fclose(file)) std::perror("ORACLE_HISTOGRAM_CLOSE");
}
__attribute__((constructor)) void install() { (void)state(); std::atexit(dump); }
}
extern "C" int __wrap_fprintf(FILE* stream, const char* fmt, ...) {
  va_list args;va_start(args,fmt);const int result=intercept(stream,-1,fmt,args);va_end(args);return result;
}
extern "C" int __wrap___fprintf_chk(FILE* stream, int flag, const char* fmt, ...) {
  va_list args;va_start(args,fmt);const int result=intercept(stream,flag,fmt,args);va_end(args);return result;
}
