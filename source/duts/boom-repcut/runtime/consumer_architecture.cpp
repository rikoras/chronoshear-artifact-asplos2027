#include "sint_pod_v2.h"
#include "consumer_architecture.h"
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

namespace chisa::boom_repcut {
namespace {
// perf record --delay=-1 --control=fifo:CONTROL samples the target program.
// Commands are asynchronous; waiting for ACK after disabling all events can
// deadlock with perf's record loop. Normal timing runs leave this path unset.
void target_boundary(bool entry, const boom_model::RetirementEvent& event) {
  std::printf("CONSUMER_TARGET_BOUNDARY kind=%s cycle=%" PRIu64 " pc=%" PRIx64 "\n",
              entry ? "entry" : "exit", event.cycle, event.pc);
  struct PerfControl {
    int control = -1;
    PerfControl() {
      const char* path = std::getenv("CHISA_PERF_CONTROL");
      if (!path) return;
      control = ::open(path, O_WRONLY);
      if (control < 0) throw std::runtime_error("cannot open perf control FIFO");
    }
    ~PerfControl() { if (control >= 0) ::close(control); }
    void send(bool enable) {
      if (control < 0) return;
      const char* command = enable ? "enable\n" : "disable\n";
      const std::size_t length = enable ? 7 : 8;
      ssize_t sent;
      do { sent = ::write(control, command, length); } while (sent < 0 && errno == EINTR);
      if (sent != static_cast<ssize_t>(length)) throw std::runtime_error("perf control write failed");
    }
  };
  static PerfControl perf;
  perf.send(entry);
}

void trace_architecture(char side, std::uint64_t sequence, const boom_model::RetirementEvent& e) {
  static std::FILE* trace = [] {
    const char* path = std::getenv("CHISA_CONSUMER_ARCH_TRACE");
    return path ? std::fopen(path, "w") : nullptr;
  }();
  if (!trace) return;
  std::fprintf(trace, "ARCH_TRACE side=%c seq=%" PRIu64 " cycle=%" PRIu64
      " pc=%" PRIx64 " x=%u f=%u rd=%u value=%" PRIx64
      " store=%u address=%" PRIx64 " data=%" PRIx64 " size=%u\n",
      side, sequence, e.cycle, e.pc, e.writes_x, e.writes_f, e.rd, e.value,
      e.memory_write, e.memory_address, e.memory_value, e.memory_size);
}
}
void ConsumerArchitectureCheck::observe_model(const boom_model::RetirementEvent& event) {
  const auto previous = model_.retired();
  model_.observe(event);
  if (model_.retired() != previous) {
    ordered_.model(event);
    trace_architecture('M', model_.retired(), event);
  }
}
void ConsumerArchitectureCheck::consume_half(bool forward, std::uint64_t first, bool reset,
                                           const consumer_arch::Frame& captured) {
  using namespace consumer_arch;
  const auto& frame = captured;
  static const auto diagnostic_range = [] {
    std::array<std::uint64_t, 2> range{};
    const char* value = std::getenv("CHISA_CONSUMER_OBSERVER_RANGE");
    if (value && std::sscanf(value, "%" SCNu64 ":%" SCNu64, &range[0], &range[1]) != 2)
      throw std::runtime_error("CHISA_CONSUMER_OBSERVER_RANGE requires FROM:UNTIL");
    return range;
  }();
  for (unsigned p = 0; p < kWidth; ++p) {
    const unsigned lane = forward ? p : kWidth - 1 - p;
    const auto get = [&](unsigned id) { return frame.get(id, lane); };
    const bool diagnostic = first + p >= diagnostic_range[0] && first + p < diagnostic_range[1];
    if (diagnostic) {
      for (unsigned slot = 0; slot < kStoreEntries; ++slot) {
        if (!frame.seen[StoreAddress0 + slot] || !frame.seen[StoreData0 + slot]) {
          std::fprintf(stderr, "CONSUMER_OBSERVER_STORE cycle=%" PRIu64 " slot=%u unobserved=1\n", first+p,slot);
          continue;
        }
        std::fprintf(stderr, "CONSUMER_OBSERVER_STORE cycle=%" PRIu64
            " slot=%u address=%" PRIx64 " data=%" PRIx64 "\n",
            first + p, slot, get(StoreAddress0 + slot), get(StoreData0 + slot));
      }
      unsigned port = 0;
      for (const auto& write : frame.integer[lane]) {
        if (write.valid)
          std::fprintf(stderr, "CONSUMER_OBSERVER_WRITE cycle=%" PRIu64
              " port=%u physical=%u value=%" PRIx64 "\n",
              first + p, port, unsigned(write.address), write.data.lo);
        ++port;
      }
    }
    // Apply actual persistent PRF writes in RTL port order, including the
    // retiring edge's write bypass. No model value supplies this shadow.
    for (const auto& write : frame.integer[lane])
      if (write.valid) integer_[write.address] = write.data.lo;
    for (const auto& write : frame.floating[lane])
      if (write.valid) floating_[write.address] = write.data;
    if (reset) {
      debug_.fill(false);
      sequence_ = 0;
      continue;
    }
    if (!get(CoreClock)) continue;
    unsigned store_slot = 0;
    bool store_cursor_valid = false;
    for (unsigned bank = 0; bank < kCommitWidth; ++bank) {
      const unsigned offset = bank * kRetirementFields;
      const bool retires = get(RetireValid + offset) != 0;
#if defined(CHISA_WIDE_MODEL)
      // LSU advances the STQ cursor for each committing uses_stq uop,
      // including AMOs/fences not counted as ordinary architectural stores.
      const bool commits_store = get(CommitValid + offset) && get(RetireStore + offset);
#else
      const bool commits_store = retires && get(RetireStore + offset);
#endif
      if (commits_store && !store_cursor_valid) {
        store_slot = static_cast<unsigned>(get(StoreCommitHead));
        if (store_slot >= kStoreEntries)
          throw std::runtime_error("committing store queue head out of range");
        store_cursor_valid = true;
      }
      if (retires) {
        boom_model::RetirementEvent event;
        event.valid = true;
        event.sequence = ++sequence_;
        event.cycle = first + p;
        const unsigned row = static_cast<unsigned>(get(RobHead));
        if (row >= kRobRows) throw std::runtime_error("retiring ROB row out of range");
        event.debug_mode = debug_[row * kCommitWidth + bank];
        const unsigned ftq = get(RetireFtq + offset) & (kFtqEntries - 1u);
        event.pc = ((get(FtqPc0 + ftq) & ~UINT64_C(63)) | get(RetirePcLow + offset)) -
                   (get(RetireEdge + offset) ? 2u : 0u);
        event.pc &= (UINT64_C(1) << 40) - 1;
        event.rd = get(RetireRd + offset) & 31u;
        event.writes_x = get(RetireRdValid + offset) && get(RetireRdType + offset) == 0 && event.rd != 0;
        event.writes_f = get(RetireRdValid + offset) && get(RetireRdType + offset) == 1;
        const auto physical = get(RetirePdst + offset);
        if (event.writes_x) {
          if (physical >= integer_.size()) throw std::runtime_error("retiring integer PRF index out of range");
          event.value = integer_[physical];
        } else if (event.writes_f) {
          if (physical >= floating_.size()) throw std::runtime_error("retiring floating PRF index out of range");
          const auto raw = floating_[physical];
          event.value = sfp::ieee64_view((static_cast<sfp::rec_t>(raw.hi) << 64) | raw.lo);
        }
        if (get(RetireStore + offset)) {
          if (!commits_store)
            throw std::runtime_error("architectural store retirement without a ROB store commit");
          event.memory_write = get(StoreCommand0 + store_slot) == 1;
          if (event.memory_write) {
            event.memory_size = get(StoreSize0 + store_slot);
            if (event.memory_size > 3) throw std::runtime_error("retiring store size out of range");
            event.memory_address = get(StoreAddress0 + store_slot);
            const unsigned bits = 8u << event.memory_size;
            event.memory_value = get(StoreData0 + store_slot) &
                                 (bits == 64 ? UINT64_MAX : (UINT64_C(1) << bits) - 1);
          }
        }
        if (diagnostic)
          std::fprintf(stderr, "CONSUMER_OBSERVER_RETIRE cycle=%" PRIu64
              " row=%u bank=%u ftq=%u pc=%" PRIx64
              " enqueue_debug=%u current_debug=%u physical=%u rd=%u value=%" PRIx64 "\n",
              event.cycle, row, bank, ftq, event.pc, unsigned(debug_[row * kCommitWidth + bank]),
              unsigned(get(DebugMode)), unsigned(physical), unsigned(event.rd), event.value);
        const auto previous = consumer_.retired();
        const bool finished_before = consumer_.finished();
        consumer_.observe(event);
        if (consumer_.retired() != previous) {
          ordered_.rtl(event);
          if (previous == 0) target_boundary(true, event);
          if (!finished_before && consumer_.finished()) target_boundary(false, event);
          trace_architecture('R', consumer_.retired(), event);
          static const bool stop_after_context = std::getenv("CHISA_ARCH_STOP_AFTER_CONTEXT") != nullptr;
          if (stop_after_context && ordered_.context_complete())
            throw std::runtime_error("first architectural divergence context saved");
        }
      }
      if (commits_store)
        store_slot = store_slot + 1 == kStoreEntries ? 0 : store_slot + 1;
    }
    // Retire all old row banks before a same-edge enqueue can reuse them.
    for (unsigned bank = 0; bank < kCommitWidth; ++bank) {
      if (!get(EnqueueValid + bank * kRetirementFields)) continue;
      const unsigned row = static_cast<unsigned>(get(RobTail));
      if (row >= kRobRows) throw std::runtime_error("enqueuing ROB row out of range");
      debug_[row * kCommitWidth + bank] = get(DebugMode) != 0;
      if (diagnostic)
        std::fprintf(stderr, "CONSUMER_OBSERVER_ENQUEUE cycle=%" PRIu64
            " row=%u bank=%u debug=%u\n", first + p, row, bank, unsigned(get(DebugMode)));
    }
  }
}
} // namespace chisa::boom_repcut
