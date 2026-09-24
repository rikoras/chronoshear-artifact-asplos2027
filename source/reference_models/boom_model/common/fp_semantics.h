#pragma once
#include <cstdint>

namespace chisa::boom_model {
// FMV.X.W and FSW are bit transfers. Unlike single-precision arithmetic,
// they do not replace an unboxed source with the canonical NaN.
inline std::uint64_t fp_move_word_to_x(std::uint64_t bits) {
  return static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(bits)));
}
inline std::uint64_t fp_store_bits(std::uint64_t bits, bool single) {
  return single ? static_cast<std::uint32_t>(bits) : bits;
}
}  // namespace chisa::boom_model
