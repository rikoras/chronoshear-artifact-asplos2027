#pragma once
#include <array>
#include <cstddef>
#include <stdexcept>

namespace chisa::boom_system::protocol {

// A bounded software FIFO. Occupancy drives its behavior. The last unmatched
// push/pop is retained separately to describe a ring's wrap state to observers.
template<class T, std::size_t Capacity> class Fifo {
  static_assert(Capacity > 0);
 public:
  bool empty() const { return count_ == 0; }
  bool full() const { return count_ == Capacity; }
  std::size_t count() const { return count_; }
  std::size_t read_index() const { return read_; }
  std::size_t write_index() const { return write_; }
  bool wrap_state() const { return last_was_push_; }
  const T& head() const { return storage_[read_]; }
  const std::array<T, Capacity>& storage() const { return storage_; }

  // The caller computes both accepted transfers from the same cycle-start
  // view. Clearing control does not clear the payload memory.
  bool commit(bool push, const T& value, bool pop, bool reset) {
    if (push && full() && !pop) throw std::logic_error("FIFO overflow");
    if (pop && empty()) throw std::logic_error("FIFO underflow");
    bool changed = false;
    if (push) { changed = !(storage_[write_] == value); storage_[write_] = value; }
    const auto old_read=read_, old_write=write_, old_count=count_;
    const bool old_wrap=last_was_push_;
    if (reset) {
      read_=write_=count_=0;last_was_push_=false;
    } else {
      if (push) write_=(write_+1)%Capacity;
      if (pop) read_=(read_+1)%Capacity;
      count_ += unsigned(push);count_ -= unsigned(pop);
      if (push != pop) last_was_push_=push;
    }
    return changed || old_read!=read_ || old_write!=write_ || old_count!=count_ || old_wrap!=last_was_push_;
  }
 private:
  std::array<T, Capacity> storage_{};
  std::size_t read_=0, write_=0, count_=0;
  bool last_was_push_=false;
};
}  // namespace chisa::boom_system::protocol
