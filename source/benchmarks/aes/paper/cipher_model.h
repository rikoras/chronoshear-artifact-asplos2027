#pragma once

// Cycle model of aes/Cipher.scala. The round key is an input each cycle;
// Cipher itself does not perform key expansion. No RTL or recorded values
// participate in this model's transitions.
#include <array>
#include <cstdint>
#if defined(__AES__)
#include <wmmintrin.h>
#endif

namespace chisa::aes_model {
using Bytes = std::array<std::uint8_t, 16>;
constexpr std::uint8_t xtime(std::uint8_t x) {
  return static_cast<std::uint8_t>((x << 1) ^ ((x & 0x80) ? 0x1b : 0));
}
constexpr std::uint8_t multiply(std::uint8_t a, std::uint8_t b) {
  std::uint8_t r = 0;
  for (unsigned i = 0; i < 8; ++i) {
    if (b & 1) r ^= a;
    a = xtime(a); b >>= 1;
  }
  return r;
}
constexpr std::uint8_t rotate(std::uint8_t x, unsigned n) {
  return static_cast<std::uint8_t>((x << n) | (x >> (8 - n)));
}
constexpr std::uint8_t substitute(std::uint8_t x) {
  std::uint8_t inverse = 1, base = x;
  for (unsigned power = 254; power; power >>= 1) {
    if (power & 1) inverse = multiply(inverse, base);
    base = multiply(base, base);
  }
  return inverse ^ rotate(inverse, 1) ^ rotate(inverse, 2) ^
         rotate(inverse, 3) ^ rotate(inverse, 4) ^ 0x63;
}
constexpr auto sbox_table() {
  std::array<std::uint8_t, 256> table{};
  for (unsigned i = 0; i < table.size(); ++i) table[i] = substitute(i);
  return table;
}
inline constexpr auto sbox = sbox_table();

inline Bytes portable_round(const Bytes& state, const Bytes& key, bool last) {
  Bytes shifted{}, result{};
  for (unsigned col = 0; col < 4; ++col)
    for (unsigned row = 0; row < 4; ++row)
      shifted[col * 4 + row] = sbox[state[((col + row) % 4) * 4 + row]];
  for (unsigned col = 0; col < 4; ++col) {
    const unsigned i = 4 * col;
    const auto sum = shifted[i] ^ shifted[i+1] ^ shifted[i+2] ^ shifted[i+3];
    for (unsigned row = 0; row < 4; ++row) {
      const auto value = shifted[i+row];
      result[i+row] = (last ? value : value ^ sum ^
          xtime(value ^ shifted[i+(row+1)%4])) ^ key[i+row];
    }
  }
  return result;
}

struct CipherModel {
  Bytes state{};
  std::uint8_t stm = 0;
  std::uint8_t rounds = 0;
  bool valid() const { return rounds == 11; }
  Bytes output() const { return valid() ? state : Bytes{}; }

  void step(bool reset, bool start, const Bytes& plaintext,
            const Bytes& round_key, bool accelerated = true) {
    if (reset) { state = {}; stm = 0; rounds = 0; return; }
    if (stm == 0) {
      state = {}; rounds = 0; stm = start ? 1 : 0;
    } else if (stm == 1) {
      for (unsigned i = 0; i < 16; ++i) state[i] = plaintext[i] ^ round_key[i];
      rounds = (rounds + 1) & 15; stm = 2;
    } else {
      const bool last = rounds == 10;
#if defined(__AES__)
      if (accelerated) {
        const auto s = _mm_loadu_si128(reinterpret_cast<const __m128i*>(state.data()));
        const auto k = _mm_loadu_si128(reinterpret_cast<const __m128i*>(round_key.data()));
        _mm_storeu_si128(reinterpret_cast<__m128i*>(state.data()),
                        last ? _mm_aesenclast_si128(s, k) : _mm_aesenc_si128(s, k));
      } else
#else
      (void)accelerated;
#endif
        state = portable_round(state, round_key, last);
      rounds = (rounds + 1) & 15;
      if (last) stm = 0;
    }
  }
};
}  // namespace chisa::aes_model
