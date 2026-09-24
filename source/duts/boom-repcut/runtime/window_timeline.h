#pragma once
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <vector>

namespace chisa::boom_repcut {
// Diagnostic only: one writer per producer/consumer row; the last decoder
// owns expansion completion. Read only after all execution threads join.
// Release events are bracketed so preemption between a clock read and the
// release store cannot silently become an exact readiness timestamp.
class WindowTimeline {
 public:
  using Clock=std::chrono::steady_clock;
  struct Pair { std::uint64_t first=0,second=0; };
  WindowTimeline(std::uint64_t first,std::uint64_t last,unsigned partitions,bool early=false)
      : first_(first),last_(last),producer_begin(last-first),source(last-first),
        expanded(last-first),consumer(partitions,std::vector<Pair>(last-first)),
        ready(early ? partitions : 0,std::vector<Pair>(last-first)) {
    const char* path=std::getenv("CHISA_WINDOW_TIMELINE_PATH");
    if (!path || !*path) throw std::runtime_error("CHISA_WINDOW_TIMELINE_PATH is required");
    output_=std::fopen(path,"wx");
    if (!output_) throw std::runtime_error("cannot exclusively create window timeline");
  }
  ~WindowTimeline() { if(output_) std::fclose(output_); }
  bool selected(std::uint64_t w) const { return first_<=w && w<last_; }
  std::size_t row(std::uint64_t w) const { return w-first_; }
  static std::uint64_t ns(Clock::time_point t) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
  }
  static std::uint64_t now() { return ns(Clock::now()); }
  void write(unsigned cycles_per_window) {
    std::fprintf(output_,"window,cycle,producer_begin,source_before,source_after,expand_before,expand_after");
    for(unsigned p=0;p<consumer.size();++p) std::fprintf(output_,",p%u_begin,p%u_end",p,p);
    for(unsigned p=0;p<ready.size();++p) std::fprintf(output_,",p%u_ready_before,p%u_ready_after",p,p);
    std::fputc('\n',output_);
    for(std::uint64_t w=first_;w<last_;++w) {
      const auto i=row(w);
      std::fprintf(output_,"%llu,%llu,%llu,%llu,%llu,%llu,%llu",
        (unsigned long long)w,(unsigned long long)(w*cycles_per_window),
        (unsigned long long)producer_begin[i],
        (unsigned long long)source[i].first,(unsigned long long)source[i].second,
        (unsigned long long)expanded[i].first,(unsigned long long)expanded[i].second);
      for(const auto& owner:consumer) std::fprintf(output_,",%llu,%llu",
        (unsigned long long)owner[i].first,(unsigned long long)owner[i].second);
      for(const auto& owner:ready) std::fprintf(output_,",%llu,%llu",
        (unsigned long long)owner[i].first,(unsigned long long)owner[i].second);
      std::fputc('\n',output_);
    }
    if(std::fflush(output_) || std::ferror(output_)) throw std::runtime_error("window timeline write failed");
  }
 private:
  std::uint64_t first_,last_;
 public:
  std::vector<std::uint64_t> producer_begin;
  std::vector<Pair> source,expanded;
  std::vector<std::vector<Pair>> consumer,ready;
 private:
  std::FILE* output_=nullptr;
};
inline std::unique_ptr<WindowTimeline> window_timeline;
} // namespace chisa::boom_repcut
