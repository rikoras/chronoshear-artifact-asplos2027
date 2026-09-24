#pragma once
#include <algorithm>
#include <cstddef>

namespace chisa::boom_model::wide {
// A non-owning column in the final record. There is no backing buffer, dirty
// state or publication step. Functional writes are the record writes.
template<class T> class RecordColumn {
 public:
  template<std::size_t N> void bind(T (&array)[N]) { data_ = array; size_ = N; }
  T& operator[](std::size_t i) { return data_[i]; }
  const T& operator[](std::size_t i) const { return data_[i]; }
  T* data() { return data_; }
  const T* data() const { return data_; }
  void fill(T value) { std::fill_n(data_, size_, value); }
 private:
  T* data_ = nullptr;
  std::size_t size_ = 0;
};
}  // namespace chisa::boom_model::wide
