#ifndef BOOM_WATCHPOINT_H
#define BOOM_WATCHPOINT_H

// Env-gated watchpoints, ported verbatim from guiders/rocket/watchpoint.h.
// Zero cost when off. Turn on targeted debugging without recompiling:
//   WATCHPOINTS=issue_select,rob_enq ./validate_boom img 3000
//   WATCHPOINTS=all WP_CYCLES=160-170 ./validate_boom img 3000
//   WP_ABORT=1 ...   (abort() on first failing WP_ASSERT)
//
// In the guider/harness code, sprinkle:
//   WP_LOG("issue_select", "slot=%d prs1=%d p1=%d", s, prs1, p1);
//   WP_ASSERT("rob_enq", tail_row == uop.rob_idx);
//   WATCHPOINT("lsu", { dump_ldq(); });

#ifndef UNLIKELY
#define UNLIKELY(x) __builtin_expect(static_cast<bool>(x), 0)
#endif

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>
#include <unordered_set>
#include <string>

class WatchpointManager {
public:
    static WatchpointManager& instance() {
        static WatchpointManager mgr;
        return mgr;
    }
    void configure_from_env() {
        if (const char* names = getenv("WATCHPOINTS")) {
            if (strcmp(names, "all") == 0) {
                all_ = true;
            } else {
                const char* p = names;
                while (*p) {
                    while (*p == ',' || *p == ' ') ++p;
                    const char* start = p;
                    while (*p && *p != ',' && *p != ' ') ++p;
                    if (p > start) enabled_.emplace(start, p);
                }
            }
        }
        if (const char* cyc = getenv("WP_CYCLES")) {
            if (sscanf(cyc, "%d-%d", &cycle_min_, &cycle_max_) == 2) use_cycle_filter_ = true;
        }
        if (getenv("WP_ABORT")) abort_on_assert_ = true;
    }
    bool any_active() const { return all_ || !enabled_.empty(); }
    bool is_enabled(const char* name) const {
        if (!all_ && enabled_.find(name) == enabled_.end()) return false;
        if (use_cycle_filter_ && (cycle_ < cycle_min_ || cycle_ > cycle_max_)) return false;
        return true;
    }
    void set_cycle(int c) { cycle_ = c; }
    int cycle() const { return cycle_; }
    bool should_abort() const { return abort_on_assert_; }
private:
    WatchpointManager() = default;
    std::unordered_set<std::string> enabled_;
    bool all_ = false;
    int cycle_ = 0;
    bool use_cycle_filter_ = false;
    bool abort_on_assert_ = false;
    int cycle_min_ = 0;
    int cycle_max_ = INT_MAX;
};

#ifdef CHISA_DISABLE_WATCHPOINTS
#define WP_CYCLE() (0)
#define WATCHPOINT(name, block) do { } while(0)
#define WATCHPOINT_IF(name, cond, block) do { } while(0)
#define WP_ASSERT(name, cond) do { } while(0)
#define WP_LOG(name, fmt, ...) do { } while(0)
#else
#define WP_CYCLE() WatchpointManager::instance().cycle()
#define WATCHPOINT(name, block) \
    do { if (UNLIKELY(WatchpointManager::instance().any_active()) && WatchpointManager::instance().is_enabled(name)) { block } } while(0)
#define WATCHPOINT_IF(name, cond, block) \
    do { if (UNLIKELY(WatchpointManager::instance().any_active()) && WatchpointManager::instance().is_enabled(name) && (cond)) { block } } while(0)
#define WP_ASSERT(name, cond) \
    do { \
        if (UNLIKELY(WatchpointManager::instance().any_active()) && WatchpointManager::instance().is_enabled(name) && !(cond)) { \
            fprintf(stderr, "[WP_ASSERT:%s FAILED c=%d] %s:%d\n  Condition: %s\n", \
                    name, WP_CYCLE(), __FILE__, __LINE__, #cond); \
            if (WatchpointManager::instance().should_abort()) abort(); \
        } \
    } while(0)
#define WP_LOG(name, fmt, ...) \
    do { \
        if (UNLIKELY(WatchpointManager::instance().any_active()) && WatchpointManager::instance().is_enabled(name)) { \
            fprintf(stderr, "[WP:%s c=%d] " fmt "\n", name, WP_CYCLE(), ##__VA_ARGS__); \
        } \
    } while(0)
#endif

#endif // BOOM_WATCHPOINT_H
