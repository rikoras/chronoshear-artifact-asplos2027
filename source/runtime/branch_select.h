#ifndef ESSENT_BRANCH_SELECT_H
#define ESSENT_BRANCH_SELECT_H

#include <cstdint>
#include <cstring>
#include <type_traits>
#if defined(__x86_64__)
#include <immintrin.h>
#endif

// Use only when both scalar operands are already available. Keeping the
// select explicit prevents LLVM from turning a cheap state choice back into
// a branch. Vector comb loops use the normal vectorizable expression path.
template<typename U>
static inline __attribute__((always_inline)) U essent_select_word(bool take, U yes, U no) {
  static_assert(std::is_unsigned<U>::value && (sizeof(U) == 4 || sizeof(U) == 8));
#if defined(__x86_64__) && (defined(__GNUC__) || defined(__clang__))
  const uint8_t condition = static_cast<uint8_t>(take);
  asm("testb %b2, %b2\n\tcmovz %1, %0" : "+r"(yes) : "r"(no), "q"(condition) : "cc");
  return yes;
#else
  return take ? yes : no;
#endif
}

template<typename T>
static inline __attribute__((always_inline)) const T* essent_select_ptr(
    bool take, const T* yes, const T* no) {
  return reinterpret_cast<const T*>(essent_select_word<uintptr_t>(take,
      reinterpret_cast<uintptr_t>(yes), reinterpret_cast<uintptr_t>(no)));
}

template<typename T>
static inline __attribute__((always_inline)) T essent_index_or_seed(
    int index, const T* values, const T& seed) {
  const bool valid = index >= 0;
  // Both candidate pointers must be legal even when there is no earlier write.
  const unsigned safe_index = static_cast<unsigned>(index) & (0u - unsigned(valid));
  return *essent_select_ptr(valid, values + safe_index, &seed);
}

// W32 scalar fields fit in one to four vector registers. Table permutation
// avoids indexed loads and per-lane branches; negative indices select seed.
// The boundary lane is written back with its original value.
template<int W, typename T>
static inline bool essent_hold_permute(T* output, const int16_t* indices,
                                     const T* values, const T& seed) {
#if defined(__AVX512F__) && defined(__AVX512BW__) && defined(__AVX512VL__)
  if constexpr (W == 32 && std::is_trivially_copyable<T>::value &&
                (sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8)) {
    uint64_t bits = 0;
    std::memcpy(&bits, &seed, sizeof(T));
    if constexpr (sizeof(T) == 1) {
#if defined(__AVX512VBMI__)
      const __m512i index = _mm512_loadu_si512(indices);
      const __mmask32 valid = _mm512_cmpge_epi16_mask(index, _mm512_setzero_si512());
      const __m256i data = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(values));
      const __m256i picked = _mm256_permutexvar_epi8(_mm512_cvtepi16_epi8(index), data);
      _mm256_storeu_si256(reinterpret_cast<__m256i*>(output),
          _mm256_mask_mov_epi8(_mm256_set1_epi8(static_cast<char>(bits)), valid, picked));
      return true;
#endif
    } else if constexpr (sizeof(T) == 2) {
      const __m512i index = _mm512_loadu_si512(indices);
      const __mmask32 valid = _mm512_cmpge_epi16_mask(index, _mm512_setzero_si512());
      const __m512i picked = _mm512_permutexvar_epi16(index, _mm512_loadu_si512(values));
      _mm512_storeu_si512(output,
          _mm512_mask_mov_epi16(_mm512_set1_epi16(static_cast<short>(bits)), valid, picked));
      return true;
    } else if constexpr (sizeof(T) == 4) {
      const __m512i lo = _mm512_loadu_si512(values);
      const __m512i hi = _mm512_loadu_si512(values + 16);
      for (int base = 0; base < 32; base += 16) {
        const __m512i index = _mm512_cvtepi16_epi32(
            _mm256_loadu_si256(reinterpret_cast<const __m256i*>(indices + base)));
        const __mmask16 valid = _mm512_cmpge_epi32_mask(index, _mm512_setzero_si512());
        const __m512i picked = _mm512_permutex2var_epi32(lo, index, hi);
        _mm512_storeu_si512(output + base,
            _mm512_mask_mov_epi32(_mm512_set1_epi32(static_cast<int>(bits)), valid, picked));
      }
      return true;
    } else {
      const __m512i a = _mm512_loadu_si512(values);
      const __m512i b = _mm512_loadu_si512(values + 8);
      const __m512i c = _mm512_loadu_si512(values + 16);
      const __m512i d = _mm512_loadu_si512(values + 24);
      for (int base = 0; base < 32; base += 8) {
        const __m512i index = _mm512_cvtepi16_epi64(
            _mm_loadu_si128(reinterpret_cast<const __m128i*>(indices + base)));
        const __mmask8 valid = _mm512_cmpge_epi64_mask(index, _mm512_setzero_si512());
        const __mmask8 upper = _mm512_cmpge_epi64_mask(index, _mm512_set1_epi64(16));
        const __m512i picked = _mm512_mask_blend_epi64(upper,
            _mm512_permutex2var_epi64(a, index, b), _mm512_permutex2var_epi64(c, index, d));
        _mm512_storeu_si512(output + base,
            _mm512_mask_mov_epi64(_mm512_set1_epi64(static_cast<long long>(bits)), valid, picked));
      }
      return true;
    }
  }
#endif
  (void)output; (void)indices; (void)values; (void)seed;
  return false;
}

#endif
